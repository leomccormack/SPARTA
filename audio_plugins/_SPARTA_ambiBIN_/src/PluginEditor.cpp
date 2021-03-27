/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

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

    TBuseDefaultHRIRs.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBuseDefaultHRIRs.get());
    TBuseDefaultHRIRs->setButtonText (juce::String());
    TBuseDefaultHRIRs->addListener (this);

    TBuseDefaultHRIRs->setBounds (613, 60, 27, 24);

    CBorderPreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBorderPreset.get());
    CBorderPreset->setEditableText (false);
    CBorderPreset->setJustificationType (juce::Justification::centredLeft);
    CBorderPreset->setTextWhenNothingSelected (TRANS("Default"));
    CBorderPreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBorderPreset->addListener (this);

    CBorderPreset->setBounds (136, 63, 104, 18);

    CBchFormat.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (juce::Justification::centredLeft);
    CBchFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBchFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBchFormat->addListener (this);

    CBchFormat->setBounds (88, 116, 72, 18);

    CBnormScheme.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (juce::Justification::centredLeft);
    CBnormScheme->setTextWhenNothingSelected (TRANS("N3D"));
    CBnormScheme->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnormScheme->addListener (this);

    CBnormScheme->setBounds (164, 116, 76, 18);

    TBmaxRE.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBmaxRE.get());
    TBmaxRE->setButtonText (juce::String());
    TBmaxRE->addListener (this);

    TBmaxRE->setBounds (411, 60, 22, 24);

    s_yaw.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_yaw.get());
    s_yaw->setRange (-180, 180, 0.01);
    s_yaw->setSliderStyle (juce::Slider::LinearHorizontal);
    s_yaw->setTextBoxStyle (juce::Slider::TextBoxAbove, false, 80, 20);
    s_yaw->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_yaw->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    s_yaw->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_yaw->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_yaw->addListener (this);

    s_yaw->setBounds (80, 171, 120, 38);

    s_pitch.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_pitch.get());
    s_pitch->setRange (-180, 180, 0.01);
    s_pitch->setSliderStyle (juce::Slider::LinearVertical);
    s_pitch->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);
    s_pitch->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_pitch->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    s_pitch->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_pitch->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_pitch->addListener (this);

    s_pitch->setBounds (208, 137, 96, 112);

    s_roll.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_roll.get());
    s_roll->setRange (-180, 180, 0.01);
    s_roll->setSliderStyle (juce::Slider::LinearVertical);
    s_roll->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);
    s_roll->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_roll->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    s_roll->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_roll->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_roll->addListener (this);

    s_roll->setBounds (328, 137, 96, 112);

    te_oscport.reset (new juce::TextEditor ("new text editor"));
    addAndMakeVisible (te_oscport.get());
    te_oscport->setMultiLine (false);
    te_oscport->setReturnKeyStartsNewLine (false);
    te_oscport->setReadOnly (false);
    te_oscport->setScrollbarsShown (true);
    te_oscport->setCaretVisible (false);
    te_oscport->setPopupMenuEnabled (true);
    te_oscport->setColour (juce::TextEditor::textColourId, juce::Colours::white);
    te_oscport->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00ffffff));
    te_oscport->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x68a3a2a2));
    te_oscport->setText (juce::String());

    te_oscport->setBounds (16, 227, 56, 18);

    label_N_dirs.reset (new juce::Label ("new label",
                                         juce::String()));
    addAndMakeVisible (label_N_dirs.get());
    label_N_dirs->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_N_dirs->setJustificationType (juce::Justification::centredLeft);
    label_N_dirs->setEditable (false, false, false);
    label_N_dirs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_N_dirs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_N_dirs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_N_dirs->setBounds (536, 148, 96, 24);

    label_HRIR_len.reset (new juce::Label ("new label",
                                           juce::String()));
    addAndMakeVisible (label_HRIR_len.get());
    label_HRIR_len->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_HRIR_len->setJustificationType (juce::Justification::centredLeft);
    label_HRIR_len->setEditable (false, false, false);
    label_HRIR_len->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_HRIR_len->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_HRIR_len->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_HRIR_len->setBounds (536, 171, 96, 24);

    label_HRIR_fs.reset (new juce::Label ("new label",
                                          juce::String()));
    addAndMakeVisible (label_HRIR_fs.get());
    label_HRIR_fs->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_HRIR_fs->setJustificationType (juce::Justification::centredLeft);
    label_HRIR_fs->setEditable (false, false, false);
    label_HRIR_fs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_HRIR_fs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_HRIR_fs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_HRIR_fs->setBounds (536, 194, 96, 24);

    label_DAW_fs.reset (new juce::Label ("new label",
                                         juce::String()));
    addAndMakeVisible (label_DAW_fs.get());
    label_DAW_fs->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_DAW_fs->setJustificationType (juce::Justification::centredLeft);
    label_DAW_fs->setEditable (false, false, false);
    label_DAW_fs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_DAW_fs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_DAW_fs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_DAW_fs->setBounds (536, 217, 96, 24);

    t_flipPitch.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipPitch.get());
    t_flipPitch->setButtonText (juce::String());
    t_flipPitch->addListener (this);

    t_flipPitch->setBounds (260, 209, 23, 24);

    t_flipRoll.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipRoll.get());
    t_flipRoll->setButtonText (juce::String());
    t_flipRoll->addListener (this);

    t_flipRoll->setBounds (376, 209, 23, 24);

    t_flipYaw.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipYaw.get());
    t_flipYaw->setButtonText (juce::String());
    t_flipYaw->addListener (this);

    t_flipYaw->setBounds (128, 209, 23, 24);

    TBcompEQ.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBcompEQ.get());
    TBcompEQ->setButtonText (juce::String());
    TBcompEQ->addListener (this);

    TBcompEQ->setBounds (656, -16, 32, 24);

    TBrpyFlag.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBrpyFlag.get());
    TBrpyFlag->setButtonText (juce::String());
    TBrpyFlag->addListener (this);

    TBrpyFlag->setBounds (59, 187, 24, 24);

    TBenableRot.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBenableRot.get());
    TBenableRot->setButtonText (juce::String());
    TBenableRot->addListener (this);

    TBenableRot->setBounds (59, 165, 24, 24);

    CBdecoderMethod.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBdecoderMethod.get());
    CBdecoderMethod->setEditableText (false);
    CBdecoderMethod->setJustificationType (juce::Justification::centredLeft);
    CBdecoderMethod->setTextWhenNothingSelected (TRANS("Default"));
    CBdecoderMethod->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBdecoderMethod->addListener (this);

    CBdecoderMethod->setBounds (88, 90, 152, 18);

    TBdiffMatching.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBdiffMatching.get());
    TBdiffMatching->setButtonText (juce::String());
    TBdiffMatching->addListener (this);

    TBdiffMatching->setBounds (411, 87, 22, 24);

    TBtruncationEQ.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBtruncationEQ.get());
    TBtruncationEQ->setButtonText (juce::String());
    TBtruncationEQ->addListener (this);

    TBtruncationEQ->setBounds (411, 113, 22, 24);

    CBhrirPreProc.reset (new juce::ComboBox ("Hrir Pre-Processing"));
    addAndMakeVisible (CBhrirPreProc.get());
    CBhrirPreProc->setEditableText (false);
    CBhrirPreProc->setJustificationType (juce::Justification::centredLeft);
    CBhrirPreProc->setTextWhenNothingSelected (TRANS("Please Select"));
    CBhrirPreProc->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBhrirPreProc->addListener (this);

    CBhrirPreProc->setBounds (520, 113, 113, 18);


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

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* add options to combo boxes */
    CBorderPreset->addItem (TRANS("1st order"), SH_ORDER_FIRST);
    CBorderPreset->addItem (TRANS("2nd order"), SH_ORDER_SECOND);
    CBorderPreset->addItem (TRANS("3rd order"), SH_ORDER_THIRD);
    CBorderPreset->addItem (TRANS("4th order"), SH_ORDER_FOURTH);
    CBorderPreset->addItem (TRANS("5th order"), SH_ORDER_FIFTH);
    CBorderPreset->addItem (TRANS("6th order"), SH_ORDER_SIXTH);
    CBorderPreset->addItem (TRANS("7th order"), SH_ORDER_SEVENTH);
    CBdecoderMethod->addItem(TRANS("Least-Squares (LS)"), DECODING_METHOD_LS);
    CBdecoderMethod->addItem(TRANS("LS with Ambi-Diff-EQ"), DECODING_METHOD_LSDIFFEQ);
    CBdecoderMethod->addItem(TRANS("Spatial Resampling (SPR)"), DECODING_METHOD_SPR);
    CBdecoderMethod->addItem(TRANS("Time-alignment (TA)"), DECODING_METHOD_TA);
    CBdecoderMethod->addItem(TRANS("Magnitude-LS"), DECODING_METHOD_MAGLS);
    CBchFormat->addItem (TRANS("ACN"), CH_ACN);
    CBchFormat->addItem (TRANS("FuMa"), CH_FUMA);
    CBnormScheme->addItem (TRANS("N3D"), NORM_N3D);
    CBnormScheme->addItem (TRANS("SN3D"), NORM_SN3D);
    CBnormScheme->addItem (TRANS("FuMa"), NORM_FUMA);
    CBhrirPreProc->addItem (TRANS("Off"), HRIR_PREPROC_OFF);
    CBhrirPreProc->addItem (TRANS("Diffuse-field EQ"), HRIR_PREPROC_EQ);
    CBhrirPreProc->addItem (TRANS("Phase Simplification"), HRIR_PREPROC_PHASE);
    CBhrirPreProc->addItem (TRANS("EQ & Phase"), HRIR_PREPROC_ALL);

    /* file loader */
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
    fileChooser.setBounds (452, 86, 181, 20);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);

    /* grab current parameter settings */
    CBdecoderMethod->setSelectedId(ambi_bin_getDecodingMethod(hAmbi), dontSendNotification);
    TBuseDefaultHRIRs->setToggleState(ambi_bin_getUseDefaultHRIRsflag(hAmbi), dontSendNotification);
    CBchFormat->setSelectedId(ambi_bin_getChOrder(hAmbi), dontSendNotification);
    CBnormScheme->setSelectedId(ambi_bin_getNormType(hAmbi), dontSendNotification);
    CBorderPreset->setSelectedId(ambi_bin_getInputOrderPreset(hAmbi), dontSendNotification);
    TBmaxRE->setToggleState(ambi_bin_getEnableMaxRE(hAmbi), dontSendNotification);
    TBdiffMatching->setToggleState(ambi_bin_getEnableDiffuseMatching(hAmbi), dontSendNotification);
    TBtruncationEQ->setToggleState(ambi_bin_getEnableTruncationEQ(hAmbi), dontSendNotification);
    TBenableRot->setToggleState(ambi_bin_getEnableRotation(hAmbi), dontSendNotification);
    s_yaw->setValue(ambi_bin_getYaw(hAmbi), dontSendNotification);
    s_pitch->setValue(ambi_bin_getPitch(hAmbi), dontSendNotification);
    s_roll->setValue(ambi_bin_getRoll(hAmbi), dontSendNotification);
    t_flipYaw->setToggleState((bool)ambi_bin_getFlipYaw(hAmbi), dontSendNotification);
    t_flipPitch->setToggleState((bool)ambi_bin_getFlipPitch(hAmbi), dontSendNotification);
    t_flipRoll->setToggleState((bool)ambi_bin_getFlipRoll(hAmbi), dontSendNotification);
    te_oscport->setText(String(hVst->getOscPortID()), dontSendNotification);
    TBrpyFlag->setToggleState((bool)ambi_bin_getRPYflag(hAmbi), dontSendNotification);
    CBchFormat->setItemEnabled(CH_FUMA, ambi_bin_getInputOrderPreset(hAmbi)==SH_ORDER_FIRST ? true : false);
    CBnormScheme->setItemEnabled(NORM_FUMA, ambi_bin_getInputOrderPreset(hAmbi)==SH_ORDER_FIRST ? true : false);

    /* tooltips */
    CBdecoderMethod->setTooltip("'Least-squares' is the simplest option, but it can give strong colourations at lower-orders; which (perhaps counter-intuitively) becomes worse as more HRIR measurements are used to compute the decoder, since more high-frequency energy is assigned to ever higher orders and lost due to the order truncation. \"Diffuse-field EQ\" applied in the spherical harmonic domain helps mitigate this problem, as does toggling on \"Apply Truncation EQ\". On the other hand, Spatial resampling (SPR), which is on the same lines as the virtual loudspeaker approach (using a subset of the HRIR measurements), will also mitigate this colouration problem as it will \"alias\" the energy of higher-order components back into the lower-order components (instead of loosing this energy to order truncation). \n\nMore perceptually-motivated decoding options, which also aim to improve the spatial performance of the decoding, are the Time-alignment (TA) or Magnitude-LS decoding options. In a nutshell, they aim to exploit the knowledge that humans are not very sensitive to interaural time differences (ITDs) at high frequencies (~1.5kHz; as described by the Haas effect); instead prioritising fitting the Ambisonic patterns to only the magnitudes of the HRTFs at these frequencies - leading to improved reproduction of the interaural level differences (ILDs). \n\nHowever! Note that this plug-in already does some pre-processing of the HRIRs before computing the binaural decoders, in particular the \"Phase Simplication\" option is our (unpublished) way of doing something similar to what the TA/MagLS decoders aim to do more explicitly. Since the interaural phase differences (IPDs) are simplified, this also has the benefit of improving the least-squares fitting of the Ambisonic patterns to the target HRIR directivities. Therefore, try disabling this option if you want to listen to the different decoders as they would have sounded in their original publication evaluations.\n\nNote also that the Time-alignment (TA) decoder is without the diffuse-covariance constraint (TAC) that was also proposed in the original paper. Instead this constraint is provided as it's own toggle button (\"Apply Cov. Constriant\") and can therefore be applied to any decoding method.");
    TBuseDefaultHRIRs->setTooltip("If this is 'ticked', the plug-in is using the default HRIR set from the Spatial_Audio_Framework.");
    fileChooser.setTooltip("Optionally, a custom HRIR set may be loaded via the SOFA standard. Note that if the plug-in fails to load the specified .sofa file, it will revert to the default HRIR data.");
    CBchFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormScheme->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    CBorderPreset->setTooltip("Decoding order. Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals as input.");
    TBmaxRE->setTooltip("Enables/Disables the max_rE weights applied to the decoding matrix. Much like with loudspeaker decoding, the spatial \"tapering\" attained by applying these maxRE weights will lead to sources becoming a bit more \"spread\", but also mitigating the problem of some source energy being routed to the opposite side of the sphere.");
    TBdiffMatching->setTooltip("Enables/Disables the diffuse covariance constraint applied to the decoding matrix. This is the 'C' part of the 'TAC' decoder. However, in this plug-in, it is given as a separate option so it can be applied to any of the available decoding methods. \n\nNote, this is not the same as applying diffuse-field EQ on the HRIRs; this is a \"spatial\" manipulation and not a timbral one. \n\nAlso note that, while it may make recodings sound broader/wider at lower-orders, it does so at the cost of greatly damaging the spatial properties of the recording (pulling everything to the sides: almost stereo-widening); therefore, we would argue that it is not \"correct\" to enable this by default... although, it can sound pretty good in some cases.");
    TBtruncationEQ->setTooltip("Applies an EQ that counteracts the high frequency loss induced by order truncation. This is an alternative to the \"Ambi-Diff-EQ\", but it is only suitable to apply this on the \"Least-Squares\" decoder and without the \"phase-simplification\" pre-processing applied to the HRIRs. ");
    CBhrirPreProc->setTooltip("Pre-processing options for the HRIRs. Diffuse-field EQ is based on a weighted summation of all the HRTF magnitudes in the currently loaded set. The phase-simplification involves estimating the ITDs for all the HRIRs, removing the phase from the HRTFs, but then re-introducing the phase as IPDs per frequency-bin. Note that this phase-simplification significantly helps when computing the least-squares fitting of the spherical harmonics to the HRTFs; on the same lines as what the TA and MagLS decoding options aim to do more explicitly. Disabling the phase simplification will result in more drastic differences between the different decoding methods.");
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

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("This plug-in is a linear and time-invariant binaural Ambisonic decoder, which implements a number of different decoder designs and processing \"tricks\". \n\nAs with most of the SPARTA plugins, the default settings generally represent the \"state-of-the-art\" approach; or at least a configuration that is suitable for the majority of applications. The vast number of configuration options and decoding methods offered by this plug-in are mainly intended for research and educational purposes, but may nevertheless be fun to play around with :-)\n\nNote that all of the configuration options have detailed tooltips, and more information about them may be found in the references stated in the saf_hoa module of the Spatial_Audio_Framework."));

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
    TBtruncationEQ = nullptr;
    CBhrirPreProc = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    setLookAndFeel(nullptr);
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 146, width = 656, height = 116;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
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
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
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
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
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
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 58, width = 237, height = 29;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x35a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 139, width = 424, height = 112;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 164, width = 73, height = 87;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x3aa0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 248, y = 58, width = 188, height = 82;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 445, y = 58, width = 196, height = 82;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 164, y = 32, width = 149, height = 30;
        juce::String text (TRANS("Decoding Settings"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 520, y = 32, width = 113, height = 30;
        juce::String text (TRANS("Output"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 451, y = 56, width = 157, height = 30;
        juce::String text (TRANS("Use Default HRIR set:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 57, width = 141, height = 30;
        juce::String text (TRANS("Decoding Order:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 109, width = 132, height = 30;
        juce::String text (TRANS("Format:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 136, width = 133, height = 30;
        juce::String text (TRANS("Rotation"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 84, width = 125, height = 30;
        juce::String text (TRANS("Method:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 125, y = 145, width = 63, height = 30;
        juce::String text (TRANS("\\ypr[0]"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 223, y = 145, width = 63, height = 30;
        juce::String text (TRANS("Pitch"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 341, y = 145, width = 63, height = 30;
        juce::String text (TRANS("Roll"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 355, y = 225, width = 63, height = 24;
        juce::String text (TRANS("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 240, y = 225, width = 63, height = 27;
        juce::String text (TRANS("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 109, y = 225, width = 63, height = 27;
        juce::String text (TRANS("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 93, y = 145, width = 60, height = 30;
        juce::String text (TRANS("Yaw"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 261, y = 145, width = 63, height = 30;
        juce::String text (TRANS("\\ypr[1]"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 373, y = 145, width = 63, height = 30;
        juce::String text (TRANS("\\ypr[2]"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 445, y = 139, width = 196, height = 112;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 452, y = 144, width = 132, height = 30;
        juce::String text (TRANS("Num dirs:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 452, y = 168, width = 132, height = 30;
        juce::String text (TRANS("HRIR length:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 452, y = 192, width = 132, height = 30;
        juce::String text (TRANS("HRIR fs:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 208, width = 63, height = 23;
        juce::String text (TRANS("OSC port:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 659, y = -15, width = 80, height = 30;
        juce::String text (TRANS("Comp. EQ:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 188, width = 63, height = 23;
        juce::String text (TRANS("R-P-Y:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 166, width = 61, height = 23;
        juce::String text (TRANS("Enable:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 1, width = 196, height = 32;
        juce::String text (TRANS("SPARTA|"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.80f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 92, y = 1, width = 184, height = 32;
        juce::String text (TRANS("AmbiBIN"));
        juce::Colour fillColour = juce::Colour (0xffdf8400);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 254, y = 57, width = 185, height = 30;
        juce::String text (TRANS("Apply MaxRE Weights:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 254, y = 84, width = 185, height = 30;
        juce::String text (TRANS("Diffuse Cov. Constraint:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 254, y = 109, width = 185, height = 30;
        juce::String text (TRANS("Apply Truncation EQ: "));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 656, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 654, y = 0, width = 2, height = 262;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 262;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 260, width = 656, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 451, y = 106, width = 83, height = 30;
        juce::String text (TRANS("Pre-Proc:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 452, y = 216, width = 132, height = 30;
        juce::String text (TRANS("DAW fs:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
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
            g.drawText(TRANS("Set frame size to multiple of ") + String(ambi_bin_getFrameSize()),
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

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
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
    else if (buttonThatWasClicked == TBtruncationEQ.get())
    {
        //[UserButtonCode_TBtruncationEQ] -- add your button handler code here..
        ambi_bin_setEnableTruncationEQ(hAmbi, (int)TBtruncationEQ->getToggleState());
        //[/UserButtonCode_TBtruncationEQ]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBorderPreset.get())
    {
        //[UserComboBoxCode_CBorderPreset] -- add your combo box handling code here..
        ambi_bin_setInputOrderPreset(hAmbi, (SH_ORDERS)CBorderPreset->getSelectedId());
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
        ambi_bin_setDecodingMethod(hAmbi, (AMBI_BIN_DECODING_METHODS)CBdecoderMethod->getSelectedId());
        //[/UserComboBoxCode_CBdecoderMethod]
    }
    else if (comboBoxThatHasChanged == CBhrirPreProc.get())
    {
        //[UserComboBoxCode_CBhrirPreProc] -- add your combo box handling code here..
        ambi_bin_setHRIRsPreProc(hAmbi, (AMBI_BIN_PREPROC)CBhrirPreProc->getSelectedId());
        //[/UserComboBoxCode_CBhrirPreProc]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
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
            if(CBhrirPreProc->getSelectedId() != ambi_bin_getHRIRsPreProc(hAmbi))
                CBhrirPreProc->setSelectedId(ambi_bin_getHRIRsPreProc(hAmbi), dontSendNotification);
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
            CBchFormat->setItemEnabled(CH_FUMA, ambi_bin_getInputOrderPreset(hAmbi)==SH_ORDER_FIRST ? true : false);
            CBnormScheme->setItemEnabled(NORM_FUMA, ambi_bin_getInputOrderPreset(hAmbi)==SH_ORDER_FIRST ? true : false);


            /* Progress bar */
            if(ambi_bin_getCodecStatus(hAmbi)==CODEC_STATUS_INITIALISING){
                addAndMakeVisible(progressbar);
                progress = (double)ambi_bin_getProgressBar0_1(hAmbi);
                char text[PROGRESSBARTEXT_CHAR_LENGTH];
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
                if(TBtruncationEQ->isEnabled())
                    TBtruncationEQ->setEnabled(false);
                if(CBhrirPreProc->isEnabled())
                    CBhrirPreProc->setEnabled(false);
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
                if(!TBtruncationEQ->isEnabled())
                    TBtruncationEQ->setEnabled(true);
                if(!CBhrirPreProc->isEnabled())
                    CBhrirPreProc->setEnabled(true);
                if(!fileChooser.isEnabled())
                    fileChooser.setEnabled(true);
            }

            /* Truncation EQ is only suitable for LS-decoding, without the phase simplication on the HRIRs */
            if(ambi_bin_getHRIRsPreProc(hAmbi) != HRIR_PREPROC_PHASE && ambi_bin_getHRIRsPreProc(hAmbi) != HRIR_PREPROC_ALL &&
               ambi_bin_getDecodingMethod(hAmbi) == DECODING_METHOD_LS){
                TBtruncationEQ->setEnabled(true);
            }
            else
                TBtruncationEQ->setEnabled(false);

            /* display warning message, if needed */
            if ((hVst->getCurrentBlockSize() % ambi_bin_getFrameSize()) != 0){
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
    <RECT pos="0 146 656 116" fill="linear: 8 264, 8 192, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="0 30 656 116" fill="linear: 8 32, 8 104, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <ROUNDRECT pos="1 2 654 31" cornerSize="5.0" fill="linear: 0 32, 656 24, 0=ff041518, 1=ff19313f"
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
    <RECT pos="445 58 196 82" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="164 32 149 30" fill="solid: ffffffff" hasStroke="0" text="Decoding Settings"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="520 32 113 30" fill="solid: ffffffff" hasStroke="0" text="Output"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="451 56 157 30" fill="solid: ffffffff" hasStroke="0" text="Use Default HRIR set:"
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
    <RECT pos="445 139 196 112" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="452 144 132 30" fill="solid: ffffffff" hasStroke="0" text="Num dirs:"
          fontname="Default font" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="452 168 132 30" fill="solid: ffffffff" hasStroke="0" text="HRIR length:"
          fontname="Default font" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="452 192 132 30" fill="solid: ffffffff" hasStroke="0" text="HRIR fs:"
          fontname="Default font" fontsize="13.0" kerning="0.0" bold="1"
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
    <TEXT pos="254 57 185 30" fill="solid: ffffffff" hasStroke="0" text="Apply MaxRE Weights:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="254 84 185 30" fill="solid: ffffffff" hasStroke="0" text="Diffuse Cov. Constraint:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="254 109 185 30" fill="solid: ffffffff" hasStroke="0" text="Apply Truncation EQ: "
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
    <TEXT pos="451 106 83 30" fill="solid: ffffffff" hasStroke="0" text="Pre-Proc:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="452 216 132 30" fill="solid: ffffffff" hasStroke="0" text="DAW fs:"
          fontname="Default font" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <TOGGLEBUTTON name="new toggle button" id="f7f951a1b21e1a11" memberName="TBuseDefaultHRIRs"
                virtualName="" explicitFocusOrder="0" pos="613 60 27 24" buttonText=""
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
                virtualName="" explicitFocusOrder="0" pos="411 60 22 24" buttonText=""
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
         virtualName="" explicitFocusOrder="0" pos="536 148 96 24" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e14d1c2e00d7849b" memberName="label_HRIR_len"
         virtualName="" explicitFocusOrder="0" pos="536 171 96 24" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f8b5274e0c8768f4" memberName="label_HRIR_fs"
         virtualName="" explicitFocusOrder="0" pos="536 194 96 24" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c59fb2aab2496c4e" memberName="label_DAW_fs"
         virtualName="" explicitFocusOrder="0" pos="536 217 96 24" outlineCol="68a3a2a2"
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
                virtualName="" explicitFocusOrder="0" pos="411 87 22 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="f65a4553b49a563a" memberName="TBtruncationEQ"
                virtualName="" explicitFocusOrder="0" pos="411 113 22 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="Hrir Pre-Processing" id="4708d72b820edbe6" memberName="CBhrirPreProc"
            virtualName="" explicitFocusOrder="0" pos="520 113 113 18" editable="0"
            layout="33" items="" textWhenNonSelected="Please Select" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

