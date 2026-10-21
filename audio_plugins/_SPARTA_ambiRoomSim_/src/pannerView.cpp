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
/* Slight offset that compensates for the size of the icons, so that the
   centre of an icon (and not its edge) follows the mouse. */
const float iconGrabOffset = 2.0f;
/* Radius (in pixels) around an icon that still counts as a hit. */
const float iconHitSlack = 4.0f;
/* Radius (in pixels) around a keyframe node that still counts as a hit. */
const float keyframeHitSlack = 3.0f;

pannerView::pannerView (PluginProcessor& p, int _width, int _height) : processor(p)
{
    /* The handle has to be set before the size is changed: setting the size
       triggers resized(), which reads the room dimensions from it. */
    hAmbi = processor.getFXHandle();
    topOrSideView = TOP_VIEW; /* default */
    sourceIconIsClicked = false;
    receiverIconIsClicked = false;
    indexOfClickedIcon = -1;

    setSize(_width, _height);
}

pannerView::~pannerView()
{
}

/* ---------------------------------------------------------------------------
   Layout
   --------------------------------------------------------------------------- */

void pannerView::updateLayout()
{
    const float roomX = ambi_roomsim_getRoomDimX(hAmbi);
    const float roomY = ambi_roomsim_getRoomDimY(hAmbi);
    const float roomZ = ambi_roomsim_getRoomDimZ(hAmbi);

    /* Space that is reserved around the two projections for the grid
       labels and the axis names. */
    const float marginL = 30.0f, marginR = 22.0f, marginT = 10.0f, marginB = 24.0f;
    const float gap = 18.0f;   /* vertical gap between the two views */

    const float spaceW = juce::jmax(20.0f, (float)getWidth()  - marginL - marginR);
    const float spaceH = juce::jmax(20.0f, (float)getHeight() - marginT - marginB);
    const float availH = juce::jmax(20.0f, spaceH - gap);

    /* Both projections share the same scale (pixels per metre), so that the
       room keeps its proportions. The width of a view is the room depth
       (y), its height is the room width (x) for the top view and the room
       height (z) for the side view. */
    const float scaleW = spaceW / juce::jmax(0.1f, roomY);
    const float scaleH = availH  / juce::jmax(0.1f, roomX + roomZ);
    roomScale = juce::jmax(0.5f, juce::jmin(scaleW, scaleH));

    const float viewW = roomY * roomScale;
    const float topH  = roomX * roomScale;
    const float sideH = roomZ * roomScale;

    const float x0 = marginL + juce::jmax(0.0f, (spaceW - viewW) * 0.5f);
    const float y0 = marginT + juce::jmax(0.0f, (availH - (topH + sideH)) * 0.5f);

    topViewRect  = { x0,        y0,             viewW, topH  };
    sideViewRect = { x0,        y0 + topH + gap, viewW, sideH };
}

Rectangle<float> pannerView::getViewRect(bool isTopView) const
{
    return isTopView ? topViewRect : sideViewRect;
}

void pannerView::drawRoomGrid (juce::Graphics& g, const Rectangle<float>& rect,
                               float horizMetres, float vertMetres,
                               const juce::String& horizAxis, const juce::String& vertAxis)
{
    if (rect.isEmpty())
        return;

    g.setColour(Colours::lightgrey);
    g.drawRect(rect, 2.0f);

    g.setFont(10.0f);

    /* Horizontal axis (the room depth, y): grid lines every metre, labels
       every other metre, drawn below the room. */
    const int nH = (int)horizMetres;
    for (int i = 0; i <= nH; ++i) {
        float lineX = rect.getRight() - (float)i * rect.getWidth() / horizMetres;
        g.setOpacity(0.25f);
        g.drawLine(lineX, rect.getY(), lineX, rect.getBottom(), 1.0f);
        g.setOpacity(0.75f);
        if ((i % 2) == 0)
            g.drawText(juce::String(i), lineX - 6.0f, rect.getBottom() + 2.0f, 12, 10,
                       juce::Justification::centred, true);
    }

    /* Vertical axis (x for the top view, z for the side view): grid lines
       every metre, labels every other metre, drawn to the right. */
    const int nV = (int)vertMetres;
    for (int i = 0; i <= nV; ++i) {
        float lineY = rect.getBottom() - (float)i * rect.getHeight() / vertMetres;
        g.setOpacity(0.25f);
        g.drawLine(rect.getX(), lineY, rect.getRight(), lineY, 1.0f);
        g.setOpacity(0.75f);
        if ((i % 2) == 0)
            g.drawText(juce::String(i), rect.getRight() + 2.0f, lineY - 5.0f, 12, 10,
                       juce::Justification::centred, true);
    }

    g.setFont(12.0f);
    g.setOpacity(0.9f);
    g.drawText(horizAxis, rect.getCentreX() - 5.0f, rect.getBottom() + 2.0f, 10, 10,
               juce::Justification::centred, true);
    g.drawText(vertAxis, rect.getRight() + 2.0f, rect.getCentreY() - 5.0f, 10, 10,
               juce::Justification::centred, true);
    g.setOpacity(1.0f);
}

