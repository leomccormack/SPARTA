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

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <cstdio>
#include <cstdlib>

#if JucePlugin_Build_AAX && !JucePlugin_AAXDisableDefaultSettingsChunks
# error "AAX Default Settings Chunk is enabled. This may override parameter defaults."
#endif

/* Diagnostic aid for state persistence debugging. When the environment
   variable SPARTA_AMB_ROOMSIM_STATE_LOG points at a writable file, every
   getStateInformation/setStateInformation call appends a line summarising
   the path bank (including the start/end window of every enabled path) so a
   lost-path or lost-window bug can be attributed to the save side or the
   restore side. No-op when the variable is unset. */
void PluginProcessor::logPathState(const char* where) const
{
    const char* logPath = std::getenv("SPARTA_AMB_ROOMSIM_STATE_LOG");
    if (logPath == nullptr || logPath[0] == '\0')
        return;

    FILE* f = std::fopen(logPath, "a");
    if (f == nullptr)
        return;
    int nSrcPaths = 0, nRecPaths = 0, nKeyframes = 0;
    std::fprintf(f, "[%s] version=%d\n", where, pathBank.getStateVersion());
    for (int i = 0; i < ROOM_SIM_MAX_NUM_SOURCES; ++i) {
        const auto& p = pathBank.getSourcePath(i);
        if (p.enabled) {
            ++nSrcPaths;
            std::fprintf(f, "    source %d: start=%.3f end=%.3f kfs=%zu\n",
                         i, p.startTime, p.endTime, p.keyframes.size());
        }
        nKeyframes += (int)p.keyframes.size();
    }
    for (int i = 0; i < ROOM_SIM_MAX_NUM_RECEIVERS; ++i) {
        const auto& p = pathBank.getReceiverPath(i);
        if (p.enabled) {
            ++nRecPaths;
            std::fprintf(f, "    receiver %d: start=%.3f end=%.3f kfs=%zu\n",
                         i, p.startTime, p.endTime, p.keyframes.size());
        }
        nKeyframes += (int)p.keyframes.size();
    }
    std::fprintf(f, "    totals: srcPaths=%d recPaths=%d keyframes=%d\n",
                 nSrcPaths, nRecPaths, nKeyframes);
    std::fclose(f);
}

