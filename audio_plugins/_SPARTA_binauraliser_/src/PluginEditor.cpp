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

    label_N_dirs->setBounds (800, 136, 96, 24);

    label_HRIR_len.reset (new Label ("new label",
                                     String()));
    addAndMakeVisible (label_HRIR_len.get());
    label_HRIR_len->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_HRIR_len->setJustificationType (Justification::centredLeft);
    label_HRIR_len->setEditable (false, false, false);
    label_HRIR_len->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_HRIR_len->setColour (TextEditor::textColourId, Colours::black);
    label_HRIR_len->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_HRIR_len->setBounds (800, 200, 96, 24);

    label_HRIR_fs.reset (new Label ("new label",
                                    String()));
    addAndMakeVisible (label_HRIR_fs.get());
    label_HRIR_fs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_HRIR_fs->setJustificationType (Justification::centredLeft);
    label_HRIR_fs->setEditable (false, false, false);
    label_HRIR_fs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_HRIR_fs->setColour (TextEditor::textColourId, Colours::black);
    label_HRIR_fs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_HRIR_fs->setBounds (800, 232, 96, 24);

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

    label_DAW_fs->setBounds (800, 264, 96, 24);

    TB_showInputs.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_showInputs.get());
    TB_showInputs->setButtonText (String());
    TB_showInputs->addListener (this);

    TB_showInputs->setBounds (545, 318, 32, 24);

    TB_showOutputs.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_showOutputs.get());
    TB_showOutputs->setButtonText (String());
    TB_showOutputs->addListener (this);

    TB_showOutputs->setBounds (673, 318, 32, 24);

    label_N_Tri.reset (new Label ("new label",
                                  String()));
    addAndMakeVisible (label_N_Tri.get());
    label_N_Tri->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_N_Tri->setJustificationType (Justification::centredLeft);
    label_N_Tri->setEditable (false, false, false);
    label_N_Tri->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_N_Tri->setColour (TextEditor::textColourId, Colours::black);
    label_N_Tri->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_N_Tri->setBounds (800, 168, 96, 24);

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
    tb_loadJSON->setButtonText (TRANS("LoadJSON"));
    tb_loadJSON->addListener (this);
    tb_loadJSON->setColour (TextButton::buttonColourId, Colour (0xff695ca4));

    tb_loadJSON->setBounds (200, 8, 112, 24);

    tb_saveJSON.reset (new TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON.get());
    tb_saveJSON->setButtonText (TRANS("saveJSON"));
    tb_saveJSON->addListener (this);
    tb_saveJSON->setColour (TextButton::buttonColourId, Colour (0xff695ca4));

    tb_saveJSON->setBounds (328, 8, 112, 24);


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
    CBinterpMode->setEnabled(false);

    /* create panning window */
    addAndMakeVisible (panWindow = new pannerView(ownerFilter, 480, 240));
    panWindow->setBounds (220, 58, 480, 240);
    panWindow->setShowInputs(TB_showInputs->getToggleState());
    panWindow->setShowOutputs(TB_showOutputs->getToggleState());
    refreshPanViewWindow = true;

	/* Specify screen refresh rate */
    startTimer(80);//80); /*ms (40ms = 25 frames per second) */

    showingFrameSizeWarning = false;

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    CBsourceDirsPreset = nullptr;
    SL_num_sources = nullptr;
    label_N_dirs = nullptr;
    label_HRIR_len = nullptr;
    label_HRIR_fs = nullptr;
    TBuseDefaultHRIRs = nullptr;
    label_DAW_fs = nullptr;
    TB_showInputs = nullptr;
    TB_showOutputs = nullptr;
    label_N_Tri = nullptr;
    CBinterpMode = nullptr;
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
        int x = 0, y = 30, width = 920, height = 326;
        Colour fillColour1 = Colour (0xff55636d), fillColour2 = Colour (0xff073642);
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
        int x = -19, y = 0, width = 195, height = 32;
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
        int x = 723, y = 131, width = 132, height = 30;
        String text (TRANS("N dirs:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 723, y = 195, width = 132, height = 30;
        String text (TRANS("HRIR len:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 723, y = 227, width = 132, height = 30;
        String text (TRANS("HRIR fs:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 723, y = 259, width = 132, height = 30;
        String text (TRANS("DAW fs:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 455, y = 314, width = 132, height = 30;
        String text (TRANS("Show Inputs:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 584, y = 314, width = 122, height = 30;
        String text (TRANS("Show HRIRs:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
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
        int x = 231, y = 314, width = 132, height = 30;
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
        int x = 723, y = 163, width = 132, height = 30;
        String text (TRANS("N Tri:"));
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

    /* display warning message */
    if(showingFrameSizeWarning){
        g.setColour(Colours::red);
        g.setFont(Font(11.00f, Font::plain));
        g.drawText(TRANS("Set frame size to multiple of ") + String(FRAME_SIZE),
                   getBounds().getWidth()-170, 16, 530, 11,
                   Justification::centredLeft, true);
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

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* labels for HRIR details */
    label_N_dirs->setText(String(binauraliser_getNDirs(hVst->hBin)), dontSendNotification);
    label_HRIR_len->setText(String(binauraliser_getHRIRlength(hVst->hBin)), dontSendNotification);
    label_HRIR_fs->setText(String(binauraliser_getHRIRsamplerate(hVst->hBin)), dontSendNotification);
    label_DAW_fs->setText(String(binauraliser_getDAWsamplerate(hVst->hBin)), dontSendNotification);
    label_N_Tri->setText(String(binauraliser_getNTriangles(hVst->hBin)), dontSendNotification);

    /* parameters whos values can change internally should be periodically refreshed */
    TBuseDefaultHRIRs->setToggleState(binauraliser_getUseDefaultHRIRsflag(hVst->hBin), dontSendNotification);
    sourceCoordsView_handle->setNCH(binauraliser_getNumSources(hVst->hBin));
    SL_num_sources->setValue(binauraliser_getNumSources(hVst->hBin),dontSendNotification);

    /* refresh pan view */
    if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) || sourceCoordsView_handle->getHasASliderChanged()){
        panWindow->refreshPanView();
        refreshPanViewWindow = false;
        sourceCoordsView_handle->setHasASliderChange(false);
    }

    /* show warning if currently selected framesize is not supported */
    if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
        showingFrameSizeWarning = true;
        repaint();
    }
    else if(showingFrameSizeWarning){
        showingFrameSizeWarning = false;
        repaint();
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
    <RECT pos="0 30 920 326" fill=" radial: 460 184, 920 352, 0=ff55636d, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="12 58 196 64" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="0 0 920 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <TEXT pos="-19 0 195 32" fill="solid: ffffffff" hasStroke="0" text="Binauraliser"
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
    <RECT pos="712 121 196 225" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
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
    <TEXT pos="723 131 132 30" fill="solid: ffffffff" hasStroke="0" text="N dirs:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="723 195 132 30" fill="solid: ffffffff" hasStroke="0" text="HRIR len:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="723 227 132 30" fill="solid: ffffffff" hasStroke="0" text="HRIR fs:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="723 259 132 30" fill="solid: ffffffff" hasStroke="0" text="DAW fs:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="455 314 132 30" fill="solid: ffffffff" hasStroke="0" text="Show Inputs:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="584 314 122 30" fill="solid: ffffffff" hasStroke="0" text="Show HRIRs:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="220 308 229 38" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="231 314 132 30" fill="solid: ffffffff" hasStroke="0" text="Interp. Mode:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="723 163 132 30" fill="solid: ffffffff" hasStroke="0" text="N Tri:"
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
         virtualName="" explicitFocusOrder="0" pos="800 136 96 24" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e14d1c2e00d7849b" memberName="label_HRIR_len"
         virtualName="" explicitFocusOrder="0" pos="800 200 96 24" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f8b5274e0c8768f4" memberName="label_HRIR_fs"
         virtualName="" explicitFocusOrder="0" pos="800 232 96 24" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="f7f951a1b21e1a11" memberName="TBuseDefaultHRIRs"
                virtualName="" explicitFocusOrder="0" pos="876 61 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="c59fb2aab2496c4e" memberName="label_DAW_fs"
         virtualName="" explicitFocusOrder="0" pos="800 264 96 24" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="74817bb8a57611dc" memberName="TB_showInputs"
                virtualName="" explicitFocusOrder="0" pos="545 318 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="1a1dfbb1d4296140" memberName="TB_showOutputs"
                virtualName="" explicitFocusOrder="0" pos="673 318 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="2c30657926641642" memberName="label_N_Tri"
         virtualName="" explicitFocusOrder="0" pos="800 168 96 24" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="aeb0b2f644784061" memberName="CBinterpMode"
            virtualName="" explicitFocusOrder="0" pos="328 318 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="new button" id="527e24c6748d02d4" memberName="tb_loadJSON"
              virtualName="" explicitFocusOrder="0" pos="200 8 112 24" bgColOff="ff695ca4"
              buttonText="LoadJSON" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="48c5d3526dcfe64f" memberName="tb_saveJSON"
              virtualName="" explicitFocusOrder="0" pos="328 8 112 24" bgColOff="ff695ca4"
              buttonText="saveJSON" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
