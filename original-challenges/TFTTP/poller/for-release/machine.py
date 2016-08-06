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

from xml.sax.saxutils import escape
from generator.actions import Actions
from random import choice, randint, shuffle
from struct import pack,unpack
from math import ceil
import imp
import os
import random
import string

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def random_data(a,b):
    chars = ''.join(map(chr, range(256)))
    return ''.join(choice(chars) for _ in range(randint(a, b)))

def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))

class TFTTP(Actions):
    UPLOADFIN = "Information upload complete."
    pkttypes = {"PUT":0,"GET":1,"RAND":2,"RESP":3,"FRAG":4}
    MAX_ENTRIES = 2048
    MAX_KEYSZ = 128
    MAX_VALSZ = 256
    MAX_DATA_LEN = 256+128
    def start(self):
        if 'quotes' not in self.state:
            self.state['quotes'] = {} #key-val pairs of keys and quotes
        return

    def initial(self):
        #empty state, just used for dealing with "stateless" protocol
        return

    def _construct_pkt(self, code, data):
        return pack("<II",len(data),code)+data

    def _build_put_good(self):
        key,val = random_string(1,self.MAX_KEYSZ-1), random_string(1,self.MAX_VALSZ-1)
        while key in self.state['quotes']:
            key = random_string(1,self.MAX_KEYSZ)
        data = key+"\x00"+val+"\x00"
        return key,val,data

    def _build_get_good(self):
        if len(self.state['quotes']) == 0:
            self.put_good()
        key = choice(self.state['quotes'].keys())
        val = self.state['quotes'][key]
        return key,val


    def put_good(self):
        key,val,data = self._build_put_good()
        self.write(self._construct_pkt(self.pkttypes['PUT'], data))
        if len(self.state['quotes']) >= self.MAX_ENTRIES:
            #should terminate
            return -1
        self.state['quotes'][key] = val
        resp = self._construct_pkt(self.pkttypes['RESP'],
                self.UPLOADFIN+("\x00"*(256-len(self.UPLOADFIN)))) 
        self.read(length=len(resp),expect=resp);

    def get_good(self):
        key,val = self._build_get_good()
        req = self._construct_pkt(self.pkttypes['GET'],key)
        self.write(req)
        padded = val+("\x00"*(256-len(val)))
        resp = self._construct_pkt(self.pkttypes['RESP'],padded)
        self.read(length=len(resp),expect=resp)

    def rand_good(self):
        if len(self.state['quotes']) == 0:
            self.put_good()
        req = self._construct_pkt(self.pkttypes['RAND'],'8\x00')
        self.write(req)
        self.read(length=8,expect=escape(pack("<II",256,self.pkttypes['RESP'])))
        self.read(length=256, expect_format="pcre", expect=".*")
