#!/usr/bin/env python
#
#
# Author: Debbie Nuttall <debbie@cromulence.co>
#
# Copyright (c) 2015 Cromulence LLC
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

import random
import struct
from collections import OrderedDict

from generator.actions import Actions, Variable

class Deck():
	SIZE_OF_DECK = 52
	DIAMONDS = 1
	SPADES = 2 
	HEARTS = 3
	CLUBS = 4
	face_value = [
		0,
		2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
		2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
		2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
		2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]


	def __init__(self, size, prng):
		self.SIZE_OF_DECK = size
		self.prng = prng
		self.card_names = ["NC"]
		suits = ["D", "S", "H", "C"]
		cards = [ '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A']
		for suit in suits:
			for card in cards:
				self.card_names.append(card+suit)


	def shuffle(self):
		self.deck = range(self.SIZE_OF_DECK)
		for i in range(0, self.SIZE_OF_DECK):
			j = self.prng.random_in_range(0, i)
			self.deck[i]= self.deck[j]
			self.deck[j] = i+1
		self.deck.reverse()

	def draw(self):
		try: 
			return self.deck.pop()
		except IndexError:
			print "Index Error drawing from empty deck"
			return 0

	def get_suit(self, card):
		if ((card <= 0) or (card > self.SIZE_OF_DECK + 1)):
			return 0;
		elif (card < 14):
			return self.DIAMONDS
		elif (card < 27):
			return self.SPADES
		elif (card < 40):
			return self.HEARTS
		else:
			return self.CLUBS

	def get_names(self, hand):
		s = ''
		for card in hand:
			s += self.card_names[card] + ' ' 
		return s

	def cmp_face_value(self, x,y):
		if (self.face_value[x] > self.face_value[y]):
			return 1
		elif (self.face_value[x] == self.face_value[y]):
			return 0
		else:
			return -1

	def count_matching(self, card, hand):
		count = 0
		for each in hand:
			if (self.cmp_face_value(card, each)==0):
				count += 1
		return count

	def blackjack_total(self, hand):
		total = 0
		aces = 0
		for card in hand:
			if (self.face_value[card] == 14):
				aces += 1
			elif (self.face_value[card] >= 10):
				total += 10
			else:
				total += self.face_value[card]
		while (aces > 0):
			if ((total + (aces-1) + 11) <= 21):
				total += 11
				aces -= 1
			else: 
				total += 1
				aces -= 1

		return total


