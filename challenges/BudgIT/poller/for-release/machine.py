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
import string
import random
import itertools
import math
from struct import *

class TemplateGenerator(Actions):

	def start(self):
		self.map = []
		self.mapSize = 100
		pass

	def newBudgetItem(self):
		if(len(self.map) < 128):
			instruction = pack('l', 1)
			self.write(instruction)
			key = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(9))
			self.write(key + '\x07')
			value = random.randint(1,1000)
			value_str = pack('i', value)
			self.write(value_str)
			self.map.append([key, value])
			self.read(delim="\n", expect="New budget created!\n")
#		else:
#			self.read(delim="\n", expect="No more entries\n")

	def newInBudgetTransaction(self):
		if(len(self.map) == 0):
			return 0
		instruction = pack('l', 2)
		self.write(instruction)
		pair = random.choice(self.map)
		while(pair[1] < 0):
			pair = random.choice(self.map)
		self.write(pair[0] + '\x07')
		amount = random.randint(0,pair[1])
		amount_str = pack('i', amount)
		self.write(amount_str)
		pair[1]-=amount

	def newOverBudgetTransaction(self):
		if(len(self.map) == 0):
			return 0
		instruction = pack('l', 2)
		self.write(instruction)
		pair = random.choice(self.map)
		while(pair[1] < 0):
			pair = random.choice(self.map)
		self.write(pair[0] + '\x07')
		amount = pair[1] + random.randint(1,100)
		amount_str = pack('i', amount)
		self.write(amount_str)
		pair[1]-=amount
		self.read(delim="\n", expect=pair[0] + " is over budget!\n")

	def getBudget(self):
		if(len(self.map) == 0):
			return 0
		instruction = pack('l', 3)
		self.write(instruction)
		pair = random.choice(self.map)
		self.write(pair[0] + '\x07')
		self.read(length=40, expect=str(pair[1])+"[0]*", expect_format='pcre')

	def deleteBudget(self):
		if(len(self.map) == 0):
			return 0
		instruction = pack('l', 6)
		self.write(instruction)
		pair = random.choice(self.map)
		self.write(pair[0] + '\x07')
		self.map.remove(pair)

	def sendReport(self):
		instruction = pack('l', 7)
		self.write(instruction)
		totalBalance = sum([pair[1] for pair in self.map])
		for x in range(0, len(self.map)):
			self.read(length=24, expect=".*", expect_format='pcre')
			self.read(length=40, expect=".*", expect_format='pcre')
		self.read(length=40, expect=str(totalBalance)+"[0]*", expect_format='pcre')

	def quit(self):
		instruction = pack('l', 8)
		self.write(instruction)
		return -1
