#!/usr/bin/env python

from generator.actions import Actions
import random
import string
from struct import pack, unpack, unpack_from

# matches User class in user.h
class User():
    user_id = 0
    weight = 0
    height = 0
    age = 0
    bloodPressure = 0
    bodyFat = 0
    sex = 0

# matches enum in common.h
class Type():
    GENERAL = 0
    REGISTER_SENSOR = 1
    REGISTER_USER = 2
    CHANGE_CURRENT_USER = 3
    INPUT_SENSOR_DATA = 4
    INPUT_MANUAL = 9
    INPUT_SETTINGS = 0x0a
    REQUEST_SENSORS = 0x0b
    REMOVE_SENSOR = 0x0c
    #TEST_VERIFY = 0x0d
    REQUEST_HW_IDS = 0x33
    END = 0xff

class ErrorCodes():
    NO_ERROR = 0
    ERROR_DUPLICATE_SENSOR = 1
    ERROR_BAD_VALUE = 2
    ERROR_NO_USER = 3
    ERROR_SENSOR_NOT_REGISTERED = 4
    ERROR_REG_OTHER_USER = 5
    ERROR_REG_THIS_USER = 6
    ERROR_BAD_SENSOR_MAC = 7
    ERROR_USER_FULL = 8
    ERROR_DUPLICATE_USER = 9
    ERROR_TEST_MAGIC_MISMATCH = 10
    ERROR_TEST_MAGIC_MATCH = 11
    ERROR_FULL_SENSORS = 12


