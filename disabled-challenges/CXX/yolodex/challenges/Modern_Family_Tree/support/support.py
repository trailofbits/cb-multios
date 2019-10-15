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
from common import CONFIG


def random_string(length, term=''):
    '''
    Make a string of length containing random letters.

    @length Length of resultant string including the term char.
    @term   String termination char.
    @return String of letters ended with term char.
    '''
    chars = string.letters
    s = "{0}{1}".format(''.join(choice(chars) for _ in range(length - len(term))), term)
    return s

def random_digits(length, term=''):
    '''
    Make a string of length containing random numbers.

    @length Length of resultant string including the term char.
    @term   String termination char.
    @return String of numbers ended with term char.
    '''
    chars = string.digits
    s = "{0}{1}".format(''.join(choice(chars) for _ in range(length - len(term))), term)
    return s

def hexify(byte_str):
    return '\\x'+'\\x'.join(x.encode('hex') for x in byte_str)


#### Protocol Funcs ####
def pack_single_double(val):
	'''
	Pack 8 byte float
	'''
	return struct.pack('d', val)

def pack_single_float(val):
	'''
	Pack 4 byte float
	'''
	return struct.pack('f', val)

def pack_single_uint64(uint64_val):
	'''
	Pack unsigned int64 (unsigned long long)
	'''
	return struct.pack('Q', uint64_val)

def pack_single_int64(int64_val):
	'''
	Pack signed int64 (long long)
	'''
	return struct.pack('q', int64_val)

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
	Pack unsigned int8
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


def unpack_single_uint16(buf, idx):
	'''
	Unpack a single uint16 from buf starting at idx.
	'''
	(res,) = struct.unpack_from('H', buf, idx)
	return res

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
	return 'a' <= ch <= 'z'

def is_upper(ch):
	'''
	Is ch an ASCII uppercase char?
	'''
	return 'A' <= ch <= 'Z'

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

def is_white_space(ch):
	'''
	Is ch a white-space char?
	'''
	if '\r' == ch or \
		'\n' == ch or \
		' ' == ch or \
		'\t' == ch:
		return True
	else:
		return False

def is_digit(ch):
	'''
	Is ch a digit?
	'''
	return '0' <= ch <= '9'

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

## dynamic string termination and line delimiters
def mk_str(astr):
	return "{0}{1}".format(astr, CONFIG['TERM'])

def mk_str_delim(astr):
	return "{0}{1}{2}".format(astr, CONFIG['DELIM'], CONFIG['TERM'])
