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
		.withInput("Input", AudioChannelSet::discreteChannels(64), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(64), true))
{
	ambi_enc_create(&hAmbi);
    refreshWindow = true;
}

PluginProcessor::~PluginProcessor()
{
	ambi_enc_destroy(&hAmbi);
}

void PluginProcessor::setParameter (int index, float newValue)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_outputOrder:   ambi_enc_setOutputOrder(hAmbi, (SH_ORDERS)(int)(newValue*(float)(MAX_SH_ORDER-1) + 1.5f)); break;
            case k_channelOrder:  ambi_enc_setChOrder(hAmbi, (int)(newValue*(float)(NUM_CH_ORDERINGS-1) + 1.5f)); break;
            case k_normType:      ambi_enc_setNormType(hAmbi, (int)(newValue*(float)(NUM_NORM_TYPES-1) + 1.5f)); break;
            case k_numSources:    ambi_enc_setNumSources(hAmbi, (int)(newValue*(float)(MAX_NUM_INPUTS)+0.5)); break;
        }
    }
    /* source direction parameters */
    else{
        index-=k_NumOfParameters;
        float newValueScaled;
        if (!(index % 2)){
            newValueScaled = (newValue - 0.5f)*360.0f;
            if (newValueScaled != ambi_enc_getSourceAzi_deg(hAmbi, index/2)){
                ambi_enc_setSourceAzi_deg(hAmbi, index/2, newValueScaled);
                refreshWindow = true;
            }
        }
        else{
            newValueScaled = (newValue - 0.5f)*180.0f;
            if (newValueScaled != ambi_enc_getSourceElev_deg(hAmbi, index/2)){
                ambi_enc_setSourceElev_deg(hAmbi, index/2, newValueScaled);
                refreshWindow = true;
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
            case k_outputOrder:   return (float)(ambi_enc_getOutputOrder(hAmbi)-1)/(float)(MAX_SH_ORDER-1);
            case k_channelOrder:  return (float)(ambi_enc_getChOrder(hAmbi)-1)/(float)(NUM_CH_ORDERINGS-1);
            case k_normType:      return (float)(ambi_enc_getNormType(hAmbi)-1)/(float)(NUM_NORM_TYPES-1);
            case k_numSources:    return (float)(ambi_enc_getNumSources(hAmbi))/(float)(MAX_NUM_INPUTS);
            default: return 0.0f;
        }
    }
    /* source direction parameters */
    else{
        index-=k_NumOfParameters;
        if (!(index % 2))
            return (ambi_enc_getSourceAzi_deg(hAmbi, index/2)/360.0f) + 0.5f;
        else
            return (ambi_enc_getSourceElev_deg(hAmbi, (index-1)/2)/180.0f) + 0.5f;
    }
}

int PluginProcessor::getNumParameters()
{
	return k_NumOfParameters + 2*MAX_NUM_INPUTS;
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
            case k_outputOrder:  return "order";
            case k_channelOrder: return "channel_order";
            case k_normType:     return "norm_type";
            case k_numSources:   return "num_sources";
            default: return "NULL";
        }
    }
    /* source direction parameters */
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
            case k_outputOrder: return String(ambi_enc_getOutputOrder(hAmbi));
            case k_channelOrder:
                switch(ambi_enc_getChOrder(hAmbi)){
                    case CH_ACN:  return "ACN";
                    case CH_FUMA: return "FuMa";
                    default: return "NULL";
                }
            case k_normType:
                switch(ambi_enc_getNormType(hAmbi)){
                    case NORM_N3D:  return "N3D";
                    case NORM_SN3D: return "SN3D";
                    case NORM_FUMA: return "FuMa";
                    default: return "NULL";
                }
            case k_numSources: return String(ambi_enc_getNumSources(hAmbi));
            default: return "NULL";
        }
    }
    /* source direction parameters */
    else{
        index-=k_NumOfParameters;
        if (!(index % 2))
            return String(ambi_enc_getSourceAzi_deg(hAmbi, index/2));
        else
            return String(ambi_enc_getSourceElev_deg(hAmbi, (index-1)/2));
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
    nNumInputs =  getTotalNumInputChannels();
    nNumOutputs = getTotalNumOutputChannels();
    nSampleRate = (int)(sampleRate + 0.5);

	ambi_enc_init(hAmbi, nSampleRate);
    AudioProcessor::setLatencySamples(ambi_enc_getProcessingDelay());
}

