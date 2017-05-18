#!/usr/bin/env python
#
# Copyright (C) 2015 Narf Industries <info@narfindustries.com>
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

	def _initDocumentID(self):
		requestBits = [29, 7, 18, 17, 16, 14, 11, 6, 8, 15]
		self.docID = 1

		for c in range(10):
			if(ord(self.magic_page[c:c+1]) % requestBits[c] == 0):
				self.docID = self.docID * requestBits[c]

	def _readDocumentID(self):
		document_str = "Document ID: " + str(self.docID) + "\n"
		self.read(delim="\n", expect=document_str)
		self.docID += 1

	def _newText(self, calledby):
		text = '<text>\n'
		text_string = ''
		words = random.randint(3, 7)
		for _ in range(words):
			length = random.randint(2,7)
			text_string += ''.join(random.choice(string.ascii_letters) for _ in range(length))
			text_string += ' '
		text_string
		text += text_string + '\n'
		text += '</text>\n'
		if self.columnNum == 1 and calledby == 'page':
			text_string = '     ' + text_string
			num_lines = len(text_string) / (self.docWidth-4)

			if(len(text_string) % (self.docWidth-4) > 0):
				num_lines += 1

			for l in range(num_lines):
				text_regex  = text_string[(self.docWidth-4)*l:(self.docWidth-4)*l+(self.docWidth-4)] + '\s*' + '\n'
				self.regex_str += '(' + text_regex + '|\s[0-9]+\n[=]{' + str(self.docWidth) + '}\n' + text_regex + ')'

		return text

	def _newList(self, depth, calledby):
		list_str = '<list>\n'
		type_num = random.randint(1,5)
		if type_num < 5:
			list_str += '<type>\n'
			if type_num == 1:
				list_str += 'numeral\n'
			elif type_num == 2:
				list_str += 'ALPHA\n'
			elif type_num == 3:
				list_str += 'alpha\n'
			elif type_num == 4:
				list_str += 'roman\n'
			list_str += '</type>\n'

		elements = random.randint(3,5)
		for e in range(elements):
			list_str += '<element>\n'
			option = random.randint(1,50)
			list_str += '<text>\n'
			length = random.randint(3,6)
			element_str = ''.join(random.choice(string.ascii_letters) for _ in range(length))
			list_str += element_str
			list_str += '\n'
			list_str += '</text>\n'

			if self.columnNum == 1 and calledby == 'page':
				element_regex = '  ' * depth
				if type_num == 1:
					element_regex += str(e+1) + ". " + element_str + '\s*'
				elif type_num == 2:
					element_regex += chr(ord('A')+e) + ". " + element_str + '\s*'
				elif type_num == 3:
					element_regex += chr(ord('a')+e) + ". " + element_str + '\s*'
				elif type_num == 4:
					element_regex += '[IXVMDCL]+' + ". " + element_str + '\s*'
				else:
					element_regex += '\* ' + element_str + '\s*'

				num_lines = len(element_regex) / (self.docWidth-4) + 1
				for l in range(num_lines):
					self.regex_str += '(' + element_regex[(self.docWidth-4)*l:(self.docWidth-4)*l+(self.docWidth-4)] + '\n|\s[0-9]+\n[=]{' + str(self.docWidth) + '}\n' + element_regex[(self.docWidth-4)*l:(self.docWidth-4)*l+(self.docWidth-4)] + '\n)'

			if option % 43 == 0 and depth < 3:
				list_str += self._newList(depth+1, calledby)

			list_str += '</element>\n'

		list_str += '</list>\n'

		return list_str

	def _newTable(self, calledby):
		maxFields = (self.columnWidth - 1) / 3 - 1
		rows = random.randint(2, 4)
		fields = 0
		if(maxFields >= 1):
			if(maxFields > 4):
				fields = 4
			else:
				fields = random.randint(1, maxFields)
		else:
			return ""
		border = 2#random.randint(0,2)
		if(border > 1):
			border_type = 'star\n'
		else:
			border_type = 'line\n'

		table = '<table>\n'
		table += '<rows>\n'
		table += str(rows) + '\n'
		table += '</rows>\n'
		table += '<fields>\n'
		table += str(fields) + '\n'
		table += '</fields>\n'
		table += '<border>\n'
		table += border_type
		table += '</border>\n'
		table += '<row>\n'
		for _ in range(fields):
			table += '<header>\n'
			table += self._newText('table')
			table += '</header>\n'
		table += '</row>\n'
		for _ in range(rows-1):
			table += '<row>\n'
			for _ in range(fields):
				table += '<field>\n'
				table += '<pgraph>\n'
				option = random.randint(1,40)
				if(option != 23):
					table += self._newText('table')
				else:
					table += self._newList(0, 'table')
				table += '</pgraph>\n'
				table += '</field>\n'
			table += '</row>\n'
		table += '</table>\n'

		fieldWidth = (self.columnWidth - 1) / fields - 3;
		tableWidth = (fieldWidth + 3) * fields + 1;
		table_regex = ''
		if self.columnNum == 1 and calledby == 'page':
			if border == 2:
				line_regex = '(\*{' + str(tableWidth) + '}\s*\n|\s[0-9]+\n[=]{' + str(self.docWidth) + '}\n\*{' + str(tableWidth) + '}\s*\n' + ')'
				row_regex = ''
				for f in range(fields):
					row_regex += '\* .{' + str(fieldWidth) + '} '
				row_regex += '\*\s*\n'
				for _ in range(rows):
					table_regex += line_regex
					table_regex += '(' + row_regex + '|\s[0-9]+\n[=]{' + str(self.docWidth) + '}\n' + row_regex + ')*'
				table_regex += line_regex
		self.regex_str += table_regex
		return table

	def _newParagraph(self, calledby):
		paragraph = '<pgraph>\n'
		option = random.randint(1, 10)
		if(option % 2 == 0):
			paragraph += self._newText(calledby)
		elif(option % 3 == 0):
			paragraph += self._newList(0, calledby)
		else:
			table_str = self._newTable(calledby)
			if len(table_str) == 0:
				return ""
			else:
				paragraph += table_str
		paragraph += '</pgraph>\n'
		self.write(paragraph)
		return paragraph


	def _newPage(self):
		page = '<page>\n'
		self.write(page)
		numParagraphs = 3#random.randint(3,10)
		self.regex_str = ''
		for _ in range(numParagraphs):
			self._newParagraph('page')
			#if len(paragraph_str) == 0:
			#	return ""
			#else:
			#	page += paragraph_str
		page = '</page>\n'
		self.write(page)
		return page

	def _newDocument(self):
		document = "<document>\n"
		document += "<length>\n"
		document += str(self.docLength) + "\n"
		document += "</length>\n"
		document += "<width>\n"
		document += str(self.docWidth) + "\n"
		document += "</width>\n"
		self.write(document)
		numPages = random.randint(1,3)
		for _ in range(numPages):
			page_str = ''
			page_regex = '[=]{' + str(self.docWidth) + '}\n'
			page_str += "<column>\n"
			self.columnNum = random.randint(1,3)
			self.columnWidth = self.docWidth / self.columnNum - 4
			page_str += str(self.columnNum) + "\n"
			page_str += "</column>\n"
			self.write(page_str)
			self._newPage()
			#if len(page_str) == 0:
			#	return ""
			#else:
			#	document += page_str

			if self.columnNum == 1:
				page_regex += self.regex_str
			else:
				page_regex += '(\n|'
				for _ in range(self.columnNum):
					page_regex += '.{' + str(self.columnWidth) + '}\s{4}'
				page_regex += '\n|\s[0-9]+\n[=]{' + str(self.docWidth) + '}\n)+'
			page_regex += '(\s*\n)*'
			page_regex += '\s[0-9]+\n'
			page_regex += '[=]{' + str(self.docWidth) + '}'
			self.regex.append(page_regex)
		document = "</document>\n"
		self.write(document)
		return document

	def start(self):
		#self.delay(100)
		self.docLength = random.randint(5,50)
		self.docWidth = random.randint(100,200)
		self.columnNum = 1
		self.regex = []
		
		self._initDocumentID()
		document = self._newDocument()
		#self.write(document)
		document_str = self.regex

		self._readDocumentID()
		for p in self.regex:
			self.read(delim=chr(3), expect=p, expect_format='pcre')

	def quit(self):
		return -1
