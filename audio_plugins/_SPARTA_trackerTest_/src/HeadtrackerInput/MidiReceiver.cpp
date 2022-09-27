#include "MidiReceiver.h"

const float MidiReceiver::RADTO14 = 2607.594587617613379;
const float MidiReceiver::ONETO14 = 8191;

const uint8_t MidiReceiver::SUPPERWARE_SETUP_RESET = 1 << 6;
const uint8_t MidiReceiver::SUPPERWARE_SETUP_RATE_50HZ = 0 << 4;
const uint8_t MidiReceiver::SUPPERWARE_SETUP_RATE_25HZ = 1 << 4;
const uint8_t MidiReceiver::SUPPERWARE_SETUP_RATE_100HZ = 2 << 4;
const uint8_t MidiReceiver::SUPPERWARE_SETUP_SENSORS_OFF = 0 << 3;
const uint8_t MidiReceiver::SUPPERWARE_SETUP_SENSORS_ON = 1 << 3;
const uint8_t MidiReceiver::SUPPERWARE_DATA_RAW_OFF = 0 << 4;
const uint8_t MidiReceiver::SUPPERWARE_DATA_RAW_COMPASS = 1 << 4;
const uint8_t MidiReceiver::SUPPERWARE_DATA_RAW_NO_COMPASS = 2 << 4;
const uint8_t MidiReceiver::SUPPERWARE_DATA_ORIENT_TAIT_BRYAN = 0 << 2;
const uint8_t MidiReceiver::SUPPERWARE_DATA_ORIENT_QUATERNIONS = 1 << 2;
const uint8_t MidiReceiver::SUPPERWARE_DATA_ORIENT_ORTHO_MATRIX = 2 << 2;
const uint8_t MidiReceiver::SUPPERWARE_DATA_TRACKING_OFF = 0;
const uint8_t MidiReceiver::SUPPERWARE_DATA_TRACKING_ON = 1;

MidiReceiver::MidiReceiver(xyzyprCallback callback, Type type)
{
    this->onXyzyprReceived = callback;
    this->type = type;
}

MidiReceiver::MidiReceiver(xyzyprCallback callback) :
    MidiReceiver(callback, Type::Supperware)
{}

MidiReceiver::MidiReceiver() :
    MidiReceiver([](Source source, float x, float y, float z, float yaw, float pitch, float roll) {})
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

    if (guessType) {
        bool looksLikeSupperware = inputName == "Head Tracker";
        type = looksLikeSupperware ? Type::Supperware : Type::MrHeadTracker;
    }

    auto midiInputs = juce::MidiInput::getDevices();

    const int inputIndex = midiInputs.indexOf(inputName);

    if (inputIndex < 0) {
        DBG("no matching midi input found");
        return false;
    }

    midiInput = juce::MidiInput::openDevice(inputIndex, this);
    if (midiInput == nullptr) {
        DBG("MidiInput::openDevice failed");
        return false;
    }

    midiInput->start();

    DBG("opened midi input: " << midiInput->getName());

    if (type == Type::Supperware) {
        return initSupperware();
    }

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
    switch (type) {
    case Type::MrHeadTracker:
        handleMrHeadTrackerMessage(message);
        break;
    case Type::Supperware:
        handleSupperwareMessage(message);
        break;
    }
}

void MidiReceiver::handleMrHeadTrackerMessage(const MidiMessage& message)
{
    if (!(message.isController() && message.getChannel() == channel)) {
        return;
    }

    int num = message.getControllerNumber();
    int val = message.getControllerValue();

    bool isCoarse = firstCcNumCoarse <= num && num < firstCcNumCoarse + NUM_COMPONENTS;
    bool isFine = firstCcNumFine <= num && num < firstCcNumFine + NUM_COMPONENTS;

    if (!(isFine || isCoarse)) {
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

void MidiReceiver::handleSupperwareMessage(const MidiMessage& message)
{
    if (!message.isSysEx()) {
        return;
    }
    
    int sysExLen = message.getSysExDataSize();
    if (sysExLen < 11) {
        return;
    }

    const uint8_t* sysExData = message.getSysExData();
    // Orientation in Tait-Bryan Angles
    // (f0) 00 21 42 40 00 <14-bit yaw> <14-bit pitch> <14-bit roll> (f7)
    bool isYpr =
        sysExData[0] == 0x00 &&
        sysExData[1] == 0x21 &&
        sysExData[2] == 0x42 &&
        sysExData[3] == 0x40 &&
        sysExData[4] == 0x00;
    if (!isYpr) {
        return;
    }
    
    float yaw = computeSupperwareYprcomponent(sysExData[5], sysExData[6]);
    float pitch = computeSupperwareYprcomponent(sysExData[7], sysExData[8]);
    float roll = computeSupperwareYprcomponent(sysExData[9], sysExData[10]);

    onXyzyprReceived(Source::SOURCE_MIDI, 0.0, 0.0, 0.0, yaw, pitch, roll);
}

bool MidiReceiver::initSupperware()
{
    auto midiOutputs = juce::MidiOutput::getDevices();

    const int outputIndex = midiOutputs.indexOf(inputName);

    if (outputIndex < 0) {
        DBG("no matching midi output found");
        return false;
    }

    auto midiOutput = juce::MidiOutput::openDevice(outputIndex);
    if (midiOutput == nullptr) {
        DBG("MidiOutput::openDevice failed");
        return false;
    }

    // protocol: https://supperware.net/downloads/head-tracker/head%20tracker%20protocol.pdf
    // Reset; turn on all sensors and processing; enable yaw, pitch and roll output at 50Hz
    uint8_t data[] = {
        // header
        0x00, 0x21, 0x42,
        // configure sensors and processing pipeline
        0x00,
        // sensor setup
        0x00,
        SUPPERWARE_SETUP_RESET | SUPPERWARE_SETUP_RATE_100HZ | SUPPERWARE_SETUP_SENSORS_ON,
        // data output and formatting
        0x01,
        SUPPERWARE_DATA_RAW_OFF | SUPPERWARE_DATA_ORIENT_TAIT_BRYAN | SUPPERWARE_DATA_TRACKING_ON
    };
    int dataLen = sizeof(data);
    MidiMessage resetMsg = MidiMessage::createSysExMessage(data, dataLen);

    midiOutput->sendMessageNow(resetMsg);

    return true;
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

float MidiReceiver::computeSupperwareYprcomponent(uint8_t hi, uint8_t lo) {
    // from https://supperware.net/downloads/head-tracker/head%20tracker%20protocol.pdf page 12
    int i = (128 * hi) + lo;
    if(i >= 8192) { i -= 16384; }
    float f_radian = i / 2048.0f;
    return f_radian;
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
