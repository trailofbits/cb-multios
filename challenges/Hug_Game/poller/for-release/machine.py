#!/usr/bin/env python

from generator.actions import Actions
import random
import string
import struct
import linecache


class Hugger(Actions):
    name = ""
    lfsrstate = 0

    def genName(self):
        return ''.join(random.choice(string.ascii_uppercase + string.ascii_lowercase) for _ in range(10))

    def doLFSR(self):
        self.lfsrstate &= 0xffffffff
        bits = ((self.lfsrstate >> 0) ^ (self.lfsrstate >> 2) ^ (self.lfsrstate >> 3) ^ (self.lfsrstate >> 5)) & 1
        self.lfsrstate = ((self.lfsrstate >> 1) & 0xffffffff) | ((bits << 31) & 0xffffffff)
        return self.lfsrstate

    def start(self):
        #self.delay(100)
        self.hugs = 1000
        self.goaway = 0
        pass

    def handleWager(self):
        self.read(delim="? ", expect="How much would you like to wager")
        if(self.hugs <= 1):
            bet = 1
        else:
            bet = random.randint(1, self.hugs)
        self.write("%d\n" % bet)
        if (bet > 1000):
            self.read(delim="\n", expect="HIGH ROLLER COMING THROUGH!")
        return bet

    def banner(self):
        self.read(delim="\n", expect="Welcome to the hug gambling server.")

    def getName(self):
        self.read(delim="\n", expect="What is your name?")
        self.name = self.genName()
        self.write(self.name+ "\n")
        self.lfsrstate = struct.unpack("I", self.name[0:4])[0]
        self.read(delim=". ", expect="Hi " + self.name)

    def cardName(self, cardNum):
        return["two","three","four","five","six","seven","eight","nine","ten","jack","queen","king","ace"][cardNum]

    def cardSuite(self, cardNum):
        return["spades","hearts","clubs","diamonds"][cardNum]

    def resolveWar(self, wager):
        bet = wager * 2
        self.doLFSR()
        self.doLFSR()
        self.doLFSR()
        playerCard = self.doLFSR()
        self.doLFSR()
        self.doLFSR()
        self.doLFSR()
        dealerCard = self.doLFSR()
        if(dealerCard % 13 > playerCard % 13):
            self.read(delim="\n", expect="Dealer's %s of %s beats player's %s of %s" % (self.cardName(dealerCard % 13), self.cardSuite(dealerCard % 4), self.cardName(playerCard % 13), self.cardSuite(playerCard % 4)))
            self.read(delim="\n", expect="YOU LOSE!")
            self.read(delim="\n\n", expect="Debiting %d from your hug balance." % bet)
            self.hugs-=bet
        elif(dealerCard % 13 < playerCard % 13):
            self.read(delim="\n", expect="Player's %s of %s beats dealer's %s of %s" % (self.cardName(playerCard % 13), self.cardSuite(playerCard % 4), self.cardName(dealerCard % 13), self.cardSuite(dealerCard % 4)))
            self.read(delim="\n", expect="YOU WIN!")
            self.read(delim="\n\n", expect="Adding %d to your hug balance." % bet)
            self.hugs+=bet
        else:
            self.read(delim="\n", expect="Both players drew a %s" % (self.cardName(playerCard % 13)))
            self.read(delim="\n", expect="THIS MEANS WAR")
            self.resolveWar(bet)

    def war(self):
        if(self.hugs <= 0):
            return
        self.write("4\n")
        bet = self.handleWager();
        playerCard = self.doLFSR()
        dealerCard = self.doLFSR()
        if(dealerCard % 13 > playerCard % 13):
            self.read(delim="\n", expect="Dealer's %s of %s beats player's %s of %s" % (self.cardName(dealerCard % 13), self.cardSuite(dealerCard % 4), self.cardName(playerCard % 13), self.cardSuite(playerCard % 4)))
            self.read(delim="\n", expect="YOU LOSE!")
            self.read(delim="\n\n", expect="Debiting %d from your hug balance." % bet)
            self.hugs-=bet
        elif(dealerCard % 13 < playerCard % 13):
            self.read(delim="\n", expect="Player's %s of %s beats dealer's %s of %s" % (self.cardName(playerCard % 13), self.cardSuite(playerCard % 4), self.cardName(dealerCard % 13), self.cardSuite(dealerCard % 4)))
            self.read(delim="\n", expect="YOU WIN!")
            self.read(delim="\n\n", expect="Adding %d to your hug balance." % bet)
            self.hugs+=bet
        else:
            self.read(delim="\n", expect="Both players drew a %s" % (self.cardName(playerCard % 13)))
            self.read(delim="\n", expect="THIS MEANS WAR")
            self.resolveWar(bet)

    def chooseGame(self):
        if(self.hugs <= 0 and self.goaway == 0):
            self.read(delim="\n", expect="You're all out of hugs :(. Thanks for playing.")
            self.goaway = 1
        if(self.goaway == 1):
            return
        if(self.hugs > 1000000):
            self.hugs = 1000000
        self.read(delim="\n", expect="You have %d hugs. Shall we play a game?" % self.hugs)
        self.read(delim="\n", expect="1. Coin Flip")
        self.read(delim="\n", expect="2. Hangman")
        self.read(delim="\n", expect="3. Dice game")
        self.read(delim="\n", expect="4. War")
        self.read(delim="\n", expect="q. Quit")

    def coinflip(self):
        if(self.hugs <= 0):
            return
        self.write("1\n")
        wagered = self.handleWager()
        choice = random.choice(['h', 't'])
        self.read(delim="\n", expect="Flipping a coin. Do you think it's going to be (h)eads or (t)ails?")
        self.write(choice + "\n")
        result = self.doLFSR() % 2
        if(choice == 'h' and result == 1):
            self.read(delim="\n", expect="YOU WIN!")
            self.read(delim="\n\n", expect="Adding %d to your hug balance." % wagered)
            self.hugs+=wagered
        elif(choice == 't' and result == 0):
            self.read(delim="\n", expect="YOU WIN!")
            self.read(delim="\n\n", expect="Adding %d to your hug balance." % wagered)
            self.hugs+=wagered            
        else:
            self.read(delim="\n", expect="YOU LOSE!")
            self.read(delim="\n\n", expect="Debiting %d from your hug balance." % wagered)
            self.hugs-=wagered

    def boards(self, which):
        return ["|---|\n|\n|\n|\n|\n______\n", "|---|\n|   O\n|\n|\n|\n______\n",
        "|---|\n|   O\n|   |\n|\n|\n______\n", "|---|\n|   O\n|  -|-\n|\n|\n______\n",
        "|---|\n|   O\n|  -|-\n|  / \\\n|\n______\n"][which];

    def hangman(self):
        if(self.hugs <= 0):
            return
        hmboard = 0
        self.write("2\n")
        bet = self.handleWager()
        word = linecache.getline("support/words", (self.doLFSR() % 235886) + 1).strip()
        boardmap = list("_" * len(word))
        letters = set([x for x in word])
        for letter in letters:
            self.read(length=len(self.boards(hmboard)), expect=self.boards(hmboard))
            self.read(delim="\n", expect=''.join(boardmap))
            self.read(delim=": ", expect="Please enter a guess")
            for i in range(len(word)):
                if word[i] == letter:
                    boardmap[i] = letter
            self.write(letter + "\n")
        self.read(delim="\n", expect="YOU WIN!")
        self.read(delim="\n\n", expect="Adding %d to your hug balance." % bet)
        self.hugs += bet

    def dicegame(self):
        if(self.hugs <= 0):
            return
        self.write("3\n")
        bet = self.handleWager()
        times = random.randint(1, 16)
        self.read(delim="? ", expect="How many rolls do you want")
        self.write("%d\n" % times)
        while(times > 0):
            roll = self.doLFSR() % 31338
            self.read(delim="\n", expect="Rolling a 31337 sided dice. 31337 wins jackpot. If you guess within 100, you win.")
            self.read(delim="? ", expect="What is your guess for the dice")
            if(roll == 31337):
                self.read(delim="\n", expect="!!!JACKPOT!!!YOU WIN!")
		bet = bet * 1000
                self.hugs+=bet
            	self.read(delim="\n\n", expect="Adding %d to your hug balance." % (bet))
            else:
            	self.write("%d\n" % roll)
            	self.read(delim="\n", expect="Yes! %d is 0 away from %d" % (roll, roll))
            	self.read(delim="\n", expect="YOU WIN!")
            	self.read(delim="\n\n", expect="Adding %d to your hug balance." % bet)
            	self.hugs+=bet
            times-=1

        pass

    def quit(self):
        if(self.hugs <= 0):
            return
        self.write("q\n")
        self.read(delim="\n", expect="Thanks for playing! Don't spend all your hugs in one place.")

    def end(self):
        pass
