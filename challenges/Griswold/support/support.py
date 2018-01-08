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
from collections import Counter

from globalids import GlobalIdNums
from common import ERRORS, DEBUG
from loadcenter import LOAD_CENTER_MODELS, LoadCenter
from breaker import BREAKER_MODELS, Breaker
from outlet import OUTLET_MODELS, Outlet
from splitter import SPLITTER_MODELS, Splitter
from receptacle import LOAD_TYPE, Receptacle
from lightstring import LIGHT_STRING_MODELS, LightString
from results import Results


MODES = {'BUILD': 13980, 'EXAMINE': 809110, 'BAD': 13}
COMMANDS = {
	'B_CMD_INIT_PANEL': 1048,
	'B_CMD_ADD_BREAKER': 1049,
	'B_CMD_ADD_OUTLET': 1050,
	'B_CMD_ADD_SPLITTER': 1051,
	'B_CMD_ADD_LIGHT_STRING': 1052,
	'E_CMD_PANEL_OVERLOADED': 2049,
	'E_CMD_BREAKER_OVERLOADED': 2050,
	'E_CMD_OUTLET_OVERLOADED': 2051,
	'E_CMD_SPLITTER_OVERLOADED': 2052,
	'E_CMD_LIGHT_STRING_OVERLOADED': 2053,
	'E_CMD_RECEPTACLE_OVERLOADED': 2054,
	'BAD': 13,
}


