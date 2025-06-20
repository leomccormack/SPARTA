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
    params.push_back(std::make_unique<juce::AudioParameterFloat>("decorrelation", "Decorrelation", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numChannels", "NumChannels", 1, MAX_NUM_INPUTS, 1, AudioParameterIntAttributes().withAutomatable(false)));
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if(parameterID == "decorrelation"){
        decorrelator_setDecorrelationAmount(hDecor, newValue);
    }
    else if(parameterID == "numChannels"){
        decorrelator_setNumberOfChannels(hDecor, static_cast<int>(newValue));
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("decorrelation", decorrelator_getDecorrelationAmount(hDecor));
    setParameterValue("numChannels", decorrelator_getNumberOfChannels(hDecor));
}

PluginProcessor::PluginProcessor() :
    AudioProcessor(BusesProperties()
        .withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
        .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	decorrelator_create(&hDecor);
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();
    
    startTimer(TIMER_PROCESSING_RELATED, 40);
}

PluginProcessor::~PluginProcessor()
{
	decorrelator_destroy(&hDecor);
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

	decorrelator_init(hDecor, nSampleRate);
    AudioProcessor::setLatencySamples(decorrelator_getProcessingDelay());
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
    int frameSize = decorrelator_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            decorrelator_process(hDecor, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
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
    xmlState->setTagName("DECORRELATORPLUGINSETTINGS");
    xmlState->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10102
    
    /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
    xmlState->setAttribute("ENERGY_COMP", decorrelator_getLevelCompensationFlag(hDecor));
    xmlState->setAttribute("BYPASS_TRANSIENTS", decorrelator_getTransientBypassFlag(hDecor));
    
    /* Save */
    copyXmlToBinary(*xmlState, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("BINAURALISERNFPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10102
            if(xmlState->hasAttribute("NCHANNELS"))
                decorrelator_setNumberOfChannels(hDecor, xmlState->getIntAttribute("NCHANNELS", 2));
            if(xmlState->hasAttribute("DECOR_AMOUNT"))
                decorrelator_setDecorrelationAmount(hDecor, (float)xmlState->getDoubleAttribute("DECOR_AMOUNT", 2));
            if(xmlState->hasAttribute("ENERGY_COMP"))
                decorrelator_setLevelCompensationFlag(hDecor, xmlState->getIntAttribute("ENERGY_COMP", 2));
            if(xmlState->hasAttribute("BYPASS_TRANSIENTS"))
                decorrelator_setTransientBypassFlag(hDecor, xmlState->getIntAttribute("BYPASS_TRANSIENTS", 2));
            
            setParameterValuesUsingInternalState();
        }
        else if(xmlState->getIntAttribute("VersionCode")>=0x10102){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
            if(xmlState->hasAttribute("ENERGY_COMP"))
                decorrelator_setLevelCompensationFlag(hDecor, xmlState->getIntAttribute("ENERGY_COMP", 2));
            if(xmlState->hasAttribute("BYPASS_TRANSIENTS"))
                decorrelator_setTransientBypassFlag(hDecor, xmlState->getIntAttribute("BYPASS_TRANSIENTS", 2));
            
        }
        
        decorrelator_refreshParams(hDecor);
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

