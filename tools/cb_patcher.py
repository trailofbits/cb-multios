#!/usr/bin/env python
import os
import shutil
import sys

ORIGINAL_CHALLS = os.path.abspath('../original-challenges')
CHALLENGE_PATH = os.path.abspath('../cqe-challenges')

LIB_PATCH = '''{}
namespace cgc {{
{}
}}
'''

SRC_PATCH = '''{}
using namespace cgc;
{}'''


def debug(s):
    sys.stdout.write(str(s))
    sys.stdout.flush()


def save_patched_file(fpath, patched, name_fmt='{}{}'):
    """Saves the patched file with a new name

    Args:
        fpath (str): Path to original file
        patched (str): Patched code
        name_fmt (str): Name format for the file, takes basename and extension as args
    """

    # Write the patched file
    with open(fpath, 'w') as f:
        f.write(patched)

    fname = os.path.basename(fpath)
    lib_path = os.path.dirname(fpath)

    # Rename C files to C++
    base, ext = os.path.splitext(fname)
    if ext == '.c':
        ext = '.cpp'
    new_name = name_fmt.format(base, ext)
    os.rename(fpath, os.path.join(lib_path, new_name))
    debug('done => {}\n'.format(new_name))


def replace_include_names(src, lib_names):
    """Replaces any #include's to a header in the lib folder with the fixed cgc name

    Args:
        src (str): Source code being patched
        lib_names (list): List of files in the lib directory

    Returns:
        str: Patched source code
    """
    for lib in lib_names:
        lib = lib.strip('cgc_')
        src = src.replace('#include <{}>'.format(lib), '#include <cgc_{}>'.format(lib))
        src = src.replace('#include "{}"'.format(lib), '#include "cgc_{}"'.format(lib))
    return src


def split_after_includes(src):
    # type: (str) -> (str, str)
    if '#include' not in src:
        return '', src

    # Find the line after the last #include
    last = src.rfind('#include')
    next_line = src[last:].find('\n') + last + 1

    # Separate the file at this line
    return src[:next_line], src[next_line:]


def patch_lib(lib_path):
    debug('Patching lib files...\n')

    # Delete libcgc.h if it exists
    try:
        os.remove(os.path.join(lib_path, 'libcgc.h'))
    except OSError:
        pass

    for fname in os.listdir(lib_path):
        debug('\tPatching {}...'.format(fname))
        fpath = os.path.join(lib_path, fname)

        # Read in the contents of the file
        with open(fpath) as f:
            src = f.read()

        # Namespace patch
        # Separate the file after all includes
        before, after = split_after_includes(src)

        # If ligcgc is missing, add it
        if 'libcgc.h' not in src:
            before += '#include <libcgc.h>\n'
        patched = LIB_PATCH.format(before, after)

        # Replace all includes with the fixed names
        patched = replace_include_names(patched, os.listdir(lib_path))

        # Replace NULLs with nullptrs
        patched = patched.replace('NULL', 'nullptr')

        # Annoying case specific to stdlib.c
        if fname == 'stdlib.c':
            patched = patched.replace('unsigned char *c = buff;', 'unsigned char *c = (unsigned char *) buff;')

        save_patched_file(fpath, patched, 'cgc_{}{}')


def patch_src(src_path):
    debug('Patching src files...\n')
    for fname in os.listdir(src_path):
        debug('\tPatching {}...'.format(fname))
        fpath = os.path.join(src_path, fname)

        # Read in the contents of the file
        with open(fpath) as f:
            src = f.read()

        # Namespace patch
        # Separate the file after all includes
        before, after = split_after_includes(src)

        # If ligcgc is missing, add it
        if 'libcgc.h' not in src:
            before += '#include <libcgc.h>\n'
        patched = SRC_PATCH.format(before, after)

        # Replace all includes with the fixed names
        lib_path = os.path.join(os.path.dirname(src_path), 'lib')
        patched = replace_include_names(patched, os.listdir(lib_path))

        # Replace NULLs with nullptrs
        patched = patched.replace('NULL', 'nullptr')

        save_patched_file(fpath, patched)


def patch_challenge(chal):
    debug('Patching {}...\n'.format(chal))
    # Patch all lib files first
    patch_lib(os.path.join(CHALLENGE_PATH, chal, 'lib'))

    # Patch all source files
    patch_src(os.path.join(CHALLENGE_PATH, chal, 'src'))


def clear_challenges():
    """Delete all patched directories"""
    for chal in os.listdir(CHALLENGE_PATH):
        shutil.rmtree(os.path.join(CHALLENGE_PATH, chal))


def main():
    clear_challenges()

    # Copy over one challenge at a time and patch it
    for chal in os.listdir(ORIGINAL_CHALLS)[:4]:  # Only a few for now
        shutil.copytree(os.path.join(ORIGINAL_CHALLS, chal),
                        os.path.join(CHALLENGE_PATH, chal))
        patch_challenge(chal)


if __name__ == '__main__':
    main()
