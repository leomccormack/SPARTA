#pragma once

#include <JuceHeader.h>
#include <array>
#include <string>
#include <vector>
#include "ambi_roomsim.h"

struct Keyframe {
    double timeSeconds = 0.0;
    float x = 0.0f, y = 0.0f, z = 0.0f;

    /* Cubic Hermite spline tangents (in metres, as u-derivatives).
       The in/out handles are drawn at P - mIn/3 and P + mOut/3. */
    float txIn = 0.0f, tyIn = 0.0f, tzIn = 0.0f;
    float txOut = 0.0f, tyOut = 0.0f, tzOut = 0.0f;

    juce::ValueTree toValueTree() const;
    static Keyframe fromValueTree(const juce::ValueTree& vt);
};

struct PathData {
    std::vector<Keyframe> keyframes;
    bool enabled = false;
    bool loop = false;
    double startTime = 0.0;
    double endTime = 10.0;
    std::string name;

    void evaluate(double t, float& outX, float& outY, float& outZ) const;
    double duration() const;
    static void redistributeTimes(PathData& path, double totalDuration);
    void recomputeDefaultTangents();
    void recomputeDefaultTangent(int index);

    juce::ValueTree toValueTree() const;
    static PathData fromValueTree(const juce::ValueTree& vt);
};

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
