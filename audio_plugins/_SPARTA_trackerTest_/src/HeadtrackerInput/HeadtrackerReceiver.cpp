#include "HeadtrackerReceiver.h"

HeadtrackerReceiver::HeadtrackerReceiver()
	: HeadtrackerReceiver([](Source source, float x, float y, float z, float yaw, float pitch, float roll) {})
{}

bool HeadtrackerReceiver::enable()
{
	disable();
	switch (activeSource) {
	case Source::SOURCE_NATNET:
		return natNetReceiver.enable();
		break;
	case Source::SOURCE_OSC:
		return oscReceiver.enable();
		break;
	case Source::SOURCE_MIDI:
		return midiReceiver.enable();
		break;
	}
	return false;
}

void HeadtrackerReceiver::disable()
{
	natNetReceiver.disable();
	midiReceiver.disable();
	oscReceiver.disable();
}

HeadtrackerReceiver::HeadtrackerReceiver(xyzyprCallback callback) :
	activeSource(Source::SOURCE_NATNET),
	onXyzyprReceived([=](Source source, float x, float y, float z, float yaw, float pitch, float roll) {
	  if (source == activeSource) {
		  callback(source, x, y, z, yaw, pitch, roll);
	  }
	}),
	natNetReceiver(onXyzyprReceived),
	oscReceiver(onXyzyprReceived),
	midiReceiver(onXyzyprReceived)
{
}

Source HeadtrackerReceiver::getActiveSource()
{
	return activeSource;
}

void HeadtrackerReceiver::setActiveSource(Source source)
{
	activeSource = source;
	enable();
}

