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

PluginProcessor::PluginProcessor()
{
    bufferInputs = new float*[MAX_NUM_CHANNELS];
    for (int i = 0; i < MAX_NUM_CHANNELS; i++)
        bufferInputs[i] = new float[FRAME_SIZE];
    
    bufferOutputs = new float*[MAX_NUM_CHANNELS];
    for (int i = 0; i < MAX_NUM_CHANNELS; i++)
        bufferOutputs[i] = new float[FRAME_SIZE];
    
	ambi_cropac_create(&hAmbi);
    
    /* specify here on which UDP port number to receive incoming OSC messages */
    osc_port_ID = DEFAULT_OSC_PORT;
    osc.connect(osc_port_ID);
    /* tell the component to listen for OSC messages */
    osc.addListener(this);
}

PluginProcessor::~PluginProcessor()
{
    osc.disconnect();
    osc.removeListener(this);
    
	ambi_cropac_destroy(&hAmbi);
    
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
        delete[] bufferInputs[i];
    delete[] bufferInputs;
    
    for (int i = 0; i < MAX_NUM_CHANNELS; ++i)
        delete[] bufferOutputs[i];
    delete[] bufferOutputs;
}

void PluginProcessor::oscMessageReceived(const OSCMessage& message)
{
    /* if rotation angles are sent as an array \ypr[3] */
    if (message.size() == 3 && message.getAddressPattern().toString().compare("ypr")) {
        if (message[0].isFloat32())
            ambi_cropac_setYaw(hAmbi, message[0].getFloat32());
        if (message[1].isFloat32())
            ambi_cropac_setPitch(hAmbi, message[1].getFloat32());
        if (message[2].isFloat32())
            ambi_cropac_setRoll(hAmbi, message[2].getFloat32());
        return;
    }
    
    /* if rotation angles are sent individually: */
    if(message.getAddressPattern().toString().compare("yaw"))
        ambi_cropac_setYaw(hAmbi, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("pitch"))
        ambi_cropac_setPitch(hAmbi, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("roll"))
        ambi_cropac_setRoll(hAmbi, message[0].getFloat32());
}

void PluginProcessor::setParameter (int index, float newValue)
{
    switch (index)
    {
        case k_yaw:
            ambi_cropac_setYaw(hAmbi, (newValue-0.5f)*360.0f );
            break;
        case k_pitch:
            ambi_cropac_setPitch(hAmbi, (newValue - 0.5f)*180.0f);
            break;
        case k_roll:
            ambi_cropac_setRoll(hAmbi, (newValue - 0.5f)*180.0f);
            break;
        case k_flipYaw:
            ambi_cropac_setFlipYaw(hAmbi, (int)(newValue + 0.5f));
            break;
        case k_flipPitch:
            ambi_cropac_setFlipPitch(hAmbi, (int)(newValue + 0.5f));
            break;
        case k_flipRoll:
            ambi_cropac_setFlipRoll(hAmbi, (int)(newValue + 0.5f));
            break;
            
        default: break;
    }
}

void PluginProcessor::setCurrentProgram (int index)
{
}

float PluginProcessor::getParameter (int index)
{
    switch (index)
    {
        case k_yaw:
            return (ambi_cropac_getYaw(hAmbi)/360.0f) + 0.5f;
        case k_pitch:
            return (ambi_cropac_getPitch(hAmbi)/180.0f) + 0.5f;
        case k_roll:
            return (ambi_cropac_getRoll(hAmbi)/180.0f) + 0.5f;
        case k_flipYaw:
            return (float)ambi_cropac_getFlipYaw(hAmbi);
        case k_flipPitch:
            return (float)ambi_cropac_getFlipPitch(hAmbi);
        case k_flipRoll:
            return (float)ambi_cropac_getFlipRoll(hAmbi);
            
        default: return 0.0f;
    }
}

int PluginProcessor::getNumParameters()
{
	return k_NumOfParameters;
}

const String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

const String PluginProcessor::getParameterName (int index)
{
    switch (index)
    {
        case k_yaw:
            return "yaw";
        case k_pitch:
            return "pitch";
        case k_roll:
            return "roll";
        case k_flipYaw:
            return "flip_yaw";
        case k_flipPitch:
            return "flip_pitch";
        case k_flipRoll:
            return "flip_roll";
        default: return "NULL";
    }
}

