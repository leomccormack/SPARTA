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
    CBpmap_method = std::make_unique<ComboBoxWithAttachment>(p.parameters, "powermapMode");
    addAndMakeVisible (CBpmap_method.get());
    CBpmap_method->setEditableText (false);
    CBpmap_method->setJustificationType (juce::Justification::centredLeft);
    CBpmap_method->addListener (this);
    CBpmap_method->setBounds (106, 512, 112, 20);

    CBsourcePreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBsourcePreset.get());
    CBsourcePreset->setEditableText (false);
    CBsourcePreset->setJustificationType (juce::Justification::centredLeft);
    CBsourcePreset->setTextWhenNothingSelected (TRANS("Ideal SH"));
    CBsourcePreset->addListener (this);
    CBsourcePreset->setBounds (106, 439, 112, 20);

    CBchFormat = std::make_unique<ComboBoxWithAttachment>(p.parameters, "channelOrder");
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (juce::Justification::centredLeft);
    CBchFormat->setBounds (80, 472, 66, 20);

    CBnormScheme = std::make_unique<ComboBoxWithAttachment>(p.parameters, "normType");
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (juce::Justification::centredLeft);
    CBnormScheme->setBounds (151, 472, 67, 20);

    s_anaOrder.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_anaOrder.get());
    s_anaOrder->setRange (0, 1, 1);
    s_anaOrder->setSliderStyle (juce::Slider::LinearVertical);
    s_anaOrder->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    s_anaOrder->addListener (this);
    s_anaOrder->setBounds (608, 552, 40, 80);

    s_pmapEQ.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_pmapEQ.get());
    s_pmapEQ->setRange (0, 2, 0.01);
    s_pmapEQ->setSliderStyle (juce::Slider::LinearVertical);
    s_pmapEQ->setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    s_pmapEQ->addListener (this);
    s_pmapEQ->setBounds (608, 448, 40, 80);

    s_covAvg = std::make_unique<SliderWithAttachment>(p.parameters, "covAvgCoeff");
    addAndMakeVisible (s_covAvg.get());
    s_covAvg->setSliderStyle (juce::Slider::LinearHorizontal);
    s_covAvg->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    s_covAvg->setBounds (106, 608, 112, 24);

    s_Nsources = std::make_unique<SliderWithAttachment>(p.parameters, "numSources");
    addAndMakeVisible (s_Nsources.get());
    s_Nsources->setSliderStyle (juce::Slider::LinearHorizontal);
    s_Nsources->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    s_Nsources->setBounds (168, 546, 50, 20);

    CB_hfov = std::make_unique<ComboBoxWithAttachment>(p.parameters, "FOVoption");
    addAndMakeVisible (CB_hfov.get());
    CB_hfov->setEditableText (false);
    CB_hfov->setJustificationType (juce::Justification::centredLeft);
    CB_hfov->setBounds (357, 406, 96, 20);

    CB_aspectRatio = std::make_unique<ComboBoxWithAttachment>(p.parameters, "ARoption");
    addAndMakeVisible (CB_aspectRatio.get());
    CB_aspectRatio->setEditableText (false);
    CB_aspectRatio->setJustificationType (juce::Justification::centredLeft);
    CB_aspectRatio->setBounds (557, 406, 96, 20);

    s_pmapAvg = std::make_unique<SliderWithAttachment>(p.parameters, "mapAvg");
    addAndMakeVisible (s_pmapAvg.get());
    s_pmapAvg->setSliderStyle (juce::Slider::LinearHorizontal);
    s_pmapAvg->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    s_pmapAvg->setBounds (106, 576, 112, 24);

    CBmasterOrder = std::make_unique<ComboBoxWithAttachment>(p.parameters, "inputOrder");
    addAndMakeVisible (CBmasterOrder.get());
    CBmasterOrder->setEditableText (false);
    CBmasterOrder->setJustificationType (juce::Justification::centredLeft);
    CBmasterOrder->addListener (this);
    CBmasterOrder->setBounds (106, 407, 112, 20);

    CB_webcam.reset (new juce::ComboBox (juce::String()));
    addAndMakeVisible (CB_webcam.get());
    CB_webcam->setEditableText (false);
    CB_webcam->setJustificationType (juce::Justification::centredLeft);
    CB_webcam->setTextWhenNothingSelected (juce::String());
    CB_webcam->setTextWhenNoChoicesAvailable (juce::String());
    CB_webcam->addListener (this);
    CB_webcam->setBounds (433, 39, 92, 17);

    TB_greyScale.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_greyScale.get());
    TB_greyScale->addListener (this);
    TB_greyScale->setBounds (639, 36, 24, 24);

    TB_flipUD.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipUD.get());
    TB_flipUD->addListener (this);
    TB_flipUD->setBounds (598, 36, 24, 24);

    TB_flipLR.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TB_flipLR.get());
    TB_flipLR->addListener (this);
    TB_flipLR->setBounds (550, 36, 24, 24);

    setSize (672, 652);

    /* handle for object */
    hPm = processor.getFXHandle();

    /* OpenGL init */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    s_Nsources->setColour(Slider::trackColourId, Colours::transparentBlack);
    s_Nsources->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    s_Nsources->setSliderSnapsToMousePosition(false);

    /* create 2d Sliders */
    int nPoints;
    float* pX_vector, *pY_values;
    int* pY_values_int;
    anaOrder2dSlider.reset (new log2dSlider(360, 63, 100, 20e3, 1, powermap_getMasterOrder(hPm), 0));
    addAndMakeVisible (anaOrder2dSlider.get());
    anaOrder2dSlider->setAlwaysOnTop(true);
    anaOrder2dSlider->setTopLeftPosition(248, 558);
    powermap_getAnaOrderHandle(hPm, &pX_vector, &pY_values_int, &nPoints);
    anaOrder2dSlider->setDataHandlesInt(pX_vector, (std::atomic<int>*)pY_values_int, nPoints);

    pmapEQ2dSlider.reset (new log2dSlider(360, 63, 100, 20e3, 0.0, 2.0, 3));
    addAndMakeVisible (pmapEQ2dSlider.get());
    pmapEQ2dSlider->setAlwaysOnTop(true);
    pmapEQ2dSlider->setTopLeftPosition(248, 454);
    powermap_getPowermapEQHandle(hPm, &pX_vector, &pY_values, &nPoints);
    pmapEQ2dSlider->setDataHandles(pX_vector, (std::atomic<float>*)pY_values, nPoints);

    /* Add microphone preset options */
    CBsourcePreset->addItem(TRANS("Ideal SH"), MIC_PRESET_IDEAL);
    CBsourcePreset->addItem(TRANS("Zylia"), MIC_PRESET_ZYLIA);
    CBsourcePreset->addItem(TRANS("Eigenmike"), MIC_PRESET_EIGENMIKE32);
    CBsourcePreset->addItem(TRANS("DTU mic"), MIC_PRESET_DTU_MIC);
    
    CB_hfov->setItemEnabled(HFOV_180, false);
    CB_hfov->setItemEnabled(HFOV_90, false);
    CB_hfov->setItemEnabled(HFOV_60, false);
    CB_aspectRatio->setItemEnabled(ASPECT_RATIO_4_3, false);
    CB_aspectRatio->setItemEnabled(ASPECT_RATIO_16_9, false);

    /* Overlay */
    previewArea.setBounds(13, 60, 646, 323);
    lastSnapshot.setBounds(previewArea);
    overlayIncluded.reset (new overlay(p));
    addAndMakeVisible (overlayIncluded.get());
    overlayIncluded->setAlwaysOnTop(true);
    overlayIncluded->setBounds(previewArea);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

    /* Camera support */
    updateCameraList();
    CB_webcam->setSelectedId (processor.getCameraID(), dontSendNotification);
    CB_webcam->onChange = [this] { cameraChanged(); };
    addAndMakeVisible (lastSnapshot);
    TB_greyScale->setToggleState(processor.getGreyScale(), dontSendNotification);
    TB_flipLR->setToggleState(processor.getFlipLR(), dontSendNotification);
    TB_flipUD->setToggleState(processor.getFlipUD(), dontSendNotification);

    /* fetch current configuration */
    s_pmapEQ->setValue(powermap_getPowermapEQAllBands(hPm));
    s_anaOrder->setRange(1, powermap_getMasterOrder(hPm)+0.1f, 1);
    s_anaOrder->setValue(powermap_getAnaOrderAllBands(hPm), dontSendNotification);
    CBchFormat->setSelectedId(powermap_getChOrder(hPm), sendNotification);
    CBnormScheme->setSelectedId(powermap_getNormType(hPm), sendNotification);
    s_Nsources->setRange(1, (int)((float)powermap_getNSHrequired(hPm)/2.0f), 1);
    s_Nsources->setValue(powermap_getNumSources(hPm), sendNotification);
    s_Nsources->setEnabled((powermap_getPowermapMode(hPm)==PM_MODE_MINNORM ||
                            powermap_getPowermapMode(hPm)==PM_MODE_MUSIC) ? true : false);
    resolutionHasChanged = false;
    CBchFormat->setItemEnabled(CH_FUMA, powermap_getMasterOrder(hPm)==SH_ORDER_FIRST ? true : false);
    CBnormScheme->setItemEnabled(NORM_FUMA, powermap_getMasterOrder(hPm)==SH_ORDER_FIRST ? true : false);

    /* tooltips */
    CBmasterOrder->setTooltip("Maximum analysis order (can be lower at different frequencies). Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals as input.");
    CBpmap_method->setTooltip("Activity-map method to use. Plane-wave decomposition (PWD) and minimum-variance distortion-less response (MVDR) options are examples of beamforming based approaches, where static (PWD) or adaptive (MVDR) beamformers are steered towards the grid directions, and the map is derived from their relative energy/power (hence PowerMap). Minimum norm (min-Norm) and Multiple-signal classification (MUSIC) are examples of subspace-based approaches, which operate on the noise or signal subspaces derived from truncating the eigen vectors extracted from the input covariance matrix, subsquently conducting the scanning in this sub-space. The truncation of the eigen-vector matrix is dependent on the number of sources.");
    CBchFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormScheme->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    s_anaOrder->setTooltip("This sets the analysis order for all frequencies. Use the 2-D slider to change the analysis order for specific frequencies.");
    s_pmapEQ->setTooltip("This sets the EQ value for all frequencies (so just a gain). Use the 2-D slider to change the gain for specific frequencies, thus adjusting the contribution of particular frequencies to the output activity-map.");
    CBsourcePreset->setTooltip("Presets for for various higher-order microphone arrays, which configure the frequency-dependent analysis order.");
    s_covAvg->setTooltip("Covariance matrix averaging coefficient (one-pole filter).");
    s_pmapAvg->setTooltip("Activity-map averaging coefficient (one-pole filter).");
    CB_webcam->setTooltip("Optionally, the video from a webcam may be streamed behind the activity-map; allowing for a make-shift acoustic camera. This is particularly effective when using, for example, a 360degree Ricoh Theta camera.");
    TB_greyScale->setTooltip("Sets the plug-in to display the webcam image in 'grey-scale'.");
    TB_flipUD->setTooltip("Flips the webcam image up-down, as it may be preferable to mount the camera upside-down on top of the microphone array; in order to bring the origin of the camera closer to that of the array.");
    TB_flipLR->setTooltip("Flips the webcam image left-right, as some webcams mirror the images taken.");
    CB_hfov->setTooltip("Horizontal field-of-view (FOV) options.");
    CB_aspectRatio->setTooltip("Aspect ratio options.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A plug-in that represents the relative sound energy, or the statistical likelihood of a source arriving at the receiving position from a particular direction using a colour gradient. Yellow indicates high sound energy/likelihood and blue indicates low sound energy/likelihood. The plug-in integrates a variety of different approaches, including: standard Plane-Wave Decomposition (PWD) beamformer-based, Minimum-Variance Distortionless Response (MVDR) beamformer-based, Multiple Signal Classification (MUSIC) pseudo-spectrum-based, and the Cross-Pattern Coherence (CroPaC) algorithm; all of which are written to operate on Ambisonic signals up to 7th order.\n\nNote that the analysis order per frequency band is also user definable, and presets for higher order microphone arrays have been included for convience (which provide some rough appropriate starting values). The plug-in utilises a 812 point uniformly-distributed spherical grid, which is then interpolated into a 2D powermap using amplitude-normalised VBAP gains (i.e. triangular interpolation). The plug-in also allows the user to place real-time video footage behind the activity-map, in order to create a make-shift acoustic camera."));
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
    stopTimer();
    setLookAndFeel(nullptr);
}

