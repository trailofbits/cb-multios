#!/usr/bin/env python

from generator.actions import Actions
import random
import string
from struct import pack, unpack

class CromuAll(Actions):

    def start(self):
        pass

    def menu(self):
        self.read( delim=': ', expect=': ' )

    def sort(self):
        item_count = random.randint( 0, 64 )

        self.write( ("sort %d" % item_count) + '\n' )

        if item_count == 0:
            self.read( delim='\n', expect='0 items sorted.\n' )

            return
        else:
            self.read( delim='\n', expect=("Enter %d items to sort:\n" % item_count) )

        idx = 0
        sortList = list()
        while idx < item_count:
            new_value = random.randint( -100000, 100000 )

            self.write( ("%d\n" % new_value) )

            sortList.append( new_value )

            idx += 1

        sortList.sort()

        self.read( delim='\n', expect=("%d items sorted.\n" % item_count) )

        idx = 0
        while idx < item_count:
            self.read( delim='\n', expect=("%d\n" % sortList[idx]) )

            idx += 1

    def list(self):
        self.write('?\n')
        self.read( delim='\n', expect='Available commands:\n' )
        self.read( delim='\n', expect='sort - This command sorts integers.\n' )
        self.read( delim='\n', expect='matrix - This command performs matrix math.\n' )
        self.read( delim='\n', expect='simon - This command plays a game like Simon Says.')
        self.read( delim='\n', expect='encode - This command encodes data.')

    def exit(self):
        self.write('exit\n')

#
# Matrix command
#
    def matrix(self):
        self.write("matrix\n")
	self.matrix_readmenu()
        operation = random.randint( 1, 4 )
 	if operation == 1:
            self.matrix_add()
	    self.matrix_readmenu()
            self.matrix_return()
 	elif operation == 2:
            self.matrix_sub()
	    self.matrix_readmenu()
            self.matrix_return()
 	elif operation == 3:
            self.matrix_smul()
	    self.matrix_readmenu()
            self.matrix_return()
 	elif operation == 4:
            self.matrix_return()

    def matrix_readmenu(self):
        self.read( delim='\n', expect='Matrix Calculator')
        self.read( delim='\n', expect='1. Add two matrices')
        self.read( delim='\n', expect='2. Subtract two matrices')
        self.read( delim='\n', expect='3. Scalar multiply a matrix')
        self.read( delim='\n', expect='4. Return to main menu')
        self.read( delim=': ', expect='Choice: ')
	
    def matrix_new(self, x, y):
	m = [[random.randint(1,1000) for i in range(y)] for j in range(x)]
	return m

    def matrix_write(self, m, X, Y):
        for x in range(X):
            for y in range(Y):
                self.read(delim=': ', expect=('%d,%d: ' % (x,y)))
                self.write('%d\n' % (m[x][y]))
        
    def matrix_read(self, result):
        self.read(delim='\n', expect='Result')
        for row in result:
            out = ' '.join(str(i) for i in row)
            out += ' \n'
            self.read(delim='\n', expect=out)
        
    def matrix_add(self):
        self.write('1\n')
        self.read( delim='\n', expect='First matrix')

        # enter the matrix dimensions
        self.read( delim='\n', expect='Provide the matrix dimensions')
	X = random.randint(0, 25)
        self.read( delim=': ', expect='X: ')
        self.write(('%d' % X)+'\n')
	if X < 1 or X > 20:
		# invalid dimension
        	self.read( delim='\n', expect='invalid\n')
		return
	Y = random.randint(0, (255/X))
        self.read( delim=': ', expect='Y: ')
        self.write(('%d' % Y)+'\n')
	if Y < 1 or Y > 20:
		# invalid dimension
        	self.read( delim='\n', expect='invalid\n')
		return

	# enter the first matrix
	m1 = self.matrix_new(X,Y)
        self.read( delim='\n', expect='Enter the matrix values')
        self.matrix_write(m1, X, Y)
	
	# enter the second matrix
	m2 = self.matrix_new(X,Y)
        self.read( delim='\n', expect='Second matrix')
        self.read( delim='\n', expect='Enter the matrix values')
        self.matrix_write(m2, X, Y)
	
	# calculate the result
	result = self.matrix_new(X,Y)
        for x in range(X):
            for y in range(Y):
		result[x][y] = m1[x][y] + m2[x][y]
	
	# read the result from the CB
        self.matrix_read(result)

    def matrix_sub(self):
        self.write('2\n')
        self.read( delim='\n', expect='First matrix')

        # enter the matrix dimensions
        self.read( delim='\n', expect='Provide the matrix dimensions')
	X = random.randint(0, 25)
        self.read( delim=': ', expect='X: ')
        self.write(('%d' % X)+'\n')
	if X < 1 or X > 20:
		# invalid dimension
        	self.read( delim='\n', expect='invalid\n')
		return
	Y = random.randint(0, (255/X))
        self.read( delim=': ', expect='Y: ')
        self.write(('%d' % Y)+'\n')
	if Y < 1 or Y > 20:
		# invalid dimension
        	self.read( delim='\n', expect='invalid\n')
		return

	# enter the first matrix
	m1 = self.matrix_new(X,Y)
        self.read( delim='\n', expect='Enter the matrix values')
        self.matrix_write(m1, X, Y)
	
	# enter the second matrix
	m2 = self.matrix_new(X,Y)
        self.read( delim='\n', expect='Second matrix')
        self.read( delim='\n', expect='Enter the matrix values')
        self.matrix_write(m2, X, Y)
	
	# calculate the result
	result = self.matrix_new(X,Y)
        for x in range(X):
            for y in range(Y):
		result[x][y] = m1[x][y] - m2[x][y]
	
	# read the result from the CB
        self.matrix_read(result)

    def matrix_smul(self):
        self.write('3\n')

        # enter the matrix dimensions
        self.read( delim='\n', expect='Provide the matrix dimensions')
	X = random.randint(0, 25)
        self.read( delim=': ', expect='X: ')
        self.write(('%d' % X)+'\n')
	if X < 1 or X > 20:
		# invalid dimension
        	self.read( delim='\n', expect='invalid\n')
		return
	Y = random.randint(0, (255/X))
        self.read( delim=': ', expect='Y: ')
        self.write(('%d' % Y)+'\n')
	if Y < 1 or Y > 20:
		# invalid dimension
        	self.read( delim='\n', expect='invalid\n')
		return

	# enter the matrix
	m1 = self.matrix_new(X,Y)
        self.read( delim='\n', expect='Enter the matrix values')
        self.matrix_write(m1, X, Y)
	
	# enter the multiplier
        self.read( delim=': ', expect='Multiplier: ')
	multiplier = random.randint(1, 1000)
        self.write(('%d' % multiplier)+'\n')

	# calculate the result
	result = self.matrix_new(X,Y)
        for x in range(X):
            for y in range(Y):
		result[x][y] = m1[x][y] * multiplier
	
	# read the result from the CB
        self.matrix_read(result)

    def matrix_return(self):
        self.write('4\n')

