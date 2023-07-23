/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "tvconv.h"
#include "rotator.h"
#include <string.h>
#define BUILD_VER_SUFFIX "alpha" /* String to be added before the version name on the GUI (beta, alpha etc..) */
#ifndef MIN
# define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
# define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif

#define DEFAULT_OSC_PORT 9000

enum {
    /* For the default VST GUI */
    k_receiverCoordX,
    k_receiverCoordY,
    k_receiverCoordZ,

    k_qw,
    k_qx,
    k_qy,
    k_qz,

	k_yaw,
	k_pitch,
	k_roll,

    k_room_size_x,
    k_room_size_y,
    k_room_size_z,

	k_param_workaround, // needed to ensure that when a parameter is set by the host, the "setParameter()" method is called

	k_NumOfParameters
};
//==============================================================================
/**
*/
class PluginProcessor  : public AudioProcessor,
                         private OSCReceiver::Listener<OSCReceiver::RealtimeCallback>,
                         public VSTCallbackHandler
{
public:
    /* Set/Get functions */
    void* getFXHandle() { return hTVCnv; }
    void* getFXHandle_rot() { return hRot; }
    int getCurrentBlockSize(){ return nHostBlockSize; }
    int getCurrentNumInputs(){ return nNumInputs; }
    int getCurrentNumOutputs(){ return nNumOutputs; }
    void setEnableRotation(bool newState){ enable_rotation = newState; }
    bool getEnableRotation(){ return enable_rotation; }
    
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

    /* OSC */
    void oscMessageReceived(const OSCMessage& message) override;
    void setOscPortID(int newID) {
        osc.disconnect();
        osc_port_ID = newID;
        osc_connected = osc.connect(osc_port_ID);
    }
    int getOscPortID() { return osc_port_ID; }
    bool getOscPortConnected() { return osc_connected; }
    
    
private:
    void* hTVCnv;         /* tvconv handle */
    void* hRot;           /* rotator handle */
    int nNumInputs;       /* current number of input channels */
    int nNumOutputs;      /* current number of output channels */
    int nSampleRate;      /* current host sample rate */
    int nHostBlockSize;   /* typical host block size to expect, in samples */
    OSCReceiver osc;
    bool osc_connected;
    int osc_port_ID;
    bool enable_rotation;
    
    
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
    
	juce::AudioParameterFloat* receiver_coordinate_x;
	juce::AudioParameterFloat* receiver_coordinate_y;
	juce::AudioParameterFloat* receiver_coordinate_z;
	juce::AudioParameterFloat* receiver_quaternion_w;
	juce::AudioParameterFloat* receiver_quaternion_x;
	juce::AudioParameterFloat* receiver_quaternion_y;
	juce::AudioParameterFloat* receiver_quaternion_z;
	juce::AudioParameterFloat* receiver_yaw;
	juce::AudioParameterFloat* receiver_pitch;
	juce::AudioParameterFloat* receiver_roll;
	juce::AudioParameterFloat* room_size_x;
	juce::AudioParameterFloat* room_size_y;
	juce::AudioParameterFloat* room_size_z;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)

	};