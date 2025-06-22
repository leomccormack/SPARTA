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
                                                                  juce::StringArray{"1st order","2nd order","3rd order","4th order","5th order","6th order","7th order","8th order","9th order","10th order"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("channelOrder", "ChannelOrder", juce::StringArray{"ACN", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("normType", "NormType", juce::StringArray{"N3D", "SN3D", "FuMa"}, 1));
    params.push_back(std::make_unique<juce::AudioParameterBool>("useRollPitchYaw", "UseRollPitchYaw", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("yaw", "Yaw", juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("pitch", "Pitch", juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("roll", "Roll", juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("qw", "Qw", juce::NormalisableRange<float>(-1.0f, 1.0f, 0.001f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("qx", "Qx", juce::NormalisableRange<float>(-1.0f, 1.0f, 0.001f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("qy", "Qy", juce::NormalisableRange<float>(-1.0f, 1.0f, 0.001f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("qz", "Qz", juce::NormalisableRange<float>(-1.0f, 1.0f, 0.001f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("flipYaw", "FlipYaw", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("flipPitch", "FlipPitch", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("flipRoll", "FlipRoll", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("flipQuaternion", "FlipQuaternion", false));
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "inputOrder"){
        rotator_setOrder(hRot, static_cast<SH_ORDERS>(newValue+1.001f));
    }
    else if (parameterID == "channelOrder"){
        rotator_setChOrder(hRot, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "normType"){
        rotator_setNormType(hRot, static_cast<int>(newValue+1.001f));
    }
    else if(parameterID == "useRollPitchYaw"){
        rotator_setRPYflag(hRot, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "yaw"){
        rotator_setYaw(hRot, newValue);
    }
    else if(parameterID == "pitch"){
        rotator_setPitch(hRot, newValue);
    }
    else if(parameterID == "roll"){
        rotator_setRoll(hRot, newValue);
    }
    else if(parameterID == "qw"){
        rotator_setQuaternionW(hRot, newValue);
    }
    else if(parameterID == "qx"){
        rotator_setQuaternionX(hRot, newValue);
    }
    else if(parameterID == "qy"){
        rotator_setQuaternionY(hRot, newValue);
    }
    else if(parameterID == "qz"){
        rotator_setQuaternionZ(hRot, newValue);
    }
    else if(parameterID == "flipYaw"){
        rotator_setFlipYaw(hRot, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "flipPitch"){
        rotator_setFlipPitch(hRot, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "flipRoll"){
        rotator_setFlipRoll(hRot, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "flipQuaternion"){
        rotator_setFlipQuaternion(hRot, static_cast<int>(newValue+0.5f));
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("inputOrder", rotator_getOrder(hRot)-1);
    setParameterValue("channelOrder", rotator_getChOrder(hRot)-1);
    setParameterValue("normType", rotator_getNormType(hRot)-1);
    setParameterValue("useRollPitchYaw", rotator_getRPYflag(hRot));
    setParameterValue("yaw", rotator_getYaw(hRot));
    setParameterValue("pitch", rotator_getPitch(hRot));
    setParameterValue("roll", rotator_getRoll(hRot));
    setParameterValue("qw", rotator_getQuaternionW(hRot));
    setParameterValue("qx", rotator_getQuaternionX(hRot));
    setParameterValue("qy", rotator_getQuaternionY(hRot));
    setParameterValue("qz", rotator_getQuaternionZ(hRot));
    setParameterValue("flipYaw", rotator_getFlipYaw(hRot));
    setParameterValue("flipPitch", rotator_getFlipPitch(hRot));
    setParameterValue("flipRoll", rotator_getFlipRoll(hRot));
    setParameterValue("flipQuaternion", rotator_getFlipQuaternion(hRot));
}

PluginProcessor::PluginProcessor() :
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	nSampleRate = 48000;
	rotator_create(&hRot);
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();

    /* specify here on which UDP port number to receive incoming OSC messages */
    osc_port_ID = DEFAULT_OSC_PORT;
    osc_connected = osc.connect(osc_port_ID);
    /* tell the component to listen for OSC messages */
    osc.addListener(this);
}

PluginProcessor::~PluginProcessor()
{
    osc.disconnect();
    osc.removeListener(this);
    
	rotator_destroy(&hRot);
}

void PluginProcessor::oscMessageReceived(const OSCMessage& message)
{
    /* if Euler rotation angles are sent as an array \ypr[3] */
    if (message.size() == 3 && message.getAddressPattern().toString().compare("/ypr")==0) {
        if (message[0].isFloat32())
            setParameterValue("yaw", message[0].getFloat32());
        if (message[1].isFloat32())
            setParameterValue("pitch", message[1].getFloat32());
        if (message[2].isFloat32())
            setParameterValue("roll", message[2].getFloat32());
        return;
    }
    /* if Quaternion values are sent as an array \quaternion[4] */
    if (message.size() == 4 && message.getAddressPattern().toString().compare("/quaternion")==0) {
        if (message[0].isFloat32())
            setParameterValue("qw", message[0].getFloat32());
        if (message[1].isFloat32())
            setParameterValue("qx", message[1].getFloat32());
        if (message[2].isFloat32())
            setParameterValue("qy", message[2].getFloat32());
        if (message[3].isFloat32())
            setParameterValue("qz", message[3].getFloat32());
        return;
    }
    /* if values are sent individually: */
    if(message.getAddressPattern().toString().compare("/yaw")==0)
        setParameterValue("yaw", message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/pitch")==0)
        setParameterValue("pitch", message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/roll")==0)
        setParameterValue("roll", message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/qw")==0)
        setParameterValue("qw", message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/qx")==0)
        setParameterValue("qx", message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/qy")==0)
        setParameterValue("qy", message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/qz")==0)
        setParameterValue("qz", message[0].getFloat32());
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
    return 1;
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

	rotator_init(hRot, (float)sampleRate);
}

void PluginProcessor::releaseResources()
{
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels(), 256);
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels(), 256);
    float* const* bufferData = buffer.getArrayOfWritePointers();
    float* pFrameData[256];
    int frameSize = rotator_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            rotator_process(hRot, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
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
    xml->setTagName("ROTATORAUDIOPLUGINSETTINGS");
    xml->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10301
    
    /* Other */
    xml->setAttribute("OSC_PORT", osc_port_ID);
    
    /* Save */
    copyXmlToBinary(*xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("ROTATORAUDIOPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10301
            if(xmlState->hasAttribute("YAW"))
                rotator_setYaw(hRot, (float)xmlState->getDoubleAttribute("YAW", 0.0f));
            if(xmlState->hasAttribute("PITCH"))
                rotator_setPitch(hRot, (float)xmlState->getDoubleAttribute("PITCH", 0.0f));
            if(xmlState->hasAttribute("ROLL"))
                rotator_setRoll(hRot, (float)xmlState->getDoubleAttribute("ROLL", 0.0f));
            
            if(xmlState->hasAttribute("FLIP_YAW"))
                rotator_setFlipYaw(hRot, xmlState->getIntAttribute("FLIP_YAW", 0));
            if(xmlState->hasAttribute("FLIP_PITCH"))
                rotator_setFlipPitch(hRot, xmlState->getIntAttribute("FLIP_PITCH", 0));
            if(xmlState->hasAttribute("FLIP_ROLL"))
                rotator_setFlipRoll(hRot, xmlState->getIntAttribute("FLIP_ROLL", 0));
            if(xmlState->hasAttribute("RPY_FLAG"))
                rotator_setRPYflag(hRot, xmlState->getIntAttribute("RPY_FLAG", 0));
            
            if(xmlState->hasAttribute("OSC_PORT")){
                osc_port_ID = xmlState->getIntAttribute("OSC_PORT", DEFAULT_OSC_PORT);
                osc.connect(osc_port_ID);
            }
            
            if(xmlState->hasAttribute("NORM"))
                rotator_setNormType(hRot, xmlState->getIntAttribute("NORM", 1));
            if(xmlState->hasAttribute("CHORDER"))
                rotator_setChOrder(hRot, xmlState->getIntAttribute("CHORDER", 1));
            
            if(xmlState->hasAttribute("ORDER"))
                rotator_setOrder(hRot, xmlState->getIntAttribute("ORDER", 1));
            
            setParameterValuesUsingInternalState();
        }
        else if(xmlState->getIntAttribute("VersionCode")>=0x10301){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* other */
            if(xmlState->hasAttribute("OSC_PORT")){
                osc_port_ID = xmlState->getIntAttribute("OSC_PORT", DEFAULT_OSC_PORT);
                osc.connect(osc_port_ID);
            }
        }
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

