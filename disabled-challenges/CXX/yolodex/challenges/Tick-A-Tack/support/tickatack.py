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
from piprng import PiPrng


class TickATackGame(object):

	EMPTY = ' '
	PLAYERS = ['P', 'Q']
	DEBUG = False

	def __init__(self, player_start=0):
		self.player_char = self.EMPTY
		self.computer_char = self.EMPTY
		self.prng = PiPrng()
		self.player_prng = PiPrng(player_start)
		self.scores = {'player': 0, 'computer': 0}

	def init_game(self, replay, player_char):
		if self.DEBUG:
			print("init_game - scores: p:{0},c:{1}, replay:{2}".format(self.scores['player'], self.scores['computer'], replay))

		if not replay:
			if self.DEBUG:
				print("Set scores to 0 from p:{0},c:{1}".format(self.scores['player'], self.scores['computer']))
			self.scores['player'] = 0
			self.scores['computer'] = 0

		if player_char == self.PLAYERS[0]:
			self.player_char = self.PLAYERS[0]
			self.computer_char = self.PLAYERS[1]
		else:
			self.player_char = self.PLAYERS[1]
			self.computer_char = self.PLAYERS[0]

		self.moves = 0
		self.winner = self.EMPTY

		self.top = [self.EMPTY, self.EMPTY, self.EMPTY]
		self.middle = [self.EMPTY, self.EMPTY, self.EMPTY]
		self.bottom = [self.EMPTY, self.EMPTY, self.EMPTY]

	def set_board_content(self):
		self.game_board =   "     0   1   2  \n" \
							"   +---+---+---+\n" \
							" 0 | {0} | {1} | {2} |\n" \
							"   +---+---+---+\n" \
							" 1 | {3} | {4} | {5} |\n" \
							"   +---+---+---+\n" \
							" 2 | {6} | {7} | {8} |\n" \
							"   +---+---+---+\n".format(
								self.top[0], self.top[1], self.top[2],
								self.middle[0], self.middle[1], self.middle[2],
								self.bottom[0], self.bottom[1], self.bottom[2])

	def get_board_content(self):
		self.set_board_content()
		return self.game_board

	def has_valid_coords(self, move_coords):
		return (0 <= move_coords['row'] and move_coords['row'] <= 2 and
		   		0 <= move_coords['col'] and move_coords['col'] <= 2)

	def coords_unoccupied(self, move_coords):
		return (self.game_board_get_at_coord(move_coords) == self.EMPTY)

	def game_board_set_at_coord(self, move_coords):
		if move_coords['row'] == 0:
			self.top[move_coords['col']] = self.PLAYERS[self.moves % 2]
		elif move_coords['row'] == 1:
			self.middle[move_coords['col']] = self.PLAYERS[self.moves % 2]
		else:
			self.bottom[move_coords['col']] = self.PLAYERS[self.moves % 2]

	def game_board_get_at_coord(self, move_coords):
		result = self.EMPTY
		if move_coords['row'] == 0:
			result = self.top[move_coords['col']]
		elif move_coords['row'] == 1:
			result = self.middle[move_coords['col']]
		else:
			result = self.bottom[move_coords['col']]

		return result

	def is_valid_move(self, move_coords):
		return (self.has_valid_coords(move_coords) and self.coords_unoccupied(move_coords))

	def update_board(self, move_coords):
		result = 0

		if self.is_valid_move(move_coords):
			self.game_board_set_at_coord(move_coords)
		else:
			result = 1

		return result

	def have_winner(self):

		result = 1

		if self.moves < 3:
			return 0

		# top row
		if self.top[0] == self.top[1] and \
		   self.top[1] == self.top[2] and \
		   self.top[0] != self.EMPTY:
		   self.winner = self.top[0]
		# middle row
		elif self.middle[0] == self.middle[1] and \
		     self.middle[1] == self.middle[2] and \
		     self.middle[0] != self.EMPTY:
		     self.winner = self.middle[0]
		# bottom row
		elif self.bottom[0] == self.bottom[1] and \
		     self.bottom[1] == self.bottom[2] and \
		     self.bottom[0] != self.EMPTY:
		     self.winner = self.bottom[0]
		# first col
		elif self.top[0] 	== self.middle[0] and \
		     self.middle[0] == self.bottom[0] and \
		     self.bottom[0] != self.EMPTY:
		     self.winner = self.top[0]
		# second col
		elif self.top[1] 	== self.middle[1] and \
		     self.middle[1] == self.bottom[1] and \
		     self.bottom[1] != self.EMPTY:
		     self.winner = self.top[1]
	    # third col
		elif self.top[2] 	== self.middle[2] and \
		     self.middle[2] == self.bottom[2] and \
		     self.bottom[2] != self.EMPTY:
		     self.winner = self.top[2]
		# diag top left to bottom right
		elif self.top[0] 	== self.middle[1] and \
		     self.middle[1] == self.bottom[2] and \
		     self.bottom[2] != self.EMPTY:
		     self.winner = self.top[0]
		# diag bottom left to top right
		elif self.top[2] 	== self.middle[1] and \
		     self.middle[1] == self.bottom[0] and \
		     self.bottom[0] != self.EMPTY:
		     self.winner = self.top[2]
		# no winner
		else:
			result = 0

		return result

	def have_moves_remaining(self):
		return (self.moves < 9)

	def is_player_winner(self):
		return (self.winner == self.player_char)

	def is_players_turn(self):
		return (self.player_char == self.PLAYERS[self.moves % 2])

	def move_complete(self):
		self.moves += 1

	def random_move(self):
		return {'row': self.prng.get_next() % 3, 
				'col': self.prng.get_next() % 3}

	def computer_valid_random_move(self):
		c_move = self.random_move()
		while(not self.is_valid_move(c_move)):
			c_move = self.random_move()

		return c_move

	def player_random_move(self):
		return {'row': self.player_prng.get_next() % 3, 
				'col': self.player_prng.get_next() % 3}

	def player_valid_random_move(self):
		p_move = self.player_random_move()
		while(not self.is_valid_move(p_move)):
			p_move = self.player_random_move()

		return p_move


	def get_scores(self):
		return self.scores

	def update_score(self):
		if self.winner == self.player_char:
			self.scores['player'] += 1
		else:
			self.scores['computer'] += 1