static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("outputOrder", "OutputOrder",
                                                                  juce::StringArray{"1st order","2nd order","3rd order","4th order","5th order","6th order","7th order","8th order","9th order","10th order"}, 2,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("channelOrder", "ChannelOrder", juce::StringArray{"ACN", "FuMa"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("normType", "NormType", juce::StringArray{"N3D", "SN3D", "FuMa"}, 1));
    params.push_back(std::make_unique<juce::AudioParameterBool>("enableReflections", "EnableReflections", true));
    params.push_back(std::make_unique<juce::AudioParameterInt>("maxReflectionOrder", "MaxReflectionOrder", 0, 7, 3));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("wallAbsCoeff_pX", "WallAbsCoeff (x+)", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
                                                                 ambi_roomsim_default_abs_wall[0]));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("wallAbsCoeff_nX", "WallAbsCoeff (x-)", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
                                                                 ambi_roomsim_default_abs_wall[1]));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("wallAbsCoeff_pY", "WallAbsCoeff (y+)", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
                                                                 ambi_roomsim_default_abs_wall[2]));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("wallAbsCoeff_nY", "WallAbsCoeff (y-)", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
                                                                 ambi_roomsim_default_abs_wall[3]));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("wallAbsCoeff_pZ", "WallAbsCoeff (z+)", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
                                                                 ambi_roomsim_default_abs_wall[4]));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("wallAbsCoeff_nZ", "WallAbsCoeff (z-)", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
                                                                 ambi_roomsim_default_abs_wall[5]));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("roomX", "RoomWidth (x)", juce::NormalisableRange<float>(0.5f, 20.0f, 0.01f), ambi_roomsim_default_room_dims[0],
                                                                 AudioParameterFloatAttributes().withLabel("m")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("roomY", "RoomDepth (y)", juce::NormalisableRange<float>(0.5f, 20.0f, 0.01f), ambi_roomsim_default_room_dims[1],
                                                                 AudioParameterFloatAttributes().withLabel("m")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("roomZ", "RoomHeight (z)", juce::NormalisableRange<float>(0.5f, 6.0f, 0.01f), ambi_roomsim_default_room_dims[2],
                                                                 AudioParameterFloatAttributes().withLabel("m")));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numSources", "NumSources", 1, ROOM_SIM_MAX_NUM_SOURCES, ambi_roomsim_defaultNumSources,
                                                               AudioParameterIntAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterInt>("numReceivers", "NumReceivers", 1, ROOM_SIM_MAX_NUM_RECEIVERS, ambi_roomsim_defaultNumReceivers,
                                                               AudioParameterIntAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("pathTimeOffset", "PathTimeOffset",
                                                                 juce::NormalisableRange<float>(-3600.0f, 3600.0f, 0.01f), 0.0f,
                                                                 AudioParameterFloatAttributes().withAutomatable(false)));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("pathTimeMode", "PathTimeMode",
                                                                  juce::StringArray{"Seconds", "Bars (PPQ)"}, 0,
                                                                  AudioParameterChoiceAttributes().withAutomatable(false)));
    for(int i=0; i<ROOM_SIM_MAX_NUM_SOURCES; i++){
        params.push_back(std::make_unique<juce::AudioParameterFloat>("sourceX" + juce::String(i), "SourceX_" + juce::String(i+1), juce::NormalisableRange<float>(0.0f, 20.0f, 0.01f), ambi_roomsim_defaultSourcePositions[i][0], AudioParameterFloatAttributes().withLabel("m")));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("sourceY" + juce::String(i), "SourceY_" + juce::String(i+1), juce::NormalisableRange<float>(0.0f, 20.0f, 0.01f), ambi_roomsim_defaultSourcePositions[i][1], AudioParameterFloatAttributes().withLabel("m")));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("sourceZ" + juce::String(i), "SourceZ_" + juce::String(i+1), juce::NormalisableRange<float>(0.0f, 6.0f, 0.01f), ambi_roomsim_defaultSourcePositions[i][2], AudioParameterFloatAttributes().withLabel("m")));
    }
    
    for(int i=0; i<ROOM_SIM_MAX_NUM_RECEIVERS; i++){
        params.push_back(std::make_unique<juce::AudioParameterFloat>("receiverX" + juce::String(i), "ReceiverX_" + juce::String(i+1), juce::NormalisableRange<float>(0.0f, 20.0f, 0.01f), ambi_roomsim_defaultReceiverPositions[i][0], AudioParameterFloatAttributes().withLabel("m")));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("receiverY" + juce::String(i), "ReceiverY_" + juce::String(i+1), juce::NormalisableRange<float>(0.0f, 20.0f, 0.01f), ambi_roomsim_defaultReceiverPositions[i][1], AudioParameterFloatAttributes().withLabel("m")));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("receiverZ" + juce::String(i), "ReceiverZ_" + juce::String(i+1), juce::NormalisableRange<float>(0.0f, 6.0f, 0.01f), ambi_roomsim_defaultReceiverPositions[i][2], AudioParameterFloatAttributes().withLabel("m")));
    }

    return { params.begin(), params.end() };
}

void PluginProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "outputOrder"){
        ambi_roomsim_setOutputOrder(hAmbi, static_cast<SH_ORDERS>(newValue+1.001f));
    }
    else if (parameterID == "channelOrder"){
        ambi_roomsim_setChOrder(hAmbi, static_cast<int>(newValue+1.001f));
    }
    else if (parameterID == "normType"){
        ambi_roomsim_setNormType(hAmbi, static_cast<int>(newValue+1.001f));
    }
    else if(parameterID == "enableReflections"){
        ambi_roomsim_setEnableIMSflag(hAmbi, static_cast<int>(newValue+0.5f));
    }
    else if(parameterID == "maxReflectionOrder"){
        ambi_roomsim_setMaxReflectionOrder(hAmbi, static_cast<int>(newValue));
    }
    else if(parameterID == "wallAbsCoeff_pX"){
        ambi_roomsim_setWallAbsCoeff(hAmbi, 0, 0, newValue);
    }
    else if(parameterID == "wallAbsCoeff_nX"){
        ambi_roomsim_setWallAbsCoeff(hAmbi, 0, 1, newValue);
    }
    else if(parameterID == "wallAbsCoeff_pY"){
        ambi_roomsim_setWallAbsCoeff(hAmbi, 1, 0, newValue);
    }
    else if(parameterID == "wallAbsCoeff_nY"){
        ambi_roomsim_setWallAbsCoeff(hAmbi, 1, 1, newValue);
    }
    else if(parameterID == "wallAbsCoeff_pZ"){
        ambi_roomsim_setWallAbsCoeff(hAmbi, 2, 0, newValue);
    }
    else if(parameterID == "wallAbsCoeff_nZ"){
        ambi_roomsim_setWallAbsCoeff(hAmbi, 2, 1, newValue);
    }
    else if(parameterID == "roomX"){
        ambi_roomsim_setRoomDimX(hAmbi, newValue);
    }
    else if(parameterID == "roomY"){
        ambi_roomsim_setRoomDimY(hAmbi, newValue);
    }
    else if(parameterID == "roomZ"){
        ambi_roomsim_setRoomDimZ(hAmbi, newValue);
    } 
    else if(parameterID == "numSources"){
        ambi_roomsim_setNumSources(hAmbi, static_cast<int>(newValue));
    }
    else if(parameterID == "numReceivers"){
        ambi_roomsim_setNumReceivers(hAmbi, static_cast<int>(newValue));
    }
    for(int i=0; i<ROOM_SIM_MAX_NUM_SOURCES; i++){
        if(parameterID == "sourceX" + juce::String(i)){
            if (!isApplyingFromAutomation()) {
                ambi_roomsim_setSourceX(hAmbi, i, newValue);
                setRefreshWindow(true);
            }
            return;
        }
        else if(parameterID == "sourceY" + juce::String(i)){
            if (!isApplyingFromAutomation()) {
                ambi_roomsim_setSourceY(hAmbi, i, newValue);
                setRefreshWindow(true);
            }
            return;
        }
        else if(parameterID == "sourceZ" + juce::String(i)){
            if (!isApplyingFromAutomation()) {
                ambi_roomsim_setSourceZ(hAmbi, i, newValue);
                setRefreshWindow(true);
            }
            return;
        }
    }
    for(int i=0; i<ROOM_SIM_MAX_NUM_RECEIVERS; i++){
        if(parameterID == "receiverX" + juce::String(i)){
            if (!isApplyingFromAutomation()) {
                ambi_roomsim_setReceiverX(hAmbi, i, newValue);
                setRefreshWindow(true);
            }
            return;
        }
        else if(parameterID == "receiverY" + juce::String(i)){
            if (!isApplyingFromAutomation()) {
                ambi_roomsim_setReceiverY(hAmbi, i, newValue);
                setRefreshWindow(true);
            }
            return;
        }
        else if(parameterID == "receiverZ" + juce::String(i)){
            if (!isApplyingFromAutomation()) {
                ambi_roomsim_setReceiverZ(hAmbi, i, newValue);
                setRefreshWindow(true);
            }
            return;
        }
    }
}

void PluginProcessor::setParameterValuesUsingInternalState()
{
    setParameterValue("outputOrder", ambi_roomsim_getOutputOrder(hAmbi)-1);
    setParameterValue("channelOrder", ambi_roomsim_getChOrder(hAmbi)-1);
    setParameterValue("normType", ambi_roomsim_getNormType(hAmbi)-1);
    setParameterValue("enableReflections", ambi_roomsim_getEnableIMSflag(hAmbi));
    setParameterValue("maxReflectionOrder", ambi_roomsim_getMaxReflectionOrder(hAmbi));
    setParameterValue("wallAbsCoeff_pX", ambi_roomsim_getWallAbsCoeff(hAmbi, 0, 0));
    setParameterValue("wallAbsCoeff_nX", ambi_roomsim_getWallAbsCoeff(hAmbi, 0, 1));
    setParameterValue("wallAbsCoeff_pY", ambi_roomsim_getWallAbsCoeff(hAmbi, 1, 0));
    setParameterValue("wallAbsCoeff_nY", ambi_roomsim_getWallAbsCoeff(hAmbi, 1, 1));
    setParameterValue("wallAbsCoeff_pZ", ambi_roomsim_getWallAbsCoeff(hAmbi, 2, 0));
    setParameterValue("wallAbsCoeff_nZ", ambi_roomsim_getWallAbsCoeff(hAmbi, 2, 1));
    setParameterValue("roomX", ambi_roomsim_getRoomDimX(hAmbi));
    setParameterValue("roomY", ambi_roomsim_getRoomDimY(hAmbi));
    setParameterValue("roomZ", ambi_roomsim_getRoomDimZ(hAmbi));
    setParameterValue("numSources", ambi_roomsim_getNumSources(hAmbi));
    setParameterValue("numReceivers", ambi_roomsim_getNumReceivers(hAmbi));
    for(int i=0; i<ROOM_SIM_MAX_NUM_SOURCES; i++){
        setParameterValue("sourceX" + juce::String(i), ambi_roomsim_getSourceX(hAmbi, i));
        setParameterValue("sourceY" + juce::String(i), ambi_roomsim_getSourceY(hAmbi, i));
        setParameterValue("sourceZ" + juce::String(i), ambi_roomsim_getSourceZ(hAmbi, i));
    }
    for(int i=0; i<ROOM_SIM_MAX_NUM_RECEIVERS; i++){
        setParameterValue("receiverX" + juce::String(i), ambi_roomsim_getReceiverX(hAmbi, i));
        setParameterValue("receiverY" + juce::String(i), ambi_roomsim_getReceiverY(hAmbi, i));
        setParameterValue("receiverZ" + juce::String(i), ambi_roomsim_getReceiverZ(hAmbi, i));
    }
}

