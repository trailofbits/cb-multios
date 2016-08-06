#!/usr/bin/env python

#Author: James Nuttall (james@cromulence.co)

#Copyright (c) 2015 Cromulence LLC

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in
#all copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#THE SOFTWARE.

from generator.actions import Actions, Variable
import struct
import random
import string
import sys
from collections import OrderedDict

#lengths of fields, used for offsets
SIZEOF_HEADER = 8
SIZEOF_CHAPTER = 6
SIZEOF_ENTRY = 7

# offsets into 'titles' and 'stit' lists
TIT_NAME = 0
TIT_FMT = 1
TIT_REQ = 2
TIT_MULT = 3

# this matches service.h enum Format
class Format():
	CHAR = 0
	SHORT = 1
	INT = 2
	STRING = 3
	BOOL = 4
	PTR = 5


# matches service.h enum Title
#class T():
#	cnt = 7
#	IDENTITY, MOVIES, VEHICLES, BOOK, SONG, JOBS, SPORTS = range(cnt)

#class ST():
#	cnt = 9
#	KAYAKING, STAMPS, COINS, KNIVES, SHOOTING, SOCCER, HOCKEY, TENNIS, BASKETBALL  = range(cnt)

titles_done = [] # keep track of the titles done for this chapter (resets after each chapter)

titles = []
#title, (entry name, entry format, required?, multiple allowed?)
titles.append(('identity', ('first name',Format.STRING, True, False), 
						('middle name',Format.STRING, False, False), 
						('last name',Format.STRING, True, False), 
						('age',Format.CHAR, True, False), 
						('weight',Format.SHORT, False, False), 
						('birth country',Format.STRING, False, False), 
						('birth state',Format.STRING, False, False), 
						('birth city',Format.STRING, False, False), 
						('married',Format.BOOL, False, False)))
titles.append(('movies', ('title',Format.STRING, True, False),
						('actor',Format.STRING, False, True), 
						('director',Format.STRING, False, True),
						('producer',Format.STRING, False, True),
						('year released',Format.SHORT, False, False), 
						('plot summary',Format.STRING, True, False)))
titles.append(('vehicles', ('make',Format.STRING, True, False),
						('model',Format.STRING, True, False), 
						('color',Format.STRING, False, True),
						('displacement',Format.SHORT, False, False),
						('displacement units',Format.CHAR, False, False), 
						('doors',Format.CHAR, True, False)))
titles.append(('books', ('author',Format.STRING, True, True),
						('year',Format.CHAR, False, False), 
						('summary',Format.STRING, False, False),
						('publisher',Format.STRING, False, False),
						('character',Format.STRING, False, True), 
						('made into a movie',Format.BOOL, True, False)))
titles.append(('songs', ('writer',Format.STRING, True, True),
						('year',Format.CHAR, False, False), 
						('genre',Format.STRING, False, False),
						('publisher',Format.STRING, False, False),
						('free online',Format.BOOL, True, False)))
titles.append(('jobs', ('title',Format.STRING, True, True),
						('years',Format.CHAR, False, False), 
						('job category',Format.STRING, False, False),
						('company',Format.STRING, True, False),
						('have a best friend',Format.BOOL, False, False),
						('salary',Format.INT, True, False)))
titles.append(('hobbies', ('sports',Format.PTR, False, False),
						('exercises',Format.PTR, False, False),
						('stamps',Format.PTR, False, False),
						('knives',Format.PTR, False, False),
						('kayaking',Format.PTR, False, False),
						('coins',Format.PTR, False, False),
						('knives',Format.PTR, False, False)))
titles.append(('pets', ('name',Format.STRING, True, True),
						('species',Format.STRING, True, False),
						('legs',Format.CHAR, False, False),
						('inside only',Format.BOOL, False, False),
						('age',Format.CHAR, False, False),
						('shots updated',Format.BOOL, True, False)))

# store the subentries for hobbies
stit = []
stit.append(('shooting', ('make',Format.STRING, True, True),
						('model',Format.STRING, True, True),
						('league',Format.STRING, False, False),
						('length',Format.CHAR, False, False),
						('length units',Format.STRING, False, False),
						('years experience',Format.CHAR, True, False),
						('injury',Format.BOOL, False, False)))
