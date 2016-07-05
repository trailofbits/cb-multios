import struct
import sys
import random
import string
import time

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
			#print 'Padding %d bits' %(8-self.cbit)
			self.pdata += struct.pack('B', self.tvalue)
			self.cbit = 0
			self.tvalue = 0

		return

	def outStream( self ):
		return self.pdata

class cvf:
	def __init__( self, verbose=[]):
		self.height = 0;
		self.width = 0;
		self.data = ''
		self.verbose = verbose

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

		f = open('img.cvf', 'wb')
		f.write( struct.pack('I', len(self.data)))
		f.write(self.data)
		f.close()
		sys.exit()

	def genIncFrame( self ):
		tempFrame = struct.pack('H', 0x5555)
		frame_type = 1
		index_type = 0

		dict_type = random.randint( 0, 7 )

		### Ensure that there is at least one custom dict
		if dict_type == 0 and len(self.customUsed) == 0:
			dict_type = random.randint( 1, 7 )

		self.pv('Dictionary: %d' %dict_type, 4)

		### If a custom dictionary is selected then select which one
		if dict_type == 0:
			custom_dict = random.choice( self.customUsed )
			dictionary = self.pixelDicts[0][ custom_dict ][:]
			self.pv('Custom dict: %d' %custom_dict, 2)
		else:
			custom_dict = 0
			dictionary = self.pixelDicts[dict_type][:]

		### Write the flag
		flag = ( frame_type << 7 ) | ( index_type << 6 ) | (dict_type << 3) | ( custom_dict)
		self.pv('Flag: %d' %flag, 4)

		tempFrame += struct.pack('B', flag)

		### This is the maximum number of pixels that we
		###	can generate
		maxPixels = self.height * self.width
	
		self.pv( 'Max pixels: %d' %maxPixels, 4)

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

		self.pv( 'Pixel Count Bits: %d' %pixelCountEncodingBitCount, 4)
		self.pv( 'Pixel Count: %d Index Enc: %d Value Enc: %d' %(cntPixelsToGenerate, pixelIndexEncodingBitCount, pixelValueEncodingBitCount), 4)

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

			self.pv( 'Index: %d Value: %d %d' %(ic, pi, ord(iv)), 4)

			pixelIndexList.append( ic )
			pixelValueList.append( pi )

			### Update the image for later
			pixelImage[ ic ] = iv

		### The bitstream is needed for handling the appending
		### of individual bits.
		bs = bitstream()

		### Append the pixel count
		self.pv( 'Pixel Count %d with %d bits' %(cntPixelsToGenerate, pixelCountEncodingBitCount), 4)
		bs.appendBits( cntPixelsToGenerate, pixelCountEncodingBitCount)

		for x in range(cntPixelsToGenerate):
			self.pv( 'Pixel Index %d with %d bits' %(pixelIndexList[x], pixelIndexEncodingBitCount), 4)
			self.pv( 'Pixel Value %d with %d bits' %(pixelValueList[x], pixelValueEncodingBitCount), 4)
			bs.appendBits( pixelIndexList[x], pixelIndexEncodingBitCount)
			bs.appendBits( pixelValueList[x], pixelValueEncodingBitCount)	
		### No more additions so pad it out then append the stream
		bs.padItOut()

		tempFrame += bs.outStream()

		if len(self.data) + len(tempFrame) > 4096:
			ti = struct.unpack('>H', self.data[ self.frameCountOffset-2: self.frameCountOffset])[0]
			cl = list(self.data)
			self.pv( 'Dropping frames from %d to %d' %(ti, ti-1), 4)
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

		print img

		self.frames.append(''.join(pixelImage))

		return

	def genFullFrame( self ):	
		### A temp frame is needed in case it will pass size limits
		tempFrame = struct.pack('H', 0x5555)

		### Frame type is statically 0
		frame_type = 0

		self.pv( 'Frame type: %d' %frame_type, 2)

		### Index is not used with full frame
		index_type = 0

		self.pv( 'Index type: %d' %index_type, 2)

		### Select the dictionary to use 0 for custom
		dict_type = random.randint( 0, 7 )

		### Ensure that there is at least one custom dict
		if dict_type == 0 and len(self.customUsed) == 0:
			dict_type = random.randint( 1, 7 )

		self.pv('Dictionary: %d' %dict_type, 2)

		### If a custom dictionary is selected then select which one
		if dict_type == 0:
			custom_dict = random.choice( self.customUsed )
			dictionary = self.pixelDicts[0][ custom_dict ][:]
			self.pv('Custom dict: %d' %custom_dict, 2)
		else:
			custom_dict = 0
			dictionary = self.pixelDicts[dict_type][:]

		### Write the flag
		flag = ( frame_type << 7 ) | ( index_type << 6 ) | (dict_type << 3) | ( custom_dict)
		self.pv('Flag: %d' %flag, 2)

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
			self.pv('Index %d: Pixel Index: %d Pixel Value: %c %d' %(p, dictionary.index(q), q, ord(q)), 2)

		### Calculate the number of bits for each pixel
		pixel_bits_required = bitsNeeded( len(dictionary) - 1)

		### Initialize the bit counter and bit data
		bit_counter = 0
		bit_data = 0

		self.pv('Pixel encoding bits: %d' %pixel_bits_required, 2)

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
			#print 'Padding: %d' %(8-bit_counter)

		if len(self.data) + len(tempFrame) > 4096:
			ti = struct.unpack('>H', self.data[ self.frameCountOffset-2: self.frameCountOffset])[0]
			cl = list(self.data)
			self.pv( 'Dropping frames from %d to %d' %(ti, ti-1), 2)
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

		print img

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

	def pv( self, string, verbose ):
		if verbose in self.verbose:
			print string

		return
		
	def genHeader( self ):
		self.width = random.randint( 1, 128 )
		self.height = random.randint(1, 35 )
		self.frameCount = random.randint( 1, 30 )

		self.pv('Width: %d\nHeight: %d\nFrames: %d' %(self.width, self.height, self.frameCount), 3)

		self.pv('Image width: %d' %self.width, 1)
		self.pv('Image height: %d' %self.height, 1)

		self.pv('Frame count: %d' %self.frameCount, 1)

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

			self.pv( 'Custom pixel: %d' %dictInd, 1)
			self.pv( 'Pixel count: %d' %count, 1)

			for x in range(count):
				ch = random.choice( c )
				pixels.append( ch )
				self.pv( 'Index %d: %c %d' %(x, ch, ord(ch)), 1)
				c.remove(ch)

			self.customUsed.append( dictInd )
			self.customAvailable.remove(dictInd)

			self.data += struct.pack('>H', 0x4444 + dictInd )
			self.data += struct.pack('B', count)
			self.data += ''.join(pixels)

			self.pixelDicts[0][ dictInd] = pixels

		return

if __name__ == '__main__':
	f = open('/dev/urandom', 'rb')
	seed = f.read(4)
	f.close()

	seed = struct.unpack('I', seed)[0]

	f = open('seed.txt', 'wb')
	f.write(str(seed))
	f.close()

	random.seed(seed)

	verbose = []
	if len(sys.argv) >= 2:
		i = len(sys.argv)
		for x in range(1, i):
			verbose.append(int(sys.argv[x]))
			print verbose[-1]
	x = cvf(verbose)