void pannerView::pointToRoomCoords (juce::Point<float> p, bool isTopView,
                                    float& outX, float& outY, float& outZ) const
{
    const float room_dims_m[3] = { ambi_roomsim_getRoomDimX(hAmbi),
                                    ambi_roomsim_getRoomDimY(hAmbi),
                                    ambi_roomsim_getRoomDimZ(hAmbi) };
    const Rectangle<float>& rect = getViewRect(isTopView);
    if (roomScale <= 0.0f)
        return;

    outY = (rect.getRight() - p.x) / roomScale;
    if (isTopView) {
        outX = (rect.getBottom() - p.y) / roomScale;
        outZ = room_dims_m[2] / 2.0f;
    } else {
        outZ = (rect.getBottom() - p.y) / roomScale;
    }

    outX = juce::jlimit(0.0f, room_dims_m[0], outX);
    outY = juce::jlimit(0.0f, room_dims_m[1], outY);
    outZ = juce::jlimit(0.0f, room_dims_m[2], outZ);
}

void pannerView::getLivePosition (bool isReceiver, int objIdx,
                                  float& outX, float& outY, float& outZ) const
{
    outX = isReceiver ? ambi_roomsim_getReceiverX(hAmbi, objIdx)
                      : ambi_roomsim_getSourceX(hAmbi, objIdx);
    outY = isReceiver ? ambi_roomsim_getReceiverY(hAmbi, objIdx)
                      : ambi_roomsim_getSourceY(hAmbi, objIdx);
    outZ = isReceiver ? ambi_roomsim_getReceiverZ(hAmbi, objIdx)
                      : ambi_roomsim_getSourceZ(hAmbi, objIdx);
}

void pannerView::getObjectPosition (bool isReceiver, int objIdx,
                                    float& outX, float& outY, float& outZ) const
{
    getLivePosition(isReceiver, objIdx, outX, outY, outZ);

    if (!previewActive)
        return;

    /* While previewing, the object is drawn at the position it will have at
       the previewed time (the path drives it, the DSP still runs on the
       live host time). */
    const PathBank& pb = processor.getPathBank();
    const PathData& path = isReceiver ? pb.getReceiverPath(objIdx)
                                      : pb.getSourcePath(objIdx);
    if (path.enabled && !path.keyframes.empty()) {
        float x = 0.0f, y = 0.0f, z = 0.0f;
        path.evaluate(previewTime, x, y, z);
        outX = x; outY = y; outZ = z;
    }
}

/* ---------------------------------------------------------------------------
   Painting
   --------------------------------------------------------------------------- */

