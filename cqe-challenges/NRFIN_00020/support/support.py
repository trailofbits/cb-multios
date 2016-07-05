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

from common import ERRORS, DEBUG



COMMANDS = {
    'CMD_TO_SYLLABLES': 804619,
    'CMD_TO_NOTES': 1128809,
	'BAD': 13,
}


class Support(object):

	def __init__(self):
		self.notes = ['C', 'D', 'E', 'F', 'G', 'A', 'B', '_']
		self.syllables = ['Ut', 'Re', 'Mi', 'Fa', 'Sol', 'La', 'Si', '___']

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

	def pack_single_char(self, char_val):
		'''
		Pack a single character.
		'''
		return struct.pack('c', char_val)

	def pack_single_string(self, str_val):
		'''
		Pack a single string.
		'''
		return struct.pack('{0}s'.format(len(str_val)), str_val)

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

	def pack_as_notes(self, id_list):
		'''
		Pack the sequence of notes that corresponds to each id in the id_list.

		id_list is a list of indexes in the notes list.
		'''
		r = ''
		for note_id in id_list:
			r += self.pack_single_char(self.notes[note_id])

		return r

	def pack_as_syllables(self, id_list):
		'''
		Pack the sequence of syllables that corresponds to each id in the id_list.

		id_list is a list of indexes in the syllables list.
		'''
		r = ''
		for syllable_id in id_list:
			r += self.pack_single_string(self.syllables[syllable_id])

		return r

	def generate_random_harmony_as_list(self, num_bytes, harmony_type, include_invalid=False, no_sol=False):
		'''
		Create a list with a random sequence of the numbers 0 thru 6, which are id's
		that can be used as indices into either the syllables or notes lists.

		num_bytes is the max bytes that this list should convert into if it is converted
		into syllables or notes (harmony_type)
		'''
		harmony = []
		bytes_remaining = num_bytes
		while True:
			idx = randint(0, 6)
			if True == no_sol and 4 == idx:
				continue
			sz = 0
			if 'syllables' == harmony_type:
				sz = len(self.syllables[idx])
			elif 'notes' == harmony_type:
				sz = len(self.notes[idx])

			bytes_remaining -= sz
			if 0 > bytes_remaining:
				break
			harmony.append(idx)

		if True == include_invalid:
			idx = randint(0, len(harmony)-1)
			harmony[idx] = 7
			idx = randint(0, idx)
			harmony[idx] = 7

		return harmony


