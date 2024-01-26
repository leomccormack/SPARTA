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

    CBpmap_method.reset (new juce::ComboBox (juce::String()));
    addAndMakeVisible (CBpmap_method.get());
    CBpmap_method->setEditableText (false);
    CBpmap_method->setJustificationType (juce::Justification::centredLeft);
    CBpmap_method->setTextWhenNothingSelected (TRANS("Default"));
    CBpmap_method->setTextWhenNoChoicesAvailable (juce::String());
    CBpmap_method->addListener (this);

    CBpmap_method->setBounds (106, 512, 112, 20);

    CBsourcePreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBsourcePreset.get());
    CBsourcePreset->setEditableText (false);
    CBsourcePreset->setJustificationType (juce::Justification::centredLeft);
    CBsourcePreset->setTextWhenNothingSelected (TRANS("Default"));
    CBsourcePreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBsourcePreset->addListener (this);

    CBsourcePreset->setBounds (106, 439, 112, 20);

    CBchFormat.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (juce::Justification::centredLeft);
    CBchFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBchFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBchFormat->addListener (this);

    CBchFormat->setBounds (80, 472, 66, 20);

    CBnormScheme.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (juce::Justification::centredLeft);
    CBnormScheme->setTextWhenNothingSelected (TRANS("N3D"));
    CBnormScheme->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnormScheme->addListener (this);

    CBnormScheme->setBounds (151, 472, 67, 20);

    s_anaOrder.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_anaOrder.get());
    s_anaOrder->setRange (0, 1, 1);
    s_anaOrder->setSliderStyle (juce::Slider::LinearVertical);
    s_anaOrder->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    s_anaOrder->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_anaOrder->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    s_anaOrder->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_anaOrder->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_anaOrder->addListener (this);

    s_anaOrder->setBounds (608, 552, 40, 80);

    s_pmapEQ.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_pmapEQ.get());
    s_pmapEQ->setRange (0, 2, 0.01);
    s_pmapEQ->setSliderStyle (juce::Slider::LinearVertical);
    s_pmapEQ->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    s_pmapEQ->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_pmapEQ->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    s_pmapEQ->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_pmapEQ->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_pmapEQ->addListener (this);

    s_pmapEQ->setBounds (608, 448, 40, 80);

    s_covAvg.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_covAvg.get());
    s_covAvg->setRange (0, 1, 0.01);
    s_covAvg->setSliderStyle (juce::Slider::LinearHorizontal);
    s_covAvg->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    s_covAvg->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_covAvg->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    s_covAvg->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_covAvg->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_covAvg->addListener (this);

    s_covAvg->setBounds (106, 608, 112, 24);

    s_Nsources.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_Nsources.get());
    s_Nsources->setRange (1, 8, 1);
    s_Nsources->setSliderStyle (juce::Slider::LinearHorizontal);
    s_Nsources->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    s_Nsources->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_Nsources->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_Nsources->addListener (this);

    s_Nsources->setBounds (168, 546, 50, 20);

    CB_hfov.reset (new juce::ComboBox (juce::String()));
    addAndMakeVisible (CB_hfov.get());
    CB_hfov->setEditableText (false);
    CB_hfov->setJustificationType (juce::Justification::centredLeft);
    CB_hfov->setTextWhenNothingSelected (TRANS("Default"));
    CB_hfov->setTextWhenNoChoicesAvailable (juce::String());
    CB_hfov->addListener (this);

    CB_hfov->setBounds (357, 406, 96, 20);

    CB_aspectRatio.reset (new juce::ComboBox (juce::String()));
    addAndMakeVisible (CB_aspectRatio.get());
    CB_aspectRatio->setEditableText (false);
    CB_aspectRatio->setJustificationType (juce::Justification::centredLeft);
    CB_aspectRatio->setTextWhenNothingSelected (TRANS("Default"));
    CB_aspectRatio->setTextWhenNoChoicesAvailable (juce::String());
    CB_aspectRatio->addListener (this);

    CB_aspectRatio->setBounds (557, 406, 96, 20);

    s_pmapAvg.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_pmapAvg.get());
    s_pmapAvg->setRange (0, 1, 0.01);
    s_pmapAvg->setSliderStyle (juce::Slider::LinearHorizontal);
    s_pmapAvg->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    s_pmapAvg->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_pmapAvg->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    s_pmapAvg->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_pmapAvg->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_pmapAvg->addListener (this);

    s_pmapAvg->setBounds (106, 576, 112, 24);

    CBmasterOrder.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBmasterOrder.get());
    CBmasterOrder->setEditableText (false);
    CBmasterOrder->setJustificationType (juce::Justification::centredLeft);
    CBmasterOrder->setTextWhenNothingSelected (TRANS("Default"));
    CBmasterOrder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBmasterOrder->addListener (this);

    CBmasterOrder->setBounds (106, 407, 112, 20);

    CB_webcam.reset (new juce::ComboBox (juce::String()));
    addAndMakeVisible (CB_webcam.get());
    CB_webcam->setEditableText (false);
    CB_webcam->setJustificationType (juce::Justification::centredLeft);
    CB_webcam->setTextWhenNothingSelected (juce::String());
    CB_webcam->setTextWhenNoChoicesAvailable (juce::String());
    CB_webcam->addListener (this);

    CB_webcam->setBounds (433, 39, 92, 17);

    TB_greyScale.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_greyScale.get());
    TB_greyScale->setButtonText (juce::String());
    TB_greyScale->addListener (this);

    TB_greyScale->setBounds (639, 36, 24, 24);

    TB_flipUD.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipUD.get());
    TB_flipUD->setButtonText (juce::String());
    TB_flipUD->addListener (this);

    TB_flipUD->setBounds (598, 36, 24, 24);

    TB_flipLR.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipLR.get());
    TB_flipLR->setButtonText (juce::String());
    TB_flipLR->addListener (this);

    TB_flipLR->setBounds (550, 36, 24, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (672, 652);


    //[Constructor] You can add your own custom stuff here..

    /* handle for pluginProcessor */
	hVst = ownerFilter;
    hPm = hVst->getFXHandle();

    /* OpenGL init */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    s_Nsources->setColour(Slider::trackColourId, Colours::transparentBlack);
    s_Nsources->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    s_Nsources->setSliderSnapsToMousePosition(false);

    /* create 2d Sliders */
    int nPoints;
    float* pX_vector, *pY_values;
    int* pY_values_int;
    anaOrder2dSlider.reset (new log2dSlider(360, 63, 100, 20e3, 1, powermap_getMasterOrder(hPm), 0));
    addAndMakeVisible (anaOrder2dSlider.get());
    anaOrder2dSlider->setAlwaysOnTop(true);
    anaOrder2dSlider->setTopLeftPosition(248, 558);
    powermap_getAnaOrderHandle(hPm, &pX_vector, &pY_values_int, &nPoints);
    anaOrder2dSlider->setDataHandlesInt(pX_vector, pY_values_int, nPoints);

    pmapEQ2dSlider.reset (new log2dSlider(360, 63, 100, 20e3, 0.0, 2.0, 3));
    addAndMakeVisible (pmapEQ2dSlider.get());
    pmapEQ2dSlider->setAlwaysOnTop(true);
    pmapEQ2dSlider->setTopLeftPosition(248, 454);
    powermap_getPowermapEQHandle(hPm, &pX_vector, &pY_values, &nPoints);
    pmapEQ2dSlider->setDataHandles(pX_vector, pY_values, nPoints);

    /* add master analysis order options */
    CBmasterOrder->addItem (TRANS("1st order"), SH_ORDER_FIRST);
    CBmasterOrder->addItem (TRANS("2nd order"), SH_ORDER_SECOND);
    CBmasterOrder->addItem (TRANS("3rd order"), SH_ORDER_THIRD);
    CBmasterOrder->addItem (TRANS("4th order"), SH_ORDER_FOURTH);
    CBmasterOrder->addItem (TRANS("5th order"), SH_ORDER_FIFTH);
    CBmasterOrder->addItem (TRANS("6th order"), SH_ORDER_SIXTH);
    CBmasterOrder->addItem (TRANS("7th order"), SH_ORDER_SEVENTH);
    CBmasterOrder->addItem (TRANS("8th order"), SH_ORDER_EIGHTH);
    CBmasterOrder->addItem (TRANS("9th order"), SH_ORDER_NINTH);
    CBmasterOrder->addItem (TRANS("10th order"), SH_ORDER_TENTH);

    /* Add powermap options */
    CBpmap_method->addItem (TRANS("PWD"), PM_MODE_PWD);
    CBpmap_method->addItem (TRANS("MVDR"), PM_MODE_MVDR);
    CBpmap_method->addItem (TRANS("CroPaC LCMV"), PM_MODE_CROPAC_LCMV);
    CBpmap_method->addItem (TRANS("MUSIC"), PM_MODE_MUSIC);
    CBpmap_method->addItem (TRANS("log(MUSIC)"), PM_MODE_MUSIC_LOG);
    CBpmap_method->addItem (TRANS("MinNorm"), PM_MODE_MINNORM);
    CBpmap_method->addItem (TRANS("log(MinNorm)"), PM_MODE_MINNORM_LOG);

    /* Add microphone preset options */
    CBsourcePreset->addItem(TRANS("Ideal SH"), MIC_PRESET_IDEAL);
    CBsourcePreset->addItem(TRANS("Zylia"), MIC_PRESET_ZYLIA);
    CBsourcePreset->addItem(TRANS("Eigenmike"), MIC_PRESET_EIGENMIKE32);
    CBsourcePreset->addItem(TRANS("DTU mic"), MIC_PRESET_DTU_MIC);

    /* Add the remaining options */
    CBchFormat->addItem(TRANS("ACN"), CH_ACN);
    CBchFormat->addItem(TRANS("FuMa"), CH_FUMA);
    CBnormScheme->addItem(TRANS("N3D"), NORM_N3D);
    CBnormScheme->addItem(TRANS("SN3D"), NORM_SN3D);
    CBnormScheme->addItem(TRANS("FuMa"), NORM_FUMA);
    CB_hfov->addItem(TRANS("360"), HFOV_360);
    CB_aspectRatio->addItem(TRANS("2:1"), ASPECT_RATIO_2_1);

    /* Overlay */
    previewArea.setBounds(13, 60, 646, 323);
	lastSnapshot.setBounds(previewArea);
    overlayIncluded.reset (new overlay(ownerFilter));
    addAndMakeVisible (overlayIncluded.get());
    overlayIncluded->setAlwaysOnTop(true);
    overlayIncluded->setBounds(previewArea);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

    /* Camera support */
    updateCameraList();
    CB_webcam->setSelectedId (hVst->getCameraID(), dontSendNotification);
    CB_webcam->onChange = [this] { cameraChanged(); };
    addAndMakeVisible (lastSnapshot);
    TB_greyScale->setToggleState(hVst->getGreyScale(), dontSendNotification);
    TB_flipLR->setToggleState(hVst->getFlipLR(), dontSendNotification);
    TB_flipUD->setToggleState(hVst->getFlipUD(), dontSendNotification);

    /* fetch current configuration */
    CBmasterOrder->setSelectedId(powermap_getMasterOrder(hPm), dontSendNotification);
    CBpmap_method->setSelectedId(powermap_getPowermapMode(hPm), dontSendNotification);
    s_covAvg->setValue(powermap_getCovAvgCoeff(hPm), dontSendNotification);
    s_pmapEQ->setValue(powermap_getPowermapEQAllBands(hPm), dontSendNotification);
    s_anaOrder->setRange(1, powermap_getMasterOrder(hPm)+0.1f, 1);
    s_anaOrder->setValue(powermap_getAnaOrderAllBands(hPm), dontSendNotification);
    CBchFormat->setSelectedId(powermap_getChOrder(hPm), dontSendNotification);
    CBnormScheme->setSelectedId(powermap_getNormType(hPm), dontSendNotification);
    s_Nsources->setRange(1, (int)((float)powermap_getNSHrequired(hPm)/2.0f), 1);
    s_Nsources->setValue(powermap_getNumSources(hPm), dontSendNotification);
    s_Nsources->setEnabled((powermap_getPowermapMode(hPm)==PM_MODE_MINNORM ||
                            powermap_getPowermapMode(hPm)==PM_MODE_MUSIC) ? true : false);
    CB_hfov->setSelectedId(powermap_getDispFOV(hPm), dontSendNotification);
    CB_aspectRatio->setSelectedId(powermap_getAspectRatio(hPm), dontSendNotification);
    s_pmapAvg->setValue(powermap_getPowermapAvgCoeff(hPm), dontSendNotification);
    resolutionHasChanged = false;
    CBchFormat->setItemEnabled(CH_FUMA, powermap_getMasterOrder(hPm)==SH_ORDER_FIRST ? true : false);
    CBnormScheme->setItemEnabled(NORM_FUMA, powermap_getMasterOrder(hPm)==SH_ORDER_FIRST ? true : false);

    /* tooltips */
    CBmasterOrder->setTooltip("Maximum analysis order (can be lower at different frequencies). Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals as input.");
    CBpmap_method->setTooltip("Activity-map method to use. Plane-wave decomposition (PWD) and minimum-variance distortion-less response (MVDR) options are examples of beamforming based approaches, where static (PWD) or adaptive (MVDR) beamformers are steered towards the grid directions, and the map is derived from their relative energy/power (hence PowerMap). Minimum norm (min-Norm) and Multiple-signal classification (MUSIC) are examples of subspace-based approaches, which operate on the noise or signal subspaces derived from truncating the eigen vectors extracted from the input covariance matrix, subsquently conducting the scanning in this sub-space. The truncation of the eigen-vector matrix is dependent on the number of sources.");
    CBchFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormScheme->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    s_anaOrder->setTooltip("This sets the analysis order for all frequencies. Use the 2-D slider to change the analysis order for specific frequencies.");
    s_pmapEQ->setTooltip("This sets the EQ value for all frequencies (so just a gain). Use the 2-D slider to change the gain for specific frequencies, thus adjusting the contribution of particular frequencies to the output activity-map.");
    CBsourcePreset->setTooltip("Presets for for various higher-order microphone arrays, which configure the frequency-dependent analysis order.");
    s_covAvg->setTooltip("Covariance matrix averaging coefficient (one-pole filter).");
    s_pmapAvg->setTooltip("Activity-map averaging coefficient (one-pole filter).");
    CB_webcam->setTooltip("Optionally, the video from a webcam may be streamed behind the activity-map; allowing for a make-shift acoustic camera. This is particularly effective when using, for example, a 360degree Ricoh Theta camera.");
    TB_greyScale->setTooltip("Sets the plug-in to display the webcam image in 'grey-scale'.");
    TB_flipUD->setTooltip("Flips the webcam image up-down, as it may be preferable to mount the camera upside-down on top of the microphone array; in order to bring the origin of the camera closer to that of the array.");
    TB_flipLR->setTooltip("Flips the webcam image left-right, as some webcams mirror the images taken.");
    CB_hfov->setTooltip("Horizontal field-of-view (FOV) options.");
    CB_aspectRatio->setTooltip("Aspect ratio options.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A plug-in that represents the relative sound energy, or the statistical likelihood of a source arriving at the receiving position from a particular direction using a colour gradient. Yellow indicates high sound energy/likelihood and blue indicates low sound energy/likelihood. The plug-in integrates a variety of different approaches, including: standard Plane-Wave Decomposition (PWD) beamformer-based, Minimum-Variance Distortionless Response (MVDR) beamformer-based, Multiple Signal Classification (MUSIC) pseudo-spectrum-based, and the Cross-Pattern Coherence (CroPaC) algorithm; all of which are written to operate on Ambisonic signals up to 7th order.\n\nNote that the analysis order per frequency band is also user definable, and presets for higher order microphone arrays have been included for convience (which provide some rough appropriate starting values). The plug-in utilises a 812 point uniformly-distributed spherical grid, which is then interpolated into a 2D powermap using amplitude-normalised VBAP gains (i.e. triangular interpolation). The plug-in also allows the user to place real-time video footage behind the activity-map, in order to create a make-shift acoustic camera."));
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

    CBpmap_method = nullptr;
    CBsourcePreset = nullptr;
    CBchFormat = nullptr;
    CBnormScheme = nullptr;
    s_anaOrder = nullptr;
    s_pmapEQ = nullptr;
    s_covAvg = nullptr;
    s_Nsources = nullptr;
    CB_hfov = nullptr;
    CB_aspectRatio = nullptr;
    s_pmapAvg = nullptr;
    CBmasterOrder = nullptr;
    CB_webcam = nullptr;
    TB_greyScale = nullptr;
    TB_flipUD = nullptr;
    TB_flipLR = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    setLookAndFeel(nullptr);
    overlayIncluded = nullptr;
    anaOrder2dSlider = nullptr;
    pmapEQ2dSlider = nullptr;
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 30, width = 672, height = 311;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             344.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             344.0f - 0.0f + x,
                                             120.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 1.0f, width = 670.0f, height = 32.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 1.0f + y,
                                             fillColour2,
                                             672.0f - 1.0f + x,
                                             32.0f - 1.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 0, y = 341, width = 672, height = 311;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             336.0f - 0.0f + x,
                                             656.0f - 341.0f + y,
                                             fillColour2,
                                             336.0f - 0.0f + x,
                                             568.0f - 341.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 13, y = 398, width = 214, height = 107;
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
        int x = 13, y = 504, width = 214, height = 136;
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
        int x = 12, y = 59, width = 648, height = 325;
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
        int x = 23, y = 402, width = 132, height = 30;
        juce::String text (TRANS("Max Order:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 23, y = 466, width = 132, height = 30;
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
        int x = 23, y = 434, width = 132, height = 30;
        juce::String text (TRANS("Mic Preset:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 236, y = 536, width = 424, height = 105;
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
        int x = 243, y = 532, width = 325, height = 30;
        juce::String text (TRANS("Analysis Order Per Frequency Band"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 243, y = 614, width = 37, height = 30;
        juce::String text (TRANS("100"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 398, y = 614, width = 37, height = 30;
        juce::String text (TRANS("1k"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 552, y = 614, width = 37, height = 30;
        juce::String text (TRANS("10k"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 434, y = 614, width = 93, height = 30;
        juce::String text (TRANS("Frequency (Hz)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 595, y = 614, width = 37, height = 30;
        juce::String text (TRANS("20k"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 643, y = 606, width = 13, height = 30;
        juce::String text (TRANS("1"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 236, y = 432, width = 424, height = 105;
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
        int x = 243, y = 428, width = 133, height = 30;
        juce::String text (TRANS("Equalisation"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 243, y = 510, width = 37, height = 30;
        juce::String text (TRANS("100"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 398, y = 510, width = 37, height = 30;
        juce::String text (TRANS("1k"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 552, y = 510, width = 37, height = 30;
        juce::String text (TRANS("10k"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 434, y = 510, width = 93, height = 30;
        juce::String text (TRANS("Frequency (Hz)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 595, y = 510, width = 37, height = 30;
        juce::String text (TRANS("20k"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 643, y = 502, width = 13, height = 30;
        juce::String text (TRANS("0"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 23, y = 571, width = 132, height = 30;
        juce::String text (TRANS("Map Avg:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 23, y = 507, width = 132, height = 30;
        juce::String text (TRANS("Map Mode:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 23, y = 603, width = 132, height = 30;
        juce::String text (TRANS("Cov. Avg:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 643, y = 443, width = 13, height = 30;
        juce::String text (TRANS("2"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 643, y = 473, width = 13, height = 30;
        juce::String text (TRANS("1"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 23, y = 540, width = 153, height = 30;
        juce::String text (TRANS("Number of Sources:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 236, y = 398, width = 424, height = 35;
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
        int x = 243, y = 400, width = 132, height = 30;
        juce::String text (TRANS("Horizontal FOV:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 456, y = 400, width = 132, height = 30;
        juce::String text (TRANS("Aspect Ratio:"));
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
        int x = 92, y = 1, width = 112, height = 32;
        juce::String text (TRANS("PowerMap"));
        juce::Colour fillColour = juce::Colour (0xfffffc08);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
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
        int x = 0, y = 0, width = 2, height = 652;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 670, y = 0, width = 2, height = 652;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 670, y = 0, width = 2, height = 652;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 650, width = 672, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 672, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 13, y = 398, width = 214, height = 36;
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
        int x = 13, y = 504, width = 214, height = 36;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x35a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		195, 16, 530, 11,
		Justification::centredLeft, true);

    /* label for max ORDER */
    int x = 641, y = 540, width = 21, height = 30;
    String text  = String(powermap_getMasterOrder(hPm));
    Colour fillColour = Colours::white;
    g.setColour (fillColour);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText (text, x, y, width, height,
                Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(powermap_getSamplingRate(hPm)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(powermap_getNSHrequired(hPm)) + TRANS(")"),
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

    if (comboBoxThatHasChanged == CBpmap_method.get())
    {
        //[UserComboBoxCode_CBpmap_method] -- add your combo box handling code here..
        powermap_setPowermapMode(hPm, CBpmap_method->getSelectedId());
        s_Nsources->setEnabled((powermap_getPowermapMode(hPm)==PM_MODE_MINNORM ||
                                powermap_getPowermapMode(hPm)==PM_MODE_MUSIC) ? true : false);
        //[/UserComboBoxCode_CBpmap_method]
    }
    else if (comboBoxThatHasChanged == CBsourcePreset.get())
    {
        //[UserComboBoxCode_CBsourcePreset] -- add your combo box handling code here..
        powermap_setSourcePreset(hPm, CBsourcePreset->getSelectedId());
		anaOrder2dSlider->setRefreshValuesFLAG(true);
		pmapEQ2dSlider->setRefreshValuesFLAG(true);
        //[/UserComboBoxCode_CBsourcePreset]
    }
    else if (comboBoxThatHasChanged == CBchFormat.get())
    {
        //[UserComboBoxCode_CBchFormat] -- add your combo box handling code here..
        powermap_setChOrder(hPm, CBchFormat->getSelectedId());
        //[/UserComboBoxCode_CBchFormat]
    }
    else if (comboBoxThatHasChanged == CBnormScheme.get())
    {
        //[UserComboBoxCode_CBnormScheme] -- add your combo box handling code here..
        powermap_setNormType(hPm, CBnormScheme->getSelectedId());
        //[/UserComboBoxCode_CBnormScheme]
    }
    else if (comboBoxThatHasChanged == CB_hfov.get())
    {
        //[UserComboBoxCode_CB_hfov] -- add your combo box handling code here..
        powermap_setDispFOV(hPm, CB_hfov->getSelectedId());
        //[/UserComboBoxCode_CB_hfov]
    }
    else if (comboBoxThatHasChanged == CB_aspectRatio.get())
    {
        //[UserComboBoxCode_CB_aspectRatio] -- add your combo box handling code here..
        powermap_setAspectRatio(hPm, CB_aspectRatio->getSelectedId());
        //[/UserComboBoxCode_CB_aspectRatio]
    }
    else if (comboBoxThatHasChanged == CBmasterOrder.get())
    {
        //[UserComboBoxCode_CBmasterOrder] -- add your combo box handling code here..
        powermap_setMasterOrder(hPm, CBmasterOrder->getSelectedId());
        anaOrder2dSlider->setYrange(1, CBmasterOrder->getSelectedId());
        anaOrder2dSlider->setRefreshValuesFLAG(true);
        s_anaOrder->setRange(1, CBmasterOrder->getSelectedId(), 1);
        s_anaOrder->setValue(CBmasterOrder->getSelectedId());
        repaint();
        //[/UserComboBoxCode_CBmasterOrder]
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

    if (sliderThatWasMoved == s_anaOrder.get())
    {
        //[UserSliderCode_s_anaOrder] -- add your slider handling code here..
        powermap_setAnaOrderAllBands(hPm, (int)(s_anaOrder->getValue()+0.5));
		anaOrder2dSlider->setRefreshValuesFLAG(true);
        //[/UserSliderCode_s_anaOrder]
    }
    else if (sliderThatWasMoved == s_pmapEQ.get())
    {
        //[UserSliderCode_s_pmapEQ] -- add your slider handling code here..
        powermap_setPowermapEQAllBands(hPm, (s_pmapEQ->getValue()));
		pmapEQ2dSlider->setRefreshValuesFLAG(true);
        //[/UserSliderCode_s_pmapEQ]
    }
    else if (sliderThatWasMoved == s_covAvg.get())
    {
        //[UserSliderCode_s_covAvg] -- add your slider handling code here..
        powermap_setCovAvgCoeff(hPm, (float)s_covAvg->getValue());
        //[/UserSliderCode_s_covAvg]
    }
    else if (sliderThatWasMoved == s_Nsources.get())
    {
        //[UserSliderCode_s_Nsources] -- add your slider handling code here..
        powermap_setNumSources(hPm, (int)(s_Nsources->getValue()+0.5));
        //[/UserSliderCode_s_Nsources]
    }
    else if (sliderThatWasMoved == s_pmapAvg.get())
    {
        //[UserSliderCode_s_pmapAvg] -- add your slider handling code here..
        powermap_setPowermapAvgCoeff(hPm, (float)s_pmapAvg->getValue());
        //[/UserSliderCode_s_pmapAvg]
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
            CBchFormat->setSelectedId(powermap_getChOrder(hPm), dontSendNotification);
            CBnormScheme->setSelectedId(powermap_getNormType(hPm), dontSendNotification);
            CBchFormat->setItemEnabled(CH_FUMA, powermap_getMasterOrder(hPm)==SH_ORDER_FIRST ? true : false);
            CBnormScheme->setItemEnabled(NORM_FUMA, powermap_getMasterOrder(hPm)==SH_ORDER_FIRST ? true : false);

            /* Nsource slider range */
            s_Nsources->setRange(1, (int)((float)powermap_getNSHrequired(hPm)/2.0f), 1);

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
            if(powermap_getCodecStatus(hPm)==CODEC_STATUS_INITIALISING){
                addAndMakeVisible(progressbar);
                progressbar.setAlwaysOnTop(true);
                progress = (double)powermap_getProgressBar0_1(hPm);
                char text[PROGRESSBARTEXT_CHAR_LENGTH];
                powermap_getProgressBarText(hPm, (char*)text);
                progressbar.setTextToDisplay(String(text));
            }
            else
                removeChildComponent(&progressbar);

            /* Some parameters shouldn't be editable during initialisation*/
            if(powermap_getCodecStatus(hPm)==CODEC_STATUS_INITIALISING){
                if(CB_hfov->isEnabled())
                    CB_hfov->setEnabled(false);
                if(CB_aspectRatio->isEnabled())
                    CB_aspectRatio->setEnabled(false);
                if(CBmasterOrder->isEnabled())
                    CBmasterOrder->setEnabled(false);
            }
            else{
                if(!CB_hfov->isEnabled())
                    CB_hfov->setEnabled(true);
                if(!CB_aspectRatio->isEnabled())
                    CB_aspectRatio->setEnabled(true);
                if(!CBmasterOrder->isEnabled())
                    CBmasterOrder->setEnabled(true);
            }

            /* refresh the powermap display */
            if ((overlayIncluded != nullptr) && (hVst->getIsPlaying())) {
                float* dirs_deg, *pmap;
                int nDirs, pmapReady, pmapWidth, hfov, aspectRatio;
                pmapReady = powermap_getPmap(hPm, &dirs_deg, &pmap, &nDirs, &pmapWidth, &hfov, &aspectRatio);
                overlayIncluded->setEnableTransparency(CB_webcam->getSelectedId() > 1 ? true : false);
                if(pmapReady){
                    overlayIncluded->refreshPowerMap(dirs_deg, pmap, nDirs, pmapWidth, hfov, aspectRatio);
                }
                if(overlayIncluded->getFinishedRefresh()){
                    powermap_requestPmapUpdate(hPm);
                }
            }

            /* refresh the 2d sliders */
            if (anaOrder2dSlider->getRefreshValuesFLAG()) {
                anaOrder2dSlider->repaint();
                anaOrder2dSlider->setRefreshValuesFLAG(false);
            }
            if (pmapEQ2dSlider->getRefreshValuesFLAG()) {
                pmapEQ2dSlider->repaint();
                pmapEQ2dSlider->setRefreshValuesFLAG(false);
            }

            /* display warning message, if needed */
            if ( !((powermap_getSamplingRate(hPm) == 44.1e3) || (powermap_getSamplingRate(hPm) == 48e3)) ){
                currentWarning = k_warning_supported_fs;
                repaint(0,0,getWidth(),32);
            }
            else if ((hVst->getCurrentNumInputs() < powermap_getNSHrequired(hPm))){
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
                 parentClasses="public AudioProcessorEditor, public MultiTimer, public AsyncUpdater, private CameraDevice::Listener"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter), progressbar(progress)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="672" initialHeight="652">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 672 311" fill="linear: 344 32, 344 120, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <ROUNDRECT pos="1 1 670 32" cornerSize="5.0" fill="linear: 0 32, 672 32, 0=ff041518, 1=ff19313f"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 341 672 311" fill="linear: 336 656, 336 568, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="13 398 214 107" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="13 504 214 136" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 59 648 325" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="23 402 132 30" fill="solid: ffffffff" hasStroke="0" text="Max Order:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 466 132 30" fill="solid: ffffffff" hasStroke="0" text="Format:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 434 132 30" fill="solid: ffffffff" hasStroke="0" text="Mic Preset:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="236 536 424 105" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="243 532 325 30" fill="solid: ffffffff" hasStroke="0" text="Analysis Order Per Frequency Band"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="243 614 37 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="398 614 37 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="552 614 37 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="434 614 93 30" fill="solid: ffffffff" hasStroke="0" text="Frequency (Hz)"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="595 614 37 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="643 606 13 30" fill="solid: ffffffff" hasStroke="0" text="1"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="236 432 424 105" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="243 428 133 30" fill="solid: ffffffff" hasStroke="0" text="Equalisation"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="243 510 37 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="398 510 37 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="552 510 37 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="434 510 93 30" fill="solid: ffffffff" hasStroke="0" text="Frequency (Hz)"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="595 510 37 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="643 502 13 30" fill="solid: ffffffff" hasStroke="0" text="0"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 571 132 30" fill="solid: ffffffff" hasStroke="0" text="Map Avg:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 507 132 30" fill="solid: ffffffff" hasStroke="0" text="Map Mode:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 603 132 30" fill="solid: ffffffff" hasStroke="0" text="Cov. Avg:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="643 443 13 30" fill="solid: ffffffff" hasStroke="0" text="2"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="643 473 13 30" fill="solid: ffffffff" hasStroke="0" text="1"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 540 153 30" fill="solid: ffffffff" hasStroke="0" text="Number of Sources:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="236 398 424 35" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="243 400 132 30" fill="solid: ffffffff" hasStroke="0" text="Horizontal FOV:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="456 400 132 30" fill="solid: ffffffff" hasStroke="0" text="Aspect Ratio:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 112 32" fill="solid: fffffc08" hasStroke="0" text="PowerMap"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
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
    <RECT pos="0 0 2 652" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="670 0 2 652" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="670 0 2 652" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 650 672 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 672 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="13 398 214 36" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 35a0a0a0"/>
    <RECT pos="13 504 214 36" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 35a0a0a0"/>
  </BACKGROUND>
  <COMBOBOX name="" id="787134d7259eea10" memberName="CBpmap_method" virtualName=""
            explicitFocusOrder="0" pos="106 512 112 20" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <COMBOBOX name="new combo box" id="d83602bab6f1a999" memberName="CBsourcePreset"
            virtualName="" explicitFocusOrder="0" pos="106 439 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="a36915795f16ceb6" memberName="CBchFormat"
            virtualName="" explicitFocusOrder="0" pos="80 472 66 20" editable="0"
            layout="33" items="" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="e10be54628a6df43" memberName="CBnormScheme"
            virtualName="" explicitFocusOrder="0" pos="151 472 67 20" editable="0"
            layout="33" items="" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="50ea77f60aadeeca" memberName="s_anaOrder"
          virtualName="" explicitFocusOrder="0" pos="608 552 40 80" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.0" max="1.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="48058a6b0227b38b" memberName="s_pmapEQ"
          virtualName="" explicitFocusOrder="0" pos="608 448 40 80" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.0" max="2.0" int="0.01" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="9f910fb3b8d0dcf3" memberName="s_covAvg"
          virtualName="" explicitFocusOrder="0" pos="106 608 112 24" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.0" max="1.0" int="0.01" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="2778ed8914910289" memberName="s_Nsources"
          virtualName="" explicitFocusOrder="0" pos="168 546 50 20" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="1.0" max="8.0" int="1.0" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="50"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="" id="e69fd08ce7960e5e" memberName="CB_hfov" virtualName=""
            explicitFocusOrder="0" pos="357 406 96 20" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <COMBOBOX name="" id="757b635652d2e8ab" memberName="CB_aspectRatio" virtualName=""
            explicitFocusOrder="0" pos="557 406 96 20" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <SLIDER name="new slider" id="d9acd6687ea4c8b5" memberName="s_pmapAvg"
          virtualName="" explicitFocusOrder="0" pos="106 576 112 24" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.0" max="1.0" int="0.01" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="a465903000494955" memberName="CBmasterOrder"
            virtualName="" explicitFocusOrder="0" pos="106 407 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="" id="974f5da4ceed6bb6" memberName="CB_webcam" virtualName=""
            explicitFocusOrder="0" pos="433 39 92 17" editable="0" layout="33"
            items="" textWhenNonSelected="" textWhenNoItems=""/>
  <TOGGLEBUTTON name="new toggle button" id="78ff43e4ccfdc462" memberName="TB_greyScale"
                virtualName="" explicitFocusOrder="0" pos="639 36 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="f4031e45e07a36d" memberName="TB_flipUD"
                virtualName="" explicitFocusOrder="0" pos="598 36 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="bb60feb319e3e7d4" memberName="TB_flipLR"
                virtualName="" explicitFocusOrder="0" pos="550 36 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

