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


# COMMANDS = {
#     'CMD_ADD_HAIKU': 1492,
#     'CMD_GET_HAIKU_BY_ID': 1999,
#     'CMD_GET_HAIKU_RANDOM': 200042,
#     'CMD_GET_HAIKU_COUNT': 1210000,
#     'CMD_GET_HAIKU_IDS': 8675309,
# 	'BAD': 13,
# }

TOKENS = {
# // tokens
'END': 0x27,
'START': 0x28,
'FIN': 0x29,
}

TAGS = {
# // tags
'GAME': 0x42,
'PLAYER': 0x43,
'CARDS': 0x44,
'CARD': 0x45,
'SUIT': 0x46,
'RANK': 0x47,
'ERROR': 0x48,
'ID': 0x49,
'DRAW': 0x50,
'GO_FISH': 0x51,
'FISHING': 0x52,
'ASK': 0x53,
'BOOKS': 0x54,
'TURN': 0x55,
'NAME': 0x56,
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
	Pack unsigned int8
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

# def pack_command(command):
# 	'''
# 	command is uint32_t
# 	'''
# 	return pack_single_uint32(COMMANDS[command])

def pack_error(err_name):
	'''
	err_name is int8_t
	'''
	return pack_single_int8(ERRORS[err_name])

def unpack_single_uint8(str_val):
	'''
	Unpack a single uint8
	'''
	return struct.unpack('B', str_val)[0]

def unpack_mult_uint8(str_val):
	 return struct.unpack('{0}B'.format(len(str_val)), str_val)

def serialize_player_name(name):
	c = pack_single_uint8(TOKENS['START'])
	c += pack_single_uint8(TAGS['GAME'])
	c += pack_single_uint8(TAGS['PLAYER'])
	c += pack_single_uint8(TAGS['NAME'])

	c += pack_single_string(name)

	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['FIN'])

	return c

def serialize_cards(card_list):
	c = pack_single_uint8(TOKENS['START'])
	c += pack_single_uint8(TAGS['CARDS'])

	for card in card_list:
		if card != None:
			c += pack_single_uint8(TAGS['CARD'])

			c += pack_single_uint8(TAGS['SUIT'])
			c += pack_single_uint8(card.get_suit())
			c += pack_single_uint8(TOKENS['END'])

			c += pack_single_uint8(TAGS['RANK'])
			c += pack_single_uint8(card.get_rank())
			c += pack_single_uint8(TOKENS['END'])

			c += pack_single_uint8(TOKENS['END'])

	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['FIN'])

	return c

def serialize_cards_vuln(qty = 1, suit = 1, rank = 1):
	c = pack_single_uint8(TOKENS['START'])
	c += pack_single_uint8(TAGS['CARDS'])

	for _ in range(qty):
		c += pack_single_uint8(TAGS['CARD'])

		c += pack_single_uint8(TAGS['SUIT'])
		c += pack_single_uint8(suit)
		c += pack_single_uint8(TOKENS['END'])

		c += pack_single_uint8(TAGS['RANK'])
		c += pack_single_uint8(rank)
		c += pack_single_uint8(TOKENS['END'])

		c += pack_single_uint8(TOKENS['END'])

	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['FIN'])

	return c

def de_serialize_cards(xml_str):
	count = (len(xml_str) - 4) / 8
	# print "len: {0}, count:{1}".format(len(xml_str), count)
	tup = unpack_mult_uint8(xml_str)
	# print tup

	cards = []

	if 0 == count:
		return cards

	card_idx = 2
	while (count > len(cards)):
		cards.append(Card(tup[card_idx + 2], tup[card_idx + 5]))
		card_idx += 8

	return cards

def serialize_draw_request():
	dr = pack_single_uint8(TOKENS['START'])
	dr += pack_single_uint8(TAGS['DRAW'])
	dr += pack_single_uint8(TOKENS['END'])
	dr += pack_single_uint8(TOKENS['FIN'])
	return dr

def serialize_go_fish(qty):
	gf = pack_single_uint8(TOKENS['START'])
	gf += pack_single_uint8(TAGS['GO_FISH'])
	gf += pack_single_uint8(qty)
	gf += pack_single_uint8(TOKENS['END'])
	gf += pack_single_uint8(TOKENS['FIN'])
	return gf

def de_serialize_go_fish(xml_str):
	tup = unpack_mult_uint8(xml_str)
	return tup[2]

def serialize_ask(rank):
	c = pack_single_uint8(TOKENS['START'])
	c += pack_single_uint8(TAGS['ASK'])

	c += pack_single_uint8(TAGS['RANK'])
	c += pack_single_uint8(rank)
	c += pack_single_uint8(TOKENS['END'])

	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['FIN'])

	return c

def de_serialize_ask(xml_str):
	tup = unpack_mult_uint8(xml_str)
	return tup[3]

def serialize_fishing():
	gf = pack_single_uint8(TOKENS['START'])
	gf += pack_single_uint8(TAGS['FISHING'])
	gf += pack_single_uint8(TOKENS['END'])
	gf += pack_single_uint8(TOKENS['FIN'])
	return gf

def de_serialize_fishing(xml_str):
	tup = unpack_mult_uint8(xml_str)
	if ((START == tup[0]) and (FISHING == tup[1]) and \
		(END == tup[2]) and (FIN == tup[3])):
		return True
	else:
		return False

def serialize_books(count):
	c = pack_single_uint8(TOKENS['START'])
	c += pack_single_uint8(TAGS['BOOKS'])
	c += pack_single_uint8(count)
	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['FIN'])
	return c

def de_serialize_books(xml_str):
	tup = unpack_mult_uint8(xml_str)
	return tup[2]

def serialize_turn(player_id):
	c = pack_single_uint8(TOKENS['START'])
	c += pack_single_uint8(TAGS['TURN'])
	c += pack_single_uint8(TAGS['PLAYER'])
	c += pack_single_uint8(TAGS['ID'])
	c += pack_single_uint8(player_id)
	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['FIN'])
	return c

def de_serialize_turn(xml_str):
	tup = unpack_mult_uint8(xml_str)
	return tup[4]

def serialize_final_results(p0_books, p1_books):
	c = pack_single_uint8(TOKENS['START'])
	c += pack_single_uint8(TAGS['GAME'])

	c += pack_single_uint8(TAGS['PLAYER'])
	c += pack_single_uint8(TAGS['ID'])
	c += pack_single_uint8(0)
	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TAGS['BOOKS'])
	c += pack_single_uint8(p0_books)
	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['END'])

	c += pack_single_uint8(TAGS['PLAYER'])
	c += pack_single_uint8(TAGS['ID'])
	c += pack_single_uint8(1)
	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TAGS['BOOKS'])
	c += pack_single_uint8(p1_books)
	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['END'])

	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['FIN'])
	return c

def de_serialize_final_results(xml_str):
	tup = unpack_mult_uint8(xml_str)
	return [tup[7], tup[15]]

def serialize_error(err_code):
	c = pack_single_uint8(TOKENS['START'])
	c += pack_single_uint8(TAGS['ERROR'])
	c += pack_error(err_code)
	c += pack_single_uint8(TOKENS['END'])
	c += pack_single_uint8(TOKENS['FIN'])
	return c

def de_serialize_error(xml_str):
	tup = struct.unpack('BBbBB', str_val)
	return tup[2]


