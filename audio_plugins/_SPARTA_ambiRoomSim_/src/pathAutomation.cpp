#include "pathAutomation.h"

/* Serialises a keyframe (time, position and both tangent handles) into a
   ValueTree so the whole path bank can be saved with the plugin state. */
juce::ValueTree Keyframe::toValueTree() const
{
    juce::ValueTree vt("KF");
    vt.setProperty("t", timeSeconds, nullptr);
    vt.setProperty("x", x, nullptr);
    vt.setProperty("y", y, nullptr);
    vt.setProperty("z", z, nullptr);
    vt.setProperty("txIn", txIn, nullptr);
    vt.setProperty("tyIn", tyIn, nullptr);
    vt.setProperty("tzIn", tzIn, nullptr);
    vt.setProperty("txOut", txOut, nullptr);
    vt.setProperty("tyOut", tyOut, nullptr);
    vt.setProperty("tzOut", tzOut, nullptr);
    return vt;
}

/* Reads a keyframe back from a ValueTree. Tangent properties may be absent
   in state saved by older versions; they default to zero there and are
   replaced by PathData::recomputeDefaultTangents() on load. */
Keyframe Keyframe::fromValueTree(const juce::ValueTree& vt)
{
    Keyframe kf;
    kf.timeSeconds = vt.getProperty("t", 0.0);
    kf.x = vt.getProperty("x", 0.0f);
    kf.y = vt.getProperty("y", 0.0f);
    kf.z = vt.getProperty("z", 0.0f);
    kf.txIn = vt.getProperty("txIn", 0.0f);
    kf.tyIn = vt.getProperty("tyIn", 0.0f);
    kf.tzIn = vt.getProperty("tzIn", 0.0f);
    kf.txOut = vt.getProperty("txOut", 0.0f);
    kf.tyOut = vt.getProperty("tyOut", 0.0f);
    kf.tzOut = vt.getProperty("tzOut", 0.0f);
    return kf;
}

/* Evaluates the cubic Hermite spline at host time t and writes the room
   position (metres) into outX/outY/outZ.

   Within the [startTime, endTime] window the position is interpolated
   segment by segment; each segment is a cubic Hermite curve built from the
   keyframe positions and their stored in/out tangents (see the basis
   functions h00..h11 below). Outside the window the curve clamps to its
   first/last keyframe, or wraps modulo the window when loop is enabled. */
void PathData::evaluate(double t, float& outX, float& outY, float& outZ) const
{
    size_t n = keyframes.size();
    if (n == 0) return;
    if (n == 1) {
        outX = keyframes[0].x;
        outY = keyframes[0].y;
        outZ = keyframes[0].z;
        return;
    }

    /* Handle out-of-window queries: wrap (loop) or clamp to the ends. */
    if (t < startTime || t > endTime) {
        if (loop && endTime > startTime) {
            double span = endTime - startTime;
            t = startTime + std::fmod(t - startTime, span);
            if (t < startTime) t += span;
        } else {
            if (t <= startTime) {
                outX = keyframes.front().x;
                outY = keyframes.front().y;
                outZ = keyframes.front().z;
            } else {
                outX = keyframes.back().x;
                outY = keyframes.back().y;
                outZ = keyframes.back().z;
            }
            return;
        }
    }

    /* Locate the segment containing t. */
    double rel = t - startTime;
    double T0 = keyframes.front().timeSeconds;
    double Tn = keyframes.back().timeSeconds;

    if (rel <= T0) {
        outX = keyframes.front().x;
        outY = keyframes.front().y;
        outZ = keyframes.front().z;
        return;
    }
    if (rel >= Tn) {
        outX = keyframes.back().x;
        outY = keyframes.back().y;
        outZ = keyframes.back().z;
        return;
    }

    size_t i;
    for (i = 0; i < n - 1; ++i)
        if (keyframes[i + 1].timeSeconds >= rel) break;

    const auto& k0 = keyframes[i];
    const auto& k1 = keyframes[i + 1];

    /* Normalised position within the segment [k0, k1]. */
    double span = k1.timeSeconds - k0.timeSeconds;
    double u = (span > 1e-9) ? (rel - k0.timeSeconds) / span : 0.0;
    if (u < 0.0) u = 0.0;
    else if (u > 1.0) u = 1.0;
    double u2 = u * u;
    double u3 = u2 * u;

    /* Cubic Hermite basis functions. */
    double h00 = 2.0 * u3 - 3.0 * u2 + 1.0;
    double h10 = u3 - 2.0 * u2 + u;
    double h01 = -2.0 * u3 + 3.0 * u2;
    double h11 = u3 - u2;

    outX = (float)(h00 * k0.x + h10 * k0.txOut + h01 * k1.x + h11 * k1.txIn);
    outY = (float)(h00 * k0.y + h10 * k0.tyOut + h01 * k1.y + h11 * k1.tyIn);
    outZ = (float)(h00 * k0.z + h10 * k0.tzOut + h01 * k1.z + h11 * k1.tzIn);
}

