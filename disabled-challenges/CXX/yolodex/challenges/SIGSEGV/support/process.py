#!/usr/bin/env python
#
# Copyright (C) 2014 
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


import sys
import os

from struct import pack

def escape(data):
    '''Escape all the things, for C'''
    return "".join("\\x%02x"%ord(i) for i in data)

def rc4ish(data):
    '''A python implementation of our lovable psuedo-hashing algorithm'''

    s = [i for i in reversed(range(256))]
    j = 0
    out = ["\x00"]*16
    key = data

    for i in range(256):
        j = (j + s[i] + ord(key[i%len(key)])) % 256
        s[i],s[j] = s[j],s[i]
    
    i = j = 0
    for c in data:
        i = (i+1) % 256
        j = (j+s[i]) % 256
        s[i],s[j] = s[j],s[i]
        out[i%16] = chr(ord(out[i%16]) ^ ord(c) ^ s[(s[i]+s[j]) % 256])

    return "".join(out)

def genfiles(d,header="trusted.h",lib="payloads.py"):
    try:
        bins = [os.path.join(d,i) for i in os.listdir(d) if i.endswith(".bin")]
    except:
        sys.exit("Directory listing failed.")

    hashes = []
    payloads = []

    try:
        for b in bins:
            with open(b,'rb') as f:
                #maximum size of 4096, always pad out
                sc = pack("4096s",f.read(4096))
                hashes.append(rc4ish(sc))
                payloads.append(sc)
    except:
        sys.exit("Failed to parse input files.")

    hashes.append(hashes[-1])
    hashes[-1] = hashes[-1][:1]+"\x00"+hashes[-1][2:] #insert our nasty null

    with open(header,"wb") as h, open(header+".tmpl","rb") as t:
        tmpl = t.read()
        h.write(tmpl % (len(hashes),",\n".join('"'+escape(i)+'"' for i in hashes)))

        
    with open(lib,"wb") as l, open(lib+".tmpl","rb") as t:
        tmpl = t.read()
        l.write(tmpl % (str(payloads),str(hashes)))

def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: %s bin_dir" % sys.argv[0])
    
    genfiles(sys.argv[1])




        

if __name__=="__main__":
    main()
