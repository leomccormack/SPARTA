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
#include "../../resources/PluginProcessorBase.h"
#include "dirass.h"
#include <thread>
#include <atomic>
#define BUILD_VER_SUFFIX ""                 /* String to be added before the version name on the GUI (e.g. beta, alpha etc..) */

class PluginProcessor  : public PluginProcessorBase,
                         public Timer
{
public:
    PluginProcessor();
    ~PluginProcessor();

    /* PluginProcessorBase mandatory overrides */
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    
    /* PluginEditor */
    juce::AudioProcessorEditor* createEditor() override;
    
    /* Get functions */
    void* getFXHandle() { return hDir; }
    bool getIsPlaying() { return isPlaying; }
    
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
    std::atomic<bool> isPlaying;
    int cameraID;
    bool flipLR, flipUD, greyScale;
    AudioPlayHead* playHead; /* Used to determine whether playback is currently ongoing */
    AudioPlayHead::CurrentPositionInfo currentPosition;
    
    /* For syncing parameter values between the JUCE parameter tree and the internal DSP object */
    void setParameterValuesUsingInternalState();
    void setInternalStateUsingParameterValues();

    void timerCallback() override
    {
        /* reinitialise codec if needed */
        if(dirass_getCodecStatus(hDir) == CODEC_STATUS_NOT_INITIALISED){
            try{
                std::thread threadInit(dirass_initCodec, hDir);
                threadInit.detach();
            } catch (const std::exception& exception) {
                std::cout << "Could not create thread" << exception.what() << std::endl;
            }
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
