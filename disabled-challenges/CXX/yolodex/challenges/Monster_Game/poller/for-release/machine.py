from generator.actions import Actions
import string
import random
import copy
import struct
def rs( length ):
	return ''.join( random.choice( string.lowercase + string.uppercase + string.digits) for _ in range(length) )

monster_names = [ "Lost Needless Duck",  "The Commander", "Toxic Major", "El Spider", "The Heroic Emperor", "Rock Beast", "Gamma Guardian", "Rough Wizard", "Persistent Puppet", "Pure Ghost Killer", "The Golden Oyster", "Hidden Leather", "Dreaded Digital Hawk", "The Admiral", "Sneaky Tough Electron", "Trolling Captain", "The Barbarian", "Elvish Moose", "Snappy Dinosaur", "The Bursting Wrench", "Itchy Eagle", "Angry Neutron", "Asada Gothar Derik", "Seth Bydern", "Quid Cipyar", "Amarisa Yerpal Jihb", "Tilthan", "Teressa Gosform", "Uerth Bredock Lidorn", "Raydan Fronar", "Aldaren Cevelt", "Florian", "Celestine Ixil Boldel", "Safize Ixen", "Corda Migorn", "Vigoth Boldel", "Gothar Mathar", "Vinkol Seryth", "Wrathran Palpur", "Luna Milen", "Zotar Phalloz", "Pildoor Vildar Virdo", "Odeir Jibar Wyeth", "Fearlock Breen", "Soderman Iroldak", "Lelani Oxpar Xavor" ]

