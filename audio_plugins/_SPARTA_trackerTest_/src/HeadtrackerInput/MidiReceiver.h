#pragma once

#include <JuceHeader.h>
#include <cmath>
#include <functional>

#include "HeadtrackerTypes.h"

using namespace HeadtrackerTypes;

class MidiReceiver : public juce::MidiInputCallback
{

public:
	MidiReceiver(xyzyprCallback callback);
	MidiReceiver();
	~MidiReceiver();

	juce::String inputName = "Headtracker #2";
	int channel = 2;
	int firstCcNumCoarse = 16;
	int firstCcNumFine = 48;
	bool receiveQuaternions = true;

	bool enable();
	void disable();

	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;

private:
	enum { NUM_COMPONENTS = 4 };
	static const float RADTO14;
	static const float ONETO14;

	xyzyprCallback onXyzyprReceived;
	std::unique_ptr<juce::MidiInput> midiInput;
	juce::CriticalSection changingMidiInput;
	
	int coarse[NUM_COMPONENTS] = {-1};
	int fine[NUM_COMPONENTS] = {-1};

	bool haveAllComponents();
	size_t getLastComponentIndex();
	int computeCombinedComponent(size_t index);
	float computeQuatComponent(size_t index);
	float computeYprComponent(size_t index);
	void quatToYpr(float w, float x, float y, float z, float& yaw, float& pitch, float& roll);
};