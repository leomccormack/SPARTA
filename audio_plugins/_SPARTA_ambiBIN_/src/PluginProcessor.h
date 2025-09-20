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
#include "../../resources/ParameterManager.h"
#include "ambi_bin.h"
#include <string.h>
#include <thread>
#include <atomic>
#include <functional>
#include <queue>

#define BUILD_VER_SUFFIX "" /* String to be added before the version name on the GUI (e.g. beta, alpha etc..) */
#define DEFAULT_OSC_PORT 9000

class ReinitManager : private juce::Thread
{
public:
    ReinitManager() : juce::Thread("ReinitWorker") {}

    void start() {
        startThread();
    }

    void stop() {
        signalThreadShouldExit();
        waitForThreadToExit(1000);
    }

    void requestReinit(void* handle) {
        std::lock_guard<std::mutex> lock(requestMutex);
        if (!reinitRequested) {
            this->handle = handle;
            reinitRequested = true;
        }
    }

    bool tryLockForAudio() {
        return reinitMutex.try_lock();
    }

    void unlockForAudio() {
        reinitMutex.unlock();
    }
    
    std::mutex reinitMutex;
    std::atomic<bool>* getReinitInProgressPtr() { return &reinitInProgress; }
    
private:
    void run() override {
        while (!threadShouldExit()) {
            bool shouldReinit = false;
            {
                std::lock_guard<std::mutex> lock(requestMutex);
                if (reinitRequested) {
                    shouldReinit = true;
                    reinitRequested = false;
                }
            }

            if (shouldReinit && handle != nullptr) {
                std::unique_lock<std::mutex> lock(reinitMutex);
                reinitInProgress.store(true, std::memory_order_release);
                ambi_bin_initCodec(handle);
                reinitInProgress.store(false, std::memory_order_release);
            }

            wait(10);
        }
    }

    std::mutex requestMutex;
    std::atomic<bool> reinitInProgress { false };
    bool reinitRequested = false;
    void* handle = nullptr;
};

class DeferredActionQueue
{
public:
    static constexpr int capacity = 128;

    void push(std::function<void()> fn) {
        int start1, size1, start2, size2;
        fifo.prepareToWrite(1, start1, size1, start2, size2);

        if (size1 > 0) {
            buffer[start1] = std::move(fn);
            fifo.finishedWrite(1);
        }
        else if (size2 > 0) {
            buffer[start2] = std::move(fn);
            fifo.finishedWrite(1);
        }
    }

    void drain() {
        int start1, size1, start2, size2;
        fifo.prepareToRead(capacity, start1, size1, start2, size2);

        for (int i = 0; i < size1; i++)
            buffer[start1 + i]();
        for (int i = 0; i < size2; i++)
            buffer[start2 + i]();

        fifo.finishedRead(size1 + size2);
    }

private:
    juce::AbstractFifo fifo { capacity };
    std::function<void()> buffer[capacity];
};


class PluginProcessor  : public AudioProcessor,
                         private OSCReceiver::Listener<OSCReceiver::RealtimeCallback>,
                         public juce::VST2ClientExtensions,
                         public ParameterManager
{
public:
    /* Get functions */
    void* getFXHandle() { return hAmbi; }
    int getCurrentBlockSize(){ return nHostBlockSize.load(); }
    int getCurrentNumInputs(){ return nNumInputs.load(); }
    int getCurrentNumOutputs(){  return nNumOutputs.load(); }
    
    /* VST CanDo */
    pointer_sized_int handleVstManufacturerSpecific (int32 /*index*/, pointer_sized_int /*value*/, void* /*ptr*/, float /*opt*/) override { return 0; }
    pointer_sized_int handleVstPluginCanDo (int32 /*index*/, pointer_sized_int /*value*/, void* ptr, float /*opt*/) override{
        auto text = (const char*) ptr;
        auto matches = [=](const char* s) { return strcmp (text, s) == 0; };
        if (matches ("wantsChannelCountNotifications"))
            return 1;
        return 0;
    }
    VST2ClientExtensions* getVST2ClientExtensions() override {return this;}
    
    /* OSC */
    void oscMessageReceived(const OSCMessage& message) override;
    void setOscPortID(int newID){
        osc.disconnect();
        osc_port_ID = newID;
        osc_connected = osc.connect(osc_port_ID);
    }
    int getOscPortID(){ return osc_port_ID; }
    bool getOscPortConnected(){ return osc_connected; }
    
    /* For handling real-time safe parameter updates and internal state reinitialisations */
    DeferredActionQueue updateQueue;
    ReinitManager reinitManager;
    
private:
    void* hAmbi;                      /* ambi_bin handle */
    std::atomic<int> nNumInputs;      /* current number of input channels */
    std::atomic<int> nNumOutputs;     /* current number of output channels */
    int nSampleRate;                  /* current host sample rate */
    std::atomic<int> nHostBlockSize;  /* typical host block size to expect, in samples */
    OSCReceiver osc;                  /* OSC receiver object */
    bool osc_connected;               /* flag. 0: not connected, 1: connect to "osc_port_ID"  */
    int osc_port_ID;                  /* port ID */
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    void setParameterValuesUsingInternalState();
    void setInternalStateUsingParameterValues();
    
    /***************************************************************************\
                                    JUCE Functions
    \***************************************************************************/
public:
    PluginProcessor();
    ~PluginProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
