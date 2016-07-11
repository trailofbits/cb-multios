#!/usr/bin/env python

import struct
import string
import random
from generator.actions import Actions


class Packet():

  def generate(self):
 
    # Generate Physical Data
    self.phy_time_received = random.randint(1420088400, 1470024000)
    self.phy_time_sent = random.randint(1420088400, 1470024000)
    self.phy_type = random.randint(1, 3)
    if (self.phy_type == 1):
      # Wire type
      self.phy_wirespeed = random.randint(0,4)
    elif (self.phy_type == 2):
      # Radio type
      self.phy_source_addr = random.randint(0, 0xffffffff)
      self.phy_dest_addr = random.randint(0, 0xffffffff)
      self.phy_transmit_strength = random.randint(1,100)
      self.phy_receive_strength = random.randint(1,100)
      self.phy_frequency = random.randint(2400, 6000)
      self.phy_snr = random.randint(0, 0xffffffff)
      

    # Generate Transport Data
    self.tp_type = random.randint(1,2)
    if (self.tp_type == 1):
      #stream
      self.tp_stream = random.randint(0, 0xffffffff)
      self.tp_sequence = random.randint(0, 0xffffffff)
      self.tp_window = random.randint(0, 0xffff)
      self.tp_ack = random.randint(0, 0xffffffff)


    # Generate Network Data
    self.network_type = random.randint(1,3)
    if (self.network_type == 1):
      #endpoint
      self.network_src_addr = random.randint(1,0xffffffff)
      self.network_dst_addr = random.randint(1,0xffffffff)

    elif (self.network_type == 2):
      #broadcast
      self.network_src_addr = random.randint(1,0xffffffff)
    else:
      #debug
      self.network_debug_type = random.randint(1, 6)
      self.network_src_addr = random.randint(1,0xffffffff)
      self.network_dst_addr = random.randint(1,0xffffffff)
      self.network_hop_count = random.randint(1,0xffff)
      self.network_timestamp = random.randint(1420088400, 1470024000)



    # Generate Application Data and Make Layer
    application_data = []
    self.app_type = random.randint(1, 5)
    if (self.app_type == 1):
      # Audio Stream
      self.app_encoding = random.randint(1,10)
      self.app_bit_rate = random.choice([8, 16, 24, 32, 40, 48])
      self.app_length = random.randint(12, 1024) 
      self.app_content = ''.join(chr(random.randint(0,255)) for _ in range(self.app_length - 12))
      application_data.append(struct.pack("<IHHI", self.app_length, self.app_type, self.app_encoding, self.app_bit_rate))
      if (self.app_content):
        application_data.append(self.app_content)

    elif (self.app_type == 2):
      # Video stream
      self.app_encoding = random.randint(1,14)
      self.app_resolution_x = random.randint(1,4096)
      self.app_resolution_y = random.randint(1,2160)
      self.app_num_options = random.randint(0,5)

      app_options = []
      self.app_options = []
      for i in range(self.app_num_options):
        option = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(5,100)))
        app_options.append(struct.pack("<B", len(option)))
        app_options.append(option)
        self.app_options.append(option)
      video_length = random.randint(0, 1024)
      self.app_content = ''.join(chr(random.randint(0,255)) for _ in range(video_length))
      self.app_length = len(''.join(app_options)) + 4 + 2 + 2 + 2 + 2 + 2 + video_length
      application_data.append(struct.pack("<IHHHHH", self.app_length, self.app_type, self.app_encoding, self.app_resolution_x, self.app_resolution_y, self.app_num_options))
      if app_options:
        application_data.extend(app_options)
      if (self.app_content):
        application_data.append(self.app_content)

    elif (self.app_type == 3):
      # File
      self.app_filename = ''.join(random.choice(string.ascii_letters) for _ in range(32))
      self.app_filetype = ''.join(random.choice(string.ascii_letters) for _ in range(32))
      file_len = random.randint(0, 1024)
      self.app_content = ''.join(chr(random.randint(0,255)) for _ in range(file_len))
      self.app_length = 4 + 2 + 32 + 32 + file_len
      application_data.append(struct.pack("<IH", self.app_length, self.app_type))
      application_data.append(self.app_filename)
      application_data.append(self.app_filetype)
      if (self.app_content):
        application_data.append(self.app_content)

    elif (self.app_type == 4):
      # Email
      email_len = 0
      email = []
      self.app_from = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(0,255)))
      self.app_to = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(0,255)))
      self.app_subject = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(0,255)))
      content_len = random.randint(0, 1024)
      self.app_content = ''.join(random.choice(string.ascii_letters) for _ in range(content_len))

      self.app_length = 4 + 2 + len(self.app_from) + len(self.app_to) + len(self.app_subject) + content_len
      application_data.append(struct.pack("<IH", self.app_length, self.app_type))
      application_data.append(struct.pack("B", len(self.app_from)))
      application_data.append(self.app_from)
      application_data.append(struct.pack("B", len(self.app_to)))
      application_data.append(self.app_to)
      application_data.append(struct.pack("B", len(self.app_subject)))
      application_data.append(self.app_subject)
      if (self.app_content):
        application_data.append(self.app_content)

    elif (self.app_type == 5):
      # Webpage
      self.app_url = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(0,256)))
      self.app_headers = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(0,1024)))
      self.app_content = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(0, 1024)))
      self.app_length = 4 + 2 + 2 + len(self.app_url) + 2 + len(self.app_headers) + 2 + len(self.app_content)

      application_data.append(struct.pack("<IH", self.app_length, self.app_type))
      application_data.append(struct.pack("<H", len(self.app_url)))
      if (self.app_url):
        application_data.append(self.app_url)
      application_data.append(struct.pack("<H", len(self.app_headers)))
      if (self.app_headers):
        application_data.append(self.app_headers)
      application_data.append(struct.pack("<H", len(self.app_content)))
      if (self.app_content):
        application_data.append(self.app_content)

   
    # Make Network Layer
    network_data = []
    if (self.network_type == 1):
      #endpoint
      self.network_length = self.app_length + 4 + 2 + 4 + 4
      network_data.append(struct.pack("<IHII", self.network_length, self.network_type, self.network_src_addr, self.network_dst_addr))
    elif (self.network_type == 2):
      #broadcast
      self.network_length = self.app_length + 4 + 2 + 4
      network_data.append(struct.pack("<IHI", self.network_length, self.network_type, self.network_src_addr))
    else:
      #debug
      self.network_length = self.app_length + 4 + 2 + 2 + 4 + 4 + 2 + 4
      network_data.append(struct.pack("<IHH", self.network_length, self.network_type, self.network_debug_type))
      network_data.append(struct.pack("<IIHI", self.network_src_addr, self.network_dst_addr, self.network_hop_count, self.network_timestamp))

    # Make Transport Layer
    transport_data = []
    if (self.tp_type == 1):
      #stream
      self.tp_length = self.network_length + 4 + 4 + 4 + 2 + 4 + 4
      transport_data.append(struct.pack("<III", self.tp_type, self.tp_stream, self.tp_sequence))
      transport_data.append(struct.pack("<HII",  self.tp_window, self.tp_ack, self.tp_length))
    else:
      #dgram
      self.tp_length = self.network_length + 4 + 4
      transport_data.append(struct.pack("<II", self.tp_type, self.tp_length))

    # Make Physical Layer
    phy_data = []
    if (self.phy_type == 1):
      # Wire
      self.phy_checksum = 0
      for each in ''.join(transport_data + network_data + application_data):
        self.phy_checksum = (self.phy_checksum + ord(each)) & 0xffffffff
      self.phy_length = self.tp_length + 4 + 4 + 4 + 2 + 2 + 4
      
      phy_data.append(struct.pack("<IIIH", self.phy_time_received, self.phy_time_sent, self.phy_length, self.phy_type))
      phy_data.append(struct.pack("<HI", self.phy_wirespeed, self.phy_checksum))
    elif (self.phy_type == 2):
      # Radio
      # Calculate ECC 
      self.phy_length = self.tp_length + 4 + 4 + 4 + 2 + 4 + 4 + 4 + 4 + 4 + 4 + 4
      phy_data.append(struct.pack("<IIIH", self.phy_time_received, self.phy_time_sent, self.phy_length, self.phy_type))
      phy_data.append(struct.pack("<IIIIII", self.phy_source_addr, self.phy_dest_addr, self.phy_transmit_strength, self.phy_receive_strength, self.phy_frequency, self.phy_snr))
      self.phy_ecc = 0
      phy_data.append(struct.pack("<I", self.phy_ecc))
    else:
      # Raw
      self.phy_length = self.tp_length + 4 + 4 + 4 + 2
      phy_data.append(struct.pack("<IIIH", self.phy_time_received, self.phy_time_sent, self.phy_length, self.phy_type))
    self.packet_bytes = ''.join(phy_data + transport_data + network_data + application_data)
  
  

  def get_bytes(self):
    bytes = []
    bytes.append(struct.pack("<H", len(self.packet_bytes)))
    bytes.append(self.packet_bytes)
    return ''.join(bytes)

