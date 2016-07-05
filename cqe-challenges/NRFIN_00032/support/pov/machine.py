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
from random import choice,randint
from struct import *

sys.path.append(os.path.dirname(os.path.realpath(__file__)))

from pollinfo import *
from dupe import *

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))

def urand(size):
    return ''.join(chr(randint(0,255)) for _ in range(size)) 

#generating all the PoVs with the poll generator is tricky
#this is all kind of hacky, but should work well enough
vulnprotos = []
vulninfo = {}
for proto in pollinfo:
    vuln = [i for i in pollinfo[proto][1] if i.endswith("vuln")]
    if len(vuln) > 0:
        vulninfo[proto] = [pollinfo[proto],len(vuln)-1]
        if proto not in vulnprotos:
            vulnprotos.append(proto)

def makevuln(ctype=0):
    #we assume all protocols are reachable from a llama frame
    #as our generator should have ensured this
    global vulnprotos
    global vulninfo

    if len(vulnprotos) == 0:
        #this will raise an error, but after we've made all our PoVs :D
        return None

    curname = vulnprotos[0]
    vcur = vulninfo[curname]
    cur = pollinfo[curname]

    #need to make a llama header in a bit
    layers = [urand(20)+pack("<I",llama.index("process_"+curname))]
    names = ["llama"]
        
    #cur = pollinfo[curname]
    names.append(curname)
    nxt = -1
    layer = []
    datvuln = 0
    addedvuln = False
    for field in cur[1]:
        if field in typelen:
            layer.append(urand(typelen[field]))
        elif field == "nextproto_b":
            nxt = -1
            layer.append(pack("b",nxt))
        elif field == "nextproto_s":
            nxt = -1
            layer.append(pack("<h",nxt))
        elif field == "string":
            layer.append("A\x00")
        elif field == "string_vuln":
            if datvuln == vcur[1]:
                l = 128
                addedvuln = "yes - string"
            else:
                l = 1
            datvuln+=1
            layer.append("A"*l+"\x00")
        elif field == "lv":
            l = 1
            layer.append(pack("B",l))
            layer.append(urand(l))
        elif field == "slv":
            l = 1
            layer.append(pack("H",l))
            layer.append(urand(l))
        elif field == "slv_vuln":
            if datvuln == vcur[1]:
                addedvuln = "yes - slv"
                l = 9920
            else:
                l = 1
            datvuln+=1
            layer.append(pack("H",l))
            layer.append(urand(l))
        elif field == "lv_vuln":
            if datvuln == vcur[1]:
                l = 255
                addedvuln = "yes - lv"
            else:
                l = 1
            datvuln+=1
            layer.append(pack("B",l))
            layer.append(urand(l))
            
    layers.append("".join(layer))

    if 0 == vcur[1]:
        #povd all the vulns for this proto
        vulnprotos = vulnprotos[1:]
    print addedvuln 
    print curname
    vcur[1]-=1
    
    return DUPEpkt("".join(layers)),names

class CABLEGRINDER(Actions):
    def start(self):
        pass
    def valid(self):
        numpkts = randint(1,200)
        pkts,names = [],[]
        ctype = 0 
        pkt,name = makevuln(ctype=ctype)
        pkts.append(pkt)
        names.append(name)
        payload = str(DUPE(heap=0x10100110,pkts=pkts,ctype=ctype,flen=pkts[0].l))
        self.write(pack("<I",len(payload)))
        self.write(payload)

        #our match deems most of the actual dissection non-essential
        #checking layer names is sufficient to ensure desync hasn't occurred
        #and our for-testing release checks actual dissection of vuln layer
        self.read(delim="\n",expect="Starting dissection...")
        for cur in names:
            self.read(delim="====\n",expect=".*New Packet",expect_format='pcre')
            for name in cur:
                self.read(delim="===\n",expect=".*==="+name,expect_format='pcre')
            
        self.read(delim="===\n",expect=".*Dissection finished",expect_format='pcre')
