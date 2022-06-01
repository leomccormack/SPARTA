/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.4

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
    : AudioProcessorEditor(ownerFilter), progressbar(progress), fileChooser ("File", File(), true, false, false,
      "*.sofa;*.nc;", String(),
      "Load SOFA File")
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    CBoutputDirsPreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBoutputDirsPreset.get());
    CBoutputDirsPreset->setEditableText (false);
    CBoutputDirsPreset->setJustificationType (juce::Justification::centredLeft);
    CBoutputDirsPreset->setTextWhenNothingSelected (TRANS("Default"));
    CBoutputDirsPreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBoutputDirsPreset->addItem (TRANS("Default"), 1);
    CBoutputDirsPreset->addListener (this);

    CBoutputDirsPreset->setBounds (520, 64, 112, 20);

    SL_num_loudspeakers.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_loudspeakers.get());
    SL_num_loudspeakers->setRange (1, 64, 1);
    SL_num_loudspeakers->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_loudspeakers->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_loudspeakers->addListener (this);

    SL_num_loudspeakers->setBounds (592, 92, 40, 20);

    TBuseDefaultHRIRs.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBuseDefaultHRIRs.get());
    TBuseDefaultHRIRs->setButtonText (juce::String());
    TBuseDefaultHRIRs->addListener (this);

    TBuseDefaultHRIRs->setBounds (409, 91, 24, 24);

    CBsourcePreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBsourcePreset.get());
    CBsourcePreset->setEditableText (false);
    CBsourcePreset->setJustificationType (juce::Justification::centredLeft);
    CBsourcePreset->setTextWhenNothingSelected (TRANS("Default"));
    CBsourcePreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBsourcePreset->addItem (TRANS("Ideal SH"), 1);
    CBsourcePreset->addListener (this);

    CBsourcePreset->setBounds (99, 96, 118, 20);

    CBchFormat.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (juce::Justification::centredLeft);
    CBchFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBchFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBchFormat->addListener (this);

    CBchFormat->setBounds (129, 120, 88, 20);

    CBnormScheme.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (juce::Justification::centredLeft);
    CBnormScheme->setTextWhenNothingSelected (TRANS("N3D"));
    CBnormScheme->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnormScheme->addListener (this);

    CBnormScheme->setBounds (129, 144, 88, 20);

    SL_transitionFreq.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_transitionFreq.get());
    SL_transitionFreq->setRange (500, 2000, 0.1);
    SL_transitionFreq->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_transitionFreq->setTextBoxStyle (juce::Slider::TextBoxAbove, false, 60, 20);
    SL_transitionFreq->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    SL_transitionFreq->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    SL_transitionFreq->addListener (this);

    SL_transitionFreq->setBounds (168, 305, 112, 40);

    CBdec1method.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBdec1method.get());
    CBdec1method->setEditableText (false);
    CBdec1method->setJustificationType (juce::Justification::centredLeft);
    CBdec1method->setTextWhenNothingSelected (TRANS("Default"));
    CBdec1method->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBdec1method->addListener (this);

    CBdec1method->setBounds (24, 297, 116, 20);

    CBdec2method.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBdec2method.get());
    CBdec2method->setEditableText (false);
    CBdec2method->setJustificationType (juce::Justification::centredLeft);
    CBdec2method->setTextWhenNothingSelected (TRANS("Default"));
    CBdec2method->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBdec2method->addListener (this);

    CBdec2method->setBounds (308, 297, 116, 20);

    TBdec1EnableMaxrE.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBdec1EnableMaxrE.get());
    TBdec1EnableMaxrE->setButtonText (juce::String());
    TBdec1EnableMaxrE->addListener (this);

    TBdec1EnableMaxrE->setBounds (120, 321, 32, 24);

    TBdec2EnableMaxrE.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBdec2EnableMaxrE.get());
    TBdec2EnableMaxrE->setButtonText (juce::String());
    TBdec2EnableMaxrE->addListener (this);

    TBdec2EnableMaxrE->setBounds (404, 321, 32, 24);

    CBdec1normtype.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBdec1normtype.get());
    CBdec1normtype->setEditableText (false);
    CBdec1normtype->setJustificationType (juce::Justification::centredLeft);
    CBdec1normtype->setTextWhenNothingSelected (TRANS("EP"));
    CBdec1normtype->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBdec1normtype->addListener (this);

    CBdec1normtype->setBounds (24, 323, 52, 20);

    TBBinauraliseLS.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBBinauraliseLS.get());
    TBBinauraliseLS->setButtonText (juce::String());
    TBBinauraliseLS->addListener (this);

    TBBinauraliseLS->setBounds (409, 62, 24, 24);

    CBdec2normtype.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBdec2normtype.get());
    CBdec2normtype->setEditableText (false);
    CBdec2normtype->setJustificationType (juce::Justification::centredLeft);
    CBdec2normtype->setTextWhenNothingSelected (TRANS("EP"));
    CBdec2normtype->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBdec2normtype->addListener (this);

    CBdec2normtype->setBounds (308, 323, 52, 20);

    s_decOrder.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_decOrder.get());
    s_decOrder->setRange (0, 1, 1);
    s_decOrder->setSliderStyle (juce::Slider::LinearVertical);
    s_decOrder->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    s_decOrder->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_decOrder->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    s_decOrder->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_decOrder->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_decOrder->addListener (this);

    s_decOrder->setBounds (384, 185, 40, 80);

    tb_loadJSON.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_loadJSON.get());
    tb_loadJSON->setButtonText (TRANS("Import"));
    tb_loadJSON->setConnectedEdges (juce::Button::ConnectedOnRight);
    tb_loadJSON->addListener (this);
    tb_loadJSON->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff14889e));

    tb_loadJSON->setBounds (447, 40, 34, 14);

    tb_saveJSON.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON.get());
    tb_saveJSON->setButtonText (TRANS("Export"));
    tb_saveJSON->setConnectedEdges (juce::Button::ConnectedOnLeft);
    tb_saveJSON->addListener (this);
    tb_saveJSON->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff224d97));
    tb_saveJSON->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff181f9a));

    tb_saveJSON->setBounds (481, 40, 34, 14);

    CBmasterOrder.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBmasterOrder.get());
    CBmasterOrder->setEditableText (false);
    CBmasterOrder->setJustificationType (juce::Justification::centredLeft);
    CBmasterOrder->setTextWhenNothingSelected (TRANS("Default"));
    CBmasterOrder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBmasterOrder->addListener (this);

    CBmasterOrder->setBounds (99, 65, 118, 20);

    TBenablePreProc.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBenablePreProc.get());
    TBenablePreProc->setTooltip (TRANS("Enable HRIR Pre-Processing"));
    TBenablePreProc->setButtonText (juce::String());
    TBenablePreProc->addListener (this);

    TBenablePreProc->setBounds (409, 143, 24, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (656, 365);


    //[Constructor] You can add your own custom stuff here..

    /* handle to pluginProcessor */
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

    /* remove slider bit of these sliders */
    SL_num_loudspeakers->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_loudspeakers->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_loudspeakers->setSliderSnapsToMousePosition(false);

    /* create 2d Slider for the decoding order parameter */
    int nPoints;
    float* pX_vector;
    int* pY_values_int;
    decOrder2dSlider.reset (new log2dSlider(360, 63, 100, 20e3, 1, ambi_dec_getMasterDecOrder(hAmbi), 0));
    addAndMakeVisible (decOrder2dSlider.get());
    decOrder2dSlider->setAlwaysOnTop(true);
    decOrder2dSlider->setTopLeftPosition(25, 192);
    ambi_dec_getDecOrderHandle(hAmbi, &pX_vector, &pY_values_int, &nPoints);
    decOrder2dSlider->setDataHandlesInt(pX_vector, pY_values_int, nPoints);

    /* add master decoding order options */
    CBmasterOrder->addItem (TRANS("1st order"), SH_ORDER_FIRST);
    CBmasterOrder->addItem (TRANS("2nd order"), SH_ORDER_SECOND);
    CBmasterOrder->addItem (TRANS("3rd order"), SH_ORDER_THIRD);
    CBmasterOrder->addItem (TRANS("4th order"), SH_ORDER_FOURTH);
    CBmasterOrder->addItem (TRANS("5th order"), SH_ORDER_FIFTH);
    CBmasterOrder->addItem (TRANS("6th order"), SH_ORDER_SIXTH);
    CBmasterOrder->addItem (TRANS("7th order"), SH_ORDER_SEVENTH);

    /* add decoder options */
    CBdec1method->addItem(TRANS("SAD"), DECODING_METHOD_SAD);
    CBdec1method->addItem(TRANS("MMD"), DECODING_METHOD_MMD);
    CBdec1method->addItem(TRANS("EPAD"), DECODING_METHOD_EPAD);
    CBdec1method->addItem(TRANS("AllRAD"), DECODING_METHOD_ALLRAD);
    CBdec2method->addItem(TRANS("SAD"), DECODING_METHOD_SAD);
    CBdec2method->addItem(TRANS("MMD"), DECODING_METHOD_MMD);
    CBdec2method->addItem(TRANS("EPAD"), DECODING_METHOD_EPAD);
    CBdec2method->addItem(TRANS("AllRAD"), DECODING_METHOD_ALLRAD);

    /* add diffuse-eq options */
    CBdec1normtype->addItem(TRANS("AP"), AMPLITUDE_PRESERVING);
    CBdec1normtype->addItem(TRANS("EP"), ENERGY_PRESERVING);
    CBdec2normtype->addItem(TRANS("AP"), AMPLITUDE_PRESERVING);
    CBdec2normtype->addItem(TRANS("EP"), ENERGY_PRESERVING);

    /* ambi convention options */
    CBchFormat->addItem (TRANS("ACN"), CH_ACN);
    CBchFormat->addItem (TRANS("FuMa"), CH_FUMA);
    CBnormScheme->addItem (TRANS("N3D"), NORM_N3D);
    CBnormScheme->addItem (TRANS("SN3D"), NORM_SN3D);
    CBnormScheme->addItem (TRANS("FuMa"), NORM_FUMA);

    /* add microphone preset options */
    CBsourcePreset->addItem(TRANS("Zylia"), MIC_PRESET_ZYLIA);
    CBsourcePreset->addItem(TRANS("Eigenmike"), MIC_PRESET_EIGENMIKE32);
    CBsourcePreset->addItem(TRANS("DTU mic"), MIC_PRESET_DTU_MIC);

    /* add loudspeaker preset options */
    CBoutputDirsPreset->addItem (TRANS("5.x"), LOUDSPEAKER_ARRAY_PRESET_5PX);
    CBoutputDirsPreset->addItem (TRANS("7.x"), LOUDSPEAKER_ARRAY_PRESET_7PX);
    CBoutputDirsPreset->addItem (TRANS("8.x"), LOUDSPEAKER_ARRAY_PRESET_8PX);
    CBoutputDirsPreset->addItem (TRANS("9.x"), LOUDSPEAKER_ARRAY_PRESET_9PX);
    CBoutputDirsPreset->addItem (TRANS("10.x"), LOUDSPEAKER_ARRAY_PRESET_10PX);
    CBoutputDirsPreset->addItem (TRANS("11.x"), LOUDSPEAKER_ARRAY_PRESET_11PX);
    CBoutputDirsPreset->addItem (TRANS("11.x (7+4)"), LOUDSPEAKER_ARRAY_PRESET_11PX_7_4);
    CBoutputDirsPreset->addItem (TRANS("13.x"), LOUDSPEAKER_ARRAY_PRESET_13PX);
    CBoutputDirsPreset->addItem (TRANS("22.x"), LOUDSPEAKER_ARRAY_PRESET_22PX);
    CBoutputDirsPreset->addItem (TRANS("Aalto MCC"), LOUDSPEAKER_ARRAY_PRESET_AALTO_MCC);
    CBoutputDirsPreset->addItem (TRANS("Aalto MCC-subset"), LOUDSPEAKER_ARRAY_PRESET_AALTO_MCC_SUBSET);
    CBoutputDirsPreset->addItem (TRANS("Aalto Apaja"), LOUDSPEAKER_ARRAY_PRESET_AALTO_APAJA);
    CBoutputDirsPreset->addItem (TRANS("Aalto LR"), LOUDSPEAKER_ARRAY_PRESET_AALTO_LR);
    CBoutputDirsPreset->addItem (TRANS("DTU AVIL"), LOUDSPEAKER_ARRAY_PRESET_DTU_AVIL);
    CBoutputDirsPreset->addItem (TRANS("Zylia Lab (22.x)"), LOUDSPEAKER_ARRAY_PRESET_ZYLIA_LAB);
    CBoutputDirsPreset->addItem (TRANS("T-design (4)"), LOUDSPEAKER_ARRAY_PRESET_T_DESIGN_4);
    CBoutputDirsPreset->addItem (TRANS("T-design (12)"), LOUDSPEAKER_ARRAY_PRESET_T_DESIGN_12);
    CBoutputDirsPreset->addItem (TRANS("T-design (24)"), LOUDSPEAKER_ARRAY_PRESET_T_DESIGN_24);
    CBoutputDirsPreset->addItem (TRANS("T-design (36)"), LOUDSPEAKER_ARRAY_PRESET_T_DESIGN_36);
    CBoutputDirsPreset->addItem (TRANS("T-design (48)"), LOUDSPEAKER_ARRAY_PRESET_T_DESIGN_48);
    CBoutputDirsPreset->addItem (TRANS("T-design (60)"), LOUDSPEAKER_ARRAY_PRESET_T_DESIGN_60);
    CBoutputDirsPreset->addItem (TRANS("SphCov (9)"), LOUDSPEAKER_ARRAY_PRESET_SPH_COV_9);
    CBoutputDirsPreset->addItem (TRANS("SphCov (16)"), LOUDSPEAKER_ARRAY_PRESET_SPH_COV_16);
    CBoutputDirsPreset->addItem (TRANS("SphCov (25)"), LOUDSPEAKER_ARRAY_PRESET_SPH_COV_25);
    CBoutputDirsPreset->addItem (TRANS("SphCov (49)"), LOUDSPEAKER_ARRAY_PRESET_SPH_COV_49);
    CBoutputDirsPreset->addItem (TRANS("SphCov (64)"), LOUDSPEAKER_ARRAY_PRESET_SPH_COV_64);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

    /* source coordinate viewport */
    outputCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (outputCoordsVP.get());
    outputCoordsView_handle = new outputCoordsView(ownerFilter, MAX_NUM_CHANNELS, ambi_dec_getNumLoudspeakers(hAmbi));
    outputCoordsVP->setViewedComponent (outputCoordsView_handle);
    outputCoordsVP->setScrollBarsShown (true, false);
    outputCoordsVP->setAlwaysOnTop(true);
    outputCoordsVP->setBounds(455, 153, 184, 188);
    outputCoordsView_handle->setNCH(ambi_dec_getNumLoudspeakers(hAmbi));

    /* file loader */
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
    fileChooser.setBounds (232, 118, 196, 20);

    /* grab current parameter settings */
    CBmasterOrder->setSelectedId(ambi_dec_getMasterDecOrder(hAmbi), dontSendNotification);
    TBuseDefaultHRIRs->setToggleState(ambi_dec_getUseDefaultHRIRsflag(hAmbi), dontSendNotification);
    SL_num_loudspeakers->setValue(ambi_dec_getNumLoudspeakers(hAmbi),dontSendNotification);
    CBchFormat->setSelectedId(ambi_dec_getChOrder(hAmbi), dontSendNotification);
    CBnormScheme->setSelectedId(ambi_dec_getNormType(hAmbi), dontSendNotification);
    s_decOrder->setRange(1, ambi_dec_getMasterDecOrder(hAmbi)+0.0001f, 1);
    s_decOrder->setValue(ambi_dec_getDecOrderAllBands(hAmbi), dontSendNotification);
    TBBinauraliseLS->setToggleState(ambi_dec_getBinauraliseLSflag(hAmbi), dontSendNotification);
    CBdec1method->setSelectedId(ambi_dec_getDecMethod(hAmbi, 0), dontSendNotification);
    CBdec2method->setSelectedId(ambi_dec_getDecMethod(hAmbi, 1), dontSendNotification);
    TBdec1EnableMaxrE->setToggleState(ambi_dec_getDecEnableMaxrE(hAmbi, 0), dontSendNotification);
    TBdec2EnableMaxrE->setToggleState(ambi_dec_getDecEnableMaxrE(hAmbi, 1), dontSendNotification);
    CBdec1normtype->setSelectedId(ambi_dec_getDecNormType(hAmbi, 0), dontSendNotification);
    CBdec2normtype->setSelectedId(ambi_dec_getDecNormType(hAmbi, 1), dontSendNotification);
    SL_transitionFreq->setRange(AMBI_DEC_TRANSITION_MIN_VALUE, AMBI_DEC_TRANSITION_MAX_VALUE, 0.1f);
    SL_transitionFreq->setValue(ambi_dec_getTransitionFreq(hAmbi), dontSendNotification);
    CBchFormat->setItemEnabled(CH_FUMA, ambi_dec_getMasterDecOrder(hAmbi)==SH_ORDER_FIRST ? true : false);
    CBnormScheme->setItemEnabled(NORM_FUMA, ambi_dec_getMasterDecOrder(hAmbi)==SH_ORDER_FIRST ? true : false);

    /* tooltips */
    CBmasterOrder->setTooltip("Maximum decoding order (can be lower at different frequencies). Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals as input.");
    TBuseDefaultHRIRs->setTooltip("If this is 'ticked', the plug-in is using the default HRIR set from the Spatial_Audio_Framework.");
    fileChooser.setTooltip("Optionally, a custom HRIR set may be loaded via the SOFA standard. Note that if the plug-in fails to load the specified .sofa file, it will revert to the default HRIR data.");
    SL_num_loudspeakers->setTooltip("Number of loudspeakers to decode to.");
    CBchFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormScheme->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    s_decOrder->setTooltip("This sets the decoding order for all frequencies. Use the 2-D slider to change the decoding order for specific frequencies.");
    TBBinauraliseLS->setTooltip("If enabled, the loudspeaker signals are binauralised and sent to the first 2 output channels. Note that this plug-in also performs phase-simplification of the HRIRs, which involves estimating the ITDs for all the HRIRs, removing the phase from the HRTFs, but then re-introducing the phase as IPDs per frequency-bin. This greatly simplifies the HRIR interpolation process, but note that it will not be the same as direct convolution; although it should be perceptually very close in the majority of cases. However, this also means that BRIRs are not supported.");
    CBdec1method->setTooltip("Decoding method for the low-frequencies. The methods are equivalent if the loudspeakers are uniformly distributed (e.g. a t-design). Sampling Ambisonic Decoder (SAD) is the simplest, as it simply steers a hyper-cardioid beamformer to each loudspeaker direction. Mode-Matching Decoder (MMD), lends more energy to parts of the sphere which are more sparsely populated with loudspeakers (therefore, be careful! as a lot of energy can go to VOG, for example). AllRAD first decodes to a t-design and pans the t-design signals to the loudspeaker set-up using VBAP (most recommended for irregular loudspeaker arrangements).");
    CBdec2method->setTooltip("Decoding method for the high-frequencies. The methods are equivalent if the loudspeakers are uniformly distributed (e.g. a t-design). Sampling Ambisonic Decoder (SAD) is the simplest, as it simply steers a hyper-cardioid beamformer to each loudspeaker direction. Mode-Matching Decoder (MMD), lends more energy to parts of the sphere which are more sparsely populated with loudspeakers (therefore, be careful! as a lot of energy can go to VOG, for example). AllRAD first decodes to a t-design and pans the t-design signals to the loudspeaker set-up using VBAP (most recommended for irregular loudspeaker arrangements).");
    TBdec1EnableMaxrE->setTooltip("Enables/Disables the max_rE weights applied to the low-frequency decoding matrix.");
    TBdec2EnableMaxrE->setTooltip("Enables/Disables the max_rE weights applied to the high-frequency decoding matrix.");
    CBdec1normtype->setTooltip("The plug-in applies a frequency-dependent normalisation factor, which helps preserve omni-directional amplitude or energy when the decoding order differs for different frequencies. Generally, it is recommended to preserve amplitude (AP) at low-frequencies, and preserve high-frequencies (EP) at high-frequencies.");
    CBdec2normtype->setTooltip("The plug-in applies a frequency-dependent normalisation factor, which helps preserve omni-directional amplitude or energy when the decoding order differs for different frequencies. Generally, it is recommended to preserve amplitude (AP) at low-frequencies, and preserve high-frequencies (EP) at high-frequencies.");
    SL_transitionFreq->setTooltip("Sets the frequency at which to transition from the low-frequency decoder, to the high-frequency decoder.");
    CBsourcePreset->setTooltip("Presets for for various higher-order microphone arrays, which configure the frequency-dependent decoding order.");
    CBoutputDirsPreset->setTooltip("Presets for loudspeaker arrangements to decode to.");
    tb_loadJSON->setTooltip("Loads loudspeaker directions from a JSON file. The JSON file format follows the same convention as the one employed by the IEM plugin suite (https://plugins.iem.at/docs/configurationfiles/).");
    tb_saveJSON->setTooltip("Saves the current loudspeaker directions to a JSON file. The JSON file format follows the same convention as the one employed by the IEM plugin suite (https://plugins.iem.at/docs/configurationfiles/).");
    TBenablePreProc->setTooltip("Enables/Disables Diffuse-field EQ of the HRIRs, which is based on a weighted summation of all the HRTF magnitudes in the currently loaded set.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("This plug-in is a linear and time-invariant loudspeaker Ambisonic decoder, which implements a number of different decoder designs. The plug-in employs a dual-decoder approach, whereby different decoding methods may be selected for the low and high frequencies. Additionally, the decoding order may be specified for each individual frequency band, in order to account for imperfect input Ambisonic signals (such as those derived from microphone arrays) or for creative purposes.\n\nAs with most of the SPARTA plugins, the default settings generally represent the \"state-of-the-art\" approach; or at least a configuration that is suitable for the majority of applications. The vast number of configuration options and decoding methods offered by this plug-in are mainly intended for research and educational purposes, but may nevertheless be fun to play around with :-)"));

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

    CBoutputDirsPreset = nullptr;
    SL_num_loudspeakers = nullptr;
    TBuseDefaultHRIRs = nullptr;
    CBsourcePreset = nullptr;
    CBchFormat = nullptr;
    CBnormScheme = nullptr;
    SL_transitionFreq = nullptr;
    CBdec1method = nullptr;
    CBdec2method = nullptr;
    TBdec1EnableMaxrE = nullptr;
    TBdec2EnableMaxrE = nullptr;
    CBdec1normtype = nullptr;
    TBBinauraliseLS = nullptr;
    CBdec2normtype = nullptr;
    s_decOrder = nullptr;
    tb_loadJSON = nullptr;
    tb_saveJSON = nullptr;
    CBmasterOrder = nullptr;
    TBenablePreProc = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    setLookAndFeel(nullptr);
    outputCoordsVP = nullptr;
    decOrder2dSlider = nullptr;
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 30, width = 656, height = 163;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             96.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 1.0f, width = 654.0f, height = 32.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 1.0f + y,
                                             fillColour2,
                                             656.0f - 1.0f + x,
                                             24.0f - 1.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 0, y = 193, width = 656, height = 172;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             360.0f - 193.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             304.0f - 193.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
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
        int x = 12, y = 58, width = 213, height = 111;
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
        int x = 12, y = 58, width = 213, height = 33;
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
        int x = 152, y = 272, width = 145, height = 81;
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
        int x = 296, y = 272, width = 140, height = 81;
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
        int x = 446, y = 121, width = 196, height = 232;
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
        int x = 224, y = 58, width = 212, height = 111;
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
        int x = 446, y = 58, width = 196, height = 64;
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
        int x = 455, y = 58, width = 67, height = 30;
        juce::String text (TRANS("Presets: "));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 12, y = 168, width = 424, height = 105;
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
        int x = 499, y = 122, width = 105, height = 28;
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
        int x = 455, y = 86, width = 169, height = 30;
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
        int x = 524, y = 32, width = 113, height = 30;
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
        int x = 232, y = 87, width = 165, height = 30;
        juce::String text (TRANS("Use Default HRIR set:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 90, width = 132, height = 30;
        juce::String text (TRANS("Mic Preset:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 140, width = 132, height = 30;
        juce::String text (TRANS("Normalisation:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 232, y = 58, width = 189, height = 30;
        juce::String text (TRANS("Binauralise Loudspeakers:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 12, y = 272, width = 141, height = 81;
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
        int x = 51, y = 270, width = 96, height = 30;
        juce::String text (TRANS("Decoder 1"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 168, y = 271, width = 120, height = 30;
        juce::String text (TRANS("Cross-over (Hz)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 339, y = 270, width = 96, height = 30;
        juce::String text (TRANS("Decoder 2"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 82, y = 317, width = 96, height = 30;
        juce::String text (TRANS("max_rE:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (10.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 165, width = 261, height = 30;
        juce::String text (TRANS("Decoding Order Per Frequency Band"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 247, width = 37, height = 30;
        juce::String text (TRANS("100"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 174, y = 247, width = 37, height = 30;
        juce::String text (TRANS("1k"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 328, y = 247, width = 37, height = 30;
        juce::String text (TRANS("10k"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 210, y = 247, width = 93, height = 30;
        juce::String text (TRANS("Frequency (Hz)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 371, y = 247, width = 37, height = 30;
        juce::String text (TRANS("20k"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 366, y = 317, width = 96, height = 30;
        juce::String text (TRANS("max_rE:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (10.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 419, y = 239, width = 13, height = 30;
        juce::String text (TRANS("1"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 58, width = 132, height = 30;
        juce::String text (TRANS("Max Order:"));
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
        juce::String text (TRANS("AmbiDEC"));
        juce::Colour fillColour = juce::Colour (0xff00d8df);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 2, height = 365;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 654, y = 0, width = 2, height = 365;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 363, width = 656, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 232, y = 139, width = 194, height = 30;
        juce::String text (TRANS("Apply Pre-Processing:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 115, width = 132, height = 30;
        juce::String text (TRANS("Channel Order:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		185, 16, 530, 11,
		Justification::centredLeft, true);

    /* label for max ORDER */
    int x = 419, y = 170, width = 13, height = 30;
    String text = String(CBmasterOrder->getSelectedId());
    Colour fillColour = Colours::white;
    g.setColour (fillColour);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));

    g.drawText (text, x, y, width, height,
                Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(ambi_dec_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(ambi_dec_getDAWsamplerate(hAmbi)) + TRANS(") is unsupported"),
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
                       TRANS("/") + String(ambi_dec_getNSHrequired(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String((ambi_dec_getBinauraliseLSflag(hAmbi) ? 2 : ambi_dec_getNumLoudspeakers(hAmbi)) ) + TRANS(")"),
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

    if (comboBoxThatHasChanged == CBoutputDirsPreset.get())
    {
        //[UserComboBoxCode_CBoutputDirsPreset] -- add your combo box handling code here..
        ambi_dec_setOutputConfigPreset(hAmbi, CBoutputDirsPreset->getSelectedId());
        //[/UserComboBoxCode_CBoutputDirsPreset]
    }
    else if (comboBoxThatHasChanged == CBsourcePreset.get())
    {
        //[UserComboBoxCode_CBsourcePreset] -- add your combo box handling code here..
        ambi_dec_setSourcePreset(hAmbi, CBsourcePreset->getSelectedId());
		decOrder2dSlider->setRefreshValuesFLAG(true);
        //[/UserComboBoxCode_CBsourcePreset]
    }
    else if (comboBoxThatHasChanged == CBchFormat.get())
    {
        //[UserComboBoxCode_CBchFormat] -- add your combo box handling code here..
        ambi_dec_setChOrder(hAmbi, CBchFormat->getSelectedId());
        //[/UserComboBoxCode_CBchFormat]
    }
    else if (comboBoxThatHasChanged == CBnormScheme.get())
    {
        //[UserComboBoxCode_CBnormScheme] -- add your combo box handling code here..
        ambi_dec_setNormType(hAmbi, CBnormScheme->getSelectedId());
        //[/UserComboBoxCode_CBnormScheme]
    }
    else if (comboBoxThatHasChanged == CBdec1method.get())
    {
        //[UserComboBoxCode_CBdec1method] -- add your combo box handling code here..
        ambi_dec_setDecMethod(hAmbi, 0, CBdec1method->getSelectedId());
        //[/UserComboBoxCode_CBdec1method]
    }
    else if (comboBoxThatHasChanged == CBdec2method.get())
    {
        //[UserComboBoxCode_CBdec2method] -- add your combo box handling code here..
        ambi_dec_setDecMethod(hAmbi, 1, CBdec2method->getSelectedId());
        //[/UserComboBoxCode_CBdec2method]
    }
    else if (comboBoxThatHasChanged == CBdec1normtype.get())
    {
        //[UserComboBoxCode_CBdec1normtype] -- add your combo box handling code here..
        ambi_dec_setDecNormType(hAmbi, 0, CBdec1normtype->getSelectedId());
        //[/UserComboBoxCode_CBdec1normtype]
    }
    else if (comboBoxThatHasChanged == CBdec2normtype.get())
    {
        //[UserComboBoxCode_CBdec2normtype] -- add your combo box handling code here..
        ambi_dec_setDecNormType(hAmbi, 1, CBdec2normtype->getSelectedId());
        //[/UserComboBoxCode_CBdec2normtype]
    }
    else if (comboBoxThatHasChanged == CBmasterOrder.get())
    {
        //[UserComboBoxCode_CBmasterOrder] -- add your combo box handling code here..
        ambi_dec_setMasterDecOrder(hAmbi, CBmasterOrder->getSelectedId());
        ambi_dec_setDecOrderAllBands(hAmbi, CBmasterOrder->getSelectedId());
        decOrder2dSlider->setYrange(1, CBmasterOrder->getSelectedId());
        decOrder2dSlider->setRefreshValuesFLAG(true);
        s_decOrder->setRange(1, CBmasterOrder->getSelectedId(), 1);
        s_decOrder->setValue(CBmasterOrder->getSelectedId());
        repaint();
        //[/UserComboBoxCode_CBmasterOrder]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == SL_num_loudspeakers.get())
    {
        //[UserSliderCode_SL_num_loudspeakers] -- add your slider handling code here..
        ambi_dec_setNumLoudspeakers(hAmbi, (int)SL_num_loudspeakers->getValue());
        //[/UserSliderCode_SL_num_loudspeakers]
    }
    else if (sliderThatWasMoved == SL_transitionFreq.get())
    {
        //[UserSliderCode_SL_transitionFreq] -- add your slider handling code here..
        ambi_dec_setTransitionFreq(hAmbi, (float)SL_transitionFreq->getValue());
        //[/UserSliderCode_SL_transitionFreq]
    }
    else if (sliderThatWasMoved == s_decOrder.get())
    {
        //[UserSliderCode_s_decOrder] -- add your slider handling code here..
        ambi_dec_setDecOrderAllBands(hAmbi, (int)s_decOrder->getValue());
		decOrder2dSlider->setRefreshValuesFLAG(true);
        //[/UserSliderCode_s_decOrder]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == TBuseDefaultHRIRs.get())
    {
        //[UserButtonCode_TBuseDefaultHRIRs] -- add your button handler code here..
        ambi_dec_setUseDefaultHRIRsflag(hAmbi, TBuseDefaultHRIRs->getToggleState());
        //[/UserButtonCode_TBuseDefaultHRIRs]
    }
    else if (buttonThatWasClicked == TBdec1EnableMaxrE.get())
    {
        //[UserButtonCode_TBdec1EnableMaxrE] -- add your button handler code here..
        ambi_dec_setDecEnableMaxrE(hAmbi, 0, TBdec1EnableMaxrE->getToggleState());
        //[/UserButtonCode_TBdec1EnableMaxrE]
    }
    else if (buttonThatWasClicked == TBdec2EnableMaxrE.get())
    {
        //[UserButtonCode_TBdec2EnableMaxrE] -- add your button handler code here..
        ambi_dec_setDecEnableMaxrE(hAmbi, 1, TBdec2EnableMaxrE->getToggleState());
        //[/UserButtonCode_TBdec2EnableMaxrE]
    }
    else if (buttonThatWasClicked == TBBinauraliseLS.get())
    {
        //[UserButtonCode_TBBinauraliseLS] -- add your button handler code here..
        ambi_dec_setBinauraliseLSflag(hAmbi, TBBinauraliseLS->getToggleState());
        //[/UserButtonCode_TBBinauraliseLS]
    }
    else if (buttonThatWasClicked == tb_loadJSON.get())
    {
        //[UserButtonCode_tb_loadJSON] -- add your button handler code here..
        chooser = std::make_unique<juce::FileChooser> ("Load configuration...",
                                                       hVst->getLastDir().exists() ? hVst->getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                                                       "*.json");
        auto chooserFlags = juce::FileBrowserComponent::openMode
                                  | juce::FileBrowserComponent::canSelectFiles;
        chooser->launchAsync (chooserFlags, [this] (const FileChooser& fc) {
            auto file = fc.getResult();
            if (file != File{}){
                hVst->setLastDir(file.getParentDirectory());
                hVst->loadConfiguration (file);
            }
        });
        //[/UserButtonCode_tb_loadJSON]
    }
    else if (buttonThatWasClicked == tb_saveJSON.get())
    {
        //[UserButtonCode_tb_saveJSON] -- add your button handler code here..
        chooser = std::make_unique<juce::FileChooser> ("Save configuration...",
                                                       hVst->getLastDir().exists() ? hVst->getLastDir() : File::getSpecialLocation (File::userHomeDirectory),
                                                       "*.json");
        auto chooserFlags = juce::FileBrowserComponent::saveMode;
        chooser->launchAsync (chooserFlags, [this] (const FileChooser& fc) {
            auto file = fc.getResult();
            if (file != File{}) {
                hVst->setLastDir(file.getParentDirectory());
                hVst->saveConfigurationToFile (file);
            }
        });
        //[/UserButtonCode_tb_saveJSON]
    }
    else if (buttonThatWasClicked == TBenablePreProc.get())
    {
        //[UserButtonCode_TBenablePreProc] -- add your button handler code here..
        ambi_dec_setEnableHRIRsPreProc(hAmbi, TBenablePreProc->getToggleState());
        //[/UserButtonCode_TBenablePreProc]
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
            /* parameters whos values can change internally should be periodically refreshed */
            if(TBuseDefaultHRIRs->getToggleState() != ambi_dec_getUseDefaultHRIRsflag(hAmbi) )
                TBuseDefaultHRIRs->setToggleState(ambi_dec_getUseDefaultHRIRsflag(hAmbi), dontSendNotification);
            if(TBBinauraliseLS->getToggleState() != ambi_dec_getBinauraliseLSflag(hAmbi) )
                TBBinauraliseLS->setToggleState(ambi_dec_getBinauraliseLSflag(hAmbi), dontSendNotification);
            if(TBenablePreProc->getToggleState() != ambi_dec_getEnableHRIRsPreProc(hAmbi) )
                TBenablePreProc->setToggleState(ambi_dec_getEnableHRIRsPreProc(hAmbi), dontSendNotification);
            if(SL_num_loudspeakers->getValue() != ambi_dec_getNumLoudspeakers(hAmbi) )
                SL_num_loudspeakers->setValue(ambi_dec_getNumLoudspeakers(hAmbi),dontSendNotification);
            if(CBdec1method->getSelectedId() != ambi_dec_getDecMethod(hAmbi, 0) )
                CBdec1method->setSelectedId(ambi_dec_getDecMethod(hAmbi, 0));
            if(CBdec2method->getSelectedId() != ambi_dec_getDecMethod(hAmbi, 1) )
                CBdec2method->setSelectedId(ambi_dec_getDecMethod(hAmbi, 1));
            if(CBchFormat->getSelectedId() != ambi_dec_getChOrder(hAmbi) )
                CBchFormat->setSelectedId(ambi_dec_getChOrder(hAmbi), dontSendNotification);
            if(CBnormScheme->getSelectedId() != ambi_dec_getNormType(hAmbi) )
                CBnormScheme->setSelectedId(ambi_dec_getNormType(hAmbi), dontSendNotification);
            CBchFormat->setItemEnabled(CH_FUMA, ambi_dec_getMasterDecOrder(hAmbi)==SH_ORDER_FIRST ? true : false);
            CBnormScheme->setItemEnabled(NORM_FUMA, ambi_dec_getMasterDecOrder(hAmbi)==SH_ORDER_FIRST ? true : false);
            outputCoordsView_handle->setNCH(ambi_dec_getNumLoudspeakers(hAmbi));

            /* refresh */
            if (decOrder2dSlider->getRefreshValuesFLAG()) {
                decOrder2dSlider->repaint();
                decOrder2dSlider->setRefreshValuesFLAG(false);
            }

            /* Progress bar */
            if(ambi_dec_getCodecStatus(hAmbi)==CODEC_STATUS_INITIALISING){
                addAndMakeVisible(progressbar);
                progress = (double)ambi_dec_getProgressBar0_1(hAmbi);
                char text[PROGRESSBARTEXT_CHAR_LENGTH];
                ambi_dec_getProgressBarText(hAmbi, (char*)text);
                progressbar.setTextToDisplay(String(text));
            }
            else
                removeChildComponent(&progressbar);

            /* Some parameters shouldn't be editable during initialisation*/
            if(ambi_dec_getCodecStatus(hAmbi)==CODEC_STATUS_INITIALISING){
                if(TBuseDefaultHRIRs->isEnabled())
                    TBuseDefaultHRIRs->setEnabled(false);
                if(CBoutputDirsPreset->isEnabled())
                    CBoutputDirsPreset->setEnabled(false);
                if(SL_num_loudspeakers->isEnabled())
                    SL_num_loudspeakers->setEnabled(false);
                if(CBdec1method->isEnabled())
                    CBdec1method->setEnabled(false);
                if(CBdec2method->isEnabled())
                    CBdec2method->setEnabled(false);
                if(TBdec1EnableMaxrE->isEnabled())
                    TBdec1EnableMaxrE->setEnabled(false);
                if(TBdec2EnableMaxrE->isEnabled())
                    TBdec2EnableMaxrE->setEnabled(false);
                if(CBdec1normtype->isEnabled())
                    CBdec1normtype->setEnabled(false);
                if(CBdec2normtype->isEnabled())
                    CBdec2normtype->setEnabled(false);
                if(TBBinauraliseLS->isEnabled())
                    TBBinauraliseLS->setEnabled(false);
                if(s_decOrder->isEnabled())
                    s_decOrder->setEnabled(false);
                if(tb_loadJSON->isEnabled())
                    tb_loadJSON->setEnabled(false);
                if(CBmasterOrder->isEnabled())
                    CBmasterOrder->setEnabled(false);
                if(fileChooser.isEnabled())
                    fileChooser.setEnabled(false);
            }
            else {
                if(!TBuseDefaultHRIRs->isEnabled())
                    TBuseDefaultHRIRs->setEnabled(true);
                if(!CBoutputDirsPreset->isEnabled())
                    CBoutputDirsPreset->setEnabled(true);
                if(!SL_num_loudspeakers->isEnabled())
                    SL_num_loudspeakers->setEnabled(true);
                if(!CBdec1method->isEnabled())
                    CBdec1method->setEnabled(true);
                if(!CBdec2method->isEnabled())
                    CBdec2method->setEnabled(true);
                if(!TBdec1EnableMaxrE->isEnabled())
                    TBdec1EnableMaxrE->setEnabled(true);
                if(!TBdec2EnableMaxrE->isEnabled())
                    TBdec2EnableMaxrE->setEnabled(true);
                if(!CBdec1normtype->isEnabled())
                    CBdec1normtype->setEnabled(true);
                if(!CBdec2normtype->isEnabled())
                    CBdec2normtype->setEnabled(true);
                if(!TBBinauraliseLS->isEnabled())
                    TBBinauraliseLS->setEnabled(true);
                if(!s_decOrder->isEnabled())
                    s_decOrder->setEnabled(true);
                if(!tb_loadJSON->isEnabled())
                    tb_loadJSON->setEnabled(true);
                if(!CBmasterOrder->isEnabled())
                    CBmasterOrder->setEnabled(true);
                if(!fileChooser.isEnabled())
                    fileChooser.setEnabled(true);
            }

            /* display warning message, if needed */
            if ((hVst->getCurrentBlockSize() % ambi_dec_getFrameSize()) != 0){
                currentWarning = k_warning_frameSize;
                repaint(0,0,getWidth(),32);
            }
            else if ( !((ambi_dec_getDAWsamplerate(hAmbi) == 44.1e3) || (ambi_dec_getDAWsamplerate(hAmbi) == 48e3)) ){
                currentWarning = k_warning_supported_fs;
                repaint(0,0,getWidth(),32);
            }
            else if (ambi_dec_getDAWsamplerate(hAmbi) != ambi_dec_getHRIRsamplerate(hAmbi)){
                currentWarning = k_warning_mismatch_fs;
                repaint(0,0,getWidth(),32);
            }
            else if (hVst->getCurrentNumInputs() < ambi_dec_getNSHrequired(hAmbi)){
                currentWarning = k_warning_NinputCH;
                repaint(0,0,getWidth(),32);
            }
            else if (hVst->getCurrentNumOutputs() <
                      (ambi_dec_getBinauraliseLSflag(hAmbi) ? 2 : ambi_dec_getNumLoudspeakers(hAmbi)) ){
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
                 parentClasses="public AudioProcessorEditor, public MultiTimer, private FilenameComponentListener"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter), progressbar(progress), fileChooser (&quot;File&quot;, File(), true, false, false,&#10;                       &quot;*.sofa;*.nc;&quot;, String(),&#10;                       &quot;Load SOFA File&quot;)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="656" initialHeight="365">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 656 163" fill="linear: 8 32, 8 96, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <ROUNDRECT pos="1 1 654 32" cornerSize="5.0" fill="linear: 0 32, 656 24, 0=ff041518, 1=ff19313f"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 193 656 172" fill="linear: 8 360, 8 304, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="0 0 656 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="12 58 213 111" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 58 213 33" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 35a0a0a0"/>
    <RECT pos="152 272 145 81" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="296 272 140 81" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="446 121 196 232" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="224 58 212 111" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="446 58 196 64" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="455 58 67 30" fill="solid: ffffffff" hasStroke="0" text="Presets: "
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="12 168 424 105" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="499 122 105 28" fill="solid: ffffffff" hasStroke="0" text="Azi&#176;   #   Elev&#176;"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="455 86 169 30" fill="solid: ffffffff" hasStroke="0" text="Number of Outputs:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="164 32 149 30" fill="solid: ffffffff" hasStroke="0" text="Decoding Settings"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="524 32 113 30" fill="solid: ffffffff" hasStroke="0" text="Outputs"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="232 87 165 30" fill="solid: ffffffff" hasStroke="0" text="Use Default HRIR set:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 90 132 30" fill="solid: ffffffff" hasStroke="0" text="Mic Preset:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 140 132 30" fill="solid: ffffffff" hasStroke="0" text="Normalisation:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="232 58 189 30" fill="solid: ffffffff" hasStroke="0" text="Binauralise Loudspeakers:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="12 272 141 81" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="51 270 96 30" fill="solid: ffffffff" hasStroke="0" text="Decoder 1"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="168 271 120 30" fill="solid: ffffffff" hasStroke="0" text="Cross-over (Hz)"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="339 270 96 30" fill="solid: ffffffff" hasStroke="0" text="Decoder 2"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="82 317 96 30" fill="solid: ffffffff" hasStroke="0" text="max_rE:"
          fontname="Default font" fontsize="10.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 165 261 30" fill="solid: ffffffff" hasStroke="0" text="Decoding Order Per Frequency Band"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 247 37 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="174 247 37 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="328 247 37 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="210 247 93 30" fill="solid: ffffffff" hasStroke="0" text="Frequency (Hz)"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="371 247 37 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="366 317 96 30" fill="solid: ffffffff" hasStroke="0" text="max_rE:"
          fontname="Default font" fontsize="10.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="419 239 13 30" fill="solid: ffffffff" hasStroke="0" text="1"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 58 132 30" fill="solid: ffffffff" hasStroke="0" text="Max Order:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 112 32" fill="solid: ff00d8df" hasStroke="0" text="AmbiDEC"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 2 365" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="654 0 2 365" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 363 656 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <TEXT pos="232 139 194 30" fill="solid: ffffffff" hasStroke="0" text="Apply Pre-Processing:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 115 132 30" fill="solid: ffffffff" hasStroke="0" text="Channel Order:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <COMBOBOX name="new combo box" id="5a2f99f88aa51390" memberName="CBoutputDirsPreset"
            virtualName="" explicitFocusOrder="0" pos="520 64 112 20" editable="0"
            layout="33" items="Default" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="2c2a2b3d0614cc94" memberName="SL_num_loudspeakers"
          virtualName="" explicitFocusOrder="0" pos="592 92 40 20" min="1.0"
          max="64.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="f7f951a1b21e1a11" memberName="TBuseDefaultHRIRs"
                virtualName="" explicitFocusOrder="0" pos="409 91 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="d83602bab6f1a999" memberName="CBsourcePreset"
            virtualName="" explicitFocusOrder="0" pos="99 96 118 20" editable="0"
            layout="33" items="Ideal SH" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="a36915795f16ceb6" memberName="CBchFormat"
            virtualName="" explicitFocusOrder="0" pos="129 120 88 20" editable="0"
            layout="33" items="" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="e10be54628a6df43" memberName="CBnormScheme"
            virtualName="" explicitFocusOrder="0" pos="129 144 88 20" editable="0"
            layout="33" items="" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="27b7eb906eb4d4f" memberName="SL_transitionFreq"
          virtualName="" explicitFocusOrder="0" pos="168 305 112 40" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" min="500.0" max="2000.0" int="0.1" style="LinearHorizontal"
          textBoxPos="TextBoxAbove" textBoxEditable="1" textBoxWidth="60"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="6fe8e095551b1808" memberName="CBdec1method"
            virtualName="" explicitFocusOrder="0" pos="24 297 116 20" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="80fc4525118b480b" memberName="CBdec2method"
            virtualName="" explicitFocusOrder="0" pos="308 297 116 20" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="new toggle button" id="2ff10cbc9f10d197" memberName="TBdec1EnableMaxrE"
                virtualName="" explicitFocusOrder="0" pos="120 321 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="f7dc2ec3654b795d" memberName="TBdec2EnableMaxrE"
                virtualName="" explicitFocusOrder="0" pos="404 321 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="51c3f0687556e1b1" memberName="CBdec1normtype"
            virtualName="" explicitFocusOrder="0" pos="24 323 52 20" editable="0"
            layout="33" items="" textWhenNonSelected="EP" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="new toggle button" id="86c014bf0612a514" memberName="TBBinauraliseLS"
                virtualName="" explicitFocusOrder="0" pos="409 62 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="da63cfe9ccba1746" memberName="CBdec2normtype"
            virtualName="" explicitFocusOrder="0" pos="308 323 52 20" editable="0"
            layout="33" items="" textWhenNonSelected="EP" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="50ea77f60aadeeca" memberName="s_decOrder"
          virtualName="" explicitFocusOrder="0" pos="384 185 40 80" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.0" max="1.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TEXTBUTTON name="new button" id="527e24c6748d02d4" memberName="tb_loadJSON"
              virtualName="" explicitFocusOrder="0" pos="447 40 34 14" bgColOff="ff14889e"
              buttonText="Import" connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="48c5d3526dcfe64f" memberName="tb_saveJSON"
              virtualName="" explicitFocusOrder="0" pos="481 40 34 14" bgColOff="ff224d97"
              bgColOn="ff181f9a" buttonText="Export" connectedEdges="1" needsCallback="1"
              radioGroupId="0"/>
  <COMBOBOX name="new combo box" id="a465903000494955" memberName="CBmasterOrder"
            virtualName="" explicitFocusOrder="0" pos="99 65 118 20" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="new toggle button" id="6518b0bb9c223228" memberName="TBenablePreProc"
                virtualName="" explicitFocusOrder="0" pos="409 143 24 24" tooltip="Enable HRIR Pre-Processing"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

