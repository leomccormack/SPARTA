/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2019 - Leo McCormack.
 
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

#include <JuceHeader.h>
#include "dirass.h"
#include <thread>
#define BUILD_VER_SUFFIX ""                 /* String to be added before the version name on the GUI (e.g. beta, alpha etc..) */

typedef enum _TIMERS{
    TIMER_PROCESSING_RELATED = 1,
    TIMER_GUI_RELATED
}TIMERS;

enum {	
    /* For the default VST GUI */
	k_NumOfParameters
};

class PluginProcessor  : public AudioProcessor,
                         public MultiTimer,
                         public VST2ClientExtensions
{
public:
    /* Get functions */
    void* getFXHandle() { return hDir; }
	bool getIsPlaying() { return isPlaying; }
    int getCurrentBlockSize(){ return nHostBlockSize; }
    int getCurrentNumInputs(){ return nNumInputs; }
    
    /* VST CanDo */
    pointer_sized_int handleVstManufacturerSpecific (int32 /*index*/, pointer_sized_int /*value*/, void* /*ptr*/, float /*opt*/) override { return 0; }
    pointer_sized_int handleVstPluginCanDo (int32 /*index*/, pointer_sized_int /*value*/, void* ptr, float /*opt*/) override{
        auto text = (const char*) ptr;
        auto matches = [=](const char* s) { return strcmp (text, s) == 0; };
        if (matches ("wantsChannelCountNotifications"))
            return 1;
        return 0;
    }
    VST2ClientExtensions* getVST2ClientExtensions() override {return this;}
    
    /* for camera */
    void setCameraID(int newID){ cameraID = newID;}
    void setFlipLR(bool newState){ flipLR = newState;}
    void setFlipUD(bool newState){ flipUD = newState;}
    void setGreyScale(bool newState){ greyScale = newState;}
    int getCameraID(){ return cameraID;}
    bool getFlipLR(){ return flipLR;}
    bool getFlipUD(){ return flipUD;}
    bool getGreyScale(){ return greyScale;}
    
private:
    void* hDir;                             /* dirass handle */
    int nNumInputs;                         /* current number of input channels */
    int nSampleRate;                        /* current host sample rate */
    int nHostBlockSize;                     /* typical host block size to expect, in samples */
    bool isPlaying;
    int cameraID;
    bool flipLR, flipUD, greyScale;
    AudioPlayHead* playHead; /* Used to determine whether playback is currently ongoing */
    AudioPlayHead::CurrentPositionInfo currentPosition;
    
    void timerCallback(int timerID) override
    {
        switch(timerID){
            case TIMER_PROCESSING_RELATED:
                /* reinitialise codec if needed */
                if(dirass_getCodecStatus(hDir) == CODEC_STATUS_NOT_INITIALISED){
                    try{
                        std::thread threadInit(dirass_initCodec, hDir);
                        threadInit.detach();
                    } catch (const std::exception& exception) {
                        std::cout << "Could not create thread" << exception.what() << std::endl;
                    }
                }
                break;
            case TIMER_GUI_RELATED:
                /* handled in PluginEditor */
                break;
        }
    }
 
public:
    PluginProcessor();
    ~PluginProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const String getName() const override;
    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;
    const String getParameterName (int index) override;
    const String getParameterText (int index) override;
    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair(int index) const override;
    void changeProgramName(int index, const String& newName) override;
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
