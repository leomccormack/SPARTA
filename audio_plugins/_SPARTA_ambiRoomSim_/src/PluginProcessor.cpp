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
	ambi_roomsim_create(&hAmbi);
    refreshWindow = true;
}

PluginProcessor::~PluginProcessor()
{
	ambi_roomsim_destroy(&hAmbi);
}

void PluginProcessor::setParameter (int index, float newValue)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_outputOrder:   ambi_roomsim_setOutputOrder(hAmbi, (SH_ORDERS)(int)(newValue*(float)(MAX_SH_ORDER-1) + 1.5f)); break;
            case k_channelOrder:  ambi_roomsim_setChOrder(hAmbi, (int)(newValue*(float)(NUM_CH_ORDERINGS-1) + 1.5f)); break;
            case k_normType:      ambi_roomsim_setNormType(hAmbi, (int)(newValue*(float)(NUM_NORM_TYPES-1) + 1.5f)); break;
            case k_numSources:    ambi_roomsim_setNumSources(hAmbi, (int)(newValue*(float)(ROOM_SIM_MAX_NUM_SOURCES)+0.5)); break;
            case k_numReceivers:  ambi_roomsim_setNumReceivers(hAmbi, (int)(newValue*(float)(ROOM_SIM_MAX_NUM_RECEIVERS)+0.5)); break;
        }
    }
    /* source position parameters */
    else if(index<3*ROOM_SIM_MAX_NUM_SOURCES+k_NumOfParameters){
        index-=k_NumOfParameters;
        float newValueScaled;
        switch((index % 3)){
            case 0:
                newValueScaled = newValue * ambi_roomsim_getRoomDimX(hAmbi);
                if (newValueScaled != ambi_roomsim_getSourceX(hAmbi, (int)((float)index/3.0f+0.001f))){
                    ambi_roomsim_setSourceX(hAmbi, (int)((float)index/3.0f+0.001f), newValueScaled);
                    refreshWindow = true;
                }
                break;
            case 1:
                newValueScaled = newValue * ambi_roomsim_getRoomDimY(hAmbi);
                if (newValueScaled != ambi_roomsim_getSourceY(hAmbi, (int)((float)index/3.0f+0.001f))){
                    ambi_roomsim_setSourceY(hAmbi, (int)((float)index/3.0f+0.001f), newValueScaled);
                    refreshWindow = true;
                }
                break;
            case 2:
                newValueScaled = newValue * ambi_roomsim_getRoomDimZ(hAmbi);
                if (newValueScaled != ambi_roomsim_getSourceZ(hAmbi, (int)((float)index/3.0f+0.001f))){
                    ambi_roomsim_setSourceZ(hAmbi, (int)((float)index/3.0f+0.001f), newValueScaled);
                    refreshWindow = true;
                }
                break;
        }
    }
    /* Receiver position parameters */
    else{
        index-= (k_NumOfParameters+3*ROOM_SIM_MAX_NUM_SOURCES);
        float newValueScaled;
        switch((index % 3)){
            case 0:
                newValueScaled = newValue * ambi_roomsim_getRoomDimX(hAmbi);
                if (newValueScaled != ambi_roomsim_getReceiverX(hAmbi, (int)((float)index/3.0f+0.001f))){
                    ambi_roomsim_setReceiverX(hAmbi, (int)((float)index/3.0f+0.001f), newValueScaled);
                    refreshWindow = true;
                }
                break;
            case 1:
                newValueScaled = newValue * ambi_roomsim_getRoomDimY(hAmbi);
                if (newValueScaled != ambi_roomsim_getReceiverY(hAmbi, (int)((float)index/3.0f+0.001f))){
                    ambi_roomsim_setReceiverY(hAmbi, (int)((float)index/3.0f+0.001f), newValueScaled);
                    refreshWindow = true;
                }
                break;
            case 2:
                newValueScaled = newValue * ambi_roomsim_getRoomDimZ(hAmbi);
                if (newValueScaled != ambi_roomsim_getReceiverZ(hAmbi, (int)((float)index/3.0f+0.001f))){
                    ambi_roomsim_setReceiverZ(hAmbi, (int)((float)index/3.0f+0.001f), newValueScaled);
                    refreshWindow = true;
                }
                break;
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
            case k_outputOrder:   return (float)(ambi_roomsim_getOutputOrder(hAmbi)-1)/(float)(MAX_SH_ORDER-1);
            case k_channelOrder:  return (float)(ambi_roomsim_getChOrder(hAmbi)-1)/(float)(NUM_CH_ORDERINGS-1);
            case k_normType:      return (float)(ambi_roomsim_getNormType(hAmbi)-1)/(float)(NUM_NORM_TYPES-1);
            case k_numSources:    return (float)(ambi_roomsim_getNumSources(hAmbi))/(float)(ROOM_SIM_MAX_NUM_SOURCES);
            case k_numReceivers:  return (float)(ambi_roomsim_getNumReceivers(hAmbi))/(float)(ROOM_SIM_MAX_NUM_RECEIVERS);
            default: return 0.0f;
        }
    }
    /* source position parameters */
    else if(index<3*ROOM_SIM_MAX_NUM_SOURCES+k_NumOfParameters){
        index-=k_NumOfParameters;
        switch((index % 3)){
            case 0: return ambi_roomsim_getSourceX(hAmbi, (int)((float)index/3.0f+0.001f))/ambi_roomsim_getRoomDimX(hAmbi);
            case 1: return ambi_roomsim_getSourceY(hAmbi, (int)((float)index/3.0f+0.001f))/ambi_roomsim_getRoomDimY(hAmbi);
            case 2: return ambi_roomsim_getSourceZ(hAmbi, (int)((float)index/3.0f+0.001f))/ambi_roomsim_getRoomDimZ(hAmbi);
            default: return 0.0f;
        }
    }
    /* Receiver position parameters */
    else{
        index-= (k_NumOfParameters+3*ROOM_SIM_MAX_NUM_SOURCES);
        switch((index % 3)){
            case 0: return ambi_roomsim_getReceiverX(hAmbi, (int)((float)index/3.0f+0.001f))/ambi_roomsim_getRoomDimX(hAmbi);
            case 1: return ambi_roomsim_getReceiverY(hAmbi, (int)((float)index/3.0f+0.001f))/ambi_roomsim_getRoomDimY(hAmbi);
            case 2: return ambi_roomsim_getReceiverZ(hAmbi, (int)((float)index/3.0f+0.001f))/ambi_roomsim_getRoomDimZ(hAmbi);
            default: return 0.0f;
        }
    }
}

