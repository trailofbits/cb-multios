#!/usr/bin/env python
#
# Copyright (C) 2014 Dustin Fraze <df@cromulence.co>
#

from generator.actions import Actions
import random

class Contact():
	first = ""

	def genderToStr(self):
		return {"M":"Male","F":"Female","T":"Trans-Gender"}.setdefault(self.gender, "Other")


	def __init__(self, first=None, last=None, phone=None, office=None, gender=None, hacker=None):
		if first != None:
			self.first = first
			self.last = last
			self.phone = phone
			self.office = office
			self.gender = gender
			self.hacker = hacker
			return

		men = 'Tom Chris Charles Bryce Dustin Joe Jim James Steve John Dan Tyler Jordan Jason Mitch Thomas Eric Mitt Jeff Rick Richard Frank Franklin Will William Steven Jeb Bill Charlie Jeffrey Terry Albert Bernard Randall Troy Ricky Eddie Jesus Bradley Kyle Alfred Ralph Douglas Henry Andrew Juan Jack Keith Nicholas Victor Phillip Todd Alan Shawn Sean'.split()
		women = 'Lilly Molly Tegan Deb Alex Samantha Stephanie Aria Ashley Amanda Tara Faye Lina Kathline Kim Jane Suzie Brianne Valerie Cindy Lacey Mary Jill Chelsea Mable Ernestine Muriel Marcella Elena Krystal Angelina Nadine Kari Estelle Dianna Paulette Lora Mona Doreen Rosemarie Angel Desiree Antonia Hope Ginger Janis Betsy Sophia Jessica Shirley Cynthia Angela Melissa Brenda Amy Anna Rebecca Virginia Carolyn Ann Alice Heather Rose Martha'.split()
		last = 'Clinton Bush Obama Smith Johnson Jones Brown Davis Miller Wilson Moore Taylor Anderson Ford McAvoy Gates Jobs Moss Snowden Flores Washington Butler Simmons Foster Gonzales Bryant Alexander Russell Griffen Diaz Hayes Myers Hamilton Perry Cook Peterson Gray Ramirez Price Morris Rogers Reed Morgan Bell Murphy Bailey Rivera Cooper Richardson Cox Howard Ward Torres Peterson Barnett Jennings Miles Lucas Gergory Sutton Castro Obrien Frazier Welch Larson Romero Lynch Dean Gilbert Burke Hanson Day Cowman Medina Fowler Brewer Hoffman Carlson Silva Underwood Phelps Luna Wilkins Roberson Barton Tran Casey Boone Bowers Morton'.split()

		self.gender = random.choice(["M", "F", "T", "?"])
		if self.gender == 'M':
			self.first = random.choice(men)
		elif self.gender == 'F':
			self.first = random.choice(women)
		else:
			self.first = random.choice(random.choice([men, women]))
		self.last = random.choice(last)
		self.phone = "(%0.3d)%0.3d-%0.4d" % (random.randrange(0, 999), random.randrange(0, 999), random.randrange(0, 9999))
		self.office = random.randrange(0,9999)
		self.hacker = random.choice("yn")

