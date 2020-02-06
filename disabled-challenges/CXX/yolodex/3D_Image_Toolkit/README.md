# 3D_Image_Toolkit

## Author Information

"Dan Czarnecki" <cgc@cromulence.com>

### DARPA performer group

Cromulence (CROMU)

## Description

This service implements a toolkit for a custom 3D image format.  The format consists of a sequence of bytes that make up the X, Y, Z coordinates and the Red (R), Green (G), Blue (B), and Alpha (A) color values for each pixel in the image.

There are commands available to the user that alter the 3DC image data within the service that allow the image to be manipulated in a multitude of ways.

### Feature List

The user can access the following commands:

 - Create a new file from user-provided data
 - View the data for every pixel in the image at once
 - View the data for a single user-selected pixel
 - Skew the X, Y, or Z coordinates of the pixels by a user-provided value
 - Rotate the entire image about the X, Y, or Z axis by a user-provided degree value
 - Scale the entire image by a user-provided value
 - Alter the brightness of the image by a user-provided value
 - Change the opacity of the image by a user-provided value
 - Compress the image by turning the RGB color values for each pixel into an 8-bit representation
 - Decompress the compressed image data back into the active image data, not without losing color data due to the compression
 - Exit the toolkit

## Vulnerability

The user has an option to compress and decompress the image data, as well as show individual pixels.  If the user provides a pixel index that is out of range, they are told that it was out of range, and they are presented the data for the last pixel that was printed.  When the compress command is selected, the compressed data is written to a variable on the main stack that is the valid size of the image data when it is compressed.  However, when the decompress command is selected, the same variable is used for the decompressed data copy.  The size of the decompressed data is obviously larger, and therefore this writes data outside of the boundary and into other variables on the stack, one of which is the pointer to the last shown pixel.

With this, the user can provide new image data that contains the address of the region of memory with magic page data, compress the image, decompress it, and then run the command to show an individual pixel's data.  The pixel index must be out of the range, so that it pulls from the pointer to the last shown pixel, which now holds a pointer to the magic page data (if the new image data was properly crafted).  This results in pixel image data in decimal X, Y, and Z coordinates, as well as hexadecimal RGBA values.  

### Generic class of vulnerability

Out of bounds read

### CWE classification

CWE-125: Out-of-bounds read

## Challenges
The first challenge for the CRS is to understand the toolkit menu interface and craft proper data to send to the CB in order to properly initiate commands to alter the image data.

For this vulnerability, the CRS must understand how to create a new image file, submit the correct length of data to the CB, and find the bug which allows for manipulation of the newly crafted image data in a certain sequence that can lead to leaking data from the magic page.  

The Subjective Quantifications for this vulnerability are:

Discovering - Medium
Proving - Easy
Fixing - Easy
