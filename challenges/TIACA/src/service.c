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

#include "libcgc.h"

#include "cgc_asan.h"
#include "cgc_stdlib.h"
#include "cgc_service.h"
#include "cgc_libc.h"
#include "cgc_string.h"

int cgc_recvUntil(int fd, char *buf, int size, char delim) {
	char tmp;
	int count = 0;
	int got;
	char *bufPtr;

	bufPtr = buf;
	while(1) {
		got = cgc_receive(fd, &tmp, 1, NULL);
		if(got >= 0) {
			if(tmp == delim){
				cgc_validateRet();
				return count;
			}
		} else {
			cgc_validateRet();
			return -1;
		}
		count++;
		cgc_validatePtr(bufPtr);
		*bufPtr = tmp;
		bufPtr++;
	}
	cgc_validateRet();
}

void cgc_bookKeeping(carstate *drive)
{
	int tmpAmount;
	
	cgc_validatePtr(drive);
	if(drive->rpm > 6000)
	{
		//car explodes.  Just cgc_exit.
		cgc_transmit_all(STDOUT, "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff", 10);
		cgc__terminate(0);
	}

	if(drive->gear != GEARS_PARK) {
		tmpAmount = (drive->rpm / 100) + drive->speed + (drive->trunk_load / 100);
		drive->fuel-=tmpAmount;

		if(drive->window_state == WINDOWS_DOWN)
			drive->fuel-=5;

		if(drive->moonroof_state == MOONROOF_OPEN)
			drive->fuel-=2;

		if((drive->info_state != INFO_OFF || drive->info_state != INFO_AM) && drive->info_volume > 20) {
			drive->speed += 1;
			drive->rpm += 25;
		}
	}

	cgc_validateRet();
	return;
}

void cgc_raiseAlarm() {
	char a;
	cgc_memcpy(&a, "AAAAAAAAAAAAAAAA", 16);
	cgc_validateRet();
}

void cgc_handleShift(carstate *drive, char shiftmode)
{
	cgc_validatePtr(drive);
	if(shiftmode == GEARS_SHIFTUP)
	{
		if(drive->gear < GEARS_FIFTH && drive->rpm > 500) {
			if(drive->gear > GEARS_PARK) {
				if(drive->speed > ((drive->gear / 0x10) * 10))
					drive->gear += 0x10;
				else {
					cgc_validateRet();
					return;
				}
			} else {
				drive->gear += 0x10;
			}
			if(drive->rpm < 750)
				drive->rpm = 0;
			else
				drive->rpm -= 750;
		}
	} else {
		if(drive->gear > GEARS_PARK) {
			drive->gear -= 0x10;
			drive->rpm += 750;
		}
	}
	cgc_validateRet();
}

void cgc_updateBTMetadata(carstate *drive, char *userbuf) {
	char *tmp;
	char len;
	cgc_validatePtr(drive);
	cgc_validatePtr(userbuf);
	tmp = userbuf+1;
	len = *tmp;
	tmp++;
	#ifdef PATCHED
	if(len > 31)
		len = 31;
	#endif
	cgc_memcpy(drive->bt_metadata, tmp, len);
	cgc_validateRet();
}

void cgc_handleTrunk(carstate *drive, char *buf)
{
	char *tmp;
	cgc_validatePtr(drive);
	cgc_validatePtr(buf);
	tmp = buf;
	if(*tmp == TRUNK_LOAD) {
		drive->trunk_load += *(buf+1);
	} else {
		if(drive->trunk_load < *(buf+1))
			drive->trunk_load = 0;
		else
			drive->trunk_load -= *(buf+1);
	}
	cgc_validateRet();
}

void cgc_initCar(carstate *drive)
{
	cgc_validatePtr(drive);
	drive->gear = GEARS_PARK;
	drive->car_power = CAR_OFF;
	drive->trunk_state = TRUNK_CLOSED;
	drive->moonroof_state = MOONROOF_CLOSED;
	drive->window_state = WINDOWS_UP;
	drive->alarm_state = ALARM_UNSET;
	drive->gear_state = GEARS_UNCLUTCH;
	drive->fuel = 65535;
	cgc_validateRet();
}

