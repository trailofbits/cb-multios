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
import ais
from common import CONFIG


class AisToEnglish(Actions):

	DEBUG = False
	DEBUG_ERR = DEBUG or False
	DEBUG_FUNC = DEBUG or False
	DEBUG_FUNC2 = DEBUG or False
	FAIL_CHANCE = 0.0001
	INVALID_SENTENCE = "INVALID SENTENCE."
	INVALID_MSG = "INVALID MESSAGE."
	PARTIAL_MSG = "PARTIAL AIS MESSAGE."

	def start(self):
		pass

	def type_one(self):
		'''
		Send type 1 message.
		'''
		m1 = ais.MsgType1()
		s1 = ais.Sentence(m1)
		[s] = s1.get_sentences()
		self.write("{0}\x07".format(s))
		eng = m1.get_engl_str()
		self.read(length=len(eng), expect=eng)

	def type_one_bad(self):
		'''
		Send a malformed type 1 message.
		'''
		m1 = ais.MsgType1()
		s1 = ais.Sentence(m1)
		[s] = s1.get_sentences()
		eng = self.INVALID_SENTENCE

		# bad checksum
		if self.chance(self.FAIL_CHANCE):
			cs = s[-2:]
			cs = int(cs, 16) + 1
			cs = '{0:0>2}'.format(hex(cs)[2:].upper())
			s = "{0}{1}".format(s[:-2], cs)
		# invalid msg
		elif self.chance(self.FAIL_CHANCE):
			s = s[15:]
		# invalid start chars
		else:
			rest = s[6:]
			s = "{0}{1}".format(sp.random_alpha(3,6), rest)

		self.write(s + '\x07')
		self.read(length=len(eng), expect=eng)

	def type_four(self):
		'''
		Send a type 4 message
		'''
		m4 = ais.MsgType4()
		s4 = ais.Sentence(m4)
		[s] = s4.get_sentences()
		self.write("{0}\x07".format(s))
		eng = m4.get_engl_str()
		self.read(length=len(eng), expect=eng)

	def type_four_bad(self):
		'''
		Send a malformed type 4 message.
		'''
		m4 = ais.MsgType4()
		s4 = ais.Sentence(m4)
		[s] = s4.get_sentences()
		eng = self.INVALID_SENTENCE

		# bad checksum
		if self.chance(self.FAIL_CHANCE):
			cs = s[-2:]
			cs = int(cs, 16) + 1
			cs = '{0:0>2}'.format(hex(cs)[2:].upper())
			s = "{0}{1}".format(s[:-2], cs)
		# invalid msg
		elif self.chance(self.FAIL_CHANCE):
			s = s[15:]
		# invalid start chars
		else:
			rest = s[6:]
			s = "{0}{1}".format(sp.random_alpha(3,6), rest)

		self.write("{0}\x07".format(s))
		self.read(length=len(eng), expect=eng)

	def type_five(self):
		'''
		Send a type 5 message.
		'''
		m5 = ais.MsgType5()
		s5 = ais.Sentence(m5)
		[s_p1, s_p2] = s5.get_sentences()
		# print "5 p1: '{0}'".format(s_p1)
		self.write("{0}\x07".format(s_p1))
		# print "read '{0}'".format(self.PARTIAL_MSG)
		self.read(length=len(self.PARTIAL_MSG), expect=self.PARTIAL_MSG)
		# print "5 p2: '{0}'".format(s_p2)
		self.write("{0}\x07".format(s_p2))

		eng = m5.get_engl_str()
		# print "read '{0}'".format(eng)
		self.read(length=len(eng), expect=eng)

	def type_five_bad(self):
		'''
		Send a malformed type 5 message.
		'''
		m5 = ais.MsgType5()
		s5 = ais.Sentence(m5)
		[s_p1, s_p2] = s5.get_sentences()
		eng = self.INVALID_SENTENCE

		if self.chance(self.FAIL_CHANCE): # invaild part 1
			# bad checksum
			if self.chance(self.FAIL_CHANCE):
				cs = s_p1[-2:]
				cs = int(cs, 16) + 1
				cs = '{0:0>2}'.format(hex(cs)[2:].upper())
				s_p1 = "{0}{1}".format(s_p1[:-2], cs)

			# invalid msg
			elif self.chance(self.FAIL_CHANCE):
				s_p1 = s_p1[15:]
			# invalid start chars
			else:
				rest = s_p1[6:]
				s_p1 = "{0}{1}".format(sp.random_alpha(3,5), rest)

			self.write("{0}\x07".format(s_p1))
			self.read(length=len(eng), expect=eng)

		else: # invalid part 2
			# bad checksum
			if self.chance(self.FAIL_CHANCE):
				cs = s_p2[-2:]
				cs = int(cs, 16) + 1
				cs = '{0:0>2}'.format(hex(cs)[2:].upper())
				s_p2 = "{0}{1}".format(s_p2[:-2], cs)
			# invalid msg
			elif self.chance(self.FAIL_CHANCE):
				s_p2 = s_p2[15:]
			# invalid start chars
			else:
				rest = s_p2[6:]
				s_p2 = "{0}{1}".format(sp.random_alpha(3,5), rest)

			self.write("{0}\x07".format(s_p1))
			self.read(length=len(self.PARTIAL_MSG), expect=self.PARTIAL_MSG)

			self.write("{0}\x07".format(s_p2))
			self.read(length=len(eng), expect=eng)

	def exit(self):
		'''
		End the poller. This node is terminal.
		'''
		return -1