const String PluginProcessor::getParameterText(int index)
{
	return String(getParameter(index), 1);    
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

	ambi_cropac_init(hAmbi, sampleRate);
    AudioProcessor::setLatencySamples(ambi_cropac_getProcessingDelay());
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
    
    if((nCurrentBlockSize % FRAME_SIZE == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/FRAME_SIZE; frame++) {
            for (int ch = 0; ch < nNumInputs; ch++)
                for (int i = 0; i < FRAME_SIZE; i++)
                    bufferInputs[ch][i] = bufferData[ch][frame*FRAME_SIZE + i];
            
            /* determine if there is actually audio in the damn buffer */
            isPlaying = buffer.getRMSLevel(0, 0, nCurrentBlockSize)>1e-5f /* -100dB */ ? true : false;
            
            /* perform processing */
            ambi_cropac_process(hAmbi, bufferInputs, bufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, isPlaying);
            
            /* replace buffer with new audio */
            buffer.clear(frame*FRAME_SIZE, FRAME_SIZE);
            for (int ch = 0; ch < nNumOutputs; ch++)
                for (int i = 0; i < FRAME_SIZE; i++)
                    bufferData[ch][frame*FRAME_SIZE + i] = bufferOutputs[ch][i];
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
    XmlElement xml("AMBIBINPLUGINSETTINGS");
    
    for(int band=0; band<ambi_cropac_getNumberOfBands(); band++){
        xml.setAttribute("Balance"+String(band), ambi_cropac_getBalance(hAmbi, band));
        xml.setAttribute("DecBalance"+String(band), ambi_cropac_getDecBalance(hAmbi, band));
    }
    xml.setAttribute("CovAVG", ambi_cropac_getCovAvg(hAmbi));
    
    xml.setAttribute("UseDefaultHRIRset", ambi_cropac_getUseDefaultHRIRsflag(hAmbi));
    xml.setAttribute("Norm", ambi_cropac_getNormType(hAmbi));
    xml.setAttribute("ChOrder", ambi_cropac_getChOrder(hAmbi));
    xml.setAttribute("maxrE", ambi_cropac_getDecEnableMaxrE(hAmbi));
    
    xml.setAttribute("ENABLEROT", ambi_cropac_getEnableRotation(hAmbi));
    xml.setAttribute("YAW", ambi_cropac_getYaw(hAmbi));
    xml.setAttribute("PITCH", ambi_cropac_getPitch(hAmbi));
    xml.setAttribute("ROLL", ambi_cropac_getRoll(hAmbi));
    xml.setAttribute("FLIP_YAW", ambi_cropac_getFlipYaw(hAmbi));
    xml.setAttribute("FLIP_PITCH", ambi_cropac_getFlipPitch(hAmbi));
    xml.setAttribute("FLIP_ROLL", ambi_cropac_getFlipRoll(hAmbi));
    xml.setAttribute("RPY_FLAG", ambi_cropac_getRPYflag(hAmbi));
    
    xml.setAttribute("OSC_PORT", osc_port_ID);
    
    if(!ambi_cropac_getUseDefaultHRIRsflag(hAmbi))
        xml.setAttribute("SofaFilePath", String(ambi_cropac_getSofaFilePath(hAmbi)));

    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr) {
        if (xmlState->hasTagName("AMBIBINPLUGINSETTINGS")) {
            
            for(int band=0; band<ambi_cropac_getNumberOfBands(); band++){
                if(xmlState->hasAttribute("Balance"+String(band)))
                    ambi_cropac_setBalance(hAmbi, (float)xmlState->getDoubleAttribute("Balance"+String(band),0), band);
                if(xmlState->hasAttribute("DecBalance"+String(band)))
                    ambi_cropac_setDecBalance(hAmbi, (float)xmlState->getDoubleAttribute("DecBalance"+String(band),0), band);
            }
            if(xmlState->hasAttribute("CovAVG"))
                ambi_cropac_setCovAvg(hAmbi, (float)xmlState->getDoubleAttribute("CovAVG", 0.5));
            
            if(xmlState->hasAttribute("UseDefaultHRIRset"))
                ambi_cropac_setUseDefaultHRIRsflag(hAmbi, xmlState->getIntAttribute("UseDefaultHRIRset", 1));
            if(xmlState->hasAttribute("Norm"))
                ambi_cropac_setNormType(hAmbi, xmlState->getIntAttribute("Norm", 1));
            if(xmlState->hasAttribute("ChOrder"))
                ambi_cropac_setChOrder(hAmbi, xmlState->getIntAttribute("ChOrder", 1));
            if(xmlState->hasAttribute("maxrE"))
                ambi_cropac_setDecEnableMaxrE(hAmbi,xmlState->getIntAttribute("maxrE", 1));
            
            if(xmlState->hasAttribute("ENABLEROT"))
                ambi_cropac_setEnableRotation(hAmbi, xmlState->getIntAttribute("ENABLEROT", 0));
            if(xmlState->hasAttribute("YAW"))
                ambi_cropac_setYaw(hAmbi, (float)xmlState->getDoubleAttribute("YAW", 0.0f));
            if(xmlState->hasAttribute("PITCH"))
                ambi_cropac_setPitch(hAmbi, (float)xmlState->getDoubleAttribute("PITCH", 0.0f));
            if(xmlState->hasAttribute("ROLL"))
                ambi_cropac_setRoll(hAmbi, (float)xmlState->getDoubleAttribute("ROLL", 0.0f));
            if(xmlState->hasAttribute("FLIP_YAW"))
                ambi_cropac_setFlipYaw(hAmbi, xmlState->getIntAttribute("FLIP_YAW", 0));
            if(xmlState->hasAttribute("FLIP_PITCH"))
                ambi_cropac_setFlipPitch(hAmbi, xmlState->getIntAttribute("FLIP_PITCH", 0));
            if(xmlState->hasAttribute("FLIP_ROLL"))
                ambi_cropac_setFlipRoll(hAmbi, xmlState->getIntAttribute("FLIP_ROLL", 0));
            if(xmlState->hasAttribute("RPY_FLAG"))
                ambi_cropac_setRPYflag(hAmbi, xmlState->getIntAttribute("RPY_FLAG", 0));
            
            if(xmlState->hasAttribute("OSC_PORT")){
                osc_port_ID = xmlState->getIntAttribute("OSC_PORT", DEFAULT_OSC_PORT);
                osc.connect(osc_port_ID);
            }
            
            if(xmlState->hasAttribute("SofaFilePath")){
                String directory = xmlState->getStringAttribute("SofaFilePath", "no_file");
                const char* new_cstring = (const char*)directory.toUTF8();
                ambi_cropac_setSofaFilePath(hAmbi, new_cstring);
            }
            
            ambi_cropac_refreshParams(hAmbi);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

