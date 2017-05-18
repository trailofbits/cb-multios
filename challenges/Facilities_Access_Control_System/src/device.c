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
#include "cgc_malloc.h"
#include "cgc_string.h"
#include "cgc_device.h"
#include "cgc_user.h"
#include "cgc_io.h"
#include "cgc_alarm.h"

Device cgc_Devices[MAX_DEVICES];

extern User cgc_Users[MAX_USERS];
const uint32_t *MagicPage = (const uint32_t *)0x4347C000;
uint16_t cgc_MagicIndex = 0;

// Generate a new DeviceId
uint16_t cgc_NewDeviceId(void) {
	uint16_t DeviceId;

	// Generate a 2-byte DeviceId from a 4-byte magic page value
	DeviceId = MagicPage[cgc_MagicIndex] % 65534;
	cgc_MagicIndex = (cgc_MagicIndex+1)%1024;

	// make sure the new ID is not zero (reserved) and isn't already in use
	while (DeviceId == 0 || (cgc_FindDeviceId(DeviceId) != MAX_DEVICES)) {
		DeviceId = MagicPage[cgc_MagicIndex] % 65534;
		cgc_MagicIndex = (cgc_MagicIndex+1)%1024;
	}

	return(DeviceId);
}

// Find an available device index
uint8_t cgc_FindAvailableDevice(void) {
	uint8_t i;
	uint8_t NewDevice = MAX_DEVICES+1;

	for (i = 1; i < MAX_DEVICES; i++) {
		if (cgc_Devices[i].Type == DEVICE_UNUSED) {
			NewDevice = i;
			break;
		}
	}

	return(NewDevice);
}

// Find a device given its DeviceId value
uint8_t cgc_FindDeviceId(uint16_t TargetId) {
	uint8_t i;

	for (i = 0; i < MAX_DEVICES; i++) {
		if (cgc_Devices[i].Type != DEVICE_UNUSED && cgc_Devices[i].DeviceId == TargetId) {
			break;
		}
	}

	return(i);

}

// Add device
uint16_t cgc_NewGenericDevice(uint8_t DeviceType, uint8_t NewDevice) {
	uint16_t DeviceId = cgc_NewDeviceId();

	// No device-specific attributes for this type device, so just
	// Add the new device
	cgc_Devices[NewDevice].Type = DeviceType;
	cgc_Devices[NewDevice].DeviceId = DeviceId;
	cgc_Devices[NewDevice].Attributes = NULL;

	return(DeviceId);
}

uint16_t cgc_NewContact(uint8_t NewDevice) {
	uint16_t DeviceId = cgc_NewDeviceId();
	uint8_t Mode;
	uint8_t State;
	pContact NewContact;

	// Read in the device-specific attributes
	if (!cgc_ReadBytes((unsigned char *)&Mode, 1)) {
		return(0);
	}
	if (!cgc_ReadBytes((unsigned char *)&State, 1)) {
		return(0);
	}

	// Add the new device
	cgc_Devices[NewDevice].Type = DEVICE_CONTACT;
	cgc_Devices[NewDevice].DeviceId = DeviceId;
	if ((NewContact = (pContact)cgc_calloc(sizeof(Contact))) == NULL) {
		return(0);
	}
	NewContact->Mode = Mode;
	NewContact->State = State;
	cgc_Devices[NewDevice].Attributes = NewContact;

	return(DeviceId);

}

uint16_t cgc_NewMotion(uint8_t NewDevice) {
	uint16_t DeviceId = cgc_NewDeviceId();
	uint8_t State;
	pMotion NewMotion;

	// Read in the device-specific attributes
	if (!cgc_ReadBytes((unsigned char *)&State, 1)) {
		return(0);
	}

	// Add the new device
	cgc_Devices[NewDevice].Type = DEVICE_MOTION;
	cgc_Devices[NewDevice].DeviceId = DeviceId;
	if ((NewMotion = (pMotion)cgc_calloc(sizeof(Motion))) == NULL) {
		return(0);
	}
	NewMotion->State = State;
	cgc_Devices[NewDevice].Attributes = NewMotion;

	return(DeviceId);

}

