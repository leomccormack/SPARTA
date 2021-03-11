/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "PluginProcessor.h"

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
class pannerView  : public Component
{
public:
    //==============================================================================
    pannerView (PluginProcessor* ownerFilter, int _width, int _height);
    ~pannerView() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    void refreshPanView();
    bool getSourceIconIsClicked(){
        return sourceIconIsClicked;
    }
    bool getReceiverIconIsClicked(){
        return receiverIconIsClicked;
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
    void* hAmbi;
    int width;
    int height;
    Rectangle<float> SourceIcons[NUM_VIEW_POINTS][ROOM_SIM_MAX_NUM_SOURCES];
    Rectangle<float> ReceiverIcons[NUM_VIEW_POINTS][ROOM_SIM_MAX_NUM_RECEIVERS];
    int NSources;
    int NReceivers;
    bool sourceIconIsClicked;
    bool receiverIconIsClicked;
    int indexOfClickedIcon;
    int topOrSideView;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (pannerView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

