#!/usr/bin/env python
#
# Copyright (C) 2015 Narf Industries <info@narfindustries.com>
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
import string
import random
import itertools
import math
from struct import *

class TemplateGenerator(Actions):

	def _getRandomName(self):
		name = ''
		for c in range(10):
			randomVal = ord(self.magic_page[self.magic_idx+c])
			if randomVal % 2 == 0:
				name += chr(ord('A') + (randomVal % 26))
			else:
				name += chr(ord('a') + (randomVal % 26))

		self.magic_idx = (self.magic_idx + 10) % 100

		return name

	def _read_view(self):
		for _ in range(self.VIEW_HEIGHT):
			self.read(delim="\n", expect=".*", expect_format='pcre')

	def _quit_game(self):
		self.write(self.state['quit'])
		self.write("\n")

	def _move_left(self):
		self.moves += 1
		self.write(self.state['left'])
		self.write("\n")
		##self._read_view()

	def _move_right(self):
		self.moves += 1
		self.write(self.state['right'])
		self.write("\n")
		#self._read_view()

	def _jump(self):
		self.moves += 1
		self.write(self.state['jump'])
		self.write("\n")
		#self._read_view()
		#self._read_view()
		#self._read_view()
		#self._read_view()

	def _jumpLeft(self):
		self.moves += 1
		self.write(self.state['jumpleft'])
		self.write("\n")
		#self._read_view()
		#self._read_view()
		#self._read_view()

	def _jumpRight(self):
		self.moves += 1
		self.write(self.state['jumpright'])
		self.write("\n")
		#self._read_view()
		#self._read_view()
		#self._read_view()

	def _wait(self):
		self.moves += 1
		self.write(self.state['wait'])
		self.write("\n")
		#self._read_view()

	def _getMenuInstruction(self):
		menu_hdr = "Menu\n"
		self.read(delim="\n", expect=menu_hdr)
		line = "-----\n"
		self.read(delim="\n", expect=line)
		self.read(length=13, assign=self.state['play'])
		self.read(length=20, assign=self.state['instructions'])
		self.read(length=15, assign=self.state['highScore'])
		self.read(length=13, assign=self.state['quit'])

	def _getGameDescription(self):
		self.write(self.state['instructions'])
		self.write("\n")
		game_menu_hdr = "Game moves\n"
		self.read(delim="\n", expect=game_menu_hdr)
		line = "----------\n"
		self.read(delim="\n", expect=line)
		self.read(length=8, assign=self.state['left'])
		self.read(length=9, assign=self.state['right'])
		self.read(length=8, assign=self.state['jump'])
		self.read(length=13, assign=self.state['jumpleft'])
		self.read(length=14, assign=self.state['jumpright'])
		self.read(length=8, assign=self.state['wait'])
		self.read(length=13, assign=self.state['quit'])

	def _rightWin(self):
		length = random.randint(5,20)
		name = ''.join(random.choice(string.ascii_letters) for _ in range(length))
		eip = 'AAAA'
		ebp = 'BBBB'
		sled = '0'*42
		#name = sled + ebp + eip
		win_pcre = r'You found the treasure at position x:([0-9]*) y:([0-9]*) after ([0-9]*) moves\n'
		self.user_id += 1
		varname = "user"+str(self.user_id)
		win = Variable(varname)
		win.set_re(win_pcre, group=3)
		self.write(self.state['right'])
		self.write("\n")
		self.read(delim="\n", assign=win)
		move_pcre = r'Move list: (.*)\n'
		self.read(delim="\n", expect=move_pcre, expect_format='pcre')
		get_name_msg = "Please enter your name: "
		self.read(length=len(get_name_msg), expect=get_name_msg)
		self.highScores.append(dict(name=name, score=win))
		self.write(name+"\n")
		#self.write(sled)
		#self.write(ebp)
		#self.write(eip)

	def _diedBat(self):
		died_pcre = r'You were killed by a bat at position x:([0-9]*) y:([0-9]*) after ([0-9]*) moves\n'
		self.read(delim="\n", expect=died_pcre, expect_format='pcre')

	def _diedZombie(self):
		died_pcre = r'You were killed by a zombie at position x:([0-9]*) y:([0-9]*) after ([0-9]*) moves\n'
		self.read(delim="\n", expect=died_pcre, expect_format='pcre')


	def start(self):
		#self.delay(100)
		self.magic_idx = 0
		self.user_id = 0
		self.highScores = []
		self.highScores.append(dict(name=self._getRandomName(), score=600))
		self.highScores.append(dict(name=self._getRandomName(), score=601))
		self.highScores.append(dict(name=self._getRandomName(), score=999999))
		play_re = "Play game: (.*)\n"
		play = Variable('play')
		play.set_re(play_re, group=1)
		self.state['play'] = play
		instructions_re = "Get instructions: (.*)\n"
		instructions = Variable('instructions')
		instructions.set_re(instructions_re, group=1)
		self.state['instructions'] = instructions
		scores_re = "High Scores: (.*)\n"
		scores = Variable('highScore')
		scores.set_re(scores_re, group=1)
		self.state['highScore'] = scores
		quit_re = "Quit game: (.*)\n"
		quit = Variable('quit')
		quit.set_re(quit_re, group=1)
		self.state['quit'] = quit
		left_re = "Left: (.*)\n"
		left = Variable('left')
		left.set_re(left_re, group=1)
		self.state['left'] = left
		right_re = "Right: (.*)\n"
		right = Variable('right')
		right.set_re(right_re, group=1)
		self.state['right'] = right
		jump_re = "Jump: (.*)\n"
		jump = Variable('jump')
		jump.set_re(jump_re, group=1)
		self.state['jump'] = jump
		jumpleft_re = "Jump Left: (.*)\n"
		jumpleft = Variable('jumpleft')
		jumpleft.set_re(jumpleft_re, group=1)
		self.state['jumpleft'] = jumpleft
		jumpright_re = "Jump Right: (.*)\n"
		jumpright = Variable('jumpright')
		jumpright.set_re(jumpright_re, group=1)
		self.state['jumpright'] = jumpright
		wait_re = "Wait: (.*)\n"
		wait = Variable('wait')
		wait.set_re(wait_re, group=1)
		self.state['wait'] = wait
		self._getMenuInstruction()
		self._firstScores()
		self.menu()

	def menu(self):
		self._getMenuInstruction()

	def instructions(self):
		self._getGameDescription()
		self._getMenuInstruction()

	def play(self):
		self.VIEW_HEIGHT = 13
		self.VIEW_WIDTH = 25
		self.SECRET_NUM = 600
		self.moves = 0
		self.write(self.state['play'])
		self.write("\n")
		#self._read_view()

		#descend stairs
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()

		#get to end
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()

		#setup next room choice
		for _ in range(37):
			self._wait()

	def start2zombie(self):
		self._jumpLeft()
		self._jumpLeft()
		self._jumpLeft()
		self._diedZombie()

	def start2bat(self):
		self._jumpLeft()
		self._jumpLeft()
		self._move_left()
		for _ in range(3):
			self._wait()
		self._jumpRight()
		self._jumpLeft()
		self._jumpLeft()
		self._jumpLeft()
		self._jumpLeft()
		self._jumpLeft()
		self._jumpLeft()				
		self._move_right()
		self._wait()
		self._wait()
		self._wait()
		self._diedBat()

	def start2first(self):
		#choose first
		self._move_left()

		#get to first
		self._jumpRight()
		self._move_right()
		self._move_right()
		self._move_right()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._move_right()
		self._jumpRight()
		self._move_right()
		self._move_right()

		#setup next room choice
		for _ in range(40):
			self._wait()

	def first2first(self):
		#choose first
		self._move_left()

		#get to finish
		self._jumpRight()
		self._wait()
		self._jumpRight()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._move_right()
		self._jumpRight()
		self._move_right()
		self._move_right()

		#setup next room choice
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()

		for _ in range(24):
			self._wait()

	def first2second(self):
		#choose second
		self._move_right()

		#get to second
		self._jumpRight()
		self._wait()
		self._jumpRight()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._move_right()
		self._jumpLeft()
		self._move_left()
		self._move_left()
		self._jumpRight()
		self._move_right()

		for _ in range(24):
			self._wait()

	def start2second(self):
		#choose second
		self._move_right()
		
		#get to finish
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._jumpLeft()
		self._move_left()
		self._jumpLeft()
		self._move_left()
		self._jumpLeft()

		#setup next room choice
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._jumpRight()
		self._jumpRight()
		self._move_right()
		self._wait()

		for _ in range(24):
			self._wait()

	def second2first(self):
		#choose first
		self._move_left()

		#get to first
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._jumpRight()
		self._wait()
		self._wait()
		self._wait()
		self._jumpRight()
		self._move_right()
		self._move_right()
		self._move_right()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._move_right()
		self._jumpRight()
		self._move_right()
		self._move_right()

		#setup next room choice
		self._wait()

		for _ in range(24):
			self._wait()

	def second2second(self):
    	#choose second
  		self._move_right()

		#get to finish
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._jumpRight()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._jumpRight()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._jumpLeft()
		self._move_left()
		self._move_left()
		self._jumpRight()
		self._move_right()

		for _ in range(24):
			self._wait()

	def start2last(self):
		#choose last
		self._wait()

		#move to treasure
		self._move_right()
		self._move_right()
		self._wait()
		self._move_right()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._wait()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._move_right()
		self._rightWin()

	def first2last(self):
		while(self.moves < self.SECRET_NUM):
			self.first2first()

		#choose last
		self._wait()

		#move to door
		self._jumpRight()
		self._wait()
		self._jumpRight()

		#move to treasure
		self._move_right()
		self._move_right()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._wait()
		self._wait()
		self._jumpRight()
		self._move_right()
		self._rightWin()

	def second2last(self):
		while(self.moves < self.SECRET_NUM):
			self.second2second()

		#choose last
		self._wait()

		#move to door
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._jumpRight()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._jumpRight()

		#move to treasure
		self._move_right()
		self._move_right()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._wait()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._move_right()
		self._rightWin()

	def _firstScores(self):
		self.write(self.state['highScore'])
		self.write("\n")
		#if len(self.highScores) == 0:
		#	no_scores_msg = "NO HIGH SCORES!\n"
		#	self.read(delim="\n", expect=no_scores_msg)
		#else:
		top_score_msg = "Dungeon conquered in " + str(self.highScores[0]['score']) + " moves " + self.highScores[0]['name'] + "\n"
		self.read(delim="\n", expect=top_score_msg)
		line_msg = "-------------------\n"
		self.read(delim="\n", expect=line_msg)
		title_msg =  " moves   |   name  \n"
		self.read(delim="\n", expect=title_msg)
		self.read(delim="\n", expect=line_msg)
		#score_pcre = r'([0-9]*). ([0-9]*)  (.*)\n'
		#self.read(delim="\n", expect=score_pcre, expect_format='pcre')
		#self.read(delim="\n", expect=score_pcre, expect_format='pcre')
		for index,score in enumerate(self.highScores[1:]):
			score_msg = str(index+2) + ". " + str(score['score']) + "  " + score['name'] + "\n"
			self.read(delim="\n", expect=score_msg)

	def scores(self):
		self.write(self.state['highScore'])
		self.write("\n")
		#if len(self.highScores) == 0:
		#	no_scores_msg = "NO HIGH SCORES!\n"
		#	self.read(delim="\n", expect=no_scores_msg)
		#else:
		top_score_msg = r'Dungeon conquered in ([0-9]*) moves (.*)\n'
		self.read(delim="\n", expect=top_score_msg, expect_format='pcre')
		line_msg = "-------------------\n"
		self.read(delim="\n", expect=line_msg)
		title_msg =  " moves   |   name  \n"
		self.read(delim="\n", expect=title_msg)
		self.read(delim="\n", expect=line_msg)
		score_pcre = r'([0-9]*). ([0-9]*)  (.*)\n'
		self.read(delim="\n", expect=score_pcre, expect_format='pcre')
		self.read(delim="\n", expect=score_pcre, expect_format='pcre')
		for _ in self.highScores[3:]:
			self.read(delim="\n", expect=score_pcre, expect_format='pcre')


	def attack1(self):
		self.VIEW_HEIGHT = 13
		self.VIEW_WIDTH = 25
		self.write(self.state['play'])
		self.write("\n")

		for _ in range(64):
			self._move_left()

		for _ in range(64):
			self._move_left()

		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._move_right()
		self._jumpRight()
		self._move_right()
		self._move_right()

		self._jumpRight()
		self._wait()
		self._wait()
		self._jumpRight()
		self._move_right()
		self._move_right()
		self._move_right()
		self._move_right()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._move_right()
		self._jumpRight()
		self._move_right()
		self._move_right()
		self._jumpRight()
		for _ in range(12):
			self._wait()
		self._jumpRight()
		for _ in range(8):
			self._move_right()
		self._move_left()
		self._move_left()
		self._move_left()
		self._wait()
		self._wait()
		self._wait()
		self._jump()		
		self._move_right()
		self._wait()
		self._wait()
		self._jumpRight()

		self._move_right()
		self._move_right()
		self._move_right()
		self._jumpLeft()
		self._move_left()
		self._jumpLeft()
		self._jumpRight()
		for _ in range(7):
			self._move_right()
		self._jumpRight()
		for _ in range(8):
			self._wait()
		self._jumpRight()
		self._move_right()
		self._move_right()
		self._move_right()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()		
		self._move_right()
		for _ in range(27):
			self._wait()		
		self._jumpRight()
		self._move_right()
		self._move_right()
		self._jumpRight()
		for _ in range(15):
			self._wait()
		self._jumpRight()

		self._move_right()
		self._move_right()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._move_right()				
		self._jumpRight()
		self._jumpRight()
		self._wait()
		self._wait()
		self._wait()
		self._jumpRight()
		self._jumpRight()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._wait()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._jumpRight()
		self._move_right()
		self.write(self.state['right'])
		self.write("\n")
		self.read(delim="\n", assign=self.state['win'])
		first_pcre = r'Move list: (.{512})'
		flag_pcre = r'(.{40})'
		last_pcre = r'(.*)\n'
		flag = Variable('flag')
		flag.set_re(flag_pcre, group=1)
		self.state['flag'] = flag
		self.read(length=523, expect=first_pcre, expect_format='pcre')
		self.read(length=40, assign=self.state['flag'])
		self.read(delim="\n", expect=last_pcre, expect_format='pcre')

	def quit(self):
		self._quit_game()
		return -1
