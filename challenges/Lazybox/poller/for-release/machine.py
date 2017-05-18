#!/usr/bin/env python

from generator.actions import Actions,Variable
from random import *
import struct
import ctypes as ct
import sys

class MyClass(Actions):
    
    def start(self):
        # init some vars
	#self.delay(100)
	self.CSI = "\x1b\x5b"
        self.User = 'crs'
        self.Group = 'crs'
        self.CommandCount = 0

        # setup ctypes for prng functions
        self.dll = ct.CDLL('build/patched/so/CROMU_00051.so')
        self.seed_prng = self.dll.seed_prng
        self.seed_prng.argtypes = [ ct.c_uint ]
        self.seed_prng.restype = None
        self.random_in_range = self.dll.random_in_range
        self.random_in_range.argtypes = [ ct.c_uint, ct.c_uint ]
        self.random_in_range.restype = ct.c_uint

        # seed the prng from the secret page data
	self.seed_prng(ct.c_uint(struct.unpack('<L', self.magic_page[0:4])[0]))

	# generate the root password that the cb will use
        self.root_passwd = ''.join(chr(self.random_in_range(65,122)) for _ in range(10))

	# the default crs password
	self.crs_password = 'crs'

	# initial file count
	self.FileCount = 2

        # user name len
        self.UserNameLen = 5

        # file name len
        self.FileNameLen = 2

	# read the intial prompt
	self.ReadPrompt()

    def RunTests(self):
        while self.CommandCount < 11:
            test = randint(0,15)
            if test is 0:
                self.TestId()
            elif test is 1:
                self.TestPrint()
            elif test is 2:
                self.TestPrintToFile()
            elif test is 3:
                self.TestInvalidUserChuser()
            elif test is 4:
                self.TestIncorrectPwChuser()
            elif test is 5:
                self.TestChpwCrs()
            elif test is 6:
                self.TestChuserRoot()
                self.TestChpwRoot()
            elif test is 7:
                self.TestInvalidCommand()
            elif test is 8:
                self.TestCtrlU()
            elif test is 9:
                self.TestCtrlC()
            elif test is 10:
                self.TestCmdHistory()
            elif test is 11:
                self.TestCmdEdit()
            elif test is 12:
                self.TestList()
            elif test is 13:
                self.TestNewUser()
            elif test is 14:
                self.TestDelUser()
            elif test is 15:
                self.TestNewExistingUser()

        if randint(0,1) is 0:
            self.TestCtrlD()
        else:
            self.TestExit()

    def TestNewExistingUser(self):
        # if we're not the root user, su to root
	if self.User is not "root":
            self.TestChuserRoot()

        # attempt to create a user that already exists
        self.write("newuser root root\n\r")
        self.BackspaceNL(2)
        buf = "User 'root' already exists\n\r"
	self.read(length=len(buf), expect=buf)
        self.CommandCount += 1
	self.ReadPrompt()

    def TestNewUser(self):
        # if we're not the root user, su to root
	if self.User is not "root":
            self.TestChuserRoot()
        
        # create a new user
	new_user = self.random_string(self.UserNameLen,self.UserNameLen)
        self.UserNameLen += 1
        self.write("newuser "+new_user+" "+new_user+"\n\r")
        self.BackspaceNL(2)
        buf = "New user password: "
	self.read(length=len(buf), expect=buf)
	passwd = self.random_string(1,5)
        self.write(passwd+"\n\r")
        self.BackspaceNL(2)
        buf = "User '"+new_user+"' added\n\r"
	self.read(length=len(buf), expect=buf)
        self.CommandCount += 1
	self.ReadPrompt()

        # su to the new user to make sure it works
        self.TestChuser(new_user, passwd)

        return(new_user)

    def TestDelUser(self):
        # if we're not the root user, su to root
	if self.User is not "root":
            self.TestChuserRoot()

        # first create a user
        new_user = self.TestNewUser()

        # change back to the root user since TestNewUser ends as the new user
        self.TestChuserRoot()

        # delete a user
        self.write("deluser "+new_user+"\n\r")
        self.BackspaceNL(2)
        buf = "User '"+new_user+"' deleted\n\r"
	self.read(length=len(buf), expect=buf)
        self.CommandCount += 1
	self.ReadPrompt()

    def TestList(self):
        # send id command
	self.write("list\n\r");
        self.BackspaceNL(2)

        # verify response
	# first line should be Directory listing
        buf = "Directory listing\n\r"
	self.read(length=len(buf), expect=buf)
        # next is the file list including the column headers
        self.read(delim="\r", expect_format="pcre", expect=".*\s+.*\s+.*\s+.*")
	for _ in range(self.FileCount):
            self.read(delim="\r", expect_format="pcre", expect=".*\s+.*\s+.*\s+\d+")

        self.CommandCount += 1
	self.ReadPrompt()

    def TestCmdEdit(self):
        # send a partial command with extra chars
        self.write("id")
	rnd_str = self.random_string(2,2)
        self.write(rnd_str);

        # backspace over those extra chars
        self.write("\x7f")
        self.Backspace(3)
        self.write("\x7f")
        self.Backspace(3)

        # run and verify the command output
        self.write("\n\r")
        self.BackspaceNL(2)
        buf = "uid="+self.User+" gid="+self.Group+"\n\r"
	self.read(length=len(buf), expect=buf)
        self.CommandCount += 1
	self.ReadPrompt()

        # send a partial command with extra chars
        self.write("id")
	rnd_str = self.random_string(2,2)
        self.write(rnd_str);

        # arrow back over those extra chars
        # first char
        self.write("\x1b\x5b\x44")
	self.EraseLine(0)
	self.ReadPrompt()
        buf = "id"+rnd_str
	self.read(length=len(buf), expect=buf)
        buf = "\x1b\x5b1D"
	self.read(length=len(buf), expect=buf)
        # second char
        self.write("\x1b\x5b\x44")
	self.EraseLine(0)
	self.ReadPrompt()
        buf = "id"+rnd_str
	self.read(length=len(buf), expect=buf)
        buf = "\x1b\x5b2D"
	self.read(length=len(buf), expect=buf)

        # run and verify the command output
        self.write("\n\r")
        self.BackspaceNL(2)
        buf = "uid="+self.User+" gid="+self.Group+"\n\r"
	self.read(length=len(buf), expect=buf)
        self.CommandCount += 1
	self.ReadPrompt()

    def TestCmdHistory(self):
        # send a test command
        self.TestId()

        # send another command (print)
	rnd_str = self.random_string(1,10)
	self.write("print "+rnd_str+"\n\r");
        self.BackspaceNL(2)
        buf = rnd_str+"\n\r"
	self.read(length=len(buf), expect=buf)
        self.CommandCount += 1
	self.ReadPrompt()

        # up arrow once to get back to the previous command
        self.write("\x1b\x5b\x41")
        self.EraseLine(0)
	self.ReadPrompt()
        buf = "print "+rnd_str
        self.read(length=len(buf), expect=buf)
        
        # up arrow again to get back to the first command
        self.write("\x1b\x5b\x41")
        self.EraseLine(0)
	self.ReadPrompt()
        buf = "id"
	self.read(length=len(buf), expect=buf)

	# execute the first command again
        self.write("\n\r")
        self.BackspaceNL(2)
        buf = "uid="+self.User+" gid="+self.Group+"\n\r"
	self.read(length=len(buf), expect=buf)
        self.CommandCount += 1
	self.ReadPrompt()

        # up arrow, then down arrow to make sure that returns us to 
        # an empty prompt
        # up
        self.write("\x1b\x5b\x41")
        self.EraseLine(0)
	self.ReadPrompt()
        buf = "id"
	self.read(length=len(buf), expect=buf)
        # down
        self.write("\x1b\x5b\x42")
        self.EraseLine(0)
	self.ReadPrompt()
        self.write("\n\r")
        self.BackspaceNL(2)
	self.ReadPrompt()

    def TestCtrlU(self):
        # write a random string
	rnd_str = self.random_string(1,10)
	self.write(rnd_str);

        # Send ctrl-u
        self.write('\x15')

        # make sure the prompt clear and re-prints as expected
        self.EraseLine(0)
	self.ReadPrompt()

        # test a command to make sure it works
        self.TestId()

    def TestCtrlD(self):
        # first test with a partially entered command
        # start a command
	self.write("id");

        # Send ctrl-d
        self.write('\x04')

        # make sure the prompt doesn't change
        buf = '\x08\x08  \x08\x08'
	self.read(length=len(buf), expect=buf)

        # send <enter> and make sure the command runs as expected
        self.write("\n\r")
        self.BackspaceNL(2)
        buf = "uid="+self.User+" gid="+self.Group+"\n\r"
	self.read(length=len(buf), expect=buf)
	self.CommandCount += 1
	self.ReadPrompt()

        # next, send ctrl-d on a blank line and make sure it logs us out
        self.write('\x04')

        # verify the response
        buf = '\x08\x08  \x08\x08'
	self.read(length=len(buf), expect=buf)
	self.read(length=6, expect="exit  ")
        self.BackspaceNL(2)
	self.read(length=8, expect="logout\n\r")

    def TestCtrlC(self):
        # write a random string
	self.write("id");

        # Send ctrl-c
        self.write('\x03')

        # make sure it returns to the prompt without executing
        self.BackspaceNL(2)
	self.ReadPrompt()

    def TestExit(self):
	self.write("exit\n\r");
        self.BackspaceNL(2)
	self.read(length=8, expect="logout\n\r")

    def TestId(self):
        # send id command
	self.write("id\n\r");
        self.BackspaceNL(2)

        # verify response
        buf = "uid="+self.User+" gid="+self.Group+"\n\r"
	self.read(length=len(buf), expect=buf)

        self.CommandCount += 1
	self.ReadPrompt()

    def TestPrint(self):
	rnd_str = self.random_string(1,5)

        # send print command
	self.write("print "+rnd_str+"\n\r");
        self.BackspaceNL(2)

        # verify response
        buf = rnd_str+"\n\r"
	self.read(length=len(buf), expect=buf)

        self.CommandCount += 1
	self.ReadPrompt()

    def TestPrintToFile(self):
	rnd_str = self.random_string(1,5)
	rnd_file = self.random_string(self.FileNameLen,self.FileNameLen)
        self.FileNameLen += 1

        # send print command
	self.write("print "+rnd_str+" > "+rnd_file+"\n\r");
        self.BackspaceNL(2)

        # verify response
        self.CommandCount += 1
	self.ReadPrompt()

	# check that the contents of the newly created file match
	self.write("dump "+rnd_file+"\n\r");
        self.BackspaceNL(2)
        buf = rnd_str+"\n\r"
	self.read(length=len(buf), expect=buf)

        self.CommandCount += 1
        self.FileCount += 1
	self.ReadPrompt()

    def TestChuserRoot(self):
        self.TestChuser('root',self.root_passwd)

    def TestChuser(self, user, password):
        # send chuser command
        self.write("chuser "+user+"\n\r");
        self.BackspaceNL(2)

        if self.User is not 'root':
            # read password prompt
            buf = "Password: "
            self.read(length=len(buf), expect=buf)

            # send the password
            self.write(password+"\n\r");
            self.BackspaceNL(2)

	# read the success message
        buf = "Authentication success for user '"+user+"'\n\r"
	self.read(length=len(buf), expect=buf)

        self.User = user
        self.Group = user

        # prompt will have the new user name
        self.CommandCount += 1
	self.ReadPrompt()

    def TestInvalidUserChuser(self):
	invalid_user = self.random_string(5,10)

        # send chuser command
	self.write("chuser "+invalid_user+"\n\r");
        self.BackspaceNL(2)

        # read invalid user prompt
        buf = "No passwd entry for user '"+invalid_user+"'\n\r"
	self.read(length=len(buf), expect=buf)

        self.CommandCount += 1
	self.ReadPrompt()

    def TestIncorrectPwChuser(self):
        if self.User is 'root':
            return
	invalid_pw = self.random_string(5,10)

        # send chuser command
	self.write("chuser crs\n\r");
        self.BackspaceNL(2)

        # read password prompt
        buf = "Password: "
	self.read(length=len(buf), expect=buf)

        # send the password
	self.write(invalid_pw+"\n\r");
        self.BackspaceNL(2)

        # read auth failure
        buf = "Authentication failure\n\r"
	self.read(length=len(buf), expect=buf)

        self.CommandCount += 1
	self.ReadPrompt()

    def TestInvalidCommand(self):
        invalid_command = "dump"+self.random_string(1,5)

        # send command
	self.write(invalid_command+"\n\r")
        self.BackspaceNL(2)

        # verify error msg
        buf = "Invalid command: "+invalid_command+"\n\r"
        self.read(length=len(buf), expect=buf)

        self.CommandCount += 1
        self.ReadPrompt()

    def TestChpwRoot(self):
        self.TestChpw('root','asdf')

    def TestChpwCrs(self):
        self.TestChpw('crs','asdf')

    def TestChpw(self, user, new_password):
        if self.User is "root":
            # send command
            self.write("chpw "+user+"\n\r")
            self.BackspaceNL(2)
        elif self.User is "crs":
            # send command
            self.write("chpw\n\r")
            self.BackspaceNL(2)
        else:
            return

        # enter the new password
        buf = "New password: "
        self.read(length=len(buf), expect=buf)
        self.write(new_password+"\n\r")
        self.BackspaceNL(2)

        if self.User is "root":
            if user is "root":
                self.root_passwd = new_password
            if user is "crs":
                self.crs_passwd = new_password
        else:
            if user is "crs":
                self.crs_passwd = new_password

        self.CommandCount += 1
        self.ReadPrompt()

        # test the new password
        self.TestChuser(user, new_password)

    def Backspace(self, count):
        buf = "\x08"*count + " "*count + "\x08"*count
        self.read(length=len(buf), expect=buf)

    def BackspaceNL(self, count):
        buf = "\x08"*count + " "*count + "\x08"*count + "\n\r"
        self.read(length=len(buf), expect=buf)

    def ReadPrompt(self):
        buf= self.User+"@CB> "
        self.read(length=len(buf), expect=buf)

    def EraseToEOL(self):
        buf= self.CSI+"K"
        self.read(length=len(buf), expect=buf)

    def EraseLine(self, StartingX):
        buf = self.CSI+str(StartingX)+"G"
        self.read(length=len(buf), expect=buf)
        self.EraseToEOL()

    def MoveCursor(self, x, y):
        buf = self.CSI+str(x)+";"+str(y)+"H"
	self.read(length=len(buf), expect=buf)

    def CursorRight(self, NumSpaces):
        buf = self.CSI+str(NumSpaces)+"C"
	self.read(length=len(buf), expect=buf)

    def CursorLeft(self, NumSpaces):
        buf = self.CSI+str(NumSpaces)+"D"
	self.read(length=len(buf), expect=buf)

    def UpArrow(self):
        buf = self.CSI+"A"
	self.read(length=len(buf), expect=buf)

    def DownArrow(self):
        buf = self.CSI+"B"
	self.read(length=len(buf), expect=buf)

    def RightArrow(self):
        buf = self.CSI+"C"
	self.read(length=len(buf), expect=buf)

    def LeftArrow(self):
        buf = self.CSI+"D"
	self.read(length=len(buf), expect=buf)

    def end(self):
	pass

    def random_string(self, min_length, max_length):
        chars = map(chr, range(48,57)+range(65,90)+range(97,122))
        str = ''
        while len(str) < min_length:
            str = ''.join(choice(chars) for _ in range(randint(min_length, max_length))).rstrip()
        return str
