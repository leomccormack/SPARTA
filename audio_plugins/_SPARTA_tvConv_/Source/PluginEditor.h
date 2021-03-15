/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Sparta_tvconvAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Sparta_tvconvAudioProcessorEditor (Sparta_tvconvAudioProcessor&);
    ~Sparta_tvconvAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Sparta_tvconvAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Sparta_tvconvAudioProcessorEditor)
};
