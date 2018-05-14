/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"
#include "anaview_window.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class anaview  : public Component
{
public:
    //==============================================================================
    anaview (int _width, int _height, float _min_freq, float _max_freq, float _min_Y, float _max_Y, String _ylabel, float _yaxislineStepSize, float _fs);
    ~anaview();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    Rectangle<int> localBounds;
    ScopedPointer<anaview_window> anaview_windowIncluded;

    void setSolidCurves_Handle(float* _freqVector, float* _solidCurves, int _numFreqPoints, int _numCurves){
        anaview_windowIncluded->setSolidCurves_Handle(_freqVector, _solidCurves, _numFreqPoints, _numCurves);
    }

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    int width, height;
    float min_freq, max_freq, min_Y, max_Y, fs;
    String ylabel;
    float yaxislineStepSize;

    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (anaview)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
