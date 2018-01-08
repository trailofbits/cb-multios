'''
Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

'''

import struct
import sys
import random
import string
import time

''' This python script generates 1000 polls at a time. The first argument may be
    a seed but if one is not provided then it generates one from time(). All polls
    are written to poller/for-testing and from there can be partitioned out.
'''

def bitsNeeded ( cnt ):
	if cnt == 0:
		return 1

	z = 0

	while ( cnt ):
		z += 1
		cnt >>= 1

	return z

class bitstream:
	def __init__( self ):
		### pdata is the final output stream
		### It is written to when the bits reach 8
		self.pdata = ''

		### Current number of bits in the queue
		self.cbit = 0

		### Current value being appended to
		self.tvalue = 0

		return

	def appendBits( self, value, bitCount ):
		for bc in range(bitCount):
			nextBit = (value >> ( bitCount - (bc+1) ) ) & 1
			
			self.tvalue |= (nextBit << (7-self.cbit))
			self.cbit += 1
			
			### If we have filled up a byte then pack it up
			if self.cbit == 8:
				self.pdata += struct.pack('B', self.tvalue)
				self.cbit = 0
				self.tvalue = 0

		return bitCount

	def padItOut( self ):
		### If there are remaining bits pack them on
		if self.cbit != 0:
			self.pdata += struct.pack('B', self.tvalue)
			self.cbit = 0
			self.tvalue = 0

		return

	def outStream( self ):
		return self.pdata

