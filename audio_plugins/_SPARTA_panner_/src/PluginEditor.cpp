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

    CBsourceDirsPreset.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBsourceDirsPreset.get());
    CBsourceDirsPreset->setEditableText (false);
    CBsourceDirsPreset->setJustificationType (Justification::centredLeft);
    CBsourceDirsPreset->setTextWhenNothingSelected (String());
    CBsourceDirsPreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBsourceDirsPreset->addListener (this);

    CBsourceDirsPreset->setBounds (88, 64, 112, 20);

    SL_num_sources.reset (new Slider ("new slider"));
    addAndMakeVisible (SL_num_sources.get());
    SL_num_sources->setRange (1, 64, 1);
    SL_num_sources->setSliderStyle (Slider::LinearHorizontal);
    SL_num_sources->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    SL_num_sources->addListener (this);

    SL_num_sources->setBounds (80, 92, 120, 24);

    TB_showInputs.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_showInputs.get());
    TB_showInputs->setButtonText (String());
    TB_showInputs->addListener (this);

    TB_showInputs->setBounds (561, 316, 24, 24);

    TB_showOutputs.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_showOutputs.get());
    TB_showOutputs->setButtonText (String());
    TB_showOutputs->addListener (this);

    TB_showOutputs->setBounds (672, 316, 24, 24);

    SL_pValue.reset (new Slider ("new slider"));
    addAndMakeVisible (SL_pValue.get());
    SL_pValue->setRange (0, 1, 0.01);
    SL_pValue->setSliderStyle (Slider::LinearHorizontal);
    SL_pValue->setTextBoxStyle (Slider::TextBoxRight, false, 50, 20);
    SL_pValue->addListener (this);

    SL_pValue->setBounds (354, 326, 120, 15);

    CBsLoudspeakerDirsPreset.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBsLoudspeakerDirsPreset.get());
    CBsLoudspeakerDirsPreset->setEditableText (false);
    CBsLoudspeakerDirsPreset->setJustificationType (Justification::centredLeft);
    CBsLoudspeakerDirsPreset->setTextWhenNothingSelected (String());
    CBsLoudspeakerDirsPreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBsLoudspeakerDirsPreset->addListener (this);

    CBsLoudspeakerDirsPreset->setBounds (788, 66, 112, 20);

    SL_num_loudspeakers.reset (new Slider ("new slider"));
    addAndMakeVisible (SL_num_loudspeakers.get());
    SL_num_loudspeakers->setRange (2, 64, 1);
    SL_num_loudspeakers->setSliderStyle (Slider::LinearHorizontal);
    SL_num_loudspeakers->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    SL_num_loudspeakers->addListener (this);

    SL_num_loudspeakers->setBounds (780, 92, 120, 24);

    tb_loadJSON_src.reset (new TextButton ("new button"));
    addAndMakeVisible (tb_loadJSON_src.get());
    tb_loadJSON_src->setButtonText (TRANS("Import"));
    tb_loadJSON_src->setConnectedEdges (Button::ConnectedOnRight);
    tb_loadJSON_src->addListener (this);
    tb_loadJSON_src->setColour (TextButton::buttonColourId, Colour (0xff14889e));

    tb_loadJSON_src->setBounds (140, 41, 34, 14);

    tb_saveJSON_src.reset (new TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON_src.get());
    tb_saveJSON_src->setButtonText (TRANS("Export"));
    tb_saveJSON_src->setConnectedEdges (Button::ConnectedOnLeft);
    tb_saveJSON_src->addListener (this);
    tb_saveJSON_src->setColour (TextButton::buttonColourId, Colour (0xff224d97));
    tb_saveJSON_src->setColour (TextButton::buttonOnColourId, Colour (0xff181f9a));

    tb_saveJSON_src->setBounds (174, 41, 34, 14);

    tb_loadJSON_ls.reset (new TextButton ("new button"));
    addAndMakeVisible (tb_loadJSON_ls.get());
    tb_loadJSON_ls->setButtonText (TRANS("Import"));
    tb_loadJSON_ls->setConnectedEdges (Button::ConnectedOnRight);
    tb_loadJSON_ls->addListener (this);
    tb_loadJSON_ls->setColour (TextButton::buttonColourId, Colour (0xff14889e));

    tb_loadJSON_ls->setBounds (712, 41, 34, 14);

    tb_saveJSON_ls.reset (new TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON_ls.get());
    tb_saveJSON_ls->setButtonText (TRANS("Export"));
    tb_saveJSON_ls->setConnectedEdges (Button::ConnectedOnLeft);
    tb_saveJSON_ls->addListener (this);
    tb_saveJSON_ls->setColour (TextButton::buttonColourId, Colour (0xff224d97));
    tb_saveJSON_ls->setColour (TextButton::buttonOnColourId, Colour (0xff181f9a));

    tb_saveJSON_ls->setBounds (746, 41, 34, 14);

    SL_spread.reset (new Slider ("new slider"));
    addAndMakeVisible (SL_spread.get());
    SL_spread->setRange (0, 90, 1);
    SL_spread->setSliderStyle (Slider::LinearHorizontal);
    SL_spread->setTextBoxStyle (Slider::TextBoxRight, false, 50, 20);
    SL_spread->addListener (this);

    SL_spread->setBounds (224, 326, 120, 15);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (920, 356);


    //[Constructor] You can add your own custom stuff here..

    /* handle to pluginProcessor */
	hVst = ownerFilter;

    /* init OpenGL */
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* add source preset options */
#ifdef ENABLE_MONO_PRESET
    CBsourceDirsPreset->addItem (TRANS("Mono"), PRESET_MONO);
