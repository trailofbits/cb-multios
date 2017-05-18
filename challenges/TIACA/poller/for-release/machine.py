#!/usr/bin/env python

from generator.actions import Actions
import random
import struct
import string
import sys

class carstate():

	def __init__(self):
		self.speed = 0
		self.fuel = 65535
		self.rpm = 0
		self.info_state = 0
		self.info_volume = 0
		self.car_power = 0
		self.gear = TIACA.GEARS_PARK
		self.gear_state = TIACA.GEARS_UNCLUTCH
		self.window_state = TIACA.WINDOWS_UP
		self.moonroof_state = TIACA.MOONROOF_CLOSED
		self.trunk_state = TIACA.TRUNK_CLOSED
		self.alarm_state = TIACA.ALARM_UNSET
		self.trunk_load = 0
		self.boom = False
		self.bt_metadata = ""

	def setPowerState(self, state):
		self.car_power = state

	def __str__(self):
		return struct.pack("<BHhBBBBBBBBBI32s", self.speed, self.fuel, self.rpm, self.info_state, self.info_volume, self.car_power,
			self.gear, self.gear_state, self.window_state, self.moonroof_state, self.trunk_state, self.alarm_state, self.trunk_load, self.bt_metadata)

class TIACA(Actions):

	GEARS_ACCEL = 0x70
	GEARS_SLOWDOWN = 0x71
	GEARS_SHIFTUP  = 0x72
	GEARS_SHIFTDOWN = 0x73
	GEARS_CLUTCH = 0x74
	GEARS_UNCLUTCH = 0x75
	GEARS_PARK	 = 0x10
	GEARS_FIRST = 0x20
	GEARS_SECOND = 0x30
	GEARS_THIRD = 0x40
	GEARS_FOURTH = 0x50
	GEARS_FIFTH = 0x60

	CAR_OFF = 0x10
	CAR_ON = 0x20
	CAR_ACC = 0x30

	WINDOWS_DOWN = 0xf0
	WINDOWS_UP	 = 0xe0
	MOONROOF_OPEN = 0xd0
	MOONROOF_CLOSED = 0xc0
	TRUNK_OPEN	 = 0xb0
	TRUNK_CLOSED = 0xa0
	TRUNK_LOAD	 = 0x90
	TRUNK_UNLOAD = 0x80

	INFO_XM = 0x05
	INFO_AM = 0x01
	INFO_FM = 0x02
	INFO_AUX = 0x03
	INFO_BT = 0x04
	INFO_VOLUP = 0x81
	INFO_VOLDOWN = 0x91
	INFO_OFF = 0xff

	ALARM_UNSET = 0xf9
	ALARM_SET = 0xf8

	CHANGE_STATE = 0xcc
	CAR_END = 0xdd
	#b
	#B
	#h
	#H
	#i
	#I unsigned

	def start(self):
		self.carstate = carstate()
