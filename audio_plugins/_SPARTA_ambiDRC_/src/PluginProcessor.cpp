
#include "PluginProcessor.h"
#include "PluginEditor.h"

PluginProcessor::PluginProcessor() : 
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(MAX_NUM_CHANNELS), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(MAX_NUM_CHANNELS), true))
{
	nSampleRate = 48000;
	ambi_drc_create(&hAmbi);
}

PluginProcessor::~PluginProcessor()
{
	ambi_drc_destroy(&hAmbi);
}

void PluginProcessor::setParameter (int index, float newValue)
{
	switch (index)
	{
        case k_inputOrder:   ambi_drc_setInputPreset(hAmbi, (SH_ORDERS)(int)(newValue*(float)(MAX_SH_ORDER-1) + 1.5f)); break;
        case k_channelOrder: ambi_drc_setChOrder(hAmbi, (int)(newValue*(float)(NUM_CH_ORDERINGS-1) + 1.5f)); break;
        case k_normType:     ambi_drc_setNormType(hAmbi, (int)(newValue*(float)(NUM_NORM_TYPES-1) + 1.5f)); break;
        case k_theshold:     ambi_drc_setThreshold(hAmbi, newValue*(AMBI_DRC_THRESHOLD_MAX_VAL-AMBI_DRC_THRESHOLD_MIN_VAL)+AMBI_DRC_THRESHOLD_MIN_VAL); break;
        case k_ratio:        ambi_drc_setRatio(hAmbi, newValue*(AMBI_DRC_RATIO_MAX_VAL-AMBI_DRC_RATIO_MIN_VAL)+AMBI_DRC_RATIO_MIN_VAL); break;
        case k_knee:         ambi_drc_setKnee(hAmbi, newValue*(AMBI_DRC_KNEE_MAX_VAL-AMBI_DRC_KNEE_MIN_VAL)+AMBI_DRC_KNEE_MIN_VAL); break;
        case k_inGain:       ambi_drc_setInGain(hAmbi, newValue*(AMBI_DRC_IN_GAIN_MAX_VAL-AMBI_DRC_IN_GAIN_MIN_VAL)+AMBI_DRC_IN_GAIN_MIN_VAL); break;
        case k_outGain:      ambi_drc_setOutGain(hAmbi, newValue*(AMBI_DRC_OUT_GAIN_MAX_VAL-AMBI_DRC_OUT_GAIN_MIN_VAL)+AMBI_DRC_OUT_GAIN_MIN_VAL); break;
        case k_attack_ms:    ambi_drc_setAttack(hAmbi, newValue*(AMBI_DRC_ATTACK_MAX_VAL-AMBI_DRC_ATTACK_MIN_VAL)+AMBI_DRC_ATTACK_MIN_VAL); break;
        case k_release_ms:   ambi_drc_setRelease(hAmbi, newValue*(AMBI_DRC_RELEASE_MAX_VAL-AMBI_DRC_RELEASE_MIN_VAL)+AMBI_DRC_RELEASE_MIN_VAL); break;
		default: break;
	} 
}

void PluginProcessor::setCurrentProgram (int /*index*/)
{
}

float PluginProcessor::getParameter (int index)
{
    switch (index)
	{
        case k_inputOrder:   return (float)(ambi_drc_getInputPreset(hAmbi)-1)/(float)(MAX_SH_ORDER-1);
        case k_channelOrder: return (float)(ambi_drc_getChOrder(hAmbi)-1)/(float)(NUM_NORM_TYPES-1);
        case k_normType:     return (float)(ambi_drc_getNormType(hAmbi)-1)/(float)(NUM_NORM_TYPES-1);
        case k_theshold:     return (ambi_drc_getThreshold(hAmbi)-AMBI_DRC_THRESHOLD_MIN_VAL)/(AMBI_DRC_THRESHOLD_MAX_VAL-AMBI_DRC_THRESHOLD_MIN_VAL);
        case k_ratio:        return (ambi_drc_getThreshold(hAmbi)-AMBI_DRC_RATIO_MIN_VAL)/(AMBI_DRC_RATIO_MAX_VAL-AMBI_DRC_RATIO_MIN_VAL);
        case k_knee:         return (ambi_drc_getKnee(hAmbi)-AMBI_DRC_KNEE_MIN_VAL)/(AMBI_DRC_KNEE_MAX_VAL-AMBI_DRC_KNEE_MIN_VAL);
        case k_inGain:       return (ambi_drc_getInGain(hAmbi)-AMBI_DRC_IN_GAIN_MIN_VAL)/(AMBI_DRC_IN_GAIN_MAX_VAL-AMBI_DRC_IN_GAIN_MIN_VAL);
        case k_outGain:      return (ambi_drc_getOutGain(hAmbi)-AMBI_DRC_OUT_GAIN_MIN_VAL)/(AMBI_DRC_OUT_GAIN_MAX_VAL-AMBI_DRC_OUT_GAIN_MIN_VAL);
        case k_attack_ms:    return (ambi_drc_getAttack(hAmbi)-AMBI_DRC_ATTACK_MIN_VAL)/(AMBI_DRC_ATTACK_MAX_VAL-AMBI_DRC_ATTACK_MIN_VAL);
        case k_release_ms:   return (ambi_drc_getRelease(hAmbi)-AMBI_DRC_RELEASE_MIN_VAL)/(AMBI_DRC_RELEASE_MAX_VAL-AMBI_DRC_RELEASE_MIN_VAL);
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
        case k_inputOrder:   return "order";
        case k_channelOrder: return "channel_order";
        case k_normType:     return "norm_type";
        case k_theshold:     return "threshold";
        case k_ratio:        return "ratio";
        case k_knee:         return "knee";
        case k_inGain:       return "in_gain";
        case k_outGain:      return "out_gain";
        case k_attack_ms:    return "attack";
        case k_release_ms:   return "release";
		default: return "NULL";
	}
}

