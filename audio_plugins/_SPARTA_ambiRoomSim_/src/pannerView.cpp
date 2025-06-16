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

#include "pannerView.h"

const float iconWidth = 8.0f;
const float iconRadius = iconWidth/2.0f;
const float room_pixels = 200;

pannerView::pannerView (PluginProcessor& p, int _width, int _height) : processor(p)
{
    setSize(_width, _height);
    
    hAmbi = processor.getFXHandle();
    width = _width;
    height = _height;
    topOrSideView = TOP_VIEW; /* default */
    sourceIconIsClicked = false;
    receiverIconIsClicked = false;
}

pannerView::~pannerView()
{
}

void pannerView::paint (juce::Graphics& g)
{
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
    //float centre_x = view_x+room_dims_pixels[1]/2.0f;
    //float centre_y = view_y+room_dims_pixels[0]/2.0f;
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
            g.drawText(String(i), line_x-5, view_y+room_dims_pixels[0], 12, 10, Justification::centred, true);
    }
    for(int i=0; i<=(int)room_dims_m[0]; i++){
        /* Horizontal lines*/
        float line_y = view_y + room_dims_pixels[0] - (float)i*room_dims_pixels[0]/room_dims_m[0];
        g.setOpacity(0.25f);
        g.drawLine (view_x, line_y, view_x+room_dims_pixels[1], line_y, 1.000f);
        g.setOpacity(0.75f);
        if( (i%2)==0 )
            g.drawText(String(i), view_x+room_dims_pixels[1]+2, line_y-5, 12, 10, Justification::centred, true);
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
    //centre_x = view_x+room_dims_pixels[1]/2.0f;
    //centre_y = view_y+room_dims_pixels[2]/2.0f;
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
            g.drawText(String(i), line_x-5, view_y+room_dims_pixels[2], 12, 10, Justification::centred, true);
    }
    for(int i=0; i<=(int)room_dims_m[2]; i++){
        /* Horizontal lines*/
        float line_y = view_y + room_dims_pixels[2] - (float)i*room_dims_pixels[2]/room_dims_m[2];
        g.setOpacity(0.25f);
        g.drawLine (view_x, line_y, view_x+room_dims_pixels[1], line_y, 1.000f);
        g.setOpacity(0.75f);
        if( (i%2)==0 )
            g.drawText(String(i), view_x+room_dims_pixels[1]+2, line_y-5, 12, 10, Justification::centred, true);
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
}

void pannerView::resized()
{
}

void pannerView::mouseDown (const juce::MouseEvent& e)
{
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
}

void pannerView::mouseDrag (const juce::MouseEvent& e)
{
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
                processor.setParameterValue("sourceY" + juce::String(indexOfClickedIcon), -(point.getX() - view_x - room_dims_pixels[1])/scale);
                processor.setParameterValue("sourceX" + juce::String(indexOfClickedIcon), -(point.getY() - view_y - room_dims_pixels[0])/scale);
                break;

            case SIDE_VIEW:
                view_x = 27.0f; view_y = 240.0f;
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                processor.setParameterValue("sourceY" + juce::String(indexOfClickedIcon), -(point.getX() - view_x - room_dims_pixels[1])/scale);
                processor.setParameterValue("sourceZ" + juce::String(indexOfClickedIcon), -(point.getY() - view_y - room_dims_pixels[2])/scale);
                break;
            default: break;
        }
    }
    else if(receiverIconIsClicked){
        switch(topOrSideView){
            case TOP_VIEW:
                view_x = 27.0f; view_y = 12.0f;
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                processor.setParameterValue("receiverY" + juce::String(indexOfClickedIcon), -(point.getX() - view_x - room_dims_pixels[1])/scale);
                processor.setParameterValue("receiverX" + juce::String(indexOfClickedIcon), -(point.getY() - view_y - room_dims_pixels[0])/scale);
                break;

            case SIDE_VIEW:
                view_x = 27.0f; view_y = 240.0f;
                point.setXY((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2);
                processor.setParameterValue("receiverY" + juce::String(indexOfClickedIcon), -(point.getX() - view_x - room_dims_pixels[1])/scale);
                processor.setParameterValue("receiverZ" + juce::String(indexOfClickedIcon), -(point.getY() - view_y - room_dims_pixels[2])/scale);
                break;
            default: break;
        }
    }
}

void pannerView::mouseUp (const juce::MouseEvent& /*e*/)
{
    sourceIconIsClicked = false;
    receiverIconIsClicked = false;
}

void pannerView::refreshPanView()
{
    repaint();
}