#endif
#ifdef ENABLE_STEREO_PRESET
    CBsourceDirsPreset->addItem (TRANS("Stereo"), PRESET_STEREO);
#endif
#ifdef ENABLE_5PX_PRESET
    CBsourceDirsPreset->addItem (TRANS("5.x"), PRESET_5PX);
#endif
#ifdef ENABLE_7PX_PRESET
    CBsourceDirsPreset->addItem (TRANS("7.x"), PRESET_7PX);
#endif
#ifdef ENABLE_8PX_PRESET
    CBsourceDirsPreset->addItem (TRANS("8.x"), PRESET_8PX);
#endif
#ifdef ENABLE_9PX_PRESET
    CBsourceDirsPreset->addItem (TRANS("9.x"), PRESET_9PX);
#endif
#ifdef ENABLE_10PX_PRESET
    CBsourceDirsPreset->addItem (TRANS("10.x"), PRESET_10PX);
#endif
#ifdef ENABLE_11PX_PRESET
    CBsourceDirsPreset->addItem (TRANS("11.x"), PRESET_11PX);
#endif
#ifdef ENABLE_11PX_7_4_PRESET
    CBsourceDirsPreset->addItem (TRANS("11.x (7+4)"), PRESET_11PX_7_4);
#endif
#ifdef ENABLE_13PX_PRESET
    CBsourceDirsPreset->addItem (TRANS("13.x"), PRESET_13PX);
#endif
#ifdef ENABLE_22PX_PRESET
    CBsourceDirsPreset->addItem (TRANS("22.x"), PRESET_22PX);
#endif
#ifdef ENABLE_AALTO_MCC_PRESET
    CBsourceDirsPreset->addItem (TRANS("Aalto MCC"), PRESET_AALTO_MCC);
#endif
#ifdef ENABLE_AALTO_APAJA_PRESET
    CBsourceDirsPreset->addItem (TRANS("Aalto Apaja"), PRESET_AALTO_APAJA);
#endif
#ifdef ENABLE_AALTO_APAJA2_PRESET
    CBsourceDirsPreset->addItem (TRANS("Aalto Apaja 2.0"), PRESET_AALTO_APAJA2);
#endif
#ifdef ENABLE_AALTO_LR_PRESET
    CBsourceDirsPreset->addItem (TRANS("Aalto LR"), PRESET_AALTO_LR);
#endif
#ifdef ENABLE_DTU_AVIL_PRESET
    CBsourceDirsPreset->addItem (TRANS("DTU AVIL"), PRESET_DTU_AVIL);