int PluginProcessor::getNumParameters()
{
    return k_NumOfParameters + 3*ROOM_SIM_MAX_NUM_SOURCES + 3*ROOM_SIM_MAX_NUM_RECEIVERS;
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
            case k_numReceivers: return "num_receivers";
            default: return "NULL";
        }
    }
    /* source position parameters */
    else if(index<3*ROOM_SIM_MAX_NUM_SOURCES+k_NumOfParameters){
        index-=k_NumOfParameters;
        switch((index % 3)){
            case 0: return TRANS("SourceX_") + String((int)((float)index/3.0f+0.001f));
            case 1: return TRANS("SourceY_") + String((int)((float)index/3.0f+0.001f));
            case 2: return TRANS("SourceZ_") + String((int)((float)index/3.0f+0.001f));
            default: return "NULL";
        }
    }
    /* Receiver position parameters */
    else{
        index-= (k_NumOfParameters+3*ROOM_SIM_MAX_NUM_SOURCES);
        switch((index % 3)){
            case 0: return TRANS("ReceiverX_") + String((int)((float)index/3.0f+0.001f));
            case 1: return TRANS("ReceiverY_") + String((int)((float)index/3.0f+0.001f));
            case 2: return TRANS("ReceiverZ_") + String((int)((float)index/3.0f+0.001f));
            default: return "NULL";
        }
    }
}

