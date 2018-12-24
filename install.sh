#!/usr/bin/env bash

source  configs/variables
source bash_helpers.sh

trap exit_trap EXIT
set -e

./apply_patches.sh; check

./build_cef.sh; check