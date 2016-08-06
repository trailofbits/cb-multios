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

from common import DEBUG

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
    'OPEN_VALVE': 12,
    'CLOSE_VALVE': 13,
    'NO_CHANGE': 14,
	'SET_IN_SERVICE': 15,
	'SET_OUT_OF_SERVICE': 16,
	'SET_END_OF_LIFE': 17,
	'BAD': 18,
}

#### Protocol Funcs ####

def pack_single_uint32(uint32_val):
	'''
	Pack unsigned int32
	'''
	return struct.pack('I', uint32_val)

def pack_single_int32(int32_val):
	'''
	Pack signed int32
	'''
	return struct.pack('i', int32_val)

def pack_single_uint16(uint16_val):
	'''
	Pack unsigned int16
	'''
	return struct.pack('H', uint16_val)

def pack_single_int16(int16_val):
	'''
	Pack signed int16
	'''
	return struct.pack('h', int16_val)

def pack_single_uint8(uint8_val):
	'''
	Pack unsigned uint8
	'''
	return struct.pack('B', uint8_val)

def pack_single_int8(int8_val):
	'''
	Pack signed int8
	'''
	return struct.pack('b', int8_val)

def pack_single_char(char_val):
	'''
	Pack a single character.
	'''
	return struct.pack('c', char_val)

def pack_single_string(str_val):
	'''
	Pack a single string.
	'''
	return struct.pack('{0}s'.format(len(str_val)), str_val)

def pack_command(command):
	'''
	command is uint8_t
	'''
	return pack_single_uint8(COMMANDS[command])

def pack_error(err_name):
	'''
	err_name is int8_t
	'''
	return pack_single_int8(ERRORS[err_name])

def pack_tank(tank):
	'''
	Pack tank values into a single string

	struct tank {
		uint8_t id;				// ID number of tank
		uint8_t fill_rate; 		// amt of h2o added per round
		uint8_t drain_rate; 	// amt of h2o drained per round
		uint8_t valve_position; // position of valve
		uint8_t capacity; 		// qty of h2o tank can hold
		uint8_t level; 			// qty of h2o in tank
		uint8_t status; 		// status of tank
		uint8_t eol; 			// make struct into even mult of 4 bytes
		struct h2o *contents[];	// array of h2o ptrs
	};
	'''
	return struct.pack('{0}'.format(8 * 'B'),
						tank.get_id(),
						tank.get_fill_rate(),
						tank.get_drain_rate(),
						tank.get_valve_position(),
						tank.get_capacity(),
						tank.get_level(),
						tank.get_status(),
						tank.is_end_of_life())


