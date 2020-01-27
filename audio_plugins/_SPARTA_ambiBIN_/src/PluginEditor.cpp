/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//#include "saf_hoa.h"
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter), progressbar(progress), fileChooser ("File", File(), true, false, false,
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

    CBorderPreset.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBorderPreset.get());
    CBorderPreset->setEditableText (false);
    CBorderPreset->setJustificationType (Justification::centredLeft);
    CBorderPreset->setTextWhenNothingSelected (TRANS("Default"));
    CBorderPreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBorderPreset->addListener (this);

    CBorderPreset->setBounds (136, 63, 104, 18);

    CBchFormat.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (Justification::centredLeft);
    CBchFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBchFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBchFormat->addListener (this);

    CBchFormat->setBounds (88, 116, 72, 18);

    CBnormScheme.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (Justification::centredLeft);
    CBnormScheme->setTextWhenNothingSelected (TRANS("N3D"));
    CBnormScheme->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnormScheme->addListener (this);

    CBnormScheme->setBounds (164, 116, 76, 18);

    TBmaxRE.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBmaxRE.get());
    TBmaxRE->setButtonText (String());
    TBmaxRE->addListener (this);

    TBmaxRE->setBounds (409, 60, 22, 24);

    s_yaw.reset (new Slider ("new slider"));
    addAndMakeVisible (s_yaw.get());
    s_yaw->setRange (-180, 180, 0.01);
    s_yaw->setSliderStyle (Slider::LinearHorizontal);
    s_yaw->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    s_yaw->setColour (Slider::backgroundColourId, Colour (0xff5c5d5e));
    s_yaw->setColour (Slider::trackColourId, Colour (0xff315b6d));
    s_yaw->setColour (Slider::textBoxTextColourId, Colours::white);
    s_yaw->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_yaw->addListener (this);

    s_yaw->setBounds (80, 171, 120, 38);

    s_pitch.reset (new Slider ("new slider"));
    addAndMakeVisible (s_pitch.get());
    s_pitch->setRange (-180, 180, 0.01);
    s_pitch->setSliderStyle (Slider::LinearVertical);
    s_pitch->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    s_pitch->setColour (Slider::backgroundColourId, Colour (0xff5c5d5e));
    s_pitch->setColour (Slider::trackColourId, Colour (0xff315b6d));
    s_pitch->setColour (Slider::textBoxTextColourId, Colours::white);
    s_pitch->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_pitch->addListener (this);

    s_pitch->setBounds (208, 137, 96, 112);

    s_roll.reset (new Slider ("new slider"));
    addAndMakeVisible (s_roll.get());
    s_roll->setRange (-180, 180, 0.01);
    s_roll->setSliderStyle (Slider::LinearVertical);
    s_roll->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    s_roll->setColour (Slider::backgroundColourId, Colour (0xff5c5d5e));
    s_roll->setColour (Slider::trackColourId, Colour (0xff315b6d));
    s_roll->setColour (Slider::textBoxTextColourId, Colours::white);
    s_roll->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_roll->addListener (this);

    s_roll->setBounds (328, 137, 96, 112);

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
    te_oscport->setColour (TextEditor::outlineColourId, Colour (0x68a3a2a2));
    te_oscport->setText (String());

    te_oscport->setBounds (16, 227, 56, 18);

    label_N_dirs.reset (new Label ("new label",
                                   String()));
    addAndMakeVisible (label_N_dirs.get());
    label_N_dirs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_N_dirs->setJustificationType (Justification::centredLeft);
    label_N_dirs->setEditable (false, false, false);
    label_N_dirs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_N_dirs->setColour (TextEditor::textColourId, Colours::black);
    label_N_dirs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_N_dirs->setBounds (536, 123, 96, 24);

    label_HRIR_len.reset (new Label ("new label",
                                     String()));
    addAndMakeVisible (label_HRIR_len.get());
    label_HRIR_len->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_HRIR_len->setJustificationType (Justification::centredLeft);
    label_HRIR_len->setEditable (false, false, false);
    label_HRIR_len->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_HRIR_len->setColour (TextEditor::textColourId, Colours::black);
    label_HRIR_len->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_HRIR_len->setBounds (536, 154, 96, 24);

    label_HRIR_fs.reset (new Label ("new label",
                                    String()));
    addAndMakeVisible (label_HRIR_fs.get());
    label_HRIR_fs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_HRIR_fs->setJustificationType (Justification::centredLeft);
    label_HRIR_fs->setEditable (false, false, false);
    label_HRIR_fs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_HRIR_fs->setColour (TextEditor::textColourId, Colours::black);
    label_HRIR_fs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_HRIR_fs->setBounds (536, 185, 96, 24);

    label_DAW_fs.reset (new Label ("new label",
                                   String()));
    addAndMakeVisible (label_DAW_fs.get());
    label_DAW_fs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_DAW_fs->setJustificationType (Justification::centredLeft);
    label_DAW_fs->setEditable (false, false, false);
    label_DAW_fs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_DAW_fs->setColour (TextEditor::textColourId, Colours::black);
    label_DAW_fs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_DAW_fs->setBounds (536, 216, 96, 24);

    t_flipPitch.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipPitch.get());
    t_flipPitch->setButtonText (String());
    t_flipPitch->addListener (this);

    t_flipPitch->setBounds (260, 209, 23, 24);

    t_flipRoll.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipRoll.get());
    t_flipRoll->setButtonText (String());
    t_flipRoll->addListener (this);

    t_flipRoll->setBounds (376, 209, 23, 24);

    t_flipYaw.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipYaw.get());
    t_flipYaw->setButtonText (String());
    t_flipYaw->addListener (this);

    t_flipYaw->setBounds (128, 209, 23, 24);

    TBcompEQ.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBcompEQ.get());
    TBcompEQ->setButtonText (String());
    TBcompEQ->addListener (this);

    TBcompEQ->setBounds (656, -16, 32, 24);

    TBrpyFlag.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBrpyFlag.get());
    TBrpyFlag->setButtonText (String());
    TBrpyFlag->addListener (this);

    TBrpyFlag->setBounds (59, 187, 24, 24);

    TBenableRot.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBenableRot.get());
    TBenableRot->setButtonText (String());
    TBenableRot->addListener (this);

    TBenableRot->setBounds (59, 165, 24, 24);

    CBdecoderMethod.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBdecoderMethod.get());
    CBdecoderMethod->setEditableText (false);
    CBdecoderMethod->setJustificationType (Justification::centredLeft);
    CBdecoderMethod->setTextWhenNothingSelected (TRANS("Default"));
    CBdecoderMethod->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBdecoderMethod->addListener (this);

    CBdecoderMethod->setBounds (88, 90, 152, 18);

    TBdiffMatching.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBdiffMatching.get());
    TBdiffMatching->setButtonText (String());
    TBdiffMatching->addListener (this);

    TBdiffMatching->setBounds (409, 87, 22, 24);

    TBphaseWarping.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBphaseWarping.get());
    TBphaseWarping->setButtonText (String());
    TBphaseWarping->addListener (this);

    TBphaseWarping->setBounds (409, 113, 22, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (656, 262);


    //[Constructor] You can add your own custom stuff here..

    /* handles */
	hVst = ownerFilter;
    hAmbi = hVst->getFXHandle();

    /* init OpenGL */
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* add options to combo boxes */
    CBorderPreset->addItem (TRANS("1st order"), INPUT_ORDER_FIRST);
    CBorderPreset->addItem (TRANS("2nd order"), INPUT_ORDER_SECOND);
    CBorderPreset->addItem (TRANS("3rd order"), INPUT_ORDER_THIRD);
    CBorderPreset->addItem (TRANS("4th order"), INPUT_ORDER_FOURTH);
    CBorderPreset->addItem (TRANS("5th order"), INPUT_ORDER_FIFTH);
    CBorderPreset->addItem (TRANS("6th order"), INPUT_ORDER_SIXTH);
    CBorderPreset->addItem (TRANS("7th order"), INPUT_ORDER_SEVENTH);
    CBdecoderMethod->addItem(TRANS("Least-Squares (LS)"), DECODING_METHOD_LS);
    CBdecoderMethod->addItem(TRANS("LS with Diffuse-EQ"), DECODING_METHOD_LSDIFFEQ);
    CBdecoderMethod->addItem(TRANS("Spatial Resampling (SPR)"), DECODING_METHOD_SPR);
    CBdecoderMethod->addItem(TRANS("Time-alignment (TA)"), DECODING_METHOD_TA);
    CBdecoderMethod->addItem(TRANS("Magnitude-LS"), DECODING_METHOD_MAGLS);
    CBchFormat->addItem (TRANS("ACN"), CH_ACN);
    CBchFormat->addItem (TRANS("FuMa"), CH_FUMA);
    CBnormScheme->addItem (TRANS("N3D"), NORM_N3D);
    CBnormScheme->addItem (TRANS("SN3D"), NORM_SN3D);
    CBnormScheme->addItem (TRANS("FuMa"), NORM_FUMA);

    /* file loader */
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
    fileChooser.setBounds (458, 86, 174, 20);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

    /* grab current parameter settings */
    CBdecoderMethod->setSelectedId(ambi_bin_getDecodingMethod(hAmbi), dontSendNotification);
    TBuseDefaultHRIRs->setToggleState(ambi_bin_getUseDefaultHRIRsflag(hAmbi), dontSendNotification);
    CBchFormat->setSelectedId(ambi_bin_getChOrder(hAmbi), dontSendNotification);
    CBnormScheme->setSelectedId(ambi_bin_getNormType(hAmbi), dontSendNotification);
    CBorderPreset->setSelectedId(ambi_bin_getInputOrderPreset(hAmbi), dontSendNotification);
    TBmaxRE->setToggleState(ambi_bin_getEnableMaxRE(hAmbi), dontSendNotification);
    TBdiffMatching->setToggleState(ambi_bin_getEnableDiffuseMatching(hAmbi), dontSendNotification);
    TBphaseWarping->setToggleState(ambi_bin_getEnablePhaseWarping(hAmbi), dontSendNotification);
    TBenableRot->setToggleState(ambi_bin_getEnableRotation(hAmbi), dontSendNotification);
    s_yaw->setValue(ambi_bin_getYaw(hAmbi), dontSendNotification);
    s_pitch->setValue(ambi_bin_getPitch(hAmbi), dontSendNotification);
    s_roll->setValue(ambi_bin_getRoll(hAmbi), dontSendNotification);
    t_flipYaw->setToggleState((bool)ambi_bin_getFlipYaw(hAmbi), dontSendNotification);
    t_flipPitch->setToggleState((bool)ambi_bin_getFlipPitch(hAmbi), dontSendNotification);
    t_flipRoll->setToggleState((bool)ambi_bin_getFlipRoll(hAmbi), dontSendNotification);
    te_oscport->setText(String(hVst->getOscPortID()), dontSendNotification);
    TBrpyFlag->setToggleState((bool)ambi_bin_getRPYflag(hAmbi), dontSendNotification);
    CBchFormat->setItemEnabled(CH_FUMA, ambi_bin_getInputOrderPreset(hAmbi)==INPUT_ORDER_FIRST ? true : false);
    CBnormScheme->setItemEnabled(NORM_FUMA, ambi_bin_getInputOrderPreset(hAmbi)==INPUT_ORDER_FIRST ? true : false);
    TBphaseWarping->setEnabled(false); // coming soon

    /* tooltips */
    CBdecoderMethod->setTooltip("Decoding method. 'Least-squares' is the simplest option, but it can give strong colourations at lower-orders. Diffuse-EQ helps with this, as does spatial resampling (SPR). However, the best options, (which also improve spatial performance at lower orders), are Time-alignment (TA) or Magnitude-LS.");
    TBuseDefaultHRIRs->setTooltip("If this is 'ticked', the plug-in is using the default HRIR set from the Spatial_Audio_Framework.");
    fileChooser.setTooltip("Optionally, a custom HRIR set may be loaded via the SOFA standard. Note that if the plug-in fails to load the specified .sofa file, it will revert to the default HRIR data.");
    CBchFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormScheme->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    CBorderPreset->setTooltip("Decoding order. Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals as input.");
    TBmaxRE->setTooltip("Enables/Disables the max_rE weights applied to the decoding matrix.");
    TBdiffMatching->setTooltip("Enables/Disables the diffuse correction applied to the decoding matrix. This is the 'C' part of the 'TAC' decoder. However, in this plug-in, it is given as a separate option so it can be applied to any of the available decoding methods.");
    TBphaseWarping->setTooltip("Not implemented yet.");
    TBenableRot->setTooltip("Enables/Disables sound-field rotation prior to decoding.");
    s_yaw->setTooltip("Sets the 'Yaw' rotation angle (in degrees).");
    s_pitch->setTooltip("Sets the 'Pitch' rotation angle (in degrees).");
    s_roll->setTooltip("Sets the 'Roll' rotation angle (in degrees).");
    t_flipYaw->setTooltip("Flips the sign (+/-) of the 'Yaw' rotation angle.");
    t_flipPitch->setTooltip("Flips the sign (+/-) of the 'Pitch' rotation angle.");
    t_flipRoll->setTooltip("Flips the sign (+/-) of the 'Roll' rotation angle.");
    te_oscport->setTooltip("The OSC port at which to receive the rotation angles. To facilitate head-tracking, send the rotation angles (in degrees) to this port ID as a 3-element vector 'ypr[3]', following the yaw-pitch-roll convention.");
    TBrpyFlag->setTooltip("If enabled, the plug-in will use the roll-pitch-yaw rotation order convention. If disabled, it will use the yaw-pitch-roll convention.");
    label_N_dirs->setTooltip("Number of HRIR directions in the current HRIR set.");
    label_HRIR_len->setTooltip("HRIR length in samples.");
    label_HRIR_fs->setTooltip("Sampling rate used when measuring/modelling the HRIRs.");
    label_DAW_fs->setTooltip("Current sampling rate, as dictated by the DAW/Host.");

	/* Specify screen refresh rate */
    startTimer(TIMER_GUI_RELATED, 20);

    /* warnings */
    currentWarning = k_warning_none;

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    TBuseDefaultHRIRs = nullptr;
    CBorderPreset = nullptr;
    CBchFormat = nullptr;
    CBnormScheme = nullptr;
    TBmaxRE = nullptr;
    s_yaw = nullptr;
    s_pitch = nullptr;
    s_roll = nullptr;
    te_oscport = nullptr;
    label_N_dirs = nullptr;
    label_HRIR_len = nullptr;
    label_HRIR_fs = nullptr;
    label_DAW_fs = nullptr;
    t_flipPitch = nullptr;
    t_flipRoll = nullptr;
    t_flipYaw = nullptr;
    TBcompEQ = nullptr;
    TBrpyFlag = nullptr;
    TBenableRot = nullptr;
    CBdecoderMethod = nullptr;
    TBdiffMatching = nullptr;
    TBphaseWarping = nullptr;


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
        int x = 0, y = 146, width = 656, height = 116;
        Colour fillColour1 = Colour (0xff1c3949), fillColour2 = Colour (0xff071e22);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       8.0f - 0.0f + x,
                                       264.0f - 146.0f + y,
                                       fillColour2,
                                       8.0f - 0.0f + x,
                                       192.0f - 146.0f + y,
                                       false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 30, width = 656, height = 116;
        Colour fillColour1 = Colour (0xff1c3949), fillColour2 = Colour (0xff071e22);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       8.0f - 0.0f + x,
                                       32.0f - 30.0f + y,
                                       fillColour2,
                                       8.0f - 0.0f + x,
                                       104.0f - 30.0f + y,
                                       false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 654.0f, height = 31.0f;
        Colour fillColour1 = Colour (0xff061c20), fillColour2 = Colour (0xff1c3949);
        Colour strokeColour = Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       0.0f - 1.0f + x,
                                       32.0f - 2.0f + y,
                                       fillColour2,
                                       656.0f - 1.0f + x,
                                       24.0f - 2.0f + y,
                                       false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 12, y = 58, width = 237, height = 82;
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
        int x = 12, y = 58, width = 237, height = 29;
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
        int x = 12, y = 139, width = 424, height = 112;
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
        int x = 12, y = 164, width = 73, height = 87;
        Colour fillColour = Colour (0x08f4f4f4);
        Colour strokeColour = Colour (0x3aa0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 248, y = 58, width = 188, height = 82;
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
        int x = 446, y = 58, width = 196, height = 54;
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
        int x = 19, y = 57, width = 141, height = 30;
        String text (TRANS("Decoding Order:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.50f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 109, width = 132, height = 30;
        String text (TRANS("Format:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.50f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 136, width = 133, height = 30;
        String text (TRANS("Rotation"));
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
        String text (TRANS("Method:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.50f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 125, y = 145, width = 63, height = 30;
        String text (TRANS("\\ypr[0]"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 223, y = 145, width = 63, height = 30;
        String text (TRANS("Pitch"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 341, y = 145, width = 63, height = 30;
        String text (TRANS("Roll"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 355, y = 225, width = 63, height = 24;
        String text (TRANS("+/-"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 240, y = 225, width = 63, height = 27;
        String text (TRANS("+/-"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 109, y = 225, width = 63, height = 27;
        String text (TRANS("+/-"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 93, y = 145, width = 60, height = 30;
        String text (TRANS("Yaw"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 261, y = 145, width = 63, height = 30;
        String text (TRANS("\\ypr[1]"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 373, y = 145, width = 63, height = 30;
        String text (TRANS("\\ypr[2]"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 446, y = 111, width = 196, height = 140;
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
        int x = 457, y = 119, width = 132, height = 30;
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
        int x = 457, y = 151, width = 132, height = 30;
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
        int x = 457, y = 182, width = 132, height = 30;
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
        int x = 457, y = 213, width = 132, height = 30;
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
        int x = 19, y = 208, width = 63, height = 23;
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
        int x = 659, y = -15, width = 80, height = 30;
        String text (TRANS("Comp. EQ:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 188, width = 63, height = 23;
        String text (TRANS("R-P-Y:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 166, width = 61, height = 23;
        String text (TRANS("Enable:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 16, y = 1, width = 196, height = 32;
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
        int x = 92, y = 1, width = 184, height = 32;
        String text (TRANS("AmbiBIN"));
        Colour fillColour = Colour (0xffdf8400);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 255, y = 57, width = 185, height = 30;
        String text (TRANS("Apply MaxRE Weights:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.50f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 255, y = 84, width = 185, height = 30;
        String text (TRANS("Diffuse Correction:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.50f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 255, y = 109, width = 185, height = 30;
        String text (TRANS("Apply Phase Warping: "));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.50f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 656, height = 2;
        Colour strokeColour = Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 654, y = 0, width = 2, height = 262;
        Colour strokeColour = Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 262;
        Colour strokeColour = Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 260, width = 656, height = 2;
        Colour strokeColour = Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

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
            g.drawText(TRANS("Sample rate (") + String(ambi_bin_getDAWsamplerate(hAmbi)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_mismatch_fs:
            g.drawText(TRANS("Sample rate mismatch between DAW/HRIRs"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(ambi_bin_getNSHrequired(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(ambi_bin_getNumEars()) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_osc_connection_fail:
            g.drawText(TRANS("Failed to connect to the selected OSC port"),
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
        ambi_bin_setUseDefaultHRIRsflag(hAmbi, (int)TBuseDefaultHRIRs->getToggleState());
        //[/UserButtonCode_TBuseDefaultHRIRs]
    }
    else if (buttonThatWasClicked == TBmaxRE.get())
    {
        //[UserButtonCode_TBmaxRE] -- add your button handler code here..
        ambi_bin_setEnableMaxRE(hAmbi, (int)TBmaxRE->getToggleState());
        //[/UserButtonCode_TBmaxRE]
    }
    else if (buttonThatWasClicked == t_flipPitch.get())
    {
        //[UserButtonCode_t_flipPitch] -- add your button handler code here..
        ambi_bin_setFlipPitch(hAmbi, (int)t_flipPitch->getToggleState());
        //[/UserButtonCode_t_flipPitch]
    }
    else if (buttonThatWasClicked == t_flipRoll.get())
    {
        //[UserButtonCode_t_flipRoll] -- add your button handler code here..
        ambi_bin_setFlipRoll(hAmbi, (int)t_flipRoll->getToggleState());
        //[/UserButtonCode_t_flipRoll]
    }
    else if (buttonThatWasClicked == t_flipYaw.get())
    {
        //[UserButtonCode_t_flipYaw] -- add your button handler code here..
        ambi_bin_setFlipYaw(hAmbi, (int)t_flipYaw->getToggleState());
        //[/UserButtonCode_t_flipYaw]
    }
    else if (buttonThatWasClicked == TBcompEQ.get())
    {
        //[UserButtonCode_TBcompEQ] -- add your button handler code here..

        //[/UserButtonCode_TBcompEQ]
    }
    else if (buttonThatWasClicked == TBrpyFlag.get())
    {
        //[UserButtonCode_TBrpyFlag] -- add your button handler code here..
        ambi_bin_setRPYflag(hAmbi, (int)TBrpyFlag->getToggleState());
        //[/UserButtonCode_TBrpyFlag]
    }
    else if (buttonThatWasClicked == TBenableRot.get())
    {
        //[UserButtonCode_TBenableRot] -- add your button handler code here..
        ambi_bin_setEnableRotation(hAmbi, (int)TBenableRot->getToggleState());
        //[/UserButtonCode_TBenableRot]
    }
    else if (buttonThatWasClicked == TBdiffMatching.get())
    {
        //[UserButtonCode_TBdiffMatching] -- add your button handler code here..
        ambi_bin_setEnableDiffuseMatching(hAmbi, (int)TBdiffMatching->getToggleState());
        //[/UserButtonCode_TBdiffMatching]
    }
    else if (buttonThatWasClicked == TBphaseWarping.get())
    {
        //[UserButtonCode_TBphaseWarping] -- add your button handler code here..
        ambi_bin_setEnablePhaseWarping(hAmbi, (int)TBphaseWarping->getToggleState());
        //[/UserButtonCode_TBphaseWarping]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PluginEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBorderPreset.get())
    {
        //[UserComboBoxCode_CBorderPreset] -- add your combo box handling code here..
        ambi_bin_setInputOrderPreset(hAmbi, (INPUT_ORDERS)CBorderPreset->getSelectedId());
        //[/UserComboBoxCode_CBorderPreset]
    }
    else if (comboBoxThatHasChanged == CBchFormat.get())
    {
        //[UserComboBoxCode_CBchFormat] -- add your combo box handling code here..
        ambi_bin_setChOrder(hAmbi, CBchFormat->getSelectedId());
        //[/UserComboBoxCode_CBchFormat]
    }
    else if (comboBoxThatHasChanged == CBnormScheme.get())
    {
        //[UserComboBoxCode_CBnormScheme] -- add your combo box handling code here..
        ambi_bin_setNormType(hAmbi, CBnormScheme->getSelectedId());
        //[/UserComboBoxCode_CBnormScheme]
    }
    else if (comboBoxThatHasChanged == CBdecoderMethod.get())
    {
        //[UserComboBoxCode_CBdecoderMethod] -- add your combo box handling code here..
        ambi_bin_setDecodingMethod(hAmbi, (DECODING_METHODS)CBdecoderMethod->getSelectedId());
        //[/UserComboBoxCode_CBdecoderMethod]
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
        ambi_bin_setYaw(hAmbi, (float)s_yaw->getValue());
        //[/UserSliderCode_s_yaw]
    }
    else if (sliderThatWasMoved == s_pitch.get())
    {
        //[UserSliderCode_s_pitch] -- add your slider handling code here..
        ambi_bin_setPitch(hAmbi, (float)s_pitch->getValue());
        //[/UserSliderCode_s_pitch]
    }
    else if (sliderThatWasMoved == s_roll.get())
    {
        //[UserSliderCode_s_roll] -- add your slider handling code here..
        ambi_bin_setRoll(hAmbi, (float)s_roll->getValue());
        //[/UserSliderCode_s_roll]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback(int timerID)
{
    switch(timerID){
        case TIMER_PROCESSING_RELATED: 
            /* Handled in PluginProcessor */
            break;

        case TIMER_GUI_RELATED:
            /* parameters whos values can change internally should be periodically refreshed */
            if(TBuseDefaultHRIRs->getToggleState() != ambi_bin_getUseDefaultHRIRsflag(hAmbi))
                TBuseDefaultHRIRs->setToggleState(ambi_bin_getUseDefaultHRIRsflag(hAmbi), dontSendNotification);
            if(s_yaw->getValue() != ambi_bin_getYaw(hAmbi))
                s_yaw->setValue(ambi_bin_getYaw(hAmbi), dontSendNotification);
            if(s_pitch->getValue() != ambi_bin_getPitch(hAmbi))
                s_pitch->setValue(ambi_bin_getPitch(hAmbi), dontSendNotification);
            if(s_roll->getValue() != ambi_bin_getRoll(hAmbi))
                s_roll->setValue(ambi_bin_getRoll(hAmbi), dontSendNotification);
            if(CBchFormat->getSelectedId() != ambi_bin_getChOrder(hAmbi))
                CBchFormat->setSelectedId(ambi_bin_getChOrder(hAmbi), dontSendNotification);
            if(CBnormScheme->getSelectedId() != ambi_bin_getNormType(hAmbi))
                CBnormScheme->setSelectedId(ambi_bin_getNormType(hAmbi), dontSendNotification);
            label_N_dirs->setText(String(ambi_bin_getNDirs(hAmbi)), dontSendNotification);
            label_HRIR_len->setText(String(ambi_bin_getHRIRlength(hAmbi)), dontSendNotification);
            label_HRIR_fs->setText(String(ambi_bin_getHRIRsamplerate(hAmbi)), dontSendNotification);
            label_DAW_fs->setText(String(ambi_bin_getDAWsamplerate(hAmbi)), dontSendNotification);
            CBchFormat->setItemEnabled(CH_FUMA, ambi_bin_getInputOrderPreset(hAmbi)==INPUT_ORDER_FIRST ? true : false);
            CBnormScheme->setItemEnabled(NORM_FUMA, ambi_bin_getInputOrderPreset(hAmbi)==INPUT_ORDER_FIRST ? true : false);

            /* Progress bar */
            if(ambi_bin_getCodecStatus(hAmbi)==CODEC_STATUS_INITIALISING){
                addAndMakeVisible(progressbar);
                progress = (double)ambi_bin_getProgressBar0_1(hAmbi);
                char text[AMBI_BIN_PROGRESSBARTEXT_CHAR_LENGTH];
                ambi_bin_getProgressBarText(hAmbi, (char*)text);
                progressbar.setTextToDisplay(String(text));
            }
            else
                removeChildComponent(&progressbar);

            /* Some parameters shouldn't be editable during initialisation*/
            if(ambi_bin_getCodecStatus(hAmbi)==CODEC_STATUS_INITIALISING){
                if(TBuseDefaultHRIRs->isEnabled())
                    TBuseDefaultHRIRs->setEnabled(false);
                if(CBorderPreset->isEnabled())
                    CBorderPreset->setEnabled(false);
                if(TBmaxRE->isEnabled())
                    TBmaxRE->setEnabled(false);
                if(TBcompEQ->isEnabled())
                    TBcompEQ->setEnabled(false);
                if(CBdecoderMethod->isEnabled())
                    CBdecoderMethod->setEnabled(false);
                if(TBdiffMatching->isEnabled())
                    TBdiffMatching->setEnabled(false);
                if(TBphaseWarping->isEnabled())
                    TBphaseWarping->setEnabled(false);
                if(fileChooser.isEnabled())
                    fileChooser.setEnabled(false);
            }
            else {
                if(!TBuseDefaultHRIRs->isEnabled())
                    TBuseDefaultHRIRs->setEnabled(true);
                if(!CBorderPreset->isEnabled())
                    CBorderPreset->setEnabled(true);
                if(!TBmaxRE->isEnabled())
                    TBmaxRE->setEnabled(true);
                if(!TBcompEQ->isEnabled())
                    TBcompEQ->setEnabled(true);
                if(!CBdecoderMethod->isEnabled())
                    CBdecoderMethod->setEnabled(true);
                if(!TBdiffMatching->isEnabled())
                    TBdiffMatching->setEnabled(true);
                if(!TBphaseWarping->isEnabled())
                    TBphaseWarping->setEnabled(true);
                if(!fileChooser.isEnabled())
                    fileChooser.setEnabled(true);
            }

            /* display warning message, if needed */
            if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
                currentWarning = k_warning_frameSize;
                repaint(0,0,getWidth(),32);
            }
            else if ( !((ambi_bin_getDAWsamplerate(hAmbi) == 44.1e3) || (ambi_bin_getDAWsamplerate(hAmbi) == 48e3)) ){
                currentWarning = k_warning_supported_fs;
                repaint(0,0,getWidth(),32);
            }
            else if (ambi_bin_getDAWsamplerate(hAmbi) != ambi_bin_getHRIRsamplerate(hAmbi)){
                currentWarning = k_warning_mismatch_fs;
                repaint(0,0,getWidth(),32);
            }
            else if ((hVst->getCurrentNumInputs() < ambi_bin_getNSHrequired(hAmbi))){
                currentWarning = k_warning_NinputCH;
                repaint(0,0,getWidth(),32);
            }
            else if ((hVst->getCurrentNumOutputs() < ambi_bin_getNumEars())){
                currentWarning = k_warning_NoutputCH;
                repaint(0,0,getWidth(),32);
            }
            else if(!hVst->getOscPortConnected() && ambi_bin_getEnableRotation(hAmbi)){
                currentWarning = k_warning_osc_connection_fail;
                repaint(0,0,getWidth(),32);
            }
            else if(currentWarning){
                currentWarning = k_warning_none;
                repaint(0,0,getWidth(),32);
            }

            /* check if OSC port has changed */
            if(hVst->getOscPortID() != te_oscport->getText().getIntValue())
                hVst->setOscPortID(te_oscport->getText().getIntValue());
            break;
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
                 parentClasses="public AudioProcessorEditor, public MultiTimer, private FilenameComponentListener"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter), progressbar(progress), fileChooser (&quot;File&quot;, File(), true, false, false,&#10;                       &quot;*.sofa;*.nc;&quot;, String(),&#10;                       &quot;Load SOFA File&quot;)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="656" initialHeight="262">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 146 656 116" fill="linear: 8 264, 8 192, 0=ff1c3949, 1=ff071e22"
          hasStroke="0"/>
    <RECT pos="0 30 656 116" fill="linear: 8 32, 8 104, 0=ff1c3949, 1=ff071e22"
          hasStroke="0"/>
    <ROUNDRECT pos="1 2 654 31" cornerSize="5.0" fill="linear: 0 32, 656 24, 0=ff061c20, 1=ff1c3949"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="12 58 237 82" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 58 237 29" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 35a0a0a0"/>
    <RECT pos="12 139 424 112" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 164 73 87" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 3aa0a0a0"/>
    <RECT pos="248 58 188 82" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="446 58 196 54" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="164 32 149 30" fill="solid: ffffffff" hasStroke="0" text="Decoding Settings"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="520 32 113 30" fill="solid: ffffffff" hasStroke="0" text="Output"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="459 56 165 30" fill="solid: ffffffff" hasStroke="0" text="Use Default HRIR set:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 57 141 30" fill="solid: ffffffff" hasStroke="0" text="Decoding Order:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 109 132 30" fill="solid: ffffffff" hasStroke="0" text="Format:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 136 133 30" fill="solid: ffffffff" hasStroke="0" text="Rotation"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 84 125 30" fill="solid: ffffffff" hasStroke="0" text="Method:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="125 145 63 30" fill="solid: ffffffff" hasStroke="0" text="\ypr[0]"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="223 145 63 30" fill="solid: ffffffff" hasStroke="0" text="Pitch"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="341 145 63 30" fill="solid: ffffffff" hasStroke="0" text="Roll"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="355 225 63 24" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="240 225 63 27" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="109 225 63 27" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="93 145 60 30" fill="solid: ffffffff" hasStroke="0" text="Yaw"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="261 145 63 30" fill="solid: ffffffff" hasStroke="0" text="\ypr[1]"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="373 145 63 30" fill="solid: ffffffff" hasStroke="0" text="\ypr[2]"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <RECT pos="446 111 196 140" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="457 119 132 30" fill="solid: ffffffff" hasStroke="0" text="N dirs:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="457 151 132 30" fill="solid: ffffffff" hasStroke="0" text="HRIR len:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="457 182 132 30" fill="solid: ffffffff" hasStroke="0" text="HRIR fs:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="457 213 132 30" fill="solid: ffffffff" hasStroke="0" text="DAW fs:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 208 63 23" fill="solid: ffffffff" hasStroke="0" text="OSC port:"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="659 -15 80 30" fill="solid: ffffffff" hasStroke="0" text="Comp. EQ:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 188 63 23" fill="solid: ffffffff" hasStroke="0" text="R-P-Y:"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 166 61 23" fill="solid: ffffffff" hasStroke="0" text="Enable:"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 1 196 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 184 32" fill="solid: ffdf8400" hasStroke="0" text="AmbiBIN"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="255 57 185 30" fill="solid: ffffffff" hasStroke="0" text="Apply MaxRE Weights:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="255 84 185 30" fill="solid: ffffffff" hasStroke="0" text="Diffuse Correction:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="255 109 185 30" fill="solid: ffffffff" hasStroke="0" text="Apply Phase Warping: "
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 656 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="654 0 2 262" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 262" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 260 656 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
  </BACKGROUND>
  <TOGGLEBUTTON name="new toggle button" id="f7f951a1b21e1a11" memberName="TBuseDefaultHRIRs"
                virtualName="" explicitFocusOrder="0" pos="614 60 21 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="d83602bab6f1a999" memberName="CBorderPreset"
            virtualName="" explicitFocusOrder="0" pos="136 63 104 18" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="a36915795f16ceb6" memberName="CBchFormat"
            virtualName="" explicitFocusOrder="0" pos="88 116 72 18" editable="0"
            layout="33" items="" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="e10be54628a6df43" memberName="CBnormScheme"
            virtualName="" explicitFocusOrder="0" pos="164 116 76 18" editable="0"
            layout="33" items="" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="new toggle button" id="943aa789e193d13a" memberName="TBmaxRE"
                virtualName="" explicitFocusOrder="0" pos="409 60 22 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="new slider" id="ace036a85eec9703" memberName="s_yaw" virtualName=""
          explicitFocusOrder="0" pos="80 171 120 38" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="-180.0" max="180.0" int="0.01" style="LinearHorizontal"
          textBoxPos="TextBoxAbove" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="9af7dd86cd139d85" memberName="s_pitch"
          virtualName="" explicitFocusOrder="0" pos="208 137 96 112" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="-180.0" max="180.0" int="0.01" style="LinearVertical" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="b5d39bb257b3289a" memberName="s_roll" virtualName=""
          explicitFocusOrder="0" pos="328 137 96 112" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="-180.0" max="180.0" int="0.01" style="LinearVertical" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TEXTEDITOR name="new text editor" id="1799da9e8cf495d6" memberName="te_oscport"
              virtualName="" explicitFocusOrder="0" pos="16 227 56 18" textcol="ffffffff"
              bkgcol="ffffff" outlinecol="68a3a2a2" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="0" popupmenu="1"/>
  <LABEL name="new label" id="167c5975ece5bfaa" memberName="label_N_dirs"
         virtualName="" explicitFocusOrder="0" pos="536 123 96 24" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e14d1c2e00d7849b" memberName="label_HRIR_len"
         virtualName="" explicitFocusOrder="0" pos="536 154 96 24" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f8b5274e0c8768f4" memberName="label_HRIR_fs"
         virtualName="" explicitFocusOrder="0" pos="536 185 96 24" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c59fb2aab2496c4e" memberName="label_DAW_fs"
         virtualName="" explicitFocusOrder="0" pos="536 216 96 24" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="c58241ee52766d62" memberName="t_flipPitch"
                virtualName="" explicitFocusOrder="0" pos="260 209 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="717e9536768dfd8c" memberName="t_flipRoll"
                virtualName="" explicitFocusOrder="0" pos="376 209 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="ac47b63592b1d4cf" memberName="t_flipYaw"
                virtualName="" explicitFocusOrder="0" pos="128 209 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="d5b2026137993288" memberName="TBcompEQ"
                virtualName="" explicitFocusOrder="0" pos="656 -16 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="b4fec6d3e1a2bae2" memberName="TBrpyFlag"
                virtualName="" explicitFocusOrder="0" pos="59 187 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="dfb8e588ab02032d" memberName="TBenableRot"
                virtualName="" explicitFocusOrder="0" pos="59 165 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="a7219c15eb41112a" memberName="CBdecoderMethod"
            virtualName="" explicitFocusOrder="0" pos="88 90 152 18" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="new toggle button" id="8039737efa3e209e" memberName="TBdiffMatching"
                virtualName="" explicitFocusOrder="0" pos="409 87 22 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="f65a4553b49a563a" memberName="TBphaseWarping"
                virtualName="" explicitFocusOrder="0" pos="409 113 22 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

