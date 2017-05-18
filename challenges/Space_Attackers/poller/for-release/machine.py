from generator.actions import Actions
import random
import struct
import sys
import random

class enemy(object):

	def __init__(self, x, y, board):
		self.myBoard = board
		self.x = x;
		self.y = y;
		self.quadrant = 0;
		self.homeColumn = x/2

	def __eq__(self, other):
		if (self.x == other.x) and (self.y == other.y):
			return True
		else:
			return False

	def move(self, newQuadrant):
		if self.quadrant == newQuadrant:
			return

		if self.quadrant == 0:
			if newQuadrant == 1:
				self.x = self.x + 1
			else:
				self.y = self.y + 1
		elif self.quadrant == 1:
			if newQuadrant == 0:
				self.x = self.x - 1
			else:
				self.y = self.y + 1
		elif self.quadrant == 2:
			if newQuadrant == 1:
				self.y = self.y - 1
			else:
				self.x = self.x - 1
		else:
			if newQuadrant == 2:
				self.x = self.x + 1
			else:
				self.y = self.y - 1

		self.quadrant = newQuadrant

	def step(self, randomNumber, clearToFire, advance):
		# check if the enemies need to move down one row
		if advance:
			self.y = self.y + 1

		move = randomNumber%7
		if move == 1:
			# fire
			if clearToFire == True:
				self.myBoard.addEnemyBullet(self.x, self.y)
		else:
			# move
			move = randomNumber%3

			newQuadrant = self.quadrant

			if move == 0:
				# move counter clockwise
				newQuadrant = newQuadrant-1
				if newQuadrant == -1:
					newQuadrant = 3
			elif move == 1:
				# move clockwise
				newQuadrant = newQuadrant+1
				if newQuadrant == 4:
					newQuadrant = 0

			self.move(newQuadrant)

class enemyBullet(object):

	def __init__(self, x, y, board):
		self.x = x
		self.y = y
		self.myBoard = board
	
	def __eq__(self, other):
		if (self.x == other.x) and (self.y == other.y):
			return True
		else:
			return False


	def step(self):
		if self.y < (self.myBoard.rows - 1):
			self.y = self.y + 1
			return True
		#if the bullet == now off the screen, return false
		return False

class userBullet(object):

	def __init__(self, x, y, board):
		self.x = x
		self.y = y
		self.myBoard = board

	def __eq__(self, other):
		if (self.x == other.x) and (self.y == other.y):
			return True
		else:
			return False

	def step(self):
		if self.y > 0:
			self.y = self.y - 1
			return True
		#if the bullet == now off the screen, return false
		return False

