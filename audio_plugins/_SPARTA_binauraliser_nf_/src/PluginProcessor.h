/*
 ==============================================================================
 
 This file is part of SPARTA; a suite of spatial audio plug-ins.
 Copyright (c) 2018 - Michael McCrea, Leo McCormack.
 
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
#include <binauraliser_nf.h>
#include <thread>
#include <atomic>
#define CONFIGURATIONHELPER_ENABLE_GENERICLAYOUT_METHODS 1
#include "../../resources/ConfigurationHelper.h"

#define BUILD_VER_SUFFIX "" /* String to be added before the version name on the GUI (e.g. beta, alpha etc..) */
#define DEFAULT_OSC_PORT 9000
#ifndef MIN
# define MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef MAX
# define MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif

class PluginProcessor  : public AudioProcessor,
                         public Timer,
                         private OSCReceiver::Listener<OSCReceiver::RealtimeCallback>,
                         public VST2ClientExtensions,
                         public ParameterManager
{
public:
    /* Get functions */
    void* getFXHandle() { return hBin; } 
    int getCurrentBlockSize(){ return nHostBlockSize; }
    int getCurrentNumInputs(){ return nNumInputs; }
    int getCurrentNumOutputs(){ return nNumOutputs; }
    bool getBusHasLFE() { return inputBusHasLFE; }

    /* For refreshing window during automation */
    bool refreshWindow;
    void setRefreshWindow(bool newState) { refreshWindow = newState; }
    bool getRefreshWindow() { return refreshWindow; }
    
    /* JSON */
    void saveConfigurationToFile (File destination);
    void loadConfiguration (const File& presetFile);
    void setLastDir(File newLastDir){ lastDir = newLastDir; }
    File getLastDir() {return lastDir;}
    
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
    void checkAndUpdateOscStatus(){
        /* Free up the port if osc is connected and rotation is disabled */
        if(!binauraliser_getEnableRotation(hBin) && osc_connected){
            osc_connected = false;
            osc.disconnect();
        }
        /* Try to connect to port if rotation is enabled */
        else if(binauraliser_getEnableRotation(hBin) && !osc_connected)
            osc_connected = osc.connect(osc_port_ID);
    }
    void setOscPortID(int newID){
        osc_port_ID = newID;
        if(binauraliser_getEnableRotation(hBin)){
            if(osc_connected)
                osc.disconnect();
            osc_connected = osc.connect(osc_port_ID);
        }
    }
    int getOscPortID(){ return osc_port_ID; }
    bool getOscPortConnected(){ return osc_connected; }
    float nfThresh;       /* near field distance threshold, below which distance values are clipped */
    float ffThresh;       /* far field distance threshold where near field filters disengage */
    float ffHeadroom;     /* headroom above the far field threshold to easily disable with the UI */
    float upperDistRange; /* ffThresh * ffHeadroom */

    
private:
    void* hBin;                        /* binauraliser handle */
    std::atomic<int> nNumInputs;       /* current number of input channels */
    std::atomic<int> nNumOutputs;      /* current number of output channels */
    int nSampleRate;                   /* current host sample rate */
    std::atomic<int> nHostBlockSize;   /* typical host block size to expect, in samples */
    File lastDir;
    ValueTree sources {"Sources"};
    OSCReceiver osc;
    bool osc_connected = false;
    int osc_port_ID = DEFAULT_OSC_PORT;
    std::atomic<bool> inputBusHasLFE = false;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    void setParameterValuesUsingInternalState();
    void setInternalStateUsingParameterValues();

    void timerCallback() override
    {
        /* reinitialise codec if needed */
        if(binauraliser_getCodecStatus(hBin) == CODEC_STATUS_NOT_INITIALISED){
            try{
                std::thread threadInit(binauraliserNF_initCodec, hBin);
                threadInit.detach();
            } catch (const std::exception& exception) {
                std::cout << "Could not create thread" << exception.what() << std::endl;
            }
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
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void processBlockBypassed (juce::AudioBuffer<float>&, juce::MidiBuffer&) override {}
    
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
