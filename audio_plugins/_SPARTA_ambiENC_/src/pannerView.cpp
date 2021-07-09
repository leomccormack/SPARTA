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

#include "pannerView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
const float icon_size = 8.0f;


//[/MiscUserDefs]

//==============================================================================
pannerView::pannerView (PluginProcessor* ownerFilter, int _width, int _height)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (480, 240);


    //[Constructor] You can add your own custom stuff here..
    hVst = ownerFilter;
    hAmbi = hVst->getFXHandle();
    width = _width;
    height = _height;

    for(int src=0; src<MAX_NUM_CHANNELS; src++){
        SourceIcons[src].setBounds(width - width*(ambi_enc_getSourceAzi_deg(hAmbi, src) + 180.0f)/360.f - icon_size/2.0f,
                                   height - height*(ambi_enc_getSourceElev_deg(hAmbi, src) + 90.0f)/180.0f - icon_size/2.0f,
                                   icon_size,
                                   icon_size);
    }
    NSources = ambi_enc_getNumSources(hAmbi);
    soloActive = false;

    //[/Constructor]
}

pannerView::~pannerView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void pannerView::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        int x = 0, y = 0, width = 480, height = 240;
        Colour fillColour1 = Colour (0xff4e4e4e), fillColour2 = Colour (0xff202020);
        Colour strokeColour = Colour (0xff9e9e9e);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       248.0f - 0.0f + x,
                                       0.0f - 0.0f + y,
                                       fillColour2,
                                       248.0f - 0.0f + x,
                                       240.0f - 0.0f + y,
                                       false));
        g.fillRect (x, y, width, height);
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    //[UserPaint] Add your own custom painting code here..


    /* Draw Grid lines and labels */
    int numGridLinesX = 8;
    int numGridLinesY = numGridLinesX / 2;
    g.setColour(Colours::white);
    g.setOpacity(0.75f);

    g.drawLine(0.0f, height / 2.0f, width, height / 2.0f, 1.0f);
    g.drawLine(width / 2.0f, 0, width / 2.0f, height, 1.0f);

    for (int i = 0; i <= numGridLinesX; i++) {
        g.setOpacity(0.1f);
        g.drawLine((float)i*width / (float)numGridLinesX, 0, (float)i*width / (float)numGridLinesX, height, 1.0f);
        g.setOpacity(0.75f);
        if (i <= numGridLinesX / 2) {
            g.drawText(String((int)(360 / 2 - i * (int)360 / numGridLinesX)) + "\xc2\xb0",
                       (float)i*width / (float)numGridLinesX, height / 2, 40, 20, Justification::centred, true);
        }
        else {
            g.drawText(String((int)(360 / 2 - i * (int)360 / numGridLinesX)) + "\xc2\xb0",
                       (float)i*width / (float)numGridLinesX - 40, height / 2, 40, 20, Justification::centred, true);
        }
    }

    for (int i = 0; i <= numGridLinesY; i++) {
        g.setOpacity(0.1f);
        g.drawLine(0, (float)i*height / (float)numGridLinesY, width, (float)i*height / (float)numGridLinesY, 1.0f);
        g.setOpacity(0.75f);
        if (i <= numGridLinesY / 2) {
            g.drawText(String((int)(180 / 2 - i * (int)180 / numGridLinesY)) + "\xc2\xb0",
                       width / 2.0f, (float)i*height / (float)numGridLinesY, 40, 20, Justification::centred, true);
        }
        else {
            g.drawText(String((int)(180 / 2 - i * (int)180 / numGridLinesY)) + "\xc2\xb0",
                       width / 2.0f, (float)i*height / (float)numGridLinesY - 20, 40, 20, Justification::centred, true);
        }
    }

    /* Draw Source icons */
    for(int src=0; src<NSources; src++){
        /* icon */
        //g.setColour(Colour::fromFloatRGBA(1.0-((float)src/(float)NSources), 0.3f, ((float)src/(float)NSources), 1.0f));
        g.setColour(Colour::fromFloatRGBA(1.0f, 0.0f, 1.0f, 0.85f));
        //setColourGradient(g, (float)src/(float)NSources);
        g.setOpacity(0.2f);
        g.fillEllipse(SourceIcons[src].expanded(8.0f,8.0f));
        g.setOpacity(0.4f);
        g.fillEllipse(SourceIcons[src].expanded(4.0f, 4.0f));
        g.setOpacity(0.85f);
        g.fillEllipse(SourceIcons[src]);
        /* icon ID */
        g.setColour(Colours::white);
        g.setOpacity(0.9f);
        g.drawText(String(src+1), SourceIcons[src].expanded(10.0f, 0.0f), Justification::centred, true); // .translated(icon_size, -icon_size)
    }

    /* Draw SOLO ACTIVE */
    if(soloActive){
        g.setColour(Colours::red);
        g.drawSingleLineText("SoloActive", 5, 15);
    }

    //[/UserPaint]
}

void pannerView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void pannerView::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    for(int i=0; i<NSources; i++){
        Rectangle<int> icon_int;
        icon_int.setBounds(SourceIcons[i].getX(),
                           SourceIcons[i].getY(),
                           SourceIcons[i].getWidth(),
                           SourceIcons[i].getHeight());
        if(icon_int.expanded(4, 4).contains(e.getMouseDownPosition())){
            sourceIconIsClicked = true;
            indexOfClickedSource = i;

            // Solo on ALT
            if(e.mods.isAltDown()){
                ambi_enc_setSourceSolo(hAmbi, i);
                soloActive = true;
            }
            break;
        }
    }
    //[/UserCode_mouseDown]
}

void pannerView::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    if(sourceIconIsClicked){
        Point<float> point;
        point.setXY((float)e.getPosition().getX()-icon_size/2.0f, (float)e.getPosition().getY()-icon_size/2.0f);
        ambi_enc_setSourceAzi_deg(hAmbi, indexOfClickedSource,
                                   ((width - (point.getX() + icon_size/2.0f))*360.0f)/width-180.0f);
        ambi_enc_setSourceElev_deg(hAmbi, indexOfClickedSource,
                                   ((height - (point.getY() + icon_size/2.0f))*180.0f)/height - 90.0f);
    }

    //[/UserCode_mouseDrag]
}

void pannerView::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
    sourceIconIsClicked = false;
    // UnSolo on ALT if not clicked on Source
    if(!e.mods.isAltDown()){
        ambi_enc_setUnSolo(hAmbi);
        soloActive = false;
    }
    repaint();
    //[/UserCode_mouseUp]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void pannerView::refreshPanView()
{
    for(int src=0; src<MAX_NUM_CHANNELS; src++){
        SourceIcons[src].setBounds(width - width*(ambi_enc_getSourceAzi_deg(hAmbi, src) + 180.0f)/360.f - icon_size/2.0f,
                                   height - height*(ambi_enc_getSourceElev_deg(hAmbi, src) + 90.0f)/180.0f - icon_size/2.0f,
                                   icon_size,
                                   icon_size);
    }
    NSources = ambi_enc_getNumSources(hAmbi);

    repaint();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="pannerView" componentName=""
                 parentClasses="public Component" constructorParams="PluginProcessor* ownerFilter, int _width, int _height"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="480" initialHeight="240">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="323e44">
    <RECT pos="0 0 480 240" fill="linear: 248 0, 248 240, 0=ff4e4e4e, 1=ff202020"
          hasStroke="1" stroke="1, mitered, butt" strokeColour="solid: ff9e9e9e"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