void pannerView::drawObjectIcon (juce::Graphics& g, bool isReceiver, int objIdx,
                                 const Rectangle<float>& rect, bool isTopView)
{
    const juce::Colour col = isReceiver ? juce::Colours::magenta : juce::Colours::orange;

    /* While previewing, the live position is drawn as a hollow marker, so
       that the live and the previewed position are visible at the same
       time. */
    if (previewActive)
    {
        float lx, ly, lz;
        getLivePosition(isReceiver, objIdx, lx, ly, lz);
        float liveX = rect.getRight() - roomScale * ly;
        float liveY = rect.getBottom() - roomScale * (isTopView ? lx : lz);
        g.setColour(col.withAlpha(0.9f));
        g.drawEllipse(liveX - iconRadius, liveY - iconRadius, iconWidth, iconWidth, 1.5f);
    }

    float x, y, z;
    getObjectPosition(isReceiver, objIdx, x, y, z);
    float point_x = rect.getRight() - roomScale * y;
    float point_y = rect.getBottom() - roomScale * (isTopView ? x : z);
    Rectangle<float> icon(point_x - iconRadius, point_y - iconRadius,
                          iconWidth, iconWidth);
    g.setColour(col);
    g.setOpacity(0.7f);
    g.fillEllipse(icon);
    g.setOpacity(0.9f);
    g.drawText(juce::String(objIdx + 1), icon.translated(8.0f, -8.0f),
               juce::Justification::centred);
}

void pannerView::paint (juce::Graphics& g)
{
    updateLayout();

    const float room_dims_m[3] = { ambi_roomsim_getRoomDimX(hAmbi),
                                    ambi_roomsim_getRoomDimY(hAmbi),
                                    ambi_roomsim_getRoomDimZ(hAmbi) };

    /* The path bank is read while the UI thread may be editing it, so the
       lock has to be held for the whole drawing of the paths. */
    const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
    const PathBank& pb = processor.getPathBank();

    /****** TOP VIEW (x,y) *****/
    drawRoomGrid(g, topViewRect, room_dims_m[1], room_dims_m[0], "y", "x");

    for (int src = 0; src < ambi_roomsim_getNumSources(hAmbi); src++)
        drawPathOnView(g, pb.getSourcePath(src), src, topViewRect, true, false);
    for (int rec = 0; rec < ambi_roomsim_getNumReceivers(hAmbi); rec++)
        drawPathOnView(g, pb.getReceiverPath(rec), rec, topViewRect, true, true);

    /* Source icons */
    for (int src = 0; src < ambi_roomsim_getNumSources(hAmbi); src++)
        drawObjectIcon(g, false, src, topViewRect, true);

    /* Receiver icons (drawn on top of the sources) */
    for (int rec = 0; rec < ambi_roomsim_getNumReceivers(hAmbi); rec++)
        drawObjectIcon(g, true, rec, topViewRect, true);

    /****** SIDE VIEW (y,z) *****/
    drawRoomGrid(g, sideViewRect, room_dims_m[1], room_dims_m[2], "y", "z");

    for (int src = 0; src < ambi_roomsim_getNumSources(hAmbi); src++)
        drawPathOnView(g, pb.getSourcePath(src), src, sideViewRect, false, false);
    for (int rec = 0; rec < ambi_roomsim_getNumReceivers(hAmbi); rec++)
        drawPathOnView(g, pb.getReceiverPath(rec), rec, sideViewRect, false, true);

    /* Source icons */
    for (int src = 0; src < ambi_roomsim_getNumSources(hAmbi); src++)
        drawObjectIcon(g, false, src, sideViewRect, false);

    /* Receiver icons (drawn on top of the sources) */
    for (int rec = 0; rec < ambi_roomsim_getNumReceivers(hAmbi); rec++)
        drawObjectIcon(g, true, rec, sideViewRect, false);

    /* Highlight the object that is currently being edited. */
    if (editingObjectIdx >= 0) {
        for (int view = 0; view < 2; ++view) {
            const bool isTop = (view == 0);
            const Rectangle<float>& rect = getViewRect(isTop);
            float x, y, z;
            getObjectPosition(editingIsReceiver, editingObjectIdx, x, y, z);
            float point_x = rect.getRight() - roomScale * y;
            float point_y = rect.getBottom() - roomScale * (isTop ? x : z);
            g.setColour(juce::Colours::white.withAlpha(0.85f));
            g.drawEllipse(point_x - iconRadius - 3.0f, point_y - iconRadius - 3.0f,
                          iconWidth + 6.0f, iconWidth + 6.0f, 1.5f);
        }
    }

    /* Draw the spline handles of the selected (enabled) path */
    if (editingObjectIdx >= 0 && isCurrentPathEnabled()) {
        const PathData* sp = editingIsReceiver ? &pb.getReceiverPath(editingObjectIdx)
                                               : &pb.getSourcePath(editingObjectIdx);
        drawPathHandlesOnView(g, *sp, editingObjectIdx, topViewRect, true, editingIsReceiver);
        drawPathHandlesOnView(g, *sp, editingObjectIdx, sideViewRect, false, editingIsReceiver);
    }
}

