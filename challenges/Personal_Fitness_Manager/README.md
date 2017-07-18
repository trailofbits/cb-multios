# Personal_Fitness_Manager

## Author Information

"James Nuttall" <james@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

A fitness tracker that allows different types of fitness sensors to attach, detach, input data, and list sensors.

### Feature List

Users may register with the system, request a list of acceptable register types, register sensors, and input data for each sesnsor.

During initialization, the system reads from the magic page to populate the hardware IDs for each type of sensor (Heart, Step, Bike, Scale, Run). These IDs must be the first byte in each sensor's MAC address during initial sensor registration.

Each sensor can be added, removed, and send data for each user. Each user 'owns' the sensors connected to their profile. The sensor manager can also list all attached sensors for all users.

Register User - Register a user
Change to User - Change to a registed user
Register Sensor - Register a sensor with a valid hardware ID
Send Sensor Data - Send sensor data to a registered sensor
Request Sensors - Request a list of all sensors (by sensor ID and MAC address) registered to the system
Remove Sensor - Remove a sensor (by sensor ID) from the system
Request Hardware IDs - Return a list of each sensor's HW ID

## Vulnerability

The POV for this CB takes advantage of the ability of the CRS to create a multiple users, each of which can have multiple sensors. When the CRS asks the service to return a list of all sensors, it only allocates enough space for 7 users each with 3 sensors. If the CRS creates an eighth user with a sensor, this buffer will be overflown with the content of the eighth user's sensor HW ID.  

### Generic class of vulnerability
Stack buffer overflow

### CWE classification
CWE-131: Incorrect Calculation of Buffer Size
CWE-121: Stack-based Buffer Overflow


## Challenges
Subjective Quantification:
Discovering - Medium
Proving - Hard
Fixing - Easy
