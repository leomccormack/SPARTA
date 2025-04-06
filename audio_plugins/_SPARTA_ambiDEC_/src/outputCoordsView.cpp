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

    setSize (176, 400);

    setSize (sensorEdit_width, sensorEdit_height*currentNCH);
    hVst = ownerFilter;
    hAmbi = hVst->getFXHandle();
    maxNCH = _maxNCH ;
    currentNCH =_currentNCH;
    aziSliders =  new std::unique_ptr<Slider>[(unsigned long)maxNCH];
    elevSliders =  new std::unique_ptr<Slider>[(unsigned long)maxNCH];

    for( int i=0; i<maxNCH; i++){
        /* create and initialise azimuth sliders */
        aziSliders[i].reset (new Slider ("new slider"));
        addAndMakeVisible (aziSliders[i].get());
        aziSliders[i]->setRange (-360.0, 360.0, 0.001);
        aziSliders[i]->setValue(ambi_dec_getLoudspeakerAzi_deg(hAmbi, i));
        aziSliders[i]->setSliderStyle (Slider::LinearHorizontal);
        aziSliders[i]->setTextBoxStyle (Slider::TextBoxRight, false, 70, 20);
        aziSliders[i]->setBounds(-25, 8 + i*sensorEdit_height, 96, 16);
        aziSliders[i]->addListener (this);
        aziSliders[i]->setTooltip("Azimuth angle (in degrees) of loudspeaker No. " + String(i+1));

        /* create and initialise elevation sliders */
        elevSliders[i].reset (new Slider ("new slider"));
        addAndMakeVisible (elevSliders[i].get());
        elevSliders[i]->setRange (-180.0, 180.0, 0.001);
        elevSliders[i]->setValue(ambi_dec_getLoudspeakerElev_deg(hAmbi, i));
        elevSliders[i]->setSliderStyle (Slider::LinearHorizontal);
        elevSliders[i]->setTextBoxStyle (Slider::TextBoxLeft, false, 70, 20);
        elevSliders[i]->setBounds(105, 8 + i*sensorEdit_height, 96, 16);
        elevSliders[i]->addListener (this);
        elevSliders[i]->setTooltip("Elevation angle (in degrees) of loudspeaker No. " + String(i+1));
    }

    sliderHasChanged = true;

	refreshCoords();
	resized();
}

outputCoordsView::~outputCoordsView()
{
    dummySlider = nullptr;

    for( int i=0; i<maxNCH; i++){
        aziSliders[i] = nullptr;
        elevSliders[i] = nullptr;
    }
    delete [] aziSliders;
    delete [] elevSliders;
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

void outputCoordsView::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    for(int i=0; i<maxNCH; i++){
        if (sliderThatWasMoved == aziSliders[i].get()) {
            ambi_dec_setLoudspeakerAzi_deg(hAmbi, i, (float)aziSliders[i]->getValue());
            break;
        }
        if (sliderThatWasMoved == elevSliders[i].get()) {
            ambi_dec_setLoudspeakerElev_deg(hAmbi, i, (float)elevSliders[i]->getValue());
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
        aziSliders[i]->setRange (-360.0, 360.0, 0.001);
        aziSliders[i]->setValue(ambi_dec_getLoudspeakerAzi_deg(hAmbi, i), dontSendNotification);
        elevSliders[i]->setRange (-180.0, 180.0, 0.001);
        elevSliders[i]->setValue(ambi_dec_getLoudspeakerElev_deg(hAmbi, i), dontSendNotification);
    }
}