int main(int cgc_argc, char *cgc_argv[]) {
	cgc_serviceLoop();
	cgc_validateRet();
}

void cgc_serviceLoop() {

	typedef struct _locals {
#ifdef PATCHED
		char ibuf[512];
#else
		char ibuf[256];
#endif
		carstate _drive;
		carstate *drive;
	} locals;
	locals drivestuff;
	drivestuff.drive = &drivestuff._drive;
	char *ptr;
	cgc_validatePtr(drivestuff.drive);
	cgc_memset(drivestuff.drive, 0, sizeof(carstate));
	cgc_validatePtr(drivestuff.drive);
	cgc_initCar(drivestuff.drive);

	while(1) {
		cgc_memset(drivestuff.ibuf, 0, sizeof(drivestuff.ibuf));
		int got;
		got = cgc_recvUntil(0, drivestuff.ibuf, 255, '\n');
		if(got <= 0)
			cgc__terminate(0);
		ptr=drivestuff.ibuf;
		cgc_bookKeeping(drivestuff.drive);
		cgc_validatePtr(ptr);
		for(;ptr<drivestuff.ibuf+256;ptr++) {
			switch(*ptr) {
				//car power state stuff.
				case CAR_END:
					cgc_validatePtr(drivestuff.drive);
					cgc_transmit_all(STDOUT, (const char *)drivestuff.drive, sizeof(carstate));
					cgc__terminate(0);
				case CAR_OFF:
					//make sure car is in park.
					cgc_validatePtr(drivestuff.drive);
					if(drivestuff.drive->gear == GEARS_PARK) {
						drivestuff.drive->car_power = CAR_OFF;
					} else {
						drivestuff.drive->rpm = 9999;
					}
					break;
				case CAR_ON:
					cgc_validatePtr(drivestuff.drive);
					if(drivestuff.drive->car_power == CAR_OFF || drivestuff.drive->car_power == CAR_ACC)
					{
						drivestuff.drive->car_power = CAR_ON;
					}
					break;
				case CAR_ACC:
					cgc_validatePtr(drivestuff.drive);
					if(drivestuff.drive->car_power == CAR_OFF || (drivestuff.drive->car_power == CAR_ON && drivestuff.drive->gear == GEARS_PARK)) {
						drivestuff.drive->car_power = CAR_ACC;
					}
					break;

				//trunk state doesn't care if the car is on or off...but if its in gear, that's bad.
				case TRUNK_OPEN:
					//if you try to open the trunk and the alarm is on, set off the alarm.
					//we don't have an alarm though, so just smash the stack.
					cgc_validatePtr(drivestuff.drive);
					if(drivestuff.drive->alarm_state == ALARM_SET)
						cgc_raiseAlarm();

				case TRUNK_CLOSED:
					cgc_validatePtr(drivestuff.drive);
					if(drivestuff.drive->gear == GEARS_PARK)
						drivestuff.drive->trunk_state = *ptr;
					break;

				case ALARM_SET:
				case ALARM_UNSET:
					cgc_validatePtr(drivestuff.drive);
					drivestuff.drive->alarm_state = *ptr;
					break;

				case TRUNK_LOAD:
				case TRUNK_UNLOAD:
					cgc_validatePtr(drivestuff.drive);
					if(drivestuff.drive->gear == GEARS_PARK && drivestuff.drive->trunk_state == TRUNK_OPEN) {
						cgc_handleTrunk(drivestuff.drive, ptr);
					}
					ptr++;
					break;
				default:
					cgc_validatePtr(drivestuff.drive);
					while(cgc_validatePtr(drivestuff.drive) && (drivestuff.drive->car_power != CAR_OFF) && ptr < drivestuff.ibuf+256) {
						cgc_validatePtr(ptr);
						switch(*ptr) {
							//windows can only be manipulated while the car is powered.
							case WINDOWS_DOWN:
								cgc_validatePtr(drivestuff.drive);
								if(drivestuff.drive->window_state != WINDOWS_DOWN)
									drivestuff.drive->window_state = WINDOWS_DOWN;
								break;
							case WINDOWS_UP:
								cgc_validatePtr(drivestuff.drive);
								if(drivestuff.drive->window_state != WINDOWS_UP)
									drivestuff.drive->window_state = WINDOWS_UP;
								break;
							case MOONROOF_OPEN:
								cgc_validatePtr(drivestuff.drive);
								if(drivestuff.drive->moonroof_state != MOONROOF_OPEN)
									drivestuff.drive->moonroof_state = MOONROOF_OPEN;
								break;
							case MOONROOF_CLOSED:
								cgc_validatePtr(drivestuff.drive);
								if(drivestuff.drive->moonroof_state != MOONROOF_CLOSED)
									drivestuff.drive->moonroof_state = MOONROOF_CLOSED;
								break;

							//same with infotainment
							case INFO_OFF:
								drivestuff.drive->info_volume = 0;
							case INFO_XM:
							case INFO_AM:
							case INFO_FM:
							case INFO_AUX:
							//we don't let you change the radio until you're cruising.
							//who listens to the radio while idled, anyway?
								cgc_validatePtr(drivestuff.drive);
								cgc_validatePtr(ptr);
								if(drivestuff.drive->gear > GEARS_THIRD)
									drivestuff.drive->info_state = *ptr;
								break;
							case INFO_BT:
								//bluetooth has some metadata
								//track list and whatnot.
								cgc_validatePtr(drivestuff.drive);
								char tmplen;
								cgc_validatePtr(ptr);
								if(drivestuff.drive->gear > GEARS_SECOND){
									drivestuff.drive->info_state = INFO_BT;
									cgc_updateBTMetadata(drivestuff.drive, ptr);
								}
								ptr++;
								tmplen = *ptr;
								ptr+=tmplen;
								break;

							case INFO_VOLUP:
							case INFO_VOLDOWN:
								cgc_validatePtr(drivestuff.drive);
								if(drivestuff.drive->info_state != INFO_OFF) {
									int sign = 1;
									short amount;
									cgc_validatePtr(ptr);
									if(*ptr == INFO_VOLDOWN)
										sign = -1;
									amount = *(ptr+1);
									ptr+=2;
									if(sign == -1) {
										if(drivestuff.drive->info_volume < amount) {
											drivestuff.drive->info_volume = 0;
										} else {
											drivestuff.drive->info_volume -= amount;
										}
									} else {
										drivestuff.drive->info_volume += amount;
									}
								}
								ptr++;
								break;

							case CAR_OFF:
								cgc_validatePtr(drivestuff.drive);
								if(drivestuff.drive->gear == GEARS_PARK)
									drivestuff.drive->car_power = CAR_OFF;
								break;

							//gears are kinda complicated...
							case GEARS_ACCEL:
								//accel doesn't impact speed until clutch is re-engaged.  It will spike RPMs
								//though...
								cgc_validatePtr(drivestuff.drive);
								if(drivestuff.drive->gear_state == GEARS_UNCLUTCH) {
									drivestuff.drive->speed++;
									drivestuff.drive->rpm += 25;
								} else {
									drivestuff.drive->rpm += 50;
								}
								break;
							case GEARS_SLOWDOWN:
								cgc_validatePtr(drivestuff.drive);
								drivestuff.drive->speed--;
								drivestuff.drive->rpm-=25;
								break;
							case GEARS_SHIFTUP:
								cgc_validatePtr(drivestuff.drive);
								if(drivestuff.drive->gear_state == GEARS_CLUTCH)
									cgc_handleShift(drivestuff.drive, GEARS_SHIFTUP);
								break;
							case GEARS_SHIFTDOWN:
								cgc_validatePtr(drivestuff.drive);
								if(drivestuff.drive->gear_state == GEARS_CLUTCH)
									cgc_handleShift(drivestuff.drive, GEARS_SHIFTDOWN);
								break;
							case GEARS_CLUTCH:
							case GEARS_UNCLUTCH:
								cgc_validatePtr(ptr);
								cgc_validatePtr(drivestuff.drive);
								drivestuff.drive->gear_state = *ptr;
								break;
					}
					ptr++;
				}
			}
		}
	}
}
