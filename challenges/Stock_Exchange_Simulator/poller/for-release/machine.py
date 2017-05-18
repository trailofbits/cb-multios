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

from generator.actions import Actions
import os
import pprint
import sys


sys.path.append(os.path.join(os.path.dirname(__file__), '..', '..','support'))
from gen_accounts import AccountGen, load_generated_accounts, write_pov

import random
import struct

BUY = 0x0
SELL = 0xFF

REQUEST = 0
RESPONSE = 1
QUOTE = 0xDD00

ERR = 0xFFFF
NO_FILL = 0x55
NO_HOLD = 0x66

class TemplateGenerator(Actions):
    def start(self):
        #self.delay(100)
        # we need a steady set of accounts in both the C side and python side.
        # this gets out of the way of any randomness going on here.

        self._accounts = load_generated_accounts()
        self._ct = 0
        self._max_depth = 500
        self._accounts.init_order_book()

    def buy(self):
        if self._ct > self._max_depth:
            return -1
        self._ct += 1
        req, resp, o = self._accounts.generate_good_buy_req_resp()
        self._comment("Buy", o)

        for i, j in self._accounts.order_book[o['symbol']].items():
            self.comment("%s oid %s price %s qty" % ( i,  j['price'], j['qty']))
        self.write(req)
        self.read(length=len(resp), expect=resp)

    def _comment(self, dir, o):
        self.comment("%s %s %s q %s p %s mp %s why? %s" % (dir, o['symbol'], o['acct_id'], o['qty'], o['price'], o.get('match_price', "NA"), o.get('why', "NC") ))
    def sell(self):
        if self._ct > self._max_depth:
            return -1
        self._ct += 1
        req, resp, o = self._accounts.generate_good_sell_req_resp()
        self._comment("Sell", o)
        self.write(req)
        self.read(length=len(resp), expect=resp)



    def quote(self):
        if self._ct > self._max_depth:
            return -1
        self._ct += 1
        random_account = random.choice(self._accounts.accounts)
        sym,  ask = self._accounts.get_random_ask()
        req = self._accounts._gen_quote_req_pkt(random_account, sym)
        self.write(req)
        resp = self._accounts._gen_quote_resp(random_account, sym, ask)
        self.read(expect=resp, length=len(resp))


    def finish(self):
        self.comment('nothing left to test')
        del self._accounts


if __name__ == "__main__":
    a = AccountGen()
    a.generate()
    a.to_c()
    a.to_pkl()
    write_pov(a)
