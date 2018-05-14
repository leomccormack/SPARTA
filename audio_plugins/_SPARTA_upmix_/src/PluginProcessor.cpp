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
    ringBufferInputs = new float*[MAX_NUM_CHANNELS];
    for (int i = 0; i < MAX_NUM_CHANNELS; i++)
        ringBufferInputs[i] = new float[FRAME_SIZE];
    
    ringBufferOutputs = new float*[MAX_NUM_CHANNELS];
    for (int i = 0; i < MAX_NUM_CHANNELS; i++)
        ringBufferOutputs[i] = new float[FRAME_SIZE];
    
	upmix_create(&hUpmx);
}

PluginProcessor::~PluginProcessor()
{
	upmix_destroy(&hUpmx);
    
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
    return 0;
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
    
    nNumInputs = getTotalNumInputChannels();
    nNumOutputs = getTotalNumOutputChannels();
 
	setPlayConfigDetails(nNumInputs, nNumOutputs, (double)nSampleRate, nHostBlockSize);
	numChannelsChanged();
    isPlaying = false;

	upmix_init(hUpmx, sampleRate);
    
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i) {
        memset(ringBufferInputs[i], 0, FRAME_SIZE*sizeof(float));
    }
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i) {
        memset(ringBufferOutputs[i], 0, FRAME_SIZE * sizeof(float));
    }
    wIdx = 1; rIdx = 1; /* read/write indices for ring buffers */
}

void PluginProcessor::releaseResources()
{
    isPlaying = false;
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    int nCurrentBlockSize = buffer.getNumSamples();
    float** bufferData = buffer.getArrayOfWritePointers();
    float** outputs = new float*[nNumOutputs];
    for (int i = 0; i < nNumOutputs; i++) {
        outputs[i] = new float[FRAME_SIZE];
    }
    
#ifdef ENABLE_IS_PLAYING_CHECK
    playHead = getPlayHead();
    bool PlayHeadAvailable = playHead->getCurrentPosition(currentPosition);
    if (PlayHeadAvailable == true)
        isPlaying = currentPosition.isPlaying;
    else
        isPlaying = false;
    
#endif
    switch (nCurrentBlockSize) {
        case (FRAME_SIZE * 8):
            for (int frame = 0; frame < 8; frame++) {
                for (int ch = 0; ch < nNumInputs; ch++)
                    for (int i = 0; i < FRAME_SIZE; i++)
                        ringBufferInputs[ch][i] = bufferData[ch][frame*FRAME_SIZE + i];
                upmix_process(hUpmx, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, (int)isPlaying);
                buffer.clear(frame*FRAME_SIZE, FRAME_SIZE);
                for (int ch = 0; ch < nNumOutputs; ch++)
                    for (int i = 0; i < FRAME_SIZE; i++)
                        bufferData[ch][frame*FRAME_SIZE + i] = ringBufferOutputs[ch][i];
            }
            break;
            
        case (FRAME_SIZE * 4):
            for (int frame = 0; frame < 4; frame++) {
                for (int ch = 0; ch < nNumInputs; ch++)
                    for (int i = 0; i < FRAME_SIZE; i++)
                        ringBufferInputs[ch][i] = bufferData[ch][frame*FRAME_SIZE + i];
                upmix_process(hUpmx, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, (int)isPlaying);
                buffer.clear(frame*FRAME_SIZE, FRAME_SIZE);
                for (int ch = 0; ch < nNumOutputs; ch++)
                    for (int i = 0; i < FRAME_SIZE; i++)
                        bufferData[ch][frame*FRAME_SIZE + i] = ringBufferOutputs[ch][i];
            }
            break;
            
        case (FRAME_SIZE*2):
            for(int frame = 0; frame < 2; frame++){
                for (int ch = 0; ch < nNumInputs; ch++)
                    for (int i = 0; i < FRAME_SIZE; i++)
                        ringBufferInputs[ch][i] = bufferData[ch][frame*FRAME_SIZE + i];
                upmix_process(hUpmx, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, (int)isPlaying);
                buffer.clear(frame*FRAME_SIZE, FRAME_SIZE);
                for (int ch = 0; ch < nNumOutputs; ch++)
                    for (int i = 0; i < FRAME_SIZE; i++)
                        bufferData[ch][frame*FRAME_SIZE + i] = ringBufferOutputs[ch][i];
            }
            break;

        case FRAME_SIZE:
            upmix_process(hUpmx, bufferData, outputs, nNumInputs, nNumOutputs, FRAME_SIZE, (int)isPlaying);
            buffer.clear();
            for (int ch = 0; ch < nNumOutputs; ch++) {
                for (int i = 0; i < FRAME_SIZE; i++) {
                    bufferData[ch][i] = outputs[ch][i];
                }
            }
            break;

        default:
            buffer.clear();
            break;
    }
#ifdef ENABLE_IS_PLAYING_CHECK
#endif
    
    if (nHostBlockSize == (FRAME_SIZE/2)) {
        wIdx++; if (wIdx > 1) { wIdx = 0; }
        rIdx++; if (rIdx > 1) { rIdx = 0; }
    }
    
    for (int i = 0; i < nNumOutputs; ++i) {
        delete[] outputs[i];
    }
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
    XmlElement xml("UPMIXPLUGINSETTINGS");
    xml.setAttribute("covAvg", upmix_getCovAvg(hUpmx));
    xml.setAttribute("scaleDoAwidth", upmix_getScaleDoAwidth(hUpmx));
    xml.setAttribute("paramAvgCoeff", upmix_getParamAvgCoeff(hUpmx));
    xml.setAttribute("pValueCoeff", upmix_getPValueCoeff(hUpmx));
    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr) {
        if (xmlState->hasTagName("UPMIXPLUGINSETTINGS")) {
            if(xmlState->hasAttribute("covAvg"))
                upmix_setCovAvg(hUpmx, (float)xmlState->getDoubleAttribute("covAvg", 0.5f));
            if(xmlState->hasAttribute("scaleDoAwidth"))
                upmix_setScaleDoAwidth(hUpmx, (float)xmlState->getDoubleAttribute("scaleDoAwidth", 0.5f));
            if(xmlState->hasAttribute("paramAvgCoeff"))
                upmix_setParamAvgCoeff(hUpmx, (float)xmlState->getDoubleAttribute("paramAvgCoeff", 0.5f));
            if(xmlState->hasAttribute("pValueCoeff"))
                upmix_setPValueCoeff(hUpmx, (float)xmlState->getDoubleAttribute("pValueCoeff", 0.5f));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

