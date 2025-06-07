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
    CBsourceDirsPreset->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBsourceDirsPreset->addItem (TRANS ("Default"), 1);
    CBsourceDirsPreset->addListener (this);

    CBsourceDirsPreset->setBounds (88, 66, 112, 20);

    SL_num_sources.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_sources.get());
    SL_num_sources->setRange (1, 128, 1);
    SL_num_sources->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_sources->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_sources->addListener (this);

    SL_num_sources->setBounds (152, 94, 48, 20);

    label_N_dirs.reset (new juce::Label ("new label",
                                         juce::String()));
    addAndMakeVisible (label_N_dirs.get());
    label_N_dirs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_N_dirs->setJustificationType (juce::Justification::centredLeft);
    label_N_dirs->setEditable (false, false, false);
    label_N_dirs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_N_dirs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_N_dirs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_N_dirs->setBounds (799, 140, 51, 20);

    label_HRIR_fs.reset (new juce::Label ("new label",
                                          juce::String()));
    addAndMakeVisible (label_HRIR_fs.get());
    label_HRIR_fs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_HRIR_fs->setJustificationType (juce::Justification::centredLeft);
    label_HRIR_fs->setEditable (false, false, false);
    label_HRIR_fs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_HRIR_fs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_HRIR_fs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_HRIR_fs->setBounds (799, 164, 51, 20);

    TBuseDefaultHRIRs.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBuseDefaultHRIRs.get());
    TBuseDefaultHRIRs->setButtonText (juce::String());
    TBuseDefaultHRIRs->addListener (this);

    TBuseDefaultHRIRs->setBounds (876, 61, 32, 24);

    label_DAW_fs.reset (new juce::Label ("new label",
                                         juce::String()));
    addAndMakeVisible (label_DAW_fs.get());
    label_DAW_fs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_DAW_fs->setJustificationType (juce::Justification::centredLeft);
    label_DAW_fs->setEditable (false, false, false);
    label_DAW_fs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_DAW_fs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_DAW_fs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

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

    label_N_Tri.reset (new juce::Label ("new label",
                                        juce::String()));
    addAndMakeVisible (label_N_Tri.get());
    label_N_Tri->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_N_Tri->setJustificationType (juce::Justification::centredLeft);
    label_N_Tri->setEditable (false, false, false);
    label_N_Tri->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_N_Tri->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_N_Tri->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_N_Tri->setBounds (853, 140, 51, 20);

    CBinterpMode.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBinterpMode.get());
    CBinterpMode->setEditableText (false);
    CBinterpMode->setJustificationType (juce::Justification::centredLeft);
    CBinterpMode->setTextWhenNothingSelected (juce::String());
    CBinterpMode->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBinterpMode->addListener (this);

    CBinterpMode->setBounds (316, 324, 125, 20);

    tb_loadJSON.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_loadJSON.get());
    tb_loadJSON->setButtonText (TRANS ("Import"));
    tb_loadJSON->setConnectedEdges (juce::Button::ConnectedOnRight);
    tb_loadJSON->addListener (this);
    tb_loadJSON->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff14889e));

    tb_loadJSON->setBounds (140, 40, 34, 14);

    tb_saveJSON.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON.get());
    tb_saveJSON->setButtonText (TRANS ("Export"));
    tb_saveJSON->setConnectedEdges (juce::Button::ConnectedOnLeft);
    tb_saveJSON->addListener (this);
    tb_saveJSON->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff224d97));
    tb_saveJSON->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff181f9a));

    tb_saveJSON->setBounds (174, 40, 34, 14);

    s_yaw.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_yaw.get());
    s_yaw->setRange (-180, 180, 0.01);
    s_yaw->setDoubleClickReturnValue(true, 0.0f);
    s_yaw->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_yaw->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 15);
    s_yaw->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6e));
    s_yaw->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_yaw->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_yaw->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_yaw->addListener (this);
    s_yaw->setBounds (717, 260, 60, 68);

    s_pitch.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_pitch.get());
    s_pitch->setRange (-180, 180, 0.01);
    s_pitch->setDoubleClickReturnValue(true, 0.0f);
    s_pitch->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_pitch->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 15);
    s_pitch->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6d));
    s_pitch->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_pitch->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_pitch->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_pitch->addListener (this);

    s_pitch->setBounds (780, 260, 60, 68);

    s_roll.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_roll.get());
    s_roll->setRange (-180, 180, 0.01);
    s_roll->setDoubleClickReturnValue(true, 0.0f);
    s_roll->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_roll->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 15);
    s_roll->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6d));
    s_roll->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_roll->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_roll->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_roll->addListener (this);

    s_roll->setBounds (843, 260, 60, 68);

    t_flipYaw.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipYaw.get());
    t_flipYaw->setButtonText (juce::String());
    t_flipYaw->addListener (this);

    t_flipYaw->setBounds (749, 329, 23, 24);

    t_flipPitch.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipPitch.get());
    t_flipPitch->setButtonText (juce::String());
    t_flipPitch->addListener (this);

    t_flipPitch->setBounds (812, 329, 23, 24);

    t_flipRoll.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipRoll.get());
    t_flipRoll->setButtonText (juce::String());
    t_flipRoll->addListener (this);

    t_flipRoll->setBounds (875, 329, 23, 24);

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
    te_oscport->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x6c838080));
    te_oscport->setText (TRANS ("9000"));

    te_oscport->setBounds (848, 216, 44, 22);

    TBrpyFlag.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBrpyFlag.get());
    TBrpyFlag->setButtonText (juce::String());
    TBrpyFlag->addListener (this);

    TBrpyFlag->setBounds (752, 216, 32, 24);

    TBenableRotation.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBenableRotation.get());
    TBenableRotation->setButtonText (juce::String());
    TBenableRotation->addListener (this);

    TBenableRotation->setBounds (832, 191, 32, 24);

    TBenablePreProc.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBenablePreProc.get());
    TBenablePreProc->setTooltip (TRANS ("Enable HRIR Pre-Processing"));
    TBenablePreProc->setButtonText (juce::String());
    TBenablePreProc->addListener (this);

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
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_num_sources->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_sources->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_sources->setSliderSnapsToMousePosition(false);

    /* interp modes */
    CBinterpMode->addItem(TRANS("Triangular"), INTERP_TRI);
    CBinterpMode->addItem(TRANS("Triangular (PS)"), INTERP_TRI_PS);

    /* add source preset options */
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
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

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
    fileChooser.setBounds (718, 89, 180, 20);
    StringArray filenames;
    filenames.add(binauraliser_getSofaFilePath(hBin));
    fileChooser.setRecentlyUsedFilenames(filenames);
    fileChooser.setFilenameIsEditable(true);

    /* grab current parameter settings */
    TBuseDefaultHRIRs->setToggleState(binauraliser_getUseDefaultHRIRsflag(hBin), dontSendNotification);
    SL_num_sources->setValue(binauraliser_getNumSources(hBin),dontSendNotification);
    TB_showInputs->setToggleState(true, dontSendNotification);
    TB_showOutputs->setToggleState(false, dontSendNotification);
    CBinterpMode->setSelectedId(binauraliser_getInterpMode(hBin), dontSendNotification);
    TBenableRotation->setToggleState((bool)binauraliser_getEnableRotation(hBin), dontSendNotification);
    s_yaw->setValue(binauraliser_getYaw(hBin), dontSendNotification);
    s_pitch->setValue(binauraliser_getPitch(hBin), dontSendNotification);
    s_roll->setValue(binauraliser_getRoll(hBin), dontSendNotification);
    t_flipYaw->setToggleState((bool)binauraliser_getFlipYaw(hBin), dontSendNotification);
    t_flipPitch->setToggleState((bool)binauraliser_getFlipPitch(hBin), dontSendNotification);
    t_flipRoll->setToggleState((bool)binauraliser_getFlipRoll(hBin), dontSendNotification);
    te_oscport->setText(String(processor.getOscPortID()), dontSendNotification);
    TBrpyFlag->setToggleState((bool)binauraliser_getRPYflag(hBin), dontSendNotification);

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
    startTimer(TIMER_GUI_RELATED, 60);

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
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
    TBenablePreProc = nullptr;

    setLookAndFeel(nullptr);
    panWindow = nullptr;
    sourceCoordsVP = nullptr;
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 30, width = 920, height = 163;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             112.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 193, width = 920, height = 167;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             360.0f - 193.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             264.0f - 193.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 918.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             920.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 712, y = 188, width = 196, height = 165;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 58, width = 196, height = 64;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 23, y = 58, width = 67, height = 30;
        juce::String text (TRANS ("Presets: "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 214, y = 58, width = 492, height = 246;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 121, width = 196, height = 232;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 446, y = 312, width = 260, height = 41;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 712, y = 58, width = 196, height = 78;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 712, y = 135, width = 196, height = 54;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 23, y = 88, width = 153, height = 30;
        juce::String text (TRANS ("Number of Inputs:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 84, y = 32, width = 113, height = 30;
        juce::String text (TRANS ("Inputs"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 788, y = 32, width = 113, height = 30;
        juce::String text (TRANS ("HRIRs"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 392, y = 32, width = 136, height = 30;
        juce::String text (TRANS ("Panning Window"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 720, y = 58, width = 160, height = 30;
        juce::String text (TRANS ("Use Default HRIR set:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 457, y = 319, width = 132, height = 30;
        juce::String text (TRANS ("Show Inputs:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 582, y = 319, width = 122, height = 30;
        juce::String text (TRANS ("Show HRIRs:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 214, y = 312, width = 233, height = 41;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 222, y = 319, width = 132, height = 30;
        juce::String text (TRANS ("Interp. Mode:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 719, y = 158, width = 89, height = 30;
        juce::String text (TRANS ("HRIR/DAW Fs:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 719, y = 134, width = 132, height = 30;
        juce::String text (TRANS ("N Dirs/Tri:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 712, y = 243, width = 196, height = 110;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 735, y = 238, width = 49, height = 30;
        juce::String text (TRANS ("\\ypr[0]"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (10.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 775, y = 238, width = 46, height = 30;
        juce::String text (TRANS ("Pitch"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 831, y = 238, width = 54, height = 30;
        juce::String text (TRANS ("Roll"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 831, y = 326, width = 63, height = 30;
        juce::String text (TRANS ("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 703, y = 326, width = 63, height = 30;
        juce::String text (TRANS ("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 767, y = 326, width = 63, height = 30;
        juce::String text (TRANS ("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 795, y = 210, width = 91, height = 35;
        juce::String text (TRANS ("OSC port:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 698, y = 238, width = 62, height = 30;
        juce::String text (TRANS ("Yaw"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 808, y = 238, width = 40, height = 30;
        juce::String text (TRANS ("\\ypr[1]"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (10.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 864, y = 238, width = 40, height = 30;
        juce::String text (TRANS ("\\ypr[2]"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (10.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 710, y = 210, width = 54, height = 35;
        juce::String text (TRANS ("R-P-Y:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 721, y = 187, width = 160, height = 30;
        juce::String text (TRANS ("Enable Rotation:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 1, width = 100, height = 32;
        juce::String text (TRANS ("SPARTA|"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.80f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 92, y = 1, width = 112, height = 32;
        juce::String text (TRANS ("Binauraliser"));
        juce::Colour fillColour = juce::Colour (0xffff73f9);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 66, y = 122, width = 108, height = 28;
        juce::String text (juce::CharPointer_UTF8 ("Azi\xc2\xb0   #   Elev\xc2\xb0"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 922, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 360;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 918, y = 0, width = 2, height = 360;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 360, width = 920, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 720, y = 106, width = 160, height = 30;
        juce::String text (TRANS ("Apply Diffuse-Field EQ:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

	g.setColour(Colours::white);
	g.setFont(juce::FontOptions (11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		200, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(binauraliser_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(binauraliser_getDAWsamplerate(hBin)) + TRANS(") is unsupported"),
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
                       TRANS("/") + String(binauraliser_getNumSources(hBin)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
                       TRANS("/") + String(binauraliser_getNumEars()) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_osc_connection_fail:
            g.drawText(TRANS("OSC failed to connect, or port is already taken"),
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
         
        processor.setParameterValue("numSources", binauraliser_getNumSources(hBin), true);
        for(int i=0; i<binauraliser_getNumSources(hBin); i++){
            processor.setParameterValue("azim" + juce::String(i), binauraliser_getSourceAzi_deg(hBin,i), true);
            processor.setParameterValue("elev" + juce::String(i), binauraliser_getSourceElev_deg(hBin,i), true);
        }
        
        refreshPanViewWindow = true;
    }
    else if (comboBoxThatHasChanged == CBinterpMode.get())
    {
        binauraliser_setInterpMode(hBin, CBinterpMode->getSelectedId());
    }
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == SL_num_sources.get())
    {
        processor.setParameterValue("numSources", SL_num_sources->getValue(), true);
        refreshPanViewWindow = true;
    }
    else if (sliderThatWasMoved == s_yaw.get())
    {
        processor.setParameterValue("yaw", s_yaw->getValue(), true); 
    }
    else if (sliderThatWasMoved == s_pitch.get())
    {
        processor.setParameterValue("pitch", s_pitch->getValue(), true);
    }
    else if (sliderThatWasMoved == s_roll.get())
    {
        processor.setParameterValue("roll", s_roll->getValue(), true);
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
    else if (buttonThatWasClicked == t_flipYaw.get())
    {
        processor.setParameterValue("flipYaw", t_flipYaw->getToggleState(), true);
    }
    else if (buttonThatWasClicked == t_flipPitch.get())
    {
        processor.setParameterValue("flipPitch", t_flipPitch->getToggleState(), true);
    }
    else if (buttonThatWasClicked == t_flipRoll.get())
    {
        processor.setParameterValue("flipRoll", t_flipRoll->getToggleState(), true);
    }
    else if (buttonThatWasClicked == TBrpyFlag.get())
    {
        processor.setParameterValue("useRollPitchYaw", TBrpyFlag->getToggleState(), true);
    }
    else if (buttonThatWasClicked == TBenableRotation.get())
    {
        processor.setParameterValue("enableRotation", TBenableRotation->getToggleState(), true);
    }
    else if (buttonThatWasClicked == TBenablePreProc.get())
    {
        binauraliser_setEnableHRIRsDiffuseEQ(hBin, (int)TBenablePreProc->getToggleState());
    }
}

void PluginEditor::timerCallback(int timerID)
{
    switch(timerID){
        case TIMER_PROCESSING_RELATED:
            /* handled in PluginProcessor */
            break;

        case TIMER_GUI_RELATED:

            /* labels for HRIR details */
            label_N_dirs->setText(String(binauraliser_getNDirs(hBin)), dontSendNotification);
            label_HRIR_fs->setText(String(binauraliser_getHRIRsamplerate(hBin)), dontSendNotification);
            label_DAW_fs->setText(String(binauraliser_getDAWsamplerate(hBin)), dontSendNotification);
            label_N_Tri->setText(String(binauraliser_getNTriangles(hBin)), dontSendNotification);

            /* parameters whos values can change internally should be periodically refreshed */
            sourceCoordsView_handle->setNCH(binauraliser_getNumSources(hBin));
            TBuseDefaultHRIRs->setToggleState(binauraliser_getUseDefaultHRIRsflag(hBin), dontSendNotification);
            TBenablePreProc->setToggleState(binauraliser_getEnableHRIRsDiffuseEQ(hBin), dontSendNotification);
            SL_num_sources->setValue(binauraliser_getNumSources(hBin),dontSendNotification);
            TBenableRotation->setToggleState((bool)binauraliser_getEnableRotation(hBin), dontSendNotification);
            s_yaw->setValue(binauraliser_getYaw(hBin), dontSendNotification);
            s_pitch->setValue(binauraliser_getPitch(hBin), dontSendNotification);
            s_roll->setValue(binauraliser_getRoll(hBin), dontSendNotification);
            t_flipYaw->setToggleState((bool)binauraliser_getFlipYaw(hBin), dontSendNotification);
            t_flipPitch->setToggleState((bool)binauraliser_getFlipPitch(hBin), dontSendNotification);
            t_flipRoll->setToggleState((bool)binauraliser_getFlipRoll(hBin), dontSendNotification);
            TBrpyFlag->setToggleState((bool)binauraliser_getRPYflag(hBin), dontSendNotification);

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
            if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) || sourceCoordsView_handle->getHasASliderChanged() || processor.getRefreshWindow()){
                panWindow->refreshPanView();
                sourceCoordsView_handle->setHasASliderChange(false);
                refreshPanViewWindow = false;
                processor.setRefreshWindow(false);
            }

            /* display warning message, if needed */
            if ((processor.getCurrentBlockSize() % binauraliser_getFrameSize()) != 0){
                currentWarning = k_warning_frameSize;
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
            else if(currentWarning){
                currentWarning = k_warning_none;
                repaint(0,0,getWidth(),32);
            }

            /* check if OSC port has changed */
            if (processor.getOscPortID() != te_oscport->getText().getIntValue())
                processor.setOscPortID(te_oscport->getText().getIntValue());

            break;
    }
}
