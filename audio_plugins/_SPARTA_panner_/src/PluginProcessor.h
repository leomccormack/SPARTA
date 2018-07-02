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
#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "panner.h"

#define BUILD_VER_SUFFIX "alpha"            /* String to be added before the version name on the GUI (e.g. beta, alpha etc..) */
#define MAX_NUM_CHANNELS 64

enum {	
    /* For the default VST GUI */
    k_nSources,
    k_srcAzi_0, k_srcElev_0,
    k_srcAzi_1, k_srcElev_1,
    k_srcAzi_2, k_srcElev_2,
    k_srcAzi_3, k_srcElev_3,
    k_srcAzi_4, k_srcElev_4,
    k_srcAzi_5, k_srcElev_5,
    k_srcAzi_6, k_srcElev_6,
    k_srcAzi_7, k_srcElev_7,
    k_srcAzi_8, k_srcElev_8,
    k_srcAzi_9, k_srcElev_9,
    k_srcAzi_10, k_srcElev_10,
    k_srcAzi_11, k_srcElev_11,
    k_srcAzi_12, k_srcElev_12,
    k_srcAzi_13, k_srcElev_13,
    k_srcAzi_14, k_srcElev_14,
    k_srcAzi_15, k_srcElev_15,
    k_srcAzi_16, k_srcElev_16,
    k_srcAzi_17, k_srcElev_17,
    k_srcAzi_18, k_srcElev_18,
    k_srcAzi_19, k_srcElev_19,
    k_srcAzi_20, k_srcElev_20,
    k_srcAzi_21, k_srcElev_21,
    k_srcAzi_22, k_srcElev_22,
    k_srcAzi_23, k_srcElev_23,
    k_srcAzi_24, k_srcElev_24,
    k_srcAzi_25, k_srcElev_25,
    k_srcAzi_26, k_srcElev_26,
    k_srcAzi_27, k_srcElev_27,
    k_srcAzi_28, k_srcElev_28,
    k_srcAzi_29, k_srcElev_29,
    k_srcAzi_30, k_srcElev_30,
    k_srcAzi_31, k_srcElev_31,
    k_srcAzi_32, k_srcElev_32,
    
    k_NumOfParameters
};

#ifndef MIN
  #define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
  #define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif

class PluginProcessor  : public AudioProcessor
{
public:
    int nNumInputs;                         /* current number of input channels */
	int nNumOutputs;                        /* current number of output channels */
	int nSampleRate;                        /* current host sample rate */
    int nHostBlockSize;                     /* typical host block size to expect, in samples */ 
    void* hPan;                             /* panner handle */
 
    float** ringBufferInputs;
    float** ringBufferOutputs;
    int wIdx, rIdx;
 
    bool isPlaying;
	AudioPlayHead* playHead;                /* Used to determine whether playback is currently occuring */
	AudioPlayHead::CurrentPositionInfo currentPosition;
    
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
