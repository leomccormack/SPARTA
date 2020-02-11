:: Script to open all .jucer files, save the project, and then compile the visual studio solution files
@echo off
echo "Batch script to build all SPARTA plugins. Run using: x64 Command Prompt for VS 2017." 
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
cd /d "%~dp0"

IF NOT EXIST %1 (
    echo "Please use the following syntax: build-plugins.bat <PathToProjucer.exe>"
) ELSE (
	IF NOT EXIST "../lib" (
		echo "Creating ../lib directory for output binaries"
		mkdir "../lib"
	)

	echo "Generating Visual Studio solution files"
	for /r %%i in (*.jucer) do (
		::echo %%~ti  %%~zi  %%i
		start "" /wait %1 --resave %%i
	)
	
	echo "Compiling Visual Studio 2017 solution files"
	for /d /r . %%d in (VisualStudio2017) do (
		@if exist "%%d"  (
			cd %%d
			for /r %%i in (*.sln) do ( 
				echo "Now compiling %%i"
				msbuild %%i /p:Configuration="Release",Platform=x64 /t:Clean,Build
			)  
			cd /d "%~dp0"
		)
	)
)
