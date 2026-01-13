/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2025 - Janani Fernandez.
 
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

#pragma once

#include "ParameterManager.h"

class BlockAdapter
{
public:
    BlockAdapter() = default;

    void configure(int frameSize, int numInputs, int numOutputs, int hostBlockSize) {
        const bool paramsChanged = frameSize  != mFrameSize || numInputs  != mNumInputs || numOutputs != mNumOutputs || hostBlockSize != mHostBlockSize;
        mFrameSize  = frameSize;
        mNumInputs  = numInputs;
        mNumOutputs = numOutputs;
        mHostBlockSize = hostBlockSize;
        usingLowDelay = (mHostBlockSize % mFrameSize == 0); /* in this case we can skip the FIFO buffering, since block size is a multiple of the processing framesize */

        jassert(mFrameSize > 0);
        jassert(mNumInputs >= 0);
        jassert(mNumOutputs >= 0);
        jassert(mHostBlockSize >= 0);
        
        if(!usingLowDelay) {
            if(paramsChanged || inBuffers.size() != (size_t)(mNumInputs * mFrameSize) || inBuffersPtrs.size() != (size_t)(mNumInputs)) {
                inBuffers.resize(mNumInputs * mFrameSize);
                inBuffersPtrs.resize(mNumInputs);
                for(int ch = 0; ch < mNumInputs; ch++)
                    inBuffersPtrs[ch] = &inBuffers[ch * mFrameSize];
            }
            if(paramsChanged || outBuffers.size() != (size_t)(mNumOutputs * mFrameSize) || outBuffersPtrs.size() != (size_t)(mNumOutputs)) {
                outBuffers.resize(mNumOutputs * mFrameSize);
                outBuffersPtrs.resize(mNumOutputs);
                for(int ch = 0; ch < mNumOutputs; ch++)
                    outBuffersPtrs[ch] = &outBuffers[ch * mFrameSize];
            }
        }
        else{
            inBuffers.clear();
            outBuffers.clear();
            inBuffersPtrs.clear();
            outBuffersPtrs.clear();
        }

        reset();
    }

    inline void reset() noexcept
    {
        inPos = outPos = availableOut = 0;
        if(!inBuffers.empty())
            std::fill(inBuffers.begin(), inBuffers.end(), 0.0f);
        if(!outBuffers.empty())
            std::fill(outBuffers.begin(), outBuffers.end(), 0.0f);
    }

    inline bool isUsingLowDelay() const noexcept { return usingLowDelay; }

    template <typename ProcessFn>
    void processBlock(juce::AudioBuffer<float>& buffer, const ProcessFn& processFrame) noexcept {
        if(usingLowDelay)
            processBlockInternalLowDelay(buffer, processFrame);
        else
            processBlockInternal(buffer, processFrame);
    }

private:
    template <typename ProcessFn>
    inline void processBlockInternalLowDelay(juce::AudioBuffer<float>& buffer, const ProcessFn& processFrame) noexcept {
        const int numSamples = buffer.getNumSamples();
        float* const* bufferData = buffer.getArrayOfWritePointers();
        float* pFrameData[256];
        
        if(numSamples % mFrameSize == 0){ /* divisible by frame size */
            for (int frame = 0; frame < numSamples/mFrameSize; frame++) {
                for (int ch = 0; ch < jmin(buffer.getNumChannels(), 256); ch++)
                    pFrameData[ch] = &bufferData[ch][frame*mFrameSize];

                /* perform processing */
                processFrame(pFrameData, pFrameData, mNumInputs, mNumOutputs, mFrameSize);
            }
        }
        else {
            buffer.clear();
        }
    }

