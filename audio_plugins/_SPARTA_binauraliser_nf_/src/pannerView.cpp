/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2018 - Michael McCrea, Leo McCormack.
 
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

pannerView::pannerView (PluginProcessor* ownerFilter, int _width, int _height)
{
    setSize (492, 246);

    hVst = ownerFilter;
    hBin = hVst->getFXHandle();
    width = _width;
    height = _height;
    halfWidth = width / 2.0f;
    halfHeight = height / 2.0f;
    icon_diam_src = height / 25.0f;
    icon_radius_src = icon_diam_src / 2.0f;
    icon_diam_hrir = height / 45.0f;
    icon_radius_hrir = icon_diam_src / 2.0f;
    ffThresh = binauraliserNF_getFarfieldThresh_m(hBin);
    // distance range of a source (closest -> farthest)
    distRange = NormalisableRange<float>(binauraliserNF_getNearfieldLimit_m(hBin), hVst->upperDistRange, 0, 0.5f);
    // pixel radius corresponding to a 45 degree spread: height/4
    iconGrowFac = NormalisableRange<float>(1.0f, (height / 4.0f) / (icon_radius_src * 3.0f));

    setSize (width, height);

    updateSrcLsIconBounds();
    
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

    g.drawLine(0.0f, halfHeight, width, halfHeight, 1.0f);
    g.drawLine(halfWidth, 0, halfWidth, height, 1.0f);

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
                       halfWidth, (float)i*height / (float)numGridLinesY, 40, 20, Justification::centred, true);
        }
        else {
            g.drawText(String((int)(180 / 2 - i * (int)180 / numGridLinesY)) + "\xc2\xb0",
                       halfWidth, (float)i*height / (float)numGridLinesY - 20, 40, 20, Justification::centred, true);
        }
    }

    if(showOutputs){
        /* Draw loudspeaker/HRIR icons */
        for(int ls=0; ls<NLoudspeakers; ls++){
            /* icon */
            g.setColour(Colour::fromFloatRGBA(0.5f, 1.0f, 0.1f, 1.0f));
            g.setOpacity(0.3f);
            g.fillEllipse(LoudspeakerIcons[ls]);
        }
    }

    if(showInputs){
        /* Draw Source icons */
        for(int src=0; src<NSources; src++){
            float curDist = binauraliserNF_getSourceDist_m(hBin, src);
            float srcDist_norm = 1.0f - distRange.convertTo0to1(curDist);
            float newDim1 = icon_radius_src * iconGrowFac.convertFrom0to1(srcDist_norm);
            float newDim2 = newDim1 * 2.0f;
            float newDim3 = newDim1 * 3.0f;
            g.setColour(Colour::fromFloatRGBA(1.0f, 0.0f, 1.0f, 0.85f));
            g.setOpacity(0.3f);
            g.fillEllipse(SourceIcons[src].withSizeKeepingCentre(newDim1, newDim1));
            g.fillEllipse(SourceIcons[src].withSizeKeepingCentre(newDim2, newDim2));
            if (curDist < ffThresh) {
                g.setColour(Colour::fromFloatRGBA(255.f/255.f, 183.f/255.f, 3.f/255.f, 0.3f));
            }
            g.fillEllipse(SourceIcons[src].withSizeKeepingCentre(newDim3, newDim3));
        }
        /* Draw Source Icon ID (always on top) */
        g.setColour(Colours::white);
        g.setOpacity(0.9f);
        for(int src=0; src<NSources; src++){
            g.drawText(String(src+1), SourceIcons[src].expanded(10.0f, 0.0f), Justification::centred, true);
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
        point.setXY((float)e.getPosition().getX()-icon_radius_src, (float)e.getPosition().getY()-icon_radius_src);
        binauraliser_setSourceAzi_deg(hBin, indexOfClickedSource,
                                   ((width - (point.getX() + icon_radius_src)) * 360.0f) / width - 180.0f);
        binauraliser_setSourceElev_deg(hBin, indexOfClickedSource,
                                   ((height - (point.getY() + icon_radius_src)) * 180.0f) / height - 90.0f);
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
    updateSrcLsIconBounds();
    repaint();
}

void pannerView::updateSrcLsIconBounds()
{
    for(int src=0; src<MAX_NUM_INPUTS; src++){
        SourceIcons[src].setBounds(
                                   width - width * (binauraliser_getSourceAzi_deg(hBin, src) + 180.0f) / 360.f - icon_radius_src,
                                   height - height * (binauraliser_getSourceElev_deg(hBin, src) + 90.0f) / 180.0f - icon_radius_src,
                                   icon_diam_src,
                                   icon_diam_src );
    }
    NSources = binauraliser_getNumSources(hBin);
    NLoudspeakers = binauraliser_getNDirs(hBin)>MAX_NUM_OUT_DIRS? MAX_NUM_OUT_DIRS : binauraliser_getNDirs(hBin);
    for(int ls=0; ls<NLoudspeakers; ls++){
        LoudspeakerIcons[ls].setBounds(
                                       width - width * (binauraliser_getHRIRAzi_deg(hBin, ls) + 180.0f) / 360.f - icon_radius_hrir,
                                       height - height * (binauraliser_getHRIRElev_deg(hBin, ls) + 90.0f) / 180.0f - icon_radius_hrir,
                                       icon_diam_hrir,
                                       icon_diam_hrir );
    }
}
