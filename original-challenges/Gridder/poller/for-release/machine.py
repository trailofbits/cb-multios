#!/usr/bin/env python

from generator.actions import Actions
import random
import struct
import ctypes
import string
import math
import copy

UNUSED = 0
USED = 1
SET_SUBSIZE = 3
SET_SIZE = SET_SUBSIZE * SET_SUBSIZE
NUM_CELLS = SET_SIZE * SET_SIZE
DIFFICULTY = 25
POOL_SIZE = 4096

pack_int = lambda x: struct.pack("<I", x)
pack_bytes = lambda x: struct.pack("{0}B".format(len(x)), *x)
byte_str = lambda x: "\\x%02x" % int(x)
ROW = lambda x: x / SET_SIZE
COL = lambda x: x % SET_SIZE
SET = lambda x: (x % SET_SIZE) + 1

DEFAULT_DIFFICULTY = 40
INITIAL_HARDEST_DIFFICULTY = 40
EASIEST_DIFFICULTY = 50
DEFAULT_BOARD_SIZE = 81

class CMD_IDS():
    EXIT = 0
    NEW_GRIDDER = 1
    ASK_DIFFICULTY = 2
    GIVE_UP = 3
    SOLVE_GRIDDER = 4
    CHANGE_DIFFICULTY = 5
    CHANGE_BOARD_SIZE = 6


class MSGS():
    EXITING = 100
    SENDING_GRIDDER = 101
    RESPOND_DIFFICULTY = 102
    SENDING_SOLUTION = 103
    CORRECT_SOLUTION = 104
    DIFFICULTY_CHANGED = 105
    NOT_YET_IMPLEMENTED = 106


class ERRORS():
    NO_ERRORS = 200
    UNINITIALIZED_GRID = 201
    NOT_ENOUGH_DATA = 202
    BAD_SOLUTION = 203
    BAD_DIFFICULTY = 204
    NOT_UNLOCKED = 205
    BAD_BOARD_SIZE = 206
    BAD_CMD_ID = 207


class NumGenerator(object):
    def __init__(self, magic_page):
        self.magic_page = magic_page
        self.rand_idx = 0
        self.nums_available = NUM_CELLS
        self.cache = []
        self.numbers = [UNUSED] * NUM_CELLS

    def get_random_num(self):
        if not self.nums_available:
            return 0

        rand = struct.unpack('<B', self.magic_page[self.rand_idx])[0] % NUM_CELLS
        self.rand_idx = (self.rand_idx + 1) % POOL_SIZE

        for i in xrange(NUM_CELLS):
            idx = (rand + i) % NUM_CELLS
            if self.numbers[idx] == UNUSED:
                self.numbers[idx] = USED
                self.nums_available -= 1
                return idx + 1

        return 0

    def reinstate_number(self, number):
        number -= 1
        if self.numbers[number] == USED:
            self.numbers[number] = UNUSED
            self.nums_available += 1
            return True
        return False

    def cache_number(self, number):
        self.cache.append(number)

    def flush_cache(self, flush_count):
        flush_count = flush_count if flush_count <= len(self.cache) else len(self.cache)
        for x in xrange(flush_count):
            self.reinstate_number(self.cache.pop())

    def reset(self):
        self.nums_available = NUM_CELLS
        self.cache = []
        self.numbers = [UNUSED] * NUM_CELLS

    def available_nums(self):
        return self.nums_available


