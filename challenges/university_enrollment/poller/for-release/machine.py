from generator.actions import Actions
import random
import string
import struct
import StringIO
import os
import csv

MAX_COURSES = 7
MAX_CREDITS = 17

st = lambda x: SimpleTime(*([int(y) for y in x.split(":")]))
cid = lambda x, y: '{0} {1}'.format(x, y)
d = lambda x: ''.join([s + '|' for s in x])[:-1]

profs = []
depts = []
courses = []


def days_intersect(d1, d2):
    if d1 == 'H' and d2 == 'H':
        return False

    for d in d1:
        if d in d2:
            return True

    return False

def timecmp(t1, t2):
    if (t1.hour < t2.hour):
        return -1
    if (t1.hour > t2.hour):
        return 1
    if (t1.minute < t2.minute):
        return -1
    if (t1.minute > t2.minute):
        return 1
    return 0


def check_time_conflict(course1, course2):
    if not days_intersect(course1.days, course2.days):
        return False;

    if (timecmp(course1.start, course2.start) >= 0 and timecmp(course1.end, course2.end) <= 0):
        return True
    if (timecmp(course2.start, course1.start) >= 0 and timecmp(course2.end, course1.end) <= 0):
        return True

    return False


def find_dept(dept_name, course):
    for dept in depts:
        if dept.name == dept_name:
            dept.courses.append(course)
            return dept


def find_prof(prof_name, course):
    for prof in profs:
        if prof.name == prof_name:
            prof.courses.append(course)
            return prof


def gen_depts():
    if depts:
        return depts
    with open('./poller/for-release/cgc_dept.txt') as f:
        lines = f.read()
    for line in lines.splitlines():
        depts.append(Department(line))
    return depts


def gen_profs():
    if profs:
        return profs
    with open('./poller/for-release/cgc_prof.txt') as f:
        lines = f.read()
    for line in lines.splitlines():
        profs.append(Professor(line))
    return profs


def gen_courses():
    gen_depts()
    gen_profs()
    if courses:
        return courses
    with open('./poller/for-release/cgc_data.csv', 'rU') as csvfile:
        cgcreader = csv.reader(csvfile)
        for row in cgcreader:
            courses.append(Course(row[0], row[3], row[1], row[2], row[4], row[5], row[6], row[7],
                                    row[8], row[9], row[10]))
    return courses


class SimpleTime():
    def __init__(self, hour, minute):
        self.hour = hour
        self.minute = minute


class Department():
    def __init__(self, name):
        self.name = name
        self.courses = []


class Professor():
    def __init__(self, name):
        self.name = name
        self.courses = []

class Student():
    def __init__(self, name):
        self.name = name
        self.courses = []
        self.major = ""

    def set_major(self, dept):
        if dept:
            self.major = dept

    def add_course(self, course):
        if course.cur_enroll >= course.max_enroll:
            return False
        if self.total_credits() + course.credits > MAX_CREDITS:
            return False
        for c in self.courses:
            if (check_time_conflict(c, course) or c == course):
                return False
            if (c.course_id == course.course_id):
                return False
        if self.major.name != course.dept.name and course.credits < 3:
            return False
        self.courses.append(course)
        return True

    def total_credits(self):
        if self.courses:
            return reduce(lambda x,y: x+y, [c.credits for c in self.courses])
        else:
            return 0

    def num_major_courses(self):
        if self.courses:
            return reduce(lambda x,y: x+y, [1 if c.dept == self.dept else 0 for c in self.courses])
        else:
            return 0

    def num_courses(self):
        return len(self.courses)


class Course():
    def __init__(self, course_id, prof, dept, course_num, credits, cur_enroll, max_enroll,
                 days, start, end, title):
        self.course_id = int(course_id)
        self.prof = find_prof(prof, self)
        self.dept = find_dept(dept, self)
        self.course_num = int(course_num)
        self.credits = int(credits)
        self.cur_enroll = int(cur_enroll)
        self.max_enroll = int(max_enroll)
        self.days = days
        self.start = st(start)
        self.end = st(end)
        self.title = title
        self.class_id = '%s %d' % (self.dept.name, self.course_num)

    def course_str(self):
        return ("%d|%s|%s|CR:%d|CE:%d|MC:%d|%s|%02d:%02d|%02d:%02d|%s" %
            (self.course_id, self.class_id, self.prof.name, self.credits,
            self.cur_enroll, self.max_enroll, self.days, self.start.hour,
            self.start.minute, self.end.hour, self.end.minute, self.title))


def random_name(max_size=8, min_size=3):
    characters = string.letters
    max_size = max_size if max_size >= min_size else min_size
    max_size = random.randint(min_size, max_size)
    fname = "".join(random.choice(characters) for c in range(max_size))
    lname = "".join(random.choice(characters) for c in range(max_size))
    fname = fname[0].upper() + fname[1:]
    lname = lname[0].upper() + lname[1:]
    return ''.join(fname) + ' ' + ''.join(lname)


