/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2018 - Leo McCormack.
 
 SPARTA is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 SPARTA is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with SPARTA.  If not, see <http://www.gnu.org/licenses/>.
 
 ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

class inputCoordsView  : public Component,
                         public juce::Slider::Listener
{
public:
    inputCoordsView (PluginProcessor* ownerFilter, int _maxNCH, int _currentNCH );
    ~inputCoordsView() override;

    void setNCH(int newNCH){
        newNCH = newNCH > MAX_NUM_CHANNELS ? MAX_NUM_CHANNELS : newNCH;
        refreshCoords();
        if(newNCH!=currentNCH){
            currentNCH = newNCH;
            resized();
            sliderHasChanged = true;
        }
    }

    bool getHasASliderChanged(){
        return sliderHasChanged;
    }

    void setHasASliderChange(bool newState){
        sliderHasChanged = newState;
    }

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;

private:
    PluginProcessor* hVst;
    void* hAmbi;
    void refreshCoords();
    std::unique_ptr<Slider>* aziSliders;
    std::unique_ptr<Slider>* elevSliders;
    int maxNCH, currentNCH;
    bool sliderHasChanged;

    std::unique_ptr<juce::Slider> dummySlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (inputCoordsView)
};
