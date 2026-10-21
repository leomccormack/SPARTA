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

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include <JuceHeader.h>
#include "../../resources/PluginProcessorBase.h"
#include "ambi_roomsim.h"
#include "pathAutomation.h"
#include "waveformCapture.h"
#include <thread>
#include <atomic>
#include <array>
#define CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS 1
#include "../../resources/ConfigurationHelper.h"

#define BUILD_VER_SUFFIX "" /* String to be added before the version name on the GUI (e.g. beta, alpha etc..) */
#ifndef MIN
# define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
# define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif

/* Peak-bucket representation of a loaded reference track, shown statically
   in the timeline strip. Built once when an audio file is chosen/restored;
   only min/max pairs are kept (see WaveformCapture::numBuckets for the
   bucket count), so memory is bounded regardless of the track length. */
struct TrackWaveform {
    bool valid = false;
    juce::String filePath;
    double sampleRate = 0.0;
    double durationSeconds = 0.0;
    std::vector<float> minPeaks;
    std::vector<float> maxPeaks;

    void clear() {
        valid = false;
        filePath.clear();
        sampleRate = 0.0;
        durationSeconds = 0.0;
        minPeaks.clear();
        maxPeaks.clear();
    }
};

class PluginProcessor  : public PluginProcessorBase
{
public:
    PluginProcessor();
    ~PluginProcessor();

    /* PluginProcessorBase mandatory overrides */
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {};
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    
    /* PluginEditor */
    juce::AudioProcessorEditor* createEditor() override;
    
    /* Get functions */
    void* getFXHandle() { return hAmbi; }
    
    /* For refreshing window during automation */ 
    void setRefreshWindow(bool newState) { refreshWindow = newState; }
    bool getRefreshWindow() { return refreshWindow; }

    /* Path automation */
    PathBank& getPathBank() { return pathBank; }
    juce::SpinLock& getPathLock() { return pathLock; }
    /* Marks the path bank as edited. The edit counter lets the audio thread
       detect a change without relying on a flag that could be cleared twice
       (see processBlock). notifyHost should only be true for discrete
       edits: during a continuous drag the host is notified once, when the
       gesture ends, instead of on every mouse-move. */
    void markPathDirty(bool notifyHost = true) {
        pathEditCounter.fetch_add(1, std::memory_order_release);
        /* The version is bumped on every edit (and not only when the host
           is notified), so that a stale host snapshot (undo/template) can
           never overwrite newer in-memory edits. */
        pathStateVersion.fetch_add(1, std::memory_order_release);
        if (notifyHost) {
            /* Tell the host that the state of the plug-in has changed, so
               that it saves the new path data. */
            updateHostDisplay(juce::AudioProcessorListener::ChangeDetails{}
                                  .withNonParameterStateChanged(true));
        }
    }
    /* Makes the audio thread pick up the current path bank again, without
       touching the state version (used after a state restore, where the
       version is taken from the restored data). */
    void refreshPathSnapshot() {
        pathEditCounter.fetch_add(1, std::memory_order_release);
    }
    double getCurrentHostTime() const { return currentHostTime.load(); }

    /* True when the host position is expressed in PPQ (bars) rather than in
       seconds. The GUI labels the time fields accordingly. */
    bool isTimeInPpq() const { return getParameterChoice("pathTimeMode") == 1; }
    /* The unit the path times are expressed in ("s" or "PPQ"). */
    juce::String getTimeUnitLabel() const { return isTimeInPpq() ? juce::String("PPQ") : juce::String("s"); }

    /* Track end length: the highest host time the transport has reached.
       JUCE's AudioPlayHead has no track-length field, so the plugin
       remembers the furthest position seen (playback or scrub) as the
       default end time for newly created paths. */
    double getTrackEndTime() const { return maxHostTime.load(); }
    void noteHostTime(double t) {
        double m = maxHostTime.load();
        while (t > m && !maxHostTime.compare_exchange_weak(m, t)) {}
    }

    /* Peak-buffer waveform capture of the mono input mix, shown in the
       timeline strip. Writers (audio thread) and readers (UI thread) are
       synchronised with waveLock. */
    const WaveformCapture& getWaveformCapture() const { return waveformCapture; }
    void resetWaveform() {
        const juce::SpinLock::ScopedLockType sl(waveLock);
        waveformCapture.reset();
    }

