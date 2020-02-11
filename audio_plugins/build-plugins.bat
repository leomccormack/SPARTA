:: "Batch script to build all SPARTA plugins. Run using: x64 Command Prompt for VS 2017." 
::
:: If you get "msbuild" command missing errors, then use (or wherever it is):
::call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
@echo off
cd /d "%~dp0"

:: ========================================================================= ::
:: Check VST2 SDK is where it should be
IF NOT EXIST "../SDKs/VST2_SDK" (
    echo The VST2 SDK was not found in the following folder: ../SDKs/VST2_SDK
	echo You can download the VST2 SDK from here: 
	echo "https://web.archive.org/web/20181016150224/https://download.steinberg.net/sdk_downloads/vstsdk3610_11_06_2018_build_37.zip"
	EXIT /B
)
:: Check that the JUCE modules are where they should be
IF NOT EXIST "../SDKs/modules" (
    echo The JUCE "modules" folder was not found in the following folder: ../SDKs/modules
	echo These folders can be found here: "https://shop.juce.com/get-juce/download"
	EXIT /B
)
:: Check that the Spatial_Audio_Framework is where it should be & its dependencies
IF NOT EXIST "../SDKs/Spatial_Audio_Framework" (
    echo The "Spatial_Audio_Framework" was not found in the following folder: ../SDKs/Spatial_Audio_Framework
	echo It can be found here:
	echo "https://github.com/leomccormack/Spatial_Audio_Framework"
	EXIT /B
)
IF NOT EXIST "../SDKs/Spatial_Audio_Framework/dependencies/Win64/lib/saf_mkl_custom.lib" (
    echo The "saf_mkl_custom.lib" file was not found in the following folder: Spatial_Audio_Framework/dependencies/Win64/lib/saf_mkl_custom.lib
	echo you can find instruction on how to acquire it from here:
	echo "https://github.com/leomccormack/Spatial_Audio_Framework/blob/master/CUSTOM_INTEL_MKL_INTRUCTIONS.md"
	EXIT /B
)
IF NOT EXIST "C:/Windows/System32/saf_mkl_custom.dll" (
    echo The "saf_mkl_custom.lib" file was not found in the following folder: Spatial_Audio_Framework/dependencies/Win64/lib/saf_mkl_custom.lib
	echo you can find instruction on how to acquire it from here:
	echo "https://github.com/leomccormack/Spatial_Audio_Framework/blob/master/CUSTOM_INTEL_MKL_INTRUCTIONS.md"
	EXIT /B
)
:: Check that the path to Projucer.exe is valid
IF NOT EXIST %1 (
    echo Please use the following syntax: build-plugins.bat "Path/To/Projucer.exe"
	echo "Projucer.exe" can be found here: "https://shop.juce.com/get-juce/download"
	EXIT /B
)
:: Check output directory exists
IF NOT EXIST "../lib" (
    echo Creating ../lib directory for output binaries
    mkdir "../lib"
)

:: ========================================================================= ::
echo "Generating Visual Studio solution files"
for /r %%i in (*.jucer) do (
    ::echo %%~ti  %%~zi  %%i
	start "" /wait %1 --resave %%i
)
	
:: ========================================================================= ::
echo "Compiling Visual Studio 2017 solution files"
for /d /r . %%d in (VisualStudio2017) do (
    @if exist "%%d"  (
		cd %%d
		for /r %%i in (*.sln) do ( 
			echo Now compiling %%i
			msbuild %%i /p:Configuration="Release",Platform=x64 /t:Clean,Build
		)  
		cd /d "%~dp0"
	)
)

