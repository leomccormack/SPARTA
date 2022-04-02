/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    SL_num_sources.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_sources.get());
    SL_num_sources->setRange (1, 16, 1);
    SL_num_sources->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_sources->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_sources->addListener (this);

    SL_num_sources->setBounds (173, 303, 48, 20);

    CBoutputFormat.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBoutputFormat.get());
    CBoutputFormat->setEditableText (false);
    CBoutputFormat->setJustificationType (juce::Justification::centredLeft);
    CBoutputFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBoutputFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBoutputFormat->addListener (this);

    CBoutputFormat->setBounds (316, 247, 76, 20);

    CBnormalisation.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBnormalisation.get());
    CBnormalisation->setEditableText (false);
    CBnormalisation->setJustificationType (juce::Justification::centredLeft);
    CBnormalisation->setTextWhenNothingSelected (TRANS("N3D"));
    CBnormalisation->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnormalisation->addListener (this);

    CBnormalisation->setBounds (398, 247, 76, 20);

    CBorder.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBorder.get());
    CBorder->setEditableText (false);
    CBorder->setJustificationType (juce::Justification::centredLeft);
    CBorder->setTextWhenNothingSelected (juce::String());
    CBorder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBorder->addListener (this);

    CBorder->setBounds (156, 247, 92, 20);

    SL_num_receivers.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_receivers.get());
    SL_num_receivers->setRange (1, 16, 1);
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


    //[UserPreSize]
    //[/UserPreSize]

    setSize (780, 500);


    //[Constructor] You can add your own custom stuff here..

    /* handle to pluginProcessor */
	hVst = ownerFilter;
    hAmbi = hVst->getFXHandle();

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

    /* add combo box options */
    CBorder->addItem (TRANS("1st order"), SH_ORDER_FIRST);
    CBorder->addItem (TRANS("2nd order"), SH_ORDER_SECOND);
    CBorder->addItem (TRANS("3rd order"), SH_ORDER_THIRD);
    CBorder->addItem (TRANS("4th order"), SH_ORDER_FOURTH);
    CBorder->addItem (TRANS("5th order"), SH_ORDER_FIFTH);
    CBorder->addItem (TRANS("6th order"), SH_ORDER_SIXTH);
    CBorder->addItem (TRANS("7th order"), SH_ORDER_SEVENTH);
    CBoutputFormat->addItem (TRANS("ACN"), CH_ACN);
    CBoutputFormat->addItem (TRANS("FuMa"), CH_FUMA);
    CBnormalisation->addItem (TRANS("N3D"), NORM_N3D);
    CBnormalisation->addItem (TRANS("SN3D"), NORM_SN3D);
    CBnormalisation->addItem (TRANS("FuMa"), NORM_FUMA);

    /* source coordinates viewport */
    sourceCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (sourceCoordsVP.get());
    sourceCoordsView_handle = new inputCoordsView(ownerFilter, ROOM_SIM_MAX_NUM_SOURCES, ambi_roomsim_getNumSources(hAmbi));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(16, 352, 212, 32*4+2);
    sourceCoordsView_handle->setNCH(ambi_roomsim_getNumSources(hAmbi));

    /* source coordinates viewport */
    receiverCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (receiverCoordsVP.get());
    receiverCoordsView_handle = new outputCoordsView(ownerFilter, ROOM_SIM_MAX_NUM_RECEIVERS, ambi_roomsim_getNumReceivers(hAmbi));
    receiverCoordsVP->setViewedComponent (receiverCoordsView_handle);
    receiverCoordsVP->setScrollBarsShown (true, false);
    receiverCoordsVP->setAlwaysOnTop(true);
    receiverCoordsVP->setBounds(256, 352, 212, 32*4+2);
    receiverCoordsView_handle->setNCH(ambi_roomsim_getNumReceivers(hAmbi));

    /* grab current parameter settings */
    SL_num_sources->setValue(ambi_roomsim_getNumSources(hAmbi),dontSendNotification);
    SL_num_receivers->setValue(ambi_roomsim_getNumReceivers(hAmbi),dontSendNotification);
    CBoutputFormat->setSelectedId(ambi_roomsim_getChOrder(hAmbi), dontSendNotification);
    CBorder->setSelectedId(ambi_roomsim_getOutputOrder(hAmbi), dontSendNotification);
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
    panWindow.reset (new pannerView(ownerFilter, 600, 600));
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
    pluginDescription->setTooltip(TRANS("This is a shoebox room simulator based on the image source method. It supports multiple sources and Ambisonic receivers. Due to the 64 channel limit, the number of receivers is order-dependent; e.g.: up to 16xFOA, 4xTOA, or 1x7th-order receivers."));

	/* Specify screen refresh rate */
    startTimer(80);//80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;


    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

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


    //[Destructor]. You can add your own custom destruction code here..
    setLookAndFeel(nullptr);
    sourceCoordsVP = nullptr;
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 321, width = 780, height = 177;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
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
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
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
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 58, width = 232, height = 158;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 297, width = 220, height = 191;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 241, width = 468, height = 31;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        float x = 1.0f, y = 2.0f, width = 778.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
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
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 297, width = 220, height = 31;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 200, y = 33, width = 96, height = 30;
        juce::String text (TRANS("Room Settings"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 588, y = 33, width = 163, height = 30;
        juce::String text (TRANS("Room View"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 256, y = 241, width = 145, height = 30;
        juce::String text (TRANS("Format:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 21, y = 241, width = 153, height = 30;
        juce::String text (TRANS("SH Encoding Order: "));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 1, width = 100, height = 32;
        juce::String text (TRANS("SPARTA|"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.80f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 92, y = 1, width = 148, height = 32;
        juce::String text (TRANS("AmbiRoomSim"));
        juce::Colour fillColour = juce::Colour (0xffffda2b);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 780, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 498, width = 780, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 500;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 871, y = 9, width = 2, height = 356;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 23, y = 124, width = 60, height = 30;
        juce::String text (TRANS("Width"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 95, y = 124, width = 60, height = 30;
        juce::String text (TRANS("Depth"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 167, y = 124, width = 60, height = 30;
        juce::String text (TRANS("Height"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 20, y = 95, width = 169, height = 30;
        juce::String text (TRANS("Max Reflection Order:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 192, y = 217, width = 137, height = 30;
        juce::String text (TRANS("Receiver Settings"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 256, y = 57, width = 60, height = 30;
        juce::String text (TRANS("Atten. X"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 304, y = 81, width = 24, height = 30;
        juce::String text (TRANS("+"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 304, y = 145, width = 24, height = 30;
        juce::String text (TRANS("-"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 332, y = 57, width = 60, height = 30;
        juce::String text (TRANS("Atten. Y"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 380, y = 81, width = 24, height = 30;
        juce::String text (TRANS("+"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 380, y = 145, width = 24, height = 30;
        juce::String text (TRANS("-"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 408, y = 57, width = 60, height = 30;
        juce::String text (TRANS("Atten. Z"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 456, y = 81, width = 24, height = 30;
        juce::String text (TRANS("+"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 456, y = 145, width = 24, height = 30;
        juce::String text (TRANS("-"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 56, y = 272, width = 137, height = 30;
        juce::String text (TRANS("Source Coordinates"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 24, y = 323, width = 200, height = 30;
        juce::String text (TRANS("#        x            y             z"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 21, y = 297, width = 153, height = 30;
        juce::String text (TRANS("Number of Sources: "));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 778, y = 0, width = 2, height = 500;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 20, y = 63, width = 169, height = 30;
        juce::String text (TRANS("Enable Image Sources:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 252, y = 297, width = 220, height = 191;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 252, y = 297, width = 220, height = 31;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 288, y = 272, width = 152, height = 30;
        juce::String text (TRANS("Receiver Coordinates"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 264, y = 323, width = 200, height = 30;
        juce::String text (TRANS("#        x            y             z"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 261, y = 297, width = 155, height = 30;
        juce::String text (TRANS("Number of Receivers: "));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		220, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(ambi_roomsim_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(ambi_roomsim_getNumSources(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(ambi_roomsim_getNSHrequired(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
    }


    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..

    //[/UserResized]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == SL_num_sources.get())
    {
        //[UserSliderCode_SL_num_sources] -- add your slider handling code here..
        ambi_roomsim_setNumSources(hAmbi, (int)SL_num_sources->getValue());
        refreshPanViewWindow = true;
        //[/UserSliderCode_SL_num_sources]
    }
    else if (sliderThatWasMoved == SL_num_receivers.get())
    {
        //[UserSliderCode_SL_num_receivers] -- add your slider handling code here..
        ambi_roomsim_setNumReceivers(hAmbi, (int)SL_num_receivers->getValue());
        refreshPanViewWindow = true;
        //[/UserSliderCode_SL_num_receivers]
    }
    else if (sliderThatWasMoved == SL_max_reflection_order.get())
    {
        //[UserSliderCode_SL_max_reflection_order] -- add your slider handling code here..
        ambi_roomsim_setMaxReflectionOrder(hAmbi, (int)SL_max_reflection_order->getValue());
        //[/UserSliderCode_SL_max_reflection_order]
    }
    else if (sliderThatWasMoved == s_attenCoeff_pX.get())
    {
        //[UserSliderCode_s_attenCoeff_pX] -- add your slider handling code here..
        ambi_roomsim_setWallAbsCoeff(hAmbi, 0, 0, s_attenCoeff_pX->getValue());
        //[/UserSliderCode_s_attenCoeff_pX]
    }
    else if (sliderThatWasMoved == s_attenCoeff_nX.get())
    {
        //[UserSliderCode_s_attenCoeff_nX] -- add your slider handling code here..
        ambi_roomsim_setWallAbsCoeff(hAmbi, 0, 1, s_attenCoeff_nX->getValue());
        //[/UserSliderCode_s_attenCoeff_nX]
    }
    else if (sliderThatWasMoved == s_attenCoeff_nY.get())
    {
        //[UserSliderCode_s_attenCoeff_nY] -- add your slider handling code here..
        ambi_roomsim_setWallAbsCoeff(hAmbi, 1, 1, s_attenCoeff_nY->getValue());
        //[/UserSliderCode_s_attenCoeff_nY]
    }
    else if (sliderThatWasMoved == s_attenCoeff_nZ.get())
    {
        //[UserSliderCode_s_attenCoeff_nZ] -- add your slider handling code here..
        ambi_roomsim_setWallAbsCoeff(hAmbi, 2, 1, s_attenCoeff_nZ->getValue());
        //[/UserSliderCode_s_attenCoeff_nZ]
    }
    else if (sliderThatWasMoved == s_attenCoeff_pZ.get())
    {
        //[UserSliderCode_s_attenCoeff_pZ] -- add your slider handling code here..
        ambi_roomsim_setWallAbsCoeff(hAmbi, 2, 0, s_attenCoeff_pZ->getValue());
        //[/UserSliderCode_s_attenCoeff_pZ]
    }
    else if (sliderThatWasMoved == s_attenCoeff_pY.get())
    {
        //[UserSliderCode_s_attenCoeff_pY] -- add your slider handling code here..
        ambi_roomsim_setWallAbsCoeff(hAmbi, 1, 0, s_attenCoeff_pY->getValue());
        //[/UserSliderCode_s_attenCoeff_pY]
    }
    else if (sliderThatWasMoved == s_roomLenZ.get())
    {
        //[UserSliderCode_s_roomLenZ] -- add your slider handling code here..
        ambi_roomsim_setRoomDimZ(hAmbi, (float)s_roomLenZ->getValue());
        //[/UserSliderCode_s_roomLenZ]
    }
    else if (sliderThatWasMoved == s_roomLenY.get())
    {
        //[UserSliderCode_s_roomLenY] -- add your slider handling code here..
        ambi_roomsim_setRoomDimY(hAmbi, (float)s_roomLenY->getValue());
        //[/UserSliderCode_s_roomLenY]
    }
    else if (sliderThatWasMoved == s_roomLenX.get())
    {
        //[UserSliderCode_s_roomLenX] -- add your slider handling code here..
        ambi_roomsim_setRoomDimX(hAmbi, (float)s_roomLenX->getValue());
        //[/UserSliderCode_s_roomLenX]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBoutputFormat.get())
    {
        //[UserComboBoxCode_CBoutputFormat] -- add your combo box handling code here..
        ambi_roomsim_setChOrder(hAmbi, CBoutputFormat->getSelectedId());
        //[/UserComboBoxCode_CBoutputFormat]
    }
    else if (comboBoxThatHasChanged == CBnormalisation.get())
    {
        //[UserComboBoxCode_CBnormalisation] -- add your combo box handling code here..
        ambi_roomsim_setNormType(hAmbi, CBnormalisation->getSelectedId());
        //[/UserComboBoxCode_CBnormalisation]
    }
    else if (comboBoxThatHasChanged == CBorder.get())
    {
        //[UserComboBoxCode_CBorder] -- add your combo box handling code here..
        ambi_roomsim_setOutputOrder(hAmbi, CBorder->getSelectedId());
        //[/UserComboBoxCode_CBorder]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == TB_enableIMS.get())
    {
        //[UserButtonCode_TB_enableIMS] -- add your button handler code here..
        ambi_roomsim_setEnableIMSflag(hAmbi, (int)TB_enableIMS->getToggleState());
        //[/UserButtonCode_TB_enableIMS]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    sourceCoordsView_handle->setNCH(ambi_roomsim_getNumSources(hAmbi));
    receiverCoordsView_handle->setNCH(ambi_roomsim_getNumReceivers(hAmbi));
    if(SL_num_sources->getValue()!=ambi_roomsim_getNumSources(hAmbi))
        SL_num_sources->setValue(ambi_roomsim_getNumSources(hAmbi),dontSendNotification);
    if(SL_num_receivers->getValue()!=ambi_roomsim_getNumReceivers(hAmbi))
        SL_num_receivers->setValue(ambi_roomsim_getNumReceivers(hAmbi),dontSendNotification);
    if(CBoutputFormat->getSelectedId()!=ambi_roomsim_getChOrder(hAmbi))
        CBoutputFormat->setSelectedId(ambi_roomsim_getChOrder(hAmbi), dontSendNotification);
    if(CBnormalisation->getSelectedId()!=ambi_roomsim_getNormType(hAmbi))
        CBnormalisation->setSelectedId(ambi_roomsim_getNormType(hAmbi), dontSendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);

    /* refresh pan view */
//    if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) ||
//        sourceCoordsView_handle->getHasASliderChanged() || hVst->getRefreshWindow()){
//        panWindow->refreshPanView();
//        refreshPanViewWindow = false;
//        sourceCoordsView_handle->setHasASliderChange(false);
//        hVst->setRefreshWindow(false);
//    }
    panWindow->refreshPanView();

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % ambi_roomsim_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < ambi_roomsim_getNumSources(hAmbi))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumOutputs() < ambi_roomsim_getNSHrequired(hAmbi))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public AudioProcessorEditor, public Timer" constructorParams="PluginProcessor* ownerFilter"
                 variableInitialisers="AudioProcessorEditor(ownerFilter)," snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="780" initialHeight="500">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 321 780 177" fill="linear: 8 496, 8 416, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="0 33 780 295" fill="linear: 8 32, 8 112, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="12 58 468 158" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 58 232 158" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 297 220 191" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 241 468 31" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <ROUNDRECT pos="1 2 778 31" cornerSize="5.0" fill="linear: 0 32, 768 32, 0=ff041518, 1=ff19313f"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="488 57 280 431" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 297 220 31" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="200 33 96 30" fill="solid: ffffffff" hasStroke="0" text="Room Settings"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="588 33 163 30" fill="solid: ffffffff" hasStroke="0" text="Room View"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="256 241 145 30" fill="solid: ffffffff" hasStroke="0" text="Format:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="21 241 153 30" fill="solid: ffffffff" hasStroke="0" text="SH Encoding Order: "
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 148 32" fill="solid: ffffda2b" hasStroke="0" text="AmbiRoomSim"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 780 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 498 780 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 500" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="871 9 2 356" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <TEXT pos="23 124 60 30" fill="solid: ffffffff" hasStroke="0" text="Width"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="95 124 60 30" fill="solid: ffffffff" hasStroke="0" text="Depth"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="167 124 60 30" fill="solid: ffffffff" hasStroke="0" text="Height"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="20 95 169 30" fill="solid: ffffffff" hasStroke="0" text="Max Reflection Order:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="192 217 137 30" fill="solid: ffffffff" hasStroke="0" text="Receiver Settings"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="256 57 60 30" fill="solid: ffffffff" hasStroke="0" text="Atten. X"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="304 81 24 30" fill="solid: ffffffff" hasStroke="0" text="+"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="304 145 24 30" fill="solid: ffffffff" hasStroke="0" text="-"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="332 57 60 30" fill="solid: ffffffff" hasStroke="0" text="Atten. Y"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="380 81 24 30" fill="solid: ffffffff" hasStroke="0" text="+"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="380 145 24 30" fill="solid: ffffffff" hasStroke="0" text="-"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="408 57 60 30" fill="solid: ffffffff" hasStroke="0" text="Atten. Z"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="456 81 24 30" fill="solid: ffffffff" hasStroke="0" text="+"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="456 145 24 30" fill="solid: ffffffff" hasStroke="0" text="-"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="56 272 137 30" fill="solid: ffffffff" hasStroke="0" text="Source Coordinates"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="24 323 200 30" fill="solid: ffffffff" hasStroke="0" text="#        x            y             z"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="21 297 153 30" fill="solid: ffffffff" hasStroke="0" text="Number of Sources: "
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="778 0 2 500" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <TEXT pos="20 63 169 30" fill="solid: ffffffff" hasStroke="0" text="Enable Image Sources:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="252 297 220 191" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="252 297 220 31" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="288 272 152 30" fill="solid: ffffffff" hasStroke="0" text="Receiver Coordinates"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="264 323 200 30" fill="solid: ffffffff" hasStroke="0" text="#        x            y             z"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="261 297 155 30" fill="solid: ffffffff" hasStroke="0" text="Number of Receivers: "
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="2c2a2b3d0614cc94" memberName="SL_num_sources"
          virtualName="" explicitFocusOrder="0" pos="173 303 48 20" min="1.0"
          max="16.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="63f8ff411606aafd" memberName="CBoutputFormat"
            virtualName="" explicitFocusOrder="0" pos="316 247 76 20" editable="0"
            layout="33" items="" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="27f130362a28f1eb" memberName="CBnormalisation"
            virtualName="" explicitFocusOrder="0" pos="398 247 76 20" editable="0"
            layout="33" items="" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="56ba0566c2fe39e0" memberName="CBorder"
            virtualName="" explicitFocusOrder="0" pos="156 247 92 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="2871a203f1a429ca" memberName="SL_num_receivers"
          virtualName="" explicitFocusOrder="0" pos="416 303 48 20" min="1.0"
          max="16.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="97b87b3a98bedb21" memberName="SL_max_reflection_order"
          virtualName="" explicitFocusOrder="0" pos="181 102 48 20" min="0.0"
          max="7.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="ace036a85eec9703" memberName="s_attenCoeff_pX"
          virtualName="" explicitFocusOrder="0" pos="256 82 60 60" rotarysliderfill="ff315b6d"
          rotaryslideroutline="ff5c5d5e" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.0" max="1.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="16" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="3a446f0d8a900a47" memberName="s_attenCoeff_nX"
          virtualName="" explicitFocusOrder="0" pos="256 148 60 60" rotarysliderfill="ff315b6d"
          rotaryslideroutline="ff5c5d5e" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.0" max="1.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="16" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="ec7a151a044bde68" memberName="s_attenCoeff_nY"
          virtualName="" explicitFocusOrder="0" pos="332 148 60 60" rotarysliderfill="ff315b6d"
          rotaryslideroutline="ff5c5d5e" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.0" max="1.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="16" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="9d3d224774ed3c11" memberName="s_attenCoeff_nZ"
          virtualName="" explicitFocusOrder="0" pos="408 148 60 60" rotarysliderfill="ff315b6d"
          rotaryslideroutline="ff5c5d5e" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.0" max="1.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="16" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="744018b1c7c544e0" memberName="s_attenCoeff_pZ"
          virtualName="" explicitFocusOrder="0" pos="408 82 60 60" rotarysliderfill="ff315b6d"
          rotaryslideroutline="ff5c5d5e" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.0" max="1.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="16" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="f691f960ad642e32" memberName="s_attenCoeff_pY"
          virtualName="" explicitFocusOrder="0" pos="332 82 60 60" rotarysliderfill="ff315b6d"
          rotaryslideroutline="ff5c5d5e" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.0" max="1.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="16" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="7d646117b60514d4" memberName="s_roomLenZ"
          virtualName="" explicitFocusOrder="0" pos="170 148 60 60" rotarysliderfill="ff315b6d"
          rotaryslideroutline="ff5c5d5e" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.5" max="6.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="16" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="91bcd46442e7ef1b" memberName="s_roomLenY"
          virtualName="" explicitFocusOrder="0" pos="96 148 60 60" rotarysliderfill="ff315b6d"
          rotaryslideroutline="ff5c5d5e" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.5" max="20.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="16" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="7a1edd460821ef6d" memberName="s_roomLenX"
          virtualName="" explicitFocusOrder="0" pos="21 148 60 60" rotarysliderfill="ff315b6d"
          rotaryslideroutline="ff5c5d5e" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.5" max="20.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="16" skewFactor="1.0" needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="3e2f1e0872c66d3b" memberName="TB_enableIMS"
                virtualName="" explicitFocusOrder="0" pos="206 65 26 26" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

