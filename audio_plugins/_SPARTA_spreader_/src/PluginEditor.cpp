/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.2

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
    : AudioProcessorEditor(ownerFilter), progressbar(progress), fileChooser ("File", File(), true, false, false,
      "*.sofa;*.nc;", String(),
      "Load SOFA File")
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    SL_num_sources.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_sources.get());
    SL_num_sources->setRange (1, 8, 1);
    SL_num_sources->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_sources->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_sources->addListener (this);

    SL_num_sources->setBounds (152, 65, 48, 20);

    label_N_dirs.reset (new juce::Label ("new label",
                                         juce::String()));
    addAndMakeVisible (label_N_dirs.get());
    label_N_dirs->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_N_dirs->setJustificationType (juce::Justification::centredLeft);
    label_N_dirs->setEditable (false, false, false);
    label_N_dirs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_N_dirs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_N_dirs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_N_dirs->setBounds (848, 207, 51, 20);

    label_HRIR_fs.reset (new juce::Label ("new label",
                                          juce::String()));
    addAndMakeVisible (label_HRIR_fs.get());
    label_HRIR_fs->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_HRIR_fs->setJustificationType (juce::Justification::centredLeft);
    label_HRIR_fs->setEditable (false, false, false);
    label_HRIR_fs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_HRIR_fs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_HRIR_fs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_HRIR_fs->setBounds (848, 255, 51, 20);

    TBuseDefaultHRIRs.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (TBuseDefaultHRIRs.get());
    TBuseDefaultHRIRs->setButtonText (juce::String());
    TBuseDefaultHRIRs->addListener (this);

    TBuseDefaultHRIRs->setBounds (876, 61, 32, 24);

    label_DAW_fs.reset (new juce::Label ("new label",
                                         juce::String()));
    addAndMakeVisible (label_DAW_fs.get());
    label_DAW_fs->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_DAW_fs->setJustificationType (juce::Justification::centredLeft);
    label_DAW_fs->setEditable (false, false, false);
    label_DAW_fs->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_DAW_fs->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_DAW_fs->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_DAW_fs->setBounds (848, 279, 51, 20);

    label_N_CH.reset (new juce::Label ("new label",
                                       juce::String()));
    addAndMakeVisible (label_N_CH.get());
    label_N_CH->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_N_CH->setJustificationType (juce::Justification::centredLeft);
    label_N_CH->setEditable (false, false, false);
    label_N_CH->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_N_CH->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_N_CH->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_N_CH->setBounds (848, 183, 51, 20);

    CBmode.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBmode.get());
    CBmode->setEditableText (false);
    CBmode->setJustificationType (juce::Justification::centredLeft);
    CBmode->setTextWhenNothingSelected (juce::String());
    CBmode->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBmode->addListener (this);

    CBmode->setBounds (816, 125, 86, 20);

    label_IR_length.reset (new juce::Label ("new label",
                                            juce::String()));
    addAndMakeVisible (label_IR_length.get());
    label_IR_length->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label_IR_length->setJustificationType (juce::Justification::centredLeft);
    label_IR_length->setEditable (false, false, false);
    label_IR_length->setColour (juce::Label::outlineColourId, juce::Colour (0x68a3a2a2));
    label_IR_length->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label_IR_length->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label_IR_length->setBounds (848, 231, 51, 20);

    SL_avgCoeff.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_avgCoeff.get());
    SL_avgCoeff->setRange (0, 1, 0.01);
    SL_avgCoeff->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_avgCoeff->setTextBoxStyle (juce::Slider::TextBoxRight, false, 45, 20);
    SL_avgCoeff->addListener (this);

    SL_avgCoeff->setBounds (805, 152, 96, 20);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (920, 316);


    //[Constructor] You can add your own custom stuff here..

    /* handle to pluginProcessor */
	hVst = ownerFilter;
    hSpr = hVst->getFXHandle();

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_num_sources->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_sources->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_sources->setSliderSnapsToMousePosition(false);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

    /* source coordinate viewport */
    sourceCoordsVP.reset (new Viewport ("new viewport"));
    addAndMakeVisible (sourceCoordsVP.get());
    sourceCoordsView_handle = new inputCoordsView(ownerFilter, SPREADER_MAX_NUM_SOURCES, spreader_getNumSources(hSpr));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(22, 119, 184, 180);
    sourceCoordsView_handle->setNCH(spreader_getNumSources(hSpr));

    /* file loader */
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
    fileChooser.setBounds (718, 89, 180, 20);
    StringArray filenames;
    filenames.add(spreader_getSofaFilePath(hSpr));
    fileChooser.setRecentlyUsedFilenames(filenames);
    fileChooser.setFilenameIsEditable(true);

    /* grab current parameter settings */
    TBuseDefaultHRIRs->setToggleState(spreader_getUseDefaultHRIRsflag(hSpr), dontSendNotification);
    SL_num_sources->setValue(spreader_getNumSources(hSpr),dontSendNotification);
    CBmode->addItem(TRANS("Basic"), SPREADER_MODE_NAIVE);
    CBmode->addItem(TRANS("EVD"), SPREADER_MODE_EVD);
    CBmode->addItem(TRANS("OM"), SPREADER_MODE_OM);
    CBmode->setSelectedId(spreader_getSpreadingMode(hSpr), dontSendNotification);
    SL_avgCoeff->setValue(spreader_getAveragingCoeff(hSpr), dontSendNotification);

    /* create panning window */
    panWindow.reset (new pannerView(ownerFilter, 492, 246));
    addAndMakeVisible (panWindow.get());
    panWindow->setBounds (214, 58, 492, 246);
    panWindow->setShowInputs(true);
    panWindow->setShowOutputs(true);
    refreshPanViewWindow = true;

    /* tooltips */
    TBuseDefaultHRIRs->setTooltip("If this is 'ticked', the plug-in is using the default HRIR set from the Spatial_Audio_Framework.");
    fileChooser.setTooltip("Optionally, a custom IR set may be loaded via the SOFA standard. Note that if the plug-in fails to load the specified .sofa file, it will revert to the default IR data.");
    label_N_dirs->setTooltip("Number of IR directions in the current IR set.");
    label_N_CH->setTooltip("Number of triangles found when computing the Convex Hull of the IR grid.");
    label_HRIR_fs->setTooltip("Sampling rate used when measuring/modelling the IRs.");
    label_DAW_fs->setTooltip("Current sampling rate, as dictated by the DAW/Host.");
    SL_avgCoeff->setTooltip("Amount of parameter averaging (0: none, 0.99: lots).");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("An arbitrary array panner with coherent and incoherent spreading options. Basically, any array (up to 64 channel) that can be desribed based on a number of impulse response (IR) measurements and loaded as a SOFA file can be used (e.g. HRIRs, or microphone array IRs).\n"));
    addAndMakeVisible (publicationLink);
    publicationLink.setColour (HyperlinkButton::textColourId, Colours::lightblue);
    publicationLink.setBounds(getBounds().getWidth()-80, 4, 80, 12);
    publicationLink.setJustificationType(Justification::centredLeft);

	/* Specify screen refresh rate */
    startTimer(TIMER_GUI_RELATED, 40);

    /* warnings */
    currentWarning = k_warning_none;

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    SL_num_sources = nullptr;
    label_N_dirs = nullptr;
    label_HRIR_fs = nullptr;
    TBuseDefaultHRIRs = nullptr;
    label_DAW_fs = nullptr;
    label_N_CH = nullptr;
    CBmode = nullptr;
    label_IR_length = nullptr;
    SL_avgCoeff = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    setLookAndFeel(nullptr);
    panWindow = nullptr;
    sourceCoordsVP = nullptr;
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 30, width = 920, height = 163;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             80.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 193, width = 920, height = 127;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             312.0f - 193.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             264.0f - 193.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 918.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             920.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 712, y = 176, width = 196, height = 128;
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
        int x = 12, y = 58, width = 196, height = 32;
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
        int x = 214, y = 58, width = 492, height = 246;
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
        int x = 12, y = 89, width = 196, height = 215;
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
        int x = 712, y = 58, width = 196, height = 60;
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
        int x = 712, y = 117, width = 196, height = 60;
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
        int x = 23, y = 58, width = 153, height = 30;
        juce::String text (TRANS("Number of Inputs:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 84, y = 32, width = 113, height = 30;
        juce::String text (TRANS("Inputs"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 782, y = 32, width = 113, height = 30;
        juce::String text (TRANS("Outputs"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 392, y = 32, width = 136, height = 30;
        juce::String text (TRANS("Panning Window"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 720, y = 58, width = 160, height = 30;
        juce::String text (TRANS("Use Default IR set:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 722, y = 274, width = 118, height = 30;
        juce::String text (TRANS("DAW Samplerate:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
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
        juce::String text (TRANS("Spreader"));
        juce::Colour fillColour = juce::Colour (0xfffff973);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 89, width = 192, height = 28;
        juce::String text (juce::CharPointer_UTF8 ("   #    Azi\xc2\xb0     Elev\xc2\xb0    Spread\xc2\xb0"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 922, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 360;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 918, y = 0, width = 2, height = 360;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 314, width = 920, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 722, y = 250, width = 118, height = 30;
        juce::String text (TRANS("IR Samplerate:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 722, y = 202, width = 126, height = 30;
        juce::String text (TRANS("Num Directions:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 722, y = 226, width = 89, height = 30;
        juce::String text (TRANS("IR length:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 722, y = 118, width = 89, height = 30;
        juce::String text (TRANS("Spread Mode:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 722, y = 178, width = 142, height = 30;
        juce::String text (TRANS("Num Channels:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 722, y = 146, width = 89, height = 30;
        juce::String text (TRANS("Avg Coeff:"));
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
		200, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(spreader_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(spreader_getDAWsamplerate(hSpr)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_mismatch_fs:
            g.drawText(TRANS("Sample rate mismatch between DAW/HRIRs"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(spreader_getNumSources(hSpr)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(spreader_getNumOutputs(hSpr)) + TRANS(")"),
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

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == SL_num_sources.get())
    {
        //[UserSliderCode_SL_num_sources] -- add your slider handling code here..
        spreader_setNumSources(hSpr, (int)SL_num_sources->getValue());
        refreshPanViewWindow = true;
        //[/UserSliderCode_SL_num_sources]
    }
    else if (sliderThatWasMoved == SL_avgCoeff.get())
    {
        //[UserSliderCode_SL_avgCoeff] -- add your slider handling code here..
        spreader_setAveragingCoeff(hSpr, SL_avgCoeff->getValue());
        //[/UserSliderCode_SL_avgCoeff]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == TBuseDefaultHRIRs.get())
    {
        //[UserButtonCode_TBuseDefaultHRIRs] -- add your button handler code here..
        spreader_setUseDefaultHRIRsflag(hSpr, (int)TBuseDefaultHRIRs->getToggleState());
        refreshPanViewWindow = true;
        //[/UserButtonCode_TBuseDefaultHRIRs]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBmode.get())
    {
        //[UserComboBoxCode_CBmode] -- add your combo box handling code here..
        spreader_setSpreadingMode(hSpr, (int)CBmode->getSelectedId());
        //[/UserComboBoxCode_CBmode]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback(int timerID)
{
    switch(timerID){
        case TIMER_PROCESSING_RELATED:
            /* handled in PluginProcessor */
            break;

        case TIMER_GUI_RELATED:

            /* labels for HRIR details */
            label_N_dirs->setText(String(spreader_getNDirs(hSpr)), dontSendNotification);
            label_HRIR_fs->setText(String(spreader_getIRsamplerate(hSpr)), dontSendNotification);
            label_DAW_fs->setText(String(spreader_getDAWsamplerate(hSpr)), dontSendNotification);
            label_N_CH->setText(String(spreader_getNumOutputs(hSpr)), dontSendNotification);
            label_IR_length->setText(String(spreader_getIRlength(hSpr)), dontSendNotification);

            /* parameters whos values can change internally should be periodically refreshed */
            sourceCoordsView_handle->setNCH(spreader_getNumSources(hSpr));
            if(spreader_getUseDefaultHRIRsflag(hSpr)!=TBuseDefaultHRIRs->getToggleState())
                TBuseDefaultHRIRs->setToggleState(spreader_getUseDefaultHRIRsflag(hSpr), dontSendNotification);
            if(spreader_getNumSources(hSpr)!=SL_num_sources->getValue())
                SL_num_sources->setValue(spreader_getNumSources(hSpr),dontSendNotification);

            /* Progress bar */
            if(spreader_getCodecStatus(hSpr)==CODEC_STATUS_INITIALISING){
                addAndMakeVisible(progressbar);
                progress = (double)spreader_getProgressBar0_1(hSpr);
                char text[PROGRESSBARTEXT_CHAR_LENGTH];
                spreader_getProgressBarText(hSpr, (char*)text);
                progressbar.setTextToDisplay(String(text));
            }
            else
                removeChildComponent(&progressbar);

            /* disable certain parameters if currently initialising */
            if(spreader_getCodecStatus(hSpr)==CODEC_STATUS_INITIALISING){
                if(SL_num_sources->isEnabled())
                    SL_num_sources->setEnabled(false);
                if(TBuseDefaultHRIRs->isEnabled())
                    TBuseDefaultHRIRs->setEnabled(false);
                if(fileChooser.isEnabled())
                   fileChooser.setEnabled(false);
                if(sourceCoordsVP->isEnabled())
                   sourceCoordsVP->setEnabled(false);
            }
            else{
                if(!SL_num_sources->isEnabled())
                    SL_num_sources->setEnabled(true);
                if(!TBuseDefaultHRIRs->isEnabled())
                    TBuseDefaultHRIRs->setEnabled(true);
                if(!fileChooser.isEnabled())
                    fileChooser.setEnabled(true);
                if(!sourceCoordsVP->isEnabled())
                    sourceCoordsVP->setEnabled(true);
            }

            /* refresh pan view */
            if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) || sourceCoordsView_handle->getHasASliderChanged() || hVst->getRefreshWindow()){
                panWindow->refreshPanView();
                sourceCoordsView_handle->setHasASliderChange(false);
                refreshPanViewWindow = false;
                hVst->setRefreshWindow(false);
            }

            /* display warning message, if needed */
            if ((hVst->getCurrentBlockSize() % spreader_getFrameSize()) != 0){
                currentWarning = k_warning_frameSize;
                repaint(0,0,getWidth(),32);
            }
            else if ( !((spreader_getDAWsamplerate(hSpr) == 44.1e3) || (spreader_getDAWsamplerate(hSpr) == 48e3)) ){
                currentWarning = k_warning_supported_fs;
                repaint(0,0,getWidth(),32);
            }
            else if (spreader_getDAWsamplerate(hSpr) != spreader_getIRsamplerate(hSpr)){
                currentWarning = k_warning_mismatch_fs;
                repaint(0,0,getWidth(),32);
            }
            else if ((hVst->getCurrentNumInputs() < spreader_getNumSources(hSpr))){
                currentWarning = k_warning_NinputCH;
                repaint(0,0,getWidth(),32);
            }
            else if ((hVst->getCurrentNumOutputs() < spreader_getNumOutputs(hSpr))){
                currentWarning = k_warning_NoutputCH;
                repaint(0,0,getWidth(),32);
            }
            else if(currentWarning){
                currentWarning = k_warning_none;
                repaint(0,0,getWidth(),32);
            }

            break;
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
                 parentClasses="public AudioProcessorEditor, public MultiTimer, private FilenameComponentListener"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter), progressbar(progress), fileChooser (&quot;File&quot;, File(), true, false, false,&#10;                       &quot;*.sofa;*.nc;&quot;, String(),&#10;                       &quot;Load SOFA File&quot;)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="920" initialHeight="316">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 920 163" fill="linear: 8 32, 8 80, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="0 193 920 127" fill="linear: 8 312, 8 264, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <ROUNDRECT pos="1 2 918 31" cornerSize="5.0" fill="linear: 0 32, 920 32, 0=ff041518, 1=ff19313f"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="712 176 196 128" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 58 196 32" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="214 58 492 246" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="12 89 196 215" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="712 58 196 60" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="712 117 196 60" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="23 58 153 30" fill="solid: ffffffff" hasStroke="0" text="Number of Inputs:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="84 32 113 30" fill="solid: ffffffff" hasStroke="0" text="Inputs"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="782 32 113 30" fill="solid: ffffffff" hasStroke="0" text="Outputs"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="392 32 136 30" fill="solid: ffffffff" hasStroke="0" text="Panning Window"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="720 58 160 30" fill="solid: ffffffff" hasStroke="0" text="Use Default IR set:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="722 274 118 30" fill="solid: ffffffff" hasStroke="0" text="DAW Samplerate:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 112 32" fill="solid: fffff973" hasStroke="0" text="Spreader"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 89 192 28" fill="solid: ffffffff" hasStroke="0" text="   #    Azi&#176;     Elev&#176;    Spread&#176;"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 922 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 360" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="918 0 2 360" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 314 920 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <TEXT pos="722 250 118 30" fill="solid: ffffffff" hasStroke="0" text="IR Samplerate:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="722 202 126 30" fill="solid: ffffffff" hasStroke="0" text="Num Directions:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="722 226 89 30" fill="solid: ffffffff" hasStroke="0" text="IR length:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="722 118 89 30" fill="solid: ffffffff" hasStroke="0" text="Spread Mode:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="722 178 142 30" fill="solid: ffffffff" hasStroke="0" text="Num Channels:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="722 146 89 30" fill="solid: ffffffff" hasStroke="0" text="Avg Coeff:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="2c2a2b3d0614cc94" memberName="SL_num_sources"
          virtualName="" explicitFocusOrder="0" pos="152 65 48 20" min="1.0"
          max="8.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="167c5975ece5bfaa" memberName="label_N_dirs"
         virtualName="" explicitFocusOrder="0" pos="848 207 51 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f8b5274e0c8768f4" memberName="label_HRIR_fs"
         virtualName="" explicitFocusOrder="0" pos="848 255 51 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="f7f951a1b21e1a11" memberName="TBuseDefaultHRIRs"
                virtualName="" explicitFocusOrder="0" pos="876 61 32 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="c59fb2aab2496c4e" memberName="label_DAW_fs"
         virtualName="" explicitFocusOrder="0" pos="848 279 51 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2c30657926641642" memberName="label_N_CH"
         virtualName="" explicitFocusOrder="0" pos="848 183 51 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="56ba0566c2fe39e0" memberName="CBmode"
            virtualName="" explicitFocusOrder="0" pos="816 125 86 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="a3ac98bebbbaf66" memberName="label_IR_length"
         virtualName="" explicitFocusOrder="0" pos="848 231 51 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="97b87b3a98bedb21" memberName="SL_avgCoeff"
          virtualName="" explicitFocusOrder="0" pos="805 152 96 20" min="0.0"
          max="1.0" int="0.01" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="45" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

