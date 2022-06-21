:: when this is called, working directory should be something like
:: [...]\SPARTA\audio_plugins\_SPARTA_6DoFconv_\make\win64\VisualStudio2017

set projectName=%~1
set outDir=%~2

:: juce runs the post-build script for both SharedCode and VST projects,
:: so we need to make sure we're in the latter

if not [%projectName:~-4%]==[_VST] goto end

:: use funny file extension to ensure DAWs don't treat NatNetLib as a VST...

set natNetDllPath=%outDir%..\VST\NatNetLib.nonvst-dll

if exist "%natNetDllPath%" goto end

copy ..\..\..\..\..\SDKs\NatNetSDK\lib\x64\NatNetLib.dll "%natNetDllPath%"

:end
