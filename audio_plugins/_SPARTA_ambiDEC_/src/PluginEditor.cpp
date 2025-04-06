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
    CBoutputDirsPreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBoutputDirsPreset.get());
    CBoutputDirsPreset->setEditableText (false);
    CBoutputDirsPreset->setJustificationType (juce::Justification::centredLeft);
    CBoutputDirsPreset->setTextWhenNothingSelected (TRANS ("Default"));
    CBoutputDirsPreset->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBoutputDirsPreset->addItem (TRANS ("Default"), 1);
    CBoutputDirsPreset->addListener (this);

    CBoutputDirsPreset->setBounds (520, 64, 112, 20);

    SL_num_loudspeakers.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_loudspeakers.get());
    SL_num_loudspeakers->setRange (1, 128, 1);
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
    CBsourcePreset->setTextWhenNothingSelected (TRANS ("Default"));
    CBsourcePreset->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBsourcePreset->addItem (TRANS ("Ideal SH"), 1);
    CBsourcePreset->addListener (this);

    CBsourcePreset->setBounds (99, 96, 118, 20);

    CBchFormat.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (juce::Justification::centredLeft);
    CBchFormat->setTextWhenNothingSelected (TRANS ("ACN"));
    CBchFormat->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBchFormat->addListener (this);

    CBchFormat->setBounds (129, 120, 88, 20);

    CBnormScheme.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (juce::Justification::centredLeft);
    CBnormScheme->setTextWhenNothingSelected (TRANS ("N3D"));
    CBnormScheme->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
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
    CBdec1method->setTextWhenNothingSelected (TRANS ("Default"));
    CBdec1method->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBdec1method->addListener (this);

    CBdec1method->setBounds (24, 297, 116, 20);

    CBdec2method.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBdec2method.get());
    CBdec2method->setEditableText (false);
    CBdec2method->setJustificationType (juce::Justification::centredLeft);
    CBdec2method->setTextWhenNothingSelected (TRANS ("Default"));
    CBdec2method->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
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
    CBdec1normtype->setTextWhenNothingSelected (TRANS ("EP"));
    CBdec1normtype->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
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
    CBdec2normtype->setTextWhenNothingSelected (TRANS ("EP"));
    CBdec2normtype->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
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
    tb_loadJSON->setButtonText (TRANS ("Import"));
    tb_loadJSON->setConnectedEdges (juce::Button::ConnectedOnRight);
    tb_loadJSON->addListener (this);
    tb_loadJSON->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff14889e));

    tb_loadJSON->setBounds (447, 40, 34, 14);

    tb_saveJSON.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON.get());
    tb_saveJSON->setButtonText (TRANS ("Export"));
    tb_saveJSON->setConnectedEdges (juce::Button::ConnectedOnLeft);
    tb_saveJSON->addListener (this);
    tb_saveJSON->setColour (juce::TextButton::buttonColourId, juce::Colour (0xff224d97));
    tb_saveJSON->setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff181f9a));

    tb_saveJSON->setBounds (481, 40, 34, 14);

    CBmasterOrder.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBmasterOrder.get());
    CBmasterOrder->setEditableText (false);
    CBmasterOrder->setJustificationType (juce::Justification::centredLeft);
    CBmasterOrder->setTextWhenNothingSelected (TRANS ("Default"));
    CBmasterOrder->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBmasterOrder->addListener (this);

    CBmasterOrder->setBounds (99, 65, 118, 20);

    TBenablePreProc.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBenablePreProc.get());
    TBenablePreProc->setTooltip (TRANS ("Enable HRIR Pre-Processing"));
    TBenablePreProc->setButtonText (juce::String());
    TBenablePreProc->addListener (this);

    TBenablePreProc->setBounds (409, 143, 24, 24);

    setSize (656, 365);

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
    CBmasterOrder->addItem (TRANS("8th order"), SH_ORDER_EIGHTH);
    CBmasterOrder->addItem (TRANS("9th order"), SH_ORDER_NINTH);
    CBmasterOrder->addItem (TRANS("10th order"), SH_ORDER_TENTH);

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
    CBmasterOrder->setTooltip("Maximum decoding order (can also be lower than this for different frequencies, see below). Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals as input.");
    TBuseDefaultHRIRs->setTooltip("If this is 'ticked', the plug-in is using the default HRIR set from the Spatial_Audio_Framework.");
    fileChooser.setTooltip("Optionally, a custom HRIR set may be loaded via the SOFA standard. Note that if the plug-in fails to load the specified .sofa file, it will revert to the default HRIR data.");
    SL_num_loudspeakers->setTooltip("Number of loudspeakers to decode to.");
    CBchFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormScheme->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    s_decOrder->setTooltip("This sets the decoding order for all frequencies. Use the 2-D slider to change the decoding order for specific frequencies.");
    TBBinauraliseLS->setTooltip("If enabled, the loudspeaker signals are binauralised and sent to the first two output channels. Note that this plug-in also performs phase-simplification (linearising the phase) of the HRIRs, which involves estimating the ITDs for all the HRIRs, removing the phase from the HRTFs, but then re-introducing the phase as IPDs per frequency-bin. This greatly simplifies the HRIR interpolation process, but note that it will not be the same as direct convolution with the unaltered HRIR; although it should be perceptually very close in the majority of cases. Note that BRIRs are not supported here.");
    CBdec1method->setTooltip("Decoding method for the low-frequencies. The methods are equivalent if the loudspeakers are uniformly distributed (e.g. a t-design). Sampling Ambisonic Decoder (SAD) is the simplest, as it simply steers a hyper-cardioid beamformer to each loudspeaker direction. Mode-Matching Decoder (MMD), lends more energy to parts of the sphere which are more sparsely populated with loudspeakers (therefore, be careful! as a lot of energy can go to loudspeakers that are far away from the others, like a 90degree elevation loudpseaker, for example). AllRAD first decodes to a t-design and pans the t-design signals to the loudspeaker set-up using VBAP (most recommended for irregular loudspeaker arrangements). EPAD optimises the decoding to have the most consistent output energy while a source is panned over the whole sphere.");
    CBdec2method->setTooltip("Decoding method for the low-frequencies. The methods are equivalent if the loudspeakers are uniformly distributed (e.g. a t-design). Sampling Ambisonic Decoder (SAD) is the simplest, as it simply steers a hyper-cardioid beamformer to each loudspeaker direction. Mode-Matching Decoder (MMD), lends more energy to parts of the sphere which are more sparsely populated with loudspeakers (therefore, be careful! as a lot of energy can go to loudspeakers that are far away from the others, like a 90degree elevation loudpseaker, for example). AllRAD first decodes to a t-design and pans the t-design signals to the loudspeaker set-up using VBAP (most recommended for irregular loudspeaker arrangements). EPAD optimises the decoding to have the most consistent output energy while a source is panned over the whole sphere.");
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
}

