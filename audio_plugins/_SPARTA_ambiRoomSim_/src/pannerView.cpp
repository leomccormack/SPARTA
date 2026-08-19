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
    float view_x = 27.0f , view_y = 12.0f;
    g.setColour(Colours::lightgrey);
    g.drawRect(view_x, view_y, room_dims_pixels[1], room_dims_pixels[0], 2.000f);

    g.setFont(10.0f);
    for(int i=0; i<=(int)room_dims_m[1]; i++){
        float line_x = view_x + room_dims_pixels[1] - (float)i*room_dims_pixels[1]/room_dims_m[1];
        g.setOpacity(0.25f);
        g.drawLine (line_x, view_y, line_x, view_y+room_dims_pixels[0], 1.000f);
        g.setOpacity(0.75f);
        if( (i%2)==0 )
            g.drawText(String(i), line_x-5, view_y+room_dims_pixels[0], 12, 10, Justification::centred, true);
    }
    for(int i=0; i<=(int)room_dims_m[0]; i++){
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

    /* Source paths + icons */
    PathBank& pb = processor.getPathBank();
    for(int src=0; src<ambi_roomsim_getNumSources(hAmbi); src++){
        drawPathOnView(g, pb.getSourcePath(src), src, view_x, view_y, scale,
                       room_dims_pixels[1], room_dims_pixels[0], true, false);
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getSourceY(hAmbi, src));
        float point_y = view_y + room_dims_pixels[0] - scale*(ambi_roomsim_getSourceX(hAmbi, src));
        srcIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        tmpIcon.setBounds(point_x-iconRadius*3, point_y-iconRadius, iconWidth*3, iconWidth);
        g.setColour(Colours::orange);
        g.setOpacity(0.7f);
        g.fillEllipse(srcIcon);
        g.setOpacity(0.8f);
        g.drawText(String(src+1), tmpIcon.translated(8.0f, -8.0f), Justification::centred);
    }

    /* Receiver paths + icons */
    for(int rec=0; rec<ambi_roomsim_getNumReceivers(hAmbi); rec++){
        drawPathOnView(g, pb.getReceiverPath(rec), rec, view_x, view_y, scale,
                       room_dims_pixels[1], room_dims_pixels[0], true, true);
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getReceiverY(hAmbi, rec));
        float point_y = view_y + room_dims_pixels[0] - scale*(ambi_roomsim_getReceiverX(hAmbi, rec));
        recIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        tmpIcon.setBounds(point_x-iconRadius*3, point_y-iconRadius, iconWidth*3, iconWidth);
        g.setColour(Colours::magenta);
        g.setOpacity(0.7f);
        g.fillEllipse(recIcon);
        g.setOpacity(0.8f);
        g.drawText(String(rec+1), tmpIcon.translated(8.0f, -8.0f), Justification::centred);
    }


    /****** DRAW SIDE VIEW *****/
    view_x = 27.0f; view_y = 240.0f;
    g.setColour(Colours::lightgrey);
    g.drawRect(view_x, view_y, room_dims_pixels[1], room_dims_pixels[2], 2.000f);

    g.setFont(10.0f);
    for(int i=0; i<=(int)room_dims_m[1]; i++){
        float line_x = view_x + room_dims_pixels[1] - (float)i*room_dims_pixels[1]/room_dims_m[1];
        g.setOpacity(0.25f);
        g.drawLine (line_x, view_y, line_x, view_y+room_dims_pixels[2], 1.000f);
        g.setOpacity(0.75f);
        if( (i%2)==0 )
            g.drawText(String(i), line_x-5, view_y+room_dims_pixels[2], 12, 10, Justification::centred, true);
    }
    for(int i=0; i<=(int)room_dims_m[2]; i++){
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
    for(int src=0; src<ambi_roomsim_getNumSources(hAmbi); src++){
        drawPathOnView(g, pb.getSourcePath(src), src, view_x, view_y, scale,
                       room_dims_pixels[1], room_dims_pixels[2], false, false);
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getSourceY(hAmbi, src));
        float point_y = view_y + room_dims_pixels[2] - scale*(ambi_roomsim_getSourceZ(hAmbi, src));
        srcIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        g.setColour(Colours::orange);
        g.setOpacity(0.7f);
        g.fillEllipse(srcIcon);
        g.setOpacity(0.8f);
        g.drawText(String(src+1), srcIcon.translated(8.0f, -8.0f), Justification::centred);
    }

    /* Receiver icons */
    for(int rec=0; rec<ambi_roomsim_getNumReceivers(hAmbi); rec++){
        drawPathOnView(g, pb.getReceiverPath(rec), rec, view_x, view_y, scale,
                       room_dims_pixels[1], room_dims_pixels[2], false, true);
        float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getReceiverY(hAmbi, rec));
        float point_y = view_y + room_dims_pixels[2] - scale*(ambi_roomsim_getReceiverZ(hAmbi, rec));
        recIcon.setBounds(point_x-iconRadius, point_y-iconRadius, iconWidth, iconWidth);
        g.setColour(Colours::magenta);
        g.setOpacity(0.7f);
        g.fillEllipse(recIcon);
        g.setOpacity(0.8f);
        g.drawText(String(rec+1), recIcon.translated(8.0f, -8.0f), Justification::centred);
    }

    /* Draw spline handles for the selected (enabled) path */
    if (editingObjectIdx >= 0 && isCurrentPathEnabled()) {
        const PathData* sp = nullptr;
        if (editingIsReceiver)
            sp = &pb.getReceiverPath(editingObjectIdx);
        else
            sp = &pb.getSourcePath(editingObjectIdx);
        if (sp != nullptr) {
            view_x = 27.0f; view_y = 12.0f;
            drawPathHandlesOnView(g, *sp, editingObjectIdx, view_x, view_y, scale,
                                  room_dims_pixels[1], room_dims_pixels[0], true, editingIsReceiver);
            view_x = 27.0f; view_y = 240.0f;
            drawPathHandlesOnView(g, *sp, editingObjectIdx, view_x, view_y, scale,
                                  room_dims_pixels[1], room_dims_pixels[2], false, editingIsReceiver);
        }
    }
}

