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
    inputCoordsView (PluginProcessor& p, int _maxNCH, int _currentNCH );
    ~inputCoordsView() override;

    void setNCH(int newNCH){
        newNCH = newNCH > MAX_NUM_CHANNELS ? MAX_NUM_CHANNELS : newNCH;
        if(newNCH!=currentNCH){
            currentNCH = newNCH;
            resized();
        }
    }

    /* Updates the coordinate fields with the current position of the
       sources. The position does not necessarily come from the parameter
       (a motion path drives it directly), so the fields are updated from
       the DSP state. The parameter is not touched (the fields would
       otherwise write the value back to it). */
    void refresh();

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;

private:
    PluginProcessor& processor;
    void* hAmbi;
    std::vector<std::unique_ptr<SliderWithAttachment>> xSliders;
    std::vector<std::unique_ptr<SliderWithAttachment>> ySliders;
    std::vector<std::unique_ptr<SliderWithAttachment>> zSliders;
    int maxNCH, currentNCH;
    bool sliderHasChanged;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (inputCoordsView)
};

