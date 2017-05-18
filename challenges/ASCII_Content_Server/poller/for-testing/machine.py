#!/usr/bin/env python
#
#
# Author: Debbie Nuttall <debbie@cromulence.co>
#
# Copyright (c) 2015 Cromulence LLC
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

import random
import pdb
import copy
import re
import struct
import string

class Tree():
	def __init__(self):
		self.root = {'name':'.', 'children':[], 'page':''}
		self.names = []

	def add_node(self, name, page):
		parts = name.split('.')
		if (self.find_node(name)):
			return 'ERROR: node already exists'
		if (name == ''):
			return 'ERROR: Name cannot be blank'
		tree = self.root['children']
		for i in range(len(parts)):
			node = None
			for node in tree:
				if node['name'] == parts[i]:
					tree = node['children']
					break
			if not node:
				# Children did not exist, make sure we are at the last part
				if (i != len(parts) - 1):
					return "ERROR: Parent node doesn't exist: %s" % ''.join(parts[0:i])
			else:
				# Children did exist, make sure match was found
				if node['name'] != parts[i]:
					# No match was found, see if parts remain in name
					if (len(parts) > 1 and i < len(parts) - 1):
						return "ERROR: Parent node doesn't exist: %s" % ''.join(parts[0:i])
	
				
		tree.append({'name':parts[i], 'children':[], 'page':page})
		self.names.append(name)

	def delete_node(self, name):
		# Make sure node exists
		node_to_delete = self.find_node(name)
		if not node_to_delete:
			return 'ERROR: Could not locate node for deletion'
		# Find parent node
		parts = name.split('.')
		parent = None
		if len(parts) == 1:
			parent = self.root['children']
		else:
			parts.pop()
			parent = self.root['children']
			for part in parts:
				node = None
				for node in parent:
					if node['name'] == part:
						parent = node['children']
						break
				if not node:
					return 'ERROR: Could not find parent node'
				if node['name'] != part:
					return 'ERROR: Could not find parent node'
		self.remove_names_recurse(name, node_to_delete)
		parent.remove(node_to_delete)

	def remove_names_recurse(self, qualified_name, node):
		for each in node['children']:
			self.remove_names_recurse('{}.{}'.format(qualified_name, each['name']), each)
		self.names.remove(qualified_name)

	def find_node(self, name):
		if not name:
			return None
		parts = name.split('.')
		tree = self.root['children']
		if not tree:
			return None
		for part in parts:
			node = None
			for node in tree:
				if node['name'] == part:
					tree = node['children']
					break
			if not node:
				return None
			if node['name'] != part:
				return None
		return node
	
	def generate_query(self, node):
		if not node:
			node = self.root
		output = []
		output.append(node['name'])
		for each in node['children']:
			self.generate_query_recurse(output, 1, each)
		return output

	def generate_query_recurse(self, output, indent, node):
		output.append('    ' * indent + node['name'])
		for each in node['children']:
			self.generate_query_recurse(output, indent + 1, each)

from generator.actions import Actions, Variable

