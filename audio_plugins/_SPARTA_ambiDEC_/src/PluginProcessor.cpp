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
	ambi_dec_create(&hAmbi);
    startTimer(TIMER_PROCESSING_RELATED, 80); 
}

PluginProcessor::~PluginProcessor()
{
	ambi_dec_destroy(&hAmbi);
}

void PluginProcessor::setParameter (int index, float newValue)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_inputOrder:      ambi_dec_setMasterDecOrder(hAmbi, (SH_ORDERS)(int)(newValue*(float)(MAX_SH_ORDER-1) + 1.5f));
                                    ambi_dec_setDecOrderAllBands(hAmbi, (newValue*(float)(MAX_SH_ORDER-1) + 1.5f)); break;
            case k_channelOrder:    ambi_dec_setChOrder(hAmbi, (int)(newValue*(float)(NUM_CH_ORDERINGS-1) + 1.5f)); break;
            case k_normType:        ambi_dec_setNormType(hAmbi, (int)(newValue*(float)(NUM_NORM_TYPES-1) + 1.5f)); break;
            case k_numLoudspeakers: ambi_dec_setNumLoudspeakers(hAmbi, (int)(newValue*(float)(MAX_NUM_OUTPUTS)+0.5)); break;
            case k_decMethod1:      ambi_dec_setDecMethod(hAmbi, 0, (AMBI_DEC_DECODING_METHODS)(int)(newValue*(float)(AMBI_DEC_NUM_DECODING_METHODS-1) + 1.5f)); break;
            case k_decMethod2:      ambi_dec_setDecMethod(hAmbi, 1, (AMBI_DEC_DECODING_METHODS)(int)(newValue*(float)(AMBI_DEC_NUM_DECODING_METHODS-1) + 1.5f)); break;
            case k_maxREweight1:    ambi_dec_setDecEnableMaxrE(hAmbi, 0, (int)(newValue+0.5f)); break;
            case k_maxREweight2:    ambi_dec_setDecEnableMaxrE(hAmbi, 1, (int)(newValue+0.5f)); break;
            case k_diffEQ1:         ambi_dec_setDecNormType(hAmbi, 0, (int)(newValue+1.5f)); break;
            case k_diffEQ2:         ambi_dec_setDecNormType(hAmbi, 1, (int)(newValue+1.5f)); break;
            case k_transitionFreq:  ambi_dec_setTransitionFreq(hAmbi, newValue*(AMBI_DEC_TRANSITION_MAX_VALUE-AMBI_DEC_TRANSITION_MIN_VALUE)+AMBI_DEC_TRANSITION_MIN_VALUE); break;
            case k_binauraliseLS:   ambi_dec_setBinauraliseLSflag(hAmbi, (int)(newValue+0.5f)); break;
        }
    }
    /* loudspeaker direction parameters */
    else{
        index-=k_NumOfParameters;
        float newValueScaled;
        if (!(index % 2)){
            newValueScaled = (newValue - 0.5f)*360.0f;
            if (newValueScaled != ambi_dec_getLoudspeakerAzi_deg(hAmbi, index/2)){
                ambi_dec_setLoudspeakerAzi_deg(hAmbi, index/2, newValueScaled);
            }
        }
        else{
            newValueScaled = (newValue - 0.5f)*180.0f;
            if (newValueScaled != ambi_dec_getLoudspeakerElev_deg(hAmbi, index/2)){
                ambi_dec_setLoudspeakerElev_deg(hAmbi, index/2, newValueScaled);
            }
        }
    }
}

void PluginProcessor::setCurrentProgram (int  /*index*/)
{
}

