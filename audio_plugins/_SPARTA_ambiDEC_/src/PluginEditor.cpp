/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "saf_hoa.h"
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter), fileChooser ("File", File(), true, false, false,
      "*.sofa;*.nc;", String(),
      "Load SOFA File")
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (CBoutputDirsPreset = new ComboBox ("new combo box"));
    CBoutputDirsPreset->setEditableText (false);
    CBoutputDirsPreset->setJustificationType (Justification::centredLeft);
    CBoutputDirsPreset->setTextWhenNothingSelected (TRANS("Default"));
    CBoutputDirsPreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBoutputDirsPreset->addItem (TRANS("Default"), 1);
    CBoutputDirsPreset->addListener (this);

    CBoutputDirsPreset->setBounds (520, 64, 112, 20);

    addAndMakeVisible (SL_num_loudspeakers = new Slider ("new slider"));
    SL_num_loudspeakers->setRange (1, 64, 1);
    SL_num_loudspeakers->setSliderStyle (Slider::LinearHorizontal);
    SL_num_loudspeakers->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    SL_num_loudspeakers->addListener (this);

    SL_num_loudspeakers->setBounds (520, 90, 112, 24);

    addAndMakeVisible (TBuseDefaultHRIRs = new ToggleButton ("new toggle button"));
    TBuseDefaultHRIRs->setButtonText (String());
    TBuseDefaultHRIRs->addListener (this);

    TBuseDefaultHRIRs->setBounds (408, 94, 32, 24);

    addAndMakeVisible (CBsourcePreset = new ComboBox ("new combo box"));
    CBsourcePreset->setEditableText (false);
    CBsourcePreset->setJustificationType (Justification::centredLeft);
    CBsourcePreset->setTextWhenNothingSelected (TRANS("Default"));
    CBsourcePreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBsourcePreset->addItem (TRANS("Ideal SH"), 1);
    CBsourcePreset->addListener (this);

    CBsourcePreset->setBounds (96, 64, 112, 20);

    addAndMakeVisible (CBchFormat = new ComboBox ("new combo box"));
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (Justification::centredLeft);
    CBchFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBchFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBchFormat->addItem (TRANS("ACN"), 1);
    CBchFormat->addListener (this);

    CBchFormat->setBounds (96, 96, 112, 20);

    addAndMakeVisible (CBnormScheme = new ComboBox ("new combo box"));
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (Justification::centredLeft);
    CBnormScheme->setTextWhenNothingSelected (TRANS("N3D"));
    CBnormScheme->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnormScheme->addItem (TRANS("N3D"), 1);
    CBnormScheme->addItem (TRANS("SN3D"), 2);
    CBnormScheme->addListener (this);

    CBnormScheme->setBounds (96, 128, 112, 20);

    addAndMakeVisible (SL_transitionFreq = new Slider ("new slider"));
    SL_transitionFreq->setRange (500, 2000, 0.1);
    SL_transitionFreq->setSliderStyle (Slider::LinearHorizontal);
    SL_transitionFreq->setTextBoxStyle (Slider::TextBoxAbove, false, 60, 20);
    SL_transitionFreq->addListener (this);

    SL_transitionFreq->setBounds (168, 296, 112, 40);

    addAndMakeVisible (CBdec1method = new ComboBox ("new combo box"));
    CBdec1method->setEditableText (false);
    CBdec1method->setJustificationType (Justification::centredLeft);
    CBdec1method->setTextWhenNothingSelected (TRANS("Default"));
    CBdec1method->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBdec1method->addListener (this);

    CBdec1method->setBounds (24, 288, 116, 20);

    addAndMakeVisible (CBdec2method = new ComboBox ("new combo box"));
    CBdec2method->setEditableText (false);
    CBdec2method->setJustificationType (Justification::centredLeft);
    CBdec2method->setTextWhenNothingSelected (TRANS("Default"));
    CBdec2method->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBdec2method->addListener (this);

    CBdec2method->setBounds (308, 288, 116, 20);

    addAndMakeVisible (TBdec1EnableMaxrE = new ToggleButton ("new toggle button"));
    TBdec1EnableMaxrE->setButtonText (String());
    TBdec1EnableMaxrE->addListener (this);

    TBdec1EnableMaxrE->setBounds (120, 312, 32, 24);

    addAndMakeVisible (TBdec2EnableMaxrE = new ToggleButton ("new toggle button"));
    TBdec2EnableMaxrE->setButtonText (String());
    TBdec2EnableMaxrE->addListener (this);

    TBdec2EnableMaxrE->setBounds (404, 312, 32, 24);

    addAndMakeVisible (CBdec1normtype = new ComboBox ("new combo box"));
    CBdec1normtype->setEditableText (false);
    CBdec1normtype->setJustificationType (Justification::centredLeft);
    CBdec1normtype->setTextWhenNothingSelected (TRANS("EP"));
    CBdec1normtype->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBdec1normtype->addListener (this);

    CBdec1normtype->setBounds (24, 314, 52, 20);

    addAndMakeVisible (TBBinauraliseLS = new ToggleButton ("new toggle button"));
    TBBinauraliseLS->setButtonText (String());
    TBBinauraliseLS->addListener (this);

    TBBinauraliseLS->setBounds (408, 62, 32, 24);

    addAndMakeVisible (CBdec2normtype = new ComboBox ("new combo box"));
    CBdec2normtype->setEditableText (false);
    CBdec2normtype->setJustificationType (Justification::centredLeft);
    CBdec2normtype->setTextWhenNothingSelected (TRANS("EP"));
    CBdec2normtype->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBdec2normtype->addListener (this);

    CBdec2normtype->setBounds (308, 314, 52, 20);

    addAndMakeVisible (s_decOrder = new Slider ("new slider"));
    s_decOrder->setRange (0, 1, 1);
    s_decOrder->setSliderStyle (Slider::LinearVertical);
    s_decOrder->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    s_decOrder->setColour (Slider::textBoxTextColourId, Colours::white);
    s_decOrder->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_decOrder->addListener (this);

    s_decOrder->setBounds (384, 176, 40, 80);

    addAndMakeVisible (tb_loadJSON = new TextButton ("new button"));
    tb_loadJSON->setButtonText (TRANS("Import"));
    tb_loadJSON->setConnectedEdges (Button::ConnectedOnRight);
    tb_loadJSON->addListener (this);
    tb_loadJSON->setColour (TextButton::buttonColourId, Colour (0xff14889e));

    tb_loadJSON->setBounds (447, 40, 34, 14);

    addAndMakeVisible (tb_saveJSON = new TextButton ("new button"));
    tb_saveJSON->setButtonText (TRANS("Export"));
    tb_saveJSON->setConnectedEdges (Button::ConnectedOnLeft);
    tb_saveJSON->addListener (this);
    tb_saveJSON->setColour (TextButton::buttonColourId, Colour (0xff224d97));
    tb_saveJSON->setColour (TextButton::buttonOnColourId, Colour (0xff181f9a));

    tb_saveJSON->setBounds (481, 40, 34, 14);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (656, 356);


    //[Constructor] You can add your own custom stuff here..

    /* handle to pluginProcessor */
	hVst = ownerFilter;

    /* init OpenGL */
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* create 2d Slider for the decoding order parameter */
    int nPoints;
    float* pX_vector;
    int* pY_values_int;
    addAndMakeVisible (decOrder2dSlider = new log2dSlider(360, 63, 100, 20e3, 1, SH_ORDER, 0));
    decOrder2dSlider->setAlwaysOnTop(true);
    decOrder2dSlider->setTopLeftPosition(25, 183);
    ambi_dec_getDecOrderHandle(hVst->hAmbi, &pX_vector, &pY_values_int, &nPoints);
    decOrder2dSlider->setDataHandlesInt(pX_vector, pY_values_int, nPoints);

    /* add decorder options */
    CBdec1method->addItem(TRANS("SAD"), DECODER_SAD);
    CBdec1method->addItem(TRANS("MMD"), DECODER_MMD);
    CBdec1method->addItem(TRANS("EPAD"), DECODER_EPAD);
    CBdec1method->addItem(TRANS("AllRAD"), DECODER_ALLRAD);
    CBdec2method->addItem(TRANS("SAD"), DECODER_SAD);
    CBdec2method->addItem(TRANS("MMD"), DECODER_MMD);
    CBdec2method->addItem(TRANS("EPAD"), DECODER_EPAD);
    CBdec2method->addItem(TRANS("AllRAD"), DECODER_ALLRAD);

    /* add diffuse-eq options */
    CBdec1normtype->addItem(TRANS("AP"), AMPLITUDE_PRESERVING);
    CBdec1normtype->addItem(TRANS("EP"), ENERGY_PRESERVING);
    CBdec2normtype->addItem(TRANS("AP"), AMPLITUDE_PRESERVING);
    CBdec2normtype->addItem(TRANS("EP"), ENERGY_PRESERVING);

    /* add microphone preset options */
