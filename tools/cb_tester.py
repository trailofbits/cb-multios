#!/usr/bin/env python
import argparse
import os
import sys

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
CHAL_DIR = os.path.join(os.path.dirname(TOOLS_DIR), 'cqe-challenges')
TEST_DIR = os.path.join(TOOLS_DIR, 'cb-testing')


def test_challenges(chals):
    # type: (list) -> None
    pass


def listdir(path):
    # type: (str) -> list
    if not os.path.isdir(path):
        return []
    return sorted(os.listdir(path))


def main():
    parser = argparse.ArgumentParser()

    g = parser.add_mutually_exclusive_group(required=True)
    g.add_argument('-a', '--all', action='store_true',
                   help='Run tests against all challenge binaries')

    g.add_argument('-c', '--chals', nargs='+', type=str,
                   help='List of challenge names to test')

    args = parser.parse_args(sys.argv[1:])

    if args.all:
        test_challenges(listdir(CHAL_DIR))
    elif args.chals:
        test_challenges(args.chals)


if __name__ == '__main__':
    main()
