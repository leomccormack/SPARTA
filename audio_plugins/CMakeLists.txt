
# SPARTA Banner:
message("
      _____     _____     _____     _____     _____     _____  
    (  ____ ) (  ___  ) (  ___  ) (  ___  ) (__   __) (  ___  )
    | (    |/ | (   ) | | (   ) | | (   ) |    | |    | (   ) |
    | (_____  | (___) | | (___) | | (___) |    | |    | (___) |
    (_____  ) |  _____) |  ___  | |     __)    | |    |  ___  |
          ) | | (       | (   ) | | |( )       | |    | (   ) |
    /|____) | | |       | |   | | | | ( )_     | |    | |   | |
    (_______) |_|       |_|   |_| |_|  (__)    |_|    |_|   |_|  (Version ${PROJECT_VERSION})
")

# Add the SPARTA plugins to the build tree
add_subdirectory(_SPARTA_ambiDRC_)
add_subdirectory(_SPARTA_ambiENC_)
add_subdirectory(_SPARTA_array2sh_)
add_subdirectory(_SPARTA_beamformer_)
add_subdirectory(_SPARTA_dirass_)
add_subdirectory(_SPARTA_MatrixConv_)
add_subdirectory(_SPARTA_MultiConv_)
add_subdirectory(_SPARTA_panner_)
add_subdirectory(_SPARTA_pitchShifter_)
add_subdirectory(_SPARTA_powermap_)
add_subdirectory(_SPARTA_rotator_)
add_subdirectory(_SPARTA_sldoa_)

# These plug-ins rely on the saf_sofa_reader module being enabled:
if(SAF_ENABLE_SOFA_READER) 
    add_subdirectory(_SPARTA_ambiBIN_)
    add_subdirectory(_SPARTA_ambiDEC_)
    add_subdirectory(_SPARTA_binauraliser_)
endif()