uint16_t cgc_NewHeat(uint8_t NewDevice) {
	uint16_t DeviceId = cgc_NewDeviceId();
	uint8_t CurrentTemperature;
	uint8_t ThresholdTemperature;
	pHeat NewHeat;

	// Read in the device-specific attributes
	if (!cgc_ReadBytes((unsigned char *)&CurrentTemperature, 1)) {
		return(0);
	}

	if (!cgc_ReadBytes((unsigned char *)&ThresholdTemperature, 1)) {
		return(0);
	}

	// Add the new device
	cgc_Devices[NewDevice].Type = DEVICE_HEAT;
	cgc_Devices[NewDevice].DeviceId = DeviceId;
	if ((NewHeat = (pHeat)cgc_calloc(sizeof(Heat))) == NULL) {
		return(0);
	}
	NewHeat->CurrentTemperature = CurrentTemperature;
	NewHeat->ThresholdTemperature = ThresholdTemperature;
	cgc_Devices[NewDevice].Attributes = NewHeat;

	return(DeviceId);

}

uint16_t cgc_NewSmoke(uint8_t NewDevice) {
	uint16_t DeviceId = cgc_NewDeviceId();
	uint8_t State;
	pSmoke NewSmoke;

	// Read in the device-specific attributes
	if (!cgc_ReadBytes((unsigned char *)&State, 1)) {
		return(0);
	}
	// Add the new device
	cgc_Devices[NewDevice].Type = DEVICE_SMOKE;
	cgc_Devices[NewDevice].DeviceId = DeviceId;
	if ((NewSmoke = (pSmoke)cgc_calloc(sizeof(Smoke))) == NULL) {
		return(0);
	}
	NewSmoke->State = State;
	cgc_Devices[NewDevice].Attributes = NewSmoke;

	return(DeviceId);

}

// Delete Device
uint8_t cgc_DeleteDevice(uint16_t DeviceId) {
	uint8_t Target;
	uint8_t i;
	uint8_t j;
	pAlarmAttributes AA;

	if ((Target = cgc_FindDeviceId(DeviceId)) == MAX_DEVICES) {
		return(0);
	}

	// remove it from any alarms that reference it
	for (i = 0; i < MAX_DEVICES; i++) {
		if (cgc_Devices[i].Type != DEVICE_ALARM) {
			continue;
		}
		if (!cgc_Devices[i].Attributes) {
			continue;
		}
		AA = (pAlarmAttributes)(cgc_Devices[i].Attributes);
		for (j = 0; j < MAX_DEVICES; j++) {
			if (AA->DeviceList[j] == Target) {
				AA->DeviceList[j] = DEVICE_UNUSED;
				break;
			}
		}
	}

	// Process any changes in alarm state that would result from
	// this device being removed
	cgc_ProcessAlarms();

	// remove the device
	cgc_Devices[Target].Type = DEVICE_UNUSED;
	cgc_Devices[Target].DeviceId = 0;
	if (cgc_Devices[Target].Attributes) {
		cgc_free(cgc_Devices[Target].Attributes);
		cgc_Devices[Target].Attributes = NULL;
	}

	return(1);
}


