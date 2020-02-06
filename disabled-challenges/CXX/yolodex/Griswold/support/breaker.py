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

BREAKER_MODELS = {
	'FIFTEEN_AMP': 15,
	'TWENTY_AMP': 20,
	'BAD': 13,
}

class Breaker(object):

	def __init__(self, model_name):
		self.id = 0
		self.amp_rating = BREAKER_MODELS[model_name]
		self.outlets = []

	def get_id(self):
		return self.id

	def get_amp_rating(self):
		return self.amp_rating

	def set_id(self, breaker_id):
		self.id = breaker_id

	def add_outlet(self, outlet):
		self.outlets.append(outlet)

	def get_count_outlets(self):
		return len(self.outlets)

	def get_outlet_by_id(self, outlet_id):
		for outlet in self.outlets:
			if outlet_id == outlet.get_id():
				return outlet
		return None

	def get_light_string_by_id(self, light_string_id):
		for outlet in self.outlets:
			ls = outlet.get_light_string_by_id(light_string_id)
			if None != ls:
				return ls
		return None

	def get_splitter_by_id(self, splitter_id):
		for outlet in self.outlets:
			sp = outlet.get_splitter_by_id(splitter_id)
			if None != sp:
				return sp
		return None

	def get_receptacle_by_id(self, receptacle_id):
		for outlet in self.outlets:
			r = outlet.get_receptacle_by_id(receptacle_id)
			if None != r:
				return r
		return None

	def get_amp_load(self):
		amp_load = 0.0
		for outlet in self.outlets:
			amp_load += outlet.get_amp_load()
		return amp_load


