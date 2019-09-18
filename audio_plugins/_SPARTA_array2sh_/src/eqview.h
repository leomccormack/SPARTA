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
#include "eqview_window.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class eqview  : public Component
{
public:
    //==============================================================================
    eqview (int _width, int _height, float _min_freq, float _max_freq, float _min_dB, float _max_dB, float _fs);
    ~eqview();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    Rectangle<int> localBounds;
    std::unique_ptr<eqview_window> eqview_windowIncluded;

    void setSolidCurves_Handle(float* _freqVector, float** _solidCurves, int _numFreqPoints, int _numCurves){
        eqview_windowIncluded->setSolidCurves_Handle(_freqVector, _solidCurves, _numFreqPoints, _numCurves);
    }
    void setFaintCurves_Handle(float* _freqVector, float** _faintCurves, int _numFreqPoints, int _numCurves){
        eqview_windowIncluded->setFaintCurves_Handle(_freqVector, _faintCurves, _numFreqPoints, _numCurves);
    }
    void setNumCurves(int _numCurves){
        eqview_windowIncluded->setNumCurves(_numCurves);
    }

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    int width, height;
    float min_freq, max_freq, min_dB, max_dB, fs;


    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (eqview)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

