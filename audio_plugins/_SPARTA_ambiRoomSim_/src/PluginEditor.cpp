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
    SL_num_sources = std::make_unique<SliderWithAttachment>(p.parameters, "numSources");
    addAndMakeVisible (SL_num_sources.get());
    SL_num_sources->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_sources->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_sources->addListener (this);

    SL_num_sources->setBounds (173, 303, 48, 20);

    CBoutputFormat = std::make_unique<ComboBoxWithAttachment>(p.parameters, "channelOrder");
    addAndMakeVisible (CBoutputFormat.get());
    CBoutputFormat->setEditableText (false);
    CBoutputFormat->setJustificationType (juce::Justification::centredLeft);
    CBoutputFormat->setTextWhenNothingSelected (TRANS ("ACN"));
    CBoutputFormat->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBoutputFormat->addListener (this);

    CBoutputFormat->setBounds (316, 247, 76, 20);

    CBnormalisation = std::make_unique<ComboBoxWithAttachment>(p.parameters, "normType");
    addAndMakeVisible (CBnormalisation.get());
    CBnormalisation->setEditableText (false);
    CBnormalisation->setJustificationType (juce::Justification::centredLeft);
    CBnormalisation->setTextWhenNothingSelected (TRANS ("N3D"));
    CBnormalisation->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBnormalisation->addListener (this);

    CBnormalisation->setBounds (398, 247, 76, 20);

    CBorder = std::make_unique<ComboBoxWithAttachment>(p.parameters, "outputOrder");
    addAndMakeVisible (CBorder.get());
    CBorder->setEditableText (false);
    CBorder->setJustificationType (juce::Justification::centredLeft);
    CBorder->setTextWhenNothingSelected (juce::String());
    CBorder->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBorder->addListener (this);

    CBorder->setBounds (156, 247, 92, 20);

    SL_num_receivers = std::make_unique<SliderWithAttachment>(p.parameters, "numReceivers");
    addAndMakeVisible (SL_num_receivers.get());
    SL_num_receivers->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_receivers->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_receivers->addListener (this);

    SL_num_receivers->setBounds (416, 303, 48, 20);

    SL_max_reflection_order.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_max_reflection_order.get());
    SL_max_reflection_order->setRange (0, 7, 1);
    SL_max_reflection_order->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_max_reflection_order->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_max_reflection_order->addListener (this);

    SL_max_reflection_order->setBounds (181, 102, 48, 20);

    s_attenCoeff_pX.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_attenCoeff_pX.get());
    s_attenCoeff_pX->setRange (0, 1, 0.01);
    s_attenCoeff_pX->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attenCoeff_pX->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_attenCoeff_pX->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6d));
    s_attenCoeff_pX->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_attenCoeff_pX->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_attenCoeff_pX->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_attenCoeff_pX->addListener (this);

    s_attenCoeff_pX->setBounds (256, 82, 60, 60);

    s_attenCoeff_nX.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_attenCoeff_nX.get());
    s_attenCoeff_nX->setRange (0, 1, 0.01);
    s_attenCoeff_nX->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attenCoeff_nX->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_attenCoeff_nX->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6d));
    s_attenCoeff_nX->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_attenCoeff_nX->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_attenCoeff_nX->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_attenCoeff_nX->addListener (this);

    s_attenCoeff_nX->setBounds (256, 148, 60, 60);

    s_attenCoeff_nY.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_attenCoeff_nY.get());
    s_attenCoeff_nY->setRange (0, 1, 0.01);
    s_attenCoeff_nY->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attenCoeff_nY->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_attenCoeff_nY->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6d));
    s_attenCoeff_nY->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_attenCoeff_nY->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_attenCoeff_nY->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_attenCoeff_nY->addListener (this);

    s_attenCoeff_nY->setBounds (332, 148, 60, 60);

    s_attenCoeff_nZ.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_attenCoeff_nZ.get());
    s_attenCoeff_nZ->setRange (0, 1, 0.01);
    s_attenCoeff_nZ->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attenCoeff_nZ->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_attenCoeff_nZ->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6d));
    s_attenCoeff_nZ->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_attenCoeff_nZ->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_attenCoeff_nZ->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_attenCoeff_nZ->addListener (this);

    s_attenCoeff_nZ->setBounds (408, 148, 60, 60);

    s_attenCoeff_pZ.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_attenCoeff_pZ.get());
    s_attenCoeff_pZ->setRange (0, 1, 0.01);
    s_attenCoeff_pZ->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attenCoeff_pZ->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_attenCoeff_pZ->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6d));
    s_attenCoeff_pZ->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_attenCoeff_pZ->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_attenCoeff_pZ->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_attenCoeff_pZ->addListener (this);

    s_attenCoeff_pZ->setBounds (408, 82, 60, 60);

    s_attenCoeff_pY.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_attenCoeff_pY.get());
    s_attenCoeff_pY->setRange (0, 1, 0.01);
    s_attenCoeff_pY->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attenCoeff_pY->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_attenCoeff_pY->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6d));
    s_attenCoeff_pY->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_attenCoeff_pY->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_attenCoeff_pY->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_attenCoeff_pY->addListener (this);

    s_attenCoeff_pY->setBounds (332, 82, 60, 60);

    s_roomLenZ.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_roomLenZ.get());
    s_roomLenZ->setRange (0.5, 6, 0.01);
    s_roomLenZ->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_roomLenZ->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_roomLenZ->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6d));
    s_roomLenZ->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_roomLenZ->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_roomLenZ->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_roomLenZ->addListener (this);

    s_roomLenZ->setBounds (170, 148, 60, 60);

    s_roomLenY.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_roomLenY.get());
    s_roomLenY->setRange (0.5, 20, 0.01);
    s_roomLenY->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_roomLenY->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_roomLenY->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6d));
    s_roomLenY->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_roomLenY->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_roomLenY->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_roomLenY->addListener (this);

    s_roomLenY->setBounds (96, 148, 60, 60);

    s_roomLenX.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_roomLenX.get());
    s_roomLenX->setRange (0.5, 20, 0.01);
    s_roomLenX->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_roomLenX->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_roomLenX->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6d));
    s_roomLenX->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_roomLenX->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_roomLenX->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_roomLenX->addListener (this);

    s_roomLenX->setBounds (21, 148, 60, 60);

    TB_enableIMS.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_enableIMS.get());
    TB_enableIMS->setButtonText (juce::String());
    TB_enableIMS->addListener (this);

    TB_enableIMS->setBounds (206, 65, 26, 26);

    setSize (780, 500);

    /* handle to object */
    hAmbi = processor.getFXHandle();

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_num_sources->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_sources->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_sources->setSliderSnapsToMousePosition(false);
    SL_num_receivers->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_receivers->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_receivers->setSliderSnapsToMousePosition(false);
    SL_max_reflection_order->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_max_reflection_order->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_max_reflection_order->setSliderSnapsToMousePosition(false);

    /* source coordinates viewport */
    sourceCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (sourceCoordsVP.get());
    sourceCoordsView_handle = new inputCoordsView(p, ROOM_SIM_MAX_NUM_SOURCES, ambi_roomsim_getNumSources(hAmbi));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(16, 352, 212, 32*4+2);
    sourceCoordsView_handle->setNCH(ambi_roomsim_getNumSources(hAmbi));

    /* source coordinates viewport */
    receiverCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (receiverCoordsVP.get());
    receiverCoordsView_handle = new outputCoordsView(p, ROOM_SIM_MAX_NUM_RECEIVERS, ambi_roomsim_getNumReceivers(hAmbi));
    receiverCoordsVP->setViewedComponent (receiverCoordsView_handle);
    receiverCoordsVP->setScrollBarsShown (true, false);
    receiverCoordsVP->setAlwaysOnTop(true);
    receiverCoordsVP->setBounds(256, 352, 212, 32*4+2);
    receiverCoordsView_handle->setNCH(ambi_roomsim_getNumReceivers(hAmbi));

    /* grab current parameter settings */