void PluginProcessor::setInternalStateUsingParameterValues()
{
    ambi_roomsim_setOutputOrder(hAmbi, getParameterChoice("outputOrder")+1);
    ambi_roomsim_setChOrder(hAmbi, getParameterChoice("channelOrder")+1);
    ambi_roomsim_setNormType(hAmbi, getParameterChoice("normType")+1);
    ambi_roomsim_setEnableIMSflag(hAmbi, getParameterBool("enableReflections"));
    ambi_roomsim_setMaxReflectionOrder(hAmbi, getParameterInt("maxReflectionOrder"));
    ambi_roomsim_setWallAbsCoeff(hAmbi, 0, 0, getParameterFloat("wallAbsCoeff_pX"));
    ambi_roomsim_setWallAbsCoeff(hAmbi, 0, 1, getParameterFloat("wallAbsCoeff_nX"));
    ambi_roomsim_setWallAbsCoeff(hAmbi, 1, 0, getParameterFloat("wallAbsCoeff_pY"));
    ambi_roomsim_setWallAbsCoeff(hAmbi, 1, 1, getParameterFloat("wallAbsCoeff_nY"));
    ambi_roomsim_setWallAbsCoeff(hAmbi, 2, 0, getParameterFloat("wallAbsCoeff_pZ"));
    ambi_roomsim_setWallAbsCoeff(hAmbi, 2, 1, getParameterFloat("wallAbsCoeff_nZ"));
    ambi_roomsim_setRoomDimX(hAmbi, getParameterFloat("roomX"));
    ambi_roomsim_setRoomDimY(hAmbi, getParameterFloat("roomY"));
    ambi_roomsim_setRoomDimZ(hAmbi, getParameterFloat("roomZ"));
    ambi_roomsim_setNumSources(hAmbi, getParameterInt("numSources"));
    ambi_roomsim_setNumReceivers(hAmbi, getParameterInt("numReceivers"));
    for(int i=0; i<ROOM_SIM_MAX_NUM_SOURCES; i++){
        ambi_roomsim_setSourceX(hAmbi, i, getParameterFloat("sourceX" + juce::String(i)));
        ambi_roomsim_setSourceY(hAmbi, i, getParameterFloat("sourceY" + juce::String(i)));
        ambi_roomsim_setSourceZ(hAmbi, i, getParameterFloat("sourceZ" + juce::String(i)));
    }
    for(int i=0; i<ROOM_SIM_MAX_NUM_RECEIVERS; i++){
        ambi_roomsim_setReceiverX(hAmbi, i, getParameterFloat("receiverX" + juce::String(i)));
        ambi_roomsim_setReceiverY(hAmbi, i, getParameterFloat("receiverY" + juce::String(i)));
        ambi_roomsim_setReceiverZ(hAmbi, i, getParameterFloat("receiverZ" + juce::String(i)));
    }
}

PluginProcessor::PluginProcessor()
    : PluginProcessorBase(
        BusesProperties()
            .withInput("Input", AudioChannelSet::discreteChannels(64), true)
            .withOutput("Output", AudioChannelSet::discreteChannels(64), true),
        createParameterLayout())
{
    ambi_roomsim_create(&hAmbi);
    addParameterListeners(this);
    
    trackFormatManager.registerBasicFormats();
    refreshWindow = true;
}

PluginProcessor::~PluginProcessor()
{
    removeParameterListeners(this);
    ambi_roomsim_destroy(&hAmbi);
}

