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

PluginProcessor::PluginProcessor() : 
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(MAX_NUM_CHANNELS), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(MAX_NUM_CHANNELS), true))
{
	array2sh_create(&hA2sh);
    startTimer(TIMER_PROCESSING_RELATED, 80);
}

PluginProcessor::~PluginProcessor()
{
	array2sh_destroy(&hA2sh);
}

void PluginProcessor::setParameter (int index, float newValue)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_outputOrder:   array2sh_setEncodingOrder(hA2sh, (SH_ORDERS)(int)(newValue*(float)(MAX_SH_ORDER-1) + 1.5f)); break;
            case k_channelOrder:  array2sh_setChOrder(hA2sh, (int)(newValue*(float)(NUM_CH_ORDERINGS-1) + 1.5f)); break;
            case k_normType:      array2sh_setNormType(hA2sh, (int)(newValue*(float)(NUM_NORM_TYPES-1) + 1.5f)); break;
            case k_filterType:    array2sh_setFilterType(hA2sh, (ARRAY2SH_FILTER_TYPES)(int)(newValue*(float)(ARRAY2SH_NUM_FILTER_TYPES-1) + 1.5f)); break;
            case k_maxGain:       array2sh_setRegPar(hA2sh, newValue*(ARRAY2SH_MAX_GAIN_MAX_VALUE-ARRAY2SH_MAX_GAIN_MIN_VALUE)+ARRAY2SH_MAX_GAIN_MIN_VALUE); break;
            case k_postGain:      array2sh_setGain(hA2sh, newValue*(ARRAY2SH_POST_GAIN_MAX_VALUE-ARRAY2SH_POST_GAIN_MIN_VALUE)+ARRAY2SH_POST_GAIN_MIN_VALUE); break;
            case k_speedOfSound:  array2sh_setc(hA2sh, newValue*(ARRAY2SH_SPEED_OF_SOUND_MAX_VALUE-ARRAY2SH_SPEED_OF_SOUND_MIN_VALUE)+ARRAY2SH_SPEED_OF_SOUND_MIN_VALUE); break;
            case k_arrayRadius:   array2sh_setr(hA2sh, (newValue*(ARRAY2SH_ARRAY_RADIUS_MAX_VALUE-ARRAY2SH_ARRAY_RADIUS_MIN_VALUE)+ARRAY2SH_ARRAY_RADIUS_MIN_VALUE)/1e3f); break;
            case k_baffleRadius:  array2sh_setR(hA2sh, (newValue*(ARRAY2SH_BAFFLE_RADIUS_MAX_VALUE-ARRAY2SH_BAFFLE_RADIUS_MIN_VALUE)+ARRAY2SH_BAFFLE_RADIUS_MIN_VALUE)/1e3f); break;
            case k_arrayType:     array2sh_setArrayType(hA2sh, (ARRAY2SH_ARRAY_TYPES)(int)(newValue*(float)(ARRAY2SH_NUM_ARRAY_TYPES-1) + 1.5f)); break;
            case k_weightType:    array2sh_setWeightType(hA2sh, (ARRAY2SH_WEIGHT_TYPES)(int)(newValue*(float)(ARRAY2SH_NUM_WEIGHT_TYPES-1) + 1.5f)); break;
            case k_numSensors:    array2sh_setNumSensors(hA2sh, (int)(newValue*(float)(ARRAY2SH_MAX_NUM_SENSORS)+0.5)); break;
        }
    }
    /* sensor direction parameters */
    else{
        index-=k_NumOfParameters;
        float newValueScaled;
        if (!(index % 2)){
            newValueScaled = (newValue - 0.5f)*360.0f;
            if (newValueScaled != array2sh_getSensorAzi_deg(hA2sh, index/2)){
                array2sh_setSensorAzi_deg(hA2sh, index/2, newValueScaled);
            }
        }
        else{
            newValueScaled = (newValue - 0.5f)*180.0f;
            if (newValueScaled != array2sh_getSensorElev_deg(hA2sh, index/2)){
                array2sh_setSensorElev_deg(hA2sh, index/2, newValueScaled);
            }
        }
    }
}

void PluginProcessor::setCurrentProgram (int /*index*/)
{
}

