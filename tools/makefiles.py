#!/usr/bin/env python
import glob
import os
import re

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
CHAL_DIR = os.path.join(os.path.dirname(TOOLS_DIR), 'processed-challenges')
IGNORED_FLAGS = [
    '-Werror',
    '-Dmain=_main',

    # Letting CMake handle these
    '--std=c++11',  # 2 dashes are intentional
    '-std=c99'
]


def generate_cmake(path):
    # Path to the new CMakelists.txt
    cmake_path = os.path.join(os.path.dirname(path), 'CMakeLists.txt')
    print('Generating: {}'.format(cmake_path))

    # Read in the Makefile
    with open(path) as f:
        old_make = f.readlines()

    # Default values for CFLAGS
    make_vars = {}
    for line in old_make:
        line = re.sub('[\r\n\t]', '', line)

        # Parse out any variables in the Makefile
        if '=' in line:
            var, val = line.split('=', 1)
            var = var.strip()
            val = val.strip()
            make_vars[var] = val

    # Generate the CMake data
    cmake = ""
    for var, val in make_vars.iteritems():
        if var in ['CFLAGS', 'CXXFLAGS']:
            # Separate the flags
            flags = val.split(' ')

            # Remove any flags we don't want
            # Not using a set here to preserve order
            flags = [v for v in flags if v not in IGNORED_FLAGS]

            # Add these flags for the directory
            cmake += 'add_compile_options( {} )\n'.format(' '.join(flags))
        else:
            # Set others as regular variables
            cmake += 'set( {} "{}" )\n'.format(var, val)
    cmake += 'buildCB()\n'

    # Write the CMakelists
    with open(cmake_path, 'w') as f:
        f.write(cmake)

    # Delete the now unused Makefile
    os.remove(path)


def main():
    makefiles = glob.glob(os.path.join(CHAL_DIR, '*', 'build_directives.txt'))
    map(generate_cmake, makefiles)


if __name__ == '__main__':
    main()
