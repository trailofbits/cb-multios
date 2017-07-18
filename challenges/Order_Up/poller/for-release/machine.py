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

from generator.actions import Actions, Variable
from random import choice, randint
from os.path import dirname, abspath, join
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
import support as sp
from common import DEBUG, CONFIG
from orderup import OrderUp
from table import Table, Customer, Order

def recv_status(status):
     return sp.pack_single_string(status)

def recv_uint8(val):
    return sp.pack_single_uint8(val)

def recv_uint16(val):
    return sp.pack_single_uint16(val)

def recv_uint32(val):
    return sp.pack_single_uint32(val)

class OrderUpPoller(Actions):

    CMD_ADD_CUST        = '\xEE\x01\xEE\x01'
    CMD_GET_ORDERS      = '\x01\xEE\x01\xEE'
    CMD_ORDER_UP        = '\x0E\x0E\x0E\x0E'
    CMD_TABLE_STATUS    = '\xBE\xBE\xBE\xBE'
    CMD_QUIT            = '\xB0\x01\xB0\x01'
    CMD_BUS_TABLES      = '\xBB\x11\x11\xBB'

    STATUS_OK                   = '\x04\x04'
    STATUS_ERR                  = '\x44\xEE'
    STATUS_QUIT                 = '\x44\x44'

    def send_cmd(self, cmd):
        self.write(cmd)

    def _make_next_table(self):
        tid = self.state['next_tid']
        self.state['next_tid'] += 1
        ## for testing
        # seats = 5
        ## for release
        seats = ord(self.magic_page[tid]) % CONFIG['MAX_TABLE_SIZE']
        if CONFIG['MIN_TABLE_SIZE'] > seats:
            seats += CONFIG['MIN_TABLE_SIZE']
        return Table(tid=tid, seats=seats, customers=[])

    def _load_tables(self):
        for tid in range(CONFIG['TABLE_CNT']):
            self.state['e'].add_table(self._make_next_table())        


    def start(self):
        #self.delay(100)
        self.state['next_tid'] = 1
        self.state['e'] = OrderUp()
        self._load_tables()

        if DEBUG:
            print "------- start -----------"

    def add_customers(self):
        '''
        A new group of customers arrives at the restaurant.
        '''
        self.send_cmd(self.CMD_ADD_CUST)
        if DEBUG:
            print "cmd: add customer -----------"

        new_customers = self.state['e'].get_next_arriving_customers()

        if DEBUG:
            print " {0} customers to be added.".format(len(new_customers))

        # send customer count
        write_data = sp.pack_single_uint8(len(new_customers))

        # send all customers on new_customers list
        for c in new_customers:
            if DEBUG:
                print " packing customer {0}".format(c.id)
            write_data += sp.pack_single_uint32(c.id)

        self.write(write_data)

        # add all customers on new_customers list to waiting_list
        # try to seat all customers on waiting_list at empty tables
        seated_cnt = self.state['e'].seat_customers(new_customers)

        # recv number of customers seated
        if DEBUG:
            print " {0} seated".format(seated_cnt)

        recv_buf = recv_uint8(seated_cnt)

        recv_buf += recv_status(self.STATUS_OK)
        self.read(length=len(recv_buf), expect=recv_buf)

        return 0

    def table_status(self):
        '''
        Get the status of all tables.
        '''
        self.send_cmd(self.CMD_TABLE_STATUS)
        if DEBUG:
            print "cmd: table status -----------"

        tss = self.state['e'].get_status_of_tables()
        packed = ''
        for t in tss:
            packed += sp.pack_single_uint32(t)
            if DEBUG:
                print " status {0}".format(t)

        recv_buf = packed

        recv_buf += recv_status(self.STATUS_OK)
        self.read(length=len(recv_buf), expect=recv_buf)

        return 0

    def get_orders(self):
        '''
        Get orders from tables with Customers that are ready to order.
        '''
        self.send_cmd(self.CMD_GET_ORDERS)
        if DEBUG:
            print "cmd: get orders -----------"

        orders = self.state['e'].get_orders(self.magic_page)

        # recv order count
        recv_buf = ''
        recv_buf += sp.pack_single_uint8(len(orders))

        if DEBUG:
            print " {0} orders: {1}".format(len(orders), orders)

        if 0 < len(orders):
            packed = self.state['e'].pack_orders(orders)
            # recv orders
            recv_buf += packed

        recv_buf += recv_status(self.STATUS_OK)
        self.read(length=len(recv_buf), expect=recv_buf)

        return 0

    def order_up(self):
        '''
        Deliver completed orders to the relevant Customers.
        '''
        self.send_cmd(self.CMD_ORDER_UP)
        if DEBUG:
            print "cmd: order up -----------"

        orders_taken = self.state['e'].get_ready_orders(count=0) # 0 means all
        order_count = len(orders_taken)

        # send number of orders
        write_buf = ''
        write_buf += sp.pack_single_uint8(order_count)

        # send orders
        if 0 < order_count:
            packed = self.state['e'].pack_orders(orders_taken)
            write_buf += packed

        self.write(write_buf)
        recv_buf = recv_status(self.STATUS_OK)
        self.read(length=len(recv_buf), expect=recv_buf)

        return 0

    def full_meal(self):
        self.add_customers()
        self.get_orders() # app
        self.order_up()
        self.get_orders() # meal
        self.order_up()
        self.get_orders() # des
        self.order_up()

        return 0

    def bus_tables(self):
        '''
        For all tables where customers are finished, clear and reset the table.
        '''
        self.send_cmd(self.CMD_BUS_TABLES)
        if DEBUG:
            print "cmd: bus tables -----------"

        bus_cnt = self.state['e'].bus_finished_tables()
        packed = sp.pack_single_uint8(bus_cnt)
        if DEBUG:
            print " bus count {0}".format(bus_cnt)

        recv_buf = packed

        recv_buf += recv_status(self.STATUS_OK)
        self.read(length=len(recv_buf), expect=recv_buf)

        return 0


    def quit(self):
        '''
        Quit cleanly
        '''
        self.send_cmd(self.CMD_QUIT)
        if DEBUG:
            print "cmd: quit -----------"

        recv_buf = recv_status(self.STATUS_QUIT)
        self.read(length=len(recv_buf), expect=recv_buf)
        return -1

    def broker(self):
        '''
        Branching node for all nodes
        '''
        return 0


