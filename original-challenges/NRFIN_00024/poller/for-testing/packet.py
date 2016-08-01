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
from random import randint
from struct import pack

def chunks(l, n):
    for i in xrange(0, len(l), n):
        yield l[i:i+n]

class LMSSession(object):
    def __init__(self,data,tnum,fnum,sid=None,randsize=False):
        self.data = data

        self.tnum = tnum
        self.fnum = fnum

        self.sid = sid if sid != None else randint(0,2**32-1)

        if randsize:
            self.msgs = []
            idx = 0
            while idx < len(data):
                maxint = 256 if len(data[idx:]) > 256 else len(data[idx:])
                s = randint(1,maxint)
                self.msgs.append(data[idx:idx+s])
                idx += s
        else:
            self.msgs = [i for i in chunks(self.data,256)]



        self.msgs = [LMSMsg(i,j,self) for j,i in enumerate(self.msgs)]

class LMSMsg(object):
    def __init__(self,data,mid=None,session=None):
        self.data = data
        self.size = len(data)
        self.count = len(session.msgs) if session else 1
        self.sid = session.sid if session else 0
        self.mid = mid if mid != None else 0
        self.tnum = session.tnum if session else "\x00"*8
        self.fnum = session.fnum if session else "\x00"*8
    def __str__(self):
        return self.tnum+self.fnum+pack("<HHHH",self.sid,
                self.mid,self.count,self.size)+self.data
