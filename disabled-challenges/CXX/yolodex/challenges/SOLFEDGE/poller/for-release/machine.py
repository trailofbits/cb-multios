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


class Solfedge(Actions):

	DEBUG = False
	DEBUG_ERR = DEBUG or False
	DEBUG_FUNC = DEBUG or False
	DEBUG_INIT = DEBUG or False


	MAX_SYLLABLES_BYTES = 4096
	MAX_NOTES_BYTES = 2048
	BUFFER_LEN = 4096
	NUM_BYTES_MIN = 5
	NUM_BYTES_MAX = 1500

	def start(self):
		self.state['m'] = Support()
		self.state['invalid'] = False
		self.state['no_sol'] = False


	def _send_command(self, command_name):
		if self.DEBUG_FUNC:
			print('-- _send_command-- {0}'.format(command_name))

		if self.chance(0.01):
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

	def _send_bytes_count(self, bytes_count, bytes_count_type):
		if self.DEBUG_FUNC:
			print('-- _send_bytes_count-- {0}'.format(bytes_count))

		# bytes_count of 0, results in ERR_NO_NOTES or ERR_NO_SYLLABLES
		if self.chance(0.01):
			bytes_count = 0
			val = self.state['m'].pack_single_uint32(bytes_count)
			self.write(val)
			if 'notes' == bytes_count_type:
				self._recv_error('ERR_NO_NOTES')
			elif 'syllables' == bytes_count_type:
				self._recv_error('ERR_NO_SYLLABLES')
			if self.DEBUG_ERR:
				print('exiting due to 0 bytes_count.')
			return -1
		elif self.chance(0.01):
			# bytes_count_type of 'notes', then bytes_count => MAX_NOTES_BYTES results in ERR_TOO_MANY_NOTES
			if 'notes' == bytes_count_type:
				bytes_count = self.MAX_NOTES_BYTES + randint(2, 10)
				val = self.state['m'].pack_single_uint32(bytes_count)
				self.write(val)
				self._recv_error('ERR_TOO_MANY_NOTES')
				if self.DEBUG_ERR:
					print('exiting due to too many notes.')
				
			# bytes_count_type of 'syllables', then bytes_count => MAX_SYLLABLES_BYTES results in ERR_TOO_MANY_SYLLABLES
			elif 'syllables' == bytes_count_type:
				bytes_count = self.MAX_SYLLABLES_BYTES + randint(2, 10)
				val = self.state['m'].pack_single_uint32(bytes_count)
				self.write(val)
				self._recv_error('ERR_TOO_MANY_SYLLABLES')
				if self.DEBUG_ERR:
					print('exiting due to too many syllables.')
			return -1
		else:
			val = self.state['m'].pack_single_uint32(bytes_count)
			self.write(val)
		return 0

	def _send_byte_count_and_notes(self, note_id_list):
		if self.DEBUG_FUNC:
			print('-- _send_byte_count_and_notes-- \n\t{0}'.format(note_id_list))

		val = self.state['m'].pack_as_notes(note_id_list)

		if 0 > self._send_bytes_count(len(val), 'notes'):
			return -1

		self.write(val)
		if self.DEBUG_FUNC:
			print('-- _send_byte_count_and_notes-- sent {0} bytes\n\t{1}'.format(len(val), val))

		return 0

	def _send_byte_count_and_syllables(self, syllable_id_list):
		if self.DEBUG_FUNC:
			print('-- _send_byte_count_and_syllables-- ids:\n\t->{0}<-'.format(syllable_id_list))

		val = self.state['m'].pack_as_syllables(syllable_id_list)

		if 0 > self._send_bytes_count(len(val), 'syllables'):
			return -1

		self.write(val)
		if self.DEBUG_FUNC:
			print('-- _send_byte_count_and_syllables-- sent {0} bytes\n\t{1}'.format(len(val), val))

		return 0

	def _recv_results(self, result_type, result_id_list):
		if self.DEBUG_FUNC:
			print('-- _recv_results-- \n\t{0} {1}\n\t ->{2}<-'.format(len(result_id_list), result_type, result_id_list))
		expected = ''
		if 'notes' == result_type:
			expected += self.state['m'].pack_as_notes(result_id_list)
		elif 'syllables' == result_type:
			expected += self.state['m'].pack_as_syllables(result_id_list)

		self.read(length=len(expected), expect=expected)
		if self.DEBUG_FUNC:
			print('-- _recv_results-- received {0} bytes\n\t->{1}<-'.format(len(expected), expected))

	def _recv_error(self, error_name):
		expected = self.state['m'].pack_error(error_name)
		self.read(length=len(expected), expect=expected)
		if True == self.DEBUG_ERR:
			print('exiting due to {0}'.format(error_name))


	def _generate_random_harmony(self, num_bytes, harmony_type, include_invalid=False, no_sol=False):
		return self.state['m'].generate_random_harmony_as_list(num_bytes, harmony_type, include_invalid=include_invalid, no_sol=no_sol)


	def to_notes(self):
		if self.DEBUG_FUNC:
			print('- to_notes -')

		num_bytes = randint(self.NUM_BYTES_MIN, self.NUM_BYTES_MAX)
		if self.chance(0.01):
			harmony = self._generate_random_harmony(num_bytes, 'syllables', include_invalid=True)
			self.state['invalid'] = True
		else:
			harmony = self._generate_random_harmony(num_bytes, 'syllables')

		if 0 > self._send_command('CMD_TO_NOTES'):
			return -1

		if 0 > self._send_byte_count_and_syllables(harmony):
			return -1

		if True == self.state['invalid']:
			self._recv_error('ERR_INVALID_SYLLABLE')
			return -1
		else:
			self._recv_results('notes', harmony)

	def to_syllables(self):
		if self.DEBUG_FUNC:
			print('- to_syllables -')

		num_bytes = randint(self.NUM_BYTES_MIN, self.NUM_BYTES_MAX)
		if self.chance(0.01):
			harmony = self._generate_random_harmony(num_bytes, 'notes', include_invalid=True)
			self.state['invalid'] = True
		else:
			harmony = self._generate_random_harmony(num_bytes, 'notes')

		if 0 > self._send_command('CMD_TO_SYLLABLES'):
			return -1

		if 0 > self._send_byte_count_and_notes(harmony):
			return -1

		if True == self.state['invalid']:
			self._recv_error('ERR_INVALID_NOTE')
			return -1
		else:
			self._recv_results('syllables', harmony)

