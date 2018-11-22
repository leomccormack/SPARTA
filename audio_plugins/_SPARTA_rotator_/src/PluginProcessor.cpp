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
		.withInput("Input", AudioChannelSet::discreteChannels(64), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(64), true))
{
	nSampleRate = 48000;
    nHostBlockSize = FRAME_SIZE;
	rotator_create(&hRot);

    bufferInputs = new float*[MAX_NUM_CHANNELS];
    for (int i = 0; i < MAX_NUM_CHANNELS; i++)
        bufferInputs[i] = new float[FRAME_SIZE];
    
    bufferOutputs = new float*[MAX_NUM_CHANNELS];
    for (int i = 0; i < MAX_NUM_CHANNELS; i++)
        bufferOutputs[i] = new float[FRAME_SIZE];

    /* specify here on which UDP port number to receive incoming OSC messages */
    osc_port_ID = DEFAULT_OSC_PORT;
    osc.connect(osc_port_ID);
    /* tell the component to listen for OSC messages */
    osc.addListener(this);
}

PluginProcessor::~PluginProcessor()
{
    osc.disconnect();
    osc.removeListener(this);
    
	rotator_destroy(&hRot);

    for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
        delete[] bufferInputs[i];
    delete[] bufferInputs;
    
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
        delete[] bufferOutputs[i];
    delete[] bufferOutputs;
}

void PluginProcessor::oscMessageReceived(const OSCMessage& message)
{
    /* if rotation angles are sent as an array \ypr[3] */
    if (message.size() == 3 && message.getAddressPattern().toString().compare("ypr")) {
        if (message[0].isFloat32())
            rotator_setYaw(hRot, message[0].getFloat32());
        if (message[1].isFloat32())
            rotator_setPitch(hRot, message[1].getFloat32());
        if (message[2].isFloat32())
            rotator_setRoll(hRot, message[2].getFloat32());
        return;
    }
    
    /* if rotation angles are sent individually: */
    if(message.getAddressPattern().toString().compare("yaw"))
        rotator_setYaw(hRot, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("pitch"))
        rotator_setPitch(hRot, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("roll"))
        rotator_setRoll(hRot, message[0].getFloat32());
}

void PluginProcessor::setParameter (int index, float newValue)
{
	switch (index)
	{
        case k_yaw:
            rotator_setYaw(hRot, (newValue-0.5f)*360.0f );
            break;
        case k_pitch:
            rotator_setPitch(hRot, (newValue - 0.5f)*180.0f);
            break;
        case k_roll:
            rotator_setRoll(hRot, (newValue - 0.5f)*180.0f);
            break;
        case k_flipYaw:
    		rotator_setFlipYaw(hRot, (int)(newValue + 0.5f));
            break;
        case k_flipPitch:
            rotator_setFlipPitch(hRot, (int)(newValue + 0.5f));
            break;
        case k_flipRoll:
            rotator_setFlipRoll(hRot, (int)(newValue + 0.5f));
            break;
            
		default: break;
	}
}

void PluginProcessor::setCurrentProgram (int index)
{
}

float PluginProcessor::getParameter (int index)
{
    switch (index)
	{
        case k_yaw:
            return (rotator_getYaw(hRot)/360.0f) + 0.5f;
        case k_pitch:
            return (rotator_getPitch(hRot)/180.0f) + 0.5f;
        case k_roll:
            return (rotator_getRoll(hRot)/180.0f) + 0.5f;
        case k_flipYaw:
            return (float)rotator_getFlipYaw(hRot);
        case k_flipPitch:
            return (float)rotator_getFlipPitch(hRot);
        case k_flipRoll:
            return (float)rotator_getFlipRoll(hRot);
            
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
    switch (index)
	{
        case k_yaw:
            return "yaw";
        case k_pitch:
            return "pitch";
        case k_roll:
            return "roll";
        case k_flipYaw:
            return "flip_yaw";
        case k_flipPitch:
            return "flip_pitch";
        case k_flipRoll:
            return "flip_roll";
		default: return "NULL";
	}
}

const String PluginProcessor::getParameterText(int index)
{
	return String(getParameter(index), 1);    
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

const String PluginProcessor::getProgramName (int index)
{
    return String();
}


bool PluginProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool PluginProcessor::isOutputChannelStereoPair (int index) const
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

void PluginProcessor::changeProgramName (int index, const String& newName)
{
}

void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    nHostBlockSize = samplesPerBlock;
    nNumInputs =  getTotalNumInputChannels();
    nNumOutputs = getTotalNumOutputChannels();
    nSampleRate = (int)(sampleRate + 0.5);
    isPlaying = false;

	rotator_init(hRot, (float)sampleRate);
}

void PluginProcessor::releaseResources()
{
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels());
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels());
    float** bufferData = buffer.getArrayOfWritePointers();

	if (nCurrentBlockSize % FRAME_SIZE == 0) { /* divisible by frame size */
		for (int frame = 0; frame < nCurrentBlockSize / FRAME_SIZE; frame++) {
			for (int ch = 0; ch < nNumInputs; ch++)
				for (int i = 0; i < FRAME_SIZE; i++)
					bufferInputs[ch][i] = bufferData[ch][frame*FRAME_SIZE + i];

			/* determine if there is actually audio in the damn buffer */
			isPlaying = buffer.getRMSLevel(0, 0, nCurrentBlockSize)>1e-5f ? true : false;
        
			/* perform processing */
			rotator_process(hRot, bufferInputs, bufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, isPlaying);

			/* replace buffer with new audio */
			buffer.clear(frame*FRAME_SIZE, FRAME_SIZE);
			for (int ch = 0; ch < nNumOutputs; ch++)
				for (int i = 0; i < FRAME_SIZE; i++)
					bufferData[ch][frame*FRAME_SIZE + i] = bufferOutputs[ch][i];
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
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

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

