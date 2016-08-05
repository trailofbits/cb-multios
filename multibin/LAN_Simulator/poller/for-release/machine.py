#!/usr/bin/env python

from generator.actions import Actions
from struct import *
from random import *
import numpy as np
import ctypes as ct

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

class MyClass(Actions):
    L2_OUR_ADDR = 0xabcd
    L3_OUR_ADDR = 0x0a010102
    L2_ROUTER_ADDR = 0x0001
    L3_ROUTER_ADDR = 0x0a010101
    L2_CB3_ADDR = 0xaaaa
    L3_CB3_ADDR = 0x0a010202

    def random_string(self, min_length, max_length):
        return ''.join(chr(randint(1,255)) for _ in range(randint(min_length, max_length)))

    def CalcChecksum(self, Data):
        Sum = 0
        for x in Data:
            Sum += ord(x)
        return Sum

    L3_HEADER_TYPE = 0x1
    L2_ADJACENCY_DISCOVERY_TYPE = 0x2
    L2_ADJACENCY_RESPONSE_TYPE = 0x3
    L2_HEADER_LEN = 7
    L2_FOOTER_LEN = 4
    L2_BROADCAST_ADDR = 0xffff
    def L2Encap(self, Packet, Dst, Src, NxtHdr, Vlan):
        Frame =  pack("<H", Dst)
        Frame += pack("<H", Src)
        Frame += pack("B", len(Packet)+self.L2_FOOTER_LEN)
        Frame += pack("B", NxtHdr)
        Frame += pack("B", Vlan)
        Frame += Packet

        Frame += pack("<L", self.CalcChecksum(Frame))

        return Frame

    def L3Encap(self, Data, Dst, Src, NxtHdr):
        Offset = 0
        Flags = 0
        Packet =  pack("<L", Dst)
        Packet += pack("<L", Src)
        Packet += pack("B", len(Data))
