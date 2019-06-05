/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"

#ifndef M_PI
#define M_PI ( 3.14159265358979323846264338327950288f )
#endif
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class eqview_window  : public Component
{
public:
    //==============================================================================
    eqview_window (int _width, int _height, float _min_freq, float _max_freq, float _min_dB, float _max_dB, float _fs);
    ~eqview_window();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    Rectangle<int> localBounds;


    void setSolidCurves_Handle(float* _freqVector, float** _solidCurves, int _numFreqPoints, int _numCurves)
    {
        freqVector = _freqVector;
        solidCurves = _solidCurves;
        numCurves =_numCurves;
        numFreqPoints = _numFreqPoints;
    }

    void setFaintCurves_Handle(float* _freqVector, float** _faintCurves, int _numFreqPoints, int _numCurves)
    {
        freqVector = _freqVector;
        faintCurves = _faintCurves;
        numCurves =_numCurves;
        numFreqPoints = _numFreqPoints;
    }

    void setNumCurves(int _numCurves){
        numCurves = _numCurves;
    }

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    int width, height;
    float min_freq, max_freq, min_dB, max_dB, fs;

    float* freqVector;
    float** solidCurves;
    float** faintCurves;
    int numCurves;
    int numFreqPoints;
 
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (eqview_window)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
