#!/usr/bin/env python

from generator.actions import Actions
from struct import *
from random import *
import numpy as np
import binascii

class TimeGen():
	def __init__(self, magic_page, magic_page_size ):
		self.magic_page = magic_page
		self.generator_size = magic_page_size

		self.last_timestamp = 1452975638
		self.last_mix = 0

		self.last_pos = 0

		self.GENERATOR_ROUNDS = 20

	def GetUnixTimestamp(self):
		new_delta = self.GetGeneratorMix()

		new_delta = new_delta % 120

		self.last_timestamp = (self.last_timestamp + new_delta)

		#print "Timestamp: %d\n" % self.last_timestamp
		return (self.last_timestamp)

	def GetGeneratorMix(self):
		a = np.uint32(self.last_mix)
		b = np.uint32(0)
		c = np.uint32(0)

		pos = self.last_pos
		i = 0
		while i < self.GENERATOR_ROUNDS:
			if ( pos > self.generator_size ):
				pos = 0

			c = ((a * 3) & 0xFFFFFFFF )
			b = ((np.left_shift( c, 7 ) & 0xFFFFFFFF) ) ^ b
			a = (b + (self.magic_page[pos] & 0xAA11AA11) % 731) & 0xFFFFFFFF

			pos += 1
			i += 1

		self.last_pos = pos

		self.last_mix = (((np.right_shift(a, 13) & 0xFFFFFFFF ) | ((np.left_shift( b, 13) & 0xFFFFFFFF ))) ^ c)

		return self.last_mix

