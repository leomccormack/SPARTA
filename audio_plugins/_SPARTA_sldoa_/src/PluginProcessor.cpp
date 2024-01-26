/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2017/2018 - Leo McCormack.
 
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
	sldoa_create(&hSld);
    startTimer(TIMER_PROCESSING_RELATED, 40);
    isPlaying = false;
    
    /* camera default settings */
    cameraID = 1;
    flipLR = flipUD = false;
    greyScale = true; 
}

PluginProcessor::~PluginProcessor()
{
	sldoa_destroy(&hSld);
}

void PluginProcessor::setParameter (int index, float /*newValue*/)
{
	switch (index)
	{
		default: break;
	}
}

void PluginProcessor::setCurrentProgram (int /*index*/)
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
    nSampleRate = (int)(sampleRate + 0.5);
    isPlaying = false; 
	sldoa_init(hSld, nSampleRate);

    //AudioProcessor::setLatencySamples(sldoa_getProcessingDelay());
}

void PluginProcessor::releaseResources()
{
    isPlaying = false;
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
	int nCurrentBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels());
    float* const* bufferData = buffer.getArrayOfWritePointers();
 
    /* check whether the playhead is moving */
    playHead = getPlayHead();
    if(playHead!=NULL)
        isPlaying = playHead->getCurrentPosition(currentPosition) == true ? currentPosition.isPlaying : false;
    else
        isPlaying = false;

    /* If there is no playhead, or it is not moving, see if there is audio in the buffer */
    if(!isPlaying){
        for(int j=0; j<nNumInputs; j++){
            isPlaying = buffer.getMagnitude(j, 0, MIN(8,nCurrentBlockSize) /* should be enough */)>1e-5f ? true : false;
            if(isPlaying)
                break;
        }
    }

    /* perform processing */
    sldoa_analysis(hSld, bufferData, nNumInputs, nCurrentBlockSize, isPlaying);
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
	XmlElement xml("SLDOAAUDIOPLUGINSETTINGS");

	/* add attributes */
    xml.setAttribute("MasterOrder", sldoa_getMasterOrder(hSld));
    xml.setAttribute("MaxFreq", sldoa_getMaxFreq(hSld));
    xml.setAttribute("MinFreq", sldoa_getMinFreq(hSld));
    xml.setAttribute("Avg", sldoa_getAvg(hSld));
    for(int i=0; i<sldoa_getNumberOfBands(); i++)
        xml.setAttribute("AnaOrder" + String(i), sldoa_getAnaOrder(hSld, i));
    xml.setAttribute("ChOrder", (int)sldoa_getChOrder(hSld));
    xml.setAttribute("Norm", (int)sldoa_getNormType(hSld));
    
    xml.setAttribute("cameraID", cameraID);
    xml.setAttribute("flipLR", flipLR);
    xml.setAttribute("flipUD", flipUD);
    xml.setAttribute("greyScale", greyScale);
    
	copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr) {
        /* make sure that it's actually the correct type of XML object */
        if (xmlState->hasTagName("SLDOAAUDIOPLUGINSETTINGS")) {
            /* pull attributes */
            if(xmlState->hasAttribute("MasterOrder"))
                sldoa_setMasterOrder(hSld, xmlState->getIntAttribute("MasterOrder", 1));
            if(xmlState->hasAttribute("MaxFreq"))
                sldoa_setMaxFreq(hSld, (float)xmlState->getDoubleAttribute("MaxFreq", 5000.0));
            if(xmlState->hasAttribute("MinFreq"))
                sldoa_setMinFreq(hSld, (float)xmlState->getDoubleAttribute("MinFreq", 500.0));
            if(xmlState->hasAttribute("Avg"))
                sldoa_setAvg(hSld, (float)xmlState->getDoubleAttribute("Avg", 100.0));
            for(int i=0; i<sldoa_getNumberOfBands(); i++){
                if(xmlState->hasAttribute("AnaOrder"+String(i)))
                    sldoa_setAnaOrder(hSld, xmlState->getIntAttribute("AnaOrder"+String(i), 1), i);
            }
            if(xmlState->hasAttribute("ChOrder"))
                sldoa_setChOrder(hSld, xmlState->getIntAttribute("ChOrder", 1));
            if(xmlState->hasAttribute("Norm"))
                sldoa_setNormType(hSld, xmlState->getIntAttribute("Norm", 1));
            
            if(xmlState->hasAttribute("cameraID"))
                cameraID = (int)xmlState->getIntAttribute("cameraID", 1);
            if(xmlState->hasAttribute("flipLR"))
                flipLR = (bool)xmlState->getIntAttribute("flipLR", 0);
            if(xmlState->hasAttribute("flipUD"))
                flipUD = (bool)xmlState->getIntAttribute("flipUD", 0);
            if(xmlState->hasAttribute("greyScale"))
                greyScale = (bool)xmlState->getIntAttribute("greyScale", 1);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