class Service(Actions):

    # header: 
    #  2b sync
    #  2b type
    #  2b data len
    # DATA
    #  depends...

    def send_message( self, pkt_type, pkt_data ):

        data = pack( '2B', 0xc3, 0x3c )

        # add type
        data = data + pack( 'H', pkt_type ) 

        # add the length of the data
        data = data + pack( 'H', len( pkt_data ) ) 

        # now append the data
        data = data + pkt_data

        self.write( data )

    def expect_message( self, pkt_type, pkt_data ):

        data = pack( '2B', 0xc3, 0x3c )

        # add type
        data = data + pack( 'H', 0x0033 )

        # add the length of the data
        data = data + pack( 'H', 3 )

        # add the length of the data
        data = data + pack( 'H', pkt_type )

        # add the length of the data
        data = data + pack( 'B', pkt_data )

        self.read(length=9, expect=data)

    # matches FitnessSensor::GenerateTypeValues() from sensor.cc
    def GenerateTypeValues( self ):
        value = self.magic_page
        offset = 0
        a = 0

        MAX_SENSOR_VALUE = 5 # comes from sensor.h. MUST MATCH

        for i in range( 0, MAX_SENSOR_VALUE ):
            j = 0

            a = ord( value[ offset + j ] )

            while a == 0:
                j += 1
                a = ord( value[ offset + j ] )

            j += 1
            while a in self.magicSensorArray or a == 0:
                a = ord( value[ offset + j ] )
                j += 1
            
            self.magicSensorArray.append( a )
            offset = ord( value[ offset + 1 ] )

    def start(self):

        # track current sensors as list of tuples (id, mac)
        #self.delay(100)
        self.sensorArray = []

        # track users w/ list of Users
        self.userArray = []

        # track current user
        self.currentUser = User()

        self.currentUser.user_id = 0xff;

        # same as m_sensorArray in sensor.h
        # stores the magic_page values
        self.magicSensorArray = []

        self.GenerateTypeValues()

        # test only:

        # magic_nums = ''

        # for x in self.magicSensorArray:
        #     magic_nums = magic_nums + pack('B', x)

        # data = pack( '2B', 0xc3, 0x3c )

        # # add type
        # data = data + pack( 'H', Type.TEST_VERIFY ) 

        # # add the length of the data
        # data = data + pack( 'H', len( magic_nums ) ) 

        # # now append the data
        # data = data + magic_nums

        # self.write( data )

        # self.expect_message( Type.TEST_VERIFY, ErrorCodes.ERROR_TEST_MAGIC_MATCH )


    def top( self ):
        pass

    def get_hw_ids( self ):
        
        if not self.magicSensorArray:
            return

        # send request
        # read response
        # save values in our array
        self.send_message( Type.REQUEST_HW_IDS, pack('B', 0 ) )

        data = ''
        data += pack( '2B', 0xc3, 0x3c )
        data += pack( '2B', 0x44, 0x77 )

        data += pack( 'H', len( self.magicSensorArray ) )
        for ms in self.magicSensorArray:
            data += pack('B', ms)


        # need to read 18B, read array
        self.read( length = len( data ), expect = data )


    def register_user( self ):

        # generate user value
        user = User()

        user.weight = random.randint( 0x0000, 0xffff )
        user.height = random.randint( 0x0000, 0xffff )
        user.user_id = random.randint( 0x0000, 0xffff )

        num_fields = 2
        weight_key = 1
        height_key = 2

        data = pack( 'B', num_fields )
        data += pack( 'H', user.user_id )
        data += pack( '=BH', weight_key, user.weight )
        data += pack( 'B', height_key )
        data += pack( 'H', user.height )

        self.send_message( Type.REGISTER_USER, data )

        code = 0
        found = False

        # is this user ID already in the list?
        for x in self.userArray:
            if x.user_id == user.user_id:
                found = True

        if found == True: # already in user list
            code = ErrorCodes.ERROR_DUPLICATE_USER
        elif len ( self.userArray ) >= 7: # too many users
            code = ErrorCodes.ERROR_USER_FULL
        else: # good, add it
            code = ErrorCodes.NO_ERROR
            self.userArray.append( user )

        self.expect_message( Type.REGISTER_USER, code )

        
    def set_current_user( self ):

        # select user id from the valid id list
        var = random.choice(self.userArray).user_id

        self.currentUser.user_id = var

        message = pack( 'H', var )

        self.send_message( Type.CHANGE_CURRENT_USER, message )

        # expect reponse
        self.expect_message( Type.CHANGE_CURRENT_USER, ErrorCodes.NO_ERROR )

    def register_sensor(self):
        # 2b sync
        # 2b type
        # 2b len
        # DATA
        # 2b sensor id
        # 4b sensor mac
        sensor_id = random.randint( 0x0000, 0xffff )
        selection = random.choice( self.magicSensorArray )
        sensor_mac = selection << 24
        sensor_mac += random.randint( 0x000000, 0xffffff )

        data = pack( 'H', sensor_id )
        data += pack( 'I', sensor_mac )

        self.send_message( Type.REGISTER_SENSOR, data )

        if self.currentUser.user_id == 0xff:
            self.expect_message( Type.REGISTER_SENSOR, ErrorCodes.ERROR_NO_USER )
            return
        
        found = False

        # is this sensor ID already in the list?
        for x in self.sensorArray:
            if x[2] == sensor_mac and self.currentUser.user_id == x[1]:
                # this user has already registered this sensor mac
                found = True
            if x[0] == sensor_id and self.currentUser.user_id == x[1]:
                # this user has already registered this sensor mac
                found = True

        # verify we have 3 or less sensors for this user
        count = 0
        for x in self.sensorArray:
            if self.currentUser.user_id == x[1]:
                count += 1

        if found:
            # repeat sensor
            self.expect_message( Type.REGISTER_SENSOR, ErrorCodes.ERROR_DUPLICATE_SENSOR )
        else:
            if count >= 3:
                self.expect_message( Type.REGISTER_SENSOR, ErrorCodes.ERROR_FULL_SENSORS )
                return
            else:    
                # expect reponse
                self.expect_message( Type.REGISTER_SENSOR, ErrorCodes.NO_ERROR )
                self.sensorArray.append( ( sensor_id, self.currentUser.user_id, sensor_mac ) )

       

    def send_sensor_data(self):

        # 90% real, 10% not real
        ran = random.randint( 0, 9 )
        if ran > 8:
            # 10% chance
            # choose non-real sensor
            sensor_id = random.randint( 0x0000, 0xffff )
            found = True

            # make sure the random number we chose is not a real sensor id
            while found == True:
                found = False
                for sid in self.sensorArray:
                    if sid[0] == sensor_id:
                        found = True
                        sensor_id = random.randint( 0x0000, 0xffff )

            # now we have a sensor id that is not valid
            # send an intentionally incorrect request
            packet_data = ''

            packet_data += pack('H', sensor_id )

            data = random.randint( 0x0000, 0xffff )
            packet_data += pack('H', data )
            
            self.send_message( Type.INPUT_SENSOR_DATA, packet_data )

            # expect error
            self.expect_message( Type.INPUT_SENSOR_DATA, ErrorCodes.ERROR_SENSOR_NOT_REGISTERED )
        else:    
            # this should be successful

            # choose random sensor in the array
            if not self.sensorArray:
                return

            valid_sensors = []
            for sensor in self.sensorArray:
                if sensor[ 1 ] == self.currentUser.user_id:
                    valid_sensors.append( sensor )

            if not valid_sensors:
                return

            chosenSensor = random.choice( valid_sensors )

            packet_data = ''

            # sensor id
            packet_data += pack('H', chosenSensor[0] )

            # random data to send
            data = random.randint( 0x0000, 0xffff )
            packet_data += pack('H', data )
            
            self.send_message( Type.INPUT_SENSOR_DATA, packet_data )

            self.expect_message( Type.INPUT_SENSOR_DATA, ErrorCodes.NO_ERROR )


    def request_sensors(self):
        # send request to system to list all attached sensors
        # system responds with ID and MAC of each sensor

        self.send_message( Type.REQUEST_SENSORS, pack('B', 0 ) )

        data = pack( '2B', 0xc3, 0x3c )

        # add type
        data = data + pack( 'H', 0x0033 )

        pkt_data = ''

        count = 0

        for user in self.userArray:
            if count >= 7:
                break
            for sensor in self.sensorArray:
                if sensor[1] == user.user_id:
                    # generate expected content
                    pkt_data += pack( 'H', sensor[0] )
                    pkt_data += pack( 'I', sensor[2] )
                    
        pkt_len = len( pkt_data )
        # add the length of the data
        data = data + pack( 'H', pkt_len ) 

        data += pkt_data

        self.read(length=len(data), expect=data)
        

    def remove_sensor(self):
        
        # 90% real, 10% not real
        ran = random.randint( 0, 9 )
        if ran > 8:
            # 10% chance
            # choose non-real sensor
            sensor_id = random.randint( 0x0000, 0xffff )
            found = True

            while found == True:
                found = False
                for sid in self.sensorArray:
                    if sid[0] == sensor_id:
                        found = True
                        sensor_id = random.randint( 0x0000, 0xffff )

            # now we have a sensor id that is not valid
            # send an intentionally incorrect request
            self.send_message( Type.REMOVE_SENSOR, pack('H', sensor_id ) )

            # expect error
            self.expect_message( Type.REMOVE_SENSOR, ErrorCodes.ERROR_SENSOR_NOT_REGISTERED )
        else:    
            # this should be successful

            # choose random sensor in the array
            if not self.sensorArray:
                return

            valid_sensors = []
            for sensor in self.sensorArray:
                if sensor[ 1 ] == self.currentUser.user_id:
                    valid_sensors.append( sensor )

            if not valid_sensors:
                return

            chosenSensor = random.choice( valid_sensors )

            self.send_message( Type.REMOVE_SENSOR, pack('H', chosenSensor[0] ) )

            self.expect_message( Type.REMOVE_SENSOR, ErrorCodes.NO_ERROR )

            self.sensorArray.remove( chosenSensor )
            

    def end(self):
        self.send_message( Type.END, pack('B', 0 ) )













