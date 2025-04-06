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

class pannerView  : public Component
{
public:
    pannerView (PluginProcessor* ownerFilter, int _width, int _height);
    ~pannerView();

    void refreshPanView();
    void setShowInputs(bool state){ showInputs = state; }
    void setShowOutputs(bool state){ showOutputs = state; }
    bool getSourceIconIsClicked(){ return sourceIconIsClicked; }

    void paint (Graphics& g) override;
    void resized() override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;

private:
    PluginProcessor* hVst;
    void* hPan;
    int width;
    int height;
    bool showInputs;
    bool showOutputs;
    Rectangle<float> SourceIcons[MAX_NUM_INPUTS];
    Rectangle<float> LoudspeakerIcons[MAX_NUM_OUTPUTS];
    int NSources;
    int NLoudspeakers;
    bool sourceIconIsClicked;
    int indexOfClickedSource;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (pannerView)
};
