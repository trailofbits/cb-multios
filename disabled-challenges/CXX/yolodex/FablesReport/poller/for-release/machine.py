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
import string
import random
import itertools
import math
from struct import *

class TemplateGenerator(Actions):

	def start(self):
		pass

	def newReport(self):
		#Release
		num_fields = random.randint(3,3)
		self.fields = []
		self.records = []
		self.record_length = 0
		for _ in range(num_fields):
			field_size = random.randint(10,20)
			random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(field_size))
			self.fields.insert(0,[self.record_length, field_size, random_field])
			self.record_length+= len(random_field)

		for field in reversed(self.fields[1:]):
			self.write(field[2] + ":")
		self.write(self.fields[0][2] + ";")

		#Vuln 1
		# num_fields = random.randint(2, 3)
		# self.fields = []
		# self.records = []
		# self.record_length = 0
		# for num in range(num_fields):
		# 	if num==num_fields-1:
		# 		field_size = 32768 - self.record_length
		# 	else:
		# 		field_size = random.randint(7,10)
		# 	random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(field_size))
		# 	self.fields.insert(0,[self.record_length, field_size, random_field])
		# 	self.record_length+= len(random_field)

		# for field in reversed(self.fields[1:]):
		# 	self.write(field[2] + ":")
		# self.write(self.fields[0][2] + ";")

		# Vuln 2
		# num_fields = random.randint(2, 3)
		# self.fields = []
		# self.records = []
		# self.record_length = 0
		# for num in range(num_fields):
		# 	if num==0:
		# 		field_size = 32768 + 32768 - 1024
		# 	elif num==1:
		# 		field_size = 2048
		# 	else:
		# 		field_size = random.randint(7,10)
		# 	random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(field_size))
		# 	self.fields.insert(0,[self.record_length, field_size, random_field])
		# 	self.record_length+= len(random_field)

		# for field in reversed(self.fields[1:]):
		# 	self.write(field[2] + ":")
		# self.write(self.fields[0][2] + ";")

		# Vuln 3
		# num_fields = random.randint(2, 3)
		# self.fields = []
		# self.records = []
		# self.record_length = 0
		# for num in range(num_fields):
		# 	if num==0:
		# 		field_size = 1024
		# 	elif num==1:
		# 		field_size = 32768 + 32768 - 1024
		# 	else:
		# 		field_size = random.randint(7,10)
		# 	random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(field_size))
		# 	self.fields.insert(0,[self.record_length, field_size, random_field])
		# 	self.record_length+= len(random_field)

		# for field in reversed(self.fields[1:]):
		# 	self.write(field[2] + ":")
		# self.write(self.fields[0][2] + ";")
		
	# Vuln 4
	# def newRecord(self):
	# 	random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(self.first_field_size))
	# 	self.write(random_field + ":")
	# 	self.write("ERROR")
	# 	self.write(";")

	# Vuln 3
	# def newRecord(self):
	# 	random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(self.first_field_size))
	# 	self.write(random_field + ":")
	# 	num = self.second_field_size
	# 	while(num >= 0):
	#  		random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(512))
	# 		num-=512
	# 		self.write(random_field)
	# 	self.write(";")

	# Vuln 2
	# def newRecord(self):
	# 	num = self.first_field_size
	# 	while(num >= 0):
	#  		random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(1024))
	# 		num-=512
	# 		self.write(random_field)
	# 	self.write(":")
	# 	random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(self.second_field_size))
	# 	self.write(random_field + ";")

	# Vuln 1
	# def newRecord(self):
	# 	random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(self.first_field_size))
	# 	self.write(random_field + ":")
	# 	num = self.second_field_size
	# 	while(num >= 0):
	# 		random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(1024))
	# 		num-=4096
	# 		self.write(random_field)
	# 	self.write(";")	

	# def errorRecord(self):
	# 	command = "ERROR"
	# 	random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(self.record_length))
	# 	while(random_field[0:3] == "END" or random_field[0:6] == "REPORT" or random_field[0:4] == "SORT"):
	# 		random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(self.record_length))
	# 	start = self.fields[0][0]
	# 	random_field = random_field[0:start] + "ERROR" + random_field[start+5:len(random_field)]
	# 	self.write(random_field)

	def newRecord(self):
		random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(self.record_length))
		while(random_field[0:3] == "END" or random_field[0:6] == "REPORT" or random_field[0:4] == "SORT"):
			random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(self.record_length))
		self.write(random_field)
		self.records.insert(0,random_field)

	def sendReport(self):
		command = "REPORT"
		random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(self.record_length-len(command)))
		self.write(command + random_field)
		for record in self.records:
			self.read(length=self.record_length, expect=record)

 	def sortReport(self):
 		command = "SORT"
 		field_num = random.randint(0,len(self.fields)-1)
 		field_num_str = pack('H', field_num)
		random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(self.record_length-len(command)-len(field_num_str)))
		self.write(command + field_num_str + random_field)
		start = self.fields[field_num][0]
		end = start + self.fields[field_num][1]
		self.records.sort(key=lambda x: x[start:end])


	def filterReport(self):
		command = "FREPORT"
		command = command + ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(self.fields[-1][1]-len(command)))
		self.write(command)
		bytes_written = len(command)
		num_filters = random.randint(1, len(self.fields)-1)
		filteredReport = []
		filter_string = ''
		random_field = ''
		for field in reversed(self.fields[0:num_filters]):
			filter_record = random.choice(self.records)
			start = field[0]
			end = start + field[1]
			filter_string = filter_string + filter_record[start:end]
			


		bytes_written += len(filter_string)
		if num_filters < len(self.fields)-1:
			random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(self.record_length-bytes_written))
			self.write(random_field)
		self.write(filter_string)

		temp_filter_string = "a"*len(command) + random_field + filter_string
		for record in self.records:
			for field in self.fields:
				start = field[0]
				end = start + field[1]
				if((record[start:end] == temp_filter_string[start:end]) and (record not in set(filteredReport))):
					filteredReport.insert(0, record)

		for record in filteredReport:
			self.read(length=self.record_length, expect=record)


	def quit(self):
		command = "END"
		random_field = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(self.record_length-len(command)))
		self.write(command + random_field)
		return -1
