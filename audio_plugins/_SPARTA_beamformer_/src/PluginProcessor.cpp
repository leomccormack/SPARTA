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
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("inputOrder", "InputOrder",
                                                                  juce::StringArray{"1st order","2nd order","3rd order","4th order","5th order","6th order","7th order","8th order","9th order","10th order"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("channelOrder", "ChannelOrder", juce::StringArray{"ACN", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("normType", "NormType", juce::StringArray{"N3D", "SN3D", "FuMa"}, 1));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("beamType", "BeamType", juce::StringArray{"Cardioid", "Hyper-Card", "Max-EV"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numBeams", "NumBeams", 1, MAX_NUM_OUTPUTS, 1, AudioParameterIntAttributes().withAutomatable(false)));
    for(int i=0; i<MAX_NUM_OUTPUTS; i++){
        params.push_back(std::make_unique<juce::AudioParameterFloat>("azim" + juce::String(i), "Azim_" + juce::String(i+1), juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f,
                                                                     AudioParameterFloatAttributes().withLabel(juce::String::fromUTF8(u8"°"))));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("elev" + juce::String(i), "Elev_" + juce::String(i+1), juce::NormalisableRange<float>(-90.0f, 90.0f, 0.01f), 0.0f,
                                                                     AudioParameterFloatAttributes().withLabel(juce::String::fromUTF8(u8"°"))));
    }
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "inputOrder"){
        beamformer_setBeamOrder(hBeam, static_cast<SH_ORDERS>(newValue+1.001f));
    }
    else if (parameterID == "channelOrder"){
        beamformer_setChOrder(hBeam, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "normType"){
        beamformer_setNormType(hBeam, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "beamType"){
        beamformer_setBeamType(hBeam, static_cast<int>(newValue+1.001f));
    }
    else if(parameterID == "numBeams"){
        beamformer_setNumBeams(hBeam, static_cast<int>(newValue));
        setRefreshWindow(true);
    }
    for(int i=0; i<MAX_NUM_OUTPUTS; i++){
        if(parameterID == "azim" + juce::String(i)){
            beamformer_setBeamAzi_deg(hBeam, i, newValue);
            setRefreshWindow(true);
            break;
        }
        else if(parameterID == "elev" + juce::String(i)){
            beamformer_setBeamElev_deg(hBeam, i, newValue);
            setRefreshWindow(true);
            break;
        }
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("inputOrder", beamformer_getBeamOrder(hBeam)-1);
    setParameterValue("channelOrder", beamformer_getChOrder(hBeam)-1);
    setParameterValue("normType", beamformer_getNormType(hBeam)-1);
    setParameterValue("beamType", beamformer_getBeamType(hBeam)-1);
    setParameterValue("numBeams", beamformer_getNumBeams(hBeam));
    for(int i=0; i<MAX_NUM_OUTPUTS; i++){
        setParameterValue("azim" + juce::String(i), beamformer_getBeamAzi_deg(hBeam, i));
        setParameterValue("elev" + juce::String(i), beamformer_getBeamElev_deg(hBeam, i));
    }
}

void PluginProcessor::setInternalStateUsingParameterValues()
{
    beamformer_setBeamOrder(hBeam, getParameterChoice("inputOrder")+1);
    beamformer_setChOrder(hBeam, getParameterChoice("channelOrder")+1);
    beamformer_setNormType(hBeam, getParameterChoice("normType")+1);
    beamformer_setBeamType(hBeam, getParameterChoice("beamType")+1);
    beamformer_setNumBeams(hBeam, getParameterInt("numBeams"));
    for(int i=0; i<MAX_NUM_OUTPUTS; i++){
        beamformer_setBeamAzi_deg(hBeam, i, getParameterFloat("azim" + juce::String(i)));
        beamformer_setBeamElev_deg(hBeam, i, getParameterFloat("elev" + juce::String(i)));
    }
}

PluginProcessor::PluginProcessor() :
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	beamformer_create(&hBeam);
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();
    refreshWindow = true;
}

PluginProcessor::~PluginProcessor()
{
	beamformer_destroy(&hBeam);
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

	beamformer_init(hBeam, nSampleRate);
    AudioProcessor::setLatencySamples(beamformer_getProcessingDelay());
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
    int frameSize = beamformer_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            beamformer_process(hBeam, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
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
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    xml->setTagName("BEAMFORMERPLUGINSETTINGS");
    xml->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10201
    
    /* Save */
    copyXmlToBinary(*xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("BEAMFORMERPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10201
            for(int i=0; i<beamformer_getMaxNumBeams(); i++){
                if(xmlState->hasAttribute("BeamAziDeg" + String(i)))
                    beamformer_setBeamAzi_deg(hBeam, i, (float)xmlState->getDoubleAttribute("BeamAziDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("BeamElevDeg" + String(i)))
                    beamformer_setBeamElev_deg(hBeam, i, (float)xmlState->getDoubleAttribute("BeamElevDeg" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("nBeams"))
                beamformer_setNumBeams(hBeam, xmlState->getIntAttribute("nBeams", 1));
            
            if(xmlState->hasAttribute("NORM"))
                beamformer_setNormType(hBeam, xmlState->getIntAttribute("NORM", 1));
            if(xmlState->hasAttribute("CHORDER"))
                beamformer_setChOrder(hBeam, xmlState->getIntAttribute("CHORDER", 1));
            if(xmlState->hasAttribute("beamOrder"))
                beamformer_setBeamOrder(hBeam, xmlState->getIntAttribute("beamOrder", 1));
            if(xmlState->hasAttribute("beamType"))
                beamformer_setBeamType(hBeam, xmlState->getIntAttribute("beamType", 1));
            
            setParameterValuesUsingInternalState();
        }
        else if(xmlState->getIntAttribute("VersionCode")>=0x10201){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* Many hosts will also trigger parameterChanged() for all parameters after calling setStateInformation() */
            /* However, some hosts do not. Therefore, it is better to ensure that the internal state is always up-to-date by calling: */
            setInternalStateUsingParameterValues();
        }
        
        beamformer_refreshSettings(hBeam);
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

