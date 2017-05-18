#!/usr/bin/env python
#
# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
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
from random import choice, randint
from os.path import dirname, abspath, join
import string
import struct
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
from support import Support

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

class FalseProfits(Actions):
    SUCCESS = '\x00' * 4
    FAILURE = '\xff' * 4

    def start(self):
        self.state['model'] = Support()
        self.state['uaf'] = False

    def cmd(self):
        pass

    def list_stocks(self):
        stocks = self.state['model'].list_stocks()

        self.write(self.state['model'].make_list_stocks_cmd())

        # After UAF, this list will be corrupted, so expect failure
        if self.state['uaf']:
            self.read(length=4, expect=self.FAILURE)
        else:
            for s in stocks:
                self.read(delim='\n', expect=s)
            self.read(length=4, expect=self.SUCCESS)

    def list_orders(self):
        pass

    def list_orders_valid(self):
        stocks = self.state['model'].list_stocks()
        if not stocks:
            return

        stock = choice(stocks)
        orders = self.state['model'].list_orders(stock)

        self.write(self.state['model'].make_list_orders_cmd(stock))

        self.read(delim='\n', expect='Order book for %s' % stock)
        self.read(delim='\n', expect='ID\tSIDE\tQTY\tPRICE\tQTY\tSIDE') 
        for o in orders:
            self.read(delim='\n', expect=str(o))
        self.read(length=4, expect=self.SUCCESS)

    def list_orders_invalid(self):
        stocks = self.state['model'].list_stocks()
        stock = random_alpha(1, 4)
        while stock in stocks:
            stock = random_alpha(1, 4)

        self.write(self.state['model'].make_list_orders_cmd(stock))

        self.read(length=4, expect=self.FAILURE)

    def add_order(self):
        pass

    def add_order_existing(self):
        stocks = self.state['model'].list_stocks()
        if not stocks:
            return

        stock = choice(list(stocks))
        price = randint(1, 20) * 100
        quantity = randint(1, 100)
        is_buy = choice((True, False))
        order, removed = self.state['model'].place_order(stock, price, quantity, is_buy)

        self.write(self.state['model'].make_place_order_cmd(stock, price, quantity, is_buy))

        self.read(length=4, expect=struct.pack('I', order))

        # Prevent hitting UAF by force-allocating new stock, only corrupting one list
        if removed:
            self.state['uaf'] = True
            self.add_order_new()

    def add_order_new(self):
        stocks = self.state['model'].list_stocks()
        stock = random_alpha(1, 4)
        while stock in stocks:
            stock = random_alpha(1, 4)

        price = randint(1, 20) * 100
        quantity = randint(1, 100)
        is_buy = choice((True, False))
        order, removed = self.state['model'].place_order(stock, price, quantity, is_buy)
        assert(not removed)

        self.write(self.state['model'].make_place_order_cmd(stock, price, quantity, is_buy))

        self.read(length=4, expect=struct.pack('I', order))

    def check_order(self):
        stocks = self.state['model'].list_stocks()
        if not stocks:
            return

        stock = self.state['model'].stock_dict[choice(stocks)]
        orders = stock.buy_orders + stock.sell_orders
        if not orders:
            return

        order = choice(orders).id_

        self.write(self.state['model'].make_check_order_cmd(order))

        self.read(delim='\n', expect=self.state['model'].check_order(order))
        self.read(length=4, expect=self.SUCCESS)

    def cancel_order(self):
        stocks = self.state['model'].list_stocks()
        if not stocks:
            return

        stock = self.state['model'].stock_dict[choice(stocks)]
        orders = stock.buy_orders + stock.sell_orders
        if not orders:
            return

        order = choice(orders).id_

        removed = self.state['model'].cancel_order(order)

        self.write(self.state['model'].make_cancel_order_cmd(order))

        self.read(length=4, expect=self.SUCCESS)

        # Prevent hitting UAF by force-allocating new stock
        if removed:
            self.state['uaf'] = True
            self.add_order_new()

    def finish(self):
        self.write(self.state['model'].make_quit_cmd())

