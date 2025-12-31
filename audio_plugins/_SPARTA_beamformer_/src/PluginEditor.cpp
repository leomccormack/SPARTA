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
    : AudioProcessorEditor(p), processor(p)
{
    SL_num_beams = std::make_unique<SliderWithAttachment>(p.parameters, "numBeams");
    addAndMakeVisible (SL_num_beams.get());
    SL_num_beams->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_beams->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_beams->setBounds (640, 96, 48, 20);

    CBoutputFormat = std::make_unique<ComboBoxWithAttachment>(p.parameters, "channelOrder");
    addAndMakeVisible (CBoutputFormat.get());
    CBoutputFormat->setEditableText (false);
    CBoutputFormat->setJustificationType (juce::Justification::centredLeft);
    CBoutputFormat->setBounds (133, 316, 112, 20);

    CBnormalisation = std::make_unique<ComboBoxWithAttachment>(p.parameters, "normType");
    addAndMakeVisible (CBnormalisation.get());
    CBnormalisation->setEditableText (false);
    CBnormalisation->setJustificationType (juce::Justification::centredLeft);
    CBnormalisation->setBounds (368, 316, 112, 20);

    CBorder = std::make_unique<ComboBoxWithAttachment>(p.parameters, "inputOrder");
    addAndMakeVisible (CBorder.get());
    CBorder->setEditableText (false);
    CBorder->setJustificationType (juce::Justification::centredLeft);
    CBorder->setBounds (578, 64, 112, 20);

    CBbeamType = std::make_unique<ComboBoxWithAttachment>(p.parameters, "beamType");
    addAndMakeVisible (CBbeamType.get());
    CBbeamType->setEditableText (false);
    CBbeamType->setJustificationType (juce::Justification::centredLeft);
    CBbeamType->setBounds (594, 125, 96, 20);

    setSize (708, 356);

    /* handle */
    hBeam = processor.getFXHandle();

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_num_beams->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_beams->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_beams->setSliderSnapsToMousePosition(false);

    /* source coordinates viewport */
    sourceCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (sourceCoordsVP.get());
    sourceCoordsView_handle = new inputCoordsView(p, MAX_NUM_CHANNELS, beamformer_getNumBeams(hBeam));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(510, 183, 184, 155);
    sourceCoordsView_handle->setNCH(beamformer_getNumBeams(hBeam));

    /* grab current parameter settings */
    CBoutputFormat->setSelectedId(beamformer_getChOrder(hBeam), dontSendNotification);
    CBnormalisation->setSelectedId(beamformer_getNormType(hBeam), dontSendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, beamformer_getBeamOrder(hBeam)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, beamformer_getBeamOrder(hBeam)==SH_ORDER_FIRST ? true : false);

    /* create panning window */
    panWindow.reset (new pannerView(p, 480, 240));
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
    stopTimer();
    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    using namespace ColoursUI;

    drawPluginBackgroundAndBanner(g, getBounds());

    /* Panels */
    drawPanel(g, {500,  58,196, 32}, panelFillLight, panelStroke);
    drawPanel(g, {500,  89,196, 64}, panelFill,      panelStroke);
    drawPanel(g, {12,   58,480,240}, panelFill,      panelStroke);
    drawPanel(g, {500, 152,196,194}, panelFill,      panelStroke);
    drawPanel(g, {12,  306,480, 40}, panelFill,      panelStroke);
    drawPanel(g, {500,  58,196, 32}, panelFill,      panelStroke);
    drawPanel(g, {12,   58,204, 32}, panelFill,      panelStroke);
    drawPanel(g, {12,   58,204, 32}, panelFillLight, panelStroke);

    /* Section titles */
    drawLabel(g, {552, 32,108,30}, "Beam Settings",    15.f);
    drawLabel(g, {197, 32,163,30}, "Steering Window",  15.f);

    /* Beam settings */
    drawLabel(g, {508, 59, 67,30}, "Order:",           15.f);
    drawLabel(g, {508, 90,180,30}, "Number of Beams:", 14.5f);
    drawLabel(g, {508,120,124,30}, "Beam Type:",       14.5f);

    /* Channel order + normalisation */
    drawLabel(g, {23, 311,145,30}, "Channel Order:",   15.f);
    drawLabel(g, {263,311,145,30}, "Normalisation:",   15.f);

    /* Title */
    drawLabel(g, {16, 1,100,32}, "SPARTA|", 18.f);
    drawLabel(g, {92,  1,132,32}, "Beamformer", 18.f, juce::Justification::centredLeft, juce::Colour(0xff4fd1ff));

    /* Azi° # Elev° label */
    drawLabel(g, {556,154,108,28}, juce::CharPointer_UTF8("Azi\xc2\xb0   #   Elev\xc2\xb0"), 15.f);
    
    g.setColour(Colours::white);
    g.setFont(juce::FontOptions(11.00f, Font::plain));
    g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
        200, 16, 530, 11,
        Justification::centredLeft, true);

    /* display warning message */
    g.setFont(juce::FontOptions(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.setColour(Colours::red);
            g.drawText(TRANS("Set frame size to multiple of ") + String(beamformer_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(beamformer_getNSHrequired(hBeam)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
                       TRANS("/") + String(beamformer_getNumBeams(hBeam)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_busContainsLFE:
            g.setColour(Colours::yellow);
            g.drawText(TRANS("LFE channels are not supported by this plugin"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
    }
}

void PluginEditor::resized()
{
}

void PluginEditor::sliderValueChanged (juce::Slider* /*sliderThatWasMoved*/)
{
}

void PluginEditor::comboBoxChanged (juce::ComboBox* /*comboBoxThatHasChanged*/)
{
}

void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    sourceCoordsView_handle->setNCH(beamformer_getNumBeams(hBeam));
    CBoutputFormat->setSelectedId(beamformer_getChOrder(hBeam), sendNotification);
    CBnormalisation->setSelectedId(beamformer_getNormType(hBeam), sendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, beamformer_getBeamOrder(hBeam)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, beamformer_getBeamOrder(hBeam)==SH_ORDER_FIRST ? true : false);

    /* refresh pan view */
    if((refreshPanViewWindow == true) || (panWindow->getBeamIconIsClicked()) || processor.getRefreshWindow()){
        panWindow->refreshPanView();
        refreshPanViewWindow = false;
        processor.setRefreshWindow(false);
    }

    /* display warning message, if needed */
    if ((processor.getCurrentBlockSize() % beamformer_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumInputs() < beamformer_getNSHrequired(hBeam))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumOutputs() < beamformer_getNumBeams(hBeam))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if (processor.getBusHasLFE()){
        currentWarning = k_warning_busContainsLFE;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}

