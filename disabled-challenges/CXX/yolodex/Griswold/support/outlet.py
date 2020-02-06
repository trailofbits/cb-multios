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
from receptacle import Receptacle

OUTLET_MODELS = {
	'FIFTEEN_AMP': 15,
	'TWENTY_AMP': 20,
	'BAD': 13,
}

class Outlet(object):

	def __init__(self, model_name, o_id, r_ids):
		self.id = o_id
		self.amp_rating = OUTLET_MODELS[model_name]
		self.r1 = Receptacle(self.amp_rating, r_ids[0])
		self.r2 = Receptacle(self.amp_rating, r_ids[1])

	def get_id(self):
		return self.id

	def get_amp_rating(self):
		return self.amp_rating

	def add_outlet(self, outlet):
		self.outlets.append(outlets)

	def get_light_string_by_id(self, light_string_id):
		ls = self.r1.get_light_string_by_id(light_string_id)
		if None == ls:
			ls = self.r2.get_light_string_by_id(light_string_id)
		return ls

	def get_splitter_by_id(self, splitter_id):
		sp = self.r1.get_splitter_by_id(splitter_id)
		if None == sp:
			sp = self.r2.get_splitter_by_id(splitter_id)
		return sp

	def get_receptacle_by_id(self, receptacle_id):
		if True == DEBUG:
			print('Outlet.get_receptacle_by_id: rid:{0}'.format(receptacle_id))
		r = self.r1.get_receptacle_by_id(receptacle_id)
		if None == r:
			r = self.r2.get_receptacle_by_id(receptacle_id)
		return r

	def get_amp_load(self):
		amp_load = 0.0
		amp_load += self.r1.get_amp_load()
		amp_load += self.r2.get_amp_load()
		return amp_load

	def get_max_receptacle_amp_load(self):
		r1_amp_load = 0.0 + self.r1.get_amp_load()
		r2_amp_load = 0.0 + self.r2.get_amp_load()
		return max([r1_amp_load, r2_amp_load])
