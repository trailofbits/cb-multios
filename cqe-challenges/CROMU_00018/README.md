# Vector Graphics Format

## Author Information

"Jason Williams" <jdw@cromulence.co>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service implements a simple vector graphics renderer. An input file is received and parsed into a file data structure. Next it is rendered into an output buffer and written out to pixel map file in RGB 24-bit color format. This service supports drawing lines, circles, triangles, and rectangles.

### Feature List

This service features the ability to render lines, triangles, circles or rectangles in any color on multiple layers. The layers are combined into a final render layer. The input format for the service is a binary file known as a VGF (Vector Graphics Format) file that contains the information for rendering the objects to the pixel map file. Upon any error conditions the service terminates. Memory allocation is handled by heap allocations using malloc/free

## Vulnerability

There are two vulnerabilities in this service. The first vulnerability is easily reached and occurs in the file receiving routines of the service. The service accepts a 16-bit signed integer for the file size of the incoming VGF file. It is compared against a maximum input file size. It is possible by using negative numbers to craft an input number that passes the maximum file size check and allows more than the maximum number of bytes allocated off the heap for the file to be written to the incoming file buffer. This ultimately leads to a write past the allocation memory region and depending on certain conditions leads to heap corruption.

The next vulnerability is in the circle rendering code. It is possible to specify a circle with a radius that causes an integer wrap-around when the radius is subtracted from the x and y coordinates of the circle. This wrap-around results in a large value for X or Y and ultimately leads to heap corruption or a page fault depending on the size and location of the wrap-around in the render buffer.

### Generic class of vulnerability

Out of bounds write
Signed to Unsigned Conversion Error
Integer Underflow (Wrap or Wraparound)

### CWE classification
CWE-119: Improper Restriction of Operations within the Bounds of a Memory Buffer
CWE-196: Unsigned to Signed Conversion Error
CWE-191: Integer Underflow (Wrap or Wraparound)

## Challenges

This CB incorporates two vulnerabilities to provide two varying levels of difficulty. The first vulnerability (the unsigned to signed conversion) is early in the input processing of the service making it easy to find for systems that start with input first symbolic execution. The next vulnerability is more difficult to discover and is buried within the rendering code for drawing circle objects. This vulnerability should prove difficult for CRS systems due to the sheer number of code paths leading up to the conditions necessary to exercise this vulnerability. Systems that perform depth first searches will most likely never arrive at this code path. Systems employing random search methods and a combination of depth first and breadth first searches should have better results.

The goal of this CB is to stress the memory subsystem of a CRS system. Image rendering can often times result in large amounts of memory being allocated and manipulated and this service is an example of that. In the service worse case memory consumption can be over 3MB of memory when rendering maximum size images of 512x512 and using all 6-layers available for rendering vector graphic objects.
