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

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DDEBUG=1 -D_DEBUG=1 -DFRAME_SIZE=128 -DSAF_USE_INTEL_MKL -DJUCER_LINUX_MAKE_874B249D=1 -DJUCE_APP_VERSION=1.0.1 -DJUCE_APP_VERSION_HEX=0x10001 $(shell pkg-config --cflags alsa freetype2 x11 xext xinerama webkit2gtk-4.0 gtk+-x11-3.0 libcurl) -pthread -I../../../../SDKs/modules/juce_audio_processors/format_types/VST3_SDK -I../../juce/sparta_beamformer/JuceLibraryCode -I../../../../SDKs/modules -I../../../../SDKs/Spatial_Audio_Framework/framework/include -I../../../../SDKs/Spatial_Audio_Framework/examples/beamformer/include -I../../../../SDKs/Spatial_Audio_Framework/dependencies/Linux/include -I../../../../SDKs/VST2_SDK $(CPPFLAGS)

  JUCE_CPPFLAGS_VST := -DJucePlugin_Build_VST=1 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0 -DJucePlugin_Build_Unity=0
  JUCE_CFLAGS_VST := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST := -shared -Wl,--no-undefined
  JUCE_TARGET_VST := sparta_beamformer_debug.so

  JUCE_CPPFLAGS_SHARED_CODE := -DJucePlugin_Build_VST=1 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0 -DJucePlugin_Build_Unity=0 -DJUCE_SHARED_CODE=1
  JUCE_TARGET_SHARED_CODE := sparta_beamformer_debug.a

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -g -ggdb -O0 -flto $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++14 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell pkg-config --libs alsa freetype2 x11 xext xinerama webkit2gtk-4.0 gtk+-x11-3.0 libcurl) -flto -L/usr/lib -lsaf_mkl_custom -lGL -ldl -lpthread -lrt $(LDFLAGS)

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

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DNDEBUG=1 -DFRAME_SIZE=128 -DSAF_USE_INTEL_MKL -DJUCER_LINUX_MAKE_874B249D=1 -DJUCE_APP_VERSION=1.0.1 -DJUCE_APP_VERSION_HEX=0x10001 $(shell pkg-config --cflags alsa freetype2 x11 xext xinerama webkit2gtk-4.0 gtk+-x11-3.0 libcurl) -pthread -I../../../../SDKs/modules/juce_audio_processors/format_types/VST3_SDK -I../../juce/sparta_beamformer/JuceLibraryCode -I../../../../SDKs/modules -I../../../../SDKs/Spatial_Audio_Framework/framework/include -I../../../../SDKs/Spatial_Audio_Framework/examples/beamformer/include -I../../../../SDKs/Spatial_Audio_Framework/dependencies/Linux/include -I../../../../SDKs/VST2_SDK $(CPPFLAGS)

  JUCE_CPPFLAGS_VST := -DJucePlugin_Build_VST=1 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0 -DJucePlugin_Build_Unity=0
  JUCE_CFLAGS_VST := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST := -shared -Wl,--no-undefined
  JUCE_TARGET_VST := sparta_beamformer.so

  JUCE_CPPFLAGS_SHARED_CODE := -DJucePlugin_Build_VST=1 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0 -DJucePlugin_Build_Unity=0 -DJUCE_SHARED_CODE=1
  JUCE_TARGET_SHARED_CODE := sparta_beamformer.a

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -O3 -flto $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++14 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell pkg-config --libs alsa freetype2 x11 xext xinerama webkit2gtk-4.0 gtk+-x11-3.0 libcurl) -fvisibility=hidden -flto -L/usr/lib -lsaf_mkl_custom -lGL -ldl -lpthread -lrt $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS_ALL := \

OBJECTS_VST := \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST2_488fa83b.o \

OBJECTS_SHARED_CODE := \
  $(JUCE_OBJDIR)/PluginEditor_758fa7c0.o \
  $(JUCE_OBJDIR)/PluginProcessor_9be2e769.o \
  $(JUCE_OBJDIR)/pannerView_14409603.o \
  $(JUCE_OBJDIR)/outputCoordsView_5498e564.o \
  $(JUCE_OBJDIR)/beamformer_c57f92d4.o \
  $(JUCE_OBJDIR)/beamformer_internal_d13ee512.o \
  $(JUCE_OBJDIR)/afSTFTlib_78f88bce.o \
  $(JUCE_OBJDIR)/fft4g_aaeef644.o \
  $(JUCE_OBJDIR)/vecTools_2eaacd34.o \
  $(JUCE_OBJDIR)/saf_cdf4sap_a8c8f1a2.o \
  $(JUCE_OBJDIR)/saf_hoa_feb0e170.o \
  $(JUCE_OBJDIR)/saf_hoa_internal_9c6645f6.o \
  $(JUCE_OBJDIR)/saf_hrir_de6b4448.o \
  $(JUCE_OBJDIR)/saf_hrir_internal_931961e.o \
  $(JUCE_OBJDIR)/saf_sh_f0d9cd48.o \
  $(JUCE_OBJDIR)/saf_sh_internal_200d2d1e.o \
  $(JUCE_OBJDIR)/saf_calloc_74e691b6.o \
  $(JUCE_OBJDIR)/saf_complex_11cd68f6.o \
  $(JUCE_OBJDIR)/saf_free_12f350b0.o \
  $(JUCE_OBJDIR)/saf_loudspeaker_presets_4fdc99e8.o \
  $(JUCE_OBJDIR)/saf_malloc_83b2526c.o \
  $(JUCE_OBJDIR)/saf_sensorarray_presets_1274fdda.o \
  $(JUCE_OBJDIR)/saf_sort_28fe2b62.o \
  $(JUCE_OBJDIR)/saf_veclib_eed777b5.o \
  $(JUCE_OBJDIR)/saf_vbap_3e11b148.o \
  $(JUCE_OBJDIR)/saf_vbap_internal_2975c91e.o \
  $(JUCE_OBJDIR)/include_juce_audio_basics_e4f896fd.o \
  $(JUCE_OBJDIR)/include_juce_audio_devices_5da6f4af.o \
  $(JUCE_OBJDIR)/include_juce_audio_formats_108df7ae.o \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_utils_df45971b.o \
  $(JUCE_OBJDIR)/include_juce_audio_processors_f415a399.o \
  $(JUCE_OBJDIR)/include_juce_core_42e798e.o \
  $(JUCE_OBJDIR)/include_juce_cryptography_e762065b.o \
  $(JUCE_OBJDIR)/include_juce_data_structures_20f05250.o \
  $(JUCE_OBJDIR)/include_juce_events_b6c79788.o \
  $(JUCE_OBJDIR)/include_juce_graphics_a21b317a.o \
  $(JUCE_OBJDIR)/include_juce_gui_basics_1a67a6f8.o \
  $(JUCE_OBJDIR)/include_juce_gui_extra_454d247.o \
  $(JUCE_OBJDIR)/include_juce_opengl_b179c41e.o \

