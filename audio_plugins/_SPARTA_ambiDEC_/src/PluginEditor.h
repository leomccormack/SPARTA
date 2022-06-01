/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "outputCoordsView.h"
#include "log2dSlider.h"
#include "../../resources/SPARTALookAndFeel.h"
#include <thread>

typedef enum _SPARTA_WARNINGS{
    k_warning_none,
    k_warning_frameSize,
    k_warning_supported_fs,
    k_warning_mismatch_fs,
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
    void* hAmbi;
    void timerCallback(int timerID) override;
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
#endif
    double progress = 0.0;
    ProgressBar progressbar;

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* freq-dependent decoding order */
    std::unique_ptr<log2dSlider> decOrder2dSlider;

    /* source coordinates viewport */
    std::unique_ptr<Viewport> outputCoordsVP;
    outputCoordsView* outputCoordsView_handle;
    FilenameComponent fileChooser;

    /* json file loading/saving */
    std::unique_ptr<juce::FileChooser> chooser;

    /* sofa file loading */
    void filenameComponentChanged (FilenameComponent*) override  {
        String directory = fileChooser.getCurrentFile().getFullPathName();
        const char* new_cstring = (const char*)directory.toUTF8();
        ambi_dec_setSofaFilePath(hAmbi, new_cstring);
    }

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    std::unique_ptr<juce::ComboBox> pluginDescription; /* Dummy combo box to provide plugin description tooltip */

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ComboBox> CBoutputDirsPreset;
    std::unique_ptr<juce::Slider> SL_num_loudspeakers;
    std::unique_ptr<juce::ToggleButton> TBuseDefaultHRIRs;
    std::unique_ptr<juce::ComboBox> CBsourcePreset;
    std::unique_ptr<juce::ComboBox> CBchFormat;
    std::unique_ptr<juce::ComboBox> CBnormScheme;
    std::unique_ptr<juce::Slider> SL_transitionFreq;
    std::unique_ptr<juce::ComboBox> CBdec1method;
    std::unique_ptr<juce::ComboBox> CBdec2method;
    std::unique_ptr<juce::ToggleButton> TBdec1EnableMaxrE;
    std::unique_ptr<juce::ToggleButton> TBdec2EnableMaxrE;
    std::unique_ptr<juce::ComboBox> CBdec1normtype;
    std::unique_ptr<juce::ToggleButton> TBBinauraliseLS;
    std::unique_ptr<juce::ComboBox> CBdec2normtype;
    std::unique_ptr<juce::Slider> s_decOrder;
    std::unique_ptr<juce::TextButton> tb_loadJSON;
    std::unique_ptr<juce::TextButton> tb_saveJSON;
    std::unique_ptr<juce::ComboBox> CBmasterOrder;
    std::unique_ptr<juce::ToggleButton> TBenablePreProc;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

