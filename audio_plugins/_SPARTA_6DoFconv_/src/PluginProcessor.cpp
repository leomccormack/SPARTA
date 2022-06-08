/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

// file-level pointer to the PluginProcessor - there shouldn't be more than one, right?...
// ugly, but NatNet callbacks need to be C-style function pointers and that doesn't really work with C++ instance methods
static PluginProcessor* thePluginProcessor = nullptr;

//==============================================================================
PluginProcessor::PluginProcessor() :
    AudioProcessor(BusesProperties()
        .withInput("Input", AudioChannelSet::discreteChannels(64), true)
        .withOutput("Output", AudioChannelSet::discreteChannels(64), true))
{
    jassert(thePluginProcessor == nullptr);
    thePluginProcessor = this;

    nSampleRate = 48000;
    nHostBlockSize = -1;
    tvconv_create(&hTVCnv);
    
    // (@todo) to be automated
    enable_rotation = true;
    
    rotator_create(&hRot);

    // (@todo) needs to be made adaptive 
    rotator_setOrder(hRot, 4);

    refreshWindow = true;

    /* specify here on which UDP port number to receive incoming OSC messages */
    osc_port_ID = DEFAULT_OSC_PORT;
    osc_connected = osc.connect(osc_port_ID);
    /* tell the component to listen for OSC messages */
    osc.addListener(this);

    if (osc_connected)
    {
        DBG("osc connected");
    }
    else
    {
        DBG("osc not connected");
    }
    
}

PluginProcessor::~PluginProcessor()
{
    osc.disconnect();
    osc.removeListener(this);
    tvconv_destroy(&hTVCnv);
}

//==============================================================================


void PluginProcessor::oscMessageReceived(const OSCMessage& message)
{
    DBG_OSC("osc received: ", message);

    if (message.size() == 3 && message.getAddressPattern().toString().compare("xyz")) {
        if (message[0].isFloat32())
            setParameterRaw(0, message[0].getFloat32());
        if (message[1].isFloat32())
            setParameterRaw(1, message[1].getFloat32());
        if (message[2].isFloat32())
            setParameterRaw(2, message[2].getFloat32());
        return;
    }
    
    else if (message.size() == 7 && message.getAddressPattern().toString().compare("xyzquat")) {
        if (message[0].isFloat32())
            setParameterRaw(0, message[0].getFloat32());
        if (message[1].isFloat32())
            setParameterRaw(1, message[1].getFloat32());
        if (message[2].isFloat32())
            setParameterRaw(2, message[2].getFloat32());
        if (message[3].isFloat32())
            rotator_setQuaternionW(hRot, message[3].getFloat32());
        if (message[4].isFloat32())
            rotator_setQuaternionX(hRot, message[4].getFloat32());
        if (message[5].isFloat32())
            rotator_setQuaternionY(hRot, message[5].getFloat32());
        if (message[6].isFloat32())
            rotator_setQuaternionY(hRot, message[6].getFloat32());
        return;
    }

    else if (message.size() == 6 && message.getAddressPattern().toString().compare("xyzypr")) {
        if (message[0].isFloat32())
            setParameterRaw(0, message[0].getFloat32());
        if (message[1].isFloat32())
            setParameterRaw(1, message[1].getFloat32());
        if (message[2].isFloat32())
            setParameterRaw(2, message[2].getFloat32());
        if (message[3].isFloat32())
            rotator_setYaw(hRot, message[3].getFloat32());
        if (message[4].isFloat32())
            rotator_setPitch(hRot, message[4].getFloat32());
        if (message[5].isFloat32())
            rotator_setRoll(hRot, message[5].getFloat32());

        return;
    }
}

const juce::String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

void PluginProcessor::setCurrentProgram (int /*index*/)
{
}

const juce::String PluginProcessor::getProgramName (int /*index*/)
{
    return {};
}

void PluginProcessor::changeProgramName (int /*index*/, const juce::String& /*newName*/)
{
}

//==============================================================================
int PluginProcessor::getNumParameters()
{
    return k_NumOfParameters;
}

float PluginProcessor::getParameter(int index)
{
    if (index < 3) {
        if (tvconv_getMaxDimension(hTVCnv, index) > tvconv_getMinDimension(hTVCnv, index)){
            return (tvconv_getTargetPosition(hTVCnv, index)-tvconv_getMinDimension(hTVCnv, index))/
                (tvconv_getMaxDimension(hTVCnv, index)-tvconv_getMinDimension(hTVCnv, index));
        }
    }
    return 0.0f;
}

const String PluginProcessor::getParameterName (int index)
{
    switch (index) {
        case k_receiverCoordX: return "receiver_coordinate_x";
        case k_receiverCoordY: return "receiver_coordinate_y";
        case k_receiverCoordZ: return "receiver_coordinate_z";
        default: return "NULL";
    }
}

