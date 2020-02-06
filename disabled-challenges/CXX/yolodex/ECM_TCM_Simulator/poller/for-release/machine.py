#!/usr/bin/env python

from generator.actions import Actions
import random
import struct
import string
import math
import binascii
import operator

class SimCommand( ):
	def __init__(self, source_id, dest_id, command_time, command_data ):
		self.source_id = source_id
		self.dest_id = dest_id
		self.command_time = command_time
		self.command_data = command_data

	def __lt__(self, other):
		return self.command_time < other.command_time

class LanbusMessage( ):
	def __init__(self, source_id, dest_id, msg_data ):
		self.source_id = source_id
		self.dest_id = dest_id
		self.msg_data = msg_data

class Simulation(Actions):
    
    
	def read_sim_commands(self):
		self.read( delim='\n', expect='Enter Command Type:\n' )
		self.read( delim='\n', expect='0 - Read EGT\n' )
		self.read( delim='\n', expect='1 - Read RPM\n' )
		self.read( delim='\n', expect='2 - Read IAT\n' )
		self.read( delim='\n', expect='3 - Read O2_1\n' )
		self.read( delim='\n', expect='4 - Read O2_2\n' )
		self.read( delim='\n', expect='5 - Read Engine Temp\n' )
		self.read( delim='\n', expect='6 - Read Engine Torque\n' )
		self.read( delim='\n', expect='7 - Start Engine\n' )
		self.read( delim='\n', expect='8 - Stop Engine\n' )
		self.read( delim='\n', expect='9 - Set Throttle Position\n' )
		self.read( delim='\n', expect='10 - Set Engine Load\n' )
		self.read( delim='\n', expect='11 - Send Binary Message\n' )
	
	def exit_simulation( self ):
		# Stop simulation
		if ( self.ts_idx >= 1024 ):
			self.ts_idx = 0

		self.ts += struct.unpack( 'I', self.magic_page[ self.ts_idx*4 : (self.ts_idx+1)*4 ] )[0]

		self.ts &= 0x7FFFF
	
		self.ts_idx += 1
		
		self.read( delim='? ', expect=('Run another simulation (TS=%d) (y/n)? ' % (self.ts+1452975600)) )

		self.write( 'n\n' )

	def done( self ):
		pass

	def restart( self ):
		# Restart simulation
		if ( self.ts_idx >= 1024 ):
			self.ts_idx = 0

		self.ts += struct.unpack( 'I', self.magic_page[ self.ts_idx*4 : (self.ts_idx+1)*4 ] )[0]

		self.ts &= 0x7FFFF
		
		self.ts_idx += 1
	
		self.read( delim='? ', expect=('Run another simulation (TS=%d) (y/n)? ' % (self.ts+1452975600)) )

		if ( self.poll_depth_count > 5 ):
			self.write( 'n\n' )

			return -1
		else:
			self.write( 'y\n' )

		self.poll_depth_count += 1

	def start(self):
		#self.delay(100)
		self.ts = struct.unpack( 'I', self.magic_page[0:4] )[0] + struct.unpack( 'I', self.magic_page[4:8] )[0] + struct.unpack( 'I', self.magic_page[8:12] )[0] + struct.unpack( 'I', self.magic_page[12:16] )[0]
		self.ts_idx = 0

		self.ts &= 0x7FFFF
		
		self.read( delim='\n', expect=('START::TS=%d\n' % (self.ts+1452975600)) )

		self.poll_depth_count = 0

	def init_run(self):
		self.SIMULATION_TICK_COUNT_MS = 50
		self.MAX_SIMULATION_TIME_MS = 120000
		self.ECM_ID = 19
		self.ECM_ENGINE_STATE_CHANGE = 0x1

		self.ECM_LANBUS_ID = 0x13

		self.ECM_READ_DATA_TYPE = 0x1
		self.ECM_SET_DATA_TYPE = 0x2
		self.ECM_ACTION_DATA_TYPE = 0x3
		self.ECM_CHECK_EQUIPMENT_TYPE = 0x4

		self.ECM_READ_EGT_COMMAND = 0x1
		self.ECM_READ_RPM_COMMAND = 0x2
		self.ECM_READ_IAT_COMMAND = 0x3
		self.ECM_READ_O2_COMMAND = 0x4
		self.ECM_READ_TEMP_COMMAND = 0x5
		self.ECM_READ_TORQUE_COMMAND = 0x6
		self.ECM_READ_THROTTLEPOS_COMMAND = 0x7

		self.ECM_SET_THROTTLEPOS_COMMAND = 0x1
		self.ECM_SET_TORQUE_COMMAND = 0x2

		self.ECM_SET_RESPONSE_INVALID_FIELD = 0xFD
		self.ECM_SET_RESPONSE_ENGINE_OFF = 0xFE
		self.ECM_SET_RESPONSE_INVALID_LENGTH = 0xFF

		self.ECM_START_ENGINE_COMMAND = 0x1
		self.ECM_STOP_ENGINE_COMMAND = 0x2

		self.ECM_READ_RESPONSE_TYPE = 0x1
		self.ECM_SET_RESPONSE_TYPE = 0x2
		self.ECM_ACTION_RESPONSE_TYPE = 0x3
		self.ECM_CHECK_RESPONSE_TYPE = 0x4
		self.ECM_FAILURE_RESPONSE_TYPE = 0x5

		self.ECM_READ_RESPONSE_EGT = 0x1
		self.ECM_READ_RESPONSE_RPM = 0x2
		self.ECM_READ_RESPONSE_IAT = 0x3
		self.ECM_READ_RESPONSE_O2 = 0x4
		self.ECM_READ_RESPONSE_TEMP = 0x5
		self.ECM_READ_RESPONSE_TORQUE = 0x6
		self.ECM_READ_RESPONSE_THROTTLEPOS = 0x7
		self.ECM_READ_RESPONSE_INVALID_FIELD = 0xFF

		self.ECM_ACTION_ENGINE_OFF = 0x0
		self.ECM_ACTION_ENGINE_ON = 0x1

		self.ECM_CHECK_RESPONSE_INVALID_LENGTH = 0xFF

		self.ECM_FAILURE_INVALID_DATA = 0x1

		self.ECM_ENGINE_MAX_TORQUE = 400

		# TCM
		self.TCM_LANBUS_ID = 0x14

		self.TCM_READ_DATA_TYPE = 0x1
		self.TCM_SET_DATA_TYPE = 0x2
		self.TCM_ACTION_DATA_TYPE = 0x3
		self.TCM_CHECK_EQUIPMENT_TYPE = 0x4

		self.TCM_READ_RESPONSE_TYPE = 0x1
		self.TCM_SET_RESPONSE_TYPE = 0x2
		self.TCM_ACTION_RESPONSE_TYPE = 0x3
		self.TCM_CHECK_RESPONSE_TYPE = 0x4
		self.TCM_FAILURE_RESPONSE_TYPE = 0x5

		self.TCM_READ_WHEELSPEED_COMMAND = 0x1
		self.TCM_READ_INVALID_COMMAND = 0xFF

		self.TCM_SET_WHEELSPEED_COMMAND = 0x1
		self.TCM_SET_INVALID_COMMAND = 0xFF

		self.TCM_TC_ON_COMMAND = 0x1
		self.TCM_TC_OFF_COMMAND = 0x2
		self.TCM_ACTION_INVALID_COMMAND = 0xFF

		self.TCM_READ_WHEELSPEED_RESPONSE = 0x1
		self.TCM_READ_FAILURE_TC_OFF_RESPONSE = 0xFF

		self.TCM_SET_WHEELSPEED_RESPONSE = 0x1
		self.TCM_SET_FAILURE_TC_OFF_RESPONSE = 0xFF

		self.TCM_ACTION_TC_ENABLE_RESPONSE = 0x1

		self.TCM_FAILURE_INVALID_DATA = 0x1

		self.TCM_CHECK_RESPONSE_INVALID_LENGTH = 0xFF
		
		# Engine settings
		self.ecm_engineRunning = False
		self.ecm_engineRunningLast = False

		self.ecm_engineRPM = 0
		self.ecm_engineEGT = 0
		self.ecm_engineIAT = 75
		self.ecm_engineTemp = 75
		self.ecm_engineTorque = 0
		self.ecm_engineThrottlePos = 0
		self.ecm_engineO2_1 = 0
		self.ecm_engineO2_2 = 0

		# TCM settings
		self.tcm_engineRunning = False
		self.tcm_enableTC = False

		self.tcm_wheelSpeed = [0, 0, 0, 0]

		# List of sent commands
		self.command_list = []
		self.send_list = []
		self.receive_list = []

		# Get ECM check ID's
		self.ecm_check_id = struct.unpack( 'Q', self.magic_page[0:8] )[0]
		self.tcm_check_id = struct.unpack( 'Q', self.magic_page[8:16] )[0]

		self.read(delim=': ', expect='Enter number of simulation commands: ' )

		self.num_sim_commands = random.randint( 0, 7 )

		self.write( '%d\n' % self.num_sim_commands )

	def run( self ):

		for i in xrange(self.num_sim_commands):
			self.read( delim=': ', expect='Enter Source ID: ' )

			random_source_select = random.randint( 0, 4 )
			if ( random_source_select < 2 ):
				source_id = 0x0
			elif ( random_source_select == 2 ):
				source_id = 0xFF
			else:
				source_id = random.randint( 0, 255 )
			
			self.write( '%d\n' % source_id )

			self.read( delim=': ', expect='Enter Dest ID: ' )

			random_dest_select = random.randint( 0, 2 ) 

			if ( random_dest_select == 0 ):
				dest_id = 20
			elif ( random_dest_select == 1 ):
				dest_id = 19
			else:
				dest_id = random.randint( 0, 255 )

			self.write( '%d\n' % dest_id )

			self.read_sim_commands()

			# Pick a sim command
			sim_command_num = random.randint( 0, 11 )

			self.write( '%d\n' % sim_command_num )

			self.read( delim='\n', expect='Enter command time (in ms):\n' )
			self.read( delim='\n', expect='Simulation will send this command at the specified time in the simulation (max 2 minutes of simulation time):\n' )

			sim_command_time = random.randint( 0, 400000 )

			ignore_command = False
			if ( sim_command_time > self.MAX_SIMULATION_TIME_MS ):
				ignore_command = True	

			self.write( '%d\n' % sim_command_time )

			command_data = ''
			if ( sim_command_num == 0 ):
				command_data = self.DoReadEGT()
			elif ( sim_command_num == 1 ):
				command_data = self.DoReadRPM()
			elif ( sim_command_num == 2 ):
				command_data = self.DoReadIAT()
			elif ( sim_command_num == 3 ):
				command_data = self.DoReadO2_1()
			elif ( sim_command_num == 4 ):
				command_data = self.DoReadO2_2()
			elif ( sim_command_num == 5 ):
				command_data = self.DoReadEngineTemp()
			elif ( sim_command_num == 6 ):
				command_data = self.DoReadEngineTorque()
			elif ( sim_command_num == 7 ):
				command_data = self.DoStartEngine()
			elif ( sim_command_num == 8 ):
				command_data = self.DoStopEngine()
			elif ( sim_command_num == 9 ):
				command_data = self.DoSetThrottlePosition()
			elif ( sim_command_num == 10 ):
				command_data = self.DoSetEngineLoad()
			elif ( sim_command_num == 11 ):
				command_data = self.DoSendBinaryMessage( dest_id )

			# Force dest ID
			if ( sim_command_num <= 10 ):
				dest_id = self.ECM_LANBUS_ID

			if ( ignore_command == False and len(command_data) > 0 ):
				self.AddCommand( source_id, dest_id, sim_command_time, command_data )
		
		# Order commands
		#self.command_list = self.command_list.sort()
		self.command_list = sorted(self.command_list, key=operator.attrgetter('command_time') )

		#print "Command List Len = %d\n" % len(self.command_list)
		
		# Run simulation
		self.RunSimulation()


	def RunSimulation( self ):
		self.read( delim='\n', expect='Running simulation:\n' )

		if ( len(self.command_list) == 0 ):
			self.read( delim='\n', expect='0 commands for simulation.\n' )

			return

		last_tick_item = self.command_list[-1]

		if ( last_tick_item == None ):
			return

		last_tick = last_tick_item.command_time / self.SIMULATION_TICK_COUNT_MS
		last_tick += 1

		# Find max tick
		cur_tick = 0
		next_tick_ms = self.SIMULATION_TICK_COUNT_MS

		while cur_tick < last_tick:
			bDidDisplayTick = False

			if ( len(self.command_list) > 0 ):
				while ( len(self.command_list) > 0 and self.command_list[0].command_time < next_tick_ms ):
					# Only display tick on an action	
					if ( bDidDisplayTick == False ):
						bDidDisplayTick = True

						self.read( delim='\n', expect=('[TICK][%d]:\n' % cur_tick) )

					
					send_command = self.command_list.pop(0)

					self.read( delim='\n', expect=('[SENDCMD][TIME=%d][LENGTH=%d][SRC=%d][DEST=%d]\n' % (send_command.command_time, len(send_command.command_data), send_command.source_id, send_command.dest_id)) )

					# Add message to send
					self.receive_list.append( LanbusMessage( send_command.source_id, send_command.dest_id, send_command.command_data ) )

			# ECM then TCM
			self.ECMRun()
			self.TCMRun()

			# Update the message lists
			self.UpdateMessages()

			# Check for return messages
			for recv_msg in self.receive_list:
				if ( recv_msg.dest_id == 0x0 or recv_msg.dest_id == 0xFF ):
					# Only display tick on an action	
					if ( bDidDisplayTick == False ):
						bDidDisplayTick = True

						self.read( delim='\n', expect=('[TICK][%d]:\n' % cur_tick) )

					
					self.read( delim='\n', expect=('[MESSAGE][SRC=%d][DEST=%d][LENGTH=%d]\n' % (recv_msg.source_id, recv_msg.dest_id, len(recv_msg.msg_data))) )

					message_hex_bytes = binascii.hexlify( recv_msg.msg_data )

					self.read( delim='\n', expect=(message_hex_bytes+'\n') )

			cur_tick += 1
			next_tick_ms += self.SIMULATION_TICK_COUNT_MS

		# Simulation completed
		self.read( delim='\n', expect='Simulation complete.\n' )
	
	
	def UpdateMessages( self ):
		del self.receive_list[:]

		#if ( len(self.send_list) > 0 ):
		#	print "Send messages (count=%d)\n" % len(self.send_list)

		self.receive_list = list(self.send_list)

		#if ( len(self.receive_list) > 0 ):
		#	print "Recv messages (count=%d)\n" % len(self.receive_list)
		
		del self.send_list[:]

	def ECMRun( self ):
		for new_msg in self.receive_list:
			#print "Got ECMRun Message\n"	
			if ( new_msg.dest_id == 0xFF ):
				self.ECMReceiveBroadcastMessage( new_msg )
			elif ( new_msg.dest_id == self.ECM_LANBUS_ID ):
				self.ECMReceiveSelfMessage( new_msg )

		self.ECMTick()

	def ECMReceiveBroadcastMessage( self, msg ):
		# Do nothing	
		pass

	def ECMReceiveSelfMessage( self, msg ):
		# Process message
		source_id = msg.source_id
		dest_id = msg.dest_id

		msg_data = msg.msg_data

		response_data = ''
		while True:
			if ( len(msg_data) < 3 ):
				failure_message = struct.pack( 'B', self.ECM_FAILURE_RESPONSE_TYPE ) + struct.pack('H', 1) + struct.pack('B', self.ECM_FAILURE_INVALID_DATA )
				response_data += failure_message
				break

			message_type_id = struct.unpack( 'B', msg_data[0] )[0]
			message_length = struct.unpack( 'H', msg_data[1:3] )[0]
			
			if ( len(msg_data) < (message_length+3) ):
				failure_message = struct.pack( 'B', self.ECM_FAILURE_RESPONSE_TYPE ) + struct.pack('H', 1) + struct.pack('B', self.ECM_FAILURE_INVALID_DATA )
				response_data += failure_message
				break

			#print "Got ECM ReceiveSelfMessage\n"	
			response_data += self.ECMHandleTLVMessage( message_type_id, msg_data[3:message_length+3] )

			msg_data = msg_data[3+message_length:]

			if ( len(msg_data) == 0 ):
				break

		# Process response data
		self.SendMessage( self.ECM_LANBUS_ID, source_id, response_data )

	def ECMHandleTLVMessage( self, message_type_id, msg_data ):
		if ( message_type_id == self.ECM_READ_DATA_TYPE ):
			#print "Got ECM READ_DATA_TYPE\n"	
			if ( len(msg_data) < 1 ):
				return ''

			field_type = struct.unpack( 'B', msg_data[0] )[0]

			response_msg = struct.pack( 'B', self.ECM_READ_RESPONSE_TYPE )
			response_data = ''
			if ( field_type == self.ECM_READ_EGT_COMMAND ):
				response_data = struct.pack( 'B', self.ECM_READ_RESPONSE_EGT ) + struct.pack( 'H', self.ecm_engineEGT )
			elif ( field_type == self.ECM_READ_RPM_COMMAND ):
				response_data = struct.pack( 'B', self.ECM_READ_RESPONSE_RPM ) + struct.pack( 'H', self.ecm_engineRPM )
			elif ( field_type == self.ECM_READ_IAT_COMMAND ):
				response_data = struct.pack( 'B', self.ECM_READ_RESPONSE_IAT ) + struct.pack( 'H', self.ecm_engineIAT )
			elif ( field_type == self.ECM_READ_O2_COMMAND ):
				if ( len(msg_data) < 2 ):
					response_msg = struct.pack( 'B', self.ECM_FAILURE_RESPONSE_TYPE ) + struct.pack( 'H', 1 ) + struct.pack( 'B', self.ECM_FAILURE_INVALID_DATA )
					return (response_msg)

				response_data = struct.pack( 'B', self.ECM_READ_RESPONSE_O2 ) + msg_data[1]

				if ( struct.unpack( 'B', msg_data[1] )[0] == 0 ):
					response_data += struct.pack( 'H', self.ecm_engineO2_1 )
				else:
					response_data += struct.pack( 'H', self.ecm_engineO2_2 )
			elif ( field_type == self.ECM_READ_TEMP_COMMAND ):
				response_data = struct.pack( 'B', self.ECM_READ_RESPONSE_TEMP ) + struct.pack( 'H', self.ecm_engineTemp )
			elif ( field_type == self.ECM_READ_TORQUE_COMMAND ):
				response_data = struct.pack( 'B', self.ECM_READ_RESPONSE_TORQUE ) + struct.pack( 'H', self.ecm_engineTorque )
			elif ( field_type == self.ECM_READ_THROTTLEPOS_COMMAND ):
				response_Data = struct.pack( 'B', self.ECM_READ_RESPONSE_THROTTLEPOS ) + struct.pack( 'H', self.ecm_engineThrottlePos )
			else:
				# Error!!!
				response_data = struct.pack( 'B', self.ECM_READ_RESPONSE_INVALID_FIELD ) + struct.pack( 'B', field_type )

			return response_msg + struct.pack( 'H', len(response_data) ) + response_data

		elif ( message_type_id == self.ECM_SET_DATA_TYPE ):
			if ( len(msg_data) < 3 ):
				return struct.pack( 'B', self.ECM_SET_RESPONSE_TYPE ) + struct.pack( 'H', 1 ) + struct.pack( 'B', self.ECM_SET_RESPONSE_INVALID_LENGTH )

			field_id = struct.unpack( 'B', msg_data[0] )[0]
			set_value = struct.unpack( 'H', msg_data[1:3] )[0]

			if ( field_id == self.ECM_SET_THROTTLEPOS_COMMAND ):
				if self.ecm_engineRunning == False:
					return struct.pack( 'B', self.ECM_SET_RESPONSE_TYPE ) + struct.pack( 'H', 1 ) + struct.pack( 'B', self.ECM_SET_RESPONSE_ENGINE_OFF )

				if ( set_value > 100 ):
					set_value = 100

				if ( set_value < 10 ):
					set_value = 10

				self.ecm_engineThrottlePos = set_value

				return struct.pack( 'B', self.ECM_SET_RESPONSE_TYPE ) + struct.pack( 'H', 3 ) + struct.pack( 'B', self.ECM_SET_THROTTLEPOS_COMMAND ) + struct.pack( 'H', self.ecm_engineThrottlePos )

			elif ( field_id == self.ECM_SET_TORQUE_COMMAND ):
				if self.ecm_engineRunning == False:
					return struct.pack( 'B', self.ECM_SET_RESPONSE_TYPE ) + struct.pack( 'H', 1 ) + struct.pack( 'B', self.ECM_SET_RESPONSE_ENGINE_OFF )

				if ( set_value > self.ECM_ENGINE_MAX_TORQUE ):
					set_value = self.ECM_ENGINE_MAX_TORQUE

				deltaTorque = 0
				newTorque = set_value
				if ( newTorque < self.ecm_engineTorque ):
					deltaTorque = self.ecm_engineTorque - newTorque

					self.ecm_engineRPM -= (deltaTorque * 10)
				else:
					deltaTorque = newTorque - self.ecm_engineTorque
					
					self.ecm_engineRPM += (deltaTorque * 10)

				self.ecm_engineTorque = newTorque
				return struct.pack( 'B', self.ECM_SET_RESPONSE_TYPE ) + struct.pack( 'H', 3 ) + struct.pack( 'B', self.ECM_SET_TORQUE_COMMAND ) + struct.pack( 'H', self.ecm_engineTorque )


		elif ( message_type_id == self.ECM_ACTION_DATA_TYPE ):
			if ( len(msg_data) < 1 ):
				return ''

			field_id = struct.unpack( 'B', msg_data[0] )[0]

			if ( field_id == self.ECM_START_ENGINE_COMMAND ):
				if ( self.ecm_engineRunning == False ):
					# Start engine
					self.ecm_engineRunning = True
					self.ecm_engineRPM = 700
					self.ecm_engineTemp = 90
					self.ecm_engineEGT = 90
					self.ecm_engineIAT = 75
					self.ecm_engineTorque = 0
					self.ecm_engineThrottlePos = 10
					self.ecm_engineO2_1 = 17
					self.ecm_engineO2_2 = 17

				return struct.pack( 'B', self.ECM_ACTION_RESPONSE_TYPE ) + struct.pack( 'H', 1 ) + struct.pack( 'B', self.ECM_ACTION_ENGINE_ON )

			elif ( field_id == self.ECM_STOP_ENGINE_COMMAND ):
				if ( self.ecm_engineRunning == True ):
					# Stop Engine
					self.ecm_engineRunning = False
					self.ecm_engineRPM = 0
					self.ecm_engineTemp = 75
					self.ecm_engineEGT = 0
					self.ecm_engineIAT = 75
					self.ecm_engineTorque = 0
					self.ecm_engineThrottlePos = 0
					self.ecm_engineO2_1 = 0
					self.ecm_engineO2_2 = 0

				return struct.pack( 'B', self.ECM_ACTION_RESPONSE_TYPE ) + struct.pack( 'H', 1 ) + struct.pack( 'B', self.ECM_ACTION_ENGINE_OFF )

			else:
				return ''

		elif ( message_type_id == self.ECM_CHECK_EQUIPMENT_TYPE ):
			if ( len(msg_data) < 8 ):
				# Error
				response_msg = struct.pack( 'B', self.ECM_CHECK_RESPONSE_TYPE ) + struct.pack( 'H', 1 ) + struct.pack( 'B', self.ECM_CHECK_RESPONSE_INVALID_LENGTH )
				return (response_msg)
			else:
				# Check equipment
				check_id = struct.unpack( 'Q', msg_data[0:8] )[0]

				response_msg = struct.pack( 'B', self.ECM_CHECK_RESPONSE_TYPE ) + struct.pack( 'H', 1 )
				if ( check_id == self.ecm_check_id ):
					response_msg += struct.pack( 'B', 1 )
				else:
					response_msg += struct.pack( 'B', 0 )

				return response_msg
		else:
			# Unknown
			return ''

		return ''

	def ECMTick( self ):
		# Broadcast message on state change
		if ( self.ecm_engineRunning != self.ecm_engineRunningLast ):
			response_msg = struct.pack( 'B', self.ECM_ENGINE_STATE_CHANGE ) + struct.pack( 'H', 1 )
			
			if ( self.ecm_engineRunning == True ):
				response_msg += struct.pack( 'B', 1 )
			else:
				response_msg += struct.pack( 'B', 0 )

			self.SendMessage( self.ECM_LANBUS_ID, 0xFF, response_msg )

		self.ecm_engineRunningLast = self.ecm_engineRunning

	def TCMRun( self ):
		for new_msg in self.receive_list:
			if ( new_msg.dest_id == 0xFF ):
				self.TCMReceiveBroadcastMessage( new_msg )
			elif ( new_msg.dest_id == self.TCM_LANBUS_ID ):
				self.TCMReceiveSelfMessage( new_msg )

		self.TCMTick()

	def TCMReceiveBroadcastMessage( self, msg ):
		source_id = msg.source_id
		dest_id = msg.dest_id

		msg_data = msg.msg_data

		if ( source_id == self.ECM_LANBUS_ID ):
			while True:
				if ( len(msg_data) < 3 ):
					break

				message_type_id = struct.unpack( 'B', msg_data[0] )[0]
				message_length = struct.unpack( 'H', msg_data[1:3] )[0]
				
				if ( len(msg_data) < (message_length+3) ):
					break

				inner_data = msg_data[3:3+message_length]

				if ( message_type_id == 0x1 and message_length == 1 ):
					if ( struct.unpack( 'B', inner_data[0] )[0] == 0x1 ):
						self.tcm_engineRunning = True
					elif ( struct.unpack( 'B', inner_data[0] )[0] == 0x0 ):
						self.tcm_engineRunning = False

				msg_data = msg_data[3+message_length:]

				if ( len(msg_data) == 0 ):
					break

	def TCMReceiveSelfMessage( self, msg ):
		# Process message
		source_id = msg.source_id
		dest_id = msg.dest_id

		msg_data = msg.msg_data

		response_data = ''
		while True:
			if ( len(msg_data) < 3 ):
				failure_message = struct.pack( 'B', self.TCM_FAILURE_RESPONSE_TYPE ) + struct.pack('H', 1) + struct.pack('B', self.TCM_FAILURE_INVALID_DATA )
				response_data += failure_message
				break

			message_type_id = struct.unpack( 'B', msg_data[0] )[0]
			message_length = struct.unpack( 'H', msg_data[1:3] )[0]
			
			if ( len(msg_data) < (message_length+3) ):
				failure_message = struct.pack( 'B', self.TCM_FAILURE_RESPONSE_TYPE ) + struct.pack('H', 1) + struct.pack('B', self.TCM_FAILURE_INVALID_DATA )
				response_data += failure_message
				break

			response_data += self.TCMHandleTLVMessage( message_type_id, msg_data[3:message_length+3] )

			msg_data = msg_data[3+message_length:]

			if ( len(msg_data) == 0 ):
				break

		# Process response data
		self.SendMessage( self.TCM_LANBUS_ID, source_id, response_data )

	def TCMHandleTLVMessage( self, message_type_id, msg_data ):
		if ( message_type_id == self.TCM_READ_DATA_TYPE ):
			if ( len(msg_data) < 1 ):
				return ''

			field_type = struct.unpack( 'B', msg_data[0] )[0]

			response_msg = struct.pack( 'B', self.TCM_READ_RESPONSE_TYPE )
			response_data = ''
			if ( field_type == self.TCM_READ_WHEELSPEED_COMMAND ):
				if ( self.tcm_enableTC == False ):
					response_data = struct.pack( 'B', self.TCM_READ_FAILURE_TC_OFF_RESPONSE )
				else:
					if ( len(msg_data) < 2 ):
						return ''

					wheelCount = struct.unpack( 'B', msg_data[1:2] )[0]

					if ( wheelCount > 4 ):
						return ''

					if ( len(msg_data) < (wheelCount+2) ):
						return ''

					pos = 0
					resultList = ''
					while ( pos < wheelCount ):
						wheel_num = struct.unpack( 'B', msg_data[pos+2:pos+3] )[0]

						if ( wheel_num >= 4 ):
							return ''

						resultList += struct.pack( 'H', self.tcm_wheelSpeed[wheel_num] )	
						pos += 1

					response_data = struct.pack( 'B', self.TCM_READ_WHEELSPEED_RESPONSE ) + struct.pack( 'B', wheelCount ) + resultList
			else:
				return ''

			return response_msg + struct.pack( 'H', len(response_data) ) + response_data

		elif ( message_type_id == self.TCM_SET_DATA_TYPE ):
			if ( len(msg_data) < 1 ):
				return ''

			field_id = struct.unpack( 'B', msg_data[0] )[0]

			response_msg = struct.pack( 'B', self.TCM_SET_RESPONSE_TYPE )
			response_data = ''
			if ( field_id == self.TCM_SET_WHEELSPEED_COMMAND ):
				if ( self.tcm_enableTC == False ):
					response_data = struct.pack( 'B', self.TCM_READ_FAILURE_TC_OFF_RESPONSE )
				else:
					if ( len(msg_data) < 2 ):
						return ''

					wheelCount = struct.unpack( 'B', msg_data[1:2] )[0]

					if ( wheelCount > 4 ):
						return ''

					if ( len(msg_data) < ((wheelCount+2)+(wheelCount*3)) ):
						return ''

					pos = 0
					while ( pos < wheelCount ):
						wheel_num = struct.unpack( 'B', msg_data[pos+2:pos+3] )[0]

						if ( wheel_num >= 4 ):
							return ''
				
						wheel_speed = struct.unpack( 'H', msg_data[2+wheelCount+(pos*2):4+wheelCount+(pos*2)] )[0]

						self.tcm_wheelSpeed[wheel_num] = wheel_speed

						pos += 1

					response_data = struct.pack( 'B', self.TCM_SET_WHEELSPEED_RESPONSE ) + struct.pack( 'B', wheelCount ) + msg_data[2:2+wheelCount+(wheelCount*3)]

			else:
				return ''

			return response_msg + struct.pack( 'H', len(response_data) ) + response_data

		elif ( message_type_id == self.TCM_ACTION_DATA_TYPE ):
			if ( len(msg_data) < 1 ):
				return ''

			if ( self.tcm_engineRunning == False ):
				return ''

			field_id = struct.unpack( 'B', msg_data[0] )[0]

			if ( field_id == self.TCM_TC_ON_COMMAND ):
				response_data = struct.pack( 'B', self.TCM_ACTION_RESPONSE_TYPE ) + struct.pack( 'H', 2 ) + struct.pack( 'B', self.TCM_ACTION_TC_ENABLE_RESPONSE ) + struct.pack( 'B', 1 )

				self.tcm_enableTC = True
				return response_data
			elif ( field_id == self.TCM_TC_OFF_COMMAND ):
				response_data = struct.pack( 'B', self.TCM_ACTION_RESPONSE_TYPE ) + struct.pack( 'H', 2 ) + struct.pack( 'B', self.TCM_ACTION_TC_ENABLE_RESPONSE ) + struct.pack( 'B', 0 )

				self.tcm_enableTC = False
				return response_data

		elif ( message_type_id == self.TCM_CHECK_EQUIPMENT_TYPE ):
			if ( len(msg_data) < 8 ):
				# Error
				response_msg = struct.pack( 'B', self.TCM_CHECK_RESPONSE_TYPE ) + struct.pack( 'H', 1 ) + struct.pack( 'B', self.TCM_CHECK_RESPONSE_INVALID_LENGTH )
				return (response_msg)
			else:
				# Check equipment
				check_id = struct.unpack( 'Q', msg_data[0:8] )[0]

				response_msg = struct.pack( 'B', self.TCM_CHECK_RESPONSE_TYPE ) + struct.pack( 'H', 1 )
				if ( check_id == self.ecm_check_id ):
					response_msg += struct.pack( 'B', 1 )
				else:
					response_msg += struct.pack( 'B', 0 )

				return response_msg
		else:
			# Unknown
			return ''

		return ''

	def TCMTick( self ):
		if ( self.tcm_enableTC == True and self.tcm_engineRunning == False ):
			self.tcm_enableTC = False

		if ( self.tcm_enableTC == False ):
			self.tcm_wheelSpeed[0] = 0
			self.tcm_wheelSpeed[1] = 0
			self.tcm_wheelSpeed[2] = 0
			self.tcm_wheelSpeed[3] = 0
		else:	
			self.tcm_wheelSpeed[0] = 300
			self.tcm_wheelSpeed[1] = 300
			self.tcm_wheelSpeed[2] = 300
			self.tcm_wheelSpeed[3] = 300

	def AddCommand( self, source_id, dest_id, command_time, command_data ):
		self.command_list.append( SimCommand( source_id, dest_id, command_time, command_data ) )

	def SendMessage( self, source_id, dest_id, msg_data ):
		self.send_list.append( LanbusMessage( source_id, dest_id, msg_data ) )  
	
	def DoReadEGT( self ):
		inner_data = struct.pack( 'B', self.ECM_READ_EGT_COMMAND )
		command_data = struct.pack('B', self.ECM_READ_DATA_TYPE ) + struct.pack('H', len(inner_data) ) + inner_data
		return command_data

	def DoReadRPM( self ):
		inner_data = struct.pack( 'B', self.ECM_READ_RPM_COMMAND )
		command_data = struct.pack('B', self.ECM_READ_DATA_TYPE ) + struct.pack('H', len(inner_data) ) + inner_data
		return command_data

	def DoReadIAT( self ):
		inner_data = struct.pack( 'B', self.ECM_READ_IAT_COMMAND )
		command_data = struct.pack('B', self.ECM_READ_DATA_TYPE ) + struct.pack('H', len(inner_data) ) + inner_data
		return command_data

	def DoReadO2_1( self ):
		inner_data = struct.pack( 'B', self.ECM_READ_O2_COMMAND ) + struct.pack( 'B', 1 )
		command_data = struct.pack('B', self.ECM_READ_DATA_TYPE ) + struct.pack('H', len(inner_data) ) + inner_data
		return command_data

	def DoReadO2_2( self ):
		inner_data = struct.pack( 'B', self.ECM_READ_O2_COMMAND ) + struct.pack( 'B', 2 )
		command_data = struct.pack('B', self.ECM_READ_DATA_TYPE ) + struct.pack('H', len(inner_data) ) + inner_data
		return command_data

	def DoReadEngineTemp( self ):
		inner_data = struct.pack( 'B', self.ECM_READ_TEMP_COMMAND )
		command_data = struct.pack('B', self.ECM_READ_DATA_TYPE ) + struct.pack('H', len(inner_data) ) + inner_data
		return command_data

	def DoReadEngineTorque( self ):
		inner_data = struct.pack( 'B', self.ECM_READ_TORQUE_COMMAND )
		command_data = struct.pack('B', self.ECM_READ_DATA_TYPE ) + struct.pack('H', len(inner_data) ) + inner_data
		return command_data

	def DoStartEngine( self ):
		inner_data = struct.pack( 'B', self.ECM_START_ENGINE_COMMAND )
		command_data = struct.pack('B', self.ECM_ACTION_DATA_TYPE ) + struct.pack('H', len(inner_data) ) + inner_data
		return command_data

	def DoStopEngine( self ):
		inner_data = struct.pack( 'B', self.ECM_STOP_ENGINE_COMMAND )
		command_data = struct.pack('B', self.ECM_ACTION_DATA_TYPE ) + struct.pack('H', len(inner_data) ) + inner_data
		return command_data

	def DoSetThrottlePosition( self ):
		throttle_pos = random.randint( 0, 2000 )

		self.read( delim=': ', expect='Enter throttle position: ' )
		self.write( '%d\n' % throttle_pos )

		inner_data = struct.pack( 'B', self.ECM_SET_THROTTLEPOS_COMMAND ) + struct.pack( 'H', throttle_pos )
		command_data = struct.pack('B', self.ECM_SET_DATA_TYPE ) + struct.pack('H', len(inner_data) ) + inner_data
		return command_data

	def DoSetEngineLoad( self ):
		engine_load = random.randint( 0, 1000 )

		self.read( delim=': ', expect='Set Engine Load: ' )
		self.write( '%d\n' % engine_load )

		inner_data = struct.pack( 'B', self.ECM_SET_TORQUE_COMMAND ) + struct.pack( 'H', engine_load )
		command_data = struct.pack('B', self.ECM_SET_DATA_TYPE ) + struct.pack('H', len(inner_data) ) + inner_data
		return command_data

	def DoSendBinaryMessage( self, dest_id ):

		binary_message = ''

		while True:
			# Generate a binary message that is not the bug
			binary_message = ''.join(chr(random.randint(0,255)) for _ in range(random.randint(0,100)))

			#binary_message = binascii.unhexlify("010600010406070809")

			if ( dest_id != self.TCM_LANBUS_ID ):
				break

			if ( len(binary_message) < 3 ):
				break

			message_type_id = struct.unpack( 'B', binary_message[0] )[0]
			message_length = struct.unpack( 'H', binary_message[1:3] )[0]
			
			if ( len(binary_message) < (message_length+3) ):
				break

			msg_data = binary_message[3:message_length+3]
				
			if ( len(msg_data) < 1 ):
				break

			field_type = struct.unpack( 'B', msg_data[0] )[0]

			if ( field_type == self.TCM_READ_WHEELSPEED_COMMAND ):
				if ( len(msg_data) < 2 ):
					break

				wheelCount = struct.unpack( 'B', msg_data[1:2] )[0]

				if ( wheelCount > 4 ):
					break

				if ( len(msg_data) < (wheelCount+2) ):
					break

				pos = 0
				resultList = ''
				bad_wheel_number = False
				while ( pos < wheelCount ):
					wheel_num = struct.unpack( 'B', msg_data[pos+2:pos+3] )[0]

					if ( wheel_num >= 4 ):
						bad_wheel_number = True
						break

				if ( bad_wheel_number == False ):
					break
				else:
					print "Redoing binary message, might hit bug\n"

		if ( len(binary_message) == 0 ):
			binary_message_hex = ''
		else:
			binary_message_hex = binascii.hexlify( binary_message )

		self.read( delim=': ', expect='Enter Binary Message (in hex): ' )
		self.write( binary_message_hex + '\n' )

		if ( len(binary_message_hex) == 0 ):
			self.read( delim='\n', expect='Message data empty. Not sending.\n' )
			return ''

		if ( len(binary_message_hex) % 2 != 0 ):
			self.read( delim='\n', expect='Invalid hex message, must be 2-byte aligned.\n' )
			return ''

		if ( len(binary_message) > 1024 ):
			self.read( delim='\n', expect='Invalid hex message, max message length exceeded.\n' )
			return ''

		command_data = binary_message
		return command_data
