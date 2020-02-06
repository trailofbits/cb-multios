# CGC Challenge Binary Template

## Author Information

"Ben Schmidt" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

SafeTechs is proud to announce the latest in our ever-expanding line of cloud offerings: GreatView, a memory-as-a-service (MaaS) technology that allows you to easily expand the amount of memory to a local application.
As an added benefit, you can retrieve this stored data in any number of supported views, abstracting away all the hassle of converting endianess and data types.


### Feature List

Using our patent-pending array management language, you can quickly and easily store and retrieve arbitrary values in any way that you so choose.
Because all the data is stored in memory, and our servers are located in some of the fastest data centers in the world, you can be certain that you can access this data as fast as possible.


## Vulnerability

The main vulnerability in this CB is based closely off of CVE-2014-1705, a vulnerability in V8's handling of ArrayViews that lead to an arbitrary read-write of memory.
In this CVE, by defining a getter for the byteLength attribute of an Array object, it was possible to fool the ArrayView constructor into creating a view with arbitrary bounds.
Similarly, this CB allows users to override the byteSize attribute of a view with a summation of declared variables, which will then be trusted by get and set functions.
This leads to an arbitrary read-write to the entire process space.

There is an additional vulnerability that causes a tokenization function to write outside the bounds of the lines array.
Due to improper bounds checking, it is possible to cause run\_viewscript to add more lines to the lines array than it has allocated, leading to a crash.

### Generic class of vulnerability

Improper bounds checking

### CWE classification

CWE-131: Incorrect Calculation of Buffer Size
CWE-787: Out-of-bounds Write

## Challenges
Discovery of this vulnerability requires the CRS to utilize the ability to set the byteSize attribute of a view to access outside the bounds of the array.
As no example of this is provided in pollers, competitors' must independently discover that this is possible, and properly create and reference variables with large enough values to access outside the bounds of the view.

Patching will also prove difficult, as a CRS must properly enforce bounds checking of the array to prevent all crashes.
Multiple PoVs exercising the vulnerability in different ways have been provided for reference.
