#!/usr/bin/env python

from generator.actions import Actions
import random
import string
from struct import pack, unpack, unpack_from


class StringSearch(Actions):


    def calc_checkval(self, value):


        if value is None:
            return -1

        tmp_token = 0
        count = 1

        for char in value:

            # do all the masking to 32 bits so it will match the C implementation
            tmp_token = ((tmp_token + (ord(char) & 0xff)* count)) & 0xffffffff
            count = count + 1

        return tmp_token


    def send_message(self, message):

        data = pack('H', 0x5AA5)

        # add the length of the message plus the checkvalue
        data = data + pack('H', len(message) + 4)

        # now append the message
        data = data + message

        checkval = self.calc_checkval(data)

        # append the checkvalue and send the message
        data = data + pack('I',checkval)

        self.write(data)


    def start(self):

        #self.delay(100)
        self.simpleresponsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        self.current_temp = 75.0
        self.set_temp = 175
        self.power_on = 0
        self.heater_on = 0
        self.currentProgramStep = -1
        self.smoke_sensor_present = 0
        self.controllerProgram = []
        self.AMBIENT_TEMP = 75
        self.sensorArray = []
        self.rand_byte = 0
        self.time = 0
        self.finished = False
        self.history = []
        self.magiccheckvalue = self.calc_checkval(self.magic_page)

    def top(self):
        pass


    def reset_sensors(self):

        sensorArrayTemp = []
        for x in range(0,len(self.sensorArray)):
            sensorCoeff = self.sensorArray[x][2]
            sensor_address = self.sensorArray[x][1]
            sensor_id = self.sensorArray[x][0]
            sensorTemp = self.AMBIENT_TEMP
            sensorArrayTemp.append([sensor_id, sensor_address, sensorCoeff, sensorTemp])

        self.sensorArray = sensorArrayTemp


    def clear_state(self):

        self.current_temp = 75.0
        self.set_temp = 175
        self.power_on = 0
        self.heater_on = 0
        self.currentProgramStep = -1
        self.smoke_sensor_present = 0
        self.controllerProgram = []
        self.AMBIENT_TEMP = 75
        self.rand_byte = 0
        self.time = 0
        self.history = []
        self.finished = False
        self.reset_sensors()



    def send_power_off(self):

        self.clear_state()
        message = pack('2H', 0x1, 0)
        self.send_message(message)

        
    def send_power_on(self):

        self.power_on = 1;

        message = pack('2H', 0x1, 1)

        self.send_message(message)


    def set_smoke_sensor_on(self):

        self.smoke_sensor_present = 1; 

        message = pack('2H', 0x5, 01)

        self.send_message(message)


    def set_smoke_sensor_off(self):

        self.smoke_sensor_present = 0; 

        message = pack('2H', 0x5, 00)

        self.send_message(message)

    def send_set_ambient_temp(self):
        temperature = random.randint(20, 90)

        message = pack('H', 0xc ) + pack('I', temperature)

        self.send_message(message)

        # if the temp is out of accepted ranges, expect an error reply
        if temperature > 175:
            responsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00)

        # otherwise, a normal response and save the temp value we send
        else:
            responsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
            self.AMBIENT_TEMP = temperature

        self.read(length=12, expect=responsebytes)

    def send_set_temp(self):
        temperature = random.randint(150, 400)

        message = pack('2H', 0x2, temperature)

        self.send_message(message)

        # if the temp is out of accepted ranges, expect an error reply
        if temperature < 175 or temperature > 350:
            responsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00)

        # otherwise, a normal response and save the temp value we send
        else:
            responsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
            self.set_temp = temperature

        self.read(length=12, expect=responsebytes)


    def read_simple_response(self):

        self.read(length=12, expect=self.simpleresponsebytes)


    def send_get_status(self):

        message = pack('4H', 0x8, 00, 00, 00)

        self.send_message(message)


    def read_status_response(self):

        responsebytes = pack('6I', 0x10a, self.set_temp, self.current_temp, self.power_on, self.heater_on, self.smoke_sensor_present)
        responsebytes = pack('8BI', 0xa5, 0x5a, 0x0a, 0x01, 0x01, 0x00, 0x08, 0x00, len(responsebytes)) + responsebytes
  
        self.read(length=len(responsebytes), expect=responsebytes)



    def update_program(self):


        number_of_steps = random.randint(1, 10)

        message = pack('2H', 6, number_of_steps)

        controllerMessage = ''
        controllerProgramTemp = []

        error_sent = False

        responsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)

        for x in range (0, number_of_steps):


            if len(self.sensorArray) > 0:

                sensor_idx = random.randint(0, len(self.sensorArray)-1)
                sensor_id = self.sensorArray[sensor_idx][0]
            else:
                sensor_id = 0

            step_type = random.randint(0,1)

            temperature = random.randint(175, 350)

            # timeval from 30 mins to 4 hours
            timeval = random.randint(30*60, 240*60)


            # now randomly decide if bad values should be sent.  Low percentage chance
            bad_data = random.randint(0, 25000)

            if bad_data == 00000 and step_type == 0:

                sensor_id = random.randint(13, 0xffff)
                responsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00)
                error_sent = True;


            elif bad_data == 10101:

                temperature = random.randint(351, 600)
                responsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00)
                error_sent = True;

            elif bad_data == 20202 and step_type == 1:
 
                timeval = random.randint(0, 1799)
                responsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00)
                error_sent = True;

            if step_type == 0:

                controllerMessage = controllerMessage + pack('3I', step_type, sensor_id, temperature)
                controllerProgramTemp.append((step_type, sensor_id, temperature))
            else:
                controllerMessage = controllerMessage + pack('3I', step_type, timeval, temperature)
                controllerProgramTemp.append((step_type, timeval, temperature))

        message = message + controllerMessage;

        self.send_message(message)

        if error_sent == False:
            self.clear_state()
            self.reset_sensors()
            self.controllerProgram = controllerProgramTemp
            self.currentProgramStep = 0;

        self.read(length=len(responsebytes), expect=responsebytes)

    def send_get_program(self):

        message = pack('2H', 0x7, 00)

        self.send_message(message)

    def send_add_sensor(self):


        sensor_id = random.randint(1, 12)
        sensor_address = sensor_id * 1000
        sensor_temp = self.AMBIENT_TEMP
        coefficient = (random.randint(1, 100) * 100)
        self.rand_byte += 1
        message = pack('2H3I', 3, sensor_id, sensor_address, coefficient, sensor_temp)

        self.send_message(message)

        # now time to decide what response to expect

        # first see if the array is "full" as we only allow for 10
        if len([item for item in self.sensorArray if item[0]==sensor_id]) > 0:#sensor_id in use
            responsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00)

        # or is the sensor array full
        elif len(self.sensorArray) == 10:
            responsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00)

        # all good, so save a copy of what we are sending to the service
        else:
            self.sensorArray.append((sensor_id, sensor_address, coefficient, sensor_temp))
            responsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)


        # now get the response message
        self.read(length=12, expect=responsebytes)


    def remove_sensor(self):


        sensor_id = random.randint(1, 12)

        message = pack('2H', 4, sensor_id)

        self.send_message(message)

        # now time to decide what response to expect

        if len([item for item in self.sensorArray if item[0]==sensor_id]) > 0:
            responsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
            
            # delete the sensor from our local copy
            for x in xrange(len(self.sensorArray)-1, -1, -1):
                if self.sensorArray[x][0] == sensor_id:
                    del self.sensorArray[x]
                    break

        # a bad sensor ID was chosen so expect an error response
        else:

            responsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00)


        # now get the response message
        self.read(length=12, expect=responsebytes)


    def read_controller_program(self):

        if (len(self.controllerProgram) == 0):
            responsebytes = pack('8BI', 0xa5, 0x5a, 0x0a, 0x01, 0x01, 0x00, 0x07, 0x00, 0x00)
        else:
