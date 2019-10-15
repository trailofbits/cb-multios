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


LIGHT_STRING_MODELS = {
	'INCANDESCENT_M5_100BULB': 5,
	'LED_C6_150BULB': 6,
	'INCANDESCENT_C7_25BULB': 7,
	'INCANDESCENT_C9_25BULB': 9,
	'BAD': 13,
}

MODEL_WATTAGE = {
	'INCANDESCENT_M5_100BULB': 40.8,
	'LED_C6_150BULB': 12.0,
	'INCANDESCENT_C7_25BULB': 165.6,
	'INCANDESCENT_C9_25BULB': 120.0,
}

MAX_RESIDENTIAL_LIGHT_STRING_WIRE_WATTAGE = 210.0
RESIDENTIAL_LINE_VOLTAGE = 120.0


class LightString(object):

	def __init__(self, model_name, s_id, r_id):
		self.id = s_id
		self.total_wattage = MODEL_WATTAGE[model_name]
		self.receptacle = Receptacle(15, r_id)
		self.model_id = LIGHT_STRING_MODELS[model_name]

	def get_id(self):
		return self.id

	def get_amp_rating(self):
		return float(MAX_RESIDENTIAL_LIGHT_STRING_WIRE_WATTAGE / RESIDENTIAL_LINE_VOLTAGE)

	def get_light_string_by_id(self, light_string_id):
		if light_string_id == self.id:
			return self
		else:
			return self.receptacle.get_light_string_by_id(light_string_id)

	def get_splitter_by_id(self, splitter_id):
		return self.receptacle.get_splitter_by_id(splitter_id)

	def get_receptacle_by_id(self, receptacle_id):
		if True == DEBUG:
			print('LightString.get_receptacle_by_id: rid:{0}'.format(receptacle_id))

		return self.receptacle.get_receptacle_by_id(receptacle_id)

	def get_amp_load(self):
		amp_load = float(self.total_wattage / RESIDENTIAL_LINE_VOLTAGE)
		amp_load += self.receptacle.get_amp_load()
		return amp_load


