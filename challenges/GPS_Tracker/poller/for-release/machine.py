from generator.actions import Actions
import string
import random
import numpy as np
import binascii
import struct

class CROMU_GENWORK():
	def __init__(self, magic_page):
		self.magic_page = magic_page
		self.magic_page_position = 0
		self.magic_page_size = len(magic_page)

		self.magic_matrix = None
		self.magic_matrix_size = 0
		self.magic_matrix_position = 0

	def GenNewMatrix( self ):
		if ( self.magic_matrix is None ):
			pos = 0
			self.magic_matrix = np.zeros( 512, dtype=np.uint32 )

			self.magic_matrix_size = 512
			while pos < self.magic_matrix_size:
				self.magic_matrix[pos] = pos
				pos += 1

		new_matrix_size = self.magic_matrix_size + 512
		if ( new_matrix_size > 4096 ):
			new_matrix_size = 4096

		pos = 0
		generator_pos = 0
		new_matrix = np.zeros( new_matrix_size, dtype=np.uint32 )
		magic_page_last = 0
		while pos < new_matrix_size:
			new_matrix[pos] = (self.magic_page[self.magic_page_position] & 0xA5C1B301)
			new_matrix[pos] = new_matrix[pos] ^ (magic_page_last+(pos+1))

			self.magic_page_position += 1
			if ( self.magic_page_position >= self.magic_page_size ):
				self.magic_page_position = 0

			new_matrix[pos] = new_matrix[pos] ^ self.magic_matrix[generator_pos]
			magic_page_last = new_matrix[pos]

			generator_pos += 1
			if ( generator_pos >= self.magic_matrix_size ):
				generator_pos = 0

			pos += 1

		self.magic_matrix = new_matrix
		self.magic_matrix_size = new_matrix_size
		self.magic_matrix_position = 0

	def GetRandomInternal( self ):
		if ( self.magic_matrix is None ):
			self.GenNewMatrix()

		if ( self.magic_matrix_position >= self.magic_matrix_size ):
			self.GenNewMatrix()

		new_value = self.magic_matrix[self.magic_matrix_position]
		self.magic_matrix_position += 1

		return new_value

	def GetRandomRange( self, start, end ):
		if ( start > end ):
			temp = end
			end = start
			start = temp

		random_range = (end-start)+1

		return (start + self.GetRandomInternal()%random_range)

class GeofencePoint():
	def __init__( self, distance, latDeg, latMin, latSec, longDeg, longMin, longSec ):
		self.distance = distance
		self.latDeg = latDeg
		self.latMin = latMin
		self.latSec = latSec
		self.longDeg = longDeg
		self.longMin = longMin
		self.longSec = longSec


