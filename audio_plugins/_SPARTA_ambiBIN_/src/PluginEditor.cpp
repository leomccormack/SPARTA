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

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor(p), processor(p), progressbar(progress), fileChooser ("File", File(), true, false, false,
      "*.sofa;*.nc;", String(),
      "Load SOFA File")
{
    TBuseDefaultHRIRs.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBuseDefaultHRIRs.get());
    TBuseDefaultHRIRs->setButtonText (juce::String());
    TBuseDefaultHRIRs->addListener (this);
    TBuseDefaultHRIRs->setBounds (613, 60, 24, 24);

    CBorderPreset = std::make_unique<ComboBoxWithAttachment>(p.parameters, "inputOrder");
    addAndMakeVisible (CBorderPreset.get());
    CBorderPreset->setEditableText (false);
    CBorderPreset->setJustificationType (juce::Justification::centredLeft);
    CBorderPreset->setBounds (136, 63, 104, 18);

    CBchFormat = std::make_unique<ComboBoxWithAttachment>(p.parameters, "channelOrder");
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (juce::Justification::centredLeft);
    CBchFormat->setBounds (88, 116, 72, 18);

    CBnormScheme = std::make_unique<ComboBoxWithAttachment>(p.parameters, "normType");
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (juce::Justification::centredLeft);
    CBnormScheme->setBounds (164, 116, 76, 18);

    TBmaxRE = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "enableMaxRE");
    addAndMakeVisible (TBmaxRE.get());
    TBmaxRE->setButtonText (juce::String());
    TBmaxRE->setBounds (411, 60, 24, 24);

    s_yaw = std::make_unique<SliderWithAttachment>(p.parameters, "yaw");
    addAndMakeVisible (s_yaw.get());
    s_yaw->setSliderStyle (juce::Slider::LinearHorizontal);
    s_yaw->setTextBoxStyle (juce::Slider::TextBoxAbove, false, 80, 20);
    s_yaw->setBounds (80, 171, 120, 38);

    s_pitch = std::make_unique<SliderWithAttachment>(p.parameters, "pitch");
    addAndMakeVisible (s_pitch.get());
    s_pitch->setSliderStyle (juce::Slider::LinearVertical);
    s_pitch->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);
    s_pitch->setBounds (208, 137, 96, 112);

    s_roll = std::make_unique<SliderWithAttachment>(p.parameters, "roll");
    addAndMakeVisible (s_roll.get());
    s_roll->setSliderStyle (juce::Slider::LinearVertical);
    s_roll->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);
    s_roll->setBounds (328, 137, 96, 112);

    te_oscport.reset (new juce::TextEditor ("new text editor"));
    addAndMakeVisible (te_oscport.get());
    te_oscport->setMultiLine (false);
    te_oscport->setReturnKeyStartsNewLine (false);
    te_oscport->setReadOnly (false);
    te_oscport->setScrollbarsShown (true);
    te_oscport->setCaretVisible (false);
    te_oscport->setPopupMenuEnabled (true);
    te_oscport->setBounds (16, 227, 56, 18);

    label_N_dirs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_N_dirs.get());
    label_N_dirs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Regular"));
    label_N_dirs->setJustificationType (juce::Justification::centredLeft);
    label_N_dirs->setEditable (false, false, false);
    label_N_dirs->setBounds (566, 148, 66, 24);

    label_HRIR_len.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_HRIR_len.get());
    label_HRIR_len->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Regular"));
    label_HRIR_len->setJustificationType (juce::Justification::centredLeft);
    label_HRIR_len->setEditable (false, false, false);
    label_HRIR_len->setBounds (566, 171, 66, 24);

    label_HRIR_fs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_HRIR_fs.get());
    label_HRIR_fs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Regular"));
    label_HRIR_fs->setJustificationType (juce::Justification::centredLeft);
    label_HRIR_fs->setEditable (false, false, false);
    label_HRIR_fs->setBounds (566, 194, 66, 24);

    label_DAW_fs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_DAW_fs.get());
    label_DAW_fs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Regular"));
    label_DAW_fs->setJustificationType (juce::Justification::centredLeft);
    label_DAW_fs->setEditable (false, false, false);
    label_DAW_fs->setBounds (566, 217, 66, 24);

    t_flipPitch = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipPitch");
    addAndMakeVisible (t_flipPitch.get());
    t_flipPitch->setButtonText (juce::String());
    t_flipPitch->setBounds (260, 209, 24, 24);

    t_flipRoll = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipRoll");
    addAndMakeVisible (t_flipRoll.get());
    t_flipRoll->setButtonText (juce::String());
    t_flipRoll->setBounds (376, 209, 24, 24);

    t_flipYaw = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipYaw");
    addAndMakeVisible (t_flipYaw.get());
    t_flipYaw->setButtonText (juce::String());
    t_flipYaw->setBounds (128, 209, 24, 24);

    TBrpyFlag = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "useRollPitchYaw");
    addAndMakeVisible (TBrpyFlag.get());
    TBrpyFlag->setButtonText (juce::String());
    TBrpyFlag->setBounds (59, 187, 24, 24);

    TBenableRot = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "enableRotation");
    addAndMakeVisible (TBenableRot.get());
    TBenableRot->setButtonText (juce::String());
    TBenableRot->setBounds (59, 165, 24, 24);

    CBdecoderMethod = std::make_unique<ComboBoxWithAttachment>(p.parameters, "decMethod");
    addAndMakeVisible (CBdecoderMethod.get());
    CBdecoderMethod->setEditableText (false);
    CBdecoderMethod->setJustificationType (juce::Justification::centredLeft);
    CBdecoderMethod->setBounds (88, 90, 152, 18);

    TBdiffMatching = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "enableDiffuseMatching");
    addAndMakeVisible (TBdiffMatching.get());
    TBdiffMatching->setButtonText (juce::String());
    TBdiffMatching->setBounds (411, 87, 24, 24);

    TBtruncationEQ = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "enableTruncationEQ");
    addAndMakeVisible (TBtruncationEQ.get());
    TBtruncationEQ->setButtonText (juce::String());
    TBtruncationEQ->setBounds (411, 113, 24, 24);

    CBhrirPreProc = std::make_unique<ComboBoxWithAttachment>(p.parameters, "hrirPreproc");
    addAndMakeVisible (CBhrirPreProc.get());
    CBhrirPreProc->setEditableText (false);
    CBhrirPreProc->setJustificationType (juce::Justification::centredLeft);
    CBhrirPreProc->setBounds (520, 113, 113, 18);

    setSize (656, 262);

    /* handles */
    hAmbi = processor.getFXHandle();

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    setLookAndFeel(&LAF);

    /* file loader */
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
    fileChooser.setBounds (452, 86, 181, 20);
    StringArray filenames;
    filenames.add("/Spatial_Audio_Framework/Default");
    filenames.add(ambi_bin_getSofaFilePath(hAmbi));
    fileChooser.setRecentlyUsedFilenames(filenames);
    fileChooser.setFilenameIsEditable(true);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setVisible(false);

    /* grab current parameter settings */
    TBuseDefaultHRIRs->setToggleState(ambi_bin_getUseDefaultHRIRsflag(hAmbi), dontSendNotification);
    te_oscport->setText(String(processor.getOscPortID()), dontSendNotification);
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
    startTimer(20);

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    stopTimer();
    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    using namespace ColoursUI;

    /* Background gradients */
    drawVerticalGradient(g, {0, 146, getWidth(), 116}, bgDark2, bgDark1);
    drawVerticalGradient(g, {0,  30, getWidth(), 116}, bgDark1, bgDark2);
    
    /* Borders */
    g.setColour(juce::Colour(0xffb9b9b9));
    g.drawRect({0, 0, 656, 2}, 2);
    g.drawRect({654, 0, 2, 262}, 2);
    g.drawRect({0, 0, 2, 262}, 2);
    g.drawRect({0, 260, 656, 2}, 2);

    /* Top rounded bar */
    {
        juce::Rectangle<float> r { 1.f, 2.f, 654.f, 31.f };
        g.setGradientFill(juce::ColourGradient(bgDark2, r.getX(), r.getBottom(),
                                               bgDark1, r.getRight(), r.getY(), false));
        g.fillRoundedRectangle(r, 5.f);
        g.setColour(juce::Colour(0xffb9b9b9));
        g.drawRoundedRectangle(r, 5.f, 2.f);
    }

    /* Panels */
    drawPanel(g, {12,  58, 237,  82}, panelFill, panelStroke);
    drawPanel(g, {12,  58, 237,  29}, panelFillLight, panelStrokeLight);
    drawPanel(g, {12, 139, 424, 112}, panelFill, panelStroke);
    drawPanel(g, {12, 164,  73,  87}, panelFillLight, panelStrokeLight);
    drawPanel(g, {248, 58, 188, 82}, panelFill, panelStroke);
    drawPanel(g, {445, 58, 196, 82}, panelFill, panelStroke);
    drawPanel(g, {445,139, 196,112}, panelFill, panelStroke);

    /* Labels */
    drawLabel(g, {164, 32, 149, 30}, "Decoding Settings", 15.f);
    drawLabel(g, {520, 32, 113, 30}, "Output", 15.f);
    drawLabel(g, {451, 56, 157, 30}, "Use Default HRIR set:", 15.f);
    drawLabel(g, {19,  57, 141, 30}, "Decoding Order:", 14.5f);
    drawLabel(g, {19, 109, 132, 30}, "Format:", 14.5f);
    drawLabel(g, {19, 136, 133, 30}, "Rotation", 15.f);
    drawLabel(g, {19,  84, 125, 30}, "Method:", 14.5f);
    drawLabel(g, {254,  57, 185, 30}, "Apply MaxRE Weights:", 14.5f);
    drawLabel(g, {254,  84, 185, 30}, "Diffuse Cov. Constraint:", 14.5f);
    drawLabel(g, {254,  109, 185, 30}, "Apply Truncation EQ:", 14.5f);
    drawLabel(g, {451,  106, 83, 30}, "Pre-Proc:", 14.5f);

    /* YPR labels */
    drawLabel(g, {93, 145, 60, 30}, "Yaw", 15.f, juce::Justification::centred);
    drawLabel(g, {125,145,63, 30}, "\\ypr[0]", 11.f, juce::Justification::centred);
    drawLabel(g, {223,145,63, 30}, "Pitch", 15.f, juce::Justification::centred);
    drawLabel(g, {261,145,63, 30}, "\\ypr[1]", 11.f, juce::Justification::centred);
    drawLabel(g, {341,145,63, 30}, "Roll", 15.f, juce::Justification::centred);
    drawLabel(g, {373,145,63, 30}, "\\ypr[2]", 11.f, juce::Justification::centred);
    drawLabel(g, {355, 225, 63, 24}, "+/-", 15.f, juce::Justification::centred);
    drawLabel(g, {240, 225, 63, 27}, "+/-", 15.f, juce::Justification::centred);
    drawLabel(g, {109, 225, 63, 27}, "+/-", 15.f, juce::Justification::centred);

    /* Other labels */
    drawLabel(g, {452,144,132,30}, "Num Directions:", 13.f);
    drawLabel(g, {452,168,132,30}, "HRIR Length:", 13.f);
    drawLabel(g, {452,192,132,30}, "HRIR Samplerate:", 13.f);
    drawLabel(g, {452,216,132,30}, "DAW Samplerate:", 13.f);
    drawLabel(g, {19, 208, 63, 23}, "OSC port:", 11.f);
    drawLabel(g, {19, 188, 63, 23}, "R-P-Y:", 11.f);
    drawLabel(g, {19, 166, 61, 23}, "Enable:", 11.f);

    /* Title */
    drawLabel(g, {16, 1, 196, 32}, "SPARTA|", 18.f);
    drawLabel(g, {92, 1, 184, 32}, "AmbiBIN", 18.f, juce::Justification::centredLeft, accentOrange);

    g.setColour(Colours::white);
    g.setFont(juce::FontOptions (11.00f, juce::Font::plain));
    g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
        185, 16, 530, 11,
        Justification::centredLeft, true);

    /* display warning message */
    g.setFont(juce::FontOptions (11.00f, juce::Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.setColour(Colours::red);
            g.drawText(TRANS("Set frame size to multiple of ") + String(ambi_bin_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(ambi_bin_getNSHrequired(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
                       TRANS("/") + String(ambi_bin_getNumEars()) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_osc_connection_fail:
            g.setColour(Colours::red);
            g.drawText(TRANS("Failed to connect to the selected OSC port"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.setColour(Colours::yellow);
            g.drawText(TRANS("Sample rate \"") + String(ambi_bin_getDAWsamplerate(hAmbi)) + TRANS("\" is not recommended"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_mismatch_fs:
            g.setColour(Colours::yellow);
            g.drawText(TRANS("Resampled HRIRs to match host samplerate"),
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
}

void PluginEditor::comboBoxChanged (juce::ComboBox* /*comboBoxThatHasChanged*/)
{
}

void PluginEditor::sliderValueChanged (juce::Slider* /*sliderThatWasMoved*/)
{
}

void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    TBuseDefaultHRIRs->setToggleState(ambi_bin_getUseDefaultHRIRsflag(hAmbi), dontSendNotification);
    CBchFormat->setSelectedId(ambi_bin_getChOrder(hAmbi), sendNotification);
    CBnormScheme->setSelectedId(ambi_bin_getNormType(hAmbi), sendNotification);
    label_N_dirs->setText(String(ambi_bin_getNDirs(hAmbi)), dontSendNotification);
    label_HRIR_len->setText(String(ambi_bin_getHRIRlength(hAmbi)), dontSendNotification);
    label_HRIR_fs->setText(String(ambi_bin_getHRIRsamplerate(hAmbi)), dontSendNotification);
    label_DAW_fs->setText(String(ambi_bin_getDAWsamplerate(hAmbi)), dontSendNotification);
    CBchFormat->setItemEnabled(CH_FUMA, ambi_bin_getInputOrderPreset(hAmbi)==SH_ORDER_FIRST ? true : false);
    CBnormScheme->setItemEnabled(NORM_FUMA, ambi_bin_getInputOrderPreset(hAmbi)==SH_ORDER_FIRST ? true : false);
    
    /* display warning message, if needed */
    if ((processor.getCurrentBlockSize() % ambi_bin_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumInputs() < ambi_bin_getNSHrequired(hAmbi))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumOutputs() < ambi_bin_getNumEars())){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(!processor.getOscPortConnected() && ambi_bin_getEnableRotation(hAmbi)){
        currentWarning = k_warning_osc_connection_fail;
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
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
        
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
    
    /* check if OSC port has changed */
    if(processor.getOscPortID() != te_oscport->getText().getIntValue())
        processor.setOscPortID(te_oscport->getText().getIntValue());
}
