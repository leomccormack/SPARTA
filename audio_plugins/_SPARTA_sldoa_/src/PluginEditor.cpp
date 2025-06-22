/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2017/2018 - Leo McCormack.
 
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
    avgSlider.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (avgSlider.get());
    avgSlider->setRange (0, 2000, 0.1);
    avgSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    avgSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    avgSlider->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    avgSlider->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6e));
    avgSlider->addListener (this);

    avgSlider->setBounds (80, 473, 118, 24);

    CB_CHorder.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CB_CHorder.get());
    CB_CHorder->setEditableText (false);
    CB_CHorder->setJustificationType (juce::Justification::centredLeft);
    CB_CHorder->setTextWhenNothingSelected (TRANS ("ACN"));
    CB_CHorder->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CB_CHorder->addListener (this);

    CB_CHorder->setBounds (66, 447, 64, 18);

    CB_Norm.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CB_Norm.get());
    CB_Norm->setEditableText (false);
    CB_Norm->setJustificationType (juce::Justification::centredLeft);
    CB_Norm->setTextWhenNothingSelected (TRANS ("N3D"));
    CB_Norm->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CB_Norm->addListener (this);

    CB_Norm->setBounds (131, 447, 68, 18);

    slider_anaOrder.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (slider_anaOrder.get());
    slider_anaOrder->setRange (0, 1, 1);
    slider_anaOrder->setSliderStyle (juce::Slider::LinearVertical);
    slider_anaOrder->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    slider_anaOrder->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    slider_anaOrder->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    slider_anaOrder->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    slider_anaOrder->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    slider_anaOrder->addListener (this);

    slider_anaOrder->setBounds (576, 424, 40, 66);

    CBinputTypePreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBinputTypePreset.get());
    CBinputTypePreset->setEditableText (false);
    CBinputTypePreset->setJustificationType (juce::Justification::centredLeft);
    CBinputTypePreset->setTextWhenNothingSelected (TRANS ("Default"));
    CBinputTypePreset->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBinputTypePreset->addItem (TRANS ("Ideal SH"), 1);
    CBinputTypePreset->addListener (this);

    CBinputTypePreset->setBounds (96, 417, 103, 18);

    s_minFreq.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_minFreq.get());
    s_minFreq->setRange (0, 24000, 1);
    s_minFreq->setSliderStyle (juce::Slider::LinearHorizontal);
    s_minFreq->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    s_minFreq->addListener (this);

    s_minFreq->setBounds (352, 382, 56, 20);

    s_maxFreq.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_maxFreq.get());
    s_maxFreq->setRange (0, 24000, 1);
    s_maxFreq->setSliderStyle (juce::Slider::LinearHorizontal);
    s_maxFreq->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    s_maxFreq->addListener (this);

    s_maxFreq->setBounds (560, 382, 56, 20);

    CBmasterOrder.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBmasterOrder.get());
    CBmasterOrder->setEditableText (false);
    CBmasterOrder->setJustificationType (juce::Justification::centredLeft);
    CBmasterOrder->setTextWhenNothingSelected (TRANS ("Default"));
    CBmasterOrder->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBmasterOrder->addListener (this);

    CBmasterOrder->setBounds (96, 382, 103, 18);

    CB_webcam.reset (new juce::ComboBox (juce::String()));
    addAndMakeVisible (CB_webcam.get());
    CB_webcam->setEditableText (false);
    CB_webcam->setJustificationType (juce::Justification::centredLeft);
    CB_webcam->setTextWhenNothingSelected (juce::String());
    CB_webcam->setTextWhenNoChoicesAvailable (juce::String());
    CB_webcam->addListener (this);

    CB_webcam->setBounds (395, 38, 92, 17);

    TB_greyScale.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_greyScale.get());
    TB_greyScale->setButtonText (juce::String());
    TB_greyScale->addListener (this);

    TB_greyScale->setBounds (600, 35, 24, 24);

    TB_flipUD.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipUD.get());
    TB_flipUD->setButtonText (juce::String());
    TB_flipUD->addListener (this);

    TB_flipUD->setBounds (559, 35, 24, 24);

    TB_flipLR.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipLR.get());
    TB_flipLR->setButtonText (juce::String());
    TB_flipLR->addListener (this);

    TB_flipLR->setBounds (511, 35, 24, 24);

    setSize (634, 514);

    /* handles */
    hSld = processor.getFXHandle();

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    s_minFreq->setColour(Slider::trackColourId, Colours::transparentBlack);
    s_minFreq->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    s_minFreq->setSliderSnapsToMousePosition(false);
    s_maxFreq->setColour(Slider::trackColourId, Colours::transparentBlack);
    s_maxFreq->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    s_maxFreq->setSliderSnapsToMousePosition(false);

    /* overlay */
    previewArea.setBounds(13, 59, 608, 303);
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

    /* create 2d Slider for the decoding order parameter */
    int nPoints;
    float* pX_vector;
    int* pY_values_int;
    anaOrder2dSlider.reset (new log2dSlider(360, 54, 100, 20e3, 1, sldoa_getMasterOrder(hSld), 0));
    addAndMakeVisible (anaOrder2dSlider.get());
    anaOrder2dSlider->setAlwaysOnTop(true);
    anaOrder2dSlider->setTopLeftPosition(218, 432);
    sldoa_getAnaOrderHandle(hSld, &pX_vector, &pY_values_int, &nPoints);
    anaOrder2dSlider->setDataHandlesInt(pX_vector, pY_values_int, nPoints);

    /* add master analysis order options */
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

    /* add ambisonic convention options */
    CB_CHorder->addItem(TRANS("ACN"), CH_ACN);
    CB_CHorder->addItem(TRANS("FuMa"), CH_FUMA);
    CB_Norm->addItem(TRANS("N3D"), NORM_N3D);
    CB_Norm->addItem(TRANS("SN3D"), NORM_SN3D);
    CB_Norm->addItem(TRANS("FuMa"), NORM_FUMA);

    /* add microphone preset options */
    CBinputTypePreset->addItem(TRANS("Zylia"), MIC_PRESET_ZYLIA);
    CBinputTypePreset->addItem(TRANS("Eigenmike"), MIC_PRESET_EIGENMIKE32);
    CBinputTypePreset->addItem(TRANS("DTU mic"), MIC_PRESET_DTU_MIC);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

	/* fetch current configuration */
    CBmasterOrder->setSelectedId(sldoa_getMasterOrder(hSld), dontSendNotification);
    avgSlider->setValue((float)sldoa_getAvg(hSld), dontSendNotification);
    CB_CHorder->setSelectedId(sldoa_getChOrder(hSld), dontSendNotification);
    CB_Norm->setSelectedId(sldoa_getNormType(hSld), dontSendNotification);
    slider_anaOrder->setRange(1, sldoa_getMasterOrder(hSld), 1);
    slider_anaOrder->setValue(sldoa_getAnaOrderAllBands(hSld), dontSendNotification);
    s_minFreq->setRange(0.0f, sldoa_getSamplingRate(hSld)/2.0f, 1.0f);
    s_maxFreq->setRange(0.0f, sldoa_getSamplingRate(hSld)/2.0f, 1.0f);
    s_minFreq->setSkewFactor(0.5f);
    s_maxFreq->setSkewFactor(0.5f);
    s_minFreq->setValue(sldoa_getMinFreq(hSld));
    s_maxFreq->setValue(sldoa_getMaxFreq(hSld));
    CB_CHorder->setItemEnabled(CH_FUMA, sldoa_getMasterOrder(hSld)==SH_ORDER_FIRST ? true : false);
    CB_Norm->setItemEnabled(NORM_FUMA, sldoa_getMasterOrder(hSld)==SH_ORDER_FIRST ? true : false);

    /* tooltips */
    CBmasterOrder->setTooltip("Maximum analysis order (can be lower at different frequencies). Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals as input");
    avgSlider->setTooltip("Temporal averaging (in miliseconds)");
    slider_anaOrder->setTooltip("This sets the analysis order for all frequencies. Use the 2-D slider to change the analysis order for specific frequencies.");
    CBinputTypePreset->setTooltip("Presets for for various higher-order microphone arrays, which configure the frequency-dependent analysis order.");
    CB_CHorder->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CB_Norm->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
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
    pluginDescription->setTooltip(TRANS("A spatially localised direction-of-arrival (DoA) estimator. The plug-in first uses VBAP beam patterns (for directions that are uniformly distributed on the surface of a shere) to obtain spatially-biased zeroth and first-order signals, which are subsequently used for the active-intensity vector estimation. This allows for a DoA estimate to be made for each of these spatially-constrained sectors, and for each sub-band. The low frequency DoA estimates are then depicted with blue icons, mid-frequencies with green, and high-frequencies with red. The size of the icon and its opacity correspond to the energy of the sector, which are normalised and scaled in ascending order for each frequency band. The plug-in employs two times as many sectors as the analysis order, with the exception of the first-order analysis, which uses the traditional active-intensity approach. The analysis order per frequency band is user definable, as is the frequency range at which to analyse.\n\nThis approach to sound-field visualisation/DoA estimation represents a much more computationally efficient option, when compared to the algorithms that are integrated into the sparta_powermap plug-in, for instance. The plug-in also allows the user to place real-time video footage behind the activity-map, in order to create a make-shift acoustic camera."));
    addAndMakeVisible (publicationLink);
    publicationLink.setColour (HyperlinkButton::textColourId, Colours::lightblue);
    publicationLink.setBounds(getBounds().getWidth()-80, 4, 80, 12);
    publicationLink.setJustificationType(Justification::centredLeft);

	/* Specify screen refresh rate */
   startTimer(TIMER_GUI_RELATED, 120);//80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    avgSlider = nullptr;
    CB_CHorder = nullptr;
    CB_Norm = nullptr;
    slider_anaOrder = nullptr;
    CBinputTypePreset = nullptr;
    s_minFreq = nullptr;
    s_maxFreq = nullptr;
    CBmasterOrder = nullptr;
    CB_webcam = nullptr;
    TB_greyScale = nullptr;
    TB_flipUD = nullptr;
    TB_flipLR = nullptr;

    overlayIncluded = nullptr;
    anaOrder2dSlider = nullptr;
    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 272, width = 634, height = 242;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             520.0f - 272.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             416.0f - 272.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 30, width = 634, height = 242;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             136.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 632.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             632.0f - 1.0f + x,
                                             24.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 8, y = 374, width = 197, height = 128;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 204, y = 374, width = 422, height = 34;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 204, y = 407, width = 422, height = 95;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 14, y = 410, width = 96, height = 30;
        juce::String text (TRANS ("Mic Preset:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 14, y = 468, width = 112, height = 30;
        juce::String text (TRANS ("Avg (ms):"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 14, y = 440, width = 127, height = 30;
        juce::String text (TRANS ("Format:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 216, y = 405, width = 312, height = 30;
        juce::String text (TRANS ("Analysis Order Per Frequency Band"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 611, y = 466, width = 13, height = 30;
        juce::String text (TRANS ("1"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 211, y = 478, width = 37, height = 30;
        juce::String text (TRANS ("100"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 366, y = 478, width = 37, height = 30;
        juce::String text (TRANS ("1k"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 520, y = 478, width = 37, height = 30;
        juce::String text (TRANS ("10k"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 402, y = 478, width = 93, height = 30;
        juce::String text (TRANS ("Frequency (Hz)"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 563, y = 478, width = 37, height = 30;
        juce::String text (TRANS ("20k"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 216, y = 376, width = 160, height = 30;
        juce::String text (TRANS ("Minimum Freq (Hz):"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 422, y = 376, width = 162, height = 30;
        juce::String text (TRANS ("Maximum Freq (Hz):"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 14, y = 376, width = 104, height = 30;
        juce::String text (TRANS ("Max Order:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (14.00f, juce::Font::plain).withStyle ("Bold"));
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
        juce::String text (TRANS ("SLDoA"));
        juce::Colour fillColour = juce::Colour (0xffff4848);
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 584, y = 32, width = 29, height = 30;
        juce::String text (TRANS ("GS:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 536, y = 32, width = 37, height = 30;
        juce::String text (TRANS ("U|D:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 490, y = 32, width = 37, height = 30;
        juce::String text (TRANS ("L|R:"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 267, y = 33, width = 125, height = 30;
        juce::String text (TRANS ("Display Window"));
        juce::Colour fillColour = juce::Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 636, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 514;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 632, y = 0, width = 2, height = 514;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 512, width = 636, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 8, y = 374, width = 197, height = 34;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 13, y = 59, width = 608, height = 303;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }
    
	g.setColour(Colours::white);
	g.setFont(juce::FontOptions (11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		166, 16, 530, 11,
		Justification::centredLeft, true);

    Colour strokeColour = Colour (0x86a3a4a5);
    g.setColour (strokeColour);
    g.setOpacity(0.8f);
    g.drawRect (previewArea);


    /* label for max ORDER */
    {
        int x = 608, y = 412, width = 20, height = 30;
        String text = String(sldoa_getMasterOrder(hSld));
        Colour fillColour = Colours::white;
        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(sldoa_getSamplingRate(hSld)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(sldoa_getNSHrequired(hSld)) + TRANS(")"),
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

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == avgSlider.get())
    {
        sldoa_setAvg(hSld, (float)avgSlider->getValue());
    }
    else if (sliderThatWasMoved == slider_anaOrder.get())
    {
        sldoa_setAnaOrderAllBands(hSld, (int)(slider_anaOrder->getValue()+0.5));
        anaOrder2dSlider->setRefreshValuesFLAG(true);
    }
    else if (sliderThatWasMoved == s_minFreq.get())
    {
        sldoa_setMinFreq(hSld, (float)s_minFreq->getValue());
    }
    else if (sliderThatWasMoved == s_maxFreq.get())
    {
        sldoa_setMaxFreq(hSld, (float)s_maxFreq->getValue());
    }
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == CB_CHorder.get())
    {
        sldoa_setChOrder(hSld, CB_CHorder->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CB_Norm.get())
    {
        sldoa_setNormType(hSld, CB_Norm->getSelectedId());
    }
    else if (comboBoxThatHasChanged == CBinputTypePreset.get())
    {
        sldoa_setSourcePreset(hSld, CBinputTypePreset->getSelectedId());
        anaOrder2dSlider->setRefreshValuesFLAG(true);
    }
    else if (comboBoxThatHasChanged == CBmasterOrder.get())
    {
        sldoa_setMasterOrder(hSld, CBmasterOrder->getSelectedId());
        CBinputTypePreset->setSelectedId(1);
        anaOrder2dSlider->setYrange(1, CBmasterOrder->getSelectedId());
        sldoa_setAnaOrderAllBands(hSld, CBmasterOrder->getSelectedId());
        anaOrder2dSlider->setRefreshValuesFLAG(true);
        slider_anaOrder->setRange(1, CBmasterOrder->getSelectedId(), 1);
        slider_anaOrder->setValue(CBmasterOrder->getSelectedId());
        repaint();
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

void PluginEditor::timerCallback(int timerID)
{
    switch(timerID){
        case TIMER_PROCESSING_RELATED:
            /* handled in PluginProcessor */
            break;

        case TIMER_GUI_RELATED:
            /* parameters whos values can change internally should be periodically refreshed */
            CB_CHorder->setSelectedId(sldoa_getChOrder(hSld), dontSendNotification);
            CB_Norm->setSelectedId(sldoa_getNormType(hSld), dontSendNotification);
            CB_CHorder->setItemEnabled(CH_FUMA, sldoa_getMasterOrder(hSld)==SH_ORDER_FIRST ? true : false);
            CB_Norm->setItemEnabled(NORM_FUMA, sldoa_getMasterOrder(hSld)==SH_ORDER_FIRST ? true : false);

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
            if(sldoa_getCodecStatus(hSld)==CODEC_STATUS_INITIALISING){
                addAndMakeVisible(progressbar);
                progressbar.setAlwaysOnTop(true);
                progress = (double)sldoa_getProgressBar0_1(hSld);
                char text[PROGRESSBARTEXT_CHAR_LENGTH];
                sldoa_getProgressBarText(hSld, (char*)text);
                progressbar.setTextToDisplay(String(text));
            }
            else
                removeChildComponent(&progressbar);

            /* Some parameters shouldn't be editable during initialisation*/
            if(sldoa_getCodecStatus(hSld)==CODEC_STATUS_INITIALISING){
                if(CBmasterOrder->isEnabled())
                    CBmasterOrder->setEnabled(false);
            }
            else{
                if(!CBmasterOrder->isEnabled())
                    CBmasterOrder->setEnabled(true);
            }

            /* refresh overlay */
            if ((overlayIncluded != nullptr) && (processor.getIsPlaying()))
                overlayIncluded->repaint();
            if (anaOrder2dSlider->getRefreshValuesFLAG())
                anaOrder2dSlider->repaint();

            s_minFreq->setValue(sldoa_getMinFreq(hSld));
            s_maxFreq->setValue(sldoa_getMaxFreq(hSld));

            /* display warning message, if needed */
            if ( !((sldoa_getSamplingRate(hSld) == 44.1e3) || (sldoa_getSamplingRate(hSld) == 48e3)) ){
                currentWarning = k_warning_supported_fs;
                repaint(0,0,getWidth(),32);
            }
            else if ((processor.getCurrentNumInputs() < sldoa_getNSHrequired(hSld))){
                currentWarning = k_warning_NinputCH;
                repaint(0,0,getWidth(),32);
            }
            else if(currentWarning){
                currentWarning = k_warning_none;
                repaint(0,0,getWidth(),32);
            }
            break;
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
