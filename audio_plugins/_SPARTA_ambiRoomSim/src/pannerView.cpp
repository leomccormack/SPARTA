/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

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
//        SourceIcons[src].setBounds(width - width*(ambi_roomsim_getSourceAzi_deg(hAmbi, src) + 180.0f)/360.f - icon_size/2.0f,
//                                   height - height*(ambi_roomsim_getSourceElev_deg(hAmbi, src) + 90.0f)/180.0f - icon_size/2.0f,
//                                   icon_size,
//                                   icon_size);
    }
    NSources = ambi_roomsim_getNumSources(hAmbi);

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
void pannerView::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0x58323e44));

    //[UserPaint] Add your own custom painting code here..
//
//    juce::Colour flareColour = juce::Colour (0x44f4f4f4), transparentColour = juce::Colour (0x00f4f4f4);
//        juce::Colour purpleColour = juce::Colour (0xffdf00c6),  purpleFlareColour = juce::Colour (0x10df00c6);

    /****** DRAW TOP VIEW ******/
//    /* Background and border */
//    float view_x = 22.0f , view_y = 72.0f;
//    float centre_x = view_x+circleRadius;
//    float centre_y = view_y+circleRadius;
//    g.setGradientFill (juce::ColourGradient (flareColour, view_x+circleRadius, view_y + circleRadius,
//                                             transparentColour, view_x+circleRadius, view_y + circleWidth, true));
//    g.fillEllipse (view_x, view_y, circleWidth, circleWidth);
//    g.setGradientFill (juce::ColourGradient (transparentColour, view_x+circleRadius, view_y + circleRadius,
//                                             purpleFlareColour, view_x+circleRadius, view_y + circleWidth, true));
//    g.fillEllipse (view_x, view_y, circleWidth, circleWidth);
//    g.setColour (purpleColour);
//    g.drawEllipse (view_x, view_y, circleWidth, circleWidth, 2.000f);
//
//    /* Receiver/origin marker and grid lines (one per metre) */
//    g.setColour(Colours::lightgrey);
//    g.setOpacity(0.5f);
//    g.fillEllipse(centre_x-iconRadius, centre_y-iconRadius, iconWidth, iconWidth);
//    g.setOpacity(0.25f);
//    g.drawLine(view_x+circleRadius, view_y, view_x+circleRadius, view_y+circleWidth,1.0f);
//    g.drawLine(view_x, view_y+circleRadius, view_x+circleWidth, view_y+circleRadius,1.0f);
//    for(int i=0; i<(int)hcompass_getSourceDistance(hCmp); i++){
//        float guideWidth = (float)i * circleWidth/hcompass_getSourceDistance(hCmp);
//        g.drawEllipse (view_x+circleRadius-guideWidth/2.0f, view_y+circleRadius-guideWidth/2.0f, guideWidth, guideWidth, 1.000f);
//    }
//
//    /* Listener and their head orientation */
//    g.setColour(purpleColour); /* NOTE THE CHANGE IN ANGLE CONVENTION! X is forwards - RIGHT-HAND-RULE! */
//    g.setOpacity(1.0f);
//    float listener_x = -circleRadius * hcompass_getListenerY(hCmp, listID)/hcompass_getSourceDistance(hCmp);
//    float listener_y = -circleRadius * hcompass_getListenerX(hCmp, listID)/hcompass_getSourceDistance(hCmp);
//    Rectangle<float> listenerIcon(centre_x-iconRadius+listener_x, centre_y-iconRadius+listener_y, iconWidth, iconWidth);
//    g.fillEllipse(listenerIcon);
//    g.setColour(Colours::lightgrey);
//    g.drawEllipse(listenerIcon.expanded(1.0f, 1.0f),1.0f);


    //[/UserPaint]
}

void pannerView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void pannerView::mouseDown (const juce::MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...

//    /* TOP VIEW */
//    float view_x = 22.0f , view_y = 72.0f;
//    float centre_x = view_x+circleRadius;
//    float centre_y = view_y+circleRadius;
//    float listener_x = -circleRadius * hcompass_getListenerY(hCmp, listID)/hcompass_getSourceDistance(hCmp);
//    float listener_y = -circleRadius * hcompass_getListenerX(hCmp, listID)/hcompass_getSourceDistance(hCmp);
//    Rectangle<int> icon_int;
//    icon_int.setBounds(centre_x-iconRadius+listener_x,
//                       centre_y-iconRadius+listener_y,
//                       iconWidth, iconWidth);
//    if(icon_int.expanded(4, 4).contains(e.getMouseDownPosition())){
//        iconIsClicked = true;
//        indexOfClickedIcon = 0; /* top */
//        return;
//    }
//
//    /* SIDE VIEW */
//    view_x = 210.0f;
//    view_y = 72.0f;
//    centre_x = view_x+circleRadius;
//    centre_y = view_y+circleRadius;
//    listener_x = -circleRadius * hcompass_getListenerY(hCmp, listID)/hcompass_getSourceDistance(hCmp);
//    listener_y = -circleRadius * hcompass_getListenerZ(hCmp, listID)/hcompass_getSourceDistance(hCmp);
//    icon_int.setBounds(centre_x-iconRadius+listener_x,
//                       centre_y-iconRadius+listener_y,
//                       iconWidth, iconWidth);
//    if(icon_int.expanded(4, 4).contains(e.getMouseDownPosition())){
//        iconIsClicked = true;
//        indexOfClickedIcon = 1; /* side */
//        return;
//    }

    //[/UserCode_mouseDown]
}

void pannerView::mouseDrag (const juce::MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
//    if(iconIsClicked){
//        Point<float> point;
//        float view_x, view_y, centre_x, centre_y;
//        switch(indexOfClickedIcon){
//            case 0: /* TOP VIEW */
//                view_x = 22.0f; view_y = 72.0f;
//                centre_x = view_x+circleRadius;
//                centre_y = view_y+circleRadius;
//                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
//                hcompass_setListenerY(hCmp, listID, ((centre_x-point.getX()) * hcompass_getSourceDistance(hCmp)/circleRadius));
//                hcompass_setListenerX(hCmp, listID, ((centre_y-point.getY()) * hcompass_getSourceDistance(hCmp)/circleRadius));
//                break;
//
//            case 1: /* SIDE VIEW */
//                view_x = 210.0f; view_y = 72.0f;
//                centre_x = view_x+circleRadius;
//                centre_y = view_y+circleRadius;
//                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
//                hcompass_setListenerY(hCmp, listID, ((centre_x-point.getX()) * hcompass_getSourceDistance(hCmp)/circleRadius));
//                hcompass_setListenerZ(hCmp, listID, ((centre_y-point.getY()) * hcompass_getSourceDistance(hCmp)/circleRadius));
//                break;
//
//        }
//    }
    //[/UserCode_mouseDrag]
}

void pannerView::mouseUp (const juce::MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
    sourceIconIsClicked = false;
    receiverIconIsClicked = false;
    //[/UserCode_mouseUp]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void pannerView::refreshPanView()
{
//    for(int src=0; src<MAX_NUM_CHANNELS; src++){
////        SourceIcons[src].setBounds(width - width*(ambi_roomsim_getSourceAzi_deg(hAmbi, src) + 180.0f)/360.f - icon_size/2.0f,
////                                   height - height*(ambi_roomsim_getSourceElev_deg(hAmbi, src) + 90.0f)/180.0f - icon_size/2.0f,
////                                   icon_size,
////                                   icon_size);
//    }
//    NSources = ambi_roomsim_getNumSources(hAmbi);
//
//    repaint();
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
  <BACKGROUND backgroundColour="58323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

