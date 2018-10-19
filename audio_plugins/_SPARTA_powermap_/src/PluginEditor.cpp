/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

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

    CBpmap_method->setBounds (106, 495, 112, 24);

    CBsourcePreset.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBsourcePreset.get());
    CBsourcePreset->setEditableText (false);
    CBsourcePreset->setJustificationType (Justification::centredLeft);
    CBsourcePreset->setTextWhenNothingSelected (TRANS("Default"));
    CBsourcePreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBsourcePreset->addListener (this);

    CBsourcePreset->setBounds (106, 423, 112, 20);

    CBchFormat.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (Justification::centredLeft);
    CBchFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBchFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBchFormat->addListener (this);

    CBchFormat->setBounds (80, 456, 66, 20);

    CBnormScheme.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (Justification::centredLeft);
    CBnormScheme->setTextWhenNothingSelected (TRANS("N3D"));
    CBnormScheme->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnormScheme->addListener (this);

    CBnormScheme->setBounds (151, 456, 67, 20);

    s_anaOrder.reset (new Slider ("new slider"));
    addAndMakeVisible (s_anaOrder.get());
    s_anaOrder->setRange (0, 1, 1);
    s_anaOrder->setSliderStyle (Slider::LinearVertical);
    s_anaOrder->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    s_anaOrder->setColour (Slider::textBoxTextColourId, Colours::white);
    s_anaOrder->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_anaOrder->addListener (this);

    s_anaOrder->setBounds (608, 536, 40, 80);

    s_pmapEQ.reset (new Slider ("new slider"));
    addAndMakeVisible (s_pmapEQ.get());
    s_pmapEQ->setRange (0, 2, 0.01);
    s_pmapEQ->setSliderStyle (Slider::LinearVertical);
    s_pmapEQ->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    s_pmapEQ->setColour (Slider::textBoxTextColourId, Colours::white);
    s_pmapEQ->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_pmapEQ->addListener (this);

    s_pmapEQ->setBounds (608, 432, 40, 80);

    s_covAvg.reset (new Slider ("new slider"));
    addAndMakeVisible (s_covAvg.get());
    s_covAvg->setRange (0, 1, 0.01);
    s_covAvg->setSliderStyle (Slider::LinearHorizontal);
    s_covAvg->setTextBoxStyle (Slider::TextBoxRight, false, 50, 20);
    s_covAvg->setColour (Slider::textBoxTextColourId, Colours::white);
    s_covAvg->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_covAvg->addListener (this);

    s_covAvg->setBounds (106, 592, 112, 24);

    s_Nsources.reset (new Slider ("new slider"));
    addAndMakeVisible (s_Nsources.get());
    s_Nsources->setRange (1, 8, 1);
    s_Nsources->setSliderStyle (Slider::LinearHorizontal);
    s_Nsources->setTextBoxStyle (Slider::TextBoxRight, false, 50, 20);
    s_Nsources->setColour (Slider::textBoxTextColourId, Colours::white);
    s_Nsources->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_Nsources->addListener (this);

    s_Nsources->setBounds (106, 528, 112, 24);

    CB_hfov.reset (new ComboBox (String()));
    addAndMakeVisible (CB_hfov.get());
    CB_hfov->setEditableText (false);
    CB_hfov->setJustificationType (Justification::centredLeft);
    CB_hfov->setTextWhenNothingSelected (TRANS("Default"));
    CB_hfov->setTextWhenNoChoicesAvailable (String());
    CB_hfov->addListener (this);

    CB_hfov->setBounds (357, 388, 96, 24);

    CB_aspectRatio.reset (new ComboBox (String()));
    addAndMakeVisible (CB_aspectRatio.get());
    CB_aspectRatio->setEditableText (false);
    CB_aspectRatio->setJustificationType (Justification::centredLeft);
    CB_aspectRatio->setTextWhenNothingSelected (TRANS("Default"));
    CB_aspectRatio->setTextWhenNoChoicesAvailable (String());
    CB_aspectRatio->addListener (this);

    CB_aspectRatio->setBounds (557, 388, 96, 24);

    s_pmapAvg.reset (new Slider ("new slider"));
    addAndMakeVisible (s_pmapAvg.get());
    s_pmapAvg->setRange (0, 1, 0.01);
    s_pmapAvg->setSliderStyle (Slider::LinearHorizontal);
    s_pmapAvg->setTextBoxStyle (Slider::TextBoxRight, false, 50, 20);
    s_pmapAvg->setColour (Slider::textBoxTextColourId, Colours::white);
    s_pmapAvg->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_pmapAvg->addListener (this);

    s_pmapAvg->setBounds (106, 560, 112, 24);

    CBmasterOrder.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBmasterOrder.get());
    CBmasterOrder->setEditableText (false);
    CBmasterOrder->setJustificationType (Justification::centredLeft);
    CBmasterOrder->setTextWhenNothingSelected (TRANS("Default"));
    CBmasterOrder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBmasterOrder->addListener (this);

    CBmasterOrder->setBounds (106, 391, 112, 20);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (672, 638);


    //[Constructor] You can add your own custom stuff here..

    /* handle for pluginProcessor */
	hVst = ownerFilter;

    /* OpenGL init */
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* create 2d Sliders */
    int nPoints;
    float* pX_vector, *pY_values;
    int* pY_values_int;
    addAndMakeVisible (anaOrder2dSlider = new log2dSlider(360, 63, 100, 20e3, 1, powermap_getMasterOrder(hVst->hPm), 0));
    anaOrder2dSlider->setAlwaysOnTop(true);
    anaOrder2dSlider->setTopLeftPosition(248, 543);
    powermap_getAnaOrderHandle(hVst->hPm, &pX_vector, &pY_values_int, &nPoints);
    anaOrder2dSlider->setDataHandlesInt(pX_vector, pY_values_int, nPoints);

    addAndMakeVisible (pmapEQ2dSlider = new log2dSlider(360, 63, 100, 20e3, 0.0, 2.0, 3));
    pmapEQ2dSlider->setAlwaysOnTop(true);
    pmapEQ2dSlider->setTopLeftPosition(248, 439);
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
    previewArea.setBounds(13, 44, 646, 323);
    addAndMakeVisible (overlayIncluded = new overlay(ownerFilter));
    overlayIncluded->setAlwaysOnTop(true);
    overlayIncluded->setBounds(previewArea);

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
        int x = 0, y = 30, width = 672, height = 608;
        Colour fillColour1 = Colour (0xff839496), fillColour2 = Colour (0xff073642);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       336.0f - 0.0f + x,
                                       208.0f - 30.0f + y,
                                       fillColour2,
                                       344.0f - 0.0f + x,
                                       608.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 13, y = 382, width = 214, height = 107;
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
        int x = 13, y = 488, width = 214, height = 136;
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
        int x = 12, y = 43, width = 648, height = 325;
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
        int x = -19, y = 0, width = 195, height = 32;
        String text (TRANS("PowerMap"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.80f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 23, y = 386, width = 132, height = 30;
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
        int x = 23, y = 450, width = 132, height = 30;
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
        int x = 23, y = 418, width = 132, height = 30;
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
        int x = 236, y = 520, width = 424, height = 105;
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
        int x = 243, y = 516, width = 325, height = 30;
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
        int x = 243, y = 598, width = 37, height = 30;
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
        int x = 398, y = 598, width = 37, height = 30;
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
        int x = 552, y = 598, width = 37, height = 30;
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
        int x = 434, y = 598, width = 93, height = 30;
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
        int x = 595, y = 598, width = 37, height = 30;
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
        int x = 643, y = 590, width = 13, height = 30;
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
        int x = 236, y = 416, width = 424, height = 105;
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
        int x = 243, y = 412, width = 133, height = 30;
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
        int x = 243, y = 494, width = 37, height = 30;
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
        int x = 398, y = 494, width = 37, height = 30;
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
        int x = 552, y = 494, width = 37, height = 30;
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
        int x = 434, y = 494, width = 93, height = 30;
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
        int x = 595, y = 494, width = 37, height = 30;
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
        int x = 643, y = 486, width = 13, height = 30;
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
        int x = 23, y = 555, width = 132, height = 30;
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
        int x = 23, y = 491, width = 132, height = 30;
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
        int x = 23, y = 587, width = 132, height = 30;
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
        int x = 643, y = 427, width = 13, height = 30;
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
        int x = 643, y = 457, width = 13, height = 30;
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
        int x = 23, y = 524, width = 132, height = 30;
        String text (TRANS("N Sources:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 236, y = 382, width = 424, height = 35;
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
        int x = 243, y = 384, width = 132, height = 30;
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
        int x = 456, y = 384, width = 132, height = 30;
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
        int x = 13, y = 382, width = 214, height = 36;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x35a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 13, y = 488, width = 214, height = 36;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x33a0a0a0);
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
		150, 16, 530, 11,
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



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* Nsource slider range */
    s_Nsources->setRange(1, (int)((float)powermap_getNSHrequired(hVst->hPm)/2.0f), 1);

	/* Some parameters shouldn't be enabled if playback is ongoing */
	if (hVst->getIsPlaying())
		CBmasterOrder->setEnabled(false);
	else {
		CBmasterOrder->setEnabled(true);
		powermap_checkReInit(hVst->hPm);
	}

    /* refresh the powermap display */
    if ((overlayIncluded != nullptr) && (hVst->isPlaying)) {
        float* dirs_deg, *pmap;
        int nDirs, pmapReady, pmapWidth, hfov, aspectRatio;
        pmapReady = powermap_getPmap(hVst->hPm, &dirs_deg, &pmap, &nDirs, &pmapWidth, &hfov, &aspectRatio);
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
    else if ((hVst->getCurrentNumInputs() < powermap_getNSHrequired(hVst->hPm))){
        currentWarning = k_warning_NinputCH;
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
                 variableInitialisers="AudioProcessorEditor(ownerFilter)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="672" initialHeight="638">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 672 608" fill=" radial: 336 208, 344 608, 0=ff839496, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="13 382 214 107" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="13 488 214 136" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="0 0 672 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <RECT pos="12 43 648 325" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="-19 0 195 32" fill="solid: ffffffff" hasStroke="0" text="PowerMap"
          fontname="Default font" fontsize="18.80000000000000071054" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="23 386 132 30" fill="solid: ffffffff" hasStroke="0" text="Max Order:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 450 132 30" fill="solid: ffffffff" hasStroke="0" text="Format:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 418 132 30" fill="solid: ffffffff" hasStroke="0" text="Mic Preset:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="236 520 424 105" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="243 516 325 30" fill="solid: ffffffff" hasStroke="0" text="Analysis Order Per Frequency Band"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="243 598 37 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="398 598 37 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="552 598 37 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="434 598 93 30" fill="solid: ffffffff" hasStroke="0" text="Frequency (Hz)"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="595 598 37 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="643 590 13 30" fill="solid: ffffffff" hasStroke="0" text="1"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="236 416 424 105" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="243 412 133 30" fill="solid: ffffffff" hasStroke="0" text="Equalisation"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="243 494 37 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="398 494 37 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="552 494 37 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="434 494 93 30" fill="solid: ffffffff" hasStroke="0" text="Frequency (Hz)"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="595 494 37 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="643 486 13 30" fill="solid: ffffffff" hasStroke="0" text="0"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 555 132 30" fill="solid: ffffffff" hasStroke="0" text="Map Avg:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 491 132 30" fill="solid: ffffffff" hasStroke="0" text="Map Mode:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 587 132 30" fill="solid: ffffffff" hasStroke="0" text="Cov. Avg:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="643 427 13 30" fill="solid: ffffffff" hasStroke="0" text="2"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="643 457 13 30" fill="solid: ffffffff" hasStroke="0" text="1"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 524 132 30" fill="solid: ffffffff" hasStroke="0" text="N Sources:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="236 382 424 35" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="243 384 132 30" fill="solid: ffffffff" hasStroke="0" text="Horizontal FOV:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="456 384 132 30" fill="solid: ffffffff" hasStroke="0" text="Aspect Ratio:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="13 382 214 36" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 35a0a0a0"/>
    <RECT pos="13 488 214 36" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 33a0a0a0"/>
  </BACKGROUND>
  <COMBOBOX name="" id="787134d7259eea10" memberName="CBpmap_method" virtualName=""
            explicitFocusOrder="0" pos="106 495 112 24" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <COMBOBOX name="new combo box" id="d83602bab6f1a999" memberName="CBsourcePreset"
            virtualName="" explicitFocusOrder="0" pos="106 423 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="a36915795f16ceb6" memberName="CBchFormat"
            virtualName="" explicitFocusOrder="0" pos="80 456 66 20" editable="0"
            layout="33" items="" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="e10be54628a6df43" memberName="CBnormScheme"
            virtualName="" explicitFocusOrder="0" pos="151 456 67 20" editable="0"
            layout="33" items="" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="50ea77f60aadeeca" memberName="s_anaOrder"
          virtualName="" explicitFocusOrder="0" pos="608 536 40 80" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0.00000000000000000000" max="1.00000000000000000000"
          int="1.00000000000000000000" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <SLIDER name="new slider" id="48058a6b0227b38b" memberName="s_pmapEQ"
          virtualName="" explicitFocusOrder="0" pos="608 432 40 80" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0.00000000000000000000" max="2.00000000000000000000"
          int="0.01000000000000000021" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <SLIDER name="new slider" id="9f910fb3b8d0dcf3" memberName="s_covAvg"
          virtualName="" explicitFocusOrder="0" pos="106 592 112 24" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0.00000000000000000000" max="1.00000000000000000000"
          int="0.01000000000000000021" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <SLIDER name="new slider" id="2778ed8914910289" memberName="s_Nsources"
          virtualName="" explicitFocusOrder="0" pos="106 528 112 24" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="1.00000000000000000000" max="8.00000000000000000000"
          int="1.00000000000000000000" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <COMBOBOX name="" id="e69fd08ce7960e5e" memberName="CB_hfov" virtualName=""
            explicitFocusOrder="0" pos="357 388 96 24" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <COMBOBOX name="" id="757b635652d2e8ab" memberName="CB_aspectRatio" virtualName=""
            explicitFocusOrder="0" pos="557 388 96 24" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <SLIDER name="new slider" id="d9acd6687ea4c8b5" memberName="s_pmapAvg"
          virtualName="" explicitFocusOrder="0" pos="106 560 112 24" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0.00000000000000000000" max="1.00000000000000000000"
          int="0.01000000000000000021" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="a465903000494955" memberName="CBmasterOrder"
            virtualName="" explicitFocusOrder="0" pos="106 391 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
