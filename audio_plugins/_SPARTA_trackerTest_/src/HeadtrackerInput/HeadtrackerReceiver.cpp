#include "HeadtrackerReceiver.h"

HeadtrackerReceiver::HeadtrackerReceiver()
	: HeadtrackerReceiver([](Source source, float x, float y, float z, float yaw, float pitch, float roll) {})
{}

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
	oscReceiver.disable();
	midiReceiver.disable();

	activeSource = source;

	switch (source) {
	case Source::SOURCE_NATNET:

		break;
	case Source::SOURCE_OSC:
		oscReceiver.enable();
		break;
	case Source::SOURCE_MIDI:
		midiReceiver.enable();
		break;
	}
}

