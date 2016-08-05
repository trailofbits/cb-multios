/*

Author: James Nuttall <james@cromulence.com>

Copyright (c) 2016 Cromulence LLC

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

*/

#ifndef SERVICE_H
#define SERVICE_H

#define MAGIC_PAGE 0x4347c000


extern "C"
{
	#include "stdio.h"
	#include <stdlib.h>
}

//
// Possible commands the CRS can send to this program
//  Must match original poller
//
enum 
{
	POWER_ON_OFF = 1,
	TEMP_SET = 2,
	SENSOR_ADD = 3,
	SENSOR_REMOVE = 4,
	SENSOR_SMOKE = 5,
	PROGRAM_UPDATE = 6,
	PROGRAM_SEND = 7,
	STATUS_SEND = 8,
	SIMULATE = 9,
	FIRMWARE_CHECK = 10,
	END = 0xff
};

//
// Possible errors to send CRS
//  Must match original poller
//
enum errorCodes { 

	NO_ERROR = 0x0,
	ERROR_TEMP_RANGE = 0x1,
	ERROR_TIME_VALUE = 0x2,
	ERROR_NO_SENSOR = 0x3,
	ERROR_BAD_PROGRAM = 0x4,
	ERROR_BAD_COMMAND = 0x5,
	ERROR_BAD_ID = 0x6,
	ERROR_ID_INUSE = 0x7,
	ERROR_SENSORS_FULL = 0x8

};






#endif