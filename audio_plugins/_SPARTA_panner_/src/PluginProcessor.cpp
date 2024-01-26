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
	panner_create(&hPan);
    refreshWindow = true;
    startTimer(TIMER_PROCESSING_RELATED, 80); 
}

PluginProcessor::~PluginProcessor()
{
	panner_destroy(&hPan);
}

void PluginProcessor::setParameter (int index, float newValue)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_yaw:        panner_setYaw(hPan, (newValue-0.5f)*360.0f ); break;
            case k_pitch:      panner_setPitch(hPan, (newValue - 0.5f)*180.0f); break;
            case k_roll:       panner_setRoll(hPan, (newValue - 0.5f)*180.0f); break;
            case k_flipYaw:    panner_setFlipYaw(hPan, (int)(newValue + 0.5f));  break;
            case k_flipPitch:  panner_setFlipPitch(hPan, (int)(newValue + 0.5f)); break;
            case k_flipRoll:   panner_setFlipRoll(hPan, (int)(newValue + 0.5f)); break;
            case k_spread:     panner_setSpread(hPan, newValue*(PANNER_SPREAD_MAX_VALUE-PANNER_SPREAD_MIN_VALUE)+PANNER_SPREAD_MIN_VALUE); break;
            case k_roomCoeff:  panner_setDTT(hPan, newValue); break;
            case k_numInputs:  panner_setNumSources(hPan, (int)(newValue*(float)(MAX_NUM_INPUTS)+0.5)); break;
            case k_numOutputs: panner_setNumLoudspeakers(hPan, (int)(newValue*(float)(MAX_NUM_OUTPUTS)+0.5)); break;
        }
    }
    /* source direction parameters */
    else if(index<2*MAX_NUM_INPUTS+k_NumOfParameters){
        index-=k_NumOfParameters;
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
    /* loudspeaker direction parameters */
    else{
        index -= (k_NumOfParameters+2*MAX_NUM_INPUTS);
        float newValueScaled;
        if (!(index % 2)){
            newValueScaled = (newValue - 0.5f)*360.0f;
            if (newValueScaled != panner_getLoudspeakerAzi_deg(hPan, index/2)){
                panner_setLoudspeakerAzi_deg(hPan, index/2, newValueScaled);
                refreshWindow = true;
            }
        }
        else{
            newValueScaled = (newValue - 0.5f)*180.0f;
            if (newValueScaled != panner_getLoudspeakerElev_deg(hPan, index/2)){
                panner_setLoudspeakerElev_deg(hPan, index/2, newValueScaled);
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
            case k_yaw:        return (panner_getYaw(hPan)/360.0f) + 0.5f;
            case k_pitch:      return (panner_getPitch(hPan)/180.0f) + 0.5f;
            case k_roll:       return (panner_getRoll(hPan)/180.0f) + 0.5f;
            case k_flipYaw:    return (float)panner_getFlipYaw(hPan);
            case k_flipPitch:  return (float)panner_getFlipPitch(hPan);
            case k_flipRoll:   return (float)panner_getFlipRoll(hPan);
            case k_spread:     return (panner_getSpread(hPan)-PANNER_SPREAD_MIN_VALUE)/(PANNER_SPREAD_MAX_VALUE-PANNER_SPREAD_MIN_VALUE);
            case k_roomCoeff:  return (float)panner_getDTT(hPan);
            case k_numInputs:  return (float)(panner_getNumSources(hPan))/(float)(MAX_NUM_INPUTS);
            case k_numOutputs: return (float)(panner_getNumLoudspeakers(hPan))/(float)(MAX_NUM_OUTPUTS);
            default: return 0.0f;
        }
    }
    /* source direction parameters */
    else if(index<2*MAX_NUM_INPUTS+k_NumOfParameters){
        index-=k_NumOfParameters;
        if (!(index % 2))
            return (panner_getSourceAzi_deg(hPan, index/2)/360.0f) + 0.5f;
        else
            return (panner_getSourceElev_deg(hPan, (index-1)/2)/180.0f) + 0.5f;
    }
    /* loudspeaker direction parameters */
    else{
        index -= (k_NumOfParameters+2*MAX_NUM_INPUTS);
        if (!(index % 2))
            return (panner_getLoudspeakerAzi_deg(hPan, index/2)/360.0f) + 0.5f;
        else
            return (panner_getLoudspeakerElev_deg(hPan, (index-1)/2)/180.0f) + 0.5f;
    }
}

int PluginProcessor::getNumParameters()
{
	return k_NumOfParameters + 2*MAX_NUM_INPUTS + 2*MAX_NUM_OUTPUTS;
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
            case k_yaw:        return "yaw";
            case k_pitch:      return "pitch";
            case k_roll:       return "roll";
            case k_flipYaw:    return "flip_yaw";
            case k_flipPitch:  return "flip_pitch";
            case k_flipRoll:   return "flip_roll";
            case k_spread:     return "spread";
            case k_roomCoeff:  return "roomCoeff";
            case k_numInputs:  return "num_sources";
            case k_numOutputs: return "num_loudspeakers";
            default: return "NULL";
        }
    }
    /* source direction parameters */
    else if(index<2*MAX_NUM_INPUTS+k_NumOfParameters){
        index-=k_NumOfParameters;
        if (!(index % 2))
            return TRANS("SrcAzim_") + String(index/2);
        else
            return TRANS("SrcElev_") + String((index-1)/2);
    }
    /* loudspeaker direction parameters */
    else{
        index -= (k_NumOfParameters+2*MAX_NUM_INPUTS);
        if (!(index % 2))
            return TRANS("LsAzim_") + String(index/2);
        else
            return TRANS("LsElev_") + String((index-1)/2);
    }
}

