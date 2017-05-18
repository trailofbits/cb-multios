#!/usr/bin/env python

from generator.actions import Actions
from struct import *
from random import *
import binascii

class MyClass(Actions):
	def start(self):
		#self.delay(100)
		self.COMMAND_OPEN   = "\x00"
		self.COMMAND_CLOSE  = "\x01"
		self.COMMAND_WRITE	= "\x02"
		self.COMMAND_READ	= "\x03"
		self.COMMAND_DELETE	= "\x04"
		self.COMMAND_END	= "\x05"

		self.MAX_FILES = 128
		self.MAX_FILE_DESCRIPTORS = 16
		self.Files = { }	

		self.fd = [ ]
		for i in range( 0, self.MAX_FILE_DESCRIPTORS ):
			self.fd.append( [ 0xFFFF, 0x0 ] )  # inode, filepos

		#print "[[[[[[[[[[[[START]]]]]]]]]]]]"
		#print self.fd

		# Read Banner
		if ( unpack('B', self.magic_page[0] )[0]  < 0x80 ):
                	blockSize = 256
        	else:
                	blockSize = 512;

        	blocksPerSector = (( unpack('B', self.magic_page[1] )[0] % 3)+2) * 4

        	sectorCount = (( unpack('B', self.magic_page[2] )[0] % 32)+128) * 4	

		expect_banner = "Starting test for device (%d, %d, %d):" % (blockSize, blocksPerSector, sectorCount)
		self.read( expect=expect_banner, delim="\n" )

	#############################
	# Helper Funtions
	#############################
	def next_inode( self ):
		for inode in range ( 0, self.MAX_FILES ):
			if inode not in self.Files.keys():
				return inode

		return None
	
	def next_fd( self ):
		for i in range( 0, self.MAX_FILE_DESCRIPTORS ):
			if ( self.fd[i][0] == 0xFFFF ):
				return i

		return None

	def get_random_fd( self ):
		fd_count = 0
		for i in range( 0, self.MAX_FILE_DESCRIPTORS ):
			if ( self.fd[i][0] != 0xFFFF ):
				fd_count += 1

		if ( fd_count == 0 ):
			return None

		rand_fd_idx = randint( 0, (fd_count-1) )
		fd_idx_cur = 0
		for i in range( 0, self.MAX_FILE_DESCRIPTORS ):
			if ( self.fd[i][0] != 0xFFFF ):
				if ( fd_idx_cur == rand_fd_idx ):
					return i
				fd_idx_cur += 1

		return None

	def random_string(self, min_length, max_length):
		return ''.join(chr(randint(1,255)) for _ in range(randint(min_length, max_length)))

	#############################
	# Read Tests
	#############################
	def TestRead(self):
		# are we going for a success or failure?
		rand_fd = self.get_random_fd( )
		if randint(0,3) > 0 and rand_fd is not None:
			# success
			#print "rand fd is: %d inode is: %d\n" % (rand_fd, self.fd[rand_fd][0])
			contents = self.Files[self.fd[rand_fd][0]][1]

			if ( len(contents) == 0 ):
				# Empty file
				self.comment( "Failed read attempt (empty file)" )
				self.SendRead( rand_fd, randint( 0, 200 ), "", 0 )
			
			else:
				offset = self.fd[rand_fd][1]
				
				if ( offset == len(contents) ):
					self.comment( "Successful read attempt -- at end of file" )
					self.SendRead( rand_fd, 0, "", 0 )
				else:
					self.comment("Successful read attempt of data")
					length = randint(1, len(contents)-offset)
					expected_string = contents[offset:offset+length]
	
					# Move file position
					self.fd[rand_fd][1] += length

					# Do successful read
					self.SendRead( rand_fd, length, expected_string, len(expected_string) )

		else:
			# failure
			if rand_fd is None:
				# No FDs available
				self.comment("Bad read attempt: no FDs")
				send_fd = randint( 0, 15 )
				length = randint( 0, 4096 )
				expected_string = ""
				self.SendRead( send_fd, length, expected_string, -1 )
			else:
				# Pick a bad FD
				self.comment("Bad read attempt: Picking invalid FD")
				send_fd = randint( 16, 3000 ) 
				length = randint(1,10)
				expected_string = ""
				self.SendRead( send_fd, length, expected_string, -1 )

	def SendRead(self, fd, length, expected_string, expected_retvalue):
		# COMMAND_READ
		self.write(self.COMMAND_READ)
		self.write(pack("<i",fd))
		self.write(pack("<I",length))

		# response
		self.read(length=4, expect=pack("<i", expected_retvalue))
		self.read(length=4, expect=pack("<I", len(expected_string)))
		if ( len(expected_string) > 0 ):
			self.read(length=len(expected_string), expect=expected_string)

	#############################
	# Write Tests
	#############################
	def TestWrite(self):
		# are we going for a success or failure?
		rand_fd = self.get_random_fd( )
		if rand_fd is not None:
			# success
			self.comment("Successful write attempt")

			string = self.random_string(1,254)
			self.SendWrite( rand_fd, string, len(string))

			file_inode = self.fd[rand_fd][0]
			file_pos = self.fd[rand_fd][1]

			# Overwrite
			new_data = self.Files[file_inode][1][0:file_pos] + string + self.Files[file_inode][1][file_pos+len(string):]
			self.Files[file_inode][1] = new_data
			self.fd[rand_fd][1] = (file_pos + len(string))

		else:
			bad_fd = randint( 0, 15 )
			# failure
			self.comment("Bad write attempt: Bad FD")
			string = self.random_string(1,254)
			self.SendWrite( bad_fd, string, -1 )

	def SendWrite(self, fd, string, expected_retvalue):
		# CFS_WRITE
		self.write(self.COMMAND_WRITE)
		self.write(pack("<i", fd))
		self.write(pack("<I", len(string)))
		if ( len(string) > 0 ):
			self.write(string)

		# response
		self.read(length=4, expect=pack("<i", expected_retvalue))
		self.read(length=4, expect=pack("<I", 0 ))

	#############################
	# Delete Tests
	#############################
	def TestDel(self):
		# are we going for a success or failure?
		if randint(0,1) and len(self.Files.keys()) > 0:
			# success
			self.comment("Successful delete attempt")
			# pick a vaild file
			inode = choice(self.Files.keys())
			filename = self.Files[inode][0]

			self.SendDel(filename, 0)

			# Clean up any FDs pointing to that inode
			for i in range( 0, self.MAX_FILE_DESCRIPTORS ):
				if ( self.fd[i][0] == inode ):
					self.fd[i][0] = 0xFFFF
					self.fd[i][1] = 0

			# Delete file
			del self.Files[inode]

			#print "Deleted file: inode=%d\n" % inode
		else:
			self.comment("Bad delete attempt: invalid file")
			filename = self.random_string(1,10)
			while filename in [self.Files[inode][0] for inode in self.Files.keys()] or len(filename) is 0:
				filename = self.random_string(1,10)
			self.SendDel(filename, -1)

	def SendDel(self, filename, expected_retvalue):
		# COMMAND_DELETE
		self.write(self.COMMAND_DELETE)
		self.write(chr(len(filename)))
		self.write(filename)

		# response
		self.read(length=4, expect=pack("<i", expected_retvalue))
		self.read(length=4, expect=pack("<I", 0 ))

	#############################
	# Open Tests
	#############################
	def TestOpen(self):
		# are we going for a success or failure?
		rand_choice = randint(0,2)
		if rand_choice == 0:
			# Open new file for writing
			open_mode = 2
			
			filename = self.random_string(1,10)
			while filename in [self.Files[inode][0] for inode in self.Files.keys()] or len(filename) is 0:
				filename = self.random_string(1,10)

			new_fd = self.next_fd( )

			if ( new_fd == None ):
				# Fail out of FDs
				self.comment( "Failed open attempt (write) out of FDs" )
	
				self.SendOpen( filename, open_mode, -1 )	
			
			else:
				# success
				self.comment("Successful open attempt (write)")

				new_inode = self.next_inode()
	
				# Created new file
				#print "Created file, fd=%d, inode=%d\n" % (new_fd, new_inode)
				self.Files[new_inode] = [ filename, "" ]

				self.fd[new_fd][0] = new_inode
				self.fd[new_fd][1] = 0

				# pick a vaild file that's not the passwd file
				self.SendOpen(filename, open_mode, new_fd)

		elif rand_choice == 1:
			# Open existing file for reading
			open_mode = 1

			if ( len(self.Files.keys()) == 0 ):
				# Nothing to read -- just try a random file
				filename = self.random_string(1, 30)

				self.comment( "Failed open attempt (read) no files available" )
				self.SendOpen( filename, open_mode, -1 )	
			else:
				inode = choice(self.Files.keys())
				filename = self.Files[inode][0]	
				new_fd = self.next_fd( )
	
				if ( new_fd == None ):
					# Fail out of FDs
					self.comment( "Failed open attempt (read) out of FDs" )

					self.SendOpen( filename, open_mode, -1 )

				else:	
					self.comment( "Successful open attempt (read)" )

					self.fd[new_fd][0] = inode
					self.fd[new_fd][1] = 0

					self.SendOpen( filename, open_mode, new_fd )
		else:
			# Open read (invalid)
			# Open existing file for reading
			open_mode = 1

			if ( len(self.Files.keys()) == 0 ):
				# Nothing to read -- just try a random file
				filename = self.random_string(1, 30)

				self.comment( "Failed open attempt (read) no files available" )
				self.SendOpen( filename, open_mode, -1 )	
			else:
				# Pick a bad file to open for reading	
				filename = self.random_string(1,10)
				while filename in [self.Files[inode][0] for inode in self.Files.keys()] or len(filename) is 0:
					filename = self.random_string(1,10)
				self.comment( "Failed open attempt (read) invalid file" )
				self.SendOpen( filename, open_mode, -1 )


	def SendOpen(self, filename, open_mode, expected_retvalue):
		# Open
		self.write(self.COMMAND_OPEN)
		self.write(chr(len(filename)))
		self.write(chr(open_mode))
		self.write(filename)

		# Response
		self.read(length=4, expect=pack("<i", expected_retvalue))
		self.read(length=4, expect=pack("<I", 0))

	#############################
	# Close Tests
	#############################
	def TestClose(self):
		# are we going for a success or failure?
		rand_fd = self.get_random_fd( )
		if randint(0,2) > 0 and rand_fd is not None:
			# success
			# Close random FD
			self.fd[rand_fd][0] = 0xFFFF
			self.fd[rand_fd][1] = 0x0

			self.comment( "Successful close attempt" )

			self.SendClose( rand_fd, rand_fd )
		else:
			# Bad attempt
			bad_fd_to_close = 0
			bad_fd_to_close_count = 0
			for i in range( 0, self.MAX_FILE_DESCRIPTORS ):
				if ( self.fd[i][0] == 0xFFFF ):
					bad_fd_to_close_count += 1

			if ( bad_fd_to_close_count == 0 ):
				# All FDs in use -- pick on
				rand_fd = randint( 0, 15 )
				
				self.fd[rand_fd][0] = 0xFFFF
				self.fd[rand_fd][1] = 0x0

				self.comment( "Successful close attempt (forced -- all FDs in use)" )
	
				self.SendClose( rand_fd, rand_fd )
			else:
				bad_fd_to_close_idx = randint( 0, bad_fd_to_close_count-1 )

				cur_idx = 0
				for i in range( 0, self.MAX_FILE_DESCRIPTORS ):
					if ( self.fd[i][0] == 0xFFFF ):
						if ( cur_idx == bad_fd_to_close_idx ):
							bad_fd_to_close = i
							break
						cur_idx += 1

				self.fd[bad_fd_to_close][0] = 0xFFFF
				self.fd[bad_fd_to_close][1] = 0x0

				self.comment( "Failed close attempt (bad FD)" )
				self.SendClose( bad_fd_to_close, -1 )

	def SendClose(self, fd, expected_retvalue):
		# Close
		self.write(self.COMMAND_CLOSE)
		self.write(pack("<i", fd))

		# Response
		self.read(length=4, expect=pack("<i", expected_retvalue))
		self.read(length=4, expect=pack("<I", 0 ))
	
	def end(self):
		self.write(self.COMMAND_END)

		self.read(delim="\n", expect="Stop simulation\n" )
		pass
