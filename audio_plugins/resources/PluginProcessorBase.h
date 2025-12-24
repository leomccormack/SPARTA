/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2025 - Janani Fernandez.
 
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

#pragma once

#include "ParameterManager.h"

class PluginProcessorBase  : public juce::AudioProcessor,
                             public juce::VST2ClientExtensions,
                             public ParameterManager,
                             public juce::AudioProcessorValueTreeState::Listener
{
public:
    explicit PluginProcessorBase(const BusesProperties& buses, juce::AudioProcessorValueTreeState::ParameterLayout layout)
        : AudioProcessor(buses), ParameterManager(*this, std::move(layout)) {}
    ~PluginProcessorBase() override {};

    int getCurrentBlockSize() const { return nHostBlockSize.load(); }
    int getCurrentNumInputs() const { return nNumInputs.load(); }
    int getCurrentNumOutputs() const { return nNumOutputs.load(); }

    /* These standard JUCE functions can be optionally overriden in the derived class */
    void processBlockBypassed(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) override {
        juce::AudioProcessor::processBlockBypassed(buffer, midi);
    }
    bool hasEditor() const override                  { return true; }
    const juce::String getName() const override      { return JucePlugin_Name; }
    bool acceptsMidi() const override                { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const override               { return JucePlugin_ProducesMidiOutput; }
    double getTailLengthSeconds() const override     { return 0.0; }
    int getNumPrograms() override                    { return 1; }
    int getCurrentProgram() override                 { return 0; }
    void setCurrentProgram (int /*index*/) override  {}
    const juce::String getProgramName(int) override  { return {}; }
    void changeProgramName(int /*index*/, const juce::String& /*newName*/) override {}
    
    /* VST CanDo */
    pointer_sized_int handleVstManufacturerSpecific (int32, pointer_sized_int, void*, float) override {
        return 0;
    }
    pointer_sized_int handleVstPluginCanDo (int32, pointer_sized_int, void* ptr, float) override {
        auto text = static_cast<const char*>(ptr);
        if (strcmp(text, "wantsChannelCountNotifications") == 0)
            return 1;
        return 0;
    }
    VST2ClientExtensions* getVST2ClientExtensions() override { return this; }
    
protected:
    bool firstInit = true;
    std::atomic<int> nNumInputs {0};
    std::atomic<int> nNumOutputs {0};
    int nSampleRate = 0;
    std::atomic<int> nHostBlockSize {0};

    /* These functions must be implemented in the derived class */
    virtual void parameterChanged(const juce::String&, float) override = 0;
    virtual void prepareToPlay(double, int) override = 0;
    virtual void releaseResources() override = 0;
    virtual void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override = 0;
    virtual void getStateInformation(juce::MemoryBlock& destData) override = 0;
    virtual void setStateInformation(const void* data, int sizeInBytes) override = 0;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessorBase)
};