    template <typename ProcessFn>
    inline void processBlockInternal(juce::AudioBuffer<float>& buffer, const ProcessFn& processFrame) noexcept {
        const int numSamples = buffer.getNumSamples();
        const float* const* inHost = buffer.getArrayOfReadPointers();
        float* const* outHost = buffer.getArrayOfWritePointers();
        const int hostChans = buffer.getNumChannels();
        
        jassert(hostChans >= mNumInputs);
        jassert(hostChans >= mNumOutputs);
        
        for(int n = 0; n < numSamples; n++) {
            for(int ch = 0; ch < mNumInputs; ch++)
                inBuffersPtrs[ch][inPos] = inHost[ch][n];
            inPos++;

            if(inPos == mFrameSize){
                processFrame(inBuffersPtrs.data(), outBuffersPtrs.data(), mNumInputs, mNumOutputs, mFrameSize);
                inPos = 0;
                outPos = 0;
                availableOut = mFrameSize;
            }

            if(availableOut > 0){
                for(int ch = 0; ch < mNumOutputs; ch++)
                    outHost[ch][n] = outBuffersPtrs[ch][outPos];
                outPos++;
                availableOut--;
            }
            else {
                for(int ch = 0; ch < mNumOutputs; ch++)
                    outHost[ch][n] = 0.0f;
            }
        }
        
        for(int ch=mNumOutputs; ch<hostChans; ch++){
            memset(outHost[ch], 0, numSamples*sizeof(float));
        }
    }

private:
    int mFrameSize      = 0;
    int mNumInputs      = 0;
    int mNumOutputs     = 0;
    int mHostBlockSize  = 0;
    bool usingLowDelay  = false;

    int inPos = 0;
    int outPos = 0;
    int availableOut = 0;

    std::vector<float> inBuffers;
    std::vector<float> outBuffers;
    std::vector<float*> inBuffersPtrs;
    std::vector<float*> outBuffersPtrs;
};


class PluginProcessorBase  : public juce::AudioProcessor,
                             public juce::VST2ClientExtensions,
                             public ParameterManager,
                             public juce::AudioProcessorValueTreeState::Listener
{
public:
    explicit PluginProcessorBase(const BusesProperties& buses, juce::AudioProcessorValueTreeState::ParameterLayout layout)
        : AudioProcessor(buses), ParameterManager(*this, std::move(layout)) {}
    ~PluginProcessorBase() override {};

    int getCurrentBlockSize() const { return nHostBlockSize.load(); }
    int getCurrentNumInputs() const { return nNumInputs.load(); }
    int getCurrentNumOutputs() const { return nNumOutputs.load(); }

    /* These standard JUCE functions can be optionally overriden in the derived class */
    void processBlockBypassed(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) override {
        juce::AudioProcessor::processBlockBypassed(buffer, midi);
    }
    bool hasEditor() const override                  { return true; }
    const juce::String getName() const override      { return JucePlugin_Name; }
    bool acceptsMidi() const override                { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const override               { return JucePlugin_ProducesMidiOutput; }
    double getTailLengthSeconds() const override     { return 0.0; }
    int getNumPrograms() override                    { return 1; }
    int getCurrentProgram() override                 { return 0; }
    void setCurrentProgram (int /*index*/) override  {}
    const juce::String getProgramName(int) override  { return {}; }
    void changeProgramName(int /*index*/, const juce::String& /*newName*/) override {}
    
    /* VST CanDo */
    pointer_sized_int handleVstManufacturerSpecific (int32, pointer_sized_int, void*, float) override {
        return 0;
    }
    pointer_sized_int handleVstPluginCanDo (int32, pointer_sized_int, void* ptr, float) override {
        auto text = static_cast<const char*>(ptr);
        if (strcmp(text, "wantsChannelCountNotifications") == 0)
            return 1;
        return 0;
    }
    VST2ClientExtensions* getVST2ClientExtensions() override { return this; }
    
protected:
    bool firstInit = true;
    std::atomic<int> nNumInputs {0};
    std::atomic<int> nNumOutputs {0};
    int nSampleRate = 0;
    std::atomic<int> nHostBlockSize {0};
    std::unique_ptr<BlockAdapter> blockAdapter;

    /* These functions must be implemented in the derived class */
    virtual void parameterChanged(const juce::String&, float) override = 0;
    virtual void prepareToPlay(double, int) override = 0;
    virtual void releaseResources() override = 0;
    virtual void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override = 0;
    virtual void getStateInformation(juce::MemoryBlock& destData) override = 0;
    virtual void setStateInformation(const void* data, int sizeInBytes) override = 0;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessorBase)
};


