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

from generator.actions import Actions
import string
import random
import itertools
import math
from struct import *

class TemplateGenerator(Actions):
	
	def _identityMap(self, message):
		return message

	def _constantMap(self, message):
		message[0] = 1
		return message

	def _absoluteValueMap(self, message):
		message = map(abs, message)
		return message

	def _modulusCoordinatesWithDimensions(self, message):
		#message[3] = message[3] % message[1]
		#message[4] = message[4] % message[2]

		message[3] = message[3] - int(float(message[3])/message[1]) * message[1]
		message[4] = message[4] - int(float(message[4])/message[2]) * message[2]

		return message


	def _subtractAverageOfMessage(self, message):
		message_sum = sum(message)
		message_len = len(message)

		if(message_sum < 0):
			message_average = (message_sum+(-message_sum % message_len)) // message_len
		else:
			message_average = message_sum // message_len

		message = map(lambda x: x - message_average, message)
		return message

	def start(self):
		perm_list = [(self._identityMap, self._constantMap, self._absoluteValueMap, self._modulusCoordinatesWithDimensions),
				(self._identityMap, self._constantMap, self._modulusCoordinatesWithDimensions, self._absoluteValueMap),
				(self._identityMap, self._absoluteValueMap, self._constantMap, self._modulusCoordinatesWithDimensions),
				(self._identityMap, self._absoluteValueMap, self._modulusCoordinatesWithDimensions, self._constantMap),
				(self._identityMap, self._modulusCoordinatesWithDimensions, self._constantMap, self._absoluteValueMap),
				(self._identityMap, self._modulusCoordinatesWithDimensions, self._absoluteValueMap, self._constantMap),
				(self._constantMap, self._identityMap, self._absoluteValueMap, self._modulusCoordinatesWithDimensions),
				(self._constantMap, self._identityMap, self._modulusCoordinatesWithDimensions, self._absoluteValueMap),
				(self._constantMap, self._absoluteValueMap, self._identityMap, self._modulusCoordinatesWithDimensions),
				(self._constantMap, self._absoluteValueMap, self._modulusCoordinatesWithDimensions, self._identityMap),
				(self._constantMap, self._modulusCoordinatesWithDimensions, self._identityMap, self._absoluteValueMap),
				(self._constantMap, self._modulusCoordinatesWithDimensions, self._absoluteValueMap, self._identityMap),
				(self._absoluteValueMap, self._constantMap, self._identityMap, self._modulusCoordinatesWithDimensions),
				(self._absoluteValueMap, self._constantMap, self._modulusCoordinatesWithDimensions, self._identityMap),
				(self._absoluteValueMap, self._identityMap, self._constantMap, self._modulusCoordinatesWithDimensions),
				(self._absoluteValueMap, self._identityMap, self._modulusCoordinatesWithDimensions, self._constantMap),
				(self._absoluteValueMap, self._modulusCoordinatesWithDimensions, self._identityMap, self._constantMap),
				(self._absoluteValueMap, self._modulusCoordinatesWithDimensions, self._constantMap, self._identityMap),
				(self._modulusCoordinatesWithDimensions, self._identityMap, self._constantMap, self._absoluteValueMap),
				(self._modulusCoordinatesWithDimensions, self._identityMap, self._absoluteValueMap, self._constantMap),
				(self._modulusCoordinatesWithDimensions, self._constantMap, self._identityMap, self._absoluteValueMap),
				(self._modulusCoordinatesWithDimensions, self._constantMap, self._absoluteValueMap, self._identityMap),
				(self._modulusCoordinatesWithDimensions, self._absoluteValueMap, self._identityMap, self._constantMap),
				(self._modulusCoordinatesWithDimensions, self._absoluteValueMap, self._constantMap, self._identityMap)]

		function_list = self._identityMap, self._constantMap, self._absoluteValueMap, self._modulusCoordinatesWithDimensions
		
		message_list = []
		for i in range(1, 40):
			index = random.randint(1,24)
			message_vals = [index, random.randint(1,100), random.randint(1,100), random.randint(1,1000), random.randint(1,1000)]
			#message_vals = [2, 18000, 18000, 17000, 17000]
			message_str = pack('hhhhh', message_vals[0], message_vals[1], message_vals[2], message_vals[3], message_vals[4])
			self.write(message_str)

			for y in range(0, len(perm_list[index-1])):
				message_vals = perm_list[index-1][y](message_vals)
		
			message_str = pack('hhhhh', message_vals[0], message_vals[1], message_vals[2], message_vals[3], message_vals[4])
			message_list.append(message_str)

		for m in range(0, len(message_list) - 4):
			self.read(message_list[m])


	def quit(self):
		pass
