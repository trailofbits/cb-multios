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
from array import array
from common import ERRORS, DEBUG

class Results(object):

	def __init__(self):
		self.object_id = 0
		self.receptacle_id = array('I', [0, 0, 0, 0, 0, 0, 0, 0])
		self.receptacle_ids_assigned_count = 0

	def get_object_id(self):
		return self.object_id

	def set_object_id(self, o_id):
		self.object_id = o_id

	def get_receptacle_ids_assigned_count(self):
		return self.receptacle_ids_assigned_count

	def get_receptacle_id_list(self):
		return self.receptacle_id

	def set_next_receptacle_id(self, r_id):
		self.receptacle_id[self.get_receptacle_ids_assigned_count()] = r_id
		self.receptacle_ids_assigned_count += 1

	def set_next_receptacle_id_from_list(self, r_id_list):
		for r_id in r_id_list:
			self.set_next_receptacle_id(r_id)

