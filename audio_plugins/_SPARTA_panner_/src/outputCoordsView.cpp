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

const int sensorEdit_width = 176;
const int sensorEdit_height = 32;

outputCoordsView::outputCoordsView (PluginProcessor& p, int _maxNCH, int _currentNCH ) : processor(p)
{
    setSize (sensorEdit_width, sensorEdit_height*currentNCH);
    hPan = processor.getFXHandle();
    maxNCH = _maxNCH ;
    currentNCH =_currentNCH;
    aziSliders.resize(maxNCH);
    elevSliders.resize(maxNCH);

    for( int i=0; i<maxNCH; i++){
        /* create and initialise azimuth sliders */
        aziSliders[i] = std::make_unique<SliderWithAttachment>(p.parameters, "lsAzim" + juce::String(i));
        addAndMakeVisible (aziSliders[i].get());
        aziSliders[i]->setSliderStyle (Slider::LinearHorizontal);
        aziSliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 70, 20);
        aziSliders[i]->setBounds(4, 6 + i*sensorEdit_height, 67, 20);
        aziSliders[i]->addListener (this);

        /* create and initialise elevation sliders */
        elevSliders[i] = std::make_unique<SliderWithAttachment>(p.parameters, "lsAzim" + juce::String(i));
        addAndMakeVisible (elevSliders[i].get());
        elevSliders[i]->setSliderStyle (Slider::LinearHorizontal);
        elevSliders[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 70, 20);
        elevSliders[i]->setBounds(105, 6 + i*sensorEdit_height, 67, 20);
        elevSliders[i]->addListener (this);
        
        /* remove slider bit of these sliders */
        aziSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        aziSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        aziSliders[i]->setSliderSnapsToMousePosition(false);
        elevSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        elevSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        elevSliders[i]->setSliderSnapsToMousePosition(false);
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

void outputCoordsView::resized()
{
    setSize (sensorEdit_width, sensorEdit_height*currentNCH);
    repaint();
}

void outputCoordsView::sliderValueChanged (juce::Slider* /*sliderThatWasMoved*/)
{
}
