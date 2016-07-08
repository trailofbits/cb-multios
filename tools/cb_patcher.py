#!/usr/bin/env python
import os
import shutil
import sys

ORIGINAL_CHALLS = os.path.abspath('../original-challenges')
CHALLENGE_PATH = os.path.abspath('../cqe-challenges')

LIB_PATCH_NO_INCLUDES = '''#include <libcgc.h>
namespace cgc {{
{}
}}
'''

LIB_PATCH_WITH_INCLUDES = '''{}
namespace cgc {{
{}
}}
'''


def debug(s):
    sys.stdout.write(str(s))


def split_after_includes(src):
    # Find the line after the last #include
    last = src.rfind('#include')
    next_line = src[last:].find('\n') + last + 1

    # Separate the file at this line
    return src[:next_line], src[next_line:]


def patch_lib(lib_path):
    for fname in os.listdir(lib_path):
        debug('\tPatching {}...'.format(fname))
        fpath = os.path.join(lib_path, fname)

        # Read in the contents of the file
        with open(fpath) as f:
            src = f.read()

        # Check if there are any includes in the file
        if '#include' in src:
            # Separate the file after the includes
            before, after = split_after_includes(src)

            # If ligcgc is missing, add it
            if 'libcgc.h' not in src:
                before += '\n#include <libcgc.h>\n'
            patched = LIB_PATCH_WITH_INCLUDES.format(before, after)
        else:
            patched = LIB_PATCH_NO_INCLUDES.format(src)

        # Write the patched file
        with open(fpath, 'w') as f:
            f.write(patched)

        # Rename C files to C++
        if fname.endswith('.c'):
            base = os.path.splitext(fname)[0]
            new_name = '{}.cpp'.format(base)
            os.rename(fpath, os.path.join(lib_path, new_name))
            debug('done => {}\n'.format(new_name))
        else:
            debug('done\n')


def patch_challenge(chal):
    debug('Patching {}...\n'.format(chal))
    # Patch all lib files first
    patch_lib(os.path.join(CHALLENGE_PATH, chal, 'lib'))


def clear_challenges():
    """Delete all patched directories"""
    for chal in os.listdir(CHALLENGE_PATH):
        shutil.rmtree(os.path.join(CHALLENGE_PATH, chal))


def main():
    clear_challenges()

    # Copy over one challenge at a time and patch it
    for chal in os.listdir(ORIGINAL_CHALLS)[:3]:  # Only 3 for now
        shutil.copytree(os.path.join(ORIGINAL_CHALLS, chal),
                        os.path.join(CHALLENGE_PATH, chal))
        patch_challenge(chal)


if __name__ == '__main__':
    main()
