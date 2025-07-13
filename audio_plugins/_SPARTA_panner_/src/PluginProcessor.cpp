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

static int getMaxNumChannelsForFormat(AudioProcessor::WrapperType format) {
    switch(format){
        case juce::AudioProcessor::wrapperType_VST:  /* fall through */
        case juce::AudioProcessor::wrapperType_VST3: /* fall through */
        case juce::AudioProcessor::wrapperType_AAX:
            return 64;
        default:
            return MAX_NUM_CHANNELS;
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("yaw", "Yaw", juce::NormalisableRange<float>(-180.0f, 180.0f, 0.1f), 0.0f,
                                                                 AudioParameterFloatAttributes().withLabel(juce::String::fromUTF8(u8"\u00B0"))));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("pitch", "Pitch", juce::NormalisableRange<float>(-180.0f, 180.0f, 0.1f), 0.0f,
                                                                 AudioParameterFloatAttributes().withLabel(juce::String::fromUTF8(u8"\u00B0"))));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("roll", "Roll", juce::NormalisableRange<float>(-180.0f, 180.0f, 0.1f), 0.0f,
                                                                 AudioParameterFloatAttributes().withLabel(juce::String::fromUTF8(u8"\u00B0"))));
    params.push_back(std::make_unique<juce::AudioParameterBool>("flipYaw", "FlipYaw", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("flipPitch", "FlipPitch", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("flipRoll", "FlipRoll", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("spread", "Spread", juce::NormalisableRange<float>(PANNER_SPREAD_MIN_VALUE, PANNER_SPREAD_MAX_VALUE, 0.01f), 0.0f,
                                                                 AudioParameterFloatAttributes().withAutomatable(false).withLabel(juce::String::fromUTF8(u8"\u00B0"))));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("roomCoeff", "RoomCoeff", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f,
                                                                 AudioParameterFloatAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numInputs", "NumInputs", 1, MAX_NUM_INPUTS, 1, AudioParameterIntAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numOutputs", "NumOutputs", 2, MAX_NUM_OUTPUTS, 1, AudioParameterIntAttributes().withAutomatable(false)));
    for(int i=0; i<MAX_NUM_INPUTS; i++){
        params.push_back(std::make_unique<juce::AudioParameterFloat>("srcAzim" + juce::String(i), "SrcAzim_" + juce::String(i+1), juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withLabel(juce::String::fromUTF8(u8"\u00B0"))));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("srcElev" + juce::String(i), "SrcElev_" + juce::String(i+1), juce::NormalisableRange<float>(-90.0f, 90.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withLabel(juce::String::fromUTF8(u8"\u00B0"))));
    }
    for(int i=0; i<MAX_NUM_OUTPUTS; i++){
        params.push_back(std::make_unique<juce::AudioParameterFloat>("lsAzim" + juce::String(i), "LsAzim_" + juce::String(i+1), juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withAutomatable(false).withLabel(juce::String::fromUTF8(u8"\u00B0"))));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("lsElev" + juce::String(i), "LsElev_" + juce::String(i+1), juce::NormalisableRange<float>(-90.0f, 90.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withAutomatable(false).withLabel(juce::String::fromUTF8(u8"\u00B0"))));
    }
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if(parameterID == "yaw"){
        panner_setYaw(hPan, newValue);
    }
    else if(parameterID == "pitch"){
        panner_setPitch(hPan, newValue);
    }
    else if(parameterID == "roll"){
        panner_setRoll(hPan, newValue);
    }
    else if(parameterID == "flipYaw"){
        panner_setFlipYaw(hPan, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "flipPitch"){
        panner_setFlipPitch(hPan, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "flipRoll"){
        panner_setFlipRoll(hPan, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "spread"){
        panner_setSpread(hPan, newValue);
    }
    else if(parameterID == "roomCoeff"){
        panner_setDTT(hPan, newValue);
    }
    else if(parameterID == "numInputs"){
        panner_setNumSources(hPan, static_cast<int>(newValue));
    }
    else if(parameterID == "numOutputs"){
        panner_setNumLoudspeakers(hPan, static_cast<int>(newValue));
    }
    for(int i=0; i<MAX_NUM_INPUTS; i++){
        if(parameterID == "srcAzim" + juce::String(i)){
            panner_setSourceAzi_deg(hPan, i, newValue);
            setRefreshWindow(true);
            break;
        }
        else if(parameterID == "srcElev" + juce::String(i)){
            panner_setSourceElev_deg(hPan, i, newValue);
            setRefreshWindow(true);
            break;
        }
    }
    for(int i=0; i<MAX_NUM_OUTPUTS; i++){
        if(parameterID == "lsAzim" + juce::String(i)){
            panner_setLoudspeakerAzi_deg(hPan, i, newValue);
            setRefreshWindow(true);
            break;
        }
        else if(parameterID == "lsElev" + juce::String(i)){
            panner_setLoudspeakerElev_deg(hPan, i, newValue);
            setRefreshWindow(true);
            break;
        }
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("yaw", panner_getYaw(hPan));
    setParameterValue("pitch", panner_getPitch(hPan));
    setParameterValue("roll", panner_getRoll(hPan));
    setParameterValue("flipYaw", panner_getFlipYaw(hPan));
    setParameterValue("flipPitch", panner_getFlipPitch(hPan));
    setParameterValue("flipRoll", panner_getFlipRoll(hPan));
    setParameterValue("spread", panner_getSpread(hPan));
    setParameterValue("roomCoeff", panner_getDTT(hPan));
    setParameterValue("numInputs", panner_getNumSources(hPan));
    for(int i=0; i<MAX_NUM_INPUTS; i++){
        setParameterValue("srcAzim" + juce::String(i), panner_getSourceAzi_deg(hPan, i));
        setParameterValue("srcElev" + juce::String(i), panner_getSourceElev_deg(hPan, i));
    }
    for(int i=0; i<MAX_NUM_OUTPUTS; i++){
        setParameterValue("lsAzim" + juce::String(i), panner_getLoudspeakerAzi_deg(hPan, i));
        setParameterValue("lsElev" + juce::String(i), panner_getLoudspeakerElev_deg(hPan, i));
    }
}

void PluginProcessor::setInternalStateUsingParameterValues()
{
    panner_setYaw(hPan, getParameterFloat("yaw"));
    panner_setPitch(hPan, getParameterFloat("pitch"));
    panner_setRoll(hPan, getParameterFloat("roll"));
    panner_setFlipYaw(hPan, getParameterBool("flipYaw"));
    panner_setFlipPitch(hPan, getParameterBool("flipPitch"));
    panner_setFlipRoll(hPan, getParameterBool("flipRoll"));
    panner_setSpread(hPan, getParameterFloat("spread"));
    panner_setDTT(hPan, getParameterFloat("roomCoeff"));
    panner_setNumSources(hPan, getParameterInt("numInputs"));
    for(int i=0; i<MAX_NUM_INPUTS; i++){
        panner_setSourceAzi_deg(hPan, i, getParameterFloat("srcAzim" + juce::String(i)));
        panner_setSourceElev_deg(hPan, i, getParameterFloat("srcElev" + juce::String(i)));
    }
    for(int i=0; i<MAX_NUM_OUTPUTS; i++){
        panner_setLoudspeakerAzi_deg(hPan, i, getParameterFloat("lsAzim" + juce::String(i)));
        panner_setLoudspeakerElev_deg(hPan, i, getParameterFloat("lsElev" + juce::String(i)));
    }
}

PluginProcessor::PluginProcessor() : 
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	panner_create(&hPan);
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();
    
    refreshWindow = true;
    startTimer(TIMER_PROCESSING_RELATED, 80); 
}

PluginProcessor::~PluginProcessor()
{
	panner_destroy(&hPan);
}

void PluginProcessor::setCurrentProgram (int /*index*/)
{
}

const String PluginProcessor::getName() const
{
    return JucePlugin_Name;
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
    ScopedNoDenormals noDenormals;
    
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

bool PluginProcessor::hasEditor() const
{
    return true; 
}

AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (*this);
}

void PluginProcessor::getStateInformation (MemoryBlock& destData)
{
    juce::ValueTree state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xmlState(state.createXml());
    xmlState->setTagName("PANNERPLUGINSETTINGS");
    xmlState->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10601
    
    /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
  
    /* Other */
    xmlState->setAttribute("JSONFilePath", lastDir.getFullPathName());
    
    /* Save */
    copyXmlToBinary(*xmlState, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("PANNERPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10601
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
            
            setParameterValuesUsingInternalState();
        }
        else if(xmlState->getIntAttribute("VersionCode")>=0x10601){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* Other */
            if(xmlState->hasAttribute("JSONFilePath"))
                lastDir = xmlState->getStringAttribute("JSONFilePath", "");
            
            /* Many hosts will also trigger parameterChanged() for all parameters after calling setStateInformation() */
            /* However, some hosts do not. Therefore, it is better to ensure that the internal state is always up-to-date by calling: */
            setInternalStateUsingParameterValues();
        }

        panner_refreshSettings(hPan);
    }
}

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
                /* Making sure that the internal coordinates above the current numSources (i.e. numSources+1:maxNumSources) are up to date in "parameters" too */
                /* This is because JUCE won't invoke parameterChanged() if the values are the same in the parameter list */
                for(int i=panner_getNumSources(hPan); i<num_el; i++){
                    setParameterValue("srcAzim" + juce::String(i), panner_getSourceAzi_deg(hPan, i));
                    setParameterValue("srcElev" + juce::String(i), panner_getSourceElev_deg(hPan, i));
                }
                
                /* update with the new configuration  */
                setParameterValue("numInputs", num_el);
                for (ValueTree::Iterator it = elements.begin() ; it != elements.end(); ++it){
                    if ( !((*it).getProperty("Imaginary"))){
                        float azimValue = (float)(*it).getProperty("Azimuth");
                        float elevValue = (float)(*it).getProperty("Elevation");
                        setParameterValue("srcAzim" + juce::String(channelIDs[el_idx]-1), azimValue);
                        setParameterValue("srcElev" + juce::String(channelIDs[el_idx]-1), elevValue);
                        el_idx++;
                    }
                }
            }
            break;
            case 1:{
                /* Making sure that the internal coordinates above the current numLoudspeakers (i.e. numLoudspeakers+1:maxNumLoudspeakers) are up to date in "parameters" too */
                /* This is because JUCE won't invoke parameterChanged() if the values are the same in the parameter list */
                for(int i=panner_getNumLoudspeakers(hPan); i<num_el; i++){
                    setParameterValue("lsAzim" + juce::String(i), panner_getLoudspeakerAzi_deg(hPan, i));
                    setParameterValue("lsElev" + juce::String(i), panner_getLoudspeakerElev_deg(hPan, i));
                }
                
                /* update with the new configuration  */
                setParameterValue("numOutputs", num_el);
                for (ValueTree::Iterator it = elements.begin() ; it != elements.end(); ++it){
                    if ( !((*it).getProperty("Imaginary"))){
                        float azimValue = (float)(*it).getProperty("Azimuth");
                        float elevValue = (float)(*it).getProperty("Elevation");
                        setParameterValue("lsAzim" + juce::String(channelIDs[el_idx]-1), azimValue);
                        setParameterValue("lsElev" + juce::String(channelIDs[el_idx]-1), elevValue);
                        el_idx++;
                    }
                }
            }
            break;
        }
    }
}
