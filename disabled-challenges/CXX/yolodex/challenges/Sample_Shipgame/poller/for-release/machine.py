#!/usr/bin/env python

from generator.actions import Actions
#import actions
import copy
import random
import string
        
unknownCommands = "abcdefghijklmnopqrstuvwxyzABCDFGIJKLOQRUVWXYZ"
locchoices = [[j + i for i in "ABCDEFGHIJ"] for j in "0123456789"]

def printMap(_map):
    pass
  
class SampleShipGame(Actions):
#class SampleShipGame(actions.Actions):

    def start(self):
        #setup the local variables and state
        self.curplayer = '1' 
        self.p1map = [['.' for i in xrange(10)] for j in xrange(10)] 
        self.p2map = [['.' for i in xrange(10)] for j in xrange(10)] 
        self.p1shipchoices = random.sample([2,3,4,5], 4)
        self.p1shiplife = [0,0,0,0]
        self.p1curship = 0
        self.p2shipchoices = random.sample([2,3,4,5], 4)
        self.p2shiplife = [0,0,0,0]
        self.p2curship = 0
        self.gameEnded = False

    def setup_input(self):
        self.read(length=10, expect="Player" + self.curplayer + ":$ ")

    def place(self):
        row = random.randint(0,9)
        col = random.randint(0,9)
        direction = random.choice('RD')
        m = self.p1map
        c = self.p1shipchoices
        n = self.p1curship
        l = self.p1shiplife
        e = False

        if (self.curplayer == '2'):
            m = self.p2map
            c = self.p2shipchoices
            n = self.p2curship
            l = self.p2shiplife

        self.write("P"+locchoices[row][col]+direction+str(c[n])+"\n")
        if (self.gameEnded) :
            self.read(delim='\n', expect="Game ended already. Try a new one\n")
            return


        for i in xrange(c[n]):
            if (direction == 'R') :
                if ((col + i) > 9) or (m[row][col+i] != '.') : 
                    e = True 
                    break;
            else :
                if ((row + i) > 9) or (m[row+i][col] != '.') : 
                    e = True 
                    break;
                
        #see if all ships have already been placed
        if (n > 3) : 
            e = True

        if e :
            #if there is an error we should get the bad command msg
            self.read(delim='\n', expect="Bad Command - Try again\n")
        else :
            #if there isn't an error then we need to update the map
            for i in xrange(c[n]):
                if (direction == 'R') :
                    m[row][col+i] = str(c[n])
                else :
                    m[row+i][col] = str(c[n])

            #set the life
            l[c[n]-2] = c[n]
            #now we can update the current player and count 
            if (self.curplayer == '1') :
                self.curplayer = '2'
                self.p1curship += 1
                self.p1curship %= len(self.p1shipchoices)
            else :
                self.curplayer = '1'
                self.p2curship += 1
                self.p2curship %= len(self.p2shipchoices)
        
    def setup_new(self):
        self.write("N\n")

    def setup_map(self):
        m = self.p1map
        if (self.curplayer == '2') :
            m = self.p2map

        self.write("M\n")
        if (self.gameEnded) :
            self.read(delim='\n', expect="Game ended already. Try a new one\n")
            return

        self.read(delim='\n', expect="\tABCDEFGHIJ\n")

        for i in xrange(10) :
            self.read(delim='\n', expect="   {:d}:\t".format(i) + "".join(m[i]) + "\n")

    def setup_help(self):
        self.write("H\n")
        self.read(delim='\n', expect="Sorry, I am not very helpful\n")

    def setup_unknown(self):
        self.write(random.choice(unknownCommands) + "\n")
        self.read(delim='\n', expect="Bad Command - Try again\n")

    def setup_exit(self):
        self.write("E\n")
        self.read(delim='\n', expect="You are stuck...\n")

    def begin(self):
        self.write("S\n")
        if (self.gameEnded) :
            self.read(delim='\n', expect="Game ended already. Try a new one\n")
            return

    def game_input(self):
        self.read(length=10, expect="Player" + self.curplayer + ":$ ")

    def target(self):
        row = random.randint(0,9)
        col = random.randint(0,9)
        m = self.p2map
        c = self.p2shipchoices
        l = self.p2shiplife

        if (self.curplayer == '2'):
            m = self.p1map
            c = self.p1shipchoices
            l = self.p1shiplife

        self.write("T"+locchoices[row][col] + "\n")
        if (self.gameEnded) :
            self.read(delim='\n', expect="Game ended already. Try a new one\n")
            return


        #we don't have to check for errors here since
        # the rows and cols are always good - can change this though  
               
        if (m[row][col] == '2') :
            m[row][col] = 'X'
            l[0] -= 1
            self.read(delim='\n', expect="OUCH!!\n")
            if (l[0] == 0) :
              self.read(delim='\n', expect="You have sunk my SHIP 2\n")

        elif (m[row][col] == '3') :
            m[row][col] = 'X'
            l[1] -= 1
            self.read(delim='\n', expect="OUCH!!\n")
            if (l[1] == 0) :
              self.read(delim='\n', expect="You have sunk my SHIP 3\n")

        elif (m[row][col] == '4') :
            m[row][col] = 'X'
            l[2] -= 1
            self.read(delim='\n', expect="OUCH!!\n")
            if (l[2] == 0) :
              self.read(delim='\n', expect="You have sunk my SHIP 4\n")

        elif (m[row][col] == '5') :
            m[row][col] = 'X'
            l[3] -= 1
            self.read(delim='\n', expect="OUCH!!\n")
            if (l[3] == 0) :
              self.read(delim='\n', expect="You have sunk my SHIP 5\n")

        else :
            self.read(delim='\n', expect="You missed\n")
         
        if sum(l) == 0 : #this only happens when 2, 3, 4, 5 are all 0
            self.read(delim='\n', expect="You win. Congrats\n")
            self.gameEnded = True

        if (self.curplayer == '1') :
            self.curplayer = '2'
            self.p1curship += 1
            self.p1curship %= len(self.p1shipchoices)
        else :
            self.curplayer = '1'
            self.p2curship += 1
            self.p2curship %= len(self.p2shipchoices)

    #these have the same behavior as the setup ones
    def game_new(self):
        self.setup_new()

    def game_map(self):
        self.setup_map()

    def game_help(self):
        self.setup_help()

    def game_unknown(self):
        self.setup_unknown()

    def game_exit(self):
        self.setup_exit()

    def end(self):
        pass #nothing to do here just end the stream


