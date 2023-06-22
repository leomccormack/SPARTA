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

// Room size in pixels
const float room_pixels = 380;

// View offset of the room rectangle in pixels
const float view_x = 10.0f;
const float view_y = 12.0f;

// Room dimensions 
float room_dims_pixels[3], room_dims_m[3], room_offset_m[3], room_offset_pixels[3];
float room_dims_pixels_o[3], room_dims_m_o[3];
float scale;

// Room grid lines
float primaryLineSpacing = 4.0;
int primaryLineLabelDownsample = 1;
float secondaryLineSpacing = 2.0f;


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


	// Screen graphics axis directon:
	// X from left to right
	// Y from top to bottom
	//
	// Listener axis directions:
	// X from right to left
	// Y from bottom to top (top view)
	// Z from bottom to top (side view)

    Rectangle<float> lstIcon;

    computeRoomDims();

    int xp_idx, yp_idx;
    String xAxisLabel, yAxisLabel;

    if(topOrSideView==TOP_VIEW){
        xp_idx = 1;  /* Y */
        yp_idx = 0;  /* X */
        xAxisLabel = String("Y");
        yAxisLabel = String("X");
    }
    else{ // SIDE VIEW
        xp_idx = 1;  /* Y */
        yp_idx = 2;  /* Z */
        xAxisLabel = String("Y");
        yAxisLabel = String("Z");
    }

    /* Background and border */
    g.setColour(Colours::lightgrey);
    g.drawRect(view_x, view_y, room_dims_pixels_o[xp_idx], room_dims_pixels_o[yp_idx], 2.000f);

    /* Grid grid lines and text */
    g.setColour(Colours::lightgrey);
    g.setFont(12.0f);
    g.setOpacity(0.15f);

    for(float i=0.0f; i<=room_dims_m_o[xp_idx]; i+= secondaryLineSpacing){
        /* Verticle lines */
        float line_x = view_x + i*room_dims_pixels_o[xp_idx]/room_dims_m_o[xp_idx];
        g.drawLine (line_x, view_y, line_x, view_y+room_dims_pixels_o[yp_idx], 1.000f);
    }
    for(float i=0; i<=room_dims_m_o[xp_idx]; i+= primaryLineSpacing){
        /* Verticle lines */
        float line_x = view_x + room_dims_pixels_o[xp_idx] - (float)i*room_dims_pixels_o[xp_idx]/room_dims_m_o[xp_idx];
        g.setOpacity(0.35f);
        g.drawLine (line_x, view_y, line_x, view_y+room_dims_pixels_o[yp_idx], 1.000f);
        g.setOpacity(0.75f);
        // vertical lines labels
        g.drawText(String(i+room_offset_m[xp_idx],1,false), line_x-10, view_y+room_dims_pixels_o[yp_idx]+5, 30, 10, Justification::centred, true);
    }
    g.setOpacity(0.15f);
    for(float i=0.0f; i<=room_dims_m_o[yp_idx]; i+= secondaryLineSpacing){
        /* Horizontal lines*/
        float line_y = view_y + room_dims_pixels_o[yp_idx] - i*room_dims_pixels_o[yp_idx]/room_dims_m_o[yp_idx];
        g.drawLine (view_x, line_y, view_x+room_dims_pixels_o[xp_idx], line_y, 1.000f);
    }
    for(float i=0; i<=room_dims_m_o[yp_idx]; i+= primaryLineSpacing){
        /* Horizontal lines*/
        float line_y = view_y + room_dims_pixels_o[yp_idx] - (float)i*room_dims_pixels_o[yp_idx]/room_dims_m_o[yp_idx];
        g.setOpacity(0.35f);
        g.drawLine (view_x, line_y, view_x+room_dims_pixels_o[xp_idx], line_y, 1.000f);
        g.setOpacity(0.75f);
        // horizontal lines labels
        g.drawText(String(i+room_offset_m[yp_idx],1,false), view_x +room_dims_pixels_o[xp_idx], line_y-5, 30, 10, Justification::centred, true);
    }
    // Axis name labels ("X", "Y", "Z")
    g.setFont(14.0f);
    g.drawText( xAxisLabel, view_x + room_dims_pixels_o[xp_idx]/2.0f+5.0f, view_y+room_dims_pixels_o[yp_idx]+20.0f, 20, 10, Justification::centred, true);
    g.drawText( yAxisLabel, view_x + room_dims_pixels_o[xp_idx] + 20.0f, view_y+room_dims_pixels_o[yp_idx]/2.0f-5.0f, 20, 10, Justification::centred, true);

    /* Listener icons */
    int targetIndex = tvconv_getListenerPositionIdx(hTVCnv);
    for(int i=0; i<tvconv_getNumListenerPositions(hTVCnv); i++){
        float point_x = view_x + room_dims_pixels_o[xp_idx] - scale*(tvconv_getListenerPosition(hTVCnv, i, xp_idx/*Y*/) - room_offset_m[xp_idx]);
        float point_y = view_y + room_dims_pixels_o[yp_idx] - scale*(tvconv_getListenerPosition(hTVCnv, i, yp_idx/*X or Z*/) - room_offset_m[yp_idx]);
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
    float point_x = view_x + room_dims_pixels_o[xp_idx] - scale*(tvconv_getSourcePosition(hTVCnv, xp_idx/*Y*/) - room_offset_m[xp_idx]);
    float point_y = view_y + room_dims_pixels_o[yp_idx] - scale*(tvconv_getSourcePosition(hTVCnv, yp_idx/*X or Z*/) - room_offset_m[yp_idx]);
    lstIcon.setBounds(point_x-iconRadius*1.2f, point_y-iconRadius*1.2f, iconWidth*1.2f, iconWidth*1.2f);
    g.setOpacity(0.9f);
    g.setColour(Colours::magenta);
    g.fillEllipse(lstIcon);
    g.setColour(Colours::lightgrey);
    g.drawEllipse(lstIcon, 1.0f);

    /* Target Listener position */
    point_x = view_x + room_dims_pixels_o[xp_idx] - scale*(tvconv_getTargetPosition(hTVCnv, xp_idx/*Y*/) - room_offset_m[xp_idx]);
    point_y = view_y + room_dims_pixels_o[yp_idx] - scale*(tvconv_getTargetPosition(hTVCnv, yp_idx /*X or Z*/) - room_offset_m[yp_idx]);
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

    computeRoomDims();

    int xp_idx, yp_idx;
    if (topOrSideView == TOP_VIEW) {
        xp_idx = 1;  /* Y */
        yp_idx = 0;  /* X */
    }
    else { // SIDE VIEW
        xp_idx = 1;  /* Y */
        yp_idx = 2;  /* Z */
    }

    float point_x = view_x + room_dims_pixels_o[xp_idx] - scale * (tvconv_getTargetPosition(hTVCnv, xp_idx) - room_offset_m[xp_idx]);
    float point_y = view_y + room_dims_pixels_o[yp_idx] - scale * (tvconv_getTargetPosition(hTVCnv, yp_idx) - room_offset_m[yp_idx]);
    recIcon.setBounds(point_x - iconRadius, point_y - iconRadius, iconWidth, iconWidth);
    if (recIcon.expanded(4, 4).contains(e.getMouseDownPosition())) {
        targetIconIsClicked = true;
        return;
    }

    //[/UserCode_mouseDown]
}

