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

from random import randint, choice
# from piprng import PiPrng
import string
from math import ceil
from common import DEBUG, CONFIG

# PRNG = PiPrng()

# 6bit chars for ASCII armoring of AIS Payload in NMEA Sentence.
def ais_6bit_to_ascii_payload(str_6bit):
	'''
	Convert a 6-bit string to an ASCII char.

	str_6bit should be a StringOfBits object containing 6 bits.
	'''
	int_val = int(str_6bit)
	if 40 <= int_val:
		int_val += 8
	int_val += 48
	return chr(int_val)

# ASCII 6bit chars for "strings" in AIS messages.
def ais_6bit_to_ascii_string(str_6bit):
	int_val = int(str_6bit)
	if 31 >= int_val:
		int_val += 64
	return chr(int_val)

# ASCII 6bit chars for "strings" in AIS messages.
def ascii_string_to_ais_6bit(ascii_char):
	int_val = ord(ascii_char)
	if 63 < int_val:
		int_val -= 64
	return StringOfBits(size=6,int_val=int_val)


class Sentence(object):

	MAX_AIS_MSG_LEN = 40 # max 6bit chars in AIS ascii encoded payload.

	def __init__(self, msg_obj):
		self.sentences = []
		self._make_sentences(msg_obj)

	def _make_sentences(self, msg_obj):
		'''
		Create NMEA sentences for each part of the AIS message.
		'''
		parts = self._make_message_parts(msg_obj)
		session_id = ''
		if 1 < len(parts):
			session_id = str(randint(1,9))
		idx = 1
		for (msg, fill_bits) in parts:
			s = self._make_sentence(idx, len(parts), session_id, msg, fill_bits)
			self.sentences.append(s)
			idx += 1

	def _make_message_parts(self, msg_obj):
		'''
		If message is too long to fit into one sentence, break it into multiple
		parts such that no part is longer than MAX_AIS_MSG_LEN

		Return a list of (msg part, fill_bit) tuples
		'''
		(message, fill_bits) = msg_obj.get_ascii6_str()
		parts_cnt = int(ceil(len(message)/float(self.MAX_AIS_MSG_LEN)))
		parts = []
		for p in range(parts_cnt):
			fb = 0
			if p == parts_cnt - 1:
				fb = fill_bits
			parts.append((message[p*self.MAX_AIS_MSG_LEN : self.MAX_AIS_MSG_LEN + p*self.MAX_AIS_MSG_LEN], fb))

		return parts

	def _make_sentence(self, s_num, s_total, session_id, msg, fill_bits):
		s = "AAAAA"
		s = "{0},{1},{2},{3},{4},{5}".format(s, s_num, s_total, session_id, msg, fill_bits)
		s = "{0}{1}{2}{3}".format('!', s, '*', self._compute_checksum(s))
		return s

	def _compute_checksum(self, str1):
		'''
		Compute the charwise xor over the string.

		For AIS message, the string should be the chars between '!' and '*'.
		'''
		cs = 0
		for ch in str1:
			cs ^= ord(ch)

		return '{0:0>2}'.format(hex(cs)[2:].upper())

	def get_sentences(self):
		return self.sentences

	def get_count(self):
		return len(self.sentences)

