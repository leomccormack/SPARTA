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

PluginProcessor::PluginProcessor() : 
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(MAX_NUM_CHANNELS), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(MAX_NUM_CHANNELS), true))
{
	nSampleRate = 48000;
	rotator_create(&hRot);

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
            rotator_setYaw(hRot, message[0].getFloat32());
        if (message[1].isFloat32())
            rotator_setPitch(hRot, message[1].getFloat32());
        if (message[2].isFloat32())
            rotator_setRoll(hRot, message[2].getFloat32());
        return;
    }
    /* if Quaternion values are sent as an array \quaternion[4] */
    if (message.size() == 4 && message.getAddressPattern().toString().compare("/quaternion")==0) {
        if (message[0].isFloat32())
            rotator_setQuaternionW(hRot, message[0].getFloat32());
        if (message[1].isFloat32())
            rotator_setQuaternionX(hRot, message[1].getFloat32());
        if (message[2].isFloat32())
            rotator_setQuaternionY(hRot, message[2].getFloat32());
        if (message[3].isFloat32())
            rotator_setQuaternionZ(hRot, message[3].getFloat32());
        return;
    }
    /* if values are sent individually: */
    if(message.getAddressPattern().toString().compare("/yaw")==0)
        rotator_setYaw(hRot, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/pitch")==0)
        rotator_setPitch(hRot, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/roll")==0)
        rotator_setRoll(hRot, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/qw")==0)
        rotator_setQuaternionW(hRot, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/qx")==0)
        rotator_setQuaternionX(hRot, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/qy")==0)
        rotator_setQuaternionY(hRot, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/qz")==0)
        rotator_setQuaternionZ(hRot, message[0].getFloat32());
}

void PluginProcessor::setParameter (int index, float newValue)
{
	switch (index) {
        case k_inputOrder:      rotator_setOrder(hRot, (SH_ORDERS)(int)(newValue*(float)(MAX_SH_ORDER-1) + 1.5f)); break;
        case k_channelOrder:    rotator_setChOrder(hRot, (int)(newValue*(float)(NUM_CH_ORDERINGS-1) + 1.5f)); break;
        case k_normType:        rotator_setNormType(hRot, (int)(newValue*(float)(NUM_NORM_TYPES-1) + 1.5f)); break;
        case k_useRollPitchYaw: rotator_setRPYflag(hRot, (int)(newValue + 0.5f)); break;
        case k_yaw:             rotator_setYaw(hRot, (newValue-0.5f)*360.0f ); break;
        case k_pitch:           rotator_setPitch(hRot, (newValue - 0.5f)*180.0f); break;
        case k_roll:            rotator_setRoll(hRot, (newValue - 0.5f)*180.0f); break;
        case k_qw:              rotator_setQuaternionW(hRot, (newValue - 0.5f)*2.0f); break;
        case k_qx:              rotator_setQuaternionX(hRot, (newValue - 0.5f)*2.0f); break;
        case k_qy:              rotator_setQuaternionY(hRot, (newValue - 0.5f)*2.0f); break;
        case k_qz:              rotator_setQuaternionZ(hRot, (newValue - 0.5f)*2.0f); break;
        case k_flipYaw:         rotator_setFlipYaw(hRot, (int)(newValue + 0.5f)); break;
        case k_flipPitch:       rotator_setFlipPitch(hRot, (int)(newValue + 0.5f)); break;
        case k_flipRoll:        rotator_setFlipRoll(hRot, (int)(newValue + 0.5f)); break;
        case k_flipQuaternion:  rotator_setFlipQuaternion(hRot, (int)(newValue + 0.5f)); break;
		default: break;
	}
}

void PluginProcessor::setCurrentProgram (int /*index*/)
{
}

float PluginProcessor::getParameter (int index)
{
    switch (index) {
        case k_inputOrder:      return (float)(rotator_getOrder(hRot)-1)/(float)(MAX_SH_ORDER-1);
        case k_channelOrder:    return (float)(rotator_getChOrder(hRot)-1)/(float)(NUM_CH_ORDERINGS-1);
        case k_normType:        return (float)(rotator_getNormType(hRot)-1)/(float)(NUM_NORM_TYPES-1);
        case k_useRollPitchYaw: return (float)rotator_getRPYflag(hRot);
        case k_yaw:             return (rotator_getYaw(hRot)/360.0f) + 0.5f;
        case k_pitch:           return (rotator_getPitch(hRot)/180.0f) + 0.5f;
        case k_roll:            return (rotator_getRoll(hRot)/180.0f) + 0.5f;
        case k_qw:              return (rotator_getQuaternionW(hRot)/2.0f) + 0.5f;
        case k_qx:              return (rotator_getQuaternionX(hRot)/2.0f) + 0.5f;
        case k_qy:              return (rotator_getQuaternionY(hRot)/2.0f) + 0.5f;
        case k_qz:              return (rotator_getQuaternionZ(hRot)/2.0f) + 0.5f;
        case k_flipYaw:         return (float)rotator_getFlipYaw(hRot);
        case k_flipPitch:       return (float)rotator_getFlipPitch(hRot);
        case k_flipRoll:        return (float)rotator_getFlipRoll(hRot);
        case k_flipQuaternion:  return (float)rotator_getFlipQuaternion(hRot);
		default: return 0.0f;
	}
}

int PluginProcessor::getNumParameters()
{
	return k_NumOfParameters;
}

const String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

const String PluginProcessor::getParameterName (int index)
{
    switch (index){
        case k_inputOrder:      return "order";
        case k_channelOrder:    return "channel_order";
        case k_normType:        return "norm_type";
        case k_useRollPitchYaw: return "use_rpy";
        case k_yaw:             return "yaw";
        case k_pitch:           return "pitch";
        case k_roll:            return "roll";
        case k_qw:              return "quaternion_w";
        case k_qx:              return "quaternion_x";
        case k_qy:              return "quaternion_y";
        case k_qz:              return "quaternion_z";
        case k_flipYaw:         return "flip_yaw";
        case k_flipPitch:       return "flip_pitch";
        case k_flipRoll:        return "flip_roll";
        case k_flipQuaternion:  return "flip_quaternion";
		default: return "NULL";
	}
}

const String PluginProcessor::getParameterText(int index)
{
    switch (index) {
        case k_inputOrder: return String(rotator_getOrder(hRot));
        case k_channelOrder:
            switch(rotator_getChOrder(hRot)){
                case CH_ACN:  return "ACN";
                case CH_FUMA: return "FuMa";
                default: return "NULL";
            }
        case k_normType:
            switch(rotator_getNormType(hRot)){
                case NORM_N3D:  return "N3D";
                case NORM_SN3D: return "SN3D";
                case NORM_FUMA: return "FuMa";
                default: return "NULL";
            }
        case k_useRollPitchYaw: return !rotator_getRPYflag(hRot) ? "YPR" : "RPY";
        case k_yaw:             return String(rotator_getYaw(hRot));
        case k_pitch:           return String(rotator_getPitch(hRot));
        case k_roll:            return String(rotator_getRoll(hRot));
        case k_qw:              return String(rotator_getQuaternionW(hRot));
        case k_qx:              return String(rotator_getQuaternionX(hRot));
        case k_qy:              return String(rotator_getQuaternionY(hRot));
        case k_qz:              return String(rotator_getQuaternionZ(hRot));
        case k_flipYaw:         return !rotator_getFlipYaw(hRot) ? "No-Flip" : "Flip";
        case k_flipPitch:       return !rotator_getFlipPitch(hRot) ? "No-Flip" : "Flip";
        case k_flipRoll:        return !rotator_getFlipRoll(hRot) ? "No-Flip" : "Flip";
        case k_flipQuaternion:  return !rotator_getFlipQuaternion(hRot) ? "No-Flip" : "Flip";
        default: return "NULL";
    }
}

const String PluginProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String PluginProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
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


bool PluginProcessor::isInputChannelStereoPair (int /*index*/) const
{
    return true;
}

bool PluginProcessor::isOutputChannelStereoPair (int /*index*/) const
{
    return true;
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

bool PluginProcessor::silenceInProducesSilenceOut() const
{
    return false;
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

//==============================================================================
bool PluginProcessor::hasEditor() const
{
    return true; 
}

AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (this);
}

//==============================================================================
void PluginProcessor::getStateInformation (MemoryBlock& destData)
{
	/* Create an outer XML element.. */ 
	XmlElement xml("ROTATORAUDIOPLUGINSETTINGS");
 
	xml.setAttribute("YAW", rotator_getYaw(hRot));
	xml.setAttribute("PITCH", rotator_getPitch(hRot));
	xml.setAttribute("ROLL", rotator_getRoll(hRot));
    
    xml.setAttribute("FLIP_YAW", rotator_getFlipYaw(hRot));
    xml.setAttribute("FLIP_PITCH", rotator_getFlipPitch(hRot));
    xml.setAttribute("FLIP_ROLL", rotator_getFlipRoll(hRot));
    xml.setAttribute("RPY_FLAG", rotator_getRPYflag(hRot));
    
    xml.setAttribute("OSC_PORT", osc_port_ID);
    
    xml.setAttribute("NORM", rotator_getNormType(hRot));
    xml.setAttribute("CHORDER", rotator_getChOrder(hRot));
    
    xml.setAttribute("ORDER", rotator_getOrder(hRot));
    
	copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	/* This getXmlFromBinary() function retrieves XML from the binary blob */
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr) {
		/* make sure that it's actually the correct XML object */
		if (xmlState->hasTagName("ROTATORAUDIOPLUGINSETTINGS")) {
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
        }
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

