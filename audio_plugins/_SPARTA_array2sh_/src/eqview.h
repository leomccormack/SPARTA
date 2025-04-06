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
#include "eqview_window.h"

class eqview  : public Component
{
public:
    eqview (int _width, int _height, float _min_freq, float _max_freq, float _min_dB, float _max_dB, float _fs);
    ~eqview() override;

    Rectangle<int> localBounds;
    std::unique_ptr<eqview_window> eqview_windowIncluded;

    void setSolidCurves_Handle(float* _freqVector, float** _solidCurves, int _numFreqPoints, int _numCurves){
        eqview_windowIncluded->setSolidCurves_Handle(_freqVector, _solidCurves, _numFreqPoints, _numCurves);
    }
    void setFaintCurves_Handle(float* _freqVector, float** _faintCurves, int _numFreqPoints, int _numCurves){
        eqview_windowIncluded->setFaintCurves_Handle(_freqVector, _faintCurves, _numFreqPoints, _numCurves);
    }
    void setNumCurves(int _numCurves){
        eqview_windowIncluded->setNumCurves(_numCurves);
    }

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    int width, height;
    float min_freq, max_freq, min_dB, max_dB, fs;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (eqview)
};
