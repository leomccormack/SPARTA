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

PluginEditor::PluginEditor (PluginProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    s_yaw.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_yaw.get());
    s_yaw->setRange (-180, 180, 0.01);
    s_yaw->setSliderStyle (juce::Slider::LinearHorizontal);
    s_yaw->setTextBoxStyle (juce::Slider::TextBoxAbove, false, 80, 20);
    s_yaw->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_yaw->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6e));
    s_yaw->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_yaw->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_yaw->addListener (this);

    s_yaw->setBounds (176, 80, 120, 32);

    s_pitch.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_pitch.get());
    s_pitch->setRange (-180, 180, 0.01);
    s_pitch->setSliderStyle (juce::Slider::LinearVertical);
    s_pitch->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);
    s_pitch->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_pitch->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    s_pitch->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_pitch->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_pitch->addListener (this);

    s_pitch->setBounds (304, 40, 96, 112);

    s_roll.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_roll.get());
    s_roll->setRange (-180, 180, 0.01);
    s_roll->setSliderStyle (juce::Slider::LinearVertical);
    s_roll->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);
    s_roll->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_roll->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    s_roll->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_roll->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_roll->addListener (this);

    s_roll->setBounds (416, 40, 96, 112);

    t_flipYaw.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipYaw.get());
    t_flipYaw->setButtonText (juce::String());
    t_flipYaw->addListener (this);

    t_flipYaw->setBounds (225, 112, 23, 24);

    t_flipPitch.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipPitch.get());
    t_flipPitch->setButtonText (juce::String());
    t_flipPitch->addListener (this);

    t_flipPitch->setBounds (356, 112, 23, 24);

    t_flipRoll.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipRoll.get());
    t_flipRoll->setButtonText (juce::String());
    t_flipRoll->addListener (this);

    t_flipRoll->setBounds (468, 112, 23, 24);

    te_oscport.reset (new juce::TextEditor ("new text editor"));
    addAndMakeVisible (te_oscport.get());
    te_oscport->setMultiLine (false);
    te_oscport->setReturnKeyStartsNewLine (false);
    te_oscport->setReadOnly (false);
    te_oscport->setScrollbarsShown (true);
    te_oscport->setCaretVisible (false);
    te_oscport->setPopupMenuEnabled (true);
    te_oscport->setColour (juce::TextEditor::textColourId, juce::Colours::white);
    te_oscport->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00ffffff));
    te_oscport->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x6c838080));
    te_oscport->setText (TRANS("9000"));

    te_oscport->setBounds (66, 128, 42, 22);

    CBoutputFormat.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBoutputFormat.get());
    CBoutputFormat->setEditableText (false);
    CBoutputFormat->setJustificationType (juce::Justification::centredLeft);
    CBoutputFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBoutputFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBoutputFormat->addListener (this);

    CBoutputFormat->setBounds (94, 78, 76, 20);

    CBnorm.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBnorm.get());
    CBnorm->setEditableText (false);
    CBnorm->setJustificationType (juce::Justification::centredLeft);
    CBnorm->setTextWhenNothingSelected (TRANS("N3D"));
    CBnorm->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnorm->addListener (this);

    CBnorm->setBounds (94, 105, 76, 20);

    CBorder.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBorder.get());
    CBorder->setEditableText (false);
    CBorder->setJustificationType (juce::Justification::centredLeft);
    CBorder->setTextWhenNothingSelected (juce::String());
    CBorder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBorder->addListener (this);

    CBorder->setBounds (65, 46, 106, 20);

    TBrpyFlag.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBrpyFlag.get());
    TBrpyFlag->setButtonText (juce::String());
    TBrpyFlag->addListener (this);

    TBrpyFlag->setBounds (145, 128, 32, 24);

    setSize (530, 160);

	hVst = ownerFilter;
    hRot = hVst->getFXHandle();

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* add combo box options */
    CBorder->addItem (TRANS("1st order"), SH_ORDER_FIRST);
    CBorder->addItem (TRANS("2nd order"), SH_ORDER_SECOND);
    CBorder->addItem (TRANS("3rd order"), SH_ORDER_THIRD);
    CBorder->addItem (TRANS("4th order"), SH_ORDER_FOURTH);
    CBorder->addItem (TRANS("5th order"), SH_ORDER_FIFTH);
    CBorder->addItem (TRANS("6th order"), SH_ORDER_SIXTH);
    CBorder->addItem (TRANS("7th order"), SH_ORDER_SEVENTH);
    CBorder->addItem (TRANS("8th order"), SH_ORDER_EIGHTH);
    CBorder->addItem (TRANS("9th order"), SH_ORDER_NINTH);
    CBorder->addItem (TRANS("10th order"), SH_ORDER_TENTH);
    CBoutputFormat->addItem (TRANS("ACN"), CH_ACN);
    CBoutputFormat->addItem (TRANS("FuMa"), CH_FUMA);
    CBnorm->addItem (TRANS("N3D"), NORM_N3D);
    CBnorm->addItem (TRANS("SN3D"), NORM_SN3D);
    CBnorm->addItem (TRANS("FuMa"), NORM_FUMA);

	/* fetch current configuration */
	s_yaw->setValue(rotator_getYaw(hRot), dontSendNotification);
    s_pitch->setValue(rotator_getPitch(hRot), dontSendNotification);
    s_roll->setValue(rotator_getRoll(hRot), dontSendNotification);
    t_flipYaw->setToggleState((bool)rotator_getFlipYaw(hRot), dontSendNotification);
    t_flipPitch->setToggleState((bool)rotator_getFlipPitch(hRot), dontSendNotification);
    t_flipRoll->setToggleState((bool)rotator_getFlipRoll(hRot), dontSendNotification);
    CBnorm->setSelectedId(rotator_getNormType(hRot), dontSendNotification);
    CBoutputFormat->setSelectedId(rotator_getChOrder(hRot), dontSendNotification);
    CBorder->setSelectedId(rotator_getOrder(hRot), dontSendNotification);
    te_oscport->setText(String(hVst->getOscPortID()), dontSendNotification);
    TBrpyFlag->setToggleState((bool)rotator_getRPYflag(hRot), dontSendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, rotator_getOrder(hRot)==SH_ORDER_FIRST ? true : false);
    CBnorm->setItemEnabled(NORM_FUMA, rotator_getOrder(hRot)==SH_ORDER_FIRST ? true : false);

    /* tooltips */
    CBorder->setTooltip("Input/output order. Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals as input.");
    CBoutputFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnorm->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    s_yaw->setTooltip("Sets the 'Yaw' rotation angle (in degrees).");
    s_pitch->setTooltip("Sets the 'Pitch' rotation angle (in degrees).");
    s_roll->setTooltip("Sets the 'Roll' rotation angle (in degrees).");
    t_flipYaw->setTooltip("Flips the sign (+/-) of the 'Yaw' rotation angle.");
    t_flipPitch->setTooltip("Flips the sign (+/-) of the 'Pitch' rotation angle.");
    t_flipRoll->setTooltip("Flips the sign (+/-) of the 'Roll' rotation angle.");
    te_oscport->setTooltip("The OSC port at which to receive the rotation angles. To facilitate head-tracking, send the rotation angles (in degrees) to this port ID as a 3-element vector 'ypr[3]', following the yaw-pitch-roll convention.");
    TBrpyFlag->setTooltip("If enabled, the plug-in will use the roll-pitch-yaw rotation order convention. If disabled, it will use the yaw-pitch-roll convention.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A simple plugin for rotating Ambisonic signals. The rotation angles can be controlled using a head tracker via OSC messages, by configuring the headtracker to send a vector: '\\ypr[3]' to OSC port 9000 (default); where \\ypr[0], \\ypr[1], \\ypr[2] are the yaw-pitch-roll angles, respectively. The angles can also be flipped +/- in order to support a wider range of devices. The rotation order (yaw-pitch-roll (default) or roll-pitch-yaw) can also be specified."));

    /* Specify screen refresh rate */
    startTimer(20); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    s_yaw = nullptr;
    s_pitch = nullptr;
    s_roll = nullptr;
    t_flipYaw = nullptr;
    t_flipPitch = nullptr;
    t_flipRoll = nullptr;
    te_oscport = nullptr;
    CBoutputFormat = nullptr;
    CBnorm = nullptr;
    CBorder = nullptr;
    TBrpyFlag = nullptr;

    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 95, width = 530, height = 65;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             160.0f - 95.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             112.0f - 95.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 30, width = 530, height = 65;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             80.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 528.0f, height = 31.0f;
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
        int x = 10, y = 127, width = 167, height = 25;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 10, y = 40, width = 167, height = 32;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 10, y = 71, width = 167, height = 57;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 176, y = 40, width = 344, height = 112;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 221, y = 45, width = 63, height = 30;
        juce::String text (TRANS("\\ypr[0]"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 319, y = 45, width = 63, height = 30;
        juce::String text (TRANS("Pitch"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 429, y = 45, width = 63, height = 30;
        juce::String text (TRANS("Roll"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 448, y = 125, width = 63, height = 30;
        juce::String text (TRANS("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 336, y = 125, width = 63, height = 30;
        juce::String text (TRANS("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 205, y = 125, width = 63, height = 30;
        juce::String text (TRANS("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 16, y = 123, width = 91, height = 35;
        juce::String text (TRANS("OSC port:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 189, y = 45, width = 60, height = 30;
        juce::String text (TRANS("Yaw"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 357, y = 45, width = 63, height = 30;
        juce::String text (TRANS("\\ypr[1]"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 461, y = 45, width = 63, height = 30;
        juce::String text (TRANS("\\ypr[2]"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 16, y = 71, width = 91, height = 35;
        juce::String text (TRANS("CH Format:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 96, width = 91, height = 35;
        juce::String text (TRANS("Norm:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 39, width = 91, height = 35;
        juce::String text (TRANS("Order:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 96, y = 123, width = 63, height = 35;
        juce::String text (TRANS("R-P-Y:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
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
        juce::String text (TRANS("Rotator"));
        juce::Colour fillColour = juce::Colour (0xff86fbff);
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
        int x = 0, y = 0, width = 2, height = 160;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 528, y = 0, width = 2, height = 160;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 158, width = 532, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    /* display version/date built */
	g.setColour(Colours::white);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		175, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(rotator_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(rotator_getNSHrequired(hRot)) + TRANS(")"),
                       getBounds().getWidth()-225, 6, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(rotator_getNSHrequired(hRot)) + TRANS(")"),
                       getBounds().getWidth()-225, 6, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_osc_connection_fail:
            g.drawText(TRANS("OSC failed to connect, or port is already taken"),
                       getBounds().getWidth()-225, 6, 530, 11,
                       Justification::centredLeft, true);
            break;
    }
}

void PluginEditor::resized()
{
	repaint();
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == s_yaw.get())
    {
        rotator_setYaw(hRot, (float)s_yaw->getValue());
    }
    else if (sliderThatWasMoved == s_pitch.get())
    {
        rotator_setPitch(hRot, (float)s_pitch->getValue());
    }
    else if (sliderThatWasMoved == s_roll.get())
    {
        rotator_setRoll(hRot, (float)s_roll->getValue());
    }
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == t_flipYaw.get())
    {
        rotator_setFlipYaw(hRot, (int)t_flipYaw->getToggleState());
    }
    else if (buttonThatWasClicked == t_flipPitch.get())
    {
        rotator_setFlipPitch(hRot, (int)t_flipPitch->getToggleState());
    }
    else if (buttonThatWasClicked == t_flipRoll.get())
    {
        rotator_setFlipRoll(hRot, (int)t_flipRoll->getToggleState());
    }
    else if (buttonThatWasClicked == TBrpyFlag.get())
    {
        rotator_setRPYflag(hRot, (int)TBrpyFlag->getToggleState());
    }
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == CBoutputFormat.get())
    {
        rotator_setChOrder(hRot, CBoutputFormat->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBnorm.get())
    {
        rotator_setNormType(hRot, CBnorm->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBorder.get())
    {
        rotator_setOrder(hRot, CBorder->getSelectedId());
    }
}

void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    s_yaw->setValue(rotator_getYaw(hRot), dontSendNotification);
    s_pitch->setValue(rotator_getPitch(hRot), dontSendNotification);
    s_roll->setValue(rotator_getRoll(hRot), dontSendNotification);
    CBoutputFormat->setSelectedId(rotator_getChOrder(hRot), dontSendNotification);
    CBnorm->setSelectedId(rotator_getNormType(hRot), dontSendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, rotator_getOrder(hRot)==SH_ORDER_FIRST ? true : false);
    CBnorm->setItemEnabled(NORM_FUMA, rotator_getOrder(hRot)==SH_ORDER_FIRST ? true : false);

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % rotator_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < rotator_getNSHrequired(hRot))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumOutputs() < rotator_getNSHrequired(hRot))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(!hVst->getOscPortConnected()){
        currentWarning = k_warning_osc_connection_fail;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }

    /* check if OSC port has changed */
    if(hVst->getOscPortID() != te_oscport->getText().getIntValue())
        hVst->setOscPortID(te_oscport->getText().getIntValue());
}
