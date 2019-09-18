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

#include "JuceHeader.h"
#include "PluginProcessor.h"

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_frameSize,
    k_warning_supported_fs,
    k_warning_mismatch_fs,
    k_warning_osc_connection_fail,
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
                      private FilenameComponentListener,
                      public Button::Listener,
                      public ComboBox::Listener,
                      public Slider::Listener
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
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void* hAmbi;
    void timerCallback() override;
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;

    /* sofa loading */
    FilenameComponent fileChooser;

    /* sofa file loading */
    void filenameComponentChanged (FilenameComponent*) override  {
        String directory = fileChooser.getCurrentFile().getFullPathName();
        const char* new_cstring = (const char*)directory.toUTF8();
        ambi_bin_setSofaFilePath(hAmbi, new_cstring);
    }

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ToggleButton> TBuseDefaultHRIRs;
    std::unique_ptr<ComboBox> CBorderPreset;
    std::unique_ptr<ComboBox> CBchFormat;
    std::unique_ptr<ComboBox> CBnormScheme;
    std::unique_ptr<ToggleButton> TBmaxRE;
    std::unique_ptr<Slider> s_yaw;
    std::unique_ptr<Slider> s_pitch;
    std::unique_ptr<Slider> s_roll;
    std::unique_ptr<TextEditor> te_oscport;
    std::unique_ptr<Label> label_N_dirs;
    std::unique_ptr<Label> label_HRIR_len;
    std::unique_ptr<Label> label_HRIR_fs;
    std::unique_ptr<Label> label_DAW_fs;
    std::unique_ptr<ToggleButton> t_flipPitch;
    std::unique_ptr<ToggleButton> t_flipRoll;
    std::unique_ptr<ToggleButton> t_flipYaw;
    std::unique_ptr<ToggleButton> TBcompEQ;
    std::unique_ptr<ToggleButton> TBrpyFlag;
    std::unique_ptr<ToggleButton> TBenableRot;
    std::unique_ptr<ComboBox> CBdecoderMethod;
    std::unique_ptr<ToggleButton> TBdiffMatching;
    std::unique_ptr<ToggleButton> TBphaseWarping;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

