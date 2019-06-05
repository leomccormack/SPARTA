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
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class log2dSlider  : public Component
{
public:
    //==============================================================================
    log2dSlider (int _width, int _height, float _min_X_value, float _max_X_value, float _min_Y_value, float _max_Y_value, int _nDecimalPoints);
    ~log2dSlider();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
   
    void setDataHandles(float* _X_vector, float* _Y_values, int nPoints){
        X_vector = _X_vector;
        Y_values = _Y_values;
        num_X_points = nPoints;
        useIntValues = false;
    }
    void setDataHandlesInt(float* _X_vector, int* _Y_values, int nPoints){
        X_vector = _X_vector;
        Y_values_int = _Y_values;
        num_X_points = nPoints;
        useIntValues = true;
    }
    
    bool getRefreshValuesFLAG(){ return refreshValues; }
    void setRefreshValuesFLAG(bool newFlag){ refreshValues = newFlag; }
    
    void setYrange(int _min_Y_value, int _max_Y_value){
        min_Y_value = _min_Y_value;
        max_Y_value = _max_Y_value;
    }

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Rectangle<int> localBounds;
    int width, height;
    float min_X_value, max_X_value, min_Y_value, max_Y_value;
    int nDecimalPoints;
    bool refreshValues;
    bool useIntValues;
    int* Y_values_int;
    float* Y_values;
    float* X_vector;
    int num_X_points;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (log2dSlider)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
