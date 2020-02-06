#!/usr/bin/env python

#Author: James Nuttall (james@cromulence.co)

#Copyright (c) 2015 Cromulence LLC

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in
#all copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#THE SOFTWARE.

from generator.actions import Actions, Variable
import random
import string
import struct
import re
import operator

class Wifi_game(Actions):

	WINNING_LENGTH = 9 # how many connected pieces to win?
	piece_stack = [] # contains string of each piece. e.g. 0n1y2y3n
	encryption_type = 1

	packet_len = 16
 	current_connection = -1
 	packet_num_sent = 0
 	packet_num_recv = -1
 	loop_count = 0
 	piece_num = 0
 	current_road_len = 0

 	def begin(self):
 		self.packet_len = 16
	 	self.current_connection = -1
	 	self.packet_num_sent = 0
	 	self.packet_num_recv = -1
	 	self.loop_count = 0
	 	self.piece_num = 0
	 	self.current_road_len = 0
	 	self.piece_stack = []

	offset = 3

	# for each char in the data, alternate adding and subtracting offset
	#  wrap around if it falls outside chars (valid between '0' and 'z')
	LAST = 'z'
	FIRST = '0'
	def _encrypt_content(self, data):
		answer = []

		i = 0
		for c in data:
			if i % 2 == 0:
				x = chr(ord(c) + self.offset)
				if x > self.LAST:
					t = ord(x)
					t = t - ord(self.LAST)
					t = t + ord(self.FIRST)
					x = chr(t)
				answer.append(x)
			else:
				x = chr(ord(c) - self.offset)
				if x < self.FIRST:
					t = ord(x)
					t = t - ord(self.FIRST)
					t = t + ord(self.LAST)
					x = chr(t)
				answer.append(x)
			i += 1

		return ''.join(answer)

	# decrypt received data
	def _decrypt_content(self, data):
		answer = []

		i = 0
		for c in data:
			if i % 2 == 0:
				x = chr(ord(c) - self.offset)
				if x < self.FIRST:
					t = ord(x)
					t = t - ord(self.FIRST)
					t = t + ord(self.LAST)
					x = chr(t)
				answer.append(x)
			else:
				x = chr(ord(c) + self.offset)
				if x > self.LAST:
					t = ord(x)
					t = t - ord(self.LAST)
					t = t + ord(self.FIRST)
					x = chr(t)
				answer.append(x)
			i += 1

		return ''.join(answer)

	def _listen_for_next_packet(self):
		self.read(delim="\n", expect="ready for next packet")

	def _listen_for_ack(self):
		matcher = "ap0" + str(self.current_connection) + '1' + str(self.packet_num_sent) + '000000000'
		matcher += self.getChecksum(matcher)
		self.read(delim="\n", expect=matcher)

	def getRoadLen(self):
		filler = "123123123"
		self.packet_num_sent += 1
		pkt = "cw" + str(self.packet_num_sent) + str(self.current_connection) + str(len(str(filler))) + str(filler) + '0'
		pkt += self.getChecksum(pkt)
		pkt += '\n'
		self.write(pkt)

		self._listen_for_ack()

		# receive length
		self.packet_num_recv += 1
		val = chr(ord('0') + self.current_road_len)
		
		if self.encryption_type == 1:
			val = self._encrypt_content(val)
		else:
			val = self._decrypt_content(val)
		matcher = "cw" + str(self.packet_num_recv) + str(self.current_connection) + '1' + str(val) + '000000000'
		matcher += self.getChecksum(pkt)
		self.read(delim="\n", expect=matcher)

		self._listen_for_next_packet()

 	# Set up the game
	def start(self):
		self.read(delim="\n", expect="go time")
		self.current_connection = -1
		self.packet_num_sent = 0
		self.read(delim="\n", expect="Enter crypto seed")
		
		# provide PRNG seed for this game
		data = ''.join(chr(random.randint(ord('!'),ord('~'))) for _ in range(random.randint(5,5)))
		self.write(data + '\n')

		# seed the PRNG with this random string
		self.rand = Prng()
		seed = 0xffffffffffffffffL
		for p in range(len(data)):
			seed = ((((seed << 4) & 0xffffffffffffffffL)| ((seed >> 60)& 0xffffffffffffffffL))) ^ ((struct.unpack("<b", data[p])[0])&0xff)
		self.rand.sprng(seed & 0xffffffffffffffffL) 

	def send_packet(self):
		self.read(delim="\n", expect="ready for next packet")
		self.write("as6fqwetyr\n");
		self.read(delim="finished\n", expect=".*", expect_format="pcre")

	# This is the first step of the game, association
	def assoc(self):
		self._listen_for_next_packet()

		self.current_connection += 1
		pkt = "bd001" + str(self.current_connection) + "123456789"
		pkt += self.getChecksum(pkt)
		pkt += '\n'
		self.write(pkt)

		matcher = "be0"+ str(self.current_connection) +"11000000000" #+ str(self.packet_num_sent) + str(self.current_connection) + "11b" + '\n'
		matcher += self.getChecksum(matcher)
		self.read(delim="\n", expect=matcher)
		self.read(delim="\n", expect="SUCCESSFUL association", expect_format="pcre")
		self._listen_for_next_packet()

	# Step 2, authentication
	def auth(self):
		# send the initial auth request
		c = random.choice("12")
		if c == '1':
			enc_type = "abc"
			self.encryption_type = 2
		else:	
			enc_type = "xyz"
			self.encryption_type = 1

		
		pkt = "bf0" + str(self.current_connection) + str(len(enc_type)) + enc_type + '0099000'
		pkt += self.getChecksum(pkt)
		pkt += '\n'
		self.write(pkt)

		# create random string we expect to see in this string
		substr = ""
		for x in range(0,5):
			substr += chr(self.rand.random_in_range(ord('a'), ord('p')))

		# handle the incoming challenge request here
		matcher = "bg0"+ str(self.current_connection) +str(len(substr))+substr+"00000" #0" + str(self.current_connection) + '14' + 'b' + '\n'
		matcher += self.getChecksum(matcher)
		self.read(delim="\n", expect=matcher)
		self._listen_for_next_packet()

		answer = ""
		if self.encryption_type == 1:
			answer = self._encrypt_content(substr);
		else:
			answer = self._decrypt_content(substr);

		pkt = "bh0" + str(self.current_connection) + str(len(str(answer))) + str(answer) + '00000'
		pkt += self.getChecksum(pkt)
		pkt += '\n'
		self.write(pkt)

		# handle the final auth response here
		matcher = "bi0"+ str(self.current_connection) +"11000000000"
		matcher += self.getChecksum(matcher)
		self.read(delim="\n", expect=matcher)

		self.packet_num_sent = -1
 		self.packet_num_recv = -1

		self._listen_for_next_packet()
		
		# we are now connected to the game server. time for data

	def getChecksum(self, packet):
		# mutate packet to return value
		lrc = reduce(operator.xor, [ord(c) for c in packet])
		return chr(lrc)

	def handle_receive_place_success(self):
		self._listen_for_ack()

		self.current_road_len += 1
		self.packet_num_recv += 1
		val = chr(ord('0') + self.current_road_len)
		if self.encryption_type == 1:
			val = self._encrypt_content(val)
		else:
			val = self._decrypt_content(val)
		matcher = "cz" + str(self.packet_num_recv) + str(self.current_connection) + '1' + str(val) + '000000000'
		matcher += self.getChecksum(matcher)
		self.read(delim="\n", expect=matcher)

		self._listen_for_next_packet()

	# placement is a string of numbers: <pieceA><sideA>,<pieceB><sideB>
	def _place_piece(self, placement):
		# need to mark a piece that has been placed (the side that is used up by this placement)
		# place the piece
		# piece number is same as self.piece_stack index

		# mark used side
		# find piece (by index) and marks the used side's 'y' to an 'x'
		#"0y1n2y3n" -> "0x1n2y3n"
		try:
			pieceAa = self.piece_stack.pop()
			pieceA = list(pieceAa)
			xA = int(placement[1])*2 + 1
			pieceA[xA] = 'x'
			pieceBb = self.piece_stack.pop()
			pieceB = list(pieceBb)
			xB = int(placement[4])*2 + 1
			pieceB[xB] = 'x'
			self.piece_stack.append(''.join(pieceB))
			self.piece_stack.append(''.join(pieceA))

			if self.encryption_type == 1:
				enc_placement = self._encrypt_content(placement)
			else:
				enc_placement = self._decrypt_content(placement)
			
			self.packet_num_sent += 1
			pkt = "cz" + str(self.packet_num_sent) + str(self.current_connection) + str(len(str(enc_placement))) + str(enc_placement) + '00034'
			pkt += self.getChecksum(pkt)
			pkt += '\n'
			self.write(pkt)

			self.handle_receive_place_success()
		except Exception, e:
			print Exception, e
			print placement

	def _create_first_piece(self):
		side1 = self.rand.random_in_range(1,3)

		ret_str = "0n1n2n3n"
		list_str = list(ret_str)

		list_str[side1*2 + 1] = 'y'

		self.piece_stack.append(''.join(list_str))

		return ''.join(list_str)

	# return the string of the next piece 
	def _create_piece(self):
		side1 = self.rand.random_in_range(0,3)
		side2 = side1

		while side2 == side1:
			side2 = self.rand.random_in_range(0,3)

		ret_str = "0n1n2n3n"
		list_str = list(ret_str)

		list_str[side1*2 + 1] = 'y'
		list_str[side2*2 + 1] = 'y'

		self.piece_stack.append(''.join(list_str))

		return ''.join(list_str)