#ifdef ENABLE_ZYLIA_MIC_PRESET
    CBsourcePreset->addItem(TRANS("Zylia"), MIC_PRESET_ZYLIA);
#endif
#ifdef ENABLE_EIGENMIKE32_MIC_PRESET
    CBsourcePreset->addItem(TRANS("Eigenmike"), MIC_PRESET_EIGENMIKE32);
#endif
#ifdef ENABLE_DTU_MIC_MIC_PRESET
    CBsourcePreset->addItem(TRANS("DTU mic"), MIC_PRESET_DTU_MIC);
#endif

    /* add loudspeaker preset options */
#ifdef ENABLE_5PX_PRESET
    CBoutputDirsPreset->addItem (TRANS("5.x"), PRESET_5PX);
#endif
#ifdef ENABLE_7PX_PRESET
    CBoutputDirsPreset->addItem (TRANS("7.x"), PRESET_7PX);
#endif
#ifdef ENABLE_8PX_PRESET
    CBoutputDirsPreset->addItem (TRANS("8.x"), PRESET_8PX);
#endif
#ifdef ENABLE_9PX_PRESET
    CBoutputDirsPreset->addItem (TRANS("9.x"), PRESET_9PX);
#endif
#ifdef ENABLE_10PX_PRESET
    CBoutputDirsPreset->addItem (TRANS("10.x"), PRESET_10PX);
