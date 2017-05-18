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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_stdint.h"
#include "cgc_device.h"
#include "cgc_io.h"
#include "cgc_user.h"

cgc_size_t cgc_ReadBytes(unsigned char *Buf, cgc_size_t Max) {
	cgc_size_t Total = 0;
	cgc_size_t Rx;

	while ((Total < Max) && (cgc_receive(0, Buf+Total, Max-Total, &Rx) == 0)) {
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

cgc_size_t cgc_SendBytes(unsigned char *Buf, cgc_size_t Max) {
	cgc_size_t Total = 0;
	cgc_size_t Tx;

	while ((Total < Max) && (cgc_transmit(1, Buf+Total, Max-Total, &Tx) == 0)) {
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
uint8_t cgc_SendResp(uint8_t Code, unsigned char *Data) {
	if (!cgc_SendBytes((unsigned char *)&Code, 1)) {
		return(0);
	}
	if (Data == NULL) {
		uint16_t NA = 0;
		if (!cgc_SendBytes((unsigned char *)&NA, 2)) {
			return(0);
		}
	} else {
		if (!cgc_SendBytes(Data, 2)) {
			return(0);
		}
	}
	return(1);
}

uint8_t cgc_RecvCommand() {
	uint8_t Cmd;
	char Username[32];
	uint8_t TargetUser = MAX_USERS+1;
	uint8_t DeviceType;
	uint16_t DeviceId;
	uint16_t AlarmId;
	uint8_t NewDevice;
	uint8_t UserId;

	// Read in the one-byte command
	if (!cgc_ReadBytes((unsigned char *)&Cmd, 1)) {
		return(0);
	}

	switch (Cmd) {
		case CMD_POWER_OFF:
			cgc_SendResp(RESP_SUCCESS, NULL);
			return(0);
			break;

		case CMD_ADD_USER:
			if (!cgc_AddUser()) {
				cgc_SendResp(RESP_ADD_USER_FAILED, NULL);
				return(1);
			}
			cgc_SendResp(RESP_SUCCESS, NULL);
			break;

		case CMD_DEL_USER:
			if (!cgc_DelUser()) {
				cgc_SendResp(RESP_DEL_USER_FAILED, NULL);
				return(1);
			}
			cgc_SendResp(RESP_SUCCESS, NULL);
			break;

		case CMD_ADD_DEVICE:
			// Read in the device type
			if (!cgc_ReadBytes((unsigned char *)&DeviceType, 1)) {
				return(0);
			}
			
		        // Find the next available device slot
			if ((NewDevice = cgc_FindAvailableDevice()) >= MAX_DEVICES) {
				cgc_SendResp(RESP_INVALID_CMD, NULL);
				return(0);
			}
			
			switch (DeviceType) {
				case DEVICE_KEYPAD:
					if (!(DeviceId = cgc_NewGenericDevice(DeviceType, NewDevice))) {
						cgc_SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(0);
					}
					break;
				case DEVICE_SWIPE:
					if (!(DeviceId = cgc_NewGenericDevice(DeviceType, NewDevice))) {
						cgc_SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(0);
					}
					break;
				case DEVICE_CONTACT:
					if (!(DeviceId = cgc_NewContact(NewDevice))) {
						cgc_SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(0);
					}
					break;
				case DEVICE_MOTION:
					if (!(DeviceId = cgc_NewMotion(NewDevice))) {
						cgc_SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(0);
					}
					break;
				case DEVICE_HEAT:
					if (!(DeviceId = cgc_NewHeat(NewDevice))) {
						cgc_SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(0);
					}
					break;
				case DEVICE_SMOKE:
					if (!(DeviceId = cgc_NewSmoke(NewDevice))) {
						cgc_SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(0);
					}
					break;
				case DEVICE_ALARM:
					if (!(DeviceId = cgc_NewGenericDevice(DeviceType, NewDevice))) {
						cgc_SendResp(RESP_ADD_DEVICE_FAILED, NULL);
						return(1);
					}
					break;
				default:
					cgc_SendResp(RESP_ADD_DEVICE_FAILED, NULL);
					break;
			}
			// Send success along with the generated DeviceId
			cgc_SendResp(RESP_SUCCESS, (unsigned char *)&DeviceId);
			break;	

		case CMD_DEL_DEVICE:
			// Read in the device id
			if (!cgc_ReadBytes((unsigned char *)&DeviceId, 2)) {
				return(0);
			}
			
			if (!cgc_DeleteDevice(DeviceId)) {
				cgc_SendResp(RESP_DEL_DEVICE_FAILED, NULL);
				return(1);
			}
			cgc_SendResp(RESP_SUCCESS, NULL);
			break;

		case CMD_GRANT_ACCESS:
			// Read in the device id
			if (!cgc_ReadBytes((unsigned char *)&DeviceId, 2)) {
				return(0);
			}
			
			// Read in the user id
			if (!cgc_ReadBytes((unsigned char *)&UserId, 1)) {
				return(0);
			}
			
			if (!cgc_GrantAccess(DeviceId, UserId)) {
				cgc_SendResp(RESP_GRANT_FAILED, NULL);
				return(1);
			}
			cgc_SendResp(RESP_SUCCESS, NULL);
			break;

		case CMD_UPDATE_DEVICE:
			// Read in the device id
			if (!cgc_ReadBytes((unsigned char *)&DeviceId, 2)) {
				return(0);
			}

			if (!cgc_UpdateDevice(DeviceId)) {
				cgc_SendResp(RESP_UPDATE_DEVICE_FAILED, NULL);
				return(1);
			}
			cgc_SendResp(RESP_SUCCESS, NULL);
			break;

		case CMD_ADD_DEVICE_TO_ALARM:
			// Read in the device id
			if (!cgc_ReadBytes((unsigned char *)&DeviceId, 2)) {
				return(0);
			}
			
			// Read in the alarm id
			if (!cgc_ReadBytes((unsigned char *)&AlarmId, 2)) {
				return(0);
			}

			if (!cgc_AddDeviceToAlarm(DeviceId, AlarmId)) {
				cgc_SendResp(RESP_ADD_DEVICE_TO_ALARM_FAILED, NULL);
				return(0);
			}

			cgc_SendResp(RESP_SUCCESS, NULL);
			break;

		case CMD_LIST_ALARM_CODES:
			// Read in the device id
			if (!cgc_ReadBytes((unsigned char *)&DeviceId, 2)) {
				return(0);
			}
			
			if (!cgc_ListValidAlarmCodes(DeviceId)) {
				cgc_SendResp(RESP_INVALID_CMD, NULL);
				return(0);
			}

			break;

		default:
			cgc_SendResp(RESP_INVALID_CMD, NULL);
			return(1);
			break;
	}

	return(1);
}
