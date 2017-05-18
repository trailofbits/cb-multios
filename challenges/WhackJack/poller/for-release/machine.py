#!/usr/bin/env python

from generator.actions import Actions
import random
import string
from struct import pack, unpack, unpack_from


class CameraSelect(Actions):


    def start(self):

        #self.delay(100)
        self.MaxPlayers = 8
        self.betSize = 5

        self.Players = []
        self.cardIndex = 0

        self.cardType = [ "", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"]

        self.silentMenu = False

        for i in range (0, self.MaxPlayers):
            self.Players.append(["", 500, 0, 0, False, 0, False, 0])

    def readMenu(self):

        
        if self.silentMenu:
            return

        self.read(delim = '\n', expect = '\n')
        self.read(delim='\n', expect ="1) Add Player\n")
        self.read(delim='\n', expect ="2) Delete Player\n")
        self.read(delim='\n', expect ="3) Play\n")
        self.read(delim='\n', expect ="4) Statistics\n")
        self.read(delim='\n', expect ="0) Exit\n")

    def top(self):
        
        self.readMenu()


    def addPlayer(self):


        self.write('1\n')

        length = random.randint(5, 10)
        PlayerName = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))
        slotFound = False


        for i in range(0, len(self.Players)):
            if len(self.Players[i][0]) == 0:
                self.Players[i] = [PlayerName, 500, 0, 0, False, 0, False, 0]
                slotFound = True
                break


        if slotFound == False:
            expect_string = "Too many players\n"
            self.read(delim = '\n', expect = expect_string)
        else:
            expect_string = "Enter player name\n"
            self.read(delim = '\n', expect = expect_string)
            self.write(PlayerName + '\n')
            expect_string = "Computer player? (y/n)\n"
            self.read(delim = '\n', expect = expect_string)
            

            computerPlayer = random.choice(['y', 'n'])
            self.write(computerPlayer+'\n')

            if computerPlayer == 'y':
                self.Players[i][4] = True;

                self.Players[i][5] = random.choice([0, 1, 2, 3])

                self.read(delim = '\n', expect = 'Method 1-4:\n')

                self.write('{}\n'.format(self.Players[i][5]+1))

            else:

                expect_string = "Would you like to enable hints?\n"
                self.read(delim = '\n', expect = expect_string)

                hints = random.choice(['y', 'n'])

                self.write(hints+'\n')

                if hints == 'y':

                    self.Players[i][6] = True
                    self.Players[i][7] = random.choice([0, 1, 2, 3])

                    self.read(delim = '\n', expect = 'Method 1-4:\n')
                    self.write('{}\n'.format(self.Players[i][7]+1))


    def deletePlayer(self):

        self.write('2\n')

        x = 1
        for i in range(0, len(self.Players)):
            if len(self.Players[i][0]) > 0:
                expect_string = '{}) {}\n'.format(x, self.Players[i][0])
                self.read(delim = '\n', expect = expect_string)
                x = x + 1

        if x == 1:
            expect_string = 'No players\n'
            self.read(delim = '\n', expect = expect_string)
            return

        expect_string = 'Player to delete (1-{}):\n'.format(x-1)
        self.read(delim = '\n', expect = expect_string)

        player2delete = random.randint(1, x)

        self.write('{}\n'.format(player2delete))

        x = 0
        for i in range(0, len(self.Players)):
            if len(self.Players[i][0]) > 0:
                x = x + 1

                if x == player2delete:
                    self.Players[i] = ['', 500, 0, 0, False, 0, False, 0]
                    break


    def showStats(self):

        self.write('4\n')

        for i in range(0, len(self.Players)):
            if len(self.Players[i][0]) > 0:
                expect_string = 'Player name: {}\n'.format(self.Players[i][0])
                self.read(delim = '\n', expect = expect_string)
                expect_string = "       Wins: {}\n".format(self.Players[i][2])
                self.read(delim = '\n', expect = expect_string)
                expect_string = "     Losses: {}\n".format(self.Players[i][3])
                self.read(delim = '\n', expect = expect_string)
                expect_string = "      Funds: {}\n".format(self.Players[i][1])
                self.read(delim = '\n', expect = expect_string)


    def make_int16(self, bytes):

        return(unpack('H', bytes[0:2])[0])

    def nextCardValue(self):

        rawValue = self.make_int16(self.magic_page[self.cardIndex:self.cardIndex+2])
        self.cardIndex = self.cardIndex + 2

        if self.cardIndex > 4094:
            self.cardIndex = 0

        return ((rawValue % 13) + 1)


    def scoreCards(self, cards):

        score = 0
        ace_count = 0

        for i in range(0, len(cards)):

            if cards[i] > 1 and cards[i] < 10:
                score = score + cards[i]

            elif cards[i] >= 10:
                score = score + 10

            elif cards[i] == 1:

                ace_count = ace_count + 1
                score = score + 11


        while score > 21 and ace_count > 0:
            score = score - 10
            ace_count = ace_count - 1

        return score


    def matchDealer(self, dealer_card, player_cards):


        player_score = self.scoreCards(player_cards)

        if player_score > 16:
            return 'S'
        else:
            return 'H'

    def basicAlgo(self, dealer_card, player_cards):

        player_score = self.scoreCards(player_cards)

        card_count = len(player_cards)

        hard = True

        if 1 in player_cards:
            hard = False

        if hard:

            if player_score < 12:
                answer = 'H'
            elif player_score > 16:
                answer = 'S'

            elif player_score > 11 and player_score < 17 and dealer_card > 6:
                answer = 'H'

            elif player_score == 12 and dealer_card < 4:
                answer = 'H'

            else:
                answer = 'S'

        else:

            if player_score < 18:
                answer = 'H'

            elif player_score == 18 and dealer_card > 8 and dealer_card < 11:
                answer = 'H'

            else:
                answer = 'S'

        return answer

    def neverBust(self, dealer_card, player_cards):

        if self.scoreCards(player_cards) > 11:
            answer = 'S'
        else:
            answer = 'H'

        return answer


    def simpleAlgo(self, dealer_card, player_cards):

        player_score = self.scoreCards(player_cards)

        card_count = len(player_cards)

        hard = True

        if 1 in player_cards:
            hard = False

        if hard:

            if player_score < 12:
                answer = 'H'
            elif player_score > 16:
                answer = 'S'
            elif dealer_card < 7:
                answer = 'S'
            else:
                answer = 'H'

        # soft hand
        else:

            if player_score < 18:
                answer = 'H'

            elif player_score == 18 and dealer_card < 7:
                answer = 'S'

            elif player_score == 18 and dealer_card > 7:
                answer = 'H'

            else:
                answer = 'S'

        return answer


    def playRound(self):


        self.write('3\n')

        playerCcount = 0

        for i in range(0, len(self.Players)):
            if len(self.Players[i][0]) > 0:
                playerCcount = playerCcount + 1

        if playerCcount == 0:
            expect_string = 'No players\n'
            self.read(delim = '\n', expect = expect_string)
            return

        for i in range(0, len(self.Players)):
            if len(self.Players[i][0]) == 0:
                continue

            expect_string = 'Player: {}\n'.format(self.Players[i][0])
            self.read(delim = '\n', expect = expect_string)

            expect_string = "Place your bet (1-{})\n".format(self.Players[i][1])
            self.read(delim = '\n', expect = expect_string)

            if self.Players[i][4] == False:
                self.write('{}\n'.format(self.betSize))

        dealerCards = []

        playerCards = []
        for i in range(0, self.MaxPlayers):
            playerCards.append([])

        dealerCards.append(self.nextCardValue())

        for i in range(0, len(self.Players)):
            if len(self.Players[i][0]) > 0:
                playerCards[i].append(self.nextCardValue())
            else:
                playerCards[i].append(0)


        dealerCards.append(self.nextCardValue())

        for i in range(0, len(self.Players)):
            if len(self.Players[i][0]) > 0:
                playerCards[i].append(self.nextCardValue())
            else:
                playerCards[i].append(0)


        expect_string = "Dealer: {} {} ({})\n".format(self.cardType[dealerCards[0]], self.cardType[dealerCards[1]], self.scoreCards(dealerCards));        
        self.read(delim = '\n', expect = expect_string)        

        for i in range(0, len(self.Players)):
            if len(self.Players[i][0]) > 0:
                expect_string = '{}: {} {} ({})\n'.format(self.Players[i][0], self.cardType[playerCards[i][0]], self.cardType[playerCards[i][1]], self.scoreCards(playerCards[i]))
                self.read(delim = '\n', expect = expect_string)


        # now go around the "table" and letting each player play 
        for i in range(0, len(self.Players)):
            if len(self.Players[i][0]) == 0:
                continue

            expect_string = 'Player: {}\n'.format(self.Players[i][0])
            self.read(delim = '\n', expect = expect_string)

            finished = 0

            while finished == 0:

                expect_string = ''

                for x in range(0, len(playerCards[i])):
                    expect_string = expect_string + '{} '.format(self.cardType[playerCards[i][x]])

                playerscore = self.scoreCards(playerCards[i])
                expect_string = expect_string + '({})\n'.format(playerscore)

                self.read(delim = '\n', expect = expect_string)

                if self.Players[i][6] == True:

                    self.read(delim = '\n', expect = 'Do you want a hint?')

                    if playerscore > 19: 
                        self.write('n\n')
                    else:

                        self.write('y\n')
                        if self.Players[i][7] == 0:
                            play = self.matchDealer(dealerCards[1], playerCards[i])
                        elif self.Players[i][7] == 1:
                            play = self.basicAlgo(dealerCards[1], playerCards[i])
                        elif self.Players[i][7] == 2:
                            play = self.simpleAlgo(dealerCards[1], playerCards[i])
                        elif self.Players[i][7] == 3:
                            play = self.neverBust(dealerCards[1], playerCards[i])

                        if play == 'S':
                            expect_string = "You should Stand\n"
                        elif play == 'H':
                            expect_string = "You should Hit\n"
                        else:
                            expect_string = "Uh.... it didn't say\n"


                        self.read(delim = '\n', expect = expect_string)


                self.read(delim = '\n', expect = 'Do you wish to H)it or S)tand\n')

                # is it a computer player
                if self.Players[i][4] == True:

                    if self.Players[i][5] == 0:
                        play = self.matchDealer(dealerCards[1], playerCards[i])
                    elif self.Players[i][5] == 1:
                        play = self.basicAlgo(dealerCards[1], playerCards[i])
                    elif self.Players[i][5] == 2:
                        play = self.simpleAlgo(dealerCards[1], playerCards[i])
                    elif self.Players[i][5] == 3:
                        play = self.neverBust(dealerCards[1], playerCards[i])

                    if play == 'S':
                        finished = 1
                    elif play == 'H':
                        drawCard = self.nextCardValue()
                        playerCards[i].append(drawCard)
                        playerscore = self.scoreCards(playerCards[i])

                        expect_string = '{} draws {}\n'.format(self.Players[i][0], self.cardType[drawCard])
                        self.read(delim = '\n', expect = expect_string)

                        if playerscore > 21:
                            finished = 1

                # no this is a "human" player so play for them
                else:
                    if playerscore < 15:

                        self.write('H\n')

                        drawCard = self.nextCardValue()
                        playerCards[i].append(drawCard)
                        playerscore = self.scoreCards(playerCards[i])

                        expect_string = '{} draws {}\n'.format(self.Players[i][0], self.cardType[drawCard])
                        self.read(delim = '\n', expect = expect_string)

                        # if player gets 21 or busts, automatically done
                        if playerscore > 21:
                            finished = 1

                    else:

                        self.write('S\n')
                        finished = 1


        # the dealer auto hits until her score is at least 17
        while self.scoreCards(dealerCards) < 17:

            drawCard = self.nextCardValue()
            dealerCards.append(drawCard)

            expect_string = 'Dealer draws {}\n'.format(self.cardType[drawCard])
            self.read(delim = '\n', expect = expect_string)


        dealerScore = self.scoreCards(dealerCards)

        for i in range(0, len(self.Players)):
            if len(self.Players[i][0]) == 0:
                continue

            expect_string = '{}: '.format(self.Players[i][0])

            playerscore = self.scoreCards(playerCards[i])

            if dealerScore > 21 and playerscore < 22:
                expect_string = expect_string + "wins!\n"
                self.read(delim = '\n', expect = expect_string)

                self.Players[i][1] = self.Players[i][1] + self.betSize
                self.Players[i][2] = self.Players[i][2] + 1
            elif playerscore > dealerScore and playerscore < 22:
                expect_string = expect_string + "wins!\n" 
                self.read(delim = '\n', expect = expect_string) 

                self.Players[i][1] = self.Players[i][1] + self.betSize
                self.Players[i][2] = self.Players[i][2] + 1
            elif playerscore == dealerScore:
                expect_string = expect_string + "pushes\n"  
                self.read(delim = '\n', expect = expect_string)    

            else:
                expect_string = expect_string + "loses\n"
                self.read(delim = '\n', expect = expect_string)

                self.Players[i][1] = self.Players[i][1] - self.betSize
                self.Players[i][3] = self.Players[i][3] + 1

                if self.Players[i][1] == 0:
                    self.Players[i] = ['', 500, 0, 0, False, 0, False, 0]


    def end(self):

        # tell it to exit normally
        self.write('0\n')








































































       
