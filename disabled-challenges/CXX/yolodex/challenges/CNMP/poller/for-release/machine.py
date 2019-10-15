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

CNMP_DIR = dirname(dirname(dirname(abspath(__file__))))
sys.path.append(join(CNMP_DIR, "support"))
from jokes import Jokes


def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))

def random_digits(a, b):
    chars = string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))


class CNMP(Actions):

	MAX_JOKES=256
	MAX_JOKE_STRING_LEN=512
	JOKE_ID_CHAR_LEN=11
	CMD_CHAR_LEN=20

	def _load_jokes(self):
		self.state['jokes'] = Jokes().get_jokes()

	def start(self):
		self._load_jokes()
		self.read(delim="\n", 
			expect="This is the Chuck Norris (joke) Management Protocol (CNMP).\n", 
			expect_format='asciic')
		self.read(delim="\n", 
			expect="We know you need a break, so take some time and amuse yourself. " \
  			      "If you have a good Chuck Norris joke, you can add it to our listing.\n", 
			expect_format='asciic')

	def menu(self):
		self.read(delim="\n", 
			expect="Enter one of these commands:\n", 
			expect_format='asciic')
		self.read(delim="\n", 
			expect="  LIST  - list all jokes\n", 
			expect_format='asciic')
		self.read(delim="\n", 
			expect="  ADD   - upload your own joke\n", 
			expect_format='asciic')
		self.read(delim="\n", 
			expect="  COUNT - find out how many jokes we have to offer you\n", 
			expect_format='asciic')
		self.read(delim="\n", 
			expect="  SHOW  - show a joke\n", 
			expect_format='asciic')
		self.read(delim="\n", 
			expect="  MENU  - display this menu\n", 
			expect_format='asciic')
		self.read(delim="\n", 
			expect="  HELP  - you gotta be kididin' me!\n", 
			expect_format='asciic')
		self.read(delim="\n", 
			expect="  QUIT  - take off eh?\n", 
			expect_format='asciic')

	def root_prompt(self):
		self.read(delim='> ', expect='> ', expect_format='asciic')

	def empty(self):
		self.write("\x07")

	def quit(self):
		self.write("QUIT\x07")
		expect_str = "Thanks for the laughs. Come back soon!\n"
		self.read(delim='\n', expect=expect_str, expect_format='asciic')
		return -1

	def list_jokes(self):
		self.write("LIST\x07")
		# joke is list of lines with format "joke_id: joke\n"
		for idx, joke in enumerate(self.state['jokes'], 0):
			self.read(delim='\n', 
				expect="{0}: {1}\n".format(idx, joke), 
				expect_format='asciic')

	def bad_cmd_die(self):
		# 0.001% of the time, submit a bad command; will exit connection
		# bad command: (self.CMD_CHAR_LEN chars w/o trailing '\x07')
		# have to stay w/in CMD_CHAR_LEN else poller will fail attempting to
		# write the extra bytes that the CB will never read
		cmd = random_string(self.CMD_CHAR_LEN, self.CMD_CHAR_LEN)
		expect_str = "\nAre you kidding me? What is that garbage? " \
			"I thought my instructions were pretty straight forward. " \
			"Try again.\n"
		self.write('{0}'.format(cmd))
		self.read(delim='.\n', expect=expect_str, expect_format='asciic')
		return -1
