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
const float iconWidth = 10.0f;
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
    hCmp = hVst->getFXHandle();
    width = _width;
    height = _height;
    topOrSideView = TOP_VIEW; /* default */
    receiverIconIsClicked = false;
    sourceIconIsClicked = false;
    listenerIconIsClicked = false;
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

    Rectangle<float> recIcon, srcIcon, lstIcon;

    float room_dims_pixels[3], room_dims_m[3];
    room_dims_m[0] = obcompass_getRoomDimX(hCmp);
    room_dims_m[1] = obcompass_getRoomDimY(hCmp);
    room_dims_m[2] = obcompass_getRoomDimZ(hCmp);

    /* Scaling factor to convert metres to pixels */
    float scale = room_pixels/MAX(MAX(room_dims_m[0], room_dims_m[1]), room_dims_m[2]);
    room_dims_pixels[0] = room_dims_m[0]*scale;
    room_dims_pixels[1] = room_dims_m[1]*scale;
    room_dims_pixels[2] = room_dims_m[2]*scale;

    float view_x = 27.0f , view_y = 12.0f;
    int xp_idx, yp_idx;

    if(topOrSideView==TOP_VIEW){
        xp_idx = 1;  /* Y */
        yp_idx = 0;  /* X */
    }
    else{
        xp_idx = 1;  /* Y */
        yp_idx = 2;  /* Z */
    }

    /* Background and border */
    g.setColour(Colours::lightgrey);
    g.drawRect(view_x, view_y, room_dims_pixels[xp_idx], room_dims_pixels[yp_idx], 2.000f);

    /* Grid grid lines and text */
    g.setColour(Colours::lightgrey);
    g.setFont(12.0f);
    g.setOpacity(0.15f);
    for(float i=0.0f; i<=room_dims_m[xp_idx]; i+=0.2f){
        /* Verticle lines */
        float line_x = view_x + room_dims_pixels[xp_idx] - i*room_dims_pixels[xp_idx]/room_dims_m[xp_idx];
        g.drawLine (line_x, view_y, line_x, view_y+room_dims_pixels[yp_idx], 1.000f);
    }
    for(int i=0; i<=(int)room_dims_m[xp_idx]; i++){
        /* Verticle lines */
        float line_x = view_x + room_dims_pixels[xp_idx] - (float)i*room_dims_pixels[xp_idx]/room_dims_m[xp_idx];
        g.setOpacity(0.35f);
        g.drawLine (line_x, view_y, line_x, view_y+room_dims_pixels[yp_idx], 1.000f);
        g.setOpacity(0.75f);
        if( (i%2)==0 )
            g.drawText(String(i), line_x-5, view_y+room_dims_pixels[yp_idx], 10, 10, Justification::centred, true);
    }
    g.setOpacity(0.15f);
    for(float i=0.0f; i<=room_dims_m[yp_idx]; i+=0.2f){
        /* Horizontal lines*/
        float line_y = view_y + room_dims_pixels[yp_idx] - i*room_dims_pixels[yp_idx]/room_dims_m[yp_idx];
        g.drawLine (view_x, line_y, view_x+room_dims_pixels[xp_idx], line_y, 1.000f);
    }
    for(int i=0; i<=(int)room_dims_m[yp_idx]; i++){
        /* Horizontal lines*/
        float line_y = view_y + room_dims_pixels[yp_idx] - (float)i*room_dims_pixels[yp_idx]/room_dims_m[yp_idx];
        g.setOpacity(0.35f);
        g.drawLine (view_x, line_y, view_x+room_dims_pixels[xp_idx], line_y, 1.000f);
        g.setOpacity(0.75f);
        if( (i%2)==0 )
            g.drawText(String(i), view_x+room_dims_pixels[xp_idx]+2, line_y-5, 10, 10, Justification::centred, true);
    }
    g.setFont(14.0f);
    g.drawText("y",  view_x + room_dims_pixels[xp_idx]/2.0f-5.0f, view_y+room_dims_pixels[yp_idx]+7.0f, 10, 10, Justification::centred, true);
    g.drawText(topOrSideView==TOP_VIEW ? "x" : "z",  view_x + room_dims_pixels[xp_idx]+12.0f, view_y+room_dims_pixels[yp_idx]/2.0f-5.0f, 10, 10, Justification::centred, true);

    /* Draw the estimated parameters / tracked targets */
    obcompass_plotting_data* pPlot;
    obcompass_getPlottingDataPtr(hCmp, &pPlot);
    if(pPlot->conStatus==OBCOMPASS_PLOTTING_CONTAINER_READY_NOT_PLOTTED){
        pPlot->conStatus = OBCOMPASS_PLOTTING_CONTAINER_READY_CURRENTLY_PLOTTING;
        float maxFreq = pPlot->pCentreFreqs[pPlot->nBands-1];

        /* Draw DoA vectors */
        if(drawDoAs){
            float rayLength = 0.75*MIN(room_dims_m[yp_idx], room_dims_m[xp_idx]);

            /* Loop over receivers and plot the vectors originating from them */
            for(int ri=0; ri<obcompass_getNumReceiversSAFE(hCmp); ri++){
                float orig_xy[2], dest_xy[2];
                orig_xy[0] = obcompass_getReceiverY(hCmp, ri);
                orig_xy[1] = topOrSideView==TOP_VIEW ? obcompass_getReceiverX(hCmp, ri) : obcompass_getReceiverZ(hCmp, ri);
                for(int doa=0; doa<pPlot->curNDirs[ri]; doa++){
                    dest_xy[0] = orig_xy[0] + pPlot->dirs_xyz_perRec[ri][doa*3+xp_idx] * rayLength;
                    dest_xy[1] = orig_xy[1] + pPlot->dirs_xyz_perRec[ri][doa*3+yp_idx] * rayLength;
                    float colScale_0_1 = sqrtf(pPlot->pCentreFreqs[pPlot->dirs_band_idx[ri][doa]] /maxFreq);
                    g.setColour(Colour::fromFloatRGBA(1.0f-colScale_0_1, colScale_0_1, 0.5f+colScale_0_1/2.0f, 0.5f));
                    g.drawLine(view_x + room_dims_pixels[xp_idx] - orig_xy[0]*scale,
                               view_y + room_dims_pixels[yp_idx] - orig_xy[1]*scale,
                               view_x + room_dims_pixels[xp_idx] - dest_xy[0]*scale,
                               view_y + room_dims_pixels[yp_idx] - dest_xy[1]*scale, 2.0f);
                }
            }
        }

        /* Draw intersections */
        if(drawIntersections){
            for(int it=0; it<pPlot->curNIntersections; it++){
                float pos_xy[2];
                float colScale_0_1 = sqrtf(pPlot->pCentreFreqs[pPlot->intersections_band_idx[it]] /maxFreq);
                pos_xy[0] = view_x + room_dims_pixels[xp_idx] - pPlot->intersections_xyz[it*3+xp_idx]*scale;
                pos_xy[1] = view_y + room_dims_pixels[yp_idx] - pPlot->intersections_xyz[it*3+yp_idx]  *scale;
                g.setColour(Colour::fromFloatRGBA(1.0f-colScale_0_1, colScale_0_1, 0.5f+colScale_0_1/2.0f, 0.5f));
                g.fillEllipse(pos_xy[0]-3.0f, pos_xy[1]-3.0f, 6.0f, 6.0f);
                g.setColour(Colours::lightgrey);
                g.drawEllipse(pos_xy[0]-3.0f, pos_xy[1]-3.0f, 6.0f, 6.0f,1.0f);
            }
        }

        /* Draw targets */
        if(drawTargets){
            for(int ti=0; ti<pPlot->curNtargets; ti++){
                float pos_xy[2], var[2];
                pos_xy[0] = view_x + room_dims_pixels[xp_idx] - pPlot->targets_pos_xyz[ti*3+xp_idx]*scale;
                pos_xy[1] = view_y + room_dims_pixels[yp_idx] - pPlot->targets_pos_xyz[ti*3+yp_idx]*scale;
                var[0] = 10.0f*sqrtf(MAX(pPlot->targets_var_xyz[ti*3+xp_idx], 2.23e-7f))*scale;
                var[1] = 10.0f*sqrtf(MAX(pPlot->targets_var_xyz[ti*3+yp_idx], 2.23e-7f))*scale;

                /* variance */
                g.setColour(Colours::orange);
                g.setOpacity(0.3f);
                g.fillEllipse(pos_xy[0]-var[0], pos_xy[1]-var[1], var[0]*2.0f, var[1]*2.0f);

                /* position */
                g.setOpacity(0.9f);
                g.fillEllipse(pos_xy[0]-5.0f, pos_xy[1]-5.0f, 10.0f, 10.0f);
                g.drawText(String(ti+1), pos_xy[0]+3.0f, pos_xy[1]-15.0f, 10.0f, 10.0f, Justification::centred);
                g.setColour(Colours::lightgrey);
                g.drawEllipse(pos_xy[0]-5.0f, pos_xy[1]-5.0f, 10.0f, 10.0f, 1.0f);
            }
        }

        /* Receiver grouping lines */
        if((obcompass_getRenderingMode(hCmp)==OBCOMPASS_RENDER_BINAURAL || obcompass_getRenderingMode(hCmp)==OBCOMPASS_RENDER_SH) && pPlot->recGrpIndices!=NULL){
            g.setColour(Colours::azure);
            g.setOpacity(0.4f);
            for(int gp=0; gp<pPlot->nRecGrps; gp++){
                for(int rg=0; rg<pPlot->nRecsPerGrp; rg++){
                    int tarrg = rg+1;
                    if (tarrg==pPlot->nRecsPerGrp)
                        tarrg = 0;
                    g.drawLine(view_x + room_dims_pixels[xp_idx] - scale*(obcompass_getReceiverY(hCmp, pPlot->recGrpIndices[gp*(pPlot->nRecsPerGrp)+rg])),
                               view_y + room_dims_pixels[yp_idx] - scale*(topOrSideView==TOP_VIEW ? obcompass_getReceiverX(hCmp, pPlot->recGrpIndices[gp*(pPlot->nRecsPerGrp)+rg]) :
                                                                          obcompass_getReceiverZ(hCmp, pPlot->recGrpIndices[gp*(pPlot->nRecsPerGrp)+rg])),
                               view_x + room_dims_pixels[xp_idx] - scale*(obcompass_getReceiverY(hCmp, pPlot->recGrpIndices[(gp)*(pPlot->nRecsPerGrp)+tarrg])),
                               view_y + room_dims_pixels[yp_idx] - scale*(topOrSideView==TOP_VIEW ? obcompass_getReceiverX(hCmp, pPlot->recGrpIndices[(gp)*(pPlot->nRecsPerGrp)+tarrg]) :
                                                                          obcompass_getReceiverZ(hCmp, pPlot->recGrpIndices[(gp)*(pPlot->nRecsPerGrp)+tarrg])), 2.0f);
                }
            }

            /* Draw interpolation weights text, under each receiver */
            g.setColour(Colours::cyan);
            g.setOpacity(0.8f);
            g.setFont(10.0f);
            for(int ri=0; ri<obcompass_getNumReceiversSAFE(hCmp); ri++){
                float point_x = view_x + room_dims_pixels[xp_idx] - scale*(obcompass_getReceiverY(hCmp, ri));
                float point_y = view_y + room_dims_pixels[yp_idx] - scale*(topOrSideView==TOP_VIEW ? obcompass_getReceiverX(hCmp, ri) : obcompass_getReceiverZ(hCmp, ri));
                g.drawText(String(pPlot->interpWeights[ri],3,false), point_x-12, point_y+10, 28, 12, Justification::centredLeft);
            }
        }

        pPlot->conStatus = OBCOMPASS_PLOTTING_CONTAINER_READY_HAS_BEEN_PLOTTED;
    }

    g.setFont(14.0f);
    /* Source icons */
    if(!obcompass_getEnableSourceTracker(hCmp)){
        for(int src=0; src<obcompass_getNumSources(hCmp); src++){
            float point_x = view_x + room_dims_pixels[xp_idx] - scale*(obcompass_getSourceY(hCmp, src));
            float point_y = view_y + room_dims_pixels[yp_idx] - scale*(topOrSideView==TOP_VIEW ? obcompass_getSourceX(hCmp, src) : obcompass_getSourceZ(hCmp, src));
            srcIcon.setBounds(point_x-5.0f, point_y-5.0f, 10.0f, 10.0f);
            g.setOpacity(0.9f);
            g.setColour(Colours::orange);
            g.fillEllipse(srcIcon);
            g.drawText(String(src+1), srcIcon.translated(8.0f, -8.0f), Justification::centred);
            g.setColour(Colours::lightgrey);
            g.drawEllipse(srcIcon, 1.0f);
        }
    }

    /* Receiver icons */
    for(int rec=0; rec<obcompass_getNumReceiversSAFE(hCmp); rec++){
        float point_x = view_x + room_dims_pixels[xp_idx] - scale*(obcompass_getReceiverY(hCmp, rec));
        float point_y = view_y + room_dims_pixels[yp_idx] - scale*(topOrSideView==TOP_VIEW ? obcompass_getReceiverX(hCmp, rec) : obcompass_getReceiverZ(hCmp, rec));
        recIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        g.setOpacity(0.9f);
        g.setColour(Colours::magenta);
        g.fillEllipse(recIcon);
        g.drawText(String(rec+1), recIcon.translated(8.0f, -8.0f), Justification::centred);
        g.setColour(Colours::lightgrey);
        g.drawEllipse(recIcon, 1.0f);
    }

    /* Listener icon */
    if(obcompass_getRenderingMode(hCmp)==OBCOMPASS_RENDER_BINAURAL || obcompass_getRenderingMode(hCmp)==OBCOMPASS_RENDER_SH){
        float point_x = view_x + room_dims_pixels[xp_idx] - scale*(obcompass_getListenerY(hCmp));
        float point_y = view_y + room_dims_pixels[yp_idx] - scale*(topOrSideView==TOP_VIEW ? obcompass_getListenerX(hCmp) : obcompass_getListenerZ(hCmp));
        lstIcon.setBounds(point_x-iconRadius*1.2f, point_y-iconRadius*1.2f, iconWidth*1.2f, iconWidth*1.2f);
        g.setOpacity(0.9f);
        g.setColour(Colours::darkcyan);
        g.fillEllipse(lstIcon);
        g.setColour(Colours::lightgrey);
        g.drawEllipse(lstIcon, 1.0f);
    }
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

    Rectangle<int> recIcon, srcIcon;
    float room_dims_pixels[3], room_dims_m[3];
    room_dims_m[0] = obcompass_getRoomDimX(hCmp);
    room_dims_m[1] = obcompass_getRoomDimY(hCmp);
    room_dims_m[2] = obcompass_getRoomDimZ(hCmp);

    /* Scaling factor to convert metres to pixels */
    float scale = room_pixels/MAX(MAX(room_dims_m[0], room_dims_m[1]), room_dims_m[2]);
    room_dims_pixels[0] = room_dims_m[0]*scale;
    room_dims_pixels[1] = room_dims_m[1]*scale;
    room_dims_pixels[2] = room_dims_m[2]*scale;

    float view_x = 27.0f; float view_y = 12.0f;

    if(topOrSideView==TOP_VIEW){
        /* REC */
        for(int rec=0; rec<obcompass_getNumReceivers(hCmp); rec++){
            float point_x = view_x + room_dims_pixels[1] - scale*(obcompass_getReceiverY(hCmp, rec));
            float point_y = view_y + room_dims_pixels[0] - scale*(obcompass_getReceiverX(hCmp, rec));
            recIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
            if(recIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
                receiverIconIsClicked = true;
                indexOfClickedIcon = rec;
                return;
            }
        }

        /* SRC */
        for(int src=0; src<obcompass_getNumSources(hCmp); src++){
            float point_x = view_x + room_dims_pixels[1] - scale*(obcompass_getSourceY(hCmp, src));
            float point_y = view_y + room_dims_pixels[0] - scale*(obcompass_getSourceX(hCmp, src));
            srcIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
            if(srcIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
                sourceIconIsClicked = true;
                indexOfClickedIcon = src;
                return;
            }
        }

        /* LST */
        float point_x = view_x + room_dims_pixels[1] - scale*(obcompass_getListenerY(hCmp));
        float point_y = view_y + room_dims_pixels[0] - scale*(obcompass_getListenerX(hCmp));
        srcIcon.setBounds(point_x-iconRadius*1.3f, point_y-iconRadius*1.3f, iconWidth*1.3f, iconWidth*1.3f);
        if(srcIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
            listenerIconIsClicked = true;
            indexOfClickedIcon = 0;
            return;
        }
    }
    else if(topOrSideView==SIDE_VIEW){
        /* REC */
        for(int rec=0; rec<obcompass_getNumReceivers(hCmp); rec++){
            float point_x = view_x + room_dims_pixels[1] - scale*(obcompass_getReceiverY(hCmp, rec));
            float point_y = view_y + room_dims_pixels[2] - scale*(obcompass_getReceiverZ(hCmp, rec));
            recIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
            if(recIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
                receiverIconIsClicked = true;
                indexOfClickedIcon = rec;
                return;
            }
        }

        /* SRC */
        for(int src=0; src<obcompass_getNumSources(hCmp); src++){
            float point_x = view_x + room_dims_pixels[1] - scale*(obcompass_getSourceY(hCmp, src));
            float point_y = view_y + room_dims_pixels[2] - scale*(obcompass_getSourceZ(hCmp, src));
            srcIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
            if(srcIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
                sourceIconIsClicked = true;
                indexOfClickedIcon = src;
                return;
            }
        }

        /* LST */
        float point_x = view_x + room_dims_pixels[1] - scale*(obcompass_getListenerY(hCmp));
        float point_y = view_y + room_dims_pixels[2] - scale*(obcompass_getListenerZ(hCmp));
        srcIcon.setBounds(point_x-iconRadius*1.2f, point_y-iconRadius*1.2f, iconWidth*1.2f, iconWidth*1.2f);
        if(srcIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
            listenerIconIsClicked = true;
            indexOfClickedIcon = 0;
            return;
        }
    }
    //[/UserCode_mouseDown]
}

