/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginProcessor::PluginProcessor() :
    AudioProcessor(BusesProperties()
                   .withInput("Input", AudioChannelSet::discreteChannels(64), true)
                   .withOutput("Output", AudioChannelSet::discreteChannels(64), true))
{
    nSampleRate = 48000;
    nHostBlockSize = -1;
    tvconv_create(&hTVCnv);
    refreshWindow = true;
}

PluginProcessor::~PluginProcessor()
{
    tvconv_destroy(&hTVCnv);
}

//==============================================================================

const juce::String PluginProcessor::getName() const
{
    return JucePlugin_Name;
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

bool PluginProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

void PluginProcessor::setCurrentProgram (int /*index*/)
{
}

const juce::String PluginProcessor::getProgramName (int /*index*/)
{
    return {};
}

void PluginProcessor::changeProgramName (int /*index*/, const juce::String& /*newName*/)
{
}

//==============================================================================
int PluginProcessor::getNumParameters()
{
    return k_NumOfParameters;
}

float PluginProcessor::getParameter(int index)
{
    if (index < 3) {
        if (tvconv_getMaxDimension(hTVCnv, index) > tvconv_getMinDimension(hTVCnv, index)){
            return (tvconv_getPosition(hTVCnv, index)-tvconv_getMinDimension(hTVCnv, index))/
                (tvconv_getMaxDimension(hTVCnv, index)-tvconv_getMinDimension(hTVCnv, index));
        }
    }
    return 0.0f;
}

const String PluginProcessor::getParameterName (int index)
{
    switch (index) {
        case k_receiverCoordX: return "receiver_coordinate_x";
        case k_receiverCoordY: return "receiver_coordinate_y";
        case k_receiverCoordZ: return "receiver_coordinate_z";
        default: return "NULL";
    }
}

const String PluginProcessor::getParameterText(int index)
{
    if (index < 3) {
        return String(tvconv_getPosition(hTVCnv, index));
    }
    else return "NULL";
}

void PluginProcessor::setParameter (int index, float newValue)
{
    float newValueScaled;
    if (index < 3) {
        newValueScaled = newValue *
        (tvconv_getMaxDimension(hTVCnv, index) - tvconv_getMinDimension(hTVCnv, index)) +
        tvconv_getMinDimension(hTVCnv, index);
        if (newValueScaled != tvconv_getPosition(hTVCnv, index)){
            tvconv_setPosition(hTVCnv, index, newValueScaled);
            refreshWindow = true;
        }
    }
}

//==============================================================================
void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    nHostBlockSize = samplesPerBlock;
    nNumInputs =  getTotalNumInputChannels();
    nNumOutputs = getTotalNumOutputChannels();
    nSampleRate = (int)(sampleRate + 0.5);
    //isPlaying = false;

    tvconv_init(hTVCnv, nSampleRate, nHostBlockSize);
    AudioProcessor::setLatencySamples(tvconv_getProcessingDelay(hTVCnv));
}

void PluginProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PluginProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels());
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels());
    float** bufferData = buffer.getArrayOfWritePointers();

    tvconv_process(hTVCnv, bufferData, bufferData, nNumInputs, nNumOutputs, nCurrentBlockSize);
}

//==============================================================================
bool PluginProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (this);
}

//==============================================================================
void PluginProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    /* Create an outer XML element.. */
    XmlElement xml("TVCONVAUDIOPLUGINSETTINGS");
    xml.setAttribute("LastSofaFilePath", tvconv_getSofaFilePath(hTVCnv));
    xml.setAttribute("ReceiverX", tvconv_getPosition(hTVCnv, 0));
    xml.setAttribute("ReceiverY", tvconv_getPosition(hTVCnv, 1));
    xml.setAttribute("ReceiverZ", tvconv_getPosition(hTVCnv, 2));
    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    /* This getXmlFromBinary() function retrieves XML from the binary blob */
        std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

        if (xmlState != nullptr) {
            /* make sure that it's actually the correct XML object */
            if (xmlState->hasTagName("TVCONVAUDIOPLUGINSETTINGS")) {
     
                if(xmlState->hasAttribute("LastSofaFilePath")){
                    String directory = xmlState->getStringAttribute("LastSofaFilePath", "no_file");
                    const char* new_cstring = (const char*)directory.toUTF8();
                    tvconv_setSofaFilePath(hTVCnv, new_cstring);
                }
                if (xmlState->hasAttribute("ReceiverX")){
                    tvconv_setPosition(hTVCnv, 0,
                        (float)xmlState->getDoubleAttribute("ReceiverX"));
                }
                if (xmlState->hasAttribute("ReceiverY")){
                    tvconv_setPosition(hTVCnv, 1,
                        (float)xmlState->getDoubleAttribute("ReceiverY"));
                }
                if (xmlState->hasAttribute("ReceiverZ")){
                    tvconv_setPosition(hTVCnv, 2,
                        (float)xmlState->getDoubleAttribute("ReceiverZ"));
                }
                
                tvconv_refreshParams(hTVCnv);
            }
        }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}
