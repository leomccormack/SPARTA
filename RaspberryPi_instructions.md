# Raspberry Pi Versions Instructions

Note: we have only tested Raspberry Pi 4 Model B and Pi 3 Model B+, with RapianOS and Reaper (armv7l) as the host.

1. First install [Raspian](https://www.raspberrypi.org/downloads/raspbian/)  (We recommend the full install)

2. The following SDKs and frameworks must then be placed in the 'SDKs' folder like so

```
SDKs/modules
SDKs/Spatial_Audio_Framework
SDKs/VST2_SDK
```
And can be obtained from:

* [modules (JUCE)](https://shop.juce.com/get-juce/download) - For audio plug-in wrappers and the GUIs
* [Spatial_Audio_Framework (SAF)](https://github.com/leomccormack/Spatial_Audio_Framework) - For the internal code used by the plug-ins
* [VST2_SDK](https://github.com/steinbergmedia/vst3sdk/releases) - The VST2 SDK (found in vstsdk3610_11_06_2018_build_37 or older)

3. Install JUCE related dependencies
```
sudo apt-get update
sudo apt-get install x11proto-xinerama-dev libwebkit2gtk-4.0-dev libgtk-3-dev x11proto-xext-dev libcurl4-openssl-dev 
sudo apt install libasound2-dev
```
 
4. Install SAF related dependencies

```
sudo apt install liblapack3 liblapack-dev libopenblas-base libopenblas-dev liblapacke-dev
sudo apt-get install libhdf5-dev libnetcdf-dev libnetcdff-dev
```

5. Run make file 
```
make CONFIG=Release
```


## Projucer

https://shop.juce.com/get-juce/download
Linux download

JUCE-X.X.X/extras/Projucer/JuceLibraryCode/AppConfig.h
JUCER_ENABLE_GPL_MODE 1

cd JUCE-X.X.X/extras/Projucer/Builds/LinuxMakefile
make CONFIG=Release










