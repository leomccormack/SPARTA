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
#include "anaview_window.h"

class anaview  : public Component
{
public:
    //==============================================================================
    anaview (int _width, int _height, float _min_freq, float _max_freq, float _min_Y, float _max_Y, String _ylabel, float _yaxislineStepSize, float _fs);
    ~anaview();

    //==============================================================================
    Rectangle<int> localBounds;
    std::unique_ptr<anaview_window> anaview_windowIncluded;

    void setSolidCurves_Handle(float* _freqVector, float* _solidCurves, int _numFreqPoints, int _numCurves){
        anaview_windowIncluded->setSolidCurves_Handle(_freqVector, _solidCurves, _numFreqPoints, _numCurves);
    }
    void setNumCurves(int _numCurves){
        anaview_windowIncluded->setNumCurves(_numCurves);
    }

    void paint (Graphics& g) override;
    void resized() override;

private:
    int width, height;
    float min_freq, max_freq, min_Y, max_Y, fs;
    String ylabel;
    float yaxislineStepSize;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (anaview)
};