    /* Loaded reference track: a full WAV/AIFF decoded into peak buckets on
       a background thread, shown statically in the timeline strip. */
    bool hasTrackWaveform() const {
        const juce::SpinLock::ScopedLockType sl(trackWaveLock);
        return trackWaveform.valid;
    }
    const TrackWaveform& getTrackWaveform() const { return trackWaveform; }
    TrackWaveform getTrackWaveformSnapshot() const {
        const juce::SpinLock::ScopedLockType sl(trackWaveLock);
        return trackWaveform;
    }
    bool isTrackLoading() const { return trackLoading.load(); }
    void loadTrackFile(const juce::File& file);
    void clearTrackFile();
    
    /* Hide internal setParameterValue when automation is pushing (to suppress parameterChanged re-entry) */
    void setApplyingFromAutomation(bool v) { applyingFromAutomation.store(v); }
    bool isApplyingFromAutomation() const { return applyingFromAutomation.load(); }
    
private:
    void* hAmbi;                       /* ambi_roomsim handle */
    bool refreshWindow;

    /* Path automation members */
    PathBank pathBank;
    juce::SpinLock pathLock;
    /* Incremented on every path edit. The audio thread compares it with the
       counter of the snapshot it holds: a difference means the snapshot is
       stale and must be refreshed. A counter is used (instead of a flag)
       because a flag could be cleared by the audio thread after the UI
       thread has already set it again, which would silently drop an edit. */
    std::atomic<uint32_t> pathEditCounter{0};
    /* Monotonic version of the path bank, saved with the plugin state and
       compared on restore so that a host re-applying an OLDER snapshot
       (Ardour undo/template/undo of a parameter change) cannot clobber
       newer in-memory edits. */
    std::atomic<int> pathStateVersion{0};
    PathBank pathSnapshot;
    uint32_t pathSnapshotCounter = 0;    /* audio thread only */
    mutable std::atomic<double> currentHostTime{0.0};
    mutable std::atomic<double> maxHostTime{0.0};
    std::atomic<bool> applyingFromAutomation{false};
    double lastWaveHostTime = 0.0;

    /* Cached pointers to the position parameters that mirror the path-driven
       object positions. They are looked up once (building juce::Strings per
       audio block would allocate on the audio thread). */
    struct PositionParams {
        juce::RangedAudioParameter* x = nullptr;
        juce::RangedAudioParameter* y = nullptr;
        juce::RangedAudioParameter* z = nullptr;
    };
    std::array<PositionParams, ROOM_SIM_MAX_NUM_SOURCES> sourceParams;
    std::array<PositionParams, ROOM_SIM_MAX_NUM_RECEIVERS> receiverParams;
    void cachePositionParameters();

    /* Waveform capture of the mono input mix (see waveformCapture.h). */
    WaveformCapture waveformCapture;
    juce::SpinLock waveLock;
    juce::AudioBuffer<float> waveMixBuffer;

    /* Loaded reference track (see TrackWaveform above). Decoding runs on a
       background thread; trackWaveLock guards the reader/writer. loadToken
       discards a stale decode if the user switches the file mid-load. */
    juce::AudioFormatManager trackFormatManager;
    TrackWaveform trackWaveform;
    juce::SpinLock trackWaveLock;
    std::atomic<bool> trackLoading{false};
    int loadToken = 0;
    juce::ThreadPool trackThreadPool{1};

    class TrackDecodeJob  : public juce::ThreadPoolJob
    {
    public:
        TrackDecodeJob(PluginProcessor& p, const juce::File& f, int token);
        JobStatus runJob() override;
    private:
        PluginProcessor& processor;
        juce::File file;
        int token;
    };

    void decodeTrack(const juce::File& file, int token);
    void applyPath(int index, const PathData& path, double t, bool isReceiver);
    /* Diagnostic: traces path-bank serialization to a file when the
       SPARTA_AMB_ROOMSIM_STATE_LOG env var points at a log path. */
    void logPathState(const char* where) const;
    
    /* For syncing parameter values between the JUCE parameter tree and the internal DSP object */
    void setParameterValuesUsingInternalState();
    void setInternalStateUsingParameterValues();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
