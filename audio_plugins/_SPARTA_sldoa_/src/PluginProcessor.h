/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2017/2018 - Leo McCormack.
 
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

#include "JuceHeader.h"
#include "sldoa.h"

#define MAX_NUM_CHANNELS 64
#define BUILD_VER_SUFFIX "alpha"

#ifndef MIN
  #define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
  #define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif

enum {	
    /* For the default VST GUI */
	k_NumOfParameters
};

class PluginProcessor  : public AudioProcessor
{
public:
    int nNumInputs;                         /* current number of input channels */
	int nSampleRate;                        /* current host sample rate */
    int nHostBlockSize;                     /* typical host block size to expect, in samples */ 
    void* hSld;                             /* handle */
	 
	bool isPlaying;
	AudioPlayHead* playHead;                /* Used to determine whether playback is currently occuring */
	AudioPlayHead::CurrentPositionInfo currentPosition;

	float** ringBufferInputs; 
	int wIdx, rIdx;

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
