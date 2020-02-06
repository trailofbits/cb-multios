from generator.actions import Actions
import string
import random
import numpy as np
import binascii
import struct

def rs( length ):
	return ''.join( random.choice( string.lowercase + string.uppercase + string.digits) for _ in range(length) )

class CROMU_PRNG():
	def __init__(self):
		self.state = np.zeros( 32, dtype=np.uint32 )
		self.state_n = np.uint32
	
		self.R = 32
		self.M1 = 3
		self.M2 = 24
		self.M3 = 10

		self.state_n = 0

	def seed_by_array( self, array_data, array_len ):
		if ( array_len > 32 ):
			array_len = 32

		i = 0
		while i < array_len:
			self.state[i] = array_data[i]
			i += 1

		while i < self.R:
			state_value = self.state[(i-1)&0x1F]

			self.state[i] = (state_value ^ (state_value >> 30) + i) * 524287
			i += 1

	def prng( self ):
		v0 = self.state[ self.state_n ]
		vM1 = self.state[ (self.state_n + self.M1) & 0x1F ]
		vM2 = self.state[ (self.state_n + self.M2) & 0x1F ]
		vM3 = self.state[ (self.state_n + self.M3) & 0x1F ]

		z0 = self.state[ (self.state_n + 31) & 0x1F ]
		z1 = v0 ^ (vM1 ^ ((vM1 >> 8) & 0xFFFFFFFF))
		z2 = (vM2 ^ ((vM2 << 19) & 0xFFFFFFFF)) ^ (vM3 ^ ((vM3 << 14) & 0xFFFFFFFF))

		newV1 = z1 ^ z2
		newV0 = (z0 ^ ((z0 << 11) & 0xFFFFFFFF)) ^ (z1 ^ ((z1 << 7) & 0xFFFFFFFF)) ^ (z2 ^ ((z2 << 13) & 0xFFFFFFFF))

		self.state[ self.state_n ] = newV1
		self.state[ (self.state_n + 31) & 0x1F ] = newV0

		self.state_n = (self.state_n + 31) & 0x1F

		return newV0

class CROMU_GENWORK():
	def __init__(self, magic_page):
		self.prng = CROMU_PRNG()
		self.magic_page = magic_page
		self.MAGIC_PAGE_DWORD_SIZE = len(self.magic_page)

		self.prng.seed_by_array( magic_page, 32 )

		self.magic_matrix = None

 	def PrintPRNG( self, x ):
		x.read( delim='\n', expect=("PRNG is: %X %X %X %X, blah=%X %X %X %X\n" % (self.prng.prng(), self.prng.prng(), self.prng.prng(), self.prng.prng(), self.magic_page[0], self.magic_page[1], self.magic_page[2], self.magic_page[3])) )

		self.GenNewMatrix()
		x.read( delim='\n', expect=("X=%X %X %X %X\n" % (self.magic_matrix[0], self.magic_matrix[1], self.magic_matrix[2], self.magic_matrix[3])) )

	def GenNewMatrix( self ):
		if ( self.magic_matrix is None ):
			pos = 0
			self.magic_matrix = np.zeros( self.MAGIC_PAGE_DWORD_SIZE, dtype=np.uint32 )

			while pos < self.MAGIC_PAGE_DWORD_SIZE:
				self.magic_matrix[pos] = self.prng.prng() ^ (self.magic_page[pos] & 0xC370E5A1)	
				pos += 1

		else:
			pos = 0

			while pos < self.MAGIC_PAGE_DWORD_SIZE:
				self.magic_matrix[pos] = self.magic_matrix[pos] ^ self.prng.prng() ^ (self.magic_page[pos] & 0xC370E5A1)
				pos += 1

	def GetRandom8BitNumber( self ):
		return self.magic_matrix[ self.prng.prng() % self.MAGIC_PAGE_DWORD_SIZE ] & 0xFF

	def GetTime( self ):
		self.GenNewMatrix()

		time = 1420070400

		time += (self.GetRandom8BitNumber() << 16 | self.GetRandom8BitNumber() << 8 | self.GetRandom8BitNumber())

		return time

	def GetBookingNumber( self ):
		char_list = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789"

		booking_number = ''

		self.GenNewMatrix()
		pos = 0
		while pos < 8:
			booking_number += char_list[ (self.GetRandom8BitNumber() & 0x1F) ]
			pos += 1

		return booking_number

class DMAWorker():
	DMA_WORKER_NONE = 0
	DMA_WORKER_READ = 1
	DMA_WORKER_WRITE = 2

	def __init__( self, worker_type, device_id, address, length ):
		self.device_id = device_id
		self.address = address
		self.length = length
		self.position = 0
		self.worker_type = worker_type

	def ClearWorker( self ):
		self.worker_type = self.DMA_WORKER_NONE

	def AdvancePosition( self, advance_amount ):
		self.position += advance_amount

	def IsWorkerAvailable( self ):
		if ( self.worker_type == self.DMA_WORKER_NONE ):
			return False
		else:
			return True