void pannerView::drawPathOnView(juce::Graphics& g, const PathData& path,
                                int objIdx,
                                const Rectangle<float>& rect, bool isTopView,
                                bool isReceiver)
{
    if (path.keyframes.size() < 2 || rect.isEmpty())
        return;

    /* Every path is drawn so switching sources/receivers never hides them.
       The path that is being edited is highlighted, the others are dimmed to
       show that they are not the active one. */
    const bool isEdited = (objIdx == editingObjectIdx) && (isReceiver == editingIsReceiver);
    juce::Colour col = getPathColour(isReceiver, objIdx);
    float colAlpha = path.enabled ? (isEdited ? 1.0f : 0.55f) : 0.20f;

    /* Draw the path curve. The keyframe times are relative to the start of
       the path, while evaluate() expects an absolute time, so the path's
       start time has to be added (otherwise the drawn curve does not match
       the motion whenever the path does not start at 0 s). */
    double T0 = path.keyframes.front().timeSeconds;
    double Tn = path.keyframes.back().timeSeconds;
    double span = (Tn > T0) ? Tn - T0 : 1.0;

    float px0 = 0, py0 = 0;
    for (int s = 0; s <= 80; ++s) {
        double rel = T0 + (double)s / 80.0 * span;
        float x, y, z;
        path.evaluate(path.startTime + rel, x, y, z);
        float px = rect.getRight() - roomScale * y;
        float py = rect.getBottom() - roomScale * (isTopView ? x : z);
        if (s > 0) {
            g.setColour(col.withAlpha(0.45f * colAlpha));
            g.drawLine(px0, py0, px, py, 1.0f);
        }
        px0 = px; py0 = py;
    }

    /* Draw keyframe markers */
    const float kfSize = 5.0f;
    for (size_t k = 0; k < path.keyframes.size(); ++k) {
        const auto& kf = path.keyframes[k];
        float kx = rect.getRight() - roomScale * kf.y;
        float ky = rect.getBottom() - roomScale * (isTopView ? kf.x : kf.z);
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
                                    const Rectangle<float>& rect, float& px, float& py) const
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
    px = rect.getRight() - roomScale * hy;
    py = rect.getBottom() - roomScale * (isTopView ? hx : hz);
}

/* Draws a line + small square marker from each keyframe to its in/out
   handles, so the user can grab them to reshape the spline. */
void pannerView::drawPathHandlesOnView(juce::Graphics& g, const PathData& path,
                                       int objIdx,
                                       const Rectangle<float>& rect, bool isTopView,
                                       bool isReceiver)
{
    juce::Colour col = getPathColour(isReceiver, objIdx);
    float px, py, hx, hy;
    for (size_t k = 0; k < path.keyframes.size(); ++k) {
        const auto& kf = path.keyframes[k];
        px = rect.getRight() - roomScale * kf.y;
        py = rect.getBottom() - roomScale * (isTopView ? kf.x : kf.z);
        for (int which = 0; which < 2; ++which) {
            bool isIn = (which == 0);
            getHandleScreenPos(kf, isIn, isTopView, rect, hx, hy);
            g.setColour(col.withAlpha(0.6f));
            g.drawLine(px, py, hx, hy, 1.0f);
            g.setColour(col.brighter(0.8f));
            g.fillRect(hx - 1.5f, hy - 1.5f, 3.0f, 3.0f);
            g.setColour(Colours::white);
            g.drawRect(hx - 1.5f, hy - 1.5f, 3.0f, 3.0f);
        }
    }
}

/* Whether the currently selected path exists and is enabled. Returns false
   when nothing is selected, so unrelated interactions are never blocked;
   Move-mode icon dragging is gated on the path being disabled. */
bool pannerView::isCurrentPathEnabled() const
{
    if (editingObjectIdx < 0) return false;
    const PathBank& pb = processor.getPathBank();
    if (editingIsReceiver) {
        if (editingObjectIdx >= ROOM_SIM_MAX_NUM_RECEIVERS) return false;
        return pb.getReceiverPath(editingObjectIdx).enabled;
    }
    if (editingObjectIdx >= ROOM_SIM_MAX_NUM_SOURCES) return false;
    return pb.getSourcePath(editingObjectIdx).enabled;
}

