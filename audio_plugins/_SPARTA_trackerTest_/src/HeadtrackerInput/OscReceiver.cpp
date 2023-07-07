#include "OscReceiver.h"

OscReceiver::OscReceiver(xyzyprCallback callback) {
	onXyzyprReceived = callback;
}

OscReceiver::OscReceiver() :
    OscReceiver([](Source source, float x, float y, float z, float yaw, float pitch, float roll) {})
{}

OscReceiver::~OscReceiver() {
    disable();
}

bool OscReceiver::enable()
{
    disable();
    bool connected = osc.connect(port);
    if (connected) {
        osc.addListener(this);
        return true;
    } else {
        return false;
    }
}

void OscReceiver::disable()
{
    osc.disconnect();
    osc.removeListener(this);
}

void OscReceiver::oscMessageReceived(const OSCMessage& message)
{
    String addr = message.getAddressPattern().toString();
    if (addr == "/xyz" && message.size() == 3) {
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;
        if (message[0].isFloat32())
            x = message[0].getFloat32();
        if (message[1].isFloat32())
            y = message[1].getFloat32();
        if (message[2].isFloat32())
            z = message[2].getFloat32();
        onXyzyprReceived(Source::SOURCE_OSC, x, y, z, 0.0, 0.0, 0.0);
    } /* else if (addr == "/xyzquat" && message.size() == 7) {
        if (message[0].isFloat32())
            x = message[0].getFloat32();
        if (message[1].isFloat32())
            y = message[1].getFloat32();
        if (message[2].isFloat32())
            z = message[2].getFloat32();
        if (message[3].isFloat32())
            //rotator_setQuaternionW(hRot, message[3].getFloat32());
            if (message[4].isFloat32())
                //rotator_setQuaternionX(hRot, message[4].getFloat32());
                if (message[5].isFloat32())
                    //rotator_setQuaternionY(hRot, message[5].getFloat32());
                    if (message[6].isFloat32())
                        //rotator_setQuaternionY(hRot, message[6].getFloat32());
                        return;
    }*/
    else if (addr == "/ypr" && message.size() == 3) {
        float yaw = 0.0;
        float pitch = 0.0;
        float roll = 0.0;
        if (message[0].isFloat32())
            yaw = message[0].getFloat32();
        if (message[1].isFloat32())
            pitch = message[1].getFloat32();
        if (message[2].isFloat32())
            roll = message[2].getFloat32();
        onXyzyprReceived(Source::SOURCE_OSC, 0.0, 0.0, 0.0, yaw, pitch, roll);
    } else if (addr == "/xyzypr" && message.size() == 6) {
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;
        float yaw = 0.0;
        float pitch = 0.0;
        float roll = 0.0;
        if (message[0].isFloat32())
            x = message[0].getFloat32();
        if (message[1].isFloat32())
            y = message[1].getFloat32();
        if (message[2].isFloat32())
            z = message[2].getFloat32();
        if (message[3].isFloat32())
            yaw = message[3].getFloat32();
        if (message[4].isFloat32())
            pitch = message[4].getFloat32();
        if (message[5].isFloat32())
            roll = message[5].getFloat32();
        onXyzyprReceived(Source::SOURCE_OSC, x, y, z, yaw, pitch, roll);
    }
}
