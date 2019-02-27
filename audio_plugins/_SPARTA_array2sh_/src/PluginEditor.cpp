/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.1

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

    presetCB.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (presetCB.get());
    presetCB->setEditableText (false);
    presetCB->setJustificationType (Justification::centredLeft);
    presetCB->setTextWhenNothingSelected (String());
    presetCB->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    presetCB->addItem (TRANS("Default"), 1);
    presetCB->addListener (this);

    presetCB->setBounds (88, 64, 120, 16);

    arrayTypeCB.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (arrayTypeCB.get());
    arrayTypeCB->setEditableText (false);
    arrayTypeCB->setJustificationType (Justification::centredLeft);
    arrayTypeCB->setTextWhenNothingSelected (TRANS("Spherical"));
    arrayTypeCB->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    arrayTypeCB->addItem (TRANS("Spherical"), 1);
    arrayTypeCB->addItem (TRANS("Cylindrical"), 2);
    arrayTypeCB->addListener (this);

    arrayTypeCB->setBounds (368, 378, 120, 16);

    QSlider.reset (new Slider ("new slider"));
    addAndMakeVisible (QSlider.get());
    QSlider->setRange (4, 64, 1);
    QSlider->setSliderStyle (Slider::LinearHorizontal);
    QSlider->setTextBoxStyle (Slider::TextBoxRight, false, 45, 20);
    QSlider->addListener (this);

    QSlider->setBounds (156, 99, 52, 16);

    rSlider.reset (new Slider ("new slider"));
    addAndMakeVisible (rSlider.get());
    rSlider->setRange (1, 200, 0.01);
    rSlider->setSliderStyle (Slider::LinearHorizontal);
    rSlider->setTextBoxStyle (Slider::TextBoxRight, false, 45, 20);
    rSlider->addListener (this);

    rSlider->setBounds (156, 131, 52, 16);

    RSlider.reset (new Slider ("new slider"));
    addAndMakeVisible (RSlider.get());
    RSlider->setRange (1, 200, 0.01);
    RSlider->setSliderStyle (Slider::LinearHorizontal);
    RSlider->setTextBoxStyle (Slider::TextBoxRight, false, 45, 20);
    RSlider->setColour (Slider::trackColourId, Colour (0xff181f22));
    RSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff263238));
    RSlider->addListener (this);

    RSlider->setBounds (156, 163, 52, 16);

    cSlider.reset (new Slider ("new slider"));
    addAndMakeVisible (cSlider.get());
    cSlider->setRange (200, 2000, 0.1);
    cSlider->setSliderStyle (Slider::LinearHorizontal);
    cSlider->setTextBoxStyle (Slider::TextBoxRight, false, 55, 20);
    cSlider->addListener (this);

    cSlider->setBounds (364, 347, 124, 16);

    weightTypeCB.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (weightTypeCB.get());
    weightTypeCB->setEditableText (false);
    weightTypeCB->setJustificationType (Justification::centredLeft);
    weightTypeCB->setTextWhenNothingSelected (TRANS("Rigid"));
    weightTypeCB->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    weightTypeCB->addListener (this);

    weightTypeCB->setBounds (368, 410, 120, 16);

    filterTypeCB.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (filterTypeCB.get());
    filterTypeCB->setEditableText (false);
    filterTypeCB->setJustificationType (Justification::centredLeft);
    filterTypeCB->setTextWhenNothingSelected (String());
    filterTypeCB->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    filterTypeCB->addListener (this);

    filterTypeCB->setBounds (640, 276, 128, 16);

    regAmountSlider.reset (new Slider ("new slider"));
    addAndMakeVisible (regAmountSlider.get());
    regAmountSlider->setRange (0, 80, 0.01);
    regAmountSlider->setSliderStyle (Slider::LinearHorizontal);
    regAmountSlider->setTextBoxStyle (Slider::TextBoxRight, false, 55, 20);
    regAmountSlider->addListener (this);

    regAmountSlider->setBounds (640, 308, 128, 16);

    CHOrderingCB.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CHOrderingCB.get());
    CHOrderingCB->setEditableText (false);
    CHOrderingCB->setJustificationType (Justification::centredLeft);
    CHOrderingCB->setTextWhenNothingSelected (TRANS("ACN"));
    CHOrderingCB->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CHOrderingCB->addItem (TRANS("ACN"), 1);
    CHOrderingCB->addListener (this);

    CHOrderingCB->setBounds (640, 377, 128, 16);

    normalisationCB.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (normalisationCB.get());
    normalisationCB->setEditableText (false);
    normalisationCB->setJustificationType (Justification::centredLeft);
    normalisationCB->setTextWhenNothingSelected (TRANS("N3D"));
    normalisationCB->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    normalisationCB->addItem (TRANS("N3D"), 1);
    normalisationCB->addItem (TRANS("SN3D"), 2);
    normalisationCB->addListener (this);

    normalisationCB->setBounds (640, 409, 128, 16);

    gainSlider.reset (new Slider ("new slider"));
    addAndMakeVisible (gainSlider.get());
    gainSlider->setRange (-60, 60, 0.01);
    gainSlider->setSliderStyle (Slider::LinearHorizontal);
    gainSlider->setTextBoxStyle (Slider::TextBoxRight, false, 55, 20);
    gainSlider->addListener (this);

    gainSlider->setBounds (640, 341, 128, 16);

    degRadTB.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (degRadTB.get());
    degRadTB->setButtonText (String());
    degRadTB->addListener (this);

    degRadTB->setBounds (186, 198, 23, 24);

    textButton.reset (new TextButton ("new button"));
    addAndMakeVisible (textButton.get());
    textButton->setButtonText (TRANS("Analyse"));
    textButton->addListener (this);
    textButton->setColour (TextButton::buttonColourId, Colour (0xff5c68a4));

    textButton->setBounds (228, 39, 60, 14);

    dispWindow.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (dispWindow.get());
    dispWindow->setEditableText (false);
    dispWindow->setJustificationType (Justification::centredLeft);
    dispWindow->setTextWhenNothingSelected (TRANS("Filters"));
    dispWindow->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    dispWindow->addItem (TRANS("Filters"), 1);
    dispWindow->addItem (TRANS("Corr"), 2);
    dispWindow->addItem (TRANS("L Diff"), 3);
    dispWindow->addListener (this);

    dispWindow->setBounds (721, 39, 63, 14);

    tb_loadJSON.reset (new TextButton ("new button"));
    addAndMakeVisible (tb_loadJSON.get());
    tb_loadJSON->setButtonText (TRANS("Import"));
    tb_loadJSON->setConnectedEdges (Button::ConnectedOnRight);
    tb_loadJSON->addListener (this);
    tb_loadJSON->setColour (TextButton::buttonColourId, Colour (0xff14889e));

    tb_loadJSON->setBounds (148, 39, 34, 14);

    tb_saveJSON.reset (new TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON.get());
    tb_saveJSON->setButtonText (TRANS("Export"));
    tb_saveJSON->setConnectedEdges (Button::ConnectedOnLeft);
    tb_saveJSON->addListener (this);
    tb_saveJSON->setColour (TextButton::buttonColourId, Colour (0xff224d97));
    tb_saveJSON->setColour (TextButton::buttonOnColourId, Colour (0xff181f9a));

    tb_saveJSON->setBounds (182, 39, 34, 14);

    CBencodingOrder.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBencodingOrder.get());
    CBencodingOrder->setEditableText (false);
    CBencodingOrder->setJustificationType (Justification::centredLeft);
    CBencodingOrder->setTextWhenNothingSelected (TRANS("Default"));
    CBencodingOrder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBencodingOrder->addListener (this);

    CBencodingOrder->setBounds (368, 274, 120, 20);

    applyDiffEQ.reset (new TextButton ("new button"));
    addAndMakeVisible (applyDiffEQ.get());
    applyDiffEQ->setButtonText (TRANS("Apply"));
    applyDiffEQ->addListener (this);
    applyDiffEQ->setColour (TextButton::buttonColourId, Colour (0xff42a2c8));

    applyDiffEQ->setBounds (427, 313, 61, 16);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 450);


    //[Constructor] You can add your own custom stuff here..
	hVst = ownerFilter;
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* remove the slider bit of these sliders */
    rSlider->setColour(Slider::trackColourId, Colours::transparentBlack);
    rSlider->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    rSlider->setSliderSnapsToMousePosition(false);
    RSlider->setColour(Slider::trackColourId, Colours::transparentBlack);
    RSlider->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    RSlider->setSliderSnapsToMousePosition(false);
    QSlider->setColour(Slider::trackColourId, Colours::transparentBlack);
    QSlider->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    QSlider->setSliderSnapsToMousePosition(false);

    /* create EQ window and analysis windows */
    addAndMakeVisible (eqviewIncluded = new eqview(556, 209, 30.0f, 20e3f, -30.0f, 60.0f, 48e3f )); /* TODO: switch to the more general "anaview"  */
    eqviewIncluded->setAlwaysOnTop(true);
    eqviewIncluded->setTopLeftPosition(228, 56);
    eqviewIncluded->setVisible(true);
    addAndMakeVisible (cohviewIncluded = new anaview(556, 209, 30.0f, 20e3f, 0.0f, 1.0f, TRANS("Spatial Corr. (T:I)"), 1, 48e3f ));
    cohviewIncluded->setAlwaysOnTop(true);
    cohviewIncluded->setTopLeftPosition(228, 56);
    cohviewIncluded->setVisible(false);
    addAndMakeVisible (ldiffviewIncluded = new anaview(556, 209, 30.0f, 20e3f, -30, 10, TRANS("Level Diff. (dB)"), 10.0f, 48e3f ));
    ldiffviewIncluded->setAlwaysOnTop(true);
    ldiffviewIncluded->setTopLeftPosition(228, 56);
    ldiffviewIncluded->setVisible(false);
    dispID = SHOW_EQ;
    needScreenRefreshFLAG = true;

    /* add master decoding order options */
    CBencodingOrder->addItem (TRANS("1st order"), ENCODING_ORDER_FIRST);
    CBencodingOrder->addItem (TRANS("2nd order"), ENCODING_ORDER_SECOND);
    CBencodingOrder->addItem (TRANS("3rd order"), ENCODING_ORDER_THIRD);
    CBencodingOrder->addItem (TRANS("4th order"), ENCODING_ORDER_FOURTH);
    CBencodingOrder->addItem (TRANS("5th order"), ENCODING_ORDER_FIFTH);
    CBencodingOrder->addItem (TRANS("6th order"), ENCODING_ORDER_SIXTH);
    CBencodingOrder->addItem (TRANS("7th order"), ENCODING_ORDER_SEVENTH);

    /* pass handles to data required for eq and analysis displays */
    int numFreqPoints, numCurves;
    float* freqVector = array2sh_getFreqVector(hVst->hA2sh, &numFreqPoints);
    float** solidCurves = array2sh_getbN_inv(hVst->hA2sh, &numCurves, &numFreqPoints);
    eqviewIncluded->setSolidCurves_Handle(freqVector, solidCurves, numFreqPoints, numCurves);
    float** faintCurves = array2sh_getbN_modal(hVst->hA2sh, &numCurves, &numFreqPoints);
    eqviewIncluded->setFaintCurves_Handle(freqVector, faintCurves, numFreqPoints, numCurves);
    float* dataHandle = array2sh_getSpatialCorrelation_Handle(hVst->hA2sh, &numCurves, &numFreqPoints);
    cohviewIncluded->setSolidCurves_Handle(freqVector, dataHandle, numFreqPoints, numCurves);
    dataHandle = array2sh_getLevelDifference_Handle(hVst->hA2sh, &numCurves, &numFreqPoints);
    ldiffviewIncluded->setSolidCurves_Handle(freqVector, dataHandle, numFreqPoints, numCurves);

    /* grab current parameter settings */
    CBencodingOrder->setSelectedId(array2sh_getEncodingOrder(hVst->hA2sh), dontSendNotification);
    arrayTypeCB->setSelectedId(array2sh_getArrayType(hVst->hA2sh), dontSendNotification);
    QSlider->setRange(array2sh_getMinNumSensors(hVst->hA2sh), array2sh_getMaxNumSensors(), 1);
    QSlider->setValue(array2sh_getNumSensors(hVst->hA2sh), dontSendNotification);
    rSlider->setValue(array2sh_getr(hVst->hA2sh)*1e3f, dontSendNotification);
    RSlider->setValue(array2sh_getR(hVst->hA2sh)*1e3f, dontSendNotification);
    cSlider->setValue(array2sh_getc(hVst->hA2sh), dontSendNotification);
    regAmountSlider->setValue(array2sh_getRegPar(hVst->hA2sh), dontSendNotification);
    CHOrderingCB->setSelectedId(array2sh_getChOrder(hVst->hA2sh), dontSendNotification);
    normalisationCB->setSelectedId(array2sh_getNormType(hVst->hA2sh), dontSendNotification);
    gainSlider->setValue(array2sh_getGain(hVst->hA2sh), dontSendNotification);
    showDegreesInstead = false;
    degRadTB->setToggleState(showDegreesInstead, dontSendNotification);

    /* add filter options */
    filterTypeCB->addItem (TRANS("Soft-Limiting"), FILTER_SOFT_LIM);
    filterTypeCB->addItem (TRANS("Tikhonov"), FILTER_TIKHONOV);
    filterTypeCB->addItem (TRANS("Z-Style"), FILTER_Z_STYLE);
    filterTypeCB->addItem (TRANS("Z-Style (max_rE)"), FILTER_Z_STYLE_MAXRE);
    filterTypeCB->setSelectedId(array2sh_getFilterType(hVst->hA2sh), dontSendNotification);

    /* add weight options */
    weightTypeCB->addItem (TRANS("Rigid-omni"), WEIGHT_RIGID_OMNI);
    weightTypeCB->addItem (TRANS("Rigid-cardioid"), WEIGHT_RIGID_CARD);
    //weightTypeCB->addItem (TRANS("Rigid-dipole"), WEIGHT_RIGID_DIPOLE);
    weightTypeCB->addItem (TRANS("Open-omni"), WEIGHT_OPEN_OMNI);
    weightTypeCB->addItem (TRANS("Open-cardioid"), WEIGHT_OPEN_CARD);
    //weightTypeCB->addItem (TRANS("Open-dipole"), WEIGHT_OPEN_DIPOLE);
    weightTypeCB->setSelectedId(array2sh_getWeightType(hVst->hA2sh), dontSendNotification);

    /* Hide decoding orders that are unsuitable for number of sensors */
    for(int i=1; i<=7; i++)
        CBencodingOrder->setItemEnabled(i, (i+1)*(i+1) <= array2sh_getNumSensors(hVst->hA2sh) ? true : false);

    /* gain range should change with order */
    int curOrder = array2sh_getEncodingOrder(hVst->hA2sh);
    gainSlider->setRange (-10-(curOrder*curOrder), 5+curOrder, 0.01);

    /* sensor coord table */
    addAndMakeVisible (sensorCoordsVP = new Viewport ("new viewport"));
    sensorCoordsView_handle = new sensorCoordsView(ownerFilter, MAX_NUM_CHANNELS, array2sh_getNumSensors(hVst->hA2sh), showDegreesInstead);
    sensorCoordsVP->setViewedComponent (sensorCoordsView_handle);
    sensorCoordsVP->setScrollBarsShown (true, false);
    sensorCoordsVP->setAlwaysOnTop(true);
    sensorCoordsVP->setBounds(24, 224, 184, 200);
    sensorCoordsView_handle->setQ(array2sh_getNumSensors(hVst->hA2sh));

    /* disable unsuitable parameters */
    bool shouldBeEnabled = array2sh_getWeightType(hVst->hA2sh) > WEIGHT_RIGID_DIPOLE ? false : true; /* is it a rigid array? */
    RSlider->setEnabled(shouldBeEnabled);
    shouldBeEnabled = array2sh_getArrayType(hVst->hA2sh) != ARRAY_SPHERICAL ? false : true;  /* is it a cylindrical array? */
    weightTypeCB->setItemEnabled(WEIGHT_RIGID_CARD, shouldBeEnabled);
    weightTypeCB->setItemEnabled(WEIGHT_RIGID_DIPOLE, shouldBeEnabled);
    weightTypeCB->setItemEnabled(WEIGHT_OPEN_CARD, shouldBeEnabled);
    weightTypeCB->setItemEnabled(WEIGHT_OPEN_DIPOLE, shouldBeEnabled);
