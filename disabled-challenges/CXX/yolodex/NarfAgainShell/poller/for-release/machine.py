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
import struct
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
from support import Support

class Linkronicity(Actions):
    SUCCESS = struct.pack('<i', 0)
    FAILURE = struct.pack('<i', -1)

    def start(self):
        self.state['model'] = Support()

    def cmd(self):
        pass

    def cd(self):
        # Can only read/write to one directory under normal operation, so just
        # hop out then back in
        self.write(self.state['model'].make_cd('..'))
        self.read(length=len(self.SUCCESS), expect=self.SUCCESS)
        self.write(self.state['model'].make_cd('user'))
        self.read(length=len(self.SUCCESS), expect=self.SUCCESS)

    def read_file(self):
        pass

    def valid_read_file(self):
        name = self.state['model'].get_filename()
        if not name:
            return
        exp = self.state['model'].read_file(name)
        if exp is not None:
            self.write(self.state['model'].make_read_file(name))
            self.read(length=len(exp), expect=exp)
            self.read(length=len(self.SUCCESS), expect=self.SUCCESS)

    def invalid_read_file(self):
        name = self.state['model'].get_new_filename()
        self.write(self.state['model'].make_read_file(name))
        self.read(length=len(self.FAILURE), expect=self.FAILURE)

    def write_file(self):
        pass

    def valid_write_file(self):
        name = self.state['model'].get_filename()
        if not name:
            return
        contents = self.state['model'].get_new_contents()
        exp = self.state['model'].write_file(name, contents)
        if exp:
            self.write(self.state['model'].make_write_file(name, len(contents), contents))
            self.read(length=len(self.SUCCESS), expect=self.SUCCESS)

    def invalid_write_file(self):
        name = self.state['model'].get_filename()
        if not name:
            return
        contents = ''
        self.write(self.state['model'].make_write_file(name, len(contents), contents))
        self.read(length=len(self.FAILURE), expect=self.FAILURE)

    def too_big_write_file(self):
        name = self.state['model'].get_new_filename()
        self.write(self.state['model'].make_write_file(name, 2 * self.state['model'].MAX_FILE_SIZE, ''))
        self.read(length=len(self.FAILURE), expect=self.FAILURE)

    def ln(self):
        pass

    def valid_ln(self):
        src = self.state['model'].get_new_filename()
        dst = self.state['model'].get_filename()
        if not dst:
            return
        self.write(self.state['model'].make_ln(src, dst))
        self.read(length=len(self.SUCCESS), expect=self.SUCCESS)

    def invalid_ln(self):
        src = self.state['model'].get_filename()
        dst = self.state['model'].get_filename()
        if not src or not dst:
            return
        self.write(self.state['model'].make_ln(src, dst))
        self.read(length=len(self.FAILURE), expect=self.FAILURE)

    def rm(self):
        pass

    def valid_rm(self):
        name = self.state['model'].get_filename()
        if not name:
            return
        self.write(self.state['model'].make_rm(name))
        self.read(length=len(self.SUCCESS), expect=self.SUCCESS)

    def invalid_rm(self):
        name = self.state['model'].get_new_filename()
        self.write(self.state['model'].make_rm(name))
        self.read(length=len(self.FAILURE), expect=self.FAILURE)

    def finish(self):
        self.write(self.state['model'].make_quit())

