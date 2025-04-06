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

#include "eqview_window.h"

const int mag_lines_interval = 10; /* dB per horizontal guide line */

static int round_nearest(int number, int multiple) {
    int result = number + multiple/2;
    result -= result % multiple;
    return result;
}

static void setCurveColour(Graphics& g, int n){
    switch(n){
        default: /* fall through */
        case 0: g.setColour(Colours::blue); break;
        case 1: g.setColour(Colours::red); break;
        case 2: g.setColour(Colours::yellow); break;
        case 3: g.setColour(Colours::purple); break;
        case 4: g.setColour(Colours::green); break;
        case 5: g.setColour(Colours::lightblue); break;
        case 6: g.setColour(Colours::darkred); break;
        case 7: g.setColour(Colours::darkblue); break;
        case 8: g.setColour(Colours::blue); break;
        case 9: g.setColour(Colours::red); break;
        case 10: g.setColour(Colours::yellow); break;
    }
}

//==============================================================================
eqview_window::eqview_window (int _width, int _height, float _min_freq, float _max_freq, float _min_dB, float _max_dB, float _fs)
{
    setSize (_width, _height);
    localBounds = getBounds();

    width = _width;
    height =_height;
    min_freq = _min_freq;
    max_freq = _max_freq;
    min_dB = _min_dB;
    max_dB = _max_dB;
    fs = _fs;

    freqVector = NULL;
    solidCurves = NULL;
    faintCurves = NULL;
}

eqview_window::~eqview_window()
{
}

//==============================================================================
void eqview_window::paint (Graphics& g)
{
    /* background */
    //Colour fillColour1 = Colour (0x75707070), fillColour2 = Colour (0xa1202020);
    Colour fillColour1 = Colour (0xff4e4e4e), fillColour2 = Colour (0xff202020);
    g.setGradientFill (ColourGradient (fillColour1, 0, 0,
                                       fillColour2, 0, localBounds.getHeight(),
                                       false));
    g.fillRect (localBounds);
    g.setColour(Colours::white);
    g.setOpacity(0.3f);
    g.drawRect (localBounds);

    /* draw frequency guide lines */
    g.setColour(Colours::white);
    g.setOpacity(0.22f);
    float freq;
    float c = log10f(min_freq);
    float m = (log10f(max_freq) - c)/(float)localBounds.getWidth();
    bool done = false;
    freq = min_freq;
    while(!done){
        float Xpixel = (log10f(freq) - c)/m;
        g.drawLine(Xpixel, 0.0f, Xpixel, localBounds.getHeight(), 1.0f);
        if (freq <= max_freq){
            if(freq<10.0f){ freq+=1.0f; } else if(freq<1e2){ freq+=10.0f; } else if (freq<1e3f){ freq+=100.0f; }
            else if (freq<1e4f){ freq+=1000.0f; } else if (freq<1e5f){ freq+=10000.0f; }
        }
        else{
            done = true;
        }
    }

    /* draw magnitude guide lines */
    g.setColour(Colours::white);
    g.setOpacity(0.08f);
    float start_dB = round_nearest(min_dB<0 ? min_dB-mag_lines_interval : min_dB, mag_lines_interval);
    float end_dB= round_nearest(max_dB, mag_lines_interval);
    for (int i = start_dB; i<=end_dB; i+=mag_lines_interval){
        float Ypixel = ((float)i-min_dB)* ((float)localBounds.getHeight()/(max_dB-min_dB));
        if ((i>min_dB-1) && (i< max_dB+1)){
            g.drawLine(0,localBounds.getHeight()-Ypixel, localBounds.getWidth(), localBounds.getHeight()-Ypixel,1.0f);
        }
    }

    /* plot faint magnitude curves (if defined) */
    if ( (freqVector != NULL) && (faintCurves != NULL) ){
        for(int crv=0; crv<numCurves; crv++){
            for(int f=0; f<numFreqPoints-1; f++){
                float Xpixel = (log10f(freqVector[f]) - c)/m;
                float Ypixel = (faintCurves[f][crv]-min_dB)* ((float)localBounds.getHeight()/(max_dB-min_dB));
                float Xpixel_next = (log10f(freqVector[f+1]) - c)/m;
                float Ypixel_next = (faintCurves[f+1][crv]-min_dB)* ((float)localBounds.getHeight()/(max_dB-min_dB));
                /* background line */
                g.setColour(Colours::white);
                g.setOpacity(0.1f);
                g.drawLine(Xpixel, localBounds.getHeight()-Ypixel, Xpixel_next, localBounds.getHeight()-Ypixel_next, 2.0f);
                /* main */
                setCurveColour(g, crv);
                g.setOpacity(0.3f);
                g.drawLine(Xpixel, localBounds.getHeight()-Ypixel, Xpixel_next, localBounds.getHeight()-Ypixel_next, 1.0f);
            }
        }
    }

    /* plot solid magnitude curves (if defined) */
    if ( (freqVector != NULL) && (solidCurves != NULL) ){
        for(int crv=0; crv<numCurves; crv++){
            for(int f=0; f<numFreqPoints-1; f++){
                float Xpixel = (log10f(freqVector[f]) - c)/m;
                float Ypixel = (solidCurves[f][crv]-min_dB)* ((float)localBounds.getHeight()/(max_dB-min_dB));
                float Xpixel_next = (log10f(freqVector[f+1]) - c)/m;
                float Ypixel_next = (solidCurves[f+1][crv]-min_dB)* ((float)localBounds.getHeight()/(max_dB-min_dB));
                /* background line */
                g.setColour(Colours::white);
                g.setOpacity(0.1f);
                g.drawLine(Xpixel, localBounds.getHeight()-Ypixel, Xpixel_next, localBounds.getHeight()-Ypixel_next, 5.0f);
                /* main */
                setCurveColour(g, crv);
                g.setOpacity(1.0f);
                g.drawLine(Xpixel, localBounds.getHeight()-Ypixel, Xpixel_next, localBounds.getHeight()-Ypixel_next, 2.0f);
            }
        }
    }

    /* Plot legend */
    float leg_x = 460;
    float leg_y = 82;
    g.setColour(Colours::grey);
    g.setOpacity(1.0f);
    g.drawRect(leg_x, leg_y, 38.0f, 10.0f*(float)numCurves, 1.0f);
    g.setOpacity(0.25f);
    g.fillRect(leg_x, leg_y, 38.0f, 10.0f*(float)numCurves);
    g.setOpacity(1.0f);
    g.setFont(9.0f);
    String suffix;
    for(int crv=0; crv<numCurves; crv++){
        g.setColour(Colours::white);
        if(crv==1)
            suffix = "st";
        else if(crv==2)
            suffix = "nd";
        else if(crv==3)
            suffix = "rd";
        else
            suffix = "th";
        g.drawText(String(crv)+suffix, leg_x+2.0f, leg_y+(float)crv*10.0f, 30.0f, 8.0f, Justification::centredLeft);
        setCurveColour(g, crv);
        g.drawLine(leg_x+18.0f, leg_y+(float)crv*10.0f+4.0f, leg_x+34.0f, leg_y+(float)crv*10.0f+4.0f, 2.0f);
    }
}

void eqview_window::resized()
{
}
