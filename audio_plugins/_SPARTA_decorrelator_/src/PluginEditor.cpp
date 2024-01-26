/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.9

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//#include "saf_hoa.h"
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter), progressbar(progress)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    SL_nChannels.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_nChannels.get());
    SL_nChannels->setRange (1, 128, 1);
    SL_nChannels->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_nChannels->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    SL_nChannels->addListener (this);

    SL_nChannels->setBounds (171, 50, 65, 16);

    SL_decorAmount.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_decorAmount.get());
    SL_decorAmount->setRange (0, 1, 0.01);
    SL_decorAmount->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_decorAmount->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);
    SL_decorAmount->addListener (this);

    SL_decorAmount->setBounds (128, 73, 108, 18);

    tb_compLevel.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (tb_compLevel.get());
    tb_compLevel->setButtonText (juce::String());
    tb_compLevel->addListener (this);

    tb_compLevel->setBounds (393, 47, 23, 24);

    tb_bypassTransients.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (tb_bypassTransients.get());
    tb_bypassTransients->setButtonText (juce::String());
    tb_bypassTransients->addListener (this);

    tb_bypassTransients->setBounds (393, 72, 23, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (440, 110);


    //[Constructor] You can add your own custom stuff here..

    /* handles */
	hVst = ownerFilter;
    hDecor = hVst->getFXHandle();

    /* remove slider bit of these sliders */
    SL_nChannels->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_nChannels->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_nChannels->setSliderSnapsToMousePosition(false);

    /* init OpenGL */
#ifndef PLUGIN_EDITOR_DISABLE_OPENGL
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);
#endif

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* ProgressBar */
    progress = 0.0;
    progressbar.setBounds(getLocalBounds().getCentreX()-175, getLocalBounds().getCentreY()-17, 350, 35);
    progressbar.ProgressBar::setAlwaysOnTop(true);
    progressbar.setColour(ProgressBar::backgroundColourId, Colours::gold);
    progressbar.setColour(ProgressBar::foregroundColourId, Colours::white);

    /* grab current parameter settings */
    SL_nChannels->setValue(decorrelator_getNumberOfChannels(hDecor), dontSendNotification);
    SL_decorAmount->setValue(decorrelator_getDecorrelationAmount(hDecor), dontSendNotification);
    tb_compLevel->setToggleState((bool)decorrelator_getLevelCompensationFlag(hDecor), dontSendNotification);
    tb_bypassTransients->setToggleState((bool)decorrelator_getTransientBypassFlag(hDecor), dontSendNotification);

    /* tooltips */
    SL_nChannels->setTooltip("Number of input/output channels to decorrelate");
    SL_decorAmount->setTooltip("Amount of decorrelation; 1=fully decorrelated, 0=bypassed.");
    tb_compLevel->setTooltip("Enable/Disable energy compensation, which can help if the loudness is falling off as the decorrelation amount is increased.");
    tb_bypassTransients->setTooltip("Enable/Disable transient extractor. When enabled only the residual is decorrelated, with the extracted transients passed through without decorrelation.");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A basic multi-channel decorrelator plug-in."));

    startTimer(TIMER_GUI_RELATED, 20);

    /* warnings */
    currentWarning = k_warning_none;

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    SL_nChannels = nullptr;
    SL_decorAmount = nullptr;
    tb_compLevel = nullptr;
    tb_bypassTransients = nullptr;


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
        int x = 0, y = 70, width = 440, height = 40;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             16.0f - 0.0f + x,
                                             120.0f - 70.0f + y,
                                             fillColour2,
                                             16.0f - 0.0f + x,
                                             88.0f - 70.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 0, y = 30, width = 440, height = 40;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             64.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 438.0f, height = 31.0f;
        juce::Colour fillColour1 = juce::Colour (0xff041518), fillColour2 = juce::Colour (0xff19313f);
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             0.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             fillColour2,
                                             592.0f - 1.0f + x,
                                             32.0f - 2.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 5.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 5.000f, 2.000f);
    }

    {
        int x = 12, y = 44, width = 412, height = 54;
        juce::Colour fillColour = juce::Colour (0x08f4f4f4);
        juce::Colour strokeColour = juce::Colour (0x35a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 18, y = 43, width = 173, height = 30;
        juce::String text (TRANS ("Number of Channels:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 16, y = 1, width = 196, height = 32;
        juce::String text (TRANS ("SPARTA|"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.80f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 92, y = 1, width = 184, height = 32;
        juce::String text (TRANS ("Decorrelator"));
        juce::Colour fillColour = juce::Colour (0xffbeffba);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 440, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 438, y = 0, width = 2, height = 120;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 2, height = 120;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 108, width = 440, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 18, y = 67, width = 173, height = 30;
        juce::String text (TRANS ("Decorrelation:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 266, y = 67, width = 134, height = 30;
        juce::String text (TRANS ("Bypass Transients:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 266, y = 43, width = 158, height = 30;
        juce::String text (TRANS ("Compensate Level:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (14.50f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		198, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_frameSize:
            g.drawText(TRANS("Set frame size to multiple of ") + String(decorrelator_getFrameSize()),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_supported_fs:
            g.drawText(TRANS("Sample rate (") + String(decorrelator_getDAWsamplerate(hDecor)) + TRANS(") is unsupported"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(decorrelator_getNumberOfChannels(hDecor)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(decorrelator_getNumberOfChannels(hDecor)) + TRANS(")"),
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

    if (sliderThatWasMoved == SL_nChannels.get())
    {
        //[UserSliderCode_SL_nChannels] -- add your slider handling code here..
        decorrelator_setNumberOfChannels(hDecor, (int)SL_nChannels->getValue());
        //[/UserSliderCode_SL_nChannels]
    }
    else if (sliderThatWasMoved == SL_decorAmount.get())
    {
        //[UserSliderCode_SL_decorAmount] -- add your slider handling code here..
        decorrelator_setDecorrelationAmount(hDecor, (float)SL_decorAmount->getValue());
        //[/UserSliderCode_SL_decorAmount]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == tb_compLevel.get())
    {
        //[UserButtonCode_tb_compLevel] -- add your button handler code here..
        decorrelator_setLevelCompensationFlag(hDecor, (int)tb_compLevel->getToggleState());
        //[/UserButtonCode_tb_compLevel]
    }
    else if (buttonThatWasClicked == tb_bypassTransients.get())
    {
        //[UserButtonCode_tb_bypassTransients] -- add your button handler code here..
        decorrelator_setTransientBypassFlag(hDecor, (int)tb_bypassTransients->getToggleState());
        //[/UserButtonCode_tb_bypassTransients]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback(int timerID)
{
    switch(timerID){
        case TIMER_PROCESSING_RELATED:
            /* Handled in PluginProcessor */
            break;

        case TIMER_GUI_RELATED:
            /* Progress bar */
            if(decorrelator_getCodecStatus(hDecor)==CODEC_STATUS_INITIALISING){
                addAndMakeVisible(progressbar);
                progress = (double)decorrelator_getProgressBar0_1(hDecor);
                char text[PROGRESSBARTEXT_CHAR_LENGTH];
                decorrelator_getProgressBarText(hDecor, (char*)text);
                progressbar.setTextToDisplay(String(text));
            }
            else
                removeChildComponent(&progressbar);

            /* display warning message, if needed */
            if ((hVst->getCurrentBlockSize() % decorrelator_getFrameSize()) != 0){
                currentWarning = k_warning_frameSize;
                repaint(0,0,getWidth(),32);
            }
            else if ( !((decorrelator_getDAWsamplerate(hDecor) == 44.1e3) || (decorrelator_getDAWsamplerate(hDecor) == 48e3)) ){
                currentWarning = k_warning_supported_fs;
                repaint(0,0,getWidth(),32);
            }
            else if ((hVst->getCurrentNumInputs() < decorrelator_getNumberOfChannels(hDecor))){
                currentWarning = k_warning_NinputCH;
                repaint(0,0,getWidth(),32);
            }
            else if ((hVst->getCurrentNumOutputs() < decorrelator_getNumberOfChannels(hDecor))){
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
                 parentClasses="public AudioProcessorEditor, public MultiTimer"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter), progressbar(progress)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="440" initialHeight="110">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 70 440 40" fill="linear: 16 120, 16 88, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="0 30 440 40" fill="linear: 8 32, 8 64, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <ROUNDRECT pos="1 2 438 31" cornerSize="5.0" fill="linear: 0 32, 592 32, 0=ff041518, 1=ff19313f"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="12 44 412 54" fill="solid: 8f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 35a0a0a0"/>
    <TEXT pos="18 43 173 30" fill="solid: ffffffff" hasStroke="0" text="Number of Channels:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 1 196 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 184 32" fill="solid: ffbeffba" hasStroke="0" text="Decorrelator"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 440 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="438 0 2 120" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 120" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 108 440 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <TEXT pos="18 67 173 30" fill="solid: ffffffff" hasStroke="0" text="Decorrelation:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="266 67 134 30" fill="solid: ffffffff" hasStroke="0" text="Bypass Transients:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="266 43 158 30" fill="solid: ffffffff" hasStroke="0" text="Compensate Level:"
          fontname="Default font" fontsize="14.5" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="21d3cac663b3ac08" memberName="SL_nChannels"
          virtualName="" explicitFocusOrder="0" pos="171 50 65 16" min="1.0"
          max="128.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="d9ad5f70d2212591" memberName="SL_decorAmount"
          virtualName="" explicitFocusOrder="0" pos="128 73 108 18" min="0.0"
          max="1.0" int="0.01" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="5461719ed498c991" memberName="tb_compLevel"
                virtualName="" explicitFocusOrder="0" pos="393 47 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="943669b0479499db" memberName="tb_bypassTransients"
                virtualName="" explicitFocusOrder="0" pos="393 72 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

