/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2017/2018 - Leo McCormack.
 
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

    params.push_back(std::make_unique<juce::AudioParameterChoice>("inputOrder", "InputOrder",
                                                                  juce::StringArray{"1st order","2nd order","3rd order","4th order","5th order","6th order","7th order","8th order","9th order","10th order"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("minFreq", "MinFreq", juce::NormalisableRange<float>(0.0f, 24e3f, 0.1f), 0.0f,
                                                                 AudioParameterFloatAttributes().withLabel("Hz")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("maxFreq", "MaxFreq", juce::NormalisableRange<float>(0.0f, 24e3f, 0.1f), 0.0f,
                                                                 AudioParameterFloatAttributes().withLabel("Hz")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("mapAvg", "MapAvg", juce::NormalisableRange<float>(0.0f, 2000.0f, 0.1f), 0.0f,
                                                                 AudioParameterFloatAttributes().withLabel("ms")));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("channelOrder", "ChannelOrder", juce::StringArray{"ACN", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("normType", "NormType", juce::StringArray{"N3D", "SN3D", "FuMa"}, 0));
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "inputOrder"){
        sldoa_setMasterOrder(hSld, static_cast<int>(newValue+1.001f));
        sldoa_setAnaOrderAllBands(hSld, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "minFreq"){
        sldoa_setMinFreq(hSld, newValue);
    }
    else if (parameterID == "maxFreq"){
        sldoa_setMaxFreq(hSld, newValue);
    }
    else if (parameterID == "mapAvg"){
        sldoa_setAvg(hSld, newValue);
    }
    else if (parameterID == "channelOrder"){
        sldoa_setChOrder(hSld, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "normType"){
        sldoa_setNormType(hSld, static_cast<int>(newValue+1.001f));
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("inputOrder", sldoa_getMasterOrder(hSld)-1);
    setParameterValue("minFreq", sldoa_getMinFreq(hSld));
    setParameterValue("maxFreq", sldoa_getMaxFreq(hSld));
    setParameterValue("mapAvg", sldoa_getAvg(hSld));
    setParameterValue("channelOrder", sldoa_getChOrder(hSld)-1);
    setParameterValue("normType", sldoa_getNormType(hSld)-1);
}

void PluginProcessor::setInternalStateUsingParameterValues()
{
    sldoa_setMasterOrder(hSld, getParameterChoice("inputOrder")+1);
    sldoa_setAnaOrderAllBands(hSld, getParameterChoice("inputOrder")+1);
    sldoa_setMinFreq(hSld, getParameterFloat("minFreq"));
    sldoa_setMaxFreq(hSld, getParameterFloat("maxFreq"));
    sldoa_setAvg(hSld, getParameterFloat("mapAvg"));
    sldoa_setChOrder(hSld, getParameterChoice("channelOrder")+1);
    sldoa_setNormType(hSld, getParameterChoice("normType")+1);
}

PluginProcessor::PluginProcessor() : 
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	nSampleRate = 48000;
	sldoa_create(&hSld);
    isPlaying = false;
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();
    
    /* camera default settings */
    cameraID = 1;
    flipLR = flipUD = false;
    greyScale = true;
    startTimer(TIMER_PROCESSING_RELATED, 40);
}

PluginProcessor::~PluginProcessor()
{
	sldoa_destroy(&hSld);
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
    nNumInputs =  getTotalNumInputChannels();
    nSampleRate = (int)(sampleRate + 0.5);
    isPlaying = false; 
	sldoa_init(hSld, nSampleRate);

    //AudioProcessor::setLatencySamples(sldoa_getProcessingDelay());
}

void PluginProcessor::releaseResources()
{
    isPlaying = false;
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    ScopedNoDenormals noDenormals;
    
	int nCurrentBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels());
    float* const* bufferData = buffer.getArrayOfWritePointers();
 
    /* check whether the playhead is moving */
    playHead = getPlayHead();
    if(playHead!=NULL)
        isPlaying = playHead->getPosition()->getIsPlaying();
    else
        isPlaying = false;

    /* If there is no playhead, or it is not moving, see if there is audio in the buffer */
    if(!isPlaying){
        for(int j=0; j<nNumInputs; j++){
            isPlaying = buffer.getMagnitude(j, 0, MIN(8,nCurrentBlockSize) /* should be enough */)>1e-5f ? true : false;
            if(isPlaying)
                break;
        }
    }

    /* perform processing */
    sldoa_analysis(hSld, bufferData, nNumInputs, nCurrentBlockSize, isPlaying);
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
    xmlState->setTagName("SLDOAAUDIOPLUGINSETTINGS");
    xmlState->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10501
    
    /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
    for(int i=0; i<sldoa_getNumberOfBands(); i++)
        xmlState->setAttribute("AnaOrder" + String(i), sldoa_getAnaOrder(hSld, i));
    
    /* Other */
    xmlState->setAttribute("cameraID", cameraID);
    xmlState->setAttribute("flipLR", flipLR);
    xmlState->setAttribute("flipUD", flipUD);
    xmlState->setAttribute("greyScale", greyScale);
    
    /* Save */
    copyXmlToBinary(*xmlState, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("SLDOAAUDIOPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10501
            /* pull attributes */
            if(xmlState->hasAttribute("MasterOrder"))
                sldoa_setMasterOrder(hSld, xmlState->getIntAttribute("MasterOrder", 1));
            if(xmlState->hasAttribute("MaxFreq"))
                sldoa_setMaxFreq(hSld, (float)xmlState->getDoubleAttribute("MaxFreq", 5000.0));
            if(xmlState->hasAttribute("MinFreq"))
                sldoa_setMinFreq(hSld, (float)xmlState->getDoubleAttribute("MinFreq", 500.0));
            if(xmlState->hasAttribute("Avg"))
                sldoa_setAvg(hSld, (float)xmlState->getDoubleAttribute("Avg", 100.0));
            for(int i=0; i<sldoa_getNumberOfBands(); i++){
                if(xmlState->hasAttribute("AnaOrder"+String(i)))
                    sldoa_setAnaOrder(hSld, xmlState->getIntAttribute("AnaOrder"+String(i), 1), i);
            }
            if(xmlState->hasAttribute("ChOrder"))
                sldoa_setChOrder(hSld, xmlState->getIntAttribute("ChOrder", 1));
            if(xmlState->hasAttribute("Norm"))
                sldoa_setNormType(hSld, xmlState->getIntAttribute("Norm", 1));
            
            if(xmlState->hasAttribute("cameraID"))
                cameraID = (int)xmlState->getIntAttribute("cameraID", 1);
            if(xmlState->hasAttribute("flipLR"))
                flipLR = (bool)xmlState->getIntAttribute("flipLR", 0);
            if(xmlState->hasAttribute("flipUD"))
                flipUD = (bool)xmlState->getIntAttribute("flipUD", 0);
            if(xmlState->hasAttribute("greyScale"))
                greyScale = (bool)xmlState->getIntAttribute("greyScale", 1);
            
            setParameterValuesUsingInternalState();
        }
        else if(xmlState->getIntAttribute("VersionCode")>=0x10501){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* pull attributes */
            for(int i=0; i<sldoa_getNumberOfBands(); i++){
                if(xmlState->hasAttribute("AnaOrder"+String(i)))
                    sldoa_setAnaOrder(hSld, xmlState->getIntAttribute("AnaOrder"+String(i), 1), i);
            }
            
            /* Other */
            if(xmlState->hasAttribute("cameraID"))
                cameraID = (int)xmlState->getIntAttribute("cameraID", 1);
            if(xmlState->hasAttribute("flipLR"))
                flipLR = (bool)xmlState->getIntAttribute("flipLR", 0);
            if(xmlState->hasAttribute("flipUD"))
                flipUD = (bool)xmlState->getIntAttribute("flipUD", 0);
            if(xmlState->hasAttribute("greyScale"))
                greyScale = (bool)xmlState->getIntAttribute("greyScale", 1);
            
            /* Many hosts will also trigger parameterChanged() for all parameters after calling setStateInformation() */
            /* However, some hosts do not. Therefore, it is better to ensure that the internal state is always up-to-date by calling: */
            setInternalStateUsingParameterValues();
        }
        
        sldoa_refreshSettings(hSld);
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

