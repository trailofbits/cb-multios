#!/usr/bin/env python

from generator.actions import Actions
import random
import string
from struct import pack

class DateTime(): #borrowed from divelogger

    def __init__ (self, year=0, month=0, day=0, hour=0, min=0, sec=0):
        self.year = year
        self.month = month
        self.day = day
        self.hour=hour
        self.min=min
        self.sec=sec
        self.time_t = 0

        count = 1970
        days_since_epoch = 0
        cumulative_days= [ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 ]

        if (year > 1969):
            while count < self.year:
                days_since_epoch+= 365+ self.leap_year(count)

            days_since_epoch+= cum_days_by_month[self.month-1]

            if self.month > 2:
                days_since_epoch+= self.leap_year(self.year)

            days_since_epoch+=self.day

            seconds_since_epoch = days_since_epoch * 86400

            seconds_since_epoch+= self.hour * 3600
            seconds_since_epoch+= self.min * 60
            seconds_since_epoch+= self.sec

            self.time_t = seconds_since_epoch


    def set_datetime(self, year, month, day, hour, min, sec):
        self.year=year
        self.month=month
        self.day=day
        self.hour=hour
        self.min=min
        self.sec=sec

    def leap_year(self, year):
        if ((year%400==0 or year%100!=0) and (year%4==0)):
            return 1
        else:
            return 0


    def set_datetime(self, time_t):

        day_seconds = 0
        num_days_since_epoch = 0
        cum_days_since_epoch = 0
        day_of_year = 0

        cum_days_by_month = [ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 ]


        self.time_t = time_t
        day_seconds = time_t % 86400
        self.hour = day_seconds / 3600
        self.min = day_seconds / 60 % 60
        self.sec = day_seconds % 60

        num_days_since_epoch = time_t / 86400
        cum_days_since_epoch = 0

        counter = 1970

        while (cum_days_since_epoch <= num_days_since_epoch):
            cum_days_since_epoch+=(365 + self.leap_year(counter))
            counter+=1

        self.year = counter - 1

        cum_days_since_epoch -= (365 + self.leap_year(self.year))

        day_of_year = num_days_since_epoch - cum_days_since_epoch + 1

        counter = 0

        while cum_days_by_month[counter] + ((counter>1) * self.leap_year(self.year)) < day_of_year:
            counter+=1

        self.month = counter

        self.day = day_of_year - cum_days_by_month[counter-1] - ((counter > 2) * self.leap_year(self.year))

    def print_date(self):

        return '{}/{}/{}'.format(self.month, self.day, self.year)

    def print_time(self):

        return '{:02d}:{:02d}:{:02d}'.format(self.hour, self.min, self.sec)

    def get_date(self):
    	return [self.year, self.month, self.day, self.hour, self.min, self.sec]


class Dates():

    def __init__ (self, year=0, month=0, day=0):
        self.year = year
        self.month = month
        self.day = day
        self.day_of_year()

    def set_date(self, year, month, day):
        self.year=year
        self.month=month
        self.day=day


    def print_date(self):

        if self.year > 0:
            return '{}/{}/{}'.format(self.month, self.day, self.year)
        else:
            return ''

    def is_leap_year(self):
        if ((self.year%400==0 or self.year%100!=0) and (self.year%4==0)):
            return 1
        else:
            return 0

    def day_of_year(self):

        cumulative_days= [ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 ]
        self.DOY=cumulative_days[self.month-1] + self.day;

        if self.month > 2:
            self.DOY+=self.is_leap_year()

        return self.DOY

    def date_from_doy(self, year, doy):
        pass


    def remaining_days(self):


        if (self.is_leap_year()):
            return (366-self.DOY);
        else:
            return (365-self.DOY)


    def compare_dates(x, y):

        if x.year > y.year:
            return 1
        elif x.year < y.year:
            return -1
        else:
            if x.month > y.month:
                return 1
            elif x.month < y.month:
                return -1
            else:
                if x.day > y.day:
                    return 1
                elif x.day < y.day:
                    return -1
                else:
                    return 0

    @classmethod
    def random_date(cls):

        tmpyear=random.randint(2015, 2019)
        tmpmonth=random.randint(1, 12)
        tmpday=random.randint(1, 28)    # cheat by picking an upper day of month that will be safe for Feb
        return cls(tmpyear, tmpmonth, tmpday)

    @classmethod
    def random_date_from_range(cls, start_year, end_year):

        tmpyear=random.randint(start_year, end_year)
        tmpmonth=random.randint(1, 12)
        tmpday=random.randint(1, 28)
        return cls(tmpyear, tmpmonth, tmpday)

