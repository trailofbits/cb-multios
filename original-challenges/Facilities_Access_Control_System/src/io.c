/*

Author: Joe Rogers <joe@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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
#include <libcgc.h>
#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "device.h"
#include "io.h"
#include "user.h"

size_t ReadBytes(unsigned char *Buf, size_t Max) {
	size_t Total = 0;
	size_t Rx;

	while ((Total < Max) && (receive(0, Buf+Total, Max-Total, &Rx) == 0)) {
		if (Rx == 0) {
			return(0);
		}
		Total+=Rx;
	}
	if (Total != Max) {
		return(0);
	}
	return(Total);
}

size_t SendBytes(unsigned char *Buf, size_t Max) {
	size_t Total = 0;
	size_t Tx;

	while ((Total < Max) && (transmit(1, Buf+Total, Max-Total, &Tx) == 0)) {
		if (Tx == 0) {
			return(0);
		}
		Total+=Tx;
	}
	if (Total != Max) {
		return(0);
	}
	return(Total);
}

// sends response code and 2-byte data value
uint8_t SendResp(uint8_t Code, unsigned char *Data) {
	if (!SendBytes((unsigned char *)&Code, 1)) {
		return(0);
	}
	if (Data == NULL) {
		uint16_t NA = 0;
		if (!SendBytes((unsigned char *)&NA, 2)) {
			return(0);
		}
	} else {
		if (!SendBytes(Data, 2)) {
			return(0);
		}
	}
	return(1);
}

uint8_t RecvCommand() {
	uint8_t Cmd;
	char Username[32];
	uint8_t TargetUser = MAX_USERS+1;
	uint8_t DeviceType;
	uint16_t DeviceId;
	uint16_t AlarmId;
	uint8_t NewDevice;
	uint8_t UserId;

	// Read in the one-byte command
	if (!ReadBytes((unsigned char *)&Cmd, 1)) {
		return(0);
	}

	switch (Cmd) {
		case CMD_POWER_OFF:
			SendResp(RESP_SUCCESS, NULL);
			return(0);
			break;

		case CMD_ADD_USER:
			if (!AddUser()) {
				SendResp(RESP_ADD_USER_FAILED, NULL);
				return(1);
			}
			SendResp(RESP_SUCCESS, NULL);
			break;

		case CMD_DEL_USER:
			if (!DelUser()) {
				SendResp(RESP_DEL_USER_FAILED, NULL);
				return(1);
			}
			SendResp(RESP_SUCCESS, NULL);
			break;

		case CMD_ADD_DEVICE:
			// Read in the device type
			if (!ReadBytes((unsigned char *)&DeviceType, 1)) {
				return(0);
			}
			
		        // Find the next available device slot
			if ((NewDevice = FindAvailableDevice()) >= MAX_DEVICES) {
				SendResp(RESP_INVALID_CMD, NULL);
				return(0);
			}
			
			switch (DeviceType) {
				case DEVICE_KEYPAD:
					if (!(DeviceId = NewGenericDevice(DeviceType, NewDevice))) {
						SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(0);
					}
					break;
				case DEVICE_SWIPE:
					if (!(DeviceId = NewGenericDevice(DeviceType, NewDevice))) {
						SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(0);
					}
					break;
				case DEVICE_CONTACT:
					if (!(DeviceId = NewContact(NewDevice))) {
						SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(0);
					}
					break;
				case DEVICE_MOTION:
					if (!(DeviceId = NewMotion(NewDevice))) {
						SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(0);
					}
					break;
				case DEVICE_HEAT:
					if (!(DeviceId = NewHeat(NewDevice))) {
						SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(0);
					}
					break;
				case DEVICE_SMOKE:
					if (!(DeviceId = NewSmoke(NewDevice))) {
						SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(0);
					}
					break;
				case DEVICE_ALARM:
					if (!(DeviceId = NewGenericDevice(DeviceType, NewDevice))) {
						SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(1);
					}
					break;
				default:
					SendResp(RESP_ADD_DEVICE_FAILED, NULL);
					break;
			}
			// Send success along with the generated DeviceId
			SendResp(RESP_SUCCESS, (unsigned char *)&DeviceId);
			break;	

		case CMD_DEL_DEVICE:
			// Read in the device id
			if (!ReadBytes((unsigned char *)&DeviceId, 2)) {
				return(0);
			}
			
			if (!DeleteDevice(DeviceId)) {
				SendResp(RESP_DEL_DEVICE_FAILED, NULL);
				return(1);
			}
			SendResp(RESP_SUCCESS, NULL);
			break;

		case CMD_GRANT_ACCESS:
			// Read in the device id
			if (!ReadBytes((unsigned char *)&DeviceId, 2)) {
				return(0);
			}
			
			// Read in the user id
			if (!ReadBytes((unsigned char *)&UserId, 1)) {
				return(0);
			}
			
			if (!GrantAccess(DeviceId, UserId)) {
				SendResp(RESP_GRANT_FAILED, NULL);
				return(1);
			}
			SendResp(RESP_SUCCESS, NULL);
			break;

		case CMD_UPDATE_DEVICE:
			// Read in the device id
			if (!ReadBytes((unsigned char *)&DeviceId, 2)) {
				return(0);
			}

			if (!UpdateDevice(DeviceId)) {
				SendResp(RESP_UPDATE_DEVICE_FAILED, NULL);
				return(1);
			}
			SendResp(RESP_SUCCESS, NULL);
			break;

		case CMD_ADD_DEVICE_TO_ALARM:
			// Read in the device id
			if (!ReadBytes((unsigned char *)&DeviceId, 2)) {
				return(0);
			}
			
			// Read in the alarm id
			if (!ReadBytes((unsigned char *)&AlarmId, 2)) {
				return(0);
			}

			if (!AddDeviceToAlarm(DeviceId, AlarmId)) {
				SendResp(RESP_ADD_DEVICE_TO_ALARM_FAILED, NULL);
				return(0);
			}

			SendResp(RESP_SUCCESS, NULL);
			break;

		case CMD_LIST_ALARM_CODES:
			// Read in the device id
			if (!ReadBytes((unsigned char *)&DeviceId, 2)) {
				return(0);
			}
			
			if (!ListValidAlarmCodes(DeviceId)) {
				SendResp(RESP_INVALID_CMD, NULL);
				return(0);
			}

			break;

		default:
			SendResp(RESP_INVALID_CMD, NULL);
			return(1);
			break;
	}

	return(1);
}
