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
from random import randint

import support as sp
from common import DEBUG, CONFIG
from menu import FOOD_TYPE


TABLE_STATUS = {
    'VACANT':       0,
    'APP_RTO':      1,
    'APP_WAIT':     2,
    'MEAL_RTO':     3,
    'MEAL_WAIT':    4,
    'DES_RTO':      5,
    'DES_WAIT':     6,
    'FINISHED':     7,
}

class Table:
    def __init__(self, tid=0, status='VACANT', seats=0, customers=[]):
        self.id = tid
        self.status = TABLE_STATUS[status]
        self.seats = seats
        self.customers = customers

        if 0 == self.seats:
            self.seats = randint(1, CONFIG['MAX_TABLE_SIZE'])

    def add_customer(self, customer):
        self.customers.append(customer)

    def add_customers(self, customers):
        if DEBUG:
            print " table {0}: initial customers: {1}".format(self.id, self.customers)
        if DEBUG:
            print " table {0}: customers to add: {1}".format(self.id, customers)

        for c in customers:
            self.add_customer(c)
            if DEBUG:
                print " table {0}: added customer: {1}\n".format(self.id, c.id)

        if DEBUG:
            print " table {0}: updated customers: {1}".format(self.id, self.customers)

        self.status += 1
        if DEBUG:
            print " new table status {0}".format(self.status)

    def is_vacant(self):
        res = TABLE_STATUS['VACANT'] == self.status
        if DEBUG:
            print " table {0} is {1}vacant".format(self.id, "" if True == res else "not ")
        return res

    def is_finished(self):
        res = TABLE_STATUS['FINISHED'] == self.status
        if DEBUG:
            print " table {0} is {1}finished".format(self.id, "" if True == res else "not ")
        return res

    def get_food_item(self, c_id, magic_page, ftype, menu):
        idx = (c_id * c_id) % 4096
        idx = ord(magic_page[idx])

        food = None
        if ftype == FOOD_TYPE['APP_TYPE']:
            app = menu.appetizers
            food = app[idx % len(app)]
        elif ftype == FOOD_TYPE['MEAL_TYPE']:
            meal = menu.meals
            food = meal[idx % len(meal)]
        elif ftype == FOOD_TYPE['DES_TYPE']:
            des = menu.desserts
            food = des[idx % len(des)]
        else:
            foood = None

        return food

    def get_order_ftype_from_status(self):
        ftype = -1
        if TABLE_STATUS['APP_RTO'] == self.status:
            ftype = FOOD_TYPE['APP_TYPE']
        elif TABLE_STATUS['MEAL_RTO'] == self.status:
            ftype = FOOD_TYPE['MEAL_TYPE']
        elif TABLE_STATUS['DES_RTO'] == self.status:
            ftype = FOOD_TYPE['DES_TYPE']
        else:
            ftype = -1

        return ftype

    def get_deliver_ftype_from_status(self):
        ftype = -1
        if TABLE_STATUS['APP_WAIT'] == self.status:
            ftype = FOOD_TYPE['APP_TYPE']
        elif TABLE_STATUS['MEAL_WAIT'] == self.status:
            ftype = FOOD_TYPE['MEAL_TYPE']
        elif TABLE_STATUS['DES_WAIT'] == self.status:
            ftype = FOOD_TYPE['DES_TYPE']
        else:
            ftype = -1

        return ftype

    def get_customer_orders(self, magic_page, menu, pov=False):
        orders = []
        if True == pov:
            self.status = TABLE_STATUS['MEAL_RTO']

        if self.status == TABLE_STATUS['APP_RTO'] or \
            self.status == TABLE_STATUS['MEAL_RTO'] or \
            self.status == TABLE_STATUS['DES_RTO']:

            ftype = self.get_order_ftype_from_status()
            if -1 != ftype:
                if DEBUG:
                    print " table {0} currently seated customers: {1}".format(self.id, self.customers)
                for c in self.customers:
                    if DEBUG:
                        print " table {0} getting order for customer: {1}".format(self.id, c.id)
                    food = self.get_food_item(c.id, magic_page, ftype, menu)
                    orders.append(Order(self.id, c.id, ftype, food))

                self.status += 1
                if DEBUG:
                    print " table {0} new table status {1}".format(self.id, self.status)
        else:
            if DEBUG:
                print " table {0} status not RTO {1} not in [{2}|{3}|{4}]".format(self.id, self.status, TABLE_STATUS['APP_RTO'], TABLE_STATUS['MEAL_RTO'], TABLE_STATUS['DES_RTO'])
        return orders

    def get_customer_by_id(self, c_id):
        for c in self.customers:
            if c.id == c_id:
                return c
        return None


    def deliver_customer_orders(self, orders):
        if self.status == TABLE_STATUS['APP_WAIT'] or \
            self.status == TABLE_STATUS['MEAL_WAIT'] or \
            self.status == TABLE_STATUS['DES_WAIT']:

            ftype = self.get_deliver_ftype_from_status()
            if -1 != ftype:
                if DEBUG:
                    print " table {0} currently seated customers: {1}".format(self.id, self.customers)
                for o in orders:
                    c = self.get_customer_by_id(o.cid)
                    if DEBUG:
                        print " table {0} delivering item to customer: {1}".format(self.id, c.id)
                    c.accept_food(o.fitem)

                self.status += 1
                if DEBUG:
                    print " table {0} new table status {1}".format(self.id, self.status)
        else:
            if DEBUG:
                print " table {0} status not WAIT {1} not in [{2}|{3}|{4}]".format(self.id, self.status, TABLE_STATUS['APP_WAIT'], TABLE_STATUS['MEAL_WAIT'], TABLE_STATUS['DES_WAIT'])

    def bus_table(self):
        del(self.customers)
        self.customers = []
        self.status = TABLE_STATUS['VACANT']


    def __str__(self):
        return "(id: {0}, status: {1}, seats: {2} customers: {3})".format(self.id,
                                                                        self.status,
                                                                        self.seats,
                                                                        self.customers)
    def __repr__(self):
        return self.__str__()

class Customer:
    def __init__(self, cid=0, appetizer=None, meal=None, dessert=None):
        self.id = cid
        self.appetizer = appetizer
        self.meal = meal
        self.dessert = dessert

    def accept_food(self, fitem):
        ftype = fitem.ftype
        if ftype == FOOD_TYPE['APP_TYPE']:
            self.appetizer = fitem
        elif ftype == FOOD_TYPE['MEAL_TYPE']:
            self.meal = fitem
        elif ftype == FOOD_TYPE['DES_TYPE']:
            self.dessert = fitem

    def __str__(self):
        return "(cid: {0}, app: {1}, meal: {2}, des: {3})".format(self.id, self.appetizer, self.meal, self.dessert)

    def __repr__(self):
        return self.__str__()


class Order:
    def __init__(self, tid=0, cid=0, ftype='APP_TYPE', fitem=None):
        self.tid = tid
        self.cid = cid
        self.ftype = ftype
        self.fitem = fitem

    def __str__(self):
        return "(tid: {0}, cid: {1}, ftype: {2}, fitem: {3})".format(self.tid, self.cid, self.ftype, self.fitem)

    def __repr__(self):
        return self.__str__()
        