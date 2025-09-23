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
    params.push_back(std::make_unique<juce::AudioParameterChoice>("decMethod", "DecMethod",
                                                                  juce::StringArray{"Least-Squares (LS)","LS with Ambi-Diff-EQ","Spatial Resampling (SPR)","Time-alignment (TA)","Magnitude-LS"}, 4,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterBool>("enableTruncationEQ", "EnableTruncationEQ", false,
                                                                AudioParameterBoolAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("hrirPreproc", "HRIRPreproc",
                                                                  juce::StringArray{"Off","Diffuse-field EQ","Phase Simplification","EQ & Phase"}, 1,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterBool>("enableDiffuseMatching", "EnableDiffuseMatching", false,
                                                                AudioParameterBoolAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterBool>("enableMaxRE", "EnableMaxRE", false, AudioParameterBoolAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterBool>("enableRotation", "EnableRotation", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("useRollPitchYaw", "UseRollPitchYaw", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("yaw", "Yaw", juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f,
                                                                 AudioParameterFloatAttributes().withLabel(juce::String::fromUTF8(u8"\u00B0"))));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("pitch", "Pitch", juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f,
                                                                 AudioParameterFloatAttributes().withLabel(juce::String::fromUTF8(u8"\u00B0"))));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("roll", "Roll", juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f,
                                                                 AudioParameterFloatAttributes().withLabel(juce::String::fromUTF8(u8"\u00B0"))));
    params.push_back(std::make_unique<juce::AudioParameterBool>("flipYaw", "FlipYaw", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("flipPitch", "FlipPitch", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("flipRoll", "FlipRoll", false));
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "inputOrder"){
        ambi_bin_setInputOrderPreset(hAmbi, static_cast<SH_ORDERS>(newValue+1.001f));
    }
    else if (parameterID == "channelOrder"){
        ambi_bin_setChOrder(hAmbi, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "normType"){
        ambi_bin_setNormType(hAmbi, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "decMethod"){
        ambi_bin_setDecodingMethod(hAmbi, static_cast<AMBI_BIN_DECODING_METHODS>(newValue+1.001f));
    }
    else if (parameterID == "enableTruncationEQ"){
        ambi_bin_setEnableTruncationEQ(hAmbi, static_cast<int>(newValue+0.5f));
    }
    else if (parameterID == "hrirPreproc"){
        ambi_bin_setHRIRsPreProc(hAmbi, static_cast<AMBI_BIN_PREPROC>(newValue+1.001f));
    }
    else if (parameterID == "enableDiffuseMatching"){
        ambi_bin_setEnableDiffuseMatching(hAmbi, static_cast<int>(newValue+0.5f));
    }
    else if (parameterID == "enableMaxRE"){
        ambi_bin_setEnableMaxRE(hAmbi, static_cast<int>(newValue+0.5f));
    }
    else if (parameterID == "enableRotation"){
        ambi_bin_setEnableRotation(hAmbi, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "useRollPitchYaw"){
        ambi_bin_setRPYflag(hAmbi, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "yaw"){
        ambi_bin_setYaw(hAmbi, newValue);
    }
    else if(parameterID == "pitch"){
        ambi_bin_setPitch(hAmbi, newValue);
    }
    else if(parameterID == "roll"){
        ambi_bin_setRoll(hAmbi, newValue);
    }
    else if(parameterID == "flipYaw"){
        ambi_bin_setFlipYaw(hAmbi, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "flipPitch"){
        ambi_bin_setFlipPitch(hAmbi, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "flipRoll"){
        ambi_bin_setFlipRoll(hAmbi, static_cast<int>(newValue+0.5f));
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("inputOrder", ambi_bin_getInputOrderPreset(hAmbi)-1);
    setParameterValue("channelOrder", ambi_bin_getChOrder(hAmbi)-1);
    setParameterValue("normType", ambi_bin_getNormType(hAmbi)-1);
    setParameterValue("decMethod", ambi_bin_getDecodingMethod(hAmbi)-1);
    setParameterValue("enableTruncationEQ", ambi_bin_getEnableTruncationEQ(hAmbi));
    setParameterValue("hrirPreproc", ambi_bin_getHRIRsPreProc(hAmbi)-1);
    setParameterValue("enableDiffuseMatching", ambi_bin_getEnableDiffuseMatching(hAmbi));
    setParameterValue("enableMaxRE", ambi_bin_getEnableMaxRE(hAmbi));
    setParameterValue("enableRotation", ambi_bin_getEnableRotation(hAmbi));
    setParameterValue("useRollPitchYaw", ambi_bin_getRPYflag(hAmbi));
    setParameterValue("yaw", ambi_bin_getYaw(hAmbi));
    setParameterValue("pitch", ambi_bin_getPitch(hAmbi));
    setParameterValue("roll", ambi_bin_getRoll(hAmbi));
    setParameterValue("flipYaw", ambi_bin_getFlipYaw(hAmbi));
    setParameterValue("flipPitch", ambi_bin_getFlipPitch(hAmbi));
    setParameterValue("flipRoll", ambi_bin_getFlipRoll(hAmbi));
}

void PluginProcessor::setInternalStateUsingParameterValues()
{
    ambi_bin_setInputOrderPreset(hAmbi, static_cast<SH_ORDERS>(getParameterChoice("inputOrder")+1));
    ambi_bin_setChOrder(hAmbi, getParameterChoice("channelOrder")+1);
    ambi_bin_setNormType(hAmbi, getParameterChoice("normType")+1);
    ambi_bin_setDecodingMethod(hAmbi, static_cast<AMBI_BIN_DECODING_METHODS>(getParameterChoice("decMethod")+1));
    ambi_bin_setEnableTruncationEQ(hAmbi, getParameterBool("enableTruncationEQ"));
    ambi_bin_setHRIRsPreProc(hAmbi, static_cast<AMBI_BIN_PREPROC>(getParameterChoice("hrirPreproc")+1));
    ambi_bin_setEnableDiffuseMatching(hAmbi, getParameterBool("enableDiffuseMatching"));
    ambi_bin_setEnableMaxRE(hAmbi, getParameterBool("enableMaxRE"));
    ambi_bin_setEnableRotation(hAmbi, getParameterBool("enableRotation"));
    ambi_bin_setRPYflag(hAmbi, getParameterBool("useRollPitchYaw"));
    ambi_bin_setYaw(hAmbi, getParameterFloat("yaw"));
    ambi_bin_setPitch(hAmbi, getParameterFloat("pitch"));
    ambi_bin_setRoll(hAmbi, getParameterFloat("roll"));
    ambi_bin_setFlipYaw(hAmbi, getParameterBool("flipYaw"));
    ambi_bin_setFlipPitch(hAmbi, getParameterBool("flipPitch"));
    ambi_bin_setFlipRoll(hAmbi, getParameterBool("flipRoll"));
}

PluginProcessor::PluginProcessor() :
    AudioProcessor(BusesProperties()
        .withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
        .withOutput("Output", AudioChannelSet::discreteChannels(2), true)),
    ParameterManager(*this, createParameterLayout())
{
	ambi_bin_create(&hAmbi);
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();
  
    /* specify here on which UDP port number to receive incoming OSC messages */
    osc_port_ID = DEFAULT_OSC_PORT;
    osc_connected = osc.connect(osc_port_ID);
    /* tell the component to listen for OSC messages */
    osc.addListener(this);
    
    startTimer(80);
}

PluginProcessor::~PluginProcessor()
{
    osc.disconnect();
    osc.removeListener(this);
        
	ambi_bin_destroy(&hAmbi);
}

void PluginProcessor::oscMessageReceived(const OSCMessage& message)
{
    /* if rotation angles are sent as an array \ypr[3] */
    if (message.size() == 3 && message.getAddressPattern().toString().compare("/ypr")==0) {
        if (message[0].isFloat32()){
            setParameterValue("yaw", message[0].getFloat32());
        }
        if (message[1].isFloat32()){
            setParameterValue("pitch", message[1].getFloat32());
        }
        if (message[2].isFloat32()){
            setParameterValue("roll", message[2].getFloat32());
        }
        return;
    }
    
    /* if rotation angles are sent individually: */
    if(message.getAddressPattern().toString().compare("/yaw")==0){
        setParameterValue("yaw", message[0].getFloat32());
    }
    else if(message.getAddressPattern().toString().compare("/pitch")==0){
        setParameterValue("pitch", message[0].getFloat32());
    }
    else if(message.getAddressPattern().toString().compare("/roll")==0){
        setParameterValue("roll", message[0].getFloat32());
    }
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
    nHostBlockSize.store(samplesPerBlock);
    nNumInputs.store(jmin(getTotalNumInputChannels(), 256));
    nNumOutputs.store(jmin(getTotalNumOutputChannels(), 256));
    nSampleRate = (int)(sampleRate + 0.5);

	ambi_bin_init(hAmbi, nSampleRate);
    AudioProcessor::setLatencySamples(ambi_bin_getProcessingDelay());
}

void PluginProcessor::releaseResources()
{
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    ScopedNoDenormals noDenormals;

    /* Apply processing using the current internal state */
    int nCurrentBlockSize = buffer.getNumSamples();
    nHostBlockSize.store(buffer.getNumSamples());
    nNumInputs.store(jmin(getTotalNumInputChannels(), buffer.getNumChannels(), 256));
    nNumOutputs.store(jmin(getTotalNumOutputChannels(), buffer.getNumChannels(), 256));
    float* const* bufferData = buffer.getArrayOfWritePointers();
    float* pFrameData[256];
    int frameSize = ambi_bin_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            ambi_bin_process(hAmbi, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
        }
    }
    else {
        buffer.clear();
    }
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
    xml->setTagName("AMBIBINPLUGINSETTINGS");
    xml->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10601
    
    /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
    xml->setAttribute("UseDefaultHRIRset", ambi_bin_getUseDefaultHRIRsflag(hAmbi));
    if(!ambi_bin_getUseDefaultHRIRsflag(hAmbi))
        xml->setAttribute("SofaFilePath", String(ambi_bin_getSofaFilePath(hAmbi)));

    /* Other */
    xml->setAttribute("OSC_PORT", osc_port_ID);
    
    /* Save */
    copyXmlToBinary(*xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("AMBIBINPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10601
            if(xmlState->hasAttribute("order"))
                ambi_bin_setInputOrderPreset(hAmbi, (SH_ORDERS)xmlState->getIntAttribute("order", 2));
            if(xmlState->hasAttribute("UseDefaultHRIRset"))
                ambi_bin_setUseDefaultHRIRsflag(hAmbi, xmlState->getIntAttribute("UseDefaultHRIRset", 1));
            if(xmlState->hasAttribute("Norm"))
                ambi_bin_setNormType(hAmbi, xmlState->getIntAttribute("Norm", 1));
            if(xmlState->hasAttribute("ChOrder"))
                ambi_bin_setChOrder(hAmbi, xmlState->getIntAttribute("ChOrder", 1));
            if(xmlState->hasAttribute("maxrE"))
                ambi_bin_setEnableMaxRE(hAmbi,xmlState->getIntAttribute("maxrE", 1));
            if(xmlState->hasAttribute("diffMatch"))
                ambi_bin_setEnableDiffuseMatching(hAmbi,xmlState->getIntAttribute("diffMatch", 1));
            if(xmlState->hasAttribute("truncationEQ"))
                ambi_bin_setEnableTruncationEQ(hAmbi,xmlState->getIntAttribute("truncationEQ", 1));
            if(xmlState->hasAttribute("method"))
                ambi_bin_setDecodingMethod(hAmbi, (AMBI_BIN_DECODING_METHODS)xmlState->getIntAttribute("method", 1));
            if(xmlState->hasAttribute("preproc"))
                ambi_bin_setHRIRsPreProc(hAmbi, (AMBI_BIN_PREPROC)xmlState->getIntAttribute("preproc", 1));
            
            if(xmlState->hasAttribute("ENABLEROT"))
                ambi_bin_setEnableRotation(hAmbi, xmlState->getIntAttribute("ENABLEROT", 0));
            if(xmlState->hasAttribute("YAW"))
                ambi_bin_setYaw(hAmbi, (float)xmlState->getDoubleAttribute("YAW", 0.0f));
            if(xmlState->hasAttribute("PITCH"))
                ambi_bin_setPitch(hAmbi, (float)xmlState->getDoubleAttribute("PITCH", 0.0f));
            if(xmlState->hasAttribute("ROLL"))
                ambi_bin_setRoll(hAmbi, (float)xmlState->getDoubleAttribute("ROLL", 0.0f));
            if(xmlState->hasAttribute("FLIP_YAW"))
                ambi_bin_setFlipYaw(hAmbi, xmlState->getIntAttribute("FLIP_YAW", 0));
            if(xmlState->hasAttribute("FLIP_PITCH"))
                ambi_bin_setFlipPitch(hAmbi, xmlState->getIntAttribute("FLIP_PITCH", 0));
            if(xmlState->hasAttribute("FLIP_ROLL"))
                ambi_bin_setFlipRoll(hAmbi, xmlState->getIntAttribute("FLIP_ROLL", 0));
            if(xmlState->hasAttribute("RPY_FLAG"))
                ambi_bin_setRPYflag(hAmbi, xmlState->getIntAttribute("RPY_FLAG", 0));
            
            if(xmlState->hasAttribute("OSC_PORT")){
                osc_port_ID = xmlState->getIntAttribute("OSC_PORT", DEFAULT_OSC_PORT);
                osc.connect(osc_port_ID);
            }
            
            if(xmlState->hasAttribute("SofaFilePath")){
                String directory = xmlState->getStringAttribute("SofaFilePath", "no_file");
                const char* new_cstring = (const char*)directory.toUTF8();
                ambi_bin_setSofaFilePath(hAmbi, new_cstring);
            }
            
            setParameterValuesUsingInternalState();
        }
        else if(xmlState->getIntAttribute("VersionCode")>=0x10601){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
            if(xmlState->hasAttribute("UseDefaultHRIRset"))
                ambi_bin_setUseDefaultHRIRsflag(hAmbi, xmlState->getIntAttribute("UseDefaultHRIRset", 1));
            if(xmlState->hasAttribute("SofaFilePath")){
                String directory = xmlState->getStringAttribute("SofaFilePath", "no_file");
                const char* new_cstring = (const char*)directory.toUTF8();
                ambi_bin_setSofaFilePath(hAmbi, new_cstring);
            }
            
            /* Other */
            if(xmlState->hasAttribute("OSC_PORT")){
                osc_port_ID = xmlState->getIntAttribute("OSC_PORT", DEFAULT_OSC_PORT);
                osc.connect(osc_port_ID);
            }
            
            /* Many hosts will also trigger parameterChanged() for all parameters after calling setStateInformation() */
            /* However, some hosts do not. Therefore, it is better to ensure that the internal state is always up-to-date by calling: */
            setInternalStateUsingParameterValues();
        }
        
        ambi_bin_refreshParams(hAmbi);
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

