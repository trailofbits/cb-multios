#!/usr/bin/python

from generator.actions import Actions
import random
import re
import subprocess
import sys
from math import sin

class CGCfs(Actions):
	def start(self):
		self.read(delim='\n', expect="Welcome to the cgcfs shell!\n")
		self.read(delim='% ', expect="Type help for a list of available commands.\n")

	def full_random_string(self, min_length, max_length):
		chars = map(chr, range(1,10)+range(11,32)+range(35,47)+range(48,255))
		str = ''
		while len(str) < min_length:
			str = ''.join(random.choice(chars) for _ in range(random.randint(min_length, max_length))).rstrip()
		return str

	def random_string(self, min_length, max_length):
		chars = map(chr, range(48,57)+range(65,90)+range(97,122))
		str = ''
		while len(str) < min_length:
			str = ''.join(random.choice(chars) for _ in range(random.randint(min_length, max_length))).rstrip()
		return str

	def nondiverse_random_string(self):
		chars = '!#/?"'
		return random.choice(chars)

	def CreateFile(self, contents, fname):
		self.write("echo \"" + contents + "\" > " + fname + "\n");
		self.read(delim='% ', expect="file created\n")

	def AppendFile(self, contents, fname):
		self.write("echo \"" + contents + "\" >> " + fname + "\n");
		self.read(delim='% ', expect="")

	def MkFolder(self, folder):
		self.write("mkfolder " + folder + "\n")
		self.read(delim='% ', expect="directory created\n")

	def MkRndFolder(self, parent="/"):
		if not parent.endswith("/"):
			parent += "/"
		rnd_str = self.full_random_string(1,207)
		self.MkFolder(rnd_str)
		return parent+rnd_str

	def DelFolder(self, folder):
		self.write("delfolder " + folder + "\n")
		self.read(delim='% ', expect="directory removed\n")
			
	def FileTooLarge(self):
		folder = self.random_string(208, 208)
		self.write("mkfolder " + folder + "\n")
		self.read(delim='% ', expect="file name too large\n")

	def MkFolderExists(self):
		folder = "/" + self.full_random_string(10,20)
		self.MkFolder(folder)
		self.write("mkfolder " + folder + "\n")
		self.read(delim='% ', expect="directory exists\n")

	def MkFolderFileExists(self):
		folder = "/" + self.random_string(10,20)
		self.CreateFile("AAAAAA", folder)
		self.write("mkfolder " + folder + "\n")
		self.read(delim='% ', expect="file exists\n")

	def MissingParentFolder(self):
		folder = "/" + self.random_string(1,10)  + "/" + self.random_string(1,10)
		self.write("mkfolder " + folder + "\n")
		self.read(delim='% ', expect="parent directory doesn't exist\n")
		
	def RemoveFolder(self):
		self.DelFolder(self.MkRndFolder())

	def RemoveNonexistentFolder(self):
		self.write("delfolder /noexists\n")
		self.read(delim='% ', expect="directory does not exist\n")

	def RemoveDirectoryFile(self):
		fname = "/" + self.random_string(10,20)
		self.CreateFile("AAAAA", fname)
		self.write("delfolder " + fname + "\n")
		self.read(delim='% ', expect="not a directory\n")
		
	def RemoveRootDirectory(self):
		self.write("delfolder /\n")
		self.read(delim='% ', expect="unable to remove /\n")

	def RemoveInUseDirectory(self):
		folder = self.MkRndFolder()
		self.CreateFile("AAAAA", folder+"/test")
		self.write("delfolder " + folder + "\n")
		self.read(delim='% ', expect="directory not empty\n")
		
	def DeleteFile(self):
		fname = "/" + self.random_string(10,20)
		self.CreateFile("AAAAA", fname)
		self.write("delete " + fname + "\n")
		self.read(delim='% ', expect="file removed\n")

	def DeleteNonexistentFile(self):
		self.write("delete /noexists\n")
		self.read(delim='% ', expect="file doesn't exist\n")

	def DeleteFileDirectory(self):
		folder = self.MkRndFolder()
		self.write("delete " + folder + "\n")
		self.read(delim='% ', expect="file is a directory\n")

	def AppendDirectory(self):
		folder = self.MkRndFolder()
		self.write("echo AAAAA >> " + folder + "\n");
		self.read(delim='% ', expect="file is a directory\n")

	def ShowDirectory(self):
		folder = "/test"
		self.MkFolder(folder)
		self.write("show\n")
		self.read(delim='% ', expect="Directory listing of /\nd test                                               0\n")
		
	def ShowNoDirectory(self):
		fname = "/" + self.random_string(10,20)
		self.write("show " + fname + "\n")
		self.read(delim='% ', expect="No such directory\n")

	def ShowNotDirectory(self):
		fname = "/" + self.random_string(10,20)
		self.CreateFile("AAAAA", fname)
		self.write("show " + fname + "\n")
		self.read(delim='% ', expect="File is not a directory\n")

	def DumpFile(self):
		fname = "/" + self.random_string(10,20)
		rnd_str = self.random_string(10,50)
		self.CreateFile(rnd_str, fname)
		rnd_str += "\n"
		self.write("dump " + fname + "\n")
		self.read(delim='% ', expect=rnd_str)

	def TooManyArgs(self):
		self.write("1 2 3 4 5 6 7 8 9\n")
		self.read(delim='% ', expect="too many args\n")
