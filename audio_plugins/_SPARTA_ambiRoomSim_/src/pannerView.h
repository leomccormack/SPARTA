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

#define TOP_VIEW ( 0 )
#define SIDE_VIEW ( 1 )
#define NUM_VIEW_POINTS ( 2 )

class pannerView  : public Component
{
public:
    pannerView (PluginProcessor* ownerFilter, int _width, int _height);
    ~pannerView() override;

    void refreshPanView();
    bool getSourceIconIsClicked(){
        return sourceIconIsClicked;
    }
    bool getReceiverIconIsClicked(){
        return receiverIconIsClicked;
    }

    void paint (juce::Graphics& g) override;
    void resized() override;
    void mouseDown (const juce::MouseEvent& e) override;
    void mouseDrag (const juce::MouseEvent& e) override;
    void mouseUp (const juce::MouseEvent& e) override;

private:
    PluginProcessor* hVst;
    void* hAmbi;
    int width;
    int height;
    Rectangle<float> SourceIcons[NUM_VIEW_POINTS][ROOM_SIM_MAX_NUM_SOURCES];
    Rectangle<float> ReceiverIcons[NUM_VIEW_POINTS][ROOM_SIM_MAX_NUM_RECEIVERS];
    bool sourceIconIsClicked;
    bool receiverIconIsClicked;
    int indexOfClickedIcon;
    int topOrSideView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (pannerView)
};
