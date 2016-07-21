#!/usr/bin/env python
import argparse
import glob
import os
import subprocess
import sys

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
CHAL_DIR = os.path.join(os.path.dirname(TOOLS_DIR), 'cqe-challenges')
TEST_DIR = os.path.join(TOOLS_DIR, 'cb-testing')


def debug(s):
    sys.stdout.write(str(s))
    sys.stdout.flush()


class Score:
    """Contains the results of a test"""

    def __init__(self):
        self.passed = 0
        self.total = 0

    @property
    def failed(self):
        """Number of failed tests"""
        return self.passed - self.total


class Tester:
    """Tests and keeps track of the results of a single challenge binary"""

    # These determine which types of tests will be run
    # Both are enabled by default
    povs = True
    polls = True

    def __init__(self, chal_name):
        self.name = chal_name

        # Directories used in testing
        self.chal_dir = os.path.join(CHAL_DIR, self.name)
        self.bin_dir = os.path.join(self.chal_dir, 'bin')
        self.pov_dir = os.path.join(self.chal_dir, 'pov')
        self.poll_dir = os.path.join(self.chal_dir, 'poller')

        # Keep track of success
        self.povs = Score()
        self.polls = Score()

    @property
    def passed(self):
        """Number of passed tests"""
        return self.povs.passed + self.polls.passed

    @property
    def total(self):
        """Total number of tests run"""
        return self.povs.total + self.polls.total

    @property
    def failed(self):
        """Number of failed tests"""
        return self.total - self.passed

    @staticmethod
    def parse_results(output):
        """ Parses out the number of passed and failed tests from cb-test output

        Args:
            output (str): Raw output from running cb-test
        Returns:
            (int, int): # of tests passed, # of tests failed
        """
        # If the test failed to run, consider it failed
        if 'polls passed' not in output:
            return 0, 1

        # Parse out results
        passed = int(output.split('polls passed: ')[1].split('\n')[0])
        failed = int(output.split('polls failed: ')[1].split('\n')[0])
        return passed, failed

    def run_test(self, bin_name, xml_dir, score):
        """ Runs a test using cb-test and saves the result

        Args:
            bin_name (str): Name of the binary being tested
            xml_dir (str): Directory containing all xml tests
            score (Score): Object to store the results in
        """
        cb_cmd = ['./cb-test', '--cb', bin_name, '--directory', self.bin_dir, '--xml_dir', xml_dir]
        p = subprocess.Popen(cb_cmd, cwd=TEST_DIR, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = p.communicate()

        passed, failed = self.parse_results(out)
        score.passed += passed
        score.total += passed + failed

    def run_against_dir(self, xml_dir, score):
        """ Runs all tests in a given directory
        against the patched and unpatched versions of a binary

        Args:
            xml_dir (str): Directory containing all xml tests
            score (Score): Object to store the results in
        """
        # Check if there are any tests available in this directory
        tests = glob.glob(os.path.join(xml_dir, '*.xml'))
        if len(tests) == 0:
            debug('None found\n')
            return

        # *2 because each test is run against the patched and unpatched binary
        debug('Running {} test(s)'.format(len(tests) * 2))

        # Keep track of old pass/totals
        p, t = score.passed, score.total

        # Run the tests
        self.run_test(self.name, xml_dir, score)
        self.run_test('{}_patched'.format(self.name), xml_dir, score)

        # Display resulting totals
        debug(' => Passed {}/{}\n'.format(score.passed - p, score.total - t))

    def run(self):
        """Runs all tests for this challenge binary"""
        debug('\nTesting {}...\n'.format(self.name))

        # Test POVs
        if self.povs:
            debug('POV:\n\t')
            self.run_against_dir(self.pov_dir, self.povs)

        # Test POLLs
        if self.polls:
            debug('POLL:\n')
            for subdir in listdir(self.poll_dir):
                debug('\t{}:\t'.format(subdir))
                self.run_against_dir(os.path.join(self.poll_dir, subdir), self.polls)
        debug('Done testing {} => Passed {}/{} tests\n'.format(self.name, self.passed, self.total))


def test_challenges(chals):
    # type: (list) -> None
    # Filter out any challenges that don't exist
    for c in chals:
        cdir = os.path.join(CHAL_DIR, c)
        if not os.path.isdir(cdir):
            debug('ERR: Challenge "{}" does not exist, skipping\n'.format(c))
            chals.remove(c)

    # Create and run all testers
    testers = map(Tester, chals)
    for test in testers:
        test.run()


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

    g = parser.add_mutually_exclusive_group()
    g.add_argument('--povs', action='store_true',
                   help='Only run tests against POVs')

    g.add_argument('--polls', action='store_true',
                   help='Only run tests against POLLS')

    args = parser.parse_args(sys.argv[1:])

    # Disable other tests depending on args
    if args.povs:
        Tester.polls = False
    if args.polls:
        Tester.povs = False

    if args.all:
        debug('Running tests against all challenges\n')
        test_challenges(listdir(CHAL_DIR))
    elif args.chals:
        debug('Running tests against {} challenge(s)\n'.format(len(args.chals)))
        test_challenges(args.chals)


if __name__ == '__main__':
    main()
