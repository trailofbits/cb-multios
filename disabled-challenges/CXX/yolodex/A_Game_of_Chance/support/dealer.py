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
from random import choice, randint

import support as sp
from common import DEBUG, CONFIG

from player import Player as p
from pov_deck import POV_DECK_BYTES

TRIGGER_BYTES = ['\x21', '\x5f', '\x3c', '\x42', '\x63', '\x51']

# 'NAME': (IDX, BYTE)
TRIGGER_BYTE_LOOKUP = {
    'DECK':     (0, TRIGGER_BYTES[0]),
    'DEAL':     (1, TRIGGER_BYTES[1]),
    'DATA':     (2, TRIGGER_BYTES[2]),
    'BALANCE':  (3, TRIGGER_BYTES[3]),
    'COUNT':    (4, TRIGGER_BYTES[4]),
    'QUIT':     (5, TRIGGER_BYTES[5]),
}

def get_non_trigger_byte():
    b = chr(randint(0, 255))
    while b in TRIGGER_BYTES:
        b = chr(randint(0,255))
    return b


class Dealer(object):
    def __init__(self, magic_page):
        self.players = []
        self.magic_page = magic_page
        self.deck = []
        self.ok = ''

    def add_players(self, p_count):
        for i in range(1, p_count + 1):
            noob = p(i, self.magic_page)
            self.players.append(noob)

        self.balances   = [0 for _ in range(p_count + 1)]
        self.wagers     = [0 for _ in range(p_count + 1)]
        self.results    = [0 for _ in range(p_count + 1)]
        self.deal1      = [0 for _ in range(p_count + 1)]
        self.deal2      = [0 for _ in range(p_count + 1)]
        if DEBUG:
            print "added {0} players".format(p_count)

    def make_trigger_buf(self, cmd_name):
        cmd = ''

        for cn in ['DECK', 'DEAL', 'DATA', 'BALANCE', 'COUNT', 'QUIT']:

            if cn == cmd_name:
                (idx, b) = TRIGGER_BYTE_LOOKUP[cmd_name]
                cmd += b
            else:
                cmd += get_non_trigger_byte()

        return cmd

    def make_new_random_deck(self, count, bad_cards=False):
        deck = [chr(randint(CONFIG['MIN_CARD_VALUE'], CONFIG['MAX_CARD_VALUE'])) for _ in range(count)]
        if True == bad_cards:
            deck[count/2] = chr(randint(CONFIG['MAX_CARD_VALUE'] + 1, 255))
            deck[count-1] = chr(randint(CONFIG['MAX_CARD_VALUE'] + 1, 255))

        if DEBUG:
            print "making new deck with {0} cards with {1}bad cards".format(count, "" if bad_cards else "no ")
        # if DEBUG:
        #     print "deck:"
        #     for c in deck:
        #         print " card 0x{0:02x},".format(ord(c))

        return deck

    def gen_ok(self):
        ok = [0,0,0,0,0,0,0,0]
        for idx in range(len(self.magic_page)):
            ok[idx % 8] ^= ord(self.magic_page[idx])
        self.ok = ''.join([chr(c) for c in ok])

    def get_packed_balances(self):
        p_bal = ''
        if DEBUG:
            print " balances were:  {0}".format(self.balances)
        for b in self.balances:
            p_bal += sp.pack_single_int32(b)

        return p_bal

    def get_packed_wagers(self):
        p_wag = ''
        if DEBUG:
            print " wagers were:  {0}".format(self.wagers)
        for w in self.wagers:
            p_wag += sp.pack_single_uint32(w)
        return p_wag

    def get_packed_results(self):
        p_res = ''
        if DEBUG:
            print " results were: {0}".format(self.results)
        for r in self.results:
            p_res += sp.pack_single_uint32(r)
        return p_res

    def enough_cards_for_round(self):
        return 0 < len(self.deck) and len(self.deck) >= len(self.players)

    def calculate_round_results(self):
        max_sum = 0
        if DEBUG:
            print "calculating round results"
        for idx in range(1, len(self.results)):
            if max_sum < self.deal1[idx] + self.deal2[idx]:
                max_sum = self.deal1[idx] + self.deal2[idx]
                if DEBUG:
                    print " updated round max_sum {0}".format(max_sum)

        for idx in range(1, len(self.results)):
            if DEBUG:
                print " calculating results for player {0}".format(idx)
            my_sum = self.deal1[idx] + self.deal2[idx]
            if DEBUG:
                print "  round sum {1}".format(idx, my_sum)
            if my_sum == max_sum:
                self.results[idx] = CONFIG['WIN']
                if DEBUG:
                    "  WIN".format(idx)
            else:
                self.results[idx] = CONFIG['LOSS']
                if DEBUG:
                    "  LOSS".format(idx)

    def get_next_card(self):
        c = self.deck.pop()
        if DEBUG:
            print "got next card 0x{0:02x}".format(ord(c))
        return c

    def play_one_round(self):

        if DEBUG:
            print "play one round with {0} players".format(len(self.players))

        # deal card to each player
        for p in self.players:
            c = self.get_next_card()
            self.deal1[p.id] = ord(c)
            p.cards[0] = ord(c)
            if DEBUG:
                print " player {0} dealt card 0x{1:02x}".format(p.id, ord(c))
        if DEBUG:
            print " cards from deal 1: {0}".format(self.deal1)

        # get wager from each player
        for p in self.players:
            self.wagers[p.id] = p.get_wager()
            if DEBUG:
                print " player {0} wagered {1}".format(p.id, self.wagers[p.id])

        # deal card to each player
        for p in self.players:
            c = self.get_next_card()
            self.deal2[p.id] = ord(c)
            p.cards[1] = ord(c)
            if DEBUG:
                print " player {0} dealt card 0x{1:02x}".format(p.id, ord(c))
        if DEBUG:
            print " cards from deal 2: {0}".format(self.deal2)

        self.calculate_round_results()

        # pay each player
        for p in self.players:
            if CONFIG['WIN'] == self.results[p.id]:
                p.exchange_money(self.wagers[p.id])
                p.win()
                self.balances[p.id] += self.wagers[p.id]
            else:
                p.exchange_money(-self.wagers[p.id])
                p.loss()
                self.balances[p.id] += -self.wagers[p.id]

    ## For testing ##
    def total_magic_page_indices_used(self):
        mpiu = set()
        for p in self.players:
            mpiu.update(p.magic_page_indices_used)
        mpiu_l = list(mpiu)
        mpiu_l.sort()
        return mpiu_l

    def check_magic_bytes_usage(self):

        mpiu_list = self.total_magic_page_indices_used()
        # print " total set of magic_page_indices_used: {0}".format(mpiu_list)
        for idx in range(len(mpiu_list) - 3):
            i0 = mpiu_list[idx]
            i1 = mpiu_list[idx + 1]
            i2 = mpiu_list[idx + 2]
            i3 = mpiu_list[idx + 3]

            if i0 == i1 - 1 and \
                i1 == i2 - 1 and \
                i2 == i3 - 1:
                if DEBUG:
                    print "#### Warning 4 consecutive magic page indices: {0}, {1}, {2}, {3}.".format(i0, i1, i2, i3)
                    print "magic total_magic_page_indices_used: {0}".format(mpiu_list)
                return [i0, i1, i2, i3]
        if DEBUG:
            print " Done checking for 4 consecutive magic page indices."
        return []

