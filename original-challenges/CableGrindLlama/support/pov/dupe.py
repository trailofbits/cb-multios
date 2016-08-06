#!/usr/bin/env python
#
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

from struct import *

typelen = {
    'ntohll':8,
    'letohll':8,
    'ntohl':4,
    'letohl':4,
    'ntohs':2,
    'letohs':2,
    'byte':1,
    'float':4,
    'double':8,
}

class DUPE(object):
    def __init__(self,ver=1,ctype=0,clen=-1,flen=1000,idx=0,heap=0,pkts=[]):
        self.ver = ver
        self.ctype = ctype
        self.clen = clen
        self.flen = flen
        self.idx = idx
        self.pkts = pkts
        self.heap = heap
    def __str__(self):
        pktdata = "".join(str(pkt) for pkt in self.pkts)
        if self.clen == -1:
            self.clen = len(pktdata)
        s = pack("<IIiiII",self.ver,self.ctype,self.clen,self.flen,self.idx,self.heap)
        return s+pktdata

class DUPEpkt(object):
    def __init__(self,data,ts=0,l=-1):
        self.data = data
        self.ts = ts
        if l == -1:
            self.l = len(data)
        else:
            self.l = l

    def __str__(self):
        return pack("<Ii",self.ts,self.l)+self.data

