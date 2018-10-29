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
    : AudioProcessorEditor(ownerFilter), fileChooser ("File", File(), true, false, false,
      "*.sofa;*.nc;", String(),
      "Load SOFA File")
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    CBsourceDirsPreset.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBsourceDirsPreset.get());
    CBsourceDirsPreset->setEditableText (false);
    CBsourceDirsPreset->setJustificationType (Justification::centredLeft);
    CBsourceDirsPreset->setTextWhenNothingSelected (String());
    CBsourceDirsPreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBsourceDirsPreset->addItem (TRANS("Default"), 1);
    CBsourceDirsPreset->addListener (this);

    CBsourceDirsPreset->setBounds (88, 64, 112, 20);

    SL_num_sources.reset (new Slider ("new slider"));
    addAndMakeVisible (SL_num_sources.get());
    SL_num_sources->setRange (1, 64, 1);
    SL_num_sources->setSliderStyle (Slider::LinearHorizontal);
    SL_num_sources->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    SL_num_sources->addListener (this);

    SL_num_sources->setBounds (80, 92, 120, 24);

    label_N_dirs.reset (new Label ("new label",
                                   String()));
    addAndMakeVisible (label_N_dirs.get());
    label_N_dirs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_N_dirs->setJustificationType (Justification::centredLeft);
    label_N_dirs->setEditable (false, false, false);
    label_N_dirs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_N_dirs->setColour (TextEditor::textColourId, Colours::black);
    label_N_dirs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_N_dirs->setBounds (797, 297, 51, 20);

    label_HRIR_fs.reset (new Label ("new label",
                                    String()));
    addAndMakeVisible (label_HRIR_fs.get());
    label_HRIR_fs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_HRIR_fs->setJustificationType (Justification::centredLeft);
    label_HRIR_fs->setEditable (false, false, false);
    label_HRIR_fs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_HRIR_fs->setColour (TextEditor::textColourId, Colours::black);
    label_HRIR_fs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_HRIR_fs->setBounds (797, 321, 51, 20);

    TBuseDefaultHRIRs.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBuseDefaultHRIRs.get());
    TBuseDefaultHRIRs->setButtonText (String());
    TBuseDefaultHRIRs->addListener (this);

    TBuseDefaultHRIRs->setBounds (876, 61, 32, 24);

    label_DAW_fs.reset (new Label ("new label",
                                   String()));
    addAndMakeVisible (label_DAW_fs.get());
    label_DAW_fs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_DAW_fs->setJustificationType (Justification::centredLeft);
    label_DAW_fs->setEditable (false, false, false);
    label_DAW_fs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_DAW_fs->setColour (TextEditor::textColourId, Colours::black);
    label_DAW_fs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_DAW_fs->setBounds (851, 321, 51, 20);

    TB_showInputs.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_showInputs.get());
    TB_showInputs->setButtonText (String());
    TB_showInputs->addListener (this);

    TB_showInputs->setBounds (552, 317, 24, 24);

    TB_showOutputs.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_showOutputs.get());
    TB_showOutputs->setButtonText (String());
    TB_showOutputs->addListener (this);

    TB_showOutputs->setBounds (674, 317, 24, 24);

    label_N_Tri.reset (new Label ("new label",
                                  String()));
    addAndMakeVisible (label_N_Tri.get());
    label_N_Tri->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_N_Tri->setJustificationType (Justification::centredLeft);
    label_N_Tri->setEditable (false, false, false);
    label_N_Tri->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_N_Tri->setColour (TextEditor::textColourId, Colours::black);
    label_N_Tri->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_N_Tri->setBounds (851, 297, 51, 20);

    CBinterpMode.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBinterpMode.get());
    CBinterpMode->setEditableText (false);
    CBinterpMode->setJustificationType (Justification::centredLeft);
    CBinterpMode->setTextWhenNothingSelected (String());
    CBinterpMode->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBinterpMode->addListener (this);

    CBinterpMode->setBounds (328, 318, 112, 20);

    tb_loadJSON.reset (new TextButton ("new button"));
    addAndMakeVisible (tb_loadJSON.get());
    tb_loadJSON->setButtonText (TRANS("Import"));
    tb_loadJSON->setConnectedEdges (Button::ConnectedOnRight);
    tb_loadJSON->addListener (this);
    tb_loadJSON->setColour (TextButton::buttonColourId, Colour (0xff14889e));

    tb_loadJSON->setBounds (140, 40, 34, 14);

    tb_saveJSON.reset (new TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON.get());
    tb_saveJSON->setButtonText (TRANS("Export"));
    tb_saveJSON->setConnectedEdges (Button::ConnectedOnLeft);
    tb_saveJSON->addListener (this);
    tb_saveJSON->setColour (TextButton::buttonColourId, Colour (0xff224d97));
    tb_saveJSON->setColour (TextButton::buttonOnColourId, Colour (0xff181f9a));

    tb_saveJSON->setBounds (174, 40, 34, 14);

    s_yaw.reset (new Slider ("new slider"));
    addAndMakeVisible (s_yaw.get());
    s_yaw->setRange (-180, 180, 0.01);
    s_yaw->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s_yaw->setTextBoxStyle (Slider::TextBoxBelow, false, 58, 15);
    s_yaw->setColour (Slider::textBoxTextColourId, Colours::white);
    s_yaw->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_yaw->addListener (this);

    s_yaw->setBounds (717, 196, 60, 68);

    s_pitch.reset (new Slider ("new slider"));
    addAndMakeVisible (s_pitch.get());
    s_pitch->setRange (-180, 180, 0.01);
    s_pitch->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s_pitch->setTextBoxStyle (Slider::TextBoxBelow, false, 58, 15);
    s_pitch->setColour (Slider::textBoxTextColourId, Colours::white);
    s_pitch->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_pitch->addListener (this);

    s_pitch->setBounds (780, 196, 60, 68);

    s_roll.reset (new Slider ("new slider"));
    addAndMakeVisible (s_roll.get());
    s_roll->setRange (-180, 180, 0.01);
    s_roll->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s_roll->setTextBoxStyle (Slider::TextBoxBelow, false, 58, 15);
    s_roll->setColour (Slider::textBoxTextColourId, Colours::white);
    s_roll->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_roll->addListener (this);

    s_roll->setBounds (843, 196, 60, 68);

    t_flipYaw.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipYaw.get());
    t_flipYaw->setButtonText (String());
    t_flipYaw->addListener (this);

    t_flipYaw->setBounds (749, 265, 23, 24);

    t_flipPitch.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipPitch.get());
    t_flipPitch->setButtonText (String());
    t_flipPitch->addListener (this);

    t_flipPitch->setBounds (812, 265, 23, 24);

    t_flipRoll.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipRoll.get());
    t_flipRoll->setButtonText (String());
    t_flipRoll->addListener (this);

    t_flipRoll->setBounds (875, 265, 23, 24);

    te_oscport.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (te_oscport.get());
    te_oscport->setMultiLine (false);
    te_oscport->setReturnKeyStartsNewLine (false);
    te_oscport->setReadOnly (false);
    te_oscport->setScrollbarsShown (true);
    te_oscport->setCaretVisible (false);
    te_oscport->setPopupMenuEnabled (true);
    te_oscport->setColour (TextEditor::textColourId, Colours::white);
    te_oscport->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));
    te_oscport->setColour (TextEditor::outlineColourId, Colour (0x6c838080));
    te_oscport->setText (TRANS("9000"));

    te_oscport->setBounds (853, 147, 44, 22);

    TBrpyFlag.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBrpyFlag.get());
    TBrpyFlag->setButtonText (String());
    TBrpyFlag->addListener (this);

    TBrpyFlag->setBounds (758, 147, 32, 24);

    TBenableRotation.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBenableRotation.get());
    TBenableRotation->setButtonText (String());
    TBenableRotation->addListener (this);

    TBenableRotation->setBounds (832, 123, 32, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (920, 356);


    //[Constructor] You can add your own custom stuff here..

    /* handle to pluginProcessor */
	hVst = ownerFilter;

    /* init OpenGL */
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* interp modes */
    CBinterpMode->addItem(TRANS("Triangular"), INTERP_TRI);

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
#ifdef ENABLE_ZYLIA_LAB_PRESET
    CBsourceDirsPreset->addItem (TRANS("Zylia Lab (22.x)"), PRESET_ZYLIA_LAB);
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

    /* source coordinate viewport */
    addAndMakeVisible (sourceCoordsVP = new Viewport ("new viewport"));
    sourceCoordsView_handle = new inputCoordsView(ownerFilter, MAX_NUM_CHANNELS, binauraliser_getNumSources(hVst->hBin));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(22, 153, 184, 180);
    sourceCoordsView_handle->setNCH(binauraliser_getNumSources(hVst->hBin));

    /* file loader */
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
    fileChooser.setBounds (718, 92, 180, 20);
    StringArray filenames;
    filenames.add(binauraliser_getSofaFilePath(hVst->hBin));
    fileChooser.setRecentlyUsedFilenames(filenames);
    fileChooser.setFilenameIsEditable(true);

    /* grab current parameter settings */
    TBuseDefaultHRIRs->setToggleState(binauraliser_getUseDefaultHRIRsflag(hVst->hBin), dontSendNotification);
    SL_num_sources->setValue(binauraliser_getNumSources(hVst->hBin),dontSendNotification);
    TB_showInputs->setToggleState(true, dontSendNotification);
    TB_showOutputs->setToggleState(true, dontSendNotification);
    CBinterpMode->setSelectedId(binauraliser_getInterpMode(hVst->hBin), dontSendNotification);
    TBenableRotation->setToggleState((bool)binauraliser_getEnableRotation(hVst->hBin), dontSendNotification);
    s_yaw->setValue(binauraliser_getYaw(hVst->hBin), dontSendNotification);
    s_pitch->setValue(binauraliser_getPitch(hVst->hBin), dontSendNotification);
    s_roll->setValue(binauraliser_getRoll(hVst->hBin), dontSendNotification);
    t_flipYaw->setToggleState((bool)binauraliser_getFlipYaw(hVst->hBin), dontSendNotification);
    t_flipPitch->setToggleState((bool)binauraliser_getFlipPitch(hVst->hBin), dontSendNotification);
    t_flipRoll->setToggleState((bool)binauraliser_getFlipRoll(hVst->hBin), dontSendNotification);
    te_oscport->setText(String(hVst->getOscPortID()), dontSendNotification);
    TBrpyFlag->setToggleState((bool)binauraliser_getRPYflag(hVst->hBin), dontSendNotification);


    /* create panning window */
    addAndMakeVisible (panWindow = new pannerView(ownerFilter, 480, 240));
    panWindow->setBounds (220, 58, 480, 240);
    panWindow->setShowInputs(TB_showInputs->getToggleState());
    panWindow->setShowOutputs(TB_showOutputs->getToggleState());
    refreshPanViewWindow = true;

	/* Specify screen refresh rate */
    startTimer(40);//80); /*ms (40ms = 25 frames per second) */

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
    label_N_dirs = nullptr;
    label_HRIR_fs = nullptr;
    TBuseDefaultHRIRs = nullptr;
    label_DAW_fs = nullptr;
    TB_showInputs = nullptr;
    TB_showOutputs = nullptr;
    label_N_Tri = nullptr;
    CBinterpMode = nullptr;
    tb_loadJSON = nullptr;
    tb_saveJSON = nullptr;
    s_yaw = nullptr;
    s_pitch = nullptr;
    s_roll = nullptr;
    t_flipYaw = nullptr;
    t_flipPitch = nullptr;
    t_flipRoll = nullptr;
    te_oscport = nullptr;
    TBrpyFlag = nullptr;
    TBenableRotation = nullptr;


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
                                       920.0f - 0.0f + x,
                                       352.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 712, y = 121, width = 196, height = 170;
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
        int x = -19, y = 0, width = 219, height = 32;
        String text (TRANS("Binauraliser"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.80f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
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
        int x = 448, y = 308, width = 252, height = 38;
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
        int x = 712, y = 290, width = 196, height = 56;
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
        int x = 788, y = 32, width = 113, height = 30;
        String text (TRANS("HRIRs"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 392, y = 32, width = 136, height = 30;
        String text (TRANS("Panning Window"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 720, y = 58, width = 160, height = 30;
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
        int x = 457, y = 314, width = 132, height = 30;
        String text (TRANS("Show Inputs:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.50f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 582, y = 314, width = 122, height = 30;
        String text (TRANS("Show HRIRs:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.50f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 220, y = 308, width = 229, height = 38;
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
        int x = 229, y = 314, width = 132, height = 30;
        String text (TRANS("Interp. Mode:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 719, y = 316, width = 89, height = 30;
        String text (TRANS("HRIR/DAW Fs:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 719, y = 294, width = 132, height = 30;
        String text (TRANS("N Dirs/Tri:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 712, y = 176, width = 196, height = 115;
        Colour fillColour = Colour (0x10f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 735, y = 174, width = 49, height = 30;
        String text (TRANS("\\ypr[0]"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (10.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 775, y = 174, width = 46, height = 30;
        String text (TRANS("Pitch"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 831, y = 174, width = 54, height = 30;
        String text (TRANS("Roll"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 831, y = 262, width = 63, height = 30;
        String text (TRANS("+/-"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 703, y = 262, width = 63, height = 30;
        String text (TRANS("+/-"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 767, y = 262, width = 63, height = 30;
        String text (TRANS("+/-"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 799, y = 142, width = 91, height = 35;
        String text (TRANS("OSC port:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 698, y = 174, width = 65, height = 30;
        String text (TRANS("Yaw"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 808, y = 174, width = 40, height = 30;
        String text (TRANS("\\ypr[1]"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (10.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 864, y = 174, width = 40, height = 30;
        String text (TRANS("\\ypr[2]"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (10.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 711, y = 142, width = 54, height = 35;
        String text (TRANS("R-P-Y:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 719, y = 120, width = 160, height = 30;
        String text (TRANS("Enable Rotation:"));
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
		174, 16, 530, 11,
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
                       TRANS("/") + String(binauraliser_getNumSources(hVst->hBin)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(binauraliser_getNumEars()) + TRANS(")"),
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
        binauraliser_setInputConfigPreset(hVst->hBin, CBsourceDirsPreset->getSelectedId());
        refreshPanViewWindow = true;
        //[/UserComboBoxCode_CBsourceDirsPreset]
    }
    else if (comboBoxThatHasChanged == CBinterpMode.get())
    {
        //[UserComboBoxCode_CBinterpMode] -- add your combo box handling code here..
        binauraliser_setInterpMode(hVst->hBin, CBinterpMode->getSelectedId());
        //[/UserComboBoxCode_CBinterpMode]
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
        binauraliser_setNumSources(hVst->hBin, (int)SL_num_sources->getValue());
        refreshPanViewWindow = true;
        //[/UserSliderCode_SL_num_sources]
    }
    else if (sliderThatWasMoved == s_yaw.get())
    {
        //[UserSliderCode_s_yaw] -- add your slider handling code here..
        binauraliser_setYaw(hVst->hBin, (float)s_yaw->getValue());
        //[/UserSliderCode_s_yaw]
    }
    else if (sliderThatWasMoved == s_pitch.get())
    {
        //[UserSliderCode_s_pitch] -- add your slider handling code here..
        binauraliser_setPitch(hVst->hBin, (float)s_pitch->getValue());
        //[/UserSliderCode_s_pitch]
    }
    else if (sliderThatWasMoved == s_roll.get())
    {
        //[UserSliderCode_s_roll] -- add your slider handling code here..
        binauraliser_setRoll(hVst->hBin, (float)s_roll->getValue());
        //[/UserSliderCode_s_roll]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == TBuseDefaultHRIRs.get())
    {
        //[UserButtonCode_TBuseDefaultHRIRs] -- add your button handler code here..
        binauraliser_setUseDefaultHRIRsflag(hVst->hBin, (int)TBuseDefaultHRIRs->getToggleState());
        refreshPanViewWindow = true;
        //[/UserButtonCode_TBuseDefaultHRIRs]
    }
    else if (buttonThatWasClicked == TB_showInputs.get())
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
    else if (buttonThatWasClicked == t_flipYaw.get())
    {
        //[UserButtonCode_t_flipYaw] -- add your button handler code here..
        binauraliser_setFlipYaw(hVst->hBin, (int)t_flipYaw->getToggleState());
        //[/UserButtonCode_t_flipYaw]
    }
    else if (buttonThatWasClicked == t_flipPitch.get())
    {
        //[UserButtonCode_t_flipPitch] -- add your button handler code here..
        binauraliser_setFlipPitch(hVst->hBin, (int)t_flipPitch->getToggleState());
        //[/UserButtonCode_t_flipPitch]
    }
    else if (buttonThatWasClicked == t_flipRoll.get())
    {
        //[UserButtonCode_t_flipRoll] -- add your button handler code here..

        binauraliser_setFlipRoll(hVst->hBin, (int)t_flipRoll->getToggleState());
        //[/UserButtonCode_t_flipRoll]
    }
    else if (buttonThatWasClicked == TBrpyFlag.get())
    {
        //[UserButtonCode_TBrpyFlag] -- add your button handler code here..
        binauraliser_setRPYflag(hVst->hBin, (int)TBrpyFlag->getToggleState());
        //[/UserButtonCode_TBrpyFlag]
    }
    else if (buttonThatWasClicked == TBenableRotation.get())
    {
        //[UserButtonCode_TBenableRotation] -- add your button handler code here..
        binauraliser_setEnableRotation(hVst->hBin, (int)TBenableRotation->getToggleState());
        //[/UserButtonCode_TBenableRotation]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* labels for HRIR details */
    label_N_dirs->setText(String(binauraliser_getNDirs(hVst->hBin)), dontSendNotification);
    label_HRIR_fs->setText(String(binauraliser_getHRIRsamplerate(hVst->hBin)), dontSendNotification);
    label_DAW_fs->setText(String(binauraliser_getDAWsamplerate(hVst->hBin)), dontSendNotification);
    label_N_Tri->setText(String(binauraliser_getNTriangles(hVst->hBin)), dontSendNotification);

    /* parameters whos values can change internally should be periodically refreshed */
    TBuseDefaultHRIRs->setToggleState(binauraliser_getUseDefaultHRIRsflag(hVst->hBin), dontSendNotification);
    sourceCoordsView_handle->setNCH(binauraliser_getNumSources(hVst->hBin));
    SL_num_sources->setValue(binauraliser_getNumSources(hVst->hBin),dontSendNotification);
    s_yaw->setValue(binauraliser_getYaw(hVst->hBin), dontSendNotification);
    s_pitch->setValue(binauraliser_getPitch(hVst->hBin), dontSendNotification);
    s_roll->setValue(binauraliser_getRoll(hVst->hBin), dontSendNotification);

	/* Some parameters shouldn't be enabled if playback is ongoing */
	if (hVst->getIsPlaying()) {
		fileChooser.setEnabled(false);
		TBuseDefaultHRIRs->setEnabled(false);
	}
	else {
		fileChooser.setEnabled(true);
		TBuseDefaultHRIRs->setEnabled(true);
		binauraliser_checkReInit(hVst->hBin);
	}

    /* refresh pan view */
    if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) || sourceCoordsView_handle->getHasASliderChanged()){
		panWindow->refreshPanView();
		sourceCoordsView_handle->setHasASliderChange(false);
		refreshPanViewWindow = false;
    }

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < binauraliser_getNumSources(hVst->hBin))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumOutputs() < binauraliser_getNumEars())){
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
                 fixedSize="1" initialWidth="920" initialHeight="356">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 920 326" fill=" radial: 460 184, 920 352, 0=ff5b6d76, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="712 121 196 170" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 58 196 64" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="0 0 920 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <TEXT pos="-19 0 219 32" fill="solid: ffffffff" hasStroke="0" text="Binauraliser"
          fontname="Default font" fontsize="18.80000000000000071054" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
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
    <RECT pos="448 308 252 38" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="712 58 196 64" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="712 290 196 56" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="23 88 113 30" fill="solid: ffffffff" hasStroke="0" text="N Chan:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="84 32 113 30" fill="solid: ffffffff" hasStroke="0" text="Inputs"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="788 32 113 30" fill="solid: ffffffff" hasStroke="0" text="HRIRs"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="392 32 136 30" fill="solid: ffffffff" hasStroke="0" text="Panning Window"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="720 58 160 30" fill="solid: ffffffff" hasStroke="0" text="Use Default HRIR set:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="457 314 132 30" fill="solid: ffffffff" hasStroke="0" text="Show Inputs:"
          fontname="Default font" fontsize="14.50000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="582 314 122 30" fill="solid: ffffffff" hasStroke="0" text="Show HRIRs:"
          fontname="Default font" fontsize="14.50000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="220 308 229 38" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="229 314 132 30" fill="solid: ffffffff" hasStroke="0" text="Interp. Mode:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="719 316 89 30" fill="solid: ffffffff" hasStroke="0" text="HRIR/DAW Fs:"
          fontname="Default font" fontsize="11.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="719 294 132 30" fill="solid: ffffffff" hasStroke="0" text="N Dirs/Tri:"
          fontname="Default font" fontsize="11.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="712 176 196 115" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="735 174 49 30" fill="solid: ffffffff" hasStroke="0" text="\ypr[0]"
          fontname="Default font" fontsize="10.00000000000000000000" kerning="0.00000000000000000000"
          bold="0" italic="0" justification="36"/>
    <TEXT pos="775 174 46 30" fill="solid: ffffffff" hasStroke="0" text="Pitch"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="831 174 54 30" fill="solid: ffffffff" hasStroke="0" text="Roll"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="831 262 63 30" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="13.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="703 262 63 30" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="13.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="767 262 63 30" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="13.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="799 142 91 35" fill="solid: ffffffff" hasStroke="0" text="OSC port:"
          fontname="Default font" fontsize="11.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="698 174 65 30" fill="solid: ffffffff" hasStroke="0" text="Yaw"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="808 174 40 30" fill="solid: ffffffff" hasStroke="0" text="\ypr[1]"
          fontname="Default font" fontsize="10.00000000000000000000" kerning="0.00000000000000000000"
          bold="0" italic="0" justification="36"/>
    <TEXT pos="864 174 40 30" fill="solid: ffffffff" hasStroke="0" text="\ypr[2]"
          fontname="Default font" fontsize="10.00000000000000000000" kerning="0.00000000000000000000"
          bold="0" italic="0" justification="36"/>
    <TEXT pos="711 142 54 35" fill="solid: ffffffff" hasStroke="0" text="R-P-Y:"
          fontname="Default font" fontsize="11.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="719 120 160 30" fill="solid: ffffffff" hasStroke="0" text="Enable Rotation:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <COMBOBOX name="new combo box" id="5a2f99f88aa51390" memberName="CBsourceDirsPreset"
            virtualName="" explicitFocusOrder="0" pos="88 64 112 20" editable="0"
            layout="33" items="Default" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="2c2a2b3d0614cc94" memberName="SL_num_sources"
          virtualName="" explicitFocusOrder="0" pos="80 92 120 24" min="1.00000000000000000000"
          max="64.00000000000000000000" int="1.00000000000000000000" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <LABEL name="new label" id="167c5975ece5bfaa" memberName="label_N_dirs"
         virtualName="" explicitFocusOrder="0" pos="797 297 51 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f8b5274e0c8768f4" memberName="label_HRIR_fs"
         virtualName="" explicitFocusOrder="0" pos="797 321 51 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="f7f951a1b21e1a11" memberName="TBuseDefaultHRIRs"
                virtualName="" explicitFocusOrder="0" pos="876 61 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="c59fb2aab2496c4e" memberName="label_DAW_fs"
         virtualName="" explicitFocusOrder="0" pos="851 321 51 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="74817bb8a57611dc" memberName="TB_showInputs"
                virtualName="" explicitFocusOrder="0" pos="552 317 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="1a1dfbb1d4296140" memberName="TB_showOutputs"
                virtualName="" explicitFocusOrder="0" pos="674 317 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="2c30657926641642" memberName="label_N_Tri"
         virtualName="" explicitFocusOrder="0" pos="851 297 51 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="aeb0b2f644784061" memberName="CBinterpMode"
            virtualName="" explicitFocusOrder="0" pos="328 318 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button" id="527e24c6748d02d4" memberName="tb_loadJSON"
              virtualName="" explicitFocusOrder="0" pos="140 40 34 14" bgColOff="ff14889e"
              buttonText="Import" connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="48c5d3526dcfe64f" memberName="tb_saveJSON"
              virtualName="" explicitFocusOrder="0" pos="174 40 34 14" bgColOff="ff224d97"
              bgColOn="ff181f9a" buttonText="Export" connectedEdges="1" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="new slider" id="ace036a85eec9703" memberName="s_yaw" virtualName=""
          explicitFocusOrder="0" pos="717 196 60 68" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="-180.00000000000000000000" max="180.00000000000000000000"
          int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="58"
          textBoxHeight="15" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="new slider" id="9af7dd86cd139d85" memberName="s_pitch"
          virtualName="" explicitFocusOrder="0" pos="780 196 60 68" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="-180.00000000000000000000" max="180.00000000000000000000"
          int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="58"
          textBoxHeight="15" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="new slider" id="b5d39bb257b3289a" memberName="s_roll" virtualName=""
          explicitFocusOrder="0" pos="843 196 60 68" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="-180.00000000000000000000" max="180.00000000000000000000"
          int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="58"
          textBoxHeight="15" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="ac47b63592b1d4cf" memberName="t_flipYaw"
                virtualName="" explicitFocusOrder="0" pos="749 265 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="c58241ee52766d62" memberName="t_flipPitch"
                virtualName="" explicitFocusOrder="0" pos="812 265 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="717e9536768dfd8c" memberName="t_flipRoll"
                virtualName="" explicitFocusOrder="0" pos="875 265 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTEDITOR name="new text editor" id="1799da9e8cf495d6" memberName="te_oscport"
              virtualName="" explicitFocusOrder="0" pos="853 147 44 22" textcol="ffffffff"
              bkgcol="ffffff" outlinecol="6c838080" initialText="9000" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="0" popupmenu="1"/>
  <TOGGLEBUTTON name="new toggle button" id="b4fec6d3e1a2bae2" memberName="TBrpyFlag"
                virtualName="" explicitFocusOrder="0" pos="758 147 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="a45ef80fa16bd3f0" memberName="TBenableRotation"
                virtualName="" explicitFocusOrder="0" pos="832 123 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
