# CROMU_00036 - Vector Graphics 2

## Author Information

"Debbie Nuttall" <debbie@cromulence.co>

### DARPA performer group

Cromulence LLC (CROMU)

## Description

This service is another implementation of the vector graphics processor from CROMU_00018. An input file is received and parsed into a file data structure. Next it is rendered into an output buffer and written out to pixel map file in RGB 24-bit color format. This service supports drawing lines, circles, triangles, and rectangles. Two new shapes have been added to this implementation, square and spray. 

### Feature List

This service features the ability to render lines, triangles, circles, rectangles, squares, and spray in any color on multiple layers. The layers are combined into a final render layer. The input format for the service is a binary file known as a VGF (Vector Graphics Format) file that contains the information for rendering the objects to the pixel map file. Upon any error conditions the service terminates. Memory allocation is handled by heap allocations using malloc/free.


## Vulnerability

There are two vulnerabilities in this service. 

The first vulnerability in this service occurs in the spray shape. When a specially crafted spray object is rendered onto the canvas by the vector graphics processor it allows a memory write outside the bounds of the canvas. 

The second vulnerability in this service occurs when a canvas is created with zero layers. When the service attempts to output the image file it will reference memory that does not exist. 

### Generic class of vulnerability

Write outside the bounds of a memory buffer. 
Read outside the bounds of a memory buffer. 

### CWE classification

CWE-119: Improper Restriction of Operations within the Bounds of a Memory Buffer
CWE-805: Buffer Access with Incorrect Length Value

## Challenges

In order to leverage the spray shape, the VGF file must contain the 'magic' value of 0x59745974 as part of the spray input. This value is not demonstrated in the sample traffic available to the CRS, so static analysis of the binary is required to uncover its existence. Fuzzing of the available inputs is highly unlikely to uncover the correct inputs required to access the spray shape. Once the spray shape is identified, additional fuzzing of a valid spray input would yield proof of the vulnerability. 

The second vulnerability should be easier to reach. A valid input must be created with the layer field set to 0. 