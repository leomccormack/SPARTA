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

//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    CBsourceDirsPreset.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBsourceDirsPreset.get());
    CBsourceDirsPreset->setEditableText (false);
    CBsourceDirsPreset->setJustificationType (juce::Justification::centredLeft);
    CBsourceDirsPreset->setTextWhenNothingSelected (juce::String());
    CBsourceDirsPreset->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBsourceDirsPreset->addListener (this);

    CBsourceDirsPreset->setBounds (104, 64, 112, 20);

    SL_num_sources.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_sources.get());
    SL_num_sources->setRange (1, 64, 1);
    SL_num_sources->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_sources->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_sources->addListener (this);

    SL_num_sources->setBounds (160, 416, 48, 20);

    CBoutputFormat.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBoutputFormat.get());
    CBoutputFormat->setEditableText (false);
    CBoutputFormat->setJustificationType (juce::Justification::centredLeft);
    CBoutputFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBoutputFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBoutputFormat->addListener (this);

    CBoutputFormat->setBounds (128, 270, 112, 20);

    CBnormalisation.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBnormalisation.get());
    CBnormalisation->setEditableText (false);
    CBnormalisation->setJustificationType (juce::Justification::centredLeft);
    CBnormalisation->setTextWhenNothingSelected (TRANS("N3D"));
    CBnormalisation->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnormalisation->addListener (this);

    CBnormalisation->setBounds (128, 294, 112, 20);

    CBorder.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBorder.get());
    CBorder->setEditableText (false);
    CBorder->setJustificationType (juce::Justification::centredLeft);
    CBorder->setTextWhenNothingSelected (juce::String());
    CBorder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBorder->addListener (this);

    CBorder->setBounds (128, 246, 112, 20);

    s_roomWidth.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_roomWidth.get());
    s_roomWidth->setRange (-60, 0, 0.01);
    s_roomWidth->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_roomWidth->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_roomWidth->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_roomWidth->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    s_roomWidth->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0x7fffffff));
    s_roomWidth->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0x66ffffff));
    s_roomWidth->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_roomWidth->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_roomWidth->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x001111ee));
    s_roomWidth->addListener (this);

    s_roomWidth->setBounds (16, 144, 64, 64);

    s_roomDepth.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_roomDepth.get());
    s_roomDepth->setRange (-60, 0, 0.01);
    s_roomDepth->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_roomDepth->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_roomDepth->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_roomDepth->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    s_roomDepth->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0x7fffffff));
    s_roomDepth->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0x66ffffff));
    s_roomDepth->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_roomDepth->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_roomDepth->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x001111ee));
    s_roomDepth->addListener (this);

    s_roomDepth->setBounds (88, 144, 64, 64);

    s_roomHeight.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_roomHeight.get());
    s_roomHeight->setRange (-60, 0, 0.01);
    s_roomHeight->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_roomHeight->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    s_roomHeight->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_roomHeight->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    s_roomHeight->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0x7fffffff));
    s_roomHeight->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0x66ffffff));
    s_roomHeight->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_roomHeight->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_roomHeight->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x001111ee));
    s_roomHeight->addListener (this);

    s_roomHeight->setBounds (160, 144, 64, 64);

    SL_num_sources2.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_sources2.get());
    SL_num_sources2->setRange (0, 2000, 1);
    SL_num_sources2->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_sources2->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    SL_num_sources2->addListener (this);

    SL_num_sources2->setBounds (120, 96, 96, 20);

    SL_num_sources3.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_sources3.get());
    SL_num_sources3->setRange (1, 64, 1);
    SL_num_sources3->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_sources3->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_sources3->addListener (this);

    SL_num_sources3->setBounds (400, 64, 48, 20);

    CBsourceDirsPreset2.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBsourceDirsPreset2.get());
    CBsourceDirsPreset2->setEditableText (false);
    CBsourceDirsPreset2->setJustificationType (juce::Justification::centredLeft);
    CBsourceDirsPreset2->setTextWhenNothingSelected (juce::String());
    CBsourceDirsPreset2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBsourceDirsPreset2->addListener (this);

    CBsourceDirsPreset2->setBounds (389, 88, 64, 20);

    test_x.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (test_x.get());
    test_x->setRange (0, 10, 0.01);
    test_x->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    test_x->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    test_x->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    test_x->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    test_x->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0x7fffffff));
    test_x->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0x66ffffff));
    test_x->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    test_x->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    test_x->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x001111ee));
    test_x->addListener (this);

    test_x->setBounds (256, 240, 64, 64);

    test_y.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (test_y.get());
    test_y->setRange (0, 10, 0.01);
    test_y->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    test_y->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    test_y->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    test_y->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    test_y->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0x7fffffff));
    test_y->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0x66ffffff));
    test_y->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    test_y->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    test_y->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x001111ee));
    test_y->addListener (this);

    test_y->setBounds (328, 240, 64, 64);

    test_z.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (test_z.get());
    test_z->setRange (0, 10, 0.01);
    test_z->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    test_z->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    test_z->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    test_z->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6d));
    test_z->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0x7fffffff));
    test_z->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0x66ffffff));
    test_z->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    test_z->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    test_z->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x001111ee));
    test_z->addListener (this);

    test_z->setBounds (400, 240, 64, 64);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (820, 600);


    //[Constructor] You can add your own custom stuff here..

    /* handle to pluginProcessor */
	hVst = ownerFilter;
    hAmbi = hVst->getFXHandle();

    /* init OpenGL */
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* remove slider bit of these sliders */
    SL_num_sources->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_sources->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_sources->setSliderSnapsToMousePosition(false);

    /* add combo box options */
    CBorder->addItem (TRANS("1st order"), SH_ORDER_FIRST);
    CBorder->addItem (TRANS("2nd order"), SH_ORDER_SECOND);
    CBorder->addItem (TRANS("3rd order"), SH_ORDER_THIRD);
    CBorder->addItem (TRANS("4th order"), SH_ORDER_FOURTH);
    CBorder->addItem (TRANS("5th order"), SH_ORDER_FIFTH);
    CBorder->addItem (TRANS("6th order"), SH_ORDER_SIXTH);
    CBorder->addItem (TRANS("7th order"), SH_ORDER_SEVENTH);
    CBoutputFormat->addItem (TRANS("ACN"), CH_ACN);
    CBoutputFormat->addItem (TRANS("FuMa"), CH_FUMA);
    CBnormalisation->addItem (TRANS("N3D"), NORM_N3D);
    CBnormalisation->addItem (TRANS("SN3D"), NORM_SN3D);
    CBnormalisation->addItem (TRANS("FuMa"), NORM_FUMA);

    /* source coordinates viewport */
    sourceCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (sourceCoordsVP.get());
    sourceCoordsView_handle = new inputCoordsView(ownerFilter, ROOM_SIM_MAX_NUM_SOURCES, ambi_roomsim_getNumSources(hAmbi));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(22, 403, 212, 155);
    sourceCoordsView_handle->setNCH(ambi_roomsim_getNumSources(hAmbi));

    /* grab current parameter settings */
    SL_num_sources->setValue(ambi_roomsim_getNumSources(hAmbi),dontSendNotification);
    CBoutputFormat->setSelectedId(ambi_roomsim_getChOrder(hAmbi), dontSendNotification);
    CBorder->setSelectedId(ambi_roomsim_getOutputOrder(hAmbi), dontSendNotification);
    CBnormalisation->setSelectedId(ambi_roomsim_getNormType(hAmbi), dontSendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);

    /* create panning window */
