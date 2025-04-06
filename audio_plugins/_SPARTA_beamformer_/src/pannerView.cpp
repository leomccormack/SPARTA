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

#include "pannerView.h"

const float icon_size = 8.0f;

//==============================================================================
pannerView::pannerView (PluginProcessor* ownerFilter, int _width, int _height)
{
    setSize (480, 240);

    hVst = ownerFilter;
    hBeam = hVst->getFXHandle();
    width = _width;
    height = _height;

    for(int beam=0; beam<MAX_NUM_CHANNELS; beam++){
        BeamIcons[beam].setBounds(width - width*(beamformer_getBeamAzi_deg(hBeam, beam) + 180.0f)/360.f - icon_size/2.0f,
                                   height - height*(beamformer_getBeamElev_deg(hBeam, beam) + 90.0f)/180.0f - icon_size/2.0f,
                                   icon_size,
                                   icon_size);
    }
    NBeams = beamformer_getNumBeams(hBeam);
}

pannerView::~pannerView()
{
}

//==============================================================================
void pannerView::paint (juce::Graphics& g)
{
    {
        int x = 0, y = 0, width = 480, height = 240;
        juce::Colour fillColour1 = juce::Colour (0xff4e4e4e), fillColour2 = juce::Colour (0xff202020);
        juce::Colour strokeColour = juce::Colour (0xff9e9e9e);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             248.0f - 0.0f + x,
                                             0.0f - 0.0f + y,
                                             fillColour2,
                                             248.0f - 0.0f + x,
                                             240.0f - 0.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    /* Draw Grid lines and labels */
    int numGridLinesX = 8;
    int numGridLinesY = numGridLinesX / 2;
    g.setColour(Colours::white);
    g.setOpacity(0.75f);

    g.drawLine(0.0f, height / 2.0f, width, height / 2.0f, 1.0f);
    g.drawLine(width / 2.0f, 0, width / 2.0f, height, 1.0f);

    for (int i = 0; i <= numGridLinesX; i++) {
        g.setOpacity(0.1f);
        g.drawLine((float)i*width / (float)numGridLinesX, 0, (float)i*width / (float)numGridLinesX, height, 1.0f);
        g.setOpacity(0.75f);
        if (i <= numGridLinesX / 2) {
            g.drawText(String((int)(360 / 2 - i * (int)360 / numGridLinesX)) + "\xc2\xb0",
                       (float)i*width / (float)numGridLinesX, height / 2, 40, 20, Justification::centred, true);
        }
        else {
            g.drawText(String((int)(360 / 2 - i * (int)360 / numGridLinesX)) + "\xc2\xb0",
                       (float)i*width / (float)numGridLinesX - 40, height / 2, 40, 20, Justification::centred, true);
        }
    }

    for (int i = 0; i <= numGridLinesY; i++) {
        g.setOpacity(0.1f);
        g.drawLine(0, (float)i*height / (float)numGridLinesY, width, (float)i*height / (float)numGridLinesY, 1.0f);
        g.setOpacity(0.75f);
        if (i <= numGridLinesY / 2) {
            g.drawText(String((int)(180 / 2 - i * (int)180 / numGridLinesY)) + "\xc2\xb0",
                       width / 2.0f, (float)i*height / (float)numGridLinesY, 40, 20, Justification::centred, true);
        }
        else {
            g.drawText(String((int)(180 / 2 - i * (int)180 / numGridLinesY)) + "\xc2\xb0",
                       width / 2.0f, (float)i*height / (float)numGridLinesY - 20, 40, 20, Justification::centred, true);
        }
    }

    /* Draw Beam icons */
    for(int src=0; src<NBeams; src++){
        /* icon */
        //g.setColour(Colour::fromFloatRGBA(1.0-((float)src/(float)NSources), 0.3f, ((float)src/(float)NSources), 1.0f));
        g.setColour(Colour::fromFloatRGBA(1.0f, 0.0f, 1.0f, 0.85f));
        //setColourGradient(g, (float)src/(float)NSources);
        g.setOpacity(0.2f);
        g.fillEllipse(BeamIcons[src].expanded(8.0f,8.0f));
        g.setOpacity(0.4f);
        g.fillEllipse(BeamIcons[src].expanded(4.0f, 4.0f));
        g.setOpacity(0.85f);
        g.fillEllipse(BeamIcons[src]);
        /* icon ID */
        g.setColour(Colours::white);
        g.setOpacity(0.9f);
        g.drawText(String(src+1), BeamIcons[src].expanded(10.0f, 0.0f), Justification::centred, true); // .translated(icon_size, -icon_size)
    }
}

void pannerView::resized()
{
}

void pannerView::mouseDown (const juce::MouseEvent& e)
{
    for(int i=0; i<NBeams; i++){
        Rectangle<int> icon_int;
        icon_int.setBounds(BeamIcons[i].getX(),
                           BeamIcons[i].getY(),
                           BeamIcons[i].getWidth(),
                           BeamIcons[i].getHeight());
        if(icon_int.expanded(4, 4).contains(e.getMouseDownPosition())){
            beamIconIsClicked = true;
            indexOfClickedBeam = i;
            break;
        }
    }
}

void pannerView::mouseDrag (const juce::MouseEvent& e)
{
    if(beamIconIsClicked){
        Point<float> point;
        point.setXY((float)e.getPosition().getX()-icon_size/2.0f, (float)e.getPosition().getY()-icon_size/2.0f);
        beamformer_setBeamAzi_deg(hBeam, indexOfClickedBeam,
                                   ((width - (point.getX() + icon_size/2.0f))*360.0f)/width-180.0f);
        beamformer_setBeamElev_deg(hBeam, indexOfClickedBeam,
                                   ((height - (point.getY() + icon_size/2.0f))*180.0f)/height - 90.0f);
    }
}

void pannerView::mouseUp (const juce::MouseEvent& /*e*/)
{
    beamIconIsClicked = false;
}

void pannerView::refreshPanView()
{
    for(int beam=0; beam<MAX_NUM_CHANNELS; beam++){
        BeamIcons[beam].setBounds(width - width*(beamformer_getBeamAzi_deg(hBeam, beam) + 180.0f)/360.f - icon_size/2.0f,
                                   height - height*(beamformer_getBeamElev_deg(hBeam, beam) + 90.0f)/180.0f - icon_size/2.0f,
                                   icon_size,
                                   icon_size);
    }
    NBeams = beamformer_getNumBeams(hBeam);

    repaint();
}
