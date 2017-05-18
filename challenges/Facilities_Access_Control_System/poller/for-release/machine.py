#!/usr/bin/env python

from generator.actions import Actions, Variable
from struct import *
from random import *
import struct

class MyClass(Actions):
    CMD_ADD_USER = 0
    CMD_DEL_USER = 1
    CMD_ADD_DEVICE = 2
    CMD_DEL_DEVICE = 3
    CMD_POWER_OFF = 4
    CMD_GRANT_ACCESS = 5
    CMD_UPDATE_DEVICE = 6
    CMD_ADD_DEVICE_TO_ALARM = 7
    CMD_LIST_ALARM_CODES = 8

    RESP_INVALID_CMD = 0
    RESP_MAX_USERS = 1
    RESP_ADD_USER_FAILED = 2
    RESP_SUCCESS = 3
    RESP_DEL_USER_FAILED = 4
    RESP_ADD_DEVICE_FAILED = 5
    RESP_DEL_DEVICE_FAILED = 6
    RESP_GRANT_FAILED = 7
    RESP_UPDATE_DEVICE_FAILED = 8
    RESP_ADD_DEVICE_TO_ALARM_FAILED = 9
    RESP_ALARM_ON = 10
    RESP_ALARM_OFF = 11
    RESP_LIST_ALARM_CODES = 12

    MAX_USERS = 128
    PIN_LEN = 6
    ACCESS_CODE_LEN = 32

    MAX_DEVICES = 128
    DEVICE_UNUSED = 0
    DEVICE_KEYPAD = 1
    DEVICE_SWIPE = 2
    DEVICE_CONTACT = 3
    DEVICE_MOTION = 4
    DEVICE_HEAT = 5
    DEVICE_SMOKE = 6
    DEVICE_ALARM = 7

    CONTACT_NO = 0
    CONTACT_NC = 1
    CONTACT_OPEN = 0
    CONTACT_CLOSED = 1

    MOTION_INACTIVE = 0
    MOTION_ACTIVE = 1

    SMOKE_INACTIVE = 0
    SMOKE_ACTIVE = 1

    ALARM_DISARMED = 0
    ALARM_ARMED = 1
    ALARM_INACTIVE = 0
    ALARM_ACTIVE = 1

    Users = dict()
    Devices = dict()

    MagicIndex = 0

    def random_string(self, min_length, max_length):
        return ''.join(chr(randint(1,255)) for _ in range(randint(min_length, max_length)))

    def random_numeric_string(self, min_length, max_length):
        return ''.join(chr(randint(0x30,0x39)) for _ in range(randint(min_length, max_length)))

    def random_hex_string(self, min_length, max_length):
        return ''.join(chr(choice([randint(0x30,0x39),randint(0x41,0x46)])) for _ in range(randint(min_length, max_length)))

    def NewDeviceId(self):
        DeviceId = unpack("<L", self.magic_page[self.MagicIndex:self.MagicIndex+4])[0] % 65534
        self.MagicIndex += 4;
        while self.FindDeviceId(DeviceId) != self.MAX_DEVICES or DeviceId == 0:
            DeviceId = unpack("<L", self.magic_page[self.MagicIndex:self.MagicIndex+4])[0] % 65534
            self.MagicIndex += 4;
        return DeviceId

    def InitProgram(self):
        self.MagicIndex = 0

    def SendCommand(self, Command):
        cmd = pack("B", Command)
        self.write(cmd)

    def ReceiveOkResponse(self, Data):
        resp = pack("B", self.RESP_SUCCESS)
        self.read(length=len(resp), expect=resp)
        resp = pack("<H", Data)
        self.read(length=2, expect=resp)

    def ReceiveResponse(self, Code, Data):
        resp = pack("B", Code)
        self.read(length=len(resp), expect=resp)
        resp = pack("<H", Data)
        self.read(length=2, expect=resp)

    def FindAvailableUserIndex(self):
        ExistingUserIndexes = self.Users.keys()
        for i in range(0, self.MAX_USERS):
            if i not in ExistingUserIndexes:
                    return i
        return self.MAX_USERS

    def FindAvailableDeviceIndex(self):
        ExistingDeviceIndexes = self.Devices.keys()
        for i in range(0, self.MAX_DEVICES):
            if i not in ExistingDeviceIndexes:
                    return i
        return self.MAX_DEVICES

    def IsUserUnique(self, Username, Pin, Code):
        for u in self.Users.keys():
            if (self.Users[u])['Username'] == Username:
                return 0
            if (self.Users[u])['Pin'] == Pin:
                return 0
            if (self.Users[u])['Code'] == Code:
                return 0

        return 1

    def AddRandomUser(self):
        self.comment("Add Random User");
        # get the next available index
        UserIndex = self.FindAvailableUserIndex()

        # generate a uniqe user
        Username = self.random_string(1, 31)
        First = self.random_string(1, 31)
        Last = self.random_string(1, 31)
        Pin = self.random_numeric_string(5, 5)
        AccessCode = self.random_hex_string(31, 31)
        while not self.IsUserUnique(Username, Pin, AccessCode):
            Username = self.random_string(1, 31)
            Pin = self.random_numeric_string(5, 5)
            AccessCode = self.random_hex_string(31, 31)

        # add the user
        self.AddUser(Username, First, Last, Pin, AccessCode)

        # if we're at our user count limit, detect the failure
        if UserIndex >= self.MAX_USERS:
            self.ReceiveResponse(self.RESP_ADD_USER_FAILED, 0)
        else:
            # otherwise, success
            self.Users[UserIndex] = { 'Username': Username, 'First': First, 'Last': Last, 'Pin': Pin, 'Code': AccessCode }
            self.ReceiveOkResponse(0)
        return(UserIndex)

    def BadRandomUser(self):
        Choice = randint(0,2)

        if Choice == 0:
            self.AddDuplicateUser()
        elif Choice == 1:
            self.AddInvalidUser()
        elif Choice == 2:
            self.DelInvalidUser()

    def AddDuplicateUser(self):
        self.comment("Add Duplicate User")
        if not self.Users:
            self.AddRandomUser()
        UserIndex = choice(self.Users.keys())
        Username = (self.Users[UserIndex])['Username']
        First = (self.Users[UserIndex])['First']
        Last = (self.Users[UserIndex])['Last']
        Pin = (self.Users[UserIndex])['Pin']
        AccessCode = (self.Users[UserIndex])['Code']
        self.AddUser(Username, First, Last, Pin, AccessCode)
        self.ReceiveResponse(self.RESP_ADD_USER_FAILED, 0)

    def AddInvalidUser(self):
        Type = randint(0,2)
        if Type == 0:
            # incorrent length pin
            self.comment("Add User with incorrect pin")
            Username = self.random_string(1, 31)
            First = self.random_string(1, 31)
            Last = self.random_string(1, 31)
            Pin = self.random_numeric_string(1, 4)
            AccessCode = self.random_hex_string(31, 31)
            while not self.IsUserUnique(Username, Pin, AccessCode):
                Username = self.random_string(1, 31)
                Pin = self.random_numeric_string(1, 4)
                AccessCode = self.random_hex_string(31, 31)
            self.AddUser(Username, First, Last, Pin, AccessCode)
            self.ReceiveResponse(self.RESP_ADD_USER_FAILED, 0)
        elif Type == 1:
            # incorrect length code
            self.comment("Add User with incorrect code")
            Username = self.random_string(1, 31)
            First = self.random_string(1, 31)
            Last = self.random_string(1, 31)
            Pin = self.random_numeric_string(5, 5)
            AccessCode = self.random_hex_string(1, 30)
            while not self.IsUserUnique(Username, Pin, AccessCode):
                Username = self.random_string(1, 31)
                Pin = self.random_numeric_string(5, 5)
                AccessCode = self.random_hex_string(1, 30)
            self.AddUser(Username, First, Last, Pin, AccessCode)
            self.ReceiveResponse(self.RESP_ADD_USER_FAILED, 0)
        elif Type == 2:
            # duplicate code
            self.comment("Add User with duplicate code")
            Username = self.random_string(1, 31)
            First = self.random_string(1, 31)
            Last = self.random_string(1, 31)
            Pin = self.random_numeric_string(5, 5)
            AccessCode = self.random_hex_string(31, 31)
            while not self.IsUserUnique(Username, Pin, AccessCode):
                Username = self.random_string(1, 31)
                Pin = self.random_numeric_string(5, 5)
                AccessCode = self.random_hex_string(31, 31)
            if not self.Users:
                self.AddRandomUser()
            UserIndex = choice(self.Users.keys())
            AccessCode = (self.Users[UserIndex])['Code']
            self.AddUser(Username, First, Last, Pin, AccessCode)
            self.ReceiveResponse(self.RESP_ADD_USER_FAILED, 0)

    def AddUser(self, Username, First, Last, Pin, AccessCode):
        self.comment("Add User")
        self.SendCommand(self.CMD_ADD_USER)
        request =  Username.ljust(32, '\0')
        request += First.ljust(32, '\0')
        request += Last.ljust(32, '\0')
        request += Pin.ljust(6, '\0')
        request += AccessCode.ljust(32, '\0')
        self.write(request)

    def DelRandomUser(self):
        if not self.Users:
            self.AddRandomUser()
        UserIndex = choice(self.Users.keys())

        self.DelUser(UserIndex)

    def DelUser(self, UserIndex):
        self.comment("Del User")
        self.SendCommand(self.CMD_DEL_USER)
        request = (self.Users[UserIndex])['Username'].ljust(32, '\0')
        self.write(request)
        self.ReceiveOkResponse(0)

        # remove the user from any keypad or swipe devices they were in
        self.RevokeAccess(UserIndex)

        # remove the user 
        del self.Users[UserIndex]

    def FindUser(self, Username):
        for user in self.Users.keys():
            if Username == (self.Users[user])['Username']:
                return Username
        return self.MAX_USERS

    def DelInvalidUser(self):
        Username = self.random_string(1, 31)
        while self.FindUser(Username) != self.MAX_USERS:
            Username = self.random_string(1, 31)
        self.comment("Del Invalid User")
        self.SendCommand(self.CMD_DEL_USER)
        request = Username.ljust(32, '\0')
        self.write(request)
        self.ReceiveResponse(self.RESP_DEL_USER_FAILED, 0)

    def PowerOff(self):
        self.comment("Power Off")
        self.SendCommand(self.CMD_POWER_OFF)
        self.ReceiveOkResponse(0)

    def FindDeviceId(self, DeviceId):
        for d in self.Devices.keys():
            if (self.Devices[d])['Id'] == DeviceId:
                return(d)
        return(self.MAX_DEVICES)

    def AddRandomAlarmTrigger(self):
        Type = choice([self.DEVICE_CONTACT, self.DEVICE_MOTION, self.DEVICE_HEAT, self.DEVICE_SMOKE])
        if Type == self.DEVICE_CONTACT:
            return(self.AddContact())
        elif Type == self.DEVICE_MOTION:
            return(self.AddMotion())
        elif Type == self.DEVICE_HEAT:
            return(self.AddHeat())
        elif Type == self.DEVICE_SMOKE:
            return(self.AddSmoke())

    def AddRandomDevice(self):
        Type = choice([self.DEVICE_KEYPAD, self.DEVICE_SWIPE, self.DEVICE_CONTACT, self.DEVICE_MOTION, self.DEVICE_HEAT, self.DEVICE_SMOKE, self.DEVICE_ALARM])
        if Type == self.DEVICE_KEYPAD:
            self.AddKeypad()
        elif Type == self.DEVICE_SWIPE:
            self.AddSwipe()
        elif Type == self.DEVICE_CONTACT:
            self.AddContact()
        elif Type == self.DEVICE_MOTION:
            self.AddMotion()
        elif Type == self.DEVICE_HEAT:
            self.AddHeat()
        elif Type == self.DEVICE_SMOKE:
            self.AddSmoke()
        elif Type == self.DEVICE_ALARM:
            self.AddAlarm()

    def DelRandomDevice(self):
        CandidateDevices = []
        if not self.Devices:
            self.AddRandomDevice()
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] != self.DEVICE_UNUSED:
                CandidateDevices.append((self.Devices[d])['Id'])
        DeviceId = choice(CandidateDevices)

        self.DelDevice(DeviceId)

    def DelDevice(self, DeviceId):
        self.comment("Del Device")
        self.SendCommand(self.CMD_DEL_DEVICE)
        request = pack("<H", DeviceId)
        self.write(request)

        RemoveMe = self.FindDeviceId(DeviceId)
    
        # remove it from any alarms that reference it
        for alarm in self.Devices.keys():
            if (self.Devices[alarm])['Type'] != self.DEVICE_ALARM:
                continue;
            for device in (self.Devices[alarm])['DeviceList']:
                if device == RemoveMe:
                        ((self.Devices[alarm])['DeviceList']).remove(RemoveMe)

        # remove the device itself
        del self.Devices[RemoveMe]

        self.ProcessAlarms()

        self.ReceiveOkResponse(0)
                
    def AddKeypad(self):
        self.comment("Add Keypad")
        self.SendCommand(self.CMD_ADD_DEVICE)
        request = pack("B", self.DEVICE_KEYPAD)
        self.write(request)

        DeviceId = self.NewDeviceId()
        DeviceIndex = self.FindAvailableDeviceIndex();
        if DeviceIndex == self.MAX_DEVICES:
            self.ReceiveResponse(self.RESP_INVALID_COMMAND, 0)
        else:
            self.ReceiveOkResponse(DeviceId)
            self.Devices[DeviceIndex] = { 'Type': self.DEVICE_KEYPAD, 'Id': DeviceId, 'AuthorizedCodes': [] }
        return(DeviceIndex)

    def AddSwipe(self):
        self.comment("Add Swipe")
        self.SendCommand(self.CMD_ADD_DEVICE)
        request = pack("B", self.DEVICE_SWIPE)
        self.write(request)

        DeviceId = self.NewDeviceId()
        DeviceIndex = self.FindAvailableDeviceIndex();
        if DeviceIndex == self.MAX_DEVICES:
            self.ReceiveResponse(self.RESP_INVALID_COMMAND, 0)
        else:
            self.ReceiveOkResponse(DeviceId)
            self.Devices[DeviceIndex] = { 'Type': self.DEVICE_SWIPE, 'Id': DeviceId, 'AuthorizedCodes': [] }
        return(DeviceIndex)

    def AddContact(self):
        self.comment("Add Contact")
        self.SendCommand(self.CMD_ADD_DEVICE)
        request = pack("B", self.DEVICE_CONTACT)
        self.write(request)
        Mode = choice([self.CONTACT_NO, self.CONTACT_NC])
        State = choice([self.CONTACT_OPEN, self.CONTACT_CLOSED])
        request = pack("BB", Mode, State)
        self.write(request)

        DeviceId = self.NewDeviceId()
        DeviceIndex = self.FindAvailableDeviceIndex();
        if DeviceIndex == self.MAX_DEVICES:
            self.ReceiveResponse(self.RESP_INVALID_COMMAND, 0)
        else:
            self.ReceiveOkResponse(DeviceId)
            self.Devices[DeviceIndex] = { 'Type': self.DEVICE_CONTACT, 'Id': DeviceId, 'Mode': Mode, 'State': State }
        return(DeviceIndex)

    def AddMotion(self):
        self.comment("Add Motion")
        self.SendCommand(self.CMD_ADD_DEVICE)
        request = pack("B", self.DEVICE_MOTION)
        self.write(request)
        State = choice([self.MOTION_INACTIVE, self.MOTION_ACTIVE])
        request = pack("B", State)
        self.write(request)

        DeviceId = self.NewDeviceId()
        DeviceIndex = self.FindAvailableDeviceIndex();
        if DeviceIndex == self.MAX_DEVICES:
            self.ReceiveResponse(self.RESP_INVALID_COMMAND, 0)
        else:
            self.ReceiveOkResponse(DeviceId)
            self.Devices[DeviceIndex] = { 'Type': self.DEVICE_MOTION, 'Id': DeviceId, 'State': State }
        return(DeviceIndex)

    def AddHeat(self):
        self.comment("Add Heat")
        self.SendCommand(self.CMD_ADD_DEVICE)
        request = pack("B", self.DEVICE_HEAT)
        self.write(request)
        CurrentTemperature = randint(0,128)
        ThresholdTemperature = randint(0,128)
        request = pack("BB", CurrentTemperature, ThresholdTemperature)
        self.write(request)

        DeviceId = self.NewDeviceId()
        DeviceIndex = self.FindAvailableDeviceIndex();
        if DeviceIndex == self.MAX_DEVICES:
            self.ReceiveResponse(self.RESP_INVALID_COMMAND, 0)
        else:
            self.ReceiveOkResponse(DeviceId)
            self.Devices[DeviceIndex] = { 'Type': self.DEVICE_HEAT, 'Id': DeviceId, 'CurrentTemperature': CurrentTemperature, 'ThresholdTemperature': ThresholdTemperature }
        return(DeviceIndex)

    def AddSmoke(self):
        self.comment("Add Smoke")
        self.SendCommand(self.CMD_ADD_DEVICE)
        request = pack("B", self.DEVICE_SMOKE)
        self.write(request)
        State = choice([self.SMOKE_INACTIVE, self.SMOKE_ACTIVE])
        request = pack("B", State)
        self.write(request)

        DeviceId = self.NewDeviceId()
        DeviceIndex = self.FindAvailableDeviceIndex();
        if DeviceIndex == self.MAX_DEVICES:
            self.ReceiveResponse(self.RESP_INVALID_COMMAND, 0)
        else:
            self.ReceiveOkResponse(DeviceId)
            self.Devices[DeviceIndex] = { 'Type': self.DEVICE_SMOKE, 'Id': DeviceId, 'State': State }
        return(DeviceIndex)

    def AddAlarm(self):
        self.comment("Add Alarm")
        self.SendCommand(self.CMD_ADD_DEVICE)
        request = pack("B", self.DEVICE_ALARM)
        self.write(request)

        DeviceId = self.NewDeviceId()
        DeviceIndex = self.FindAvailableDeviceIndex();
        if DeviceIndex == self.MAX_DEVICES:
            self.ReceiveResponse(self.RESP_INVALID_COMMAND, 0)
        else:
            self.ReceiveOkResponse(DeviceId)
            self.Devices[DeviceIndex] = { 'Type': self.DEVICE_ALARM, 'Id': DeviceId, 'Armed': self.ALARM_DISARMED, 'Active': self.ALARM_INACTIVE, 'DeviceList': [] }
        return DeviceIndex

    def FindAlarmTriggerDevice(self):
        CandidateDevices = []
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] in [self.DEVICE_CONTACT, self.DEVICE_MOTION, self.DEVICE_HEAT, self.DEVICE_SMOKE]:
                    CandidateDevices.append((self.Devices[d])['Id'])

        if not CandidateDevices:
            return []
        else:
            return choice(CandidateDevices);

    def FindAlarmDevice(self):
        CandidateDevices = []
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] == self.DEVICE_ALARM:
                    CandidateDevices.append((self.Devices[d])['Id'])

        if not CandidateDevices:
            return []
        else:
            return choice(CandidateDevices);

    def AddRandomDeviceToAlarm(self):
        # find a suitable contact, smoke, heat, or motion sensor
        Device = self.FindAlarmTriggerDevice()
        while not Device:
            if self.AddRandomAlarmTrigger() == self.MAX_DEVICES:
                return
            Device = self.FindAlarmTriggerDevice()

        # find an alarm device
        Alarm = self.FindAlarmDevice()
        while not Alarm:
            if self.AddAlarm() == self.MAX_DEVICES:
                return
            Alarm = self.FindAlarmDevice()

        self.AddDeviceToAlarm(Device, Alarm)

    def AddDeviceToAlarm(self, DeviceId, AlarmId):
        Device = self.FindDeviceId(DeviceId)
        Alarm = self.FindDeviceId(AlarmId)
        if Device not in (self.Devices[Alarm])['DeviceList']:
            (self.Devices[Alarm])['DeviceList'].append(Device)

        self.comment("Add Device to Alarm")
        self.SendCommand(self.CMD_ADD_DEVICE_TO_ALARM)
        request = pack("<HH", DeviceId, AlarmId)
        self.write(request)

        self.ProcessAlarms()

        self.ReceiveOkResponse(0)

    def GrantAccess(self):
        # find a keypad or swipe to add them to
        CandidateDevices = []
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] in [self.DEVICE_KEYPAD, self.DEVICE_SWIPE]:
                CandidateDevices.append(d)
        if not CandidateDevices:
            Index = self.AddKeypad()
            if Index == self.MAX_DEVICES:
                return
            CandidateDevices.append(Index)
        DeviceIndex = choice(CandidateDevices)
        DeviceId = (self.Devices[DeviceIndex])['Id']

        # find a user 
        if not self.Users:
            self.AddRandomUser()
        UserIndex = choice(self.Users.keys())

        # send the command
        self.comment("Grant Access")
        self.SendCommand(self.CMD_GRANT_ACCESS)
        request = pack("<HB", DeviceId, UserIndex)
        self.write(request)
        self.ReceiveOkResponse(0)

        # add them to the device's AuthorizedCodes
        if (self.Devices[DeviceIndex])['Type'] == self.DEVICE_KEYPAD:
	    if (self.Users[UserIndex])['Pin'] not in (self.Devices[DeviceIndex])['AuthorizedCodes']:
                (self.Devices[DeviceIndex])['AuthorizedCodes'].append((self.Users[UserIndex])['Pin'])
        else:
	    if (self.Users[UserIndex])['Code'] not in (self.Devices[DeviceIndex])['AuthorizedCodes']:
                (self.Devices[DeviceIndex])['AuthorizedCodes'].append((self.Users[UserIndex])['Code'])

    def BadGrantAccess(self):
        Type = randint(0,3)
        if Type == 0:
            # Invalid DeviceId
            self.comment("Grant Acesss with invalid DeviceId")
            # get a valid user
            if not self.Users:
                self.AddRandomUser()
            UserIndex = choice(self.Users.keys())
            # get an invalid DeviceId
            DeviceId = randint(0,100)
            while self.FindDeviceId(DeviceId) != self.MAX_DEVICES:
                DeviceId = randint(0,100)
            # send the command
            self.SendCommand(self.CMD_GRANT_ACCESS)
            request = pack("<HB", DeviceId, UserIndex)
            self.write(request)
            self.ReceiveResponse(self.RESP_GRANT_FAILED, 0)
        elif Type == 1:
            # Invalid device type
            self.comment("Grant Acesss with invalid device type")
            # get an invalid device 
            DeviceId = self.FindAlarmTriggerDevice()
            if not DeviceId:
                self.AddSmoke()
            DeviceId = self.FindAlarmTriggerDevice()
            # get a valid user
            if not self.Users:
                UserIndex = self.AddRandomUser()
            UserIndex = choice(self.Users.keys())
            # send the command
            self.SendCommand(self.CMD_GRANT_ACCESS)
            request = pack("<HB", DeviceId, UserIndex)
            self.write(request)
            self.ReceiveResponse(self.RESP_GRANT_FAILED, 0)
        elif Type == 2:
            # invalid UserID value
            self.comment("Grant Acesss with invalid userid value")
            CandidateDevices = []
            for d in self.Devices.keys():
                if (self.Devices[d])['Type'] in [self.DEVICE_KEYPAD, self.DEVICE_SWIPE]:
                    CandidateDevices.append(d)
            if not CandidateDevices:
                Index = self.AddKeypad()
                if Index == self.MAX_DEVICES:
                    return
                CandidateDevices.append(Index)
            DeviceIndex = choice(CandidateDevices)
            DeviceId = (self.Devices[DeviceIndex])['Id']
            UserIndex = randint(128,255)
            # send the command
            self.SendCommand(self.CMD_GRANT_ACCESS)
            request = pack("<HB", DeviceId, UserIndex)
            self.write(request)
            self.ReceiveResponse(self.RESP_GRANT_FAILED, 0)
        elif Type == 3:
            # unused UserID
            self.comment("Grant Acesss with unused userid")
            CandidateDevices = []
            for d in self.Devices.keys():
                if (self.Devices[d])['Type'] in [self.DEVICE_KEYPAD, self.DEVICE_SWIPE]:
                    CandidateDevices.append(d)
            if not CandidateDevices:
                Index = self.AddKeypad()
                if Index == self.MAX_DEVICES:
                    return
                CandidateDevices.append(Index)
            DeviceIndex = choice(CandidateDevices)
            DeviceId = (self.Devices[DeviceIndex])['Id']
            # find an available user index (aka, an unused userid)
            UserIndex = self.FindAvailableUserIndex()
            if UserIndex == self.MAX_USERS:
                self.DelRandomUser()
            UserIndex = self.FindAvailableUserIndex()
            # send the command
            self.SendCommand(self.CMD_GRANT_ACCESS)
            request = pack("<HB", DeviceId, UserIndex)
            self.write(request)
            self.ReceiveResponse(self.RESP_GRANT_FAILED, 0)

    def RevokeAccess(self, UserIndex):
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] == self.DEVICE_KEYPAD:
                if (self.Users[UserIndex])['Pin'] in (self.Devices[d])['AuthorizedCodes']:
                    (self.Devices[d])['AuthorizedCodes'].remove((self.Users[UserIndex])['Pin'])
            if (self.Devices[d])['Type'] == self.DEVICE_SWIPE:
                if (self.Users[UserIndex])['Code'] in (self.Devices[d])['AuthorizedCodes']:
                    (self.Devices[d])['AuthorizedCodes'].remove((self.Users[UserIndex])['Code'])

    def IsDeviceInAlarm(self, DeviceIndex):
        if (self.Devices[DeviceIndex])['Type'] == self.DEVICE_CONTACT:
            if (self.Devices[DeviceIndex])['Mode'] == self.CONTACT_NO:
                if (self.Devices[DeviceIndex])['State'] == self.CONTACT_OPEN:
                    return 0
                else:
                    return 1
            if (self.Devices[DeviceIndex])['Mode'] == self.CONTACT_NC:
                if (self.Devices[DeviceIndex])['State'] == self.CONTACT_CLOSED:
                    return 0
                else:
                    return 1
        elif (self.Devices[DeviceIndex])['Type'] == self.DEVICE_MOTION:
            if (self.Devices[DeviceIndex])['State'] == self.MOTION_ACTIVE:
                return 1
            else:
                return 0
        elif (self.Devices[DeviceIndex])['Type'] == self.DEVICE_SMOKE:
            if (self.Devices[DeviceIndex])['State'] == self.SMOKE_ACTIVE:
                return 1
            else:
                return 0
        elif (self.Devices[DeviceIndex])['Type'] == self.DEVICE_HEAT:
            if (self.Devices[DeviceIndex])['CurrentTemperature'] > (self.Devices[DeviceIndex])['ThresholdTemperature']:
                return 1
            else:
                return 0

        return 0
            
    def ProcessAlarms(self):
        for alarm in self.Devices.keys():
            if (self.Devices[alarm])['Type'] != self.DEVICE_ALARM:
                continue

            self.comment("Found Alarm");
            PrevAlarmState = (self.Devices[alarm])['Active']

            if (self.Devices[alarm])['Armed'] == self.ALARM_ARMED:
                self.comment("Found Armed Alarm");

                #(self.Devices[alarm])['Active'] = self.ALARM_INACTIVE
		NewState = self.ALARM_INACTIVE

                for device in (self.Devices[alarm])['DeviceList']:
                    if self.IsDeviceInAlarm(device):
                        self.comment("Found device in alarm");
                        # yes, set the alarm
                        #(self.Devices[alarm])['Active'] = self.ALARM_ACTIVE
			NewState = self.ALARM_ACTIVE
                        if PrevAlarmState == self.ALARM_INACTIVE:
                            # read the new alarm state response
			    self.comment("New alarm state")
                            self.ReceiveResponse(self.RESP_ALARM_ON, (self.Devices[alarm])['Id'])
			    break;
                if (self.Devices[alarm])['Active'] == self.ALARM_INACTIVE:
		    if NewState == self.ALARM_ACTIVE:
		        (self.Devices[alarm])['Active'] = NewState

            else: # not armed
                (self.Devices[alarm])['Active'] = self.ALARM_INACTIVE
                if PrevAlarmState == self.ALARM_ACTIVE:
		    self.comment("New alarm state")
                    self.ReceiveResponse(self.RESP_ALARM_OFF, (self.Devices[alarm])['Id'])

    def InvalidCommand(self):
        cmd = randint(9,127)
        self.comment("Invalid Command")
        self.SendCommand(cmd)
        self.ReceiveResponse(self.RESP_INVALID_CMD, 0)

    def UpdateKeypad(self):
        self.comment("Update Keypad")
        # find a device with a user associated
        CandidateDevices = []
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] == self.DEVICE_KEYPAD:
                CandidateDevices.append(d)
        if not CandidateDevices:
            # no available devices, so create a device
            DeviceIndex = self.AddKeypad()
            if DeviceIndex == self.MAX_DEVICES:
                 return
            CandidateDevices.append(DeviceIndex)
            # add a user to it
            if not self.Users:
                UserIndex = self.AddRandomUser()
            UserIndex = choice(self.Users.keys())
            Pin = (self.Users[UserIndex])['Pin']
	    if Pin not in (self.Devices[DeviceIndex])['AuthorizedCodes']:
	            (self.Devices[DeviceIndex])['AuthorizedCodes'].append(Pin)
            self.comment("Grant Access")
            self.SendCommand(self.CMD_GRANT_ACCESS)
            request = pack("<HB", (self.Devices[DeviceIndex])['Id'], UserIndex)
            self.write(request)
            self.ReceiveOkResponse(0)
        else:
            # pick from the available devices
            DeviceIndex = choice(CandidateDevices)
            if not (self.Devices[DeviceIndex])['AuthorizedCodes']:
                # add a user to it
                if not self.Users:
                    UserIndex = self.AddRandomUser()
                UserIndex = choice(self.Users.keys())
                Pin = (self.Users[UserIndex])['Pin']
	        if Pin not in (self.Devices[DeviceIndex])['AuthorizedCodes']:
	            (self.Devices[DeviceIndex])['AuthorizedCodes'].append(Pin)
                self.comment("Grant Access")
                self.SendCommand(self.CMD_GRANT_ACCESS)
                request = pack("<HB", (self.Devices[DeviceIndex])['Id'], UserIndex)
                self.write(request)
                self.ReceiveOkResponse(0)
            else:
                Pin = choice((self.Devices[DeviceIndex])['AuthorizedCodes'])

        self.comment("Pins: {}".format((self.Devices[DeviceIndex])['AuthorizedCodes']))
        # make sure the keypad is tied to an alarm
        CandidateAlarms = []
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] == self.DEVICE_ALARM:
                CandidateAlarms.append(d)
        if not CandidateAlarms:
            # create a new alarm
            AlarmIndex = self.AddAlarm()
            if AlarmIndex == self.MAX_DEVICES:
                return
        else:
            AlarmIndex = choice(CandidateAlarms)
        self.AddDeviceToAlarm((self.Devices[DeviceIndex])['Id'], (self.Devices[AlarmIndex])['Id'])

	# for all of the alarms associated with this swipe
	for d in self.Devices.keys():
	    if (self.Devices[d])['Type'] == self.DEVICE_ALARM:
                if DeviceIndex in (self.Devices[d])['DeviceList']:
                    # update the alarm's state
                    if (self.Devices[d])['Armed'] == self.ALARM_ARMED:
                        self.comment("Disarming Device: {:4x}".format((self.Devices[d])['Id']))
                        (self.Devices[d])['Armed'] = self.ALARM_DISARMED
                    else:
                        self.comment("arming Device: {:4x}".format((self.Devices[d])['Id']))
                        (self.Devices[d])['Armed'] = self.ALARM_ARMED

        # send the user's code to arm/disarm the alarm
        self.SendCommand(self.CMD_UPDATE_DEVICE)
        request = pack("<H", (self.Devices[DeviceIndex])['Id'])
        self.write(request)
        self.write(Pin)

    def UpdateSwipe(self):
        self.comment("Update Swipe")
        # find a device with a user associated
        CandidateDevices = []
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] == self.DEVICE_SWIPE:
                CandidateDevices.append(d)
        if not CandidateDevices:
            # no available devices, so create a device
            DeviceIndex = self.AddSwipe()
            if DeviceIndex == self.MAX_DEVICES:
                 return
            CandidateDevices.append(DeviceIndex)
            # add a user to it
            if not self.Users:
                UserIndex = self.AddRandomUser()
            UserIndex = choice(self.Users.keys())
            Code = (self.Users[UserIndex])['Code']
	    if Code not in (self.Devices[DeviceIndex])['AuthorizedCodes']:
                (self.Devices[DeviceIndex])['AuthorizedCodes'].append(Code)
            self.comment("Grant Access")
            self.SendCommand(self.CMD_GRANT_ACCESS)
            request = pack("<HB", (self.Devices[DeviceIndex])['Id'], UserIndex)
            self.write(request)
            self.ReceiveOkResponse(0)
        else:
            # pick from the available devices
            DeviceIndex = choice(CandidateDevices)
            if not (self.Devices[DeviceIndex])['AuthorizedCodes']:
                # add a user to it
                if not self.Users:
                    UserIndex = self.AddRandomUser()
                UserIndex = choice(self.Users.keys())
                Code = (self.Users[UserIndex])['Code']
	        if Code not in (self.Devices[DeviceIndex])['AuthorizedCodes']:
                    (self.Devices[DeviceIndex])['AuthorizedCodes'].append(Code)
                self.comment("Grant Access")
                self.SendCommand(self.CMD_GRANT_ACCESS)
                request = pack("<HB", (self.Devices[DeviceIndex])['Id'], UserIndex)
                self.write(request)
                self.ReceiveOkResponse(0)
            else:
                Code = choice((self.Devices[DeviceIndex])['AuthorizedCodes'])

	self.comment("AuthorizedCodes: {}".format((self.Devices[DeviceIndex])['AuthorizedCodes']))
        # make sure the swipe is tied to an alarm
        CandidateAlarms = []
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] == self.DEVICE_ALARM:
                CandidateAlarms.append(d)
        if not CandidateAlarms:
            # create a new alarm
            AlarmIndex = self.AddAlarm()
            if AlarmIndex == self.MAX_DEVICES:
                return
        else:
            AlarmIndex = choice(CandidateAlarms)
        self.AddDeviceToAlarm((self.Devices[DeviceIndex])['Id'], (self.Devices[AlarmIndex])['Id'])

	# for all of the alarms associated with this swipe
	for d in self.Devices.keys():
	    if (self.Devices[d])['Type'] == self.DEVICE_ALARM:
                if DeviceIndex in (self.Devices[d])['DeviceList']:
                    # update the alarm's state
                    if (self.Devices[d])['Armed'] == self.ALARM_ARMED:
                        self.comment("Disarming Device: {:4x}".format((self.Devices[d])['Id']))
                        (self.Devices[d])['Armed'] = self.ALARM_DISARMED
                    else:
                        self.comment("arming Device: {:4x}".format((self.Devices[d])['Id']))
                        (self.Devices[d])['Armed'] = self.ALARM_ARMED

        # send the user's code to arm/disarm the alarm
        self.SendCommand(self.CMD_UPDATE_DEVICE)
        request = pack("<H", (self.Devices[DeviceIndex])['Id'])
        self.write(request)
        self.write(Code)

    def UpdateContact(self):
        self.comment("Update Contact")
        # find a contact
        CandidateDevices = []
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] == self.DEVICE_CONTACT:
                CandidateDevices.append(d)
        if not CandidateDevices:
            # no available devices, so create a device
            DeviceIndex = self.AddContact()
            if DeviceIndex == self.MAX_DEVICES:
                 return
        else:
            DeviceIndex = choice(CandidateDevices)

        # finally, update the contact
        if (self.Devices[DeviceIndex])['State'] == self.CONTACT_OPEN:
            (self.Devices[DeviceIndex])['State'] = self.CONTACT_CLOSED
        else:
            (self.Devices[DeviceIndex])['State'] = self.CONTACT_OPEN
        self.SendCommand(self.CMD_UPDATE_DEVICE)
        request = pack("<H", (self.Devices[DeviceIndex])['Id'])
        self.write(request)
        self.write(chr((self.Devices[DeviceIndex])['State']))

    def UpdateMotion(self):
        self.comment("Update Motion")
        # find a Motion device
        CandidateDevices = []
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] == self.DEVICE_MOTION:
                CandidateDevices.append(d)
        if not CandidateDevices:
            # no available devices, so create a device
            DeviceIndex = self.AddMotion()
            if DeviceIndex == self.MAX_DEVICES:
                 return
        else:
            DeviceIndex = choice(CandidateDevices)

        # finally, update the motion device
        if (self.Devices[DeviceIndex])['State'] == self.MOTION_INACTIVE:
            (self.Devices[DeviceIndex])['State'] = self.MOTION_ACTIVE
        else:
            (self.Devices[DeviceIndex])['State'] = self.MOTION_INACTIVE
        self.SendCommand(self.CMD_UPDATE_DEVICE)
        request = pack("<H", (self.Devices[DeviceIndex])['Id'])
        self.write(request)
        self.write(chr((self.Devices[DeviceIndex])['State']))

    def UpdateHeat(self):
        self.comment("Update Heat")
        # find a Heat device
        CandidateDevices = []
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] == self.DEVICE_HEAT:
                CandidateDevices.append(d)
        if not CandidateDevices:
            # no available devices, so create a device
            DeviceIndex = self.AddHeat()
            if DeviceIndex == self.MAX_DEVICES:
                 return
        else:
            DeviceIndex = choice(CandidateDevices)

        # finally, update the heat device
        (self.Devices[DeviceIndex])['CurrentTemperature'] = randint(0,128)
        self.SendCommand(self.CMD_UPDATE_DEVICE)
        request = pack("<H", (self.Devices[DeviceIndex])['Id'])
        self.write(request)
        self.write(chr((self.Devices[DeviceIndex])['CurrentTemperature']))

    def UpdateSmoke(self):
        self.comment("Update Smoke")
        # find a smoke detector
        CandidateDevices = []
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] == self.DEVICE_SMOKE:
                CandidateDevices.append(d)
        if not CandidateDevices:
            # no available devices, so create a device
            DeviceIndex = self.AddSmoke()
            if DeviceIndex == self.MAX_DEVICES:
                 return
        else:
            DeviceIndex = choice(CandidateDevices)

        # finally, update the smoke device
        if (self.Devices[DeviceIndex])['State'] == self.SMOKE_INACTIVE:
            (self.Devices[DeviceIndex])['State'] = self.SMOKE_ACTIVE
        else:
            (self.Devices[DeviceIndex])['State'] = self.SMOKE_INACTIVE
        self.SendCommand(self.CMD_UPDATE_DEVICE)
        request = pack("<H", (self.Devices[DeviceIndex])['Id'])
        self.write(request)
        self.write(chr((self.Devices[DeviceIndex])['State']))

    def UpdateRandomDevice(self):
        Type = choice([self.DEVICE_KEYPAD, self.DEVICE_SWIPE, self.DEVICE_CONTACT, self.DEVICE_MOTION, self.DEVICE_SMOKE, self.DEVICE_HEAT])

        if Type == self.DEVICE_KEYPAD:
            self.UpdateKeypad()
        elif Type == self.DEVICE_SWIPE:
            self.UpdateSwipe()
        elif Type == self.DEVICE_CONTACT:
            self.UpdateContact()
        elif Type == self.DEVICE_MOTION:
            self.UpdateMotion()
        elif Type == self.DEVICE_SMOKE:
            self.UpdateSmoke()
        elif Type == self.DEVICE_HEAT:
            self.UpdateHeat()

        self.ProcessAlarms()
        self.ReceiveOkResponse(0)

    def ListAlarmCodes(self):
        self.comment("List Alarm Codes")
        # get a list of Keypads and Swipes
        CandidateDevices = []
        for d in self.Devices.keys():
            if (self.Devices[d])['Type'] in [self.DEVICE_KEYPAD, self.DEVICE_SWIPE]:
                CandidateDevices.append(d)
        if not CandidateDevices:
            return
        DeviceIndex = choice(CandidateDevices)
        DeviceId = (self.Devices[DeviceIndex])['Id']

        # send the command to list the alarm codes of DeviceId
        self.SendCommand(self.CMD_LIST_ALARM_CODES)
        self.write(pack("<H", DeviceId))

        # get a count of the number of AuthorizedCodes for the device
        AlarmCodeCount = len((self.Devices[DeviceIndex])['AuthorizedCodes'])
        self.read(length=1, expect=chr(AlarmCodeCount))

        # read the alarm codes
        if AlarmCodeCount > 0:
            Codes = (self.Devices[DeviceIndex])['AuthorizedCodes']
            for code in sorted(Codes):
                self.read(length=32, expect=code.ljust(32, '\0'))

        self.ReceiveOkResponse(0)

    def TestFullAlarmSystem(self):
        self.comment("Test Full Alarm System")
	# add a contact
        contact = (self.Devices[self.AddContact()])['Id']
	# add an alarm
        alarm = (self.Devices[self.AddAlarm()])['Id']
	# add the contact to the alarm
	self.AddDeviceToAlarm(contact, alarm)
	# add user
        user = self.AddRandomUser()
	# add a keypad
        keypad = (self.Devices[self.AddKeypad()])['Id']
	# add the keypad to the alarm
	self.AddDeviceToAlarm(keypad, alarm)
	# grant the user access to the keypad
        self.GrantAccess()
	# arm the keypad
	self.UpdateKeypad()
	self.ProcessAlarms()
	self.ReceiveOkResponse(0)
	# change the contact state
        self.UpdateContact()
	self.ProcessAlarms()
	self.ReceiveOkResponse(0)

    def GoodTests(self):
        Good = [ self.AddRandomUser, self.AddRandomUser, self.DelRandomUser, self.AddRandomAlarmTrigger, self.AddRandomDevice, self.AddRandomDeviceToAlarm, self.DelRandomDevice, self.GrantAccess, self.UpdateRandomDevice, self.TestFullAlarmSystem, self.ListAlarmCodes ]
        choice(Good)()

    def BadTests(self):
        Bad = [ self.BadGrantAccess, self.InvalidCommand, self.BadRandomUser ]
        choice(Bad)()

    def start(self):
        #self.delay(100)
        self.InitProgram()
        self.Users = dict()
        self.Devices = dict()

    def end(self):
        pass
