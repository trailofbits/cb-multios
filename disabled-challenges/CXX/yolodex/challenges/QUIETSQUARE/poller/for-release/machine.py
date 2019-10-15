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

def is_byte_fragmented(byte):
    return (ord(byte) & 0x80)

# -----------------
# state transitions
# -----------------
# CONNTERM
#   |- OTP (on receipt of PKT_CONNTERM)
#   |- else -> CONNTERM
# OTP
#   |- MSG (on receipt of correct-length packet, any contents)
#   |- else -> OTP
# MSG
#   |- OTP (on reciept of PKT_CONNTERM)
#   |- else -> MSG


class QuietSquare(Actions):

    GLOBAL_DEBUG = False
    GLOBAL_POV = False

    # States
    STATE_CONNTERM = 0
    STATE_OTP = 1
    STATE_MSG = 2

    # Packet lengths
    BUF_RX_SZ = 256
    CONNTERM_SZ = BUF_RX_SZ
    OTP_SZ = 16
    MSG_SZ = BUF_RX_SZ

    # Packet contents
    PKT_INVALID_SZ = "\xFF" + "\xDD" * (BUF_RX_SZ-1)
    PKT_CONNTERM = "\x00" * CONNTERM_SZ
    PKT_CONNTERM_ACK = "\xFF" + "\xCC" * (CONNTERM_SZ-1)
    PKT_CONNTERM_ERR = "\xFF" + "\xFF" * (CONNTERM_SZ-1)
    PKT_OTP_ACK = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
    PKT_EXIT = "\xAA" * 42
    PKT_EXIT_ACK = "\xFF" + "\xAA" * 41

    # Maximum number of recursions before vuln is triggered.
    MAX_DEPTH = 125 # There's an off-by-one here, but it doesn't matter.

    def dispatch(self):
        """
        Dummy node.  Acts as central node for more interesting connterm, otp 
        and msg nodes.
        """
        pass

    def refresh_otp(self):
        """
        A seldom-visited node to refreshes what OTP is.
        """
        DEBUG = True and self.GLOBAL_DEBUG
        if DEBUG:
            print "REFRESH_OTP node"
        self.state["PKT_OTP"] = random_bytes(16, 16)

    def connterm(self):
        """
        This node wants to send a CONNTERM pkt regardless of current CB state.

        Our expectation on this one is simple: all states should behave the 
        same way: advance / revert to STATE_OTP.
        """
        DEBUG = True and self.GLOBAL_DEBUG
        if DEBUG:
            print "CONNTERM node"
        self.write(self.PKT_CONNTERM)

        # We should only expect the CONNTERM ACK if the CB was in CONNTERM state.
        # Initially unintentional, makes protocol slightly more conditional.
        if self.STATE_CONNTERM == self.state["state"]:
            self.read(length=len(self.PKT_CONNTERM_ACK), expect=self.PKT_CONNTERM_ACK)

        # If we're in OTP state already, this would be an invalid size.
        if self.STATE_OTP == self.state["state"]:
            self.read(length=len(self.PKT_INVALID_SZ), expect=self.PKT_INVALID_SZ)

        self.state["state"] = self.STATE_OTP

    def otp(self):
        """
        The node wants to populate the OTP regardless of current CB state.

        Expected response should differ based on state.
        """
        DEBUG = True and self.GLOBAL_DEBUG
        if DEBUG:
            print "OTP node"

        if self.STATE_CONNTERM == self.state["state"]:
            # If the CB is in CONNTERM state, it expects a packet with a length 
            # of CONNTERM_SZ.  Any other size (including OTP_SZ) will result in 
            # PKT_INVALID_SZ.
            if DEBUG: 
                print "send OTP -> CONNTERM state"
            self.write(self.state["PKT_OTP"])
            self.read(length=len(self.PKT_INVALID_SZ), expect=self.PKT_INVALID_SZ)
        elif self.STATE_OTP == self.state["state"]:
            if DEBUG:
                print "send OTP -> OTP state"
            self.write(self.state["PKT_OTP"])
            self.read(length=self.OTP_SZ, expect=self.PKT_OTP_ACK)
            self.state["otp_on_cb"] = self.state["PKT_OTP"]
            self.state["state"] = self.STATE_MSG # advance to MSG state
        elif self.STATE_MSG == self.state["state"]:
            # If the CB is in MSG state, it expects a packet with a length 
            # of MSG_SZ.  Any other size (including OTP_SZ) will result in 
            # PKT_INVALID_SZ.
            if DEBUG:
                print "send OTP -> MSG state"
            self.write(self.state["PKT_OTP"])
            self.read(length=len(self.PKT_INVALID_SZ), expect=self.PKT_INVALID_SZ)
        else:
            print "[E] THIS SHOULD NEVER HAPPEN"

    def msg(self):
        """
        The node wants to send a MSG regardless of current CB state.

        Expected response should differ based on state.
        """
        DEBUG = True and self.GLOBAL_DEBUG
        if DEBUG:
            print "MSG node"

        while True:
            # Start with a bunch of random bytes, expect CB to drop bytes that 
            # have their most signficant bit set and then XOR the remaining 
            # with the OTP (looped over).  

            # This is a simplification of the FRAG protocol, see service.c 
            # for a discussion on implications.
            PKT_MSG = random_bytes(256, 256)

            # Avoid collision with CONNTERM
            if "\x00" == PKT_MSG[0]:
                PKT_MSG = "\x42" + PKT_MSG[1:]

            # We need to make sure don't accidentally trigger the vuln.  The 
            # vuln is triggered when a sufficient depth is reached.  We take a 
            # simplified avoidance approach here and just limit the total 
            # number of recursions. In reality, stack may be unwound in between 
            # recursions.  This check will catch all vuln-triggering messages - 
            # and then some.
            depth = 0
            for byte in PKT_MSG:
                if is_byte_fragmented(byte):
                    depth = depth + 1

            # Re-try based on whether we want to trigger the vuln.
            if not self.GLOBAL_POV and self.MAX_DEPTH < depth:
                if DEBUG:
                    print "MAX_DEPTH exceeded (depth = %d) and we're not making a POV; looping..." % depth
                continue
            if self.GLOBAL_POV and self.MAX_DEPTH >= depth:
                if DEBUG:
                    print "MAX_DEPTH not exceeed (depth = %d) and we're making a POV; looping..." % depth
                continue

            # Cases:
            # 1) We are not making a POV and the depth is less than MAX_DEPTH.
            # 2) We are making a POV and the depth is greater than MAX_DEPTH.
            break

        # If we've broken the above loop, we have a PKT_MSG that will not 
        # trigger the vuln.  Now we must calculate the CB's expected response.

        # If the MSG begins with "\xFF", this is easy. \xFF signifies error 
        # MSG, which the CB will reflect verbatim to us.
        if "\xFF" == PKT_MSG[0]:
            PKT_MSG_RESPONSE = PKT_MSG

        # Otherwise, we have to emulate the CB's actions.
        # First, we drop all bytes that have the fragment bit set.
        else:
            PKT_MSG_RESPONSE = ""
            for byte in PKT_MSG:
                if not is_byte_fragmented(byte):
                    PKT_MSG_RESPONSE += byte

            # Then, we XOR with OTP (on cb), looped over.
            # Yes, everything about this snippet is bad.
            for i in range(len(PKT_MSG_RESPONSE)):
                PKT_MSG_RESPONSE = \
                    PKT_MSG_RESPONSE[:i] + \
                    chr(ord(PKT_MSG_RESPONSE[i]) ^ ord(self.state["otp_on_cb"][i % self.OTP_SZ])) + \
                    PKT_MSG_RESPONSE[i+1:]
        
        if self.STATE_CONNTERM == self.state["state"]:
            if DEBUG: 
                print "send MSG -> CONNTERM state"
            # CONNTERM and MSG packet lengths are the same, but a MSG PKT will 
            # never begin with "\x00", so the two cannot be confused.
            # As such, we should expect PKT_CONNTERM_ERR.
            self.write(PKT_MSG)
            self.read(length=len(self.PKT_CONNTERM_ERR), expect=self.PKT_CONNTERM_ERR)
        elif self.STATE_OTP == self.state["state"]:
            if DEBUG:
                print "send MSG -> OTP state"
            # MSG and OTP packets are different lengths, so we should expect
            # PKT_INVALID_SZ.
            self.write(PKT_MSG)
            self.read(length=len(self.PKT_INVALID_SZ), expect=self.PKT_INVALID_SZ)
        elif self.STATE_MSG == self.state["state"]:
            if DEBUG:
                print "send MSG -> MSG state"
            # The most interesting case. We send a MSG and the CB is in the MSG 
            # state.  Vulns be triggered thar.
            self.write(PKT_MSG)
            self.read(length=len(PKT_MSG_RESPONSE), expect=PKT_MSG_RESPONSE)
        else:
            if DEBUG:
                print "[E] THIS SHOULD NEVER HAPPEN"

    def finish(self):
        """
        Invoke exit functionality, terminating test.

        Must always be last node executed.
        """
        DEBUG = True and self.GLOBAL_DEBUG
        if DEBUG:
            print "exit node"

        self.write(self.PKT_EXIT)
        self.read(length=len(self.PKT_EXIT_ACK), expect=self.PKT_EXIT_ACK)
        return -1

    def start(self):
        """
        Initialize state.
        """
        self.state["PKT_OTP"] = random_bytes(16, 16)
        self.state["otp_on_cb"] = "\x00" * self.OTP_SZ
        self.state["state"] = self.STATE_CONNTERM




