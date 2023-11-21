/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <string.h>

#include "HeadtrackerReceiver.h"
#include "NatNetTools/NATUtils.h"

#define BUILD_VER_SUFFIX0 "alpha" /* String to be added before the version name on the GUI (beta, alpha etc..) */
#ifndef NDEBUG
#define BUILD_VER_SUFFIX (BUILD_VER_SUFFIX0 " (DEBUG)")
#else
#define BUILD_VER_SUFFIX BUILD_VER_SUFFIX0
#endif
#ifndef MIN
# define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
# define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif

#define ENABLE_DBG_OSC 0
#if ENABLE_DBG_OSC
#define DBG_OSC(prefix, osc_msg) JUCE_BLOCK_WITH_FORCED_SEMICOLON ( \
    juce::String tempDbgBuf; \
    tempDbgBuf << prefix << osc_msg.getAddressPattern().toString(); \
    for(int i = 0; i < osc_msg.size(); i++) { \
        OSCArgument arg = osc_msg[i]; \
        OSCType osc_type; \
        tempDbgBuf << " "; \
        if(arg.isInt32()) { \
            tempDbgBuf << arg.getInt32(); \
        } else if(arg.isFloat32()) { \
            tempDbgBuf << arg.getFloat32(); \
        } else if(arg.isString()) {  \
            tempDbgBuf << arg.getString(); \
        } else if(arg.isBlob()) { \
            tempDbgBuf << "<blob>"; \
        } else if(arg.isColour()) { \
            tempDbgBuf << "<colour>"; \
        } else { \
            tempDbgBuf << "<unknown>"; \
        } \
    } \
    juce::Logger::outputDebugString (tempDbgBuf); \
)
#else
#define DBG_OSC(prefix, osc_msg) 
#endif

enum {
    /* For the default VST GUI */
    k_receiverCoordX,
    k_receiverCoordY,
    k_receiverCoordZ,

    k_NumOfParameters,

    k_qw,
    k_qx,
    k_qy,
    k_qz
};

//==============================================================================
/**
*/
class PluginProcessor  : public AudioProcessor,
                         public VST2ClientExtensions
{
public:
    /* Set/Get functions */
    int getCurrentBlockSize(){ return nHostBlockSize; }
    int getCurrentNumInputs(){ return nNumInputs; }
    int getCurrentNumOutputs(){ return nNumOutputs; }
    
    /* For refreshing window during automation */
    bool refreshWindow;
    void setRefreshWindow(bool newState) { refreshWindow = newState; }
    bool getRefreshWindow() { return refreshWindow; }
    
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

    float getX();
    float getY();
    float getZ();
    float getYaw();
    float getPitch();
    float getRoll();

    void setUnmute(bool shouldUnmute);

    HeadtrackerReceiver headtrackerReceiver;

private:
    int nNumInputs;       /* current number of input channels */
    int nNumOutputs;      /* current number of output channels */
    int nSampleRate;      /* current host sample rate */
    int nHostBlockSize;   /* typical host block size to expect, in samples */
    float x;
    float y;
    float z;
    float yaw;
    float pitch;
    float roll;

    bool unmute;

    
/***************************************************************************\
                    JUCE Functions
\***************************************************************************/
public:
    //==============================================================================
    PluginProcessor();
    ~PluginProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    
    //==============================================================================
    int getNumParameters() override;
    float getParameter (int index) override;
    const String getParameterName (int index) override;
    const String getParameterText (int index) override;
    void setParameter (int index, float newValue) override;
    void setParameterRaw(int index, float newValue);

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};
