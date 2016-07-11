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

	def start(self):
		
		starting_balance = 1000
		record_str = pack('HH', 0, starting_balance)
		self.write(record_str)

		dataset = {'sampleSize' : 0.0, 'mean' : 0.0, 'Q' : 0.0, 'variance' : 0.0, 'stdDev' : 0.0}
		for i in range(0, 500):
			while True:
				record = [random.normalvariate(50.0, 10), random.normalvariate(50.0, 10)]
				if (record[0] < 65000 and record[0] >= 1 and record[1] < 65000 and record[1] >= 1):
					break
			dataset['sampleSize'] += 1
			priceRelative = record[0]/record[1]
			oldMean = dataset['mean']
			dataset['mean'] = oldMean + (priceRelative - oldMean) / dataset['sampleSize']
			dataset['Q'] =  dataset['Q'] + (priceRelative - oldMean) * (priceRelative - dataset['mean'])
			dataset['variance'] = dataset['Q'] / dataset['sampleSize']
			dataset['stdDev'] = math.sqrt(dataset['variance'])
			record_str = pack('HH', int(record[0]), int(record[1]))
			self.write(record_str)

		for i in range(0,500):
			minRange = dataset['mean'] + dataset['stdDev']*2
			maxRange = dataset['mean'] + dataset['stdDev']*3
			priceRelative = random.uniform(minRange, maxRange)
			firstStock = random.uniform(40.0, 50.0)
			secondStock = firstStock/priceRelative - .1
			record = [firstStock, secondStock]
			dataset['sampleSize'] += 1
			oldMean = dataset['mean']
			dataset['Q'] =  dataset['Q'] + (priceRelative - oldMean) * (priceRelative - dataset['mean'])
			dataset['variance'] = dataset['Q'] / dataset['sampleSize']
			dataset['stdDev'] = math.sqrt(dataset['variance'])
			record_str = pack('HH', record[0], record[1])
			self.write(record_str)

		for i in range(0,500):
			minRange = dataset['mean'] + dataset['stdDev']
			maxRange = dataset['mean'] + dataset['stdDev']*2
			priceRelative = random.uniform(minRange, maxRange)
			firstStock = random.uniform(40.0, 50.0)
			secondStock = firstStock/priceRelative - .1
			record = [secondStock, firstStock]
			dataset['sampleSize'] += 1
			oldMean = dataset['mean']
			dataset['Q'] =  dataset['Q'] + (priceRelative - oldMean) * (priceRelative - dataset['mean'])
			dataset['variance'] = dataset['Q'] / dataset['sampleSize']
			dataset['stdDev'] = math.sqrt(dataset['variance'])
			record_str = pack('HH', record[0], record[1])
			self.write(record_str)

		record_str = pack('hh', -1, -1)
		self.write(record_str)
		self.read(delim="\n", expect="You doubled your money!")


	def quit(self):
		pass
