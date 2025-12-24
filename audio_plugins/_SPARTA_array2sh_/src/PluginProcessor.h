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

#include <JuceHeader.h>
#include "../../resources/PluginProcessorBase.h"
#include "array2sh.h"
#include <thread>
#include <atomic>
#define CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS 1
#include "../../resources/ConfigurationHelper.h"
#define BUILD_VER_SUFFIX ""   /* String to be added before the version name on the GUI (e.g. beta, alpha etc..) */ 
#ifndef M_PI
# define M_PI ( 3.14159265358979323846264338327950288f )
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
    void* getFXHandle() { return hA2sh; }
    bool getBusHasLFE() { return inputBusHasLFE; }

    /* JSON */
    void saveConfigurationToFile (File destination);
    void loadConfiguration (const File& presetFile);
    void setLastDir(File newLastDir){ lastDir = newLastDir; }
    File getLastDir() {return lastDir;}
    
private:
    void* hA2sh;                        /* array2sh handle */
    File lastDir;
    ValueTree sensors {"Sensors"};
    std::atomic<bool> inputBusHasLFE = false;

    /* For syncing parameter values between the JUCE parameter tree and the internal DSP object */
    void setParameterValuesUsingInternalState();
    void setInternalStateUsingParameterValues();
    
    void timerCallback() override
    {
        /* reinitialise codec if needed */
        if(array2sh_getRequestEncoderEvalFLAG(hA2sh)){
            try{
                std::thread threadInit(array2sh_evalEncoder, hA2sh);
                //needScreenRefreshFLAG = 1;
                array2sh_setRequestEncoderEvalFLAG(hA2sh, 0);
                threadInit.detach();
            } catch (const std::exception& exception) {
                std::cout << "Could not create thread" << exception.what() << std::endl;
            }
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
