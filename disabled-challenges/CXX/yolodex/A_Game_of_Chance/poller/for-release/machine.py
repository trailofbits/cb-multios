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
from common import DEBUG, CONFIG
from dealer import Dealer

class TemplatePoller(Actions):

    def start(self):
        #self.delay(100)
        if DEBUG:
            print "------- start -----------"
        self.state['e'] = Dealer(self.magic_page)
        self.state['e'].add_players(CONFIG['PLAYER_COUNT'])
        self.state['e'].gen_ok()


    def new_deck(self, deck=[], allow_bad=True):
        '''
        Give the dealer a new deck.
        '''
        if DEBUG:
            print "cmd: new deck -----------"

        # cmd
        byte_str = self.state['e'].make_trigger_buf('DECK')

        bad_cards = False
        if True == allow_bad and self.chance(0.001):
            if DEBUG:
                print "deck includes bad cards"
            bad_cards = True

        if [] == deck:
            deck = self.state['e'].make_new_random_deck(randint(500,3500), bad_cards)

        # number of cards (uint32)
        byte_str += sp.pack_single_uint32(len(deck))
        # cards (array of uint8)
        byte_str += sp.pack_single_string(''.join(deck))
        self.write(byte_str)

        # self.state['e'].ok
        self.read(length=len(self.state['e'].ok), expect=self.state['e'].ok)

        if False == bad_cards:
            self.state['e'].deck = deck
            return 0
        else:
            return -1

    def deal_one_round(self):
        '''
        Instruct dealer to deal one round to players
        '''
        if DEBUG:
            print "cmd: deal one round -----------"

        self.write(self.state['e'].make_trigger_buf('DEAL'))

        enough_cards = self.state['e'].enough_cards_for_round()

        self.read(length=len(self.state['e'].ok), expect=self.state['e'].ok)
        if False == enough_cards:
            if DEBUG:
                print "not enough cards for a round"
            return -1
        else:
            if DEBUG:
                print "enough cards for a round"
            self.state['e'].play_one_round()
            if DEBUG:
                mpiu = self.state['e'].total_magic_page_indices_used()
                print "## fp indices testing ##"
                self.state['e'].check_magic_bytes_usage()

            return 0

    def get_round_data(self):
        '''
        Ask dealer for round data
        '''
        if DEBUG:
            print "cmd: get round data -----------"

        self.write(self.state['e'].make_trigger_buf('DATA'))

        pw = self.state['e'].get_packed_wagers()
        pr = self.state['e'].get_packed_results()

        self.read(length=len(pw)+len(pr))

        self.read(length=len(self.state['e'].ok), expect=self.state['e'].ok)

    def get_balance(self):
        '''
        Ask dealer for house balance per player
        '''
        if DEBUG:
            print "cmd: get balances -----------"

        self.write(self.state['e'].make_trigger_buf('BALANCE'))

        balances = self.state['e'].get_packed_balances()

        self.read(length=len(balances))

        self.read(length=len(self.state['e'].ok), expect=self.state['e'].ok)

    def get_player_count(self):
        '''
        Ask dealer for the number of players
        '''
        if DEBUG:
            print "cmd: get player count -----------"

        self.write(self.state['e'].make_trigger_buf('COUNT'))

        self.read(length=4, expect=sp.pack_single_uint32(CONFIG['PLAYER_COUNT']))

        self.read(length=len(self.state['e'].ok), expect=self.state['e'].ok)

    def quit(self):
        '''
        Quit cleanly
        '''
        if DEBUG:
            print "cmd: quit -----------"

        self.write(self.state['e'].make_trigger_buf('QUIT'))

        self.read(length=len(self.state['e'].ok), expect=self.state['e'].ok)

        return -1

    def bogus(self):
        '''
        Send a bogus command
        '''
        if DEBUG:
            print "cmd: bogus -----------"

        self.write(self.state['e'].make_trigger_buf('BOGUS'))

        self.read(length=len(self.state['e'].ok), expect=self.state['e'].ok)

        return -1

    def broker(self):
        '''
        Branching node for all nodes
        '''
        return 0
