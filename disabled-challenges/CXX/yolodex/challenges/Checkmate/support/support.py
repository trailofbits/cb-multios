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

class Piece(object):
    def __init__(self, white, row, col):
        self.white = white
        self.row = row
        self.col = col

    def abbrev(self):
        return ''

    def moves(self, board):
        return []

class Pawn(Piece):
    def __init__(self, white, row, col):
        super(Pawn, self).__init__(white, row, col)

    def abbrev(self):
        return 'P'

    def moves(self, board):
        ret = []
        # Move one
        r = self.row + (1 if self.white else -1)
        c = self.col
        if r in xrange(8) and c in xrange(8) and not board.get_piece(r, c):
            ret.append(Move(self, r, c))

        # Move two
        r = self.row + (2 if self.white else -2)
        c = self.col
        if ret and self.row == (1 if self.white else 6) and \
                r in xrange(8) and c in xrange(8) and not board.get_piece(r, c):
            ret.append(Move(self, r, c))

        # Capture
        r = self.row + (1 if self.white else -1)
        c = self.col - 1
        if r in xrange(8) and c in xrange(8) and board.get_piece(r, c) and \
                board.get_piece(r, c).white != self.white:
            ret.append(Move(self, r, c, capture=True))

        if r in xrange(8) and c in xrange(8) and board.ep_row == r and board.ep_col == c:
            ret.append(Move(self, r, c, capture=True))

        r = self.row + (1 if self.white else -1)
        c = self.col + 1
        if r in xrange(8) and c in xrange(8) and board.get_piece(r, c) and \
                board.get_piece(r, c).white != self.white:
            ret.append(Move(self, r, c, capture=True))

        if r in xrange(8) and c in xrange(8) and board.ep_row == r and board.ep_col == c:
            ret.append(Move(self, r, c, capture=True))

        return ret

class Rook(Piece):
    def __init__(self, white, row, col):
        super(Rook, self).__init__(white, row, col)

    def abbrev(self):
        return 'R'

    def moves(self, board):
        ret = []
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

        for d in directions:
            r = self.row + d[0]
            c = self.col + d[1]

            while r in xrange(8) and c in xrange(8) and not board.get_piece(r, c):
                ret.append(Move(self, r, c))
                r += d[0]
                c += d[1]

            p = board.get_piece(r, c)
            if p and p.white != self.white:
                ret.append(Move(self, r, c, capture=True))

        return ret

class Knight(Piece):
    def __init__(self, white, row, col):
        super(Knight, self).__init__(white, row, col)

    def abbrev(self):
        return 'N'

    def moves(self, board):
        ret = []
        moves = [(2, 1), (1, 2), (1, -2), (-2, 1), (-2, -1), (-1, -2), (-1, 2), (2, -1)]

        for m in moves:
            r = self.row + m[0]
            c = self.col + m[1]

            if r in xrange(8) and c in xrange(8):
                p = board.get_piece(r, c)
                if not p:
                    ret.append(Move(self, r, c))
                elif p.white != self.white:
                    ret.append(Move(self, r, c, capture=True))

        return ret

class Bishop(Piece):
    def __init__(self, white, row, col):
        super(Bishop, self).__init__(white, row, col)

    def abbrev(self):
        return 'B'

    def moves(self, board):
        ret = []
        directions = [(1, 1), (-1, 1), (1, -1), (-1, -1)]

        for d in directions:
            r = self.row + d[0]
            c = self.col + d[1]

            while r in xrange(8) and c in xrange(8) and not board.get_piece(r, c):
                ret.append(Move(self, r, c))
                r += d[0]
                c += d[1]

            p = board.get_piece(r, c)
            if p and p.white != self.white:
                ret.append(Move(self, r, c, capture=True))

        return ret

class Queen(Piece):
    def __init__(self, white, row, col):
        super(Queen, self).__init__(white, row, col)

    def abbrev(self):
        return 'Q'

    def moves(self, board):
        ret = Rook(self.white, self.row, self.col).moves(board) + \
                Bishop(self.white, self.row, self.col).moves(board)
        for m in ret:
            m.piece = self
        return ret

