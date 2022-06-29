#pragma once

#include <JuceHeader.h>
#include <cmath>
#include <functional>

#include "HeadtrackerTypes.h"

using namespace HeadtrackerTypes;

class MidiReceiver : public juce::MidiInputCallback
{
public:
	enum class Type { MrHeadTracker, Supperware };

	MidiReceiver(xyzyprCallback callback, Type type);
	MidiReceiver(xyzyprCallback callback);
	MidiReceiver();
	~MidiReceiver();

	Type type;

	juce::String inputName = "";

	// params for MrHeadTracker
	int channel = 1;
	int firstCcNumCoarse = 16;
	int firstCcNumFine = 48;
	bool guessType = true;
	bool receiveQuaternions = false;

	bool enable();
	void disable();

	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;
	void handleMrHeadTrackerMessage(const MidiMessage& message);
	void handleSupperwareMessage(const MidiMessage& message);
	bool initSupperware();

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