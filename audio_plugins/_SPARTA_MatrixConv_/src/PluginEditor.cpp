/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.4

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
    : AudioProcessorEditor(ownerFilter), fileChooser ("File", File(), true, false, false,
      "*.wav;", String(),
      "Load .wav File")
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    TBenablePartConv.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (TBenablePartConv.get());
    TBenablePartConv->setButtonText (String());
    TBenablePartConv->addListener (this);

    TBenablePartConv->setBounds (261, 146, 26, 26);

    label_hostBlockSize.reset (new Label ("new label",
                                          String()));
    addAndMakeVisible (label_hostBlockSize.get());
    label_hostBlockSize->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_hostBlockSize->setJustificationType (Justification::centredLeft);
    label_hostBlockSize->setEditable (false, false, false);
    label_hostBlockSize->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_hostBlockSize->setColour (TextEditor::textColourId, Colours::black);
    label_hostBlockSize->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_hostBlockSize->setBounds (451, 73, 60, 20);

    label_NFilters.reset (new Label ("new label",
                                     String()));
    addAndMakeVisible (label_NFilters.get());
    label_NFilters->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_NFilters->setJustificationType (Justification::centred);
    label_NFilters->setEditable (false, false, false);
    label_NFilters->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_NFilters->setColour (TextEditor::textColourId, Colours::black);
    label_NFilters->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_NFilters->setBounds (237, 98, 48, 20);

    label_filterLength.reset (new Label ("new label",
                                         String()));
    addAndMakeVisible (label_filterLength.get());
    label_filterLength->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_filterLength->setJustificationType (Justification::centredLeft);
    label_filterLength->setEditable (false, false, false);
    label_filterLength->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_filterLength->setColour (TextEditor::textColourId, Colours::black);
    label_filterLength->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_filterLength->setBounds (451, 98, 60, 20);

    label_hostfs.reset (new Label ("new label",
                                   String()));
    addAndMakeVisible (label_hostfs.get());
    label_hostfs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_hostfs->setJustificationType (Justification::centredLeft);
    label_hostfs->setEditable (false, false, false);
    label_hostfs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_hostfs->setColour (TextEditor::textColourId, Colours::black);
    label_hostfs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_hostfs->setBounds (451, 150, 60, 20);

    label_filterfs.reset (new Label ("new label",
                                     String()));
    addAndMakeVisible (label_filterfs.get());
    label_filterfs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_filterfs->setJustificationType (Justification::centredLeft);
    label_filterfs->setEditable (false, false, false);
    label_filterfs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_filterfs->setColour (TextEditor::textColourId, Colours::black);
    label_filterfs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_filterfs->setBounds (451, 124, 60, 20);

    SL_num_inputs.reset (new Slider ("new slider"));
    addAndMakeVisible (SL_num_inputs.get());
    SL_num_inputs->setRange (1, 64, 1);
    SL_num_inputs->setSliderStyle (Slider::LinearHorizontal);
    SL_num_inputs->setTextBoxStyle (Slider::TextBoxRight, false, 55, 20);
    SL_num_inputs->addListener (this);

    SL_num_inputs->setBounds (237, 46, 48, 20);

    label_MatrixNInputs.reset (new Label ("new label",
                                          String()));
    addAndMakeVisible (label_MatrixNInputs.get());
    label_MatrixNInputs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_MatrixNInputs->setJustificationType (Justification::centred);
    label_MatrixNInputs->setEditable (false, false, false);
    label_MatrixNInputs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_MatrixNInputs->setColour (TextEditor::textColourId, Colours::black);
    label_MatrixNInputs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_MatrixNInputs->setBounds (451, 45, 60, 20);

    label_MatrixNoutputs.reset (new Label ("new label",
                                           String()));
    addAndMakeVisible (label_MatrixNoutputs.get());
    label_MatrixNoutputs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_MatrixNoutputs->setJustificationType (Justification::centred);
    label_MatrixNoutputs->setEditable (false, false, false);
    label_MatrixNoutputs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_MatrixNoutputs->setColour (TextEditor::textColourId, Colours::black);
    label_MatrixNoutputs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_MatrixNoutputs->setBounds (368, 45, 60, 20);

    label_NOutputs.reset (new Label ("new label",
                                     String()));
    addAndMakeVisible (label_NOutputs.get());
    label_NOutputs->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_NOutputs->setJustificationType (Justification::centred);
    label_NOutputs->setEditable (false, false, false);
    label_NOutputs->setColour (Label::outlineColourId, Colour (0x68a3a2a2));
    label_NOutputs->setColour (TextEditor::textColourId, Colours::black);
    label_NOutputs->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_NOutputs->setBounds (237, 124, 48, 20);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (530, 184);


    //[Constructor] You can add your own custom stuff here..
	hVst = ownerFilter;
    hMC = hVst->getFXHandle();

    /* remove slider bit of these sliders */
    SL_num_inputs->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_inputs->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_inputs->setSliderSnapsToMousePosition(false);

    /* file loader */
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
    fileChooser.setBounds (70, 72, 214, 20);
    formatManager.registerBasicFormats();
    durationInSeconds = 0.0f;
    if(hVst->getWavDirectory() != TRANS("no_file")){
        fileChooser.setCurrentFile(hVst->getWavDirectory(), true);
        loadWavFile();
    }

	/* fetch current configuration */
    TBenablePartConv->setToggleState((bool)matrixconv_getEnablePart(hMC), dontSendNotification);
    SL_num_inputs->setValue(matrixconv_getNumInputChannels(hMC), dontSendNotification);
    label_NFilters->setJustificationType (Justification::centred);

    /* tooltips */
    fileChooser.setTooltip("Load multi-channel *.wav file here. If want to do a 4 x 8 matrix convolution, then the number of inputs should be set to 8, and you should load a 32 channel .wav file, where the filters are stacked on top of each other. This will map the 8 inputs to the 4 outputs, as dictated by your 4 x 8 filter matrix. Also bear in mind, the maximum number of channels for .wav files is 1024 (e.g. 32 x 32)");
    TBenablePartConv->setTooltip("Enable/Disable partitioned convolution. Try both and use whichever uses less CPU. The end result is the same.");
    label_hostBlockSize->setTooltip("The current host block size. The higher the block size, the less CPU the plug-in will use.");
    label_NFilters->setTooltip("The number of filters in the loaded wav file. If the number filters is not divisable by the number of input channels, then the plugin will set the number of outputs to 0 and do nothing. Also bear in mind, the maximum number of channels for .wav files is 1024 (e.g. 32 x 32).");
    label_filterLength->setTooltip("Filter length in seconds. the longer this is the more your CPU will cry.");
    label_hostfs->setTooltip("The host samplerate. This should match the filter samplerate.");
    label_filterfs->setTooltip("The filter samplerate. This should match the host samplerate.");
    SL_num_inputs->setTooltip("The number of input channels.");
    label_MatrixNInputs->setTooltip("The number of input channels.");
    label_MatrixNoutputs->setTooltip("The number of output channels. If this is 0, then you loaded an incorrect number of filters for this number of inputs.");
    label_NOutputs->setTooltip("The number of output channels. If this is 0, then you loaded an incorrect number of filters for this number of inputs.");

    /* Specify screen refresh rate */
    startTimer(30); /*ms (40ms = 25 frames per second) */

    /* warnings */
    currentWarning = k_warning_none;

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    TBenablePartConv = nullptr;
    label_hostBlockSize = nullptr;
    label_NFilters = nullptr;
    label_filterLength = nullptr;
    label_hostfs = nullptr;
    label_filterfs = nullptr;
    SL_num_inputs = nullptr;
    label_MatrixNInputs = nullptr;
    label_MatrixNoutputs = nullptr;
    label_NOutputs = nullptr;


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
        int x = 0, y = 30, width = 530, height = 65;
        Colour fillColour1 = Colour (0xff1c3949), fillColour2 = Colour (0xff071e22);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       8.0f - 0.0f + x,
                                       32.0f - 30.0f + y,
                                       fillColour2,
                                       8.0f - 0.0f + x,
                                       88.0f - 30.0f + y,
                                       false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 304, y = 40, width = 216, height = 29;
        Colour fillColour = Colour (0x10c7c7c7);
        Colour strokeColour = Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 0, y = 95, width = 530, height = 89;
        Colour fillColour1 = Colour (0xff1c3949), fillColour2 = Colour (0xff071e22);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       8.0f - 0.0f + x,
                                       184.0f - 95.0f + y,
                                       fillColour2,
                                       8.0f - 0.0f + x,
                                       136.0f - 95.0f + y,
                                       false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 8, y = 39, width = 288, height = 137;
        Colour fillColour = Colour (0x10c7c7c7);
        Colour strokeColour = Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        float x = 1.0f, y = 2.0f, width = 528.0f, height = 31.0f;
        Colour fillColour1 = Colour (0xff061c20), fillColour2 = Colour (0xff1c3949);
        Colour strokeColour = Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
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
        int x = 304, y = 68, width = 216, height = 108;
        Colour fillColour = Colour (0x10c7c7c7);
        Colour strokeColour = Colour (0x1fffffff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 16, y = 1, width = 100, height = 32;
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
        int x = 92, y = 1, width = 124, height = 32;
        String text (TRANS("MatrixConv"));
        Colour fillColour = Colour (0xffe9ff00);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 532, height = 2;
        Colour strokeColour = Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 184;
        Colour strokeColour = Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 528, y = 0, width = 2, height = 184;
        Colour strokeColour = Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 182, width = 532, height = 2;
        Colour strokeColour = Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 312, y = 66, width = 115, height = 30;
        String text (TRANS("Host Block Size:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 16, y = 92, width = 232, height = 30;
        String text (TRANS("Number of Filters in .wav File:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 312, y = 92, width = 200, height = 30;
        String text (TRANS("Filter Length (s):"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 312, y = 118, width = 128, height = 30;
        String text (TRANS("Filter Samplerate:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 312, y = 144, width = 144, height = 30;
        String text (TRANS("Host Samplerate:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 16, y = 144, width = 256, height = 30;
        String text (TRANS("Enable Partitioned Convolution:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 16, y = 40, width = 224, height = 30;
        String text (TRANS("Number of Input Channels:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 16, y = 66, width = 88, height = 30;
        String text (TRANS("Filters:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 16, y = 118, width = 232, height = 31;
        String text (TRANS("Number of Output Channels:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 312, y = 39, width = 115, height = 30;
        String text (TRANS("Matrix:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 436, y = 40, width = 115, height = 30;
        String text (TRANS("x"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..

    /* display version/date built */
	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		186, 16, 530, 11,
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

void PluginEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == TBenablePartConv.get())
    {
        //[UserButtonCode_TBenablePartConv] -- add your button handler code here..
        matrixconv_setEnablePart(hMC, (int)TBenablePartConv->getToggleState());
        //[/UserButtonCode_TBenablePartConv]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PluginEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == SL_num_inputs.get())
    {
        //[UserSliderCode_SL_num_inputs] -- add your slider handling code here..
        matrixconv_setNumInputChannels(hMC, (int)SL_num_inputs->getValue());
        //[/UserSliderCode_SL_num_inputs]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */
    label_hostBlockSize->setText(String(matrixconv_getHostBlockSize(hMC)), dontSendNotification);
    label_NFilters->setText(String(matrixconv_getNfilters(hMC)), dontSendNotification);
    //label_filterLength->setText(String(matrixconv_getFilterLength(hMC)), dontSendNotification);
    label_filterLength->setText(String(durationInSeconds), dontSendNotification);
    label_hostfs->setText(String(matrixconv_getHostFs(hMC)), dontSendNotification);
    label_filterfs->setText(String(matrixconv_getFilterFs(hMC)), dontSendNotification);
    label_MatrixNInputs->setText(String(matrixconv_getNumInputChannels(hMC)), dontSendNotification);
    label_MatrixNoutputs->setText(String(matrixconv_getNumOutputChannels(hMC)), dontSendNotification);
    label_NOutputs->setText(String(matrixconv_getNumOutputChannels(hMC)), dontSendNotification);

    /* display warning message, if needed */
    if((matrixconv_getNfilters(hMC) != 0) && (matrixconv_getHostFs(hMC)!=matrixconv_getFilterFs(hMC))){
        currentWarning = k_warning_sampleRate_missmatch;
        repaint(0,0,getWidth(),32);
    }
    else if(matrixconv_getNumInputChannels(hMC)>MATRIXCONV_MAX_NUM_CHANNELS){
        currentWarning = k_warning_nInputs_more_than_64;
        repaint(0,0,getWidth(),32);
    }
    else if(matrixconv_getNumOutputChannels(hMC)>MATRIXCONV_MAX_NUM_CHANNELS){
        currentWarning = k_warning_nOutputs_more_than_64;
        repaint(0,0,getWidth(),32);
    }
    else{
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
                 parentClasses="public AudioProcessorEditor, public Timer, private FilenameComponentListener"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter), fileChooser (&quot;File&quot;, File(), true, false, false,&#10;                       &quot;*.wav;&quot;, String(),&#10;                       &quot;Load .wav File&quot;)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="530" initialHeight="184">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 530 65" fill="linear: 8 32, 8 88, 0=ff1c3949, 1=ff071e22"
          hasStroke="0"/>
    <RECT pos="304 40 216 29" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <RECT pos="0 95 530 89" fill="linear: 8 184, 8 136, 0=ff1c3949, 1=ff071e22"
          hasStroke="0"/>
    <RECT pos="8 39 288 137" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <ROUNDRECT pos="1 2 528 31" cornerSize="5.0" fill="linear: 0 32, 528 32, 0=ff061c20, 1=ff1c3949"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="304 68 216 108" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 124 32" fill="solid: ffe9ff00" hasStroke="0" text="MatrixConv"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 532 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 184" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="528 0 2 184" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 182 532 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <TEXT pos="312 66 115 30" fill="solid: ffffffff" hasStroke="0" text="Host Block Size:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 92 232 30" fill="solid: ffffffff" hasStroke="0" text="Number of Filters in .wav File:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="312 92 200 30" fill="solid: ffffffff" hasStroke="0" text="Filter Length (s):"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="312 118 128 30" fill="solid: ffffffff" hasStroke="0" text="Filter Samplerate:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="312 144 144 30" fill="solid: ffffffff" hasStroke="0" text="Host Samplerate:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 144 256 30" fill="solid: ffffffff" hasStroke="0" text="Enable Partitioned Convolution:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 40 224 30" fill="solid: ffffffff" hasStroke="0" text="Number of Input Channels:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 66 88 30" fill="solid: ffffffff" hasStroke="0" text="Filters:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 118 232 31" fill="solid: ffffffff" hasStroke="0" text="Number of Output Channels:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="312 39 115 30" fill="solid: ffffffff" hasStroke="0" text="Matrix:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="436 40 115 30" fill="solid: ffffffff" hasStroke="0" text="x"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
  </BACKGROUND>
  <TOGGLEBUTTON name="new toggle button" id="abe48e7ad8d6ea52" memberName="TBenablePartConv"
                virtualName="" explicitFocusOrder="0" pos="261 146 26 26" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="167c5975ece5bfaa" memberName="label_hostBlockSize"
         virtualName="" explicitFocusOrder="0" pos="451 73 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="d9e906d62b5da562" memberName="label_NFilters"
         virtualName="" explicitFocusOrder="0" pos="237 98 48 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="7d9ebaead925d1e6" memberName="label_filterLength"
         virtualName="" explicitFocusOrder="0" pos="451 98 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b5990c279ece4f98" memberName="label_hostfs"
         virtualName="" explicitFocusOrder="0" pos="451 150 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5ca688f8365be60e" memberName="label_filterfs"
         virtualName="" explicitFocusOrder="0" pos="451 124 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="2c2a2b3d0614cc94" memberName="SL_num_inputs"
          virtualName="" explicitFocusOrder="0" pos="237 46 48 20" min="1.0"
          max="64.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="55" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="12474ab47e0dd793" memberName="label_MatrixNInputs"
         virtualName="" explicitFocusOrder="0" pos="451 45 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="b181725bd20bd1e9" memberName="label_MatrixNoutputs"
         virtualName="" explicitFocusOrder="0" pos="368 45 60 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="fbe948204f97884b" memberName="label_NOutputs"
         virtualName="" explicitFocusOrder="0" pos="237 124 48 20" outlineCol="68a3a2a2"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

