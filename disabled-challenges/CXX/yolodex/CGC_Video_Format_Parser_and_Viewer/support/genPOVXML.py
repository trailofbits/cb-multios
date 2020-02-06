'''
Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

'''

import struct
import sys
import random
import string
import time

'''
	This script is used to generate the POV style xml from a supplied image.
	It writes "pov.xml" in the current director.
'''

if __name__ == '__main__':

	if len(sys.argv) != 2:
		print 'USAGE: %s <pov.cvf>' %sys.argv[0]
		sys.exit()

	try:
		f = open( sys.argv[1], 'rb')
		cvf = f.read()
		f.close()
	except:
		print '[ERROR] Failed to open %s' %sys.argv[1]
		sys.exit()


	pollxml = '<?xml version="1.0" standalone="no" ?>\n'
	pollxml += '<!DOCTYPE pov SYSTEM "/usr/share/cgc-replay/replay.dtd">\n'
	pollxml += '<pov>\n'
	pollxml += '\t<cbid>CROMU_00032</cbid>\n'
	pollxml += '\t<replay>\n'
	pollxml += '\t\t<read echo="ascii"><delim>----------------Stream Me Your Video----------------\\n</delim><match><data>----------------Stream Me Your Video----------------\\n</data></match></read>\n'

	pollxml += '\t\t<write echo = "ascii"><data>'

	sz = struct.pack('I', len(cvf))

	for z in sz:
		pollxml += '\\x%.2x' %ord(z)

	pollxml += '</data></write>\n'

	pollxml += '\t\t<write echo = "ascii"><data>'
	for z in cvf:
		pollxml += '\\x%.2x' %ord(z)

	pollxml += '</data></write>\n'

	pollxml += '\t</replay>\n'
	pollxml += '</pov>\n'

	nm = "pov.xml"

	f = open(nm, 'wb')
	f.write(pollxml)
	f.close()
