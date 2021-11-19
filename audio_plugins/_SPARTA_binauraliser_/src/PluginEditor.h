/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

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
#include "../../resources/SPARTALookAndFeel.h"

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_frameSize,
    k_warning_supported_fs,
    k_warning_mismatch_fs,
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
                      public MultiTimer,
                      private FilenameComponentListener,
                      public juce::ComboBox::Listener,
                      public juce::Slider::Listener,
                      public juce::Button::Listener
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
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void* hBin;
    void timerCallback(int timerID) override;
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
    double progress = 0.0;
    ProgressBar progressbar;

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* source coordinates viewport */
    std::unique_ptr<Viewport> sourceCoordsVP;
    inputCoordsView* sourceCoordsView_handle;
    FilenameComponent fileChooser;

    /* json file loading/saving */
    std::unique_ptr<juce::FileChooser> chooser;

    /* sofa file loading */
    void filenameComponentChanged (FilenameComponent*) override  {
        String directory = fileChooser.getCurrentFile().getFullPathName();
        const char* new_cstring = (const char*)directory.toUTF8();
        binauraliser_setSofaFilePath(hBin, new_cstring);
        refreshPanViewWindow = true;
    }

    /* panning window */
    std::unique_ptr<pannerView> panWindow;
    bool refreshPanViewWindow;

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ComboBox> CBsourceDirsPreset;
    std::unique_ptr<juce::Slider> SL_num_sources;
    std::unique_ptr<juce::Label> label_N_dirs;
    std::unique_ptr<juce::Label> label_HRIR_fs;
    std::unique_ptr<juce::ToggleButton> TBuseDefaultHRIRs;
    std::unique_ptr<juce::Label> label_DAW_fs;
    std::unique_ptr<juce::ToggleButton> TB_showInputs;
    std::unique_ptr<juce::ToggleButton> TB_showOutputs;
    std::unique_ptr<juce::Label> label_N_Tri;
    std::unique_ptr<juce::ComboBox> CBinterpMode;
    std::unique_ptr<juce::TextButton> tb_loadJSON;
    std::unique_ptr<juce::TextButton> tb_saveJSON;
    std::unique_ptr<juce::Slider> s_yaw;
    std::unique_ptr<juce::Slider> s_pitch;
    std::unique_ptr<juce::Slider> s_roll;
    std::unique_ptr<juce::ToggleButton> t_flipYaw;
    std::unique_ptr<juce::ToggleButton> t_flipPitch;
    std::unique_ptr<juce::ToggleButton> t_flipRoll;
    std::unique_ptr<juce::TextEditor> te_oscport;
    std::unique_ptr<juce::ToggleButton> TBrpyFlag;
    std::unique_ptr<juce::ToggleButton> TBenableRotation;
    std::unique_ptr<juce::ToggleButton> TBenablePreProc;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

