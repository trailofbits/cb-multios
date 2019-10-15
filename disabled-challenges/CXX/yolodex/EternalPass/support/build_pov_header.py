#!/usr/bin/env python
#
# Copyright (C) 2015 
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
from binascii import crc32
from random import *


tmpl = '''char *%s_%s() {
    char *s = calloc(%d);
    %s
    return s;
}

'''
def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def build_header(fn):
    base_fn = fn.split("_")[0]

    with open(fn,"rb") as f:
        l = [i.strip().translate(None,";~- '/0123456789") for i in f.readlines()]

    out_txt = base_fn + "_list.h"

    with open(out_txt,"wb") as f:
        f.write("char * %s_list[4096] = {" % base_fn)
        for w in l:
            f.write('"%s",\n' % w)
        f.write("};\n");

def main():
    #import lists
    build_header("adjectives_sample.txt")
    build_header("adverbs_sample.txt")
    build_header("nouns_sample.txt")
    build_header("verbs_sample.txt")


if __name__=="__main__":
    main()
