#!/usr/bin/env python
#
# Copyright (C) 2014, 2015
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

# NOTE 1: The .data segment address is not consistent across executions.
# Therefore, if we wish to poll the .data segment, we must leak the base 
# address during the poll.  We don't do this for several reasons:
# 1) A legitimate defensive strategy might be to XOR encrypt or otherwise mask 
#   pointers to as to mitigate certain exploit strategies.
# 2) Leaking a pointer to .data and computing the base address of .data from 
#   that pointer is not feasible in machine.py because you cannot compute over 
#   Variables.

from generator.actions import Actions, Variable
from random import randint, choice, randrange
from copy import deepcopy
import struct, os

GLOBAL_DEBUG = False

# "#defines"
SZ_PAGE = 0x1000
SZ_WORD = 4
UINT_MAX = 0xFFFFFFFF
SZ_PKT = 28

# Size of query regions
SZ_STATIC = 0x10000
# We do 1000 polls, but the SCRATCH size is 0x1000 bytes.  We reduce the used 
# SCRATCH space to increase likelihood that we R back something we've W before.
SZ_SCRATCH = 0x10

# These don't vary
TEXT_BGN = 0x08048000
#TEXT_END = 0x0804e000 # w/o STATIC
TEXT_END = 0x08146000 # w/ STATIC
STCK_BGN = 0xbaa8b000
STCK_END = 0xbaaab000
HEAP_BGN = 0xb7fff000
HEAP_END = HEAP_BGN + SZ_SCRATCH
FLAG_BGN = 0x4347C000
FLAG_END = FLAG_BGN + SZ_PAGE

# Segments
G_TEXT = 0
#G_DATA = 1 # We don't touch the .data segment.  See NOTE 1 at the top.
G_STCK = 1
G_LAST = G_STCK

# status
S_REQ = 0
S_RESP = 1
S_ERROR = 2
S_EXIT = 3
S_LAST = S_EXIT
# access type
X_NORMAL = 0
X_SCRATCH = 1
X_STATIC = 2
X_PREV = 3
X_LAST = X_PREV
# action
A_READ = 0
A_WRITE = 1
A_LAST = A_WRITE
 # operand2 type
OP2_IMM = 0
OP2_MEM = 1
OP2_LAST = OP2_MEM


class Packet:
    def __init__(self, status, seq, access_type=0xFF, action=0xFF, op2type=0xFF, dst=0, src=0):
        self.status = status
        self.seq = seq
        self.access_type = access_type
        self.action = action
        self.op2type = op2type
        self.dst = dst
        self.src = src

    def __str__(self):
        return "Packet | status = %d, seq = 0x%08x, access_type = %d, action = %d, op2type = %d, dst = 0x%08x, src = 0x%08x" % \
            (self.status, self.seq, self.access_type, self.action, self.op2type, self.dst, self.src)

    def to_bin(self):
        if GLOBAL_DEBUG: print self
        return struct.pack("<LLLLLLL", 
            self.status, self.seq, self.access_type, self.action, self.op2type, self.dst, self.src)


def b2uint32le(bytes):
    return (ord(bytes[0]) << 0 | 
            ord(bytes[1]) << 8 |
            ord(bytes[2]) << 16 |
            ord(bytes[3]) << 24)

def uint32le2b(uint32):
    return [chr(uint32 >> 0 & 0xFF), 
            chr(uint32 >> 8 & 0xFF),
            chr(uint32 >> 16 & 0xFF),
            chr(uint32 >> 24 & 0xFF)]


