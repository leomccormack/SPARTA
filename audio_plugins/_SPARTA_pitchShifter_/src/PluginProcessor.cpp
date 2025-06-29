/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2020 - Leo McCormack.
 
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
    params.push_back(std::make_unique<juce::AudioParameterInt>("numChannels", "NumChannels", 1, MAX_NUM_INPUTS, 1, AudioParameterIntAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("pitchShiftFactor", "PitchShiftFactor", juce::NormalisableRange<float>(PITCH_SHIFTER_MIN_SHIFT_FACTOR, PITCH_SHIFTER_MAX_SHIFT_FACTOR, 0.01f), 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("fftOption", "FFTOption", juce::StringArray{"512", "1024", "2048", "4096", "8192", "16384"}, 1, AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("oSampOption", "OSampOption", juce::StringArray{"2", "4", "8", "16", "32"}, 1, AudioParameterChoiceAttributes().withAutomatable(false)));
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if(parameterID == "numChannels"){
        pitch_shifter_setNumChannels(hPS, static_cast<int>(newValue));
    }
    else if(parameterID == "pitchShiftFactor"){
        pitch_shifter_setPitchShiftFactor(hPS, newValue);
    }
    else if(parameterID == "fftOption"){
        pitch_shifter_setFFTSizeOption(hPS, static_cast<PITCH_SHIFTER_FFTSIZE_OPTIONS>(newValue+1.001f));
    }
    else if(parameterID == "oSampOption"){
        pitch_shifter_setOSampOption(hPS, static_cast<PITCH_SHIFTER_OSAMP_OPTIONS>(newValue+1.001f));
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("numChannels", pitch_shifter_getNCHrequired(hPS));
    setParameterValue("pitchShiftFactor", pitch_shifter_getPitchShiftFactor(hPS));
    setParameterValue("fftOption", pitch_shifter_getFFTSizeOption(hPS));
    setParameterValue("oSampOption", pitch_shifter_getOSampOption(hPS));
}

PluginProcessor::PluginProcessor() : 
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	nSampleRate = 48000; 
	pitch_shifter_create(&hPS);
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();
    
    startTimer(TIMER_PROCESSING_RELATED, 80);
}

PluginProcessor::~PluginProcessor()
{
	pitch_shifter_destroy(&hPS);
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

	pitch_shifter_init(hPS, (float)sampleRate);
    AudioProcessor::setLatencySamples(pitch_shifter_getProcessingDelay(hPS));
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

    pitch_shifter_process(hPS, bufferData, bufferData, nNumInputs, nNumOutputs, nCurrentBlockSize);
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
    xmlState->setTagName("PITCHSHIFTERAUDIOPLUGINSETTINGS");
    xmlState->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10101
    
    /* Save */
    copyXmlToBinary(*xmlState, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("PITCHSHIFTERAUDIOPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10101
            if(xmlState->hasAttribute("PITCHSHIFTFACTOR"))
                pitch_shifter_setPitchShiftFactor(hPS, (float)xmlState->getDoubleAttribute("PITCHSHIFTFACTOR", 1.0f));
            if(xmlState->hasAttribute("NCHANNELS"))
                pitch_shifter_setNumChannels(hPS, xmlState->getIntAttribute("NCHANNELS", 1));
            if(xmlState->hasAttribute("OSAMP"))
                pitch_shifter_setOSampOption(hPS, (PITCH_SHIFTER_OSAMP_OPTIONS)xmlState->getIntAttribute("OSAMP", PITCH_SHIFTER_OSAMP_16));
            if(xmlState->hasAttribute("FFTSIZE"))
                pitch_shifter_setFFTSizeOption(hPS, (PITCH_SHIFTER_FFTSIZE_OPTIONS)xmlState->getIntAttribute("FFTSIZE", PITCH_SHIFTER_FFTSIZE_8192));
            
            setParameterValuesUsingInternalState();
        }
        else if(xmlState->getIntAttribute("VersionCode")>=0x10101){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
        }
        
        pitch_shifter_refreshParams(hPS);
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

