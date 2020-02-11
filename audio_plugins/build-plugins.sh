#!/bin/bash

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
[ -e "${SDKs}/modules" ] \
&& [ -e "${SDKs}/Spatial_Audio_Framework" ] \
&& [ -e "${SDKs}/VST2_SDK" ] && ok=1
if [ $ok == 0 ]; then
  echo "Install missing dependencies in \"${SDKs}\""
  exit
fi

# location of plugin binaries
binaries=$(cd ${HERE}/../lib && pwd)
# create if missing
mkdir -p "${binaries}"

i=$#
while [ $i -gt 0 ]; do
  var=$1
  if [ -d ${var} ]; then
    from="${var}"
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

# location of Projucer app: priority to the one found in SDKs
projucer_app="${SDKs}/Projucer"
[ ! -e ${projucer_app} ] && projucer_app=$(which Projucer)
if [ ! ${projucer_app} ] || [ ! -e ${projucer_app} ]; then
  echo "Projucer is not installed"
  echo "On Debian (and Ubuntu), install the \"juce-tools\" package"
  echo "or compile a GPL enabled version using this script:"
  echo "${HERE}/linux-build-projucer.sh"
  echo "or install Projucer as you like, set the \"projucer_app\" variable"
  echo "or create a \"${SDKs}/Projucer\" symbolic link"
  exit
fi

if [ ${info} -gt 0 ]; then
    get_info () {
        jucer=$@
        status="$(${projucer_app} --status ${jucer} 2>&1)"
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
[ ${projucer} -gt 0 ] && find "${from}" -type f -name "*.jucer" \
  -exec ${projucer_app} "{}" \;

# projucing (resaving Projucer files)
[ ${projuce} -gt 0 ] && find "${from}" -type f -name "*.jucer" \
  -exec ${projucer_app} --resave "{}" \;

# cleaning)
[ ${clean} -gt 0 ] && find "${from}" -type d -name "LinuxMakefile" \
  -exec bash -c "cd \"{}\" && make CONFIG=Release clean" \;

# building
[ ${build} -gt 0 ] && find "${from}" -type d -name "LinuxMakefile" \
  -exec bash -c "cd \"{}\" && make CONFIG=Release $@" \;
