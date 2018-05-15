# SPARTA

Spatial audio real-time applications (SPARTA). A collection of VST audio plug-ins for spatial audio production, reproduction and analysis.

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
And can be obtained from

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


