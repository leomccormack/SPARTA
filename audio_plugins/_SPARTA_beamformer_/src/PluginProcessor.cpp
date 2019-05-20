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
	beamformer_create(&hBeam);
    refreshWindow = true;
}

PluginProcessor::~PluginProcessor()
{
	beamformer_destroy(&hBeam);
}

void PluginProcessor::setParameter (int index, float newValue)
{
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

void PluginProcessor::setCurrentProgram (int index)
{
}

float PluginProcessor::getParameter (int index)
{
    if (!(index % 2))
        return (beamformer_getBeamAzi_deg(hBeam, index/2)/360.0f) + 0.5f;
    else
        return (beamformer_getBeamElev_deg(hBeam, (index-1)/2)/180.0f) + 0.5f;
}

int PluginProcessor::getNumParameters()
{
	return MIN(2*beamformer_getMaxNumBeams(), 2*NUM_OF_AUTOMATABLE_SOURCES);
}

const String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

const String PluginProcessor::getParameterName (int index)
{
    if (!(index % 2))
        return TRANS("Azim_") + String(index/2);
    else
        return TRANS("Elev_") + String((index-1)/2);
}

const String PluginProcessor::getParameterText(int index)
{
    if (!(index % 2))
        return String(beamformer_getBeamAzi_deg(hBeam, index/2));
    else
        return String(beamformer_getBeamElev_deg(hBeam, (index-1)/2));
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

const String PluginProcessor::getProgramName (int index)
{
    return String();
}


bool PluginProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool PluginProcessor::isOutputChannelStereoPair (int index) const
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

void PluginProcessor::changeProgramName (int index, const String& newName)
{
}

void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    nHostBlockSize = samplesPerBlock;
    nNumInputs =  getTotalNumInputChannels();
    nNumOutputs = getTotalNumOutputChannels();
    nSampleRate = (int)(sampleRate + 0.5);
    isPlaying = false;

	beamformer_init(hBeam, sampleRate);
}

void PluginProcessor::releaseResources()
{
    isPlaying = false;
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels());
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels());
    float** bufferData = buffer.getArrayOfWritePointers();
    float* pFrameData[MAX_NUM_CHANNELS];
    
    if(nCurrentBlockSize % FRAME_SIZE == 0){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/FRAME_SIZE; frame++) {
            for (int ch = 0; ch < buffer.getNumChannels(); ch++)
                pFrameData[ch] = &bufferData[ch][frame*FRAME_SIZE];
        
            /* check whether the playhead is moving */
            playHead = getPlayHead();
            bool PlayHeadAvailable = playHead->getCurrentPosition(currentPosition);
            if (PlayHeadAvailable == true)
                isPlaying = currentPosition.isPlaying;
            else
                isPlaying = false;

            /* If there is no playhead, or it is not moving, see if there is audio in the buffer */
            if(!isPlaying){
                for(int j=0; j<nNumInputs; j++){
                    isPlaying = buffer.getMagnitude(j, 0, 8 /* should be enough */)>1e-5f ? true : false;
                    if(isPlaying)
                        break;
                }
            }
            
            /* perform processing */
            beamformer_process(hBeam, pFrameData, pFrameData, nNumInputs, nNumOutputs, FRAME_SIZE, isPlaying);
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
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

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

