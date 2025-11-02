/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2021 - Leo McCormack.
 
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

    params.push_back(std::make_unique<juce::AudioParameterChoice>("procMode", "ProcMode",
                                                                  juce::StringArray{"Basic","OM","EVD"}, 1,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("avgCoeff", "AvgCoeff", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.85f));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numInputs", "NumInputs", 1, SPREADER_MAX_NUM_SOURCES, 1, AudioParameterIntAttributes().withAutomatable(false)));
    for(int i=0; i<SPREADER_MAX_NUM_SOURCES; i++){
        params.push_back(std::make_unique<juce::AudioParameterFloat>("azim" + juce::String(i), "Azim_" + juce::String(i+1), juce::NormalisableRange<float>(-180.0f, 180.0f, 0.1f), 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("elev" + juce::String(i), "Elev_" + juce::String(i+1), juce::NormalisableRange<float>(-90.0f, 90.0f, 0.1f), 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("spread" + juce::String(i), "Spread_" + juce::String(i+1), juce::NormalisableRange<float>(0.0f, 360.0f, 1.0f), 0.0f));
    }
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "procMode"){
        spreader_setSpreadingMode(hSpr, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "avgCoeff"){
        spreader_setAveragingCoeff(hSpr, newValue);
    }
    else if(parameterID == "numInputs"){
        spreader_setNumSources(hSpr, static_cast<int>(newValue));
    }
    for(int i=0; i<SPREADER_MAX_NUM_SOURCES; i++){
        if(parameterID == "azim" + juce::String(i)){
            spreader_setSourceAzi_deg(hSpr, i, newValue);
            setRefreshWindow(true);
            break;
        }
        else if(parameterID == "elev" + juce::String(i)){
            spreader_setSourceElev_deg(hSpr, i, newValue);
            setRefreshWindow(true);
            break;
        }
        else if(parameterID == "spread" + juce::String(i)){
            spreader_setSourceSpread_deg(hSpr, i, newValue);
            setRefreshWindow(true);
            break;
        }
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("procMode", spreader_getSpreadingMode(hSpr)-1);
    setParameterValue("avgCoeff", spreader_getAveragingCoeff(hSpr));
    setParameterValue("numInputs", spreader_getNumSources(hSpr));
    for(int i=0; i<SPREADER_MAX_NUM_SOURCES; i++){
        setParameterValue("azim" + juce::String(i), spreader_getSourceAzi_deg(hSpr, i));
        setParameterValue("elev" + juce::String(i), spreader_getSourceElev_deg(hSpr, i));
        setParameterValue("spread" + juce::String(i), spreader_getSourceSpread_deg(hSpr, i));
    }
}

void PluginProcessor::setInternalStateUsingParameterValues()
{
    spreader_setSpreadingMode(hSpr, getParameterChoice("procMode")+1);
    spreader_setAveragingCoeff(hSpr, getParameterFloat("avgCoeff"));
    spreader_setNumSources(hSpr, getParameterInt("numInputs"));
    for(int i=0; i<SPREADER_MAX_NUM_SOURCES; i++){
        spreader_setSourceAzi_deg(hSpr, i, getParameterFloat("azim" + juce::String(i)));
        spreader_setSourceElev_deg(hSpr, i, getParameterFloat("elev" + juce::String(i)));
        spreader_setSourceSpread_deg(hSpr, i, getParameterFloat("spread" + juce::String(i)));
    }
    setRefreshWindow(true);
}

PluginProcessor::PluginProcessor() :
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	spreader_create(&hSpr);
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();

    refreshWindow = true;
    startTimer(80);
}

PluginProcessor::~PluginProcessor()
{
	spreader_destroy(&hSpr);
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
    
	spreader_init(hSpr, nSampleRate);
    AudioProcessor::setLatencySamples(spreader_getProcessingDelay());
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
    int frameSize = spreader_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            spreader_process(hSpr, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
        }
    }
    else
        buffer.clear();
}

//==============================================================================
bool PluginProcessor::hasEditor() const
{
    return true; 
}

AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (*this);
}

//==============================================================================
void PluginProcessor::getStateInformation (MemoryBlock& destData)
{
    juce::ValueTree state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xmlState(state.createXml());
    xmlState->setTagName("SPREADERPLUGINSETTINGS");
    xmlState->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10101
    
    /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
    xmlState->setAttribute("UseDefaultHRIRset", spreader_getUseDefaultHRIRsflag(hSpr));
    if(!spreader_getUseDefaultHRIRsflag(hSpr))
        xmlState->setAttribute("SofaFilePath", String(spreader_getSofaFilePath(hSpr)));
    
    /* Save */
    copyXmlToBinary(*xmlState, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("SPREADERPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10101
            for(int i=0; i<spreader_getMaxNumSources(); i++){
                if(xmlState->hasAttribute("SourceAziDeg" + String(i)))
                    spreader_setSourceAzi_deg(hSpr, i, (float)xmlState->getDoubleAttribute("SourceAziDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceElevDeg" + String(i)))
                    spreader_setSourceElev_deg(hSpr, i, (float)xmlState->getDoubleAttribute("SourceElevDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceSpreadDeg" + String(i)))
                    spreader_setSourceSpread_deg(hSpr, i, (float)xmlState->getDoubleAttribute("SourceSpreadDeg" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("nSources"))
                spreader_setNumSources(hSpr, xmlState->getIntAttribute("nSources", 1));
            if(xmlState->hasAttribute("procMode"))
                spreader_setSpreadingMode(hSpr, xmlState->getIntAttribute("procMode", 1));
            if(xmlState->hasAttribute("avgCoeff"))
                spreader_setAveragingCoeff(hSpr, xmlState->getDoubleAttribute("avgCoeff", 0.5f));

            if(xmlState->hasAttribute("SofaFilePath")){
                String directory = xmlState->getStringAttribute("SofaFilePath", "no_file");
                const char* new_cstring = (const char*)directory.toUTF8();
                spreader_setSofaFilePath(hSpr, new_cstring);
            }
            
            setParameterValuesUsingInternalState();
        }
        else if(xmlState->getIntAttribute("VersionCode")>=0x10101){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
            if(xmlState->hasAttribute("UseDefaultHRIRset"))
                spreader_setUseDefaultHRIRsflag(hSpr, xmlState->getIntAttribute("UseDefaultHRIRset", 1));
            if(xmlState->hasAttribute("SofaFilePath")){
                String directory = xmlState->getStringAttribute("SofaFilePath", "no_file");
                const char* new_cstring = (const char*)directory.toUTF8();
                spreader_setSofaFilePath(hSpr, new_cstring);
            }
            
            /* Many hosts will also trigger parameterChanged() for all parameters after calling setStateInformation() */
            /* However, some hosts do not. Therefore, it is better to ensure that the internal state is always up-to-date by calling: */
            setInternalStateUsingParameterValues();
        }
        
        spreader_refreshSettings(hSpr);
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
} 
