#!/usr/bin/env bash

set -e

# Root cb-multios directory
DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

if [[ -z "${NO_PYTHON_I_KNOW_WHAT_I_AM_DOING_I_SWEAR}" ]]; then
  # Install necessary python packages
  if ! /usr/bin/env python -c "import xlsxwriter; import Crypto" 2>/dev/null; then
      echo "Please install required python packages" >&2
      echo "  $ sudo pip install xlsxwriter pycrypto" >&2
      exit 1
  fi
fi

echo "Creating Makefiles"
CMAKE_OPTS="${CMAKE_OPTS} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"

if [ -n "$BUILD64" ]; then
  CMAKE_OPTS="$CMAKE_OPTS -DCMAKE_TOOLCHAIN_FILE=../cmake/64.cmake"
  BUILD_DIR="build64"
else
  CMAKE_OPTS="$CMAKE_OPTS -DCMAKE_TOOLCHAIN_FILE=../cmake/32.cmake"
  BUILD_DIR="build"
fi;

echo "Creating build directory"
mkdir -p "${DIR}/${BUILD_DIR}"
cd "${DIR}/${BUILD_DIR}"

LINK=${LINK:-SHARED}
case $LINK in
    SHARED) CMAKE_OPTS="$CMAKE_OPTS -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=OFF";;
    STATIC) CMAKE_OPTS="$CMAKE_OPTS -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON";;
esac

# Prefer ninja over make, if it is available
if command -v ninja >/dev/null; then
  CMAKE_OPTS="-G Ninja $CMAKE_OPTS"
fi

# shellcheck disable=SC2086
cmake $CMAKE_OPTS ..

cmake --build .
