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
class outputCoordsView  : public Component,
                          public Slider::Listener
{
public:
    //==============================================================================
    outputCoordsView (PluginProcessor* ownerFilter, int _maxNCH, int _currentNCH );
    ~outputCoordsView();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setNCH(int newNCH){
		newNCH = newNCH > MAX_NUM_OUTPUTS ? MAX_NUM_OUTPUTS : newNCH;
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

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginProcessor* hVst;
    void *hPan;
    void refreshCoords();
    std::unique_ptr<Slider>* aziSliders;
    std::unique_ptr<Slider>* elevSliders;
    int maxNCH, currentNCH;
    bool sliderHasChanged;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Slider> dummySlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (outputCoordsView)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