//    if((array2sh_getWeightType(hVst->hA2sh) == 3) || (array2sh_getWeightType(hVst->hA2sh) == 4 ))
//        weightTypeCB->setSelectedId(1, dontSendNotification);
//    regAmountSlider->setEnabled(shouldBeEnabled);

    /* Presets */
    presetCB->setTextWhenNothingSelected (TRANS("Default"));
#ifdef ENABLE_SENNHEISER_AMBEO_PRESET
    presetCB->addItem (TRANS("Sennheiser Ambeo"), PRESET_SENNHEISER_AMBEO);
#endif
#ifdef ENABLE_CORE_SOUND_TETRAMIC_PRESET
    presetCB->addItem (TRANS("Core Sound TetraMic"), PRESET_CORE_SOUND_TETRAMIC);
#endif
#ifdef ENABLE_SOUND_FIELD_SPS200_PRESET
    presetCB->addItem (TRANS("Sound-field SPS200"), PRESET_SOUND_FIELD_SPS200);
#endif
#ifdef ENABLE_ZYLIA_1D_PRESET
    presetCB->addItem (TRANS("Zylia 1D"), PRESET_ZYLIA_1D);
#endif
#ifdef ENABLE_EIGENMIKE32_PRESET
    presetCB->addItem (TRANS("Eigenmike32"), PRESET_EIGENMIKE32);
