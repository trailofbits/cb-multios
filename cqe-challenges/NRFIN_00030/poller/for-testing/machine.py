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
import support as sp
from gofish import GoFish, Card



class FishyXml(Actions):

	DEBUG = False
	DEBUG_ERR = DEBUG or False
	DEBUG_FUNC = DEBUG or False
	DEBUG_INIT = DEBUG or False
	FAIL_CHANCE = 0.001

	def start(self):
		self.state['g'] = GoFish(sp.random_string(5, 20))

	def _recv_error(self, error_name):
		expected = sp.serialize_error(error_name)
		self.read(length=len(expected), expect=expected)
		if True == self.DEBUG_ERR:
			print('exiting due to {0}'.format(error_name))

	def _books(self):
		'''
		Process the act of removing books from hand and reporting the count.
		'''
		turn = self.state['g'].get_turn_pid()
		count = self.state['g'].books_qty()

		if True == self.DEBUG_FUNC:
			print "pid {0} books this turn: {1}".format(turn, count)

		msg = sp.serialize_books(count)

		if 0 == turn:
			self.write(msg)
		else:
			self.read(length=len(msg), expect=msg)

		return 0

	def _fishing(self, rank):
		'''
		Process the act of going fishing.
		'''
		turn = self.state['g'].get_turn_pid()
		if True == self.DEBUG_FUNC:
			print "pid {0} going fishing.".format(turn)

		FAIL = ''
		if 0 == turn:
			if self.chance(self.FAIL_CHANCE): # correct len, wrong tags for this msg
				msg = sp.serialize_draw_request()
				FAIL = 'ERR_INVALID_XML'
			else:
				msg = sp.serialize_fishing()
			self.write(msg)

		if '' != FAIL:
			self._recv_error(FAIL)
			return -1

		# if pool is out of cards, card == None; will get xml shell w/o a card
		card = self.state['g'].go_fishing()
		msg = sp.serialize_cards([card])
		if 0 == turn:
			self.read(length=len(msg), expect=msg)

		if True == self.DEBUG_FUNC:
			print " fishing card:{0}, rank:{1}, msg:{2}".format(card, rank, msg)

		ZERO = False
		if (None != card) and (False == card.has_rank(rank)):
			msg = sp.serialize_cards([None])
			ZERO = True

		if 0 == turn:
			if self.chance(self.FAIL_CHANCE): #  invalid card and incorrect for this msg
				if True == ZERO:
					msg = sp.serialize_draw_request() # just need 4 bytes
				else:
					msg = sp.serialize_cards([Card(5,15)]) # just need bogus card (12 bytes)
				FAIL = 'ERR_INVALID_CARD'

			self.write(msg)
		else:
			self.read(length=len(msg), expect=msg)

		if '' != FAIL:
			self._recv_error(FAIL)
			return -1
		else:
			return 0

	def _reload_empty_hand(self):
		'''
		Process the act of reloading hand with cards if it is empty.
		'''
		turn = self.state['g'].get_turn_pid()
		if True == self.state['g'].is_hand_empty():
			if True == self.DEBUG_FUNC:
				print "pid {0} drawing hand.".format(turn)

			FAIL = ''
			if 0 == turn:
				if self.chance(self.FAIL_CHANCE): # correct len, wrong tags for this msg
					msg = sp.serialize_turn(0)
					msg = msg[5:]
					FAIL = 'ERR_INVALID_XML'
				else:
					msg = sp.serialize_draw_request()
				self.write(msg)

			new_hand = self.state['g'].draw_new_hand()

			if 0 == turn:
				if '' != FAIL:
					msg = sp.serialize_error(FAIL)
					self.read(length=len(msg), expect=msg)
					return -1
				else:
					msg = sp.serialize_cards(new_hand)
					self.read(length=len(msg), expect=msg)

			if True == self.DEBUG_FUNC:
				print "  new hand: {0}".format(new_hand)

		return 0


	def _ask_give_cards(self, rank):
		'''
		Process the action of giving cards to other player
		as a result of an ask request.
		'''
		turn = self.state['g'].get_turn_pid()
		if True == self.DEBUG_FUNC:
			print "pid {0} accepting cards.".format(turn)

		FAIL = ''
		cards = self.state['g'].ask_response_give(rank)
		msg = sp.serialize_cards(cards)
		if 0 == turn:
			self.read(length=len(msg), expect=msg)
		else:
			cnt = len(cards)
			if self.chance(self.FAIL_CHANCE) and 1 <= cnt: #  invalid card and incorrect for this msg
				msg = sp.serialize_cards([Card(5,15)])
				FAIL = 'ERR_INVALID_CARD'

			self.write(msg)

		if '' != FAIL:
			self._recv_error
			return -1

		return 0

	def _ask(self):
		'''
		Process the act of asking the other player for cards having a given rank.
		'''
		turn = self.state['g'].get_turn_pid()
		if True == self.DEBUG_FUNC:
			print "pid {0} asking.".format(turn)

		FAIL = ''

		rank = self.state['g'].ask_rank()
		msg = sp.serialize_ask(rank)
		if 0 == turn:
			if self.chance(self.FAIL_CHANCE): # invliad rank
				msg = sp.serialize_ask(20)
				FAIL = 'ERR_INVALID_RANK'
			elif self.chance(self.FAIL_CHANCE): # wrong tags for this msg
				# length needs to be 7
				msg = sp.serialize_fishing() # len 4
				msg = msg[:-1] + msg # len 3 + 4
				FAIL = 'ERR_INVALID_XML'

			self.write(msg)
		else:
			self.read(length=len(msg), expect=msg)

		if True == self.DEBUG_FUNC:
			print "  asked for rank {0}.".format(rank)

		if '' != FAIL:
			self._recv_error(FAIL)
			return -1


		qty = self.state['g'].ask_response_qty(rank)
		msg = sp.serialize_go_fish(qty)
		if 0 == turn:
			self.read(length=len(msg), expect=msg)
		else:
			if self.chance(self.FAIL_CHANCE): # total junk
				msg = sp.pack_single_string(sp.random_string(5,5))
				FAIL = 'ERRNO_RECV'
			elif self.chance(self.FAIL_CHANCE): # wrong qty
				msg = sp.serialize_go_fish(6)
				FAIL = 'ERR_INVALID_QTY'
			elif self.chance(self.FAIL_CHANCE): # correct len, wrong tags for this msg
				msg = sp.serialize_fishing()
				msg = msg[1] + msg
				FAIL = 'ERR_INVALID_XML'
			elif self.chance(self.FAIL_CHANCE): # too short, wrong tags for this msg
				msg = sp.serialize_fishing()
				FAIL = 'ERRNO_RECV'


			self.write(msg)

		if True == self.DEBUG_FUNC:
			print "  asked player has qty {0}.".format(qty)

		if '' != FAIL:
			self._recv_error(FAIL)
			return -1


		if 0 == qty:
			return self._fishing(rank)
		else:
			return self._ask_give_cards(rank)

	def _name(self):
		# send remote player's name
		msg = ''
		FAIL = ''

		# for these name string msgs, if they are not properly terminated, they need
		# to be 100 chars long to prevent a recv timeout
		if self.chance(self.FAIL_CHANCE): # not xml, no delim
			msg = sp.pack_single_string(sp.random_string(100,100))
			FAIL = 'ERRNO_RECV'
		elif self.chance(self.FAIL_CHANCE): # xml, no delim
			msg = sp.serialize_player_name(sp.random_string(95,95))
			msg = msg[0:-3]
			FAIL = 'ERRNO_RECV'
		elif self.chance(self.FAIL_CHANCE): # malformed xml, with delim
			msg = sp.serialize_player_name(self.state['g'].get_remote_player_name())
			msg = msg[3:]
			FAIL = 'ERR_INVALID_XML'
		else:
			msg = sp.serialize_player_name(self.state['g'].get_remote_player_name())


		self.write(msg)

		if '' != FAIL:
			self._recv_error(FAIL)
			return -1

		return 0


	def game(self):
		'''
		Run the game logic.
		'''
		if True == self.DEBUG_FUNC:
			print "Starting game."

		if 0 > self._name():
			return -1

		# recv initial cards
		my_init_hand = self.state['g'].deal()
		msg = sp.serialize_cards(my_init_hand)
		self.read(length=len(msg), expect=msg)

		if True == self.DEBUG_FUNC:
			print "  initial hand: {0}.".format(my_init_hand)

		# do turns
		while (False == self.state['g'].is_game_over()):
			turn = self.state['g'].get_turn_pid()
			if True == self.DEBUG_FUNC:
				score = self.state['g'].get_score()
				print "pid {0} turn; books (p0, p1):{1}".format(turn, score)

			msg = sp.serialize_turn(turn)
			self.read(length=len(msg), expect=msg)

			if 0 > self._reload_empty_hand():
				return -1

			if 0 > self._ask():
				return -1

			if 0 > self._books():
				return -1

			self.state['g'].turn_complete()


		# recv final results
		score = self.state['g'].get_score()
		msg = sp.serialize_final_results(score[0], score[1])
		self.read(length=len(msg), expect=msg)

		return


