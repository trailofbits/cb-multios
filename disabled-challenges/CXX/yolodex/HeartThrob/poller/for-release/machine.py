#!/usr/bin/env python
#
# Copyright (C) 2014 
#   Brian Caswell <bmc@lungetech.com>
#   Narf Industries <info@narfindustries.com>
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
from random import choice, randint
import imp
import os
import random
import string

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))


def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))

hello = "Hello.*"


class Heartthrob(Actions):
    RECV_BUF_LEN = 1044
    RESP_BUF_LEN = 1024

    def start(self):
        self.read(delim="try...\n\n", expect=hello, expect_format='pcre')

    def prompt(self):
        self.read(delim='> ', expect='> ')

    def john_nomatch(self):
        self.write("John: %s\n" % random_string(0,self.RECV_BUF_LEN-len("John: ")-1))
        # self.read(delim="\n-John\n\n", expect=".*",expect_format="pcre")
        self.read(delim="\n-John\n\n")

    def error(self):
        if self.chance(0.1):
            err = "E"
            self.write(random_string(self.RECV_BUF_LEN,self.RECV_BUF_LEN+50)+"\n")
            self.read(length=len(err),expect=err)
            return -1
        else:
            self.write(random_alpha(1,self.RECV_BUF_LEN-1)+'\n')
            self.read(delim='\n',expect="Error\n")

    def quit(self):
        self.write("quit\n")

    def empty(self):
        self.write("\n")
