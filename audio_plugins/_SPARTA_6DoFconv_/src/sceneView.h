/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.6

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include <assert.h>

#define TOP_VIEW ( 0 )
#define SIDE_VIEW ( 1 )
#define NUM_VIEW_POINTS ( 2 )

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class sceneView  : public Component
{
public:
    //==============================================================================
    sceneView (PluginProcessor* ownerFilter, int _width, int _height);
    ~sceneView() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    void computeRoomDims();

    void refreshSceneView();
    bool getTargetIconIsClicked(){
        return targetIconIsClicked;
    }

    void setViewMode(int newMode){
        assert(newMode == TOP_VIEW || newMode == SIDE_VIEW);
        topOrSideView = newMode;
    }
    int getViewMode(){
        return topOrSideView;
    }
    void setDrawDoAs(bool newState){
        drawDoAs = newState;
    }
    void setDrawIntersections(bool newState){
        drawIntersections = newState;
    }
    void setDrawTargets(bool newState){
        drawTargets = newState;
    }
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void mouseDown (const juce::MouseEvent& e) override;
    void mouseDrag (const juce::MouseEvent& e) override;
    void mouseUp (const juce::MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void* hTVCnv; 
    int width;
    int height;
    bool targetIconIsClicked;

    int topOrSideView;

    bool drawDoAs;
    bool drawIntersections;
    bool drawTargets;

    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (sceneView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

