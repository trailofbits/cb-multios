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

from generator.actions import Actions, Variable
from random import randint, choice
import struct
from copy import deepcopy

GLOBAL_DEBUG = False
GLOBAL_POV = False

OPERATION_SZ = 8
SCRATCH_SZ = 256
OPCODE_SZ_MAX = 512
OPCODE_SZ_UTILIZED = 256

SESSIONS_MAX = 20

MAGIC_NEW_SESSION = 0
MAGIC_EXIT = 0xE3E3F046


def refresh_session(old_session, DEBUG):
    """
    Generates opcodes, computes expected output from SCRATCH area.

    Consumes: session tuple
    Produces: new session tuple
    """
    DEBUG = GLOBAL_DEBUG and True
    if DEBUG: print "refresh_session()"
    
    opcodes = { 
        'NUL' : 0x004C554E, # 'NUL\x00'
        'SET' : 0x00544553, # 'SET\x00'
        'ADD' : 0x00444441, # 'ADD\x00'
        'SUB' : 0x00425553, # 'SUB\x00'
        'MUL' : 0x004C554D, # 'MUL\x00'
        'DIV' : 0x00564944, # 'DIV\x00'
        'SHR' : 0x00524853, # 'SHR\x00'
        'SHL' : 0x004C4853, # 'SHL\x00'
    }

    session = deepcopy(old_session)
    session['opcodes'] = ""

    for i in range(0, session['sz'], OPERATION_SZ):

        # Pick an opcode + immediate + offset.
        imm = randint(0, 0xFF)
        off = randint(0, SCRATCH_SZ-1)

        # Should we use a real opcode or an unknown one?
        if (0 == randint(0, 9)):
            # Do an unknown one.
            opc_str = "UNK"
            while True:
                opc = randint(0, 0xFFFFFFFF)
                unused = True
                for v in opcodes.values():
                    if opc == v: 
                        unused = False
                        break
                if unused == True: 
                    break
        else:
            # Do a known one.
            opc_str = choice(opcodes.keys())
            opc = opcodes[opc_str]

        if DEBUG: 
            print "op[%04d]: %s, imm = 0x%02x (%d), off = 0x%02x (%d)" % \
                (i, opc_str, imm, imm, off, off)        

        # Add it to the opcode buffer.
        session['opcodes'] += struct.pack("<LBBBB", opc, ord(' '), imm, ord(' '), off)

        # Emulate the operation on the scratch buffer.
        if   'NUL' == opc_str:
            if DEBUG: print "0x%02x (%d) = 0x00" % (off, off) 
            session['scratch'][off] = chr(0)
        elif 'SET' == opc_str: 
            if DEBUG: print "0x%02x (%d) = 0x%02x (%d)" % (off, off, imm, imm) 
            session['scratch'][off] = chr(imm)
        elif 'ADD' == opc_str:
            if DEBUG: print "0x%02x (%d) += 0x%02x (%d)" % (off, off, imm, imm) 
            session['scratch'][off] = chr((ord(session['scratch'][off]) + imm) % 0x100)
        elif 'SUB' == opc_str:
            if DEBUG: print "0x%02x (%d) -= 0x%02x (%d)" % (off, off, imm, imm) 
            session['scratch'][off] = chr((ord(session['scratch'][off]) - imm) % 0x100)
        elif 'MUL' == opc_str:
            if DEBUG: print "0x%02x (%d) *= 0x%02x (%d)" % (off, off, imm, imm) 
            session['scratch'][off] = chr((ord(session['scratch'][off]) * imm) % 0x100)
        elif 'DIV' == opc_str:
            if 0 == imm:    
                if DEBUG: print "0x%02x (%d) += 0xAA" % (off, off) 
                session['scratch'][off] = chr(0xAA)
            else:
                if DEBUG: print "0x%02x (%d) *= 0x%02x (%d)" % (off, off, imm, imm) 
                session['scratch'][off] = chr((ord(session['scratch'][off]) / imm) % 0x100)
        elif 'SHR' == opc_str:
            if DEBUG: print "0x%02x (%d) >>= 0x%02x (%d)" % (off, off, imm, imm) 
            session['scratch'][off] = chr((ord(session['scratch'][off]) >> imm) % 0x100)
        elif 'SHL' == opc_str:
            if DEBUG: print "0x%02x (%d) <<= 0x%02x (%d)" % (off, off, imm, imm) 
            session['scratch'][off] = chr((ord(session['scratch'][off]) << imm) % 0x100)
        elif 'UNK' == opc_str:
            if DEBUG: print "UNK opcode; no effect on scratch buffer"
        else:
            print "INVALID OPC_STR; EXITING..."
            return -1

    return session


