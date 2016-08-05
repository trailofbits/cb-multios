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
#ifndef __COMMON_H__
#define __COMMON_H__

#include "stdint.h"

#define MAX_DATA_LEN 256
#define MAGIC_PAGE 0x4347c000

// print to the screen in human-readible format
// disable to return in binary format for polling
//#define HUMAN_PRINT 1
//#define TEST_VER 1
//#define DEBUG 1

//
// Possible commands the CRS can send to this program
//
enum 
{
	GENERAL = 0,
	REGISTER_SENSOR = 1,
	REGISTER_USER = 2,
	CHANGE_CURRENT_USER = 3,
	INPUT_SENSOR_DATA = 4,
	INPUT_MANUAL = 9,
	INPUT_SETTINGS = 0x0a,
	REQUEST_SENSORS = 0x0b,
	REMOVE_SENSOR = 0x0c,
	//TEST_VERIFY = 0x0d, // \r
	REQUEST_HW_IDS = 0x33,
	END = 0xff
} PacketType;

//
// Possible errors to send CRS
//
enum errorCodes 
{ 
	NO_ERROR = 0,
	ERROR_DUPLICATE_SENSOR = 1,
	ERROR_BAD_VALUE = 2,
	ERROR_NO_USER = 3,
	ERROR_SENSOR_NOT_REGISTERED = 4,
	ERROR_REG_OTHER_USER = 5,
	ERROR_REG_THIS_USER = 6,
	ERROR_BAD_SENSOR_MAC = 7,
	ERROR_USER_FULL = 8,
	ERROR_DUPLICATE_USER = 9, // \t
	ERROR_TEST_MAGIC_MISMATCH = 10,
	ERROR_TEST_MAGIC_MATCH = 11,
	ERROR_FULL_SENSORS = 12
};


#endif // __COMMON_H__