class Filter():

  def __init__(self):
    self.filterdata = ""
    self.include = True

  def generate_filter(self, include=True):
    p = Packet()
    p.generate()
    self.filterdata = p.get_bytes()[2:]
    filtermask = []
    for each in self.filterdata:
      if (random.randint(0, 10) == 10):
        filtermask.append(struct.pack("<B", random.randint(0,255)))
      else:
        filtermask.append("\x00")
    self.filtermask = ''.join(filtermask)
    self.include = include
    
  def get_bytes(self):
    output = []
    output.append(struct.pack("<H", len(self.filterdata)))
    #include or exclude
    if self.include:
      output.append('\x01')
    else:
      output.append('\x02')

    output.append(self.filtermask)
    output.append(self.filterdata)
    return ''.join(output)

  def match_packet(self, packet):
    if (len(self.filtermask) > packet.phy_length):
      return False
    packet_bytes = packet.get_bytes()[2:]
    for i in range(len(self.filtermask)):
      p_i = struct.unpack("B", packet_bytes[i])[0]
      m_i = struct.unpack("B", self.filtermask[i])[0]
      f_i = struct.unpack("B", self.filterdata[i])[0]
      if ((p_i & m_i) != (f_i & m_i)):
        return False
    return True

class OptionHeader():

  def __init__(self):
    self.type = 0
    self.header = ""
    self.display_string = ""

  def generate(self):
    self.type = random.randint(1,7)
    if self.type == 1:
      #string
      self.header = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1,255)))
      self.display_string = self.header
    elif self.type == 2:
      #location
      if random.randint(0,1):
        #gps coordinates
        lat = str(random.uniform(-90, 90))
        lon = str(random.uniform(-180, 180))
        self.header = lat + '\x00' + lon
        self.display_string = "GPS Coordinates: %s Latitude, %s Longitude" % (lat, lon)
      else:
        #address string
        self.header = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1,35)))
        self.display_string = "Address: " + self.header
    elif self.type == 3:
      #authority
      i = random.randint(0,5)
      self.header = str(i)
      names = ["Self", "Law Enforcement", "University", "Employer", "Network Provider"]
      if i != 5:
        self.display_string = "Capturing Authority: " + names[i]
      else:
        self.display_string = "Capturing Authority Unknown"

    elif self.type == 4:
      #date
      self.header = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1,35)))
      self.display_string = "Capture Date: " + self.header
    elif self.type == 5:
      #sharing
      self.header = str(random.randint(0,1))
      if (self.header == '1'):
        self.display_string = "Sharing Allowed: True"
      else:
        self.display_string = "Sharing Allowed: False"
    elif self.type == 6:
      #modified
      self.header = str(random.randint(0,1))
      if (self.header == '1'):
        self.display_string = "This content has been modified"
      else:
        self.display_string = "This content has not been modified from the original"
    elif self.type == 7:
      #device
      self.header = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1,35)))
      self.display_string = "Capturing Device: " + self.header

  def get_bytes(self):
    bytes = []
    bytes.append(struct.pack("<B", self.type))
    if (len(self.header) >= 256):
      self.header = self.header[0:255]
    bytes.append(struct.pack("<B", len(self.header)))
    bytes.append(self.header)
    return ''.join(bytes)


