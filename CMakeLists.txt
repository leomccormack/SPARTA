cmake_minimum_required(VERSION 3.15)

project(sparta_head VERSION 1.7.1)

# Build everything as "Release" by default
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

# Configure CMake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Platform specific flags and definitions
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
elseif(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10" CACHE STRING "Minimum OS X deployment version" FORCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -Wall -Wextra -Wno-inconsistent-missing-override")  
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
    add_definitions(
        #-std=c++11
        -DLINUX=1   
    )
endif()

# Disable JUCE extras and examples:
option(JUCE_BUILD_EXTRAS   "Build JUCE Extras"   OFF)
option(JUCE_BUILD_EXAMPLES "Build JUCE Examples" OFF)

# Disable SAF tests, but enable SAF examples:
option(SAF_BUILD_TESTS    "Build SAF unit tests." OFF)
option(SAF_BUILD_EXAMPLES "Build SAF examples."   ON)

# Add JUCE, Spatial_Audio_Framework, and VST2_SDK to the project
add_subdirectory(SDKs) 


# Configure SPARTA plugins
option(BUILD_PLUGIN_FORMAT_VST2 "Build VST2 plugins" ON)
option(BUILD_PLUGIN_FORMAT_VST3 "Build VST3 plugins" OFF)
option(BUILD_PLUGIN_FORMAT_AU   "Build AU plugins"   OFF)
option(BUILD_PLUGIN_FORMAT_LV2  "Build LV2 plugins"  OFF)
add_subdirectory(audio_plugins)