from os import listdir

#reads in old makefile from folder
#parses for compiler arguments 
#creates cmake lists file with parsed arguments as parent-scope variables
def readAndMake(folder):
	inStream = open(folder+"/Makefile", "r")
	oldMake = inStream.readlines()
	inStream.close()

	makeVars = []
	for i in oldMake:
		i = i.replace("\n", "").replace("\t", "") 
		if "=" in i:
			var = i[:i.find("=")]
			val = i[i.find("=") + 1:]
			var = var.strip()
			val = val.strip()
			makeVars += ['set( ' + var + ' "' + val + '")']
	newMake = ""

	for i in makeVars:
		newMake += i + "\n"
	if "-Werror" in newMake:
		newMake = newMake.replace("-Werror", "")

	
	if "CFLAGS" not in newMake:
		newMake +=  'set( CFLAGS " ")\n' 
	#newMake += 'MESSAGE("Building!!! ")\n'
	newMake += "buildCB(${CFLAGS})"



	outStream = open(folder + "/CMakeLists.txt", "w")
	outStream.write(newMake)
	#print newMake	
	outStream.close()

#write makeFiles for all folders in path
def doAll(path):
	dirs = listdir(path)
	for folder in dirs:
		folder = path + "/" + folder
		#print folder
		if "00" in folder:
			print folder
			readAndMake(folder)


path = "../cqe-challenges"
#doAll(path)   ##path should be folder containing multiple challenge binaries and nothing else. 
readAndMake("../cqe-challenges/YAN01_00003/")  #path should be folder of a single challenge binary