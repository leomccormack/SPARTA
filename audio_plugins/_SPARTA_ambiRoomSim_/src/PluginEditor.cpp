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
    SL_num_sources = std::make_unique<SliderWithAttachment>(p.parameters, "numSources");
    addAndMakeVisible (SL_num_sources.get());
    SL_num_sources->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_sources->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_sources->addListener (this);
    SL_num_sources->setBounds (173, 303, 48, 20);

    CBoutputFormat = std::make_unique<ComboBoxWithAttachment>(p.parameters, "channelOrder");
    addAndMakeVisible (CBoutputFormat.get());
    CBoutputFormat->setEditableText (false);
    CBoutputFormat->setJustificationType (juce::Justification::centredLeft);
    CBoutputFormat->setBounds (316, 247, 76, 20);

    CBnormalisation = std::make_unique<ComboBoxWithAttachment>(p.parameters, "normType");
    addAndMakeVisible (CBnormalisation.get());
    CBnormalisation->setEditableText (false);
    CBnormalisation->setJustificationType (juce::Justification::centredLeft);
    CBnormalisation->setBounds (398, 247, 76, 20);

    CBorder = std::make_unique<ComboBoxWithAttachment>(p.parameters, "outputOrder");
    addAndMakeVisible (CBorder.get());
    CBorder->setEditableText (false);
    CBorder->setJustificationType (juce::Justification::centredLeft);
    CBorder->setBounds (156, 247, 92, 20);

    SL_num_receivers = std::make_unique<SliderWithAttachment>(p.parameters, "numReceivers");
    addAndMakeVisible (SL_num_receivers.get());
    SL_num_receivers->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_receivers->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_receivers->addListener (this);
    SL_num_receivers->setBounds (416, 303, 48, 20);

    SL_max_reflection_order = std::make_unique<SliderWithAttachment>(p.parameters, "maxReflectionOrder");
    addAndMakeVisible (SL_max_reflection_order.get());
    SL_max_reflection_order->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_max_reflection_order->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_max_reflection_order->setBounds (181, 102, 48, 20);
    
    s_attenCoeff_pX = std::make_unique<SliderWithAttachment>(p.parameters, "wallAbsCoeff_pX");
    addAndMakeVisible (s_attenCoeff_pX.get());
    s_attenCoeff_pX->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attenCoeff_pX->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_attenCoeff_pX->setBounds (256, 82, 60, 60);

    s_attenCoeff_nX = std::make_unique<SliderWithAttachment>(p.parameters, "wallAbsCoeff_nX");
    addAndMakeVisible (s_attenCoeff_nX.get());
    s_attenCoeff_nX->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attenCoeff_nX->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_attenCoeff_nX->setBounds (256, 148, 60, 60);

    s_attenCoeff_nY = std::make_unique<SliderWithAttachment>(p.parameters, "wallAbsCoeff_nY");
    addAndMakeVisible (s_attenCoeff_nY.get());
    s_attenCoeff_nY->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attenCoeff_nY->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_attenCoeff_nY->setBounds (332, 148, 60, 60);

    s_attenCoeff_nZ = std::make_unique<SliderWithAttachment>(p.parameters, "wallAbsCoeff_nZ");
    addAndMakeVisible (s_attenCoeff_nZ.get());
    s_attenCoeff_nZ->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attenCoeff_nZ->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_attenCoeff_nZ->setBounds (408, 148, 60, 60);

    s_attenCoeff_pZ = std::make_unique<SliderWithAttachment>(p.parameters, "wallAbsCoeff_pZ");
    addAndMakeVisible (s_attenCoeff_pZ.get());
    s_attenCoeff_pZ->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attenCoeff_pZ->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_attenCoeff_pZ->setBounds (408, 82, 60, 60);

    s_attenCoeff_pY = std::make_unique<SliderWithAttachment>(p.parameters, "wallAbsCoeff_pY");
    addAndMakeVisible (s_attenCoeff_pY.get());
    s_attenCoeff_pY->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attenCoeff_pY->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_attenCoeff_pY->setBounds (332, 82, 60, 60);

    s_roomLenZ = std::make_unique<SliderWithAttachment>(p.parameters, "roomZ");
    addAndMakeVisible (s_roomLenZ.get());
    s_roomLenZ->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_roomLenZ->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_roomLenZ->setBounds (170, 148, 60, 60);

    s_roomLenY = std::make_unique<SliderWithAttachment>(p.parameters, "roomY");
    addAndMakeVisible (s_roomLenY.get());
    s_roomLenY->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_roomLenY->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_roomLenY->setBounds (96, 148, 60, 60);

    s_roomLenX = std::make_unique<SliderWithAttachment>(p.parameters, "roomX");
    addAndMakeVisible (s_roomLenX.get());
    s_roomLenX->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_roomLenX->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 16);
    s_roomLenX->setBounds (21, 148, 60, 60);

    TB_enableIMS = std::make_unique<ToggleButtonWithAttachment>(p.parameters, "enableReflections");
    addAndMakeVisible (TB_enableIMS.get());
    TB_enableIMS->setButtonText (juce::String());
    TB_enableIMS->setBounds (206, 65, 26, 26);

    setSize (780, 500);

    /* handle to object */
    hAmbi = processor.getFXHandle();

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
    SL_num_receivers->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_receivers->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_receivers->setSliderSnapsToMousePosition(false);
    SL_max_reflection_order->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_max_reflection_order->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_max_reflection_order->setSliderSnapsToMousePosition(false);

    /* source coordinates viewport */
    sourceCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (sourceCoordsVP.get());
    sourceCoordsView_handle = new inputCoordsView(p, ROOM_SIM_MAX_NUM_SOURCES, ambi_roomsim_getNumSources(hAmbi));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(16, 352, 212, 32*4+2);
    sourceCoordsView_handle->setNCH(ambi_roomsim_getNumSources(hAmbi));

    /* source coordinates viewport */
    receiverCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (receiverCoordsVP.get());
    receiverCoordsView_handle = new outputCoordsView(p, ROOM_SIM_MAX_NUM_RECEIVERS, ambi_roomsim_getNumReceivers(hAmbi));
    receiverCoordsVP->setViewedComponent (receiverCoordsView_handle);
    receiverCoordsVP->setScrollBarsShown (true, false);
    receiverCoordsVP->setAlwaysOnTop(true);
    receiverCoordsVP->setBounds(256, 352, 212, 32*4+2);
    receiverCoordsView_handle->setNCH(ambi_roomsim_getNumReceivers(hAmbi));

    /* grab current parameter settings */
    CBoutputFormat->setSelectedId(ambi_roomsim_getChOrder(hAmbi), sendNotification);
    CBnormalisation->setSelectedId(ambi_roomsim_getNormType(hAmbi), sendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);

    /* create panning window */
    panWindow.reset (new pannerView(p, 600, 600));
    addAndMakeVisible (panWindow.get());
    panWindow->setBounds (490, 58, 600, 600);
    refreshPanViewWindow = true;

    /* tooltips */
    CBorder->setTooltip("The encoding order. Note that the plug-in will output (order+1)^2 Ambisonic (spherical harmonic) signals.");
    CBoutputFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormalisation->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    SL_num_sources->setTooltip("Number of sound sources to include in the simulation (one input channel for each).");
    SL_num_receivers->setTooltip("Number of Ambisonic receivers to include in the simulation (outputs stacked up to a maximum of 64 channels).");
    s_roomLenX->setTooltip("Room length along the X-axis, in metres.");
    s_roomLenY->setTooltip("Room length along the Y-axis, in metres.");
    s_roomLenZ->setTooltip("Room length along the Z-axis, in metres.");
    s_attenCoeff_pX->setTooltip("Wall absorption coefficient for the wall at which the positive X-axis intersects.");
    s_attenCoeff_nX->setTooltip("Wall absorption coefficient for the wall at which the negative X-axis intersects.");
    s_attenCoeff_pY->setTooltip("Wall absorption coefficient for the wall at which the positive Y-axis intersects.");
    s_attenCoeff_nY->setTooltip("Wall absorption coefficient for the wall at which the negative Y-axis intersects.");
    s_attenCoeff_pZ->setTooltip("Wall absorption coefficient for the wall at which the positive Z-axis intersects.");
    s_attenCoeff_nZ->setTooltip("Wall absorption coefficient for the wall at which the negative Z-axis intersects.");
    TB_enableIMS->setTooltip("Whether to enable reflection orders greater than 0.");
    SL_max_reflection_order->setTooltip("The maximum reflection order for the simulation.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("This is a shoebox room simulator based on the image source method. It supports multiple sources and Ambisonic receivers. Due to the 64 channel limit, the number of receivers is order-dependent; e.g.: up to 16x FOA, 4x 3rd order, or 1x 7th-order receivers."));

    /* Specify screen refresh rate */
    startTimer(80);//80); /*ms (40ms = 25 frames per second) */

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

    /* Background gradients */
    drawVerticalGradient(g, {0, 321, 780, 177}, bgDark2, bgDark1);
    drawVerticalGradient(g, {0,  33, 780, 295}, bgDark1, bgDark2);

    /* Top rounded bar */
    {
        juce::Rectangle<float> r { 1.f, 2.f, 778.f, 31.f };
        g.setGradientFill(juce::ColourGradient(bgDark2,
                                               r.getX(), r.getBottom(),
                                               bgDark1,
                                               r.getRight(), r.getY(),
                                               false));
        g.fillRoundedRectangle(r, 5.f);
        g.setColour(borderGrey);
        g.drawRoundedRectangle(r, 5.f, 2.f);
    }

    /* Panels */
    drawPanel(g, {12,  58, 468,158}, panelFill,      panelStroke);
    drawPanel(g, {12,  58, 232,158}, panelFillLight, panelStroke);
    drawPanel(g, {12, 297, 220,191}, panelFill,      panelStroke);
    drawPanel(g, {12, 241, 468, 31}, panelFill,      panelStroke);
    drawPanel(g, {488, 57, 280,431}, panelFill,      panelStroke);
    drawPanel(g, {12, 297, 220, 31}, panelFillLight, panelStroke);
    drawPanel(g, {252,297, 220,191}, panelFill,      panelStroke);
    drawPanel(g, {252,297, 220, 31}, panelFillLight, panelStroke);

    /* Borders */
    g.setColour(borderGrey);
    g.drawRect({0,   0, 780, 2}, 2);
    g.drawRect({0, 498, 780, 2}, 2);
    g.drawRect({0,   0,   2,500}, 2);
    g.drawRect({778, 0,   2,500}, 2);

    /* Section titles */
    drawLabel(g, {200, 33,  96,30}, "Room Settings", 15.f);
    drawLabel(g, {588, 33, 163,30}, "Room View",     15.f);

    /* Encoding order + format */
    drawLabel(g, {21, 241,153,30}, "SH Encoding Order:", 15.f);
    drawLabel(g, {256,241,145,30}, "Format:",            15.f);
 
    /* Title */
    drawLabel(g, {16, 1, 100,32}, "SPARTA|", 18.8f);
    drawLabel(g, {92,  1, 148,32}, "AmbiRoomSim", 18.f, juce::Justification::centredLeft, juce::Colour(0xffffda2b));

    /* Room dimensions */
    drawLabel(g, {23, 124, 60,30}, "Width",  15.f, juce::Justification::centred);
    drawLabel(g, {95, 124, 60,30}, "Depth",  15.f, juce::Justification::centred);
    drawLabel(g, {167,124, 60,30}, "Height", 15.f, juce::Justification::centred);

    /* Receiver settings */
    drawLabel(g, {192,217,137,30}, "Receiver Settings", 15.f);

    /* Attenuation controls */
    drawLabel(g, {256,57, 60,30}, "Atten. X", 15.f, juce::Justification::centred);
    drawLabel(g, {304,81, 24,30}, "+",        15.f, juce::Justification::centred);
    drawLabel(g, {304,145,24,30}, "-",        15.f, juce::Justification::centred);
    drawLabel(g, {332,57, 60,30}, "Atten. Y", 15.f, juce::Justification::centred);
    drawLabel(g, {380,81, 24,30}, "+",        15.f, juce::Justification::centred);
    drawLabel(g, {380,145,24,30}, "-",        15.f, juce::Justification::centred);
    drawLabel(g, {408,57, 60,30}, "Atten. Z", 15.f, juce::Justification::centred);
    drawLabel(g, {456,81, 24,30}, "+",        15.f, juce::Justification::centred);
    drawLabel(g, {456,145,24,30}, "-",        15.f, juce::Justification::centred);

    /* Source coordinates */
    drawLabel(g, {56, 272,137,30}, "Source Coordinates", 15.f);
    drawLabel(g, {24, 323,200,30}, "#        x            y             z", 15.f);
    drawLabel(g, {21, 297,153,30}, "Number of Sources:", 15.f);

    /* Receiver coordinates */
    drawLabel(g, {288,272,152,30}, "Receiver Coordinates", 15.f);
    drawLabel(g, {264,323,200,30}, "#        x            y             z", 15.f);
    drawLabel(g, {261,297,155,30}, "Number of Receivers:", 15.f);

    /* Image sources toggle */
    drawLabel(g, {20, 63,169,30}, "Enable Image Sources:", 14.5f);
    drawLabel(g, {20, 95,169,30}, "Max Reflection Order:", 14.5f);
    
    g.setColour(Colours::white);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
        220, 16, 530, 11,
        Justification::centredLeft, true);

    /* display warning message */
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.setColour(Colours::red);
            g.drawText(TRANS("Set frame size to multiple of ") + String(ambi_roomsim_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(ambi_roomsim_getNumSources(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of output channels (") + String(processor.getTotalNumOutputChannels()) +
                       TRANS("/") + String(ambi_roomsim_getNSHrequired(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
    }
}

void PluginEditor::resized()
{

}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == SL_num_sources.get())
    {
        refreshPanViewWindow = true;
    }
    else if (sliderThatWasMoved == SL_num_receivers.get())
    {
        refreshPanViewWindow = true;
    }
}

void PluginEditor::comboBoxChanged (juce::ComboBox* /*comboBoxThatHasChanged*/)
{
}

void PluginEditor::buttonClicked (juce::Button* /*buttonThatWasClicked*/)
{
}

void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    sourceCoordsView_handle->setNCH(ambi_roomsim_getNumSources(hAmbi));
    receiverCoordsView_handle->setNCH(ambi_roomsim_getNumReceivers(hAmbi));
    CBoutputFormat->setSelectedId(ambi_roomsim_getChOrder(hAmbi), sendNotification);
    CBnormalisation->setSelectedId(ambi_roomsim_getNormType(hAmbi), sendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);

    /* refresh pan view */
//    if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) ||
//        sourceCoordsView_handle->getHasASliderChanged() || processor.getRefreshWindow()){
//        panWindow->refreshPanView();
//        refreshPanViewWindow = false;
//        sourceCoordsView_handle->setHasASliderChange(false);
//        processor.setRefreshWindow(false);
//    }
    panWindow->refreshPanView();

    /* display warning message, if needed */
    if ((processor.getCurrentBlockSize() % ambi_roomsim_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumInputs() < ambi_roomsim_getNumSources(hAmbi))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumOutputs() < ambi_roomsim_getNSHrequired(hAmbi))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}