####################################
###
####################################

class state():
	def __init__(self,date):
		self.userList = []
		self.userList.append("root")
		self.groupList = []
		self.groupList.append(["root",[]])
		self.groupList[0][1].append("root")
		self.nodeList = []
		self.nodeList.append(["root", "dir", date, []])
		self.date = date
		self.workingDir = self.nodeList[0]
		self.dirpath = [0]
		self.currentUser = self.userList[0]
		self.currentGroup = self.groupList[0]
		return

	def get_currentUser(self):	
		return self.currentUser

	def get_currentGroup(self):
		return self.currentGroup[0]

	def fix_workingDir(self):
		for i in self.dirpath:
			self.workingDir = self.workingDir[3][i]

	def add_directory(self,name, parent):
		#add_directory(name, self.oState.workingDir)
		parent[3].append([name, "dir", self.date, []])
		return

	def add_file(self,name,size,data,parent):
		parent[3].append([name, "file", self.date, size, data])
		return

	def change_dir_up(self):
		if len(self.dirpath) > 1:
			self.dirpath.pop()
		fix_workingDir()

	def change_dir(self,name):
		for i in self.workingDir:
			if (i[1] == "dir") and (i[0] == name):
				self.dirpath.append(i)
				self.workingDir = self.workingDir[3][i]


