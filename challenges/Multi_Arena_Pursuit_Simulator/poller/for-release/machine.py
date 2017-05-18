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

	harborMap = [
	#        -10,  -9,  -8,  -7,  -6,  -5,  -4,  -3,  -2,  -1,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13
			[100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,  13, 100, 100, 100, 100, 100], # 10
			[100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   7,   6,   7,   9, 100, 100, 100], # 9
			[100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   7,   5,   6,   7, 100, 100, 100, 100], # 8
			[100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   5,   5,   5,   6,   7,   8,   9, 100, 100], # 7
			[100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   4,   4,   5,   6,   7,   9,   9, 100, 100], # 6			
			[100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   3,   3,   4,   5,   6,   7,   8,   8, 100, 100], # 5
			[100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   2,   2,   2,   3,   4,   5,   6,   8,   9,   9, 100, 100], # 4			
			[100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   1,   1,   1,   1,   2,   3,   4,   5,   6,   6,   7, 100, 100, 100], # 3			
			[100, 100, 100, 100, 100, 100, 100, 100, 100,   1,   1,   1,   1,   1,   2,   3,   4,   5,   6,   7,   8,   9,   9, 100], # 2
			[100, 100, 100, 100, 100, 100, 100, 100, 100,   1,   0,   0,   1,   1,   2,   3,   4,   5,   6,   8,   9,   9,  10, 100], # 1
			[100, 100, 100, 100, 100, 100, 100, 100, 100,   0,   0,   0,   1,   1,   2,   3,   4,   5,   6,   7,   8,  13, 100, 100], # 0
			[100, 100, 100, 100, 100, 100, 100, 100,  13,   0,   0,   1,   1,   2,   3,   4,   5,   6,   7,   8,   8, 100, 100, 100], # -1
			[100, 100, 100, 100, 100, 100,   9,  12,  13,  13,  13,  13,   2,   3,   4,   5,   6,   7,   8,   9, 100, 100, 100, 100], # -2
			[100, 100, 100, 100, 100,  10,  11,  12,  12,  12,  12,  13,   3,   4,   5,   6,   7,   8,  10,   9, 100, 100, 100, 100], # -3
			[100, 100, 100, 100, 100,   9,  11,  11,  11,  11,  11,   4,   4,   5,   6,   7,   8,   9,  11, 100, 100, 100, 100, 100], # -4
			[100, 100, 100,   9, 100,   9,   9,  10,  10,   9,   5,   5,   5,   6,   7,   8,  10,  10, 100, 100, 100, 100, 100, 100], # -5
	        [100, 100, 100,  10,  10,   9,   8,   7,   6,   6,   6,   6,   6,   7,   8,  10,   9,  11, 100, 100, 100, 100, 100, 100], # -6
	   		[100, 100,  11,  11,  10,   9,   8,   7,   7,   7,   7,   7,   7,   8,   9,   9, 100,  12, 100, 100, 100, 100, 100, 100], # -7
			[100,  12,  12,  11,  10,   9,   8,   8,   8,   8,   8,   8,   8,   9,   9, 100, 100, 100, 100, 100, 100, 100, 100, 100], # -8
		    [100,  13,  12,  11,  10,   9,   9,   9,   9,   9,   9,   9,   9,   8,  10, 100, 100, 100, 100, 100, 100, 100, 100, 100], # -9
			[100, 100,  12, 100,  10,  10,  10,  10,  10,  11,  10, 100,  12,  11, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100], # -10
			[100, 100, 100,  11,  11,  11,   9,  12,  11,  12, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100], # -11
			[100, 100, 100,  13,  11,  10,  12,  10,  11, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100], # -12
			[100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100], # -13
			[100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100]  # -14

		  ]

	cityMap = [
			# -2,  -1,   0, 1,   2,   3,   4,   5,   6,   7
			[100, 100, 100, 8,  11, 100, 100, 100, 100, 100], # 7
			[100, 100, 100, 5,   8, 100, 100, 100, 100, 100], # 6
			[100, 100,   3, 4,   7,  10, 100, 100, 100, 100], # 5
			[100, 100,   2, 3,   4,   7, 100, 100, 100, 100], # 4
			[100,   1,   1, 1,   3,   6,   9, 100, 100, 100], # 3
			[100,   1,   1, 1,   2,   3,   6, 100, 100, 100], # 2
			[100,   0,   0, 0,   1,   1,   5,   8, 100, 100], # 1
			[100,   0,   0, 0,   1,   1,   2,   3, 100, 100], # 0
			[  9,   0,   0, 0,   1,   1,   3,   4,   5,   8], # -1
			[100,   7,   4, 3,   2,   3,   4,   7,   8,  11], # -2
			[100,  10,   7, 4,   3,   6,   7,  10, 100, 100], # -3
			[100, 100,  8, 5,   6,   9,  100, 100, 100, 100], # -4
			[100, 100, 11, 8, 100, 100,  100, 100, 100, 100]  # -5
		  ]

	def _getRandomNumber(self, minN, maxN):
		diff = maxN - minN + 1
		num = ord(self.magic_page[self.flag_idx: self.flag_idx+1])
		self.flag_idx += 1
		if(self.flag_idx) == 200:
			self.flag_idx = 0
		num = num % diff
		num += minN
		return num

	def _getXInBoat(self):
		self.x = self._getRandomNumber(-9, 9)

	def _getYInBoat(self):

		if self.x == -9:
			self.y = self._getRandomNumber(-9, -8)
		elif self.x ==  -8: 
			self.x = -9
			self.y = self._getRandomNumber(-9, -8)
		elif self.x ==  -7:
			self.y = self._getRandomNumber(-7, -5)
		elif self.x ==  -6:
			self.y = self._getRandomNumber(-10, -5)
		elif self.x ==  -5:
			self.y = self._getRandomNumber(-10, -3)
		elif self.x ==  -4:
			self.y = self._getRandomNumber(-8, -3)
		elif self.x ==  -3:
			self.y = self._getRandomNumber(-10, -2)
		elif self.x ==  -2:
			self.y = self._getRandomNumber(-10, 0)
		elif self.x ==  -1:
			self.y = self._getRandomNumber(-9, 0)
 			if(self.y == -1):
 				self.y = -2
 			if(self.y == 0):
 				self.y = -2
		elif self.x ==  0:
			self.y = self._getRandomNumber(-9, 0)
 			if(self.y < 0 and self.y > -2):
 				self.y = -2
 			if(self.y >= 0 and self.y < 2):
 				self.y = -2
		elif self.x ==  1:
			self.y = self._getRandomNumber(-9, 0)
 			if(self.y == 0):
 				self.y = -3
 			if(self.y == 1):
 				self.y = -3
		elif self.x ==  2:
			self.y = self._getRandomNumber(-9, 4)
		elif self.x ==  3:
			self.y = self._getRandomNumber(-8, 4)
		elif self.x ==  4:
			self.y = self._getRandomNumber(-7, 5)
		elif self.x ==  5:
			self.y = self._getRandomNumber(-5, 6)
		elif self.x ==  6:
			self.y = self._getRandomNumber(-4, 6)
		elif self.x ==  7:
			self.y = self._getRandomNumber(-5, 6)
		elif self.x ==  8:
			self.y = self._getRandomNumber(0, 1)
		elif self.x ==  9:
			self.y = self._getRandomNumber(0, 1)

	def _getXInCar(self):
		self.x = self._getRandomNumber(-2, 7)

	def _getYInCar(self):
		if self.x ==  -2: 
			self.y =  -1
		elif self.x == -1:
			self.y = self._getRandomNumber(-3, 3)
 			if(self.y < 0 and self.y > -2):
 				self.y = -2
 			if(self.y > 0 and self.y < 2):
 				self.y =  2
 		elif self.x == 0:
 			self.y = self._getRandomNumber(-5,5)
 			if(self.y < 0 and self.y > -2):
 				self.y =  -2
 			if(self.y >= 0 and self.y < 2):
 				self.y =  2		 
 		elif self.x == 1:
 			self.y = self._getRandomNumber(-5,7)
 			if(self.y < 0 and self.y > -2):
 				self.y =  -2
 			if(self.y > 0 and self.y < 2):
 				self.y =  2
		elif self.x == 2:
 			self.y =  self._getRandomNumber(-4,7)
		elif self.x == 3:
 			self.y =  self._getRandomNumber(-4,5)
		elif self.x == 4:
 			self.y =  self._getRandomNumber(-3,3)
		elif self.x == 5:
 			self.y =  self._getRandomNumber(-3,1)
		elif self.x == 6:
 			self.y =  self._getRandomNumber(-2,-1)
		elif self.x == 7:
 			self.y =  self._getRandomNumber(-2,-1)

 	def _bestCriminalMove(self, x, y):
 		value = 0

 		tmp = self.harborMap[23 - y - 13][x + 10 - 1]
 		if tmp > value:
 			value = tmp

  		tmp = self.harborMap[23 - y - 13][x + 10 + 1]
 		if tmp > value:
 			value = tmp

 		tmp = self.harborMap[23 - y - 13 + 1][x + 10]
 		if tmp > value:
 			value = tmp

  		tmp = self.harborMap[23 - y - 13 - 1][x + 10]
 		if tmp > value:
 			value = tmp

  		tmp = self.harborMap[23 - y - 13 + 1][x + 10 - 1]
 		if tmp > value:
 			value = tmp

  		tmp = self.harborMap[23 - y - 13 - 1][x + 10 + 1]
 		if tmp > value:
 			value = tmp

 		return value

 	def _moveCriminalInBoat(self):
		value = 0
		bestX = self.x
		bestY = self.y

		x = self.x
		y = self.y
		if x > -11 and x < 14 and y > -14 and y < 11:
			tmp = self.harborMap[23 - y - 13][x + 10] 
			if tmp > value: 
				value = tmp
				bestX = self.x
				bestY = self.y

		x = self.x + 1
		y = self.y
		if x > -11 and x < 14 and y > -14 and y < 11:
			tmp = self.harborMap[23 - y - 13][x + 10] 
			if tmp > value: 
				value = tmp
				bestX = self.x + 1
				bestY = self.y

		x = self.x
		y = self.y + 1
		if x > -11 and x < 14 and y > -14 and y < 11:
			tmp = self.harborMap[23 - y - 13][x + 10] 
			if tmp > value: 
				value = tmp
				bestX = self.x
				bestY = self.y + 1

		x = self.x - 1
		y = self.y
		if x > -11 and x < 14 and y > -14 and y < 11:
			tmp = self.harborMap[23 - y - 13][x + 10] 
			if tmp > value: 
				value = tmp
				bestX = self.x - 1
				bestY = self.y

		x = self.x
		y = self.y - 1
		if x > -11 and x < 14 and y > -14 and y < 11:
			tmp = self.harborMap[23 - y - 13][x + 10] 
			if tmp > value: 
				value = tmp
				bestX = self.x
				bestY = self.y - 1

		x = self.x + 1
		y = self.y + 1
		if x > -11 and x < 14 and y > -14 and y < 11:
			tmp = self.harborMap[23 - y - 13][x + 10] 
			if tmp > value: 
				value = tmp
				bestX = self.x + 1
				bestY = self.y + 1

		x = self.x - 1
		y = self.y - 1
		if x > -11 and x < 14 and y > -14 and y < 11:
			tmp = self.harborMap[23 - y - 13][x + 10] 
			if tmp > value: 
				value = tmp
				bestX = self.x - 1
				bestY = self.y - 1

		self.x = bestX
		self.y = bestY
		#print "Criminal moves. Criminal at (" + str(self.x) + ", " + str(self.y) + ")"



 	def _moveCriminal(self):
		value=0
		bestX=self.x
		bestY=self.y
		
		tmp = self.cityMap[12-self.y-5][self.x + 2]
		if tmp > value: 
			value = tmp
			bestX = self.x
			bestY = self.y

		tmp = self.cityMap[12-self.y-5][self.x + 2 + 1]
		if tmp > value: 
			value = tmp
			bestX = self.x+1
			bestY = self.y

		tmp = self.cityMap[12-self.y-5-1][self.x + 2]
		if tmp > value: 
			value = tmp
			bestX = self.x
			bestY = self.y+1

		tmp = self.cityMap[12-self.y-5][self.x + 2 - 1]
		if tmp > value: 
			value = tmp
			bestX = self.x-1
			bestY = self.y

		tmp = self.cityMap[12-self.y-5+1][self.x + 2]
		if tmp > value: 
			value = tmp
			bestX = self.x
			bestY = self.y-1

		self.x = bestX
		self.y = bestY

	def _moveLeftInBoat(self):
		newX = self.y
		newY = self.y - self.x
		self.x = newX - 2
		self.y = newY - 2
		#print "Move Left. Criminal at (" + str(self.x) + ", " + str(self.y) + ")"
		return 'L'		

	def _moveForwardInBoat(self):
		self.x = self.x - 2
		self.y = self.y - 2
		#print "Move Forward. Criminal at (" + str(self.x) + ", " + str(self.y) + ")"
		return 'F'

	def _moveRightInBoat(self):
		newX = self.x - self.y
		newY = self.x
		self.x = newX - 2
		self.y = newY - 2
		#print "Move Right. Criminal at (" + str(self.x) + ", " + str(self.y) + ")"
		return 'R'

 	def _moveForward(self):
 		self.y = self.y - 2
 		return 'F'

	def _moveRight(self):
		newX = self.y * -1
		newY = self.x - 2
		self.x = newX;
		self.y = newY;
		return 'R'

	def _makeMoveInBoat(self):
		value=100
		move = ''

		y = self.y - self.x - 2
		x = self.y - 2
		if x > -11 and x < 14 and y > -14 and y < 11:
			tmp = self.harborMap[23 - y - 13][x + 10]
			if tmp < 100:
				tmp = self._bestCriminalMove(x, y)
				if tmp < value: 
					value = tmp
					move = 'L'

		y = self.y - 2
		x = self.x - 2
		if x > -11 and x < 14 and y > -14 and y < 11:
			tmp = self.harborMap[23 - y - 13][x + 10]
			if tmp < 100:
				tmp = self._bestCriminalMove(x, y)
				if tmp < value: 
					value = tmp
					move = 'F'		

		y = self.x - 2
		x = self.x - self.y - 2
		if x > -11 and x < 14 and y > -14 and y < 11:
			tmp = self.harborMap[23 - y - 13][x + 10]
			if tmp < 100:
				tmp = self._bestCriminalMove(x, y)
				if tmp < value: 
					value = tmp
					move = 'R'

		if(move == 'L'):
			return self._moveLeftInBoat()
		elif(move == 'F'):
			return self._moveForwardInBoat()
		else:
			return self._moveRightInBoat()		

	def _makeMoveInCar(self):
		if self.y < 1 or self.x < -1:
			return self._moveRight()
		else:
			return self._moveForward()

	def start(self):
		#self.delay(100)
		self.flag_idx = 0

	def catchCriminalInCar(self):
		for i in range(100):
			self._getXInCar()
			self._getYInCar()
			#self.x = 4
			#self.y = -1
			criminal_str = "Criminal at (" + str(self.x) + ", " + str(self.y) + ")\n"
			self.read(delim="\n", expect=criminal_str)
			move_str = self._makeMoveInCar() + "#"
			while not (self.x > -2 and self.x < 2 and self.y > -2 and self.y < 2):
				self._moveCriminal()
				move_str += self._makeMoveInCar() + "#"
			self.write(move_str)
			caught_str = 'Criminal caught in ([0-9]*) moves\n'
			self.read(delim="\n", expect=caught_str, expect_format='pcre')

	def catchCriminalInBoat(self):
		for i in range(100):
			self._getXInBoat()
			self._getYInBoat()
			criminal_str = "Criminal at (" + str(self.x) + ", " + str(self.y) + ")\n"
			self.read(delim="\n", expect=criminal_str)
			move_str = self._makeMoveInBoat() + "#"
			while not self.harborMap[23 - self.y - 13][self.x + 10] == 0:
				self._moveCriminalInBoat()
				move_str += self._makeMoveInBoat() + "#"
			self.write(move_str)
			caught_str = 'Criminal caught in ([0-9]*) moves\n'
			self.read(delim="\n", expect=caught_str, expect_format='pcre')

	def attack1(self):
		self.catchCriminalInCar()
		self._getXInBoat()
		self._getYInBoat()
		self.x = 4
		self.y = -1
		moves = 0
		criminalX_re = r'Criminal at \((-?\d+),'
		criminalY_re = r' (-?\d+)\)\n'
		criminalX = Variable('criminalX')
		criminalY = Variable('criminalY')
		criminalX.set_re(criminalX_re, group=1)
		criminalY.set_re(criminalY_re, group=1)
		#criminal_str = "Criminal at (" + str(self.x) + ", " + str(self.y) + ")\n"
		#self.read(delim="\n", expect=criminal_str)
		self.read(delim=",", assign=criminalX)
		self.read(delim="\n", assign=criminalY)
		move_str = self._makeMoveInBoat() + "#"
		moves += 1
		while moves < 100000:
			while not self.harborMap[23 - self.y - 13][self.x + 10] == 1:
				self._moveCriminalInBoat()
				move_str += self._makeMoveInBoat() + "#"
				moves += 1
			self._moveCriminalInBoat()
			move_str += self._moveLeftInBoat() + "#"
			moves += 1
		while not self.harborMap[23 - self.y - 13][self.x + 10] == 0:
			self._moveCriminalInBoat()
			move_str += self._makeMoveInBoat() + "#"
		self.write(move_str)
		caught_str = 'Criminal caught in ([0-9]*) moves\n'
		self.read(delim="\n", expect=caught_str, expect_format='pcre')
		flag_re = r'(.*)'
		flag = Variable('flag')
		flag.set_re(flag_re, group=1)
		self.read(length=40, assign=flag)

	def quit(self):
		return -1
