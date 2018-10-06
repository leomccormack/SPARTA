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
#include "binauraliser.h"
#define CONFIGURATIONHELPER_ENABLE_LOUDSPEAKERLAYOUT_METHODS 1
#define CONFIGURATIONHELPER_ENABLE_SOURCEARRANGEMENT_METHODS 1
#include "ConfigurationHelper.h"


#define BUILD_VER_SUFFIX "alpha"            /* String to be added before the version name on the GUI (e.g. beta, alpha etc..) */
#define MAX_NUM_CHANNELS 64
#define NUM_OF_AUTOMATABLE_SOURCES 32

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
    void* hBin;                             /* binauraliser handle */
 
    float** ringBufferInputs;
    float** ringBufferOutputs;
 
    bool isPlaying;
	AudioPlayHead* playHead;                /* Used to determine whether playback is currently occuring */
	AudioPlayHead::CurrentPositionInfo currentPosition;
    
    int getCurrentBlockSize(){
        return nHostBlockSize;
    }
    
    /* JSON */
    void saveConfigurationToFile (File destination);
    void loadConfiguration (const File& presetFile);
    ValueTree sources {"Sources"};
    void setLastDir(File newLastDir){ lastDir = newLastDir; }
    File getLastDir() {return lastDir;};
    File lastDir;
    
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
