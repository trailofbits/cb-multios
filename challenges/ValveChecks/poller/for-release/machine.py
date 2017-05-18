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

from xml.sax.saxutils import escape
from generator.actions import Actions
from random import randint, choice
from struct import *

from hashlib import md5 as MD5
from struct import *
from zlib import crc32

def chunks(l, n):
    for i in xrange(0, len(l), n):
        yield l[i:i+n]

mask64 = 0xffffffffffffffff
class VPacket(object):
    def __init__(self,code, data,**kwargs):
        self.__dict__.update(kwargs)
        self.data = data[:128].ljust(128,"\x00")
        self.code = pack("<I",code)

    def __getattr__(self,x):
        return None

    def calc_md5(self):
        self.md5 = MD5(self.data).digest()

    def calc_crc(self):
        self.crc = pack("<i",crc32(self.data,0x50C0FFEE))

    def calc_additive(self):
        csum = 0xDEADBEEFC0FFEE
        csum += sum(unpack("<Q",x)[0] for x in chunks(self.data,8))
        self.additive = pack("<Q",csum&mask64)

    def calc_addxoradd(self):
        csum = 0x31337157C0FFEE
        for x in chunks(self.data,8):
            y = unpack("<Q",x)[0]
            csum += y
            csum &= mask64
            csum ^= y
            csum += y
            csum &= mask64
        self.addxoradd = pack("<Q",csum)

    def calc_fp(self):
        csum = 3.141592
        for x in chunks(self.data,8):
            csum += unpack("<d",x)[0]
        self.fp = pack("<d",csum)
    
    def __str__(self):
        if not self.md5:
            self.calc_md5()
        if not self.crc:
            self.calc_crc()
        if not self.additive:
            self.calc_additive()
        if not self.addxoradd:
            self.calc_addxoradd()
        if not self.fp:
            self.calc_fp()

        return self.code+self.data+self.additive+self.addxoradd+\
                self.fp+self.crc+self.md5

        


def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))


def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))

def random_data(a,b):
    chars = ''.join(map(chr, range(256)))
    return ''.join(choice(chars) for _ in range(randint(a, b)))
#   return ''.join(choice
#   return devrand.read(randint(a,b))
#   devrand = open("/dev/urandom","rb")

class SOMECHECKS(Actions):
    SUCCESS = "Valve successfully modified."
    INVALIDCSUM = "Invalid checksum."
    REDACTED = "This is not the function you're looking for."
    WATMAN = "NaNaNaNaNaNaNaNaNaNaNaNaNaN watman!"
    pkttypes = {"GETV":0,"SETV":1,"GETT":2,"NOTHERE":3}
    MAX_DATA_LEN = 128
    def start(self):
        pass
    def gett(self):
        pkt = VPacket(self.pkttypes['GETT'],"\x00"*128)
        self.write(str(pkt))
        self.read(delim="\n",expect="\d+",expect_format='pcre')
    def getv(self):
        pkt = VPacket(self.pkttypes['GETV'],random_data(1,128))
        self.write(str(pkt))
        self.read(delim="\n",expect="\d+",expect_format='pcre')
    def setv(self):
        pkt = VPacket(self.pkttypes['SETV'],random_data(1,128))
        self.write(str(pkt))
        self.read(delim="\n",expect=self.SUCCESS)
    def redacted(self):
        pkt = VPacket(self.pkttypes['NOTHERE'],
                pack("<I",randint(0,4))+random_data(1,124))
        self.write(str(pkt))
        self.read(delim="\n",expect=self.REDACTED)
    def badadd(self):
        pkt = VPacket(randint(4,255),random_data(1,128),
                additive=random_data(8,8)) 
        self.write(str(pkt))
        self.read(delim="\n",expect=self.INVALIDCSUM)
    def badaddxor(self):
        pkt = VPacket(randint(4,255),random_data(1,128),
                addxoradd=random_data(8, 8))
        self.write(str(pkt))
        self.read(delim="\n",expect=self.INVALIDCSUM)
    def badcrc(self):
        pkt = VPacket(randint(4,255),random_data(1,128),
                crc=random_data(4, 4))
        self.write(str(pkt))
        self.read(delim="\n",expect=self.INVALIDCSUM)
    def badfp(self):
        #no randomized bad fp because of how nasty this gets in python
        #we just want to make sure here that the branch gets exercised
        pkt = VPacket(randint(4,255),random_data(1,128),
                fp="AAAAAAAA")
        self.write(str(pkt))
        self.read(delim="\n",expect=self.INVALIDCSUM)
    def badmd5(self):
        pkt = VPacket(randint(4,255),random_data(1,128),
                additive=random_data(8, 8))
        self.write(str(pkt))
        self.read(delim="\n",expect=self.INVALIDCSUM)
    def badcmd(self):
        pkt = VPacket(randint(4,255),random_data(1,128))
        self.write(str(pkt))
        self.read(delim="\n",expect=self.WATMAN)