float PluginProcessor::getParameter (int index)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_inputOrder:      return (float)(ambi_dec_getMasterDecOrder(hAmbi)-1)/(float)(MAX_SH_ORDER-1);
            case k_channelOrder:    return (float)(ambi_dec_getChOrder(hAmbi)-1)/(float)(NUM_CH_ORDERINGS-1);
            case k_normType:        return (float)(ambi_dec_getNormType(hAmbi)-1)/(float)(NUM_NORM_TYPES-1);
            case k_numLoudspeakers: return (float)(ambi_dec_getNumLoudspeakers(hAmbi))/(float)(MAX_NUM_OUTPUTS);
            case k_decMethod1:      return (float)(ambi_dec_getDecMethod(hAmbi,0)-1)/(float)(AMBI_DEC_NUM_DECODING_METHODS-1);
            case k_decMethod2:      return (float)(ambi_dec_getDecMethod(hAmbi,1)-1)/(float)(AMBI_DEC_NUM_DECODING_METHODS-1);
            case k_maxREweight1:    return (float)(ambi_dec_getDecEnableMaxrE(hAmbi, 0));
            case k_maxREweight2:    return (float)(ambi_dec_getDecEnableMaxrE(hAmbi, 1));
            case k_diffEQ1:         return (float)(ambi_dec_getDecNormType(hAmbi, 0)-1);
            case k_diffEQ2:         return (float)(ambi_dec_getDecNormType(hAmbi, 1)-1);
            case k_transitionFreq:  return (ambi_dec_getTransitionFreq(hAmbi)-AMBI_DEC_TRANSITION_MIN_VALUE)/(AMBI_DEC_TRANSITION_MAX_VALUE-AMBI_DEC_TRANSITION_MIN_VALUE);
            case k_binauraliseLS:   return (float)(ambi_dec_getBinauraliseLSflag(hAmbi));
            default: return 0.0f;
        }
    }
    /* loudspeaker direction parameters */
    else{
        index-=k_NumOfParameters;
        if (!(index % 2))
            return (ambi_dec_getLoudspeakerAzi_deg(hAmbi, index/2)/360.0f) + 0.5f;
        else
            return (ambi_dec_getLoudspeakerElev_deg(hAmbi, (index-1)/2)/180.0f) + 0.5f;
    }
}

