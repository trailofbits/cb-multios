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

MAX_NAME_LEN = 15
MAX_PASS_LEN = 15
MAX_MSG_LEN = 15
MAX_MESSAGES = 20
MAX_USERS = 10
MAX_MSG_LOGIN = 4


class User():
	name = ""
	password = ""

	def __init__(self):
		self.users = []

	def CreateRandomUser(self):
		
		passwd = ''.join(random.choice('xyz') for _ in range(random.randint(5, MAX_PASS_LEN - 2)))
		unique = False
		while not unique:
			name = ''.join(random.choice('abc') for _ in range(random.randint(5, MAX_NAME_LEN - 2)))
			unique = True
			for x,y in self.users:
				if x == name:
					unique = False
					
					
		self.AddUser((name, passwd))

		return (name, passwd)

	def AddUser(self, (name, passwd)):
		self.users.append((name, passwd))

	def GetUser(self, num):
		return self.users[num]

	def SetRandomUser(self):
		if len(self.users) == 0:
			return
		(self.name, self.password) = random.choice(self.users)

		#num = random.randint(0, len(self.users) - 1)
		#self.name, self.password = self.GetUser(num)

	def GetRandomUser(self):
		num = random.randint(0, len(self.users) - 1)
		n,p = self.GetUser(num)
		return n


