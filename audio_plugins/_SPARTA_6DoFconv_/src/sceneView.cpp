/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.6

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

//[/Headers]

#include "sceneView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
const float iconWidth = 8.0f;
const float iconRadius = iconWidth/2.0f;
const float room_pixels = 386;

#ifndef CLAMP
/** Ensures value "a" is clamped between the "min" and "max" values */
# define CLAMP(a,min,max) (MAX(min, MIN(max, a)))
#endif
//[/MiscUserDefs]

//==============================================================================
sceneView::sceneView (PluginProcessor* ownerFilter, int _width, int _height)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (480, 240);


    //[Constructor] You can add your own custom stuff here..
    setSize(_width, _height);
    hVst = ownerFilter;
    hTVCnv = hVst->getFXHandle();
    width = _width;
    height = _height;
    topOrSideView = TOP_VIEW; /* default */
    targetIconIsClicked = false;
    drawDoAs = true;
    drawIntersections = true;
    drawTargets = true;
    //[/Constructor]
}

sceneView::~sceneView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void sceneView::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..

    Rectangle<float> lstIcon;

    float room_dims_pixels[3], room_dims_m[3], room_offset_m[3], room_offset_pixels[3];
    float room_dims_pixels_o[3], room_dims_m_o[3];
    if (tvconv_getNumListenerPositions(hTVCnv)==0){
        room_dims_m[0] = room_dims_m[1] = 1.0f;
        room_dims_m[2] = 0.35f;
        room_offset_m[0] = room_offset_m[1] = room_offset_m[2] = 0.0f;
    }
    else{
        room_dims_m[0] = MAX(MAX(tvconv_getMaxDimension(hTVCnv, 0), tvconv_getSourcePosition(hTVCnv, 0)), 1.0f) * 1.2f;
        room_dims_m[1] = MAX(MAX(tvconv_getMaxDimension(hTVCnv, 1), tvconv_getSourcePosition(hTVCnv, 1)), 1.0f) * 1.2f;
        room_dims_m[2] = MAX(MAX(tvconv_getMaxDimension(hTVCnv, 2), tvconv_getSourcePosition(hTVCnv, 2)), 0.35f) * 1.2f;
        room_offset_m[0] = floorf(MIN(tvconv_getMinDimension(hTVCnv, 0), tvconv_getSourcePosition(hTVCnv, 0)) * 0.8f);
        room_offset_m[1] = floorf(MIN(tvconv_getMinDimension(hTVCnv, 1), tvconv_getSourcePosition(hTVCnv, 1)) * 0.8f);
        room_offset_m[2] = floorf(MIN(tvconv_getMinDimension(hTVCnv, 2), tvconv_getSourcePosition(hTVCnv, 2)) * 0.8f);
    }
    room_dims_m_o[0] = room_dims_m[0]-room_offset_m[0];
    room_dims_m_o[1] = room_dims_m[1]-room_offset_m[1];
    room_dims_m_o[2] = room_dims_m[2]-room_offset_m[2];

    /* Scaling factor to convert metres to pixels */
    float scale = room_pixels/MAX(MAX(room_dims_m[0]-room_offset_m[0], room_dims_m[1]-room_offset_m[1]), room_dims_m[2]-room_offset_m[2]);
    room_dims_pixels[0] = room_dims_m[0]*scale;
    room_dims_pixels[1] = room_dims_m[1]*scale;
    room_dims_pixels[2] = room_dims_m[2]*scale;
    room_offset_pixels[0] = room_offset_m[0]*scale;
    room_offset_pixels[1] = room_offset_m[1]*scale;
    room_offset_pixels[2] = room_offset_m[2]*scale;
    room_dims_pixels_o[0] = room_dims_pixels[0]-room_offset_pixels[0];
    room_dims_pixels_o[1] = room_dims_pixels[1]-room_offset_pixels[1];
    room_dims_pixels_o[2] = room_dims_pixels[2]-room_offset_pixels[2];

    float view_x = 27.0f , view_y = 12.0f;
    int xp_idx, yp_idx;

    if(topOrSideView==TOP_VIEW){
        xp_idx = 0;  /* X */
        yp_idx = 1;  /* Y */
    }
    else{
        xp_idx = 0;  /* X */
        yp_idx = 2;  /* Z */
    }

    /* Background and border */
    g.setColour(Colours::lightgrey);
    g.drawRect(view_x, view_y, room_dims_pixels_o[xp_idx], room_dims_pixels_o[yp_idx], 2.000f);

    /* Grid grid lines and text */
    g.setColour(Colours::lightgrey);
    g.setFont(12.0f);
    g.setOpacity(0.15f);
    for(float i=0.0f; i<=room_dims_m_o[xp_idx]; i+=0.2f){
        /* Verticle lines */
        float line_x = view_x + room_dims_pixels_o[xp_idx] - i*room_dims_pixels_o[xp_idx]/room_dims_m_o[xp_idx];
        g.drawLine (line_x, view_y, line_x, view_y+room_dims_pixels_o[yp_idx], 1.000f);
    }
    for(int i=0; i<=(int)room_dims_m_o[xp_idx]; i++){
        /* Verticle lines */
        float line_x = view_x + room_dims_pixels_o[xp_idx] - (float)i*room_dims_pixels_o[xp_idx]/room_dims_m_o[xp_idx];
        g.setOpacity(0.35f);
        g.drawLine (line_x, view_y, line_x, view_y+room_dims_pixels_o[yp_idx], 1.000f);
        g.setOpacity(0.75f);
        if( (i%2)==0 )
            g.drawText(String(i+(int)room_offset_m[yp_idx]), line_x-10, view_y+room_dims_pixels_o[yp_idx], 20, 10, Justification::centred, true);
    }
    g.setOpacity(0.15f);
    for(float i=0.0f; i<=room_dims_m_o[yp_idx]; i+=0.2f){
        /* Horizontal lines*/
        float line_y = view_y + room_dims_pixels_o[yp_idx] - i*room_dims_pixels_o[yp_idx]/room_dims_m_o[yp_idx];
        g.drawLine (view_x, line_y, view_x+room_dims_pixels_o[xp_idx], line_y, 1.000f);
    }
    for(int i=0; i<=(int)room_dims_m_o[yp_idx]; i++){
        /* Horizontal lines*/
        float line_y = view_y + room_dims_pixels_o[yp_idx] - (float)i*room_dims_pixels_o[yp_idx]/room_dims_m_o[yp_idx];
        g.setOpacity(0.35f);
        g.drawLine (view_x, line_y, view_x+room_dims_pixels_o[xp_idx], line_y, 1.000f);
        g.setOpacity(0.75f);
        if( (i%2)==0 )
            g.drawText(String(i+(int)room_offset_m[xp_idx]), view_x+room_dims_pixels_o[xp_idx], line_y-5, 20, 10, Justification::centred, true);
    }
    g.setFont(14.0f);
    g.drawText("x",  view_x + room_dims_pixels_o[xp_idx]/2.0f-5.0f, view_y+room_dims_pixels_o[yp_idx]+7.0f, 10, 10, Justification::centred, true);
    g.drawText(topOrSideView==TOP_VIEW ? "y" : "z",  view_x + room_dims_pixels_o[xp_idx]+12.0f, view_y+room_dims_pixels_o[yp_idx]/2.0f-5.0f, 10, 10, Justification::centred, true);

    /* Listener icons */
    int targetIndex = tvconv_getListenerPositionIdx(hTVCnv);
    for(int i=0; i<tvconv_getNumListenerPositions(hTVCnv); i++){
        float point_x = view_x + room_dims_pixels_o[xp_idx] - scale*(tvconv_getListenerPosition(hTVCnv, i, 0/*X*/) - room_offset_m[0]);
        float point_y = view_y + room_dims_pixels_o[yp_idx] - scale*(topOrSideView==TOP_VIEW ?
                                                                     tvconv_getListenerPosition(hTVCnv, i, 1/*Y*/) - room_offset_m[1] :
                                                                     tvconv_getListenerPosition(hTVCnv, i, 2/*Z*/) - room_offset_m[2]);
        if(i==targetIndex){
            lstIcon.setBounds(point_x-iconRadius*1.8f, point_y-iconRadius*1.8f, iconWidth*1.8f, iconWidth*1.8f);
            g.setColour(Colours::white);
            g.drawText(String(targetIndex), lstIcon.translated(10.0f, -10.0f), Justification::centred);
            g.setColour(Colours::green);
            g.fillEllipse(lstIcon);
            g.setColour(Colours::lightgrey);
            g.setOpacity(0.9f);
            g.drawEllipse(lstIcon, 1.0f);
        }
        else{
            lstIcon.setBounds(point_x-iconRadius*1.4f, point_y-iconRadius*1.4f, iconWidth*1.4f, iconWidth*1.4f);
            g.setColour(Colours::darkcyan);
            g.setOpacity(0.3f);
            g.fillEllipse(lstIcon);
            g.setColour(Colours::lightgrey);
            g.setOpacity(0.3f);
            g.drawEllipse(lstIcon, 1.0f);
        }
    }

    /* Source icon */
    float point_x = view_x + room_dims_pixels_o[xp_idx] - scale*(tvconv_getSourcePosition(hTVCnv, 0/*X*/) - room_offset_m[0]);
    float point_y = view_y + room_dims_pixels_o[yp_idx] - scale*(topOrSideView==TOP_VIEW ?
                                                                 tvconv_getSourcePosition(hTVCnv, 1/*Y*/) - room_offset_m[1] :
                                                                 tvconv_getSourcePosition(hTVCnv, 2/*Z*/) - room_offset_m[2]);
    lstIcon.setBounds(point_x-iconRadius*1.2f, point_y-iconRadius*1.2f, iconWidth*1.2f, iconWidth*1.2f);
    g.setOpacity(0.9f);
    g.setColour(Colours::magenta);
    g.fillEllipse(lstIcon);
    g.setColour(Colours::lightgrey);
    g.drawEllipse(lstIcon, 1.0f);

    /* Target Listener position */
    point_x = view_x + room_dims_pixels_o[xp_idx] - scale*(tvconv_getTargetPosition(hTVCnv, 0/*X*/) - room_offset_m[0]);
    point_y = view_y + room_dims_pixels_o[yp_idx] - scale*(topOrSideView==TOP_VIEW ?
                                                           tvconv_getTargetPosition(hTVCnv, 1/*Y*/) - room_offset_m[1] :
                                                           tvconv_getTargetPosition(hTVCnv, 2/*Z*/) - room_offset_m[2]);
    lstIcon.setBounds(point_x-iconRadius*1.2f, point_y-iconRadius*1.2f, iconWidth*1.2f, iconWidth*1.2f);
    g.setOpacity(0.9f);
    g.setColour(Colours::orange);
    g.fillEllipse(lstIcon);
    g.setColour(Colours::lightgrey);
    g.drawEllipse(lstIcon, 1.0f);

    //[/UserPaint]
}

