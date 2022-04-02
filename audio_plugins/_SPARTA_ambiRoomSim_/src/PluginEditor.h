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
#include "outputCoordsView.h"
#include "pannerView.h"
#include "../../resources/SPARTALookAndFeel.h"

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
                      public juce::Slider::Listener,
                      public juce::ComboBox::Listener,
                      public juce::Button::Listener
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
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void* hAmbi;
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;
#endif

    /* Look and Feel */
    SPARTALookAndFeel LAF;

    /* source coordinates viewport */
    std::unique_ptr<Viewport> sourceCoordsVP;
    inputCoordsView* sourceCoordsView_handle;

    /* receiver coordinates viewport */
    std::unique_ptr<Viewport> receiverCoordsVP;
    outputCoordsView* receiverCoordsView_handle;

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
    std::unique_ptr<juce::Slider> SL_num_sources;
    std::unique_ptr<juce::ComboBox> CBoutputFormat;
    std::unique_ptr<juce::ComboBox> CBnormalisation;
    std::unique_ptr<juce::ComboBox> CBorder;
    std::unique_ptr<juce::Slider> SL_num_receivers;
    std::unique_ptr<juce::Slider> SL_max_reflection_order;
    std::unique_ptr<juce::Slider> s_attenCoeff_pX;
    std::unique_ptr<juce::Slider> s_attenCoeff_nX;
    std::unique_ptr<juce::Slider> s_attenCoeff_nY;
    std::unique_ptr<juce::Slider> s_attenCoeff_nZ;
    std::unique_ptr<juce::Slider> s_attenCoeff_pZ;
    std::unique_ptr<juce::Slider> s_attenCoeff_pY;
    std::unique_ptr<juce::Slider> s_roomLenZ;
    std::unique_ptr<juce::Slider> s_roomLenY;
    std::unique_ptr<juce::Slider> s_roomLenX;
    std::unique_ptr<juce::ToggleButton> TB_enableIMS;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

