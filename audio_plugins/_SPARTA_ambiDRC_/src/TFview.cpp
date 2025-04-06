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

#include "TFview.h"

#ifndef MIN
#define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif

//==============================================================================
TFview::TFview (PluginProcessor* ownerFilter, int _width, int _height, float _min_freq, float _max_freq, float _min_dB, float _max_dB)
{
    setSize (470, 220);

    /* local pars */
	hVst = ownerFilter;
    hAmbi = hVst->getFXHandle();
    width = _width;
    height = _height;
    min_freq = _min_freq;
    max_freq = _max_freq;
    min_dB = _min_dB;
    max_dB = _max_dB;
    freqVector = NULL;

    /* component bounds */
    setSize(width, height);
    localBounds = getBounds();
}

TFview::~TFview()
{
}

//==============================================================================
void TFview::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    /* Background */
    int x = 0, y = 0;
    Colour fillColour2 = Colour (0xff4e4e4e), fillColour1 = Colour (0xff202020);
    //Colour fillColour1 = Colour (0xffcdf1ff), fillColour2 = Colour (0xff616161);
    Colour strokeColour = Colour (0x7dffffff);
    g.setGradientFill (ColourGradient (fillColour1,
                                       (float)width/2.0f + x,
                                       (float)width/2.0f + y,
                                       fillColour2,
                                       (float)width/2.0f + x,
                                       y,
                                       false));
    g.fillRect (x, y, width, height);
    g.setColour (strokeColour);
    g.drawRect (x, y, width, height, 1);

    if(freqVector!=NULL) {
        /* define TF tile bounds */
        float tileWidth = (float)(width) / (float)(AMBI_DRC_NUM_DISPLAY_TIME_SLOTS);
        float c = log10f(min_freq);
        float m = (log10f(max_freq) - c)/(float)height;
        for (int band = 0; band < AMBI_DRC_NUM_BANDS; band++) {
            float prev_Ypixel = band == 0 || band == 1 ? 0.0f : (log10f(freqVector[band-1]) - c)/m;
            float Ypixel = band == 0 ? 0.0f : (log10f(freqVector[band]) - c)/m;
            float tileHeight = Ypixel -prev_Ypixel;//SWAPPED!!!!
            for (int t = 0; t < AMBI_DRC_NUM_DISPLAY_TIME_SLOTS; t++) {
                TFtiles[band][t].setBounds((float)t*tileWidth,
                                           (float)height- Ypixel, //SWAPPED!!! prev_Ypixel,
                                           tileWidth,
                                           tileHeight);
            }
        }

        /* Fill in TF tiles */ //MIN_DISPLAY_DB
        float**gainTF = ambi_drc_getGainTF(hAmbi);
        int wIdx = ambi_drc_getGainTFwIdx(hAmbi);
        int rIdx;
        float logScale = (log10f(1.0f) - log10f(AMBI_DRC_SPECTRAL_FLOOR));
        g.setOpacity(1.0f);
        for (int band = 0; band < AMBI_DRC_NUM_BANDS; band++) {
            for (int t = 0; t < AMBI_DRC_READ_OFFSET; t++) {
                rIdx = 0>wIdx - AMBI_DRC_READ_OFFSET + t ? 0 : wIdx - AMBI_DRC_READ_OFFSET + t;
                float col_val = 1.0f - (log10f(gainTF[band][rIdx]) - log10f(AMBI_DRC_SPECTRAL_FLOOR))/logScale;
                int col_idx = MAX(MIN((int)(col_val*(float)(mapColourTable_N)), mapColourTable_N-1), 0);
                g.setColour(mapColourTable[col_idx]);
                g.fillRect(TFtiles[band][(int)(rIdx)]);
            }
        }
    }

	/* Draw wIdx line */
	g.setColour(Colours::black);
	g.setOpacity(1.0f);
	g.drawLine(0.0f, height, width, height, 2.0f);

    /* draw frequency guide lines on top */
    g.setColour(Colours::white);
    g.setOpacity(0.35f);
    float freq;
    float c = log10f(min_freq);
    float m = (log10f(max_freq) - c)/(float)height;
    bool done = false;
    freq = min_freq;
    while(!done){
        float Ypixel = (log10f(freq) - c)/m;
        g.drawLine(0.0f, height-Ypixel, width, height-Ypixel, 1.0f);
        if (freq <= max_freq){
            if(freq<10.0f){ freq+=1.0f; } else if(freq<1e2){ freq+=10.0f; } else if (freq<1e3f){ freq+=100.0f; }
            else if (freq<1e4f){ freq+=1000.0f; } else if (freq<1e5f){ freq+=10000.0f; }
        }
        else
            done = true;
    }

    /* draw time guide lines on top */
    g.setColour(Colours::white);
    g.setOpacity(0.17f);
    for(int i=0; i<AMBI_DRC_NUM_DISPLAY_SECONDS; i++){
        g.drawLine((float)i*(float)width/(float)AMBI_DRC_NUM_DISPLAY_SECONDS, 0.0f,
                   (float)i*(float)width/(float)AMBI_DRC_NUM_DISPLAY_SECONDS, (float)height, 1.0f);
    }

	/* Draw scroll line */
    int wIdx = ambi_drc_getGainTFwIdx(hAmbi);
	float linePos = (float)wIdx*(width / (float)AMBI_DRC_NUM_DISPLAY_TIME_SLOTS);
	g.setColour(Colours::white);
	g.setOpacity(1.0f);
	g.drawLine(linePos, 0, linePos, height, 1);
	g.setColour(Colour(0x7dffffff));
	g.drawRect(0, 0, width, height, 1);
}

void TFview::resized()
{
}

 