.PHONY: clean all strip VST

all : VST

VST : $(JUCE_OUTDIR)/$(JUCE_TARGET_VST)


$(JUCE_OUTDIR)/$(JUCE_TARGET_VST) : $(OBJECTS_VST) $(RESOURCES) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE)
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors alsa freetype2 x11 xext xinerama webkit2gtk-4.0 gtk+-x11-3.0 libcurl
	@echo Linking "sparta_beamformer - VST"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_VST) $(OBJECTS_VST) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(JUCE_LDFLAGS_VST) $(RESOURCES) $(TARGET_ARCH)

$(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) : $(OBJECTS_SHARED_CODE) $(RESOURCES)
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors alsa freetype2 x11 xext xinerama webkit2gtk-4.0 gtk+-x11-3.0 libcurl
	@echo Linking "sparta_beamformer - Shared Code"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(AR) -rcs $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(OBJECTS_SHARED_CODE)

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST2_488fa83b.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_audio_plugin_client_VST2.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_VST2.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_VST) $(JUCE_CFLAGS_VST) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginEditor_758fa7c0.o: ../../src/PluginEditor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginProcessor_9be2e769.o: ../../src/PluginProcessor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginProcessor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pannerView_14409603.o: ../../src/pannerView.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pannerView.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/outputCoordsView_5498e564.o: ../../src/outputCoordsView.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling outputCoordsView.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/beamformer_c57f92d4.o: ../../../../SDKs/Spatial_Audio_Framework/examples/beamformer/src/beamformer.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling beamformer.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/beamformer_internal_d13ee512.o: ../../../../SDKs/Spatial_Audio_Framework/examples/beamformer/src/beamformer_internal.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling beamformer_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/afSTFTlib_78f88bce.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_afstft/afSTFTlib.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling afSTFTlib.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fft4g_aaeef644.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_afstft/fft4g.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fft4g.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/vecTools_2eaacd34.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_afstft/vecTools.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling vecTools.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_cdf4sap_a8c8f1a2.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_cdf4sap/saf_cdf4sap.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_cdf4sap.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_hoa_feb0e170.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_hoa/saf_hoa.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_hoa.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_hoa_internal_9c6645f6.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_hoa/saf_hoa_internal.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_hoa_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_hrir_de6b4448.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_hrir/saf_hrir.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_hrir.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_hrir_internal_931961e.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_hrir/saf_hrir_internal.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_hrir_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_sh_f0d9cd48.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_sh/saf_sh.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_sh.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_sh_internal_200d2d1e.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_sh/saf_sh_internal.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_sh_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_calloc_74e691b6.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_utilities/saf_calloc.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_calloc.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_complex_11cd68f6.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_utilities/saf_complex.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_complex.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_free_12f350b0.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_utilities/saf_free.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_free.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_loudspeaker_presets_4fdc99e8.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_utilities/saf_loudspeaker_presets.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_loudspeaker_presets.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_malloc_83b2526c.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_utilities/saf_malloc.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_malloc.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_sensorarray_presets_1274fdda.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_utilities/saf_sensorarray_presets.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_sensorarray_presets.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_sort_28fe2b62.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_utilities/saf_sort.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_sort.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_veclib_eed777b5.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_utilities/saf_veclib.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_veclib.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_vbap_3e11b148.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_vbap/saf_vbap.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_vbap.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saf_vbap_internal_2975c91e.o: ../../../../SDKs/Spatial_Audio_Framework/framework/saf_vbap/saf_vbap_internal.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saf_vbap_internal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_basics_e4f896fd.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_audio_basics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_devices_5da6f4af.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_audio_devices.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_devices.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_formats_108df7ae.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_audio_formats.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_formats.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_utils_df45971b.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_audio_plugin_client_utils.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_processors_f415a399.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_audio_processors.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_processors.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_core_42e798e.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_core.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_cryptography_e762065b.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_cryptography.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_cryptography.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_data_structures_20f05250.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_data_structures.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_data_structures.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_events_b6c79788.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_events.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_events.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_graphics_a21b317a.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_graphics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_graphics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_basics_1a67a6f8.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_gui_basics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_gui_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_extra_454d247.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_gui_extra.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_gui_extra.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_opengl_b179c41e.o: ../../juce/sparta_beamformer/JuceLibraryCode/include_juce_opengl.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_opengl.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

clean:
	@echo Cleaning sparta_beamformer
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping sparta_beamformer
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

-include $(OBJECTS_VST:%.o=%.d)
-include $(OBJECTS_SHARED_CODE:%.o=%.d)
