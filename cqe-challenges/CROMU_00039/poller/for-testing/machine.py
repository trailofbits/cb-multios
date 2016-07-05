#!/usr/bin/python

from generator.actions import Actions
import random
import string
from struct import pack

class MyClass(Actions):
	def start(self):
		self.var = { 
			"system.name": [1, "CGC CB"] 
		}
		return

	def end(self):
		return

	def TestErrors(self):

		error_type = random.randint(1,4)
		request_id = random.randint(0,255)
		if error_type == 1:
			error_subtype = random.randint(1,5)
			if error_subtype == 1:
				# read name_len != pkt_len-COMMON_HDR_LEN-1
				pkt = ''
				pkt += '\x00'		# version
				pkt += chr(7)		# len
				pkt += '\x01'		# READ
				pkt += chr(request_id)
				pkt += chr(10)		# incorrect len
				pkt += "asdf"
			elif error_subtype == 2:
				# write name_len != pkt_len-COMMON_HDR_LEN-1
				pkt = ''
				pkt += '\x00'		# version
				pkt += chr(13)		# len
				pkt += '\x02'		# WRITE
				pkt += chr(request_id)
				pkt += chr(20)		# incorrect len
				pkt += "asdf"
				pkt += chr(2)		# type int32
				pkt += chr(4)		# value_len
				pkt += pack("<L",1)	# value
			elif error_subtype == 3:
				# write name_len > 127
				pkt = ''
				pkt += '\x00'		# version
				pkt += chr(137)		# len
				pkt += '\x02'		# WRITE
				pkt += chr(request_id)
				pkt += chr(128)		# incorrect len
				pkt += "a"*128
				pkt += chr(2)		# type int32
				pkt += chr(4)		# value_len
				pkt += pack("<L",1)	# value
			elif error_subtype == 4:
				# write value_len != pkt_len-curr_len
				pkt = ''
				pkt += '\x00'		# version
				pkt += chr(13)		# len
				pkt += '\x02'		# WRITE
				pkt += chr(request_id)
				pkt += chr(4)		# incorrect len
				pkt += "asdf"
				pkt += chr(2)		# type int32
				pkt += chr(10)		# value_len
				pkt += pack("<L",1)	# value
			elif error_subtype == 5:
				# write value_len > 127
				pkt = ''
				pkt += '\x00'		# version
				pkt += chr(137)		# len
				pkt += '\x02'		# WRITE
				pkt += chr(request_id)
				pkt += chr(4)		# incorrect len
				pkt += "test"
				pkt += chr(1)		# type string
				pkt += chr(128)		# value_len
				pkt += 'a'*128		# value

		elif error_type == 2:		# WRITEFAILED
			pkt = ''
			pkt += '\x00'		# version
			pkt += chr(20)		# len
			pkt += '\x02'		# WRITE
			pkt += chr(request_id)
			pkt += chr(11)		# name_len
			pkt += "system.name"	# name
			pkt += chr(2)		# type int32
			pkt += chr(4)		# value_len
			pkt += pack("<L",1)	# value

		elif error_type == 3:		# UNKNOWN
			pkt = ''
			pkt += '\x00'		# version
			pkt += chr(7)		# len
			pkt += chr(10)		# invalid
			pkt += chr(request_id)
			pkt += chr(10)		# incorrect len
			pkt += "asdf"

		elif error_type == 4:		# ERROR_NOTFOUND
			pkt = ''
			pkt += '\x00'		# version
			pkt += chr(13)		# len
			pkt += '\x01'		# READ
			pkt += chr(request_id)
			pkt += chr(10)		# name_len
			pkt += "system.nam"	# name

		self.write(pkt)

		# process response
		pkt = ''
		pkt += '\x00'		# version
		pkt += chr(3)		# len
		pkt += '\x04'		# ERROR
		pkt += chr(request_id)
		pkt += chr(error_type)

		self.read(length=len(pkt), expect=pkt)
		
	def ReadObject(self):

		# read a valid or invalid object
		if random.randint(0,1) == 0:
			# valid
			name = random.choice(self.var.keys())
		else:
			# invalid
			name = ''.join(random.choice(string.ascii_lowercase) for _ in range(5,10))
			while name in self.var:
				name = ''.join(random.choice(string.ascii_lowercase) for _ in range(5,10))

		# send the read request
		pkt = ''
		pkt += '\x00'                      # version
		pkt += chr(2+1+len(name))          # len
		pkt += '\x01'                      # READ_REQUEST
		request_id = chr(random.randint(0,255))
		pkt += request_id
		pkt += chr(len(name))
		pkt += name
	
		self.write(pkt)

		if name in self.var:
			# read back the expected packet response
			pkt = ''
			pkt += '\x00'
			pkt += chr(2+len(self.var[name][1]))
			pkt += '\x03'           # response
			pkt += request_id
			pkt += self.var[name][1]
		else: 
			pkt = ''
			pkt += '\x00'		# version
			pkt += '\x03' 		# len
			pkt += '\x04'		# ERROR
			pkt += request_id
			pkt += '\x04'		# NOTFOUND
			
		self.read(length=len(pkt), expect=pkt)
	
	def WriteObject(self):

		# write an existing or new object
		if random.randint(0,1) == 0:
			# existing
			name = random.choice(self.var.keys())
			objtype = self.var[name][0]
		else:
			# new
			name = ''.join(random.choice(string.ascii_lowercase) for _ in range(5,10))
			while name in self.var:
				name = ''.join(random.choice(string.ascii_lowercase) for _ in range(5,10))
			objtype = random.randint(1,2)

		# send the write request
		if objtype == 1:
			newval = ''.join(random.choice(string.ascii_lowercase) for _ in range(5,10))
			pkt = ''
			pkt += '\x00'                                # version
			pkt += chr(2+1+len(name)+1+1+len(newval))    # len
			pkt += '\x02'                                # WRITE_REQUEST
			request_id = chr(random.randint(0,255))
			pkt += request_id
			pkt += chr(len(name))
			pkt += name
			pkt += chr(objtype)
			pkt += chr(len(newval))
			pkt += newval
		else:
			newval = pack("<L", random.randint(0,100))
			pkt = ''
			pkt += '\x00'                                # version
			pkt += chr(2+1+len(name)+1+1+4)    # len
			pkt += '\x02'                                # WRITE_REQUEST
			request_id = chr(random.randint(0,255))
			pkt += request_id
			pkt += chr(len(name))
			pkt += name
			pkt += chr(objtype)
			pkt += chr(4)
			pkt += newval
	
		# update the local copy of the var
		self.var[name] = (objtype, newval)
		self.write(pkt)

		# read back the expected packet response
		if objtype == 1:
			pkt = ''
			pkt += '\x00'
			pkt += chr(2+len(self.var[name][1]))
			pkt += '\x03'           # response
			pkt += request_id
			pkt += self.var[name][1]
		else: 
			pkt = ''
			pkt += '\x00'
			pkt += chr(6)
			pkt += '\x03'           # response
			pkt += request_id
			pkt += newval
			
		self.read(length=len(pkt), expect=pkt)
	
