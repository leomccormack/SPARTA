#include "pathAutomation.h"

/* Serialises a keyframe (time, position, pause duration and both tangent
   handles) into a ValueTree so the whole path bank can be saved with the
   plugin state. */
juce::ValueTree Keyframe::toValueTree() const
{
    juce::ValueTree vt("KF");
    vt.setProperty("t", timeSeconds, nullptr);
    vt.setProperty("x", x, nullptr);
    vt.setProperty("y", y, nullptr);
    vt.setProperty("z", z, nullptr);
    vt.setProperty("st", stopTime, nullptr);
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
   replaced by PathData::recomputeDefaultTangents() on load. The pause
   (stopTime) property is also optional and defaults to 0 (no pause). */
Keyframe Keyframe::fromValueTree(const juce::ValueTree& vt)
{
    Keyframe kf;
    kf.timeSeconds = vt.getProperty("t", 0.0);
    kf.x = vt.getProperty("x", 0.0f);
    kf.y = vt.getProperty("y", 0.0f);
    kf.z = vt.getProperty("z", 0.0f);
    kf.stopTime = vt.getProperty("st", 0.0f);
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
   first/last keyframe, or wraps modulo the window when loop is enabled.

   Pauses: when a keyframe has a non-zero stopTime, the object holds that
   keyframe's position for stopTime seconds after reaching it. Because each
   pause delays everything that follows, the effective time of keyframe i is
   timeSeconds[i] + (sum of stopTime for all earlier keyframes). The pause
   window itself spans [effTime_i, effTime_i + stopTime_i]; within it the
   position is the keyframe's own. */
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

    /* Pauses extend the path: the total pause time is added to the loop
       period (or clamp end) so wrapping lands back on the same keyframe
       phase. */
    double totalStop = 0.0;
    for (auto& kf : keyframes) totalStop += kf.stopTime;

    /* Handle out-of-window queries: wrap (loop) or clamp to the ends. */
    double loopSpan = (endTime - startTime) + totalStop;
    if (t < startTime || t > startTime + loopSpan) {
        if (loop && loopSpan > 0.0) {
            t = startTime + std::fmod(t - startTime, loopSpan);
            if (t < startTime) t += loopSpan;
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

    /* Effective keyframe times: each keyframe is delayed by the accumulated
       stopTime of every earlier keyframe. While the host time sits inside a
       pause window the object stays put at that keyframe. */
    double rel = t - startTime;
    double cumStop = 0.0;

    for (size_t k = 0; k < n; ++k) {
        double effTime = keyframes[k].timeSeconds + cumStop;
        double pauseEnd = effTime + keyframes[k].stopTime;

        if (rel < effTime) {
            /* Before this keyframe (only possible for the first one, since
               previous pauses+segments fill all earlier time). */
            if (k == 0) {
                outX = keyframes.front().x;
                outY = keyframes.front().y;
                outZ = keyframes.front().z;
                return;
            }
            break;
        }

        if (rel < pauseEnd) {
            /* Inside the pause window: hold the keyframe position. */
            outX = keyframes[k].x;
            outY = keyframes[k].y;
            outZ = keyframes[k].z;
            return;
        }

        if (k + 1 < n) {
            /* Segment from keyframe k to k+1. Its effective start is the end
               of k's pause; its end is keyframe k+1's effective time. */
            double nextEff = keyframes[k + 1].timeSeconds + cumStop + keyframes[k].stopTime;
            if (rel < nextEff) {
                const auto& k0 = keyframes[k];
                const auto& k1 = keyframes[k + 1];

                double span = k1.timeSeconds - k0.timeSeconds;
                double u = (span > 1e-9) ? (rel - pauseEnd) / span : 0.0;
                if (u < 0.0) u = 0.0;
                else if (u > 1.0) u = 1.0;
                double u2 = u * u;
                double u3 = u2 * u;

                double h00 = 2.0 * u3 - 3.0 * u2 + 1.0;
                double h10 = u3 - 2.0 * u2 + u;
                double h01 = -2.0 * u3 + 3.0 * u2;
                double h11 = u3 - u2;

                outX = (float)(h00 * k0.x + h10 * k0.txOut + h01 * k1.x + h11 * k1.txIn);
                outY = (float)(h00 * k0.y + h10 * k0.tyOut + h01 * k1.y + h11 * k1.tyIn);
                outZ = (float)(h00 * k0.z + h10 * k0.tzOut + h01 * k1.z + h11 * k1.tzIn);
                return;
            }
        }

        cumStop += keyframes[k].stopTime;
    }

    /* Past the last keyframe (or the pause that follows it): clamp. */
    outX = keyframes.back().x;
    outY = keyframes.back().y;
    outZ = keyframes.back().z;
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
        sources[i] = PathData();
        sources[i].name = "Path 1";
    }
    for (int i = 0; i < ROOM_SIM_MAX_NUM_RECEIVERS; ++i) {
        receivers[i] = PathData();
        receivers[i].name = "Path 1";
    }
    stateVersion = 0;
}

PathData& PathBank::getSourcePath(int index)
{
    return sources[index];
}

const PathData& PathBank::getSourcePath(int index) const
{
    return sources[index];
}

PathData& PathBank::getReceiverPath(int index)
{
    return receivers[index];
}

const PathData& PathBank::getReceiverPath(int index) const
{
    return receivers[index];
}

juce::ValueTree PathBank::toValueTree() const
{
    juce::ValueTree vt("PATHS");
    vt.setProperty("version", stateVersion, nullptr);
    for (int i = 0; i < ROOM_SIM_MAX_NUM_SOURCES; ++i) {
        juce::ValueTree srcVt("SOURCE");
        srcVt.setProperty("index", i, nullptr);
        srcVt.addChild(sources[i].toValueTree(), -1, nullptr);
        vt.addChild(srcVt, -1, nullptr);
    }
    for (int i = 0; i < ROOM_SIM_MAX_NUM_RECEIVERS; ++i) {
        juce::ValueTree recVt("RECEIVER");
        recVt.setProperty("index", i, nullptr);
        recVt.addChild(receivers[i].toValueTree(), -1, nullptr);
        vt.addChild(recVt, -1, nullptr);
    }
    return vt;
}

void PathBank::fromValueTree(const juce::ValueTree& vt)
{
    if (!vt.hasType("PATHS")) return;
    clear();
    /* Older states without the version property are treated as version 0:
       they still apply on a fresh load, but can never overwrite edits made
       after them. */
    stateVersion = vt.getProperty("version", 0);

    /* States saved before the one-path-per-object simplification may contain
       several PATH children per SOURCE/RECEIVER. Pick the most useful one:
       the first enabled path, else the first path that has keyframes, else
       the first path. */
    const auto pickPath = [] (const juce::ValueTree& node) -> PathData {
        PathData enabledPath;
        bool haveEnabled = false;
        PathData fallback;
        for (int p = 0; p < node.getNumChildren(); ++p) {
            auto pathChild = node.getChild(p);
            if (!pathChild.hasType("PATH")) continue;
            PathData pd = PathData::fromValueTree(pathChild);
            if (!haveEnabled && pd.enabled) {
                enabledPath = pd;
                haveEnabled = true;
            }
            if (fallback.keyframes.empty() && !pd.keyframes.empty())
                fallback = pd;
        }
        if (haveEnabled) return enabledPath;
        if (!fallback.keyframes.empty()) return fallback;
        for (int p = 0; p < node.getNumChildren(); ++p) {
            auto pathChild = node.getChild(p);
            if (pathChild.hasType("PATH"))
                return PathData::fromValueTree(pathChild);
        }
        return PathData();
    };

    for (int i = 0; i < vt.getNumChildren(); ++i) {
        auto child = vt.getChild(i);
        int idx = child.getProperty("index", -1);
        if (idx < 0) continue;
        if (child.hasType("SOURCE") && idx < ROOM_SIM_MAX_NUM_SOURCES)
            sources[idx] = pickPath(child);
        else if (child.hasType("RECEIVER") && idx < ROOM_SIM_MAX_NUM_RECEIVERS)
            receivers[idx] = pickPath(child);
    }
}
