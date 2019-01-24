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
    bufferInputs = new float*[MAX_NUM_CHANNELS];
    for (int i = 0; i < MAX_NUM_CHANNELS; i++)
        bufferInputs[i] = new float[FRAME_SIZE];
    
    bufferOutputs = new float*[MAX_NUM_CHANNELS];
    for (int i = 0; i < MAX_NUM_CHANNELS; i++)
        bufferOutputs[i] = new float[FRAME_SIZE];
    
	panner_create(&hPan);
    refreshWindow = true;
}

PluginProcessor::~PluginProcessor()
{
	panner_destroy(&hPan);
    
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
        delete[] bufferInputs[i];
    delete[] bufferInputs;
    
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
        delete[] bufferOutputs[i];
    delete[] bufferOutputs;
}

void PluginProcessor::setParameter (int index, float newValue)
{
    float newValueScaled;
    if (!(index % 2)){
        newValueScaled = (newValue - 0.5f)*360.0f;
        if (newValueScaled != panner_getSourceAzi_deg(hPan, index/2)){
            panner_setSourceAzi_deg(hPan, index/2, newValueScaled);
            refreshWindow = true;
        }
    }
    else{
        newValueScaled = (newValue - 0.5f)*180.0f;
        if (newValueScaled != panner_getSourceElev_deg(hPan, index/2)){
            panner_setSourceElev_deg(hPan, index/2, newValueScaled);
            refreshWindow = true;
        }
    }
}

void PluginProcessor::setCurrentProgram (int index)
{
}

float PluginProcessor::getParameter (int index)
{
    if (!(index % 2))
        return (panner_getSourceAzi_deg(hPan, index/2)/360.0f) + 0.5f;
    else
        return (panner_getSourceElev_deg(hPan, (index-1)/2)/180.0f) + 0.5f;
}

int PluginProcessor::getNumParameters()
{
	return MIN(panner_getMaxNumSources(), NUM_OF_AUTOMATABLE_SOURCES);
}

const String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

const String PluginProcessor::getParameterName (int index)
{
    if (!(index % 2))
        return TRANS("Azim_") + String(index/2);
    else
        return TRANS("Elev_") + String((index-1)/2);
}

const String PluginProcessor::getParameterText(int index)
{
    if (!(index % 2))
        return String(panner_getSourceAzi_deg(hPan, index/2));
    else
        return String(panner_getSourceElev_deg(hPan, (index-1)/2));
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

	panner_init(hPan, sampleRate);
    AudioProcessor::setLatencySamples(panner_getProcessingDelay());
}

