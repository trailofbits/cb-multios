# Trust_Platform_Module

@Author: Lok Yan <Lok.Yan@us.af.mil>
@Group: AFRL

## Description:

The Trusted Platform Module is a specialized piece of hardware that can 1. securely store cryptographic keys, 2. support public key crypto such as RSA and 3. supports a cryptographic hash function such as SHA-1. 

This service is a simple TPM service that only supports the cryptographic hash function (implemented as an XOR hash). Additionally, the secure storage is implemented as a number of Platform Configuration Registers (PCRs) that can only be reset, zeroed or extended (i.e. the value can't be set directly).

This particular TPM supports the following commands which are newline terminated.

R - Resets the PCRs to special values of 0X0X0X... where X is the PCR number (0-7)
Z # - Zeroes out the PCR #
E # ## ### - Extends PCR # with the data from address ## to ## + ### (where ### is the size). Extend is basically XOR(HASH(## -> ##+###), #) that is, we xorhash the current PCR value with the hash of the memory in the range from ## to ##+###. Note that if the memory is not mapped, then it will be treated as 0 - meaning the current PCR value is not changed.
H # DDDD - Hashes the data from DDDD which is of length #. Note that there is a newline between the # and DDDD meaning we first submit the hashing command and then follow through with the data to be hashed. THe hash value is returned back immediately.
P # - Prints the value of the PCR at #

## Vulnerability Class:

There are two vulnerabilities. The first is a classic buffer overflow (CWE-121: Stack-baed Buffer Overflow) which results in a type 1 POV. The overflow results when too long of a command string is passed into the program.

The second vulnerability is the inadvertent disclosure which is due to the Extend functionality (CWE-202: Exposure of Sensitive Data Through Data Queries). Since a real TPM should have access to all of memory, this inadvertent disclosure isn't much of a problem (that plus cryptographic hash functions are one-way), however since we are using XOR as the hash, we can recover the original value. In the case of the MAGIC page with the secret data for a Type 2 POV, the pages around it don't exist and therefore should be 0. and since 0 XOR X is always X, this means we can just read the value straight out from the output of Extend followed by a Print

## Notes:

One of the uses of a Trusted Platform Module is to perform measurements. In particular, TPMs support both a static root of trust for measurement (i.e. you cryptographically hash binaries before they are loaded starting from system boot) and dynamic root of trust for measurement (i.e. you stop the system, load a special piece of software to bootstrap the measurement process, and use the TPM to cryptographically hash memory such as binaries, to ensure that they are as expected). This binary implements the dynamic root of trust for measurement functionality by having polls that will measure the binary by computing an XOR hash of the binary's .text and .data sections and comparing the value to a known value.

Since the regular version and the patched binaries differ, the poll generator includes a python script that effectively performs a hexdump on both binaries, finds the differences, and then ensure that the XOR hash doesn't include the difference bytes. In this way, the polls will pass both the vulnerable binary and patched binary.