// Grant user access to device
uint8_t cgc_GrantAccess(uint16_t DeviceId, uint8_t UserId) {
	pAuthorizedCodes codes;
	uint8_t i;
	uint8_t NewCode;
	uint8_t DeviceIndex;

	// Look up the device index
	if ((DeviceIndex = cgc_FindDeviceId(DeviceId)) == MAX_DEVICES) {
		return(0);
	}

	// make sure it's a keypad or swipe device
	if (cgc_Devices[DeviceIndex].Type != DEVICE_KEYPAD && cgc_Devices[DeviceIndex].Type != DEVICE_SWIPE) {
		return(0);
	}

	// validate the userid
	if (UserId > MAX_USERS) {
		return(0);
	}
	if (cgc_Users[UserId].Username[0] == '\0') {
		return(0);
	}

	// allocate new attributes buffer if it's not already in place
	if (!cgc_Devices[DeviceIndex].Attributes) {
		if ((codes = (pAuthorizedCodes)cgc_calloc(sizeof(AuthorizedCodes))) == NULL) {
			return(0);
		}
		cgc_Devices[DeviceIndex].Attributes = codes;
	} else {
		codes = (pAuthorizedCodes)(cgc_Devices[DeviceIndex].Attributes);
	}

	// Find an open authorized code slot
	NewCode = MAX_USERS;
	for (i = 0; i < MAX_USERS; i++) {
		if (codes->AccessCodes[i][0] == '\0' && NewCode == MAX_USERS) {
			// found a open slot
			NewCode = i;
		}
		if (!cgc_strcmp(codes->AccessCodes[i], cgc_Users[UserId].Pin) || !cgc_strcmp(codes->AccessCodes[i], cgc_Users[UserId].AccessCode)) {
			// code is already in the list
			return(1);
		}
	}
	if (NewCode == MAX_USERS) {
		// No available slots
		return(0);
	}

	// Add the pin to a Keypad device
	if (cgc_Devices[DeviceIndex].Type == DEVICE_KEYPAD) {
		cgc_strcpy(codes->AccessCodes[NewCode], cgc_Users[UserId].Pin);
		codes->AccessCodes[NewCode][PIN_LEN] = '\0';
	// Add the access code to a swipe device
	} else if (cgc_Devices[DeviceIndex].Type == DEVICE_SWIPE) {
		cgc_strcpy(codes->AccessCodes[NewCode], cgc_Users[UserId].AccessCode);
		codes->AccessCodes[NewCode][ACCESS_CODE_LEN] = '\0';
	}

	return(1);
}

uint8_t cgc_RevokeAccess(uint8_t UserIndex) {
	uint8_t i;
	uint8_t j;
	pAuthorizedCodes codes;

	// run through the devices
	for (i = 0; i < MAX_DEVICES; i++) {
		// only need to remove users from keypads and swipes
		if (cgc_Devices[i].Type != DEVICE_KEYPAD && cgc_Devices[i].Type != DEVICE_SWIPE) {
			continue;
		}

		// See if this device has any pins or access codes associated with it
		if (!cgc_Devices[i].Attributes) {
			continue;
		}
		codes = cgc_Devices[i].Attributes;

		// run through the codes on this device
		for (j = 0; j < MAX_USERS; j++) {
			if (!cgc_strcmp(codes->AccessCodes[j], cgc_Users[UserIndex].Pin) || !cgc_strcmp(codes->AccessCodes[j], cgc_Users[UserIndex].AccessCode)) {
				// found matching code, remove it
				codes->AccessCodes[j][0] = '\0';
			}
		}
	}

	return(1);
}

// Associate device with alarm
uint8_t cgc_AddDeviceToAlarm(uint16_t DeviceId, uint16_t AlarmId) {
	uint8_t DeviceIndex;
	uint8_t AlarmIndex;
	pAlarmAttributes AA;
	uint8_t NewDevice;
	uint8_t i;

	if ((DeviceIndex = cgc_FindDeviceId(DeviceId)) == MAX_DEVICES) {
		return(0);
	}

	if ((AlarmIndex = cgc_FindDeviceId(AlarmId)) == MAX_DEVICES) {
		return(0);
	}

	// allocate new attributes buffer if it's not already in place
	if (!cgc_Devices[AlarmIndex].Attributes) {
		if ((AA = (pAlarmAttributes)cgc_calloc(sizeof(AlarmAttributes))) == NULL) {
			return(0);
		}
		cgc_Devices[AlarmIndex].Attributes = AA;
	} else {
		AA = (pAlarmAttributes)(cgc_Devices[AlarmIndex].Attributes);
	}

	// find an available device slot in this alarm
	// and make sure the new device isn't already in the list
	NewDevice = MAX_DEVICES;
	for (i = 0; i < MAX_DEVICES; i++) {
		if (AA->DeviceList[i] == DEVICE_UNUSED && NewDevice == MAX_DEVICES) {
			// found an available slot
			NewDevice = i;
		}
		if (AA->DeviceList[i] == DeviceIndex) {
			// device is already in the list
			return(1);
		}
	}
	if (NewDevice == MAX_DEVICES) {
		// no space
		return(0);
	}

	AA->DeviceList[NewDevice] = DeviceIndex;

	// process any alarms that might now be triggered by this device
	cgc_ProcessAlarms();

	return(1);
}