#endif
#ifdef ENABLE_11PX_PRESET
    CBoutputDirsPreset->addItem (TRANS("11.x"), PRESET_11PX);
#endif
#ifdef ENABLE_11PX_7_4_PRESET
    CBoutputDirsPreset->addItem (TRANS("11.x (7+4)"), PRESET_11PX_7_4);
#endif
#ifdef ENABLE_13PX_PRESET
    CBoutputDirsPreset->addItem (TRANS("13.x"), PRESET_13PX);
#endif
#ifdef ENABLE_22PX_PRESET
    CBoutputDirsPreset->addItem (TRANS("22.x"), PRESET_22PX);
#endif
#ifdef ENABLE_AALTO_MCC_PRESET
    CBoutputDirsPreset->addItem (TRANS("Aalto MCC"), PRESET_AALTO_MCC);
#endif
#ifdef ENABLE_AALTO_APAJA_PRESET
    CBoutputDirsPreset->addItem (TRANS("Aalto Apaja"), PRESET_AALTO_APAJA);
#endif
#ifdef ENABLE_AALTO_APAJA2_PRESET
    CBoutputDirsPreset->addItem (TRANS("Aalto Apaja 2.0"), PRESET_AALTO_APAJA2);
#endif
#ifdef ENABLE_AALTO_LR_PRESET
    CBoutputDirsPreset->addItem (TRANS("Aalto LR"), PRESET_AALTO_LR);
#endif
#ifdef ENABLE_DTU_AVIL_PRESET
    CBoutputDirsPreset->addItem (TRANS("DTU AVIL"), PRESET_DTU_AVIL);
#endif
#ifdef ENABLE_ZYLIA_LAB_PRESET
    CBoutputDirsPreset->addItem (TRANS("Zylia Lab (22.x)"), PRESET_ZYLIA_LAB);
#endif
#ifdef ENABLE_T_DESIGN_4_PRESET
    CBoutputDirsPreset->addItem (TRANS("T-design (4)"), PRESET_T_DESIGN_4);
