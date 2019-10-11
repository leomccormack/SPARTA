# SPARTA

SPatial Audio Real-Time Applications (SPARTA). A collection of VST audio plug-ins for spatial audio production, reproduction and visualisation.

![](sparta_screenshot.png)

## The Plug-ins

This repository contains the following VST plug-ins:
* **AmbiBIN** - A binaural ambisonic decoder (up to 7th order) with a built-in SOFA loader and head-tracking support via OSC messages. Includes: Least-Squares (LS), spatial re-sampling (SPR), time-alignment (TA), and magnitude least-squares (Mag-LS) decoding options.
* **AmbiDEC** - A frequency-dependent loudspeaker ambisonic decoder (up to 7th order) with user specifiable loudspeaker directions (up to 64), which may be optionally imported via JSON configuration files. Includes: All-Round (AllRAD), Energy-Preserving (EPAD), Spatial (SAD), and Mode-Matching (MMD) ambisonic decoding options. The loudspeaker signals may also be binauralised for headphone playback.
* **AmbiDRC** - A frequency-dependent dynamic range compressor for ambisonic signals (up to 7th order). 
* **AmbiENC** - An ambisonic encoder/panner (up to 7th order), with support for up to 64 input channels; the directions for which may also be imported via JSON configuration files. 
* **Array2SH** - A microphone array spatial encoder (up to 7th order), with presets for several commercially available A-format and higher-order microphone arrays. The plug-in can also present objective evaluation metrics for the currently selected configuration.
* **Beamformer** - A spherical harmonic domain beamforming plug-in with multiple beamforming strategies (up to 64 output beams).  
* **Binauraliser** - A binaural panner (up to 64 input channels) with a built-in SOFA loader and head-tracking support via OSC messages.
* **DirASS** - A sound-field visualiser based on re-assigning the energy of beamformers. This re-assigment is based on DoA estimates extracted from "spatially-constrained" regions, which are centred around each beamformer look-direction. 
* **MatrixConv** - A basic matrix convolver with an optional partitioned convolution mode. The user need only specify the number of inputs and load the filters via a wav file.
* **MultiConv** - A basic multi-channel convolver with an optional partitioned convolution mode. Unlike "MatrixConv", this plug-in does not perform any matrixing. Instead, each input channel is convolved with the respective filter; i.e. numInputs = numFilters = numOutputs.
* **Panner** - A frequency-dependent 3-D panner using the VBAP method (up to 64 inputs and outputs).
* **PowerMap** - A sound-field visualisation plug-in based on ambisonic signals as input (up to 7th order), with PWD/MVDR/MUSIC/Min-Norm options.
* **Rotator** - A flexible ambisonic rotator (up to 7th order) with head-tracking support via OSC messages. 
* **SLDoA** - A frequency-dependent sound-field visualiser (up to 7th order), based on depicting the direction-of-arrival (DoA) estimates derived from spatially localised active-intensity vectors. The low frequency estimates are shown with blue icons, mid-frequencies with green, and high-frequencies with red. 

## Getting Started

These instructions will help you compile the individual VST audio plug-ins. Alternatively, they can be downloaded from here:
* [Pre-built](http://research.spa.aalto.fi/projects/sparta_vsts/) - for Windows (64-bit), Mac OSX (10.10 or higher), and Linux (x86_64)

### Prerequisites

To compile the plugins yourself, the following SDKs and frameworks must be placed in the 'SDKs' folder like so

```
SDKs/modules
SDKs/Spatial_Audio_Framework
SDKs/VST2_SDK
```
And can be obtained from:

* [modules (JUCE)](https://shop.juce.com/get-juce/download) - For audio plug-in wrappers and the GUIs (currently tested with: **JUCE v5.4.4**)
* [Spatial_Audio_Framework](https://github.com/leomccormack/Spatial_Audio_Framework) - For the internal code used by the plug-ins
* [VST2_SDK](https://github.com/steinbergmedia/vst3sdk/releases) - The VST2 SDK (found in [vstsdk3610_11_06_2018_build_37](https://web.archive.org/web/20181016150224/https://download.steinberg.net/sdk_downloads/vstsdk3610_11_06_2018_build_37.zip) or older)

You must also install a custom [Intel MKL](https://software.intel.com/en-us/articles/free-ipsxe-tools-and-libraries) .dll/.dylib in a system path folder. More details on this can be found [here](https://github.com/leomccormack/Spatial_Audio_Framework). However, MacOSX users may elect to remove the "SAF_USE_INTEL_MKL" flag in the global pre-precessor definitions, in order to get around this requirement; albeit, at the expense of a reduction in performance.

### Building the plug-ins

Visual Studio (2015/2017) solutions, Xcode project files, and Linux Makefiles are included in:

```
audio_plugins/_SPARTA_X_/make/
```

To generate project files for other IDEs, you can open and configure the included .jucer files with JUCE's Projucer App accordingly.

We are currently exploring CMake, to make this endeavour more streamlined.

## Known issues

* Note: since Xcode cannot understand folder/file aliases, if "mkl.h" cannot be found, it is because the current header search path is set to: /opt/intel/compilers_and_libraries_2018.5.231/mac/mkl/include. Which may not correspond to your install path (i.e. you have a different version to us). If anyone has a good solution/workaround for this, please let us know : )
* Linux versions are quite experimental, but have been tested and largely work for us (we have experienced some graphical glitches, but these are consistent with other JUCE-made plugins).  However, please report any weird behaviour. 
* Due to missing code in the JUCE framework: on MacOSX, the camera ID cannot be changed for the visualisation plugins. And on Linux, the camera cannot be used at all.

Please let us know if you encounter any other issues (contact via email: leo.mccormack@aalto.fi, or raise a github "issue").

## Authors

* **Leo McCormack** - C/C++ programmer and DSP design
* **Symeon Delikaris-Manias** - DSP design
* **Archontis Politis** -  DSP design
* **Ville Pulkki** - DSP design


## License

This project is licensed under the GPLv3 License - see the [LICENSE](LICENSE) file for details


