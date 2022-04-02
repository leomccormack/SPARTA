/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter), progressbar(progress)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    CBsourceDirsPreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBsourceDirsPreset.get());
    CBsourceDirsPreset->setEditableText (false);
    CBsourceDirsPreset->setJustificationType (juce::Justification::centredLeft);
    CBsourceDirsPreset->setTextWhenNothingSelected (juce::String());
    CBsourceDirsPreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBsourceDirsPreset->addListener (this);

    CBsourceDirsPreset->setBounds (88, 66, 112, 20);

    SL_num_sources.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_sources.get());
    SL_num_sources->setRange (1, 64, 1);
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

    SL_pValue.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_pValue.get());
    SL_pValue->setRange (0, 1, 0.01);
    SL_pValue->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_pValue->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    SL_pValue->addListener (this);

    SL_pValue->setBounds (309, 351, 48, 18);

    CBsLoudspeakerDirsPreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBsLoudspeakerDirsPreset.get());
    CBsLoudspeakerDirsPreset->setEditableText (false);
    CBsLoudspeakerDirsPreset->setJustificationType (juce::Justification::centredLeft);
    CBsLoudspeakerDirsPreset->setTextWhenNothingSelected (juce::String());
    CBsLoudspeakerDirsPreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBsLoudspeakerDirsPreset->addListener (this);

    CBsLoudspeakerDirsPreset->setBounds (788, 66, 112, 20);

    SL_num_loudspeakers.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_loudspeakers.get());
    SL_num_loudspeakers->setRange (2, 64, 1);
    SL_num_loudspeakers->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_loudspeakers->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_loudspeakers->addListener (this);

    SL_num_loudspeakers->setBounds (860, 94, 40, 20);

    tb_loadJSON_src.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_loadJSON_src.get());
    tb_loadJSON_src->setButtonText (TRANS("Import"));
    tb_loadJSON_src->setConnectedEdges (juce::Button::ConnectedOnRight);
    tb_loadJSON_src->addListener (this);
    tb_loadJSON_src->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff14889e));

    tb_loadJSON_src->setBounds (140, 41, 34, 14);

    tb_saveJSON_src.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON_src.get());
    tb_saveJSON_src->setButtonText (TRANS("Export"));
    tb_saveJSON_src->setConnectedEdges (juce::Button::ConnectedOnLeft);
    tb_saveJSON_src->addListener (this);
    tb_saveJSON_src->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff224d97));
    tb_saveJSON_src->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff181f9a));

    tb_saveJSON_src->setBounds (174, 41, 34, 14);

    tb_loadJSON_ls.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_loadJSON_ls.get());
    tb_loadJSON_ls->setButtonText (TRANS("Import"));
    tb_loadJSON_ls->setConnectedEdges (juce::Button::ConnectedOnRight);
    tb_loadJSON_ls->addListener (this);
    tb_loadJSON_ls->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff14889e));

    tb_loadJSON_ls->setBounds (712, 41, 34, 14);

    tb_saveJSON_ls.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON_ls.get());
    tb_saveJSON_ls->setButtonText (TRANS("Export"));
    tb_saveJSON_ls->setConnectedEdges (juce::Button::ConnectedOnLeft);
    tb_saveJSON_ls->addListener (this);
    tb_saveJSON_ls->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff224d97));
    tb_saveJSON_ls->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff181f9a));

    tb_saveJSON_ls->setBounds (746, 41, 34, 14);

    SL_spread.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_spread.get());
    SL_spread->setRange (0, 90, 1);
    SL_spread->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_spread->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    SL_spread->addListener (this);

    SL_spread->setBounds (309, 319, 48, 18);

    s_yaw.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_yaw.get());
    s_yaw->setRange (-180, 180, 0.01);
    s_yaw->setSliderStyle (juce::Slider::LinearBar);
    s_yaw->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 14);
    s_yaw->setColour (juce::Slider::trackColourId, juce::Colour (0xff25637e));
    s_yaw->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_yaw->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_yaw->addListener (this);

    s_yaw->setBounds (373, 333, 63, 18);

    t_flipYaw.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipYaw.get());
    t_flipYaw->setButtonText (juce::String());
    t_flipYaw->addListener (this);

    t_flipYaw->setBounds (406, 352, 23, 24);

    t_flipPitch.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipPitch.get());
    t_flipPitch->setButtonText (juce::String());
    t_flipPitch->addListener (this);

    t_flipPitch->setBounds (473, 352, 23, 24);

    t_flipRoll.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipRoll.get());
    t_flipRoll->setButtonText (juce::String());
    t_flipRoll->addListener (this);

    t_flipRoll->setBounds (538, 352, 23, 24);

    s_pitch.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_pitch.get());
    s_pitch->setRange (-90, 90, 0.01);
    s_pitch->setSliderStyle (juce::Slider::LinearBar);
    s_pitch->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 14);
    s_pitch->setColour (juce::Slider::trackColourId, juce::Colour (0xff25637e));
    s_pitch->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_pitch->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_pitch->addListener (this);

    s_pitch->setBounds (440, 333, 63, 18);

    s_roll.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_roll.get());
    s_roll->setRange (-90, 90, 0.01);
    s_roll->setSliderStyle (juce::Slider::LinearBar);
    s_roll->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 14);
    s_roll->setColour (juce::Slider::trackColourId, juce::Colour (0xff25637e));
    s_roll->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_roll->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_roll->addListener (this);

    s_roll->setBounds (507, 333, 63, 18);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (920, 386);


    //[Constructor] You can add your own custom stuff here..

    /* handle to pluginProcessor */
	hVst = ownerFilter;
    hPan = hVst->getFXHandle();

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    LAF.setDefaultColours();
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
    sourceCoordsView_handle = new inputCoordsView(ownerFilter, MAX_NUM_INPUTS, panner_getNumSources(hPan));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(22, 153, 184, 210);
    sourceCoordsView_handle->setNCH(panner_getNumSources(hPan));

    /* loudspeaker coordinates viewport */
    loudspeakerCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (loudspeakerCoordsVP.get());
    loudspeakerCoordsView_handle = new outputCoordsView(ownerFilter, MAX_NUM_OUTPUTS, panner_getNumLoudspeakers(hPan));
    loudspeakerCoordsVP->setViewedComponent (loudspeakerCoordsView_handle);
    loudspeakerCoordsVP->setScrollBarsShown (true, false);
    loudspeakerCoordsVP->setAlwaysOnTop(true);
    loudspeakerCoordsVP->setBounds(722, 153, 184, 210);
    loudspeakerCoordsView_handle->setNCH(panner_getNumLoudspeakers(hPan));

    /* grab current parameter settings */
    SL_num_sources->setValue(panner_getNumSources(hPan),dontSendNotification);
    TB_showInputs->setToggleState(true, dontSendNotification);
    TB_showOutputs->setToggleState(true, dontSendNotification);
    SL_pValue->setValue(panner_getDTT(hPan), dontSendNotification);
    SL_spread->setRange(PANNER_SPREAD_MIN_VALUE, PANNER_SPREAD_MAX_VALUE, 0.01f);
    SL_spread->setValue(panner_getSpread(hPan), dontSendNotification);
    s_yaw->setValue(panner_getYaw(hPan), dontSendNotification);
    s_pitch->setValue(panner_getPitch(hPan), dontSendNotification);
    s_roll->setValue(panner_getRoll(hPan), dontSendNotification);
    t_flipYaw->setToggleState((bool)panner_getFlipYaw(hPan), dontSendNotification);
    t_flipPitch->setToggleState((bool)panner_getFlipPitch(hPan), dontSendNotification);
    t_flipRoll->setToggleState((bool)panner_getFlipRoll(hPan), dontSendNotification);

    /* create panning window */
    panWindow.reset (new pannerView(ownerFilter, 480, 240));
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
    startTimer(TIMER_GUI_RELATED, 40);

    /* warnings */
    currentWarning = k_warning_none;

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

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


    //[Destructor]. You can add your own custom destruction code here..
    setLookAndFeel(nullptr);
    sourceCoordsVP = nullptr;
    loudspeakerCoordsVP = nullptr;
    panWindow = nullptr;
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 208, width = 920, height = 178;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
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
        float x = 1.0f, y = 2.0f, width = 918.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
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
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 366, y = 308, width = 211, height = 68;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 220, y = 308, width = 147, height = 68;
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
        int x = 12, y = 58, width = 196, height = 64;
        juce::Colour fillColour = juce::Colour (0x13f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 23, y = 58, width = 67, height = 30;
        juce::String text (TRANS("Presets: "));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 220, y = 58, width = 480, height = 240;
        juce::Colour fillColour = juce::Colour (0x13f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 121, width = 196, height = 255;
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
        int x = 576, y = 308, width = 124, height = 68;
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
        int x = 712, y = 58, width = 196, height = 64;
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
        int x = 712, y = 121, width = 196, height = 255;
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
        int x = 23, y = 88, width = 145, height = 30;
        juce::String text (TRANS("Number of Inputs:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 84, y = 32, width = 113, height = 30;
        juce::String text (TRANS("Inputs"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 789, y = 32, width = 113, height = 30;
        juce::String text (TRANS("Outputs"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 404, y = 32, width = 156, height = 30;
        juce::String text (TRANS("Panning Window"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 587, y = 314, width = 132, height = 30;
        juce::String text (TRANS("Show Inputs:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 587, y = 346, width = 132, height = 30;
        juce::String text (TRANS("Show Outputs:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 227, y = 338, width = 123, height = 30;
        juce::String text (TRANS("Room coeff:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 723, y = 58, width = 67, height = 30;
        juce::String text (TRANS("Presets: "));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 723, y = 88, width = 157, height = 30;
        juce::String text (TRANS("Number of Outputs:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 1, width = 100, height = 32;
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
        int x = 92, y = 1, width = 112, height = 32;
        juce::String text (TRANS("Panner"));
        juce::Colour fillColour = juce::Colour (0xff0eff00);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 227, y = 313, width = 123, height = 30;
        juce::String text (juce::CharPointer_UTF8 ("Spread (\xc2\xb0):"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 228, y = 354, width = 108, height = 24;
        juce::String text (TRANS("(0: Wet, 1: Dry)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (10.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 66, y = 122, width = 108, height = 28;
        juce::String text (juce::CharPointer_UTF8 ("Azi\xc2\xb0   #   Elev\xc2\xb0"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 767, y = 122, width = 108, height = 28;
        juce::String text (juce::CharPointer_UTF8 ("Azi\xc2\xb0   #   Elev\xc2\xb0"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 451, y = 306, width = 46, height = 30;
        juce::String text (TRANS("Pitch"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 515, y = 306, width = 54, height = 30;
        juce::String text (TRANS("Roll"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 376, y = 306, width = 58, height = 30;
        juce::String text (TRANS("Yaw"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 495, y = 350, width = 63, height = 26;
        juce::String text (TRANS("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 362, y = 350, width = 63, height = 26;
        juce::String text (TRANS("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 429, y = 350, width = 63, height = 26;
        juce::String text (TRANS("+/-"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (13.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 0, y = 0, width = 922, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 386;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 918, y = 0, width = 2, height = 386;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 922, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 384, width = 922, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		175, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(panner_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(panner_getDAWsamplerate(hPan)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(panner_getNumSources(hPan)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(panner_getNumLoudspeakers(hPan)) + TRANS(")"),
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

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBsourceDirsPreset.get())
    {
        //[UserComboBoxCode_CBsourceDirsPreset] -- add your combo box handling code here..
        panner_setInputConfigPreset(hPan, CBsourceDirsPreset->getSelectedId());
        refreshPanViewWindow = true;
        //[/UserComboBoxCode_CBsourceDirsPreset]
    }
    else if (comboBoxThatHasChanged == CBsLoudspeakerDirsPreset.get())
    {
        //[UserComboBoxCode_CBsLoudspeakerDirsPreset] -- add your combo box handling code here..
        panner_setOutputConfigPreset(hPan, CBsLoudspeakerDirsPreset->getSelectedId());
        refreshPanViewWindow = true;
        //[/UserComboBoxCode_CBsLoudspeakerDirsPreset]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == SL_num_sources.get())
    {
        //[UserSliderCode_SL_num_sources] -- add your slider handling code here..
        panner_setNumSources(hPan, (int)SL_num_sources->getValue());
        refreshPanViewWindow = true;
        //[/UserSliderCode_SL_num_sources]
    }
    else if (sliderThatWasMoved == SL_pValue.get())
    {
        //[UserSliderCode_SL_pValue] -- add your slider handling code here..
        panner_setDTT(hPan, (float)SL_pValue->getValue());
        //[/UserSliderCode_SL_pValue]
    }
    else if (sliderThatWasMoved == SL_num_loudspeakers.get())
    {
        //[UserSliderCode_SL_num_loudspeakers] -- add your slider handling code here..
        panner_setNumLoudspeakers(hPan, (int)SL_num_loudspeakers->getValue());
        //[/UserSliderCode_SL_num_loudspeakers]
    }
    else if (sliderThatWasMoved == SL_spread.get())
    {
        //[UserSliderCode_SL_spread] -- add your slider handling code here..
        panner_setSpread(hPan, (float)SL_spread->getValue());
        //[/UserSliderCode_SL_spread]
    }
    else if (sliderThatWasMoved == s_yaw.get())
    {
        //[UserSliderCode_s_yaw] -- add your slider handling code here..
        panner_setYaw(hPan, (float)s_yaw->getValue());
        //[/UserSliderCode_s_yaw]
    }
    else if (sliderThatWasMoved == s_pitch.get())
    {
        //[UserSliderCode_s_pitch] -- add your slider handling code here..
        panner_setPitch(hPan, (float)s_pitch->getValue());
        //[/UserSliderCode_s_pitch]
    }
    else if (sliderThatWasMoved == s_roll.get())
    {
        //[UserSliderCode_s_roll] -- add your slider handling code here..
        panner_setRoll(hPan, (float)s_roll->getValue());
        //[/UserSliderCode_s_roll]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == TB_showInputs.get())
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
    else if (buttonThatWasClicked == tb_loadJSON_src.get())
    {
        //[UserButtonCode_tb_loadJSON_src] -- add your button handler code here..
        chooser = std::make_unique<juce::FileChooser> ("Load configuration...",
                                                       hVst->getLastDir().exists() ? hVst->getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                                                       "*.json");
        auto chooserFlags = juce::FileBrowserComponent::openMode
                                  | juce::FileBrowserComponent::canSelectFiles;
        chooser->launchAsync (chooserFlags, [this] (const FileChooser& fc) {
            auto file = fc.getResult();
            if (file != File{}){
                hVst->setLastDir(file.getParentDirectory());
                hVst->loadConfiguration (file,0);
            }
        });
        //[/UserButtonCode_tb_loadJSON_src]
    }
    else if (buttonThatWasClicked == tb_saveJSON_src.get())
    {
        //[UserButtonCode_tb_saveJSON_src] -- add your button handler code here..
        chooser = std::make_unique<juce::FileChooser> ("Save configuration...",
                                                       hVst->getLastDir().exists() ? hVst->getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                                                       "*.json");
        auto chooserFlags = juce::FileBrowserComponent::saveMode;
        chooser->launchAsync (chooserFlags, [this] (const FileChooser& fc) {
            auto file = fc.getResult();
            if (file != File{}) {
                hVst->setLastDir(file.getParentDirectory());
                hVst->saveConfigurationToFile (file,0);
            }
        });
        //[/UserButtonCode_tb_saveJSON_src]
    }
    else if (buttonThatWasClicked == tb_loadJSON_ls.get())
    {
        //[UserButtonCode_tb_loadJSON_ls] -- add your button handler code here..
        chooser = std::make_unique<juce::FileChooser> ("Load configuration...",
                                                       hVst->getLastDir().exists() ? hVst->getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                                                       "*.json");
        auto chooserFlags = juce::FileBrowserComponent::openMode
                                  | juce::FileBrowserComponent::canSelectFiles;
        chooser->launchAsync (chooserFlags, [this] (const FileChooser& fc) {
            auto file = fc.getResult();
            if (file != File{}){
                hVst->setLastDir(file.getParentDirectory());
                hVst->loadConfiguration (file,1);
            }
        });
        //[/UserButtonCode_tb_loadJSON_ls]
    }
    else if (buttonThatWasClicked == tb_saveJSON_ls.get())
    {
        //[UserButtonCode_tb_saveJSON_ls] -- add your button handler code here..
        chooser = std::make_unique<juce::FileChooser> ("Save configuration...",
                                                       hVst->getLastDir().exists() ? hVst->getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                                                       "*.json");
        auto chooserFlags = juce::FileBrowserComponent::saveMode;
        chooser->launchAsync (chooserFlags, [this] (const FileChooser& fc) {
            auto file = fc.getResult();
            if (file != File{}) {
                hVst->setLastDir(file.getParentDirectory());
                hVst->saveConfigurationToFile (file,1);
            }
        });
        //[/UserButtonCode_tb_saveJSON_ls]
    }
    else if (buttonThatWasClicked == t_flipYaw.get())
    {
        //[UserButtonCode_t_flipYaw] -- add your button handler code here..
        panner_setFlipYaw(hPan, (int)t_flipYaw->getToggleState());
        //[/UserButtonCode_t_flipYaw]
    }
    else if (buttonThatWasClicked == t_flipPitch.get())
    {
        //[UserButtonCode_t_flipPitch] -- add your button handler code here..
        panner_setFlipPitch(hPan, (int)t_flipPitch->getToggleState());
        //[/UserButtonCode_t_flipPitch]
    }
    else if (buttonThatWasClicked == t_flipRoll.get())
    {
        //[UserButtonCode_t_flipRoll] -- add your button handler code here..
        panner_setFlipRoll(hPan, (int)t_flipRoll->getToggleState());
        //[/UserButtonCode_t_flipRoll]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback(int timerID)
{
    switch(timerID){
        case TIMER_PROCESSING_RELATED:
            /* handled in PluginProcessor */
            break;

        case TIMER_GUI_RELATED:
            /* refresh parameters that can change internally */
            sourceCoordsView_handle->setNCH(panner_getNumSources(hPan));
            loudspeakerCoordsView_handle->setNCH(panner_getNumLoudspeakers(hPan));
            SL_num_sources->setValue(panner_getNumSources(hPan),dontSendNotification);
            SL_num_loudspeakers->setValue(panner_getNumLoudspeakers(hPan),dontSendNotification);
            s_yaw->setValue(panner_getYaw(hPan), dontSendNotification);
            s_pitch->setValue(panner_getPitch(hPan), dontSendNotification);
            s_roll->setValue(panner_getRoll(hPan), dontSendNotification);


            /* Progress bar */
#if 0
            if(panner_getCodecStatus(hPan)==CODEC_STATUS_INITIALISING){
                addAndMakeVisible(progressbar);
                progress = (double)panner_getProgressBar0_1(hPan);
                char text[PANNER_PROGRESSBARTEXT_CHAR_LENGTH];
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
                if(hVst->getIsPlaying())
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
                if(hVst->getIsPlaying())
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
            if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) ||
               sourceCoordsView_handle->getHasASliderChanged() || loudspeakerCoordsView_handle->getHasASliderChanged() || hVst->getRefreshWindow()){
                panWindow->refreshPanView();
                refreshPanViewWindow = false;
                sourceCoordsView_handle->setHasASliderChange(false);
                loudspeakerCoordsView_handle->setHasASliderChange(false);
                hVst->setRefreshWindow(false);
            }

            /* display warning message, if needed */
            if ((hVst->getCurrentBlockSize() % panner_getFrameSize()) != 0){
                currentWarning = k_warning_frameSize;
                repaint(0,0,getWidth(),32);
            }
            else if ( !((panner_getDAWsamplerate(hPan) == 44.1e3) || (panner_getDAWsamplerate(hPan) == 48e3)) ){
                currentWarning = k_warning_supported_fs;
                repaint(0,0,getWidth(),32);
            }
            else if ((hVst->getCurrentNumInputs() < panner_getNumSources(hPan))){
                currentWarning = k_warning_NinputCH;
                repaint(0,0,getWidth(),32);
            }
            else if ((hVst->getCurrentNumOutputs() < panner_getNumLoudspeakers(hPan))){
                currentWarning = k_warning_NoutputCH;
                repaint(0,0,getWidth(),32);
            }
            else if(currentWarning){
                currentWarning = k_warning_none;
                repaint(0,0,getWidth(),32);
            }
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
                 parentClasses="public AudioProcessorEditor, public MultiTimer"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter), progressbar(progress)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="920" initialHeight="386">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 208 920 178" fill="linear: 8 384, 8 304, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="0 30 920 178" fill="linear: 8 32, 8 104, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <ROUNDRECT pos="1 2 918 31" cornerSize="5.0" fill="linear: 0 32, 912 24, 0=ff041518, 1=ff19313f"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="366 308 211 68" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="366 308 211 68" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="220 308 147 68" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 58 196 64" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="23 58 67 30" fill="solid: ffffffff" hasStroke="0" text="Presets: "
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="220 58 480 240" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 121 196 255" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="576 308 124 68" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="712 58 196 64" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="712 121 196 255" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="23 88 145 30" fill="solid: ffffffff" hasStroke="0" text="Number of Inputs:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="84 32 113 30" fill="solid: ffffffff" hasStroke="0" text="Inputs"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="789 32 113 30" fill="solid: ffffffff" hasStroke="0" text="Outputs"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="404 32 156 30" fill="solid: ffffffff" hasStroke="0" text="Panning Window"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="587 314 132 30" fill="solid: ffffffff" hasStroke="0" text="Show Inputs:"
          fontname="Default font" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="587 346 132 30" fill="solid: ffffffff" hasStroke="0" text="Show Outputs:"
          fontname="Default font" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="227 338 123 30" fill="solid: ffffffff" hasStroke="0" text="Room coeff:"
          fontname="Default font" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="723 58 67 30" fill="solid: ffffffff" hasStroke="0" text="Presets: "
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="723 88 157 30" fill="solid: ffffffff" hasStroke="0" text="Number of Outputs:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 112 32" fill="solid: ff0eff00" hasStroke="0" text="Panner"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="227 313 123 30" fill="solid: ffffffff" hasStroke="0" text="Spread (&#176;):"
          fontname="Default font" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="228 354 108 24" fill="solid: ffffffff" hasStroke="0" text="(0: Wet, 1: Dry)"
          fontname="Default font" fontsize="10.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="66 122 108 28" fill="solid: ffffffff" hasStroke="0" text="Azi&#176;   #   Elev&#176;"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="767 122 108 28" fill="solid: ffffffff" hasStroke="0" text="Azi&#176;   #   Elev&#176;"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="451 306 46 30" fill="solid: ffffffff" hasStroke="0" text="Pitch"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="515 306 54 30" fill="solid: ffffffff" hasStroke="0" text="Roll"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="376 306 58 30" fill="solid: ffffffff" hasStroke="0" text="Yaw"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="495 350 63 26" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="362 350 63 26" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="429 350 63 26" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="13.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="0 0 922 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 386" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="918 0 2 386" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 922 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 384 922 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
  </BACKGROUND>
  <COMBOBOX name="new combo box" id="5a2f99f88aa51390" memberName="CBsourceDirsPreset"
            virtualName="" explicitFocusOrder="0" pos="88 66 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="2c2a2b3d0614cc94" memberName="SL_num_sources"
          virtualName="" explicitFocusOrder="0" pos="152 94 48 20" min="1.0"
          max="64.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="74817bb8a57611dc" memberName="TB_showInputs"
                virtualName="" explicitFocusOrder="0" pos="672 317 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="1a1dfbb1d4296140" memberName="TB_showOutputs"
                virtualName="" explicitFocusOrder="0" pos="672 349 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="new slider" id="5b4f982e7ea9b2d5" memberName="SL_pValue"
          virtualName="" explicitFocusOrder="0" pos="309 351 48 18" min="0.0"
          max="1.0" int="0.01" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="cfd23f574e19957c" memberName="CBsLoudspeakerDirsPreset"
            virtualName="" explicitFocusOrder="0" pos="788 66 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="cbb243fa14b960d0" memberName="SL_num_loudspeakers"
          virtualName="" explicitFocusOrder="0" pos="860 94 40 20" min="2.0"
          max="64.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TEXTBUTTON name="new button" id="527e24c6748d02d4" memberName="tb_loadJSON_src"
              virtualName="" explicitFocusOrder="0" pos="140 41 34 14" bgColOff="ff14889e"
              buttonText="Import" connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="48c5d3526dcfe64f" memberName="tb_saveJSON_src"
              virtualName="" explicitFocusOrder="0" pos="174 41 34 14" bgColOff="ff224d97"
              bgColOn="ff181f9a" buttonText="Export" connectedEdges="1" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="9e16f5d467ae2a3b" memberName="tb_loadJSON_ls"
              virtualName="" explicitFocusOrder="0" pos="712 41 34 14" bgColOff="ff14889e"
              buttonText="Import" connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="87186d3e46663c48" memberName="tb_saveJSON_ls"
              virtualName="" explicitFocusOrder="0" pos="746 41 34 14" bgColOff="ff224d97"
              bgColOn="ff181f9a" buttonText="Export" connectedEdges="1" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="new slider" id="502f78257b11f666" memberName="SL_spread"
          virtualName="" explicitFocusOrder="0" pos="309 319 48 18" min="0.0"
          max="90.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="ace036a85eec9703" memberName="s_yaw" virtualName=""
          explicitFocusOrder="0" pos="373 333 63 18" trackcol="ff25637e"
          textboxtext="ffffffff" textboxbkgd="ffffff" min="-180.0" max="180.0"
          int="0.01" style="LinearBar" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="58" textBoxHeight="14" skewFactor="1.0" needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="ac47b63592b1d4cf" memberName="t_flipYaw"
                virtualName="" explicitFocusOrder="0" pos="406 352 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="c58241ee52766d62" memberName="t_flipPitch"
                virtualName="" explicitFocusOrder="0" pos="473 352 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="717e9536768dfd8c" memberName="t_flipRoll"
                virtualName="" explicitFocusOrder="0" pos="538 352 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="new slider" id="392ca672356bf48a" memberName="s_pitch"
          virtualName="" explicitFocusOrder="0" pos="440 333 63 18" trackcol="ff25637e"
          textboxtext="ffffffff" textboxbkgd="ffffff" min="-90.0" max="90.0"
          int="0.01" style="LinearBar" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="58" textBoxHeight="14" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="d066861bf0a08264" memberName="s_roll" virtualName=""
          explicitFocusOrder="0" pos="507 333 63 18" trackcol="ff25637e"
          textboxtext="ffffffff" textboxbkgd="ffffff" min="-90.0" max="90.0"
          int="0.01" style="LinearBar" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="58" textBoxHeight="14" skewFactor="1.0" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

