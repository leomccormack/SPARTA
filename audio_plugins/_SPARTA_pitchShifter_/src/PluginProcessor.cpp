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

PluginProcessor::PluginProcessor() : 
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(MAX_NUM_CHANNELS), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(MAX_NUM_CHANNELS), true))
{
	nSampleRate = 48000; 
	pitch_shifter_create(&hPS);
    startTimer(TIMER_PROCESSING_RELATED, 80);
}

PluginProcessor::~PluginProcessor()
{
	pitch_shifter_destroy(&hPS);
}

void PluginProcessor::setParameter (int index, float newValue)
{
	switch (index) {
        case k_numChannels:      pitch_shifter_setNumChannels(hPS, (int)(newValue*(float)(MAX_NUM_CHANNELS-1) + 1.5f)); break;
        case k_pitchShiftFactor: pitch_shifter_setPitchShiftFactor(hPS, newValue * (PITCH_SHIFTER_MAX_SHIFT_FACTOR - PITCH_SHIFTER_MIN_SHIFT_FACTOR) + PITCH_SHIFTER_MIN_SHIFT_FACTOR); break;
        case k_OSampOption:      pitch_shifter_setOSampOption(hPS, (PITCH_SHIFTER_OSAMP_OPTIONS)(int)(newValue*(float)(PITCH_SHIFTER_NUM_OSAMP_OPTIONS-1) + 1.5f)); break;
        case k_fftOption:        pitch_shifter_setFFTSizeOption(hPS, (PITCH_SHIFTER_FFTSIZE_OPTIONS)(int)(newValue*(float)(PITCH_SHIFTER_NUM_FFTSIZE_OPTIONS-1) + 1.5f)); break;
		default: break;
	}
}

void PluginProcessor::setCurrentProgram (int /*index*/)
{
}

float PluginProcessor::getParameter (int index)
{
    switch (index) {
        case k_numChannels:      return (float)(pitch_shifter_getNCHrequired(hPS)-1)/(float)(MAX_NUM_CHANNELS-1);
        case k_OSampOption:      return (float)(pitch_shifter_getOSampOption(hPS)-1)/(float)(PITCH_SHIFTER_NUM_OSAMP_OPTIONS-1);
        case k_fftOption:        return (float)(pitch_shifter_getFFTSizeOption(hPS)-1)/(float)(PITCH_SHIFTER_NUM_FFTSIZE_OPTIONS-1);
        case k_pitchShiftFactor: return (float)(pitch_shifter_getPitchShiftFactor(hPS) - PITCH_SHIFTER_MIN_SHIFT_FACTOR)/(PITCH_SHIFTER_MAX_SHIFT_FACTOR - PITCH_SHIFTER_MIN_SHIFT_FACTOR);
		default: return 0.0f;
	}
}

int PluginProcessor::getNumParameters()
{
	return k_NumOfParameters;
}

const String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

const String PluginProcessor::getParameterName (int index)
{
    switch (index){
        case k_numChannels:      return "N Channels";
        case k_fftOption:        return "FFTSize";
        case k_OSampOption:      return "OverSamp";
        case k_pitchShiftFactor: return "pitchShift";
		default: return "NULL";
	}
}

const String PluginProcessor::getParameterText(int index)
{
    switch (index) {
        case k_numChannels:      return String(pitch_shifter_getNCHrequired(hPS));
        case k_pitchShiftFactor: return String(pitch_shifter_getPitchShiftFactor(hPS));
        case k_OSampOption:
            switch(pitch_shifter_getOSampOption(hPS)){
                case PITCH_SHIFTER_OSAMP_2:   return "2";
                case PITCH_SHIFTER_OSAMP_4:   return "4";
                case PITCH_SHIFTER_OSAMP_8:   return "8";
                case PITCH_SHIFTER_OSAMP_16:  return "16";
                case PITCH_SHIFTER_OSAMP_32:  return "32";
                default: return "NULL";
            }
        case k_fftOption:
            switch(pitch_shifter_getFFTSizeOption(hPS)){
                case PITCH_SHIFTER_FFTSIZE_512:   return "512";
                case PITCH_SHIFTER_FFTSIZE_1024:  return "1024";
                case PITCH_SHIFTER_FFTSIZE_2048:  return "2048";
                case PITCH_SHIFTER_FFTSIZE_4096:  return "4096";
                case PITCH_SHIFTER_FFTSIZE_8192:  return "8192";
                case PITCH_SHIFTER_FFTSIZE_16384: return "16384";
                default: return "NULL";
            }
        default: return "NULL";
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
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels());
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels());
    float* const* bufferData = buffer.getArrayOfWritePointers();

    pitch_shifter_process(hPS, bufferData, bufferData, nNumInputs, nNumOutputs, nCurrentBlockSize);
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
	/* Create an outer XML element.. */ 
	XmlElement xml("PITCHSHIFTERAUDIOPLUGINSETTINGS");
 
	xml.setAttribute("PITCHSHIFTFACTOR", pitch_shifter_getPitchShiftFactor(hPS));
    xml.setAttribute("NCHANNELS", pitch_shifter_getNCHrequired(hPS));
    xml.setAttribute("OSAMP", (int)pitch_shifter_getOSampOption(hPS));
    xml.setAttribute("FFTSIZE", (int)pitch_shifter_getFFTSizeOption(hPS));
    
	copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	/* This getXmlFromBinary() function retrieves XML from the binary blob */
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr) {
		/* make sure that it's actually the correct XML object */
		if (xmlState->hasTagName("PITCHSHIFTERAUDIOPLUGINSETTINGS")) {
            if(xmlState->hasAttribute("PITCHSHIFTFACTOR"))
                pitch_shifter_setPitchShiftFactor(hPS, (float)xmlState->getDoubleAttribute("PITCHSHIFTFACTOR", 1.0f));
            if(xmlState->hasAttribute("NCHANNELS"))
                pitch_shifter_setNumChannels(hPS, xmlState->getIntAttribute("NCHANNELS", 1));
            if(xmlState->hasAttribute("OSAMP"))
                pitch_shifter_setOSampOption(hPS, (PITCH_SHIFTER_OSAMP_OPTIONS)xmlState->getIntAttribute("OSAMP", PITCH_SHIFTER_OSAMP_16));
            if(xmlState->hasAttribute("FFTSIZE"))
                pitch_shifter_setFFTSizeOption(hPS, (PITCH_SHIFTER_FFTSIZE_OPTIONS)xmlState->getIntAttribute("FFTSIZE", PITCH_SHIFTER_FFTSIZE_8192));

            pitch_shifter_refreshParams(hPS);
        }
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

