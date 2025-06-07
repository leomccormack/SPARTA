
#include "PluginProcessor.h"
#include "PluginEditor.h"

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

//enum {
//    /* For the default VST GUI */
//    k_inputOrder,
//    k_channelOrder,
//    k_normType,
//    k_theshold,
//    k_ratio,
//    k_knee,
//    k_inGain,
//    k_outGain,
//    k_attack_ms,
//    k_release_ms,
//    k_NumOfParameters
//};

juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("inputOrder", "InputOrder",
                                                                  juce::StringArray{"1st","2nd","3rd","4th","5th","6th","7th","8th","9th","10th"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("channelOrder", "ChannelOrder", juce::StringArray{"ACN", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("normType", "NormType", juce::StringArray{"N3D", "SN3D", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("threshold", "Threshold", juce::NormalisableRange<float>(-60.0f, 0.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ratio", "Ratio", juce::NormalisableRange<float>(1.0f, 30.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("knee", "Knee", juce::NormalisableRange<float>(0.0f, 10.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("inGain", "InGain", juce::NormalisableRange<float>(-20.0f, 12.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("outGain", "OutGain", juce::NormalisableRange<float>(-20.0f, 12.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("attack_ms", "Attack_ms", juce::NormalisableRange<float>(10.0f, 200.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("release_ms", "Release_ms", juce::NormalisableRange<float>(50.0f, 1000.0f, 0.01f), 0.0f));
    
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

PluginProcessor::PluginProcessor() :
	AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)
	    .withOutput("Output", AudioChannelSet::discreteChannels(getMaxNumChannelsForFormat(juce::PluginHostType::getPluginLoadedAs())), true)),
    ParameterManager(*this, createParameterLayout())
{
	nSampleRate = 48000;
	ambi_drc_create(&hAmbi);
    
    /* Grab defaults */
    setParameterValue("inputOrder", ambi_drc_getInputPreset(hAmbi)-1, false);
    setParameterValue("channelOrder", ambi_drc_getChOrder(hAmbi)-1, false);
    setParameterValue("normType", ambi_drc_getNormType(hAmbi)-1, false);
    setParameterValue("threshold", ambi_drc_getThreshold(hAmbi), false);
    setParameterValue("ratio", ambi_drc_getRatio(hAmbi), false);
    setParameterValue("knee", ambi_drc_getKnee(hAmbi), false);
    setParameterValue("inGain", ambi_drc_getInGain(hAmbi), false);
    setParameterValue("outGain", ambi_drc_getOutGain(hAmbi), false);
    setParameterValue("attack_ms", ambi_drc_getAttack(hAmbi), false);
    setParameterValue("release_ms", ambi_drc_getRelease(hAmbi), false);
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
    
    /* Save */
    copyXmlToBinary(*xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("AMBIDRCPLUGINSETTINGS") && JucePlugin_VersionCode>=0x10301){
        parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
        
        ambi_drc_refreshSettings(hAmbi);
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

