# SPARTA

Spatial audio real-time applications (SPARTA). A collection of VST audio plug-ins for spatial audio production, reproduction and analysis.

![](sparta_screenshot.png)

## The Plug-ins

This repository contains the following VST plug-ins:
* **AmbiBIN** - A binaural ambisonic decoder (orders 0-7) with a built-in SOFA loader and head-tracking support via OSC messages.
* **AmbiDEC** - A frequency-dependent loudspeaker ambisonic decoder (orders 1-7) with user specifiable loudspeaker directions (up to 64), which may be optionally imported via JSON configuration files. It includes AllRAD/EPAD/SAD/MMD decoding methods. The loudspeaker signals may also be binauralised for headphone playback.
* **AmbiDRC** - A frequency-dependent dynamic range compressor for ambisonic signals (orders 0-7). 
* **AmbiENC** - An ambisonic encoder/panner (orders 1-7), with support for up to 64 input channels; the directions for which may also be imported via JSON configuration files. 
* **Array2SH** - A microphone array spatial encoder (orders 1-7), with presets for several commercially available A-format and higher-order microphone arrays. The plug-in can also present objective evaluation metrics for the currently selected configuration.
* **Binauraliser** - A binaural panner (up to 64 input channels) with a built-in SOFA loader and head-tracking support via OSC messages.
* **Panner** - A frequency-dependent 3-D panner using the VBAP method (up to 64 inputs and outputs).
* **PowerMap** - A sound-field visualisation plug-in based on ambisonic signals as input (orders 1-7), with PWD/MVDR/MUSIC/Min-Norm options.
* **Rotator** - A flexible ambisonic signals rotator (orders 1-7) with head-tracking support via OSC messages. 
* **SLDoA** - A frequency-dependent sound-field visualiser, based on depicting the direction-of-arrival (DoA) estimates derived from spatially localised active-intensity vectors. The low frequency estimates are shown with blue icons, mid-frequencies with green, and high-frequencies with red. 

## Getting Started

These instructions will help you compile the individual VST audio plug-ins. Alternatively, they can be downloaded from here:
* [Pre-built](http://research.spa.aalto.fi/projects/sparta_vsts/) - for Windows (64-bit) and Mac OSX (10.9 or higher)

### Prerequisites

To compile the plugins yourself, the following SDKs and frameworks must be placed in the 'SDKs' folder like so

```
SDKs/modules
SDKs/Spatial_Audio_Framework/framework
SDKs/VST3_SDK
```
And can be obtained from:

* [JUCE](https://shop.juce.com/get-juce/download) - For audio plug-in wrappers and GUIs
* [Spatial_Audio_Framework](https://github.com/leomccormack/Spatial_Audio_Framework) - For the internal code used by the plug-ins
* [VST3_SDK](https://www.steinberg.net/en/company/developers.html) - The VST SDK

Windows users must also install Intel's MKL, which can be freely acquired from
* [Intel MKL](https://software.intel.com/en-us/articles/free-ipsxe-tools-and-libraries)

### Installing

For each individual plug-in, simply open the Visual Studio or X-code project file and build a release version

```
audio_plugins/_SPARTA_X_/make/
```

## Authors

* **Leo McCormack** - C/C++ programmer and DSP researcher (contact: leo.mccormack@aalto.fi)
* **Symeon Delikaris-Manias** - DSP researcher
* **Archontis Politis** -  DSP researcher
* **Ville Pulkki** - DSP researcher


## License

This project is licensed under the GPLv3 License - see the [LICENSE](LICENSE) file for details


