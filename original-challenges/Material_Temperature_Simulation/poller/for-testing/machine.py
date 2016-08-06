#!/usr/bin/python

import sys
from generator.actions import Actions
import ctypes as ct
import random

class TSim:
	def __init__(self):
		self.dll = ct.CDLL('build/patched/so/CROMU_00029.so')

		# variables for size of the material
		self.X = ct.c_uint32.in_dll(self.dll, 'X')
		self.Y = ct.c_uint32.in_dll(self.dll, 'Y')
		self.Z = ct.c_uint32.in_dll(self.dll, 'Z')

		# TimeStep between simulation calculations
		self.TimeStep = ct.c_double.in_dll(self.dll, 'TimeStep')

		# Total elapsed simlulation time
		self.SIM_TIME = ct.c_double.in_dll(self.dll, 'SIM_TIME')

		# Function to run one calculation step
		self.SimStep = self.dll.SimStep;
		self.SimStep.argtypes = None
		self.SimStep.restype = ct.c_int32

		# Function to allocate a new grid
		self.AllocateGrid = self.dll.AllocateGrid;
		self.AllocateGrid.restype = ct.c_int

		# Function to average a block of array values
		self.TGridAverage = self.dll.TGridAverage;
		self.TGridAverage.argtypes = [ ct.c_uint32, ct.c_uint32, ct.c_uint32, ct.c_uint32, ct.c_uint32, ct.c_uint32, ct.c_uint32 ]
		self.TGridAverage.restype = ct.c_double

		# Functions to init materials
		self.InitAir = self.dll.InitAir
		self.InitAir.argtypes = None
		self.InitAir.restype = None
		self.InitAluminum = self.dll.InitAluminum;
		self.InitAluminum.argtypes = None
		self.InitAluminum.restype = None
		self.InitCopper = self.dll.InitCopper
		self.InitCopper.argtypes = None
		self.InitCopper.restype = None
		self.SetTC = self.dll.SetTC
		self.SetTC.argtypes = [ ct.c_uint32, ct.c_char_p ]
		self.SetTC.restype = None
		self.SetHC = self.dll.SetHC
		self.SetHC.argtypes = [ ct.c_uint32, ct.c_char_p ]
		self.SetHC.restype = None

		# Increment simulation time
		self.IncrementTimestep = self.dll.IncrementTimestep
		self.IncrementTimestep.argtypes = [ ct.POINTER(ct.c_double) ]
		self.IncrementTimestep.restype = None

		# Store value into a Temperature grid location
		self.StoreTemp = self.dll.StoreTemp
		self.StoreTemp.argtypes = [ ct.POINTER(ct.c_double), ct.c_uint32, ct.c_uint32, ct.c_uint32, ct.c_char_p ]
		self.StoreTemp.restype = ct.c_uint32

		# Function to calculate the best timestep
		self.TimeStep = ct.c_double.in_dll(self.dll, 'TimeStep')
		self.CalcTimeStep = self.dll.CalcTimeStep;

		# Function to generate an output string using CB libraries
		self.output_str = self.dll.output_str
		self.output_str.argtypes = [ ct.c_uint32, ct.c_uint32, ct.c_char_p ]
		self.output_str.restype = None

	def Offset(self, x, y, z):
		return x + y*self.X.value + z*self.X.value*self.Y.value

	def SetDimensions(self, X, Y, Z):
		self.X.value = X
		self.Y.value = Y
		self.Z.value = Z

		# allocate space to hold the array
		self.TGrid = ct.POINTER(ct.c_double).in_dll(self.dll, "TGrid")
		self.AllocateGrid(ct.byref(self.TGrid), X,Y,Z)

		self.HGrid = ct.POINTER(ct.c_double).in_dll(self.dll, "HGrid")
		self.AllocateGrid(ct.byref(self.HGrid), X,Y,Z)

	def SetTemp(self, x, y, z, buf):
		c_x = ct.c_uint32(x)
		c_y = ct.c_uint32(y)
		c_z = ct.c_uint32(z)
		self.StoreTemp(self.TGrid, c_x, c_y, c_z, buf)

	def SetHeat(self, x, y, z, buf):
		c_x = ct.c_uint32(x)
		c_y = ct.c_uint32(y)
		c_z = ct.c_uint32(z)
		self.StoreTemp(self.HGrid, c_x, c_y, c_z, buf)

	def SetSimLength(self, SimLength):
		self.SIM_TIME = SimLength

