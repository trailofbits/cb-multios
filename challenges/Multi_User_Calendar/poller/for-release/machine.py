from generator.actions import Actions
import random
import string
import struct
import numpy as np
import math
import datetime as dt

MAX_NAME = 20
MAX_DESC = 200

def random_word(max_size=7, min_size=3):
    characters = string.letters
    max_size = max_size if max_size >= min_size else min_size
    max_size = random.randint(min_size, max_size)
    return ("".join(random.choice(characters) for c in range(max_size))).lower()

def random_text(max_words=32, min_words=3):
    max_words = max_words if max_words >= min_words else min_words
    text = ''
    for x in xrange(random.randint(min_words, max_words)):
        text += random_word() + ' '
    return text

def random_username(max_size=MAX_NAME, min_size=1):
    return random_word(MAX_NAME, 1)

def random_date(min_date=None):
    if not min_date:
        year = random.randint(2015, 2020)
        month = random.randint(1, 12)
        day = random.randint(1,28)
        year = 2016
        month = 8
        day = 4
        return dt.datetime(year, month, day)
    else:
        return min_date + dt.timedelta(days=random.randint(1,20))

def random_time(date, min_time=None):
    if not min_time:
        hour = random.randint(0, 23)
        minute = random.randint(0, 59)
        return dt.datetime(date.year, date.month, date.day, hour, minute)
    else:
        return min_time + dt.timedelta(minutes=random.randint(1,1000))

class Event(object):
    def __init__(self, id, name, desc, start, end, is_all_day):
        self.id = id
        self.name = name
        self.desc = desc
        self.start = start
        self.end = end
        self.is_all_day = is_all_day

class User:
    def __init__(self, id, username, about):
        self.id = id
        self.username = username
        self.about = about
        self.events = []

