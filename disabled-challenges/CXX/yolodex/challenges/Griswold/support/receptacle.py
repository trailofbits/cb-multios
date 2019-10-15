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


LOAD_TYPE = {
	'SPLITTER': 0,
	'LIGHT_STRING': 1,
	'NO_LOAD': 2,
}

class Receptacle(object):

	def __init__(self, amp_rating, r_id):
		self.id = r_id
		self.amp_rating = amp_rating
		self.load_type = LOAD_TYPE['NO_LOAD']
		self.load = None
		if True == DEBUG:
			print('Receptacle.__init__() created amp_rating:{0}, r_id:{1}'.format(amp_rating, r_id))

	def get_id(self):
		return self.id

	def get_amp_rating(self):
		return self.amp_rating

	def is_loaded(self):
		return self.load_type != LOAD_TYPE['NO_LOAD']

	def get_light_string_by_id(self, light_string_id):
		if True == self.is_loaded():
			return self.load.get_light_string_by_id(light_string_id)
		else:
			return None

	def get_splitter_by_id(self, splitter_id):
		if True == self.is_loaded():
			return self.load.get_splitter_by_id(splitter_id)
		else:
			return None

	def get_receptacle_by_id(self, receptacle_id):
		r = None
		if receptacle_id == self.get_id():
			r = self
		elif True == self.is_loaded():
			r = self.load.get_receptacle_by_id(receptacle_id)

		return r

	def connect_load(self, load_type_name, load_obj):
		self.load_type = LOAD_TYPE[load_type_name]
		self.load = load_obj

	def get_amp_load(self):
		amp_load = 0.0
		if self.is_loaded():
			amp_load = self.load.get_amp_load()
		return amp_load


