# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

# build with "V=1" for verbose builds
ifeq ($(V), 1)
V_AT =
else
V_AT = @
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef STRIP
  STRIP=strip
endif

ifndef AR
  AR=ar
endif

ifndef CONFIG
  CONFIG=Debug
endif

JUCE_ARCH_LABEL := $(shell uname -m)

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := ../../../../lib

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DDEBUG=1 -D_DEBUG=1 -DFRAME_SIZE=128 -DSAF_USE_OPEN_BLAS_AND_LAPACKE -DSAF_ENABLE_SOFA_READER -DJUCER_LINUX_MAKE_3E669B1F=1 -DJUCE_APP_VERSION=1.3.8 -DJUCE_APP_VERSION_HEX=0x10308 $(shell pkg-config --cflags alsa x11 xinerama xext freetype2 webkit2gtk-4.0 gtk+-x11-3.0 libcurl) -pthread -I../../../../SDKs/modules/juce_audio_processors/format_types/VST3_SDK -I../../juce/sparta_ambiBIN/JuceLibraryCode -I../../../../SDKs/modules -I../../../../SDKs/Spatial_Audio_Framework/framework/include -I../../../../SDKs/Spatial_Audio_Framework/examples/ambi_bin/include -I../../../../SDKs/VST2_SDK -I/home/pi/openblas-0.2.20/include -I/usr/include $(CPPFLAGS)

  JUCE_CPPFLAGS_VST := -DJucePlugin_Build_VST=1 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0 -DJucePlugin_Build_Unity=0
  JUCE_CFLAGS_VST := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST := -shared -Wl,--no-undefined
  JUCE_TARGET_VST := sparta_ambiBIN_debug.so

  JUCE_CPPFLAGS_SHARED_CODE := -DJucePlugin_Build_VST=1 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0 -DJucePlugin_Build_Unity=0 -DJUCE_SHARED_CODE=1
  JUCE_TARGET_SHARED_CODE := sparta_ambiBIN_debug.a

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -g -ggdb -O0 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++14 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell pkg-config --libs alsa x11 xinerama xext freetype2 webkit2gtk-4.0 gtk+-x11-3.0 libcurl) -L/usr/lib -lopenblas -L/usr/lib/arm-linux-gnueabihf -llapacke -L/usr/lib/arm-linux-gnueabihf -lnetcdf -lrt -ldl -lpthread -lGL $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := ../../../../lib

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DNDEBUG=1 -DFRAME_SIZE=128 -DSAF_USE_OPEN_BLAS_AND_LAPACKE -DSAF_ENABLE_SOFA_READER -DJUCER_LINUX_MAKE_3E669B1F=1 -DJUCE_APP_VERSION=1.3.8 -DJUCE_APP_VERSION_HEX=0x10308 $(shell pkg-config --cflags alsa x11 xinerama xext freetype2 webkit2gtk-4.0 gtk+-x11-3.0 libcurl) -pthread -I../../../../SDKs/modules/juce_audio_processors/format_types/VST3_SDK -I../../juce/sparta_ambiBIN/JuceLibraryCode -I../../../../SDKs/modules -I../../../../SDKs/Spatial_Audio_Framework/framework/include -I../../../../SDKs/Spatial_Audio_Framework/examples/ambi_bin/include -I../../../../SDKs/VST2_SDK -I/home/pi/openblas-0.2.20/include -I/usr/include $(CPPFLAGS)

  JUCE_CPPFLAGS_VST := -DJucePlugin_Build_VST=1 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0 -DJucePlugin_Build_Unity=0
  JUCE_CFLAGS_VST := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST := -shared -Wl,--no-undefined
  JUCE_TARGET_VST := sparta_ambiBIN.so

  JUCE_CPPFLAGS_SHARED_CODE := -DJucePlugin_Build_VST=1 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0 -DJucePlugin_Build_Unity=0 -DJUCE_SHARED_CODE=1
  JUCE_TARGET_SHARED_CODE := sparta_ambiBIN.a

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -O3 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++14 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell pkg-config --libs alsa x11 xinerama xext freetype2 webkit2gtk-4.0 gtk+-x11-3.0 libcurl) -fvisibility=hidden -L/usr/lib -lopenblas -L/usr/lib/arm-linux-gnueabihf -llapacke -L/usr/lib/arm-linux-gnueabihf -lnetcdf -lrt -ldl -lpthread -lGL $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS_ALL := \

OBJECTS_VST := \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST2_c654022b.o \

