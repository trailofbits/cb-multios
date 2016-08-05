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
#include "malloc.h"
#include "string.h"
#include "device.h"
#include "user.h"
#include "io.h"
#include "alarm.h"

Device Devices[MAX_DEVICES];

extern User Users[MAX_USERS];
const uint32_t *MagicPage = (const uint32_t *)0x4347C000;
uint16_t MagicIndex = 0;

// Generate a new DeviceId
uint16_t NewDeviceId(void) {
	uint16_t DeviceId;

	// Generate a 2-byte DeviceId from a 4-byte magic page value
	DeviceId = MagicPage[MagicIndex] % 65534;
	MagicIndex = (MagicIndex+1)%1024;

	// make sure the new ID is not zero (reserved) and isn't already in use
	while (DeviceId == 0 || (FindDeviceId(DeviceId) != MAX_DEVICES)) {
		DeviceId = MagicPage[MagicIndex] % 65534;
		MagicIndex = (MagicIndex+1)%1024;
	}

	return(DeviceId);
}

// Find an available device index
uint8_t FindAvailableDevice(void) {
	uint8_t i;
	uint8_t NewDevice = MAX_DEVICES+1;

	for (i = 1; i < MAX_DEVICES; i++) {
		if (Devices[i].Type == DEVICE_UNUSED) {
			NewDevice = i;
			break;
		}
	}
			
	return(NewDevice);
}

// Find a device given its DeviceId value
uint8_t FindDeviceId(uint16_t TargetId) {
	uint8_t i;

	for (i = 0; i < MAX_DEVICES; i++) {
		if (Devices[i].Type != DEVICE_UNUSED && Devices[i].DeviceId == TargetId) {
			break;
		}
	}

	return(i);

}

// Add device
uint16_t NewGenericDevice(uint8_t DeviceType, uint8_t NewDevice) {
	uint16_t DeviceId = NewDeviceId();
	
	// No device-specific attributes for this type device, so just
	// Add the new device
	Devices[NewDevice].Type = DeviceType;
	Devices[NewDevice].DeviceId = DeviceId;
	Devices[NewDevice].Attributes = NULL;

	return(DeviceId);
}

uint16_t NewContact(uint8_t NewDevice) {
	uint16_t DeviceId = NewDeviceId();
	uint8_t Mode;
	uint8_t State;
	pContact NewContact;

	// Read in the device-specific attributes
	if (!ReadBytes((unsigned char *)&Mode, 1)) {
		return(0);
	}
	if (!ReadBytes((unsigned char *)&State, 1)) {
		return(0);
	}
	
	// Add the new device
	Devices[NewDevice].Type = DEVICE_CONTACT;
	Devices[NewDevice].DeviceId = DeviceId;
	if ((NewContact = (pContact)calloc(sizeof(Contact))) == NULL) {
		return(0);
	}
	NewContact->Mode = Mode;
	NewContact->State = State;
	Devices[NewDevice].Attributes = NewContact;

	return(DeviceId);

}

uint16_t NewMotion(uint8_t NewDevice) {
	uint16_t DeviceId = NewDeviceId();
	uint8_t State;
	pMotion NewMotion;

	// Read in the device-specific attributes
	if (!ReadBytes((unsigned char *)&State, 1)) {
		return(0);
	}
	
	// Add the new device
	Devices[NewDevice].Type = DEVICE_MOTION;
	Devices[NewDevice].DeviceId = DeviceId;
	if ((NewMotion = (pMotion)calloc(sizeof(Motion))) == NULL) {
		return(0);
	}
	NewMotion->State = State;
	Devices[NewDevice].Attributes = NewMotion;

	return(DeviceId);

}

uint16_t NewHeat(uint8_t NewDevice) {
	uint16_t DeviceId = NewDeviceId();
	uint8_t CurrentTemperature;
	uint8_t ThresholdTemperature;
	pHeat NewHeat;

	// Read in the device-specific attributes
	if (!ReadBytes((unsigned char *)&CurrentTemperature, 1)) {
		return(0);
	}
	
	if (!ReadBytes((unsigned char *)&ThresholdTemperature, 1)) {
		return(0);
	}
	
	// Add the new device
	Devices[NewDevice].Type = DEVICE_HEAT;
	Devices[NewDevice].DeviceId = DeviceId;
	if ((NewHeat = (pHeat)calloc(sizeof(Heat))) == NULL) {
		return(0);
	}
	NewHeat->CurrentTemperature = CurrentTemperature;
	NewHeat->ThresholdTemperature = ThresholdTemperature;
	Devices[NewDevice].Attributes = NewHeat;

	return(DeviceId);

}

