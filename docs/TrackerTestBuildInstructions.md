# Tracker Test Build Instructions

The sparta_trackerTest plugin requires an additional SDK to be placed in the following folder like so:
```
SDKs/NatNetSDK
```
This SDK may be downloaded from [here](https://optitrack.com/support/downloads/developer-tools.html#natnet-sdk).

Note that due to this dependency (which is Win64 only), this plugin can only be built using VisualStudio solutions which are exported by Projucer. 

## Running the sparta_trackerTest plugin

In order to use the plugin, the sparta_trackerTest.dll file should be placed in a folder that is scanned by the DAW.
Additionally, the following file (included in the SDK described above) must be placed in a system PATH folder, such as
```
C://Windows/System32/NatNetLib.dll
C://Windows/System32/NatNetML.dll
```
