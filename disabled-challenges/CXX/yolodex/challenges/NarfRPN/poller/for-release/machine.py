#!/usr/bin/env python
#
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

from generator.actions import Actions
from os.path import dirname, abspath, join
import random
import struct
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
from support import Support, Matrix

class PolandBall(Actions):
    SUCCESS = '\x00' * 4
    FAILURE = '\xff' * 4

    def start(self):
        self.state['model'] = Support()

    def cmd(self):
        pass

    def push(self):
        pass

    def push_int(self):
        val = random.randint(-Support.INT_LIMIT, Support.INT_LIMIT)
        self.state['model'].push(val)
        self.write(self.state['model'].make_push(val))
        self.read(length=4, expect=self.SUCCESS)

    def push_matrix(self):
        pass

    def push_square_matrix(self):
        size = random.randint(1, 2)
        val = Matrix(size, size)
        self.state['model'].push(val)
        self.write(self.state['model'].make_push(val))
        self.read(length=4, expect=self.SUCCESS)

    def push_large_matrix(self):
        width = random.randint(3, 16)
        height = random.randint(3, 16)
        val = Matrix(width, height)
        self.state['model'].push(val)
        self.write(self.state['model'].make_push(val))
        self.read(length=4, expect=self.SUCCESS)

    def push_invalid_matrix(self):
        size = random.randint(1, 8)
        self.write(self.state['model'].make_push(Matrix(size, size, None, False)))
        self.read(length=4, expect=self.FAILURE)

    def push_double(self):
        pass

    def push_valid_double(self):
        val = random.uniform(-Support.FLOAT_LIMIT, Support.FLOAT_LIMIT)
        self.state['model'].push(val)
        self.write(self.state['model'].make_push(val))
        self.read(length=4, expect=self.SUCCESS)

    def push_invalid_double(self):
        self.write(self.state['model'].make_push(float('inf')))
        self.read(length=4, expect=self.FAILURE)

    def pop(self):
        res = self.state['model'].pop()
        self.write(self.state['model'].make_pop())
        if res is not None:
            fuzzy = isinstance(res, Matrix)
            packed, length = self.state['model'].pack_value(res, fuzzy=fuzzy)
            self.read(length=length, expect=packed, expect_format='pcre' if fuzzy else 'asciic')
            self.read(length=4, expect=self.SUCCESS)
        else:
            self.read(length=4, expect=self.FAILURE)

    def clear(self):
        self.state['model'].clear()
        self.write(self.state['model'].make_clear())
        self.read(length=4, expect=self.SUCCESS)

    def add(self):
        exp = self.state['model'].add()
        self.write(self.state['model'].make_add())
        self.read(length=4, expect=self.SUCCESS if exp == 0 else self.FAILURE)

    def sub(self):
        exp = self.state['model'].sub()
        self.write(self.state['model'].make_sub())
        self.read(length=4, expect=self.SUCCESS if exp == 0 else self.FAILURE)

    def mul(self):
        exp = self.state['model'].mul()
        self.write(self.state['model'].make_mul())
        self.read(length=4, expect=self.SUCCESS if exp == 0 else self.FAILURE)

    def div(self):
        exp = self.state['model'].div()
        self.write(self.state['model'].make_div())
        self.read(length=4, expect=self.SUCCESS if exp == 0 else self.FAILURE)

    def inv(self):
        exp = self.state['model'].inv()
        # Avoid vuln by not inverting when invalid
        if exp == -1:
            return

        self.write(self.state['model'].make_inv())
        self.read(length=4, expect=self.SUCCESS if exp == 0 else self.FAILURE)

    def finish(self):
        self.write(self.state['model'].make_quit())

    def invalid_cmd(self):
        self.write(struct.pack('<I', random.randint(8, 2 ** 32 - 1)))
        self.read(length=4, expect=self.FAILURE)


