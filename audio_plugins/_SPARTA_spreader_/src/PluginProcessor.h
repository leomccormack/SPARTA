/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2021 - Leo McCormack.
 
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
#include "spreader.h"
#include <thread>
#include <atomic>

#define BUILD_VER_SUFFIX "" /* String to be added before the version name on the GUI (e.g. beta, alpha etc..) */
#ifndef MIN
# define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
# define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif

class PluginProcessor  : public PluginProcessorBase,
                         public Timer
{
public:
    PluginProcessor();
    ~PluginProcessor();

    /* PluginProcessorBase mandatory overrides */
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {};
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    
    /* PluginEditor */
    juce::AudioProcessorEditor* createEditor() override;
    
    /* Get functions */
    void* getFXHandle() { return hSpr; }
    
    /* For refreshing window during automation */
    bool refreshWindow;
    void setRefreshWindow(bool newState) { refreshWindow = newState; }
    bool getRefreshWindow() { return refreshWindow; }

private:
    void* hSpr;                        /* spreader handle */
    
    /* For syncing parameter values between the JUCE parameter tree and the internal DSP object */
    void setParameterValuesUsingInternalState();
    void setInternalStateUsingParameterValues();

    void timerCallback() override
    {
        /* reinitialise codec if needed */
        if(spreader_getCodecStatus(hSpr) == CODEC_STATUS_NOT_INITIALISED){
            try{
                std::thread threadInit(spreader_initCodec, hSpr);
                threadInit.detach();
            } catch (const std::exception& exception) {
                std::cout << "Could not create thread" << exception.what() << std::endl;
            }
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