class Calendar(Actions):
    def _datestr(self, cur_date):
        return cur_date.strftime('%m-%d-%Y').lstrip("0").replace("-0", "-")

    def _timestr(self, cur_time):
        timestr = cur_time.strftime('%H:%M')
        if (timestr[0:2] == '00'):
            return timestr[1:]
        else:
            return timestr.lstrip("0")

    def _find_user(self, username):
        for user in self.all_users:
            if username == user.username:
                return user
        return None

    def _find_user_event(self, id):
        for event in self.cur_user.events:
            if id == event.id:
                return event
        return None

    def _find_user_event_day(self, day):
        events = []
        for event in self.cur_user.events:
            if event.start <= day <= event.end:
                events.append(event)
        return events

    def _find_user_event_month(self, day):
        events = []
        for event in self.cur_user.events:
            if event.start.month == day.month or event.end.month == day.month:
                events.append(event)
        return events

    def _find_user_event_agenda(self, day):
        lyear = day.year
        lmonth = day.month + 3
        lday = day.day
        if lmonth > 12:
            lyear += 1
            lmonth %= 12

        lookahead = dt.datetime(lyear, lmonth, lday)
        events = []
        i = 0
        for event in self.cur_user.events:
            if day <= event.start <= lookahead and i < 8:
                events.append(event)
                i += 1
            else:
                break
        return events

    def _read(self, data):
        self.read(length=len(data), expect=data)

    def _read_user_menu(self):
        self._read("Options:\n")
        self._read("1. View users\n")
        self._read("2. Add user\n")
        self._read("3. Remove user\n")
        self._read("4. Set user\n")
        self._read("5. View Calendar\n")
        self._read("6. Change Date\n")
        self._read("7. Exit\n")
        if self.cur_user:
            self._read("---Current User is *%s*---\n" % (self.cur_user.username))
        else:
            self._read("---Current User is *%s*---\n" % (self.cur_user))
        self._read("---Today's date is ")
        self._read(self._datestr(self.cur_date))
        self._read("---\n")
        self._read("Selection: ")

    def _read_calendar_menu(self):
        self._read("Options:\n")
        self._read("1. View Day\n")
        self._read("2. View Month\n")
        self._read("3. View Agenda\n")
        self._read("4. Change Date\n")
        self._read("5. Change View Date\n")
        self._read("6. Add Calendar Event\n")
        self._read("7. Remove Calendar Event\n")
        self._read("8. Return to User Selection\n")
        self._read("---Current User is *%s*---\n" % self.cur_user.username)
        self._read("---Today's date is ")
        self._read(self._datestr(self.cur_date))
        self._read("---\n")
        self._read("---Calendar view date is ")
        self._read(self._datestr(self.view_date))
        self._read("---\n")

        self._read("Selection: ")

    def _read_user(self, user):
        if not user:
            return
        self._read("User id = %d\n" % user.id)
        self._read("Username is \"%s\"\n" % user.username)
        self._read("About %s: %s\n" % (user.username, user.about))
        self._read("---------------------\n")

    def _read_event(self, event):
        self._read("Event ID: %d - %s\n" % (event.id, event.name))
        self._read("About the event: %s\n" % (event.desc))
        if event.is_all_day == 'y':
            self._read("Starts %s\n" % (self._datestr(event.start)))
            self._read("Ends %s\n" % (self._datestr(event.end)))
        else:
            self._read("Starts %s @ %s\n" % (self._datestr(event.start), self._timestr(event.start)))
            self._read("Ends %s @ %s\n" % (self._datestr(event.end), self._timestr(event.end)))

    def _bad_choice(self):
        self.write("-1\n")
        self._read("Try again\n")

    def start(self):
        #self.delay(100)
        self.all_users = []
        self.cur_user = None
        self.cur_date = dt.datetime(2016, 8, 4)
        self.view_date = dt.datetime(2016, 8, 4)
        self.mode = 'user'
        self.global_user_id = 0
        self.global_event_id = 0

        self.write(self.magic_page[:4])
        self.read(length=0x1000, expect=self.magic_page)

    def main_menu(self):
        if self.mode == 'user':
            self._read_user_menu()
        else:
            self._read_calendar_menu()

    def view_users(self):
        if self.mode != 'user':
            self._bad_choice()
            return
        self.write("1\n")
        self._read("------All Users------\n")
        for user in self.all_users:
            self._read_user(user)

    def add_users(self):
        if self.mode != 'user':
            self._bad_choice()
            return
        self.write('2\n')
        new_user = False
        while not new_user:
            username = random_username()
            new_user = not self._find_user(username)
            self._read('Enter username: ')
            self.write(username + '\n')
            if not new_user:
                self._read('Try again\n')

        about = random_text()
        self._read('Enter a short "about me" section.: ')
        self.write(about + '\n')
        user = User(self.global_user_id, username, about)
        self.all_users.append(user)
        self.all_users = sorted(self.all_users, key=lambda user: user.username)
        self._read("Successfully added user\n")
        self.global_user_id += 1

    def remove_user(self):
        if self.mode != 'user':
            self._bad_choice()
            return
        self.write('3\n')
        self._read('Enter username: ')
        do_remove = random.randint(1,10) == 1
        if do_remove and len(self.all_users):
            idx = random.randint(1, len(self.all_users)) - 1
            user = self.all_users.pop(idx)
            self.cur_user = None if user == self.cur_user else self.cur_user
            self.write(user.username + '\n')
            self._read('Suceessfully deleted user\n')
        else:
            self.write('\n')
            self._read('User not found\n')

    def set_user(self):
        if self.mode != 'user':
            self._bad_choice()
            return
        self.write('4\n')
        self._read("------All Users------\n")
        for user in self.all_users:
            self._read_user(user)
        self._read("Entering a username will set it as the current user\n")
        self._read('Enter username: ')
        do_set_user = random.randint(1,4) == 1
        if do_set_user and len(self.all_users):
            idx = random.randint(1, len(self.all_users)) - 1
            user = self.all_users[idx]
            self.write(user.username + '\n')
            self.cur_user = user
        else:
            self.write('\n')
            self._read('User not set\n')

    def view_calendar(self):
        if self.mode != 'user':
            self._bad_choice()
            return
        self.write('5\n')
        if not self.cur_user:
            self._read('Must select a user before viewing a calendar\n')
        else:
            self.mode = 'cal'

    def change_date(self):
        if self.mode == 'user':
            self.write('6\n')
        else:
            self.write('4\n')
        self._read('Enter new date (MM-DD-YYYY): ')
        do_change = random.randint(1,10) == 1
        if do_change:
            self.cur_date = random_date()
            self.view_date = self.cur_date
            self.write(self._datestr(self.cur_date) + '\n')
            self._read('Date successfully changed\n')
        else:
            self.write('\n')
            self._read('Date not changed\n')

    def view_day(self):
        if self.mode != 'cal':
            self._bad_choice()
            return
        self.write('1\n')
        self._read('Viewing Calendar Appointments for %s\n' % self._datestr(self.view_date))
        events = self._find_user_event_day(self.view_date)
        for event in events:
            self._read('------------------------\n')
            self._read_event(event)
        self._read('------------------------\n')

    def view_month(self):
        if self.mode != 'cal':
            self._bad_choice()
            return
        self.write('2\n')
        self._read('Viewing Monthly Calendar for %s\n' % self.view_date.strftime("%B %Y"))
        events = self._find_user_event_month(self.view_date)
        for event in events:
            self._read('------------------------\n')
            self._read_event(event)
        self._read('------------------------\n')

    def view_agenda(self):
        if self.mode != 'cal':
            self._bad_choice()
            return
        self.write('3\n')
        self._read('Agenda View\n')
        events = self._find_user_event_agenda(self.view_date)
        for event in events:
            self._read('------------------------\n')
            self._read_event(event)
        self._read('------------------------\n')

    def change_view_date(self):
        if self.mode != 'cal':
            self._bad_choice()
            return
        self.write('5\n')
        self._read('Enter date to view (MM-DD-YYYY): ')
        do_change = random.randint(1,10) == 1
        if do_change:
            self.view_date = random_date()
            self.write(self._datestr(self.view_date) + '\n')
            self._read('Successfully changed calendar view date\n')
        else:
            self.write('\n')
            self._read('Date not changed\n')


    def add_user_event(self):
        if self.mode != 'cal':
            self._bad_choice()
            return
        self.write('6\n')
        event_name = random_text(15)
        event_desc = random_text()
        start_date = random_date()
        start_time = random_time(start_date)
        all_day = 'y' if random.randint(1,3) != 1 else 'n'
        all_day = 'y'
        if random.randint(1,3) == 1:
            end_date = random_date(start_date)
            end_time = random_time(end_date)
        else:
            end_date = start_date
            end_time = random_time(start_time, start_time)
        if all_day == 'y':
            start_time = dt.datetime(start_date.year, start_date.month, start_date.day, 0, 0)
            end_time = dt.datetime(end_date.year, end_date.month, end_date.day, 23, 59)

        self._read('Event Name: ')
        self.write(event_name + '\n')
        self._read('Event Description: ')
        self.write(event_desc + '\n')
        self._read('Start Date (MM-DD-YYYY): ')
        self.write(self._datestr(start_time.date()) + '\n')
        self._read("End Date (MM-DD-YYYY) [%s]: " % self._datestr(start_time))
        self.write(self._datestr(end_time.date()) + '\n')
        self._read("All day event? (y/n) [n]: ")
        self.write(all_day + '\n')
        if all_day == 'n':
            self._read('Start Time (HH:MM): ')
            self.write(self._timestr(start_time) + '\n')
            self._read('End time (HH:MM): ')
            self.write(self._timestr(end_time) + '\n')
        new_event = Event(self.global_event_id, event_name, event_desc, start_time, end_time, all_day)
        i = 0
        for event in self.cur_user.events:
            if new_event.start <= event.start:
                break
            i += 1
        self.cur_user.events.insert(i, new_event)
        self._read_event(new_event)
        self.global_event_id += 1

    def remove_event(self):
        if self.mode != 'user':
            self._bad_choice()
            return
        self.write('3\n')
        self._read('Enter eventid: ')
        do_remove = random.randint(1,10) == 1
        if do_remove and len(self.cur_user.events):
            idx = random.randint(1, len(self.cur_user.events)) - 1
            event = self.cur_user.events.pop(idx)
            self.write(event.id + '\n')
            self._read('Successfully removed event\n')
        else:
            self.write('\n')
            self._read('Event not found\n')

    def return_to_user_view(self):
        if self.mode != 'cal':
            self._bad_choice()
            return
        self.mode = 'user'
        self.write('8\n')

    def exit(self):
        if self.mode != 'user':
            self.write('8\n')
            self.mode = 'user'
            self._read_user_menu()
        self.write('7\n')

