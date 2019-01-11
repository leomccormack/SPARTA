/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

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

    s_thresh.reset (new Slider ("new slider"));
    addAndMakeVisible (s_thresh.get());
    s_thresh->setRange (-60, 0, 0.01);
    s_thresh->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s_thresh->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    s_thresh->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    s_thresh->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    s_thresh->setColour (Slider::textBoxTextColourId, Colours::white);
    s_thresh->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_thresh->setColour (Slider::textBoxHighlightColourId, Colour (0x001111ee));
    s_thresh->addListener (this);

    s_thresh->setBounds (96, 364, 64, 64);

    s_ratio.reset (new Slider ("new slider"));
    addAndMakeVisible (s_ratio.get());
    s_ratio->setRange (1, 30, 0.01);
    s_ratio->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s_ratio->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    s_ratio->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    s_ratio->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    s_ratio->setColour (Slider::textBoxTextColourId, Colours::white);
    s_ratio->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_ratio->setColour (Slider::textBoxHighlightColourId, Colour (0x001111ee));
    s_ratio->addListener (this);

    s_ratio->setBounds (168, 364, 64, 64);

    s_knee.reset (new Slider ("new slider"));
    addAndMakeVisible (s_knee.get());
    s_knee->setRange (0, 10, 0.01);
    s_knee->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s_knee->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    s_knee->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    s_knee->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    s_knee->setColour (Slider::textBoxTextColourId, Colours::white);
    s_knee->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_knee->setColour (Slider::textBoxHighlightColourId, Colour (0x001111ee));
    s_knee->addListener (this);

    s_knee->setBounds (240, 364, 64, 64);

    s_attack.reset (new Slider ("new slider"));
    addAndMakeVisible (s_attack.get());
    s_attack->setRange (10, 200, 0.01);
    s_attack->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s_attack->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    s_attack->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    s_attack->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    s_attack->setColour (Slider::textBoxTextColourId, Colours::white);
    s_attack->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_attack->setColour (Slider::textBoxHighlightColourId, Colour (0x001111ee));
    s_attack->addListener (this);

    s_attack->setBounds (319, 364, 64, 64);

    s_release.reset (new Slider ("new slider"));
    addAndMakeVisible (s_release.get());
    s_release->setRange (50, 1000, 0.01);
    s_release->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s_release->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    s_release->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    s_release->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    s_release->setColour (Slider::textBoxTextColourId, Colours::white);
    s_release->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_release->setColour (Slider::textBoxHighlightColourId, Colour (0x001111ee));
    s_release->addListener (this);

    s_release->setBounds (391, 364, 64, 64);

    s_outgain.reset (new Slider ("new slider"));
    addAndMakeVisible (s_outgain.get());
    s_outgain->setRange (-20, 40, 0.01);
    s_outgain->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s_outgain->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    s_outgain->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    s_outgain->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    s_outgain->setColour (Slider::textBoxTextColourId, Colours::white);
    s_outgain->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_outgain->setColour (Slider::textBoxHighlightColourId, Colour (0x001111ee));
    s_outgain->addListener (this);

    s_outgain->setBounds (468, 364, 64, 64);

    s_ingain.reset (new Slider ("new slider"));
    addAndMakeVisible (s_ingain.get());
    s_ingain->setRange (-40, 20, 0.01);
    s_ingain->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    s_ingain->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    s_ingain->setColour (Slider::rotarySliderFillColourId, Colour (0x7fffffff));
    s_ingain->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66ffffff));
    s_ingain->setColour (Slider::textBoxTextColourId, Colours::white);
    s_ingain->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_ingain->setColour (Slider::textBoxHighlightColourId, Colour (0x001111ee));
    s_ingain->addListener (this);

    s_ingain->setBounds (17, 364, 64, 64);

    presetCB.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (presetCB.get());
    presetCB->setEditableText (false);
    presetCB->setJustificationType (Justification::centredLeft);
    presetCB->setTextWhenNothingSelected (String());
    presetCB->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    presetCB->addListener (this);

    presetCB->setBounds (72, 296, 120, 16);

    CHOrderingCB.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CHOrderingCB.get());
    CHOrderingCB->setEditableText (false);
    CHOrderingCB->setJustificationType (Justification::centredLeft);
    CHOrderingCB->setTextWhenNothingSelected (TRANS("ACN"));
    CHOrderingCB->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CHOrderingCB->addListener (this);

    CHOrderingCB->setBounds (288, 296, 80, 16);

    normalisationCB.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (normalisationCB.get());
    normalisationCB->setEditableText (false);
    normalisationCB->setJustificationType (Justification::centredLeft);
    normalisationCB->setTextWhenNothingSelected (TRANS("N3D"));
    normalisationCB->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    normalisationCB->addListener (this);

    normalisationCB->setBounds (440, 296, 88, 16);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (550, 440);


    //[Constructor] You can add your own custom stuff here..
	hVst = ownerFilter;
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* Init TF view */
    addAndMakeVisible (TFviewIncluded = new TFview(ownerFilter, 430, 220, 100.0f, 20e3f, -60.0f, 0.0f));
    TFviewIncluded->setAlwaysOnTop(true);
    TFviewIncluded->setTopLeftPosition(46, 44);
    TFviewIncluded->setVisible(true);
    int numFreqPoints;
    float* freqVector = ambi_drc_getFreqVector(hVst->hAmbi, &numFreqPoints);
    TFviewIncluded->setFreqVector(freqVector, numFreqPoints);

    /* add options to drop down boxes */
    normalisationCB->addItem (TRANS("N3D"), NORM_N3D);
    normalisationCB->addItem (TRANS("SN3D"), NORM_SN3D);
    CHOrderingCB->addItem (TRANS("ACN"), CH_ACN);
    presetCB->addItem(TRANS("Omni"), INPUT_OMNI);
    presetCB->addItem(TRANS("1st order"), INPUT_ORDER_1);
    presetCB->addItem(TRANS("2nd order"), INPUT_ORDER_2);
    presetCB->addItem(TRANS("3rd order"), INPUT_ORDER_3);
    presetCB->addItem(TRANS("4th order"), INPUT_ORDER_4);
    presetCB->addItem(TRANS("5th order"), INPUT_ORDER_5);
    presetCB->addItem(TRANS("6th order"), INPUT_ORDER_6);
    presetCB->addItem(TRANS("7th order"), INPUT_ORDER_7);

	/* fetch current configuration */
	s_thresh->setValue(ambi_drc_getThreshold(hVst->hAmbi), dontSendNotification);
	s_ratio->setValue(ambi_drc_getRatio(hVst->hAmbi), dontSendNotification);
	s_knee->setValue(ambi_drc_getKnee(hVst->hAmbi), dontSendNotification);
	s_ingain->setValue(ambi_drc_getInGain(hVst->hAmbi), dontSendNotification);
    s_outgain->setValue(ambi_drc_getOutGain(hVst->hAmbi), dontSendNotification);
	s_attack->setValue(ambi_drc_getAttack(hVst->hAmbi), dontSendNotification);
	s_release->setValue(ambi_drc_getRelease(hVst->hAmbi), dontSendNotification);
    CHOrderingCB->setSelectedId(ambi_drc_getChOrder(hVst->hAmbi), dontSendNotification);
    normalisationCB->setSelectedId(ambi_drc_getNormType(hVst->hAmbi), dontSendNotification);
    presetCB->setSelectedId(ambi_drc_getInputPreset(hVst->hAmbi), dontSendNotification);

    startTimer(80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    s_thresh = nullptr;
    s_ratio = nullptr;
    s_knee = nullptr;
    s_attack = nullptr;
    s_release = nullptr;
    s_outgain = nullptr;
    s_ingain = nullptr;
    presetCB = nullptr;
    CHOrderingCB = nullptr;
    normalisationCB = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    {
        int x = 0, y = 0, width = 550, height = 440;
        Colour fillColour1 = Colour (0xff5b6d76), fillColour2 = Colour (0xff073642);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       272.0f - 0.0f + x,
                                       152.0f - 0.0f + y,
                                       fillColour2,
                                       288.0f - 0.0f + x,
                                       440.0f - 0.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 10, y = 36, width = 530, height = 246;
        Colour fillColour = Colour (0x17c7c7c7);
        Colour strokeColour = Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 88, y = 320, width = 224, height = 112;
        Colour fillColour = Colour (0x17c7c7c7);
        Colour strokeColour = Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 0, y = 0, width = 550, height = 32;
        Colour fillColour = Colour (0xff073642);
        Colour strokeColour = Colour (0xdcbdbdbd);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 3);

    }

    {
        int x = 96, y = 325, width = 60, height = 30;
        String text (TRANS("Thresh."));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 169, y = 326, width = 60, height = 30;
        String text (TRANS("Ratio"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 241, y = 326, width = 60, height = 30;
        String text (TRANS("Knee"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 311, y = 320, width = 151, height = 112;
        Colour fillColour = Colour (0x17c7c7c7);
        Colour strokeColour = Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 461, y = 320, width = 79, height = 112;
        Colour fillColour = Colour (0x17c7c7c7);
        Colour strokeColour = Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 321, y = 326, width = 60, height = 30;
        String text (TRANS("Attack"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 393, y = 326, width = 60, height = 30;
        String text (TRANS("Release"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 470, y = 326, width = 60, height = 30;
        String text (TRANS("Out Gain"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 96, y = 341, width = 60, height = 30;
        String text (TRANS("(dB)"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 240, y = 341, width = 60, height = 30;
        String text (TRANS("(dB)"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 470, y = 341, width = 60, height = 30;
        String text (TRANS("(dB)"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 320, y = 341, width = 60, height = 30;
        String text (TRANS("(ms)"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 392, y = 341, width = 60, height = 30;
        String text (TRANS("(ms)"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 168, y = 341, width = 60, height = 30;
        String text (TRANS("(X:1)"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 10, y = 320, width = 79, height = 112;
        Colour fillColour = Colour (0x17c7c7c7);
        Colour strokeColour = Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 19, y = 326, width = 60, height = 30;
        String text (TRANS("In Gain"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 18, y = 341, width = 60, height = 30;
        String text (TRANS("(dB)"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 10, y = 288, width = 530, height = 33;
        Colour fillColour = Colour (0x17c7c7c7);
        Colour strokeColour = Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 214, y = 289, width = 172, height = 30;
        String text (TRANS("CH Order:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 390, y = 289, width = 58, height = 30;
        String text (TRANS("Norm:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 22, y = 289, width = 50, height = 30;
        String text (TRANS("Input:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 246, y = 257, width = 58, height = 30;
        String text (TRANS("Time (s)"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 22, y = 246, width = 26, height = 30;
        String text (TRANS("100"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 28, y = 153, width = 26, height = 30;
        String text (TRANS("1k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 28, y = 86, width = 26, height = 30;
        String text (TRANS("5k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 22, y = 57, width = 26, height = 30;
        String text (TRANS("10k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 22, y = 31, width = 26, height = 30;
        String text (TRANS("20k"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 508, y = 31, width = 26, height = 30;
        String text (TRANS("0"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 500, y = 247, width = 26, height = 30;
        String text (TRANS("-16"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 502, y = 85, width = 26, height = 30;
        String text (TRANS("-4"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 502, y = 193, width = 26, height = 30;
        String text (TRANS("-12"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 22, y = 219, width = 26, height = 30;
        String text (TRANS("200"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 502, y = 139, width = 26, height = 30;
        String text (TRANS("-8"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 502, y = 58, width = 26, height = 30;
        String text (TRANS("-2"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 502, y = 112, width = 26, height = 30;
        String text (TRANS("-6"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 502, y = 166, width = 26, height = 30;
        String text (TRANS("-10"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 502, y = 220, width = 26, height = 30;
        String text (TRANS("-14"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 10, y = 288, width = 193, height = 33;
        Colour fillColour = Colour (0x08c7c7c7);
        Colour strokeColour = Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 16, y = 0, width = 100, height = 32;
        String text (TRANS("SPARTA|"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.80f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 92, y = 0, width = 112, height = 32;
        String text (TRANS("AmbiDRC"));
        Colour fillColour = Colour (0xfff77bf5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
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
            g.drawText(TRANS("Set frame size to multiple of ") + String(FRAME_SIZE),
                       getBounds().getWidth()-225, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(ambi_drc_getSamplerate(hVst->hAmbi)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(ambi_drc_getNSHrequired(hVst->hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(ambi_drc_getNSHrequired(hVst->hAmbi)) + TRANS(")"),
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
    g.addTransform(AffineTransform::rotation(-M_PI/2).followedBy(AffineTransform::translation(-(TFviewIncluded->getHeight()/2 - (int)((float)textWidth/2.5f)),
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

void PluginEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == s_thresh.get())
    {
        //[UserSliderCode_s_thresh] -- add your slider handling code here..
		ambi_drc_setThreshold(hVst->hAmbi, s_thresh->getValue());
        //[/UserSliderCode_s_thresh]
    }
    else if (sliderThatWasMoved == s_ratio.get())
    {
        //[UserSliderCode_s_ratio] -- add your slider handling code here..
		ambi_drc_setRatio(hVst->hAmbi, s_ratio->getValue());
        //[/UserSliderCode_s_ratio]
    }
    else if (sliderThatWasMoved == s_knee.get())
    {
        //[UserSliderCode_s_knee] -- add your slider handling code here..
		ambi_drc_setKnee(hVst->hAmbi, s_knee->getValue());
        //[/UserSliderCode_s_knee]
    }
    else if (sliderThatWasMoved == s_attack.get())
    {
        //[UserSliderCode_s_attack] -- add your slider handling code here..
		ambi_drc_setAttack(hVst->hAmbi, s_attack->getValue());
        //[/UserSliderCode_s_attack]
    }
    else if (sliderThatWasMoved == s_release.get())
    {
        //[UserSliderCode_s_release] -- add your slider handling code here..
		ambi_drc_setRelease(hVst->hAmbi, s_release->getValue());
        //[/UserSliderCode_s_release]
    }
    else if (sliderThatWasMoved == s_outgain.get())
    {
        //[UserSliderCode_s_outgain] -- add your slider handling code here..
        ambi_drc_setOutGain(hVst->hAmbi, s_outgain->getValue());
        //[/UserSliderCode_s_outgain]
    }
    else if (sliderThatWasMoved == s_ingain.get())
    {
        //[UserSliderCode_s_ingain] -- add your slider handling code here..
        ambi_drc_setInGain(hVst->hAmbi, s_ingain->getValue());
        //[/UserSliderCode_s_ingain]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == presetCB.get())
    {
        //[UserComboBoxCode_presetCB] -- add your combo box handling code here..
        ambi_drc_setInputPreset(hVst->hAmbi, (INPUT_ORDER)presetCB->getSelectedId());
        //[/UserComboBoxCode_presetCB]
    }
    else if (comboBoxThatHasChanged == CHOrderingCB.get())
    {
        //[UserComboBoxCode_CHOrderingCB] -- add your combo box handling code here..
        ambi_drc_setChOrder(hVst->hAmbi, CHOrderingCB->getSelectedId());
        //[/UserComboBoxCode_CHOrderingCB]
    }
    else if (comboBoxThatHasChanged == normalisationCB.get())
    {
        //[UserComboBoxCode_normalisationCB] -- add your combo box handling code here..
        ambi_drc_setNormType(hVst->hAmbi, normalisationCB->getSelectedId());
        //[/UserComboBoxCode_normalisationCB]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    if (hVst->isPlaying) {
        int wIdx = ambi_drc_getGainTFwIdx(hVst->hAmbi);
        float linePos = (float)wIdx*((float)TFviewIncluded->getWidth() / (float)NUM_DISPLAY_TIME_SLOTS);
        TFviewIncluded->repaint(linePos-10, 0, TFviewIncluded->getWidth(), TFviewIncluded->getHeight());
    }

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
        currentWarning = k_warning_frameSize;
        repaint();
    }
    else if ( !((ambi_drc_getSamplerate(hVst->hAmbi) == 44.1e3) || (ambi_drc_getSamplerate(hVst->hAmbi) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < ambi_drc_getNSHrequired(hVst->hAmbi))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumOutputs() < ambi_drc_getNSHrequired(hVst->hAmbi))){
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
    <RECT pos="0 0 550 440" fill=" radial: 272 152, 288 440, 0=ff5b6d76, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="10 36 530 246" fill="solid: 17c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <RECT pos="88 320 224 112" fill="solid: 17c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <RECT pos="0 0 550 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <TEXT pos="96 325 60 30" fill="solid: ffffffff" hasStroke="0" text="Thresh."
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="169 326 60 30" fill="solid: ffffffff" hasStroke="0" text="Ratio"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="241 326 60 30" fill="solid: ffffffff" hasStroke="0" text="Knee"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="311 320 151 112" fill="solid: 17c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <RECT pos="461 320 79 112" fill="solid: 17c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <TEXT pos="321 326 60 30" fill="solid: ffffffff" hasStroke="0" text="Attack"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="393 326 60 30" fill="solid: ffffffff" hasStroke="0" text="Release"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="470 326 60 30" fill="solid: ffffffff" hasStroke="0" text="Out Gain"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="96 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(dB)"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="240 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(dB)"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="470 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(dB)"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="320 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(ms)"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="392 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(ms)"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="168 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(X:1)"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="10 320 79 112" fill="solid: 17c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <TEXT pos="19 326 60 30" fill="solid: ffffffff" hasStroke="0" text="In Gain"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="18 341 60 30" fill="solid: ffffffff" hasStroke="0" text="(dB)"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="10 288 530 33" fill="solid: 17c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <TEXT pos="214 289 172 30" fill="solid: ffffffff" hasStroke="0" text="CH Order:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="390 289 58 30" fill="solid: ffffffff" hasStroke="0" text="Norm:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="22 289 50 30" fill="solid: ffffffff" hasStroke="0" text="Input:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="246 257 58 30" fill="solid: ffffffff" hasStroke="0" text="Time (s)"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="22 246 26 30" fill="solid: ffffffff" hasStroke="0" text="100"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="28 153 26 30" fill="solid: ffffffff" hasStroke="0" text="1k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="28 86 26 30" fill="solid: ffffffff" hasStroke="0" text="5k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="22 57 26 30" fill="solid: ffffffff" hasStroke="0" text="10k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="22 31 26 30" fill="solid: ffffffff" hasStroke="0" text="20k"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="508 31 26 30" fill="solid: ffffffff" hasStroke="0" text="0"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="500 247 26 30" fill="solid: ffffffff" hasStroke="0" text="-16"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 85 26 30" fill="solid: ffffffff" hasStroke="0" text="-4"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 193 26 30" fill="solid: ffffffff" hasStroke="0" text="-12"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="22 219 26 30" fill="solid: ffffffff" hasStroke="0" text="200"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 139 26 30" fill="solid: ffffffff" hasStroke="0" text="-8"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 58 26 30" fill="solid: ffffffff" hasStroke="0" text="-2"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 112 26 30" fill="solid: ffffffff" hasStroke="0" text="-6"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 166 26 30" fill="solid: ffffffff" hasStroke="0" text="-10"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="502 220 26 30" fill="solid: ffffffff" hasStroke="0" text="-14"
          fontname="Default font" fontsize="12.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="10 288 193 33" fill="solid: 8c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <TEXT pos="16 0 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.80000000000000071054" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 0 112 32" fill="solid: fff77bf5" hasStroke="0" text="AmbiDRC"
          fontname="Default font" fontsize="18.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="863726658f50da67" memberName="s_thresh"
          virtualName="" explicitFocusOrder="0" pos="96 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="-60.00000000000000000000" max="0.00000000000000000000"
          int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="new slider" id="fed2163dcc7c5f5b" memberName="s_ratio"
          virtualName="" explicitFocusOrder="0" pos="168 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="1.00000000000000000000" max="30.00000000000000000000"
          int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="new slider" id="e407bc6da965376a" memberName="s_knee" virtualName=""
          explicitFocusOrder="0" pos="240 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="0.00000000000000000000" max="10.00000000000000000000"
          int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="new slider" id="81df0065d1121d11" memberName="s_attack"
          virtualName="" explicitFocusOrder="0" pos="319 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="10.00000000000000000000" max="200.00000000000000000000"
          int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="new slider" id="b27162f80677dd01" memberName="s_release"
          virtualName="" explicitFocusOrder="0" pos="391 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="50.00000000000000000000" max="1000.00000000000000000000"
          int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="new slider" id="a28183cd37cba9a8" memberName="s_outgain"
          virtualName="" explicitFocusOrder="0" pos="468 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="-20.00000000000000000000" max="40.00000000000000000000"
          int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="new slider" id="d8d8f3ebe9b6f67e" memberName="s_ingain"
          virtualName="" explicitFocusOrder="0" pos="17 364 64 64" rotarysliderfill="7fffffff"
          rotaryslideroutline="66ffffff" textboxtext="ffffffff" textboxbkgd="ffffff"
          textboxhighlight="1111ee" min="-40.00000000000000000000" max="20.00000000000000000000"
          int="0.01000000000000000021" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="abcd469891fabf2d" memberName="presetCB"
            virtualName="" explicitFocusOrder="0" pos="72 296 120 16" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="44b90530e58253e" memberName="CHOrderingCB"
            virtualName="" explicitFocusOrder="0" pos="288 296 80 16" editable="0"
            layout="33" items="" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="caeee0fc74db72a4" memberName="normalisationCB"
            virtualName="" explicitFocusOrder="0" pos="440 296 88 16" editable="0"
            layout="33" items="" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