#        Packet += pack("<H", len(Data))
#        Packet += pack("B", Offset)
#        Packet += pack("B", Flags)
        Packet += pack("B", NxtHdr)
        Packet += Data

        return Packet

    L4_HEADER_TYPE = 0x01
    def L4Encap(self, Data, Dst, Src):
        Segment =  pack("B", Dst)
        Segment += pack("B", Src)
        Segment += pack("B", len(Data))
        Segment += Data

        return Segment

    def BuildL2AdjacencyPkt(self, L3Addr, L2Addr):
        L2AdjPkt = pack("<L", L3Addr)
        L2AdjPkt += pack("<H", L2Addr)
        L2AdjPkt += pack("B", 0)
        L2AdjPkt += pack("B", 0)

        return L2AdjPkt

    def DoWeExpectADP(self):
        # have we been ADP'd by the router yet?
	self.ADP_Age -= 1;
	if self.ADP_Age <= 0:
            # expect an ADP DISCOVERY packet
            L2AdjPkt = self.BuildL2AdjacencyPkt(self.L3_OUR_ADDR, 0x0000)
            Frame = self.L2Encap(L2AdjPkt, self.L2_BROADCAST_ADDR, self.L2_ROUTER_ADDR, self.L2_ADJACENCY_DISCOVERY_TYPE, 0);
            self.read(length=len(Frame), expect=Frame)

            # send back an ADP RESPONSE packet
            L2AdjPkt = self.BuildL2AdjacencyPkt(self.L3_OUR_ADDR, self.L2_OUR_ADDR)
            Frame = self.L2Encap(L2AdjPkt, self.L2_ROUTER_ADDR, self.L2_OUR_ADDR, self.L2_ADJACENCY_RESPONSE_TYPE, 0);
            self.write(Frame)

            # reset the Age counter
            self.ADP_Age = 7

    def ResolveL2Adjacency(self):
        self.comment("ResolveL2Adjacency Test")
        # send the Adjacency discovery frame
        L2AdjPkt = self.BuildL2AdjacencyPkt(self.L3_ROUTER_ADDR, 0x0000)
        Frame = self.L2Encap(L2AdjPkt, self.L2_BROADCAST_ADDR, self.L2_OUR_ADDR, self.L2_ADJACENCY_DISCOVERY_TYPE, 0);
        self.write(Frame)

        # check the expected response
        L2AdjPkt = self.BuildL2AdjacencyPkt(self.L3_ROUTER_ADDR, self.L2_ROUTER_ADDR)
        Frame = self.L2Encap(L2AdjPkt, self.L2_OUR_ADDR, self.L2_ROUTER_ADDR, self.L2_ADJACENCY_RESPONSE_TYPE, 0);
        self.read(length=len(Frame), expect=Frame)

    ECHO_PORT = 7
    def EchoRequest(self):
        self.comment("Echo Request Test")
        # send the echo request packet
        Data = self.random_string(1,228)
        SrcPort = randint(1,255)
        Segment = self.L4Encap(Data, self.ECHO_PORT, SrcPort)
        Packet = self.L3Encap(Segment, self.L3_CB3_ADDR, self.L3_OUR_ADDR, self.L4_HEADER_TYPE)
        Frame = self.L2Encap(Packet, self.L2_ROUTER_ADDR, self.L2_OUR_ADDR, self.L3_HEADER_TYPE, 0)
        self.write(Frame)

        # handle an ADP if we expect one
        self.DoWeExpectADP()

        # verify the echo response packet
        Segment = self.L4Encap(Data, SrcPort, self.ECHO_PORT)
        Packet = self.L3Encap(Segment, self.L3_OUR_ADDR, self.L3_CB3_ADDR, self.L4_HEADER_TYPE)
        Frame = self.L2Encap(Packet, self.L2_OUR_ADDR, self.L2_ROUTER_ADDR, self.L3_HEADER_TYPE, 0)
        self.read(length=len(Frame), expect=Frame)

    CHARGEN_PORT = 19
    def ChargenRequest(self):
        self.comment("Chargen Request Test")
        # send the chargen request packet
        Data = ""
        SrcPort = randint(1,255)
        Segment = self.L4Encap(Data, self.CHARGEN_PORT, SrcPort)
        Packet = self.L3Encap(Segment, self.L3_CB3_ADDR, self.L3_OUR_ADDR, self.L4_HEADER_TYPE)
        Frame = self.L2Encap(Packet, self.L2_ROUTER_ADDR, self.L2_OUR_ADDR, self.L3_HEADER_TYPE, 0)
        self.write(Frame)

        # handle an ADP if we expect one
        self.DoWeExpectADP()

        # verify the chargen response packet
        NumGeneratedBytes = self.prng.prng() % 127
	Response = ""
	for i in range(NumGeneratedBytes):
	    Response += chr(self.prng.prng() % 256)
        Segment = self.L4Encap(Response, SrcPort, self.CHARGEN_PORT)
        Packet = self.L3Encap(Segment, self.L3_OUR_ADDR, self.L3_CB3_ADDR, self.L4_HEADER_TYPE)
        Frame = self.L2Encap(Packet, self.L2_OUR_ADDR, self.L2_ROUTER_ADDR, self.L3_HEADER_TYPE, 0)
	self.read(length=len(Frame), expect=Frame)

    PWDGEN_PORT = 129
    def PwdgenRequest(self):
        self.comment("Pwdgen Request Test")
        Pwdgen_Offset = 6
	index = 0

	# Generate a pwdgen request
        SrcPort = randint(1,255)
        Data = ""
        Segment = self.L4Encap(Data, self.PWDGEN_PORT, SrcPort)
        Packet = self.L3Encap(Segment, self.L3_CB3_ADDR, self.L3_OUR_ADDR, self.L4_HEADER_TYPE)
        Frame = self.L2Encap(Packet, self.L2_ROUTER_ADDR, self.L2_OUR_ADDR, self.L3_HEADER_TYPE, 0)
        self.write(Frame)
        Passwords = ""

        # handle an ADP if we expect one
        self.DoWeExpectADP()

	# form up the expected response
	Passwords = ""
	for NumPasswords in range(6):
            for Syllables in range (10):
                rand_value = ord(self.magic_page[index])
                Passwords += chr(ord('a')+rand_value/26)
                Passwords += chr(ord('a')+rand_value%26)
                index += Pwdgen_Offset
            Passwords += "\n"
    
        # verify the response
        Segment = self.L4Encap(Passwords, SrcPort, self.PWDGEN_PORT)
        Packet = self.L3Encap(Segment, self.L3_OUR_ADDR, self.L3_CB3_ADDR, self.L4_HEADER_TYPE)
        Frame = self.L2Encap(Packet, self.L2_OUR_ADDR, self.L2_ROUTER_ADDR, self.L3_HEADER_TYPE, 0)
	self.read(length=len(Frame), expect=Frame)

    def SpoofTest(self):
        self.comment("Spoof Test")
        # send a spoofed packet
        Data = ""
        SrcPort = randint(1,255)
        Segment = self.L4Encap(Data, self.CHARGEN_PORT, SrcPort)
        Packet = self.L3Encap(Segment, self.L3_CB3_ADDR, 0x0a010302, self.L4_HEADER_TYPE)
        Frame = self.L2Encap(Packet, self.L2_ROUTER_ADDR, self.L2_OUR_ADDR, self.L3_HEADER_TYPE, 0)
        self.write(Frame)

        # send a normal EchoRequest.  If it fails, so did the spoof test
        self.EchoRequest()

    def InvalidLengthTest(self):
        self.comment("Invalid Packet/Segment Length Test")
        # change either the L3 len or L4 len and make sure it's caught
        Data = ""
        SrcPort = randint(1,255)
        Segment = self.L4Encap(Data, self.CHARGEN_PORT, SrcPort)
        Packet = self.L3Encap(Segment, self.L3_CB3_ADDR, 0x0a010302, self.L4_HEADER_TYPE)
        Frame = self.L2Encap(Packet, self.L2_ROUTER_ADDR, self.L2_OUR_ADDR, self.L3_HEADER_TYPE, 0)
        l = list(Frame)
        if randint(0,1):
            # change the L3 len
            l[15] = chr(0x1)
        else:
            # change the L4 len
            l[19] = chr(0x1)
        Frame = "".join(l)

        self.write(Frame)

        # send a normal EchoRequest.  If it fails, so did the length test
        self.EchoRequest()

    def UnknownUnicastTest(self):
        self.comment("Unknown Unicast Test")
        # send a frame to a previously unused dst L2 addr
        Data = ""
        SrcPort = randint(1,255)
        Segment = self.L4Encap(Data, self.CHARGEN_PORT, SrcPort)
        Packet = self.L3Encap(Segment, self.L3_CB3_ADDR, 0x0a010302, self.L4_HEADER_TYPE)
        Frame = self.L2Encap(Packet, self.UnknownDstL2, self.L2_OUR_ADDR, self.L3_HEADER_TYPE, 0)
        self.write(Frame)

        # send a normal EchoRequest.  If it fails, so did the length test
        self.EchoRequest()

        self.UnknownDstL2 +=1

    def InvalidChecksum(self):
        self.comment("Invalid Checksum Test")
        Data = ""
        SrcPort = randint(1,255)
        Segment = self.L4Encap(Data, self.ECHO_PORT, SrcPort)
        Packet = self.L3Encap(Segment, self.L3_CB3_ADDR, self.L3_OUR_ADDR, self.L4_HEADER_TYPE)
        Frame = self.L2Encap(Packet, self.L2_ROUTER_ADDR, self.L2_OUR_ADDR, self.L3_HEADER_TYPE, 0)
        l = list(Frame)
        l[-1] = chr(ord(l[-1])+1)
        Frame = "".join(l)
        self.write(Frame)

        # send a normal EchoRequest.  If it fails, so did the length test
        self.EchoRequest()

    def WrongNxtHdr(self):
        self.comment("Wrong NxtHdr Test")
        Data = ""
        SrcPort = randint(1,255)
        Segment = self.L4Encap(Data, self.ECHO_PORT, SrcPort)
        Packet = self.L3Encap(Segment, self.L3_CB3_ADDR, self.L3_OUR_ADDR, self.L4_HEADER_TYPE)
        Frame = self.L2Encap(Packet, self.L2_ROUTER_ADDR, self.L2_OUR_ADDR, self.L3_HEADER_TYPE, 0)

        l = list(Frame)
        if randint(0,1):
            # change the L2 NxtHdr
            l[5] = chr(randint(5,255))
        else:
            # change the L3 NxtHdr
            l[16] = chr(randint(5,255))
        Frame = "".join(l)

        self.write(Frame)

        # send a normal EchoRequest.  If it fails, so did the length test
        self.EchoRequest()

    def start(self):
        #self.delay(100)
        self.prng = CROMU_PRNG()
        self.prng.seed_by_array(np.fromstring( self.magic_page, dtype=np.uint32 ), 32)

	self.CHARGEN_MAGIC_PAGE_INDEX = 0
	self.ADP_Age = 0

        # keep track of the unknown L2 dst addr's we've used
        self.UnknownDstL2 = 0xb000

        pass

    def end(self):
        pass

