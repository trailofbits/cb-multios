# CGC Video Format Parser and Viewer

## Author Information

"John Berry" <john.n.berry@gmail.com>

### DARPA performer group
Cromulence

## Description

A user can stream a video to the CB which will then be parsed and the frames will be presented back to the user in a video format.

### Feature List

Cromulence Video Format (CVF)
Magic: These MUST be the first 4 bytes of every CVF file
	0x00, 'C', 'V', 'F

Header: The header contains the height, width, and frame count information. It is usually first but can be in any order as long as it is before the start of Frame data. This section is indicated by the two byte 0x1111 sequence.
	8 bits - Height. The unsigned integer has an actual allowed maximum of 35. Values above this will be considered invalid.
	8 bits - Width. The unsigned integer has an actual allowed maximum of 128. Values above this will be considered invalid.
	16 bits - Frame Count. The number of frames present in the video. Maximum frame count is 2048

Name: This section contains the name of the video. This is an optional section but if it exists then the value will be displayed above the playing video. It has a maximum length of 256 bytes including the length field. It is indicated by the two byte 0x2222 sequence.
	8 bits - Length. Length in characters of the name field.

Description: Contains a description of the video. This is optional but is used to describe the video content. It has a maximum length of 256 bytes including the length field. It is indicated by the two byte sequence 0x3333. It is limitted to upper case, lower case,  digits or whitespace.

Custom Pixel Dictionary: These custom dictionaries are used to minimize data size by only selecting those values that are necessary to display a given frame. It is possible to have 8 different custom dictionaries labeled 0-7. They are indicated by the sequences 0x4444-0x444b. They can be a maximum of 256 bytes.
	8 bits - Length.
	Length Bytes - This array is the index used for the custom pixel dictionary. For example, a dictionary of [ '0', '1', '2', '4'] Will have a length of 4 and the values can be access via their 0 based index into the array.

Frame Data: Array of frames used to display the image. The first frame is always a full frame. The start of frame data is indicated by the two byte sequence 0x5555.

Frame:
Flag 8 bits
	bit 7 - Full frame or individual pixels
		0 - Full frame redraws the entire frame. This requires that a frame have height*width pixels.
		1 - Incremental pixels takes the previous frame and applies the changes to it.
	bit 6 - 0 based index or x, y coords
		0 - If 0 based then the index is between 0 and height * width. If it is a full frame then this is irrelavant
		1 - If x, y then the origin is the bottom left to ensure only positive coordinates
	bits 5-3
		Pixel dictionary
		0 - Custom
			If custom is chosen then bits 2-0 are used as a selection for which custom dictionary.
			A video can have up to 8 custom dictionaries.
		1 - ' ', '.'
		2 - 1 + '|', '#'
		3 - 2 + '@', '$', '(', ')'
		4 - 3 + '*', 'H', 'O', 'E', 'W', 'M', '%', '&'
		5 - 4 + 'a-z'
		6 - 'a-zA-Z0-9'
		7 - All ascii 0x20-0x7e

	If the frame type is incremental then log2(height*width) bits for pixel count
	Variable Bits - Pixel Count
	If it is zero index the bit length of the location is the log2(height*width) rounded up to the nearest integer.
	If it is x,y then the x length is log2(x) and y is log2(y)

	For example a height of 28 and 40 would result in 28*40=1120 which means 11 bits for each with type 0, type 1 with x,y would be 4 bits for x, 5 bits for y with a total of 9. Following this is the pixel dictionary. This length is also dependent upon the type. Custom depends upon the number of characters, 1 is 1 bit, 2 is 2 bits, 3 is 3 bits, 4 is 4 bits, 5 is 6 bits, 6 is 6 bits and 7 is 7 bits.


## Vulnerability
The user must specify in the video header how many frames are present. The application then allocates a buffer large enough to hold the specified number of frame pointers but proceeds to parse and store as many frames as the video contains.


### Generic class of vulnerability
Heap based buffer overflow due to invalid verification of an input size.

### CWE classification

CWE-120 Buffer copy without checking size of input

## Challenges
There is a significant amount of processing on variable length bit fields. They must determine the format of video frame data and how to construct a valid video. Bitwise dataflow will be required.

