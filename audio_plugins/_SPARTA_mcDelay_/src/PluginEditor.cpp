/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.2.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
/*
 ==============================================================================

 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2018 - Leo McCormack.

 SPARTA is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 SPARTA is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with SPARTA.  If not, see <http://www.gnu.org/licenses/>.

 ==============================================================================
*/
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

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

    /* handle to pluginProcessor */
	hVst = ownerFilter;

    /* init OpenGL */
    openGLContext.setMultisamplingEnabled(true);
    openGLContext.attachTo(*this);

    /* grab current parameter settings */
//    SL_num_sources->setValue(pannerlib_getNumSources(hVst->hPan),dontSendNotification);
//    TB_showInputs->setToggleState(true, dontSendNotification);
//    TB_showOutputs->setToggleState(true, dontSendNotification);
//    SL_pValue->setValue(pannerlib_getDTT(hVst->hPan), dontSendNotification);


	/* Specify screen refresh rate */
    startTimer(80);//80); /*ms (40ms = 25 frames per second) */

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
        int x = 0, y = 30, width = 600, height = 370;
        Colour fillColour1 = Colour (0xff55636d), fillColour2 = Colour (0xff073642);
        Colour strokeColour = Colour (0xffa3a4a5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       312.0f - 0.0f + x,
                                       184.0f - 30.0f + y,
                                       fillColour2,
                                       592.0f - 0.0f + x,
                                       496.0f - 30.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    {
        int x = 0, y = 0, width = 600, height = 32;
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
        int x = -19, y = 0, width = 171, height = 32;
        String text (TRANS("mcEQ"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (18.80f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        int x = 279, y = 366, width = 67, height = 30;
        String text (TRANS("Presets: "));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 15, y = 320, width = 569, height = 70;
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
        int x = 31, y = 324, width = 113, height = 30;
        String text (TRANS("N Chan:"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 31, y = 356, width = 113, height = 30;
        String text (TRANS("Inputs"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 383, y = 326, width = 113, height = 30;
        String text (TRANS("Panning Window"));
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
		150, 16, 530, 11,
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
                 initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 30 600 370" fill=" radial: 312 184, 592 496, 0=ff55636d, 1=ff073642"
          hasStroke="1" stroke="1.9, mitered, butt" strokeColour="solid: ffa3a4a5"/>
    <RECT pos="0 0 600 32" fill="solid: ff073642" hasStroke="1" stroke="2.7, mitered, butt"
          strokeColour="solid: dcbdbdbd"/>
    <TEXT pos="-19 0 171 32" fill="solid: ffffffff" hasStroke="0" text="mcEQ"
          fontname="Default font" fontsize="18.800000000000000711" kerning="0"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="279 366 67 30" fill="solid: ffffffff" hasStroke="0" text="Presets: "
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
    <RECT pos="15 320 569 70" fill="solid: 13f4f4f4" hasStroke="1" stroke="0.8, mitered, butt"
          strokeColour="solid: 67a0a0a0"/>
    <TEXT pos="31 324 113 30" fill="solid: ffffffff" hasStroke="0" text="N Chan:"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
    <TEXT pos="31 356 113 30" fill="solid: ffffffff" hasStroke="0" text="Inputs"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
    <TEXT pos="383 326 113 30" fill="solid: ffffffff" hasStroke="0" text="Panning Window"
          fontname="Default font" fontsize="15" kerning="0" bold="1" italic="0"
          justification="33" typefaceStyle="Bold"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