const String PluginProcessor::getParameterText(int index)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_outputOrder: return String(ambi_roomsim_getOutputOrder(hAmbi));
            case k_channelOrder:
                switch(ambi_roomsim_getChOrder(hAmbi)){
                    case CH_ACN:  return "ACN";
                    case CH_FUMA: return "FuMa";
                    default: return "NULL";
                }
            case k_normType:
                switch(ambi_roomsim_getNormType(hAmbi)){
                    case NORM_N3D:  return "N3D";
                    case NORM_SN3D: return "SN3D";
                    case NORM_FUMA: return "FuMa";
                    default: return "NULL";
                }
            case k_numSources: return String(ambi_roomsim_getNumSources(hAmbi));
            case k_numReceivers: return String(ambi_roomsim_getNumReceivers(hAmbi));
            default: return "NULL";
        }
    }
    /* source position parameters */
    else if(index<3*ROOM_SIM_MAX_NUM_SOURCES+k_NumOfParameters){
        index-=k_NumOfParameters;
        switch((index % 3)){
            case 0: return String(ambi_roomsim_getSourceX(hAmbi, (int)((float)index/3.0f+0.001f)));
            case 1: return String(ambi_roomsim_getSourceY(hAmbi, (int)((float)index/3.0f+0.001f)));
            case 2: return String(ambi_roomsim_getSourceZ(hAmbi, (int)((float)index/3.0f+0.001f)));
            default: return "NULL";
        }
    }
    /* Receiver position parameters */
    else{
        index-= (k_NumOfParameters+3*ROOM_SIM_MAX_NUM_SOURCES);
        switch((index % 3)){
            case 0: return String(ambi_roomsim_getReceiverX(hAmbi, (int)((float)index/3.0f+0.001f)));
            case 1: return String(ambi_roomsim_getReceiverY(hAmbi, (int)((float)index/3.0f+0.001f)));
            case 2: return String(ambi_roomsim_getReceiverZ(hAmbi, (int)((float)index/3.0f+0.001f)));
            default: return "NULL";
        }
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

	ambi_roomsim_init(hAmbi, nSampleRate);
    AudioProcessor::setLatencySamples(ambi_roomsim_getProcessingDelay());
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
    int frameSize = ambi_roomsim_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            ambi_roomsim_process(hAmbi, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
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
    XmlElement xml("AMBIROOMSIMPLUGINSETTINGS");
    for(int i=0; i<ambi_roomsim_getMaxNumSources(); i++){
        xml.setAttribute("SourceX" + String(i), ambi_roomsim_getSourceX(hAmbi,i));
        xml.setAttribute("SourceY" + String(i), ambi_roomsim_getSourceY(hAmbi,i));
        xml.setAttribute("SourceZ" + String(i), ambi_roomsim_getSourceZ(hAmbi,i));
    }
    for(int i=0; i<ambi_roomsim_getMaxNumReceivers(); i++){
        xml.setAttribute("ReceiverX" + String(i), ambi_roomsim_getReceiverX(hAmbi,i));
        xml.setAttribute("ReceiverY" + String(i), ambi_roomsim_getReceiverY(hAmbi,i));
        xml.setAttribute("ReceiverZ" + String(i), ambi_roomsim_getReceiverZ(hAmbi,i));
    }
    for(int i=0; i<3; i++)
        for(int j=0; j<2; j++)
            xml.setAttribute("wallAbsCoeff" + String(i) + "_" + String(j), ambi_roomsim_getWallAbsCoeff(hAmbi, i, j));
    xml.setAttribute("RoomX", ambi_roomsim_getRoomDimX(hAmbi));
    xml.setAttribute("RoomY", ambi_roomsim_getRoomDimY(hAmbi));
    xml.setAttribute("RoomZ", ambi_roomsim_getRoomDimZ(hAmbi)); 
    xml.setAttribute("NORM", ambi_roomsim_getNormType(hAmbi));
    xml.setAttribute("CHORDER", ambi_roomsim_getChOrder(hAmbi));
    xml.setAttribute("OUT_ORDER", ambi_roomsim_getOutputOrder(hAmbi));
    xml.setAttribute("nSources", ambi_roomsim_getNumSources(hAmbi));
    xml.setAttribute("nReceivers", ambi_roomsim_getNumReceivers(hAmbi));

    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr) {
        if (xmlState->hasTagName("AMBIROOMSIMPLUGINSETTINGS")) {
            for(int i=0; i<ambi_roomsim_getMaxNumSources(); i++){
                if(xmlState->hasAttribute("SourceX" + String(i)))
                    ambi_roomsim_setSourceX(hAmbi, i, (float)xmlState->getDoubleAttribute("SourceX" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceY" + String(i)))
                    ambi_roomsim_setSourceY(hAmbi, i, (float)xmlState->getDoubleAttribute("SourceY" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceZ" + String(i)))
                    ambi_roomsim_setSourceZ(hAmbi, i, (float)xmlState->getDoubleAttribute("SourceZ" + String(i), 0.0f));
            }
            for(int i=0; i<ambi_roomsim_getMaxNumReceivers(); i++){
                if(xmlState->hasAttribute("ReceiverX" + String(i)))
                    ambi_roomsim_setReceiverX(hAmbi, i, (float)xmlState->getDoubleAttribute("ReceiverX" + String(i), 0.0f));
                if(xmlState->hasAttribute("ReceiverY" + String(i)))
                    ambi_roomsim_setReceiverY(hAmbi, i, (float)xmlState->getDoubleAttribute("ReceiverY" + String(i), 0.0f));
                if(xmlState->hasAttribute("ReceiverZ" + String(i)))
                    ambi_roomsim_setReceiverZ(hAmbi, i, (float)xmlState->getDoubleAttribute("ReceiverZ" + String(i), 0.0f));
            }
            for(int i=0; i<3; i++)
                for(int j=0; j<2; j++)
                    if(xmlState->hasAttribute("wallAbsCoeff" + String(i) + "_" + String(j)))
                        ambi_roomsim_setWallAbsCoeff(hAmbi, i, j, (float)xmlState->getDoubleAttribute("wallAbsCoeff" + String(i) + "_" + String(j), 0.0f));
            if(xmlState->hasAttribute("RoomX"))
                ambi_roomsim_setRoomDimX(hAmbi, (float)xmlState->getDoubleAttribute("RoomX", 0.0f));
            if(xmlState->hasAttribute("RoomY"))
                ambi_roomsim_setRoomDimY(hAmbi, (float)xmlState->getDoubleAttribute("RoomY", 0.0f));
            if(xmlState->hasAttribute("RoomZ"))
                ambi_roomsim_setRoomDimZ(hAmbi, (float)xmlState->getDoubleAttribute("RoomZ", 0.0f));
            if(xmlState->hasAttribute("nSources"))
                ambi_roomsim_setNumSources(hAmbi, xmlState->getIntAttribute("nSources", 1));
            if(xmlState->hasAttribute("nReceivers"))
                ambi_roomsim_setNumReceivers(hAmbi, xmlState->getIntAttribute("nReceivers", 1));

            if(xmlState->hasAttribute("NORM"))
                ambi_roomsim_setNormType(hAmbi, xmlState->getIntAttribute("NORM", 1));
            if(xmlState->hasAttribute("CHORDER"))
                ambi_roomsim_setChOrder(hAmbi, xmlState->getIntAttribute("CHORDER", 1));
            if(xmlState->hasAttribute("OUT_ORDER"))
                ambi_roomsim_setOutputOrder(hAmbi, xmlState->getIntAttribute("OUT_ORDER", 1));
            
            ambi_roomsim_refreshParams(hAmbi);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
