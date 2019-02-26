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


import sys
import os
import random
import hashlib

sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'narfpylib.zip'))
from jinja2 import Template

ACCOUNT_C_F = os.path.join(os.path.dirname(__file__), '..', 'src', 'account.c')
ACCOUNT_TMPL = """
#include "libc.h"
#include "account.h"

account_record_t ACCOUNTS[NUM_ACCOUNTS];
void init_account(uint32_t idx, float balance, char *key){
    // unsafe to be called externally
    ACCOUNTS[idx].balance = balance;
	for(int i = 0; i < KEY_LEN; ++i){
		ACCOUNTS[idx].key[i] = key[i];
	}
}
option_holding_t * next_holding(uint32_t acct_id){
	for(int i = 0; i < MAX_HOLDINGS; i++){
		if(ACCOUNTS[acct_id].holdings[i].symbol[0] == 0x0)
			return &(ACCOUNTS[acct_id].holdings[i]);
	}
	return NULL;
}
void init_holding(uint32_t acct_id, uint32_t holding_idx, char *sym, uint32_t qty){
	option_holding_t *t = &(ACCOUNTS[acct_id].holdings[holding_idx]);
	t->qty = qty;
	memcpy(sym, t->symbol, strlen(sym));


}
void init_accounts(){
		{% for acct in accounts %}
			init_account({{ acct.idx }}, {{ acct.balance }}, "{{ acct.key }}" );


		{% endfor %}
		{% for acct_idx, holding_idx, sym, qty in holdings %}
			init_holding({{ acct_idx }}, {{ holding_idx }}, "{{ sym }}", {{ qty }});
		{% endfor %}

}
"""

BUY = 0x0
SELL = 0xFF

REQUEST = 0
RESPONSE = 1
QUOTE = 0xDD00

ERR = 0xFFFF
NO_FILL = 0x55
NO_HOLD = 0x66
ORDERFILL=0xFF0000
NO_MATCH = 0x88
SELL_ADD = 0x99

import struct

SYMS = ['AAPL', 'GOOG', 'NRFIN', "CROMU", "KPRCA", "PIRATE", "DDTEK", "OAK", "MAPLE", "PALM", "SK3WL"]
BAD_SYMS = ["DDTEK", "SK3WL", "PALM"]
GOOD_SYMS = filter(lambda x: x not in BAD_SYMS, SYMS)

class Account(object):
    MAX_SHARES = 2**24
    MIN_SHARES = 10**6

    def __init__(self, idx, balance, key):
        self.balance = balance
        self.idx = idx
        self.key = key
        self.holdings = {}
        self.symbols = SYMS

    def dec_balance(self, amount):
        self.balance -= amount

    def inc_balance(self, amount):
        self.balance += amount

    def dec_holdings(self, sym, qty):
        qt = self.holdings[sym]
        qt = qt - qty
        assert(qt >= 0)
        if qt == 0:
            del self.holdings[sym]

    def inc_holdings(self, sym, qty):
        self.holdings[sym] = self.holdings.get(sym, 0) + qty


    def generate_holdings(self):
        for sym in SYMS:
            self.holdings[sym] = random.randint(self.MIN_SHARES, self.MAX_SHARES)


        s = random.choice(BAD_SYMS)
        self.holdings[s] = 0xFFFFFFFF

    def get_holdings(self):
        l = []
        for r, kv in zip(range(0, len(self.holdings)), self.holdings.items()):
            k, v = kv
            l.append((self.idx, r, k, v))
        return l

    @property
    def random_holding(self):
        return random.choice(filter(lambda x: x[0] not in BAD_SYMS and x[1] > 0, self.holdings.items()))

import pickle

PKL_FILE = os.path.join(os.path.dirname(__file__), 'accounts.pkl')


def load_generated_accounts():
    with open(PKL_FILE, 'r') as f:
        return pickle.load(f)