float PluginProcessor::getParameter (int index)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_outputOrder:   return (float)(array2sh_getEncodingOrder(hA2sh)-1)/(float)(MAX_SH_ORDER-1);
            case k_channelOrder:  return (float)(array2sh_getChOrder(hA2sh)-1)/(float)(NUM_CH_ORDERINGS-1);
            case k_normType:      return (float)(array2sh_getNormType(hA2sh)-1)/(float)(NUM_NORM_TYPES-1);
            case k_filterType:    return (float)(array2sh_getFilterType(hA2sh)-1)/(float)(ARRAY2SH_NUM_FILTER_TYPES-1);
            case k_maxGain:       return (array2sh_getRegPar(hA2sh)-ARRAY2SH_MAX_GAIN_MIN_VALUE)/(ARRAY2SH_MAX_GAIN_MAX_VALUE-ARRAY2SH_MAX_GAIN_MIN_VALUE);
            case k_postGain:      return (array2sh_getGain(hA2sh)-ARRAY2SH_POST_GAIN_MIN_VALUE)/(ARRAY2SH_POST_GAIN_MAX_VALUE-ARRAY2SH_POST_GAIN_MIN_VALUE);
            case k_speedOfSound:  return (array2sh_getc(hA2sh)-ARRAY2SH_SPEED_OF_SOUND_MIN_VALUE)/(ARRAY2SH_SPEED_OF_SOUND_MAX_VALUE-ARRAY2SH_SPEED_OF_SOUND_MIN_VALUE);
            case k_arrayRadius:   return (/*m->mm*/1e3f*array2sh_getr(hA2sh)-ARRAY2SH_ARRAY_RADIUS_MIN_VALUE)/(ARRAY2SH_ARRAY_RADIUS_MAX_VALUE-ARRAY2SH_ARRAY_RADIUS_MIN_VALUE);
            case k_baffleRadius:  return (/*m->mm*/1e3f*array2sh_getR(hA2sh)-ARRAY2SH_BAFFLE_RADIUS_MIN_VALUE)/(ARRAY2SH_BAFFLE_RADIUS_MAX_VALUE-ARRAY2SH_BAFFLE_RADIUS_MIN_VALUE);
            case k_arrayType:     return (float)(array2sh_getArrayType(hA2sh)-1)/(float)(ARRAY2SH_NUM_ARRAY_TYPES-1);
            case k_weightType:    return (float)(array2sh_getWeightType(hA2sh)-1)/(float)(ARRAY2SH_NUM_WEIGHT_TYPES-1);
            case k_numSensors:    return (float)(array2sh_getNumSensors(hA2sh))/(float)(ARRAY2SH_MAX_NUM_SENSORS);
            default: return 0.0f;
        }
    }
    /* sensor direction parameters */
    else{
        index-=k_NumOfParameters;
        if (!(index % 2))
            return (array2sh_getSensorAzi_deg(hA2sh, index/2)/360.0f) + 0.5f;
        else
            return (array2sh_getSensorElev_deg(hA2sh, (index-1)/2)/180.0f) + 0.5f;
    }
}

int PluginProcessor::getNumParameters()
{
	return k_NumOfParameters + 2*ARRAY2SH_MAX_NUM_SENSORS;
}

const String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

const String PluginProcessor::getParameterName (int index)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_outputOrder:     return "order";
            case k_channelOrder:    return "channel_order";
            case k_normType:        return "norm_type";
            case k_filterType:      return "filter_type";
            case k_maxGain:         return "max_gain";
            case k_postGain:        return "post_gain";
            case k_speedOfSound:    return "speed_of_sound";
            case k_arrayRadius:     return "array_radius";
            case k_baffleRadius:    return "baffle_radius";
            case k_arrayType:       return "array_type";
            case k_weightType:      return "weight_type";
            case k_numSensors:      return "num_sensors";
            default: return "NULL";
        }
    }
    /* sensor direction parameters */
    else{
        index-=k_NumOfParameters;
        if (!(index % 2))
            return TRANS("Azim_") + String(index/2);
        else
            return TRANS("Elev_") + String((index-1)/2);
    }
}

