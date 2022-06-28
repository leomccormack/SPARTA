/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.6

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

    label_hostBlockSize->setBounds (136, 55, 60, 20);

    label_hostfs.reset (new juce::Label ("new label",
                                         juce::String()));
    addAndMakeVisible (label_hostfs.get());
    label_hostfs->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_hostfs->setJustificationType (juce::Justification::centredLeft);
    label_hostfs->setEditable (false, false, false);
    label_hostfs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_hostfs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_hostfs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_hostfs->setBounds (333, 55, 60, 20);

    te_oscport.reset (new juce::TextEditor ("new text editor"));
    addAndMakeVisible (te_oscport.get());
    te_oscport->setMultiLine (false);
    te_oscport->setReturnKeyStartsNewLine (false);
    te_oscport->setReadOnly (false);
    te_oscport->setScrollbarsShown (true);
    te_oscport->setCaretVisible (true);
    te_oscport->setPopupMenuEnabled (true);
    te_oscport->setColour (juce::TextEditor::textColourId, juce::Colours::white);
    te_oscport->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00ffffff));
    te_oscport->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x6c838080));
    te_oscport->setText (TRANS("9000"));

    te_oscport->setBounds (160, 322, 42, 22);

    te_myip.reset (new juce::TextEditor ("new text editor"));
    addAndMakeVisible (te_myip.get());
    te_myip->setMultiLine (false);
    te_myip->setReturnKeyStartsNewLine (false);
    te_myip->setReadOnly (false);
    te_myip->setScrollbarsShown (true);
    te_myip->setCaretVisible (true);
    te_myip->setPopupMenuEnabled (true);
    te_myip->setColour (juce::TextEditor::textColourId, juce::Colours::white);
    te_myip->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00ffffff));
    te_myip->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x6c838080));
    te_myip->setText (TRANS("127.0.0.1"));

    te_myip->setBounds (160, 220, 110, 22);

    te_serverip.reset (new juce::TextEditor ("new text editor"));
    addAndMakeVisible (te_serverip.get());
    te_serverip->setMultiLine (false);
    te_serverip->setReturnKeyStartsNewLine (false);
    te_serverip->setReadOnly (false);
    te_serverip->setScrollbarsShown (true);
    te_serverip->setCaretVisible (true);
    te_serverip->setPopupMenuEnabled (true);
    te_serverip->setColour (juce::TextEditor::textColourId, juce::Colours::white);
    te_serverip->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00ffffff));
    te_serverip->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x6c838080));
    te_serverip->setText (TRANS("127.0.0.1"));

    te_serverip->setBounds (160, 244, 110, 22);

    bt_connect.reset (new juce::TextButton ("connect"));
    addAndMakeVisible (bt_connect.get());
    bt_connect->addListener (this);

    bt_connect->setBounds (280, 268, 110, 22);

    te_connectionlabel.reset (new juce::Label ("new label",
                                               juce::String()));
    addAndMakeVisible (te_connectionlabel.get());
    te_connectionlabel->setFont (juce::Font (14.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    te_connectionlabel->setJustificationType (juce::Justification::topLeft);
    te_connectionlabel->setEditable (false, false, false);
    te_connectionlabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    te_connectionlabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    te_connectionlabel->setBounds (280, 222, 110, 39);

    tb_unicast.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (tb_unicast.get());
    tb_unicast->setButtonText (TRANS("Enabled"));
    tb_unicast->addListener (this);

    tb_unicast->setBounds (160, 268, 110, 22);

    label_x.reset (new juce::Label ("new label",
                                    juce::String()));
    addAndMakeVisible (label_x.get());
    label_x->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_x->setJustificationType (juce::Justification::centredLeft);
    label_x->setEditable (false, false, false);
    label_x->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_x->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_x->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_x->setBounds (140, 114, 48, 20);

    label_y.reset (new juce::Label ("new label",
                                    juce::String()));
    addAndMakeVisible (label_y.get());
    label_y->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_y->setJustificationType (juce::Justification::centredLeft);
    label_y->setEditable (false, false, false);
    label_y->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_y->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_y->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_y->setBounds (196, 114, 48, 20);

    label_z.reset (new juce::Label ("new label",
                                    juce::String()));
    addAndMakeVisible (label_z.get());
    label_z->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_z->setJustificationType (juce::Justification::centredLeft);
    label_z->setEditable (false, false, false);
    label_z->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_z->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_z->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_z->setBounds (252, 114, 48, 20);

    label_yaw.reset (new juce::Label ("new label",
                                      juce::String()));
    addAndMakeVisible (label_yaw.get());
    label_yaw->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_yaw->setJustificationType (juce::Justification::centredLeft);
    label_yaw->setEditable (false, false, false);
    label_yaw->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_yaw->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_yaw->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_yaw->setBounds (140, 160, 48, 20);

    label_pitch.reset (new juce::Label ("new label",
                                        juce::String()));
    addAndMakeVisible (label_pitch.get());
    label_pitch->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_pitch->setJustificationType (juce::Justification::centredLeft);
    label_pitch->setEditable (false, false, false);
    label_pitch->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_pitch->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_pitch->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_pitch->setBounds (196, 160, 48, 20);

    label_roll.reset (new juce::Label ("new label",
                                       juce::String()));
    addAndMakeVisible (label_roll.get());
    label_roll->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_roll->setJustificationType (juce::Justification::centredLeft);
    label_roll->setEditable (false, false, false);
    label_roll->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_roll->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_roll->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_roll->setBounds (252, 160, 48, 20);

    tb_unmute.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (tb_unmute.get());
    tb_unmute->setButtonText (TRANS("Unmute (DANGEROUS! MAKE SURE THIS IS NOT ROUTED TO SPEAKERS)"));
    tb_unmute->addListener (this);

    tb_unmute->setBounds (7, 454, 393, 24);

    juce__comboBox.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (juce__comboBox.get());
    juce__comboBox->setEditableText (false);
    juce__comboBox->setJustificationType (juce::Justification::centredLeft);
    juce__comboBox->setTextWhenNothingSelected (juce::String());
    juce__comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    juce__comboBox->addListener (this);

    juce__comboBox->setBounds (408, 192, 150, 24);

    cb_sourceMode.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (cb_sourceMode.get());
    cb_sourceMode->setEditableText (false);
    cb_sourceMode->setJustificationType (juce::Justification::centredLeft);
    cb_sourceMode->setTextWhenNothingSelected (juce::String());
    cb_sourceMode->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cb_sourceMode->addItem (TRANS("NatNet"), 1);
    cb_sourceMode->addItem (TRANS("OSC"), 2);
    cb_sourceMode->addItem (TRANS("MIDI"), 3);
    cb_sourceMode->addListener (this);

    cb_sourceMode->setBounds (318, 135, 72, 24);

    te_midiCcCoarse.reset (new juce::TextEditor ("new text editor"));
    addAndMakeVisible (te_midiCcCoarse.get());
    te_midiCcCoarse->setMultiLine (false);
    te_midiCcCoarse->setReturnKeyStartsNewLine (false);
    te_midiCcCoarse->setReadOnly (false);
    te_midiCcCoarse->setScrollbarsShown (true);
    te_midiCcCoarse->setCaretVisible (true);
    te_midiCcCoarse->setPopupMenuEnabled (true);
    te_midiCcCoarse->setColour (juce::TextEditor::textColourId, juce::Colours::white);
    te_midiCcCoarse->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00ffffff));
    te_midiCcCoarse->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x6c838080));
    te_midiCcCoarse->setText (TRANS("16"));

    te_midiCcCoarse->setBounds (128, 402, 42, 22);

    te_midiCcFine.reset (new juce::TextEditor ("new text editor"));
    addAndMakeVisible (te_midiCcFine.get());
    te_midiCcFine->setMultiLine (false);
    te_midiCcFine->setReturnKeyStartsNewLine (false);
    te_midiCcFine->setReadOnly (false);
    te_midiCcFine->setScrollbarsShown (true);
    te_midiCcFine->setCaretVisible (true);
    te_midiCcFine->setPopupMenuEnabled (true);
    te_midiCcFine->setColour (juce::TextEditor::textColourId, juce::Colours::white);
    te_midiCcFine->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00ffffff));
    te_midiCcFine->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x6c838080));
    te_midiCcFine->setText (TRANS("48"));

    te_midiCcFine->setBounds (128, 426, 42, 22);

    tb_midiQuaternions.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (tb_midiQuaternions.get());
    tb_midiQuaternions->setButtonText (TRANS("Yes"));
    tb_midiQuaternions->addListener (this);

    tb_midiQuaternions->setBounds (319, 426, 72, 22);

    te_midiChannel.reset (new juce::TextEditor ("new text editor"));
    addAndMakeVisible (te_midiChannel.get());
    te_midiChannel->setMultiLine (false);
    te_midiChannel->setReturnKeyStartsNewLine (false);
    te_midiChannel->setReadOnly (false);
    te_midiChannel->setScrollbarsShown (true);
    te_midiChannel->setCaretVisible (true);
    te_midiChannel->setPopupMenuEnabled (true);
    te_midiChannel->setColour (juce::TextEditor::textColourId, juce::Colours::white);
    te_midiChannel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00ffffff));
    te_midiChannel->setColour (juce::TextEditor::outlineColourId, juce::Colour (0x6c838080));
    te_midiChannel->setText (TRANS("1"));

    te_midiChannel->setBounds (320, 402, 42, 22);

    cb_midiDevice.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (cb_midiDevice.get());
    cb_midiDevice->setEditableText (false);
    cb_midiDevice->setJustificationType (juce::Justification::centredLeft);
    cb_midiDevice->setTextWhenNothingSelected (juce::String());
    cb_midiDevice->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cb_midiDevice->addListener (this);

    cb_midiDevice->setBounds (128, 379, 192, 22);

    bt_midiRescan.reset (new juce::TextButton ("rescan"));
    addAndMakeVisible (bt_midiRescan.get());
    bt_midiRescan->addListener (this);

    bt_midiRescan->setBounds (325, 379, 68, 22);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (410, 482);


    //[Constructor] You can add your own custom stuff here..
	hVst = ownerFilter;

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

	/* fetch current configuration */

    te_myip->setText(hVst->headtrackerReceiver.natNetReceiver.myAddress);
    te_serverip->setText(hVst->headtrackerReceiver.natNetReceiver.serverAddress);
    tb_unicast->setToggleState(hVst->headtrackerReceiver.natNetReceiver.connectionType == ConnectionType::ConnectionType_Unicast, false);
    te_midiCcCoarse->setText(String(hVst->headtrackerReceiver.midiReceiver.firstCcNumCoarse));
    te_midiCcFine->setText(String(hVst->headtrackerReceiver.midiReceiver.firstCcNumFine));
    te_midiChannel->setText(String(hVst->headtrackerReceiver.midiReceiver.channel));
    tb_midiQuaternions->setToggleState(hVst->headtrackerReceiver.midiReceiver.receiveQuaternions, false);
    te_oscport->setText(String(hVst->headtrackerReceiver.oscReceiver.port), dontSendNotification);
    cb_sourceMode->setSelectedItemIndex(hVst->headtrackerReceiver.getActiveSource());

    /* tooltips */

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

    te_myip->addListener(this);
    te_serverip->addListener(this);

    te_midiCcCoarse->addListener(this);
    te_midiCcFine->addListener(this);
    te_midiChannel->addListener(this);

    te_oscport->addListener(this);

    refreshMidiDevices();

    /* NatNet */
    originalConnectButtonText = bt_connect->getButtonText();
    natNetConnListener.setCallback([this](const String& message) { natNetconnListenerCallback(message); });
    hVst->headtrackerReceiver.natNetReceiver.addConnListener(&natNetConnListener);

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label_hostBlockSize = nullptr;
    label_hostfs = nullptr;
    te_oscport = nullptr;
    te_myip = nullptr;
    te_serverip = nullptr;
    bt_connect = nullptr;
    te_connectionlabel = nullptr;
    tb_unicast = nullptr;
    label_x = nullptr;
    label_y = nullptr;
    label_z = nullptr;
    label_yaw = nullptr;
    label_pitch = nullptr;
    label_roll = nullptr;
    tb_unmute = nullptr;
    juce__comboBox = nullptr;
    cb_sourceMode = nullptr;
    te_midiCcCoarse = nullptr;
    te_midiCcFine = nullptr;
    tb_midiQuaternions = nullptr;
    te_midiChannel = nullptr;
    cb_midiDevice = nullptr;
    bt_midiRescan = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    setLookAndFeel(nullptr);
    hVst->headtrackerReceiver.natNetReceiver.removeConnListener(&natNetConnListener);
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::white);

    {
        int x = 2, y = 28, width = 408, height = 452;
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
        int x = 10, y = 318, width = 390, height = 32;
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
        int x = 71, y = 190, width = 270, height = 31;
        juce::String text (TRANS("NatNet Client"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 10, y = 84, width = 390, height = 108;
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
        int x = 308, y = 84, width = 92, height = 108;
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
        float x = 1.0f, y = 2.0f, width = 408.0f, height = 31.0f;
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
        int x = 10, y = 45, width = 390, height = 40;
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
        juce::String text (TRANS("TrackerTest"));
        juce::Colour fillColour = juce::Colour (0xffff00f4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 410, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 324;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 408, y = 0, width = 2, height = 480;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 480, width = 410, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 18, y = 50, width = 115, height = 30;
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
        int x = 208, y = 50, width = 144, height = 30;
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
        int x = 18, y = 108, width = 121, height = 30;
        juce::String text (TRANS("Source Position:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 139, y = 86, width = 160, height = 30;
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
        int x = 10, y = 216, width = 390, height = 79;
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
        int x = 18, y = 218, width = 142, height = 26;
        juce::String text (TRANS("IP Address:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 242, width = 142, height = 26;
        juce::String text (TRANS("Server IP Address:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 266, width = 142, height = 26;
        juce::String text (TRANS("Unicast:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 140, y = 133, width = 160, height = 30;
        juce::String text (TRANS("yaw     pitch      roll"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 18, y = 155, width = 121, height = 30;
        juce::String text (TRANS("Source Rotation:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 314, y = 110, width = 80, height = 26;
        juce::String text (TRANS("Source mode"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (11.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 71, y = 293, width = 270, height = 31;
        juce::String text (TRANS("OSC"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 18, y = 320, width = 142, height = 26;
        juce::String text (TRANS("Port:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 71, y = 349, width = 270, height = 31;
        juce::String text (TRANS("MIDI"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 10, y = 374, width = 390, height = 78;
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
        int x = 18, y = 400, width = 102, height = 26;
        juce::String text (TRANS("CC# (coarse):"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 424, width = 102, height = 26;
        juce::String text (TRANS("CC# (fine):"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 210, y = 424, width = 102, height = 26;
        juce::String text (TRANS("Quaternions:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 210, y = 400, width = 102, height = 26;
        juce::String text (TRANS("Channel:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 376, width = 102, height = 26;
        juce::String text (TRANS("Device:"));
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
		200, 16, 530, 11,
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

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == bt_connect.get())
    {
        //[UserButtonCode_bt_connect] -- add your button handler code here..
        // TODO: maybe there's a better way to track this state
        bool connect = bt_connect->getButtonText() == originalConnectButtonText;
        if (connect) {
            String myIp = te_myip->getText();
            String serverIp = te_serverip->getText();
            bool unicast = tb_unicast->getToggleState();
            ConnectionType connType = unicast ? ConnectionType::ConnectionType_Unicast : ConnectionType::ConnectionType_Multicast;

            hVst->headtrackerReceiver.natNetReceiver.myAddress = myIp;
            hVst->headtrackerReceiver.natNetReceiver.serverAddress = serverIp;
            hVst->headtrackerReceiver.natNetReceiver.connectionType = connType;

            hVst->headtrackerReceiver.natNetReceiver.enable();
        } else {
            hVst->headtrackerReceiver.natNetReceiver.disable();
        }

        //[/UserButtonCode_bt_connect]
    }
    else if (buttonThatWasClicked == tb_unicast.get())
    {
        //[UserButtonCode_tb_unicast] -- add your button handler code here..
        //[/UserButtonCode_tb_unicast]
    }
    else if (buttonThatWasClicked == tb_unmute.get())
    {
        //[UserButtonCode_tb_unmute] -- add your button handler code here..
        hVst->setUnmute(tb_unmute->getToggleState());
        //[/UserButtonCode_tb_unmute]
    }
    else if (buttonThatWasClicked == tb_midiQuaternions.get())
    {
        //[UserButtonCode_tb_midiQuaternions] -- add your button handler code here..
        hVst->headtrackerReceiver.midiReceiver.receiveQuaternions = tb_midiQuaternions->getToggleState();
        if (hVst->headtrackerReceiver.getActiveSource() == Source::SOURCE_MIDI) {
            hVst->headtrackerReceiver.enable();
        }
        //[/UserButtonCode_tb_midiQuaternions]
    }
    else if (buttonThatWasClicked == bt_midiRescan.get())
    {
        //[UserButtonCode_bt_midiRescan] -- add your button handler code here..
        refreshMidiDevices();
        //[/UserButtonCode_bt_midiRescan]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == juce__comboBox.get())
    {
        //[UserComboBoxCode_juce__comboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_juce__comboBox]
    }
    else if (comboBoxThatHasChanged == cb_sourceMode.get())
    {
        //[UserComboBoxCode_cb_sourceMode] -- add your combo box handling code here..
        hVst->headtrackerReceiver.setActiveSource(static_cast<HeadtrackerTypes::Source>(cb_sourceMode->getSelectedItemIndex()));
        //[/UserComboBoxCode_cb_sourceMode]
    }
    else if (comboBoxThatHasChanged == cb_midiDevice.get())
    {
        //[UserComboBoxCode_cb_midiDevice] -- add your combo box handling code here..
        hVst->headtrackerReceiver.midiReceiver.inputName = midiInputs[comboBoxThatHasChanged->getSelectedItemIndex()];
        if (hVst->headtrackerReceiver.getActiveSource() == Source::SOURCE_MIDI) {
            hVst->headtrackerReceiver.enable();
        }
        //[/UserComboBoxCode_cb_midiDevice]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void PluginEditor::refreshMidiDevices()
{
    midiInputs = juce::MidiInput::getDevices();
    cb_midiDevice->clear();
    cb_midiDevice->addItemList(midiInputs, 1);
    const int selectedIndex = midiInputs.indexOf(hVst->headtrackerReceiver.midiReceiver.inputName);
    cb_midiDevice->setSelectedItemIndex(selectedIndex >= 0 ? selectedIndex : 0);
}

void PluginEditor::textEditorTextChanged(TextEditor& textEditor) {
    String text = textEditor.getText();
    if (&textEditor == te_midiCcCoarse.get()) {
        int num = text.getIntValue();
        hVst->headtrackerReceiver.midiReceiver.firstCcNumCoarse = num;
        if (hVst->headtrackerReceiver.getActiveSource() == Source::SOURCE_MIDI) {
            hVst->headtrackerReceiver.enable();
        }
    } else if (&textEditor == te_midiCcFine.get()) {
        int num = text.getIntValue();
        hVst->headtrackerReceiver.midiReceiver.firstCcNumFine = num;
        if (hVst->headtrackerReceiver.getActiveSource() == Source::SOURCE_MIDI) {
            hVst->headtrackerReceiver.enable();
        }
    } else if (&textEditor == te_midiChannel.get()) {
        int num = text.getIntValue();
        hVst->headtrackerReceiver.midiReceiver.channel = num;
        if (hVst->headtrackerReceiver.getActiveSource() == Source::SOURCE_MIDI) {
            hVst->headtrackerReceiver.enable();
        }
    } else if (&textEditor == te_oscport.get()) {
        int port = text.getIntValue();
        if (port > 0) {
            hVst->headtrackerReceiver.oscReceiver.port = port;
            if (hVst->headtrackerReceiver.getActiveSource() == Source::SOURCE_OSC) {
                hVst->headtrackerReceiver.enable();
            }
        }
    }

    /*
    te_myip->addListener(this);
    te_serverip->addListener(this);

    te_midiCcCoarse->addListener(this);
    te_midiCcFine->addListener(this);
    te_midiChannel->addListener(this);

    te_oscport->addListener(this);
    */
}

void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */

    label_hostBlockSize->setText(String(hVst->getBlockSize()), dontSendNotification);
    label_hostfs->setText(String(hVst->getSampleRate()), dontSendNotification);

    const int decimals = 3;
    label_x->setText(String(hVst->getX(), decimals), dontSendNotification);
    label_y->setText(String(hVst->getY(), decimals), dontSendNotification);
    label_z->setText(String(hVst->getZ(), decimals), dontSendNotification);
    label_yaw->setText(String(hVst->getYaw(), decimals), dontSendNotification);
    label_pitch->setText(String(hVst->getPitch(), decimals), dontSendNotification);
    label_roll->setText(String(hVst->getRoll(), decimals), dontSendNotification);

    /* check if OSC port has changed */
    if (hVst->headtrackerReceiver.oscReceiver.port != te_oscport->getText().getIntValue())
        hVst->headtrackerReceiver.oscReceiver.port = te_oscport->getText().getIntValue();
}

void PluginEditor::natNetconnListenerCallback(const String& message) {
    StringArray parts;
    parts.addTokens(message, " ");
    jassert(parts.size() >= 1);
    String id = parts[0];
    if (id == "natnet_connect") {
        te_connectionlabel->setText("connected", NotificationType::dontSendNotification);
        bt_connect->setButtonText("disconnect");
    } else if (id == "natnet_connect_error") {
        te_connectionlabel->setText("connection error", NotificationType::dontSendNotification);
        bt_connect->setButtonText(originalConnectButtonText);
    } else if (id == "natnet_disconnect") {
        te_connectionlabel->setText("disconnected", NotificationType::dontSendNotification);
        bt_connect->setButtonText(originalConnectButtonText);
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
                 parentClasses="public AudioProcessorEditor, public Timer, public juce::TextEditor::Listener"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="410" initialHeight="482">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="2 28 408 452" fill="linear: 8 32, 8 112, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="10 318 390 32" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="71 190 270 31" fill="solid: ffffffff" hasStroke="0" text="NatNet Client"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="10 84 390 108" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="308 84 92 108" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <ROUNDRECT pos="1 2 408 31" cornerSize="5.0" fill="linear: 0 32, 528 32, 0=ff041518, 1=ff19313f"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="10 45 390 40" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 148 32" fill="solid: ffff00f4" hasStroke="0" text="TrackerTest"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 410 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 324" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="408 0 2 480" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 480 410 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <TEXT pos="18 50 115 30" fill="solid: ffffffff" hasStroke="0" text="Host Block Size:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="208 50 144 30" fill="solid: ffffffff" hasStroke="0" text="Host Samplerate:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="18 108 121 30" fill="solid: ffffffff" hasStroke="0" text="Source Position:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="139 86 160 30" fill="solid: ffffffff" hasStroke="0" text="x           y           z"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="10 216 390 79" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="18 218 142 26" fill="solid: ffffffff" hasStroke="0" text="IP Address:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="18 242 142 26" fill="solid: ffffffff" hasStroke="0" text="Server IP Address:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="18 266 142 26" fill="solid: ffffffff" hasStroke="0" text="Unicast:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="140 133 160 30" fill="solid: ffffffff" hasStroke="0" text="yaw     pitch      roll"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="18 155 121 30" fill="solid: ffffffff" hasStroke="0" text="Source Rotation:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="314 110 80 26" fill="solid: ffffffff" hasStroke="0" text="Source mode"
          fontname="Default font" fontsize="11.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="71 293 270 31" fill="solid: ffffffff" hasStroke="0" text="OSC"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="18 320 142 26" fill="solid: ffffffff" hasStroke="0" text="Port:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="71 349 270 31" fill="solid: ffffffff" hasStroke="0" text="MIDI"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <RECT pos="10 374 390 78" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="18 400 102 26" fill="solid: ffffffff" hasStroke="0" text="CC# (coarse):"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="18 424 102 26" fill="solid: ffffffff" hasStroke="0" text="CC# (fine):"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="210 424 102 26" fill="solid: ffffffff" hasStroke="0" text="Quaternions:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="210 400 102 26" fill="solid: ffffffff" hasStroke="0" text="Channel:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="18 376 102 26" fill="solid: ffffffff" hasStroke="0" text="Device:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <LABEL name="new label" id="167c5975ece5bfaa" memberName="label_hostBlockSize"
         virtualName="" explicitFocusOrder="0" pos="136 55 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b5990c279ece4f98" memberName="label_hostfs"
         virtualName="" explicitFocusOrder="0" pos="333 55 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="1799da9e8cf495d6" memberName="te_oscport"
              virtualName="" explicitFocusOrder="0" pos="160 322 42 22" textcol="ffffffff"
              bkgcol="ffffff" outlinecol="6c838080" initialText="9000" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="60e9708fea0d003a" memberName="te_myip"
              virtualName="" explicitFocusOrder="0" pos="160 220 110 22" textcol="ffffffff"
              bkgcol="ffffff" outlinecol="6c838080" initialText="127.0.0.1"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="f8396d4e40c249a1" memberName="te_serverip"
              virtualName="" explicitFocusOrder="0" pos="160 244 110 22" textcol="ffffffff"
              bkgcol="ffffff" outlinecol="6c838080" initialText="127.0.0.1"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="connect" id="cf0ea0fca66caeaf" memberName="bt_connect"
              virtualName="" explicitFocusOrder="0" pos="280 268 110 22" buttonText="connect"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="e9ef59c6d394b3c7" memberName="te_connectionlabel"
         virtualName="" explicitFocusOrder="0" pos="280 222 110 39" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14.0"
         kerning="0.0" bold="0" italic="0" justification="9"/>
  <TOGGLEBUTTON name="new toggle button" id="966e593234714c11" memberName="tb_unicast"
                virtualName="" explicitFocusOrder="0" pos="160 268 110 22" buttonText="Enabled"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="244f8b31bbee0615" memberName="label_x" virtualName=""
         explicitFocusOrder="0" pos="140 114 48 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="520fa9fa22c52b0d" memberName="label_y" virtualName=""
         explicitFocusOrder="0" pos="196 114 48 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f709ae6e14e4cb76" memberName="label_z" virtualName=""
         explicitFocusOrder="0" pos="252 114 48 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="9bb95f8d5ebcc920" memberName="label_yaw"
         virtualName="" explicitFocusOrder="0" pos="140 160 48 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b47b691d0d443ed8" memberName="label_pitch"
         virtualName="" explicitFocusOrder="0" pos="196 160 48 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="dca2d55d6c7c562b" memberName="label_roll"
         virtualName="" explicitFocusOrder="0" pos="252 160 48 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="f9cc0651ab491a56" memberName="tb_unmute"
                virtualName="" explicitFocusOrder="0" pos="7 454 393 24" buttonText="Unmute (DANGEROUS! MAKE SURE THIS IS NOT ROUTED TO SPEAKERS)"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="new combo box" id="4e7387bcea96b2c2" memberName="juce__comboBox"
            virtualName="" explicitFocusOrder="0" pos="408 192 150 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="28ef328a4079820" memberName="cb_sourceMode"
            virtualName="" explicitFocusOrder="0" pos="318 135 72 24" editable="0"
            layout="33" items="NatNet&#10;OSC&#10;MIDI" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <TEXTEDITOR name="new text editor" id="4613ab94650e752c" memberName="te_midiCcCoarse"
              virtualName="" explicitFocusOrder="0" pos="128 402 42 22" textcol="ffffffff"
              bkgcol="ffffff" outlinecol="6c838080" initialText="16" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="a9e35af4ba2a54a8" memberName="te_midiCcFine"
              virtualName="" explicitFocusOrder="0" pos="128 426 42 22" textcol="ffffffff"
              bkgcol="ffffff" outlinecol="6c838080" initialText="48" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="new toggle button" id="49b1046bffae38cc" memberName="tb_midiQuaternions"
                virtualName="" explicitFocusOrder="0" pos="319 426 72 22" buttonText="Yes"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTEDITOR name="new text editor" id="81a4ab89fe67a6f5" memberName="te_midiChannel"
              virtualName="" explicitFocusOrder="0" pos="320 402 42 22" textcol="ffffffff"
              bkgcol="ffffff" outlinecol="6c838080" initialText="1" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <COMBOBOX name="new combo box" id="ec9eeadcf5da0bc3" memberName="cb_midiDevice"
            virtualName="" explicitFocusOrder="0" pos="128 379 192 22" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTBUTTON name="rescan" id="87f009dff7912e2d" memberName="bt_midiRescan"
              virtualName="" explicitFocusOrder="0" pos="325 379 68 22" buttonText="rescan"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