stit.append(('knives', ('make',Format.STRING, False, False),
						('model',Format.STRING, True, False),
						('value',Format.SHORT, False, False), 
						('style',Format.STRING, False, False),
						('blade length',Format.CHAR, True, False),
						('length units',Format.STRING, True, False),
						('comes with sheath',Format.BOOL, False, False),
						('injury',Format.BOOL, True, False)))
stit.append(('stamps', ('name',Format.STRING, True, False),
						('value',Format.SHORT, True, False), 
						('seller',Format.STRING, False, False),
						('mint',Format.BOOL, True, False),
						('count',Format.CHAR, True, False)))
stit.append(('kayaking', ('make',Format.STRING, True, False),
						('model',Format.STRING, True, False), 
						('length',Format.CHAR, False, False),
						('style',Format.STRING, False, False),
						('initial stability',Format.CHAR, False, False),
						('years experience',Format.CHAR, False, False),
						('highest class',Format.CHAR, False, False),
						('touring',Format.BOOL, False, False),
						('surfing',Format.BOOL, False, False),
						('tricking',Format.BOOL, False, False),
						('injury',Format.BOOL, False, False)))
stit.append(('coins', ('name',Format.STRING, True, False),
						('seller',Format.STRING, False, False),
						('value',Format.INT, True, False),
						('mint',Format.BOOL, True, False),
						('count',Format.CHAR, True, False)))
stit.append(('exercises', ('name',Format.STRING, True, True),
						('max weight',Format.SHORT, True, False), 
						('reps',Format.CHAR, False, False),
						('sets',Format.CHAR, True, False),
						('injury',Format.BOOL, False, False)))
stit.append(('sports', ('name',Format.STRING, True, False),
						('position',Format.STRING, True, True), 
						('years experience',Format.CHAR, True, False),
						('injury',Format.BOOL, False, False)))


class HobbyException(Exception):
	pass

isSubEntry = False # like Hobby, where we choose from the subentry table

# return the string representation of a title
def getRandomTitle():
	if isSubEntry:
		rnd = random.randint(0, len(stit)-1)
		return (rnd, stit[rnd][0])
	else:
		rnd = random.randint(0, len(titles)-1)
		return (rnd, titles[rnd][0])

def getEntryInfo(title, entry):
	if isSubEntry:
		return stit[title][entry+1]
	else:
		return titles[title][entry+1]

# given the title as string, return the entry as a string and int
# ret: name, value, format
def getRandomEntry(title):
	if isSubEntry:
		num = len(stit[title])
		rnd = random.randint(0, num - 2)
		return getEntryInfo(title, rnd)
	else:
		num = len(titles[title])
		rnd = random.randint(0, num - 2)
		return getEntryInfo(title, rnd)


# make temp copy of all titles
# remove them if they can't be multiples
acceptable_list = []

# use titles_done
def getAllowedRandomEntry(title, count):

	global acceptable_list

	ret = []

	if count == 0:
		return ret

	while len(ret) < count:
		if len(acceptable_list) == 0:
			#print "ERROR: NOT ENOUGH ENTRIES FOR COUNT: " + str(count)
			return 0

		rnd = random.randint(0,len(acceptable_list)-1)

		tmp = acceptable_list[rnd]

		if tmp[1][TIT_MULT] is False:
			acceptable_list.remove(tmp)

		ret.append(tmp)

	return ret

def getRequiredEntries(title):
	# return a list of required entries
	global acceptable_list
	acceptable_list = []

	if isSubEntry:
		for index, val in enumerate(stit[title][1:]):
			acceptable_list.append((index,val))
	else:
		for index, val in enumerate(titles[title][1:]):
			acceptable_list.append((index,val))

