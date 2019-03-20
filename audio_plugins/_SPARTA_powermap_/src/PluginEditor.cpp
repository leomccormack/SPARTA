/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

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

    CBpmap_method.reset (new ComboBox (String()));
    addAndMakeVisible (CBpmap_method.get());
    CBpmap_method->setEditableText (false);
    CBpmap_method->setJustificationType (Justification::centredLeft);
    CBpmap_method->setTextWhenNothingSelected (TRANS("Default"));
    CBpmap_method->setTextWhenNoChoicesAvailable (String());
    CBpmap_method->addListener (this);

    CBpmap_method->setBounds (106, 512, 112, 20);

    CBsourcePreset.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBsourcePreset.get());
    CBsourcePreset->setEditableText (false);
    CBsourcePreset->setJustificationType (Justification::centredLeft);
    CBsourcePreset->setTextWhenNothingSelected (TRANS("Default"));
    CBsourcePreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBsourcePreset->addListener (this);

    CBsourcePreset->setBounds (106, 439, 112, 20);

    CBchFormat.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (Justification::centredLeft);
    CBchFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBchFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBchFormat->addListener (this);

    CBchFormat->setBounds (80, 472, 66, 20);

    CBnormScheme.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (Justification::centredLeft);
    CBnormScheme->setTextWhenNothingSelected (TRANS("N3D"));
    CBnormScheme->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnormScheme->addListener (this);

    CBnormScheme->setBounds (151, 472, 67, 20);

    s_anaOrder.reset (new Slider ("new slider"));
    addAndMakeVisible (s_anaOrder.get());
    s_anaOrder->setRange (0, 1, 1);
    s_anaOrder->setSliderStyle (Slider::LinearVertical);
    s_anaOrder->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    s_anaOrder->setColour (Slider::textBoxTextColourId, Colours::white);
    s_anaOrder->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_anaOrder->addListener (this);

    s_anaOrder->setBounds (608, 552, 40, 80);

    s_pmapEQ.reset (new Slider ("new slider"));
    addAndMakeVisible (s_pmapEQ.get());
    s_pmapEQ->setRange (0, 2, 0.01);
    s_pmapEQ->setSliderStyle (Slider::LinearVertical);
    s_pmapEQ->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    s_pmapEQ->setColour (Slider::textBoxTextColourId, Colours::white);
    s_pmapEQ->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_pmapEQ->addListener (this);

    s_pmapEQ->setBounds (608, 448, 40, 80);

    s_covAvg.reset (new Slider ("new slider"));
    addAndMakeVisible (s_covAvg.get());
    s_covAvg->setRange (0, 1, 0.01);
    s_covAvg->setSliderStyle (Slider::LinearHorizontal);
    s_covAvg->setTextBoxStyle (Slider::TextBoxRight, false, 50, 20);
    s_covAvg->setColour (Slider::textBoxTextColourId, Colours::white);
    s_covAvg->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_covAvg->addListener (this);

    s_covAvg->setBounds (106, 608, 112, 24);

    s_Nsources.reset (new Slider ("new slider"));
    addAndMakeVisible (s_Nsources.get());
    s_Nsources->setRange (1, 8, 1);
    s_Nsources->setSliderStyle (Slider::LinearHorizontal);
    s_Nsources->setTextBoxStyle (Slider::TextBoxRight, false, 50, 20);
    s_Nsources->setColour (Slider::textBoxTextColourId, Colours::white);
    s_Nsources->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_Nsources->addListener (this);

    s_Nsources->setBounds (168, 546, 50, 20);

    CB_hfov.reset (new ComboBox (String()));
    addAndMakeVisible (CB_hfov.get());
    CB_hfov->setEditableText (false);
    CB_hfov->setJustificationType (Justification::centredLeft);
    CB_hfov->setTextWhenNothingSelected (TRANS("Default"));
    CB_hfov->setTextWhenNoChoicesAvailable (String());
    CB_hfov->addListener (this);

    CB_hfov->setBounds (357, 406, 96, 20);

    CB_aspectRatio.reset (new ComboBox (String()));
    addAndMakeVisible (CB_aspectRatio.get());
    CB_aspectRatio->setEditableText (false);
    CB_aspectRatio->setJustificationType (Justification::centredLeft);
    CB_aspectRatio->setTextWhenNothingSelected (TRANS("Default"));
    CB_aspectRatio->setTextWhenNoChoicesAvailable (String());
    CB_aspectRatio->addListener (this);

    CB_aspectRatio->setBounds (557, 406, 96, 20);

    s_pmapAvg.reset (new Slider ("new slider"));
    addAndMakeVisible (s_pmapAvg.get());
    s_pmapAvg->setRange (0, 1, 0.01);
    s_pmapAvg->setSliderStyle (Slider::LinearHorizontal);
    s_pmapAvg->setTextBoxStyle (Slider::TextBoxRight, false, 50, 20);
    s_pmapAvg->setColour (Slider::textBoxTextColourId, Colours::white);
    s_pmapAvg->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_pmapAvg->addListener (this);

    s_pmapAvg->setBounds (106, 576, 112, 24);

    CBmasterOrder.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBmasterOrder.get());
    CBmasterOrder->setEditableText (false);
    CBmasterOrder->setJustificationType (Justification::centredLeft);
    CBmasterOrder->setTextWhenNothingSelected (TRANS("Default"));
    CBmasterOrder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBmasterOrder->addListener (this);

    CBmasterOrder->setBounds (106, 407, 112, 20);

    CB_webcam.reset (new ComboBox (String()));
    addAndMakeVisible (CB_webcam.get());
    CB_webcam->setEditableText (false);
    CB_webcam->setJustificationType (Justification::centredLeft);
    CB_webcam->setTextWhenNothingSelected (String());
    CB_webcam->setTextWhenNoChoicesAvailable (String());
    CB_webcam->addListener (this);

    CB_webcam->setBounds (433, 39, 92, 17);

    TB_greyScale.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_greyScale.get());
    TB_greyScale->setButtonText (String());
    TB_greyScale->addListener (this);

    TB_greyScale->setBounds (638, 36, 24, 24);

    TB_flipUD.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipUD.get());
    TB_flipUD->setButtonText (String());
    TB_flipUD->addListener (this);

    TB_flipUD->setBounds (597, 36, 24, 24);

    TB_flipLR.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipLR.get());
    TB_flipLR->setButtonText (String());
    TB_flipLR->addListener (this);

    TB_flipLR->setBounds (549, 36, 24, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (672, 652);


    //[Constructor] You can add your own custom stuff here..

    /* handle for pluginProcessor */
	hVst = ownerFilter;

    /* OpenGL init */
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* remove slider bit of these sliders */
    s_Nsources->setColour(Slider::trackColourId, Colours::transparentBlack);
    s_Nsources->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    s_Nsources->setSliderSnapsToMousePosition(false);

    /* create 2d Sliders */
    int nPoints;
    float* pX_vector, *pY_values;
    int* pY_values_int;
    addAndMakeVisible (anaOrder2dSlider = new log2dSlider(360, 63, 100, 20e3, 1, powermap_getMasterOrder(hVst->hPm), 0));
    anaOrder2dSlider->setAlwaysOnTop(true);
    anaOrder2dSlider->setTopLeftPosition(248, 558);
    powermap_getAnaOrderHandle(hVst->hPm, &pX_vector, &pY_values_int, &nPoints);
    anaOrder2dSlider->setDataHandlesInt(pX_vector, pY_values_int, nPoints);

    addAndMakeVisible (pmapEQ2dSlider = new log2dSlider(360, 63, 100, 20e3, 0.0, 2.0, 3));
    pmapEQ2dSlider->setAlwaysOnTop(true);
    pmapEQ2dSlider->setTopLeftPosition(248, 454);
    powermap_getPowermapEQHandle(hVst->hPm, &pX_vector, &pY_values, &nPoints);
    pmapEQ2dSlider->setDataHandles(pX_vector, pY_values, nPoints);

    /* add master analysis order options */
    CBmasterOrder->addItem (TRANS("1st order"), MASTER_ORDER_FIRST);
    CBmasterOrder->addItem (TRANS("2nd order"), MASTER_ORDER_SECOND);
    CBmasterOrder->addItem (TRANS("3rd order"), MASTER_ORDER_THIRD);
    CBmasterOrder->addItem (TRANS("4th order"), MASTER_ORDER_FOURTH);
    CBmasterOrder->addItem (TRANS("5th order"), MASTER_ORDER_FIFTH);
    CBmasterOrder->addItem (TRANS("6th order"), MASTER_ORDER_SIXTH);
    CBmasterOrder->addItem (TRANS("7th order"), MASTER_ORDER_SEVENTH);

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
#ifdef ENABLE_ZYLIA_MIC_PRESET
    CBsourcePreset->addItem(TRANS("Zylia"), MIC_PRESET_ZYLIA);
#endif
#ifdef ENABLE_EIGENMIKE32_MIC_PRESET
    CBsourcePreset->addItem(TRANS("Eigenmike"), MIC_PRESET_EIGENMIKE32);
#endif
#ifdef ENABLE_DTU_MIC_MIC_PRESET
    CBsourcePreset->addItem(TRANS("DTU mic"), MIC_PRESET_DTU_MIC);
#endif

    /* Add the remaining options */
    CBchFormat->addItem(TRANS("ACN"), CH_ACN);
    CBnormScheme->addItem(TRANS("N3D"), NORM_N3D);
    CBnormScheme->addItem(TRANS("SN3D"), NORM_SN3D);
    CB_hfov->addItem(TRANS("360"), HFOV_360);
    CB_aspectRatio->addItem(TRANS("2:1"), ASPECT_RATIO_2_1);

    /* Overlay */
    previewArea.setBounds(13, 60, 646, 323);
    addAndMakeVisible (overlayIncluded = new overlay(ownerFilter));
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

    /* fetch current configuration */
    CBmasterOrder->setSelectedId(powermap_getMasterOrder(hVst->hPm), dontSendNotification);
    CBpmap_method->setSelectedId(powermap_getPowermapMode(hVst->hPm), dontSendNotification);
    s_covAvg->setValue(powermap_getCovAvgCoeff(hVst->hPm), dontSendNotification);
    s_pmapEQ->setValue(powermap_getPowermapEQAllBands(hVst->hPm), dontSendNotification);
    s_anaOrder->setRange(1, powermap_getMasterOrder(hVst->hPm), 1);
    s_anaOrder->setValue(powermap_getAnaOrderAllBands(hVst->hPm), dontSendNotification);
    CBchFormat->setSelectedId(powermap_getChOrder(hVst->hPm), dontSendNotification);
    CBnormScheme->setSelectedId(powermap_getNormType(hVst->hPm), dontSendNotification);
    s_Nsources->setRange(1, (int)((float)powermap_getNSHrequired(hVst->hPm)/2.0f), 1);
    s_Nsources->setValue(powermap_getNumSources(hVst->hPm), dontSendNotification);
    s_Nsources->setEnabled((powermap_getPowermapMode(hVst->hPm)==PM_MODE_MINNORM ||
                            powermap_getPowermapMode(hVst->hPm)==PM_MODE_MUSIC) ? true : false);
    CB_hfov->setSelectedId(powermap_getDispFOV(hVst->hPm), dontSendNotification);
    CB_aspectRatio->setSelectedId(powermap_getAspectRatio(hVst->hPm), dontSendNotification);
    s_pmapAvg->setValue(powermap_getPowermapAvgCoeff(hVst->hPm), dontSendNotification);
    resolutionHasChanged = false;

	/* Specify screen refresh rate */
    startTimer(120);//80); /*ms (40ms = 25 frames per second) */

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
    overlayIncluded = nullptr;
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    {
        int x = 0, y = 30, width = 672, height = 622;
        Colour fillColour1 = Colour (0xff5b6d76), fillColour2 = Colour (0xff073642);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       336.0f - 0.0f + x,
                                       208.0f - 30.0f + y,
                                       fillColour2,
                                       360.0f - 0.0f + x,
                                       552.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 13, y = 398, width = 214, height = 107;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 13, y = 504, width = 214, height = 136;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 0, y = 0, width = 672, height = 32;
        Colour fillColour = Colour (0xff073642);
        Colour strokeColour = Colour (0xdcbdbdbd);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 3);

    }

    {
        int x = 12, y = 59, width = 648, height = 325;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 23, y = 402, width = 132, height = 30;
        String text (TRANS("Max Order:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 23, y = 466, width = 132, height = 30;
        String text (TRANS("Format:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 23, y = 434, width = 132, height = 30;
        String text (TRANS("Mic Preset:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 236, y = 536, width = 424, height = 105;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 243, y = 532, width = 325, height = 30;
        String text (TRANS("Analysis Order Per Frequency Band"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 243, y = 614, width = 37, height = 30;
        String text (TRANS("100"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 398, y = 614, width = 37, height = 30;
        String text (TRANS("1k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 552, y = 614, width = 37, height = 30;
        String text (TRANS("10k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 434, y = 614, width = 93, height = 30;
        String text (TRANS("Frequency (Hz)"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 595, y = 614, width = 37, height = 30;
        String text (TRANS("20k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 643, y = 606, width = 13, height = 30;
        String text (TRANS("1"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 236, y = 432, width = 424, height = 105;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 243, y = 428, width = 133, height = 30;
        String text (TRANS("Equalisation"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 243, y = 510, width = 37, height = 30;
        String text (TRANS("100"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 398, y = 510, width = 37, height = 30;
        String text (TRANS("1k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 552, y = 510, width = 37, height = 30;
        String text (TRANS("10k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 434, y = 510, width = 93, height = 30;
        String text (TRANS("Frequency (Hz)"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 595, y = 510, width = 37, height = 30;
        String text (TRANS("20k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 643, y = 502, width = 13, height = 30;
        String text (TRANS("0"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 23, y = 571, width = 132, height = 30;
        String text (TRANS("Map Avg:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 23, y = 507, width = 132, height = 30;
        String text (TRANS("Map Mode:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 23, y = 603, width = 132, height = 30;
        String text (TRANS("Cov. Avg:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 643, y = 443, width = 13, height = 30;
        String text (TRANS("2"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 643, y = 473, width = 13, height = 30;
        String text (TRANS("1"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 23, y = 540, width = 153, height = 30;
        String text (TRANS("Number of Sources:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 236, y = 398, width = 424, height = 35;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 243, y = 400, width = 132, height = 30;
        String text (TRANS("Horizontal FOV:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 456, y = 400, width = 132, height = 30;
        String text (TRANS("Aspect Ratio:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 13, y = 398, width = 214, height = 36;
        Colour fillColour = Colour (0x08f4f4f4);
        Colour strokeColour = Colour (0x35a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 13, y = 504, width = 214, height = 36;
        Colour fillColour = Colour (0x08f4f4f4);
        Colour strokeColour = Colour (0x33a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 16, y = 0, width = 100, height = 32;
        String text (TRANS("SPARTA|"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.80f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 92, y = 0, width = 112, height = 32;
        String text (TRANS("PowerMap"));
        Colour fillColour = Colour (0xfffffc08);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 624, y = 32, width = 29, height = 30;
        String text (TRANS("GS:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 576, y = 32, width = 37, height = 30;
        String text (TRANS("U|D:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 530, y = 32, width = 37, height = 30;
        String text (TRANS("L|R:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 283, y = 33, width = 125, height = 30;
        String text (TRANS("Display Window"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		195, 16, 530, 11,
		Justification::centredLeft, true);

    /* label for max ORDER */
    int x = 643, y = 530, width = 13, height = 30;
    String text  = String(powermap_getMasterOrder(hVst->hPm));
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
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(FRAME_SIZE),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(powermap_getSamplingRate(hVst->hPm)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(powermap_getNSHrequired(hVst->hPm)) + TRANS(")"),
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
    lastSnapshot.setBounds(previewArea);

    if (overlayIncluded != nullptr){
        overlayIncluded->setAlwaysOnTop(true);
        overlayIncluded->setBounds(previewArea);
        overlayIncluded->resized();
    }
	repaint();
    //[/UserResized]
}

void PluginEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBpmap_method.get())
    {
        //[UserComboBoxCode_CBpmap_method] -- add your combo box handling code here..
        powermap_setPowermapMode(hVst->hPm, CBpmap_method->getSelectedId());
        s_Nsources->setEnabled((powermap_getPowermapMode(hVst->hPm)==PM_MODE_MINNORM ||
                                powermap_getPowermapMode(hVst->hPm)==PM_MODE_MUSIC) ? true : false);
        //[/UserComboBoxCode_CBpmap_method]
    }
    else if (comboBoxThatHasChanged == CBsourcePreset.get())
    {
        //[UserComboBoxCode_CBsourcePreset] -- add your combo box handling code here..
        powermap_setSourcePreset(hVst->hPm, CBsourcePreset->getSelectedId());
		anaOrder2dSlider->setRefreshValuesFLAG(true);
		pmapEQ2dSlider->setRefreshValuesFLAG(true);
        //[/UserComboBoxCode_CBsourcePreset]
    }
    else if (comboBoxThatHasChanged == CBchFormat.get())
    {
        //[UserComboBoxCode_CBchFormat] -- add your combo box handling code here..
        powermap_setChOrder(hVst->hPm, CBchFormat->getSelectedId());
        //[/UserComboBoxCode_CBchFormat]
    }
    else if (comboBoxThatHasChanged == CBnormScheme.get())
    {
        //[UserComboBoxCode_CBnormScheme] -- add your combo box handling code here..
        powermap_setNormType(hVst->hPm, CBnormScheme->getSelectedId());
        //[/UserComboBoxCode_CBnormScheme]
    }
    else if (comboBoxThatHasChanged == CB_hfov.get())
    {
        //[UserComboBoxCode_CB_hfov] -- add your combo box handling code here..
        powermap_setDispFOV(hVst->hPm, CB_hfov->getSelectedId());
        //[/UserComboBoxCode_CB_hfov]
    }
    else if (comboBoxThatHasChanged == CB_aspectRatio.get())
    {
        //[UserComboBoxCode_CB_aspectRatio] -- add your combo box handling code here..
        powermap_setAspectRatio(hVst->hPm, CB_aspectRatio->getSelectedId());
        //[/UserComboBoxCode_CB_aspectRatio]
    }
    else if (comboBoxThatHasChanged == CBmasterOrder.get())
    {
        //[UserComboBoxCode_CBmasterOrder] -- add your combo box handling code here..
        powermap_setMasterOrder(hVst->hPm, CBmasterOrder->getSelectedId());
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

void PluginEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == s_anaOrder.get())
    {
        //[UserSliderCode_s_anaOrder] -- add your slider handling code here..
        powermap_setAnaOrderAllBands(hVst->hPm, (int)(s_anaOrder->getValue()+0.5));
		anaOrder2dSlider->setRefreshValuesFLAG(true);
        //[/UserSliderCode_s_anaOrder]
    }
    else if (sliderThatWasMoved == s_pmapEQ.get())
    {
        //[UserSliderCode_s_pmapEQ] -- add your slider handling code here..
        powermap_setPowermapEQAllBands(hVst->hPm, (s_pmapEQ->getValue()));
		pmapEQ2dSlider->setRefreshValuesFLAG(true);
        //[/UserSliderCode_s_pmapEQ]
    }
    else if (sliderThatWasMoved == s_covAvg.get())
    {
        //[UserSliderCode_s_covAvg] -- add your slider handling code here..
        powermap_setCovAvgCoeff(hVst->hPm, (float)s_covAvg->getValue());
        //[/UserSliderCode_s_covAvg]
    }
    else if (sliderThatWasMoved == s_Nsources.get())
    {
        //[UserSliderCode_s_Nsources] -- add your slider handling code here..
        powermap_setNumSources(hVst->hPm, (int)(s_Nsources->getValue()+0.5));
        //[/UserSliderCode_s_Nsources]
    }
    else if (sliderThatWasMoved == s_pmapAvg.get())
    {
        //[UserSliderCode_s_pmapAvg] -- add your slider handling code here..
        powermap_setPowermapAvgCoeff(hVst->hPm, (float)s_pmapAvg->getValue());
        //[/UserSliderCode_s_pmapAvg]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (Button* buttonThatWasClicked)
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
void PluginEditor::timerCallback()
{
    /* Nsource slider range */
    s_Nsources->setRange(1, (int)((float)powermap_getNSHrequired(hVst->hPm)/2.0f), 1);

#ifndef __APPLE__
	/* Some parameters shouldn't be enabled if playback is ongoing */
	if (hVst->getIsPlaying())
		CBmasterOrder->setEnabled(false);
	else {
		CBmasterOrder->setEnabled(true);
		powermap_checkReInit(hVst->hPm);
	}
#endif

    /* take webcam picture */
    if(CB_webcam->getSelectedId()>1){
        handleAsyncUpdate();
        if (incomingImage.isValid())
            lastSnapshot.setImage(incomingImage);
    }

    /* refresh the powermap display */
    if ((overlayIncluded != nullptr) && (hVst->isPlaying)) {
        float* dirs_deg, *pmap;
        int nDirs, pmapReady, pmapWidth, hfov, aspectRatio;
        pmapReady = powermap_getPmap(hVst->hPm, &dirs_deg, &pmap, &nDirs, &pmapWidth, &hfov, &aspectRatio);
        overlayIncluded->setEnableTransparency(CB_webcam->getSelectedId() > 1 ? true : false);
        if(pmapReady){
            overlayIncluded->refreshPowerMap(dirs_deg, pmap, nDirs, pmapWidth, hfov, aspectRatio);
        }
        if(overlayIncluded->getFinishedRefresh()){
            powermap_requestPmapUpdate(hVst->hPm);
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
    if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ( !((powermap_getSamplingRate(hVst->hPm) == 44.1e3) || (powermap_getSamplingRate(hVst->hPm) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < powermap_getNSHrequired(hVst->hPm))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}

void PluginEditor::cameraChanged()
{
    if (CB_webcam->getSelectedId() > 1)
        cameraDeviceOpenResult (CameraDevice::openDevice (CB_webcam->getSelectedId() - 2), {});
    else
        cameraDevice.reset ();
}

void PluginEditor::cameraDeviceOpenResult (CameraDevice* device, const String& error)
{
    cameraDevice.reset (device);
    resized();
}

void PluginEditor::updateCameraList()
{
    CB_webcam->clear();
    CB_webcam->addItem ("No camera", 1);
    CB_webcam->addSeparator();

    auto cameras = CameraDevice::getAvailableDevices();
    for (int i = 0; i < cameras.size(); ++i)
        CB_webcam->addItem (cameras[i], i + 2);
    CB_webcam->setSelectedId(1);
}


void PluginEditor::imageReceived(const Image& image)
{
    if (! image.isValid())
        return;
    Image newImage = image;

    /* L/R */
    if(TB_flipLR->getToggleState()){
        Image mirrorImage = newImage;
        Graphics g(mirrorImage);
        AffineTransform m_LR;
        m_LR = AffineTransform(-1, 0, mirrorImage.getWidth(),
                               0, 1, 0);
        g.drawImageTransformed(mirrorImage, m_LR);
        newImage = mirrorImage;
    }

    /* U/D */
    if(TB_flipUD->getToggleState()){
        Image mirrorImage = newImage;
        Graphics g(mirrorImage);
        AffineTransform m_UD;
        m_UD = AffineTransform(1, 0, 0,
                               0, -1, mirrorImage.getHeight());

        g.drawImageTransformed(mirrorImage, m_UD);
        newImage = mirrorImage;
    }

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
                 parentClasses="public AudioProcessorEditor, public Timer, private CameraDevice::Listener, public AsyncUpdater"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="672" initialHeight="652">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 672 622" fill=" radial: 336 208, 360 552, 0=ff5b6d76, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="13 398 214 107" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="13 504 214 136" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="0 0 672 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <RECT pos="12 59 648 325" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="23 402 132 30" fill="solid: ffffffff" hasStroke="0" text="Max Order:"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 466 132 30" fill="solid: ffffffff" hasStroke="0" text="Format:"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 434 132 30" fill="solid: ffffffff" hasStroke="0" text="Mic Preset:"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="236 536 424 105" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="243 532 325 30" fill="solid: ffffffff" hasStroke="0" text="Analysis Order Per Frequency Band"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="243 614 37 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="398 614 37 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="552 614 37 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="434 614 93 30" fill="solid: ffffffff" hasStroke="0" text="Frequency (Hz)"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="595 614 37 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="643 606 13 30" fill="solid: ffffffff" hasStroke="0" text="1"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="236 432 424 105" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="243 428 133 30" fill="solid: ffffffff" hasStroke="0" text="Equalisation"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="243 510 37 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="398 510 37 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="552 510 37 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="434 510 93 30" fill="solid: ffffffff" hasStroke="0" text="Frequency (Hz)"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="595 510 37 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="643 502 13 30" fill="solid: ffffffff" hasStroke="0" text="0"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 571 132 30" fill="solid: ffffffff" hasStroke="0" text="Map Avg:"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 507 132 30" fill="solid: ffffffff" hasStroke="0" text="Map Mode:"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 603 132 30" fill="solid: ffffffff" hasStroke="0" text="Cov. Avg:"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="643 443 13 30" fill="solid: ffffffff" hasStroke="0" text="2"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="643 473 13 30" fill="solid: ffffffff" hasStroke="0" text="1"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 540 153 30" fill="solid: ffffffff" hasStroke="0" text="Number of Sources:"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="236 398 424 35" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="243 400 132 30" fill="solid: ffffffff" hasStroke="0" text="Horizontal FOV:"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="456 400 132 30" fill="solid: ffffffff" hasStroke="0" text="Aspect Ratio:"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="13 398 214 36" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 35a0a0a0"/>
    <RECT pos="13 504 214 36" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 33a0a0a0"/>
    <TEXT pos="16 0 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="1.88e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 0 112 32" fill="solid: fffffc08" hasStroke="0" text="PowerMap"
          fontname="Default font" fontsize="1.8e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="624 32 29 30" fill="solid: ffffffff" hasStroke="0" text="GS:"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="576 32 37 30" fill="solid: ffffffff" hasStroke="0" text="U|D:"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="530 32 37 30" fill="solid: ffffffff" hasStroke="0" text="L|R:"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="283 33 125 30" fill="solid: ffffffff" hasStroke="0" text="Display Window"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
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
          virtualName="" explicitFocusOrder="0" pos="608 552 40 80" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0" max="1" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="new slider" id="48058a6b0227b38b" memberName="s_pmapEQ"
          virtualName="" explicitFocusOrder="0" pos="608 448 40 80" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0" max="2" int="1e-2" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="new slider" id="9f910fb3b8d0dcf3" memberName="s_covAvg"
          virtualName="" explicitFocusOrder="0" pos="106 608 112 24" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0" max="1" int="1e-2" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="50"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="new slider" id="2778ed8914910289" memberName="s_Nsources"
          virtualName="" explicitFocusOrder="0" pos="168 546 50 20" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="1" max="8" int="1" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="50"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <COMBOBOX name="" id="e69fd08ce7960e5e" memberName="CB_hfov" virtualName=""
            explicitFocusOrder="0" pos="357 406 96 20" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <COMBOBOX name="" id="757b635652d2e8ab" memberName="CB_aspectRatio" virtualName=""
            explicitFocusOrder="0" pos="557 406 96 20" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <SLIDER name="new slider" id="d9acd6687ea4c8b5" memberName="s_pmapAvg"
          virtualName="" explicitFocusOrder="0" pos="106 576 112 24" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0" max="1" int="1e-2" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="50"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="a465903000494955" memberName="CBmasterOrder"
            virtualName="" explicitFocusOrder="0" pos="106 407 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="" id="974f5da4ceed6bb6" memberName="CB_webcam" virtualName=""
            explicitFocusOrder="0" pos="433 39 92 17" editable="0" layout="33"
            items="" textWhenNonSelected="" textWhenNoItems=""/>
  <TOGGLEBUTTON name="new toggle button" id="78ff43e4ccfdc462" memberName="TB_greyScale"
                virtualName="" explicitFocusOrder="0" pos="638 36 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="f4031e45e07a36d" memberName="TB_flipUD"
                virtualName="" explicitFocusOrder="0" pos="597 36 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="bb60feb319e3e7d4" memberName="TB_flipLR"
                virtualName="" explicitFocusOrder="0" pos="549 36 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

