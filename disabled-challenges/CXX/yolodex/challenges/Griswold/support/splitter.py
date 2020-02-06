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

SPLITTER_MODELS = {
	'THREE_WAY': 3,
	'SIX_WAY': 6,
	'EIGHT_WAY': 8,
	'BAD': 13,
}

class Splitter(object):

	def __init__(self, model_name, s_id, r_ids):
		self.id = s_id
		self.total_amp_rating = 15
		self.receptacle_amp_rating = 0
		self.receptacle_count = SPLITTER_MODELS[model_name]
		self.receptacles = []
		for idx in range(self.receptacle_count):
			self.receptacles.append(Receptacle(15, r_ids[idx]))
		if True == DEBUG:
			print('Splitter.__init__() created model_name:{0}, id:{1}, receptacles:{2}'.format(model_name, self.id, self.receptacles))

	def get_id(self):
		return self.id

	def get_amp_rating(self):
		return self.total_amp_rating

	def get_light_string_by_id(self, light_string_id):
		ls = None
		for receptacle in self.receptacles:
			ls = receptacle.get_light_string_by_id(light_string_id)
			if None != ls:
				return ls
		return ls

	def get_splitter_by_id(self, splitter_id):
		if True == DEBUG:
			print('Splitter.get_splitter_by_id: splitter_id:{0}'.format(splitter_id))

		if splitter_id == self.id:
			return self
		else:
			sp = None
			for receptacle in self.receptacles:
				sp = receptacle.get_splitter_by_id(splitter_id)
				if None != sp:
					return sp
			return sp

	def get_receptacle_by_id(self, receptacle_id):
		if True == DEBUG:
			print('Splitter.get_receptacle_by_id: rid:{0}'.format(receptacle_id))

		r = None
		for receptacle in self.receptacles:
			r = receptacle.get_receptacle_by_id(receptacle_id)
			if None != r:
				break
		return r

	def get_amp_load(self):
		amp_load = 0.0
		for receptacle in self.receptacles:
			amp_load += receptacle.get_amp_load()
		return amp_load

	def get_max_receptacle_amp_load(self):
		amp_loads = []
		for receptacle in self.receptacles:
			amp_loads.append(receptacle.get_amp_load())
		return max(amp_loads)