double PathData::duration() const
{
    return endTime - startTime;
}

/* Evenly re-times the keyframes so they span totalDuration. Used after
   adding/removing a keyframe; the room-space shape (positions + tangents)
   is unaffected because tangents are stored as u-derivatives. */
void PathData::redistributeTimes(PathData& path, double totalDuration)
{
    int n = (int)path.keyframes.size();
    if (n <= 1) return;
    double step = totalDuration / (double)(n - 1);
    for (int i = 0; i < n; ++i)
        path.keyframes[i].timeSeconds = (double)i * step;
}

/* Resets the tangents of one keyframe to the Catmull-Rom default
   (dx,dy,dz) = (next - prev)/2, where prev/next are the neighbouring
   keyframes (clamped to the keyframe itself at the path ends). With the
   same default applied everywhere, the Hermite spline reproduces the
   classic smooth-through-all-points Catmull-Rom curve. */
void PathData::recomputeDefaultTangent(int index)
{
    int n = (int)keyframes.size();
    if (n == 0 || index < 0 || index >= n) return;
    const Keyframe& prev = keyframes[index > 0 ? index - 1 : 0];
    const Keyframe& next = keyframes[index < n - 1 ? index + 1 : n - 1];
    float dx = 0.5f * (next.x - prev.x);
    float dy = 0.5f * (next.y - prev.y);
    float dz = 0.5f * (next.z - prev.z);
    keyframes[index].txIn  = dx;
    keyframes[index].tyIn  = dy;
    keyframes[index].tzIn  = dz;
    keyframes[index].txOut = dx;
    keyframes[index].tyOut = dy;
    keyframes[index].tzOut = dz;
}

void PathData::recomputeDefaultTangents()
{
    for (int i = 0; i < (int)keyframes.size(); ++i)
        recomputeDefaultTangent(i);
}

juce::ValueTree PathData::toValueTree() const
{
    juce::ValueTree vt("PATH");
    vt.setProperty("enabled", enabled, nullptr);
    vt.setProperty("loop", loop, nullptr);
    vt.setProperty("startTime", startTime, nullptr);
    vt.setProperty("endTime", endTime, nullptr);
    vt.setProperty("name", juce::String(name), nullptr);
    for (auto& kf : keyframes)
        vt.addChild(kf.toValueTree(), -1, nullptr);
    return vt;
}

PathData PathData::fromValueTree(const juce::ValueTree& vt)
{
    PathData path;
    path.enabled = vt.getProperty("enabled", false);
    path.loop = vt.getProperty("loop", false);
    path.startTime = vt.getProperty("startTime", 0.0);
    path.endTime = vt.getProperty("endTime", 10.0);
    path.name = vt.getProperty("name", "").toString().toStdString();
    bool hasTangents = false;
    for (int i = 0; i < vt.getNumChildren(); ++i) {
        auto child = vt.getChild(i);
        if (child.hasType("KF")) {
            if (child.hasProperty("txOut"))
                hasTangents = true;
            path.keyframes.push_back(Keyframe::fromValueTree(child));
        }
    }
    if (!hasTangents)
        path.recomputeDefaultTangents();
    return path;
}

PathBank::PathBank()
{
    clear();
}

