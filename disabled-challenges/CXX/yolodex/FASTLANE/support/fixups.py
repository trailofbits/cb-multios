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

# Substitute values .TEMPLATE files so as to more easily centralize and 
# automate configuration.

# This script is super inefficient, but only needs to be run once each time any 
# .TEMPLATE file is modified.

import os
import glob
from config import conf


def do_fixups():
	for template in \
		glob.glob(os.path.join("poller", "for-testing", "*.TEMPLATE")) + \
		glob.glob(os.path.join("poller", "for-release", "*.TEMPLATE")) + \
		glob.glob(os.path.join("pov", "*.TEMPLATE")) + \
		glob.glob(os.path.join("lib", "*.TEMPLATE")):
		
		fp = open(template, "r")
		buf = fp.read()
		fp.close()

		for key in conf.keys():
			buf = buf.replace(key, conf[key])

		fp = open(template[:-len(".TEMPLATE")], "w")
		fp.write(buf)
		fp.close()


def main():
	do_fixups()


if __name__=="__main__":
	main()