#!/usr/bin/env python

from generator.actions import Actions, Variable
import random
import string
import struct
import re

class MathGame(Actions):

 	operator_list = ['+', '-', '*', '/']
 	MAXINT = 0x7fffffff
 	FAIL = 0
 	SUCCESS = 1
 	PI = 3

	def start(self):
		self.read(delim="\n", expect="Enter some data")
		#write up to 255 bytes of random data (not null)
		data = ''.join(chr(random.randint(ord('!'),ord('~'))) for _ in range(random.randint(1,254)))
		self.write(data)
	
		self.rand = Prng()
		seed = 0xffffffffffffffffL
		for p in range(len(data)):
			seed = ((((seed << 4) & 0xffffffffffffffffL)| ((seed >> 60)& 0xffffffffffffffffL))) ^ ((struct.unpack("<b", data[p])[0])&0xff)
		self.rand.sprng(seed & 0xffffffffffffffffL) 
		
		self.state['solveEquation'] = 0
		self.state['createEquation'] = 0
		self.state['solveArea'] = 0
		self.state['solvePerimeter'] = 0
		self.state['solveVolume'] = 0
		self.state['viewStatistics'] = 0

		self.state['solveEquation_correct'] = 0
		self.state['createEquation_correct'] = 0
		self.state['solveArea_correct'] = 0
		self.state['solvePerimeter_correct'] = 0
		self.state['solveVolume_correct'] = 0

		self.op_stack = []
		self.num_stack = []

	def mainMenu(self):
		self.read(delim='Equation\n', expect="1. Solve Equation")
		self.read(delim='Equation\n', expect="2. Create Equation")
		self.read(delim='Area\n', expect="3. Solve Area")
		self.read(delim='Perimeter\n', expect="4. Solve Perimeter")
		self.read(delim='Volume\n', expect="5. Solve Volume")
		self.read(delim='Statistics\n', expect="6. View Statistics")
		self.read(delim='Exit\n', expect="7. Exit")

	def generate_one_equation(self):
		answer = 0
		valid_equation = False
		while (valid_equation == False):
			last_op = ''
			last_num = 1
			num_ops = self.rand.random_in_range(4, 15)
			num_nums = num_ops + 1
			num_parens = self.rand.random_in_range(0, num_ops)
		
			equation = ''
			opening_parens_inserted = 0
			closing_parens_inserted = 0
			cur_num = 0

			while cur_num < num_nums:
				# Add a number
				if ((cur_num < num_nums/2) and (opening_parens_inserted < num_parens)):
					equation += '('
					opening_parens_inserted += 1
				num = self.rand.random_in_range(1,256)
				if (last_op == '/'):
					num = self.rand.random_in_range(1,last_num)
				last_num = num
				equation += str(num)
				if ((cur_num + 1 > num_nums/2) and (closing_parens_inserted < opening_parens_inserted)):
					equation += ')'
					closing_parens_inserted += 1
				cur_num += 1
				if cur_num != num_nums:
					# Add an operator
					last_op = self.operator_list[self.rand.random_in_range(0,3)]
					equation += last_op

			equation += ')' * (opening_parens_inserted - closing_parens_inserted)
			(solve_ret, answer) = self.solve(equation)
			#print "equation: {} = {} [{}]".format(equation, answer, solve_ret)
			if ((solve_ret == self.SUCCESS) and (answer != 0)):
				valid_equation = True
				
		return (equation, answer)
		
	def evaluate(self, b, op, a):
		ret = self.FAIL
		answer = 0
		if (op == '+'):
			if (not((a > 0 and b > self.MAXINT - a) or
				(a < 0 and b < (-1*self.MAXINT) - a))):
				ret = self.SUCCESS
			answer = a + b
		if (op == '-'):
			if not(((a > 0 and b < (-1*self.MAXINT) + a) or
			(a < 0 and b > self.MAXINT + a))):
				ret = self.SUCCESS
			answer = a - b
		if (op == '*'):
			answer = a * b
			if not((answer > self.MAXINT) or (answer< -1*self.MAXINT)):
				ret = self.SUCCESS
		if (op == '/'):
			if not(b==0):
				ret = self.SUCCESS
				answer = int(float(a)/b)
		#print "evaluate: {} {} {} = {} [{}] {} {}".format(a, op, b, answer, ret, self.num_stack, self.op_stack)
		return (ret, answer)

	def satisfy_paren(self):
		ret = self.SUCCESS
		while (len(self.op_stack)>0 and self.op_stack[len(self.op_stack)-1] != '('):
			if (len(self.num_stack) < 2):
				ret = self.FAIL
				break
			(eval_ret, eval_answer) = self.evaluate(self.num_stack.pop(), self.op_stack.pop(), self.num_stack.pop())
			if (eval_ret == self.FAIL):
				ret = self.FAIL
				break
			self.num_stack.append(eval_answer)
		if (len(self.op_stack)== 0):
			ret = self.FAIL
		if (self.op_stack[len(self.op_stack)-1]=='('):
			self.op_stack.pop()
		return ret


	def solve(self, equation):
		ret = self.SUCCESS
		self.num_stack = []
		self.op_stack = []
		for each in re.split("([-+/*()])", equation):
			if each.isdigit():
				self.num_stack.append(int(each))
			elif each == '(':
				self.op_stack.append(each)
			elif each == ')':
				if (self.satisfy_paren() == self.FAIL):
					ret = self.FAIL
					break
			elif ((each == '+') or (each == '-')):
				op_len = len(self.op_stack)
				while (op_len>0):
					last_op = self.op_stack[op_len-1]
				  	if (last_op == '+' or last_op == '-' or last_op == '*' or last_op == '/'):
				  		if (len(self.num_stack) < 2):
				  			ret = self.FAIL
				  			break
				  		(eval_ret, eval_answer) = self.evaluate(self.num_stack.pop(), self.op_stack.pop(), self.num_stack.pop())
				  		if (eval_ret != self.SUCCESS):
				  			ret = self.FAIL
				  			break
				  		self.num_stack.append(eval_answer)
				  		op_len = len(self.op_stack)
				  		continue
				  	else:
				  		break
				self.op_stack.append(each)
			elif ((each=='*' or each == '/')):
				op_len = len(self.op_stack)
				while (op_len>0):
					last_op = self.op_stack[op_len-1]
					if (last_op == '*' or last_op == '/'):
						if (len(self.num_stack)<2):
							ret = self.FAIL
							break
						(eval_ret, eval_answer) = self.evaluate(self.num_stack.pop(), self.op_stack.pop(), self.num_stack.pop())
						if (eval_ret != self.SUCCESS):
							ret = self.FAIL
							break
						self.num_stack.append(eval_answer)
						op_len = len(self.op_stack)
						continue
					else:
						break
				self.op_stack.append(each)

		if (ret == self.FAIL):
			return (ret, 0)

		while (len(self.op_stack)>0):
			if (len(self.num_stack)<2):
				ret = self.FAIL
				break
			(eval_ret, eval_answer) = self.evaluate(self.num_stack.pop(), self.op_stack.pop(), self.num_stack.pop())
			if (eval_ret == self.FAIL):
				ret = self.FAIL
				break
			self.num_stack.append(eval_answer)
		if (len(self.num_stack)<=0):
			return (self.FAIL, 0)
		return (ret, self.num_stack.pop())

	def solveEquation(self):
		self.write("1")

		(equation, answer) = self.generate_one_equation()
		self.read(delim="\n", expect="Equation: {}".format(equation))
		self.read(delim=": ", expect="gimme answer: ")

		# answer incorrectly
		r = random.randint(1,10)
		if r == 1:
			rstr = ''.join(random.choice(string.digits) for _ in range(random.randint(1,14)))
			self.write(rstr)
			self.read(delim="\n", expect="Incorrect answer")
			self.state['solveEquation'] += 1
			return
		elif r == 2:
			rstr = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1,14)))
			self.write(rstr)
			self.read(delim="\n", expect="incorrect item entered")
			self.read(delim="\n", expect="Bad input")
			self.state['solveEquation'] += 1
			return

		self.state['solveEquation']+=1


		if (self.chance(0.5)):
			self.write(str(0))
			self.read(delim='\n', expect="Incorrect answer")
		else:
			self.write(str(answer));
			self.read(delim='\n', expect="success!!")
			self.state['solveEquation_correct'] += 1


	def createEquation(self):
		self.write("2")


		self.read(delim="\n", expect="Enter .*", expect_format="pcre")
		self.read(delim="\n", expect="It must .*", expect_format="pcre")
		self.read(delim="\n", expect="and must .*", expect_format="pcre")

		r = random.randint(1,10)
		# if r == 3, create an incorrect equation. see below

		self.state['createEquation'] += 1
		goal_parens = self.rand.random_in_range(0,5)
		if r == 3:
			# make this equation slightly wrong, but keep the correct format
			goal_parens += 1
		goal_answer = self.rand.random_in_range(0,32768)
		goal_operator = self.operator_list[self.rand.random_in_range(0,3)]
		goal_num_list = []
		for i in range(4):
			goal_num_list.append(self.rand.random_in_range(1,256))

		equation = '(' * goal_parens
		
		equation += str(goal_num_list[0]) + goal_operator + str(goal_num_list[1])
		equation += "+" + str(goal_num_list[2]) + "+" + str(goal_num_list[3])
		equation += ')' * goal_parens
		(ret, answer) = self.solve(equation)
		if (goal_answer - answer > 0):
			equation += '+'  + str(goal_answer - answer)
		else:
			equation += '-' + str(answer - goal_answer)

		# throw some errors
		if r == 1:
			# incorrect number
			rstr = ''.join(random.choice(string.digits) for _ in range(random.randint(1,14)))
			self.write(rstr)
			self.read(delim="\n", expect=".*", expect_format="pcre")
			self.read(delim="\n", expect=".*", expect_format="pcre")
			return
		elif r == 2:
			# incorrect string
			rstr = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1,14)))
			self.write(rstr)
			self.read(delim="\n", expect=".*", expect_format="pcre")
			self.read(delim="\n", expect=".*", expect_format="pcre")
			return
		if r == 3:
			# slightly incorrect equation
			self.write(equation)
			self.read(delim='\n', expect=".*", expect_format="pcre")
			self.read(delim='\n', expect=".*", expect_format="pcre") # error string
		else:
			self.write(equation)
			self.state['createEquation_correct'] += 1
			self.read(delim='\n', expect="string is formatted correct")
			self.read(delim='\n', expect=equation + " does resolve to {}, good!".format(goal_answer))


	def solveArea(self):
		self.write("3")
		self.read(delim="\n", expect="find .*", expect_format="pcre")
		
		self.state['solveArea'] += 1
		self.state['solveArea_correct'] += 1

		which = self.rand.random_in_range(0,1)

		# normal check for area of shape
		if which == 0: # request_area()
			# select type of shape
			rnum = self.rand.random_in_range(0,2)
			# 0: circle
			if rnum == 0:
				radius = self.rand.random_in_range(0,15000)
				area = self.PI * radius * radius
				self.write("{}".format(area))

			# 1: rectangle
			if rnum == 1:
				side = self.rand.random_in_range(0,34567)
				base = self.rand.random_in_range(0,34567)
				area = side * base
				self.write("{}".format(area))

			# 2: square
			if rnum == 2:
				side = self.rand.random_in_range(0,34567)
				area = side * side
				self.write("{}".format(area))
		else: # requesting either area or other dimension
			# request_2d_area_dim()
			rnum = self.rand.random_in_range(0,1)
			# 0: circle
			if rnum == 0:
				radius = self.rand.random_in_range(0,15000)
				area = self.PI * radius * radius
				if self.rand.random_in_range(0,1) == 0:
					self.write("{}".format(area))
				else:
					self.write("{}".format(radius))

			# 1: rectangle
			if rnum == 1:
				side = self.rand.random_in_range(0,34567)
				base = self.rand.random_in_range(0,34567)
				area = side * base
				ran = self.rand.random_in_range(0,2)
				if ran == 0:
					self.write("{}".format(area))
				elif ran == 1:
					self.write("{}".format(side))
				elif ran == 2:
					self.write("{}".format(base))

		self.read(delim="\n", expect="you got it", expect_format="pcre")


	def solvePerimeter(self):
		self.write("4")
		self.read(delim="\n", expect="find .*", expect_format="pcre")
		
		self.state['solvePerimeter'] += 1
		self.state['solvePerimeter_correct'] += 1

		which = self.rand.random_in_range(676,677)

		# normal check for area of shape
		if which == 676: # request_perimeter()
			# select type of shape
			rnum = self.rand.random_in_range(0,2)
			
			# 0: circle
			if rnum == 0:
				PI = 3
				radius = self.rand.random_in_range(0,34567)
				peri = 2 * PI * radius
				self.write("{}".format(peri))

			# 1: rectangle
			if rnum == 1:
				side = self.rand.random_in_range(0,34567)
				base = self.rand.random_in_range(0,34567)
				peri = 2 * side + 2 * base
				self.write("{}".format(peri))

			# 2: multi-side
			if rnum == 2:
				num_sides = self.rand.random_in_range(0,1234)
				length_of_side = self.rand.random_in_range(0,34567)
				peri = num_sides * length_of_side
				self.write("{}".format(peri))
		else: # requesting either area or other dimension
			# request_2d_peri_dim()
			rnum = self.rand.random_in_range(0,2)
			PI = 3
			# 0: circle
			if rnum == 0:
				PI = 3
				radius = self.rand.random_in_range(0,34567)
				peri = 2 * PI * radius
				if self.rand.random_in_range(0,1) == 0:
					self.write("{}".format(peri))
				else:
					self.write("{}".format(radius))

			# 1: rectangle
			elif rnum == 1:
				side = self.rand.random_in_range(0,34567)
				base = self.rand.random_in_range(0,34567)
				peri = 2 * side + 2 * base
				ran = self.rand.random_in_range(0,2)
				if ran == 0:
					self.write("{}".format(peri))
				elif ran == 1:
					self.write("{}".format(side))
				elif ran == 2:
					self.write("{}".format(base))

			# 2: multi-sided
			elif rnum == 2:
				num_sides = self.rand.random_in_range(0,1234) 
				length_of_side = self.rand.random_in_range(0,34567)
				peri = num_sides * length_of_side
				ran = self.rand.random_in_range(0,2)
				if ran == 0:
					self.write("{}".format(peri))
				elif ran == 1:
					self.write("{}".format(num_sides))
				elif ran == 2:
					self.write("{}".format(length_of_side))

		self.read(delim="\n", expect="you got it", expect_format="pcre")

	def solveVolume(self):
		self.write("5")
		self.read(delim="\n", expect="find .*", expect_format="pcre")
		
		self.state['solveVolume'] += 1
		self.state['solveVolume_correct'] += 1

		which = self.rand.random_in_range(44,45)

		# normal check for area of shape
		if which == 45: # request_volume()
			# select type of shape
			rnum = self.rand.random_in_range(0,2)
			
			# 0: sphere
			if rnum == 0:
				radius = self.rand.random_in_range(0,430)
				vol = 4 * self.PI * (radius * radius * radius / 3)
				
				self.write("{}".format(vol))

			# 1: rectangular prism
			if rnum == 1:
				side = self.rand.random_in_range(0,1288)
				base = self.rand.random_in_range(0,1288)
				height = self.rand.random_in_range(0,1288)
				vol = side * base * height
				self.write("{}".format(vol))

			# 2: cube
			if rnum == 2:
				side = self.rand.random_in_range(0,1288)
				vol = side * side * side
				self.write("{}".format(vol))
		else: # requesting either area or other dimension
			# request_3d_dim_vol()
			rnum = self.rand.random_in_range(0,2)
			# 0: sphere
			if rnum == 0:
				radius = self.rand.random_in_range(0,430)
				vol = 4 * self.PI * (radius * radius * radius / 3)
				if self.rand.random_in_range(0,1) == 0:
					self.write("{}".format(vol))
				else:
					self.write("{}".format(radius))

			# 1: rectangular prism
			if rnum == 1:
				side = self.rand.random_in_range(0,1288)
				base = self.rand.random_in_range(0,1288)
				height = self.rand.random_in_range(0,1288)
				vol = side * base * height
				ran = self.rand.random_in_range(0,3)
				if ran == 0:
					self.write("{}".format(vol))
				elif ran == 1:
					self.write("{}".format(side))
				elif ran == 2:
					self.write("{}".format(base))
				elif ran == 3:
					self.write("{}".format(height))

			# 2: cube
			if rnum == 2:
				side = self.rand.random_in_range(0,1288)
				vol = side * side * side
				ran = self.rand.random_in_range(0,1)
				if ran == 0:
					self.write("{}".format(vol))
				elif ran == 1:
					self.write("{}".format(side))

		self.read(delim="\n", expect="you got it", expect_format="pcre")

	def printStats(self):

		self.write("6")
		total = Variable('totalwon')
		total.set_re("Total won: (\d+)")
		self.read(delim="\n", assign=total)
		self.read(delim="\n", expect="Total lost: \d+", expect_format='pcre')
		self.read(delim="\n", expect="Equations solved correctly: {}".format(self.state['solveEquation_correct']), expect_format='pcre')
		self.read(delim="\n", expect="Equations solved incorrectly: {}".format(self.state['solveEquation'] - self.state['solveEquation_correct']), expect_format='pcre')
		self.read(delim="\n", expect="Equations created correctly: {}".format(self.state['createEquation_correct']), expect_format='pcre')
		self.read(delim="\n", expect="Equations created incorrectly: {}".format(self.state['createEquation'] - self.state['createEquation_correct']), expect_format='pcre')
		self.read(delim="\n", expect="Solved perimeter problems {}".format(self.state['solvePerimeter_correct']), expect_format='pcre')
		self.read(delim="\n", expect="Unsolved perimeter problems {}".format(self.state['solvePerimeter'] - self.state['solvePerimeter_correct']), expect_format='pcre')
		self.read(delim="\n", expect="Solved volume problems {}".format(self.state['solveVolume_correct']), expect_format='pcre')
		self.read(delim="\n", expect="Unsolved volume problems {}".format(self.state['solveVolume'] - self.state['solveVolume_correct']), expect_format='pcre')
		self.read(delim="\n", expect="Solved area problems {}".format(self.state['solveArea_correct']), expect_format='pcre')
		self.read(delim="\n", expect="Unsolved area problems {}".format(self.state['solveArea'] - self.state['solveArea_correct']), expect_format='pcre')


	def exit(self):
		self.write("7")


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