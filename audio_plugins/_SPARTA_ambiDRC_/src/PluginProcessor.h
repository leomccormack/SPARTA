

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "JuceHeader.h"
#include "ambi_drc.h"

#define MAX_NUM_CHANNELS 64
#define BUILD_VER_SUFFIX "alpha"


enum {	
    /* For the default VST GUI */
	k_NumOfParameters
};

class PluginProcessor  : public AudioProcessor
{
public:
    int nNumInputs;                         /* current number of input channels */
	int nNumOutputs;                        /* current number of output channels */
	int nSampleRate;                        /* current host sample rate */
    int nHostBlockSize;                     /* typical host block size to expect, in samples */ 
    void* hAmbi;                            /* dynamic range compressor handle */

	bool isPlaying;       
	AudioPlayHead* playHead;                /* Used to determine whether playback is currently occuring */
	AudioPlayHead::CurrentPositionInfo currentPosition;
    
    int getCurrentBlockSize(){
        return nHostBlockSize;
    }

	float** ringBufferInputs;
	float** ringBufferOutputs;

    /***************************************************************************\
                                    JUCE Functions
    \***************************************************************************/
public:
    PluginProcessor();
    ~PluginProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;
    const String getName() const;
    int getNumParameters();
    float getParameter (int index);
    void setParameter (int index, float newValue);
    const String getParameterName (int index);
    const String getParameterText (int index);
    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;    
    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;
    int getNumPrograms();
    int getCurrentProgram();
	void setCurrentProgram(int index);
	const String getProgramName(int index);
	bool isInputChannelStereoPair (int index) const;
	bool isOutputChannelStereoPair(int index) const;
	void changeProgramName(int index, const String& newName);
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
