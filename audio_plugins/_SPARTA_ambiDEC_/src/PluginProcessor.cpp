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
                                                                  juce::StringArray{"1st","2nd","3rd","4th","5th","6th","7th","8th","9th","10th"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("channelOrder", "ChannelOrder", juce::StringArray{"ACN", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("normType", "NormType", juce::StringArray{"N3D", "SN3D", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("decMethod1", "DecMethod1", juce::StringArray{"SAD","MMD","EPAD","AllRAD"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("decMethod2", "DecMethod2", juce::StringArray{"SAD","MMD","EPAD","AllRAD"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterBool>("enableMaxRE1", "EnableMaxRE1", false, AudioParameterBoolAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterBool>("enableMaxRE2", "EnableMaxRE2", false, AudioParameterBoolAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("diffEQ1", "DiffEQ1", juce::StringArray{"AP", "EP"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("diffEQ2", "DiffEQ2", juce::StringArray{"AP","EP"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("transitionFreq", "TransitionFreq", juce::NormalisableRange<float>(500.0f, 2000.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("binauraliseLS", "BinauraliseLS", false, AudioParameterBoolAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numLoudspeakers", "NumLoudspeakers", 1, MAX_NUM_OUTPUTS, 1,
                                                               AudioParameterIntAttributes().withAutomatable(false)));
    for(int i=0; i<MAX_NUM_OUTPUTS; i++){
        params.push_back(std::make_unique<juce::AudioParameterFloat>("azim" + juce::String(i), "Azim_" + juce::String(i+1), juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withAutomatable(false)));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("elev" + juce::String(i), "Elev_" + juce::String(i+1), juce::NormalisableRange<float>(-90.0f, 90.0f, 0.01f), 0.0f, AudioParameterFloatAttributes().withAutomatable(false)));
    }
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "inputOrder"){
        ambi_dec_setMasterDecOrder(hAmbi, static_cast<int>(newValue+1.001f));
        ambi_dec_setDecOrderAllBands(hAmbi, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "channelOrder"){
        ambi_dec_setChOrder(hAmbi, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "normType"){
        ambi_dec_setNormType(hAmbi, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "decMethod1"){
        ambi_dec_setDecMethod(hAmbi, 0, static_cast<AMBI_DEC_DECODING_METHODS>(newValue+1.001f));
    }
    else if (parameterID == "decMethod2"){
        ambi_dec_setDecMethod(hAmbi, 1, static_cast<AMBI_DEC_DECODING_METHODS>(newValue+1.001f));
    }
    else if (parameterID == "enableMaxRE1"){
        ambi_dec_setDecEnableMaxrE(hAmbi, 0, static_cast<int>(newValue+0.5f));
    }
    else if (parameterID == "enableMaxRE2"){
        ambi_dec_setDecEnableMaxrE(hAmbi, 1, static_cast<int>(newValue+0.5f));
    }
    else if (parameterID == "diffEQ1"){
        ambi_dec_setDecNormType(hAmbi, 0, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "diffEQ2"){
        ambi_dec_setDecNormType(hAmbi, 1, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "transitionFreq"){
        ambi_dec_setTransitionFreq(hAmbi, newValue);
    }
    else if (parameterID == "binauraliseLS"){
        ambi_dec_setBinauraliseLSflag(hAmbi, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "numLoudspeakers"){
        ambi_dec_setNumLoudspeakers(hAmbi, static_cast<int>(newValue));
    }
    for(int i=0; i<MAX_NUM_OUTPUTS; i++){
        if(parameterID == "azim" + juce::String(i)){
            ambi_dec_setLoudspeakerAzi_deg(hAmbi, i, newValue);
            break;
        }
        else if(parameterID == "elev" + juce::String(i)){
            ambi_dec_setLoudspeakerElev_deg(hAmbi, i, newValue);
            break;
        }
    }
}

PluginProcessor::PluginProcessor() :
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	ambi_dec_create(&hAmbi);
    
    /* Grab defaults */
    setParameterValue("inputOrder", ambi_dec_getMasterDecOrder(hAmbi)-1, false);
    setParameterValue("channelOrder", ambi_dec_getChOrder(hAmbi)-1, false);
    setParameterValue("normType", ambi_dec_getNormType(hAmbi)-1, false);
    setParameterValue("decMethod1", ambi_dec_getDecMethod(hAmbi, 0)-1, false);
    setParameterValue("decMethod2", ambi_dec_getDecMethod(hAmbi, 1)-1, false);
    setParameterValue("enableMaxRE1", ambi_dec_getDecEnableMaxrE(hAmbi, 0), false);
    setParameterValue("enableMaxRE2", ambi_dec_getDecEnableMaxrE(hAmbi, 1), false);
    setParameterValue("diffEQ1", ambi_dec_getDecNormType(hAmbi, 0)-1, false);
    setParameterValue("diffEQ2", ambi_dec_getDecNormType(hAmbi, 1)-1, false);
    setParameterValue("transitionFreq", ambi_dec_getTransitionFreq(hAmbi), false);
    setParameterValue("binauraliseLS", ambi_dec_getBinauraliseLSflag(hAmbi), false);
    setParameterValue("numLoudspeakers", ambi_dec_getNumLoudspeakers(hAmbi), false);
    for(int i=0; i<MAX_NUM_OUTPUTS; i++){
        setParameterValue("azim" + juce::String(i), ambi_dec_getLoudspeakerAzi_deg(hAmbi, i), false);
        setParameterValue("elev" + juce::String(i), ambi_dec_getLoudspeakerElev_deg(hAmbi, i), false);
    }
    
    startTimer(TIMER_PROCESSING_RELATED, 80);
}

PluginProcessor::~PluginProcessor()
{
	ambi_dec_destroy(&hAmbi);
}

void PluginProcessor::setCurrentProgram (int  /*index*/)
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

    ambi_dec_init(hAmbi, nSampleRate);
    AudioProcessor::setLatencySamples(ambi_dec_getProcessingDelay());
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
    int frameSize = ambi_dec_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            ambi_dec_process(hAmbi, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
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
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    xml->setTagName("AMBIDECPLUGINSETTINGS");
    
    /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
    for(int band=0; band<ambi_dec_getNumberOfBands(); band++)
        xml->setAttribute("DecOrder"+String(band), ambi_dec_getDecOrder(hAmbi, band));
    xml->setAttribute("UseDefaultHRIRset", ambi_dec_getUseDefaultHRIRsflag(hAmbi));
    xml->setAttribute("preProcHRIRs", ambi_dec_getEnableHRIRsPreProc(hAmbi));
    if(!ambi_dec_getUseDefaultHRIRsflag(hAmbi))
        xml->setAttribute("SofaFilePath", String(ambi_dec_getSofaFilePath(hAmbi)));
    
    /* Other */
    xml->setAttribute("JSONFilePath", lastDir.getFullPathName());
    
    /* Save */
    copyXmlToBinary(*xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("AMBIDECPLUGINSETTINGS") && JucePlugin_VersionCode>=0x10701){
        parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
        
        /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
        for(int band=0; band<ambi_dec_getNumberOfBands(); band++)
            if(xmlState->hasAttribute("DecOrder"+String(band)))
                ambi_dec_setDecOrder(hAmbi, xmlState->getIntAttribute("DecOrder"+String(band),1), band);
        if(xmlState->hasAttribute("UseDefaultHRIRset"))
            ambi_dec_setUseDefaultHRIRsflag(hAmbi, xmlState->getIntAttribute("UseDefaultHRIRset", 1));
        if(xmlState->hasAttribute("preProcHRIRs"))
            ambi_dec_setEnableHRIRsPreProc(hAmbi, xmlState->getIntAttribute("preProcHRIRs", 1));
        if(xmlState->hasAttribute("SofaFilePath")){
            String directory = xmlState->getStringAttribute("SofaFilePath", "no_file");
            const char* new_cstring = (const char*)directory.toUTF8();
            ambi_dec_setSofaFilePath(hAmbi, new_cstring);
        }
        
        /* Other */
        if(xmlState->hasAttribute("JSONFilePath"))
            lastDir = xmlState->getStringAttribute("JSONFilePath", "");
        
        ambi_dec_refreshSettings(hAmbi);
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
    loudspeakers.removeAllChildren(nullptr);
    for (int i=0; i<ambi_dec_getNumLoudspeakers(hAmbi);i++)
    {
        loudspeakers.appendChild (ConfigurationHelper::
                                  createElement(ambi_dec_getLoudspeakerAzi_deg(hAmbi, i),
                                              ambi_dec_getLoudspeakerElev_deg(hAmbi, i),
                                              1.0f,
                                              i+1,
                                              false,
                                              1.0f), nullptr);
    }
    DynamicObject* jsonObj = new DynamicObject();
    jsonObj->setProperty("Name", var("SPARTA AmbiDEC loudspeaker directions."));
    char versionString[10];
    strcpy(versionString, "v");
    strcat(versionString, JucePlugin_VersionString);
    jsonObj->setProperty("Description", var("This configuration file was created with the SPARTA AmbiDEC " + String(versionString) + " plug-in. " + Time::getCurrentTime().toString(true, true)));
    jsonObj->setProperty ("LoudspeakerLayout", ConfigurationHelper::convertLoudspeakersToVar (loudspeakers, "Loudspeaker Directions"));
    Result result = ConfigurationHelper::writeConfigurationToFile (destination, var (jsonObj));
}

/* Adapted from the AllRADecoder by Daniel Rudrich, (c) 2017 (GPLv3 license) */
void PluginProcessor::loadConfiguration (const File& configFile)
{
    int channelIDs[MAX_NUM_CHANNELS+1] = {0};
    int virtual_channelIDs[MAX_NUM_CHANNELS+1] = {0};
    loudspeakers.removeAllChildren(nullptr);
    Result result = ConfigurationHelper::parseFileForLoudspeakerLayout (configFile, loudspeakers, nullptr);
    if(result.wasOk()){
        int num_ls, num_virtual_ls, ls_idx, jj;
        num_ls = num_virtual_ls = ls_idx = jj = 0;
        /* get Channel IDs and find number of directions and virtual directions */
        for (ValueTree::Iterator it = loudspeakers.begin(); it != loudspeakers.end(); ++it){
            if ( !((*it).getProperty("Imaginary"))){
                num_ls++; channelIDs[jj] = (*it).getProperty("Channel");
            }
            else{
                virtual_channelIDs[num_virtual_ls] = (*it).getProperty("Channel");
                num_virtual_ls++; channelIDs[jj] = -1;
            }
            jj++;
        }
        /* remove virtual channels and shift the channel indices down */
        for(int i=0; i<num_virtual_ls; i++)
            for(int j=0; j<num_ls+num_virtual_ls; j++)
                if(channelIDs[j] == -1)
                    for(int k=j; k<num_ls+num_virtual_ls; k++)
                        channelIDs[k] = channelIDs[k+1];
        
        /* then decriment the channel IDs to remove the gaps */
        for(int i=0; i<num_virtual_ls; i++)
            for(int j=0; j<num_ls+num_virtual_ls; j++)
                if( channelIDs[j] > virtual_channelIDs[i]-i )
                    channelIDs[j]--;
        
        /* update with the new configuration  */
        ambi_dec_setNumLoudspeakers(hAmbi, num_ls);
        for (ValueTree::Iterator it = loudspeakers.begin() ; it != loudspeakers.end(); ++it){
            if ( !((*it).getProperty("Imaginary"))){
                ambi_dec_setLoudspeakerAzi_deg(hAmbi, channelIDs[ls_idx]-1, (*it).getProperty("Azimuth"));
                ambi_dec_setLoudspeakerElev_deg(hAmbi, channelIDs[ls_idx]-1, (*it).getProperty("Elevation"));
                ls_idx++;
            }
        }
    } 
}