uint16_t NewSmoke(uint8_t NewDevice) {
	uint16_t DeviceId = NewDeviceId();
	uint8_t State;
	pSmoke NewSmoke;

	// Read in the device-specific attributes
	if (!ReadBytes((unsigned char *)&State, 1)) {
		return(0);
	}
	// Add the new device
	Devices[NewDevice].Type = DEVICE_SMOKE;
	Devices[NewDevice].DeviceId = DeviceId;
	if ((NewSmoke = (pSmoke)calloc(sizeof(Smoke))) == NULL) {
		return(0);
	}
	NewSmoke->State = State;
	Devices[NewDevice].Attributes = NewSmoke;

	return(DeviceId);

}

// Delete Device 
uint8_t DeleteDevice(uint16_t DeviceId) { 
	uint8_t Target; 
	uint8_t i;
	uint8_t j;
	pAlarmAttributes AA;
	
	if ((Target = FindDeviceId(DeviceId)) == MAX_DEVICES) {
		return(0);
	}

	// remove it from any alarms that reference it
	for (i = 0; i < MAX_DEVICES; i++) {
		if (Devices[i].Type != DEVICE_ALARM) {
			continue;
		}
		if (!Devices[i].Attributes) {
			continue;
		}
		AA = (pAlarmAttributes)(Devices[i].Attributes);
		for (j = 0; j < MAX_DEVICES; j++) {
			if (AA->DeviceList[j] == Target) {
				AA->DeviceList[j] = DEVICE_UNUSED;
				break;
			}
		}
	}

	// Process any changes in alarm state that would result from
	// this device being removed
	ProcessAlarms();

	// remove the device
	Devices[Target].Type = DEVICE_UNUSED;
	Devices[Target].DeviceId = 0;
	if (Devices[Target].Attributes) {
		free(Devices[Target].Attributes);
		Devices[Target].Attributes = NULL;
	}

	return(1);
}


// Grant user access to device
uint8_t GrantAccess(uint16_t DeviceId, uint8_t UserId) {
	pAuthorizedCodes codes;
	uint8_t i;
	uint8_t NewCode;
	uint8_t DeviceIndex;

	// Look up the device index
	if ((DeviceIndex = FindDeviceId(DeviceId)) == MAX_DEVICES) {
		return(0);
	}

	// make sure it's a keypad or swipe device
	if (Devices[DeviceIndex].Type != DEVICE_KEYPAD && Devices[DeviceIndex].Type != DEVICE_SWIPE) {
		return(0);
	}

	// validate the userid
	if (UserId > MAX_USERS) {
		return(0);
	}
	if (Users[UserId].Username[0] == '\0') {
		return(0);
	}

	// allocate new attributes buffer if it's not already in place
	if (!Devices[DeviceIndex].Attributes) {
		if ((codes = (pAuthorizedCodes)calloc(sizeof(AuthorizedCodes))) == NULL) {
			return(0);
		}
		Devices[DeviceIndex].Attributes = codes;
	} else {
		codes = (pAuthorizedCodes)(Devices[DeviceIndex].Attributes);
	}

	// Find an open authorized code slot
	NewCode = MAX_USERS;
	for (i = 0; i < MAX_USERS; i++) {
		if (codes->AccessCodes[i][0] == '\0' && NewCode == MAX_USERS) {
			// found a open slot
			NewCode = i;
		}
		if (!strcmp(codes->AccessCodes[i], Users[UserId].Pin) || !strcmp(codes->AccessCodes[i], Users[UserId].AccessCode)) {
			// code is already in the list
			return(1);
		}
	}
	if (NewCode == MAX_USERS) {
		// No available slots
		return(0);
	}

	// Add the pin to a Keypad device
	if (Devices[DeviceIndex].Type == DEVICE_KEYPAD) {
		strcpy(codes->AccessCodes[NewCode], Users[UserId].Pin);
		codes->AccessCodes[NewCode][PIN_LEN] = '\0';
	// Add the access code to a swipe device
	} else if (Devices[DeviceIndex].Type == DEVICE_SWIPE) {	
		strcpy(codes->AccessCodes[NewCode], Users[UserId].AccessCode);
		codes->AccessCodes[NewCode][ACCESS_CODE_LEN] = '\0';
	}

	return(1);
}

