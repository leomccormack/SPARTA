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

	static const uint8_t SUPPERWARE_SETUP_RESET;
	static const uint8_t SUPPERWARE_SETUP_RATE_50HZ;
	static const uint8_t SUPPERWARE_SETUP_RATE_25HZ;
	static const uint8_t SUPPERWARE_SETUP_RATE_100HZ;
	static const uint8_t SUPPERWARE_SETUP_SENSORS_OFF;
	static const uint8_t SUPPERWARE_SETUP_SENSORS_ON;
	static const uint8_t SUPPERWARE_DATA_RAW_OFF;
	static const uint8_t SUPPERWARE_DATA_RAW_COMPASS;
	static const uint8_t SUPPERWARE_DATA_RAW_NO_COMPASS;
	static const uint8_t SUPPERWARE_DATA_ORIENT_TAIT_BRYAN;
	static const uint8_t SUPPERWARE_DATA_ORIENT_QUATERNIONS;
	static const uint8_t SUPPERWARE_DATA_ORIENT_ORTHO_MATRIX;
	static const uint8_t SUPPERWARE_DATA_TRACKING_OFF;
	static const uint8_t SUPPERWARE_DATA_TRACKING_ON;

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
	float computeSupperwareYprcomponent(uint8_t hi, uint8_t lo);
	void quatToYpr(float w, float x, float y, float z, float& yaw, float& pitch, float& roll);
};