
#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include <assert.h>

#define TOP_VIEW ( 0 )
#define SIDE_VIEW ( 1 )
#define NUM_VIEW_POINTS ( 2 )

class sceneView  : public Component
{
public:
    //==============================================================================
    sceneView (PluginProcessor* ownerFilter, int _width, int _height);
    ~sceneView() override;

    void computeRoomDims();

    void refreshSceneView();
    bool getTargetIconIsClicked(){
        return targetIconIsClicked;
    }

    void setViewMode(int newMode){
        assert(newMode == TOP_VIEW || newMode == SIDE_VIEW);
        topOrSideView = newMode;
    }
    int getViewMode(){
        return topOrSideView;
    }
    void setDrawDoAs(bool newState){
        drawDoAs = newState;
    }
    void setDrawIntersections(bool newState){
        drawIntersections = newState;
    }
    void setDrawTargets(bool newState){
        drawTargets = newState;
    }

    void paint (juce::Graphics& g) override;
    void resized() override;
    void mouseDown (const juce::MouseEvent& e) override;
    void mouseDrag (const juce::MouseEvent& e) override;
    void mouseUp (const juce::MouseEvent& e) override;



private:
    PluginProcessor* hVst;
    void* hTVCnv; 
    int width;
    int height;
    bool targetIconIsClicked;

    int topOrSideView;

    bool drawDoAs;
    bool drawIntersections;
    bool drawTargets;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (sceneView)
};