OBJECTS_SHARED_CODE := \
  $(JUCE_OBJDIR)/PluginProcessor_9be2e769.o \
  $(JUCE_OBJDIR)/PluginEditor_758fa7c0.o \
  $(JUCE_OBJDIR)/ambi_bin_3edfbfb4.o \
  $(JUCE_OBJDIR)/ambi_bin_internal_43933432.o \
  $(JUCE_OBJDIR)/saf_cdf4sap_fcdc8d1a.o \
  $(JUCE_OBJDIR)/saf_hoa_e8f374e8.o \
  $(JUCE_OBJDIR)/saf_hoa_internal_cac6197e.o \
  $(JUCE_OBJDIR)/saf_default_hrirs_2bfe5f3f.o \
  $(JUCE_OBJDIR)/saf_hrir_4256d9c0.o \
  $(JUCE_OBJDIR)/saf_hrir_internal_1eeaa7a6.o \
  $(JUCE_OBJDIR)/saf_sofa_reader_8b298948.o \
  $(JUCE_OBJDIR)/saf_sh_671adec0.o \
  $(JUCE_OBJDIR)/saf_sh_internal_85dc42a6.o \
  $(JUCE_OBJDIR)/saf_complex_af68066e.o \
  $(JUCE_OBJDIR)/saf_decor_1f784023.o \
  $(JUCE_OBJDIR)/saf_erb_eb10e253.o \
  $(JUCE_OBJDIR)/saf_error_6b60dc06.o \
  $(JUCE_OBJDIR)/saf_fft_eb19c8f2.o \
  $(JUCE_OBJDIR)/saf_filters_ce7e9ef9.o \
  $(JUCE_OBJDIR)/saf_loudspeaker_presets_7edec360.o \
  $(JUCE_OBJDIR)/saf_matrixConv_981a9ee1.o \
  $(JUCE_OBJDIR)/saf_sensorarray_presets_41772752.o \
  $(JUCE_OBJDIR)/saf_sort_8ecd40ea.o \
  $(JUCE_OBJDIR)/saf_veclib_1d374b3d.o \
  $(JUCE_OBJDIR)/saf_vbap_a1fd46c0.o \
  $(JUCE_OBJDIR)/saf_vbap_internal_3f2edaa6.o \
  $(JUCE_OBJDIR)/afSTFTlib_53a89331.o \
  $(JUCE_OBJDIR)/convhull_3d_6ea2ea7e.o \
  $(JUCE_OBJDIR)/kiss_fft_7a7b7f87.o \
  $(JUCE_OBJDIR)/kiss_fftr_d4f56a95.o \
  $(JUCE_OBJDIR)/md_malloc_f5f270c0.o \
  $(JUCE_OBJDIR)/include_juce_audio_basics_128058ed.o \
  $(JUCE_OBJDIR)/include_juce_audio_devices_e11770bf.o \
  $(JUCE_OBJDIR)/include_juce_audio_formats_93fe73be.o \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_utils_1a0c7b2b.o \
  $(JUCE_OBJDIR)/include_juce_audio_processors_b30aed89.o \
  $(JUCE_OBJDIR)/include_juce_core_80cf2b7e.o \
  $(JUCE_OBJDIR)/include_juce_cryptography_14e9c84b.o \
  $(JUCE_OBJDIR)/include_juce_data_structures_8a320a60.o \
  $(JUCE_OBJDIR)/include_juce_events_8e038d78.o \
  $(JUCE_OBJDIR)/include_juce_graphics_9a316b6a.o \
  $(JUCE_OBJDIR)/include_juce_gui_basics_65d724e8.o \
  $(JUCE_OBJDIR)/include_juce_gui_extra_f05d657.o \
  $(JUCE_OBJDIR)/include_juce_opengl_88b5ba0e.o \
  $(JUCE_OBJDIR)/include_juce_osc_c6eacc4a.o \

.PHONY: clean all strip VST

all : VST

VST : $(JUCE_OUTDIR)/$(JUCE_TARGET_VST)


$(JUCE_OUTDIR)/$(JUCE_TARGET_VST) : $(OBJECTS_VST) $(RESOURCES) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE)
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors alsa x11 xinerama xext freetype2 webkit2gtk-4.0 gtk+-x11-3.0 libcurl
	@echo Linking "sparta_ambiBIN - VST"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_VST) $(OBJECTS_VST) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(JUCE_LDFLAGS_VST) $(RESOURCES) $(TARGET_ARCH)

