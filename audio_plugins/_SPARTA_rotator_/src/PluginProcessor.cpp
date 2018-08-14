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

PluginProcessor::PluginProcessor()
{
	nSampleRate = 48000;
    nHostBlockSize = FRAME_SIZE;
	rotator_create(&hRot);

	ringBufferInputs = new float*[MAX_NUM_CHANNELS];
	for (int i = 0; i < MAX_NUM_CHANNELS; i++)
		ringBufferInputs[i] = new float[FRAME_SIZE];

	ringBufferOutputs = new float*[MAX_NUM_CHANNELS];
	for (int i = 0; i < MAX_NUM_CHANNELS; i++)
		ringBufferOutputs[i] = new float[FRAME_SIZE];

	refreshDefaultGUIParams = true;
}

PluginProcessor::~PluginProcessor()
{
	rotator_destroy(&hRot);

	for (int i = 0; i < MAX_NUM_CHANNELS; ++i) {
		delete[] ringBufferInputs[i];
	}
	delete[] ringBufferInputs;

	for (int i = 0; i < MAX_NUM_CHANNELS; ++i) {
		delete[] ringBufferOutputs[i];
	}
	delete[] ringBufferOutputs;
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
	refreshDefaultGUIParams = true;
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
    return String::empty;
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
	nSampleRate = (int)(sampleRate + 0.5);

	nNumInputs = getNumInputChannels();
    nNumOutputs = getNumOutputChannels();

	setPlayConfigDetails(nNumInputs, nNumOutputs, (double)nSampleRate, nHostBlockSize);
	numChannelsChanged();

	rotator_init(hRot, (float)sampleRate);

	for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
		memset(ringBufferInputs[i], 0, FRAME_SIZE*sizeof(float));
	for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
		memset(ringBufferOutputs[i], 0, FRAME_SIZE * sizeof(float));
	 
	isPlaying = false;
}

void PluginProcessor::releaseResources()
{
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	int nCurrentBlockSize = buffer.getNumSamples();
	float** bufferData = buffer.getArrayOfWritePointers(); 
	float** outputs = new float*[nNumOutputs];
	for (int i = 0; i < nNumOutputs; i++)
		outputs[i] = new float[FRAME_SIZE];

	if (nCurrentBlockSize % FRAME_SIZE == 0) { /* divisible by frame size */
		for (int frame = 0; frame < nCurrentBlockSize / FRAME_SIZE; frame++) {
			for (int ch = 0; ch < nNumInputs; ch++)
				for (int i = 0; i < FRAME_SIZE; i++)
					ringBufferInputs[ch][i] = bufferData[ch][frame*FRAME_SIZE + i];

			/* determine if there is actually audio in the damn buffer */
			playHead = getPlayHead();
			bool PlayHeadAvailable = playHead->getCurrentPosition(currentPosition);
			if (PlayHeadAvailable == true)
				isPlaying = currentPosition.isPlaying;
			else
				isPlaying = false;
            if(!isPlaying) /* for DAWs with no transport */
                isPlaying = buffer.getRMSLevel(0, 0, nCurrentBlockSize)>1e-5f ? true : false;
        
			/* perform processing */
			rotator_process(hRot, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, isPlaying);

			/* replace buffer with new audio */
			buffer.clear(frame*FRAME_SIZE, FRAME_SIZE);
			for (int ch = 0; ch < nNumOutputs; ch++)
				for (int i = 0; i < FRAME_SIZE; i++)
					bufferData[ch][frame*FRAME_SIZE + i] = ringBufferOutputs[ch][i];
		}
	}
	else
		buffer.clear();

	for (int i = 0; i < nNumOutputs; ++i)
		delete[] outputs[i];
	delete[] outputs;
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