class CROMU00076(Actions):
	def start(self):
		#self.delay(100)
		self.magic_index = 0
		self.player = {}
		self.queue = []

		self.generate_player()

		self.generate_map()

		for move in range( len( self.prev_solution)):
			self.read( delim=': ', expect=': ')
			self.write( self.prev_solution[move] + '\n')

			## update map
			self.set_marker( self.arena['current_x'], self.arena['current_y'], 0)

			if self.prev_solution[move] == 'u':
				self.arena['current_y'] -= 1
			elif self.prev_solution[move] == 'd':
				self.arena['current_y'] += 1
			elif self.prev_solution[move] == 'l':
				self.arena['current_x'] -= 1
			elif self.prev_solution[move] == 'r':
				self.arena['current_x'] += 1
			else:
				print '[ERROR] This should not be hit: %d' %(self.prev_solution[move])
				return

			self.set_marker( self.arena['current_x'], self.arena['current_y'], '@')

			self.print_map()

			## Check for end
			if ( self.arena['current_x'] == self.arena['end_x']) and ( self.arena['current_y'] == self.arena['end_y']):
				self.read( delim='\n', expect="reached the end\n")
				## Handle the boss
				val = self.daboss()

				if ( val == 1):
					self.read( delim='\n', expect='You won!!!\n')
				else:
					self.read(delim='\n', expect='You failed!!!\n')
				return

			## Check for monster
			y = self.pull_secret_byte()
			self.update_index()

			if ( y % 100 ) < 10:
				succ = self.fight()

				if succ == 1:
					self.player['level'] += 1
					self.read(delim='\n', expect='player gains a level. now %d' %(self.player['level']))


				self.print_map()

		pass

	def reset_monsters(self):
		for monster in self.player['monsters']:
			monster['health'] = monster['hitpoints']

	def print_monster(self, mons):
		self.read(delim='\n', expect="\tType: %s\n" %mons['type'])
		self.read(delim='\n', expect="\tLevel: %s\n" %mons['level'])
		self.read(delim='\n', expect="\tHealth: %s\n" %mons['health'])
		self.read(delim='\n', expect="\tHit Points: %s\n" %mons['hitpoints'])
		self.read(delim='\n\n', expect="\tPower: %s\n\n" %mons['power'])

	def select_monster( self ):

		success = 0

		for monster in self.player['monsters']:
			if monster['health'] > 0:
				success = 1

		if success == 0:
			return None

		self.read(delim='\n', expect='Monsters: \n')

		for index in range( len( self.player['monsters']) ):
			self.read(delim='\n', expect='\t%d} \n' %(index+1))
			self.read(delim='\n', expect="\tType: %s\n" %self.player['monsters'][index]['type'])
			self.read(delim='\n', expect="\tLevel: %s\n" %self.player['monsters'][index]['level'])
			self.read(delim='\n', expect="\tHealth: %s\n" %self.player['monsters'][index]['health'])
			self.read(delim='\n\n', expect="\tPower: %s\n\n" %self.player['monsters'][index]['power'])


		self.read(delim=': ', expect='Selection: ')

		### Just select the first one
		for index in range( len( self.player['monsters']) ):
			if self.player['monsters'][index]['health'] > 0:
				self.write( str(index+1) + '\n')
				return self.player['monsters'][index]

		return None
	

	def oneup_monster( self, monster ):

		monster['experience'] += 1

		if (monster['experience'] % 15) == 0:
			self.read(delim='\n', expect='%s gained a level\n' %(monster['type']))
			monster['hitpoints'] += 1
			monster['power'] += 1
			monster['health'] = monster['hitpoints']
			monster['level'] += 1
			monster['experience'] = 0
		return

	def capture_monster( self, monster):
		self.read( delim=': ', expect='capture monster? (y\\n): ')


		## randomly choose yes or now
		choice = random.choice( ['y', 'n'] )

		self.write( choice + '\n')

		if choice == 'n':
			return

		if len( self.player['monsters'] ) < 5:
			self.player['monsters'].append( monster)
			return

		self.read(delim='\n', expect='your cart is full.\n')

		for index in range(len(self.player['monsters'])):
			self.read(delim='\n', expect='%d} \n' %(index+1))
			self.print_monster( self.player['monsters'][index])

		self.read(delim='\n', expect='*********************************\n')
		self.print_monster( monster )
		self.read(delim='\n', expect='*********************************\n')
		self.read( delim=': ', expect='replace one of yours? (y\\n): ')

		## randomly decide to replace one
		choice = random.choice( ['y', 'n'])

		self.write(choice + '\n')

		if choice == 'n':
			return


		self.read( delim=': ', expect='which one: ')

		## select one to replace
		choice = random.randint( 0, 4)

		temp_monsters = copy.deepcopy( self.player['monsters'])

		temp_monsters = temp_monsters[0: choice] + [monster] + temp_monsters[ choice+1: 5]
		self.player['monsters'] = copy.deepcopy( temp_monsters )
		self.write( str(choice+1) + '\n')
		return

	def capture_boss( self, monster):
		self.read( delim=': ', expect='capture monster? (y\\n): ')


		## randomly choose yes or now
		choice = random.choice( ['y', 'n'] )

		self.write( choice + '\n')

		if choice == 'n':
			return

		self.read(delim=': ', expect='update boss name? (y\\n): ')

		## randomly decide to update name
		choice = random.choice( ['y', 'n'])

		self.write( choice + '\n')

		if choice == 'y':
			self.read(delim=': ', expect='New name: ')
			nn = rs(10)
			monster['type'] = nn
			self.write( nn + '\n')


		if len( self.player['monsters'] ) < 5:
			self.player['monsters'].append( monster)
			return

		self.read(delim='\n', expect='your cart is full.\n')

		for index in range(len(self.player['monsters'])):
			self.read(delim='\n', expect='%d} \n' %(index+1))
			self.print_monster( self.player['monsters'][index])

		self.read(delim='\n', expect='*********************************\n')
		monster['health'] = monster['hitpoints']
		self.print_monster( monster )
		self.read(delim='\n', expect='*********************************\n')
		self.read( delim=': ', expect='replace one of yours? (y\\n): ')

		## randomly decide to replace one
		choice = random.choice( ['y', 'n'])

		self.write(choice + '\n')

		if choice == 'n':
			return


		self.read( delim=': ', expect='which one: ')

		## select one to replace
		choice = random.randint( 0, 4)

		temp_monsters = copy.deepcopy( self.player['monsters'])

		temp_monsters = temp_monsters[0: choice] + [monster] + temp_monsters[ choice+1: 5]
		self.player['monsters'] = copy.deepcopy( temp_monsters )
		self.write( str(choice+1) + '\n')
		return


	def generate_boss(self):

		new_monster = {}

		new_monster['type'] = self.select_name()
		new_monster['health'] = (self.pull_secret_byte() % 10 ) + 9
		new_monster['hitpoints'] = new_monster['health']

		self.update_index()

		new_monster['power'] = (self.pull_secret_byte() % 6) + 4
		self.update_index()

		new_monster['level'] = 4
		new_monster['experience'] = 0

		return new_monster

	def daboss( self ):

		boss = self.generate_boss()
		self.reset_monsters()

		self.read(delim='UN\n', expect="\nDUN DUN DUUUUUUUUUUUUUUN\n")
		self.read(delim='\n\n', expect="You have reached the boss!!!!!\n\n")
		self.print_monster( boss );

		while boss['health'] > 0:

			defender = self.select_monster()

			if ( defender == None):
				self.read( delim='\n', expect='You have no living monsters. You lose.\n')
				return 0

			player_hit = self.pull_secret_byte() % defender['power']
			self.update_index()

			boss['health'] -= player_hit
			self.read( delim='\n', expect='You hit for %d. %d left\n' %(player_hit, boss['health']))
			self.oneup_monster( defender )

			if boss['health'] <= 0:
				self.read( delim='\n', expect='You destroyed the boss!!!!\n')
				self.reset_monsters()
				self.capture_boss( boss )
				return 1


			target_hit = self.pull_secret_byte() % boss['power']
			self.update_index();

			self.read(delim='\n', expect='%s hits %s for %d\n' %(boss['type'], defender['type'], target_hit))
			defender['health'] -= target_hit

			if ( defender['health'] <= 0 ):
				self.read( delim='\n', expect='%s was knocked out\n' %(defender['type']))

		return 1

	def fight( self ):

		self.reset_monsters()

		self.read(delim='\n', expect='You are being attacked!!!\n')

		new_monster = self.generate_monster()
		self.print_monster( new_monster )


		while new_monster['health'] > 0:

			defender = self.select_monster()

			if ( defender == None):
				self.read( delim='\n', expect='You have no living monsters. You lose.\n')
				return 0

			player_hit = self.pull_secret_byte() % defender['power']
			self.update_index()

			new_monster['health'] -= player_hit
			self.read( delim='\n', expect='You hit for %d. %d left\n' %(player_hit, new_monster['health']))
			self.oneup_monster( defender )

			if new_monster['health'] <= 0:
				self.read( delim='\n', expect='You knocked out %s\n' %(new_monster['type']))
				self.reset_monsters()
				self.capture_monster( new_monster )
				return 1


			target_hit = self.pull_secret_byte() % new_monster['power']
			self.update_index();

			self.read(delim='\n', expect='%s hits %s for %d\n' %(new_monster['type'], defender['type'], target_hit))
			defender['health'] -= target_hit

			if ( defender['health'] <= 0 ):
				self.read( delim='\n', expect='%s was knocked out\n' %(defender['type']))

		return 1

	def update_index(self):
		self.magic_index += 3

		self.magic_index = self.magic_index % 0x1000

	def select_name(self):
		value = self.pull_secret_byte()

		value = value % len(monster_names)
		self.update_index()

		return monster_names[value]

	def pull_secret_byte( self ):
		return struct.unpack('B', self.magic_page[ self.magic_index])[0]

	def generate_monster(self):

		new_monster = {}

		new_monster['type'] = self.select_name()
		new_monster['health'] = (self.pull_secret_byte() % 10 ) + 4
		new_monster['hitpoints'] = new_monster['health']

		self.update_index()

		new_monster['power'] = (self.pull_secret_byte() % 6) + 2
		self.update_index()

		new_monster['level'] = 1
		new_monster['experience'] = 0

		return new_monster

	def generate_player(self):
		self.read( delim='| ', expect='Enter your name|| ')

		l = random.randint( 1, 100 )

		if l < 10:
			self.write( '\n' )
			self.player['name'] = 'Player One'
		else:
			self.player['name']= rs( random.randint( 2, 11) )
			self.write( self.player['name'] + '\n')

		self.player['monsters'] = [] 
		for i in range(3):
			self.player['monsters'].append(self.generate_monster())

		self.player['level'] = 1

		self.read( delim='\n', expect='Name: ' + self.player['name'] + '\n')
		self.read( delim='\n', expect='Level: 1\n')
		self.read( delim='\n', expect='Monsters: \n')

		for m in self.player['monsters']:
			self.read( delim='\n', expect='\tType: ' + m['type'] + '\n')
			self.read( delim='\n', expect='\tHealth: ' + str(m['health']) + '\n')
			self.read( delim='\n\n', expect='\tPower: ' + str(m['power']) + '\n\n')

		return 1

	def set_marker( self, x, y, mark ):
		self.arena['map'][y][x] = mark

	def place_marker( self ):

		self.arena['last_x'] = self.pull_secret_byte() % self.arena['width']
		self.update_index();

		self.arena['last_y'] = self.pull_secret_byte() % self.arena['height']
		self.update_index()

		count = 0

		while ( self.arena['map'][ self.arena['last_y'] ][ self.arena['last_x']  ] != 0 ) and count < 100:
			self.arena['last_x'] = self.pull_secret_byte() % self.arena['width']
			self.update_index()

			self.arena['last_y'] = self.pull_secret_byte() % self.arena['height']
			self.update_index()
		
			count += 1

		done = 0
		if count == 100:
			for y in range( len( self.arena['map'])):
				for x in range( len( self.arena['map'][y])):
					if self.arena['map'][y][x] == 0:

						if done == 0:
							self.arena['last_x'] = x
							self.arena['last_y'] = y
							done = 1

		self.arena['map'][ self.arena['last_y'] ][ self.arena['last_x']  ] = '#'

		return

	def initialize_queue_matrix( self ):

		self.matrix = copy.deepcopy(self.arena['map'])

		for y in self.matrix:
			for x in range( len( y ) ):
				if y[x] != 0:
					y[x] = 1


	def add_queue( self, x, y, direction):

		if self.matrix[y][x] == 1:
			return


		self.matrix[y][x] = 1
		self.queue.append( [x, y, direction] )

	def check_adjacent( self, x, y ):
		if x == self.arena['end_x']:
			if ((y - 1) == self.arena['end_y']):
				self.solution = ['u']
				return 'u'
			elif ((y+1) == self.arena['end_y']):
				self.solution = ['d']
				return 'd'
		elif y == self.arena['end_y']:
			if ((x - 1) == self.arena['end_x']):
				self.solution = ['l']
				return 'l'
			elif ((x+1) == self.arena['end_x']):
				self.solution = ['r']
				return 'r'

		return 0

	def find_path( self, x, y, direction ):

		## First check adjacent
		if self.check_adjacent( x, y ) == 1:
			return [ 1, direction ]

		if 0 < y:
			### Queue up
			self.add_queue(x, y-1, 'u' )

		if x < (self.arena['width'] - 1):
			### Queue right
			self.add_queue(x+1, y, 'r' )

		if y < (self.arena['height'] - 1):
			### Queue down
			self.add_queue( x, y+1, 'd')

		if 0 < x:
			### Queue left
			self.add_queue( x - 1, y, 'l' )

		while len(self.queue):
			which_way = self.queue[0]
			self.queue = self.queue[1:]

			adj = self.check_adjacent( which_way[0], which_way[1])

			if adj != 0:
				return [1, which_way[2] + adj ]

			if 0 < which_way[1]:
				### Queue up
				self.add_queue(which_way[0], which_way[1]-1, which_way[2] + 'u' )

			if which_way[0] < (self.arena['width'] - 1):
				### Queue right
				self.add_queue(which_way[0]+1, which_way[1], which_way[2] + 'r' )

			if which_way[1] < (self.arena['height'] - 1):
				### Queue down
				self.add_queue( which_way[0], which_way[1]+1, which_way[2] + 'd')

			if 0 < which_way[0]:
				### Queue left
				self.add_queue( which_way[0] - 1, which_way[1], which_way[2] + 'l' )

		return [0, '']

	def print_map_no( self ):
		for y in self.arena['map']:
			z = ''
			for x in y:
				if x == 0:
					z += '.'
				else:
					z += str(x)
			z += '\n'
			print z
		print '\n'

	def print_map( self ):
		for y in self.arena['map']:
			z = ''
			for x in y:
				if x == 0:
					z += '.'
				else:
					z += str(x)
			z += '\n'
			self.read( delim='\n', expect=z)

	def generate_map(self): 
		self.arena = {}

		self.arena['width'] = (self.pull_secret_byte() % 31) + 5;
		self.update_index()

		self.arena['height'] = (self.pull_secret_byte() % 31) + 5;
		self.update_index()

		self.arena['start_x'] = 0
		self.arena['start_y'] = 0
		self.arena['end_x'] = 0
		self.arena['end_y'] = 0

		while (self.arena['start_x'] == self.arena['end_x']) or ( (self.arena['start_x']+1) == self.arena['end_x']) or ( (self.arena['start_x']-1) == self.arena['end_x']) or (self.arena['start_y'] == self.arena['end_y']) or ( (self.arena['start_y']+1) == self.arena['end_y']) or ( (self.arena['start_y']-1) == self.arena['end_y']):
			self.arena['start_x'] = self.pull_secret_byte() % self.arena['width']
			self.update_index()

			self.arena['start_y'] = self.pull_secret_byte() % self.arena['height']
			self.update_index()

			self.arena['end_x'] = self.pull_secret_byte() % self.arena['width']
			self.update_index()

			self.arena['end_y'] = self.pull_secret_byte() % self.arena['height']
			self.update_index()

		self.arena['current_x'] = self.arena['start_x']
		self.arena['current_y'] = self.arena['start_y']

		self.arena['map'] = []

		for y in range(self.arena['height']):
			self.arena['map'].append([])

			for x in range( self.arena['width']):
				self.arena['map'][y].append( 0 )

		self.set_marker( self.arena['start_x'], self.arena['start_y'], '@')
		self.set_marker( self.arena['end_x'], self.arena['end_y'], 'X')

		self.read( delim='\n\n', expect="Width: %d Height: %d\nStartX: %d StartY: %d\nEndX: %d EndY: %d\n\n" %(self.arena['width'], self.arena['height'], self.arena['start_x'], self.arena['start_y'], self.arena['end_x'], self.arena['end_y']))

		success = 0

		while success == 0:
			self.place_marker()

			self.initialize_queue_matrix()

			
			r = self.find_path( self.arena['start_x'], self.arena['start_y'], 's')

			self.queue = []

			### If the last placement failed then back off
			if r[0] == 0:
				self.arena['map'][ self.arena['last_y']][self.arena['last_x']] = 0
				success = 1
			else:
				self.prev_solution = r[1]
			
		self.print_map()

	def end(self):
		pass

