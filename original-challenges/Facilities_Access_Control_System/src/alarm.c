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
#include "io.h"
#include "device.h"
#include "user.h"

extern Device Devices[MAX_DEVICES];

uint8_t IsDeviceInAlarm(uint8_t TargetDevice) {
	pContact ContactAttributes;
	pMotion MotionAttributes;
	pSmoke SmokeAttributes;
	pHeat HeatAttributes;

	switch (Devices[TargetDevice].Type) {
		case DEVICE_CONTACT:
			ContactAttributes = (pContact)(Devices[TargetDevice].Attributes);
			if (ContactAttributes->Mode == CONTACT_NO) {
				if (ContactAttributes->State == CONTACT_OPEN) {
					return(0);
				} else {
					return(1);
				}
			}
			if (ContactAttributes->Mode == CONTACT_NC) {
				if (ContactAttributes->State == CONTACT_CLOSED) {
					return(0);
				} else {
					return(1);
				}
			}
			break;
		case DEVICE_MOTION:
			MotionAttributes = (pMotion)(Devices[TargetDevice].Attributes);
			if (MotionAttributes->State == MOTION_ACTIVE) {
				return(1);
			} else {
				return(0);
			}
			break;
		case DEVICE_SMOKE:
			SmokeAttributes = (pSmoke)(Devices[TargetDevice].Attributes);
			if (SmokeAttributes->State == SMOKE_ACTIVE) {
				return(1);
			} else {
				return(0);
			}
			break;
		case DEVICE_HEAT:
			HeatAttributes = (pHeat)(Devices[TargetDevice].Attributes);
			if (HeatAttributes->CurrentTemperature > HeatAttributes->ThresholdTemperature) {
				return(1);
			} else {
				return(0);
			}
			break;

		default:
			return(0);
	}

	return(0);
}

void InvertAlarmState(uint8_t TargetDevice) {
	uint8_t i;
	uint8_t j;
	pAlarmAttributes AA;

	// find any alarms associated with this device
	for (i = 0; i < MAX_DEVICES; i++) {
		if (Devices[i].Type != DEVICE_ALARM) {
			continue;
		}
		AA = (pAlarmAttributes)(Devices[i].Attributes);
		if (!AA) {
			continue;
		}
		for (j = 0; j < MAX_DEVICES; j++) {
			if (AA->DeviceList[j] != TargetDevice) {
				continue;
			}
			AA->Armed = (AA->Armed) ? 0 : 1;
		}
	}

	return;
}

void ProcessAlarms(void) {
	uint8_t i;
	uint8_t j;
	pAlarmAttributes AA;
	uint8_t TargetDevice;
	uint8_t PrevAlarmState;
	uint8_t NewState;

	// for each alarm
	for (i = 0; i < MAX_DEVICES; i++) {
		if (Devices[i].Type != DEVICE_ALARM) {
			continue;
		}
	
		AA = (pAlarmAttributes)(Devices[i].Attributes);
		if (!AA) {
			continue;
		}
		
		// keep track of the previous alarm state
		PrevAlarmState = AA->Active;

		// is the alarm armed?
		if (AA->Armed == ALARM_ARMED) {
			// yes

			// start by assuming the alarm isn't active
			NewState = ALARM_INACTIVE;

			// for each device associated with the alarm
			for (j = 0; j < MAX_DEVICES; j++) {
				TargetDevice = AA->DeviceList[j];
				// is it in an alarm state?
				if (IsDeviceInAlarm(TargetDevice)) {
					// yes, set the alarm
					NewState = ALARM_ACTIVE;
				}
			}
			// only make an inactive alarm active if a device
			// was found in alarm state 
			if (AA->Active == ALARM_INACTIVE) {
				if (NewState == ALARM_ACTIVE) {
					AA->Active = NewState;
					SendResp(RESP_ALARM_ON, (unsigned char *)&(Devices[i].DeviceId));
				}
			}

		} else {
			// no
			// clear the alarm
			AA->Active = ALARM_INACTIVE;
			// if its previous state was ACTIVE, then send a response
			// indicating the new alarm state
			if (PrevAlarmState == ALARM_ACTIVE) {
				SendResp(RESP_ALARM_OFF, (unsigned char *)&(Devices[i].DeviceId));
			}
		}
	}
			
	return;
}
