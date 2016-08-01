#!/usr/bin/env python
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

import sys
from re import sub
from random import *

COPYRIGHT = '''/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
'''

PYCOPYRIGHT = '''# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
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
'''

fn_names = [
                "ntohll",
                "ntohl",
                "ntohs",
                "letohll",
                "letohl",
                "letohs",
                "byte",
                "lv",
                "string",
                "float",
                "double",
                "nextproto_b",
                "nextproto_s",
]

MAX_FIELDS = 50
MAX_NEXT = 100
MAX_PKT_SIZE = 1000
NUM_DISSECTORS = 10000


CF_TEMPLATE = COPYRIGHT+'''#include "libc.h"
#include "cablegrind.h"
#include "cablegrindprotos.h"
#include "helpers.h"

%s
'''

HF_TEMPLATE = COPYRIGHT+'''#ifndef CABLEGRINDPROTOS_H
#define CABLEGRINDPROTOS_H
%s

#endif'''
FN_PROTO_TEMPLATE = "void process_%s(uint8_t **, int *);\n"

PF_TEMPLATE = COPYRIGHT+'''//this file exists solely so we can keep this
//out of cablegrind.c
void (*rofl_dissectors[]) (uint8_t **payload, int *size) = {%s};
void (*lol_dissectors[]) (uint8_t **payload, int *size) = {%s};
'''

DISSECTOR_TEMPLATE = '''STACKPROTECTINIT
void process_%s(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {%s};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===%s===")-1,"===%s===");
%s
STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)) next_dissectors[next](payload,size);
}
'''
FN_TEMPLATE = "handle_%s(payload, size);\n"
NEXT_TEMPLATE = "next = handle_%s(payload,size);\n"

PI_TEMPLATE = PYCOPYRIGHT+'''
rofl = %s
lol  = %s
pollinfo = %s
'''

def build_dissector(dissectors,pollinfo,words,
        max_fields=MAX_FIELDS,max_pkt_size=MAX_PKT_SIZE):
    fn = "STACKPROTECTINIT\n"
    name = sub(r'\W+','',"".join(sample(words,2)))
    #created for corner case in which first entry might need nextproto to refer to
    dissectors[name] = ""
    pollinfo[name] = ([],[])
    body,hasnext = [],random() < 0.3
    for i in range(randint(0,MAX_FIELDS)):
        fn = choice(fn_names)
        if fn.find("next") == -1:
            body.append(FN_TEMPLATE%fn)
            pollinfo[name][1].append(fn)
        elif hasnext: #decided to allow multiple "next" fields for more complexity
            body.append(NEXT_TEMPLATE%fn)
            pollinfo[name][1].append(fn)

    next_dissectors = []
    if hasnext:
        next_dissectors = sample(dissectors,randint(0,len(dissectors))%MAX_NEXT)
    pollinfo[name][0].extend(next_dissectors)
    next_dissectors = ",".join(['process_'+i for i in next_dissectors])

    dissectors[name] = DISSECTOR_TEMPLATE % (name, next_dissectors, name, name, 
                                                 "".join(body))

def main():
    if len(sys.argv) > 2:
        sys.exit("Usage: %s [num_dissectors]" % sys.argv[0])
    header = open("cablegrindprotos.h","wb")
    code = open("cablegrindprotos.c","wb")
    phy = open("phydissectors.h","wb")
    poll = open("pollinfo.py","wb")

    ndissect = NUM_DISSECTORS if len(sys.argv) == 1 else int(sys.argv[1])
    words = [i.strip() for i in open("words").readlines()]

    dissectors,pollinfo = {},{}
    for i in range(ndissect):
        build_dissector(dissectors,pollinfo, words)

    #build and write header files
    rofl = ",".join("process_"+i for i in dissectors if choice([True,False]))
    lol = ",".join("process_"+i for i in dissectors if choice([True,False]))
    phy.write(PF_TEMPLATE%(rofl,lol))
    phy.close()
    protos = "".join(FN_PROTO_TEMPLATE%i for i in dissectors)
    header.write(HF_TEMPLATE%protos)
    header.close()

    #build and write code file
    code.write(CF_TEMPLATE%"".join(dissectors.values()))
    code.close()

    #build and write pollinfo file
    poll.write(PI_TEMPLATE%(rofl.split(","),lol.split(","),pollinfo))
    poll.close()


if __name__=="__main__":
    main()
