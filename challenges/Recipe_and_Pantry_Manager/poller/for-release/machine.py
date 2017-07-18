from generator.actions import Actions
import string
import random
import ctypes as ct
import sys
import struct

def rs( length ):
	return ''.join( random.choice( string.lowercase + string.uppercase + string.digits) for _ in range(length) )

class CROMU00087(Actions):
	def start(self):
		#self.delay(100)
		self.dll = ct.CDLL('build/patched/so/CROMU_00087.so')
		self.multiply = self.dll.multiply
		self.multiply.argtypes = (ct.c_double, ct.c_double)
		self.multiply.restype = ct.c_double

		self.add = self.dll.add
		self.add.argtypes = (ct.c_double, ct.c_double)
		self.add.restype = ct.c_double

		self.recipes = []
		self.pantries = []
		self.recipe_count = 0
		self.pantry_count = 0

		self.depth = 0
		self.max_depth = 100

		### Init recipe array
		for _ in range(512):
			self.recipes.append([])

		## Init pantry array
		for _ in range(128):
			self.pantries.append([])
		
		self.ingredients = []

		## Generate some ingredients
		count = random.randint(20, 30)

		for _ in range(count):
			nm = rs( random.randint( 5, 10 ) )

			while nm in self.ingredients:
				nm = rs( random.randint( 5, 10 ) )

			self.ingredients.append( nm )


		### Handle the banner
		self.banner()

		## Generate some pantries
		self.menu()

		count = random.randint( 2, 3)

		self.pantry()
		self.pantry_menu()

		for _ in range(count):
			self.create_pantry()
			self.pantry_menu()

		self.leave_pantry()

		self.menu()

		### Generate some recipes
		self.recipe()
		self.recipe_menu()

		count = random.randint( 2, 4)

		for _ in range(count):
			self.add_recipe()
			self.recipe_menu()

		self.leave_recipe_menu()

		self.depth = 0
		self.max_depth = 7

	def banner(self):
		self.read(delim=': ', expect='Today: ')

		month = struct.unpack('B', self.magic_page[0])[0] % 12
		year = 2016

		if month == 1:
			day = struct.unpack('B', self.magic_page[10])[0] % 29
		elif month in [3,6,9,11]:
			day = struct.unpack('B', self.magic_page[10])[0] % 30
		else:
			day = struct.unpack('B', self.magic_page[10])[0] % 31

		hour = struct.unpack('B', self.magic_page[20])[0] %24
		minute = struct.unpack('B', self.magic_page[30])[0] % 60
		second = struct.unpack('B', self.magic_page[40])[0] % 60

		dow = struct.unpack('B', self.magic_page[50])[0] % 7

		fdow = ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat']
		fmon = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec']

		self.read(delim=' ', expect='%s ' %(fdow[dow]))
		self.read(delim=' ', expect='%s ' %(fmon[month]))
		self.read(delim='\n\n', expect='%.2d:%.2d:%.2d %d\n\n' %(hour, minute, second, year))


	def menu(self):
		self.depth += 1

		self.read(delim='\n', expect='1) Recipe Menu\n')
		self.read(delim='\n', expect='2) Pantry Menu\n')
		self.read(delim='\n', expect='3) Query Recipe\n')
		self.read(delim='\n', expect='4) Quit\n')
		self.read(delim=' ', expect='-> ')

		if self.depth > self.max_depth:
			self.write('4\n')
			self.read(delim='\n')
			return -1

	def recipe(self):
		self.write('1\n')

	def recipe_menu( self ):
		self.depth += 1

		self.read(delim='\n', expect='1) Add Recipe\n')
		self.read(delim='\n', expect='2) Remove Recipe\n')
		self.read(delim='\n', expect='3) List Recipe\n')
		self.read(delim='\n', expect='4) List All\n')
		self.read(delim='\n', expect='5) Print Name\n')
		self.read(delim='\n', expect='6) Recipe Costs\n')
		self.read(delim='\n', expect='7) Leave Menu\n')
		self.read(delim='-> ', expect='-> ')

		if self.depth > self.max_depth:
			self.write( '7\n')
			self.read(delim='-> ')
			self.write('4\n')
			self.read(delim='\n')
			return -1

	def prn(self):
		## If no recipes exist then create a few
		if self.recipe_count == 0:
			for i in range( random.randint(2, 6)):
				self.add_recipe()
				self.recipe_menu()


		self.write('5\n')

		self.read(delim=': ', expect='Recipe Index [1..512]: ')

		r = random.randint( 1, self.recipe_count)

		k = 0

		while r != 0:
			if self.recipes[k] != []:
				r -= 1

			if r:
				k += 1

		self.write( str(k + 1 ) + '\n')
		self.read(delim='\n', expect='Single Name: %s\n' %(self.recipes[k][0]))


	def delete_pantry(self):

		### Don't remove the last pantry. Create one first
		if self.pantry_count < 2:
			self.create_pantry()
			self.depth -= 1
			self.pantry_menu()

		self.write('2\n')

		for i in range( len(self.pantries) ):
			if self.pantries[i] == []:
				continue

			self.read(delim='\n', expect='Index: %d\n' %(i+1))

			self.read(delim='\n', expect='Name: %s\n' %(self.pantries[i][0]))
			self.read(delim='\n', expect='Item:\n')

			for ing in self.pantries[i][1]:
				self.read(delim='\n', expect='\t%.6f %s\t%s\n' %(float(ing[1]), ing[3], ing[0]))

			self.read(delim='\n\n', expect='\n\n')

		self.read(delim=': ', expect='Pantry Index [1..128]: ')

		## Small chance of an error

		r = random.randint(0, 100)

		if r < 2:
			if random.randint(0, 1 ) or self.pantry_count == 128:
				self.write( str(random.randint(129, 150)) + '\n')
				self.read(delim='\n', expect='[ERROR] Must be between 1 and 128\n')
				return
			else:
				for i in range( len(self.pantries)):
					if self.pantries[i] == []:
						self.write( str(i+1) + '\n')
						self.read(delim='\n', expect='[ERROR] Empty pantry\n')
						return

		r = random.randint( 1, self.pantry_count)
		i = 0

		while r:
			if self.pantries[i] != []:
				r -= 1

			if r:
				i += 1

		self.write( str(i+1) + '\n')
		self.pantry_count -= 1
		self.pantries[i] = []

	def add_recipe( self ):
		self.write('1\n')
		self.read(delim=': ', expect="Enter recipe name: ")

		new_recipe = []
		
		new_recipe.append(rs( random.randint(5,10)))

		self.write( new_recipe[0] + '\n')

		count = random.randint( 1, 5 )

		i = []

		tr = self.ingredients[:]

		for _ in range( count ):
			r = random.choice( tr )

			tr.remove(r)

			amnt = str( random.random()*10)[:4]
			cost = str( random.random()*10)[:4]

			t = random.choice( ['oz', 'gram'])

			i.append([r, amnt, cost, t])

		for x in i:
			self.read(delim='\n', expect='Enter ingredient name or a \"done\" to quit.\n')
			self.read(delim=': ', expect=': ')
			self.write( x[0] + '\n')
			self.read(delim=': ', expect='Enter the amount: ')
			self.write( x[1] + '\n')
			self.read(delim=': ', expect='Enter the cost per unit: ')
			self.write( x[2] + '\n')
			self.read(delim=': ', expect='Enter the type (oz/gram):')
			self.write( x[3] + '\n')

			if x[3] == 'gram':
				x[3] = 'g'

		self.read(delim='\n', expect='Enter ingredient name or a \"done\" to quit.\n')
		self.read(delim=': ', expect=': ')
		self.write('done\n')

		i.reverse()

		new_recipe.append(i)

		count = random.randint( 3, 7)

		j = []

		for _ in range(count):
			self.read(delim=': ', expect='Enter Instruction: ')
			ins = rs(random.randint( 10,20))

			j.append(ins)

			self.write( ins + '\n')

		self.read(delim=': ', expect='Enter Instruction: ')
		self.write('done\n')

		new_recipe.append(j)

		for i in range( len(self.recipes) ):
			if self.recipes[i] == []:
				self.recipes[i] = new_recipe
				break

		self.recipe_count += 1

	def remove_recipe( self):

		## Don't remove the last recipe Create one first
		if self.recipe_count == 1:
			self.add_recipe()
			self.depth -= 1
			self.recipe_menu()

		self.write('2\n')

		for i in range( len(self.recipes)):
			if self.recipes[i] == []:
				continue

			self.read(delim='\n', expect='Index: %d\n' %(i+1))
			self.read(delim='\n', expect='Name: %s\n' %(self.recipes[i][0]))
			self.read(delim='\n', expect='Ingredients:\n')

			for ing in self.recipes[i][1]:
				self.read(delim='\n', expect='\t%.6f %s\t%s\n' %(float(ing[1]), ing[3], ing[0]))

			self.read(delim='\n', expect='\n')
			self.read(delim='\n', expect='Instructions:\n')

			for j in range(len(self.recipes[i][2])):
				self.read(delim='\n', expect='\t%d) %s\n' %(j+1, self.recipes[i][2][j]))

			self.read(delim='\n\n', expect='\n\n')

		self.read(delim=': ', expect='Recipe Index [1..512]: ')

		## small chance of an invalid number
		r = random.randint(0, 100)

		if r < 5:
			r = random.randint( 0, 1)

			if r or self.recipe_count == 512:
				self.write(str( random.randint(520, 550) ) + '\n')
				self.read( delim='\n', expect='[ERROR] Must be between 1 and 512\n')
				return 
			else:
				## find the first empty
				i = 0

				while i < 512:
					if self.recipes[i] == []:
						self.write( str( i+1) + '\n')
						self.read(delim='\n', expect='[ERROR] Empty recipe\n')
						return

					i += 1

			return

		## select a recipe
		r = random.randint( 1, self.recipe_count)

		k = 0

		while r != 0:
			if self.recipes[k] != []:
				r -= 1

			if r:
				k += 1

		self.recipes[k] = []
		self.recipe_count -= 1

		self.write( str(k+1) + '\n')


	def list_recipe( self ):

		## If no recipes exist then create a few
		if self.recipe_count == 0:
			for i in range( random.randint(1, 4)):
				self.add_recipe()
				self.recipe_menu()


		## select a recipe
		r = random.randint( 1, self.recipe_count)

		i = 0

		while r != 0:
			if self.recipes[i] != []:
				r -= 1

			if r:
				i += 1


		self.write('3\n')
		self.read(delim=': ', expect='Recipe Index [1..512]: ')
		self.write(str(i+1) + '\n')
		self.read(delim='\n', expect='Name: %s\n' %(self.recipes[i][0]))
		self.read(delim='\n', expect='Ingredients:\n')

		for ing in self.recipes[i][1]:
			self.read(delim='\n', expect='\t%.6f %s\t%s\n' %(float(ing[1]), ing[3], ing[0]))

		self.read(delim='\n', expect='\n')
		self.read(delim='\n', expect='Instructions:\n')

		for j in range(len(self.recipes[i][2])):
			self.read(delim='\n', expect='\t%d) %s\n' %(j+1, self.recipes[i][2][j]))

		self.read(delim='\n\n', expect='\n\n')

	def recipe_costs( self ):
		self.write('6\n')

		self.read(delim='\n', expect='Recipe Costs:\n')

		for i in range(len(self.recipes)):
			if self.recipes[i] == []:
				continue

			total = ct.c_double(0.0)

			for ing in self.recipes[i][1]:
				a = ct.c_double( float(ing[2]))
				b = ct.c_double( float(ing[1]))

				t = ct.c_double( self.multiply( a, b))

				total = ct.c_double( self.add( total, t) )
 
			self.read(delim='\n', expect='\t%d) %s - $%.5f\n' %(i+1, self.recipes[i][0], total.value))

	def list_all( self ):
		self.write('4\n')

		for i in range( len(self.recipes)):
			if self.recipes[i] == []:
				continue

			self.read(delim='\n', expect='Index: %d\n' %(i+1))
			self.read(delim='\n', expect='Name: %s\n' %(self.recipes[i][0]))
			self.read(delim='\n', expect='Ingredients:\n')

			for ing in self.recipes[i][1]:
				self.read(delim='\n', expect='\t%.6f %s\t%s\n' %(float(ing[1]), ing[3], ing[0]))

			self.read(delim='\n', expect='\n')
			self.read(delim='\n', expect='Instructions:\n')

			for j in range(len(self.recipes[i][2])):
				self.read(delim='\n', expect='\t%d) %s\n' %(j+1, self.recipes[i][2][j]))

			self.read(delim='\n\n', expect='\n\n')

	def leave_recipe_menu( self ):
		self.write('7\n')
		self.read(delim='\n', expect='Leave\n')

	def create_pantry( self ):
		self.write('1\n')

		if self.pantry_count == 128:
			self.read(delim='\n', expect='[ERROR] Pantry List is full\n')
			return

		self.read(delim=': ', expect='Enter pantry name: ')

		## Low chance of entering a pantry that exists
		r = random.randint( 0, 100)

		if r < 2 and self.pantry_count > 0:
			i = 0
			while i < len(self.pantries):
				if self.pantries[i] != []:
					self.write( self.pantries[i][0] + '\n')
					self.read(delim='\n', expect='[ERROR] Pantry already exists with that name.\n')
					return
				i += 1


		pn = rs( random.randint( 8,14) )

		self.write(pn + '\n')

		count = random.randint( 5, 15 )

		i = []

		tr = self.ingredients[:]

		for _ in range( count ):
			r = random.choice( tr )

			tr.remove(r)

			amnt = str( random.random()*10)[:4]
			cost = str( random.random()*10)[:4]

			t = random.choice( ['oz', 'gram'])

			i.append([r, amnt, cost, t])

		for x in i:
			self.read(delim='\n', expect='Enter ingredient name or a \"done\" to quit.\n')
			self.read(delim=': ', expect=': ')
			self.write( x[0] + '\n')
			self.read(delim=': ', expect='Enter the amount: ')
			self.write( x[1] + '\n')
			self.read(delim=': ', expect='Enter the cost per unit: ')
			self.write( x[2] + '\n')
			self.read(delim=': ', expect='Enter the type (oz/gram):')
			self.write( x[3] + '\n')

			if x[3] == 'gram':
				x[3] = 'g'

		self.read(delim='\n', expect='Enter ingredient name or a \"done\" to quit.\n')
		self.read(delim=': ', expect=': ')
		self.write('done\n')

		self.pantry_count += 1

		for z in range( len(self.pantries) ):
			if self.pantries[z] == []:
				i.reverse()
				self.pantries[z] = [ pn, i]
				break

	def print_pantry( self ):

		if self.pantry_count == 0:
			self.create_pantry()
			self.depth -= 1
			self.pantry_menu()

		self.write( '3\n')

		self.read(delim=': ', expect='Pantry Index [1..128]: ')

		## randomly choose an invalid value
		r = random.randint(0, 100)

		if r < 2:
			if random.randint(0, 1) or self.pantry_count == 128:
				i = 0
				while self.pantries[i] != []:
					i += 1
				self.write( str(i + 1) + '\n')
				self.read(delim='\n', expect='[ERROR] Empty pantry: %d\n' %(i+1))
				return
			else:
				self.write( str(random.randint( 130, 150)) + '\n' )
				self.read(delim='\n', expect='[ERROR] Must be between 1 and 128\n')
				return

		if ( self.pantry_count <= 0 ):
			print "WHAT THE HELL: %d" %self.pantry_count

		r = random.randint( 1, self.pantry_count)
		i = 0

		while r:
			if self.pantries[i] != []:
				r -= 1

			if r:
				i += 1

		self.write( str(i + 1) + '\n')

		self.read(delim='\n', expect='Name: %s\n' %(self.pantries[i][0]))
		self.read(delim='\n', expect='Item:\n')

		for ing in self.pantries[i][1]:
			self.read(delim='\n', expect='\t%.6f %s\t%s\n' %(float(ing[1]), ing[3], ing[0]))

		self.read(delim='\n\n', expect='\n\n')

	def print_all_pantries(self):

		self.write('4\n')

		for i in range( len(self.pantries)):
			if self.pantries[i] == []:
				continue

			self.read(delim='\n', expect='Index: %d\n' %(i+1))

			self.read(delim='\n', expect='Name: %s\n' %(self.pantries[i][0]))
			self.read(delim='\n', expect='Item:\n')

			for ing in self.pantries[i][1]:
				self.read(delim='\n', expect='\t%.6f %s\t%s\n' %(float(ing[1]), ing[3], ing[0]))

			self.read(delim='\n\n', expect='\n\n')

	def update_pantry( self ):
		if self.pantry_count == 0:
			count = random.randint( 1,2)

			for _ in range(count):
				self.create_pantry()
				self.depth -= 1
				self.pantry_menu()


		self.write('5\n')

		for i in range( len(self.pantries)):
			if self.pantries[i] == []:
				continue

			self.read(delim='\n', expect='Index: %d\n' %(i+1))

			self.read(delim='\n', expect='Name: %s\n' %(self.pantries[i][0]))
			self.read(delim='\n', expect='Item:\n')

			for ing in self.pantries[i][1]:
				self.read(delim='\n', expect='\t%.6f %s\t%s\n' %(float(ing[1]), ing[3], ing[0]))

			self.read(delim='\n\n', expect='\n\n')

		self.read( delim=': ', expect='Pantry Index [1..128]: ')

		r = random.randint( 1, self.pantry_count)
		i = 0

		while r:
			if self.pantries[i] != []:
				r -= 1

			if r:
				i += 1

		self.write( str(i+1) + '\n')

		self.read(delim='\n', expect='Name: %s\n' %(self.pantries[i][0]))
		self.read(delim='\n', expect='Item:\n')

		for ing in self.pantries[i][1]:
			self.read(delim='\n', expect='\t%.6f %s\t%s\n' %(float(ing[1]), ing[3], ing[0]))

		self.read(delim='\n\n', expect='\n\n')

		self.read(delim=': ', expect='Which item to update: ')

		z = random.choice( self.pantries[i][1])

		self.write( z[0] + '\n')
		self.read(delim=': ', expect='Enter the amount: ')

		na = str( random.random()*10)[:4]
		self.write( na + '\n')

		z[1] = na

		nt = random.choice( ['oz', 'gram'] )

		self.read(delim=': ', expect='Enter the type (oz/gram): ')
		self.write( nt + '\n')

		if nt == 'gram':
			nt = 'g'

		z[3] = nt

	def pantry_menu(self):

		self.depth += 1

		self.read(delim='\n', expect='1) Create Pantry\n')
		self.read(delim='\n', expect='2) Delete Pantry\n')
		self.read(delim='\n', expect='3) Print Pantry\n')
		self.read(delim='\n', expect='4) Print All Pantries\n')
		self.read(delim='\n', expect='5) Update Pantry\n')
		self.read(delim='\n', expect='6) Leave Menu\n')
		self.read(delim=' ', expect='-> ')

		if self.depth > self.max_depth:
			self.write( '6\n')
			self.read(delim='-> ')
			self.write('4\n')
			self.read(delim='\n')
			return -1

	def pantry(self):
		self.write('2\n')
	
	def leave_pantry(self):
		self.write( '6\n')
		self.read(delim='\n', expect='Leave.\n')

	def query( self ):
		self.write('3\n')

	def print_cheapest( self ):
		self.write( '3\n')

		i = 0
		cheapest_index = 0
		cheapest_value = 0.0

		for i in range(len(self.recipes)):
			if self.recipes[i] == []:
				continue

			total = ct.c_double(0.0)

			for ing in self.recipes[i][1]:
				a = ct.c_double( float(ing[2]))
				b = ct.c_double( float(ing[1]))

				t = ct.c_double( self.multiply( a, b))

				total = ct.c_double( self.add( total, t) )

			if cheapest_index == 0:
				cheapest_index = i+1
				cheapest_value = total.value
			elif total.value < cheapest_value:
				cheapest_value = total.value
				cheapest_index = i + 1


		if cheapest_index == 0:
			self.read(delim='\n', expect='No cheapest recipe found\n')
		else:
			self.read(delim='\n', expect='Cheapest: %d at %f\n' %(cheapest_index, cheapest_value))

	def print_expensivest( self ):
		self.write( '4\n')

		i = 0
		expensivest_index = 0
		expensivest_value = 0.0

		for i in range(len(self.recipes)):
			if self.recipes[i] == []:
				continue

			total = ct.c_double(0.0)

			for ing in self.recipes[i][1]:
				a = ct.c_double( float(ing[2]))
				b = ct.c_double( float(ing[1]))

				t = ct.c_double( self.multiply( a, b))

				total = ct.c_double( self.add( total, t) )

			if expensivest_index == 0:
				expensivest_index = i+1
				expensivest_value = total.value
			elif expensivest_value < total.value:
				expensivest_value = total.value
				expensivest_index = i + 1


		if expensivest_index == 0:
			self.read(delim='\n', expect='The most expensive recipe was not found\n')
		else:
			self.read(delim='\n', expect='Most expensive: %d at %f\n' %(expensivest_index, expensivest_value))

	def query_menu( self ):
		self.depth += 1

		self.read(delim='\n', expect='1) List Doable Recipes by Pantry\n')
		self.read(delim='\n', expect='2) List Doable Recipes by Cost\n')
		self.read(delim='\n', expect='3) Print Cheapest Recipe\n')
		self.read(delim='\n', expect='4) Print Most Expensive Recipe\n')
		self.read(delim='\n', expect='5) Leave Menu\n')
		self.read(delim='> ', expect='-> ')

		if self.depth > self.max_depth:
			self.write( '5\n')
			self.read(delim='-> ')
			self.write('4\n')
			self.read(delim='\n')
			return -1

	def query_by_pantry(self):

		## If there are no pantries then create a few
		if self.pantry_count == 0:
			self.leave_query()
			self.depth -= 1
			self.menu()
			self.pantry()
			self.depth -= 1
			self.pantry_menu()

			for _ in range( 1, 2):
				self.create_pantry()
				self.depth -= 1
				self.pantry_menu()

			self.leave_pantry()
			self.depth -= 1
			self.menu()
			self.query()
			self.depth -= 1
			self.query_menu()

		## If there are no recipes then create a few
		if self.recipe_count == 0:
			self.leave_query()
			self.depth -= 1
			self.menu()
			self.recipe()
			self.depth -= 1
			self.recipe_menu()

			for _ in range( 2, 3):
				self.add_recipe()
				self.depth -= 1
				self.recipe_menu()

			self.leave_recipe_menu()
			self.depth -= 1
			self.menu()
			self.query()
			self.depth -= 1
			self.query_menu()

		self.write( '1\n')
		self.read( delim='\n', expect='Select a pantry:\n')

		for i in range( len(self.pantries) ):
			if self.pantries[i] == []:
				continue

			self.read(delim='\n', expect='%d) %s\n' %(i + 1, self.pantries[i][0]))

		self.read(delim='> ', expect='-> ')

		### Select a pantry
		r = random.randint( 1, self.pantry_count)

		i = 0

		while r:
			if self.pantries[i] != []:
				r -= 1

			if r:
				i += 1

		self.write( str(i+1) + '\n')

		pantry_list = self.pantries[i][1]

		## just generate a list of names
		nm = []
		co = []

		for x in pantry_list:
			nm.append(x[0])
			co.append(x[1])

		###
		for recipe_index in range( len(self.recipes)):
			if self.recipes[recipe_index] == []:
				continue

			ingredient_list = self.recipes[recipe_index][1]
			found = 1

			for x in ingredient_list:
				if x[0] not in nm:
					found = 0
					break
				elif co [ nm.index( x[0] ) ] < x[1]:
					found = 0
					break

			if found == 1:
				self.read(delim='\n', expect='You can make: %s\n' %(self.recipes[recipe_index][0]))


	def query_by_cost( self ):
		## If there are no recipes then create a few
		if self.recipe_count == 0:
			self.leave_query()
			self.menu()
			self.recipe()
			self.recipe_menu()

			for _ in range( 2, 3):
				self.add_recipe()
				self.recipe_menu()

			self.leave_recipe_menu()
			self.menu()
			self.query()
			self.query_menu()



		self.write('2\n')
		self.read(delim=': ', expect='How much can you spend: ')

		amnt = str( random.random()*random.randint(1000, 5000))[:4]

		self.write( amnt + '\n')

		self.read( delim='\n', expect="You can make: \n")

		for i in range(len(self.recipes)):
			if self.recipes[i] == []:
				continue

			total = ct.c_double(0.0)

			for ing in self.recipes[i][1]:
				a = ct.c_double( float(ing[2]))
				b = ct.c_double( float(ing[1]))

				t = ct.c_double( self.multiply( a, b))

				total = ct.c_double( self.add( total, t) )
 
 			if total.value <= float(amnt):
 				self.read(delim='\n', expect='\t%d) %s\n' %(i+1, self.recipes[i][0]))

	def leave_query(self):
		self.write( '5\n')
		self.read(delim='\n', expect='Leaving..\n')

	def end(self):
		self.write('4\n')
		self.read(delim='\n', expect='Quit\n')

