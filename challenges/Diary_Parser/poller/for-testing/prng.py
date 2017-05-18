#!/usr/bin/python
# This is a python implementation of the xorshift1024* pseudo
# random number generator for use by the poller
# When seeded with the same value, it will produce identical 
# results to the c implementation

import numpy as np
import pdb

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

if __name__=="__main__":
	r = Prng()
	r.sprng(1)
	print r.prng()
	print r.random_in_range(0, 10)
	print r.random_in_range(200,256)