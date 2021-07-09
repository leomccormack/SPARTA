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

    void refreshPanView();
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
    PluginProcessor* hVst;
    void* hAmbi;
    int width;
    int height;
    Rectangle<float> SourceIcons[MAX_NUM_CHANNELS];
    int NSources;
    bool sourceIconIsClicked;
    int indexOfClickedSource;
    bool soloActive;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (pannerView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