class MyClass(Actions):
	def start(self):
		self.Sim = TSim()

		self.InitMaterial()

		return

	def InitCustomMaterial(self):
		temps = ["-264.15", "-193.15", "-112.15", " -31.15", "  49.85", " 129.85", " 210.85", " 291.85"]

		# set the thermal conductivities
		self.read(delim='\n', expect='Enter the thermal conductivities in W/(m*K) for your material at the following temperatures (Celcius):\n')
		rnd = random.uniform(1.0,1000.0);
		index = 0
		for temp in temps:
			self.read(delim=': ', expect=temp+': ')
			rnd = rnd * random.uniform(.75,1.25)
			rnd_text = "%0.5f" % rnd
			self.write(rnd_text+'\n')
			self.Sim.SetTC(index, rnd_text)
			index += 1

		# set the heat capacities
		self.read(delim='\n', expect='Enter the heat capacity in J/(m^3*K) for your material when it is at the following temperatures (Celcius):\n')
		rnd = random.uniform(1.0,2000000.0);
		index = 0
		for temp in temps:
			self.read(delim=': ', expect=temp+': ')
			rnd = rnd * random.uniform(.75,1.25)
			rnd_text = "%0.5f" % rnd
			self.write(rnd_text+'\n')
			self.Sim.SetHC(index, rnd_text)
			index += 1


	def InitMaterial(self):
		self.read(delim='\n', expect='For what material would you like to run this simulation?\n')
		self.read(delim='\n', expect='  1. Air\n')
		self.read(delim='\n', expect='  2. Aluminum\n')
		self.read(delim='\n', expect='  3. Copper\n')
		self.read(delim='\n', expect='  4. Custom\n')
		self.read(delim=': ', expect='Selection: ')

		material = random.randint(1,4)
		self.write("%d\n" % material)
		if (material == 1):
			self.Sim.InitAir();
		elif (material == 2):
			self.Sim.InitAluminum();
		elif (material == 3):
			self.Sim.InitCopper();
		elif (material == 4):
			self.InitCustomMaterial()

		# get the material dimensions
		self.read(delim=': ', expect='How large is the material (X,Y,Z meters): ')
		X = random.randint(1,15)
		Y = random.randint(1,15)
		Z = random.randint(1,15)
		self.write('%d,%d,%d\n' % (X,Y,Z))
		self.Sim.SetDimensions(X,Y,Z)

		# set up temperature grid
		self.read(delim=': ', expect='Should the material be isothermic? (y,n): ')
		if (random.randint(0,1) == 1):
			# isothermic
			self.write('y\n')
			self.read(delim=': ', expect='  What temperature? (-173.15000 - 373.00000 degrees C): ')
			temp = random.uniform(-173.15, 373.00)
			self.write("%0.5f\n" % temp)
			for z in range(0, Z):
				for y in range(0, Y):
					for x in range(0, X):
						temp_text = "%0.5f" % temp
						self.Sim.SetTemp(x, y, z, temp_text)
		else:
			# not isothermic 
			self.write('n\n')

			# manually defined
			self.read(delim='\n', expect='  Send the grid temperatures as a comma separated list of Celcius decimal values.\n')
			self.read(delim='\n', expect='  The program will populate the X, then Y, then Z dimensions of the room.\n')
			for z in range(0, Z):
				for y in range(0, Y):
					for x in range(0, X):
						temp = random.uniform(-173.15, 373.00)
						self.write('%0.5f' % temp)
						if (z != Z-1 or y != Y-1 or x != X-1):
							self.write(',')
						temp_text = "%0.5f" % temp
						self.Sim.SetTemp(x, y, z, temp_text)
			self.write('\n')
		
		# setup energy sources
		self.read(delim=': ', expect='Are there any constant energy sources in the room? (y,n): ')
		if (random.randint(0,1) == 1):
			# there are energy sources
			self.write('y\n')
			self.read(delim='\n', expect='  Send the heat sources as temperatures in a comma separated list of Celcius decimal values.\n')
			self.read(delim='\n', expect='  The program will populate the X, then Y, then Z dimensions of the room.\n')
			self.read(delim='\n', expect="  Send -174.00000 for any grid location which doesn't have a heat source.\n")
			for z in range(0, Z):
				for y in range(0, Y):
					for x in range(0, X):
						if (random.randint(0,10) == 0):
							# this cell has a source
							temp = random.uniform(-173.15, 373.00)
							self.write('%0.5f' % temp)
							if (z != Z-1 or y != Y-1 or x != X-1):
								self.write(',')
							temp_text = "%0.5f" % temp
							self.Sim.SetHeat(x, y, z, temp_text)
						else:
							# no source
							self.write('-174.0000')
							if (z != Z-1 or y != Y-1 or x != X-1):
								self.write(',')
							temp_text = "%0.5f" % (-174.00000)
							self.Sim.SetHeat(x, y, z, temp_text)
			self.write('\n')
		else:
			# no energy sources
			self.write('n\n')
			temp_text = "%0.5f" % (-174.00000)
			for z in range(0, Z):
				for y in range(0, Y):
					for x in range(0, X):
						self.Sim.SetHeat(x, y, z, temp_text)

		# setup simulation length
		self.Sim.CalcTimeStep()
		self.read(delim=': ', expect='For how long would you like to run the simulation? (s): ')
		# run for somewhere between 1 and 25 rounds of calculations
		simlength = random.uniform(1.0,25.0)*self.Sim.TimeStep.value
		self.write("%0.5f\n" % simlength)
		self.Sim.SetSimLength(simlength)

	def ReadGraphTemps2(self):
		# output array
		output = [[0 for x in range(10)] for y in range(10)]

		# read the clear screen 
		self.read(length=7, expect='\033[2J\033[H')

		countx = int(self.Sim.X.value/10.0)+1
		county = int(self.Sim.Y.value/10.0)+1
		
		for z in range(0, self.Sim.Z.value):
			self.read(delim='\n', expect='z: %d\n' % z);
			
			starty = 0
			y = 0
	
			while (starty < self.Sim.Y.value):
				startx = 0
				x = 0

				while (startx < self.Sim.X.value):
					output[x][y] = self.Sim.TGridAverage(x, y, startx, starty, countx, county, z)
					startx += countx
					x += 1

				starty += county
				y += 1

			c_buf = ct.create_string_buffer(512)
			for out_x in range(0, x):
				outstring = ""
				for out_y in range (0, y):
					self.Sim.output_str(out_x, out_y, c_buf)
					outstring += "{:>10} ".format(c_buf.value)

				self.read(delim='\n', expect=outstring+'\n')
			self.read(delim='\n', expect='\n')
					
	def RunSimulation(self):

		self.ReadGraphTemps2()
		self.read(delim='\n', expect='At 0.00000 seconds\n')
		self.write('\n')

		CurrTime = ct.c_double(0.0)
		while CurrTime.value < self.Sim.SIM_TIME:
			self.Sim.SimStep()
			self.Sim.IncrementTimestep(ct.pointer(CurrTime))
			self.ReadGraphTemps2()
			self.read(delim='\n', expect='At %0.5f seconds\n' % CurrTime.value)
			self.write('\n')
