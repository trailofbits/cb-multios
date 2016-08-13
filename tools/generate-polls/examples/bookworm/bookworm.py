#!/usr/bin/env python
#
# Copyright (C) 2014 Brian Caswell <bmc@lungetech.com>
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
import imp
import os
import random
import string

print os.path.realpath(__file__)
filename = os.path.sep.join(os.path.realpath(__file__).split(os.path.sep)[:-1] + ['books.py'])
books = imp.load_source('books', filename).books


def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))


def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))


class Bookworm(Actions):

    def start(self):
        self.read(delim='\n', expect='Welcome to the book review server\n')
        self.state['reviews'] = []

    def menu(self):
        self.read(delim='Selection: ', expect="1. List Available "
                  "Books\n2. Books you have reviewed\n3. Review "
                  "more books\n4. Exit\nSelection: ")

    def list_books(self):
        self.write_number(1)
        expected = ['\nAvailable Books']
        for i, book in enumerate(books, 1):
            expected.append('%d: %s' % (i, book))
        self.read(delim='\n\n', expect='\n'.join(expected) + '\n\n')

    def reviewed(self):
        self.write_number(2)
        if 'reviews' not in self.state:
            self.state['reviews'] = []

        expected = ['Book Title: Your rating'] + self.state['reviews']
        self.read(delim='\n\n', expect='\n' + '\n'.join(expected) + '\n\n')

    def write_number(self, digit):
        trail = ''
        if self.chance(.01):
            trail = random_alpha(1, 30)
        self.write('%d%s\n' % (digit, trail))

    def review(self):
        self.write_number(3)
        self.read(delim='?: ', expect='\nWhat book would you like to '
                  'review (1 - 100)?: ')

        # 1% of the time, review an invalid book.  sometimes with strings,
        # sometimes with numbers, sometimes both
        if self.chance(.01):
            invalid = None
            while invalid is None:
                invalid = random_string(1, 30)
                if re.match('^0*(\d|\d{2}|100)\D', invalid):
                    invalid = None
            self.write("%s\n" % invalid)
            self.read(delim='\n', expect='Invalid book\n')
        else:
            choice = randint(1, 100)
            self.write_number(choice)
            self.read(delim='? ', expect='What rating would you like '
                      'to give this book? ')

            rating = 0
            # 1% of the time, send random jiberish as a response
            if self.chance(.01):
                self.write(random_alpha(1, 30))
            else:
                rating = randint(0, 0xFFFF)
                self.write_number(rating)

            if 'reviews' not in self.state:
                self.state['reviews'] = []

            self.state['reviews'].append("%s: %d" % (books[choice - 1],
                                                     rating))

    def bad_menu(self):
        if self.chance(.5):
            self.write_number(randint(6, 30))
        else:
            self.write('%s\n' % random_alpha(1, 98))
        self.read(delim='\n', expect='Invalid menu selection\n')

    def exit(self):
        self.write_number(4)
        self.read(delim='\n', expect='k, bye\n')

    def hidden(self):
        # This is the vulnerable condition.  Do we want to expose this?
        if 0:
            self.write_number(5)
