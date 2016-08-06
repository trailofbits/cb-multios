#!/usr/bin/env python
#
# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
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
from random import choice, randint

import support as sp
from common import DEBUG, CONFIG

# Plain content, send SVU as UINT32 and STI as UCHAR
# Serialized content, send SVU as UINT32, STI as UINT32, and name as series of chars.

class Liquids(object):
    def __init__(self):
        self.serialVersionUID = 0
        self.typeName = "Liquids"
        self.subTypeID = 0

    def rand_content(self):
        self.subTypeID = randint(0,4)

    def get_plain_content(self):
        pc = ''
        pc += sp.pack_single_uint32(self.serialVersionUID)
        pc += sp.pack_single_uint8(self.subTypeID)
        return pc

    def get_serialized_content(self):
        sc = ''
        sc += sp.pack_single_uint32(self.serialVersionUID)
        sc += sp.pack_single_string(self.typeName)
        sc += sp.pack_single_uint32(self.subTypeID)
        return sc

    def __eq__(self, other):
        return self.serialVersionUID == other.serialVersionUID \
                and  self.subTypeID == other.subTypeID

    def __hash__(self):
        return hash( ("serialVersionUID", self.serialVersionUID, "subTypeID", self.subTypeID))

    def __str__(self):
        return "SVU {0}, {1}, SubType {2}".format(self.serialVersionUID, self.typeName, self.subTypeID)

    def __repr__(self):
        return self.__str__()

class Cereals(object):
    def __init__(self):
        self.serialVersionUID = 1
        self.typeName = "Cereals"
        self.subTypeID = 0

    def rand_content(self):
        self.subTypeID = randint(0,6)

    def get_plain_content(self):
        pc = ''
        pc += sp.pack_single_uint32(self.serialVersionUID)
        pc += sp.pack_single_uint8(self.subTypeID)
        return pc

    def get_serialized_content(self):
        sc = ''
        sc += sp.pack_single_uint32(self.serialVersionUID)
        sc += sp.pack_single_string(self.typeName)
        sc += sp.pack_single_uint32(self.subTypeID)
        return sc

    def __eq__(self, other):
        return self.serialVersionUID == other.serialVersionUID \
                and  self.subTypeID == other.subTypeID

    def __hash__(self):
        return hash( ("serialVersionUID", self.serialVersionUID, "subTypeID", self.subTypeID))

    def __str__(self):
        return "SVU {0}, {1}, SubType {2}".format(self.serialVersionUID, self.typeName, self.subTypeID)

    def __repr__(self):
        return self.__str__()

class Toppings(object):
    def __init__(self):
        self.serialVersionUID = 2
        self.typeName = "Toppings"
        self.subTypeID = 0

    def rand_content(self):
        self.subTypeID = randint(0,4)

    def get_plain_content(self):
        pc = ''
        pc += sp.pack_single_uint32(self.serialVersionUID)
        pc += sp.pack_single_uint8(self.subTypeID)
        return pc

    def get_serialized_content(self):
        sc = ''
        sc += sp.pack_single_uint32(self.serialVersionUID)
        sc += sp.pack_single_string(self.typeName)
        sc += sp.pack_single_uint32(self.subTypeID)
        return sc

    def __eq__(self, other):
        return self.serialVersionUID == other.serialVersionUID \
                and  self.subTypeID == other.subTypeID

    def __hash__(self):
        return hash( ("serialVersionUID", self.serialVersionUID, "subTypeID", self.subTypeID))

    def __str__(self):
        return "SVU {0}, {1}, SubType {2}".format(self.serialVersionUID, self.typeName, self.subTypeID)

    def __repr__(self):
        return self.__str__()

class GenericString(object):
    def __init__(self):
        self.serialVersionUID = 3
        self.typeName = "GenericString"
        self.str = ""

    def rand_content(self):
        self.str = sp.random_string(randint(5, 25))

    def get_plain_content(self):
        pc = ''
        pc += sp.pack_single_uint32(self.serialVersionUID)
        pc += sp.pack_single_string(self.str)
        pc += sp.pack_single_char('\0')
        return pc

    def get_serialized_content(self):
        sc = ''
        sc += sp.pack_single_uint32(self.serialVersionUID)
        sc += sp.pack_single_string(self.typeName)
        sc += sp.pack_single_string(self.str)
        sc += sp.pack_single_char('\0')
        return sc

    def __str__(self):
        return "SVU {0}, {1}, Str {2}".format(self.serialVersionUID, self.typeName, self.str)

    def __repr__(self):
        return self.__str__()

class PrinterString(object):
    def __init__(self):
        self.serialVersionUID = 4
        self.typeName = "PrinterString"
        self.str = ""

    def rand_content(self):
        self.str = sp.random_string(randint(5, 25))

    def get_plain_content(self):
        pc = ''
        pc += sp.pack_single_uint32(self.serialVersionUID)
        pc += sp.pack_single_string(self.str)
        pc += sp.pack_single_char('\0')
        return pc

    def get_serialized_content(self):
        sc = ''
        sc += sp.pack_single_uint32(self.serialVersionUID)
        sc += sp.pack_single_string(self.typeName)
        sc += sp.pack_single_string(self.str)
        sc += sp.pack_single_char('\0')
        return sc

    def __str__(self):
        return "SVU {0}, {1}, Str {2}".format(self.serialVersionUID, self.typeName, self.str)

    def __repr__(self):
        return self.__str__()

class CommandRunner(object):
    def __init__(self):
        self.serialVersionUID = 5
        self.typeName = "CommandRunner"
        self.fn_addr = ''
        self.args = []

    def rand_content(self):
        self.fn_addr = 'AADD'
        self.args = [128, 1024, 4096]

    def get_plain_content(self):
        pc = ''
        pc += sp.pack_single_uint32(self.serialVersionUID)
        pc += sp.pack_single_uint16(1 + len(self.args))
        pc += sp.pack_single_string(self.fn_addr)
        pc += sp.pack_single_char(' ')
        pc += sp.pack_single_uint32(self.args[0])
        pc += sp.pack_single_char(' ')
        pc += sp.pack_single_uint32(self.args[1])
        pc += sp.pack_single_char(' ')
        pc += sp.pack_single_uint32(self.args[2])
        pc += sp.pack_single_char('\0')
        return pc

    def get_serialized_content(self):
        sc = ''
        sc += sp.pack_single_uint32(self.serialVersionUID)
        sc += sp.pack_single_string(self.typeName)
        sc += sp.pack_single_uint16(1 + len(self.args))
        sc += sp.pack_single_string(self.fn_addr)        
        sc += sp.pack_single_char(' ')
        sc += sp.pack_single_uint32(self.args[0])
        sc += sp.pack_single_char(' ')
        sc += sp.pack_single_uint32(self.args[1])
        sc += sp.pack_single_char(' ')
        sc += sp.pack_single_uint32(self.args[2])
        sc += sp.pack_single_char('\0')
        return sc

    def __str__(self):
        return "SVU {0}, {1}, fn_addr 0x{2}, args {3}".format(self.serialVersionUID, self.typeName, self.fn_addr, self.args)

    def __repr__(self):
        return self.__str__()



if __name__ == '__main__':

    b = []
    for item_type in [Liquids, Cereals, Toppings, GenericString, PrinterString, CommandRunner]:
        item = item_type()
        item.rand_content()

        print item
        print ''.join(["\\x{0:02x}".format(ord(c)) for c in item.get_plain_content()])
        print ''.join(["\\x{0:02x}".format(ord(c)) for c in item.get_serialized_content()])
        b.append(item)

    print b


