#!/bin/bash

# Author: Marc Lavallée 2020

if [[ "${OSTYPE}" != "linux-gnu" && "${OSTYPE}" != "darwin"* ]]; then
    echo "${OSTYPE} is unsupported"
    exit
fi

if [ ! $(which unzip) ]; then
    echo "The \"unzip\" command is required. Please install and retry."
fi

github_user="WeAreROLI"
github_repo="JUCE"
git_url_base=https://github.com/${github_user}/${github_repo}

NPROC=3

help_message="
Script to build Projucer in GPL mode

By default it tries to compile the JUCE git sub-module

options:
- \"-t\": list available git tags
- \"-v <tag>\": activate git version (either \"master\" or a tag)
- \"-j <nproc>\": compile using <nproc> CPU cores (default: ${NPROC})
- \"-h\": show this message
"

usage() {
    echo "${help_message}"
    exit
}

# find the SDKs directory
HERE=$(cd $(dirname $0) && pwd)
SDKs=$(cd ${HERE}/../SDKs && pwd)

list_git_tags() {
    git ls-remote -t ${git_url_base}.git | sed 's|.*/\(.*\)$|\1|' \
    | grep -v '\^' | sort -t. -k1,1nr -k2,2nr -k3,3nr
}

check_tag () {
    version=$1
    if [ -z "${version}" ]; then
        return
    fi

    while read tag; do
        if [ "${version}" = "${tag}" ]; then
            echo "${version}"
            return
        fi
    done <<< """master
    $(list_git_tags)"""
}

get_projucer_folder () {
    version=$1
    base_folder="JUCE${version}/extras/Projucer"
    if [[ "$OSTYPE" == "linux-gnu" ]]; then
        echo ${base_folder}/Builds/LinuxMakefile
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo ${base_folder}/Builds/MacOSX
    fi
}

validate_link () {
    if [ -L ${1} ] && [ -e ${1} ]; then
        echo "symlink \"${1}\" is valid"
    else
        echo "invalid symlink: \"$1\""
        exit
    fi
}

activate_version () {
    version=$1
    if [ -z "${version}" ]; then
        git submodule update --init "${SDKs}/JUCE"
        if [ -d "${SDKs}/JUCE" ]; then
            echo "building git submodule version ..."
            build
        else
            activate_version master
            exit
        fi
    else
        if [ ! -d "${SDKs}/JUCE${version}" ]; then
            echo "version ${version} is not installed in the \"${SDKs}\" folder."
            echo "building version ${version} ..."
            build "${version}"
        fi
    fi

    cd "${SDKs}"

    # create symlink for Projucer
    projucer_folder="$(get_projucer_folder "${version}")"
    if [[ "${OSTYPE}" == "linux-gnu" ]]; then
        projucer="${projucer_folder}/build/Projucer"
        if [ -f "${SDKs}/${projucer}" ]; then
            rm -f Projucer
            ln -sf "${projucer}" .
        else
            echo "${SDKs}/${projucer} does not exists..."
            exit
        fi
        validate_link "Projucer"
    elif [[ "${OSTYPE}" == "darwin"* ]]; then
        projucer="${projucer_folder}/build/Release/Projucer.app"
        if [ -d "${SDKs}/${projucer}" ]; then
            rm -f "Projucer.app"
            ln -sf "${projucer}" "Projucer.app"
        else
            echo "${SDKs}/${projucer} does not exists..."
            exit
        fi
        validate_link "Projucer.app"
    fi

}

build () {
    if [ ! -z "${1}" ]; then
        version=$(check_tag ${1})
        if [ "${version}" = "" ]; then
            echo "tag ${1} does not exist"
            exit
        fi
        version=""
    fi

    cd "${SDKs}"

    # fetch JUCE
    if [ ! -d "${SDKs}/JUCE${version}" ]; then
        archive_url="${git_url_base}/archive/${version}.tar.gz"
        curl -L "${archive_url}" --output - | tar -xzf -
    fi

    # configure Projucer
    cd "$(get_projucer_folder ${version})"
    sed -i'' -e 's/JUCER_ENABLE_GPL_MODE 0/JUCER_ENABLE_GPL_MODE 1/g' \
    ../../JuceLibraryCode/AppConfig.h

    # build Projucer
    if [[ "${OSTYPE}" == "linux-gnu" ]]; then
        make -j${NPROC}
    elif [[ "${OSTYPE}" == "darwin"* ]]; then
        xcodebuild -quiet -configuration Release
    fi

}


while getopts "tv:a:j:" opt; do
  case ${opt} in
    t) echo "available tags:" && list_git_tags && usage;;
    v) activate_version "$OPTARG" ;;
    j) NPROC="$OPTARG" ;;
    *) usage ;;
  esac
done

if [ $OPTIND -eq 1 ]; then
    activate_version
fi