class CROMU00035(Actions):

	oState = state(0)
	oDate = DateTime()

	def write_date(self):	

		self.read(delim='\n', expect='Please enter the date as prompted')
		self.read(delim=':', expect='Enter year between 1970 and 2105 ')
		self.write(str(self.oDate.year) + '\n')
		self.read(delim=':', expect='Enter month ')
		self.write(str(self.oDate.month) + '\n')
		self.read(delim=':', expect='Enter day :')
		self.write(str(self.oDate.day) + '\n')
		self.read(delim=':', expect='Enter hour (00-23) ')
		self.write(str(self.oDate.hour) + '\n')		
		self.read(delim=':', expect='Enter Minute (00-59) ')
		self.write(str(self.oDate.min) + '\n')
		self.read(delim=':', expect='Enter second (00-59) ')
		self.write(str(self.oDate.sec) + '\n')

	def random_string(self, size):
		chars = string.letters + string.digits
		return ''.join(random.choice(chars) for _ in range(size))

	def random_digits(self, size):
		chars = string.digits
		return ''.join(random.choice(chars) for _ in range(size))

	def read_prompt(self):
		user = self.oState.get_currentUser()
		self.read(delim='@', expect=user)
		self.read(delim='/', expect="SPIFF:")
		self.read(delim='>', expect=r"([[:alnum:]]/)*", expect_format="pcre")

	def start(self):
		#initialize any context
		epoch = (1388534400 + random.randint(1, 86400*365))
		#epoch = random.randint(0, (2**32)-1)
		self.oDate.set_datetime(epoch)
		self.oState = state(epoch)
		return

	def banner(self):
		#banner for service
		self.read(delim='\n', expect='Welcome to SPIFFS (Somewhat Poorly Implemented Fast File System)')
		self.write_date()
		return

	def prompt(self):
		#main menu
		self.read_prompt()
		#prompt {"set", "get", "add", "delete","exit","help","ls","cat","cd"};
		#set {"date", "user", "group","help"};
		#get {"date", "user", "group", "workingDir","help", "userlist", "grouplist", "usersingroup"};
		#self.read
		return

	def set_date(self):
		self.write('set date\n')
		epoch = (1388534400 + random.randint(1, 86400*365))
		self.oDate.set_datetime(epoch)
		self.oState.date = epoch
		self.write_date()
		return

	def set_user(self):
		user = self.oState.userList[random.randint(0,len(self.oState.userList)-1)]
		self.oState.currentUser = user
		self.write('set user '+ user +'\n')

	def set_group(self):
		group = self.oState.groupList[random.randint(0,len(self.oState.groupList)-1)]
		self.oState.currentGroup = group
		self.write('set group '+ group[0] +'\n')

	def set_help(self):
		self.write('set help\n')
		self.read(delim='\n', expect="< date, user, group, help >")

	def get_date(self):
		self.write('get date\n')
		self.read(delim='\n', expect=r"([[:print:]])*", expect_format="pcre")	

	def get_user(self):
		user = self.oState.get_currentUser()		
		self.write('get user\n')
		self.read(delim='\n', expect=user)

	def get_group(self):
		group = self.oState.get_currentGroup()
		self.write('get group\n')
		self.read(delim='\n', expect=group)

	def get_workingDir(self):
		self.write('get workingDir\n')
		self.read(delim='\n', expect=r"([[:print:]])*", expect_format="pcre")	

	def get_help(self):
		self.write('get help\n')
		self.read(delim='\n', expect='< date, user, group, workingDir, help, userlist, grouplist, usersingroup >')

	def get_userlist(self):
		self.write('get userlist\n')
		self.read(delim='\n', expect="UID    NAME")
		self.read(delim='\n', expect="__________")
		count = 0

		for i in self.oState.userList:
			self.read(delim='\n', expect=str(count) + ' ' + i)
			count = count + 1

	def get_grouplist(self):
		self.write('get grouplist\n')
		count = 0
		self.read(delim='\n', expect="GUID     NAME")
		self.read(delim='\n', expect="____________________")
		for i in self.oState.groupList:
			self.read(delim='\n', expect=str(count) + ' ' + i[0])
			count = count + 1

	def get_usersingroup(self,last=False):
		self.write('get usersingroup ')
		if(last):
			groupNum = len(self.oState.groupList)-1
		if not(last):
			groupNum = random.randint(0,len(self.oState.groupList))-1
		groupname = self.oState.groupList[groupNum][0]
		self.write(groupname + '\n')		
		count = 0
		self.read(delim='\n', expect="Count Name")
		self.read(delim='\n', expect="____________________")
		if len(self.oState.groupList[groupNum][1]) > 0:
			for i in self.oState.groupList[groupNum][1]:
				self.read(delim='\n', expect=str(count) + ' ' + i)
				count = count + 1

	def add_user(self):
		self.write('add user ')
		username = self.random_string(random.randint(5,10))
		self.oState.userList.append(username)
		self.write(username + '\n')
		return

	def add_group(self):
		self.write('add group ')
		groupname = self.random_string(random.randint(5,10))
		self.oState.groupList.append([groupname,[]])
		self.write(groupname + '\n')
		return

	def add_file(self):
		self.write('add file ')
		#name
		filename = self.random_string(random.randint(5,10))
		size = random.randint(4,100)
		self.write(filename + ' ' + str(size) + '\n')
		filechunk = self.random_string(size)
		self.read(delim='\n', expect='-----Begin File-----')
		self.write(filechunk)
		#add file to oState
		self.oState.add_file(filename,size,filechunk,self.oState.workingDir)

		return
	def add_directory(self):
		self.write('add directory ')
		#name
		directoryname = self.random_string(random.randint(5,10))
		self.oState.add_directory(directoryname,self.oState.workingDir)
		#add directory to oState
		self.write(directoryname + '\n')

		return
	def add_usertogroup(self):
		#add user and group to make test better
		self.add_user()
		self.prompt()
		self.add_group()
		self.prompt()
		#self.set_group()
		group = self.oState.groupList[-1]
		self.oState.currentGroup = group
		self.write('set group '+ group[0] +'\n')
		#group is now set to new, empty group

		self.prompt()
		#pick user from userlist
		user = self.oState.userList[random.randint(0,len(self.oState.userList)-1)]
		self.write('add usertogroup ' + user + '\n')

		#work on currentgroup
		self.oState.currentGroup[1].append(user)
		return

	def _add_perm(self):
		#make sure there is a user group and file in workingDir
		self.add_user()
		self.prompt()		
		self.add_group()
		self.prompt()
		self.add_file()
		self.prompt()
		#cheat and pick last which is file
		filetmp = self.oState.workingDir[3][-1]
		filename = filetmp[0]
		username = self.oState.userList[-1]
		groupname = self.oState.groupList[-1][0]
		self.write('add perm ' + filename + ' user ' + username + '\n')
		self.prompt()
		self.write('add perm ' + filename + ' group ' + groupname + '\n')
		return filename, username, groupname

	def add_perm(self):
		self._add_perm()
		return

	def add_help(self):
		self.write('add help\n')
		self.read(delim='\n', expect='< user, group, file, directory, usertogroup, perm, appendfile, help >')
		return

	def delete_user(self):
		#add a user to delete it, so there is a user to delete
		self.add_user()
		self.read_prompt()
		self.get_userlist()
		self.read_prompt()
		username = self.oState.userList[-1]
		self.write("delete user " + username +'\n')
		self.oState.userList.pop()
		return

	def delete_group(self):
		self.add_group()
		self.read_prompt()
		groupname = self.oState.groupList[-1][0]
		self.write("delete group " + groupname + '\n')
		self.oState.groupList.pop()
		return

	def delete_file(self):
		self.add_file()
		self.read_prompt()
		self.ls()
		self.read_prompt()
		filename = self.oState.workingDir[3][-1][0]
		self.write("delete file " + filename + '\n')
		self.oState.workingDir[3].pop()
		return

	def delete_directory(self):
		self.add_directory()
		self.read_prompt()
		#do an ls
		dirname = self.oState.workingDir[3][-1][0]
		self.write("delete directory " + dirname + '\n')
		self.oState.workingDir[3].pop()
		return

	def delete_usertogroup(self):
		self.add_user()
		self.read_prompt()
		self.add_group()
		self.read_prompt()
		self.add_usertogroup()
		self.read_prompt()
		self.get_usersingroup(True)
		self.read_prompt()
		groupNum = len(self.oState.groupList)-1
		groupname = self.oState.groupList[-1][0]
		username = self.oState.groupList[-1][1][-1]
		self.write("delete usertogroup " + username + ' ' + groupname + '\n')
		self.oState.groupList[-1][1].pop()
		return

	def delete_perm(self):
		self.add_file()
		self.read_prompt()
		self.add_user()
		self.read_prompt()
		filename, username, groupname = self._add_perms()
		self.read_prompt()
		self.ls()
		self.read_prompt()
		self.write("delete perm " + filename  + username + '\n')
		self.read_prompt()
		self.ls()
		self.read_prompt()
		self.write("delete perm " + filename  + groupname + '\n')
		self.read_prompt()
		self.ls()
		return
	def delete_filebytes(self):
		self.add_file()
		self.read_prompt()
		filet = self.oState.workingDir[3][-1] 
		filename = filet[0]
		filesize = filet[3]
		if filesize > 1:
			self.write("delete filebytes " + filename + ' ' + str(filesize-1)+ '\n')
		else:
			self.ls()

	def delete_help(self):
		self.write("delete help\n")
		self.read(delim='\n', expect='< user, group, file, directory, usertogroup, perm, filebytes, help >')

	def help(self):
		self.write('help\n')
		self.read(delim='\n', expect='< set, get, add, delete, exit, help, ls, cat, cd >')

	def ls(self):
		self.write('ls\n')
		self.read(delim='\n', expect='Type  Size     Date     Name       Perms')
		self.read(delim='\n', expect='_______________________________________')
		for i in self.oState.workingDir[3]:
			self.read(delim='\n', expect=r"([[:print:]])*", expect_format="pcre")

	def cat(self):
		self.add_file()
		self.prompt()
		filetmp = self.oState.workingDir[3][-1]
		filename = filetmp[0]
		filelen = filetmp[3]
		filedata = filetmp[4]
		self.write('cat ' + filename + '\n')
		self.read(delim='\n', expect="-----Begin File-----")
		self.read(length=filelen, expect=r"([[:print:]])*", expect_format="pcre")
		self.read(delim='\n', expect="-----END File-----")

		#filename

	def cd(self):
		self.add_directory()
		self.read_prompt()
		index = len(self.oState.workingDir[3])-1
		dirname = self.oState.workingDir[3][-1][0]
		self.write('cd ' + dirname +'\n' )
		self.oState.workingDir = self.oState.workingDir[3][-1]
		self.oState.dirpath.append(index)

		#directory or ..

	def exit(self):
		#any context cleanup and select exit
		self.write("exit\n")
		return
