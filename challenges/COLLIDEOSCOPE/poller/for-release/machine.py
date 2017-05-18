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
import string
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), 'support'))
from support import Support

class Collideoscope(Actions):
    def start(self):
        self.delay(50)
        self.state['model'] = Support(self.magic_page)

    def command(self):
        self.read(length=2, expect='> ')

    def invalid(self):
        alphabet = list(string.printable)
        alphabet.remove('\n')
        alphabet.remove('%')

        length = random.randint(1, 100)

        s = ''.join([random.choice(alphabet) for _ in xrange(length)])
        # Make sure this is invalid
        s += '(\n'

        self.write(s)
        self.read(delim='\n', expect='ERROR!\n')

    def valid(self):
        s, e, v = self.state['model'].create_expression()
        self.write(s)

        lines = e.splitlines()
        for l in lines[:-1]:
            self.read(delim='\n', expect=l+'\n')

        l = lines[-1]
        if l == '_ = <ptr>':
            l = l.replace('<ptr>', '-?[0-9a-f]*')
            self.read(delim='\n', expect='^'+l+'$', expect_format='pcre')
            self.read(delim='\n', expect='^[0-9a-f]*$', expect_format='pcre')
        elif l != 'ERROR!':
            self.read(delim='\n', expect=l+'\n')
            csum_str = '%x' % self.state['model'].calculate_csum(v)
            csum_str = '0' * (8 - len(csum_str)) + csum_str + '\n'
            self.read(length=len(csum_str), expect=csum_str)
        else:
            self.read(delim='\n', expect=l+'\n')

    def tokens(self):
        self.state['model'].toggle_tokens()
        self.write('%tokens\n')

    def ast(self):
        self.state['model'].toggle_ast()
        self.write('%ast\n')

    def quit(self):
        self.write('%quit\n')

