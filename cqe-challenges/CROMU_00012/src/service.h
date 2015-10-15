/*

Author: Dustin Fraze (df@cromulence.co)

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

*/

#ifndef _SERVICE_H
#define _SERVICE_H

#define GEARS_ACCEL 	'\x70'
#define GEARS_SLOWDOWN	'\x71'
#define GEARS_SHIFTUP 	'\x72'
#define GEARS_SHIFTDOWN '\x73'
#define GEARS_CLUTCH	'\x74'
#define GEARS_UNCLUTCH	'\x75'
#define GEARS_PARK		'\x10'
#define GEARS_FIRST		'\x20'
#define GEARS_SECOND	'\x30'
#define GEARS_THIRD		'\x40'
#define GEARS_FOURTH	'\x50'
#define GEARS_FIFTH		'\x60'

#define CAR_OFF			'\x10'
#define CAR_ON			'\x20'
#define CAR_ACC			'\x30'

#define WINDOWS_DOWN	'\xf0'
#define WINDOWS_UP		'\xe0'
#define MOONROOF_OPEN	'\xd0'
#define MOONROOF_CLOSED	'\xc0'
#define TRUNK_OPEN		'\xb0'
#define TRUNK_CLOSED	'\xa0'
#define TRUNK_LOAD		'\x90'
#define TRUNK_UNLOAD	'\x80'

#define INFO_XM			'\x05'
#define INFO_AM			'\x01'
#define INFO_FM			'\x02'
#define INFO_AUX		'\x03'
#define INFO_BT			'\x04'
#define INFO_VOLUP		'\x81'
#define INFO_VOLDOWN	'\x91'
#define INFO_OFF		'\xff'

#define ALARM_SET 		'\xf8'
#define ALARM_UNSET		'\xf9'

#define CHANGE_STATE	'\xcc'
#define CAR_END			'\xdd'
#pragma pack(push, 1)
typedef struct _carstate {
	unsigned char speed;
	unsigned short fuel;
	unsigned short rpm;
	char info_state;
	unsigned char info_volume;
	char car_power;
	unsigned char gear;
	char gear_state;
	char window_state;
	char moonroof_state;
	char trunk_state;
	char alarm_state;
	int trunk_load;
	char bt_metadata[32];
} carstate;
#pragma pack(pop)

void serviceLoop();

#endif //_SERVICE_H