class CROMU00071(Actions):
	def GetLatRadians( self, latDeg, latMin, latSec ):
		radians = 0.0

		if ( latDeg < 90 ):
			radians = -(90 - latDeg)
		else:
			radians = (latDeg - 90)

		radians += (latMin / 60.0)
		radians += (latSec / 3600.0)

		return ((radians * self.INTERNAL_PI) / 180.0)

	def GetLongRadians( self, longDeg, longMin, longSec ):
		radians = 0.0

		if ( longDeg < 180 ):
			radians = -(180 - longDeg)
		else:
			radians = (longDeg - 180)

		radians += (longMin / 60.0)
		radians += (longSec / 3600.0)

		return ((radians * self.INTERNAL_PI) / 180.0)

	def GetGPSDistance( self, coord1, coord2 ):
		# Spherical earth model
		R = 6371000.0

		lat1Radians = self.GetLatRadians( coord1[0], coord1[1], coord1[2] )
		lat2Radians = self.GetLatRadians( coord2[0], coord2[1], coord2[2] )

		long1Radians = self.GetLongRadians( coord1[3], coord1[4], coord1[5] )
		long2Radians = self.GetLongRadians( coord2[3], coord2[4], coord2[5] )

		deltaLat = lat2Radians - lat1Radians
		deltaLong = long2Radians - long1Radians

		S = np.sin(deltaLat/2.0) * np.sin(deltaLat/2.0) + np.cos( lat1Radians ) * np.cos( lat2Radians ) * np.sin( deltaLong/2.0 ) * np.sin( deltaLong/2.0 )
		C = 2.0*np.arctan2( np.sqrt(S), np.sqrt(1.0-S) )

		return (R*C)

	def PackGPSCoordinates( self, latDeg, latMin, latSec, longDeg, longMin, longSec ):
		packed_data = ''

		lat_packed_val = (latDeg * 3600) + (latMin * 60) + latSec
		long_packed_val = (longDeg * 3600) + (longMin * 60) + longSec

		packed_data += chr( (lat_packed_val >> 16) & 0xFF )
		packed_data += chr( (lat_packed_val >> 8) & 0xFF )
		packed_data += chr( (lat_packed_val & 0xFF) )

		packed_data += chr( (long_packed_val >> 16) & 0xFF )
		packed_data += chr( (long_packed_val >> 8) & 0xFF )
		packed_data += chr( (long_packed_val & 0xFF) )

		return packed_data

	def GetCRC8( self, data ):
		crc8 = 0
		for c in data:
			crc8 += ord(c)

		return (crc8 & 0xFF)

	def SendCommand( self, command_num, command_data ):
		send_data = struct.pack( '<B', command_num ) + struct.pack( '<H', len(command_data) ) + command_data
		command_crc8 = self.GetCRC8( send_data )

		send_data += struct.pack( '<B', command_crc8 )

		self.write( send_data )


	def GetResponse( self, expect_command_num, expect_command_response, expect_command ):
		expect_response_header = struct.pack( '<B', expect_command_num ) + struct.pack( '<B', expect_command_response ) + struct.pack( '<H', len(expect_command) )
		self.read( expect=expect_response_header, length=len(expect_response_header) )

		if ( len(expect_command) > 0 ):
			self.read( expect=expect_command, length=len(expect_command) )

		# Check crc
		expect_crc8 = self.GetCRC8( expect_response_header+expect_command )

		self.read( expect=(struct.pack('<B', expect_crc8 )), length=1 )

	def start( self ):
		#self.delay(100)
		self.INTERNAL_PI = 3.1415926536

		self.MAX_GEOFENCE_POINTS = 20

		self.INTERNAL_ERROR_COMMS = 1
		self.INTERNAL_ERROR_BAD_DATA = 2

		self.COMMAND_INFO = 0
		self.COMMAND_SHUTDOWN = 1
		self.COMMAND_DEBUG = 2
		self.COMMAND_UPDATE_GEOFENCE = 3
		self.COMMAND_POSITION = 4
		self.COMMAND_GPS_OFF = 5
		self.COMMAND_GPS_ON = 6
		self.COMMAND_SLEEP = 7
		self.COMMAND_WAKEUP = 8

		self.COMMAND_RESPONSE_OK = 0
		self.COMMAND_RESPONSE_INVALID = 1
		self.COMMAND_RESPONSE_BAD_CHECKSUM = 2
		self.COMMAND_RESPONSE_MAX_POINTS = 3
		self.COMMAND_RESPONSE_SLEEP = 4
		self.COMMAND_RESPONSE_GPS_OFF = 5

		self.GPS_STATE_ON = 0
		self.GPS_STATE_OFF = 1
		self.GPS_STATE_NOT_LOCKED = 2

		self.GEOFENCE_UPDATE_NEW = 0
		self.GEOFENCE_UPDATE_ADD = 1
		self.GEOFENCE_UPDATE_CLEAR = 2

		self.GEOFENCE_RESPONSE_IN_BOUNDS = 0
		self.GEOFENCE_RESPONSE_OUT_OF_BOUNDS = 1

		self.DEBUG_SET_BATTERY_LEVEL = 0
		self.DEBUG_SET_COORDINATES = 1
		self.DEBUG_SET_DEVICE_ID = 2

		self.gps_state_on = False
		self.device_sleep = False

		self.prng = CROMU_GENWORK( np.fromstring( self.magic_page[32:], dtype=np.uint32) )

		self.device_id = self.prng.GetRandomInternal()
		self.battery_level = self.prng.GetRandomRange( 10, 50 )

		self.gps_coords = [ self.prng.GetRandomRange( 30, 160 ), self.prng.GetRandomRange( 0, 59 ), self.prng.GetRandomRange( 0, 59 ), self.prng.GetRandomRange( 0, 359 ), self.prng.GetRandomRange( 0, 59 ), self.prng.GetRandomRange( 0, 59 ) ]
		self.gps_locked = True

		self.geofence_list = [ ]

	def command_main(self):
		# Small chance of sending a bad command (invalid command number or invalid checksum!)
		if ( random.randint( 0, 50 ) == 0 ):
			# Do bad command
			do_bad_checksum = False
			do_bad_command_num = False
			bad_choice = random.randint( 0, 2 )
			if ( bad_choice == 0 ):
				# Bad checksum
				do_bad_checksum = True
			elif ( bad_choice == 1 ):
				do_bad_checksum = True
				do_bad_command_num = True
			else:
				do_bad_command_num = True

			command_num = random.randint( 0, 8 )
			if ( do_bad_command_num ):
				command_num = random.randint( 9, 255 )

			command_data_length = random.randint( 0, 255 )

			command_data = ''
			for i in range(command_data_length):
				command_data += chr( random.randint( 0, 255 ) )

			command_header = struct.pack( '<B', command_num ) + struct.pack( '<H', len(command_data) )

			# Get checksum
			checksum_value = self.GetCRC8( command_header + command_data )

			if ( do_bad_checksum ):
				new_checksum_value = random.randint( 0, 255 )
				while ( new_checksum_value == checksum_value ):
					new_checksum_value = random.randint( 0, 255 )

				checksum_value = new_checksum_value

			# Send bad command
			self.write( command_header + command_data + struct.pack( '<B', checksum_value ) )

			if ( do_bad_checksum ):
				response_data = ''
				self.GetResponse( command_num, self.COMMAND_RESPONSE_BAD_CHECKSUM, response_data )

			else:
				# Check sleep
				if ( self.device_sleep ):
					self.DoSleepResponse( command_num )
					return

				response_data = ''
				self.GetResponse( command_num, self.COMMAND_RESPONSE_INVALID, response_data )

		# Reset point
		# Do nothing
		return

	def DoSleepResponse( self, command_num ):
		sleep_response = ''
		self.GetResponse( command_num, self.COMMAND_RESPONSE_SLEEP, sleep_response )

	def info(self):
		command_data = ''
		self.SendCommand( self.COMMAND_INFO, command_data )

		if ( self.device_sleep ):
			self.DoSleepResponse( self.COMMAND_INFO )
			return

		device_state = 0
		if ( self.gps_state_on ):
			if ( self.gps_locked ):
				device_state = self.GPS_STATE_ON
			else:
				device_state = self.GPS_STATE_NOT_LOCKED
		else:
			device_state = self.GPS_STATE_OFF

		info_command_data = struct.pack( '<B', device_state ) + struct.pack( '<B', self.battery_level ) + struct.pack( '<I', self.device_id )

		# Get Info
		info_response_data = self.GetResponse( self.COMMAND_INFO, self.COMMAND_RESPONSE_OK, info_command_data )


	def debug(self):
		correct_debug_token = struct.unpack( '<Q', self.magic_page[0:8] )[0] ^ 0xDEB4370331337A7F

		# Debug access -- available only with magic page data
		if ( random.randint( 0, 10 ) == 0 ):
			# Bad access
			self.comment( "Bad debug token" )
			new_debug_token = random.randint( 0, 0xFFFFFFFFFFFFFFFF )
			while ( new_debug_token == correct_debug_token ):
				# Extremely unlikely but... just in case lolz
				new_debug_token = random.randint( 0, 0xFFFFFFFFFFFFFFFF )

			debug_command_length = random.randint( 0, 255 )
			command_data = struct.pack( '<Q', new_debug_token )
			command_data += struct.pack( '<B', random.randint( 0, 255 ) )
			command_data += struct.pack( '<B', debug_command_length )

			command_data += struct.pack( '<B', random.randint( 0, 255 ) ) * debug_command_length

			self.SendCommand( self.COMMAND_DEBUG, command_data )

			if ( self.device_sleep ):
				self.DoSleepResponse( self.COMMAND_DEBUG )
				return

			response_data = ''
			self.GetResponse( self.COMMAND_DEBUG, self.COMMAND_RESPONSE_INVALID, response_data )

			return

		# Send correct debug command
		debug_command_num = random.randint( 0, 2 )
		debug_command_inner_data = ''

		if ( debug_command_num == 0 ):
			self.comment( "Debug update battery level" )
			# Set battery level
			new_battery_level = random.randint( 10, 50 )

			debug_command_inner_data = struct.pack( '<B', new_battery_level )

			if ( self.device_sleep == False ):
				self.battery_level = new_battery_level

		elif ( debug_command_num == 1 ):
			self.comment( "Debug update coordinates" )
			# Set coordinates
			new_coords = [ random.randint( 0, 159 ), random.randint( 0, 59 ), random.randint( 0, 59 ), random.randint( 0, 359 ), random.randint( 0, 59 ), random.randint( 0, 59 ) ]

			debug_command_inner_data = self.PackGPSCoordinates( new_coords[0], new_coords[1], new_coords[2], new_coords[3], new_coords[4], new_coords[5] )

			if ( self.device_sleep == False ):
				self.gps_coords = new_coords

		else:
			self.comment( "Debug set device ID" )
			# Set device ID
			new_device_id = random.randint( 0, 0xFFFFFFFF )

			debug_command_inner_data = struct.pack( '<I', new_device_id )

			if ( self.device_sleep == False ):
				self.device_id = new_device_id

		debug_command_data = struct.pack( '<Q', correct_debug_token )
		debug_command_data += struct.pack( '<B', debug_command_num )
		debug_command_data += struct.pack( '<B', len(debug_command_inner_data) )
		debug_command_data += debug_command_inner_data

		self.SendCommand( self.COMMAND_DEBUG, debug_command_data )

		if ( self.device_sleep ):
			self.DoSleepResponse( self.COMMAND_DEBUG )
			return

		# Command succeeded
		self.comment( "Debug command succeeded" )
		response_data = ''
		self.GetResponse( self.COMMAND_DEBUG, self.COMMAND_RESPONSE_OK, response_data )

	def update_geofence(self):
		# Perform geofence command

		# Pick an action
		geofence_action_type = random.randint( 0, 2 )
		geofence_point_count = random.randint( 1, 20 )

		if ( random.randint( 0, 50 ) == 0 ):
			# Send bad action
			geofence_action_type = random.randint( 3, 255 )

			geofence_command_data = ''
			geofence_command_data += struct.pack( '<B', geofence_action_type )
			geofence_command_data += struct.pack( '<B', random.randint( 0, 255 ) )

			geofence_command_data += struct.pack( '<B', random.randint( 0, 255 ) ) * random.randint( 0, 255 )

			self.SendCommand( self.COMMAND_UPDATE_GEOFENCE, geofence_command_data )

			if ( self.device_sleep ):
				self.DoSleepResponse( self.COMMAND_UPDATE_GEOFENCE )
				return

			response_data = ''
			self.GetResponse( self.COMMAND_UPDATE_GEOFENCE, self.COMMAND_RESPONSE_INVALID, response_data )

			return


		if ( geofence_action_type == 0 ):
			if ( random.randint( 0, 30 ) == 0 ):
				# Exceed max points
				geofence_command = ''

				geofence_point_count = random.randint( 21, 255 )

				geofence_command += struct.pack( '<B', geofence_action_type )
				geofence_command += struct.pack( '<B', geofence_point_count )

				geofence_command += struct.pack( '<B', random.randint( 0, 255 ) ) * (10*geofence_point_count)

				self.SendCommand( self.COMMAND_UPDATE_GEOFENCE, geofence_command )

				if ( self.device_sleep ):
					self.DoSleepResponse( self.COMMAND_UPDATE_GEOFENCE )
					return

				response_data = ''
				self.GetResponse( self.COMMAND_UPDATE_GEOFENCE, self.COMMAND_RESPONSE_MAX_POINTS, response_data )

				return

			# New points
			geofence_command_data = ''
			geofence_command_data += struct.pack( '<B', geofence_action_type )
			geofence_command_data += struct.pack( '<B', geofence_point_count )

			new_geofence_list = []
			point_cur = 0
			while point_cur < geofence_point_count:
				# Generate random points
				distance = random.randint( 10000, 3000000 )
				new_point = [ random.randint( 0, 179 ), random.randint( 0, 59 ), random.randint( 0, 59 ), random.randint( 0, 359 ), random.randint( 0, 59 ), random.randint( 0, 59 ) ]

				new_geofence_list.append( GeofencePoint( distance, new_point[0], new_point[1], new_point[2], new_point[3], new_point[4], new_point[5] ) )

				# Send the point data
				geofence_command_data += struct.pack( '<I', distance )
				geofence_command_data += self.PackGPSCoordinates( new_point[0], new_point[1], new_point[2], new_point[3], new_point[4], new_point[5] )

				point_cur += 1

			# Send command
			self.SendCommand( self.COMMAND_UPDATE_GEOFENCE, geofence_command_data )

			# Check for sleep
			if ( self.device_sleep ):
				self.DoSleepResponse( self.COMMAND_UPDATE_GEOFENCE )
				return

			# Set new geofence list
			self.geofence_list = new_geofence_list

		elif ( geofence_action_type == 1 ):
			# Add points

			# Calculate the number of points that can be added
			points_to_add = self.MAX_GEOFENCE_POINTS - len(self.geofence_list)

			if ( geofence_point_count > points_to_add ):
				geofence_point_count = points_to_add

			geofence_command_data = ''
			geofence_command_data += struct.pack( '<B', geofence_action_type )
			geofence_command_data += struct.pack( '<B', geofence_point_count )


			new_geofence_list = []
			for item in self.geofence_list:
				new_geofence_list.append( item )

			point_cur = 0
			while point_cur < geofence_point_count:
				# Generate random points
				distance = random.randint( 10000, 3000000 )
				new_point = [ random.randint( 0, 179 ), random.randint( 0, 59 ), random.randint( 0, 59 ), random.randint( 0, 359 ), random.randint( 0, 59 ), random.randint( 0, 59 ) ]

				new_geofence_list.append( GeofencePoint( distance, new_point[0], new_point[1], new_point[2], new_point[3], new_point[4], new_point[5] ) )

				# Send the point data
				geofence_command_data += struct.pack( '<I', distance )
				geofence_command_data += self.PackGPSCoordinates( new_point[0], new_point[1], new_point[2], new_point[3], new_point[4], new_point[5] )

				point_cur += 1

			# Send command
			self.SendCommand( self.COMMAND_UPDATE_GEOFENCE, geofence_command_data )

			# Check for sleep
			if ( self.device_sleep ):
				self.DoSleepResponse( self.COMMAND_UPDATE_GEOFENCE )
				return

			# Set new geofence list
			self.geofence_list = new_geofence_list

		elif ( geofence_action_type == 2 ):
			# Clear points
			geofence_command_data = ''
			geofence_command_data += struct.pack( '<B', geofence_action_type )
			geofence_command_data += struct.pack( '<B', 0 )

			self.SendCommand( self.COMMAND_UPDATE_GEOFENCE, geofence_command_data )

			if ( self.device_sleep ):
				self.DoSleepResponse( self.COMMAND_UPDATE_GEOFENCE )
				return

			# Clear geofence list
			self.geofence_list = [ ]

			response_data = ''
			self.GetResponse( self.COMMAND_UPDATE_GEOFENCE, self.COMMAND_RESPONSE_OK, response_data )

			# Exit -- no need to check geofence list as it is empty
			return

		# Check GPS state
		if ( self.gps_state_on == False ):
			response_data = ''
			self.GetResponse( self.COMMAND_UPDATE_GEOFENCE, self.COMMAND_RESPONSE_GPS_OFF, response_data )

			return

		# Evaluate geofence points
		for point in self.geofence_list:
			# Check distances
			gps_coord2 = [ point.latDeg, point.latMin, point.latSec, point.longDeg, point.longMin, point.longSec ]
			distance = self.GetGPSDistance( self.gps_coords, gps_coord2 )

			if ( distance > point.distance ):
				response_data = ''
				response_data += struct.pack( '<B', self.GEOFENCE_RESPONSE_OUT_OF_BOUNDS )
				response_data += self.PackGPSCoordinates( point.latDeg, point.latMin, point.latSec, point.longDeg, point.longMin, point.longSec )
				response_data += struct.pack( '<I', distance )

				self.GetResponse( self.COMMAND_UPDATE_GEOFENCE, self.COMMAND_RESPONSE_OK, response_data )
				return

		# Nothing outside of boundsa

		# Getting potentially uninit data, manually receive response
		self.comment( "All geofence points in bounds" )
		response_data = struct.pack( '<B', self.COMMAND_UPDATE_GEOFENCE ) + struct.pack( '<B', self.COMMAND_RESPONSE_OK ) + struct.pack( '<H', 11 ) + struct.pack( '<B', self.GEOFENCE_RESPONSE_IN_BOUNDS )

		self.read( expect=response_data, length=5 )
		self.read( length=6 )
		self.read( expect='\x00\x00\x00\x00', length=4 )
		self.read( length=1 )

		return

	def position(self):
		command_data = ''
		self.SendCommand( self.COMMAND_POSITION, command_data )

		if ( self.device_sleep ):
			self.DoSleepResponse( self.COMMAND_POSITION )
			return

		device_state = 0
		if ( self.gps_state_on ):
			if ( self.gps_locked ):
				device_state = self.GPS_STATE_ON
			else:
				device_state = self.GPS_STATE_NOT_LOCKED
		else:
			device_state = self.GPS_STATE_OFF

		if ( device_state == self.GPS_STATE_ON ):
			# Read coordinates
			packed_coordinates = self.PackGPSCoordinates( self.gps_coords[0], self.gps_coords[1], self.gps_coords[2], self.gps_coords[3], self.gps_coords[4], self.gps_coords[5] )

			response_data = struct.pack( '<B', device_state ) + packed_coordinates
			self.GetResponse( self.COMMAND_POSITION, self.COMMAND_RESPONSE_OK, response_data )

		else:
			header_data = struct.pack( '<B', self.COMMAND_POSITION ) + struct.pack( '<B', self.COMMAND_RESPONSE_OK ) + struct.pack( '<H', 7 )

			# Un-initialized memory here, just read past it
			self.read( expect=(header_data+struct.pack('B', device_state )), length=len(header_data)+1 )
			self.read( length=7 )

		# Do position command
		return

	def gps_on(self):
		# GPS On command
		command_data = ''
		self.SendCommand( self.COMMAND_GPS_ON, command_data )

		if ( self.device_sleep ):
			self.DoSleepResponse( self.COMMAND_GPS_ON )
			return

		# Turn on gps
		self.gps_state_on = True

		response_data = ''
		self.GetResponse( self.COMMAND_GPS_ON, self.COMMAND_RESPONSE_OK, response_data )

	def gps_off(self):
		# GPS Off command
		command_data = ''
		self.SendCommand( self.COMMAND_GPS_OFF, command_data )

		if ( self.device_sleep ):
			self.DoSleepResponse( self.COMMAND_GPS_OFF )
			return

		# Turn off gps
		self.gps_state_on = False

		response_data = ''
		self.GetResponse( self.COMMAND_GPS_OFF, self.COMMAND_RESPONSE_OK, response_data )

	def sleep(self):
		# Sleep command
		command_data = ''
		self.SendCommand( self.COMMAND_SLEEP, command_data )

		if ( self.device_sleep ):
			self.DoSleepResponse( self.COMMAND_SLEEP )
			return

		self.device_sleep = True

		response_data = ''
		self.GetResponse( self.COMMAND_SLEEP, self.COMMAND_RESPONSE_OK, response_data )

		return

	def wakeup(self):
		# Wakeup command
		command_data = ''
		self.SendCommand( self.COMMAND_WAKEUP, command_data )

		self.device_sleep = False

		response_data = ''
		self.GetResponse( self.COMMAND_WAKEUP, self.COMMAND_RESPONSE_OK, response_data )

	def shutdown(self):
		# shutdown command
		command_data = ''
		self.SendCommand( self.COMMAND_SHUTDOWN, command_data )

		response_data = ''
		self.GetResponse( self.COMMAND_SHUTDOWN, self.COMMAND_RESPONSE_OK, response_data )