class DMAEngine():
	def __init__( self, mmu, write_func, read_func ):
		self.mmu = mmu
		self.worker_count = 0
		self.worker_last = 0
		self.write_func = write_func
		self.read_func = read_func
		
		self.workers = list()
		i = 0
		while i < 5:
			self.workers.append( DMAWorker( DMAWorker.DMA_WORKER_NONE, 0, 0, 0 ) )

			i += 1

	def InitReadWorker( self, device_id, address, length ):
		worker_cur = self.worker_count
		self.worker_count += 1

		if ( worker_cur >= 5 ):
			if ( device_id == 1 or device_id == 2 ):
				print "===== CRITICAL ERROR: Too many DMA workers... this could trigger the bug ===="
			return

		self.workers[worker_cur].worker_type = DMAWorker.DMA_WORKER_READ
		self.workers[worker_cur].device_id = device_id
		self.workers[worker_cur].address = address
		self.workers[worker_cur].length = length
	
	def InitWriteWorker( self, device_id, address, length ):
		worker_cur = self.worker_count
		self.worker_count += 1

		if ( worker_cur >= 5 ):
			print "===== CRITICAL ERROR: Too many DMA workers... this could trigger the bug ===="
			return

		self.workers[worker_cur].worker_type = DMAWorker.DMA_WORKER_WRITE
		self.workers[worker_cur].device_id = device_id
		self.workers[worker_cur].address = address
		self.workers[worker_cur].length = length
		
	def ServiceDMA( self ):
		
		i = 0
		while i < self.worker_count:
			if ( i >= 4 ):
				break

			worker_cur = self.worker_last
			worker_available = False

			try_count = 0
			while try_count < 5:
				if ( worker_cur >= 5 ):
					worker_cur = 0

				if ( self.workers[worker_cur].IsWorkerAvailable() ):
					worker_available = True
					break

				worker_cur += 1
				try_count += 1

			if ( worker_available ):
				device_id = self.workers[worker_cur].device_id
				action_type = self.workers[worker_cur].worker_type
				position = self.workers[worker_cur].position
				address = self.workers[worker_cur].address
				length = self.workers[worker_cur].length

				dmaAmount = (length - position)
				if ( dmaAmount > 4 ):
					dmaAmount = 4

				if ( dmaAmount == 0 ):
					# End worker
					self.worker_count -= 1

					self.workers[worker_cur].ClearWorker()
				
				elif ( device_id == 1 ):	# Send DMA peripheral
					if ( action_type == DMAWorker.DMA_WORKER_WRITE ):
						#print "**** SEND DMA WRITE **** **** ****!!!!"

						read_data, exception = self.mmu.ReadDMA( address+position, dmaAmount )

						if ( exception == True ):
							if ( dmaAmount != len(read_data) ):
								print "****!!!!ERROR!!!!!**** dmaAmount and length did not match!"

							self.read_func( expect=read_data, length=dmaAmount )
			
					if ( position+dmaAmount >= length ):
						self.worker_count -= 1

						self.workers[worker_cur].ClearWorker()
					else:
						# Advance position
						self.workers[worker_cur].AdvancePosition( dmaAmount )

				elif ( device_id == 2 ): # Read DMA peripheral
					if ( action_type == DMAWorker.DMA_WORKER_READ ):
						#print "**** READ DMA READ **** **** ****!!!!"
						read_data, exception = self.mmu.ReadDMA( address+position, dmaAmount )
						write_data = ''
						for i in range(dmaAmount):
							write_data += struct.pack( 'B', random.randint( 0, 255 ) )

						self.write_func( write_data )

						self.mmu.WriteDMA( address+position, write_data )

					if ( position+dmaAmount >= length ):
						self.worker_count -= 1

						self.workers[worker_cur].ClearWorker()
					else:
						# Advance position
						self.workers[worker_cur].AdvancePosition( dmaAmount )
				else:
					# Device does not exist -- exit
					self.worker_count -= 1

					self.workers[worker_cur].ClearWorker()
					
				# Advance worker_cur and last worker
				worker_last = worker_cur
				worker_cur += 1
			else:
				worker_last = 0
				break

			i += 1

class MMUSection():
	def __init__( self, prot_flags, address, data ):
		self.prot_flags = prot_flags
		self.address = address
		self.data = data

	def SetData( self, offset, data ):
		if ( len(data)+offset > 512 ):
			new_data = self.data[0:offset] + data[0:512-offset]
		else:
			new_data = self.data[0:offset] + data + self.data[offset+len(data):]
		
		self.data = new_data

	def SetProtFlags( self, prot_flags ):
		self.prot_flags |= prot_flags

