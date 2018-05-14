/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.2.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "PluginProcessor.h"


#ifndef MIN
#define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif
#ifndef M_PI
#define M_PI ( 3.14159265359f )
#endif
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class overlay  : public Component
{
public:
    //==============================================================================
    overlay (PluginProcessor* ownerFilter);
    ~overlay();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    PluginProcessor* hVst;
    Rectangle<int> localBounds;

    bool hasFinishedDrawing;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (overlay)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
