/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.3

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

    SL_num_beams.reset (new Slider ("new slider"));
    addAndMakeVisible (SL_num_beams.get());
    SL_num_beams->setRange (1, 64, 1);
    SL_num_beams->setSliderStyle (Slider::LinearHorizontal);
    SL_num_beams->setTextBoxStyle (Slider::TextBoxRight, false, 60, 20);
    SL_num_beams->addListener (this);

    SL_num_beams->setBounds (640, 96, 48, 20);

    CBoutputFormat.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBoutputFormat.get());
    CBoutputFormat->setEditableText (false);
    CBoutputFormat->setJustificationType (Justification::centredLeft);
    CBoutputFormat->setTextWhenNothingSelected (TRANS("ACN"));
    CBoutputFormat->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBoutputFormat->addItem (TRANS("ACN"), 1);
    CBoutputFormat->addListener (this);

    CBoutputFormat->setBounds (133, 316, 112, 20);

    CBnormalisation.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBnormalisation.get());
    CBnormalisation->setEditableText (false);
    CBnormalisation->setJustificationType (Justification::centredLeft);
    CBnormalisation->setTextWhenNothingSelected (TRANS("N3D"));
    CBnormalisation->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBnormalisation->addItem (TRANS("N3D"), 1);
    CBnormalisation->addItem (TRANS("SN3D"), 2);
    CBnormalisation->addListener (this);

    CBnormalisation->setBounds (368, 316, 112, 20);

    CBorder.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBorder.get());
    CBorder->setEditableText (false);
    CBorder->setJustificationType (Justification::centredLeft);
    CBorder->setTextWhenNothingSelected (String());
    CBorder->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBorder->addListener (this);

    CBorder->setBounds (578, 64, 112, 20);

    CBbeamType.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (CBbeamType.get());
    CBbeamType->setEditableText (false);
    CBbeamType->setJustificationType (Justification::centredLeft);
    CBbeamType->setTextWhenNothingSelected (String());
    CBbeamType->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    CBbeamType->addListener (this);

    CBbeamType->setBounds (594, 125, 96, 20);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (708, 356);


    //[Constructor] You can add your own custom stuff here..

    /* handle to pluginProcessor */
	hVst = ownerFilter;

    /* init OpenGL */
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* remove slider bit of these sliders */
    SL_num_beams->setColour(Slider::trackColourId, Colours::transparentBlack);
    SL_num_beams->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    SL_num_beams->setSliderSnapsToMousePosition(false);
 
    /* add combobox options */
    CBorder->addItem (TRANS("1st order"), BEAM_ORDER_FIRST);
    CBorder->addItem (TRANS("2nd order"), BEAM_ORDER_SECOND);
    CBorder->addItem (TRANS("3rd order"), BEAM_ORDER_THIRD);
    CBorder->addItem (TRANS("4th order"), BEAM_ORDER_FOURTH);
    CBorder->addItem (TRANS("5th order"), BEAM_ORDER_FIFTH);
    CBorder->addItem (TRANS("6th order"), BEAM_ORDER_SIXTH);
    CBorder->addItem (TRANS("7th order"), BEAM_ORDER_SEVENTH);
    CBbeamType->addItem(TRANS("Card"), BEAM_TYPE_CARDIOID);
    CBbeamType->addItem(TRANS("HyperCard"), BEAM_TYPE_HYPERCARDIOID);
    CBbeamType->addItem(TRANS("MaxEV"), BEAM_TYPE_MAX_EV);

    /* source coordinates viewport */
    addAndMakeVisible (sourceCoordsVP = new Viewport ("new viewport"));
    sourceCoordsView_handle = new inputCoordsView(ownerFilter, MAX_NUM_CHANNELS, beamformer_getNumBeams(hVst->hBeam));
    sourceCoordsVP->setViewedComponent (sourceCoordsView_handle);
    sourceCoordsVP->setScrollBarsShown (true, false);
    sourceCoordsVP->setAlwaysOnTop(true);
    sourceCoordsVP->setBounds(510, 183, 184, 155);
    sourceCoordsView_handle->setNCH(beamformer_getNumBeams(hVst->hBeam));

    /* grab current parameter settings */
    SL_num_beams->setValue(beamformer_getNumBeams(hVst->hBeam),dontSendNotification);
    CBoutputFormat->setSelectedId(beamformer_getChOrder(hVst->hBeam), dontSendNotification);
    CBnormalisation->setSelectedId(beamformer_getNormType(hVst->hBeam), dontSendNotification);
    CBorder->setSelectedId(beamformer_getBeamOrder(hVst->hBeam), dontSendNotification);
    CBbeamType->setSelectedId(beamformer_getBeamType(hVst->hBeam), dontSendNotification);

    /* create panning window */
    addAndMakeVisible (panWindow = new pannerView(ownerFilter, 480, 240));
    panWindow->setBounds (12, 58, 480, 240);
    refreshPanViewWindow = true;

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

    SL_num_beams = nullptr;
    CBoutputFormat = nullptr;
    CBnormalisation = nullptr;
    CBorder = nullptr;
    CBbeamType = nullptr;


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
        int x = 0, y = 30, width = 708, height = 326;
        Colour fillColour1 = Colour (0xff1f3b49), fillColour2 = Colour (0xff0a2931);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       376.0f - 0.0f + x,
                                       176.0f - 30.0f + y,
                                       fillColour2,
                                       704.0f - 0.0f + x,
                                       352.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 500, y = 58, width = 196, height = 32;
        Colour fillColour = Colour (0x09f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 0, y = 0, width = 708, height = 32;
        Colour fillColour = Colour (0xff05222a);
        Colour strokeColour = Colour (0xdcbdbdbd);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 500, y = 89, width = 196, height = 64;
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
        int x = 508, y = 120, width = 124, height = 30;
        String text (TRANS("Beam Type:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.50f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 12, y = 58, width = 480, height = 240;
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
        int x = 500, y = 152, width = 196, height = 194;
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
        int x = 508, y = 90, width = 180, height = 30;
        String text (TRANS("Number of Beams:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.50f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 552, y = 32, width = 108, height = 30;
        String text (TRANS("Beam Settings"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 197, y = 32, width = 163, height = 30;
        String text (TRANS("Steering Window"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 12, y = 306, width = 480, height = 40;
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
        int x = 23, y = 311, width = 145, height = 30;
        String text (TRANS("Channel Order:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 263, y = 311, width = 145, height = 30;
        String text (TRANS("Normalisation:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 500, y = 58, width = 196, height = 32;
        Colour fillColour = Colour (0x10f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 508, y = 60, width = 67, height = 30;
        String text (TRANS("Order: "));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
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
        g.setFont (Font (18.80f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 92, y = 0, width = 132, height = 32;
        String text (TRANS("Beamformer"));
        Colour fillColour = Colour (0xff4fd1ff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 554, y = 154, width = 108, height = 28;
        String text (CharPointer_UTF8 ("Azi\xc2\xb0   #   Elev\xc2\xb0"));
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
		200, 16, 530, 11,
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
        case k_warning_NinputCH:
            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
                       TRANS("/") + String(beamformer_getNumBeams(hVst->hBeam)) + TRANS(")"),
                       getBounds().getWidth()-225, 16, 530, 11,
                       Justification::centredLeft, true);
            break;
        case k_warning_NoutputCH:
            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
                       TRANS("/") + String(beamformer_getNSHrequired(hVst->hBeam)) + TRANS(")"),
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

void PluginEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == SL_num_beams.get())
    {
        //[UserSliderCode_SL_num_beams] -- add your slider handling code here..
        beamformer_setNumBeams(hVst->hBeam, (float)SL_num_beams->getValue());
        //[/UserSliderCode_SL_num_beams]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == CBoutputFormat.get())
    {
        //[UserComboBoxCode_CBoutputFormat] -- add your combo box handling code here..
        beamformer_setChOrder(hVst->hBeam, CBoutputFormat->getSelectedId());
        //[/UserComboBoxCode_CBoutputFormat]
    }
    else if (comboBoxThatHasChanged == CBnormalisation.get())
    {
        //[UserComboBoxCode_CBnormalisation] -- add your combo box handling code here..
        beamformer_setNormType(hVst->hBeam, CBnormalisation->getSelectedId());
        //[/UserComboBoxCode_CBnormalisation]
    }
    else if (comboBoxThatHasChanged == CBorder.get())
    {
        //[UserComboBoxCode_CBorder] -- add your combo box handling code here..
        beamformer_setBeamOrder(hVst->hBeam, CBorder->getSelectedId());
        //[/UserComboBoxCode_CBorder]
    }
    else if (comboBoxThatHasChanged == CBbeamType.get())
    {
        //[UserComboBoxCode_CBbeamType] -- add your combo box handling code here..
        beamformer_setBeamType(hVst->hBeam, CBbeamType->getSelectedId());
        //[/UserComboBoxCode_CBbeamType]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* update number of sources */
    sourceCoordsView_handle->setNCH(beamformer_getNumBeams(hVst->hBeam));
    SL_num_beams->setValue(beamformer_getNumBeams(hVst->hBeam),dontSendNotification);

    /* refresh pan view */
    if((refreshPanViewWindow == true) || (panWindow->getBeamIconIsClicked()) ||
        sourceCoordsView_handle->getHasASliderChanged() || hVst->getRefreshWindow()){
        panWindow->refreshPanView();
        refreshPanViewWindow = false;
        sourceCoordsView_handle->setHasASliderChange(false);
        hVst->setRefreshWindow(false);
    }

    /* display warning message, if needed */
    if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
        currentWarning = k_warning_frameSize;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumInputs() < beamformer_getNumBeams(hVst->hBeam))){
        currentWarning = k_warning_NinputCH;
        repaint(0,0,getWidth(),32);
    }
    else if ((hVst->getCurrentNumOutputs() < beamformer_getNSHrequired(hVst->hBeam))){
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
                 initialWidth="708" initialHeight="356">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 708 326" fill=" radial: 376 176, 704 352, 0=ff1f3b49, 1=ff0a2931"
          hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="500 58 196 32" fill="solid: 9f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="0 0 708 32" fill="solid: ff05222a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <RECT pos="500 89 196 64" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="508 120 124 30" fill="solid: ffffffff" hasStroke="0" text="Beam Type:"
          fontname="Default font" fontsize="1.45e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="12 58 480 240" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="500 152 196 194" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="508 90 180 30" fill="solid: ffffffff" hasStroke="0" text="Number of Beams:"
          fontname="Default font" fontsize="1.45e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="552 32 108 30" fill="solid: ffffffff" hasStroke="0" text="Beam Settings"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="197 32 163 30" fill="solid: ffffffff" hasStroke="0" text="Steering Window"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="12 306 480 40" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="23 311 145 30" fill="solid: ffffffff" hasStroke="0" text="Channel Order:"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="263 311 145 30" fill="solid: ffffffff" hasStroke="0" text="Normalisation:"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="500 58 196 32" fill="solid: 10f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="508 60 67 30" fill="solid: ffffffff" hasStroke="0" text="Order: "
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="16 0 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="1.88e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 0 132 32" fill="solid: ff4fd1ff" hasStroke="0" text="Beamformer"
          fontname="Default font" fontsize="1.8e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="554 154 108 28" fill="solid: ffffffff" hasStroke="0" text="Azi&#176;   #   Elev&#176;"
          fontname="Default font" fontsize="1.5e1" kerning="0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="2c2a2b3d0614cc94" memberName="SL_num_beams"
          virtualName="" explicitFocusOrder="0" pos="640 96 48 20" min="1"
          max="6.4e1" int="1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="63f8ff411606aafd" memberName="CBoutputFormat"
            virtualName="" explicitFocusOrder="0" pos="133 316 112 20" editable="0"
            layout="33" items="ACN" textWhenNonSelected="ACN" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="27f130362a28f1eb" memberName="CBnormalisation"
            virtualName="" explicitFocusOrder="0" pos="368 316 112 20" editable="0"
            layout="33" items="N3D&#10;SN3D" textWhenNonSelected="N3D" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="56ba0566c2fe39e0" memberName="CBorder"
            virtualName="" explicitFocusOrder="0" pos="578 64 112 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="1807ce01be358d35" memberName="CBbeamType"
            virtualName="" explicitFocusOrder="0" pos="594 125 96 20" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