uint8_t cgc_IsValidCredential(uint8_t DeviceIndex, char *TargetCode) {
	uint8_t i;
	pAuthorizedCodes Codes;

	// valid index?
	if (DeviceIndex == 0 || DeviceIndex >= MAX_DEVICES) {
		return(0);
	}

	if (!TargetCode) {
		return(0);
	}

	// Is it a keypad or swipe device (the only ones with credentials)
	if (cgc_Devices[DeviceIndex].Type != DEVICE_KEYPAD && cgc_Devices[DeviceIndex].Type != DEVICE_SWIPE) {
		return(0);
	}

	// Does this device have attributes defined yet?
	if (!cgc_Devices[DeviceIndex].Attributes) {
		return(0);
	}

	Codes = (pAuthorizedCodes)(cgc_Devices[DeviceIndex].Attributes);
	for (i = 0; i < MAX_USERS; i++) {
		if (!cgc_strcmp(Codes->AccessCodes[i], TargetCode)) {
			return(1);
		}
	}

	return(0);
}

uint8_t cgc_UpdateDevice(uint16_t DeviceId) {
	uint8_t DeviceIndex;
	char Pin[6];
	char Code[32];
	uint8_t NewState;
	uint8_t NewTemperature;
	pContact ContactAttributes;
	pMotion MotionAttributes;
	pSmoke SmokeAttributes;
	pHeat HeatAttributes;

	if ((DeviceIndex = cgc_FindDeviceId(DeviceId)) == MAX_DEVICES) {
		return(0);
	}

	switch (cgc_Devices[DeviceIndex].Type) {
		case DEVICE_KEYPAD:
			// cgc_read in the PIN
			if (!cgc_ReadBytes((unsigned char *)&Pin, PIN_LEN)) {
				return(0);
			}
			Pin[PIN_LEN] = '\0';

			// see if it's valid for the specified Keypad device
			if (cgc_IsValidCredential(DeviceIndex, Pin)) {
				// yes, change the alarm state
				cgc_InvertAlarmState(DeviceIndex);
				// Process any alarm changes
				cgc_ProcessAlarms();
			}

			break;

		case DEVICE_SWIPE:
			// cgc_read in the Code
			if (!cgc_ReadBytes((unsigned char *)&Code, ACCESS_CODE_LEN)) {
				return(0);
			}
			Code[ACCESS_CODE_LEN] = '\0';

			// see if it's valid for the specified Keypad device
			if (cgc_IsValidCredential(DeviceIndex, Code)) {
				// yes, change the alarm state
				cgc_InvertAlarmState(DeviceIndex);
				// Process any alarm changes
				cgc_ProcessAlarms();
			}

			break;

		case DEVICE_CONTACT:
			// Read in the new state
			if (!cgc_ReadBytes((unsigned char *)&NewState, 1)) {
				return(0);
			}

			// Update the device state
			if (!cgc_Devices[DeviceIndex].Attributes) {
				return(0);
			}
			ContactAttributes = (pContact)(cgc_Devices[DeviceIndex].Attributes);
			ContactAttributes->State = NewState;

			// Process any alarm changes
			cgc_ProcessAlarms();

			break;

		case DEVICE_MOTION:
			// Read in the new state
			if (!cgc_ReadBytes((unsigned char *)&NewState, 1)) {
				return(0);
			}

			// Update the device state
			if (!cgc_Devices[DeviceIndex].Attributes) {
				return(0);
			}
			MotionAttributes = (pMotion)(cgc_Devices[DeviceIndex].Attributes);
			MotionAttributes->State = NewState;

			// Process any alarm changes
			cgc_ProcessAlarms();

			break;

		case DEVICE_SMOKE:
			// Read in the new state
			if (!cgc_ReadBytes((unsigned char *)&NewState, 1)) {
				return(0);
			}

			// Update the device state
			if (!cgc_Devices[DeviceIndex].Attributes) {
				return(0);
			}
			SmokeAttributes = (pSmoke)(cgc_Devices[DeviceIndex].Attributes);
			SmokeAttributes->State = NewState;

			// Process any alarm changes
			cgc_ProcessAlarms();

			break;

		case DEVICE_HEAT:
			// Read in the new state
			if (!cgc_ReadBytes((unsigned char *)&NewTemperature, 1)) {
				return(0);
			}

			// Update the device state
			if (!cgc_Devices[DeviceIndex].Attributes) {
				return(0);
			}
			HeatAttributes = (pHeat)(cgc_Devices[DeviceIndex].Attributes);
			HeatAttributes->CurrentTemperature = NewTemperature;

			// Process any alarm changes
			cgc_ProcessAlarms();

			break;


		default:
			return(0);
			break;
	}

	return(1);
}

