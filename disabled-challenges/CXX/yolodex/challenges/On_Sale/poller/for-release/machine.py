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
from onsale import OnSale

class OnSalePoller(Actions):

    CMD_BUY            = '\xBE\x0E\xBE\x0E'
    CMD_CHECK          = '\xC4\xEC\x4E\xEE'
    CMD_ADD            = '\xAD\xDD\xAD\xDD'
    CMD_RM             = '\xDE\xAD\xDE\xAD'
    CMD_UPDATE         = '\x04\xD4\x7E\x00'
    CMD_ONSALE         = '\x54\x13\x54\x13'
    CMD_NOSALE         = '\x0F\x0F\x0F\x0F'
    CMD_LIST           = '\x11\x44\x11\x44'
    CMD_QUIT           = '\xFF\xFF\xFF\xFF'


    STATUS_OK                   = ''
    STATUS_ERR                  = ''
    STATUS_QUIT                 = ''

    def compute_status_codes(self):
        ok = [0, 0]
        err = [0, 0]
        quit = [0, 0]

        idx = 0
        while idx < 4094:
            ok[idx % 2]         ^= ord(self.magic_page[idx])
            err[(idx + 1) % 2]  ^= ord(self.magic_page[idx + 1])
            quit[(idx + 2) % 2] ^= ord(self.magic_page[idx + 2])
            idx += 3

        self.STATUS_OK      = ''.join([chr(c) for c in ok])
        self.STATUS_ERR     = ''.join([chr(c) for c in err])
        self.STATUS_QUIT    = ''.join([chr(c) for c in quit])

    def send_cmd(self, cmd):
        self.write(cmd)

    def recv_status(self, status):
        self.read(length=2, expect=sp.pack_single_string(status))

    def recv_uint16(self, val, match=True):
        if True == match:
            self.read(length=2, expect=sp.pack_single_uint16(val))
        else:
            self.read(length=2)

    def recv_uint32(self, val, match=True):
        if True == match:
            self.read(length=4, expect=sp.pack_single_uint32(val))
        else:
            self.read(length=4)

    def recv_float(self, val, match=True):
        if True == match:
            self.read(length=4, expect=sp.pack_single_float(val))
        else:
            self.read(length=4)

    def recv_double(self, val, match=True):
        if True == match:
            self.read(length=8, expect=sp.pack_single_double(val))
        else:
            self.read(length=8)

    def recv_hash(self, hash_val, match=True):
        if True == match:
            self.read(length=8, expect=hash_val)
        else:
            self.read(length=8)

    def start(self):
        #self.delay(100)
        self.state['e'] = OnSale()
        self.compute_status_codes()
        if DEBUG:
            print "------- start -----------"

    def buy_products(self):
        '''
        Purchase one or more products
        '''
        self.send_cmd(self.CMD_BUY)
        if DEBUG:
            print "cmd: buy products"

        # get list of products from inventory (duplicates are ok)
        products = self.state['e'].get_rand_products_to_buy(count=randint(1,50))

        # for each product
        write_str = ''
        total_cost = 0.0
        for p in products:
            # send BUY_MORE
            write_str += CONFIG['BUY_MORE']
            # send barcode
            write_str += (str(p.barcode))

            if DEBUG:
                print "\t buy: {0}".format(p.barcode)

            total_cost += p.get_sale_price()

        # when finished send BUY_TERM
        write_str += CONFIG['BUY_TERM']
        self.write(write_str)

        # recv total cost; do NOT try matching floats/doubles
        self.recv_double(total_cost, match=False) 

        if DEBUG:
            print "\t total cost: {0}".format(total_cost)

        #     self.recv_status(self.STATUS_ERR)
        self.recv_status(self.STATUS_OK)

        return 0

    def check_product(self):
        '''
        Check info about product.
        '''
        self.send_cmd(self.CMD_CHECK)
        if DEBUG:
            print "cmd: check product"

        # select a product from existing inventory
        invalid = False
        if self.chance(0.1):
            invalid=True

        product = self.state['e'].get_rand_product_from_inventory(invalid=invalid)

        # send barcode
        self.write(product.barcode)

        if True == invalid:   # if not found/invalid, recv err status
            self.recv_status(self.STATUS_ERR)

        else:  # if found
            match_str = ''
        # recv model num
            self.recv_uint32(product.model_num, match=True)
        # recv price
            self.recv_float(product.get_sale_price(), match=False)
        # recv desc
            desc_packed = sp.pack_single_string(product.description)
            match_str += desc_packed
        # recv desc term char
            match_str += sp.pack_single_char(CONFIG['DESC_TERM'])

            self.read(length=len(match_str), expect=match_str)
            self.recv_status(self.STATUS_OK)
        return 0

    def add_product(self):
        '''
        Add a new product.
        '''
        self.send_cmd(self.CMD_ADD)
        if DEBUG:
            print "cmd: add product"

        # gen new product
        p = self.state['e'].get_new_rand_product()
        #send bc
        self.write(p.barcode)
        # if bc is not unique -> STATUS_ERR
        if False == self.state['e'].is_barcode_unique(p.barcode):
            self.recv_status(self.STATUS_ERR)
            return -1

        write_str = ''
        #send model_num
        write_str += sp.pack_single_uint32(p.model_num)

        #send cost
        write_str += sp.pack_single_float(p.cost)

        #send desc + CONFIG['DESC_TERM']
        write_str += sp.pack_single_string(p.description + CONFIG['DESC_TERM'])
        self.write(write_str)

        # add new product to inventory
        self.state['e'].add_prod_to_inventory(p)

        self.recv_status(self.STATUS_OK)

        return 0

    def rm_product(self):
        '''
        Remove a product.
        '''
        self.send_cmd(self.CMD_RM)
        if DEBUG:
            print "cmd: rm product"

        # select a product from existing inventory
        invalid = False
        if self.chance(0.1):
            invalid=True

        product = self.state['e'].get_rand_product_from_inventory(invalid=invalid)

        # send barcode
        self.write(product.barcode)

        if True == invalid:   # if not found/invalid, recv err status
            self.recv_status(self.STATUS_ERR)

        else:  # if found
            self.state['e'].rm_prod_from_inventory(product)
            del product
            self.recv_status(self.STATUS_OK)
    
        return 0

    def update_product(self):
        '''
        Update the info about a product.
        '''
        self.send_cmd(self.CMD_UPDATE)
        if DEBUG:
            print "cmd: update product"

        # select a product from existing inventory
        invalid = False
        if self.chance(0.1):
            invalid=True

        product = self.state['e'].get_rand_product_from_inventory(invalid=invalid)

        # send barcode
        self.write(product.barcode)

        if True == invalid:   # if not found/invalid, recv err status
            self.recv_status(self.STATUS_ERR)

        else:  # if found

            # gen new product
            p = self.state['e'].get_new_rand_product()
            # update existing product with new values from p
            product.model_num = p.model_num
            product.cost = p.cost
            product.description = p.description
    
            write_str = ''
            #send model_num
            write_str += sp.pack_single_uint32(p.model_num)
            #send cost
            write_str += sp.pack_single_float(p.cost)
            #send desc + CONFIG['DESC_TERM']
            write_str += sp.pack_single_string(p.description + CONFIG['DESC_TERM'])
            self.write(write_str)

            self.recv_status(self.STATUS_OK)

        return 0

    def set_onsale(self):
        '''
        Set a product as on sale.
        '''
        self.send_cmd(self.CMD_ONSALE)
        if DEBUG:
            print "cmd: set onsale"

        # select a product from existing inventory
        invalid = False
        if self.chance(0.1):
            invalid=True
        product = self.state['e'].get_rand_product_from_inventory(invalid=invalid)

        # send barcode
        self.write(product.barcode)

        if True == invalid:   # if not found/invalid, recv err status
            self.recv_status(self.STATUS_ERR)

        else:  # if found
        # send sale percent
            sale_percent = randint(1, 150)
            self.write(sp.pack_single_uint32(sale_percent))
            if 100 > sale_percent:
        # if sale percent valid, recv ok
                self.recv_status(self.STATUS_OK)
                product.set_on_sale(sale_percent)
            else:
        # if sale percent invalid, recv err
                self.recv_status(self.STATUS_ERR)

        return 0

    def set_nosale(self):
        '''
        Set a product as not on sale.
        '''
        self.send_cmd(self.CMD_NOSALE)
        if DEBUG:
            print "cmd: set no sale"

        # select a product from existing inventory
        invalid = False
        if self.chance(0.1):
            invalid=True
        product = self.state['e'].get_rand_product_from_inventory(invalid=invalid)

        # send barcode
        self.write(product.barcode)

        if True == invalid:   # if not found/invalid, recv err status
            self.recv_status(self.STATUS_ERR)

        else:  # if found
            self.recv_status(self.STATUS_OK)

        return 0

    def list_products(self):
        '''
        Get a listing of all products. Get additional info depending on options selected.
        '''
        self.send_cmd(self.CMD_LIST)
        if DEBUG:
            print "cmd: list products"

        opt_model_num = chr(randint(1, 200))
        opt_cost = chr(2) # don't want this option on; can't match float reliably
        opt_sale_cost = chr(3) # don't want this option on; can't match float reliably
        opt_description = chr(randint(1, 200))
        options = "{0}{1}{2}{3}".format(opt_model_num, opt_cost, opt_sale_cost, opt_description)

        self.write(sp.pack_single_string(options))

        inventory = self.state['e'].inventory
        if (0 == len(inventory)):
            self.recv_status(self.STATUS_ERR)
        else:
            match_str = ''
            for p in inventory:
                match_str += sp.pack_single_string(p.barcode)

                if 0 == ord(opt_model_num) % 2:
                    match_str += sp.pack_single_uint32(p.model_num)

                # skip cost and sale_cost

                if 0 != ord(opt_description) % 2:
                    if 0 < len(p.description):
                        desc_packed = sp.pack_single_string(p.description)
                        match_str += desc_packed
                    # recv desc term char
                    match_str += sp.pack_single_char(CONFIG['DESC_TERM'])

            if '' != match_str:
                self.read(length=len(match_str), expect=match_str)
            self.recv_status(self.STATUS_OK)

        return 0

    def quit(self):
        '''
        Quit cleanly
        '''
        self.send_cmd(self.CMD_QUIT)
        if DEBUG:
            print "cmd: quit -----------"

        self.recv_status(self.STATUS_QUIT)
        return -1

    def broker(self):
        '''
        Branching node for all nodes
        '''
        return 0


