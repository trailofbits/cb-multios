#!/usr/bin/python

from generator.actions import Actions
import random
from math import log
from collections import deque
import ctypes as ct

#
# Implementation of Mersenne Twister PRNG
#
class Mersenne:
	
	def __init__(self,seed):
		self.mt_state = range(624)
		self.idx = 0
		self.mt_state[0] = seed & 0xffffffff
		for i in range(1,624):
			self.mt_state[i] = (0x6c078965 * (self.mt_state[i-1] ^ (self.mt_state[i-1] >> 30)) + i) & 0xffffffff

	def gen_mt_state(self):
		for i in range(624):
			t = (self.mt_state[i] & 0x80000000) + (self.mt_state[(i+1) % 624] & 0x7fffffff)
			self.mt_state[i] = self.mt_state[(i+397) % 624] ^ (t >> 1)
			if t % 2 != 0:
				self.mt_state[i] = self.mt_state[i] ^ 0x9908b0df

	# generate and return a random number
	def rand_mt(self):
		if self.idx == 0:
			self.gen_mt_state()
	
		ret = self.mt_state[self.idx]
		ret = ret ^ (ret >> 11)
		ret = ret ^ ((ret << 7) & 0x9d2c5680)
		ret = ret ^ ((ret << 15) & 0xefc60000)
		ret = ret ^ (ret >> 18)
		
		self.idx = (self.idx + 1) % 624
		
		return(ret)

#
# Packet Generator
#
class Generator:

	def __init__(self, MT):
		self.mode = 1
		self.MT = MT
		self.gen_rate = 0

		self.NextPkt = {}
		self.NextPkt['timestamp'] = 0.0
		self.NextPkt['bytes'] = 0
		self.NextPkt['priority'] = 0
		self.last_pkt_time = 0.0

		self.ManualPkts = {}
		self.ManualCurr = -1
		self.ManualNumPkts = 0
		self.repeat = 0

		self.Generators = {
			1: self.GenerateRandom,
			2: self.GeneratePoisson,
			3: self.GenerateManual,
		}

		# call to CB's CalcDelta to deal with floating point 
		# inconsistencies between python and C's log() functions
		self.dll = ct.CDLL('build/patched/so/CROMU_00016.so')
		self.CalcDelta = self.dll.CalcDelta;
		self.CalcDelta.argtypes = [ct.c_uint32, ct.c_double]
		self.CalcDelta.restype = ct.c_double

	def SetRepeat(self, repeat):
		self.repeat = repeat

	def SetMode(self, mode):
		self.mode = mode

	def SetGenRate(self, gen_rate):
		self.gen_rate = gen_rate

	def GetGenRate(self):
		return self.gen_rate

	def ManualAppend(self, timestamp, length, priority):
		self.ManualPkts[self.ManualNumPkts] = {}
		self.ManualPkts[self.ManualNumPkts]['timestamp'] = timestamp
		self.ManualPkts[self.ManualNumPkts]['bytes'] = length
		self.ManualPkts[self.ManualNumPkts]['priority'] = priority
		self.ManualNumPkts += 1

	# generate a random packet
	def GenerateRandom(self):
		if self.NextPkt['bytes']:
			return(self.NextPkt)

		delta = self.MT.rand_mt() / 4294967295.0
		delta *= self.gen_rate

		length = (self.MT.rand_mt() % 1436) + 64

		pri = self.MT.rand_mt()
		pri = pri & 0x0000003f

		self.NextPkt['timestamp'] = self.last_pkt_time + delta
		self.last_pkt_time = self.NextPkt['timestamp']
		self.NextPkt['bytes'] = length
		self.NextPkt['priority'] = pri

		return(self.NextPkt)

	# generate a Poisson distribution random packet
	def GeneratePoisson(self):
		if self.NextPkt['bytes']:
			return(self.NextPkt)

		delta = self.CalcDelta(self.MT.rand_mt(), self.gen_rate)

		length = (self.MT.rand_mt() % 1436) + 64

		pri = self.MT.rand_mt()
		pri = pri & 0x0000003f

		self.NextPkt['timestamp'] = self.last_pkt_time + delta
		self.last_pkt_time = self.NextPkt['timestamp']
		self.NextPkt['bytes'] = length
		self.NextPkt['priority'] = pri

		return(self.NextPkt)

	# generate a manually entered packet
	def GenerateManual(self):
		if self.NextPkt['bytes']:
			return(self.NextPkt)

		if self.ManualCurr == -1:
			# first time we've been called
			self.NextPkt['timestamp'] = self.ManualPkts[0]['timestamp'] + self.last_pkt_time
			self.last_pkt_time = self.NextPkt['timestamp']
			self.NextPkt['bytes'] = self.ManualPkts[0]['bytes']
			self.NextPkt['priority'] = self.ManualPkts[0]['priority']
			self.ManualCurr = (1) % self.ManualNumPkts
		else:
			if (self.ManualCurr == 0 and self.repeat == 0):
				return (self.NextPkt)

			self.NextPkt['timestamp'] = self.ManualPkts[self.ManualCurr]['timestamp'] + self.last_pkt_time
			self.last_pkt_time = self.NextPkt['timestamp']
			self.NextPkt['bytes'] = self.ManualPkts[self.ManualCurr]['bytes']
			self.NextPkt['priority'] = self.ManualPkts[self.ManualCurr]['priority']
			self.ManualCurr = (self.ManualCurr+1) % self.ManualNumPkts

		return(self.NextPkt)

	# generic function that calls the appropriate specfic function
	# based on the mode (random, poisson, manual) that was selected
	def Generate(self):
		return self.Generators[self.mode]()		


