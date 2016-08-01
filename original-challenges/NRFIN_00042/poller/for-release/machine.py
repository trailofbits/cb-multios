#!/usr/bin/env python
#
# Copyright (C) 2014 
#   Brian Caswell <bmc@lungetech.com>
#   Narf Industries <info@narfindustries.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
import string
import sys
import os

from generator.actions import Actions
from random import choice,randint
from struct import *

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def get_rand_array(nspace):
    arrs = filter(lambda x: x[1] == "arr",nspace.values())
    if len(arrs) == 0:
        return None
    return choice(arrs)[0]

def get_unique_name(nspace):
    #for some stupid reason, this check isn't working
    #for now, we just make it unlikely a collision will occur
    name = random_alpha(10,16)
    while name in nspace:
        name = random_alpha(10,16)
    return name

types = ["num","arr","view"]
viewtypes = ["uint","int","ushort","short","ubyte","byte"]

class GREATVIEW(Actions):
    def start(self):
        self.nspace = {}
        self.expected = []
        self.arrs = {}
        pass
    def validnew(self):
        name = get_unique_name(self.nspace)
        ntype = choice(types)
        arg2 = ""
        cmd = ""
        if ntype == "num":
            arg1 = randint(-(2**31),2**31-1)
        elif ntype == "arr":
            arg1 = randint(1,200)
            self.arrs[name] = [0]*arg1
        elif ntype == "view":
            arg1 = get_rand_array(self.nspace)
            if not arg1:
                newarr = get_unique_name(self.nspace)
                newarrsize = randint(1,200)
                cmd += "new arr %s %s\n" % (newarr,newarrsize)
                self.nspace[newarr] = (newarr,"arr",newarrsize,arg2)
                self.arrs[newarr] = [0]*newarrsize
                arg1 = newarr
            arg2 = " "+choice(viewtypes)
        cmd += "new %s %s %s%s\n" % (ntype,name,arg1,arg2)
        if ntype != "view":
            self.nspace[name] = (name,ntype,arg1,arg2)
        else:
            self.nspace[name] = (name,ntype,arg1,[self.nspace[arg1],self.arrs[arg1]])

        self.write(cmd)
    def validget(self):
        if len(self.nspace) == 0:
            self.validnew()
        name,vtype,arg1,arg2 = choice(self.nspace.values())
        if vtype == "num":
            cmd = "get %s\n" % name
            res = str(arg1)
        elif vtype == "arr":
            idx = randint(0,arg1-1)
            cmd = "get %s %s\n"  % (name, idx)
            res = str(self.arrs[name][idx])
        else:
            #ignore views. make them figure it out :D
            return

        self.write(cmd)
        self.expected.append(res)


    def validset(self):
        if len(self.nspace) == 0:
            self.validnew()
        name,vtype,arg1,arg2 = choice(self.nspace.values())
        newval = randint(-(2**31),2**31-1)
        if vtype == "num":
            cmd = "set %s %s\n" % (name,newval)
            self.nspace[name] = (name,vtype,newval,"")
        elif vtype == "arr":
            idx = randint(0,arg1-1)
            cmd = "set %s %s %s\n" % (name,idx,newval)
            self.arrs[name][idx] = newval
        else:
            #ignore views. make them figure it out :D
            return

        self.write(cmd)

    def validdel(self):
        if len(self.nspace) == 0:
            self.validnew()
        name,vtype,arg1,arg2 = choice(self.nspace.values())
        del self.nspace[name]
        if vtype == "arr":
            del self.arrs[name]

    def end(self):
        self.expected.append("Done.")
        self.write("\x00")
        for line in self.expected:
            self.read(delim="\n",expect=line)



