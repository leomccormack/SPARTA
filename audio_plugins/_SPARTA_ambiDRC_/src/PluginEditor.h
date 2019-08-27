/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "PluginProcessor.h"
#include "TFview.h"
#include "colourGradient.h"

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
                      public Slider::Listener,
                      public ComboBox::Listener
{
public:
    //==============================================================================
    PluginEditor (PluginProcessor* ownerFilter);
    ~PluginEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void* hAmbi;
    void timerCallback() override;
    ScopedPointer<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
    ScopedPointer<TFview> TFviewIncluded;

    /* warnings */
    SPARTA_WARNINGS currentWarning;
    
    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Slider> s_thresh;
    std::unique_ptr<Slider> s_ratio;
    std::unique_ptr<Slider> s_knee;
    std::unique_ptr<Slider> s_attack;
    std::unique_ptr<Slider> s_release;
    std::unique_ptr<Slider> s_outgain;
    std::unique_ptr<Slider> s_ingain;
    std::unique_ptr<ComboBox> presetCB;
    std::unique_ptr<ComboBox> CHOrderingCB;
    std::unique_ptr<ComboBox> normalisationCB;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

