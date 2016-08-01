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

DEBUG = False

ERRORS = {
	# // errno
	'ERRNO_ALLOC': -5,
	'ERRNO_SEND': -6,
	'ERRNO_RECV': -9,
	'ERRNO_RAND': -12,

	'ERR_UNINITIALIZED_TANK': -15,
	'ERR_INVALID_QTY': -16,
	'ERR_INVALID_VALVE_POS': -17,
	'ERR_TANK_EMPTY': -18,
	'ERR_END_OF_LIFE': -19,
	'ERR_TANK_FULL': -20,
}

CONFIG = {
	'SLEEP_INT': 1,
	'FILL_RATE': 12,
	'TANK_QTY': 10,
	'TANK_CAP': 255,
	'INIT_LEVEL': 90,
	'LOW_LEVEL': 25,
	'CRIT_LEVEL': 5,
}
