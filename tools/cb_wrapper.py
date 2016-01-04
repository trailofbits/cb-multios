import subprocess
import os
COMPLETED = 0 #start at a specfic binary and continue from there if interrupted. 

def CBtestResult(directory, cbName, povName):
	""" return result of testing one challenge binary
		params:	
			directory: string of file path to folder of challenge binary
			cbName: string of name of challenge binary to run 
			povName: string name of POV to run tests with
		return:
			if err, return err
			else return output of the tests
	"""
	p = subprocess.Popen(['./cb-test', '--cb', '%s' % cbName, '--directory', 
		'%s' % directory + "/bin/" , 
		'--xml', '%s/pov/%s' % (directory, povName)],  
	stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	out,err = p.communicate()
	if len(err) > 0:
		return str(err)
	print "Finished testing %s %s." % (cbName,povName)
	return out

def writePOVTest(directory, cbName, povName, output_dir):
	cbRet = CBtestResult(directory, cbName, povName)
	f = open(output_dir + "/" + cbName + povName + ".txt", "w")
	f.write(str(cbRet))
	f.close()

def runOneAndPrint(cbName, povName):
	dirName = "../cb-multios/cqe-challenges/" + cbName
	cbRet = CBtestResult(dirName, cbName , povName)
	print cbRet

def runAndWriteAllPovs(directory, cbName, output_dir):
	"""	Run all POVs for a given challenge binary
		params:
			directory: string of file path to folder of challenge binary
			cbName: string of name of challenge binary to run 
		return:
			None
	"""
	if (os.path.isdir(directory + "/pov/")):
		povs = os.listdir(directory + "/pov/")
		for povName in povs:
			if not (".xml" in povName ):
				povs.remove(povName)
			writePOVTest(directory, cbName, povName, output_dir)


def runAllCBs(directory, output_dir):
	""" Run all POVs on all challenge binaries in the given folder (ie: cqe-challenges)
		Prints output of the tests to the output_dir with name of cb
		params:	
			directory: string of directory containing challenge binary folders
			output_dir: directory to store output of tests
		return: 
			None
	"""
	cb_dirs = os.listdir(directory)
	cb_dirs = cb_dirs[COMPLETED:] #don't repeat ones I've already done
	for cb_dir in cb_dirs:
		if len(cb_dir) != 11:
			print "removing " + cb_dir
			cb_dirs.remove(cb_dir)
		runAndWriteAllPovs(directory + cb_dir, cb_dir, output_dir)
		runAndWriteAllPovs(directory + cb_dir, cb_dir + "_patched", output_dir)


print "imported cb-wrapper"
# runAllPovs("../cb-multios/cqe-challenges/CADET_00001/", "CADET_00001")
if __name__ == "__main__":
	
	print "running against all challenge binaries."
	runAllCBs("../cb-multios/cqe-challenges/", "testing_output")
