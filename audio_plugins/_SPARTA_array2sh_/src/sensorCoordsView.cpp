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

#include "sensorCoordsView.h"

const int sensorEdit_width = 176;
const int sensorEdit_height = 32;

sensorCoordsView::sensorCoordsView (PluginProcessor& p, int _maxQ, int _currentQ) : processor(p)
{
    setSize (sensorEdit_width, sensorEdit_height*_currentQ);
    hA2sh = processor.getFXHandle();
    maxQ = _maxQ;
    currentQ =_currentQ;
    aziSliders.resize(maxQ);
    elevSliders.resize(maxQ);

    for( int i=0; i<maxQ; i++){
        /* create and initialise azimuth sliders */
        aziSliders[i] = std::make_unique<SliderWithAttachment>(p.parameters, "azim" + juce::String(i));
        addAndMakeVisible (aziSliders[i].get());
        aziSliders[i]->setSliderStyle (Slider::LinearHorizontal);
        aziSliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 70, 20);
        aziSliders[i]->setBounds(-25, 8 + i*sensorEdit_height, 96, 16);
        aziSliders[i]->addListener (this);

        /* create and initialise elevation sliders */
        elevSliders[i] = std::make_unique<SliderWithAttachment>(p.parameters, "elev" + juce::String(i));
        addAndMakeVisible (elevSliders[i].get());
        elevSliders[i]->setSliderStyle (Slider::LinearHorizontal);
        elevSliders[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 70, 20);
        elevSliders[i]->setBounds(105, 8 + i*sensorEdit_height, 96, 16);
        elevSliders[i]->addListener (this);
    }

    resized();
}

sensorCoordsView::~sensorCoordsView()
{
}

void sensorCoordsView::paint (juce::Graphics& g)
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

    for( int i=0; i<maxQ; i++){
        /* draw sensor IDs */
        g.setColour (fillColour);
        g.drawText (String(i+1), 72, 5+ i*sensorEdit_height, 33, 23,
                    Justification::centred, true);

        /* draw rectangle around sensor parameter */
        //Colour strokeColour = Colour (0x2370702b);
        //g.setColour (strokeColour);
        g.setColour(Colours::white);
        g.setOpacity(0.15f);
        g.drawRect (0, i*sensorEdit_height, sensorEdit_width, sensorEdit_height+1, 1);
    }
}

void sensorCoordsView::resized()
{
    setSize (sensorEdit_width, sensorEdit_height*currentQ+1);
    repaint();
}

void sensorCoordsView::sliderValueChanged (juce::Slider* /*sliderThatWasMoved*/)
{
}
