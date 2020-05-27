#!/bin/bash

# Author: Marc Lavallée 2020

# find the SDKs directory
HERE=$(cd $(dirname $0) && pwd)
SDKs=$(cd ${HERE}/../SDKs && pwd)

cd "${SDKs}"
archive_name="vstsdk3610_11_06_2018_build_37.zip"
archive_url="https://web.archive.org/web/20181016150224/https://download.steinberg.net/sdk_downloads/${archive_name}"
archive_md5_sum="f66fc320407822e610ccd26c5ba48b08"
downloaded=0

validate_link () {
    if [ -L ${1} ] && [ -e ${1} ]; then
        echo "symlink \"${1}\" is valid"
    else
        echo "invalid symlink: \"$1\""
        exit
    fi
}

if [ ! -f "${archive_name}" ]; then
    echo "downloading VST_SDK"
    curl -L "${archive_url}" --output "${archive_name}"
    downloaded=1
fi

md5_sum=$(openssl md5 "${archive_name}" | cut -f 2 -d ' ')
if [ "${md5_sum}" != "${archive_md5_sum}" ]; then
    rm "${archive_name}"
    get_vst_sdk
fi

if [ ${downloaded} ]; then
    unzip -qu "${archive_name}"
    ln -sf "VST_SDK/VST2_SDK" .
    validate_link "VST2_SDK"
fi