/* ---------------------------------------------------------------------------
   Mouse interaction
   --------------------------------------------------------------------------- */

int pannerView::hitTestIcon (juce::Point<float> p, bool& isReceiverOut,
                             bool& isTopViewOut) const
{
    const int nSrc = ambi_roomsim_getNumSources(hAmbi);
    const int nRec = ambi_roomsim_getNumReceivers(hAmbi);

    for (int view = 0; view < 2; ++view) {
        const bool isTop = (view == 0);
        const Rectangle<float>& rect = getViewRect(isTop);

        /* Receivers are painted on top of the sources and, within each type,
           the last icon drawn is the topmost. Hit-test front-to-back so the
           visible icon is the one grabbed (overlapping icons previously
           grabbed the hidden source instead of the receiver). */
        for (int rec = nRec - 1; rec >= 0; rec--) {
            float x, y, z;
            getObjectPosition(true, rec, x, y, z);
            float point_x = rect.getRight() - roomScale * y;
            float point_y = rect.getBottom() - roomScale * (isTop ? x : z);
            if (Rectangle<float>(point_x - iconRadius, point_y - iconRadius,
                                 iconWidth, iconWidth)
                    .expanded(iconHitSlack, iconHitSlack).contains(p)) {
                isReceiverOut = true;
                isTopViewOut = isTop;
                return rec;
            }
        }
        for (int src = nSrc - 1; src >= 0; src--) {
            float x, y, z;
            getObjectPosition(false, src, x, y, z);
            float point_x = rect.getRight() - roomScale * y;
            float point_y = rect.getBottom() - roomScale * (isTop ? x : z);
            if (Rectangle<float>(point_x - iconRadius, point_y - iconRadius,
                                 iconWidth, iconWidth)
                    .expanded(iconHitSlack, iconHitSlack).contains(p)) {
                isReceiverOut = false;
                isTopViewOut = isTop;
                return src;
            }
        }
    }
    return -1;
}

void pannerView::resized()
{
    updateLayout();
}

