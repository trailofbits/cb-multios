#!/usr/bin/env python

from generator.actions import Actions
import random
from struct import pack


class ProposalGenerator(Actions):


    def start(self):

        self.DiverFirstName = ''
        self.DiverLastName = ''
        self.DiverAddress = ''
        self.DiverCity = ''
        self.DiverState = ''
        self.DiverZip = ''
        self.DiverPhone = ''
        self.DiverPadiNum = ''
        self.DiverPadiDate = ''
        self.dive_entries_count = 0;
        self.dive_entries=[]

        self.dive_site_name = ''
        self.dive_date = ''
        self.dive_time = ''
        self.dive_location = ''
        self.dive_max_depth = 0
        self.dive_avg_depth = 0
        self.dive_duration = 0
        self.dive_o2 = 0
        self.dive_pressure_in = 0
        self.dive_pressure_out = 0
        self.dive_bincount = 0

        self.read_main_menu_text()

    def read_main_menu_text(self):


        self.read(delim='\n', expect='\n')
        self.read(delim='\n', expect='C - Change Diver Info')
        self.read(delim='\n', expect='L - Log a New Dive')
        self.read(delim='\n', expect='D - Download Dive Data')
        self.read(delim='\n', expect='E - Edit Dives')
        self.read(delim='\n', expect='P - Print Dive Logs')
        self.read(delim='\n', expect='R - Remove Dives')
        self.read(delim='\n', expect='S - Diver Statistics')
        self.read(delim='\n', expect='X - Exit Application')

    def menu(self):

        pass

    def exit(self):

        self.read(delim=':', expect=':')
        self.write(random.choice('xX') + '\n')

    def enter_a_dive(self):

        mydate = DateTime()
        mydate.set_datetime(1388534400 + random.randint(1, 86400*365))

        self.read(length=1, expect=':')
        self.write(random.choice('lL') + '\n')
        self.read(delim='\n', expect='\n')
  

        dive_site = ''.join(random.choice('abcdefghijklmnop') for _ in range(10))
        dive_date = mydate.print_date()
        dive_time = mydate.print_time()
        dive_location = ''.join(random.choice('abcdefghijklmnop') for _ in range(10))

        max_depth = random.randint(20, 130)
        avg_depth = max_depth/2;
        duration = random.randint(20, 55)
        dive_o2 = random.randint(21, 50)
        psi_in = random.randint(3000, 3200)
        psi_out = random.randint(400, 1000)


        self.read(length=11, expect='Dive Site: ')
        self.write(dive_site + '\n')

        self.read(length=6, expect='Date: ')
        self.write(dive_date+'\n')

        self.read(length=6, expect='Time: ')

        self.write(dive_time+'\n')

        self.read(length=22, expect='Location (area/city): ')

        self.write(dive_location+ '\n')

        self.read(length=17, expect='Max Depth in ft: ')
        self.write('{}'.format(max_depth)+'\n')

        self.read(length=17, expect='Avg Depth in ft: ')
        self.write('{}'.format(avg_depth)+'\n')

        self.read(length=22, expect='Dive Duration (mins): ')
        self.write('{}'.format(duration)+'\n')

        self.read(length=15, expect='O2 Percentage: ')
        self.write('{}'.format(dive_o2)+'\n')
 
        self.read(length=19, expect='Pressure In (psi): ')
        self.write('{}'.format(psi_in)+'\n')        

        self.read(length=20, expect='Pressure Out (psi): ')
        self.write('{}'.format(psi_out)+'\n')

        self.dive_entries.append((dive_site, dive_date, dive_time, dive_location, max_depth, avg_depth, duration, dive_o2, psi_in, psi_out, 0))
        self.dive_entries_count+=1
        

        self.read_main_menu_text()


    def read_dive_list(self):

        self.read(delim='\n', expect='\n')

        if self.dive_entries_count==0:

            self.read(delim='\n', expect='Dive Log is empty\n')
            return

        expect_string = 'Dive# {:<10} {:<8} {:<25} {:<25}\n'.format('Date', 'Time', 'Dive Site', 'Location')
        self.read(delim='\n', expect=expect_string) 

        i = 0
        while (i < self.dive_entries_count): 
            expect_string = '{:4}: {:<10} {:<8} {:<25} {:<25}\n'.format(i+1, self.dive_entries[i][1],
                                        self.dive_entries[i][2] , self.dive_entries[i][0],
                                        self.dive_entries[i][3])
            self.read(delim='\n', expect=expect_string)
            i+=1


    def print_dives (self):

        self.read(length=1, expect=':')
        self.write(random.choice('pP') + '\n')
        self.read(delim='\n', expect='\n')

        self.read_dive_list()

        if self.dive_entries_count == 0:
            self.read_main_menu_text()
            return

        self.read(delim='\n', expect='\n')
        expect_string='Enter Dive # to display: '

        self.read(length=len(expect_string), expect=expect_string)

        dive_to_show = random.randint(1, self.dive_entries_count)

        self.write('{}'.format(dive_to_show) + '\n')

        dive_to_show-=1

        self.read(delim='\n', expect='\n')
        self.read(delim='\n', expect='          Date: ' + self.dive_entries[dive_to_show][1]+ '\n')
        self.read(delim='\n', expect='          Time: ' + self.dive_entries[dive_to_show][2]+ '\n')
        self.read(delim='\n', expect='     Dive Site: ' + self.dive_entries[dive_to_show][0] + '\n')
        self.read(delim='\n', expect='      Location: ' + self.dive_entries[dive_to_show][3] + '\n')
        self.read(delim='\n', expect='     Max Depth: ' + '{}'.format(self.dive_entries[dive_to_show][4]) + '\n')
        self.read(delim='\n', expect='     Avg Depth: ' + '{}'.format(self.dive_entries[dive_to_show][5])+ '\n')
        self.read(delim='\n', expect='      Duration: ' + '{}'.format(self.dive_entries[dive_to_show][6]) + '\n')
        self.read(delim='\n', expect='    O2 Percent: ' + '{}'.format(self.dive_entries[dive_to_show][7]) + '\n')
        self.read(delim='\n', expect='Start Pressure: ' + '{}'.format(self.dive_entries[dive_to_show][8]) + '\n')
        self.read(delim='\n', expect='  End Pressure: ' + '{}'.format(self.dive_entries[dive_to_show][9]) + '\n')
        self.read(delim='\n', expect='     Bin Count: ' + '{}'.format(self.dive_entries[dive_to_show][10]) + '\n')
        self.read(delim='\n', expect='\n')

        self.read_main_menu_text()

    def remove_dive(self):

        self.read(length=1, expect=':')
        self.write(random.choice('rR') + '\n')
        self.read(delim='\n', expect='\n')

        self.read_dive_list()

        if self.dive_entries_count == 0:
            self.read_main_menu_text()
            return

        self.read(delim='\n', expect='\n')
        expect_string='Enter Dive # to delete or blank to abort: '

        self.read(length=len(expect_string), expect=expect_string)

        dive_to_edit = random.randint(1, self.dive_entries_count)

        self.write('{}'.format(dive_to_edit) + '\n')

        del self.dive_entries[dive_to_edit-1]

        self.dive_entries_count-=1

        self.read_main_menu_text()

    def download_dive(self):

        rand_time_t = 1388534400 + random.randint(1, 86400*365)
        mydate = DateTime()
        mydate.set_datetime(rand_time_t)

        dive_site = ''.join(random.choice('abcdefghijklmnop') for _ in range(10))
        dive_date = mydate.print_date()
        dive_time = mydate.print_time()
        dive_location = ''.join(random.choice('abcdefghijklmnop') for _ in range(10))

        max_depth = 0
        avg_depth = 0
        sum_samples = 0
        count_samples = 0
        duration = random.randint(3, 30)
        dive_o2 = random.randint(21, 50)
        psi_in = random.randint(3000, 3200)
        psi_out = random.randint(400, 1000)

        self.read(length=1, expect=':')
        self.write(random.choice('dD') + '\n')
        self.read(delim='\n', expect='\n')

        counter = 0

        while counter <= duration:

            mydate.set_datetime(rand_time_t)
            depth = random.randint(1, 130)

            sum_samples+=depth
            count_samples+=1

            if depth > max_depth:
                max_depth=depth

            self.write(pack('<L', mydate.time_t))

            self.write(pack('<L', depth))

            rand_time_t+=60
            counter+=1


        self.write(pack('<L', 0))

        avg_depth=sum_samples/count_samples


        self.read(length=11, expect='Dive Site: ')
        self.write(dive_site + '\n')

        expect_string= 'Date ('+ dive_date +'): '

        self.read(length=len(expect_string), expect=expect_string)

        self.write(dive_date+'\n')

        expect_string= 'Time ('+ dive_time +'): '
        self.read(length=len(expect_string), expect=expect_string)

        self.write(dive_time+'\n')

        self.read(length=22, expect='Location (area/city): ')

        self.write(dive_location+ '\n')

        expect_string= 'Max Depth in ft ('+ '{}'.format(max_depth)+'): '

        self.read(length=len(expect_string), expect=expect_string)

        self.write('\n')

        expect_string= 'Avg Depth in ft ('+ '{}'.format(avg_depth)+'): '

        self.read(length=len(expect_string), expect=expect_string)

        self.write('\n')

        expect_string= 'Dive Duration (mins) ('+ '{}'.format(duration)+'): '

        self.read(length=len(expect_string), expect=expect_string)

        self.write('\n')

        self.read(length=15, expect='O2 Percentage: ')
        self.write('{}'.format(dive_o2)+'\n')
 
        self.read(length=19, expect='Pressure In (psi): ')
        self.write('{}'.format(psi_in)+'\n')        

        self.read(length=20, expect='Pressure Out (psi): ')
        self.write('{}'.format(psi_out)+'\n')

        self.dive_entries.append((dive_site, dive_date, dive_time, dive_location, max_depth, avg_depth, duration, dive_o2, psi_in, psi_out, duration+1))
        self.dive_entries_count+=1
        

        self.read_main_menu_text()


    def edit_dive(self):

        mydate = DateTime()
        mydate.set_datetime(1388534400 + random.randint(1, 86400*365))


        dive_site = ''.join(random.choice('abcdefghijklmnop') for _ in range(10))
        dive_date = mydate.print_date()
        dive_time = mydate.print_time()
        dive_location = ''.join(random.choice('abcdefghijklmnop') for _ in range(10))

        max_depth = random.randint(20, 130)
        avg_depth = max_depth/2
        duration = random.randint(20, 55)
        dive_o2 = random.randint(21, 50)
        psi_in = random.randint(3000, 3200)
        psi_out = random.randint(400, 1000)

        self.read(length=1, expect=':')
        self.write(random.choice('eE') + '\n')
        self.read(delim='\n', expect='\n')


        self.read_dive_list()

        if self.dive_entries_count == 0:
            self.read_main_menu_text()
            return
      
        self.read(delim='\n', expect='\n')
        expect_string='Enter Dive # to edit: '

        self.read(length=len(expect_string), expect=expect_string)

        dive_to_edit = random.randint(1, self.dive_entries_count+1)

        self.write('{}'.format(dive_to_edit) + '\n')

        if dive_to_edit > self.dive_entries_count:
            self.read(delim='\n', expect='Invalid dive number entered\n')
            self.read_main_menu_text()
            return 0
        else:
            self.read(delim='\n')

            expect_string= 'Dive Site ('+self.dive_entries[dive_to_edit-1][0]+'): '

            self.read(length=len(expect_string), expect=expect_string)
            self.write(dive_site+'\n')

            expect_string= 'Date ('+self.dive_entries[dive_to_edit-1][1]+'): '

            self.read(length=len(expect_string), expect=expect_string)
            self.write(dive_date+'\n')

            expect_string= 'Time ('+self.dive_entries[dive_to_edit-1][2]+'): '

            self.read(length=len(expect_string), expect=expect_string)
            self.write(dive_time+'\n')

            expect_string= 'Location (area/city) ('+self.dive_entries[dive_to_edit-1][3]+'): '

            self.read(length=len(expect_string), expect=expect_string)
            self.write(dive_location+'\n')

            expect_string= 'Max Depth in ft ('+ '{}'.format(self.dive_entries[dive_to_edit-1][4])+'): '

            self.read(length=len(expect_string), expect=expect_string)
            self.write('{}'.format(max_depth)+'\n')

            expect_string= 'Avg Depth in ft ('+ '{}'.format(self.dive_entries[dive_to_edit-1][5])+'): '

            self.read(length=len(expect_string), expect=expect_string)
            self.write('{}'.format(avg_depth)+'\n')

            expect_string= 'Dive Duration (mins) ('+ '{}'.format(self.dive_entries[dive_to_edit-1][6])+'): '

            self.read(length=len(expect_string), expect=expect_string)
            self.write('{}'.format(duration)+'\n')

            expect_string= 'O2 Percentage ('+ '{}'.format(self.dive_entries[dive_to_edit-1][7])+'): '

            self.read(length=len(expect_string), expect=expect_string)
            self.write('{}'.format(dive_o2)+'\n')

            expect_string= 'Pressure In (psi) ('+ '{}'.format(self.dive_entries[dive_to_edit-1][8])+'): '

            self.read(length=len(expect_string), expect=expect_string)
            self.write('{}'.format(psi_in)+'\n')

            expect_string= 'Pressure Out (psi) ('+ '{}'.format(self.dive_entries[dive_to_edit-1][9])+'): '

            self.read(length=len(expect_string), expect=expect_string)
            self.write('{}'.format(psi_out)+'\n')


            self.dive_entries[dive_to_edit-1]=(dive_site, dive_date, dive_time, dive_location, max_depth, avg_depth, duration, dive_o2, psi_in, psi_out, self.dive_entries[dive_to_edit-1][10])

            self.read_main_menu_text()


    def enter_diver_info (self):


        self.read(length=1, expect=':')
        self.write(random.choice('cC') + '\n')
        self.read(delim='\n', expect='\n')

        if self.DiverFirstName == '':
            self.read(length=12, expect='First Name: ')
            self.DiverFirstName = ''.join(random.choice('abcdefghijklmnop') for _ in range(random.randint(1, 25)))
            self.write(self.DiverFirstName+ '\n')
            self.DiverFirstName=self.DiverFirstName[:20]
        else:
            self.read(length=15+len(self.DiverFirstName), expect='First Name (' + self.DiverFirstName + '): ')
            self.write('\n')

        if self.DiverLastName == '':
            self.read(length=11, expect='Last Name: ')
            self.DiverLastName = ''.join(random.choice('abcdefghijklmnop') for _ in range(random.randint(1,25)))
            self.write(self.DiverLastName+ '\n')
            self.DiverLastName=self.DiverLastName[:20]
        else:
            self.read(length=14+len(self.DiverLastName), expect='Last Name (' + self.DiverLastName + '): ')
            self.write('\n')

        if self.DiverAddress == '':
            self.read(length=8, expect='Street: ')
            self.DiverAddress = ''.join(random.choice('abcdefghijklmnop') for _ in range(random.randint(10,35)))
            self.write(self.DiverAddress+ '\n')
            self.DiverAddress=self.DiverAddress[:29]
        else:
            self.read(length=11+len(self.DiverAddress), expect='Street (' + self.DiverAddress + '): ')
            self.write('\n')

        if self.DiverCity== '':
            expect_string = 'City: '
            self.read(length=len(expect_string), expect=expect_string)
            self.DiverCity = ''.join(random.choice('abcdefghijklmnop') for _ in range(random.randint(5, 21)))
            self.write(self.DiverCity+ '\n')
            self.DiverCity=self.DiverCity[:19]
        else:
            expect_string= 'City ('+self.DiverCity+'): '
            self.read(length=len(expect_string), expect=expect_string)
            self.write('\n')

        if self.DiverState== '':
            expect_string = 'State: '
            self.read(length=len(expect_string), expect=expect_string)
            self.DiverState = ''.join(random.choice('abcdefghijklmnop') for _ in range(random.randint(1,4)))
            self.write(self.DiverState+ '\n')
            self.DiverState=self.DiverState[:2]
        else:
            expect_string= 'State ('+self.DiverState+'): '
            self.read(length=len(expect_string), expect=expect_string)
            self.write('\n')

        if self.DiverZip== '':
            expect_string = 'Zip Code: '
            self.read(length=len(expect_string), expect=expect_string)
            self.DiverZip = ''.join(random.choice('1234567890') for _ in range(random.randint(5, 12)))
            self.write(self.DiverZip + '\n')
            self.DiverZip=self.DiverZip[:10]
        else:
            expect_string= 'Zip Code ('+self.DiverZip+'): '
            self.read(length=len(expect_string), expect=expect_string)
            self.write('\n')

        if self.DiverPhone== '':
            expect_string = 'Phone Number: '
            self.read(length=len(expect_string), expect=expect_string)
            self.DiverPhone = ''.join(random.choice('1234567890') for _ in range(random.randint(10, 17)))
            self.write(self.DiverPhone + '\n')
            self.DiverPhone=self.DiverPhone[:15]
        else:
            expect_string= 'Phone Number ('+self.DiverPhone+'): '
            self.read(length=len(expect_string), expect=expect_string)
            self.write('\n')

        if self.DiverPadiNum== '':
            expect_string = 'PADI Diver Number: '
            self.read(length=len(expect_string), expect=expect_string)
            self.DiverPadiNum = ''.join(random.choice('1234567890') for _ in range(random.randint(15,22)))
            self.write(self.DiverPadiNum + '\n')
            self.DiverPadiNum=self.DiverPadiNum[:19]
        else:
            expect_string= 'PADI Diver Number ('+self.DiverPadiNum+'): '
            self.read(length=len(expect_string), expect=expect_string)
            self.write('\n')

        if self.DiverPadiDate== '':
            expect_string = 'PADI Cert Date: '
            self.read(length=len(expect_string), expect=expect_string)
            self.DiverPadiDate = ''.join(random.choice('1234567890') for _ in range(random.randint(9,11)))
            self.write(self.DiverPadiDate + '\n')
            self.DiverPadiDate=self.DiverPadiDate[:10]
        else:
            expect_string= 'PADI Cert Date ('+self.DiverPadiDate+'): '
            self.read(length=len(expect_string), expect=expect_string)
            self.write('\n')      


        self.read(delim='\n', expect='\n')
        self.read(delim='\n', expect='     Name: '+ self.DiverFirstName + ' ' + self.DiverLastName + '\n')
        self.read(delim='\n', expect='  Address: ' + self.DiverAddress+ '\n')
        self.read(delim='\n', expect='     City: ' + self.DiverCity + '\n')
        self.read(delim='\n', expect='    State: ' + self.DiverState + '\n')
        self.read(delim='\n', expect=' Zip Code: ' + self.DiverZip + '\n')
        self.read(delim='\n', expect='    Phone: ' + self.DiverPhone+ '\n')
        self.read(delim='\n', expect=' PADI Num: ' + self.DiverPadiNum + '\n')
        self.read(delim='\n', expect='Cert Date: ' + self.DiverPadiDate + '\n')
        self.read(delim='\n', expect='\n')

        self.read_main_menu_text()

    def dive_statistics(self):

        sum_avg_depth = 0
        avg_depth_count = 0
        sum_length = 0
        avg_length_count = 0

        self.read(length=1, expect=':')
        self.write(random.choice('sS') + '\n')
        self.read(delim='\n', expect='\n')

        if self.dive_entries_count==0:

            self.read(delim='\n', expect='\n')
            self.read(delim='\n', expect='No dives are logged\n')

            self.read_main_menu_text()
            return

        i = 0
        while (i < self.dive_entries_count): 

            if self.dive_entries[i][4] != 0:
                sum_avg_depth+= self.dive_entries[i][4];
                avg_depth_count+=1

            if self.dive_entries[i][6] != 0:
                sum_length += self.dive_entries[i][6]
                avg_length_count += 1
    
            i+=1

        avg_depth = sum_avg_depth/avg_depth_count;
        avg_length = sum_length/avg_length_count;

        self.read(delim='\n', expect='\n')

        expect_string = 'Dives logged: '+ '{}'.format(self.dive_entries_count)

        self.read(delim='\n', expect=expect_string)

        expect_string = 'Average Max Depth: ' + '{}'.format(avg_depth)
        self.read(delim='\n', expect=expect_string)

        expect_string = 'Average Dive Length: ' + '{}'.format(avg_length)
        self.read(delim='\n', expect=expect_string)

        self.read_main_menu_text()

class DateTime():

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


