#include "MidiReceiver.h"

const float MidiReceiver::RADTO14 = 2607.594587617613379;
const float MidiReceiver::ONETO14 = 8191;

MidiReceiver::MidiReceiver(xyzyprCallback callback) {
	onXyzyprReceived = callback;
}

MidiReceiver::MidiReceiver() : MidiReceiver([](Source source, float x, float y, float z, float yaw, float pitch, float roll) {})
{}

MidiReceiver::~MidiReceiver() {
    disable();
}

bool MidiReceiver::enable()
{
    if (midiInput != nullptr) {
        disable();
    }

    const juce::ScopedLock scopedLock(changingMidiInput);

    auto midiInputs = juce::MidiInput::getDevices();

    const int inputIndex = midiInputs.indexOf(inputName);

    if (inputIndex < 0) {
        DBG("no matching midi input found");
        return false;
    }

    midiInput = juce::MidiInput::openDevice(inputIndex, this);
    if (midiInput == nullptr) {
        DBG("openDevice failed");
        return false;
    }

    midiInput->start();

    DBG("opened midi input: " << midiInput->getName());

	return true;
}

void MidiReceiver::disable()
{
    const juce::ScopedLock scopedLock(changingMidiInput);
    if (midiInput != nullptr) {
        midiInput->stop();
        midiInput.reset();
        DBG("closed midi input");
    }
}

void MidiReceiver::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
{
    if (!(message.isController() && message.getChannel() == channel)) {
        return;
    }

    int num = message.getControllerNumber();
    int val = message.getControllerValue();

    bool isCoarse = firstCcNumCoarse <= num && num < firstCcNumCoarse + NUM_COMPONENTS;
    bool isFine = firstCcNumFine <= num && num < firstCcNumFine + NUM_COMPONENTS;

    if(!(isFine || isCoarse)) {
        return;
    }

    if (isFine) {
        int index = num - firstCcNumFine;
        fine[index] = val;
    } else { // isCoarse
        int index = num - firstCcNumCoarse;
        coarse[index] = val;

        int lastIndex = getLastComponentIndex();

        if (index == lastIndex && haveAllComponents()) {
            float yaw;
            float pitch;
            float roll;

            if (receiveQuaternions) {
                float qw = computeQuatComponent(0);
                float qx = computeQuatComponent(1);
                float qy = computeQuatComponent(2);
                float qz = computeQuatComponent(3);
                quatToYpr(qw, qx, qy, qz, yaw, pitch, roll);
            } else {
                yaw = computeYprComponent(0);
                pitch = computeYprComponent(1);
                roll = computeYprComponent(2);
            }

            onXyzyprReceived(Source::SOURCE_MIDI, 0.0, 0.0, 0.0, yaw, pitch, roll);
        }
    }
}

bool MidiReceiver::haveAllComponents()
{
    for (size_t i = 0; i < NUM_COMPONENTS; i++) {
        if (coarse[i] < 0 || fine[i] < 0) {
            return false;
        }
    }
    return true;
}

size_t MidiReceiver::getLastComponentIndex() {
    return receiveQuaternions ? 3 : 2;
}

int MidiReceiver::computeCombinedComponent(size_t index)
{
    return (coarse[index] << 7) | fine[index];
}

float MidiReceiver::computeQuatComponent(size_t index)
{
    return computeCombinedComponent(index) / ONETO14 - 1.0;
}

float MidiReceiver::computeYprComponent(size_t index)
{
    return computeCombinedComponent(index) / RADTO14 - MathConstants<float>::pi;
}

void MidiReceiver::quatToYpr(float w, float x, float y, float z, float& yaw, float& pitch, float& roll)
{
    // yaw (z-axis rotation)
    double siny_cosp = 2.0 * ((w * z) + (x * y));
    double cosy_cosp = 1.0 - (2.0 * ((y * y) + (z * z)));
    yaw = atan2(siny_cosp, cosy_cosp);

    // pitch (y-axis rotation)
    double sinp = 2.0 * ((w * y) - (z * x));
    pitch = abs(sinp) >= 1.0 ? copysign(MathConstants<double>::halfPi, sinp) : asin(sinp);

    // roll (x-axis rotation)
    double sinr_cosp = 2.0 * ((w * x) + (y * z));
    double cosr_cosp = 1.0 - (2.0 * ((x * x) + (y * y)));
    roll = atan2(sinr_cosp, cosr_cosp);
}