class cvf:
	def __init__( self ):
		self.height = 0;
		self.width = 0;
		self.data = ''

		self.customAvailable = [ 0,1,2,3,4,5,6,7]
		self.customUsed = []

		### This is needed in case the size of the video
		###  will go beyond 4096
		self.frameCountOffset = 0

		self.pixelDicts = []
		## Append empty lists for custom dictionary place holders
		self.pixelDicts.append( [ [], [], [], [], [], [], [], [] ] )
		
		## Append standard dictionaries
		self.pixelDicts.append( [' ', '.'] )
		self.pixelDicts.append( [' ', '.', '|', '#'] )
		self.pixelDicts.append( [' ', '.', '|', '#', '@', '$', '(', ')']) 
		self.pixelDicts.append( [ ' ', '.', '|', '#', '@', '$', '(', ')', '*', 'H', 'O', 'E', 'W', 'M', '%', '&']) 
		self.pixelDicts.append( [ ' ', '.', '|', '#', '@', '$', '(', ')', '*', 'H', 'O', 'E', 'W', 'M', '%', '&', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u','v', 'w', 'x', 'y','z'] ) 
		self.pixelDicts.append( ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']) 
		self.pixelDicts.append( [ ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'] )

		self.frameCount = 0
		self.frames = []
		self.viewableFrames = []

		self.name = ''
		self.description = ''

		### Set magic
		self.data = "\x00CVF"

		### Generate the header
		self.genHeader()

		self.genDesc()

		self.genCustomPixelDict()

		for x in range(self.frameCount):
			self.genFrame()

	def genIncFrame( self ):
		tempFrame = struct.pack('H', 0x5555)
		frame_type = 1
		index_type = 0

		dict_type = random.randint( 0, 7 )

		### Ensure that there is at least one custom dict
		if dict_type == 0 and len(self.customUsed) == 0:
			dict_type = random.randint( 1, 7 )

		### If a custom dictionary is selected then select which one
		if dict_type == 0:
			custom_dict = random.choice( self.customUsed )
			dictionary = self.pixelDicts[0][ custom_dict ][:]
		else:
			custom_dict = 0
			dictionary = self.pixelDicts[dict_type][:]

		### Write the flag
		flag = ( frame_type << 7 ) | ( index_type << 6 ) | (dict_type << 3) | ( custom_dict)
		tempFrame += struct.pack('B', flag)

		### This is the maximum number of pixels that we
		###	can generate
		maxPixels = self.height * self.width
	

		genMax = maxPixels / 2

		if genMax <= 1:
			genMax = maxPixels
	
		### This is the number that we will actually generate
		cntPixelsToGenerate = random.randint( 1, genMax )

		### The count must be encoded in bits.
		### Since this is not 0 indexed we do not subtract 1
		pixelCountEncodingBitCount = bitsNeeded( maxPixels )

		### This is the size of each index field
		pixelIndexEncodingBitCount = bitsNeeded( maxPixels - 1)

		### The actual pixel value bit length needs to be calcd
		pixelValueEncodingBitCount = bitsNeeded( len(dictionary) - 1)


		### Get a copy of the previous image.
		pixelImage = list( self.frames[-1] )

		pixelIndexList = []
		pixelValueList = []

		### Generate the new pixel data
		for x in range(cntPixelsToGenerate):
			### Select image index
			ic = random.randint(0, maxPixels-1)

			### Select pixel value
			iv = random.choice( dictionary )

			### Pull out index of the pixel
			pi = dictionary.index( iv )


			pixelIndexList.append( ic )
			pixelValueList.append( pi )

			### Update the image for later
			pixelImage[ ic ] = iv

		### The bitstream is needed for handling the appending
		### of individual bits.
		bs = bitstream()

		### Append the pixel count
		bs.appendBits( cntPixelsToGenerate, pixelCountEncodingBitCount)

		for x in range(cntPixelsToGenerate):
			bs.appendBits( pixelIndexList[x], pixelIndexEncodingBitCount)
			bs.appendBits( pixelValueList[x], pixelValueEncodingBitCount)	
		### No more additions so pad it out then append the stream
		bs.padItOut()

		tempFrame += bs.outStream()

		if len(self.data) + len(tempFrame) > 4096:
			ti = struct.unpack('>H', self.data[ self.frameCountOffset-2: self.frameCountOffset])[0]
			cl = list(self.data)
			self.data = cl[:self.frameCountOffset-2]
			self.data += struct.pack('>H', ti-1)
			self.data += cl[self.frameCountOffset:]
			self.data = ''.join( self.data )
	
			return
		else:
			self.data += tempFrame

		### Fix the frame
		img = ''
		for x in range(len(pixelImage)):
			if x != 0 and x % self.width == 0:
				img += '\n'
			img += pixelImage[x]

		img += '\n'

		self.viewableFrames.append( img )
		self.frames.append(''.join(pixelImage))

		return

	def genFullFrame( self ):	
		### A temp frame is needed in case it will pass size limits
		tempFrame = struct.pack('H', 0x5555)

		### Frame type is statically 0
		frame_type = 0

		### Index is not used with full frame
		index_type = 0

		### Select the dictionary to use 0 for custom
		dict_type = random.randint( 0, 7 )

		### Ensure that there is at least one custom dict
		if dict_type == 0 and len(self.customUsed) == 0:
			dict_type = random.randint( 1, 7 )

		### If a custom dictionary is selected then select which one
		if dict_type == 0:
			custom_dict = random.choice( self.customUsed )
			dictionary = self.pixelDicts[0][ custom_dict ][:]
		else:
			custom_dict = 0
			dictionary = self.pixelDicts[dict_type][:]

		### Write the flag
		flag = ( frame_type << 7 ) | ( index_type << 6 ) | (dict_type << 3) | ( custom_dict)

		tempFrame += struct.pack('B', flag)

		### Randomly select a pixel and generate both
		###	the pixel image and the index array
		pixel_image = []
		index_array = []

		length = self.height * self.width

		for p in range(length):
			q = random.choice( dictionary )
			pixel_image.append( q )
			index_array.append( dictionary.index( q ) )

		### Calculate the number of bits for each pixel
		pixel_bits_required = bitsNeeded( len(dictionary) - 1)

		### Initialize the bit counter and bit data
		bit_counter = 0
		bit_data = 0


		### Loop through each index and write the data
		for i in range( len(index_array) ):
			for j in range(pixel_bits_required):
				cb = (index_array[i] >> ( (pixel_bits_required-1)-j)) & 1
				bit_data |= ( cb << ( 7-bit_counter) )
				bit_counter += 1

				if bit_counter == 8:
					tempFrame += struct.pack('B', bit_data)
					bit_counter = 0
					bit_data = 0

		### Add in any extra padding
		if bit_counter != 0:
			tempFrame += struct.pack('B', bit_data)

		if len(self.data) + len(tempFrame) > 4096:
			ti = struct.unpack('>H', self.data[ self.frameCountOffset-2: self.frameCountOffset])[0]
			cl = list(self.data)
			self.data = cl[:self.frameCountOffset-2]
			self.data += struct.pack('>H', ti-1)
			self.data += cl[self.frameCountOffset:]
			self.data = ''.join( self.data )
			
			return
		else:
			self.data += tempFrame

		img = ''
		for x in range(len(pixel_image)):
			if x != 0 and x % self.width == 0:
				img += '\n'
			img += pixel_image[x]

		img += '\n'

		self.viewableFrames.append( img )
		self.frames.append( ''.join( pixel_image ))
		return

	def genFrame(self):
		### First frame must be a full frame
		if len(self.frames) == 0:
			frame_type = 0
		else:
			frame_type = (random.randint(0, 100)) & 1


		### If frame type is full then generate all the pixels
		if frame_type == 0:
			self.genFullFrame()
		else:
			self.genIncFrame()
		return

	def genDesc( self ):
		length = random.randint(10,255)
		self.data += struct.pack('H', 0x3333)
		self.data += struct.pack('B', length)

		n = ''

		for i in range(length):
			n += random.choice( string.lowercase + string.uppercase + string.digits + ' \t\n')

		self.data += n
		self.description = n

		return

	def genName(self):
		length = random.randint(10,255)
		self.data = struct.pack('H', 0x2222)
		self.data += struct.pack('B', length)

		n = ''

		for i in range(length):
			n += random.choice( string.lowercase + string.uppercase + string.digits)
	
		self.data += n
		self.name = n

		return

	def genHeader( self ):
		self.width = random.randint( 1, 128 )
		self.height = random.randint(1, 35 )
		self.frameCount = random.randint( 1, 30 )

		self.data += struct.pack('H', 0x1111)
		self.data += struct.pack('B', self.height)
		self.data += struct.pack('B', self.width)
		self.data += struct.pack('>H', self.frameCount)

		### Save this in case it must be modified
		self.frameCountOffset = len(self.data)

		return

	def genCustomPixelDict( self ):
		### number of dicts to generate

		toGen = random.randint( 0, 7)

		for i in range(toGen):
			c = string.lowercase + string.uppercase + string.digits
			c = list(c)

			## This will be the number of available characters
			count = random.randint(10,len(c))

			pixels = []

			### Randomly select the pixel dictionary index
			dictInd = random.choice( self.customAvailable )

			for x in range(count):
				ch = random.choice( c )
				pixels.append( ch )
				c.remove(ch)

			self.customUsed.append( dictInd )
			self.customAvailable.remove(dictInd)

			self.data += struct.pack('>H', 0x4444 + dictInd )
			self.data += struct.pack('B', count)
			self.data += ''.join(pixels)

			self.pixelDicts[0][ dictInd] = pixels

		return

if __name__ == '__main__':

	seed = int(time.time())

	if len(sys.argv) >= 2:
		try:
			seed = int(sys.argv[1])
		except:
			print '[ERROR] Converting seed to int failed'
			sys.exit(0)

	
	random.seed( seed )

	for p in range(1000):
		x = cvf()

		pollxml = '<?xml version="1.0" standalone="no" ?>\n'
		pollxml += '<!DOCTYPE pov SYSTEM "/usr/share/cgc-replay/replay.dtd">\n'
		pollxml += '<pov>\n'
		pollxml += '\t<cbid>CROMU_00032</cbid>\n'
		pollxml += '\t<replay>\n'
		pollxml += '\t\t<read echo="ascii"><delim>----------------Stream Me Your Video----------------\\n</delim><match><data>----------------Stream Me Your Video----------------\\n</data></match></read>\n'

		pollxml += '\t\t<write echo = "ascii"><data>'

		sz = struct.pack('I', len(x.data))

		for z in sz:
			pollxml += '\\x%.2x' %ord(z)

		pollxml += '</data></write>\n'

		pollxml += '\t\t<write echo = "ascii"><data>'
		for z in x.data:
			pollxml += '\\x%.2x' %ord(z)

		pollxml += '</data></write>\n'

		pollxml += '\t\t<read echo="ascii"><delim>--------------------Playing video-------------------\\n</delim><match><data>--------------------Playing video-------------------\\n</data></match></read>\n'

		pollxml += '\t\t<read echo="ascii"><delim>\\n</delim><match><data>INFO: Height: %d Width: %d Frames: %d\\n</data></match></read>\n' %(x.height, x.width, len(x.frames))	

		pollxml += '\t\t<read echo="ascii"><delim>\\n</delim><match><data>INFO: Set your terminal height so that only the \'|\'s show.\\n</data></match></read>\n'

		pollxml += '\t\t<read echo="ascii"><delim>\\n</delim><match><data>INFO: This will provide a better viewing experience\\n</data></match></read>\n'

		pollxml += '\t\t<read echo="ascii"><delim>\\n</delim><match><data>INFO: When ready press a key...\\n</data></match></read>\n'

		pollxml += '\t\t<write echo="ascii"><data>%c</data></write>\n' %(random.choice(string.lowercase))

		for i in range(x.height):
			pollxml += '\t\t<read echo="ascii"><delim>\\n</delim><match><data>|</data></match></read>\n'

		for i in x.viewableFrames:
			dataString = ''
			for j in i:
				dataString += '\\x%.2x' %(ord(j))

			pollxml += '\t\t<read echo = "ascii"><delim>%s</delim><match><data>%s</data></match></read>\n' %(dataString, dataString)

		pollxml += '\t</replay>\n'
		pollxml += '</pov>\n'

		nm = "poller/for-testing/POLL%.5d.xml" %p

		f = open(nm, 'wb')
		f.write(pollxml)
		f.close()

		### Uncomment this to write the actual image
		#f = open('images/img%.5d.cvf' %(p), 'wb')
		#f.write(struct.pack('I', len(x.data)))
		#f.write(x.data)
		#f.close()
