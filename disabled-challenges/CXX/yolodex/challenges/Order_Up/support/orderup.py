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
# from random import choice
from random import choice, randint

import support as sp
from common import DEBUG, CONFIG

import menu as m
import table as t
import todays_menu as tm

class OrderUp(object):
    def __init__(self):
        self.menu = tm.get_initial_menu()
        self.tables = []
        self.waiting_list = []
        self.orders_taken = []
        self.next_cid = 0

    def add_table(self, table):
        self.tables.append(table)

    def get_next_arriving_customers(self):
        new_customers = []
        # prevent waiting_list size counter overflow (uint8)
        if len(self.waiting_list) < (255 - CONFIG['MAX_TABLE_SIZE']):
            # make some new customers (1 - MAX_TABLE_SIZE)
            # and add to new_customers list
            for c in range(randint(0, CONFIG['MAX_TABLE_SIZE'])):
                new_customers.append(t.Customer(self.next_cid))
                self.next_cid += 1
                self.next_cid %= 256

        return new_customers

    def add_customers_to_table(self, tid, customers):
        self.tables[tid-1].add_customers(customers)

    def add_customers_to_waiting_list(self, customers):
        if DEBUG:
            print " cur waiting_list: {0}".format(self.waiting_list)
        self.waiting_list += customers
        if DEBUG:
            print " updated waiting_list: {0}".format(self.waiting_list)

    def get_next_customer_from_waiting_list(self):
        if [] == self.waiting_list:
            if DEBUG:
                print " waiting list is empty"
            return None
        return self.waiting_list.pop(0)

    def get_next_vacant_table(self):
        for t in self.tables:
            if True == t.is_vacant():
                return t
        if DEBUG:
            print " no vacant tables"

        return None 

    def seat_customers(self, new_customers):
        self.add_customers_to_waiting_list(new_customers)

        seated = 0

        while [] != self.waiting_list:
            t = self.get_next_vacant_table()
            if None == t:
                break

            seats = t.seats
            if DEBUG:
                print " table {0} has {1} seats".format(t.id, t.seats)
                print " currently seated customers: {0}".format(t.customers)

            to_seat = []
            for s in range(seats):
                if DEBUG:
                    print " getting customer from waiting_list"
                c = self.get_next_customer_from_waiting_list()
                if None == c:
                    if DEBUG:
                        print " waiting_list is empty"
                    break
                if DEBUG:
                    print " selected customer {0}".format(c.id)

                to_seat.append(c)
            self.add_customers_to_table(t.id, to_seat)
            seated += len(to_seat)

        return seated

    def get_status_of_tables(self):
        return [t.status for t in self.tables]

    def get_orders(self, magic_page, pov=False):
        orders = []
        for t in self.tables:
            orders += t.get_customer_orders(magic_page, self.menu, pov)

        self.orders_taken += orders
        return orders

    def _pad_and_pack_str(self, aStr, full_len):
        pad_byte = CONFIG['STR_PAD_BYTE']
        padding = ''
        if len(aStr) < full_len:
            padding += ''.join(pad_byte for _ in range(full_len - len(aStr)))
        return sp.pack_single_string("{0}{1}".format(aStr, padding))

    def pack_orders(self, orders):
        packed = ''

        if [] == orders:
            return packed

        # for each order
        for o in orders:
            #  table id
            packed += sp.pack_single_uint32(o.tid)
            #  customer id
            packed += sp.pack_single_uint32(o.cid)
            #  ftype
            packed += sp.pack_single_uint32(o.ftype)
            #  food details

            food = o.fitem
            if o.ftype == m.FOOD_TYPE['APP_TYPE']:
                packed += self._pad_and_pack_str(food.name, CONFIG['APP_NAME_SZ'])
            elif o.ftype == m.FOOD_TYPE['MEAL_TYPE']:
                packed += self._pad_and_pack_str(food.name, CONFIG['MEAL_NAME_SZ'])
                packed += self._pad_and_pack_str(food.main, CONFIG['MEAL_MAIN_SZ'])
                packed += self._pad_and_pack_str(food.veggie, CONFIG['MEAL_VEG_SZ'])
                packed += self._pad_and_pack_str(food.side, CONFIG['MEAL_SIDE_SZ'])
            elif o.ftype == m.FOOD_TYPE['DES_TYPE']:
                packed += self._pad_and_pack_str(food.name, CONFIG['DES_NAME_SZ'])

        return packed

    def pack_orders_tuples(self, orders):
        packed = []

        if [] == orders:
            return packed

        # for each order
        for o in orders:
            #  table id
            p_tid = sp.pack_single_uint32(o.tid)
            #  customer id
            p_cid = sp.pack_single_uint32(o.cid)
            #  ftype
            p_ft = sp.pack_single_uint32(o.ftype)
            #  food details

            food = o.fitem
            p_fi = ''
            if o.ftype == m.FOOD_TYPE['APP_TYPE']:
                p_fi += self._pad_and_pack_str(food.name, CONFIG['APP_NAME_SZ'])
            elif o.ftype == m.FOOD_TYPE['MEAL_TYPE']:
                p_fi += self._pad_and_pack_str(food.name, CONFIG['MEAL_NAME_SZ'])
                p_fi += self._pad_and_pack_str(food.main, CONFIG['MEAL_MAIN_SZ'])
                p_fi += self._pad_and_pack_str(food.veggie, CONFIG['MEAL_VEG_SZ'])
                p_fi += self._pad_and_pack_str(food.side, CONFIG['MEAL_SIDE_SZ'])
            elif o.ftype == m.FOOD_TYPE['DES_TYPE']:
                p_fi += self._pad_and_pack_str(food.name, CONFIG['DES_NAME_SZ'])

            packed.append( (p_tid, p_cid, p_ft, p_fi) )

        return packed


    def deliver_orders(self, order_list):
        t_orders = [[] for t in self.tables]
        for o in order_list:
            t_orders[o.tid - 1].append(o)

        for t in self.tables:
            t.deliver_customer_orders(t_orders[t.id - 1])

    def get_ready_orders(self, count=0):
        ot = []
        if 0 == count:
            for _ in range(len(self.orders_taken)):
                ot.append(self.orders_taken.pop())
        else:
            for _ in range(count):
                ot.append(self.orders_taken.pop())

        if [] != ot:
            self.deliver_orders(ot)
        return ot

    def bus_finished_tables(self):
        bus_count = 0
        for t in self.tables:
            if True == t.is_finished():
                t.bus_table()
                bus_count += 1

        return bus_count

