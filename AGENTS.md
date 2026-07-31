# SPARTA

C++ spatial audio plugin suite (VST/VST3/AU/LV2/AAX/Standalone) built with
[JUCE] + [Spatial_Audio_Framework] (SAF). Signal processing lives in the SAF
submodule; `audio_plugins/` is the JUCE GUI/host wrapper only.

## Build

```sh
git submodule update --init --recursive   # mandatory — SDK dirs are empty otherwise
cmake -S . -B build && cmake --build build
```

VST2 ON by default (requires proprietary `SDKs/VST2_SDK`). Other formats OFF
by default: `-DBUILD_PLUGIN_FORMAT_VST3=ON -DBUILD_PLUGIN_FORMAT_AU=ON`
`-DBUILD_PLUGIN_FORMAT_LV2=ON -DBUILD_PLUGIN_FORMAT_AAX=ON -DBUILD_PLUGIN_FORMAT_STANDALONE=ON`.

## Platform prerequisites

- **macOS**: no setup (uses Accelerate). Universal arm64+x86_64, min 12.0.
- **Linux/Windows x86_64**: Intel oneAPI MKL+IPP required. Run
  `SDKs/Spatial_Audio_Framework/scripts/install-safmkl.{sh,bat}` then
  `install-safipp.{sh,bat}`.
- **Linux ARM/Pi**: `apt install liblapack3 liblapack-dev libopenblas-dev liblapacke-dev`
- **Linux (all arches)**: `apt install libwebkit2gtk-4.0-dev libgtk-3-dev libx11-dev
  libxinerama-dev libxext-dev libcurl4-openssl-dev libasound2-dev`

### Build without MKL (fallback, x86_64)
If MKL is not available, build LAPACKE from source and use OpenBLAS:

```sh
sudo apt install libblas-dev liblapack3  # needed -dev packages
git submodule update --init --recursive
wget -qO- https://github.com/Reference-LAPACK/lapack/archive/refs/tags/v3.12.0.tar.gz | tar xz
mv lapack-3.12.0 lib/                        # keep it OUT of /tmp (tmp gets wiped)
cd lib/lapack-3.12.0 && mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DLAPACKE=ON -DCBLAS=OFF -DLAPACK=OFF -DBUILD_TESTING=OFF
make -j$(nproc) lapacke
cd /path/to/SPARTA
cmake -S . -B build \
  -DSAF_PERFORMANCE_LIB=SAF_USE_OPEN_BLAS_AND_LAPACKE \
  -DOPENBLAS_LIBRARY=/usr/lib/x86_64-linux-gnu/libblas.so \
  -DLAPACKE_LIBRARY="/path/to/SPARTA/lib/lapack-3.12.0/build/lib/liblapacke.a;/usr/lib/x86_64-linux-gnu/liblapack.so" \
  -DLAPACKE_HEADER_PATH=/path/to/SPARTA/lib/lapack-3.12.0/build/include
cmake --build build --target sparta_ambiRoomSim_LV2
```

## Build groups (audio_plugins/CMakeLists.txt)

| Group | Plugins |
|-------|---------|
| Always built | ambiDRC, ambiENC, ambiRoomSim, array2sh, beamformer, decorrelator, matrixConv, multiConv, panner, pitchShifter, rotator |
| Skipped on Linux | dirass, powermap, sldoa (depend on JUCE CameraDevice) |
| SOFA-gated | ambiBIN, ambiDEC, binauraliser, spreader, binauraliser_nf, 6DoFconv (`SAF_ENABLE_SOFA_READER_MODULE=ON`) |
| Projucer-only | trackerTest (`SDKs/NatNetSDK`, Windows, `docs/TrackerTestBuildInstructions.md`) |

## Layout

```
audio_plugins/_SPARTA_<name>_/
  CMakeLists.txt         → juce_add_plugin + links saf_example_<name>
  sparta_<name>.jucer    → deprecated, use CMake
  src/PluginProcessor.{h,cpp}  +  PluginEditor.{h,cpp}
audio_plugins/resources/
  PluginProcessorBase.h  → BlockAdapter (FIFO bridging host↔SAF frame sizes)
  ParameterManager.h, SPARTALookAndFeel.h, ConfigurationHelper.h
  Fonts/Inter-{Bold,Regular}.ttf  → embedded via juce_add_binary_data(GUI_fonts)
```

## Conventions

- C++14, C11 (C99 MSVC). Release default. CMake ≥ 3.15.
- Linux: `juce_opengl` disabled (`PLUGIN_EDITOR_DISABLE_OPENGL=1`).
- No in-repo tests/lint/CI. SAF submodule tests: `-DSAF_BUILD_TESTS=ON` (OFF).
- Submodules use SSH URLs — if `git submodule update --init` fails with
  "Permission denied", the submodules need SSH credentials or a URL override.

## Build quirks (this environment)

