#!/usr/bin/env bash

PROJECT_ROOT="$(git rev-parse --show-toplevel)"

function generateAndMoveToProjectWorkspaceSubdirectory()
{
  if (( $# != 1)); then echo "$0 requires 1 args"; exit 1; fi

  BUILD_DIR="$1"

  if [ ! -d "${BUILD_DIR}" ]; then mkdir "${BUILD_DIR}"; fi

  pushd "${BUILD_DIR}"
}

generateAndMoveToProjectWorkspaceSubdirectory 'linux-or-macos' 

cmake $PROJECT_ROOT && make