class MMU():
	MMU_PROT_READ = 1
	MMU_PROT_WRITE = 2
	MMU_PROT_EXEC = 4


	def __init__( self ):
		i = 0
		zero_data = struct.pack( 'B', 0 ) * 512

		self.mmu_sections = list()
		while i < 128:
			self.mmu_sections.append( MMUSection( 0, i*512, zero_data ) )

			i += 1
		#return ''

	def AddSection( self, prot_flags, address, data ):
		#print "Adding section (%X, %X, %X)\n" % (prot_flags, address, len(data)	)
		
		copy_remaining = len(data)
		copy_from_pos = 0

		while copy_remaining > 0:
			page_idx = int((address+copy_from_pos) / 512)
			page_offset = (address+copy_from_pos) % 512
			copy_amount = copy_remaining

			if ( copy_amount > (512 - page_offset) ):
				copy_amount = (512 - page_offset)

			#print "Allocated section (%X, %X, %X, %X)\n" % ((address+copy_from_pos), page_idx, page_offset, copy_amount )
			self.mmu_sections[page_idx].SetData( page_offset, data[copy_from_pos:copy_from_pos+copy_amount] )
			self.mmu_sections[page_idx].SetProtFlags( prot_flags )

			copy_remaining -= copy_amount
			copy_from_pos += copy_amount

	def Fetch16( self, address ):
		address &= 0xFFFE

		page_idx = int(address / 512)
		page_offset = address % 512

		#print "Fetching instr at %X\n" % address

		if ( (self.mmu_sections[page_idx].prot_flags & self.MMU_PROT_EXEC) == 0 ):
			return (0, False)

		return (struct.unpack( 'H', self.mmu_sections[page_idx].data[page_offset:page_offset+2] )[0], True )

	def Read16( self, address ):
		address &= 0xFFFE

		page_idx = int(address / 512)
		page_offset = address % 512

		if ( (self.mmu_sections[page_idx].prot_flags & self.MMU_PROT_READ) == 0 ):
			return (0, False)

		return (struct.unpack( 'H', self.mmu_sections[page_idx].data[page_offset:page_offset+2] )[0], True )

	def Write16( self, address, value ):
		address &= 0xFFFE

		page_idx = int(address / 512)
		page_offset = address % 512

		if ( (self.mmu_sections[page_idx].prot_flags & self.MMU_PROT_WRITE) == 0 ):
			return (False )

		self.mmu_sections[page_idx].SetData( page_offset, struct.pack( 'H', value ) )
		return True

	def ReadDMA( self, address, amount ):
		offset = 0

		read_data = ''
		while amount > 0:
			page_idx = int((address+offset) / 512)
			page_offset = (address+offset) % 512

			if ( (self.mmu_sections[page_idx].prot_flags & self.MMU_PROT_READ) == 0 ):
				return (0, False)

			amountToRead = amount
			if ( (page_offset+amountToRead) > 512 ):
				amountToRead = (512 - (page_offset+amountToRead))

			read_data += self.mmu_sections[page_idx].data[page_offset:page_offset+amountToRead]

			amount -= amountToRead
			offset += amountToRead

		return (read_data, True)

	def WriteDMA( self, address, data ):
		offset = 0

		amount = len(data)
		while amount > 0:	
			page_idx = int((address+offset) / 512)
			page_offset = (address+offset) % 512

			if ( (self.mmu_sections[page_idx].prot_flags & self.MMU_PROT_WRITE) == 0 ):
				return (False )

			amountToWrite = amount
			if ( (page_offset+amountToWrite) > 512 ):
				amountToWrite = (512 - (page_offset+amountToWrite))

			self.mmu_sections[page_idx].SetData( page_offset, data[offset:offset+amountToWrite] )

			amount -= amountToWrite
			offset += amountToWrite
			
		return True


