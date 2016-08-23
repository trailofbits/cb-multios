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

IDX_MAJOR = 5
IDX_MINOR = 2
IDX_PENDING = 1
IDX_ACK = 0

conf = {

	"NUM_THREADS" : 5,

	"IDX_MINOR" : IDX_MINOR,

	"MASK_MAJOR" :   (7<<IDX_MAJOR),
	"MASK_MINOR" :   (7<<IDX_MINOR),
	"MASK_PENDING" : (1<<IDX_PENDING),
	"MASK_ACK" :     (1<<IDX_ACK),

	"MAJOR_FUTEX" :   (0<<IDX_MAJOR),
	"MAJOR_PAUSE" :   (1<<IDX_MAJOR),
	"MAJOR_SENDMSG" : (2<<IDX_MAJOR),
	"MAJOR_PROC" :    (3<<IDX_MAJOR),
	"MAJOR_TGKILL":   (4<<IDX_MAJOR),
	# 5 & 6 are unused
	"MAJOR_UNKNOWN" : (7<<IDX_MAJOR),

	"MINOR_FUTEX_WAIT" :           (0<<IDX_MINOR),
	"MINOR_FUTEX_WAKE" :           (1<<IDX_MINOR),
	"MINOR_FUTEX_FD" :             (2<<IDX_MINOR),
	"MINOR_FUTEX_REQUEUE_PI" :     (3<<IDX_MINOR),
	"MINOR_FUTEX_CMP_REQUEUE_PI" : (4<<IDX_MINOR),

	"MINOR_PROC_THREAD_STATE" : (0<<IDX_MINOR),
	"MINOR_PROC_LIST_DUMP" :    (1<<IDX_MINOR),

}