# Main entry point here
class Agent_message(Actions):
	user = User() # holds all (User, Password) pairs
	#					   [0]  [1][0] [1][1] [1][2]
	#messages = [] # holds (indx, draft?, (To, From, Msg)) pairs
	# indx is the array index c is using

	messages = {} # user_name: (msg), (msg), (msg)...
	num_msg_login = 0

	def valid_login(self, force_user=""):
		if force_user is "":
			self.user.SetRandomUser()
		else:
			self.user.name = force_user
			for x,y in self.user.users:
				if x == self.user.name:
					self.user.password = y
		self.write("2\n") # login

		for x in self.user.users:
			exp = "{} -- {}".format(x[0], x[1])
			self.read(delim="\n", expect=exp)	

		self.read(delim="\n", expect="Username: ")
		self.write(self.user.name + '\n')
		self.read(delim="\n", expect="Password: ")
		self.write(self.user.password + '\n')
		self.num_msg_login = 0

	def add_user(self):
		if len(self.user.users) == MAX_USERS:
			return
		self.write("1\n")
		n,p = self.user.CreateRandomUser()
		self.messages[n] = [] # add user to messages
		self.read(delim="\n", expect="Username: ")
		self.write(n + '\n')
		self.read(delim="\n", expect="Password: ")
		self.write(p + '\n')

	def delete_draft(self):
		self.write("6\n")

		blah = self.messages[self.user.name]
		my_msgs = []

		for x in blah:
			if x[1] is True:
				my_msgs.append(x)

		if len(my_msgs) == 0:
			self.read(delim="\n", expect="Must create draft first.")
			return

		for i, x in enumerate(my_msgs):
			exp = "{}: To: {} Msg: {}".format(x[0], x[2][0], x[2][2])
			self.read(delim="\n", expect=exp)

		pick = random.choice(my_msgs)
		self.messages[self.user.name].remove(pick)
		self.write(str(pick[0]) + '\n')

	def find_lowest(self, name):
		all_nums = []
		for x in range(100): 
			all_nums.append(x)

		
		if name in self.messages.keys():
			for x in self.messages[name]:
				all_nums.remove(x[0])

		if len(all_nums) == 0:
			return -1
		lowest = min(all_nums)
		return lowest

	def create_message(self):
		self.write("1\n")

		if self.num_msg_login == MAX_MSG_LOGIN:
			self.read(delim="\n", expect="Reached maximum messages for this session.")
			return

		msg = ''.join(random.choice('mog') for _ in range(random.randint(4, MAX_MSG_LEN - 2)))
		self.read(delim="\n", expect="To:")
		usr = self.user.GetRandomUser()
		self.write(usr + '\n')
		self.read(delim="\n", expect="Message:")
		self.write(msg + '\n')

		lowest = self.find_lowest(self.user.name)
		if lowest == -1:
			return

		self.messages[self.user.name] += [(lowest, True, (usr, self.user.name, msg))]
		self.num_msg_login += 1

	def send_message(self):
		my_drafts = []
		for x in self.messages[self.user.name]:
			if x[1] == True:
				my_drafts.append(x)

		self.write("2\n")
		# random msg from drafts, change to sent

		if len(my_drafts) == 0:
			self.read(delim="\n", expect="Must create draft first.")
			return

		my_drafts = sorted(my_drafts, key=lambda blah: blah[0])
		for x in my_drafts:
			exp = "{}: To: {} Msg: {}".format(x[0], x[2][0], x[2][2])
			self.read(delim="\n", expect=exp)

		pick = random.choice(my_drafts)

		self.write(str(pick[0]) + '\n')

		# move message to correct 'dest' list
		pick_new = list(pick)
		
		# update the index when put into this list
		lowest = self.find_lowest(pick_new[2][0])
		if lowest == -1:
			return
		pick_new = (lowest,False,pick_new[2])

		# remove from sender's list
		self.messages[self.user.name].remove(pick)
		
		self.messages[pick_new[2][0]].append(pick_new)


	def list_all_messages(self):
		self.write("3\n")
		found = False

		# if there are no messages, look for error message
		if self._size_all() == 0:
			self.read(delim="\n", expect="No messages.")
			return

		group = []
		for indx, (name, pwd) in enumerate(self.user.users):
			tmp = []
			for x in self.messages[name]:
				tmp.append((x, indx))
			tmp = sorted(tmp, key=lambda blah: blah[0])
			group.append(tmp)

		for user_group in group:
			if len(user_group) > 0:
				user_num = user_group[0][1]
				for i, msg in enumerate(user_group):
					if i == 19:
						return
					found = True
					self.read(delim="\n", expect="******************")
					exp = "To: {}".format(msg[0][2][0])
					self.read(delim="\n", expect=exp)
					exp = "From: {}".format(msg[0][2][1])
					self.read(delim="\n", expect=exp)
					exp = "Msg: {}".format(msg[0][2][2])
					self.read(delim="\n", expect=exp)

		if not found:
			self.read(delim="\n", expect="No messages.")
			return

	def list_inbox(self):
		self.write("5\n")
		found = False

		msgs = []
		for x in self.messages[self.user.name]:
			if x[1] != True: # not a draft
				msgs.append(x)

		msgs.sort()

		for x in msgs:
			found = True
			self.read(delim="\n", expect="******************")
			exp = "To: {}".format(x[2][0])
			self.read(delim="\n", expect=exp)
			exp = "From: {}".format(x[2][1])
			self.read(delim="\n", expect=exp)
			exp = "Msg: {}".format(x[2][2])
			self.read(delim="\n", expect=exp)

		if not found:
			self.read(delim="\n", expect="No messages for this user.")
			return

	def list_drafts(self):
		# list drafts for this user
		self.write("4\n")
		found = False

		msgs = []
		for x in self.messages[self.user.name]:
			if x[1] == True: 
				msgs.append(x)

		msgs.sort()

		for x in msgs:
			found = True
			self.read(delim="\n", expect="******************")
			exp = "To: {}".format(x[2][0])
			self.read(delim="\n", expect=exp)
			exp = "From: {}".format(x[2][1])
			self.read(delim="\n", expect=exp)
			exp = "Msg: {}".format(x[2][2])
			self.read(delim="\n", expect=exp)

		if not found:
			self.read(delim="\n", expect="No drafts for this user.")
			return

	# Set up the game
	def start(self):
		self.user.users = []
		self.messages = {}

	def leave_A(self):
		self.write("3\n")
		self.read(delim="\n", expect="The end.")

	def leave_B(self):
		self.write("8\n")
		self.read(delim="\n", expect="The end.")

	def read_A(self):
		self.read(delim="\n", expect="******************")
		self.read(delim="\n", expect="1. Create User")
		self.read(delim="\n", expect="2. Login")
		self.read(delim="\n", expect="3. Exit")
		self.read(delim="\n", expect=": ")

	def _size_all(self):
		count = 0

		for x in self.messages.values():
			for y in x:
				count += 1
		return count

	def _size_inbox(self):
		count = 0
		for x in self.messages[self.user.name]:
			if x[1] is False: # messages TO this user, only
				count += 1
		return count

	def _size_drafts(self):
		count = 0
		for x in self.messages[self.user.name]:
			if x[1] is True: # drafts only
				count += 1
		return count

	def read_B(self):
		exp = "********{}********".format(self.user.name)
		self.read(delim="\n", expect=exp)
		self.read(delim="\n", expect="1. Create Message")
		self.read(delim="\n", expect="2. Send Message")
		exp = "3. List All [{}]".format(self._size_all())
		self.read(delim="\n", expect=exp)
		cnt = self._size_drafts()
		exp = "4. List Drafts [{}]".format(cnt)
		self.read(delim="\n", expect=exp)
		exp = "5. List Inbox [{}]".format(self._size_inbox())
		self.read(delim="\n", expect=exp)
		self.read(delim="\n", expect="6. Delete Draft")
		self.read(delim="\n", expect="7. Logout")
		self.read(delim="\n", expect="8. Exit")
		self.read(delim="\n", expect=": ")

	def logout(self):
		self.write("7\n") # logout
		exp = "Logging out of user {}".format(self.user.name)
		self.read(delim="\n", expect=exp)

	def bad_login(self, force_user=""):

		self.write("2\n") # login

		for x in self.user.users:
			exp = "{} -- {}".format(x[0], x[1])
			self.read(delim="\n", expect=exp)

		self.read(delim="\n", expect="Username: ")
		self.write(force_user + '\n')
		self.read(delim="\n", expect="Password: ")
		self.write('abcd990\n') # probably wrong
		self.read(delim="\n", expect="Bad login.")

	def valid_login2(self, force_user=""):
		if force_user is "":
			self.user.SetRandomUser()
		else:
			self.user.name = force_user
			for x,y in self.user.users:
				if x == self.user.name:
					self.user.password = y
		self.read(delim="\n", expect="Username: ")
		self.write(self.user.name + '\n')
		self.read(delim="\n", expect="Password: ")
		self.write(self.user.password + '\n')
		self.num_msg_login = 0

	def read_B_fake(self):
		exp = "********{}********".format(self.user.name)
		self.read(delim="\n", expect=exp)
		self.read(delim="\n", expect="1. Create Message")
		self.read(delim="\n", expect="2. Send Message")
		exp = "3. List All [{}]".format(0)
		self.read(delim="\n", expect=exp)
		exp = "4. List Drafts [{}]".format(20)
		self.read(delim="\n", expect=exp)
		exp = "5. List Inbox [{}]".format(self._size_inbox())
		self.read(delim="\n", expect=exp)
		self.read(delim="\n", expect="6. Delete Draft")
		self.read(delim="\n", expect="7. Logout")
		self.read(delim="\n", expect="8. Exit")
		self.read(delim="\n", expect=": ")

	def begin(self):
		self.user.users = []
		self.messages = {}
		for _ in range(MAX_USERS):
			self.read_A()
			self.add_user()



# POV CODE BELOW
		#self.read_A()
		#self.valid_login(self.user.users[MAX_USERS-1][0])
#
		#self.read_B()
		#
		#for _ in range(5):
		#	for _ in range(MAX_MSG_LOGIN):
		#		self.create_message()
		#		self.read_B()
		#	self.logout()
		#	self.read_A()
		#	self.valid_login(self.user.users[MAX_USERS-1][0])
		#	self.read_B()
#
		##self.logout()
		##self.read_A()
		##self.bad_login(self.user.users[MAX_USERS-1][0])
		##self.read_A()
		##self.bad_login(self.user.users[MAX_USERS-1][0])
		##self.read_A()
		##self.bad_login(self.user.users[MAX_USERS-1][0])
		##self.valid_login2(self.user.users[MAX_USERS-1][0])
		##self.read_A()
		##self.valid_login(self.user.users[MAX_USERS-1][0])
##
		##self.read_B_fake()
		#self.logout()
		#self.read_A()
		#self.valid_login(self.user.users[MAX_USERS-1][0])
		#self.read_B()
		#self.create_message()
		#self.read_B()
		#self.list_all_messages()
		#self.read_B()
		#self.list_drafts()
		#self.read_B()

