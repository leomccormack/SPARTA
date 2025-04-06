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

#include "log2dSlider.h"

#ifndef MIN
#define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif


float round_float(float in, int nDecimalPoints)
{
    float out;
    int n = (int)pow(10, nDecimalPoints);
    out = in*(float)n;
    out = (out > (floor(out)+0.5f)) ? ceil(out) : floor(out);
    out = out/(float)n;
    return out;
}

log2dSlider::log2dSlider (int _width, int _height, float _min_X_value, float _max_X_value, float _min_Y_value, float _max_Y_value, int _nDecimalPoints)
{
    setSize (320, 50);

    setSize (_width, _height);
    localBounds = getBounds();

    width = _width;
    height =_height;
    min_X_value = _min_X_value;
    max_X_value = _max_X_value;
    min_Y_value = _min_Y_value;
    max_Y_value = _max_Y_value;
    nDecimalPoints = _nDecimalPoints;

    X_vector = NULL;
    Y_values = NULL;
    Y_values_int = NULL;
    refreshValues = true;
}

log2dSlider::~log2dSlider()
{
}

void log2dSlider::paint (Graphics& g)
{
    /* background */
    int x = 0, y = 0;
    Colour fillColour1 = Colour (0x11ffffff), fillColour2 = Colour (0x425b5b5b);
    Colour strokeColour = Colour (0xe1999999);
    g.setGradientFill (ColourGradient (fillColour1,
                                       0.0f,
                                       0.0f,
                                       fillColour2,
                                       0.0f,
                                       (float)height,
                                       false));
    g.fillRect (x, y, width, height);
    g.setColour (strokeColour);
    g.drawRect (x, y, width, height, 1);


    /* draw logarithmic X-axis guide lines */
    g.setColour(Colours::white);
    g.setOpacity(0.15f);
    float xlog;
    float c = log10f(min_X_value);
    float m = (log10f(max_X_value) - c)/(float)localBounds.getWidth();
    bool done = false;
    xlog = min_X_value;
    while(!done){
        float Xpixel = (log10f(xlog) - c)/m;
        g.drawLine(Xpixel, 0.0f, Xpixel, (float)localBounds.getHeight(), 1.0f);
        if (xlog <= max_X_value){
            if(xlog<10.0f){ xlog+=1.0f; } else if(xlog<1e2){ xlog+=10.0f; } else if (xlog<1e3f){ xlog+=100.0f; }
            else if (xlog<1e4f){ xlog+=1000.0f; } else if (xlog<1e5f){ xlog+=10000.0f; }
        }
        else
            done = true;
    }

    /* draw Y-axis guide lines */
    g.setColour(Colours::white);
    g.setOpacity(0.03f);
    g.drawLine(0.0f, (float)height/2.0f, (float)width, (float)height/2.0f, 1.0f);
    g.drawLine(0.0f, (float)height/4.0f, (float)width, (float)height/4.0f, 1.0f);
    g.drawLine(0.0f, 3.0f*(float)height/4.0f, (float)width,  3.0f*(float)height/4.0f, 1.0f);

    /* draw data */

    if( (X_vector!=NULL) && (useIntValues ? (Y_values_int!=NULL) : (Y_values!=NULL)) ){
        float y_range = max_Y_value - min_Y_value;
        for(int xIdx = 0; xIdx<num_X_points-1; xIdx++){
            float Xpixel_1 = MAX(0,(log10f(X_vector[xIdx]+2.23e-13f) - c)/m);
            float Xpixel_2 = MAX(0,(log10f(X_vector[xIdx+1]+2.23e-13f) - c)/m)+1.0f;
            float Yval;
            if(useIntValues)
                Yval = (float)Y_values_int[xIdx]-min_Y_value;
            else
                Yval = Y_values[xIdx]-min_Y_value;
            Yval = round_float(Yval, nDecimalPoints);
            float Ylength;
            if(max_Y_value==min_Y_value)
                Ylength = height/2.0f;
            else
                Ylength = (Yval/y_range)*(float)height;

            g.setColour(Colours::deepskyblue);
            g.setOpacity(0.2f);
            g.fillRect(Xpixel_1, (float)height- Ylength, Xpixel_2-Xpixel_1, Ylength);
            g.setColour(Colours::white);
            g.setOpacity(0.3f);
            g.drawRect(Xpixel_1, (float)height- Ylength, Xpixel_2-Xpixel_1, Ylength ,1.0f);
        }
    }

    //refreshValues = false;
}

void log2dSlider::resized()
{
}

void log2dSlider::mouseDown (const MouseEvent& e)
{
    float c = log10f(min_X_value);
    float m = (log10f(max_X_value) - c)/(float)localBounds.getWidth();
    bool shouldContinue = true;

    if( (X_vector!=NULL) && (useIntValues ? (Y_values_int!=NULL) : (Y_values!=NULL)) ){
        float y_range = max_Y_value - min_Y_value;
        for(int xIdx = 0; (xIdx<num_X_points-1) && shouldContinue; xIdx++){
            float Xpixel_1 = MAX(0,(log10f(X_vector[xIdx]+2.23e-13f) - c)/m);
            float Xpixel_2 = MAX(0,(log10f(X_vector[xIdx+1]+2.23e-13f) - c)/m);
            float Yval = 1.0f-(float)e.getPosition().y/(float)height;
            /* if down click is between two X-axis indices */
            if((e.getPosition().x>Xpixel_1) && (e.getPosition().x<=Xpixel_2)){
                Yval = round_float(Yval*y_range, nDecimalPoints);
                if(useIntValues)
                    Y_values_int[xIdx] = (int)((Yval+min_Y_value)+0.5f);
                else
                    Y_values[xIdx] = Yval+min_Y_value;
                refreshValues = true;
                shouldContinue = false;
            }
        }
    }
}

void log2dSlider::mouseDrag (const MouseEvent& e)
{
    float c = log10f(min_X_value);
    float m = (log10f(max_X_value) - c)/(float)localBounds.getWidth();
    bool shouldContinue = true;

    if( (X_vector!=NULL) && (useIntValues ? (Y_values_int!=NULL) : (Y_values!=NULL)) ){
        float y_range = max_Y_value - min_Y_value;
        for(int xIdx = 0; (xIdx<num_X_points-1) && shouldContinue; xIdx++){
            float Xpixel_1 = MAX(0,(log10f(X_vector[xIdx]+2.23e-13f) - c)/m)-6.0f;
            float Xpixel_2 = MAX(0,(log10f(X_vector[xIdx+1]+2.23e-13f) - c)/m)+6.0f;
            float Yval = 1.0f-(float)e.getPosition().y/(float)height;
            /* if down click is between two X-axis indices */
            if((e.getPosition().x>=Xpixel_1) && (e.getPosition().x<=Xpixel_2)){
                Yval = round_float(Yval*y_range, nDecimalPoints);
                if(useIntValues)
                    Y_values_int[xIdx] = (int)((Yval+min_Y_value)+0.5f);
                else
                    Y_values[xIdx] = Yval+min_Y_value;
                refreshValues = true;
            }
        }
    }
}
