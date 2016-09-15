#!/usr/bin/env python
import glob
import os
import re

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
CHAL_DIR = os.path.join(os.path.dirname(TOOLS_DIR), 'processed-challenges')


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
        if "=" in line:
            var, val = line.split('=', 1)
            var = var.strip().replace('CFLAGS', 'flags')  # Rename CFLAGS to flags
            val = val.strip().replace('-Werror', '')      # Get rid of -Werror if it's there
            make_vars[var] = val

    # Generate the CMake data
    cmake = ""
    for var, val in make_vars.iteritems():
        cmake += 'set( {} "{}" )\n'.format(var, val)
    cmake += 'buildCB("${flags} ")'

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
