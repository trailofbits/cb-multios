# REMATCH_2--Mail_Server--Crackaddr

## Author Information

debbie@cromulence.com

### DARPA performer group
Cromulence LLC (CROMU)

## Description
This binary mimics the function in sendmail that was vulnerable to CVE-2002-1337 commonly known as the crackaddr bug. Sendmail is an email server originally published in 1983. The CVE-2002-1337 was a buffer overflow in the crackaddr function for email address parsing. In 2011, 8 years after the bug was published, security researcher Thomas Dullien (AKA Halvar Flake) showcased the bug as something static analysis tools were unable to detect and created a simplified implementation to demonstrate that point. Since then, multiple teams have used the crackaddr bug as a litmus test for the real world viability of analysis tools. To date some tools have been able to detect the vulnerability in the simplified version but not the original. This implementation closely mimics the original bug in sendmail.  

### Feature List
The crackaddr function in sendmail was created to parse addresses with a complex combination of embedded parenthesis, angle brackets, quotes, and grouping syntax. The function recreated here adds in some additional complexity from the original function and changes all the special characters to other ascii values. 

## Vulnerability
The vulnerability is an error in how the while loop keeps track of matching "brackets". A pointer is used to indicate the end of the expected output stream. That pointer is manipulated to make sure there is enough room to close out any opened brackets with matching close brackets. The error occurs when the pointer is incremented on a close bracket, but not decremented on the previous open bracket. This allows the pointer to end up pointing past the end of the actual output buffer, alowing the input stream to overwrite a portion of the stack. 

### Generic class of vulnerability
Buffer Overflow

### CWE classification
CWE-120 Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')

## Challenges
The crackaddr function poses a complex challenge to the CRS. The unbounded nature of the input prevents imposing a simple size restriction because that would lead to failing valid polls. The CRS must then interpret exactly which overly long inputs would result in an overflow of the output. The crackaddr function modifies the output bounds based on the sequence of input characters in a while loop which quickly leads to an unmanageable state equation for the CRS. 
 
