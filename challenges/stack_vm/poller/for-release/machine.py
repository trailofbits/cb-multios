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

class TemplateGenerator(Actions):

	def start(self):
		self.state['programs'] = list()
		self.state['program_num'] = 0
		pass

	def new_program(self):
		if(self.state['program_num'] < 10):
			self.write("program" + "\x07")
			self.state['starting_lines'] = random.randint(20, 320)
			self.state['lines'] = self.state['starting_lines']
			self.state['prints'] = list()
			self.state['stack'] = list()
			self._size()
			self._push_cmd()
			for i in range(0, self.state['lines']):
				command = random.randint(1,5)
				if(command == 1):
					self._push_cmd()
				if(command == 2):
					self._pop_cmd()
				if(command == 3):
					self._add_cmd()
				if(command == 4):
					self._print_cmd()
				if(command == 5):
					self._copy_cmd()
			self.state['programs'].insert(self.state['program_num'], self.state['prints'])
			self.state['program_num']+=1
		else:
			self.quit()

	def execute_program(self):
		if(self.state['program_num'] > 0):
			program_num = random.randint(0,self.state['program_num']-1)
			self.write("execute" + str(program_num) + "\x07")
			for i in self.state['programs'][program_num]:
				self.read(delim="\n", expect=str(i))

	def _size(self):
		self.write("size" + str(self.state['lines']) + "\x07")

	def _push_cmd(self):
		a = random.randint(1,9999)
		self.state['stack'].insert(0,a)
		self.write("push" + str(a) + "\x07")
		self.state['lines']-=1

	def _pop_cmd(self):
		if(len(self.state['stack']) >= 1):
			self.state['stack'].pop(0)
			self.write("pop" + "\x07")
			self.state['lines']-=1
		else:
			self._push_cmd()


	def _add_cmd(self):
		if(len(self.state['stack']) >= 2):
			a = self.state['stack'].pop(0)
			b = self.state['stack'].pop(0)
			c_str = str(a+b)
			c = int(c_str[:8])
			self.state['stack'].insert(0, c)
			self.write("add" + "\x07")
			self.state['lines']-=1
		else:
			self._push_cmd()

	def _print_cmd(self):
		if(len(self.state['stack']) >= 1):
			a = self.state['stack'].pop(0)
			self.state['prints'].append(a)
			self.write("print" + "\x07")
			self.state['lines']-=1
		else:
			self._push_cmd()

	def _copy_cmd(self):
		if(len(self.state['stack']) >= 1):
			available_stack_space = self.state['starting_lines']*16 - len(self.state['stack']) - self.state['lines']
			if(available_stack_space > 0):
				a = self.state['stack'].pop(0)
				copy_num = random.randint(1, available_stack_space)
				for i in range(0,copy_num):
					self.state['stack'].insert(0,a)
				self.write("copy" + str(copy_num) + "\x07")
				self.state['lines']-=1
		else:
			self._push_cmd()


	def quit(self):
		return -1
