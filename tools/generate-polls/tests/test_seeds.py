#!/usr/bin/python

import re
import zipfile
import tempfile
import shutil
import os
import unittest
import subprocess


class generator_zip(unittest.TestCase):
    def setUp(self):
        self.tmp_dir = tempfile.mkdtemp('generator_zip')

    def tearDown(self):
        shutil.rmtree(self.tmp_dir)

    def read_zip(self, zip_filename):
        contents = []
        with zipfile.ZipFile(zip_filename, 'r') as zip_fh:
            for filename in zip_fh.namelist():
                contents.append((filename, zip_fh.read(filename)))
        return contents

    def expected_names(self, results, rounds, count):
        expected = []
        for i in range(rounds):
            expected += ['GEN_%05d_%05d.xml' % (i, x) for x in range(count)]
        names = [x[0] for x in results]
        self.assertEquals(expected, names)

    def expected_content_reuse(self,
                               results,
                               rounds,
                               repeat,
                               duplicate,
                               strip_seed=False):
        dup_min = 0
        dup_max = 0

        if repeat > 0:
            dup_min = rounds
            dup_max = rounds * repeat * duplicate

        contents = []
        dups = []

        for filename, content in results:
            if strip_seed is True:
                stripped = re.sub(r"<seed>.*</seed>", "", content)
                if stripped not in contents:
                    contents.append(stripped)
                else:
                    dups.append(stripped)
            else:
                if content not in contents:
                    contents.append(content)
                else:
                    dups.append(content)

        self.assertTrue(len(dups) >= dup_min)
        self.assertTrue(len(dups) <= dup_max)

    def test_zip(self):
        count = 30
        subprocess.check_output(
            ['./generate-polls', '--seed', '10', '--count', '%d' % count,
             '--package', 'poll-1.zip', 'examples/dfars/dfars.py',
             'examples/dfars/state-graph.yaml', self.tmp_dir])
        subprocess.check_output(
            ['./generate-polls', '--seed', '10', '--count', '%d' % count,
             '--package', 'poll-2.zip', 'examples/dfars/dfars.py',
             'examples/dfars/state-graph.yaml', self.tmp_dir])

        a = self.read_zip(os.path.join(self.tmp_dir, '0-poll-1.zip'))
        b = self.read_zip(os.path.join(self.tmp_dir, '0-poll-2.zip'))
        self.assertEquals(a, b)
        self.assertEquals(len(a), 30)

        self.expected_names(a, 1, count)
        self.expected_content_reuse(a, 1, 0, 0)

    def test_zip_rounds(self):
        rounds = 2
        count = 30
        subprocess.check_output(
            ['./generate-polls', '--round', '%d' % rounds, '--seed', '10',
             '--count', '%d' % count, '--package', 'poll-1.zip',
             'examples/dfars/dfars.py', 'examples/dfars/state-graph.yaml',
             self.tmp_dir])
        subprocess.check_output(
            ['./generate-polls', '--round', '%d' % rounds, '--seed', '10',
             '--count', '%d' % count, '--package', 'poll-2.zip',
             'examples/dfars/dfars.py', 'examples/dfars/state-graph.yaml',
             self.tmp_dir])

        a = self.read_zip(os.path.join(self.tmp_dir, '0-poll-1.zip'))
        a += self.read_zip(os.path.join(self.tmp_dir, '1-poll-1.zip'))
        b = self.read_zip(os.path.join(self.tmp_dir, '0-poll-2.zip'))
        b += self.read_zip(os.path.join(self.tmp_dir, '1-poll-2.zip'))
        self.assertEquals(a, b)
        self.assertEquals(len(a), rounds * count)
        self.expected_names(a, rounds, count)
        self.expected_content_reuse(a, 2, 0, 0)

    def test_zip_repeat(self):
        rounds = 2
        count = 30
        subprocess.check_output(
            ['./generate-polls', '--repeat', '5', '--duplicate', '5',
             '--round', '%d' % rounds, '--seed', '10', '--count', '%d' % count,
             '--package', 'poll-1.zip', 'examples/dfars/dfars.py',
             'examples/dfars/state-graph.yaml', self.tmp_dir])
        subprocess.check_output(
            ['./generate-polls', '--repeat', '5', '--duplicate', '5',
             '--round', '%d' % rounds, '--seed', '10', '--count', '%d' % count,
             '--package', 'poll-2.zip', 'examples/dfars/dfars.py',
             'examples/dfars/state-graph.yaml', self.tmp_dir])

        a = self.read_zip(os.path.join(self.tmp_dir, '0-poll-1.zip'))
        a += self.read_zip(os.path.join(self.tmp_dir, '1-poll-1.zip'))
        b = self.read_zip(os.path.join(self.tmp_dir, '0-poll-2.zip'))
        b += self.read_zip(os.path.join(self.tmp_dir, '1-poll-2.zip'))
        self.assertEquals(a, b)
        self.assertEquals(len(a), rounds * count)
        self.expected_names(a, rounds, count)
        self.expected_content_reuse(a, 2, 5, 5)

    def test_zip_repeat_with_seed(self):
        rounds = 2
        count = 30
        subprocess.check_output(
            ['./generate-polls', '--store_seed', '--repeat', '5',
             '--duplicate', '5', '--round', '%d' % rounds, '--seed', '10',
             '--count', '%d' % count, '--package', 'poll-1.zip',
             'examples/dfars/dfars.py', 'examples/dfars/state-graph.yaml',
             self.tmp_dir])
        subprocess.check_output(
            ['./generate-polls', '--store_seed', '--repeat', '5',
             '--duplicate', '5', '--round', '%d' % rounds, '--seed', '10',
             '--count', '%d' % count, '--package', 'poll-2.zip',
             'examples/dfars/dfars.py', 'examples/dfars/state-graph.yaml',
             self.tmp_dir])

        a = self.read_zip(os.path.join(self.tmp_dir, '0-poll-1.zip'))
        a += self.read_zip(os.path.join(self.tmp_dir, '1-poll-1.zip'))
        b = self.read_zip(os.path.join(self.tmp_dir, '0-poll-2.zip'))
        b += self.read_zip(os.path.join(self.tmp_dir, '1-poll-2.zip'))
        self.assertEquals(a, b)
        self.assertEquals(len(a), rounds * count)
        self.expected_names(a, rounds, count)
        self.expected_content_reuse(a, 0, 0, 0)
        self.expected_content_reuse(a, 2, 5, 5, strip_seed=True)

    def test_zip_magic_page_reuse(self):
        # in this case, the polls should use the magic seed, which prevents the poll from being repeatedly used.
        rounds = 2
        count = 50
        subprocess.check_output(
            ['./generate-polls', '--store_seed', '--repeat', '5',
             '--duplicate', '5', '--round', '%d' % rounds, '--seed', '10',
             '--count', '%d' % count, '--package', 'poll-1.zip',
             'examples/hangman/machine.py',
             'examples/hangman/state-graph.yaml', self.tmp_dir])
        subprocess.check_output(
            ['./generate-polls', '--store_seed', '--repeat', '5',
             '--duplicate', '5', '--round', '%d' % rounds, '--seed', '10',
             '--count', '%d' % count, '--package', 'poll-2.zip',
             'examples/hangman/machine.py',
             'examples/hangman/state-graph.yaml', self.tmp_dir])

        a = self.read_zip(os.path.join(self.tmp_dir, '0-poll-1.zip'))
        a += self.read_zip(os.path.join(self.tmp_dir, '1-poll-1.zip'))
        b = self.read_zip(os.path.join(self.tmp_dir, '0-poll-2.zip'))
        b += self.read_zip(os.path.join(self.tmp_dir, '1-poll-2.zip'))
        self.assertEquals(a, b)
        self.assertEquals(len(a), rounds * count)
        self.expected_names(a, rounds, count)
        self.expected_content_reuse(a, 2, 0, 0)
        self.expected_content_reuse(a, 2, 0, 0, strip_seed=True)


if __name__ == '__main__':
    unittest.main()
