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
    hBin = hVst->getFXHandle();
    maxNCH = _maxNCH ;
    currentNCH =_currentNCH;
    aziSliders = new std::unique_ptr<Slider>[(unsigned long)maxNCH];
    elevSliders = new std::unique_ptr<Slider>[(unsigned long)maxNCH];
    distSliders = new std::unique_ptr<Slider>[(unsigned long)maxNCH];

    int left = 15, tbw = 45, tbh = 20, tbhpad = 6; // text box layout dimensions
    int tbvpad = (sensorEdit_height - tbh) / 2;
    for( int i=0; i<maxNCH; i++){
        /* create and initialise azimuth sliders */
        aziSliders[i].reset (new Slider ("new slider"));
        aziSliders[i]->setTooltip("Source azimuth: 0 degrees is forward, 90 degrees is left, -90 degrees right.");
        addAndMakeVisible (aziSliders[i].get());
        aziSliders[i]->setRange (-360.0, 360.0, 0.1); // overwritten by refreshCoords() below
        aziSliders[i]->setValue(binauraliser_getSourceAzi_deg(hBin, i));
        aziSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical); // vertical drag slider as number box
        aziSliders[i]->setSliderSnapsToMousePosition(false);
        aziSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        aziSliders[i]->setColour(Slider::rotarySliderFillColourId, Colours::transparentBlack); // hide slider value fill
        aziSliders[i]->setBounds(left+tbhpad, tbvpad + i*sensorEdit_height, tbw, tbh);
        aziSliders[i]->addListener (this);
        aziSliders[i]->setNumDecimalPlacesToDisplay (1);

        /* create and initialise elevation sliders */
        elevSliders[i].reset (new Slider ("new slider"));
        elevSliders[i]->setTooltip("Source elevation: 90 degrees is above, -90 degree is below.");
        addAndMakeVisible (elevSliders[i].get());
        elevSliders[i]->setRange (-180.0, 180.0, 0.1);
        elevSliders[i]->setNumDecimalPlacesToDisplay (1);
        elevSliders[i]->setValue(binauraliser_getSourceElev_deg(hBin, i));
        elevSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        elevSliders[i]->setSliderSnapsToMousePosition(false);
        elevSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        elevSliders[i]->setColour(Slider::rotarySliderFillColourId, Colours::transparentBlack);
        elevSliders[i]->setBounds(left+tbhpad+tbw+tbhpad, tbvpad + i*sensorEdit_height, tbw, tbh);
        elevSliders[i]->addListener (this);

        /* create and initialise distance sliders */
        distSliders[i].reset (new Slider ("new slider"));
        distSliders[i]->setTooltip("Distance from the center of the head (m). Filters disengage when maximally far (approx > 3 m).");
        addAndMakeVisible (distSliders[i].get());
        distSliders[i]->setRange (binauraliserNF_getNearfieldLimit_m(hBin), hVst->upperDistRange, 0.001);
        distSliders[i]->setNumDecimalPlacesToDisplay (2);
        distSliders[i]->setSkewFactor (0.5, false);
        distSliders[i]->setValue(binauraliserNF_getSourceDist_m(hBin, i));
        distSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        distSliders[i]->setSliderSnapsToMousePosition(false);
        distSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        distSliders[i]->setColour(Slider::rotarySliderFillColourId , Colours::transparentBlack);
        distSliders[i]->setBounds(left+tbhpad+tbw+tbhpad+tbw+tbhpad, tbvpad + i*sensorEdit_height, tbw, tbh);
        distSliders[i]->addListener (this);
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
        distSliders[i] = nullptr;
    }
    delete [] aziSliders;
    delete [] elevSliders;
    delete [] distSliders;
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
        g.drawText (String(i+1), -6, 4 + i*sensorEdit_height, 33, 23,
                    Justification::centred, true);
        /* draw rectangle around sensor parameter */
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
            binauraliser_setSourceAzi_deg(hBin, i, (float)aziSliders[i]->getValue());
            break;
        }
        if (sliderThatWasMoved == elevSliders[i].get()) {
            binauraliser_setSourceElev_deg(hBin, i, (float)elevSliders[i]->getValue());
            break;
        }
        if (sliderThatWasMoved == distSliders[i].get()) {
            binauraliserNF_setSourceDist_m(hBin, i, (float)distSliders[i]->getValue());
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
        aziSliders[i]->setRange (-360.0, 360.0, 0.1); // TODO: this range doens't conform to binauraliser_setSourceAzi_deg, so UI bugs out beyond +/-180 when dragging (but value OK on mouseup)
        aziSliders[i]->setValue(binauraliser_getSourceAzi_deg(hBin, i), dontSendNotification);

        elevSliders[i]->setRange (-180.0, 180.0, 0.1);
        elevSliders[i]->setValue (binauraliser_getSourceElev_deg(hBin, i), dontSendNotification);

        distSliders[i]->setRange (binauraliserNF_getNearfieldLimit_m(hBin), hVst->upperDistRange, 0.01);
        distSliders[i]->setValue (binauraliserNF_getSourceDist_m(hBin, i), dontSendNotification);
    }
}
