# CGC Image Parser

## Author Information

"John Berry" <hj@cromulence.co>

### DARPA performer group
Cromulence

## Description
The user has the ability to upload images formatted in one of five custom formats. They can also list, remove, or display the rendered images.
The purpose was to challenge them with non-eight bit aligned bitwise manipulation as well as management of user derived and user influenced data.

### Feature List
Tag Based Image Renderer (TBIR)

Header
32 bit magic 0xb0c4df76

16 bit header start: 0xaaaa
8 bit width with a max of 128
8 bit height with a max of 128

16 bit flag field: 0xaabb
4 bits pixel type:
	0001 - 1 bit for a ' ' or a '.'
	0010 - 2 bits for a ' ', '#', '*', '@'
	0110 - 6 bits for a ' a-zA-Z0-9'
	0111 - 7 bits for ascii 0x20-0x7e 0 indexed
4 bits load direction
	0000 Start top row left to right then continue down
	0001 Start top row right to left then continue down
	0010 Start bottom row left to right then continue up
	0011 Start bottom row right to left then continue up
	0100 Start left column top down then continue right
	0101 Start right column top down then continue left
	0110 Start left column bottom up then continue right
	0111 Start right column bottom up then continue left

16 bit pixel start field: 0xaacc
	width * height * ([1|2|6|7]) 
	aligned to 32 bit

16 bit checksum field: 0xaadd
	32 bit xor checksum

16 bit end of file: 0xaaee
************************************************************************

Total Pixel AsciiBased Image (TPAI)
Each pixel must have a value. The ordering is specified via flags

Image Header
32 bit magic 0xcb590f31
6 bit Width
6 bit Height
3 bit pixel load direction
	000 Start top row left to right then continue down
	001 Start top row right to left then continue down
	010 Start bottom row left to right then continue up
	011 Start bottom row right to left then continue up
	100 Start left column top down then continue right
	101 Start right column top down then continue left
	110 Start left column bottom up then continue right
	111 Start right column bottom up then continue left
17 bit Reserved

Width * Height Pixels
7 bit Ascii value

The pixel array must be 16 bit aligned.

16 bit xor checksum of all data including the header.

************************************************************************
Fixed Point AsciiBased Image (FPAI)
Each pixel is relative to the 0,0 (origin) point
Each pixel can be any ascii value

Image Header
32 bit MAGIC 0x55d9b6de
6 bit X axis
6 bit Y axis
3 bit axis type (origin location)
16 bit pixel checksum (Checksum by adding all the 16-bit values)
	Checksum only covers the pixel data

1 bit reserved.
	Should be 0

Pixel:
7 bit X value
7 bit Y value
7 bit Pixel Value ' ' - '~' 0 based 

Image is padded to 8 bits

************************************************************************
Fixed Point TextBased Image (FPTI)
Each pixel is relative to the 0,0 point as opposed to the previous pixel with RPTI
Each pixel will be represented by a '.','*','#', or '+' based upon the header flag

Image Header
32 bit MAGIC 0x24c7ee85
6 bits X axis total length (unsigned)
	0 is an error condition
	Max of 63
6 bits Y axis total length (unsigned)
	0 is an error condition
	Max of 63
2 bit pixel type
	00 - '.'
	01 - '*'
	10 - '#'
	11 - '+'
3 bit axis type (origin location)
	001 - 0,0 upper left
	010 - 0,0 upper right
	011 - 0,0 lower left
	100 - 0,0 lower right
	111 - 0,0 at midpoint rounded down
15 bits reserved
	Should be 0

The first bit is a sign bit
7 bits X axis relative to the origin
7 bits Y axis relative to the origin

************************************************************************
Relative Point TextBased Image ( RPTI )

32 bit MAGIC 0xc35109d3
6 bits X axis total length
6 bits Y axis total length

The first bit of the initial position is the sign bit
7 bits X axis initial position
7 bits Y axis initial position

3 bit Axis type:
001 - 0,0 upper left
010 - 0,0 upper right
011 - 0,0 lower left
100 - 0,0 lower right
111 - 0,0 at midpoint rounded down

3 bit reserved. Should be 0

For example:
X total of 51
Y total of 51
Midpoint would be at 25, 25.

The initial position is based upon the 0,0 point whose location is set in the grid by the axis type flag

Each "Pixel"
The first bit is a sign bit
7 bits X axis relative to previous point
7 bits Y axis relative to previous point

Each Image is zero padded out to a byte
Attempt to place a pixel beyond the bound results in a failure condition
Each pixel is based upon the relative point of the previous pixel
************************************************************************

## Vulnerability
The first vulnerability is in the FPTI image type. The mistake is a common one due to either a mistyping of misunderstanding of C truth statements.
The line is:
if ( y < miny && y > maxy ) {
	error
}
Obviously this statement can never be true but it is an easy one to make. This results in an invalid bounds check of the y value and a SIGSEGV when
the user attempts to write before an allocated buffer.

The second bug is in the TBIR image type. It is a failure to clear certain values after a parsing error and buffer deallocation. This ultimately results in a use after free situation.

Due to the way the parsing works, the pixel needs to be the last in an image and end on a 32-bit boundary due to a check just following the code.

### Generic class of vulnerability
The first vulnerability is an out of bounds write due to an invalid bounds check
The second class of vulnerability is a use after free.

### CWE classification
The first is CWE-129: Improper Validation of Array Index. The product uses untrusted input when calculating or using an array index, but the product does not validate or incorrectly validates the index to ensure the index references a valid position within the array. Also known as out-of-bounds array index.

The second is CWE-416: Use after free. Referencing memory after it has been freed.

## Challenges

These formats require the ability to track bitwise dataflow. It also requires that competitors track user derived and user influenced data.

They must also carefully track memory allocations and frees to catch their use if freed.
