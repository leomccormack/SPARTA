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
    hAmbi = hVst->getFXHandle();
    width = _width;
    height = _height;

    for(int src=0; src<MAX_NUM_CHANNELS; src++){
        SourceIcons[src].setBounds(width - width*(ambi_enc_getSourceAzi_deg(hAmbi, src) + 180.0f)/360.f - icon_size/2.0f,
                                   height - height*(ambi_enc_getSourceElev_deg(hAmbi, src) + 90.0f)/180.0f - icon_size/2.0f,
                                   icon_size,
                                   icon_size);
    }
    NSources = ambi_enc_getNumSources(hAmbi);
    soloActive = false;
}

pannerView::~pannerView()
{
}

//==============================================================================
void pannerView::paint (Graphics& g)
{
    {
        int x = 0, y = 0, width = 480, height = 240;
        Colour fillColour1 = Colour (0xff4e4e4e), fillColour2 = Colour (0xff202020);
        Colour strokeColour = Colour (0xff9e9e9e);
        g.setGradientFill (ColourGradient (fillColour1,
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

    /* Draw Source icons */
    for(int src=0; src<NSources; src++){
        /* icon */
        //g.setColour(Colour::fromFloatRGBA(1.0-((float)src/(float)NSources), 0.3f, ((float)src/(float)NSources), 1.0f));
        g.setColour(Colour::fromFloatRGBA(1.0f, 0.0f, 1.0f, 0.85f));
        //setColourGradient(g, (float)src/(float)NSources);
        g.setOpacity(0.2f);
        g.fillEllipse(SourceIcons[src].expanded(8.0f,8.0f));
        g.setOpacity(0.4f);
        g.fillEllipse(SourceIcons[src].expanded(4.0f, 4.0f));
        g.setOpacity(0.85f);
        g.fillEllipse(SourceIcons[src]);
        /* icon ID */
        g.setColour(Colours::white);
        g.setOpacity(0.9f);
        g.drawText(String(src+1), SourceIcons[src].expanded(10.0f, 0.0f), Justification::centred, true); // .translated(icon_size, -icon_size)
    }

    /* Draw SOLO ACTIVE */
    if(soloActive){
        g.setColour(Colours::red);
        g.drawSingleLineText("SoloActive", 5, 15);
    }
}

void pannerView::resized()
{
}

void pannerView::mouseDown (const MouseEvent& e)
{
    for(int i=0; i<NSources; i++){
        Rectangle<int> icon_int;
        icon_int.setBounds(SourceIcons[i].getX(),
                           SourceIcons[i].getY(),
                           SourceIcons[i].getWidth(),
                           SourceIcons[i].getHeight());
        if(icon_int.expanded(4, 4).contains(e.getMouseDownPosition())){
            sourceIconIsClicked = true;
            indexOfClickedSource = i;

            // Solo on ALT
            if(e.mods.isAltDown()){
                ambi_enc_setSourceSolo(hAmbi, i);
                soloActive = true;
            }
            break;
        }
    }
}

void pannerView::mouseDrag (const MouseEvent& e)
{
    if(sourceIconIsClicked){
        Point<float> point;
        point.setXY((float)e.getPosition().getX()-icon_size/2.0f, (float)e.getPosition().getY()-icon_size/2.0f);
        ambi_enc_setSourceAzi_deg(hAmbi, indexOfClickedSource,
                                   ((width - (point.getX() + icon_size/2.0f))*360.0f)/width-180.0f);
        ambi_enc_setSourceElev_deg(hAmbi, indexOfClickedSource,
                                   ((height - (point.getY() + icon_size/2.0f))*180.0f)/height - 90.0f);
    }
}

void pannerView::mouseUp (const MouseEvent& e)
{
    sourceIconIsClicked = false;
    // UnSolo on ALT if not clicked on Source
    if(!e.mods.isAltDown()){
        ambi_enc_setUnSolo(hAmbi);
        soloActive = false;
    }
    repaint();
}

void pannerView::refreshPanView()
{
    for(int src=0; src<MAX_NUM_CHANNELS; src++){
        SourceIcons[src].setBounds(width - width*(ambi_enc_getSourceAzi_deg(hAmbi, src) + 180.0f)/360.f - icon_size/2.0f,
                                   height - height*(ambi_enc_getSourceElev_deg(hAmbi, src) + 90.0f)/180.0f - icon_size/2.0f,
                                   icon_size,
                                   icon_size);
    }
    NSources = ambi_enc_getNumSources(hAmbi);

    repaint();
}
