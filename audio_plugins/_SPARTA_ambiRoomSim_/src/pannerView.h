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

#define TOP_VIEW ( 0 )
#define SIDE_VIEW ( 1 )
#define NUM_VIEW_POINTS ( 2 )

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

    void setEditingObject(int index, bool isReceiver, int pathIdx) {
        editingObjectIdx = index; editingIsReceiver = isReceiver; editingPathIdx = pathIdx;
    }
    int getEditingObjectIndex() const { return editingObjectIdx; }
    bool getEditingIsReceiver() const { return editingIsReceiver; }
    int getEditingPathIndex() const { return editingPathIdx; }

    void paint (juce::Graphics& g) override;
    void resized() override;
    void mouseDown (const juce::MouseEvent& e) override;
    void mouseDrag (const juce::MouseEvent& e) override;
    void mouseUp (const juce::MouseEvent& e) override;

private:
    void drawPathOnView(juce::Graphics& g, const PathData& path, float view_x, float view_y,
                        float scale, float room_w, float room_h,
                        bool isTopView, bool isReceiver);
    void drawPathHandlesOnView(juce::Graphics& g, const PathData& path, float view_x, float view_y,
                               float scale, float room_w, float room_h,
                               bool isTopView, bool isReceiver);
    void getHandleScreenPos(const Keyframe& kf, bool isIn, bool isTopView,
                            float view_x, float view_y, float scale,
                            float room_w, float room_h, float& px, float& py) const;
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
    int editingObjectIdx = -1;
    bool editingIsReceiver = false;
    int editingPathIdx = 0;
    bool draggingKeyframe = false;
    int dragKeyframeIdx = -1;
    int dragPathObjIdx = -1;
    bool dragPathIsReceiver = false;
    int dragPathIdx = 0;
    float dragStartX, dragStartY;

    /* Spline handle editing state */
    bool draggingHandle = false;
    int dragHandleKeyframeIdx = -1;
    bool dragHandleIsIn = false;

    /* True when mouseDown landed on a source/receiver icon (not draggable) */
    bool mouseDownOnIcon = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (pannerView)
};
