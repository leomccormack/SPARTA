/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#ifndef M_PI
#define M_PI ( 3.14159265358979323846264338327950288f )
#endif
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    s_ratio.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_ratio.get());
    s_ratio->setRange (1, 30, 0.01);
    s_ratio->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_ratio->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_ratio->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0x7fffffff));
    s_ratio->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0x66ffffff));
    s_ratio->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_ratio->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_ratio->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x001111ee));
    s_ratio->addListener (this);

    s_ratio->setBounds (168, 364, 64, 64);

    s_knee.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_knee.get());
    s_knee->setRange (0, 10, 0.01);
    s_knee->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_knee->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_knee->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0x7fffffff));
    s_knee->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0x66ffffff));
    s_knee->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_knee->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_knee->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x001111ee));
    s_knee->addListener (this);

    s_knee->setBounds (240, 364, 64, 64);

    s_attack.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_attack.get());
    s_attack->setRange (10, 200, 0.01);
    s_attack->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_attack->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_attack->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0x7fffffff));
    s_attack->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0x66ffffff));
    s_attack->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_attack->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_attack->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x001111ee));
    s_attack->addListener (this);

    s_attack->setBounds (319, 364, 64, 64);

    s_release.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_release.get());
    s_release->setRange (50, 1000, 0.01);
    s_release->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_release->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_release->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0x7fffffff));
    s_release->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0x66ffffff));
    s_release->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_release->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_release->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x001111ee));
    s_release->addListener (this);

    s_release->setBounds (391, 364, 64, 64);

    s_outgain.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_outgain.get());
    s_outgain->setRange (-20, 40, 0.01);
    s_outgain->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_outgain->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_outgain->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0x7fffffff));
    s_outgain->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0x66ffffff));
    s_outgain->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_outgain->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_outgain->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x001111ee));
    s_outgain->addListener (this);

    s_outgain->setBounds (468, 364, 64, 64);

    presetCB.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (presetCB.get());
    presetCB->setEditableText (false);
    presetCB->setJustificationType (juce::Justification::centredLeft);
    presetCB->setTextWhenNothingSelected (juce::String());
    presetCB->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    presetCB->addListener (this);

    presetCB->setBounds (72, 296, 120, 16);

    CHOrderingCB.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CHOrderingCB.get());
    CHOrderingCB->setEditableText (false);
    CHOrderingCB->setJustificationType (juce::Justification::centredLeft);
    CHOrderingCB->setTextWhenNothingSelected (TRANS("ACN"));
    CHOrderingCB->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CHOrderingCB->addListener (this);

    CHOrderingCB->setBounds (288, 296, 80, 16);

    normalisationCB.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (normalisationCB.get());
    normalisationCB->setEditableText (false);
    normalisationCB->setJustificationType (juce::Justification::centredLeft);
    normalisationCB->setTextWhenNothingSelected (TRANS("N3D"));
    normalisationCB->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    normalisationCB->addListener (this);

    normalisationCB->setBounds (440, 296, 88, 16);

    s_ingain.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_ingain.get());
    s_ingain->setRange (-20, 40, 0.01);
    s_ingain->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_ingain->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_ingain->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0x7fffffff));
    s_ingain->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0x66ffffff));
    s_ingain->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_ingain->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_ingain->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x001111ee));
    s_ingain->addListener (this);

    s_ingain->setBounds (16, 364, 64, 64);

    s_thresh.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_thresh.get());
    s_thresh->setRange (-60, 0, 0.01);
    s_thresh->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_thresh->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_thresh->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0x7fffffff));
    s_thresh->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0x66ffffff));
    s_thresh->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_thresh->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_thresh->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x001111ee));
    s_thresh->addListener (this);

    s_thresh->setBounds (96, 364, 64, 64);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (550, 440);


    //[Constructor] You can add your own custom stuff here..
	hVst = ownerFilter;
    hAmbi = hVst->getFXHandle();
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* Init TF view */
    TFviewIncluded.reset (new TFview(ownerFilter, 430, 220, 100.0f, 20e3f, -60.0f, 0.0f));
    addAndMakeVisible (TFviewIncluded.get());
    TFviewIncluded->setAlwaysOnTop(true);
    TFviewIncluded->setTopLeftPosition(46, 44);
    TFviewIncluded->setVisible(true);
    int numFreqPoints;
    float* freqVector = ambi_drc_getFreqVector(hAmbi, &numFreqPoints);
    TFviewIncluded->setFreqVector(freqVector, numFreqPoints);

    /* add options to drop down boxes */
    normalisationCB->addItem (TRANS("N3D"), NORM_N3D);
    normalisationCB->addItem (TRANS("SN3D"), NORM_SN3D);
    normalisationCB->addItem (TRANS("FuMa"), NORM_FUMA);
    CHOrderingCB->addItem (TRANS("ACN"), CH_ACN);
    CHOrderingCB->addItem (TRANS("FuMa"), CH_FUMA);
    presetCB->addItem(TRANS("1st order"), SH_ORDER_FIRST);
    presetCB->addItem(TRANS("2nd order"), SH_ORDER_SECOND);
    presetCB->addItem(TRANS("3rd order"), SH_ORDER_THIRD);
    presetCB->addItem(TRANS("4th order"), SH_ORDER_FOURTH);
    presetCB->addItem(TRANS("5th order"), SH_ORDER_FIFTH);
    presetCB->addItem(TRANS("6th order"), SH_ORDER_SIXTH);
    presetCB->addItem(TRANS("7th order"), SH_ORDER_SEVENTH);
    presetCB->addItem(TRANS("8th order"), SH_ORDER_EIGHTH);
    presetCB->addItem(TRANS("9th order"), SH_ORDER_NINTH);
    presetCB->addItem(TRANS("10th order"), SH_ORDER_TENTH);

	/* fetch current configuration */
    s_thresh->setRange(AMBI_DRC_THRESHOLD_MIN_VAL, AMBI_DRC_THRESHOLD_MAX_VAL, 0.01);
	s_thresh->setValue(ambi_drc_getThreshold(hAmbi), dontSendNotification);
    s_ratio->setRange(AMBI_DRC_RATIO_MIN_VAL, AMBI_DRC_RATIO_MAX_VAL, 0.01);
	s_ratio->setValue(ambi_drc_getRatio(hAmbi), dontSendNotification);
    s_knee->setRange(AMBI_DRC_KNEE_MIN_VAL, AMBI_DRC_KNEE_MAX_VAL, 0.01);
	s_knee->setValue(ambi_drc_getKnee(hAmbi), dontSendNotification);
    s_ingain->setRange(AMBI_DRC_IN_GAIN_MIN_VAL, AMBI_DRC_IN_GAIN_MAX_VAL, 0.01);
	s_ingain->setValue(ambi_drc_getInGain(hAmbi), dontSendNotification);
    s_outgain->setRange(AMBI_DRC_OUT_GAIN_MIN_VAL, AMBI_DRC_OUT_GAIN_MAX_VAL, 0.01);
    s_outgain->setValue(ambi_drc_getOutGain(hAmbi), dontSendNotification);
    s_attack->setRange(AMBI_DRC_ATTACK_MIN_VAL, AMBI_DRC_ATTACK_MAX_VAL, 0.01);
	s_attack->setValue(ambi_drc_getAttack(hAmbi), dontSendNotification);
    s_release->setRange(AMBI_DRC_RELEASE_MIN_VAL, AMBI_DRC_RELEASE_MAX_VAL, 0.01);
	s_release->setValue(ambi_drc_getRelease(hAmbi), dontSendNotification);
    CHOrderingCB->setSelectedId(ambi_drc_getChOrder(hAmbi), dontSendNotification);
    normalisationCB->setSelectedId(ambi_drc_getNormType(hAmbi), dontSendNotification);
    presetCB->setSelectedId(ambi_drc_getInputPreset(hAmbi), dontSendNotification);
    CHOrderingCB->setItemEnabled(CH_FUMA, ambi_drc_getInputPreset(hAmbi)==SH_ORDER_FIRST ? true : false);
    normalisationCB->setItemEnabled(NORM_FUMA, ambi_drc_getInputPreset(hAmbi)==SH_ORDER_FIRST ? true : false);

    /* tooltips */
    presetCB->setTooltip("The input/output order. Note that the plug-in will require (order+1)^2 Ambisonic (spherical harmonic) signals. The plug-in derives the frequency-dependent gain factors based on the omni-directional component, which are then applied to all input signals equally. The spatial properties of the original signals will remain unchanged, although your perception of them after decoding may change.");
    CHOrderingCB->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    normalisationCB->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    s_thresh->setTooltip("Compressor threshold (in dB).");
    s_ratio->setTooltip("Compression ratio (X:1).");
    s_knee->setTooltip("Compressor knee (in dB). Hard-knee: when set to 0; soft-knee: when set to more than 0.");
    s_ingain->setTooltip("Input gain (in dB).");
    s_outgain->setTooltip("Output/Make-up gain (in dB).");
    s_attack->setTooltip("Envelope attack time (in miliseconds).");
    s_release->setTooltip("Envelope release time (in miliseconds).");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("This plug-in is a frequency-dependent Ambisonic dynamic range compressor (DRC). The gain factors are derived by analysing the omnidirectional component for each frequency band, which are then applied to all of the input signals equally. The spatial properties of the original signals will remain unchanged, although your perception of them after decoding may change."));

    /* Specify screen refresh rate */
    startTimer(80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    s_ratio = nullptr;
    s_knee = nullptr;
    s_attack = nullptr;
    s_release = nullptr;
    s_outgain = nullptr;
    presetCB = nullptr;
    CHOrderingCB = nullptr;
    normalisationCB = nullptr;
    s_ingain = nullptr;
    s_thresh = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
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
        int x = 0, y = 235, width = 550, height = 205;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             440.0f - 235.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             360.0f - 235.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 30, width = 550, height = 205;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
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
        float x = 1.0f, y = 2.0f, width = 548.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             616.0f - 1.0f + x,
                                             24.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 10, y = 38, width = 530, height = 244;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 88, y = 320, width = 224, height = 112;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 96, y = 325, width = 60, height = 30;
        juce::String text (TRANS("Thresh."));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 169, y = 326, width = 60, height = 30;
        juce::String text (TRANS("Ratio"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 241, y = 326, width = 60, height = 30;
        juce::String text (TRANS("Knee"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 311, y = 320, width = 151, height = 112;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 461, y = 320, width = 79, height = 112;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 321, y = 326, width = 60, height = 30;
        juce::String text (TRANS("Attack"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 393, y = 326, width = 60, height = 30;
        juce::String text (TRANS("Release"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 470, y = 326, width = 60, height = 30;
        juce::String text (TRANS("Out Gain"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 96, y = 341, width = 60, height = 30;
        juce::String text (TRANS("(dB)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 240, y = 341, width = 60, height = 30;
        juce::String text (TRANS("(dB)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 470, y = 341, width = 60, height = 30;
        juce::String text (TRANS("(dB)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 320, y = 341, width = 60, height = 30;
        juce::String text (TRANS("(ms)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 392, y = 341, width = 60, height = 30;
        juce::String text (TRANS("(ms)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 168, y = 341, width = 60, height = 30;
        juce::String text (TRANS("(X:1)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 10, y = 320, width = 79, height = 112;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 19, y = 326, width = 60, height = 30;
        juce::String text (TRANS("In Gain"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 18, y = 341, width = 60, height = 30;
        juce::String text (TRANS("(dB)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 10, y = 288, width = 530, height = 33;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 214, y = 289, width = 172, height = 30;
        juce::String text (TRANS("CH Order:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 390, y = 289, width = 58, height = 30;
        juce::String text (TRANS("Norm:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 289, width = 50, height = 30;
        juce::String text (TRANS("Input:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 246, y = 257, width = 58, height = 30;
        juce::String text (TRANS("Time (s)"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 246, width = 26, height = 30;
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
        int x = 28, y = 153, width = 26, height = 30;
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
        int x = 28, y = 86, width = 26, height = 30;
        juce::String text (TRANS("5k"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 57, width = 26, height = 30;
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
        int x = 22, y = 31, width = 26, height = 30;
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
        int x = 508, y = 31, width = 26, height = 30;
        juce::String text (TRANS("0"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 500, y = 247, width = 26, height = 30;
        juce::String text (TRANS("-16"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 85, width = 26, height = 30;
        juce::String text (TRANS("-4"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 193, width = 26, height = 30;
        juce::String text (TRANS("-12"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 22, y = 219, width = 26, height = 30;
        juce::String text (TRANS("200"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 139, width = 26, height = 30;
        juce::String text (TRANS("-8"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 58, width = 26, height = 30;
        juce::String text (TRANS("-2"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 112, width = 26, height = 30;
        juce::String text (TRANS("-6"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 166, width = 26, height = 30;
        juce::String text (TRANS("-10"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 502, y = 220, width = 26, height = 30;
        juce::String text (TRANS("-14"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 10, y = 288, width = 193, height = 33;
        juce::Colour fillColour = juce::Colour (0x08c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

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
        juce::String text (TRANS("AmbiDRC"));
        juce::Colour fillColour = juce::Colour (0xfff77bf5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 550, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 440;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 548, y = 0, width = 2, height = 440;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 438, width = 550, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    //[UserPaint] Add your own custom painting code here..

    /* banner text */
	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		185, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    g.setOpacity(1.0f);
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(ambi_drc_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(ambi_drc_getSamplerate(hAmbi)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(ambi_drc_getNSHrequired(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(ambi_drc_getNSHrequired(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
    }

    /* draw colour bar */
    int colourbarWidth = 16;
    g.setOpacity(1.0f);
    Rectangle<int> TFviewBounds = TFviewIncluded->getBounds();
    for(int i=0; i<mapColourTable_N; i++){
        g.setColour(mapColourTable[i]);
        g.fillRect((float)TFviewBounds.getTopRight().x+5.0f,
                   (float)TFviewBounds.getTopRight().y + (float)i*(float)TFviewBounds.getHeight()/(float)mapColourTable_N,
                   (float)colourbarWidth,
                   (float)TFviewBounds.getHeight()/(float)mapColourTable_N);
    }
    g.setColour(Colours::white);
    g.drawRect(TFviewBounds.getTopRight().x+5, TFviewBounds.getTopRight().y, colourbarWidth, TFviewBounds.getHeight(), 1);

    /* axis labels */
    g.setColour(Colours::white);
    int textWidth = 105;
    g.addTransform(AffineTransform::rotation(-M_PI/2.0f).followedBy(AffineTransform::translation(-(TFviewIncluded->getHeight()/2 - (int)((float)textWidth/2.5f)),
                                                                                              TFviewIncluded->getHeight() - textWidth/2)));
    g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
    g.drawText(TRANS("Frequency (Hz)"), -36,
               (int) ((float)TFviewIncluded->getHeight()/2.0f) - textWidth/2,
               textWidth, 57, Justification::centred);

	textWidth = 118;
    g.drawText(TRANS("Gain Reduction (dB)"), -36,
               (int) ((float)TFviewIncluded->getHeight()/2.0f) - textWidth/2,
               textWidth, 1084, Justification::centred);

    g.addTransform(AffineTransform());

    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..


	repaint();
    //[/UserResized]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == s_ratio.get())
    {
        //[UserSliderCode_s_ratio] -- add your slider handling code here..
		ambi_drc_setRatio(hAmbi, (float)s_ratio->getValue());
        //[/UserSliderCode_s_ratio]
    }
    else if (sliderThatWasMoved == s_knee.get())
    {
        //[UserSliderCode_s_knee] -- add your slider handling code here..
		ambi_drc_setKnee(hAmbi, (float)s_knee->getValue());
        //[/UserSliderCode_s_knee]
    }
    else if (sliderThatWasMoved == s_attack.get())
    {
        //[UserSliderCode_s_attack] -- add your slider handling code here..
		ambi_drc_setAttack(hAmbi, (float)s_attack->getValue());
        //[/UserSliderCode_s_attack]
    }
    else if (sliderThatWasMoved == s_release.get())
    {
        //[UserSliderCode_s_release] -- add your slider handling code here..
		ambi_drc_setRelease(hAmbi, (float)s_release->getValue());
        //[/UserSliderCode_s_release]
    }
    else if (sliderThatWasMoved == s_outgain.get())
    {
        //[UserSliderCode_s_outgain] -- add your slider handling code here..
        ambi_drc_setOutGain(hAmbi, (float)s_outgain->getValue());
        //[/UserSliderCode_s_outgain]
    }
    else if (sliderThatWasMoved == s_ingain.get())
    {
        //[UserSliderCode_s_ingain] -- add your slider handling code here..
        ambi_drc_setInGain(hAmbi, (float)s_ingain->getValue());
        //[/UserSliderCode_s_ingain]
    }
    else if (sliderThatWasMoved == s_thresh.get())
    {
        //[UserSliderCode_s_thresh] -- add your slider handling code here..
        ambi_drc_setThreshold(hAmbi, (float)s_thresh->getValue());
        //[/UserSliderCode_s_thresh]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == presetCB.get())
    {
        //[UserComboBoxCode_presetCB] -- add your combo box handling code here..
        ambi_drc_setInputPreset(hAmbi, (SH_ORDERS)presetCB->getSelectedId());
        //[/UserComboBoxCode_presetCB]
    }
    else if (comboBoxThatHasChanged == CHOrderingCB.get())
    {
        //[UserComboBoxCode_CHOrderingCB] -- add your combo box handling code here..
        ambi_drc_setChOrder(hAmbi, CHOrderingCB->getSelectedId());
        //[/UserComboBoxCode_CHOrderingCB]
    }
    else if (comboBoxThatHasChanged == normalisationCB.get())
    {
        //[UserComboBoxCode_normalisationCB] -- add your combo box handling code here..
        ambi_drc_setNormType(hAmbi, normalisationCB->getSelectedId());
        //[/UserComboBoxCode_normalisationCB]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    CHOrderingCB->setSelectedId(ambi_drc_getChOrder(hAmbi), dontSendNotification);
    normalisationCB->setSelectedId(ambi_drc_getNormType(hAmbi), dontSendNotification);
    CHOrderingCB->setItemEnabled(CH_FUMA, ambi_drc_getInputPreset(hAmbi)==SH_ORDER_FIRST ? true : false);
    normalisationCB->setItemEnabled(NORM_FUMA, ambi_drc_getInputPreset(hAmbi)==SH_ORDER_FIRST ? true : false);

    if (hVst->getIsPlaying()) {
        int wIdx = ambi_drc_getGainTFwIdx(hAmbi);
        float linePos = (float)wIdx*((float)TFviewIncluded->getWidth() / (float)AMBI_DRC_NUM_DISPLAY_TIME_SLOTS);
        TFviewIncluded->repaint((int)linePos-10, 0, TFviewIncluded->getWidth(), TFviewIncluded->getHeight());
    }

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % ambi_drc_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ( !((ambi_drc_getSamplerate(hAmbi) == 44.1e3) || (ambi_drc_getSamplerate(hAmbi) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < ambi_drc_getNSHrequired(hAmbi))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumOutputs() < ambi_drc_getNSHrequired(hAmbi))){
        currentWarning = k_warning_NoutputCH;
        repaint(0,0,getWidth(),32);
    }
    else if(currentWarning){
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
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
                 parentClasses="public AudioProcessorEditor, public Timer" constructorParams="PluginProcessor* ownerFilter"
                 variableInitialisers="AudioProcessorEditor(ownerFilter)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="550" initialHeight="440">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 235 550 205" fill="linear: 8 440, 8 360, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="0 30 550 205" fill="linear: 8 32, 8 104, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <ROUNDRECT pos="1 2 548 31" cornerSize="5.0" fill="linear: 0 32, 616 24, 0=ff041518, 1=ff19313f"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="10 38 530 244" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <RECT pos="88 320 224 112" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <TEXT pos="96 325 60 30" fill="solid: ffffffff" hasStroke="0" text="Thresh."
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="169 326 60 30" fill="solid: ffffffff" hasStroke="0" text="Ratio"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="241 326 60 30" fill="solid: ffffffff" hasStroke="0" text="Knee"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="311 320 151 112" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <RECT pos="461 320 79 112" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <TEXT pos="321 326 60 30" fill="solid: ffffffff" hasStroke="0" text="Attack"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="393 326 60 30" fill="solid: ffffffff" hasStroke="0" text="Release"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="470 326 60 30" fill="solid: ffffffff" hasStroke="0" text="Out Gain"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="96 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(dB)"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="240 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(dB)"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="470 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(dB)"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="320 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(ms)"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="392 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(ms)"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="168 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(X:1)"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="10 320 79 112" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <TEXT pos="19 326 60 30" fill="solid: ffffffff" hasStroke="0" text="In Gain"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="18 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(dB)"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="10 288 530 33" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <TEXT pos="214 289 172 30" fill="solid: ffffffff" hasStroke="0" text="CH Order:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="390 289 58 30" fill="solid: ffffffff" hasStroke="0" text="Norm:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="22 289 50 30" fill="solid: ffffffff" hasStroke="0" text="Input:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="246 257 58 30" fill="solid: ffffffff" hasStroke="0" text="Time (s)"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="22 246 26 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="28 153 26 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="28 86 26 30" fill="solid: ffffffff" hasStroke="0" text="5k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="22 57 26 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="22 31 26 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="508 31 26 30" fill="solid: ffffffff" hasStroke="0" text="0"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="500 247 26 30" fill="solid: ffffffff" hasStroke="0" text="-16"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 85 26 30" fill="solid: ffffffff" hasStroke="0" text="-4"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 193 26 30" fill="solid: ffffffff" hasStroke="0" text="-12"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="22 219 26 30" fill="solid: ffffffff" hasStroke="0" text="200"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 139 26 30" fill="solid: ffffffff" hasStroke="0" text="-8"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 58 26 30" fill="solid: ffffffff" hasStroke="0" text="-2"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 112 26 30" fill="solid: ffffffff" hasStroke="0" text="-6"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 166 26 30" fill="solid: ffffffff" hasStroke="0" text="-10"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 220 26 30" fill="solid: ffffffff" hasStroke="0" text="-14"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="10 288 193 33" fill="solid: 8c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 112 32" fill="solid: fff77bf5" hasStroke="0" text="AmbiDRC"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 550 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 440" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="548 0 2 440" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 438 550 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="fed2163dcc7c5f5b" memberName="s_ratio"
          virtualName="" explicitFocusOrder="0" pos="168 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="1.0" max="30.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="e407bc6da965376a" memberName="s_knee" virtualName=""
          explicitFocusOrder="0" pos="240 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="0.0" max="10.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="81df0065d1121d11" memberName="s_attack"
          virtualName="" explicitFocusOrder="0" pos="319 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="10.0" max="200.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="b27162f80677dd01" memberName="s_release"
          virtualName="" explicitFocusOrder="0" pos="391 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="50.0" max="1000.0" int="0.01"
          style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="a28183cd37cba9a8" memberName="s_outgain"
          virtualName="" explicitFocusOrder="0" pos="468 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="-20.0" max="40.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="abcd469891fabf2d" memberName="presetCB"
            virtualName="" explicitFocusOrder="0" pos="72 296 120 16" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="44b90530e58253e" memberName="CHOrderingCB"
            virtualName="" explicitFocusOrder="0" pos="288 296 80 16" editable="0"
            layout="33" items="" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="caeee0fc74db72a4" memberName="normalisationCB"
            virtualName="" explicitFocusOrder="0" pos="440 296 88 16" editable="0"
            layout="33" items="" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="aaacc03ec0b04595" memberName="s_ingain"
          virtualName="" explicitFocusOrder="0" pos="16 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="-20.0" max="40.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="5b7f5b1c551c43d1" memberName="s_thresh"
          virtualName="" explicitFocusOrder="0" pos="96 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="-60.0" max="0.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