void sceneView::mouseDrag (const juce::MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...

    Point<float> point;

    int xp_idx, yp_idx;
    if (topOrSideView == TOP_VIEW) {
        xp_idx = 1;  /* Y */
        yp_idx = 0;  /* X */
    }
    else { // SIDE VIEW
        xp_idx = 1;  /* Y */
        yp_idx = 2;  /* Z */
    }

    if(targetIconIsClicked){

        computeRoomDims();

        point.setXY((float)e.getPosition().getX() - 2, (float)e.getPosition().getY() - 2);
        tvconv_setTargetPosition(hTVCnv, -(point.getX() - view_x - room_dims_pixels_o[xp_idx]) / scale + room_offset_m[xp_idx], xp_idx);
        tvconv_setTargetPosition(hTVCnv, -(point.getY() - view_y - room_dims_pixels_o[yp_idx]) / scale + room_offset_m[yp_idx], yp_idx);

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

void sceneView::computeRoomDims()
{

if (tvconv_getNumListenerPositions(hTVCnv) == 0) {
    room_dims_m[0] = room_dims_m[1] = 1.0f;
    room_dims_m[2] = 0.35f;
    room_offset_m[0] = room_offset_m[1] = room_offset_m[2] = 0.0f;
}
else {
    room_dims_m[0] = MAX(MAX(tvconv_getMaxDimension(hTVCnv, 0), tvconv_getSourcePosition(hTVCnv, 0)), 0.01f) * 1.2f;
    room_dims_m[1] = MAX(MAX(tvconv_getMaxDimension(hTVCnv, 1), tvconv_getSourcePosition(hTVCnv, 1)), 0.01f) * 1.2f;
    room_dims_m[2] = MAX(MAX(tvconv_getMaxDimension(hTVCnv, 2), tvconv_getSourcePosition(hTVCnv, 2)), 0.003f) * 1.2f;
    room_offset_m[0] = floorf(MIN(tvconv_getMinDimension(hTVCnv, 0), tvconv_getSourcePosition(hTVCnv, 0)) * 0.8f * 10.0f) / 10.0f;
    room_offset_m[1] = floorf(MIN(tvconv_getMinDimension(hTVCnv, 1), tvconv_getSourcePosition(hTVCnv, 1)) * 0.8f * 10.0f) / 10.0f;
    room_offset_m[2] = floorf(MIN(tvconv_getMinDimension(hTVCnv, 2), tvconv_getSourcePosition(hTVCnv, 2)) * 0.8f * 10.0f) / 10.0f;
}
room_dims_m_o[0] = room_dims_m[0] - room_offset_m[0];
room_dims_m_o[1] = room_dims_m[1] - room_offset_m[1];
room_dims_m_o[2] = room_dims_m[2] - room_offset_m[2];

/* Scaling factor to convert metres to pixels */
scale = room_pixels / MAX(MAX(room_dims_m[0] - room_offset_m[0], room_dims_m[1] - room_offset_m[1]), room_dims_m[2] - room_offset_m[2]);
room_dims_pixels[0] = room_dims_m[0] * scale;
room_dims_pixels[1] = room_dims_m[1] * scale;
room_dims_pixels[2] = room_dims_m[2] * scale;
room_offset_pixels[0] = room_offset_m[0] * scale;
room_offset_pixels[1] = room_offset_m[1] * scale;
room_offset_pixels[2] = room_offset_m[2] * scale;
room_dims_pixels_o[0] = room_dims_pixels[0] - room_offset_pixels[0];
room_dims_pixels_o[1] = room_dims_pixels[1] - room_offset_pixels[1];
room_dims_pixels_o[2] = room_dims_pixels[2] - room_offset_pixels[2];


// Compute room grid lines
float gridStepSize[] = { 0.002, 0.005, 0.01, 0.02, 0.05, 0.1, .2, .5, 1, 2, 5, 10, 20, 50, 100, 200, 500, 1000 };
float stepSizeBoudaries[] = { 0.00316, 0.00707, 0.0141, 0.0316, 0.0707, 0.1414, 0.3162, 0.7071, 1.4142, 3.1623, 7.0711, 14.1421, 31.6228, 70.7107, 141.4, 316.2, 707.1, 1414.2 };
float spacing = MAX(MAX(room_dims_m_o[0], room_dims_m_o[1]), room_dims_m_o[2]) / 5;
int spacingIndex = 0;
for( int i = 0; i < sizeof(stepSizeBoudaries); i++ )
{
    if (spacing < stepSizeBoudaries[i])
    {
        spacingIndex = i;
        break;
    }
}
primaryLineSpacing = gridStepSize[spacingIndex];
secondaryLineSpacing = primaryLineSpacing / 5;

}




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