const String PluginProcessor::getParameterText(int index)
{
    if (index < 3) {
        return String(tvconv_getTargetPosition(hTVCnv, index));
    }
    else return "NULL";
}

void PluginProcessor::setParameter (int index, float newValue)
{
    DBG("param set");
    float newValueScaled;
    if (index < 3) {
        newValueScaled = newValue *
        (tvconv_getMaxDimension(hTVCnv, index) - tvconv_getMinDimension(hTVCnv, index)) +
        tvconv_getMinDimension(hTVCnv, index);
        if (newValueScaled != tvconv_getTargetPosition(hTVCnv, index)){
            tvconv_setTargetPosition(hTVCnv, newValueScaled, index);
            refreshWindow = true;
        }
    }
}

void PluginProcessor::setParameterRaw(int index, float newValue)
{
    if (index < 3) {
        if (newValue != tvconv_getTargetPosition(hTVCnv, index)) {
            tvconv_setTargetPosition(hTVCnv, newValue, index);
            refreshWindow = true;
        }
    }
}

//==============================================================================
void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    nHostBlockSize = samplesPerBlock;
    nNumInputs =  getTotalNumInputChannels();
    nNumOutputs = getTotalNumOutputChannels();
    nSampleRate = (int)(sampleRate + 0.5);
    //isPlaying = false;

    tvconv_init(hTVCnv, nSampleRate, nHostBlockSize);

    int numConvolverOutputChannels = tvconv_getNumOutputChannels(hTVCnv);

    if (numConvolverOutputChannels) {
        
        int sh_order = sqrt(numConvolverOutputChannels) - 1;
        
        DBG("order");
        DBG(String(sh_order));
        rotator_setOrder(hRot, sh_order);
    }

    AudioProcessor::setLatencySamples(tvconv_getProcessingDelay(hTVCnv));
    rotator_init(hRot, (float)sampleRate);
}

void PluginProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PluginProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    int nCurrentBlockSize = nHostBlockSize = buffer.getNumSamples();
    nNumInputs = jmin(getTotalNumInputChannels(), buffer.getNumChannels());
    nNumOutputs = jmin(getTotalNumOutputChannels(), buffer.getNumChannels());
    float** bufferData = buffer.getArrayOfWritePointers();

    tvconv_process(hTVCnv, bufferData, bufferData, nNumInputs, nNumOutputs, nCurrentBlockSize);

    if (enable_rotation) {
        float* pFrameData[MAX_NUM_CHANNELS];
        int frameSize = rotator_getFrameSize();

        if ((nCurrentBlockSize % frameSize == 0)) { /* divisible by frame size */
            for (int frame = 0; frame < nCurrentBlockSize / frameSize; frame++) {
                for (int ch = 0; ch < buffer.getNumChannels(); ch++)
                    pFrameData[ch] = &bufferData[ch][frame * frameSize];

                /* perform processing */
                rotator_process(hRot, pFrameData, pFrameData, nNumOutputs, nNumOutputs, frameSize);
            }
        }
        else
            buffer.clear();
    }

}

//==============================================================================
bool PluginProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (this);
}

