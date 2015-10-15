from os import listdir
from os.path import isdir, isfile
from sys import argv
from os import system


##Actually works recursively
#currently set to, when run, replace command line args with cgc_[orignal phrase]
#recursively for all files in the path
#Replaces all command line args in below directories recursively with cgc_arg

def replaceInFile(file, replaceThis, withThis):
	inStream = open(file, "r")
	fileText = inStream.read()

	inStream.close()
	fileWords = fileText.split(" ")
	fileFixed = []

	for w in fileWords:
		fileFixed += [ w.replace(replaceThis, withThis) ]
	fileFixed = " ".join(fileFixed)

	#write out the file
	outStream = open(file,"w")
	outStream.write(fileFixed)
	outStream.close()


##recursively replaces words in all files in directories, and their subdirs, and so on

def runInDirectory(path, replaceThis, withThis):
	#ensure that directory contains only files that you wish to change
	fileList = listdir(path) #change to go to dif directory
	for f in fileList:
		if "cgc_replacer.py" not in f:  #dont overwrite yourself
			f = path + "/" + f
			if isdir(f) : #is directory, replace inthat directory
				print "runnin in directory " + f
				runInDirectory(f, replaceThis, withThis)
			elif isfile(f):   #is file, replace the words
				print "runnin on file " + f
				replaceInFile(f, replaceThis, withThis)
			else:
				print"Not file or directory: " + f
				
def replaceList(replaceThese, here):
	replaceThis = ""
	withThis = ""
	for i in replaceThese:
		replaceThis = i
		withThis = "cgc_" + replaceThis
		runInDirectory(here, replaceThis, withThis)

def removeCache(here):
	dirs = os.listdir(here)
	dirs.pop(0) #remove .ds_store
	for i in dirs:
		os.system("rm -r " + path + "/" + i + "/bin/CMakeFiles")


replaceThese = []


numReplace = len(argv) - 1
for i in range(numReplace):
	i += 1
	replaceThese += [argv[i]]

#path = "../cqe-challenges/" 

#replaceList(replaceThese, path)
#removeCache(path)




