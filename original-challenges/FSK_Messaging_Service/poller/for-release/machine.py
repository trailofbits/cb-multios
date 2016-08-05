#!/usr/bin/env python

from generator.actions import Actions
import random
import struct
import string
import math
import binascii

class SinglePacket():
	def __init__(self, packet_type, packet_data):
		self.packet_type = packet_type
		self.packet_data = packet_data

		self.MAX_USERNAME_LENGTH = 8

	def ParsePacket(self):
		packet_parse_string = ""

		if ( self.packet_type == 0 ):
			# Broadcast packet
			if ( len(self.packet_data) < 1 ):
				return "[BROADCAST]Missing length"

			fromUserNameLen = struct.unpack('B', self.packet_data[0] )[0]

			if ( len(self.packet_data) < fromUserNameLen+2 ):
				return "[BROADCAST]Invalid message length"

			if ( fromUserNameLen > self.MAX_USERNAME_LENGTH ):
				return "[BROADCAST]Username length was too large"

			broadcastMessageLen = struct.unpack( 'B', self.packet_data[fromUserNameLen+1] )[0]

			if ( len(self.packet_data) != (fromUserNameLen+broadcastMessageLen+2) ):
				return "[BROADCAST]Message length did not match packet length"

			return "[BROADCAST]From %s::%s" % ( self.packet_data[1:fromUserNameLen+1], self.packet_data[fromUserNameLen+2:fromUserNameLen+2+broadcastMessageLen] )

		elif ( self.packet_type == 1 ):
			if ( len(self.packet_data) < 2 ):
				return "[CHANNEL]Invalid length"

			fromUserNameLen = struct.unpack('B', self.packet_data[0] )[0]

			if ( len(self.packet_data) < fromUserNameLen+3 ):
				return "[CHANNEL]Invalid message length"

			if ( fromUserNameLen > self.MAX_USERNAME_LENGTH ):
				return "[CHANNEL]Username length was too large"

			channelNumber = struct.unpack( 'B', self.packet_data[fromUserNameLen+1] )[0]
			channelMessageLen = struct.unpack( 'B', self.packet_data[fromUserNameLen+2] )[0]

			if ( len(self.packet_data) != (fromUserNameLen+channelMessageLen+3) ):
				return "[CHANNEL]Message length did not match packet length"

			return "[CHANNEL %d]Message from %s::%s" % ( channelNumber, self.packet_data[1:fromUserNameLen+1], self.packet_data[fromUserNameLen+3:fromUserNameLen+channelMessageLen+3] )

		elif ( self.packet_type == 2 ):
			if ( len(self.packet_data) < 2 ):
				return "[PRIVATE MESSAGE]Invalid length"

			toUserNameLen = struct.unpack('B', self.packet_data[0] )[0]

			if ( len(self.packet_data) < toUserNameLen+3 ):
				return "[PRIVATE MESSAGE]Message length did not match packet length"

			if ( toUserNameLen > self.MAX_USERNAME_LENGTH ):
				return "[PRIVATE MESSAGE]Username length was too large"

			fromUserNameLen = struct.unpack('B', self.packet_data[toUserNameLen+1] )[0]

			if ( len(self.packet_data) < toUserNameLen+fromUserNameLen+3 ):
				return "[PRIVATE MESSAGE]Message length did not match packet length"

			if ( fromUserNameLen > self.MAX_USERNAME_LENGTH ):
				return "[PRIVATE MESSAGE]Username length was too large"

			privateMessageLen = struct.unpack('B', self.packet_data[toUserNameLen+fromUserNameLen+2] )[0]

			if ( len(self.packet_data) != toUserNameLen+fromUserNameLen+privateMessageLen+3 ):
				return "[PRIVATE MESSAGE]Message length did not match packet length"

			return "[PRIVATE MESSAGE]%s to %s::%s" % (self.packet_data[1:toUserNameLen+1], self.packet_data[toUserNameLen+2:toUserNameLen+fromUserNameLen+2], self.packet_data[toUserNameLen+fromUserNameLen+3:toUserNameLen+fromUserNameLen+privateMessageLen+3] )
	
		elif ( self.packet_type == 3 ):
			if ( len(self.packet_data) < 1 ):
				return "[CONNECT MESSAGE]Invalid length"

			connectUserNameLen = struct.unpack( 'B', self.packet_data[0] )[0]

			if ( len(self.packet_data) != connectUserNameLen+1 ):
				return "[CONNECT MESSAGE]Message length did not match packet length"

			if ( connectUserNameLen > self.MAX_USERNAME_LENGTH ):
				return "[CONNECT MESSAGE]Username length was too large"

			return "[CONNECT MESSAGE]%s connected" % (self.packet_data[1:connectUserNameLen+1])

		elif ( self.packet_type == 4 ):
			if ( len(self.packet_data) < 1 ):
				return "[DISCONNECT MESSAGE]Invalid length"

			disconnectUserNameLen = struct.unpack( 'B', self.packet_data[0] )[0]

			if ( len(self.packet_data) != disconnectUserNameLen+1 ):
				return "[DISCONNECT MESSAGE]Message length did not match packet length"

			if ( disconnectUserNameLen > self.MAX_USERNAME_LENGTH ):
				return "[DISCONNECT MESSAGE]Username length was too large"

			return "[DISCONNECT MESSAGE]%s disconnected" % (self.packet_data[1:disconnectUserNameLen+1])

		return ""

	def get_type(self):
		return self.packet_type


