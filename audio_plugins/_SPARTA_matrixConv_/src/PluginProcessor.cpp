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

static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterBool>("enablePartitionedConv", "EnablePartitionedConv", false, AudioParameterBoolAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numInputChannels", "NumInputChannels", 1, MAX_NUM_INPUTS, 1, AudioParameterIntAttributes().withAutomatable(false)));
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if(parameterID == "enablePartitionedConv"){
        matrixconv_setEnablePart(hMCnv, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "numInputChannels"){
        matrixconv_setNumInputChannels(hMCnv, static_cast<int>(newValue));
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("enablePartitionedConv", matrixconv_getEnablePart(hMCnv));
    setParameterValue("numInputChannels", matrixconv_getNumInputChannels(hMCnv));
}

void PluginProcessor::setInternalStateUsingParameterValues()
{
    matrixconv_setEnablePart(hMCnv, getParameterBool("enablePartitionedConv"));
    matrixconv_setNumInputChannels(hMCnv, getParameterInt("numInputChannels"));
}

PluginProcessor::PluginProcessor()
    : PluginProcessorBase(
        BusesProperties()
            .withInput("Input", AudioChannelSet::discreteChannels(64), true)
            .withOutput("Output", AudioChannelSet::discreteChannels(64), true),
        createParameterLayout())
{
    nSampleRate = 48000;
    nHostBlockSize = -1;
    formatManager.registerBasicFormats();
    durationInSeconds = 0.0f; 
    lastWavDirectory = TRANS("no_file");
    matrixconv_create(&hMCnv);
    addParameterListeners(this);
}

PluginProcessor::~PluginProcessor()
{
    removeParameterListeners(this);
    matrixconv_destroy(&hMCnv);
}

void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    if(firstInit){
        /* Need to grab defaults */
        setParameterValuesUsingInternalState();
        firstInit = false;
    }
    nHostBlockSize = samplesPerBlock;
    nNumInputs =  getTotalNumInputChannels();
    nNumOutputs = getTotalNumOutputChannels();
    nSampleRate = (int)(sampleRate + 0.5);

    matrixconv_init(hMCnv, nSampleRate, nHostBlockSize);
    AudioProcessor::setLatencySamples(matrixconv_getProcessingDelay(hMCnv));
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    ScopedNoDenormals noDenormals;
    
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels());
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels());
    float* const* bufferData = buffer.getArrayOfWritePointers();

    matrixconv_process(hMCnv, bufferData, bufferData, nNumInputs, nNumOutputs, nCurrentBlockSize);
}

AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (*this);
}

void PluginProcessor::getStateInformation (MemoryBlock& destData)
{
    juce::ValueTree state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xmlState(state.createXml());
    xmlState->setTagName("MATRIXCONVAUDIOPLUGINSETTINGS");
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
    if (xmlState != nullptr && xmlState->hasTagName("MATRIXCONVAUDIOPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10101
            if(xmlState->hasAttribute("LastWavFilePath"))
                lastWavDirectory = xmlState->getStringAttribute("LastWavFilePath", "no_file");
            if(xmlState->hasAttribute("usePartitionedConv"))
                matrixconv_setEnablePart(hMCnv, xmlState->getIntAttribute("usePartitionedConv", 1));
            if(xmlState->hasAttribute("numInputChannels"))
                matrixconv_setNumInputChannels(hMCnv, xmlState->getIntAttribute("numInputChannels", 1));

            if(lastWavDirectory!="no_file")
                loadWavFile();
            
            setParameterValuesUsingInternalState();
        }
        else if(xmlState->getIntAttribute("VersionCode")>=0x10101){
            removeParameterListeners(this);
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            addParameterListeners(this);
            
            /* Many hosts will also trigger parameterChanged() for all parameters after calling setStateInformation() */
            /* However, some hosts do not. Therefore, it is better to ensure that the internal state is always up-to-date by calling: */
            setInternalStateUsingParameterValues();
            
            /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
            if(xmlState->hasAttribute("LastWavFilePath"))
                lastWavDirectory = xmlState->getStringAttribute("LastWavFilePath", "no_file");

            if(lastWavDirectory!="no_file")
                loadWavFile();
        }

        //matrixconv_refreshParams(hMCnv);
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

