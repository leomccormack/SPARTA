/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

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

    label_hostBlockSize.reset (new juce::Label ("new label",
                                                juce::String()));
    addAndMakeVisible (label_hostBlockSize.get());
    label_hostBlockSize->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_hostBlockSize->setJustificationType (juce::Justification::centredLeft);
    label_hostBlockSize->setEditable (false, false, false);
    label_hostBlockSize->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_hostBlockSize->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_hostBlockSize->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_hostBlockSize->setBounds (224, 184, 60, 20);

    label_filterLength.reset (new juce::Label ("new label",
                                               juce::String()));
    addAndMakeVisible (label_filterLength.get());
    label_filterLength->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_filterLength->setJustificationType (juce::Justification::centredLeft);
    label_filterLength->setEditable (false, false, false);
    label_filterLength->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_filterLength->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_filterLength->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_filterLength->setBounds (224, 256, 60, 20);

    label_hostfs.reset (new juce::Label ("new label",
                                         juce::String()));
    addAndMakeVisible (label_hostfs.get());
    label_hostfs->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_hostfs->setJustificationType (juce::Justification::centredLeft);
    label_hostfs->setEditable (false, false, false);
    label_hostfs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_hostfs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_hostfs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_hostfs->setBounds (224, 304, 60, 20);

    label_filterfs.reset (new juce::Label ("new label",
                                           juce::String()));
    addAndMakeVisible (label_filterfs.get());
    label_filterfs->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_filterfs->setJustificationType (juce::Justification::centredLeft);
    label_filterfs->setEditable (false, false, false);
    label_filterfs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_filterfs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_filterfs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_filterfs->setBounds (224, 280, 60, 20);

    SL_num_inputs.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_inputs.get());
    SL_num_inputs->setRange (1, 64, 1);
    SL_num_inputs->setSliderStyle (juce::Slider::LinearBarVertical);
    SL_num_inputs->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_num_inputs->addListener (this);

    SL_num_inputs->setBounds (240, 64, 48, 20);

    label_NOutputs.reset (new juce::Label ("new label",
                                           juce::String()));
    addAndMakeVisible (label_NOutputs.get());
    label_NOutputs->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_NOutputs->setJustificationType (juce::Justification::centredLeft);
    label_NOutputs->setEditable (false, false, false);
    label_NOutputs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_NOutputs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_NOutputs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_NOutputs->setBounds (224, 208, 60, 20);

    label_nIRpositions.reset (new juce::Label ("new label",
                                               juce::String()));
    addAndMakeVisible (label_nIRpositions.get());
    label_nIRpositions->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_nIRpositions->setJustificationType (juce::Justification::centredLeft);
    label_nIRpositions->setEditable (false, false, false);
    label_nIRpositions->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_nIRpositions->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_nIRpositions->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_nIRpositions->setBounds (224, 232, 60, 20);

    SL_source_y.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_source_y.get());
    SL_source_y->setRange (0, 1, 0.001);
    SL_source_y->setSliderStyle (juce::Slider::LinearBarVertical);
    SL_source_y->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_source_y->addListener (this);

    SL_source_y->setBounds (176, 408, 48, 20);

    SL_source_z.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_source_z.get());
    SL_source_z->setRange (0, 1, 0.001);
    SL_source_z->setSliderStyle (juce::Slider::LinearBarVertical);
    SL_source_z->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_source_z->addListener (this);

    SL_source_z->setBounds (232, 408, 48, 20);

    SL_source_x.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_source_x.get());
    SL_source_x->setRange (0, 1, 0.001);
    SL_source_x->setSliderStyle (juce::Slider::LinearBarVertical);
    SL_source_x->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_source_x->addListener (this);

    SL_source_x->setBounds (120, 408, 48, 20);

    SL_receiver_x.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_receiver_x.get());
    SL_receiver_x->setRange (0, 1, 0.001);
    SL_receiver_x->setSliderStyle (juce::Slider::LinearBarVertical);
    SL_receiver_x->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_receiver_x->addListener (this);

    SL_receiver_x->setBounds (120, 432, 48, 20);

    SL_receiver_y.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_receiver_y.get());
    SL_receiver_y->setRange (0, 1, 0.001);
    SL_receiver_y->setSliderStyle (juce::Slider::LinearBarVertical);
    SL_receiver_y->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_receiver_y->addListener (this);

    SL_receiver_y->setBounds (176, 432, 48, 20);

    SL_receiver_z.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_receiver_z.get());
    SL_receiver_z->setRange (0, 1, 0.001);
    SL_receiver_z->setSliderStyle (juce::Slider::LinearBarVertical);
    SL_receiver_z->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_receiver_z->addListener (this);

    SL_receiver_z->setBounds (232, 432, 48, 20);

    label_receiverIdx.reset (new juce::Label ("new label",
                                              juce::String()));
    addAndMakeVisible (label_receiverIdx.get());
    label_receiverIdx->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_receiverIdx->setJustificationType (juce::Justification::centredLeft);
    label_receiverIdx->setEditable (false, false, false);
    label_receiverIdx->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_receiverIdx->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_receiverIdx->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_receiverIdx->setBounds (176, 456, 48, 20);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (780, 500);


    //[Constructor] You can add your own custom stuff here..
	hVst = ownerFilter;
    hTVC = hVst->getFXHandle();

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_num_inputs->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_inputs->setSliderSnapsToMousePosition(false);
    SL_num_inputs->setEnabled(false); /* One source allowed for now*/

    SL_source_x->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_source_x->setSliderSnapsToMousePosition(false);
    SL_source_y->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_source_y->setSliderSnapsToMousePosition(false);
    SL_source_z->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_source_z->setSliderSnapsToMousePosition(false);
    /*Source position not implemented yet*/
    SL_source_x->setEnabled(false);
    SL_source_y->setEnabled(false);
    SL_source_z->setEnabled(false);

    SL_receiver_x->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_receiver_x->setSliderSnapsToMousePosition(false);
    SL_receiver_y->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_receiver_y->setSliderSnapsToMousePosition(false);
    SL_receiver_z->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_receiver_z->setSliderSnapsToMousePosition(false);


    /* file loader */
    fileComp.reset (new FilenameComponent("fileComp", {},
                                          true, false, false,
                                          "*.sofa;*.nc;", {},
                                          "Load SOFA File"));
    addAndMakeVisible (fileComp.get());
    fileComp->addListener(this);
    fileComp->setBounds (16, 90, 272, 20);
    if(strcmp(tvconv_getSofaFilePath(hTVC), "no_file") != 0){
        fileComp->setCurrentFile(String(tvconv_getSofaFilePath(hTVC)), true, dontSendNotification);
        refreshCoords();
    } else {
        SL_receiver_x->setEnabled(false);
        SL_receiver_y->setEnabled(false);
        SL_receiver_z->setEnabled(false);
    }


	/* fetch current configuration */
    SL_num_inputs->setValue(tvconv_getNumInputChannels(hTVC), dontSendNotification);

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 240, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("Time-varying impulse response convolver. A set of IRs can be loaded from a sofa file, where IRs have to be assigned with different ListenerPositions. The position of the receiver can be varied during playback using the parameter sliders. The convolver finds the nearest neighbour IR of the selected position. It applies overlap-add partitioned convolution and cross-fades between previous and current positions to produce smooth transitions. Each IR can have up to 64 channels (7th order Ambisonics). Single fixed SourcePosition is assumed and only mono input is supported.\n"));

    /* Specify screen refresh rate */
    startTimer(40); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label_hostBlockSize = nullptr;
    label_filterLength = nullptr;
    label_hostfs = nullptr;
    label_filterfs = nullptr;
    SL_num_inputs = nullptr;
    label_NOutputs = nullptr;
    label_nIRpositions = nullptr;
    SL_source_y = nullptr;
    SL_source_z = nullptr;
    SL_source_x = nullptr;
    SL_receiver_x = nullptr;
    SL_receiver_y = nullptr;
    SL_receiver_z = nullptr;
    label_receiverIdx = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    setLookAndFeel(nullptr);
    fileComp = nullptr;
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::white);

    {
        int x = 2, y = 28, width = 780, height = 290;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 2.0f + x,
                                             32.0f - 28.0f + y,
                                             fillColour2,
                                             8.0f - 2.0f + x,
                                             112.0f - 28.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 312, width = 780, height = 186;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             496.0f - 312.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             416.0f - 312.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 10, y = 60, width = 286, height = 76;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        float x = 1.0f, y = 2.0f, width = 778.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             528.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 10, y = 172, width = 288, height = 164;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
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
        juce::String text (TRANS("TimeVarConvolver"));
        juce::Colour fillColour = juce::Colour (0xffe9ff00);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 780, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 500;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 778, y = 0, width = 2, height = 500;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 498, width = 780, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 18, y = 180, width = 115, height = 30;
        juce::String text (TRANS("Host Block Size:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 252, width = 200, height = 30;
        juce::String text (TRANS("IR Length (s):"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 276, width = 128, height = 30;
        juce::String text (TRANS("Filter Samplerate:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 300, width = 144, height = 30;
        juce::String text (TRANS("Host Samplerate:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 60, width = 224, height = 30;
        juce::String text (TRANS("Number of Sources:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 204, width = 120, height = 31;
        juce::String text (TRANS("N# IR channels:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 30, width = 270, height = 31;
        juce::String text (TRANS("IR dataset"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 18, y = 140, width = 270, height = 31;
        juce::String text (TRANS("Loaded Dataset Info"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 18, y = 228, width = 200, height = 30;
        juce::String text (TRANS("N# IR positions:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 312, y = 60, width = 458, height = 424;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 314, y = 30, width = 456, height = 31;
        juce::String text (TRANS("Coordinate View"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 10, y = 372, width = 288, height = 112;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 18, y = 340, width = 270, height = 31;
        juce::String text (TRANS("Coordinates"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 18, y = 404, width = 134, height = 30;
        juce::String text (TRANS("Source:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 428, width = 142, height = 30;
        juce::String text (TRANS("Listener:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 120, y = 380, width = 160, height = 30;
        juce::String text (TRANS("x           y           z"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 18, y = 452, width = 142, height = 30;
        juce::String text (TRANS("Listener Index:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..

    /* display version/date built */
	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		250, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_sampleRate_missmatch:
            g.drawText(TRANS("Host samplerate does not match filter samplerate"),
                       getBounds().getWidth()-250, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_nInputs_more_than_64:
            g.drawText(TRANS("Number of input channels exceeds VST maximum"),
                       getBounds().getWidth()-250, 5, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_nOutputs_more_than_64:
            g.drawText(TRANS("Number of output channels exceeds VST maximum"),
                       getBounds().getWidth()-250, 5, 530, 11,
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

	repaint();
    //[/UserResized]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == SL_num_inputs.get())
    {
        //[UserSliderCode_SL_num_inputs] -- add your slider handling code here..
        //[/UserSliderCode_SL_num_inputs]
    }
    else if (sliderThatWasMoved == SL_source_y.get())
    {
        //[UserSliderCode_SL_source_y] -- add your slider handling code here..
        //[/UserSliderCode_SL_source_y]
    }
    else if (sliderThatWasMoved == SL_source_z.get())
    {
        //[UserSliderCode_SL_source_z] -- add your slider handling code here..
        //[/UserSliderCode_SL_source_z]
    }
    else if (sliderThatWasMoved == SL_source_x.get())
    {
        //[UserSliderCode_SL_source_x] -- add your slider handling code here..
        //[/UserSliderCode_SL_source_x]
    }
    else if (sliderThatWasMoved == SL_receiver_x.get())
    {
        //[UserSliderCode_SL_receiver_x] -- add your slider handling code here..
        tvconv_setPosition(hTVC, 0, SL_receiver_x->getValue());
        //[/UserSliderCode_SL_receiver_x]
    }
    else if (sliderThatWasMoved == SL_receiver_y.get())
    {
        //[UserSliderCode_SL_receiver_y] -- add your slider handling code here..
        tvconv_setPosition(hTVC, 1, SL_receiver_y->getValue());
        //[/UserSliderCode_SL_receiver_y]
    }
    else if (sliderThatWasMoved == SL_receiver_z.get())
    {
        //[UserSliderCode_SL_receiver_z] -- add your slider handling code here..
        tvconv_setPosition(hTVC, 2, SL_receiver_z->getValue());
        //[/UserSliderCode_SL_receiver_z]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    label_hostBlockSize->setText(String(tvconv_getHostBlockSize(hTVC)), dontSendNotification);
    label_NOutputs->setText(String(tvconv_getNIRs(hTVC)), dontSendNotification);
    label_nIRpositions->setText(String(tvconv_getNPositions(hTVC)), dontSendNotification);
    label_filterLength->setText(String((float)tvconv_getIRLength(hTVC)/MAX((float)tvconv_getIRFs(hTVC),1/*avoid nan*/)), dontSendNotification);
    label_hostfs->setText(String(tvconv_getHostFs(hTVC)), dontSendNotification);
    label_filterfs->setText(String(tvconv_getIRFs(hTVC)), dontSendNotification);
    label_receiverIdx->setText(String(tvconv_getPositionIdx(hTVC)), dontSendNotification);

    SL_receiver_x->setValue(tvconv_getPosition(hTVC, 0));
    SL_receiver_y->setValue(tvconv_getPosition(hTVC, 1));
    SL_receiver_z->setValue(tvconv_getPosition(hTVC, 2));

    /* display warning message, if needed */
    if((tvconv_getNIRs(hTVC) != 0) && (tvconv_getHostFs(hTVC)!=tvconv_getIRFs(hTVC))){
        currentWarning = k_warning_sampleRate_missmatch;
        repaint(0,0,getWidth(),32);
    }
    else if(tvconv_getNumInputChannels(hTVC)>MAX_NUM_CHANNELS){
        currentWarning = k_warning_nInputs_more_than_64;
        repaint(0,0,getWidth(),32);
    }
    else if(tvconv_getNumOutputChannels(hTVC)>MAX_NUM_CHANNELS){
        currentWarning = k_warning_nOutputs_more_than_64;
        repaint(0,0,getWidth(),32);
    }
    else{
        currentWarning = k_warning_none;
        repaint(0,0,getWidth(),32);
    }
}

void PluginEditor::refreshCoords()
{
    if (tvconv_getMaxDimension(hTVC, 0) > tvconv_getMinDimension(hTVC, 0)){
        SL_receiver_x->setEnabled(true);
        SL_receiver_x->setRange(tvconv_getMinDimension(hTVC, 0),
                                tvconv_getMaxDimension(hTVC, 0),
                                0.001);
    } else {
        SL_receiver_x->setEnabled(false);
    }
    SL_receiver_x->setValue(tvconv_getPosition(hTVC, 0));
    if (tvconv_getMaxDimension(hTVC, 1) > tvconv_getMinDimension(hTVC, 1)){
        SL_receiver_y->setEnabled(true);
        SL_receiver_y->setRange(tvconv_getMinDimension(hTVC, 1),
                                tvconv_getMaxDimension(hTVC, 1),
                                0.001);
    } else {
        SL_receiver_y->setEnabled(false);
    }
    SL_receiver_y->setValue(tvconv_getPosition(hTVC, 1));
    if (tvconv_getMaxDimension(hTVC, 2) > tvconv_getMinDimension(hTVC, 2)){
        SL_receiver_z->setEnabled(true);
        SL_receiver_z->setRange(tvconv_getMinDimension(hTVC, 2),
                                tvconv_getMaxDimension(hTVC, 2),
                                0.001);
    } else {
        SL_receiver_z->setEnabled(false);
    }
    SL_receiver_z->setValue(tvconv_getPosition(hTVC, 2));

    SL_source_x->setRange(tvconv_getSourcePosition(hTVC, 0), tvconv_getSourcePosition(hTVC, 0)+1, 0.1);
    SL_source_x->setValue(tvconv_getSourcePosition(hTVC, 0));
    SL_source_y->setRange(tvconv_getSourcePosition(hTVC, 1), tvconv_getSourcePosition(hTVC, 1)+1, 0.1);
    SL_source_y->setValue(tvconv_getSourcePosition(hTVC, 1));
    SL_source_z->setRange(tvconv_getSourcePosition(hTVC, 2), tvconv_getSourcePosition(hTVC, 2)+1, 0.1);
    SL_source_z->setValue(tvconv_getSourcePosition(hTVC, 2));
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public AudioProcessorEditor, public Timer, private FilenameComponentListener"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="780" initialHeight="500">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="2 28 780 290" fill="linear: 8 32, 8 112, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="0 312 780 186" fill="linear: 8 496, 8 416, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="10 60 286 76" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <ROUNDRECT pos="1 2 778 31" cornerSize="5.0" fill="linear: 0 32, 528 32, 0=ff041518, 1=ff19313f"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="10 172 288 164" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 148 32" fill="solid: ffe9ff00" hasStroke="0" text="TimeVarConvolver"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 780 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 500" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="778 0 2 500" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 498 780 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <TEXT pos="18 180 115 30" fill="solid: ffffffff" hasStroke="0" text="Host Block Size:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="18 252 200 30" fill="solid: ffffffff" hasStroke="0" text="IR Length (s):"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="18 276 128 30" fill="solid: ffffffff" hasStroke="0" text="Filter Samplerate:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="18 300 144 30" fill="solid: ffffffff" hasStroke="0" text="Host Samplerate:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="18 60 224 30" fill="solid: ffffffff" hasStroke="0" text="Number of Sources:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="18 204 120 31" fill="solid: ffffffff" hasStroke="0" text="N# IR channels:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="18 30 270 31" fill="solid: ffffffff" hasStroke="0" text="IR dataset"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="18 140 270 31" fill="solid: ffffffff" hasStroke="0" text="Loaded Dataset Info"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="18 228 200 30" fill="solid: ffffffff" hasStroke="0" text="N# IR positions:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="312 60 458 424" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="314 30 456 31" fill="solid: ffffffff" hasStroke="0" text="Coordinate View"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="10 372 288 112" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="18 340 270 31" fill="solid: ffffffff" hasStroke="0" text="Coordinates"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="18 404 134 30" fill="solid: ffffffff" hasStroke="0" text="Source:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="18 428 142 30" fill="solid: ffffffff" hasStroke="0" text="Listener:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="120 380 160 30" fill="solid: ffffffff" hasStroke="0" text="x           y           z"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="18 452 142 30" fill="solid: ffffffff" hasStroke="0" text="Listener Index:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <LABEL name="new label" id="167c5975ece5bfaa" memberName="label_hostBlockSize"
         virtualName="" explicitFocusOrder="0" pos="224 184 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="7d9ebaead925d1e6" memberName="label_filterLength"
         virtualName="" explicitFocusOrder="0" pos="224 256 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b5990c279ece4f98" memberName="label_hostfs"
         virtualName="" explicitFocusOrder="0" pos="224 304 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5ca688f8365be60e" memberName="label_filterfs"
         virtualName="" explicitFocusOrder="0" pos="224 280 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="2c2a2b3d0614cc94" memberName="SL_num_inputs"
          virtualName="" explicitFocusOrder="0" pos="240 64 48 20" min="1.0"
          max="64.0" int="1.0" style="LinearBarVertical" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="55" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="fbe948204f97884b" memberName="label_NOutputs"
         virtualName="" explicitFocusOrder="0" pos="224 208 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b7d47df871a4b9f8" memberName="label_nIRpositions"
         virtualName="" explicitFocusOrder="0" pos="224 232 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="91838e1f378b04d5" memberName="SL_source_y"
          virtualName="" explicitFocusOrder="0" pos="176 408 48 20" min="0.0"
          max="1.0" int="0.001" style="LinearBarVertical" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="55" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="4f9b7b9e0e5eb928" memberName="SL_source_z"
          virtualName="" explicitFocusOrder="0" pos="232 408 48 20" min="0.0"
          max="1.0" int="0.001" style="LinearBarVertical" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="55" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="15013dd0f37db52c" memberName="SL_source_x"
          virtualName="" explicitFocusOrder="0" pos="120 408 48 20" min="0.0"
          max="1.0" int="0.001" style="LinearBarVertical" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="55" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="572be8cab2789e9d" memberName="SL_receiver_x"
          virtualName="" explicitFocusOrder="0" pos="120 432 48 20" min="0.0"
          max="1.0" int="0.001" style="LinearBarVertical" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="55" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="2c60d2500e81284e" memberName="SL_receiver_y"
          virtualName="" explicitFocusOrder="0" pos="176 432 48 20" min="0.0"
          max="1.0" int="0.001" style="LinearBarVertical" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="55" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="a60197fb8a061339" memberName="SL_receiver_z"
          virtualName="" explicitFocusOrder="0" pos="232 432 48 20" min="0.0"
          max="1.0" int="0.001" style="LinearBarVertical" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="55" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="d173a8591e895adf" memberName="label_receiverIdx"
         virtualName="" explicitFocusOrder="0" pos="176 456 48 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

