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
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (530, 160);


    //[Constructor] You can add your own custom stuff here..
	hVst = ownerFilter;
    hMC = hVst->getFXHandle();

    /* add combo box options */

	/* fetch current configuration */

    /* tooltips */

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
        int x = 0, y = 95, width = 530, height = 65;
        Colour fillColour1 = Colour (0xff1c3949), fillColour2 = Colour (0xff071e22);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       8.0f - 0.0f + x,
                                       160.0f - 95.0f + y,
                                       fillColour2,
                                       8.0f - 0.0f + x,
                                       112.0f - 95.0f + y,
                                       false));
        g.fillRect (x, y, width, height);
    }

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
                                       80.0f - 30.0f + y,
                                       false));
        g.fillRect (x, y, width, height);
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
        int x = 10, y = 127, width = 167, height = 25;
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
        int x = 10, y = 40, width = 167, height = 32;
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
        int x = 10, y = 71, width = 167, height = 57;
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
        int x = 176, y = 40, width = 344, height = 112;
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
        int x = 189, y = 45, width = 115, height = 30;
        String text (TRANS("Something"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
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
        String text (TRANS("MultiConv"));
        Colour fillColour = Colour (0xff7deeff);
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
        int x = 0, y = 0, width = 2, height = 160;
        Colour strokeColour = Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 528, y = 0, width = 2, height = 160;
        Colour strokeColour = Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 158, width = 532, height = 2;
        Colour strokeColour = Colour (0xffb9b9b9);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    //[UserPaint] Add your own custom painting code here..

    /* display version/date built */
	g.setColour(Colours::white);
	g.setFont(Font(11.00f, Font::plain));
	g.drawText(TRANS("Ver ") + JucePlugin_VersionString + BUILD_VER_SUFFIX + TRANS(", Build Date ") + __DATE__ + TRANS(" "),
		175, 16, 530, 11,
		Justification::centredLeft, true);

    /* display warning message */
    g.setColour(Colours::red);
    g.setFont(Font(11.00f, Font::plain));
    switch (currentWarning){
//        case k_warning_none:
//            break;
//        case k_warning_frameSize:
//            g.drawText(TRANS("Set frame size to multiple of ") + String(FRAME_SIZE),
//                       getBounds().getWidth()-225, 6, 530, 11,
//                       Justification::centredLeft, true);
//            break;
//        case k_warning_NinputCH:
//            g.drawText(TRANS("Insufficient number of input channels (") + String(hVst->getTotalNumInputChannels()) +
//                       TRANS("/") + String(rotator_getNSHrequired(hRot)) + TRANS(")"),
//                       getBounds().getWidth()-225, 6, 530, 11,
//                       Justification::centredLeft, true);
//            break;
//        case k_warning_NoutputCH:
//            g.drawText(TRANS("Insufficient number of output channels (") + String(hVst->getTotalNumOutputChannels()) +
//                       TRANS("/") + String(rotator_getNSHrequired(hRot)) + TRANS(")"),
//                       getBounds().getWidth()-225, 6, 530, 11,
//                       Justification::centredLeft, true);
//            break;
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



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::timerCallback()
{
    /* parameters whos values can change internally should be periodically refreshed */

//    /* display warning message, if needed */
//    if ((hVst->getCurrentBlockSize() % FRAME_SIZE) != 0){
//        currentWarning = k_warning_frameSize;
//        repaint(0,0,getWidth(),32);
//    }
//    else if ((hVst->getCurrentNumInputs() < rotator_getNSHrequired(hRot))){
//        currentWarning = k_warning_NinputCH;
//        repaint(0,0,getWidth(),32);
//    }
//    else if ((hVst->getCurrentNumOutputs() < rotator_getNSHrequired(hRot))){
//        currentWarning = k_warning_NoutputCH;
//        repaint(0,0,getWidth(),32);
//    }
//    else if(currentWarning){
//        currentWarning = k_warning_none;
//        repaint(0,0,getWidth(),32);
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
                 variableInitialisers="AudioProcessorEditor(ownerFilter)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="530" initialHeight="160">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 95 530 65" fill="linear: 8 160, 8 112, 0=ff1c3949, 1=ff071e22"
          hasStroke="0"/>
    <RECT pos="0 30 530 65" fill="linear: 8 32, 8 80, 0=ff1c3949, 1=ff071e22"
          hasStroke="0"/>
    <ROUNDRECT pos="1 2 528 31" cornerSize="5.0" fill="linear: 0 32, 528 32, 0=ff061c20, 1=ff1c3949"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ffb9b9b9"/>
    <RECT pos="10 127 167 25" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <RECT pos="10 40 167 32" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <RECT pos="10 71 167 57" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <RECT pos="176 40 344 112" fill="solid: 10c7c7c7" hasStroke="1" stroke="1.1, mitered, butt"
          strokeColour="solid: 1fffffff"/>
    <TEXT pos="189 45 115 30" fill="solid: ffffffff" hasStroke="0" text="Something"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="16 1 100 32" fill="solid: ffffffff" hasStroke="0" text="SPARTA|"
          fontname="Default font" fontsize="18.8" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="92 1 124 32" fill="solid: ff7deeff" hasStroke="0" text="MultiConv"
          fontname="Default font" fontsize="18.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <RECT pos="0 0 532 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 0 2 160" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="528 0 2 160" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
    <RECT pos="0 158 532 2" fill="solid: 61a52a" hasStroke="1" stroke="2, mitered, butt"
          strokeColour="solid: ffb9b9b9"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

