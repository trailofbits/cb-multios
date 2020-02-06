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
from support import Support

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))

def random_digits(a, b):
    chars = string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))


class GrizLight(Actions):

	DEBUG = False
	DEBUG_ERR = DEBUG or False
	DEBUG_FUNC = DEBUG or False
	DEBUG_INIT = DEBUG or False
	DEBUG_ADD_BREAKER = DEBUG or False
	DEBUG_ADD_OUTLET = DEBUG or False
	DEBUG_ADD_LIGHT_STRING = DEBUG or False
	DEBUG_ADD_SPLITTER = DEBUG or False
	DEBUG_PANEL_OVERLOADED = DEBUG or False
	DEBUG_BREAKER_OVERLOADED = DEBUG or False
	DEBUG_OUTLET_OVERLOADED = DEBUG or False
	DEBUG_SPLITTER_OVERLOADED = DEBUG or False
	DEBUG_LIGHT_STRING_OVERLOADED = DEBUG or False
	DEBUG_RECEPTACLE_OVERLOADED = DEBUG or False

	def start(self):
		self.state['m'] = Support()
		self.state['created'] = False
		self.state['invalid_model_id'] = False
		self.state['invalid_target_id'] = False
		self.state['receptacle_full'] = False
		self.state['have_splitter'] = False
		self.state['splitter_receptacle_ids'] = []
		self.state['examine_count'] = 0

	def _recv_error(self, error_name):
		expected = self.state['m'].pack_error(error_name)
		self.read(length=len(expected), expect=expected)
		if True == self.DEBUG_ERR:
			print('exiting due to {0}'.format(error_name))


	def _process_nonce(self):
		nonce = Variable('nonce')
		nonce.set_slice(0, None)
		self.read(length=8, assign=nonce)
		if self.chance(0.001):
			cmd = self.state['m'].pack_single_uint32(0xAAAA)
			cmd += self.state['m'].pack_single_uint32(0xBBBB)
			self.write(cmd)
			self._recv_error('ERR_INVALID_NONCE')
			if self.DEBUG_ERR:
				print('exiting due to incorrect nonce.')
			return -1
		else:
			self.write(nonce)
			return 0

	def _send_command(self, command_name):
		if self.DEBUG_FUNC:
			print('-- _send_command {0}--'.format(command_name))

		if self.chance(0.001):
			cmd = self.state['m'].pack_command('BAD')
			self.write(cmd)
			self._recv_error('ERR_INVALID_COMMAND')
			if self.DEBUG_ERR:
				print('exiting due to BAD command.')
			return -1
		else:
			cmd = self.state['m'].pack_command(command_name)
			self.write(cmd)
			return 0

	def _send_mode(self, mode_name):
		if self.DEBUG_FUNC:
			print('-- _send_mode {0}--'.format(mode_name))

		if self.chance(0.001):
			mode = self.state['m'].pack_mode('BAD')
			self.write(mode)
			self._recv_error('ERR_INVALID_MODE')
			if self.DEBUG_ERR:
				print('exiting due to BAD mode.')
			return -1
		else:
			mode = self.state['m'].pack_mode(mode_name)
			self.write(mode)
			return 0

	def _send_model_id(self, model_name, component_type):
		if self.DEBUG_FUNC:
			print('-- _send_model_id {0}--'.format(model_name))

		if self.chance(0.001):
			model = self.state['m'].pack_model('BAD', component_type)
			self.write(model)
			self.state['invalid_model_id'] = True
		else:
			model = self.state['m'].pack_model(model_name, component_type)
			self.write(model)
		return 0

	def _send_target_id(self, target_id):
		if self.DEBUG_FUNC:
			print('-- _send_target_id {0}--'.format(target_id))

		target = self.state['m'].pack_target(target_id)
		self.write(target)
		return 0

	def _get_random_model_name(self, component_type):
		model_list = self.state['m'].get_list_valid_models(component_type)
		# idx = randint(0, len(model_list)-1)
		# return model_list[idx]
		return model_list[0]

	def _get_random_valid_breaker_id(self):
		b_count = self.state['m'].get_breaker_count()
		if True == self.DEBUG_FUNC:
			print('_get_random_valid_breaker_id - breaker count:{0}'.format(b_count))
		if 0 == b_count:
			self.state['invalid_target_id'] = True
			return b_count
		elif 1 == b_count:
			return b_count - 1
		else:
			# return randint(0, b_count - 1)
			return 0

	def _get_valid_receptacle_id(self, max=False, min=False):
		r_id = 0
		if True == max:
			r_id = self.state['m'].get_max_empty_receptacle_id()
		elif True == min:
			r_id = self.state['m'].get_min_empty_receptacle_id()
		elif self.chance(0.9):
			r_id = self.state['m'].get_random_empty_receptacle_id()
		else:
			r_id = self.state['m'].get_random_full_receptacle_id()
			self.state['receptacle_full'] = True

		if 0 == r_id:
			self.state['invalid_target_id'] = True
		return r_id

	def _get_min_valid_outlet_id(self):
		return self.state['m'].get_min_valid_outlet_id()

	def _get_min_valid_splitter_id(self):
		return self.state['m'].get_min_valid_splitter_id()

	def _get_min_valid_light_string_id(self):
		return self.state['m'].get_min_valid_light_string_id()

	def _recv_results(self, results):
		if self.DEBUG_FUNC:
			print('_recv_results Results: object_id:{0}, receptacle_ids:{1}, receptacle_cnt:{2}'.format(results.get_object_id(), list(results.get_receptacle_id_list()), results.get_receptacle_ids_assigned_count()))
		expected = self.state['m'].pack_results(results)
		self.read(length=len(expected), expect=expected)

		# add a couple of valid receptacle id's that can be used to hold light strings before we bail.
		r_id_list = results.get_receptacle_id_list()
		r_count = results.get_receptacle_ids_assigned_count()
		for idx in range(r_count):
			self.state['splitter_receptacle_ids'].append(r_id_list[idx])


	def build_finished(self):
		pass

	def cmd_init_panel(self):
		if self._process_nonce() < 0:
			return -1
		if self._send_mode('BUILD') < 0:
			return -1

		if self._send_command('B_CMD_INIT_PANEL') < 0:
			return -1

		model_name = self._get_random_model_name('LOAD_CENTER')
		self._send_model_id(model_name, 'LOAD_CENTER')

		if True == self.state['m'].is_model_created():
			self._recv_error('ERR_E_MODEL_EXISTS')
			return -1

		elif True == self.state['invalid_model_id']:
			self._recv_error('ERR_INVALID_MODEL_ID')
			return -1

		else:
			self.state['m'].init_panel(model_name)
			if True == self.DEBUG_INIT:
				print('cmd_init_panel() added panel: {0}'.format(model_name))

	def cmd_add_breaker(self):
		# don't want valid receptacle_ids on outlets added after a splitter, else trigger vuln -> segfault
		if True == self.state['have_splitter']:
			return -1

		if self._process_nonce() < 0:
			return -1
		if self._send_mode('BUILD') < 0:
			return -1

		if self._send_command('B_CMD_ADD_BREAKER') < 0:
			return -1

		model_name = self._get_random_model_name('BREAKER')
		self._send_model_id(model_name, 'BREAKER')

		if False == self.state['m'].is_model_created():
			self._recv_error('ERR_E_MODEL_NOT_EXISTS')
			return -1

		elif True == self.state['m'].is_panel_full():
			self._recv_error('ERR_BREAKER_SPACES_FULL')
			return -1

		elif True == self.state['invalid_model_id']:
			self._recv_error('ERR_INVALID_MODEL_ID')
			return -1

		else:
			if True == self.DEBUG_ADD_BREAKER:
				print('cmd_add_breaker() added breaker: {0}'.format(model_name))
			results = self.state['m'].add_breaker(model_name)
			self._recv_results(results)

	def cmd_add_outlet(self):
		# don't want valid receptacle_ids on outlets added after a splitter, else trigger vuln -> segfault
		if True == self.state['have_splitter']:
			return -1

		if self._process_nonce() < 0:
			return -1
		if self._send_mode('BUILD') < 0:
			return -1

		if self._send_command('B_CMD_ADD_OUTLET') < 0:
			return -1

		model_name = ''
		breaker_id = self._get_random_valid_breaker_id()

		if self.chance(0.1):
			model_name = 'TWENTY_AMP'
		else:
			model_name = 'FIFTEEN_AMP'

		self._send_model_id(model_name, 'OUTLET')
		self._send_target_id(breaker_id)

		if True == self.DEBUG_ADD_OUTLET:
			print('cmd_add_outlet - {0} outlet on breaker {1}.'.format(model_name, breaker_id))

		if False == self.state['m'].is_model_created():
			self._recv_error('ERR_E_MODEL_NOT_EXISTS')
			return -1

		elif True == self.state['invalid_target_id']:
			self._recv_error('ERR_INVALID_BREAKER_ID')
			return -1

		elif True == self.state['invalid_model_id']:
			self._recv_error('ERR_INVALID_MODEL_ID')
			return -1

		elif True == self.state['m'].outlet_amps_exceed_breaker_amps(model_name, breaker_id):
			self._recv_error('ERR_OUTLET_AMPS_EXCEED_BREAKER_AMPS')
			return -1

		else:
			results = self.state['m'].add_outlet(model_name, breaker_id)
			if True == self.DEBUG_ADD_OUTLET:
				print('cmd_add_outlet() added outlet: {0}'.format(model_name))
			self._recv_results(results)

	def cmd_add_light_string(self):
		if self._process_nonce() < 0:
			return -1
		if self._send_mode('BUILD') < 0:
			return -1

		if self._send_command('B_CMD_ADD_LIGHT_STRING') < 0:
			return -1

		model_name = self._get_random_model_name('LIGHT_STRING')
		receptacle_id = 0
		# # artifically bail if this will cause a search beyond the base splitter, else it'll trigger vuln -> segfault
		if True == self.state['have_splitter']:
			if 0 < len(self.state['splitter_receptacle_ids']):
				receptacle_id = self.state['splitter_receptacle_ids'].pop()
			else:
				if self.DEBUG_ERR:
					print('cmd_add_light_string() - exit due to receptacle_id > splitters connection point.')
				return -1
		else:
			receptacle_id = self._get_valid_receptacle_id(min=True)

		self._send_model_id(model_name, 'LIGHT_STRING')
		self._send_target_id(receptacle_id)

		if True == self.DEBUG_ADD_LIGHT_STRING:
			print('cmd_add_light_string - {0} light string on receptacle_id {1}.'.format(model_name, receptacle_id))

		if False == self.state['m'].is_model_created():
			self._recv_error('ERR_E_MODEL_NOT_EXISTS')
			return -1

		elif True == self.state['invalid_target_id']:
			self._recv_error('ERR_INVALID_RECEPTACLE_ID')
			return -1

		elif True == self.state['receptacle_full']:
			self._recv_error('ERR_RECEPTACLE_FULL')
			return -1

		elif True == self.state['invalid_model_id']:
			self._recv_error('ERR_INVALID_MODEL_ID')
			return -1

		else:
			results = self.state['m'].add_light_string(model_name, receptacle_id)
			if True == self.DEBUG_ADD_LIGHT_STRING:
				print('cmd_add_light_string() added light string: {0} to receptacle: {1}'.format(model_name, receptacle_id))
			self._recv_results(results)


	def cmd_add_splitter(self):
		# more than 1 splitter will trigger vuln => segfault
		if True == self.state['have_splitter']:
			return -1
		if self._process_nonce() < 0:
			return -1
		if self._send_mode('BUILD') < 0:
			return -1

		if self._send_command('B_CMD_ADD_SPLITTER') < 0:
			return -1

		model_name = self._get_random_model_name('SPLITTER')
		receptacle_id = self._get_valid_receptacle_id(max=True)
		self._send_model_id(model_name, 'SPLITTER')
		self._send_target_id(receptacle_id)

		if True == self.DEBUG_ADD_SPLITTER:
			print('cmd_add_splitter - {0} splitter on receptacle_id {1}.'.format(model_name, receptacle_id))

		if False == self.state['m'].is_model_created():
			self._recv_error('ERR_E_MODEL_NOT_EXISTS')
			return -1

		elif True == self.state['invalid_target_id']:
			self._recv_error('ERR_INVALID_RECEPTACLE_ID')
			return -1

		elif True == self.state['receptacle_full']:
			self._recv_error('ERR_RECEPTACLE_FULL')
			return -1

		elif True == self.state['invalid_model_id']:
			self._recv_error('ERR_INVALID_MODEL_ID')
			return -1

		else:
			results = self.state['m'].add_splitter(model_name, receptacle_id)
			if True == self.DEBUG_ADD_SPLITTER:
				print('cmd_add_splitter() added splitter: {0} to receptacle: {1}'.format(model_name, receptacle_id))
			self._recv_results(results)
			self.state['have_splitter'] = True




	def cmd_panel_overloaded(self):
		# no need to repeated loop over the same functions.
		if self.state['examine_count'] > 10:
			return -1

		if self._process_nonce() < 0:
			return -1

		if self._send_mode('EXAMINE') < 0:
			return -1

		if self._send_command('E_CMD_PANEL_OVERLOADED') < 0:
			return -1

		results = self.state['m'].is_panel_overloaded()
		if True == self.DEBUG_PANEL_OVERLOADED:
			print('cmd_panel_overloaded() ret:{0}'.format(results.get_object_id()))
		self._recv_results(results)
		self.state['examine_count'] += 1



	def cmd_breaker_overloaded(self):
		# no need to repeated loop over the same functions.
		if self.state['examine_count'] > 10:
			return -1

		if self._process_nonce() < 0:
			return -1

		if self._send_mode('EXAMINE') < 0:
			return -1

		if self._send_command('E_CMD_BREAKER_OVERLOADED') < 0:
			return -1

		breaker_id = self._get_random_valid_breaker_id()
		self._send_target_id(breaker_id)

		results = self.state['m'].is_breaker_overloaded(breaker_id)
		if True == self.DEBUG_BREAKER_OVERLOADED:
			print('cmd_breaker_overloaded() ret:{0}'.format(results.get_object_id()))
		self._recv_results(results)
		self.state['examine_count'] += 1


	def cmd_outlet_overloaded(self):
		# no need to repeated loop over the same functions.
		if self.state['examine_count'] > 10:
			return -1

		if self._process_nonce() < 0:
			return -1

		if self._send_mode('EXAMINE') < 0:
			return -1

		if self._send_command('E_CMD_OUTLET_OVERLOADED') < 0:
			return -1

		outlet_id = self._get_min_valid_outlet_id()
		self._send_target_id(outlet_id)

		results = self.state['m'].is_outlet_overloaded(outlet_id)
		if True == self.DEBUG_OUTLET_OVERLOADED:
			print('cmd_outlet_overloaded() ret:{0}'.format(results.get_object_id()))
		self._recv_results(results)
		self.state['examine_count'] += 1

	def cmd_splitter_overloaded(self):
		# no need to repeated loop over the same functions.
		if self.state['examine_count'] > 10:
			return -1

		if self._process_nonce() < 0:
			return -1

		if self._send_mode('EXAMINE') < 0:
			return -1

		if self._send_command('E_CMD_SPLITTER_OVERLOADED') < 0:
			return -1

		splitter_id = self._get_min_valid_splitter_id()
		self._send_target_id(splitter_id)

		results = self.state['m'].is_splitter_overloaded(splitter_id)
		if True == self.DEBUG_SPLITTER_OVERLOADED:
			print('cmd_splitter_overloaded() ret:{0}'.format(results.get_object_id()))
		self._recv_results(results)
		self.state['examine_count'] += 1

	def cmd_light_string_overloaded(self):
		# no need to repeated loop over the same functions.
		if self.state['examine_count'] > 10:
			return -1

		if self._process_nonce() < 0:
			return -1

		if self._send_mode('EXAMINE') < 0:
			return -1

		if self._send_command('E_CMD_LIGHT_STRING_OVERLOADED') < 0:
			return -1

		light_string_id = self._get_min_valid_light_string_id()
		self._send_target_id(light_string_id)

		results = self.state['m'].is_light_string_overloaded(light_string_id)
		if True == self.DEBUG_LIGHT_STRING_OVERLOADED:
			print('cmd_light_string_overloaded() ret:{0}'.format(results.get_object_id()))
		self._recv_results(results)
		self.state['examine_count'] += 1

	def cmd_receptacle_overloaded(self):
		# no need to repeated loop over the same functions.
		if self.state['examine_count'] > 10:
			return -1

		if self._process_nonce() < 0:
			return -1

		if self._send_mode('EXAMINE') < 0:
			return -1

		if self._send_command('E_CMD_RECEPTACLE_OVERLOADED') < 0:
			return -1

		receptacle_id = self._get_valid_receptacle_id()
		self._send_target_id(receptacle_id)

		results = self.state['m'].is_receptacle_overloaded(receptacle_id)
		if True == self.DEBUG_RECEPTACLE_OVERLOADED:
			print('cmd_receptacle_overloaded() ret:{0}'.format(results.get_object_id()))
		self._recv_results(results)
		self.state['examine_count'] += 1


