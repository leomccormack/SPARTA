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

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor(p), processor(p)
{
    s_yaw = std::make_unique<SliderWithAttachment>(p.parameters, "yaw");
    addAndMakeVisible (s_yaw.get());
    s_yaw->setSliderStyle (juce::Slider::LinearHorizontal);
    s_yaw->setTextBoxStyle (juce::Slider::TextBoxAbove, false, 80, 20);
    s_yaw->setBounds (176, 80, 120, 32);

    s_pitch = std::make_unique<SliderWithAttachment>(p.parameters, "pitch");
    addAndMakeVisible (s_pitch.get());
    s_pitch->setSliderStyle (juce::Slider::LinearVertical);
    s_pitch->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);
    s_pitch->setBounds (304, 40, 96, 112);

    s_roll = std::make_unique<SliderWithAttachment>(p.parameters, "roll");
    addAndMakeVisible (s_roll.get());
    s_roll->setSliderStyle (juce::Slider::LinearVertical);
    s_roll->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);
    s_roll->setBounds (416, 40, 96, 112);

    t_flipYaw = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipYaw");
    addAndMakeVisible (t_flipYaw.get());
    t_flipYaw->setBounds (225, 112, 23, 24);

    t_flipPitch = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipPitch");
    addAndMakeVisible (t_flipPitch.get());
    t_flipPitch->setBounds (356, 112, 23, 24);

    t_flipRoll = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipRoll");
    addAndMakeVisible (t_flipRoll.get());
    t_flipRoll->setBounds (468, 112, 23, 24);

    te_oscport.reset (new juce::TextEditor ("new text editor"));
    addAndMakeVisible (te_oscport.get());
    te_oscport->setMultiLine (false);
    te_oscport->setReturnKeyStartsNewLine (false);
    te_oscport->setReadOnly (false);
    te_oscport->setScrollbarsShown (true);
    te_oscport->setCaretVisible (false);
    te_oscport->setPopupMenuEnabled (true);
    te_oscport->setText (TRANS("9000"));
    te_oscport->setBounds (66, 131, 42, 18);

    CBoutputFormat = std::make_unique<ComboBoxWithAttachment>(p.parameters, "channelOrder");
    addAndMakeVisible (CBoutputFormat.get());
    CBoutputFormat->setEditableText (false);
    CBoutputFormat->setJustificationType (juce::Justification::centredLeft);
    CBoutputFormat->setBounds (94, 78, 76, 20);

    CBnorm = std::make_unique<ComboBoxWithAttachment>(p.parameters, "normType");
    addAndMakeVisible (CBnorm.get());
    CBnorm->setEditableText (false);
    CBnorm->setJustificationType (juce::Justification::centredLeft);
    CBnorm->setBounds (94, 105, 76, 20);

    CBorder = std::make_unique<ComboBoxWithAttachment>(p.parameters, "inputOrder");
    addAndMakeVisible (CBorder.get());
    CBorder->setEditableText (false);
    CBorder->setJustificationType (juce::Justification::centredLeft);
    CBorder->setBounds (65, 46, 106, 20);

    TBrpyFlag = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "useRollPitchYaw");
    addAndMakeVisible (TBrpyFlag.get());
    TBrpyFlag->setButtonText (juce::String());
    TBrpyFlag->setBounds (145, 128, 32, 24);

    setSize (530, 160);

    hRot = processor.getFXHandle();

    /* Look and Feel */
    setLookAndFeel(&LAF);

    /* fetch current configuration */
    CBnorm->setSelectedId(rotator_getNormType(hRot), dontSendNotification);
    CBoutputFormat->setSelectedId(rotator_getChOrder(hRot), dontSendNotification);
    te_oscport->setText(String(processor.getOscPortID()), dontSendNotification);
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
    stopTimer();
    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    using namespace ColoursUI;

    drawPluginBackgroundAndBanner(g, getBounds());

    /* Panels */
    drawPanel(g, {10, 40,167,32}, panelFill,      panelStrokeLight);
    drawPanel(g, {10, 71,167,57}, panelFill,      panelStrokeLight);
    drawPanel(g, {10,127,167,25}, panelFill,      panelStrokeLight);
    drawPanel(g, {176,40,344,112}, panelFill,     panelStrokeLight);

    /* Labels: left column */
    drawLabel(g, {16, 39,91,35}, "Order:", 15.f);
    drawLabel(g, {16, 71,91,35}, "CH Format:", 14.5f);
    drawLabel(g, {16, 96,91,35}, "Norm:", 14.5f);
    drawLabel(g, {16,123,91,35}, "OSC port:", 11.f);

    /* Labels: R-P-Y block */
    drawLabel(g, {96,123,63,35}, "R-P-Y:", 11.f, juce::Justification::centred);
    drawLabel(g, {189,45,60,30}, "Yaw",   15.f, juce::Justification::centred);
    drawLabel(g, {221,45,63,30}, "\\ypr[0]", 11.f, juce::Justification::centred);
    drawLabel(g, {319,45,63,30}, "Pitch", 15.f, juce::Justification::centred);
    drawLabel(g, {357,45,63,30}, "\\ypr[1]", 11.f, juce::Justification::centred);
    drawLabel(g, {429,45,63,30}, "Roll",  15.f, juce::Justification::centred);
    drawLabel(g, {461,45,63,30}, "\\ypr[2]", 11.f, juce::Justification::centred);

    /* +/- row */
    drawLabel(g, {205,125,63,30}, "+/-", 15.f, juce::Justification::centred);
    drawLabel(g, {336,125,63,30}, "+/-", 15.f, juce::Justification::centred);
    drawLabel(g, {448,125,63,30}, "+/-", 15.f, juce::Justification::centred);

    /* Title */
    drawLabel(g, {16,1,100,32}, "SPARTA|", 18.f);
    drawLabel(g, {92,1,112,32}, "Rotator", 18.f, juce::Justification::centredLeft, juce::Colour(0xff86fbff));

    /* display version/date built */
    g.setColour(Colours::white);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
        175, 16, 530, 11,
        Justification::centredLeft, true);

    /* display warning message */
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_NinputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(rotator_getNSHrequired(hRot)) + TRANS(")"),
                       getBounds().getWidth()-225, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
                       TRANS("/") + String(rotator_getNSHrequired(hRot)) + TRANS(")"),
                       getBounds().getWidth()-225, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_osc_connection_fail:
            g.setColour(Colours::red);
            g.drawText(TRANS("OSC failed to connect, or port is already taken"),
                       getBounds().getWidth()-225, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_frameSize:
            g.setColour(Colours::yellow);
            g.drawText(TRANS("Set host block size to \"") + String(rotator_getFrameSize()) + TRANS("\" for lowest latency"),
                       getBounds().getWidth()-225, 5, 530, 11,
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

void PluginEditor::buttonClicked (juce::Button* /*buttonThatWasClicked*/)
{
}

void PluginEditor::comboBoxChanged (juce::ComboBox* /*comboBoxThatHasChanged*/)
{
}

void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    CBnorm->setSelectedId(rotator_getNormType(hRot), sendNotification);
    CBoutputFormat->setSelectedId(rotator_getChOrder(hRot), sendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, rotator_getOrder(hRot)==SH_ORDER_FIRST ? true : false);
    CBnorm->setItemEnabled(NORM_FUMA, rotator_getOrder(hRot)==SH_ORDER_FIRST ? true : false);

    /* display warning message, if needed */
    if ((processor.getCurrentNumInputs() < rotator_getNSHrequired(hRot))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumOutputs() < rotator_getNSHrequired(hRot))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(!processor.getOscPortConnected()){
        currentWarning = k_warning_osc_connection_fail;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentBlockSize() != rotator_getFrameSize())){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }

    /* check if OSC port has changed */
    if(processor.getOscPortID() != te_oscport->getText().getIntValue())
        processor.setOscPortID(te_oscport->getText().getIntValue());
}
