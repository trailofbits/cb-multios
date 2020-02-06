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
from common import CONFIG

class Product:
    def __init__(self, barcode="", description="", model_num=0, cost=0.0):
        self.barcode = barcode
        self.description = description
        self.model_num = model_num
        self.cost = cost
        self.sale = 0

        if "" == self.barcode:
            self.barcode = self.rand_barcode()

        if "" == self.description:
            self.description = self.rand_desc()

        if 0 == self.model_num:
            self.model_num = self.rand_model_num()

        if 0.0 == self.cost:
            self.cost = self.rand_cost()

    def rand_barcode(self):
        return sp.random_digits(8)

    def rand_desc(self):
        # artificailly shortening desc len to keep message sizes lower to enable better IO
        return sp.random_string(randint(1, CONFIG['MAX_DESC_LEN']/4 - 1))

    def rand_model_num(self):
        return randint(1, 65000)

    def rand_cost(self):
        return randint(1, 1000) / 100.0

    def get_sale_price(self):
        return self.cost * (1.0 - (float(self.sale) / 100.0))

    def set_no_sale(self):
        self.sale = 0

    def set_on_sale(self, amt):
        self.sale = amt

    def __str__(self):
        return "barcode: {0}, model_num: {1}, cost: {2}\ndescription: {3}".format(self.barcode,
                                                                                self.model_num,
                                                                                self.cost,
                                                                                self.description)

    def __repr__(self):
        return self.__str__()
