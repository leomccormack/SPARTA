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
	    .withOutput("Output", AudioChannelSet::discreteChannels(2), true))
{
    bufferInputs = new float*[MAX_NUM_CHANNELS];
    for (int i = 0; i < MAX_NUM_CHANNELS; i++)
        bufferInputs[i] = new float[FRAME_SIZE];
    
    bufferOutputs = new float*[MAX_NUM_CHANNELS];
    for (int i = 0; i < MAX_NUM_CHANNELS; i++)
        bufferOutputs[i] = new float[FRAME_SIZE];
    
	ambi_bin_create(&hAmbi);
    
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
    
	ambi_bin_destroy(&hAmbi);
    
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
            ambi_bin_setYaw(hAmbi, message[0].getFloat32());
        if (message[1].isFloat32())
            ambi_bin_setPitch(hAmbi, message[1].getFloat32());
        if (message[2].isFloat32())
            ambi_bin_setRoll(hAmbi, message[2].getFloat32());
        return;
    }
    
    /* if rotation angles are sent individually: */
    if(message.getAddressPattern().toString().compare("yaw"))
        ambi_bin_setYaw(hAmbi, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("pitch"))
        ambi_bin_setPitch(hAmbi, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("roll"))
        ambi_bin_setRoll(hAmbi, message[0].getFloat32());
}

