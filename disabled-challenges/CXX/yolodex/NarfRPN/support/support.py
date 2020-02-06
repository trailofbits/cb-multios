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

import ctypes
import random
import re
import struct

from binascii import hexlify

class Matrix(object):
    def __init__(self, width, height, data=None, valid=True):
        self.width = width
        self.height = height
        self.data = data

        # Disallow singular matrices to avoid vulnerability
        while not self.data or self.det() == 0.0:
            self.data = []
            for i in xrange(height):
                self.data.append([])
                for j in xrange(width):
                    self.data[i].append(random.uniform(-Support.FLOAT_LIMIT, Support.FLOAT_LIMIT))

        if not valid:
            self.data[random.randint(0, self.height - 1)][random.randint(0, self.width - 1)] = float('inf')

    def __str__(self):
        return str(self.data)

    def __add__(self, other):
        data = []
        if isinstance(other, (int, long, float)):
            for i in xrange(self.height):
                data.append([])
                for j in xrange(self.width):
                    data[i].append(self.data[i][j] + float(other))

            return Matrix(self.width, self.height, data)
        elif isinstance(other, Matrix):
            if self.width != other.width or self.height != other.height:
                raise ValueError()

            for i in xrange(self.height):
                data.append([])
                for j in xrange(self.width):
                    data[i].append(self.data[i][j] + other.data[i][j])

            return Matrix(self.width, self.height, data)
        else:
            return NotImplemented

    def __radd__(self, other):
        return self + other

    def __sub__(self, other):
        if isinstance(other, (int, long, float)):
            return self + -other
        elif isinstance(other, Matrix):
            neg = Matrix(other.width, other.height, [[-x for x in c] for c in other.data])
            return self + neg
        else:
            return NotImplemented

    def __rsub__(self, other):
        neg = Matrix(self.width, self.height, [[-x for x in c] for c in self.data])
        return neg + other

    def __mul__(self, other):
        data = []
        if isinstance(other, (int, long, float)):
            for i in xrange(self.height):
                data.append([])
                for j in xrange(self.width):
                    data[i].append(self.data[i][j] * float(other))

            return Matrix(self.width, self.height, data)
        elif isinstance(other, Matrix):
            if self.width != other.height:
                raise ValueError()

            for i in xrange(self.height):
                data.append([])
                for j in xrange(other.width):
                    data[i].append(0.0)
                    for k in xrange(self.width):
                        data[i][j] += self.data[i][k] * other.data[k][j]

            return Matrix(self.height, other.width, data)
        else:
            return NotImplemented

    def __rmul__(self, other):
        return self * other

    def __div__(self, other):
        data = []
        if isinstance(other, Matrix):
            return NotImplemented
        elif isinstance(other, (int, long, float)):
            for i in xrange(self.height):
                data.append([])
                for j in xrange(self.width):
                    data[i].append(self.data[i][j] / other)

            return Matrix(self.width, self.height, data)
        else:
            return NotImplemented

    def __rdiv__(self, other):
        return Matrix(self.width, self.height, [[other / x for x in c] for c in self.data])

    def det(self):
        if self.width != self.height:
            return None

        if self.width == 1:
            return self.data[0][0]
        elif self.width == 2:
            return (self.data[0][0] * self.data[1][1]) - (self.data[0][1] * self.data[1][0])
        else:
            return None

    def inv(self):
        det = self.det()

        if det is None or det == 0.0:
            raise ValueError()

        data = []
        for i in xrange(self.height):
            data.append([])
            for j in xrange(self.width):
                data[i].append(0.0)

        if self.width == 1:
            data[0][0] = 1.0 / det
        elif self.width == 2:
            data[0][0] = self.data[1][1] / det
            data[0][1] = (-self.data[0][1]) / det
            data[1][0] = (-self.data[1][0]) / det
            data[1][1] = self.data[0][0] / det
        else:
            raise ValueError()

        return Matrix(self.width, self.height, data)

class Support(object):
    FLOAT_LIMIT = 100000
    INT_LIMIT = 0x7fffffff

    def __init__(self):
        self.stack = []

    def push(self, operand):
        self.stack.append(operand)

    def pop(self):
        if not self.stack:
            return None

        return self.stack.pop()

    def clear(self):
        self.stack = []

    def binary_op(self, op):
        b = self.pop()
        if b is None:
            return -1

        a = self.pop()
        if a is None:
            self.push(b)
            return -1

        try:
            res = op(a, b)
            if isinstance(res, (int, long)):
                # Simulate integer overflow
                res = ctypes.c_int(res & 0xffffffff).value

            self.push(res)
            return 0
        except:
            self.push(a)
            self.push(b)
            return -1

    def add(self):
        return self.binary_op(lambda a, b: a + b)

    def sub(self):
        return self.binary_op(lambda a, b: a - b)

    def mul(self):
        return self.binary_op(lambda a, b: a * b)

    def div(self):
        # Python integer div floors, not truncate towards 0 like C
        def c_div(a, b):
            if isinstance(a, (int, long)) and isinstance(b, (int, long)):
                return int(float(a) / b)
            else:
                return a / b

        return self.binary_op(c_div)

    def inv(self):
        a = self.pop()

        try:
            if a.det() == 0.0:
                raise ValueError()
            res = a.inv()
            self.push(res)
            return 0
        except:
            self.push(a)
            return -1

    def pack_value(self, value, fuzzy=False):
        if isinstance(value, (int, long)):
            ret = struct.pack('<II', 0, value & 0xffffffff)
            return ret, len(ret)
        elif isinstance(value, Matrix):
            ret = struct.pack('<HBB', 1, value.width, value.height)
            length = len(ret)
            if fuzzy:
                ret = ''.join(['\\x' + hexlify(c) for c in ret])

            for i in xrange(value.height):
                for j in xrange(value.width):
                    packed = struct.pack('<d', value.data[i][j])
                    length += len(packed)
                    # Deal with differences in float precision
                    if fuzzy:
                        packed = '...' + ''.join(['\\x' + hexlify(c) for c in packed[3:]])
                    ret += packed
            return ret, length
        elif isinstance(value, float):
            ret = struct.pack('<Id', 2, value)
            return ret, len(ret)

    def make_push(self, value):
        return struct.pack('<I', 0) + self.pack_value(value)[0]

    def make_pop(self):
        return struct.pack('<I', 1)

    def make_clear(self):
        return struct.pack('<I', 2)

    def make_add(self):
        return struct.pack('<I', 3)

    def make_sub(self):
        return struct.pack('<I', 4)

    def make_mul(self):
        return struct.pack('<I', 5)

    def make_div(self):
        return struct.pack('<I', 6)

    def make_inv(self):
        return struct.pack('<I', 7)

    def make_quit(self):
        return '\xff' * 4

