# Provided a path to a blob of random data, produce a horrible C function 
# capable of returning it when queried.  This script is almost as horrible as 
# the resulting C.

# Assumes a blob length that is a multiple of 4.

import struct

SZ_WORD = 4

def doit():
	blob = open("switch.blob", "rb").read()

	c_bgn = \
"#include \"static.h\"\n\
\n\
size_t static_switch(size_t idx) {\n\
	switch (idx) {\n"

	case = list()
	for i in range(0, len(blob), SZ_WORD):
		case.append(\
"		case 0x%08x:\n\
			return 0x%08x;\n" % \
					(i, struct.unpack("<L", blob[i:i+SZ_WORD])[0]))
	c_end = \
"		default:\n\
			return 0xdeadbeef;\n\
	}\n\
}\n"

	c = "".join([c_bgn, "".join(case), c_end])

	open("../src/switch.c", "w").write(c)

if __name__ == "__main__":
	doit()