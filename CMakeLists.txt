cmake_minimum_required(VERSION 3.15)

project(sparta_head VERSION 1.4.1)

# Build everything as "Release" by default
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

# Disable JUCE extras and examples:
option(JUCE_BUILD_EXTRAS   "Build JUCE Extras"   OFF)
option(JUCE_BUILD_EXAMPLES "Build JUCE Examples" OFF)

# Disable SAF tests, but enable SAF examples:
option(SAF_BUILD_TESTS    "Build SAF unit tests." OFF)
option(SAF_BUILD_EXAMPLES "Build SAF examples."   ON)

# Add JUCE, Spatial_Audio_Framework, and VST2_SDK to the project
add_subdirectory(SDKs) 
juce_set_vst2_sdk_path(${CMAKE_CURRENT_SOURCE_DIR}/SDKs/VST2_SDK)

# Configure SPARTA plugins
add_subdirectory(audio_plugins)