#!/usr/bin/env python

from generator.actions import Actions
import random
from struct import pack
from struct import unpack

def bit_writer( write_func, bit_buffer, bit_pos, bit_value ):
    bit_pos = bit_pos % 8

    bit_buffer = (bit_buffer << 1) | (bit_value & 0x1)

    bit_pos = bit_pos + 1

    if ( bit_pos == 8 ):
        # Write out a byte
        write_func( pack( "B", bit_buffer ) )

        # Clear both
        bit_pos = 0
        bit_buffer = 0

        # Return 1 byte written and the new bit_buffer and bit_ops
        return (1,bit_buffer,bit_pos)
    else:
        # Byte not written yet (return 0 for bytes written) and bit_buffer and bit_pos
        return (0,bit_buffer,bit_pos)

def bit_flush( write_func, bit_buffer, bit_pos ):

    if bit_pos != 0:
        while bit_pos != 0:
            byte_sent,bit_buffer,bit_pos = bit_writer( write_func, bit_buffer, bit_pos, 1 )

        return (1,bit_buffer,bit_pos)
    else:
        return (0,bit_buffer,bit_pos)



class PacketGenerator(Actions):

    PACKET_COUNT_TEST_TOTAL = 60
    PACKET_BYTES_TOTAL = 64000

    PACKET_FRAGMENTED_BIT = 0x1
    PACKET_LAST_FRAGMENT_BIT = 0x2
    PACKET_LARGE_CHECKSUM_BIT = 0x4
    PACKET_PARITY_BIT = 0x8
    PACKET_PARITY_BIT_POS = 0x3

    PACKET_HEADER_IDENTIFIER_BIT_MASK = 0xF0
    PACKET_HEADER_IDENTIFIER_VALUE = 0xB0

    message_render_count = 0

    def start(self):
        self.packet_count = random.randint( 1, self.PACKET_COUNT_TEST_TOTAL )
        self.bytes_count = random.randint( 256, self.PACKET_BYTES_TOTAL )

    def read_render_header(self):
        self.read( delim='\n', expect="<HTML>\n" )
        self.read( delim='\n', expect="<HEAD>Messages</HEAD>\n" )
        self.read( delim='\n', expect="<BODY>\n" )

    def read_render_footer(self):
        self.read( delim='\n', expect="</BODY>\n" )
        self.read( delim='\n', expect="</HTML>\n" )

    def render_packet( self, packet_hdr, cur_packet_sequence_number, cur_packet_fragment_number, cur_packet_data, packet_len ):

        #print "Packet length coming in: %d" % packet_len
        if ( packet_hdr & self.PACKET_FRAGMENTED_BIT ):
            #print "Fragment %d sequence %d" % (cur_packet_fragment_number, cur_packet_sequence_number)
            self.packet_fragment_data[cur_packet_sequence_number][cur_packet_fragment_number] = cur_packet_data[2:]

            if ( packet_hdr & self.PACKET_LAST_FRAGMENT_BIT ):
                cur_packet_data = ''

                packet_fragments_total = 0
                packet_total_count = cur_packet_fragment_number+1

                i = 0
                while i < packet_total_count:
                    if (len(self.packet_fragment_data[cur_packet_sequence_number][i]) > 0 ):
                        cur_packet_data += self.packet_fragment_data[cur_packet_sequence_number][i]
                        packet_fragments_total += 1

                    i += 1

                #print "Assembled fragmented message: %d packets %d last packet" % (packet_fragments_total, cur_packet_fragment_number)
                if ( packet_fragments_total != cur_packet_fragment_number+1 ):
                    return

                packet_len = len(cur_packet_data)
                #print "Packet length is now: %d\n" % packet_len
            else:
                return


        # Now render the packet
        if ( packet_len >= 2 ):
            #print "Packet length=%d len(cur_packet_data)=%d" % (packet_len, len(cur_packet_data))

            # Read render header for packet
            self.read_render_header()

            # Get from and to address
            from_address = unpack( 'B', cur_packet_data[0] )[0]
            to_address = unpack( 'B', cur_packet_data[1] )[0]

            # Initialize render string
            render_string = ''

            # Initialize markup states
            markup_italics = False
            markup_bold = False
            markup_underline = False

            # Now process message
            cur_char_pos = 2
            while cur_char_pos < packet_len:
                curchar = unpack( 'B', cur_packet_data[cur_char_pos] )[0]

                if ( curchar & 0x80 ):
                    if ( curchar & 0x40 ):
                        lower_bits = (curchar & 0xF)

                        new_markup_italics = False
                        new_markup_bold = False
                        new_markup_underline = False
                        if ( lower_bits == 0 ):
                            # Clear em out
                            new_markup_italics = False
                            new_markup_bold = False
                            new_markup_underline = False
                        elif ( lower_bits == 1 ):
                            new_markup_italics = True
                        elif ( lower_bits == 2 ):
                            new_markup_bold = True
                        elif ( lower_bits == 3 ):
                            new_markup_underline = True
                        elif ( lower_bits == 4 ):
                            new_markup_italics = True
                            new_markup_bold = True
                        elif ( lower_bits == 5 ):
                            new_markup_italics = True
                            new_markup_underline = True
                        elif ( lower_bits == 6 ):
                            new_markup_bold = True
                            new_markup_underline = True
                        elif ( lower_bits == 7 ):
                            new_markup_italics = True
                            new_markup_bold = True
                            new_markup_underline = True
                        else:
                            # Do nothing
                            new_markup_italics = markup_italics
                            new_markup_bold = markup_bold
                            new_markup_underline = markup_underline

                        if ( markup_italics == True and new_markup_italics == False ):
                            render_string += '</i>'

                        if ( markup_italics == False and new_markup_italics == True ):
                            render_string += '<i>'

                        if ( markup_bold == True and new_markup_bold == False ):
                            render_string += '</b>'

                        if ( markup_bold == False and new_markup_bold == True ):
                            render_string += '<b>'

                        if ( markup_underline == True and new_markup_underline == False ):
                            render_string += '</u>'

                        if ( markup_underline == False and new_markup_underline == True ):
                            render_string += '<u>'

                        # Save new states
                        markup_italics = new_markup_italics
                        markup_bold = new_markup_bold
                        markup_underline = new_markup_underline
                    else:
                        lower_bits = (curchar & 0xF)

                        if ( lower_bits == 0 ):
                            render_string += '<BR>'
                        elif ( lower_bits == 1 ):
                            render_string += '&nbsp&nbsp&nbsp&nbsp'
                        elif ( lower_bits == 2 ):
                            render_string += '<p>'
                        elif ( lower_bits == 3 ):
                            render_string += '\n'
                else:
                    # Render character
                    if ( curchar >= 32 ):
                        render_string += chr(curchar)
                    else:
                        render_string += '_'

                cur_char_pos += 1


            # Now render the packet
            self.read( delim='\n', expect='<b>Message %d:</b><BR>\n' % self.message_render_count )

            # Update message render counter
            self.message_render_count += 1

            # To/From address
            self.read( delim='\n', expect='<b>From:</b> %d<BR>\n' % from_address )
            self.read( delim='\n', expect='<b>To:</b> %d<BR>\n' % to_address )

            # Lastly render the message contents
            self.read( delim='\n', expect='<b>Message Data:</b><BR>\n' )

            if ( len(render_string) > 0 ):
                self.read( length=len(render_string), expect=render_string )
            self.read( delim='\n', expect='\n' )

            # Read render footer for packet
            self.read_render_footer()

        return 0

    def write_packets(self):

        # Reset message render counter
        self.message_render_count = 0

        # Initialize bit buffers
        bytes_sent = 0
        bit_pos = 0
        bit_buffer = 0

        packet_cur = 0
        current_fragment_number = 0
        packet_sequence_number = 0

        self.packet_fragment_data = list()
        for i in range(1<<12):
            self.packet_fragment_data.append( list() )
            for t in range(16):
                self.packet_fragment_data[i].append( '' )

        #print "New run......"
        while packet_cur < self.packet_count:

            # Write out random noise (random bits) before sending the packet
            write_random_bits_count = random.randint( 0, 100 )

            '''
            cur_random_bit = 0
            while cur_random_bit < write_random_bits_count:
                # Check exit condition
                if ( bytes_sent >= self.bytes_count ):
                    return

                # Write out random noise before the packet...
                byte_sent, bit_buffer, bit_pos = bit_writer( self.write, bit_buffer, bit_pos, random.randint( 0, 1 ) )
                bytes_sent += byte_sent

                cur_random_bit = cur_random_bit + 1
            '''

            # Send preamble (before packet)
            preamble_bit_count = random.randint( 32, 64 )

            cur_preamble_bit = 0
            while cur_preamble_bit < preamble_bit_count:
                if ( bytes_sent >= self.bytes_count ):
                    return

                if ( cur_preamble_bit % 2 == 0 ):
                    byte_sent, bit_buffer, bit_pos = bit_writer( self.write, bit_buffer, bit_pos, 0 )
                    bytes_sent += byte_sent
                else:
                    byte_sent, bit_buffer, bit_pos = bit_writer( self.write, bit_buffer, bit_pos, 1 )
                    bytes_sent += byte_sent

                cur_preamble_bit = cur_preamble_bit + 1

            # Preamble sent now send sync field
            cur_sync_bit = 0
            cur_sync_pattern = 0xC3AC
            while cur_sync_bit < 16:
                if ( bytes_sent >= self.bytes_count ):
                    return

                byte_sent, bit_buffer, bit_pos = bit_writer( self.write, bit_buffer, bit_pos, (cur_sync_pattern >> (15-cur_sync_bit)) & 0x1 )
                bytes_sent += byte_sent

                cur_sync_bit = cur_sync_bit + 1

            # Generate message data
            is_fragmented_packet = random.randint( 0, 8 ) == 0
            #is_fragmented_packet = False
            is_large_checksum_packet = random.randint( 0, 1 ) == 0

            packet_hdr = 0
            cur_packet_sequence_number = 0
            cur_packet_fragment_number = 0

            # Set large checksum bit
            if is_large_checksum_packet:
                packet_hdr = packet_hdr | self.PACKET_LARGE_CHECKSUM_BIT

            # Set header identifier
            packet_hdr = packet_hdr | self.PACKET_HEADER_IDENTIFIER_VALUE

            # Handle fragmented packets
            if is_fragmented_packet:
                # Setup packet_len
                packet_len = random.randint(3,250)

                # Is this a new fragmented packet???
                if current_fragment_number == 0:
                    total_fragments = random.randint( 1, 15 )

                # Turn on fragment bit
                packet_hdr = packet_hdr | self.PACKET_FRAGMENTED_BIT

                # Remember packet sequence number
                cur_packet_sequence_number = packet_sequence_number

                # Remember packet fragment number
                cur_packet_fragment_number = current_fragment_number

                # Get packet sequence data
                packet_fragment_data = (cur_packet_sequence_number << 4) + cur_packet_fragment_number

                # Handle last fragment
                if ( current_fragment_number+1 == total_fragments ):
                    current_fragment_number = 0
                    packet_sequence_number += 1
                    packet_hdr = packet_hdr | self.PACKET_LAST_FRAGMENT_BIT

                    packet_fragments_complete = True
                else:
                    current_fragment_number += 1
                    packet_fragments_complete = False


                # Calculate packet header parity bit -- set and then write
                cur_hdr_bit = 0
                hdr_bit_count = 0
                while cur_hdr_bit < 8:
                    if ( cur_hdr_bit != self.PACKET_PARITY_BIT_POS ):
                        hdr_bit_count += ((packet_hdr & (1<<cur_hdr_bit)) >> cur_hdr_bit) & 0x1
                    cur_hdr_bit += 1

                packet_hdr = packet_hdr | ((hdr_bit_count % 2) << self.PACKET_PARITY_BIT_POS)

                # Write out packet headers
                cur_hdr_bit = 0
                while cur_hdr_bit < 8:
                    if ( bytes_sent >= self.bytes_count ):
                        return

                    byte_sent, bit_buffer, bit_pos = bit_writer( self.write, bit_buffer, bit_pos, (packet_hdr >> (7-cur_hdr_bit)) & 0x1 )
                    bytes_sent += byte_sent

                    cur_hdr_bit = cur_hdr_bit + 1

                # Write out packet length
                cur_hdr_bit = 0
                while cur_hdr_bit < 8:
                    if ( bytes_sent >= self.bytes_count ):
                        return

                    byte_sent, bit_buffer, bit_pos = bit_writer( self.write, bit_buffer, bit_pos, (packet_len >> (7-cur_hdr_bit)) & 0x1 )
                    bytes_sent += byte_sent

                    cur_hdr_bit = cur_hdr_bit + 1

                # Start data off data with fragment header
                cur_packet_data = pack( '<H', packet_fragment_data )
                cur_packet_data_pos = 2

                # Write out data fragment header
                cur_data_bit = 0
                packet_data_byte = unpack('B', cur_packet_data[0])[0]
                packet_data_byte1 = packet_data_byte
                while cur_data_bit < 8:
                    if ( bytes_sent >= self.bytes_count ):
                        return

                    byte_sent, bit_buffer, bit_pos = bit_writer( self.write, bit_buffer, bit_pos, (packet_data_byte >> (7-cur_data_bit)) & 0x1 )
                    bytes_sent += byte_sent

                    cur_data_bit = cur_data_bit + 1

                cur_data_bit = 0
                packet_data_byte = unpack('B', cur_packet_data[1])[0]
                packet_data_byte2 = packet_data_byte
                while cur_data_bit < 8:
                    if ( bytes_sent >= self.bytes_count ):
                        return

                    byte_sent, bit_buffer, bit_pos = bit_writer( self.write, bit_buffer, bit_pos, (packet_data_byte >> (7-cur_data_bit)) & 0x1 )
                    bytes_sent += byte_sent

                    cur_data_bit = cur_data_bit + 1

                #print "Writing fragmented message: seq=%d frag=%d hdr=%d len=%d (%d,%d)" % (cur_packet_sequence_number, cur_packet_fragment_number, packet_hdr, packet_len, packet_data_byte1, packet_data_byte2 )

            else:
                # Clear packet data
                cur_packet_data = ''
                cur_packet_data_pos = 0

                # Setup packet_len
                packet_len = random.randint(1,255)

                # Calculate packet header parity bit -- set and then write
                cur_hdr_bit = 0
                hdr_bit_count = 0
                while cur_hdr_bit < 8:
                    if ( cur_hdr_bit != self.PACKET_PARITY_BIT_POS ):
                        hdr_bit_count += ((packet_hdr & (1<<cur_hdr_bit)) >> cur_hdr_bit) & 0x1
                    cur_hdr_bit += 1

                packet_hdr = packet_hdr | ((hdr_bit_count % 2) << self.PACKET_PARITY_BIT_POS)

                # Write out packet header (non-fragmented)
                cur_hdr_bit = 0
                while cur_hdr_bit < 8:
                    if ( bytes_sent >= self.bytes_count ):
                        return

                    byte_sent, bit_buffer, bit_pos = bit_writer( self.write, bit_buffer, bit_pos, (packet_hdr >> (7-cur_hdr_bit)) & 0x1 )
                    bytes_sent += byte_sent

                    cur_hdr_bit = cur_hdr_bit + 1

                # Write out packet length
                cur_hdr_bit = 0
                while cur_hdr_bit < 8:
                    if ( bytes_sent >= self.bytes_count ):
                        return

                    byte_sent, bit_buffer, bit_pos = bit_writer( self.write, bit_buffer, bit_pos, (packet_len >> (7-cur_hdr_bit)) & 0x1 )
                    bytes_sent += byte_sent

                    cur_hdr_bit = cur_hdr_bit + 1

            # Now write out packet data!
            while ( cur_packet_data_pos < packet_len ):
                # Get random packet data
                packet_data_byte = random.randint( 0, 255 )

                # Remember packet data -- we will render this
                cur_packet_data += pack( 'B', packet_data_byte )

                # Write out packet data byte
                cur_data_bit = 0
                while cur_data_bit < 8:
                    if ( bytes_sent >= self.bytes_count ):
                        return

                    byte_sent, bit_buffer, bit_pos = bit_writer( self.write, bit_buffer, bit_pos, (packet_data_byte >> (7-cur_data_bit)) & 0x1 )
                    bytes_sent += byte_sent

                    cur_data_bit = cur_data_bit + 1

                cur_packet_data_pos = cur_packet_data_pos + 1

            # Randomly send a corrupted checksum
            do_bad_checksum = random.randint( 0, 20 ) == 0

            # Do checksum
            if is_large_checksum_packet:
                checksum32 = 0
                cur_data_pos = 0
                while cur_data_pos < packet_len:
                    # Update checksum
                    checksum32 += unpack( 'B', cur_packet_data[cur_data_pos] )[0]

                    # Advance
                    cur_data_pos += 1

                # Make sure it is a 32-bit number
                checksum32 = checksum32 & 0xFFFFFFFF

                # Do a bad checksum
                if ( do_bad_checksum ):
                    old_checksum32 = checksum32
                    while old_checksum32 == checksum32:
                        checksum32 = checksum32 ^ random.randint( 0, (1<<32)-1 )

                # Write out checksum32
                cur_checksum_bit = 0
                while cur_checksum_bit < 32:
                    if ( bytes_sent >= self.bytes_count ):
                        return

                    byte_sent, bit_buffer, bit_pos = bit_writer( self.write, bit_buffer, bit_pos, (checksum32 >> (31-cur_checksum_bit)) & 0x1 )
                    bytes_sent += byte_sent

                    cur_checksum_bit = cur_checksum_bit + 1

            else:
                checksum16 = 0
                cur_data_pos = 0
                while cur_data_pos < packet_len:
                    # Update checksum
                    checksum16 += unpack( 'B', cur_packet_data[cur_data_pos] )[0]

                    # Advance
                    cur_data_pos += 1

                # Make sure it is 16-bit number
                checksum16 = checksum16 & 0xFFFF

                # Do a bad checksum
                if ( do_bad_checksum ):
                    old_checksum16 = checksum16
                    while old_checksum16 == checksum16:
                        checksum16 = checksum16 ^ random.randint( 0, (1<<16)-1 )

                # Write out checksum16
                cur_checksum_bit = 0
                while cur_checksum_bit < 16:
                    if ( bytes_sent >= self.bytes_count ):
                        return

                    byte_sent, bit_buffer, bit_pos = bit_writer( self.write, bit_buffer, bit_pos, (checksum16 >> (15-cur_checksum_bit)) & 0x1 )
                    bytes_sent += byte_sent

                    cur_checksum_bit = cur_checksum_bit + 1

            # Check overrun
            if ( bytes_sent >= self.bytes_count ):
                return

            # Flush packet bits (since we can only write 1 byte at a time)
            byte_sent, bit_buffer, bit_pos = bit_flush( self.write, bit_buffer, bit_pos )
            bytes_sent += byte_sent


            # Lastly render the packet!
            if ( do_bad_checksum == False ):
                # Now render the packet
                self.render_packet( packet_hdr, cur_packet_sequence_number, cur_packet_fragment_number, cur_packet_data, packet_len )

            packet_cur += 1

    def menu(self):

        pass

    def exit(self):
        # Exits
        pass