class PacketReceiver(Actions):

    def start(self):
	#self.delay(100)
	self.SAMPLE_FS_RATE = 9600
	self.SEND_AMPLITUDE = 64.0

	ts = struct.unpack( 'I', self.magic_page[0:4] )[0] + struct.unpack( 'I', self.magic_page[4:8] )[0] + struct.unpack( 'I', self.magic_page[8:12] )[0] + struct.unpack( 'I', self.magic_page[12:16] )[0] 

	ts &= 0x7FFFF

	ts += 1452975630

        self.read(delim='\n', expect=("[[RECEIVER STARTED -- TIMESTAMP: %d]]\n" % ts))
	self.sample_count = 0

	self.packet_list = list()

    def get_checksum( self, input_bytes ):
	checksum = 0xbfad

	for c in input_bytes:
	    checksum = (checksum + ord(c)) & 0xffff
					          
	return checksum 

    def send_packet_byte( self, send_byte ):
	transmit_bytes = ""

	i = 0
	while i < 8:
		# Get send bit
		send_bit = (int(send_byte)>> (7-i)) & 0x1

		i += 1

		# Generate waveform
		period = 0
		while period < 32:
			# Write out appropriate FSK waveform
			if send_bit == 0:
				send_sample = self.SEND_AMPLITUDE * math.cos( 2 * math.pi * 1200.0 * (float(period) / self.SAMPLE_FS_RATE) )
			else:
				send_sample = self.SEND_AMPLITUDE * math.cos( 2 * math.pi * 2400.0 * (float(period) / self.SAMPLE_FS_RATE) )

			# Write out sample
			#self.write( struct.pack( 'b', int(send_sample) ) )
			transmit_bytes += struct.pack( 'b', int(send_sample) )

			#self.sample_count += 1

			# Update period
			period += 1

	self.write( transmit_bytes )

    def get_samples_for_packet(self, packet_data):
	# 3 bytes for preamble, 2 bytes for sync word, n-bytes for packet data, and 2-bytes for CRC
	send_byte_count = 3
	send_byte_count += 2

	# Factor length of packet
	send_byte_count += 1

	# Now factor packet data
	send_byte_count += len(packet_data)

	# Lastly checksum
	send_byte_count += 2

	return (send_byte_count * 32 * 8)

    def send_packet_data(self, packet_data):
	send_byte_count = 0

	# Premable 1010 1010 1010 1010 1010 1010
	self.send_packet_byte( 0xAA )
	self.send_packet_byte( 0xAA )
	self.send_packet_byte( 0xAA )
	send_byte_count += 3

	# Sync word 0xCFA3
	self.send_packet_byte( 0xCF )
	self.send_packet_byte( 0xA3 )
	send_byte_count += 2

	# packet data
	self.send_packet_byte( len(packet_data) )
	send_byte_count += 1

	for cur_byte in packet_data:
		self.send_packet_byte( struct.unpack('B', cur_byte)[0] )
		send_byte_count += 1

	# CHECKSUM
	checksum_value = self.get_checksum( packet_data )

	self.send_packet_byte( (checksum_value >> 8) & 0xff )
	self.send_packet_byte( (checksum_value & 0xff) )

	send_byte_count += 2

	return (send_byte_count * 32 * 8)

    def corrupt_packet(self, packet_data):
	    corrupt_count = random.randint( 0, len(packet_data)-1 )

	    packet_data_characters = list(packet_data)
	    while corrupt_count > 0:
		    loc = random.randint( 0, len(packet_data)-1 )
		    new_value = random.randint( 1, 254 )

		    if ( new_value >= 10 ):
		    	new_value += 1

		    packet_data_characters[loc] = struct.pack( 'B', new_value )

		    corrupt_count -= 1

	    return ''.join(packet_data_characters)

    def run(self):
	    packet_count = random.randint( 0, 10 )

	    send_sample_count = 0
	    max_send_samples = self.SAMPLE_FS_RATE * 4

	    max_packet_length = 48
	    current_packet = 0

	    packet_byte_count = 0
	    packet_valid_count = 0
	    packet_invalid_count = 0

	    transmit_bytes = ""
	    while send_sample_count < 256:
	    	#self.write( struct.pack( 'b', random.randint( -100, 100 ) ) )
		transmit_bytes += struct.pack( 'b', random.randint( -100, 100 ) )
		send_sample_count += 1

	    self.write( transmit_bytes )

	    while current_packet < packet_count:
		    packet_type = random.randint( 0, 4 )

		    max_username_len = random.randint( 1, 7 )
		    from_username = ''.join( random.choice( string.ascii_uppercase + string.ascii_lowercase + string.digits) for _ in range( 0, max_username_len ) )

		    if packet_type == 0:
		    	packet_data_len_max = max_packet_length - (len(from_username) + 2)
		    
		    	packet_data_len = random.randint( 1, packet_data_len_max-1 )
			packet_data = ''.join( random.choice( string.ascii_uppercase + string.ascii_lowercase + string.digits) for _ in range( 0, packet_data_len ) )
		    	
			# send broadcast
			packet_data = struct.pack( 'B', packet_type ) + struct.pack( 'B', len(from_username) ) + from_username + struct.pack( 'B', len(packet_data) ) + packet_data

			if ( random.randint( 0, 7 ) == 0 ):
				# Corrupt
				packet_data = self.corrupt_packet( packet_data )
				
				packet_type = struct.unpack( 'B', packet_data[0] )[0]
			
			if ( self.get_samples_for_packet( packet_data ) + send_sample_count + 128) > max_send_samples:
				break

			send_sample_count += self.send_packet_data( packet_data )

			if ( packet_type > 4 ):
				packet_invalid_count += 1
			else:
				new_packet = SinglePacket( packet_type, packet_data[1:] )
				self.packet_list.append( new_packet )

				packet_byte_count += len(packet_data)
				packet_valid_count += 1
			   
		    elif packet_type == 1:
			packet_data_len_max = max_packet_length - (len(from_username) + 3)

			packet_data_len = random.randint( 1, packet_data_len_max-1 )
			packet_data = ''.join( random.choice( string.ascii_uppercase + string.ascii_lowercase + string.digits) for _ in range( 0, packet_data_len ) )

			packet_channel_number = random.randint( 0, 255 )

			# Create channel packet
			packet_data = struct.pack( 'B', packet_type ) + struct.pack( 'B', len(from_username) ) + from_username + struct.pack( 'B', packet_channel_number ) + struct.pack( 'B', len(packet_data) ) + packet_data

			if ( random.randint( 0, 7 ) == 0 ):
				# Corrupt
				packet_data = self.corrupt_packet( packet_data )
				
				packet_type = struct.unpack( 'B', packet_data[0] )[0]
			
			if ( self.get_samples_for_packet( packet_data ) + send_sample_count + 128) > max_send_samples:
				break

			send_sample_count += self.send_packet_data( packet_data )

			if ( packet_type > 4 ):
				packet_invalid_count += 1
			else:
				new_packet = SinglePacket( packet_type, packet_data[1:] )
				self.packet_list.append( new_packet )

				packet_byte_count += len(packet_data)
				packet_valid_count += 1

		    elif packet_type == 2:
		        max_to_username_len = random.randint( 1, 7 )
		        to_username = ''.join( random.choice( string.ascii_uppercase + string.ascii_lowercase + string.digits) for _ in range( 0, max_to_username_len ) )
			
			packet_data_len_max = max_packet_length - (len(from_username) + len(to_username) + 3)

			packet_data_len = random.randint( 1, packet_data_len_max-1 )
			packet_data = ''.join( random.choice( string.ascii_uppercase + string.ascii_lowercase + string.digits) for _ in range( 0, packet_data_len ) )

			# Create private message packet
			packet_data = struct.pack( 'B', packet_type ) + struct.pack( 'B', len(to_username) ) + to_username + struct.pack('B', len(from_username) ) + from_username + struct.pack('B', len(packet_data)) + packet_data

			if ( random.randint( 0, 7 ) == 0 ):
				# Corrupt
				packet_data = self.corrupt_packet( packet_data )
				
				packet_type = struct.unpack( 'B', packet_data[0] )[0]
			
			if ( self.get_samples_for_packet( packet_data ) + send_sample_count + 128) > max_send_samples:
				break

			send_sample_count += self.send_packet_data( packet_data )

			if ( packet_type > 4 ):
				packet_invalid_count += 1
			else:
				new_packet = SinglePacket( packet_type, packet_data[1:] )
				self.packet_list.append( new_packet )

				packet_byte_count += len(packet_data)
				packet_valid_count += 1

		    elif packet_type == 3 or packet_type == 4:
			packet_data = struct.pack( 'B', packet_type ) + struct.pack( 'B', len(from_username) ) + from_username
			
			if ( random.randint( 0, 7 ) == 0 ):
				# Corrupt
				packet_data = self.corrupt_packet( packet_data )
				
				packet_type = struct.unpack( 'B', packet_data[0] )[0]

			if ( self.get_samples_for_packet( packet_data ) + send_sample_count + 128) > max_send_samples:
				break

			send_sample_count += self.send_packet_data( packet_data )

			if ( packet_type > 4 ):
				packet_invalid_count += 1
			else:
				new_packet = SinglePacket( packet_type, packet_data[1:] )
				self.packet_list.append( new_packet )

				packet_byte_count += len(packet_data)
				packet_valid_count += 1


		    # Go to next packet
		    current_packet += 1

	    # Send remaining bytes
	    transmit_bytes = ""
	    while send_sample_count < max_send_samples:
	    	#self.write( struct.pack( 'b', random.randint( -100, 100 ) ) )
	    	transmit_bytes += struct.pack( 'b', random.randint( -100, 100 ) )

		send_sample_count += 1

	    self.write( transmit_bytes )

	    # Display packets
	    self.read( delim='\n', expect="Total %d bytes received and %d invalid packets." % (packet_byte_count, packet_invalid_count ) )
	    self.read( delim='\n', expect="Displaying %d received packets:" % packet_valid_count )

	    # Parse individual packets
	    display_packet_number = 0
	    for display_packet in self.packet_list[::-1]:
		    # Read display string
		    self.read( delim='\n', expect="Displaying packet %d type %d:" % (display_packet_number, display_packet.get_type()) )

		    # Display packet data
		    display_string = display_packet.ParsePacket()

		    # Validate
		    self.read( delim='\n', expect=display_string )

		    # Next packet
		    display_packet_number += 1

    def finish(self):
	    pass
