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
from random import choice, randint
from struct import *

instrs = {"trans": 0, "coupon": 1, "stats": 2, "log": 3, "finish": 4, }

resps = {"init": 0, "log": 1, "stats": 2, "done": 3, }

cmds = {"pay": 0, "ticket": 1, "rmticket": 2, "coupon": 3, }


def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))


class OverflowParking(Actions):
    def start(self):
        self.delay(50)
        self.coupons = []
        self.log = []
        self.read(length=260,
                  expect=self._build_resp(resps['init'], "INITSTART"))

    def _build_instr(self, instr, cmd, size, cmdbuf):
        return pack("<III", instr, cmd, size) + cmdbuf + "$"

    def _build_cmd(self, cmd, size, cmdbuf, value):
        self.log.append((cmd, size, value))
        return self._build_instr(instrs['trans'], cmd, size, cmdbuf)

    def _build_resp(self, rtype, text):
        return pack("<I255s", rtype, text)

    def _build_stats_resp(self):

        payments = len([i for i in self.log if i[0] == cmds['pay']])
        tickets = len([i for i in self.log if i[0] == cmds['ticket']])
        coupons = len([i for i in self.log if i[0] == cmds['coupon']])
        gross = sum([i[2] for i in self.log if i[0] != cmds['ticket']])
        expenses = 0
        for i in self.log:
            if i[0] == cmds["pay"]: expenses += i[2] / 2
            if i[0] == cmds["ticket"]: expenses += 1
            if i[0] == cmds["coupon"]:
                coupon = [j for j in self.coupons if j[0] == i[3]]
                if len(coupon) > 0:
                    expenses += coupon[0][1]
        net = gross - expenses
        fmt = "\nPayments made: %08X\nTickets given: %08X\nCoupons used: %08X\nGross revenue: %08X\nOperating costs: %08X\nNet revenue: %08X\n\n"
        #masks make sure we enforce overflow/underflow behavior
        r = fmt % (payments & 0xffffffff, tickets & 0xffffffff, coupons
                   & 0xffffffff, gross & 0xffffffff, expenses & 0xffffffff, net
                   & 0xffffffff)
        return self._build_resp(resps['stats'], r)

    def _build_log_resp(self):
        for i in self.log:
            cmd, length = i[:2]
            msg = "LogMessage - Type:%08x, Size:%08x" % (cmd, length)
            self.read(length=260, expect=self._build_resp(resps['log'], msg))

    def add_valid_payment(self):
        #mask is to avoid "$"
        value = randint(5, 50) & 0xfb
        cmdbuf = pack("<II", randint(0, 0xffffff) & 0xfbfbfbfb, value)
        self.write(self._build_cmd(cmds['pay'], len(cmdbuf) + 1, cmdbuf,
                                   value))

    def add_valid_ticket(self):
        value = randint(5, 255) & 0xfb
        cmdbuf = pack("<II", randint(0, 0xffffff) & 0xfbfbfbfb, value)
        self.write(self._build_cmd(cmds['ticket'], len(cmdbuf) + 1, cmdbuf,
                                   value))

    def add_valid_ticket_payment(self):
        value = randint(5, 255) & 0xfb
        cmdbuf = pack("<II", randint(0, 0xffffff) & 0xfbfbfbfb, value)
        self.write(self._build_cmd(cmds['rmticket'], len(cmdbuf) + 1, cmdbuf,
                                   value))

    def add_valid_coupon_payment(self):
        if randint(0, 1) or len(self.coupons) == 0:
            cid = random_alpha(6, 10)
        else:
            cid = choice(self.coupons)[0]
        value = randint(0, 20)
        cmdbuf = pack("<I127s", value, cid)
        self.write(self._build_cmd(cmds['coupon'], len(cmdbuf) + 1, cmdbuf,
                                   value))
        self.log[-1] = (self.log[-1][0], self.log[-1][1], self.log[-1][2], cid)

    def add_valid_coupon(self):
        cid, value = random_alpha(6, 10), randint(0, 20)
        self.coupons.append((cid, value))
        self.write(self._build_instr(instrs['coupon'], 0, 132, pack(
            "<I127s", value, cid)))

    def get_stats(self):
        self.write(self._build_instr(instrs['stats'], 0, 1, ""))
        self.read(length=260, expect=self._build_stats_resp())

    def get_log(self):
        self.write(self._build_instr(instrs['log'], 0, 1, ""))
        self._build_log_resp()

    def finish(self):
        self.write(self._build_instr(instrs['finish'], 0, 1, ""))
        self.read(length=260, expect=self._build_stats_resp())
        self.read(length=260, expect=self._build_resp(resps['done'], "done."))
        return -1
