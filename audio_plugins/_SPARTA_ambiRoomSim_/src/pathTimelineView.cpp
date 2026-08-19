#include "pathTimelineView.h"

static constexpr float rowHeight = 20.0f;
static constexpr float rulerHeight = 24.0f;
static constexpr float labelWidth = 44.0f;
static constexpr float keyframeSize = 7.0f;
static constexpr float stripHeight = 46.0f;

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

/* The pause model is "baked": a keyframe's timeSeconds already includes the
   stopTime of every earlier keyframe (editing a stop time shifts all later
   keyframes and the path endTime). So the timeline simply uses the stored
   timeSeconds / endTime directly — no extra adjustment is applied here. */

void pathTimelineView::rebuildRows()
{
    rows.clear();
    PathBank& pb = processor.getPathBank();
    int nSrc = ambi_roomsim_getNumSources(hAmbi);
    int nRec = ambi_roomsim_getNumReceivers(hAmbi);
    for (int i = 0; i < nSrc; ++i) {
        auto& path = pb.getSourcePath(i);
        if (!path.keyframes.empty())
            rows.add({ "S" + juce::String(i + 1), i, false });
    }
    for (int i = 0; i < nRec; ++i) {
        auto& path = pb.getReceiverPath(i);
        if (!path.keyframes.empty())
            rows.add({ "R" + juce::String(i + 1), i, true });
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
    if (y < rulerHeight || y >= getRowsMaxY()) return -1;
    int idx = (int)((y - rulerHeight) / rowHeight);
    return (idx >= 0 && idx < rows.size()) ? idx : -1;
}

float pathTimelineView::getRowsMaxY() const
{
    return (float)getHeight() - stripHeight;
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

/* Shared time axis for the whole timeline: the furthest path end, extended
   to cover a loaded reference track, floored at 10 s. Used by drawing,
   scrubbing and keyframe dragging so they all agree. */
double pathTimelineView::getTimelineMaxTime() const
{
    double maxTime = 0.0;
    PathBank& pb = processor.getPathBank();
    for (auto& row : rows) {
        auto& path = row.isReceiver
                         ? pb.getReceiverPath(row.objIdx)
                         : pb.getSourcePath(row.objIdx);
        /* endTime already includes all pauses (they are baked in). */
        double end = path.endTime;
        if (end > maxTime) maxTime = end;
    }
    if (processor.hasTrackWaveform()) {
        double dur = processor.getTrackWaveform().durationSeconds;
        if (dur > maxTime) maxTime = dur;
    }
    if (maxTime <= 0.0) maxTime = 10.0;
    return maxTime;
}

void pathTimelineView::paint(juce::Graphics& g)
{
    rebuildRows();

    auto area = getLocalBounds().toFloat();
    g.fillAll(juce::Colour(0xff1a2e3a));

    PathBank& pb = processor.getPathBank();
    double maxTime = getTimelineMaxTime();

    double step = maxTime <= 5.0 ? 1.0 : (maxTime <= 20.0 ? 2.0 : 5.0);
    float timeWidth = area.getWidth() - labelWidth;

    g.setColour(juce::Colours::white);
    g.setFont(10.0f);

    /* Start the title at the second gridline so it clears the "0.0" tick. */
    g.drawText("Path Timeline", timeToX(step, maxTime), 0, timeWidth, rulerHeight,
               juce::Justification::centredLeft);

    g.setColour(juce::Colour(0x55ffffff));
    g.drawHorizontalLine((int)rulerHeight, area.getX(), area.getRight());

    for (double t = 0.0; t <= maxTime; t += step) {
        float x = timeToX(t, maxTime);
        g.setOpacity(0.3f);
        g.drawVerticalLine((int)x, rulerHeight, area.getBottom());
        g.setOpacity(0.7f);
        g.drawText(juce::String(t, 1), x - 8, 0, 30, rulerHeight,
                   juce::Justification::centredLeft);
    }

    /* Keyframe rows are clipped to the top region so many-row banks never
       spill over the waveform strip. */
    float rowsMaxY = getRowsMaxY();
    g.saveState();
    g.reduceClipRegion(area.getX(), rulerHeight, area.getWidth(),
                       jmax(0.0f, rowsMaxY - rulerHeight));

    for (int r = 0; r < rows.size(); ++r) {
        auto row = rows[r];
        auto& path = row.isReceiver
                         ? pb.getReceiverPath(row.objIdx)
                         : pb.getSourcePath(row.objIdx);
        juce::Colour col = getPathColour(row.isReceiver, row.objIdx);
        const float colAlpha = path.enabled ? 1.0f : 0.30f;

        g.setColour(col.withAlpha(colAlpha));
        g.setFont(9.0f);
        g.drawText(row.label, 0, rulerHeight + r * rowHeight,
                   labelWidth - 2, rowHeight, juce::Justification::centredRight);

        g.setColour(juce::Colour(0x33ffffff));
        g.drawHorizontalLine((int)(rulerHeight + (r + 1) * rowHeight),
                             area.getX(), area.getRight());

        /* Draw a thin bar from startTime to the effective end. */
        float sx = timeToX(path.startTime, maxTime);
        float ex = timeToX(path.endTime, maxTime);
        float ky = rulerHeight + r * rowHeight + rowHeight / 2.0f;
        g.setColour(col.withAlpha(0.2f * colAlpha));
        g.fillRect(sx, ky - 2.0f, ex - sx, 4.0f);

        for (size_t k = 0; k < path.keyframes.size(); ++k) {
            /* Keyframes sit at their effective time, i.e. after all earlier
               pauses have been added. */
            float kx = timeToX(path.startTime + path.keyframes[k].timeSeconds, maxTime);

            Path diamond;
            diamond.startNewSubPath(kx, ky - keyframeSize / 2.0f);
            diamond.lineTo(kx + keyframeSize / 2.0f, ky);
            diamond.lineTo(kx, ky + keyframeSize / 2.0f);
            diamond.lineTo(kx - keyframeSize / 2.0f, ky);
            diamond.closeSubPath();

            g.setColour(col.withAlpha(0.9f * colAlpha));
            g.fillPath(diamond);
            g.setColour(col.brighter(0.4f).withAlpha(colAlpha));
            g.strokePath(diamond, juce::PathStrokeType(1.0f));
        }
    }

    g.restoreState();

    paintWaveformStrip(g, maxTime, rowsMaxY);

    float px = timeToX(scrubTime, maxTime);
    g.setColour(juce::Colours::red);
    g.drawVerticalLine((int)px, rulerHeight, area.getBottom());
    g.setColour(juce::Colours::red.withAlpha(0.3f));
    g.drawVerticalLine((int)px - 1, rulerHeight, area.getBottom());
}

void pathTimelineView::paintWaveformStrip(juce::Graphics& g, double maxTime, float rowsMaxY)
{
    if (maxTime <= 0.0 || getHeight() - rowsMaxY < 8.0f) return;

    auto area = getLocalBounds().toFloat();
    float stripY = rowsMaxY;
    float stripH = area.getBottom() - stripY;
    float centreY = stripY + stripH / 2.0f;

    /* Distinguish the strip from the keyframe rows. */
    g.setColour(juce::Colour(0xff162632));
    g.fillRect(labelWidth, stripY, area.getWidth() - labelWidth, stripH);
    g.setColour(juce::Colour(0x33ffffff));
    g.drawHorizontalLine((int)stripY, area.getX(), area.getRight());

    int xStart = (int)labelWidth;
    int xEnd = (int)area.getRight();
    const float ampScale = (stripH / 2.0f - 3.0f) * 1.0f;

    if (processor.hasTrackWaveform()) {
        /* Full reference track, drawn statically from t = 0. */
        TrackWaveform track = processor.getTrackWaveformSnapshot();
        const int numBuckets = (int)track.minPeaks.size();
        if (numBuckets > 0) {
            const int64 samplesPerBucket = jmax((int64)1, (int64)(track.durationSeconds * track.sampleRate / numBuckets));
            g.setColour(juce::Colour(0xcc6fd3d3));
            for (int x = xStart; x < xEnd; ++x) {
                double t0 = xToTime((float)x, maxTime);
                double t1 = xToTime((float)(x + 1), maxTime);
                if (t0 >= track.durationSeconds) continue;
                int b0 = (int)((t0 * track.sampleRate) / samplesPerBucket);
                int b1 = (int)((t1 * track.sampleRate) / samplesPerBucket);
                if (b0 >= numBuckets) continue;
                if (b1 >= numBuckets) b1 = numBuckets - 1;
                if (b1 < b0) b1 = b0;
                float mn = 1.0f, mx = -1.0f;
                for (int b = b0; b <= b1; ++b) {
                    mn = jmin(mn, track.minPeaks[(size_t)b]);
                    mx = jmax(mx, track.maxPeaks[(size_t)b]);
                }
                if (mx <= mn) continue;
                g.drawVerticalLine(x,
                    jlimit(stripY + 2.0f, area.getBottom() - 2.0f, centreY - mx * ampScale),
                    jlimit(stripY + 2.0f, area.getBottom() - 2.0f, centreY - mn * ampScale));
            }
        }
    }
    else if (processor.isTrackLoading()) {
        /* A decode is in flight; nothing to draw yet. */
        g.setColour(juce::Colour(0x88ffffff));
        g.setFont(11.0f);
        g.drawText("Loading track...", labelWidth, (int)stripY,
                   (int)(area.getWidth() - labelWidth), (int)stripH,
                   juce::Justification::centred);
    }
    else {
        /* Live capture. The newest sample sits exactly under the playhead
           (scrubTime), so the recorded waveform grows out of the playhead
           position as playback advances: capture time c for a pixel at
           timeline time t is c = headTime - (scrubTime - t). */
        double headTime = processor.getCurrentHostTime();
        const WaveformCapture& wf = processor.getWaveformCapture();
        const int numBuckets = wf.getNumBuckets();
        const double bucketSpan = wf.getBucketSpanSeconds();
        const int writeBucket = wf.getWriteBucket();

        g.setColour(juce::Colour(0xcc6fd3d3));
        for (int x = xStart; x < xEnd; ++x) {
            double t0 = xToTime((float)x, maxTime);
            double t1 = xToTime((float)(x + 1), maxTime);

            double c0 = headTime - (scrubTime - t0);
            double c1 = headTime - (scrubTime - t1);
            if (c1 < 0.0 || c0 > headTime) continue;  /* before capture start / ahead of playhead */

            int offLo = (int)floor((headTime - c1) / bucketSpan);
            int offHi = (int)floor((headTime - c0) / bucketSpan);
            if (offLo < 0) offLo = 0;
            if (offHi >= numBuckets) offHi = numBuckets - 1;
            if (offHi < offLo) continue;

            float mn = 1.0f, mx = -1.0f;
            for (int o = offLo; o <= offHi; ++o) {
                int idx = writeBucket - 1 - o;
                idx %= numBuckets;
                if (idx < 0) idx += numBuckets;
                mn = jmin(mn, wf.getBucketMin(idx));
                mx = jmax(mx, wf.getBucketMax(idx));
            }
            if (mx <= mn) continue;

            g.drawVerticalLine(x,
                jlimit(stripY + 2.0f, area.getBottom() - 2.0f, centreY - mx * ampScale),
                jlimit(stripY + 2.0f, area.getBottom() - 2.0f, centreY - mn * ampScale));
        }
    }

    /* Faint centre line so the strip reads as a waveform. */
    g.setColour(juce::Colour(0x22ffffff));
    g.drawHorizontalLine((int)centreY, labelWidth, area.getRight());
}

void pathTimelineView::resized() {}

void pathTimelineView::mouseDown(const juce::MouseEvent& e)
{
    auto area = getLocalBounds().toFloat();
    rebuildRows();

    PathBank& pb = processor.getPathBank();
    double maxTime = getTimelineMaxTime();

    float rowsMaxY = getRowsMaxY();
    for (int r = 0; r < rows.size(); ++r) {
        auto row = rows[r];
        auto& path = row.isReceiver
                         ? pb.getReceiverPath(row.objIdx)
                         : pb.getSourcePath(row.objIdx);
        if (!path.enabled) continue;
        float ky = rulerHeight + r * rowHeight + rowHeight / 2.0f;
        if (ky + keyframeSize / 2.0f >= rowsMaxY) continue;
        for (size_t k = 0; k < path.keyframes.size(); ++k) {
            float kx = timeToX(path.startTime + path.keyframes[k].timeSeconds, maxTime);
            juce::Rectangle<float> hit(kx - 5, ky - 5, 10, 10);
            if (hit.contains(e.getPosition().toFloat())) {
                isDraggingKeyframe = true;
                dragObjectIdx = row.objIdx;
                dragIsReceiver = row.isReceiver;
                dragKeyframeIdx = (int)k;
                return;
            }
        }
    }

    /* Clicking a row or the waveform strip scrubs; the ruler does not. */
    float y = (float)e.getPosition().getY();
    if (y >= rulerHeight) {
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
                             ? pb.getReceiverPath(dragObjectIdx)
                             : pb.getSourcePath(dragObjectIdx);

        double maxTime = getTimelineMaxTime();

        /* The pointer position is the keyframe's stored time directly:
           timeSeconds already includes all earlier pauses (baked-in model),
           and the timeline draws nodes at their stored times. */
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
