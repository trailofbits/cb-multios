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

conf = {
	#"FIXUP_DEBUG_ENABLE" : "#define DEBUG_ENABLE 1",
	"FIXUP_DEBUG_ENABLE" : "",
	"FIXUP_POLLER_POV_DELAY" : "100",
	
	# trivial params
	# "FIXUP_CYCLIC_GROUP_GENERATOR" : "5",
	# "FIXUP_CYCLIC_GROUP_ORDER" : "97", 
	# "FIXUP_CYCLIC_GROUP_PRODUCT" : "29",
	# "FIXUP_CYCLIC_GROUP_SPACE" : "0xFFFF",
	# "FIXUP_CYCLIC_GROUP_KEY" : "D",
	
	# ~ 2^16 difficulty
	# "FIXUP_CYCLIC_GROUP_GENERATOR" : "5",
	# "FIXUP_CYCLIC_GROUP_ORDER" : "65521", # closest prime to 0xFFFF
	# "FIXUP_CYCLIC_GROUP_PRODUCT" : "39555",
	# "FIXUP_CYCLIC_GROUP_SPACE" : "0xFFFF",
	# "FIXUP_CYCLIC_GROUP_KEY" : "6EA9",

	# ~ 2^24 difficulty
	"FIXUP_CYCLIC_GROUP_GENERATOR" : "5",
	"FIXUP_CYCLIC_GROUP_ORDER" : "16777213", # closest prime to 0xFFFFFF
	"FIXUP_CYCLIC_GROUP_PRODUCT" : "12937613",
	"FIXUP_CYCLIC_GROUP_SPACE" : "0xFFFFFF",
	"FIXUP_CYCLIC_GROUP_KEY" : "7FFF53",
}