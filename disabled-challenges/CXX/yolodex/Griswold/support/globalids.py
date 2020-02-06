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

class GlobalIdNums(object):

	def __init__(self):
		self.receptacle_id = 1
		self.light_string_id = 1
		self.splitter_id = 1
		self.outlet_id = 1

	def get_next_receptacle_id(self):
		self.receptacle_id += 1
		return self.receptacle_id - 1

	def get_current_receptacle_id(self):
		return self.receptacle_id

	def get_next_light_string_id(self):
		self.light_string_id += 1
		return self.light_string_id - 1

	def get_current_light_string_id(self):
		return self.light_string_id

	def get_next_splitter_id(self):
		self.splitter_id += 1
		return self.splitter_id - 1

	def get_current_splitter_id(self):
		return self.splitter_id

	def get_next_outlet_id(self):
		self.outlet_id += 1
		return self.outlet_id - 1

	def get_current_outlet_id(self):
		return self.outlet_id