void sceneView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void sceneView::mouseDown (const juce::MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...

    Rectangle<int> recIcon;
    float room_dims_pixels[3], room_dims_m[3], room_offset_m[3], room_offset_pixels[3];
    float room_dims_pixels_o[3], room_dims_m_o[3];
    if (tvconv_getNumListenerPositions(hTVCnv)==0){
        room_dims_m[0] = room_dims_m[1] = 1.0f;
        room_dims_m[2] = 0.35f;
        room_offset_m[0] = room_offset_m[1] = room_offset_m[2] = 0.0f;
    }
    else{
        room_dims_m[0] = MAX(MAX(tvconv_getMaxDimension(hTVCnv, 0), tvconv_getSourcePosition(hTVCnv, 0)), 1.0f) * 1.2f;
        room_dims_m[1] = MAX(MAX(tvconv_getMaxDimension(hTVCnv, 1), tvconv_getSourcePosition(hTVCnv, 1)), 1.0f) * 1.2f;
        room_dims_m[2] = MAX(MAX(tvconv_getMaxDimension(hTVCnv, 2), tvconv_getSourcePosition(hTVCnv, 2)), 0.35f) * 1.2f;
        room_offset_m[0] = floorf(MIN(tvconv_getMinDimension(hTVCnv, 0), tvconv_getSourcePosition(hTVCnv, 0)) * 0.8f);
        room_offset_m[1] = floorf(MIN(tvconv_getMinDimension(hTVCnv, 1), tvconv_getSourcePosition(hTVCnv, 1)) * 0.8f);
        room_offset_m[2] = floorf(MIN(tvconv_getMinDimension(hTVCnv, 2), tvconv_getSourcePosition(hTVCnv, 2)) * 0.8f);
    }
    room_dims_m_o[0] = room_dims_m[0]-room_offset_m[0];
    room_dims_m_o[1] = room_dims_m[1]-room_offset_m[1];
    room_dims_m_o[2] = room_dims_m[2]-room_offset_m[2];

    /* Scaling factor to convert metres to pixels */
    float scale = room_pixels/MAX(MAX(room_dims_m[0]-room_offset_m[0], room_dims_m[1]-room_offset_m[1]), room_dims_m[2]-room_offset_m[2]);
    room_dims_pixels[0] = room_dims_m[0]*scale;
    room_dims_pixels[1] = room_dims_m[1]*scale;
    room_dims_pixels[2] = room_dims_m[2]*scale;
    room_offset_pixels[0] = room_offset_m[0]*scale;
    room_offset_pixels[1] = room_offset_m[1]*scale;
    room_offset_pixels[2] = room_offset_m[2]*scale;
    room_dims_pixels_o[0] = room_dims_pixels[0]-room_offset_pixels[0];
    room_dims_pixels_o[1] = room_dims_pixels[1]-room_offset_pixels[1];
    room_dims_pixels_o[2] = room_dims_pixels[2]-room_offset_pixels[2];

    float view_x = 27.0f; float view_y = 12.0f;

    if(topOrSideView==TOP_VIEW){
        float point_x = view_x + room_dims_pixels_o[0] - scale*(tvconv_getTargetPosition(hTVCnv, 0/*X*/) - room_offset_m[0]);
        float point_y = view_y + room_dims_pixels_o[1] - scale*(tvconv_getTargetPosition(hTVCnv, 1/*Y*/) - room_offset_m[1]);
        recIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        if(recIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
            targetIconIsClicked = true;
            return;
        }
    }
    else if(topOrSideView==SIDE_VIEW){
        /* REC */
        float point_x = view_x + room_dims_pixels_o[0] - scale*(tvconv_getTargetPosition(hTVCnv, 0/*X*/) - room_offset_m[0]);
        float point_y = view_y + room_dims_pixels_o[2] - scale*(tvconv_getTargetPosition(hTVCnv, 2/*Z*/) - room_offset_m[2]);
        recIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        if(recIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
            targetIconIsClicked = true;
            return;
        }
    }
    //[/UserCode_mouseDown]
}