void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    if(firstInit){
        /* Need to grab defaults */
        setParameterValuesUsingInternalState();
        firstInit = false;
    }
    nHostBlockSize = samplesPerBlock;
    nNumInputs =  jmin(getTotalNumInputChannels(), 256);
    nNumOutputs = jmin(getTotalNumOutputChannels(), 256);
    nSampleRate = (int)(sampleRate + 0.5);

    ambi_roomsim_init(hAmbi, nSampleRate);
    AudioProcessor::setLatencySamples(ambi_roomsim_getProcessingDelay());
    
    waveformCapture.prepare(nSampleRate);
    waveMixBuffer.setSize(1, samplesPerBlock, false, false, true);

    if(!blockAdapter)
        blockAdapter = std::make_unique<BlockAdapter>();
    blockAdapter->configure(ambi_roomsim_getFrameSize(), nNumInputs, nNumOutputs, nHostBlockSize);
}

void PluginProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    ScopedNoDenormals noDenormals;

    /* Host position is needed for both path automation and the waveform
       strip, so track it regardless of whether a path is enabled. */
    double t = 0.0;
    if (auto* ph = getPlayHead()) {
        if (auto pos = ph->getPosition()) {
            t = (getParameterChoice("pathTimeMode") == 0)
                    ? pos->getTimeInSeconds().orFallback(0.0)
                    : pos->getPpqPosition().orFallback(0.0);
        }
    }
    t += getParameterFloat("pathTimeOffset");
    currentHostTime.store(t);
    /* Remember the furthest position seen so newly created paths can
       default their end time to the track length. */
    noteHostTime(t);

    /* Clear stale audio when the transport rewinds/loops backwards. */
    if (t < lastWaveHostTime - 0.5)
        waveformCapture.reset();
    lastWaveHostTime = t;

    /* Mono-mix the input into the waveform capture ring (peak buckets). */
    {
        const juce::SpinLock::ScopedLockType sl(waveLock);
        waveMixBuffer.clear();
        int numCh = jmin(buffer.getNumChannels(), nNumInputs.load());
        for (int ch = 0; ch < numCh; ++ch)
            waveMixBuffer.addFrom(0, 0, buffer, ch, 0, buffer.getNumSamples(), 1.0f / (float)jmax(1, numCh));
        waveformCapture.addSamples(waveMixBuffer.getReadPointer(0), buffer.getNumSamples());
    }

    if (pathDirty.exchange(false)) {
        const juce::SpinLock::ScopedTryLockType tl(pathLock);
        if (tl.isLocked())
            pathSnapshot = pathBank;
    }

    int numSrc = ambi_roomsim_getNumSources(hAmbi);
    for (int i = 0; i < numSrc; ++i)
        applyPath(i, pathSnapshot.getSourcePath(i), t, "source");
    int numRec = ambi_roomsim_getNumReceivers(hAmbi);
    for (int i = 0; i < numRec; ++i)
        applyPath(i, pathSnapshot.getReceiverPath(i), t, "receiver");

    blockAdapter->processBlock (buffer, [this] (const float* const* inFrame, float* const* outFrame, int numIns, int numOuts, int frameSize) {
            ambi_roomsim_process(hAmbi, inFrame, outFrame, numIns, numOuts, frameSize);
        });
}

void PluginProcessor::applyPath(int index, const PathData& path, double t, const char* prefix)
{
    if (!path.enabled || path.keyframes.empty())
        return;

    float x=0, y=0, z=0;
    path.evaluate(t, x, y, z);

    juce::String idX = juce::String(prefix) + "X" + juce::String(index);
    juce::String idY = juce::String(prefix) + "Y" + juce::String(index);
    juce::String idZ = juce::String(prefix) + "Z" + juce::String(index);

    float rX = ambi_roomsim_getRoomDimX(hAmbi);
    float rY = ambi_roomsim_getRoomDimY(hAmbi);
    float rZ = ambi_roomsim_getRoomDimZ(hAmbi);
    x = juce::jlimit(0.0f, rX, x);
    y = juce::jlimit(0.0f, rY, y);
    z = juce::jlimit(0.0f, rZ, z);

    setApplyingFromAutomation(true);

    if (strcmp(prefix, "source") == 0) {
        ambi_roomsim_setSourceX(hAmbi, index, x);
        ambi_roomsim_setSourceY(hAmbi, index, y);
        ambi_roomsim_setSourceZ(hAmbi, index, z);
    } else {
        ambi_roomsim_setReceiverX(hAmbi, index, x);
        ambi_roomsim_setReceiverY(hAmbi, index, y);
        ambi_roomsim_setReceiverZ(hAmbi, index, z);
    }

    auto* pX = parameters.getParameter(idX);
    auto* pY = parameters.getParameter(idY);
    auto* pZ = parameters.getParameter(idZ);
    if (pX) pX->setValue(pX->convertTo0to1(x));
    if (pY) pY->setValue(pY->convertTo0to1(y));
    if (pZ) pZ->setValue(pZ->convertTo0to1(z));

    setApplyingFromAutomation(false);
}

AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (*this);
}

void PluginProcessor::getStateInformation (MemoryBlock& destData)
{
    juce::ValueTree state = parameters.copyState();
    /* Remove any PATHS children that may have leaked into the parameter tree
       from an earlier setStateInformation (see setStateInformation). */
    while (state.getChildWithName("PATHS").isValid())
        state.removeChild(state.getChildWithName("PATHS"), nullptr);

    /* The audio thread copies pathBank into pathSnapshot under pathLock, so
       the live bank must be serialized under the same lock to avoid a data
       race with processBlock() while the host is saving. */
    {
        const juce::SpinLock::ScopedLockType sl(pathLock);
        state.addChild(pathBank.toValueTree(), -1, nullptr);
        logPathState("save");
    }

    std::unique_ptr<juce::XmlElement> xmlState(state.createXml());
    xmlState->setTagName("AMBIROOMSIMPLUGINSETTINGS");
    xmlState->setAttribute("VersionCode", JucePlugin_VersionCode); // added since 0x10101

    /* Path to the loaded reference track, so the full-track waveform can be
       restored on the next plugin initialization. */
    {
        const juce::SpinLock::ScopedLockType sl(trackWaveLock);
        if (trackWaveform.valid)
            xmlState->setAttribute("TrackFilePath", trackWaveform.filePath);
    }

    /* Save */
    copyXmlToBinary(*xmlState, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Load */
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("AMBIROOMSIMPLUGINSETTINGS")){
        if(!xmlState->hasAttribute("VersionCode")){ // pre-0x10101
            for(int i=0; i<ambi_roomsim_getMaxNumSources(); i++){
                if(xmlState->hasAttribute("SourceX" + String(i)))
                    ambi_roomsim_setSourceX(hAmbi, i, (float)xmlState->getDoubleAttribute("SourceX" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceY" + String(i)))
                    ambi_roomsim_setSourceY(hAmbi, i, (float)xmlState->getDoubleAttribute("SourceY" + String(i), 0.0f));
                if(xmlState->hasAttribute("SourceZ" + String(i)))
                    ambi_roomsim_setSourceZ(hAmbi, i, (float)xmlState->getDoubleAttribute("SourceZ" + String(i), 0.0f));
            }
            for(int i=0; i<ambi_roomsim_getMaxNumReceivers(); i++){
                if(xmlState->hasAttribute("ReceiverX" + String(i)))
                    ambi_roomsim_setReceiverX(hAmbi, i, (float)xmlState->getDoubleAttribute("ReceiverX" + String(i), 0.0f));
                if(xmlState->hasAttribute("ReceiverY" + String(i)))
                    ambi_roomsim_setReceiverY(hAmbi, i, (float)xmlState->getDoubleAttribute("ReceiverY" + String(i), 0.0f));
                if(xmlState->hasAttribute("ReceiverZ" + String(i)))
                    ambi_roomsim_setReceiverZ(hAmbi, i, (float)xmlState->getDoubleAttribute("ReceiverZ" + String(i), 0.0f));
            }
            for(int i=0; i<3; i++)
                for(int j=0; j<2; j++)
                    if(xmlState->hasAttribute("wallAbsCoeff" + String(i) + "_" + String(j)))
                        ambi_roomsim_setWallAbsCoeff(hAmbi, i, j, (float)xmlState->getDoubleAttribute("wallAbsCoeff" + String(i) + "_" + String(j), 0.0f));
            if(xmlState->hasAttribute("RoomX"))
                ambi_roomsim_setRoomDimX(hAmbi, (float)xmlState->getDoubleAttribute("RoomX", 0.0f));
            if(xmlState->hasAttribute("RoomY"))
                ambi_roomsim_setRoomDimY(hAmbi, (float)xmlState->getDoubleAttribute("RoomY", 0.0f));
            if(xmlState->hasAttribute("RoomZ"))
                ambi_roomsim_setRoomDimZ(hAmbi, (float)xmlState->getDoubleAttribute("RoomZ", 0.0f));
            if(xmlState->hasAttribute("nSources"))
                ambi_roomsim_setNumSources(hAmbi, xmlState->getIntAttribute("nSources", 1));
            if(xmlState->hasAttribute("nReceivers"))
                ambi_roomsim_setNumReceivers(hAmbi, xmlState->getIntAttribute("nReceivers", 1));
            
            if(xmlState->hasAttribute("NORM"))
                ambi_roomsim_setNormType(hAmbi, xmlState->getIntAttribute("NORM", 1));
            if(xmlState->hasAttribute("CHORDER"))
                ambi_roomsim_setChOrder(hAmbi, xmlState->getIntAttribute("CHORDER", 1));
            if(xmlState->hasAttribute("OUT_ORDER"))
                ambi_roomsim_setOutputOrder(hAmbi, xmlState->getIntAttribute("OUT_ORDER", 1));
            
            setParameterValuesUsingInternalState();
        }
        else if (xmlState->getIntAttribute("VersionCode")>=0x10101){
            juce::ValueTree state = juce::ValueTree::fromXml(*xmlState);
            removeParameterListeners(this);
            /* IMPORTANT: do NOT let the PATHS node become a child of the
               parameter tree. Ardour may restore the plugin state multiple
               times (session load, undo, template, re-activation); if PATHS
               is left inside the parameter tree, every subsequent
               getStateInformation() would stack another PATHS node on top
               of the previous one, and setStateInformation would then read
               an OLDER stacked section instead of the latest path data.

               States saved by older builds may already contain several
               stacked PATHS nodes; pick the newest one (highest version)
               so the latest path data wins over stale sections. */
            juce::ValueTree incomingPaths;
            for (int i = 0; i < state.getNumChildren(); ++i) {
                auto child = state.getChild(i);
                if (!child.hasType("PATHS")) continue;
                if (!incomingPaths.isValid()
                    || (int)child.getProperty("version", 0)
                           > (int)incomingPaths.getProperty("version", 0))
                    incomingPaths = child;
            }
            state.removeChild(incomingPaths, nullptr);
            // Strip legacy dead params (pathEnable / pathLoop) removed in fix
            for (int i = state.getNumChildren(); i-- > 0; ) {
                auto c = state.getChild(i);
                if (c.hasProperty("id")) {
                    auto id = c.getProperty("id").toString();
                    if (id == "pathEnable" || id == "pathLoop")
                        state.removeChild(c, nullptr);
                }
            }
            parameters.replaceState(state);
            addParameterListeners(this);
            
            /* Many hosts will also trigger parameterChanged() for all parameters after calling setStateInformation() */
            /* However, some hosts do not. Therefore, it is better to ensure that the internal state is always up-to-date by calling: */
            setInternalStateUsingParameterValues();

            /* Restore path keyframe data */
            if (incomingPaths.isValid()) {
                bool applied = false;
                {
                    const juce::SpinLock::ScopedLockType sl(pathLock);
                    int incomingVersion = incomingPaths.getProperty("version", 0);
                    /* Guard against the host re-applying an OLDER snapshot
                       (Ardour undo/template/undo of a parameter change) over
                       newer in-memory edits. A fresh instance starts at
                       version 0, so any saved state still applies on load. */
                    if (incomingVersion >= pathBank.getStateVersion()) {
                        pathBank.fromValueTree(incomingPaths);
                        applied = true;
                    }
                    logPathState("restore");
                    if (const char* logPath = std::getenv("SPARTA_AMB_ROOMSIM_STATE_LOG"))
                        if (logPath[0] != '\0')
                            if (FILE* f = std::fopen(logPath, "a")) {
                                std::fprintf(f, "    incomingVersion=%d currentVersion=%d %s\n",
                                             incomingVersion, pathBank.getStateVersion(),
                                             applied ? "-> APPLIED" : "-> REJECTED (stale)");
                                std::fclose(f);
                            }
                }
                /* Refresh the audio-thread snapshot WITHOUT re-flagging the
                   host dirty right after a restore. */
                if (applied)
                    markPathDirty(false);
            }
        }

        /* Restore the reference track on initialization: kick off a decode
           of the saved file (on the background thread) so the full-track
           waveform is available before playback starts. */
        juce::String trackPath = xmlState->getStringAttribute("TrackFilePath", "");
        if (trackPath.isNotEmpty())
            loadTrackFile(juce::File(trackPath));
    
        ambi_roomsim_refreshParams(hAmbi);
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

PluginProcessor::TrackDecodeJob::TrackDecodeJob(PluginProcessor& p, const juce::File& f, int token)
    : ThreadPoolJob("trackWaveform"), processor(p), file(f), token(token) {}

juce::ThreadPoolJob::JobStatus PluginProcessor::TrackDecodeJob::runJob()
{
    processor.decodeTrack(file, token);
    return jobHasFinished;
}

void PluginProcessor::loadTrackFile(const juce::File& file)
{
    if (file.isDirectory() || !file.existsAsFile()) {
        clearTrackFile();
        return;
    }

    /* Skip restarting a decode when the same path was already requested and
       is either decoded or still in flight (hosts may restore the same state
       several times). */
    {
        const juce::SpinLock::ScopedLockType sl(trackWaveLock);
        if (trackWaveform.filePath == file.getFullPathName()
            && (trackWaveform.valid || trackLoading.load()))
            return;
        /* Remember the request so the UI can show it while decoding. */
        trackWaveform.filePath = file.getFullPathName();
    }

    const int token = ++loadToken;
    trackLoading.store(true);
    trackThreadPool.addJob(new TrackDecodeJob(*this, file, token), true);
}

void PluginProcessor::clearTrackFile()
{
    ++loadToken;   /* cancel any in-flight decode (its result becomes stale) */
    trackLoading.store(false);
    const juce::SpinLock::ScopedLockType sl(trackWaveLock);
    trackWaveform.clear();
}

void PluginProcessor::decodeTrack(const juce::File& file, int token)
{
    std::unique_ptr<juce::AudioFormatReader> reader(trackFormatManager.createReaderFor(file));
    if (reader == nullptr) {
        /* Only clear when we are still the current request. */
        const juce::SpinLock::ScopedLockType sl(trackWaveLock);
        if (token == loadToken) {
            trackWaveform.clear();
            trackLoading.store(false);
        }
        return;
    }

    TrackWaveform out;
    out.filePath = file.getFullPathName();
    out.sampleRate = reader->sampleRate;
    out.durationSeconds = (double)reader->lengthInSamples / reader->sampleRate;
    out.minPeaks.assign(WaveformCapture::numBuckets, 0.0f);
    out.maxPeaks.assign(WaveformCapture::numBuckets, 0.0f);

    /* Fold the whole file into a fixed number of min/max buckets without
       ever holding the decoded track in memory. */
    const int64 samplesPerBucket = jmax((int64)1, reader->lengthInSamples / WaveformCapture::numBuckets);
    juce::AudioBuffer<float> chunk(reader->numChannels, 4096);
    int64 pos = 0, bucket = 0;
    int into = 0;
    float cmin = 0.0f, cmax = 0.0f;
    while (pos < reader->lengthInSamples) {
        int n = (int)jmin((int64)chunk.getNumSamples(), reader->lengthInSamples - pos);
        reader->read(&chunk, 0, n, pos, true, true);
        for (int s = 0; s < n; ++s) {
            float m = 0.0f;
            for (int c = 0; c < chunk.getNumChannels(); ++c)
                m += chunk.getSample(c, s);
            m /= (float)chunk.getNumChannels();
            cmin = jmin(cmin, m);
            cmax = jmax(cmax, m);
            if (++into >= samplesPerBucket) {
                out.minPeaks[(size_t)bucket] = cmin;
                out.maxPeaks[(size_t)bucket] = cmax;
                cmin = 0.0f; cmax = 0.0f; into = 0;
                if (++bucket >= WaveformCapture::numBuckets)
                    bucket = WaveformCapture::numBuckets - 1;
            }
        }
        pos += n;
    }
    if (into > 0 && bucket < WaveformCapture::numBuckets) {
        out.minPeaks[(size_t)bucket] = cmin;
        out.maxPeaks[(size_t)bucket] = cmax;
    }
    out.valid = true;

    /* Swap in only if this is still the most recent request. */
    const juce::SpinLock::ScopedLockType sl(trackWaveLock);
    if (token == loadToken) {
        trackWaveform = out;
        trackLoading.store(false);
    }
}
