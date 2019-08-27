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
#include "inputCoordsView.h"
#include "outputCoordsView.h"
#include "pannerView.h"

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


    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void* hPan;
    void timerCallback() override;
    ScopedPointer<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;

    /* source coordinates viewport */
    ScopedPointer<Viewport> sourceCoordsVP;
    inputCoordsView* sourceCoordsView_handle;

    /* loudspeaker coordinates viewport */
    ScopedPointer<Viewport> loudspeakerCoordsVP;
    outputCoordsView* loudspeakerCoordsView_handle;

    /* panning window */
    ScopedPointer<pannerView> panWindow;
    bool refreshPanViewWindow;

    /* warnings */
    SPARTA_WARNINGS currentWarning;
    
    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ComboBox> CBsourceDirsPreset;
    std::unique_ptr<Slider> SL_num_sources;
    std::unique_ptr<ToggleButton> TB_showInputs;
    std::unique_ptr<ToggleButton> TB_showOutputs;
    std::unique_ptr<Slider> SL_pValue;
    std::unique_ptr<ComboBox> CBsLoudspeakerDirsPreset;
    std::unique_ptr<Slider> SL_num_loudspeakers;
    std::unique_ptr<TextButton> tb_loadJSON_src;
    std::unique_ptr<TextButton> tb_saveJSON_src;
    std::unique_ptr<TextButton> tb_loadJSON_ls;
    std::unique_ptr<TextButton> tb_saveJSON_ls;
    std::unique_ptr<Slider> SL_spread;
    std::unique_ptr<Slider> s_yaw;
    std::unique_ptr<ToggleButton> t_flipYaw;
    std::unique_ptr<ToggleButton> t_flipPitch;
    std::unique_ptr<ToggleButton> t_flipRoll;
    std::unique_ptr<Slider> s_pitch;
    std::unique_ptr<Slider> s_roll;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