#            responsebytes = pack('8BI', 0xa5, 0x5a, 0x0a, 0x01, 0x01, 0x00, 0x07, 0x00, len(self.controllerProgram)) + self.controllerProgram
            responsebytes = pack('8BI', 0xa5, 0x5a, 0x0a, 0x01, 0x01, 0x00, 0x07, 0x00, len(self.controllerProgram)*12)
            for x in range(0,len(self.controllerProgram)):
                step_type = self.controllerProgram[x][0]
                sensorIDOrTime = self.controllerProgram[x][1]
                temp = self.controllerProgram[x][2]
                responsebytes = responsebytes + pack('3I', step_type, sensorIDOrTime, temp)
  
        self.read(length=len(responsebytes), expect=responsebytes)

    def send_get_sensor(self):

        message = pack('2H', 0xb, 00)

        self.send_message(message)        

    def read_sensor(self):
        responsebytes = pack('8B', 0xa5, 0x5a, 0x0a, 0x01, 0x01, 0x00, 0x0b, 0x00)
        responsebytes = responsebytes + pack('1I',(len(self.sensorArray)*16)) 
        for x in range(0,len(self.sensorArray)):
            sensor_id = self.sensorArray[x][0]
            sensor_address = self.sensorArray[x][1]
            sensorCoef = self.sensorArray[x][2]
            sensorTemp = self.sensorArray[x][3]
            responsebytes = responsebytes + pack('4I', sensor_id, sensor_address, sensorCoef, int(sensorTemp))
        self.read(length=len(responsebytes), expect=responsebytes)        


    def update_sensors(self):

        sensorArrayTemp = []
        for x in range(0,len(self.sensorArray)):
            sensorTemp = self.sensorArray[x][3]
            sensorCoeff = self.sensorArray[x][2]
            sensor_address = self.sensorArray[x][1]
            sensor_id = self.sensorArray[x][0]
            factor = 0.5 + float(sensorCoeff)/float(20000)
            base = float(self.current_temp) - float(sensorTemp)
            adjustment = float(base) * float(factor)
            sensorTemp = float(sensorTemp) + float(adjustment)
            sensorArrayTemp.append([sensor_id, sensor_address, sensorCoeff, sensorTemp])

        self.sensorArray = sensorArrayTemp

    def print_history(self):
        responsebytes = pack('8B', 0xa5, 0x5a, 0x0a, 0x01, 0x01, 0x00, 0x0c, 0x00)
        responsebytes = responsebytes + pack('1I',(len(self.history)))
        for x in range(0,len(self.history)):
            responsebytes = responsebytes + self.history[x]
        self.read(length=len(responsebytes), expect=responsebytes)
	self.read(length=4, expect=pack('I',self.AMBIENT_TEMP))
	self.read(length=4, expect=pack('I',self.set_temp))

    def get_sensor_temp_by_id(self,sensorID):

        for x in range(0, len(self.sensorArray)):
            if (self.sensorArray[x][0] == sensorID):
                return self.sensorArray[x][3]
        return None

    def check_program(self):
        sensorTemp = None
        if (self.currentProgramStep >= len(self.controllerProgram)):
            self.finished = True

            return

        thisStep = self.controllerProgram[self.currentProgramStep]
        steptype = thisStep[0]

        if (steptype == 0):
            sensorTemp = self.get_sensor_temp_by_id(thisStep[1])
            if (sensorTemp == None):
                self.currentProgramStep += 1

                return

            if ( (int(sensorTemp)+5) > int(self.set_temp) ):
                self.set_temp = thisStep[2]
                self.currentProgramStep += 1

                return

        if (steptype == 1):
            if (self.time > thisStep[1]):
                self.set_temp = thisStep[2]
                self.currentProgramStep += 1
        return

    def simulate_temp_change(self):


        number_of_seconds = random.randint(100, 200)

        message = pack('2H', 0x9, number_of_seconds)
        self.send_message(message)

        for i in range(0, number_of_seconds):

            if self.power_on == 1:

                if self.heater_on == 1:

                    self.current_temp = (float(self.current_temp) + 1.0)

                    if float(self.current_temp) > ((float(self.set_temp) + 5)):
                        self.heater_on = 0

                else:

                    if float(self.current_temp) > (float(self.AMBIENT_TEMP)):

                        self.current_temp = (float(self.current_temp) - 0.25)

                    if float(self.current_temp) < (float(self.set_temp) - 5):
                        self.heater_on = 1
            #end if self.power_on == 1
            else:

                if self.current_temp > float(self.AMBIENT_TEMP):

                    self.current_temp = float(self.current_temp) - 0.25


            self.update_sensors()
            if (self.currentProgramStep > -1):
                self.check_program()
                if (self.finished):
                    self.print_history()
                    self.clear_state()
                    return
            if (self.time%60 ==0):
                self.history.append(pack('I',int(self.current_temp)))    
            self.time = self.time + 1
        #end for()

        responsebytes = pack('8BI', 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x09, 0x00, self.time)
        self.read(length=len(responsebytes), expect=responsebytes)


    def end_finish(self):

        # tell the controller to exit normally
        message = pack('4H', 0xff, 00, 00, 00)

        self.send_message(message)

	return -1

    # send bad command codes to the controller
    def bad_command(self):

        #all command codes except Terminate are less than 0xb
        command = random.randint(0xd, 0xffff)

        # 0xff is valid so don't send that one
        if command == 0xff:
            command = 0x100

        message = pack('6H', command, 0, 0, 0, 0, 0)

        self.send_message(message)

        errorresponsebytes = pack('12B', 0xa5, 0x5a, 0x0a, 0x01, 0x0, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00)

        self.read(length=len(errorresponsebytes), expect=errorresponsebytes)


    def validate_firmware(self):


        # just a simple check that the magic page data hasn't been corrupted
        checkvalue = self.calc_checkval(self.magic_page)

        message = pack('4H', 0xa, 00, 00, 00)

        self.send_message(message)


        responsebytes = pack('8BII', 0xa5, 0x5a, 0x0a, 0x01, 0x01, 0x00, 0x0a, 0x00, 0x4, checkvalue)
  
        self.read(length=len(responsebytes), expect=responsebytes)
       
