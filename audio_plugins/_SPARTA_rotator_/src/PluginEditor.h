/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "PluginProcessor.h"

typedef enum _SPARTA_WARNINGS{
    k_warning_none, 
    k_warning_NinputCH,
    k_warning_NoutputCH,
    k_warning_osc_connection_fail
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
                      public Button::Listener,
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
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void* hRot;
    void timerCallback() override;

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Slider> s_yaw;
    std::unique_ptr<Slider> s_pitch;
    std::unique_ptr<Slider> s_roll;
    std::unique_ptr<ToggleButton> t_flipYaw;
    std::unique_ptr<ToggleButton> t_flipPitch;
    std::unique_ptr<ToggleButton> t_flipRoll;
    std::unique_ptr<TextEditor> te_oscport;
    std::unique_ptr<ComboBox> CBoutputFormat;
    std::unique_ptr<ComboBox> CBnorm;
    std::unique_ptr<ComboBox> CBorder;
    std::unique_ptr<ToggleButton> TBrpyFlag;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