# 2
#1 3
# 0
	# mapping of which sides can connect to each other
	matching_sides = {0:2,1:3,3:1,2:0}

	# looks at top two pieces and determines if they can fit together
	# returns empty string if pieces don't fit
	# returns format <pieceA><sideA>, <pieceB><sideB>
	def _piece_fits(self):
		# pieceB only has one 'y', find it
		# then determine if sideA has the complimentary piece with a 'y'

		if len(self.piece_stack) < 2:
			return ""

		ret = ""
		pieceA = self.piece_stack[-1]
		pieceB = self.piece_stack[-2]
		
		sideB = pieceB[pieceB.find('y')-1]
		needed_sideA = self.matching_sides[int(sideB)]
		if pieceA[needed_sideA*2+1] == 'y':
			pA_index = self.piece_stack.index(pieceA)
			pB_index = self.piece_stack.index(pieceB)

			ret = str(pA_index) + str(needed_sideA) + ':' + str(pB_index) + str(sideB)

		return ret

	# we have reached the max number of moves in a connection, need to reconnect
	def _reconnect(self):
		self._deauth()
		self._disass()

		self.assoc()
		self.auth()


	# generate an arbitrary number of data packets
	def data(self):
		self.packet_num_sent = -1 # starting at first packet
		self.piece_num = 0
		
		filler = "1234567890"

		# draw piece 0
		self.current_road_len = 1
		piece_info = str(self.piece_num) + self._create_first_piece()
		self._draw_piece(piece_info)

		moves = 0
		while (self.current_road_len < self.WINNING_LENGTH):
			# check if we've maxed out our moves
			moves += 1
			if moves >= 9:
				moves = 0
				self._reconnect()

			piece_info = str(self.piece_num) + self._create_piece()
			self._draw_piece(piece_info)

			# check if we've maxed out our moves
			moves += 1
			if moves >= 9:
				moves = 0
				self._reconnect()

			placement = self._piece_fits()
			if placement != "":
				self._place_piece(placement)
			else:
				self._discard_piece()

		# check for win
		matcher = "YOU WIN, what is your name?";
		self.read(delim="\n", expect=matcher)

		# send a random name
		name = ''.join(random.choice(string.letters) for _ in range(random.randint(1,12)))
		self.write(name + '\n');

		matcher = "Well done,"
		self.read(delim="\n", expect=matcher, expect_format="pcre")
		# we win
		return

	def _deauth(self):
		pkt = "bl" + '0' + str(self.current_connection) + '9' + '7122334455'
		pkt += self.getChecksum(pkt)
		pkt += '\n'
		self.write(pkt)

		matcher = "bm" + '0' + str(self.current_connection) + '1' + '1000000000'
		matcher += self.getChecksum(matcher)
		self.read(delim="\n", expect=matcher)

		self._listen_for_next_packet()

	def _disass(self):
		pkt = "bj" + '0' + str(self.current_connection) + '9' + '3122334455'
		pkt += self.getChecksum(pkt)
		pkt += '\n'
		self.write(pkt)

		matcher = "bk" + '0' + str(self.current_connection) + '1' + '1000000000'
		matcher += self.getChecksum(matcher)
		self.read(delim="\n", expect=matcher)

	def _discard_piece(self):
		self.piece_stack.pop()

		self.packet_num_sent += 1
		pkt = "cv" + str(self.packet_num_sent) + str(self.current_connection) + '9' + '1122334455'
		pkt += self.getChecksum(pkt)
		pkt += '\n'
		self.write(pkt)

		self._listen_for_ack()

		self.packet_num_recv += 1
		matcher = "cv" + str(self.packet_num_recv) + str(self.current_connection) + '1' + 'y000000000'
		matcher += self.getChecksum(matcher)
		self.read(delim="\n", expect=matcher)

		self.piece_num -= 1

		self._listen_for_next_packet()

	def _draw_piece(self, piece_info):

		self.packet_num_sent += 1
		pkt = "cx" + str(self.packet_num_sent) + str(self.current_connection) + '9' + '1122334455'
		pkt += self.getChecksum(pkt)
		pkt += '\n'
		self.write(pkt)

		self._listen_for_ack()

		self.piece_num += 1
		self.packet_num_recv += 1
		if self.encryption_type == 1:
			piece_info = self._encrypt_content(piece_info)
		else:
			piece_info = self._decrypt_content(piece_info)

		matcher = "cx" + str(self.packet_num_recv) + str(self.current_connection) + '9' + piece_info + '0'
		matcher += self.getChecksum(matcher)
		self.read(delim="\n", expect=matcher)

		self._listen_for_next_packet()

	def endgame(self):
		self.write("1212\n")
		self.read(delim="good bye\n", expect="good bye")