class ACSPollGenerator(Actions):

	def start(self):
		self.tree = Tree()
		self.tree.add_node("Hello", "Hello, World!~n")
		self.tree.add_node("Hello.Name", "Hello, #name#!~n"
		                "This page outputs the value of a variable called name.~n"
		                "If the variable is not passed to the page (via the INTERACT method), it has no value and prints nothing.~n"),
		self.tree.add_node("Server", "The ACS Server responds to the following messages:~n"
		            "~tACS-0.1~[COMMAND~] (indicates no commands follow)~n"
		            "~tACS+0.1~[COMMAND~] (indicates another command follows)~n")
		self.tree.add_node("Server.Commands", "Commands all share the form:~n"
		              "~tCOMMAND:page_name:length:data~n"
		              "The Commands are REQUEST, QUERY, SEND, REMOVE, VISUALIZE, and INTERACT.~n")
		self.tree.add_node("Server.Commands.REQUEST", "The REQUEST command fetches a page.~n"
		                      "~t~[REQUEST:somepage::~]~n")
		self.tree.add_node("Server.Commands.QUERY", "The QUERY command retrieves a listing of the pages on the server.~n"
		                    "To retrieve the entire list of all pages:~n"
		                    "~t~[QUERY:::~]~n"
		                    "To retrieve a subset of the page tree:~n"
		                    "~t~[QUERY:somepage::~]~n")
		self.tree.add_node("Server.Commands.SEND", "Upload a page to the server~n"
		                    "~t~[SEND:newpage:length:pagedata~]~n")
		self.tree.add_node("Server.Commands.REMOVE", "Remove a page from the server~n"
		                      "~t~[REMOVE:pagename::~]~n")
		self.tree.add_node("Server.Commands.VISUALIZE", "Process and display page data without uploading it to the server~n"
		                        "~t~[VISUALIZE::length:pagedata~]~n")
		self.tree.add_node("Server.Commands.INTERACT", "Fetch a page from the server using variable substitution.~n"
		                        "~t~[INTERACT:pagename:length:variabledata~]~n"
		                        "~tvariabledata is in the form: ~[var:name:value~]~[var:name:value~]...~n")
		self.tree.add_node("AML", "ASCII Markup Language")
		self.tree.add_node("AML.Commands", "ASCII Markup Language uses the ~~ character as a command code~n"
		                  "~t~~n converts to newline~n"
		                  "~t~~t converts to tab~n")
		self.tree.add_node("AML.Literals", "AML uses certain characters as control codes~n"
		                  "Those characters can be inserted as literals using the escape character ~~~n"
		                  "~t~~~[ inserts left bracket~n"
		                  "~t~~~] inserts right bracket~n"
		                  "~t~~~~ inserts tilde~n"
		                  "~t~~~# inserts hash~n")
		self.tree.add_node("AML.Variables", "AML supports string variables.~n"
		                    "Variables are created within a script (see AML.Scripts)~n"
		                    "and referenced with this syntax:~n"
		                    "~t~#variable~#~n")  
		self.tree.add_node("AML.Scripts",  "AML supports additional commands within script tags ~[~]~n"
		                  "~t~[var:name:value~] - sets a variable~n"
		                  "~t~[line:character:length~] - insert a line of characters~n"
		                  "~t~[box:pagedata~] - put the page data inside a box outlined with *'s~n" )
		self.tree.add_node("AML.Examples", "AML examples~n")
		self.tree.add_node("AML.Examples.Line", "Draw some lines~n[line:X:80]~n"
		                      "[line:A:42]~n"
		                      "[line:B:1][line:C:2][line:*:100]~n"
		                      "[line:~:5][line:*:1][line:[:5]~n" )
		self.tree.add_node("AML.Examples.Variableset", "Set a variable [var:name:Sterling]~n"
		                              "Then get the variable: #name#~n" )
		self.tree.add_node("AML.Examples.ManyVariables", "[var:var0:value0][var:var1:value1][var:var2:value2][var:var3:value3][var:var4:value4][var:var5:value5][var:var6:value6][var:var7:value7][var:var8:value8][var:var9:value9]~n"
																											"#var0##var1##var2##var3##var4##var5##var6##var7##var8##var9#~n")
		self.tree.add_node("AML.Examples.Box", "Test putting some stuff in a box~n"
		                      "[box:Help, I'm trapped in a box!]~n"
		                      "[box:~nLine in a box[line:X:15]~n]")
		self.state['tree'] = self.tree


	def release(self):
		self.tree = self.state['tree']
		max_commands = random.randint(1, 10)
		num_commands = 0
		while (num_commands < max_commands):
			number = random.randint(1, 100)
			if number > 60:
				# 40% of the time request a random page
				name = random.choice(self.tree.names)
				self.request(name)
			elif number > 50:
				# 10% of the time query a random page
				name = random.choice(self.tree.names)
				self.query(name)
			elif number > 35:
				# 15% of the time send a new page
				name = random.choice(self.tree.names)
				node = self.tree.find_node(name)
				if not node:
					print "Node not found: %s" % name
				if not node['page']:
					print "page not found: %s" % name
				self.send(name + '_new', node['page'])

			elif number > 25:
				# 10% of the time remove a random page
				name = random.choice(self.tree.names)
				self.remove(name)
				# Don't let the tree go empty
				if not self.tree.names:
					self.send("Hello", "Here is the page data~n")
					self.send("Hello.there", "Welcome, #name!~n")
					self.send("Commands", "Now I'll test ~~ output~n")
					self.send("Commands.tab", "~t~ttab~n")

			elif number > 5:
				# 20% of the time visualize a page
				name = random.choice(self.tree.names)
				node = self.tree.find_node(name)
				if not node:
					print "Node not found: %s" % name
				if not node['page']:
					print "page not found: %s" % name
				self.visualize(node['page'])
			else:
			 	#5% of the time interact with a page,
			 	varlist = {'name': 'value'}
			 	name = random.choice(self.tree.names)
				self.interact(name, varlist)
			num_commands += 1
			

	def runtest(self):

		self.tree = self.state['tree']
		max_commands = random.randint(1, 10)
		num_commands = 0
		while (num_commands < max_commands):
			number = random.randint(1, 100)
			if number > 60:
				# 40% of the time request a random page
				if (self.chance(0.01)):
						name = ''.join(random.choice(string.letters) for _ in range(random.randint(1,63)))
				else:
					name = random.choice(self.tree.names)
				self.request(name)
			elif number > 50:
				# 10% of the time query a random page
				if (self.chance(0.01)):
					name = ''.join(random.choice(string.letters) for _ in range(random.randint(1,63)))
				else:
					name = random.choice(self.tree.names)
				self.query(name)
			elif number > 35:
				# 15% of the time send a new page
				if (self.chance(0.01)):
					name = ''.join(random.choice(string.letters) for _ in range(random.randint(1,63)))
					page = ''.join(random.choice(string.letters) for _ in range(random.randint(1,255)))
					self.send(name, page)
				else:
					name = random.choice(self.tree.names)
					node = self.tree.find_node(name)
					self.send(name + '_new', node['page'])

			elif number > 25:
				# 10% of the time remove a random page
				if (self.chance(0.01)):
					name = name = ''.join(random.choice(string.letters) for _ in range(random.randint(1,63)))
				else:
					name = random.choice(self.tree.names)
				self.remove(name)
				# Don't let the tree go empty
				if not self.tree.names:
					self.send("Hello", "Here is the page data~n")
					self.send("Hello.there", "Welcome, #name!~n")
					self.send("Commands", "Now I'll test ~~ output~n")
					self.send("Commands.tab", "~t~ttab~n")

			elif number > 5:
				# 20% of the time visualize a page
				if (self.chance(0.01)):
					page = ''.join(random.choice(string.letters) for _ in range(random.randint(1,255)))
					self.visualize(page)
				else:
					name = random.choice(self.tree.names)
					node = self.tree.find_node(name)
					self.visualize(node['page'])
			else:
				# 5% of the time interact with a page,
				value = ''.join(random.choice(string.letters) for _ in range(random.randint(1,63)))
				varlist = {'name':value}
				name = random.choice(self.tree.names)
				self.interact(name, varlist)
			num_commands += 1


	def pov1(self):
		for i in range(62):
			self.send('a' + '.'*i, 'pagedata')
			self.send('a' + '.'*i + 'p', 'pagedata')


	def exit(self):
		self.send_command('QUERY', more=False)
		query = self.tree.generate_query(None)
		for each in query:
			self.read(length=len(each)+1, expect=each+'\n')

	def send_command(self, command, name='', data=None, more=True):
		cmd = []
		cmd.append('ACS')
		cmd.append('+' if more else '-')
		cmd.append('0.1')
		if not data:
			cmd.append('[%s:%s::]' % (command, name))
		else:
			if self.chance(0.9):
				cmd.append('[%s:%s:%d:%s]' % (command, name, len(data), data))
			else:
				# Encode the data (compress by removing high bit from each byte)
				data = self.compress(data)
				data = struct.pack("<i", len(data)) + data
				cmd.append('[%s:%s:%d:%s]' % (command, name, -1, data))

		self.write(''.join(cmd))
		if len(name)>63:
			self.read(delim='\n', expect='ERROR: Receive command failed\n')

	def compress(self, data_in):
		data_out = []
		bytes_consumed = 0
		if (len(data_in)%8 != 0):
			data_in += '\x00'
		while (bytes_consumed < len(data_in) - 1):
			i = len(data_out) % 7
			packed_byte = (ord(data_in[bytes_consumed]) << (i + 1)) & 0xff | (((ord(data_in[bytes_consumed + 1])) >> (6 - i)) & 0x7f) 
			data_out.append(packed_byte)
			if (i == 6):
				bytes_consumed += 2
			else:
				bytes_consumed += 1
		out = []
		for each in data_out:
				out.append(str(hex(each)))

		return str(bytearray(data_out))

	def request(self, name):
		self.send_command('REQUEST', name)
		self.receive_page(name)

	def query(self, name):
		self.send_command('QUERY', name)
		if (name == ''):
			node = None
		else:
			node = self.tree.find_node(name)
			if not node:
				self.read(delim='\n', expect='ERROR: Tree not found: %s' % name)
				return
		query = self.tree.generate_query(node)
		for each in query:
			self.read(length=len(each)+1, expect=each+'\n')

	def send(self, name, page):
		self.send_command('SEND', name, page)
		ret = self.tree.add_node(name, page)
		if ret:
			self.read(delim='\n', expect=ret)
			self.read(delim='\n', expect='ERROR: Unable to upload page')
		else:
			self.read(delim='\n', expect='SUCCESS: Page uploaded to server')
			
	def remove(self, name):
		self.send_command('REMOVE', name)
		ret = self.tree.delete_node(name)
		if ret:
			self.read(delim='\n', expect=ret)
			self.read(delim='\n', expect='ERROR: Unable to delete page')
		else:
			self.read(delim='\n', expect='SUCCESS: Page deleted')

	def visualize(self, data):
		self.send_command('VISUALIZE', '', data)
		self.visualize_page(data, None)

	def interact(self, name, varlist):
		data = []
		for each in varlist.keys():
			data.append('[var:%s:%s]' % (each, varlist[each]))
		self.send_command('INTERACT', name, ''.join(data))
		page = self.tree.find_node(name)
		self.visualize_page(page['page'], varlist)


	def receive_page(self, name):
		page = self.tree.find_node(name)
		if not page:
			self.read(delim='\n', expect='Page not found: %s' % (name))
		else:
			self.visualize_page(page['page'], None)


	def output_char(self, c):
		self.line.append(c)
		self.line_length += 1
		if (self.in_a_box and self.line_length == 78):
			self.flush_output()
		elif self.line_length == 80:
			self.flush_output()

	def output_str(self, s):
		if (len(s) + self.line_length > 80):
			self.flush_output()
		if (len(s) > 80):
			self.read(length=len(s)+1, expect=s+'\n')
		else:
			self.line.append(s)
			self.line_length += len(s)
		
	def flush_output(self):
		line = ''.join(self.line)
		if self.in_a_box:
			while (len(line) < 79):
				line += ' '
			line += '*'
		self.read(length=len(line)+1, expect=line+'\n')
		self.line = []
		self.line_length = 0
		if self.in_a_box:
			self.line.append('* ')
			self.line_length += 2

	def visualize_page(self, data, override_list):
		self.vars = {}
		if not override_list:
			override_list = {}
		process_command_flag = False
		script_open_flag = False
		var_open_flag = False
		varname = []
		script = []
		self.line_length = 0
		self.line = []
		self.in_a_box = False
		for each in data:
			if var_open_flag:
				if each == '#':
					varname = ''.join(varname)
					if override_list.has_key(varname):
						self.output_str(override_list[varname])
					elif self.vars.has_key(varname):
						self.output_str(self.vars[varname])
					var_open_flag = False
				else:
					varname.append(each)
			elif script_open_flag:
				if each == ']':
					script_open_flag = False
					self.process_script(''.join(script))
				else:
					script.append(each)
				if (''.join(script) == 'box:'):	
					self.flush_output()
					self.in_a_box = True
					script_open_flag = False
					self.read(length=81, expect='*'*80 + '\n')
					self.line.append('* ')
					self.line_length += 2
			elif process_command_flag:
				process_command_flag = False
				if each == 't':
					for i in range(4):
						self.output_char(' ')
				elif each == 'n':
					self.flush_output()
				elif each == '[':
					self.output_char('[')
				elif each == ']':
					self.output_char(']')
				elif each == '~':
					self.output_char('~')
				elif each == '#':
					self.output_char('#')
				else:
					self.read(delim='\n', expect='ERROR: Invalid control code\n')
					self.read(delim='\n', expect='ERROR: Invalid syntax\n')
					return
			elif each == '~':
				process_command_flag = True
			elif each == '[':
				script_open_flag = True
				script = []
			elif each == '#':
					var_open_flag = True
					varname = []
			elif self.in_a_box and each == ']':
				if (self.line_length > 0):
					self.flush_output()
				self.read(length=81, expect='*'*80 + '\n')
				self.in_a_box = False
				self.line = []
				self.line_length = 0
			else:
				self.output_char(each)

		if (process_command_flag or script_open_flag 
			or var_open_flag or self.in_a_box):
			self.read(delim='\n', expect='ERROR: Invalid syntax')
		elif self.line:
			self.flush_output()
		
	def process_script(self, script):
		if script.startswith('line'):
			parts = script.split(':')
			char = parts[1]
			length = int(parts[2])
			for i in range(length):
				self.output_char(char)
		elif script.startswith('var'):
			parts = script.split(':')
			self.vars[parts[1]] = parts[2]



