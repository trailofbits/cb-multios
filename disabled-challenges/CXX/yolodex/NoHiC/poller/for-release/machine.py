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
import string
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
from mathsupport import MathSupport

class MultiPass(Actions):
	
	DEBUG = False
	DEBUG_ERR = DEBUG or False
	DEBUG_FUNC = DEBUG or False

	DEBUG_MEAN = DEBUG or False
	DEBUG_SUM = DEBUG or False
	DEBUG_PRODUCT = DEBUG or False
	DEBUG_MIN = DEBUG or False
	DEBUG_MAX = DEBUG or False
	DEBUG_MEDIAN = DEBUG or False
	DEBUG_SORT = DEBUG or False
	DEBUG_RSORT = DEBUG or False
	DEBUG_ODDS = DEBUG or False
	DEBUG_EVENS = DEBUG or False
	DEBUG_MODE = DEBUG or False
	DEBUG_RANGE = DEBUG or False

	MAX_UINT32 = 2 * sys.maxint + 1
	MAX_LIST_LEN = 1000

	def start(self):
		self.LIST_TYPE = choice(['INT32', 'DBL64'])
		self.LIST_SIZE = randint(5, 1005)
		self.state['m'] = MathSupport(list_type=self.LIST_TYPE, list_size=self.LIST_SIZE)
		self.state['created'] = False
		self.state['cnonce'] = Variable('cnonce')
		self.state['cnonce'].set_slice(0,8)
		self.state['enonce'] = Variable('enonce')
		self.state['enonce'].set_slice(0,8)

	def process_nonce_create(self):
		if self.DEBUG_FUNC:
			print('-- process_nonce_create --')

		self.read(length=8, assign=self.state['cnonce'])
		self.write(self.state['cnonce'])

		return 0

	def process_nonce_eval(self):
		if self.DEBUG_FUNC:
			print('-- process_nonce_eval --')

		self.read(length=8, assign=self.state['enonce'])
		if self.chance(0.001):
			# send an invalid nonce
			self.write(self.state['cnonce'])
			expected = self.state['m'].pack_single_int32(-44)
			self.read(length=len(expected), expect=expected)
			if self.DEBUG_ERR:
				print('exiting due to incorrect nonce.')
			return -1
		else:
			self.write(self.state['enonce'])
			return 0

	def _send_command(self, command):
		if self.DEBUG_FUNC:
			print('-- _send_command --')

		if self.chance(0.001):
			# send invalid command (BAD)
			cmd = self.state['m'].pack_command('BAD')
			self.write(cmd)
			expected = self.state['m'].pack_single_int32(-150)
			self.read(length=len(expected), expect=expected)
			if self.DEBUG_ERR:
				print('exiting due to BAD command.')
			return -1
		else:
			cmd = self.state['m'].pack_command(command)
			self.write(cmd)
			return 0

	def send_eval(self):
		if self.DEBUG_FUNC:
			print('-- send_eval --')

		# Eval only works after load_list has been run
		if self.state['created'] == False:
			# EVAL before load_list CREATE
			if self._send_command('EVAL') < 0:
				return -1
			expected = self.state['m'].pack_single_int32(-10)
			self.read(length=len(expected), expect=expected)
			if self.DEBUG_ERR:
				print('exiting due to EVAL before CREATE.')
			return -1
		else:
			# pack and send EVAL command
			if self._send_command('EVAL') < 0:
				return -1

	def _send_op_code(self, op_code):
		if self.DEBUG_FUNC:
			print('-- _send_op_code --')

		if self.chance(0.001):
			# invalid op_code to EVAL
			op_code = self.state['m'].pack_op_code('BAD')
			self.write(op_code)
			expected = self.state['m'].pack_single_int32(-80)
			self.read(length=len(expected), expect=expected)
			if self.DEBUG_ERR:
				print('exiting due to invalid op_code BAD.')
			return -1
		else:
			# pack and send op_code
			op_code = self.state['m'].pack_op_code(op_code)
			self.write(op_code)
			return 0

	def send_create(self):
		if self.DEBUG_FUNC:
			print('-- send_create --')

		if self.state['created'] == True:
			# send CREATE command again
			if self._send_command('CREATE') < 0:
				return -1
			expected = self.state['m'].pack_single_int32(-9)
			self.read(length=len(expected), expect=expected)
			if self.DEBUG_ERR:
				print('exiting due to re-sending CREATE.')
			return -1
		else:
			# pack and send CREATE command
			if self._send_command('CREATE') < 0:
				return -1

			if self.chance(0.001):
				# invalid list_type
				# pack and send LIST_TYPE "BAD"
				t = self.state['m'].pack_list_type('BAD')
				self.write(t)
				expected = self.state['m'].pack_single_int32(-30)
				self.read(length=len(expected), expect=expected)
				if self.DEBUG_ERR:
					print('exiting due to invalid list_type BAD.')
				return -1
			else:
				# pack and send LIST_TYPE
				t = self.state['m'].pack_list_type()
				self.write(t)

				# pack and send LIST LENGTH
				l = self.state['m'].pack_length_and_list(internal_list=True, split=True)
				self.write(l[0])

				if self.LIST_SIZE > self.MAX_LIST_LEN:
					expected = self.state['m'].pack_single_int32(-70)
					self.read(length=len(expected), expect=expected)
					if self.DEBUG_ERR:
						print('exiting due to too large of list_size.')
					return -1

				# pack and send LIST
				self.write(l[1])

				self.state['created'] = True
				return 0

	def _read_and_match_calculated_dbl64(self, val):
		'''
		This function will read the least significant byte of a double precision
		float with a wildcard, and then read the other 7 bytes with an exact match.

		Exact comparison with computed double precision floating point numbers
		is non-deterministic when the numbers are computed in 2 different programming languages.
		
		There are too many cases where the least significant digit or two
		of a calculated float differ when calculated in C vs Python.
		'''
		exp_result = self.state['m'].pack_single(val)[1:]
		# read 1 byte with wildcard
		least_sig_byte = Variable('LSB')
		least_sig_byte.set_slice(0,1)
		self.read(length=1, assign=least_sig_byte)

		# read 7 bytes for exact match
		self.read(length=len(exp_result), expect=exp_result)

	def _read_and_match_calculated_int32(self, val):
		'''
		Matching INTs is not a problem. So just do it.
		'''
		exp_result = self.state['m'].pack_single(val)
		self.read(length=len(exp_result), expect=exp_result)

	def _read_and_match_calculated_value(self, val):
		if self.LIST_TYPE == 'INT32':
			self._read_and_match_calculated_int32(val)
		else:
			self._read_and_match_calculated_dbl64(val)

	def mean_op(self):
		if self.DEBUG_MEAN:
			print('-- mean_op --')

		if self._send_op_code('MEAN') < 0:
			return -1
		# read expected result
		val = self.state['m'].get_mean()
		if self.DEBUG_MEAN:
			print('mean_op: val = {0}'.format(val))
		self._read_and_match_calculated_value(val)

	def sum_op(self):
		if self.DEBUG_SUM:
			print('-- sum_op --')

		if self._send_op_code('SUM') < 0:
			return -1

		# read expected result
		val = self.state['m'].get_sum()
		if self.DEBUG_SUM:
			print('sum_op: val = {0}'.format(val))
		self._read_and_match_calculated_value(val)

	def product_op(self):
		if self.DEBUG_PRODUCT:
			print('-- product_op --')
			
		if self._send_op_code('PRODUCT') < 0:
			return -1

		# read expected result
		val = self.state['m'].get_product()
		if self.DEBUG_PRODUCT:
			print('product_op: val = {0}'.format(val))
		self._read_and_match_calculated_value(val)

	def min_op(self):
		if self.DEBUG_MIN:
			print('-- min_op --')
			
		if self._send_op_code('MIN') < 0:
			return -1

		# read expected result
		val = self.state['m'].get_min()
		if self.DEBUG_MIN:
			print('min_op: val = {0}'.format(val))
		exp_result = self.state['m'].pack_single(val)
		self.read(length=len(exp_result), expect=exp_result)

	def max_op(self):
		if self.DEBUG_MAX:
			print('-- max_op --')
			
		if self._send_op_code('MAX') < 0:
			return -1

		# read expected result
		val = self.state['m'].get_max()
		if self.DEBUG_MAX:
			print('max_op: val = {0}'.format(val))
		exp_result = self.state['m'].pack_single(val)
		self.read(length=len(exp_result), expect=exp_result)

	def median_op(self):
		if self.DEBUG_MEDIAN:
			print('-- median_op --')
			
		if self._send_op_code('MEDIAN') < 0:
			return -1

		# read expected result
		val = self.state['m'].get_median()
		if self.DEBUG_MEDIAN:
			print('median_op: val = {0}'.format(val))
		self._read_and_match_calculated_value(val)

	def sort_op(self):
		if self.DEBUG_SORT:
			print('-- sort_op --')
			
		if self._send_op_code('SORT') < 0:
			return -1

		# read expected result
		val_list = self.state['m'].get_sort()
		if self.DEBUG_SORT:
			print('sort_op: sorted list = {0}'.format(val_list))
		exp_result = self.state['m'].pack_list(val_list)
		self.read(length=len(exp_result), expect=exp_result)

	def rsort_op(self):
		if self.DEBUG_RSORT:
			print('-- rsort_op --')
			
		if self._send_op_code('RSORT') < 0:
			return -1

		# read expected result
		val_list = self.state['m'].get_rsort()
		if self.DEBUG_RSORT:
			print('rsort_op: rsorted list = {0}'.format(val_list))
		exp_result = self.state['m'].pack_list(val_list)
		self.read(length=len(exp_result), expect=exp_result)

	def odds_op(self):
		if self.DEBUG_ODDS:
			print('-- odds_op --')
			
		if self._send_op_code('ODDS') < 0:
			return -1

		# read expected result
		val_list = self.state['m'].get_odds()
		if self.DEBUG_ODDS:
			print('odds_op: odds count {0}, odds list = {1}'.format(len(val_list), val_list))

		exp_result = self.state['m'].pack_length_and_list(val_list=val_list)
		self.read(length=len(exp_result), expect=exp_result)

	def evens_op(self):
		if self.DEBUG_EVENS:
			print('-- evens_op --')
			
		if self._send_op_code('EVENS') < 0:
			return -1

		# read expected result
		val_list = self.state['m'].get_evens()
		if self.DEBUG_EVENS:
			print('evens_op: evens count {0}, evens list = {1}'.format(len(val_list), val_list))

		exp_result = self.state['m'].pack_length_and_list(val_list=val_list)
		self.read(length=len(exp_result), expect=exp_result)

	def mode_op(self):
		if self.DEBUG_MODE:
			print('-- mode_op --')
			
		if self._send_op_code('MODE') < 0:
			return -1

		# read expected result
		val_list = self.state['m'].get_mode()
		if self.DEBUG_MODE:
			print('mode_op: val_list = {0}'.format(val_list))

		exp_result = self.state['m'].pack_length_and_list(val_list=val_list)
		self.read(length=len(exp_result), expect=exp_result)

	def range_op(self):
		if self.DEBUG_RANGE:
			print('-- range_op --')
			
		if self._send_op_code('RANGE') < 0:
			return -1

		# read expected result
		val = self.state['m'].get_range()
		if self.DEBUG_RANGE:
			print('range_op: val = {0}'.format(val))
		self._read_and_match_calculated_value(val)