const String PluginProcessor::getParameterText(int index)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_yaw:        return String(panner_getYaw(hPan));
            case k_pitch:      return String(panner_getPitch(hPan));
            case k_roll:       return String(panner_getRoll(hPan));
            case k_flipYaw:    return !panner_getFlipYaw(hPan) ? "No-Flip" : "Flip";
            case k_flipPitch:  return !panner_getFlipPitch(hPan) ? "No-Flip" : "Flip";
            case k_flipRoll:   return !panner_getFlipRoll(hPan) ? "No-Flip" : "Flip";
            case k_spread:     return String(panner_getSpread(hPan)) + " degrees";
            case k_roomCoeff:  return String(panner_getDTT(hPan));
            case k_numInputs:  return String(panner_getNumSources(hPan));
            case k_numOutputs: return String(panner_getNumLoudspeakers(hPan));
            default: return "NULL";
        }
    }
    /* source direction parameters */
    else if(index<2*MAX_NUM_INPUTS+k_NumOfParameters){
        index -= k_NumOfParameters;
        if (!(index % 2))
            return String(panner_getSourceAzi_deg(hPan, index/2));
        else
            return String(panner_getSourceElev_deg(hPan, (index-1)/2));
    }
    /* loudspeaker direction parameters */
    else{
        index -= (k_NumOfParameters+2*MAX_NUM_INPUTS);
        if (!(index % 2))
            return String(panner_getLoudspeakerAzi_deg(hPan, index/2));
        else
            return String(panner_getLoudspeakerElev_deg(hPan, (index-1)/2));
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
    nNumInputs =  jmin(getTotalNumInputChannels(), 256);
    nNumOutputs = jmin(getTotalNumOutputChannels(), 256);
    nSampleRate = (int)(sampleRate + 0.5);
    isPlaying = false;

	panner_init(hPan, nSampleRate);
    AudioProcessor::setLatencySamples(panner_getProcessingDelay());
}

void PluginProcessor::releaseResources()
{
    isPlaying = false;
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels(), 256);
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels(), 256);
    float* const* bufferData = buffer.getArrayOfWritePointers();
    float* pFrameData[256];
    int frameSize = panner_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
       for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
           for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
               pFrameData[ch] = &bufferData[ch][frame*frameSize];

           /* perform processing */
           panner_process(hPan, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
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
    xml.setAttribute("YAW", panner_getYaw(hPan));
    xml.setAttribute("PITCH", panner_getPitch(hPan));
    xml.setAttribute("ROLL", panner_getRoll(hPan));
    xml.setAttribute("FLIP_YAW", panner_getFlipYaw(hPan));
    xml.setAttribute("FLIP_PITCH", panner_getFlipPitch(hPan));
    xml.setAttribute("FLIP_ROLL", panner_getFlipRoll(hPan));
    
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
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
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
            if(xmlState->hasAttribute("YAW"))
                panner_setYaw(hPan, (float)xmlState->getDoubleAttribute("YAW", 0.0f));
            if(xmlState->hasAttribute("PITCH"))
                panner_setPitch(hPan, (float)xmlState->getDoubleAttribute("PITCH", 0.0f));
            if(xmlState->hasAttribute("ROLL"))
                panner_setRoll(hPan, (float)xmlState->getDoubleAttribute("ROLL", 0.0f));
            if(xmlState->hasAttribute("FLIP_YAW"))
                panner_setFlipYaw(hPan, xmlState->getIntAttribute("FLIP_YAW", 0));
            if(xmlState->hasAttribute("FLIP_PITCH"))
                panner_setFlipPitch(hPan, xmlState->getIntAttribute("FLIP_PITCH", 0));
            if(xmlState->hasAttribute("FLIP_ROLL"))
                panner_setFlipRoll(hPan, xmlState->getIntAttribute("FLIP_ROLL", 0));
            
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
    int channelIDs[MAX(MAX_NUM_INPUTS, MAX_NUM_OUTPUTS)+1] = {0};
    int virtual_channelIDs[MAX(MAX_NUM_INPUTS, MAX_NUM_OUTPUTS)+1] = {0};
    elements.removeAllChildren(nullptr);
    Result result = ConfigurationHelper::parseFileForGenericLayout(configFile, elements, nullptr);
    if(result.wasOk()){
        int num_el, num_virtual_el, el_idx, jj;
        num_el = num_virtual_el = el_idx = jj = 0;
        /* get Channel IDs and find number of directions and virtual directions */
        for (ValueTree::Iterator it = elements.begin(); it != elements.end(); ++it){
            if ( !((*it).getProperty("Imaginary"))){
                num_el++; channelIDs[jj] = (*it).getProperty("Channel");
            }
            else{
                virtual_channelIDs[num_virtual_el] = (*it).getProperty("Channel");
                num_virtual_el++; channelIDs[jj] = -1;
            }
            jj++;
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
