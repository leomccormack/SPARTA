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
const float iconWidth = 8.0f;
const float iconRadius = iconWidth/2.0f;
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
    topOrSideView = TOP_VIEW; /* default */

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

    Rectangle<float> srcIcon, recIcon;
    const float room_pixels = 220;
    float room_dims_pixels[3], room_dims_m[3];
    room_dims_m[0] = ambi_roomsim_getRoomDimX(hAmbi);
    room_dims_m[1] = ambi_roomsim_getRoomDimY(hAmbi);
    room_dims_m[2] = ambi_roomsim_getRoomDimZ(hAmbi);

    /* Scaling factor to convert metres to pixels */
    float scale = room_pixels/MAX(MAX(room_dims_m[0], room_dims_m[1]), room_dims_m[2]);
    room_dims_pixels[0] = room_dims_m[0]*scale;
    room_dims_pixels[1] = room_dims_m[1]*scale;
    room_dims_pixels[2] = room_dims_m[2]*scale;

    /****** DRAW TOP VIEW *****/
    /* Background and border */
    float view_x = 22.0f , view_y = 22.0f;
    float centre_x = view_x+room_dims_pixels[1]/2.0f;
    float centre_y = view_y+room_dims_pixels[0]/2.0f;
    g.setColour(Colours::lightgrey);
    g.drawRect(view_x, view_y, room_dims_pixels[1], room_dims_pixels[0], 2.000f);

    /* Origin marker and grid lines (one per metre) */
    g.setColour(Colours::lightgrey);
//    g.setOpacity(0.35f);
//    g.fillEllipse(centre_x-iconRadius, centre_y-iconRadius, iconWidth, iconWidth);
    g.setOpacity(0.25f);
    for(int i=0; i<=(int)room_dims_m[1]; i++){
        /* Verticle lines */
        float line_x = view_x + room_dims_pixels[1] - (float)i*room_dims_pixels[1]/room_dims_m[1];
        g.drawLine (line_x, view_y, line_x, view_y+room_dims_pixels[0], 1.000f);
    }
    for(int i=0; i<=(int)room_dims_m[0]; i++){
        /* Horizontal lines*/
        float line_y = view_y + room_dims_pixels[0] - (float)i*room_dims_pixels[0]/room_dims_m[0];
        g.drawLine (view_x, line_y, view_x+room_dims_pixels[1], line_y, 1.000f);
    }

    /* Source icons */
    g.setColour(Colours::orange);
    g.setOpacity(0.5f);
    for(int src=0; src<ambi_roomsim_getNumSources(hAmbi); src++){
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getSourceY(hAmbi, src));
        float point_y = view_y + room_dims_pixels[0] - scale*(ambi_roomsim_getSourceX(hAmbi, src));
        srcIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        g.fillEllipse(srcIcon);
    }

    /* Receiver icons */
    g.setColour(Colours::magenta);
    g.setOpacity(0.5f);
    for(int rec=0; rec<ambi_roomsim_getNumReceivers(hAmbi); rec++){
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getReceiverY(hAmbi, rec));
        float point_y = view_y + room_dims_pixels[0] - scale*(ambi_roomsim_getReceiverX(hAmbi, rec));
        recIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        g.fillEllipse(recIcon);
    }


    /****** DRAW SIDE VIEW *****/
    /* Background and border */
    view_x = 22.0f; view_y = 262.0f;
    centre_x = view_x+room_dims_pixels[1]/2.0f;
    centre_y = view_y+room_dims_pixels[2]/2.0f;
    g.setColour(Colours::lightgrey);
    g.drawRect(view_x, view_y, room_dims_pixels[1], room_dims_pixels[2], 2.000f);

    /* Origin marker and grid lines (one per metre) */
    g.setColour(Colours::lightgrey);
//    g.setOpacity(0.35f);
//    g.fillEllipse(centre_x-iconRadius, centre_y-iconRadius, iconWidth, iconWidth);
    g.setOpacity(0.25f);
    for(int i=0; i<=(int)room_dims_m[1]; i++){
        /* Verticle lines */
        float line_x = view_x + room_dims_pixels[1] - (float)i*room_dims_pixels[1]/room_dims_m[1];
        g.drawLine (line_x, view_y, line_x, view_y+room_dims_pixels[2], 1.000f);
    }
    for(int i=0; i<=(int)room_dims_m[2]; i++){
        /* Horizontal lines*/
        float line_y = view_y + room_dims_pixels[2] - (float)i*room_dims_pixels[2]/room_dims_m[2];
        g.drawLine (view_x, line_y, view_x+room_dims_pixels[1], line_y, 1.000f);
    }

    /* Source icons */
    g.setColour(Colours::orange);
    g.setOpacity(0.5f);
    for(int src=0; src<ambi_roomsim_getNumSources(hAmbi); src++){
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getSourceY(hAmbi, src));
        float point_y = view_y + room_dims_pixels[2] - scale*(ambi_roomsim_getSourceZ(hAmbi, src));
        srcIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        g.fillEllipse(srcIcon);
    }

    /* Receiver icons */
    g.setColour(Colours::magenta);
    g.setOpacity(0.5f);
    for(int rec=0; rec<ambi_roomsim_getNumReceivers(hAmbi); rec++){
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getReceiverY(hAmbi, rec));
        float point_y = view_y + room_dims_pixels[2] - scale*(ambi_roomsim_getReceiverZ(hAmbi, rec));
        recIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        g.fillEllipse(recIcon);
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

