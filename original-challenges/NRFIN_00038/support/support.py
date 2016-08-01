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
import struct

class Support(object):
    def random_alpha(self, a, b):
        return ''.join(random.choice(string.letters) for _ in range(random.randint(a, b)))

    def __init__(self):
        self.logins = {}
        self.lastvar = 0

    def get_new_login(self):
        name = self.random_alpha(1, 16)
        while name in self.logins:
            name = self.random_alpha(1, 16)

        return name

    def get_existing_login(self):
        return random.choice(self.logins.items())

    def get_new_variable(self):
        self.lastvar += 1
        return self.lastvar

    def set_variable(self, name, var):
        self.logins[name] = var

