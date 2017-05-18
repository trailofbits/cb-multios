#!/usr/bin/env python

from generator.actions import Actions
import random
import string

BOARD_SIZE = 32
ZERO_CHAR = '.'
ONE_CHAR = '1'
END_CHAR = chr(0xFF)
INIT_VALUE_PY = [ONE_CHAR for _ in xrange(BOARD_SIZE)]
ROW_1 = BOARD_SIZE - 1
ROW_2 = BOARD_SIZE - 2 


class BitBreaker(Actions):

    def start(self):
        self.board = [ [ZERO_CHAR for _ in xrange(BOARD_SIZE)] for __ in xrange(BOARD_SIZE) ]
        self.board[ROW_1] = INIT_VALUE_PY
        self.board[ROW_2] = INIT_VALUE_PY 

    def isWinner(self):
        for row in self.board :
            if not row == "".join([ZERO_CHAR for _ in xrange(BOARD_SIZE)]) :
                return False
        return True

    def shift_right(self, row):
        self.board[row] = [ self.board[row][-1] ] + self.board[row][0:-1]

    def shift_down(self, col):
        botrow = self.board[-1] 
        for row in reversed(xrange(1, BOARD_SIZE)) :
            self.board[row] = self.board[row][0:col] + self.board[row-1][col:col+1] + self.board[row][col+1:]
        self.board[0] = self.board[0][0:col] + botrow[col:col+1] + self.board[0][col+1:]

    def toCmd(self, direction, num) :
        if direction == 'R' :
            return (0x20 | num) & 0xFF 
        else :
            return ((~0x20) & num) & 0xFF

    def remove_bits(self) :
        if (self.board[-1][0] == ONE_CHAR and self.board[-1][1] == ONE_CHAR and
           self.board[-2][0] == ONE_CHAR and self.board[-2][1] == ONE_CHAR) :
            self.board[-1] = [ZERO_CHAR, ZERO_CHAR] + self.board[-1][2 :]       
            self.board[-2] = [ZERO_CHAR, ZERO_CHAR] + self.board[-2][2 :]       
 
    def go(self):
        d = random.choice("RD")
        n = random.randint(0,BOARD_SIZE - 1) 

        bak = self.board

        if d == "R" :
            self.shift_right(n)  
        else :
            self.shift_down(n)  

        self.remove_bits()

        if self.isWinner() :
            #if we won somehow then just skip this one
            print "WARNING: We won!!!"
            self.board = bak
        else :
            self.write([chr(self.toCmd(d,n))])

    def toStr(self) :
        ret = ""
        for row in self.board :
            ret += "".join(row) + "\n"

        return (ret)

    def end(self):
        self.write(END_CHAR)
        s = self.toStr()
        self.read(length=len(s), expect=s)



