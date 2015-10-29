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
			if (var == "CFLAGS"):
				makeVars += ['set( ' + var + ' "' + val + ' -fno-builtin -Wno-int-to-pointer-cast ")']
			else:
				makeVars += ['set( ' + var + ' "' + val + '")']
	newMake = ""

	for i in makeVars:
		newMake += i + "\n"
	# if "-Werror" in newMake:
	# 	newMake = newMake.replace("-Werror", "")

	
	if "CFLAGS" not in newMake:
		newMake +=  'set( CFLAGS " -fno-builtin ")\n' 
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
doAll(path)   ##path should be folder containing multiple challenge binaries and nothing else. 
# readAndMake("../cqe-challenges/NRFIN_00010/")  #path should be folder of a single challenge binary
# readAndMake("../cqe-challenges/NRFIN_00013/") 