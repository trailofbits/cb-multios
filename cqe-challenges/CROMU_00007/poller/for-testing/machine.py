#!/usr/bin/env python

from generator.actions import Actions
import random
import pdb
import locale
import decimal
import ctypes

class Paycheck():
    def __init__(self):
        self.standardhours = 0
        self.standardminutes = 0
        self.overtimehours = 0
        self.overtimeminutes = 0
        self.standardpay = 0
        self.overtimepay = 0

class Employee():

    def __init__(self):
        self.id = -1
        self.name = ""
        self.wagedollars= 0
        self.wagecents = 0
        self.paychecks = []
        for i in range(0,52):
            self.paychecks.append(Paycheck())

class TimecardPollGenerator(Actions):

    def start(self):
        self.NUMBER_OF_EMPLOYEES = 50
        self.state['employees'] = []
        for each in range(0, self.NUMBER_OF_EMPLOYEES):
            self.state['employees'].append(Employee())
        # Generate a random list of employee id's from 1 to 10 elements long. The generator will create inputs for those employees only.
        self.state['id_subset'] = random.sample(range(0,self.NUMBER_OF_EMPLOYEES), random.randint(1,10))
        self.state['weeks_subset'] = random.sample(range(0,52), random.randint(1,10))
        self.state['id_subset'].sort()
        self.state['weeks_subset'].sort()
        testlib = ctypes.CDLL('build/patched/so/CROMU_00007.so')
        self.standardpay = testlib.c_standardpay
        self.standardpay.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
        self.standardpay.restype = ctypes.c_float
        self.overtimepay = testlib.c_overtimepay
        self.overtimepay.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
        self.overtimepay.restype = ctypes.c_float
        self.netpay = testlib.c_netpay
        self.netpay.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
        self.netpay.restype = ctypes.c_float

    def register(self):
        names = ["Jonathan Archer", "Chef", "Daniels", "Travis Mayweather", "John Paxton", "Phlox", "Malcolm Reed", "Hoshi Sato", "T'Pol", "Trip Tucker"]
        for id in self.state['id_subset']:
            name = names[random.randint(0, len(names) - 1)]
            self.state['employees'][id].name = name
            self.state['employees'][id].id = id
            if self.chance(0.5):
                self.state['employees'][id].exempt = False
            else:
                self.state['employees'][id].exempt = True
            self.state['employees'][id].wagedollars = random.randint(0,76)
            self.state['employees'][id].wagecents = random.randint(0, 99)
            if  (self.state['employees'][id].exempt):
                self.write("employee_id-{a.id}`employee_name-{a.name}`wage-{a.wagedollars}.{a.wagecents:02}`exempt-yes`\n".format(a=self.state['employees'][id]))
            else:
                self.write("employee_id-{a.id}`employee_name-{a.name}`wage-{a.wagedollars}.{a.wagecents:02}`\n".format(a=self.state['employees'][id]))
            if (self.state['employees'][id].wagedollars >= 75):
                self.state['employees'][id].wagedollars = 75
                self.state['employees'][id].wagecents = 0
            
    def logday(self, day, paycheck):
       
        hours = random.randint(0,25)
        minutes = random.randint(0,61)  
        self.write("%s-%dh%dm`" % (day, hours,minutes))

        # Modify hours to match internal bounds checks on CB 
        # max hours 24, max minutes 59
        # minutes rounded to quarter hour
        if (hours > 24):
            hours = 24
        if (hours > 59):
            hours = 59
        if (minutes < 8):
            minutes = 0
        elif (minutes < 23):
            minutes = 15
        elif (minutes < 38):
            minutes = 30
        elif (minutes < 53):
            minutes = 45
        else:
            minutes = 0
            hours += 1

        if (day == "saturday" or day== "sunday"):
            paycheck.overtimehours += hours + (paycheck.overtimeminutes + minutes) / 60
            paycheck.overtimeminutes = (paycheck.overtimeminutes + minutes) % 60
        elif (hours < 8):
            paycheck.standardhours += (hours) + (paycheck.standardminutes + minutes) / 60
            paycheck.standardminutes = (paycheck.standardminutes + minutes) % 60
        else:
            paycheck.standardhours += 8
            paycheck.overtimehours += hours - 8 + (paycheck.overtimeminutes + minutes) / 60
            paycheck.overtimeminutes = (paycheck.overtimeminutes + minutes) % 60

    def loghours(self):
        for id in self.state['id_subset']:
            for week in self.state['weeks_subset']:
                self.write("employee_id-{}`week-{}`".format(id, week))
                if self.chance(0.9):    
                    self.logday("monday", self.state['employees'][id].paychecks[week])
                if self.chance(0.01):    
                    self.logday("monday", self.state['employees'][id].paychecks[week])
                if self.chance(0.9):
                    self.logday("tuesday", self.state['employees'][id].paychecks[week])
                if self.chance(0.01):   
                    self.logday("tuesday", self.state['employees'][id].paychecks[week])
                if self.chance(0.9):
                    self.logday("wednesday", self.state['employees'][id].paychecks[week])
                if self.chance(0.01):
                    self.logday("wednesday", self.state['employees'][id].paychecks[week])
                if self.chance(0.9):
                    self.logday("thursday", self.state['employees'][id].paychecks[week])
                if self.chance(0.01):
                    self.logday("thursday", self.state['employees'][id].paychecks[week])
                if self.chance(0.9):
                    self.logday("friday", self.state['employees'][id].paychecks[week])
                if self.chance(0.01):
                    self.logday("friday", self.state['employees'][id].paychecks[week])
                if self.chance(0.2):
                    self.logday("saturday", self.state['employees'][id].paychecks[week])
                if self.chance(0.01):
                    self.logday("saturday", self.state['employees'][id].paychecks[week])
                if self.chance(0.1):
                    self.logday("sunday", self.state['employees'][id].paychecks[week])
                if self.chance(0.01):
                    self.logday("sunday", self.state['employees'][id].paychecks[week])
                self.write("\n")
                employee = self.state['employees'][id]
                paycheck = employee.paychecks[week]
                paycheck.standardpay = self.standardpay(paycheck.standardhours, paycheck.standardminutes, employee.wagedollars, employee.wagecents )
                if (employee.exempt):
                    paycheck.overtimepay = self.overtimepay(paycheck.overtimehours, paycheck.overtimeminutes, employee.wagedollars, employee.wagecents, 1)
                else:
                    paycheck.overtimepay = self.overtimepay(paycheck.overtimehours, paycheck.overtimeminutes, employee.wagedollars, employee.wagecents, 0)

   
    def get_response(self, id, week):
        employee = self.state['employees'][id]
        pay = employee.paychecks[week]
        if (employee.exempt):
            netpay = self.netpay(pay.standardhours, pay.standardminutes, pay.overtimehours, pay.overtimeminutes, employee.wagedollars, employee.wagecents, 1)
        else:
            netpay = self.netpay(pay.standardhours, pay.standardminutes, pay.overtimehours, pay.overtimeminutes, employee.wagedollars, employee.wagecents, 0)
    
        response = "employee-{}`week-{}`standardtime-{pay.standardhours}h{pay.standardminutes}m`overtime-{pay.overtimehours}h{pay.overtimeminutes}m`standardpay-${pay.standardpay:,.2f}`overtimepay-${pay.overtimepay:,.2f}`netpay-${netpay:,.2f}`\n".format(self.state['employees'][id].name, week, pay=pay, netpay=netpay)
        return response

    def query(self):
        for id in self.state['id_subset']:
            if self.chance(0.33):
                for week in range(0,52):
                    if self.chance(0.05):
                        self.write("query-week_all`week-{}`\n".format(week))
                        for id2 in self.state['id_subset']:
                            self.read(delim='\n', expect=self.get_response(id2, week))
                    else:
                        self.write("query-week`employee_id-{}`week-{}`\n".format(id, week))
                        self.read(delim='\n', expect=self.get_response(id, week))
            elif self.chance(0.50):
                self.write("query-one`employee_id-{}`\n".format(id))
                response = " "
                for week in range(0,52):
                   self.read(delim='\n', expect=self.get_response(id, week))
            else:
                self.write("query-all`\n")
                response = " "
                for id2 in self.state['id_subset']:
                    for week in range(0,52):
                        self.read(delim='\n', expect=self.get_response(id2, week))

    def quit(self):
        self.write("\n")
        self.read(delim='\n', expect="Exiting")
