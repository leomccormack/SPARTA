
#include "PluginProcessor.h"
#include "PluginEditor.h"

PluginProcessor::PluginProcessor()
{
	nHostBlockSize = FRAME_SIZE;
	nSampleRate = 48000;

	ringBufferInputs = new float*[MAX_NUM_CHANNELS];
	for (int i = 0; i < MAX_NUM_CHANNELS; i++)
		ringBufferInputs[i] = new float[FRAME_SIZE];

	ringBufferOutputs = new float*[MAX_NUM_CHANNELS];
	for (int i = 0; i < MAX_NUM_CHANNELS; i++)
		ringBufferOutputs[i] = new float[FRAME_SIZE];

	sfcropaclib_create(&hSfcropac);
}

PluginProcessor::~PluginProcessor()
{
	sfcropaclib_destroy(&hSfcropac);

	for (int i = 0; i < MAX_NUM_CHANNELS; ++i) {
		delete[] ringBufferInputs[i];
	}
	delete[] ringBufferInputs;

	for (int i = 0; i < MAX_NUM_CHANNELS; ++i) {
		delete[] ringBufferOutputs[i];
	}
	delete[] ringBufferOutputs;
}

void PluginProcessor::setParameter (int index, float newValue)
{
	switch (index)
	{
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
    return String::empty;
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
	nSampleRate = (int)(sampleRate + 0.5);

    nNumInputs = getNumInputChannels();
    nNumOutputs = getNumOutputChannels();

	setPlayConfigDetails(nNumInputs, nNumOutputs, (double)nSampleRate, nHostBlockSize);	
	numChannelsChanged(); 

	for (int i = 0; i < MAX_NUM_CHANNELS; ++i) {
		memset(ringBufferInputs[i], 0, FRAME_SIZE * sizeof(float));
	}
	for (int i = 0; i < MAX_NUM_CHANNELS; ++i) {
		memset(ringBufferOutputs[i], 0, FRAME_SIZE * sizeof(float));
	}
	wIdx = 1; rIdx = 1; /* read/write indices for ring buffers */

#ifdef ENABLE_IS_PLAYING_CHECK
	isPlaying = false;
#endif

	sfcropaclib_init(hSfcropac, sampleRate);
}

void PluginProcessor::releaseResources()
{
    isPlaying = false;
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	int nCurrentBlockSize = buffer.getNumSamples();
	float** bufferData = buffer.getArrayOfWritePointers();
	float** outputs = new float*[nNumOutputs];
	for (int i = 0; i < nNumOutputs; i++) {
		outputs[i] = new float[FRAME_SIZE];
	}

#ifdef ENABLE_IS_PLAYING_CHECK
	playHead = getPlayHead();
	bool PlayHeadAvailable = playHead->getCurrentPosition(currentPosition);
	if (PlayHeadAvailable == true)
		isPlaying = currentPosition.isPlaying;
	else
		isPlaying = false;

	if (isPlaying) {
#endif
		switch (nCurrentBlockSize) {   

		case FRAME_SIZE: 
			sfcropaclib_process(hSfcropac, bufferData, outputs, nNumInputs, nNumOutputs, FRAME_SIZE);
			buffer.clear();
			for (int ch = 0; ch < nNumOutputs; ch++) {
				for (int i = 0; i < FRAME_SIZE; i++) {
					bufferData[ch][i] = outputs[ch][i];
				}
			}
			break;

		default:
			buffer.clear();
			break;
		}
#ifdef ENABLE_IS_PLAYING_CHECK
	}
#endif

	if (nHostBlockSize == (FRAME_SIZE / 2)) {
		wIdx++; if (wIdx > 1) { wIdx = 0; }
		rIdx++; if (rIdx > 1) { rIdx = 0; }
	}

	for (int i = 0; i < nNumOutputs; ++i) {
		delete[] outputs[i];
	}
	delete[] outputs;
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
	XmlElement xml("SFCROPACAUDIOPLUGINSETTINGS");

	/* add attributes */
	//xml.setAttribute("POWERMAP_MODE", (int)accropaclib_getPowermapMode(hAccropac));
	//xml.setAttribute("_360DEG_MODE", accropaclib_get360degMode(hAccropac));
 
	/* then use this helper function to stuff it into the binary blob and return it.. */
	copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	/* This getXmlFromBinary() function retrieves XML from the binary blob */
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr) {
		/* make sure that it's actually the correct type of XML object */
		if (xmlState->hasTagName("SFCROPACAUDIOPLUGINSETTINGS")) {
			/* pull attributes */
           // accropaclib_setPowermapMode(hAccropac, xmlState->getIntAttribute("POWERMAP_MODE", 1));
			//accropaclib_set360degMode(hAccropac, xmlState->getIntAttribute("_360DEG_MODE", 1));
        }

	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