class CasinoPollGenerator(Actions):
	

	def start(self):
		self.state["players"] = []
		self.state["current_player"] = None
		self.state["payouts"] = OrderedDict([("SLOTS_COLUMN_MATCH", 4),
									("SLOTS_ROW_MATCH", 4),
									("POKER_ROYAL_FLUSH", 500),
									("POKER_STRAIGHT_FLUSH", 200),
									("POKER_FLUSH", 40),
									("POKER_FOUR_OF_A_KIND", 100),
									("POKER_FULL_HOUSE", 50),
									("POKER_TWO_PAIR",10),
									("POKER_THREE_OF_A_KIND", 20),
									("POKER_JACKS_OR_BETTER", 10),
									("POKER_STRAIGHT",30),
									("BLACKJACK_PUSH", 10),
									("BLACKJACK_BLACKJACK", 25),
									("BLACKJACK_WIN", 20)])

		self.read(delim=':', expect="Enter your name:")
		if (self.chance(0.1)):
			# Hidden config interface
			name = "71db10261c"
			self.write(name + '\n')
			self.read(delim='\n', expect="Hello, {}!\n".format(name))
			self.read(delim='\n', expect="Access Granted")
			self.config()
		else:
			# Normal login
			name = data = ''.join(chr(random.randint(ord('!'),ord('~'))) for _ in range(random.randint(1,64)))
			self.write(name + '\n')
			self.read(delim='\n', expect="Hello, {}!\n".format(name))

		# Setup prng
		self.prng = Prng()
		seed = 0
		for i in range(0, len(name)):
			seed = (((seed << 8) & 0xffffffffffffffffL) | ((seed >> 56) ^ (ord(name[i]) & 0xff))) & 0xffffffffffffffffL
		
		self.prng.sprng(seed)
		self.deck = Deck(52, self.prng)

		

	def config(self):
		self.state["payouts"] = OrderedDict([("SLOTS_COLUMN_MATCH", random.randint(0,4)),
									("SLOTS_ROW_MATCH", random.randint(0,4)),
									("POKER_ROYAL_FLUSH", random.randint(0,500)),
									("POKER_STRAIGHT_FLUSH", random.randint(0,200)),
									("POKER_FLUSH", random.randint(0,40)),
									("POKER_FOUR_OF_A_KIND", random.randint(0,100)),
									("POKER_FULL_HOUSE",random.randint(0, 50)),
									("POKER_TWO_PAIR", random.randint(0,10)),
									("POKER_THREE_OF_A_KIND", random.randint(0,20)),
									("POKER_JACKS_OR_BETTER", random.randint(0,10)),
									("POKER_STRAIGHT", random.randint(0,30)),
									("BLACKJACK_PUSH", random.randint(0,10)),
									("BLACKJACK_BLACKJACK", random.randint(0,25)),
									("BLACKJACK_WIN", random.randint(0,20))])

		numbers = self.state["payouts"].values()
		data = struct.pack("<" + "i"*len(numbers), *numbers)
		encoded = ''
		lookup = "!@#$%^&+=:><|?~*"
		for each in data:
			encoded += lookup[ord(each)&0xf]
			encoded += lookup[ord(each)>>4]

		self.write(struct.pack("<i", len(encoded)))
		self.write(encoded)

	def menu(self):
		self.read(delim='\n', expect='\n')
		self.read(delim='\n', expect="1. Play Blackjack\n")
		self.read(delim='\n', expect="2. Play Poker\n")
		self.read(delim='\n', expect="3. Play Slots\n")
		self.read(delim='\n', expect="4. Enter a Players Club Number\n")
		self.read(delim='\n', expect="5. Register a new Player\n")
		self.read(delim='\n', expect="6. Show Player Status\n")
		self.read(delim='\n', expect="7. Show All Players\n")
		self.read(delim='\n', expect="8. Exit\n")
		self.read(delim=':', expect="Select a number:")
		

	def blackjack(self):
		self.write("1\n")
		self.read(delim='\n', expect="Play Blackjack\n")

		player = {"name":"", "number":0, "wallet":0, "b_score":0, "p_score":0, "s_score":0}
		
		if (self.state["current_player"] != None):
			player = self.state["players"][self.state["current_player"]]

		if (player["wallet"]>=10):
			player["wallet"] -= 10
		player["b_score"] += 50

		self.deck.shuffle()
		playerhand = []
		playerhand.append(self.deck.draw())
		dealerhand = []
		dealerhand.append(self.deck.draw())
		playerhand.append(self.deck.draw())
		dealerhand.append(self.deck.draw())
		
		self.read(delim='\n', expect="D: * " + self.deck.get_names([dealerhand[1]]))
		self.read(delim='\n', expect="P: " + self.deck.get_names(playerhand))
		

		result = ""
		if (self.deck.blackjack_total(dealerhand) == 21):
			if (self.deck.blackjack_total(playerhand) == 21):
				result = "Dealer Blackjack! Player Blackjack! You Tie :/"
				player["wallet"] += self.state["payouts"]["BLACKJACK_PUSH"]
			else:
				result = "Dealer Blackjack! You Lose!"
		elif (self.deck.blackjack_total(playerhand) == 21):
			result = "Blackjack! You Win!"
			player["wallet"] += self.state["payouts"]["BLACKJACK_BLACKJACK"]

		else:
			# Play Player Hand
			while (self.deck.blackjack_total(playerhand) < 17):
				self.read(delim=':', expect="Enter h for hit or s for stand:")
				self.write("h\n")	
				playerhand.append(self.deck.draw())
				self.read(delim='\n', expect="P: " + self.deck.get_names(playerhand))
			if (self.deck.blackjack_total(playerhand)>21):
				self.read(delim='\n', expect="Bust")
			else:
				self.read(delim=':', expect="Enter h for hit or s for stand:")
				self.write("s\n")

			# Play Dealer Hand			
			self.read(delim='\n', expect="D: " + self.deck.get_names(dealerhand))	
			while (self.deck.blackjack_total(dealerhand) < 17):
				dealerhand.append(self.deck.draw())
				self.read(delim='\n', expect="D: " + self.deck.get_names(dealerhand))	
			
			if (self.deck.blackjack_total(playerhand) > 21):
				result = "Player Bust. You Lose."
			elif (self.deck.blackjack_total(dealerhand) > 21):
				result = "Dealer Bust. You Win."
				player["wallet"] += self.state["payouts"]["BLACKJACK_WIN"]
			elif (self.deck.blackjack_total(dealerhand) > self.deck.blackjack_total(playerhand)):
				result = "You Lose."
			elif (self.deck.blackjack_total(dealerhand) == self.deck.blackjack_total(playerhand)):
				result = "Push."
				player["wallet"] += self.state["payouts"]["BLACKJACK_PUSH"]
			else:
				result = "You Win."
				player["wallet"] += self.state["payouts"]["BLACKJACK_WIN"]
			self.read(delim='\n', expect="P:{} D:{}".format(self.deck.blackjack_total(playerhand), self.deck.blackjack_total(dealerhand)))
		self.read(delim='\n', expect=result)
		if (self.state["current_player"] != None):
			self.state["players"][self.state["current_player"]] = player

		self.menu()
		self.show_status()

	def poker(self):
		self.write("2\n")
		self.read(delim='\n', expect='Play Poker')
		player = {"name":"", "number":0, "wallet":0, "b_score":0, "p_score":0, "s_score":0}
		
		if (self.state["current_player"] != None):
			player = self.state["players"][self.state["current_player"]]

		if (player["wallet"]>=5):
			player["wallet"] -= 5

		player["p_score"] += 100
		self.deck.shuffle()
		# Draw hand
		hand = []
		for i in range(5):
			hand.append(self.deck.draw())

		self.read(delim='\n', expect=self.deck.get_names(hand))
		# Hold none
		self.read(delim='\n', expect="Enter cards to hold by number (ex: 13 or 12345). Others will be replaced.")
		self.write("\n")
		# Draw new hand
		hand = []
		for i in range(5):
			hand.append(self.deck.draw())

		self.read(delim='\n', expect=self.deck.get_names(hand))

		result = ""
		hand.sort()
		# Process results
		if ((self.deck.get_suit(hand[0]) == self.deck.get_suit(hand[1])) and
		(self.deck.get_suit(hand[0]) == self.deck.get_suit(hand[2])) and
		(self.deck.get_suit(hand[0]) == self.deck.get_suit(hand[3])) and
		(self.deck.get_suit(hand[0]) == self.deck.get_suit(hand[4]))):
			if (self.deck.face_value[hand[0]]==10):
				result = "Royal Flush!"
				player["wallet"] += self.state["payouts"]["POKER_ROYAL_FLUSH"]
			elif (hand[4] == hand[0] + 4):
				result = "Straight Flush!"
				player["wallet"] += self.state["payouts"]["POKER_STRAIGHT_FLUSH"]
			else:
				result = "Flush!"
				player["wallet"] += self.state["payouts"]["POKER_FLUSH"]
		else:
			hand.sort(self.deck.cmp_face_value)
			pair = 0
			i = 0
			while (i<4):
				if (self.deck.count_matching(hand[i], hand) == 4):
					result = "Four of a kind!"
					player["wallet"] += self.state["payouts"]["POKER_FOUR_OF_A_KIND"]
					i = i + 4
				elif (self.deck.count_matching(hand[i], hand) == 3):
					if (pair == 1):
						if (result == "Jacks or better!"):
							player["wallet"] -= self.state["payouts"]["POKER_JACKS_OR_BETTER"]
						result = "Full House!"
						player["wallet"] += self.state["payouts"]["POKER_FULL_HOUSE"]
					else:
						result = "Three of a kind!"
						player["wallet"] += self.state["payouts"]["POKER_THREE_OF_A_KIND"]
					i = i + 3
				elif (self.deck.count_matching(hand[i], hand) == 2):
					if (pair == 1):
						if (result == "Jacks or better!"):
							player["wallet"] -= self.state["payouts"]["POKER_JACKS_OR_BETTER"]
						player["wallet"] += self.state["payouts"]["POKER_TWO_PAIR"]
						result = "Two Pair!"
					elif (result == "Three of a kind!"):
						result = "Full House!"
						player["wallet"] -= self.state["payouts"]["POKER_THREE_OF_A_KIND"]
						player["wallet"] += self.state["payouts"]["POKER_FULL_HOUSE"]
					else:
						pair = 1
						if (self.deck.cmp_face_value(9, hand[i]) == -1):
							result = "Jacks or better!"
							player["wallet"] += self.state["payouts"]["POKER_JACKS_OR_BETTER"]
					i = i + 2
				else:
					i = i + 1
			

		if ((result == "") and (pair == 0)): 
			if (self.deck.face_value[hand[4]] == self.deck.face_value[hand[0]] + 4):
				result = "Straight!"
				player["wallet"] += self.state["payouts"]["POKER_STRAIGHT"]

		if (result == ""):
			result = "You Lose!"

		self.read(delim='\n', expect=result)

		# Draw new hand
		hand = []
		for i in range(5):
			hand.append(self.deck.draw())

		self.deck.shuffle()
		self.read(delim='\n', expect=".*\n", expect_format="pcre")
		self.read(delim='\n', expect="Enter cards to hold by number (ex: 13 or 12345). Others will be replaced.")
		self.write('q\n')

		if (self.state["current_player"] != None):
			self.state["players"][self.state["current_player"]] = player

		self.menu()
		self.show_status()

	def slots(self):
		self.write('3\n')
		rows = random.randint(2, 5)
		self.read(delim='\n', expect="Play Slots")
		player = {"name":"", "number":0, "wallet":0, "b_score":0, "p_score":0, "s_score":0}
		if (self.state["current_player"] != None):
			player = self.state["players"][self.state["current_player"]]

		if (player["wallet"]>=2):
			player["wallet"] -= 2
		player["s_score"]+= 1

		self.read(delim=':', expect="Enter number of rows (2 to 5):")
		self.write(str(rows) + '\n')
		max_char = ord('/')
		if (rows == 3):
			max_char = ord('!') + 6
		elif (rows == 4):
			max_char = ord('!') + 4
		elif (rows == 5):
			max_char = ord('!') + 2

		board = []
		for i in range(rows):
			line = []
			for j in range(rows):
				line.append(self.prng.random_in_range(ord('!'), max_char))
			board.append(line)

		for j in range(rows):
			line = ''
			for i in range(rows):
				line += '{} '.format(chr(board[i][j]))
			self.read(delim='\n', expect=line + '\n')

		for i in range(rows):
			for j in range(rows)[1:]:
				if (board[i][j] != board[i][0]): 
					break;
				if (j == rows - 1):
					self.read(delim='\n', expect='Column match: {}!'.format(i))
					player["wallet"] += self.state["payouts"]["SLOTS_COLUMN_MATCH"]

		for j in range(rows):
			for i in range(rows)[1:]:
				if (board[i][j] != board[0][j]):
					break
				if (i == rows - 1):
					self.read(delim='\n', expect='Row match: {}!'.format(j))
					player["wallet"] += self.state["payouts"]["SLOTS_ROW_MATCH"]
						
		self.read(delim=':', expect="Enter q to quit, any other key to play again:")
		self.write('q\n')
		if (self.state["current_player"] != None):
			self.state["players"][self.state["current_player"]] = player

		self.menu()
		self.show_status()

	def lookup_player(self, number):
		for i in range(len(self.state["players"])):
			if self.state["players"][i]["number"] == number:
				return i
		return None

	def enter_players_club(self):
		self.write("4\n")
		self.read(delim=":", expect="Enter Player Number")
		if ((len(self.state["players"]) == 0) or self.chance(0.2)):
			rand = random.randint(0, 0xffffffff)
			while (self.lookup_player(rand)!= None):
				rand = random.randint(0, 0xffffffff)
			self.write(str(rand) + '\n')
			self.read(delim='\n', expect="Player not found")
			self.state["current_player"] = None
		else:
			self.state["current_player"] = random.randint(0, len(self.state["players"])-1)
			player =self.state["players"][self.state["current_player"]] 
			self.write(str(player["number"]) + '\n')
			self.read(delim='\n', expect="Hello, {}!".format(player["name"]))


	def player_stats(self, player):
		self.read(delim='\n', expect="Player Name: " + player["name"])
		self.read(delim='\n', expect="Player Number: " + str(player["number"]))
		self.read(delim='\n', expect="Blackjack Score: " + str(player["b_score"]))
		self.read(delim='\n', expect="Poker Score: " + str(player["p_score"]))
		self.read(delim='\n', expect="Slots Score: " + str(player["s_score"]))
		self.read(delim='\n\n', expect="Player Wallet Balance: " + str(player["wallet"]))

	def register_player(self):
		self.write("5\n")
		self.read(delim=':', expect="Register a new Player\nEnter your name")
		names = ["Aragorn son of Arathorn", "Arwen Undomiel", "Bilbo Baggins", "Boromir", "Denethor", "Elrond, Lord of Rivendell", "Eomer", "Eowyn", "Faramir", "Frodo Baggins", "Galadriel",
		"Gandalf", "Gimli", "Gollum", "Haldir", "Isildur", "Legolas", "Merry", "Pippin", "Sam", "Saruman", "Theoden", "Treebeard", "Wormtongue" ]
		name = names[random.randint(0, len(names) - 1)]
		self.write(name + '\n')
		self.read(delim=':', expect="How much cash do you want to spend?")
		wallet = random.randint(0, 1000)
		self.write(str(wallet) + '\n')
		number = self.prng.prng() & 0x7fffffff
		self.state["players"].insert(0, {"name":name, "number":number, "wallet":wallet, "b_score":0, "p_score":0, "s_score":0})
		if self.state["current_player"] != None:
			self.state["current_player"] += 1
		self.player_stats(self.state["players"][0])


	def show_status(self):
		self.write("6\n")
		if (self.state["current_player"] == None):
			self.read(delim='\n', expect="Player does not exist")
		else:
			self.player_stats(self.state["players"][self.state["current_player"]])

	def leaderboard(self):
		self.write("7\n")
		self.read(delim='\n', expect="Show All Players")
		for each in self.state["players"]:
			self.player_stats(each)


	def exit(self):
		self.write("8\n")
		self.read(delim='\n')
		self.write("y\n")
		self.read(delim='\n', expect=".*", expect_format="pcre")