void sceneView::mouseDrag (const juce::MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...

    float room_dims_pixels[3], room_dims_m[3], room_offset_m[3], room_offset_pixels[3];
    float room_dims_pixels_o[3], room_dims_m_o[3];
    float scale;
    Point<float> point;
    float view_x, view_y;
    view_x = 27.0f; view_y = 12.0f;

    if(targetIconIsClicked){
        /* Scaling factor to convert metres to pixels */
        if (tvconv_getNumListenerPositions(hTVCnv)==0){
            room_dims_m[0] = room_dims_m[1] = 1.0f;
            room_dims_m[2] = 0.35f;
            room_offset_m[0] = room_offset_m[1] = room_offset_m[2] = 0.0f;
        }
        else{
            room_dims_m[0] = MAX(MAX(tvconv_getMaxDimension(hTVCnv, 0), tvconv_getSourcePosition(hTVCnv, 0)), 1.0f) * 1.2f;
            room_dims_m[1] = MAX(MAX(tvconv_getMaxDimension(hTVCnv, 1), tvconv_getSourcePosition(hTVCnv, 1)), 1.0f) * 1.2f;
            room_dims_m[2] = MAX(MAX(tvconv_getMaxDimension(hTVCnv, 2), tvconv_getSourcePosition(hTVCnv, 2)), 0.35f) * 1.2f;
            room_offset_m[0] = floorf(MIN(tvconv_getMinDimension(hTVCnv, 0), tvconv_getSourcePosition(hTVCnv, 0)) * 0.8f);
            room_offset_m[1] = floorf(MIN(tvconv_getMinDimension(hTVCnv, 1), tvconv_getSourcePosition(hTVCnv, 1)) * 0.8f);
            room_offset_m[2] = floorf(MIN(tvconv_getMinDimension(hTVCnv, 2), tvconv_getSourcePosition(hTVCnv, 2)) * 0.8f);
        }
        room_dims_m_o[0] = room_dims_m[0]-room_offset_m[0];
        room_dims_m_o[1] = room_dims_m[1]-room_offset_m[1];
        room_dims_m_o[2] = room_dims_m[2]-room_offset_m[2];
        scale = room_pixels/MAX(MAX(room_dims_m[0]-room_offset_m[0], room_dims_m[1]-room_offset_m[1]), room_dims_m[2]-room_offset_m[2]);
        room_dims_pixels[0] = room_dims_m[0]*scale;
        room_dims_pixels[1] = room_dims_m[1]*scale;
        room_dims_pixels[2] = room_dims_m[2]*scale;
        room_offset_pixels[0] = room_offset_m[0]*scale;
        room_offset_pixels[1] = room_offset_m[1]*scale;
        room_offset_pixels[2] = room_offset_m[2]*scale;
        room_dims_pixels_o[0] = room_dims_pixels[0]-room_offset_pixels[0];
        room_dims_pixels_o[1] = room_dims_pixels[1]-room_offset_pixels[1];
        room_dims_pixels_o[2] = room_dims_pixels[2]-room_offset_pixels[2];
    }

    if(targetIconIsClicked){
        switch(topOrSideView){
            case TOP_VIEW:
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                tvconv_setTargetPosition(hTVCnv, -(point.getX() - view_x - room_dims_pixels_o[0])/scale + room_offset_m[0], 0/*X*/);
                tvconv_setTargetPosition(hTVCnv, -(point.getY() - view_y - room_dims_pixels_o[1])/scale + room_offset_m[1], 1/*Y*/);
                break;

            case SIDE_VIEW:
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                tvconv_setTargetPosition(hTVCnv, -(point.getX() - view_x - room_dims_pixels_o[0])/scale + room_offset_m[0], 0/*X*/);
                tvconv_setTargetPosition(hTVCnv, -(point.getY() - view_y - room_dims_pixels_o[2])/scale + room_offset_m[2], 2/*Z*/);
                break;
            default: break;
        }
    }

    //[/UserCode_mouseDrag]
}

void sceneView::mouseUp (const juce::MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
    (void)e;
    targetIconIsClicked = false;
    //[/UserCode_mouseUp]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void sceneView::refreshSceneView()
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

<JUCER_COMPONENT documentType="Component" className="sceneView" componentName=""
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

