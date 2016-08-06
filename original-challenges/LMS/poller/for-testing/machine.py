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
from random import choice,randint,random
from numpy.random import randint as nprandint
from struct import *


sys.path.append(os.path.dirname(os.path.realpath(__file__)))

from packet import *

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))

def urand(size):
    return ''.join(chr(randint(0,255)) for _ in range(size)) 

class LMS(Actions):
    def start(self):
        pass
    def valid(self):
        valid_tnum = pack("<II",0x73317331,1<<28|3<<24) #pack in our num and outstanding count
        valid_fnum = pack("<II",randint(0,2**32-1),randint(0,2**32-1))

        num_sessions = 1
        
        #dat list comprehension
        sessions = [LMSSession(urand(randint(1,256*100)),valid_tnum,valid_fnum,i) 
                   for i in set([randint(0,2**16-1) for i in xrange(0,num_sessions)])]

        for sess in sessions:
            for msg in sorted(sess.msgs, key=lambda k: random()):
                self.write(str(msg))
            self.read(length=len(sess.data),expect=sess.data)

    def valid_randlen(self):
        valid_tnum = pack("<II",0x73317331,1<<28|3<<24)
        valid_fnum = pack("<II",randint(0,2**32-1),randint(0,2**32-1))
        num_sessions = 1
        
        #dat list comprehension
        sessions = [LMSSession(urand(randint(1,256*100)),valid_tnum,
                    valid_fnum,i,randsize=True) for i in
                    set([randint(0,2**16-1) for i in xrange(0,num_sessions)])]

        for sess in sessions:
            for msg in sorted(sess.msgs, key=lambda k: random()):
                self.write(str(msg))
            self.read(length=len(sess.data),expect=sess.data)

    def invalid_badlen(self):
        valid_tnum = pack("<II",0x73317331,1<<28|3<<24)
        msg = LMSMsg(urand(randint(1,256)))
        msg.size = 0 if choice([True,False]) else randint(257,2**16-1)
        msg.tnum = valid_tnum
        self.write(str(msg))
        self.read(delim="\n",expect="ROFL FALAFELS!")
    def invalid_badmid(self):
        valid_tnum = pack("<II",0x73317331,1<<28|3<<24)
        valid_fnum = pack("<II",randint(0,2**32-1),randint(0,2**32-1))
        num_sessions = 1
        
        #dat list comprehension
        sessions = [LMSSession(urand(randint(1,256*100)),valid_tnum,
                    valid_fnum,i,randsize=True) for i in
                    set([randint(0,2**16-1) for i in xrange(0,num_sessions)])]

        for sess in sessions:
            for msg in sorted(sess.msgs, key=lambda k: random()):
                self.write(str(msg))
                if (random() < 0.05):
                    msg.mid = randint(len(sess.msgs),2**16-1)
                    self.write(str(msg))
            self.read(length=len(sess.data),expect=sess.data)
        