const String PluginProcessor::getParameterText(int index)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_outputOrder: return String(array2sh_getEncodingOrder(hA2sh));
            case k_channelOrder:
                switch(array2sh_getChOrder(hA2sh)){
                    case CH_ACN:  return "ACN";
                    case CH_FUMA: return "FuMa";
                    default: return "NULL";
                }
            case k_normType:
                switch(array2sh_getNormType(hA2sh)){
                    case NORM_N3D:  return "N3D";
                    case NORM_SN3D: return "SN3D";
                    case NORM_FUMA: return "FuMa";
                    default: return "NULL";
                }
                
            case k_filterType:
                switch(array2sh_getFilterType(hA2sh)){
                    case FILTER_SOFT_LIM:      return "Soft-Limiting";
                    case FILTER_TIKHONOV:      return "Tikhonov";
                    case FILTER_Z_STYLE:       return "Z-style";
                    case FILTER_Z_STYLE_MAXRE: return "Z-style (max_rE)";
                    default: return "NULL";
                }
            case k_maxGain:      return String(array2sh_getRegPar(hA2sh)) + " dB";
            case k_postGain:     return String(array2sh_getGain(hA2sh)) + " dB";
            case k_speedOfSound: return String(array2sh_getc(hA2sh)) + " m/s";
            case k_arrayRadius:  return String(/*m->mm*/1e3f*array2sh_getr(hA2sh)) + " mm";
            case k_baffleRadius: return String(/*m->mm*/1e3f*array2sh_getR(hA2sh)) + " mm";
            case k_arrayType:
                switch(array2sh_getArrayType(hA2sh)){
                    case ARRAY_SPHERICAL:   return "Spherical";
                    case ARRAY_CYLINDRICAL: return "Cylindrical";
                    default: return "NULL";
                }
            case k_weightType:
                switch(array2sh_getWeightType(hA2sh)){
                    case WEIGHT_RIGID_OMNI:   return "Rigid-Omni";
                    case WEIGHT_RIGID_CARD:   return "Rigid-Card";
                    case WEIGHT_RIGID_DIPOLE: return "Rigid-Dipole";
                    case WEIGHT_OPEN_OMNI:    return "Open-Omni";
                    case WEIGHT_OPEN_CARD:    return "Open-Card";
                    case WEIGHT_OPEN_DIPOLE:  return "Open-Dipole";
                    default: return "NULL";
                }
            case k_numSensors: return String(array2sh_getNumSensors(hA2sh));
            default: return "NULL";
        }
    }
    /* sensor direction parameters */
    else{
        index-=k_NumOfParameters;
        if (!(index % 2))
            return String(array2sh_getSensorAzi_deg(hA2sh, index/2));
        else
            return String(array2sh_getSensorElev_deg(hA2sh, (index-1)/2));
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
    XmlElement xml("ARRAY2SHPLUGINSETTINGS");
    
    xml.setAttribute("order", array2sh_getEncodingOrder(hA2sh));
    xml.setAttribute("Q", array2sh_getNumSensors(hA2sh));
    for(int i=0; i<MAX_NUM_CHANNELS; i++){
        xml.setAttribute("AziRad" + String(i), array2sh_getSensorAzi_rad(hA2sh,i));
        xml.setAttribute("ElevRad" + String(i), array2sh_getSensorElev_rad(hA2sh,i));
    }
    xml.setAttribute("r", array2sh_getr(hA2sh));
    xml.setAttribute("R", array2sh_getR(hA2sh));
    xml.setAttribute("arrayType", array2sh_getArrayType(hA2sh));
    xml.setAttribute("weightType", array2sh_getWeightType(hA2sh));
    xml.setAttribute("filterType", array2sh_getFilterType(hA2sh));
    xml.setAttribute("regPar", array2sh_getRegPar(hA2sh));
    xml.setAttribute("chOrder", array2sh_getChOrder(hA2sh));
    xml.setAttribute("normType", array2sh_getNormType(hA2sh));
    xml.setAttribute("c", array2sh_getc(hA2sh));
    xml.setAttribute("gain", array2sh_getGain(hA2sh));
    //xml.setAttribute("maxFreq", array2sh_getMaxFreq(hA2sh));
    xml.setAttribute("enableDiffPastAliasing", array2sh_getDiffEQpastAliasing(hA2sh));
    
    xml.setAttribute("JSONFilePath", lastDir.getFullPathName());
    
    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    int i;
    
    if (xmlState != nullptr) {
        if (xmlState->hasTagName("ARRAY2SHPLUGINSETTINGS")) {
            for(i=0; i<array2sh_getMaxNumSensors(); i++){
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
            
            array2sh_refreshSettings(hA2sh);
        }
    }
}

//==============================================================================
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
        array2sh_setNumSensors(hA2sh, num_sensors);
        for (ValueTree::Iterator it = sensors.begin() ; it != sensors.end(); ++it){
            if ( !((*it).getProperty("Imaginary"))){
                array2sh_setSensorAzi_deg(hA2sh, channelIDs[sensor_idx]-1, (*it).getProperty("Azimuth"));
                array2sh_setSensorElev_deg(hA2sh, channelIDs[sensor_idx]-1, (*it).getProperty("Elevation"));
                sensor_idx++;
            }
        }
    }
}