#endif
#ifdef ENABLE_T_DESIGN_12_PRESET
    CBoutputDirsPreset->addItem (TRANS("T-design (12)"), PRESET_T_DESIGN_12);
#endif
#ifdef ENABLE_T_DESIGN_24_PRESET
    CBoutputDirsPreset->addItem (TRANS("T-design (24)"), PRESET_T_DESIGN_24);
#endif
#ifdef ENABLE_T_DESIGN_36_PRESET
    CBoutputDirsPreset->addItem (TRANS("T-design (36)"), PRESET_T_DESIGN_36);
#endif
#ifdef ENABLE_T_DESIGN_48_PRESET
    CBoutputDirsPreset->addItem (TRANS("T-design (48)"), PRESET_T_DESIGN_48);
#endif
#ifdef ENABLE_T_DESIGN_60_PRESET
    CBoutputDirsPreset->addItem (TRANS("T-design (60)"), PRESET_T_DESIGN_60);
#endif

    /* source coordinate viewport */
    addAndMakeVisible (outputCoordsVP = new Viewport ("new viewport"));
    outputCoordsView_handle = new outputCoordsView(ownerFilter, MAX_NUM_CHANNELS, ambi_dec_getNumLoudspeakers(hVst->hAmbi));
    outputCoordsVP->setViewedComponent (outputCoordsView_handle);
    outputCoordsVP->setScrollBarsShown (true, false);
    outputCoordsVP->setAlwaysOnTop(true);
    outputCoordsVP->setBounds(455, 153, 184, 180);
    outputCoordsView_handle->setNCH(ambi_dec_getNumLoudspeakers(hVst->hAmbi));

    /* file loader */
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
    fileChooser.setBounds (226, 128, 200, 20);

    /* grab current parameter settings */
    TBuseDefaultHRIRs->setToggleState(ambi_dec_getUseDefaultHRIRsflag(hVst->hAmbi), dontSendNotification);
    SL_num_loudspeakers->setValue(ambi_dec_getNumLoudspeakers(hVst->hAmbi),dontSendNotification);
    CBchFormat->setSelectedId(ambi_dec_getChOrder(hVst->hAmbi), dontSendNotification);
    CBnormScheme->setSelectedId(ambi_dec_getNormType(hVst->hAmbi), dontSendNotification);
    s_decOrder->setRange(1, SH_ORDER, 1);
    s_decOrder->setValue(ambi_dec_getDecOrderAllBands(hVst->hAmbi), dontSendNotification);
    TBBinauraliseLS->setToggleState(ambi_dec_getBinauraliseLSflag(hVst->hAmbi), dontSendNotification);
    CBdec1method->setSelectedId(ambi_dec_getDecMethod(hVst->hAmbi, 0), dontSendNotification);
    CBdec2method->setSelectedId(ambi_dec_getDecMethod(hVst->hAmbi, 1), dontSendNotification);
    TBdec1EnableMaxrE->setToggleState(ambi_dec_getDecEnableMaxrE(hVst->hAmbi, 0), dontSendNotification);
    TBdec2EnableMaxrE->setToggleState(ambi_dec_getDecEnableMaxrE(hVst->hAmbi, 1), dontSendNotification);
    CBdec1normtype->setSelectedId(ambi_dec_getDecNormType(hVst->hAmbi, 0), dontSendNotification);
    CBdec2normtype->setSelectedId(ambi_dec_getDecNormType(hVst->hAmbi, 1), dontSendNotification);
    SL_transitionFreq->setValue(ambi_dec_getTransitionFreq(hVst->hAmbi), dontSendNotification);

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

    CBoutputDirsPreset = nullptr;
    SL_num_loudspeakers = nullptr;
    TBuseDefaultHRIRs = nullptr;
    CBsourcePreset = nullptr;
    CBchFormat = nullptr;
    CBnormScheme = nullptr;
    SL_transitionFreq = nullptr;
    CBdec1method = nullptr;
    CBdec2method = nullptr;
    TBdec1EnableMaxrE = nullptr;
    TBdec2EnableMaxrE = nullptr;
    CBdec1normtype = nullptr;
    TBBinauraliseLS = nullptr;
    CBdec2normtype = nullptr;
    s_decOrder = nullptr;
    tb_loadJSON = nullptr;
    tb_saveJSON = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    {
        int x = 0, y = 30, width = 656, height = 326;
        Colour fillColour1 = Colour (0xff55636d), fillColour2 = Colour (0xff073642);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       336.0f - 0.0f + x,
                                       184.0f - 30.0f + y,
                                       fillColour2,
                                       656.0f - 0.0f + x,
                                       352.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 152, y = 263, width = 145, height = 81;
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
        int x = 296, y = 263, width = 140, height = 81;
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
        int x = 446, y = 121, width = 196, height = 223;
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
        int x = 216, y = 58, width = 220, height = 102;
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
        int x = 446, y = 58, width = 196, height = 64;
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
        int x = 12, y = 58, width = 205, height = 102;
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
        int x = 0, y = 0, width = 656, height = 32;
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
        int x = -19, y = 0, width = 195, height = 32;
        String text (TRANS("AmbiDEC"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.80f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 455, y = 58, width = 67, height = 30;
        String text (TRANS("Presets: "));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 12, y = 159, width = 424, height = 105;
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
        int x = 502, y = 124, width = 105, height = 32;
        String text (TRANS("Azi    #    Elev"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 455, y = 86, width = 113, height = 30;
        String text (TRANS("N Chan:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 164, y = 32, width = 149, height = 30;
        String text (TRANS("Decoding Settings"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 524, y = 32, width = 113, height = 30;
        String text (TRANS("Outputs"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 227, y = 90, width = 165, height = 30;
        String text (TRANS("Use Default HRIR set:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 58, width = 132, height = 30;
        String text (TRANS("Preset:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 90, width = 132, height = 30;
        String text (TRANS("CH Order:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 122, width = 132, height = 30;
        String text (TRANS("Norm:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 227, y = 58, width = 189, height = 30;
        String text (TRANS("Binauralise Loudspeakers:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 12, y = 263, width = 141, height = 81;
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
        int x = 51, y = 261, width = 96, height = 30;
        String text (TRANS("Decoder 1"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 168, y = 262, width = 120, height = 30;
        String text (TRANS("Cross-over (Hz)"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 339, y = 261, width = 96, height = 30;
        String text (TRANS("Decoder 2"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 82, y = 308, width = 96, height = 30;
        String text (TRANS("max_rE:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (10.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 156, width = 133, height = 30;
        String text (TRANS("Decoding Order"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 238, width = 37, height = 30;
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
        int x = 174, y = 238, width = 37, height = 30;
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
        int x = 328, y = 238, width = 37, height = 30;
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
        int x = 210, y = 238, width = 93, height = 30;
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
        int x = 371, y = 238, width = 37, height = 30;
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
        int x = 366, y = 308, width = 96, height = 30;
        String text (TRANS("max_rE:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (10.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 419, y = 230, width = 13, height = 30;
        String text (TRANS("1"));
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
		150, 16, 530, 11,
		Justification::centredLeft, true);

    /* label for max ORDER */
    int x = 419, y = 170, width = 13, height = 30;
    String text (String(SH_ORDER));
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
                       TRANS("/") + String(ambi_dec_getNSHrequired()) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(ambi_dec_getNumLoudspeakers(hVst->hAmbi)) + TRANS(")"),
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

void PluginEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBoutputDirsPreset)
    {
        //[UserComboBoxCode_CBoutputDirsPreset] -- add your combo box handling code here..
        ambi_dec_setOutputConfigPreset(hVst->hAmbi, CBoutputDirsPreset->getSelectedId());
        //[/UserComboBoxCode_CBoutputDirsPreset]
    }
    else if (comboBoxThatHasChanged == CBsourcePreset)
    {
        //[UserComboBoxCode_CBsourcePreset] -- add your combo box handling code here..
        ambi_dec_setSourcePreset(hVst->hAmbi, CBsourcePreset->getSelectedId());
        //[/UserComboBoxCode_CBsourcePreset]
    }
    else if (comboBoxThatHasChanged == CBchFormat)
    {
        //[UserComboBoxCode_CBchFormat] -- add your combo box handling code here..
        ambi_dec_setChOrder(hVst->hAmbi, CBchFormat->getSelectedId());
        //[/UserComboBoxCode_CBchFormat]
    }
    else if (comboBoxThatHasChanged == CBnormScheme)
    {
        //[UserComboBoxCode_CBnormScheme] -- add your combo box handling code here..
        ambi_dec_setNormType(hVst->hAmbi, CBnormScheme->getSelectedId());
        //[/UserComboBoxCode_CBnormScheme]
    }
    else if (comboBoxThatHasChanged == CBdec1method)
    {
        //[UserComboBoxCode_CBdec1method] -- add your combo box handling code here..
        ambi_dec_setDecMethod(hVst->hAmbi, 0, CBdec1method->getSelectedId());
        //[/UserComboBoxCode_CBdec1method]
    }
    else if (comboBoxThatHasChanged == CBdec2method)
    {
        //[UserComboBoxCode_CBdec2method] -- add your combo box handling code here..
        ambi_dec_setDecMethod(hVst->hAmbi, 1, CBdec2method->getSelectedId());
        //[/UserComboBoxCode_CBdec2method]
    }
    else if (comboBoxThatHasChanged == CBdec1normtype)
    {
        //[UserComboBoxCode_CBdec1normtype] -- add your combo box handling code here..
        ambi_dec_setDecNormType(hVst->hAmbi, 0, CBdec1normtype->getSelectedId());
        //[/UserComboBoxCode_CBdec1normtype]
    }
    else if (comboBoxThatHasChanged == CBdec2normtype)
    {
        //[UserComboBoxCode_CBdec2normtype] -- add your combo box handling code here..
        ambi_dec_setDecNormType(hVst->hAmbi, 1, CBdec2normtype->getSelectedId());
        //[/UserComboBoxCode_CBdec2normtype]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == SL_num_loudspeakers)
    {
        //[UserSliderCode_SL_num_loudspeakers] -- add your slider handling code here..
        ambi_dec_setNumLoudspeakers(hVst->hAmbi, (int)SL_num_loudspeakers->getValue());
        //[/UserSliderCode_SL_num_loudspeakers]
    }
    else if (sliderThatWasMoved == SL_transitionFreq)
    {
        //[UserSliderCode_SL_transitionFreq] -- add your slider handling code here..
        ambi_dec_setTransitionFreq(hVst->hAmbi, (float)SL_transitionFreq->getValue());
        //[/UserSliderCode_SL_transitionFreq]
    }
    else if (sliderThatWasMoved == s_decOrder)
    {
        //[UserSliderCode_s_decOrder] -- add your slider handling code here..
        ambi_dec_setDecOrderAllBands(hVst->hAmbi, (int)s_decOrder->getValue());
        //[/UserSliderCode_s_decOrder]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == TBuseDefaultHRIRs)
    {
        //[UserButtonCode_TBuseDefaultHRIRs] -- add your button handler code here..
        ambi_dec_setUseDefaultHRIRsflag(hVst->hAmbi, TBuseDefaultHRIRs->getToggleState());
        //[/UserButtonCode_TBuseDefaultHRIRs]
    }
    else if (buttonThatWasClicked == TBdec1EnableMaxrE)
    {
        //[UserButtonCode_TBdec1EnableMaxrE] -- add your button handler code here..
        ambi_dec_setDecEnableMaxrE(hVst->hAmbi, 0, TBdec1EnableMaxrE->getToggleState());
        //[/UserButtonCode_TBdec1EnableMaxrE]
    }
    else if (buttonThatWasClicked == TBdec2EnableMaxrE)
    {
        //[UserButtonCode_TBdec2EnableMaxrE] -- add your button handler code here..
        ambi_dec_setDecEnableMaxrE(hVst->hAmbi, 1, TBdec2EnableMaxrE->getToggleState());
        //[/UserButtonCode_TBdec2EnableMaxrE]
    }
    else if (buttonThatWasClicked == TBBinauraliseLS)
    {
        //[UserButtonCode_TBBinauraliseLS] -- add your button handler code here..
        ambi_dec_setBinauraliseLSflag(hVst->hAmbi, TBBinauraliseLS->getToggleState());
        //[/UserButtonCode_TBBinauraliseLS]
    }
    else if (buttonThatWasClicked == tb_loadJSON)
    {
        //[UserButtonCode_tb_loadJSON] -- add your button handler code here..
        FileChooser myChooser ("Load configuration...",
                               hVst->getLastDir().exists() ? hVst->getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                               "*.json");
        if (myChooser.browseForFileToOpen()) {
            File configFile (myChooser.getResult());
            hVst->setLastDir(configFile.getParentDirectory());
            hVst->loadConfiguration (configFile);
        }
        //[/UserButtonCode_tb_loadJSON]
    }
    else if (buttonThatWasClicked == tb_saveJSON)
    {
        //[UserButtonCode_tb_saveJSON] -- add your button handler code here..
        FileChooser myChooser ("Save configuration...",
                               hVst->getLastDir().exists() ? hVst->getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                               "*.json");
        if (myChooser.browseForFileToSave (true)) {
            File configFile (myChooser.getResult());
            hVst->setLastDir(configFile.getParentDirectory());
            hVst->saveConfigurationToFile (configFile);
        }
        //[/UserButtonCode_tb_saveJSON]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    TBuseDefaultHRIRs->setToggleState(ambi_dec_getUseDefaultHRIRsflag(hVst->hAmbi), dontSendNotification);
    TBBinauraliseLS->setToggleState(ambi_dec_getBinauraliseLSflag(hVst->hAmbi), dontSendNotification);
    outputCoordsView_handle->setNCH(ambi_dec_getNumLoudspeakers(hVst->hAmbi));
    SL_num_loudspeakers->setValue(ambi_dec_getNumLoudspeakers(hVst->hAmbi),dontSendNotification);

    /* refresh */
    if (decOrder2dSlider->getRefreshValuesFLAG())
        decOrder2dSlider->repaint();

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < ambi_dec_getNSHrequired())){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumOutputs() < ambi_dec_getNumLoudspeakers(hVst->hAmbi))){
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
                 parentClasses="public AudioProcessorEditor, public Timer, private FilenameComponentListener"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter), fileChooser (&quot;File&quot;, File(), true, false, false,&#10;                       &quot;*.sofa;*.nc;&quot;, String(),&#10;                       &quot;Load SOFA File&quot;)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="656" initialHeight="356">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 656 326" fill=" radial: 336 184, 656 352, 0=ff55636d, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="152 263 145 81" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="296 263 140 81" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="446 121 196 223" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="216 58 220 102" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="446 58 196 64" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 58 205 102" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="0 0 656 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <TEXT pos="-19 0 195 32" fill="solid: ffffffff" hasStroke="0" text="AmbiDEC"
          fontname="Default font" fontsize="18.80000000000000071054" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="455 58 67 30" fill="solid: ffffffff" hasStroke="0" text="Presets: "
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="12 159 424 105" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="502 124 105 32" fill="solid: ffffffff" hasStroke="0" text="Azi    #    Elev"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="455 86 113 30" fill="solid: ffffffff" hasStroke="0" text="N Chan:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="164 32 149 30" fill="solid: ffffffff" hasStroke="0" text="Decoding Settings"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="524 32 113 30" fill="solid: ffffffff" hasStroke="0" text="Outputs"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="227 90 165 30" fill="solid: ffffffff" hasStroke="0" text="Use Default HRIR set:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 58 132 30" fill="solid: ffffffff" hasStroke="0" text="Preset:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 90 132 30" fill="solid: ffffffff" hasStroke="0" text="CH Order:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 122 132 30" fill="solid: ffffffff" hasStroke="0" text="Norm:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="227 58 189 30" fill="solid: ffffffff" hasStroke="0" text="Binauralise Loudspeakers:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="12 263 141 81" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="51 261 96 30" fill="solid: ffffffff" hasStroke="0" text="Decoder 1"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="168 262 120 30" fill="solid: ffffffff" hasStroke="0" text="Cross-over (Hz)"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="339 261 96 30" fill="solid: ffffffff" hasStroke="0" text="Decoder 2"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="82 308 96 30" fill="solid: ffffffff" hasStroke="0" text="max_rE:"
          fontname="Default font" fontsize="10.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 156 133 30" fill="solid: ffffffff" hasStroke="0" text="Decoding Order"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 238 37 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="174 238 37 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="328 238 37 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="210 238 93 30" fill="solid: ffffffff" hasStroke="0" text="Frequency (Hz)"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="371 238 37 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="366 308 96 30" fill="solid: ffffffff" hasStroke="0" text="max_rE:"
          fontname="Default font" fontsize="10.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="419 230 13 30" fill="solid: ffffffff" hasStroke="0" text="1"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <COMBOBOX name="new combo box" id="5a2f99f88aa51390" memberName="CBoutputDirsPreset"
            virtualName="" explicitFocusOrder="0" pos="520 64 112 20" editable="0"
            layout="33" items="Default" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="2c2a2b3d0614cc94" memberName="SL_num_loudspeakers"
          virtualName="" explicitFocusOrder="0" pos="520 90 112 24" min="1.00000000000000000000"
          max="64.00000000000000000000" int="1.00000000000000000000" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="f7f951a1b21e1a11" memberName="TBuseDefaultHRIRs"
                virtualName="" explicitFocusOrder="0" pos="408 94 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="d83602bab6f1a999" memberName="CBsourcePreset"
            virtualName="" explicitFocusOrder="0" pos="96 64 112 20" editable="0"
            layout="33" items="Ideal SH" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="a36915795f16ceb6" memberName="CBchFormat"
            virtualName="" explicitFocusOrder="0" pos="96 96 112 20" editable="0"
            layout="33" items="ACN" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="e10be54628a6df43" memberName="CBnormScheme"
            virtualName="" explicitFocusOrder="0" pos="96 128 112 20" editable="0"
            layout="33" items="N3D&#10;SN3D" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="27b7eb906eb4d4f" memberName="SL_transitionFreq"
          virtualName="" explicitFocusOrder="0" pos="168 296 112 40" min="500.00000000000000000000"
          max="2000.00000000000000000000" int="0.10000000000000000555"
          style="LinearHorizontal" textBoxPos="TextBoxAbove" textBoxEditable="1"
          textBoxWidth="60" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="6fe8e095551b1808" memberName="CBdec1method"
            virtualName="" explicitFocusOrder="0" pos="24 288 116 20" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="80fc4525118b480b" memberName="CBdec2method"
            virtualName="" explicitFocusOrder="0" pos="308 288 116 20" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="new toggle button" id="2ff10cbc9f10d197" memberName="TBdec1EnableMaxrE"
                virtualName="" explicitFocusOrder="0" pos="120 312 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="f7dc2ec3654b795d" memberName="TBdec2EnableMaxrE"
                virtualName="" explicitFocusOrder="0" pos="404 312 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="51c3f0687556e1b1" memberName="CBdec1normtype"
            virtualName="" explicitFocusOrder="0" pos="24 314 52 20" editable="0"
            layout="33" items="" textWhenNonSelected="EP" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="new toggle button" id="86c014bf0612a514" memberName="TBBinauraliseLS"
                virtualName="" explicitFocusOrder="0" pos="408 62 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="da63cfe9ccba1746" memberName="CBdec2normtype"
            virtualName="" explicitFocusOrder="0" pos="308 314 52 20" editable="0"
            layout="33" items="" textWhenNonSelected="EP" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="50ea77f60aadeeca" memberName="s_decOrder"
          virtualName="" explicitFocusOrder="0" pos="384 176 40 80" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0.00000000000000000000" max="1.00000000000000000000"
          int="1.00000000000000000000" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <TEXTBUTTON name="new button" id="527e24c6748d02d4" memberName="tb_loadJSON"
              virtualName="" explicitFocusOrder="0" pos="447 40 34 14" bgColOff="ff14889e"
              buttonText="Import" connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="48c5d3526dcfe64f" memberName="tb_saveJSON"
              virtualName="" explicitFocusOrder="0" pos="481 40 34 14" bgColOff="ff224d97"
              bgColOn="ff181f9a" buttonText="Export" connectedEdges="1" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
