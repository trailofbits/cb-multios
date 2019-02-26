#!/usr/bin/env python
#
# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

from random import randint, choice
from piprng import PiPrng
from common import DEBUG, CONFIG

PRNG = PiPrng()

class TankSet(object):

	def __init__(self, qty):
		PRNG.reset()
		self.tanks = self._gen_tanks(qty)

	def _gen_tanks(self, qty):
		t =[]
		for idx in range(qty):
			t.append(Tank(idx + 1, CONFIG['TANK_CAP']))
		return t

	def count(self):
		return len(self.tanks)

	def update_drain_factors(self):
		for tank in self.tanks:
			if False == tank.is_end_of_life() and True == tank.is_in_service():
				f = PRNG.get_next()
				if 0 == f % 2:
					tank.set_drain_rate(2 * f)
				else:
					tank.set_drain_rate(f)

	def update_water_levels(self):
		for tank in self.tanks:
			if False == tank.is_end_of_life():
				tank.do_drain()
				tank.do_fill()
		return 0

	def check_levels(self):
		for tank in self.tanks:
			if False == tank.is_end_of_life():
				if True == tank.is_crit_low_level():
					if True == DEBUG:
						print("Tank {0} level critically low {1}.".format(tank.get_id(), tank.get_level()))
					return -1
				if True == tank.is_low_level():
					if True == DEBUG:
						print("Tank {0} level is low {1}.".format(tank.get_id(), tank.get_level()))
					tank.add_water(1 + CONFIG['LOW_LEVEL'] - tank.get_level())
					if True == DEBUG:
						print(" Autofilled to {0}.".format(tank.get_level()))
		return 0

	def get_valve_change_choices(self):
		c = []
		for tank in self.tanks:
			if True == tank.is_end_of_life():
				c.append('NO_CHANGE')
			elif False == tank.is_in_service():
				c.append('SET_IN_SERVICE')
			# elif 200 < tank.get_level():
			# 	c.append('SET_END_OF_LIFE')
			# elif 27 > tank.get_level():
			# 	c.append('SET_OUT_OF_SERVICE')
			elif 30 > tank.get_level():
				c.append('OPEN_VALVE')
			elif 190 < tank.get_level():
				c.append('CLOSE_VALVE')
			else:
				c.append(choice(['OPEN_VALVE', 'CLOSE_VALVE', 'NO_CHANGE']))
		return c

	def get_tanks(self):
		return self.tanks

class Tank(object):

	CLOSED = 0
	OPEN = 1
	IN_SERVICE = 2
	OUT_OF_SERVICE = 6

	def __init__(self, tid, capacity):
		self.id = tid
		self.fill_rate = 0
		self.drain_rate = 0
		self.valve_position = self.CLOSED
		self.capacity = capacity
		self.level = 0
		self.status = self.OUT_OF_SERVICE
		self.eol = False
		self.contents = self._load_contents()

	def _load_contents(self):
		c = []
		for _ in range(CONFIG['INIT_LEVEL']):
			c.append(H2O())
			self.inc_level()
		return c

	def get_id(self):
		return self.id

	def get_fill_rate(self):
		return self.fill_rate

	def set_fill_rate(self, f):
		self.fill_rate = f

	def get_drain_rate(self):
		return self.drain_rate

	def set_drain_rate(self, dr):
		self.drain_rate = dr

	def get_valve_position(self):
		return self.valve_position

	def set_valve_position(self, vp):
		self.valve_position = vp

	def open_valve(self):
		self.set_valve_position(self.OPEN)

	def close_valve(self):
		self.set_valve_position(self.CLOSED)

	def get_capacity(self):
		return self.capacity

	def get_level(self):
		return self.level

	def inc_level(self):
		self.level = (self.level + 1) % 256

	def dec_level(self):
		self.level = (self.level - 1) % 256

	def get_status(self):
		return self.status

	def set_status(self, s):
		self.status = s

	def set_in_service(self):
		self.set_fill_rate(CONFIG['FILL_RATE'])
		self.set_status(self.IN_SERVICE)

	def set_out_of_service(self):
		self.set_fill_rate(0)
		self.set_drain_rate(0)
		self.set_status(self.OUT_OF_SERVICE)
		self.close_valve()

	def is_in_service(self):
		return self.IN_SERVICE == self.status

	def set_end_of_life(self):
		self.set_out_of_service()
		self.eol = True

	def is_end_of_life(self):
		return True == self.eol

	def is_low_level(self):
		if self.get_level() <= CONFIG['LOW_LEVEL']:
			return True
		else:
			return False

	def is_crit_low_level(self):
		if self.get_level() <= CONFIG['CRIT_LEVEL']:
			return True
		else:
			return False

	def add_water(self, qty):
		for _ in range(qty):
			self.contents.append(H2O())
			self.inc_level()

	def rm_water(self, qty):
		for _ in range(qty):
			if 0 < self.get_level():
				self.contents.pop()
				self.dec_level()

	def do_fill(self):
		if self.OPEN == self.get_valve_position() and self.IN_SERVICE == self.get_status():
			self.add_water(self.fill_rate)

	def do_drain(self):
		if self.IN_SERVICE == self.get_status():
			self.rm_water(self.drain_rate)

	def __str__(self):
		return "id:{0}, fill_rate:{1}, drain_rate:{2}, valve_position:{3}, capacity:{4}, level:{5}, status:{6}, eol:{7}".format(self.get_id(), self.get_fill_rate(), self.get_drain_rate(), self.get_valve_position(), self.get_capacity(), self.get_level(), self.get_status(), self.is_end_of_life())

	def __repr__(self):
		return self.__str__()


class H2O(object):

	def __init__(self):
		self.h2o = ['H', 'H', 'O']

	def __str__(self):
		return "({0}{1}{2})".format(self.h2o[0], self.h2o[1], self.h2o[2])

	def __repr__(self):
		return self.__str__()



