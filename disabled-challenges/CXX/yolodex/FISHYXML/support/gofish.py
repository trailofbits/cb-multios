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

from random import randint
from piprng import PiPrng
from common import DEBUG

PRNG = PiPrng()

class GoFish(object):

	HAND_SIZE = 7

	def __init__(self, p0name):
		PRNG.reset()
		self.pool = Deck(ord(p0name[0]))
		self.turn = 0
		self.p = [Player(0, p0name), Player(1, "Bot")]
		if True == DEBUG:
			print "GoFish(): p0 name:{0}, p1 name:{1}".format(p0name, 'Bot')

	def deal(self):
		for _ in range(self.HAND_SIZE):
			self.p[0].take_top_card(self.pool)
			self.p[1].take_top_card(self.pool)
		if True == DEBUG:
			print "GoFish.deal():\n\tp0 hand:{0}\n\tp1 hand:{1}".format(self.p[0].get_hand(), self.p[1].get_hand())
		return self.p[0].get_hand()

	def get_init_hand_size(self):
		return self.HAND_SIZE

	def get_remote_player_name(self):
		return self.p[0].get_name()

	def turn_complete(self):
		self.turn = self.get_other_pid()

	def get_turn_pid(self):
		return self.turn

	def get_other_pid(self):
		return (self.get_turn_pid() + 1) % 2

	def is_game_over(self):
		if True == DEBUG:
			print "GoFish.is_game_over():\n\tStatus:\n\tPool: {0}\n\tP0: {1}\n\tP1: {2}.".format(self.pool, self.p[0].get_hand(), self.p[1].get_hand())
		return self.is_pool_empty() and self.p[0].is_hand_empty() and self.p[1].is_hand_empty()

	def get_score(self):
		return (self.p[0].get_count_books(), self.p[1].get_count_books())

	def ask_rank(self):
		return self.p[self.get_turn_pid()].select_random_card_rank()

	def ask_response_qty(self, rank):
		return self.p[self.get_other_pid()].qty_cards_of_rank(rank)

	def ask_response_give(self, rank):
		cards = self.p[self.get_other_pid()].get_cards_of_rank(rank)
		self.p[self.get_turn_pid()].accept_cards(cards)
		return cards

	def go_fishing(self):
		return self.p[self.get_turn_pid()].take_top_card(self.pool)

	def books_qty(self):
		return self.p[self.get_turn_pid()].play_books()

	def is_hand_empty(self):
		return self.p[self.get_turn_pid()].is_hand_empty()

	def is_pool_empty(self):
		return 0 == self.pool.count()

	def draw_new_hand(self):
		qty = 0
		if 0 == self.pool.count():
			return [None]
		if self.pool.count() >= self.get_init_hand_size():
			qty = self.get_init_hand_size()
		else:
			qty = self.pool.count()
		if True == DEBUG:
			print "GoFish.draw_new_hand(): qty:{0}, pool_sz:{1}.".format(qty, self.pool.count())
		return self.p[self.get_turn_pid()].draw_new_hand(self.pool, qty)



class Deck(object):
	def __init__(self, seed):
		self.card_list = self._load_cards()
		self.shuffle(seed)

	def _load_cards(self):
		cards = []
		for suit in range(1,5):
			for rank in range(1,14):
				cards.append(Card(suit, rank))
		return cards

	def count(self):
		return len(self.card_list)

	def is_empty(self):
		return 0 == self.count()

	def get_card_by_idx(self, idx):
		card = self.card_list[idx]
		self.card_list.remove(card)
		return card

	def shuffle(self, seed):
		idx = seed % 52
		rand_idx = 0

		for count in range(52):
			idx = (idx + count) % 52
			rand_idx = (rand_idx + PRNG.get_next()) % 52
			if True == DEBUG:
				print "Deck.shuffle: idx:{0}, rand_idx:{1}, count:{2}, deck_len:{3}.".format(idx, rand_idx, count, len(self.card_list))
			if idx != rand_idx:
				temp_card = self.card_list[idx]
				self.card_list[idx] = self.card_list[rand_idx]
				self.card_list[rand_idx] = temp_card
		if True == DEBUG:
			print "Deck.shuffle(): seed: {0}, shuffled deck:\n{1}".format(seed, self.card_list)

	def pop(self):
		return self.get_card_by_idx(-1)

	def __str__(self):
		return "{0}".format(self.card_list)

	def __repr__(self):
		return self.__str__()


