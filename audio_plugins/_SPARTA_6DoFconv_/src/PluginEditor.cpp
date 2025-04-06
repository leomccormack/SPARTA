
#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    label_hostBlockSize.reset (new juce::Label ("new label",
                                                juce::String()));
    addAndMakeVisible (label_hostBlockSize.get());
    label_hostBlockSize->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_hostBlockSize->setJustificationType (juce::Justification::centredLeft);
    label_hostBlockSize->setEditable (false, false, false);
    label_hostBlockSize->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_hostBlockSize->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_hostBlockSize->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_hostBlockSize->setBounds (136, 95, 60, 20);

    label_filterLength.reset (new juce::Label ("new label",
                                               juce::String()));
    addAndMakeVisible (label_filterLength.get());
    label_filterLength->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_filterLength->setJustificationType (juce::Justification::centredLeft);
    label_filterLength->setEditable (false, false, false);
    label_filterLength->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_filterLength->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_filterLength->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_filterLength->setBounds (333, 95, 60, 20);

    label_hostfs.reset (new juce::Label ("new label",
                                         juce::String()));
    addAndMakeVisible (label_hostfs.get());
    label_hostfs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_hostfs->setJustificationType (juce::Justification::centredLeft);
    label_hostfs->setEditable (false, false, false);
    label_hostfs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_hostfs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_hostfs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_hostfs->setBounds (333, 139, 60, 20);

    label_filterfs.reset (new juce::Label ("new label",
                                           juce::String()));
    addAndMakeVisible (label_filterfs.get());
    label_filterfs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_filterfs->setJustificationType (juce::Justification::centredLeft);
    label_filterfs->setEditable (false, false, false);
    label_filterfs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_filterfs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_filterfs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_filterfs->setBounds (333, 117, 60, 20);

    label_NOutputs.reset (new juce::Label ("new label",
                                           juce::String()));
    addAndMakeVisible (label_NOutputs.get());
    label_NOutputs->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_NOutputs->setJustificationType (juce::Justification::centredLeft);
    label_NOutputs->setEditable (false, false, false);
    label_NOutputs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_NOutputs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_NOutputs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_NOutputs->setBounds (136, 117, 60, 20);

    label_nIRpositions.reset (new juce::Label ("new label",
                                               juce::String()));
    addAndMakeVisible (label_nIRpositions.get());
    label_nIRpositions->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_nIRpositions->setJustificationType (juce::Justification::centredLeft);
    label_nIRpositions->setEditable (false, false, false);
    label_nIRpositions->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_nIRpositions->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_nIRpositions->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_nIRpositions->setBounds (136, 139, 60, 20);

    SL_source_y.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_source_y.get());
    SL_source_y->setRange (0, 1, 0.001);
    SL_source_y->setSliderStyle (juce::Slider::LinearBarVertical);
    SL_source_y->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_source_y->addListener (this);

    SL_source_y->setBounds (200, 200, 48, 20);

    SL_source_z.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_source_z.get());
    SL_source_z->setRange (0, 1, 0.001);
    SL_source_z->setSliderStyle (juce::Slider::LinearBarVertical);
    SL_source_z->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_source_z->addListener (this);

    SL_source_z->setBounds (256, 200, 48, 20);

    SL_source_x.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_source_x.get());
    SL_source_x->setRange (0, 1, 0.001);
    SL_source_x->setSliderStyle (juce::Slider::LinearBarVertical);
    SL_source_x->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_source_x->addListener (this);

    SL_source_x->setBounds (144, 200, 48, 20);

    SL_receiver_x.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_receiver_x.get());
    SL_receiver_x->setRange (0, 1, 0.001);
    SL_receiver_x->setSliderStyle (juce::Slider::LinearBarVertical);
    SL_receiver_x->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_receiver_x->addListener (this);

    SL_receiver_x->setBounds (144, 284, 48, 20);

    SL_receiver_y.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_receiver_y.get());
    SL_receiver_y->setRange (0, 1, 0.001);
    SL_receiver_y->setSliderStyle (juce::Slider::LinearBarVertical);
    SL_receiver_y->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_receiver_y->addListener (this);

    SL_receiver_y->setBounds (200, 284, 48, 20);

    SL_receiver_z.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_receiver_z.get());
    SL_receiver_z->setRange (0, 1, 0.001);
    SL_receiver_z->setSliderStyle (juce::Slider::LinearBarVertical);
    SL_receiver_z->setTextBoxStyle (juce::Slider::TextBoxRight, false, 55, 20);
    SL_receiver_z->addListener (this);

    SL_receiver_z->setBounds (256, 284, 48, 20);

    label_receiverIdx.reset (new juce::Label ("new label",
                                              juce::String()));
    addAndMakeVisible (label_receiverIdx.get());
    label_receiverIdx->setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Regular"));
    label_receiverIdx->setJustificationType (juce::Justification::centredLeft);
    label_receiverIdx->setEditable (false, false, false);
    label_receiverIdx->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_receiverIdx->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_receiverIdx->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_receiverIdx->setBounds (200, 308, 48, 20);

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
    te_oscport->setText (TRANS ("9000"));

    te_oscport->setBounds (344, 296, 42, 22);

    CBviewMode.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBviewMode.get());
    CBviewMode->setEditableText (false);
    CBviewMode->setJustificationType (juce::Justification::centredLeft);
    CBviewMode->setTextWhenNothingSelected (juce::String());
    CBviewMode->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBviewMode->addListener (this);

    CBviewMode->setBounds (755, 38, 92, 16);

    s_yaw.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_yaw.get());
    s_yaw->setRange (-180, 180, 0.01);
    s_yaw->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_yaw->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 15);
    s_yaw->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6e));
    s_yaw->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_yaw->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_yaw->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_yaw->addListener (this);

    s_yaw->setBounds (200, 396, 60, 68);

    s_pitch.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_pitch.get());
    s_pitch->setRange (-180, 180, 0.01);
    s_pitch->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_pitch->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 15);
    s_pitch->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6d));
    s_pitch->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_pitch->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_pitch->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_pitch->addListener (this);

    s_pitch->setBounds (263, 396, 60, 68);

    s_roll.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_roll.get());
    s_roll->setRange (-180, 180, 0.01);
    s_roll->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    s_roll->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 58, 15);
    s_roll->setColour (juce::Slider::rotarySliderFillColourId, juce::Colour (0xff315b6d));
    s_roll->setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour (0xff5c5d5e));
    s_roll->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_roll->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_roll->addListener (this);

    s_roll->setBounds (326, 396, 60, 68);

    t_flipYaw.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipYaw.get());
    t_flipYaw->setButtonText (juce::String());
    t_flipYaw->addListener (this);

    t_flipYaw->setBounds (232, 465, 23, 24);

    t_flipPitch.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipPitch.get());
    t_flipPitch->setButtonText (juce::String());
    t_flipPitch->addListener (this);

    t_flipPitch->setBounds (295, 465, 23, 24);

    t_flipRoll.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (t_flipRoll.get());
    t_flipRoll->setButtonText (juce::String());
    t_flipRoll->addListener (this);

    t_flipRoll->setBounds (358, 465, 23, 24);

    TBenableRotation.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBenableRotation.get());
    TBenableRotation->setButtonText (juce::String());
    TBenableRotation->addListener (this);

    TBenableRotation->setBounds (85, 402, 32, 24);


    setSize (860, 502);

	hVst = ownerFilter;
    hTVC = hVst->getFXHandle();
    hRot = hVst->getFXHandle_rot();

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_source_x->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_source_x->setSliderSnapsToMousePosition(false);
    SL_source_y->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_source_y->setSliderSnapsToMousePosition(false);
    SL_source_z->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_source_z->setSliderSnapsToMousePosition(false);
    SL_receiver_x->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_receiver_x->setSliderSnapsToMousePosition(false);
    SL_receiver_y->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_receiver_y->setSliderSnapsToMousePosition(false);
    SL_receiver_z->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_receiver_z->setSliderSnapsToMousePosition(false);

    /* Used only as labels */
    SL_source_x->setEnabled(false);
    SL_source_y->setEnabled(false);
    SL_source_z->setEnabled(false);


	/* fetch current configuration *///////////////////////////////////////////////////////////////////////////////////
    te_oscport->setText(String(hVst->getOscPortID()), dontSendNotification);
    CBviewMode->addItem(TRANS("Top View"), TOP_VIEW+1); /* must start from 1... */
    CBviewMode->addItem(TRANS("Side View"), SIDE_VIEW+1);
    CBviewMode->setSelectedId(TOP_VIEW+1, dontSendNotification);
    s_yaw->setValue(rotator_getYaw(hRot), dontSendNotification);
    s_pitch->setValue(rotator_getPitch(hRot), dontSendNotification);
    s_roll->setValue(rotator_getRoll(hRot), dontSendNotification);
    t_flipYaw->setToggleState((bool)rotator_getFlipYaw(hRot), dontSendNotification);
    t_flipPitch->setToggleState((bool)rotator_getFlipPitch(hRot), dontSendNotification);
    t_flipRoll->setToggleState((bool)rotator_getFlipRoll(hRot), dontSendNotification);
    TBenableRotation->setToggleState(hVst->getEnableRotation(), dontSendNotification);


    /* create SCENE VIEW window *//////////////////////////////////////////////////////////////////////////////////////
    sceneWindow.reset (new sceneView(ownerFilter, 440, 432));
    addAndMakeVisible (sceneWindow.get());
    sceneWindow->setViewMode(CBviewMode->getSelectedId()-1);
    sceneWindow->setBounds (408, 58, 440, 432);
    refreshSceneViewWindow = true;


    /* file loader *///////////////////////////////////////////////////////////////////////////////////////////////////
    fileComp.reset(new FilenameComponent("fileComp", {},
        true, false, false,
        "*.sofa;*.nc;", {},
        "Load SOFA File"));
    addAndMakeVisible(fileComp.get());
    fileComp->addListener(this);
    fileComp->setBounds(16, 62, 380, 20);
    if (strcmp(tvconv_getSofaFilePath(hTVC), "no_file") != 0) {
        // string is different from "no_file" -> it's been selected a valid file
        fileComp->setCurrentFile(String(tvconv_getSofaFilePath(hTVC)), true, dontSendNotification);
        refreshCoords();
        refreshSceneViewWindow = true;
        sceneWindow->refreshSceneView();
    }
    else {
        SL_receiver_x->setEnabled(false);
        SL_receiver_y->setEnabled(false);
        SL_receiver_z->setEnabled(false);
    }


    /* tooltips *//////////////////////////////////////////////////////////////////////////////////////////////////////
    TBenableRotation->setTooltip("Enable spherical harmonic/sound-field rotation. This is only applicable if you have loaded Ambisonic IRs, which must be in the ACN channel ordering convention. (Note that the Ambisonics normalisation convention does not affect the rotations (i.e. it doesn't matter if the Ambisonic signals are N3D or SN3D, the rotations will be correct)).");
    s_yaw->setTooltip("Sets the 'Yaw' rotation angle (in degrees).");
    s_pitch->setTooltip("Sets the 'Pitch' rotation angle (in degrees).");
    s_roll->setTooltip("Sets the 'Roll' rotation angle (in degrees).");
    t_flipYaw->setTooltip("Flips the sign (+/-) of the 'Yaw' rotation angle.");
    t_flipPitch->setTooltip("Flips the sign (+/-) of the 'Pitch' rotation angle.");
    t_flipRoll->setTooltip("Flips the sign (+/-) of the 'Roll' rotation angle.");


    /* Plugin description *////////////////////////////////////////////////////////////////////////////////////////////
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 240, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("Time-varying impulse response convolver. A set of IRs can be loaded from a sofa file, where IRs have to be assigned with different ListenerPositions. The position of the receiver can be varied during playback using the parameter sliders. The convolver finds the nearest neighbour IR of the selected position. It applies overlap-add partitioned convolution and cross-fades between previous and current positions to produce smooth transitions. Each IR can have up to 64 channels (7th order Ambisonics). Single fixed SourcePosition is assumed and only mono input is supported.\n"));

    /* Specify screen refresh rate */
    startTimer(refreshInterval); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;
}

