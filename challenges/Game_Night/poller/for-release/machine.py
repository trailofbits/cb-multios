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

from generator.actions import Actions
from os.path import dirname, abspath, join
import random
import string
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), 'support'))
from support import Support

class GameNight(Actions):
    def start(self):
        self.delay(50)
        self.state['model'] = Support(self.magic_page)

    def game(self):
        self.read(delim='\n', expect='Shall we play a game?\n')
        self.read(delim='\n', expect='\n')
        self.read(delim='\n', expect='1. Hugman\n')
        self.read(delim='\n', expect='2. Chess\n')
        self.read(delim='\n', expect='3. Sudoku\n')
        self.read(delim='\n', expect='4. Gallon Challenge\n')
        self.read(delim='\n', expect='5. Safari Zone\n')
        self.read(delim='\n', expect='6. Chance of Survival\n')
        self.read(delim='\n', expect='7. Lesson in Futility\n')
        self.read(delim='\n', expect='8. Quit\n')
        self.read(delim='\n', expect='\n')

    def invalid(self):
        self.write('%s\n' % random.randint(9, 0xffffffff))

    def hugman(self):
        self.write('1\n')
        for i in xrange(7):
            self.read(delim='\n', expect_format='pcre', expect='                     --------\n')
            self.read(delim='\n', expect_format='pcre', expect='                     |      |\n')
            self.read(delim='\n', expect_format='pcre', expect='                     .      |\n')
            self.read(delim='\n', expect_format='pcre', expect='                    ...     |\n')
            self.read(delim='\n', expect_format='pcre', expect='                     .      |\n')
            self.read(delim='\n', expect_format='pcre', expect='                    . .     |\n')
            self.read(delim='\n', expect_format='pcre', expect='                            |\n')
            self.read(delim='\n', expect_format='pcre', expect='                     _______|\n')
            self.read(delim='\n', expect_format='pcre', expect='                             \n')
            self.read(delim='\n', expect_format='pcre', expect='                             \n')
            self.read(delim='\n', expect_format='pcre', expect='        . . . . . . . .      \n')
            self.read(delim='\n', expect_format='pcre', expect='Incorrect: .*\n')

            self.write(':')

        self.read(delim='\n', expect_format='pcre', expect='                     --------\n')
        self.read(delim='\n', expect_format='pcre', expect='                     |      |\n')
        self.read(delim='\n', expect_format='pcre', expect='                     .      |\n')
        self.read(delim='\n', expect_format='pcre', expect='                    ...     |\n')
        self.read(delim='\n', expect_format='pcre', expect='                     .      |\n')
        self.read(delim='\n', expect_format='pcre', expect='                    . .     |\n')
        self.read(delim='\n', expect_format='pcre', expect='                            |\n')
        self.read(delim='\n', expect_format='pcre', expect='                     _______|\n')
        self.read(delim='\n', expect_format='pcre', expect='                             \n')
        self.read(delim='\n', expect_format='pcre', expect='                             \n')
        self.read(delim='\n', expect_format='pcre', expect='        . . . . . . . .      \n')

        self.state['model'].hugman_round += 1
        if self.state['model'].hugman_round == 6 or self.state['model'].hugman_round == 0xffffffff:
            self.state['model'].hugman_round += 1

        self.read(delim='\n', expect_format='pcre', expect='Sorry, the word was ........!\n')

    def chess(self):
        board, move = self.state['model'].do_chess()

        self.write('2\n')
        self.read(delim='\n', expect='Welcome to chessmaster 0x8000, enter your board:\n')
        self.write('\n'.join([''.join(row) for row in board]) + '\n')
        self.read(delim='\n', expect='Muahhaha, I move to %s\n' % move)

        # A valid chess breaks the cookie check, so look for propmpt and then go right to quit
        self.read(delim='\n', expect='Shall we play a game?\n')
        self.read(delim='\n', expect='\n')
        self.read(delim='\n', expect='1. Hugman\n')
        self.read(delim='\n', expect='2. Chess\n')
        self.read(delim='\n', expect='3. Sudoku\n')
        self.read(delim='\n', expect='4. Gallon Challenge\n')
        self.read(delim='\n', expect='5. Safari Zone\n')
        self.read(delim='\n', expect='6. Chance of Survival\n')
        self.read(delim='\n', expect='7. Lesson in Futility\n')
        self.read(delim='\n', expect='8. Quit\n')
        self.read(delim='\n', expect='\n')

    def sudoku(self):
        board = self.state['model'].do_sudoku()
        self.write('3\n')
        self.read(delim='\n', expect='Let me help you cheat at sudoku, enter your board n00b:\n')
        self.write('\n'.join([''.join([str(n) for n in row]) for row in board]) + '\n')
        self.read(delim='\n', expect='Solved!\n')
        for row in board:
            self.read(delim='\n', expect=''.join([str(n) for n in row]) + '\n')
        self.read(delim='\n', expect='\n')

    def gallon(self):
        self.write('4\n')
        self.read(delim='\n', expect='Give me a countdown!\n')
        self.write('0\n')
        self.read(delim='\n', expect='CHUG! ' * 100 + '\n')
        self.read(delim='\n', expect='Nice!\n')

    def safari(self):
        self.write('5\n')
        self.read(delim='\n', expect='Welcome to the Safari Zone!\n')

        index = self.state['model'].hugman_round
        if index > 6:
            self.read(delim='\n', expect='Nothing happened...\n')
            return

        monsters = ['Pidgeon', 'RegularRat', 'ElectricRat', 'Centipede-Thing', 'Caterpillar', 'Carp']
        monster = monsters[index]
        self.state['model'].hugman_round = ord(self.state['model'].get_flag_byte(index + 1)) % 6
        capture_chance = 128
        run_chance = 128
        round_ = 0

        self.read(delim='\n', expect='A wild %s has appeared!\n' % monster)
        while True:
            self.read(delim='\n', expect='What to do?\n')
            self.read(delim='\n', expect='1. Ball\n')
            self.read(delim='\n', expect='2. Rock\n')
            self.read(delim='\n', expect='3. Bait\n')
            self.read(delim='\n', expect='4. Run\n')
            self.read(delim='\n', expect='\n')

            move = random.randint(1, 4)
            self.write('%s\n' % move)

            if round_ > 10 or (round_ > 0 and run_chance >= ord(self.state['model'].get_flag_byte(round_))):
                self.read(delim='\n', expect='%s got away :(\n' % monster)
                return

            round_ += 1

            if move == 1:
                if capture_chance >= ord(self.state['model'].get_flag_byte(round_)):
                    self.read(delim='\n', expect='Congratulations, you\'ve caught %s!\n' % monster)
                    self.read(delim='\n', expect='Please enter a nickname:\n')

                    nickname = 0x41414141;
                    self.write('%s\n' % hex(nickname)[2:])

                    if 0 in self.state['model'].safari_party:
                        self.read(delim='\n', expect='AAAA has joined your party\n')
                        self.state['model'].safari_party[self.state['model'].safari_party.index(0)] = index + 1
                    else:
                        self.read(delim='\n', expect='AAAA was transferred to box 1 in your PC\n')

                    return
                else:
                    self.read(delim='\n', expect='Darn! Almost had it!\n')
                    round_ += 1
            elif move == 2:
                capture_chance = (capture_chance * 2) & 0xff
                run_chance = (run_chance * 2) & 0xff
            elif move == 3:
                capture_chance = (capture_chance / 2) & 0xff
                run_chance = (run_chance / 2) & 0xff
            elif move == 4:
                self.read(delim='\n', expect='Got away safely!\n')
                return

    def roulette(self):
        self.write('6\n')
        reponses = ['Is this thing on?', '*CLICK*', '*CLICK*', '*CLICK*', '*NERVOUS LOOK*', '*CRAZY EYES*', 'WHEW!']
        for x in self.state['model'].safari_party:
            self.read(delim='\n', expect=reponses[x] + '\n')

    def wargames(self):
        self.write('7\n')
        self.read(delim='\n', expect='Wouldn\'t you prefer a nice game of chess?\n')
        self.read(delim='\n', expect='A strange game. The only winning move is not to play.\n')

    def quit(self):
        self.write('8\n')