const String PluginProcessor::getParameterText(int index)
{
    switch (index)
    {
        case k_inputOrder: return String(ambi_drc_getInputPreset(hAmbi));
        case k_channelOrder:
            switch(ambi_drc_getChOrder(hAmbi)){
                case CH_ACN:  return "ACN";
                case CH_FUMA: return "FuMa";
                default: return "NULL";
            }
        case k_normType:
            switch(ambi_drc_getNormType(hAmbi)){
                case NORM_N3D:  return "N3D";
                case NORM_SN3D: return "SN3D";
                case NORM_FUMA: return "FuMa";
                default: return "NULL";
            }
        case k_theshold:     return String(ambi_drc_getThreshold(hAmbi));
        case k_ratio:        return String(ambi_drc_getRatio(hAmbi));
        case k_knee:         return String(ambi_drc_getKnee(hAmbi));
        case k_inGain:       return String(ambi_drc_getInGain(hAmbi));
        case k_outGain:      return String(ambi_drc_getOutGain(hAmbi));
        case k_attack_ms:    return String(ambi_drc_getAttack(hAmbi));
        case k_release_ms:   return String(ambi_drc_getRelease(hAmbi));
            
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
    return 1;
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
    isPlaying = false;

	ambi_drc_init(hAmbi, nSampleRate);
    AudioProcessor::setLatencySamples(ambi_drc_getProcessingDelay());
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
    int frameSize = ambi_drc_getFrameSize();

    /* check whether the playhead is moving */
    playHead = getPlayHead();
    if(playHead!=nullptr)
        isPlaying = playHead->getCurrentPosition(currentPosition) == true ? currentPosition.isPlaying : false;
    else
        isPlaying = false;

    /* process one frame at a time: */
    if((nCurrentBlockSize % frameSize == 0)){ /* divisible by frame size */
        for (int frame = 0; frame < nCurrentBlockSize/frameSize; frame++) {
            for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                pFrameData[ch] = &bufferData[ch][frame*frameSize];

            /* perform processing */
            ambi_drc_process(hAmbi, pFrameData, pFrameData, nNumInputs < nNumOutputs ? nNumInputs : nNumOutputs, frameSize);
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
	/* Create an outer XML element.. */ 
	XmlElement xml("AMBIDRCAUDIOPLUGINSETTINGS");

	/* add attributes */
	xml.setAttribute("THRESHOLD", ambi_drc_getThreshold(hAmbi));
	xml.setAttribute("RATIO", ambi_drc_getRatio(hAmbi));
	xml.setAttribute("KNEE", ambi_drc_getKnee(hAmbi));
	xml.setAttribute("INGAIN", ambi_drc_getInGain(hAmbi));
    xml.setAttribute("OUTGAIN", ambi_drc_getOutGain(hAmbi));
	xml.setAttribute("ATTACK", ambi_drc_getAttack(hAmbi));
	xml.setAttribute("RELEASE", ambi_drc_getRelease(hAmbi));
    xml.setAttribute("NORM", ambi_drc_getNormType(hAmbi));
    xml.setAttribute("CHORDER", ambi_drc_getChOrder(hAmbi));
    xml.setAttribute("PRESET", ambi_drc_getInputPreset(hAmbi));
 
	copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	/* This getXmlFromBinary() function retrieves XML from the binary blob */
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr) {
		/* make sure that it's actually the correct type of XML object */
		if (xmlState->hasTagName("AMBIDRCAUDIOPLUGINSETTINGS")) {
            
			/* pull attributes */
            if(xmlState->hasAttribute("THRESHOLD"))
                ambi_drc_setThreshold(hAmbi, (float)xmlState->getDoubleAttribute("THRESHOLD", 0.0f));
            if(xmlState->hasAttribute("RATIO"))
                ambi_drc_setRatio(hAmbi, (float)xmlState->getDoubleAttribute("RATIO", 1.0f));
            if(xmlState->hasAttribute("KNEE"))
                ambi_drc_setKnee(hAmbi, (float)xmlState->getDoubleAttribute("KNEE", 0.0f));
            if(xmlState->hasAttribute("INGAIN"))
                ambi_drc_setInGain(hAmbi, (float)xmlState->getDoubleAttribute("INGAIN", 0.0f));
            if(xmlState->hasAttribute("OUTGAIN"))
                ambi_drc_setOutGain(hAmbi, (float)xmlState->getDoubleAttribute("OUTGAIN", 0.0f));
            if(xmlState->hasAttribute("ATTACK"))
                ambi_drc_setAttack(hAmbi, (float)xmlState->getDoubleAttribute("ATTACK", 50.0f));
            if(xmlState->hasAttribute("RELEASE"))
                ambi_drc_setRelease(hAmbi, (float)xmlState->getDoubleAttribute("RELEASE", 100.0f));
            if(xmlState->hasAttribute("NORM"))
                ambi_drc_setNormType(hAmbi, xmlState->getIntAttribute("NORM", 1));
            if(xmlState->hasAttribute("CHORDER"))
                ambi_drc_setChOrder(hAmbi, xmlState->getIntAttribute("CHORDER", 1));
            if(xmlState->hasAttribute("PRESET"))
                ambi_drc_setInputPreset(hAmbi, (SH_ORDERS)xmlState->getIntAttribute("PRESET", 1));
            
            ambi_drc_refreshSettings(hAmbi);
        } 
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