void pannerView::mouseDown (const juce::MouseEvent& e)
{
    updateLayout();

    /* Every press starts from a clean slate: the flags used to be left
       behind by the early returns of mouseUp(), which left an icon stuck in
       the "dragging" state (it then followed the mouse around). */
    sourceIconIsClicked = false;
    receiverIconIsClicked = false;
    mouseDownOnIcon = false;
    draggingKeyframe = false;
    dragKeyframeIdx = -1;
    draggingHandle = false;
    dragHandleKeyframeIdx = -1;

    const juce::Point<float> p = e.getPosition().toFloat();

    if (interactionMode == InteractionMode::Move) {
        /* While the path is enabled only its nodes are edited, so icon
           dragging is blocked; a disabled path leaves icons draggable. */
        if (isCurrentPathEnabled())
            return;

        bool isReceiver = false, isTop = true;
        int idx = hitTestIcon(p, isReceiver, isTop);
        if (idx >= 0) {
            receiverIconIsClicked = isReceiver;
            sourceIconIsClicked = !isReceiver;
            indexOfClickedIcon = idx;
            topOrSideView = isTop ? TOP_VIEW : SIDE_VIEW;
        }
        return;
    }

    /* --- AddKeyframe mode --- */
    const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
    const PathBank& pb = processor.getPathBank();

    /* 1) Spline handles of the selected (enabled) path take first priority,
          so fine control points can be grabbed even when they overlap a
          keyframe marker. */
    if (editingObjectIdx >= 0 && isCurrentPathEnabled()) {
        const PathData* sp = editingIsReceiver ? &pb.getReceiverPath(editingObjectIdx)
                                               : &pb.getSourcePath(editingObjectIdx);
        for (int view = 0; view < 2; ++view) {
            const bool isTop = (view == 0);
            const Rectangle<float>& rect = getViewRect(isTop);
            for (size_t k = 0; k < sp->keyframes.size(); ++k) {
                const auto& kf = sp->keyframes[k];
                for (int which = 0; which < 2; ++which) {
                    bool isIn = (which == 0);
                    float hx, hy;
                    getHandleScreenPos(kf, isIn, isTop, rect, hx, hy);
                    if (std::abs(p.x - hx) < 5.0f + keyframeHitSlack &&
                        std::abs(p.y - hy) < 5.0f + keyframeHitSlack) {
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

    /* 2) Keyframe nodes. Only nodes of enabled paths are grabbable;
          disabled paths are locked. Receiver paths are painted over source
          paths, so their nodes are hit-tested first (front-to-back). */
    for (int view = 0; view < 2; ++view) {
        const bool isTop = (view == 0);
        const Rectangle<float>& rect = getViewRect(isTop);
        for (int rec = ambi_roomsim_getNumReceivers(hAmbi) - 1; rec >= 0; --rec) {
            const PathData& path = pb.getReceiverPath(rec);
            if (!path.enabled) continue;
            for (size_t k = 0; k < path.keyframes.size(); ++k) {
                const auto& kf = path.keyframes[k];
                float kx = rect.getRight() - roomScale * kf.y;
                float ky = rect.getBottom() - roomScale * (isTop ? kf.x : kf.z);
                if (std::abs(p.x - kx) < 5.0f + keyframeHitSlack &&
                    std::abs(p.y - ky) < 5.0f + keyframeHitSlack) {
                    draggingKeyframe = true;
                    dragKeyframeIdx = (int)k;
                    dragPathObjIdx = rec;
                    dragPathIsReceiver = true;
                    topOrSideView = isTop ? TOP_VIEW : SIDE_VIEW;
                    return;
                }
            }
        }
        for (int src = ambi_roomsim_getNumSources(hAmbi) - 1; src >= 0; --src) {
            const PathData& path = pb.getSourcePath(src);
            if (!path.enabled) continue;
            for (size_t k = 0; k < path.keyframes.size(); ++k) {
                const auto& kf = path.keyframes[k];
                float kx = rect.getRight() - roomScale * kf.y;
                float ky = rect.getBottom() - roomScale * (isTop ? kf.x : kf.z);
                if (std::abs(p.x - kx) < 5.0f + keyframeHitSlack &&
                    std::abs(p.y - ky) < 5.0f + keyframeHitSlack) {
                    draggingKeyframe = true;
                    dragKeyframeIdx = (int)k;
                    dragPathObjIdx = src;
                    dragPathIsReceiver = false;
                    topOrSideView = isTop ? TOP_VIEW : SIDE_VIEW;
                    return;
                }
            }
        }
    }

    /* 3) Source/receiver icons. While the selected path is enabled the room
          is in path-editing mode and only its nodes are editable, so
          pressing an icon is just remembered (mouseUp must not create a
          keyframe under it). With the path disabled (or nothing selected)
          the icons become draggable again, exactly as in Move mode. */
    const bool iconsDraggable = !(editingObjectIdx >= 0 && isCurrentPathEnabled());
    bool isReceiver = false, isTop = true;
    int idx = hitTestIcon(p, isReceiver, isTop);
    if (idx >= 0) {
        if (!iconsDraggable) {
            mouseDownOnIcon = true;
            return;
        }
        receiverIconIsClicked = isReceiver;
        sourceIconIsClicked = !isReceiver;
        indexOfClickedIcon = idx;
        topOrSideView = isTop ? TOP_VIEW : SIDE_VIEW;
    }
}

void pannerView::mouseDrag (const juce::MouseEvent& e)
{
    updateLayout();

    /* Dragging a spline handle: convert the cursor position to room
       coordinates and set the tangent of the grabbed keyframe. The handle is
       at P + m/3, so the tangent is m = 3 * (cursor - P); the incoming
       handle mirrors this sign. Only the two axes visible in the current
       view are updated (x/y in the top view, y/z in the side view). */
    if (draggingHandle && interactionMode == InteractionMode::AddKeyframe) {
        PathBank& pb = processor.getPathBank();
        bool edited = false;
        {
            const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
            if (editingObjectIdx >= 0) {
                auto& path = editingIsReceiver ? pb.getReceiverPath(editingObjectIdx)
                                               : pb.getSourcePath(editingObjectIdx);
                if (dragHandleKeyframeIdx >= 0 &&
                    (size_t)dragHandleKeyframeIdx < path.keyframes.size()) {
                    auto& kf = path.keyframes[dragHandleKeyframeIdx];
                    float outX = kf.x, outY = kf.y, outZ = kf.z;
                    pointToRoomCoords(e.getPosition().toFloat() -
                                       juce::Point<float>(iconGrabOffset, iconGrabOffset),
                                       topOrSideView == TOP_VIEW, outX, outY, outZ);

                    if (topOrSideView == TOP_VIEW) {
                        float dtx = 3.0f * (outX - kf.x);
                        float dty = 3.0f * (outY - kf.y);
                        if (dragHandleIsIn) { kf.txIn = -dtx; kf.tyIn = -dty; }
                        else                { kf.txOut = dtx; kf.tyOut = dty; }
                    } else {
                        float dty = 3.0f * (outY - kf.y);
                        float dtz = 3.0f * (outZ - kf.z);
                        if (dragHandleIsIn) { kf.tyIn = -dty; kf.tzIn = -dtz; }
                        else                { kf.tyOut = dty; kf.tzOut = dtz; }
                    }
                    /* Keep the curve smooth (mirror the opposite handle)
                       unless Shift is held */
                    if (!e.mods.isShiftDown()) {
                        if (dragHandleIsIn) { kf.txOut = kf.txIn;  kf.tyOut = kf.tyIn;  kf.tzOut = kf.tzIn; }
                        else                { kf.txIn  = kf.txOut; kf.tyIn  = kf.tyOut; kf.tzIn  = kf.tzOut; }
                    }
                    edited = true;
                }
            }
        }
        if (edited) {
            /* The host is notified once, when the gesture ends (see
               mouseUp), so that a drag does not spam the host. */
            processor.markPathDirty(false);
            repaint();
        }
        return;
    }

    /* Dragging a keyframe node: move it to the cursor position and reset
       its tangents to the Catmull-Rom default so the curve stays smooth
       through the node after the move. */
    if (draggingKeyframe && interactionMode == InteractionMode::AddKeyframe) {
        PathBank& pb = processor.getPathBank();
        bool edited = false;
        {
            const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
            if (dragPathObjIdx >= 0) {
                auto& path = dragPathIsReceiver ? pb.getReceiverPath(dragPathObjIdx)
                                                : pb.getSourcePath(dragPathObjIdx);
                if (dragKeyframeIdx >= 0 && (size_t)dragKeyframeIdx < path.keyframes.size()) {
                    auto& kf = path.keyframes[dragKeyframeIdx];
                    float outX = kf.x, outY = kf.y, outZ = kf.z;
                    pointToRoomCoords(e.getPosition().toFloat() -
                                       juce::Point<float>(iconGrabOffset, iconGrabOffset),
                                       topOrSideView == TOP_VIEW, outX, outY, outZ);

                    if (topOrSideView == TOP_VIEW) {
                        kf.x = outX; kf.y = outY; kf.z = outZ;
                    } else {
                        kf.y = outY; kf.z = outZ;
                    }
                    path.recomputeDefaultTangent(dragKeyframeIdx);
                    edited = true;
                }
            }
        }
        if (edited) {
            processor.markPathDirty(false);
            repaint();
        }
        return;
    }

    /* Dragging a source/receiver icon. */
    if (!sourceIconIsClicked && !receiverIconIsClicked)
        return;

    float outX = 0.0f, outY = 0.0f, outZ = 0.0f;
    pointToRoomCoords(e.getPosition().toFloat() -
                       juce::Point<float>(iconGrabOffset, iconGrabOffset),
                       topOrSideView == TOP_VIEW, outX, outY, outZ);

    /* The position is limited to the room dimensions: the image source
       method is only defined inside the room. */
    if (sourceIconIsClicked) {
        const juce::String idx = juce::String(indexOfClickedIcon);
        processor.setParameterValue("sourceY" + idx, outY);
        if (topOrSideView == TOP_VIEW)
            processor.setParameterValue("sourceX" + idx, outX);
        else
            processor.setParameterValue("sourceZ" + idx, outZ);
    }
    else if (receiverIconIsClicked) {
        const juce::String idx = juce::String(indexOfClickedIcon);
        processor.setParameterValue("receiverY" + idx, outY);
        if (topOrSideView == TOP_VIEW)
            processor.setParameterValue("receiverX" + idx, outX);
        else
            processor.setParameterValue("receiverZ" + idx, outZ);
    }
    repaint();
}

void pannerView::mouseUp (const juce::MouseEvent& e)
{
    updateLayout();

    /* Release over the room in AddKeyframe mode: if the press was not on a
       keyframe, handle or source/receiver icon, drop a new keyframe on the
       selected path at the cursor position. */
    bool addedKeyframe = false;
    if (interactionMode == InteractionMode::AddKeyframe && !draggingKeyframe && !draggingHandle
        && !mouseDownOnIcon && editingObjectIdx >= 0) {
        const juce::Point<float> p = e.getPosition().toFloat();
        for (int view = 0; view < 2; ++view) {
            const bool isTop = (view == 0);
            const Rectangle<float>& rect = getViewRect(isTop);
            if (!rect.contains(p))
                continue;

            float outX = 0.0f, outY = 0.0f, outZ = 0.0f;
            pointToRoomCoords(p, isTop, outX, outY, outZ);

            PathBank& pb = processor.getPathBank();
            {
                const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
                PathData& path = editingIsReceiver ? pb.getReceiverPath(editingObjectIdx)
                                                   : pb.getSourcePath(editingObjectIdx);
                if (!path.enabled)
                    break;               /* disabled path is locked */

                /* The number of keyframes per path is limited, so that the
                   copy of the path bank that the audio thread makes never
                   has to allocate memory. */
                if ((int)path.keyframes.size() >= MAX_KEYFRAMES_PER_PATH)
                    break;

                if (path.keyframes.empty() && path.startTime == 0.0 && path.endTime == 10.0) {
                    /* Default a fresh path to span the whole track; fall back
                       to 10 s if no transport position is known yet. Only
                       applied while the path still has its untouched default
                       window, so a start/end the user already set via the
                       Path Controls sliders is preserved. */
                    double trackEnd = processor.getTrackEndTime();
                    path.endTime = (trackEnd > 0.0) ? trackEnd : 10.0;
                }

                /* The new keyframe is inserted at the current (previewed)
                   time and the existing keyframes keep their timing:
                   redistributing them evenly would move every node of the
                   path whenever a single keyframe is added. */
                const double dur = juce::jmax(0.0, path.endTime - path.startTime);
                const double newTime = path.keyframes.empty() ? 0.0
                    : juce::jlimit(0.0, dur,
                                   (previewActive ? previewTime : scrubTime) - path.startTime);

                Keyframe kf;
                kf.timeSeconds = newTime;
                kf.x = outX; kf.y = outY; kf.z = outZ;
                /* Insert it in time order. */
                auto it = std::find_if(path.keyframes.begin(), path.keyframes.end(),
                                       [&newTime] (const Keyframe& k) {
                                           return k.timeSeconds > newTime;
                                       });
                const int newIdx = (int)std::distance(path.keyframes.begin(), it);
                path.keyframes.insert(it, kf);
                /* Only the new node gets the default tangents: the handles of
                   the other nodes may have been shaped by hand. */
                path.recomputeDefaultTangent(newIdx);
                addedKeyframe = true;
            }
            break;
        }
    }
    if (addedKeyframe)
        processor.markPathDirty();

    /* End any active drag and reset the per-press flags. */
    if (draggingHandle) {
        draggingHandle = false;
        dragHandleKeyframeIdx = -1;
        processor.markPathDirty();
    }
    else if (draggingKeyframe) {
        draggingKeyframe = false;
        processor.markPathDirty();
    }
    else if (sourceIconIsClicked || receiverIconIsClicked) {
        processor.markPathDirty();
    }

    sourceIconIsClicked = false;
    receiverIconIsClicked = false;
    mouseDownOnIcon = false;
    draggingKeyframe = false;
    draggingHandle = false;
    dragKeyframeIdx = -1;
    dragHandleKeyframeIdx = -1;
}

void pannerView::refreshPanView()
{
    repaint();
}
