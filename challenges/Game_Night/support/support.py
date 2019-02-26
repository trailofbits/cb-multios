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

import random

class Support(object):
    def __init__(self, magic_page):
        self.magic_page = magic_page

        self.hugman_round = 0
        self.sudoku_fitness = 0
        self.safari_party = [0] * 6

    def get_flag_byte(self, index):
        return self.magic_page[(index % 1024) * 4]

    def get_flag_byte_unsafe(self, index):
        return self.magic_page[(index % 4096)]

    def do_chess(self):
        piece = random.choice('prnbqk')
        board = [list(' ' * 8) for _ in xrange(8)]

        x = random.randint(0, 7)
        y = random.randint(0, 6 if piece == 'p' else 7)

        board[y][x] = piece

        def check_coords(x, y):
            return x >= 0 and x < 8 and y >= 0 and y < 8

        def move_pawn(x, y):
            ret = (0, 0)
            if check_coords(x, y + 2):
                ret = (x, y + 2)
            elif check_coords(x, y + 1):
                ret = (x, y + 1)
            return ret

        def move_rook(x, y):
            ret = (0, 0)
            if check_coords(x, y + 1):
                ret = (x, y + 1)
            elif check_coords(x - 1, y):
                ret = (x - 1, y)
            elif check_coords(x + 1, y):
                ret = (x + 1, y)
            elif check_coords(x, y - 1):
                ret = (x, y - 1)
            return ret

        def move_knight(x, y):
            ret = (0, 0)
            if check_coords(x + 1, y + 2):
                ret = (x + 1, y + 2)
            elif check_coords(x + 2, y + 1):
                ret = (x + 2, y + 1)
            elif check_coords(x + 2, y - 1):
                ret = (x + 2, y - 1)
            elif check_coords(x + 1, y - 2):
                ret = (x + 1, y - 2)
            elif check_coords(x - 1, y + 2):
                ret = (x - 1, y + 2)
            elif check_coords(x - 2, y + 1):
                ret = (x - 2, y + 1)
            elif check_coords(x - 2, y - 1):
                ret = (x - 2, y - 1)
            elif check_coords(x - 1, y - 2):
                ret = (x - 1, y - 2)
            return ret

        def move_bishop(x, y):
            ret = (0, 0)
            if check_coords(x - 1, y + 1):
                ret = (x - 1, y + 1)
            elif check_coords(x + 1, y + 1):
                ret = (x + 1, y + 1)
            elif check_coords(x - 1, y - 1):
                ret = (x - 1, y - 1)
            elif check_coords(x + 1, y - 1):
                ret = (x + 1, y - 1)
            return ret

        def move_queen(x, y):
            ret = (0, 0)
            if check_coords(x, y + 1):
                ret = (x, y + 1)
            elif check_coords(x - 1, y):
                ret = (x - 1, y)
            elif check_coords(x + 1, y):
                ret = (x + 1, y)
            elif check_coords(x, y - 1):
                ret = (x, y - 1)
            elif check_coords(x - 1, y + 1):
                ret = (x - 1, y + 1)
            elif check_coords(x + 1, y + 1):
                ret = (x + 1, y + 1)
            elif check_coords(x - 1, y - 1):
                ret = (x - 1, y - 1)
            elif check_coords(x + 1, y - 1):
                ret = (x + 1, y - 1)
            return ret

        def move_king(x, y):
            return move_queen(x, y)

        def coords_to_move(x0, y0, x1, y1):
            return '%s%s%s%s' % (chr(ord('a') + x0), y0 + 1,
                    chr(ord('a') + x1), y1 + 1)

        if piece == 'p':
            move = coords_to_move(x, y, *move_pawn(x, y))
        elif piece == 'r':
            move = coords_to_move(x, y, *move_rook(x, y))
        elif piece == 'n':
            move = coords_to_move(x, y, *move_knight(x, y))
        elif piece == 'b':
            move = coords_to_move(x, y, *move_bishop(x, y))
        elif piece == 'q':
            move = coords_to_move(x, y, *move_queen(x, y))
        elif piece == 'k':
            move = coords_to_move(x, y, *move_king(x, y))

        return (board, move)

    def do_sudoku(self):
        board = [
                [1,2,3,4,5,6,7,8,9],
                [4,5,6,7,8,9,1,2,3],
                [7,8,9,1,2,3,4,5,6],
                [2,3,4,5,6,7,8,9,1],
                [5,6,7,8,9,1,2,3,4],
                [8,9,1,2,3,4,5,6,7],
                [3,4,5,6,7,8,9,1,2],
                [6,7,8,9,1,2,3,4,5],
                [9,1,2,3,4,5,6,7,8]
                ]

        def transpose(board):
            return [list(x) for x in zip(*board)]

        def swap_rows(board):
            ret = list(board)
            group = random.randint(0, 2)
            exclude = random.randint(0, 2)
            src, dst = [3 * group + x for x in range(3) if x != exclude]
            ret.insert(dst, ret.pop(src))
            return ret

        iterations = random.randint(100, 1000)
        for i in xrange(iterations):
            board = random.choice([transpose, swap_rows])(board)

        self.safari_party[0] = 0
        self.safari_party[1] = 0

        return board

