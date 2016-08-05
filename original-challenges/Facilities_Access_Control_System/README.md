# Facilities_Access_Control_System

## Author Information

"Joe Rogers" <joe@cromulence.com>

### DARPA performer group
Cromulence (CROMU)

## Description
This CB implements a basic facility security system.  It takes inputs from door contact, heat sensors, smoke alarms, motion sensors, keypads and card swipes.  Users can be added or deleted from the system, and they can be granted access to specific keypads and card swipes.  Input devices are then associated with alarm devices which read sensors throughout the facility and can be armed or disarmed using keypad or card swipe devices.

Once the devices and users are defined, the CRS can send inputs to the various devices to change their state (ie: motion detected/not-detected, contact open/closed).  And based on these state changes, a given alarm might be triggered.  

### Feature List
- 5-digit PIN numbers for keypads
- 32-digit codes for card swipes
- Alarms capable of monitoring door contacts, heat sensors, smoke alarms, and motion sensors
- Binary interface suitable for integration with any user interface front-end
- User creation and deletion
- User access controls per keypad or card swipe

## Vulnerability
The CB is designed to handle up to 128 users (with UserID's 0 - 127).  User information is stored in an appropriately sized array.  However, a mistake in the AddUser function allows the signed 8-bit integer used for array indexing to take on a value of -1 if an attempt is made to create 129 users.  

This out-of-bounds write allows portions of the preceding Device array to be overwritten.  The device array contains a pointer to device-specific information for the various device types supported by the CB.  For keypad and card swipe devices, this pointer references memory containing the valid pin and codes for those devices.  And, there exists a function available to the user to list all pins and codes for those types of devices.  If the overwritten device entry is properly formatted to look like a keypad or card swipe device, and if the pointer is set to the address of the magic page, a type 2 vulnerability exists.

### Generic class of vulnerability
Integer overflow leading to an out-of-bounds array write

### CWE classification
CWE-190: Integer Overflow or Wraparound
CWE-787: Out-of-bounds Write

## Challenges
The integer overflow should be relatively easy to identify.  Determining that this overflow can be used to craft a specific type of device and then use that device's pointer to access the magic page will be more difficult.

Discovering - Easy
Proving - Medium
Fixing - Easy