$(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) : $(OBJECTS_SHARED_CODE) $(RESOURCES)
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors alsa x11 xinerama xext freetype2 webkit2gtk-4.0 gtk+-x11-3.0 libcurl
	@echo Linking "sparta_ambiBIN - Shared Code"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(AR) -rcs $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(OBJECTS_SHARED_CODE)

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST2_c654022b.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_audio_plugin_client_VST2.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_VST2.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_VST) $(JUCE_CFLAGS_VST) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginProcessor_9be2e769.o: ../../src/PluginProcessor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginProcessor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginEditor_758fa7c0.o: ../../src/PluginEditor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ambi_bin_3edfbfb4.o: ../../../../SDKs/Spatial_Audio_Framework/examples/ambi_bin/src/ambi_bin.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ambi_bin.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ambi_bin_internal_43933432.o: ../../../../SDKs/Spatial_Audio_Framework/examples/ambi_bin/src/ambi_bin_internal.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ambi_bin_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_cdf4sap_fcdc8d1a.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_cdf4sap/saf_cdf4sap.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_cdf4sap.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_hoa_e8f374e8.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_hoa/saf_hoa.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_hoa.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_hoa_internal_cac6197e.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_hoa/saf_hoa_internal.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_hoa_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_default_hrirs_2bfe5f3f.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_hrir/saf_default_hrirs.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_default_hrirs.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_hrir_4256d9c0.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_hrir/saf_hrir.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_hrir.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_hrir_internal_1eeaa7a6.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_hrir/saf_hrir_internal.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_hrir_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_sofa_reader_8b298948.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_hrir/saf_sofa_reader.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_sofa_reader.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_sh_671adec0.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_sh/saf_sh.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_sh.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_sh_internal_85dc42a6.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_sh/saf_sh_internal.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_sh_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_complex_af68066e.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_complex.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_complex.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_decor_1f784023.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_decor.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_decor.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_erb_eb10e253.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_erb.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_erb.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_error_6b60dc06.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_error.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_error.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_fft_eb19c8f2.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_fft.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_fft.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_filters_ce7e9ef9.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_filters.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_filters.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_loudspeaker_presets_7edec360.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_loudspeaker_presets.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_loudspeaker_presets.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_matrixConv_981a9ee1.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_matrixConv.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_matrixConv.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_sensorarray_presets_41772752.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_sensorarray_presets.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_sensorarray_presets.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_sort_8ecd40ea.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_sort.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_sort.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_veclib_1d374b3d.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_utilities/saf_veclib.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_veclib.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_vbap_a1fd46c0.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_vbap/saf_vbap.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_vbap.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_vbap_internal_3f2edaa6.o: ../../../../SDKs/Spatial_Audio_Framework/framework/modules/saf_vbap/saf_vbap_internal.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_vbap_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/afSTFTlib_53a89331.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/afSTFT/afSTFTlib.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling afSTFTlib.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/convhull_3d_6ea2ea7e.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/convhull_3d/convhull_3d.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling convhull_3d.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/kiss_fft_7a7b7f87.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/kissFFT/kiss_fft.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling kiss_fft.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/kiss_fftr_d4f56a95.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/kissFFT/kiss_fftr.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling kiss_fftr.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/md_malloc_f5f270c0.o: ../../../../SDKs/Spatial_Audio_Framework/framework/resources/md_malloc/md_malloc.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling md_malloc.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_basics_128058ed.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_audio_basics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_devices_e11770bf.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_audio_devices.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_devices.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_formats_93fe73be.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_audio_formats.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_formats.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_utils_1a0c7b2b.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_audio_plugin_client_utils.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_processors_b30aed89.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_audio_processors.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_processors.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_core_80cf2b7e.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_core.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_cryptography_14e9c84b.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_cryptography.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_cryptography.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_data_structures_8a320a60.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_data_structures.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_data_structures.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_events_8e038d78.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_events.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_events.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_graphics_9a316b6a.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_graphics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_graphics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_basics_65d724e8.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_gui_basics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_gui_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_extra_f05d657.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_gui_extra.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_gui_extra.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_opengl_88b5ba0e.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_opengl.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_opengl.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_osc_c6eacc4a.o: ../../juce/sparta_ambiBIN/JuceLibraryCode/include_juce_osc.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_osc.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

clean:
	@echo Cleaning sparta_ambiBIN
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping sparta_ambiBIN
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

-include $(OBJECTS_VST:%.o=%.d)
-include $(OBJECTS_SHARED_CODE:%.o=%.d)
