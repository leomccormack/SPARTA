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

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

/* The two 2D projections of the room shown side by side: top-down (x,y) and
   side (y,z). */
#define TOP_VIEW ( 0 )
#define SIDE_VIEW ( 1 )
#define NUM_VIEW_POINTS ( 2 )

/* Room-view interaction modes. Move drags the source/receiver icons to
   reposition them; AddKeyframe edits the selected object's path by clicking
   to add keyframes, dragging keyframe nodes and dragging spline handles. */
enum class InteractionMode { Move, AddKeyframe };

class pannerView  : public Component
{
public:
    pannerView (PluginProcessor& p, int _width, int _height);
    ~pannerView() override;

    void refreshPanView();
    bool getSourceIconIsClicked(){
        return sourceIconIsClicked;
    }
    bool getReceiverIconIsClicked(){
        return receiverIconIsClicked;
    }

    void setInteractionMode(InteractionMode mode) { interactionMode = mode; }
    void setScrubTime(double t) { scrubTime = t; }
    InteractionMode getInteractionMode() const { return interactionMode; }

    /* Selects which object the room view edits. Called on every timer
       tick so the room view stays in sync with the Path Controls panel. */
    void setEditingObject(int index, bool isReceiver) {
        editingObjectIdx = index; editingIsReceiver = isReceiver;
    }
    int getEditingObjectIndex() const { return editingObjectIdx; }
    bool getEditingIsReceiver() const { return editingIsReceiver; }

    void paint (juce::Graphics& g) override;
    void resized() override;
    void mouseDown (const juce::MouseEvent& e) override;
    void mouseDrag (const juce::MouseEvent& e) override;
    void mouseUp (const juce::MouseEvent& e) override;

private:
    /* Draws the path curve (via PathData::evaluate) and its keyframe markers
       for one view. Every path is drawn; disabled paths are dimmed so they
       stay visible but clearly inactive. */
    void drawPathOnView(juce::Graphics& g, const PathData& path, int objIdx,
                        float view_x, float view_y,
                        float scale, float room_w, float room_h,
                        bool isTopView, bool isReceiver);
    /* Draws the in/out spline handles of the selected path's keyframes. */
    void drawPathHandlesOnView(juce::Graphics& g, const PathData& path, int objIdx,
                               float view_x, float view_y,
                               float scale, float room_w, float room_h,
                               bool isTopView, bool isReceiver);
    /* Projects one of a keyframe's handle points (P - mIn/3 or P + mOut/3)
       into screen space for the given view. */
    void getHandleScreenPos(const Keyframe& kf, bool isIn, bool isTopView,
                            float view_x, float view_y, float scale,
                            float room_w, float room_h, float& px, float& py) const;
    /* Whether the currently selected path exists and is enabled. Disabled
       paths are locked and block all room-view editing. */
    bool isCurrentPathEnabled() const;
    void pixelToSourceCoords(float px, float py, float view_x, float view_y,
                             float scale, float room_w, float room_h,
                             bool isTopView, float& outX, float& outY, float& outZ) const;

    PluginProcessor& processor;
    void* hAmbi;
    int width;
    int height;
    Rectangle<float> SourceIcons[NUM_VIEW_POINTS][ROOM_SIM_MAX_NUM_SOURCES];
    Rectangle<float> ReceiverIcons[NUM_VIEW_POINTS][ROOM_SIM_MAX_NUM_RECEIVERS];
    bool sourceIconIsClicked;
    bool receiverIconIsClicked;
    int indexOfClickedIcon;
    int topOrSideView;

    /* Keyframe/path editing state */
    InteractionMode interactionMode = InteractionMode::Move;
    double scrubTime = 0.0;
    /* The object currently selected in the Path Controls panel. */
    int editingObjectIdx = -1;
    bool editingIsReceiver = false;
    /* Active drag of a keyframe node (draggingKeyframe). */
    bool draggingKeyframe = false;
    int dragKeyframeIdx = -1;
    int dragPathObjIdx = -1;
    bool dragPathIsReceiver = false;
    float dragStartX, dragStartY;

    /* Active drag of a spline handle (draggingHandle). */
    bool draggingHandle = false;
    int dragHandleKeyframeIdx = -1;
    bool dragHandleIsIn = false;

    /* True when mouseDown landed on a source/receiver icon (not draggable,
       so mouseUp must not create a keyframe there). */
    bool mouseDownOnIcon = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (pannerView)
};
