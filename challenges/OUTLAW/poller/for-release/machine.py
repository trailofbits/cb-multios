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

SZ_MSG = 24 # in bytes, 128 bits
SZ_MSG_BEFORE_GAP = 13
SZ_MSG_GAP = 3
SZ_MSG_AFTER_GAP = 8

SZ_PAGE = 4096
SZ_PRNG_BUF = 8
OFF_ENCKEY_IDX = 42
OFF_AUTH_TOKEN_IDX = 24

SZ_UINT32_T = 4
SZ_UINT8_T = 1

OP_ADD = 0
OP_SUB = 1
OP_MUL = 2
OP_DIV = 3
OP_MOD = 61

DST_CB1 = 3
DST_CB2 = 5
DST_EXIT = 0xdeadbeef

UINT8_MAX = 0xFF
UINT32_MAX = 0xFFFFFFFF
UINT64_MAX = 0xFFFFFFFFFFFFFFFF

def correct(value, bits, signed):
    base = 1 << bits
    value %= base
    return value - base if signed and value.bit_length() == bits else value

int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t = (
    lambda v: correct(v,  8,  True), lambda v: correct(v, 16,  True),
    lambda v: correct(v, 32,  True), lambda v: correct(v, 64,  True),
    lambda v: correct(v,  8, False), lambda v: correct(v, 16, False),
    lambda v: correct(v, 32, False), lambda v: correct(v, 64, False))

CRYPTO_ROUNDS = 42
CRYPTO_DETLA = 0xcafebabe
CRYPTO_SUM = uint32_t(CRYPTO_DETLA * CRYPTO_ROUNDS)

def do_op(req):
    if OP_ADD == req.op:
        answer = uint32_t(req.x + req.y)
    elif OP_SUB == req.op:
        answer = uint32_t(req.x - req.y)
    elif OP_MUL == req.op:
        answer = uint32_t(req.x * req.y)
    elif OP_DIV == req.op:
        if 0 == req.y: answer = 0
        else: answer = uint32_t(req.x / req.y)
    else:
        print "[E] invalid op (%d); this shouldn't happen" % req.op
        return -1
    return answer

def modify_req(req):
    req.x = randint(0, UINT32_MAX)
    req.y = randint(0, UINT32_MAX)
    req.op = choice([OP_ADD, OP_SUB, OP_MUL, OP_DIV])
    return req


class Msg():

    def __init__(self, dst, x, y, op, result):
        self.dst = dst
        self.x = x
        self.y = y
        self.op = op
        self.result = result

    def __str__(self):
        return struct.pack("<LLLBBBBQ", 
            self.dst,
            self.x, 
            self.y, 
            self.op, 
            # We can't match on nmb or pad.
            randint(0, 0xFF), 
            randint(0, 0xFF),
            randint(0, 0xFF), 
            self.result)
    
    def dump(self):
        print "msg:"
        print "  dst .... 0x%08x (%d)" % (self.dst, self.dst)
        print "  x ...... 0x%08x (%d)" % (self.x, self.x)
        print "  y ...... 0x%08x (%d)" % (self.y, self.y)
        print "  op ..... 0x%02x (%d)" % (self.op, self.op)
        # print "  nmb .... 0x%02x (%d)" % (self.nmb, self.nmb)
        print "  result . 0x%016lx (%d)" % (self.result, self.result)


