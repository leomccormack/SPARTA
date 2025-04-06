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

inputCoordsView::inputCoordsView (PluginProcessor* ownerFilter, int _maxNCH, int _currentNCH )
{
    dummySlider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (dummySlider.get());
    dummySlider->setRange (0.01, 0.3, 0.001);
    dummySlider->setSliderStyle (juce::Slider::LinearHorizontal);
    dummySlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 70, 20);
    dummySlider->addListener (this);

    dummySlider->setBounds (-176, 144, 96, 16);

    setSize (sensorEdit_width, sensorEdit_height*currentNCH);
    hVst = ownerFilter;
    hSpr = hVst->getFXHandle();
    maxNCH = _maxNCH ;
    currentNCH =_currentNCH;
    aziSliders =  new std::unique_ptr<Slider>[(unsigned long)maxNCH];
    elevSliders =  new std::unique_ptr<Slider>[(unsigned long)maxNCH];
    spreadSliders =  new std::unique_ptr<Slider>[(unsigned long)maxNCH];

    for( int i=0; i<maxNCH; i++){
        /* create and initialise azimuth sliders */
        aziSliders[i].reset (new Slider ("new slider"));
        addAndMakeVisible (aziSliders[i].get());
        aziSliders[i]->setRange (-360.0, 360.0, 0.1);
        aziSliders[i]->setValue(spreader_getSourceAzi_deg(hSpr, i));
        aziSliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 48, 20);
        aziSliders[i]->setBounds(22, 8 + i*sensorEdit_height, 48, 16);
        aziSliders[i]->addListener (this);
        aziSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        aziSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        aziSliders[i]->setSliderSnapsToMousePosition(false);

        /* create and initialise elevation sliders */
        elevSliders[i].reset (new Slider ("new slider"));
        addAndMakeVisible (elevSliders[i].get());
        elevSliders[i]->setRange (-180.0, 180.0, 0.1);
        elevSliders[i]->setValue(spreader_getSourceElev_deg(hSpr, i));
        elevSliders[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 48, 20);
        elevSliders[i]->setBounds(73, 8 + i*sensorEdit_height, 48, 16);
        elevSliders[i]->addListener (this);
        elevSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        elevSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        elevSliders[i]->setSliderSnapsToMousePosition(false);

        /* create and initialise spreading sliders */
        spreadSliders[i].reset (new Slider ("new slider"));
        addAndMakeVisible (spreadSliders[i].get());
        spreadSliders[i]->setRange (0.0, 360.0, 0.1);
        spreadSliders[i]->setValue(spreader_getSourceElev_deg(hSpr, i));
        spreadSliders[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 48, 20);
        spreadSliders[i]->setBounds(124, 8 + i*sensorEdit_height, 48, 16);
        spreadSliders[i]->addListener (this);
        spreadSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        spreadSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        spreadSliders[i]->setSliderSnapsToMousePosition(false);
    }
    sliderHasChanged = true;

	/* Get and display current settings */
	refreshCoords();
	resized();
}

inputCoordsView::~inputCoordsView()
{
    dummySlider = nullptr;

    for( int i=0; i<maxNCH; i++){
        aziSliders[i] = nullptr;
        elevSliders[i] = nullptr;
        spreadSliders[i] = nullptr;
    }
    delete [] aziSliders;
    delete [] elevSliders;
    delete [] spreadSliders;
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

void inputCoordsView::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    for(int i=0; i<maxNCH; i++){
        if (sliderThatWasMoved == aziSliders[i].get()) {
            spreader_setSourceAzi_deg(hSpr, i, (float)aziSliders[i]->getValue());
            break;
        }
        if (sliderThatWasMoved == elevSliders[i].get()) {
            spreader_setSourceElev_deg(hSpr, i, (float)elevSliders[i]->getValue());
            break;
        }
        if (sliderThatWasMoved == spreadSliders[i].get()) {
            spreader_setSourceSpread_deg(hSpr, i, (float)spreadSliders[i]->getValue());
            break;
        }
    }

    if (sliderThatWasMoved == dummySlider.get())
    {
    }

    sliderHasChanged = true;
}

void inputCoordsView::refreshCoords(){
    /* update slider values and limits */
    for( int i=0; i<maxNCH; i++){
        aziSliders[i]->setRange (-360.0, 360.0, 0.1);
        aziSliders[i]->setValue(spreader_getSourceAzi_deg(hSpr, i), dontSendNotification);
        elevSliders[i]->setRange (-180.0, 180.0, 0.1);
        elevSliders[i]->setValue(spreader_getSourceElev_deg(hSpr, i), dontSendNotification);
        spreadSliders[i]->setRange (0.0, 360.0, 0.1);
        spreadSliders[i]->setValue(spreader_getSourceSpread_deg(hSpr, i), dontSendNotification);
    }
}

