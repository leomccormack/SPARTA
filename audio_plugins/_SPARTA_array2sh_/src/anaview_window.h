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

#ifndef M_PI
#define M_PI ( 3.14159265358979323846264338327950288f )
#endif

class anaview_window  : public Component
{
public:
    anaview_window (int _width, int _height, float _min_freq, float _max_freq, float _min_Y, float _max_Y, float _yaxislineStepSize, float _fs);
    ~anaview_window() override;

    Rectangle<int> localBounds;

    void setSolidCurves_Handle(float* _freqVector, float* _solidCurves, int _numFreqPoints, int _numCurves)
    {
        freqVector = _freqVector;
        solidCurves = _solidCurves;
        numCurves =_numCurves;
        numFreqPoints = _numFreqPoints;
    }
    void setNumCurves(int _numCurves){
        numCurves = _numCurves;
    }

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    int width, height;
    float min_freq, max_freq, min_Y, max_Y, fs;
    float yaxislineStepSize;

    float* freqVector;
    float* solidCurves;
    int numCurves;
    int numFreqPoints;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (anaview_window)
};