PluginEditor::~PluginEditor()
{
    label_hostBlockSize = nullptr;
    label_filterLength = nullptr;
    label_hostfs = nullptr;
    label_filterfs = nullptr;
    label_NOutputs = nullptr;
    label_nIRpositions = nullptr;
    SL_source_y = nullptr;
    SL_source_z = nullptr;
    SL_source_x = nullptr;
    SL_receiver_x = nullptr;
    SL_receiver_y = nullptr;
    SL_receiver_z = nullptr;
    label_receiverIdx = nullptr;
    te_oscport = nullptr;
    CBviewMode = nullptr;
    s_yaw = nullptr;
    s_pitch = nullptr;
    s_roll = nullptr;
    t_flipYaw = nullptr;
    t_flipPitch = nullptr;
    t_flipRoll = nullptr;
    TBenableRotation = nullptr;

    setLookAndFeel(nullptr);
    fileComp = nullptr;
}

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    {
        int x = 2, y = 28, width = 860, height = 290;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
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
        int x = 0, y = 316, width = 860, height = 188;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             496.0f - 316.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             416.0f - 316.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 10, y = 256, width = 390, height = 88;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 10, y = 168, width = 390, height = 62;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 10, y = 375, width = 174, height = 116;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);

        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 329, y = 256, width = 71, height = 88;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);

        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 183, y = 375, width = 218, height = 116;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);

        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 408, y = 58, width = 440, height = 430;
        juce::Colour fillColour = juce::Colour (0x10f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);

        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 10, y = 58, width = 390, height = 28;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);

        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        float x = 1.0f, y = 2.0f, width = 858.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);

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
        int x = 10, y = 85, width = 390, height = 84;
        juce::Colour fillColour = juce::Colour (0x10c7c7c7);
        juce::Colour strokeColour = juce::Colour (0x67a0a0a0);

        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

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
        int x = 92, y = 1, width = 148, height = 32;
        juce::String text (TRANS ("6DoFconv"));
        juce::Colour fillColour = juce::Colour (0xffff00f4);

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (18.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 860, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);

        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 610;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);

        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 858, y = 0, width = 2, height = 610;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);

        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 500, width = 860, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);

        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 18, y = 86, width = 115, height = 30;
        juce::String text (TRANS ("Host Block Size:"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 210, y = 86, width = 200, height = 30;
        juce::String text (TRANS ("IR Length (s):"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 210, y = 110, width = 128, height = 30;
        juce::String text (TRANS ("Filter Samplerate:"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 210, y = 134, width = 144, height = 30;
        juce::String text (TRANS ("Host Samplerate:"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 110, width = 120, height = 31;
        juce::String text (TRANS ("N# IR channels:"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 71, y = 34, width = 270, height = 31;
        juce::String text (TRANS ("Load IR dataset"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 18, y = 134, width = 200, height = 30;
        juce::String text (TRANS ("N# IR positions:"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 415, y = 34, width = 417, height = 31;
        juce::String text (TRANS ("Coordinate View"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 71, y = 231, width = 270, height = 31;
        juce::String text (TRANS ("Target Listener Position"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 18, y = 193, width = 121, height = 30;
        juce::String text (TRANS ("Source Position:"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 18, y = 280, width = 142, height = 26;
        juce::String text (TRANS ("Target Position:"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 143, y = 255, width = 160, height = 30;
        juce::String text (TRANS ("x           y           z"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 18, y = 304, width = 142, height = 26;
        juce::String text (TRANS ("Target Index:"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 343, y = 263, width = 91, height = 35;
        juce::String text (TRANS ("OSC Port"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (11.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 221, y = 374, width = 49, height = 30;
        juce::String text (TRANS ("\\ypr[0]"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (10.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 261, y = 374, width = 46, height = 30;
        juce::String text (TRANS ("Pitch"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 317, y = 374, width = 54, height = 30;
        juce::String text (TRANS ("Roll"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 317, y = 462, width = 63, height = 30;
        juce::String text (TRANS ("+/-"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 189, y = 462, width = 63, height = 30;
        juce::String text (TRANS ("+/-"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 253, y = 462, width = 63, height = 30;
        juce::String text (TRANS ("+/-"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (13.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 184, y = 374, width = 62, height = 30;
        juce::String text (TRANS ("Yaw"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 294, y = 374, width = 40, height = 30;
        juce::String text (TRANS ("\\ypr[1]"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (10.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 350, y = 374, width = 40, height = 30;
        juce::String text (TRANS ("\\ypr[2]"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (10.00f, juce::Font::plain).withStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 20, y = 375, width = 160, height = 30;
        juce::String text (TRANS ("Enable Rotation"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 143, y = 167, width = 160, height = 30;
        juce::String text (TRANS ("x           y           z"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 71, y = 349, width = 270, height = 31;
        juce::String text (TRANS ("Ambisonic Sound-Field Rotation"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (15.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 18, y = 423, width = 160, height = 30;
        juce::String text (TRANS ("(Note that this rotation is"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 18, y = 439, width = 160, height = 30;
        juce::String text (TRANS ("only suitable if you have "));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 18, y = 455, width = 160, height = 30;
        juce::String text (TRANS ("loaded Ambisonic IRs)"));
        juce::Colour fillColour = juce::Colours::white;

        g.setColour (fillColour);
        g.setFont (juce::FontOptions (12.00f, juce::Font::plain).withStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    /* display version/date built */
	g.setColour(Colours::white);
	g.setFont(juce::FontOptions(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		200, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(juce::FontOptions(11.00f, Font::plain));
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

    g.setColour(Colours::white);
    switch (tvConvError)
    {
    case SAF_TVCONV_NOT_INIT: /** TVCONV no file loaded */
        g.drawText(TRANS("SOFA file not initialized"),
            10, 35, 264, 11,
            Justification::centredLeft, true);
        break;
    case SAF_TVCONV_SOFA_LOADING: /** Loading SOFA file */
        g.drawText(TRANS("SOFA file: loading"),
            10, 35, 264, 11,
            Justification::centredLeft, true);
        break;
    case SAF_TVCONV_SOFA_OK: /** None of the error checks failed */
        g.drawText(TRANS("SOFA file loaded"),
            10, 35, 264, 11,
            Justification::centredLeft, true);
        break;
    case SAF_TVCONV_SOFA_ERROR_INVALID_FILE_OR_FILE_PATH:  /** Not a SOFA file, or no such file was found in the specified location */
        g.drawText(TRANS("SOFA file not loaded: INVALID FILE OR FILE PATH"),
            10, 35, 264, 11,
            Justification::centredLeft, true);
        break;
    case SAF_TVCONV_SOFA_ERROR_DIMENSIONS_UNEXPECTED:      /** Dimensions of the SOFA data were not as expected */
        g.drawText(TRANS("SOFA file not loaded: DIMENSIONS UNEXPECTED"),
            10, 35, 264, 11,
            Justification::centredLeft, true);
        break;
    case SAF_TVCONV_SOFA_ERROR_FORMAT_UNEXPECTED: /** The data-type of the SOFA data was not as expected */
        g.drawText(TRANS("SOFA file not loaded: FORMAT UNEXPECTED"),
            10, 35, 264, 11,
            Justification::centredLeft, true);
        break;
    case SAF_TVCONV_SOFA_ERROR_NETCDF_IN_USE: /** NetCDF is not thread safe! */
        g.drawText(TRANS("SOFA file not loaded: NETCDF IN USE"),
            10, 35, 264, 11,
            Justification::centredLeft, true);
        break;
    default:
        g.drawText(TRANS("SOFA file state"), 10, 35, 264, 11, Justification::centredLeft, true);
    }
}

void PluginEditor::resized()
{
	repaint();
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == SL_source_y.get())
    {
    }
    else if (sliderThatWasMoved == SL_source_z.get())
    {
    }
    else if (sliderThatWasMoved == SL_source_x.get())
    {
    }
    else if (sliderThatWasMoved == SL_receiver_x.get())
    {
        tvconv_setTargetPosition(hTVC, SL_receiver_x->getValue(), 0);
        refreshSceneViewWindow = true;
    }
    else if (sliderThatWasMoved == SL_receiver_y.get())
    {
        tvconv_setTargetPosition(hTVC, SL_receiver_y->getValue(), 1);
        refreshSceneViewWindow = true;
    }
    else if (sliderThatWasMoved == SL_receiver_z.get())
    {
        tvconv_setTargetPosition(hTVC, SL_receiver_z->getValue(), 2);
        refreshSceneViewWindow = true;
    }
    else if (sliderThatWasMoved == s_yaw.get())
    {
        rotator_setYaw(hRot, (float)s_yaw->getValue());
    }
    else if (sliderThatWasMoved == s_pitch.get())
    {
        rotator_setPitch(hRot, (float)s_pitch->getValue());
    }
    else if (sliderThatWasMoved == s_roll.get())
    {
        rotator_setRoll(hRot, (float)s_roll->getValue());
    }
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == CBviewMode.get())
    {
        sceneWindow->setViewMode(CBviewMode->getSelectedId()-1);
        refreshSceneViewWindow = true;
    }
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == t_flipYaw.get())
    {
        rotator_setFlipYaw(hRot, (int)t_flipYaw->getToggleState());
    }
    else if (buttonThatWasClicked == t_flipPitch.get())
    {
        rotator_setFlipPitch(hRot, (int)t_flipPitch->getToggleState());
    }
    else if (buttonThatWasClicked == t_flipRoll.get())
    {
        rotator_setFlipRoll(hRot, (int)t_flipRoll->getToggleState());
    }
    else if (buttonThatWasClicked == TBenableRotation.get())
    {
        hVst->setEnableRotation(TBenableRotation->getToggleState());
    }
}

#if 0
void PluginEditor::refreshCoords()
{
    if (tvconv_getMaxDimension(hTVC, 0) > tvconv_getMinDimension(hTVC, 0)) {
        SL_receiver_x->setEnabled(true);
        SL_receiver_x->setRange(tvconv_getMinDimension(hTVC, 0),
            tvconv_getMaxDimension(hTVC, 0),
            0.001);
    } else {
        SL_receiver_x->setEnabled(false);
    }
    SL_receiver_x->setValue(tvconv_getTargetPosition(hTVC, 0));
    if (tvconv_getMaxDimension(hTVC, 1) > tvconv_getMinDimension(hTVC, 1)) {
        SL_receiver_y->setEnabled(true);
        SL_receiver_y->setRange(tvconv_getMinDimension(hTVC, 1),
            tvconv_getMaxDimension(hTVC, 1),
            0.001);
    } else {
        SL_receiver_y->setEnabled(false);
    }
    SL_receiver_y->setValue(tvconv_getTargetPosition(hTVC, 1));
    if (tvconv_getMaxDimension(hTVC, 2) > tvconv_getMinDimension(hTVC, 2)) {
        SL_receiver_z->setEnabled(true);
        SL_receiver_z->setRange(tvconv_getMinDimension(hTVC, 2),
            tvconv_getMaxDimension(hTVC, 2),
            0.001);
    } else {
        SL_receiver_z->setEnabled(false);
    }
    SL_receiver_z->setValue(tvconv_getTargetPosition(hTVC, 2));

    //float sourcePosition = tvconv_getSourcePosition(hTVC, 0);

    SL_source_x->setRange(tvconv_getSourcePosition(hTVC, 0), tvconv_getSourcePosition(hTVC, 0) + 1, 0.1);
    SL_source_x->setValue(tvconv_getSourcePosition(hTVC, 0));
    SL_source_y->setRange(tvconv_getSourcePosition(hTVC, 1), tvconv_getSourcePosition(hTVC, 1) + 1, 0.1);
    SL_source_y->setValue(tvconv_getSourcePosition(hTVC, 1));
    SL_source_z->setRange(tvconv_getSourcePosition(hTVC, 2), tvconv_getSourcePosition(hTVC, 2) + 1, 0.1);
    SL_source_z->setValue(tvconv_getSourcePosition(hTVC, 2));
}
#endif

void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    s_yaw->setValue(rotator_getYaw(hRot), dontSendNotification);
    s_pitch->setValue(rotator_getPitch(hRot), dontSendNotification);
    s_roll->setValue(rotator_getRoll(hRot), dontSendNotification);
    label_hostBlockSize->setText(String(tvconv_getHostBlockSize(hTVC)), dontSendNotification);
    label_NOutputs->setText(String(tvconv_getNumIRs(hTVC)), dontSendNotification);
    label_nIRpositions->setText(String(tvconv_getNumListenerPositions(hTVC)), dontSendNotification);
    label_filterLength->setText(String((float)tvconv_getIRLength(hTVC)/MAX((float)tvconv_getIRFs(hTVC),1/*avoid nan*/)), dontSendNotification);
    label_hostfs->setText(String(tvconv_getHostFs(hTVC)), dontSendNotification);
    label_filterfs->setText(String(tvconv_getIRFs(hTVC)), dontSendNotification);
    label_receiverIdx->setText(String(tvconv_getListenerPositionIdx(hTVC)), dontSendNotification);

    SL_receiver_x->setValue(tvconv_getTargetPosition(hTVC, 0));
    SL_receiver_y->setValue(tvconv_getTargetPosition(hTVC, 1));
    SL_receiver_z->setValue(tvconv_getTargetPosition(hTVC, 2));

    /* display warning message, if needed */
    if((tvconv_getNumIRs(hTVC) != 0) && (tvconv_getHostFs(hTVC)!=tvconv_getIRFs(hTVC))){
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

    tvConvError = tvconv_getSofaErrorState(hTVC);
    repaint(136, 45, 264, 11);


    if (refreshSceneViewWindow == true)
    {
        sceneWindow->refreshSceneView();
        refreshSceneViewWindow = false;
    }
    else
    {
        refreshDecimationCounter--;
        if (refreshDecimationCounter == 0)
        {
            refreshDecimationCounter = 25;
            sceneWindow->refreshSceneView();
        }
    }

    /* check if OSC port has changed */
    if (hVst->getOscPortID() != te_oscport->getText().getIntValue())
        hVst->setOscPortID(te_oscport->getText().getIntValue());
}

void PluginEditor::refreshCoords()
{
    // Get receiver position data from convolver and update slider X
    if (tvconv_getMaxDimension(hTVC, 0) > tvconv_getMinDimension(hTVC, 0))
    {
        SL_receiver_x->setEnabled(true);
        SL_receiver_x->setRange(tvconv_getMinDimension(hTVC, 0),
                                tvconv_getMaxDimension(hTVC, 0),
                                0.001);
    }
    else
    {
        SL_receiver_x->setEnabled(false);
    }
    SL_receiver_x->setValue(tvconv_getTargetPosition(hTVC, 0));

    // Get receiver position data from convolver and update slider Y
    if (tvconv_getMaxDimension(hTVC, 1) > tvconv_getMinDimension(hTVC, 1)){
        SL_receiver_y->setEnabled(true);
        SL_receiver_y->setRange(tvconv_getMinDimension(hTVC, 1),
                                tvconv_getMaxDimension(hTVC, 1),
                                0.001);
    } else {
        SL_receiver_y->setEnabled(false);
    }
    SL_receiver_y->setValue(tvconv_getTargetPosition(hTVC, 1));

    // Get receiver position data from convolver and update slider Z
    if (tvconv_getMaxDimension(hTVC, 2) > tvconv_getMinDimension(hTVC, 2)){
        SL_receiver_z->setEnabled(true);
        SL_receiver_z->setRange(tvconv_getMinDimension(hTVC, 2),
                                tvconv_getMaxDimension(hTVC, 2),
                                0.001);
    } else {
        SL_receiver_z->setEnabled(false);
    }
    SL_receiver_z->setValue(tvconv_getTargetPosition(hTVC, 2));


    // Get SOURCE position data from convolver and update sliders (XYZ)

    //float sourcePosition = tvconv_getSourcePosition(hTVC, 0);

    SL_source_x->setRange(tvconv_getSourcePosition(hTVC, 0), tvconv_getSourcePosition(hTVC, 0)+1, 0.1);
    SL_source_x->setValue(tvconv_getSourcePosition(hTVC, 0));
    SL_source_y->setRange(tvconv_getSourcePosition(hTVC, 1), tvconv_getSourcePosition(hTVC, 1)+1, 0.1);
    SL_source_y->setValue(tvconv_getSourcePosition(hTVC, 1));
    SL_source_z->setRange(tvconv_getSourcePosition(hTVC, 2), tvconv_getSourcePosition(hTVC, 2)+1, 0.1);
    SL_source_z->setValue(tvconv_getSourcePosition(hTVC, 2));

	// Notify the host about the room size
	hVst->room_size_x->beginChangeGesture();
	hVst->room_size_x->setValueNotifyingHost(tvconv_getMaxDimension(hTVC, 0) - tvconv_getMinDimension(hTVC, 0));
	hVst->room_size_x->endChangeGesture();
	hVst->room_size_y->beginChangeGesture();
	hVst->room_size_y->setValueNotifyingHost(tvconv_getMaxDimension(hTVC, 1) - tvconv_getMinDimension(hTVC, 1));
	hVst->room_size_y->endChangeGesture();
	hVst->room_size_z->beginChangeGesture();
	hVst->room_size_z->setValueNotifyingHost(tvconv_getMaxDimension(hTVC, 2) - tvconv_getMinDimension(hTVC, 2));
	hVst->room_size_z->endChangeGesture();
}


bool PluginEditor::getRefreshSceneViewWindow()
{
    return this->refreshSceneViewWindow;
}

void PluginEditor::setRefreshSceneViewWindow(bool val)
{
    refreshSceneViewWindow = val;
}