class King(Piece):
    def __init__(self, white, row, col):
        super(King, self).__init__(white, row, col)

    def abbrev(self):
        return 'K'

    def moves(self, board):
        ret = []
        moves = [(1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1), (0, -1), (1, -1), (1, 0)]

        for m in moves:
            r = self.row + m[0]
            c = self.col + m[1]

            if r in xrange(8) and c in xrange(8):
                p = board.get_piece(r, c)
                if not p or (p and p.white != self.white):
                    if not board.at_risk(self.white, r, c, True):
                        ret.append(Move(self, r, c, capture=(p is not None)))

        return ret

class Move(object):
    def __init__(self, piece, dst_row, dst_col, capture=False,
            castle_kingside=False, castle_queenside=False,
            check=False, checkmate=False, promotion=''):
        self.piece = piece
        self.dst_row = dst_row
        self.dst_col = dst_col
        self.capture = capture
        self.castle_kingside = castle_kingside
        self.castle_queenside = castle_queenside
        self.check = check
        self.checkmate = checkmate
        self.promotion = promotion

    def to_san(self):
        if self.castle_kingside:
            return 'O-O'
        elif self.castle_queenside:
            return 'O-O-O'

        s = self.piece.abbrev() if not isinstance(self.piece, Pawn) else ''
        s += 'abcdefgh'[self.piece.col]
        s += str(self.piece.row + 1)
        if self.capture:
            s += 'x'
        s += 'abcdefgh'[self.dst_col]
        s += str(self.dst_row + 1)
        if self.promotion:
            s += '=' + self.promotion
        if self.check:
            s += '+'
        elif self.checkmate:
            s += '#'

        return s

