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
    CBsourceDirsPreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBsourceDirsPreset.get());
    CBsourceDirsPreset->setEditableText (false);
    CBsourceDirsPreset->setJustificationType (juce::Justification::centredLeft);
    CBsourceDirsPreset->setTextWhenNothingSelected (juce::String());
    CBsourceDirsPreset->addListener (this);
    CBsourceDirsPreset->setBounds (88, 66, 112, 20);

    SL_num_sources = std::make_unique<SliderWithAttachment>(p.parameters, "numSources");
    addAndMakeVisible (SL_num_sources.get());
    SL_num_sources->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_sources->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_sources->addListener (this);
    SL_num_sources->setBounds (152, 94, 48, 20);

    label_N_dirs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_N_dirs.get());
    label_N_dirs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_N_dirs->setJustificationType (juce::Justification::centredLeft);
    label_N_dirs->setEditable (false, false, false);
    label_N_dirs->setBounds (799, 140, 51, 20);

    label_HRIR_fs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_HRIR_fs.get());
    label_HRIR_fs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_HRIR_fs->setJustificationType (juce::Justification::centredLeft);
    label_HRIR_fs->setEditable (false, false, false);
    label_HRIR_fs->setBounds (799, 164, 51, 20);

    TBuseDefaultHRIRs.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBuseDefaultHRIRs.get());
    TBuseDefaultHRIRs->setButtonText (juce::String());
    TBuseDefaultHRIRs->addListener (this);
    TBuseDefaultHRIRs->setBounds (876, 61, 32, 24);

    label_DAW_fs.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_DAW_fs.get());
    label_DAW_fs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_DAW_fs->setJustificationType (juce::Justification::centredLeft);
    label_DAW_fs->setEditable (false, false, false);
    label_DAW_fs->setBounds (853, 164, 51, 20);

    TB_showInputs.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_showInputs.get());
    TB_showInputs->setButtonText (juce::String());
    TB_showInputs->addListener (this);
    TB_showInputs->setBounds (550, 322, 24, 24);

    TB_showOutputs.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_showOutputs.get());
    TB_showOutputs->setButtonText (juce::String());
    TB_showOutputs->addListener (this);
    TB_showOutputs->setBounds (672, 322, 24, 24);

    label_N_Tri.reset (new juce::Label ("new label", juce::String()));
    addAndMakeVisible (label_N_Tri.get());
    label_N_Tri->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_N_Tri->setJustificationType (juce::Justification::centredLeft);
    label_N_Tri->setEditable (false, false, false);
    label_N_Tri->setBounds (853, 140, 51, 20);

    CBinterpMode = std::make_unique<ComboBoxWithAttachment>(p.parameters, "interpMode");
    addAndMakeVisible (CBinterpMode.get());
    CBinterpMode->setEditableText (false);
    CBinterpMode->setJustificationType (juce::Justification::centredLeft);
    CBinterpMode->setBounds (316, 324, 125, 20);

    tb_loadJSON.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_loadJSON.get());
    tb_loadJSON->setButtonText (TRANS ("Import"));
    tb_loadJSON->setConnectedEdges (juce::Button::ConnectedOnRight);
    tb_loadJSON->addListener (this);
    tb_loadJSON->setBounds (140, 40, 34, 14);

    tb_saveJSON.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON.get());
    tb_saveJSON->setButtonText (TRANS ("Export"));
    tb_saveJSON->setConnectedEdges (juce::Button::ConnectedOnLeft);
    tb_saveJSON->addListener (this);
    tb_saveJSON->setBounds (174, 40, 34, 14);

    s_yaw = std::make_unique<SliderWithAttachment>(p.parameters, "yaw");
    addAndMakeVisible (s_yaw.get());
    s_yaw->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_yaw->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 15);
    s_yaw->setBounds (717, 260, 60, 68);

    s_pitch = std::make_unique<SliderWithAttachment>(p.parameters, "pitch");
    addAndMakeVisible (s_pitch.get());
    s_pitch->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_pitch->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 15);
    s_pitch->setBounds (780, 260, 60, 68);

    s_roll = std::make_unique<SliderWithAttachment>(p.parameters, "roll");
    addAndMakeVisible (s_roll.get());
    s_roll->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_roll->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 15);
    s_roll->setBounds (843, 260, 60, 68);

    t_flipYaw = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipYaw");
    addAndMakeVisible (t_flipYaw.get());
    t_flipYaw->setBounds (749, 329, 23, 24);

    t_flipPitch = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipPitch");
    addAndMakeVisible (t_flipPitch.get());
    t_flipPitch->setBounds (812, 329, 23, 24);

    t_flipRoll = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipRoll");
    addAndMakeVisible (t_flipRoll.get());
    t_flipRoll->setBounds (875, 329, 23, 24);

    te_oscport.reset (new juce::TextEditor ("new text editor"));
    addAndMakeVisible (te_oscport.get());
    te_oscport->setMultiLine (false);
    te_oscport->setReturnKeyStartsNewLine (false);
    te_oscport->setReadOnly (false);
    te_oscport->setScrollbarsShown (true);
    te_oscport->setCaretVisible (false);
    te_oscport->setPopupMenuEnabled (true);
    te_oscport->setText (TRANS ("9000"));
    te_oscport->setBounds (848, 216, 44, 22);

    TBrpyFlag = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "useRollPitchYaw");
    addAndMakeVisible (TBrpyFlag.get());
    TBrpyFlag->setButtonText (juce::String());
    TBrpyFlag->setBounds (752, 216, 32, 24);

    TBenableRotation = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "enableRotation");
    addAndMakeVisible (TBenableRotation.get());
    TBenableRotation->setButtonText (juce::String());
    TBenableRotation->setBounds (832, 190, 32, 24);

    TBenablePreProc = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "enableDiffuseEQ");
    addAndMakeVisible (TBenablePreProc.get());
    TBenablePreProc->setTooltip (TRANS ("Enable HRIR Pre-Processing"));
    TBenablePreProc->setButtonText (juce::String());
    TBenablePreProc->setBounds (876, 109, 32, 24);

    setSize (920, 362);

    /* handle to object */
    hBin = processor.getFXHandle();

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_num_sources->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_sources->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_sources->setSliderSnapsToMousePosition(false);

    /* add source preset options */
    if(processor.wrapperType == AudioProcessor::wrapperType_AAX){
        CBsourceDirsPreset->addItem (TRANS("ProTools Stereo"), SOURCE_CONFIG_PRESET_PROTOOLS_STEREO);
        CBsourceDirsPreset->addItem (TRANS("ProTools LCR"), SOURCE_CONFIG_PRESET_PROTOOLS_LCR);
        CBsourceDirsPreset->addItem (TRANS("ProTools Quad"), SOURCE_CONFIG_PRESET_PROTOOLS_QUAD);
        CBsourceDirsPreset->addItem (TRANS("ProTools 5.0"), SOURCE_CONFIG_PRESET_PROTOOLS_5_0);
        CBsourceDirsPreset->addItem (TRANS("ProTools 5.0.2"), SOURCE_CONFIG_PRESET_PROTOOLS_5_0_2);
        CBsourceDirsPreset->addItem (TRANS("ProTools 5.0.4"), SOURCE_CONFIG_PRESET_PROTOOLS_5_0_4);
        CBsourceDirsPreset->addItem (TRANS("ProTools 7.0"), SOURCE_CONFIG_PRESET_PROTOOLS_7_0);
        CBsourceDirsPreset->addItem (TRANS("ProTools 7.0.2"), SOURCE_CONFIG_PRESET_PROTOOLS_7_0_2);
        CBsourceDirsPreset->addItem (TRANS("ProTools 7.0.4"), SOURCE_CONFIG_PRESET_PROTOOLS_7_0_4);
        CBsourceDirsPreset->addItem (TRANS("ProTools 7.0.6"), SOURCE_CONFIG_PRESET_PROTOOLS_7_0_6);
        CBsourceDirsPreset->addItem (TRANS("ProTools 9.0.4"), SOURCE_CONFIG_PRESET_PROTOOLS_9_0_4);
        CBsourceDirsPreset->addItem (TRANS("ProTools 9.0.6"), SOURCE_CONFIG_PRESET_PROTOOLS_9_0_6);
    }
    CBsourceDirsPreset->addItem (TRANS("Mono"), SOURCE_CONFIG_PRESET_MONO);
    CBsourceDirsPreset->addItem (TRANS("Stereo"), SOURCE_CONFIG_PRESET_STEREO);
    CBsourceDirsPreset->addItem (TRANS("5.x"), SOURCE_CONFIG_PRESET_5PX);
    CBsourceDirsPreset->addItem (TRANS("7.x"), SOURCE_CONFIG_PRESET_7PX);
    CBsourceDirsPreset->addItem (TRANS("8.x"), SOURCE_CONFIG_PRESET_8PX);
    CBsourceDirsPreset->addItem (TRANS("9.x"), SOURCE_CONFIG_PRESET_9PX);
    CBsourceDirsPreset->addItem (TRANS("10.x"), SOURCE_CONFIG_PRESET_10PX);
    CBsourceDirsPreset->addItem (TRANS("11.x"), SOURCE_CONFIG_PRESET_11PX);
    CBsourceDirsPreset->addItem (TRANS("11.x (7+4)"), SOURCE_CONFIG_PRESET_11PX_7_4);
    CBsourceDirsPreset->addItem (TRANS("13.x"), SOURCE_CONFIG_PRESET_13PX);
    CBsourceDirsPreset->addItem (TRANS("22.x"), SOURCE_CONFIG_PRESET_22PX);
    CBsourceDirsPreset->addItem (TRANS("9+10+3.2"), SOURCE_CONFIG_PRESET_22P2_9_10_3);
    CBsourceDirsPreset->addItem (TRANS("Aalto MCC"), SOURCE_CONFIG_PRESET_AALTO_MCC);
    CBsourceDirsPreset->addItem (TRANS("Aalto MCC-subset"), SOURCE_CONFIG_PRESET_AALTO_MCC_SUBSET);
    CBsourceDirsPreset->addItem (TRANS("Aalto Apaja"), SOURCE_CONFIG_PRESET_AALTO_APAJA);
    CBsourceDirsPreset->addItem (TRANS("Aalto LR"), SOURCE_CONFIG_PRESET_AALTO_LR);
    CBsourceDirsPreset->addItem (TRANS("DTU AVIL"), SOURCE_CONFIG_PRESET_DTU_AVIL);
    CBsourceDirsPreset->addItem (TRANS("Zylia Lab (22.x)"), SOURCE_CONFIG_PRESET_ZYLIA_LAB);
    CBsourceDirsPreset->addItem (TRANS("T-design (4)"), SOURCE_CONFIG_PRESET_T_DESIGN_4);
    CBsourceDirsPreset->addItem (TRANS("T-design (12)"), SOURCE_CONFIG_PRESET_T_DESIGN_12);
    CBsourceDirsPreset->addItem (TRANS("T-design (24)"), SOURCE_CONFIG_PRESET_T_DESIGN_24);
    CBsourceDirsPreset->addItem (TRANS("T-design (36)"), SOURCE_CONFIG_PRESET_T_DESIGN_36);
    CBsourceDirsPreset->addItem (TRANS("T-design (48)"), SOURCE_CONFIG_PRESET_T_DESIGN_48);
    CBsourceDirsPreset->addItem (TRANS("T-design (60)"), SOURCE_CONFIG_PRESET_T_DESIGN_60);
    CBsourceDirsPreset->addItem (TRANS("SphCov (9)"), SOURCE_CONFIG_PRESET_SPH_COV_9);
    CBsourceDirsPreset->addItem (TRANS("SphCov (16)"), SOURCE_CONFIG_PRESET_SPH_COV_16);
    CBsourceDirsPreset->addItem (TRANS("SphCov (25)"), SOURCE_CONFIG_PRESET_SPH_COV_25);
    CBsourceDirsPreset->addItem (TRANS("SphCov (49)"), SOURCE_CONFIG_PRESET_SPH_COV_49);
    CBsourceDirsPreset->addItem (TRANS("SphCov (64)"), SOURCE_CONFIG_PRESET_SPH_COV_64);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);

    /* source coordinate viewport */
    sourceCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (sourceCoordsVP.get());
    sourceCoordsView_handle = new inputCoordsView(p, MAX_NUM_INPUTS, binauraliser_getNumSources(hBin));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(22, 153, 184, 180);
    sourceCoordsView_handle->setNCH(binauraliser_getNumSources(hBin));

    /* file loader */
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
    fileChooser.setBounds (719, 87, 182, 20);
    StringArray filenames;
    filenames.add("/Spatial_Audio_Framework/Default");
    filenames.add(binauraliser_getSofaFilePath(hBin));
    fileChooser.setRecentlyUsedFilenames(filenames);
    fileChooser.setFilenameIsEditable(true);

    /* grab current parameter settings */
    TBuseDefaultHRIRs->setToggleState(binauraliser_getUseDefaultHRIRsflag(hBin), dontSendNotification);
    TB_showInputs->setToggleState(true, dontSendNotification);
    TB_showOutputs->setToggleState(false, dontSendNotification);
    te_oscport->setText(String(processor.getOscPortID()), dontSendNotification);

    /* create panning window */
    panWindow.reset (new pannerView(p, 492, 246));
    addAndMakeVisible (panWindow.get());
    panWindow->setBounds (214, 58, 492, 246);
    panWindow->setShowInputs(TB_showInputs->getToggleState());
    panWindow->setShowOutputs(TB_showOutputs->getToggleState());
    refreshPanViewWindow = true;

    /* tooltips */
    CBsourceDirsPreset->setTooltip("Presets for source directions to use for spatialisation.");
    TBuseDefaultHRIRs->setTooltip("If this is 'ticked', the plug-in is using the default HRIR set from the Spatial_Audio_Framework.");
    fileChooser.setTooltip("Optionally, a custom HRIR set may be loaded via the SOFA standard. Note that if the plug-in fails to load the specified .sofa file, it will revert to the default HRIR data.");
    CBinterpMode->setTooltip("Interpolation approach. Note that this plug-in can also perform \"phase-simplification\" (PS) of the HRTFs, which involves estimating the ITDs for all the HRIRs, removing the phase from the HRTFs, but then re-introducing the phase as IPDs per frequency-bin. Note that binaural room impulse responses (BRIRs) are not supported by either of the two modes!");
    TBenableRotation->setTooltip("Enables/Disables rotation of the source directions.");
    s_yaw->setTooltip("Sets the 'Yaw' rotation angle (in degrees).");
    s_pitch->setTooltip("Sets the 'Pitch' rotation angle (in degrees).");
    s_roll->setTooltip("Sets the 'Roll' rotation angle (in degrees).");
    t_flipYaw->setTooltip("Flips the sign (+/-) of the 'Yaw' rotation angle.");
    t_flipPitch->setTooltip("Flips the sign (+/-) of the 'Pitch' rotation angle.");
    t_flipRoll->setTooltip("Flips the sign (+/-) of the 'Roll' rotation angle.");
    te_oscport->setTooltip("The OSC port at which to receive the rotation angles. To facilitate head-tracking, send the rotation angles (in degrees) to this port ID as a 3-element vector 'ypr[3]', following the yaw-pitch-roll convention.");
    TBrpyFlag->setTooltip("If enabled, the plug-in will use the roll-pitch-yaw rotation order convention. If disabled, it will use the yaw-pitch-roll convention.");
    label_N_dirs->setTooltip("Number of HRIR directions in the current HRIR set.");
    label_N_Tri->setTooltip("Number of triangles found when computing the Convex Hull of the HRIR grid.");
    label_HRIR_fs->setTooltip("Sampling rate used when measuring/modelling the HRIRs.");
    label_DAW_fs->setTooltip("Current sampling rate, as dictated by the DAW/Host.");
    TB_showInputs->setTooltip("Enables/Disables displaying the source directions in the panning window.");
    TB_showOutputs->setTooltip("Enables/Disables displaying the HRIR directions in the panning window.");
    tb_loadJSON->setTooltip("Loads source directions from a JSON file. The JSON file format follows the same convention as the one employed by the IEM plugin suite (https://plugins.iem.at/docs/configurationfiles/).");
    tb_saveJSON->setTooltip("Saves the current source directions to a JSON file. The JSON file format follows the same convention as the one employed by the IEM plugin suite (https://plugins.iem.at/docs/configurationfiles/).");
    TBenablePreProc->setTooltip("Enables/Disables Diffuse-field EQ of the HRIRs, which is based on a weighted summation of all the HRTF magnitudes in the currently loaded set.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A simple HRIR interpolator and convolver. Note that binaural room impulse responses (BRIRs) are not supported!\n"));

    /* Specify screen refresh rate */
    startTimer(60);

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

    drawPluginBackgroundAndBanner(g, getBounds());

    /* Panels */
    drawPanel(g, {712,188,196,165}, panelFill,      panelStroke);
    drawPanel(g, {12, 58,196, 64}, panelFill,      panelStroke);
    drawPanel(g, {214,58,492,246}, panelFill,      panelStroke);
    drawPanel(g, {12,121,196,232}, panelFill,      panelStroke);
    drawPanel(g, {446,312,260, 41}, panelFill,      panelStroke);
    drawPanel(g, {712, 58,196, 78}, panelFill,      panelStroke);
    drawPanel(g, {712,135,196, 54}, panelFill,      panelStroke);
    drawPanel(g, {214,312,233, 41}, panelFill,      panelStroke);
    drawPanel(g, {712,243,196,110}, panelFillLight, panelStroke);

    /* Section titles */
    drawLabel(g, {84,  32,113,30}, "Inputs",         15.f);
    drawLabel(g, {392, 32,136,30}, "Panning Window", 15.f, juce::Justification::centred);
    drawLabel(g, {788, 32,113,30}, "HRIRs",          15.f);

    /* Presets + input settings */
    drawLabel(g, {23, 58, 67,30}, "Presets:",         14.5f);
    drawLabel(g, {23, 88,153,30}, "Number of Inputs:",14.5f);

    /* HRIR settings */
    drawLabel(g, {720, 58,160,30}, "Use Default HRIR set:", 15.f);
    drawLabel(g, {719,134,132,30}, "Num Dirs/Tri:",           11.f);
    drawLabel(g, {719,158, 89,30}, "HRIR/DAW Fs:",          11.f);

    /* Rotation block */
    drawLabel(g, {721,187,160,30}, "Enable Rotation:", 15.f);
    drawLabel(g, {710,210, 54,35}, "R-P-Y:",           11.f, juce::Justification::centred);
    drawLabel(g, {795,210, 91,35}, "OSC port:",        11.f);
    drawLabel(g, {698,238, 62,30}, "Yaw",   12.f, juce::Justification::centred);
    drawLabel(g, {735,238, 49,30}, "\\ypr[0]", 10.f, juce::Justification::centred);
    drawLabel(g, {775,238, 46,30}, "Pitch", 12.f, juce::Justification::centred);
    drawLabel(g, {808,238, 40,30}, "\\ypr[1]", 10.f, juce::Justification::centred);
    drawLabel(g, {831,238, 54,30}, "Roll",  12.f, juce::Justification::centred);
    drawLabel(g, {864,238, 40,30}, "\\ypr[2]", 10.f, juce::Justification::centred);
    drawLabel(g, {703,326,63,30}, "+/-", 13.f, juce::Justification::centred);
    drawLabel(g, {767,326,63,30}, "+/-", 13.f, juce::Justification::centred);
    drawLabel(g, {831,326,63,30}, "+/-", 13.f, juce::Justification::centred);

    /* Interpolation + visibility */
    drawLabel(g, {222,319,132,30}, "Interpolation:", 14.5f);
    drawLabel(g, {457,319,132,30}, "Show Inputs:",  14.5f);
    drawLabel(g, {582,319,122,30}, "Show HRIRs:",   14.5f);

    /* Diffuse-field EQ */
    drawLabel(g, {720,106,160,30}, "Apply Diffuse-Field EQ:", 15.f);

    /* Title */
    drawLabel(g, {16, 1,100,32}, "SPARTA|", 18.f);
    drawLabel(g, {92,  1,112,32}, "Binauraliser", 18.f, juce::Justification::centredLeft, juce::Colour(0xffff73f9));

    /* Azi° # Elev° label */
    drawLabel(g, {68,122,108,28}, juce::CharPointer_UTF8("Azi\xc2\xb0   #   Elev\xc2\xb0"), 15.f);

    g.setColour(Colours::white);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
        200, 16, 530, 11,
        Justification::centredLeft, true);

    /* display warning message */
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.setColour(Colours::red);
            g.drawText(TRANS("Set frame size to multiple of ") + String(binauraliser_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(binauraliser_getNumSources(hBin)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
                       TRANS("/") + String(binauraliser_getNumEars()) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_osc_connection_fail:
            g.setColour(Colours::red);
            g.drawText(TRANS("OSC failed to connect, or port is already taken"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_busContainsLFE:
            g.setColour(Colours::yellow);
            g.drawText(TRANS("LFE channels are not supported by this plugin"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.setColour(Colours::yellow);
            g.drawText(TRANS("Sample rate \"") + String(binauraliser_getDAWsamplerate(hBin)) + TRANS("\" is not recommended"),
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

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == CBsourceDirsPreset.get())
    {
        binauraliser_setInputConfigPreset(hBin, CBsourceDirsPreset->getSelectedId());
         
        processor.setParameterValue("numSources", binauraliser_getNumSources(hBin));
        for(int i=0; i<binauraliser_getNumSources(hBin); i++){
            processor.setParameterValue("azim" + juce::String(i), binauraliser_getSourceAzi_deg(hBin,i));
            processor.setParameterValue("elev" + juce::String(i), binauraliser_getSourceElev_deg(hBin,i));
        }
                
        refreshPanViewWindow = true;
    }
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == SL_num_sources.get())
    {
        refreshPanViewWindow = true;
    }
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == TBuseDefaultHRIRs.get())
    {
        binauraliser_setUseDefaultHRIRsflag(hBin, (int)TBuseDefaultHRIRs->getToggleState());
        refreshPanViewWindow = true;
    }
    else if (buttonThatWasClicked == TB_showInputs.get())
    {
        panWindow->setShowInputs(TB_showInputs->getToggleState());
        refreshPanViewWindow = true;
    }
    else if (buttonThatWasClicked == TB_showOutputs.get())
    {
        panWindow->setShowOutputs(TB_showOutputs->getToggleState());
        refreshPanViewWindow = true;
    }
    else if (buttonThatWasClicked == tb_loadJSON.get())
    {
        chooser = std::make_unique<juce::FileChooser> ("Load configuration...",
                                                       processor.getLastDir().exists() ? processor.getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                                                       "*.json");
        auto chooserFlags = juce::FileBrowserComponent::openMode
                                  | juce::FileBrowserComponent::canSelectFiles;
        chooser->launchAsync (chooserFlags, [this] (const FileChooser& fc) {
            auto file = fc.getResult();
            if (file != File{}){
                processor.setLastDir(file.getParentDirectory());
                processor.loadConfiguration (file);
            }
        });
    }
    else if (buttonThatWasClicked == tb_saveJSON.get())
    {
        chooser = std::make_unique<juce::FileChooser> ("Save configuration...",
                                                       processor.getLastDir().exists() ? processor.getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                                                       "*.json");
        auto chooserFlags = juce::FileBrowserComponent::saveMode;
        chooser->launchAsync (chooserFlags, [this] (const FileChooser& fc) {
            auto file = fc.getResult();
            if (file != File{}) {
                processor.setLastDir(file.getParentDirectory());
                processor.saveConfigurationToFile (file);
            }
        });
    }
}

void PluginEditor::timerCallback()
{
    /* labels for HRIR details */
    label_N_dirs->setText(String(binauraliser_getNDirs(hBin)), dontSendNotification);
    label_HRIR_fs->setText(String(binauraliser_getHRIRsamplerate(hBin)), dontSendNotification);
    label_DAW_fs->setText(String(binauraliser_getDAWsamplerate(hBin)), dontSendNotification);
    label_N_Tri->setText(String(binauraliser_getNTriangles(hBin)), dontSendNotification);

    /* parameters whos values can change internally should be periodically refreshed */
    sourceCoordsView_handle->setNCH(binauraliser_getNumSources(hBin));
    TBuseDefaultHRIRs->setToggleState(binauraliser_getUseDefaultHRIRsflag(hBin), dontSendNotification);

    /* Progress bar */
    if(binauraliser_getCodecStatus(hBin)==CODEC_STATUS_INITIALISING){
        addAndMakeVisible(progressbar);
        progress = (double)binauraliser_getProgressBar0_1(hBin);
        char text[PROGRESSBARTEXT_CHAR_LENGTH];
        binauraliser_getProgressBarText(hBin, (char*)text);
        progressbar.setTextToDisplay(String(text));
    }
    else
        removeChildComponent(&progressbar);

    /* disable certain parameters if currently initialising */
    if(binauraliser_getCodecStatus(hBin)==CODEC_STATUS_INITIALISING){
        if(CBsourceDirsPreset->isEnabled())
           CBsourceDirsPreset->setEnabled(false);
        if(SL_num_sources->isEnabled())
            SL_num_sources->setEnabled(false);
        if(TBuseDefaultHRIRs->isEnabled())
            TBuseDefaultHRIRs->setEnabled(false);
        if(CBinterpMode->isEnabled())
            CBinterpMode->setEnabled(false);
        if(tb_loadJSON->isEnabled())
            tb_loadJSON->setEnabled(false);
        if(fileChooser.isEnabled())
           fileChooser.setEnabled(false);
        if(sourceCoordsVP->isEnabled())
           sourceCoordsVP->setEnabled(false);
    }
    else{
        if(!CBsourceDirsPreset->isEnabled())
            CBsourceDirsPreset->setEnabled(true);
        if(!SL_num_sources->isEnabled())
            SL_num_sources->setEnabled(true);
        if(!TBuseDefaultHRIRs->isEnabled())
            TBuseDefaultHRIRs->setEnabled(true);
        if(!CBinterpMode->isEnabled())
            CBinterpMode->setEnabled(true);
        if(!tb_loadJSON->isEnabled())
            tb_loadJSON->setEnabled(true);
        if(!fileChooser.isEnabled())
            fileChooser.setEnabled(true);
        if(!sourceCoordsVP->isEnabled())
            sourceCoordsVP->setEnabled(true);
    }

    /* refresh pan view */
    if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) || processor.getRefreshWindow()){
        panWindow->refreshPanView();
        refreshPanViewWindow = false;
        processor.setRefreshWindow(false);
    }

    /* display warning message, if needed */
    if ((processor.getCurrentBlockSize() % binauraliser_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumInputs() < binauraliser_getNumSources(hBin))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumOutputs() < binauraliser_getNumEars())){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(!processor.getOscPortConnected() && binauraliser_getEnableRotation(hBin)){
        currentWarning = k_warning_osc_connection_fail;
        repaint(0,0,getWidth(),32);
    }
    else if (processor.getBusHasLFE()){
        currentWarning = k_warning_busContainsLFE;
        repaint(0,0,getWidth(),32);
    }
    else if ( !((binauraliser_getDAWsamplerate(hBin) == 44.1e3) || (binauraliser_getDAWsamplerate(hBin) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if (binauraliser_getDAWsamplerate(hBin) != binauraliser_getHRIRsamplerate(hBin)){
        currentWarning = k_warning_mismatch_fs;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }

    /* check if OSC port has changed */
    if (processor.getOscPortID() != te_oscport->getText().getIntValue())
        processor.setOscPortID(te_oscport->getText().getIntValue());
}
