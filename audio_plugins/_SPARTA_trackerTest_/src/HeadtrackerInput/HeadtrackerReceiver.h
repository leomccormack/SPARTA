#pragma once

#include "HeadtrackerTypes.h"
#include "NatNetReceiver.h"
#include "OscReceiver.h"
#include "MidiReceiver.h"

using namespace HeadtrackerTypes;

class HeadtrackerReceiver
{
public:
	HeadtrackerReceiver(xyzyprCallback callback);
	HeadtrackerReceiver();

	bool enable();
	void disable();
	Source getActiveSource();
	void setActiveSource(Source source);

private:
	Source activeSource;
	xyzyprCallback onXyzyprReceived;

// second public section here because we rely on the order of member declarations for initialization
public:
	NatNetReceiver natNetReceiver;
	OscReceiver oscReceiver;
	MidiReceiver midiReceiver;
};