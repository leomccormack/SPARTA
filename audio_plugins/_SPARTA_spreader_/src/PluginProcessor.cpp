/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2021 - Leo McCormack.
 
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
	spreader_create(&hSpr);

    refreshWindow = true;
    startTimer(TIMER_PROCESSING_RELATED, 80);
}

PluginProcessor::~PluginProcessor()
{
	spreader_destroy(&hSpr);
}

void PluginProcessor::setParameter (int index, float newValue)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_numInputs:       spreader_setNumSources(hSpr, (int)(newValue*(float)(SPREADER_MAX_NUM_SOURCES)+0.5)); break;
        }
    }
    /* source direction parameters */
    else{
        index-=k_NumOfParameters;
        float newValueScaled;
        if (!(index % 2)){
            newValueScaled = (newValue - 0.5f)*360.0f;
            if (newValueScaled != spreader_getSourceAzi_deg(hSpr, index/2)){
                spreader_setSourceAzi_deg(hSpr, index/2, newValueScaled);
                refreshWindow = true;
            }
        }
        else{
            newValueScaled = (newValue - 0.5f)*180.0f;
            if (newValueScaled != spreader_getSourceElev_deg(hSpr, index/2)){
                spreader_setSourceElev_deg(hSpr, index/2, newValueScaled);
                refreshWindow = true;
            }
        }
    }
}

void PluginProcessor::setCurrentProgram (int /*index*/)
{
}

float PluginProcessor::getParameter (int index)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_numInputs:       return (float)(spreader_getNumSources(hSpr))/(float)(SPREADER_MAX_NUM_SOURCES);
            default: return 0.0f;
        }
    }
    /* source direction parameters */
    else{
        index-=k_NumOfParameters;
        if (!(index % 2))
            return (spreader_getSourceAzi_deg(hSpr, index/2)/360.0f) + 0.5f;
        else
            return (spreader_getSourceElev_deg(hSpr, (index-1)/2)/180.0f) + 0.5f;
    }
}

int PluginProcessor::getNumParameters()
{
	return k_NumOfParameters + 2*SPREADER_MAX_NUM_SOURCES;
}

const String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

const String PluginProcessor::getParameterName (int index)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_numInputs:       return "num_sources";
            default: return "NULL";
        }
    }
    /* source direction parameters */
    else{
        index-=k_NumOfParameters;
        if (!(index % 2))
            return TRANS("Azim_") + String(index/2);
        else
            return TRANS("Elev_") + String((index-1)/2);
    }
}

const String PluginProcessor::getParameterText(int index)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) { 
            case k_numInputs:       return String(spreader_getNumSources(hSpr));
            default: return "NULL";
        }
    }
    /* source direction parameters */
    else{
        index-=k_NumOfParameters;
        if (!(index % 2))
            return String(spreader_getSourceAzi_deg(hSpr, index/2));
        else
            return String(spreader_getSourceElev_deg(hSpr, (index-1)/2));
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
    nNumInputs =  getTotalNumInputChannels();
    nNumOutputs = getTotalNumOutputChannels();
	nSampleRate = (int)(sampleRate + 0.5);
    
	spreader_init(hSpr, nSampleRate);
    AudioProcessor::setLatencySamples(spreader_getProcessingDelay());
}

void PluginProcessor::releaseResources()
{
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels());
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels());
    float** bufferData = buffer.getArrayOfWritePointers();
    float* pFrameData[MAX_NUM_CHANNELS];
    int frameSize = spreader_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < buffer.getNumChannels(); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            spreader_process(hSpr, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
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
    XmlElement xml("SPREADERPLUGINSETTINGS");
    for(int i=0; i<spreader_getMaxNumSources(); i++){
        xml.setAttribute("SourceAziDeg" + String(i), spreader_getSourceAzi_deg(hSpr,i));
        xml.setAttribute("SourceElevDeg" + String(i), spreader_getSourceElev_deg(hSpr,i));
        xml.setAttribute("SourceSpreadDeg" + String(i), spreader_getSourceSpread_deg(hSpr,i));
    }
    xml.setAttribute("nSources", spreader_getNumSources(hSpr));
    xml.setAttribute("procMode", spreader_getSpreadingMode(hSpr));
    xml.setAttribute("avgCoeff", spreader_getAveragingCoeff(hSpr));

    if(!spreader_getUseDefaultHRIRsflag(hSpr))
        xml.setAttribute("SofaFilePath", String(spreader_getSofaFilePath(hSpr)));

    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr) {
        if (xmlState->hasTagName("SPREADERPLUGINSETTINGS")) {
            for(int i=0; i<spreader_getMaxNumSources(); i++){
                if(xmlState->hasAttribute("SourceAziDeg" + String(i)))
                    spreader_setSourceAzi_deg(hSpr, i, (float)xmlState->getDoubleAttribute("SourceAziDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceElevDeg" + String(i)))
                    spreader_setSourceElev_deg(hSpr, i, (float)xmlState->getDoubleAttribute("SourceElevDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceSpreadDeg" + String(i)))
                    spreader_setSourceSpread_deg(hSpr, i, (float)xmlState->getDoubleAttribute("SourceSpreadDeg" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("nSources"))
                spreader_setNumSources(hSpr, xmlState->getIntAttribute("nSources", 1));
            if(xmlState->hasAttribute("procMode"))
                spreader_setSpreadingMode(hSpr, xmlState->getIntAttribute("procMode", 1));
            if(xmlState->hasAttribute("avgCoeff"))
                spreader_setAveragingCoeff(hSpr, xmlState->getDoubleAttribute("avgCoeff", 0.5f));

            if(xmlState->hasAttribute("SofaFilePath")){
                String directory = xmlState->getStringAttribute("SofaFilePath", "no_file");
                const char* new_cstring = (const char*)directory.toUTF8();
                spreader_setSofaFilePath(hSpr, new_cstring);
            }

            spreader_refreshSettings(hSpr);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
} 