//    SL_num_sources->setValue(ambi_roomsim_getNumSources(hAmbi),dontSendNotification);
//    SL_num_receivers->setValue(ambi_roomsim_getNumReceivers(hAmbi),dontSendNotification);
    //    CBorder->setSelectedId(ambi_roomsim_getOutputOrder(hAmbi), dontSendNotification);

    CBoutputFormat->setSelectedId(ambi_roomsim_getChOrder(hAmbi), dontSendNotification);
    CBnormalisation->setSelectedId(ambi_roomsim_getNormType(hAmbi), dontSendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);
    s_roomLenX->setValue(ambi_roomsim_getRoomDimX(hAmbi), dontSendNotification);
    s_roomLenY->setValue(ambi_roomsim_getRoomDimY(hAmbi), dontSendNotification);
    s_roomLenZ->setValue(ambi_roomsim_getRoomDimZ(hAmbi), dontSendNotification);
    s_attenCoeff_pX->setValue(ambi_roomsim_getWallAbsCoeff(hAmbi, 0, 0), dontSendNotification);
    s_attenCoeff_nX->setValue(ambi_roomsim_getWallAbsCoeff(hAmbi, 0, 1), dontSendNotification);
    s_attenCoeff_pY->setValue(ambi_roomsim_getWallAbsCoeff(hAmbi, 1, 0), dontSendNotification);
    s_attenCoeff_nY->setValue(ambi_roomsim_getWallAbsCoeff(hAmbi, 1, 1), dontSendNotification);
    s_attenCoeff_pZ->setValue(ambi_roomsim_getWallAbsCoeff(hAmbi, 2, 0), dontSendNotification);
    s_attenCoeff_nZ->setValue(ambi_roomsim_getWallAbsCoeff(hAmbi, 2, 1), dontSendNotification);
    TB_enableIMS->setToggleState((bool)ambi_roomsim_getEnableIMSflag(hAmbi), dontSendNotification);
    SL_max_reflection_order->setValue(ambi_roomsim_getMaxReflectionOrder(hAmbi), dontSendNotification);

    /* create panning window */
    panWindow.reset (new pannerView(p, 600, 600));
    addAndMakeVisible (panWindow.get());
    panWindow->setBounds (490, 58, 600, 600);
    refreshPanViewWindow = true;

    /* tooltips */
    CBorder->setTooltip("The encoding order. Note that the plug-in will output (order+1)^2 Ambisonic (spherical harmonic) signals.");
    CBoutputFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormalisation->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    SL_num_sources->setTooltip("Number of sound sources to include in the simulation (one input channel for each).");
    SL_num_receivers->setTooltip("Number of Ambisonic receivers to include in the simulation (outputs stacked up to a maximum of 64 channels).");
    s_roomLenX->setTooltip("Room length along the X-axis, in metres.");
    s_roomLenY->setTooltip("Room length along the Y-axis, in metres.");
    s_roomLenZ->setTooltip("Room length along the Z-axis, in metres.");
    s_attenCoeff_pX->setTooltip("Wall absorption coefficient for the wall at which the positive X-axis intersects.");
    s_attenCoeff_nX->setTooltip("Wall absorption coefficient for the wall at which the negative X-axis intersects.");
    s_attenCoeff_pY->setTooltip("Wall absorption coefficient for the wall at which the positive Y-axis intersects.");
    s_attenCoeff_nY->setTooltip("Wall absorption coefficient for the wall at which the negative Y-axis intersects.");
    s_attenCoeff_pZ->setTooltip("Wall absorption coefficient for the wall at which the positive Z-axis intersects.");
    s_attenCoeff_nZ->setTooltip("Wall absorption coefficient for the wall at which the negative Z-axis intersects.");
    TB_enableIMS->setTooltip("Whether to enable reflection orders greater than 0.");
    SL_max_reflection_order->setTooltip("The maximum reflection order for the simulation.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("This is a shoebox room simulator based on the image source method. It supports multiple sources and Ambisonic receivers. Due to the 64 channel limit, the number of receivers is order-dependent; e.g.: up to 16x FOA, 4x 3rd order, or 1x 7th-order receivers."));

	/* Specify screen refresh rate */
    startTimer(80);//80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    SL_num_sources = nullptr;
    CBoutputFormat = nullptr;
    CBnormalisation = nullptr;
    CBorder = nullptr;
    SL_num_receivers = nullptr;
    SL_max_reflection_order = nullptr;
    s_attenCoeff_pX = nullptr;
    s_attenCoeff_nX = nullptr;
    s_attenCoeff_nY = nullptr;
    s_attenCoeff_nZ = nullptr;
    s_attenCoeff_pZ = nullptr;
    s_attenCoeff_pY = nullptr;
    s_roomLenZ = nullptr;
    s_roomLenY = nullptr;
    s_roomLenX = nullptr;
    TB_enableIMS = nullptr;

    setLookAndFeel(nullptr);
    sourceCoordsVP = nullptr;
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 321, width = 780, height = 177;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             496.0f - 321.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             416.0f - 321.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 33, width = 780, height = 295;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 33.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             112.0f - 33.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 12, y = 58, width = 468, height = 158;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 58, width = 232, height = 158;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 297, width = 220, height = 191;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 241, width = 468, height = 31;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        float x = 1.0f, y = 2.0f, width = 778.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             768.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 488, y = 57, width = 280, height = 431;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 297, width = 220, height = 31;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 200, y = 33, width = 96, height = 30;
        juce::String text (TRANS ("Room Settings"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 588, y = 33, width = 163, height = 30;
        juce::String text (TRANS ("Room View"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 256, y = 241, width = 145, height = 30;
        juce::String text (TRANS ("Format:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 21, y = 241, width = 153, height = 30;
        juce::String text (TRANS ("SH Encoding Order: "));
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
        int x = 92, y = 1, width = 148, height = 32;
        juce::String text (TRANS ("AmbiRoomSim"));
        juce::Colour fillColour = juce::Colour (0xffffda2b);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 780, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 498, width = 780, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 500;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 871, y = 9, width = 2, height = 356;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 23, y = 124, width = 60, height = 30;
        juce::String text (TRANS ("Width"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 95, y = 124, width = 60, height = 30;
        juce::String text (TRANS ("Depth"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 167, y = 124, width = 60, height = 30;
        juce::String text (TRANS ("Height"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 20, y = 95, width = 169, height = 30;
        juce::String text (TRANS ("Max Reflection Order:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 192, y = 217, width = 137, height = 30;
        juce::String text (TRANS ("Receiver Settings"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 256, y = 57, width = 60, height = 30;
        juce::String text (TRANS ("Atten. X"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 304, y = 81, width = 24, height = 30;
        juce::String text (TRANS ("+"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 304, y = 145, width = 24, height = 30;
        juce::String text (TRANS ("-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 332, y = 57, width = 60, height = 30;
        juce::String text (TRANS ("Atten. Y"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 380, y = 81, width = 24, height = 30;
        juce::String text (TRANS ("+"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 380, y = 145, width = 24, height = 30;
        juce::String text (TRANS ("-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 408, y = 57, width = 60, height = 30;
        juce::String text (TRANS ("Atten. Z"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 456, y = 81, width = 24, height = 30;
        juce::String text (TRANS ("+"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 456, y = 145, width = 24, height = 30;
        juce::String text (TRANS ("-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 56, y = 272, width = 137, height = 30;
        juce::String text (TRANS ("Source Coordinates"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 24, y = 323, width = 200, height = 30;
        juce::String text (TRANS ("#        x            y             z"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 21, y = 297, width = 153, height = 30;
        juce::String text (TRANS ("Number of Sources: "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 778, y = 0, width = 2, height = 500;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 20, y = 63, width = 169, height = 30;
        juce::String text (TRANS ("Enable Image Sources:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 252, y = 297, width = 220, height = 191;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 252, y = 297, width = 220, height = 31;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 288, y = 272, width = 152, height = 30;
        juce::String text (TRANS ("Receiver Coordinates"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 264, y = 323, width = 200, height = 30;
        juce::String text (TRANS ("#        x            y             z"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 261, y = 297, width = 155, height = 30;
        juce::String text (TRANS ("Number of Receivers: "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

	g.setColour(Colours::white);
	g.setFont(juce::FontOptions (11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		220, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(ambi_roomsim_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(ambi_roomsim_getNumSources(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
                       TRANS("/") + String(ambi_roomsim_getNSHrequired(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
    }
}

void PluginEditor::resized()
{

}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == SL_num_sources.get())
    {
        ambi_roomsim_setNumSources(hAmbi, (int)SL_num_sources->getValue());
        refreshPanViewWindow = true;
    }
    else if (sliderThatWasMoved == SL_num_receivers.get())
    {
        ambi_roomsim_setNumReceivers(hAmbi, (int)SL_num_receivers->getValue());
        refreshPanViewWindow = true;
    }
    else if (sliderThatWasMoved == SL_max_reflection_order.get())
    {
        ambi_roomsim_setMaxReflectionOrder(hAmbi, (int)SL_max_reflection_order->getValue());
    }
    else if (sliderThatWasMoved == s_attenCoeff_pX.get())
    {
        ambi_roomsim_setWallAbsCoeff(hAmbi, 0, 0, s_attenCoeff_pX->getValue());
    }
    else if (sliderThatWasMoved == s_attenCoeff_nX.get())
    {
        ambi_roomsim_setWallAbsCoeff(hAmbi, 0, 1, s_attenCoeff_nX->getValue());
    }
    else if (sliderThatWasMoved == s_attenCoeff_nY.get())
    {
        ambi_roomsim_setWallAbsCoeff(hAmbi, 1, 1, s_attenCoeff_nY->getValue());
    }
    else if (sliderThatWasMoved == s_attenCoeff_nZ.get())
    {
        ambi_roomsim_setWallAbsCoeff(hAmbi, 2, 1, s_attenCoeff_nZ->getValue());
    }
    else if (sliderThatWasMoved == s_attenCoeff_pZ.get())
    {
        ambi_roomsim_setWallAbsCoeff(hAmbi, 2, 0, s_attenCoeff_pZ->getValue());
    }
    else if (sliderThatWasMoved == s_attenCoeff_pY.get())
    {
        ambi_roomsim_setWallAbsCoeff(hAmbi, 1, 0, s_attenCoeff_pY->getValue());
    }
    else if (sliderThatWasMoved == s_roomLenZ.get())
    {
        ambi_roomsim_setRoomDimZ(hAmbi, (float)s_roomLenZ->getValue());
    }
    else if (sliderThatWasMoved == s_roomLenY.get())
    {
        ambi_roomsim_setRoomDimY(hAmbi, (float)s_roomLenY->getValue());
    }
    else if (sliderThatWasMoved == s_roomLenX.get())
    {
        ambi_roomsim_setRoomDimX(hAmbi, (float)s_roomLenX->getValue());
    }
}

void PluginEditor::comboBoxChanged (juce::ComboBox* /*comboBoxThatHasChanged*/)
{
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == TB_enableIMS.get())
    {
        ambi_roomsim_setEnableIMSflag(hAmbi, (int)TB_enableIMS->getToggleState());
    }
}

void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    sourceCoordsView_handle->setNCH(ambi_roomsim_getNumSources(hAmbi));
    receiverCoordsView_handle->setNCH(ambi_roomsim_getNumReceivers(hAmbi));
//    SL_num_sources->setValue(ambi_roomsim_getNumSources(hAmbi),dontSendNotification);
//    SL_num_receivers->setValue(ambi_roomsim_getNumReceivers(hAmbi),dontSendNotification);
    CBoutputFormat->setSelectedId(ambi_roomsim_getChOrder(hAmbi), sendNotification);
    CBnormalisation->setSelectedId(ambi_roomsim_getNormType(hAmbi), sendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);

    /* refresh pan view */
//    if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) ||
//        sourceCoordsView_handle->getHasASliderChanged() || processor.getRefreshWindow()){
//        panWindow->refreshPanView();
//        refreshPanViewWindow = false;
//        sourceCoordsView_handle->setHasASliderChange(false);
//        processor.setRefreshWindow(false);
//    }
    panWindow->refreshPanView();

    /* display warning message, if needed */
    if ((processor.getCurrentBlockSize() % ambi_roomsim_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumInputs() < ambi_roomsim_getNumSources(hAmbi))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumOutputs() < ambi_roomsim_getNSHrequired(hAmbi))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}
