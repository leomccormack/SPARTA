/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

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
const float room_pixels = 200;
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
    setSize(_width, _height);
    hVst = ownerFilter;
    hAmbi = hVst->getFXHandle();
    width = _width;
    height = _height;
    topOrSideView = TOP_VIEW; /* default */
    sourceIconIsClicked = false;
    receiverIconIsClicked = false;
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

    //[UserPaint] Add your own custom painting code here..

    Rectangle<float> srcIcon, tmpIcon, recIcon;

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
    float view_x = 27.0f , view_y = 12.0f;
    float centre_x = view_x+room_dims_pixels[1]/2.0f;
    float centre_y = view_y+room_dims_pixels[0]/2.0f;
    g.setColour(Colours::lightgrey);
    g.drawRect(view_x, view_y, room_dims_pixels[1], room_dims_pixels[0], 2.000f);

    /* Grid lines and text */
    g.setColour(Colours::lightgrey);
    g.setFont(10.0f);
    for(int i=0; i<=(int)room_dims_m[1]; i++){
        /* Verticle lines */
        float line_x = view_x + room_dims_pixels[1] - (float)i*room_dims_pixels[1]/room_dims_m[1];
        g.setOpacity(0.25f);
        g.drawLine (line_x, view_y, line_x, view_y+room_dims_pixels[0], 1.000f);
        g.setOpacity(0.75f);
        if( (i%2)==0 )
            g.drawText(String(i), line_x-5, view_y+room_dims_pixels[0], 10, 10, Justification::centred, true);
    }
    for(int i=0; i<=(int)room_dims_m[0]; i++){
        /* Horizontal lines*/
        float line_y = view_y + room_dims_pixels[0] - (float)i*room_dims_pixels[0]/room_dims_m[0];
        g.setOpacity(0.25f);
        g.drawLine (view_x, line_y, view_x+room_dims_pixels[1], line_y, 1.000f);
        g.setOpacity(0.75f);
        if( (i%2)==0 )
            g.drawText(String(i), view_x+room_dims_pixels[1]+2, line_y-5, 10, 10, Justification::centred, true);
    }
    g.setFont(12.0f);
    g.drawText("y",  view_x + room_dims_pixels[1]/2.0f-5.0f, view_y+room_dims_pixels[0]+7.0f, 10, 10, Justification::centred, true);
    g.drawText("x",  view_x + room_dims_pixels[1]+12.0f, view_y+room_dims_pixels[0]/2.0f-5.0f, 10, 10, Justification::centred, true);

    /* Source icons */
    g.setColour(Colours::orange);
    for(int src=0; src<ambi_roomsim_getNumSources(hAmbi); src++){
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getSourceY(hAmbi, src));
        float point_y = view_y + room_dims_pixels[0] - scale*(ambi_roomsim_getSourceX(hAmbi, src));
        srcIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        tmpIcon.setBounds(point_x-iconRadius*3, point_y-iconRadius, iconWidth*3, iconWidth);
        g.setOpacity(0.7f);
        g.fillEllipse(srcIcon);
        g.setOpacity(0.8f);
        g.drawText(String(src+1), tmpIcon.translated(8.0f, -8.0f), Justification::centred);
    }

    /* Receiver icons */
    g.setColour(Colours::magenta);
    for(int rec=0; rec<ambi_roomsim_getNumReceivers(hAmbi); rec++){
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getReceiverY(hAmbi, rec));
        float point_y = view_y + room_dims_pixels[0] - scale*(ambi_roomsim_getReceiverX(hAmbi, rec));
        recIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        tmpIcon.setBounds(point_x-iconRadius*3, point_y-iconRadius, iconWidth*3, iconWidth);
        g.setOpacity(0.7f);
        g.fillEllipse(recIcon);
        g.setOpacity(0.8f);
        g.drawText(String(rec+1), tmpIcon.translated(8.0f, -8.0f), Justification::centred);
    }


    /****** DRAW SIDE VIEW *****/
    /* Background and border */
    view_x = 27.0f; view_y = 240.0f;
    centre_x = view_x+room_dims_pixels[1]/2.0f;
    centre_y = view_y+room_dims_pixels[2]/2.0f;
    g.setColour(Colours::lightgrey);
    g.drawRect(view_x, view_y, room_dims_pixels[1], room_dims_pixels[2], 2.000f);

    /* Origin marker and grid lines (one per metre) */
    g.setColour(Colours::lightgrey);
    g.setFont(10.0f);
    for(int i=0; i<=(int)room_dims_m[1]; i++){
        /* Verticle lines */
        float line_x = view_x + room_dims_pixels[1] - (float)i*room_dims_pixels[1]/room_dims_m[1];
        g.setOpacity(0.25f);
        g.drawLine (line_x, view_y, line_x, view_y+room_dims_pixels[2], 1.000f);
        g.setOpacity(0.75f);
        if( (i%2)==0 )
            g.drawText(String(i), line_x-5, view_y+room_dims_pixels[2], 10, 10, Justification::centred, true);
    }
    for(int i=0; i<=(int)room_dims_m[2]; i++){
        /* Horizontal lines*/
        float line_y = view_y + room_dims_pixels[2] - (float)i*room_dims_pixels[2]/room_dims_m[2];
        g.setOpacity(0.25f);
        g.drawLine (view_x, line_y, view_x+room_dims_pixels[1], line_y, 1.000f);
        g.setOpacity(0.75f);
        if( (i%2)==0 )
            g.drawText(String(i), view_x+room_dims_pixels[1]+2, line_y-5, 10, 10, Justification::centred, true);
    }
    g.setFont(12.0f);
    g.drawText("y",  view_x + room_dims_pixels[1]/2.0f-5.0f, view_y+room_dims_pixels[2]+7.0f, 10, 10, Justification::centred, true);
    g.drawText("z",  view_x + room_dims_pixels[1]+12.0f, view_y+room_dims_pixels[2]/2.0f-5.0f, 10, 10, Justification::centred, true);

    /* Source icons */
    g.setFont(10.0f);
    g.setColour(Colours::orange);
    for(int src=0; src<ambi_roomsim_getNumSources(hAmbi); src++){
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getSourceY(hAmbi, src));
        float point_y = view_y + room_dims_pixels[2] - scale*(ambi_roomsim_getSourceZ(hAmbi, src));
        srcIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        g.setOpacity(0.7f);
        g.fillEllipse(srcIcon);
        g.setOpacity(0.8f);
        g.drawText(String(src+1), srcIcon.translated(8.0f, -8.0f), Justification::centred);
    }

    /* Receiver icons */
    g.setColour(Colours::magenta);
    for(int rec=0; rec<ambi_roomsim_getNumReceivers(hAmbi); rec++){
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getReceiverY(hAmbi, rec));
        float point_y = view_y + room_dims_pixels[2] - scale*(ambi_roomsim_getReceiverZ(hAmbi, rec));
        recIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        g.setOpacity(0.7f);
        g.fillEllipse(recIcon);
        g.setOpacity(0.8f);
        g.drawText(String(rec+1), recIcon.translated(8.0f, -8.0f), Justification::centred);
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
    float view_x = 27.0f; float view_y = 12.0f;
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
    view_x = 27.0f; view_y = 240.0f;
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
                view_x = 27.0f; view_y = 12.0f;
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                ambi_roomsim_setSourceY(hAmbi, indexOfClickedIcon, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                ambi_roomsim_setSourceX(hAmbi, indexOfClickedIcon, -(point.getY() - view_y - room_dims_pixels[0])/scale);
                break;

            case SIDE_VIEW:
                view_x = 27.0f; view_y = 240.0f;
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                ambi_roomsim_setSourceY(hAmbi, indexOfClickedIcon, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                ambi_roomsim_setSourceZ(hAmbi, indexOfClickedIcon, -(point.getY() - view_y - room_dims_pixels[2])/scale);
                break;
            default: break;
        }
    }
    else if(receiverIconIsClicked){
        switch(topOrSideView){
            case TOP_VIEW:
                view_x = 27.0f; view_y = 12.0f;
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                ambi_roomsim_setReceiverY(hAmbi, indexOfClickedIcon, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                ambi_roomsim_setReceiverX(hAmbi, indexOfClickedIcon, -(point.getY() - view_y - room_dims_pixels[0])/scale);
                break;

            case SIDE_VIEW:
                view_x = 27.0f; view_y = 240.0f;
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                ambi_roomsim_setReceiverY(hAmbi, indexOfClickedIcon, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                ambi_roomsim_setReceiverZ(hAmbi, indexOfClickedIcon, -(point.getY() - view_y - room_dims_pixels[2])/scale);
                break;
            default: break;
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
  <BACKGROUND backgroundColour="323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

