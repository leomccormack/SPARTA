#include "pathTimelineView.h"

static constexpr float rowHeight = 20.0f;
static constexpr float rulerHeight = 24.0f;
static constexpr float labelWidth = 44.0f;
static constexpr float keyframeSize = 7.0f;

pathTimelineView::pathTimelineView(PluginProcessor& p)
    : processor(p)
{
    hAmbi = processor.getFXHandle();
}

pathTimelineView::~pathTimelineView() {}

void pathTimelineView::setScrubTime(double t)
{
    scrubTime = t;
    repaint();
}

void pathTimelineView::rebuildRows()
{
    rows.clear();
    PathBank& pb = processor.getPathBank();
    int nSrc = ambi_roomsim_getNumSources(hAmbi);
    int nRec = ambi_roomsim_getNumReceivers(hAmbi);
    for (int i = 0; i < nSrc; ++i) {
        for (int p = 0; p < pb.getNumSourcePaths(i); ++p) {
            auto& path = pb.getSourcePath(i, p);
            if (path.enabled && !path.keyframes.empty())
                rows.add({ "S" + juce::String(i + 1) + ".P" + juce::String(p + 1), i, false, p });
        }
    }
    for (int i = 0; i < nRec; ++i) {
        for (int p = 0; p < pb.getNumReceiverPaths(i); ++p) {
            auto& path = pb.getReceiverPath(i, p);
            if (path.enabled && !path.keyframes.empty())
                rows.add({ "R" + juce::String(i + 1) + ".P" + juce::String(p + 1), i, true, p });
        }
    }
}

juce::Rectangle<float> pathTimelineView::getRowBounds(int rowIdx) const
{
    auto area = getLocalBounds().toFloat();
    float y = rulerHeight + rowIdx * rowHeight;
    return { area.getX() + labelWidth, y, area.getWidth() - labelWidth, rowHeight };
}

int pathTimelineView::getRowForY(float y) const
{
    if (y < rulerHeight) return -1;
    int idx = (int)((y - rulerHeight) / rowHeight);
    return (idx >= 0 && idx < rows.size()) ? idx : -1;
}

float pathTimelineView::timeToX(double t, double maxTime) const
{
    auto area = getLocalBounds().toFloat();
    float w = area.getWidth() - labelWidth;
    if (maxTime <= 0.0) return area.getX() + labelWidth;
    return area.getX() + labelWidth + (float)(t / maxTime) * w;
}

double pathTimelineView::xToTime(float x, double maxTime) const
{
    auto area = getLocalBounds().toFloat();
    float w = area.getWidth() - labelWidth;
    if (w <= 0.0f) return 0.0;
    return ((double)(x - area.getX() - labelWidth) / (double)w) * maxTime;
}

void pathTimelineView::paint(juce::Graphics& g)
{
    rebuildRows();

    auto area = getLocalBounds().toFloat();
    g.fillAll(juce::Colour(0xff1a2e3a));

    double maxTime = 0.0;
    PathBank& pb = processor.getPathBank();
    for (auto& row : rows) {
        auto& path = row.isReceiver
                         ? pb.getReceiverPath(row.objIdx, row.pathIdx)
                         : pb.getSourcePath(row.objIdx, row.pathIdx);
        if (path.endTime > maxTime) maxTime = path.endTime;
    }
    if (maxTime <= 0.0) maxTime = 10.0;

    float timeWidth = area.getWidth() - labelWidth;

    g.setColour(juce::Colours::white);
    g.setFont(10.0f);

    g.drawText("Path Timeline", labelWidth, 0, timeWidth, rulerHeight,
               juce::Justification::centredLeft);

    g.setColour(juce::Colour(0x55ffffff));
    g.drawHorizontalLine((int)rulerHeight, area.getX(), area.getRight());

    double step = maxTime <= 5.0 ? 1.0 : (maxTime <= 20.0 ? 2.0 : 5.0);
    for (double t = 0.0; t <= maxTime; t += step) {
        float x = timeToX(t, maxTime);
        g.setOpacity(0.3f);
        g.drawVerticalLine((int)x, rulerHeight, area.getBottom());
        g.setOpacity(0.7f);
        g.drawText(juce::String(t, 1), x - 8, 0, 30, rulerHeight,
                   juce::Justification::centredLeft);
    }

    for (int r = 0; r < rows.size(); ++r) {
        auto row = rows[r];
        auto& path = row.isReceiver
                         ? pb.getReceiverPath(row.objIdx, row.pathIdx)
                         : pb.getSourcePath(row.objIdx, row.pathIdx);
        juce::Colour col = row.isReceiver ? juce::Colours::magenta : juce::Colours::orange;

        g.setColour(col);
        g.setFont(9.0f);
        g.drawText(row.label, 0, rulerHeight + r * rowHeight,
                   labelWidth - 2, rowHeight, juce::Justification::centredRight);

        g.setColour(juce::Colour(0x33ffffff));
        g.drawHorizontalLine((int)(rulerHeight + (r + 1) * rowHeight),
                             area.getX(), area.getRight());

        /* Draw a thin bar from startTime to endTime */
        float sx = timeToX(path.startTime, maxTime);
        float ex = timeToX(path.endTime, maxTime);
        float ky = rulerHeight + r * rowHeight + rowHeight / 2.0f;
        g.setColour(col.withAlpha(0.2f));
        g.fillRect(sx, ky - 2.0f, ex - sx, 4.0f);

        for (size_t k = 0; k < path.keyframes.size(); ++k) {
            auto& kf = path.keyframes[k];
            float kx = timeToX(path.startTime + kf.timeSeconds, maxTime);

            Path diamond;
            diamond.startNewSubPath(kx, ky - keyframeSize / 2.0f);
            diamond.lineTo(kx + keyframeSize / 2.0f, ky);
            diamond.lineTo(kx, ky + keyframeSize / 2.0f);
            diamond.lineTo(kx - keyframeSize / 2.0f, ky);
            diamond.closeSubPath();

            g.setColour(col.withAlpha(0.9f));
            g.fillPath(diamond);
            g.setColour(col.brighter(0.4f));
            g.strokePath(diamond, juce::PathStrokeType(1.0f));
        }
    }

    float px = timeToX(scrubTime, maxTime);
    g.setColour(juce::Colours::red);
    g.drawVerticalLine((int)px, rulerHeight, area.getBottom());
    g.setColour(juce::Colours::red.withAlpha(0.3f));
    g.drawVerticalLine((int)px - 1, rulerHeight, area.getBottom());
}