class AccountGen(object):
    MAX_BAL_MULT = 10 ** 6
    MAX_ORDER_SZ = 1000
    sym_size = 8
    key_len = 32
    def to_pkl(self):
        with open(PKL_FILE, 'w') as f:
            return pickle.dump(self, f)

    def __init__(self, num_accounts=100):
        self.order_id = 0
        self.num_accounts = num_accounts
        self.accounts = {}
        self.order_book = {
        }
    def init_order_book(self):

        for sym in SYMS:
            self.order_book[sym] = {}
    @property
    def accts_with_money(self):
        return filter(lambda x: x.balance > self.MAX_ORDER_SZ, self.accounts.values())

    @property
    def random_acct_with_money(self):
        return random.choice(self.accts_with_money)

    @property
    def accounts_with_holding(self):
        return filter(lambda x: len(x.get_holdings()) > 0, self.accounts.values())

    @property
    def random_account_with_holding(self):
        return random.choice(self.accounts_with_holding)

    @property
    def account_with_bad_holding(self):

        accounts = []
        for a in self.accounts.values():

            badness = filter(lambda x: x[0] in BAD_SYMS and x[1] == 0xFFFFFFFF,  a.holdings.items())
            if badness:
                accounts.append((a, dict(badness)))
        return accounts



    @property
    def account_with_bad_holding_sym_only(self):
        for a in self.accounts.values():
            badness = filter(lambda x: x[0] in BAD_SYMS and x[1] < 0xFFFFFFFF,  a.holdings.items())
            if badness:
                return a, dict(badness)
        raise Exception("No holdings can overflow")

    @property
    def random_symbol_to_buy(self):
        return random.choice(GOOD_SYMS)

    def get_oid_sorted_orders_for(self,sym):

        return sorted(self.order_book.get(sym, {}).keys())

    def get_order_on_book(self, symbol, oid):
        return self.order_book[symbol][oid]

    def add_to_order_book(self, order):

        order['order_id'] = self.order_id

        self.order_id += 1
        self.order_book[order['symbol']][order['order_id']] = order

    def will_match_sell_order_and_fill(self, buy_order):
        sel_oids  = self.get_oid_sorted_orders_for(buy_order['symbol'])
        if not sel_oids:
            buy_order['why'] = 'no sell ids'
            return None
        w = 'no internal match'
        for sell_oid in sel_oids:
            sell_order = self.get_order_on_book(buy_order['symbol'], sell_oid)

            if buy_order['price'] >= sell_order['price']:

                if sell_order['qty'] >= buy_order['qty']:

                    return sell_order
                else:

                    w = 'qty too low %d' % sell_order['qty']
            else:
                w = 'price too high'

        buy_order['why'] = w
        return None

    def generate_good_buy_req_resp(self):
        acct_to_buy_with = self.random_acct_with_money
        # assume all orders on order book must be prepaid
        sym_to_buy = self.random_symbol_to_buy
        assert(sym_to_buy not in BAD_SYMS)
        # now size order such that its under the max order size
        qty_avail = self.order_book.get(sym_to_buy, 0)
        qty = random.randint(1,99)


        price = float(random.randint(1, 10.0))

        buy_price = price * qty
        assert(buy_price < self.MAX_ORDER_SZ)
        assert(acct_to_buy_with.balance > buy_price)

        o = {
            'qty': qty,
            'symbol' : sym_to_buy,
            'price' : price,
            'acct_id' : acct_to_buy_with.idx
        }
        req = self._gen_order_pkt(acct_to_buy_with, o, BUY)

        sell_match = self.will_match_sell_order_and_fill(o)
        if sell_match:
            resp = self._gen_good_order_resp(BUY, acct_to_buy_with, o)


            self.proc_order_match(o, sell_match, sell_match['price'], sym_to_buy, qty)
            o['match_price'] = sell_match['price']
            # todo make sure we do same error on other side
            if sell_match['qty'] == 0:
                o['why'] = "order fill"
                resp = self._gen_bad_order_resp(acct_to_buy_with, code=ORDERFILL)
        else:

            resp = self._gen_bad_order_resp(acct_to_buy_with, code=NO_MATCH)
        return req, resp, o

    def proc_order_match(self, buy_order, sell_order, final_price, sym, qty):
        self.accounts[buy_order['acct_id']].dec_balance(final_price*qty)
        self.accounts[sell_order['acct_id']].inc_balance(final_price * qty)
        self.accounts[buy_order['acct_id']].inc_holdings(sym, qty)
        self.accounts[sell_order['acct_id']].dec_holdings(sym, qty)

        new_sell_qty = sell_order['qty'] - qty
        sell_order['qty'] = new_sell_qty
        if new_sell_qty == 0:
            # print "Zeroed out %s" % sym
            del self.order_book[sym][sell_order['order_id']]
        else:

            self.order_book[sym][sell_order['order_id']] = sell_order

    def get_random_ask(self):
        sym = self.random_symbol_to_buy
        return sym, self.get_ask(sym)

    def get_ask(self, sym):
        for k in self.get_oid_sorted_orders_for(sym):
            obe = self.get_order_on_book(sym, k)
            return obe['price']
        return 0.0

    def generate_good_sell_req_resp(self):
        acct_to_sell_with = self.random_account_with_holding
        sym_to_sell, qty_avail = acct_to_sell_with.random_holding
        assert(sym_to_sell not in BAD_SYMS)

        price = float(random.randint(1, 10.0))
        mx_qty = int((self.MAX_ORDER_SZ-1) / price)
        qty = random.randint(1, mx_qty)

        sell_price = qty * price

        assert(sell_price < self.MAX_ORDER_SZ)
        assert(acct_to_sell_with.balance > sell_price)




        o = {
            'qty': qty,
            'symbol': sym_to_sell,
            'price' : price,
            'acct_id': acct_to_sell_with.idx

        }
        self.add_to_order_book(o)
        req = self._gen_order_pkt(acct_to_sell_with, o, SELL)

        resp = self._gen_bad_order_resp(acct_to_sell_with, code=SELL_ADD)
        return req, resp, o

    def sign_order(self, acct_id, order):
        b = bytearray()
        # clear first jic

        sym_pack = struct.pack('%ds' % self.sym_size, order['symbol'])
        b += sym_pack
        # remember to add symback at end too

        acct_pack = struct.pack('I', order['acct_id'])
        qty_pack = struct.pack('I', order['qty'])
        b += qty_pack
        b += acct_pack
        chk = acct_id * 2 + order['qty'];

        chk_pack = struct.pack('I', chk)
        b += chk_pack

        b += struct.pack('4s', self.accounts[acct_id].key[:4])

        b += struct.pack('8s', order['symbol'])

        k = bytearray(self.accounts[acct_id].key)
        final = bytearray([0x0] * self.key_len)

        assert (len(b) == len(k))
        for r in range(0, len(k)):
            b[r]
            k[r]
            final[r] = b[r] ^ k[r]

        return str(final)

    def _gen_regular_req_pkt(self, rt, ot, account, datal=0, bank_id=0):
        return struct.pack('IIIII', rt, ot, account.idx, datal, bank_id)

    def _gen_order_ds(self, order):
        return struct.pack('fI8s32s', order['price'], order['qty'], order['symbol'],
                           self.sign_order(order['acct_id'], order))

    def _gen_order_pkt(self, acct, order, direction, datal=0):
        assert(direction in [BUY, SELL])
        return self._gen_regular_req_pkt(REQUEST, direction, acct, datal=datal) + self._gen_order_ds(order)

    def _gen_quote_data(self, sym, ask=0.0):
        return struct.pack('f8s', ask, sym)

    def _gen_quote_req_pkt(self, acct, sym):
        return self._gen_regular_req_pkt(REQUEST, QUOTE, acct) + self._gen_quote_data(sym)

    def _gen_quote_resp(self, acct, sym, ask):
        return self._gen_regular_req_pkt(RESPONSE, QUOTE, acct) + self._gen_quote_data(sym,  ask=ask)

    def _gen_good_order_resp(self, ot, account, order):
        return self._gen_regular_req_pkt(RESPONSE, ot, account) + struct.pack("8sI", order['symbol'], order['qty'])

    def _gen_bad_order_resp(self, account, code=NO_FILL):
        return self._gen_regular_req_pkt(RESPONSE, ERR, account) + struct.pack("I", code)


    def generate(self):
        for r in range(0, self.num_accounts):
            balance = float(random.randint(10000, 10**6))
            k = hashlib.md5("%d%s" % (r, balance)).hexdigest()
            a = Account(r, balance, k)
            a.generate_holdings()
            self.accounts[r] = a

    def to_c(self):

        t = Template(ACCOUNT_TMPL)
        hlds = [a.get_holdings() for a in self.accounts.values()]
        flat_holdings = []

        map(flat_holdings.extend, hlds)
        rendered_s = t.render(accounts=self.accounts.values(), holdings=flat_holdings)
        with open(ACCOUNT_C_F, 'w') as f:
            f.write(rendered_s)




