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
    MAX_FILE_NAME_LENGTH = 16
    MAX_FILE_SIZE = 4088

    def random_alpha(self, a, b):
        return ''.join(random.choice(string.letters) for _ in range(random.randint(a, b)))

    def __init__(self):
        self.files = {}

    def get_new_filename(self):
        name = self.random_alpha(1, self.MAX_FILE_NAME_LENGTH)
        return name if name not in self.files else self.get_new_name()

    def get_new_contents(self):
        return self.random_alpha(1, self.MAX_FILE_SIZE)

    def get_filename(self):
        return random.choice(self.files.keys()) if self.files else None

    def read_file(self, name):
        if name in self.files:
            contents = self.files[name]
            if contents.startswith('link:'):
                return self.read_file(contents[5:])
            else:
                return contents
        else:
            return None

    def write_file(self, name, contents):
        if name not in self.files:
            if self.files[name].startswith('link:'):
                return self.write_file(self.files[name][5:], contents)
            else:
                self.files[name] = contents
            return True
        else:
            return False

    def link_file(self, src, dst):
        return self.write_file(self, src, 'link:' + dst)

    def delete_file(self, name):
        del self.files[name]

    def pad_filename(self, name):
        return name + '\x00' * (self.MAX_FILE_NAME_LENGTH - len(name))

    def make_cd(self, name):
        return struct.pack('<I', 0) + self.pad_filename(name)

    def make_read_file(self, name):
        return struct.pack('<I', 1) + self.pad_filename(name)

    def make_write_file(self, name, length, contents):
        return struct.pack('<I', 2) + self.pad_filename(name) + \
                struct.pack('<I', length) + contents
                
    def make_ln(self, src, dst):
        return struct.pack('<I', 3) + self.pad_filename(src) + \
                struct.pack('<I', len(dst)) + dst

    def make_rm(self, name):
        return struct.pack('<I', 4) + self.pad_filename(name)

    def make_quit(self):
        return struct.pack('<i', -1)

