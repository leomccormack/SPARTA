/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2018 - Michael McCrea, Leo McCormack.
 
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
    
    params.push_back(std::make_unique<juce::AudioParameterBool>("enableRotation", "EnableRotation", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("useRollPitchYaw", "UseRollPitchYaw", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("yaw", "Yaw", juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("pitch", "Pitch", juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("roll", "Roll", juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("flipYaw", "FlipYaw", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("flipPitch", "FlipPitch", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>("flipRoll", "FlipRoll", false));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numSources", "NumSources", 1, MAX_NUM_INPUTS, 1, AudioParameterIntAttributes().withAutomatable(false)));
    for(int i=0; i<MAX_NUM_INPUTS; i++){
        params.push_back(std::make_unique<juce::AudioParameterFloat>("azim" + juce::String(i), "Azim_" + juce::String(i+1), juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("elev" + juce::String(i), "Elev_" + juce::String(i+1), juce::NormalisableRange<float>(-90.0f, 90.0f, 0.01f), 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("dist" + juce::String(i), "Dist_" + juce::String(i+1), juce::NormalisableRange<float>(0.15f, 3.25f, 0.01f), 0.0f)); // ranges based on internal constants found in binauraliser_nf.c
    }
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "enableRotation"){
        binauraliser_setEnableRotation(hBin, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "useRollPitchYaw"){
        binauraliser_setRPYflag(hBin, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "yaw"){
        binauraliser_setYaw(hBin, newValue);
    }
    else if(parameterID == "pitch"){
        binauraliser_setPitch(hBin, newValue);
    }
    else if(parameterID == "roll"){
        binauraliser_setRoll(hBin, newValue);
    }
    else if(parameterID == "flipYaw"){
        binauraliser_setFlipYaw(hBin, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "flipPitch"){
        binauraliser_setFlipPitch(hBin, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "flipRoll"){
        binauraliser_setFlipRoll(hBin, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "numSources"){
        binauraliser_setNumSources(hBin, static_cast<int>(newValue));
    }
    for(int i=0; i<MAX_NUM_INPUTS; i++){
        if(parameterID == "azim" + juce::String(i)){
            binauraliser_setSourceAzi_deg(hBin, i, newValue);
            setRefreshWindow(true);
            break;
        }
        else if(parameterID == "elev" + juce::String(i)){
            binauraliser_setSourceElev_deg(hBin, i, newValue);
            setRefreshWindow(true);
            break;
        }
        else if(parameterID == "dist" + juce::String(i)){
            binauraliserNF_setSourceDist_m(hBin, i, newValue);
            setRefreshWindow(true);
            break;
        }
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("enableRotation", binauraliser_getEnableRotation(hBin));
    setParameterValue("useRollPitchYaw", binauraliser_getRPYflag(hBin));
    setParameterValue("yaw", binauraliser_getYaw(hBin));
    setParameterValue("pitch", binauraliser_getPitch(hBin));
    setParameterValue("roll", binauraliser_getRoll(hBin));
    setParameterValue("flipYaw", binauraliser_getFlipYaw(hBin));
    setParameterValue("flipPitch", binauraliser_getFlipPitch(hBin));
    setParameterValue("flipRoll", binauraliser_getFlipRoll(hBin));
    setParameterValue("numSources", binauraliser_getNumSources(hBin));
    for(int i=0; i<MAX_NUM_INPUTS; i++){
        setParameterValue("azim" + juce::String(i), binauraliser_getSourceAzi_deg(hBin, i));
        setParameterValue("elev" + juce::String(i), binauraliser_getSourceElev_deg(hBin, i));
        setParameterValue("dist" + juce::String(i), binauraliserNF_getSourceDist_m(hBin, i));
    }
}

PluginProcessor::PluginProcessor() :
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(2), true)),
    ParameterManager(*this, createParameterLayout())
{
	binauraliserNF_create(&hBin);
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();
    
    /* specify here on which UDP port number to receive incoming OSC messages */
    osc_port_ID = DEFAULT_OSC_PORT;
    osc_connected = osc.connect(osc_port_ID);
    /* tell the component to listen for OSC messages */
    osc.addListener(this);
    refreshWindow = true;
    startTimer(TIMER_PROCESSING_RELATED, 80);
    /* Far field distance threshold plus head room to firmly clear it with UI sliders. */
    nfThresh = binauraliserNF_getNearfieldLimit_m(hBin);
    ffThresh = binauraliserNF_getFarfieldThresh_m(hBin);
    ffHeadroom = binauraliserNF_getFarfieldHeadroom(hBin);
    upperDistRange = ffThresh * ffHeadroom;
}

PluginProcessor::~PluginProcessor()
{
    osc.disconnect();
    osc.removeListener(this);
    
	binauraliserNF_destroy(&hBin);
}

void PluginProcessor::oscMessageReceived(const OSCMessage& message)
{
    /* if rotation angles are sent as an array \ypr[3] */
    if (message.size() == 3 && message.getAddressPattern().toString().compare("/ypr")==0) {
        if (message[0].isFloat32()){
            setParameterValue("yaw", message[0].getFloat32());
        }
        if (message[1].isFloat32()){
            setParameterValue("pitch", message[1].getFloat32());
        }
        if (message[2].isFloat32()){
            setParameterValue("roll", message[2].getFloat32());
        }
        return;
    }
    
    /* if rotation angles are sent individually: */
    if(message.getAddressPattern().toString().compare("/yaw")==0){
        setParameterValue("yaw", message[0].getFloat32());
    }
    else if(message.getAddressPattern().toString().compare("/pitch")==0){
        setParameterValue("pitch", message[0].getFloat32());
    }
    else if(message.getAddressPattern().toString().compare("/roll")==0){
        setParameterValue("roll", message[0].getFloat32());
    }
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
    
	binauraliserNF_init(hBin, nSampleRate);
    AudioProcessor::setLatencySamples(binauraliser_getProcessingDelay());
}

void PluginProcessor::releaseResources()
{
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels(), 256);
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels(), 256);
    float* const* bufferData = buffer.getArrayOfWritePointers();
    float* pFrameData[256];
    int frameSize = binauraliser_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            binauraliserNF_process(hBin, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
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
    xmlState->setTagName("BINAURALISERNFPLUGINSETTINGS");
    xmlState->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x201
    
    /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
    if(!binauraliser_getUseDefaultHRIRsflag(hBin))
        xmlState->setAttribute("SofaFilePath", String(binauraliser_getSofaFilePath(hBin)));
    xmlState->setAttribute("INTERP_MODE", binauraliser_getInterpMode(hBin));
    xmlState->setAttribute("HRIRdiffEQ", binauraliser_getEnableHRIRsDiffuseEQ(hBin));
        
    /* Other */
    xmlState->setAttribute("JSONFilePath", lastDir.getFullPathName());
    xmlState->setAttribute("OSC_PORT", osc_port_ID);
    
    /* Save */
    copyXmlToBinary(*xmlState, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("BINAURALISERNFPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x201
            for(int i=0; i<binauraliser_getMaxNumSources(); i++){
                if(xmlState->hasAttribute("SourceAziDeg" + String(i)))
                    binauraliser_setSourceAzi_deg(hBin, i, (float)xmlState->getDoubleAttribute("SourceAziDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceElevDeg" + String(i)))
                    binauraliser_setSourceElev_deg(hBin, i, (float)xmlState->getDoubleAttribute("SourceElevDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceDistMeter" + String(i)))
                    binauraliserNF_setSourceDist_m(hBin, i, (float)xmlState->getDoubleAttribute("SourceDistMeter" + String(i), upperDistRange)); // default source distance is far field (no near field filtering)
            }
            if(xmlState->hasAttribute("nSources"))
                binauraliser_setNumSources(hBin, xmlState->getIntAttribute("nSources", 1));
            
            if(xmlState->hasAttribute("SofaFilePath")){
                String directory = xmlState->getStringAttribute("SofaFilePath", "no_file");
                const char* new_cstring = (const char*)directory.toUTF8();
                binauraliser_setSofaFilePath(hBin, new_cstring);
            }
            
            if(xmlState->hasAttribute("JSONFilePath"))
                lastDir = xmlState->getStringAttribute("JSONFilePath", "");
            
            if(xmlState->hasAttribute("INTERP_MODE"))
                binauraliser_setInterpMode(hBin, xmlState->getIntAttribute("INTERP_MODE", 1));
            if(xmlState->hasAttribute("ENABLE_ROT"))
                binauraliser_setEnableRotation(hBin, xmlState->getIntAttribute("ENABLE_ROT", 0));
            if(xmlState->hasAttribute("YAW"))
                binauraliser_setYaw(hBin, (float)xmlState->getDoubleAttribute("YAW", 0.0f));
            if(xmlState->hasAttribute("PITCH"))
                binauraliser_setPitch(hBin, (float)xmlState->getDoubleAttribute("PITCH", 0.0f));
            if(xmlState->hasAttribute("ROLL"))
                binauraliser_setRoll(hBin, (float)xmlState->getDoubleAttribute("ROLL", 0.0f));
            if(xmlState->hasAttribute("FLIP_YAW"))
                binauraliser_setFlipYaw(hBin, xmlState->getIntAttribute("FLIP_YAW", 0));
            if(xmlState->hasAttribute("FLIP_PITCH"))
                binauraliser_setFlipPitch(hBin, xmlState->getIntAttribute("FLIP_PITCH", 0));
            if(xmlState->hasAttribute("FLIP_ROLL"))
                binauraliser_setFlipRoll(hBin, xmlState->getIntAttribute("FLIP_ROLL", 0));
            if(xmlState->hasAttribute("RPY_FLAG"))
                binauraliser_setRPYflag(hBin, xmlState->getIntAttribute("RPY_FLAG", 0));
            if(xmlState->hasAttribute("HRIRdiffEQ"))
                binauraliser_setEnableHRIRsDiffuseEQ(hBin, xmlState->getIntAttribute("HRIRdiffEQ", 1));
            
            if(xmlState->hasAttribute("OSC_PORT")){
                osc_port_ID = xmlState->getIntAttribute("OSC_PORT", DEFAULT_OSC_PORT);
                osc.connect(osc_port_ID);
            }
            
            setParameterValuesUsingInternalState();
        }
        else if(xmlState->getIntAttribute("VersionCode")>=0x201){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
            if(xmlState->hasAttribute("SofaFilePath")){
                String directory = xmlState->getStringAttribute("SofaFilePath", "no_file");
                const char* new_cstring = (const char*)directory.toUTF8();
                binauraliser_setSofaFilePath(hBin, new_cstring);
            }
            
            if(xmlState->hasAttribute("INTERP_MODE"))
                binauraliser_setInterpMode(hBin, xmlState->getIntAttribute("INTERP_MODE", 1));
            if(xmlState->hasAttribute("HRIRdiffEQ"))
                binauraliser_setEnableHRIRsDiffuseEQ(hBin, xmlState->getIntAttribute("HRIRdiffEQ", 1));
            
            /* Other */
            if(xmlState->hasAttribute("JSONFilePath"))
                lastDir = xmlState->getStringAttribute("JSONFilePath", "");
            if(xmlState->hasAttribute("OSC_PORT")){
                osc_port_ID = xmlState->getIntAttribute("OSC_PORT", DEFAULT_OSC_PORT);
                osc.connect(osc_port_ID);
            }
        }

        binauraliser_refreshSettings(hBin);
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

/* Adapted from the AllRADecoder by Daniel Rudrich, (c) 2017 (GPLv3 license) */
void PluginProcessor::saveConfigurationToFile (File destination)
{
    sources.removeAllChildren(nullptr);
    for (int i=0; i<binauraliser_getNumSources(hBin);i++)
    {
        sources.appendChild (ConfigurationHelper::
                             createElement(binauraliser_getSourceAzi_deg(hBin, i),
                                           binauraliser_getSourceElev_deg(hBin, i),
                                           binauraliserNF_getSourceDist_m(hBin, i),
                                           i+1, false, 1.0f), nullptr);
    }
    DynamicObject* jsonObj = new DynamicObject();
    jsonObj->setProperty("Name", var("SPARTA Binauraliser source directions and distances."));
    char versionString[10];
    strcpy(versionString, "v");
    strcat(versionString, JucePlugin_VersionString);
    jsonObj->setProperty("Description", var("This configuration file was created with the SPARTA Binauraliser " + String(versionString) + " plug-in. " + Time::getCurrentTime().toString(true, true)));
    jsonObj->setProperty ("GenericLayout", ConfigurationHelper::convertElementsToVar (sources, "Source Directions and Distances"));
    //jsonObj->setProperty ("LoudspeakerLayout", ConfigurationHelper::convertLoudspeakersToVar (sources, "Source Directions"));
    Result result = ConfigurationHelper::writeConfigurationToFile (destination, var (jsonObj));
}

/* Adapted from the AllRADecoder by Daniel Rudrich, (c) 2017 (GPLv3 license) */
void PluginProcessor::loadConfiguration (const File& configFile)
{
    int channelIDs[MAX_NUM_INPUTS+1] = {0};
    int virtual_channelIDs[MAX_NUM_INPUTS+1] = {0};
    sources.removeAllChildren(nullptr);
    Result result = ConfigurationHelper::parseFileForGenericLayout (configFile, sources, nullptr);
    //Result result = ConfigurationHelper::parseFileForLoudspeakerLayout (configFile, sources, nullptr);
    if(result.wasOk()){
        int num_srcs, num_virtual_srcs, src_idx, jj;
        num_srcs = num_virtual_srcs = src_idx = jj = 0;
        /* get Channel IDs and find number of directions and virtual directions */
        for (ValueTree::Iterator it = sources.begin(); it != sources.end(); ++it){
            if ( !((*it).getProperty("Imaginary"))){
                num_srcs++; channelIDs[jj] = (*it).getProperty("Channel");
            }
            else{
                virtual_channelIDs[num_virtual_srcs] = (*it).getProperty("Channel");
                num_virtual_srcs++; channelIDs[jj] = -1;
            }
            jj++;
        }
        /* remove virtual channels and shift the channel indices down */
        for(int i=0; i<num_virtual_srcs; i++)
            for(int j=0; j<num_srcs+num_virtual_srcs; j++)
                if(channelIDs[j] == -1)
                    for(int k=j; k<num_srcs+num_virtual_srcs; k++)
                        channelIDs[k] = channelIDs[k+1];
        
        /* then decriment the channel IDs to remove the gaps */
        for(int i=0; i<num_virtual_srcs; i++)
            for(int j=0; j<num_srcs+num_virtual_srcs; j++)
                if( channelIDs[j] > virtual_channelIDs[i]-i )
                    channelIDs[j]--;
        
        /* update with the new configuration  */
        setParameterValue("numSources", num_srcs);
        for (ValueTree::Iterator it = sources.begin() ; it != sources.end(); ++it){
            if ( !((*it).getProperty("Imaginary"))){
                float azimValue = (float)(*it).getProperty("Azimuth");
                float elevValue = (float)(*it).getProperty("Elevation");
                float distValue = (float)(*it).getProperty("Radius");
                setParameterValue("azim" + juce::String(channelIDs[src_idx]-1), azimValue);
                setParameterValue("elev" + juce::String(channelIDs[src_idx]-1), elevValue);
                setParameterValue("dist" + juce::String(channelIDs[src_idx]-1), distValue);
                src_idx++;
            }
        }
        
        refreshWindow = true;
    }
}


