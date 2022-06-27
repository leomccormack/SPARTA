#pragma once

#include <JuceHeader.h>
#include <cmath>
#include <functional>

#include "HeadtrackerTypes.h"

using namespace HeadtrackerTypes;

class OscReceiver : public juce::OSCReceiver::Listener<juce::OSCReceiver::RealtimeCallback>
{
public:
	OscReceiver(xyzyprCallback callback);
	OscReceiver();
	~OscReceiver();

	int port = 9000;

	bool enable();
	void disable();

	void oscMessageReceived(const OSCMessage& message) override;

private:
	xyzyprCallback onXyzyprReceived;
	juce::OSCReceiver osc;
};