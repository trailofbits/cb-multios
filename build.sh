#!/usr/bin/env bash

# Root cb-multios directory
DIR=$(cd "$(dirname ${BASH_SOURCE[0]})" && pwd)
TOOLS="$DIR/tools"

function prompt() {
    read -p "$1 (y/n): " -n 1 -r
    echo
    [[ $REPLY =~ ^[Yy]$ ]]
}

# Install necessary python packages
pip install pyyaml xlsxwriter

# Check if the patched challenges are already there
REGEN=0
if [[ -d "$DIR/cqe-challenges" && -n "$(ls -A "$DIR/cqe-challenges" 2>/dev/null)"  ]]; then
    prompt "Patched challenges already exist. Delete and regenerate?"
    REGEN=$?
fi

if [[ ${REGEN} == 0 ]]; then
    echo "Generating patched challenges..."#
    ${TOOLS}/cb_patcher.py
fi

echo "Generating CMakelists"
${TOOLS}/makefiles.py

echo "Creating build directory"
mkdir ${DIR}/build
cd ${DIR}/build

echo "Creating Makefiles"
cmake ..

make