class Prng():

	COEFFICIENT_A_64 = 12
	COEFFICIENT_B_64 = 25
	COEFFICIENT_C_64 = 27
	MULTIPLIER_64 = 1803442709493370165
	COEFFICIENT_A_1024 = 27
	COEFFICIENT_B_1024 = 13
	COEFFICIENT_C_1024 = 46
	MULTIPLIER_1024 = 1865811235122147685

	def __init__(self):
		self.state = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
		self.position = 0

	def sprng(self, seed):

		state_64 = seed & 0xffffffffffffffffL
		for i in range(16):
			state_64 ^= (state_64 >> self.COEFFICIENT_A_64)& 0xffffffffffffffffL
			state_64 ^= (state_64 << self.COEFFICIENT_B_64)& 0xffffffffffffffffL
			state_64 ^= (state_64 >> self.COEFFICIENT_C_64)& 0xffffffffffffffffL
			self.state[i] = (state_64 *self.MULTIPLIER_64)& 0xffffffffffffffffL
		self.position = 0

	def prng(self):
		
		state0 = self.state[self.position]
		self.position = (self.position +1) % 16
		state1 = self.state[self.position]

		state1 ^= (state1 << self.COEFFICIENT_A_1024)& 0xffffffffffffffffL
		state1 ^= (state1 >> self.COEFFICIENT_B_1024)& 0xffffffffffffffffL
		state0 ^= (state0 >> self.COEFFICIENT_C_1024)& 0xffffffffffffffffL
		self.state[self.position] = (state0 ^ state1)& 0xffffffffffffffffL
		return (self.state[self.position] * self.MULTIPLIER_1024)& 0xffffffffffffffffL

	def random_in_range(self, min, max):
		
		if (max <= min):
			return 0
		range = max - min + 1
		scale_factor = 0xffffffff / range
		#discard numbers that would cause bias
		while True:
			rand_uint = self.prng() & 0xffffffff
			if (rand_uint < (scale_factor * range)):
				break

		return (rand_uint / scale_factor + min)
