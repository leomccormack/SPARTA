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

#include "colourGradient.h"
#include "PluginProcessor.h"
#define NEAREST(number, multiple) (((number) + ((multiple) / 2)) / (multiple) * (multiple))
#define ROUND_DOWN(N,S) ((N / S) * S)

class TFview  : public Component
{
public:
    TFview (PluginProcessor* ownerFilter, int _width, int _height, float _min_freq, float _max_freq, float _min_dB, float _max_dB);
    ~TFview() override;

    void setFreqVector(float* _freqVector, int _numFreqPoints)
    {
        freqVector = _freqVector;
        numFreqPoints = _numFreqPoints;
    }

    void paint (Graphics& g) override;
    void resized() override;

private:
    PluginProcessor* hVst;
    void* hAmbi;
	Rectangle<float> TFtiles[AMBI_DRC_NUM_BANDS][AMBI_DRC_NUM_DISPLAY_TIME_SLOTS];
    int numFreqPoints, width, height, min_freq, max_freq, min_dB, max_dB;
    float* freqVector;

    Rectangle<int> localBounds;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TFview)
};