class Player(object):
	def __init__(self, pid, pname):
		self.id = pid
		self.name = pname
		self.book_count = 0
		self.hand = Hand()

	def get_hand(self):
		return self.hand.get_cards()

	def get_name(self):
		return self.name

	def take_top_card(self, deck):
		if 0 == deck.count():
			return None
		card = deck.pop()
		self.hand.add_card(card)
		return card

	def have_cards_of_rank(self, rank):
		return 0 != self.qty_card_of_rank(rank)

	def qty_cards_of_rank(self, rank):
		return self.hand.count_cards_with_rank(rank)

	def get_cards_of_rank(self, rank):
		return self.hand.get_cards_with_rank(rank)

	def play_books(self):
		count = self.hand.make_books()
		self.book_count += count
		return count

	def is_hand_empty(self):
		return self.hand.is_empty()

	def draw_new_hand(self, deck, qty):
		how_many = 0
		if deck.count() >= qty:
			how_many = qty
		else:
			how_many = deck.count()

		cards = []
		for _ in range(how_many):
			cards.append(deck.pop())

		self.hand.add_cards(cards)
		return cards

	def select_random_card_rank(self):
		return self.hand.select_rand_card_rank(self.id)

	def accept_cards(self, cards):
		self.hand.add_cards(cards)

	def get_newest_card(self):
		return self.hand.get_latest_card()

	def get_count_books(self):
		return self.book_count

class Hand(object):

	def __init__(self):
		self.card_list = []

	def get_count(self):
		return len(self.card_list)

	def is_empty(self):
		return 0 == self.get_count()

	def add_card(self, card):
		self.card_list.append(card)

	def add_cards(self, card_list):
		for card in card_list:
			self.add_card(card)

	def rm_card(self, card):
		self.card_list.remove(card)

	def select_rand_card_rank(self, pid):
		idx = 0
		if True == DEBUG:
			print "Hand.select_rand_card_rank(): count: {0}.".format(self.get_count())

		if 0 == self.get_count():
			return 0
		if 1 < self.get_count():

			if 0 == pid:
				idx = (randint(1, 52) % self.get_count())
			else:
				# only Bot should pull from PRNG
				r = PRNG.get_next()
				idx = r % self.get_count()
				if True == DEBUG:
					print "Hand.select_rand_card_rank() PRNG val: {0}.".format(r)

		return self.card_list[idx].get_rank()

	def count_cards_with_rank(self, rank):
		count = 0
		for card in self.card_list:
			if card.get_rank() == rank:
				count += 1
		return count

	def get_cards_with_rank(self, rank):
		cards = [card for card in self.card_list if card.has_rank(rank)]
		for card in cards:
			self.rm_card(card)

		return cards

	def make_books(self):
		count = 0
		if 4 > self.get_count():
			return count

		for rank in Card.get_valid_ranks():
			if 4 == self.count_cards_with_rank(rank):
				cards = self.get_cards_with_rank(rank)
				count += 1

		return count

	# def get_rank_of_random_card(self):
	# 	rand_idx = PRNG.get_next() % self.get_count()
	# 	return self.card_list[rand_idx]

	def get_latest_card(self):
		return self.card_list[-1]

	def get_cards(self):
		return self.card_list

	def __str__(self):
		return "{0}".format(self.card_list)

	def __repr__(self):
		return self.__str__()

class Card(object):

	def __init__(self, suit, rank):
		self.suit = suit
		self.rank = rank

	@staticmethod
	def get_valid_ranks():
		return [1,2,3,4,5,6,7,8,9,10,11,12,13]

	@staticmethod
	def is_set_equal(set1, set2):
		if len(set1) != len(set2):
			return False

		found = 0
		for card1 in set1:
			for card2 in set2:
				if True == card1.is_equal(card2):
					found += 1

		return found == len(set1)

	def get_suit(self):
		return self.suit

	def get_rank(self):
		return self.rank

	def has_suit(self, suit):
		if (self.get_suit() == suit):
			return True
		else:
			return False

	def has_rank(self, rank):
		if (self.get_rank() == rank):
			return True
		else:
			return False

	def is_equal(self, other_card):
		if (self.get_rank() == other_card.get_rank()) and \
			(self.get_suit() == other_card.get_suit()):
			return True
		else:
			return False


	def __str__(self):
		return "(s:{0}, r:{1})".format(self.get_suit(), self.get_rank())

	def __repr__(self):
		return self.__str__()



