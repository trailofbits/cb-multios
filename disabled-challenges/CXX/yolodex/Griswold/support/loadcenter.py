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
from common import ERRORS, DEBUG

LOAD_CENTER_MODELS = {
	'ONE_HUNDRED_AMP_EIGHT_SPACE': 10008,
	'ONE_HUNDRED_AMP_SIXTEEN_SPACE': 10016,
	'ONE_HUNDRED_AMP_TWENTY_SPACE': 10020,
	'ONE_HUNDRED_FIFTY_AMP_TWENTY_SPACE': 15020,
	'ONE_HUNDRED_FIFTY_AMP_TWENTY_FOUR_SPACE': 15024,
	'ONE_HUNDRED_FIFTY_AMP_THIRTY_SPACE': 15030,
	'TWO_HUNDRED_AMP_TWENTY_SPACE': 20020,
	'TWO_HUNDRED_AMP_THIRTY_SPACE': 20030,
	'TWO_HUNDRED_AMP_FOURTY_SPACE': 20040,
	'TWO_HUNDRED_AMP_FOURTY_TWO_SPACE': 20042,
	'FOUR_HUNDRED_AMP_TWENTY_SPACE': 40020,
	'FOUR_HUNDRED_AMP_THIRTY_SPACE': 40030,
	'FOUR_HUNDRED_AMP_FOURTY_SPACE': 40040,
	'FOUR_HUNDRED_AMP_FOURTY_TWO_SPACE': 40042,
	'BAD': 13,
}

class LoadCenter(object):

	def __init__(self, model_name):
		self.breaker_spaces = LOAD_CENTER_MODELS[model_name] % 100
		self.amp_rating = LOAD_CENTER_MODELS[model_name] / 100
		self.breakers = []

	def get_breaker_spaces_cnt(self):
		return self.breaker_spaces

	def get_breakers_installed_cnt(self):
		return len(self.breakers)

	def get_amp_rating(self):
		return self.amp_rating

	def is_full(self):
		return self.get_breakers_installed_cnt() >= self.get_breaker_spaces_cnt()

	def is_empty(self):
		return 0 == self.get_breakers_installed_cnt()
		
	def add_breaker(self, breaker):
		breaker.set_id(self.get_breakers_installed_cnt())
		self.breakers.append(breaker)

	def get_breaker_by_id(self, breaker_id):
		for breaker in self.breakers:
			if breaker_id == breaker.get_id():
				return breaker
		return None

	def get_outlet_by_id(self, outlet_id):
		for breaker in self.breakers:
			o = breaker.get_outlet_by_id(outlet_id)
			if None != o:
				return o
		return None

	def get_light_string_by_id(self, light_string_id):
		for breaker in self.breakers:
			ls = breaker.get_light_string_by_id(light_string_id)
			if None != ls:
				return ls
		return None

	def get_splitter_by_id(self, splitter_id):
		for breaker in self.breakers:
			sp = breaker.get_splitter_by_id(splitter_id)
			if None != sp:
				return sp
		return None

	def get_receptacle_by_id(self, receptacle_id):
		for breaker in self.breakers:
			r = breaker.get_receptacle_by_id(receptacle_id)
			if None != r:
				return r
		return None

	def get_amp_load(self):
		amp_load = 0.0
		for breaker in self.breakers:
			amp_load += breaker.get_amp_load()
		return amp_load

