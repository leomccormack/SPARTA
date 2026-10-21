#pragma once

#include <JuceHeader.h>
#include <atomic>
#include <limits>
#include <vector>

/* Ring buffer of peak (min/max) pairs used to draw the waveform strip below
   the path timeline. The audio thread mono-mixes the input and folds each
   sample into a fixed number of time buckets; each bucket keeps the min and
   max of every sample that fell into it. Only peaks are stored, so memory is
   bounded and painting the strip never touches full-rate audio.

   The window is fixed (windowSeconds) and written as a ring, so the strip
   shows the most recent N seconds regardless of the timeline zoom. */
class WaveformCapture
{
public:
    static constexpr int numBuckets = 4096;
    static constexpr double windowSeconds = 600.0;

    WaveformCapture()
    {
        minPeaks.assign(numBuckets, 0.0f);
        maxPeaks.assign(numBuckets, 0.0f);
    }

    /* Re-derive per-bucket sample counts for the given sample rate. */
    void prepare(double sampleRate)
    {
        this->sampleRate = sampleRate > 0.0 ? sampleRate : 48000.0;
        samplesPerBucket = (int)(this->sampleRate * windowSeconds / (double)numBuckets);
        if (samplesPerBucket < 1) samplesPerBucket = 1;
        reset();
    }

    /* Clear the ring and accumulators. */
    void reset()
    {
        std::fill(minPeaks.begin(), minPeaks.end(), 0.0f);
        std::fill(maxPeaks.begin(), maxPeaks.end(), 0.0f);
        samplesIntoBucket = 0;
        writeBucket = 0;
        curMin = std::numeric_limits<float>::max();
        curMax = std::numeric_limits<float>::lowest();
        active = true;
    }

    /* Fold `n` mono samples into the peak ring. Call from the audio thread. */
    void addSamples(const float* mono, int n)
    {
        if (!active || mono == nullptr || n <= 0) return;
        for (int i = 0; i < n; ++i) {
            float s = mono[i];
            if (s < curMin) curMin = s;
            if (s > curMax) curMax = s;
            ++samplesIntoBucket;
            if (samplesIntoBucket >= samplesPerBucket) {
                minPeaks[writeBucket] = curMin;
                maxPeaks[writeBucket] = curMax;
                writeBucket = (writeBucket + 1) % numBuckets;
                samplesIntoBucket = 0;
                /* The extremes start at +/- infinity (and not at 0), otherwise
                   a bucket that only holds positive (or only negative)
                   samples would be reported as spanning zero, which makes the
                   drawn waveform far too loud. */
                curMin = std::numeric_limits<float>::max();
                curMax = std::numeric_limits<float>::lowest();
            }
        }
    }

    int getNumBuckets() const { return numBuckets; }
    float getBucketMin(int i) const { return minPeaks[i]; }
    float getBucketMax(int i) const { return maxPeaks[i]; }
    int getWriteBucket() const { return writeBucket; }
    double getBucketSpanSeconds() const { return windowSeconds / (double)numBuckets; }
    double getWindowSeconds() const { return windowSeconds; }

private:
    double sampleRate = 48000.0;
    int samplesPerBucket = 0;
    int samplesIntoBucket = 0;
    int writeBucket = 0;
    float curMin = std::numeric_limits<float>::max();
    float curMax = std::numeric_limits<float>::lowest();
    std::atomic<bool> active{false};
    std::vector<float> minPeaks;
    std::vector<float> maxPeaks;
};
