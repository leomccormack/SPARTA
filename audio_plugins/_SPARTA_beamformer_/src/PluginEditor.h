/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.0.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"

#include "overlay.h"

#define OVERLAY_HEIGHT 400
#ifndef M_PI
  #define M_PI (3.14159265359f)
#endif
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
                      private CameraDevice::Listener,
                      public AsyncUpdater,
                      public ComboBoxListener,
                      public ButtonListener,
                      public SliderListener
{
public:
    //==============================================================================
    PluginEditor (PluginProcessor* ownerFilter);
    ~PluginEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    PluginProcessor* hVst;
    void timerCallback() override;

    /* CAMERA */
    void updateCameraList();
    void imageReceived(const Image& image) override;
    Rectangle<int> previewArea;

    /* OVERLAY */
    ScopedPointer<overlay> overlayIncluded;
    void handleAsyncUpdate() override;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ScopedPointer<CameraDevice> cameraDevice;
	ScopedPointer<Component> cameraPreviewComp;
	Image incomingImage;
	ImageComponent lastSnapshot;
    bool bMirrorImageLR;
    bool bMirrorImageUD;


    ScopedPointer<OpenGLGraphicsContextCustomShader> shader;

	OpenGLContext openGLContext; 
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> BFmodeCB;
    ScopedPointer<ComboBox> cameraCB;
    ScopedPointer<ComboBox> aspectRatioCB;
    ScopedPointer<ComboBox> fovCB;
    ScopedPointer<ToggleButton> mirrorLR_TB;
    ScopedPointer<ToggleButton> mirrorUD_TB;
    ScopedPointer<Slider> azi_SL;
    ScopedPointer<Slider> elev_SL;
    ScopedPointer<ToggleButton> auto_TB;
    ScopedPointer<ToggleButton> bin_TB;
    ScopedPointer<ComboBox> PFmodeCB;
    ScopedPointer<Slider> lambda_SL;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
