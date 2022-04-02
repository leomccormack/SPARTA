/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.3

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
    : AudioProcessorEditor(ownerFilter), progressbar(progress)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    CBbeamType.reset (new juce::ComboBox (juce::String()));
    addAndMakeVisible (CBbeamType.get());
    CBbeamType->setEditableText (false);
    CBbeamType->setJustificationType (juce::Justification::centredLeft);
    CBbeamType->setTextWhenNothingSelected (TRANS("Default"));
    CBbeamType->setTextWhenNoChoicesAvailable (juce::String());
    CBbeamType->addListener (this);

    CBbeamType->setBounds (121, 440, 112, 18);

    CBchFormat.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (juce::Justification::centredLeft);
    CBchFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBchFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBchFormat->addListener (this);

    CBchFormat->setBounds (90, 504, 66, 18);

    CBnormScheme.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (juce::Justification::centredLeft);
    CBnormScheme->setTextWhenNothingSelected (TRANS("N3D"));
    CBnormScheme->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnormScheme->addListener (this);

    CBnormScheme->setBounds (161, 504, 71, 18);

    CB_hfov.reset (new juce::ComboBox (juce::String()));
    addAndMakeVisible (CB_hfov.get());
    CB_hfov->setEditableText (false);
    CB_hfov->setJustificationType (juce::Justification::centredLeft);
    CB_hfov->setTextWhenNothingSelected (TRANS("360"));
    CB_hfov->setTextWhenNoChoicesAvailable (juce::String());
    CB_hfov->addListener (this);

    CB_hfov->setBounds (584, 406, 66, 18);

    CB_aspectRatio.reset (new juce::ComboBox (juce::String()));
    addAndMakeVisible (CB_aspectRatio.get());
    CB_aspectRatio->setEditableText (false);
    CB_aspectRatio->setJustificationType (juce::Justification::centredLeft);
    CB_aspectRatio->setTextWhenNothingSelected (TRANS("2:1"));
    CB_aspectRatio->setTextWhenNoChoicesAvailable (juce::String());
    CB_aspectRatio->addListener (this);

    CB_aspectRatio->setBounds (584, 438, 66, 18);

    SLmapAvg.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SLmapAvg.get());
    SLmapAvg->setRange (0, 1, 0.01);
    SLmapAvg->setSliderStyle (juce::Slider::LinearHorizontal);
    SLmapAvg->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    SLmapAvg->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    SLmapAvg->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    SLmapAvg->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    SLmapAvg->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    SLmapAvg->addListener (this);

    SLmapAvg->setBounds (349, 468, 104, 24);

    CBinputOrder.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBinputOrder.get());
    CBinputOrder->setEditableText (false);
    CBinputOrder->setJustificationType (juce::Justification::centredLeft);
    CBinputOrder->setTextWhenNothingSelected (TRANS("Default"));
    CBinputOrder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBinputOrder->addListener (this);

    CBinputOrder->setBounds (121, 403, 112, 18);

    s_minFreq.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_minFreq.get());
    s_minFreq->setRange (0, 24000, 1);
    s_minFreq->setSliderStyle (juce::Slider::LinearHorizontal);
    s_minFreq->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    s_minFreq->addListener (this);

    s_minFreq->setBounds (592, 469, 58, 24);

    s_maxFreq.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_maxFreq.get());
    s_maxFreq->setRange (0, 24000, 1);
    s_maxFreq->setSliderStyle (juce::Slider::LinearHorizontal);
    s_maxFreq->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    s_maxFreq->addListener (this);

    s_maxFreq->setBounds (592, 500, 58, 24);

    CBgridOption.reset (new juce::ComboBox (juce::String()));
    addAndMakeVisible (CBgridOption.get());
    CBgridOption->setEditableText (false);
    CBgridOption->setJustificationType (juce::Justification::centredLeft);
    CBgridOption->setTextWhenNothingSelected (TRANS("Default"));
    CBgridOption->setTextWhenNoChoicesAvailable (juce::String());
    CBgridOption->addListener (this);

    CBgridOption->setBounds (121, 472, 112, 18);

    CBupscaleOrder.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBupscaleOrder.get());
    CBupscaleOrder->setEditableText (false);
    CBupscaleOrder->setJustificationType (juce::Justification::centredLeft);
    CBupscaleOrder->setTextWhenNothingSelected (TRANS("Default"));
    CBupscaleOrder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBupscaleOrder->addListener (this);

    CBupscaleOrder->setBounds (354, 440, 99, 18);

    CBdirassMode.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBdirassMode.get());
    CBdirassMode->setEditableText (false);
    CBdirassMode->setJustificationType (juce::Justification::centredLeft);
    CBdirassMode->setTextWhenNothingSelected (TRANS("Default"));
    CBdirassMode->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBdirassMode->addListener (this);

    CBdirassMode->setBounds (354, 403, 99, 18);

    s_interpWidth.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_interpWidth.get());
    s_interpWidth->setRange (64, 256, 1);
    s_interpWidth->setSliderStyle (juce::Slider::LinearHorizontal);
    s_interpWidth->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    s_interpWidth->addListener (this);

    s_interpWidth->setBounds (368, 500, 85, 24);

    CB_webcam.reset (new juce::ComboBox (juce::String()));
    addAndMakeVisible (CB_webcam.get());
    CB_webcam->setEditableText (false);
    CB_webcam->setJustificationType (juce::Justification::centredLeft);
    CB_webcam->setTextWhenNothingSelected (juce::String());
    CB_webcam->setTextWhenNoChoicesAvailable (juce::String());
    CB_webcam->addListener (this);

    CB_webcam->setBounds (434, 38, 92, 17);

    TB_greyScale.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_greyScale.get());
    TB_greyScale->setButtonText (juce::String());
    TB_greyScale->addListener (this);

    TB_greyScale->setBounds (639, 35, 24, 24);

    TB_flipUD.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipUD.get());
    TB_flipUD->setButtonText (juce::String());
    TB_flipUD->addListener (this);

    TB_flipUD->setBounds (598, 35, 24, 24);

    TB_flipLR.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipLR.get());
    TB_flipLR->setButtonText (juce::String());
    TB_flipLR->addListener (this);

    TB_flipLR->setBounds (550, 35, 24, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (672, 542);


    //[Constructor] You can add your own custom stuff here..

    /* handle for pluginProcessor */
	hVst = ownerFilter;
    hDir = hVst->getFXHandle();

    /* OpenGL init */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    s_minFreq->setColour(Slider::trackColourId, Colours::transparentBlack);
    s_minFreq->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    s_minFreq->setSliderSnapsToMousePosition(false);
    s_maxFreq->setColour(Slider::trackColourId, Colours::transparentBlack);
    s_maxFreq->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    s_maxFreq->setSliderSnapsToMousePosition(false);
    s_interpWidth->setColour(Slider::trackColourId, Colours::transparentBlack);
    s_interpWidth->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    //s_interpWidth->setSliderSnapsToMousePosition(false);

    /* add input order options */
    CBinputOrder->addItem (TRANS("1st order"), SH_ORDER_FIRST);
    CBinputOrder->addItem (TRANS("2nd order"), SH_ORDER_SECOND);
    CBinputOrder->addItem (TRANS("3rd order"), SH_ORDER_THIRD);
    CBinputOrder->addItem (TRANS("4th order"), SH_ORDER_FOURTH);
    CBinputOrder->addItem (TRANS("5th order"), SH_ORDER_FIFTH);
    CBinputOrder->addItem (TRANS("6th order"), SH_ORDER_SIXTH);
    CBinputOrder->addItem (TRANS("7th order"), SH_ORDER_SEVENTH);

    /* add upscale order options */
    CBupscaleOrder->addItem (TRANS("1st order"), UPSCALE_ORDER_FIRST);
    CBupscaleOrder->addItem (TRANS("2nd order"), UPSCALE_ORDER_SECOND);
    CBupscaleOrder->addItem (TRANS("3rd order"), UPSCALE_ORDER_THIRD);
    CBupscaleOrder->addItem (TRANS("4th order"), UPSCALE_ORDER_FOURTH);
    CBupscaleOrder->addItem (TRANS("5th order"), UPSCALE_ORDER_FIFTH);
    CBupscaleOrder->addItem (TRANS("6th order"), UPSCALE_ORDER_SIXTH);
    CBupscaleOrder->addItem (TRANS("7th order"), UPSCALE_ORDER_SEVENTH);
    CBupscaleOrder->addItem (TRANS("8th order"), UPSCALE_ORDER_EIGHTH);
    CBupscaleOrder->addItem (TRANS("9th order"), UPSCALE_ORDER_NINTH);
    CBupscaleOrder->addItem (TRANS("10th order"), UPSCALE_ORDER_TENTH);
    CBupscaleOrder->addItem (TRANS("11th order"), UPSCALE_ORDER_ELEVENTH);
    CBupscaleOrder->addItem (TRANS("12th order"), UPSCALE_ORDER_TWELFTH);
    CBupscaleOrder->addItem (TRANS("13th order"), UPSCALE_ORDER_THIRTEENTH);
    CBupscaleOrder->addItem (TRANS("14th order"), UPSCALE_ORDER_FOURTEENTH);
    CBupscaleOrder->addItem (TRANS("15th order"), UPSCALE_ORDER_FIFTEENTH);
    CBupscaleOrder->addItem (TRANS("16th order"), UPSCALE_ORDER_SIXTHTEENTH);
    CBupscaleOrder->addItem (TRANS("17th order"), UPSCALE_ORDER_SEVENTEENTH);
    CBupscaleOrder->addItem (TRANS("18th order"), UPSCALE_ORDER_EIGHTEENTH);
    CBupscaleOrder->addItem (TRANS("19th order"), UPSCALE_ORDER_NINETEENTH);
    CBupscaleOrder->addItem (TRANS("20th order"), UPSCALE_ORDER_TWENTIETH);

    /* Add beam options */
    CBbeamType->addItem (TRANS("Cardioid"), STATIC_BEAM_TYPE_CARDIOID);
    CBbeamType->addItem (TRANS("Hyper-Cardioid"), STATIC_BEAM_TYPE_HYPERCARDIOID);
    CBbeamType->addItem (TRANS("Max-EV"), STATIC_BEAM_TYPE_MAX_EV);

    /* Add processing options */
    CBdirassMode->addItem (TRANS("Off"), REASS_MODE_OFF);
    CBdirassMode->addItem (TRANS("Upscale"), REASS_UPSCALE);
    CBdirassMode->addItem (TRANS("Nearest"), REASS_NEAREST);

    /* Add grid options */
    CBgridOption->addItem (TRANS("T-design: 6"), T_DESIGN_3);
    CBgridOption->addItem (TRANS("T-design: 12"), T_DESIGN_4);
    CBgridOption->addItem (TRANS("T-design: 24"), T_DESIGN_6);
    CBgridOption->addItem (TRANS("T-design: 48"), T_DESIGN_9);
    CBgridOption->addItem (TRANS("T-design: 94"), T_DESIGN_13);
    CBgridOption->addItem (TRANS("T-design: 180"), T_DESIGN_18);
    CBgridOption->addItem (TRANS("G-sphere: 362"), GRID_GEOSPHERE_6);
    CBgridOption->addItem (TRANS("T-design: 480"), T_DESIGN_30);
    CBgridOption->addItem (TRANS("G-sphere: 642"), GRID_GEOSPHERE_8);
    CBgridOption->addItem (TRANS("G-sphere: 812"), GRID_GEOSPHERE_9);
    CBgridOption->addItem (TRANS("G-sphere: 1002"), GRID_GEOSPHERE_10);
    CBgridOption->addItem (TRANS("G-sphere: 1442"), GRID_GEOSPHERE_12);

    /* Add remaining options */
    CBchFormat->addItem(TRANS("ACN"), CH_ACN);
    CBchFormat->addItem(TRANS("FuMa"), CH_FUMA);
    CBnormScheme->addItem(TRANS("N3D"), NORM_N3D);
    CBnormScheme->addItem(TRANS("SN3D"), NORM_SN3D);
    CBnormScheme->addItem(TRANS("FuMa"), NORM_FUMA);
    CB_hfov->addItem(TRANS("360"), HFOV_360);
    CB_hfov->addItem(TRANS("180"), HFOV_180);
    CB_hfov->addItem(TRANS("90"), HFOV_90);
    CB_hfov->addItem(TRANS("60"), HFOV_60);
    CB_aspectRatio->addItem(TRANS("2:1"), ASPECT_RATIO_2_1);
    CB_aspectRatio->addItem(TRANS("16:9"), ASPECT_RATIO_16_9);
    CB_aspectRatio->addItem(TRANS("4:3"), ASPECT_RATIO_4_3);

    /* Overlay */
    previewArea.setBounds(13, 59, 646, 323);
    overlayIncluded.reset (new overlay(ownerFilter));
    addAndMakeVisible (overlayIncluded.get());
    overlayIncluded->setAlwaysOnTop(true);
    overlayIncluded->setBounds(previewArea);

    /* Camera support */
    updateCameraList();
    CB_webcam->setSelectedId (hVst->getCameraID(), dontSendNotification);
    CB_webcam->onChange = [this] { cameraChanged(); };
    addAndMakeVisible (lastSnapshot);
    TB_greyScale->setToggleState(hVst->getGreyScale(), dontSendNotification);
    TB_flipLR->setToggleState(hVst->getFlipLR(), dontSendNotification);
    TB_flipUD->setToggleState(hVst->getFlipUD(), dontSendNotification);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

    /* fetch current configuration */
    CBinputOrder->setSelectedId(dirass_getInputOrder(hDir), dontSendNotification);
    CBbeamType->setSelectedId(dirass_getBeamType(hDir), dontSendNotification);
    CBgridOption->setSelectedId(dirass_getDisplayGridOption(hDir), dontSendNotification);
    CBupscaleOrder->setSelectedId(dirass_getUpscaleOrder(hDir), dontSendNotification);
    CBdirassMode->setSelectedId(dirass_getDiRAssMode(hDir), dontSendNotification);
    s_minFreq->setValue((double)dirass_getMinFreq(hDir), dontSendNotification);
    s_maxFreq->setValue((double)dirass_getMaxFreq(hDir), dontSendNotification);
    CBchFormat->setSelectedId(dirass_getChOrder(hDir), dontSendNotification);
    CBnormScheme->setSelectedId(dirass_getNormType(hDir), dontSendNotification);
    CB_hfov->setSelectedId(dirass_getDispFOV(hDir), dontSendNotification);
    CB_aspectRatio->setSelectedId(dirass_getAspectRatio(hDir), dontSendNotification);
    SLmapAvg->setValue(dirass_getMapAvgCoeff(hDir), dontSendNotification);
    s_interpWidth->setValue(dirass_getDispWidth(hDir), dontSendNotification);
    CBupscaleOrder->setEnabled(dirass_getDiRAssMode(hDir) == REASS_UPSCALE ? true : false);
    resolutionHasChanged = false;
    CBchFormat->setItemEnabled(CH_FUMA, dirass_getInputOrder(hDir)==SH_ORDER_FIRST ? true : false);
    CBnormScheme->setItemEnabled(NORM_FUMA, dirass_getInputOrder(hDir)==SH_ORDER_FIRST ? true : false);

    /* tooltips */
    CBinputOrder->setTooltip("Analysis order. Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals as input.");
    CBbeamType->setTooltip("Sector beamforming pattern to use.");
    CBgridOption->setTooltip("Analysis/scanning grid options.");
    CBupscaleOrder->setTooltip("Sets the upscaling order. Since the plug-in is not bound by the VST channel limit, we can go pretty crazy here.");
    CBdirassMode->setTooltip("Off: direction-reassignment (DirASS) is disabled, and the plug-in displays a basic steered-response power (SRP) activity-map. \n\nNearest: for each scanning direction, the direction of arrival is estimated within the sector beam-pattern and the energy of the beamformer is quantised to the nearest display pixel. \n\nUpscale: rather than re-assigning the energy to the nearest pixel, the sector-beamformer is encoded into an order higher than that of the input. The upscaled energy is then used for the activity-map.");
    CB_hfov->setTooltip("Horizontal field-of-view (FOV) options.");
    CB_aspectRatio->setTooltip("Aspect ratio options.");
    SLmapAvg->setTooltip("Activity-map averaging coefficient (one-pole filter).");
    CBchFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormScheme->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    CB_webcam->setTooltip("Optionally, the video from a webcam may be streamed behind the activity-map; allowing for a make-shift acoustic camera. This is particularly effective when using, for example, a 360degree Ricoh Theta camera.");
    TB_greyScale->setTooltip("Sets the plug-in to display the webcam image in 'grey-scale'.");
    TB_flipUD->setTooltip("Flips the webcam image up-down, as it may be preferable to mount the camera upside-down on top of the microphone array; in order to bring the origin of the camera closer to that of the array.");
    TB_flipLR->setTooltip("Flips the webcam image left-right, as some webcams mirror the images taken.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A sound-field visualiser, which is based on the directional re-assignment of beamformer energy. This energy re-assignment is based on local DoA estimates for each scanning direction, and may be quantised to the nearest direction or upscaled to a higher-order than the input; resulting in sharper activity-maps. For example, a second-order input may be displayed with (up to) 20th order output resolution. The plug-in also allows the user to place real-time video footage behind the activity-map, in order to create a make-shift acoustic camera.\n"));
    addAndMakeVisible (publicationLink);
    publicationLink.setColour (HyperlinkButton::textColourId, Colours::lightblue);
    publicationLink.setBounds(getBounds().getWidth()-80, 4, 80, 12);
    publicationLink.setJustificationType(Justification::centredLeft);

	/* Specify screen refresh rate */
    startTimer(TIMER_GUI_RELATED, 140);//80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    CBbeamType = nullptr;
    CBchFormat = nullptr;
    CBnormScheme = nullptr;
    CB_hfov = nullptr;
    CB_aspectRatio = nullptr;
    SLmapAvg = nullptr;
    CBinputOrder = nullptr;
    s_minFreq = nullptr;
    s_maxFreq = nullptr;
    CBgridOption = nullptr;
    CBupscaleOrder = nullptr;
    CBdirassMode = nullptr;
    s_interpWidth = nullptr;
    CB_webcam = nullptr;
    TB_greyScale = nullptr;
    TB_flipUD = nullptr;
    TB_flipLR = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    setLookAndFeel(nullptr);
    overlayIncluded = nullptr;
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 286, width = 672, height = 256;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041519);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             544.0f - 286.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             448.0f - 286.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 30, width = 672, height = 256;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
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
        float x = 1.0f, y = 2.0f, width = 670.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             656.0f - 1.0f + x,
                                             24.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 13, y = 394, width = 450, height = 138;
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
        int x = 242, y = 394, width = 221, height = 36;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x35a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 13, y = 394, width = 230, height = 36;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x35a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 58, width = 648, height = 325;
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
        int x = 22, y = 397, width = 132, height = 30;
        juce::String text (TRANS("Input Order:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 497, width = 132, height = 30;
        juce::String text (TRANS("Format:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 250, y = 465, width = 132, height = 30;
        juce::String text (TRANS("Average Coeff:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 433, width = 132, height = 30;
        juce::String text (TRANS("Beam Type:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 465, width = 132, height = 30;
        juce::String text (TRANS("Scanning Grid:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 472, y = 394, width = 186, height = 138;
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
        int x = 481, y = 399, width = 132, height = 30;
        juce::String text (TRANS("Horiz. FOV:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 481, y = 432, width = 132, height = 30;
        juce::String text (TRANS("Aspect Ratio:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
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
        int x = 92, y = 1, width = 112, height = 32;
        juce::String text (TRANS("DirASS"));
        juce::Colour fillColour = juce::Colour (0xffb0a6e7);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 481, y = 465, width = 152, height = 30;
        juce::String text (TRANS("Min Freq (Hz):"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 481, y = 497, width = 104, height = 30;
        juce::String text (TRANS("Max Freq (Hz):"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 250, y = 433, width = 132, height = 30;
        juce::String text (TRANS("Upscale Order:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 250, y = 397, width = 181, height = 30;
        juce::String text (TRANS("DirASS Mode:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 250, y = 497, width = 132, height = 30;
        juce::String text (TRANS("Width (pixels):"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 624, y = 32, width = 29, height = 30;
        juce::String text (TRANS("GS:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 576, y = 32, width = 37, height = 30;
        juce::String text (TRANS("U|D:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 530, y = 32, width = 37, height = 30;
        juce::String text (TRANS("L|R:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 283, y = 33, width = 125, height = 30;
        juce::String text (TRANS("Display Window"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 674, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 540, width = 674, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 540;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 670, y = 0, width = 2, height = 540;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		170, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(dirass_getSamplingRate(hDir)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(dirass_getNSHrequired(hDir)) + TRANS(")"),
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

    if (overlayIncluded != nullptr){
        if (cameraPreviewComp.get() != nullptr) {
            cameraPreviewComp->setBounds(overlayIncluded->getBounds());
            cameraPreviewComp->setVisible(false);
        }
        lastSnapshot.setBounds(overlayIncluded->getBounds());
        overlayIncluded->setAlwaysOnTop(true);
        overlayIncluded->setBounds(previewArea);
        overlayIncluded->resized();
    }
    repaint();
    //[/UserResized]
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBbeamType.get())
    {
        //[UserComboBoxCode_CBbeamType] -- add your combo box handling code here..
        dirass_setBeamType(hDir, CBbeamType->getSelectedId());
        //[/UserComboBoxCode_CBbeamType]
    }
    else if (comboBoxThatHasChanged == CBchFormat.get())
    {
        //[UserComboBoxCode_CBchFormat] -- add your combo box handling code here..
        dirass_setChOrder(hDir, CBchFormat->getSelectedId());
        //[/UserComboBoxCode_CBchFormat]
    }
    else if (comboBoxThatHasChanged == CBnormScheme.get())
    {
        //[UserComboBoxCode_CBnormScheme] -- add your combo box handling code here..
        dirass_setNormType(hDir, CBnormScheme->getSelectedId());
        //[/UserComboBoxCode_CBnormScheme]
    }
    else if (comboBoxThatHasChanged == CB_hfov.get())
    {
        //[UserComboBoxCode_CB_hfov] -- add your combo box handling code here..
        dirass_setDispFOV(hDir, CB_hfov->getSelectedId());
        //[/UserComboBoxCode_CB_hfov]
    }
    else if (comboBoxThatHasChanged == CB_aspectRatio.get())
    {
        //[UserComboBoxCode_CB_aspectRatio] -- add your combo box handling code here..
        dirass_setAspectRatio(hDir, CB_aspectRatio->getSelectedId());
        //[/UserComboBoxCode_CB_aspectRatio]
    }
    else if (comboBoxThatHasChanged == CBinputOrder.get())
    {
        //[UserComboBoxCode_CBinputOrder] -- add your combo box handling code here..
        dirass_setInputOrder(hDir, CBinputOrder->getSelectedId());
        //[/UserComboBoxCode_CBinputOrder]
    }
    else if (comboBoxThatHasChanged == CBgridOption.get())
    {
        //[UserComboBoxCode_CBgridOption] -- add your combo box handling code here..
        dirass_setDisplayGridOption(hDir, CBgridOption->getSelectedId());
        //[/UserComboBoxCode_CBgridOption]
    }
    else if (comboBoxThatHasChanged == CBupscaleOrder.get())
    {
        //[UserComboBoxCode_CBupscaleOrder] -- add your combo box handling code here..
        dirass_setUpscaleOrder(hDir, CBupscaleOrder->getSelectedId());
        //[/UserComboBoxCode_CBupscaleOrder]
    }
    else if (comboBoxThatHasChanged == CBdirassMode.get())
    {
        //[UserComboBoxCode_CBdirassMode] -- add your combo box handling code here..
        dirass_setDiRAssMode(hDir, CBdirassMode->getSelectedId());
        CBupscaleOrder->setEnabled(dirass_getDiRAssMode(hDir) == REASS_UPSCALE ? true : false);
        //[/UserComboBoxCode_CBdirassMode]
    }
    else if (comboBoxThatHasChanged == CB_webcam.get())
    {
        //[UserComboBoxCode_CB_webcam] -- add your combo box handling code here..
        hVst->setCameraID(CB_webcam->getSelectedId());
        cameraChanged();
        if(CB_webcam->getSelectedId()==1){
            incomingImage.clear(previewArea);
            lastSnapshot.setImage(incomingImage);
        }
        //[/UserComboBoxCode_CB_webcam]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == SLmapAvg.get())
    {
        //[UserSliderCode_SLmapAvg] -- add your slider handling code here..
        dirass_setMapAvgCoeff(hDir, (float)SLmapAvg->getValue());
        //[/UserSliderCode_SLmapAvg]
    }
    else if (sliderThatWasMoved == s_minFreq.get())
    {
        //[UserSliderCode_s_minFreq] -- add your slider handling code here..
        dirass_setMinFreq(hDir, (float)s_minFreq->getValue());
        //[/UserSliderCode_s_minFreq]
    }
    else if (sliderThatWasMoved == s_maxFreq.get())
    {
        //[UserSliderCode_s_maxFreq] -- add your slider handling code here..
        dirass_setMaxFreq(hDir, (float)s_maxFreq->getValue());
        //[/UserSliderCode_s_maxFreq]
    }
    else if (sliderThatWasMoved == s_interpWidth.get())
    {
        //[UserSliderCode_s_interpWidth] -- add your slider handling code here..
        dirass_setDispWidth(hDir, (int)s_interpWidth->getValue());
        //[/UserSliderCode_s_interpWidth]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == TB_greyScale.get())
    {
        //[UserButtonCode_TB_greyScale] -- add your button handler code here..
        hVst->setGreyScale(TB_greyScale->getToggleState());
        //[/UserButtonCode_TB_greyScale]
    }
    else if (buttonThatWasClicked == TB_flipUD.get())
    {
        //[UserButtonCode_TB_flipUD] -- add your button handler code here..
        hVst->setFlipUD(TB_flipUD->getToggleState());
        //[/UserButtonCode_TB_flipUD]
    }
    else if (buttonThatWasClicked == TB_flipLR.get())
    {
        //[UserButtonCode_TB_flipLR] -- add your button handler code here..
        hVst->setFlipLR(TB_flipLR->getToggleState());
        //[/UserButtonCode_TB_flipLR]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback(int timerID)
{
    switch(timerID){
        case TIMER_PROCESSING_RELATED:
            /* handled in PluginProcessor */
            break;

        case TIMER_GUI_RELATED:
            /* parameters whos values can change internally should be periodically refreshed */
            if(CBchFormat->getSelectedId()!=dirass_getChOrder(hDir))
                CBchFormat->setSelectedId(dirass_getChOrder(hDir), dontSendNotification);
            if(CBnormScheme->getSelectedId()!=dirass_getNormType(hDir))
                CBnormScheme->setSelectedId(dirass_getNormType(hDir), dontSendNotification);
            CBchFormat->setItemEnabled(CH_FUMA, dirass_getInputOrder(hDir)==SH_ORDER_FIRST ? true : false);
            CBnormScheme->setItemEnabled(NORM_FUMA, dirass_getInputOrder(hDir)==SH_ORDER_FIRST ? true : false);
            CBgridOption->setEnabled(hVst->getIsPlaying() ? false : true);
            s_interpWidth->setEnabled(hVst->getIsPlaying() ? false : true);

            /* take webcam picture */
            if(CB_webcam->getSelectedId()>1){
                handleAsyncUpdate();
                lastSnapshot.setTransform(AffineTransform()); /*identity*/
                AffineTransform m_LR, m_UD, m_LR_UD;
                m_LR = AffineTransform(-1, 0, previewArea.getWidth(), 0, 1, 0).followedBy(AffineTransform::translation(2 * previewArea.getX(),0));    /* flip left/right */
                m_UD = AffineTransform(1, 0, 0, 0, -1, previewArea.getHeight()).followedBy(AffineTransform::translation(0, 2 * previewArea.getY()));  /* flip up/down */
                m_LR_UD = m_LR.followedBy(m_UD);  /* flip left/right and up/down */

                if (TB_flipLR->getToggleState() && TB_flipUD->getToggleState())
                    lastSnapshot.setTransform(m_LR_UD);
                else if (TB_flipLR->getToggleState())
                    lastSnapshot.setTransform(m_LR);
                else if (TB_flipUD->getToggleState())
                    lastSnapshot.setTransform(m_UD);

                if (incomingImage.isValid())
                    lastSnapshot.setImage(incomingImage);
            }

            /* Progress bar */
            if(dirass_getCodecStatus(hDir)==CODEC_STATUS_INITIALISING){
                addAndMakeVisible(progressbar);
                progressbar.setAlwaysOnTop(true);
                progress = (double)dirass_getProgressBar0_1(hDir);
                char text[PROGRESSBARTEXT_CHAR_LENGTH];
                dirass_getProgressBarText(hDir, (char*)text);
                progressbar.setTextToDisplay(String(text));
            }
            else
                removeChildComponent(&progressbar);

            /* Some parameters shouldn't be editable during initialisation*/
            if(dirass_getCodecStatus(hDir)==CODEC_STATUS_INITIALISING){
                if(CBbeamType->isEnabled())
                    CBbeamType->setEnabled(false);
                if(CBbeamType->isEnabled())
                    CBbeamType->setEnabled(false);
                if(CB_hfov->isEnabled())
                    CB_hfov->setEnabled(false);
                if(CB_aspectRatio->isEnabled())
                    CB_aspectRatio->setEnabled(false);
                if(CBinputOrder->isEnabled())
                    CBinputOrder->setEnabled(false);
                if(CBgridOption->isEnabled())
                    CBgridOption->setEnabled(false);
                if(CBupscaleOrder->isEnabled())
                    CBupscaleOrder->setEnabled(false);
                if(s_interpWidth->isEnabled())
                    s_interpWidth->setEnabled(false);
            }
            else{
                if(!CBbeamType->isEnabled())
                    CBbeamType->setEnabled(true);
                if(!CBbeamType->isEnabled())
                    CBbeamType->setEnabled(true);
                if(!CB_hfov->isEnabled())
                    CB_hfov->setEnabled(true);
                if(!CB_aspectRatio->isEnabled())
                    CB_aspectRatio->setEnabled(true);
                if(!CBinputOrder->isEnabled())
                    CBinputOrder->setEnabled(true);
                if(!CBgridOption->isEnabled())
                    CBgridOption->setEnabled(true);
                if(!CBupscaleOrder->isEnabled())
                    CBupscaleOrder->setEnabled(true);
                if(!s_interpWidth->isEnabled())
                    s_interpWidth->setEnabled(true);
            }

            /* refresh the powermap display */
            if ((overlayIncluded != nullptr) && (hVst->getIsPlaying())) {
                float* dirs_deg, *pmap;
                int nDirs, pmapReady, pmapWidth, hfov;
                float aspectRatio;
                pmapReady = dirass_getPmap(hDir, &dirs_deg, &pmap, &nDirs, &pmapWidth, &hfov, &aspectRatio);
                overlayIncluded->setEnableTransparency(CB_webcam->getSelectedId() > 1 ? true : false);
                if(pmapReady){
                    overlayIncluded->refreshPowerMap(dirs_deg, pmap, nDirs, pmapWidth, hfov, aspectRatio);
                }
                if(overlayIncluded->getFinishedRefresh()){
                    dirass_requestPmapUpdate(hDir);
                }
            }

            /* display warning message, if needed */
            if ( !((dirass_getSamplingRate(hDir) == 44.1e3) || (dirass_getSamplingRate(hDir) == 48e3)) ){
                currentWarning = k_warning_supported_fs;
                repaint(0,0,getWidth(),32);
            }
            else if ((hVst->getCurrentNumInputs() < dirass_getNSHrequired(hDir))){
                currentWarning = k_warning_NinputCH;
                repaint(0,0,getWidth(),32);
            }
            else if(currentWarning){
                currentWarning = k_warning_none;
                repaint(0,0,getWidth(),32);
            }
            break;
    }
}

void PluginEditor::cameraChanged()
{
    cameraDevice.reset();
    cameraPreviewComp.reset();

    if (CB_webcam->getSelectedId() > 1)
        cameraDeviceOpenResult (CameraDevice::openDevice (CB_webcam->getSelectedId() - 2), {});
    else
        resized();
}

void PluginEditor::cameraDeviceOpenResult (CameraDevice* device, const String& /*error*/)
{
    cameraDevice.reset (device);

    if (cameraDevice.get() != nullptr) {
        cameraPreviewComp.reset (cameraDevice->createViewerComponent());
        addAndMakeVisible (cameraPreviewComp.get());
        cameraPreviewComp->setAlwaysOnTop(false);
    }
    resized();
}

void PluginEditor::updateCameraList()
{
    CB_webcam->clear();
    CB_webcam->addItem("No camera", 1);
    CB_webcam->addSeparator();

    auto cameras = CameraDevice::getAvailableDevices();

    for (int i = 0; i < cameras.size(); ++i)
        CB_webcam->addItem(cameras[i], i + 2);
    CB_webcam->setSelectedId(1);
}

void PluginEditor::imageReceived(const Image& image)
{
    if (! image.isValid())
        return;
    Image newImage = image;

    if(TB_greyScale->getToggleState())
        newImage.desaturate();

    incomingImage = newImage;
}

void PluginEditor::handleAsyncUpdate()
{
    if (cameraDevice != nullptr){
        SafePointer<PluginEditor> safeThis (this);
        cameraDevice->takeStillPicture ([safeThis] (const Image& image) mutable { safeThis->imageReceived (image); });
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
                 parentClasses="public AudioProcessorEditor, public MultiTimer, private CameraDevice::Listener, public AsyncUpdater"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter), progressbar(progress)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="672" initialHeight="542">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 286 672 256" fill="linear: 8 544, 8 448, 0=ff19313f, 1=ff041519"
          hasStroke="0"/>
    <RECT pos="0 30 672 256" fill="linear: 8 32, 8 104, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <ROUNDRECT pos="1 2 670 31" cornerSize="5.0" fill="linear: 0 32, 656 24, 0=ff041518, 1=ff19313f"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="13 394 450 138" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="242 394 221 36" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 35a0a0a0"/>
    <RECT pos="13 394 230 36" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 35a0a0a0"/>
    <RECT pos="12 58 648 325" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="22 397 132 30" fill="solid: ffffffff" hasStroke="0" text="Input Order:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="22 497 132 30" fill="solid: ffffffff" hasStroke="0" text="Format:"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="250 465 132 30" fill="solid: ffffffff" hasStroke="0" text="Average Coeff:"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="22 433 132 30" fill="solid: ffffffff" hasStroke="0" text="Beam Type:"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="22 465 132 30" fill="solid: ffffffff" hasStroke="0" text="Scanning Grid:"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="472 394 186 138" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="481 399 132 30" fill="solid: ffffffff" hasStroke="0" text="Horiz. FOV:"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="481 432 132 30" fill="solid: ffffffff" hasStroke="0" text="Aspect Ratio:"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 112 32" fill="solid: ffb0a6e7" hasStroke="0" text="DirASS"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="481 465 152 30" fill="solid: ffffffff" hasStroke="0" text="Min Freq (Hz):"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="481 497 104 30" fill="solid: ffffffff" hasStroke="0" text="Max Freq (Hz):"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="250 433 132 30" fill="solid: ffffffff" hasStroke="0" text="Upscale Order:"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="250 397 181 30" fill="solid: ffffffff" hasStroke="0" text="DirASS Mode:"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="250 497 132 30" fill="solid: ffffffff" hasStroke="0" text="Width (pixels):"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="624 32 29 30" fill="solid: ffffffff" hasStroke="0" text="GS:"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="576 32 37 30" fill="solid: ffffffff" hasStroke="0" text="U|D:"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="530 32 37 30" fill="solid: ffffffff" hasStroke="0" text="L|R:"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="283 33 125 30" fill="solid: ffffffff" hasStroke="0" text="Display Window"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 674 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 540 674 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 540" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="670 0 2 540" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
  </BACKGROUND>
  <COMBOBOX name="" id="787134d7259eea10" memberName="CBbeamType" virtualName=""
            explicitFocusOrder="0" pos="121 440 112 18" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <COMBOBOX name="new combo box" id="a36915795f16ceb6" memberName="CBchFormat"
            virtualName="" explicitFocusOrder="0" pos="90 504 66 18" editable="0"
            layout="33" items="" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="e10be54628a6df43" memberName="CBnormScheme"
            virtualName="" explicitFocusOrder="0" pos="161 504 71 18" editable="0"
            layout="33" items="" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="" id="e69fd08ce7960e5e" memberName="CB_hfov" virtualName=""
            explicitFocusOrder="0" pos="584 406 66 18" editable="0" layout="33"
            items="" textWhenNonSelected="360" textWhenNoItems=""/>
  <COMBOBOX name="" id="757b635652d2e8ab" memberName="CB_aspectRatio" virtualName=""
            explicitFocusOrder="0" pos="584 438 66 18" editable="0" layout="33"
            items="" textWhenNonSelected="2:1" textWhenNoItems=""/>
  <SLIDER name="new slider" id="d9acd6687ea4c8b5" memberName="SLmapAvg"
          virtualName="" explicitFocusOrder="0" pos="349 468 104 24" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.0" max="1.0" int="0.01" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="a465903000494955" memberName="CBinputOrder"
            virtualName="" explicitFocusOrder="0" pos="121 403 112 18" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="905f4ab0adab1f4f" memberName="s_minFreq"
          virtualName="" explicitFocusOrder="0" pos="592 469 58 24" min="0.0"
          max="24000.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="45" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="3aad5000f228ef1b" memberName="s_maxFreq"
          virtualName="" explicitFocusOrder="0" pos="592 500 58 24" min="0.0"
          max="24000.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="45" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="" id="6daf8adec965e9f2" memberName="CBgridOption" virtualName=""
            explicitFocusOrder="0" pos="121 472 112 18" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <COMBOBOX name="new combo box" id="5fec20e10170996c" memberName="CBupscaleOrder"
            virtualName="" explicitFocusOrder="0" pos="354 440 99 18" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="580b96da4b9f34a6" memberName="CBdirassMode"
            virtualName="" explicitFocusOrder="0" pos="354 403 99 18" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="79f6fe93d6735ce3" memberName="s_interpWidth"
          virtualName="" explicitFocusOrder="0" pos="368 500 85 24" min="64.0"
          max="256.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="45" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="" id="974f5da4ceed6bb6" memberName="CB_webcam" virtualName=""
            explicitFocusOrder="0" pos="434 38 92 17" editable="0" layout="33"
            items="" textWhenNonSelected="" textWhenNoItems=""/>
  <TOGGLEBUTTON name="new toggle button" id="78ff43e4ccfdc462" memberName="TB_greyScale"
                virtualName="" explicitFocusOrder="0" pos="639 35 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="f4031e45e07a36d" memberName="TB_flipUD"
                virtualName="" explicitFocusOrder="0" pos="598 35 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="bb60feb319e3e7d4" memberName="TB_flipLR"
                virtualName="" explicitFocusOrder="0" pos="550 35 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

