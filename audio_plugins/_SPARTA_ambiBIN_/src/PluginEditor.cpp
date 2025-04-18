/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2018 - Leo McCormack.
 
 SPARTA is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 SPARTA is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with SPARTA.  If not, see <http://www.gnu.org/licenses/>.
 
 ==============================================================================
*/

#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter), progressbar(progress), fileChooser ("File", File(), true, false, false,
      "*.sofa;*.nc;", String(),
      "Load SOFA File")
{
    TBuseDefaultHRIRs.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBuseDefaultHRIRs.get());
    TBuseDefaultHRIRs->setButtonText (juce::String());
    TBuseDefaultHRIRs->addListener (this);

    TBuseDefaultHRIRs->setBounds (613, 60, 27, 24);

    CBorderPreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBorderPreset.get());
    CBorderPreset->setEditableText (false);
    CBorderPreset->setJustificationType (juce::Justification::centredLeft);
    CBorderPreset->setTextWhenNothingSelected (TRANS ("Default"));
    CBorderPreset->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBorderPreset->addListener (this);

    CBorderPreset->setBounds (136, 63, 104, 18);

    CBchFormat.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (juce::Justification::centredLeft);
    CBchFormat->setTextWhenNothingSelected (TRANS ("ACN"));
    CBchFormat->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBchFormat->addListener (this);

    CBchFormat->setBounds (88, 116, 72, 18);

    CBnormScheme.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (juce::Justification::centredLeft);
    CBnormScheme->setTextWhenNothingSelected (TRANS ("N3D"));
    CBnormScheme->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
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

    label_N_dirs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Regular"));
    label_N_dirs->setJustificationType (juce::Justification::centredLeft);
    label_N_dirs->setEditable (false, false, false);
    label_N_dirs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_N_dirs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_N_dirs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_N_dirs->setBounds (536, 148, 96, 24);

    label_HRIR_len.reset (new juce::Label ("new label",
                                           juce::String()));
    addAndMakeVisible (label_HRIR_len.get());
    label_HRIR_len->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Regular"));
    label_HRIR_len->setJustificationType (juce::Justification::centredLeft);
    label_HRIR_len->setEditable (false, false, false);
    label_HRIR_len->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_HRIR_len->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_HRIR_len->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_HRIR_len->setBounds (536, 171, 96, 24);

    label_HRIR_fs.reset (new juce::Label ("new label",
                                          juce::String()));
    addAndMakeVisible (label_HRIR_fs.get());
    label_HRIR_fs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Regular"));
    label_HRIR_fs->setJustificationType (juce::Justification::centredLeft);
    label_HRIR_fs->setEditable (false, false, false);
    label_HRIR_fs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_HRIR_fs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_HRIR_fs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_HRIR_fs->setBounds (536, 194, 96, 24);

    label_DAW_fs.reset (new juce::Label ("new label",
                                         juce::String()));
    addAndMakeVisible (label_DAW_fs.get());
    label_DAW_fs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Regular"));
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
    CBdecoderMethod->setTextWhenNothingSelected (TRANS ("Default"));
    CBdecoderMethod->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
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
    CBhrirPreProc->setTextWhenNothingSelected (TRANS ("Please Select"));
    CBhrirPreProc->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBhrirPreProc->addListener (this);

    CBhrirPreProc->setBounds (520, 113, 113, 18);

    setSize (656, 262);

    /* handles */
	hVst = ownerFilter;
    hAmbi = hVst->getFXHandle();

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

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
    CBorderPreset->addItem (TRANS("8th order"), SH_ORDER_EIGHTH);
    CBorderPreset->addItem (TRANS("9th order"), SH_ORDER_NINTH);
    CBorderPreset->addItem (TRANS("10th order"), SH_ORDER_TENTH);
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
    CBdecoderMethod->setTooltip("'Least-squares' is the simplest option, but it can give strong colourations at lower-orders; which can (perhaps counter-intuitively) become worse as more HRIR measurements are used to compute the decoder, since more high-frequency energy is assigned to ever higher orders and lost due to the order truncation. \"Diffuse-field EQ\" applied in the spherical harmonic domain helps mitigate this problem, as does toggling on \"Apply Truncation EQ\". On the other hand, Spatial resampling (SPR), which is similar to what is known as the virtual loudspeaker approach (using a subset of the HRIR measurements), will also mitigate this colouration problem as it will \"alias\" the energy of higher-order components back into the lower-order components (instead of loosing this energy to order truncation). \n\nMore perceptually-motivated decoding options, which also aim to improve the spatial performance of the decoding, are the Time-alignment (TA) or Magnitude-LS decoding options. In a nutshell, they aim to exploit the knowledge that humans are not very sensitive to interaural time differences (ITDs) at high frequencies (~1.5kHz; as described by the Duplex theory); instead prioritising fitting the Ambisonic patterns to only the magnitudes of the HRTFs at these frequencies - leading to a reduction in interaural level differences (ILDs) errors. \n\nHowever! Note that this plug-in already does some pre-processing of the HRIRs before computing the binaural decoders, in particular the \"Phase Simplication\" option is linearising the phase of the HRTFs, which also helps steer the least-squares solution towards better matching the magnitude responses of the HRTFs. Therefore, try disabling this option if you want to listen to the different decoders as they would have sounded in their original publication evaluations.\n\nNote also that the Time-alignment (TA) decoder is without the diffuse-covariance constraint (TAC) that was also proposed in the original paper. Instead this constraint is provided as it's own toggle button (\"Apply Cov. Constriant\") and can therefore be applied to any decoding method.");
    TBuseDefaultHRIRs->setTooltip("If this is 'ticked', the plug-in is using the default HRIR set from the Spatial_Audio_Framework. Otherwise, the plugin will use the HRIRs found in the provided SOFA file.");
    fileChooser.setTooltip("Optionally, a custom HRIR set may be loaded via the SOFA standard. Note that if the plug-in fails to load the specified .sofa file, it will revert to the default HRIR data.");
    CBchFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormScheme->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    CBorderPreset->setTooltip("Decoding order. Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals as input.");
    TBmaxRE->setTooltip("Enables/Disables the max_rE weights applied to the decoding matrix. Much like with loudspeaker decoding, the spatial \"tapering\" attained by applying these maxRE weights will lead to sources becoming a bit more \"spread\", but also mitigating the problem of some source energy being routed to the opposite side of the sphere.");
    TBdiffMatching->setTooltip("Enables/Disables the diffuse covariance constraint applied to the decoding matrix. This is the 'C' part of the 'TAC' decoder. However, in this plug-in, it is given as a separate option so it can be applied to any of the available decoding methods. \n\nNote, this is not the same as applying diffuse-field EQ on the HRIRs; this is more of a \"spatial\" manipulation and not a timbral one. \n\nAlso note that, while it may make recordings sound broader/wider at lower-orders, it does so at the cost of distorting the spatial properties of the recording (usually pushing energy to the sides: almost akin to stereo-widening); therefore, we believe that this effect should not be enabled by default. However, it can indeed sound good in some cases... so the option is still here.");
    TBtruncationEQ->setTooltip("Applies an EQ that counteracts the high frequency loss induced by order truncation. This is an alternative to the \"Ambi-Diff-EQ\", but it is only suitable to apply this on the \"Least-Squares\" decoder and without the \"phase-simplification\" pre-processing applied to the HRIRs.");
    CBhrirPreProc->setTooltip("Pre-processing options for the HRIRs. Diffuse-field EQ is based on a weighted summation of all the HRTF magnitudes in the currently loaded set (i.e., removing the common/direction-independent filtering of the HRTFs). The phase-simplification involves estimating the ITDs for all the HRIRs, removing the phase from the HRTFs, but then re-introducing the phase as IPDs per frequency-bin. Note that this phase-simplification significantly helps when computing the least-squares fitting of the spherical harmonics to the HRTFs; on the same lines as what the TA and MagLS decoding options aim to do more explicitly. Disabling the phase simplification will result in more drastic differences between the different decoding methods.");
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
    pluginDescription->setTooltip(TRANS("This plug-in is a linear and time-invariant binaural Ambisonic decoder, which implements a number of different decoder designs and processing \"tricks\". \n\nAs with most of the SPARTA plugins, the default settings generally represent the \"state-of-the-art\"/recommended approach; or at least a configuration that is suitable for the majority of applications. The vast number of configuration options and decoding methods offered by this plug-in are mainly intended for research and educational purposes, but may nevertheless be fun to play around with :-)\n\nNote that all of the configuration options have detailed tooltips, and more information about them may be found in the references stated in the saf_hoa module of the Spatial_Audio_Framework."));

	/* Specify screen refresh rate */
    startTimer(TIMER_GUI_RELATED, 20);

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
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

    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 146, width = 656, height = 116;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
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
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 58, width = 237, height = 29;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x35a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 139, width = 424, height = 112;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 164, width = 73, height = 87;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x3aa0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 248, y = 58, width = 188, height = 82;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 445, y = 58, width = 196, height = 82;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 164, y = 32, width = 149, height = 30;
        juce::String text (TRANS ("Decoding Settings"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 520, y = 32, width = 113, height = 30;
        juce::String text (TRANS ("Output"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 451, y = 56, width = 157, height = 30;
        juce::String text (TRANS ("Use Default HRIR set:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 57, width = 141, height = 30;
        juce::String text (TRANS ("Decoding Order:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 109, width = 132, height = 30;
        juce::String text (TRANS ("Format:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 136, width = 133, height = 30;
        juce::String text (TRANS ("Rotation"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 84, width = 125, height = 30;
        juce::String text (TRANS ("Method:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 125, y = 145, width = 63, height = 30;
        juce::String text (TRANS ("\\ypr[0]"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 223, y = 145, width = 63, height = 30;
        juce::String text (TRANS ("Pitch"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 341, y = 145, width = 63, height = 30;
        juce::String text (TRANS ("Roll"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 355, y = 225, width = 63, height = 24;
        juce::String text (TRANS ("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 240, y = 225, width = 63, height = 27;
        juce::String text (TRANS ("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 109, y = 225, width = 63, height = 27;
        juce::String text (TRANS ("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 93, y = 145, width = 60, height = 30;
        juce::String text (TRANS ("Yaw"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 261, y = 145, width = 63, height = 30;
        juce::String text (TRANS ("\\ypr[1]"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 373, y = 145, width = 63, height = 30;
        juce::String text (TRANS ("\\ypr[2]"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 445, y = 139, width = 196, height = 112;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 452, y = 144, width = 132, height = 30;
        juce::String text (TRANS ("Num dirs:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 452, y = 168, width = 132, height = 30;
        juce::String text (TRANS ("HRIR length:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 452, y = 192, width = 132, height = 30;
        juce::String text (TRANS ("HRIR fs:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 208, width = 63, height = 23;
        juce::String text (TRANS ("OSC port:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 659, y = -15, width = 80, height = 30;
        juce::String text (TRANS ("Comp. EQ:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 188, width = 63, height = 23;
        juce::String text (TRANS ("R-P-Y:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 166, width = 61, height = 23;
        juce::String text (TRANS ("Enable:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 1, width = 196, height = 32;
        juce::String text (TRANS ("SPARTA|"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 92, y = 1, width = 184, height = 32;
        juce::String text (TRANS ("AmbiBIN"));
        juce::Colour fillColour = juce::Colour (0xffdf8400);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 254, y = 57, width = 185, height = 30;
        juce::String text (TRANS ("Apply MaxRE Weights:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 254, y = 84, width = 185, height = 30;
        juce::String text (TRANS ("Diffuse Cov. Constraint:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 254, y = 109, width = 185, height = 30;
        juce::String text (TRANS ("Apply Truncation EQ: "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 656, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 654, y = 0, width = 2, height = 262;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 262;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 260, width = 656, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 451, y = 106, width = 83, height = 30;
        juce::String text (TRANS ("Pre-Proc:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 452, y = 216, width = 132, height = 30;
        juce::String text (TRANS ("DAW fs:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

	g.setColour(Colours::white);
	g.setFont(juce::FontOptions (11.00f, juce::Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		185, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions (11.00f, juce::Font::plain));
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
}

void PluginEditor::resized()
{
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == TBuseDefaultHRIRs.get())
    {
        ambi_bin_setUseDefaultHRIRsflag(hAmbi, (int)TBuseDefaultHRIRs->getToggleState());
    }
    else if (buttonThatWasClicked == TBmaxRE.get())
    {
        ambi_bin_setEnableMaxRE(hAmbi, (int)TBmaxRE->getToggleState());
    }
    else if (buttonThatWasClicked == t_flipPitch.get())
    {
        ambi_bin_setFlipPitch(hAmbi, (int)t_flipPitch->getToggleState());
    }
    else if (buttonThatWasClicked == t_flipRoll.get())
    {
        ambi_bin_setFlipRoll(hAmbi, (int)t_flipRoll->getToggleState());
    }
    else if (buttonThatWasClicked == t_flipYaw.get())
    {
        ambi_bin_setFlipYaw(hAmbi, (int)t_flipYaw->getToggleState());
    }
    else if (buttonThatWasClicked == TBcompEQ.get())
    {
        // TODO: is this supposed to link to something?
    }
    else if (buttonThatWasClicked == TBrpyFlag.get())
    {
        ambi_bin_setRPYflag(hAmbi, (int)TBrpyFlag->getToggleState());
    }
    else if (buttonThatWasClicked == TBenableRot.get())
    {
        ambi_bin_setEnableRotation(hAmbi, (int)TBenableRot->getToggleState());
    }
    else if (buttonThatWasClicked == TBdiffMatching.get())
    {
        ambi_bin_setEnableDiffuseMatching(hAmbi, (int)TBdiffMatching->getToggleState());
    }
    else if (buttonThatWasClicked == TBtruncationEQ.get())
    {
        ambi_bin_setEnableTruncationEQ(hAmbi, (int)TBtruncationEQ->getToggleState());
    }
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == CBorderPreset.get())
    {
        ambi_bin_setInputOrderPreset(hAmbi, (SH_ORDERS)CBorderPreset->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBchFormat.get())
    {
        ambi_bin_setChOrder(hAmbi, CBchFormat->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBnormScheme.get())
    {
        ambi_bin_setNormType(hAmbi, CBnormScheme->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBdecoderMethod.get())
    {
        ambi_bin_setDecodingMethod(hAmbi, (AMBI_BIN_DECODING_METHODS)CBdecoderMethod->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBhrirPreProc.get())
    {
        ambi_bin_setHRIRsPreProc(hAmbi, (AMBI_BIN_PREPROC)CBhrirPreProc->getSelectedId());
    }
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == s_yaw.get())
    {
        ambi_bin_setYaw(hAmbi, (float)s_yaw->getValue());
    }
    else if (sliderThatWasMoved == s_pitch.get())
    {
        ambi_bin_setPitch(hAmbi, (float)s_pitch->getValue());
    }
    else if (sliderThatWasMoved == s_roll.get())
    {
        ambi_bin_setRoll(hAmbi, (float)s_roll->getValue());
    }
}

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
