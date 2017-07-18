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

from generator.actions import Actions, Variable
from random import choice, randint
from os.path import dirname, abspath, join
import sys


sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
import support as sp
from flow import TankSet
from common import CONFIG


class H2Flow(Actions):

	DEBUG = False
	DEBUG_ERR = DEBUG or False
	DEBUG_FUNC = DEBUG or False
	DEBUG_FUNC2 = DEBUG or False
	FAIL_CHANCE = 0.0001

	def start(self):
		self.state['s'] = TankSet(CONFIG['TANK_QTY'])
		expected = sp.pack_single_string("INFO: H2FLOW Service Ready.")
		self.read(length=len(expected), expect=expected)

	def _recv_error(self, error_name):
		expected = sp.pack_error(error_name)
		self.read(length=len(expected), expect=expected)
		if True == self.DEBUG_ERR:
			print('exiting due to {0}'.format(error_name))

	def _do_io(self):
		vcc = self.state['s'].get_valve_change_choices()
		tanks = self.state['s'].get_tanks()
		for idx in range(self.state['s'].count()):
			if True == self.DEBUG_FUNC:
				print "Tank{0} settings: {1}".format(idx, tanks[idx])
			expected = sp.pack_tank(tanks[idx])
			self.read(length=len(expected), expect=expected)

			valve_cmd = ''
			error_name = ''
			if self.chance(self.FAIL_CHANCE) and True == tanks[idx].is_end_of_life():
				valve_cmd = choice(['OPEN_VALVE', 'CLOSE_VALVE', 'SET_IN_SERVICE', 'SET_OUT_OF_SERVICE', 'SET_END_OF_LIFE'])
				error_name = 'ERR_END_OF_LIFE'
			elif self.chance(self.FAIL_CHANCE) and False == tanks[idx].is_end_of_life():
				valve_cmd = choice(['SET_END_OF_LIFE', 'SET_OUT_OF_SERVICE'])
			elif self.chance(self.FAIL_CHANCE):
				valve_cmd ='BAD'
				error_name = 'ERR_INVALID_VALVE_POS'
			else:
				valve_cmd = vcc[idx]

			if True == self.DEBUG_FUNC:
				print " Valve cmd selected: {0}".format(valve_cmd)

			msg = sp.pack_command(valve_cmd)
			self.write(msg)

			if 'OPEN_VALVE' == valve_cmd:
				tanks[idx].open_valve()
			elif 'CLOSE_VALVE' == valve_cmd:
				tanks[idx].close_valve()
			elif 'SET_IN_SERVICE' == valve_cmd:
				tanks[idx].set_in_service()
			elif 'SET_OUT_OF_SERVICE' == valve_cmd:
				tanks[idx].set_out_of_service()
				if True == self.DEBUG_FUNC2:
					print " SET_OUT_OF_SERVICE"
			elif 'SET_END_OF_LIFE' == valve_cmd:
				tanks[idx].set_end_of_life()
				if True == self.DEBUG_FUNC2:
					print " SET_END_OF_LIFE"

			if '' != error_name:
				self._recv_error(error_name)
				return -1

		return 0

	def rxtx(self):
		self.state['s'].update_drain_factors()

		if 0 > self._do_io():
			return -1

		if 0 > self.state['s'].update_water_levels():
			return -1

		if 0 > self.state['s'].check_levels():
			return -1
    

	def exit(self):
		pass