void pannerView::drawPathOnView(juce::Graphics& g, const PathData& path,
                                int objIdx,
                                float view_x, float view_y,
                                float scale, float room_w, float room_h,
                                bool isTopView, bool isReceiver)
{
    if (path.keyframes.size() < 2) return;

    /* Every path is drawn so switching sources/receivers never hides them.
       Disabled paths are dimmed to show they are inactive. */
    juce::Colour col = getPathColour(isReceiver, objIdx);
    const float colAlpha = path.enabled ? 1.0f : 0.30f;

    /* Draw the path curve */
    double T0 = path.keyframes.front().timeSeconds;
    double Tn = path.keyframes.back().timeSeconds;
    double span = (Tn > T0) ? Tn - T0 : 1.0;

    float px0 = 0, py0 = 0;
    for (int s = 0; s <= 80; ++s) {
        double t = T0 + (double)s / 80.0 * span;
        float x, y, z;
        path.evaluate(t, x, y, z);
        float px = view_x + room_w - scale * y;
        float py;
        if (isTopView)
            py = view_y + room_h - scale * x;
        else
            py = view_y + room_h - scale * z;
        if (s > 0) {
            g.setColour(col.withAlpha(0.35f * colAlpha));
            g.drawLine(px0, py0, px, py, 1.0f);
        }
        px0 = px; py0 = py;
    }

    /* Draw keyframe markers */
    float kfSize = 5.0f;
    for (size_t k = 0; k < path.keyframes.size(); ++k) {
        auto& kf = path.keyframes[k];
        float kx, ky;
        if (isTopView) {
            kx = view_x + room_w - scale * kf.y;
            ky = view_y + room_h - scale * kf.x;
        } else {
            kx = view_x + room_w - scale * kf.y;
            ky = view_y + room_h - scale * kf.z;
        }
        Path diamond;
        diamond.startNewSubPath(kx, ky - kfSize);
        diamond.lineTo(kx + kfSize, ky);
        diamond.lineTo(kx, ky + kfSize);
        diamond.lineTo(kx - kfSize, ky);
        diamond.closeSubPath();
        g.setColour(col.withAlpha(0.9f * colAlpha));
        g.fillPath(diamond);
        g.setColour(col.brighter(0.5f).withAlpha(colAlpha));
        g.strokePath(diamond, PathStrokeType(1.0f));
    }
}