uint8_t RevokeAccess(uint8_t UserIndex) {
	uint8_t i;
	uint8_t j;
	pAuthorizedCodes codes;

	// run through the devices
	for (i = 0; i < MAX_DEVICES; i++) {
		// only need to remove users from keypads and swipes
		if (Devices[i].Type != DEVICE_KEYPAD && Devices[i].Type != DEVICE_SWIPE) {
			continue;	
		}

		// See if this device has any pins or access codes associated with it
		if (!Devices[i].Attributes) {
			continue;
		}
		codes = Devices[i].Attributes;
		
		// run through the codes on this device
		for (j = 0; j < MAX_USERS; j++) {
			if (!strcmp(codes->AccessCodes[j], Users[UserIndex].Pin) || !strcmp(codes->AccessCodes[j], Users[UserIndex].AccessCode)) {
				// found matching code, remove it
				codes->AccessCodes[j][0] = '\0';
			}
		}
	}

	return(1);
}

// Associate device with alarm
uint8_t AddDeviceToAlarm(uint16_t DeviceId, uint16_t AlarmId) {
	uint8_t DeviceIndex;
	uint8_t AlarmIndex;
	pAlarmAttributes AA;
	uint8_t NewDevice;
	uint8_t i;

	if ((DeviceIndex = FindDeviceId(DeviceId)) == MAX_DEVICES) {
		return(0);
	}

	if ((AlarmIndex = FindDeviceId(AlarmId)) == MAX_DEVICES) {
		return(0);
	}

	// allocate new attributes buffer if it's not already in place
	if (!Devices[AlarmIndex].Attributes) {
		if ((AA = (pAlarmAttributes)calloc(sizeof(AlarmAttributes))) == NULL) {
			return(0);
		}
		Devices[AlarmIndex].Attributes = AA;
	} else {
		AA = (pAlarmAttributes)(Devices[AlarmIndex].Attributes);
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
	ProcessAlarms();

	return(1);
}

uint8_t IsValidCredential(uint8_t DeviceIndex, char *TargetCode) {
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
	if (Devices[DeviceIndex].Type != DEVICE_KEYPAD && Devices[DeviceIndex].Type != DEVICE_SWIPE) {
		return(0);
	}

	// Does this device have attributes defined yet?
	if (!Devices[DeviceIndex].Attributes) {
		return(0);
	}

	Codes = (pAuthorizedCodes)(Devices[DeviceIndex].Attributes);
	for (i = 0; i < MAX_USERS; i++) {
		if (!strcmp(Codes->AccessCodes[i], TargetCode)) {
			return(1);
		}
	}

	return(0);
}

uint8_t UpdateDevice(uint16_t DeviceId) {
	uint8_t DeviceIndex;
	char Pin[6];
	char Code[32];
	uint8_t NewState;
	uint8_t NewTemperature;
	pContact ContactAttributes;
	pMotion MotionAttributes;
	pSmoke SmokeAttributes;
	pHeat HeatAttributes;

	if ((DeviceIndex = FindDeviceId(DeviceId)) == MAX_DEVICES) {
		return(0);
	}

	switch (Devices[DeviceIndex].Type) {
		case DEVICE_KEYPAD:
			// read in the PIN
			if (!ReadBytes((unsigned char *)&Pin, PIN_LEN)) {
				return(0);
			}
			Pin[PIN_LEN] = '\0';
	
			// see if it's valid for the specified Keypad device
			if (IsValidCredential(DeviceIndex, Pin)) {
				// yes, change the alarm state
				InvertAlarmState(DeviceIndex);
				// Process any alarm changes
				ProcessAlarms();
			} 

			break;

		case DEVICE_SWIPE:
			// read in the Code
			if (!ReadBytes((unsigned char *)&Code, ACCESS_CODE_LEN)) {
				return(0);
			}
			Code[ACCESS_CODE_LEN] = '\0';
	
			// see if it's valid for the specified Keypad device
			if (IsValidCredential(DeviceIndex, Code)) {
				// yes, change the alarm state
				InvertAlarmState(DeviceIndex);
				// Process any alarm changes
				ProcessAlarms();
			} 

			break;

		case DEVICE_CONTACT:
			// Read in the new state
			if (!ReadBytes((unsigned char *)&NewState, 1)) {
				return(0);
			}

			// Update the device state
			if (!Devices[DeviceIndex].Attributes) {
				return(0);
			}
			ContactAttributes = (pContact)(Devices[DeviceIndex].Attributes);
			ContactAttributes->State = NewState;

			// Process any alarm changes
			ProcessAlarms();
			
			break;

		case DEVICE_MOTION:
			// Read in the new state
			if (!ReadBytes((unsigned char *)&NewState, 1)) {
				return(0);
			}

			// Update the device state
			if (!Devices[DeviceIndex].Attributes) {
				return(0);
			}
			MotionAttributes = (pMotion)(Devices[DeviceIndex].Attributes);
			MotionAttributes->State = NewState;

			// Process any alarm changes
			ProcessAlarms();
			
			break;

		case DEVICE_SMOKE:
			// Read in the new state
			if (!ReadBytes((unsigned char *)&NewState, 1)) {
				return(0);
			}

			// Update the device state
			if (!Devices[DeviceIndex].Attributes) {
				return(0);
			}
			SmokeAttributes = (pSmoke)(Devices[DeviceIndex].Attributes);
			SmokeAttributes->State = NewState;

			// Process any alarm changes
			ProcessAlarms();
			
			break;

		case DEVICE_HEAT:
			// Read in the new state
			if (!ReadBytes((unsigned char *)&NewTemperature, 1)) {
				return(0);
			}

			// Update the device state
			if (!Devices[DeviceIndex].Attributes) {
				return(0);
			}
			HeatAttributes = (pHeat)(Devices[DeviceIndex].Attributes);
			HeatAttributes->CurrentTemperature = NewTemperature;

			// Process any alarm changes
			ProcessAlarms();
			
			break;


		default:
			return(0);
			break;
	}

	return(1);
}

void SortCodes(pAuthorizedCodes Codes) {
	uint8_t Sorted = 0;
	char Temp[ACCESS_CODE_LEN+1];
	int res;
	uint8_t i;

	while (!Sorted) {
		Sorted = 1;
		for (i = 0; i < MAX_DEVICES-1; i++) {
			res = strcmp(Codes->AccessCodes[i], Codes->AccessCodes[i+1]);
			if (res > 0) {
				memcpy(Temp, Codes->AccessCodes[i+1], 32);
				memcpy(Codes->AccessCodes[i+1], Codes->AccessCodes[i], 32);
				memcpy(Codes->AccessCodes[i], Temp, 32);
				Sorted = 0;
			}
		}
	}
}

uint8_t ListValidAlarmCodes(uint16_t DeviceId) {
	uint8_t DeviceIndex;
	pAuthorizedCodes codes;
	uint8_t i;
	uint8_t AlarmCodeCount = 0;

	if ((DeviceIndex = FindDeviceId(DeviceId)) == MAX_DEVICES) {
		return(0);
	}

	// make sure it's a keypad or swipe device
	if (Devices[DeviceIndex].Type != DEVICE_KEYPAD && Devices[DeviceIndex].Type != DEVICE_SWIPE) {
		return(0);
	}

	// make a copy of the device's valid codes
	if (!Devices[DeviceIndex].Attributes) {
		SendBytes((unsigned char *)&AlarmCodeCount, 1);
		SendResp(RESP_SUCCESS, NULL);
		return(1);
	}
	if ((codes = (pAuthorizedCodes)calloc(sizeof(AuthorizedCodes))) == NULL) {
		return(0);
	}
	memcpy(codes, Devices[DeviceIndex].Attributes, sizeof(AuthorizedCodes));
	SortCodes(codes);

	// once through to get a count of codes we'll be sending
	for (i = 0; i < MAX_USERS; i++) {
		if (codes->AccessCodes[i][0] == '\0') {
			continue;
		}
		AlarmCodeCount++;
	}

	// Send the count
	SendBytes((unsigned char *)&AlarmCodeCount, 1);

	// Send the codes
	for (i = 0; i < MAX_USERS; i++) {
		if (codes->AccessCodes[i][0] == '\0') {
			continue;
		}
		SendBytes((unsigned char *)&codes->AccessCodes[i], 32);
	}

	SendResp(RESP_SUCCESS, NULL);

	free(codes);

	return(1);
}
