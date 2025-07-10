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

    params.push_back(std::make_unique<juce::AudioParameterChoice>("inputOrder", "InputOrder",
                                                                  juce::StringArray{"1st order","2nd order","3rd order","4th order","5th order","6th order","7th order","8th order","9th order","10th order"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("powermapMode", "PowermapMode",
                                                                  juce::StringArray{"PWD","MVDR","CroPaC LCMV","MUSIC","log(MUSIC)","MinNorm","log(MinNorm)"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("covAvgCoeff", "CovAvgCoeff", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("channelOrder", "ChannelOrder", juce::StringArray{"ACN", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("normType", "NormType", juce::StringArray{"N3D", "SN3D", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numSources", "NumSources", 1, MAX_NUM_SH_SIGNALS/2, 1, AudioParameterIntAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FOVoption", "FOV",
                                                                  juce::StringArray{"360","180","90","60"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("ARoption", "AspectRatio",
                                                                  juce::StringArray{"2:1","16:9","4:3"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("mapAvg", "MapAvg", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.25f));
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "inputOrder"){
        powermap_setMasterOrder(hPm, static_cast<int>(newValue+1.001f));
        powermap_setAnaOrderAllBands(hPm, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "powermapMode"){
        powermap_setPowermapMode(hPm, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "covAvgCoeff"){
        powermap_setCovAvgCoeff(hPm, newValue);
    }
    else if (parameterID == "channelOrder"){
        powermap_setChOrder(hPm, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "normType"){
        powermap_setNormType(hPm, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "numSources"){
        powermap_setNumSources(hPm, static_cast<int>(newValue));
    }
    else if (parameterID == "FOVoption"){
        powermap_setDispFOV(hPm, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "ARoption"){
        powermap_setAspectRatio(hPm, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "mapAvg"){
        powermap_setPowermapAvgCoeff(hPm, newValue);
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("inputOrder", powermap_getMasterOrder(hPm)-1);
    setParameterValue("powermapMode", powermap_getPowermapMode(hPm)-1);
    setParameterValue("covAvgCoeff", powermap_getCovAvgCoeff(hPm));
    setParameterValue("channelOrder", powermap_getChOrder(hPm)-1);
    setParameterValue("normType", powermap_getNormType(hPm)-1);
    setParameterValue("numSources", powermap_getNumSources(hPm));
    setParameterValue("FOVoption", powermap_getDispFOV(hPm)-1);
    setParameterValue("ARoption", powermap_getAspectRatio(hPm)-1);
    setParameterValue("mapAvg", powermap_getPowermapAvgCoeff(hPm));
}

void PluginProcessor::setInternalStateUsingParameterValues()
{
    powermap_setMasterOrder(hPm, getParameterChoice("inputOrder")+1);
    powermap_setAnaOrderAllBands(hPm, getParameterChoice("inputOrder")+1);
    powermap_setPowermapMode(hPm, getParameterChoice("powermapMode")+1);
    powermap_setCovAvgCoeff(hPm, getParameterFloat("covAvgCoeff"));
    powermap_setChOrder(hPm, getParameterChoice("channelOrder")+1);
    powermap_setNormType(hPm, getParameterChoice("normType")+1);
    powermap_setNumSources(hPm, getParameterInt("numSources"));
    powermap_setDispFOV(hPm, getParameterChoice("FOVoption")+1);
    powermap_setAspectRatio(hPm, getParameterChoice("ARoption")+1);
    powermap_setPowermapAvgCoeff(hPm, getParameterFloat("mapAvg"));
}

PluginProcessor::PluginProcessor() :
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
    powermap_create(&hPm);
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
    powermap_destroy(&hPm);
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

    powermap_init(hPm, nSampleRate);
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

    powermap_analysis(hPm, bufferData, nNumInputs, nCurrentBlockSize, isPlaying); 
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
    xmlState->setTagName("POWERMAPAUDIOPLUGINSETTINGS");
    xmlState->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10501
    
    /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
    for(int i=0; i<powermap_getNumberOfBands(); i++){
        xmlState->setAttribute("powermapEQ"+String(i), powermap_getPowermapEQ(hPm, i));
        xmlState->setAttribute("anaOrder"+String(i), powermap_getAnaOrder(hPm, i));
    }
    
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
    if (xmlState != nullptr && xmlState->hasTagName("POWERMAPAUDIOPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10501
            if(xmlState->hasAttribute("masterOrder"))
                powermap_setMasterOrder(hPm, xmlState->getIntAttribute("masterOrder", 1));
            if(xmlState->hasAttribute("powermapMode"))
                powermap_setPowermapMode(hPm, xmlState->getIntAttribute("powermapMode", 1));
            if(xmlState->hasAttribute("covAvgCoeff"))
                powermap_setCovAvgCoeff(hPm, (float)xmlState->getDoubleAttribute("covAvgCoeff", 0.5f));
            for(int i=0; i<powermap_getNumberOfBands(); i++){
                if(xmlState->hasAttribute("powermapEQ"+String(i)))
                    powermap_setPowermapEQ(hPm, (float)xmlState->getDoubleAttribute("powermapEQ"+String(i), 0.5f), i);
                if(xmlState->hasAttribute("anaOrder"+String(i)))
                    powermap_setAnaOrder(hPm, xmlState->getIntAttribute("anaOrder"+String(i), 1), i);
            }
            if(xmlState->hasAttribute("chOrder"))
                powermap_setChOrder(hPm, xmlState->getIntAttribute("chOrder", 1));
            if(xmlState->hasAttribute("normType"))
                powermap_setNormType(hPm, xmlState->getIntAttribute("normType", 1));
            if(xmlState->hasAttribute("numSources"))
                powermap_setNumSources(hPm, xmlState->getIntAttribute("numSources", 1));
            if(xmlState->hasAttribute("dispFov"))
                powermap_setDispFOV(hPm, xmlState->getIntAttribute("dispFov", 1));
            if(xmlState->hasAttribute("aspectRatio"))
                powermap_setAspectRatio(hPm, xmlState->getIntAttribute("aspectRatio", 1));
            if(xmlState->hasAttribute("powermapAvgCoeff"))
                powermap_setPowermapAvgCoeff(hPm, (float)xmlState->getDoubleAttribute("powermapAvgCoeff", 0.5f));
            
            /* Other */
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
            
            /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
            for(int i=0; i<powermap_getNumberOfBands(); i++){
                if(xmlState->hasAttribute("powermapEQ"+String(i)))
                    powermap_setPowermapEQ(hPm, (float)xmlState->getDoubleAttribute("powermapEQ"+String(i), 0.5f), i);
                if(xmlState->hasAttribute("anaOrder"+String(i)))
                    powermap_setAnaOrder(hPm, xmlState->getIntAttribute("anaOrder"+String(i), 1), i);
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
        
        powermap_refreshSettings(hPm);
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