#	print "ACCEPTABLE: " + str(acceptable_list)

	cnt = -1
	ret = []
	if isSubEntry:
		for x in stit[title]:
			if x[2] is True:
				ret.append((cnt,x))
				if x[TIT_MULT] is False:
					for y,z in acceptable_list:
						if x == z:
							acceptable_list.remove((y,z))
					#print "Removing: " + str((y,z))
			cnt += 1
	else:
		for x in titles[title]:
			if x[2] is True:
				ret.append((cnt,x))
				if x[TIT_MULT] is False:
					for y,z in acceptable_list:
						if x == z:
							acceptable_list.remove((y,z))
					#print "Removing: " + str((y,z))
			cnt += 1
	return ret

# how many required fields are in this chapter?
def getRequiredCount(title):
	return len(getRequiredEntries(title))

def getEntryCountInTitle(title):
	if isSubEntry:
		return (len(stit[title]) - 1) # don't count the title of the chapter
	else:
		return (len(titles[title]) - 1) # don't count the title of the chapter

# book has chapters in it
# chapters have titles and content
class Book():

	def __init__(self, count):
		self.num_chapters = count

	# offset_to_me is the file offset to the start of this entry
	# title is the title of this chapter. all of the tags should be correct for this title type
	# e.g. TITLE is Identity, TAGs are: first_name, mid_name, weight, birthdate, height, age
	# if TITLE is hobby, TAGs are: name, years, total_cost, club_name, 
	# if TITLE is sport, TAGs are: sport_name, years_exp, position, 
	# TITLE books, TAGs: title, # in series, publisher, year released first, year released last, made into movie?, num pages total
	# TITLE diary entry, TAGs: date, heading, summary, alcohol involved?, time, place, friends_involved
	# TITLE guns, TAGs: make, model, caliber, units, range, terminal velocity, capacity, barrel length, grain of bullet, #grains of 230, 
	# TITLE music, TAGs: artist, year, song name, publisher, available on internet?, 
	# TITLE Martial art, TAGs: country of origin, year of start, style name, rank, years, instructor name, 
	# TITLE Movie, TAGs: name, director, # main actors, names of actors in list, summary, date released
	def CreateEntry(self, offset_to_me, title, entry, last):
		
		responses = []

		# (entry_number, (name, format, req, mult))
		#print "CreateEntry: " + str(entry)
		entry_name = entry[1][0]
		entry_value = entry[0]
		entry_format = entry[1][1]
		entry_req = entry[1][2]
		entry_mult = entry[1][3]

		#ENTRY
		ret = struct.pack('B', entry_value)

		#FORMAT
		ret += struct.pack('B', entry_format)

		my_size = SIZEOF_ENTRY

		lenn = 0
		big_int = 0
		big_str = ''
		odata = 0
		#calculate offset data
		if entry_format == Format.CHAR:
			odata = random.randint(12,255) # 12 is so we don't accidently trigger a POV (kid's age)
			lenn = 0
			responses.append(entry_name + ": " + str(hex(odata)))
		elif entry_format == Format.SHORT:
			odata = random.randint(0,65535)
			lenn = 0
			responses.append(entry_name + ": " + str(hex(odata)))
		elif entry_format == Format.INT:
			big_int = random.randint(0,2147483647) 
			lenn = 4
			odata = offset_to_me + my_size 
			my_size += lenn
			responses.append(entry_name + ": " + str(hex(big_int)))
		elif entry_format == Format.STRING:
			# calc string

			big_str = ''.join(random.choice('abc') for _ in range(random.randint(1,24)))
			#big_str = ''.join(random.choice(string.letters) for _ in range(random.randint(1,24)))
			# get len
			lenn = len(big_str)
			# save offset in odata
			odata = offset_to_me + my_size 
			my_size += lenn
			# save string in value
			responses.append(entry_name + ": " + big_str)
		elif entry_format == Format.BOOL:
			odata = random.randint(0,1)
			if (odata == 1):
				responses.append(entry_name + ": " + 'true')
			else:
				responses.append(entry_name + ": " + 'false')
			lenn = 0

		#LEN
		ret += struct.pack('B', lenn)

		#OFFSET DATA
		ret += struct.pack('H', odata)

		#OFFSET_NEXT_ENTRY
		if not last:
			offset = offset_to_me + my_size
			ret += struct.pack('H', offset)
		else:
			# this is the last entry for this chapter
			ret += struct.pack('H', 0)

		# DATA?
		if (entry_format == Format.INT):
			# need to store the INT
			ret += struct.pack('I', big_int)
		elif entry_format == Format.STRING:
			# store the string
			for x in big_str:
				ret += struct.pack('B', ord(x))

		return (responses, my_size, ret)



	def CreateAllEntries(self, offset_to_me, title, count):

		# how much space we will take up
		my_size = 0

		# a list of expected strings during polling
		responses = []

		# the string that will become the poller file
		return_string = ''

		entries_left = count

		tmp_resp = []
		tmp_ret_str = []
		tmp_size = 0

		current_offset = offset_to_me

		special_subentries = []

		# for entry in required
		entries = getRequiredEntries(title)

		for entry in entries:
			if entry[1][1] == Format.PTR:
				special_subentries.append(entry)
				entries_left -= 1
				continue
			if entry[0] == -1:
				continue
			# entry has: title, format, required?, multiple allowed?

			if entries_left == 1:
				tmp_resp, tmp_size, tmp_ret_str = self.CreateEntry(current_offset, title, entry, True)
			else:
				tmp_resp, tmp_size, tmp_ret_str = self.CreateEntry(current_offset, title, entry, False)
			entries_left -= 1
			responses += tmp_resp
			return_string += tmp_ret_str
			my_size += tmp_size
			current_offset += tmp_size

		entries = getAllowedRandomEntry(title, entries_left)

		for entry in entries:
			if entry[0] == -1:
				continue
			if entry[1][1] == Format.PTR:
				special_subentries.append(entry)
				entries_left -= 1
				continue
			# entry has: title, format, required?, multiple allowed?
			if entries_left == 1:
				tmp_resp, tmp_size, tmp_ret_str = self.CreateEntry(current_offset, title, entry, True)
			else:
				tmp_resp, tmp_size, tmp_ret_str = self.CreateEntry(current_offset, title, entry, False)
			entries_left -= 1
			responses += tmp_resp
			return_string += tmp_ret_str
			my_size += tmp_size
			current_offset += tmp_size

		return (responses, my_size, return_string)

	def CreateChapter(self, offset_to_me, chapter, sub, last):
		ret = ''
		all_responses = []
		my_size = SIZEOF_CHAPTER
		global isSubEntry

		current_offset = offset_to_me + SIZEOF_CHAPTER

		try:
			# create a random title
			title_value = chapter[0]
			title_str = chapter[1]
			#print " >>> " + title_str
			#print "offset given to me: " + str(hex(offset_to_me))

			if title_str == 'hobbies':
				#print "HOBBIES!!!"

				# TITLE (hobbies)
				ret += struct.pack('B', title_value)
				all_responses.append("Title: " + title_str)

				hobby_count = random.randint(1, 6)

				# ENTRY_COUNT
				ret += struct.pack('B', hobby_count)
				all_responses.append("Entry Count: " + str(hex(hobby_count)))

				offset = offset_to_me + SIZEOF_CHAPTER # (hobbies chapter)

				# OFFSET_FIRST_ENTRY (actually a chapter this time)
				ret += struct.pack('H', offset)

				isSubEntry = True

				ret_tmp = ''

				# pick count here and loop
				for x in range(hobby_count):
					hobby_choice = random.randint(0, len(stit) -1)
					hob = (hobby_choice, stit[hobby_choice][0])
					if (x == hobby_count-1):
						tmp_resp, tmp_size, tmp_out = self.CreateChapter(current_offset, hob, True, True)
					else:
						tmp_resp, tmp_size, tmp_out = self.CreateChapter(current_offset, hob, True, False)
					
					# aggregate tmp_resp, tmp_size, tmp_out
					all_responses += tmp_resp
					my_size += tmp_size
					ret_tmp += tmp_out
					current_offset += tmp_size
					
				# OFFSET_NEXT_CHAPTER
				if last:
					# last chapter, no offset for another one
					ret += struct.pack('H', 0)
				else:
					ret += struct.pack('H', current_offset)

				ret += ret_tmp

				isSubEntry = False

				raise HobbyException

			# TITLE
			ret += struct.pack('B', title_value)

			all_responses.append("Title: " + title_str)

			mmin = getRequiredCount(title_value)
			mmax = getEntryCountInTitle(title_value)
			entry_count = random.randint(mmin, mmax)

			# ENTRY_COUNT
			ret += struct.pack('B', entry_count)
			all_responses.append("Entry Count: " + str(hex(entry_count)))
			#print "Count: " + str(entry_count)

			# offset to the first entry (right after this chapter)
			# offset of the file up to me + my size
			offset = offset_to_me + SIZEOF_CHAPTER

			# OFFSET_FIRST_ENTRY
			ret += struct.pack('H', offset)

			resp = []
			loop_ret = ''
			entry_sizes = 0

			#offset_to_me, title, count
			resp, entry_sizes, r = self.CreateAllEntries(offset, title_value, entry_count)
			all_responses += resp
			loop_ret += r

			# OFFSET_NEXT_CHAPTER
			if last:
				# last chapter, no offset for another one
				offset_to_next_chapter = 0
				ret += struct.pack('H', 0)
			else:
				offset_to_next_chapter = offset_to_me + SIZEOF_CHAPTER + entry_sizes
				ret += struct.pack('H', offset_to_next_chapter)

			ret += loop_ret

			my_size += entry_sizes

			return (all_responses, my_size, ret)

		except HobbyException: # skip the above work if doing hobbies
			return (all_responses, my_size, ret)


	# chapter contains arbitrary number of entries within it
	# offset_to_me is the file offset when this chapter entry started
	# if 'last' is True, this is the last chapter 
	def CreateRandomChapter(self, offset_to_me, last):
		return self.CreateChapter(offset_to_me, getRandomTitle(), 0, last)

	def PopulateBookPov(self):
		offset = SIZEOF_HEADER
		ret = ''
		responses = []

		 #THIS SECTION IS TO CREATE POLLERS
		 #chapters to win:
		# married ID
		(resp, diff, val) = self.CreateChapter(offset, (0, titles[0][0]), 0, False)
		ret += val
		responses += resp
		# append the length of a chapter (and its entries) to get the right offset
		offset += diff

		# married ID
		(resp, diff, val) = self.CreateChapter(offset, (0, titles[0][0]), 0, False)
		ret += val
		responses += resp
		# append the length of a chapter (and its entries) to get the right offset
		offset += diff

		# kid ID
		(resp, diff, val) = self.CreateChapter(offset, (0, titles[0][0]), 0, False)
		ret += val
		responses += resp
		# append the length of a chapter (and its entries) to get the right offset
		offset += diff

		# pet
		(resp, diff, val) = self.CreateChapter(offset, (7, titles[7][0]), 0, False)
		ret += val
		responses += resp
		# append the length of a chapter (and its entries) to get the right offset
		offset += diff
		
		# pet
		(resp, diff, val) = self.CreateChapter(offset, (7, titles[7][0]), 0, False)
		ret += val
		responses += resp
		# append the length of a chapter (and its entries) to get the right offset
		offset += diff
		
		# job > 20 yrs experience
		(resp, diff, val) = self.CreateChapter(offset, (5, titles[5][0]), 0, True)
		ret += val
		responses += resp
		# append the length of a chapter (and its entries) to get the right offset
		offset += diff


		return (responses, ret)

	def PopulateBook(self):
		offset = SIZEOF_HEADER
		ret = ''
		responses = []

		for chap in range(self.num_chapters):
			if chap == self.num_chapters - 1:
				(resp, diff, val) = self.CreateRandomChapter(offset, True)
			else:
				(resp, diff, val) = self.CreateRandomChapter(offset, False)
			ret += val
			responses += resp
			# append the length of a chapter (and its entries) to get the right offset
			offset += diff

		return (responses, ret)


