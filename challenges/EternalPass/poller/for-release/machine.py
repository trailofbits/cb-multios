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
import string
import sys
import os

from generator.actions import Actions
from random import choice,randint
from struct import *

WELCOME="Welcome to EternalPass! Please enter your last password: "
HOWMANY="\nHow many new passwords do you need? "
SEED="\nWhat seed to use for pw generation (0 for system seed)? "
PRNG="\nAddress of custom PRNG (ALPHA, unsupported, 0 for default)? "
PLZWAIT="\nPlease wait while we build your password file. While you wait, here are your plaintext passwords:\n"
HEREITIS="\nThanks for waiting! Here is your password file. Welcome!\n"
SECUREMODE="\nTry experimental secure mode (1 for yes)? "
SECUREMODESEEDS="\nEnter secure mode seeds: "

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

class EternalPass(Actions):
    def start(self):
        self.delay(50)
        pass
    def enter_pass(self):
        self.read(length=len(WELCOME),expect=WELCOME)
        self.passwd = random_alpha(10,20)
        self.write(self.passwd+"\n")
    def enter_num_pass(self):
        self.read(length=len(HOWMANY),expect=HOWMANY)
        self.count = randint(1,20)
        self.write(str(self.count)+"\n")
    def enter_seed(self):
        self.read(length=len(SEED),expect=SEED)
        self.seed = randint(0,1)
        self.write(str(self.seed)+"\n")
    def enter_prng(self):
        self.read(length=len(PRNG),expect=PRNG)
        #default, prng, another_prng
        self.prng = choice([0,0x08c6b0d0,0x08c6b100])
        self.write(str(self.prng)+"\n")
    def secure_mode(self):
        self.read(length=len(SECUREMODE),expect=SECUREMODE)
        #default, prng, another_prng
        self.secure_mode = choice([0,1])
        if self.secure_mode:
            self.write("1\n")
            self.read(length=len(SECUREMODESEEDS),expect=SECUREMODESEEDS)
            self.sseeds = [randint(0,0xffffffff) for i in range(4)]
            for s in self.sseeds:
                self.write("%d\n"%s)
        else:
            self.write("0\n")
    def get_results(self):
        self.read(length=len(PLZWAIT),expect=PLZWAIT)
        for i in range(self.count):
            self.read(expect=".*",delim="\n",expect_format="pcre")
        self.read(length=len(HEREITIS), expect=HEREITIS)
        #TODO actually parse rc4 buffer?

        
