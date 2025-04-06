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

class sensorCoordsView  : public Component,
                          public juce::Slider::Listener
{
public:
    //==============================================================================
    sensorCoordsView (PluginProcessor* ownerFilter, int _maxQ, int _currentQ, bool _useDegreesInstead);
    ~sensorCoordsView() override;

    //==============================================================================
    void setUseDegreesInstead(bool newState);
    void setQ(int newQ){
		newQ = newQ > MAX_NUM_CHANNELS ? MAX_NUM_CHANNELS : newQ;
        refreshCoords();
		if (newQ != currentQ) {
			currentQ = newQ;
			resized();
		}
    }

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;

private:
    PluginProcessor* hVst;
    void* hA2sh;
    void refreshCoords();

    std::unique_ptr<Slider>* aziSliders;
    std::unique_ptr<Slider>* elevSliders;

    int maxQ, currentQ;
    bool useDegreesInstead;

    //==============================================================================
    std::unique_ptr<juce::Slider> dummySlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (sensorCoordsView)
};