void PluginEditor::paint (juce::Graphics& g)
{
    using namespace ColoursUI;

    drawPluginBackgroundAndBanner(g, getBounds());

    /* Panels */
    drawPanelRect(g, { 12,  59,648,325}, panelFill,      panelStroke);
    drawPanel(g, { 13, 398,214,107}, panelFill,      panelStroke);
    drawPanel(g, { 13, 504,214,136}, panelFill,      panelStroke);
    drawPanel(g, {236, 398,424, 35}, panelFill,      panelStroke);
    drawPanel(g, {236, 432,424,105}, panelFill,      panelStroke);
    drawPanel(g, {236, 536,424,105}, panelFill,      panelStroke);

    /* Highlight strips */
    drawPanel(g, {13,398,214,36}, panelFillLight, panelStrokeLight);
    drawPanel(g, {13,504,214,36}, panelFillLight, panelStrokeLight);

    /* Section titles */
    drawLabel(g, {283,33,125,30}, "Display Window", 15.f);
    drawLabel(g, {530,32,37,30}, "L|R:", 11.f);
    drawLabel(g, {576,32,37,30}, "U|D:", 11.f);
    drawLabel(g, {624,32,29,30}, "GS:",  11.f);

    /* Left‑side labels */
    drawLabel(g, {23,402,132,30}, "Max Order:", 15.f);
    drawLabel(g, {23,434,132,30}, "Mic Preset:", 15.f);
    drawLabel(g, {23,466,132,30}, "Format:",     15.f);

    drawLabel(g, {23,507,153,30}, "Map Mode:",   15.f);
    drawLabel(g, {23,540,153,30}, "Number of Sources:", 15.f);
    drawLabel(g, {23,571,132,30}, "Map Avg:",    15.f);
    drawLabel(g, {23,603,132,30}, "Cov. Avg:",   15.f);

    /* Equalisation block */
    drawLabel(g, {243,428,133,30}, "Equalisation", 15.f);
    drawLabel(g, {243,510,37,30}, "100", 12.f);
    drawLabel(g, {398,510,37,30}, "1k",  12.f);
    drawLabel(g, {552,510,37,30}, "10k", 12.f);
    drawLabel(g, {434,510,93,30}, "Frequency (Hz)", 12.f);
    drawLabel(g, {595,510,37,30}, "20k", 12.f);
    drawLabel(g, {643,502,13,30}, "0",   15.f);
    drawLabel(g, {643,473,13,30}, "1",   15.f);
    drawLabel(g, {643,443,13,30}, "2",   15.f);
    
    /* Analysis order block */
    drawLabel(g, {243,532,325,30}, "Analysis Order Per Frequency Band", 15.f);
    drawLabel(g, {243,614,37,30}, "100", 12.f);
    drawLabel(g, {398,614,37,30}, "1k",  12.f);
    drawLabel(g, {552,614,37,30}, "10k", 12.f);
    drawLabel(g, {434,614,93,30}, "Frequency (Hz)", 12.f);
    drawLabel(g, {595,614,37,30}, "20k", 12.f);
    drawLabel(g, {643,606,13,30}, "1",   15.f);

    /* Horizontal FOV block */
    drawLabel(g, {243,400,132,30}, "Horizontal FOV:", 15.f);
    drawLabel(g, {458,400,132,30}, "Aspect Ratio:",   15.f);

    /* Title */
    drawLabel(g, {16,1,100,32}, "SPARTA|", 18.f);
    drawLabel(g, {92,1,112,32}, "PowerMap", 18.f, juce::Justification::centredLeft, juce::Colour(0xfffffc08));

    g.setColour(Colours::white);
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
        195, 16, 530, 11,
        Justification::centredLeft, true);

    /* label for max ORDER */
    int x = 641, y = 540, width = 21, height = 30;
    String text  = String(powermap_getMasterOrder(hPm));
    Colour fillColour = Colours::white;
    g.setColour (fillColour);
    g.setFont (juce::FontOptions (15.00f, Font::plain).withStyle("Bold"));
    g.drawText (text, x, y, width, height,
                Justification::centredLeft, true);

    /* display warning message */
    g.setFont(juce::FontOptions (11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_NinputCH:
            g.setColour(Colours::red);
            g.drawText(TRANS("Insufficient number of input channels (") + String(processor.getTotalNumInputChannels()) +
                       TRANS("/") + String(powermap_getNSHrequired(hPm)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.setColour(Colours::yellow);
            g.drawText(TRANS("Sample rate \"") + String(powermap_getSamplingRate(hPm)) + TRANS("\" is not recommended"),
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
    if (comboBoxThatHasChanged == CBpmap_method.get())
    {
        s_Nsources->setEnabled((powermap_getPowermapMode(hPm)==PM_MODE_MINNORM ||
                                powermap_getPowermapMode(hPm)==PM_MODE_MUSIC) ? true : false);
    }
    else if (comboBoxThatHasChanged == CBsourcePreset.get())
    {
        powermap_setSourcePreset(hPm, CBsourcePreset->getSelectedId());
        anaOrder2dSlider->setRefreshValuesFLAG(true);
        pmapEQ2dSlider->setRefreshValuesFLAG(true);
    }
    else if (comboBoxThatHasChanged == CBmasterOrder.get())
    {
        anaOrder2dSlider->setYrange(1, CBmasterOrder->getSelectedId());
        anaOrder2dSlider->setRefreshValuesFLAG(true);
        s_anaOrder->setRange(1, CBmasterOrder->getSelectedId(), 1);
        s_anaOrder->setValue(CBmasterOrder->getSelectedId());
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

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == s_anaOrder.get())
    {
        powermap_setAnaOrderAllBands(hPm, (int)(s_anaOrder->getValue()+0.5));
        anaOrder2dSlider->setRefreshValuesFLAG(true);
    }
    else if (sliderThatWasMoved == s_pmapEQ.get())
    {
        powermap_setPowermapEQAllBands(hPm, (s_pmapEQ->getValue()));
        pmapEQ2dSlider->setRefreshValuesFLAG(true);
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

void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    CBchFormat->setSelectedId(powermap_getChOrder(hPm), sendNotification);
    CBnormScheme->setSelectedId(powermap_getNormType(hPm), sendNotification);
    CBchFormat->setItemEnabled(CH_FUMA, powermap_getMasterOrder(hPm)==SH_ORDER_FIRST ? true : false);
    CBnormScheme->setItemEnabled(NORM_FUMA, powermap_getMasterOrder(hPm)==SH_ORDER_FIRST ? true : false);

    /* Nsource slider range */
    s_Nsources->setRange(1, (int)((float)powermap_getNSHrequired(hPm)/2.0f), 1);

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
    if(powermap_getCodecStatus(hPm)==CODEC_STATUS_INITIALISING){
        addAndMakeVisible(progressbar);
        progressbar.setAlwaysOnTop(true);
        progress = (double)powermap_getProgressBar0_1(hPm);
        char text[PROGRESSBARTEXT_CHAR_LENGTH];
        powermap_getProgressBarText(hPm, (char*)text);
        progressbar.setTextToDisplay(String(text));
    }
    else
        removeChildComponent(&progressbar);

    /* Some parameters shouldn't be editable during initialisation*/
    if(powermap_getCodecStatus(hPm)==CODEC_STATUS_INITIALISING){
        if(CB_hfov->isEnabled())
            CB_hfov->setEnabled(false);
        if(CB_aspectRatio->isEnabled())
            CB_aspectRatio->setEnabled(false);
        if(CBmasterOrder->isEnabled())
            CBmasterOrder->setEnabled(false);
    }
    else{
        if(!CB_hfov->isEnabled())
            CB_hfov->setEnabled(true);
        if(!CB_aspectRatio->isEnabled())
            CB_aspectRatio->setEnabled(true);
        if(!CBmasterOrder->isEnabled())
            CBmasterOrder->setEnabled(true);
    }

    /* refresh the powermap display */
    if ((overlayIncluded != nullptr) && (processor.getIsPlaying())) {
        float* dirs_deg, *pmap;
        int nDirs, pmapReady, pmapWidth, hfov, aspectRatio;
        pmapReady = powermap_getPmap(hPm, &dirs_deg, &pmap, &nDirs, &pmapWidth, &hfov, &aspectRatio);
        overlayIncluded->setEnableTransparency(CB_webcam->getSelectedId() > 1 ? true : false);
        if(pmapReady){
            overlayIncluded->refreshPowerMap(dirs_deg, pmap, nDirs, pmapWidth, hfov, aspectRatio);
        }
        if(overlayIncluded->getFinishedRefresh()){
            powermap_requestPmapUpdate(hPm);
        }
    }

    /* refresh the 2d sliders */
    if (anaOrder2dSlider->getRefreshValuesFLAG()) {
        anaOrder2dSlider->repaint();
        anaOrder2dSlider->setRefreshValuesFLAG(false);
    }
    if (pmapEQ2dSlider->getRefreshValuesFLAG()) {
        pmapEQ2dSlider->repaint();
        pmapEQ2dSlider->setRefreshValuesFLAG(false);
    }

    /* display warning message, if needed */
    if ((processor.getCurrentNumInputs() < powermap_getNSHrequired(hPm))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ( !((powermap_getSamplingRate(hPm) == 44.1e3) || (powermap_getSamplingRate(hPm) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
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
