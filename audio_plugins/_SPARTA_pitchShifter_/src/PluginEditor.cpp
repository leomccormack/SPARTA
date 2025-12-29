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
    s_pitchShiftFactor->setBounds (360, 40, 120, 32);

    SL_num_channels = std::make_unique<SliderWithAttachment>(p.parameters, "numChannels");
    addAndMakeVisible (SL_num_channels.get());
    SL_num_channels->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_channels->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_channels->setBounds (163, 47, 48, 20);

    CBfftsize  = std::make_unique<ComboBoxWithAttachment>(p.parameters, "fftOption");
    addAndMakeVisible (CBfftsize.get());
    CBfftsize->setEditableText (false);
    CBfftsize->setJustificationType (juce::Justification::centredLeft);
    CBfftsize->setBounds (98, 78, 112, 19);

    CBoversampling = std::make_unique<ComboBoxWithAttachment>(p.parameters, "oSampOption");
    addAndMakeVisible (CBoversampling.get());
    CBoversampling->setEditableText (false);
    CBoversampling->setJustificationType (juce::Justification::centredLeft);
    CBoversampling->setBounds (361, 78, 112, 19);

    setSize (500, 112);

    hPS = processor.getFXHandle();

    /* Look and Feel */
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
    startTimer(40);

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    stopTimer();
    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    using namespace ColoursUI;

    drawPluginBackgroundAndBanner(g, getBounds());

    /* Panels */
    drawPanel(g, {10, 71,476,33}, panelFill,      panelStrokeLight);
    drawPanel(g, {10, 40,213,32}, panelFill,      panelStrokeLight);
    drawPanel(g, {222,40,264,32}, panelFill,      panelStrokeLight);

    /* Labels */
    drawLabel(g, {16, 41,152,30}, "Number of Channels:", 15.f);
    drawLabel(g, {218,41,139,30}, "Pitch Shift Factor:", 15.f, juce::Justification::centred);

    drawLabel(g, {15, 71,96,35}, "FFT Size:",       15.f);
    drawLabel(g, {230,71,96,35}, "Oversampling:",   15.f);

    /* Title */
    drawLabel(g, {16,1,100,32}, "SPARTA|", 18.8f);
    drawLabel(g, {92,1,124,32}, "PitchShifter", 18.f, juce::Justification::centredLeft, juce::Colour(0xff8dff86));

    /* display version/date built */
    g.setColour(Colours::white);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
        190, 16, 530, 11,
        Justification::centredLeft, true);

    /* display warning message */
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_NCH:
            g.setColour(Colours::red);
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

void PluginEditor::timerCallback()
{
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