class ClassSchedule(Actions):
    courses = gen_courses()
    profs = gen_profs()
    depts = gen_depts()

    def _read(self, string):
        self.read(length=len(string), expect=string)

    def _read_courses(self, courses):
        self._read("IDX|CID|Course|Professor|Credits|Enrolled|Max|Days|Start|End|Title\n")
        for i, course in enumerate(courses):
            self._read("#%d|%s\n" % (i+1, course.course_str()))

    def start(self):
        self._read("University Course Scheduler\n\n")
        self._read("Enter name: ")
        self.student = Student(random_name())
        self.write(self.student.name + '\n')
        self._read("Select a major\n")
        self._read("List Departments?\n")
        self._read("1 - Yes\n")
        self._read("2 - No\n")
        self._read("Choice: ")
        self.write("2\n")
        self.student.set_major(self.depts[random.randint(0, len(self.depts) - 1)])
        self._read("Enter your Major's Department Name: ")
        self.write(self.student.major.name + '\n')
        self._read("Congratulations. You're read to start adding classes\n")
        self.state['skip_write'] = False
        self.state['must_return_to_menu'] = False

    def main_menu(self):
        self._read("Main Menu\n")
        self._read("1 - Search Classes\n")
        self._read("2 - Add Class\n")
        self._read("3 - Remove Class\n")
        self._read("4 - Print Schedule\n")
        self._read("5 - Exit\n")
        self._read("Choice: ")

    def return_to_main_menu(self):
        if self.state['must_return_to_menu']:
            self.state['must_return_to_menu'] = False

        self.write('0\n')
        self._read("Returning to main menu\n")
        self.state['skip_write'] = False

    def search_classes(self):
        if not self.state['skip_write']:
            self.write('1\n')
        self._read("Class Search\n")
        self._read("0 - Go Back\n")
        self._read("1 - Search by Professor Name (ex: Gerardo Chacon)\n")
        self._read("2 - Search by Department Name (ex: MAT)\n")
        self._read("3 - Search by Class ID (ex: MAT 150)\n")
        self._read("4 - Search by Course ID (ex: 2600)\n")
        self._read("Choice: ")

    def sc_by_prof(self):
        self.write('1\n')
        self._read("List Professors?\n")
        self._read("1 - Yes\n")
        self._read("2 - No\n")
        self._read("Choice: ")
        self.write("2\n")
        self._read("Enter professor's full name: ")
        prof = self.profs[random.randint(0, len(self.profs) - 1)]
        self.write(prof.name + '\n')
        self._read("--%s's Classes--\n" % (prof.name))
        self._read_courses(prof.courses)
        self.state['skip_write'] = True

    def sc_by_dept(self):
        self.write('2\n')
        self._read("List Departments?\n")
        self._read("1 - Yes\n")
        self._read("2 - No\n")
        self._read("Choice: ")
        self.write("2\n")
        self._read("Enter Department name: ")
        dept = self.depts[random.randint(0, len(self.depts) - 1)]
        self.write(dept.name + '\n')
        self._read("--Department Availability--\n")
        self._read_courses(dept.courses)
        self.state['skip_write'] = True

    def sc_by_class_id(self):
        self.write('3\n')
        self._read("Enter Class ID: ")
        course = self.courses[random.randint(0, len(self.courses) - 1)]
        self.write(course.class_id + '\n')
        courses = [c for c in self.courses if c.class_id == course.class_id]
        self._read_courses(courses)
        self.state['skip_write'] = True

    def sc_by_course_id(self):
        self.write('4\n')
        self._read("Enter Course ID: ")
        course = self.courses[random.randint(0, len(self.courses) - 1)]
        self.write(str(course.course_id) + '\n')
        courses = [c for c in self.courses if c.course_id == course.course_id]
        self._read_courses(courses)
        self.state['skip_write'] = True

    def add_class(self):
        if self.state['must_return_to_menu']:
            return

        if not self.state['skip_write']:
            self.write('2\n')
        self._read("Add Class to Schedule\n")
        self._read("0 - Go Back\n")
        self._read("1 - Add by Class Num (ex: MAT 150)\n")
        self._read("2 - Add by Course ID (ex: 2600)\n")
        self._read("Choice: ")

        if self.student.num_courses() >= MAX_COURSES:
            self.state['must_return_to_menu'] = True

    def ac_by_class_id(self):
        if self.state['must_return_to_menu']:
            return

        self.write('1\n')
        self._read("Enter Class ID: ")
        course = self.courses[random.randint(0, len(self.courses) - 1)]
        self.write(course.class_id + '\n')
        courses = [c for c in self.courses if c.class_id == course.class_id]
        self._read("0 - Go Back\n")
        self._read_courses(courses)
        self._read("Choice: ")
        choice = random.randint(0, len(courses))
        self.write('%d\n' % (choice))
        if choice != 0:
            course = courses[choice - 1]
            if self.student.add_course(course):
                self._read("Successfully added course!\n")
            else:
                self._read("Could not add course.\n")
        self.state['skip_write'] = True

    def ac_by_course_id(self):
        if self.state['must_return_to_menu']:
            return

        self.write('2\n')
        self._read("Enter Course ID: ")
        course = self.courses[random.randint(0, len(self.courses) - 1)]
        self.write(str(course.course_id) + '\n')
        courses = [c for c in self.courses if c.course_id == course.course_id]
        self._read("0 - Go Back\n")
        self._read_courses(courses)
        self._read("Choice: ")
        choice = random.randint(0, len(courses))
        self.write('%d\n' % (choice))
        if choice != 0:
            course = courses[choice - 1]
            if self.student.add_course(course):
                self._read("Successfully added course!\n")
            else:
                self._read("Could not add course.\n")
        self.state['skip_write'] = True

    def remove_class(self):
        self.write('3\n')
        self._read("Remove Class from Schedule\n")
        self._read("0 - Go Back\n")
        self._read_courses(self.student.courses)
        self._read("Choice: ")
        choice = random.randint(0, len(self.student.courses))
        self.write('%d\n' % (choice))
        if choice != 0:
            del self.student.courses[choice - 1]
            self._read("Successfully removed course!\n")
        self._read('Returning to main menu\n')

    def view_schedule(self):
        self.write('4\n')
        self._read_courses(self.student.courses)

    def quit(self):
        self.write('5\n')
        self._read("Exiting.\n")

