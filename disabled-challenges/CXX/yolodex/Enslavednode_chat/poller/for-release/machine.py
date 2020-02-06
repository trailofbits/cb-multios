#!/usr/bin/env python

import math
import random
import string
import sys

from generator.actions import Actions

class Machine(Actions):
    WELCOME = (
        "\nWelcome to the Enslavednode chat server!\n"
        "The bots here love to talk, but they are shy...\n"
        "You need to get the ball rolling.\n"
    )

    PROMPT = "you > "

    def random_sentence(self):
        s = ''
        for i in xrange(random.randint(0, 16)):
            for k in xrange(random.randint(0, 256)):
                s += random.choice(string.letters)
            s += ' '
        return s

    def start(self):
        self.read(expect=self.WELCOME, length=len(self.WELCOME))

    def read_until_prompt(self):
        self.read(expect='.*', expect_format='pcre', delim=self.PROMPT)

    def dosomething(self):
        pass

    def call_reverse(self):
        to_rev = self.random_sentence()
        inp = ' '.join(['/rev', to_rev])
        self.write(inp + '\n')
        self.read(expect='case > ' + to_rev[::-1], delim='\n')

    def call_hello(self):
        inp = ' '.join(['/hello', self.random_sentence()])
        self.write(inp + '\n')
        self.read(expect='case > Hello, you.', delim='\n')

    def call_howsmart(self):
        inp = ' '.join(['/howsmart', self.random_sentence()])
        self.write(inp + '\n')
        self.read(expect='case > I have an intelligence rating of:.*',
                  expect_format='pcre', delim='\n')

    def call_pont(self):
        inp = ' '.join(['/pont', self.random_sentence()])
        self.write(inp + '\n')

    def jabber(self):
        self.write(self.random_sentence() + '\n')

    def part(self):
        self.write('/part\n')
        self.read(expect='BYE!', delim='\n')