class MyClass(Actions):

    def start(self):
        self.delay(50)
        self.CFS_LOGIN          = "\x00"
        self.CFS_DIR            = "\x01"
        self.CFS_READ           = "\x02"
        self.CFS_WRITE          = "\x03"
        self.CFS_WRITE_APPEND   = "\x04"
        self.CFS_DEL            = "\x05"
        self.CFS_RENAME         = "\x06"

        self.RESP_SUCCESS               = "\x00"
        self.RESP_LOGIN_FAILED          = "\x01"
        self.RESP_SYSTEM_FAILURE        = "\x02"
        self.RESP_INVALID_FILE          = "\x03"
        self.RESP_DELETE_FAILED         = "\x04"
        self.RESP_RENAME_FAILED         = "\x05"
        self.RESP_TOO_MANY_OPEN_FILES   = "\x06"

	self.timegen = TimeGen( np.fromstring( self.magic_page, dtype=np.uint32 ), len(self.magic_page)/4 )
        
	self.User = "root"
        self.Password = "rootpasswd"
        self.MaxFiles = 10
        self.Files =  { 0: ['passwd', 15, self.User+":"+self.Password, self.timegen.GetUnixTimestamp()]}
        self.LoggedIn = 0


    #############################
    # Helper Funtions
    #############################
    def NextInode(self):
        for inode in range (0, self.MaxFiles):
            if inode not in self.Files.keys():
                return inode

    def FindInode(self, filename):
        for inode in sorted(self.Files.keys()):
            if self.Files[inode][0] is filename:
                return inode

    def random_string(self, min_length, max_length):
            return ''.join(chr(randint(1,255)) for _ in range(randint(min_length, max_length)))

    #############################
    # Login Tests
    #############################
    def TestLogin(self):
        while self.LoggedIn is not 1:
            # are we going for a success or failure?
            if randint(0,1):
                # success
                self.comment("Successful login attempt")
                self.SendLogin(self.User, self.Password, self.RESP_SUCCESS)
                self.LoggedIn = 1
            else:
                # failure
                self.comment("Bad login attempt")
                BadUser = self.random_string(1,10)
                BadPassword = self.random_string(1,10)
                self.SendLogin(BadUser, BadPassword, self.RESP_LOGIN_FAILED)

    def SendLogin(self, username, password, code):
	# CFS_LOGIN
        self.write(self.CFS_LOGIN)
	self.write(chr(len(username)))
	self.write(chr(len(password)))
        self.write(username+password)

        # response
        self.read(length=1, expect=self.CFS_LOGIN)
        self.read(length=1, expect=code)
        self.read(length=2, expect=pack("<H", 0))

    #############################
    # Dir Tests
    #############################
    def TestDir(self):
        # there aren't any real failure scenarios to test with a basic Dir
        # so just run it
        self.comment("Successful dir attempt")
        self.SendDir()

    def SendDir(self):
        # CFS_DIR
        self.write(self.CFS_DIR)

        # response
        self.read(length=1, expect=self.CFS_DIR)
        self.read(length=1, expect="\x00")
        self.read(length=2, expect=pack("<H", 91*(len(self.Files.keys())+1)))
        self.read(length=91, expect="{:<32} {:<32} {:<8} {:<4} {:<10}\n".format("Filename", "Owner", "Size", "Mode", "Timestamp"))
       	
	sorted_dir_list = { } 
	#print "Unsorted: "
	for inode in sorted(self.Files.keys()):
		#print ("{:<32} {:<32} {:<8} {:<4}\n".format(binascii.hexlify(self.Files[inode][0]), "root", self.Files[inode][1], "rw--"))
		sorted_dir_list[self.Files[inode][0]] = [ self.Files[inode][0], self.Files[inode][1], self.Files[inode][2], self.Files[inode][3] ]

	#print "Sorted: "
	for dir_file_name in sorted(sorted_dir_list):
            filename = sorted_dir_list[dir_file_name][0]
	    size = sorted_dir_list[dir_file_name][1]
	    timestamp = sorted_dir_list[dir_file_name][3]
	    #print ("{:<32} {:<32} {:<8} {:<4}\n".format(binascii.hexlify(filename), "root", size, "rw--"))
            self.read(length=91, expect="{:<32} {:<32} {:<8} rw-- {:<10}\n".format(filename, "root", size, timestamp))

    #############################
    # Read Tests
    #############################
    def TestRead(self):
        # are we going for a success or failure?
        if randint(0,1):
            # success
            self.comment("Successful read attempt")
            inode = choice(self.Files.keys())
            filename = self.Files[inode][0]
            contents = self.Files[inode][2]
            offset = randint(0, len(contents)-1)
            length = randint(1, len(contents)-offset)
            expected_string = contents[offset:offset+length]
            self.SendRead(filename, offset, length, self.RESP_SUCCESS, expected_string)
        else:
            # failure
            if randint(0,1) is 0:
                # invalid file
                self.comment("Bad read attempt: invalid file")
                filename = self.random_string(1,10)
                while filename in [self.Files[inode][0] for inode in self.Files.keys()] or len(filename) is 0:
                    filename = self.random_string(1,10)
                offset = 0
                length = 0
                expected_string = ""
                self.SendRead(filename, offset, length, self.RESP_INVALID_FILE, expected_string)
            else:
                # invalid offset
                self.comment("Bad read attempt: invalid offset")
                inode = choice(self.Files.keys())
                filename = self.Files[inode][0]
                offset = len(self.Files[inode][2])+1
                length = randint(1,10)
                expected_string = ""
                self.SendRead(filename, offset, length, self.RESP_SYSTEM_FAILURE, expected_string)

    def SendRead(self, filename, offset, length, code, expected_string):
        # CFS_READ
        self.write(self.CFS_READ)
        self.write(pack("<L",offset))
        self.write(pack("<H",length))
        self.write(chr(len(filename)))
        self.write(filename)

        # response
        self.read(length=1, expect=self.CFS_READ)
        self.read(length=1, expect=code)
        if code is self.RESP_SUCCESS:
            self.read(length=2, expect=pack("<H", len(expected_string)))
        else:
            self.read(length=2, expect=pack("<H", 0))
        if code is self.RESP_SUCCESS:
            self.read(length=len(expected_string), expect=expected_string)

    #############################
    # Write Tests
    #############################
    def TestWrite(self):
        # check if we're at the max number of files 
        if self.MaxFiles is not len(self.Files.keys()):
            # success
            self.comment("Successful write attempt")
            filename = self.random_string(1,10)
            while filename in [self.Files[inode][0] for inode in self.Files.keys()] or len(filename) is 0:
                filename = self.random_string(1,10)
            string = self.random_string(1,254)
            self.SendWrite(filename, string, self.RESP_SUCCESS)
        else:
            # failure
            self.comment("Bad write attempt: too many files")
            filename = self.random_string(1,10)
            while filename in [self.Files[inode][0] for inode in self.Files.keys()] or len(filename) is 0:
                filename = self.random_string(1,10)
            string = self.random_string(1,254)
            self.SendWrite(filename, string, self.RESP_INVALID_FILE)

    def SendWrite(self, filename, string, code):
        # CFS_WRITE
        self.write(self.CFS_WRITE)
        self.write(pack("<H", len(string)))
        self.write(chr(len(filename)))
        self.write(filename)
        self.write(string)

        # response
        self.read(length=1, expect=self.CFS_WRITE)
        self.read(length=1, expect=code)
        self.read(length=2, expect=pack("<H", 0))

        # update the Files list
        if code is self.RESP_SUCCESS:
            self.Files[self.NextInode()] = [ filename, len(string), string, self.timegen.GetUnixTimestamp() ]

    #############################
    # Write Append Tests
    #############################
    def TestWriteAppend(self):
        # if the only file is passwd, write a file first
        if len(self.Files.keys()) is 1:
            filename = self.random_string(1,10)
            while filename in [self.Files[inode][0] for inode in self.Files.keys()] or len(filename) is 0:
                filename = self.random_string(1,10)
            string = self.random_string(1,254)
            self.SendWrite(filename, string, self.RESP_SUCCESS)

        # are we going for a success or failure?
        if randint(0,1):
            # success
            self.comment("Successful write append attempt")
            # pick a vaild file that's not the passwd file
            inode = choice(self.Files.keys())
            while inode is 0:
                inode = choice(self.Files.keys())
    
            # Append some bytes to it
            filename = self.Files[inode][0]
            string = self.random_string(1,10)
            self.SendWriteAppend(filename, string, self.RESP_SUCCESS)
        else:
            # failure
            self.comment("Bad write append attempt: invalid file")
            filename = self.random_string(1,10)
            while filename in [self.Files[inode][0] for inode in self.Files.keys()] or len(filename) is 0:
                filename = self.random_string(1,10)
            string = self.random_string(1,10)
            self.SendWriteAppend(filename, string, self.RESP_INVALID_FILE)


    def SendWriteAppend(self, filename, string, code):
        # CFS_WRITE
        self.write(self.CFS_WRITE_APPEND)
        self.write(pack("<H", len(string)))
        self.write(chr(len(filename)))
        self.write(filename)
        self.write(string)

        # response
        self.read(length=1, expect=self.CFS_WRITE_APPEND)
        self.read(length=1, expect=code)
        self.read(length=2, expect=pack("<H", 0))

        # update the Files list
        if code is self.RESP_SUCCESS:
            if filename in [self.Files[inode][0] for inode in self.Files.keys()]:
                # file already exists
                if code is self.RESP_SUCCESS:
                    self.Files[self.FindInode(filename)][1] += len(string)
                    self.Files[self.FindInode(filename)][2] += string
            else:
                # new file
                if code is self.RESP_SUCCESS:
                    self.Files[self.NextInode()] = [ filename, len(string), string, self.timegen.GetUnixTimestamp() ]

    #############################
    # Delete Tests
    #############################
    def TestDel(self):
        # if the only file is passwd, write a file first
        if len(self.Files.keys()) is 1:
            filename = self.random_string(1,10)
            while filename in [self.Files[inode][0] for inode in self.Files.keys()] or len(filename) is 0:
                filename = self.random_string(1,10)
            string = self.random_string(1,254)
            self.SendWrite(filename, string, self.RESP_SUCCESS)

        # are we going for a success or failure?
        if randint(0,1):
            # success
            self.comment("Successful delete attempt")
            # pick a vaild file that's not the passwd file
            inode = choice(self.Files.keys())
            while inode is 0:
                inode = choice(self.Files.keys())
            filename = self.Files[inode][0]
            self.SendDel(filename, self.RESP_SUCCESS)

        else:
            self.comment("Bad delete attempt: invalid file")
            filename = self.random_string(1,10)
            while filename in [self.Files[inode][0] for inode in self.Files.keys()] or len(filename) is 0:
                filename = self.random_string(1,10)
            self.SendDel(filename, self.RESP_DELETE_FAILED)

    def SendDel(self, filename, code):
        # CFS_DEL
        self.write(self.CFS_DEL)
        self.write(chr(len(filename)))
        self.write(filename)

        # response
        self.read(length=1, expect=self.CFS_DEL)
        self.read(length=1, expect=code)
        self.read(length=2, expect=pack("<H", 0))

        if code is self.RESP_SUCCESS:
            # delete the file from the list
            del self.Files[self.FindInode(filename)]

    #############################
    # Rename Tests
    #############################
    def TestRename(self):
        # if we only have the 'passwd' file, write one more
        while len(self.Files.keys()) < 3:
            filename = self.random_string(1,10)
            while filename in [self.Files[inode][0] for inode in self.Files.keys()] or len(filename) is 0:
                filename = self.random_string(1,10)
            string = self.random_string(1,254)
            self.SendWrite(filename, string, self.RESP_SUCCESS)
            
        # are we going for a success or failure?
        if randint(0,1):
            # success
            self.comment("Successful rename attempt")

            # pick a vaild file that's not the passwd file
            inode = choice(self.Files.keys())
            while inode is 0:
                inode = choice(self.Files.keys())
            oldfilename = self.Files[inode][0]

            # pick a file that's not in the list at all
            newfilename = self.random_string(1,10)
            while newfilename in [self.Files[inode][0] for inode in self.Files.keys()] or len(newfilename) is 0:
                newfilename = self.random_string(1,10)

            self.SendRename(oldfilename, newfilename, self.RESP_SUCCESS)

        else:
            # failure
            if randint(0,1):
                # pick an invalid source file
                oldfilename = self.random_string(1,10)
                while oldfilename in [self.Files[inode][0] for inode in self.Files.keys()] or len(oldfilename) is 0:
                    oldfilename = self.random_string(1,10)

                # pick a file that's not in the list at all
                newfilename = self.random_string(1,10)
                while newfilename in [self.Files[inode][0] for inode in self.Files.keys()] or len(newfilename) is 0:
                    newfilename = self.random_string(1,10)

                self.SendRename(oldfilename, newfilename, self.RESP_RENAME_FAILED)
            else: 
                # pick a valid source file 
                oldinode = choice(self.Files.keys())
                while oldinode is 0:
                    oldinode = choice(self.Files.keys())
                oldfilename = self.Files[oldinode][0]

                # pick a new file that already exists
                inode = choice(self.Files.keys())
                while inode is 0 or oldinode is inode:
                    inode = choice(self.Files.keys())
                newfilename = self.Files[inode][0]

                self.SendRename(oldfilename, newfilename, self.RESP_RENAME_FAILED)

    def SendRename(self, oldfilename, newfilename, code):
        # CFS_RENAME
        self.write(self.CFS_RENAME)
        self.write(chr(len(oldfilename)))
        self.write(chr(len(newfilename)))
        self.write(oldfilename)
        self.write(newfilename)

        # response
        self.read(length=1, expect=self.CFS_RENAME)
        self.read(length=1, expect=code)
        self.read(length=2, expect=pack("<H", 0))

        if code is self.RESP_SUCCESS:
            # change the filename
            self.Files[self.FindInode(oldfilename)][0] = newfilename

    def end(self):
	pass
