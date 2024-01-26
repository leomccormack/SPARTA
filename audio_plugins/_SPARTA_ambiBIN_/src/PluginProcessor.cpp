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
        .withOutput("Output", AudioChannelSet::discreteChannels(2), true))
{
	ambi_bin_create(&hAmbi);
  
    /* specify here on which UDP port number to receive incoming OSC messages */
    osc_port_ID = DEFAULT_OSC_PORT;
    osc.connect(osc_port_ID);
    /* tell the component to listen for OSC messages */
    osc.addListener(this);
    
    startTimer(TIMER_PROCESSING_RELATED, 40); 
}

PluginProcessor::~PluginProcessor()
{
    osc.disconnect();
    osc.removeListener(this);
    
	ambi_bin_destroy(&hAmbi);
}

void PluginProcessor::oscMessageReceived(const OSCMessage& message)
{
    /* if rotation angles are sent as an array \ypr[3] */
    if (message.size() == 3 && message.getAddressPattern().toString().compare("/ypr")==0) {
        if (message[0].isFloat32())
            ambi_bin_setYaw(hAmbi, message[0].getFloat32());
        if (message[1].isFloat32())
            ambi_bin_setPitch(hAmbi, message[1].getFloat32());
        if (message[2].isFloat32())
            ambi_bin_setRoll(hAmbi, message[2].getFloat32());
        return;
    }
    
    /* if rotation angles are sent individually: */
    if(message.getAddressPattern().toString().compare("/yaw")==0)
        ambi_bin_setYaw(hAmbi, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/pitch")==0)
        ambi_bin_setPitch(hAmbi, message[0].getFloat32());
    else if(message.getAddressPattern().toString().compare("/roll")==0)
        ambi_bin_setRoll(hAmbi, message[0].getFloat32());
}

void PluginProcessor::setParameter (int index, float newValue)
{
    switch (index) {
        case k_inputOrder:            ambi_bin_setInputOrderPreset(hAmbi, (SH_ORDERS)(int)(newValue*(float)(MAX_SH_ORDER-1) + 1.5f)); break;
        case k_channelOrder:          ambi_bin_setChOrder(hAmbi, (int)(newValue*(float)(NUM_CH_ORDERINGS-1) + 1.5f)); break;
        case k_normType:              ambi_bin_setNormType(hAmbi, (int)(newValue*(float)(NUM_NORM_TYPES-1) + 1.5f)); break;
        case k_decMethod:             ambi_bin_setDecodingMethod(hAmbi, (AMBI_BIN_DECODING_METHODS)(int)(newValue*(float)(AMBI_BIN_NUM_DECODING_METHODS-1) + 1.5f)); break;
        case k_enableDiffuseMatching: ambi_bin_setEnableDiffuseMatching(hAmbi, (int)(newValue + 0.5f)); break;
        case k_enableMaxRE:           ambi_bin_setEnableMaxRE(hAmbi, (int)(newValue + 0.5f)); break;
        case k_enableRotation:        ambi_bin_setEnableRotation(hAmbi, (int)(newValue + 0.5f)); break;
        case k_useRollPitchYaw:       ambi_bin_setRPYflag(hAmbi, (int)(newValue + 0.5f)); break;
        case k_yaw:                   ambi_bin_setYaw(hAmbi, (newValue-0.5f)*360.0f ); break;
        case k_pitch:                 ambi_bin_setPitch(hAmbi, (newValue - 0.5f)*180.0f); break;
        case k_roll:                  ambi_bin_setRoll(hAmbi, (newValue - 0.5f)*180.0f); break;
        case k_flipYaw:               ambi_bin_setFlipYaw(hAmbi, (int)(newValue + 0.5f));  break;
        case k_flipPitch:             ambi_bin_setFlipPitch(hAmbi, (int)(newValue + 0.5f)); break;
        case k_flipRoll:              ambi_bin_setFlipRoll(hAmbi, (int)(newValue + 0.5f)); break;
         
        default: break;
    }
}

void PluginProcessor::setCurrentProgram (int /*index*/)
{
}

float PluginProcessor::getParameter (int index)
{
    switch (index) {
        case k_inputOrder:            return (float)(ambi_bin_getInputOrderPreset(hAmbi)-1)/(float)(MAX_SH_ORDER-1);
        case k_channelOrder:          return (float)(ambi_bin_getChOrder(hAmbi)-1)/(float)(NUM_NORM_TYPES-1);
        case k_normType:              return (float)(ambi_bin_getNormType(hAmbi)-1)/(float)(NUM_NORM_TYPES-1);
        case k_decMethod:             return (float)(ambi_bin_getDecodingMethod(hAmbi)-1)/(float)(AMBI_BIN_NUM_DECODING_METHODS-1);
        case k_enableDiffuseMatching: return (float)ambi_bin_getEnableDiffuseMatching(hAmbi);
        case k_enableMaxRE:           return (float)ambi_bin_getEnableMaxRE(hAmbi);
        case k_enableRotation:        return (float)ambi_bin_getEnableRotation(hAmbi);
        case k_useRollPitchYaw:       return (float)ambi_bin_getRPYflag(hAmbi);
        case k_yaw:                   return (ambi_bin_getYaw(hAmbi)/360.0f) + 0.5f;
        case k_pitch:                 return (ambi_bin_getPitch(hAmbi)/180.0f) + 0.5f;
        case k_roll:                  return (ambi_bin_getRoll(hAmbi)/180.0f) + 0.5f;
        case k_flipYaw:               return (float)ambi_bin_getFlipYaw(hAmbi);
        case k_flipPitch:             return (float)ambi_bin_getFlipPitch(hAmbi);
        case k_flipRoll:              return (float)ambi_bin_getFlipRoll(hAmbi);
        
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
    switch (index) {
        case k_inputOrder:            return "order";
        case k_channelOrder:          return "channel_order";
        case k_normType:              return "norm_type";
        case k_decMethod:             return "decode_method";
        case k_enableDiffuseMatching: return "apply_diff_match";
        case k_enableMaxRE:           return "apply_maxre_weights";
        case k_enableRotation:        return "enable_rotation";
        case k_useRollPitchYaw:       return "use_rpy";
        case k_yaw:                   return "yaw";
        case k_pitch:                 return "pitch";
        case k_roll:                  return "roll";
        case k_flipYaw:               return "flip_yaw";
        case k_flipPitch:             return "flip_pitch";
        case k_flipRoll:              return "flip_roll";
       
        default: return "NULL";
    }
}

const String PluginProcessor::getParameterText(int index)
{
    switch (index) {
        case k_inputOrder: return String(ambi_bin_getInputOrderPreset(hAmbi));
        case k_channelOrder:
            switch(ambi_bin_getChOrder(hAmbi)){
                case CH_ACN:  return "ACN";
                case CH_FUMA: return "FuMa";
                default: return "NULL";
            }
        case k_normType:
            switch(ambi_bin_getNormType(hAmbi)){
                case NORM_N3D:  return "N3D";
                case NORM_SN3D: return "SN3D";
                case NORM_FUMA: return "FuMa";
                default: return "NULL";
            }
        case k_decMethod:
            switch(ambi_bin_getDecodingMethod(hAmbi)){
                case DECODING_METHOD_LS:       return "LS";
                case DECODING_METHOD_LSDIFFEQ: return "LS-DiffEQ";
                case DECODING_METHOD_SPR:      return "SPR";
                case DECODING_METHOD_TA:       return "TA";
                case DECODING_METHOD_MAGLS:    return "Mag-LS";
                default: return "NULL";
            }
        case k_enableDiffuseMatching: return !ambi_bin_getEnableDiffuseMatching(hAmbi) ? "Off" : "On";
        case k_enableMaxRE:           return !ambi_bin_getEnableMaxRE(hAmbi) ? "Off" : "On";
        case k_enableRotation:        return !ambi_bin_getEnableRotation(hAmbi) ? "Off" : "On";
        case k_useRollPitchYaw:       return !ambi_bin_getRPYflag(hAmbi) ? "YPR" : "RPY";
        case k_yaw:                   return String(ambi_bin_getYaw(hAmbi));
        case k_pitch:                 return String(ambi_bin_getPitch(hAmbi));
        case k_roll:                  return String(ambi_bin_getRoll(hAmbi));
        case k_flipYaw:               return !ambi_bin_getFlipYaw(hAmbi) ? "No-Flip" : "Flip";
        case k_flipPitch:             return !ambi_bin_getFlipPitch(hAmbi) ? "No-Flip" : "Flip";
        case k_flipRoll:              return !ambi_bin_getFlipRoll(hAmbi) ? "No-Flip" : "Flip";
            
        default: return "NULL";
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

bool PluginProcessor::isBusesLayoutSupported(const BusesLayout& /*layouts*/) const
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

	ambi_bin_init(hAmbi, nSampleRate);
    AudioProcessor::setLatencySamples(ambi_bin_getProcessingDelay());
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
    int frameSize = ambi_bin_getFrameSize();

    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            ambi_bin_process(hAmbi, pFrameData, pFrameData, nNumInputs, nNumOutputs, frameSize);
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
    
    xml.setAttribute("order", ambi_bin_getInputOrderPreset(hAmbi));
  
    xml.setAttribute("UseDefaultHRIRset", ambi_bin_getUseDefaultHRIRsflag(hAmbi));
    xml.setAttribute("Norm", ambi_bin_getNormType(hAmbi));
    xml.setAttribute("ChOrder", ambi_bin_getChOrder(hAmbi));
    xml.setAttribute("maxrE", ambi_bin_getEnableMaxRE(hAmbi));
    xml.setAttribute("diffMatch", ambi_bin_getEnableDiffuseMatching(hAmbi));
    xml.setAttribute("truncationEQ", ambi_bin_getEnableTruncationEQ(hAmbi));
    xml.setAttribute("method", ambi_bin_getDecodingMethod(hAmbi));
    xml.setAttribute("preproc", ambi_bin_getHRIRsPreProc(hAmbi));
    
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
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr) {
        if (xmlState->hasTagName("AMBIBINPLUGINSETTINGS")) {
            
            if(xmlState->hasAttribute("order"))
                ambi_bin_setInputOrderPreset(hAmbi, (SH_ORDERS)xmlState->getIntAttribute("order", 2));
            if(xmlState->hasAttribute("UseDefaultHRIRset"))
                ambi_bin_setUseDefaultHRIRsflag(hAmbi, xmlState->getIntAttribute("UseDefaultHRIRset", 1));
            if(xmlState->hasAttribute("Norm"))
                ambi_bin_setNormType(hAmbi, xmlState->getIntAttribute("Norm", 1));
            if(xmlState->hasAttribute("ChOrder"))
                ambi_bin_setChOrder(hAmbi, xmlState->getIntAttribute("ChOrder", 1));
            if(xmlState->hasAttribute("maxrE"))
                ambi_bin_setEnableMaxRE(hAmbi,xmlState->getIntAttribute("maxrE", 1));
            if(xmlState->hasAttribute("diffMatch"))
                ambi_bin_setEnableDiffuseMatching(hAmbi,xmlState->getIntAttribute("diffMatch", 1));
            if(xmlState->hasAttribute("truncationEQ"))
                ambi_bin_setEnableTruncationEQ(hAmbi,xmlState->getIntAttribute("truncationEQ", 1));
            if(xmlState->hasAttribute("method"))
                ambi_bin_setDecodingMethod(hAmbi, (AMBI_BIN_DECODING_METHODS)xmlState->getIntAttribute("method", 1));
            if(xmlState->hasAttribute("preproc"))
                ambi_bin_setHRIRsPreProc(hAmbi, (AMBI_BIN_PREPROC)xmlState->getIntAttribute("preproc", 1));
            
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

