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

# NOTE1: All the different opcodes are generated in a single node in order to 
# conform to 1 node per write convention in other CBs.

# NOTE2: There's no special exit code.  The CB executes the bytecode (if it's 
# valid) and then exits.

# REM
# op1 = op1 for calculations in Python
# op1_inst = op1 as we're sending in the instruction
#   - differs for offsets (op1 holds value, op1_inst holds offset)
#   - differs for ignored op1 (no need to have an op1, we're not computing over it)

from generator.actions import Actions, Variable
from random import randint, choice
import struct

class InterpretThis(Actions):

    GLOBAL_DEBUG = False
    GLOBAL_POV = False

    SCRATCH_SZ = 2048
    BYTECODE_SZ = 2048

    INST_OFF_SZ = 4
    INST_IMM_SZ = 2

    INST_MASK_DST = 0x01
    INST_MASK_ACC = 0x02
    INST_MASK_OP1 = 0x04
    INST_MASK_OP2 = 0x08
    INST_MASK_OPCODE = 0xF0

    OPCODE_ADD = 0x00
    OPCODE_SUB = 0x10
    OPCODE_MUL = 0x20
    OPCODE_DIV = 0x30 
    OPCODE_OUT = 0xF0
    ops = [OPCODE_ADD, OPCODE_SUB, OPCODE_MUL, OPCODE_DIV, OPCODE_OUT]

    OUT_DEFAULT = 0xDEADBEEF
    NUM_OFFSETS = 5

    def bytes(self):
        """
        The node that does everything (bytecode generation, output verification).
        """
        DEBUG = self.GLOBAL_DEBUG and True
        POV = self.GLOBAL_POV and True

        bytecode = ""

        if POV:
            # We intend to cause dereference in kernelspace as well as @ NULL.
            # Either dereference should cause a crash, but it's safer to do 
            # both in the face of cheeseball defenses.

            # Immediates are only 2B long, so we must use math to construct 
            # the 4B offsets. Because x86, these offsets need to be in LE.

            # XXXX: We make two assumptions:
            #   space is @ 0xb7fff000
            #   kernelspace is 0xc0000000+
            # space = 0xb7fff000
            # del_null = 0x100000000 - space = 0x48001000 -> 0x00100048
            # del_kern =  0xc0000000 - space = 0x08001000 -> 0x00100008
            SCRATCH_NULL = 0x500
            SCRATCH_KERN = 0x600

            ####
            # Cause NULL deref
            ####

            # 0) ACC <- 0x1000
            opcode = self.OPCODE_ADD
            opcode |= self.INST_MASK_ACC
            bytecode += struct.pack(">B", opcode)
            bytecode += struct.pack(">H", 0xFFFF) # ignored
            bytecode += struct.pack(">H", 0x1000) 

            # 1) ACC *= 0x100 = 0x00100000
            opcode = self.OPCODE_MUL
            opcode |= self.INST_MASK_ACC
            bytecode += struct.pack(">B", opcode)
            bytecode += struct.pack(">H", 0xFFFF) # ignored
            bytecode += struct.pack(">H", 0x0100) 

            # 2) ACC += 0x48 = 0x00100048
            # # We store this result off to use it later.
            opcode = self.OPCODE_ADD
            opcode |= self.INST_MASK_DST
            opcode |= self.INST_MASK_ACC
            opcode |= self.INST_MASK_OP1
            bytecode += struct.pack(">B", opcode)
            bytecode += struct.pack(">L", SCRATCH_NULL) 
            bytecode += struct.pack(">H", 0x0048)

            # 3) Reset ACC to 0
            opcode = self.OPCODE_MUL
            opcode |= self.INST_MASK_ACC
            bytecode += struct.pack(">B", opcode)
            bytecode += struct.pack(">H", 0xFFFF) # ignored
            bytecode += struct.pack(">H", 0x0000) 

            # 4) Rewrite of subsequent instruction.
            # CLOBBER_NULL (next op1) <- ACC (0) + *(SCRATCH_NULL)
            CLOBBER_NULL = (self.SCRATCH_SZ + # get us to bytecode section
                            len(bytecode) + # consume bytecode length thus far
                            1 + 4 + 4 + # consume this instruction itself
                            1) # consume next instruction's opcode
            opcode = self.OPCODE_ADD
            opcode |= self.INST_MASK_DST
            opcode |= self.INST_MASK_ACC
            opcode |= self.INST_MASK_OP1
            opcode |= self.INST_MASK_OP2
            bytecode += struct.pack(">B", opcode)
            bytecode += struct.pack(">L", CLOBBER_NULL) # to be clobbered
            bytecode += struct.pack(">L", SCRATCH_NULL) # doesn't matter

            # 5) SIGSEGV on NULL
            opcode = self.OPCODE_ADD
            opcode |= self.INST_MASK_DST
            opcode |= self.INST_MASK_ACC
            opcode |= self.INST_MASK_OP1
            bytecode += struct.pack(">B", opcode)
            bytecode += struct.pack(">L", 0x00000000) # to be clobbered
            bytecode += struct.pack(">H", 0xAAAA) # doesn't matter

            ####
            # Cause KERN deref
            ####

            # 0) ACC <- 0x1000
            opcode = self.OPCODE_ADD
            opcode |= self.INST_MASK_ACC
            bytecode += struct.pack(">B", opcode)
            bytecode += struct.pack(">H", 0xFFFF) # ignored
            bytecode += struct.pack(">H", 0x1000) 

            # 1) ACC *= 0x100 = 0x00100000
            opcode = self.OPCODE_MUL
            opcode |= self.INST_MASK_ACC
            bytecode += struct.pack(">B", opcode)
            bytecode += struct.pack(">H", 0xFFFF) # ignored
            bytecode += struct.pack(">H", 0x0100) 

            # 2) ACC += 0x8 = 0x00100008
            # # We store this result off to use it later.
            opcode = self.OPCODE_ADD
            opcode |= self.INST_MASK_DST
            opcode |= self.INST_MASK_ACC
            opcode |= self.INST_MASK_OP1
            bytecode += struct.pack(">B", opcode)
            bytecode += struct.pack(">L", SCRATCH_KERN) 
            bytecode += struct.pack(">H", 0x0008)

            # 3) Reset ACC to 0
            opcode = self.OPCODE_MUL
            opcode |= self.INST_MASK_ACC
            bytecode += struct.pack(">B", opcode)
            bytecode += struct.pack(">H", 0xFFFF) # ignored
            bytecode += struct.pack(">H", 0x0000) 

            # 4) Rewrite of subsequent instruction.
            # CLOBBER_NULL (next op1) <- ACC (0) + *(SCRATCH_NULL)
            CLOBBER_NULL = (self.SCRATCH_SZ + # get us to bytecode section
                            len(bytecode) + # consume bytecode length thus far
                            1 + 4 + 4 + # consume this instruction itself
                            1) # consume next instruction's opcode
            opcode = self.OPCODE_ADD
            opcode |= self.INST_MASK_DST
            opcode |= self.INST_MASK_ACC
            opcode |= self.INST_MASK_OP1
            opcode |= self.INST_MASK_OP2
            bytecode += struct.pack(">B", opcode)
            bytecode += struct.pack(">L", CLOBBER_NULL) # to be clobbered
            bytecode += struct.pack(">L", SCRATCH_KERN) # doesn't matter

            # 5) SIGSEGV on KERN
            opcode = self.OPCODE_ADD
            opcode |= self.INST_MASK_DST
            opcode |= self.INST_MASK_ACC
            opcode |= self.INST_MASK_OP1
            bytecode += struct.pack(">B", opcode)
            bytecode += struct.pack(">L", 0x00000000) # to be clobbered
            bytecode += struct.pack(">H", 0xAAAA) # doesn't matter

            self.write(struct.pack("<H", len(bytecode)))
            self.write(bytecode)

            return -1

        acc = 0
        out = self.OUT_DEFAULT
        if DEBUG: inst_count = 0

        # At a minimim, we set bytecode to be 20 bytes or larger, so that we 
        # send *something*.  Not sending any instructions isn't a problem for 
        # the CB, but is for cb-replay and empty self.write()s.  We could also 
        # have a special case, but this is easier.
        bytecode_len = randint(20, self.BYTECODE_SZ-4)
        bytes_left = bytecode_len
        if DEBUG: print "bytecode_len = 0x%04x (%d)" % (bytecode_len, bytecode_len)

        while 0 < bytes_left:

            if DEBUG: 
                print "\n----instruction #%d----" % inst_count
                print "current memory state: %s" % self.state['offsets']
                dbg_flags = ""

            opcode = 0
            inst_len = 0

            # Pick INST_MASK_DST
            # F: store in ACC; T: store in memory
            if (choice([False, True])):
                opcode |= self.INST_MASK_DST
                if DEBUG: dbg_flags += " +INST_MASK_DST"
            else:
                if DEBUG: dbg_flags += " -INST_MASK_DST"

            # Pick INST_MASK_ACC
            # F: op1 & op2; T: ACC & op2.
            # If INST_MASK_DST is set, then op1 is the dst offset; operands 
            #   must be ACC & op2. INST_MASK_ACC must therefore also be set.
            if (opcode & self.INST_MASK_DST or choice([False, True])):
                opcode |= self.INST_MASK_ACC
                if DEBUG: dbg_flags += " +INST_MASK_ACC"
                inst_op1 = acc
                op1 = acc
            else:
                # At this point, op1 is unknown; could be offset or immediate.
                if DEBUG: dbg_flags += " -INST_MASK_ACC"

            # Pick INST_MASK_OP1 & op1 contents
            # F: immediate; T: offset
            # If INST_MASK_DST is set, then op1 is the dst offset; 
            #   INST_MASK_OP1 must be set.
            if (opcode & self.INST_MASK_DST or choice([False, True])):
                opcode |= self.INST_MASK_OP1
                # ?INST_MASK_DST +INST_MASK_OP1
                if DEBUG: dbg_flags += " +INST_MASK_OP1"
                inst_op1 = choice(self.state['offsets'].keys())
                op1 = self.state['offsets'][inst_op1]
            else:
                # -INST_MASK_DST
                if opcode & self.INST_MASK_ACC:
                    # (-INST_MASK_DST) +INST_MASK_ACC
                    # operands are ACC and op2, dst is ACC.
                    # op1 and INST_MASK_OP1 are ignored, so use full range.
                    if choice([False, True]): 
                        opcode |= self.INST_MASK_OP1
                        if DEBUG: dbg_flags += " +INST_MASK_OP1"
                        # TODO: relax this to full range? (need to modify vrfy() checks)
                        inst_op1 = randint(0, self.SCRATCH_SZ-4)
                        op1 = inst_op1
                    else:
                        if DEBUG: dbg_flags += " -INST_MASK_OP1"
                        inst_op1 = randint(0, 0xFFFF)
                        op1 = inst_op1
                else:
                    # (-INST_MASK_DST) -INST_MASK_ACC
                    # operands are op1 and op2, dst is ACC.
                    # We need to determine whether op1 is offset.
                    if choice([False, True]):
                        # (-INST_MASK_DST) (-INST_MASK_ACC) +INST_MASK_OP1
                        # operands are op1 (offset) and op2, dst is ACC.
                        opcode |= self.INST_MASK_OP1
                        if DEBUG: dbg_flags += " +INST_MASK_OP1"
                        inst_op1 = choice(self.state['offsets'].keys())
                        op1 = self.state['offsets'][inst_op1]
                    else:
                        # (-INST_MASK_DST) (-INST_MASK_ACC) -INST_MASK_OP1
                        # operands are op1 (imm) and op2, dst is ACC.
                        if DEBUG: dbg_flags += " -INST_MASK_OP1"
                        inst_op1 = inst_op1 = randint(0, 0xFFFF)
                        op1 = inst_op1

            # Pick INST_MASK_OP2 & op2 contents
            if (choice([False, True])):
                opcode |= self.INST_MASK_OP2
                if DEBUG: dbg_flags += " +INST_MASK_OP2"
                inst_op2 = choice(self.state['offsets'].keys())
                op2 = self.state['offsets'][inst_op2]
            else:
                if DEBUG: dbg_flags += " -INST_MASK_OP2"
                inst_op2 = randint(0, 0xFFFF)
                op2 = inst_op2

            # Pick the operation.
            opcode |= choice(self.ops)

            # Emulate the operation.
            if   (opcode & self.INST_MASK_OPCODE) == self.OPCODE_ADD:
                if DEBUG: print "OPCODE_ADD |%s" % dbg_flags
                if opcode & self.INST_MASK_ACC:
                    op = "tmp = (acc + op2) & 0xFFFFFFFF"
                    if DEBUG: print op
                    exec(op)
                else:
                    op = "tmp = (op1 + op2) & 0xFFFFFFFF"
                    if DEBUG: print op
                    exec(op)
            elif (opcode & self.INST_MASK_OPCODE) == self.OPCODE_SUB:
                if DEBUG: print "OPCODE_SUB |%s" % dbg_flags
                if opcode & self.INST_MASK_ACC:
                    op = "tmp = (acc - op2) & 0xFFFFFFFF"
                    if DEBUG: print op
                    exec(op)
                else:
                    op = "tmp = (op1 - op2) & 0xFFFFFFFF"
                    if DEBUG: print op
                    exec(op)
            elif (opcode & self.INST_MASK_OPCODE) == self.OPCODE_MUL:
                if DEBUG: print "OPCODE_MUL |%s" % dbg_flags
                if opcode & self.INST_MASK_ACC:
                    op = "tmp = (acc * op2) & 0xFFFFFFFF"
                    if DEBUG: print op
                    exec(op)
                else:
                    op = "tmp = (op1 * op2) & 0xFFFFFFFF"
                    if DEBUG: print op
                    exec(op)
            elif (opcode & self.INST_MASK_OPCODE) == self.OPCODE_DIV:
                if 0 == op2: op2 = 0xf000f000
                if DEBUG: print "OPCODE_DIV |%s" % dbg_flags
                if opcode & self.INST_MASK_ACC:
                    op = "tmp = (acc / op2) & 0xFFFFFFFF"
                    if DEBUG: print op
                    exec(op)
                else:
                    op = "tmp = (op1 / op2) & 0xFFFFFFFF"
                    if DEBUG: print op
                    exec(op)
            elif (opcode & self.INST_MASK_OPCODE) == self.OPCODE_OUT:
                if DEBUG: print "OPCODE_OUT |%s" % dbg_flags
                op = "out = acc"
                if DEBUG: print op
                exec(op)

            # Store result, as appropriate.
            if (opcode & self.INST_MASK_OPCODE) == self.OPCODE_OUT:
                pass # All we do is OUT <-- ACC, which we've already done.
            else:
                if DEBUG: print "tmp = 0x%08x" % tmp
                if opcode & self.INST_MASK_DST:
                    self.state['offsets'][inst_op1] = tmp
                else:
                    acc = tmp

            if DEBUG: print "    ************    "

            # Add to bytecode buffer, advance.
            bytecode += struct.pack(">B", opcode)
            if DEBUG: print "opcode: 0x%02x" % opcode
            inst_len += 1

            if opcode & self.INST_MASK_OP1:
                if DEBUG: print "inst_op1 (offset): 0x%08x (%d)" % (inst_op1, inst_op1)
                if DEBUG: print "op1 (offset): 0x%08x (%d)" % (op1, op1)
                bytecode += struct.pack(">L", inst_op1)
                inst_len += 4
            else:
                if DEBUG: print "inst_op1 (imm): 0x%04x (%d)" % (inst_op1, inst_op1)
                if DEBUG: print "op1 (imm): 0x%04x (%d)" % (op1, op1)
                bytecode += struct.pack(">H", inst_op1)
                inst_len += 2

            if opcode & self.INST_MASK_OP2:
                if DEBUG: print "inst_op2 (offset): 0x%08x (%d)" % (inst_op2, inst_op2)
                if DEBUG: print "op2 (offset): 0x%08x (%d)" % (op2, op2)
                bytecode += struct.pack(">L", inst_op2)
                inst_len += 4
            else:
                if DEBUG: print "inst_op2 (imm): 0x%04x (%d)" % (inst_op2, inst_op2)
                if DEBUG: print "op2 (imm): 0x%04x (%d)" % (op2, op2)
                bytecode += struct.pack(">H", inst_op2)
                inst_len += 2

            if DEBUG: 
                print "#%04d: acc = 0x%08x" % (inst_count, acc)
                inst_count += 1

            bytes_left -= inst_len
            # If bytes_left < max(len(inst)), then we're done.
            if 9 > bytes_left: break

        # Send the bytecode length + payload.
        self.write(struct.pack("<H", len(bytecode)))
        self.write(bytecode)

        # Verify output.
        self.read(length=4, expect=struct.pack("<L", out))

        # It takes ~20mins to run through 1000 polls when we conduct 1 send / 
        # recv pair per poll.  Not feasible to do more; this CB is slow.
        return -1


    def start(self):
        """
        Initialize state.

        Specifically, choose SCRATCH offsets we'll actually be using, up to 
        self.NUM_OFFSETS.
        """
        DEBUG = self.GLOBAL_DEBUG and True
        if DEBUG: print "\n-------setup-------"

        # SCRATCH_SZ is large and it's unlikely that we'll propagate through 
        # the same offsets if we don't limit ourselves.  So, we limit ourselves 
        # to NUM_OFFSETS.  We choose these offsets here.
        # K = offset, V = value
        self.state['offsets'] = {}
        for _ in range(self.NUM_OFFSETS):
            idx = randint(0, self.SCRATCH_SZ-4)
            # Only do multiples of 4 because we don't fully emulate memory 
            # correctly here (we don't model one write overflowing into another).
            while 0 != (idx % 4): idx = randint(0, self.SCRATCH_SZ-4)
            self.state['offsets'][idx] = 0

        if DEBUG: print "offsets: %s" % self.state['offsets'].keys()


