
#include "PluginProcessor.h"
#include "PluginEditor.h"

#if JucePlugin_Build_AAX && !JucePlugin_AAXDisableDefaultSettingsChunks
# error "AAX Default Settings Chunk is enabled. This may override parameter defaults."
#endif

static int getMaxNumChannelsForFormat(AudioProcessor::WrapperType format) {
    switch(format){
        case juce::AudioProcessor::wrapperType_VST:  /* fall through */
        case juce::AudioProcessor::wrapperType_VST3: /* fall through */
        case juce::AudioProcessor::wrapperType_AAX:
            return 64;
        default:
            return MAX_NUM_CHANNELS;
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("inputOrder", "InputOrder",
                                                                  juce::StringArray{"1st order","2nd order","3rd order","4th order","5th order","6th order","7th order","8th order","9th order","10th order"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("channelOrder", "ChannelOrder", juce::StringArray{"ACN", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("normType", "NormType", juce::StringArray{"N3D", "SN3D", "FuMa"}, 1));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("threshold", "Threshold", juce::NormalisableRange<float>(-60.0f, 6.0f, 0.1f), 0.0f,
                                                                 AudioParameterFloatAttributes().withLabel(" dB")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ratio", "Ratio", juce::NormalisableRange<float>(1.0f, 30.0f, 0.1f), 8.0f,
                                                                 AudioParameterFloatAttributes().withLabel(":1")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("knee", "Knee", juce::NormalisableRange<float>(0.0f, 10.0f, 0.1f), 0.0f,
                                                                 AudioParameterFloatAttributes().withLabel(" dB")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("inGain", "InGain", juce::NormalisableRange<float>(-20.0f, 12.0f, 0.1f), 0.0f,
                                                                 AudioParameterFloatAttributes().withLabel(" dB")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("outGain", "OutGain", juce::NormalisableRange<float>(-20.0f, 12.0f, 0.1f), 0.0f,
                                                                 AudioParameterFloatAttributes().withLabel(" dB")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("attack_ms", "Attack", juce::NormalisableRange<float>(10.0f, 200.0f, 1.0f), 50.0f,
                                                                 AudioParameterFloatAttributes().withLabel(" ms")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("release_ms", "Release", juce::NormalisableRange<float>(50.0f, 1000.0f, 1.0f), 100.0f,
                                                                 AudioParameterFloatAttributes().withLabel(" ms")));
    
    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "inputOrder"){
        ambi_drc_setInputPreset(hAmbi, static_cast<SH_ORDERS>(newValue+1.001f));
    }
    else if (parameterID == "channelOrder"){
        ambi_drc_setChOrder(hAmbi, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "normType"){
        ambi_drc_setNormType(hAmbi, static_cast<int>(newValue+1.001f));
    }
    else if(parameterID == "threshold"){
        ambi_drc_setThreshold(hAmbi, newValue);
    }
    else if(parameterID == "ratio"){
        ambi_drc_setRatio(hAmbi, newValue);
    }
    else if(parameterID == "knee"){
        ambi_drc_setKnee(hAmbi, newValue);
    }
    else if(parameterID == "inGain"){
        ambi_drc_setInGain(hAmbi, newValue);
    }
    else if(parameterID == "outGain"){
        ambi_drc_setOutGain(hAmbi, newValue);
    }
    else if(parameterID == "attack_ms"){
        ambi_drc_setAttack(hAmbi, newValue);
    }
    else if(parameterID == "release_ms"){
        ambi_drc_setRelease(hAmbi, newValue);
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("inputOrder", ambi_drc_getInputPreset(hAmbi)-1);
    setParameterValue("channelOrder", ambi_drc_getChOrder(hAmbi)-1);
    setParameterValue("normType", ambi_drc_getNormType(hAmbi)-1);
    setParameterValue("threshold", ambi_drc_getThreshold(hAmbi));
    setParameterValue("ratio", ambi_drc_getRatio(hAmbi));
    setParameterValue("knee", ambi_drc_getKnee(hAmbi));
    setParameterValue("inGain", ambi_drc_getInGain(hAmbi));
    setParameterValue("outGain", ambi_drc_getOutGain(hAmbi));
    setParameterValue("attack_ms", ambi_drc_getAttack(hAmbi));
    setParameterValue("release_ms", ambi_drc_getRelease(hAmbi));
}

void PluginProcessor::setInternalStateUsingParameterValues()
{
    ambi_drc_setInputPreset(hAmbi, static_cast<SH_ORDERS>(getParameterChoice("inputOrder")+1));
    ambi_drc_setChOrder(hAmbi, getParameterChoice("channelOrder")+1);
    ambi_drc_setNormType(hAmbi, getParameterChoice("normType")+1);
    ambi_drc_setThreshold(hAmbi, getParameterFloat("threshold"));
    ambi_drc_setRatio(hAmbi, getParameterFloat("ratio"));
    ambi_drc_setKnee(hAmbi, getParameterFloat("knee"));
    ambi_drc_setInGain(hAmbi, getParameterFloat("inGain"));
    ambi_drc_setOutGain(hAmbi, getParameterFloat("outGain"));
    ambi_drc_setAttack(hAmbi, getParameterFloat("attack_ms"));
    ambi_drc_setRelease(hAmbi, getParameterFloat("release_ms"));
}

PluginProcessor::PluginProcessor() :
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	nSampleRate = 48000;
	ambi_drc_create(&hAmbi);
    
    /* Grab defaults */
    setParameterValuesUsingInternalState();
}

PluginProcessor::~PluginProcessor()
{
	ambi_drc_destroy(&hAmbi);
}


void PluginProcessor::setCurrentProgram (int /*index*/)
{
}

const String PluginProcessor::getName() const
{
    return JucePlugin_Name;
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
    ScopedNoDenormals noDenormals;
    
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels(), 256);
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels(), 256);
    float* const* bufferData = buffer.getArrayOfWritePointers();
    float* pFrameData[256];
    int frameSize = ambi_drc_getFrameSize();

    /* check whether the playhead is moving */
    playHead = getPlayHead();
    if(playHead!=nullptr)
        isPlaying = playHead->getPosition()->getIsPlaying();
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

bool PluginProcessor::hasEditor() const
{
    return true; 
}

AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (*this);
}

void PluginProcessor::getStateInformation (MemoryBlock& destData)
{
    juce::ValueTree state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    xml->setTagName("AMBIDRCPLUGINSETTINGS");
    xml->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10301
    
    /* Save */
    copyXmlToBinary(*xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("AMBIDRCPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10301
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
            
            setParameterValuesUsingInternalState();
        }
        else if(xmlState->getIntAttribute("VersionCode")>=0x10301){
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            
            /* Many hosts will also trigger parameterChanged() for all parameters after calling setStateInformation() */
            /* However, some hosts do not. Therefore, it is better to ensure that the internal state is always up-to-date by calling: */
            setInternalStateUsingParameterValues();
        }
        
        ambi_drc_refreshSettings(hAmbi);
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

