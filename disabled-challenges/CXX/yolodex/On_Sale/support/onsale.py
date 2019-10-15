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
from random import choice

import support as sp
from product import Product
import inventory as inv


class OnSale(object):
	def __init__(self):
		self.inventory = inv.get_initial_inventory()

	def get_new_rand_product(self, desc=""):
		p = Product(description=desc)
		while (False == self.is_barcode_unique(p.barcode)):
			p = Product(description=desc)
		return p

	def add_prod_to_inventory(self, product):
		self.inventory.append(product)

	def rm_prod_from_inventory(self, product):
		if product in self.inventory:
			self.inventory.remove(product)

	def get_rand_product_from_inventory(self, invalid=False):
		if True == invalid:
			return self.get_new_rand_product()
		else:
			return choice(self.inventory)

	def get_rand_products_to_buy(self, count=10):
		return [self.get_rand_product_from_inventory() for x in range(count)]

	def is_barcode_unique(self, bc):
		for p in self.inventory:
			if bc == p.barcode:
				return False
		return True
