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
from os.path import dirname, abspath, join
from commands import getoutput
from re import escape
from collections import OrderedDict

cb = join(dirname(dirname(abspath(__file__))), "build/release/bin/NRFIN_00071")

req = {
    "MKDIR":0,
    "LIST":1,
    "PUT":2,
    "GET":3,
    "RM":4,
    "RMDIR":5,
    "QUIT":6,
}

resp = {
    "MKDIR_OK":0,
    "MKDIR_FAIL":1,
    "LIST_OK":2,
    "LIST_FAIL":3,
    "PUT_OK":4,
    "PUT_FAIL":5,
    "GET_OK":6,
    "GET_FAIL":7,
    "RM_OK":8,
    "RM_FAIL":9,
    "RMDIR_OK":10,
    "RMDIR_FAIL":11,
    "QUIT_OK":12
}

README = "This is a sample file! Feel free to add your own!"

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

x,y,z,w = 0,0,0,0 

def getshifty():
    global x, y, z, w
    tmp = x ^ ((x<<12)&0xffffffff)
    x = y
    y = z
    z = w
    w = w ^ (w>>18) ^ tmp ^ (tmp >> 9)
    return w

def xor(x,y):
    return x^y

def chunks(l, n):
    for i in xrange(0, len(l), n):
        yield l[i:i+n]

class SBTP(Actions):
    def start(self):
        #init prng
        global x, y, z, w
        x = xor(*unpack("<II",self.magic_page[:8]))
        y = xor(*unpack("<II",self.magic_page[8:16]))
        z = xor(*unpack("<II",self.magic_page[16:24]))
        w = xor(*unpack("<II",self.magic_page[24:32]))
        
        #set up our config
        self.version = randint(0xc0ff33,0xffffffff)
        self.min_ver = randint(0,0xc0ff32)

        #we make a point to always "encrypt"
        #and see if competitors discover/choose to use plaintext
        self.encrypt = 0
        self.allow_reconnect = 1
        self.buf_size = 0
        self.files = OrderedDict([("#README",README)]) 
        self.subdir = None

    def verify(self):
        readcgcef = getoutput("readcgcef -a %s" % cb)
        for line in readcgcef.split("\n"):
            parts = line.split()
            if len(parts) != 7:
                continue
            if parts[6] == "go":
                start = int(parts[1],16)-0x8048000
            if parts[6] == "longjmp":
                end = int(parts[1],16)-0x8048000

        csum = getshifty();
        magic =  0x1337b33f;
        cbdata = open(cb,"r").read()
        for i in range(start,end,4):
            csum ^= unpack("<I",cbdata[i:i+4])[0]

        magic = pack(">I",magic).encode("hex").upper()
        csum = pack(">I",csum).encode("hex").upper()

        #leaving debug magic in on the off chance anyone manages to brute force it
        self.read(length=8, expect="("+magic+"|"+csum+")", expect_format="pcre")
        self.write(pack("<I",1))

    def read_seed(self):
        global x, y, z, w

        if self.encrypt:
            x = xor(*unpack("<II",self.magic_page[32:40]))
            y = xor(*unpack("<II",self.magic_page[40:48]))
            z = xor(*unpack("<II",self.magic_page[48:56]))
            w = xor(*unpack("<II",self.magic_page[56:64]))
        else:
            x,y,z,w = 0,0,0,0

        self.read(length=16, expect=pack("<IIII",x,y,z,w))

    def send_conf(self):
        self.write(pack("<IIIII",self.version, self.min_ver, self.encrypt, self.allow_reconnect, self.buf_size))
        self.read(length=4, expect=pack("<I",1))

    def doreconn(self):
        self.delay(3000)
        self.write(pack("<IIIII",self.version, self.min_ver, self.encrypt, self.allow_reconnect, 0xfffffc1c))
        self.write(pack("<I",1028))
        self.doread(pack("<I1024s", resp['GET_OK'], README))
          

    def _enc(self,s):
        if (len(s) % 4) != 0:
            raise Exception("Must be 4 byte aligned.")

        res = []
        for dword in chunks(s,4):
            tmp = getshifty()
            res.append(pack("<I",tmp^unpack("<I",dword)[0]))

        return "".join(res)

    def dowrite(self,s):
        if (self.encrypt):
            s = self._enc(s)
        self.write(s)

    def doread(self,s):
        if (self.encrypt):
            s = self._enc(s)
        self.read(length=len(s), expect=s)

    def get_file(self, fn, data):
        self.dowrite(pack("<I1024s", req['GET'], fn))
        self.doread(pack("<I1024s", resp['GET_OK'], data))

    def get_file_fail(self,fn):
        self.dowrite(pack("<I1024s", req['GET'], fn))
        self.doread(pack("<I1024s", resp['GET_FAIL'], ""))

    def get_readme(self):
        self.get_file("#README", README)

    def put_file(self, fn, data):
        self.dowrite(pack("<I1024s", req['PUT'],fn+'\x00'+data))
        self.doread(pack("<I1024s", resp['PUT_OK'], ''))
        self.files[fn] = data

    def add_rootfile(self):
        for i in range(randint(0,5)):
            fn = "#"+random_alpha(1,20)
            if fn not in self.files:
                data = random_alpha(1,900)
                self.put_file(fn, data)

    def ls_dir(self, path, files=[]):
        files = [f.split("#")[-1] for f in files]
        self.dowrite(pack("<I1024s", req['LIST'],path+'\x00'))
        self.doread(pack("<I1024s", resp['LIST_OK'],":".join(files)))

    def list_root(self):
        self.ls_dir("#", [fn for fn in self.files if fn.count("#") == 1])

    def list_subdir(self):
        if not self.subdir:
            self.add_subdir()
        self.ls_dir(self.subdir, [fn for fn in self.files if fn.startswith(self.subdir+"#")])

    def add_subdir(self):
        if self.subdir:
            self.rm_subdir()
        self.subdir = "#"+random_alpha(1,20)
        self.dowrite(pack("<I1024s", req['MKDIR'], self.subdir))
        self.doread(pack("<I1024s", resp['MKDIR_OK'], ''))

    def add_subfile(self):
        if not self.subdir:
            self.add_subdir()
        for i in range(randint(0,5)):
            fn = self.subdir+"#"+random_alpha(1,20)
            if fn not in self.files:
                data = random_alpha(1,900)
                self.put_file(fn, data)

    def get_all_files(self):
        for fn,data in self.files.items():
            self.get_file(fn,data)

    def rm(self, path):
        self.dowrite(pack("<I1024s", req['RM'], path))
        self.doread(pack("<I1024s", resp['RM_OK'], ''))
        #confirm deletion
        self.get_file_fail(path)
        del(self.files[path])

    def rm_dir(self, path):
        self.dowrite(pack("<I1024s", req['RMDIR'], path))
        self.doread(pack("<I1024s", resp['RMDIR_OK'], ''))
        deleted = [fn for fn in self.files if fn.startswith(path+"#")]
        #confirm deletion
        for fn in deleted:
            self.get_file_fail(fn)
            del(self.files[fn])

    def rm_all_files(self):
        for fn in self.files:
            self.rm(fn)
        self.files = OrderedDict()

    def rm_subdir_file(self):
        if not self.subdir:
            self.add_subdir()
        sfiles = [fn for fn in self.files if fn.startswith(self.subdir+"#")]
        if len(sfiles) != 0:
            self.rm(choice(sfiles))

    def rm_subdir(self):
        if not self.subdir:
            self.add_subdir()
        self.rm_dir(self.subdir)
        self.subdir = None

    def quit(self):
        self.dowrite(pack("<I1024s", req['QUIT'],""))
