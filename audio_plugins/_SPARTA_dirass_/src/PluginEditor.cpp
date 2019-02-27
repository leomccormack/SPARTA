/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

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

    CBmapMode.reset (new ComboBox (String()));
    addAndMakeVisible (CBmapMode.get());
    CBmapMode->setEditableText (false);
    CBmapMode->setJustificationType (Justification::centredLeft);
    CBmapMode->setTextWhenNothingSelected (TRANS("Default"));
    CBmapMode->setTextWhenNoChoicesAvailable (String());
    CBmapMode->addListener (this);

    CBmapMode->setBounds (112, 424, 104, 24);

    CBchFormat.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBchFormat.get());
    CBchFormat->setEditableText (false);
    CBchFormat->setJustificationType (Justification::centredLeft);
    CBchFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBchFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBchFormat->addListener (this);

    CBchFormat->setBounds (81, 488, 66, 20);

    CBnormScheme.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBnormScheme.get());
    CBnormScheme->setEditableText (false);
    CBnormScheme->setJustificationType (Justification::centredLeft);
    CBnormScheme->setTextWhenNothingSelected (TRANS("N3D"));
    CBnormScheme->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnormScheme->addListener (this);

    CBnormScheme->setBounds (152, 488, 67, 20);

    CB_hfov.reset (new ComboBox (String()));
    addAndMakeVisible (CB_hfov.get());
    CB_hfov->setEditableText (false);
    CB_hfov->setJustificationType (Justification::centredLeft);
    CB_hfov->setTextWhenNothingSelected (TRANS("Default"));
    CB_hfov->setTextWhenNoChoicesAvailable (String());
    CB_hfov->addListener (this);

    CB_hfov->setBounds (560, 392, 96, 24);

    CB_aspectRatio.reset (new ComboBox (String()));
    addAndMakeVisible (CB_aspectRatio.get());
    CB_aspectRatio->setEditableText (false);
    CB_aspectRatio->setJustificationType (Justification::centredLeft);
    CB_aspectRatio->setTextWhenNothingSelected (TRANS("Default"));
    CB_aspectRatio->setTextWhenNoChoicesAvailable (String());
    CB_aspectRatio->addListener (this);

    CB_aspectRatio->setBounds (560, 424, 96, 24);

    SLmapAvg.reset (new Slider ("new slider"));
    addAndMakeVisible (SLmapAvg.get());
    SLmapAvg->setRange (0, 1, 0.01);
    SLmapAvg->setSliderStyle (Slider::LinearHorizontal);
    SLmapAvg->setTextBoxStyle (Slider::TextBoxRight, false, 50, 20);
    SLmapAvg->setColour (Slider::textBoxTextColourId, Colours::white);
    SLmapAvg->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    SLmapAvg->addListener (this);

    SLmapAvg->setBounds (312, 456, 112, 24);

    CBinputOrder.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBinputOrder.get());
    CBinputOrder->setEditableText (false);
    CBinputOrder->setJustificationType (Justification::centredLeft);
    CBinputOrder->setTextWhenNothingSelected (TRANS("Default"));
    CBinputOrder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBinputOrder->addListener (this);

    CBinputOrder->setBounds (112, 391, 106, 20);

    s_minFreq.reset (new Slider ("new slider"));
    addAndMakeVisible (s_minFreq.get());
    s_minFreq->setRange (0, 24000, 0.1);
    s_minFreq->setSliderStyle (Slider::LinearHorizontal);
    s_minFreq->setTextBoxStyle (Slider::TextBoxRight, false, 45, 20);
    s_minFreq->addListener (this);

    s_minFreq->setBounds (560, 456, 96, 24);

    s_maxFreq.reset (new Slider ("new slider"));
    addAndMakeVisible (s_maxFreq.get());
    s_maxFreq->setRange (0, 24000, 0.1);
    s_maxFreq->setSliderStyle (Slider::LinearHorizontal);
    s_maxFreq->setTextBoxStyle (Slider::TextBoxRight, false, 45, 20);
    s_maxFreq->addListener (this);

    s_maxFreq->setBounds (560, 480, 96, 24);

    CBgridOption.reset (new ComboBox (String()));
    addAndMakeVisible (CBgridOption.get());
    CBgridOption->setEditableText (false);
    CBgridOption->setJustificationType (Justification::centredLeft);
    CBgridOption->setTextWhenNothingSelected (TRANS("Default"));
    CBgridOption->setTextWhenNoChoicesAvailable (String());
    CBgridOption->addListener (this);

    CBgridOption->setBounds (112, 456, 104, 24);

    CBupscaleOrder.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBupscaleOrder.get());
    CBupscaleOrder->setEditableText (false);
    CBupscaleOrder->setJustificationType (Justification::centredLeft);
    CBupscaleOrder->setTextWhenNothingSelected (TRANS("Default"));
    CBupscaleOrder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBupscaleOrder->addListener (this);

    CBupscaleOrder->setBounds (336, 424, 106, 20);

    TBenableReAss.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBenableReAss.get());
    TBenableReAss->setButtonText (String());
    TBenableReAss->addListener (this);

    TBenableReAss->setBounds (400, 384, 31, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (672, 530);


    //[Constructor] You can add your own custom stuff here..

    /* handle for pluginProcessor */
	hVst = ownerFilter;

    /* OpenGL init */
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* add input order options */
    CBinputOrder->addItem (TRANS("1st order"), INPUT_ORDER_FIRST);
    CBinputOrder->addItem (TRANS("2nd order"), INPUT_ORDER_SECOND);
    CBinputOrder->addItem (TRANS("3rd order"), INPUT_ORDER_THIRD);
    CBinputOrder->addItem (TRANS("4th order"), INPUT_ORDER_FOURTH);
    CBinputOrder->addItem (TRANS("5th order"), INPUT_ORDER_FIFTH);
    CBinputOrder->addItem (TRANS("6th order"), INPUT_ORDER_SIXTH);
    CBinputOrder->addItem (TRANS("7th order"), INPUT_ORDER_SEVENTH);
    
    /* add upscale order options */
    CBupscaleOrder->addItem (TRANS("1st order"), UPSCALE_ORDER_FIRST);
    CBupscaleOrder->addItem (TRANS("2nd order"), UPSCALE_ORDER_SECOND);
    CBupscaleOrder->addItem (TRANS("3rd order"), UPSCALE_ORDER_THIRD);
    CBupscaleOrder->addItem (TRANS("4th order"), UPSCALE_ORDER_FOURTH);
    CBupscaleOrder->addItem (TRANS("5th order"), UPSCALE_ORDER_FIFTH);
    CBupscaleOrder->addItem (TRANS("6th order"), UPSCALE_ORDER_SIXTH);
    CBupscaleOrder->addItem (TRANS("7th order"), UPSCALE_ORDER_SEVENTH);

    /* Add map options */
    CBmapMode->addItem (TRANS("PWD"), PM_MODE_PWD);
    
    /* Add grid options */
    CBgridOption->addItem (TRANS("Geosphere (812)"), GRID_GEOSPHERE_9);

    /* Add remaining options */
    CBchFormat->addItem(TRANS("ACN"), CH_ACN);
    CBnormScheme->addItem(TRANS("N3D"), NORM_N3D);
    CBnormScheme->addItem(TRANS("SN3D"), NORM_SN3D);
    CB_hfov->addItem(TRANS("360"), HFOV_360);
    CB_aspectRatio->addItem(TRANS("2:1"), ASPECT_RATIO_2_1);

    /* Overlay */
    previewArea.setBounds(13, 44, 646, 323);
    addAndMakeVisible (overlayIncluded = new overlay(ownerFilter));
    overlayIncluded->setAlwaysOnTop(true);
    overlayIncluded->setBounds(previewArea);

    /* fetch current configuration */
    CBinputOrder->setSelectedId(dirass_getInputOrder(hVst->hDir), dontSendNotification);
    CBmapMode->setSelectedId(dirass_getMapMode(hVst->hDir), dontSendNotification);
    CBgridOption->setSelectedId(dirass_getDisplayGridOption(hVst->hDir), dontSendNotification);
    CBupscaleOrder->setSelectedId(dirass_getUpscaleOrder(hVst->hDir), dontSendNotification);
    TBenableReAss->setToggleState((bool)dirass_getEnableDiRAss(hVst->hDir), dontSendNotification);
    s_minFreq->setValue((double)dirass_getMinFreq(hVst->hDir), dontSendNotification);
    s_maxFreq->setValue((double)dirass_getMaxFreq(hVst->hDir), dontSendNotification);
    CBchFormat->setSelectedId(dirass_getChOrder(hVst->hDir), dontSendNotification);
    CBnormScheme->setSelectedId(dirass_getNormType(hVst->hDir), dontSendNotification);
    CB_hfov->setSelectedId(dirass_getDispFOV(hVst->hDir), dontSendNotification);
    CB_aspectRatio->setSelectedId(dirass_getAspectRatio(hVst->hDir), dontSendNotification);
    SLmapAvg->setValue(dirass_getMapAvgCoeff(hVst->hDir), dontSendNotification);
    resolutionHasChanged = false;

	/* Specify screen refresh rate */
    startTimer(120);//80); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    CBmapMode = nullptr;
    CBchFormat = nullptr;
    CBnormScheme = nullptr;
    CB_hfov = nullptr;
    CB_aspectRatio = nullptr;
    SLmapAvg = nullptr;
    CBinputOrder = nullptr;
    s_minFreq = nullptr;
    s_maxFreq = nullptr;
    CBgridOption = nullptr;
    CBupscaleOrder = nullptr;
    TBenableReAss = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    overlayIncluded = nullptr;
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    {
        int x = 0, y = 30, width = 672, height = 500;
        Colour fillColour1 = Colour (0xff5b6d76), fillColour2 = Colour (0xff073642);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       336.0f - 0.0f + x,
                                       208.0f - 30.0f + y,
                                       fillColour2,
                                       360.0f - 0.0f + x,
                                       552.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 13, y = 382, width = 214, height = 138;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 227, y = 381, width = 214, height = 136;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 13, y = 382, width = 211, height = 36;
        Colour fillColour = Colour (0x08f4f4f4);
        Colour strokeColour = Colour (0x35a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 0, y = 0, width = 672, height = 32;
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
        int x = 12, y = 43, width = 648, height = 325;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 23, y = 386, width = 132, height = 30;
        String text (TRANS("Input Order:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 485, width = 132, height = 30;
        String text (TRANS("Format:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 235, y = 447, width = 132, height = 30;
        String text (TRANS("Map Avg:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 421, width = 132, height = 30;
        String text (TRANS("Map Mode:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 453, width = 132, height = 30;
        String text (TRANS("Scan Grid:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 448, y = 382, width = 208, height = 130;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 459, y = 381, width = 132, height = 30;
        String text (TRANS("Horizontal FOV:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 459, y = 413, width = 132, height = 30;
        String text (TRANS("Aspect Ratio:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 16, y = 0, width = 100, height = 32;
        String text (TRANS("SPARTA|"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.8f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 92, y = 0, width = 112, height = 32;
        String text (TRANS("DiRAss"));
        Colour fillColour = Colour (0xffb0a6e7);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 459, y = 445, width = 152, height = 30;
        String text (TRANS("Min Freq (Hz):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 459, y = 477, width = 104, height = 30;
        String text (TRANS("Max Freq (Hz):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 235, y = 415, width = 132, height = 30;
        String text (TRANS("Upscale Order:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 235, y = 383, width = 132, height = 30;
        String text (TRANS("Enable Re-Ass:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 227, y = 383, width = 211, height = 65;
        Colour fillColour = Colour (0x08f4f4f4);
        Colour strokeColour = Colour (0x35a0a0a0);
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
		195, 16, 530, 11,
		Justification::centredLeft, true);

  
    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(FRAME_SIZE),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(dirass_getSamplingRate(hVst->hDir)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(dirass_getNSHrequired(hVst->hDir)) + TRANS(")"),
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
        overlayIncluded->setAlwaysOnTop(true);
        overlayIncluded->setBounds(previewArea);
        overlayIncluded->resized();
    }
	repaint();
    //[/UserResized]
}

void PluginEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBmapMode.get())
    {
        //[UserComboBoxCode_CBmapMode] -- add your combo box handling code here..
        dirass_setMapMode(hVst->hDir, CBmapMode->getSelectedId());
        //[/UserComboBoxCode_CBmapMode]
    }
    else if (comboBoxThatHasChanged == CBchFormat.get())
    {
        //[UserComboBoxCode_CBchFormat] -- add your combo box handling code here..
        dirass_setChOrder(hVst->hDir, CBchFormat->getSelectedId());
        //[/UserComboBoxCode_CBchFormat]
    }
    else if (comboBoxThatHasChanged == CBnormScheme.get())
    {
        //[UserComboBoxCode_CBnormScheme] -- add your combo box handling code here..
        dirass_setNormType(hVst->hDir, CBnormScheme->getSelectedId());
        //[/UserComboBoxCode_CBnormScheme]
    }
    else if (comboBoxThatHasChanged == CB_hfov.get())
    {
        //[UserComboBoxCode_CB_hfov] -- add your combo box handling code here..
        dirass_setDispFOV(hVst->hDir, CB_hfov->getSelectedId());
        //[/UserComboBoxCode_CB_hfov]
    }
    else if (comboBoxThatHasChanged == CB_aspectRatio.get())
    {
        //[UserComboBoxCode_CB_aspectRatio] -- add your combo box handling code here..
        dirass_setAspectRatio(hVst->hDir, CB_aspectRatio->getSelectedId());
        //[/UserComboBoxCode_CB_aspectRatio]
    }
    else if (comboBoxThatHasChanged == CBinputOrder.get())
    {
        //[UserComboBoxCode_CBinputOrder] -- add your combo box handling code here..
        dirass_setInputOrder(hVst->hDir, CBinputOrder->getSelectedId());
        //[/UserComboBoxCode_CBinputOrder]
    }
    else if (comboBoxThatHasChanged == CBgridOption.get())
    {
        //[UserComboBoxCode_CBgridOption] -- add your combo box handling code here..
        dirass_setDisplayGridOption(hVst->hDir, CBgridOption->getSelectedId());
        //[/UserComboBoxCode_CBgridOption]
    }
    else if (comboBoxThatHasChanged == CBupscaleOrder.get())
    {
        //[UserComboBoxCode_CBupscaleOrder] -- add your combo box handling code here..
        dirass_setUpscaleOrder(hVst->hDir, CBupscaleOrder->getSelectedId());
        //[/UserComboBoxCode_CBupscaleOrder]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == SLmapAvg.get())
    {
        //[UserSliderCode_SLmapAvg] -- add your slider handling code here..
        dirass_setMapAvgCoeff(hVst->hDir, (float)SLmapAvg->getValue());
        //[/UserSliderCode_SLmapAvg]
    }
    else if (sliderThatWasMoved == s_minFreq.get())
    {
        //[UserSliderCode_s_minFreq] -- add your slider handling code here..
        dirass_setMinFreq(hVst->hDir, (float)s_minFreq->getValue());
        //[/UserSliderCode_s_minFreq]
    }
    else if (sliderThatWasMoved == s_maxFreq.get())
    {
        //[UserSliderCode_s_maxFreq] -- add your slider handling code here..
        dirass_setMaxFreq(hVst->hDir, (float)s_maxFreq->getValue());
        //[/UserSliderCode_s_maxFreq]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == TBenableReAss.get())
    {
        //[UserButtonCode_TBenableReAss] -- add your button handler code here..
        dirass_setEnableDiRAss(hVst->hDir, (int)TBenableReAss->getToggleState());
        //[/UserButtonCode_TBenableReAss]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
#ifndef __APPLE__
	/* Some parameters shouldn't be enabled if playback is ongoing */
	if (hVst->getIsPlaying())
		CBinputOrder->setEnabled(false);
    ADD OTHERS HERE
	else {
		CBinputOrder->setEnabled(true);
		dirass_checkReInit(hVst->hDir);
	}
#endif

    /* refresh the powermap display */
    if ((overlayIncluded != nullptr) && (hVst->isPlaying)) {
        float* dirs_deg, *pmap;
        int nDirs, pmapReady, pmapWidth, hfov, aspectRatio;
        pmapReady = dirass_getPmap(hVst->hDir, &dirs_deg, &pmap, &nDirs, &pmapWidth, &hfov, &aspectRatio);
        if(pmapReady){
            overlayIncluded->refreshPowerMap(dirs_deg, pmap, nDirs, pmapWidth, hfov, aspectRatio);
        }
        if(overlayIncluded->getFinishedRefresh()){
            dirass_requestPmapUpdate(hVst->hDir);
        }
    }
    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ( !((dirass_getSamplingRate(hVst->hDir) == 44.1e3) || (dirass_getSamplingRate(hVst->hDir) == 48e3)) ){
        currentWarning = k_warning_supported_fs;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < dirass_getNSHrequired(hVst->hDir))){
        currentWarning = k_warning_NinputCH;
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
                 snapActive="1" snapShown="1" overlayOpacity="0.33" fixedSize="1"
                 initialWidth="672" initialHeight="530">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 672 500" fill=" radial: 336 208, 360 552, 0=ff5b6d76, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="13 382 214 138" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="227 381 214 136" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="13 382 211 36" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 35a0a0a0"/>
    <RECT pos="0 0 672 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <RECT pos="12 43 648 325" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="23 386 132 30" fill="solid: ffffffff" hasStroke="0" text="Input Order:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 485 132 30" fill="solid: ffffffff" hasStroke="0" text="Format:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="235 447 132 30" fill="solid: ffffffff" hasStroke="0" text="Map Avg:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 421 132 30" fill="solid: ffffffff" hasStroke="0" text="Map Mode:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 453 132 30" fill="solid: ffffffff" hasStroke="0" text="Scan Grid:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="448 382 208 130" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="459 381 132 30" fill="solid: ffffffff" hasStroke="0" text="Horizontal FOV:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="459 413 132 30" fill="solid: ffffffff" hasStroke="0" text="Aspect Ratio:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 0 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.80000000000000071054" kerning="0.0"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 0 112 32" fill="solid: ffb0a6e7" hasStroke="0" text="DiRAss"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="459 445 152 30" fill="solid: ffffffff" hasStroke="0" text="Min Freq (Hz):"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="459 477 104 30" fill="solid: ffffffff" hasStroke="0" text="Max Freq (Hz):"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="235 415 132 30" fill="solid: ffffffff" hasStroke="0" text="Upscale Order:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="235 383 132 30" fill="solid: ffffffff" hasStroke="0" text="Enable Re-Ass:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="227 383 211 65" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 35a0a0a0"/>
  </BACKGROUND>
  <COMBOBOX name="" id="787134d7259eea10" memberName="CBmapMode" virtualName=""
            explicitFocusOrder="0" pos="112 424 104 24" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <COMBOBOX name="new combo box" id="a36915795f16ceb6" memberName="CBchFormat"
            virtualName="" explicitFocusOrder="0" pos="81 488 66 20" editable="0"
            layout="33" items="" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="e10be54628a6df43" memberName="CBnormScheme"
            virtualName="" explicitFocusOrder="0" pos="152 488 67 20" editable="0"
            layout="33" items="" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="" id="e69fd08ce7960e5e" memberName="CB_hfov" virtualName=""
            explicitFocusOrder="0" pos="560 392 96 24" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <COMBOBOX name="" id="757b635652d2e8ab" memberName="CB_aspectRatio" virtualName=""
            explicitFocusOrder="0" pos="560 424 96 24" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <SLIDER name="new slider" id="d9acd6687ea4c8b5" memberName="SLmapAvg"
          virtualName="" explicitFocusOrder="0" pos="312 456 112 24" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="0.0" max="1.0" int="0.01000000000000000021"
          style="LinearHorizontal" textBoxPos="TextBoxRight" textBoxEditable="1"
          textBoxWidth="50" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="a465903000494955" memberName="CBinputOrder"
            virtualName="" explicitFocusOrder="0" pos="112 391 106 20" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="905f4ab0adab1f4f" memberName="s_minFreq"
          virtualName="" explicitFocusOrder="0" pos="560 456 96 24" min="0.0"
          max="24000.0" int="0.10000000000000000555" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="45"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="3aad5000f228ef1b" memberName="s_maxFreq"
          virtualName="" explicitFocusOrder="0" pos="560 480 96 24" min="0.0"
          max="24000.0" int="0.10000000000000000555" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="45"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="" id="6daf8adec965e9f2" memberName="CBgridOption" virtualName=""
            explicitFocusOrder="0" pos="112 456 104 24" editable="0" layout="33"
            items="" textWhenNonSelected="Default" textWhenNoItems=""/>
  <COMBOBOX name="new combo box" id="5fec20e10170996c" memberName="CBupscaleOrder"
            virtualName="" explicitFocusOrder="0" pos="336 424 106 20" editable="0"
            layout="33" items="" textWhenNonSelected="Default" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="new toggle button" id="de15dc1399751b46" memberName="TBenableReAss"
                virtualName="" explicitFocusOrder="0" pos="400 384 31 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
