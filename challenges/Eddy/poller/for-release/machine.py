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
import struct
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), 'support'))
from support import Support, Command, random_string, random_regex

class Eddy(Actions):
    def start(self):
        ##self.delay(100)
        self.state['model'] = Support(self.magic_page)

    def command(self):
        self.comment(repr(self.state['model'].lines_list))

    def invalid(self):
        r = self.state['model'].random_range()
        if not r:
            r = (0, 0)

        cmds = [c for c in string.lowercase + string.punctuation if c not in 'acdgijlmnqtv=']

        invalid_command = Command(random.choice(cmds), r[0], r[1], random_string(4, 40))
        self.write(invalid_command.pack())
        res = self.state['model'].do_invalid(invalid_command)
        expect = res.pack()
        self.read(length=len(expect), expect=expect)

    def append(self):
        r = self.state['model'].random_range()
        if not r:
            r = (0, 0)

        append_command = Command('a', r[0], r[1], random_string(4, 40))
        self.write(append_command.pack())
        res = self.state['model'].do_insert(append_command, True)
        expect = res.pack()
        self.read(length=len(expect), expect=expect)

    def insert(self):
        r = self.state['model'].random_range()
        if not r:
            r = (0, 0)

        insert_command = Command('i', r[0], r[1], random_string(4, 40))
        self.write(insert_command.pack())
        res = self.state['model'].do_insert(insert_command, False)
        expect = res.pack()
        self.read(length=len(expect), expect=expect)

    def change(self):
        r = self.state['model'].random_range()
        if not r:
            return

        change_command = Command('c', r[0], r[1], random_string(4, 40))
        self.write(change_command.pack())
        res = self.state['model'].do_change(change_command)
        expect = res.pack()
        self.read(length=len(expect), expect=expect)

    def delete(self):
        r = self.state['model'].random_range()
        if not r:
            return

        delete_command = Command('d', r[0], r[1], '')
        self.write(delete_command.pack())
        res = self.state['model'].do_delete(delete_command)
        expect = res.pack()
        self.read(length=len(expect), expect=expect)

    def join(self):
        r = self.state['model'].random_range()
        if not r:
            return

        join_command = Command('j', r[0], r[1], '')
        self.write(join_command.pack())
        res = self.state['model'].do_join(join_command)
        expect = res.pack()
        self.read(length=len(expect), expect=expect)

    def list(self):
        r = self.state['model'].random_range()
        if not r:
            return

        list_command = Command('l', r[0], r[1], '')
        self.write(list_command.pack())
        res = self.state['model'].do_list(list_command)
        expect = res.pack()
        self.read(length=len(expect), expect=expect)

    def num(self):
        if len(self.state['model'].lines_list) > 99:
            return

        r = self.state['model'].random_range()
        if not r:
            return

        num_command = Command('n', r[0], r[1], '')
        self.write(num_command.pack())
        res = self.state['model'].do_num(num_command)
        expect = res.pack()
        self.read(length=len(expect), expect=expect)

    def mark(self):
        if self.state['model'].just_marked is not None:
            return

        r = self.state['model'].random_range()
        if not r:
            return

        mark_command = Command('m', r[0], r[1], struct.pack('<I', random.randint(0, 25)))
        self.write(mark_command.pack())
        res = self.state['model'].do_mark(mark_command)
        expect = res.pack()
        self.read(length=len(expect), expect=expect)

    def global_cmd(self):
        r = self.state['model'].random_range()
        if not r:
            return

        global_command = Command('g', r[0], r[1], random_regex(2, 8))
        self.write(global_command.pack())
        self.comment("%s, %s", global_command.buf, self.state['model'].lines_list)
        res = self.state['model'].do_global(global_command, False)
        expect = res.pack()
        self.read(length=len(expect), expect=expect)

    def inverse_global_cmd(self):
        r = self.state['model'].random_range()
        if not r:
            return

        inverse_global_command = Command('v', r[0], r[1], random_regex(2, 8))
        self.write(inverse_global_command.pack())
        self.comment("%s, %s", inverse_global_command.buf, self.state['model'].lines_list)
        res = self.state['model'].do_global(inverse_global_command, True)
        expect = res.pack()
        self.read(length=len(expect), expect=expect)

    def transform(self):
        r = self.state['model'].random_range()
        if not r:
            return

        op = random.choice(string.lowercase)

        transform_command = Command('t', r[0], r[1], struct.pack('<I', ord(op)))
        self.write(transform_command.pack())
        res = self.state['model'].do_transform(transform_command)
        expect = res.pack()
        self.read(length=len(expect), expect=expect)

    def finish(self):
        quit_command = Command('q', 0, 0, '')
        self.write(quit_command.pack())
        ##self.delay(100)