class CloudCompute(Actions):

    def compute(self):
        """
        Really the only node that does anything.  Handles the protocol 
        difference between NEW and OLD sessions; calls down to refresh_session()
        for the actual work.
        """
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "compute()"

        # Decide whether we will create a new session or exercise an existing one.
        if  (0 == len(self.state['sessions']) or # no existing sessions
            (0 == randint(0, 1) # we choose to create a new session
                and SESSIONS_MAX > len(self.state['sessions']) + 1)): # ...and we have space

            # Condition:
            # - we're opening a new session
            if DEBUG: print "NEW session"

            # *** NEW SESSION ***
            # CRS -> CB: 4B MAGIC_NEW_SESSION
            # CRS <- CB: 4B (generated) session ID
            # CRS -> CB: 4B session ID | 2B session SZ -- THIS DOESN'T EXIST IN OLD SESSION
            # CRS -> CB: 4B session ID | opcodes (of length session->sz)
            # CRS <- CB: 4B session ID | scratch area (of length SCRATCH_SZ)

            # CRS -> CB: 4B MAGIC_NEW_SESSION
            self.write(struct.pack("<L", MAGIC_NEW_SESSION))

            # CRS <- CB: 4B (generated) session ID
            session_id_idx = len(self.state['sessions'])
            self.state['session_vars'][session_id_idx] = deepcopy(Variable("session%02d" % session_id_idx))

            # Populate the session ID Variable object.
            self.state['session_vars'][session_id_idx].set_slice(0, None)
            self.read(length=4, assign=self.state['session_vars'][session_id_idx])

            # Now that we have the session ID, let's initialize the session.

            # We limit opcode length to avoid forever poll generation.  
            # Opcode length must be a multiple of OPERATION_SZ.
            sz_tmp = randint(16, OPCODE_SZ_UTILIZED)
            sz_tmp = sz_tmp - (sz_tmp % OPERATION_SZ) # floor to nearest multiple

            self.state['sessions'][session_id_idx] = {
                'sz' : sz_tmp, 
                'opcodes' : None,
                'scratch' : ["\x00"] * SCRATCH_SZ
            }

            # CRS -> CB: 4B session ID | 2B session SZ -- THIS STEP DOESN'T EXIST IN OLD SESSION
            self.write(self.state['session_vars'][session_id_idx])
            self.write(struct.pack("<H", self.state['sessions'][session_id_idx]['sz']))

        else: 

            # Condition:
            # - we're using an existing session
            if DEBUG: print "OLD session"

            # *** OLD SESSION ***
            # CRS -> CB: 4B (existing) session ID
            # CRS <- CB: 4B (reflected) session ID
            # CRS -> CB: 4B session ID | opcodes (of length session->sz)
            # CRS <- CB: 4B session ID | scratch area (of length SCRATCH_SZ)

            # CRS -> CB: 4B (existing) session ID
            session_id_idx = choice(self.state['session_vars'].keys())
            self.write(self.state['session_vars'][session_id_idx])

            # CRS <- CB: 4B (reflected) session ID
            # self.read(length=4, expect=session_id) # NOTE: pending DARPA support
            self.read(length=4)

        #### The following is common for both NEW and OLD sessions.

        # We've agreed on the session we will interact with.  
        # Let's give the CB something new to compute.
        self.state['sessions'][session_id_idx] = refresh_session(self.state['sessions'][session_id_idx], DEBUG)

        # CRS -> CB: 4B session ID | opcodes (of length session->sz)
        self.write(self.state['session_vars'][session_id_idx])
        self.write(self.state['sessions'][session_id_idx]['opcodes'])

        # CRS <- CB: 4B session ID | scratch area (of length SCRATCH_SZ)
        # self.read(length=4, expect=session_id) # NOTE: pending DARPA support
        self.read(length=4)
        self.read(length=SCRATCH_SZ, expect=self.state['sessions'][session_id_idx]['scratch'])


    def exit(self):
        """
        Send exit MAGIC as session ID to shut down.
        """
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "exit()"
        
        self.write(struct.pack("<L", MAGIC_EXIT))
        return -1


    def start(self):
        """
        Initialize state.

        We maintain a dict() of sessions:
            key: session ID
            val: (session_sz, opcodes, expected_output) tuple
        """
        self.delay(50)
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "start()"
        self.state['sessions'] = dict()
        self.state['session_vars'] = dict()