class PacketParserPollGenerator(Actions):

  DISPLAY_PHYSICAL    = 0x0001
  DISPLAY_TRANSPORT     = 0x0002
  DISPLAY_NETWORK     = 0x0004
  DISPLAY_APPLICATION = 0x0008
  DISPLAY_STATS       = 0x0010 
  DISPLAY_CONTENT     = 0x0020

  MODE_FILE   = '\x01'
  MODE_STREAM = '\x02'

  def start(self):
    return

  def reset_values(self):
    self.initial_packet = []
    self.packet_filters = []
    self.option_headers = []
    self.display_flags = 0
    self.packets = []
    self.start_time = 0
    self.end_time = 0
    self.largest_packet = 0
    self.smallest_packet = 0
    self.num_malformed = 0
    self.num_packets_shown = 0

  def generate_initial_packet(self, mode, num_filters):
    packet = []
    packet.append("\x5A\xA5\x5A\xA5")
    packet.append(mode)
    display_flags = 0
    if self.chance(0.5):
      display_flags |= self.DISPLAY_PHYSICAL
    if self.chance(0.5):
      display_flags |= self.DISPLAY_TRANSPORT
    if self.chance(0.5):
      display_flags |= self.DISPLAY_NETWORK
    if self.chance(0.5):
      display_flags |= self.DISPLAY_APPLICATION
    if self.chance(0.9):
      display_flags |= self.DISPLAY_STATS
    if self.chance(0.2):
      display_flags |= self.DISPLAY_CONTENT
    self.display_flags = display_flags
    packet.append(struct.pack("<H", display_flags))
    packet.append(struct.pack("<B", num_filters))
    return ''.join(packet)


  def CheckAllFilters(self, packet):
    pos_match = 0
    neg_match = 0
    for f in self.packet_filters:
      if (f.match_packet(packet)):
        if f.include:
          pos_match += 1
        else:
          neg_match += 1
    return (pos_match, neg_match)


  def ShowPacket(self, packet):
    #check all filters
    (num_pos, num_neg) = self.CheckAllFilters(packet)
    if (num_neg > 0):
      return False
    if ((self.num_positive_filters > 0) and (num_pos == 0)):
      return False
    else:
      return True

  def ConditionalRead(self, flag, string):
    if (self.display_flags & flag):
      self.read(delim='\n', expect=string)

  def HexDump(self, data):
    line = []
    for each in data:
      line.append(each)
      if (len(line) == 16):
        self.read(delim='\n', expect=''.join('{:02X} '.format(ord(b)) for b in line))
        line = []
    if len(line) != 0:
      self.read(delim='\n', expect=''.join('{:02X} '.format(ord(b)) for b in line))
        
  def AnalyzePacket(self, packet):
    if (not self.ShowPacket(packet)):
      self.read(delim='\n', expect="skip")
      return

    self.num_packets_shown += 1
    # Physical Layer
    self.ConditionalRead(self.DISPLAY_PHYSICAL, "Physical Length:%d" % packet.phy_length)
    type_names = ["Wire", "Radio", "Raw"];
    self.ConditionalRead(self.DISPLAY_PHYSICAL, "Physical Type: %s" % type_names[packet.phy_type - 1])
    if (packet.phy_type == 1):
      # Wire
      if ((packet.phy_wirespeed == 0) or (packet.phy_wirespeed - 1 >= 4)):
        self.ConditionalRead(self.DISPLAY_PHYSICAL, "Invalid Wire speed")
        return
      else:
        physical_wire_speeds = ["1,000", "10,000", "100,000", "1,000,000"]
        self.ConditionalRead(self.DISPLAY_PHYSICAL, "Wire Speed: %s" % physical_wire_speeds[packet.phy_wirespeed - 1])
    elif (packet.phy_type == 2):
      # Radio
      self.ConditionalRead(self.DISPLAY_PHYSICAL, "Source Address: 0x%08X" % packet.phy_source_addr)
      self.ConditionalRead(self.DISPLAY_PHYSICAL, "Destination Address: 0x%08X" % packet.phy_dest_addr)
      self.ConditionalRead(self.DISPLAY_PHYSICAL, "Transmit strength: %u" % packet.phy_transmit_strength)
      self.ConditionalRead(self.DISPLAY_PHYSICAL, "Receive strength: %u" % packet.phy_receive_strength)
      self.ConditionalRead(self.DISPLAY_PHYSICAL, "Frequency: %d" % packet.phy_frequency)
      self.ConditionalRead(self.DISPLAY_PHYSICAL, "SNR: %u" % packet.phy_snr)
    elif (packet.phy_type == 3):
      # Raw
      data = packet.get_bytes()[16:]
      if (self.display_flags & self.DISPLAY_PHYSICAL):
        self.HexDump(data)
      return
    else:
      self.ConditionalRead(self.DISPLAY_PHYSICAL, "Invalid Physical Type")
      return

    # Transport Layer
    if (packet.tp_type == 1):
      self.ConditionalRead(self.DISPLAY_TRANSPORT, "Transport Type: STREAM")
      self.ConditionalRead(self.DISPLAY_TRANSPORT, "Stream number: %u" % packet.tp_stream)
      self.ConditionalRead(self.DISPLAY_TRANSPORT, "Sequence number: %u" % packet.tp_sequence)
      self.ConditionalRead(self.DISPLAY_TRANSPORT, "Window: %d" % packet.tp_window)
      self.ConditionalRead(self.DISPLAY_TRANSPORT, "Acknowledgment: 0x%08X" % packet.tp_ack)
      self.ConditionalRead(self.DISPLAY_TRANSPORT, "Length: %d" % packet.tp_length)
    elif (packet.tp_type == 2):
      self.ConditionalRead(self.DISPLAY_TRANSPORT, "Transport Type: MESSAGE")
      self.ConditionalRead(self.DISPLAY_TRANSPORT, "Length: %d" % packet.tp_length)
    else:
      self.ConditionalRead(self.DISPLAY_TRANSPORT, "Invalid Transport Type")
      return


    # Network Layer
    if (packet.network_type == 1):
      self.ConditionalRead(self.DISPLAY_NETWORK, "Network type: Endpoint")
      self.ConditionalRead(self.DISPLAY_NETWORK, "Source Address: 0x%08X" % packet.network_src_addr)
      self.ConditionalRead(self.DISPLAY_NETWORK, "Destination Address: 0x%08X" % packet.network_dst_addr)
    elif (packet.network_type == 2):
      self.ConditionalRead(self.DISPLAY_NETWORK, "Network type: Broadcast")
      self.ConditionalRead(self.DISPLAY_NETWORK, "Source Address: 0x%08X" % packet.network_src_addr)
    elif (packet.network_type == 3):
      self.ConditionalRead(self.DISPLAY_NETWORK, "Network type: Debug")
      debug_type_names = ["PING", "PONG", "TRACEROUTE", "QUERY", "CONNECT", "REPLY"]
      self.ConditionalRead(self.DISPLAY_NETWORK, "Network debug type: %s" % debug_type_names[packet.network_debug_type - 1])
      self.ConditionalRead(self.DISPLAY_NETWORK, "Source Address: 0x%08X" % packet.network_src_addr)
      self.ConditionalRead(self.DISPLAY_NETWORK, "Destination Address: 0x%08X" % packet.network_dst_addr)
      self.ConditionalRead(self.DISPLAY_NETWORK, "Hop Count: %d" % packet.network_hop_count)
      self.ConditionalRead(self.DISPLAY_NETWORK, "Timestamp: %d" % packet.network_timestamp)

    # Application Layer
    if (packet.app_type == 1):
      self.ConditionalRead(self.DISPLAY_APPLICATION, "Application type: Audio Stream")
      self.ConditionalRead(self.DISPLAY_APPLICATION, "Encoding type: %d" % packet.app_encoding)
      self.ConditionalRead(self.DISPLAY_APPLICATION, "Bit rate: %d" % packet.app_bit_rate)
    elif (packet.app_type == 2):
      self.ConditionalRead(self.DISPLAY_APPLICATION, "Application type: Video Stream")
      self.ConditionalRead(self.DISPLAY_APPLICATION, "X Resolution: %d" % packet.app_resolution_x)
      self.ConditionalRead(self.DISPLAY_APPLICATION, "Y Resolution: %d" % packet.app_resolution_y)
      self.ConditionalRead(self.DISPLAY_APPLICATION, "Video Option Headers: ")
      for each in packet.app_options:
        self.ConditionalRead(self.DISPLAY_APPLICATION, "\t%s" % each)

    elif (packet.app_type == 3):
      self.ConditionalRead(self.DISPLAY_APPLICATION, "Application type: File")
      self.ConditionalRead(self.DISPLAY_APPLICATION, "Filename: %s" % packet.app_filename)
      self.ConditionalRead(self.DISPLAY_APPLICATION, "File type: %s" % packet.app_filetype)

    elif (packet.app_type == 4):
      self.ConditionalRead(self.DISPLAY_APPLICATION, "Application type: Email")
      self.ConditionalRead(self.DISPLAY_APPLICATION, "From: %s" % packet.app_from)
      self.ConditionalRead(self.DISPLAY_APPLICATION, "To: %s" % packet.app_to)
      self.ConditionalRead(self.DISPLAY_APPLICATION, "Subject: %s" % packet.app_subject)

    elif (packet.app_type == 5):
      self.ConditionalRead(self.DISPLAY_APPLICATION, "Application type: Webpage")
      self.ConditionalRead(self.DISPLAY_APPLICATION, "URL: %s" % packet.app_url)
      self.ConditionalRead(self.DISPLAY_APPLICATION, "Headers: %s" % packet.app_headers)
      

    if (self.display_flags & self.DISPLAY_CONTENT):
      if (packet.app_content):
        self.HexDump(packet.app_content)
      self.read(delim='\n')

     

  def GetStatistics(self):
    if (self.display_flags & self.DISPLAY_STATS):
      self.read(delim='\n', expect="Final Statistics:")
      self.read(delim='\n', expect="\tTotal Packets: %d" % self.num_packets)
      self.read(delim='\n', expect="\tStart Time: 0x%08X" % self.start_time)
      self.read(delim='\n', expect="\tEnd Time: 0x%08X" % self.end_time)
      self.read(delim='\n', expect="\tLargest Packet: %d" % self.largest_packet)
      self.read(delim='\n', expect="\tSmallest Packet: %d" % self.smallest_packet)
      self.read(delim='\n', expect="\tNumber of malformed packets: %d" % self.num_malformed)
      self.read(delim='\n', expect="\tNumber of packets shown %d" % self.num_packets_shown)
 
      self.read(delim='\n', expect="Option Headers:")
      for o in self.option_headers:
        self.read(delim='\n', expect=o.display_string)
      self.read(delim='\n')


  def send_file(self):
    self.reset_values()
    if (random.randint(0,10)==10):
      self.num_filters = random.randint(1,4)
    else:
      self.num_filters = 0
    initial_packet = self.generate_initial_packet(mode=self.MODE_FILE, num_filters=self.num_filters)

    filter_bytes = []
    self.num_positive_filters = 0
    for i in range(self.num_filters):
      f = Filter()
      if (self.chance(0.5)):
        f.generate_filter(True)
        self.num_positive_filters += 1
      else:
        f.generate_filter(False)
      self.packet_filters.append(f)
      filter_bytes.append(f.get_bytes())

    #file header
    file_header = []
    file_header.append('\xA9\xDC\xAF\xDC')
    self.start_time = random.randint(1420088400, 1470024000)
    self.end_time = random.randint(1420088400, 1470024000)
    file_header.append(struct.pack("<I", self.start_time))
    file_header.append(struct.pack("<I", self.end_time))
    self.num_packets = random.randint(1,50)
    file_header.append(struct.pack("<I", self.num_packets))
    self.num_option_headers = random.randint(0, 50)
    file_header.append(struct.pack("<B", self.num_option_headers))

    option_bytes = []
    for i in range(self.num_option_headers):
      o = OptionHeader()
      o.generate()
      self.option_headers.append(o)
      option_bytes.append(o.get_bytes())

    for i in range(self.num_packets):
      p = Packet()
      p.generate()
      self.packets.append(p)

    #transmit 
    self.write(''.join(initial_packet))
    if (filter_bytes):
      self.write(''.join(filter_bytes))
    self.write(''.join(file_header))
    if (option_bytes):
      self.write(''.join(option_bytes))
    for i in range(self.num_packets):
      p = self.packets[i]
      self.write(struct.pack("<I", random.randint(1420088400, 1470024000)))
      self.write(p.get_bytes())

    for i in range(self.num_packets):
      p = self.packets[i]
      self.AnalyzePacket(p)

    self.GetStatistics()

    return

  def send_stream(self):
    self.reset_values()
    if (random.randint(0,10)==10):
      self.num_filters = random.randint(1,4)
    else:
      self.num_filters = 0
    
    initial_packet = self.generate_initial_packet(mode=self.MODE_STREAM, num_filters=self.num_filters)

    filter_bytes = []
    self.num_positive_filters = 0
    for i in range(self.num_filters):
      f = Filter()
      if (self.chance(0.5)):
        f.generate_filter(True)
        self.num_positive_filters += 1
      else:
        f.generate_filter(False)
      self.packet_filters.append(f)
      filter_bytes.append(f.get_bytes())

    self.num_packets = random.randint(1,50)
    for i in range(self.num_packets):
      p = Packet()
      p.generate()
      self.packets.append(p)

    self.write(''.join(initial_packet))
    if (filter_bytes):
      self.write(''.join(filter_bytes))

    for i in range(self.num_packets):
      p = self.packets[i]
      self.write(p.get_bytes())
      self.AnalyzePacket(p)

    self.write("\x00\x00")

    self.GetStatistics()
    return

  def final(self):
    self.read(delim='\n', expect="Goodbye.")



