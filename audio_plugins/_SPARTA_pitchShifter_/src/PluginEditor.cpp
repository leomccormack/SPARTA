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

//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (PluginProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter),progressbar(progress)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    s_pitchShiftFactor.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (s_pitchShiftFactor.get());
    s_pitchShiftFactor->setRange (0.1, 4, 0.01);
    s_pitchShiftFactor->setSliderStyle (juce::Slider::LinearHorizontal);
    s_pitchShiftFactor->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    s_pitchShiftFactor->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff5c5d5e));
    s_pitchShiftFactor->setColour (juce::Slider::trackColourId, juce::Colour (0xff315b6e));
    s_pitchShiftFactor->setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    s_pitchShiftFactor->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x00ffffff));
    s_pitchShiftFactor->addListener (this);

    s_pitchShiftFactor->setBounds (360, 40, 120, 32);

    SL_num_channels.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (SL_num_channels.get());
    SL_num_channels->setRange (1, 128, 1);
    SL_num_channels->setSliderStyle (juce::Slider::LinearHorizontal);
    SL_num_channels->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    SL_num_channels->addListener (this);

    SL_num_channels->setBounds (163, 47, 48, 20);

    CBfftsize.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBfftsize.get());
    CBfftsize->setEditableText (false);
    CBfftsize->setJustificationType (juce::Justification::centredLeft);
    CBfftsize->setTextWhenNothingSelected (juce::String());
    CBfftsize->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBfftsize->addListener (this);

    CBfftsize->setBounds (98, 78, 112, 19);

    CBoversampling.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (CBoversampling.get());
    CBoversampling->setEditableText (false);
    CBoversampling->setJustificationType (juce::Justification::centredLeft);
    CBoversampling->setTextWhenNothingSelected (juce::String());
    CBoversampling->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    CBoversampling->addListener (this);

    CBoversampling->setBounds (361, 78, 112, 19);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (500, 112);


    //[Constructor] You can add your own custom stuff here..
	hVst = ownerFilter;
    hPS = hVst->getFXHandle();

    /* Look and Feel */
    LAF.setDefaultColours();
    setLookAndFeel(&LAF);

    /* remove slider bit of these sliders */
    SL_num_channels->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_channels->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_channels->setSliderSnapsToMousePosition(false);

    /* add combo box options */
    CBfftsize->addItem(TRANS("512"),   PITCH_SHIFTER_FFTSIZE_512);
    CBfftsize->addItem(TRANS("1024"),  PITCH_SHIFTER_FFTSIZE_1024);
    CBfftsize->addItem(TRANS("2048"),  PITCH_SHIFTER_FFTSIZE_2048);
    CBfftsize->addItem(TRANS("4096"),  PITCH_SHIFTER_FFTSIZE_4096);
    CBfftsize->addItem(TRANS("8192"),  PITCH_SHIFTER_FFTSIZE_8192);
    CBfftsize->addItem(TRANS("16384"), PITCH_SHIFTER_FFTSIZE_16384);
    CBoversampling->addItem(TRANS("2"),  PITCH_SHIFTER_OSAMP_2);
    CBoversampling->addItem(TRANS("4"),  PITCH_SHIFTER_OSAMP_4);
    CBoversampling->addItem(TRANS("8"),  PITCH_SHIFTER_OSAMP_8);
    CBoversampling->addItem(TRANS("16"), PITCH_SHIFTER_OSAMP_16);
    CBoversampling->addItem(TRANS("32"), PITCH_SHIFTER_OSAMP_32);

	/* fetch current configuration */
    SL_num_channels->setValue(pitch_shifter_getNCHrequired(hPS));
    s_pitchShiftFactor->setRange(PITCH_SHIFTER_MIN_SHIFT_FACTOR, PITCH_SHIFTER_MAX_SHIFT_FACTOR, 0.01f);
	s_pitchShiftFactor->setValue(pitch_shifter_getPitchShiftFactor(hPS), dontSendNotification);
    CBfftsize->setSelectedId((int)pitch_shifter_getFFTSizeOption(hPS), dontSendNotification);
    CBoversampling->setSelectedId((int)pitch_shifter_getOSampOption(hPS), dontSendNotification);

    /* tooltips */
    s_pitchShiftFactor->setTooltip("Pitch shift factor, 1: no change, 0.5: down one octave, 2: up one octave");
    CBfftsize->setTooltip("FFT size used by the algorithm. Higher values permit more drastic pitch shifts, but at the cost of increased CPU and latency");
    CBoversampling->setTooltip("Oversampling factor used by the algorithm. Higher values improve signal fidelity, but at the cost of increased CPU and latency");

    /* Plugin description */
    pluginDescription.reset (new juce::ComboBox ("new combo box"));
    addAndMakeVisible (pluginDescription.get());
    pluginDescription->setBounds (0, 0, 200, 32);
    pluginDescription->setAlpha(0.0f);
    pluginDescription->setEnabled(false);
    pluginDescription->setTooltip(TRANS("A simple multi-channel pitch shifter, based on the phase-vocoder approach."));

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

    s_pitchShiftFactor = nullptr;
    SL_num_channels = nullptr;
    CBfftsize = nullptr;
    CBoversampling = nullptr;


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
        int x = 0, y = 70, width = 498, height = 42;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             120.0f - 70.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             96.0f - 70.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 10, y = 71, width = 476, height = 33;
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
        int x = 0, y = 30, width = 530, height = 40;
        juce::Colour fillColour1 = juce::Colour (0xff19313f), fillColour2 = juce::Colour (0xff041518);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             8.0f - 0.0f + x,
                                             32.0f - 30.0f + y,
                                             fillColour2,
                                             8.0f - 0.0f + x,
                                             56.0f - 30.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = 1.0f, y = 2.0f, width = 498.0f, height = 31.0f;
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
        int x = 10, y = 40, width = 213, height = 32;
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
        int x = 222, y = 40, width = 264, height = 32;
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
        int x = 218, y = 41, width = 139, height = 30;
        juce::String text (TRANS ("Pitch Shift Factor:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 16, y = 41, width = 152, height = 30;
        juce::String text (TRANS ("Number of Channels:"));
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
        int x = 92, y = 1, width = 124, height = 32;
        juce::String text (TRANS ("PitchShifter"));
        juce::Colour fillColour = juce::Colour (0xff8dff86);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (18.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 0, y = 0, width = 532, height = 2;
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
        int x = 498, y = 3, width = 6, height = 117;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 110, width = 512, height = 2;
        juce::Colour strokeColour = juce::Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 15, y = 71, width = 96, height = 35;
        juce::String text (TRANS ("FFT Size:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 230, y = 71, width = 96, height = 35;
        juce::String text (TRANS ("Oversampling:"));
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
		190, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
        case k_warning_none:
            break;
        case k_warning_NCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(pitch_shifter_getNCHrequired(hPS)) + TRANS(")"),
                       getBounds().getWidth()-225, 6, 530, 11,
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

    if (sliderThatWasMoved == s_pitchShiftFactor.get())
    {
        //[UserSliderCode_s_pitchShiftFactor] -- add your slider handling code here..
        pitch_shifter_setPitchShiftFactor(hPS, (float)s_pitchShiftFactor->getValue());
        //[/UserSliderCode_s_pitchShiftFactor]
    }
    else if (sliderThatWasMoved == SL_num_channels.get())
    {
        //[UserSliderCode_SL_num_channels] -- add your slider handling code here..
        pitch_shifter_setNumChannels(hPS, (int)SL_num_channels->getValue());
        //[/UserSliderCode_SL_num_channels]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBfftsize.get())
    {
        //[UserComboBoxCode_CBfftsize] -- add your combo box handling code here..
        pitch_shifter_setFFTSizeOption(hPS, (PITCH_SHIFTER_FFTSIZE_OPTIONS)CBfftsize->getSelectedId());
        //[/UserComboBoxCode_CBfftsize]
    }
    else if (comboBoxThatHasChanged == CBoversampling.get())
    {
        //[UserComboBoxCode_CBoversampling] -- add your combo box handling code here..
        pitch_shifter_setOSampOption(hPS, (PITCH_SHIFTER_OSAMP_OPTIONS)CBoversampling->getSelectedId());
        //[/UserComboBoxCode_CBoversampling]
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
            /* parameters whos values can change internally should be periodically refreshed */
            SL_num_channels->setValue(pitch_shifter_getNCHrequired(hPS));

            /* Progress bar */
            if(pitch_shifter_getCodecStatus(hPS)==CODEC_STATUS_INITIALISING){
                addAndMakeVisible(progressbar);
                progress = (double)pitch_shifter_getProgressBar0_1(hPS);
                char text[PROGRESSBARTEXT_CHAR_LENGTH];
                pitch_shifter_getProgressBarText(hPS, (char*)text);
                progressbar.setTextToDisplay(String(text));
            }
            else
                removeChildComponent(&progressbar);

            /* display warning message, if needed */
            if ((hVst->getCurrentNumInputs() < pitch_shifter_getNCHrequired(hPS))){
                currentWarning = k_warning_NCH;
                repaint(0,0,getWidth(),32);
            }
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
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter),progressbar(progress)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="500" initialHeight="112">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 70 498 42" fill="linear: 8 120, 8 96, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <RECT pos="10 71 476 33" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <RECT pos="0 30 530 40" fill="linear: 8 32, 8 56, 0=ff19313f, 1=ff041518"
          hasStroke="0"/>
    <ROUNDRECT pos="1 2 498 31" cornerSize="5.0" fill="linear: 0 32, 528 32, 0=ff041518, 1=ff19313f"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="10 40 213 32" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <RECT pos="222 40 264 32" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <TEXT pos="218 41 139 30" fill="solid: ffffffff" hasStroke="0" text="Pitch Shift Factor:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="16 41 152 30" fill="solid: ffffffff" hasStroke="0" text="Number of Channels:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 124 32" fill="solid: ff8dff86" hasStroke="0" text="PitchShifter"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 532 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 120" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="498 3 6 117" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 110 512 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <TEXT pos="15 71 96 35" fill="solid: ffffffff" hasStroke="0" text="FFT Size:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="230 71 96 35" fill="solid: ffffffff" hasStroke="0" text="Oversampling:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="ace036a85eec9703" memberName="s_pitchShiftFactor"
          virtualName="" explicitFocusOrder="0" pos="360 40 120 32" bkgcol="ff5c5d5e"
          trackcol="ff315b6e" textboxtext="ffffffff" textboxbkgd="ffffff"
          min="0.1" max="4.0" int="0.01" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="2c2a2b3d0614cc94" memberName="SL_num_channels"
          virtualName="" explicitFocusOrder="0" pos="163 47 48 20" min="1.0"
          max="128.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="aeb0b2f644784061" memberName="CBfftsize"
            virtualName="" explicitFocusOrder="0" pos="98 78 112 19" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="98bc13619e0f8706" memberName="CBoversampling"
            virtualName="" explicitFocusOrder="0" pos="361 78 112 19" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

