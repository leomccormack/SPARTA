/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.0

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
    PluginProcessor* hVst;
    void timerCallback() override;


    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ScopedPointer<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
    ScopedPointer<TFview> TFviewIncluded;
    bool showingFrameSizeWarning;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> s_thresh;
    ScopedPointer<Slider> s_ratio;
    ScopedPointer<Slider> s_knee;
    ScopedPointer<Slider> s_attack;
    ScopedPointer<Slider> s_release;
    ScopedPointer<Slider> s_outgain;
    ScopedPointer<Slider> s_ingain;
    ScopedPointer<ComboBox> presetCB;
    ScopedPointer<ComboBox> CHOrderingCB;
    ScopedPointer<ComboBox> normalisationCB;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
