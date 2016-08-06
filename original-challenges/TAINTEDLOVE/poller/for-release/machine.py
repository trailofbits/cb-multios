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

from generator.actions import Actions, Variable
from random import choice, randint
import string
import struct
import os


# NOTE: this is super inefficient, don't care.
def random_bytes(min, max, mod=255):
    return ''.join(chr(choice(range(mod))) for _ in range(randint(min,max)))

def round_up_to_align(sz_alloc):
    SZ_PAGE = 0x1000
    return (sz_alloc + SZ_PAGE-1) & ~(SZ_PAGE-1)


class TaintedLove(Actions):

    GLOBAL_DEBUG = False
    GLOBAL_POV = False
    MAX_RX_BYTES = 1400 # 65535 is just unwieldy in testing...

    def entanglement_razzmatazz(self):
        """
        This calculation implements the challenge #1 from README.md: 
        Ignore / Throw Out Most Input
        """
        DEBUG = self.GLOBAL_DEBUG and True
        POV = self.GLOBAL_POV and True
        if DEBUG:
            print "entanglement_razzmatazz()"

        ID = "\x01"
        MIN_RX_BYTES = 1+1337
        GATE_MAGIC = 0xCAFEBABE

        # Half of the time, we will satisfy the gate. For these times, the 
        # requested mapping size must be aligned so we don't trigger the vuln.
        if POV: 
            gate_satisfy = 1
        else:
            gate_satisfy = self.chance(0.5)

        if gate_satisfy:
            gate = GATE_MAGIC
        else:
            while True:
                gate = randint(0, 0xFFFFFFFF)
                if GATE_MAGIC != gate:
                    break
        GATE = struct.pack("<L", gate)

        # Pick a random-sized allocation.
        # NOTE: We don't test 0-sized allocs.  A zero-sized allocation request 
        # will return EINVAL and terminate the calculation anyway.
        sz_alloc = randint(1, 0x2000) # Play nice for testing
        if gate_satisfy:
            sz_alloc = round_up_to_align(sz_alloc)
            if POV:
                sz_alloc -= 1
        if DEBUG:
            print "sz_alloc (after rounding): %d" % sz_alloc
        ALLOC = struct.pack("<H", sz_alloc)

        # Pick a random 2-byte OOB loop initializer. 
        # This only comes into play if we satisfy the gate.
        oob = randint(0, 0xFFFF)
        OOB = struct.pack("<H", oob)

        # Construct input.
        buf  = [ID] # next index: 1
        buf += random_bytes(200-1, 200-1) # next index: 200
        buf += GATE # size_t GATE_OFF = 200; (4 bytes); next index: 204
        buf += random_bytes(100-4, 100-4) # next index: 300
        buf += ALLOC # size_t ALLOC_OFF = 300; (2 bytes); next index: 302
        buf += random_bytes(100-2, 100-2) # next index: 400
        buf += OOB # size_t OOB_OFF = 400; (2 bytes); next index: 402
        buf += random_bytes(MIN_RX_BYTES-len(buf), self.MAX_RX_BYTES-len(buf))

        # Compute output.
        output = "\x00" # Default if gate not satisfied.
        if gate_satisfy: 
            mapping = {}
            mapping[0] = ord(OOB[0])
            mapping[1] = ord(OOB[1])
            if DEBUG:
                print "OOB inits: mapping[0] = 0x%02x, mapping[1] = 0x%02x" % \
                    (mapping[0], mapping[1])
            for i in range(0, sz_alloc-2):
                mapping[i+2] = (mapping[i+1] + mapping[i] + i) & 0xFF
                if DEBUG:
                    print "OOB calc #%d: mapping[i+2] = 0x%02x" % \
                        (i, mapping[i+2])
            output = struct.pack("B", mapping[sz_alloc-1])
        
        # Send the request, check the answer.
        self.write(buf)
        self.read(length=1, expect=output)


    def causality_poppycock(self):
        """
        This calculation implements the challenge #2 from README.md: 
        Sanitize Input
        """
        DEBUG = self.GLOBAL_DEBUG and True
        POV = self.GLOBAL_POV and False
        if DEBUG:
            print "causality_poppycock()"

        ID = "\x07"
        MIN_RX_BYTES = 1+1337
        SZ_VULN_BUF = 20

        SKIP_PRIME = 13
        GATE_PRIME = 37
        MAGIC_OFF = SKIP_PRIME*GATE_PRIME

        GATE_MAGIC_PASS = 0xAA
        GATE_MAGIC_FAIL = 0xBB

        TOTAL_BYTES = randint(MIN_RX_BYTES, self.MAX_RX_BYTES)

        # Half of the time, we will satisfy the gate. We use this opportunity to 
        # directly overwrite a byte in the output, deterring cheeseball defense.
        # NOTE: to make PoV, this must be true
        if POV:
            gate_satisfy = 1
        else:
            gate_satisfy = self.chance(0.5)
        
        if DEBUG:
            print "gate_satisfy: %d" % gate_satisfy

        if gate_satisfy:
            GATE_MAGIC = GATE_MAGIC_PASS
        else:
            GATE_MAGIC = GATE_MAGIC_FAIL
    
        # First, we generate a candidate random buffer, then we fix up 
        # according to whether we want to satisfy the gate.
        # We keep all the multiples of SKIP_PRIME modulo SZ_VULN_BUF so that 
        # behavior is identical to expected PATCHED version (the RELEASE 
        # version will not "sanitize" these modulos).
        buf = [ID]
        for _ in range(0, TOTAL_BYTES-SKIP_PRIME, SKIP_PRIME):
            buf += random_bytes(SKIP_PRIME-1, SKIP_PRIME-1)
            buf += random_bytes(1, 1, SZ_VULN_BUF-1)
        
        if DEBUG:
            print "poppycock | TOTAL_BYTES = %d, len(buf) = %d, TOTAL_BYTES-len(buf) = %d" % \
                (TOTAL_BYTES, len(buf), TOTAL_BYTES-len(buf))
        buf += random_bytes(TOTAL_BYTES-len(buf), TOTAL_BYTES-len(buf))

        if POV:
            buf[SKIP_PRIME*GATE_PRIME] = chr(255)

        # Solve for gate FIXUP.
        GATE_CURR = 0
        for i in range(0, TOTAL_BYTES, GATE_PRIME):

            if POV and i == SKIP_PRIME*GATE_PRIME:
                GATE_CURR = (GATE_CURR + (ord(buf[i]))) & 0xFF
            else:
                GATE_CURR = (GATE_CURR + (ord(buf[i]) % SZ_VULN_BUF)) & 0xFF

            if DEBUG:
                print "poppycock | ord(buf[%04d]) = 0x%02x, ord(buf[%04d]) %% SZ_VULN_BUF = 0x%02x" % (i, ord(buf[i]), i, ord(buf[i]) % SZ_VULN_BUF)
                print "poppycock | #%08d: after adding buf[%04d] = 0x%02x, GATE_CURR = 0x%02x" % (i, i, ord(buf[i]), GATE_CURR)
        FIXUP = (GATE_MAGIC - GATE_CURR) & 0xFF
        if DEBUG:
            print "poppycock | final GATE_CURR = 0x%02x, would need to add 0x%02x (%d) of FIXUP to match 0x%02x" % (GATE_CURR, FIXUP, FIXUP, GATE_MAGIC)

        # Apply FIXUP. We need to spread the fixup over several GATE_PRIME 
        # offsets because a proper patch will mod them SZ_VULN_BUF.
        # There is a (slim) possibility, however, that there are insufficient 
        # deltas to apply the FIXUP.  In this case, we take the nuclear option:
        # 1) zero out of all of the GATE_PRIME multiples
        # 2) try again
        # Yes, this is very messy.
        i = GATE_PRIME
        ORIG_FIXUP = FIXUP
        while (FIXUP):

            # This happens if there's insufficient delta to apply FIXUP
            if i > len(buf)-1:
                # Go nuclear
                if DEBUG:
                    print "poppycock | deltas insufficient for FIXUP; nuclear option..."
                buf[0] = ID
                for j in range(GATE_PRIME, TOTAL_BYTES-GATE_PRIME, GATE_PRIME):
                    buf[j] = chr(0)
                # Try again
                i = GATE_PRIME
                FIXUP = ORIG_FIXUP
                continue

            if DEBUG:
                print "poppycock | applying FIXUP; i = %d" % i
            curr = ord(buf[i]) % SZ_VULN_BUF
            delta = min((SZ_VULN_BUF-1) - curr, FIXUP)
            if DEBUG:
                print "poppycock | adding delta = %d to buf[%04d]" % (delta, i)
            buf[i] = chr(curr + delta)
            FIXUP -= delta
            i += GATE_PRIME
        
        # Compute vuln_buf[]
        vuln_buf = [0] * SZ_VULN_BUF
        for i in range(1, TOTAL_BYTES):
            tmp1 = ord(buf[i]) % SZ_VULN_BUF 
            tmp2 = ( tmp1 ^ vuln_buf[ (tmp1+1) % SZ_VULN_BUF ] ) % SZ_VULN_BUF
            # if DEBUG:
            #     print "tmp2 = ( tmp1{0x%02x} ^ vuln_buf[ (tmp1+1) %% SZ_VULN_BUF ]{0x%02x} ) %% SZ_VULN_BUF" % (tmp1, vuln_buf[ (tmp2+1) % SZ_VULN_BUF ])
            #     print "poppycock | #%08d: vuln_buf[%02d] = 0x%02x" % (i, tmp1, tmp2)
            vuln_buf[tmp1] = tmp2

        if gate_satisfy:
            # If we satisfy the gate, we have one final vuln_buf write (the 
            # vulnerable one). This will be reflected in the output.
            vuln_buf[ord(buf[MAGIC_OFF]) % SZ_VULN_BUF] = 0xAA

        output = 0
        for i in range(0, SZ_VULN_BUF-3, 4):
            output +=   vuln_buf[i+0] <<  0 | \
                        vuln_buf[i+1] <<  8 | \
                        vuln_buf[i+2] << 16 | \
                        vuln_buf[i+3] << 24
            if DEBUG:
                print "poppycock | #%08d: output = 0x%08x" % (i, output)
        
        if DEBUG:
            print "poppycock | final output: 0x%08x" % output

        self.write(buf)
        self.read(length=4, expect=struct.pack("<L", output))
        

    def heisenberg_hooey(self):
        """
        This calculation implements the challenge #3 from README.md: 
        Use "Unusual" Means to Terminate or Propagate Taint

        From the poller perspective, this is a relatively simple function.  
        Much of the input is thrown out, but in ways that may trip up a CRS.

        Really all we care about are the PROPGATE items.  
        The CONSTIFY items are irrelevant.
        """
        DEBUG = self.GLOBAL_DEBUG and True
        POV = self.GLOBAL_POV and True
        if DEBUG:
            print "heisenberg_hooey()"

        ID = "\x03"
        MIN_RX_BYTES = 1+1337

        if POV:
            gate_satisfy = 1
        else:
            gate_satisfy = self.chance(0.5)

        if DEBUG:
            print "gate_satisfy: %d" % gate_satisfy

        buf  = [ID]
        buf += random_bytes(MIN_RX_BYTES-len(buf), self.MAX_RX_BYTES-len(buf))

        # The following are interesting offsets; the others are ignored:

        # size_t SYSCALL_PROP_OFF = 1+600;
        # - vuln: 0xDE after arithmetic
        # - arith: val = val*2 + 1
        # - vuln: 0x6F before arithmetic
        SYSCALL_PROP_OFF = 1+600 

        # size_t FLOAT_PROP_OFF = 1+400;
        # - vuln: 0xAD after arithmetic.
        # - arith: val = val*2
        # - vuln: 0x56 before arithmetic
        FLOAT_PROP_OFF = 1+400 
        
        # size_t BE_OFF = 1+800;
        # gate: must be 0xBE
        BE_OFF = 1+800

        # size_t EF_OFF = 1+900;
        # gate: must be 0xEF
        EF_OFF = 1+900 

        # Another offset that factors into the output:
        # size_t VULN_OFF = 1+1000;
        # - factors into output
        VULN_OFF = 1+1000

        # If we pass the gate, we will do an assignment.
        # If we pass the 'vuln', this assignment will cause a crash.

        if gate_satisfy:
            buf[BE_OFF] = "\xBE"
            buf[EF_OFF] = "\xEF"
        else:
            buf[BE_OFF] = "\x42"
            buf[EF_OFF] = "\x42"

        if POV:
            buf[SYSCALL_PROP_OFF] = "\x56"
            buf[FLOAT_PROP_OFF] = "\x6F"
            buf[BE_OFF] = "\xBE"
            buf[EF_OFF] = "\xEF"
        else:
            # There's a (very small) possibility (2^32) we tripped the gate and 
            # will exercise vuln.  
            # We need to negate this possibility in the poller.
            # if  0x56 == ord(buf[SYSCALL_PROP_OFF]) and \
                # 0x6F == ord(buf[FLOAT_PROP_OFF]) and \
            if  0xBE == ord(buf[BE_OFF]) and \
                0xEF == ord(buf[EF_OFF]):
                buf[SYSCALL_PROP_OFF] = "\xAA"

        # If we tripped the gate, we must do the assignment:
        if  0xBE == ord(buf[BE_OFF]) and \
            0xEF == ord(buf[EF_OFF]):
            buf[VULN_OFF] = "\x42"

        self.write(buf)

        # Apply transformations to offsets as CB does:
        buf[SYSCALL_PROP_OFF] = chr((ord(buf[SYSCALL_PROP_OFF]) * 2 + 1) & 0xFF)
        buf[FLOAT_PROP_OFF] = chr(((ord(buf[FLOAT_PROP_OFF]) * 2)) & 0xFF)

        # Calculate anticipated output.
        output =    (    ord(buf[FLOAT_PROP_OFF]) ^ \
                        (ord(buf[SYSCALL_PROP_OFF]) + ord(buf[VULN_OFF])) \
                    ) & 0xFFFFFFFF
        if DEBUG:
            print "buf[SYSCALL_PROP_OFF] = 0x%02x, buf[FLOAT_PROP_OFF] = 0x%02x, buf[VULN_OFF] = 0x%02x, output = 0x%08x" % \
            (   ord(buf[SYSCALL_PROP_OFF]), \
                ord(buf[FLOAT_PROP_OFF]), \
                ord(buf[VULN_OFF]), \
                output)

        # If we pass the gate, it sends extra data:
        if gate_satisfy:
            self.read(length=4, expect=struct.pack("<L", 0xDEADBEEF))
        self.read(length=4, expect=struct.pack("<L", output))


    def relativistic_jabberwock(self):
        """
        This calculation implements the challenge #4 from README.md: 
        Symbolic Memory Accesses
        """
        DEBUG = self.GLOBAL_DEBUG and True
        POV = self.GLOBAL_POV and True
        if DEBUG:
            print "relativistic_jabberwock()"

        ID = "\x04"
        MIN_RX_BYTES = 1+1337

        if POV:
            gate_satisfy = 1
        else:
            gate_satisfy = self.chance(0.5)
        
        if DEBUG:
            print "gate_satisfy: %d" % gate_satisfy

        # First, we get a random buffer, then we fix it up.
        buf  = [ID]
        buf += random_bytes(MIN_RX_BYTES-len(buf), self.MAX_RX_BYTES-len(buf))

        # Relevant offsets:
        SYM_PROP_PTR_1 = 1+100 # size_t SYM_PROP_PTR_1 = 1+100;
        SYM_PROP_PTR_2 = 1+200 # size_t SYM_PROP_PTR_2 = 1+200;
        SYM_PROP_VAL = 1+70 # size_t SYM_PROP_VAL = 1+70;

        SYM_CONST_PTR_1 = 1+50 # size_t SYM_CONST_PTR_1 = 1+50;
        SYM_CONST_PTR_2 = 1+60 # size_t SYM_CONST_PTR_2 = 1+60;

        VULN_OFF = 1+400 # size_t VULN_OFF = 1+400;
        
        GATE_MAGIC_OFF = 1+10

        # In order to satisfy the gate, we need to:
        # 1) propagate to rx_buf[SYM_PROP_PTR_1] & point to GATE_MAGIC
        # 2) re-constify at rx_buf[rx_buf[SYM_CONST_PTR_1]]
        if gate_satisfy:

            # 1) propagate to rx_buf[SYM_PROP_PTR_1] & point to GATE_MAGIC

            buf[SYM_PROP_PTR_1] = chr(1+40) # unused
            buf[SYM_PROP_PTR_2] = chr(SYM_PROP_PTR_1)

            # write GATE_MAGIC_OFF into buf[buf[SYM_PROP_PTR_1]]
            buf[SYM_PROP_VAL] = chr(GATE_MAGIC_OFF)

            # writing backing GATE_MAGIC values
            buf[GATE_MAGIC_OFF+0] = "\xd5"
            buf[GATE_MAGIC_OFF+1] = "\x00"
            buf[GATE_MAGIC_OFF+2] = "\x00"
            buf[GATE_MAGIC_OFF+3] = "\xd0"

            ############################################################

            # 2) re-constify at rx_buf[rx_buf[SYM_CONST_PTR_1]]
            # - rx_buf[rx_buf[SYM_CONST_PTR_1]] is constified to 0
            # - rx_buf[rx_buf[SYM_CONST_PTR_2]] is constified to 42
            # By having them alias the same memory, we satisfy.
            buf[SYM_CONST_PTR_1] = chr(1+20)
            buf[SYM_CONST_PTR_2] = chr(1+20)

            # Finally, we gotta make sure we do/don't trip the vuln.
            if POV:
                buf[VULN_OFF] = chr(255) 
            else:
                buf[VULN_OFF] = chr(1)
            # NOTE: we never try making this 0... let's cut them some slack.

        else:
            # Make sure #1 doesn't happen by just pointing them both to some 
            # place that isn't used.  Throw CRSs a bone.
            buf[SYM_PROP_PTR_1] = chr(1+30)
            buf[SYM_PROP_PTR_2] = chr(1+31)

            # Make sure #2 doesn't happen.
            buf[SYM_CONST_PTR_1] = chr(1+32)

        # Write out our buffer.
        self.write(buf)

        # Apply same transformations as CB.
        buf[SYM_PROP_PTR_1] = chr(0);
        buf[ord(buf[SYM_PROP_PTR_1])+0] = chr(0);
        buf[ord(buf[SYM_PROP_PTR_1])+1] = chr(0);
        buf[ord(buf[SYM_PROP_PTR_1])+2] = chr(0);
        buf[ord(buf[SYM_PROP_PTR_1])+3] = chr(0); 

        buf[ord(buf[SYM_PROP_PTR_2])] = buf[SYM_PROP_VAL];
        buf[ord(buf[SYM_CONST_PTR_1])] = chr(0);
        buf[ord(buf[SYM_CONST_PTR_2])] = chr(0x42);

        if gate_satisfy:
            buf[1000] = chr(0x42);

        # Calculate expected output
        if gate_satisfy:
            # NOTE: the first item will always be index 1000 because we don't 
            # want to trip vuln.
            output =    (   ord(buf[1000])                      <<  0 | \
                            ord(buf[SYM_CONST_PTR_1])           <<  8 | \
                            ord(buf[ord(buf[SYM_CONST_PTR_1])]) << 16 | \
                            ord(buf[SYM_PROP_VAL])              << 24) & 0xFFFFFFFF
        else:
            output =   ~((  0                                   <<  0 | \
                            ord(buf[SYM_CONST_PTR_1])           <<  8 | \
                            ord(buf[ord(buf[SYM_CONST_PTR_1])]) << 16 | \
                            ord(buf[SYM_PROP_VAL])              << 24) & 0xFFFFFFFF) & 0xFFFFFFFF
        
        self.read(length=4, expect=struct.pack("<L", output))


    def exit(self):
        """
        Invoke exit functionality, terminating test."
        """
        DEBUG = True and self.GLOBAL_DEBUG
        if DEBUG:
            print "exit()"

        ID = ord("\x00")
        EXIT_CODE = randint(1, 255)

        self.write(struct.pack("BB", ID, EXIT_CODE))
        self.read(length=1, expect=struct.pack("B", EXIT_CODE))

        # This node is terminal
        return -1

    def start(self):
        """
        Intialize state; happens once, then goes to dispatch.
        """
        pass




