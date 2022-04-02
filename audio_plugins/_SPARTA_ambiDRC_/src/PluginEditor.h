/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "PluginProcessor.h"
#include "TFview.h"
#include "colourGradient.h"
#include "../../resources/SPARTALookAndFeel.h"

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_frameSize,
    k_warning_supported_fs,
    k_warning_NinputCH,
    k_warning_NoutputCH
}SPARTA_WARNINGS;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor  : public AudioProcessorEditor,
                      public Timer,
                      public juce::Slider::Listener,
                      public juce::ComboBox::Listener
{
public:
    //==============================================================================
    PluginEditor (PluginProcessor* ownerFilter);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void* hAmbi;
    void timerCallback() override;
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
#endif
    std::unique_ptr<TFview> TFviewIncluded;

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */ 

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Slider> s_ratio;
    std::unique_ptr<juce::Slider> s_knee;
    std::unique_ptr<juce::Slider> s_attack;
    std::unique_ptr<juce::Slider> s_release;
    std::unique_ptr<juce::Slider> s_outgain;
    std::unique_ptr<juce::ComboBox> presetCB;
    std::unique_ptr<juce::ComboBox> CHOrderingCB;
    std::unique_ptr<juce::ComboBox> normalisationCB;
    std::unique_ptr<juce::Slider> s_ingain;
    std::unique_ptr<juce::Slider> s_thresh;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