# Main entry point here
class ReMe_parser(Actions):
	MAGIC_NUMBER = 0x4242
	all_responses = []

	MIN_CHAPTERS = 2
	MAX_CHAPTERS = 10

	counter = 0

	def begin(self):
		pass

	def _write_header(self):
		b = struct.pack('H', self.MAGIC_NUMBER) # magic number
		self.all_responses.append("Magic number: " + str(hex(self.MAGIC_NUMBER)))
		future = random.randint(0x0100, 0x7fff)
		b += struct.pack('H', future) # future
		self.all_responses.append("Future: " + str(hex(future)))
		offset = SIZEOF_HEADER
		b += struct.pack('<I', offset)  # offset to first chapter
		self.all_responses.append("Offset: " + str(hex(offset)))
		return b

	def _write_book(self):
		# randomly choose a type and insert it
		# count of dirs
		# first entry:
		  # tag, format, num_components, data or offset
		# offset to next dir
		count = random.randint(self.MIN_CHAPTERS, self.MAX_CHAPTERS)
		#print "We are going to make " + str(count) + " chapters!"
		book = Book(count)
		return book.PopulateBook()


	# Set up the game
	def start(self):

		self.read(delim="\n", expect="Welcome to the diary logger!")

		blob = ''
		#print "----------------- gen_" + str(self.counter) + " start"
		while True:
			self.all_responses = []
			blob = self._write_header()

			resp, c = self._write_book()
			blob += c
			self.all_responses += resp
			if len(blob) < 1000: # limited by the malloc in MAIN() of service.c
				break;

		self.write( struct.pack( "H", len(blob) ) ) # length of blob
		self.write( blob )

		# DEBUG ONLY
		#filename = "%04d" % self.counter #random.randint(1, 12345))
		#filename += '.test.out'
		#f =  open("files/"+filename, 'w')
		#f.write(blob)
		#f.close()

		self.counter += 1

		# END OF WRITING HERE

		self.read(delim="\n", expect="Length: " + str(len(blob)))
		for x in self.all_responses:
			self.read(delim="\n", expect=x)

		self.read(delim="\n", expect="good book.")

