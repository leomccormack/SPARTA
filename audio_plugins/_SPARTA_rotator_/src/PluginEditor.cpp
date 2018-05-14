/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.2.1

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

    addAndMakeVisible (s_yaw = new Slider ("new slider"));
    s_yaw->setRange (-180, 180, 0.01);
    s_yaw->setSliderStyle (Slider::LinearHorizontal);
    s_yaw->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    s_yaw->setColour (Slider::textBoxTextColourId, Colours::white);
    s_yaw->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_yaw->addListener (this);

    s_yaw->setBounds (176, 80, 120, 32);

    addAndMakeVisible (s_pitch = new Slider ("new slider"));
    s_pitch->setRange (-90, 90, 0.01);
    s_pitch->setSliderStyle (Slider::LinearVertical);
    s_pitch->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    s_pitch->setColour (Slider::textBoxTextColourId, Colours::white);
    s_pitch->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_pitch->addListener (this);

    s_pitch->setBounds (304, 40, 96, 112);

    addAndMakeVisible (s_roll = new Slider ("new slider"));
    s_roll->setRange (-90, 90, 0.01);
    s_roll->setSliderStyle (Slider::LinearVertical);
    s_roll->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    s_roll->setColour (Slider::textBoxTextColourId, Colours::white);
    s_roll->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s_roll->addListener (this);

    s_roll->setBounds (416, 40, 96, 112);

    addAndMakeVisible (t_flipYaw = new ToggleButton ("new toggle button"));
    t_flipYaw->setButtonText (String());
    t_flipYaw->addListener (this);

    t_flipYaw->setBounds (226, 112, 23, 24);

    addAndMakeVisible (t_flipPitch = new ToggleButton ("new toggle button"));
    t_flipPitch->setButtonText (String());
    t_flipPitch->addListener (this);

    t_flipPitch->setBounds (356, 112, 23, 24);

    addAndMakeVisible (t_flipRoll = new ToggleButton ("new toggle button"));
    t_flipRoll->setButtonText (String());
    t_flipRoll->addListener (this);

    t_flipRoll->setBounds (468, 112, 23, 24);

    addAndMakeVisible (te_oscport = new TextEditor ("new text editor"));
    te_oscport->setMultiLine (false);
    te_oscport->setReturnKeyStartsNewLine (false);
    te_oscport->setReadOnly (true);
    te_oscport->setScrollbarsShown (true);
    te_oscport->setCaretVisible (false);
    te_oscport->setPopupMenuEnabled (true);
    te_oscport->setColour (TextEditor::textColourId, Colours::white);
    te_oscport->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));
    te_oscport->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    te_oscport->setText (TRANS("9000"));

    te_oscport->setBounds (96, 116, 64, 24);

    addAndMakeVisible (CBoutputFormat = new ComboBox ("new combo box"));
    CBoutputFormat->setEditableText (false);
    CBoutputFormat->setJustificationType (Justification::centredLeft);
    CBoutputFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBoutputFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBoutputFormat->addItem (TRANS("ACN"), 1);
    CBoutputFormat->addListener (this);

    CBoutputFormat->setBounds (96, 52, 64, 20);

    addAndMakeVisible (CBnorm = new ComboBox ("new combo box"));
    CBnorm->setEditableText (false);
    CBnorm->setJustificationType (Justification::centredLeft);
    CBnorm->setTextWhenNothingSelected (TRANS("N3D"));
    CBnorm->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnorm->addItem (TRANS("N3D"), 1);
    CBnorm->addItem (TRANS("SN3D"), 2);
    CBnorm->addSeparator();
    CBnorm->addListener (this);

    CBnorm->setBounds (96, 84, 64, 20);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (530, 160);


    //[Constructor] You can add your own custom stuff here..
	hVst = ownerFilter;

	/* fetch current configuration */
	s_yaw->setValue(rotator_getYaw(hVst->hRot), dontSendNotification);
    s_pitch->setValue(rotator_getPitch(hVst->hRot), dontSendNotification);
    s_roll->setValue(rotator_getRoll(hVst->hRot), dontSendNotification);
    t_flipYaw->setToggleState((bool)rotator_getFlipYaw(hVst->hRot), dontSendNotification);
    t_flipPitch->setToggleState((bool)rotator_getFlipPitch(hVst->hRot), dontSendNotification);
    t_flipRoll->setToggleState((bool)rotator_getFlipRoll(hVst->hRot), dontSendNotification);

	// specify here on which UDP port number to receive incoming OSC messages
    connect(9000);

    showingFrameSizeWarning = false;

	// tell the component to listen for OSC messages
	addListener(this);

    startTimer(80); /*ms (40ms = 25 frames per second) */

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    s_yaw = nullptr;
    s_pitch = nullptr;
    s_roll = nullptr;
    t_flipYaw = nullptr;
    t_flipPitch = nullptr;
    t_flipRoll = nullptr;
    te_oscport = nullptr;
    CBoutputFormat = nullptr;
    CBnorm = nullptr;


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
        int x = 0, y = 30, width = 530, height = 130;
        Colour fillColour1 = Colour (0xff55636d), fillColour2 = Colour (0xff073642);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       280.0f - 0.0f + x,
                                       104.0f - 30.0f + y,
                                       fillColour2,
                                       528.0f - 0.0f + x,
                                       160.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 13, y = 40, width = 155, height = 112;
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
        int x = 0, y = 0, width = 530, height = 32;
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
        int x = 176, y = 40, width = 344, height = 112;
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
        int x = -10, y = 0, width = 122, height = 32;
        String text (TRANS("Rotator"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.80f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 221, y = 45, width = 63, height = 30;
        String text (TRANS("\\ypr[0]"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 319, y = 45, width = 63, height = 30;
        String text (TRANS("Pitch"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 429, y = 45, width = 63, height = 30;
        String text (TRANS("Roll"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 448, y = 125, width = 63, height = 30;
        String text (TRANS("+/-"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 336, y = 125, width = 63, height = 30;
        String text (TRANS("+/-"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 205, y = 125, width = 63, height = 30;
        String text (TRANS("+/-"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 20, y = 108, width = 91, height = 35;
        String text (TRANS("OSC port:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 189, y = 45, width = 60, height = 30;
        String text (TRANS("Yaw"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 357, y = 45, width = 63, height = 30;
        String text (TRANS("\\ypr[1]"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 461, y = 45, width = 63, height = 30;
        String text (TRANS("\\ypr[2]"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (11.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 20, y = 44, width = 91, height = 35;
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
        int x = 20, y = 76, width = 91, height = 35;
        String text (TRANS("Norm:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..

	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		110, 16, 530, 11,
		Justification::centredLeft, true);


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

    if (sliderThatWasMoved == s_yaw)
    {
        //[UserSliderCode_s_yaw] -- add your slider handling code here..
        rotator_setYaw(hVst->hRot, (float)s_yaw->getValue());
        //[/UserSliderCode_s_yaw]
    }
    else if (sliderThatWasMoved == s_pitch)
    {
        //[UserSliderCode_s_pitch] -- add your slider handling code here..
        rotator_setPitch(hVst->hRot, (float)s_pitch->getValue());
        //[/UserSliderCode_s_pitch]
    }
    else if (sliderThatWasMoved == s_roll)
    {
        //[UserSliderCode_s_roll] -- add your slider handling code here..
        rotator_setRoll(hVst->hRot, (float)s_roll->getValue());
        //[/UserSliderCode_s_roll]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == t_flipYaw)
    {
        //[UserButtonCode_t_flipYaw] -- add your button handler code here..
        rotator_setFlipYaw(hVst->hRot, (int)t_flipYaw->getToggleState());
        //[/UserButtonCode_t_flipYaw]
    }
    else if (buttonThatWasClicked == t_flipPitch)
    {
        //[UserButtonCode_t_flipPitch] -- add your button handler code here..
        rotator_setFlipPitch(hVst->hRot, (int)t_flipPitch->getToggleState());
        //[/UserButtonCode_t_flipPitch]
    }
    else if (buttonThatWasClicked == t_flipRoll)
    {
        //[UserButtonCode_t_flipRoll] -- add your button handler code here..
        rotator_setFlipRoll(hVst->hRot, (int)t_flipRoll->getToggleState());
        //[/UserButtonCode_t_flipRoll]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PluginEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBoutputFormat)
    {
        //[UserComboBoxCode_CBoutputFormat] -- add your combo box handling code here..
        rotator_setChOrder(hVst->hRot, CBoutputFormat->getSelectedId());
        //[/UserComboBoxCode_CBoutputFormat]
    }
    else if (comboBoxThatHasChanged == CBnorm)
    {
        //[UserComboBoxCode_CBnorm] -- add your combo box handling code here..
        rotator_setNormType(hVst->hRot, CBnorm->getSelectedId());
        //[/UserComboBoxCode_CBnorm]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{

}



//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public AudioProcessorEditor, public Timer, private OSCReceiver, private OSCReceiver::Listener&lt;OSCReceiver::RealtimeCallback&gt;"
                 constructorParams="PluginProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="530" initialHeight="160">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 530 130" fill=" radial: 280 104, 528 160, 0=ff55636d, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="13 40 155 112" fill="solid: 17c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <RECT pos="0 0 530 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <RECT pos="176 40 344 112" fill="solid: 17c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <TEXT pos="-10 0 122 32" fill="solid: ffffffff" hasStroke="0" text="Rotator"
          fontname="Default font" fontsize="18.80000000000000071054" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="221 45 63 30" fill="solid: ffffffff" hasStroke="0" text="\ypr[0]"
          fontname="Default font" fontsize="11.00000000000000000000" kerning="0.00000000000000000000"
          bold="0" italic="0" justification="36"/>
    <TEXT pos="319 45 63 30" fill="solid: ffffffff" hasStroke="0" text="Pitch"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="429 45 63 30" fill="solid: ffffffff" hasStroke="0" text="Roll"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="448 125 63 30" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="336 125 63 30" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="205 125 63 30" fill="solid: ffffffff" hasStroke="0" text="+/-"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="20 108 91 35" fill="solid: ffffffff" hasStroke="0" text="OSC port:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="189 45 60 30" fill="solid: ffffffff" hasStroke="0" text="Yaw"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="357 45 63 30" fill="solid: ffffffff" hasStroke="0" text="\ypr[1]"
          fontname="Default font" fontsize="11.00000000000000000000" kerning="0.00000000000000000000"
          bold="0" italic="0" justification="36"/>
    <TEXT pos="461 45 63 30" fill="solid: ffffffff" hasStroke="0" text="\ypr[2]"
          fontname="Default font" fontsize="11.00000000000000000000" kerning="0.00000000000000000000"
          bold="0" italic="0" justification="36"/>
    <TEXT pos="20 44 91 35" fill="solid: ffffffff" hasStroke="0" text="CH Order:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="20 76 91 35" fill="solid: ffffffff" hasStroke="0" text="Norm:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="ace036a85eec9703" memberName="s_yaw" virtualName=""
          explicitFocusOrder="0" pos="176 80 120 32" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="-180.00000000000000000000" max="180.00000000000000000000"
          int="0.01000000000000000021" style="LinearHorizontal" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <SLIDER name="new slider" id="9af7dd86cd139d85" memberName="s_pitch"
          virtualName="" explicitFocusOrder="0" pos="304 40 96 112" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="-90.00000000000000000000" max="90.00000000000000000000"
          int="0.01000000000000000021" style="LinearVertical" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <SLIDER name="new slider" id="b5d39bb257b3289a" memberName="s_roll" virtualName=""
          explicitFocusOrder="0" pos="416 40 96 112" textboxtext="ffffffff"
          textboxbkgd="ffffff" min="-90.00000000000000000000" max="90.00000000000000000000"
          int="0.01000000000000000021" style="LinearVertical" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="ac47b63592b1d4cf" memberName="t_flipYaw"
                virtualName="" explicitFocusOrder="0" pos="226 112 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="c58241ee52766d62" memberName="t_flipPitch"
                virtualName="" explicitFocusOrder="0" pos="356 112 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="717e9536768dfd8c" memberName="t_flipRoll"
                virtualName="" explicitFocusOrder="0" pos="468 112 23 24" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTEDITOR name="new text editor" id="1799da9e8cf495d6" memberName="te_oscport"
              virtualName="" explicitFocusOrder="0" pos="96 116 64 24" textcol="ffffffff"
              bkgcol="ffffff" outlinecol="0" initialText="9000" multiline="0"
              retKeyStartsLine="0" readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <COMBOBOX name="new combo box" id="63f8ff411606aafd" memberName="CBoutputFormat"
            virtualName="" explicitFocusOrder="0" pos="96 52 64 20" editable="0"
            layout="33" items="ACN" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="2d87659a256dc599" memberName="CBnorm"
            virtualName="" explicitFocusOrder="0" pos="96 84 64 20" editable="0"
            layout="33" items="N3D&#10;SN3D&#10;" textWhenNonSelected="N3D"
            textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
