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

from generator.actions import Actions
from os.path import dirname, abspath, join
import random
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), 'support'))
from support import Support

class Matchmaker(Actions):
    def start(self):
        self.delay(50)
        self.state['model'] = Support(self.magic_page)

    def init_dfa(self):
        dfa = self.state['model'].make_dfa().splitlines()

        for line in dfa:
            if self.chance(0.1):
                self.write(self.state['model'].make_invalid_dfa() + '\n')
                self.read(delim='\n', expect='Invalid')

            self.write(line + '\n')

        self.read(delim='\n', expect='Ok, matching input now')

    def cont(self):
        pass

    def match(self):
        pass

    def valid_match(self):
        matching_input = self.state['model'].make_match()
        if matching_input:
            self.write(matching_input + '\n')
            self.read(delim='\n', expect=self.state['model'].make_onmatch_result(matching_input))
            csum_str = '%x' % self.state['model'].calculate_csum(matching_input)
            csum_str = '0' * (8 - len(csum_str)) + csum_str + '\n'
            self.read(length=len(csum_str), expect=csum_str)

    def invalid_match(self):
        unmatching_input = self.state['model'].make_nomatch()
        if unmatching_input:
            self.write(unmatching_input + '\n')
            self.read(delim='\n', expect='No match :( "%s"' % unmatching_input)

    def onmatch(self):
        pass

    def valid_onmatch(self):
        self.write(self.state['model'].make_valid_onmatch() + '\n')
        self.read(delim='\n', expect='Match action updated')

    def invalid_onmatch(self):
        self.write(self.state['model'].make_invalid_onmatch() + '\n')
        self.read(delim='\n', expect='Unrecognized action')

    def example(self):
        example = self.state['model'].make_example()
        if example:
            self.write('example' + '\n')
            self.read(delim='\n', expect='Here\'s an example: "%s"' % example)
        else:
            self.write('example' + '\n')
            self.read(delim='\n', expect='Error, are you done initializing?')

    def reset_dfa(self):
        self.write('reset' + '\n')
        self.read(delim='\n', expect='Please re-enter state machine')

    def quit(self):
        self.write('quit' + '\n')

