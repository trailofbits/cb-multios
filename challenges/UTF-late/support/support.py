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
            return self.files[name]
        else:
            return None

    def write_file(self, name, contents):
        if name not in self.files:
            self.files[name] = contents
            return True
        else:
            return False

    def pad_filename(self, name):
        return name + '\x00' * (self.MAX_FILE_NAME_LENGTH - len(name))

    def list_files(self):
        return ''.join(self.pad_filename(f) for f in self.files)

    def make_read_file(self, name):
        return struct.pack('<I', 0) + self.pad_filename(name)

    def make_write_file(self, name, length, contents):
        return struct.pack('<I', 1) + self.pad_filename(name) + \
                struct.pack('<I', length) + contents

    def make_list_files(self):
        return struct.pack('<I', 2)

    def make_quit(self):
        return struct.pack('<i', -1)

