# Thermal_Controller_v3

## Author Information

"James Connor" <jymbo@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This is a software re-implementation of Thermal controller software and simulation, a heating element controller such as would be used in commercial oven, BBQ smoker, or other industrial control device.

### Feature List

The thermal controller is much more capable than the typical controller found in consumer level appliances such as stoves.  Although it does contain static modes such a maintaining a set temperature, it also supports up to 10 temperature sensors, a smoke sensor, and a 10 step programmable thermal profile.  The different program steps can be based on temperature triggers from any of the configured temperature probes, or can dwell at a fixed temperature for a programmed length of time.  An ideal use of this controller would be in a competition BBQ smoker where different kinds of meat require finely tuned adjustments to temperature during the smoking process to result in proper breakdown of connective tissue, maintenance of moinsture, and control of the smoke generation.  The controller was designed to be remotely operated using a separate "app" on a mobile device, and implements a binary protocol for this purprose.  The controller was designed to be robust and rigorously checks that remote commands correctly configure the device. 

## Vulnerability
A vulnerability exists when the history list is populated with too many entries and can cause a buffer overflow of the send buffer. The last 8-bytes of the sent information for a simulate command contains the ambient temperature and the last set temperature for the thermal controller. It is possible to arbitrarily control the set temperature by sending a program list with a negative value for type. Due to an incorrect check (a signed/unsigned error) allows arbitrary set temperatures to be written by avoiding the temperature range checks. Next it is possible to write an arbitrary ambient temperature, again, due to an incorrect comparison checked of signed data (failing to validate negative numbers). This ultimately results in the ability to overflow the send buffer (which is allocated on the stack) with two arbitrary 4-byte values that results in a type-1 POV when the return address for the get_command function is overwritten.

### Generic class of vulnerability
Vulnerability 1 of 1:
Stack buffer overflow

### CWE classification
Vulnerability 1 of 1:
CWE-121 Stack-based Buffer Overflow

## Challenges

Authors Subjective Challenge Difficulty:
Discovering: Medium
Proving: Medium
Fixing: Easy

This vulnerability is considered to be on the harder side of proving due to the conditions that are needed to properly trigger a type-1 vulnerability. Due to its nature fixing the vulnerability is a trivial as it involves fixing the type checks to unsigned values. There may be some difficulty for the CRS in discovering all of the initial conditions needed to trigger and prove the vulnerability in this service.