void cgc_SortCodes(pAuthorizedCodes Codes) {
	uint8_t Sorted = 0;
	char Temp[ACCESS_CODE_LEN+1];
	int res;
	uint8_t i;

	while (!Sorted) {
		Sorted = 1;
		for (i = 0; i < MAX_DEVICES-1; i++) {
			res = cgc_strcmp(Codes->AccessCodes[i], Codes->AccessCodes[i+1]);
			if (res > 0) {
				cgc_memcpy(Temp, Codes->AccessCodes[i+1], 32);
				cgc_memcpy(Codes->AccessCodes[i+1], Codes->AccessCodes[i], 32);
				cgc_memcpy(Codes->AccessCodes[i], Temp, 32);
				Sorted = 0;
			}
		}
	}
}

uint8_t cgc_ListValidAlarmCodes(uint16_t DeviceId) {
	uint8_t DeviceIndex;
	pAuthorizedCodes codes;
	uint8_t i;
	uint8_t AlarmCodeCount = 0;

	if ((DeviceIndex = cgc_FindDeviceId(DeviceId)) == MAX_DEVICES) {
		return(0);
	}

	// make sure it's a keypad or swipe device
	if (cgc_Devices[DeviceIndex].Type != DEVICE_KEYPAD && cgc_Devices[DeviceIndex].Type != DEVICE_SWIPE) {
		return(0);
	}

	// make a copy of the device's valid codes
	if (!cgc_Devices[DeviceIndex].Attributes) {
		cgc_SendBytes((unsigned char *)&AlarmCodeCount, 1);
		cgc_SendResp(RESP_SUCCESS, NULL);
		return(1);
	}
	if ((codes = (pAuthorizedCodes)cgc_calloc(sizeof(AuthorizedCodes))) == NULL) {
		return(0);
	}
	cgc_memcpy(codes, cgc_Devices[DeviceIndex].Attributes, sizeof(AuthorizedCodes));
	cgc_SortCodes(codes);

	// once through to get a count of codes we'll be sending
	for (i = 0; i < MAX_USERS; i++) {
		if (codes->AccessCodes[i][0] == '\0') {
			continue;
		}
		AlarmCodeCount++;
	}

	// Send the count
	cgc_SendBytes((unsigned char *)&AlarmCodeCount, 1);

	// Send the codes
	for (i = 0; i < MAX_USERS; i++) {
		if (codes->AccessCodes[i][0] == '\0') {
			continue;
		}
		cgc_SendBytes((unsigned char *)&codes->AccessCodes[i], 32);
	}

	cgc_SendResp(RESP_SUCCESS, NULL);

	cgc_free(codes);

	return(1);
}
