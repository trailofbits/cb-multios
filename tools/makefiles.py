#!/usr/bin/env python
from os import listdir
import re

#reads in old makefile from folder
#parses for compiler arguments 
#creates cmake lists file with parsed arguments as parent-scope variables
def readAndMake(folder):
    inStream = open(folder+"/Makefile", "r")
    oldMake = inStream.readlines()
    inStream.close()

    makeVars = {'CFLAGS': '-fno-builtin -Wno-int-to-pointer-cast '}
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
    dirs = listdir(path)
    for folder in dirs:
        folder = path + "/" + folder
        #print folder
        if "00" in folder:
            print folder
            readAndMake(folder)

if __name__ == '__main__':
    path = "../cqe-challenges"
    doAll(path)   ##path should be folder containing multiple challenge binaries and nothing else.
