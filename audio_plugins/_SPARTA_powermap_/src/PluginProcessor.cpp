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
    powermap_create(&hPm);
    isPlaying = false;
    
    /* camera default settings */
    cameraID = 1;
    flipLR = flipUD = false;
    greyScale = true;
    startTimer(TIMER_PROCESSING_RELATED, 40);
}

PluginProcessor::~PluginProcessor()
{
    powermap_destroy(&hPm);
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

    powermap_init(hPm, nSampleRate);
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

    powermap_analysis(hPm, bufferData, nNumInputs, nCurrentBlockSize, isPlaying); 
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
 	XmlElement xml("POWERMAPAUDIOPLUGINSETTINGS");

    xml.setAttribute("masterOrder", powermap_getMasterOrder(hPm));
    xml.setAttribute("powermapMode", powermap_getPowermapMode(hPm));
    xml.setAttribute("covAvgCoeff", powermap_getCovAvgCoeff(hPm));
    for(int i=0; i<powermap_getNumberOfBands(); i++){
        xml.setAttribute("powermapEQ"+String(i), powermap_getPowermapEQ(hPm, i));
        xml.setAttribute("anaOrder"+String(i), powermap_getAnaOrder(hPm, i));
    }
    xml.setAttribute("chOrder", powermap_getChOrder(hPm));
    xml.setAttribute("normType", powermap_getNormType(hPm));
    xml.setAttribute("numSources", powermap_getNumSources(hPm));
    xml.setAttribute("dispFov", powermap_getDispFOV(hPm));
    xml.setAttribute("aspectRatio", powermap_getAspectRatio(hPm));
    xml.setAttribute("powermapAvgCoeff", powermap_getPowermapAvgCoeff(hPm));
    
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
        if (xmlState->hasTagName("POWERMAPAUDIOPLUGINSETTINGS")) {
            if(xmlState->hasAttribute("masterOrder"))
                powermap_setMasterOrder(hPm, xmlState->getIntAttribute("masterOrder", 1));
            if(xmlState->hasAttribute("powermapMode"))
                powermap_setPowermapMode(hPm, xmlState->getIntAttribute("powermapMode", 1));
            if(xmlState->hasAttribute("covAvgCoeff"))
                powermap_setCovAvgCoeff(hPm, (float)xmlState->getDoubleAttribute("covAvgCoeff", 0.5f));
            for(int i=0; i<powermap_getNumberOfBands(); i++){
                if(xmlState->hasAttribute("powermapEQ"+String(i)))
                    powermap_setPowermapEQ(hPm, (float)xmlState->getDoubleAttribute("powermapEQ"+String(i), 0.5f), i);
                if(xmlState->hasAttribute("anaOrder"+String(i)))
                    powermap_setAnaOrder(hPm, xmlState->getIntAttribute("anaOrder"+String(i), 1), i);
            }
            if(xmlState->hasAttribute("chOrder"))
                powermap_setChOrder(hPm, xmlState->getIntAttribute("chOrder", 1));
            if(xmlState->hasAttribute("normType"))
                powermap_setNormType(hPm, xmlState->getIntAttribute("normType", 1));
            if(xmlState->hasAttribute("numSources"))
                powermap_setNumSources(hPm, xmlState->getIntAttribute("numSources", 1));
            if(xmlState->hasAttribute("dispFov"))
                powermap_setDispFOV(hPm, xmlState->getIntAttribute("dispFov", 1));
            if(xmlState->hasAttribute("aspectRatio"))
                powermap_setAspectRatio(hPm, xmlState->getIntAttribute("aspectRatio", 1));
            if(xmlState->hasAttribute("powermapAvgCoeff"))
                powermap_setPowermapAvgCoeff(hPm, (float)xmlState->getDoubleAttribute("powermapAvgCoeff", 0.5f));

            if(xmlState->hasAttribute("cameraID"))
                cameraID = (int)xmlState->getIntAttribute("cameraID", 1);
            if(xmlState->hasAttribute("flipLR"))
                flipLR = (bool)xmlState->getIntAttribute("flipLR", 0);
            if(xmlState->hasAttribute("flipUD"))
                flipUD = (bool)xmlState->getIntAttribute("flipUD", 0);
            if(xmlState->hasAttribute("greyScale"))
                greyScale = (bool)xmlState->getIntAttribute("greyScale", 1);
            
			powermap_refreshSettings(hPm);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

