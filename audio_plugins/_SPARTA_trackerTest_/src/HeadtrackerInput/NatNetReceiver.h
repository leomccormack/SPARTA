#pragma once

#include <JuceHeader.h>
#define NOGDI
#define NOMINMAX
#include <Windows.h>
#include <delayimp.h>

#include <algorithm>
#include <cmath>
#include <functional>

#include "NatNetTypes.h"
#include "NatNetCAPI.h"
#include "NatNetClient.h"

#include "HeadtrackerTypes.h"

#include "NatNetTools/MarkerPositionCollection.h"
#include "NatNetTools/RigidBodyCollection.h"
#include "NatNetTools/TransformedData.h"

using namespace HeadtrackerTypes;

class NatNetReceiver
{
public:
	NatNetReceiver(xyzyprCallback callback);
	NatNetReceiver();
	~NatNetReceiver();

	juce::String myAddress = "127.0.0.1";
	juce::String serverAddress = "127.0.0.1";
	ConnectionType connectionType = ConnectionType::ConnectionType_Multicast;

	bool enable();
	void disable();
	void addConnListener(ActionListener* listener);
	void removeConnListener(ActionListener* listener);

	void handleData(sFrameOfMocapData* data, void* pUserData);
	void handleMessage(Verbosity msgType, const char* msg);

	// NatNet SDK takes callbacks as function pointers and is thus incompatible with C++ instance methods
	// so we make these static functions which grab a file-level pointer to our instance and invoke the corresponding methods
	// very ugly!
	static void NATNET_CALLCONV staticHandleData(sFrameOfMocapData* data, void* pUserData); // receives data from the server
	static void NATNET_CALLCONV staticHandleMessage(Verbosity msgType, const char* msg); // receives NatNet error messages

	bool parseRigidBodyDescription(sDataDescriptions* pDataDefs);

private:
	NatNetClient natNetClient;
	xyzyprCallback onXyzyprReceived;

	ActionBroadcaster connBroadcaster;
	void sendConnMessage(const String& message);
	float unitConversion;
	long upAxis;

	// Objects for saving off marker and rigid body data streamed from NatNet.
	MarkerPositionCollection markerPositions;
	RigidBodyCollection rigidBodies;
	std::map<int, std::string> mapIDToName;

	// Currently only transforming data for one rigid body, so don't bother with a collection
	TransformedData transData;
};