/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "colourGradient.h"
#include "PluginProcessor.h"
#define NEAREST(number, multiple) (((number) + ((multiple) / 2)) / (multiple) * (multiple))
#define ROUND_DOWN(N,S) ((N / S) * S)

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TFview  : public Component
{
public:
    //==============================================================================
    TFview (PluginProcessor* ownerFilter, int _width, int _height, float _min_freq, float _max_freq, float _min_dB, float _max_dB);
    ~TFview() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    void setFreqVector(float* _freqVector, int _numFreqPoints)
    {
        freqVector = _freqVector;
        numFreqPoints = _numFreqPoints;
    }

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void* hAmbi;
	Rectangle<float> TFtiles[HYBRID_BANDS][NUM_DISPLAY_TIME_SLOTS];
    int numFreqPoints, width, height, min_freq, max_freq, min_dB, max_dB;
    float* freqVector;

    Rectangle<int> localBounds;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TFview)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

