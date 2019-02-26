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

def build_c(fn):
    base_fn = fn.split(".")[0]

    with open(fn,"rb") as f:
        s = set([i.strip().translate(None,";~- '/0123456789") for i in f.readlines()])
        l = sample(s, 4096)

    out_txt = base_fn + "_sample.txt"

    with open(out_txt,"wb") as f:
        f.write("\n".join(l))

    out_c = base_fn + ".c"

    with open(out_c, "wb") as f:
        f.write("#include <libc.h>\n#include \"malloc.h\"\n#include \"crc32.h\"\n\n")

        for word in l:
            strcat_list = []
            for c in word:
                out = []
                if randint(0,1):
                    rstr = random_alpha(5,15) 
                    out.append('if (crc32("%s",%d) == %d) strcat(s, "%s");' % 
                            (rstr, len(rstr), (randint(1,0xffffffff)+(crc32(rstr)&0xffffffff))&0xffffffff,
                             choice(string.letters)))
                rstr = random_alpha(5,15) 
                out.append('if (crc32("%s",%d) == %d) strcat(s, "%s");' % 
                        (rstr, len(rstr), crc32(rstr)&0xffffffff, c))
                strcat_list.append("\n".join(out))
            f.write(tmpl % (word, base_fn, len(word)+1, "\n".join(strcat_list)))

        f.write("\nchar *(*%s_list[4096])() = {\n" % base_fn)

        for word in l:
            f.write("%s_%s,\n" % (word,base_fn))

        f.write("};\n");
    
    out_h = base_fn + ".h"

    with open(out_h, "wb") as f:
        f.write('''#ifndef %s_H
char *(*%s_list[4096])();
#endif''' % (base_fn,base_fn));
            

def main():
    #import lists
    build_c("adjectives.txt")
    build_c("adverbs.txt")
    build_c("nouns.txt")
    build_c("verbs.txt")


if __name__=="__main__":
    main()
