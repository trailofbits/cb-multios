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

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
from challenges import challenges

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
        #self.delay(100)
        #init prng
        self.last = None
        cookie = self._rand(4)
        self.files = {}
        self.verinfo = {
                0x10000000:[
                    (self._retrieve,0x41414141),
                    (self._submit,0x41414142),
                    (self._quit,0x41414146)],
                0x10000001:[
                    (self._retrieve,0x41414141),
                    (self._submit,0x41414142),
                    (self._check,0x41414143),
                    (self._delete,0x41414145),
                    (self._quit,0x41414146)],
                0x10000002:[
                    (self._retrieve,0x41414141),
                    (self._submit,0x41414142),
                    (self._check,0x41414143),
                    (self._auth,0x41414144),
                    (self._delete,0x41414145),
                    (self._quit,0x41414146)],
                0x10000003:[
                    (self._quit,0x41414146)],
        }

        self.reqpaths = []

    def _retrieve(self, ver, code):
        le = choice([True,False])
        hdr = lehdr if le else behdr
        fmt = "<4sIIIIII" if le else ">4sIIIIII"

        if (randint(1,5) == 5) or len(self.files) == 0:
            path = random_alpha(10,100)
            self.reqpaths.append((ERROR,path))
        else:
            path = choice(self.files.keys())
            self.reqpaths.append((INFO,path))


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

    def _submit(self, ver, code):
        le = choice([True,False])
        hdr = lehdr if le else behdr
        fmt = "<4sIIIIII" if le else ">4sIIIIII"

        path = random_alpha(10,100)
        while path in self.files:
            path = random_alpha(10,100)

        self.reqpaths.append((INFO,path))

        body = random_alpha(100,200)

        pkt = pack(fmt, hdr, ver, code, len(path), len(body), 0, 0) + path + body 

        fmt = "<4sII" if le else ">4sII"
        self.files[path] = body
        code = 0xbaaaaaaa;
        body = SUBMITOK 

        return (pkt, pack(fmt, hdr, code, len(body)) + body)

    def _check(self, ver, code):
        le = choice([True,False])
        hdr = lehdr if le else behdr
        fmt = "<4sIIIIII" if le else ">4sIIIIII"

        if (randint(1,5) == 5) or len(self.files) == 0:
            path = random_alpha(10,100)
            self.reqpaths.append((ERROR,path))
        else:
            path = choice(self.files.keys())
            self.reqpaths.append((INFO,path))

        body = "" 

        pkt = pack(fmt, hdr, ver, code, len(path), len(body), 0, 0) + path + body 

        fmt = "<4sII" if le else ">4sII"
        if path in self.files:
            body = pack("<I", len(self.files[path]))
            code = 0xbaaaaaaa;
        else:
            body = INTERNALERR
            code = 0xbaaaaaab;

        return (pkt, pack(fmt, hdr, code, len(body)) + body)

    def _auth(self, ver, code):
        le = choice([True,False])
        hdr = lehdr if le else behdr
        fmt = "<4sIIIIII" if le else ">4sIIIIII"

        if (randint(1,5) == 5) or len(self.files) == 0:
            path = random_alpha(10,100)
            self.reqpaths.append((ERROR,path))
        else:
            path = choice(self.files.keys())
            self.reqpaths.append((INFO,path))


        body = "" 

        pkt = pack(fmt, hdr, ver, code, len(path), len(body), 0, 0) + path + body 

        fmt = "<4sII" if le else ">4sII"

        challenge = challenges[self._randint() % len(challenges)]
        key = 0xff & (self._randint() ^ self._randint())
        token = self._randint()

        encoded = "".join(chr(ord(i)^key) for i in challenge)
        etoken = "".join(chr(ord(i)^key) for i in pack("<I",token))
        
        #hack to stick with previous conventions
        self.write(pkt)
        self.read(length=5, expect=pack("<BI",key,len(challenge)))
        #prevent OOM problems due to unstated size limits because of caching in /tmp/
        self.read(length=20, expect=encoded[:20])
        self.read(length=len(challenge)-20, expect=".*", expect_format="pcre")
        self.read(length=4, expect=etoken)

        if path in self.files:
            body = self.files[path]
            code = 0xbaaaaaaa;
            key = 0xff & self._randint()
            body = "".join(chr(ord(i)^key) for i in body)
        else:
            body = INTERNALERR
            code = 0xbaaaaaab;

        return (challenge+pack("<I",token^0x127a1b76), pack(fmt, hdr, code, len(body)) + body)

    def _delete(self, ver, code):
        le = choice([True,False])
        hdr = lehdr if le else behdr
        fmt = "<4sIIIIII" if le else ">4sIIIIII"

        if (randint(1,5) == 5) or len(self.files) == 0:
            path = random_alpha(10,100)
            self.reqpaths.append((ERROR,path))
        else:
            path = choice(self.files.keys())
            self.reqpaths.append((INFO,path))

        body = "" 

        pkt = pack(fmt, hdr, ver, code, len(path), len(body), 0, 0) + path + body 

        fmt = "<4sII" if le else ">4sII"
        if path in self.files:
            body = DELETEOK
            code = 0xbaaaaaaa;
            del self.files[path]
        else:
            body = INTERNALERR
            code = 0xbaaaaaab;

        return (pkt, pack(fmt, hdr, code, len(body)) + body)

    def _quit(self, ver, code):
        le = choice([True,False])
        hdr = lehdr if le else behdr
        fmt = "<4sIIIIII" if le else ">4sIIIIII"

        path = ""

        body = "" 

        pkt = pack(fmt, hdr, ver, code, len(path), len(body), 0, 0) + path + body 

        resp = "done"

        return (pkt, resp)


    def _notimplemented(self, ver, code):
        le = choice([True,False])
        hdr = lehdr if le else behdr
        fmt = "<4sIIIIII" if le else ">4sIIIIII"

        path = random_alpha(10,100)
        body = random_alpha(10,1000)

        self.reqpaths.append((ERROR,path))

        pkt = pack(fmt, hdr, ver, code, len(path), len(body), 0, 0) + path + body 

        fmt = "<4sII" if le else ">4sII"
        body = NOTIMPLEMENTED;
        code = 0xbaaaaaad;

        return (pkt, pack(fmt, hdr, code, len(body)) + body)


    def do_auth(self):
        code = 0x41414141
        ver = 0x10000000
        le = choice([True,False])
        hdr = lehdr if le else behdr
        fmt = "<4sIIIIII" if le else ">4sIIIIII"

        path = random_alpha(10,100)
        self.reqpaths.append((ERROR,path))
        body = "" 

        pkt = pack(fmt, hdr, ver, code, len(path), len(body), 0, 0) 

        fmt = "<4sII" if le else ">4sII"
        respbody = INTERNALERR
        respcode = 0xbaaaaaab;

        challenge = challenges[self._randint() % len(challenges)]
        key = 0xff & (self._randint() ^ self._randint())
        token = self._randint()

        encoded = "".join(chr(ord(i)^key) for i in challenge)
        etoken = "".join(chr(ord(i)^key) for i in pack("<I",token))
        
        self.write(pkt)

        #prevent OOM problems due to unstated size limits because of caching in /tmp/
        self.read(length=20+5, expect=pack("<BI",key,len(challenge))+encoded[:20])
        self.read(length=len(challenge)-20, expect=".*", expect_format="pcre")
        self.read(length=len(etoken), expect=etoken)

        self.write(challenge+pack("<I",token^0x127a1b76)+path+body)

        resp = pack(fmt, hdr, respcode, len(respbody)) + respbody
        self.read(length=len(resp), expect=resp)

    def send_requests(self):
        self.do_auth()
        #sync prng
        heapcookie = self._rand(4)
        
        for _ in range(randint(0,10)):
            ver = choice(self.verinfo.keys())
            rtype = choice(self.verinfo[ver])
            if rtype[0] == self._quit:
                rtype = (self._notimplemented, randint(0x41414147,0xffffffff))
            req,resp = rtype[0](ver, rtype[1])
            self.write(req)
            self.read(length=len(resp), expect=resp)
        
        ver = choice(self.verinfo.keys())
        req, resp = self._quit(ver, 0x41414146)
        self.write(req)
        self.read(length=len(resp), expect=resp)

        for level,path in self.reqpaths:
            self.read(length=4+len(path), expect=pack("<I",level)+path)

    def quit(self):
        pass

    def _uint32(self, i):
        i = (i % 1024) * 4
        return unpack("<I",self.magic_page[i:i+4])[0]

    def _randint(self):
        if self.last == None:
            self.last = self._uint32(0) 
        self.last ^= self._uint32(self._uint32(self.last)) ^ self._uint32(0xffffffff & (self.last * self._uint32(self.last)))
        return self.last

    def _rand(self, count):
        return "".join(chr(self._randint()&0xff) for i in range(0,count))