/* Projects one of a keyframe's spline handles into screen space for the
   given view. The in/out handles sit at P - mIn/3 and P + mOut/3 (one third
   of the tangent, matching the cubic Bezier control points of the Hermite
   segment). */
void pannerView::getHandleScreenPos(const Keyframe& kf, bool isIn, bool isTopView,
                                    float view_x, float view_y, float scale,
                                    float room_w, float room_h, float& px, float& py) const
{
    float hx, hy, hz;
    if (isIn) {
        hx = kf.x - kf.txIn / 3.0f;
        hy = kf.y - kf.tyIn / 3.0f;
        hz = kf.z - kf.tzIn / 3.0f;
    } else {
        hx = kf.x + kf.txOut / 3.0f;
        hy = kf.y + kf.tyOut / 3.0f;
        hz = kf.z + kf.tzOut / 3.0f;
    }
    px = view_x + room_w - scale * hy;
    py = isTopView ? view_y + room_h - scale * hx
                   : view_y + room_h - scale * hz;
}

/* Draws a line + small square marker from each keyframe to its in/out
   handles, so the user can grab them to reshape the spline. */
void pannerView::drawPathHandlesOnView(juce::Graphics& g, const PathData& path,
                                       int objIdx,
                                       float view_x, float view_y,
                                       float scale, float room_w, float room_h,
                                       bool isTopView, bool isReceiver)
{
    juce::Colour col = getPathColour(isReceiver, objIdx);
    float px, py, hx, hy;
    for (size_t k = 0; k < path.keyframes.size(); ++k) {
        const auto& kf = path.keyframes[k];
        px = view_x + room_w - scale * kf.y;
        py = isTopView ? view_y + room_h - scale * kf.x : view_y + room_h - scale * kf.z;
        for (int which = 0; which < 2; ++which) {
            bool isIn = (which == 0);
            getHandleScreenPos(kf, isIn, isTopView, view_x, view_y, scale, room_w, room_h, hx, hy);
            g.setColour(col.withAlpha(0.6f));
            g.drawLine(px, py, hx, hy, 1.0f);
            g.setColour(col.brighter(0.8f));
            g.fillRect(hx - 1.5f, hy - 1.5f, 3.0f, 3.0f);
            g.setColour(Colours::white);
            g.drawRect(hx - 1.5f, hy - 1.5f, 3.0f, 3.0f);
        }
    }
}

/* Whether the currently selected path exists and is enabled. Returns true
   when nothing is selected or the index is out of range, so unrelated
   interactions are never blocked; Move-mode icon dragging is gated on the
   path being disabled. */
bool pannerView::isCurrentPathEnabled() const
{
    if (editingObjectIdx < 0) return false;
    PathBank& pb = processor.getPathBank();
    if (editingIsReceiver)
        return pb.getReceiverPath(editingObjectIdx).enabled;
    return pb.getSourcePath(editingObjectIdx).enabled;
}