class Board(object):
    def __init__(self):
        self.board = [['' for x in xrange(8)] for y in xrange(8)]
        self.board[0] = list('rnbqkbnr')
        self.board[1] = list('pppppppp')
        self.board[6] = list('PPPPPPPP')
        self.board[7] = list('RNBQKBNR')

        self.castle_flag = [[True, True], [True, True]]
        self.ep_row = -1
        self.ep_col = -1
        self.stalemate_ctr = 0

    def to_string(self, white):
        ret = ''

        colors = [
            '\033[1;36;47m',
            '\033[1;35;47m',
            '\033[1;36;40m',
            '\033[1;35;40m'
        ]

        types = [
            '\xe2\x99\x99\x20',
            '\xe2\x99\x9f\x20',
            '\xe2\x99\x96\x20',
            '\xe2\x99\x9c\x20',
            '\xe2\x99\x98\x20',
            '\xe2\x99\x9e\x20',
            '\xe2\x99\x97\x20',
            '\xe2\x99\x9d\x20',
            '\xe2\x99\x95\x20',
            '\xe2\x99\x9b\x20',
            '\xe2\x99\x94\x20',
            '\xe2\x99\x9a\x20'
        ]

        reset = '\033[0m'

        for i in xrange(8):
            row = i if white else 8 - i - 1
            ret += str(8 - row) + ' '

            for j in xrange(8):
                col = j if white else 8 - j - 1
                p = self.get_piece(8 - row - 1, col)
                color = (((row % 2) + (col % 2)) % 2) << 1

                if p:
                    color |= 0 if p.white else 1
                    t = ('PRNBQK'.index(p.abbrev()) << 1) | (0 if p.white else 1)
                    ret += colors[color] + types[t] + reset
                else:
                    ret += colors[color] + '  ' + reset

            ret += '\n'

        ret += '  a b c d e f g h \n' if white else '  h g f e d c b a \n'
        return ret

    def set_piece(self, piece, row, col):
        if row not in xrange(8) or col not in xrange(8):
            return

        abbrev = piece.abbrev()
        self.board[row][col] = abbrev.lower() if piece.white else abbrev

    def clear_piece(self, row, col):
        if row not in xrange(8) or col not in xrange(8):
            return

        self.board[row][col] = ''

    def get_piece(self, row, col):
        if row not in xrange(8) or col not in xrange(8):
            return None

        abbrev = self.board[row][col]
        if not abbrev:
            return None

        types = [Pawn, Rook, Knight, Bishop, Queen, King]
        return types['prnbqk'.index(abbrev.lower())](abbrev.islower(), row, col)

    def make_move(self, move):
        dst_p = self.get_piece(move.dst_row, move.dst_col)
        if isinstance(move.piece, Pawn) or (dst_p and dst_p.white != move.piece.white):
            self.stalemate_ctr = 0
        else:
            self.stalemate_ctr += 1

        castle_row = 0 if move.piece.white else 7
        if move.castle_kingside:
            self.clear_piece(castle_row, 4)
            self.clear_piece(castle_row, 7)
            self.set_piece(King(move.piece.white, castle_row, 6), castle_row, 6)
            self.set_piece(Rook(move.piece.white, castle_row, 5), castle_row, 5)
            self.castle_flag[0 if move.piece.white else 1] = [False, False]
        elif move.castle_queenside:
            self.clear_piece(castle_row, 4)
            self.clear_piece(castle_row, 0)
            self.set_piece(King(move.piece.white, castle_row, 2), castle_row, 2)
            self.set_piece(Rook(move.piece.white, castle_row, 3), castle_row, 3)
            self.castle_flag[0 if move.piece.white else 1] = [False, False]
        else:
            p = self.get_piece(move.dst_row, move.dst_col)
            if isinstance(p, King) and p.white != move.piece.white:
                return 2

            self.clear_piece(move.piece.row, move.piece.col)
            self.clear_piece(move.dst_row, move.dst_col)
            if move.promotion:
                options = [Rook, Knight, Bishop, Queen]
                self.set_piece(options['RKBQ'.index(move.promotion)](move.piece.white, move.dst_row, move.dst_src),
                        move.dst_row, move.dst_src)
            else:
                self.set_piece(move.piece, move.dst_row, move.dst_col)
                
            if isinstance(move.piece, King):
                self.castle_flag[0 if move.piece.white else 1] = [False, False]
            elif isinstance(move.piece, Rook):
                if move.piece.row == castle_row and move.piece.col == 7:
                    self.castle_flag[0 if move.piece.white else 1][0] = False
                elif move.piece.row == castle_row and move.piece.col == 0:
                    self.castle_flag[0 if move.piece.white else 1][1] = False

            if isinstance(move.piece, Pawn) and move.dst_row == self.ep_row and move.dst_col == self.ep_col:
                if move.dst_row > move.piece.row:
                    self.clear_piece(move.dst_row - 1, move.dst_col)
                else:
                    self.clear_piece(move.dst_row + 1, move.dst_col)

            if isinstance(move.piece, Pawn) and abs(move.dst_row - move.piece.row) == 2:
                self.ep_row = (move.dst_row + move.piece.row) / 2
                self.ep_col = move.dst_col
            else:
                self.ep_row = -1
                self.ep_col = -1

        if self.stalemate(move.piece.white):
            return 3

        if self.checkmate(move.piece.white):
            return 2

        if self.check(move.piece.white):
            return 1

        return 0

    def all_moves(self, white):
        ret = []

        for row in xrange(8):
            for col in xrange(8):
                p = self.get_piece(row, col)
                if p and p.white == white:
                    ret += p.moves(self)

        return ret

    def at_risk(self, white, row, col, skip_kings=False):
        for r in xrange(8):
            for c in xrange(8):
                p = self.get_piece(r, c)
                if not p:
                    continue

                if skip_kings and isinstance(p, King):
                    continue

                if p.white != white:
                    if isinstance(p, Pawn) and p.col == col:
                        continue

                    moves = p.moves(self)
                    for m in moves:
                        if m.dst_row == row and m.dst_col == col:
                            return True

        return False

    def check(self, white):
        for r in xrange(8):
            for c in xrange(8):
                p = self.get_piece(r, c)
                if not p:
                    continue

                if isinstance(p, King) and p.white != white:
                    return self.at_risk(p.white, p.row, p.col, False)


    def checkmate(self, white):
        for r in xrange(8):
            for c in xrange(8):
                p = self.get_piece(r, c)
                if not p:
                    continue

                if isinstance(p, King) and p.white != white:
                    return self.at_risk(p.white, p.row, p.col, False) \
                            and not p.moves(self)

        return False

    def stalemate(self, white):
        if self.stalemate_ctr >= 100:
            return True

        for r in xrange(8):
            for c in xrange(8):
                p = self.get_piece(r, c)
                if not p:
                    continue

                if p.white != white and p.moves(self):
                    return False

        return True

    def can_castle(self, white, kingside):
        king_col = 4
        rook_col = 7 if kingside else 0
        row = 0 if white else 7

        if not self.castle_flag[0 if white else 1][0 if kingside else 1]:
            return False

        king = self.get_piece(row, king_col)
        if not king or not isinstance(king, King):
            return False

        rook = self.get_piece(row, rook_col)
        if not rook or not isinstance(rook, Rook):
            return False

        start_col = min(king_col, rook_col) + (1 if kingside else 2)
        end_col = max(king_col, rook_col)
        for i in xrange(start_col, end_col):
            if self.get_piece(row, i) or self.at_risk(white, row, i, False):
                return False

        return True

    def get_empty_squares(self):
        ret = []
        for row in xrange(8):
            for col in xrange(8):
                if not self.board[row][col]:
                    ret.append((row, col))

        return ret

