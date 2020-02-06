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
import re
import struct
import string

def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(random.choice(chars) for _ in range(random.randint(a, b)))

def random_regex(a, b):
    def random_regex_element():
        ret = ''
        chars = string.letters + string.digits
        if random.random() < 0.7:
            ret = random.choice(chars)
        else:
            ret = random_string(2, 8)
            if random.random() < 0.2:
                ret = '^' + ret

            ret = '[%s]' % ret

        if random.random() < 0.1:
            ret += '*'

        return ret

    ret = ''.join(random_regex_element() for _ in range(random.randint(a, b)))

    if random.random() < 0.1:
        ret = '^' + ret

    if random.random() < 0.1:
        ret = ret + '$'

    return ret


class Command(object):
    def __init__(self, cmd, start, end, buf):
        self.cmd = cmd
        self.start = start
        self.end = end
        self.buf = buf

    def pack(self):
        return struct.pack('<ciiI', self.cmd, self.start, self.end, len(self.buf)) + self.buf

class Result(object):
    def __init__(self, result, buf, magic_page, full_unpack=False):
        self.result = result
        self.buf = buf
        self.magic_page = magic_page
        self.full_unpack = full_unpack

    def generate_csum(self):
        ret = 0
        for i in xrange(1024):
            ret = ret ^ ord(self.magic_page[i * 4])

        for c in self.buf:
            ret = ret ^ ord(c)

        return ret & 0xff

    def pack(self):
        if self.buf or self.full_unpack:
            return struct.pack('<iII', self.result, len(self.buf), self.generate_csum()) + self.buf
        else:
            return struct.pack('<i', self.result)

class Support(object):
    def __init__(self, magic_page):
        self.magic_page = magic_page

        self.lines_list = []
        self.marks = [-1] * 28
        self.just_marked = None

        self.EXIT_SUCCESS = 0
        self.EXIT_FAILURE = -1

    def fixup_marks(self, address):
        if address < 0:
            return self.marks[-address - 1]
        else:
            return address

    def random_range(self):
        if len(self.lines_list) == 0:
            return None

        if self.just_marked is not None:
            index = self.just_marked
            self.just_marked = None
            return (self.marks[index], len(self.lines_list) - 1)

        r = [random.randint(0, len(self.lines_list) - 1), random.randint(0, len(self.lines_list) - 1)]

        return (min(r), max(r))

    def do_invalid(self, cmd):
        return Result(self.EXIT_FAILURE, '', self.magic_page)

    def do_insert(self, cmd, append):
        start = self.fixup_marks(cmd.start)

        if append:
            start += 1

        for tok in cmd.buf.splitlines():
            if len(tok) > 256 or len(self.lines_list) > 256:
                return -1

            self.lines_list.insert(start, tok)
            start += 1

        return Result(self.EXIT_SUCCESS, '', self.magic_page)

    def do_delete(self, cmd):
        start = self.fixup_marks(cmd.start)
        end = self.fixup_marks(cmd.end)

        del self.lines_list[start:end + 1]

        return Result(self.EXIT_SUCCESS, '', self.magic_page)

    def do_change(self, cmd):
        self.do_delete(cmd)
        return self.do_insert(cmd, True)

    def do_join(self, cmd):
        start = self.fixup_marks(cmd.start)
        end = self.fixup_marks(cmd.end)

        for line in self.lines_list[start + 1:end + 1]:
            self.lines_list[start] += line

        del self.lines_list[start + 1:end + 1]

        return Result(self.EXIT_SUCCESS, '', self.magic_page)

    def do_mark(self, cmd):
        start = self.fixup_marks(cmd.start)
        index = struct.unpack('<I', cmd.buf)[0]

        if index >= 26:
            return Result(self.EXIT_FAILURE, '', self.magic_page)

        self.marks[index] = start
        self.just_marked = index

        return Result(self.EXIT_SUCCESS, '', self.magic_page)

    def do_list(self, cmd):
        start = self.fixup_marks(cmd.start)
        end = self.fixup_marks(cmd.end)
        contents = '\n'.join(self.lines_list[start:end + 1]) + '\n'

        return Result(self.EXIT_SUCCESS, contents, self.magic_page, True)

    def do_num(self, cmd):
        start = self.fixup_marks(cmd.start)
        end = self.fixup_marks(cmd.end)
        lines = [str(n + start + 1) + ' ' + s for n, s in enumerate(self.lines_list[start:end + 1])]
        contents = '\n'.join(lines) + '\n'

        return Result(self.EXIT_SUCCESS, contents, self.magic_page, True)

    def do_global(self, cmd, invert):
        start = self.fixup_marks(cmd.start)
        end = self.fixup_marks(cmd.end)

        lines = []
        if invert:
            lines = [line for line in self.lines_list[start:end + 1] if re.search(cmd.buf, line) is None]
        else:
            lines = [line for line in self.lines_list[start:end + 1] if re.search(cmd.buf, line) is not None]

        if not lines:
            return Result(self.EXIT_FAILURE, '', self.magic_page)

        contents = ''
        if lines:
            contents = '\n'.join(lines) + '\n'

        return Result(self.EXIT_SUCCESS, contents, self.magic_page, True)

    def do_transform(self, cmd):
        start = self.fixup_marks(cmd.start)
        end = self.fixup_marks(cmd.end)

        op = chr(struct.unpack('<I', cmd.buf)[0])

        if op not in 'ilu':
            return Result(self.EXIT_FAILURE, '', self.magic_page)

        for i, line in enumerate(self.lines_list[start:end + 1]):
            if op == 'i':
                self.lines_list[i + start] = ''.join(c.lower() if c.isupper() else c.upper() for c in line)
            elif op == 'l':
                self.lines_list[i + start] = line.lower()
            elif op == 'u':
                self.lines_list[i + start] = line.upper()

        return Result(self.EXIT_SUCCESS, '', self.magic_page)
