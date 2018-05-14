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
    
	mcEQlib_create(&hMEQ);
}

PluginProcessor::~PluginProcessor()
{
	mcEQlib_destroy(&hMEQ);
    
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

	mcEQlib_init(hMEQ, sampleRate);
    
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
                mcEQlib_process(hMEQ, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, (int)isPlaying);
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
                mcEQlib_process(hMEQ, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, (int)isPlaying);
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
                mcEQlib_process(hMEQ, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, (int)isPlaying);
                buffer.clear(frame*FRAME_SIZE, FRAME_SIZE);
                for (int ch = 0; ch < nNumOutputs; ch++)
                    for (int i = 0; i < FRAME_SIZE; i++)
                        bufferData[ch][frame*FRAME_SIZE + i] = ringBufferOutputs[ch][i];
            }
            break;

        case FRAME_SIZE:
            mcEQlib_process(hMEQ, bufferData, outputs, nNumInputs, nNumOutputs, FRAME_SIZE, (int)isPlaying);
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
    XmlElement xml("MCEQPLUGINSETTINGS");
//    for(int i=0; i<pannerlib_getMaxNumSources(); i++){
//        xml.setAttribute("SourceAziDeg" + String(i), pannerlib_getSourceAzi_deg(hMEQ,i));
//        xml.setAttribute("SourceElevDeg" + String(i), pannerlib_getSourceElev_deg(hMEQ,i));
//    }
//    xml.setAttribute("nSources", pannerlib_getNumSources(hMEQ));
//    xml.setAttribute("DTT", pannerlib_getDTT(hMEQ));
//
//    for(int i=0; i<pannerlib_getMaxNumLoudspeakers(); i++){
//        xml.setAttribute("LoudspeakerAziDeg" + String(i), pannerlib_getLoudspeakerAzi_deg(hMEQ,i));
//        xml.setAttribute("LoudspeakerElevDeg" + String(i), pannerlib_getLoudspeakerElev_deg(hMEQ,i));
//    }
//    xml.setAttribute("nLoudspeakers", pannerlib_getNumLoudspeakers(hMEQ));

    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    int i;

//    if (xmlState != nullptr) {
//        if (xmlState->hasTagName("MCEQPLUGINSETTINGS")) {
//            for(i=0; i<1; i++){
//                pannerlib_setSourceAzi_deg(hMEQ, i, (float)xmlState->getDoubleAttribute("SourceAziDeg" + String(i), 0.0f));
//                pannerlib_setSourceElev_deg(hMEQ, i, (float)xmlState->getDoubleAttribute("SourceElevDeg" + String(i), 0.0f));
//            }
//            for(; i<pannerlib_getMaxNumSources(); i++){
//                pannerlib_setSourceAzi_deg(hMEQ, i, (float)xmlState->getDoubleAttribute("SourceAziDeg" + String(i), 180.0f/M_PI * default_LScoords64_rad[i][0]));
//                pannerlib_setSourceElev_deg(hMEQ, i, (float)xmlState->getDoubleAttribute("SourceElevDeg" + String(i), 180.0f/M_PI * default_LScoords64_rad[i][1]));
//            }
//            pannerlib_setNumSources(hMEQ, xmlState->getIntAttribute("nSources", 1));
//            pannerlib_setDTT(hMEQ, (float)xmlState->getDoubleAttribute("DTT", 1));
//
//            for(i=0; i<9; i++){
//                pannerlib_setLoudspeakerAzi_deg(hMEQ, i, (float)xmlState->getDoubleAttribute("LoudspeakerAziDeg" + String(i), 0.0f));
//                pannerlib_setLoudspeakerElev_deg(hMEQ, i, (float)xmlState->getDoubleAttribute("LoudspeakerElevDeg" + String(i), 0.0f));
//            }
//            for(; i<pannerlib_getMaxNumLoudspeakers(); i++){
//                pannerlib_setLoudspeakerAzi_deg(hMEQ, i, (float)xmlState->getDoubleAttribute("LoudspeakerAziDeg" + String(i), 180.0f/M_PI * default_LScoords64_rad[i][0]));
//                pannerlib_setLoudspeakerElev_deg(hMEQ, i, (float)xmlState->getDoubleAttribute("LoudspeakerElevDeg" + String(i), 180.0f/M_PI * default_LScoords64_rad[i][1]));
//            }
//            pannerlib_setNumLoudspeakers(hMEQ, xmlState->getIntAttribute("nLoudspeakers", 1));
//        }
//    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

