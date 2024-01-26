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
	beamformer_create(&hBeam);
    refreshWindow = true;
}

PluginProcessor::~PluginProcessor()
{
	beamformer_destroy(&hBeam);
}

void PluginProcessor::setParameter (int index, float newValue)
{
    /* standard parameters */
    if(index < k_NumOfParameters){
        switch (index) {
            case k_inputOrder:   beamformer_setBeamOrder(hBeam, (SH_ORDERS)(int)(newValue*(float)(MAX_SH_ORDER-1) + 1.5f)); break;
            case k_channelOrder: beamformer_setChOrder(hBeam, (int)(newValue*(float)(NUM_CH_ORDERINGS-1) + 1.5f)); break;
            case k_normType:     beamformer_setNormType(hBeam, (int)(newValue*(float)(NUM_NORM_TYPES-1) + 1.5f)); break;
            case k_beamType:     beamformer_setBeamType(hBeam, (STATIC_BEAM_TYPES)(int)(newValue*(float)(NUM_STATIC_BEAM_TYPES-1) + 1.5f)); break;
            case k_numBeams:     beamformer_setNumBeams(hBeam, (int)(newValue*(float)(MAX_NUM_OUTPUTS)+0.5)); break;
        }
    }
    /* source direction parameters */
    else{
        index-=k_NumOfParameters;
        float newValueScaled;
        if (!(index % 2)){
            newValueScaled = (newValue - 0.5f)*360.0f;
            if (newValueScaled != beamformer_getBeamAzi_deg(hBeam, index/2)){
                beamformer_setBeamAzi_deg(hBeam, index/2, newValueScaled);
                refreshWindow = true;
            }
        }
        else{
            newValueScaled = (newValue - 0.5f)*180.0f;
            if (newValueScaled != beamformer_getBeamElev_deg(hBeam, index/2)){
                beamformer_setBeamElev_deg(hBeam, index/2, newValueScaled);
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
            case k_inputOrder:   return (float)(beamformer_getBeamOrder(hBeam)-1)/(float)(MAX_SH_ORDER-1);
            case k_channelOrder: return (float)(beamformer_getChOrder(hBeam)-1)/(float)(NUM_CH_ORDERINGS-1);
            case k_normType:     return (float)(beamformer_getNormType(hBeam)-1)/(float)(NUM_NORM_TYPES-1);
            case k_beamType:     return (float)(beamformer_getBeamType(hBeam)-1)/(float)(NUM_STATIC_BEAM_TYPES-1);
            case k_numBeams:     return (float)(beamformer_getNumBeams(hBeam))/(float)(MAX_NUM_OUTPUTS);
            default: return 0.0f;
        }
    }
    /* source direction parameters */
    else{
        index-=k_NumOfParameters;
        if (!(index % 2))
            return (beamformer_getBeamAzi_deg(hBeam, index/2)/360.0f) + 0.5f;
        else
            return (beamformer_getBeamElev_deg(hBeam, (index-1)/2)/180.0f) + 0.5f;
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
            case k_inputOrder:   return "order";
            case k_channelOrder: return "channel_order";
            case k_normType:     return "norm_type";
            case k_beamType:     return "beam_type";
            case k_numBeams:     return "num_beams";
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
            case k_inputOrder: return String(beamformer_getBeamOrder(hBeam));
            case k_channelOrder:
                switch(beamformer_getChOrder(hBeam)){
                    case CH_ACN:  return "ACN";
                    case CH_FUMA: return "FuMa";
                    default: return "NULL";
                }
            case k_normType:
                switch(beamformer_getNormType(hBeam)){
                    case NORM_N3D:  return "N3D";
                    case NORM_SN3D: return "SN3D";
                    case NORM_FUMA: return "FuMa";
                    default: return "NULL";
                }
            case k_beamType:
                switch(beamformer_getBeamType(hBeam)){
                    case STATIC_BEAM_TYPE_HYPERCARDIOID: return "Hyper-Card";
                    case STATIC_BEAM_TYPE_CARDIOID:      return "Cardioid";
                    case STATIC_BEAM_TYPE_MAX_EV:        return "Max-EV";
                    default: return "NULL";
                }
            case k_numBeams: return String(beamformer_getNumBeams(hBeam));
            default: return "NULL";
        }
    }
    /* source direction parameters */
    else{
        index-=k_NumOfParameters;
        if (!(index % 2))
            return String(beamformer_getBeamAzi_deg(hBeam, index/2));
        else
            return String(beamformer_getBeamElev_deg(hBeam, (index-1)/2));
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

	beamformer_init(hBeam, nSampleRate);
    AudioProcessor::setLatencySamples(beamformer_getProcessingDelay());
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
    int frameSize = beamformer_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            beamformer_process(hBeam, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
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
    XmlElement xml("BEAMFORMERPLUGINSETTINGS");
    for(int i=0; i<beamformer_getMaxNumBeams(); i++){
        xml.setAttribute("BeamAziDeg" + String(i), beamformer_getBeamAzi_deg(hBeam,i));
        xml.setAttribute("BeamElevDeg" + String(i), beamformer_getBeamElev_deg(hBeam,i));
    }
    xml.setAttribute("NORM", beamformer_getNormType(hBeam));
    xml.setAttribute("CHORDER", beamformer_getChOrder(hBeam));
    xml.setAttribute("beamOrder", beamformer_getBeamOrder(hBeam));
    xml.setAttribute("nBeams", beamformer_getNumBeams(hBeam));
    xml.setAttribute("beamType", beamformer_getBeamType(hBeam));
    
    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr) {
        if (xmlState->hasTagName("BEAMFORMERPLUGINSETTINGS")) {
            for(int i=0; i<beamformer_getMaxNumBeams(); i++){
                if(xmlState->hasAttribute("BeamAziDeg" + String(i)))
                    beamformer_setBeamAzi_deg(hBeam, i, (float)xmlState->getDoubleAttribute("BeamAziDeg" + String(i), 0.0f));
                if(xmlState->hasAttribute("BeamElevDeg" + String(i)))
                    beamformer_setBeamElev_deg(hBeam, i, (float)xmlState->getDoubleAttribute("BeamElevDeg" + String(i), 0.0f));
            }
            if(xmlState->hasAttribute("nBeams"))
                beamformer_setNumBeams(hBeam, xmlState->getIntAttribute("nBeams", 1));
            
            if(xmlState->hasAttribute("NORM"))
                beamformer_setNormType(hBeam, xmlState->getIntAttribute("NORM", 1));
            if(xmlState->hasAttribute("CHORDER"))
                beamformer_setChOrder(hBeam, xmlState->getIntAttribute("CHORDER", 1));
            if(xmlState->hasAttribute("beamOrder"))
                beamformer_setBeamOrder(hBeam, xmlState->getIntAttribute("beamOrder", 1));
            if(xmlState->hasAttribute("beamType"))
                beamformer_setBeamType(hBeam, xmlState->getIntAttribute("beamType", 1));
            
            beamformer_refreshSettings(hBeam);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