- **Submodule init**: SSH URLs fail without keys. Override to HTTPS:
  ```sh
  git config --local submodule.SDKs/Spatial_Audio_Framework.url https://github.com/leomccormack/Spatial_Audio_Framework.git
  git config --local submodule.SDKs/JUCE.url https://github.com/juce-framework/JUCE.git
  git submodule update --init --depth=1
  ```
- **LTO segfault**: `juce::juce_recommended_lto_flags` injects `-flto` which crashes
  the linker (`ld` segfault during LTRANS). Fix: remove `juce::juce_recommended_lto_flags`
  from `target_link_libraries` in the plugin's `CMakeLists.txt`. This means editing
  every `_SPARTA_*` CMakeLists.txt to drop that line.
- **`juce_lv2_helper` segfault**: After linking the LV2 `.so` successfully,
  `juce_lv2_helper` crashes with segfault when generating `ui.ttl`. Workaround:
  manually link the `.so` (run the link command from the build output verbatim),
  then copy a known-good `ui.ttl` from a previous install (it's a static template
  that doesn't change between builds for the same plugin).
- **LAPACKE not installed**: `liblapacke-dev` is not available on this system.
  Build it from source: download LAPACK 3.12.0, `cmake -DLAPACKE=ON`, `make lapacke`.
  **QUIRK — never put required libs in `/tmp`**: it gets wiped, breaking the build.
  Keep the build under the repo's `lib/` (gitignored) at
  `lib/lapack-3.12.0/build/` and point CMake at it
  (`-DLAPACKE_LIBRARY=/path/to/SPARTA/lib/lapack-3.12.0/build/lib/liblapacke.a`).
  Symlink the headers (`lapacke.h`, `lapack.h`, `lapacke_mangling.h`, `lapacke_utils.h`,
  `lapacke_config.h`) into `SDKs/Spatial_Audio_Framework/framework/include/` so the
  `#include "lapacke.h"` in `saf_externals.h` resolves.
- **Constructor `setSize()` crashes**: Calling `setSize()` early in a JUCE
  `AudioProcessorEditor` constructor triggers `resized()` before child components
  are constructed. Always guard `resized()` with null checks, or move `setSize()`
  to the end of the constructor after all components are created.

<!-- BEGIN opencode-rag -->
## Code Navigation

ALWAYS use OpenCodeRAG tools before reading or editing:
- **Search first** — `search_semantic(query)` instead of grep/glob
- **Skeleton before read** — `get_file_skeleton(filePath)` then read specific lines
- **Usages before edit** — `find_usages(symbolName)` before modifying any symbol
- **Images via describe** — `describe_image(filePath)` — never read raw bytes
- **Recall quirks** — `recall_quirks(query)` when you hit a known pitfall
- **Add quirks** — `add_quirk(content)` when you discover a non-obvious fact

If no results, run `opencode-rag index`.

### Decision tree — ALWAYS follow this order
1. User mentions code behavior/architecture → `search_semantic(query)`
2. User mentions a file path → `get_file_skeleton(filePath)` THEN `read` on specific lines
3. User mentions a function/class/variable to edit → `find_usages(symbolName)` THEN `search_semantic` THEN `edit`
4. User asks a code question → `search_semantic` to gather context before answering
5. User asks about an image or visual asset → `describe_image(filePath)` to retrieve its generated description, then optionally `search_semantic` for related code
6. You encounter an error or need to recall a known pitfall → `recall_quirks(query)`
7. You discover a non-obvious fact or workaround → `add_quirk(content)` to persist it for future sessions

### Proactive triggers — you MUST call these tools when
- User asks about code behavior, architecture, or implementation details
- User asks to edit, refactor, or fix code — call `find_usages` first
- User references files or functions you haven't read yet
- User says "find", "search", "look up", "where is", "how does"
- User refers to an image, screenshot, diagram, or visual asset
- Before answering ANY code-related question, retrieve context first
- Before reading ANY file, call `get_file_skeleton` to orient first

### Anti-patterns — NEVER do these
- Reading full files without calling `get_file_skeleton` first (wastes tokens)
- Editing a function without calling `find_usages` first (breaks call sites)
- Answering code questions without calling `search_semantic` first (you guess at behavior)
- Using `grep`/`glob` when `search_semantic` would find the answer faster
- Treating image files as text — use `describe_image` instead of reading raw bytes
- Using `npx opencode-rag quirk` shell commands instead of the built-in `add_quirk` / `recall_quirks` tools (the tools are faster, already loaded in-process, and go through the trust monitor)

### MANDATORY quirk capture rules — you MUST call `add_quirk` when
- A build, test, or type-check command fails and you resolve it
- You discover an undocumented library constraint, peer dep, or workaround
- You learn an environment-specific requirement (OS, tool version, etc.)
- You make a design decision that future sessions should remember
- You resolve a gotcha that cost more than one attempt
- NEVER finish a coding session without adding quirks for resolved errors.
<!-- END opencode-rag -->
