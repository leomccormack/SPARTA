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

#include "PluginEditor.h"

#ifndef M_PI
#define M_PI ( 3.14159265358979323846264338327950288f )
#endif

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor(p), processor(p)
{
    s_ratio = std::make_unique<SliderWithAttachment>(p.parameters, "ratio");
    addAndMakeVisible (s_ratio.get());
    s_ratio->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_ratio->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_ratio->setBounds (168, 354, 64, 74);

    s_knee = std::make_unique<SliderWithAttachment>(p.parameters, "knee");
    addAndMakeVisible (s_knee.get());
    s_knee->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_knee->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_knee->setBounds (240, 354, 64, 74);

    s_attack = std::make_unique<SliderWithAttachment>(p.parameters, "attack_ms");
    addAndMakeVisible (s_attack.get());
    s_attack->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attack->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_attack->setBounds (319, 354, 64, 74);

    s_release = std::make_unique<SliderWithAttachment>(p.parameters, "release_ms");
    addAndMakeVisible (s_release.get());
    s_release->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_release->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_release->setBounds (391, 354, 64, 74);

    s_outgain = std::make_unique<SliderWithAttachment>(p.parameters, "outGain");
    addAndMakeVisible (s_outgain.get());
    s_outgain->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_outgain->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_outgain->setBounds (468, 354, 64, 74);

    presetCB = std::make_unique<ComboBoxWithAttachment>(p.parameters, "inputOrder");
    addAndMakeVisible (presetCB.get());
    presetCB->setEditableText (false);
    presetCB->setJustificationType (juce::Justification::centredLeft);
    presetCB->setBounds (72, 296, 120, 16);

    CHOrderingCB = std::make_unique<ComboBoxWithAttachment>(p.parameters, "channelOrder");
    addAndMakeVisible (CHOrderingCB.get());
    CHOrderingCB->setEditableText (false);
    CHOrderingCB->setJustificationType (juce::Justification::centredLeft);
    CHOrderingCB->setBounds (288, 296, 80, 16);

    normalisationCB = std::make_unique<ComboBoxWithAttachment>(p.parameters, "normType");
    addAndMakeVisible (normalisationCB.get());
    normalisationCB->setEditableText (false);
    normalisationCB->setJustificationType (juce::Justification::centredLeft);
    normalisationCB->setBounds (440, 296, 88, 16);

    s_ingain = std::make_unique<SliderWithAttachment>(p.parameters, "inGain");
    addAndMakeVisible (s_ingain.get());
    s_ingain->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_ingain->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_ingain->setBounds (16, 354, 64, 74);

    s_thresh = std::make_unique<SliderWithAttachment>(p.parameters, "threshold");
    addAndMakeVisible (s_thresh.get());
    s_thresh->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_thresh->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_thresh->setBounds (96, 354, 64, 74);

    setSize (550, 440);

    hAmbi = processor.getFXHandle();
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    setLookAndFeel(&LAF);

    /* Init TF view */
    TFviewIncluded.reset (new TFview(p, 430, 220, 100.0f, 20e3f, -60.0f, 0.0f));
    addAndMakeVisible (TFviewIncluded.get());
    TFviewIncluded->setAlwaysOnTop(true);
    TFviewIncluded->setTopLeftPosition(46, 44);
    TFviewIncluded->setVisible(true);
    int numFreqPoints;
    float* freqVector = ambi_drc_getFreqVector(hAmbi, &numFreqPoints);
    TFviewIncluded->setFreqVector(freqVector, numFreqPoints);

	/* fetch current configuration */
    CHOrderingCB->setSelectedId(ambi_drc_getChOrder(hAmbi), dontSendNotification);
    normalisationCB->setSelectedId(ambi_drc_getNormType(hAmbi), dontSendNotification);
    CHOrderingCB->setItemEnabled(CH_FUMA, ambi_drc_getInputPreset(hAmbi)==SH_ORDER_FIRST ? true : false);
    normalisationCB->setItemEnabled(NORM_FUMA, ambi_drc_getInputPreset(hAmbi)==SH_ORDER_FIRST ? true : false);

    /* tooltips */
    presetCB->setTooltip("The input/output order. Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals. The plug-in derives the frequency-dependent gain factors based on the omni-directional component, which are then applied to all input signals equally. The spatial properties of the original signals will remain unchanged, although your perception of them after decoding may change.");
    CHOrderingCB->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    normalisationCB->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    s_thresh->setTooltip("Compressor threshold (in dB).");
    s_ratio->setTooltip("Compression ratio (X:1).");
    s_knee->setTooltip("Compressor knee (in dB). Hard-knee: when set to 0; soft-knee: when set to more than 0.");
    s_ingain->setTooltip("Input gain (in dB).");
    s_outgain->setTooltip("Output/Make-up gain (in dB).");
    s_attack->setTooltip("Envelope attack time (in miliseconds).");
    s_release->setTooltip("Envelope release time (in miliseconds).");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("This plug-in is a frequency-dependent Ambisonic dynamic range compressor (DRC). The gain factors are derived by analysing the omnidirectional component for each frequency band, which are then applied to all of the input signals equally. The spatial properties of the original signals will remain unchanged, although your perception of them after decoding may change."));

    /* Specify screen refresh rate */
    startTimer(80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    s_ratio = nullptr;
    s_knee = nullptr;
    s_attack = nullptr;
    s_release = nullptr;
    s_outgain = nullptr;
    presetCB = nullptr;
    CHOrderingCB = nullptr;
    normalisationCB = nullptr;
    s_ingain = nullptr;
    s_thresh = nullptr;

    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 235, width = 550, height = 205;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             440.0f - 235.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             360.0f - 235.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 30, width = 550, height = 205;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             104.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 548.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             616.0f - 1.0f + x,
                                             24.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 10, y = 38, width = 530, height = 244;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 88, y = 320, width = 224, height = 112;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 96, y = 325, width = 60, height = 30;
        juce::String text (TRANS("Thresh."));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 169, y = 326, width = 60, height = 30;
        juce::String text (TRANS("Ratio"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 241, y = 326, width = 60, height = 30;
        juce::String text (TRANS("Knee"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 311, y = 320, width = 151, height = 112;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 461, y = 320, width = 79, height = 112;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 321, y = 326, width = 60, height = 30;
        juce::String text (TRANS("Attack"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 393, y = 326, width = 60, height = 30;
        juce::String text (TRANS("Release"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 470, y = 326, width = 60, height = 30;
        juce::String text (TRANS("Out Gain"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 10, y = 320, width = 79, height = 112;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 19, y = 326, width = 60, height = 30;
        juce::String text (TRANS("In Gain"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 10, y = 288, width = 530, height = 33;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 214, y = 289, width = 172, height = 30;
        juce::String text (TRANS("CH Order:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 390, y = 289, width = 58, height = 30;
        juce::String text (TRANS("Norm:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 289, width = 50, height = 30;
        juce::String text (TRANS("Input:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 246, y = 257, width = 58, height = 30;
        juce::String text (TRANS("Time (s)"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 246, width = 26, height = 30;
        juce::String text (TRANS("100"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 28, y = 153, width = 26, height = 30;
        juce::String text (TRANS("1k"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 28, y = 86, width = 26, height = 30;
        juce::String text (TRANS("5k"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 57, width = 26, height = 30;
        juce::String text (TRANS("10k"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 31, width = 26, height = 30;
        juce::String text (TRANS("20k"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 508, y = 31, width = 26, height = 30;
        juce::String text (TRANS("0"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 500, y = 247, width = 26, height = 30;
        juce::String text (TRANS("-16"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 85, width = 26, height = 30;
        juce::String text (TRANS("-4"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 193, width = 26, height = 30;
        juce::String text (TRANS("-12"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 219, width = 26, height = 30;
        juce::String text (TRANS("200"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 139, width = 26, height = 30;
        juce::String text (TRANS("-8"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 58, width = 26, height = 30;
        juce::String text (TRANS("-2"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 112, width = 26, height = 30;
        juce::String text (TRANS("-6"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 166, width = 26, height = 30;
        juce::String text (TRANS("-10"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 220, width = 26, height = 30;
        juce::String text (TRANS("-14"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 10, y = 288, width = 193, height = 33;
        juce::Colour fillColour = juce::Colour (0x08c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 16, y = 1, width = 100, height = 32;
        juce::String text (TRANS("SPARTA|"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.80f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 92, y = 1, width = 112, height = 32;
        juce::String text (TRANS("AmbiDRC"));
        juce::Colour fillColour = juce::Colour (0xfff77bf5);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 550, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 440;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 548, y = 0, width = 2, height = 440;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 438, width = 550, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    /* banner text */
	g.setColour(Colours::white);
	g.setFont(juce::FontOptions (11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
        185, 16, 530, 11,
        Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    g.setOpacity(1.0f);
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(ambi_drc_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(ambi_drc_getSamplerate(hAmbi)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(ambi_drc_getNSHrequired(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
                       TRANS("/") + String(ambi_drc_getNSHrequired(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
    }

    /* draw colour bar */
    int colourbarWidth = 16;
    g.setOpacity(1.0f);
    Rectangle<int> TFviewBounds = TFviewIncluded->getBounds();
    for(int i=0; i<mapColourTable_N; i++){
        g.setColour(mapColourTable[i]);
        g.fillRect((float)TFviewBounds.getTopRight().x+5.0f,
                   (float)TFviewBounds.getTopRight().y + (float)i*(float)TFviewBounds.getHeight()/(float)mapColourTable_N,
                   (float)colourbarWidth,
                   (float)TFviewBounds.getHeight()/(float)mapColourTable_N);
    }
    g.setColour(Colours::white);
    g.drawRect(TFviewBounds.getTopRight().x+5, TFviewBounds.getTopRight().y, colourbarWidth, TFviewBounds.getHeight(), 1);

    /* axis labels */
    g.setColour(Colours::white);
    int textWidth = 105;
    g.addTransform(AffineTransform::rotation(-M_PI/2.0f).followedBy(AffineTransform::translation(-(TFviewIncluded->getHeight()/2 - (int)((float)textWidth/2.5f)),
                                                                                              TFviewIncluded->getHeight() - textWidth/2)));
    g.setFont (juce::FontOptions (12.00f, Font::plain).withStyle ("Bold"));
    g.drawText(TRANS("Frequency (Hz)"), -36,
               (int) ((float)TFviewIncluded->getHeight()/2.0f) - textWidth/2,
               textWidth, 57, Justification::centred);

	textWidth = 118;
    g.drawText(TRANS("Gain Reduction (dB)"), -36,
               (int) ((float)TFviewIncluded->getHeight()/2.0f) - textWidth/2,
               textWidth, 1084, Justification::centred);

    g.addTransform(AffineTransform());
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
    CHOrderingCB->setSelectedId(ambi_drc_getChOrder(hAmbi), sendNotification);
    normalisationCB->setSelectedId(ambi_drc_getNormType(hAmbi), sendNotification);
    CHOrderingCB->setItemEnabled(CH_FUMA, ambi_drc_getInputPreset(hAmbi)==SH_ORDER_FIRST ? true : false);
    normalisationCB->setItemEnabled(NORM_FUMA, ambi_drc_getInputPreset(hAmbi)==SH_ORDER_FIRST ? true : false);

    if (processor.getIsPlaying()) {
        int wIdx = ambi_drc_getGainTFwIdx(hAmbi);
        float linePos = (float)wIdx*((float)TFviewIncluded->getWidth() / (float)AMBI_DRC_NUM_DISPLAY_TIME_SLOTS);
        TFviewIncluded->repaint((int)linePos-10, 0, TFviewIncluded->getWidth(), TFviewIncluded->getHeight());
    }

    /* display warning message, if needed */
    if ((processor.getCurrentBlockSize() % ambi_drc_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ( !((ambi_drc_getSamplerate(hAmbi) == 44.1e3) || (ambi_drc_getSamplerate(hAmbi) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumInputs() < ambi_drc_getNSHrequired(hAmbi))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumOutputs() < ambi_drc_getNSHrequired(hAmbi))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}
