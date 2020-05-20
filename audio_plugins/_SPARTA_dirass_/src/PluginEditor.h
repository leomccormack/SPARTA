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
#include "overlay.h"
#include <thread>

#ifndef M_PI
# define M_PI (3.14159265359f)
#endif

typedef enum _SPARTA_WARNINGS{
    k_warning_none, 
    k_warning_supported_fs,
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
                      public MultiTimer,
                      private CameraDevice::Listener,
                      public AsyncUpdater,
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
    void* hDir;
    void timerCallback(int timerID) override;
    double progress = 0.0;
    ProgressBar progressbar;

    /* for openGL speed-ups */
    std::unique_ptr<OpenGLGraphicsContextCustomShader> shader;
    OpenGLContext openGLContext;

    /* for the powermap overlay */
    Rectangle<int> previewArea;
    std::unique_ptr<overlay> overlayIncluded;
    bool resolutionHasChanged;

    /* for webcam support */
    void updateCameraList();
    void imageReceived(const Image& image) override;
    void handleAsyncUpdate() override;
    std::unique_ptr<CameraDevice> cameraDevice;
    ImageComponent lastSnapshot;
    Image incomingImage;
    void cameraChanged();
    void cameraDeviceOpenResult (CameraDevice* device, const String& error);

    /* warnings */
    SPARTA_WARNINGS currentWarning;

    /* tooltips */
    SharedResourcePointer<TooltipWindow> tipWindow;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ComboBox> CBbeamType;
    std::unique_ptr<ComboBox> CBchFormat;
    std::unique_ptr<ComboBox> CBnormScheme;
    std::unique_ptr<ComboBox> CB_hfov;
    std::unique_ptr<ComboBox> CB_aspectRatio;
    std::unique_ptr<Slider> SLmapAvg;
    std::unique_ptr<ComboBox> CBinputOrder;
    std::unique_ptr<Slider> s_minFreq;
    std::unique_ptr<Slider> s_maxFreq;
    std::unique_ptr<ComboBox> CBgridOption;
    std::unique_ptr<ComboBox> CBupscaleOrder;
    std::unique_ptr<ComboBox> CBdirassMode;
    std::unique_ptr<Slider> s_interpWidth;
    std::unique_ptr<ComboBox> CB_webcam;
    std::unique_ptr<ToggleButton> TB_greyScale;
    std::unique_ptr<ToggleButton> TB_flipUD;
    std::unique_ptr<ToggleButton> TB_flipLR;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

