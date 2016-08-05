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

def pack_results(r):
	'''
	Need to pack the components of results dict in the order of the c struct:
    # unsigned short chars;
    # unsigned short words;
    # unsigned short sentences;
    # unsigned short paragraphs;

    # unsigned short printable;
    # unsigned short non_printable;

    # unsigned short letters;
    # unsigned short numbers;
    # unsigned short symbols;

    # unsigned short session_id;

    # r = {'chars': 0, 'words': 0,
    #     'sentences': 0, 'paragraphs': 0, 'printable': 0,
    #     'non_printable': 0, 'letters': 0, 'numbers': 0, 'symbols': 0
    #	  'session_id': 0}
	'''
	return struct.pack('H'*9, r['chars'], r['words'], r['sentences'], r['paragraphs'],
								r['printable'], r['non_printable'],
								r['letters'], r['numbers'], r['symbols']) + pack_single_uint16(r['session_id'])

####
def is_printable(ch):
	'''
	Is ch ASCII printable char?
	'''
	return is_symbol(ch) or is_letter(ch) or is_digit(ch)

def is_non_printable(ch):
	'''
	Is ch not ASCII printable char?
	'''
	if not is_printable(ch):
		return True
	else:
		return False

def is_lower(ch):
	'''
	Is ch an ASCII lowercase char?
	'''
	return 0x61 <= ch <= 0x7A

def is_upper(ch):
	'''
	Is ch an ASCII uppercase char?
	'''
	return 0x41 <= ch <= 0x5A

def is_letter(ch):
	'''
	Is ch a letter?
	'''
	return is_lower(ch) or is_upper(ch)

def is_symbol(ch):
	'''
	Is ch a symbol?
	'''
	if 0x21 <= ch <= 0x2F or \
		0x3A <= ch <= 0x40 or \
		0x5B <= ch <= 0x60 or \
		0x7B <= ch <= 0x7E:
		return True
	else:
		return False

def is_digit(ch):
	'''
	Is ch a digit?
	'''
	return 0x30 <= ch <= 0x39

def is_word_end_char(ch):
    if ' ' == ch or True == is_sentence_end_char(ch):
        return True
    else:
        return False

def is_sentence_end_char(ch):
    if '.' == ch or '!' == ch or '?' == ch:
        return True
    else:
        return False

def is_paragraph_end_char(ch):
    if '\n' == ch:
        return True
    else:
        return False