void PathBank::clear()
{
    for (int i = 0; i < ROOM_SIM_MAX_NUM_SOURCES; ++i) {
        sources[i].clear();
        sources[i].push_back(PathData());
        sources[i].back().name = "Path 1";
    }
    for (int i = 0; i < ROOM_SIM_MAX_NUM_RECEIVERS; ++i) {
        receivers[i].clear();
        receivers[i].push_back(PathData());
        receivers[i].back().name = "Path 1";
    }
}

int PathBank::getNumSourcePaths(int index) const
{
    return (int)sources[index].size();
}

PathData& PathBank::getSourcePath(int index, int pathIdx)
{
    return sources[index][pathIdx];
}

const PathData& PathBank::getSourcePath(int index, int pathIdx) const
{
    return sources[index][pathIdx];
}

int PathBank::addSourcePath(int index)
{
    PathData pd;
    int n = (int)sources[index].size();
    pd.name = "Path " + std::to_string(n + 1);
    sources[index].push_back(std::move(pd));
    return (int)sources[index].size() - 1;
}

void PathBank::removeSourcePath(int index, int pathIdx)
{
    sources[index].erase(sources[index].begin() + pathIdx);
}

int PathBank::getNumReceiverPaths(int index) const
{
    return (int)receivers[index].size();
}

PathData& PathBank::getReceiverPath(int index, int pathIdx)
{
    return receivers[index][pathIdx];
}

const PathData& PathBank::getReceiverPath(int index, int pathIdx) const
{
    return receivers[index][pathIdx];
}

int PathBank::addReceiverPath(int index)
{
    PathData pd;
    int n = (int)receivers[index].size();
    pd.name = "Path " + std::to_string(n + 1);
    receivers[index].push_back(std::move(pd));
    return (int)receivers[index].size() - 1;
}

void PathBank::removeReceiverPath(int index, int pathIdx)
{
    receivers[index].erase(receivers[index].begin() + pathIdx);
}

juce::ValueTree PathBank::toValueTree() const
{
    juce::ValueTree vt("PATHS");
    for (int i = 0; i < ROOM_SIM_MAX_NUM_SOURCES; ++i) {
        if (sources[i].empty()) continue;
        juce::ValueTree srcVt("SOURCE");
        srcVt.setProperty("index", i, nullptr);
        for (auto& path : sources[i])
            srcVt.addChild(path.toValueTree(), -1, nullptr);
        vt.addChild(srcVt, -1, nullptr);
    }
    for (int i = 0; i < ROOM_SIM_MAX_NUM_RECEIVERS; ++i) {
        if (receivers[i].empty()) continue;
        juce::ValueTree recVt("RECEIVER");
        recVt.setProperty("index", i, nullptr);
        for (auto& path : receivers[i])
            recVt.addChild(path.toValueTree(), -1, nullptr);
        vt.addChild(recVt, -1, nullptr);
    }
    return vt;
}

void PathBank::fromValueTree(const juce::ValueTree& vt)
{
    if (!vt.hasType("PATHS")) return;
    clear();
    for (int i = 0; i < vt.getNumChildren(); ++i) {
        auto child = vt.getChild(i);
        int idx = child.getProperty("index", -1);
        if (idx < 0) continue;
        if (child.hasType("SOURCE") && idx < ROOM_SIM_MAX_NUM_SOURCES) {
            sources[idx].clear();
            for (int p = 0; p < child.getNumChildren(); ++p) {
                auto pathChild = child.getChild(p);
                if (pathChild.hasType("PATH"))
                    sources[idx].push_back(PathData::fromValueTree(pathChild));
            }
            if (sources[idx].empty())
                sources[idx].push_back(PathData());
        } else if (child.hasType("RECEIVER") && idx < ROOM_SIM_MAX_NUM_RECEIVERS) {
            receivers[idx].clear();
            for (int p = 0; p < child.getNumChildren(); ++p) {
                auto pathChild = child.getChild(p);
                if (pathChild.hasType("PATH"))
                    receivers[idx].push_back(PathData::fromValueTree(pathChild));
            }
            if (receivers[idx].empty())
                receivers[idx].push_back(PathData());
        }
    }
}
