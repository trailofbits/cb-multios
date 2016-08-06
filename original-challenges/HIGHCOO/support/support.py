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

# random gen functions
def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))

def random_digits(a, b):
    chars = string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))


COMMANDS = {
    'CMD_ADD_HAIKU': 1492,
    'CMD_GET_HAIKU_BY_ID': 1999,
    'CMD_GET_HAIKU_RANDOM': 200042,
    'CMD_GET_HAIKU_COUNT': 1210000,
    'CMD_GET_HAIKU_IDS': 8675309,
	'BAD': 13,
}

INIT_HAIKU_ID = 424242

EGG_ID = 31337
EGG_HAIKU = " from within HIGHCOO\x07 new Haiku every login\x07 a warm thought engulfs\x07"

class Support(object):

	def __init__(self):
		self.haiku_list = []
		self.next_haiku_id = INIT_HAIKU_ID

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

	def pack_single_uint16(self, uint16_val):
		'''
		Pack unsigned int16
		'''
		return struct.pack('H', uint16_val)

	def pack_single_int16(self, int16_val):
		'''
		Pack signed int16
		'''
		return struct.pack('h', int16_val)

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


	# specific helper functions
	def generate_random_haiku(self, max_line_len, max_total_len, invalid=False):
		if True == invalid:
			return random_string(max_line_len, max_line_len)

		low_len = 2			
		line1 = random_string(low_len, max_line_len - 1)
		line1 += '\x07'
		line2 = random_string(low_len, max_line_len - 1)
		line2 += '\x07'
		line3 = random_string(low_len, max_line_len - 1)
		line3 += '\x07'

		haiku = line1 + line2 + line3
		if max_total_len < len(haiku):
			return self.generate_random_haiku(max_line_len, max_total_len, invalid)
		else:
			return haiku

	def generate_vuln_haiku(self, line_len, total_haiku_len):
		haiku = ''
		while 0 < total_haiku_len:
			haiku += random_string(line_len - 1, line_len - 1)
			haiku += '\x07'
			total_haiku_len -= (line_len - 1)

		return haiku

	def get_next_haiku_id(self):
		haiku_id = 0
		haiku_id = self.next_haiku_id
		self.next_haiku_id += 1
		return haiku_id

	def get_haiku_list_len(self):
		return len(self.haiku_list)

	def add_haiku(self, haiku_str):
		haiku = {'id': self.get_next_haiku_id(),
				 'length': len(haiku_str),
				 'content': haiku_str}
		self.haiku_list.append(haiku)
		return haiku['id']

	def get_haiku(self, idnum=0):
		haiku = {}
		count = len(self.haiku_list)
		if EGG_ID == idnum:				#get easter egg haiku
			haiku['id'] = EGG_ID
			haiku['length'] = len(EGG_HAIKU)
			haiku['content'] = EGG_HAIKU
		elif 0 == idnum and 0 < count: 	#get random haiku
			idx = randint(1, count) - 1
			haiku = self.haiku_list[idx]
		else: 							#get haiku with idnum
			for h in self.haiku_list:
				if idnum == h['id']:
					haiku = h
					break
		# invalid idnum != 0 will return {}
		return haiku

	def get_haiku_id_list(self):
		haiku_ids = []
		for h in self.haiku_list:
			haiku_ids.append(h['id'])
		return haiku_ids