//    panWindow.reset (new pannerView(ownerFilter, 480, 240));
//    addAndMakeVisible (panWindow.get());
//    panWindow->setBounds (220, 58, 480, 240);
//    refreshPanViewWindow = true;

    /* tooltips */
    CBorder->setTooltip("The encoding order. Note that the plug-in will output (order+1)^2 Ambisonic (spherical harmonic) signals.");
    CBoutputFormat->setTooltip("Ambisonic channel ordering convention (Note that AmbiX: ACN/SN3D).");
    CBnormalisation->setTooltip("Ambisonic normalisation scheme (Note that AmbiX: ACN/SN3D).");
    CBsourceDirsPreset->setTooltip("Presets for source encoding directions.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("WIP"));

	/* Specify screen refresh rate */
    startTimer(40);//80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    CBsourceDirsPreset = nullptr;
    SL_num_sources = nullptr;
    CBoutputFormat = nullptr;
    CBnormalisation = nullptr;
    CBorder = nullptr;
    s_roomWidth = nullptr;
    s_roomDepth = nullptr;
    s_roomHeight = nullptr;
    SL_num_sources2 = nullptr;
    SL_num_sources3 = nullptr;
    CBsourceDirsPreset2 = nullptr;
    test_x = nullptr;
    test_y = nullptr;
    test_z = nullptr;


    //[Destructor]. You can add your own custom destruction code here..

    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 33, width = 816, height = 575;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 33.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             232.0f - 33.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 15, y = 241, width = 233, height = 119;
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
        int x = 12, y = 58, width = 452, height = 158;
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
        float x = 1.0f, y = 2.0f, width = 813.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
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
        int x = 183, y = 497, width = 196, height = 64;
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
        int x = 23, y = 57, width = 67, height = 30;
        juce::String text (TRANS("Presets: "));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 488, y = 57, width = 312, height = 383;
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
        int x = 15, y = 385, width = 196, height = 194;
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
        int x = 175, y = 33, width = 96, height = 30;
        juce::String text (TRANS("Room Settings"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 615, y = 33, width = 163, height = 30;
        juce::String text (TRANS("Room View"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 335, y = 473, width = 480, height = 40;
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
        int x = 23, y = 265, width = 145, height = 30;
        juce::String text (TRANS("Channel Order:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 23, y = 289, width = 145, height = 30;
        juce::String text (TRANS("Normalisation:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 23, y = 241, width = 67, height = 30;
        juce::String text (TRANS("Order: "));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 95, y = 457, width = 196, height = 32;
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
        int x = 92, y = 1, width = 148, height = 32;
        juce::String text (TRANS("AmbiRoomSim"));
        juce::Colour fillColour = juce::Colour (0xffffda2b);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 714, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 15, y = 593, width = 714, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 356;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 871, y = 9, width = 2, height = 356;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 15, y = 121, width = 60, height = 30;
        juce::String text (TRANS("Width"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 87, y = 121, width = 60, height = 30;
        juce::String text (TRANS("Depth"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 159, y = 121, width = 60, height = 30;
        juce::String text (TRANS("Height"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 23, y = 81, width = 121, height = 30;
        juce::String text (TRANS("Max IR length:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 71, y = 217, width = 137, height = 30;
        juce::String text (TRANS("Receiver Settings"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 247, y = 241, width = 233, height = 119;
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
        int x = 303, y = 217, width = 137, height = 30;
        juce::String text (TRANS("Source Settings"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		205, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(ambi_roomsim_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(ambi_roomsim_getNumSources(hAmbi)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(ambi_roomsim_getNSHrequired(hAmbi)) + TRANS(")"),
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

    //[/UserResized]
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBsourceDirsPreset.get())
    {
        //[UserComboBoxCode_CBsourceDirsPreset] -- add your combo box handling code here..
        assert(0); // remove
        refreshPanViewWindow = true;
        //[/UserComboBoxCode_CBsourceDirsPreset]
    }
    else if (comboBoxThatHasChanged == CBoutputFormat.get())
    {
        //[UserComboBoxCode_CBoutputFormat] -- add your combo box handling code here..
        ambi_roomsim_setChOrder(hAmbi, CBoutputFormat->getSelectedId());
        //[/UserComboBoxCode_CBoutputFormat]
    }
    else if (comboBoxThatHasChanged == CBnormalisation.get())
    {
        //[UserComboBoxCode_CBnormalisation] -- add your combo box handling code here..
        ambi_roomsim_setNormType(hAmbi, CBnormalisation->getSelectedId());
        //[/UserComboBoxCode_CBnormalisation]
    }
    else if (comboBoxThatHasChanged == CBorder.get())
    {
        //[UserComboBoxCode_CBorder] -- add your combo box handling code here..
        ambi_roomsim_setOutputOrder(hAmbi, CBorder->getSelectedId());
        //[/UserComboBoxCode_CBorder]
    }
    else if (comboBoxThatHasChanged == CBsourceDirsPreset2.get())
    {
        //[UserComboBoxCode_CBsourceDirsPreset2] -- add your combo box handling code here..
        //[/UserComboBoxCode_CBsourceDirsPreset2]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == SL_num_sources.get())
    {
        //[UserSliderCode_SL_num_sources] -- add your slider handling code here..
        ambi_roomsim_setNumSources(hAmbi, (int)SL_num_sources->getValue());
        refreshPanViewWindow = true;
        //[/UserSliderCode_SL_num_sources]
    }
    else if (sliderThatWasMoved == s_roomWidth.get())
    {
        //[UserSliderCode_s_roomWidth] -- add your slider handling code here..
        //[/UserSliderCode_s_roomWidth]
    }
    else if (sliderThatWasMoved == s_roomDepth.get())
    {
        //[UserSliderCode_s_roomDepth] -- add your slider handling code here..
        //[/UserSliderCode_s_roomDepth]
    }
    else if (sliderThatWasMoved == s_roomHeight.get())
    {
        //[UserSliderCode_s_roomHeight] -- add your slider handling code here..
        //[/UserSliderCode_s_roomHeight]
    }
    else if (sliderThatWasMoved == SL_num_sources2.get())
    {
        //[UserSliderCode_SL_num_sources2] -- add your slider handling code here..
        //[/UserSliderCode_SL_num_sources2]
    }
    else if (sliderThatWasMoved == SL_num_sources3.get())
    {
        //[UserSliderCode_SL_num_sources3] -- add your slider handling code here..
        //[/UserSliderCode_SL_num_sources3]
    }
    else if (sliderThatWasMoved == test_x.get())
    {
        //[UserSliderCode_test_x] -- add your slider handling code here..
        ambi_roomsim_setSourceX(hAmbi, 0, test_x->getValue());
        //[/UserSliderCode_test_x]
    }
    else if (sliderThatWasMoved == test_y.get())
    {
        //[UserSliderCode_test_y] -- add your slider handling code here..
        ambi_roomsim_setSourceY(hAmbi, 0, test_y->getValue());
        //[/UserSliderCode_test_y]
    }
    else if (sliderThatWasMoved == test_z.get())
    {
        //[UserSliderCode_test_z] -- add your slider handling code here..
        ambi_roomsim_setSourceZ(hAmbi, 0, test_z->getValue());
        //[/UserSliderCode_test_z]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    sourceCoordsView_handle->setNCH(ambi_roomsim_getNumSources(hAmbi));
    if(SL_num_sources->getValue()!=ambi_roomsim_getNumSources(hAmbi))
        SL_num_sources->setValue(ambi_roomsim_getNumSources(hAmbi),dontSendNotification);
    if(CBoutputFormat->getSelectedId()!=ambi_roomsim_getChOrder(hAmbi))
        CBoutputFormat->setSelectedId(ambi_roomsim_getChOrder(hAmbi), dontSendNotification);
    if(CBnormalisation->getSelectedId()!=ambi_roomsim_getNormType(hAmbi))
        CBnormalisation->setSelectedId(ambi_roomsim_getNormType(hAmbi), dontSendNotification);
    CBoutputFormat->setItemEnabled(CH_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);
    CBnormalisation->setItemEnabled(NORM_FUMA, ambi_roomsim_getOutputOrder(hAmbi)==SH_ORDER_FIRST ? true : false);

    /* refresh pan view */
//    if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) ||
//        sourceCoordsView_handle->getHasASliderChanged() || hVst->getRefreshWindow()){
//        panWindow->refreshPanView();
//        refreshPanViewWindow = false;
//        sourceCoordsView_handle->setHasASliderChange(false);
//        hVst->setRefreshWindow(false);
//    }

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % ambi_roomsim_getFrameSize()) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < ambi_roomsim_getNumSources(hAmbi))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumOutputs() < ambi_roomsim_getNSHrequired(hAmbi))){
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
                 variableInitialisers="AudioProcessorEditor(ownerFilter)," snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="820" initialHeight="600">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 33 816 575" fill="linear: 8 32, 8 232, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="15 241 233 119" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 58 452 158" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <ROUNDRECT pos="1 2 813 31" cornerSize="5.0" fill="linear: 0 32, 656 24, 0=ff041518, 1=ff19313f"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="183 497 196 64" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="23 57 67 30" fill="solid: ffffffff" hasStroke="0" text="Presets: "
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="488 57 312 383" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="15 385 196 194" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="175 33 96 30" fill="solid: ffffffff" hasStroke="0" text="Room Settings"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="615 33 163 30" fill="solid: ffffffff" hasStroke="0" text="Room View"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="335 473 480 40" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="23 265 145 30" fill="solid: ffffffff" hasStroke="0" text="Channel Order:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 289 145 30" fill="solid: ffffffff" hasStroke="0" text="Normalisation:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="23 241 67 30" fill="solid: ffffffff" hasStroke="0" text="Order: "
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="95 457 196 32" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 148 32" fill="solid: ffffda2b" hasStroke="0" text="AmbiRoomSim"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 714 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="15 593 714 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 356" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="871 9 2 356" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <TEXT pos="15 121 60 30" fill="solid: ffffffff" hasStroke="0" text="Width"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="87 121 60 30" fill="solid: ffffffff" hasStroke="0" text="Depth"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="159 121 60 30" fill="solid: ffffffff" hasStroke="0" text="Height"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="23 81 121 30" fill="solid: ffffffff" hasStroke="0" text="Max IR length:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="71 217 137 30" fill="solid: ffffffff" hasStroke="0" text="Receiver Settings"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="247 241 233 119" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="303 217 137 30" fill="solid: ffffffff" hasStroke="0" text="Source Settings"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <COMBOBOX name="new combo box" id="5a2f99f88aa51390" memberName="CBsourceDirsPreset"
            virtualName="" explicitFocusOrder="0" pos="104 64 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="2c2a2b3d0614cc94" memberName="SL_num_sources"
          virtualName="" explicitFocusOrder="0" pos="160 416 48 20" min="1.0"
          max="64.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="63f8ff411606aafd" memberName="CBoutputFormat"
            virtualName="" explicitFocusOrder="0" pos="128 270 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="27f130362a28f1eb" memberName="CBnormalisation"
            virtualName="" explicitFocusOrder="0" pos="128 294 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="56ba0566c2fe39e0" memberName="CBorder"
            virtualName="" explicitFocusOrder="0" pos="128 246 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="863726658f50da67" memberName="s_roomWidth"
          virtualName="" explicitFocusOrder="0" pos="16 144 64 64" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" rotarysliderfill="7fffffff" rotaryslideroutline="66ffffff"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxhighlight="1111ee"
          min="-60.0" max="0.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="5d86e1389643d7b5" memberName="s_roomDepth"
          virtualName="" explicitFocusOrder="0" pos="88 144 64 64" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" rotarysliderfill="7fffffff" rotaryslideroutline="66ffffff"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxhighlight="1111ee"
          min="-60.0" max="0.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="804923c5c2eaafe3" memberName="s_roomHeight"
          virtualName="" explicitFocusOrder="0" pos="160 144 64 64" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" rotarysliderfill="7fffffff" rotaryslideroutline="66ffffff"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxhighlight="1111ee"
          min="-60.0" max="0.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="3fcb7176f49ba3ef" memberName="SL_num_sources2"
          virtualName="" explicitFocusOrder="0" pos="120 96 96 20" min="0.0"
          max="2000.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="2871a203f1a429ca" memberName="SL_num_sources3"
          virtualName="" explicitFocusOrder="0" pos="400 64 48 20" min="1.0"
          max="64.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="4e1dd41648ca8cb7" memberName="CBsourceDirsPreset2"
            virtualName="" explicitFocusOrder="0" pos="389 88 64 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="a7c07aa3e4c43620" memberName="test_x" virtualName=""
          explicitFocusOrder="0" pos="256 240 64 64" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" rotarysliderfill="7fffffff" rotaryslideroutline="66ffffff"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxhighlight="1111ee"
          min="0.0" max="10.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="797f92ebe182926e" memberName="test_y" virtualName=""
          explicitFocusOrder="0" pos="328 240 64 64" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" rotarysliderfill="7fffffff" rotaryslideroutline="66ffffff"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxhighlight="1111ee"
          min="0.0" max="10.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="3af7dcfcaa3bc30b" memberName="test_z" virtualName=""
          explicitFocusOrder="0" pos="400 240 64 64" bkgcol="ff5c5d5e"
          trackcol="ff315b6d" rotarysliderfill="7fffffff" rotaryslideroutline="66ffffff"
          textboxtext="ffffffff" textboxbkgd="ffffff" textboxhighlight="1111ee"
          min="0.0" max="10.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

