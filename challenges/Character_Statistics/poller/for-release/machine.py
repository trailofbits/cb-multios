#!/usr/bin/env python

from generator.actions import Actions
#import actions
import copy
import random
import string
        
LOWs =  "abcdefghijklmnopqrstuvwxyz"
UPs =   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
NUMs =  "0123456789"
SPECIALs = "`~!@#$%^&*()-_=+]}[{\\|'\";:/?.>,<"
SPACEs = " \t"
OTHERs = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x0A\x0B\x0C\x0D\x0E\x0F"  \
         "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F" \
         "\x7f"

def printMap(_map):
    pass
  
class CharStats(Actions):

    def addAndPrint(self, c):
        self.buf += c
        if (len(self.buf) >= self.maxlen) :
            self.write(self.buf)
            self.read(length = len(self.buf), expect=self.buf)
            self.buf = ""    

    def start(self):
        self.ups = 0
        self.lows = 0
        self.specials = 0
        self.nums = 0
        self.spaces = 0
        self.others = 0
        self.buf = ""
        self.maxlen = random.randint(100,1000)

    def chooseChar(self):
        pass; #nothing to do here

    def upletter(self):
        self.ups += 1
        self.ups %= 256 
        c = random.choice(UPs)
        self.addAndPrint(c)

    def lowletter(self):
        self.lows += 1
        self.lows %= 256 
        c = random.choice(LOWs)
        self.addAndPrint(c)

    def special(self):
        self.specials += 1
        self.specials %= 256 
        c = random.choice(SPECIALs)
        self.addAndPrint(c)

    def number(self):
        self.nums += 1
        self.nums %= 256 
        c = random.choice(NUMs)
        self.addAndPrint(c)

    def other(self):
        self.others += 1
        self.others %= 256 
        c = random.choice(OTHERs)
        self.addAndPrint(c)

    def space(self):
        if (self.spaces < 255) :
            self.spaces += 1
            c = random.choice(SPACEs)
            self.addAndPrint(c)

    def end(self):

        if (len(self.buf) > 0) :
            self.write(self.buf)
            self.read(length = len(self.buf), expect=self.buf)
        #do a read to make sure the final statistics are the same
        self.read(delim='\n', expect="numbers  = %010u" % self.nums)
        self.read(delim='\n', expect="uppers   = %010u" % self.ups)
        self.read(delim='\n', expect="lowers   = %010u" % self.lows)
        self.read(delim='\n', expect="spaces   = %010u" % self.spaces)
        self.read(delim='\n', expect="special  = %010u" % self.specials)
        self.read(delim='\n', expect="other    = %010u" % self.others)


