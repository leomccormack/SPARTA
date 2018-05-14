/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.0

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

    addAndMakeVisible (SL_covAvg = new Slider ("new slider"));
    SL_covAvg->setRange (0, 1, 0.001);
    SL_covAvg->setSliderStyle (Slider::LinearHorizontal);
    SL_covAvg->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    SL_covAvg->addListener (this);

    SL_covAvg->setBounds (144, 80, 150, 24);

    addAndMakeVisible (SL_paramAvg = new Slider ("new slider"));
    SL_paramAvg->setRange (0, 1, 0.001);
    SL_paramAvg->setSliderStyle (Slider::LinearHorizontal);
    SL_paramAvg->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    SL_paramAvg->addListener (this);

    SL_paramAvg->setBounds (144, 112, 150, 24);

    addAndMakeVisible (SL_panWidth = new Slider ("new slider"));
    SL_panWidth->setRange (0, 1, 0.001);
    SL_panWidth->setSliderStyle (Slider::LinearHorizontal);
    SL_panWidth->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    SL_panWidth->addListener (this);

    SL_panWidth->setBounds (144, 144, 150, 24);

    addAndMakeVisible (SL_pValueCoeff = new Slider ("new slider"));
    SL_pValueCoeff->setRange (0, 1, 0.001);
    SL_pValueCoeff->setSliderStyle (Slider::LinearHorizontal);
    SL_pValueCoeff->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    SL_pValueCoeff->addListener (this);

    SL_pValueCoeff->setBounds (144, 176, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (320, 220);


    //[Constructor] You can add your own custom stuff here..

    /* handle to pluginProcessor */
	hVst = ownerFilter;

    /* init OpenGL */
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* grab current parameter settings */
    SL_covAvg->setValue(upmix_getCovAvg(hVst->hUpmx), dontSendNotification);
    SL_paramAvg->setValue(upmix_getParamAvgCoeff(hVst->hUpmx), dontSendNotification);
    SL_panWidth->setValue(upmix_getScaleDoAwidth(hVst->hUpmx), dontSendNotification);
    SL_pValueCoeff->setValue(upmix_getPValueCoeff(hVst->hUpmx), dontSendNotification);

	/* Specify screen refresh rate */
    startTimer(80);//80); /*ms (40ms = 25 frames per second) */

    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    SL_covAvg = nullptr;
    SL_paramAvg = nullptr;
    SL_panWidth = nullptr;
    SL_pValueCoeff = nullptr;


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
        int x = 0, y = 30, width = 320, height = 190;
        Colour fillColour1 = Colour (0xff55636d), fillColour2 = Colour (0xff073642);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       160.0f - 0.0f + x,
                                       136.0f - 30.0f + y,
                                       fillColour2,
                                       320.0f - 0.0f + x,
                                       216.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 11, y = 43, width = 296, height = 29;
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
        int x = 0, y = 0, width = 320, height = 32;
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
        int x = -32, y = 0, width = 184, height = 32;
        String text (TRANS("UpMix"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.80f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 16, y = 41, width = 288, height = 32;
        String text (TRANS("Stereo (L+R)  to 5.x (L+R+C+Ls+Rs)"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 19, y = 75, width = 173, height = 30;
        String text (TRANS("Covarience Avg:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 107, width = 133, height = 30;
        String text (TRANS("Parameter Avg:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 139, width = 133, height = 30;
        String text (TRANS("Panning Width:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 19, y = 171, width = 133, height = 30;
        String text (TRANS("pValue Coeff:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 11, y = 72, width = 296, height = 136;
        Colour fillColour = Colour (0x13f4f4f4);
        Colour strokeColour = Colour (0x67a0a0a0);
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
		120, 16, 530, 11,
		Justification::centredLeft, true);

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

    if (sliderThatWasMoved == SL_covAvg)
    {
        //[UserSliderCode_SL_covAvg] -- add your slider handling code here..
        upmix_setCovAvg(hVst->hUpmx, (float)SL_covAvg->getValue());
        //[/UserSliderCode_SL_covAvg]
    }
    else if (sliderThatWasMoved == SL_paramAvg)
    {
        //[UserSliderCode_SL_paramAvg] -- add your slider handling code here..
        upmix_setParamAvgCoeff(hVst->hUpmx, (float)SL_paramAvg->getValue());
        //[/UserSliderCode_SL_paramAvg]
    }
    else if (sliderThatWasMoved == SL_panWidth)
    {
        //[UserSliderCode_SL_panWidth] -- add your slider handling code here..
        upmix_setScaleDoAwidth(hVst->hUpmx, (float)SL_panWidth->getValue());
        //[/UserSliderCode_SL_panWidth]
    }
    else if (sliderThatWasMoved == SL_pValueCoeff)
    {
        //[UserSliderCode_SL_pValueCoeff] -- add your slider handling code here..
        upmix_setPValueCoeff(hVst->hUpmx, (float)SL_pValueCoeff->getValue());
        //[/UserSliderCode_SL_pValueCoeff]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
//    /*  */
//    sourceCoordsView_handle->setNCH(pannerlib_getNumSources(hVst->hPan));
//    loudspeakerCoordsView_handle->setNCH(pannerlib_getNumLoudspeakers(hVst->hPan));
//    SL_num_sources->setValue(pannerlib_getNumSources(hVst->hPan),dontSendNotification);
//    SL_num_loudspeakers->setValue(pannerlib_getNumLoudspeakers(hVst->hPan),dontSendNotification);
//
//    /* refresh pan view */
//    if((refreshPanViewWindow == true) || (panWindow->getSourceIconIsClicked()) ||
//       sourceCoordsView_handle->getHasASliderChanged() || loudspeakerCoordsView_handle->getHasASliderChanged()){
//        panWindow->refreshPanView();
//        refreshPanViewWindow = false;
//        sourceCoordsView_handle->setHasASliderChange(false);
//        loudspeakerCoordsView_handle->setHasASliderChange(false);
//    }
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
                 initialWidth="320" initialHeight="220">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 320 190" fill=" radial: 160 136, 320 216, 0=ff55636d, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="11 43 296 29" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <RECT pos="0 0 320 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <TEXT pos="-32 0 184 32" fill="solid: ffffffff" hasStroke="0" text="UpMix"
          fontname="Default font" fontsize="18.80000000000000071054" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="16 41 288 32" fill="solid: ffffffff" hasStroke="0" text="Stereo (L+R)  to 5.x (L+R+C+Ls+Rs)"
          fontname="Default font" fontsize="14.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="19 75 173 30" fill="solid: ffffffff" hasStroke="0" text="Covarience Avg:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 107 133 30" fill="solid: ffffffff" hasStroke="0" text="Parameter Avg:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 139 133 30" fill="solid: ffffffff" hasStroke="0" text="Panning Width:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="19 171 133 30" fill="solid: ffffffff" hasStroke="0" text="pValue Coeff:"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="1" italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="11 72 296 136" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="a2bf4fd84213ca1b" memberName="SL_covAvg"
          virtualName="" explicitFocusOrder="0" pos="144 80 150 24" min="0.00000000000000000000"
          max="1.00000000000000000000" int="0.00100000000000000002" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="new slider" id="2380afc562542fb3" memberName="SL_paramAvg"
          virtualName="" explicitFocusOrder="0" pos="144 112 150 24" min="0.00000000000000000000"
          max="1.00000000000000000000" int="0.00100000000000000002" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="new slider" id="7e3f141127379039" memberName="SL_panWidth"
          virtualName="" explicitFocusOrder="0" pos="144 144 150 24" min="0.00000000000000000000"
          max="1.00000000000000000000" int="0.00100000000000000002" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <SLIDER name="new slider" id="88c1132ea72a3cdf" memberName="SL_pValueCoeff"
          virtualName="" explicitFocusOrder="0" pos="144 176 150 24" min="0.00000000000000000000"
          max="1.00000000000000000000" int="0.00100000000000000002" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
