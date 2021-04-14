/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

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
class inputCoordsView  : public Component,
                         public juce::Slider::Listener
{
public:
    //==============================================================================
    inputCoordsView (PluginProcessor* ownerFilter, int _maxNCH, int _currentNCH );
    ~inputCoordsView() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setNCH(int newNCH){
		newNCH = newNCH > MAX_NUM_INPUTS ? MAX_NUM_INPUTS : newNCH;
		refreshCoords();
		if (newNCH != currentNCH) {
			currentNCH = newNCH;
			resized();
			sliderHasChanged = true;
		}
    }
    bool getHasASliderChanged(){ return sliderHasChanged; }
    void setHasASliderChange(bool newState){ sliderHasChanged = newState; }

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void* hBin;
    void refreshCoords();
    std::unique_ptr<Slider>* aziSliders;
    std::unique_ptr<Slider>* elevSliders;
    std::unique_ptr<Slider>* distSliders;
    int maxNCH, currentNCH;
    bool sliderHasChanged;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Slider> dummySlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (inputCoordsView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

