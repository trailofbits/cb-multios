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
from random import choice, randint
from struct import pack,unpack
import imp
import os
import random
import string

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))


def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))


def random_data(a,b):
    chars = ''.join(map(chr, range(256)))
    return ''.join(choice(chars) for _ in range(randint(a, b)))

hello = "Hello.*"


class Heartthrob(Actions):
    RECV_BUF_LEN = 1024
    MAX_NAME_LEN = 127
    MAX_VID_LEN = 1024*129
    UINT_MAX = 2**32-1

    def start(self):
        self.state['videos'] = {}
        self.state['vidlist'] = []
        self.read(delim="needs!\n\n\n", expect=hello, expect_format='pcre')

    def prompt(self):
        self.read(delim='8=D ', expect='8=D ')

    def add_good(self):
        #here we provide valid add commands, but the videos are not necessarily valid
        #these will cause failures

        l = randint(4,4096)
        l -= l % 4
        buf = random_data(l, l)

        name = random_alpha(1,self.MAX_NAME_LEN)
        self.state['videos'][name] = {'buf':buf}
        
        if self.chance(0.5):
            csum = 0xffffffff & sum(unpack("<I",buf[i:i+4])[0]^0x42424242 for i in xrange(0,l,4))
            csum = pack("<I",csum)
            self.state['videos'][name]['badcsum'] = False
        else:
            csum = random_data(4, 4)
            self.state['videos'][name]['badcsum'] = True

        buf += csum

        self.write("add %s\n" % name)
        self.read(delim=": ", expect="Length")
        self.write(str(l+4)+"\n")
        self.read(delim="\n",expect="Your personal access key is: 0x42")
        self.write(buf)
        self.state['vidlist'].append(name)

    def play_good(self):
        '''try to play videos in list'''
        #in case we get called before adding video
        if len(self.state['videos']) == 0:
            self.write("\n")
            self.read(delim="\n",expect="wat")
            return
        vid = choice(self.state['videos'].items())
        key = "B" if self.chance(0.5) else chr(randint(0x0b,ord('A')))
        self.write("play %s %s\n" % (vid[0],key))

        if key != "B" or vid[1]['badcsum']:
            self.read(delim="\n",expect="I hate this hacker crap!")
        else:
            #calc expected xord, run-length decoded buffer
            xbuf = ''.join(chr(0x42^ord(i)) for i in vid[1]['buf'])
            xbuf = ''.join((ord(xbuf[i])+1)*xbuf[i+1] for i in xrange(0,len(xbuf),2))
            self.read(delim="PLAYBACK FINISHED\n",expect=xbuf+"\n")

    def list(self):
        '''list videos'''
        if len(self.state['videos']) == 0:
           self.write("\n")
           self.read(delim="\n",expect="wat")
           return
        self.write("list\n")
        for i,name in enumerate(self.state['vidlist']):
            self.read(delim="\n",expect=escape("%s.) %s" % (i+1,name)))
        
    def remove_good(self):
        '''test well formmated remove commands'''
        if len(self.state['videos']) == 0:
           self.write("\n")
           self.read(delim="\n",expect="wat")
        else:
            vid = choice(self.state['vidlist'])
            self.state['vidlist'].remove(vid)
            del self.state['videos'][vid]
            self.write("remove %s\n" % vid)
            self.read(delim="\n",expect="Creation is an act of sheer will. Next time it'll be flawless.")
        
    def quit(self):
        self.write("quit\n")
        self.read(delim="\n",expect="God help us, we're in the hands of engineers...")
