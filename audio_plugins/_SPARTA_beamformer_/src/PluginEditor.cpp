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
    : AudioProcessorEditor(ownerFilter)
{
    SL_num_beams.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_beams.get());
    SL_num_beams->setRange (1, 128, 1);
    SL_num_beams->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_beams->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_beams->addListener (this);

    SL_num_beams->setBounds (640, 96, 48, 20);

    CBoutputFormat.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBoutputFormat.get());
    CBoutputFormat->setEditableText (false);
    CBoutputFormat->setJustificationType (juce::Justification::centredLeft);
    CBoutputFormat->setTextWhenNothingSelected (TRANS ("ACN"));
    CBoutputFormat->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBoutputFormat->addListener (this);

    CBoutputFormat->setBounds (133, 316, 112, 20);

    CBnormalisation.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBnormalisation.get());
    CBnormalisation->setEditableText (false);
    CBnormalisation->setJustificationType (juce::Justification::centredLeft);
    CBnormalisation->setTextWhenNothingSelected (TRANS ("N3D"));
    CBnormalisation->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBnormalisation->addListener (this);

    CBnormalisation->setBounds (368, 316, 112, 20);

    CBorder.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBorder.get());
    CBorder->setEditableText (false);
    CBorder->setJustificationType (juce::Justification::centredLeft);
    CBorder->setTextWhenNothingSelected (juce::String());
    CBorder->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBorder->addListener (this);

    CBorder->setBounds (578, 64, 112, 20);

    CBbeamType.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBbeamType.get());
    CBbeamType->setEditableText (false);
    CBbeamType->setJustificationType (juce::Justification::centredLeft);
    CBbeamType->setTextWhenNothingSelected (juce::String());
    CBbeamType->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBbeamType->addListener (this);

    CBbeamType->setBounds (594, 125, 96, 20);

    setSize (708, 356);

    /* handle to pluginProcessor */
	hVst = ownerFilter;
    hBeam = hVst->getFXHandle();

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_num_beams->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_beams->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_beams->setSliderSnapsToMousePosition(false);

    /* add combobox options */
    CBorder->addItem (TRANS("1st order"), SH_ORDER_FIRST);
    CBorder->addItem (TRANS("2nd order"), SH_ORDER_SECOND);
    CBorder->addItem (TRANS("3rd order"), SH_ORDER_THIRD);
    CBorder->addItem (TRANS("4th order"), SH_ORDER_FOURTH);
    CBorder->addItem (TRANS("5th order"), SH_ORDER_FIFTH);
    CBorder->addItem (TRANS("6th order"), SH_ORDER_SIXTH);
    CBorder->addItem (TRANS("7th order"), SH_ORDER_SEVENTH);
    CBorder->addItem (TRANS("8th order"), SH_ORDER_EIGHTH);
    CBorder->addItem (TRANS("9th order"), SH_ORDER_NINTH);
    CBorder->addItem (TRANS("10th order"), SH_ORDER_TENTH);
    CBbeamType->addItem(TRANS("Cardioid"), STATIC_BEAM_TYPE_CARDIOID);
    CBbeamType->addItem(TRANS("HyperCard"), STATIC_BEAM_TYPE_HYPERCARDIOID);
    CBbeamType->addItem(TRANS("MaxEV"), STATIC_BEAM_TYPE_MAX_EV);
    CBoutputFormat->addItem (TRANS("ACN"), CH_ACN);
    CBoutputFormat->addItem (TRANS("FuMa"), CH_FUMA);
    CBnormalisation->addItem (TRANS("N3D"), NORM_N3D);
    CBnormalisation->addItem (TRANS("SN3D"), NORM_SN3D);
    CBnormalisation->addItem (TRANS("FuMa"), NORM_FUMA);

    /* source coordinates viewport */
    sourceCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (sourceCoordsVP.get());
    sourceCoordsView_handle = new inputCoordsView(ownerFilter, MAX_NUM_CHANNELS, beamformer_getNumBeams(hBeam));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(510, 183, 184, 155);
    sourceCoordsView_handle->setNCH(beamformer_getNumBeams(hBeam));

    /* grab current parameter settings */
    SL_num_beams->setValue(beamformer_getNumBeams(hBeam),dontSendNotification);
    CBoutputFormat->setSelectedId(beamformer_getChOrder(hBeam), dontSendNotification);
    CBnormalisation->setSelectedId(beamformer_getNormType(hBeam), dontSendNotification);
    CBorder->setSelectedId(beamformer_getBeamOrder(hBeam), dontSendNotification);
    CBbeamType->setSelectedId(beamformer_getBeamType(hBeam), dontSendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, beamformer_getBeamOrder(hBeam)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, beamformer_getBeamOrder(hBeam)==SH_ORDER_FIRST ? true : false);

    /* create panning window */
    panWindow.reset (new pannerView(ownerFilter, 480, 240));
    addAndMakeVisible (panWindow.get());
    panWindow->setBounds (12, 58, 480, 240);
    refreshPanViewWindow = true;

    /* tooltips */
    CBorder->setTooltip("Beamforming order. Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals as input.");
    CBbeamType->setTooltip("Beamformer pattern.");
    CBoutputFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormalisation->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A simple beamforming plug-in using Ambisonic signals as input; offering a variety of different static beam-pattern options.\n"));

	/* Specify screen refresh rate */
    startTimer(40);//80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    SL_num_beams = nullptr;
    CBoutputFormat = nullptr;
    CBnormalisation = nullptr;
    CBorder = nullptr;
    CBbeamType = nullptr;

    setLookAndFeel(nullptr);
    sourceCoordsVP = nullptr;
    panWindow = nullptr;
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 30, width = 708, height = 163;
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
        int x = 0, y = 193, width = 708, height = 163;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             360.0f - 193.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             280.0f - 193.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 706.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             696.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 500, y = 58, width = 196, height = 32;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 500, y = 89, width = 196, height = 64;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 508, y = 120, width = 124, height = 30;
        juce::String text (TRANS ("Beam Type:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 12, y = 58, width = 480, height = 240;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 500, y = 152, width = 196, height = 194;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 508, y = 90, width = 180, height = 30;
        juce::String text (TRANS ("Number of Beams:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.50f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 552, y = 32, width = 108, height = 30;
        juce::String text (TRANS ("Beam Settings"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 197, y = 32, width = 163, height = 30;
        juce::String text (TRANS ("Steering Window"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 12, y = 306, width = 480, height = 40;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 23, y = 311, width = 145, height = 30;
        juce::String text (TRANS ("Channel Order:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 263, y = 311, width = 145, height = 30;
        juce::String text (TRANS ("Normalisation:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 500, y = 58, width = 196, height = 32;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 508, y = 60, width = 67, height = 30;
        juce::String text (TRANS ("Order: "));
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
        int x = 92, y = 1, width = 132, height = 32;
        juce::String text (TRANS ("Beamformer"));
        juce::Colour fillColour = juce::Colour (0xff4fd1ff);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 554, y = 154, width = 108, height = 28;
        juce::String text (juce::CharPointer_UTF8 ("Azi\xc2\xb0   #   Elev\xc2\xb0"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 710, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 356;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 706, y = 0, width = 2, height = 356;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 354, width = 710, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }
    
	g.setColour(Colours::white);
	g.setFont(juce::FontOptions(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		200, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(beamformer_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(beamformer_getNumBeams(hBeam)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(beamformer_getNSHrequired(hBeam)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
    }
}

void PluginEditor::resized()
{
}

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
    #pragma warning(push)
    #pragma warning(disable: 4996)  // MSVC ignore deprecated functions
#endif

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == SL_num_beams.get())
    {
        hVst->beginParameterChangeGesture(k_numBeams);
        beamformer_setNumBeams(hBeam, (int)SL_num_beams->getValue());
        hVst->endParameterChangeGesture(k_numBeams);
    }
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == CBoutputFormat.get())
    {
        hVst->beginParameterChangeGesture(k_channelOrder);
        beamformer_setChOrder(hBeam, CBoutputFormat->getSelectedId());
        hVst->endParameterChangeGesture(k_channelOrder);
    }
    else if (comboBoxThatHasChanged == CBnormalisation.get())
    {
        hVst->beginParameterChangeGesture(k_normType);
        beamformer_setNormType(hBeam, CBnormalisation->getSelectedId());
        hVst->endParameterChangeGesture(k_normType);
    }
    else if (comboBoxThatHasChanged == CBorder.get())
    {
        hVst->beginParameterChangeGesture(k_inputOrder);
        beamformer_setBeamOrder(hBeam, CBorder->getSelectedId());
        hVst->endParameterChangeGesture(k_inputOrder);
    }
    else if (comboBoxThatHasChanged == CBbeamType.get())
    {
        hVst->beginParameterChangeGesture(k_beamType);
        beamformer_setBeamType(hBeam, CBbeamType->getSelectedId());
        hVst->endParameterChangeGesture(k_beamType);
    }
}

#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#elif defined(_MSC_VER)
    #pragma warning(pop)
#endif

void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    sourceCoordsView_handle->setNCH(beamformer_getNumBeams(hBeam));
    SL_num_beams->setValue(beamformer_getNumBeams(hBeam),dontSendNotification);
    CBoutputFormat->setSelectedId(beamformer_getChOrder(hBeam), dontSendNotification);
    CBnormalisation->setSelectedId(beamformer_getNormType(hBeam), dontSendNotification);
    CBorder->setSelectedId(beamformer_getBeamOrder(hBeam), dontSendNotification);
    CBbeamType->setSelectedId(beamformer_getBeamType(hBeam), dontSendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, beamformer_getBeamOrder(hBeam)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, beamformer_getBeamOrder(hBeam)==SH_ORDER_FIRST ? true : false);
    CBoutputFormat->setItemEnabled(CH_FUMA, beamformer_getBeamOrder(hBeam)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, beamformer_getBeamOrder(hBeam)==SH_ORDER_FIRST ? true : false);

    /* refresh pan view */
    if((refreshPanViewWindow == true) || (panWindow->getBeamIconIsClicked()) ||
        sourceCoordsView_handle->getHasASliderChanged() || hVst->getRefreshWindow()){
        panWindow->refreshPanView();
        refreshPanViewWindow = false;
        sourceCoordsView_handle->setHasASliderChange(false);
        hVst->setRefreshWindow(false);
    }

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % beamformer_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < beamformer_getNumBeams(hBeam))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumOutputs() < beamformer_getNSHrequired(hBeam))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}