#endif
#ifdef ENABLE_DTU_MIC_PRESET
    presetCB->addItem (TRANS("DTU mic"), PRESET_DTU_MIC );
#endif
#ifdef ENABLE_AALTO_HYDROPHONE_PRESET
    presetCB->addItem (TRANS("Aalto Hydro"), PRESET_AALTO_HYDROPHONE);
#endif
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

    presetCB = nullptr;
    arrayTypeCB = nullptr;
    QSlider = nullptr;
    rSlider = nullptr;
    RSlider = nullptr;
    cSlider = nullptr;
    weightTypeCB = nullptr;
    filterTypeCB = nullptr;
    regAmountSlider = nullptr;
    CHOrderingCB = nullptr;
    normalisationCB = nullptr;
    gainSlider = nullptr;
    degRadTB = nullptr;
    textButton = nullptr;
    dispWindow = nullptr;
    tb_loadJSON = nullptr;
    tb_saveJSON = nullptr;
    CBencodingOrder = nullptr;
    applyDiffEQ = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    eqviewIncluded = nullptr;
    sensorCoordsVP = nullptr;
    sensorCoordsView_handle = nullptr;
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    {
        int x = 0, y = 30, width = 800, height = 420;
        Colour fillColour1 = Colour (0xff5b6d76), fillColour2 = Colour (0xff073642);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       424.0f - 0.0f + x,
                                       160.0f - 30.0f + y,
                                       fillColour2,
                                       696.0f - 0.0f + x,
                                       440.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 228, y = 56, width = 556, height = 209;
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
        int x = 280, y = 70, width = 456, height = 158;
        Colour fillColour = Colour (0x13000000);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 506, y = 264, width = 278, height = 104;
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
        int x = 506, y = 264, width = 278, height = 104;
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
        int x = 506, y = 367, width = 278, height = 69;
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
        int x = 228, y = 264, width = 279, height = 172;
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
        int x = 228, y = 264, width = 279, height = 36;
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
        int x = 12, y = 87, width = 204, height = 106;
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
        int x = 0, y = 0, width = 800, height = 32;
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
        int x = 20, y = 57, width = 67, height = 30;
        String text (TRANS("Presets: "));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 20, y = 91, width = 180, height = 30;
        String text (TRANS("Number of Sensors: "));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 20, y = 123, width = 116, height = 30;
        String text (TRANS("Array radius (mm):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 20, y = 155, width = 180, height = 30;
        String text (TRANS("Baffle radius (mm):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 12, y = 192, width = 204, height = 244;
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
        int x = 240, y = 337, width = 172, height = 30;
        String text (TRANS("c (m/s):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 12, y = 56, width = 204, height = 32;
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
        int x = 240, y = 369, width = 172, height = 30;
        String text (TRANS("Array Type:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 240, y = 401, width = 172, height = 30;
        String text (TRANS("Baffle/Directivity:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 520, y = 268, width = 172, height = 30;
        String text (TRANS("Filter Approach:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 520, y = 301, width = 172, height = 30;
        String text (TRANS("Max Gain (dB):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 520, y = 369, width = 172, height = 30;
        String text (TRANS("CH Order:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 520, y = 401, width = 172, height = 30;
        String text (TRANS("Normalisation:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 520, y = 334, width = 172, height = 30;
        String text (TRANS("Post Gain (dB):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 75, y = 193, width = 101, height = 30;
        String text (TRANS("Azi   #   Elev"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 24, y = 224, width = 184, height = 200;
        Colour strokeColour = Colour (0x29b6b5b5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 179, y = 193, width = 24, height = 23;
        String text (CharPointer_UTF8 ("\xc2\xb0"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 92, y = 30, width = 88, height = 30;
        String text (TRANS("Inputs"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 440, y = 30, width = 149, height = 30;
        String text (TRANS("Encoding Settings"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 240, y = 268, width = 172, height = 30;
        String text (TRANS("Encoding Order:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
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
        g.setFont (Font (18.8f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 92, y = 0, width = 112, height = 32;
        String text (TRANS("Array2SH"));
        Colour fillColour = Colour (0xffe9ff00);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 240, y = 305, width = 172, height = 30;
        String text (TRANS("Diffuse-EQ Past Aliasing:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 328, y = 65, width = 392, height = 31;
        String text (TRANS("Press the \"Analyse\" button"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 291, y = 88, width = 477, height = 23;
        String text (TRANS("Corr: The spatial correlation is derived by comparing the patterns of the array responses with"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.0f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 291, y = 104, width = 477, height = 23;
        String text (TRANS("the patterns of ideal spherical harmonics, where \'1\' means they are perfect, and \'0\' completely "));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.0f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 291, y = 120, width = 477, height = 23;
        String text (TRANS("uncorrelated; the spatial aliasing frequency can therefore be observed for each order, as the "));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.0f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 291, y = 160, width = 477, height = 23;
        String text (TRANS("Ldiff: The level difference is the mean level difference over all directions (diffuse level differe-"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.0f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 291, y = 192, width = 477, height = 23;
        String text (TRANS("amplification limits [Max Gain (dB)] will result in noisier signals; however, this will also result in "));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.0f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 291, y = 176, width = 477, height = 23;
        String text (TRANS("nce) between the ideal and simulated components. One can observe that higher permitted "));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.0f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 291, y = 136, width = 477, height = 23;
        String text (TRANS("point where the spatial correlation tends towards 0."));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.0f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 291, y = 208, width = 477, height = 23;
        String text (TRANS("a wider frequency range of useful spherical harmonic components at each order."));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.0f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 673, y = 33, width = 119, height = 25;
        String text (TRANS("Display:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
    g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		185, 16, 530, 11,
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
            g.drawText(TRANS("Sample rate (") + String(array2sh_getSamplingRate(hVst->hA2sh)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(array2sh_getNumSensors(hVst->hA2sh)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(array2sh_getNSHrequired(hVst->hA2sh)) + TRANS(")"),
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

    if (comboBoxThatHasChanged == presetCB.get())
    {
        //[UserComboBoxCode_presetCB] -- add your combo box handling code here..
        array2sh_setPreset(hVst->hA2sh, (int)presetCB->getSelectedId());

        /* grab current parameter settings */
        arrayTypeCB->setSelectedId(array2sh_getArrayType(hVst->hA2sh), dontSendNotification);
        CBencodingOrder->setSelectedId(array2sh_getEncodingOrder(hVst->hA2sh), dontSendNotification);
        int curOrder = CBencodingOrder->getSelectedId();
        QSlider->setRange((curOrder+1)*(curOrder+1), array2sh_getMaxNumSensors(), 1);
        QSlider->setValue(array2sh_getNumSensors(hVst->hA2sh), dontSendNotification);
        rSlider->setValue(array2sh_getr(hVst->hA2sh)*1e3f, dontSendNotification);
        RSlider->setValue(array2sh_getR(hVst->hA2sh)*1e3f, dontSendNotification);
        cSlider->setValue(array2sh_getc(hVst->hA2sh), dontSendNotification);
        weightTypeCB->setSelectedId(array2sh_getWeightType(hVst->hA2sh), dontSendNotification);
        filterTypeCB->setSelectedId(array2sh_getFilterType(hVst->hA2sh), dontSendNotification);
        regAmountSlider->setValue(array2sh_getRegPar(hVst->hA2sh), dontSendNotification);
        CHOrderingCB->setSelectedId(array2sh_getChOrder(hVst->hA2sh), dontSendNotification);
        normalisationCB->setSelectedId(array2sh_getNormType(hVst->hA2sh), dontSendNotification);
        gainSlider->setValue(array2sh_getGain(hVst->hA2sh), dontSendNotification);

        /* update view windows */
        sensorCoordsView_handle->setQ(array2sh_getNumSensors(hVst->hA2sh));

        needScreenRefreshFLAG = true;
        //[/UserComboBoxCode_presetCB]
    }
    else if (comboBoxThatHasChanged == arrayTypeCB.get())
    {
        //[UserComboBoxCode_arrayTypeCB] -- add your combo box handling code here..
        array2sh_setArrayType(hVst->hA2sh, arrayTypeCB->getSelectedId());
        needScreenRefreshFLAG = true;
        //[/UserComboBoxCode_arrayTypeCB]
    }
    else if (comboBoxThatHasChanged == weightTypeCB.get())
    {
        //[UserComboBoxCode_weightTypeCB] -- add your combo box handling code here..
        array2sh_setWeightType(hVst->hA2sh, weightTypeCB->getSelectedId());
        needScreenRefreshFLAG = true;
        //[/UserComboBoxCode_weightTypeCB]
    }
    else if (comboBoxThatHasChanged == filterTypeCB.get())
    {
        //[UserComboBoxCode_filterTypeCB] -- add your combo box handling code here..
        array2sh_setFilterType(hVst->hA2sh, filterTypeCB->getSelectedId());
        needScreenRefreshFLAG = true;
        //[/UserComboBoxCode_filterTypeCB]
    }
    else if (comboBoxThatHasChanged == CHOrderingCB.get())
    {
        //[UserComboBoxCode_CHOrderingCB] -- add your combo box handling code here..
        array2sh_setChOrder(hVst->hA2sh, CHOrderingCB->getSelectedId());
        //[/UserComboBoxCode_CHOrderingCB]
    }
    else if (comboBoxThatHasChanged == normalisationCB.get())
    {
        //[UserComboBoxCode_normalisationCB] -- add your combo box handling code here..
        array2sh_setNormType(hVst->hA2sh, normalisationCB->getSelectedId());
        //[/UserComboBoxCode_normalisationCB]
    }
    else if (comboBoxThatHasChanged == dispWindow.get())
    {
        //[UserComboBoxCode_dispWindow] -- add your combo box handling code here..
        dispID = (DISP_WINDOW)dispWindow->getSelectedId();
        needScreenRefreshFLAG = 1;
        //[/UserComboBoxCode_dispWindow]
    }
    else if (comboBoxThatHasChanged == CBencodingOrder.get())
    {
        //[UserComboBoxCode_CBencodingOrder] -- add your combo box handling code here..
        int newOrder = CBencodingOrder->getSelectedId();
        array2sh_setEncodingOrder(hVst->hA2sh, newOrder);
        needScreenRefreshFLAG = true;
        //[/UserComboBoxCode_CBencodingOrder]
    }

    //[UsercomboBoxChanged_Post]
    /* disable unsuitable parameters */
    bool shouldBeEnabled = array2sh_getWeightType(hVst->hA2sh) > WEIGHT_RIGID_DIPOLE ? false : true; /* is it a rigid array? */
    RSlider->setEnabled(shouldBeEnabled);
    shouldBeEnabled = array2sh_getArrayType(hVst->hA2sh) != ARRAY_SPHERICAL ? false : true;  /* is it a cylindrical array? */
    weightTypeCB->setItemEnabled(WEIGHT_RIGID_CARD, shouldBeEnabled);
    weightTypeCB->setItemEnabled(WEIGHT_RIGID_DIPOLE, shouldBeEnabled);
    weightTypeCB->setItemEnabled(WEIGHT_OPEN_CARD, shouldBeEnabled);
    weightTypeCB->setItemEnabled(WEIGHT_OPEN_DIPOLE, shouldBeEnabled);
//    if( (array2sh_getArrayType(hVst->hA2sh) == 2) && ((array2sh_getWeightType(hVst->hA2sh) == 3) || (array2sh_getWeightType(hVst->hA2sh) == 4)) )
//        weightTypeCB->setSelectedId(1, sendNotification); /* force a suitable option */

    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == QSlider.get())
    {
        //[UserSliderCode_QSlider] -- add your slider handling code here..
        if(array2sh_getMinNumSensors(hVst->hA2sh)<= (int)QSlider->getValue())
            array2sh_setNumSensors(hVst->hA2sh, (int)QSlider->getValue());
        needScreenRefreshFLAG = true;
        //[/UserSliderCode_QSlider]
    }
    else if (sliderThatWasMoved == rSlider.get())
    {
        //[UserSliderCode_rSlider] -- add your slider handling code here..
        array2sh_setr(hVst->hA2sh, (float)rSlider->getValue()/1e3f);
        needScreenRefreshFLAG = true;
        //[/UserSliderCode_rSlider]
    }
    else if (sliderThatWasMoved == RSlider.get())
    {
        //[UserSliderCode_RSlider] -- add your slider handling code here..
        array2sh_setR(hVst->hA2sh, (float)RSlider->getValue()/1e3f);
        bool changerToo = (array2sh_getWeightType(hVst->hA2sh) == WEIGHT_RIGID_OMNI) ||
            (array2sh_getWeightType(hVst->hA2sh) == WEIGHT_RIGID_CARD) ||
            (array2sh_getWeightType(hVst->hA2sh) == WEIGHT_RIGID_DIPOLE) ? true : false; /* is it a rigid array? */
        if(changerToo){
            array2sh_setr(hVst->hA2sh, (float)RSlider->getValue()/1e3f);
            rSlider->setValue(RSlider->getValue(), dontSendNotification);
        }
        needScreenRefreshFLAG = true;
        //[/UserSliderCode_RSlider]
    }
    else if (sliderThatWasMoved == cSlider.get())
    {
        //[UserSliderCode_cSlider] -- add your slider handling code here..
        array2sh_setc(hVst->hA2sh, (float)cSlider->getValue());
        needScreenRefreshFLAG = true;
        //[/UserSliderCode_cSlider]
    }
    else if (sliderThatWasMoved == regAmountSlider.get())
    {
        //[UserSliderCode_regAmountSlider] -- add your slider handling code here..
        array2sh_setRegPar(hVst->hA2sh, (float)regAmountSlider->getValue());
        needScreenRefreshFLAG = true;
        //[/UserSliderCode_regAmountSlider]
    }
    else if (sliderThatWasMoved == gainSlider.get())
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
        array2sh_setGain(hVst->hA2sh, (float)gainSlider->getValue());
        //[/UserSliderCode_gainSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == degRadTB.get())
    {
        //[UserButtonCode_degRadTB] -- add your button handler code here..
        showDegreesInstead = degRadTB->getToggleState();
        sensorCoordsView_handle->setUseDegreesInstead(showDegreesInstead);
        //[/UserButtonCode_degRadTB]
    }
    else if (buttonThatWasClicked == textButton.get())
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
        array2sh_evaluateFilters(hVst->hA2sh);
        //[/UserButtonCode_textButton]
    }
    else if (buttonThatWasClicked == tb_loadJSON.get())
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
    else if (buttonThatWasClicked == tb_saveJSON.get())
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
    else if (buttonThatWasClicked == applyDiffEQ.get())
    {
        //[UserButtonCode_applyDiffEQ] -- add your button handler code here..
        array2sh_applyDiffEQpastAliasing(hVst->hA2sh);
        //[/UserButtonCode_applyDiffEQ]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* these parameters can change internally */
    RSlider->setValue(array2sh_getR(hVst->hA2sh)*1e3f, dontSendNotification);
    CBencodingOrder->setSelectedId(array2sh_getEncodingOrder(hVst->hA2sh), dontSendNotification);
    int curOrder = CBencodingOrder->getSelectedId();
    QSlider->setRange((curOrder+1)*(curOrder+1), array2sh_getMaxNumSensors(), 1);
    QSlider->setValue(array2sh_getNumSensors(hVst->hA2sh), dontSendNotification);
    sensorCoordsView_handle->setQ(array2sh_getNumSensors(hVst->hA2sh));

#ifndef __APPLE__
	/* Some parameters shouldn't be enabled if playback is ongoing */
    if (hVst->getIsPlaying()){
		textButton->setEnabled(false);
        applyDiffEQ->setEnabled(false);
    }
	else {
		textButton->setEnabled(true);
        applyDiffEQ->setEnabled(true);
		array2sh_checkReInit(hVst->hA2sh);
	}
#endif

    /* draw magnitude/spatial-correlation/level-difference curves */
    if (needScreenRefreshFLAG || array2sh_getEvalReady(hVst->hA2sh)){
        switch(dispID){
            default:
            case SHOW_EQ:
                eqviewIncluded->setNumCurves(array2sh_getEncodingOrder(hVst->hA2sh)+1);
                eqviewIncluded->setVisible(true);
                cohviewIncluded->setVisible(false);
                ldiffviewIncluded->setVisible(false);
                eqviewIncluded->repaint();
                break;
            case SHOW_SPATIAL_COH:
                eqviewIncluded->setVisible(false);
                ldiffviewIncluded->setVisible(false);
                if(array2sh_getIsEvalValid(hVst->hA2sh)){
                    cohviewIncluded->setNumCurves(array2sh_getEncodingOrder(hVst->hA2sh)+1);
                    cohviewIncluded->setVisible(true);
                    cohviewIncluded->repaint();
                }
                else
                    cohviewIncluded->setVisible(false);
                break;
            case SHOW_LEVEL_DIFF:
                eqviewIncluded->setVisible(false);
                cohviewIncluded->setVisible(false);
                if(array2sh_getIsEvalValid(hVst->hA2sh)){
                    ldiffviewIncluded->setNumCurves(array2sh_getEncodingOrder(hVst->hA2sh)+1);
                    ldiffviewIncluded->setVisible(true);
                    ldiffviewIncluded->repaint();
                }
                else
                    ldiffviewIncluded->setVisible(false);
                break;
        }
        needScreenRefreshFLAG = false;
    }

    /* gain range should ideally change with order */
    gainSlider->setRange (-10-(curOrder*curOrder), 5+curOrder, 0.01);

    /* Hide decoding orders that are unsuitable for the current number of sensors */
    for(int i=1; i<=7; i++)
        CBencodingOrder->setItemEnabled(i, (i+1)*(i+1) <= array2sh_getNumSensors(hVst->hA2sh) ? true : false);

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ( !((array2sh_getSamplingRate(hVst->hA2sh) == 44.1e3) || (array2sh_getSamplingRate(hVst->hA2sh) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < array2sh_getNumSensors(hVst->hA2sh))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumOutputs() < array2sh_getNSHrequired(hVst->hA2sh))){
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
                 variableInitialisers="AudioProcessorEditor(ownerFilter)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.33" fixedSize="1"
                 initialWidth="800" initialHeight="450">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 800 420" fill=" radial: 424 160, 696 440, 0=ff5b6d76, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="228 56 556 209" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="280 70 456 158" fill="solid: 13000000" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="506 264 278 104" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="506 264 278 104" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="506 367 278 69" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="228 264 279 172" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="228 264 279 36" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 87 204 106" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="0 0 800 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <TEXT pos="20 57 67 30" fill="solid: ffffffff" hasStroke="0" text="Presets: "
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="20 91 180 30" fill="solid: ffffffff" hasStroke="0" text="Number of Sensors: "
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="20 123 116 30" fill="solid: ffffffff" hasStroke="0" text="Array radius (mm):"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="20 155 180 30" fill="solid: ffffffff" hasStroke="0" text="Baffle radius (mm):"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="12 192 204 244" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="240 337 172 30" fill="solid: ffffffff" hasStroke="0" text="c (m/s):"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="12 56 204 32" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="240 369 172 30" fill="solid: ffffffff" hasStroke="0" text="Array Type:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="240 401 172 30" fill="solid: ffffffff" hasStroke="0" text="Baffle/Directivity:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="520 268 172 30" fill="solid: ffffffff" hasStroke="0" text="Filter Approach:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="520 301 172 30" fill="solid: ffffffff" hasStroke="0" text="Max Gain (dB):"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="520 369 172 30" fill="solid: ffffffff" hasStroke="0" text="CH Order:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="520 401 172 30" fill="solid: ffffffff" hasStroke="0" text="Normalisation:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="520 334 172 30" fill="solid: ffffffff" hasStroke="0" text="Post Gain (dB):"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="75 193 101 30" fill="solid: ffffffff" hasStroke="0" text="Azi   #   Elev"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="24 224 184 200" fill="solid: 39a52a" hasStroke="1" stroke="1, mitered, butt"
          strokeColour="solid: 29b6b5b5"/>
    <TEXT pos="179 193 24 23" fill="solid: ffffffff" hasStroke="0" text="&#176;"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 30 88 30" fill="solid: ffffffff" hasStroke="0" text="Inputs"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="440 30 149 30" fill="solid: ffffffff" hasStroke="0" text="Encoding Settings"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="240 268 172 30" fill="solid: ffffffff" hasStroke="0" text="Encoding Order:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 0 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.80000000000000071054" kerning="0.0"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 0 112 32" fill="solid: ffe9ff00" hasStroke="0" text="Array2SH"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="240 305 172 30" fill="solid: ffffffff" hasStroke="0" text="Diffuse-EQ Past Aliasing:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="328 65 392 31" fill="solid: ffffffff" hasStroke="0" text="Press the &quot;Analyse&quot; button"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="291 88 477 23" fill="solid: ffffffff" hasStroke="0" text="Corr: The spatial correlation is derived by comparing the patterns of the array responses with"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
    <TEXT pos="291 104 477 23" fill="solid: ffffffff" hasStroke="0" text="the patterns of ideal spherical harmonics, where '1' means they are perfect, and '0' completely "
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
    <TEXT pos="291 120 477 23" fill="solid: ffffffff" hasStroke="0" text="uncorrelated; the spatial aliasing frequency can therefore be observed for each order, as the "
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
    <TEXT pos="291 160 477 23" fill="solid: ffffffff" hasStroke="0" text="Ldiff: The level difference is the mean level difference over all directions (diffuse level differe-"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
    <TEXT pos="291 192 477 23" fill="solid: ffffffff" hasStroke="0" text="amplification limits [Max Gain (dB)] will result in noisier signals; however, this will also result in "
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
    <TEXT pos="291 176 477 23" fill="solid: ffffffff" hasStroke="0" text="nce) between the ideal and simulated components. One can observe that higher permitted "
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
    <TEXT pos="291 136 477 23" fill="solid: ffffffff" hasStroke="0" text="point where the spatial correlation tends towards 0."
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
    <TEXT pos="291 208 477 23" fill="solid: ffffffff" hasStroke="0" text="a wider frequency range of useful spherical harmonic components at each order."
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
    <TEXT pos="673 33 119 25" fill="solid: ffffffff" hasStroke="0" text="Display:"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <COMBOBOX name="new combo box" id="abcd469891fabf2d" memberName="presetCB"
            virtualName="" explicitFocusOrder="0" pos="88 64 120 16" editable="0"
            layout="33" items="Default" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="ee4eaf9d9b41f219" memberName="arrayTypeCB"
            virtualName="" explicitFocusOrder="0" pos="368 378 120 16" editable="0"
            layout="33" items="Spherical&#10;Cylindrical" textWhenNonSelected="Spherical"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="93dd93c125dcb3b3" memberName="QSlider"
          virtualName="" explicitFocusOrder="0" pos="156 99 52 16" min="4.0"
          max="64.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="45" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="f6fe97a46cc051e2" memberName="rSlider"
          virtualName="" explicitFocusOrder="0" pos="156 131 52 16" min="1.0"
          max="200.0" int="0.01000000000000000021" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="45"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="41d575604e9dcd3a" memberName="RSlider"
          virtualName="" explicitFocusOrder="0" pos="156 163 52 16" trackcol="ff181f22"
          rotaryslideroutline="ff263238" min="1.0" max="200.0" int="0.01000000000000000021"
          style="LinearHorizontal" textBoxPos="TextBoxRight" textBoxEditable="1"
          textBoxWidth="45" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="c3b6d9fc71650ee4" memberName="cSlider"
          virtualName="" explicitFocusOrder="0" pos="364 347 124 16" min="200.0"
          max="2000.0" int="0.10000000000000000555" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="55"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="ea26910fd5e03b81" memberName="weightTypeCB"
            virtualName="" explicitFocusOrder="0" pos="368 410 120 16" editable="0"
            layout="33" items="" textWhenNonSelected="Rigid" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="d818d0d5310dc52a" memberName="filterTypeCB"
            virtualName="" explicitFocusOrder="0" pos="640 276 128 16" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="9f4f4ac547d19161" memberName="regAmountSlider"
          virtualName="" explicitFocusOrder="0" pos="640 308 128 16" min="0.0"
          max="80.0" int="0.01000000000000000021" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="55"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="44b90530e58253e" memberName="CHOrderingCB"
            virtualName="" explicitFocusOrder="0" pos="640 377 128 16" editable="0"
            layout="33" items="ACN" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="caeee0fc74db72a4" memberName="normalisationCB"
            virtualName="" explicitFocusOrder="0" pos="640 409 128 16" editable="0"
            layout="33" items="N3D&#10;SN3D" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="ee4c42494881e7dc" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="640 341 128 16" min="-60.0"
          max="60.0" int="0.01000000000000000021" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="55"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="3fdbf3711d00f4db" memberName="degRadTB"
                virtualName="" explicitFocusOrder="0" pos="186 198 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTBUTTON name="new button" id="dde3f82641b3717c" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="228 39 60 14" bgColOff="ff5c68a4"
              buttonText="Analyse" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="new combo box" id="fb3d8d6828195921" memberName="dispWindow"
            virtualName="" explicitFocusOrder="0" pos="721 39 63 14" editable="0"
            layout="33" items="Filters&#10;Corr&#10;L Diff" textWhenNonSelected="Filters"
            textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button" id="527e24c6748d02d4" memberName="tb_loadJSON"
              virtualName="" explicitFocusOrder="0" pos="148 39 34 14" bgColOff="ff14889e"
              buttonText="Import" connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="48c5d3526dcfe64f" memberName="tb_saveJSON"
              virtualName="" explicitFocusOrder="0" pos="182 39 34 14" bgColOff="ff224d97"
              bgColOn="ff181f9a" buttonText="Export" connectedEdges="1" needsCallback="1"
              radioGroupId="0"/>
  <COMBOBOX name="new combo box" id="a465903000494955" memberName="CBencodingOrder"
            virtualName="" explicitFocusOrder="0" pos="368 274 120 20" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button" id="9682df42480f4111" memberName="applyDiffEQ"
              virtualName="" explicitFocusOrder="0" pos="427 313 61 16" bgColOff="ff42a2c8"
              buttonText="Apply" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