#		self.carstate.
		pass

	def carOff(self):
		self.write("%c\n" % self.CAR_OFF)
		if(self.carstate.gear == self.GEARS_PARK):
			self.carstate.setPowerState(self.CAR_OFF)

	def carOn(self):
		self.write("%c\n" % self.CAR_ON)
		self.carstate.setPowerState(self.CAR_ON)

	def carAcc(self):
		self.write("%c\n" % self.CAR_ACC)
		if(self.carstate.car_power == self.CAR_OFF or (self.carstate.car_power == self.CAR_ON and self.carstate.gear == self.GEARS_PARK)):
			self.carstate.setPowerState(self.CAR_ACC)

	def end(self):
		if(self.carstate.boom == True):
			return
		self.write("%c\n" % self.CAR_END)
		self.read(length=len(str(self.carstate)), expect=str(self.carstate))

	def windowsUp(self):
		self.write("%c\n" % self.WINDOWS_UP)
		self.carstate.window_state = self.WINDOWS_UP

	def windowsDown(self):
		self.write("%c\n" % self.WINDOWS_DOWN)
		self.carstate.window_state = self.WINDOWS_DOWN

	def changeInfo(self):
		state = random.choice([self.INFO_OFF, self.INFO_AM, self.INFO_FM, self.INFO_XM, self.INFO_AUX])
		self.write("%c\n" % state)
		if(self.carstate.gear > self.GEARS_THIRD and self.carstate.speed > 30):
			self.carstate.info_state = state
		if(state == self.INFO_OFF):
			self.carstate.info_volume = 0

	def btInfo(self):
		metadata = "".join(random.choice(string.ascii_letters + string.digits) for _ in range(31))
		tosend = struct.pack("<BB31s", int(self.INFO_BT), 31, metadata)
		self.write(tosend + "\n")
		if(self.carstate.gear > self.GEARS_THIRD and self.carstate.speed > 30):
			self.carstate.bt_metadata = metadata
			self.carstate.info_state = self.INFO_BT

	def carPowered(self):
		if(self.carstate.gear != self.GEARS_PARK):
			amount = (self.carstate.rpm / 100) + self.carstate.speed + (self.carstate.trunk_load / 100)
			self.carstate.fuel -= amount
			if(self.carstate.window_state == self.WINDOWS_DOWN):
				self.carstate.fuel -= 5;
			if(self.carstate.moonroof_state == self.MOONROOF_OPEN):
				self.carstate.fuel -= 2;
			if(self.carstate.info_state != self.INFO_OFF or self.carstate.info_state != self.INFO_AM):
				if(self.carstate.info_volume > 20):
					self.carstate.speed += 1
					self.carstate.rpm += 25

	def openTrunk(self):
		self.write("%c\n" % self.TRUNK_OPEN)
		self.carstate.trunk_state = self.TRUNK_OPEN

	def closeTrunk(self):
		self.write("%c\n" % self.TRUNK_CLOSED)
		self.carstate.trunk_state = self.TRUNK_CLOSED

	def loadTrunk(self):
		weight = random.choice(range(11,100))
		tosend = struct.pack("<BB", int(self.TRUNK_LOAD), weight)
		self.write(tosend + "\n")
		self.carstate.trunk_load += weight

	def unloadTrunk(self):
		weight = random.choice(range(11,100))
		tosend = struct.pack("<BB", int(self.TRUNK_UNLOAD), weight)
		self.write(tosend + "\n")
		if(self.carstate.trunk_load < weight):
			self.carstate.trunk_load = 0
		else:
			self.carstate.trunk_load -= weight

	def setAlarm(self):
		self.write("%c\n" % self.ALARM_SET)
		self.carstate.alarm_state = self.ALARM_SET

	def unsetAlarm(self):
		self.write("%c\n" % self.ALARM_UNSET)
		self.carstate.alarm_state = self.ALARM_UNSET

	def changeVolume(self):
		if(self.carstate.info_state != self.INFO_OFF):
			adjustDirection = random.choice([self.INFO_VOLUP, self.INFO_VOLDOWN])
			amount = random.choice(range(10))
			tosend = struct.pack("<BB", int(adjustDirection), amount)
			self.write(tosend + "\n")
			if(adjustDirection == self.INFO_VOLDOWN):
				if(self.carstate.info_volume < amount):
					self.carstate.info_volume = 0
				else:
					self.carstate.info_volume -= amount
			else:
				self.carstate.info_volume += amount
		else:
			self.write("???\n")


	def alarmTrunk(self):
		self.write("%c%c\n" % (self.ALARM_SET, self.TRUNK_OPEN))
		self.read(expect="***** STACK SMASHING DETECTED! *****", delim="\n")
		self.carstate.boom = True

	def shiftUp(self):
		tosend = ""
		if(self.carstate.rpm > 500 and self.carstate.rpm < 6000):
			if(self.carstate.gear < self.GEARS_FIFTH):
				tosend += "%c" % self.GEARS_CLUTCH
				while(self.carstate.rpm < 800):
					tosend+= "%c"  % self.GEARS_ACCEL
					self.carstate.rpm += 50
				tosend += "%c%c" % (self.GEARS_SHIFTUP, self.GEARS_UNCLUTCH)
				while(self.carstate.speed < ((self.carstate.gear / 0x16) * 10)):
					tosend+= "%c" % self.GEARS_ACCEL
					self.carstate.speed+=1
				tosend+="\n"
				self.write(tosend)
				self.carstate.rpm -= 750
				self.carstate.gear += 0x10
				self.carstate.gear_state = self.GEARS_UNCLUTCH
		else:
			self.write("@@@@@@@@@@@\n")

	def shiftDown(self):
		if(self.carstate.gear > self.GEARS_PARK):
			self.write("%c" % self.GEARS_CLUTCH)
			while(self.carstate.rpm > 5250):
				self.write("%c" % self.GEARS_SLOWDOWN)
				self.carstate.rpm-=25
			self.write("%c%c\n" % (self.GEARS_SHIFTDOWN, self.GEARS_UNCLUTCH))
			self.carstate.rpm+= 750
			self.carstate.gear -= 0x10
			self.carstate.gear_state = self.GEARS_UNCLUTCH

	def revUp(self):
		tosend = "?"
		while(self.carstate.rpm < 550):
			tosend+="%c" % self.GEARS_ACCEL
			if(self.carstate.gear_state == self.GEARS_UNCLUTCH):
				self.carstate.rpm+=25
				self.carstate.speed+=1
			else:
				self.carstate.rpm+=50
		self.write(tosend + "\n")

	def speedUp(self):
		self.write("%c\n" % self.GEARS_ACCEL)
		if(self.carstate.gear_state == self.GEARS_UNCLUTCH):
			self.carstate.speed+=1
			self.carstate.rpm+=25
		else:
			self.carstate.rpm+=50