void PluginProcessor::releaseResources()
{
    isPlaying = false;
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
            for(int j=0; j<nNumInputs; j++){
                isPlaying = buffer.getRMSLevel(j, 0, nCurrentBlockSize)>1e-5f ? true : false;
                if(isPlaying)
                    break;
            }
            
            /* perform processing */
            panner_process(hPan, bufferInputs, bufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, isPlaying);
            
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
    XmlElement xml("PANNERPLUGINSETTINGS");
    for(int i=0; i<panner_getMaxNumSources(); i++){
        xml.setAttribute("SourceAziDeg" + String(i), panner_getSourceAzi_deg(hPan,i));
        xml.setAttribute("SourceElevDeg" + String(i), panner_getSourceElev_deg(hPan,i));
    }
    xml.setAttribute("nSources", panner_getNumSources(hPan));
    xml.setAttribute("DTT", panner_getDTT(hPan));
    xml.setAttribute("Spread", panner_getSpread(hPan));
    
    xml.setAttribute("JSONFilePath", lastDir.getFullPathName());
    
    for(int i=0; i<panner_getMaxNumLoudspeakers(); i++){
        xml.setAttribute("LoudspeakerAziDeg" + String(i), panner_getLoudspeakerAzi_deg(hPan,i));
        xml.setAttribute("LoudspeakerElevDeg" + String(i), panner_getLoudspeakerElev_deg(hPan,i));
    }
    xml.setAttribute("nLoudspeakers", panner_getNumLoudspeakers(hPan));

    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState != nullptr) {
        if (xmlState->hasTagName("PANNERPLUGINSETTINGS")) {
            for(int i=0; i<panner_getMaxNumSources(); i++){
                if(xmlState->hasAttribute("SourceAziDeg" + String(i)))
                    panner_setSourceAzi_deg(hPan, i, (float)xmlState->getDoubleAttribute("SourceAziDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceElevDeg" + String(i)))
                    panner_setSourceElev_deg(hPan, i, (float)xmlState->getDoubleAttribute("SourceElevDeg" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("nSources"))
                panner_setNumSources(hPan, xmlState->getIntAttribute("nSources", 1));
            if(xmlState->hasAttribute("DTT"))
                panner_setDTT(hPan, (float)xmlState->getDoubleAttribute("DTT", 0.5f));
            if(xmlState->hasAttribute("Spread"))
                panner_setSpread(hPan, (float)xmlState->getDoubleAttribute("Spread", 0.0f));
            
            if(xmlState->hasAttribute("JSONFilePath"))
                lastDir = xmlState->getStringAttribute("JSONFilePath", "");
            
            for(int i=0; i<panner_getMaxNumLoudspeakers(); i++){
                if(xmlState->hasAttribute("LoudspeakerAziDeg" + String(i)))
                    panner_setLoudspeakerAzi_deg(hPan, i, (float)xmlState->getDoubleAttribute("LoudspeakerAziDeg" + String(i),0.0f));
                if(xmlState->hasAttribute("LoudspeakerElevDeg" + String(i)))
                    panner_setLoudspeakerElev_deg(hPan, i, (float)xmlState->getDoubleAttribute("LoudspeakerElevDeg" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("nLoudspeakers"))
                panner_setNumLoudspeakers(hPan, xmlState->getIntAttribute("nLoudspeakers", 1));
            
            panner_refreshSettings(hPan);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

/* Adapted from the AllRADecoder by Daniel Rudrich, (c) 2017 (GPLv3 license) */
void PluginProcessor::saveConfigurationToFile (File destination, int srcOrLs)
{
    DynamicObject* jsonObj;
    char versionString[10];
    elements.removeAllChildren(nullptr);
    switch (srcOrLs){
        case 0:{
            for (int i=0; i<panner_getNumSources(hPan);i++) {
                elements.appendChild (ConfigurationHelper::
                                      createElement(panner_getSourceAzi_deg(hPan, i),
                                                    panner_getSourceElev_deg(hPan, i),
                                                    1.0f, i+1, false, 1.0f), nullptr);
            }
        }
        break;
        case 1:{
            for (int i=0; i<panner_getNumLoudspeakers(hPan);i++) {
                elements.appendChild (ConfigurationHelper::
                                     createElement(panner_getLoudspeakerAzi_deg(hPan, i),
                                                       panner_getLoudspeakerElev_deg(hPan, i),
                                                       1.0f, i+1, false, 1.0f), nullptr);
            }
        }
        break;
    }
    jsonObj = new DynamicObject();
    jsonObj->setProperty("Name", var("SPARTA Panner source/loudspeaker directions."));
    strcpy(versionString, "v");
    strcat(versionString, JucePlugin_VersionString);
    jsonObj->setProperty("Description", var("This configuration file was created with the SPARTA Panner " + String(versionString) + " plug-in. " + Time::getCurrentTime().toString(true, true)));
    jsonObj->setProperty ("GenericLayout", ConfigurationHelper::convertElementsToVar (elements, "Source/Loudspeaker Directions"));
    Result result2 = ConfigurationHelper::writeConfigurationToFile (destination, var (jsonObj));
}

/* Adapted from the AllRADecoder by Daniel Rudrich, (c) 2017 (GPLv3 license) */
void PluginProcessor::loadConfiguration (const File& configFile, int srcOrLs)
{
    int channelIDs[MAX_NUM_CHANNELS+1] = {0};
    int virtual_channelIDs[MAX_NUM_CHANNELS+1] = {0};
    elements.removeAllChildren(nullptr);
    Result result = ConfigurationHelper::parseFileForGenericLayout(configFile, elements, nullptr);
    if(result.wasOk()){
        int num_el, num_virtual_el, el_idx, j;
        num_el = num_virtual_el = el_idx = j = 0;
        /* get Channel IDs and find number of directions and virtual directions */
        for (ValueTree::Iterator it = elements.begin(); it != elements.end(); ++it){
            if ( !((*it).getProperty("Imaginary"))){
                num_el++; channelIDs[j] = (*it).getProperty("Channel");
            }
            else{
                virtual_channelIDs[num_virtual_el] = (*it).getProperty("Channel");
                num_virtual_el++; channelIDs[j] = -1;
            }
            j++;
        }
        /* remove virtual channels and shift the channel indices down */
        for(int i=0; i<num_virtual_el; i++)
            for(int j=0; j<num_el+num_virtual_el; j++)
                if(channelIDs[j] == -1)
                    for(int k=j; k<num_el+num_virtual_el; k++)
                        channelIDs[k] = channelIDs[k+1];
        
        /* then decriment the channel IDs to remove the gaps */
        for(int i=0; i<num_virtual_el; i++)
            for(int j=0; j<num_el+num_virtual_el; j++)
                if( channelIDs[j] > virtual_channelIDs[i]-i )
                    channelIDs[j]--;
        
        /* update with the new configuration  */
        switch(srcOrLs){
            case 0:{
                panner_setNumSources(hPan, num_el);
                for (ValueTree::Iterator it = elements.begin() ; it != elements.end(); ++it){
                    if ( !((*it).getProperty("Imaginary"))){
                        panner_setSourceAzi_deg(hPan, channelIDs[el_idx]-1, (*it).getProperty("Azimuth"));
                        panner_setSourceElev_deg(hPan, channelIDs[el_idx]-1, (*it).getProperty("Elevation"));
                        el_idx++;
                    }
                }
            }
            break;
            case 1:{
                panner_setNumLoudspeakers(hPan, num_el);
                for (ValueTree::Iterator it = elements.begin() ; it != elements.end(); ++it){
                    if ( !((*it).getProperty("Imaginary"))){
                        panner_setLoudspeakerAzi_deg(hPan, channelIDs[el_idx]-1, (*it).getProperty("Azimuth"));
                        panner_setLoudspeakerElev_deg(hPan, channelIDs[el_idx]-1, (*it).getProperty("Elevation"));
                        el_idx++;
                    }
                }
            }
            break;
        }
    }
}
