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
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("outputOrder", "OutputOrder",
                                                                  juce::StringArray{"1st order","2nd order","3rd order","4th order","5th order","6th order","7th order","8th order","9th order","10th order"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("channelOrder", "ChannelOrder", juce::StringArray{"ACN", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("normType", "NormType", juce::StringArray{"N3D", "SN3D", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numSources", "NumSources", 1, MAX_NUM_INPUTS, 1, AudioParameterIntAttributes().withAutomatable(false)));
    for(int i=0; i<MAX_NUM_INPUTS; i++){
        params.push_back(std::make_unique<juce::AudioParameterFloat>("azim" + juce::String(i), "Azim_" + juce::String(i+1), juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withLabel(juce::String::fromUTF8(u8"°"))));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("elev" + juce::String(i), "Elev_" + juce::String(i+1), juce::NormalisableRange<float>(-90.0f, 90.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withLabel(juce::String::fromUTF8(u8"°"))));
    }
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "outputOrder"){
        ambi_enc_setOutputOrder(hAmbi, static_cast<SH_ORDERS>(newValue+1.001f));
    }
    else if (parameterID == "channelOrder"){
        ambi_enc_setChOrder(hAmbi, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "normType"){
        ambi_enc_setNormType(hAmbi, static_cast<int>(newValue+1.001f));
    }
    else if(parameterID == "numSources"){
        ambi_enc_setNumSources(hAmbi, static_cast<int>(newValue));
    }
    for(int i=0; i<MAX_NUM_INPUTS; i++){
        if(parameterID == "azim" + juce::String(i)){
            ambi_enc_setSourceAzi_deg(hAmbi, i, newValue);
            setRefreshWindow(true);
            break;
        }
        else if(parameterID == "elev" + juce::String(i)){
            ambi_enc_setSourceElev_deg(hAmbi, i, newValue);
            setRefreshWindow(true);
            break;
        }
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("outputOrder", ambi_enc_getOutputOrder(hAmbi)-1);
    setParameterValue("channelOrder", ambi_enc_getChOrder(hAmbi)-1);
    setParameterValue("normType", ambi_enc_getNormType(hAmbi)-1);
    setParameterValue("numSources", ambi_enc_getNumSources(hAmbi));
    for(int i=0; i<MAX_NUM_INPUTS; i++){
        setParameterValue("azim" + juce::String(i), ambi_enc_getSourceAzi_deg(hAmbi, i));
        setParameterValue("elev" + juce::String(i), ambi_enc_getSourceElev_deg(hAmbi, i));
    }
}

PluginProcessor::PluginProcessor() :
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	ambi_enc_create(&hAmbi);
    refreshWindow = true;
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();
}

PluginProcessor::~PluginProcessor()
{
	ambi_enc_destroy(&hAmbi);
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

	ambi_enc_init(hAmbi, nSampleRate);
    AudioProcessor::setLatencySamples(ambi_enc_getProcessingDelay());
}

void PluginProcessor::releaseResources()
{
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    ScopedNoDenormals noDenormals;
    
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels(), 256);
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels(), 256);
    float* const* bufferData = buffer.getArrayOfWritePointers();
    float* pFrameData[256];
    int frameSize = ambi_enc_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            ambi_enc_process(hAmbi, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
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
    xmlState->setTagName("AMBIENCPLUGINSETTINGS");
    xmlState->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10401

    /* Other */
    xmlState->setAttribute("JSONFilePath", lastDir.getFullPathName());

    /* Save */
    copyXmlToBinary(*xmlState, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("AMBIENCPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10401
            for(int i=0; i<ambi_enc_getMaxNumSources(); i++){
                if(xmlState->hasAttribute("SourceAziDeg" + String(i)))
                    ambi_enc_setSourceAzi_deg(hAmbi, i, (float)xmlState->getDoubleAttribute("SourceAziDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceElevDeg" + String(i)))
                    ambi_enc_setSourceElev_deg(hAmbi, i, (float)xmlState->getDoubleAttribute("SourceElevDeg" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("nSources"))
                ambi_enc_setNumSources(hAmbi, xmlState->getIntAttribute("nSources", 1));
            
            if(xmlState->hasAttribute("JSONFilePath"))
                lastDir = xmlState->getStringAttribute("JSONFilePath", "");
            
            if(xmlState->hasAttribute("NORM"))
                ambi_enc_setNormType(hAmbi, xmlState->getIntAttribute("NORM", 1));
            if(xmlState->hasAttribute("CHORDER"))
                ambi_enc_setChOrder(hAmbi, xmlState->getIntAttribute("CHORDER", 1));
            if(xmlState->hasAttribute("OUT_ORDER"))
                ambi_enc_setOutputOrder(hAmbi, xmlState->getIntAttribute("OUT_ORDER", 1));
            
            setParameterValuesUsingInternalState();
        }
        else if(xmlState->getIntAttribute("VersionCode")>=0x10401){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* Other */
            if(xmlState->hasAttribute("JSONFilePath"))
                lastDir = xmlState->getStringAttribute("JSONFilePath", "");
        }
        
        ambi_enc_refreshParams(hAmbi);
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
    for (int i=0; i<ambi_enc_getNumSources(hAmbi);i++)
    {
        sources.appendChild (ConfigurationHelper::
                             createElement(ambi_enc_getSourceAzi_deg(hAmbi, i),
                                          ambi_enc_getSourceElev_deg(hAmbi, i),
                                          1.0f, i+1, false, 1.0f), nullptr);
    }
    DynamicObject* jsonObj = new DynamicObject();
    jsonObj->setProperty("Name", var("SPARTA AmbiENC source directions."));
    char versionString[10];
    strcpy(versionString, "v");
    strcat(versionString, JucePlugin_VersionString);
    jsonObj->setProperty("Description", var("This configuration file was created with the SPARTA AmbiENC " + String(versionString) + " plug-in. " + Time::getCurrentTime().toString(true, true)));
    jsonObj->setProperty ("GenericLayout", ConfigurationHelper::convertElementsToVar (sources, "Source Directions"));
    Result result = ConfigurationHelper::writeConfigurationToFile (destination, var (jsonObj));
}

/* Adapted from the AllRADecoder by Daniel Rudrich, (c) 2017 (GPLv3 license) */
void PluginProcessor::loadConfiguration (const File& configFile)
{
    int channelIDs[MAX_NUM_CHANNELS+1] = {0};
    int virtual_channelIDs[MAX_NUM_CHANNELS+1] = {0};
    sources.removeAllChildren(nullptr);
    Result result = ConfigurationHelper::parseFileForGenericLayout(configFile, sources, nullptr);
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
                setParameterValue("azim" + juce::String(channelIDs[src_idx]-1), azimValue);
                setParameterValue("elev" + juce::String(channelIDs[src_idx]-1), elevValue);
                src_idx++;
            }
        }
        
        refreshWindow=true;
    }
}