#
# Network Simulator and bulk of the CB interaction code
#
class NetSim(Actions):
	def start(self):
		# define the vars needed for the poller state
		self.iface = {}
		self.iface['speed'] = 0
		self.iface['total_pkts'] = 0
		self.iface['total_bytes'] = 0
		self.iface['num_queues'] = 0
		self.iface['priority_queue_enable'] = 0
		self.iface['ifg'] = 0.0

		self.generator = 0
		self.gen_rate = 0.0
		self.repeat = 0
		self.wall_clock = 0.0
		self.max_wall_clock = 0.0
		self.num_queues = 0

		self.queue = range(8)
		for q in range(0,8):
			# create the queue
			self.queue[q] = {
				'min_priority': 0,
				'max_priority': 0,
				'weight': 0,
				'max_depth': 0,
				'curr_depth': 0,
				'bucket': 0,
				'max_tokens': 0,
				'total_pkts': 0,
				'total_bytes': 0,
				'dropped_pkts': 0,
				'cumulative_latency': 0.0,
				'pkts': deque() }

		# call each of the CB interaction functions
		self.SetIntSpeed()
		if self.SetGenerator():
			return
		self.SetQueues()

	#
	# Handle the CB banner and interface speed prompts
	#
	def SetIntSpeed(self):
		self.read(delim='\n', expect="Welcome to the network queuing simulator\n")
		self.read(delim=': ', expect="What's the interface speed (in bps up to 4194304 bps): ")
		# randomly try sending an incorrect value
		if random.randint(0,1):
			# send an invalid input 
			self.iface['speed'] = random.randint(4194305,9999999)
			self.write("%d\n" % self.iface['speed'])
			self.read(delim=': ', expect="What's the interface speed (in bps up to 4194304 bps): ")

		# send valid input
		self.iface['speed'] = random.randint(10000,4194304)
		self.write("%d\n" % self.iface['speed'])

		# init MT prng using the speed as the seed
		self.MT = Mersenne(self.iface['speed'])
		
		# set the 96-bit inter-frame gap time
		self.iface['ifg'] = 96.0 / self.iface['speed']

	#
	# Handle the packet generator prompts
	#
	def SetGenerator(self):	
		self.read(delim='\n', expect="The following packet generators are available:\n")
		self.read(delim='\n', expect="  1 - Random\n")
		self.read(delim='\n', expect="  2 - Poisson\n")
		self.read(delim='\n', expect="  3 - Manual\n")
		self.read(delim=': ', expect="Which generator would you like to use? (1-3): ")
		# randomly try sending an incorrect value
		if random.randint(0,1):
			# send an invalid input 
			mode = random.randint(4, 10)
			self.write("%d\n" % self.generator)
			self.read(delim=': ', expect="Which generator would you like to use? (1-3): ")
		
		# send valid input
		mode = random.randint(1, 3)
		self.write("%d\n" % mode)

		# init the local MT PRNG
		self.PktGen = Generator(self.MT)

		if mode == 1:
			self.SetRandomGenerator()
			self.PktGen.SetMode(1)
		elif mode == 2:
			self.SetPoissonGenerator()
			self.PktGen.SetMode(2)
		elif mode == 3:
			if self.SetManualGenerator():
				return -1
			self.PktGen.SetMode(3)

		self.read(delim=': ', expect="For how long would you like the simulation to run? (1 - 10s): ")
		self.max_wall_clock = random.randint(0, 10)
		self.write("%d\n" % self.max_wall_clock)

		return 0


	#
	# Handle the Random Generator prompts
	#
	def SetRandomGenerator(self):
		self.read(delim=': ', expect="What average bit rate do you want the random generator to produce? (1 - 4194304 bps): ")
		# randomly try sending an incorrect value
		if random.randint(0,1):
			# send an invalid input 
			gen_bps = random.randint(4194305, 9999999)
			self.write("%d\n" % gen_bps)
			self.read(delim=': ', expect="What average bit rate do you want the random generator to produce? (1 - 4194304 bps): ")

		# send valid input
		gen_bps = random.randint(1, 4194304)
		self.write("%d\n" % gen_bps)

		# calculate the actual packet rate from the bps and average packet size
		self.gen_rate = ((1500-64)/2*8.0) / gen_bps * 2.0
		self.PktGen.SetGenRate(self.gen_rate)

	#
	# Handle the Poisson Generator prompts
	#
	def SetPoissonGenerator(self):
		self.read(delim=': ', expect="What average bit rate do you want the poisson generator to produce? (1 - 4194304 bps): ")
		# randomly try sending an incorrect value
		if random.randint(0,1):
			# send an invalid input 
			gen_bps = random.randint(4194305, 9999999)
			self.write("%d\n" % gen_bps)
			self.read(delim=': ', expect="What average bit rate do you want the poisson generator to produce? (1 - 4194304 bps): ")

		# send valid input
		gen_bps = random.randint(1, 4194304)
		self.write("%d\n" % gen_bps)

		# calculate the actual packet rate from the bps and average packet size
		self.gen_rate = gen_bps / ((1500-64)/2.0*8.0)
		self.PktGen.SetGenRate(self.gen_rate)

	#
	# Handle the Manual Generator prompts
	#
	def SetManualGenerator(self):
		self.read(delim=': ', expect="Should the packet generator repeat the manually entered packets? (y,n): ")
		# randomly try sending an incorrect value
		if random.randint(0,50) == 0:
			# send an invalid input 
			self.write('z' + '\n')
			self.read(delim=': ', expect="Should the packet generator repeat the manually entered packets? (y,n): ")

		# send valid input
		choice = random.choice(['y','n'])
		self.write(choice + '\n')
		if (choice == 'y'):
			self.PktGen.SetRepeat(1)

		self.read(delim=': ', expect="How many packets would you like to enter? (1 - 1000): ")

		# randomly try sending an incorrect value
		if random.randint(0,50) == 0:
			# send an invalid input 
			pkt_count = random.choice([random.randint(-9999,0), random.randint(1001, 9999)])
			self.write("%d\n" % pkt_count)
			self.read(delim=': ', expect="How many packets would you like to enter? (1 - 1000): ")
		
		# send valid input
		pkt_count = random.randint(1, 1000)
		self.write("%d\n" % pkt_count)

		self.read(delim='\n', expect="Enter the packets, one per line in this format:\n")
		self.read(delim='\n', expect="time since last packet (s, ##.######),length (bytes 64-1500),priority (0-63)\n")
		# randomly try sending an incorrect value
		choice = random.randint(0,50)
		if choice > 40:
			# send incorrectly formatted timestamp
			length = random.randint(64, 1500)
			priority = random.randint(0, 63)
			self.write("%0.6f,%d,%d\n" % (random.uniform(-10.0, -0.00001), length, priority))
			self.read(delim='\n', expect="Invalid timestamp\n")
			self.read(delim='\n', expect="Unable to init packet generator\n")
			return -1
		elif choice > 30:
			# send incorrect bytes
			time = random.uniform(0.00001, 10.00000)
			priority = random.randint(0, 63)
			self.write("%0.6f,%d,%d\n" % (time, random.choice([random.randint(-10, 63), random.randint(1501, 9999)]), priority))
			self.read(delim='\n', expect="Invalid bytes\n")
			self.read(delim='\n', expect="Unable to init packet generator\n")
			return -1
		elif choice > 20:
			# send incorrect priority
			time = random.uniform(0.00001, 10.00000)
			length = random.randint(64, 1500)
			self.write("%0.6f,%d,%d\n" % (time, length, random.choice([random.randint(-10, -1), random.randint(64, 99)])))
			self.read(delim='\n', expect="Invalid priority\n")
			self.read(delim='\n', expect="Unable to init packet generator\n")
			return -1
		elif choice > 10:
			# send too many commas
			time = random.uniform(0.00001, 10.00000)
			length = random.randint(64, 1500)
			priority = random.randint(0, 63)
			self.write("%0.6f,%d,,%d\n" % (time, length, priority))
			self.read(delim='\n', expect="Invalid priority\n")
			self.read(delim='\n', expect="Unable to init packet generator\n")
			return -1

		# send valid input
		for x in range (0, pkt_count):
			time = random.uniform(0.00001, 0.10000)
			length = random.randint(64, 1500)
			priority = random.randint(0, 63)
			self.write("%0.6f,%d,%d\n" % (time, length, priority))
			# append to the packet list
			self.PktGen.ManualAppend(time, length, priority)

		return 0

	#
	# Handle the Queue creation prompts
	#
	def SetQueues(self):
		self.read(delim=': ', expect="How many queues (1-8)?: ")

		# randomly try sending an incorrect value
		if random.randint(0,1):
			# send an invalid input 
			self.write("%d\n" % random.choice([random.randint(-10, 0), random.randint(9, 20)]))
			self.read(delim=': ', expect="How many queues (1-8)?: ")

		# send valid input
		self.num_queues = random.randint(1, 8)
		self.write("%d\n" % self.num_queues)

		# setup each queue
		max_pri = 63
		remaining_weight = 100
		lowest_weight = 999
		for q in range (0, self.num_queues):
			self.read(delim='\n', expect="Queue %d:\n" % q)
			if q == 0:
				self.read(delim=': ', expect="  Is queue #0 a priority queue(y,n): ")
				if random.randint(0,1):
					self.iface['priority_queue_enable'] = 1
					self.write('y' + '\n')
				else: 
					self.write('n' + '\n')

			self.read(delim=': ', expect="  What's the minimum priority packet to place in queue #%d (0-63): " % q)
			self.queue[q]['min_priority'] = max_pri - (64 // self.num_queues)
			if q == self.num_queues-1:
				self.queue[q]['min_priority'] = 0
			self.write("%d\n" % self.queue[q]['min_priority'])
			
			self.read(delim=': ', expect="  What's the maximum priority packet to place in queue #%d (0-63): " % q)
			self.queue[q]['max_priority'] = max_pri
			self.write("%d\n" % self.queue[q]['max_priority'])
			max_pri = max_pri - (64 // self.num_queues) - 1

			self.read(delim=': ', expect="  What is the depth of queue #%d (1 - 1024 packets): " % q)
			self.queue[q]['max_depth'] = random.randint(1, 1024)
			self.write("%d\n" % self.queue[q]['max_depth'])
			
			if q == 0 and self.iface['priority_queue_enable']:
				self.queue[q]['weight'] = 100
			else: 
				self.read(delim=': ', expect="  What is the weight of queue #%d (1 - 100 percent): " % q)
				self.queue[q]['weight'] = 100 // self.num_queues
				if q == self.num_queues-1:
					self.queue[q]['weight'] = remaining_weight
				self.write("%d\n" % self.queue[q]['weight'])
				remaining_weight -= self.queue[q]['weight']

			if self.queue[q]['weight'] < lowest_weight:
				lowest_weight = self.queue[q]['weight']

		# calculate the max tokens or each queue
		total_tokens = 1500 * 100 // lowest_weight

		for q in range(0, self.num_queues):
			self.queue[q]['max_tokens'] = int(total_tokens * (self.queue[q]['weight'] / 100.0))

	#
	# During the simulation, 'receive' generated packets
	# and put the into the correct queues for 'transmission'
	#
	def RX(self):
		p = self.PktGen.Generate()
		while p['bytes']:
			if p['timestamp'] > self.wall_clock:
				# designated time hasn't arrived yet for this packet
				break

			# time has arrived, so place the packet in the appropriate queue
			for q in range(0,self.num_queues):
				if p['priority'] >= self.queue[q]['min_priority'] and p['priority'] <= self.queue[q]['max_priority']:
					if self.queue[q]['curr_depth'] < self.queue[q]['max_depth']:
						self.queue[q]['pkts'].append(p.copy())
						self.queue[q]['curr_depth'] += 1
					else:
						self.queue[q]['dropped_pkts'] += 1

					# mark the genrated packet as queued
					p['bytes'] = 0

					break

			# gen the next packet
			p = self.PktGen.Generate()

	#
	# During the simulation, service the queues based 
	# on the configured priorities
	#
	def TX(self):
		# replinish tokens
		for q in range(0,self.num_queues):
			self.queue[q]['bucket'] = self.queue[q]['max_tokens']

		# service the priority queue
		if self.iface['priority_queue_enable']:
			while self.queue[0]['curr_depth']:
				# get the next packet and send it
				p = self.queue[0]['pkts'].popleft()
				self.queue[0]['cumulative_latency'] += self.wall_clock - p['timestamp']
				self.wall_clock += ((p['bytes'] * 8.0) / self.iface['speed']) + self.iface['ifg']
				self.queue[0]['curr_depth'] -= 1

				# keep some stats
				self.queue[0]['total_pkts'] += 1;
				self.queue[0]['total_bytes'] += p['bytes']
				self.iface['total_pkts'] += 1;
				self.iface['total_bytes'] += p['bytes']

				if self.wall_clock > self.max_wall_clock:
					return

				# receive any new packets which have arrived
				self.RX()
				
		# service the rest of the queues
		for q in range(0, self.num_queues):
			if (self.iface['priority_queue_enable'] and q == 0):
				continue

			while self.queue[q]['curr_depth']:
				# get the next packet and try to send it
				if self.queue[q]['pkts'][0]['bytes'] <= self.queue[q]['bucket']:
					p = self.queue[q]['pkts'].popleft()
					# we have tokens, send the packet
					self.queue[q]['cumulative_latency'] += self.wall_clock - p['timestamp']
					self.wall_clock += ((p['bytes'] * 8.0) / self.iface['speed']) + self.iface['ifg']
					self.queue[q]['curr_depth'] -= 1
					self.queue[q]['bucket'] -= p['bytes']
	
					# keep some stats
					self.queue[q]['total_pkts'] += 1;
					self.queue[q]['total_bytes'] += p['bytes']
					self.iface['total_pkts'] += 1;
					self.iface['total_bytes'] += p['bytes']

					if self.wall_clock > self.max_wall_clock:
						return

					# receive any new packets which have arrived
					self.RX()
				else:
					break

	# 
	# Check the output of the CB and make sure all of the queue
	# stats match up
	#
	def CheckStats(self):
		# deal with floating point inaccuracies in python
		self.read(delim='\n', expect_format='pcre', expect="wall_clock:\s+\d+\.\d+\s+\(s\)")
		for q in range(0,self.num_queues):
			self.read(delim='\n', expect="Queue %d\n" % q)
			self.read(delim='\n', expect="  Pkts Transmitted:       %d\n" % self.queue[q]['total_pkts'])
			self.read(delim='\n', expect="  Pkts Dropped:           %d\n" % self.queue[q]['dropped_pkts'])

			if self.queue[q]['total_pkts'] == 0:
				self.read(delim='\n', expect="  Average Latency (s):    %0.5f\n" % 0.0)
			else:
				# deal with floating point inaccuracies in python
				self.read(delim='\n', expect_format='pcre', expect="  Average Latency \(s\):\s+\d+\.\d+")

			self.read(delim='\n', expect="  Enqueued Pkts:          %d\n" % self.queue[q]['curr_depth'])
			b = 0
			pktnum = 0
			while len(self.queue[q]['pkts']):
				p = self.queue[q]['pkts'].popleft()
				b += p['bytes']
				pktnum += 1
			self.read(delim='\n', expect="  Queue Depth (bytes):    %d\n" % b)

		self.read(delim='\n', expect="Interface Stats\n")
		self.read(delim='\n', expect="  Pkts Transmitted:       %d\n" % self.iface['total_pkts'])

	#
	# main routine to run the simulation
	#
	def RunSimulation(self):
		if self.num_queues == 0:
			return

		# run the simulation until time is up
		while 1:
			self.RX()
			self.TX()
			self.wall_clock += 0.00001
			if (self.wall_clock > self.max_wall_clock):
				break
		
		# check the output stats
		self.CheckStats()
