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
#include "eqview.h"
#include "anaview.h"
#include "sensorCoordsView.h"

typedef enum {
    SHOW_EQ = 1,
    SHOW_SPATIAL_COH,
    SHOW_LEVEL_DIFF
}DISP_WINDOW;

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
    void* hA2sh;
    void timerCallback() override;
    ScopedPointer<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;

    ScopedPointer<Viewport> sensorCoordsVP;
    sensorCoordsView* sensorCoordsView_handle;
    ScopedPointer<eqview> eqviewIncluded;
    ScopedPointer<anaview> cohviewIncluded;
    ScopedPointer<anaview> ldiffviewIncluded;
    DISP_WINDOW dispID;

    bool needScreenRefreshFLAG;
    bool showDegreesInstead;

    /* warnings */
    SPARTA_WARNINGS currentWarning;
    
    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;
    
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ComboBox> presetCB;
    std::unique_ptr<ComboBox> arrayTypeCB;
    std::unique_ptr<Slider> QSlider;
    std::unique_ptr<Slider> rSlider;
    std::unique_ptr<Slider> RSlider;
    std::unique_ptr<Slider> cSlider;
    std::unique_ptr<ComboBox> weightTypeCB;
    std::unique_ptr<ComboBox> filterTypeCB;
    std::unique_ptr<Slider> regAmountSlider;
    std::unique_ptr<ComboBox> CHOrderingCB;
    std::unique_ptr<ComboBox> normalisationCB;
    std::unique_ptr<Slider> gainSlider;
    std::unique_ptr<ToggleButton> degRadTB;
    std::unique_ptr<TextButton> textButton;
    std::unique_ptr<ComboBox> dispWindow;
    std::unique_ptr<TextButton> tb_loadJSON;
    std::unique_ptr<TextButton> tb_saveJSON;
    std::unique_ptr<ComboBox> CBencodingOrder;
    std::unique_ptr<TextButton> applyDiffEQ;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

