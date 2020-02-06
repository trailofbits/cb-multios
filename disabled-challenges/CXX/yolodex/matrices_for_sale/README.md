# CGC Challenge Binary Template

## Author Information

"Jason Rogers" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description

Too lazy to compute your own matrices? Let our workers do it for you. They'll process your messages in their super-speed pipeline, while you sit back and relax. 


### Feature List

The first message you send provides the configuration of the pipeline. From there each subsequent message uses the same pipele, for super-speed operation. Since the pipeline only moves as fast as you submit messages, always make sure to clear the pipeline when you are done. 

Message structure is the following
{Configuration, Array length, Array width, X Plotter, Y Plotter}

"Configuration" will be used to configure the pipeline
"Array length" and "Array width" configure the dimensions of the matrix.
"X Plotter" and "Y Plotter" drive the computation of the matrix.


## Vulnerability
This service has three vulnerabilties.

The first vulnerability will trigger if negative dimensions are submitted in a pipeline configuration where the modulus of the X plotter and Y plotter are configured before the dimensions are set to the absolute value. The modulus computation will result in negative plotter values. The first array assigment will use the negative values leading to an out-of-bounds write.

The second vulnerability will trigger if X Plotter or Y Plotter values are sumbitted. When the matrix is computed these values will be doubled as part of the modulus computation, resulting in an integer overlfow that causes a negative X Plotter or Y Plotter value. Similarily to the first vulnerability this will result in the same out-of-bounds write.

The third vulnerability will trigger if any of the message values for X_FIELD or Y_FIELD are equal to -32768. When the absoluteValueMap function is run, -32768 will remain -32768 due to the compiler using the 2's complete notation. When computeResult attempts to use assign '1' to the array using a negative offset it will result in an out-of-bounds write.

### Generic class of vulnerability
Out-of-bounds Write
Integer Overflow
Improper Validation of Array Index

### CWE classification
CWE-787: Out-of-bounds Write
CWE-190: Integer Overflow
CWE-129: Improper Validation of Array Index

## Challenge

1) Understand how the "Configuration" value provided by the client influences the permutation of message processing functions and the resulting output, in order to produce an exploitable configuration of the pipeline. 

2) Determine how the modulus calculation is impacted by negative inputs. Both vulnerabilities require achieving a negative result from the modulus calculation.
