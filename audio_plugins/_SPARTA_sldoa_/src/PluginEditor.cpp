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
    CB_CHorder->setTextWhenNothingSelected (TRANS("ACN"));
    CB_CHorder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CB_CHorder->addListener (this);

    CB_CHorder->setBounds (66, 447, 64, 18);

    CB_Norm.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CB_Norm.get());
    CB_Norm->setEditableText (false);
    CB_Norm->setJustificationType (juce::Justification::centredLeft);
    CB_Norm->setTextWhenNothingSelected (TRANS("N3D"));
    CB_Norm->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
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
    CBinputTypePreset->setTextWhenNothingSelected (TRANS("Default"));
    CBinputTypePreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBinputTypePreset->addItem (TRANS("Ideal SH"), 1);
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
    CBmasterOrder->setTextWhenNothingSelected (TRANS("Default"));
    CBmasterOrder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
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


    //[UserPreSize]
    //[/UserPreSize]

    setSize (634, 514);


    //[Constructor] You can add your own custom stuff here..

    /* handles */
    hVst = ownerFilter;
    hSld = hVst->getFXHandle();

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
    overlayIncluded.reset (new overlay(ownerFilter));
    addAndMakeVisible (overlayIncluded.get());
    overlayIncluded->setAlwaysOnTop(true);
    overlayIncluded->setBounds(previewArea);

    /* Camera support */
    updateCameraList();
    CB_webcam->setSelectedId (hVst->getCameraID(), dontSendNotification);
    CB_webcam->onChange = [this] { cameraChanged(); };
    addAndMakeVisible (lastSnapshot);
    TB_greyScale->setToggleState(hVst->getGreyScale(), dontSendNotification);
    TB_flipLR->setToggleState(hVst->getFlipLR(), dontSendNotification);
    TB_flipUD->setToggleState(hVst->getFlipUD(), dontSendNotification);

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

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

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


    //[Destructor]. You can add your own custom destruction code here..
    overlayIncluded = nullptr;
    anaOrder2dSlider = nullptr;
    setLookAndFeel(nullptr);
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 272, width = 634, height = 242;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
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
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
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
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
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
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 204, y = 374, width = 422, height = 34;
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
        int x = 204, y = 407, width = 422, height = 95;
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
        int x = 14, y = 410, width = 96, height = 30;
        juce::String text (TRANS("Mic Preset:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 14, y = 468, width = 112, height = 30;
        juce::String text (TRANS("Avg (ms):"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 14, y = 440, width = 127, height = 30;
        juce::String text (TRANS("Format:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 216, y = 405, width = 312, height = 30;
        juce::String text (TRANS("Analysis Order Per Frequency Band"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 611, y = 466, width = 13, height = 30;
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
        int x = 211, y = 478, width = 37, height = 30;
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
        int x = 366, y = 478, width = 37, height = 30;
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
        int x = 520, y = 478, width = 37, height = 30;
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
        int x = 402, y = 478, width = 93, height = 30;
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
        int x = 563, y = 478, width = 37, height = 30;
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
        int x = 216, y = 376, width = 160, height = 30;
        juce::String text (TRANS("Minimum Freq (Hz):"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 422, y = 376, width = 162, height = 30;
        juce::String text (TRANS("Maximum Freq (Hz):"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 14, y = 376, width = 104, height = 30;
        juce::String text (TRANS("Max Order:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
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
        juce::String text (TRANS("SLDoA"));
        juce::Colour fillColour = juce::Colour (0xffff4848);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 584, y = 32, width = 29, height = 30;
        juce::String text (TRANS("GS:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 536, y = 32, width = 37, height = 30;
        juce::String text (TRANS("U|D:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 490, y = 32, width = 37, height = 30;
        juce::String text (TRANS("L|R:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 267, y = 33, width = 125, height = 30;
        juce::String text (TRANS("Display Window"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 636, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 514;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 632, y = 0, width = 2, height = 514;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 512, width = 636, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 8, y = 374, width = 197, height = 34;
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
        int x = 13, y = 59, width = 608, height = 303;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		166, 16, 530, 11,
		Justification::centredLeft, true);

    Colour strokeColour = Colour (0x86a3a4a5);
    g.setColour (strokeColour);
    g.setOpacity(0.8f);
    g.drawRect (previewArea);


    /* label for max ORDER */
    {
        int x = 610, y = 412, width = 13, height = 30;
        String text = String(sldoa_getMasterOrder(hSld));
        Colour fillColour = Colours::white;
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(sldoa_getSamplingRate(hSld)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(sldoa_getNSHrequired(hSld)) + TRANS(")"),
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
    //[/UserResized]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == avgSlider.get())
    {
        //[UserSliderCode_avgSlider] -- add your slider handling code here..
        sldoa_setAvg(hSld, (float)avgSlider->getValue());
        //[/UserSliderCode_avgSlider]
    }
    else if (sliderThatWasMoved == slider_anaOrder.get())
    {
        //[UserSliderCode_slider_anaOrder] -- add your slider handling code here..
        sldoa_setAnaOrderAllBands(hSld, (int)(slider_anaOrder->getValue()+0.5));
        anaOrder2dSlider->setRefreshValuesFLAG(true);
        //[/UserSliderCode_slider_anaOrder]
    }
    else if (sliderThatWasMoved == s_minFreq.get())
    {
        //[UserSliderCode_s_minFreq] -- add your slider handling code here..
        sldoa_setMinFreq(hSld, (float)s_minFreq->getValue());


        //[/UserSliderCode_s_minFreq]
    }
    else if (sliderThatWasMoved == s_maxFreq.get())
    {
        //[UserSliderCode_s_maxFreq] -- add your slider handling code here..
        sldoa_setMaxFreq(hSld, (float)s_maxFreq->getValue());
        //[/UserSliderCode_s_maxFreq]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CB_CHorder.get())
    {
        //[UserComboBoxCode_CB_CHorder] -- add your combo box handling code here..
        sldoa_setChOrder(hSld, CB_CHorder->getSelectedId());
        //[/UserComboBoxCode_CB_CHorder]
    }
    else if (comboBoxThatHasChanged == CB_Norm.get())
    {
        //[UserComboBoxCode_CB_Norm] -- add your combo box handling code here..
        sldoa_setNormType(hSld, CB_Norm->getSelectedId());
        //[/UserComboBoxCode_CB_Norm]
    }
    else if (comboBoxThatHasChanged == CBinputTypePreset.get())
    {
        //[UserComboBoxCode_CBinputTypePreset] -- add your combo box handling code here..
        sldoa_setSourcePreset(hSld, CBinputTypePreset->getSelectedId());
        anaOrder2dSlider->setRefreshValuesFLAG(true);
        //[/UserComboBoxCode_CBinputTypePreset]
    }
    else if (comboBoxThatHasChanged == CBmasterOrder.get())
    {
        //[UserComboBoxCode_CBmasterOrder] -- add your combo box handling code here..
        sldoa_setMasterOrder(hSld, CBmasterOrder->getSelectedId());
        CBinputTypePreset->setSelectedId(1);
        anaOrder2dSlider->setYrange(1, CBmasterOrder->getSelectedId());
        sldoa_setAnaOrderAllBands(hSld, CBmasterOrder->getSelectedId());
        anaOrder2dSlider->setRefreshValuesFLAG(true);
        slider_anaOrder->setRange(1, CBmasterOrder->getSelectedId(), 1);
        slider_anaOrder->setValue(CBmasterOrder->getSelectedId());
        repaint();
        //[/UserComboBoxCode_CBmasterOrder]
    }
    else if (comboBoxThatHasChanged == CB_webcam.get())
    {
        //[UserComboBoxCode_CB_webcam] -- add your combo box handling code here..
        hVst->setCameraID(CB_webcam->getSelectedId());
        cameraChanged();
        if(CB_webcam->getSelectedId()==1){
            incomingImage.clear(previewArea);
            lastSnapshot.setImage(incomingImage);
        }
        //[/UserComboBoxCode_CB_webcam]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == TB_greyScale.get())
    {
        //[UserButtonCode_TB_greyScale] -- add your button handler code here..
        hVst->setGreyScale(TB_greyScale->getToggleState());
        //[/UserButtonCode_TB_greyScale]
    }
    else if (buttonThatWasClicked == TB_flipUD.get())
    {
        //[UserButtonCode_TB_flipUD] -- add your button handler code here..
        hVst->setFlipUD(TB_flipUD->getToggleState());
        //[/UserButtonCode_TB_flipUD]
    }
    else if (buttonThatWasClicked == TB_flipLR.get())
    {
        //[UserButtonCode_TB_flipLR] -- add your button handler code here..
        hVst->setFlipLR(TB_flipLR->getToggleState());
        //[/UserButtonCode_TB_flipLR]
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
            if ((overlayIncluded != nullptr) && (hVst->getIsPlaying()))
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
            else if ((hVst->getCurrentNumInputs() < sldoa_getNSHrequired(hSld))){
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

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public AudioProcessorEditor, public MultiTimer, private CameraDevice::Listener, public AsyncUpdater"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter), progressbar(progress)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="634" initialHeight="514">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 272 634 242" fill="linear: 8 520, 8 416, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="0 30 634 242" fill="linear: 8 32, 8 136, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <ROUNDRECT pos="1 2 632 31" cornerSize="5.0" fill="linear: 0 32, 632 24, 0=ff041518, 1=ff19313f"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="8 374 197 128" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="204 374 422 34" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="204 407 422 95" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="14 410 96 30" fill="solid: ffffffff" hasStroke="0" text="Mic Preset:"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="14 468 112 30" fill="solid: ffffffff" hasStroke="0" text="Avg (ms):"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="14 440 127 30" fill="solid: ffffffff" hasStroke="0" text="Format:"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="216 405 312 30" fill="solid: ffffffff" hasStroke="0" text="Analysis Order Per Frequency Band"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="611 466 13 30" fill="solid: ffffffff" hasStroke="0" text="1"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="211 478 37 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="366 478 37 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="520 478 37 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="402 478 93 30" fill="solid: ffffffff" hasStroke="0" text="Frequency (Hz)"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="563 478 37 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="216 376 160 30" fill="solid: ffffffff" hasStroke="0" text="Minimum Freq (Hz):"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="422 376 162 30" fill="solid: ffffffff" hasStroke="0" text="Maximum Freq (Hz):"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="14 376 104 30" fill="solid: ffffffff" hasStroke="0" text="Max Order:"
          fontname="Default font" fontsize="14.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 112 32" fill="solid: ffff4848" hasStroke="0" text="SLDoA"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="584 32 29 30" fill="solid: ffffffff" hasStroke="0" text="GS:"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="536 32 37 30" fill="solid: ffffffff" hasStroke="0" text="U|D:"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="490 32 37 30" fill="solid: ffffffff" hasStroke="0" text="L|R:"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="267 33 125 30" fill="solid: ffffffff" hasStroke="0" text="Display Window"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 636 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 514" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="632 0 2 514" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 512 636 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="8 374 197 34" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="13 59 608 303" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="86d1295f97e935ba" memberName="avgSlider"
          virtualName="" explicitFocusOrder="0" pos="80 473 118 24" bkgcol="ff5c5d5e"
          trackcol="ff315b6e" min="0.0" max="2000.0" int="0.1" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="45"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="3d1c447f9542fa94" memberName="CB_CHorder"
            virtualName="" explicitFocusOrder="0" pos="66 447 64 18" editable="0"
            layout="33" items="" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="d046f2696f3a4a04" memberName="CB_Norm"
            virtualName="" explicitFocusOrder="0" pos="131 447 68 18" editable="0"
            layout="33" items="" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="50ea77f60aadeeca" memberName="slider_anaOrder"
          virtualName="" explicitFocusOrder="0" pos="576 424 40 66" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.0" max="1.0" int="1.0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="932ca035edce041d" memberName="CBinputTypePreset"
            virtualName="" explicitFocusOrder="0" pos="96 417 103 18" editable="0"
            layout="33" items="Ideal SH" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="905f4ab0adab1f4f" memberName="s_minFreq"
          virtualName="" explicitFocusOrder="0" pos="352 382 56 20" min="0.0"
          max="24000.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="45" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="3aad5000f228ef1b" memberName="s_maxFreq"
          virtualName="" explicitFocusOrder="0" pos="560 382 56 20" min="0.0"
          max="24000.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="45" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="346a30a1bf8969e9" memberName="CBmasterOrder"
            virtualName="" explicitFocusOrder="0" pos="96 382 103 18" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="" id="974f5da4ceed6bb6" memberName="CB_webcam" virtualName=""
            explicitFocusOrder="0" pos="395 38 92 17" editable="0" layout="33"
            items="" textWhenNonSelected="" textWhenNoItems=""/>
  <TOGGLEBUTTON name="new toggle button" id="78ff43e4ccfdc462" memberName="TB_greyScale"
                virtualName="" explicitFocusOrder="0" pos="600 35 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="f4031e45e07a36d" memberName="TB_flipUD"
                virtualName="" explicitFocusOrder="0" pos="559 35 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="bb60feb319e3e7d4" memberName="TB_flipLR"
                virtualName="" explicitFocusOrder="0" pos="511 35 24 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