from generator.actions import Actions, Variable




BUY = 0x0
SELL = 0xFF

REQUEST = 0
RESPONSE = 1
QUOTE = 0xDD00

ERR = 0xFFFF
NO_FILL = 0x55
NO_HOLD = 0x66

class TemplateGenerator(Actions):
    p_hdr_sz = 16
    def start(self, accts):
        self._accounts = accts

    def gengen(self):
        self.comment("CLIP ABOVE")
        accts = self._accounts.account_with_bad_holding
        buy_acct, bad_hold_dict = accts.pop()
        sym = None
        for a, bhd in accts:

            sym = set(bad_hold_dict.keys()).intersection(bhd.keys())
            if(len(sym) > 0):

                sym = list(sym)[0]
                sell_acct, sell_hold_bad = a, bhd
                break
        assert(sym is not None)
        o = {
            'price' : 0.00001,
            'qty' : 200,
            'symbol' : sym,
            'acct_id' : sell_acct.idx
        }


        sell_order_pkt = self._accounts._gen_order_pkt(sell_acct, o, SELL)
        # address to read goes here
        assert(len(sell_order_pkt) == 24-4+48)
        self.comment("Using sell acct id %s with key %s" % (sell_acct.idx, sell_acct.key))

        self.write(sell_order_pkt)

        sell_resp =self._accounts._gen_bad_order_resp(sell_acct, code=0x99)

        self.read(length=len(sell_resp), expect=sell_resp)


        # all should be buy account below here
        so = {
            'qty': 10,
            'acct_id': buy_acct.idx,
            'price': 1.0,
            'symbol': sym
        }

        self.comment("Using buy acct id %s with key %s" % (buy_acct.idx, buy_acct.key))
        start_frag = struct.pack("III", REQUEST, BUY, buy_acct.idx)
        self.write(start_frag)
        self.comment("Length of read here")
        rlen = struct.pack("I", 0)
        self.write(rlen)
        self.comment("Read location here")
        r = struct.pack("I", 0)
        self.write(r)

        # 5B above here
        assert(len(r)+len(start_frag) + len(rlen)  == 20)
        order_only = self._accounts._gen_order_ds(so)
        self.write(order_only)
        print "Order len %d" % len(order_only)
        assert(len(order_only) == 8 + 32 + 4 + 4)
        assert(len(r+start_frag+rlen) + len(order_only) == 24-4+48)
        pre = start_frag + rlen + r
        self.read(length=20, expect=pre)
        self.comment("Manual t2 variable reading goes here...")
        self.comment("CLIP BELOW")
        