class StringOfBits(object):

	def __init__(self, *args, **kwargs):
		"""
		Can only call constructor with kwargs:
		- size - size only
		- [size] str_val - string with optional size
		- [size] int_val - integer with optional size
		"""
		self.string_val = ""

		if args:
			raise ValueError('StringOfBits: Only keyword arguments are accepted: size, str_val, or int_val.')

		#kwargs: 
		size 	= None
		str_val = None
		int_val = None
		if kwargs.has_key('size'):
			size = kwargs.pop('size')
		if kwargs.has_key('str_val'):
			str_val = kwargs.pop('str_val')
		if kwargs.has_key('int_val'):
			int_val = kwargs.pop('int_val')
		if kwargs:
			raise TypeError('StringOfBits: {0} are invalid keyword arguments'.format(kwargs.keys()))

		if None != int_val and None != str_val:
			raise ValueError('StringOfBits: Cannot use both str_val and int_val keyword args.')

		if True == DEBUG:
			if size: print "size:{0}".format(size)
			if int_val: print "int_val: {0}".format(int_val) 
			if str_val: print "str_val: {0}".format(str_val)

		if None != str_val:
			if None != size and size > len(str_val):
				extra_bits = '0'*(size - len(str_val))
				if False == self._is_valid_bits(str_val):
					raise ValueError("StringOfBits: Invalid bits in str_val. Only '0' and '1' are accepted.")
				self.string_val = extra_bits + str_val
			else:
				self.string_val = str_val
		elif None != int_val:
			if 0 > int_val:
				raise ValueError("StringOfBits: int_val must be >= 0. For negative values, use two's complement (~, increment/decrement.")
			self.string_val = self._hex2bits(hex(int_val))
			lsv = len(self.string_val)
			if None != size:
				if size > lsv:
					extra_bits = '0'*(size - lsv)
					self.string_val = extra_bits + self.string_val
				elif size < lsv:
					extra_bits = lsv - size
					self.string_val = self.string_val[extra_bits:]
			else:
				self.string_val = self.string_val
		elif None != size:
			self.string_val = '0'*size

		if True == DEBUG:
			print " result: {0}: {1}".format(len(self.string_val), self.string_val)

	def _is_valid_bits(self, str_val):
		for bit in str_val:
			if '0' != bit and '1' != bit:
				return False
		return True

	def _hex2bits(self, hex_str):
		'''
		Assumes hex_str looks like '0xNNN' where NNN are 0-9,a-f,A-F.
		'''
		hexes = {'0': '0000',	'1': '0001',	'2': '0010',	'3': '0011',
				 '4': '0100',	'5': '0101',	'6': '0110',	'7': '0111',
				 '8': '1000',	'9': '1001',	'a': '1010',	'b': '1011',
				 'c': '1100',	'd': '1101',	'e': '1110',	'f': '1111'}
		digits = hex_str[2:].lower().rstrip('l')
		bit_str = ''.join(map(lambda x: hexes[x], digits))
		return bit_str

	def __len__(self):
		return len(self.string_val)

	def __add__(self, other):
		new_val = self.string_val
		for b in str(other):
			new_val += b
		return StringOfBits(str_val=new_val)

	def __invert__(self):
		for idx in range(len(self)):
			if '1' == self[idx]: 
				self[idx] = '0'
			else: 
				self[idx] = '1'

	def __eq__(self, other):
		if self.string_val == str(other):
			return True
		else:
			return False

	def __getslice__(self, begin, end):
		s = ""
		if end > len(self):
			end = len(self)
		if begin < 0:
			begin = end + begin
		for bit_idx in range(begin, end):
			s += self.string_val[bit_idx]
		return StringOfBits(str_val=s)

	def __int__(self):
		result = 0
		l = len(self)
		for i in range(l):
			result += int(self[i]) * (2 ** (l - i - 1))
		return result

	def __str__(self):
		return self.string_val

	def __repr__(self):
		return self.__str__()

	def __getitem__(self, idx):
		return self.string_val[idx]

	def __setitem__(self, idx, bit):
		l = len(self)
		if idx >= l:
			raise IndexError("StringOfBits.set_bit(idx, bit): bit index out of range.")
		if bit not in ['0', '1']:
			raise ValueError("StringOfBits.set_bit(idx, bit): invalid bit value.")
		if 0 > idx:
			idx = l + idx

		self.string_val = self.string_val[:idx] + str(bit) + self.string_val[idx+1:]

	def increment(self):
		l = len(self)
		r = range(l)
		r.reverse()
		idx = 0
		for idx in r:
			if '0' == self[idx]:
				self[idx] = '1'
				break
			else:
				self[idx] = '0'

	def decrement(self):
		l = len(self)
		r = range(l)
		r.reverse()
		idx = 0
		for idx in r:
			if '0' == self[idx]:
				self[idx] = '1'
			else:
				self[idx] = '0'
				break
	def int_twos(self):
		if 1 == int(self[0]):
			t = StringOfBits(str_val=str(self))
			t.decrement()
			~t
			return -1 * int(t)
		else:
			return int(self)


