# SPARTA

Spatial Audio Real-Time Applications (SPARTA) [1]. A collection of VST audio plug-ins for spatial audio production, reproduction and visualisation. Developed using [JUCE](https://github.com/WeAreROLI/JUCE/) and the [Spatial_Audio_Framework](https://github.com/leomccormack/Spatial_Audio_Framework).

![](sparta_screenshot.png)

* [1] McCormack, L. and Politis, A., 2019. **SPARTA & COMPASS: Real-time implementations of linear and parametric spatial audio reproduction and processing methods**. In Audio Engineering Society Conference: 2019 AES International Conference on Immersive and Interactive Audio.

## Plug-in descriptions

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
* **PitchShifter** - A very basic multi-channel pitch shifter, based on the phase-vocoder approach.
* **PowerMap** - A sound-field visualisation plug-in based on ambisonic signals as input (up to 7th order), with PWD/MVDR/MUSIC/Min-Norm options.
* **Rotator** - A flexible ambisonic rotator (up to 7th order) with head-tracking support via OSC messages. 
* **SLDoA** - A frequency-dependent sound-field visualiser (up to 7th order), based on depicting the direction-of-arrival (DoA) estimates derived from spatially localised active-intensity vectors. The low frequency estimates are shown with blue icons, mid-frequencies with green, and high-frequencies with red. 

## Pre-built plug-ins

The plug-in suite may be downloaded from [here](http://research.spa.aalto.fi/projects/sparta_vsts/) [Mac OSX (10.10 or higher), Linux (x86_64), and Windows (64-bit)].

## Building the plug-ins yourself

First clone the repository (including submodules) with:

```
git clone --recursive https://github.com/leomccormack/SPARTA
# or if you have already cloned the repository, update with:
git submodule update --init --recursive
```

## Prerequisites 

The [VST2_SDK](https://web.archive.org/web/20181016150224/https://download.steinberg.net/sdk_downloads/vstsdk3610_11_06_2018_build_37.zip) should be placed in the 'SDKs' folder like so:
```
SDKs/VST2_SDK
```

**MacOSX, Linux and Windows (x86_64/amd64)** users must install a custom Intel MKL library. Detailed instructions on how to do this can be found [here](https://github.com/leomccormack/Spatial_Audio_Framework/blob/master/CUSTOM_INTEL_MKL_INTRUCTIONS.md). 

**Raspberry Pi (ARM)** users instead require OpenBLAS and LAPACKE libraries:
``` 
sudo apt-get install liblapack3 liblapack-dev libopenblas-base libopenblas-dev liblapacke-dev
```

**Linux (x86_64/amd64 and ARM)** users must also install the following libraries (the former line for JUCE, and the latter line for the Spatial_Audio_Framework):

```
sudo apt-get install x11proto-xinerama-dev libwebkit2gtk-4.0-dev libgtk-3-dev x11proto-xext-dev libcurl4-openssl-dev libasound2-dev
sudo apt-get install libhdf5-dev libnetcdf-dev libnetcdff-dev
```

## Building all plug-ins via scripts

**MacOSX/Linux users** may run the following bash script via the Terminal to build all of the plugins:

```
./build-plugins.sh all
# Note: MacOSX users may need to first install and enable Xcode Command Line Tools:
xcode-select --install 
sudo xcode-select -s /Applications/Xcode.app/Contents/Developer 
```

**Windows users** may instead run the following batch script via the "x64 Developer Command Prompt for VS.exe":

```
build-plugins.bat <path/to/Projucer.exe>
```

### Additional scripts and options for MacOSX/Linux users

The repository also includes the following install scripts:
```
./install-juce.sh  # builds a GPLv3 version of the Projucer App and places it in the "SDKs" folder
./install-vst2_sdk.sh  # downloads, unzips, and places the VST2_SDK in the "SDKs" folder
```

The build.plugins.sh script also supports many additional options:
```
./build-plugins.sh projuce  # generates Linux makefiles and Xcode/VisualStudio project files for all plugins
./build-plugins.sh clean  # cleans all plugins 
./build-plugins.sh build  # builds all plugins
./build-plugins.sh all  # projuces, cleans, and then builds all plugins
./build-plugins.sh _SPARTA_ambiBIN_ all  # projuces, cleans, and builds only "sparta_ambiBIN.vst"
./build-plugins.sh _SPARTA_ambiBIN_ build  # builds only "sparta_ambiBIN.vst"
./build-plugins.sh _SPARTA_ambiBIN_ projucer  # opens the "sparta_ambiBIN.jucer" file with the Projucer App
```
 
 ## Building the plug-ins via CMake 

The plug-ins may also be built with CMake (version 3.15 or higher):
 ```
 mkdir build
 cmake -S . -B build -DSAF_ENABLE_SOFA_READER=1 -DSAF_BUILD_TESTS=1
 # Linux users must link with an installed shared netcdf library:
 -DNETCDF_LIBRARY="/usr/lib/x86_64-linux-gnu/libnetcdf.so"
 # Same for MSYS2 users
 -DNETCDF_LIBRARY="/c/msys64/mingw64/lib/libnetcdf.dll.a"
 cd build
 make
 ```
 
 Note, however, that this is relatively new feature which has not been fully implemented and tested. Therefore, please let us know if you encounter any problems or are willing to contribute :- )
 
 
## Building the plug-ins without scripts

First manually open each .jucer file with the Projucer App and click "Save Project". This will generate Visual Studio (2015/2017) solution files, Xcode project files, Linux Makefiles (amd64), and Raspberry Pi Linux Makefiles (ARM), which are placed in:

```
audio_plugins/_SPARTA_X_/make/
```

To generate project files for other IDEs, you may open and configure the included .jucer files accordingly.


## Known issues

* Linux versions are quite experimental, but have been tested and largely work for us (we have experienced some graphical glitches, but these are consistent with other JUCE-made plugins).  However, please report any weird behaviour. 
* Raspberry PI versions are also quite experimental, and experience some graphical glitches, but are mostly working. 
* Due to missing code in the JUCE framework: on MacOSX, the camera ID cannot be changed for the visualisation plugins. And on Linux, the camera cannot be used at all.

Please let us know if you encounter any other issues (contact via email: leo.mccormack@aalto.fi, or raise a github "issue").

## Contributing

Suggestions and contributions to the code are both welcomed and encouraged. Feel free to branch off the 'develop' branch and submit pull requests. Note, however, that if the changes/additions are major, then consider first discussing it via a github "issue" or by contacting the developers directly via email. We may also be able to help in the implementation if needed.

## Developers

* **Leo McCormack** - C/C++ programmer and algorithm design (contact: leo.mccormack(at)aalto.fi)
* **Symeon Delikaris-Manias** - algorithm design
* **Archontis Politis** -  algorithm design
* **Ville Pulkki** - algorithm design
* **Marc Lavallée** - bash scripter

## License

This project is licensed under the GPLv3 License - see the [LICENSE](LICENSE) file for details