//==============================================================================
void PluginProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    /* Create an outer XML element.. */
    XmlElement xml("TVCONVAUDIOPLUGINSETTINGS");
    xml.setAttribute("LastSofaFilePath", tvconv_getSofaFilePath(hTVCnv));
    xml.setAttribute("ReceiverX", tvconv_getTargetPosition(hTVCnv, 0));
    xml.setAttribute("ReceiverY", tvconv_getTargetPosition(hTVCnv, 1));
    xml.setAttribute("ReceiverZ", tvconv_getTargetPosition(hTVCnv, 2));

    xml.setAttribute("OSC_PORT", osc_port_ID);

    copyXmlToBinary(xml, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    /* This getXmlFromBinary() function retrieves XML from the binary blob */
        std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

        if (xmlState != nullptr) {
            /* make sure that it's actually the correct XML object */
            if (xmlState->hasTagName("TVCONVAUDIOPLUGINSETTINGS")) {
     
                if(xmlState->hasAttribute("LastSofaFilePath")){
                    String directory = xmlState->getStringAttribute("LastSofaFilePath", "no_file");
                    const char* new_cstring = (const char*)directory.toUTF8();
                    tvconv_setSofaFilePath(hTVCnv, new_cstring);
                }
                if (xmlState->hasAttribute("ReceiverX")){
                    tvconv_setTargetPosition(hTVCnv,
                        (float)xmlState->getDoubleAttribute("ReceiverX"), 0);
                }
                if (xmlState->hasAttribute("ReceiverY")){
                    tvconv_setTargetPosition(hTVCnv,
                        (float)xmlState->getDoubleAttribute("ReceiverY"), 1);
                }
                if (xmlState->hasAttribute("ReceiverZ")){
                    tvconv_setTargetPosition(hTVCnv,
                        (float)xmlState->getDoubleAttribute("ReceiverZ"), 2);
                }

                if (xmlState->hasAttribute("OSC_PORT")) {
                    osc_port_ID = xmlState->getIntAttribute("OSC_PORT", DEFAULT_OSC_PORT);
                    osc.connect(osc_port_ID);
                }

                if (xmlState->hasAttribute("TBRotFlag")) {
                    DBG("flag set");
                }
                
                tvconv_refreshParams(hTVCnv);
            }
        }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

// NatNet

// Initialize the NatNet client with client and server IP addresses.
void PluginProcessor::connectNatNet(const char* myIpAddress, const char* serverIpAddress, ConnectionType connType)
{
    unsigned char ver[4];
    NatNet_GetVersion(ver);

    // Set callback handlers
    // Callback for NatNet messages.

    // typedef void (NATNET_CALLCONV* NatNetLogCallback)( Verbosity level, const char* message );

    sNatNetClientConnectParams connectParams;
    connectParams.connectionType = connType;
    connectParams.localAddress = myIpAddress;
    connectParams.serverAddress = serverIpAddress;
    natNetClient.Disconnect();
    int retCode = natNetClient.Connect(connectParams);
    if (retCode != ErrorCode_OK) {
        //Unable to connect to server.
        sendNatNetConnMessage("natnet_connect_error");
        return;
    } else {
        // Print server info
        sServerDescription ServerDescription;
        memset(&ServerDescription, 0, sizeof(ServerDescription));
        natNetClient.GetServerDescription(&ServerDescription);
        if (!ServerDescription.HostPresent)
        {
            //Unable to connect to server. Host not present
            sendNatNetConnMessage("natnet_connect_error");
            return;
        }
    }

    // Retrieve RigidBody description from server
    sDataDescriptions* pDataDefs = NULL;
    retCode = natNetClient.GetDataDescriptionList(&pDataDefs);
    if (retCode != ErrorCode_OK || parseRigidBodyDescription(pDataDefs) == false)
    {
        //Unable to retrieve RigidBody description
        //return false;
        // TODO: report
        return;
    }
    NatNet_FreeDescriptions(pDataDefs);
    pDataDefs = NULL;

    // example of NatNet general message passing. Set units to millimeters
    // and get the multiplicative conversion factor in the response.
    void* response;
    int nBytes;
    retCode = natNetClient.SendMessageAndWait("UnitsToMillimeters", &response, &nBytes);
    if (retCode == ErrorCode_OK)
    {
        natNetUnitConversion = *(float*)response;
    }

    retCode = natNetClient.SendMessageAndWait("UpAxis", &response, &nBytes);
    if (retCode == ErrorCode_OK)
    {
        natNetUpAxis = *(long*)response;
    }

    sendNatNetConnMessage("natnet_connect");

    NatNet_SetLogCallback(staticHandleNatNetMessage);
    // this function will receive data from the server
    natNetClient.SetFrameReceivedCallback(staticHandleNatNetData);

    return;
}

void PluginProcessor::disconnectNatNet() {
    natNetClient.Disconnect();
    sendNatNetConnMessage("natnet_disconnect");
}

void PluginProcessor::addNatNetConnListener(ActionListener* listener) {
    natNetConnBroadcaster.addActionListener(listener);
}

void PluginProcessor::removeNatNetConnListener(ActionListener* listener) {
    natNetConnBroadcaster.removeActionListener(listener);
}

void PluginProcessor::sendNatNetConnMessage(const String& message) {
    natNetConnBroadcaster.sendActionMessage(message);
}

void PluginProcessor::handleNatNetData(sFrameOfMocapData* data, void* pUserData) {
    DBG("handleNatNetData()");
}

void PluginProcessor::handleNatNetMessage(Verbosity msgType, const char* msg) {
    DBG("handleNatNetMessage()");
}

void NATNET_CALLCONV PluginProcessor::staticHandleNatNetData(sFrameOfMocapData* data, void* pUserData) {
    jassert(thePluginProcessor != nullptr);
    thePluginProcessor->handleNatNetData(data, pUserData);
}

void NATNET_CALLCONV PluginProcessor::staticHandleNatNetMessage(Verbosity msgType, const char* msg) {
    jassert(thePluginProcessor != nullptr);
    thePluginProcessor->handleNatNetMessage(msgType, msg);
}

bool PluginProcessor::parseRigidBodyDescription(sDataDescriptions* pDataDefs) {
    /*
    mapIDToName.clear();

    if (pDataDefs == NULL || pDataDefs->nDataDescriptions <= 0)
        return false;

    // preserve a "RigidBody ID to Rigid Body Name" mapping, which we can lookup during data streaming
    int iSkel = 0;
    for (int i = 0, j = 0; i < pDataDefs->nDataDescriptions; i++)
    {
        if (pDataDefs->arrDataDescriptions[i].type == Descriptor_RigidBody)
        {
            sRigidBodyDescription* pRB = pDataDefs->arrDataDescriptions[i].Data.RigidBodyDescription;
            mapIDToName[pRB->ID] = std::string(pRB->szName);
        }
        else if (pDataDefs->arrDataDescriptions[i].type == Descriptor_Skeleton)
        {
            sSkeletonDescription* pSK = pDataDefs->arrDataDescriptions[i].Data.SkeletonDescription;
            for (int i = 0; i < pSK->nRigidBodies; i++)
            {
                // Note: Within FrameOfMocapData, skeleton rigid body ids are of the form:
                //   parent skeleton ID   : high word (upper 16 bits of int)
                //   rigid body id        : low word  (lower 16 bits of int)
                //
                // However within DataDescriptions they are not, so apply that here for correct lookup during streaming
                int id = pSK->RigidBodies[i].ID | (pSK->skeletonID << 16);
                mapIDToName[id] = std::string(pSK->RigidBodies[i].szName);
            }
            iSkel++;
        }
        else
            continue;
    }
    */

    return true;
}


// delayload for the NatNetSdk DLL

FARPROC WINAPI delayHook(unsigned dliNotify, PDelayLoadInfo pdli) {
    switch (dliNotify) {
    case dliStartProcessing:
        // If you want to return control to the helper, return 0.
        // Otherwise, return a pointer to a FARPROC helper function
        // that will be used instead, thereby bypassing the rest
        // of the helper.
        break;

    case dliNotePreLoadLibrary:
        // If you want to return control to the helper, return 0.
        // Otherwise, return your own HMODULE to be used by the
        // helper instead of having it call LoadLibrary itself.
        {
            std::string natNetDllName = "NatNetLib.dll";
            if(natNetDllName == pdli->szDll) {
                // get the path of the dll we're in

                char thisDllPath[MAX_PATH];
                HMODULE hm = NULL;

                if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                    GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                    (LPCSTR)&delayHook, &hm) == 0
                ) {
                    int ret = GetLastError();
                    DBG("GetModuleHandle failed, error = " << ret);
                    return 0;
                }

                if (GetModuleFileName(hm, thisDllPath, sizeof(thisDllPath)) == 0) {
                    int ret = GetLastError();
                    DBG("GetModuleFileName failed, error = " << ret);
                    return 0;
                }

                // find dirname of the path

                std::string thisDllPathStr = thisDllPath;
                size_t lastSepPos = thisDllPathStr.find_last_of("/\\");
                if (lastSepPos == std::string::npos) {
                    DBG("Failed to find last path separator of " << thisDllPath);
                    return 0;
                }

                // construct natnet dll path and load

                std::string natNetDllPath = thisDllPathStr.substr(0, lastSepPos + 1) + "NatNetLib.nonvst-dll";
                return reinterpret_cast<FARPROC>(LoadLibrary(natNetDllPath.c_str()));
            }
        }
        break;

    case dliNotePreGetProcAddress:
        // If you want to return control to the helper, return 0.
        // If you choose you may supply your own FARPROC function
        // address and bypass the helper's call to GetProcAddress.
        break;

    case dliFailLoadLib:
        // LoadLibrary failed.
        // If you don't want to handle this failure yourself, return 0.
        // In this case the helper will raise an exception
        // (ERROR_MOD_NOT_FOUND) and exit.
        // If you want to handle the failure by loading an alternate
        // DLL (for example), then return the HMODULE for
        // the alternate DLL. The helper will continue execution with
        // this alternate DLL and attempt to find the
        // requested entrypoint via GetProcAddress.
        break;

    case dliFailGetProc:
        // GetProcAddress failed.
        // If you don't want to handle this failure yourself, return 0.
        // In this case the helper will raise an exception
        // (ERROR_PROC_NOT_FOUND) and exit.
        // If you choose, you may handle the failure by returning
        // an alternate FARPROC function address.
        break;

    case dliNoteEndProcessing:
        // This notification is called after all processing is done.
        // There is no opportunity for modifying the helper's behavior
        // at this point except by longjmp()/throw()/RaiseException.
        // No return value is processed.
        break;
    }

    return NULL;
}

ExternC const PfnDliHook __pfnDliNotifyHook2 = delayHook;
ExternC const PfnDliHook __pfnDliFailureHook2 = delayHook;
