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
    
	ambi_dec_create(&hAmbi);
}

PluginProcessor::~PluginProcessor()
{
	ambi_dec_destroy(&hAmbi);
    
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

	ambi_dec_init(hAmbi, sampleRate);
    
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
        memset(ringBufferInputs[i], 0, FRAME_SIZE*sizeof(float));
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
        memset(ringBufferOutputs[i], 0, FRAME_SIZE * sizeof(float));
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
                isPlaying = false;
            
            /* perform processing */
            ambi_dec_process(hAmbi, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, isPlaying);
            
            /* replace buffer with new audio */
            buffer.clear(frame*FRAME_SIZE, FRAME_SIZE);
            for (int ch = 0; ch < nNumOutputs; ch++)
                for (int i = 0; i < FRAME_SIZE; i++)
                    bufferData[ch][frame*FRAME_SIZE + i] = ringBufferOutputs[ch][i];
        }
    }
    else
        buffer.clear();
    
//    playHead = getPlayHead();
//    bool PlayHeadAvailable = playHead->getCurrentPosition(currentPosition);
//    if (PlayHeadAvailable == true)
//        isPlaying = currentPosition.isPlaying;
//    else
//        isPlaying = false;
//
//    switch (nCurrentBlockSize) {
//        case (FRAME_SIZE * 8):
//            for (int frame = 0; frame < 8; frame++) {
//                for (int ch = 0; ch < nNumInputs; ch++)
//                    for (int i = 0; i < FRAME_SIZE; i++)
//                        ringBufferInputs[ch][i] = bufferData[ch][frame*FRAME_SIZE + i];
//                ambi_dec_process(hAmbi, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, (int)isPlaying);
//                buffer.clear(frame*FRAME_SIZE, FRAME_SIZE);
//                for (int ch = 0; ch < nNumOutputs; ch++)
//                    for (int i = 0; i < FRAME_SIZE; i++)
//                        bufferData[ch][frame*FRAME_SIZE + i] = ringBufferOutputs[ch][i];
//            }
//            break;
//
//        case (FRAME_SIZE * 4):
//            for (int frame = 0; frame < 4; frame++) {
//                for (int ch = 0; ch < nNumInputs; ch++)
//                    for (int i = 0; i < FRAME_SIZE; i++)
//                        ringBufferInputs[ch][i] = bufferData[ch][frame*FRAME_SIZE + i];
//                ambi_dec_process(hAmbi, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, (int)isPlaying);
//                buffer.clear(frame*FRAME_SIZE, FRAME_SIZE);
//                for (int ch = 0; ch < nNumOutputs; ch++)
//                    for (int i = 0; i < FRAME_SIZE; i++)
//                        bufferData[ch][frame*FRAME_SIZE + i] = ringBufferOutputs[ch][i];
//            }
//            break;
//
//        case (FRAME_SIZE*2):
//            for(int frame = 0; frame < 2; frame++){
//                for (int ch = 0; ch < nNumInputs; ch++)
//                    for (int i = 0; i < FRAME_SIZE; i++)
//                        ringBufferInputs[ch][i] = bufferData[ch][frame*FRAME_SIZE + i];
//                ambi_dec_process(hAmbi, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, (int)isPlaying);
//                buffer.clear(frame*FRAME_SIZE, FRAME_SIZE);
//                for (int ch = 0; ch < nNumOutputs; ch++)
//                    for (int i = 0; i < FRAME_SIZE; i++)
//                        bufferData[ch][frame*FRAME_SIZE + i] = ringBufferOutputs[ch][i];
//            }
//            break;
//
//        case FRAME_SIZE:
//            ambi_dec_process(hAmbi, bufferData, outputs, nNumInputs, nNumOutputs, FRAME_SIZE, (int)isPlaying);
//            buffer.clear();
//            for (int ch = 0; ch < nNumOutputs; ch++)
//                for (int i = 0; i < FRAME_SIZE; i++)
//                    bufferData[ch][i] = outputs[ch][i];
//            break;
//
//        default:
//            buffer.clear();
//            break;
//    }

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
    XmlElement xml("AMBIDECPLUGINSETTINGSO"+String(SH_ORDER));
 
    for(int band=0; band<ambi_dec_getNumberOfBands(); band++){
        xml.setAttribute("DecOrder"+String(band), ambi_dec_getDecOrder(hAmbi, band));
    }
    for(int i=0; i<ambi_dec_getMaxNumLoudspeakers(); i++){
        xml.setAttribute("LoudspeakerAziDeg" + String(i), ambi_dec_getLoudspeakerAzi_deg(hAmbi,i));
        xml.setAttribute("LoudspeakerElevDeg" + String(i), ambi_dec_getLoudspeakerElev_deg(hAmbi,i));
    }
    xml.setAttribute("nLoudspeakers", ambi_dec_getNumLoudspeakers(hAmbi));
    xml.setAttribute("BinauraliseLS", ambi_dec_getBinauraliseLSflag(hAmbi));
    xml.setAttribute("UseDefaultHRIRset", ambi_dec_getUseDefaultHRIRsflag(hAmbi));
    xml.setAttribute("Norm", ambi_dec_getNormType(hAmbi));
    xml.setAttribute("ChOrder", ambi_dec_getChOrder(hAmbi));
    xml.setAttribute("Dec1method", ambi_dec_getDecMethod(hAmbi, 0));
    xml.setAttribute("Dec2method", ambi_dec_getDecMethod(hAmbi, 1));
    xml.setAttribute("Dec1normType", ambi_dec_getDecNormType(hAmbi, 0));
    xml.setAttribute("Dec2normType", ambi_dec_getDecNormType(hAmbi, 1));
    xml.setAttribute("Dec1maxrE", ambi_dec_getDecEnableMaxrE(hAmbi, 0));
    xml.setAttribute("Dec2maxrE", ambi_dec_getDecEnableMaxrE(hAmbi, 1));
    xml.setAttribute("TransitionFreq", ambi_dec_getTransitionFreq(hAmbi));
    
    if(!ambi_dec_getUseDefaultHRIRsflag(hAmbi))
        xml.setAttribute("SofaFilePath", String(ambi_dec_getSofaFilePath(hAmbi)));

    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    int i;

    if (xmlState != nullptr) {
        if (xmlState->hasTagName("AMBIDECPLUGINSETTINGSO"+String(SH_ORDER))) {
            for(int band=0; band<ambi_dec_getNumberOfBands(); band++){
                if(xmlState->hasAttribute("DecOrder"+String(band)))
                    ambi_dec_setDecOrder(hAmbi, xmlState->getIntAttribute("DecOrder"+String(band),0), band);
            }
            for(i=0; i<ambi_dec_getMaxNumLoudspeakers(); i++){
                if(xmlState->hasAttribute("LoudspeakerAziDeg" + String(i)))
                    ambi_dec_setLoudspeakerAzi_deg(hAmbi, i, (float)xmlState->getDoubleAttribute("LoudspeakerAziDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("LoudspeakerElevDeg" + String(i)))
                    ambi_dec_setLoudspeakerElev_deg(hAmbi, i, (float)xmlState->getDoubleAttribute("LoudspeakerElevDeg" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("nLoudspeakers"))
                ambi_dec_setNumLoudspeakers(hAmbi, xmlState->getIntAttribute("nLoudspeakers", 1));
            if(xmlState->hasAttribute("BinauraliseLS"))
                ambi_dec_setBinauraliseLSflag(hAmbi, xmlState->getIntAttribute("BinauraliseLS", 1));
            if(xmlState->hasAttribute("UseDefaultHRIRset"))
                ambi_dec_setUseDefaultHRIRsflag(hAmbi, xmlState->getIntAttribute("UseDefaultHRIRset", 1));
            if(xmlState->hasAttribute("Norm"))
                ambi_dec_setNormType(hAmbi, xmlState->getIntAttribute("Norm", 1));
            if(xmlState->hasAttribute("ChOrder"))
                ambi_dec_setChOrder(hAmbi, xmlState->getIntAttribute("ChOrder", 1));
            if(xmlState->hasAttribute("Dec1method"))
                ambi_dec_setDecMethod(hAmbi, 0, xmlState->getIntAttribute("Dec1method", 1));
            if(xmlState->hasAttribute("Dec2method"))
                ambi_dec_setDecMethod(hAmbi, 1, xmlState->getIntAttribute("Dec2method", 1));
            if(xmlState->hasAttribute("Dec1normType"))
                ambi_dec_setDecNormType(hAmbi, 0, xmlState->getIntAttribute("Dec1normType", 1));
            if(xmlState->hasAttribute("Dec2normType"))
                ambi_dec_setDecNormType(hAmbi, 1, xmlState->getIntAttribute("Dec2normType", 1));
            if(xmlState->hasAttribute("Dec1maxrE"))
                ambi_dec_setDecEnableMaxrE(hAmbi, 0, xmlState->getIntAttribute("Dec1maxrE", 1));
            if(xmlState->hasAttribute("Dec2maxrE"))
                ambi_dec_setDecEnableMaxrE(hAmbi, 1, xmlState->getIntAttribute("Dec2maxrE", 1));
            if(xmlState->hasAttribute("TransitionFreq"))
                ambi_dec_setTransitionFreq(hAmbi, (float)xmlState->getDoubleAttribute("TransitionFreq", 1e3f));
            
            if(xmlState->hasAttribute("SofaFilePath")){
                String directory = xmlState->getStringAttribute("SofaFilePath", "no_file");
                const char* new_cstring = (const char*)directory.toUTF8();
                ambi_dec_setSofaFilePath(hAmbi, new_cstring);
            }
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