void pannerView::pixelToSourceCoords(float px, float py,
                                     float view_x, float view_y,
                                     float scale, float room_w, float room_h,
                                     bool isTopView,
                                     float& outX, float& outY, float& outZ) const
{
    float room_dims_m[3];
    room_dims_m[0] = ambi_roomsim_getRoomDimX(hAmbi);
    room_dims_m[1] = ambi_roomsim_getRoomDimY(hAmbi);
    room_dims_m[2] = ambi_roomsim_getRoomDimZ(hAmbi);
    outY = -(px - view_x - room_w) / scale;
    if (isTopView) {
        outX = -(py - view_y - room_h) / scale;
        outZ = room_dims_m[2] / 2.0f;
    } else {
        outX = 0.0f;
        outZ = -(py - view_y - room_h) / scale;
    }
    outX = jlimit(0.0f, room_dims_m[0], outX);
    outY = jlimit(0.0f, room_dims_m[1], outY);
    outZ = jlimit(0.0f, room_dims_m[2], outZ);
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

    float scale = room_pixels/MAX(MAX(room_dims_m[0], room_dims_m[1]), room_dims_m[2]);
    room_dims_pixels[0] = room_dims_m[0]*scale;
    room_dims_pixels[1] = room_dims_m[1]*scale;
    room_dims_pixels[2] = room_dims_m[2]*scale;

    if (interactionMode == InteractionMode::Move) {
        /* While the path is enabled only its nodes are edited, so icon
           dragging is blocked; a disabled path leaves icons draggable. */
        if (isCurrentPathEnabled()) return;

        /* Existing mouseDown logic: select and drag source/receiver icons */

        /* TOP VIEW */
        float view_x = 27.0f; float view_y = 12.0f;
        /* Receivers are painted on top of sources and, within each type, the
           last icon drawn is the topmost. Hit-test front-to-back so the
           visible icon is the one grabbed (overlapping icons previously
           grabbed the hidden source instead of the receiver). */
        for(int rec=ambi_roomsim_getNumReceivers(hAmbi)-1; rec>=0; rec--){
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
        for(int src=ambi_roomsim_getNumSources(hAmbi)-1; src>=0; src--){
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

        /* SIDE VIEW */
        view_x = 27.0f; view_y = 240.0f;
        for(int rec=ambi_roomsim_getNumReceivers(hAmbi)-1; rec>=0; rec--){
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
        for(int src=ambi_roomsim_getNumSources(hAmbi)-1; src>=0; src--){
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
    }
    else if (interactionMode == InteractionMode::AddKeyframe) {
        PathBank& pb = processor.getPathBank();
        float kfSize = 5.0f;
        float view_x, view_y;

        /* 1) Spline handles of the selected (enabled) path take first
              priority, so fine control points can be grabbed even when they
              overlap a keyframe marker. */
        if (editingObjectIdx >= 0 && isCurrentPathEnabled()) {
            const PathData* sp = nullptr;
            if (editingIsReceiver)
                sp = &pb.getReceiverPath(editingObjectIdx);
            else
                sp = &pb.getSourcePath(editingObjectIdx);
            if (sp != nullptr) {
                for (int view = 0; view < 2; ++view) {
                    bool isTop = (view == 0);
                    view_x = 27.0f; view_y = isTop ? 12.0f : 240.0f;
                    float room_w = room_dims_pixels[1];
                    float room_h = isTop ? room_dims_pixels[0] : room_dims_pixels[2];
                    for (size_t k = 0; k < sp->keyframes.size(); ++k) {
                        const auto& kf = sp->keyframes[k];
                        for (int which = 0; which < 2; ++which) {
                            bool isIn = (which == 0);
                            float hx, hy;
                            getHandleScreenPos(kf, isIn, isTop, view_x, view_y, scale, room_w, room_h, hx, hy);
                            if (fabs(e.getMouseDownX() - hx) < kfSize + 3 && fabs(e.getMouseDownY() - hy) < kfSize + 3) {
                                draggingHandle = true;
                                dragHandleKeyframeIdx = (int)k;
                                dragHandleIsIn = isIn;
                                topOrSideView = isTop ? TOP_VIEW : SIDE_VIEW;
                                return;
                            }
                        }
                    }
                }
            }
        }

        /* 2) Keyframe nodes. Only nodes of enabled paths are grabbable;
              disabled paths are locked and their nodes are not drawn. */

        /* Check top view first. Receiver paths are painted over source
           paths, so their nodes are hit-tested first (front-to-back). */
        view_x = 27.0f; view_y = 12.0f;
        for (int rec = ambi_roomsim_getNumReceivers(hAmbi)-1; rec >= 0; --rec) {
            auto& path = pb.getReceiverPath(rec);
            if (!path.enabled) continue;
            for (size_t k = 0; k < path.keyframes.size(); ++k) {
                auto& kf = path.keyframes[k];
                float kx = view_x + room_dims_pixels[1] - scale * kf.y;
                float ky = view_y + room_dims_pixels[0] - scale * kf.x;
                if (fabs(e.getMouseDownX() - kx) < kfSize + 3 && fabs(e.getMouseDownY() - ky) < kfSize + 3) {
                    draggingKeyframe = true;
                    dragKeyframeIdx = (int)k;
                    dragPathObjIdx = rec;
                    dragPathIsReceiver = true;
                    dragStartX = e.getMouseDownX();
                    dragStartY = e.getMouseDownY();
                    topOrSideView = TOP_VIEW;
                    return;
                }
            }
        }
        for (int src = ambi_roomsim_getNumSources(hAmbi)-1; src >= 0; --src) {
            auto& path = pb.getSourcePath(src);
            if (!path.enabled) continue;
            for (size_t k = 0; k < path.keyframes.size(); ++k) {
                auto& kf = path.keyframes[k];
                float kx = view_x + room_dims_pixels[1] - scale * kf.y;
                float ky = view_y + room_dims_pixels[0] - scale * kf.x;
                if (fabs(e.getMouseDownX() - kx) < kfSize + 3 && fabs(e.getMouseDownY() - ky) < kfSize + 3) {
                    draggingKeyframe = true;
                    dragKeyframeIdx = (int)k;
                    dragPathObjIdx = src;
                    dragPathIsReceiver = false;
                    dragStartX = e.getMouseDownX();
                    dragStartY = e.getMouseDownY();
                    topOrSideView = TOP_VIEW;
                    return;
                }
            }
        }

        /* Check side view */
        view_x = 27.0f; view_y = 240.0f;
        for (int rec = ambi_roomsim_getNumReceivers(hAmbi)-1; rec >= 0; --rec) {
            auto& path = pb.getReceiverPath(rec);
            if (!path.enabled) continue;
            for (size_t k = 0; k < path.keyframes.size(); ++k) {
                auto& kf = path.keyframes[k];
                float kx = view_x + room_dims_pixels[1] - scale * kf.y;
                float ky = view_y + room_dims_pixels[2] - scale * kf.z;
                if (fabs(e.getMouseDownX() - kx) < kfSize + 3 && fabs(e.getMouseDownY() - ky) < kfSize + 3) {
                    draggingKeyframe = true;
                    dragKeyframeIdx = (int)k;
                    dragPathObjIdx = rec;
                    dragPathIsReceiver = true;
                    dragStartX = e.getMouseDownX();
                    dragStartY = e.getMouseDownY();
                    topOrSideView = SIDE_VIEW;
                    return;
                }
            }
        }
        for (int src = ambi_roomsim_getNumSources(hAmbi)-1; src >= 0; --src) {
            auto& path = pb.getSourcePath(src);
            if (!path.enabled) continue;
            for (size_t k = 0; k < path.keyframes.size(); ++k) {
                auto& kf = path.keyframes[k];
                float kx = view_x + room_dims_pixels[1] - scale * kf.y;
                float ky = view_y + room_dims_pixels[2] - scale * kf.z;
                if (fabs(e.getMouseDownX() - kx) < kfSize + 3 && fabs(e.getMouseDownY() - ky) < kfSize + 3) {
                    draggingKeyframe = true;
                    dragKeyframeIdx = (int)k;
                    dragPathObjIdx = src;
                    dragPathIsReceiver = false;
                    dragStartX = e.getMouseDownX();
                    dragStartY = e.getMouseDownY();
                    topOrSideView = SIDE_VIEW;
                    return;
                }
            }
        }

        /* 3) Source/receiver icons. While the selected path is enabled the
              room is in path-editing mode and only its nodes are editable,
              so pressing an icon is just remembered (mouseUp must not create
              a keyframe under it). With the path disabled (or nothing
              selected) the icons become draggable again, exactly as in
              Move mode. */
        bool iconsDraggable = !(editingObjectIdx >= 0 && isCurrentPathEnabled());
        view_x = 27.0f; view_y = 12.0f;
        for (int rec = ambi_roomsim_getNumReceivers(hAmbi)-1; rec >= 0; --rec) {
            float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getReceiverY(hAmbi, rec));
            float point_y = view_y + room_dims_pixels[0] - scale*(ambi_roomsim_getReceiverX(hAmbi, rec));
            recIcon.setBounds((int)(point_x-iconRadius), (int)(point_y-iconRadius), (int)iconWidth, (int)iconWidth);
            if (recIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
                if (!iconsDraggable) { mouseDownOnIcon = true; return; }
                receiverIconIsClicked = true;
                indexOfClickedIcon = rec;
                topOrSideView = TOP_VIEW;
                return;
            }
        }
        for (int src = ambi_roomsim_getNumSources(hAmbi)-1; src >= 0; --src) {
            float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getSourceY(hAmbi, src));
            float point_y = view_y + room_dims_pixels[0] - scale*(ambi_roomsim_getSourceX(hAmbi, src));
            srcIcon.setBounds((int)(point_x-iconRadius), (int)(point_y-iconRadius), (int)iconWidth, (int)iconWidth);
            if (srcIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
                if (!iconsDraggable) { mouseDownOnIcon = true; return; }
                sourceIconIsClicked = true;
                indexOfClickedIcon = src;
                topOrSideView = TOP_VIEW;
                return;
            }
        }
        view_x = 27.0f; view_y = 240.0f;
        for (int rec = ambi_roomsim_getNumReceivers(hAmbi)-1; rec >= 0; --rec) {
            float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getReceiverY(hAmbi, rec));
            float point_y = view_y + room_dims_pixels[2] - scale*(ambi_roomsim_getReceiverZ(hAmbi, rec));
            recIcon.setBounds((int)(point_x-iconRadius), (int)(point_y-iconRadius), (int)iconWidth, (int)iconWidth);
            if (recIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
                if (!iconsDraggable) { mouseDownOnIcon = true; return; }
                receiverIconIsClicked = true;
                indexOfClickedIcon = rec;
                topOrSideView = SIDE_VIEW;
                return;
            }
        }
        for (int src = ambi_roomsim_getNumSources(hAmbi)-1; src >= 0; --src) {
            float point_x = view_x + room_dims_pixels[1] - scale*(ambi_roomsim_getSourceY(hAmbi, src));
            float point_y = view_y + room_dims_pixels[2] - scale*(ambi_roomsim_getSourceZ(hAmbi, src));
            srcIcon.setBounds((int)(point_x-iconRadius), (int)(point_y-iconRadius), (int)iconWidth, (int)iconWidth);
            if (srcIcon.expanded(4, 4).contains(e.getMouseDownPosition())){
                if (!iconsDraggable) { mouseDownOnIcon = true; return; }
                sourceIconIsClicked = true;
                indexOfClickedIcon = src;
                topOrSideView = SIDE_VIEW;
                return;
            }
        }
    }
}

void pannerView::mouseDrag (const juce::MouseEvent& e)
{
    float room_dims_pixels[3], room_dims_m[3];
    float scale;
    Point<float> point;
    float view_x, view_y;

    /* Dragging a spline handle: convert the cursor position to room
       coordinates and set the tangent of the grabbed keyframe. The handle is
       at P + m/3, so the tangent is m = 3 * (cursor - P); the incoming
       handle mirrors this sign. Only the two axes visible in the current
       view are updated (x/y in the top view, y/z in the side view). */
    if (draggingHandle && interactionMode == InteractionMode::AddKeyframe) {
        room_dims_m[0] = ambi_roomsim_getRoomDimX(hAmbi);
        room_dims_m[1] = ambi_roomsim_getRoomDimY(hAmbi);
        room_dims_m[2] = ambi_roomsim_getRoomDimZ(hAmbi);
        scale = room_pixels/MAX(MAX(room_dims_m[0], room_dims_m[1]), room_dims_m[2]);
        room_dims_pixels[0] = room_dims_m[0]*scale;
        room_dims_pixels[1] = room_dims_m[1]*scale;
        room_dims_pixels[2] = room_dims_m[2]*scale;

        PathBank& pb = processor.getPathBank();
        {
            const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
            auto& path = editingIsReceiver ? pb.getReceiverPath(editingObjectIdx)
                                           : pb.getSourcePath(editingObjectIdx);
            if (dragHandleKeyframeIdx >= 0 && (size_t)dragHandleKeyframeIdx < path.keyframes.size()) {
                auto& kf = path.keyframes[dragHandleKeyframeIdx];
                float outX, outY, outZ;
                if (topOrSideView == TOP_VIEW) {
                    view_x = 27.0f; view_y = 12.0f;
                    pixelToSourceCoords((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2,
                        view_x, view_y, scale, room_dims_pixels[1], room_dims_pixels[0], true,
                        outX, outY, outZ);
                    float dtx = 3.0f * (outX - kf.x);
                    float dty = 3.0f * (outY - kf.y);
                    if (dragHandleIsIn) { kf.txIn = -dtx; kf.tyIn = -dty; }
                    else                { kf.txOut = dtx; kf.tyOut = dty; }
                } else {
                    view_x = 27.0f; view_y = 240.0f;
                    pixelToSourceCoords((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2,
                        view_x, view_y, scale, room_dims_pixels[1], room_dims_pixels[2], false,
                        outX, outY, outZ);
                    float dty = 3.0f * (outY - kf.y);
                    float dtz = 3.0f * (outZ - kf.z);
                    if (dragHandleIsIn) { kf.tyIn = -dty; kf.tzIn = -dtz; }
                    else                { kf.tyOut = dty; kf.tzOut = dtz; }
                }
                /* Keep the curve smooth (mirror the opposite handle) unless Shift is held */
                if (!e.mods.isShiftDown()) {
                    if (dragHandleIsIn) { kf.txOut = kf.txIn;  kf.tyOut = kf.tyIn;  kf.tzOut = kf.tzIn; }
                    else                { kf.txIn  = kf.txOut; kf.tyIn  = kf.tyOut; kf.tzIn  = kf.tzOut; }
                }
                processor.markPathDirty();
            }
        }
        return;
    }

    /* Dragging a keyframe node: move it to the cursor position and reset
       its tangents to the Catmull-Rom default so the curve stays smooth
       through the node after the move. */
    if (draggingKeyframe && interactionMode == InteractionMode::AddKeyframe) {
        room_dims_m[0] = ambi_roomsim_getRoomDimX(hAmbi);
        room_dims_m[1] = ambi_roomsim_getRoomDimY(hAmbi);
        room_dims_m[2] = ambi_roomsim_getRoomDimZ(hAmbi);
        scale = room_pixels/MAX(MAX(room_dims_m[0], room_dims_m[1]), room_dims_m[2]);
        room_dims_pixels[0] = room_dims_m[0]*scale;
        room_dims_pixels[1] = room_dims_m[1]*scale;
        room_dims_pixels[2] = room_dims_m[2]*scale;

        PathBank& pb = processor.getPathBank();
        {
            const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
            auto& path = dragPathIsReceiver ? pb.getReceiverPath(dragPathObjIdx)
                                            : pb.getSourcePath(dragPathObjIdx);
            if (dragKeyframeIdx >= 0 && (size_t)dragKeyframeIdx < path.keyframes.size()) {
                auto& kf = path.keyframes[dragKeyframeIdx];
                float outX, outY, outZ;
                if (topOrSideView == TOP_VIEW) {
                    view_x = 27.0f; view_y = 12.0f;
                    pixelToSourceCoords((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2,
                        view_x, view_y, scale, room_dims_pixels[1], room_dims_pixels[0], true,
                        outX, outY, outZ);
                    kf.x = outX; kf.y = outY; kf.z = outZ;
                } else {
                    view_x = 27.0f; view_y = 240.0f;
                    pixelToSourceCoords((float)e.getPosition().getX()-2, (float)e.getPosition().getY()-2,
                        view_x, view_y, scale, room_dims_pixels[1], room_dims_pixels[2], false,
                        outX, outY, outZ);
                    kf.y = outY; kf.z = outZ;
                }
                path.recomputeDefaultTangent(dragKeyframeIdx);
                processor.markPathDirty();
            }
        }
        return;
    }

    if(sourceIconIsClicked||receiverIconIsClicked){
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

void pannerView::mouseUp (const juce::MouseEvent& e)
{
    /* Release over the room in AddKeyframe mode: if the press was not on a
       keyframe, handle or source/receiver icon, drop a new keyframe on the
       selected path at the cursor position. */
    if (interactionMode == InteractionMode::AddKeyframe && !draggingKeyframe && !draggingHandle
        && !mouseDownOnIcon && editingObjectIdx >= 0) {
        float room_dims_m[3];
        room_dims_m[0] = ambi_roomsim_getRoomDimX(hAmbi);
        room_dims_m[1] = ambi_roomsim_getRoomDimY(hAmbi);
        room_dims_m[2] = ambi_roomsim_getRoomDimZ(hAmbi);
        float scale = room_pixels/MAX(MAX(room_dims_m[0], room_dims_m[1]), room_dims_m[2]);
        float room_dims_pixels[3] = { room_dims_m[0]*scale, room_dims_m[1]*scale, room_dims_m[2]*scale };

        float view_x = 27.0f, view_y;
        for (int attempt = 0; attempt < 2; ++attempt) {
            bool isTop = (attempt == 0);
            view_y = isTop ? 12.0f : 240.0f;
            float view_w = room_dims_pixels[1];
            float view_h = isTop ? room_dims_pixels[0] : room_dims_pixels[2];
            juce::Rectangle<float> bounds(view_x, view_y, view_w, view_h);
            if (bounds.contains(e.getPosition().toFloat())) {
                float outX, outY, outZ;
                pixelToSourceCoords((float)e.getPosition().getX(), (float)e.getPosition().getY(),
                    view_x, view_y, scale, view_w, view_h, isTop, outX, outY, outZ);
                PathBank& pb = processor.getPathBank();
                juce::SpinLock::ScopedLockType sl(processor.getPathLock());

                PathData& path = editingIsReceiver ? pb.getReceiverPath(editingObjectIdx)
                                                   : pb.getSourcePath(editingObjectIdx);
                if (!path.enabled)
                    return;                /* disabled path is locked: block keyframe creation */
                if (path.keyframes.empty() && path.startTime == 0.0 && path.endTime == 10.0) {
                    /* Default a fresh path to span the whole track; fall
                       back to 10 s if no transport position is known yet.
                       Only applied while the path still has its untouched
                       default window, so a start/end the user already set
                       via the Path Controls sliders is preserved. */
                    double trackEnd = processor.getTrackEndTime();
                    path.endTime = (trackEnd > 0.0) ? trackEnd : 10.0;
                }
                path.keyframes.push_back({0.0, outX, outY, outZ});
                double dur = path.endTime - path.startTime;
                PathData::redistributeTimes(path, dur);
                path.recomputeDefaultTangent((int)path.keyframes.size() - 1);
                processor.markPathDirty();
                return;
            }
        }
    }

    /* End any active drag and reset the per-press flags. */
    if (draggingHandle) {
        draggingHandle = false;
        dragHandleKeyframeIdx = -1;
        return;
    }

    if (draggingKeyframe) {
        draggingKeyframe = false;
        return;
    }

    sourceIconIsClicked = false;
    receiverIconIsClicked = false;
    mouseDownOnIcon = false;
}

void pannerView::refreshPanView()
{
    repaint();
}
