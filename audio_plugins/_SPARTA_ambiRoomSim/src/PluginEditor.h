/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "inputCoordsView.h"
#include "pannerView.h"

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_frameSize,
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
                      public juce::ComboBox::Listener,
                      public juce::Slider::Listener
{
public:
    //==============================================================================
    PluginEditor (PluginProcessor* ownerFilter);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback() override;

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void* hAmbi;
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;

    /* source coordinates viewport */
    //std::unique_ptr<Viewport> sourceCoordsVP;
    //inputCoordsView* sourceCoordsView_handle;

    /* panning window */
    //std::unique_ptr<pannerView> panWindow;
    bool refreshPanViewWindow;

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ComboBox> CBsourceDirsPreset;
    std::unique_ptr<juce::Slider> SL_num_sources;
    std::unique_ptr<juce::ComboBox> CBoutputFormat;
    std::unique_ptr<juce::ComboBox> CBnormalisation;
    std::unique_ptr<juce::ComboBox> CBorder;
    std::unique_ptr<juce::Slider> s_roomWidth;
    std::unique_ptr<juce::Slider> s_roomDepth;
    std::unique_ptr<juce::Slider> s_roomHeight;
    std::unique_ptr<juce::Slider> SL_num_sources2;
    std::unique_ptr<juce::Slider> SL_num_sources3;
    std::unique_ptr<juce::ComboBox> CBsourceDirsPreset2;
    std::unique_ptr<juce::Slider> test_x;
    std::unique_ptr<juce::Slider> test_y;
    std::unique_ptr<juce::Slider> test_z;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