class Prng():

	COEFFICIENT_A_64 = 12
	COEFFICIENT_B_64 = 25
	COEFFICIENT_C_64 = 27
	MULTIPLIER_64 = 1803442709493370165
	COEFFICIENT_A_1024 = 27
	COEFFICIENT_B_1024 = 13
	COEFFICIENT_C_1024 = 46
	MULTIPLIER_1024 = 1865811235122147685

	def __init__(self):

		self.state = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
		self.position = 0

	def sprng(self, seed):

		state_64 = seed & 0xffffffffffffffffL
		for i in range(16):
			state_64 ^= (state_64 >> self.COEFFICIENT_A_64)& 0xffffffffffffffffL
			state_64 ^= (state_64 << self.COEFFICIENT_B_64)& 0xffffffffffffffffL
			state_64 ^= (state_64 >> self.COEFFICIENT_C_64)& 0xffffffffffffffffL
			self.state[i] = (state_64 *self.MULTIPLIER_64)& 0xffffffffffffffffL
		self.position = 0

	def prng(self):
		state0 = self.state[self.position]
		self.position = (self.position +1) % 16
		state1 = self.state[self.position]

		state1 ^= (state1 << self.COEFFICIENT_A_1024)& 0xffffffffffffffffL
		state1 ^= (state1 >> self.COEFFICIENT_B_1024)& 0xffffffffffffffffL
		state0 ^= (state0 >> self.COEFFICIENT_C_1024)& 0xffffffffffffffffL
		self.state[self.position] = (state0 ^ state1)& 0xffffffffffffffffL
		return (self.state[self.position] * self.MULTIPLIER_1024)& 0xffffffffffffffffL

	def random_in_range(self, min, max):

		if (max <= min):
			return 0
		range = max - min + 1
		scale_factor = 0xffffffff / range
		#discard numbers that would cause bias
		while True:
			rand_uint = self.prng() & 0xffffffff
			if (rand_uint < (scale_factor * range)):
				break

		return (rand_uint / scale_factor + min)