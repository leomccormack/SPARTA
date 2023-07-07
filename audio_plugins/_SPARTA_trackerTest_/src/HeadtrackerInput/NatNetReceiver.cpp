#include "NatNetReceiver.h"

// file-level pointer to the NatNetReceiver - there shouldn't be more than one, right?...
// ugly, but NatNet callbacks need to be C-style function pointers and that doesn't really work with C++ instance methods
static NatNetReceiver* theNatNetReceiver = nullptr;

NatNetReceiver::NatNetReceiver(xyzyprCallback callback) {
    jassert(theNatNetReceiver == nullptr);
    theNatNetReceiver = this;
	onXyzyprReceived = callback;
}

NatNetReceiver::NatNetReceiver() :
    NatNetReceiver([](Source source, float x, float y, float z, float yaw, float pitch, float roll) {})
{}

NatNetReceiver::~NatNetReceiver() {
    disable();
}

bool NatNetReceiver::enable()
{
    unsigned char ver[4];
    NatNet_GetVersion(ver);

    // Set callback handlers
    // Callback for NatNet messages.

    // typedef void (NATNET_CALLCONV* NatNetLogCallback)( Verbosity level, const char* message );

    sNatNetClientConnectParams connectParams;
    connectParams.connectionType = connectionType;
    connectParams.localAddress = myAddress.toRawUTF8();
    connectParams.serverAddress = serverAddress.toRawUTF8();
    natNetClient.Disconnect();
    int retCode = natNetClient.Connect(connectParams);
    if (retCode != ErrorCode_OK) {
        //Unable to connect to server.
        sendConnMessage("natnet_connect_error");
        return false;
    } else {
        // Print server info
        sServerDescription ServerDescription;
        memset(&ServerDescription, 0, sizeof(ServerDescription));
        natNetClient.GetServerDescription(&ServerDescription);
        if (!ServerDescription.HostPresent)
        {
            //Unable to connect to server. Host not present
            sendConnMessage("natnet_connect_error");
            return false;
        }
    }

    // Retrieve RigidBody description from server
    sDataDescriptions* pDataDefs = NULL;
    retCode = natNetClient.GetDataDescriptionList(&pDataDefs);
    if (retCode != ErrorCode_OK || parseRigidBodyDescription(pDataDefs) == false)
    {
        //Unable to retrieve RigidBody description
        // TODO: report
        return false;
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
        unitConversion = *(float*)response;
    }

    retCode = natNetClient.SendMessageAndWait("UpAxis", &response, &nBytes);
    if (retCode == ErrorCode_OK)
    {
        upAxis = *(long*)response;
    }

    sendConnMessage("natnet_connect");

    NatNet_SetLogCallback(staticHandleMessage);
    // this function will receive data from the server
    natNetClient.SetFrameReceivedCallback(staticHandleData);

	return true;
}

void NatNetReceiver::disable()
{
    natNetClient.Disconnect();
    sendConnMessage("natnet_disconnect");
}

void NatNetReceiver::addConnListener(ActionListener* listener)
{
    connBroadcaster.addActionListener(listener);
}

void NatNetReceiver::removeConnListener(ActionListener* listener)
{
    connBroadcaster.removeActionListener(listener);
}

void NatNetReceiver::handleData(sFrameOfMocapData* data, void* pUserData)
{
    int mcount = std::min(MarkerPositionCollection::MAX_MARKER_COUNT, static_cast<size_t>(data->MocapData->nMarkers));
    markerPositions.SetMarkerPositions(data->MocapData->Markers, mcount);

    // Marker Data
    markerPositions.SetLabledMarkers(data->LabeledMarkers, data->nLabeledMarkers);

    // nOtherMarkers is deprecated
    // mcount = min(MarkerPositionCollection::MAX_MARKER_COUNT, data->nOtherMarkers);
    // markerPositions.AppendMarkerPositions(data->OtherMarkers, mcount);

    // rigid bodies
    int rbcount = std::min(RigidBodyCollection::MAX_RIGIDBODY_COUNT, static_cast<size_t>(data->nRigidBodies));
    rigidBodies.SetRigidBodyData(data->RigidBodies, rbcount);

    // for first rigid body, transform data and send OSC
    if (rbcount > 0) {
        int i = 0;
        transData.setFromBodyData(
            rigidBodies.GetCoordinates(i),
            rigidBodies.GetQuaternion(i),
            upAxis
        );
        onXyzyprReceived(Source::SOURCE_NATNET, transData.x, transData.y, transData.z, transData.yaw, transData.pitch, transData.roll);
    }
}

void NatNetReceiver::handleMessage(Verbosity msgType, const char* msg)
{
    DBG("handleNatNetMessage(): " << msg);
}

void NATNET_CALLCONV NatNetReceiver::staticHandleData(sFrameOfMocapData* data, void* pUserData)
{
    jassert(theNatNetReceiver != nullptr);
    theNatNetReceiver->handleData(data, pUserData);
}

void NATNET_CALLCONV NatNetReceiver::staticHandleMessage(Verbosity msgType, const char* msg)
{
    jassert(theNatNetReceiver != nullptr);
    theNatNetReceiver->handleMessage(msgType, msg);
}

bool NatNetReceiver::parseRigidBodyDescription(sDataDescriptions* pDataDefs)
{
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
        } else if (pDataDefs->arrDataDescriptions[i].type == Descriptor_Skeleton)
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
        } else
            continue;
    }
}

void NatNetReceiver::sendConnMessage(const String& message)
{
    connBroadcaster.sendActionMessage(message);
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
        if (natNetDllName == pdli->szDll) {
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
