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

//==============================================================================
outputCoordsView::outputCoordsView (PluginProcessor* ownerFilter, int _maxNCH, int _currentNCH )
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
    hAmbi = hVst->getFXHandle();
    maxNCH = _maxNCH ;
    currentNCH =_currentNCH;
    xSliders =  new std::unique_ptr<Slider>[maxNCH];
    ySliders =  new std::unique_ptr<Slider>[maxNCH];
    zSliders =  new std::unique_ptr<Slider>[maxNCH];

    for( int i=0; i<maxNCH; i++){
        /* create x sliders */
        xSliders[i].reset (new Slider ("new slider"));
        addAndMakeVisible (xSliders[i].get());
        xSliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 58, 20);
        xSliders[i]->setBounds(24, 8 + i*sensorEdit_height, 58, 16);
        xSliders[i]->addListener (this);
        xSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        xSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        xSliders[i]->setSliderSnapsToMousePosition(false);

        /* create y sliders */
        ySliders[i].reset (new Slider ("new slider"));
        addAndMakeVisible (ySliders[i].get());
        ySliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 58, 20);
        ySliders[i]->setBounds(86, 8 + i*sensorEdit_height, 58, 16);
        ySliders[i]->addListener (this);
        ySliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        ySliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        ySliders[i]->setSliderSnapsToMousePosition(false);

        /* create z sliders */
        zSliders[i].reset (new Slider ("new slider"));
        addAndMakeVisible (zSliders[i].get());
        zSliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 58, 20);
        zSliders[i]->setBounds(148, 8 + i*sensorEdit_height, 58, 16);
        zSliders[i]->addListener (this);
        zSliders[i]->setColour(Slider::trackColourId, Colours::transparentBlack);
        zSliders[i]->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        zSliders[i]->setSliderSnapsToMousePosition(false);

        /* Initialise sliders */
        xSliders[i]->setRange (0.0f, ambi_roomsim_getRoomDimX(hAmbi), 0.001);
        xSliders[i]->setValue(ambi_roomsim_getReceiverX(hAmbi, i), dontSendNotification);
        ySliders[i]->setRange (0.0f, ambi_roomsim_getRoomDimY(hAmbi), 0.001);
        ySliders[i]->setValue(ambi_roomsim_getReceiverY(hAmbi, i), dontSendNotification);
        zSliders[i]->setRange (0.0f, ambi_roomsim_getRoomDimZ(hAmbi), 0.001);
        zSliders[i]->setValue(ambi_roomsim_getReceiverZ(hAmbi, i), dontSendNotification);
    }

    sliderHasChanged = true;
    refreshCoords();
    resized();
}

outputCoordsView::~outputCoordsView()
{
    dummySlider = nullptr;

    for( int i=0; i<maxNCH; i++){
        xSliders[i] = nullptr;
        ySliders[i] = nullptr;
        zSliders[i] = nullptr;
    }
    delete [] xSliders;
    delete [] ySliders;
    delete [] zSliders;
}

//==============================================================================
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

void outputCoordsView::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    for(int i=0; i<maxNCH; i++){
        if (sliderThatWasMoved == xSliders[i].get()) {
            ambi_roomsim_setReceiverX(hAmbi, i, (float)xSliders[i]->getValue());
            break;
        }
        if (sliderThatWasMoved == ySliders[i].get()) {
            ambi_roomsim_setReceiverY(hAmbi, i, (float)ySliders[i]->getValue());
            break;
        }
        if (sliderThatWasMoved == zSliders[i].get()) {
            ambi_roomsim_setReceiverZ(hAmbi, i, (float)zSliders[i]->getValue());
            break;
        }
    }

    if (sliderThatWasMoved == dummySlider.get())
    {
    }

    sliderHasChanged = true;
}

void outputCoordsView::refreshCoords(){
    /* update slider values and limits */
    for( int i=0; i<maxNCH; i++){
        xSliders[i]->setRange (0.0f, ambi_roomsim_getRoomDimX(hAmbi), 0.001);
        xSliders[i]->setValue(ambi_roomsim_getReceiverX(hAmbi, i), dontSendNotification);
        ySliders[i]->setRange (0.0f, ambi_roomsim_getRoomDimY(hAmbi), 0.001);
        ySliders[i]->setValue(ambi_roomsim_getReceiverY(hAmbi, i), dontSendNotification);
        zSliders[i]->setRange (0.0f, ambi_roomsim_getRoomDimZ(hAmbi), 0.001);
        zSliders[i]->setValue(ambi_roomsim_getReceiverZ(hAmbi, i), dontSendNotification);
    }
}
