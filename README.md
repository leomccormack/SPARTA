# SPARTA

SPatial Audio Real-Time Applications (SPARTA). A collection of VST audio plug-ins for spatial audio production, reproduction and visualisation.

![](sparta_screenshot.png)

## The Plug-ins

This repository contains the following VST plug-ins:
* **AmbiBIN** - A binaural ambisonic decoder (up to 7th order) with a built-in SOFA loader and head-tracking support via OSC messages.
* **AmbiDEC** - A frequency-dependent loudspeaker ambisonic decoder (up to 7th order) with user specifiable loudspeaker directions (up to 64), which may be optionally imported via JSON configuration files. It includes AllRAD/EPAD/SAD/MMD decoding methods. The loudspeaker signals may also be binauralised for headphone playback.
* **AmbiDRC** - A frequency-dependent dynamic range compressor for ambisonic signals (up to 7th order). 
* **AmbiENC** - An ambisonic encoder/panner (up to 7th order), with support for up to 64 input channels; the directions for which may also be imported via JSON configuration files. 
* **Array2SH** - A microphone array spatial encoder (up to 7th order), with presets for several commercially available A-format and higher-order microphone arrays. The plug-in can also present objective evaluation metrics for the currently selected configuration.
* **Binauraliser** - A binaural panner (up to 64 input channels) with a built-in SOFA loader and head-tracking support via OSC messages.
* **Panner** - A frequency-dependent 3-D panner using the VBAP method (up to 64 inputs and outputs).
* **PowerMap** - A sound-field visualisation plug-in based on ambisonic signals as input (up to 7th order), with PWD/MVDR/MUSIC/Min-Norm options.
* **Rotator** - A flexible ambisonic rotator (up to 7th order) with head-tracking support via OSC messages. 
* **SLDoA** - A frequency-dependent sound-field visualiser (up to 7th order), based on depicting the direction-of-arrival (DoA) estimates derived from spatially localised active-intensity vectors. The low frequency estimates are shown with blue icons, mid-frequencies with green, and high-frequencies with red. 

## Getting Started

These instructions will help you compile the individual VST audio plug-ins. Alternatively, they can be downloaded from here:
* [Pre-built](http://research.spa.aalto.fi/projects/sparta_vsts/) - for Windows (64-bit) and Mac OSX (10.10 or higher)

**NOTE: As of 6.12.2018, the code requires JUCE v5.3.2 and vstsdk3610_11_06_2018_build_37 or older. We are currently looking into how to accommodate the recent changes.**

### Prerequisites

To compile the plugins yourself, the following SDKs and frameworks must be placed in the 'SDKs' folder like so

```
SDKs/modules
SDKs/Spatial_Audio_Framework
SDKs/VST3_SDK
```
And can be obtained from:

* [modules](https://shop.juce.com/get-juce/download) - For audio plug-in wrappers and the GUIs
* [Spatial_Audio_Framework](https://github.com/leomccormack/Spatial_Audio_Framework) - For the internal code used by the plug-ins
* [VST3_SDK](https://www.steinberg.net/en/company/developers.html) - The VST SDK

You must also install a custom [Intel MKL](https://software.intel.com/en-us/articles/free-ipsxe-tools-and-libraries) .dll/.dylib in a system path folder. More details on this can be found [here](https://github.com/leomccormack/Spatial_Audio_Framework). However, Mac users may elect to remove the "SAF_USE_INTEL_MKL" flag in the global pre-precessor definitions, in order to get around this requirement; albeit, at the expense of a reduction in performance.

### Installing

For each individual plug-in, simply open the Visual Studio (2015/2017) or X-code project file and build a release version

```
audio_plugins/_SPARTA_X_/make/
```

To generate project files for other IDEs or Linux makefiles, one must open and configure the included .jucer files with JUCE's Projucer App accordingly; however, these are currently not officially supported. 

## Authors

* **Leo McCormack** - C/C++ programmer and DSP researcher (contact: leo.mccormack@aalto.fi)
* **Symeon Delikaris-Manias** - DSP researcher
* **Archontis Politis** -  DSP researcher
* **Ville Pulkki** - DSP researcher


## License

This project is licensed under the GPLv3 License - see the [LICENSE](LICENSE) file for details