void PluginProcessor::setParameter (int index, float newValue)
{
    switch (index)
    {
        case k_yaw:
            ambi_bin_setYaw(hAmbi, (newValue-0.5f)*360.0f );
            break;
        case k_pitch:
            ambi_bin_setPitch(hAmbi, (newValue - 0.5f)*180.0f);
            break;
        case k_roll:
            ambi_bin_setRoll(hAmbi, (newValue - 0.5f)*180.0f);
            break;
        case k_flipYaw:
            ambi_bin_setFlipYaw(hAmbi, (int)(newValue + 0.5f));
            break;
        case k_flipPitch:
            ambi_bin_setFlipPitch(hAmbi, (int)(newValue + 0.5f));
            break;
        case k_flipRoll:
            ambi_bin_setFlipRoll(hAmbi, (int)(newValue + 0.5f));
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
            return (ambi_bin_getYaw(hAmbi)/360.0f) + 0.5f;
        case k_pitch:
            return (ambi_bin_getPitch(hAmbi)/180.0f) + 0.5f;
        case k_roll:
            return (ambi_bin_getRoll(hAmbi)/180.0f) + 0.5f;
        case k_flipYaw:
            return (float)ambi_bin_getFlipYaw(hAmbi);
        case k_flipPitch:
            return (float)ambi_bin_getFlipPitch(hAmbi);
        case k_flipRoll:
            return (float)ambi_bin_getFlipRoll(hAmbi);
            
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

bool PluginProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
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

	ambi_bin_init(hAmbi, sampleRate); 
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
    
    if(nCurrentBlockSize % FRAME_SIZE == 0){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/FRAME_SIZE; frame++) {
            for (int ch = 0; ch < nNumInputs; ch++)
                for (int i = 0; i < FRAME_SIZE; i++)
                    bufferInputs[ch][i] = bufferData[ch][frame*FRAME_SIZE + i];
            
            /* determine if there is actually audio in the damn buffer */
            playHead = getPlayHead();
            bool PlayHeadAvailable = playHead->getCurrentPosition(currentPosition);
            if (PlayHeadAvailable)
                isPlaying = currentPosition.isPlaying;
            else
                isPlaying = false;
            if(!isPlaying) /* for DAWs with no transport */
                isPlaying = buffer.getRMSLevel(0, 0, nCurrentBlockSize)>1e-5f ? true : false;
            
            /* perform processing */
            ambi_bin_process(hAmbi, bufferInputs, bufferOutputs, nNumInputs, nNumOutputs, FRAME_SIZE, isPlaying);
            
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
    
    xml.setAttribute("orderPreset", ambi_bin_getInputOrderPreset(hAmbi));
  
    xml.setAttribute("UseDefaultHRIRset", ambi_bin_getUseDefaultHRIRsflag(hAmbi));
    xml.setAttribute("Norm", ambi_bin_getNormType(hAmbi));
    xml.setAttribute("ChOrder", ambi_bin_getChOrder(hAmbi));
    xml.setAttribute("maxrE", ambi_bin_getDecEnableMaxrE(hAmbi));
    xml.setAttribute("PhaseManip", ambi_bin_getEnablePhaseManip(hAmbi));
    
    xml.setAttribute("ENABLEROT", ambi_bin_getEnableRotation(hAmbi));
    xml.setAttribute("YAW", ambi_bin_getYaw(hAmbi));
    xml.setAttribute("PITCH", ambi_bin_getPitch(hAmbi));
    xml.setAttribute("ROLL", ambi_bin_getRoll(hAmbi));
    xml.setAttribute("FLIP_YAW", ambi_bin_getFlipYaw(hAmbi));
    xml.setAttribute("FLIP_PITCH", ambi_bin_getFlipPitch(hAmbi));
    xml.setAttribute("FLIP_ROLL", ambi_bin_getFlipRoll(hAmbi));
    xml.setAttribute("RPY_FLAG", ambi_bin_getRPYflag(hAmbi));
    
    xml.setAttribute("OSC_PORT", osc_port_ID);
    
    if(!ambi_bin_getUseDefaultHRIRsflag(hAmbi))
        xml.setAttribute("SofaFilePath", String(ambi_bin_getSofaFilePath(hAmbi)));

    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr) {
        if (xmlState->hasTagName("AMBIBINPLUGINSETTINGS")) {
            
            if(xmlState->hasAttribute("orderPreset"))
                ambi_bin_setInputOrderPreset(hAmbi, (INPUT_ORDERS)xmlState->getIntAttribute("orderPreset", 2));
            if(xmlState->hasAttribute("UseDefaultHRIRset"))
                ambi_bin_setUseDefaultHRIRsflag(hAmbi, xmlState->getIntAttribute("UseDefaultHRIRset", 1));
            if(xmlState->hasAttribute("Norm"))
                ambi_bin_setNormType(hAmbi, xmlState->getIntAttribute("Norm", 1));
            if(xmlState->hasAttribute("ChOrder"))
                ambi_bin_setChOrder(hAmbi, xmlState->getIntAttribute("ChOrder", 1));
            if(xmlState->hasAttribute("maxrE"))
                ambi_bin_setDecEnableMaxrE(hAmbi,xmlState->getIntAttribute("maxrE", 1));
            if(xmlState->hasAttribute("PhaseManip"))
                ambi_bin_setEnablePhaseManip(hAmbi,xmlState->getIntAttribute("PhaseManip", 1));
            
            if(xmlState->hasAttribute("ENABLEROT"))
                ambi_bin_setEnableRotation(hAmbi, xmlState->getIntAttribute("ENABLEROT", 0));
            if(xmlState->hasAttribute("YAW"))
                ambi_bin_setYaw(hAmbi, (float)xmlState->getDoubleAttribute("YAW", 0.0f));
            if(xmlState->hasAttribute("PITCH"))
                ambi_bin_setPitch(hAmbi, (float)xmlState->getDoubleAttribute("PITCH", 0.0f));
            if(xmlState->hasAttribute("ROLL"))
                ambi_bin_setRoll(hAmbi, (float)xmlState->getDoubleAttribute("ROLL", 0.0f));
            if(xmlState->hasAttribute("FLIP_YAW"))
                ambi_bin_setFlipYaw(hAmbi, xmlState->getIntAttribute("FLIP_YAW", 0));
            if(xmlState->hasAttribute("FLIP_PITCH"))
                ambi_bin_setFlipPitch(hAmbi, xmlState->getIntAttribute("FLIP_PITCH", 0));
            if(xmlState->hasAttribute("FLIP_ROLL"))
                ambi_bin_setFlipRoll(hAmbi, xmlState->getIntAttribute("FLIP_ROLL", 0));
            if(xmlState->hasAttribute("RPY_FLAG"))
                ambi_bin_setRPYflag(hAmbi, xmlState->getIntAttribute("RPY_FLAG", 0));
            
            if(xmlState->hasAttribute("OSC_PORT")){
                osc_port_ID = xmlState->getIntAttribute("OSC_PORT", DEFAULT_OSC_PORT);
                osc.connect(osc_port_ID);
            }
            
            if(xmlState->hasAttribute("SofaFilePath")){
                String directory = xmlState->getStringAttribute("SofaFilePath", "no_file");
                const char* new_cstring = (const char*)directory.toUTF8();
                ambi_bin_setSofaFilePath(hAmbi, new_cstring);
            }
            
            ambi_bin_refreshParams(hAmbi);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