class board(object):

	def __init__(self, rows, columns, seed1, seed2):
		self.rows = rows
		self.columns = columns

		self.enemies = []
		self.enemyBullets = []

		self.userBullets = []
		self.shipCords = [0, rows-1]

		self.level = 0
		
		self.seed1 = seed1
		self.seed2 = seed2

		# Add enemies
		self.rowCount = 2;
		for i in xrange(self.rowCount):
			for j in xrange(int(self.columns/2)):
				newEnemy = enemy(j*2, i*2, self)
				self.enemies.append(newEnemy)

	def getRandomInt(self):
		self.seed1 = (((42871 * (self.seed1 & 0xFFFF)) & 0xffffffff) + (self.seed1 >> 16)) & 0xffffffff
		self.seed2 = (((28172 * (self.seed2 & 0xFFFF)) & 0xffffffff) + (self.seed2 >> 16)) & 0xffffffff
		return ((self.seed1 << 16) + self.seed2) & 0xffffffff;	

	def addEnemyBullet(self, x, y):
		self.enemyBullets.append(enemyBullet(x, y, self))

	def addEnemy(self, x, y):
		self.enemies.append(x, y, self)

	def addUserBullet(self, x, y):
		self.userBullets.append(userBullet(x, y, self))

	def updateUser(self, action):
		#check if user == dead
		for ele in self.enemyBullets:
			if (self.shipCords[0] == ele.x) and (self.shipCords[1] == ele.y):
				return False

		#fire
		if action == "~":
			self.addUserBullet(self.shipCords[0], self.shipCords[1])
		#up
		elif action == "w":
		   if self.shipCords[1] > 0:
			   self.shipCords[1] = self.shipCords[1] - 1
		#right
		elif action == "d":
		   if self.shipCords[0] < self.columns - 1:
			   self.shipCords[0] = self.shipCords[0] + 1
		#down
		elif action == "s":
		   if self.shipCords[1] < self.rows - 1:
			   self.shipCords[1] = self.shipCords[1] + 1
		#left
		elif action == "a":
		   if self.shipCords[0] > 0:
			   self.shipCords[0] = self.shipCords[0] - 1
		else:	
			self.addUserBullet(self.shipCords[0], self.shipCords[1])

		for ele in self.enemyBullets:
			if (self.shipCords[0] == ele.x) and (self.shipCords[1] == ele.y):
				return False
		return True

	def step(self, advance):
		output = ""
		#step the enemies
		for ele in self.enemies:
			# Check if enemy should be allowed to fire
			clearToFire = True
			for ele2 in self.enemies:
				if ele != ele2:
					if (ele2.homeColumn == ele.homeColumn) and (ele2.y > ele.y):
						clearToFire = False
			val = self.getRandomInt()
			output += str(val%1000) + "\n"
			ele.step(val, clearToFire, advance)

		#step enemy bullets
		self.enemyBullets = [x for x in self.enemyBullets if x.step()]

		#step user bullets
		self.userBullets = [x for x in self.userBullets if x.step()]

		#check for enemy collisions
		enemyHold = []
		userBulletHold = []
		for ele in self.enemies:
			for bullet in self.userBullets:
				if (ele.x == bullet.x) and (ele.y == bullet.y):
					enemyHold.append(ele)
					userBulletHold.append(bullet)
					
		for ele in enemyHold:
			self.enemies.remove(ele)

		for ele in userBulletHold:		
			self.userBullets.remove(ele)
		
		return output

	def draw(self, username, levelAdv):
		output = ""
	
		output += "\tWelcome to Attackers General " + username + "!"

		output += '\n'
		for i in xrange(self.columns+2):
			output += '-'
		output += '\n'

		for i in xrange(self.rows):
			output += '|'
			for j in xrange(self.columns):
				printed = False;
				# Check if we should print the user's ship
				if(self.shipCords[0] == j and self.shipCords[1] == i):
					output += 'W'
					printed = True

				# Check if we should print enemy bullet
				for ele in self.enemyBullets:
					if(ele.x == j and ele.y == i) and (printed == False):
						output += '+'
						printed = True
						break

				# Check if we should print an enemy
				for ele in self.enemies:
					if(ele.x == j and ele.y == i) and (printed == False):
						output += '#'
						printed = True
						break
				# Check if we should print user bullet
				for ele in self.userBullets:
					if(ele.x == j and ele.y == i) and (printed == False):
						output += '!'
						printed = True
						break

				# If there wasn't anything to draw, draw a space
				if(printed == False):
					output += ' '

			output += '|\n'
		for i in xrange(self.columns+2):
			output += '-'
		output += '\n'

		if levelAdv:
			self.level = self.level + 1

		# print level
		output += '\t\tLevel #' + str(self.level) + "\n"

		# Return the output of the draw
		return output

rows = 25
columns = 25

