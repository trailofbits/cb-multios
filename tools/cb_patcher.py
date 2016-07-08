#!/usr/bin/env python
import os
import shutil

ORIGINAL_CHALLS = os.path.abspath('../original-challenges')
CHALLENGE_PATH = os.path.abspath('../cqe-challenges')


def patch_challenge(path):
    pass


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
        patch_challenge(os.path.join(CHALLENGE_PATH, chal))


if __name__ == '__main__':
    main()
