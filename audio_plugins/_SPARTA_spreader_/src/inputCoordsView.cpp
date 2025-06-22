/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2021 - Leo McCormack.
 
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

#include "inputCoordsView.h"

const int sensorEdit_width = 176;
const int sensorEdit_height = 32;

inputCoordsView::inputCoordsView (PluginProcessor& p, int _maxNCH, int _currentNCH ) : processor(p)
{
    setSize (sensorEdit_width, sensorEdit_height*currentNCH);
    hSpr = processor.getFXHandle();
    maxNCH = _maxNCH ;
    currentNCH =_currentNCH;
    aziSliders.resize(maxNCH);
    elevSliders.resize(maxNCH);
    spreadSliders.resize(maxNCH);

    for( int i=0; i<maxNCH; i++){
        /* create and initialise azimuth sliders */
        aziSliders[i] = std::make_unique<SliderWithAttachment>(p.parameters, "azim" + juce::String(i));
        addAndMakeVisible (aziSliders[i].get());
        aziSliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 48, 20);
        aziSliders[i]->setBounds(22, 8 + i*sensorEdit_height, 48, 16);
        aziSliders[i]->addListener (this);
        aziSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        aziSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        aziSliders[i]->setSliderSnapsToMousePosition(false);

        /* create and initialise elevation sliders */
        elevSliders[i] = std::make_unique<SliderWithAttachment>(p.parameters, "elev" + juce::String(i));
        addAndMakeVisible (elevSliders[i].get());
        elevSliders[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 48, 20);
        elevSliders[i]->setBounds(73, 8 + i*sensorEdit_height, 48, 16);
        elevSliders[i]->addListener (this);
        elevSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        elevSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        elevSliders[i]->setSliderSnapsToMousePosition(false);

        /* create and initialise spreading sliders */
        spreadSliders[i] = std::make_unique<SliderWithAttachment>(p.parameters, "spread" + juce::String(i));
        addAndMakeVisible (spreadSliders[i].get());
        spreadSliders[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 48, 20);
        spreadSliders[i]->setBounds(124, 8 + i*sensorEdit_height, 48, 16);
        spreadSliders[i]->addListener (this);
        spreadSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        spreadSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        spreadSliders[i]->setSliderSnapsToMousePosition(false);
    }

	/* Get and display current settings */
	resized();
}

inputCoordsView::~inputCoordsView()
{
}

void inputCoordsView::paint (juce::Graphics& g)
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
        g.drawText (String(i+1), -6, 5+ i*sensorEdit_height, 33, 23,
                    Justification::centred, true);

        /* draw rectangle around sensor parameter */
        //Colour strokeColour = Colour (0x2370702b);
        //g.setColour (strokeColour);
        g.setColour(Colours::white);
        g.setOpacity(0.15f);
        g.drawRect (0, i*sensorEdit_height, sensorEdit_width, sensorEdit_height+1, 1);
    }
}

void inputCoordsView::resized()
{
    setSize (sensorEdit_width, sensorEdit_height*currentNCH);
    repaint();
}

void inputCoordsView::sliderValueChanged (juce::Slider* /*sliderThatWasMoved*/)
{
}
