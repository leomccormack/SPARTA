/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "inputCoordsView.h"
#include "pannerView.h"

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
                      public ComboBox::Listener,
                      public Slider::Listener,
                      public Button::Listener
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
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ScopedPointer<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;

    /* source coordinates viewport */
    ScopedPointer<Viewport> sourceCoordsVP;
    inputCoordsView* sourceCoordsView_handle;

    FilenameComponent fileChooser;

    /* sofa file loading */
    void filenameComponentChanged (FilenameComponent*) override  {
        String directory = fileChooser.getCurrentFile().getFullPathName();
        const char* new_cstring = (const char*)directory.toUTF8();
        binauraliser_setSofaFilePath(hVst->hBin, new_cstring);
    }

    /* panning window */
    ScopedPointer<pannerView> panWindow;
    bool refreshPanViewWindow;

    bool showingFrameSizeWarning;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ComboBox> CBsourceDirsPreset;
    std::unique_ptr<Slider> SL_num_sources;
    std::unique_ptr<Label> label_N_dirs;
    std::unique_ptr<Label> label_HRIR_len;
    std::unique_ptr<Label> label_HRIR_fs;
    std::unique_ptr<ToggleButton> TBuseDefaultHRIRs;
    std::unique_ptr<Label> label_DAW_fs;
    std::unique_ptr<ToggleButton> TB_showInputs;
    std::unique_ptr<ToggleButton> TB_showOutputs;
    std::unique_ptr<Label> label_N_Tri;
    std::unique_ptr<ComboBox> CBinterpMode;
    std::unique_ptr<TextButton> tb_loadJSON;
    std::unique_ptr<TextButton> tb_saveJSON;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