class CAT(Actions):

    def do_normal(self):
        """
        Send a NORMAL query type.

        We use this to verify certain aspects of the .text section...
        """
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "do_normal()"
        self.state['seq'] = self.state['seq'] + 1 % 0xFFFFFFFF
        self.state['exit_allowed'] = True

        # We do not utilize NORMAL + WRITE because:
        # - WRITES can only occur to .text and .data
        # - a WRITE to .text will always SIGSEGV, which we don't want
        # - a WRITE to .data might clobber something important, sometimes 
        #   resulting in SIGSEGV
        action = A_READ
        op2type = randint(0, OP2_LAST)
        
        # READs never result in a memory write, so dst can be whatever.
        dst = randint(0, UINT_MAX)

        if OP2_IMM == op2type:
            # A READ with OP2_IMM will simply reflect the src.
            src = randint(0, UINT_MAX)
            pkt = Packet(S_REQ, self.state['seq'], X_NORMAL, action, op2type, 0, src)
            self.write(pkt.to_bin())
            self.read(length=SZ_PKT, expect=struct.pack("<LLLLLLL", 
                S_RESP, self.state['seq'], 0, 0, 0, src, 0))
        
        else: # OP2_MEM
            # A READ with OP2_MEM will result in 4B from the chosen address.
            # The CB allows us to READ from anywhere but the flag page, but to
            # avoid SIGSEGV, we're effectively limited to: .text, .data, stack.
            # We avoid .data; see NOTE 1 at the top.
            # The heap is safe too, but we read from that via SCRATCH.
            section = randint(0, G_LAST)

            if G_TEXT == section:
                # We don't want to be *too* mean, so we poll .text and make 
                # sure it's there, but we don't actually check contents.  This 
                # forces CRSs that employ ASLR to at least keep *something* at 
                # the original .text location.  Ideally, this prevents an ASLR 
                # strategy and am adversary takes advantage of the lack of ASLR.
                src = randrange(TEXT_BGN, TEXT_END, SZ_WORD)
                dst = randint(0, UINT_MAX)
                pkt = Packet(S_REQ, self.state['seq'], X_NORMAL, action, op2type, dst, src)
                self.write(pkt.to_bin())
                # We expect a valid response, but aren't going to try to 
                # predict what the bytes are, so we avoid matching on the dst.
                self.read(length=SZ_PKT-8, expect=struct.pack("<LLLLL", 
                    S_RESP, self.state['seq'], 0, 0, 0))
                self.read(length=4)
                self.read(length=4, expect=struct.pack("<L", 0))

            # The address of the stack is hardcoded in CGC kernel.
            else: # G_STCK == section
                dst = randint(0, UINT_MAX)
                src = randrange(STCK_BGN, STCK_END, SZ_WORD)
                pkt = Packet(S_REQ, self.state['seq'], X_NORMAL, action, op2type, dst, src)
                self.write(pkt.to_bin())
                # We expect a valid response, but aren't going to try to 
                # predict what the bytes are, so we avoid matching on the dst.
                self.read(length=SZ_PKT-8, expect=struct.pack("<LLLLL", 
                    S_RESP, self.state['seq'], 0, 0, 0))
                self.read(length=4)
                self.read(length=4, expect=struct.pack("<L", 0))
                

    def do_scratch(self):
        """
        Send a SCRATCH query type.
        """
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "do_scratch()"
        self.state['seq'] = self.state['seq'] + 1 % 0xFFFFFFFF
        self.state['exit_allowed'] = True

        action = randint(0, A_LAST)
        op2type = randint(0, OP2_LAST)

        # 4 main possibilies, based on READ/WRITE and IMM/MEM

        if action == A_READ and op2type == OP2_IMM:
            # We're bouncing an immediate back to ourselves.
            if DEBUG: print "SCRATCH, A_READ, OP2_IMM"
            src = randint(0, UINT_MAX)
            dst = src
            pkt = Packet(S_REQ, self.state['seq'], X_SCRATCH, action, op2type, 0, src)
            self.write(pkt.to_bin())
            self.read(length=SZ_PKT, expect=struct.pack("<LLLLLLL", 
                S_RESP, self.state['seq'], 0, 0, 0, dst, 0))

        elif action == A_READ and op2type == OP2_MEM:
            # We're querying a memory location.
            if DEBUG: print "SCRATCH, A_READ, OP2_MEM"
            rel_src = randrange(0, SZ_SCRATCH, SZ_WORD)
            abs_src = abs_src = rel_src+HEAP_BGN
            dst = b2uint32le(self.state['scratch'][rel_src:rel_src+SZ_WORD])
            pkt = Packet(S_REQ, self.state['seq'], X_SCRATCH, action, op2type, 0, abs_src)
            self.write(pkt.to_bin())
            self.read(length=SZ_PKT, expect=struct.pack("<LLLLLLL", 
                S_RESP, self.state['seq'], 0, 0, 0, dst, 0))

        elif action == A_WRITE and op2type == OP2_IMM:
            # We're writing an immediate value into memory.
            if DEBUG: print "SCRATCH, A_WRITE, OP2_IMM"
            src = randint(0, UINT_MAX)
            rel_dst = randrange(0, SZ_SCRATCH, SZ_WORD)
            abs_dst = rel_dst+HEAP_BGN
            pkt = Packet(S_REQ, self.state['seq'], X_SCRATCH, action, op2type, abs_dst, src)
            self.write(pkt.to_bin())
            i = 0
            for byte in uint32le2b(src):
                self.state['scratch'][rel_dst+i] = byte
                i += 1
            self.read(length=SZ_PKT, expect=struct.pack("<LLLLLLL", 
                S_RESP, self.state['seq'], 0, 0, 0, 0, 0))

        elif action == A_WRITE and op2type == OP2_MEM:
            # We're copying SZ_WORD bytes around.
            if DEBUG: print "SCRATCH, A_WRITE, OP2_MEM"
            rel_src = randrange(0, SZ_SCRATCH, SZ_WORD)
            abs_src = rel_src+HEAP_BGN
            rel_dst = randrange(0, SZ_SCRATCH, SZ_WORD)
            abs_dst = rel_dst+HEAP_BGN
            pkt = Packet(S_REQ, self.state['seq'], X_SCRATCH, action, op2type, abs_dst, abs_src)
            self.write(pkt.to_bin())
            for i in range(SZ_WORD):
                self.state['scratch'][rel_dst+i] = self.state['scratch'][rel_src+i]
            self.read(length=SZ_PKT, expect=struct.pack("<LLLLLLL", 
                S_RESP, self.state['seq'], 0, 0, 0, 0, 0))

        else:
            print "ERROR - THIS SHOULD NEVER HAPPEN"
            return -1


    def do_static(self):
        """
        Send a STATIC query type.
        """
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "do_static()" 
        self.state['seq'] = self.state['seq'] + 1 % 0xFFFFFFFF
        self.state['exit_allowed'] = True

        action = A_READ # Only READs are allowed to STATIC region(s).
        op2type = randint(0, OP2_LAST) # OP2 type is ignored.
        src = randrange(0, SZ_STATIC, 4)
        dst = randint(0, UINT_MAX)
        pkt = Packet(S_REQ, self.state['seq'], X_STATIC, action, op2type, dst, src)
        self.write(pkt.to_bin())
        dst = b2uint32le(self.state['static_switch'][src:src+SZ_WORD])
        self.read(length=SZ_PKT, expect=struct.pack("<LLLLLLL", 
                S_RESP, self.state['seq'], 0, 0, 0, dst, 0))


    def error(self):
        """
        Trigger various expected S_ERROR responses.
        """
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "error()"
        self.state['seq'] = self.state['seq'] + 1 % 0xFFFFFFFF
        self.state['exit_allowed'] = True

        NUM_ERRORS = 5
        error = randint(0, NUM_ERRORS)
        if 0 == error:
            # Test S_RESP, S_ERROR
            if DEBUG: print "testing S_RESP / S_ERROR"
            status = randint(S_RESP, S_ERROR)
            access_type = randint(0, X_LAST)
            action = randint(0, A_LAST)
            op2type = randint(0, OP2_LAST)
            dst = randint(0, UINT_MAX)
            src = randint(0, UINT_MAX)
            pkt = Packet(status, self.state['seq'], access_type, action, op2type, dst, src)
            self.write(pkt.to_bin())
            self.read(length=SZ_PKT, expect=struct.pack("<LLLLLLL", 
                S_ERROR, self.state['seq'], 0, 0, 0, 0, 0))
        elif 1 == error:
            # Attempt NORMAL R of FLAG page
            if DEBUG: print "testing NORMAL + READ + OP2_MEM + FLAG"
            dst = randint(0, UINT_MAX)
            src = randint(FLAG_BGN, FLAG_END)
            pkt = Packet(S_REQ, self.state['seq'], X_NORMAL, A_READ, OP2_MEM, dst, src)
            self.write(pkt.to_bin())
            self.read(length=SZ_PKT, expect=struct.pack("<LLLLLLL", 
                S_ERROR, self.state['seq'], 0, 0, 0, 0, 0))
        elif 2 == error:
            # Attempt NORMAL + WRITE + OP2_MEM
            if DEBUG: print "testing NORMAL + WRITE + OP2_MEM"
            dst = randint(0, UINT_MAX)
            src = randint(0, UINT_MAX)
            pkt = Packet(S_REQ, self.state['seq'], X_NORMAL, A_WRITE, OP2_MEM, dst, src)
            self.write(pkt.to_bin())
            self.read(length=SZ_PKT, expect=struct.pack("<LLLLLLL", 
                S_ERROR, self.state['seq'], 0, 0, 0, 0, 0))
        elif 3 == error:
            # Attempt SCRATCH R/W outside of region
            if DEBUG: print "testing SCRATCH outside of region"
            action = randint(0, A_LAST)
            dst = randint(0, UINT_MAX-SZ_SCRATCH)
            if HEAP_BGN >= dst and dst <= HEAP_END: dst += SZ_SCRATCH
            src = randint(0, UINT_MAX-SZ_SCRATCH)
            if HEAP_BGN >= src and src <= HEAP_END: src += SZ_SCRATCH
            pkt = Packet(S_REQ, self.state['seq'], X_SCRATCH, action, OP2_MEM, dst, src)
            self.write(pkt.to_bin())
            self.read(length=SZ_PKT, expect=struct.pack("<LLLLLLL", 
                S_ERROR, self.state['seq'], 0, 0, 0, 0, 0))
        elif 4 == error:
            # Attempt STATIC + WRITE
            if DEBUG: print "testing STATIC + WRITE"
            op2type = randint(0, OP2_LAST)
            dst = randint(0, UINT_MAX)
            src = randint(0, UINT_MAX)
            pkt = Packet(S_REQ, self.state['seq'], X_STATIC, A_WRITE, op2type, dst, src)
            self.write(pkt.to_bin())
            self.read(length=SZ_PKT, expect=struct.pack("<LLLLLLL", 
                S_ERROR, self.state['seq'], 0, 0, 0, 0, 0))
        elif 5 == error:
            # Attempt STATIC + READ outside of region
            if DEBUG: print "testing STATIC + READ + outside region"
            op2type = randint(0, OP2_LAST)
            dst = randint(SZ_STATIC, UINT_MAX)
            src = randint(SZ_STATIC, UINT_MAX)
            pkt = Packet(S_REQ, self.state['seq'], X_STATIC, A_READ, op2type, dst, src)
            self.write(pkt.to_bin())
            self.read(length=SZ_PKT, expect=struct.pack("<LLLLLLL", 
                S_ERROR, self.state['seq'], 0, 0, 0, 0, 0))


    def exit(self):
        """
        Send exit MAGIC as session ID to shut down.
        """
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "exit()"

        # We need to have at least 1 send/recv ndoe before exit.
        if False == self.state['exit_allowed']: return

        self.state['seq'] = self.state['seq'] + 1 % 0xFFFFFFFF
        
        pkt = Packet(S_EXIT, self.state['seq'])
        self.write(pkt.to_bin())
        return -1


    def dispatch(self):
        """
        Post-init intermediatery between actual work.
        """
        pass


    def finish(self):
        """
        Make sure we always end with an EXIT command.
        """
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "finish(), calling exit()"
        self.exit()


    def start(self):
        """
        Initialize state.
        """
        #self.delay(100)
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "start()"
        self.state['exit_allowed'] = False
        self.state['seq'] = randint(0, 0xFFFFFFFF)
        self.state['scratch'] = ['\0'] * SZ_SCRATCH
        self.state['static_switch'] = \
            open(os.path.join( \
                os.path.dirname(os.path.realpath(__file__)), 
                    "..", "..", "support", "switch.blob"), "rb").read()



