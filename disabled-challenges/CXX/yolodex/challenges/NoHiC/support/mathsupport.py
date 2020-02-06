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

import struct
import string
from random import choice, randint
from os.path import join
import operator
import sys
from array import array
import numpy as np
from collections import Counter

class MathSupport(object):

	DEBUG = False

	DOUBLE_DIVISOR = 3.1415926535 # a piece of pi to help us make a float
	LIST_TYPE = {'INT32': 0, 'DBL64': 1, 'BAD': 2}
	COMMANDS = {'CREATE': 0, 'EVAL': 1, 'BAD': 2}
	MATH_OP_CODES = {
		'MEAN': 0,
		'MEDIAN': 1,
		'MODE': 2,
		'RANGE': 3,
		'SUM': 4,
		'PRODUCT': 5,
		'MIN': 6,
		'MAX': 7,
		'SORT': 8,
		'RSORT': 9,
		'ODDS': 10,
		'EVENS': 11,
		'BAD': 12,
	}

	def __init__(self, list_type='INT32', list_size='1000'):
		self.INT_LIST = array('i') # list of signed ints
		self.DBL_LIST = [] # list of doubles
		self.list_type = self.LIST_TYPE[list_type]
		self._gen_list(list_size)
		# self._gen_static_list(list_size)

	## Helper functions ##
	def _get_list(self):
		if self.list_type == self.LIST_TYPE['INT32']:
			return self.INT_LIST
		else:
			return self.DBL_LIST

	def _gen_static_list(self, list_size):
		static_val = -1695260149
		for idx in range(list_size):
			if self.list_type == self.LIST_TYPE['INT32']:
				self.INT_LIST.append(np.int_(static_val))

			else:
				self.DBL_LIST.append(float(static_val / self.DOUBLE_DIVISOR))

	def _gen_list(self, list_size):
		count = 0
		for idx in range(list_size):
			val = randint(-(sys.maxint - 1), sys.maxint)

			if count == list_size:
				continue

			# add one value
			if self.list_type == self.LIST_TYPE['INT32']:
				self.INT_LIST.append(np.int_(val))
				count += 1

			else:
				self.DBL_LIST.append(float(val / self.DOUBLE_DIVISOR))
				count += 1

			# add some duplicates so mode() will be tested properly
			if count < list_size and idx % 2 == 0:
				count += 1
				if self.list_type == self.LIST_TYPE['INT32']:
					self.INT_LIST.append(self.INT_LIST[0])
				else:
					self.DBL_LIST.append(self.DBL_LIST[0])

			if count < list_size and idx % 5 == 0:
				count += 1
				if self.list_type == self.LIST_TYPE['INT32']:
					self.INT_LIST.append(self.INT_LIST[-1])
				else:
					self.DBL_LIST.append(self.DBL_LIST[-1])

		if self.DEBUG:
			print("\nlist_size: {0}".format(count))

	#### Protocol Funcs ####

	def pack_single_uint32(self, uint32_val):
		'''
		Pack unsigned int32
		'''
		return struct.pack('I', uint32_val)

	def pack_single_int32(self, int32_val):
		'''
		Pack signed int32
		'''
		return struct.pack('i', int32_val)

	def pack_single_dbl64(self, dbl64_val):
		return struct.pack('d', dbl64_val)

	def pack_single(self, val):
		'''
		Pack a single value based on the list_type.
		'''
		if self.list_type == self.LIST_TYPE['INT32']:
			return self.pack_single_int32(val)
		else:
			return self.pack_single_dbl64(val)

	def pack_list_int32(self, int32_val_list):
		'''
		Pack a list of int32 values.
		'''
		fmt = 'i' * len(int32_val_list)
		return struct.pack(fmt, *int32_val_list)

	def pack_list_dbl64(self, dbl64_val_list):
		'''
		Pack a list of double values.
		'''
		fmt = 'd' * len(dbl64_val_list)
		return struct.pack(fmt, *dbl64_val_list)

	def pack_list(self, val_list=[]):
		'''
		Pack a list of values based on the list_type.
		'''
		if self.list_type == self.LIST_TYPE['INT32']:
			if val_list == []:
				val_list = self.INT_LIST
			return self.pack_list_int32(val_list)
		else:
			if val_list == []:
				val_list = self.DBL_LIST
			return self.pack_list_dbl64(val_list)

	def pack_op_code(self, op_code):
		'''
		op_code is uint8_t
		'''
		return struct.pack('B', self.MATH_OP_CODES[op_code])

	def pack_command(self, command):
		'''
		command is uint8_t
		'''
		return struct.pack('B', self.COMMANDS[command])

	def pack_list_type(self, list_type=''):
		'''
		list_type is uint8_t
		'''
		if list_type == '':
			return struct.pack('B', self.list_type)
		else:
			return struct.pack('B', self.LIST_TYPE[list_type])

	def pack_length_and_list(self, val_list=[], internal_list=False, split=False):
		'''
		val_list can contain either all int32_t's or all double's
		internal_list causes the full self.INT_LIST or self.DBL_LIST to be used.
		length is uint32_t
		INT_LIST has int32_t values
		DBL_LIST has double values
		'''
		if self.DEBUG:
			print('  val_list: {0}\n'.format(val_list))
		if internal_list == True:
			if self.list_type == self.LIST_TYPE['INT32']:
				val_list = self.INT_LIST
			else:
				val_list = self.DBL_LIST

		length = len(val_list)

		if self.list_type == self.LIST_TYPE['INT32']:
			fmt = length * 'i'
			if self.DEBUG:
				print(' INT32 list. len: {0}\n fmt: {1}\n list: {2}'.format(length, fmt, val_list))
			# return struct.pack(fmt, length, *val_list)
		else:
			fmt = length * 'd'
			if self.DEBUG:
				print(' DBL64 list. len: {0}\n fmt: {1}\n list: {2}'.format(length, fmt, val_list))
			# return struct.pack(fmt, length, *val_list)

		res = [struct.pack('I', length), struct.pack(fmt, *val_list)]
		if True == split:
			return res
		else:
			return "{0}{1}".format(res[0], res[1])

	#### Math Funcs ####
	def do_c_int_division(self, int_val, int_divisor):
		'''
		Simulate C style int division (truncate toward 0)
		and do int overflow/underflow.
		'''
		return np.int_(np.trunc(np.divide(int_val, (int_divisor + 0.0))))

	def get_mean(self):
		'''
		Get the mean of the values in the currently used list.
		Use the same calculation method as the cb func's.
		Simulate C style int division (truncate toward 0)
		'''
		if self.list_type == self.LIST_TYPE['INT32']:
			return self.do_c_int_division(self.get_sum(), len(self.INT_LIST))
		else:
			return sum(self.DBL_LIST) / len(self.DBL_LIST)

	def get_sum(self):
		'''
		Get the sum of the values in the currently used list.
		Use the same calculation method as the cb func's.
		Simulate int32 overflow and float going to inf/-inf.
		'''
		if self.list_type == self.LIST_TYPE['INT32']:
			return np.sum(self.INT_LIST, dtype=np.int_)
		else:
			return sum(self.DBL_LIST)

	def get_product(self):
		'''
		Get the product of the values in the currently used list.
		Use the same calculation method as the cb func's.
		Simulate int32 overflow and float going to inf/-inf.
		'''
		if self.list_type == self.LIST_TYPE['INT32']:
			return np.prod(self.INT_LIST, dtype=np.int_)
		else:
			return reduce(operator.mul, self.DBL_LIST)

	def get_min(self):
		'''
		Get the minimum of the values in the currently used list.
		'''
		if self.list_type == self.LIST_TYPE['INT32']:
			return np.amin(self.INT_LIST)
		else:
			return min(self.DBL_LIST)

	def get_max(self):
		'''
		Get the maximum of the values in the currently used list.
		'''
		if self.list_type == self.LIST_TYPE['INT32']:
			return np.amax(self.INT_LIST)
		else:
			return max(self.DBL_LIST)

	def get_median(self):
		'''
		Get the median of the values in the currently used list.
		Use the same calculation method as the cb func's.
		Simulate C int division (truncate toward 0) and int32 overflow
		'''
		if self.list_type == self.LIST_TYPE['INT32']:
			length = len(self.INT_LIST)
			middle = length / 2
			median = 0
			lst = np.sort(self.INT_LIST)
			if length % 2 == 0:
				median = self.do_c_int_division(np.sum([lst[middle - 1], lst[middle]], dtype=np.int_), 2)
			else:
				median = lst[middle]

			return median
		else:
			length = len(self.DBL_LIST)
			middle = length / 2
			median = 0.0
			lst = list(self.DBL_LIST)
			lst.sort()
			if length % 2 == 0:
				median = sum([lst[middle - 1], lst[middle]]) / 2.0
			else:
				median = lst[middle]

			return median

	def get_sort(self):
		'''
		Get the list sorted ascending.
		'''
		if self.list_type == self.LIST_TYPE['INT32']:
			return np.sort(self.INT_LIST)
		else:
			return np.sort(self.DBL_LIST)

	def get_rsort(self):
		'''
		Get the list sorted descending.
		'''
		if self.list_type == self.LIST_TYPE['INT32']:
			return np.sort(self.INT_LIST)[::-1]
		else:
			return np.sort(self.DBL_LIST)[::-1]

	def get_odds(self):
		'''
		Get the list of odd values in the list.
		Imagine fairy world where you can determine odd/even of a float.
		'''
		if self.list_type == self.LIST_TYPE['INT32']:
			odd_list = array('i')
			for val in self.INT_LIST:
				if val % 2 != 0:
					odd_list.append(val)
			return odd_list
		else:
			odd_list = []
			for val in self.DBL_LIST:
				if np.int_(np.trunc(val)) % 2 != 0:
					odd_list.append(val)
			return odd_list

	def get_evens(self):
		'''
		Get the list of odd values in the list.
		Imagine fairy world where you can determine odd/even of a float.
		'''

		if self.list_type == self.LIST_TYPE['INT32']:
			even_list = array('i')
			for val in self.INT_LIST:
				if val % 2 == 0:
					even_list.append(val)
			return even_list
		else:
			even_list = []
			for val in self.DBL_LIST:
				if np.int_(np.trunc(val)) % 2 == 0:
					even_list.append(val)
			return even_list

	def get_mode(self):
		'''
		Get the list of numbers having the max mode in the list.
		'''
		if self.list_type == self.LIST_TYPE['INT32']:
			res = array('i')
			c = Counter(self.INT_LIST)
			max_count = max(c.values())
			if max_count > 1:
				for (val, cnt) in c.most_common():
					if cnt == max_count:
						res.append(val)
			return res

		else:
			res = array('d')
			c = Counter(self.DBL_LIST)
			max_count = max(c.values())
			if max_count > 1:
				for (val, cnt) in c.most_common():
					if cnt == max_count:
						res.append(val)
			return res

	def get_range(self):
		'''
		Get the range of the list of numbers.
		Simulate C's int math.
		'''
		if self.list_type == self.LIST_TYPE['INT32']:
			return np.subtract(np.amax(self.INT_LIST), np.amin(self.INT_LIST))
		else:
			return max(self.DBL_LIST) - min(self.DBL_LIST)
