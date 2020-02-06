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
from random import choice, randint, shuffle
from struct import pack,unpack
from math import ceil
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

def chunks(l, n):
    for i in xrange(0, len(l), n):
        yield l[i:i+n]


class TFTTP(Actions):
    #define ALL the things
    NOTFOUND = "Not found."
    RESPLEN = 256
    NOTFOUND += ("\x00"*(RESPLEN-len(NOTFOUND))) 
    UPLOADFIN = "Information upload complete."
    UPLOADFIN += ("\x00"*(RESPLEN-len(UPLOADFIN))) 
    ERRQUIT = "Mkay"
    ERRQUIT += ("\x00"*(RESPLEN-len(ERRQUIT)))
    pkttypes = {"PUT":0,"GET":1,"RAND":2,"RESP":3,"FRAG":4}
    MAX_ENTRIES = 2048
    MAX_KEYSZ = 128
    MAX_VALSZ = 256
    MAX_FRAG = 256
    MAX_DATA_LEN = 256+128
    MAX_FRAG_DATA_LEN = MAX_DATA_LEN-8
    MAX_PKT_SIZE = MAX_FRAG_DATA_LEN * MAX_FRAG

    def start(self):
        if 'quotes' not in self.state:
            self.state['quotes'] = {} #key-val pairs of keys and quotes
        return

    def initial(self):
        #empty state, just used for dealing with "stateless" protocol
        return

    def _expect_fail(self):
        resp = self._construct_pkt(self.pkttypes['RESP'],self.ERRQUIT)
        self.read(length=len(resp), expect=resp)

    def _construct_pkt(self, code, data):
        return pack("<II",len(data),code)+data

    def _fragment_pkt(self, code, data):
        frag = []
        for i, chunk in enumerate(chunks(data,self.MAX_FRAG_DATA_LEN)):
            frag.append(pack("<BBHI",i,
                        int(ceil(len(data)/float(self.MAX_FRAG_DATA_LEN)))-1,
                            0,code)+chunk)
        if len(frag[-1]) != self.MAX_DATA_LEN:
            frag[-1] += "\x00"*(self.MAX_DATA_LEN-len(frag[-1]))
        return [self._construct_pkt(self.pkttypes['FRAG'],i) for i in frag]

    def _build_put_good(self):
        key,val = random_string(1,self.MAX_KEYSZ-1), random_string(1,self.MAX_VALSZ-1)
        while key in self.state['quotes']:
            key = random_string(1,self.MAX_KEYSZ)
        data = key+"\x00"+val+"\x00"
        return key,val,data

    def _build_get_good(self):
        if len(self.state['quotes']) == 0:
            self.put_good()
        key = choice(self.state['quotes'].keys())
        val = self.state['quotes'][key]
        return key,val


    def put_good(self):
        key,val,data = self._build_put_good()
        self.write(self._construct_pkt(self.pkttypes['PUT'], data))
        if len(self.state['quotes']) >= self.MAX_ENTRIES:
            #should terminate
            return -1
        self.state['quotes'][key] = val
        resp = self._construct_pkt(self.pkttypes['RESP'],self.UPLOADFIN)
        self.read(length=len(resp),expect=resp);

    def put_bad(self):
        #two error conditions we can hit with a valid packet (but invalid put)
        if self.chance(0.5):
            #too long of a key
            key = random_string(self.MAX_KEYSZ,self.MAX_DATA_LEN-2)+"\x00"
            #value shouldn't matter
            val = random_data(0,self.MAX_DATA_LEN-len(key))
        else:
            #too long of a value
            val = random_string(self.MAX_VALSZ,self.MAX_DATA_LEN-2)+"\x00"
            #key can't contain nulls, or we might not have a big enough val
            key = random_data(0,self.MAX_DATA_LEN-len(val)).replace("\x00","A")
        self.write(self._construct_pkt(self.pkttypes['PUT'], key+val))
        self._expect_fail()
        return -1

    def frag_good(self):
        #TODO add checks for out-of-order/retransmitted but valid packets
        if self.chance(0.5):
            key,val,data = self._build_put_good()
            data += random_string((self.MAX_FRAG_DATA_LEN*2)-len(data),
                                    self.MAX_PKT_SIZE-len(data))
            for pkt in self._fragment_pkt(self.pkttypes['PUT'],data):
                self.write(pkt)
            if len(self.state['quotes']) >= self.MAX_ENTRIES:
                #should terminate
                return -1
            self.state['quotes'][key] = val
            resp = self._construct_pkt(self.pkttypes['RESP'],self.UPLOADFIN)
            self.read(length=len(resp),expect=resp);
        else:
            key,val = self._build_get_good()
            key += "\x00"+random_string((self.MAX_FRAG_DATA_LEN*2)-len(key)-1,
                                    self.MAX_PKT_SIZE-len(key)-1)
            for pkt in self._fragment_pkt(self.pkttypes['GET'],key):
                self.write(pkt)
            padded = val+("\x00"*(256-len(val)))
            resp = self._construct_pkt(self.pkttypes['RESP'],padded)
            self.read(length=len(resp),expect=resp)

    def frag_bad(self):
        #we only test put here for simplicity
        key,val,data = self._build_put_good()
        data += random_string((self.MAX_FRAG_DATA_LEN*2)-len(data),
                                self.MAX_PKT_SIZE-len(data))
        pkts = self._fragment_pkt(self.pkttypes['PUT'],data)

        #many cases where this can fail, we try to check them all
        outoforder = random.choice([True,False])
        badcode = random.choice([True,False])
        badhdrsize = random.choice([True,False])
        badtfrag = random.choice([True,False]) 

        #ensure at least something is wrong
        if not (outoforder or badcode or badhdrsize or badtfrag):
            badhdrsize = True
        
        if badtfrag and len(pkts) > 1:
            pktid = randint(1,len(pkts)-1)
            pkt = list(pkts[pktid])
            new = randint(0,255)
            while new == len(pkts):
                new = randint(0,255)
            pkt[9] = chr(new)
            pkts[pktid] = "".join(pkt)
            pkts = pkts[:pktid+1]


        if outoforder:
            #this is more complicated than a simple shuffle since we
            #need to cut the list at the spot of out of order packets
            toswap = randint(0,len(pkts)-1)
            toswap2 = randint(0,len(pkts)-1)
            while toswap == toswap2:
                toswap2 = randint(0,len(pkts)-1)
            pkts[toswap2],pkts[toswap] = pkts[toswap],pkts[toswap2]
            if toswap<toswap2:
                pkts = pkts[:toswap+1]
            else:
                pkts = pkts[:toswap2+1]
            
        if badcode and len(pkts) > 1:
            pktid = randint(1,len(pkts)-1)
            pkt = pkts[pktid]
            pkts[pktid] = pkt[:4]+pack("<I",randint(0,3))+pkt[8:]
            pkts = pkts[:pktid+1]

        if badhdrsize:
            pktid = randint(0,len(pkts)-1)
            pkt = pkts[pktid]
            data = random_data(1,self.MAX_FRAG_DATA_LEN-1)
            data = pack("<BBHI",pktid,
                        int(ceil(len(data)/float(self.MAX_FRAG_DATA_LEN)))-1,
                            0,self.pkttypes['PUT'])+data
            pkts[pktid] = self._construct_pkt(self.pkttypes['FRAG'],data)
            pkts = pkts[:pktid+1]

        for pkt in pkts:
            self.write(pkt)

        self._expect_fail()
        return -1

    def get_good(self):
        key,val = self._build_get_good()
        req = self._construct_pkt(self.pkttypes['GET'],key)
        self.write(req)
        padded = val+("\x00"*(256-len(val)))
        resp = self._construct_pkt(self.pkttypes['RESP'],padded)
        self.read(length=len(resp),expect=resp)

    def get_bad(self):
        #only get error condition is NOTFOUND
        
        #chances of collision are negligible
        req = self._construct_pkt(self.pkttypes['GET'], 
                random_data(8,self.MAX_DATA_LEN-1).replace("\x00","A")+"\x00")
        self.write(req)
        resp = self._construct_pkt(self.pkttypes['RESP'],self.NOTFOUND)
        self.read(length=len(resp), expect=resp)
        return -1
        

    def rand_good(self):
        if len(self.state['quotes']) == 0:
            self.put_good()
        req = self._construct_pkt(self.pkttypes['RAND'],'8\x00')
        self.write(req)
        self.read(length=8,expect=escape(pack("<II",256,self.pkttypes['RESP'])))
        self.read(length=256, expect_format="pcre", expect=".*")

    def rand_bad(self):
        #only non-crashing way for this to fail is if numbytes > 8
        req = self._construct_pkt(self.pkttypes['RAND'],str(randint(8,2**32-1))+"\x00")
        self.write(req)
        self._expect_fail()
        return -1

    def invalid(self):
        #invalid length or invalid packet code
        if self.chance(0.5):
            req = self._construct_pkt(choice(self.pkttypes.values()),
                    random_data(0,10000)) #arbitrary max len
            req = pack("<I",randint(self.MAX_PKT_SIZE,2**32-1))+req[4:]
        else:
            req = self._construct_pkt(randint(max(self.pkttypes.values())+1,255),
                    random_data(0,self.MAX_PKT_SIZE)) #arbitrary max len
        self.write(req)
        self._expect_fail()
        return -1