class MsgType1(object):

	STATUS = {0: 'underway using engine',
			  1: 'at anchor',
			  2: 'not under command',
			  3: 'restricted maneuverability',
			  4: 'constrained by draught',
			  5: 'moored',
			  6: 'aground',
			  7: 'fishing',
			  8: 'underway using sail'}

	MANEUVER = {0: 'maneuver not available',
				1: 'no special maneuver',
				2: 'special maneuver'}


	def __init__(self):
		self.type = 1 		# 3 bits
		self.mmsi = 0 		# 30 bits 	(9 digits)
		self.status = 0 	# 4 bits 	(0-8)
		self.turn = 0 		# 8 bits 	(-127 to 128)
		self.speed = 0 		# 10 bits 	(0 to 1023)
		self.accuracy = 0 	# 1 bit 	(0 or 1)
		self.lat = 0 		# 27 bits 	(60k * (-90 to 91))
		self.lon = 0 		# 28 bits 	(60k * (-180 to 181))
		self.course = 0 	# 12 bits 	(0 - 3600)
		self.heading = 0 	# 9 bits 	(0 - 511)
		self.seconds = 0 	# 6 bits 	(0 - 59)
		self.maneuver = 0 	# 2 bits 	(0 - 2)
							# 140 bits total
		self._gen_values()

		self.fill_bits = 4	# 144 bits total (multiple of 8)

	def _gen_values(self):

		self.mmsi = randint(0, -1 + 10**9)
		self.status = randint(0, 8)
		self.turn = randint(-127, 128)
		self.speed = randint(0, 1023)
		self.accuracy = choice([0, 1])
		self.lon = 60000 * randint(-180, 181)
		self.lat = 60000 * randint(-90, 91)
		self.course = choice([randint(0, 3590), 3600])
		self.heading = choice([randint(0,359), 511])
		self.seconds = randint(0, 63)
		self.maneuver = choice([0, 1, 2])


	def get_engl_str(self):
		'''
		Return the English language translation of the AIS message.
		'''
		e_str =		'type 1,'
		e_str += 	'{0},'.format(self.mmsi)
		e_str += 	'{0},'.format(self.STATUS[self.status])
		# turn
		if 0 == self.turn:
			e_str += 'not turning,'
		elif 0 > self.turn:
			e_str += 'turning left {0},'.format(abs(self.turn))
		else:
			e_str += 'turning right {0},'.format(self.turn)
		# speed
		if 1023 == self.speed:
			e_str += 'speed unk,'
		elif 1020 < self.speed:
			e_str += '>102kts,'
		else:
			e_str += '{0}kts,'.format(self.speed/10)
		# lat
		if 91*60000 == self.lat:
			e_str += 'lat unk,'
		elif 0 == self.lat:
			e_str += '0,'
		elif 0 < self.lat:
			e_str += '{0}N,'.format(self.lat)
		else:
			e_str += '{0}S,'.format(abs(self.lat))
		# lon
		if 181*60000 == self.lon:
			e_str += 'lon unk,'
		elif 0 == self.lon:
			e_str += '0,'
		elif 0 < self.lon:
			e_str += '{0}E,'.format(self.lon)
		else:
			e_str += '{0}W,'.format(abs(self.lon))
		# course
		if 3600 == self.course:
			e_str += 'course unk,'
		else:
			e_str += 'c:{0},'.format(self.course/10)
		# heading
		if 511 == self.heading:
			e_str += 'heading unk,'
		else:
			e_str += 'h:{0} TN,'.format(self.heading)
		# maneuver
		e_str += '{0}.'.format(self.MANEUVER[self.maneuver])

		return e_str

	def get_bit_str(self, fill_bits=False):
		'''
		Return the bit string (StringOfBits object) representation of the AIS message. 
		Optionally, include	the fill bits.
		'''
		bs = StringOfBits(size=3,int_val=self.type)
		bs += StringOfBits(size=30,int_val=self.mmsi)
		bs += StringOfBits(size=4,int_val=self.status)
		t = StringOfBits(size=8,int_val=abs(self.turn)) # can be - (two's comp)
		if 0 > self.turn:
			t.decrement()
			~t
		bs += t
		bs += StringOfBits(size=10,int_val=self.speed)
		bs += StringOfBits(size=1,int_val=self.accuracy)
		t = StringOfBits(size=27,int_val=abs(self.lat)) # can be - (two's comp)
		if 0 > self.lat:
			t.decrement()
			~t
		bs += t
		t = StringOfBits(size=28,int_val=abs(self.lon)) # can be - (two's comp)
		if 0 > self.lon:
			t.decrement()
			~t
		bs += t
		bs += StringOfBits(size=12,int_val=self.course)
		bs += StringOfBits(size=9,int_val=self.heading)
		bs += StringOfBits(size=6,int_val=self.seconds)
		bs += StringOfBits(size=2,int_val=self.maneuver)
		if True == fill_bits:
			bs += StringOfBits(size=self.fill_bits,int_val=0)

		return bs

	def get_ascii6_str(self):
		'''
		Return a tuple containing the ascii encoded AIS payload and the number of fill bits 
		used to bring it to the next 6-bit boundary.
		'''
		bit_str = self.get_bit_str(fill_bits=True)

		fill_bits = 0
		rem = len(bit_str) % 6
		if 0 != rem:
			fill_bits = 6 - rem
			bit_str += StringOfBits(size=fill_bits,int_val=0)

		char_count = len(bit_str) / 6
		ascii6_str = ''
		for idx in range(char_count):
			bitset = bit_str[0 + (idx * 6) : 6 + (idx * 6)]
			if True == DEBUG:
				print "{0}-{1}: {2}".format(0 + (idx * 6), 6 + (idx * 6), int(bitset))
			ascii6_str += ais_6bit_to_ascii_payload(bitset)

		return (ascii6_str, fill_bits)

	def __str__(self):
		return "{0}".format(self.get_ascii6_str()[0])

	def __repr__(self):
		return self.__str__()


