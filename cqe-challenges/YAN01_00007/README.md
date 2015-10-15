# Diophantine Password Wallet

## Description

This service is supposed to be a simple service where a user can login to the service and and then *add*, *delete* and *print* out the list of currently stored passwords. The strange thing about this service is that the passwords must all be 3rd power diophantine equations in the form of secret1^3 + secret2^3 + secret3^3 = stored-secret^3. 

This CB is meant to be a harder version of YAN01_00008, but is also provided to help CRS authors to test their solver integration. What makes this CB more difficult than the other is that, the uint32 numbers are converted into 256bit large ints before addition and multiplication takes place. This and the fact that numbers are entered as ascii decimal numbers and then converted into uint32_t also obfuscates the process.

## Vulnerabilities

There is a null pointer dereference vulnerability. The vulnerability arises from the fact that some numbers *d* have more than one solution to a^3 + b^3 + c^3 = d^3, but the CB itself only initializes the function pointers for one set of solutions. In this way, finding the alternative solution will result in a null pointer derefernece. This falls under [CWE-824: Access of Uninitialized Pointer](http://cwe.mitre.org/data/definitions/824.html) and [CWE-476: Null Pointer Derefernece](http://cwe.mitre.org/data/definitions/476.html).

## Notes

The CB itself doesn't actually check to make sure that the passwords stored in the database satisfy the constraint mentioned in the description.