#endif
#ifdef ENABLE_T_DESIGN_4_PRESET
    CBsourceDirsPreset->addItem (TRANS("T-design (4)"), PRESET_T_DESIGN_4);
#endif
#ifdef ENABLE_T_DESIGN_12_PRESET
    CBsourceDirsPreset->addItem (TRANS("T-design (12)"), PRESET_T_DESIGN_12);
#endif
#ifdef ENABLE_T_DESIGN_24_PRESET
    CBsourceDirsPreset->addItem (TRANS("T-design (24)"), PRESET_T_DESIGN_24);
#endif
#ifdef ENABLE_T_DESIGN_36_PRESET
    CBsourceDirsPreset->addItem (TRANS("T-design (36)"), PRESET_T_DESIGN_36);
#endif
#ifdef ENABLE_T_DESIGN_48_PRESET
    CBsourceDirsPreset->addItem (TRANS("T-design (48)"), PRESET_T_DESIGN_48);
#endif
#ifdef ENABLE_T_DESIGN_60_PRESET
    CBsourceDirsPreset->addItem (TRANS("T-design (60)"), PRESET_T_DESIGN_60);
#endif

    /* add Loudspeaker preset options */
#ifdef ENABLE_STEREO_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("Stereo"), PRESET_STEREO);
#endif
#ifdef ENABLE_5PX_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("5.x"), PRESET_5PX);
#endif
#ifdef ENABLE_7PX_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("7.x"), PRESET_7PX);
#endif
#ifdef ENABLE_8PX_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("8.x"), PRESET_8PX);
#endif
#ifdef ENABLE_9PX_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("9.x"), PRESET_9PX);
#endif
#ifdef ENABLE_10PX_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("10.x"), PRESET_10PX);
#endif
#ifdef ENABLE_11PX_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("11.x"), PRESET_11PX);
#endif
#ifdef ENABLE_11PX_7_4_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("11.x (7+4)"), PRESET_11PX_7_4);
#endif
#ifdef ENABLE_13PX_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("13.x"), PRESET_13PX);
#endif
#ifdef ENABLE_22PX_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("22.x"), PRESET_22PX);
#endif
#ifdef ENABLE_AALTO_MCC_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("Aalto MCC"), PRESET_AALTO_MCC);
#endif
#ifdef ENABLE_AALTO_APAJA_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("Aalto Apaja"), PRESET_AALTO_APAJA);
#endif
#ifdef ENABLE_AALTO_APAJA2_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("Aalto Apaja 2.0"), PRESET_AALTO_APAJA2);
#endif
#ifdef ENABLE_AALTO_LR_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("Aalto LR"), PRESET_AALTO_LR);
#endif
#ifdef ENABLE_DTU_AVIL_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("DTU AVIL"), PRESET_DTU_AVIL);
#endif
#ifdef ENABLE_T_DESIGN_4_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("T-design (4)"), PRESET_T_DESIGN_4);
#endif
#ifdef ENABLE_T_DESIGN_12_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("T-design (12)"), PRESET_T_DESIGN_12);
#endif
#ifdef ENABLE_T_DESIGN_24_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("T-design (24)"), PRESET_T_DESIGN_24);
#endif
#ifdef ENABLE_T_DESIGN_36_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("T-design (36)"), PRESET_T_DESIGN_36);
#endif
#ifdef ENABLE_T_DESIGN_48_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("T-design (48)"), PRESET_T_DESIGN_48);
#endif
#ifdef ENABLE_T_DESIGN_60_PRESET
    CBsLoudspeakerDirsPreset->addItem (TRANS("T-design (60)"), PRESET_T_DESIGN_60);