class Outlaw(Actions):

    def _encrypt_block(self, v, k):
        """
        Block size is fixed at 64 bits
        """
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "_encrypt_block()"

        v0 = struct.unpack("<L", v[0:4])[0]
        v1 = struct.unpack("<L", v[4:8])[0]
        delta = CRYPTO_DETLA; _sum = 0
        k0 = struct.unpack("<L", k[ 0: 4])[0]
        k1 = struct.unpack("<L", k[ 4: 8])[0]
        k2 = struct.unpack("<L", k[ 8:12])[0]
        k3 = struct.unpack("<L", k[12:16])[0]

        for i in range(CRYPTO_ROUNDS):
            _sum = uint32_t(_sum + delta)

            tmp0 = uint32_t(uint32_t(v1 << 6) + k0)
            tmp1 = uint32_t(v1 + _sum)
            tmp2 = uint32_t(uint32_t(v1 >> 7) + k1)
            v0 = uint32_t(v0 + uint32_t(tmp0 ^ tmp1 ^ tmp2))

            tmp0 = uint32_t(uint32_t(v0 << 6) + k2)
            tmp1 = uint32_t(v0 + _sum)
            tmp2 = uint32_t(uint32_t(v0 >> 7) + k3)
            v1 = uint32_t(v1 + uint32_t(tmp0 ^ tmp1 ^ tmp2))

        return struct.pack("<LL", v0, v1)

    def _decrypt_block(self, v, k):
        """
        Block size is fixed at 64 bits
        """
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "_decrypt_block()"

        v0 = struct.unpack("<L", v[0:4])[0]
        v1 = struct.unpack("<L", v[4:8])[0]
        delta = CRYPTO_DETLA; _sum = CRYPTO_SUM
        k0 = struct.unpack("<L", k[ 0: 4])[0]
        k1 = struct.unpack("<L", k[ 4: 8])[0]
        k2 = struct.unpack("<L", k[ 8:12])[0]
        k3 = struct.unpack("<L", k[12:16])[0]

        for i in range(CRYPTO_ROUNDS):
            tmp0 = uint32_t(uint32_t(v0 << 6) + k2)
            tmp1 = uint32_t(v0 + _sum)
            tmp2 = uint32_t(uint32_t(v0 >> 7) + k3)
            v1 = uint32_t(v1 - uint32_t(tmp0 ^ tmp1 ^ tmp2))

            tmp0 = uint32_t(uint32_t(v1 << 6) + k0)
            tmp1 = uint32_t(v1 + _sum)
            tmp2 = uint32_t(uint32_t(v1 >> 7) + k1)
            v0 = uint32_t(v0 - uint32_t(tmp0 ^ tmp1 ^ tmp2))

            _sum = uint32_t(_sum - delta)

        return struct.pack("<LL", v0, v1)

    def _prng_refill_cache(self):
        """
        Refill the PRNG cache via prng_buf = decrypt(prng_buf)
        """
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "_prng_refill_cache()"

        if DEBUG:
            msg = 'self.state["prng_buf"] before: 0x'
            for i in range(8):
                msg += "%02x" % struct.unpack("B", self.state["prng_buf"][i])
            print msg

        self.state["prng_buf"] = \
            self._decrypt_block(v=self.state["prng_buf"], k=self.state["prng_key"])

        if DEBUG:
            msg = 'self.state["prng_buf"] after: 0x'
            for i in range(8):
                msg += "%02x" % struct.unpack("B", self.state["prng_buf"][i])
            print msg

        self.state["prng_bytes_remaining"] = SZ_PRNG_BUF

    def _prng_get_bytes(self, count):
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "prng_get_bytes(%d)" % count

        idx_buf = 0
        buf = ""

        while (count):
            while (0 != self.state["prng_bytes_remaining"] and 0 != count):
                buf += self.state["prng_buf"][SZ_PRNG_BUF - self.state["prng_bytes_remaining"]]
                self.state["prng_bytes_remaining"] -= 1
                count -= 1
                idx_buf += 1

            if 0 == self.state["prng_bytes_remaining"]:
                self._prng_refill_cache()

        return buf

    def  _next_expected_dst(self):
        DEBUG = GLOBAL_DEBUG and False
        if DEBUG: print "prng_get_bytes()"

        if DST_CB1 == self.state["expected_dst"]:
            if DEBUG: print "CB1 -> TAP -> CRS / poller (here) -> TAP -> CB2"
            self.state["expected_dst"] = DST_CB2
            return DST_CB2
        elif DST_CB2 == self.state["expected_dst"]:
            if DEBUG: print "CB1 <- TAP <- CRS / poller (here) <- TAP <- CB2"
            self.state["expected_dst"] = DST_CB1
            return DST_CB1
        else:
            print "[E] invalid dst; bailing..."
            return -1

    def mitm(self):
        """
        The node that does all the interesting things.
        """
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "mitm()"

        auth_token_num = struct.unpack("<L", self.state["auth_token"])[0]
        req_dst = self._next_expected_dst()
        resp_dst = self._next_expected_dst()

        # The CLIENT and SERVER have gone about their negotiation; now it's 
        # computation (mitm) time.

        #### Anticipate REQUEST contents from CLIENT
        x = struct.unpack("<L", self._prng_get_bytes(SZ_UINT32_T))[0]
        y = struct.unpack("<L", self._prng_get_bytes(SZ_UINT32_T))[0]
        true_op = struct.unpack("B", self._prng_get_bytes(SZ_UINT8_T))[0]
        if DEBUG: print "true_op = %s" % true_op 
        if OP_MOD == true_op: true_op = OP_ADD
        true_op %= 4
        true_req = Msg(
            dst = req_dst,
            x = x, 
            y = y, 
            op = true_op, 
            result = 0)

        # Read & verify REQUEST from the TAP.
        if DEBUG: true_req.dump()
        self.read(length=SZ_MSG_BEFORE_GAP, expect=str(true_req)[:SZ_MSG_BEFORE_GAP])
        self.read(length=SZ_MSG_GAP) # bury GAP
        self.read(length=SZ_MSG_AFTER_GAP, expect=str(true_req)[-SZ_MSG_AFTER_GAP:])

        # Compute the true RESPONSE.
        true_answer = do_op(true_req)
        if DEBUG: print "true_answer = %d" % true_answer
        true_result_pt = struct.pack("<Q", (uint64_t(true_answer << 32) | auth_token_num))
        true_result_ct = self._encrypt_block(v=true_result_pt, k=self.state["enckey"])
        if DEBUG: print "[D] true_result_pt = 0x%016lx; true_result_ct = 0x%016lx" % \
            (struct.unpack("<Q", true_result_pt)[0], struct.unpack("<Q", true_result_ct)[0])
        true_resp = Msg(
            dst = resp_dst,
            x = 0,
            y = 0,
            op = true_req.op,
            result = struct.unpack("<Q", true_result_ct)[0])

        # Decide if we're going to modify the REQUEST to the SERVER.
        if randint(0, 1):
            # We're not going to modify.  This one is easy.
            if DEBUG: print "[D] passing REQUEST verbatim"
            self.write(str(true_req))
            self.read(length=SZ_MSG_BEFORE_GAP, expect=str(true_resp)[:SZ_MSG_BEFORE_GAP])
            self.read(length=SZ_MSG_GAP) # bury GAP
            self.read(length=SZ_MSG_AFTER_GAP, expect=str(true_resp)[-SZ_MSG_AFTER_GAP:])
            self.write(str(true_resp))

        else:
            # Compute the modified REQUEST.
            mod_req = modify_req(true_req)

            # Compute the modified RESPOSNE.
            mod_answer = do_op(mod_req)
            mod_result_pt = struct.pack("<Q", (uint64_t(mod_answer << 32) | auth_token_num))
            mod_result_ct = self._encrypt_block(v=mod_result_pt, k=self.state["enckey"])
            if DEBUG: print "[D] mod_result_pt = 0x%016lx; mod_result_ct = 0x%016lx" % \
                (struct.unpack("<Q", mod_result_pt)[0], struct.unpack("<Q", mod_result_ct)[0])
            mod_resp = Msg(
                dst = resp_dst,
                x = 0,
                y = 0,
                op = mod_req.op,
                result = struct.unpack("<Q", mod_result_ct)[0])

            if DEBUG: print "[D] REQUEST modified"
            self.write(str(mod_req))
            self.read(length=SZ_MSG_BEFORE_GAP, expect=str(mod_resp)[:SZ_MSG_BEFORE_GAP])
            self.read(length=SZ_MSG_GAP) # bury GAP
            self.read(length=SZ_MSG_AFTER_GAP, expect=str(mod_resp)[-SZ_MSG_AFTER_GAP:])
            self.write(str(true_resp)) # CLIENT still expected true response.

    
    def exit(self):
        """
        Send exit MAGIC as session ID to shut down.
        """
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "exit()"

        # exit() functionality is implemented with a special dst.
        exit_msg = Msg(
            dst = DST_EXIT,
            x = randint(0, UINT32_MAX),
            y = randint(0, UINT32_MAX),
            op = randint(0, UINT8_MAX),
            result = randint(0, UINT64_MAX))

        # First, bury a REQUEST.
        self.read(length=SZ_MSG)

        # Then, write the exit packet to TAP.
        self.write(str(exit_msg))

        # Exit the poller.
        return -1


    def start(self):
        """
        Initialize state for the poller.  
        Effectively emulate the negotiate() functionality of each CB.
        """
        self.delay(50)
        DEBUG = GLOBAL_DEBUG and True
        if DEBUG: print "start()"

        # Get enckey_idx
        enckey_idx = struct.unpack("<L", self.magic_page[OFF_ENCKEY_IDX:OFF_ENCKEY_IDX+4])[0]
        enckey_idx_actual = ((enckey_idx % SZ_PAGE) & ~0xF) & 0xFFFFFFFF;
        if DEBUG: print "enckey_idx = 0x%08x; enckey_idx_actual = 0x%08x" % (enckey_idx, enckey_idx_actual)

        # Get the enckey: a 4-lengthed array of uint32_ts
        self.state["enckey"] = self.magic_page[enckey_idx_actual:enckey_idx_actual+16]
        # NOTE: this doesn't take LE into account
        if DEBUG: 
            print "enckey_idx_actual = 0x%02x, enckey = %s" % (enckey_idx_actual, self.state["enckey"])
            msg = "0x"
            for byte in self.state["enckey"]:
                msg += "%02x" % struct.unpack("B", byte)
            print "enckey (hex) = %s" % msg

        # Get auth_token_idx
        auth_token_idx = struct.unpack("<L", self.magic_page[OFF_AUTH_TOKEN_IDX:OFF_AUTH_TOKEN_IDX+4])[0]
        auth_token_idx_actual = ((auth_token_idx % SZ_PAGE) & ~0xF) & 0xFFFFFFFF;
        if DEBUG: print "auth_token_idx = 0x%08x; auth_token_idx_actual = 0x%08x" % (auth_token_idx, auth_token_idx_actual)

        # Get the auth_token: a single uin32_t
        self.state["auth_token"] = self.magic_page[auth_token_idx_actual:auth_token_idx_actual+4]
        # NOTE: this doesn't take LE into account
        if DEBUG: 
            print "auth_token_idx_actual = 0x%02x, auth_token = %s" % (auth_token_idx_actual, self.state["auth_token"])
            msg = "0x"
            for byte in self.state["auth_token"]:
                msg += "%02x" % struct.unpack("B", byte)
            print "auth_token (hex) = %s" % msg

        # Initialize PRNG buf (static)
        self.state["prng_buf"] = struct.pack("<BBBBBBBB", 
            0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 );
        if DEBUG: 
            print 'self.state["prng_buf"] = %s' % self.state["prng_buf"] 
            msg = "0x"
            for byte in self.state["prng_buf"]:
                msg += "%02x" % struct.unpack("B", byte)
            print 'self.state["prng_buf"] = %s' % msg
        
        # Get PRNG key (based on flag page)
        self.state["prng_key"] = "".join([ 
            self.magic_page[ 2], self.magic_page[ 3], 
            self.magic_page[ 5], self.magic_page[ 7],
            self.magic_page[11], self.magic_page[13],
            self.magic_page[17], self.magic_page[19],
            self.magic_page[23], self.magic_page[29],
            self.magic_page[31], self.magic_page[37],
            self.magic_page[41], self.magic_page[43],
            self.magic_page[53], self.magic_page[59] ] )
        if DEBUG: 
            print 'self.state["prng_key"] = %s' % self.state["prng_key"] 
            msg = "0x"
            for byte in self.state["prng_key"]:
                msg += "%02x" % struct.unpack("B", byte)
            print 'self.state["prng_key"] = %s' % msg

        # We start with an empty PRNG cache.
        self.state["prng_bytes_remaining"] = 0

        # Toggle for expected destination of messages.
        self.state["expected_dst"] = DST_CB1


