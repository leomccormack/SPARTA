/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2019 - Leo McCormack.
 
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
    dirass_create(&hDir);

    isPlaying = false;
    
    /* camera default settings */
    cameraID = 1;
    flipLR = flipUD = false;
    greyScale = true;
    startTimer(TIMER_PROCESSING_RELATED, 40);
}

PluginProcessor::~PluginProcessor()
{
    dirass_destroy(&hDir);
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
    nSampleRate = (int)(sampleRate + 0.5);
    nNumInputs = getTotalNumInputChannels();
    isPlaying = false;
    dirass_init(hDir, nSampleRate);

    //AudioProcessor::setLatencySamples(dirass_getProcessingDelay());
}

void PluginProcessor::releaseResources()
{
    isPlaying = false;
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    int nCurrentBlockSize = buffer.getNumSamples();
    nNumInputs = getTotalNumInputChannels(), buffer.getNumChannels();
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

    /* perform analysis */
    dirass_analysis(hDir, bufferData, nNumInputs, nCurrentBlockSize, isPlaying);
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
 	XmlElement xml("DIRASSAUDIOPLUGINSETTINGS");
 
    xml.setAttribute("beamType", dirass_getBeamType(hDir));
    xml.setAttribute("InputOrder", dirass_getInputOrder(hDir));
    xml.setAttribute("GridOption", dirass_getDisplayGridOption(hDir));
    xml.setAttribute("UpscaleOrder", dirass_getUpscaleOrder(hDir));
    xml.setAttribute("DirASSmode", dirass_getDiRAssMode(hDir));
    xml.setAttribute("MinFreq", dirass_getMinFreq(hDir));
    xml.setAttribute("MaxFreq", dirass_getMaxFreq(hDir));
    xml.setAttribute("CHorder", dirass_getChOrder(hDir));
    xml.setAttribute("Norm", dirass_getNormType(hDir));
    xml.setAttribute("FOVoption", dirass_getDispFOV(hDir));
    xml.setAttribute("ARoption", dirass_getAspectRatio(hDir));
    xml.setAttribute("MapAvg", dirass_getMapAvgCoeff(hDir));
    xml.setAttribute("DispWidth", dirass_getDispWidth(hDir));
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
        if (xmlState->hasTagName("DIRASSAUDIOPLUGINSETTINGS")) { 
            if(xmlState->hasAttribute("beamType"))
                dirass_setBeamType(hDir, xmlState->getIntAttribute("beamType", 1));
            if(xmlState->hasAttribute("InputOrder"))
                dirass_setInputOrder(hDir, xmlState->getIntAttribute("InputOrder", 1));
            if(xmlState->hasAttribute("GridOption"))
                dirass_setDisplayGridOption(hDir, xmlState->getIntAttribute("GridOption", 1));
            if(xmlState->hasAttribute("UpscaleOrder"))
                dirass_setUpscaleOrder(hDir, xmlState->getIntAttribute("UpscaleOrder", 1));
            if(xmlState->hasAttribute("DirASSmode"))
                dirass_setDiRAssMode(hDir, xmlState->getIntAttribute("DirASSmode", 1));
            if(xmlState->hasAttribute("MinFreq"))
                dirass_setMinFreq(hDir, (float)xmlState->getDoubleAttribute("MinFreq", 100.0f));
            if(xmlState->hasAttribute("MaxFreq"))
                dirass_setMaxFreq(hDir, (float)xmlState->getDoubleAttribute("MaxFreq", 20e3f));
            if(xmlState->hasAttribute("CHorder"))
                dirass_setChOrder(hDir, xmlState->getIntAttribute("CHorder", 1));
            if(xmlState->hasAttribute("Norm"))
                dirass_setNormType(hDir, xmlState->getIntAttribute("Norm", 1));
            if(xmlState->hasAttribute("FOVoption"))
                dirass_setDispFOV(hDir, xmlState->getIntAttribute("FOVoption", 1));
            if(xmlState->hasAttribute("ARoption"))
                dirass_setAspectRatio(hDir, xmlState->getIntAttribute("ARoption", 1));
            if(xmlState->hasAttribute("MapAvg"))
                dirass_setMapAvgCoeff(hDir, (float)xmlState->getDoubleAttribute("MapAvg", 0.5f));
            if(xmlState->hasAttribute("DispWidth"))
                dirass_setDispWidth(hDir, (float)xmlState->getDoubleAttribute("DispWidth", 120));
            if(xmlState->hasAttribute("cameraID"))
                cameraID = (int)xmlState->getIntAttribute("cameraID", 1);
            if(xmlState->hasAttribute("flipLR"))
                flipLR = (bool)xmlState->getIntAttribute("flipLR", 0);
            if(xmlState->hasAttribute("flipUD"))
                flipUD = (bool)xmlState->getIntAttribute("flipUD", 0);
            if(xmlState->hasAttribute("greyScale"))
                greyScale = (bool)xmlState->getIntAttribute("greyScale", 1);
                
			dirass_refreshSettings(hDir);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

