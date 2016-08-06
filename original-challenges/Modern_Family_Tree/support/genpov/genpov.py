#!/usr/bin/env python
#
# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

from generator.actions import Actions, Variable
from random import choice, randint
from os.path import dirname, abspath, join
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
import support as sp
from common import DEBUG, CONFIG
from template import FamilyTree, Person

class TemplatePoller(Actions):


    ADD_PERSON            =   '\xa0\xa1\xa2\xa3'
    SET_BIOLOGICAL_CHILD  =   '\xbc\xbc\xbc\xbc'
    SET_ADOPTED_CHILD     =   '\xac\xac\xac\xac'
    SET_UNION             =   '\xf0\xf1\xf2\xf3'
    SET_DECEASED          =   '\xde\xce\xde\xce'
    SET_SEPARATED         =   '\x50\x11\x50\x11'

    OK      = ''
    ERR     = ''


    def _gen_status_msgs(self):
        ok = [0,0,0,0]
        err = [0,0,0,0]
        for idx in [c for c in range(len(self.magic_page)) if c % 2 == 0]:
            ok[idx % 4] ^= ord(self.magic_page[idx])
            err[(idx+1) % 4] ^= ord(self.magic_page[idx+1])
        self.OK  = ''.join([chr(c) for c in ok])
        self.ERR = ''.join([chr(c) for c in err])

    def _gen_random_person(self):
        p_id = randint(1, 100000)
        while p_id in self.state['pids']:
            p_id = randint(1, 100000)
        self.state['pids'].add(p_id)
        p = Person(p_id, self.state['s'].p_unk)
        p.gen_random_details()
        return p

    def start(self):
        if DEBUG:
            print "------- start -----------"
        self._gen_status_msgs()
        self.state['s'] = FamilyTree(flag_page=self.magic_page)
        self.state['pids'] = set()

        # for _ in range(randint(5,20)):
        #     self.add_person()

    def add_person(self, person=None):
        '''
        Add a new person
        '''
        if DEBUG:
            print "cmd: add person -----------"

        if person != None:
            p = person
        else:
            p = self._gen_random_person()

        buf = self.ADD_PERSON + p.gen_new_person_bytes()
        self.write(buf)

        self.state['s'].people.append(p)
        self.read(length=len(self.OK))

        return 0

    def set_bio_child(self):
        '''
        Set biological child relationship between child and parents
        '''
        if DEBUG:
            print "cmd: set biological child -----------"

        [child, mother, father] = self.state['s'].get_random_people(3)
        if self.state['s'].p_unk == child or mother == father:
            return -1

        buf = child.get_id_bytes()
        buf += mother.get_id_bytes()
        buf += father.get_id_bytes()

        buf = self.SET_BIOLOGICAL_CHILD + sp.pack_single_uint32(len(buf)) + buf
        self.write(buf)

        ret = self.state['s'].set_bio_child(child, mother, father)
        if 0 != ret:
            self.read(length=len(self.ERR))
            return -1

        self.read(length=len(self.OK))
        return 0

    def set_adopted_child(self, people=[]):
        '''
        Set adopted child relationship between child and 1 or 2 parents

        people => [child, parent1, parent2] (one of parent1 or parent2 can be p_unk)
        '''
        if DEBUG:
            print "cmd: set adopted child -----------"

        if people != []:
            [child, parent1, parent2] = people
        else:
            [child, parent1, parent2] = self.state['s'].get_random_people(3)

        if self.state['s'].p_unk == child or parent1 == parent2:
            return -1

        buf = child.get_id_bytes()
        buf += parent1.get_id_bytes()
        buf += parent2.get_id_bytes()

        buf = self.SET_ADOPTED_CHILD + sp.pack_single_uint32(len(buf)) + buf
        self.write(buf)

        ret = self.state['s'].set_adopted_child(child, parent1, parent2)
        if 0 != ret:
            self.read(length=len(self.ERR))
            return -1

        self.read(length=len(self.OK))
        return 0

    def set_union(self, people=[]):
        '''
        Set a union relationship between 2 people

        people => [parent1, parent2]
        '''
        if DEBUG:
            print "cmd: set union -----------"

        if people != []:
            [parent1, parent2] = people
        else:
            [parent1, parent2] = self.state['s'].get_random_people(2)
  
        if parent1 == parent2 or self.state['s'].p_unk == parent1 or \
            self.state['s'].p_unk == parent2:
            return -1

        buf = parent1.get_id_bytes()
        buf += parent2.get_id_bytes()
        buf = self.SET_UNION + sp.pack_single_uint32(len(buf)) + buf
        self.write(buf)

        ret = self.state['s'].set_union(parent1, parent2)
        if 0 != ret:
            self.read(length=len(self.ERR))
            return -1

        self.read(length=len(self.OK))
        return 0

    def set_separated(self, people=[]):
        '''
        Unset a union relationship between 2 people

        people => [parent1, parent2]
        '''
        if DEBUG:
            print "cmd: set separated -----------"

        if people != []:
            [parent1, parent2] = people
        else:
            [parent1, parent2] = self.state['s'].get_random_union()

        if parent1 == parent2 or self.state['s'].p_unk == parent1 or \
            self.state['s'].p_unk == parent2:
            # no union
            return -1

        buf = parent1.get_id_bytes()
        buf += parent2.get_id_bytes()
        buf = self.SET_SEPARATED + sp.pack_single_uint32(len(buf)) + buf
        self.write(buf)

        ret = self.state['s'].separate_two_people(parent1, parent2)
        if 0 != ret:
            self.read(length=len(self.ERR))
            return -1

        self.read(length=len(self.OK))
        return 0

    def set_deceased(self):
        '''
        Set a person as deceased
        '''
        if DEBUG:
            print "cmd: set deceased -----------"

        [parent1] = self.state['s'].get_random_people(1)
        if self.state['s'].p_unk == parent1:
            # no people
            return -1

        buf = parent1.get_id_bytes()
        buf += parent1.get_death_date_bytes()
        buf = self.SET_DECEASED + sp.pack_single_uint32(len(buf)) + buf
        self.write(buf)

        ret = self.state['s'].set_deceased(parent1)
        if 0 != ret:
            self.read(length=len(self.ERR))
            return -1

        self.read(length=len(self.OK))
        return 0


    def full_set(self):

        for _ in range(randint(5,20)):
            self.add_person()

        if 0 != self.set_bio_child():
            return -1

        if 0 != self.set_adopted_child():
            return -1

        if 0 != self.set_union():
            return -1

        if 0 != self.set_separated():
            return -1

        if 0 != self.set_deceased():
            return -1

        return 0

    def pov1(self):

        for _ in range(randint(10,20)):
            self.add_person()

        child = self.state['s'].people[0]
        parent1 = self.state['s'].people[2]
        parent2 = self.state['s'].people[5]
        parent3 = self.state['s'].people[8]

        self.set_union([parent1, parent2])
        self.set_adopted_child([child, parent1, parent2])
        self.set_separated([parent1, parent2])


        self.set_union([parent1, parent3])
        # write p3 onto p1's shift pointer
        self.set_separated([parent1, parent3])
        # trigger call to p1's shift pointer
        self.set_adopted_child([child, parent1, self.state['s'].p_unk])

        return 0

    def pov2(self):

        for _ in range(randint(10,20)):
            self.add_person()

        child = self.state['s'].people[0]
        parent1 = self.state['s'].people[2]
        parent2 = self.state['s'].people[5]
        parent3 = self.state['s'].people[8]

        self.set_union([parent1, parent2])
        self.set_adopted_child([child, parent1, parent2])
        self.set_separated([parent1, parent2])


        self.set_union([parent2, parent3])
        # write p3 onto p2's shift pointer
        self.set_separated([parent2, parent3])
        # trigger call to p2's shift pointer
        self.set_adopted_child([child, self.state['s'].p_unk, parent2])

        return 0

    def quit(self):
        '''
        Quit cleanly
        '''
        if DEBUG:
            print "cmd: quit -----------"

        return -1

    def broker(self):
        '''
        Branching node for all nodes
        '''
        return 0
