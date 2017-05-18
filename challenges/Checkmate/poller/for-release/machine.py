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

from generator.actions import Actions
from os.path import dirname, abspath, join
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
from support import Support

class Checkmate(Actions):
    def start(self):
        self.delay(50)
        self.state['model'] = Support(self.magic_page)

        output = self.state['model'].board_string()
        self.read(length=len(output), expect=output)

        prompt = self.state['model'].prompt_string()
        self.read(length=len(prompt), expect=prompt)

    def move(self):
        pass

    def valid_move(self):
        move = self.state['model'].get_valid_move()
        san = move.to_san()
        self.comment('Valid move')
        self.write(san + '\n')
        self.read(length=len(san) + 2, expect='\n' + san + '\n')

        result = self.state['model'].apply_move(move)
        self.state['model'].next_player()
        output = self.state['model'].board_string()

        csum = self.state['model'].calculate_csum(result)
        csum_str = '%x' % csum
        csum_str = '0' * (8 - len(csum_str)) + csum_str + '\n'
        self.read(length=len(csum_str), expect=csum_str)

        if result == 1:
            self.read(delim='\n', expect='CHECK!')
        elif result == 2:
            self.read(delim='\n', expect='CHECKMATE!')
        elif result == 3:
            self.read(delim='\n', expect='STALEMATE!')

        if result == 2 or result == 3:
            self.state['model'].reset()
            output = self.state['model'].board_string()

        self.read(length=len(output), expect=output)

        prompt = self.state['model'].prompt_string()
        self.read(length=len(prompt), expect=prompt)

    def invalid_move(self):
        move = self.state['model'].get_invalid_move()
        san = move.to_san()
        self.comment('Invalid move')
        self.write(san + '\n')
        self.read(delim='\n', expect='INVALID MOVE!')

        output = self.state['model'].board_string()
        self.read(length=len(output), expect=output)

        prompt = self.state['model'].prompt_string()
        self.read(length=len(prompt), expect=prompt)

    def finish(self):
        self.write('quit\n')

