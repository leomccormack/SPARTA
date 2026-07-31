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
#include <thread>
#include <atomic>
#define CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS 1
#include "../../resources/ConfigurationHelper.h"

#define BUILD_VER_SUFFIX "" /* String to be added before the version name on the GUI (e.g. beta, alpha etc..) */
#ifndef MIN
# define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
# define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif

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
    void markPathDirty() { pathDirty = true; }
    double getCurrentHostTime() const { return currentHostTime; }
    
    /* Hide internal setParameterValue when automation is pushing (to suppress parameterChanged re-entry) */
    void setApplyingFromAutomation(bool v) { applyingFromAutomation.store(v); }
    bool isApplyingFromAutomation() const { return applyingFromAutomation.load(); }
    
private:
    void* hAmbi;                       /* ambi_roomsim handle */
    bool refreshWindow;

    /* Path automation members */
    PathBank pathBank;
    juce::SpinLock pathLock;
    std::atomic<bool> pathDirty{false};
    PathBank pathSnapshot;
    mutable std::atomic<double> currentHostTime{0.0};
    std::atomic<bool> applyingFromAutomation{false};
    void applyPath(int index, const PathData& path, double t, const char* prefix);
    
    /* For syncing parameter values between the JUCE parameter tree and the internal DSP object */
    void setParameterValuesUsingInternalState();
    void setInternalStateUsingParameterValues();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
