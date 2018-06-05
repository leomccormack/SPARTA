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
    
	array2sh_create(&hA2sh);
}

PluginProcessor::~PluginProcessor()
{
	array2sh_destroy(&hA2sh);
    
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

    array2sh_init(hA2sh, sampleRate);

    for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
        memset(ringBufferInputs[i], 0, FRAME_SIZE*sizeof(float));
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
        memset(ringBufferOutputs[i], 0, FRAME_SIZE * sizeof(float));
    
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
        memset(outputs[i],0,FRAME_SIZE*sizeof(float));
    }
    
    if(nCurrentBlockSize % FRAME_SIZE == 0){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/FRAME_SIZE; frame++) {
            for (int ch = 0; ch < nNumInputs; ch++)
                for (int i = 0; i < FRAME_SIZE; i++)
                    ringBufferInputs[ch][i] = bufferData[ch][frame*FRAME_SIZE + i];
            
            /* determine if there is actually audio in the damn buffer */
            playHead = getPlayHead();
            bool PlayHeadAvailable = playHead->getCurrentPosition(currentPosition);
            if (PlayHeadAvailable == true)
                isPlaying = currentPosition.isPlaying;
            else
                isPlaying = true;
//            if(buffer.getRMSLevel(0, 0, nCurrentBlockSize)>0.000001f) /* Plogue Bidule informs plug-in that it has a playHead, but it is not moving... */
//                isPlaying = true;
            
            /* perform processing */
            array2sh_process(hA2sh, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, (int)isPlaying);
            
            /* replace buffer with new audio */
            buffer.clear(frame*FRAME_SIZE, FRAME_SIZE);
            for (int ch = 0; ch < nNumOutputs; ch++)
                for (int i = 0; i < FRAME_SIZE; i++)
                    bufferData[ch][frame*FRAME_SIZE + i] = ringBufferOutputs[ch][i];
        }
    }
    else
        buffer.clear();

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
    XmlElement xml("ARRAY2SHPLUGINSETTINGS"+String(SH_ORDER));
    
    xml.setAttribute("Q", array2sh_getNumSensors(hA2sh));
    for(int i=0; i<MAX_NUM_CHANNELS; i++){
        xml.setAttribute("AziRad" + String(i), array2sh_getSensorAzi_rad(hA2sh,i));
        xml.setAttribute("ElevRad" + String(i), array2sh_getSensorElev_rad(hA2sh,i));
    }
    xml.setAttribute("r", array2sh_getr(hA2sh));
    xml.setAttribute("R", array2sh_getR(hA2sh));
    xml.setAttribute("admittance", array2sh_getAdmittance(hA2sh));
    xml.setAttribute("arrayType", array2sh_getArrayType(hA2sh));
    xml.setAttribute("weightType", array2sh_getWeightType(hA2sh));
    xml.setAttribute("regType", array2sh_getRegType(hA2sh));
    xml.setAttribute("regPar", array2sh_getRegPar(hA2sh));
    xml.setAttribute("chOrder", array2sh_getChOrder(hA2sh));
    xml.setAttribute("normType", array2sh_getNormType(hA2sh));
    xml.setAttribute("c", array2sh_getc(hA2sh));
    xml.setAttribute("gain", array2sh_getGain(hA2sh));
    xml.setAttribute("maxFreq", array2sh_getMaxFreq(hA2sh));
    
    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    int i;
    
    if (xmlState != nullptr) {
        if (xmlState->hasTagName("ARRAY2SHPLUGINSETTINGS"+String(SH_ORDER))) {
            for(i=0; i<array2sh_getMaxNumSensors(); i++){
                if(xmlState->hasAttribute("AziRad" + String(i)))
                    array2sh_setSensorAzi_rad(hA2sh, i, (float)xmlState->getDoubleAttribute("AziRad" + String(i), 0.0f));
                if(xmlState->hasAttribute("ElevRad" + String(i)))
                    array2sh_setSensorElev_rad(hA2sh, i, (float)xmlState->getDoubleAttribute("ElevRad" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("Q"))
                array2sh_setNumSensors(hA2sh, xmlState->getIntAttribute("Q", (SH_ORDER+1)*(SH_ORDER+1)));
            if(xmlState->hasAttribute("r"))
                array2sh_setr(hA2sh, (float)xmlState->getDoubleAttribute("r", 0.042));
            if(xmlState->hasAttribute("R"))
                array2sh_setR(hA2sh, (float)xmlState->getDoubleAttribute("R", 0.042));
            if(xmlState->hasAttribute("admittance"))
                array2sh_setAdmittance(hA2sh, (float)xmlState->getDoubleAttribute("admittance", 0.0));
            if(xmlState->hasAttribute("arrayType"))
                array2sh_setArrayType(hA2sh, xmlState->getIntAttribute("arrayType", 1));
            if(xmlState->hasAttribute("weightType"))
                array2sh_setWeightType(hA2sh, xmlState->getIntAttribute("weightType", 1));
            if(xmlState->hasAttribute("regType"))
                array2sh_setRegType(hA2sh, xmlState->getIntAttribute("regType", 3));
            if(xmlState->hasAttribute("regPar"))
                array2sh_setRegPar(hA2sh, (float)xmlState->getDoubleAttribute("regPar", 15.0));
            if(xmlState->hasAttribute("chOrder"))
                array2sh_setChOrder(hA2sh, xmlState->getIntAttribute("chOrder", 1));
            if(xmlState->hasAttribute("normType"))
                array2sh_setNormType(hA2sh, xmlState->getIntAttribute("normType", 1));
            if(xmlState->hasAttribute("c"))
                array2sh_setc(hA2sh, (float)xmlState->getDoubleAttribute("c", 343.0));
            if(xmlState->hasAttribute("gain"))
                array2sh_setGain(hA2sh, (float)xmlState->getDoubleAttribute("gain", 0.0));
            if(xmlState->hasAttribute("maxFreq"))
                array2sh_setMaxFreq(hA2sh, (float)xmlState->getDoubleAttribute("maxFreq", 20000.0));
            
            array2sh_refreshSettings(hA2sh);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

