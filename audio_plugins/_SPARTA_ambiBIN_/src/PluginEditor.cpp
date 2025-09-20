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
    TBuseDefaultHRIRs->setBounds (613, 60, 27, 24);

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
    TBmaxRE->setBounds (411, 60, 22, 24);

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
    label_N_dirs->setBounds (536, 148, 96, 24);

    label_HRIR_len.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_HRIR_len.get());
    label_HRIR_len->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Regular"));
    label_HRIR_len->setJustificationType (juce::Justification::centredLeft);
    label_HRIR_len->setEditable (false, false, false);
    label_HRIR_len->setBounds (536, 171, 96, 24);

    label_HRIR_fs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_HRIR_fs.get());
    label_HRIR_fs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Regular"));
    label_HRIR_fs->setJustificationType (juce::Justification::centredLeft);
    label_HRIR_fs->setEditable (false, false, false);
    label_HRIR_fs->setBounds (536, 194, 96, 24);

    label_DAW_fs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_DAW_fs.get());
    label_DAW_fs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle("Regular"));
    label_DAW_fs->setJustificationType (juce::Justification::centredLeft);
    label_DAW_fs->setEditable (false, false, false);
    label_DAW_fs->setBounds (536, 217, 96, 24);

    t_flipPitch = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipPitch");
    addAndMakeVisible (t_flipPitch.get());
    t_flipPitch->setButtonText (juce::String());
    t_flipPitch->setBounds (260, 209, 23, 24);

    t_flipRoll = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipRoll");
    addAndMakeVisible (t_flipRoll.get());
    t_flipRoll->setButtonText (juce::String());
    t_flipRoll->setBounds (376, 209, 23, 24);

    t_flipYaw = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipYaw");
    addAndMakeVisible (t_flipYaw.get());
    t_flipYaw->setButtonText (juce::String());
    t_flipYaw->setBounds (128, 209, 23, 24);

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
    TBdiffMatching->setBounds (411, 87, 22, 24);

    TBtruncationEQ = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "enableTruncationEQ");
    addAndMakeVisible (TBtruncationEQ.get());
    TBtruncationEQ->setButtonText (juce::String());
    TBtruncationEQ->setBounds (411, 113, 22, 24);

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
    if (std::unique_lock<std::mutex> reinitLock(processor.reinitManager.reinitMutex, std::try_to_lock); reinitLock.owns_lock()) {
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
                g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                           TRANS("/") + String(ambi_bin_getNSHrequired(hAmbi)) + TRANS(")"),
                           getBounds().getWidth()-225, 16, 530, 11,
                           Justification::centredLeft, true);
                break;
            case k_warning_NoutputCH:
                g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
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
}

void PluginEditor::resized()
{
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == TBuseDefaultHRIRs.get())
    {
        processor.updateQueue.push([this]() { ambi_bin_setUseDefaultHRIRsflag(hAmbi, (int)TBuseDefaultHRIRs->getToggleState()); });
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
    /* Only update if we can take the reinitialisation lock */
    if (std::unique_lock<std::mutex> reinitLock(processor.reinitManager.reinitMutex, std::try_to_lock); reinitLock.owns_lock()) {
        /* parameters whos values can change internally should be periodically refreshed */
        TBuseDefaultHRIRs->setToggleState(ambi_bin_getUseDefaultHRIRsflag(hAmbi), dontSendNotification);
        CBchFormat->setSelectedId(ambi_bin_getChOrder(hAmbi), sendNotification); // processor.getParameterChoice("")
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
        else if ( !((ambi_bin_getDAWsamplerate(hAmbi) == 44.1e3) || (ambi_bin_getDAWsamplerate(hAmbi) == 48e3)) ){
            currentWarning = k_warning_supported_fs;
            repaint(0,0,getWidth(),32);
        }
        else if (ambi_bin_getDAWsamplerate(hAmbi) != ambi_bin_getHRIRsamplerate(hAmbi)){
            currentWarning = k_warning_mismatch_fs;
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
        else if(currentWarning){
            currentWarning = k_warning_none;
            repaint(0,0,getWidth(),32);
        }
    }
    
    // TODO: Hitting occasional data races with getCodecStatus(), getProgressBar0_1(), getProgressBarText(). However, the MSVC C compiler does not yet support atomics
    
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
