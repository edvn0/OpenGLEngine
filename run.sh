#!/usr/bin/env bash

set -e

FORCE_RECONFIGURE=${1:-0}
BUILD_TYPE=${2:-Debug}

SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
BUILDPATH="$SCRIPTPATH/build"

function build() {
  # Build folder may exists, but for a clean reconfigure, we just delete it and binaries.
  if [ "$FORCE_RECONFIGURE" == "1" ];
  then
    rm -rf "$BUILDPATH"
  fi
  
  # Build folder does not exist, create it.
  # All third party configuration is in the Modules/CMakeLists.txt
  # Runtime build type and OS is determined from CMake too.
  if ! [ -d "$BUILDPATH" ];
  then
    cmake -GNinja -S "$SCRIPTPATH" -B "$BUILDPATH" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
  fi
  cmake --build "$BUILDPATH"
}

function run() {
  local RUNPATH="$BUILDPATH/Application"
  pushd "$RUNPATH" > /dev/null 2>&1
  ./Application
  popd > /dev/null 2>&1
}

build
run
