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

from generator.actions import Actions
from random import choice, randint
from os.path import dirname, abspath, join
import imp
import random
import string
import sys


TICKATACK_DIR = dirname(dirname(dirname(abspath(__file__))))
sys.path.append(join(TICKATACK_DIR, "support"))
from tickatack import TickATackGame

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))

def random_digits(a, b):
    chars = string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))


class TICKATACK(Actions):

	CMD_CHAR_LEN=14
	DEBUG = False

	def _load_game(self):
		self.state['game'] = TickATackGame()
		# self.state['move_coords'] = {'row': -1, 'col': -1}
		# self.state['move_fail'] = False
		# self.state['game_complete'] = False
		self.state['replay'] = False

	def start(self):
		self._load_game()
		self.read(delim="\n", 
			expect="Welcome to Tick-A-Tack.\n", 
			expect_format='asciic')

	def init_menu(self):
		self.read(delim="\n", 
			expect="Make your selection:\n", 
			expect_format='asciic')
		self.read(delim="\n", 
			expect="PLAY\n", 
			expect_format='asciic')
		self.read(delim="\n", 
			expect="QUIT\n", 
			expect_format='asciic')
		self.read(delim='$ ', expect='$ ', expect_format='asciic')

	def replay_menu(self):
		self.read(delim="\n", 
			expect="Make your selection:\n", 
			expect_format='asciic')
		self.read(delim="\n", 
			expect="PLAY AGAIN\n", 
			expect_format='asciic')
		self.read(delim="\n", 
			expect="START OVER\n", 
			expect_format='asciic')
		self.read(delim="\n", 
			expect="QUIT\n", 
			expect_format='asciic')
		self.read(delim='$ ', expect='$ ', expect_format='asciic')

	def quit(self):
		self.write("QUIT\x07")
		expect_str = "Give up?. Don't be a stranger!\n"
		self.read(delim='\n', expect=expect_str, expect_format='asciic')
		return -1

	def play(self):
		self.write("PLAY\x07")
		if self.DEBUG:
			print("Play")

	def select_char(self):
		expect_str = "P goes first. Do you want P or Q?\n"
		self.read(delim='\n', expect=expect_str, expect_format='asciic')
		self.read(delim='$ ', expect='$ ', expect_format='asciic')

	def select_char_good(self):
		# select either P or Q
		if self.chance(0.5):
			# P
			self.write("P\x07")
			self.state['game'].init_game(self.state['replay'], 'P')
		else:
			# Q
			self.write("Q\x07")
			self.state['game'].init_game(self.state['replay'], 'Q')

	def begin_game(self):
		expect_str = "Game on!\n"
		self.read(delim='!\n', expect=expect_str, expect_format='asciic')
		game_complete = False
		move_coords = {'row': -1, 'col': -1}

		# if game complete; return
		while not game_complete:

			# read the board
			# expect_str = self.state['game'].get_board_content()
			# self.read(length=len(expect_str), expect=expect_str, expect_format='asciic')

			# if player's turn, send bad coords a small percentage of the time
			# and send too much input an even smaller % of time and return -1
			if self.state['game'].is_players_turn():
				# read MAKEMOVE string
				expect_str = "It's your move. Enter 'row col'\n"
				self.read(delim='\n', expect=expect_str, expect_format='asciic')
				self.read(delim='$ ', expect='$ ', expect_format='asciic')

				# write valid coords
				move_coords = self.state['game'].player_valid_random_move()

			# if computer's turn, use random_move to select coords
			else:
				move_coords = self.state['game'].computer_valid_random_move()

			# update board
			update_failed = self.state['game'].update_board(move_coords)

			# if board update failed, coords are bad.
			# if coords are bad, and it's player's turn, send BADMOVE
			if update_failed:
				if self.state['game'].is_players_turn():
					self.write('{0} {1}\x07'.format(move_coords['row'], move_coords['col']))
					expect_str = "Invalid coordinates!\n"
					self.read(delim='\n', expect=expect_str, expect_format='asciic')
			else:
				# if coords are good, move_complete()
				if self.state['game'].is_players_turn():
					self.write('{0} {1}\x07'.format(move_coords['row'], move_coords['col']))
				else:
					#read computer's move
					expect_str = "Computer's move: {0} {1}.\n".format(move_coords['row'], move_coords['col'])
					self.read(delim='.\n', expect=expect_str, expect_format='asciic')

				self.state['game'].move_complete()

			if self.state['game'].have_winner() or not self.state['game'].have_moves_remaining():
			   self.state['game'].update_score()
			   game_complete = True

	def game_results(self):

		# read the board
		# expect_str = self.state['game'].get_board_content()
		# self.read(length=len(expect_str), expect=expect_str, expect_format='asciic')

		# read win/loss
		if self.state['game'].is_player_winner():
			expect_str = "Congratulations! You Win!\n"
			self.read(delim='\n', expect=expect_str, expect_format='asciic')
		else:
			expect_str = "Nice effort. Maybe next time.\n"
			self.read(delim='\n', expect=expect_str, expect_format='asciic')

		# read final score msg
		player_score = self.state['game'].get_scores()['player'] % 256
		computer_score = self.state['game'].get_scores()['computer'] % 256
		expect_str = "{0} wins. {1} losses.\n".format(player_score, computer_score)
		self.read(delim='.\n', expect=expect_str, expect_format='asciic')


