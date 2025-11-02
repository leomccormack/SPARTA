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

#if JucePlugin_Build_AAX && !JucePlugin_AAXDisableDefaultSettingsChunks
# error "AAX Default Settings Chunk is enabled. This may override parameter defaults."
#endif

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
    
    params.push_back(std::make_unique<juce::AudioParameterBool>("enablePartitionedConv", "EnablePartitionedConv", false, AudioParameterBoolAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numChannels", "NumChannels", 1, MAX_NUM_INPUTS, 1, AudioParameterIntAttributes().withAutomatable(false)));
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if(parameterID == "enablePartitionedConv"){
        multiconv_setEnablePart(hMCnv, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "numChannels"){
        multiconv_setNumChannels(hMCnv, static_cast<int>(newValue));
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("enablePartitionedConv", multiconv_getEnablePart(hMCnv));
    setParameterValue("numChannels", multiconv_getNumChannels(hMCnv));
}

void PluginProcessor::setInternalStateUsingParameterValues()
{
    multiconv_setEnablePart(hMCnv, getParameterBool("enablePartitionedConv"));
    multiconv_setNumChannels(hMCnv, getParameterInt("numChannels"));
}

PluginProcessor::PluginProcessor() :
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	nSampleRate = 48000;
    nHostBlockSize = -1;
    formatManager.registerBasicFormats();
    durationInSeconds = 0.0f;
    lastWavDirectory = TRANS("no_file");
	multiconv_create(&hMCnv);
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();
}

PluginProcessor::~PluginProcessor()
{
	multiconv_destroy(&hMCnv);
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
    return 1;
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
    nNumInputs =  getTotalNumInputChannels();
    nNumOutputs = getTotalNumOutputChannels();
    nSampleRate = (int)(sampleRate + 0.5);

	multiconv_init(hMCnv, nSampleRate, nHostBlockSize);
    AudioProcessor::setLatencySamples(multiconv_getProcessingDelay(hMCnv));
}

void PluginProcessor::releaseResources()
{
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    ScopedNoDenormals noDenormals;
    
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels());
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels());
    float* const* bufferData = buffer.getArrayOfWritePointers();

    multiconv_process(hMCnv, bufferData, bufferData, nNumInputs, nNumOutputs, nCurrentBlockSize); 
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
    xmlState->setTagName("MULTICONVAUDIOPLUGINSETTINGS");
    xmlState->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10101
        
    /* Other */
    xmlState->setAttribute("LastWavFilePath", lastWavDirectory);
    
    /* Save */
    copyXmlToBinary(*xmlState, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("MULTICONVAUDIOPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10101
            if(xmlState->hasAttribute("LastWavFilePath"))
                lastWavDirectory = xmlState->getStringAttribute("LastWavFilePath", "no_file");
            if(xmlState->hasAttribute("usePartitionedConv"))
                multiconv_setEnablePart(hMCnv, xmlState->getIntAttribute("usePartitionedConv", 1));
            if(xmlState->hasAttribute("numChannels"))
                multiconv_setNumChannels(hMCnv, xmlState->getIntAttribute("numChannels", 1));

            if(lastWavDirectory!="no_file")
                loadWavFile();
            
            setParameterValuesUsingInternalState();
        }
        else if(xmlState->getIntAttribute("VersionCode")>=0x10101){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
            if(xmlState->hasAttribute("LastWavFilePath"))
                lastWavDirectory = xmlState->getStringAttribute("LastWavFilePath", "no_file");
            if(lastWavDirectory!="no_file")
                loadWavFile();
            
            /* Many hosts will also trigger parameterChanged() for all parameters after calling setStateInformation() */
            /* However, some hosts do not. Therefore, it is better to ensure that the internal state is always up-to-date by calling: */
            setInternalStateUsingParameterValues();
        }

        //multiconv_refreshParams(hMCnv);
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

