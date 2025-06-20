/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2019 - Leo McCormack.
 
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

    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& /*parameterID*/, float /*newValue*/)
{
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
}

PluginProcessor::PluginProcessor() : 
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
    dirass_create(&hDir);
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();

    isPlaying = false;
    
    /* camera default settings */
    cameraID = 1;
    flipLR = flipUD = false;
    greyScale = true;
    startTimer(TIMER_PROCESSING_RELATED, 40);
}

PluginProcessor::~PluginProcessor()
{
    dirass_destroy(&hDir);
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
    nSampleRate = (int)(sampleRate + 0.5);
    nNumInputs = getTotalNumInputChannels();
    isPlaying = false;
    dirass_init(hDir, nSampleRate);

    //AudioProcessor::setLatencySamples(dirass_getProcessingDelay());
}

void PluginProcessor::releaseResources()
{
    isPlaying = false;
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    int nCurrentBlockSize = buffer.getNumSamples();
    nNumInputs = getTotalNumInputChannels();// buffer.getNumChannels();
    float* const* bufferData = buffer.getArrayOfWritePointers();

    /* check whether the playhead is moving */
    playHead = getPlayHead();
    if(playHead!=NULL)
        isPlaying = playHead->getCurrentPosition(currentPosition) == true ? currentPosition.isPlaying : false;
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

    /* perform analysis */
    dirass_analysis(hDir, bufferData, nNumInputs, nCurrentBlockSize, isPlaying);
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
    xmlState->setTagName("DIRASSAUDIOPLUGINSETTINGS");
    xmlState->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10201
    
    /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
    xmlState->setAttribute("beamType", dirass_getBeamType(hDir));
    xmlState->setAttribute("InputOrder", dirass_getInputOrder(hDir));
    xmlState->setAttribute("GridOption", dirass_getDisplayGridOption(hDir));
    xmlState->setAttribute("UpscaleOrder", dirass_getUpscaleOrder(hDir));
    xmlState->setAttribute("DirASSmode", dirass_getDiRAssMode(hDir));
    xmlState->setAttribute("MinFreq", dirass_getMinFreq(hDir));
    xmlState->setAttribute("MaxFreq", dirass_getMaxFreq(hDir));
    xmlState->setAttribute("CHorder", dirass_getChOrder(hDir));
    xmlState->setAttribute("Norm", dirass_getNormType(hDir));
    xmlState->setAttribute("FOVoption", dirass_getDispFOV(hDir));
    xmlState->setAttribute("ARoption", dirass_getAspectRatio(hDir));
    xmlState->setAttribute("MapAvg", dirass_getMapAvgCoeff(hDir));
    xmlState->setAttribute("DispWidth", dirass_getDispWidth(hDir));
    
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
    if (xmlState != nullptr && xmlState->hasTagName("DIRASSAUDIOPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10201
            if(xmlState->hasAttribute("beamType"))
                dirass_setBeamType(hDir, xmlState->getIntAttribute("beamType", 1));
            if(xmlState->hasAttribute("InputOrder"))
                dirass_setInputOrder(hDir, xmlState->getIntAttribute("InputOrder", 1));
            if(xmlState->hasAttribute("GridOption"))
                dirass_setDisplayGridOption(hDir, xmlState->getIntAttribute("GridOption", 1));
            if(xmlState->hasAttribute("UpscaleOrder"))
                dirass_setUpscaleOrder(hDir, xmlState->getIntAttribute("UpscaleOrder", 1));
            if(xmlState->hasAttribute("DirASSmode"))
                dirass_setDiRAssMode(hDir, xmlState->getIntAttribute("DirASSmode", 1));
            if(xmlState->hasAttribute("MinFreq"))
                dirass_setMinFreq(hDir, (float)xmlState->getDoubleAttribute("MinFreq", 100.0f));
            if(xmlState->hasAttribute("MaxFreq"))
                dirass_setMaxFreq(hDir, (float)xmlState->getDoubleAttribute("MaxFreq", 20e3f));
            if(xmlState->hasAttribute("CHorder"))
                dirass_setChOrder(hDir, xmlState->getIntAttribute("CHorder", 1));
            if(xmlState->hasAttribute("Norm"))
                dirass_setNormType(hDir, xmlState->getIntAttribute("Norm", 1));
            if(xmlState->hasAttribute("FOVoption"))
                dirass_setDispFOV(hDir, xmlState->getIntAttribute("FOVoption", 1));
            if(xmlState->hasAttribute("ARoption"))
                dirass_setAspectRatio(hDir, xmlState->getIntAttribute("ARoption", 1));
            if(xmlState->hasAttribute("MapAvg"))
                dirass_setMapAvgCoeff(hDir, (float)xmlState->getDoubleAttribute("MapAvg", 0.5f));
            if(xmlState->hasAttribute("DispWidth"))
                dirass_setDispWidth(hDir, (float)xmlState->getDoubleAttribute("DispWidth", 120));
            
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
        else if(xmlState->getIntAttribute("VersionCode")>=0x10201){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
            if(xmlState->hasAttribute("beamType"))
                dirass_setBeamType(hDir, xmlState->getIntAttribute("beamType", 1));
            if(xmlState->hasAttribute("InputOrder"))
                dirass_setInputOrder(hDir, xmlState->getIntAttribute("InputOrder", 1));
            if(xmlState->hasAttribute("GridOption"))
                dirass_setDisplayGridOption(hDir, xmlState->getIntAttribute("GridOption", 1));
            if(xmlState->hasAttribute("UpscaleOrder"))
                dirass_setUpscaleOrder(hDir, xmlState->getIntAttribute("UpscaleOrder", 1));
            if(xmlState->hasAttribute("DirASSmode"))
                dirass_setDiRAssMode(hDir, xmlState->getIntAttribute("DirASSmode", 1));
            if(xmlState->hasAttribute("MinFreq"))
                dirass_setMinFreq(hDir, (float)xmlState->getDoubleAttribute("MinFreq", 100.0f));
            if(xmlState->hasAttribute("MaxFreq"))
                dirass_setMaxFreq(hDir, (float)xmlState->getDoubleAttribute("MaxFreq", 20e3f));
            if(xmlState->hasAttribute("CHorder"))
                dirass_setChOrder(hDir, xmlState->getIntAttribute("CHorder", 1));
            if(xmlState->hasAttribute("Norm"))
                dirass_setNormType(hDir, xmlState->getIntAttribute("Norm", 1));
            if(xmlState->hasAttribute("FOVoption"))
                dirass_setDispFOV(hDir, xmlState->getIntAttribute("FOVoption", 1));
            if(xmlState->hasAttribute("ARoption"))
                dirass_setAspectRatio(hDir, xmlState->getIntAttribute("ARoption", 1));
            if(xmlState->hasAttribute("MapAvg"))
                dirass_setMapAvgCoeff(hDir, (float)xmlState->getDoubleAttribute("MapAvg", 0.5f));
            if(xmlState->hasAttribute("DispWidth"))
                dirass_setDispWidth(hDir, (float)xmlState->getDoubleAttribute("DispWidth", 120));
            
            /* Other */
            if(xmlState->hasAttribute("cameraID"))
                cameraID = (int)xmlState->getIntAttribute("cameraID", 1);
            if(xmlState->hasAttribute("flipLR"))
                flipLR = (bool)xmlState->getIntAttribute("flipLR", 0);
            if(xmlState->hasAttribute("flipUD"))
                flipUD = (bool)xmlState->getIntAttribute("flipUD", 0);
            if(xmlState->hasAttribute("greyScale"))
                greyScale = (bool)xmlState->getIntAttribute("greyScale", 1);
        }
        
        dirass_refreshSettings(hDir);
    } 
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

