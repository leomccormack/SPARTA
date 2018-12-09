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

    TBuseDefaultHRIRs.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBuseDefaultHRIRs.get());
    TBuseDefaultHRIRs->setButtonText (String());
    TBuseDefaultHRIRs->addListener (this);

    TBuseDefaultHRIRs->setBounds (614, 60, 21, 24);

    CBchFormat.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (Justification::centredLeft);
    CBchFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBchFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBchFormat->addItem (TRANS("ACN"), 1);
    CBchFormat->addListener (this);

    CBchFormat->setBounds (332, 64, 98, 20);

    CBnormScheme.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (Justification::centredLeft);
    CBnormScheme->setTextWhenNothingSelected (TRANS("N3D"));
    CBnormScheme->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnormScheme->addItem (TRANS("N3D"), 1);
    CBnormScheme->addItem (TRANS("SN3D"), 2);
    CBnormScheme->addListener (this);

    CBnormScheme->setBounds (332, 91, 98, 20);

    TBmaxRE.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBmaxRE.get());
    TBmaxRE->setButtonText (String());
    TBmaxRE->addListener (this);

    TBmaxRE->setBounds (191, 60, 22, 24);

    label_N_dirs.reset (new Label ("new label",
                                   String()));
    addAndMakeVisible (label_N_dirs.get());
    label_N_dirs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_N_dirs->setJustificationType (Justification::centredLeft);
    label_N_dirs->setEditable (false, false, false);
    label_N_dirs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_N_dirs->setColour (TextEditor::textColourId, Colours::black);
    label_N_dirs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_N_dirs->setBounds (531, 277, 51, 20);

    label_HRIR_fs.reset (new Label ("new label",
                                    String()));
    addAndMakeVisible (label_HRIR_fs.get());
    label_HRIR_fs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_HRIR_fs->setJustificationType (Justification::centredLeft);
    label_HRIR_fs->setEditable (false, false, false);
    label_HRIR_fs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_HRIR_fs->setColour (TextEditor::textColourId, Colours::black);
    label_HRIR_fs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_HRIR_fs->setBounds (531, 301, 51, 20);

    label_DAW_fs.reset (new Label ("new label",
                                   String()));
    addAndMakeVisible (label_DAW_fs.get());
    label_DAW_fs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_DAW_fs->setJustificationType (Justification::centredLeft);
    label_DAW_fs->setEditable (false, false, false);
    label_DAW_fs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_DAW_fs->setColour (TextEditor::textColourId, Colours::black);
    label_DAW_fs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_DAW_fs->setBounds (585, 301, 51, 20);

    label_N_Tri.reset (new Label ("new label",
                                  String()));
    addAndMakeVisible (label_N_Tri.get());
    label_N_Tri->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_N_Tri->setJustificationType (Justification::centredLeft);
    label_N_Tri->setEditable (false, false, false);
    label_N_Tri->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_N_Tri->setColour (TextEditor::textColourId, Colours::black);
    label_N_Tri->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_N_Tri->setBounds (585, 277, 51, 20);

    s_yaw.reset (new Slider ("new slider"));
    addAndMakeVisible (s_yaw.get());
    s_yaw->setRange (-180, 180, 0.01);
    s_yaw->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s_yaw->setTextBoxStyle (Slider::TextBoxBelow, false, 58, 15);
    s_yaw->setColour (Slider::textBoxTextColourId, Colours::white);
    s_yaw->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_yaw->addListener (this);

    s_yaw->setBounds (451, 181, 60, 68);

    s_pitch.reset (new Slider ("new slider"));
    addAndMakeVisible (s_pitch.get());
    s_pitch->setRange (-180, 180, 0.01);
    s_pitch->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s_pitch->setTextBoxStyle (Slider::TextBoxBelow, false, 58, 15);
    s_pitch->setColour (Slider::textBoxTextColourId, Colours::white);
    s_pitch->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_pitch->addListener (this);

    s_pitch->setBounds (514, 181, 60, 68);

    s_roll.reset (new Slider ("new slider"));
    addAndMakeVisible (s_roll.get());
    s_roll->setRange (-180, 180, 0.01);
    s_roll->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s_roll->setTextBoxStyle (Slider::TextBoxBelow, false, 58, 15);
    s_roll->setColour (Slider::textBoxTextColourId, Colours::white);
    s_roll->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_roll->addListener (this);

    s_roll->setBounds (577, 181, 60, 68);

    t_flipYaw.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipYaw.get());
    t_flipYaw->setButtonText (String());
    t_flipYaw->addListener (this);

    t_flipYaw->setBounds (483, 249, 23, 24);

    t_flipPitch.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipPitch.get());
    t_flipPitch->setButtonText (String());
    t_flipPitch->addListener (this);

    t_flipPitch->setBounds (546, 249, 23, 24);

    t_flipRoll.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipRoll.get());
    t_flipRoll->setButtonText (String());
    t_flipRoll->addListener (this);

    t_flipRoll->setBounds (609, 249, 23, 24);

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

    te_oscport->setBounds (587, 138, 44, 22);

    TBrpyFlag.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBrpyFlag.get());
    TBrpyFlag->setButtonText (String());
    TBrpyFlag->addListener (this);

    TBrpyFlag->setBounds (492, 138, 32, 24);

    TBenableRotation.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBenableRotation.get());
    TBenableRotation->setButtonText (String());
    TBenableRotation->addListener (this);

    TBenableRotation->setBounds (566, 114, 32, 24);

    s_cov_avg.reset (new Slider ("new slider"));
    addAndMakeVisible (s_cov_avg.get());
    s_cov_avg->setRange (0, 1, 0.01);
    s_cov_avg->setSliderStyle (Slider::LinearHorizontal);
    s_cov_avg->setTextBoxStyle (Slider::TextBoxRight, false, 50, 20);
    s_cov_avg->setColour (Slider::textBoxTextColourId, Colours::white);
    s_cov_avg->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_cov_avg->addListener (this);

    s_cov_avg->setBounds (84, 84, 128, 32);

    s_diff2dir.reset (new Slider ("new slider"));
    addAndMakeVisible (s_diff2dir.get());
    s_diff2dir->setRange (0, 2, 0.01);
    s_diff2dir->setSliderStyle (Slider::LinearVertical);
    s_diff2dir->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    s_diff2dir->setColour (Slider::textBoxTextColourId, Colours::white);
    s_diff2dir->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_diff2dir->addListener (this);

    s_diff2dir->setBounds (388, 136, 40, 74);

    s_decBal.reset (new Slider ("new slider"));
    addAndMakeVisible (s_decBal.get());
    s_decBal->setRange (0, 1, 0.01);
    s_decBal->setSliderStyle (Slider::LinearVertical);
    s_decBal->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    s_decBal->setColour (Slider::textBoxTextColourId, Colours::white);
    s_decBal->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_decBal->addListener (this);

    s_decBal->setBounds (388, 241, 40, 74);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (656, 336);


    //[Constructor] You can add your own custom stuff here..

    /* handle to pluginProcessor */
	hVst = ownerFilter;

    /* init OpenGL */
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* file loader */
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
    fileChooser.setBounds (458, 86, 168, 20);
    
    /* create 2d Sliders */
    int nPoints;
    float* pX_vector;
    float* pY_values;
    
    /* create 2d Slider for the balance parameter */
    addAndMakeVisible (balance2dSlider = new log2dSlider(360, 62, 100, 20e3, 0, 2, 2));
    balance2dSlider->setAlwaysOnTop(true);
    balance2dSlider->setTopLeftPosition(25, 142);
    ambi_cropac_getBalanceHandle(hVst->hAmbi, &pX_vector, &pY_values, &nPoints);
    balance2dSlider->setDataHandles(pX_vector, pY_values, nPoints);
    
    /* create 2d Slider for the decoding balance parameter */
    addAndMakeVisible (decBalance2dSlider = new log2dSlider(360, 62, 100, 20e3, 0, 1, 2));
    decBalance2dSlider->setAlwaysOnTop(true);
    decBalance2dSlider->setTopLeftPosition(25, 246);
    ambi_cropac_getDecBalanceHandle(hVst->hAmbi, &pX_vector, &pY_values, &nPoints);
    decBalance2dSlider->setDataHandles(pX_vector, pY_values, nPoints);

    /* grab current parameter settings */
    TBuseDefaultHRIRs->setToggleState(ambi_cropac_getUseDefaultHRIRsflag(hVst->hAmbi), dontSendNotification);
    CBchFormat->setSelectedId(ambi_cropac_getChOrder(hVst->hAmbi), dontSendNotification);
    CBnormScheme->setSelectedId(ambi_cropac_getNormType(hVst->hAmbi), dontSendNotification);
    TBmaxRE->setToggleState(ambi_cropac_getDecEnableMaxrE(hVst->hAmbi), dontSendNotification);
    TBenableRotation->setToggleState(ambi_cropac_getEnableRotation(hVst->hAmbi), dontSendNotification);
    s_cov_avg->setValue(ambi_cropac_getCovAvg(hVst->hAmbi), dontSendNotification);
    s_diff2dir->setValue(ambi_cropac_getBalanceAllBands(hVst->hAmbi), dontSendNotification);
    s_decBal->setValue(ambi_cropac_getDecBalanceAllBands(hVst->hAmbi), dontSendNotification);
    s_yaw->setValue(ambi_cropac_getYaw(hVst->hAmbi), dontSendNotification);
    s_pitch->setValue(ambi_cropac_getPitch(hVst->hAmbi), dontSendNotification);
    s_roll->setValue(ambi_cropac_getRoll(hVst->hAmbi), dontSendNotification);
    t_flipYaw->setToggleState((bool)ambi_cropac_getFlipYaw(hVst->hAmbi), dontSendNotification);
    t_flipPitch->setToggleState((bool)ambi_cropac_getFlipPitch(hVst->hAmbi), dontSendNotification);
    t_flipRoll->setToggleState((bool)ambi_cropac_getFlipRoll(hVst->hAmbi), dontSendNotification);
    te_oscport->setText(String(hVst->getOscPortID()), dontSendNotification);
    TBrpyFlag->setToggleState((bool)ambi_cropac_getRPYflag(hVst->hAmbi), dontSendNotification);

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

    TBuseDefaultHRIRs = nullptr;
    CBchFormat = nullptr;
    CBnormScheme = nullptr;
    TBmaxRE = nullptr;
    label_N_dirs = nullptr;
    label_HRIR_fs = nullptr;
    label_DAW_fs = nullptr;
    label_N_Tri = nullptr;
    s_yaw = nullptr;
    s_pitch = nullptr;
    s_roll = nullptr;
    t_flipYaw = nullptr;
    t_flipPitch = nullptr;
    t_flipRoll = nullptr;
    te_oscport = nullptr;
    TBrpyFlag = nullptr;
    TBenableRotation = nullptr;
    s_cov_avg = nullptr;
    s_diff2dir = nullptr;
    s_decBal = nullptr;


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
        int x = 0, y = 30, width = 656, height = 306;
        Colour fillColour1 = Colour (0xff5b6d76), fillColour2 = Colour (0xff073642);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       336.0f - 0.0f + x,
                                       176.0f - 30.0f + y,
                                       fillColour2,
                                       656.0f - 0.0f + x,
                                       336.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 12, y = 58, width = 207, height = 59;
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
        int x = 218, y = 58, width = 218, height = 59;
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
        int x = 446, y = 58, width = 196, height = 54;
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
        int x = -24, y = 0, width = 216, height = 32;
        String text (TRANS("AmbiCroPaC"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.80f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
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
        int x = 520, y = 32, width = 113, height = 30;
        String text (TRANS("Output"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 459, y = 56, width = 165, height = 30;
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
        int x = 19, y = 84, width = 125, height = 30;
        String text (TRANS("Cov Avg:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 227, y = 56, width = 132, height = 30;
        String text (TRANS("Channel Order:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 227, y = 84, width = 132, height = 30;
        String text (TRANS("Norm Scheme:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 56, width = 189, height = 30;
        String text (TRANS("Enable max_rE Weighting:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 446, y = 111, width = 196, height = 163;
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
        int x = 446, y = 273, width = 196, height = 52;
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
        int x = 455, y = 296, width = 89, height = 30;
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
        int x = 455, y = 272, width = 132, height = 30;
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
        int x = 446, y = 166, width = 196, height = 108;
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
        int x = 471, y = 162, width = 49, height = 30;
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
        int x = 511, y = 162, width = 46, height = 30;
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
        int x = 567, y = 162, width = 54, height = 30;
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
        int x = 567, y = 246, width = 63, height = 30;
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
        int x = 439, y = 246, width = 63, height = 30;
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
        int x = 503, y = 246, width = 63, height = 30;
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
        int x = 535, y = 134, width = 91, height = 35;
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
        int x = 434, y = 162, width = 65, height = 30;
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
        int x = 544, y = 162, width = 40, height = 30;
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
        int x = 600, y = 162, width = 40, height = 30;
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
        int x = 447, y = 134, width = 54, height = 35;
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
        int x = 455, y = 112, width = 160, height = 30;
        String text (TRANS("Enable Rotation:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 12, y = 116, width = 424, height = 105;
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
        int x = 21, y = 112, width = 283, height = 30;
        String text (TRANS("Diffuse to Direct Balance Per Band"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 12, y = 220, width = 424, height = 105;
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
        int x = 21, y = 216, width = 323, height = 30;
        String text (TRANS("Ambi to CroPaC Balance Per Band"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 419, y = 184, width = 13, height = 30;
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
        int x = 419, y = 126, width = 13, height = 30;
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
        int x = 419, y = 289, width = 13, height = 30;
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
        int x = 419, y = 229, width = 13, height = 30;
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
        int x = 19, y = 196, width = 37, height = 30;
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
        int x = 174, y = 196, width = 37, height = 30;
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
        int x = 328, y = 196, width = 37, height = 30;
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
        int x = 210, y = 196, width = 93, height = 30;
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
        int x = 19, y = 300, width = 37, height = 30;
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
        int x = 174, y = 300, width = 37, height = 30;
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
        int x = 328, y = 300, width = 37, height = 30;
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
        int x = 210, y = 300, width = 93, height = 30;
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
        int x = 371, y = 196, width = 37, height = 30;
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
        int x = 371, y = 300, width = 37, height = 30;
        String text (TRANS("20k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
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
                       TRANS("/") + String(ambi_cropac_getNSHrequired()) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(ambi_cropac_getNumEars()) + TRANS(")"),
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

void PluginEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == TBuseDefaultHRIRs.get())
    {
        //[UserButtonCode_TBuseDefaultHRIRs] -- add your button handler code here..
        ambi_cropac_setUseDefaultHRIRsflag(hVst->hAmbi, (int)TBuseDefaultHRIRs->getToggleState());
        //[/UserButtonCode_TBuseDefaultHRIRs]
    }
    else if (buttonThatWasClicked == TBmaxRE.get())
    {
        //[UserButtonCode_TBmaxRE] -- add your button handler code here..
        ambi_cropac_setDecEnableMaxrE(hVst->hAmbi, (int)TBmaxRE->getToggleState());
        //[/UserButtonCode_TBmaxRE]
    }
    else if (buttonThatWasClicked == t_flipYaw.get())
    {
        //[UserButtonCode_t_flipYaw] -- add your button handler code here..
        //[/UserButtonCode_t_flipYaw]
    }
    else if (buttonThatWasClicked == t_flipPitch.get())
    {
        //[UserButtonCode_t_flipPitch] -- add your button handler code here..
        //[/UserButtonCode_t_flipPitch]
    }
    else if (buttonThatWasClicked == t_flipRoll.get())
    {
        //[UserButtonCode_t_flipRoll] -- add your button handler code here..
        //[/UserButtonCode_t_flipRoll]
    }
    else if (buttonThatWasClicked == TBrpyFlag.get())
    {
        //[UserButtonCode_TBrpyFlag] -- add your button handler code here..
        //[/UserButtonCode_TBrpyFlag]
    }
    else if (buttonThatWasClicked == TBenableRotation.get())
    {
        //[UserButtonCode_TBenableRotation] -- add your button handler code here..
        //[/UserButtonCode_TBenableRotation]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PluginEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBchFormat.get())
    {
        //[UserComboBoxCode_CBchFormat] -- add your combo box handling code here..
        ambi_cropac_setChOrder(hVst->hAmbi, CBchFormat->getSelectedId());
        //[/UserComboBoxCode_CBchFormat]
    }
    else if (comboBoxThatHasChanged == CBnormScheme.get())
    {
        //[UserComboBoxCode_CBnormScheme] -- add your combo box handling code here..
        ambi_cropac_setNormType(hVst->hAmbi, CBnormScheme->getSelectedId());
        //[/UserComboBoxCode_CBnormScheme]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == s_yaw.get())
    {
        //[UserSliderCode_s_yaw] -- add your slider handling code here..
        //[/UserSliderCode_s_yaw]
    }
    else if (sliderThatWasMoved == s_pitch.get())
    {
        //[UserSliderCode_s_pitch] -- add your slider handling code here..
        //[/UserSliderCode_s_pitch]
    }
    else if (sliderThatWasMoved == s_roll.get())
    {
        //[UserSliderCode_s_roll] -- add your slider handling code here..
        //[/UserSliderCode_s_roll]
    }
    else if (sliderThatWasMoved == s_cov_avg.get())
    {
        //[UserSliderCode_s_cov_avg] -- add your slider handling code here..
        //[/UserSliderCode_s_cov_avg]
    }
    else if (sliderThatWasMoved == s_diff2dir.get())
    {
        //[UserSliderCode_s_diff2dir] -- add your slider handling code here..
        //[/UserSliderCode_s_diff2dir]
    }
    else if (sliderThatWasMoved == s_decBal.get())
    {
        //[UserSliderCode_s_decBal] -- add your slider handling code here..
        //[/UserSliderCode_s_decBal]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    TBuseDefaultHRIRs->setToggleState(ambi_cropac_getUseDefaultHRIRsflag(hVst->hAmbi), dontSendNotification);
    label_N_dirs->setText(String(ambi_cropac_getNDirs(hVst->hAmbi)), dontSendNotification);
    label_N_Tri->setText(String(ambi_cropac_getNTriangles(hVst->hAmbi)), dontSendNotification);
    label_HRIR_fs->setText(String(ambi_cropac_getHRIRsamplerate(hVst->hAmbi)), dontSendNotification);
    label_DAW_fs->setText(String(ambi_cropac_getDAWsamplerate(hVst->hAmbi)), dontSendNotification);
    s_yaw->setValue(ambi_cropac_getYaw(hVst->hAmbi), dontSendNotification);
    s_pitch->setValue(ambi_cropac_getPitch(hVst->hAmbi), dontSendNotification);
    s_roll->setValue(ambi_cropac_getRoll(hVst->hAmbi), dontSendNotification);

	/* Some parameters shouldn't be enabled if playback is ongoing */
	if (hVst->getIsPlaying()) {
		fileChooser.setEnabled(false);
		TBuseDefaultHRIRs->setEnabled(false);
		TBmaxRE->setEnabled(false);
	}
	else {
		fileChooser.setEnabled(true);
		TBuseDefaultHRIRs->setEnabled(true);
		TBmaxRE->setEnabled(true);
		ambi_cropac_checkReInit(hVst->hAmbi);
	}

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < ambi_cropac_getNSHrequired())){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumOutputs() < ambi_cropac_getNumEars())){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }

    /* check if OSC port has changed */
    if(hVst->getOscPortID() != te_oscport->getText().getIntValue())
        hVst->setOscPortID(te_oscport->getText().getIntValue());
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
                 fixedSize="1" initialWidth="656" initialHeight="336">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 656 306" fill=" radial: 336 176, 656 336, 0=ff5b6d76, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="12 58 207 59" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="218 58 218 59" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="446 58 196 54" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="0 0 656 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <TEXT pos="-24 0 216 32" fill="solid: ffffffff" hasStroke="0" text="AmbiCroPaC"
          fontname="Default font" fontsize="18.80000000000000071054" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="164 32 149 30" fill="solid: ffffffff" hasStroke="0" text="Decoding Settings"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="520 32 113 30" fill="solid: ffffffff" hasStroke="0" text="Output"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="459 56 165 30" fill="solid: ffffffff" hasStroke="0" text="Use Default HRIR set:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 84 125 30" fill="solid: ffffffff" hasStroke="0" text="Cov Avg:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="227 56 132 30" fill="solid: ffffffff" hasStroke="0" text="Channel Order:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="227 84 132 30" fill="solid: ffffffff" hasStroke="0" text="Norm Scheme:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 56 189 30" fill="solid: ffffffff" hasStroke="0" text="Enable max_rE Weighting:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="446 111 196 163" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="446 273 196 52" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="455 296 89 30" fill="solid: ffffffff" hasStroke="0" text="HRIR/DAW Fs:"
          fontname="Default font" fontsize="11.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="455 272 132 30" fill="solid: ffffffff" hasStroke="0" text="N Dirs/Tri:"
          fontname="Default font" fontsize="11.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="446 166 196 108" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="471 162 49 30" fill="solid: ffffffff" hasStroke="0" text="\ypr[0]"
          fontname="Default font" fontsize="10.00000000000000000000" kerning="0.00000000000000000000"
          bold="0" italic="0" justification="36"/>
    <TEXT pos="511 162 46 30" fill="solid: ffffffff" hasStroke="0" text="Pitch"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="567 162 54 30" fill="solid: ffffffff" hasStroke="0" text="Roll"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="567 246 63 30" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="13.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="439 246 63 30" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="13.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="503 246 63 30" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="13.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="535 134 91 35" fill="solid: ffffffff" hasStroke="0" text="OSC port:"
          fontname="Default font" fontsize="11.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="434 162 65 30" fill="solid: ffffffff" hasStroke="0" text="Yaw"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="544 162 40 30" fill="solid: ffffffff" hasStroke="0" text="\ypr[1]"
          fontname="Default font" fontsize="10.00000000000000000000" kerning="0.00000000000000000000"
          bold="0" italic="0" justification="36"/>
    <TEXT pos="600 162 40 30" fill="solid: ffffffff" hasStroke="0" text="\ypr[2]"
          fontname="Default font" fontsize="10.00000000000000000000" kerning="0.00000000000000000000"
          bold="0" italic="0" justification="36"/>
    <TEXT pos="447 134 54 35" fill="solid: ffffffff" hasStroke="0" text="R-P-Y:"
          fontname="Default font" fontsize="11.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="455 112 160 30" fill="solid: ffffffff" hasStroke="0" text="Enable Rotation:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="12 116 424 105" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="21 112 283 30" fill="solid: ffffffff" hasStroke="0" text="Diffuse to Direct Balance Per Band"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="12 220 424 105" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="21 216 323 30" fill="solid: ffffffff" hasStroke="0" text="Ambi to CroPaC Balance Per Band"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="419 184 13 30" fill="solid: ffffffff" hasStroke="0" text="0"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="419 126 13 30" fill="solid: ffffffff" hasStroke="0" text="2"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="419 289 13 30" fill="solid: ffffffff" hasStroke="0" text="0"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="419 229 13 30" fill="solid: ffffffff" hasStroke="0" text="1"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 196 37 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="174 196 37 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="328 196 37 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="210 196 93 30" fill="solid: ffffffff" hasStroke="0" text="Frequency (Hz)"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 300 37 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="174 300 37 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="328 300 37 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="210 300 93 30" fill="solid: ffffffff" hasStroke="0" text="Frequency (Hz)"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="371 196 37 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="371 300 37 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <TOGGLEBUTTON name="new toggle button" id="f7f951a1b21e1a11" memberName="TBuseDefaultHRIRs"
                virtualName="" explicitFocusOrder="0" pos="614 60 21 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="a36915795f16ceb6" memberName="CBchFormat"
            virtualName="" explicitFocusOrder="0" pos="332 64 98 20" editable="0"
            layout="33" items="ACN" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="e10be54628a6df43" memberName="CBnormScheme"
            virtualName="" explicitFocusOrder="0" pos="332 91 98 20" editable="0"
            layout="33" items="N3D&#10;SN3D" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="new toggle button" id="943aa789e193d13a" memberName="TBmaxRE"
                virtualName="" explicitFocusOrder="0" pos="191 60 22 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="167c5975ece5bfaa" memberName="label_N_dirs"
         virtualName="" explicitFocusOrder="0" pos="531 277 51 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f8b5274e0c8768f4" memberName="label_HRIR_fs"
         virtualName="" explicitFocusOrder="0" pos="531 301 51 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c59fb2aab2496c4e" memberName="label_DAW_fs"
         virtualName="" explicitFocusOrder="0" pos="585 301 51 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2c30657926641642" memberName="label_N_Tri"
         virtualName="" explicitFocusOrder="0" pos="585 277 51 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="ace036a85eec9703" memberName="s_yaw" virtualName=""
          explicitFocusOrder="0" pos="451 181 60 68" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="-180.00000000000000000000" max="180.00000000000000000000"
          int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="58"
          textBoxHeight="15" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="new slider" id="9af7dd86cd139d85" memberName="s_pitch"
          virtualName="" explicitFocusOrder="0" pos="514 181 60 68" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="-180.00000000000000000000" max="180.00000000000000000000"
          int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="58"
          textBoxHeight="15" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="new slider" id="b5d39bb257b3289a" memberName="s_roll" virtualName=""
          explicitFocusOrder="0" pos="577 181 60 68" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="-180.00000000000000000000" max="180.00000000000000000000"
          int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="58"
          textBoxHeight="15" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="ac47b63592b1d4cf" memberName="t_flipYaw"
                virtualName="" explicitFocusOrder="0" pos="483 249 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="c58241ee52766d62" memberName="t_flipPitch"
                virtualName="" explicitFocusOrder="0" pos="546 249 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="717e9536768dfd8c" memberName="t_flipRoll"
                virtualName="" explicitFocusOrder="0" pos="609 249 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTEDITOR name="new text editor" id="1799da9e8cf495d6" memberName="te_oscport"
              virtualName="" explicitFocusOrder="0" pos="587 138 44 22" textcol="ffffffff"
              bkgcol="ffffff" outlinecol="6c838080" initialText="9000" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="0" popupmenu="1"/>
  <TOGGLEBUTTON name="new toggle button" id="b4fec6d3e1a2bae2" memberName="TBrpyFlag"
                virtualName="" explicitFocusOrder="0" pos="492 138 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="a45ef80fa16bd3f0" memberName="TBenableRotation"
                virtualName="" explicitFocusOrder="0" pos="566 114 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="new slider" id="cbc7bfc460a3cd23" memberName="s_cov_avg"
          virtualName="" explicitFocusOrder="0" pos="84 84 128 32" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0.00000000000000000000" max="1.00000000000000000000"
          int="0.01000000000000000021" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <SLIDER name="new slider" id="b82f31194d53ffb4" memberName="s_diff2dir"
          virtualName="" explicitFocusOrder="0" pos="388 136 40 74" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0.00000000000000000000" max="2.00000000000000000000"
          int="0.01000000000000000021" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <SLIDER name="new slider" id="f7fb788345473a3a" memberName="s_decBal"
          virtualName="" explicitFocusOrder="0" pos="388 241 40 74" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0.00000000000000000000" max="1.00000000000000000000"
          int="0.01000000000000000021" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
