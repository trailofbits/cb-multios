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

import struct
import ctypes

class Pool(object):
    def __init__(self, size):
        self.size = size
        self.freeblks = []
        self.page = 0xb7fff000

    def alloc(self):
        if not self.freeblks:
            self.freeblks = range(self.page, self.page + 0xfff, self.size)
            self.freeblks.pop()
            self.page -= 0x1000

        return self.freeblks.pop()

    def free(self, addr):
        self.freeblks.append(addr)

class Order(object):
    def __init__(self, stock, id_, price, quantity, is_buy):
        self.stock = stock
        self.id_ = id_
        self.price = price
        self.quantity = quantity
        self.is_buy = is_buy

    def __str__(self):
        id_ = ctypes.c_int(self.id_).value
        if self.is_buy:
            return "%s\tBUY\t%s\t%s\t\t\t" % (id_, self.quantity, self.price)
        else:
            return "%s\t\t\t%s\t%s\tSELL" % (id_, self.price, self.quantity)

    def __cmp__(self, other):
        if self.price != other.price:
            return other.price - self.price

        if self.is_buy:
            return (other.id_ & 0xffffffff) - (self.id_ & 0xffffffff)
        else:
            return (self.id_ & 0xffffffff) - (other.id_ & 0xffffffff)

class Stock(object):
    def __init__(self, name, id_):
        self.name = name
        self.id_ = id_
        self.buy_orders = []
        self.sell_orders = []

    def __cmp__(self, other):
        return cmp(self.id_, other.id_)

    def add_order(self, order, orders):
        # Should insert in order, but this is easier
        if order.is_buy:
            for bid in reversed(self.sell_orders):
                if order.price >= bid.price:
                    quantity = min(order.quantity, bid.quantity)

                    order.quantity -= quantity
                    bid.quantity -= quantity

                    if bid.quantity == 0:
                        self.remove_order(bid)
                        orders.remove(bid)

                    if order.quantity == 0:
                        return None

            self.buy_orders.append(order)
            self.buy_orders.sort()
        else:
            for bid in reversed(self.buy_orders):
                if order.price <= bid.price:
                    quantity = min(order.quantity, bid.quantity)

                    order.quantity -= quantity
                    bid.quantity -= quantity

                    if bid.quantity == 0:
                        self.remove_order(bid)
                        orders.remove(bid)

                    if order.quantity == 0:
                        return None

            self.sell_orders.append(order)
            self.sell_orders.sort()

        return order

    def remove_order(self, order):
        if order.is_buy:
            self.buy_orders.remove(order)
        else:
            self.sell_orders.remove(order)

class Support(object):
    def __init__(self):
        self.stocks = []
        self.orders = []
        self.stock_dict = {}
        self.pool = Pool(0x2c)
        self.bad_stocks = set()

    def list_stocks(self):
        return [s.name for s in reversed(self.stocks)]

    def list_orders(self, name):
        stock = self.stock_dict.get(name, None)
        if not stock:
            return None
        return [str(o) for o in stock.sell_orders + stock.buy_orders]

    def place_order(self, name, price, quantity, is_buy):
        stock = self.stock_dict.get(name, None)
        if not stock:
            stock = Stock(name, self.pool.alloc())
            self.stocks.append(stock)
            self.stock_dict[name] = stock

        id_ = self.pool.alloc()
        order = stock.add_order(Order(stock, id_, price, quantity, is_buy), self.orders)
        if not order:
            id_ = 0
        else:
            self.orders.append(order)

        if not stock.buy_orders and not stock.sell_orders:
            self.pool.free(stock.id_)
            self.stocks.remove(stock)
            del self.stock_dict[stock.name]
            return (id_, True)
        else:
            return (id_, False)

    def check_order(self, id_):
        order = next((o for o in self.orders if o.id_ == id_), None)
        if not order:
            return None
        return str(order)

    def cancel_order(self, id_):
        order = next((o for o in self.orders if o.id_ == id_), None)
        if not order:
            return False

        stock = order.stock
        self.orders.remove(order)
        stock.remove_order(order)

        if not stock.buy_orders and not stock.sell_orders:
            self.pool.free(stock.id_)
            self.stocks.remove(stock)
            del self.stock_dict[stock.name]
            return True
        else:
            return False

    def make_list_stocks_cmd(self):
        return '\x00' * 20

    def make_list_orders_cmd(self, name):
        assert(len(name) <= 4)
        name = name + '\x00' * (4 - len(name))
        return '\x01\x00\x00\x00' + name + '\x00' * 12

    def make_place_order_cmd(self, name, price, quantity, is_buy):
        assert(len(name) <= 4)
        name = name + '\x00' * (4 - len(name))
        price = struct.pack("I", price)
        quantity = struct.pack("I", quantity)
        is_buy = '\x00\x00\x00\x00' if is_buy else '\x01\x00\x00\x00'
        return '\x02\x00\x00\x00' + name + is_buy + quantity + price

    def make_check_order_cmd(self, id_):
        return '\x03\x00\x00\x00' + struct.pack("I", id_) + '\x00' * 12

    def make_cancel_order_cmd(self, id_):
        return '\x04\x00\x00\x00' + struct.pack("I", id_) + '\x00' * 12

    def make_quit_cmd(self):
        return '\x05' + '\x00' * 19

