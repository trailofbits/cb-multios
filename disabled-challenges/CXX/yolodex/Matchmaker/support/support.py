# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

import random
import string

def random_string(alphabet, min_len, max_len):
    return ''.join(random.choice(alphabet) for _ in xrange(random.randint(min_len, max_len)))

def random_set(alphabet, min_len, max_len):
    return set(random.choice(alphabet) for _ in xrange(random.randint(min_len, max_len)))

class Rng(object):
    def __init__(self):
        self.seed = 0xdeadbeef

    def rand(self):
        self.seed = 6364136223846793005 * self.seed + 1442695040888963407;
        return (self.seed >> 32) & 0xffffffff

class Dfa(object):
    def __init__(self, rng=None):
        self.states = []
        self.rng = rng if rng else Rng()

    @classmethod
    def make_random(cls, rng=None):
        self = cls(rng)
        num_states = random.randint(1, 8)

        for i in xrange(num_states):
            self.states.append(({}, (i != 0 and random.random() < 0.2)))
            default_alphabet = set(string.letters + string.digits + string.punctuation)
            num_transitions = random.randint(0, min(num_states, 4))
            for j in xrange(num_transitions):
                transition_set = random_set(list(default_alphabet), 1, 20)
                default_alphabet -= transition_set

                self.states[i][0][''.join(transition_set)] = random.randint(0, num_states - 1)

        return self

    def to_string(self):
        ret = []
        for state in self.states:
            if state[1]:
                ret.append('state accept')
            else:
                ret.append('state')

            for chars, dest in state[0].iteritems():
                ret.append('transition %s %s' % (chars, dest))

        ret.append('done')
        return '\n'.join(ret)

    def example(self, use_rng=True):
        ret = []
        current = 0

        can_accept = reduce(lambda x, a: x or a, [s[1] for s in self.states], False)
        if not can_accept:
            return None

        while len(ret) < (40 - 1) and not self.states[current][1]:
            # Get a sorted list of (char, dest) pairs
            d = {}
            for chars, dest in self.states[current][0].iteritems():
                for c in chars:
                    d[ord(c)] = dest
            table = [(key, d[key]) for key in sorted(d)]

            if len(table) == 0:
                return None

            if use_rng:
                i = self.rng.rand() % len(table)
            else:
                i = random.randint(0, len(table) - 1)

            ret.append(chr(table[i][0]))
            current = table[i][1]

        return ''.join(ret) if self.states[current][1] else None

    def accept(self, s):
        current = 0
        i = 0

        while not self.states[current][1]:
            found = False

            for chars, dest in self.states[current][0].iteritems():
                if i < len(s) and s[i] in chars:
                    found = True
                    current = dest
                    i += 1
                    break

            if not found:
                return False

        return self.states[current][1]

class Support(object):
    def __init__(self, magic_page):
        self.dfa = None
        self.rng = Rng()
        self.onmatch = 0
        self.magic_page = magic_page

    def calculate_csum(self, line):
        ret = 0
        for i in xrange(1024):
            ret = ret ^ ord(self.magic_page[i * 4])

        for i in xrange(len(line)):
            ret = ret ^ ord(line[i])

        return ret

    def make_dfa(self):
        self.dfa = Dfa.make_random(self.rng)
        return self.dfa.to_string()

    def make_invalid_dfa(self):
        alphabet = string.letters + string.digits + string.punctuation
        while True:
            s = random_string(alphabet, 1, 16)
            if s.startswith('state') or s.startswith('transition') or s.startswith('done'):
                continue
            return s

    def make_match(self):
        return self.dfa.example(False)

    def make_nomatch(self):
        # Possible that our DFA accepts all, so try 10 strings and then give up
        for _ in xrange(10):
            alphabet = string.letters + string.digits + string.punctuation
            s = random_string(alphabet, 1, 16)
            if not self.dfa.accept(s):
                return s

        return None

    def make_example(self):
        return self.dfa.example(True)

    def make_valid_onmatch(self):
        self.onmatch = random.randint(0, 2)
        return 'onmatch ' + ['default', 'length', 'xor'][self.onmatch]

    def make_invalid_onmatch(self):
        alphabet = string.letters + string.digits + string.punctuation
        while True:
            s = random_string(alphabet, 1, 16)
            if s == 'default' or s == 'length' or s == 'xor' or s == 'magic':
                continue
            return 'onmatch ' + s

    def make_onmatch_result(self, s):
        return [self.make_default_onmatch_result, self.make_length_onmatch_result, 
                self.make_xor_onmatch_result][self.onmatch](s)

    def make_default_onmatch_result(self, s):
        return 'Got a match! "%s"' % s

    def make_length_onmatch_result(self, s):
        return 'Got a match of length %s' % len(s)

    def make_xor_onmatch_result(self, s):
        x = 0
        for c in s:
            x ^= ord(c)

        return 'Checksum: %s' % x