def check_deck(deck_sz=1000):
    if DEBUG:
        print "find_trigger_deck size {0}".format(deck_sz)
    # setup
    d = Dealer('A'*4096)
    d.add_players(CONFIG['PLAYER_COUNT'])

    # make deck
    deck = d.make_new_random_deck(deck_sz)
    d.deck = list(deck)

    mpiu_list = []
    while d.enough_cards_for_round():
        # play a round
        d.play_one_round()

        # break if found 4 consecutive fp indices
        mpiu_list = d.check_magic_bytes_usage()
        if [] != mpiu_list:
            if DEBUG:
                print "indices {0}".format(mpiu_list)
            return deck

    return []

def find_trigger_deck():
    deck_sz = 2500
    deck = check_deck(deck_sz)
    while [] == deck:
        deck_sz += 10
        deck = check_deck(deck_sz)
    if DEBUG:
        print "trigger deck len {0}, deck {1}".format(len(deck), deck)
    return deck

def test_trigger_deck(deck):
    if DEBUG:
        print "test_trigger_deck"
    # setup
    d = Dealer('A'*4096)
    d.add_players(CONFIG['PLAYER_COUNT'])
    d.deck = list(deck)

    mpiu_list = []
    while d.enough_cards_for_round():
        # play a round
        d.play_one_round()

        # break if found 4 consecutive fp indices
        mpiu_list = d.check_magic_bytes_usage()
        if [] != mpiu_list:
            # if DEBUG:
            print "trigger indices {0}".format(mpiu_list)
            return True

    return False

if __name__ == '__main__':
    # deck = find_trigger_deck()
    deck = POV_DECK_BYTES
    print test_trigger_deck(deck)



