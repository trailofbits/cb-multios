#!/usr/bin/env python
import os
import re

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
CHAL_DIR = os.path.join(os.path.dirname(TOOLS_DIR), 'cqe-challenges')

#reads in old makefile from folder
#parses for compiler arguments 
#creates cmake lists file with parsed arguments as parent-scope variables
def readAndMake(folder):
    inStream = open(folder+"/Makefile", "r")
    oldMake = inStream.readlines()
    inStream.close()

    makeVars = {'CFLAGS': '-fno-builtin -Wno-int-to-pointer-cast -Wno-writable-strings -nostdinc '}
    for line in oldMake:
        line = re.sub('[\r\n\t]', '', line)
        if "=" in line:
            var, val = line.split('=', 1)
            var = var.strip()
            val = val.strip()
            if var == "CFLAGS":
                makeVars[var] += val.replace('-Werror', '')
            else:
                makeVars[var] = val

    newMake = ""
    for var, val in makeVars.iteritems():
        newMake += 'set( {} "{}" )\n'.format(var, val)
    newMake += 'buildCB(${CFLAGS})'

    outStream = open(folder + "/CMakeLists.txt", "w")
    outStream.write(newMake)
    outStream.close()

#write makeFiles for all folders in path
def doAll(path):
    dirs = os.listdir(path)
    for folder in dirs:
        folder = path + "/" + folder
        #print folder
        if "00" in folder:
            print folder
            readAndMake(folder)

if __name__ == '__main__':
    doAll(CHAL_DIR)   ##path should be folder containing multiple challenge binaries and nothing else.
