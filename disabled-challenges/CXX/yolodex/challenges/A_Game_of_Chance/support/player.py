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
from random import randint
from operator import add, mul

import support as sp
from common import DEBUG, CONFIG

class Player(object):
    def __init__(self, pid=0, magic_page=''):
        self.id = pid
        self.magic_page = magic_page
        self.current_mp_idx = 0
        self.magic_page_indices_used = set()
        self.cards = [0, 0]
        self.wallet = CONFIG['INITIAL_CASH']

    def __str__(self):
        return "(id: {0})".format(self.id)

    def __repr__(self):
        return self.__str__()

    def get_wager(self):
        if 2 == self.cards[0] or 3 == self.cards[0]:
            return 0
        wager = ord(self.magic_page[self.current_mp_idx]) 
        self.magic_page_indices_used.add(self.current_mp_idx)
        return wager

    def exchange_money(self, amount):
        self.wallet += amount
        if DEBUG:
            print "[p{0}] exchanged ${1}, new wallet balance ${2}".format(self.id, amount, self.wallet)

    def update_fp_idx(self, shift):
        if DEBUG:
            print "[p{0}] fp idx {1} + shift {2}".format(self.id, self.current_mp_idx, shift)
        self.current_mp_idx = (self.current_mp_idx + shift) % 4096
        if DEBUG:
            print "[p{0}] new fp idx {1}".format(self.id, self.current_mp_idx)

    def win(self):
        self.update_fp_idx(CONFIG['WIN_SHIFT'])
        if DEBUG:
            print "[p{0}] win".format(self.id)

    def loss(self):
        self.update_fp_idx(CONFIG['LOSS_SHIFT'])
        if DEBUG:
            print "[p{0}] loss".format(self.id)