class MsgType4(object):

	EPFD = {0: 'undefined',
			  1: 'GPS',
			  2: 'GLONASS',
			  3: 'Combined GPS/GLONASS',
			  4: 'Loran-C',
			  5: 'Chayka',
			  6: 'Integrated navigation system',
			  7: 'Surveyed',
			  8: 'Galileo'}

	def __init__(self):
		self.type = 4 		# 3 bits
		self.mmsi = 0 		# 30 bits 	(9 digits)
		self.year = 0 		# 14 bits   (0 - 9999)
		self.month = 0 		# 4 bits 	(0 - 12)
		self.day = 0 		# 5 bits 	(0 - 31)
		self.hour = 0 		# 5 bits 	(0 - 24)
		self.minutes = 0 	# 6 bits 	(0 - 60)
		self.seconds = 0 	# 6 bits 	(0 - 60)
		self.accuracy = 0 	# 1 bit 	(0 or 1)
		self.lat = 0 		# 27 bits 	(60k * (-90 to 91))
		self.lon = 0 		# 28 bits 	(60k * (-180 to 181))
		self.epfd = 0 		# 4 bits 	(0 - 8)
							# 133 bits total
		self._gen_values()

		self.fill_bits = 3	# 136 bits total (multiple of 8)

	def _gen_values(self):

		self.mmsi = randint(0, -1 + 10**9)
		self.year = randint(0, 9999)
		self.month = randint(0, 12)
		self.day = randint(0, 31)
		self.hour = randint(0, 24)
		self.minutes = randint(0, 60)
		self.seconds = randint(0, 60)
		self.accuracy = choice([0, 1])

		self.lon = 60000 * randint(-180, 181)
		self.lat = 60000 * randint(-90, 91)

		self.epfd = randint(0, 8)

	def get_engl_str(self):
		'''
		Return the English language translation of the AIS message.
		'''
		# type
		e_str =		'type 4,'
		# mmsi
		e_str += '{0},'.format(self.mmsi)
		# year
		if 0 == self.year:
			e_str += 'N/A,'
		else:
			e_str += '{0},'.format(self.year)
		# month
		if 0 == self.month:
			e_str += 'N/A,'
		else:
			e_str += '{0},'.format(self.month)
		# day
		if 0 == self.day:
			e_str += 'N/A,'
		else:
			e_str += '{0},'.format(self.day)
		# hour
		if 24 == self.hour:
			e_str += 'N/A,'
		else:
			e_str += '{0},'.format(self.hour)
		# minutes
		if 60 == self.minutes:
			e_str += 'N/A,'
		else:
			e_str += '{0},'.format(self.minutes)
		# seconds
		if 60 == self.seconds:
			e_str += 'N/A,'
		else:
			e_str += '{0},'.format(self.seconds)
		# lat
		if 91*60000 == self.lat:
			e_str += 'lat unk,'
		elif 0 == self.lat:
			e_str += '0,'
		elif 0 < self.lat:
			e_str += '{0}N,'.format(self.lat)
		else:
			e_str += '{0}S,'.format(abs(self.lat))
		# lon
		if 181*60000 == self.lon:
			e_str += 'lon unk,'
		elif 0 == self.lon:
			e_str += '0,'
		elif 0 < self.lon:
			e_str += '{0}E,'.format(self.lon)
		else:
			e_str += '{0}W,'.format(abs(self.lon))
		# epfd
		e_str += '{0}.'.format(self.EPFD[self.epfd])

		return e_str

	def get_bit_str(self, fill_bits=False):
		'''
		Return the bit string (StringOfBits object) representation of the AIS message. 
		Optionally, include	the fill bits.
		'''
		bs = StringOfBits(size=3,int_val=self.type)
		bs += StringOfBits(size=30,int_val=self.mmsi)
		bs += StringOfBits(size=14,int_val=self.year)
		bs += StringOfBits(size=4,int_val=self.month)
		bs += StringOfBits(size=5,int_val=self.day)
		bs += StringOfBits(size=5,int_val=self.hour)
		bs += StringOfBits(size=6,int_val=self.minutes)
		bs += StringOfBits(size=6,int_val=self.seconds)
		bs += StringOfBits(size=1,int_val=self.accuracy)

		t = StringOfBits(size=27,int_val=abs(self.lat)) # can be - (two's comp)
		if 0 > self.lat:
			t.decrement()
			~t
		bs += t
		t = StringOfBits(size=28,int_val=abs(self.lon)) # can be - (two's comp)
		if 0 > self.lon:
			t.decrement()
			~t
		bs += t

		bs += StringOfBits(size=4,int_val=self.epfd)
		if True == fill_bits:
			bs += StringOfBits(size=self.fill_bits,int_val=0)

		return bs

	def get_ascii6_str(self):
		'''
		Return a tuple containing the ascii encoded AIS payload and the number of fill bits 
		used to bring it to the next 6-bit boundary.
		'''
		bit_str = self.get_bit_str(fill_bits=True)

		fill_bits = 0
		rem = len(bit_str) % 6
		if 0 != rem:
			fill_bits = 6 - rem
			bit_str += StringOfBits(size=fill_bits,int_val=0)

		char_count = len(bit_str) / 6
		ascii6_str = ''
		for idx in range(char_count):
			bitset = bit_str[0 + (idx * 6) : 6 + (idx * 6)]
			if True == DEBUG:
				print "{0}-{1}: {2}".format(0 + (idx * 6), 6 + (idx * 6), int(bitset))
			ascii6_str += ais_6bit_to_ascii_payload(bitset)

		return (ascii6_str, fill_bits)

	def __str__(self):
		return "{0}".format(self.get_ascii6_str()[0])

	def __repr__(self):
		return self.__str__()

