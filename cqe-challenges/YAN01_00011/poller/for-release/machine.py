#!/usr/bin/env python

from generator.actions import Actions
import random
import string
import re

VALID_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
ENTER_NUM_MSG = "Please Enter a 2 Digit Number\n"
WORD_MSG = "Word: "
LOSE_MSG = "You Lose\n"
WIN_MSG = "You Win!\n"
NEXT_WORD_MSG = "Next Word: "
FINAL_RND_MSG = "Final Round. Chose another 2 digit number\n"
NUM_ROUNDS = 10

def RANDOM(register) :
  register = ((((register >> 31)
             ^ (register >> 6)
             ^ (register >> 4)
             ^ (register >> 2)
             ^ (register >> 1)
             ^ register)
             & 0x00000001)
             << 31) | (register >> 1)

  return (register)

gRandRegister = 0xDA2bAC9C

def rand() :
  global gRandRegister
  gRandRegister = RANDOM(gRandRegister)
  return (gRandRegister)

def srand(seed) :
  global gRandRegister
  gRandRegister = seed

def strToSeed(s) :
  temp = [ ord(_) for _ in s ]
  for i in xrange(len(s), 4) :
    temp.append(0)

  #do a byte swap because of little endian

  return ( (temp[3] << 24)
           | (temp[2] << 16)
           | (temp[1] << 8)
           | temp[0]
         )

class WordCompletion(Actions):

    def rotN(self, s, n) :
        ret = ""
        for c in s :
            if c in VALID_CHARS :
                ret += VALID_CHARS[(VALID_CHARS.find(c) + n) % len(VALID_CHARS)]
            else :
                ret += c
        return (ret)

    def start(self):
        self.words = []

        self.seed = random.randint(0,99)
        self.seedStr = "%02u\n" % self.seed
        srand(strToSeed(self.seedStr))

        #seems a bit overkill to read the file again and again no?
        for l in open("src/words.h") :
            mat = re.match('"(.+)",', l)
            if mat :
              self.words.append(self.rotN(mat.group(1), self.seed + 1))

        self.wincount = 0
 
        self.read(length=len(ENTER_NUM_MSG), expect=ENTER_NUM_MSG)
        self.write(self.seedStr)
        self.gameover = False

    def scramble(self) :
        r = (rand() % 3) + 2
        s = ""
        i = 0
     
        for c in self.curWord :
            if c in VALID_CHARS and (i % r) == 0 :
                s += '_'
            else :
                s += c
            i += 1

        return s

    def play(self):
        if self.gameover :
            return

        prompt = ""

        if self.wincount == 0 :
            prompt += WORD_MSG
        elif self.wincount < 10 :
            prompt += NEXT_WORD_MSG
        elif self.wincount == NUM_ROUNDS :
            #this is the final round
            prompt += FINAL_RND_MSG
            self.read(length=len(prompt), expect=prompt)

            finalchoice = random.randint(0,len(self.words)-1)
            temp = "%02u\n" % finalchoice
            self.write(temp)

            self.curWord = self.words[finalchoice] 
            s = self.scramble()
            s += '\n'
            self.read(length=len(s), expect=s)
            return
  
        else :
            return    

        self.curWord = self.words[rand() % len(self.words)]

        s = self.scramble() 
        prompt += s
        prompt += '\n'
        self.read(length=len(prompt), expect=prompt)            

    def win(self):
        if self.gameover :
            return

        self.write(self.curWord + "\n")
        self.wincount += 1

        if self.wincount >= (NUM_ROUNDS + 1) :
            self.gameover = True

    def lose(self):
        if self.gameover :
            return

        i = random.randint(0, len(self.curWord))
        s = self.curWord[0:i] + self.rotN(self.curWord[i:i+1], 1) + self.curWord[i+1:]
        if s == self.curWord : #if somehow we found a non-shiftable character using rand
            s = "A" + s
        s += '\n'

        self.write(s)
        self.read(length=len(LOSE_MSG), expect=LOSE_MSG)

        self.gameover = True

    def end(self):
        pass