class Gridder(object):
    def __init__(self, board=None):
        if board:
            self.board = [ list(subarr) for subarr in board ]
        else:
            self.board = [ [UNUSED] * SET_SIZE for x in xrange(SET_SIZE) ]

    def debug(self):
        for r in xrange(SET_SIZE):
            out = ''
            if r and r % SET_SUBSIZE == 0:
                print("------+-------+------")
            for c in xrange(SET_SIZE):
                if c and c % SET_SUBSIZE == 0:
                    out += "| "
                out += "{0} ".format(self.board[r][c])
            print out
        print "=====================\n"


    def read_board(self, read_uint):
        for r in xrange(SET_SIZE):
            for c in xrange(SET_SIZE):
                read_uint(self.board[r][c])


    def write_board(self, write_uint):
        for r in xrange(SET_SIZE):
            for c in xrange(SET_SIZE):
                write_uint(self.board[r][c])

    def reset_board(self):
        self.board = [ [UNUSED] * SET_SIZE for x in xrange(SET_SIZE) ]

    def generate_new_gridder(self, cell_idx, pngen):
        if cell_idx == 0:
            self.reset_board()
            pngen.reset()

        if cell_idx == NUM_CELLS:
            return True

        num_cached = 0
        valid_nums = [UNUSED] * SET_SIZE

        while pngen.available_nums():
            row = ROW(cell_idx)
            col = COL(cell_idx)
            next_num = pngen.get_random_num()
            if not next_num:
                continue

            if valid_nums[SET(next_num) - 1] != UNUSED or not self.valid_add_num(SET(next_num), row, col):
                valid_nums[SET(next_num) - 1] = USED
                pngen.cache_number(next_num)
                num_cached += 1
            else:
                #self.debug()
                pngen.flush_cache(num_cached)
                valid_nums[SET(next_num) - 1] = USED
                pngen.cache_number(next_num)
                num_cached = 1

                if self.generate_new_gridder(cell_idx + 1, pngen):
                    return True
                self.board[row][col] = UNUSED

        pngen.flush_cache(num_cached)
        return False

    def make_gridder_solveable(self, difficulty, pngen):
        solution = None
        pngen.reset()

        difficulty = DIFFICULTY if difficulty < DIFFICULTY else difficulty
        while difficulty < pngen.available_nums():
            if solution:
                solution = None

            cell_idx  = pngen.get_random_num()
            if not cell_idx:
                return

            cell_idx -= 1
            row = ROW(cell_idx)
            col = COL(cell_idx)
            prev_val = self.board[row][col]
            self.board[row][col] = UNUSED

            orig = Gridder(self.board)
            solution = orig.find_solution(0)
            if solution:
                exit = []
                orig = Gridder(self.board)
                if not orig.has_unique_solution(0, solution, exit):
                    self.board[row][col] = prev_val
            else:
                self.board[row][col] = prev_val

    def find_solution(self, cell_idx):
        if cell_idx == NUM_CELLS:
            return Gridder(self.board)

        row = ROW(cell_idx);
        col = COL(cell_idx);
        if self.board[row][col] != UNUSED:
            return self.find_solution(cell_idx+1);

        for i in xrange(1, SET_SIZE + 1):
            self.board[row][col] = i;
            if self.valid_cell(row, col):
                solution = self.find_solution(cell_idx + 1)
                if solution:
                    return solution;

        self.board[row][col] = UNUSED;
        return None

    def has_unique_solution(self, cell_idx, s1, exit):
        if cell_idx == NUM_CELLS:
            exit.append(1)
            for r in xrange(SET_SIZE):
                for c in xrange(SET_SIZE):
                    if self.board[r][c] != s1.board[r][c]:
                        return False
            return True

        row = ROW(cell_idx)
        col = COL(cell_idx)
        if self.board[row][col]:
            return self.has_unique_solution(cell_idx+1, s1, exit)

        for i in reversed(xrange(1, SET_SIZE + 1)):
            if len(exit):
                return False

            self.board[row][col] = i
            if self.valid_cell(row,col) and self.has_unique_solution(cell_idx+1, s1, exit):
                return True

        self.board[row][col] = UNUSED
        return False

    def valid_add_num(self, val, row, col):
       if self.board[row][col] != UNUSED:
           return False

       self.board[row][col] = val
       if self.valid_cell(row, col):
           return True

       self.board[row][col] = UNUSED
       return False

    def valid_cell(self, row, col):
        cell = self.board[row][col];
        for i in xrange(SET_SIZE):
            if (row != i and cell == self.board[i][col]) or (col != i and cell == self.board[row][i]):
                return False

        r = (row/SET_SUBSIZE) * SET_SUBSIZE
        while r < ((row/SET_SUBSIZE) + 1) * SET_SUBSIZE:
            c = (col/SET_SUBSIZE) * SET_SUBSIZE
            while c < ((col/SET_SUBSIZE) + 1) * SET_SUBSIZE:
                if (row == r and col == c):
                    c += 1
                    continue
                if (cell == self.board[r][c]):
                    return False
                c += 1
            r += 1
        return True


class GridderGame(Actions):
    def _read(self, data):
        self.read(length=len(data), expect=data)

    def _write_uint(self, x):
        self.write(pack_int(x))

    def _read_uint(self, data):
        data = pack_int(data)
        self.read(length=len(data), expect=data)

    def _read_board_data(self):
        self._read_uint(NUM_CELLS * 4)
        self.grid.read_board(self._read_uint)

    def _write_board_data(self):
        self._write_uint(NUM_CELLS)
        self.grid.write_board(self._write_uint)

    def start(self):
        #self.delay(100)
        self.grid = Gridder()
        self.ngen = NumGenerator(self.magic_page)
        self.difficulty = DEFAULT_DIFFICULTY
        self.initialized = False

    def player_selection(self):
        pass

    def new_gridder(self):
        self._write_uint(CMD_IDS.NEW_GRIDDER)
        self._read_uint(MSGS.SENDING_GRIDDER)
        self.grid.generate_new_gridder(0, self.ngen)
        self.grid.make_gridder_solveable(self.difficulty, self.ngen)
        self._read_board_data()
        self.initialized = True

    def ask_difficulty_range(self):
        self._write_uint(CMD_IDS.ASK_DIFFICULTY)
        self._read_uint(MSGS.RESPOND_DIFFICULTY)
        self._read_uint(INITIAL_HARDEST_DIFFICULTY)
        self._read_uint(EASIEST_DIFFICULTY)

    def give_up(self):
        self._write_uint(CMD_IDS.GIVE_UP)
        if not self.initialized:
            self._read_uint(ERRORS.UNINITIALIZED_GRID)
        else:
            self.grid.find_solution(0)
            self._read_uint(MSGS.SENDING_SOLUTION)
            self._read_board_data()
            self.grid.reset_board()

    def solve_gridder(self):
        self._write_uint(CMD_IDS.SOLVE_GRIDDER)
        if not self.initialized:
            self._read_uint(ERRORS.UNINITIALIZED_GRID)
        else:
            if random.randint(1,4) != 1:
                self.grid.find_solution(0)
                self._write_board_data()
                self._read_uint(MSGS.CORRECT_SOLUTION)
                self.initialized = False
            else:
                temp_grid = self.grid
                self.grid = Gridder(self.grid.board)
                self._write_board_data()
                self.grid = temp_grid
                self._read_uint(ERRORS.BAD_SOLUTION)

    def change_difficulty(self):
        self._write_uint(CMD_IDS.CHANGE_DIFFICULTY)
        self.difficulty = random.randint(INITIAL_HARDEST_DIFFICULTY, EASIEST_DIFFICULTY)
        self._write_uint(self.difficulty)
        self._read_uint(MSGS.DIFFICULTY_CHANGED)

    def change_board_size(self):
        self._write_uint(CMD_IDS.CHANGE_BOARD_SIZE)
        self._write_uint(random.randint(81, 256))
        self._read_uint(MSGS.NOT_YET_IMPLEMENTED)


    def exit(self):
        self._write_uint(CMD_IDS.EXIT)
        self._read_uint(MSGS.EXITING)
