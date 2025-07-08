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

#include "outputCoordsView.h"

const int sensorEdit_width = 212;
const int sensorEdit_height = 32;

outputCoordsView::outputCoordsView (PluginProcessor& p, int _maxNCH, int _currentNCH ) : processor(p)
{
    setSize (sensorEdit_width, sensorEdit_height*currentNCH);
    hAmbi = processor.getFXHandle();
    maxNCH = _maxNCH ;
    currentNCH =_currentNCH;
    xSliders.resize(maxNCH);
    ySliders.resize(maxNCH);
    zSliders.resize(maxNCH);

    for( int i=0; i<maxNCH; i++){
        /* create x sliders */
        xSliders[i] = std::make_unique<SliderWithAttachment>(p.parameters, "receiverX" + juce::String(i));
        addAndMakeVisible (xSliders[i].get());
        xSliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 58, 20);
        xSliders[i]->setBounds(24, 6 + i*sensorEdit_height, 58, 20);
        xSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        xSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        xSliders[i]->setSliderSnapsToMousePosition(false);

        /* create y sliders */
        ySliders[i] = std::make_unique<SliderWithAttachment>(p.parameters, "receiverY" + juce::String(i));
        addAndMakeVisible (ySliders[i].get());
        ySliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 58, 20);
        ySliders[i]->setBounds(86, 6 + i*sensorEdit_height, 58, 20);
        ySliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        ySliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        ySliders[i]->setSliderSnapsToMousePosition(false);

        /* create z sliders */
        zSliders[i] = std::make_unique<SliderWithAttachment>(p.parameters, "receiverZ" + juce::String(i));
        addAndMakeVisible (zSliders[i].get());
        zSliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 58, 20);
        zSliders[i]->setBounds(148, 6 + i*sensorEdit_height, 58, 20);
        zSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        zSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        zSliders[i]->setSliderSnapsToMousePosition(false);
    }

    resized();
}

outputCoordsView::~outputCoordsView()
{
}

void outputCoordsView::paint (juce::Graphics& g)
{
    {
        int x = 88, y = 0, width = 88, height = 2048;
        juce::Colour fillColour1 = juce::Colour (0x21ffffff), fillColour2 = juce::Colour (0x05252a25);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             88.0f - 88.0f + x,
                                             128.0f - 0.0f + y,
                                             fillColour2,
                                             176.0f - 88.0f + x,
                                             128.0f - 0.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 0, width = 88, height = 2048;
        juce::Colour fillColour1 = juce::Colour (0x21ffffff), fillColour2 = juce::Colour (0x05252a25);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             88.0f - 0.0f + x,
                                             128.0f - 0.0f + y,
                                             fillColour2,
                                             0.0f - 0.0f + x,
                                             128.0f - 0.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    Colour fillColour = Colours::white;
    g.setColour (fillColour);
    g.setFont (juce::FontOptions (15.00f, Font::plain).withStyle ("Regular"));

    for( int i=0; i<maxNCH; i++){
        /* draw sensor IDs */
        g.setColour (fillColour);
        g.drawText (String(i+1), -4, 5+ i*sensorEdit_height, 33, 23,
                    Justification::centred, true);

        /* draw rectangle around sensor parameter */
        //Colour strokeColour = Colour (0x2370702b);
        //g.setColour (strokeColour);
        g.setColour(Colours::white);
        g.setOpacity(0.15f);
        g.drawRect (0, i*sensorEdit_height, sensorEdit_width, sensorEdit_height+1, 1);
    }
}

void outputCoordsView::resized()
{
    setSize (sensorEdit_width, sensorEdit_height*currentNCH);
    repaint();
}

void outputCoordsView::sliderValueChanged (juce::Slider* /*sliderThatWasMoved*/)
{
}

