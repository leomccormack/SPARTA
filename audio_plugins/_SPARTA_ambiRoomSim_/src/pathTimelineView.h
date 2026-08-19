#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "pathAutomation.h"

class pathTimelineView  : public Component
{
public:
    pathTimelineView(PluginProcessor& p);
    ~pathTimelineView() override;

    void setScrubTime(double t);

    void paint(juce::Graphics& g) override;
    void resized() override;
    void mouseDown(const juce::MouseEvent& e) override;
    void mouseDrag(const juce::MouseEvent& e) override;
    void mouseUp(const juce::MouseEvent& e) override;

private:
    PluginProcessor& processor;
    void* hAmbi;
    double scrubTime = 0.0;
    bool isDraggingKeyframe = false;
    int dragObjectIdx = -1;
    bool dragIsReceiver = false;
    int dragKeyframeIdx = -1;

    struct RowInfo {
        juce::String label;
        int objIdx;
        bool isReceiver;
    };
    juce::Array<RowInfo> rows;
    void rebuildRows();

    juce::Rectangle<float> getRowBounds(int rowIdx) const;
    int getRowForY(float y) const;
    float getRowsMaxY() const;
    double getTimelineMaxTime() const;
    float timeToX(double t, double maxTime) const;
    double xToTime(float x, double maxTime) const;
    void paintWaveformStrip(juce::Graphics& g, double maxTime, float rowsMaxY);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(pathTimelineView)
};
