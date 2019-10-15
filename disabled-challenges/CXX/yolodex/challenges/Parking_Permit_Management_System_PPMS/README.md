# CGC Challenge Binary (KPRCA\_00027): Parking Permit Management System (PPMS)

### DARPA performer group
Kaprica Security (KPRCA)

## Description

PPMS is a simple service that supports a binary protocol to create and test one or more parking permits for the parking lot owner. This is meant to be used in embedded devices, so it has very limited features. The data returned from the service can be parsed and written on to the permit card. Since this system is used for VIP car owners that have multiple cars, it provides a "permit ring", which is like a key ring where multiple permits (up to 5) can be stored on a single card. Master key is needed to authenticate the manager, before using any of the features.

### Feature List

- ***Authenticate the manager (using the master key)***
  - When authenticated, the session key is created and returned.
  - The session key expires after 3 valid requests.
  - The session key needs to be renewed once expired.
- ***Create a parking permit***
  - Valid session key is required.
  - On request, a permit data with the valid permit token is returned.
  - Request must specify the number of allowed entrances/exits, license number of the vehicle, and the parking spot number to be used for the permit.
- ***Create a parking permit ring***
  - Valid session key is required.
  - On request, a permit ring data with the appropriate permits is returned.
  - Request must specify a valid permits to combine into a ring.
- ***Refactor a parking permit ring***
  - Valid session key is required.
  - On request, the permit ring is refactored by removing expired permits (i.e. the permits that have 0 allowed entrance left).
  - Request must specify a valid permit ring to be refactored.
- ***Test a parking permit***
  - Valid session key is required.
  - On request, the permit is reviewed and tested for its validity: valid token, expiration, valid spot, valid license number.
  - Request must specify a valid permit to be tested.
- ***Test a parking permit ring***
  - Valid session key is required.
  - On request, the permit ring is reviewed and tested for its validity: all permits inside of the ring must be valid.
  - Request must specify a valid permit ring to be tested.


## Vulnerability

The vulnerability exists in the function that handles creating a new permit ring based on user-supplied data. The user can specify the count of permits that they want to include in a permit ring, which is limited to the maximum number of permits in a single permit ring, 5. However, when the program iterates through and copies over the data to a permit ring data structure on the stack, it may copy 1 more parking permit data due to a failure in loop condition.

Instead of having the condition to be ***i < count***, ***i <= count*** is used. However, in normal situations, this would not trigger a stack buffer overflow since the following data (supposedly 6th permit data) must pass the ***permit_test*** function's validity test -- only when it passes the check, the data gets copied over. With a carefully crafted input, it is possible to arbitrarily control the EIP by overwriting the local variable (_count_) to copy more data onto the stack.

### Generic class of vulnerability

Stack Buffer Overlfow
Off-by-one Error

### CWE classification

Stack-based Buffer Overflow (CWE-121)
Off-by-one Error (CWE-193)

## Challenges

The competitors need to analyze and find out about the hard-coded data (master key) in order to generate valid session keys, which are random each time they are generated and expire in 3 actions. In order to trigger the bug successfully, good understanding of stack structure (location of local variables and their usage) is important as well as computing the correct token values (constraint solving).
