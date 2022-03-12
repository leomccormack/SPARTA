
# SPARTA Banner:
message(STATUS "Configuring SPARTA (Version ${PROJECT_VERSION})...")

# Add the SPARTA plugins to the build tree
add_subdirectory(_SPARTA_ambiDRC_)
add_subdirectory(_SPARTA_ambiENC_)
add_subdirectory(_SPARTA_ambiRoomSim_)
add_subdirectory(_SPARTA_array2sh_)
add_subdirectory(_SPARTA_beamformer_)
add_subdirectory(_SPARTA_decorrelator_)
add_subdirectory(_SPARTA_matrixConv_)
add_subdirectory(_SPARTA_multiConv_)
add_subdirectory(_SPARTA_panner_)
add_subdirectory(_SPARTA_pitchShifter_)
add_subdirectory(_SPARTA_rotator_)

# These plug-ins rely on the JUCE CameraDevice, which is sadly not implemented for Linux users:
if(NOT UNIX OR APPLE)
    add_subdirectory(_SPARTA_dirass_)
    add_subdirectory(_SPARTA_powermap_)
    add_subdirectory(_SPARTA_sldoa_)
else()
    message(STATUS "  Note: disabling the plug-ins which rely on JUCE CameraDevice.")
endif()

# These plug-ins rely on the saf_sofa_reader module being enabled:
if(SAF_ENABLE_SOFA_READER_MODULE)
    add_subdirectory(_SPARTA_ambiBIN_)
    add_subdirectory(_SPARTA_ambiDEC_)
    add_subdirectory(_SPARTA_binauraliser_)
    add_subdirectory(_SPARTA_spreader_)
    add_subdirectory(_SPARTA_binauraliser_nf_)
    add_subdirectory(_SPARTA_6DoFconv_)
else()
    message(STATUS "  Note: disabling the plug-ins which rely on the saf_sofa_reader module.")
endif()
