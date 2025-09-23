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
    presetCB.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (presetCB.get());
    presetCB->setEditableText (false);
    presetCB->setJustificationType (juce::Justification::centredLeft);
    presetCB->setTextWhenNothingSelected (juce::String());
    presetCB->addListener (this);
    presetCB->setBounds (88, 62, 120, 20);

    arrayTypeCB = std::make_unique<ComboBoxWithAttachment>(p.parameters, "arrayType");
    addAndMakeVisible (arrayTypeCB.get());
    arrayTypeCB->setEditableText (false);
    arrayTypeCB->setJustificationType (juce::Justification::centredLeft);
    arrayTypeCB->addListener (this);
    arrayTypeCB->setBounds (368, 374, 120, 20);

    QSlider = std::make_unique<SliderWithAttachment>(p.parameters, "numSensors");
    addAndMakeVisible (QSlider.get());
    QSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    QSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    QSlider->addListener (this);
    QSlider->setBounds (154, 97, 54, 20);

    rSlider = std::make_unique<SliderWithAttachment>(p.parameters, "arrayRadius");
    addAndMakeVisible (rSlider.get());
    rSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    rSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    rSlider->addListener (this);
    rSlider->setBounds (124, 129, 84, 20);

    RSlider = std::make_unique<SliderWithAttachment>(p.parameters, "baffleRadius");
    addAndMakeVisible (RSlider.get());
    RSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    RSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    RSlider->addListener (this);
    RSlider->setBounds (124, 161, 84, 20);
    
    cSlider = std::make_unique<SliderWithAttachment>(p.parameters, "speedOfSound");
    addAndMakeVisible (cSlider.get());
    cSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    cSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    cSlider->addListener (this);
    cSlider->setBounds (368, 342, 120, 20);

    weightTypeCB = std::make_unique<ComboBoxWithAttachment>(p.parameters, "weightType");
    addAndMakeVisible (weightTypeCB.get());
    weightTypeCB->setEditableText (false);
    weightTypeCB->setJustificationType (juce::Justification::centredLeft);
    weightTypeCB->addListener (this);
    weightTypeCB->setBounds (368, 406, 120, 20);

    filterTypeCB = std::make_unique<ComboBoxWithAttachment>(p.parameters, "filterType");
    addAndMakeVisible (filterTypeCB.get());
    filterTypeCB->setEditableText (false);
    filterTypeCB->setJustificationType (juce::Justification::centredLeft);
    filterTypeCB->addListener (this);
    filterTypeCB->setBounds (640, 274, 128, 20);

    regAmountSlider = std::make_unique<SliderWithAttachment>(p.parameters, "maxGain");
    addAndMakeVisible (regAmountSlider.get());
    regAmountSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    regAmountSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 65, 20);
    regAmountSlider->addListener (this);
    regAmountSlider->setBounds (610, 308, 158, 20);

    CHOrderingCB = std::make_unique<ComboBoxWithAttachment>(p.parameters, "channelOrder");
    addAndMakeVisible (CHOrderingCB.get());
    CHOrderingCB->setEditableText (false);
    CHOrderingCB->setJustificationType (juce::Justification::centredLeft);
    CHOrderingCB->addListener (this);
    CHOrderingCB->setBounds (640, 375, 128, 20);

    normalisationCB = std::make_unique<ComboBoxWithAttachment>(p.parameters, "normType");
    addAndMakeVisible (normalisationCB.get());
    normalisationCB->setEditableText (false);
    normalisationCB->setJustificationType (juce::Justification::centredLeft);
    normalisationCB->addListener (this);
    normalisationCB->setBounds (640, 407, 128, 20);

    gainSlider = std::make_unique<SliderWithAttachment>(p.parameters, "postGain");
    addAndMakeVisible (gainSlider.get());
    gainSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    gainSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 65, 20);
    gainSlider->addListener (this);
    gainSlider->setBounds (610, 341, 158, 20);

    textButton.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (textButton.get());
    textButton->setButtonText (TRANS ("Analyse"));
    textButton->addListener (this);
    textButton->setBounds (228, 39, 60, 14);

    dispWindow.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (dispWindow.get());
    dispWindow->setEditableText (false);
    dispWindow->setJustificationType (juce::Justification::centredLeft);
    dispWindow->addItem (TRANS ("Filters"), 1);
    dispWindow->addItem (TRANS ("Corr"), 2);
    dispWindow->addItem (TRANS ("L Diff"), 3);
    dispWindow->setSelectedId(1);
    dispWindow->addListener (this);
    dispWindow->setBounds (721, 39, 63, 14);

    tb_loadJSON.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_loadJSON.get());
    tb_loadJSON->setButtonText (TRANS ("Import"));
    tb_loadJSON->setConnectedEdges (juce::Button::ConnectedOnRight);
    tb_loadJSON->addListener (this);
    tb_loadJSON->setBounds (148, 39, 34, 14);

    tb_saveJSON.reset (new juce::TextButton ("new button"));
    addAndMakeVisible (tb_saveJSON.get());
    tb_saveJSON->setButtonText (TRANS ("Export"));
    tb_saveJSON->setConnectedEdges (juce::Button::ConnectedOnLeft);
    tb_saveJSON->addListener (this);
    tb_saveJSON->setBounds (182, 39, 34, 14);

    CBencodingOrder = std::make_unique<ComboBoxWithAttachment>(p.parameters, "outputOrder");
    addAndMakeVisible (CBencodingOrder.get());
    CBencodingOrder->setEditableText (false);
    CBencodingOrder->setJustificationType (juce::Justification::centredLeft);
    CBencodingOrder->addListener (this);
    CBencodingOrder->setBounds (368, 274, 120, 20);

    applyDiffEQ = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "enableDiffEQ");
    addAndMakeVisible (applyDiffEQ.get());
    applyDiffEQ->setButtonText (juce::String());
    applyDiffEQ->addListener (this);
    applyDiffEQ->setBounds (466, 309, 23, 24);

    setSize (800, 450);

    /* handle to object */
    hA2sh = processor.getFXHandle();

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    setLookAndFeel(&LAF);

    /* remove the slider bit of these sliders */
    rSlider->setColour(Slider::trackColourId, Colours::transparentBlack);
    rSlider->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    rSlider->setSliderSnapsToMousePosition(false);
    RSlider->setColour(Slider::trackColourId, Colours::transparentBlack);
    RSlider->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    RSlider->setSliderSnapsToMousePosition(false);
    QSlider->setColour(Slider::trackColourId, Colours::transparentBlack);
    QSlider->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    QSlider->setSliderSnapsToMousePosition(false);
    cSlider->setColour(Slider::trackColourId, Colours::transparentBlack);
    cSlider->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    cSlider->setSliderSnapsToMousePosition(false);

    /* create EQ window and analysis windows */
    eqviewIncluded.reset (new eqview(556, 209, 30.0f, 20e3f, -30.0f, 60.0f, 48e3f )); /* TODO: switch to the more general "anaview"  */
    addAndMakeVisible (eqviewIncluded.get());
    eqviewIncluded->setAlwaysOnTop(true);
    eqviewIncluded->setTopLeftPosition(228, 56);
    eqviewIncluded->setVisible(true);
    cohviewIncluded.reset (new anaview(556, 209, 30.0f, 20e3f, 0.0f, 1.0f, TRANS("Spatial Corr. (T:I)"), 1, 48e3f ));
    addAndMakeVisible (cohviewIncluded.get());
    cohviewIncluded->setAlwaysOnTop(true);
    cohviewIncluded->setTopLeftPosition(228, 56);
    cohviewIncluded->setVisible(false);
    ldiffviewIncluded.reset (new anaview(556, 209, 30.0f, 20e3f, -30, 10, TRANS("Level Diff. (dB)"), 10.0f, 48e3f ));
    addAndMakeVisible (ldiffviewIncluded.get());
    ldiffviewIncluded->setAlwaysOnTop(true);
    ldiffviewIncluded->setTopLeftPosition(228, 56);
    ldiffviewIncluded->setVisible(false);
    dispID = SHOW_EQ;
    needScreenRefreshFLAG = true;

    /* pass handles to data required for eq and analysis displays */
    int numFreqPoints, numCurves;
    float* freqVector = array2sh_getFreqVector(hA2sh, &numFreqPoints);
    float** solidCurves = array2sh_getbN_inv(hA2sh, &numCurves, &numFreqPoints);
    eqviewIncluded->setSolidCurves_Handle(freqVector, solidCurves, numFreqPoints, numCurves);
    float** faintCurves = array2sh_getbN_modal(hA2sh, &numCurves, &numFreqPoints);
    eqviewIncluded->setFaintCurves_Handle(freqVector, faintCurves, numFreqPoints, numCurves);
    float* dataHandle = array2sh_getSpatialCorrelation_Handle(hA2sh, &numCurves, &numFreqPoints);
    cohviewIncluded->setSolidCurves_Handle(freqVector, dataHandle, numFreqPoints, numCurves);
    dataHandle = array2sh_getLevelDifference_Handle(hA2sh, &numCurves, &numFreqPoints);
    ldiffviewIncluded->setSolidCurves_Handle(freqVector, dataHandle, numFreqPoints, numCurves);

    /* Hide decoding orders that are unsuitable for number of sensors */
    for(int i=1; i<=MAX_SH_ORDER; i++)
        CBencodingOrder->setItemEnabled(i, (i+1)*(i+1) <= array2sh_getNumSensors(hA2sh) ? true : false);

    /* sensor coord table */
    //addAndMakeVisible (sensorCoordsVP = new Viewport ("new viewport"));
    sensorCoordsVP.reset(new Viewport ("new viewport"));
    addAndMakeVisible (sensorCoordsVP.get());
    sensorCoordsView_handle = new sensorCoordsView(p, MAX_NUM_CHANNELS, array2sh_getNumSensors(hA2sh));
    sensorCoordsVP->setViewedComponent (sensorCoordsView_handle);
    sensorCoordsVP->setScrollBarsShown (true, false);
    sensorCoordsVP->setAlwaysOnTop(true);
    sensorCoordsVP->setBounds(24, 224, 184, 200);
    sensorCoordsView_handle->setQ(array2sh_getNumSensors(hA2sh));

    /* disable unsuitable parameters */
    bool shouldBeEnabled = array2sh_getWeightType(hA2sh) > WEIGHT_RIGID_DIPOLE ? false : true; /* is it a rigid array? */
    RSlider->setEnabled(shouldBeEnabled);
    shouldBeEnabled = array2sh_getArrayType(hA2sh) != ARRAY_SPHERICAL ? false : true;  /* is it a cylindrical array? */
    weightTypeCB->setItemEnabled(WEIGHT_RIGID_CARD, shouldBeEnabled);
    weightTypeCB->setItemEnabled(WEIGHT_RIGID_DIPOLE, shouldBeEnabled);
    weightTypeCB->setItemEnabled(WEIGHT_OPEN_CARD, shouldBeEnabled);
    weightTypeCB->setItemEnabled(WEIGHT_OPEN_DIPOLE, shouldBeEnabled);

    /* Presets */
    presetCB->setTextWhenNothingSelected (TRANS("Default"));
    presetCB->addItem (TRANS("Sennheiser Ambeo"), MICROPHONE_ARRAY_PRESET_SENNHEISER_AMBEO);
    presetCB->addItem (TRANS("Core Sound TetraMic"), MICROPHONE_ARRAY_PRESET_CORE_SOUND_TETRAMIC);
    presetCB->addItem (TRANS("Zoom H3-VR"), MICROPHONE_ARRAY_PRESET_ZOOM_H3VR_PRESET);
    presetCB->addItem (TRANS("Sound-field SPS200"), MICROPHONE_ARRAY_PRESET_SOUND_FIELD_SPS200);
    presetCB->addItem (TRANS("Zylia 1D"), MICROPHONE_ARRAY_PRESET_ZYLIA_1D);
    presetCB->addItem (TRANS("Eigenmike32"), MICROPHONE_ARRAY_PRESET_EIGENMIKE32);
    presetCB->addItem (TRANS("Eigenmike64"), MICROPHONE_ARRAY_PRESET_EIGENMIKE64);
    presetCB->addItem (TRANS("DTU mic"), MICROPHONE_ARRAY_PRESET_DTU_MIC );
    presetCB->addItem (TRANS("Aalto Hydro"), MICROPHONE_ARRAY_PRESET_AALTO_HYDROPHONE);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

    /* grab current parameter settings */
    int curOrder = CBencodingOrder->getSelectedId();
    QSlider->setRange((curOrder+1)*(curOrder+1), array2sh_getMaxNumSensors(), 1);
    QSlider->setValue(array2sh_getNumSensors(hA2sh), sendNotification);
    RSlider->setValue(array2sh_getR(hA2sh)*1e3f, sendNotification);
    CHOrderingCB->setSelectedId(array2sh_getChOrder(hA2sh), sendNotification);
    normalisationCB->setSelectedId(array2sh_getNormType(hA2sh), sendNotification);
    CHOrderingCB->setItemEnabled(CH_FUMA, array2sh_getEncodingOrder(hA2sh)==SH_ORDER_FIRST ? true : false);
    normalisationCB->setItemEnabled(NORM_FUMA, array2sh_getEncodingOrder(hA2sh)==SH_ORDER_FIRST ? true : false);

    /* tooltips */
    CBencodingOrder->setTooltip("Encoding order. Note that the plug-in will require at least (order+1)^2 microphone array signals as input.");
    presetCB->setTooltip("Presets for various microphone arrays, which appropriately configures the sensor directions and some other specifications.");
    cSlider->setTooltip("Speed of sound of the medium. Air ~343 m/s, water ~1484 m/s (temperature and salinity dependent though).");
    regAmountSlider->setTooltip("Maximum gain amplification permitted. Higher-values give a wider frequency range of usable spherical harmonic components, but at the cost of increased sensor noise at lower frequencies.");
    gainSlider->setTooltip("Post-gain factor (in dB).");
    arrayTypeCB->setTooltip("Array type. Since the plug-in relies purely on theory, only shapes which have analytical descriptions available are supported; namely, spheres or infinitely long cylinders.");
    weightTypeCB->setTooltip("Array construction and sensor directivity. Either open (e.g. A-format) or rigid (e.g. Eigenmike or Zylia), with usually either cardioid or omnidirectional sensors, respectively.");
    filterTypeCB->setTooltip("Encoding filter design approach. Tikhonov is generally recommended as a starting point. However, Z-style may work better for Ambisonic reproduction purposes, and it can also have max_rE weights baked into the signals at the encoding stage.");
    CHOrderingCB->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    normalisationCB->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    tb_loadJSON->setTooltip("Loads microphone array sensor directions from a JSON file. The JSON file format follows the same convention as the one employed by the IEM plugin suite (https://plugins.iem.at/docs/configurationfiles/).");
    tb_saveJSON->setTooltip("Saves the current microphone array sensor directions to a JSON file. The JSON file format follows the same convention as the one employed by the IEM plugin suite (https://plugins.iem.at/docs/configurationfiles/).");
    textButton->setTooltip("Anlyses the performance of the currently configured microphone array, based on established objective metrics. The plug-in first simulates the microphone array and applies the current encoding matrix to it, subsequently comparing the resulting patterns with ideal spherical harmonics.");
    dispWindow->setTooltip("Switches between the different display options. \n\nFilters: order-dependent equalisation curves, which are applied to eliminate the effect of the sphere. \n\nCorr: The spatial correlation is derived by comparing the patterns of the array responses with the patterns of ideal spherical harmonics, where '1' means they are perfect, and '0' completely uncorrelated; the spatial aliasing frequency can therefore be observed for each order, as the point where the spatial correlation tends towards 0. \n\nLdiff: The level difference is the mean level difference over all directions (diffuse level difference) between the ideal and simulated components. One can observe that higher permitted amplification limits [Max Gain (dB)] will result in noisier signals; however, this will also result in a wider frequency range of useful spherical harmonic components at each order.");
    applyDiffEQ->setTooltip("Applies diffuse-field equalisation past the theoretical spatial aliasing frequency of the currently configured microphone array. This may help reduce any 'harshness' perceived at the high frequencies after decoding, since this will flatten any gain boosting happening up there.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("This plug-in spatially encodes spherical/cylindrical array signals into spherical harmonic signals (aka: Ambisonic or B-Format signals). The plug-in utilises analytical descriptors, which ascertain the frequency and order-dependent influence that the physical properties of the array have on the plane-waves arriving at its surface. The plug-in then determines the order-dependent equalisation curves needed to be imposed onto the initial spherical harmonic signals estimate, in order to remove the influence of the array itself. However, especially for higher-orders, this generally results in a large amplification of the low frequencies (including the sensor noise at these frequencies that accompanies it); therefore, four different regularisation approaches have been integrated into the plug-in, which allow the user to make a compromise between noise amplification and transform accuracy. These target (faint lines) and regularised (solid lines) equalisation curves are depicted on the user interface.\n\n")+
                                  TRANS("Note that this ability to balance the noise amplification with the accuracy of the spatial encoding (to better suit a given application) is very important, for example: the perceived fidelity of Ambisonic decoded audio can be rather poor if the noise amplification is set too high, which is also sound-scene dependent (since there are likely different tolerance limits for e.g. an orchestral recording vs a metal band recording...). Also, in general, a lower amplification regularisation limit is used for Ambisonics reproduction applications, when compared to sound-field visualisation algorithms, or beamformers that employ appropriate post-filtering etc."));
    addAndMakeVisible (publicationLink);
    publicationLink.setColour (HyperlinkButton::textColourId, Colours::lightblue);
    publicationLink.setBounds(getBounds().getWidth()-80, 4, 80, 12);
    publicationLink.setJustificationType(Justification::centredLeft);

	/* Specify screen refresh rate */
    startTimer(40);

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    presetCB = nullptr;
    arrayTypeCB = nullptr;
    QSlider = nullptr;
    rSlider = nullptr;
    RSlider = nullptr;
    cSlider = nullptr;
    weightTypeCB = nullptr;
    filterTypeCB = nullptr;
    regAmountSlider = nullptr;
    CHOrderingCB = nullptr;
    normalisationCB = nullptr;
    gainSlider = nullptr;
    textButton = nullptr;
    dispWindow = nullptr;
    tb_loadJSON = nullptr;
    tb_saveJSON = nullptr;
    CBencodingOrder = nullptr;
    applyDiffEQ = nullptr;

    setLookAndFeel(nullptr);
    eqviewIncluded = nullptr;
    cohviewIncluded = nullptr;
    ldiffviewIncluded = nullptr;
    sensorCoordsVP = nullptr;
    sensorCoordsView_handle = nullptr;
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 240, width = 800, height = 210;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             448.0f - 240.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             352.0f - 240.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 30, width = 800, height = 210;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             128.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 798.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             792.0f - 1.0f + x,
                                             24.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 12, y = 56, width = 204, height = 32;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 228, y = 56, width = 556, height = 209;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 280, y = 70, width = 456, height = 158;
        juce::Colour fillColour = juce::Colour (0x13000000);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 506, y = 264, width = 278, height = 104;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 506, y = 264, width = 278, height = 104;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 506, y = 367, width = 278, height = 69;
        juce::Colour fillColour = juce::Colour (0x13f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 228, y = 264, width = 279, height = 172;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 228, y = 264, width = 279, height = 38;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 87, width = 204, height = 106;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 20, y = 57, width = 67, height = 30;
        juce::String text (TRANS ("Presets: "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 20, y = 91, width = 180, height = 30;
        juce::String text (TRANS ("Number of Sensors: "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 20, y = 123, width = 180, height = 30;
        juce::String text (TRANS ("Array radius:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 20, y = 155, width = 180, height = 30;
        juce::String text (TRANS ("Baffle radius:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 12, y = 192, width = 204, height = 244;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 240, y = 337, width = 172, height = 30;
        juce::String text (TRANS ("Speed of Sound:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 240, y = 369, width = 172, height = 30;
        juce::String text (TRANS ("Array Type:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 240, y = 401, width = 172, height = 30;
        juce::String text (TRANS ("Baffle-Directivity:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 520, y = 268, width = 172, height = 30;
        juce::String text (TRANS ("Filter Approach:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 520, y = 301, width = 172, height = 30;
        juce::String text (TRANS ("Max Gain:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 520, y = 369, width = 172, height = 30;
        juce::String text (TRANS ("Channel Order:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 520, y = 401, width = 172, height = 30;
        juce::String text (TRANS ("Normalisation:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 520, y = 334, width = 172, height = 30;
        juce::String text (TRANS ("Post Gain:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 75, y = 193, width = 101, height = 30;
        juce::String text (TRANS ("Azi   #   Elev"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 24, y = 224, width = 184, height = 200;
        juce::Colour strokeColour = juce::Colour (0x29b6b5b5);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 92, y = 30, width = 88, height = 30;
        juce::String text (TRANS ("Inputs"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 440, y = 30, width = 149, height = 30;
        juce::String text (TRANS ("Encoding Settings"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 240, y = 268, width = 172, height = 30;
        juce::String text (TRANS ("Encoding Order:"));
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
        juce::String text (TRANS ("Array2SH"));
        juce::Colour fillColour = juce::Colour (0xffe9ff00);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 240, y = 305, width = 248, height = 30;
        juce::String text (TRANS ("Enable Diffuse-EQ Past Aliasing:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 328, y = 65, width = 392, height = 31;
        juce::String text (TRANS ("Press the \"Analyse\" button"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 291, y = 88, width = 477, height = 23;
        juce::String text (TRANS ("Corr: The spatial correlation is derived by comparing the patterns of the array responses with"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 291, y = 104, width = 477, height = 23;
        juce::String text (TRANS ("the patterns of ideal spherical harmonics, where \'1\' means they are perfect, and \'0\' completely "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 291, y = 120, width = 477, height = 23;
        juce::String text (TRANS ("uncorrelated; the spatial aliasing frequency can therefore be observed for each order, as the "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 291, y = 160, width = 477, height = 23;
        juce::String text (TRANS ("Ldiff: The level difference is the mean level difference over all directions (diffuse level differe-"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 291, y = 192, width = 477, height = 23;
        juce::String text (TRANS ("amplification limits [Max Gain (dB)] will result in noisier signals; however, this will also result in "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 291, y = 176, width = 477, height = 23;
        juce::String text (TRANS ("nce) between the ideal and simulated components. One can observe that higher permitted "));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 291, y = 136, width = 477, height = 23;
        juce::String text (TRANS ("point where the spatial correlation tends towards 0."));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 291, y = 208, width = 477, height = 23;
        juce::String text (TRANS ("a wider frequency range of useful spherical harmonic components at each order."));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 673, y = 33, width = 119, height = 25;
        juce::String text (TRANS ("Display:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 802, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 448, width = 802, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 450;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 798, y = 0, width = 2, height = 450;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 12, y = 56, width = 204, height = 32;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

	g.setColour(Colours::white);
	g.setFont(juce::FontOptions (11.00f, Font::plain));
    g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		185, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(array2sh_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(array2sh_getSamplingRate(hA2sh)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(array2sh_getNumSensors(hA2sh)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
                       TRANS("/") + String(array2sh_getNSHrequired(hA2sh)) + TRANS(")"),
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
    if (comboBoxThatHasChanged == presetCB.get())
    {
        array2sh_setPreset(hA2sh, (ARRAY2SH_MICROPHONE_ARRAY_PRESETS)presetCB->getSelectedId());

        /* grab current parameter settings */
        processor.setParameterValue("outputOrder", array2sh_getEncodingOrder(hA2sh)-1);
        int curOrder = CBencodingOrder->getSelectedId();
        QSlider->setRange((curOrder+1)*(curOrder+1), array2sh_getMaxNumSensors(), 1);
        
        processor.setParameterValue("arrayRadius", array2sh_getr(hA2sh)*1e3f);
        processor.setParameterValue("baffleRadius", array2sh_getR(hA2sh)*1e3f);
        processor.setParameterValue("speedOfSound", array2sh_getc(hA2sh));
        processor.setParameterValue("weightType", array2sh_getWeightType(hA2sh)-1);
        processor.setParameterValue("arrayType", array2sh_getArrayType(hA2sh)-1);
        CHOrderingCB->setSelectedId(array2sh_getChOrder(hA2sh), sendNotification);
        normalisationCB->setSelectedId(array2sh_getNormType(hA2sh), sendNotification);

        /* update view windows */
        sensorCoordsView_handle->setQ(array2sh_getNumSensors(hA2sh));
        
        processor.setParameterValue("numSensors", array2sh_getNumSensors(hA2sh));
        for(int i=0; i<array2sh_getNumSensors(hA2sh); i++){
            processor.setParameterValue("azim" + juce::String(i), array2sh_getSensorAzi_deg(hA2sh,i));
            processor.setParameterValue("elev" + juce::String(i), array2sh_getSensorElev_deg(hA2sh,i));
        }

        needScreenRefreshFLAG = true;
    }
    else if (comboBoxThatHasChanged == arrayTypeCB.get())
    {
        needScreenRefreshFLAG = true;
    }
    else if (comboBoxThatHasChanged == weightTypeCB.get())
    {
        needScreenRefreshFLAG = true;
    }
    else if (comboBoxThatHasChanged == filterTypeCB.get())
    {
        needScreenRefreshFLAG = true;
    }
    else if (comboBoxThatHasChanged == dispWindow.get())
    {
        dispID = (DISP_WINDOW)dispWindow->getSelectedId();
        needScreenRefreshFLAG = 1;
    }
    else if (comboBoxThatHasChanged == CBencodingOrder.get())
    {
        needScreenRefreshFLAG = true;
    }

    /* disable unsuitable parameters */
    bool shouldBeEnabled = array2sh_getWeightType(hA2sh) > WEIGHT_RIGID_DIPOLE ? false : true; /* is it a rigid array? */
    RSlider->setEnabled(shouldBeEnabled);
    shouldBeEnabled = array2sh_getArrayType(hA2sh) != ARRAY_SPHERICAL ? false : true;  /* is it a cylindrical array? */
    weightTypeCB->setItemEnabled(WEIGHT_RIGID_CARD, shouldBeEnabled);
    weightTypeCB->setItemEnabled(WEIGHT_RIGID_DIPOLE, shouldBeEnabled);
    weightTypeCB->setItemEnabled(WEIGHT_OPEN_CARD, shouldBeEnabled);
    weightTypeCB->setItemEnabled(WEIGHT_OPEN_DIPOLE, shouldBeEnabled);
//    if( (array2sh_getArrayType(hA2sh) == 2) && ((array2sh_getWeightType(hA2sh) == 3) || (array2sh_getWeightType(hA2sh) == 4)) )
//        weightTypeCB->setSelectedId(1, sendNotification); /* force a suitable option */
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == QSlider.get())
    {
        needScreenRefreshFLAG = true;
    }
    else if (sliderThatWasMoved == rSlider.get())
    {
        needScreenRefreshFLAG = true;
    }
    else if (sliderThatWasMoved == RSlider.get())
    {
//        bool changerToo = (array2sh_getWeightType(hA2sh) == WEIGHT_RIGID_OMNI) ||
//            (array2sh_getWeightType(hA2sh) == WEIGHT_RIGID_CARD) ||
//            (array2sh_getWeightType(hA2sh) == WEIGHT_RIGID_DIPOLE) ? true : false; /* is it a rigid array? */
//        if(changerToo){
//            processor.setParameterValue("arrayRadius", (float)RSlider->getValue());
//        }
        needScreenRefreshFLAG = true;
    }
    else if (sliderThatWasMoved == cSlider.get())
    {
        needScreenRefreshFLAG = true;
    }
    else if (sliderThatWasMoved == regAmountSlider.get())
    {
        needScreenRefreshFLAG = true;
    }
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == textButton.get())
    {
        array2sh_setRequestEncoderEvalFLAG(hA2sh, 1);
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
    else if (buttonThatWasClicked == applyDiffEQ.get())
    {
        needScreenRefreshFLAG = true;
    }
}

void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    int curOrder = CBencodingOrder->getSelectedId();
    QSlider->setRange((curOrder+1)*(curOrder+1), array2sh_getMaxNumSensors(), 1);
    QSlider->setValue(array2sh_getNumSensors(hA2sh), sendNotification);
    rSlider->setValue(array2sh_getr(hA2sh)*1e3f, sendNotification);
    RSlider->setValue(array2sh_getR(hA2sh)*1e3f, sendNotification);
    weightTypeCB->setSelectedId(array2sh_getWeightType(hA2sh), sendNotification);
    sensorCoordsView_handle->setQ(array2sh_getNumSensors(hA2sh));
    CHOrderingCB->setSelectedId(array2sh_getChOrder(hA2sh), sendNotification);
    normalisationCB->setSelectedId(array2sh_getNormType(hA2sh), sendNotification);
    CHOrderingCB->setItemEnabled(CH_FUMA, array2sh_getEncodingOrder(hA2sh)==SH_ORDER_FIRST ? true : false);
    normalisationCB->setItemEnabled(NORM_FUMA, array2sh_getEncodingOrder(hA2sh)==SH_ORDER_FIRST ? true : false);

    /* check if eval curves have recently been computed */
    if(array2sh_getEvalStatus(hA2sh)==EVAL_STATUS_RECENTLY_EVALUATED){
        needScreenRefreshFLAG = true;
        array2sh_setEvalStatus(hA2sh, EVAL_STATUS_EVALUATED);
    }

    /* disable certain sliders if evaluation is ongoing */
    bool RshouldBeEnabled = array2sh_getWeightType(hA2sh) > WEIGHT_RIGID_DIPOLE ? false : true; /* is it a rigid array? */
    if(array2sh_getEvalStatus(hA2sh)==EVAL_STATUS_EVALUATING){
        if(presetCB->isEnabled())
            presetCB->setEnabled(false);
        if(arrayTypeCB->isEnabled())
            arrayTypeCB->setEnabled(false);
        if(QSlider->isEnabled())
            QSlider->setEnabled(false);
        if(rSlider->isEnabled())
            rSlider->setEnabled(false);
        if(RSlider->isEnabled() || !RshouldBeEnabled)
           RSlider->setEnabled(false);
        if(cSlider->isEnabled())
            cSlider->setEnabled(false);
        if(weightTypeCB->isEnabled())
            weightTypeCB->setEnabled(false);
        if(filterTypeCB->isEnabled())
            filterTypeCB->setEnabled(false);
        if(regAmountSlider->isEnabled())
            regAmountSlider->setEnabled(false);
        if(tb_loadJSON->isEnabled())
            tb_loadJSON->setEnabled(false);
        if(CBencodingOrder->isEnabled())
            CBencodingOrder->setEnabled(false);
        if(applyDiffEQ->isEnabled())
            applyDiffEQ->setEnabled(false);
        if(sensorCoordsVP->isEnabled())
            sensorCoordsVP->setEnabled(false);
    }
    else{
        if(!presetCB->isEnabled())
            presetCB->setEnabled(true);
        if(!arrayTypeCB->isEnabled())
            arrayTypeCB->setEnabled(true);
        if(!QSlider->isEnabled())
            QSlider->setEnabled(true);
        if(!rSlider->isEnabled())
            rSlider->setEnabled(true);
        if(!RSlider->isEnabled() && RshouldBeEnabled)
            RSlider->setEnabled(true);
        if(!cSlider->isEnabled())
            cSlider->setEnabled(true);
        if(!weightTypeCB->isEnabled())
            weightTypeCB->setEnabled(true);
        if(!filterTypeCB->isEnabled())
            filterTypeCB->setEnabled(true);
        if(!regAmountSlider->isEnabled())
            regAmountSlider->setEnabled(true);
        if(!tb_loadJSON->isEnabled())
            tb_loadJSON->setEnabled(true);
        if(!CBencodingOrder->isEnabled())
            CBencodingOrder->setEnabled(true);
        if(!applyDiffEQ->isEnabled())
            applyDiffEQ->setEnabled(true);
        if(!sensorCoordsVP->isEnabled())
            sensorCoordsVP->setEnabled(true);
    }

    /* draw magnitude/spatial-correlation/level-difference curves */
    if (needScreenRefreshFLAG && !array2sh_getReinitSHTmatrixFLAG(hA2sh)){
        switch(dispID){
            default:
            case SHOW_EQ:
                eqviewIncluded->setNumCurves(array2sh_getEncodingOrder(hA2sh)+1);
                eqviewIncluded->setVisible(true);
                cohviewIncluded->setVisible(false);
                ldiffviewIncluded->setVisible(false);
                eqviewIncluded->repaint();
                break;
            case SHOW_SPATIAL_COH:
                eqviewIncluded->setVisible(false);
                ldiffviewIncluded->setVisible(false);
                if((array2sh_getEvalStatus(hA2sh) == EVAL_STATUS_EVALUATED)){
                    cohviewIncluded->setNumCurves(array2sh_getEncodingOrder(hA2sh)+1);
                    cohviewIncluded->setVisible(true);
                    cohviewIncluded->repaint();
                }
                else
                    cohviewIncluded->setVisible(false);
                break;
            case SHOW_LEVEL_DIFF:
                eqviewIncluded->setVisible(false);
                cohviewIncluded->setVisible(false);
                if((array2sh_getEvalStatus(hA2sh) == EVAL_STATUS_EVALUATED)){
                    ldiffviewIncluded->setNumCurves(array2sh_getEncodingOrder(hA2sh)+1);
                    ldiffviewIncluded->setVisible(true);
                    ldiffviewIncluded->repaint();
                }
                else
                    ldiffviewIncluded->setVisible(false);
                break;
        }
        needScreenRefreshFLAG = false;
    }

    /* Progress bar */
    if(array2sh_getEvalStatus(hA2sh)==EVAL_STATUS_EVALUATING){
        addAndMakeVisible(progressbar);
        progress = (double)array2sh_getProgressBar0_1(hA2sh);
        char text[PROGRESSBARTEXT_CHAR_LENGTH];
        array2sh_getProgressBarText(hA2sh, (char*)text);
        progressbar.setTextToDisplay(String(text));
    }
    else
        removeChildComponent(&progressbar);

    /* Hide decoding orders that are unsuitable for the current number of sensors */
    for(int i=1; i<=MAX_SH_ORDER; i++)
        CBencodingOrder->setItemEnabled(i, (i+1)*(i+1) <= array2sh_getNumSensors(hA2sh) ? true : false);

    /* display warning message, if needed */
    if ((processor.getCurrentBlockSize() % array2sh_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ( !((array2sh_getSamplingRate(hA2sh) == 44.1e3) || (array2sh_getSamplingRate(hA2sh) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumInputs() < array2sh_getNumSensors(hA2sh))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumOutputs() < array2sh_getNSHrequired(hA2sh))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}

