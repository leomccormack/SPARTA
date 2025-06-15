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

pannerView::pannerView (PluginProcessor& p, int _width, int _height) : processor(p)
{
    setSize (492, 246);

    hBin = processor.getFXHandle();
    width = _width;
    height = _height;

    for(int src=0; src<MAX_NUM_INPUTS; src++){
        SourceIcons[src].setBounds(width - width*(binauraliser_getSourceAzi_deg(hBin, src) + 180.0f)/360.f - icon_size/2.0f,
                                   height - height*(binauraliser_getSourceElev_deg(hBin, src) + 90.0f)/180.0f - icon_size/2.0f,
                                   icon_size,
                                   icon_size);
    }
    NSources = binauraliser_getNumSources(hBin);
    NLoudspeakers = binauraliser_getNDirs(hBin)>MAX_NUM_OUT_DIRS? MAX_NUM_OUT_DIRS : binauraliser_getNDirs(hBin);
    for(int ls=0; ls<NLoudspeakers; ls++){
        LoudspeakerIcons[ls].setBounds(width - width*(binauraliser_getHRIRAzi_deg(hBin, ls) + 180.0f)/360.f - icon_size/2.0f,
                                       height - height*(binauraliser_getHRIRElev_deg(hBin, ls)+90.0f)/180.0f - icon_size/2.0f,
                                       icon_size,
                                       icon_size);
    }
    showInputs = true;
    showOutputs = true;
	sourceIconIsClicked = false;
    soloActive = false;
}

pannerView::~pannerView()
{
}

void pannerView::paint (juce::Graphics& g)
{
    {
        int x = 0, y = 0, width = 492, height = 246;
        juce::Colour fillColour1 = juce::Colour (0xff4e4e4e), fillColour2 = juce::Colour (0xff202020);
        juce::Colour strokeColour = juce::Colour (0xff9e9e9e);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             248.0f - 0.0f + x,
                                             0.0f - 0.0f + y,
                                             fillColour2,
                                             248.0f - 0.0f + x,
                                             248.0f - 0.0f + y,
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

    if(showOutputs){
        /* Draw loudspeaker/HRIR icons */
        for(int ls=0; ls<NLoudspeakers; ls++){
            /* icon */
            g.setColour(Colour::fromFloatRGBA(0.5f, 1.0f, 0.1f, 1.0f));
            g.setOpacity(0.3f);
            g.fillRect(LoudspeakerIcons[ls]);
        }
    }

    if(showInputs){
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

void pannerView::mouseDown (const juce::MouseEvent& e)
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
                binauraliser_setSourceSolo(hBin, i);
                soloActive = true;
            }
            break;
        }
    }
}

void pannerView::mouseDrag (const juce::MouseEvent& e)
{
    if(sourceIconIsClicked){
        Point<float> point;
        point.setXY((float)e.getPosition().getX()-icon_size/2.0f, (float)e.getPosition().getY()-icon_size/2.0f);
        
        processor.setParameterValue("azim" + juce::String(indexOfClickedSource), ((width - (point.getX() + icon_size/2.0f))*360.0f)/width - 180.0f);
        processor.setParameterValue("elev" + juce::String(indexOfClickedSource), ((height - (point.getY() + icon_size/2.0f))*180.0f)/height - 90.0f);
    }
}

void pannerView::mouseUp (const juce::MouseEvent& e)
{
    sourceIconIsClicked = false;
    // UnSolo on ALT if not clicked on Source
    if(!e.mods.isAltDown()){
        binauraliser_setUnSolo(hBin);
        soloActive = false;
    }
    repaint();
}

void pannerView::refreshPanView()
{
    for(int src=0; src<MAX_NUM_INPUTS; src++){
        SourceIcons[src].setBounds(width - width*(binauraliser_getSourceAzi_deg(hBin, src) + 180.0f)/360.f - icon_size/2.0f,
                                   height - height*(binauraliser_getSourceElev_deg(hBin, src) + 90.0f)/180.0f - icon_size/2.0f,
                                   icon_size,
                                   icon_size);
    }
    NSources = binauraliser_getNumSources(hBin);
    NLoudspeakers = binauraliser_getNDirs(hBin)>MAX_NUM_OUT_DIRS ? MAX_NUM_OUT_DIRS : binauraliser_getNDirs(hBin);
    for(int ls=0; ls<NLoudspeakers; ls++){
        LoudspeakerIcons[ls].setBounds(width - width*(binauraliser_getHRIRAzi_deg(hBin, ls) + 180.0f)/360.f - icon_size/2.0f,
                                       height - height*(binauraliser_getHRIRElev_deg(hBin, ls) + 90.0f)/180.0f - icon_size/2.0f,
                                       icon_size,
                                       icon_size);
    }

    repaint();
}
