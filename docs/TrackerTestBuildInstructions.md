# Tracker Test Build Instructions

The sparta_trackerTest plugin requires an additional SDK to be placed in the following folder like so:
```
SDKs/NatNetSDK
```
This SDK may be downloaded from [here](https://optitrack.com/support/downloads/developer-tools.html#natnet-sdk).

Note that due to this dependency (which is Win64 only), this plugin can only be built using VisualStudio solutions which are exported by Projucer. 