class Support(object):
    def __init__(self, magic_page):
        self.reset()
        self.magic_page = magic_page

    def calculate_csum(self, result):
        ret = 0
        for i in xrange(1024):
            ret = ret ^ ord(self.magic_page[i * 4])
        return (ret ^ result) & 0xffffffff

    def board_string(self):
        return self.board.to_string(self.white)

    def prompt_string(self):
        return '%s>\033[0m ' % ('\033[1;36m' if self.white else '\033[0;35m')

    def get_valid_move(self):
        if random.random() < 0.05 and self.board.can_castle(self.white, True):
            return Move(King(self.white, 0, 0), 0, 0, castle_kingside=True)
        elif random.random() < 0.05 and self.board.can_castle(self.white, False):
            return Move(King(self.white, 0, 0), 0, 0, castle_queenside=True)
        else:
            return random.choice(self.board.all_moves(self.white))

    def get_invalid_move(self):
        square = random.choice(self.board.get_empty_squares())
        piece = random.choice([Pawn, Rook, Knight, Bishop, Queen, King])(self.white, square[0], square[1])
        moves = piece.moves(self.board)
        if moves and random.random() < 0.5:
            move = random.choice(moves)
        else:
            if random.random() < 0.1 and not self.board.can_castle(self.white, True):
                move = Move(piece, random.randint(0, 7), random.randint(0, 7),
                        bool(random.getrandbits(1)), True, False,
                        bool(random.getrandbits(1)), bool(random.getrandbits(1)),
                        random.choice('RKBQ'))
            elif random.random() < 0.1 and not self.board.can_castle(self.white, False):
                move = Move(piece, random.randint(0, 7), random.randint(0, 7),
                        bool(random.getrandbits(1)), False, True,
                        bool(random.getrandbits(1)), bool(random.getrandbits(1)),
                        random.choice('RKBQ'))
            else:
                move = Move(piece, random.randint(0, 7), random.randint(0, 7),
                        bool(random.getrandbits(1)), False, False,
                        bool(random.getrandbits(1)), bool(random.getrandbits(1)),
                        random.choice('RKBQ'))

        return move

    def apply_move(self, move):
        return self.board.make_move(move)

    def next_player(self):
        self.white = not self.white

    def reset(self):
        self.board = Board()
        self.white = True