class game(object):

	def __init__(self, username, seed1, seed2, f):
		self.f = f
		self.username = username
		if self.username == "magic":
			self.seed1 = 0
			self.seed2 = 0
		else:
			self.seed1 = seed1
			self.seed2 = seed2
		
		self.lost = False		
		
		self.currentUserInput = ""
		
		self.turnCounter = 0
		self.level = 1	
		# Create the board
		self.myBoard = board(rows, columns, self.seed1, self.seed2)
	
	def next(self, userInput):
		enemyCount = len(self.myBoard.enemies)
		output = ""
		
		# If the user just pressed enter, account for that
		if len(userInput) == 0:
			userInput = "~"
		else:
			userInput = userInput[0]
	
		if enemyCount != 0:
			if self.turnCounter != 0:
				# Take action
				alive = self.myBoard.updateUser(self.currentUserInput)
				enemyCount = len(self.myBoard.enemies)

				if (self.turnCounter+1)%20 == 0:
					self.level += 1

				if (alive == False) or ((self.level >= 23) and (self.turnCounter%20 == 0)):
					#self.f.comment('you lose %d %d %d', alive, self.level, self.turnCounter)
					output += "\t\tyou lose\n\n\n\n\n"
					self.lost = True
					return output
				else:
					self.myBoard.step(((self.turnCounter%20) == 0))	

			# Draw the board
			output += self.myBoard.draw(self.username, (((self.turnCounter)%20) == 0))
			
			self.currentUserInput = userInput
			self.turnCounter += 1
		# We won
		if enemyCount == 0:
			danceX = 4
			danceY = 5
			num = 0
			for i in xrange(100000):
				output += "\t\t!!!DANCE MODE!!!\n\n\n\n\n\n\n\n"

				# Draw top of dance box
				for j in xrange(12):
					output += '-'
				output += '\n'

				# Draw out board
				for m in xrange(10):
					output += '|'
					for n in xrange(10):
						if (m == danceY) and (n == danceX):
							output += 'W'
						else:
							output += ' '
					output += '|\n'

				# Draw bottom of dance box
				for j in xrange(12):
					output += '-'
				output += '\n'

				output += "Bust a move (w = +1, s=SaveDigit, d=FIRE)\n"
				output += str(num) + '\n'
				input = raw_input()
				if len(input) == 0:
					input = "~"
				if input[0] == "w":
					num = num + 1
				elif input[0] == "s":
					num = 0

				# Move the ship randomly
				r = random.randint(0,4)
				if r == 0:
					if danceY == 0:
						danceY = 9
					else:
						danceY = danceY - 1
				elif r == 1:
					if danceY == 9:
						danceY = 0
					else:
						danceY = danceY + 1
				if r == 2:
					if danceX == 0:
						danceX = 9
					else:
						danceX = danceX - 1
				elif r == 3:
					if danceX == 9:
						danceX = 0
					else:
						danceX = danceX + 1

		return output


def random_string(cnt):
	return ''.join([chr(random.randint(97, 122)) for x in xrange(cnt)])
def random_input(cnt):
	rndStr = random_string(cnt)
	rndInp = ""
	for ele in rndStr:
		if ele != '\n':
			rndInp += ele
	
	return rndInp

class TemplateGenerator(Actions):
	def init_rng(self):
		vals = struct.unpack('<IIII', self.magic_page[0:16])
		self.state['seed1'] = (vals[0] ^ vals[1]) & 0xffffffff
		self.state['seed2'] = (vals[2] ^ vals[3]) & 0xffffffff

	def start(self):
		#self.delay(100)
		# read prompt
		self.read(delim='\n', expect='Please input your name:\n')

		# send name
		self.state['username'] = random_input(32)
		newUsername = ""
		for ele in self.state['username']:
			if ((ord(ele) >= 97) and (ord(ele) <= 122)):
				newUsername += ele
			else:
				break
		self.write(self.state['username'] + '\n')
		self.state['username'] = newUsername

		# Pull the secret values out		
		self.init_rng()

		# Setup game object
		self.game = game(self.state['username'], self.state['seed1'], self.state['seed2'], self)

	def go(self):
		while True:
			if self.game.lost == True:
				break
			# Get user input
			userInput = random_input(1) 
			# Get predicted gameboard state
			boardState = self.game.next(userInput)
			if not self.game.lost:
				self.write(userInput + '\n')
			
			#self.read(delim='\n', expect = str(struct.unpack('<i', struct.pack('<I', self.game.seed1))[0]) + " " + str(struct.unpack('<i', struct.pack('<I', self.game.seed2))[0]) + "\n")
			# Check if predicted gameboard state matches realtiy
			lines = boardState.split('\n')
			del lines[-1]
			for line in lines:
				self.read(delim='\n', expect=line+'\n')

	def quit(self):
		pass