void pannerView::mouseDown (const juce::MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...

    Rectangle<int> srcIcon, recIcon;
    const float room_pixels = 220;
    float room_dims_pixels[3], room_dims_m[3];
    room_dims_m[0] = ambi_roomsim_getRoomDimX(hAmbi);
    room_dims_m[1] = ambi_roomsim_getRoomDimY(hAmbi);
    room_dims_m[2] = ambi_roomsim_getRoomDimZ(hAmbi);

    /* Scaling factor to convert metres to pixels */
    float scale = room_pixels/MAX(MAX(room_dims_m[0], room_dims_m[1]), room_dims_m[2]);
    room_dims_pixels[0] = room_dims_m[0]*scale;
    room_dims_pixels[1] = room_dims_m[1]*scale;
    room_dims_pixels[2] = room_dims_m[2]*scale;

    /* TOP VIEW */
    float view_x = 22.0f; float view_y = 22.0f;
    for(int src=0; src<ambi_roomsim_getNumSources(hAmbi); src++){
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getSourceY(hAmbi, src));
        float point_y = view_y + room_dims_pixels[0] - scale*(ambi_roomsim_getSourceX(hAmbi, src));
        srcIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        if(srcIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
            sourceIconIsClicked = true;
            indexOfClickedIcon = src;
            topOrSideView = TOP_VIEW;
            return;
        }
    }
    for(int rec=0; rec<ambi_roomsim_getNumReceivers(hAmbi); rec++){
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getReceiverY(hAmbi, rec));
        float point_y = view_y + room_dims_pixels[0] - scale*(ambi_roomsim_getReceiverX(hAmbi, rec));
        recIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        if(recIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
            receiverIconIsClicked = true;
            indexOfClickedIcon = rec;
            topOrSideView = TOP_VIEW;
            return;
        }
    }

    /* SIDE VIEW */
    view_x = 22.0f; view_y = 262.0f;
    for(int src=0; src<ambi_roomsim_getNumSources(hAmbi); src++){
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getSourceY(hAmbi, src));
        float point_y = view_y + room_dims_pixels[2] - scale*(ambi_roomsim_getSourceZ(hAmbi, src));
        srcIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        if(srcIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
            sourceIconIsClicked = true;
            indexOfClickedIcon = src;
            topOrSideView = SIDE_VIEW;
            return;
        }
    }
    for(int rec=0; rec<ambi_roomsim_getNumReceivers(hAmbi); rec++){
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getReceiverY(hAmbi, rec));
        float point_y = view_y + room_dims_pixels[2] - scale*(ambi_roomsim_getReceiverZ(hAmbi, rec));
        recIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        if(recIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
            receiverIconIsClicked = true;
            indexOfClickedIcon = rec;
            topOrSideView = SIDE_VIEW;
            return;
        }
    }
    //[/UserCode_mouseDown]
}

void pannerView::mouseDrag (const juce::MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...

    const float room_pixels = 220;
    float room_dims_pixels[3], room_dims_m[3];
    float scale;
    Point<float> point;
    float view_x, view_y;

    if(sourceIconIsClicked||receiverIconIsClicked){
        /* Scaling factor to convert metres to pixels */
        room_dims_m[0] = ambi_roomsim_getRoomDimX(hAmbi);
        room_dims_m[1] = ambi_roomsim_getRoomDimY(hAmbi);
        room_dims_m[2] = ambi_roomsim_getRoomDimZ(hAmbi);
        scale = room_pixels/MAX(MAX(room_dims_m[0], room_dims_m[1]), room_dims_m[2]);
        room_dims_pixels[0] = room_dims_m[0]*scale;
        room_dims_pixels[1] = room_dims_m[1]*scale;
        room_dims_pixels[2] = room_dims_m[2]*scale;
    }

    if(sourceIconIsClicked){
        switch(topOrSideView){
            case TOP_VIEW:
                view_x = 22.0f; view_y = 22.0f;
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                ambi_roomsim_setSourceY(hAmbi, indexOfClickedIcon, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                ambi_roomsim_setSourceX(hAmbi, indexOfClickedIcon, -(point.getY() - view_y - room_dims_pixels[0])/scale);
                break;

            case SIDE_VIEW:
                view_x = 22.0f; view_y = 262.0f;
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                ambi_roomsim_setSourceY(hAmbi, indexOfClickedIcon, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                ambi_roomsim_setSourceZ(hAmbi, indexOfClickedIcon, -(point.getY() - view_y - room_dims_pixels[2])/scale);
                break;
            default: assert(0); break;
        }
    }
    else if(receiverIconIsClicked){
        switch(topOrSideView){
            case TOP_VIEW:
                view_x = 22.0f; view_y = 22.0f;
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                ambi_roomsim_setReceiverY(hAmbi, indexOfClickedIcon, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                ambi_roomsim_setReceiverX(hAmbi, indexOfClickedIcon, -(point.getY() - view_y - room_dims_pixels[0])/scale);
                break;

            case SIDE_VIEW:
                view_x = 22.0f; view_y = 262.0f;
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                ambi_roomsim_setReceiverY(hAmbi, indexOfClickedIcon, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                ambi_roomsim_setReceiverZ(hAmbi, indexOfClickedIcon, -(point.getY() - view_y - room_dims_pixels[2])/scale);
                break;
            default: assert(0); break;
        }
    }
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
  <BACKGROUND backgroundColour="58323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