void pathTimelineView::resized() {}

void pathTimelineView::mouseDown(const juce::MouseEvent& e)
{
    auto area = getLocalBounds().toFloat();
    rebuildRows();

    double maxTime = 0.0;
    PathBank& pb = processor.getPathBank();
    for (auto& row : rows) {
        auto& path = row.isReceiver
                         ? pb.getReceiverPath(row.objIdx, row.pathIdx)
                         : pb.getSourcePath(row.objIdx, row.pathIdx);
        if (path.endTime > maxTime) maxTime = path.endTime;
    }
    if (maxTime <= 0.0) maxTime = 10.0;

    for (int r = 0; r < rows.size(); ++r) {
        auto row = rows[r];
        auto& path = row.isReceiver
                         ? pb.getReceiverPath(row.objIdx, row.pathIdx)
                         : pb.getSourcePath(row.objIdx, row.pathIdx);
        float ky = rulerHeight + r * rowHeight + rowHeight / 2.0f;
        for (size_t k = 0; k < path.keyframes.size(); ++k) {
            float kx = timeToX(path.startTime + path.keyframes[k].timeSeconds, maxTime);
            juce::Rectangle<float> hit(kx - 5, ky - 5, 10, 10);
            if (hit.contains(e.getPosition().toFloat())) {
                isDraggingKeyframe = true;
                dragObjectIdx = row.objIdx;
                dragIsReceiver = row.isReceiver;
                dragPathIdx = row.pathIdx;
                dragKeyframeIdx = (int)k;
                return;
            }
        }
    }

    int rowIdx = getRowForY((float)e.getPosition().getY());
    if (rowIdx >= 0) {
        double t = xToTime((float)e.getPosition().getX(), maxTime);
        setScrubTime(t);
    }
}

void pathTimelineView::mouseDrag(const juce::MouseEvent& e)
{
    if (!isDraggingKeyframe) return;

    PathBank& pb = processor.getPathBank();
    {
        const juce::SpinLock::ScopedLockType sl(processor.getPathLock());
        PathData& path = dragIsReceiver
                             ? pb.getReceiverPath(dragObjectIdx, dragPathIdx)
                             : pb.getSourcePath(dragObjectIdx, dragPathIdx);

        double maxTime = path.endTime;
        if (maxTime <= 0.0) maxTime = 10.0;

        double newTime = xToTime((float)e.getPosition().getX(), maxTime);
        newTime -= path.startTime;
        if (newTime < 0.0) newTime = 0.0;
        if (dragKeyframeIdx >= 0 && (size_t)dragKeyframeIdx < path.keyframes.size())
            path.keyframes[dragKeyframeIdx].timeSeconds = newTime;

        processor.markPathDirty();
    }
    repaint();
}

void pathTimelineView::mouseUp(const juce::MouseEvent& /*e*/)
{
    isDraggingKeyframe = false;
}
