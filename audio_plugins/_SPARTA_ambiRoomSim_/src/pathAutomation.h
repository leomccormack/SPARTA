#pragma once

#include <JuceHeader.h>
#include <array>
#include <string>
#include <vector>
#include "ambi_roomsim.h"

/* A single point on a path. The path is a cubic Hermite spline that passes
   through every keyframe; each keyframe also carries a pair of tangent
   vectors (in/out) that shape the curve between neighbouring keyframes. */
struct Keyframe {
    /* Time of this keyframe relative to the path's startTime (seconds). */
    double timeSeconds = 0.0;
    /* Position in the room, in metres. */
    float x = 0.0f, y = 0.0f, z = 0.0f;

    /* Cubic Hermite spline tangents (in metres, as u-derivatives).
       The in/out handles are drawn at P - mIn/3 and P + mOut/3. */
    float txIn = 0.0f, tyIn = 0.0f, tzIn = 0.0f;
    float txOut = 0.0f, tyOut = 0.0f, tzOut = 0.0f;

    juce::ValueTree toValueTree() const;
    static Keyframe fromValueTree(const juce::ValueTree& vt);
};

/* One motion path for a single source or receiver. When enabled, the path
   drives the object's position through its keyframes as the host time
   advances. Multiple paths can coexist per object; only one plays at a time. */
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
    /* Display name shown in the path selector. */
    std::string name;

    /* Sample the spline at time t (host seconds); writes the resulting
       room position (metres) into outX/outY/outZ. Outside the window the
       path clamps to its ends, or wraps when loop is enabled. */
    void evaluate(double t, float& outX, float& outY, float& outZ) const;
    double duration() const;
    /* Evenly redistribute keyframe times across totalDuration. */
    static void redistributeTimes(PathData& path, double totalDuration);
    /* Reset every keyframe's tangents to the Catmull-Rom default that
       reproduces the classic smooth-through-all-points curve. */
    void recomputeDefaultTangents();
    /* Reset only the tangent(s) of the keyframe at index to the default. */
    void recomputeDefaultTangent(int index);

    juce::ValueTree toValueTree() const;
    static PathData fromValueTree(const juce::ValueTree& vt);
};

/* Container for the paths of all sources and receivers. Always keeps at
   least one (possibly empty) path per object. */
class PathBank {
public:
    PathBank();

    void clear();

    int getNumSourcePaths(int index) const;
    PathData& getSourcePath(int index, int pathIdx);
    const PathData& getSourcePath(int index, int pathIdx) const;
    int addSourcePath(int index);
    void removeSourcePath(int index, int pathIdx);

    int getNumReceiverPaths(int index) const;
    PathData& getReceiverPath(int index, int pathIdx);
    const PathData& getReceiverPath(int index, int pathIdx) const;
    int addReceiverPath(int index);
    void removeReceiverPath(int index, int pathIdx);

    juce::ValueTree toValueTree() const;
    void fromValueTree(const juce::ValueTree& vt);

private:
    std::array<std::vector<PathData>, ROOM_SIM_MAX_NUM_SOURCES> sources;
    std::array<std::vector<PathData>, ROOM_SIM_MAX_NUM_RECEIVERS> receivers;
};