class Yolodex(Actions):
	addState = 0

	def genInitialContacts(self):
		self.contacts = []
		self.contacts.append(Contact(first="Robert", last="Morris", phone="(617)253-5982", office=32972, gender='M', hacker='y'))
		self.contacts.append(Contact("Chareth", "Cutestory", "(123)456-7890", 4242, 'M', 'n'))
		self.contacts.append(Contact("Tim", "Berners-Lee", "(638)844-2074", 404, 'M','y'))
		self.contacts.append(Contact("Pwnies", "McPwn", "(222)223-1337", 31337, 'F','y'))
		self.contacts.append(Contact("Jenny", "Fakename", "(555)867-5309", 31337, 'F','n'))


	def start(self):
		self.read(delim='\n', expect='Welcome to the yolodex.')
		self.genInitialContacts()

	def add(self):
		self.write("@\n")

	def addBadHacker(self):
		self.newContact = Contact()
		self.read(delim=": ", expect="First")
		self.write(self.newContact.first + "\n")
		self.read(delim=": ", expect="Last")
		self.write(self.newContact.last + "\n")
		self.read(delim=": ", expect="Phone Number")
		self.write(self.newContact.phone + "\n")
		self.read(delim=": ", expect="Office Number")
		self.write(str(self.newContact.office) + "\n")
		self.read(delim=": ", expect="Gender")
		self.write(self.newContact.gender + "\n")
		self.read(delim=": ", expect="Hacker")
		hacker = random.choice("abcdefghijklmopqrstuvwxz01234567890-!@#$%^&*()")
		self.write(hacker + "\n")
		self.read(delim="\n", expect="Please enter y or n for hacker.")
		self.read(delim=": ", expect="Hacker")
		self.write(self.newContact.hacker + "\n")

	def addBadName(self):
		self.newContact = Contact()
		bad = random.choice(["first", "last"])
		self.read(delim=": ", expect="First: ")
		self.write((self.newContact.first if bad == "last" else self.newContact.first.lower()) + "\n")
		self.read(delim=": ", expect="Last: ")
		self.write((self.newContact.last.lower() if bad == "last" else self.newContact.last) + "\n")
		self.addState = 3
		self.finishAdd()
		self.read(delim="\n", expect="Invalid %s name.  Must begin with a capital letter." % bad)
		self.addState = 1
		self.finishAdd()

	def addBadPhone(self):
		self.newContact = Contact()
		self.read(delim=": ", expect="First")
		self.write(self.newContact.first + "\n")
		self.read(delim=": ", expect="Last")
		self.write(self.newContact.last + "\n")
		self.read(delim=": ", expect="Phone Number")
		self.write(''.join(random.choice('abcdefghiklmnopqrstuvwxyz0123456789-)') for _ in range(12)))
		self.write("\n")
		self.addState = 4
		self.finishAdd()

	def mainmenu(self):
		pass

	def showinvalid(self):
		self.write(random.choice('abcdfghijklmorstuvwxyz0123456789-)') + "\n")
		self.showGoodUser()


	def finishAdd(self):
		if self.addState <= 1:
			self.read(delim=": ", expect="First")
			self.write(self.newContact.first + "\n")
		if self.addState <= 2:
			self.read(delim=": ", expect="Last")
			self.write(self.newContact.last + "\n")
		if self.addState <= 3:
			self.read(delim=": ", expect="Phone Number")
			self.write(self.newContact.phone + "\n")			
		if self.addState <= 4:
			self.read(delim=": ", expect="Office Number")
			self.write(str(self.newContact.office) + "\n")
		if self.addState <= 5:
			self.read(delim=": ", expect="Gender")
			self.write(self.newContact.gender + "\n")
		if self.addState <= 6:
			self.read(delim=": ", expect="Hacker")
			self.write(self.newContact.hacker + "\n")


	def addGood(self):
		self.newContact = Contact()
		self.addState = 1
		self.finishAdd()
		self.contacts.append(self.newContact)

	def userLookup(self, first, last):
		self.read(delim=": ", expect="First")
		self.write(first + "\n")
		self.read(delim=": ", expect="Last")
		self.write(last + "\n")


	def delete(self):
		try:
			picked = random.choice(self.contacts)
		except IndexError:
			return
		self.write("A\n")
		self.userLookup(picked.first, picked.last)
		self.read(delim="\n", expect="Contact removed.")
		self.contacts.remove(picked)

	def edit(self):
		try:
			picked = random.choice(self.contacts)
		except IndexError:
			return
		new = Contact()
		self.write("B\n")
		self.userLookup(picked.first, picked.last)
		self.read(delim="\n", expect="Updating fields.  Send just a newline to keep old data.")
		self.read(delim=": ", expect="New first name")
		self.write(new.first + "\n")
		self.read(delim=": ", expect="New last name")
		self.write(new.last + "\n")
		self.read(delim=": ", expect="New phone number")
		self.write(new.phone + "\n")
		self.read(delim=": ", expect="New office number")
		self.write(str(new.office) + "\n")
		self.read(delim=": ", expect="New gender")
		self.write(new.gender + "\n")
		self.read(delim="? ", expect="Is the user a hacker")
		self.write(new.hacker + "\n")
		self.contacts[self.contacts.index(picked)] = new

	def badcommand(self):
		self.write(random.choice("qwertyuiopasdfghjklzxcvbnm,.[];'/1234567890!#$%^&*()-=_+") + "\n")
		self.read(delim="\n", expect="Unrecognized Command.")

	def showmenu(self):
		try:
			self.picked = random.choice(self.contacts)
		except IndexError:
			self.picked = None
			return
		self.write("C\n")

	def showprev(self):
		if not getattr(self, "picked", None):
			return
		self.write("p\n")
		if self.contacts.index(self.picked) == 0:
			self.read(delim="\n", expect="No previous contact.")
		else:
			self.picked = self.contacts[self.contacts.index(self.picked)-1]
			self.showGoodUser()

	def shownext(self):
		if not getattr(self, "picked", None):
			return
		self.write("n\n")
		if self.contacts.index(self.picked) == len(self.contacts)-1:
			self.read(delim="\n", expect="No next contact.")
		else:
			self.picked = self.contacts[self.contacts.index(self.picked)+1]
			self.showGoodUser()

	def showexit(self):
		if len(self.contacts) == 0:
			return
		self.write("q\n")

	def showBadUser(self):
		baduser = Contact()
		self.userLookup(baduser.first, baduser.last)
		self.read(delim="\n", expect="No such contact.")

	def showGoodUser(self):
		if not getattr(self, "picked", None):
			return
		picked = self.picked
		self.picked = None
		self.userLookup(picked.first, picked.last)
		self.read(delim="\n", expect="*"*40)
		self.read(delim="\t", expect="First name:")
		self.read(delim="\n", expect=picked.first)
		self.read(delim="\t", expect="Last name:")
		self.read(delim="\n", expect=picked.last)
		self.read(delim="\t", expect="Phone num:")
		self.read(delim="\n", expect=picked.phone)
		self.read(delim="\t", expect="Office Number:")
		self.read(delim="\n", expect=str(picked.office))
		self.read(delim="\t\t", expect="Gender:")
		self.read(delim="\n", expect=picked.genderToStr())
		if picked.hacker == 'y':
			self.read(delim="\n", expect="[\x1b[31m!\x1b[0m]This user known to be a hacker[\x1b[31m!\x1b[0m]")
		self.read(delim="\n", expect="*"*40)

	def showdelete(self):
		if not getattr(self, "picked", None):
			return

		index = self.contacts.index(self.picked)

		if index == 0 and len(self.contacts) == 0:
			self.picked = None
			return

		self.write("d\n")

		if index == len(self.contacts)-1:
			self.picked = self.contacts[index-2]
		else:
			self.picked = self.contacts[index]
		self.showGoodUser()


	def showlist(self):
		self.write("D\n")
		for c in self.contacts:
			self.read(delim="\n", expect="="*40)
			self.read(delim="\t", expect="First Name:")
			self.read(delim="\n", expect=c.first)
			self.read(delim="\t", expect="Last Name:")
			self.read(delim="\n", expect=c.last)
			self.read(delim="\t", expect="Phone Number:")
			self.read(delim="\n", expect=c.phone)
		if len(self.contacts) == 0:
			self.read(delim="\n", expect="Empty yolodex.")
		self.read(delim="\n", expect="="*40)

	def sortContacts(self, a, b):
		return cmp(a.last, b.last)

	def sort(self):
		self.contacts = sorted(self.contacts, self.sortContacts)
		self.write("E\n")

	def exit(self):
		self.write("F\n")
		self.read(delim="\n", expect="Thank you for using the yolodex.")
