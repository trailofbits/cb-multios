# Divelogger

## Author Information

"Jason Williams" <jdw@cromulence.co>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service is an implementation of Divelogger using C++ instead of C. This service accepts diver information and has the ability to log dives into a database.

### Feature List

The service features the ability to enter diver specific information: Phone Number, First Name, Last Name, etc. It also has the ability to enter individual dive information such as location, date, average and max depth, dive duration, etc. The user can insert, remove, add, or download dive data into the database. During download the service accepts binary timestamps and depth points and stores those in the dive log.

## Vulnerability

There is one vulnerability in this service. It is associated with the download dive functionality. During the download process the user enters binary data into the service and this data is entered as two 4-byte number (a timestamp and depth point). A static array is used to store these points in memory. In the vulnerable service upon entry the array length is not checked allowing the user to overflow this variable and corrupt the heap. If the data passes a page boundary (or future memory allocation/free operations) occur a page fault can occur resulting in a crash.

### Generic class of vulnerability

Out of bounds write

### CWE classification
CWE-119: Improper Restriction of Operations within the Bounds of a Memory Buffer

## Challenges

This CB incorporates a single vulnerability. This vulnerability will require a CRS system to enter the appropriate state (navigating the state machine) and entering more than 128 dive points when downloading dive data. The difficulty lies in the numerous code paths available in the service as well as the unconstrained inputs available to the user.
