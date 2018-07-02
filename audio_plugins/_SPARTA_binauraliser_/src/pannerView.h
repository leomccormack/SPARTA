/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "PluginProcessor.h"

#define MAX_NUM_OUT_DIRS 12000
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class pannerView  : public Component
{
public:
    //==============================================================================
    pannerView (PluginProcessor* ownerFilter, int _width, int _height);
    ~pannerView();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    PluginProcessor* hVst;

    void refreshPanView();

    void setShowInputs(bool state){
        showInputs = state;
    }
    void setShowOutputs(bool state){
        showOutputs = state;
    }

    bool getSourceIconIsClicked(){
        return sourceIconIsClicked;
    }

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    int width;
    int height;

    bool showInputs;
    bool showOutputs;
    Rectangle<float> SourceIcons[MAX_NUM_CHANNELS];
    Rectangle<float> LoudspeakerIcons[MAX_NUM_OUT_DIRS];
    int NSources;
    int NLoudspeakers;

    bool sourceIconIsClicked;
    int indexOfClickedSource;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (pannerView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
