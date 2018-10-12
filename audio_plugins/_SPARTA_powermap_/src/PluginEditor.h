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

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "overlay.h"
#include "log2dSlider.h"

#ifndef M_PI
  #define M_PI (3.14159265359f)
#endif

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_frameSize,
    k_warning_NinputCH
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
                      public ComboBox::Listener,
                      public Slider::Listener
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
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    /* for openGL speed-ups */
    ScopedPointer<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;

    /* for the powermap overlay */
    Rectangle<int> previewArea;
    ScopedPointer<overlay> overlayIncluded;

    /* for freq-dependent analysis order + EQ */
    ScopedPointer<log2dSlider> anaOrder2dSlider;
    ScopedPointer<log2dSlider> pmapEQ2dSlider;

    bool resolutionHasChanged;
    
    /* warnings */
    SPARTA_WARNINGS currentWarning; 

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> CBpmap_method;
    ScopedPointer<ComboBox> CBsourcePreset;
    ScopedPointer<ComboBox> CBchFormat;
    ScopedPointer<ComboBox> CBnormScheme;
    ScopedPointer<Slider> s_anaOrder;
    ScopedPointer<Slider> s_pmapEQ;
    ScopedPointer<Slider> s_covAvg;
    ScopedPointer<Slider> s_Nsources;
    ScopedPointer<ComboBox> CB_hfov;
    ScopedPointer<ComboBox> CB_aspectRatio;
    ScopedPointer<Slider> s_pmapAvg;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
