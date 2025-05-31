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

//#include "../JuceLibraryCode/JuceHeader.h"
#include <JuceHeader.h>
#include "ambi_bin.h"
#include <string.h>
#include <thread>
#define BUILD_VER_SUFFIX "" /* String to be added before the version name on the GUI (e.g. beta, alpha etc..) */
#define DEFAULT_OSC_PORT 9000

typedef enum _TIMERS{
    TIMER_PROCESSING_RELATED = 1,
    TIMER_GUI_RELATED
}TIMERS;

/* Parameter tags: for the default VST GUI */
enum {	 
    k_inputOrder,
    k_channelOrder,
    k_normType,
    k_decMethod,
    k_enableDiffuseMatching,
    k_enableMaxRE,
    k_enableRotation,
    k_useRollPitchYaw,
    k_yaw,
    k_pitch,
    k_roll,
    k_flipYaw,
    k_flipPitch,
    k_flipRoll,
    
	k_NumOfParameters
};

class PluginProcessor  : public AudioProcessor,
                         public MultiTimer,
                         private OSCReceiver::Listener<OSCReceiver::RealtimeCallback>,
                         public juce::VST2ClientExtensions
{
public:
    /* Get functions */
    void* getFXHandle() { return hAmbi; }
    int getCurrentBlockSize(){ return nHostBlockSize; }
    int getCurrentNumInputs(){ return nNumInputs; }
    int getCurrentNumOutputs(){  return nNumOutputs; }
    
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
    
private:
    void* hAmbi;             /* ambi_bin handle */
    int nNumInputs;          /* current number of input channels */
    int nNumOutputs;         /* current number of output channels */
    int nSampleRate;         /* current host sample rate */
    int nHostBlockSize;      /* typical host block size to expect, in samples */
    OSCReceiver osc;         /* OSC receiver object */
    bool osc_connected;      /* flag. 0: not connected, 1: connect to "osc_port_ID"  */
    int osc_port_ID;         /* port ID */
    
    void timerCallback(int timerID) override {
        switch(timerID){
            case TIMER_PROCESSING_RELATED:
                /* reinitialise codec if needed */
                if(ambi_bin_getCodecStatus(hAmbi) == CODEC_STATUS_NOT_INITIALISED){
                    try{
                        std::thread threadInit(ambi_bin_initCodec, hAmbi);
                        threadInit.detach();
                    } catch (const std::exception& exception) {
                        std::cout << "Could not create thread" << exception.what() << std::endl;
                    }
                }
                break;
                
            case TIMER_GUI_RELATED:
                /* handled in PluginEditor; */
                break;
        }
    }
    
    /***************************************************************************\
                                    JUCE Functions
    \***************************************************************************/
public:
    PluginProcessor();
    ~PluginProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const String getName() const override;
    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;
    bool isParameterAutomatable (int index) const override;
    const String getParameterName (int index) override;
    const String getParameterText (int index) override;
    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const String getProgramName(int index) override;
	bool isInputChannelStereoPair (int index) const override;
	bool isOutputChannelStereoPair(int index) const override;
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
	void changeProgramName(int index, const String& newName) override;
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
