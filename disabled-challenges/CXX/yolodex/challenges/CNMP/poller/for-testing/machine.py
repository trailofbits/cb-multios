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

	def help(self):
		self.write("HELP\x07")
		expect_str = "Is our menu so extensive that you cannot remember all of the commands? " \
        			 "Here, let me jog all 6 of your neurons:\n"
		self.read(delim='\n', expect=expect_str, expect_format='asciic')

	def list_jokes(self):
		self.write("LIST\x07")
		# joke is list of lines with format "joke_id: joke\n"
		for idx, joke in enumerate(self.state['jokes'], 0):
			self.read(delim='\n', 
				expect="{0}: {1}\n".format(idx, joke), 
				expect_format='asciic')

	def count(self):
		self.write("COUNT\x07")
		# read count string
		expect_str = "Current CNMP joke count is {0}. Enjoy!\n".format(len(self.state['jokes']))
		self.read(delim='\n', expect=expect_str, expect_format='asciic')

	def menu_cmd(self):
		self.write("MENU\x07")

	def bad_cmd_die(self):
		# submit a bad command; will exit connection
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

	def add_msg(self):
		expect_str = ""
		self.write("ADD\x07")
		self.read(delim="\n", expect="So, you think you have a good Chuck Norris joke? "\
        "Give me the joke string already....\n", expect_format='asciic')
		self.read(delim='> ', expect='ADD> ', expect_format='asciic')

		# submit a bad message; will exit connection
		# bad message: (> MAX_JOKE_STRING_LEN chars, i.e. MAX_JOKE_STRING_LEN*'A' w/o '\x07')
		if self.chance(0.0001):
			joke = random_string(self.MAX_JOKE_STRING_LEN, self.MAX_JOKE_STRING_LEN)
			expect_str = "\nAre you kidding me? What is that garbage? " \
    				"I thought my instructions were pretty straight forward. " \
    				"Try again.\n"
			self.write('{0}'.format(joke))
			self.read(delim='.\n', expect=expect_str, expect_format='asciic')
			return -1
		# submit a bad joke
		# bad joke (MAX_JOKE_STRING_LEN-1 chars, i.e (MAX_JOKE_STRING_LEN-1)*'A' + \x07)
		elif self.chance(0.001):
			joke = random_string(self.MAX_JOKE_STRING_LEN - 1, self.MAX_JOKE_STRING_LEN - 1)
			expect_str = "\nThat joke you gave me is crap! " \
				        "For that, you get to start over!\n"
			self.write('{0}\x07'.format(joke))
			self.read(delim='!\n', expect=expect_str, expect_format='asciic')
		else:
			joke = random_string(1, self.MAX_JOKE_STRING_LEN - 2)
			self.write('{0}\x07'.format(joke))
			joke_count = len(self.state['jokes'])

			if joke_count < self.MAX_JOKES:
				# add a joke
				expect_str = "Joke added. Thanks for sharing! Your joke is ID: {0}\n".format(joke_count)
				self.state['jokes'].append(joke)

			else:
				# joke db is full
				expect_str = "Lordy, lordy, I've had enough Chuck Norris jokes. Go away.\n"

			self.read(delim='\n', expect=expect_str, expect_format='asciic')

	def show(self):
		expect_str = "Give me the ID of the joke you want to read. Or better yet, " \
			        "enter RANDOM and I'll choose one for you.\n"
		self.write("SHOW\x07")
		self.read(delim="\n", expect=expect_str, expect_format="asciic")

	def show_prompt(self):
		expect_str = 'SHOW> '
		self.read(delim='> ', expect=expect_str, expect_format='asciic')

	def show_msg_good(self):
		expect_str = ""
		expect_format='asciic'
		joke_id = ""
		# find the easteregg joke
		if self.chance(0.001):
			joke_id = "1337"
			expect_str = "Congratulations, you are the only person in the past, present " \
        					"or future to beat Chuck Norris.\n"
		else:
			# choose a RANDOM joke
			if self.chance(0.2):
				joke_id = "RANDOM"
				expect_str = "[0-9]+: (.*)\n"
				expect_format='pcre'
			else:
				# id form 0 to joke_count - 1
				joke_count = len(self.state['jokes'])
				joke_id = str(randint(0, joke_count - 1))
				expect_str = "{0}: {1}\n".format(joke_id, self.state['jokes'][int(joke_id)])

		self.write("{0}\x07".format(joke_id))
		self.read(delim='\n', expect=expect_str, expect_format=expect_format)

	def show_msg_bad(self):
		# submit a bad joke id, w/ len < self.JOKE_ID_CHAR_LEN
		joke_id = ""
		if self.chance(0.33):
			# numeric < 0
			joke_id = "-1{0}".format(random_digits(1,self.JOKE_ID_CHAR_LEN - 5))

		elif self.chance(0.33):
			#not numeric that is not "RANDOM", w/ len < self.JOKE_ID_CHAR_LEN
			joke_id = random_alpha(1, self.JOKE_ID_CHAR_LEN - 1)
			if joke_id == "RANDOM":
				joke_id  = random_alpha(1, self.JOKE_ID_CHAR_LEN - 1)

		# submit a bad joke id w/ len = self.JOKE_ID_CHAR_LEN w/o '\x07'
		# will exit connection
		elif self.chance(0.0001):
			joke_id = "1{0}".format(random_digits(self.JOKE_ID_CHAR_LEN-1, self.JOKE_ID_CHAR_LEN-1))
			self.write("{0}".format(joke_id))
			expect_str = "\nAre you kidding me? What is that garbage? " \
				        "I thought my instructions were pretty straight forward. Try again.\n"
			self.read(delim='.\n', expect=expect_str, expect_format='asciic')
			return -1

		else:
			# number >= len(jokedb), not 1337, w/ len < self.JOKE_ID_CHAR_LEN
			joke_id = len(self.state['jokes']) + 1338

		self.write("{0}\x07".format(joke_id))
		expect_str = "\nWhat do you take me for? That ID is bogus! Try again.\n"
		self.read(delim='.\n', expect=expect_str, expect_format='asciic')