#endif

    /* source coordinates viewport */
    addAndMakeVisible (sourceCoordsVP = new Viewport ("new viewport"));
    sourceCoordsView_handle = new inputCoordsView(ownerFilter, MAX_NUM_CHANNELS, panner_getNumSources(hVst->hPan));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(22, 153, 184, 180);
    sourceCoordsView_handle->setNCH(panner_getNumSources(hVst->hPan));

    /* loudspeaker coordinates viewport */
    addAndMakeVisible (loudspeakerCoordsVP = new Viewport ("new viewport"));
    loudspeakerCoordsView_handle = new outputCoordsView(ownerFilter, MAX_NUM_CHANNELS, panner_getNumLoudspeakers(hVst->hPan));
    loudspeakerCoordsVP->setViewedComponent (loudspeakerCoordsView_handle);
    loudspeakerCoordsVP->setScrollBarsShown (true, false);
    loudspeakerCoordsVP->setAlwaysOnTop(true);
    loudspeakerCoordsVP->setBounds(722, 153, 184, 180);
    loudspeakerCoordsView_handle->setNCH(panner_getNumLoudspeakers(hVst->hPan));

    /* grab current parameter settings */
    SL_num_sources->setValue(panner_getNumSources(hVst->hPan),dontSendNotification);
    TB_showInputs->setToggleState(true, dontSendNotification);
    TB_showOutputs->setToggleState(true, dontSendNotification);
    SL_pValue->setValue(panner_getDTT(hVst->hPan), dontSendNotification);
    SL_spread->setValue(panner_getSpread(hVst->hPan), dontSendNotification);

    /* create panning window */
    addAndMakeVisible (panWindow = new pannerView(ownerFilter, 480, 240));
    panWindow->setBounds (220, 58, 480, 240);
    panWindow->setShowInputs(TB_showInputs->getToggleState());
    panWindow->setShowOutputs(TB_showOutputs->getToggleState());
    refreshPanViewWindow = true;

	/* Specify screen refresh rate */
    startTimer(35);//80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    CBsourceDirsPreset = nullptr;
    SL_num_sources = nullptr;
    TB_showInputs = nullptr;
    TB_showOutputs = nullptr;
    SL_pValue = nullptr;
    CBsLoudspeakerDirsPreset = nullptr;
    SL_num_loudspeakers = nullptr;
    tb_loadJSON_src = nullptr;
    tb_saveJSON_src = nullptr;
    tb_loadJSON_ls = nullptr;
    tb_saveJSON_ls = nullptr;
    SL_spread = nullptr;


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
        int x = 0, y = 30, width = 920, height = 326;
        Colour fillColour1 = Colour (0xff5b6d76), fillColour2 = Colour (0xff073642);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       460.0f - 0.0f + x,
                                       184.0f - 30.0f + y,
                                       fillColour2,
                                       928.0f - 0.0f + x,
                                       368.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 350, y = 308, width = 131, height = 38;
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
        int x = 220, y = 308, width = 131, height = 38;
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
        int x = 12, y = 58, width = 196, height = 64;
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
        int x = 0, y = 0, width = 920, height = 32;
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
        int x = 23, y = 58, width = 67, height = 30;
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
        int x = 220, y = 58, width = 480, height = 240;
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
        int x = 12, y = 121, width = 196, height = 225;
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
        int x = 70, y = 123, width = 105, height = 32;
        String text (TRANS("Azi    #   Elev"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 480, y = 308, width = 220, height = 38;
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
        int x = 712, y = 58, width = 196, height = 64;
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
        int x = 712, y = 121, width = 196, height = 225;
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
        int x = 23, y = 88, width = 113, height = 30;
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
        int x = 84, y = 32, width = 113, height = 30;
        String text (TRANS("Inputs"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 789, y = 32, width = 113, height = 30;
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
        int x = 404, y = 32, width = 156, height = 30;
        String text (TRANS("Panning Window"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 486, y = 313, width = 132, height = 30;
        String text (TRANS("Show Inputs:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 588, y = 313, width = 132, height = 30;
        String text (TRANS("Show Outputs:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 354, y = 303, width = 123, height = 30;
        String text (TRANS("pValue Coeff:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 723, y = 58, width = 67, height = 30;
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
        int x = 770, y = 123, width = 105, height = 32;
        String text (TRANS("Azi    #   Elev"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 723, y = 88, width = 113, height = 30;
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
        String text (TRANS("Panner"));
        Colour fillColour = Colour (0xff0eff00);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		175, 16, 530, 11,
		Justification::centredLeft, true);

    /* spread text*/
    {
        float kerningFactor = 0.5f * panner_getSpread(hVst->hPan)/90.0f;
        int x = 205, y = 303, width = 167, height = 30;
        String text (CharPointer_UTF8 ("Spread (\xc2\xb0):"));
        Colour fillColour = Colours::white;
        g.setColour (fillColour);
        //g.setOpacity(1.0f-kerningFactor);
        g.setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Bold").withExtraKerningFactor (kerningFactor));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
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
            g.drawText(TRANS("Sample rate (") + String(panner_getDAWsamplerate(hVst->hPan)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(panner_getNumSources(hVst->hPan)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(panner_getNumLoudspeakers(hVst->hPan)) + TRANS(")"),
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

    if (comboBoxThatHasChanged == CBsourceDirsPreset.get())
    {
        //[UserComboBoxCode_CBsourceDirsPreset] -- add your combo box handling code here..
        panner_setInputConfigPreset(hVst->hPan, CBsourceDirsPreset->getSelectedId());
        refreshPanViewWindow = true;
        //[/UserComboBoxCode_CBsourceDirsPreset]
    }
    else if (comboBoxThatHasChanged == CBsLoudspeakerDirsPreset.get())
    {
        //[UserComboBoxCode_CBsLoudspeakerDirsPreset] -- add your combo box handling code here..
        panner_setOutputConfigPreset(hVst->hPan, CBsLoudspeakerDirsPreset->getSelectedId());
        refreshPanViewWindow = true;
        //[/UserComboBoxCode_CBsLoudspeakerDirsPreset]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == SL_num_sources.get())
    {
        //[UserSliderCode_SL_num_sources] -- add your slider handling code here..
        panner_setNumSources(hVst->hPan, (int)SL_num_sources->getValue());
        refreshPanViewWindow = true;
        //[/UserSliderCode_SL_num_sources]
    }
    else if (sliderThatWasMoved == SL_pValue.get())
    {
        //[UserSliderCode_SL_pValue] -- add your slider handling code here..
        panner_setDTT(hVst->hPan, (float)SL_pValue->getValue());
        //[/UserSliderCode_SL_pValue]
    }
    else if (sliderThatWasMoved == SL_num_loudspeakers.get())
    {
        //[UserSliderCode_SL_num_loudspeakers] -- add your slider handling code here..
        panner_setNumLoudspeakers(hVst->hPan, (int)SL_num_loudspeakers->getValue());
        //[/UserSliderCode_SL_num_loudspeakers]
    }
    else if (sliderThatWasMoved == SL_spread.get())
    {
        //[UserSliderCode_SL_spread] -- add your slider handling code here..
        panner_setSpread(hVst->hPan, (float)SL_spread->getValue());
        repaint(203, 303, 167, 30);
        //[/UserSliderCode_SL_spread]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == TB_showInputs.get())
    {
        //[UserButtonCode_TB_showInputs] -- add your button handler code here..
        panWindow->setShowInputs(TB_showInputs->getToggleState());
        refreshPanViewWindow = true;
        //[/UserButtonCode_TB_showInputs]
    }
    else if (buttonThatWasClicked == TB_showOutputs.get())
    {
        //[UserButtonCode_TB_showOutputs] -- add your button handler code here..
        panWindow->setShowOutputs(TB_showOutputs->getToggleState());
        refreshPanViewWindow = true;
        //[/UserButtonCode_TB_showOutputs]
    }
    else if (buttonThatWasClicked == tb_loadJSON_src.get())
    {
        //[UserButtonCode_tb_loadJSON_src] -- add your button handler code here..
        FileChooser myChooser ("Load configuration...",
                               hVst->getLastDir().exists() ? hVst->getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                               "*.json");
        if (myChooser.browseForFileToOpen()) {
            File configFile (myChooser.getResult());
            hVst->setLastDir(configFile.getParentDirectory());
            hVst->loadConfiguration (configFile, 0);
        }
        //[/UserButtonCode_tb_loadJSON_src]
    }
    else if (buttonThatWasClicked == tb_saveJSON_src.get())
    {
        //[UserButtonCode_tb_saveJSON_src] -- add your button handler code here..
        FileChooser myChooser ("Save configuration...",
                               hVst->getLastDir().exists() ? hVst->getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                               "*.json");
        if (myChooser.browseForFileToSave (true)) {
            File configFile (myChooser.getResult());
            hVst->setLastDir(configFile.getParentDirectory());
            hVst->saveConfigurationToFile (configFile, 0);
        }
        //[/UserButtonCode_tb_saveJSON_src]
    }
    else if (buttonThatWasClicked == tb_loadJSON_ls.get())
    {
        //[UserButtonCode_tb_loadJSON_ls] -- add your button handler code here..
        FileChooser myChooser ("Load configuration...",
                               hVst->getLastDir().exists() ? hVst->getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                               "*.json");
        if (myChooser.browseForFileToOpen()) {
            File configFile (myChooser.getResult());
            hVst->setLastDir(configFile.getParentDirectory());
            hVst->loadConfiguration (configFile, 1);
        }
        //[/UserButtonCode_tb_loadJSON_ls]
    }
    else if (buttonThatWasClicked == tb_saveJSON_ls.get())
    {
        //[UserButtonCode_tb_saveJSON_ls] -- add your button handler code here..
        FileChooser myChooser ("Save configuration...",
                               hVst->getLastDir().exists() ? hVst->getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                               "*.json");
        if (myChooser.browseForFileToSave (true)) {
            File configFile (myChooser.getResult());
            hVst->setLastDir(configFile.getParentDirectory());
            hVst->saveConfigurationToFile (configFile, 1);
        }
        //[/UserButtonCode_tb_saveJSON_ls]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* refresh parameters that can change internally */
    sourceCoordsView_handle->setNCH(panner_getNumSources(hVst->hPan));
    loudspeakerCoordsView_handle->setNCH(panner_getNumLoudspeakers(hVst->hPan));
    SL_num_sources->setValue(panner_getNumSources(hVst->hPan),dontSendNotification);
    SL_num_loudspeakers->setValue(panner_getNumLoudspeakers(hVst->hPan),dontSendNotification);

#ifndef __APPLE__
	/* Some parameters shouldn't be enabled if playback is ongoing */
	if (hVst->getIsPlaying()) {
		SL_num_loudspeakers->setEnabled(false);
		loudspeakerCoordsView_handle->setEnabled(false);
		CBsLoudspeakerDirsPreset->setEnabled(false);
	}
	else {
		SL_num_loudspeakers->setEnabled(true);
		loudspeakerCoordsView_handle->setEnabled(true);
		CBsLoudspeakerDirsPreset->setEnabled(true);
		panner_checkReInit(hVst->hPan);
	}
#endif
    if (hVst->getIsPlaying())
        SL_spread->setEnabled(false);
    else
        SL_spread->setEnabled(true);

    /* refresh pan view */
    if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) ||
       sourceCoordsView_handle->getHasASliderChanged() || loudspeakerCoordsView_handle->getHasASliderChanged() || hVst->getRefreshWindow()){
        panWindow->refreshPanView();
        refreshPanViewWindow = false;
        sourceCoordsView_handle->setHasASliderChange(false);
        loudspeakerCoordsView_handle->setHasASliderChange(false);
        hVst->setRefreshWindow(false);
    }

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ( !((panner_getDAWsamplerate(hVst->hPan) == 44.1e3) || (panner_getDAWsamplerate(hVst->hPan) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < panner_getNumSources(hVst->hPan))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumOutputs() < panner_getNumLoudspeakers(hVst->hPan))){
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
                 initialWidth="920" initialHeight="356">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 920 326" fill=" radial: 460 184, 928 368, 0=ff5b6d76, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="350 308 131 38" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="220 308 131 38" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 58 196 64" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="0 0 920 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <TEXT pos="23 58 67 30" fill="solid: ffffffff" hasStroke="0" text="Presets: "
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="220 58 480 240" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 121 196 225" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="70 123 105 32" fill="solid: ffffffff" hasStroke="0" text="Azi    #   Elev"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="480 308 220 38" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="712 58 196 64" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="712 121 196 225" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="23 88 113 30" fill="solid: ffffffff" hasStroke="0" text="N Chan:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="84 32 113 30" fill="solid: ffffffff" hasStroke="0" text="Inputs"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="789 32 113 30" fill="solid: ffffffff" hasStroke="0" text="Outputs"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="404 32 156 30" fill="solid: ffffffff" hasStroke="0" text="Panning Window"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="486 313 132 30" fill="solid: ffffffff" hasStroke="0" text="Show Inputs:"
          fontname="Default font" fontsize="13.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="588 313 132 30" fill="solid: ffffffff" hasStroke="0" text="Show Outputs:"
          fontname="Default font" fontsize="13.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="354 303 123 30" fill="solid: ffffffff" hasStroke="0" text="pValue Coeff:"
          fontname="Default font" fontsize="13.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="723 58 67 30" fill="solid: ffffffff" hasStroke="0" text="Presets: "
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="770 123 105 32" fill="solid: ffffffff" hasStroke="0" text="Azi    #   Elev"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="723 88 113 30" fill="solid: ffffffff" hasStroke="0" text="N Chan:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 0 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.80000000000000071054" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 0 112 32" fill="solid: ff0eff00" hasStroke="0" text="Panner"
          fontname="Default font" fontsize="18.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <COMBOBOX name="new combo box" id="5a2f99f88aa51390" memberName="CBsourceDirsPreset"
            virtualName="" explicitFocusOrder="0" pos="88 64 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="2c2a2b3d0614cc94" memberName="SL_num_sources"
          virtualName="" explicitFocusOrder="0" pos="80 92 120 24" min="1.00000000000000000000"
          max="64.00000000000000000000" int="1.00000000000000000000" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="74817bb8a57611dc" memberName="TB_showInputs"
                virtualName="" explicitFocusOrder="0" pos="561 316 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="1a1dfbb1d4296140" memberName="TB_showOutputs"
                virtualName="" explicitFocusOrder="0" pos="672 316 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="new slider" id="5b4f982e7ea9b2d5" memberName="SL_pValue"
          virtualName="" explicitFocusOrder="0" pos="354 326 120 15" min="0.00000000000000000000"
          max="1.00000000000000000000" int="0.01000000000000000021" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="50"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="cfd23f574e19957c" memberName="CBsLoudspeakerDirsPreset"
            virtualName="" explicitFocusOrder="0" pos="788 66 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="cbb243fa14b960d0" memberName="SL_num_loudspeakers"
          virtualName="" explicitFocusOrder="0" pos="780 92 120 24" min="2.00000000000000000000"
          max="64.00000000000000000000" int="1.00000000000000000000" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <TEXTBUTTON name="new button" id="527e24c6748d02d4" memberName="tb_loadJSON_src"
              virtualName="" explicitFocusOrder="0" pos="140 41 34 14" bgColOff="ff14889e"
              buttonText="Import" connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="48c5d3526dcfe64f" memberName="tb_saveJSON_src"
              virtualName="" explicitFocusOrder="0" pos="174 41 34 14" bgColOff="ff224d97"
              bgColOn="ff181f9a" buttonText="Export" connectedEdges="1" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="9e16f5d467ae2a3b" memberName="tb_loadJSON_ls"
              virtualName="" explicitFocusOrder="0" pos="712 41 34 14" bgColOff="ff14889e"
              buttonText="Import" connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="87186d3e46663c48" memberName="tb_saveJSON_ls"
              virtualName="" explicitFocusOrder="0" pos="746 41 34 14" bgColOff="ff224d97"
              bgColOn="ff181f9a" buttonText="Export" connectedEdges="1" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="new slider" id="502f78257b11f666" memberName="SL_spread"
          virtualName="" explicitFocusOrder="0" pos="224 326 120 15" min="0.00000000000000000000"
          max="90.00000000000000000000" int="1.00000000000000000000" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="50"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