class CROMU00066(Actions):
		
	def LoadSection( self, section_type, section_data, section_address ):
			
		if ( section_type == self.SECTION_TYPE_EXECUTE ):
			self.mmu.AddSection( MMU.MMU_PROT_READ | MMU.MMU_PROT_EXEC, section_address, section_data )	
		elif ( section_type == self.SECTION_TYPE_DATA ):
			self.mmu.AddSection( MMU.MMU_PROT_READ | MMU.MMU_PROT_WRITE, section_address, section_data )
		
		return

	def start(self):
		self.delay(50)
		np.seterr(all='ignore')
		self.instruction_list = [ "LoadImmediateHI", "LoadImmediateLO", "AddReg", "SubReg", "MulReg", "DivReg", "AddImm", "SubImm",
					  "MulImm", "DivImm", "MovReg", "SwapReg", "JumpOffsetZero", "JumpOffsetNotZero", "JumpLTReg",
					  "JumpGTReg", "JumpReg", "JumpOffset", "JumpRegZero", "JumpRegNotZero", "DMAInit", "DMARead",
					  "DMAWrite", "GetInstrCount", "GetRand", "GetSeedMaterial", "InvalidOpcode", "LoadRegister", "StoreRegister" ]

		self.SECTION_TYPE_EXECUTE = 0
		self.SECTION_TYPE_DATA = 1
		self.SECTION_TYPE_COMMENT = 2

		self.prng = CROMU_PRNG()
		self.prng.seed_by_array( np.fromstring( self.magic_page, dtype=np.uint32 ), 32 )

	def GenerateExecuteSection( self, section_len ):
		instr_count = section_len / 2

		next_invalid_opcode = False

		section_data = ''
		i = 0
		while i < instr_count:
			good_instr = False
			dma_count = 0
			while good_instr == False:
				instr_name = random.choice( self.instruction_list )

				if ( instr_name == "DMARead" ):
					dma_count += 1
				elif ( instr_name == "DMAWrite" ):
					dma_count += 1

				if ( dma_count > 3 and (instr_name == "DMARead" or instr_name == "DMAWrite" ) ):
					good_instr = False
				else:
					good_instr = True

			if ( next_invalid_opcode == True ):
				instr_name = "InvalidOpcode"
				next_invalid_opcode = False

			if instr_name == "LoadImmediateHI":
				instr_data = 0x0 | random.randint( 0, 15 ) << 8 | random.randint( 0, 0xFF )
			elif instr_name == "LoadImmediateLO":
				instr_data = (0x1 << 12) | (random.randint( 0, 15 ) << 8) | random.randint( 0, 0xFF )
			elif instr_name == "AddReg":
				instr_data = (0x2 << 12) | (random.randint( 0, 15 ) << 8) | (random.randint( 0, 15 ) << 4) | random.randint( 0, 15 )
			elif instr_name == "SubReg":
				instr_data = (0x3 << 12) | (random.randint( 0, 15 ) << 8) | (random.randint( 0, 15 ) << 4) | random.randint( 0, 15 )
			elif instr_name == "MulReg":
				instr_data = (0x4 << 12) | (random.randint( 0, 15 ) << 8) | (random.randint( 0, 15 ) << 4) | random.randint( 0, 15 )
			elif instr_name == "DivReg":
				instr_data = (0x5 << 12) | (random.randint( 0, 15 ) << 8) | (random.randint( 0, 15 ) << 4) | random.randint( 0, 15 )
			elif instr_name == "MovReg":
				instr_data = (0x3 << 13) | (0 << 8) | (random.randint( 0, 15 ) << 4) | (random.randint( 0, 15 ))
			elif instr_name == "SwapReg":
				instr_data = (0x3 << 13) | (1 << 8) | (random.randint( 0, 15 ) << 4) | (random.randint( 0, 15 ))
			elif instr_name == "JumpRegZero":
				instr_data = (0x3 << 13) | (2 << 8) | (random.randint( 0, 15 ) << 4) | (random.randint( 0, 15 ))
			elif instr_name == "JumpRegNotZero":
				instr_data = (0x3 << 13) | (3 << 8) | (random.randint( 0, 15 ) << 4) | (random.randint( 0, 15 ))
			elif instr_name == "DMAInit":
				instr_data = (0x3 << 13) | (4 << 8) | random.randint( 1, 2 ) #(random.randint( 0, 0xFF))
			elif instr_name == "DMARead":
				instr_data = (0x3 << 13) | (5 << 8) | (random.randint( 0, 15 ) << 4) | (random.randint( 0, 15 ))
				next_invalid_opcode = True
			elif instr_name == "DMAWrite":
				instr_data = (0x3 << 13) | (6 << 8) | (random.randint( 0, 15 ) << 4) | (random.randint( 0, 15 ))
				next_invalid_opcode = True
			elif instr_name == "JumpOffset":
				instr_data = (0x3 << 13) | (random.randint( 7, 8 ) << 8) | (random.randint( 0, 0xFF ))
			elif instr_name == "JumpReg":
				instr_data = (0x3 << 13) | (9 << 8) | (random.randint( 0, 15 ))
			elif instr_name == "GetInstrCount":
				instr_data = (0x3 << 13) | (10 << 8) | (random.randint( 0, 15 ) << 4) | (random.randint( 0, 15 ))
			elif instr_name == "GetRand":
				instr_data = (0x3 << 13) | (11 << 8) | (random.randint( 0, 15 ))
			elif instr_name == "GetSeedMaterial":
				instr_data = (0x3 << 13) | (12 << 8) | (random.randint( 0, 15 ))
			elif instr_name == "LoadRegister":
				instr_data = (0x3 << 13) | (13 << 8) | (random.randint( 0, 15 ) << 4) | (random.randint( 0, 15 ))
			elif instr_name == "StoreRegister":
				instr_data = (0x3 << 13) | (14 << 8) | (random.randint( 0, 15 ) << 4) | (random.randint( 0, 15 ))
			elif instr_name == "InvalidOpcode":
				instr_data = (0x3 << 13) | (15 << 8) | (random.randint( 0, 0xFF ))
			elif instr_name == "AddImm":
				instr_data = (0x4 << 13) | (0 << 11) | (random.randint( 0, 15 ) << 7) | (random.randint( 0, 127 ))
			elif instr_name == "SubImm":
				instr_data = (0x4 << 13) | (1 << 11) | (random.randint( 0, 15 ) << 7) | (random.randint( 0, 127 ))
			elif instr_name == "MulImm":
				instr_data = (0x4 << 13) | (2 << 11) | (random.randint( 0, 15 ) << 7) | (random.randint( 0, 127 ))
			elif instr_name == "DivImm":
				instr_data = (0x4 << 13) | (3 << 11) | (random.randint( 0, 15 ) << 7) | (random.randint( 0, 127 ))
			elif instr_name == "JumpLTReg":
				instr_data = (0x5 << 13) | (0 << 12) | (random.randint( 0, 15 ) << 8) | (random.randint( 0, 15 ) << 4) | (random.randint( 0, 15 ))
			elif instr_name == "JumpGTReg":
				instr_data = (0x5 << 13) | (0 << 12) | (random.randint( 0, 15 ) << 8) | (random.randint( 0, 15 ) << 4) | (random.randint( 0, 15 ))
			elif instr_name == "JumpOffsetZero":
				instr_data = (0x6 << 13) | (random.randint( 0, 15 ) << 9) | (random.randint( 0, 1 ) << 8) | (random.randint( 0, 255 ))
			elif instr_name == "JumpOffsetNotZero":
				instr_data = (0x7 << 13) | (random.randint( 0, 15 ) << 9) | (random.randint( 0, 1 ) << 8) | (random.randint( 0, 255 ))
			else:
				print "Missing instruction: %s\n" % instr_name

			#print "EMIT INSTR: %s::%04X\n" % (instr_name, instr_data) 

			section_data += struct.pack( 'H', instr_data )
			i += 1

		return section_data

	def GenerateDataSection( self, sectionSize ):
		section_data = struct.pack( 'B', random.randint( 0, 255 ) ) * sectionSize
		return section_data

	def GenerateCommentSection( self, sectionSize ):
		section_data = struct.pack( 'B', random.randint( 0, 255 ) ) * sectionSize
		return section_data

	def gen_file(self):
		# Generate new section
		section_count = random.randint( 1, 4 )

		# Save file
		file_section_header_data = ''
		file_section_data = ''

		section_file_offset = 0

		i = 0
		while i < section_count:
			if i == 0:
				sectionType = self.SECTION_TYPE_EXECUTE
			else:
				sectionType = random.randint( 0, 2 )

			sectionAddress = random.randint( 0, 0x7FFF ) * 2
			sectionSize = random.randint( 1, 3 ) * 512

			if ( (sectionAddress + sectionSize) > 0x10000 ):
				sectionSize = 512
				if ( (sectionAddress + sectionSize) > 0x10000 ):
					sectionAddress = (0x10000 - sectionSize)
			
			if ( i == 0 ):
				entry_address = random.randint( sectionAddress, sectionAddress+sectionSize-2 )
				entry_address = entry_address & 0xFFFE # (sectionAddress + sectionSize) - 12
				#print "Chosen entry address: %08X\n" % entry_address

			if ( sectionType == self.SECTION_TYPE_EXECUTE ):
				sectionData = self.GenerateExecuteSection( sectionSize )
			elif ( sectionType == self.SECTION_TYPE_DATA ):
				sectionData = self.GenerateDataSection( sectionSize )
			else:
				sectionData = self.GenerateCommentSection( sectionSize )

			file_section_header_data += struct.pack( 'B', sectionType )
			file_section_header_data += struct.pack( 'H', sectionSize )
			file_section_header_data += struct.pack( 'H', sectionAddress )
			file_section_header_data += struct.pack( 'I', 12+(9*section_count)+section_file_offset )

			file_section_data += sectionData
			i += 1

			section_file_offset += sectionSize
		
		# File header
		self.file_data = ''
		self.file_data += struct.pack( 'I', 0xc3585c51 )
		self.file_data += struct.pack( 'I', 12+len(file_section_header_data)+len(file_section_data) )
		self.file_data += struct.pack( 'H', section_count )
		self.file_data += struct.pack( 'H', entry_address )

		self.file_data += file_section_header_data
		self.file_data += file_section_data

		self.write( struct.pack( 'I', len(self.file_data) ) )
		self.write( self.file_data )

	def DMAInit( self, device_id ):
		self.dma_device_id = device_id

	def DMARead( self, reg_addr, reg_len  ):
		self.dma_engine.InitReadWorker( self.dma_device_id, self.cpu_registers[reg_addr], self.cpu_registers[reg_len] )

	def DMAWrite( self, reg_addr, reg_len ):
		self.dma_engine.InitWriteWorker( self.dma_device_id, self.cpu_registers[reg_addr], self.cpu_registers[reg_len] )

	def run_vm( self ):
		self.regs = np.zeros( 16, dtype=np.uint16 )
		self.cpu_exception = False
		self.cpu_instr_count = 0
		self.dma_device_id = 0

		# Memory Management Unit
		self.mmu = MMU( )

		# DMA Engine
		self.dma_engine = DMAEngine( self.mmu, self.write, self.read )


		if ( len( self.file_data ) > 64000 ):
			self.ExitEarly()
			return ''

		if ( len( self.file_data ) < 16 ):
			self.ExitEarly()
			return ''

		# Load file!
		file_header = struct.unpack( 'I', self.file_data[0:4] )[0]
		
		if ( file_header != 0xc3585c51 ):
			self.ExitEarly()
			return ''

		file_size = struct.unpack( 'I', self.file_data[4:8] )[0]

		if ( len(self.file_data) != file_size ):
			self.ExitEarly()
			return ''

		section_count = struct.unpack( 'H', self.file_data[8:10] )[0]
		entry_address = struct.unpack( 'H', self.file_data[10:12] )[0]

		if ( section_count == 0 ):
			self.ExitEarly()
			return ''

		if ( section_count > 10 ):
			self.ExitEarly()
			return ''

		if ( len(self.file_data)-12 < (9*section_count) ):
			self.ExitEarly()
			return ''

		# Load sections

		file_pos = 12
		i = 0
		while i < section_count:
			section_type = struct.unpack( 'B', self.file_data[file_pos:file_pos+1] )[0]
			section_size = struct.unpack( 'H', self.file_data[file_pos+1:file_pos+3] )[0]
			section_address = struct.unpack( 'H', self.file_data[file_pos+3:file_pos+5] )[0]
			section_offset = struct.unpack( 'I', self.file_data[file_pos+5:file_pos+9] )[0]

			if ( section_type > 2 ):
				self.ExitEarly()
				return ''

			if ( (section_address+section_size) > 0x10000 ):
				self.ExitEarly()
				return ''

			if ( section_offset+section_size > len(self.file_data) ):
				self.ExitEarly()
				return ''

			file_pos += 9
			i += 1

			# Now load
			if ( section_type == self.SECTION_TYPE_EXECUTE ):
				self.LoadSection( self.SECTION_TYPE_EXECUTE, self.file_data[section_offset:section_offset+section_size], section_address )
			elif ( section_type == self.SECTION_TYPE_DATA ):
				self.LoadSection( self.SECTION_TYPE_DATA, self.file_data[section_offset:section_offset+section_size], section_address )
			elif ( section_type == self.SECTION_TYPE_COMMENT ):
				self.LoadSection( self.SECTION_TYPE_COMMENT, self.file_data[section_offset:section_offset+section_size], section_address )

		# Execute
		self.entry_address = entry_address
	
		cpu_registers = np.zeros( 16, dtype=np.uint16 )
		self.cpu_registers = cpu_registers

		cpu_registers[14] = 0xFFFC
		cpu_registers[15] = entry_address

		#print "Running CPU!\n"

		# Run
		exception_text = ''
		exception_flag = False
		instr_count = 0
		while True:
			# Fetch
			instr_data, success_flag = self.mmu.Fetch16( cpu_registers[15] )

			# Advance PC
			cpu_registers[15] += 2

			if ( success_flag == False ):
				#print "Exception (MMU Fetch)! %d %X\n" % (instr_count, cpu_registers[15])
				exception_text = "MMU Fetch Exception"	
				exception_flag = True
				break
			
			if ( instr_count > 400 ):
				instr_count += 1
				exception_text = "Max instructions reached"
				exception_flag = True
				break
			
			instr_count += 1

			self.read( delim='\n=====\n', expect=("DEBUG:Instructions: %d\nR0  = %08X R1  = %08X R2  = %08X R3  = %08X\nR4  = %08X R5  = %08X R6  = %08X R7  = %08X\nR8  = %08X R9  = %08X R10 = %08X R11 = %08X\nR12 = %08X R13 = %08X SP  = %08X PC  = %08X\n=====\n" % (instr_count, cpu_registers[0], cpu_registers[1], cpu_registers[2], cpu_registers[3], cpu_registers[4], cpu_registers[5], cpu_registers[6], cpu_registers[7], cpu_registers[8], cpu_registers[9], cpu_registers[10], cpu_registers[11], cpu_registers[12], cpu_registers[13], cpu_registers[14], cpu_registers[15] ) ) )
		
			# Service DMA Engine
			self.dma_engine.ServiceDMA()

			# Run CPU
			instr_part1 = ((instr_data >> 13) & 0x7)

			#print "INSTR %04X: %04X (%d)\n" % ( cpu_registers[15]-2, instr_data, instr_part1 )
			if ( instr_part1 == 0 ):
				instr_part2 = ((instr_data >> 12) & 0x1)
				reg1 = ((instr_data >> 8) & 0xF)
				immediate = ((instr_data >> 0) & 0xFF)

				if ( instr_part2 == 0 ):
					cpu_registers[reg1] = (cpu_registers[reg1] & 0xFF) | (immediate << 8)
				else:
					cpu_registers[reg1] = (cpu_registers[reg1] & 0xFF00) | immediate
			
			elif ( instr_part1 == 1 ):
				instr_part2 = ((instr_data >> 12) & 0x1)
				reg1 = ((instr_data >> 8) & 0xF)
				reg2 = ((instr_data >> 4) & 0xF)
				reg3 = ((instr_data >> 0) & 0xF)

				if ( instr_part2 == 0 ):
					cpu_registers[reg1] = (cpu_registers[reg2] + cpu_registers[reg3]) & 0xFFFF
				else:
					cpu_registers[reg1] = (cpu_registers[reg2] - cpu_registers[reg3]) & 0xFFFF

			elif ( instr_part1 == 2 ):
				instr_part2 = ((instr_data >> 12) & 0x1)
				reg1 = ((instr_data >> 8) & 0xF)
				reg2 = ((instr_data >> 4) & 0xF)
				reg3 = ((instr_data >> 0) & 0xF)

				if ( instr_part2 == 0 ):
					cpu_registers[reg1] = (cpu_registers[reg2] * cpu_registers[reg3]) & 0xFFFF
				else:
					if ( cpu_registers[reg3] == 0 ):
						exception_text = "Divide by zero"
						exception_flag = True
					else:
						cpu_registers[reg1] = int(cpu_registers[reg2] / cpu_registers[reg3]) & 0xFFFF
			
			elif ( instr_part1 == 3 ):
				instr_part2 = ((instr_data >> 8) & 0xF)

				if ( instr_part2 == 0 ):
					cpu_registers[ (instr_data >> 4) & 0xF ] = cpu_registers[ (instr_data & 0xF) ]
				elif ( instr_part2 == 1 ):
					temp = cpu_registers[ (instr_data >> 4) & 0xF ]
					cpu_registers[ (instr_data >> 4) & 0xF ] = cpu_registers[ (instr_data & 0xF) ]
					cpu_registers[ (instr_data & 0xF) ] = temp
				elif ( instr_part2 == 2 ):
					if ( cpu_registers[ (instr_data >> 4) & 0xF ] == 0 ):
						cpu_registers[15] = (cpu_registers[15] + cpu_registers[ (instr_data & 0xF) ]) & 0xFFFF
				elif ( instr_part2 == 3 ):
					if ( cpu_registers[ (instr_data >> 4) & 0xF ] != 0 ):
						cpu_registers[15] = (cpu_registers[15] + cpu_registers[ (instr_data & 0xF) ]) & 0xFFFF
				elif ( instr_part2 == 4 ):
					self.DMAInit( (instr_data & 0xFF) )
				elif ( instr_part2 == 5 ):
					self.DMARead( (instr_data >> 4 ) & 0xF, (instr_data & 0xF) )
				elif ( instr_part2 == 6 ):
					self.DMAWrite( (instr_data >> 4) & 0xF, (instr_data & 0xF) )
				elif ( instr_part2 == 7 ):
					cpu_registers[15] = (cpu_registers[15] + (instr_data & 0xFF)) & 0xFFFF
				elif ( instr_part2 == 8 ):
					cpu_registers[15] = (cpu_registers[15] - (instr_data & 0xFF)) & 0xFFFF
				elif ( instr_part2 == 9 ):
					cpu_registers[15] = cpu_registers[ (instr_data & 0xF) ]
				elif ( instr_part2 == 10 ):
					cpu_registers[ (instr_data & 0xF) ] = 0
					cpu_registers[ (instr_data >> 4) & 0xF ] = instr_count
				elif ( instr_part2 == 11 ):
					#print "GetRand()\n"
					cpu_registers[ (instr_data & 0xF) ] = self.prng.prng() & 0xFFFF
				elif ( instr_part2 == 12 ):
					#print "GetSeedMaterial()\n"
					seed_offset = ((instr_count % 256) << 2)
					cpu_registers[ (instr_data & 0xF) ] = (self.prng.prng()&0xFFFF) ^ struct.unpack( 'H', self.magic_page[seed_offset:seed_offset+2] )[0]
				elif ( instr_part2 == 13 ):
					value, success_flag = self.mmu.Read16( cpu_registers[ (instr_data & 0xF) ] )
					if ( success_flag == False ):
						exception_text = "MMU Read Exception"
						exception_flag = True
					else:
						cpu_registers[ (instr_data >> 4) & 0xF ] = value
				elif ( instr_part2 == 14 ):
					success_flag = self.mmu.Write16( cpu_registers[ (instr_data & 0xF) ], cpu_registers[ (instr_data >> 4) & 0xF ] )
					if ( success_flag == False ):
						exception_text = "MMU Write Exception"
						exception_flag = True
				else:
					exception_text = "Invalid opcode"
					exception_flag = True
			elif ( instr_part1 == 4 ):
				instr_part2 = ((instr_data >> 11) & 0x3)
				regD = ((instr_data >> 7) & 0xF)
				immediate = (instr_data & 0x7F)

				if ( instr_part2 == 0 ):
					cpu_registers[ regD ] = (cpu_registers[ regD ] + immediate) & 0xFFFF
				elif ( instr_part2 == 1 ):
					cpu_registers[ regD ] = (cpu_registers[ regD ] - immediate) & 0xFFFF
				elif ( instr_part2 == 2 ):
					cpu_registers[ regD ] = (cpu_registers[ regD ] * immediate) & 0xFFFF
				else:
					if ( immediate == 0 ):
						exception_text = "Divide by zero"
						exception_flag = True
					else:
						cpu_registers[ regD ] = int(cpu_registers[ regD ] / immediate) & 0xFFFF

			elif ( instr_part1 == 5 ):
				regL = ((instr_data >> 8) & 0xF)
				regR = ((instr_data >> 4) & 0xF)
				offsetReg = (instr_data & 0xF)

				if ( ((instr_data >> 12) & 0x1) == 0 ):
					if ( cpu_registers[regL] < cpu_registers[regR] ):
						cpu_registers[15] = (cpu_registers[15] + cpu_registers[offsetReg]) & 0xFFFF
				else:
					if ( cpu_registers[regL] > cpu_registers[regR] ):
						cpu_registers[15] = (cpu_registers[15] + cpu_registers[offsetReg]) & 0xFFFF

			elif ( instr_part1 == 6 ): # JumpOffsetZero
				reg = ((instr_data >> 9) & 0xF)
				sign = ((instr_data >> 8) & 0x1)
				immediate = (instr_data & 0xFF) << 1

				if ( cpu_registers[reg] == 0 ):
					if ( sign == 0 ):
						cpu_registers[15] = (cpu_registers[15] + immediate) & 0xFFFF
					else:
						cpu_registers[15] = (cpu_registers[15] - immediate) & 0xFFFF

			elif ( instr_part1 == 7 ): # JumpOffsetNotZero
				reg = ((instr_data >> 9) & 0xF)
				sign = ((instr_data >> 8) & 0x1)
				immediate = (instr_data & 0xFF) << 1

				if ( cpu_registers[reg] != 0 ):
					if ( sign == 0 ):
						cpu_registers[15] = (cpu_registers[15] + immediate) & 0xFFFF
					else:
						cpu_registers[15] = (cpu_registers[15] - immediate) & 0xFFFF

			if ( exception_flag == True ):
				#print "Received exception! %s\n" % exception_text
				break

			for t in range( 0, 15 ):
				cpu_registers[t] = np.uint16( cpu_registers[t] )


		if ( exception_flag == True ):
			self.read( delim='\n', expect=("Exception: %s\n" % exception_text) )

		self.read( delim='\nEnd Registers\n', expect=("Registers:\nInstructions: %d\nR0  = %08X R1  = %08X R2  = %08X R3  = %08X\nR4  = %08X R5  = %08X R6  = %08X R7  = %08X\nR8  = %08X R9  = %08X R10 = %08X R11 = %08X\nR12 = %08X R13 = %08X SP  = %08X PC  = %08X\nEnd Registers\n" % (instr_count, cpu_registers[0], cpu_registers[1], cpu_registers[2], cpu_registers[3], cpu_registers[4], cpu_registers[5], cpu_registers[6], cpu_registers[7], cpu_registers[8], cpu_registers[9], cpu_registers[10], cpu_registers[11], cpu_registers[12], cpu_registers[13], cpu_registers[14], cpu_registers[15] ) ) )
		return

	def ExitEarly( self ):
		self.read( delim='\n', expect='Exiting\n' )

	def gen_bad_file( self ):
		random_data = '' 
		random_length = random.randint( 12, 50000 )
		for i in range( random_length ):
			random_data += struct.pack( 'B', random.randint( 0, 255 ) )

		self.write( struct.pack( 'I', len(random_data) ) )
		self.write( random_data )
		self.file_data = random_data

		return

	def exit( self ):
	
		return
