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
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("outputOrder", "OutputOrder",
                                                                  juce::StringArray{"1st order","2nd order","3rd order","4th order","5th order","6th order","7th order","8th order","9th order","10th order"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("channelOrder", "ChannelOrder", juce::StringArray{"ACN", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("normType", "NormType", juce::StringArray{"N3D", "SN3D", "FuMa"}, 1));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("filterType", "FilterType",
                                                                  juce::StringArray{"Soft-Limiting","Tikhonov","Z-style","Z-style (max_rE)"}, 1,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("maxGain", "MaxGain",
                                                                 juce::NormalisableRange<float>(ARRAY2SH_MAX_GAIN_MIN_VALUE, ARRAY2SH_MAX_GAIN_MAX_VALUE, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("postGain", "PostGain",
                                                                 juce::NormalisableRange<float>(ARRAY2SH_POST_GAIN_MIN_VALUE, ARRAY2SH_POST_GAIN_MAX_VALUE, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("speedOfSound", "SpeedOfSound",
                                                                 juce::NormalisableRange<float>(ARRAY2SH_SPEED_OF_SOUND_MIN_VALUE, ARRAY2SH_SPEED_OF_SOUND_MAX_VALUE, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("arrayRadius", "ArrayRadius", juce::NormalisableRange<float>(1.0f, 400.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("baffleRadius", "BaffleRadius", juce::NormalisableRange<float>(1.0f, 400.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("arrayType", "ArrayType", juce::StringArray{"Spherical","Cylindrical"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("weightType", "WeightType",
                                                                  juce::StringArray{"Rigid-Omni","Rigid-Card","Rigid-Dipole","Open-Omni","Open-Card","Open-Dipole"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numSensors", "NumSensors", 4, MAX_NUM_INPUTS, 1, AudioParameterIntAttributes().withAutomatable(false)));
    for(int i=0; i<MAX_NUM_INPUTS; i++){
        params.push_back(std::make_unique<juce::AudioParameterFloat>("azim" + juce::String(i), "Azim_" + juce::String(i+1), juce::NormalisableRange<float>(-360.0f, 360.0f, 0.01f), 0.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("elev" + juce::String(i), "Elev_" + juce::String(i+1), juce::NormalisableRange<float>(-180.0f, 180.0f, 0.01f), 0.0f));
    }
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "outputOrder"){
        array2sh_setEncodingOrder(hA2sh, static_cast<SH_ORDERS>(newValue+1.001f));
    }
    else if (parameterID == "channelOrder"){
        array2sh_setChOrder(hA2sh, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "normType"){
        array2sh_setNormType(hA2sh, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "filterType"){
        array2sh_setFilterType(hA2sh, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "maxGain"){
        array2sh_setRegPar(hA2sh, newValue);
    }
    else if (parameterID == "postGain"){
        array2sh_setGain(hA2sh, newValue);
    }
    else if (parameterID == "speedOfSound"){
        array2sh_setc(hA2sh, newValue);
    }
    else if (parameterID == "arrayRadius"){
        array2sh_setr(hA2sh, newValue/1000.0f);
    }
    else if (parameterID == "baffleRadius"){
        array2sh_setR(hA2sh, newValue/1000.0f);
    }
    else if (parameterID == "arrayType"){
        array2sh_setArrayType(hA2sh, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "weightType"){
        array2sh_setWeightType(hA2sh, static_cast<int>(newValue+1.001f));
    }
    else if(parameterID == "numSensors"){
        array2sh_setNumSensors(hA2sh, static_cast<int>(newValue));
    }
    for(int i=0; i<MAX_NUM_INPUTS; i++){
        if(parameterID == "azim" + juce::String(i)){
            array2sh_setSensorAzi_deg(hA2sh, i, newValue);
            break;
        }
        else if(parameterID == "elev" + juce::String(i)){
            array2sh_setSensorElev_deg(hA2sh, i, newValue);
            break;
        }
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("outputOrder", array2sh_getEncodingOrder(hA2sh)-1);
    setParameterValue("channelOrder", array2sh_getChOrder(hA2sh)-1);
    setParameterValue("normType", array2sh_getNormType(hA2sh)-1);
    setParameterValue("filterType", array2sh_getFilterType(hA2sh)-1);
    setParameterValue("maxGain", array2sh_getRegPar(hA2sh));
    setParameterValue("postGain", array2sh_getGain(hA2sh));
    setParameterValue("speedOfSound", array2sh_getc(hA2sh));
    setParameterValue("arrayRadius", array2sh_getr(hA2sh)*1000.0f);
    setParameterValue("baffleRadius", array2sh_getR(hA2sh)*1000.0f);
    setParameterValue("arrayType", array2sh_getArrayType(hA2sh)-1);
    setParameterValue("weightType", array2sh_getWeightType(hA2sh)-1);
    setParameterValue("numSensors", array2sh_getNumSensors(hA2sh));
    for(int i=0; i<MAX_NUM_INPUTS; i++){
        setParameterValue("azim" + juce::String(i), array2sh_getSensorAzi_deg(hA2sh, i));
        setParameterValue("elev" + juce::String(i), array2sh_getSensorElev_deg(hA2sh, i));
    }
}

PluginProcessor::PluginProcessor() : 
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	array2sh_create(&hA2sh);
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();
    
    startTimer(TIMER_PROCESSING_RELATED, 80);
}

PluginProcessor::~PluginProcessor()
{
	array2sh_destroy(&hA2sh);
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

    array2sh_init(hA2sh, nSampleRate);
    AudioProcessor::setLatencySamples(array2sh_getProcessingDelay());
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
    int frameSize = array2sh_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            array2sh_process(hA2sh, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
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
    xmlState->setTagName("ARRAY2SHPLUGINSETTINGS");
    
    /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
    xmlState->setAttribute("enableDiffPastAliasing", array2sh_getDiffEQpastAliasing(hA2sh));
    
    /* Other */
    xmlState->setAttribute("JSONFilePath", lastDir.getFullPathName());
    
    /* Save */
    copyXmlToBinary(*xmlState, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("ARRAY2SHPLUGINSETTINGS")){
        if(JucePlugin_VersionCode<0x10701){
            for(int i=0; i<array2sh_getMaxNumSensors(); i++){
                if(xmlState->hasAttribute("AziRad" + String(i)))
                    array2sh_setSensorAzi_rad(hA2sh, i, (float)xmlState->getDoubleAttribute("AziRad" + String(i), 0.0f));
                if(xmlState->hasAttribute("ElevRad" + String(i)))
                    array2sh_setSensorElev_rad(hA2sh, i, (float)xmlState->getDoubleAttribute("ElevRad" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("order"))
                array2sh_setEncodingOrder(hA2sh, xmlState->getIntAttribute("order", 1));
            if(xmlState->hasAttribute("Q"))
                array2sh_setNumSensors(hA2sh, xmlState->getIntAttribute("Q", 4));
            if(xmlState->hasAttribute("r"))
                array2sh_setr(hA2sh, (float)xmlState->getDoubleAttribute("r", 0.042));
            if(xmlState->hasAttribute("R"))
                array2sh_setR(hA2sh, (float)xmlState->getDoubleAttribute("R", 0.042));
            if(xmlState->hasAttribute("arrayType"))
                array2sh_setArrayType(hA2sh, xmlState->getIntAttribute("arrayType", 1));
            if(xmlState->hasAttribute("weightType"))
                array2sh_setWeightType(hA2sh, xmlState->getIntAttribute("weightType", 1));
            if(xmlState->hasAttribute("filterType"))
                array2sh_setFilterType(hA2sh, xmlState->getIntAttribute("filterType", 3));
            if(xmlState->hasAttribute("regPar"))
                array2sh_setRegPar(hA2sh, (float)xmlState->getDoubleAttribute("regPar", 15.0));
            if(xmlState->hasAttribute("chOrder"))
                array2sh_setChOrder(hA2sh, xmlState->getIntAttribute("chOrder", 1));
            if(xmlState->hasAttribute("normType"))
                array2sh_setNormType(hA2sh, xmlState->getIntAttribute("normType", 1));
            if(xmlState->hasAttribute("c"))
                array2sh_setc(hA2sh, (float)xmlState->getDoubleAttribute("c", 343.0));
            if(xmlState->hasAttribute("gain"))
                array2sh_setGain(hA2sh, (float)xmlState->getDoubleAttribute("gain", 0.0));
            //if(xmlState->hasAttribute("maxFreq"))
            //    array2sh_setMaxFreq(hA2sh, (float)xmlState->getDoubleAttribute("maxFreq", 20000.0));
            if(xmlState->hasAttribute("enableDiffPastAliasing"))
                array2sh_setDiffEQpastAliasing(hA2sh, xmlState->getIntAttribute("enableDiffPastAliasing", 0));
            
            if(xmlState->hasAttribute("JSONFilePath"))
                lastDir = xmlState->getStringAttribute("JSONFilePath", "");
            
            setParameterValuesUsingInternalState();
        }
        else{
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* Now for the other DSP object parameters (that have no JUCE parameter counterpart) */
            if(xmlState->hasAttribute("enableDiffPastAliasing"))
                array2sh_setDiffEQpastAliasing(hA2sh, xmlState->getIntAttribute("enableDiffPastAliasing", 0));
            
            /* Other */
            if(xmlState->hasAttribute("JSONFilePath"))
                lastDir = xmlState->getStringAttribute("JSONFilePath", "");
        }
        
        array2sh_refreshSettings(hA2sh);
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
    sensors.removeAllChildren(nullptr);
    for (int i=0; i<array2sh_getNumSensors(hA2sh);i++)
    {
        sensors.appendChild (ConfigurationHelper::
                             createElement(array2sh_getSensorAzi_deg(hA2sh, i),
                                           array2sh_getSensorElev_deg(hA2sh, i),
                                           1.0f, i+1, false, 1.0f), nullptr);
    }
    DynamicObject* jsonObj = new DynamicObject();
    jsonObj->setProperty("Name", var("SPARTA Array2SH sensor directions."));
    char versionString[10];
    strcpy(versionString, "v");
    strcat(versionString, JucePlugin_VersionString);
    jsonObj->setProperty("Description", var("This configuration file was created with the SPARTA Array2SH " + String(versionString) + " plug-in. " + Time::getCurrentTime().toString(true, true)));
    jsonObj->setProperty ("GenericLayout", ConfigurationHelper::convertElementsToVar (sensors, "Sensor Directions"));
    Result result = ConfigurationHelper::writeConfigurationToFile (destination, var (jsonObj));
}

/* Adapted from the AllRADecoder by Daniel Rudrich, (c) 2017 (GPLv3 license) */
void PluginProcessor::loadConfiguration (const File& configFile)
{
    int channelIDs[MAX_NUM_CHANNELS+1] = {0};
    int virtual_channelIDs[MAX_NUM_CHANNELS+1] = {0};
    sensors.removeAllChildren(nullptr);
    Result result = ConfigurationHelper::parseFileForGenericLayout (configFile, sensors, nullptr);
    if(result.wasOk()){
        int num_sensors, num_virtual_sensors, sensor_idx, jj;
        num_sensors = num_virtual_sensors = sensor_idx = jj = 0;
        /* get Channel IDs and find number of directions and virtual directions */
        for (ValueTree::Iterator it = sensors.begin(); it != sensors.end(); ++it){
            if ( !((*it).getProperty("Imaginary"))){
                num_sensors++; channelIDs[jj] = (*it).getProperty("Channel");
            }
            else{
                virtual_channelIDs[num_virtual_sensors] = (*it).getProperty("Channel");
                num_virtual_sensors++; channelIDs[jj] = -1;
            }
            jj++;
        }
        /* remove virtual channels and shift the channel indices down */
        for(int i=0; i<num_virtual_sensors; i++)
            for(int j=0; j<num_sensors+num_virtual_sensors; j++)
                if(channelIDs[j] == -1)
                    for(int k=j; k<num_sensors+num_virtual_sensors; k++)
                        channelIDs[k] = channelIDs[k+1];
        
        /* then decriment the channel IDs to remove the gaps */
        for(int i=0; i<num_virtual_sensors; i++)
            for(int j=0; j<num_sensors+num_virtual_sensors; j++)
                if( channelIDs[j] > virtual_channelIDs[i]-i )
                    channelIDs[j]--;
        
        /* update with the new configuration  */
        setParameterValue("numSensors", num_sensors);
        for (ValueTree::Iterator it = sensors.begin() ; it != sensors.end(); ++it){
            if ( !((*it).getProperty("Imaginary"))){
                float azimValue = (float)(*it).getProperty("Azimuth");
                float elevValue = (float)(*it).getProperty("Elevation");
                setParameterValue("azim" + juce::String(channelIDs[sensor_idx]-1), azimValue);
                setParameterValue("elev" + juce::String(channelIDs[sensor_idx]-1), elevValue);
                sensor_idx++;
            }
        }
    }
}
