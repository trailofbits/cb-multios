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
import sys


sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
from support import Support



class HighCoo(Actions):

	DEBUG = False
	DEBUG_ERR = DEBUG or False
	DEBUG_FUNC = DEBUG or False
	DEBUG_INIT = DEBUG or False


	MAX_HAIKU_LINE_LEN = 1362
	MAX_HAIKU_LEN = 4087

	def start(self):
		self.state['m'] = Support()
		self.state['created'] = False
		self.state['invalid'] = False

	def _send_command(self, command_name):
		if self.DEBUG_FUNC:
			print('-- _send_command-- {0}'.format(command_name))

		if self.chance(0.007):
			cmd = self.state['m'].pack_command('BAD')
			self.write(cmd)
			self._recv_error('ERR_INVALID_CMD')
			if self.DEBUG_ERR:
				print('exiting due to BAD command.')
			return -1
		else:
			cmd = self.state['m'].pack_command(command_name)
			self.write(cmd)
			return 0

	def _recv_error(self, error_name):
		expected = self.state['m'].pack_error(error_name)
		self.read(length=len(expected), expect=expected)
		if True == self.DEBUG_ERR:
			print('exiting due to {0}'.format(error_name))

	def add_haiku(self):
		if self.DEBUG_FUNC:
			print('- add_haiku -')

		# send add_haiku command
		if 0 > self._send_command('CMD_ADD_HAIKU'):
			return -1

		haiku = ''

		# send haiku size
		# sending size in the valid range of sizes, that is smaller than
		# the length of the haiku will cause crash, so leave that for POV.
		if self.chance(0.01): # size zero
			cmd = self.state['m'].pack_single_uint16(0)
			self.write(cmd)
			self._recv_error('ERR_INVALID_HAIKU_LEN')
			if self.DEBUG_ERR:
				print('exiting due to zero sized haiku length.')
			return -1
		elif self.chance(0.01): # size too large
			cmd = self.state['m'].pack_single_uint16(self.MAX_HAIKU_LEN + 5)
			self.write(cmd)
			self._recv_error('ERR_INVALID_HAIKU_LEN')
			if self.DEBUG_ERR:
				print('exiting due to over-sized haiku length.')
			return -1
		else:
			cmd = ''
			if self.chance(0.01): #invalid haiku
				haiku = self.state['m'].generate_random_haiku(self.MAX_HAIKU_LINE_LEN,
															self.MAX_HAIKU_LEN, 
															invalid=True)
				cmd = self.state['m'].pack_single_uint16(len(haiku))
				self.state['invalid'] = True

			else:
				haiku = self.state['m'].generate_random_haiku(200, 1000)
				cmd = self.state['m'].pack_single_uint16(len(haiku))

			self.write(cmd)
			self.state['created'] = True

		# send haiku
		packed_haiku = self.state['m'].pack_single_string(haiku)
		self.write(packed_haiku)

		if True == self.state['invalid']:
			self._recv_error('ERR_INVALID_HAIKU')
			if self.DEBUG_ERR:
				print('exiting due to invalid haiku.')
			return -1

		haiku_id = self.state['m'].add_haiku(haiku)
		# recv haiku id
		packed_id = self.state['m'].pack_single_uint32(haiku_id)
		self.read(length=len(packed_id), expect=packed_id)


	def get_haiku_by_id(self):
		if self.DEBUG_FUNC:
			print('- get_haiku_by_id -')

		# send get_haiku_by_id command
		if 0 > self._send_command('CMD_GET_HAIKU_BY_ID'):
			return -1

		if False == self.state['created']:
			self._recv_error('ERR_LIST_NOT_EXIST')
			if self.DEBUG_ERR:
				print('exiting due to haiku list not exiting.')
			return -1

		haiku = ''
		if self.chance(0.008): # easter egg id
			haiku = self.state['m'].get_haiku(idnum=31337)
			cmd = self.state['m'].pack_single_uint32(31337)
			self.write(cmd)
		elif self.chance(0.008): #invalid id
				cmd = self.state['m'].pack_single_uint32(10)
				self.write(cmd)
				if 0 == self.state['m'].get_haiku_list_len():
					self._recv_error('ERR_LIST_EMPTY')
					if self.DEBUG_ERR:
						print('exiting due to haiku list empty.')
					return -1
				else:
					self._recv_error('ERR_INVALID_ID')
					if self.DEBUG_ERR:
						print('exiting due to invalid haiku id.')
					return -1
		else:
			haiku = self.state['m'].get_haiku()
			cmd = self.state['m'].pack_single_uint32(haiku['id'])
			self.write(cmd)
			if 0 == self.state['m'].get_haiku_list_len():
				self._recv_error('ERR_LIST_EMPTY')
				if self.DEBUG_ERR:
					print('exiting due to haiku list empty.')
				return -1

		packed = self.state['m'].pack_single_uint32(haiku['id'])
		self.read(length=len(packed), expect=packed)
		packed = self.state['m'].pack_single_uint16(haiku['length'])
		self.read(length=len(packed), expect=packed)

		## full match
		packed = self.state['m'].pack_single_string(haiku['content'])
		self.read(length=len(packed), expect=packed)

		## regex match
		# content_list = haiku['content'].split('\x07')
		# self.read(length=len(content_list[0]), expect="(.+)", expect_format='pcre')
		# self.read(length=len(content_list[1]), expect="(.+)", expect_format='pcre')
		# self.read(length=len(content_list[2]), expect="(.+)", expect_format='pcre')

	def get_haiku_random(self):
		if self.DEBUG_FUNC:
			print('- get_haiku_random -')

		if 0 > self._send_command('CMD_GET_HAIKU_RANDOM'):
			return -1

		if False == self.state['created']:
			self._recv_error('ERR_LIST_NOT_EXIST')
			if self.DEBUG_ERR:
				print('exiting due to haiku list not exiting.')
			return -1

		if 0 == self.state['m'].get_haiku_list_len():
			self._recv_error('ERR_LIST_EMPTY')
			if self.DEBUG_ERR:
				print('exiting due to haiku list empty.')
			return -1

		# id
		self.read(length=4, expect=r'(.+)', expect_format='pcre')

		# length
		self.read(length=2, expect=r'(.+)', expect_format='pcre')

		# content
		self.read(delim='\x07', expect=r'(.+)', expect_format='pcre')
		self.read(delim='\x07', expect=r'(.+)', expect_format='pcre')
		self.read(delim='\x07', expect=r'(.+)', expect_format='pcre')

	def get_haiku_count(self):
		if self.DEBUG_FUNC:
			print('- get_haiku_count -')

		if 0 > self._send_command('CMD_GET_HAIKU_COUNT'):
			return -1

		if False == self.state['created']:
			self._recv_error('ERR_LIST_NOT_EXIST')
			if self.DEBUG_ERR:
				print('exiting due to haiku list not exiting.')
			return -1

		count = self.state['m'].get_haiku_list_len()
		packed = self.state['m'].pack_single_uint32(count)
		self.read(length=len(packed), expect=packed)

	def get_haiku_ids(self):
		if self.DEBUG_FUNC:
			print('- get_haiku_ids -')

		if 0 > self._send_command('CMD_GET_HAIKU_IDS'):
			return -1

		if False == self.state['created']:
			self._recv_error('ERR_LIST_NOT_EXIST')
			if self.DEBUG_ERR:
				print('exiting due to haiku list not exiting.')
			return -1

		count = self.state['m'].get_haiku_list_len()
		packed = self.state['m'].pack_single_uint32(count)
		self.read(length=len(packed), expect=packed)

		id_list = self.state['m'].get_haiku_id_list()

		packed_list = ''
		for h_id in id_list:
			packed_list += self.state['m'].pack_single_uint32(h_id)

		self.read(length=len(packed_list), expect=packed_list)

	def cmd_done(self):
		pass
