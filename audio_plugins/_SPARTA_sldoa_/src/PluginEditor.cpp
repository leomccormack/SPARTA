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

    avgSlider.reset (new Slider ("new slider"));
    addAndMakeVisible (avgSlider.get());
    avgSlider->setRange (0, 2000, 0.1);
    avgSlider->setSliderStyle (Slider::LinearHorizontal);
    avgSlider->setTextBoxStyle (Slider::TextBoxRight, false, 45, 20);
    avgSlider->addListener (this);

    avgSlider->setBounds (80, 473, 118, 24);

    CB_CHorder.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CB_CHorder.get());
    CB_CHorder->setEditableText (false);
    CB_CHorder->setJustificationType (Justification::centredLeft);
    CB_CHorder->setTextWhenNothingSelected (TRANS("ACN"));
    CB_CHorder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CB_CHorder->addListener (this);

    CB_CHorder->setBounds (66, 447, 64, 18);

    CB_Norm.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CB_Norm.get());
    CB_Norm->setEditableText (false);
    CB_Norm->setJustificationType (Justification::centredLeft);
    CB_Norm->setTextWhenNothingSelected (TRANS("N3D"));
    CB_Norm->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CB_Norm->addListener (this);

    CB_Norm->setBounds (131, 447, 68, 18);

    slider_anaOrder.reset (new Slider ("new slider"));
    addAndMakeVisible (slider_anaOrder.get());
    slider_anaOrder->setRange (0, 1, 1);
    slider_anaOrder->setSliderStyle (Slider::LinearVertical);
    slider_anaOrder->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider_anaOrder->setColour (Slider::textBoxTextColourId, Colours::white);
    slider_anaOrder->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    slider_anaOrder->addListener (this);

    slider_anaOrder->setBounds (576, 424, 40, 66);

    CBinputTypePreset.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBinputTypePreset.get());
    CBinputTypePreset->setEditableText (false);
    CBinputTypePreset->setJustificationType (Justification::centredLeft);
    CBinputTypePreset->setTextWhenNothingSelected (TRANS("Default"));
    CBinputTypePreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBinputTypePreset->addItem (TRANS("Ideal SH"), 1);
    CBinputTypePreset->addListener (this);

    CBinputTypePreset->setBounds (96, 417, 103, 18);

    s_minFreq.reset (new Slider ("new slider"));
    addAndMakeVisible (s_minFreq.get());
    s_minFreq->setRange (0, 24000, 1);
    s_minFreq->setSliderStyle (Slider::LinearHorizontal);
    s_minFreq->setTextBoxStyle (Slider::TextBoxRight, false, 45, 20);
    s_minFreq->addListener (this);

    s_minFreq->setBounds (352, 382, 56, 20);

    s_maxFreq.reset (new Slider ("new slider"));
    addAndMakeVisible (s_maxFreq.get());
    s_maxFreq->setRange (0, 24000, 1);
    s_maxFreq->setSliderStyle (Slider::LinearHorizontal);
    s_maxFreq->setTextBoxStyle (Slider::TextBoxRight, false, 45, 20);
    s_maxFreq->addListener (this);

    s_maxFreq->setBounds (560, 382, 56, 20);

    CBmasterOrder.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBmasterOrder.get());
    CBmasterOrder->setEditableText (false);
    CBmasterOrder->setJustificationType (Justification::centredLeft);
    CBmasterOrder->setTextWhenNothingSelected (TRANS("Default"));
    CBmasterOrder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBmasterOrder->addListener (this);

    CBmasterOrder->setBounds (96, 384, 103, 18);

    CB_webcam.reset (new ComboBox (String()));
    addAndMakeVisible (CB_webcam.get());
    CB_webcam->setEditableText (false);
    CB_webcam->setJustificationType (Justification::centredLeft);
    CB_webcam->setTextWhenNothingSelected (String());
    CB_webcam->setTextWhenNoChoicesAvailable (String());
    CB_webcam->addListener (this);

    CB_webcam->setBounds (395, 38, 92, 17);

    TB_greyScale.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_greyScale.get());
    TB_greyScale->setButtonText (String());
    TB_greyScale->addListener (this);

    TB_greyScale->setBounds (600, 35, 24, 24);

    TB_flipUD.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipUD.get());
    TB_flipUD->setButtonText (String());
    TB_flipUD->addListener (this);

    TB_flipUD->setBounds (559, 35, 24, 24);

    TB_flipLR.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipLR.get());
    TB_flipLR->setButtonText (String());
    TB_flipLR->addListener (this);

    TB_flipLR->setBounds (511, 35, 24, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (634, 514);


    //[Constructor] You can add your own custom stuff here..
	hVst = ownerFilter;
    hSld = hVst->getFXHandle();
	openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* remove slider bit of these sliders */
    s_minFreq->setColour(Slider::trackColourId, Colours::transparentBlack);
    s_minFreq->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    s_minFreq->setSliderSnapsToMousePosition(false);
    s_maxFreq->setColour(Slider::trackColourId, Colours::transparentBlack);
    s_maxFreq->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    s_maxFreq->setSliderSnapsToMousePosition(false);

    /* overlay */
    previewArea.setBounds(13, 59, 608, 303);
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

    /* create 2d Slider for the decoding order parameter */
    int nPoints;
    float* pX_vector;
    int* pY_values_int;
    addAndMakeVisible (anaOrder2dSlider = new log2dSlider(360, 54, 100, 20e3, 1, sldoa_getMasterOrder(hSld), 0));
    anaOrder2dSlider->setAlwaysOnTop(true);
    anaOrder2dSlider->setTopLeftPosition(218, 432);
    sldoa_getAnaOrderHandle(hSld, &pX_vector, &pY_values_int, &nPoints);
    anaOrder2dSlider->setDataHandlesInt(pX_vector, pY_values_int, nPoints);

    /* add master analysis order options */
    CBmasterOrder->addItem (TRANS("1st order"), MASTER_ORDER_FIRST);
    CBmasterOrder->addItem (TRANS("2nd order"), MASTER_ORDER_SECOND);
    CBmasterOrder->addItem (TRANS("3rd order"), MASTER_ORDER_THIRD);
    CBmasterOrder->addItem (TRANS("4th order"), MASTER_ORDER_FOURTH);
    CBmasterOrder->addItem (TRANS("5th order"), MASTER_ORDER_FIFTH);
    CBmasterOrder->addItem (TRANS("6th order"), MASTER_ORDER_SIXTH);
    CBmasterOrder->addItem (TRANS("7th order"), MASTER_ORDER_SEVENTH);

    /* add ambisonic convention options */
    CB_CHorder->addItem(TRANS("ACN"), CH_ACN);
    CB_CHorder->addItem(TRANS("FuMa"), CH_FUMA);
    CB_Norm->addItem(TRANS("N3D"), NORM_N3D);
    CB_Norm->addItem(TRANS("SN3D"), NORM_SN3D);
    CB_Norm->addItem(TRANS("FuMa"), NORM_FUMA);

    /* add microphone preset options */
#ifdef ENABLE_ZYLIA_MIC_PRESET
    CBinputTypePreset->addItem(TRANS("Zylia"), MIC_PRESET_ZYLIA);
#endif
#ifdef ENABLE_EIGENMIKE32_MIC_PRESET
    CBinputTypePreset->addItem(TRANS("Eigenmike"), MIC_PRESET_EIGENMIKE32);
#endif
#ifdef ENABLE_DTU_MIC_MIC_PRESET
    CBinputTypePreset->addItem(TRANS("DTU mic"), MIC_PRESET_DTU_MIC);
#endif

	/* fetch current configuration */
    CBmasterOrder->setSelectedId(sldoa_getMasterOrder(hSld), dontSendNotification);
    avgSlider->setValue((float)sldoa_getAvg(hSld), dontSendNotification);
    CB_CHorder->setSelectedId(sldoa_getChOrder(hSld), dontSendNotification);
    CB_Norm->setSelectedId(sldoa_getNormType(hSld), dontSendNotification);
    slider_anaOrder->setRange(1, sldoa_getMasterOrder(hSld), 1);
    slider_anaOrder->setValue(sldoa_getAnaOrderAllBands(hSld), dontSendNotification);
    s_minFreq->setRange(0.0f, sldoa_getSamplingRate(hSld)/2.0f, 1.0f);
    s_maxFreq->setRange(0.0f, sldoa_getSamplingRate(hSld)/2.0f, 1.0f);
    s_minFreq->setSkewFactor(0.5f);
    s_maxFreq->setSkewFactor(0.5f);
    s_minFreq->setValue(sldoa_getMinFreq(hSld));
    s_maxFreq->setValue(sldoa_getMaxFreq(hSld));
    CB_CHorder->setItemEnabled(CH_FUMA, sldoa_getMasterOrder(hSld)==MASTER_ORDER_FIRST ? true : false);
    CB_Norm->setItemEnabled(NORM_FUMA, sldoa_getMasterOrder(hSld)==MASTER_ORDER_FIRST ? true : false);

	/* Specify screen refresh rate */
    startTimer(100);//80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    avgSlider = nullptr;
    CB_CHorder = nullptr;
    CB_Norm = nullptr;
    slider_anaOrder = nullptr;
    CBinputTypePreset = nullptr;
    s_minFreq = nullptr;
    s_maxFreq = nullptr;
    CBmasterOrder = nullptr;
    CB_webcam = nullptr;
    TB_greyScale = nullptr;
    TB_flipUD = nullptr;
    TB_flipLR = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    overlayIncluded = nullptr;
    anaOrder2dSlider = nullptr;
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    {
        int x = 0, y = 30, width = 634, height = 484;
        Colour fillColour1 = Colour (0xff1f3b49), fillColour2 = Colour (0xff0a2931);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       320.0f - 0.0f + x,
                                       240.0f - 30.0f + y,
                                       fillColour2,
                                       632.0f - 0.0f + x,
                                       512.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 8, y = 374, width = 197, height = 128;
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
        int x = 204, y = 374, width = 422, height = 34;
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
        int x = 8, y = 374, width = 197, height = 34;
        Colour fillColour = Colour (0x19f4f4f4);
        Colour strokeColour = Colour (0x32a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 204, y = 407, width = 422, height = 95;
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
        int x = 0, y = 0, width = 634, height = 32;
        Colour fillColour = Colour (0xff05222a);
        Colour strokeColour = Colour (0xdcbdbdbd);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 14, y = 410, width = 96, height = 30;
        String text (TRANS("Mic Preset:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 14, y = 468, width = 112, height = 30;
        String text (TRANS("Avg (ms):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 14, y = 440, width = 127, height = 30;
        String text (TRANS("Format:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 216, y = 405, width = 312, height = 30;
        String text (TRANS("Analysis Order Per Frequency Band"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 611, y = 466, width = 13, height = 30;
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
        int x = 211, y = 478, width = 37, height = 30;
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
        int x = 366, y = 478, width = 37, height = 30;
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
        int x = 520, y = 478, width = 37, height = 30;
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
        int x = 402, y = 478, width = 93, height = 30;
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
        int x = 563, y = 478, width = 37, height = 30;
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
        int x = 216, y = 376, width = 160, height = 30;
        String text (TRANS("Minimum Freq (Hz):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 422, y = 376, width = 162, height = 30;
        String text (TRANS("Maximum Freq (Hz):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 14, y = 376, width = 104, height = 30;
        String text (TRANS("Max Order:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
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
        String text (TRANS("SLDoA"));
        Colour fillColour = Colour (0xffff4848);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 584, y = 32, width = 29, height = 30;
        String text (TRANS("GS:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 536, y = 32, width = 37, height = 30;
        String text (TRANS("U|D:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 490, y = 32, width = 37, height = 30;
        String text (TRANS("L|R:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 267, y = 33, width = 125, height = 30;
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
		166, 16, 530, 11,
		Justification::centredLeft, true);

    Colour strokeColour = Colour (0x86a3a4a5);
    g.setColour (strokeColour);
    g.setOpacity(0.8f);
    g.drawRect (previewArea);


    /* label for max ORDER */
    {
        int x = 610, y = 412, width = 13, height = 30;
        String text = String(sldoa_getMasterOrder(hSld));
        Colour fillColour = Colours::white;
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

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
            g.drawText(TRANS("Sample rate (") + String(sldoa_getSamplingRate(hSld)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(sldoa_getNSHrequired(hSld)) + TRANS(")"),
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

void PluginEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == avgSlider.get())
    {
        //[UserSliderCode_avgSlider] -- add your slider handling code here..
        sldoa_setAvg(hSld, (float)avgSlider->getValue());
        //[/UserSliderCode_avgSlider]
    }
    else if (sliderThatWasMoved == slider_anaOrder.get())
    {
        //[UserSliderCode_slider_anaOrder] -- add your slider handling code here..
        sldoa_setAnaOrderAllBands(hSld, (int)(slider_anaOrder->getValue()+0.5));
        anaOrder2dSlider->setRefreshValuesFLAG(true);
        //[/UserSliderCode_slider_anaOrder]
    }
    else if (sliderThatWasMoved == s_minFreq.get())
    {
        //[UserSliderCode_s_minFreq] -- add your slider handling code here..
        sldoa_setMinFreq(hSld, (float)s_minFreq->getValue());


        //[/UserSliderCode_s_minFreq]
    }
    else if (sliderThatWasMoved == s_maxFreq.get())
    {
        //[UserSliderCode_s_maxFreq] -- add your slider handling code here..
        sldoa_setMaxFreq(hSld, (float)s_maxFreq->getValue());
        //[/UserSliderCode_s_maxFreq]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CB_CHorder.get())
    {
        //[UserComboBoxCode_CB_CHorder] -- add your combo box handling code here..
        sldoa_setChOrder(hSld, CB_CHorder->getSelectedId());
        //[/UserComboBoxCode_CB_CHorder]
    }
    else if (comboBoxThatHasChanged == CB_Norm.get())
    {
        //[UserComboBoxCode_CB_Norm] -- add your combo box handling code here..
        sldoa_setNormType(hSld, CB_Norm->getSelectedId());
        //[/UserComboBoxCode_CB_Norm]
    }
    else if (comboBoxThatHasChanged == CBinputTypePreset.get())
    {
        //[UserComboBoxCode_CBinputTypePreset] -- add your combo box handling code here..
        sldoa_setSourcePreset(hSld, CBinputTypePreset->getSelectedId());
        anaOrder2dSlider->setRefreshValuesFLAG(true);
        //[/UserComboBoxCode_CBinputTypePreset]
    }
    else if (comboBoxThatHasChanged == CBmasterOrder.get())
    {
        //[UserComboBoxCode_CBmasterOrder] -- add your combo box handling code here..
        sldoa_setMasterOrder(hSld, CBmasterOrder->getSelectedId());
        CBinputTypePreset->setSelectedId(1);
        anaOrder2dSlider->setYrange(1, CBmasterOrder->getSelectedId());
        sldoa_setAnaOrderAllBands(hSld, CBmasterOrder->getSelectedId());
        anaOrder2dSlider->setRefreshValuesFLAG(true);
        slider_anaOrder->setRange(1, CBmasterOrder->getSelectedId(), 1);
        slider_anaOrder->setValue(CBmasterOrder->getSelectedId());
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
    /* parameters whos values can change internally should be periodically refreshed */
    CB_CHorder->setSelectedId(sldoa_getChOrder(hSld), dontSendNotification);
    CB_Norm->setSelectedId(sldoa_getNormType(hSld), dontSendNotification);
    CB_CHorder->setItemEnabled(CH_FUMA, sldoa_getMasterOrder(hSld)==MASTER_ORDER_FIRST ? true : false);
    CB_Norm->setItemEnabled(NORM_FUMA, sldoa_getMasterOrder(hSld)==MASTER_ORDER_FIRST ? true : false);

    /* take webcam picture */
    if(CB_webcam->getSelectedId()>1){
        handleAsyncUpdate();
        if (incomingImage.isValid())
            lastSnapshot.setImage(incomingImage);
    }

    /* refresh overlay */
	if ((overlayIncluded != nullptr) && (hVst->getIsPlaying()))
		overlayIncluded->repaint();
    if (anaOrder2dSlider->getRefreshValuesFLAG())
        anaOrder2dSlider->repaint();

    s_minFreq->setValue(sldoa_getMinFreq(hSld));
    s_maxFreq->setValue(sldoa_getMaxFreq(hSld));

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ( !((sldoa_getSamplingRate(hSld) == 44.1e3) || (sldoa_getSamplingRate(hSld) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < sldoa_getNSHrequired(hSld))){
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
                 fixedSize="1" initialWidth="634" initialHeight="514">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 634 484" fill=" radial: 320 240, 632 512, 0=ff1f3b49, 1=ff0a2931"
          hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="8 374 197 128" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="204 374 422 34" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="8 374 197 34" fill="solid: 19f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 32a0a0a0"/>
    <RECT pos="204 407 422 95" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="0 0 634 32" fill="solid: ff05222a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <TEXT pos="14 410 96 30" fill="solid: ffffffff" hasStroke="0" text="Mic Preset:"
          fontname="Default font" fontsize="1.4e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="14 468 112 30" fill="solid: ffffffff" hasStroke="0" text="Avg (ms):"
          fontname="Default font" fontsize="1.4e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="14 440 127 30" fill="solid: ffffffff" hasStroke="0" text="Format:"
          fontname="Default font" fontsize="1.4e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="216 405 312 30" fill="solid: ffffffff" hasStroke="0" text="Analysis Order Per Frequency Band"
          fontname="Default font" fontsize="1.4e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="611 466 13 30" fill="solid: ffffffff" hasStroke="0" text="1"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="211 478 37 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="366 478 37 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="520 478 37 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="402 478 93 30" fill="solid: ffffffff" hasStroke="0" text="Frequency (Hz)"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="563 478 37 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="1.2e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="216 376 160 30" fill="solid: ffffffff" hasStroke="0" text="Minimum Freq (Hz):"
          fontname="Default font" fontsize="1.4e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="422 376 162 30" fill="solid: ffffffff" hasStroke="0" text="Maximum Freq (Hz):"
          fontname="Default font" fontsize="1.4e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="14 376 104 30" fill="solid: ffffffff" hasStroke="0" text="Max Order:"
          fontname="Default font" fontsize="1.4e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 0 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="1.88e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 0 112 32" fill="solid: ffff4848" hasStroke="0" text="SLDoA"
          fontname="Default font" fontsize="1.8e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="584 32 29 30" fill="solid: ffffffff" hasStroke="0" text="GS:"
          fontname="Default font" fontsize="1.1e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="536 32 37 30" fill="solid: ffffffff" hasStroke="0" text="U|D:"
          fontname="Default font" fontsize="1.1e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="490 32 37 30" fill="solid: ffffffff" hasStroke="0" text="L|R:"
          fontname="Default font" fontsize="1.1e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="267 33 125 30" fill="solid: ffffffff" hasStroke="0" text="Display Window"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="86d1295f97e935ba" memberName="avgSlider"
          virtualName="" explicitFocusOrder="0" pos="80 473 118 24" min="0"
          max="2e3" int="1e-1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="45" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="3d1c447f9542fa94" memberName="CB_CHorder"
            virtualName="" explicitFocusOrder="0" pos="66 447 64 18" editable="0"
            layout="33" items="" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="d046f2696f3a4a04" memberName="CB_Norm"
            virtualName="" explicitFocusOrder="0" pos="131 447 68 18" editable="0"
            layout="33" items="" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="50ea77f60aadeeca" memberName="slider_anaOrder"
          virtualName="" explicitFocusOrder="0" pos="576 424 40 66" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0" max="1" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="932ca035edce041d" memberName="CBinputTypePreset"
            virtualName="" explicitFocusOrder="0" pos="96 417 103 18" editable="0"
            layout="33" items="Ideal SH" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="905f4ab0adab1f4f" memberName="s_minFreq"
          virtualName="" explicitFocusOrder="0" pos="352 382 56 20" min="0"
          max="2.4e4" int="1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="45" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="new slider" id="3aad5000f228ef1b" memberName="s_maxFreq"
          virtualName="" explicitFocusOrder="0" pos="560 382 56 20" min="0"
          max="2.4e4" int="1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="45" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="346a30a1bf8969e9" memberName="CBmasterOrder"
            virtualName="" explicitFocusOrder="0" pos="96 384 103 18" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="" id="974f5da4ceed6bb6" memberName="CB_webcam" virtualName=""
            explicitFocusOrder="0" pos="395 38 92 17" editable="0" layout="33"
            items="" textWhenNonSelected="" textWhenNoItems=""/>
  <TOGGLEBUTTON name="new toggle button" id="78ff43e4ccfdc462" memberName="TB_greyScale"
                virtualName="" explicitFocusOrder="0" pos="600 35 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="f4031e45e07a36d" memberName="TB_flipUD"
                virtualName="" explicitFocusOrder="0" pos="559 35 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="bb60feb319e3e7d4" memberName="TB_flipLR"
                virtualName="" explicitFocusOrder="0" pos="511 35 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

