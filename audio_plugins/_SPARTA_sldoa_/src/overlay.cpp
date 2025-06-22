/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2017/2018 - Leo McCormack.
 
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

#include "overlay.h"

static Colour getColour_val(float val)
{
    if (val >= 0.9f)
        return Colour::fromRGB(191, 40, 0);
    else if (val >= 0.8f)
        return Colour::fromRGB(195, 0, 12);
    else if (val >= 0.7f)
        return Colour::fromRGB(199, 198, 0);
    else if (val >= 0.6f)
        return Colour::fromRGB(125, 203, 0);
    else if (val >= 0.5f)
        return Colour::fromRGB(46, 207, 0);
    else if (val >= 0.4f)
        return Colour::fromRGB(0, 212, 35);
    else if (val >= 0.3f)
        return Colour::fromRGB(0, 216, 120);
    else if (val >= 0.2f)
        return Colour::fromRGB(0, 220, 209);
    else if (val >= 0.1f)
        return Colour::fromRGB(0, 148, 224);
    else
        return Colour::fromRGB(0, 62, 229);
}

overlay::overlay (PluginProcessor& p) : processor(p)
{
    setSize (600, 400);

    hSld = processor.getFXHandle();
    hasFinishedDrawing = true;
}

overlay::~overlay()
{
}

void overlay::paint (Graphics& g)
{
    if (hasFinishedDrawing) { /* in order to stop it from tripping over itself */
        hasFinishedDrawing = false;

        Rectangle<int> r(getLocalBounds());
        localBounds = r;
        float width = (float)localBounds.getWidth();
        float height = (float)localBounds.getHeight();
        float circ_dia = 12.0f;
        float growF = 2.2f; // grow factor
        float radius;

        /* fetch data handles */
        int maxNumSectors, startBand, endBand;
        int* nSectorsPerBand;
        float* hAzi_deg, *hElev_deg, *hScaleColour, *hScaleAlpha;
        sldoa_getDisplayData(hSld, &hAzi_deg, &hElev_deg, &hScaleColour, &hScaleAlpha, &nSectorsPerBand, &maxNumSectors, &startBand, &endBand);

        /* Draw the DoAs */
        for(int band=MAX(startBand,1); band<endBand; band++){ /* ignore DC */
            for(int sec=0; sec<nSectorsPerBand[band]; sec++){
                float x_pixel, y_pixel;
                radius = (growF*hScaleAlpha[band*maxNumSectors + sec]*circ_dia)/2.0f;
                x_pixel = width  - ((hAzi_deg[band*maxNumSectors  + sec] + 180.0f)/360.0f) * width  - radius;
                y_pixel = height - ((hElev_deg[band*maxNumSectors + sec] + 90.0f) /180.0f) * height - radius;
                float val = hScaleColour[band*maxNumSectors + sec];
                float expfactor = 10.0f;
                Colour colour1 = getColour_val(powf(expfactor, val)/expfactor- 1.0f/expfactor*(1.0f-val));
                Colour colour2 = Colour::fromFloatRGBA(1.0f, 1.0f, 1.0f, 0.2f);
                g.setGradientFill (ColourGradient (colour1,
                                                   x_pixel+radius,
                                                   y_pixel+radius,
                                                   colour2,
                                                   x_pixel+radius/4.0f,
                                                   y_pixel+radius/4.0f,
                                                   true));
                g.fillEllipse(x_pixel,
                              y_pixel,
                              2.0f*radius,
                              2.0f*radius);
                g.setColour(Colours::lightgrey);
                g.setOpacity(hScaleAlpha[band*maxNumSectors + sec]/20.0f);
                g.fillEllipse(x_pixel,
                              y_pixel,
                              2.0f*radius,
                              2.0f*radius);
            }
        }

		/* DRAW THE GRID ON TOP */
		int numGridLinesX = 8;
		int numGridLinesY = numGridLinesX / 2;
		g.setColour(Colours::white);
		g.setOpacity(0.8f);

		g.drawLine(0.0f, height / 2.0f, width, height / 2.0f, 1.0f);
		g.drawLine(width / 2.0f, 0, width / 2.0f, height, 1.0f);

		for (int i = 0; i <= numGridLinesX; i++) {
			g.setOpacity(0.25f);
			g.drawLine((float)i*width / (float)numGridLinesX, 0, (float)i*width / (float)numGridLinesX, height, 1.0f);
			g.setOpacity(0.75f);
			if (i <= numGridLinesX / 2) {
				g.drawText(String((int)(360 / 2 - i * 360 / numGridLinesX)) + "\xc2\xb0",
					(float)i*width / (float)numGridLinesX, height / 2, 40, 20, Justification::centred, true);
			}
			else {
				g.drawText(String((int)(360 / 2 - i * 360 / numGridLinesX)) + "\xc2\xb0",
					(float)i*width / (float)numGridLinesX - 40, height / 2, 40, 20, Justification::centred, true);
			}
		}

		for (int i = 0; i <= numGridLinesY; i++) {
			g.setOpacity(0.25f);
			g.drawLine(0, (float)i*height / (float)numGridLinesY, width, (float)i*height / (float)numGridLinesY, 1.0f);
			g.setOpacity(0.75f);
			if (i <= numGridLinesY / 2) {
				g.drawText(String((int)(180 / 2 - i * 180 / numGridLinesY)) + "\xc2\xb0",
					width / 2.0f, (float)i*height / (float)numGridLinesY, 40, 20, Justification::centred, true);
			}
			else {
				g.drawText(String((int)(180 / 2 - i * 180 / numGridLinesY)) + "\xc2\xb0",
					width / 2.0f, (float)i*height / (float)numGridLinesY - 20, 40, 20, Justification::centred, true);
			}
		}
        hasFinishedDrawing = true;
    }
}

void overlay::resized()
{
}

void overlay::mouseDown (const MouseEvent& /*e*/)
{
}

void overlay::mouseDrag (const MouseEvent& /*e*/)
{
}

