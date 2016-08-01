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

def random_data(a,b):
    chars = ''.join(map(chr, range(256)))
    return ''.join(choice(chars) for _ in range(randint(a, b)))

def random_string(a, b):
    chars = string.letters + string.digits
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

    def add_bad(self):
        t = randint(0,9)
        cmd = "add "
        if t < 2:
            #overly long name or empty string
            if self.chance(0.5):
                cmd += random_alpha(self.MAX_NAME_LEN+1,self.RECV_BUF_LEN-4)
        elif  t < 9:
            #name exists or space in filename
            if self.chance(0.5):
                if len(self.state['videos']) > 0:
                    cmd += choice(self.state['videos'].keys())
                else:
                    cmd += " "
            else:
                cmd += " "
        else:
            #overly long size, too short, or not multiple of 4
            #we trigger this case later
            name = random_alpha(1,self.MAX_NAME_LEN)
            while name in self.state['videos']:
                name = random_alpha(1,self.MAX_NAME_LEN)
            cmd += name
        self.write(cmd+'\n')

        if t < 2:
            #just some ascii art, don't care
            self.read(delim="\n", expect="You didn't say the magic word.")
            return -1
        elif t < 9:
            self.read(delim="\n", expect="It's a UNIX system, I know this!")
        else:
            self.read(delim=": ", expect="Length")
            t = randint(0,8)
            if t < 3:
                num = randint(self.MAX_VID_LEN+1,self.UINT_MAX)
            elif t < 6:
                num = randint(0,7)
            else:
                num = randint(0,self.UINT_MAX)
                if num%4 == 0:
                    num += randint(1,3)
            self.write(str(num)+"\n")
            self.read(delim="\n", expect="You didn't say the magic word.")
            return -1

    def add_good(self):
        #here we provide valid add commands, but the videos are not necessarily valid
        #these will cause failures

        #should re-enable this when we figure out how to add custom timeout to pov spec
        #if self.chance(0.99):
        l = randint(4,8192)
        #else:
            # leave room for checksum,MAX_VID_LEN-1 will be altered to MAX_VID_LEN-4
        #    l = randint(4,self.MAX_VID_LEN-1) 
        l -= l % 4
        buf = random_data(l, l).replace("\n","\x00")

        name = random_alpha(1,self.MAX_NAME_LEN)
        self.state['videos'][name] = {'buf':buf}
        
        if self.chance(0.5):
            csum = 0xffffffff & sum(unpack("<I",buf[i:i+4])[0]^0x42424242 for i in xrange(0,l,4))
            csum = pack("<I",csum)
            self.state['videos'][name]['badcsum'] = False
        else:
            csum = random_data(4, 4).replace("\n","\x00")
            self.state['videos'][name]['badcsum'] = True

        buf += csum

        self.write("add %s\n" % name)
        self.read(delim=": ", expect="Length")
        self.write(str(l+4)+"\n")
        self.read(delim="\n",expect="Your personal access key is: 0x42")
        self.write(buf)
        self.state['vidlist'].append(name)
            
    def play_bad(self):
        '''test invalidly formatted invalid play commands'''
        t = randint(0,9)
        cmd = "play "
        if self.chance(0.5) and len(self.state['videos']) != 0:
            #key argument missing or malformed
            n = choice(self.state['videos'].keys())
            if self.chance(0.5):
                cmd += n #no key provided
            else:
                c = choice([0]+range(2,10))
                # key not single byte
                cmd += n+" "+random_data(c, c).replace("\n","\x00")
            #key not provided
        else:
           #no such video
           cmd += random_alpha(1,127)
        self.write(cmd+"\n")
        self.read(delim="\n",expect="I hate this hacker crap!")

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
    def remove_bad(self):
        '''test invalid remove commands'''
        #once we add rick, we will have two cases here
        self.write("remove %s\n" % random_alpha(0,self.RECV_BUF_LEN-8))
        self.read(delim="\n",expect="I hate this hacker crap!")
        
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
        
    def badcmd(self):
        '''test random junk data'''
        self.write(random_data(0,self.RECV_BUF_LEN-1).replace("\n","")+"\n")
        self.read(delim="\n",expect="wat")

    def quit(self):
        self.write("quit\n")
        self.read(delim="\n",expect="God help us, we're in the hands of engineers...")
