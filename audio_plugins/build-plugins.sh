#!/bin/bash

# Author: Marc Lavallée 2020

if [[ "${OSTYPE}" != "linux-gnu" && "${OSTYPE}" != "darwin"* ]]; then
    echo "${OSTYPE} is unsupported"
    exit
fi

help_message="
script to \"projuce\" and build the SPARTA plugins on Linux

parameters:
without parameters the script will show info about the plugin(s)
- \"help\": to show this message
- a plugin directory, else commands will apply to all plugins
- \"info\": about plugins(s)
- \"projucer\": to open Projucer for plugins(s)
- \"projuce\": to regenerate Projucer files
- \"clean\": to clean the plugin(s)
- \"build\": to build the plugin(s)
- \"all\": shortcut for \"projuce clean build\"
remaining params are passed to \"make\"

ex: \"_SPARTA_ambiBIN_ projucer\" opens Projucer for the \"_SPARTA_ambiBIN_\" plugin
ex: \"_SPARTA_ambiBIN_ build -j6\" builds _SPARTA_ambiBIN_ using 6 CPU cores
ex: \"projuce clean build\" generates all make files, clean and build all plugins
ex: \"all -j6\" projuce, clean and build all plugins, using 6 CPU cores.
"

help=0
info=0
build=0
clean=0
all=0
projucer=0
projuce=0

HERE=$(cd $(dirname $0) && pwd)

# check SDKs
ok=0
SDKs=$(cd ${HERE}/../SDKs && pwd)


# check Spatial audio Framework:
if [ ! -e "${SDKs}/Spatial_Audio_Framework/.git" ]; then
  echo "
    Spatial_Audio_Framework was not found...
    Do you wish to install it ?"
    select yn in "Yes" "No"; do
      case $yn in
        Yes ) git submodule update --init "${SDKs}/Spatial_Audio_Framework"; $0 $@; break;;
        No ) echo "Exiting now..."; exit;;
      esac
    done
    exit
fi

# set Projucer
if [[ "${OSTYPE}" == "linux-gnu" ]]; then
    projucer_bin="${SDKs}/Projucer"
elif [[ "${OSTYPE}" == "darwin"*  ]]; then
    projucer_app="${SDKs}/Projucer.app"
    projucer_bin="${projucer_app}/Contents/MacOS/Projucer"
fi

if [ ! ${projucer_bin} ] || [ ! -e ${projucer_bin} ] ; then
    echo "
    Projucer is not installed (or configured)
    in the \"${SDKs}\" folder.
    Do you wish to run install-juce.sh?"
    select yn in "Yes" "No"; do
      case $yn in
          Yes ) "${HERE}/install-juce.sh"; $0 $@; break;;
          No ) echo "Exiting now..."; exit;;
      esac
    done
    exit
fi

VST2_SDK="${SDKs}/VST2_SDK"
if [ ! ${VST2_SDK} ] || [ ! -e ${VST2_SDK} ]; then
    echo "
    VST2_SDK is not installed (or configured)
    in the \"${SDKs}\" folder.
    Do you wish to run install-vst2_sdk.sh?"
    select yn in "Yes" "No"; do
      case $yn in
        Yes ) "${HERE}/install-vst2_sdk.sh"; $0 $@; break;;
        No ) echo "Exiting now..."; exit;;
      esac
    done
    exit
fi


PATH="${SDKs}/JUCE/modules:$PATH"

# location of plugin binaries
mkdir -p "${HERE}/../lib"
binaries=$(cd ${HERE}/../lib && pwd)

i=$#
while [ $i -gt 0 ]; do
  var=$1
  if [ -d "${HERE}/${var}" ]; then
    from="${HERE}/${var}"
  elif [ ${var} == "help" ]; then
    help=1
  elif [ ${var} == "projucer" ]; then
    projucer=1
  elif [ ${var} == "info" ]; then
    info=1
  elif [ ${var} == "projuce" ]; then
    projuce=1
  elif [ ${var} == "clean" ]; then
    clean=1
  elif [ ${var} == "build" ]; then
    build=1
  elif [ ${var} == "all" ]; then
    projuce=1
    clean=1
    build=1
  else
    set -- "$@" "$var"
  fi
  i=$(($i-1))
  shift
done

if [ $(( info + projucer + projuce + clean + build + all)) -eq 0 ]; then help=1; fi
if [ ${help} -gt 0 ]; then
  echo "${help_message}"
  exit
fi


if [ ${info} -gt 0 ]; then
    get_info () {
        jucer=$@
        status="$(${projucer_bin} --status ${jucer} 2>&1)"
        name=$(echo "${status}" | grep Name | cut -c 7-)
        echo "${status}"
        name=$(echo "${status}" | grep Name | cut -c 7-)
        ls -Rh --color ${binaries}/${name}* 2>/dev/null
    }
    while read jucer; do
        get_info ${jucer}
    done <<< "$(find ${from} -type f -name "*.jucer")"
fi

[ -z ${from+x} ] && from="${HERE}"

# opening Projucer editor
if [[ "${OSTYPE}" == "linux-gnu" ]]; then
    [ ${projucer} -gt 0 ] && find "${from}" -type f -name "*.jucer" \
        -exec ${projucer_bin} "{}" \;
elif [[ "${OSTYPE}" == "darwin"*  ]]; then
    [ ${projucer} -gt 0 ] && find "${from}" -type f -name "*.jucer" \
        -exec open ${projucer_app} "{}" \;
fi


[ ${projucer} -gt 0 ] && find "${from}" -type f -name "*.jucer" \
  -exec ${projucer_bin} "{}" \;

# projucing (resaving Projucer files)
[ ${projuce} -gt 0 ] && find "${from}" -type f -name "*.jucer" \
  -exec ${projucer_bin} --resave "{}" \;

if [[ "${OSTYPE}" == "linux-gnu" ]]; then

    # cleaning)
    [ ${clean} -gt 0 ] && find "${from}" -type d -name "LinuxMakefile" \
      -exec bash -c "echo cleaning \"{}\" && cd \"{}\" && make CONFIG=Release clean" \;

    # building
    [ ${build} -gt 0 ] && find "${from}" -type d -name "LinuxMakefile" \
      -exec bash -c "echo building \"{}\" && cd \"{}\" && make CONFIG=Release $@" \;

elif [[ "${OSTYPE}" == "darwin"* ]]; then

    # cleaning)
    [ ${clean} -gt 0 ] && find "${from}" -type d -name "Xcode" \
      -exec bash -c "echo cleaning \"{}\" && cd \"{}\" && xcodebuild -quiet -configuration Release clean" \;

    # building
    [ ${build} -gt 0 ] && find "${from}" -type d -name "Xcode" \
      -exec bash -c "echo building \"{}\" && cd \"{}\" && xcodebuild -quiet -configuration Release" \;

fi


