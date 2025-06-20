/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2020 - Leo McCormack.
 
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

#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor(p), processor(p), progressbar(progress)
{
    s_pitchShiftFactor = std::make_unique<SliderWithAttachment>(p.parameters, "pitchShiftFactor");
    addAndMakeVisible (s_pitchShiftFactor.get());
    s_pitchShiftFactor->setSliderStyle (juce::Slider::LinearHorizontal);
    s_pitchShiftFactor->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    s_pitchShiftFactor->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_pitchShiftFactor->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6e));
    s_pitchShiftFactor->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_pitchShiftFactor->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_pitchShiftFactor->addListener (this);

    s_pitchShiftFactor->setBounds (360, 40, 120, 32);

    SL_num_channels = std::make_unique<SliderWithAttachment>(p.parameters, "numChannels");
    addAndMakeVisible (SL_num_channels.get());
    SL_num_channels->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_channels->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_channels->addListener (this);

    SL_num_channels->setBounds (163, 47, 48, 20);

    CBfftsize  = std::make_unique<ComboBoxWithAttachment>(p.parameters, "fftOption");
    addAndMakeVisible (CBfftsize.get());
    CBfftsize->setEditableText (false);
    CBfftsize->setJustificationType (juce::Justification::centredLeft);
    CBfftsize->setTextWhenNothingSelected (juce::String());
    CBfftsize->addListener (this);

    CBfftsize->setBounds (98, 78, 112, 19);

    CBoversampling = std::make_unique<ComboBoxWithAttachment>(p.parameters, "oSampOption");
    addAndMakeVisible (CBoversampling.get());
    CBoversampling->setEditableText (false);
    CBoversampling->setJustificationType (juce::Justification::centredLeft);
    CBoversampling->setTextWhenNothingSelected (juce::String());
    CBoversampling->addListener (this);

    CBoversampling->setBounds (361, 78, 112, 19);

    setSize (500, 112);

    hPS = processor.getFXHandle();

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_num_channels->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_channels->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_channels->setSliderSnapsToMousePosition(false);

    /* tooltips */
    s_pitchShiftFactor->setTooltip("Pitch shift factor, 1: no change, 0.5: down one octave, 2: up one octave");
    CBfftsize->setTooltip("FFT size used by the algorithm. Higher values permit more drastic pitch shifts, but at the cost of increased CPU and latency");
    CBoversampling->setTooltip("Oversampling factor used by the algorithm. Higher values improve signal fidelity, but at the cost of increased CPU and latency");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A simple multi-channel pitch shifter, based on the phase-vocoder approach."));

    /* Specify screen refresh rate */
    startTimer(TIMER_GUI_RELATED, 40);

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    s_pitchShiftFactor = nullptr;
    SL_num_channels = nullptr;
    CBfftsize = nullptr;
    CBoversampling = nullptr;

    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 70, width = 498, height = 42;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             120.0f - 70.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             96.0f - 70.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 10, y = 71, width = 476, height = 33;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 0, y = 30, width = 530, height = 40;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             56.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 498.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             528.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 10, y = 40, width = 213, height = 32;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 222, y = 40, width = 264, height = 32;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 218, y = 41, width = 139, height = 30;
        juce::String text (TRANS ("Pitch Shift Factor:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 16, y = 41, width = 152, height = 30;
        juce::String text (TRANS ("Number of Channels:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 1, width = 100, height = 32;
        juce::String text (TRANS ("SPARTA|"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.80f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 92, y = 1, width = 124, height = 32;
        juce::String text (TRANS ("PitchShifter"));
        juce::Colour fillColour = juce::Colour (0xff8dff86);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 532, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 120;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 498, y = 3, width = 6, height = 117;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 110, width = 512, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 15, y = 71, width = 96, height = 35;
        juce::String text (TRANS ("FFT Size:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 230, y = 71, width = 96, height = 35;
        juce::String text (TRANS ("Oversampling:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    /* display version/date built */
	g.setColour(Colours::white);
	g.setFont(juce::FontOptions (11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		190, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_NCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(pitch_shifter_getNCHrequired(hPS)) + TRANS(")"),
                       getBounds().getWidth()-225, 6, 530, 11,
                       Justification::centredLeft, true);
            break;
    }
}

void PluginEditor::resized()
{
	repaint();
}

void PluginEditor::sliderValueChanged (juce::Slider* /*sliderThatWasMoved*/)
{
}

void PluginEditor::comboBoxChanged (juce::ComboBox* /*comboBoxThatHasChanged*/)
{
}

void PluginEditor::timerCallback(int timerID)
{
    switch(timerID){
        case TIMER_PROCESSING_RELATED:
            /* handled in PluginProcessor */
            break;

        case TIMER_GUI_RELATED:
            /* parameters whos values can change internally should be periodically refreshed */

            /* Progress bar */
            if(pitch_shifter_getCodecStatus(hPS)==CODEC_STATUS_INITIALISING){
                addAndMakeVisible(progressbar);
                progress = (double)pitch_shifter_getProgressBar0_1(hPS);
                char text[PROGRESSBARTEXT_CHAR_LENGTH];
                pitch_shifter_getProgressBarText(hPS, (char*)text);
                progressbar.setTextToDisplay(String(text));
            }
            else
                removeChildComponent(&progressbar);

            /* display warning message, if needed */
            if ((processor.getCurrentNumInputs() < pitch_shifter_getNCHrequired(hPS))){
                currentWarning = k_warning_NCH;
                repaint(0,0,getWidth(),32);
            }
    }
}