class Support(object):

	def __init__(self):
		self.global_ids = GlobalIdNums()
		self.e_model = False
		self.empty_receptacle_ids = []
		self.full_receptacle_ids = []
		self.outlet_ids = []
		self.light_string_ids = []
		self.splitter_ids = []

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

	def pack_single_uint8(self, uint8_val):
		'''
		Pack unsigned int8
		'''
		return struct.pack('B', uint8_val)

	def pack_single_int8(self, int8_val):
		'''
		Pack signed int8
		'''
		return struct.pack('b', int8_val)

	def pack_mode(self, mode):
		'''
		mode is uint32_t
		'''
		return self.pack_single_uint32(MODES[mode])

	def pack_command(self, command):
		'''
		command is uint32_t
		'''
		return self.pack_single_uint32(COMMANDS[command])

	def pack_error(self, err_name):
		'''
		err_name is int32_t
		'''
		return self.pack_single_int32(ERRORS[err_name])

	def pack_model(self, model_id, component_type='LOAD_CENTER'):
		'''
		model_id is uint32_t
		'''
		if component_type == 'LOAD_CENTER':
			return self.pack_single_uint32(LOAD_CENTER_MODELS[model_id])
		elif component_type == 'BREAKER':
			return self.pack_single_uint32(BREAKER_MODELS[model_id])
		elif component_type == 'OUTLET':
			return self.pack_single_uint32(OUTLET_MODELS[model_id])
		elif component_type == 'SPLITTER':
			return self.pack_single_uint32(SPLITTER_MODELS[model_id])
		elif component_type == 'LIGHT_STRING':
			return self.pack_single_uint32(LIGHT_STRING_MODELS[model_id])

	def pack_target(self, target_id):
		'''
		target_id is uint32_t
		'''
		return self.pack_single_uint32(target_id)

	def pack_results(self, results_obj):
		'''
		results_obj is an instance of Results
		'''
		r = ''
		r += self.pack_single_uint32(results_obj.get_object_id())
		r_ids = results_obj.get_receptacle_id_list()
		for idx in range(8):
			r += self.pack_single_uint32(r_ids[idx])
		r += self.pack_single_uint8(results_obj.get_receptacle_ids_assigned_count())
		return r


	def get_list_valid_models(self, component_type):
		res = {}
		if component_type == 'LOAD_CENTER':
			res = LOAD_CENTER_MODELS
		elif component_type == 'BREAKER':
			res = BREAKER_MODELS
		elif component_type == 'OUTLET':
			res = OUTLET_MODELS
		elif component_type == 'SPLITTER':
			res = SPLITTER_MODELS
		elif component_type == 'LIGHT_STRING':
			res = LIGHT_STRING_MODELS

		keys = res.keys()
		if 'BAD' in keys:
			keys.remove('BAD')
		return keys

	def is_model_created(self):
		return self.e_model != False

	def init_panel(self, model_name):
		self.e_model = LoadCenter(model_name)

	def is_panel_full(self):
		return self.e_model.is_full()

	def is_panel_empty(self):
		return self.e_model.is_empty()

	def add_breaker(self, model_name):
		b = Breaker(model_name)
		self.e_model.add_breaker(b)

		r = Results()
		r.set_object_id(b.get_id())
		return r

	def get_breaker_count(self):
		if True == self.is_model_created():
			return self.e_model.get_breakers_installed_cnt()
		else:
			return 0

	def outlet_amps_exceed_breaker_amps(self, outlet_model_name, breaker_id):
		if True == self.is_panel_empty():
			if True == DEBUG:
				print('Support outlet amps > breaker amps - is_empty: {0}, breaker count: {1}'.format(self.is_panel_empty(), self.get_breaker_count()))
			return True
		else:
			b = self.e_model.get_breaker_by_id(breaker_id)
			if True == DEBUG:
				print('Support outlet amps > breaker amps - outlet:{0} > breaker:{1}'.format(OUTLET_MODELS[outlet_model_name], b.get_amp_rating()))
			return OUTLET_MODELS[outlet_model_name] > b.get_amp_rating()

	def get_random_empty_receptacle_id(self):
		r_count = len(self.empty_receptacle_ids)
		if 1 < r_count:
			return self.empty_receptacle_ids[randint(0, r_count - 1)]
		elif 1 == r_count:
			return self.empty_receptacle_ids[0]
		else:
			return 0

	def get_random_full_receptacle_id(self):
		r_count = len(self.full_receptacle_ids)
		if 1 < r_count:
			return self.full_receptacle_ids[randint(0, r_count - 1)]
		elif 1 == r_count:
			return self.full_receptacle_ids[0]
		else:
			return 0

	def get_max_empty_receptacle_id(self):
		r_count = len(self.empty_receptacle_ids)
		if 1 < r_count:
			return max(self.empty_receptacle_ids)
		elif 1 == r_count:
			return self.empty_receptacle_ids[0]
		else:
			return 0

	def get_min_empty_receptacle_id(self):
		r_count = len(self.empty_receptacle_ids)
		if 1 < r_count:
			return min(self.empty_receptacle_ids)
		elif 1 == r_count:
			return self.empty_receptacle_ids[0]
		else:
			return 0

	def get_min_valid_outlet_id(self):
		count = len(self.outlet_ids)
		if 1 < count:
			return min(self.outlet_ids)
		elif 1 == count:
			return self.outlet_ids[0]
		else:
			return 0

	def get_min_valid_light_string_id(self):
		count = len(self.light_string_ids)
		if 1 < count:
			return min(self.light_string_ids)
		elif 1 == count:
			return self.light_string_ids[0]
		else:
			return 0

	def get_min_valid_splitter_id(self):
		count = len(self.splitter_ids)
		if 1 < count:
			return min(self.splitter_ids)
		elif 1 == count:
			return self.splitter_ids[0]
		else:
			return 0

	def get_receptacle_by_id(self, receptacle_id):
		if True == DEBUG:
			print('Support.get_receptacle_by_id. receptacle_id:{0}'.format(receptacle_id))
		return self.e_model.get_receptacle_by_id(receptacle_id)

	def add_outlet(self, model_name, breaker_id):
		outlet_id = self.global_ids.get_next_outlet_id()
		rid_1 = self.global_ids.get_next_receptacle_id()
		rid_2 = self.global_ids.get_next_receptacle_id()
		if True == DEBUG:
			print('Support.add_outlet o_id:{0}, rid_1:{1}, rid_2:{2}.'.format(outlet_id, rid_1, rid_2))

		o = Outlet(model_name, outlet_id, [rid_1, rid_2])
		b = self.e_model.get_breaker_by_id(breaker_id)
		b.add_outlet(o)

		r = Results()
		r.set_object_id(outlet_id)
		r.set_next_receptacle_id(rid_1)
		r.set_next_receptacle_id(rid_2)

		r1 = o.get_receptacle_by_id(rid_1)
		r2 = o.get_receptacle_by_id(rid_2)
		if None == r1:
			print('Support.add_outlet o.get_receptacle_by_id returned None for r1.')
		if None == r2:
			print('Support.add_outlet o.get_receptacle_by_id returned None for r2.')

		self.outlet_ids.append(outlet_id)
		self.empty_receptacle_ids.append(rid_1)
		self.empty_receptacle_ids.append(rid_2)

		if True == DEBUG:
			print('Support.add_outlet(). Final empty_receptacle_ids:{0}'.format(self.empty_receptacle_ids))

		return r

	def add_light_string(self, model_name, receptacle_id):
		light_string_id = self.global_ids.get_next_light_string_id()
		rid_1 = self.global_ids.get_next_receptacle_id()
		ls = LightString(model_name, light_string_id, rid_1)

		receptacle = self.get_receptacle_by_id(receptacle_id)
		receptacle.connect_load('LIGHT_STRING', ls)

		self.full_receptacle_ids.append(receptacle_id)
		self.empty_receptacle_ids.remove(receptacle_id)

		r = Results()
		r.set_object_id(light_string_id)
		r.set_next_receptacle_id(rid_1)

		r1 = ls.get_receptacle_by_id(rid_1)
		if None == r1:
			print('Support.add_light_string ls.get_receptacle_by_id returned None for r1.')

		self.light_string_ids.append(light_string_id)
		self.empty_receptacle_ids.append(rid_1)

		if True == DEBUG:
			print('Support.add_light_string(). Final empty_receptacle_ids:{0}'.format(self.empty_receptacle_ids))
			print('Support.add_light_string(). Final full_receptacle_ids:{0}'.format(self.full_receptacle_ids))

		return r

	def add_splitter(self, model_name, receptacle_id):
		splitter_id = self.global_ids.get_next_splitter_id()
		rids = []
		receptacle_count = SPLITTER_MODELS[model_name]
		for r_id in range(receptacle_count):
			rids.append(self.global_ids.get_next_receptacle_id())

		if True == DEBUG:
			print('Support.add_splitter() receptacle_count:{0}, rids:{1}'.format(receptacle_count, rids))

		sp = Splitter(model_name, splitter_id, rids)

		receptacle = self.get_receptacle_by_id(receptacle_id)
		receptacle.connect_load('SPLITTER', sp)

		self.full_receptacle_ids.append(receptacle_id)
		self.empty_receptacle_ids.remove(receptacle_id)

		r = Results()
		r.set_object_id(splitter_id)
		r.set_next_receptacle_id_from_list(rids)

		self.splitter_ids.append(splitter_id)
		del(r_id)
		for r_id in rids:
			r1 = sp.get_receptacle_by_id(r_id)
			if None == r1:
				print('Support.add_splitter sp.get_receptacle_by_id returned None for r1. r_id:{0}, rids:{1}'.format(r_id, rids))
			self.empty_receptacle_ids.append(r_id)

		if True == DEBUG:
			print('Support.add_splitter(). Final empty_receptacle_ids:{0}'.format(self.empty_receptacle_ids))
			print('Support.add_splitter(). Final full_receptacle_ids:{0}'.format(self.full_receptacle_ids))

		return r

	def is_panel_overloaded(self):
		res = (self.e_model.get_amp_load() > self.e_model.get_amp_rating())
		r = Results()
		r.set_object_id(res)
		return r

	def is_breaker_overloaded(self, breaker_id):
		b = self.e_model.get_breaker_by_id(breaker_id)
		too_much_amp_load = (b.get_amp_load() > (0.8 * b.get_amp_rating()))

		outlet_count = b.get_count_outlets()
		too_many_outlets = False
		if b.get_amp_rating() == BREAKER_MODELS['FIFTEEN_AMP']:
			if 8 < outlet_count:
				too_many_outlets = True
		elif b.get_amp_rating() == BREAKER_MODELS['TWENTY_AMP']:
			if 10 < outlet_count:
				too_many_outlets = True

		res = too_many_outlets or too_much_amp_load
		r = Results()
		r.set_object_id(res)
		return r

	def is_outlet_overloaded(self, outlet_id):
		o = self.e_model.get_outlet_by_id(outlet_id)
		total_amp_load = o.get_amp_load()
		amp_rating = (0.8 * o.get_amp_rating())
		max_amp_load = o.get_max_receptacle_amp_load()

		too_much_total_amp_load = (total_amp_load > amp_rating)
		too_much_amp_load_one_receptacle = (max_amp_load > amp_rating)
		res = too_much_total_amp_load or too_much_amp_load_one_receptacle
		if True == DEBUG:
			print('Support.is_outlet_overloaded() total_amp_load:{0}, max_amp_load:{1}, amp_rating:{2} => {3}'.format(total_amp_load, max_amp_load, amp_rating, res))
		r = Results()
		r.set_object_id(res)
		return r


	def is_splitter_overloaded(self, splitter_id):
		sp = self.e_model.get_splitter_by_id(splitter_id)
		res = False
		if None != sp:
			amp_rating = (0.8 * sp.get_amp_rating())
			total_amp_load = sp.get_amp_load()
			max_amp_load = sp.get_max_receptacle_amp_load()

			too_much_total_amp_load = (total_amp_load > amp_rating)
			too_much_amp_load_one_receptacle = (max_amp_load > amp_rating)
			res = too_much_total_amp_load or too_much_amp_load_one_receptacle
			if True == DEBUG:
				print('Support.is_splitter_overloaded() total_amp_load:{0}, max_amp_load:{1}, amp_rating:{2} => {3}'.format(total_amp_load, max_amp_load, amp_rating, res))
		r = Results()
		r.set_object_id(res)
		return r

	def is_light_string_overloaded(self, light_string_id):
		ls = self.e_model.get_light_string_by_id(light_string_id)
		res = False
		if None != ls:
			total_amp_load = ls.get_amp_load()
			amp_rating = ls.get_amp_rating()
			res = (total_amp_load > amp_rating)
			if True == DEBUG:
				print('Support.is_light_string_overloaded() total_amp_load:{0} > amp_rating:{1} => {2}'.format(total_amp_load, amp_rating, res))
		r = Results()
		r.set_object_id(res)
		return r

	def is_receptacle_overloaded(self, receptacle_id):
		receptacle = self.e_model.get_receptacle_by_id(receptacle_id)
		total_amp_load = receptacle.get_amp_load()
		amp_rating = receptacle.get_amp_rating()
		res = (total_amp_load > amp_rating)
		if True == DEBUG:
			print('Support.is_receptacle_overloaded() total_amp_load:{0} > amp_rating:{1} => {2}'.format(total_amp_load, amp_rating, res))

		r = Results()
		r.set_object_id(res)
		return r
