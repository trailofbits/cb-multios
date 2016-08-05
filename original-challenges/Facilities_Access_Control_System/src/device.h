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
#ifndef DEVICE_H
#define DEVICE_H

#include <libcgc.h>
#include "stdint.h"
#include "user.h"

#define MAX_DEVICES (128)

#define DEVICE_UNUSED  (0)
#define DEVICE_KEYPAD  (1)
#define DEVICE_SWIPE   (2)
#define DEVICE_CONTACT (3)
#define DEVICE_MOTION  (4)
#define DEVICE_HEAT    (5)
#define DEVICE_SMOKE   (6)
#define DEVICE_ALARM   (7)

// Generic Device handle
typedef struct _device {
	uint8_t Type;
	uint16_t DeviceId;
	void *Attributes;
} Device, *pDevice;

// List of authorized codes for a given keypad or swipe
typedef struct _authorized_codes {
	char AccessCodes[MAX_USERS][ACCESS_CODE_LEN+1];
} AuthorizedCodes, *pAuthorizedCodes;

// Alarm control Devices
#define ALARM_DISARMED (0)
#define ALARM_ARMED (1)
#define ALARM_INACTIVE (0)
#define ALARM_ACTIVE (1)
typedef struct _alarm_attributes {
	uint8_t Armed;
	uint8_t Active;
	uint8_t DeviceList[MAX_DEVICES];
} AlarmAttributes, *pAlarmAttributes;

#define CONTACT_NO     (0)
#define CONTACT_NC     (1)
#define CONTACT_OPEN   (0)
#define CONTACT_CLOSED (1)
typedef struct _contact {
	uint8_t Mode;
	uint8_t State;
} Contact, *pContact;

#define MOTION_INACTIVE (0)
#define MOTION_ACTIVE   (1)
typedef struct _motion {
	uint8_t State;
} Motion, *pMotion;

typedef struct _heat {
	uint8_t CurrentTemperature;
	uint8_t ThresholdTemperature;
} Heat, *pHeat;

#define SMOKE_INACTIVE (0)
#define SMOKE_ACTIVE   (1)
typedef struct _smoke {
	uint8_t State;
} Smoke, *pSmoke;

uint8_t FindAvailableDevice(void);
uint8_t FindDeviceId(uint16_t TargetId);
uint16_t NewGenericDevice(uint8_t DeviceType, uint8_t NewDevice);
uint16_t NewContact(uint8_t NewDevice);
uint16_t NewMotion(uint8_t NewDevice);
uint16_t NewHeat(uint8_t NewDevice);
uint16_t NewSmoke(uint8_t NewDevice);
uint16_t NewStrike(uint8_t NewDevice);
uint8_t DeleteDevice(uint16_t DeviceId);
uint8_t GrantAccess(uint16_t DeviceId, uint8_t UserId);
uint8_t RevokeAccess(uint8_t UserId);
uint8_t AddDeviceToAlarm(uint16_t DeviceId, uint16_t AlarmId);
uint8_t RevokeAccess(uint8_t UserId);
uint8_t UpdateDevice(uint16_t DeviceId);
uint8_t ListValidAlarmCodes(uint16_t DeviceId);

#endif

