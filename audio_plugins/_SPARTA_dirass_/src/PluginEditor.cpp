/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2019 - Leo McCormack.
 
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
    CBbeamType = std::make_unique<ComboBoxWithAttachment>(p.parameters, "beamType");
    addAndMakeVisible (CBbeamType.get());
    CBbeamType->setEditableText (false);
    CBbeamType->setJustificationType (juce::Justification::centredLeft);
    CBbeamType->setBounds (121, 440, 112, 18);

    CBchFormat = std::make_unique<ComboBoxWithAttachment>(p.parameters, "channelOrder");
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (juce::Justification::centredLeft);
    CBchFormat->setBounds (90, 504, 66, 18);

    CBnormScheme = std::make_unique<ComboBoxWithAttachment>(p.parameters, "normType");
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (juce::Justification::centredLeft);
    CBnormScheme->setBounds (161, 504, 71, 18);

    CB_hfov = std::make_unique<ComboBoxWithAttachment>(p.parameters, "FOVoption");
    addAndMakeVisible (CB_hfov.get());
    CB_hfov->setEditableText (false);
    CB_hfov->setJustificationType (juce::Justification::centredLeft);
    CB_hfov->setBounds (584, 406, 66, 18);

    CB_aspectRatio = std::make_unique<ComboBoxWithAttachment>(p.parameters, "ARoption");
    addAndMakeVisible (CB_aspectRatio.get());
    CB_aspectRatio->setEditableText (false);
    CB_aspectRatio->setJustificationType (juce::Justification::centredLeft);
    CB_aspectRatio->setBounds (584, 438, 66, 18);

    SLmapAvg = std::make_unique<SliderWithAttachment>(p.parameters, "mapAvg");
    addAndMakeVisible (SLmapAvg.get());
    SLmapAvg->setSliderStyle (juce::Slider::LinearHorizontal);
    SLmapAvg->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    SLmapAvg->setBounds (349, 468, 104, 24);

    CBinputOrder = std::make_unique<ComboBoxWithAttachment>(p.parameters, "inputOrder");
    addAndMakeVisible (CBinputOrder.get());
    CBinputOrder->setEditableText (false);
    CBinputOrder->setJustificationType (juce::Justification::centredLeft);
    CBinputOrder->setBounds (121, 403, 112, 18);

    s_minFreq = std::make_unique<SliderWithAttachment>(p.parameters, "minFreq");
    addAndMakeVisible (s_minFreq.get());
    s_minFreq->setSliderStyle (juce::Slider::LinearHorizontal);
    s_minFreq->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    s_minFreq->setBounds (552, 471, 98, 18);

    s_maxFreq = std::make_unique<SliderWithAttachment>(p.parameters, "maxFreq");
    addAndMakeVisible (s_maxFreq.get());
    s_maxFreq->setSliderStyle (juce::Slider::LinearHorizontal);
    s_maxFreq->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    s_maxFreq->setBounds (552, 502, 98, 18);

    CBgridOption = std::make_unique<ComboBoxWithAttachment>(p.parameters, "gridOption");
    addAndMakeVisible (CBgridOption.get());
    CBgridOption->setEditableText (false);
    CBgridOption->setJustificationType (juce::Justification::centredLeft);
    CBgridOption->setBounds (121, 472, 112, 18);

    CBupscaleOrder = std::make_unique<ComboBoxWithAttachment>(p.parameters, "upscaleOrder");
    addAndMakeVisible (CBupscaleOrder.get());
    CBupscaleOrder->setEditableText (false);
    CBupscaleOrder->setJustificationType (juce::Justification::centredLeft);
    CBupscaleOrder->setBounds (354, 440, 99, 18);

    CBdirassMode = std::make_unique<ComboBoxWithAttachment>(p.parameters, "DirASSmode");
    addAndMakeVisible (CBdirassMode.get());
    CBdirassMode->setEditableText (false);
    CBdirassMode->setJustificationType (juce::Justification::centredLeft);
    CBdirassMode->addListener (this);
    CBdirassMode->setBounds (354, 403, 99, 18);

    s_interpWidth = std::make_unique<SliderWithAttachment>(p.parameters, "dispWidth");
    addAndMakeVisible (s_interpWidth.get());
    s_interpWidth->setSliderStyle (juce::Slider::LinearHorizontal);
    s_interpWidth->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    s_interpWidth->setBounds (368, 502, 85, 18);

    CB_webcam.reset (new juce::ComboBox (juce::String()));
    addAndMakeVisible (CB_webcam.get());
    CB_webcam->setEditableText (false);
    CB_webcam->setJustificationType (juce::Justification::centredLeft);
    CB_webcam->setTextWhenNothingSelected (juce::String());
    CB_webcam->setTextWhenNoChoicesAvailable (juce::String());
    CB_webcam->addListener (this);
    CB_webcam->setBounds (434, 38, 92, 17);

    TB_greyScale.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_greyScale.get());
    TB_greyScale->setButtonText (juce::String());
    TB_greyScale->addListener (this);
    TB_greyScale->setBounds (639, 35, 24, 24);

    TB_flipUD.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipUD.get());
    TB_flipUD->setButtonText (juce::String());
    TB_flipUD->addListener (this);
    TB_flipUD->setBounds (598, 35, 24, 24);

    TB_flipLR.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipLR.get());
    TB_flipLR->setButtonText (juce::String());
    TB_flipLR->addListener (this);
    TB_flipLR->setBounds (550, 35, 24, 24);

    setSize (672, 542);

    /* handle for object */
    hDir = processor.getFXHandle();

    /* OpenGL init */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    s_minFreq->setColour(Slider::trackColourId, Colours::transparentBlack);
    s_minFreq->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    s_minFreq->setSliderSnapsToMousePosition(false);
    s_maxFreq->setColour(Slider::trackColourId, Colours::transparentBlack);
    s_maxFreq->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    s_maxFreq->setSliderSnapsToMousePosition(false);
    s_interpWidth->setColour(Slider::trackColourId, Colours::transparentBlack);
    s_interpWidth->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    //s_interpWidth->setSliderSnapsToMousePosition(false);

    /* Overlay */
    previewArea.setBounds(13, 59, 646, 323);
    overlayIncluded.reset (new overlay(p));
    addAndMakeVisible (overlayIncluded.get());
    overlayIncluded->setAlwaysOnTop(true);
    overlayIncluded->setBounds(previewArea);

    /* Camera support */
    updateCameraList();
    CB_webcam->setSelectedId (processor.getCameraID(), dontSendNotification);
    CB_webcam->onChange = [this] { cameraChanged(); };
    addAndMakeVisible (lastSnapshot);
    TB_greyScale->setToggleState(processor.getGreyScale(), dontSendNotification);
    TB_flipLR->setToggleState(processor.getFlipLR(), dontSendNotification);
    TB_flipUD->setToggleState(processor.getFlipUD(), dontSendNotification);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

    /* fetch current configuration */
    CBchFormat->setSelectedId(dirass_getChOrder(hDir), sendNotification);
    CBnormScheme->setSelectedId(dirass_getNormType(hDir), sendNotification);
    resolutionHasChanged = false;
    CBchFormat->setItemEnabled(CH_FUMA, dirass_getInputOrder(hDir)==SH_ORDER_FIRST ? true : false);
    CBnormScheme->setItemEnabled(NORM_FUMA, dirass_getInputOrder(hDir)==SH_ORDER_FIRST ? true : false);
    CBupscaleOrder->setEnabled(dirass_getDiRAssMode(hDir) == REASS_UPSCALE ? true : false);

    /* tooltips */
    CBinputOrder->setTooltip("Analysis order. Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals as input.");
    CBbeamType->setTooltip("Sector beamforming pattern to use.");
    CBgridOption->setTooltip("Analysis/scanning grid options.");
    CBupscaleOrder->setTooltip("Sets the upscaling order. Since the plug-in is not bound by the VST channel limit, we can go pretty crazy here.");
    CBdirassMode->setTooltip("Off: direction-reassignment (DirASS) is disabled, and the plug-in displays a basic steered-response power (SRP) activity-map. \n\nNearest: for each scanning direction, the direction of arrival is estimated within the sector beam-pattern and the energy of the beamformer is quantised to the nearest display pixel. \n\nUpscale: rather than re-assigning the energy to the nearest pixel, the sector-beamformer is encoded into an order higher than that of the input. The upscaled energy is then used for the activity-map.");
    CB_hfov->setTooltip("Horizontal field-of-view (FOV) options.");
    CB_aspectRatio->setTooltip("Aspect ratio options.");
    SLmapAvg->setTooltip("Activity-map averaging coefficient (one-pole filter).");
    CBchFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormScheme->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    CB_webcam->setTooltip("Optionally, the video from a webcam may be streamed behind the activity-map; allowing for a make-shift acoustic camera. This is particularly effective when using, for example, a 360degree Ricoh Theta camera.");
    TB_greyScale->setTooltip("Sets the plug-in to display the webcam image in 'grey-scale'.");
    TB_flipUD->setTooltip("Flips the webcam image up-down, as it may be preferable to mount the camera upside-down on top of the microphone array; in order to bring the origin of the camera closer to that of the array.");
    TB_flipLR->setTooltip("Flips the webcam image left-right, as some webcams mirror the images taken.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A sound-field visualiser, which is based on the directional re-assignment of beamformer energy. This energy re-assignment is based on local DoA estimates for each scanning direction, and may be quantised to the nearest direction or upscaled to a higher-order than the input; resulting in sharper activity-maps. For example, a second-order input may be displayed with (up to) 20th order output resolution. The plug-in also allows the user to place real-time video footage behind the activity-map, in order to create a make-shift acoustic camera.\n"));
    addAndMakeVisible (publicationLink);
    publicationLink.setColour (HyperlinkButton::textColourId, Colours::lightblue);
    publicationLink.setBounds(getBounds().getWidth()-80, 4, 80, 12);
    publicationLink.setJustificationType(Justification::centredLeft);

	/* Specify screen refresh rate */
    startTimer(140);//80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    CBbeamType = nullptr;
    CBchFormat = nullptr;
    CBnormScheme = nullptr;
    CB_hfov = nullptr;
    CB_aspectRatio = nullptr;
    SLmapAvg = nullptr;
    CBinputOrder = nullptr;
    s_minFreq = nullptr;
    s_maxFreq = nullptr;
    CBgridOption = nullptr;
    CBupscaleOrder = nullptr;
    CBdirassMode = nullptr;
    s_interpWidth = nullptr;
    CB_webcam = nullptr;
    TB_greyScale = nullptr;
    TB_flipUD = nullptr;
    TB_flipLR = nullptr;

    setLookAndFeel(nullptr);
    overlayIncluded = nullptr;
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 286, width = 672, height = 256;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041519);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             544.0f - 286.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             448.0f - 286.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 30, width = 672, height = 256;
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
        float x = 1.0f, y = 2.0f, width = 670.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             656.0f - 1.0f + x,
                                             24.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 13, y = 394, width = 450, height = 138;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 242, y = 394, width = 221, height = 36;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x35a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 13, y = 394, width = 230, height = 36;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x35a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 12, y = 58, width = 648, height = 325;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 22, y = 397, width = 132, height = 30;
        juce::String text (TRANS("Input Order:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 497, width = 132, height = 30;
        juce::String text (TRANS("Format:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 250, y = 465, width = 132, height = 30;
        juce::String text (TRANS("Average Coeff:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 433, width = 132, height = 30;
        juce::String text (TRANS("Beam Type:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 465, width = 132, height = 30;
        juce::String text (TRANS("Scanning Grid:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 472, y = 394, width = 186, height = 138;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 481, y = 399, width = 132, height = 30;
        juce::String text (TRANS("Horiz. FOV:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 481, y = 432, width = 132, height = 30;
        juce::String text (TRANS("Aspect Ratio:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 1, width = 100, height = 32;
        juce::String text (TRANS("SPARTA|"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.80f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 92, y = 1, width = 112, height = 32;
        juce::String text (TRANS("DirASS"));
        juce::Colour fillColour = juce::Colour (0xffb0a6e7);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 481, y = 465, width = 152, height = 30;
        juce::String text (TRANS("Min Freq:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 481, y = 497, width = 104, height = 30;
        juce::String text (TRANS("Max Freq:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 250, y = 433, width = 132, height = 30;
        juce::String text (TRANS("Upscale Order:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 250, y = 397, width = 181, height = 30;
        juce::String text (TRANS("DirASS Mode:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 250, y = 497, width = 132, height = 30;
        juce::String text (TRANS("Width (pixels):"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 624, y = 32, width = 29, height = 30;
        juce::String text (TRANS("GS:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 576, y = 32, width = 37, height = 30;
        juce::String text (TRANS("U|D:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 530, y = 32, width = 37, height = 30;
        juce::String text (TRANS("L|R:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 283, y = 33, width = 125, height = 30;
        juce::String text (TRANS("Display Window"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 674, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 540, width = 674, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 540;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 670, y = 0, width = 2, height = 540;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

	g.setColour(Colours::white);
	g.setFont(juce::FontOptions (11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		170, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(dirass_getSamplingRate(hDir)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(dirass_getNSHrequired(hDir)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
    }
}

void PluginEditor::resized()
{
    if (overlayIncluded != nullptr){
        if (cameraPreviewComp.get() != nullptr) {
            cameraPreviewComp->setBounds(overlayIncluded->getBounds());
            cameraPreviewComp->setVisible(false);
        }
        lastSnapshot.setBounds(overlayIncluded->getBounds());
        overlayIncluded->setAlwaysOnTop(true);
        overlayIncluded->setBounds(previewArea);
        overlayIncluded->resized();
    }
    repaint();
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == CBdirassMode.get())
    {
        CBupscaleOrder->setEnabled(CBdirassMode->getSelectedId() == REASS_UPSCALE ? true : false);
    }
    else if (comboBoxThatHasChanged == CB_webcam.get())
    {
        processor.setCameraID(CB_webcam->getSelectedId());
        cameraChanged();
        if(CB_webcam->getSelectedId()==1){
            incomingImage.clear(previewArea);
            lastSnapshot.setImage(incomingImage);
        }
    }
}

void PluginEditor::sliderValueChanged (juce::Slider* /*sliderThatWasMoved*/)
{
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == TB_greyScale.get())
    {
        processor.setGreyScale(TB_greyScale->getToggleState());
    }
    else if (buttonThatWasClicked == TB_flipUD.get())
    {
        processor.setFlipUD(TB_flipUD->getToggleState());
    }
    else if (buttonThatWasClicked == TB_flipLR.get())
    {
        processor.setFlipLR(TB_flipLR->getToggleState());
    }
}

void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    CBchFormat->setSelectedId(dirass_getChOrder(hDir), sendNotification);
    CBnormScheme->setSelectedId(dirass_getNormType(hDir), sendNotification);
    CBchFormat->setItemEnabled(CH_FUMA, dirass_getInputOrder(hDir)==SH_ORDER_FIRST ? true : false);
    CBnormScheme->setItemEnabled(NORM_FUMA, dirass_getInputOrder(hDir)==SH_ORDER_FIRST ? true : false);
    CBgridOption->setEnabled(processor.getIsPlaying() ? false : true);
    s_interpWidth->setEnabled(processor.getIsPlaying() ? false : true);

    /* take webcam picture */
    if(CB_webcam->getSelectedId()>1){
        handleAsyncUpdate();
        lastSnapshot.setTransform(AffineTransform()); /*identity*/
        AffineTransform m_LR, m_UD, m_LR_UD;
        m_LR = AffineTransform(-1, 0, previewArea.getWidth(), 0, 1, 0).followedBy(AffineTransform::translation(2 * previewArea.getX(),0));    /* flip left/right */
        m_UD = AffineTransform(1, 0, 0, 0, -1, previewArea.getHeight()).followedBy(AffineTransform::translation(0, 2 * previewArea.getY()));  /* flip up/down */
        m_LR_UD = m_LR.followedBy(m_UD);  /* flip left/right and up/down */

        if (TB_flipLR->getToggleState() && TB_flipUD->getToggleState())
            lastSnapshot.setTransform(m_LR_UD);
        else if (TB_flipLR->getToggleState())
            lastSnapshot.setTransform(m_LR);
        else if (TB_flipUD->getToggleState())
            lastSnapshot.setTransform(m_UD);

        if (incomingImage.isValid())
            lastSnapshot.setImage(incomingImage);
    }

    /* Progress bar */
    if(dirass_getCodecStatus(hDir)==CODEC_STATUS_INITIALISING){
        addAndMakeVisible(progressbar);
        progressbar.setAlwaysOnTop(true);
        progress = (double)dirass_getProgressBar0_1(hDir);
        char text[PROGRESSBARTEXT_CHAR_LENGTH];
        dirass_getProgressBarText(hDir, (char*)text);
        progressbar.setTextToDisplay(String(text));
    }
    else
        removeChildComponent(&progressbar);

    /* Some parameters shouldn't be editable during initialisation*/
    bool usingUpscale = (CBdirassMode->getSelectedId() == REASS_UPSCALE ? true : false);
    if(dirass_getCodecStatus(hDir)==CODEC_STATUS_INITIALISING){
        if(CBbeamType->isEnabled())
            CBbeamType->setEnabled(false);
        if(CBbeamType->isEnabled())
            CBbeamType->setEnabled(false);
        if(CB_hfov->isEnabled())
            CB_hfov->setEnabled(false);
        if(CB_aspectRatio->isEnabled())
            CB_aspectRatio->setEnabled(false);
        if(CBinputOrder->isEnabled())
            CBinputOrder->setEnabled(false);
        if(CBgridOption->isEnabled())
            CBgridOption->setEnabled(false);
        if(CBupscaleOrder->isEnabled())
            CBupscaleOrder->setEnabled(false);
        if(s_interpWidth->isEnabled())
            s_interpWidth->setEnabled(false);
    }
    else{
        if(!CBbeamType->isEnabled())
            CBbeamType->setEnabled(true);
        if(!CBbeamType->isEnabled())
            CBbeamType->setEnabled(true);
        if(!CB_hfov->isEnabled())
            CB_hfov->setEnabled(true);
        if(!CB_aspectRatio->isEnabled())
            CB_aspectRatio->setEnabled(true);
        if(!CBinputOrder->isEnabled())
            CBinputOrder->setEnabled(true);
        if(!CBgridOption->isEnabled())
            CBgridOption->setEnabled(true);
        if(!CBupscaleOrder->isEnabled() && usingUpscale)
            CBupscaleOrder->setEnabled(true);
        if(!s_interpWidth->isEnabled())
            s_interpWidth->setEnabled(true);
    }

    /* refresh the powermap display */
    if ((overlayIncluded != nullptr) && (processor.getIsPlaying())) {
        float* dirs_deg, *pmap;
        int nDirs, pmapReady, pmapWidth, hfov;
        float aspectRatio;
        pmapReady = dirass_getPmap(hDir, &dirs_deg, &pmap, &nDirs, &pmapWidth, &hfov, &aspectRatio);
        overlayIncluded->setEnableTransparency(CB_webcam->getSelectedId() > 1 ? true : false);
        if(pmapReady){
            overlayIncluded->refreshPowerMap(dirs_deg, pmap, nDirs, pmapWidth, hfov, aspectRatio);
        }
        if(overlayIncluded->getFinishedRefresh()){
            dirass_requestPmapUpdate(hDir);
        }
    }

    /* display warning message, if needed */
    if ( !((dirass_getSamplingRate(hDir) == 44.1e3) || (dirass_getSamplingRate(hDir) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if ((processor.getCurrentNumInputs() < dirass_getNSHrequired(hDir))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}

void PluginEditor::cameraChanged()
{
    cameraDevice.reset();
    cameraPreviewComp.reset();

    if (CB_webcam->getSelectedId() > 1)
        cameraDeviceOpenResult (CameraDevice::openDevice (CB_webcam->getSelectedId() - 2), {});
    else
        resized();
}

void PluginEditor::cameraDeviceOpenResult (CameraDevice* device, const String& /*error*/)
{
    cameraDevice.reset (device);

    if (cameraDevice.get() != nullptr) {
        cameraPreviewComp.reset (cameraDevice->createViewerComponent());
        addAndMakeVisible (cameraPreviewComp.get());
        cameraPreviewComp->setAlwaysOnTop(false);
    }
    resized();
}

void PluginEditor::updateCameraList()
{
    CB_webcam->clear();
    CB_webcam->addItem("No camera", 1);
    CB_webcam->addSeparator();

    auto cameras = CameraDevice::getAvailableDevices();

    for (int i = 0; i < cameras.size(); ++i)
        CB_webcam->addItem(cameras[i], i + 2);
    CB_webcam->setSelectedId(1);
}

void PluginEditor::imageReceived(const Image& image)
{
    if (! image.isValid())
        return;
    Image newImage = image;

    if(TB_greyScale->getToggleState())
        newImage.desaturate();

    incomingImage = newImage;
}

void PluginEditor::handleAsyncUpdate()
{
    if (cameraDevice != nullptr){
        SafePointer<PluginEditor> safeThis (this);
        cameraDevice->takeStillPicture ([safeThis] (const Image& image) mutable { safeThis->imageReceived (image); });
    }
}