void PluginProcessor::releaseResources()
{
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels());
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels());
    float** bufferData = buffer.getArrayOfWritePointers();
    float* pFrameData[MAX_NUM_CHANNELS];
    int frameSize = ambi_enc_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < buffer.getNumChannels(); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            ambi_enc_process(hAmbi, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
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
    XmlElement xml("AMBIENCPLUGINSETTINGS");
    for(int i=0; i<ambi_enc_getMaxNumSources(); i++){
        xml.setAttribute("SourceAziDeg" + String(i), ambi_enc_getSourceAzi_deg(hAmbi,i));
        xml.setAttribute("SourceElevDeg" + String(i), ambi_enc_getSourceElev_deg(hAmbi,i));
    }
    
    xml.setAttribute("JSONFilePath", lastDir.getFullPathName());
    xml.setAttribute("NORM", ambi_enc_getNormType(hAmbi));
    xml.setAttribute("CHORDER", ambi_enc_getChOrder(hAmbi));
    xml.setAttribute("OUT_ORDER", ambi_enc_getOutputOrder(hAmbi));
    xml.setAttribute("nSources", ambi_enc_getNumSources(hAmbi));

    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr) {
        if (xmlState->hasTagName("AMBIENCPLUGINSETTINGS")) {
            for(int i=0; i<ambi_enc_getMaxNumSources(); i++){
                if(xmlState->hasAttribute("SourceAziDeg" + String(i)))
                    ambi_enc_setSourceAzi_deg(hAmbi, i, (float)xmlState->getDoubleAttribute("SourceAziDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceElevDeg" + String(i)))
                    ambi_enc_setSourceElev_deg(hAmbi, i, (float)xmlState->getDoubleAttribute("SourceElevDeg" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("nSources"))
                ambi_enc_setNumSources(hAmbi, xmlState->getIntAttribute("nSources", 1));
            
            if(xmlState->hasAttribute("JSONFilePath"))
                lastDir = xmlState->getStringAttribute("JSONFilePath", "");

            if(xmlState->hasAttribute("NORM"))
                ambi_enc_setNormType(hAmbi, xmlState->getIntAttribute("NORM", 1));
            if(xmlState->hasAttribute("CHORDER"))
                ambi_enc_setChOrder(hAmbi, xmlState->getIntAttribute("CHORDER", 1));
            if(xmlState->hasAttribute("OUT_ORDER"))
                ambi_enc_setOutputOrder(hAmbi, xmlState->getIntAttribute("OUT_ORDER", 1));
            
            ambi_enc_refreshParams(hAmbi);
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
    sources.removeAllChildren(nullptr);
    for (int i=0; i<ambi_enc_getNumSources(hAmbi);i++)
    {
        sources.appendChild (ConfigurationHelper::
                             createElement(ambi_enc_getSourceAzi_deg(hAmbi, i),
                                          ambi_enc_getSourceElev_deg(hAmbi, i),
                                          1.0f, i+1, false, 1.0f), nullptr);
    }
    DynamicObject* jsonObj = new DynamicObject();
    jsonObj->setProperty("Name", var("SPARTA AmbiENC source directions."));
    char versionString[10];
    strcpy(versionString, "v");
    strcat(versionString, JucePlugin_VersionString);
    jsonObj->setProperty("Description", var("This configuration file was created with the SPARTA AmbiENC " + String(versionString) + " plug-in. " + Time::getCurrentTime().toString(true, true)));
    jsonObj->setProperty ("GenericLayout", ConfigurationHelper::convertElementsToVar (sources, "Source Directions"));
    Result result = ConfigurationHelper::writeConfigurationToFile (destination, var (jsonObj));
}

/* Adapted from the AllRADecoder by Daniel Rudrich, (c) 2017 (GPLv3 license) */
void PluginProcessor::loadConfiguration (const File& configFile)
{
    int channelIDs[MAX_NUM_CHANNELS+1] = {0};
    int virtual_channelIDs[MAX_NUM_CHANNELS+1] = {0};
    sources.removeAllChildren(nullptr);
    Result result = ConfigurationHelper::parseFileForGenericLayout(configFile, sources, nullptr);
    if(result.wasOk()){
        int num_srcs, num_virtual_srcs, src_idx, jj;
        num_srcs = num_virtual_srcs = src_idx = jj = 0;
        /* get Channel IDs and find number of directions and virtual directions */
        for (ValueTree::Iterator it = sources.begin(); it != sources.end(); ++it){
            if ( !((*it).getProperty("Imaginary"))){
                num_srcs++; channelIDs[jj] = (*it).getProperty("Channel");
            }
            else{
                virtual_channelIDs[num_virtual_srcs] = (*it).getProperty("Channel");
                num_virtual_srcs++; channelIDs[jj] = -1;
            }
            jj++;
        }
        /* remove virtual channels and shift the channel indices down */
        for(int i=0; i<num_virtual_srcs; i++)
            for(int j=0; j<num_srcs+num_virtual_srcs; j++)
                if(channelIDs[j] == -1)
                    for(int k=j; k<num_srcs+num_virtual_srcs; k++)
                        channelIDs[k] = channelIDs[k+1];
        
        /* then decriment the channel IDs to remove the gaps */
        for(int i=0; i<num_virtual_srcs; i++)
            for(int j=0; j<num_srcs+num_virtual_srcs; j++)
                if( channelIDs[j] > virtual_channelIDs[i]-i )
                    channelIDs[j]--;
        
        /* update with the new configuration  */
        ambi_enc_setNumSources(hAmbi, num_srcs);
        for (ValueTree::Iterator it = sources.begin() ; it != sources.end(); ++it){
            if ( !((*it).getProperty("Imaginary"))){
                ambi_enc_setSourceAzi_deg(hAmbi, channelIDs[src_idx]-1, (*it).getProperty("Azimuth"));
                ambi_enc_setSourceElev_deg(hAmbi, channelIDs[src_idx]-1, (*it).getProperty("Elevation"));
                src_idx++;
            }
        }
        refreshWindow=true;
    }
}

