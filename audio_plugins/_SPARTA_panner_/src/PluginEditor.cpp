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
    : AudioProcessorEditor(p), processor(p), progressbar(progress)
{
    CBsourceDirsPreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBsourceDirsPreset.get());
    CBsourceDirsPreset->setEditableText (false);
    CBsourceDirsPreset->setJustificationType (juce::Justification::centredLeft);
    CBsourceDirsPreset->setTextWhenNothingSelected (juce::String());
    CBsourceDirsPreset->addListener (this);
    CBsourceDirsPreset->setBounds (88, 66, 112, 20);

    SL_num_sources = std::make_unique<SliderWithAttachment>(p.parameters, "numInputs");
    addAndMakeVisible (SL_num_sources.get());
    SL_num_sources->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_sources->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_sources->addListener (this);
    SL_num_sources->setBounds (152, 94, 48, 20);

    TB_showInputs.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_showInputs.get());
    TB_showInputs->setButtonText (juce::String());
    TB_showInputs->addListener (this);
    TB_showInputs->setBounds (672, 317, 24, 24);

    TB_showOutputs.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_showOutputs.get());
    TB_showOutputs->setButtonText (juce::String());
    TB_showOutputs->addListener (this);
    TB_showOutputs->setBounds (672, 349, 24, 24);

    SL_pValue = std::make_unique<SliderWithAttachment>(p.parameters, "roomCoeff");
    addAndMakeVisible (SL_pValue.get());
    SL_pValue->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_pValue->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    SL_pValue->addListener (this);
    SL_pValue->setBounds (309, 351, 48, 18);

    CBsLoudspeakerDirsPreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBsLoudspeakerDirsPreset.get());
    CBsLoudspeakerDirsPreset->setEditableText (false);
    CBsLoudspeakerDirsPreset->setJustificationType (juce::Justification::centredLeft);
    CBsLoudspeakerDirsPreset->setTextWhenNothingSelected (juce::String());
    CBsLoudspeakerDirsPreset->addListener (this);
    CBsLoudspeakerDirsPreset->setBounds (788, 66, 112, 20);

    SL_num_loudspeakers = std::make_unique<SliderWithAttachment>(p.parameters, "numOutputs");
    addAndMakeVisible (SL_num_loudspeakers.get());
    SL_num_loudspeakers->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_loudspeakers->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_loudspeakers->addListener (this);
    SL_num_loudspeakers->setBounds (860, 94, 40, 20);

    tb_loadJSON_src.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_loadJSON_src.get());
    tb_loadJSON_src->setButtonText (TRANS ("Import"));
    tb_loadJSON_src->setConnectedEdges (juce::Button::ConnectedOnRight);
    tb_loadJSON_src->addListener (this);
    tb_loadJSON_src->setBounds (140, 41, 34, 14);

    tb_saveJSON_src.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON_src.get());
    tb_saveJSON_src->setButtonText (TRANS ("Export"));
    tb_saveJSON_src->setConnectedEdges (juce::Button::ConnectedOnLeft);
    tb_saveJSON_src->addListener (this);
    tb_saveJSON_src->setBounds (174, 41, 34, 14);

    tb_loadJSON_ls.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_loadJSON_ls.get());
    tb_loadJSON_ls->setButtonText (TRANS ("Import"));
    tb_loadJSON_ls->setConnectedEdges (juce::Button::ConnectedOnRight);
    tb_loadJSON_ls->addListener (this);
    tb_loadJSON_ls->setBounds (712, 41, 34, 14);

    tb_saveJSON_ls.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON_ls.get());
    tb_saveJSON_ls->setButtonText (TRANS ("Export"));
    tb_saveJSON_ls->setConnectedEdges (juce::Button::ConnectedOnLeft);
    tb_saveJSON_ls->addListener (this);
    tb_saveJSON_ls->setBounds (746, 41, 34, 14);

    SL_spread = std::make_unique<SliderWithAttachment>(p.parameters, "spread");
    addAndMakeVisible (SL_spread.get());
    SL_spread->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_spread->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    SL_spread->addListener (this);
    SL_spread->setBounds (309, 319, 48, 18);

    s_yaw = std::make_unique<SliderWithAttachment>(p.parameters, "yaw");
    addAndMakeVisible (s_yaw.get());
    s_yaw->setSliderStyle (juce::Slider::LinearBar);
    s_yaw->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 14);
    s_yaw->setBounds (373, 333, 63, 18);

    t_flipYaw = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipYaw");
    addAndMakeVisible (t_flipYaw.get());
    t_flipYaw->setBounds (406, 352, 23, 24);

    t_flipPitch = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipPitch");
    addAndMakeVisible (t_flipPitch.get());
    t_flipPitch->setBounds (473, 352, 23, 24);

    t_flipRoll = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "flipRoll");
    addAndMakeVisible (t_flipRoll.get());
    t_flipRoll->setBounds (538, 352, 23, 24);

    s_pitch = std::make_unique<SliderWithAttachment>(p.parameters, "pitch");
    addAndMakeVisible (s_pitch.get());
    s_pitch->setSliderStyle (juce::Slider::LinearBar);
    s_pitch->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 14);
    s_pitch->setBounds (440, 333, 63, 18);

    s_roll = std::make_unique<SliderWithAttachment>(p.parameters, "roll");
    addAndMakeVisible (s_roll.get());
    s_roll->setSliderStyle (juce::Slider::LinearBar);
    s_roll->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 14);
    s_roll->setBounds (507, 333, 63, 18);

    setSize (920, 386);

    /* handle to object */
    hPan = processor.getFXHandle();

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    setLookAndFeel(&LAF);

    /* remove slider bit from these sliders */
    SL_pValue->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_pValue->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_pValue->setSliderSnapsToMousePosition(false);
    SL_spread->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_spread->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_spread->setSliderSnapsToMousePosition(false);
    SL_num_sources->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_sources->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_sources->setSliderSnapsToMousePosition(false);
    SL_num_loudspeakers->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_loudspeakers->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_loudspeakers->setSliderSnapsToMousePosition(false);

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
    //CBsourceDirsPreset->addItem (TRANS("9+10+3.2"), SOURCE_CONFIG_ARRAY_PRESET_22P2_9_10_3);
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
    CBsourceDirsPreset->addItem (TRANS("Aalto MCC"), SOURCE_CONFIG_PRESET_AALTO_MCC);
    CBsourceDirsPreset->addItem (TRANS("Aalto MCC-subset"), SOURCE_CONFIG_PRESET_AALTO_MCC_SUBSET);
    CBsourceDirsPreset->addItem (TRANS("Aalto Apaja"), SOURCE_CONFIG_PRESET_AALTO_APAJA);
    CBsourceDirsPreset->addItem (TRANS("Aalto LR"), SOURCE_CONFIG_PRESET_AALTO_LR);
    CBsourceDirsPreset->addItem (TRANS("DTU AVIL"), SOURCE_CONFIG_PRESET_DTU_AVIL);
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

    /* add Loudspeaker preset options */
    CBsLoudspeakerDirsPreset->addItem (TRANS("Stereo"), LOUDSPEAKER_ARRAY_PRESET_STEREO);
    CBsLoudspeakerDirsPreset->addItem (TRANS("5.x"), LOUDSPEAKER_ARRAY_PRESET_5PX);
    CBsLoudspeakerDirsPreset->addItem (TRANS("7.x"), LOUDSPEAKER_ARRAY_PRESET_7PX);
    CBsLoudspeakerDirsPreset->addItem (TRANS("8.x"), LOUDSPEAKER_ARRAY_PRESET_8PX);
    CBsLoudspeakerDirsPreset->addItem (TRANS("9.x"), LOUDSPEAKER_ARRAY_PRESET_9PX);
    CBsLoudspeakerDirsPreset->addItem (TRANS("10.x"), LOUDSPEAKER_ARRAY_PRESET_10PX);
    CBsLoudspeakerDirsPreset->addItem (TRANS("11.x"), LOUDSPEAKER_ARRAY_PRESET_11PX);
    CBsLoudspeakerDirsPreset->addItem (TRANS("11.x (7+4)"), LOUDSPEAKER_ARRAY_PRESET_11PX_7_4);
    CBsLoudspeakerDirsPreset->addItem (TRANS("13.x"), LOUDSPEAKER_ARRAY_PRESET_13PX);
    CBsLoudspeakerDirsPreset->addItem (TRANS("22.x"), LOUDSPEAKER_ARRAY_PRESET_22PX);
    CBsLoudspeakerDirsPreset->addItem (TRANS("9+10+3.2"), LOUDSPEAKER_ARRAY_PRESET_22P2_9_10_3);
    CBsLoudspeakerDirsPreset->addItem (TRANS("ProTools Stereo"), LOUDSPEAKER_ARRAY_PRESET_PROTOOLS_STEREO);
    CBsLoudspeakerDirsPreset->addItem (TRANS("ProTools LCR"), LOUDSPEAKER_ARRAY_PRESET_PROTOOLS_LCR);
    CBsLoudspeakerDirsPreset->addItem (TRANS("ProTools Quad"), LOUDSPEAKER_ARRAY_PRESET_PROTOOLS_QUAD);
    CBsLoudspeakerDirsPreset->addItem (TRANS("ProTools 5.0"), LOUDSPEAKER_ARRAY_PRESET_PROTOOLS_5_0);
    CBsLoudspeakerDirsPreset->addItem (TRANS("ProTools 5.0.2"), LOUDSPEAKER_ARRAY_PRESET_PROTOOLS_5_0_2);
    CBsLoudspeakerDirsPreset->addItem (TRANS("ProTools 5.0.4"), LOUDSPEAKER_ARRAY_PRESET_PROTOOLS_5_0_4);
    CBsLoudspeakerDirsPreset->addItem (TRANS("ProTools 7.0"), LOUDSPEAKER_ARRAY_PRESET_PROTOOLS_7_0);
    CBsLoudspeakerDirsPreset->addItem (TRANS("ProTools 7.0.2"), LOUDSPEAKER_ARRAY_PRESET_PROTOOLS_7_0_2);
    CBsLoudspeakerDirsPreset->addItem (TRANS("ProTools 7.0.4"), LOUDSPEAKER_ARRAY_PRESET_PROTOOLS_7_0_4);
    CBsLoudspeakerDirsPreset->addItem (TRANS("ProTools 7.0.6"), LOUDSPEAKER_ARRAY_PRESET_PROTOOLS_7_0_6);
    CBsLoudspeakerDirsPreset->addItem (TRANS("ProTools 9.0.4"), LOUDSPEAKER_ARRAY_PRESET_PROTOOLS_9_0_4);
    CBsLoudspeakerDirsPreset->addItem (TRANS("ProTools 9.0.6"), LOUDSPEAKER_ARRAY_PRESET_PROTOOLS_9_0_6);
    CBsLoudspeakerDirsPreset->addItem (TRANS("Aalto MCC"), LOUDSPEAKER_ARRAY_PRESET_AALTO_MCC);
    CBsLoudspeakerDirsPreset->addItem (TRANS("Aalto MCC-subset"), LOUDSPEAKER_ARRAY_PRESET_AALTO_MCC_SUBSET);
    CBsLoudspeakerDirsPreset->addItem (TRANS("Aalto Apaja"), LOUDSPEAKER_ARRAY_PRESET_AALTO_APAJA);
    CBsLoudspeakerDirsPreset->addItem (TRANS("Aalto LR"), LOUDSPEAKER_ARRAY_PRESET_AALTO_LR);
    CBsLoudspeakerDirsPreset->addItem (TRANS("DTU AVIL"), LOUDSPEAKER_ARRAY_PRESET_DTU_AVIL);
    CBsLoudspeakerDirsPreset->addItem (TRANS("T-design (4)"), LOUDSPEAKER_ARRAY_PRESET_T_DESIGN_4);
    CBsLoudspeakerDirsPreset->addItem (TRANS("T-design (12)"), LOUDSPEAKER_ARRAY_PRESET_T_DESIGN_12);
    CBsLoudspeakerDirsPreset->addItem (TRANS("T-design (24)"), LOUDSPEAKER_ARRAY_PRESET_T_DESIGN_24);
    CBsLoudspeakerDirsPreset->addItem (TRANS("T-design (36)"), LOUDSPEAKER_ARRAY_PRESET_T_DESIGN_36);
    CBsLoudspeakerDirsPreset->addItem (TRANS("T-design (48)"), LOUDSPEAKER_ARRAY_PRESET_T_DESIGN_48);
    CBsLoudspeakerDirsPreset->addItem (TRANS("T-design (60)"), LOUDSPEAKER_ARRAY_PRESET_T_DESIGN_60);
    CBsLoudspeakerDirsPreset->addItem (TRANS("SphCov (9)"), LOUDSPEAKER_ARRAY_PRESET_SPH_COV_9);
    CBsLoudspeakerDirsPreset->addItem (TRANS("SphCov (16)"), LOUDSPEAKER_ARRAY_PRESET_SPH_COV_16);
    CBsLoudspeakerDirsPreset->addItem (TRANS("SphCov (25)"), LOUDSPEAKER_ARRAY_PRESET_SPH_COV_25);
    CBsLoudspeakerDirsPreset->addItem (TRANS("SphCov (49)"), LOUDSPEAKER_ARRAY_PRESET_SPH_COV_49);
    CBsLoudspeakerDirsPreset->addItem (TRANS("SphCov (64)"), LOUDSPEAKER_ARRAY_PRESET_SPH_COV_64);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

    /* source coordinates viewport */
    sourceCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (sourceCoordsVP.get());
    sourceCoordsView_handle = new inputCoordsView(p, MAX_NUM_INPUTS, panner_getNumSources(hPan));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(22, 153, 184, 210);
    sourceCoordsView_handle->setNCH(panner_getNumSources(hPan));

    /* loudspeaker coordinates viewport */
    loudspeakerCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (loudspeakerCoordsVP.get());
    loudspeakerCoordsView_handle = new outputCoordsView(p, MAX_NUM_OUTPUTS, panner_getNumLoudspeakers(hPan));
    loudspeakerCoordsVP->setViewedComponent (loudspeakerCoordsView_handle);
    loudspeakerCoordsVP->setScrollBarsShown (true, false);
    loudspeakerCoordsVP->setAlwaysOnTop(true);
    loudspeakerCoordsVP->setBounds(722, 153, 184, 210);
    loudspeakerCoordsView_handle->setNCH(panner_getNumLoudspeakers(hPan));

    /* grab current parameter settings */
    TB_showInputs->setToggleState(true, dontSendNotification);
    TB_showOutputs->setToggleState(true, dontSendNotification);

    /* create panning window */
    panWindow.reset (new pannerView(p, 480, 240));
    addAndMakeVisible (panWindow.get());
    panWindow->setBounds (220, 58, 480, 240);
    panWindow->setShowInputs(TB_showInputs->getToggleState());
    panWindow->setShowOutputs(TB_showOutputs->getToggleState());
    refreshPanViewWindow = true;

    /* tooltips */
    CBsourceDirsPreset->setTooltip("Presets for source directions to use for spatialisation.");
    CBsLoudspeakerDirsPreset->setTooltip("Presets for loudspeaker directions to pan to.");
    s_yaw->setTooltip("Sets the 'Yaw' rotation angle (in degrees).");
    s_pitch->setTooltip("Sets the 'Pitch' rotation angle (in degrees).");
    s_roll->setTooltip("Sets the 'Roll' rotation angle (in degrees).");
    t_flipYaw->setTooltip("Flips the sign (+/-) of the 'Yaw' rotation angle.");
    t_flipPitch->setTooltip("Flips the sign (+/-) of the 'Pitch' rotation angle.");
    t_flipRoll->setTooltip("Flips the sign (+/-) of the 'Roll' rotation angle.");
    TB_showInputs->setTooltip("Enables/Disables displaying the source directions in the panning window.");
    TB_showOutputs->setTooltip("Enables/Disables displaying the loudspeaker directions in the panning window.");
    tb_loadJSON_src->setTooltip("Loads source directions from a JSON file. The JSON file format follows the same convention as the one employed by the IEM plugin suite (https://plugins.iem.at/docs/configurationfiles/).");
    tb_saveJSON_src->setTooltip("Saves the current source directions to a JSON file. The JSON file format follows the same convention as the one employed by the IEM plugin suite (https://plugins.iem.at/docs/configurationfiles/).");
    tb_loadJSON_ls->setTooltip("Loads loudspeaker directions from a JSON file. The JSON file format follows the same convention as the one employed by the IEM plugin suite (https://plugins.iem.at/docs/configurationfiles/).");
    tb_saveJSON_ls->setTooltip("Saves the current loudspeaker directions to a JSON file. The JSON file format follows the same convention as the one employed by the IEM plugin suite (https://plugins.iem.at/docs/configurationfiles/).");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A frequency-dependent 3D panner based on the Vector-base Amplitude Panning (VBAP) method, which can offer more consistent loudness when sources are panned in-between the loudspeaker directions when compared to frequency-independent VBAP."));

	/* Specify screen refresh rate */
    startTimer(40);

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    CBsourceDirsPreset = nullptr;
    SL_num_sources = nullptr;
    TB_showInputs = nullptr;
    TB_showOutputs = nullptr;
    SL_pValue = nullptr;
    CBsLoudspeakerDirsPreset = nullptr;
    SL_num_loudspeakers = nullptr;
    tb_loadJSON_src = nullptr;
    tb_saveJSON_src = nullptr;
    tb_loadJSON_ls = nullptr;
    tb_saveJSON_ls = nullptr;
    SL_spread = nullptr;
    s_yaw = nullptr;
    t_flipYaw = nullptr;
    t_flipPitch = nullptr;
    t_flipRoll = nullptr;
    s_pitch = nullptr;
    s_roll = nullptr;

    setLookAndFeel(nullptr);
    sourceCoordsVP = nullptr;
    loudspeakerCoordsVP = nullptr;
    panWindow = nullptr;
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 208, width = 920, height = 178;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             384.0f - 208.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             304.0f - 208.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 30, width = 920, height = 178;
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
        float x = 1.0f, y = 2.0f, width = 918.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             912.0f - 1.0f + x,
                                             24.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 366, y = 308, width = 211, height = 68;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 366, y = 308, width = 211, height = 68;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 220, y = 308, width = 147, height = 68;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 58, width = 196, height = 64;
        juce::Colour fillColour = juce::Colour (0x13f4f4f4);
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
        int x = 220, y = 58, width = 480, height = 240;
        juce::Colour fillColour = juce::Colour (0x13f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 121, width = 196, height = 255;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 576, y = 308, width = 124, height = 68;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 712, y = 58, width = 196, height = 64;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 712, y = 121, width = 196, height = 255;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 23, y = 88, width = 145, height = 30;
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
        int x = 789, y = 32, width = 113, height = 30;
        juce::String text (TRANS ("Outputs"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 404, y = 32, width = 156, height = 30;
        juce::String text (TRANS ("Panning Window"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 587, y = 314, width = 132, height = 30;
        juce::String text (TRANS ("Show Inputs:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 587, y = 346, width = 132, height = 30;
        juce::String text (TRANS ("Show Outputs:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 227, y = 338, width = 123, height = 30;
        juce::String text (TRANS ("Room coeff:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 723, y = 58, width = 67, height = 30;
        juce::String text (TRANS ("Presets: "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 723, y = 88, width = 157, height = 30;
        juce::String text (TRANS ("Number of Outputs:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
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
        juce::String text (TRANS ("Panner"));
        juce::Colour fillColour = juce::Colour (0xff0eff00);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 227, y = 313, width = 123, height = 30;
        juce::String text (juce::CharPointer_UTF8 ("Spread (\xc2\xb0):"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 228, y = 354, width = 108, height = 24;
        juce::String text (TRANS ("(0: Wet, 1: Dry)"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (10.00f, juce::Font::plain).withStyle ("Bold"));
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
        int x = 767, y = 122, width = 108, height = 28;
        juce::String text (juce::CharPointer_UTF8 ("Azi\xc2\xb0   #   Elev\xc2\xb0"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 451, y = 306, width = 46, height = 30;
        juce::String text (TRANS ("Pitch"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 515, y = 306, width = 54, height = 30;
        juce::String text (TRANS ("Roll"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 376, y = 306, width = 58, height = 30;
        juce::String text (TRANS ("Yaw"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 495, y = 350, width = 63, height = 26;
        juce::String text (TRANS ("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 362, y = 350, width = 63, height = 26;
        juce::String text (TRANS ("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 429, y = 350, width = 63, height = 26;
        juce::String text (TRANS ("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 0, y = 0, width = 922, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 386;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 918, y = 0, width = 2, height = 386;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 922, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 384, width = 922, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

	g.setColour(Colours::white);
	g.setFont(juce::FontOptions (11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		175, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.setColour(Colours::red);
            g.drawText(TRANS("Set frame size to multiple of ") + String(panner_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(panner_getNumSources(hPan)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
                       TRANS("/") + String(panner_getNumLoudspeakers(hPan)) + TRANS(")"),
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
            g.drawText(TRANS("Sample rate \"") + String(panner_getDAWsamplerate(hPan)) + TRANS("\" is not recommended"),
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
        panner_setInputConfigPreset(hPan, CBsourceDirsPreset->getSelectedId());
        
        processor.setParameterValue("numInputs", panner_getNumSources(hPan));
        for(int i=0; i<panner_getNumSources(hPan); i++){
            processor.setParameterValue("srcAzim" + juce::String(i), panner_getSourceAzi_deg(hPan,i));
            processor.setParameterValue("srcElev" + juce::String(i), panner_getSourceElev_deg(hPan,i));
        }
        
        refreshPanViewWindow = true;
    }
    else if (comboBoxThatHasChanged == CBsLoudspeakerDirsPreset.get())
    {
        panner_setOutputConfigPreset(hPan, CBsLoudspeakerDirsPreset->getSelectedId());
        
        processor.setParameterValue("numOutputs", panner_getNumLoudspeakers(hPan));
        for(int i=0; i<panner_getNumLoudspeakers(hPan); i++){
            processor.setParameterValue("lsAzim" + juce::String(i), panner_getLoudspeakerAzi_deg(hPan,i));
            processor.setParameterValue("lsElev" + juce::String(i), panner_getLoudspeakerElev_deg(hPan,i));
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
    else if (sliderThatWasMoved == SL_num_loudspeakers.get())
    {
        refreshPanViewWindow = true;
    }
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == TB_showInputs.get())
    {
        panWindow->setShowInputs(TB_showInputs->getToggleState());
        refreshPanViewWindow = true;
    }
    else if (buttonThatWasClicked == TB_showOutputs.get())
    {
        panWindow->setShowOutputs(TB_showOutputs->getToggleState());
        refreshPanViewWindow = true;
    }
    else if (buttonThatWasClicked == tb_loadJSON_src.get())
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
                processor.loadConfiguration (file,0);
            }
        });
    }
    else if (buttonThatWasClicked == tb_saveJSON_src.get())
    {
        chooser = std::make_unique<juce::FileChooser> ("Save configuration...",
                                                       processor.getLastDir().exists() ? processor.getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                                                       "*.json");
        auto chooserFlags = juce::FileBrowserComponent::saveMode;
        chooser->launchAsync (chooserFlags, [this] (const FileChooser& fc) {
            auto file = fc.getResult();
            if (file != File{}) {
                processor.setLastDir(file.getParentDirectory());
                processor.saveConfigurationToFile (file,0);
            }
        });
    }
    else if (buttonThatWasClicked == tb_loadJSON_ls.get())
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
                processor.loadConfiguration (file,1);
            }
        });
    }
    else if (buttonThatWasClicked == tb_saveJSON_ls.get())
    {
        chooser = std::make_unique<juce::FileChooser> ("Save configuration...",
                                                       processor.getLastDir().exists() ? processor.getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                                                       "*.json");
        auto chooserFlags = juce::FileBrowserComponent::saveMode;
        chooser->launchAsync (chooserFlags, [this] (const FileChooser& fc) {
            auto file = fc.getResult();
            if (file != File{}) {
                processor.setLastDir(file.getParentDirectory());
                processor.saveConfigurationToFile (file,1);
            }
        });
    }
}

void PluginEditor::timerCallback()
{
    /* refresh parameters that can change internally */
    sourceCoordsView_handle->setNCH(panner_getNumSources(hPan));
    loudspeakerCoordsView_handle->setNCH(panner_getNumLoudspeakers(hPan));

    /* Progress bar */
#if 1
    if(panner_getCodecStatus(hPan)==CODEC_STATUS_INITIALISING){
        addAndMakeVisible(progressbar);
        progress = (double)panner_getProgressBar0_1(hPan);
        char text[PROGRESSBARTEXT_CHAR_LENGTH];
        panner_getProgressBarText(hPan, (char*)text);
        progressbar.setTextToDisplay(String(text));
    }
    else
        removeChildComponent(&progressbar);
#endif

    /* Some parameters shouldn't be editable during initialisation*/
    if (panner_getCodecStatus(hPan)==CODEC_STATUS_INITIALISING){
        if(SL_spread->isEnabled())
            SL_spread->setEnabled(false);
        if(CBsourceDirsPreset->isEnabled())
            CBsourceDirsPreset->setEnabled(false);
        if(SL_num_sources->isEnabled())
            SL_num_sources->setEnabled(false);
        if(SL_pValue->isEnabled())
            SL_pValue->setEnabled(false);
        if(CBsLoudspeakerDirsPreset->isEnabled())
            CBsLoudspeakerDirsPreset->setEnabled(false);
        if(SL_num_loudspeakers->isEnabled())
            SL_num_loudspeakers->setEnabled(false);
        if(tb_loadJSON_src->isEnabled())
            tb_loadJSON_src->setEnabled(false);
        if(tb_loadJSON_ls->isEnabled())
            tb_loadJSON_ls->setEnabled(false);
        if(loudspeakerCoordsVP->isEnabled())
            loudspeakerCoordsVP->setEnabled(false);
    }
    else{
        if(processor.getIsPlaying())
            SL_spread->setEnabled(false);
        else if(!SL_spread->isEnabled())
            SL_spread->setEnabled(true);
        if(!CBsourceDirsPreset->isEnabled())
            CBsourceDirsPreset->setEnabled(true);
        if(!SL_num_sources->isEnabled())
            SL_num_sources->setEnabled(true);
        if(!SL_pValue->isEnabled())
            SL_pValue->setEnabled(true);
        if(!CBsLoudspeakerDirsPreset->isEnabled())
            CBsLoudspeakerDirsPreset->setEnabled(true);
        if(processor.getIsPlaying())
            SL_num_loudspeakers->setEnabled(false);
        else if(!SL_num_loudspeakers->isEnabled())
            SL_num_loudspeakers->setEnabled(true);
        if(!tb_loadJSON_src->isEnabled())
            tb_loadJSON_src->setEnabled(true);
        if(!tb_loadJSON_ls->isEnabled())
            tb_loadJSON_ls->setEnabled(true);
        if(!loudspeakerCoordsVP->isEnabled())
            loudspeakerCoordsVP->setEnabled(true);
    }

    /* refresh pan view */
    if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) || processor.getRefreshWindow()){
        panWindow->refreshPanView();
        refreshPanViewWindow = false;
        processor.setRefreshWindow(false);
    }

    /* display warning message, if needed */
    if ((processor.getCurrentBlockSize() % panner_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumInputs() < panner_getNumSources(hPan))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumOutputs() < panner_getNumLoudspeakers(hPan))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if (processor.getBusHasLFE()){
        currentWarning = k_warning_busContainsLFE;
        repaint(0,0,getWidth(),32);
    }
    else if ( !((panner_getDAWsamplerate(hPan) == 44.1e3) || (panner_getDAWsamplerate(hPan) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}
