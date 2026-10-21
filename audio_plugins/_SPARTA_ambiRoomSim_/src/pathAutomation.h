#pragma once

#include <JuceHeader.h>
#include <array>
#include <cmath>
#include <string>
#include <vector>
#include "ambi_roomsim.h"

/* A stable colour per path, shared by the room view and the timeline so the
   same path always looks the same. Source paths start from a warm hue and
   receiver paths from a cool hue; each object index shifts the hue so
   neighbouring objects are easy to tell apart. */
inline juce::Colour getPathColour(bool isReceiver, int objIdx)
{
    const float baseHue = isReceiver ? 0.80f : 0.10f;
    const float hue = std::fmod(baseHue + objIdx * 0.20f, 1.0f);
    return juce::Colour::fromHSV(hue, 0.70f, 0.95f, 1.0f);
}

/* A single point on a path. The path is a cubic Hermite spline that passes
   through every keyframe; each keyframe also carries a pair of tangent
   vectors (in/out) that shape the curve between neighbouring keyframes. */
struct Keyframe {
    /* Time of this keyframe relative to the path's startTime (seconds). */
    double timeSeconds = 0.0;
    /* Position in the room, in metres. */
    float x = 0.0f, y = 0.0f, z = 0.0f;

    /* Hold the object at this keyframe's position for stopTime seconds
       after it arrives (a pause), before continuing along the next segment.
       The pause is baked into the timeline: editing stopTime shifts the
       timeSeconds of all following keyframes (and the path endTime) by the
       same amount, so timeSeconds is the real arrival time including all
       earlier pauses. */
    float stopTime = 0.0f;

    /* Cubic Hermite spline tangents (in metres, as u-derivatives).
       The in/out handles are drawn at P - mIn/3 and P + mOut/3. */
    float txIn = 0.0f, tyIn = 0.0f, tzIn = 0.0f;
    float txOut = 0.0f, tyOut = 0.0f, tzOut = 0.0f;

    juce::ValueTree toValueTree() const;
    static Keyframe fromValueTree(const juce::ValueTree& vt);
};

/* Maximum number of keyframes that a single path may hold. The limit keeps
   the keyframe buffers of a fixed size, so that the copy of the path bank
   that the audio thread makes never has to allocate memory. */
static constexpr int MAX_KEYFRAMES_PER_PATH = 64;

/* One motion path for a single source or receiver. When enabled, the path
   drives the object's position through its keyframes as the host time
   advances. Exactly one path exists per source/receiver. */
struct PathData {
    std::vector<Keyframe> keyframes;
    /* Whether the path drives the object position. Disabled paths are
       locked in the room view (not editable) and ignored by the audio thread. */
    bool enabled = false;
    /* Wrap the path around its [startTime, endTime] window. */
    bool loop = false;
    /* Start/end of the path window, in seconds. */
    double startTime = 0.0;
    double endTime = 10.0;

    /* Sample the spline at time t (host seconds); writes the resulting
       room position (metres) into outX/outY/outZ. Outside the window the
       path clamps to its ends, or wraps when loop is enabled. */
    void evaluate(double t, float& outX, float& outY, float& outZ) const;
    double duration() const;
    /* Scales the keyframe times proportionally when the path duration
       changes from oldDuration to newDuration. The pauses (stopTime) are
       kept as they are, only the time spent moving is scaled, so the
       relative timing of the nodes survives stretching the path. */
    static void scaleTimes(PathData& path, double oldDuration, double newDuration);
    /* Reset every keyframe's tangents to the Catmull-Rom default that
       reproduces the classic smooth-through-all-points curve. */
    void recomputeDefaultTangents();
    /* Reset only the tangent(s) of the keyframe at index to the default. */
    void recomputeDefaultTangent(int index);

    juce::ValueTree toValueTree() const;
    static PathData fromValueTree(const juce::ValueTree& vt);
};

/* Container for the single path of every source and receiver. */
class PathBank {
public:
    PathBank();

    void clear();

    PathData& getSourcePath(int index);
    const PathData& getSourcePath(int index) const;

    PathData& getReceiverPath(int index);
    const PathData& getReceiverPath(int index) const;

    /* Serialises the bank. The version is passed in (rather than stored
       here) because it is bumped by the processor whenever the bank is
       edited, and it has to be readable while the bank is being edited. */
    juce::ValueTree toValueTree(int version) const;
    void fromValueTree(const juce::ValueTree& vt);

    /* Reserves room for n keyframes in every path. The audio thread copies
       the bank whenever it is edited; reserving the capacity up-front means
       that this copy never allocates memory (which would be a real-time
       violation). */
    void reserveKeyframeCapacity(int n);

private:
    std::array<PathData, ROOM_SIM_MAX_NUM_SOURCES> sources;
    std::array<PathData, ROOM_SIM_MAX_NUM_RECEIVERS> receivers;
};
