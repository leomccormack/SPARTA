/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2018 - Leo McCormack.
 
 SPARTA is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 SPARTA is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with SPARTA.  If not, see <http://www.gnu.org/licenses/>.
 
 ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

static int getMaxNumChannelsForFormat(AudioProcessor::WrapperType format) {
    switch(format){
        case juce::AudioProcessor::wrapperType_VST:  /* fall through */
        case juce::AudioProcessor::wrapperType_VST3: /* fall through */
        case juce::AudioProcessor::wrapperType_AAX:
            return 64;
        default:
            return MAX_NUM_CHANNELS;
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("outputOrder", "OutputOrder",
                                                                  juce::StringArray{"1st order","2nd order","3rd order","4th order","5th order","6th order","7th order","8th order","9th order","10th order"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("channelOrder", "ChannelOrder", juce::StringArray{"ACN", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("normType", "NormType", juce::StringArray{"N3D", "SN3D", "FuMa"}, 1));
    params.push_back(std::make_unique<juce::AudioParameterBool>("enableReflections", "EnableReflections", true));
    params.push_back(std::make_unique<juce::AudioParameterInt>("maxReflectionOrder", "MaxReflectionOrder", 0, 7, 1));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("wallAbsCoeff_pX", "WallAbsCoeff (x+)", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.341055f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("wallAbsCoeff_nX", "WallAbsCoeff (x-)", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.431295f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("wallAbsCoeff_pY", "WallAbsCoeff (y+)", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.351295f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("wallAbsCoeff_nY", "WallAbsCoeff (y-)", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.344335f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("wallAbsCoeff_pZ", "WallAbsCoeff (z+)", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.401775f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("wallAbsCoeff_nZ", "WallAbsCoeff (z-)", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.482095f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("roomX", "RoomWidth (x)", juce::NormalisableRange<float>(0.5f, 20.0f, 0.01f), 9.1f,
                                                                 AudioParameterFloatAttributes().withLabel("m")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("roomY", "RoomDepth (y)", juce::NormalisableRange<float>(0.5f, 20.0f, 0.01f), 8.0f,
                                                                 AudioParameterFloatAttributes().withLabel("m")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("roomZ", "RoomHeight (z)", juce::NormalisableRange<float>(0.5f, 6.0f, 0.01f), 3.0f,
                                                                 AudioParameterFloatAttributes().withLabel("m")));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numSources", "NumSources", 1, ROOM_SIM_MAX_NUM_SOURCES, 1,
                                                               AudioParameterIntAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numReceivers", "NumReceivers", 1, ROOM_SIM_MAX_NUM_RECEIVERS, 1,
                                                               AudioParameterIntAttributes().withAutomatable(false)));
    for(int i=0; i<ROOM_SIM_MAX_NUM_SOURCES; i++){
        params.push_back(std::make_unique<juce::AudioParameterFloat>("sourceX" + juce::String(i), "SourceX_" + juce::String(i+1), juce::NormalisableRange<float>(0.0f, 20.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withLabel("m")));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("sourceY" + juce::String(i), "SourceY_" + juce::String(i+1), juce::NormalisableRange<float>(0.0f, 20.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withLabel("m")));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("sourceZ" + juce::String(i), "SourceZ_" + juce::String(i+1), juce::NormalisableRange<float>(0.0f, 6.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withLabel("m")));
    }
    
    for(int i=0; i<ROOM_SIM_MAX_NUM_RECEIVERS; i++){
        params.push_back(std::make_unique<juce::AudioParameterFloat>("receiverX" + juce::String(i), "ReceiverX_" + juce::String(i+1), juce::NormalisableRange<float>(0.0f, 20.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withLabel("m")));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("receiverY" + juce::String(i), "ReceiverY_" + juce::String(i+1), juce::NormalisableRange<float>(0.0f, 20.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withLabel("m")));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("receiverZ" + juce::String(i), "ReceiverZ_" + juce::String(i+1), juce::NormalisableRange<float>(0.0f, 6.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withLabel("m")));
    }

    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "outputOrder"){
        ambi_roomsim_setOutputOrder(hAmbi, static_cast<SH_ORDERS>(newValue+1.001f));
    }
    else if (parameterID == "channelOrder"){
        ambi_roomsim_setChOrder(hAmbi, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "normType"){
        ambi_roomsim_setNormType(hAmbi, static_cast<int>(newValue+1.001f));
    }
    else if(parameterID == "enableReflections"){
        ambi_roomsim_setEnableIMSflag(hAmbi, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "maxReflectionOrder"){
        ambi_roomsim_setMaxReflectionOrder(hAmbi, static_cast<int>(newValue));
    }
    else if(parameterID == "wallAbsCoeff_pX"){
        ambi_roomsim_setWallAbsCoeff(hAmbi, 0, 0, newValue);
    }
    else if(parameterID == "wallAbsCoeff_nX"){
        ambi_roomsim_setWallAbsCoeff(hAmbi, 0, 1, newValue);
    }
    else if(parameterID == "wallAbsCoeff_pY"){
        ambi_roomsim_setWallAbsCoeff(hAmbi, 1, 0, newValue);
    }
    else if(parameterID == "wallAbsCoeff_nY"){
        ambi_roomsim_setWallAbsCoeff(hAmbi, 1, 1, newValue);
    }
    else if(parameterID == "wallAbsCoeff_pZ"){
        ambi_roomsim_setWallAbsCoeff(hAmbi, 2, 0, newValue);
    }
    else if(parameterID == "wallAbsCoeff_nZ"){
        ambi_roomsim_setWallAbsCoeff(hAmbi, 2, 1, newValue);
    }
    else if(parameterID == "roomX"){
        ambi_roomsim_setRoomDimX(hAmbi, newValue);
    }
    else if(parameterID == "roomY"){
        ambi_roomsim_setRoomDimY(hAmbi, newValue);
    }
    else if(parameterID == "roomZ"){
        ambi_roomsim_setRoomDimZ(hAmbi, newValue);
    } 
    else if(parameterID == "numSources"){
        ambi_roomsim_setNumSources(hAmbi, static_cast<int>(newValue));
    }
    else if(parameterID == "numReceivers"){
        ambi_roomsim_setNumReceivers(hAmbi, static_cast<int>(newValue));
    }
    for(int i=0; i<ROOM_SIM_MAX_NUM_SOURCES; i++){
        if(parameterID == "sourceX" + juce::String(i)){
            ambi_roomsim_setSourceX(hAmbi, i, newValue);
            setRefreshWindow(true);
            return;
        }
        else if(parameterID == "sourceY" + juce::String(i)){
            ambi_roomsim_setSourceY(hAmbi, i, newValue);
            setRefreshWindow(true);
            return;
        }
        else if(parameterID == "sourceZ" + juce::String(i)){
            ambi_roomsim_setSourceZ(hAmbi, i, newValue);
            setRefreshWindow(true);
            return;
        }
    }
    for(int i=0; i<ROOM_SIM_MAX_NUM_RECEIVERS; i++){
        if(parameterID == "receiverX" + juce::String(i)){
            ambi_roomsim_setReceiverX(hAmbi, i, newValue);
            setRefreshWindow(true);
            return;
        }
        else if(parameterID == "receiverY" + juce::String(i)){
            ambi_roomsim_setReceiverY(hAmbi, i, newValue);
            setRefreshWindow(true);
            return;
        }
        else if(parameterID == "receiverZ" + juce::String(i)){
            ambi_roomsim_setReceiverZ(hAmbi, i, newValue);
            setRefreshWindow(true);
            return;
        }
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("outputOrder", ambi_roomsim_getOutputOrder(hAmbi)-1);
    setParameterValue("channelOrder", ambi_roomsim_getChOrder(hAmbi)-1);
    setParameterValue("normType", ambi_roomsim_getNormType(hAmbi)-1);
    setParameterValue("enableReflections", ambi_roomsim_getEnableIMSflag(hAmbi));
    setParameterValue("maxReflectionOrder", ambi_roomsim_getMaxReflectionOrder(hAmbi));
    setParameterValue("wallAbsCoeff_pX", ambi_roomsim_getWallAbsCoeff(hAmbi, 0, 0));
    setParameterValue("wallAbsCoeff_nX", ambi_roomsim_getWallAbsCoeff(hAmbi, 0, 1));
    setParameterValue("wallAbsCoeff_pY", ambi_roomsim_getWallAbsCoeff(hAmbi, 1, 0));
    setParameterValue("wallAbsCoeff_nY", ambi_roomsim_getWallAbsCoeff(hAmbi, 1, 1));
    setParameterValue("wallAbsCoeff_pZ", ambi_roomsim_getWallAbsCoeff(hAmbi, 2, 0));
    setParameterValue("wallAbsCoeff_nZ", ambi_roomsim_getWallAbsCoeff(hAmbi, 2, 1));
    setParameterValue("roomX", ambi_roomsim_getRoomDimX(hAmbi));
    setParameterValue("roomY", ambi_roomsim_getRoomDimY(hAmbi));
    setParameterValue("roomZ", ambi_roomsim_getRoomDimZ(hAmbi));
    setParameterValue("numSources", ambi_roomsim_getNumSources(hAmbi));
    setParameterValue("numReceivers", ambi_roomsim_getNumReceivers(hAmbi));
    for(int i=0; i<ROOM_SIM_MAX_NUM_SOURCES; i++){
        setParameterValue("sourceX" + juce::String(i), ambi_roomsim_getSourceX(hAmbi, i));
        setParameterValue("sourceY" + juce::String(i), ambi_roomsim_getSourceY(hAmbi, i));
        setParameterValue("sourceZ" + juce::String(i), ambi_roomsim_getSourceZ(hAmbi, i));
    }
    for(int i=0; i<ROOM_SIM_MAX_NUM_RECEIVERS; i++){
        setParameterValue("receiverX" + juce::String(i), ambi_roomsim_getReceiverX(hAmbi, i));
        setParameterValue("receiverY" + juce::String(i), ambi_roomsim_getReceiverY(hAmbi, i));
        setParameterValue("receiverZ" + juce::String(i), ambi_roomsim_getReceiverZ(hAmbi, i));
    }
}

void PluginProcessor::setInternalStateUsingParameterValues()
{
    ambi_roomsim_setOutputOrder(hAmbi, getParameterChoice("outputOrder")+1);
    ambi_roomsim_setChOrder(hAmbi, getParameterChoice("channelOrder")+1);
    ambi_roomsim_setNormType(hAmbi, getParameterChoice("normType")+1);
    ambi_roomsim_setEnableIMSflag(hAmbi, getParameterBool("enableReflections"));
    ambi_roomsim_setMaxReflectionOrder(hAmbi, getParameterInt("maxReflectionOrder"));
    ambi_roomsim_setWallAbsCoeff(hAmbi, 0, 0, getParameterFloat("wallAbsCoeff_pX"));
    ambi_roomsim_setWallAbsCoeff(hAmbi, 0, 1, getParameterFloat("wallAbsCoeff_nX"));
    ambi_roomsim_setWallAbsCoeff(hAmbi, 1, 0, getParameterFloat("wallAbsCoeff_pY"));
    ambi_roomsim_setWallAbsCoeff(hAmbi, 1, 1, getParameterFloat("wallAbsCoeff_nY"));
    ambi_roomsim_setWallAbsCoeff(hAmbi, 2, 0, getParameterFloat("wallAbsCoeff_pZ"));
    ambi_roomsim_setWallAbsCoeff(hAmbi, 2, 1, getParameterFloat("wallAbsCoeff_nZ"));
    ambi_roomsim_setRoomDimX(hAmbi, getParameterFloat("roomX"));
    ambi_roomsim_setRoomDimY(hAmbi, getParameterFloat("roomY"));
    ambi_roomsim_setRoomDimZ(hAmbi, getParameterFloat("roomZ"));
    ambi_roomsim_setNumSources(hAmbi, getParameterInt("numSources"));
    ambi_roomsim_setNumReceivers(hAmbi, getParameterInt("numReceivers"));
    for(int i=0; i<ROOM_SIM_MAX_NUM_SOURCES; i++){
        ambi_roomsim_setSourceX(hAmbi, i, getParameterFloat("sourceX" + juce::String(i)));
        ambi_roomsim_setSourceY(hAmbi, i, getParameterFloat("sourceY" + juce::String(i)));
        ambi_roomsim_setSourceZ(hAmbi, i, getParameterFloat("sourceZ" + juce::String(i)));
    }
    for(int i=0; i<ROOM_SIM_MAX_NUM_RECEIVERS; i++){
        ambi_roomsim_setReceiverX(hAmbi, i, getParameterFloat("receiverX" + juce::String(i)));
        ambi_roomsim_setReceiverY(hAmbi, i, getParameterFloat("receiverY" + juce::String(i)));
        ambi_roomsim_setReceiverZ(hAmbi, i, getParameterFloat("receiverZ" + juce::String(i)));
    }
}

PluginProcessor::PluginProcessor() : 
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	ambi_roomsim_create(&hAmbi);
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();
    
    refreshWindow = true;
}

PluginProcessor::~PluginProcessor()
{
	ambi_roomsim_destroy(&hAmbi);
}

void PluginProcessor::setCurrentProgram (int /*index*/)
{
}

const String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    return 0;
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

const String PluginProcessor::getProgramName (int /*index*/)
{
    return String();
}

bool PluginProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

void PluginProcessor::changeProgramName (int /*index*/, const String& /*newName*/)
{
}

void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    nHostBlockSize = samplesPerBlock;
    nNumInputs =  jmin(getTotalNumInputChannels(), 256);
    nNumOutputs = jmin(getTotalNumOutputChannels(), 256);
    nSampleRate = (int)(sampleRate + 0.5);

	ambi_roomsim_init(hAmbi, nSampleRate);
    AudioProcessor::setLatencySamples(ambi_roomsim_getProcessingDelay());
}

void PluginProcessor::releaseResources()
{
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    ScopedNoDenormals noDenormals;
    
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels(), 256);
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels(), 256);
    float* const* bufferData = buffer.getArrayOfWritePointers();
    float* pFrameData[256];
    int frameSize = ambi_roomsim_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            ambi_roomsim_process(hAmbi, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
        }
    }
    else
        buffer.clear(); 
}

bool PluginProcessor::hasEditor() const
{
    return true; 
}

AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (*this);
}

void PluginProcessor::getStateInformation (MemoryBlock& destData)
{
    juce::ValueTree state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xmlState(state.createXml());
    xmlState->setTagName("AMBIROOMSIMPLUGINSETTINGS");
    xmlState->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10101
    
    /* Save */
    copyXmlToBinary(*xmlState, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("AMBIROOMSIMPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10101
            for(int i=0; i<ambi_roomsim_getMaxNumSources(); i++){
                if(xmlState->hasAttribute("SourceX" + String(i)))
                    ambi_roomsim_setSourceX(hAmbi, i, (float)xmlState->getDoubleAttribute("SourceX" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceY" + String(i)))
                    ambi_roomsim_setSourceY(hAmbi, i, (float)xmlState->getDoubleAttribute("SourceY" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceZ" + String(i)))
                    ambi_roomsim_setSourceZ(hAmbi, i, (float)xmlState->getDoubleAttribute("SourceZ" + String(i), 0.0f));
            }
            for(int i=0; i<ambi_roomsim_getMaxNumReceivers(); i++){
                if(xmlState->hasAttribute("ReceiverX" + String(i)))
                    ambi_roomsim_setReceiverX(hAmbi, i, (float)xmlState->getDoubleAttribute("ReceiverX" + String(i), 0.0f));
                if(xmlState->hasAttribute("ReceiverY" + String(i)))
                    ambi_roomsim_setReceiverY(hAmbi, i, (float)xmlState->getDoubleAttribute("ReceiverY" + String(i), 0.0f));
                if(xmlState->hasAttribute("ReceiverZ" + String(i)))
                    ambi_roomsim_setReceiverZ(hAmbi, i, (float)xmlState->getDoubleAttribute("ReceiverZ" + String(i), 0.0f));
            }
            for(int i=0; i<3; i++)
                for(int j=0; j<2; j++)
                    if(xmlState->hasAttribute("wallAbsCoeff" + String(i) + "_" + String(j)))
                        ambi_roomsim_setWallAbsCoeff(hAmbi, i, j, (float)xmlState->getDoubleAttribute("wallAbsCoeff" + String(i) + "_" + String(j), 0.0f));
            if(xmlState->hasAttribute("RoomX"))
                ambi_roomsim_setRoomDimX(hAmbi, (float)xmlState->getDoubleAttribute("RoomX", 0.0f));
            if(xmlState->hasAttribute("RoomY"))
                ambi_roomsim_setRoomDimY(hAmbi, (float)xmlState->getDoubleAttribute("RoomY", 0.0f));
            if(xmlState->hasAttribute("RoomZ"))
                ambi_roomsim_setRoomDimZ(hAmbi, (float)xmlState->getDoubleAttribute("RoomZ", 0.0f));
            if(xmlState->hasAttribute("nSources"))
                ambi_roomsim_setNumSources(hAmbi, xmlState->getIntAttribute("nSources", 1));
            if(xmlState->hasAttribute("nReceivers"))
                ambi_roomsim_setNumReceivers(hAmbi, xmlState->getIntAttribute("nReceivers", 1));
            
            if(xmlState->hasAttribute("NORM"))
                ambi_roomsim_setNormType(hAmbi, xmlState->getIntAttribute("NORM", 1));
            if(xmlState->hasAttribute("CHORDER"))
                ambi_roomsim_setChOrder(hAmbi, xmlState->getIntAttribute("CHORDER", 1));
            if(xmlState->hasAttribute("OUT_ORDER"))
                ambi_roomsim_setOutputOrder(hAmbi, xmlState->getIntAttribute("OUT_ORDER", 1));
            
            setParameterValuesUsingInternalState();
        }
        else if (xmlState->getIntAttribute("VersionCode")>=0x10101){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* Many hosts will also trigger parameterChanged() for all parameters after calling setStateInformation() */
            /* However, some hosts do not. Therefore, it is better to ensure that the internal state is always up-to-date by calling: */
            setInternalStateUsingParameterValues();
        }
    
        ambi_roomsim_refreshParams(hAmbi);
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
