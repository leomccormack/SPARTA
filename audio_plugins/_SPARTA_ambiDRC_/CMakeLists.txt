
cmake_minimum_required(VERSION 3.15)

project(sparta_ambiDRC VERSION 1.3.1)
message(STATUS "  ${PROJECT_NAME}")

# juce helper function to create a library, which is configured as a JUCE plugin
juce_add_plugin(${PROJECT_NAME}
    VERSION                     "${PROJECT_VERSION}"
    COMPANY_NAME                "AALTO"                         
    IS_SYNTH                    FALSE                               
    NEEDS_MIDI_INPUT            FALSE                      
    NEEDS_MIDI_OUTPUT           FALSE                  
    IS_MIDI_EFFECT              FALSE                       
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE           
    COPY_PLUGIN_AFTER_BUILD     TRUE     # Where does this go in Windows + Linux?
    PLUGIN_MANUFACTURER_CODE    LEOM                
    PLUGIN_CODE                 ADRC                     
    FORMATS                     ${BUILD_PLUGIN_FORMATS}      # ( VST AAX Unity VST3 AU AUv3 Standalone )
    PRODUCT_NAME                "${PROJECT_NAME}"
    LV2URI                      "http://AALTO.${PROJECT_NAME}.${PROJECT_VERSION}"
)   

# Generates "JuceHeader.h", and adds its path to the include paths of the target
juce_generate_juce_header(${PROJECT_NAME})  

# Add plugin source files
target_sources(${PROJECT_NAME} 
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/colourGradient.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PluginEditor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PluginProcessor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PluginEditor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PluginProcessor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TFview.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TFview.cpp
)

# Add any extra JUCE-specific pre-processor definitions
target_compile_definitions(${PROJECT_NAME}
PUBLIC 
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)
 
# Link with saf example, and the required juce modules
target_link_libraries(${PROJECT_NAME} 
PRIVATE 
    saf_example_ambi_drc
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_audio_plugin_client
    juce::juce_audio_utils
)

# The JUCE OpenGL module seems to have some issues on Linux...
if(UNIX AND NOT APPLE)
    message(STATUS "    (juce_opengl module disabled)")
    target_compile_definitions(${PROJECT_NAME}
    PUBLIC 
        PLUGIN_EDITOR_DISABLE_OPENGL=1
    )
else()
    target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        juce::juce_opengl
    )
endif()
