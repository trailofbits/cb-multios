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

	def play_again(self):
		self.write("PLAY AGAIN\x07")
		self.state['replay'] = True
		if self.DEBUG:
			print("Play again")

	def start_over(self):
		self.write("START OVER\x07")
		self.state['replay'] = False
		if self.DEBUG:
			print("Start over")

	def bad_cmd_die(self):

		if self.chance(0.1):
			self.write("\x07")
			self.read(delim="\n", 
				expect="Wat?\n", 
				expect_format='asciic')
		elif self.chance(0.0001):
			# 0.001% of the time, submit a bad command; will exit connection
			# bad command: (> self.CMD_CHAR_LEN chars, i.e. self.CMD_CHAR_LEN*'A' + \x07)
			cmd = random_string(self.CMD_CHAR_LEN + 1, 2 * self.CMD_CHAR_LEN)
			expect_str = "\nI don't think that means what you think it means.\n"
			self.write('{0}\x07'.format(cmd))
			self.read(delim='.\n', expect=expect_str, expect_format='asciic')
		return -1

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

	def select_char_bad(self):
		# select too many chars
		if self.chance(0.0001):
			ch = random_alpha(2, 10)
			self.write('{0}\x07'.format(ch))
			expect_str = "\nI don't think that means what you think it means.\n"
			self.read(delim='.\n', expect=expect_str, expect_format='asciic')
			return -1

		# select a single letter that is not P or Q
		else:
			ch = 'P'
			while(ch == 'P' or ch == 'Q'):
				ch = random_alpha(1, 1)
			self.write('{0}\x07'.format(ch))
			self.read(delim="\n", 
				expect="Wat?\n", 
				expect_format='asciic')

	def begin_game(self):
		expect_str = "Game on!\n"
		self.read(delim='!\n', expect=expect_str, expect_format='asciic')
		game_complete = False
		move_coords = {'row': -1, 'col': -1}
		move_fail = False

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

				if self.chance(0.0001):
					# write too much info
					move_coords['row'] = random_digits(2, 5)
					move_coords['col'] = random_digits(2, 5)
					move_fail = True

				elif self.chance(0.001):
					# write bad coords
					move_coords['row'] = randint(3, 6)
					move_coords['col'] = randint(3, 6)

				else:
					# write valid coords
					move_coords['row'] = randint(0, 2)				
					move_coords['col'] = randint(0, 2)

			# if computer's turn, use random_move to select coords
			else:
				move_coords = self.state['game'].computer_valid_random_move()

			if move_fail:
				self.write('{0} {1}\x07'.format(move_coords['row'], move_coords['col']))
				expect_str = "\nI don't think that means what you think it means.\n"
				self.read(delim='.\n', expect=expect_str, expect_format='asciic')
				return -1

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