TMPL="""<?xml version="1.0" standalone="no" ?>
<!DOCTYPE cfepov SYSTEM "/usr/share/cgc-docs/cfe-pov.dtd">
<cfepov>
<cbid>service</cbid>
<replay>
    <negotiate><type2 /></negotiate>
    {{ var_replace }}
    <read>
       <length>48</length>
       <assign>
          <var>TYPE2_VALUE</var>
          <slice />
       </assign>
    </read>
    <submit><var>TYPE2_VALUE</var></submit>

</replay>
</cfepov>
"""
from jinja2 import Template
POV_PATH=os.path.join(os.path.dirname(__file__), '..','pov', 'POV_00001.povxml')
def write_pov(accts):
    tg = TemplateGenerator()
    tg.start(accts)
    tg.gengen()
    x = tg.xml()
    xml_lines = x.split("\n")
    xml_body = xml_lines[6:-3]
    xml_body[xml_body.index(filter(lambda x: x.endswith('<!-- Length of read here -->'), xml_body)[0])+1] = "\t<write><var>TYPE2_SIZE</var></write>"
    xml_body[xml_body.index(filter(lambda x: x.endswith('<!-- Read location here -->'), xml_body)[0])+1] = "\t<write><var>TYPE2_ADDR</var></write>"


    fixed_xml = "\n".join(xml_body)
    t = Template(TMPL)
    rendered_s = t.render(var_replace=fixed_xml)

    with open(POV_PATH, 'w') as f:
        f.write(rendered_s)
