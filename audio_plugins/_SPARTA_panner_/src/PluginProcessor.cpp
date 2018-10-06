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
    
	panner_create(&hPan);
}

PluginProcessor::~PluginProcessor()
{
	panner_destroy(&hPan);
    
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
        delete[] ringBufferInputs[i];
    delete[] ringBufferInputs;
    
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
        delete[] ringBufferOutputs[i];
    delete[] ringBufferOutputs;
}

void PluginProcessor::setParameter (int index, float newValue)
{
    if (index % 2 || index == 0)
        panner_setSourceAzi_deg(hPan, index/2, (newValue - 0.5f)*360.0f);
    else
        panner_setSourceElev_deg(hPan, (index-1)/2, (newValue - 0.5f)*180.0f);
}

void PluginProcessor::setCurrentProgram (int index)
{
}

float PluginProcessor::getParameter (int index)
{
    if (index % 2 || index == 0)
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
    if (index % 2 || index == 0)
        return TRANS("Azim_") + String(index/2);
    else
        return TRANS("Elev_") + String((index-1)/2);
}

const String PluginProcessor::getParameterText(int index)
{
    if (index % 2 || index == 0)
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

	panner_init(hPan, sampleRate);
    
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
    
    playHead = getPlayHead();
    bool PlayHeadAvailable = playHead->getCurrentPosition(currentPosition);
    if (PlayHeadAvailable == true)
        isPlaying = currentPosition.isPlaying;
    else
        isPlaying = false;
    
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
            panner_process(hPan, ringBufferInputs, ringBufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, isPlaying);
            
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
    XmlElement xml("PANNERPLUGINSETTINGS");
    for(int i=0; i<panner_getMaxNumSources(); i++){
        xml.setAttribute("SourceAziDeg" + String(i), panner_getSourceAzi_deg(hPan,i));
        xml.setAttribute("SourceElevDeg" + String(i), panner_getSourceElev_deg(hPan,i));
    }
    xml.setAttribute("nSources", panner_getNumSources(hPan));
    xml.setAttribute("DTT", panner_getDTT(hPan));
    
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
                panner_setDTT(hPan, (float)xmlState->getDoubleAttribute("DTT", 1));
            
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

void PluginProcessor::saveConfigurationToFile (File destination, int srcOrLs)
{
    DynamicObject* jsonObj;
    char versionString[10];
    
    switch (srcOrLs){
        case 0: {
            sources.removeAllChildren(nullptr);
            for (int i=0; i<panner_getNumSources(hPan);i++)
            {
                sources.appendChild (ConfigurationHelper::
                                     createSource(panner_getSourceAzi_deg(hPan, i),
                                                  panner_getSourceElev_deg(hPan, i),
                                                  1.0f,
                                                  i,
                                                  false,
                                                  1.0f), nullptr);
            }
            jsonObj = new DynamicObject();
            jsonObj->setProperty("Name", var("SPARTA Panner source directions."));
            strcpy(versionString, "v");
            strcat(versionString, JucePlugin_VersionString);
            jsonObj->setProperty("Description", var("This configuration file was created with the SPARTA Panner " + String(versionString) + " plug-in. " + Time::getCurrentTime().toString(true, true)));
            jsonObj->setProperty ("SourceArrangement", ConfigurationHelper::convertSourcesToVar (sources, "Source Directions"));
            Result result = ConfigurationHelper::writeConfigurationToFile (destination, var (jsonObj));
            assert(result.wasOk());
            break;
        }
            
        case 1: {
            loudspeakers.removeAllChildren(nullptr);
            for (int i=0; i<panner_getNumLoudspeakers(hPan);i++)
            {
                loudspeakers.appendChild (ConfigurationHelper::
                                     createLoudspeaker(panner_getLoudspeakerAzi_deg(hPan, i),
                                                       panner_getLoudspeakerElev_deg(hPan, i),
                                                       1.0f,
                                                       i,
                                                       false,
                                                       1.0f), nullptr);
            }
            jsonObj = new DynamicObject();
            jsonObj->setProperty("Name", var("SPARTA Panner loudspeaker directions."));
            strcpy(versionString, "v");
            strcat(versionString, JucePlugin_VersionString);
            jsonObj->setProperty("Description", var("This configuration file was created with the SPARTA Panner " + String(versionString) + " plug-in. " + Time::getCurrentTime().toString(true, true)));
            jsonObj->setProperty ("LoudspeakerLayout", ConfigurationHelper::convertLoudspeakersToVar (loudspeakers, "Loudspeaker Directions"));
            Result result2 = ConfigurationHelper::writeConfigurationToFile (destination, var (jsonObj));
            assert(result2.wasOk());
            break;
        }
    }
}

void PluginProcessor::loadConfiguration (const File& configFile, int srcOrLs)
{
    switch (srcOrLs){
        case 0: {
            sources.removeAllChildren(nullptr);
            Result result = ConfigurationHelper::parseFileForSourceArrangement (configFile, sources, nullptr);
            if(result.wasOk()){
                int num_srcs = 0;
                int src_idx = 0;
                for (ValueTree::Iterator it = sources.begin() ; it != sources.end(); ++it)
                    if ( !((*it).getProperty("Imaginary")))
                        num_srcs++;
                panner_setNumSources(hPan, num_srcs);
                for (ValueTree::Iterator it = sources.begin() ; it != sources.end(); ++it){
                    if ( !((*it).getProperty("Imaginary"))){
                        panner_setSourceAzi_deg(hPan, src_idx, (*it).getProperty("Azimuth"));
                        panner_setSourceElev_deg(hPan, src_idx, (*it).getProperty("Elevation"));
                        src_idx++;
                    }
                }
            }
        }
           
        case 1: {
            loudspeakers.removeAllChildren(nullptr);
            Result result = ConfigurationHelper::parseFileForLoudspeakerLayout (configFile, loudspeakers, nullptr);
            if(result.wasOk()){
                int num_ls = 0;
                int ls_idx = 0;
                for (ValueTree::Iterator it = loudspeakers.begin() ; it != loudspeakers.end(); ++it)
                    if ( !((*it).getProperty("Imaginary")))
                        num_ls++;
                panner_setNumLoudspeakers(hPan, num_ls);
                for (ValueTree::Iterator it = loudspeakers.begin() ; it != loudspeakers.end(); ++it){
                    if ( !((*it).getProperty("Imaginary"))){
                        panner_setLoudspeakerAzi_deg(hPan, ls_idx, (*it).getProperty("Azimuth"));
                        panner_setLoudspeakerElev_deg(hPan, ls_idx, (*it).getProperty("Elevation"));
                        ls_idx++;
                    }
                }
            }
        }
    }
    panner_refreshSettings(hPan);
}
