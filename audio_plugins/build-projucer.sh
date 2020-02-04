#!/bin/bash

if [[ "${OSTYPE}" != "linux-gnu" && "${OSTYPE}" != "darwin"* ]]; then
    echo "${OSTYPE} is unsupported"
    exit
fi

github_user="WeAreROLI"
github_repo="JUCE"
git_url_base=https://github.com/${github_user}/${github_repo}

NPROC=3

help_message="
script to fetch JUCE from github, and build Projucer in GPL mode

options:
- \"-t\": list available git tags
- \"-v <tag>\": compile and set git version (either \"master\" or a tag)
- \"-a <tag>\": activate git version (previously compiled)
- \"-j <nproc>\": compile using <nproc> CPU cores (default: ${NPROC})
- \"-h\": show this message
"

usage() {
    echo "${help_message}"
    exit
}

# find the SDKs directory
HERE=$(cd $(dirname $(which $0));pwd)
SDKs=$(cd ${HERE}/../SDKs;pwd)

list_git_tags() {
    git ls-remote -t ${git_url_base}.git | sed 's|.*/\(.*\)$|\1|' \
    | grep -v '\^' | sort -t. -k1,1nr -k2,2nr -k3,3nr
}

check_tag () {
    version=$1
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
    base_folder="JUCE-${version}/extras/Projucer"
    if [[ "$OSTYPE" == "linux-gnu" ]]; then
        echo ${base_folder}/Builds/LinuxMakefile
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo ${base_folder}/Builds/MacOSX
    fi
}

validate_link () {
    if [ -L ${1} ] && [ -e ${1} ]; then
        echo "symlink \"${1}\" is valid"
        return
    else
        echo "invalid symlink: \"$1\""
        exit
    fi
}

activate_version () {
    version=$1
    if [ ! -d "${SDKs}/JUCE-${version}" ]; then
        echo "version ${version} is not installed"
        exit
    fi

    cd "${SDKs}"

    # create symlink for Projucer
    projucer="$(get_projucer_folder "${version}")/build/Projucer"
    if [ -f "${SDKs}/${projucer}" ]; then
        rm -f Projucer
        ln -sf "${projucer}" .
    else
        echo "${SDKs}/${projucer} does not exists..."
        exit
    fi
    validate_link Projucer


    # create symlink for the JUCE modules
    modules="JUCE-${version}/modules"
    if [ -d "${SDKs}/${modules}" ]; then
        rm -rf modules
        ln -sf "JUCE-${version}/modules" .
    else
        echo "${SDKs}/${modules} does not exists..."
        exit
    fi
    validate_link modules
}


build () {
    version=$(check_tag ${1})
    if [ "${version}" = "" ]; then
        echo "tag ${1} does not exist"
        exit
    fi

    cd "${SDKs}"

    # fetch JUCE
    archive_url="${git_url_base}/archive/${version}.tar.gz"
    curl -L "${archive_url}" --output - | tar -xzf -

    # configure Projucer
    cd "$(get_projucer_folder ${version})"
    sed -i 's/JUCER_ENABLE_GPL_MODE 0/JUCER_ENABLE_GPL_MODE 1/g' \
    ../../JuceLibraryCode/AppConfig.h

    # build Projucer
    make -j${NPROC}

    activate_version "${version}"
}


while getopts "tv:a:j:" opt; do
  case ${opt} in
    t) echo "available tags:" && list_git_tags && usage;;
    v) build "$OPTARG" ;;
    a) activate_version "$OPTARG" ;;
    j) NPROC="$OPTARG" ;;
    *) usage ;;
  esac
done

if [ $OPTIND -eq 1 ]; then usage; fi

