/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2019 - Leo McCormack.
 
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

#include "PluginProcessor.h"
#include "dirass.h"

#ifndef MIN
#define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif

class overlay  : public Component
{
public:
    overlay (PluginProcessor& p);
    ~overlay();

    void refreshPowerMap(float* _dirs_deg, float* _pmap, int _nDirs, int _pmapWidth, int _hfov, float _aspectRatio );
    bool getFinishedRefresh(){ return finishedRefresh; }
    void setEnableTransparency(bool newState){ enableTransparency = newState; }

    void paint (Graphics& g) override;
    void resized() override;

private:
    float* dirs_deg, *pmap;
    int nDirs, pmapWidth, hfov;
    float aspectRatio;
    Rectangle<int> localBounds;
    bool finishedRefresh;
    bool enableTransparency;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (overlay)
};