int PluginProcessor::getNumParameters()
{
	return k_NumOfParameters + 2*MAX_NUM_OUTPUTS;
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
            case k_inputOrder:      return "order";
            case k_channelOrder:    return "channel_order";
            case k_normType:        return "norm_type";
            case k_numLoudspeakers: return "num_loudspeakers";
            case k_decMethod1:      return "dec_method_LF";
            case k_decMethod2:      return "dec_method_HF";
            case k_maxREweight1:    return "maxre_weight_LF";
            case k_maxREweight2:    return "maxre_weight_HF";
            case k_diffEQ1:         return "diffeq_LF";
            case k_diffEQ2:         return "diffeq_HF";
            case k_transitionFreq:  return "transition_freq";
            case k_binauraliseLS:   return "binauralise_ls";
            default: return "NULL";
        }
    }
    /* loudspeaker direction parameters */
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
            case k_inputOrder: return String(ambi_dec_getMasterDecOrder(hAmbi));
            case k_channelOrder:
                switch(ambi_dec_getChOrder(hAmbi)){
                    case CH_ACN:  return "ACN";
                    case CH_FUMA: return "FuMa";
                    default: return "NULL";
                }
            case k_normType:
                switch(ambi_dec_getNormType(hAmbi)){
                    case NORM_N3D:  return "N3D";
                    case NORM_SN3D: return "SN3D";
                    case NORM_FUMA: return "FuMa";
                    default: return "NULL";
                }
                
            case k_numLoudspeakers:  return String(ambi_dec_getNumLoudspeakers(hAmbi));
            case k_decMethod1:
                switch(ambi_dec_getDecMethod(hAmbi,0)){
                    case DECODING_METHOD_SAD:    return "SAD";
                    case DECODING_METHOD_MMD:    return "MMD";
                    case DECODING_METHOD_EPAD:   return "EPAD";
                    case DECODING_METHOD_ALLRAD: return "AllRAD";
                    default: return "NULL";
                }
            case k_decMethod2:
                switch(ambi_dec_getDecMethod(hAmbi,1)){
                    case DECODING_METHOD_SAD:    return "SAD";
                    case DECODING_METHOD_MMD:    return "MMD";
                    case DECODING_METHOD_EPAD:   return "EPAD";
                    case DECODING_METHOD_ALLRAD: return "AllRAD";
                    default: return "NULL";
                }
            case k_maxREweight1: return !ambi_dec_getDecEnableMaxrE(hAmbi, 0) ? "Off" : "On";
            case k_maxREweight2: return !ambi_dec_getDecEnableMaxrE(hAmbi, 1) ? "Off" : "On";
            case k_diffEQ1:
                switch(ambi_dec_getDecNormType(hAmbi,0)){
                    case AMPLITUDE_PRESERVING: return "AP";
                    case ENERGY_PRESERVING: return "EP";
                    default: return "NULL";
                }
            case k_diffEQ2:
                switch(ambi_dec_getDecNormType(hAmbi,1)){
                    case AMPLITUDE_PRESERVING: return "AP";
                    case ENERGY_PRESERVING: return "EP";
                    default: return "NULL";
                }
            case k_transitionFreq: return String(ambi_dec_getTransitionFreq(hAmbi)) + " Hz";
            case k_binauraliseLS:  return !ambi_dec_getBinauraliseLSflag(hAmbi) ? "Off" : "On";
        
            default: return "NULL";
        }
    }
    /* loudspeaker direction parameters */
    else{
        index-=k_NumOfParameters;
        if (!(index % 2))
            return String(ambi_dec_getLoudspeakerAzi_deg(hAmbi, index/2));
        else
            return String(ambi_dec_getLoudspeakerElev_deg(hAmbi, (index-1)/2));
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
    XmlElement xml("AMBIDECPLUGINSETTINGS");
 
    xml.setAttribute("MasterDecOrder", ambi_dec_getMasterDecOrder(hAmbi));
    for(int band=0; band<ambi_dec_getNumberOfBands(); band++)
        xml.setAttribute("DecOrder"+String(band), ambi_dec_getDecOrder(hAmbi, band));
    for(int i=0; i<ambi_dec_getMaxNumLoudspeakers(); i++){
        xml.setAttribute("LoudspeakerAziDeg" + String(i), ambi_dec_getLoudspeakerAzi_deg(hAmbi,i));
        xml.setAttribute("LoudspeakerElevDeg" + String(i), ambi_dec_getLoudspeakerElev_deg(hAmbi,i));
    }
    xml.setAttribute("nLoudspeakers", ambi_dec_getNumLoudspeakers(hAmbi));
    xml.setAttribute("BinauraliseLS", ambi_dec_getBinauraliseLSflag(hAmbi));
    xml.setAttribute("UseDefaultHRIRset", ambi_dec_getUseDefaultHRIRsflag(hAmbi));
    xml.setAttribute("Norm", ambi_dec_getNormType(hAmbi));
    xml.setAttribute("ChOrder", ambi_dec_getChOrder(hAmbi));
    xml.setAttribute("Dec1method", ambi_dec_getDecMethod(hAmbi, 0));
    xml.setAttribute("Dec2method", ambi_dec_getDecMethod(hAmbi, 1));
    xml.setAttribute("Dec1normType", ambi_dec_getDecNormType(hAmbi, 0));
    xml.setAttribute("Dec2normType", ambi_dec_getDecNormType(hAmbi, 1));
    xml.setAttribute("Dec1maxrE", ambi_dec_getDecEnableMaxrE(hAmbi, 0));
    xml.setAttribute("Dec2maxrE", ambi_dec_getDecEnableMaxrE(hAmbi, 1));
    xml.setAttribute("TransitionFreq", ambi_dec_getTransitionFreq(hAmbi));
    xml.setAttribute("preProcHRIRs", ambi_dec_getEnableHRIRsPreProc(hAmbi));
    
    xml.setAttribute("JSONFilePath", lastDir.getFullPathName());
    
    if(!ambi_dec_getUseDefaultHRIRsflag(hAmbi))
        xml.setAttribute("SofaFilePath", String(ambi_dec_getSofaFilePath(hAmbi)));

    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    int i;

    if (xmlState != nullptr) {
        if (xmlState->hasTagName("AMBIDECPLUGINSETTINGS")) {
            if(xmlState->hasAttribute("MasterDecOrder"))
                ambi_dec_setMasterDecOrder(hAmbi, xmlState->getIntAttribute("MasterDecOrder",1));
            for(int band=0; band<ambi_dec_getNumberOfBands(); band++)
                if(xmlState->hasAttribute("DecOrder"+String(band)))
                    ambi_dec_setDecOrder(hAmbi, xmlState->getIntAttribute("DecOrder"+String(band),1), band);
            for(i=0; i<ambi_dec_getMaxNumLoudspeakers(); i++){
                if(xmlState->hasAttribute("LoudspeakerAziDeg" + String(i)))
                    ambi_dec_setLoudspeakerAzi_deg(hAmbi, i, (float)xmlState->getDoubleAttribute("LoudspeakerAziDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("LoudspeakerElevDeg" + String(i)))
                    ambi_dec_setLoudspeakerElev_deg(hAmbi, i, (float)xmlState->getDoubleAttribute("LoudspeakerElevDeg" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("nLoudspeakers"))
                ambi_dec_setNumLoudspeakers(hAmbi, xmlState->getIntAttribute("nLoudspeakers", 1));
            if(xmlState->hasAttribute("BinauraliseLS"))
                ambi_dec_setBinauraliseLSflag(hAmbi, xmlState->getIntAttribute("BinauraliseLS", 1));
            if(xmlState->hasAttribute("UseDefaultHRIRset"))
                ambi_dec_setUseDefaultHRIRsflag(hAmbi, xmlState->getIntAttribute("UseDefaultHRIRset", 1));
            if(xmlState->hasAttribute("Norm"))
                ambi_dec_setNormType(hAmbi, xmlState->getIntAttribute("Norm", 1));
            if(xmlState->hasAttribute("ChOrder"))
                ambi_dec_setChOrder(hAmbi, xmlState->getIntAttribute("ChOrder", 1));
            if(xmlState->hasAttribute("Dec1method"))
                ambi_dec_setDecMethod(hAmbi, 0, xmlState->getIntAttribute("Dec1method", 1));
            if(xmlState->hasAttribute("Dec2method"))
                ambi_dec_setDecMethod(hAmbi, 1, xmlState->getIntAttribute("Dec2method", 1));
            if(xmlState->hasAttribute("Dec1normType"))
                ambi_dec_setDecNormType(hAmbi, 0, xmlState->getIntAttribute("Dec1normType", 1));
            if(xmlState->hasAttribute("Dec2normType"))
                ambi_dec_setDecNormType(hAmbi, 1, xmlState->getIntAttribute("Dec2normType", 1));
            if(xmlState->hasAttribute("Dec1maxrE"))
                ambi_dec_setDecEnableMaxrE(hAmbi, 0, xmlState->getIntAttribute("Dec1maxrE", 1));
            if(xmlState->hasAttribute("Dec2maxrE"))
                ambi_dec_setDecEnableMaxrE(hAmbi, 1, xmlState->getIntAttribute("Dec2maxrE", 1));
            if(xmlState->hasAttribute("TransitionFreq"))
                ambi_dec_setTransitionFreq(hAmbi, (float)xmlState->getDoubleAttribute("TransitionFreq", 1e3f));
            if(xmlState->hasAttribute("preProcHRIRs"))
                ambi_dec_setEnableHRIRsPreProc(hAmbi, xmlState->getIntAttribute("preProcHRIRs", 1));
            
            if(xmlState->hasAttribute("JSONFilePath"))
                lastDir = xmlState->getStringAttribute("JSONFilePath", "");
            
            if(xmlState->hasAttribute("SofaFilePath")){
                String directory = xmlState->getStringAttribute("SofaFilePath", "no_file");
                const char* new_cstring = (const char*)directory.toUTF8();
                ambi_dec_setSofaFilePath(hAmbi, new_cstring);
            }
            
            ambi_dec_refreshSettings(hAmbi);
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