#
# Simon command
#

    def simon(self):
        seed = ''.join(random.choice(string.ascii_letters) for _ in range(8))
        self.write("simon %s\n" % seed)
        self.play_simon(seed, 101)

    def simon_pov(self):
        seed = ''.join(random.choice(string.ascii_letters) for _ in range(8))
        self.write("simon %s\n" % seed)
        self.play_simon(seed, 256)

    def play_simon(self, seed, rounds):     
        prng = Prng()
        prng.sprng(unpack("Q", seed)[0])
        sequence = []
        color_nums = ['0', '1', '2', '3', '4', '5', '6']
        color_names = ["RED", "ORANGE", "YELLOW", "GREEN", "BLUE", "INDIGO", "VIOLET"]
        BREAK_ROUND = 100
        MAX_ROUNDS = 256
        DIFFERENCE = 20
        for rounds_played in range(rounds):
            if (rounds_played == BREAK_ROUND ):
                self.read(delim=':', expect="You're doing great! Continue?(y/n)")
                if (rounds == rounds_played + 1):
                    self.write("n\n")
                    self.read(delim='\n', expect="Good game")
                    return
                else:
                    self.write("y\n")

            sequence.append(prng.random_in_range(0,len(color_names) - 1))
            says = "Simon says: "
            for each in sequence:
                says += color_names[each] + ' '
            says += ':'
            self.read(delim='\n', expect=says)

            correct_rsp = ""
            for each in sequence:
                correct_rsp += color_nums[each]
            self.write(correct_rsp + '\n')
        self.read(delim='\n', expect="You Win!")


    def my_encode(self, data):

        encoder_values = [  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                            'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 
                            'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 
                            'y', 'z', '1', '2', '3', '4', '5', '6',
                            '7', '8', '9', '0', 'A', 'B', 'C', 'D',
                            'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                            'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                            'U', 'V', 'W', 'X', 'Y', 'Z', '-', '+'   ]


        output_data = []

        mod_len = len(data) % 3

        if mod_len == 1:
            data.append(chr(0))
            data.append(chr(0))
        elif mod_len == 2:
            data.append(chr(0))

        for i in xrange(0, len(data), 3):

            byteA = ord(data[i]) >> 2
            byteB = ((ord(data[i]) & 0x3) << 4) | (ord(data[i+1])>>4)
            byteC = ((ord(data[i+1]) & 0xf) <<2) | ((ord(data[i+2]) & 0xc0)>> 6)
            byteD = (ord(data[i+2]) & 0x3f)

            output_data.append( encoder_values[byteA])
            output_data.append( encoder_values[byteB])
            output_data.append( encoder_values[byteC])
            output_data.append( encoder_values[byteD])


        return output_data

    def encode(self):

        self.write("encode\n")

        self.read( delim='\n', expect = 'How many bytes of data:')

        data_len = random.randint(1, 1000)

        self.write('{}\n'.format(data_len))

        self.read( delim='\n', expect='Enter data to be encoded:')

        my_string = []

        for x in range(data_len):

            value = random.randint(1, 255)

            my_string.append(chr(value))

            #self.write(pack('c',chr(value)))

        self.write(my_string)
        
        output_data = self.my_encode(my_string)

        expect_string = output_data;

        self.read(delim='\n', expect = expect_string)


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


