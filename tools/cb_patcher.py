#!/usr/bin/env python
import os
import shutil
import sys

import yaml  # pip install pyyaml

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
ORIGINAL_CHALLS = os.path.abspath('../original-challenges')
CHALLENGE_PATH = os.path.abspath('../cqe-challenges')

# Load the manual patches
with open(os.path.join(TOOLS_DIR, 'manual_patches.yaml')) as f:
    mpatches = yaml.safe_load(f)


def debug(s):
    sys.stdout.write(str(s))
    sys.stdout.flush()


def save_patched_file(fpath, patched):
    """Saves the patched file with a new name

    Args:
        fpath (str): Path to original file
        patched (str): Patched code
    """
    # Write the patched file
    with open(fpath, 'w') as f:
        f.write(patched)

    fname = os.path.basename(fpath)
    debug('done => {}\n'.format(fname))


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


def try_delete(path):
    try:
        os.remove(path)
    except OSError:
        pass


def patch_files_in_dir(path):
    for fname in listdir(path):
        debug('\tPatching {}...'.format(fname))
        fpath = os.path.join(path, fname)

        # Read in the contents of the file
        with open(fpath) as f:
            src = f.read()

        # Apply all manual patches
        patched = apply_manual_patches(fname, src)

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
        debug('Patching lib files...\n')
        lib_path = os.path.join(CHALLENGE_PATH, chal, 'lib')

        # Delete libcgc.h if it exists
        try_delete(os.path.join(lib_path, 'libcgc.h'))

        patch_files_in_dir(lib_path)

        # Patch all source files
        debug('Patching src files...\n')
        patch_files_in_dir(os.path.join(CHALLENGE_PATH, chal, 'src'))
        patch_files_in_dir(os.path.join(CHALLENGE_PATH, chal, 'include'))


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
    for chal in listdir(ORIGINAL_CHALLS):  # Only a few for now
        shutil.copytree(os.path.join(ORIGINAL_CHALLS, chal),
                        os.path.join(CHALLENGE_PATH, chal))
        patch_challenge(chal)


if __name__ == '__main__':
    main()