void sceneView::mouseDrag (const juce::MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...

    float room_dims_pixels[3], room_dims_m[3];
    float scale;
    Point<float> point;
    float view_x, view_y;
    view_x = 27.0f; view_y = 12.0f;

    if(receiverIconIsClicked || sourceIconIsClicked || listenerIconIsClicked){
        /* Scaling factor to convert metres to pixels */
        room_dims_m[0] = obcompass_getRoomDimX(hCmp);
        room_dims_m[1] = obcompass_getRoomDimY(hCmp);
        room_dims_m[2] = obcompass_getRoomDimZ(hCmp);
        scale = room_pixels/MAX(MAX(room_dims_m[0], room_dims_m[1]), room_dims_m[2]);
        room_dims_pixels[0] = room_dims_m[0]*scale;
        room_dims_pixels[1] = room_dims_m[1]*scale;
        room_dims_pixels[2] = room_dims_m[2]*scale;
    }

    if(listenerIconIsClicked){
        switch(topOrSideView){
            case TOP_VIEW:
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                obcompass_setListenerY(hCmp, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                obcompass_setListenerX(hCmp, -(point.getY() - view_y - room_dims_pixels[0])/scale);
                break;

            case SIDE_VIEW:
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                obcompass_setListenerY(hCmp, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                obcompass_setListenerZ(hCmp, -(point.getY() - view_y - room_dims_pixels[2])/scale);
                break;
            default: break;
        }
    }
    else if(receiverIconIsClicked){
        switch(topOrSideView){
            case TOP_VIEW:
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                obcompass_setReceiverY(hCmp, indexOfClickedIcon, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                obcompass_setReceiverX(hCmp, indexOfClickedIcon, -(point.getY() - view_y - room_dims_pixels[0])/scale);
                break;

            case SIDE_VIEW:
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                obcompass_setReceiverY(hCmp, indexOfClickedIcon, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                obcompass_setReceiverZ(hCmp, indexOfClickedIcon, -(point.getY() - view_y - room_dims_pixels[2])/scale);
                break;
            default: break;
        }
    }
    else if(sourceIconIsClicked){
        switch(topOrSideView){
            case TOP_VIEW:
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                obcompass_setSourceY(hCmp, indexOfClickedIcon, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                obcompass_setSourceX(hCmp, indexOfClickedIcon, -(point.getY() - view_y - room_dims_pixels[0])/scale);
                break;

            case SIDE_VIEW:
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                obcompass_setSourceY(hCmp, indexOfClickedIcon, -(point.getX() - view_x - room_dims_pixels[1])/scale);
                obcompass_setSourceZ(hCmp, indexOfClickedIcon, -(point.getY() - view_y - room_dims_pixels[2])/scale);
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
    receiverIconIsClicked = false;
    sourceIconIsClicked = false;
    listenerIconIsClicked = false;
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

