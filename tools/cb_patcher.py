#!/usr/bin/env python
import os
import shutil
import sys

import yaml  # pip install pyyaml

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
ORIGINAL_CHALLS = os.path.abspath('../original-challenges')
CHALLENGE_PATH = os.path.abspath('../cqe-challenges')

LIB_PATCH = '''{}
namespace cgc {{
{}
}}
'''

SRC_PATCH = '''{}
using namespace cgc;
{}
'''

# Load the manual patches
with open(os.path.join(TOOLS_DIR, 'manual_patches.yaml')) as f:
    mpatches = yaml.safe_load(f)


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


def apply_manual_patches(fname, src):
    # type: (str, str) -> str
    # Apply everything in 'all' first
    for match, rep in mpatches['all'].iteritems():
        src = src.replace(match, rep)

    # Apply any patches specific to this file
    if fname in mpatches:
        for match, rep in mpatches[fname].iteritems():
            src = src.replace(match, rep)
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

    for fname in listdir(lib_path):
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
        patched = replace_include_names(patched, listdir(lib_path))

        # Apply all manual patches
        patched = apply_manual_patches(fname, patched)

        save_patched_file(fpath, patched, 'cgc_{}{}')


def patch_src(src_path):
    debug('Patching src files...\n')
    for fname in listdir(src_path):
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
        lib_files = listdir(os.path.join(os.path.dirname(src_path), 'lib'))
        patched = replace_include_names(patched, lib_files)

        # Apply all manual patches
        patched = apply_manual_patches(fname, patched)

        save_patched_file(fpath, patched)


def patch_challenge(chal):
    debug('Patching {}...\n'.format(chal))

    # Some challenges have multiple binaries with the source in cb_* directories
    dirs = listdir(os.path.join(CHALLENGE_PATH, chal))
    cbdirs = filter(lambda d: d.startswith('cb_'), dirs)

    if len(cbdirs) > 0:
        # Process each of these as a separate challenge binary
        for d in cbdirs:
            patch_challenge(os.path.join(chal, d))
    else:
        # Patch all lib files first
        patch_lib(os.path.join(CHALLENGE_PATH, chal, 'lib'))

        # Patch all source files
        patch_src(os.path.join(CHALLENGE_PATH, chal, 'src'))


def listdir(path):
    if not os.path.isdir(path):
        return []
    return sorted(os.listdir(path))


def clear_challenges():
    """Delete all patched directories"""
    for chal in listdir(CHALLENGE_PATH):
        shutil.rmtree(os.path.join(CHALLENGE_PATH, chal))


def main():
    clear_challenges()

    # Copy over one challenge at a time and patch it
    for chal in listdir(ORIGINAL_CHALLS)[:7]:  # Only a few for now
        shutil.copytree(os.path.join(ORIGINAL_CHALLS, chal),
                        os.path.join(CHALLENGE_PATH, chal))
        patch_challenge(chal)


if __name__ == '__main__':
    main()
