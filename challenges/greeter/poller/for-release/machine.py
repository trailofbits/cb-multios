#!/usr/bin/env python
#
# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the 'Software'),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

from generator.actions import Actions, Variable
from os.path import dirname, abspath, join
import struct
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), 'support'))
from support import Support

class TokenForge(Actions):
    SUCCESS = '00000000'
    FAILURE = 'ffffffff'

    def start(self):
        self.state['model'] = Support()

    def login(self):
        name = self.state['model'].get_new_login()
        self.write('login ' + name + '\n')
        var = Variable('token' + str(self.state['model'].get_new_variable()))
        var.set_re('.*')
        self.state['model'].set_variable(name, var)
        self.read(delim='\n', assign=var)
        self.read(delim='\n', expect=self.SUCCESS)

    def greet(self):
        pass

    def valid_greet(self):
        name, var = self.state['model'].get_existing_login()
        self.write('greet ', var, '\n')
        self.read(delim='\n', expect_format='pcre', expect=r'Hello %s, we\'ve seen you \d+ times!' % name)
        self.read(delim='\n', expect=self.SUCCESS)

    def invalid_greet(self):
        # Generate a token that will be guaranteed to be rejected, minium
        # signature is 8 chars so get something below that
        self.write('greet counter=deadbeef|name=foobar|' + self.state['model'].random_alpha(1, 7) + '\n')
        self.read(delim='\n', expect=self.FAILURE)

    def quit(self):
        self.write('quit\n')