# randomly generate lengths and entries
# generate the text response at the same time

class Prng():

	COEFFICIENT_A_64 = 12
	COEFFICIENT_B_64 = 25
	COEFFICIENT_C_64 = 27
	MULTIPLIER_64 = 1803442709493370165
	COEFFICIENT_A_1024 = 27
	COEFFICIENT_B_1024 = 13
	COEFFICIENT_C_1024 = 46
	MULTIPLIER_1024 = 1865811235122147685

	def __init__(self):

		self.state = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
		self.position = 0

	def sprng(self, seed):

		state_64 = seed & 0xffffffffffffffffL
		for i in range(16):
			state_64 ^= (state_64 >> self.COEFFICIENT_A_64)& 0xffffffffffffffffL
			state_64 ^= (state_64 << self.COEFFICIENT_B_64)& 0xffffffffffffffffL
			state_64 ^= (state_64 >> self.COEFFICIENT_C_64)& 0xffffffffffffffffL
			self.state[i] = (state_64 *self.MULTIPLIER_64)& 0xffffffffffffffffL
		self.position = 0

	def prng(self):
		state0 = self.state[self.position]
		self.position = (self.position +1) % 16
		state1 = self.state[self.position]

		state1 ^= (state1 << self.COEFFICIENT_A_1024)& 0xffffffffffffffffL
		state1 ^= (state1 >> self.COEFFICIENT_B_1024)& 0xffffffffffffffffL
		state0 ^= (state0 >> self.COEFFICIENT_C_1024)& 0xffffffffffffffffL
		self.state[self.position] = (state0 ^ state1)& 0xffffffffffffffffL
		return (self.state[self.position] * self.MULTIPLIER_1024)& 0xffffffffffffffffL

	def random_in_range(self, min, max):

		if (max <= min):
			return 0
		range = max - min + 1
		scale_factor = 0xffffffff / range
		#discard numbers that would cause bias
		while True:
			rand_uint = self.prng() & 0xffffffff
			if (rand_uint < (scale_factor * range)):
				break

		return (rand_uint / scale_factor + min)