PluginEditor::~PluginEditor()
{
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

    setLookAndFeel(nullptr);
    outputCoordsVP = nullptr;
    decOrder2dSlider = nullptr;
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 30, width = 656, height = 163;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
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
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 12, y = 58, width = 213, height = 111;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 58, width = 213, height = 33;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x35a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 152, y = 272, width = 145, height = 81;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 296, y = 272, width = 140, height = 81;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 446, y = 121, width = 196, height = 232;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 224, y = 58, width = 212, height = 111;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 446, y = 58, width = 196, height = 64;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 455, y = 58, width = 67, height = 30;
        juce::String text (TRANS ("Presets: "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 12, y = 168, width = 424, height = 105;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 499, y = 122, width = 105, height = 28;
        juce::String text (juce::CharPointer_UTF8 ("Azi\xc2\xb0   #   Elev\xc2\xb0"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 455, y = 86, width = 169, height = 30;
        juce::String text (TRANS ("Number of Outputs:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 164, y = 32, width = 149, height = 30;
        juce::String text (TRANS ("Decoding Settings"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 524, y = 32, width = 113, height = 30;
        juce::String text (TRANS ("Outputs"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 232, y = 87, width = 165, height = 30;
        juce::String text (TRANS ("Use Default HRIR set:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 90, width = 132, height = 30;
        juce::String text (TRANS ("Mic Preset:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 140, width = 132, height = 30;
        juce::String text (TRANS ("Normalisation:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 232, y = 58, width = 189, height = 30;
        juce::String text (TRANS ("Binauralise Loudspeakers:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 12, y = 272, width = 141, height = 81;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 51, y = 270, width = 96, height = 30;
        juce::String text (TRANS ("Decoder 1"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 168, y = 271, width = 120, height = 30;
        juce::String text (TRANS ("Cross-over (Hz)"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 339, y = 270, width = 96, height = 30;
        juce::String text (TRANS ("Decoder 2"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 82, y = 317, width = 96, height = 30;
        juce::String text (TRANS ("max_rE:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(10.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 165, width = 261, height = 30;
        juce::String text (TRANS ("Decoding Order Per Frequency Band"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 247, width = 37, height = 30;
        juce::String text (TRANS ("100"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 174, y = 247, width = 37, height = 30;
        juce::String text (TRANS ("1k"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 328, y = 247, width = 37, height = 30;
        juce::String text (TRANS ("10k"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 210, y = 247, width = 93, height = 30;
        juce::String text (TRANS ("Frequency (Hz)"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 371, y = 247, width = 37, height = 30;
        juce::String text (TRANS ("20k"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 366, y = 317, width = 96, height = 30;
        juce::String text (TRANS ("max_rE:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(10.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 419, y = 239, width = 13, height = 30;
        juce::String text (TRANS ("1"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 58, width = 132, height = 30;
        juce::String text (TRANS ("Max Order:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 1, width = 100, height = 32;
        juce::String text (TRANS ("SPARTA|"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(18.80f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 92, y = 1, width = 112, height = 32;
        juce::String text (TRANS ("AmbiDEC"));
        juce::Colour fillColour = juce::Colour (0xff00d8df);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 2, height = 365;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 654, y = 0, width = 2, height = 365;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 363, width = 656, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 232, y = 139, width = 194, height = 30;
        juce::String text (TRANS ("Apply Pre-Processing:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 19, y = 115, width = 132, height = 30;
        juce::String text (TRANS ("Channel Order:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions(14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

	g.setColour(Colours::white);
	g.setFont(juce::FontOptions(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		185, 16, 530, 11,
		Justification::centredLeft, true);

    /* label for max ORDER */
    int x = 419, y = 170, width = 13, height = 30;
    String text = String(CBmasterOrder->getSelectedId());
    Colour fillColour = Colours::white;
    g.setColour (fillColour);
    g.setFont (juce::FontOptions (15.00f, Font::plain).withStyle ("Bold"));

    g.drawText (text, x, y, width, height,
                Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
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
}

void PluginEditor::resized()
{
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == CBoutputDirsPreset.get())
    {
        ambi_dec_setOutputConfigPreset(hAmbi, CBoutputDirsPreset->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBsourcePreset.get())
    {
        ambi_dec_setSourcePreset(hAmbi, CBsourcePreset->getSelectedId());
		decOrder2dSlider->setRefreshValuesFLAG(true);
    }
    else if (comboBoxThatHasChanged == CBchFormat.get())
    {
        ambi_dec_setChOrder(hAmbi, CBchFormat->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBnormScheme.get())
    {
        ambi_dec_setNormType(hAmbi, CBnormScheme->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBdec1method.get())
    {
        ambi_dec_setDecMethod(hAmbi, 0, CBdec1method->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBdec2method.get())
    {
        ambi_dec_setDecMethod(hAmbi, 1, CBdec2method->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBdec1normtype.get())
    {
        ambi_dec_setDecNormType(hAmbi, 0, CBdec1normtype->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBdec2normtype.get())
    {
        ambi_dec_setDecNormType(hAmbi, 1, CBdec2normtype->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBmasterOrder.get())
    {
        ambi_dec_setMasterDecOrder(hAmbi, CBmasterOrder->getSelectedId());
        ambi_dec_setDecOrderAllBands(hAmbi, CBmasterOrder->getSelectedId());
        decOrder2dSlider->setYrange(1, CBmasterOrder->getSelectedId());
        decOrder2dSlider->setRefreshValuesFLAG(true);
        s_decOrder->setRange(1, CBmasterOrder->getSelectedId(), 1);
        s_decOrder->setValue(CBmasterOrder->getSelectedId());
        repaint();
    }
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == SL_num_loudspeakers.get())
    {
        ambi_dec_setNumLoudspeakers(hAmbi, (int)SL_num_loudspeakers->getValue());
    }
    else if (sliderThatWasMoved == SL_transitionFreq.get())
    {
        ambi_dec_setTransitionFreq(hAmbi, (float)SL_transitionFreq->getValue());
    }
    else if (sliderThatWasMoved == s_decOrder.get())
    {
        ambi_dec_setDecOrderAllBands(hAmbi, (int)s_decOrder->getValue());
		decOrder2dSlider->setRefreshValuesFLAG(true);
    }
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == TBuseDefaultHRIRs.get())
    {
        ambi_dec_setUseDefaultHRIRsflag(hAmbi, TBuseDefaultHRIRs->getToggleState());
    }
    else if (buttonThatWasClicked == TBdec1EnableMaxrE.get())
    {
        ambi_dec_setDecEnableMaxrE(hAmbi, 0, TBdec1EnableMaxrE->getToggleState());
    }
    else if (buttonThatWasClicked == TBdec2EnableMaxrE.get())
    {
        ambi_dec_setDecEnableMaxrE(hAmbi, 1, TBdec2EnableMaxrE->getToggleState());
    }
    else if (buttonThatWasClicked == TBBinauraliseLS.get())
    {
        ambi_dec_setBinauraliseLSflag(hAmbi, TBBinauraliseLS->getToggleState());
    }
    else if (buttonThatWasClicked == tb_loadJSON.get())
    {
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
    }
    else if (buttonThatWasClicked == tb_saveJSON.get())
    {
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
    }
    else if (buttonThatWasClicked == TBenablePreProc.get())
    {
        ambi_dec_setEnableHRIRsPreProc(hAmbi, TBenablePreProc->getToggleState());
    }
}

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
