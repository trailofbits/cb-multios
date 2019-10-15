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

    def will_match(self):
        max_len = self.RECV_BUF_LEN-len("William: <3 ")-1
        test_str = "<3 "
        if self.chance(0.5):
            while len(test_str) < randint(0,max_len):
                if self.chance(0.5):
                    test_str += "your" if self.chance(0.5) else "has"
                else:
                    test_str += random_string(1,max_len-len(test_str))

            test_str = test_str[:max_len]

            expected_str = test_str.replace("your","thy").replace("has","hath")
            expected_str = expected_str[:self.RESP_BUF_LEN]

        else:
            test_str += random_string(0, max_len-3)
            expected_str = test_str.replace("your","thy").replace("has","hath")[0:self.RESP_BUF_LEN-4]

        #want to match both patched/unpatched versions
        if(len(expected_str) > len(test_str)):
            expected_str = expected_str[:len(test_str)-2-len("William: ")]

        self.write("William: %s\n" % test_str)
        self.read(delim="\n",expect=expected_str)

    def will_nomatch(self):
        self.write("William: %s\n" % random_string(0,self.RECV_BUF_LEN-len("William: ")-1))
        self.read(delim="\n", expect="(bb|[^b]{2})?\n")
        
    def eliz_all(self):
        self.write("Elizabeth: %s\n" % random_string(0,self.RECV_BUF_LEN-len("Elizabeth: ")-1))
        self.read(delim="\n", expect="I love thee seven ways.\n")

    def edgr_match(self):
        test_str = "lenore"+random_string(0,self.RESP_BUF_LEN-\
                len("Edgar: lenore")-len(" - Quoth the raven, 'Nevermore'.\n")-1)
        expected_str = test_str+" - Quoth the raven, 'Nevermore'."
        expected_str = expected_str[:self.RESP_BUF_LEN-1]+"\n"
        self.write("Edgar: %s\n" % test_str)
        self.read(delim="\n", expect=expected_str)

    def edgr_nomatch(self):
        test_str = random_string(0,self.RECV_BUF_LEN-len("Edgar: ")-1)
        expected_str = test_str + " - Nevermore"
        expected_str = expected_str[:self.RESP_BUF_LEN-1]+"\n"
        self.write("Edgar: %s\n" % test_str)
        self.read(delim="\n", expect=expected_str)

    def john_nomatch(self):
        self.write("John: %s\n" % random_string(0,self.RECV_BUF_LEN-len("John: ")-1))
        self.read(delim="\n-John\n\n")
#        self.read(delim="\n-John\n\n", expect=".*",expect_format="pcre")

    def john_match(self):
        self.write("John: hoff\n")
        self.read(delim=".. ...\n\n\n", expect="YOU STILL CAN'T.*", expect_format='pcre')

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