class MsgType5(object):

	EPFD = {0: 'undefined',
			  1: 'GPS',
			  2: 'GLONASS',
			  3: 'Combined GPS/GLONASS',
			  4: 'Loran-C',
			  5: 'Chayka',
			  6: 'Integrated navigation system',
			  7: 'Surveyed',
			  8: 'Galileo'}

	def __init__(self):
		self.type = 5 			# 3 bits
		self.mmsi = 0 			# 30 bits 	(9 digits)
		self.imo = 0 			# 30 bits 	(9 digits)
		self.callsign = '' 		# 42 bits 	7 six-bit chars
		self.shipname = '' 		# 120 bits 	20 six-bit chars
		self.epfd = 0 			# 4 bits 	(0 - 8)
		self.month = 0 			# 4 bits 	(0 - 12)
		self.day = 0 			# 5 bits 	(0 - 31)
		self.hour = 0 			# 5 bits 	(0 - 24)
		self.minutes = 0 		# 6 bits 	(0 - 60)

		self.draught = 0 		# 8 bits 	(0 - 255)
		self.dest = '' 			# 120 bits 	20 six-bit chars
								# 377 bits total
		self._gen_values()

		self.fill_bits = 7		# 384 bits total (multiple of 8)

	def _gen_values(self):

		self.mmsi = randint(0, -1 + 10**9)
		self.imo = randint(0, -1 + 10**9)
		self.callsign = ''.join(ais_6bit_to_ascii_string(StringOfBits(size=6,int_val=randint(1,63))) for _ in range(randint(4,7)))
		self.shipname = ''.join(ais_6bit_to_ascii_string(StringOfBits(size=6,int_val=randint(1,63))) for _ in range(randint(10,20)))
		self.epfd = randint(0, 8)

		self.month = randint(0, 12)
		self.day = randint(0, 31)
		self.hour = randint(0, 24)
		self.minutes = randint(0, 60)

		self.draught = randint(0,255)
		self.dest = ''.join(ais_6bit_to_ascii_string(StringOfBits(size=6,int_val=randint(1,63))) for _ in range(randint(5,20)))

	def get_engl_str(self):
		'''
		Return the English language translation of the AIS message.
		'''
		# type
		e_str =		'type 5,'
		# mmsi
		e_str += '{0},'.format(self.mmsi)
		# imo
		e_str += '{0},'.format(self.imo)
		# callsign
		e_str += '{0},'.format(self.callsign)
		# shipname
		e_str += '{0},'.format(self.shipname)
		# epfd
		e_str += '{0},'.format(self.EPFD[self.epfd])
		# month
		if 0 == self.month:
			e_str += 'N/A,'
		else:
			e_str += '{0},'.format(self.month)
		# day
		if 0 == self.day:
			e_str += 'N/A,'
		else:
			e_str += '{0},'.format(self.day)
		# hour
		if 24 == self.hour:
			e_str += 'N/A,'
		else:
			e_str += '{0},'.format(self.hour)
		# minutes
		if 60 == self.minutes:
			e_str += 'N/A,'
		else:
			e_str += '{0},'.format(self.minutes)

		# draught
		e_str += '{0},'.format(self.draught)
		# dest
		e_str += '{0}.'.format(self.dest)

		return e_str

	def get_bit_str(self, fill_bits=False):
		'''
		Return the bit string (StringOfBits object) representation of the AIS message. 
		Optionally, include	the fill bits.
		'''
		bs = StringOfBits(size=3,int_val=self.type)
		bs += StringOfBits(size=30,int_val=self.mmsi)
		bs += StringOfBits(size=30,int_val=self.imo)
		lcs = len(self.callsign)
		for c in self.callsign:
			bs += ascii_string_to_ais_6bit(c)
		for idx in range(7 - lcs):
			bs += ascii_string_to_ais_6bit('@')

		lsn = len(self.shipname)
		for c in self.shipname:
			bs += ascii_string_to_ais_6bit(c)
		for idx in range(20 - lsn):
			bs += ascii_string_to_ais_6bit('@')

		bs += StringOfBits(size=4,int_val=self.epfd)
		bs += StringOfBits(size=4,int_val=self.month)
		bs += StringOfBits(size=5,int_val=self.day)
		bs += StringOfBits(size=5,int_val=self.hour)
		bs += StringOfBits(size=6,int_val=self.minutes)
		bs += StringOfBits(size=8,int_val=self.draught)

		ldst = len(self.dest)
		for c in self.dest:
			bs += ascii_string_to_ais_6bit(c)
		for idx in range(20 - ldst):
			bs += ascii_string_to_ais_6bit('@')

		if True == fill_bits:
			bs += StringOfBits(size=self.fill_bits,int_val=0)

		return bs

	def get_ascii6_str(self):
		'''
		Return a tuple containing the ascii encoded AIS payload and the number of fill bits 
		used to bring it to the next 6-bit boundary.
		'''
		bit_str = self.get_bit_str(fill_bits=True)

		fill_bits = 0
		rem = len(bit_str) % 6
		if 0 != rem:
			fill_bits = 6 - rem
			bit_str += StringOfBits(size=fill_bits,int_val=0)

		char_count = len(bit_str) / 6
		ascii6_str = ''
		for idx in range(char_count):
			bitset = bit_str[0 + (idx * 6) : 6 + (idx * 6)]
			if True == DEBUG:
				print "{0}-{1}: {2}".format(0 + (idx * 6), 6 + (idx * 6), int(bitset))
			ascii6_str += ais_6bit_to_ascii_payload(bitset)

		return (ascii6_str, fill_bits)

	def __str__(self):
		return "{0}".format(self.get_ascii6_str()[0])

	def __repr__(self):
		return self.__str__()

