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
from random import choice, randint

import support as sp
from common import DEBUG, CONFIG

class FamilyTree(object):
    def __init__(self, flag_page=''):
        self.people = []
        self.p_unk = Person(0, None)
        self.search_map = {}

    def new_search_map(self):
        if {} != self.search_map:
            self.search_map = {}

        for p in self.people:
            self.search_map[p.id] = 0

    def is_search_locked(self, p_id, lock_type):
        ''' get the status of the lock for this lock type TRUE (>0) or FALSE (==0) '''
        return self.search_map[p_id] & lock_type

    def set_search_lock(self, p_id, lock_type):
        ''' set the status of the lock for this lock type'''
        self.search_map[p_id] = self.search_map[p_id] | lock_type

    def degrees_of_separation(self, p1, p2):
        ''' 
            Determine the number of degrees of separation between p1 and p2.

            @return 0 if self, number of degrees (>0) if related, -1 if not related
        '''
        ret = 0;

        if p1 == self.p_unk or p2 == self.p_unk:
            return -1

        ## check self
        if p1 == p2:
            return 0;

        ## check relations

        # search p1.adopted
        if 0 == self.is_search_locked(p1.id, CONFIG['RT_ADOPTED_CHILD']):
            self.set_search_lock(p1.id, CONFIG['RT_ADOPTED_CHILD'])
            for i in range(len(p1.adopted_children)):
                ret = self.degrees_of_separation(p1.adopted_children[i], p2)
                if 0 <= ret:
                    if DEBUG:
                        print "{0} degrees between {1}.a_c[{2}]={3} and p2={4}".format(ret, p1.id, i, p1.adopted_children[i].id, p2.id)
                    return 1 + ret

        # search p1.biological
        if 0 == self.is_search_locked(p1.id, CONFIG['RT_BIO_CHILD']):
            self.set_search_lock(p1.id, CONFIG['RT_BIO_CHILD'])
            for i in range(len(p1.biological_children)):
                ret = self.degrees_of_separation(p1.biological_children[i], p2)
                if 0 <= ret:
                    if DEBUG:
                        print "{0} degrees between {1}.b_c[{2}]={3} and p2={4}".format(ret, p1.id, i, p1.biological_children[i].id, p2.id)
                    return 1 + ret

        # search p1.biological_mother
        if 0 == self.is_search_locked(p1.id, CONFIG['RT_MOTHER']):
            self.set_search_lock(p1.id, CONFIG['RT_MOTHER'])
            ret = self.degrees_of_separation(p1.biological_mother, p2)
            if 0 <= ret:
                if DEBUG:
                    print "{0} degrees between {1}.b_m={2} and p2={3}".format(ret, p1.id, p1.biological_mother.id, p2.id)
                return 1 + ret

        # search p1.biological_father
        if 0 == self.is_search_locked(p1.id, CONFIG['RT_FATHER']):
            self.set_search_lock(p1.id, CONFIG['RT_FATHER'])
            ret = self.degrees_of_separation(p1.biological_father, p2)
            if 0 <= ret:
                if DEBUG:
                    print "{0} degrees between {1}.b_f={2} and p2={3}".format(ret, p1.id, p1.biological_father.id, p2.id)
                return 1 + ret

        # search p1.adopting
        if 0 == self.is_search_locked(p1.id, CONFIG['RT_ADOPTING_PARENT']):
            self.set_search_lock(p1.id, CONFIG['RT_ADOPTING_PARENT'])
            ret = self.degrees_of_separation(p1.adopting_parents[0], p2)
            if 0 <= ret:
                if DEBUG:
                    print "{0} degrees between {1}.a_p[0]={2} and p2={3}".format(ret, p1.id, p1.adopting_parents[0].id, p2.id)
                return 1 + ret

            ret = self.degrees_of_separation(p1.adopting_parents[1], p2)
            if 0 <= ret:
                if DEBUG:
                    print "{0} degrees between {1}.a_p[1]={2} and p2={3}".format(ret, p1.id, p1.adopting_parents[1].id, p2.id)
                return 1 + ret;

        # search p1.current
        if 0 == self.is_search_locked(p1.id, CONFIG['RT_PARTNER']):
            self.set_search_lock(p1.id, CONFIG['RT_PARTNER'])
            ret = self.degrees_of_separation(p1.current_partner, p2)
            if 0 <= ret:
                if DEBUG:
                    print "{0} degrees between {1}.c_p={2} and p2={3}".format(ret, p1.id, p1.current_partner.id, p2.id)
                return 1 + ret

        # search p1.former
        if 0 ==self.is_search_locked(p1.id, CONFIG['RT_FORMER']):
            self.set_search_lock(p1.id, CONFIG['RT_FORMER'])
            ret = self.degrees_of_separation(p1.former_partners[0], p2)
            if 0 <= ret:
                return 1 + ret

            ret = self.degrees_of_separation(p1.former_partners[1], p2)
            if 0 <= ret:
                return 1 + ret;

        return -1

    def find_are_related(self, p1, p2):
        ''' determine if p1 and p2 are related '''
        self.new_search_map()
        res = self.degrees_of_separation(p1, p2)
        if DEBUG:
            print " {0} degrees of separation for relation check on {1} and {2}".format(res, p1.id, p2.id)

        if 0 <= res:
            return CONFIG['RELATED']
        else:
            return CONFIG['NOT_RELATED']

    def get_random_people(self, count):
        ''' return count random people in a list '''
        l = []
        if [] == self.people:
            return count * [self.p_unk]

        s_idx = randint(0, len(self.people)-1)
        for x in range(count):
            l.append(self.people[s_idx])
            s_idx = (s_idx + 1) % len(self.people)

        return l

    def get_random_union(self):
        ''' return list of 2 people that are in union together '''
        l = [self.p_unk, self.p_unk]
        for p in self.people:
            if self.p_unk != p.current_partner:
                l = [p, p.current_partner]
                break

        return l

    def set_bio_child(self, child, mother, father):
        ''' Set the biological child relationship between child and 2 parents 

        A parent can have up to 10 biological children. After that this should return -1
        '''
        if 10 <= len(mother.biological_children) or 10 <= len(father.biological_children):
            return -1

        child.biological_mother = mother
        child.biological_father = father
        mother.biological_children.append(child)
        father.biological_children.append(child)
        return 0

    def unset_adopted_child(self, child, parent):
        ''' Unset the adopted child relationship between parent and a child.'''
        parent.adopted_children.remove(child)

    def set_adopted_child(self, child, parent1, parent2):
        ''' Set the adopted child relationship between child and 1 or 2 parents

        A parent can have up to 10 adopted children. After that this should return -1
        '''
        if 10 <= len(parent1.adopted_children) or 10 <= len(parent2.adopted_children):
            return -1

        for idx, p in enumerate([parent1, parent2]):
            if p == self.p_unk:
                continue

            if self.p_unk != child.adopting_parents[idx]:
                self.unset_adopted_child(child, child.adopting_parents[idx])

            child.adopting_parents[idx] = p
            p.adopted_children.append(child)

        return 0

    def separate_two_people(self, p1, p2):
        ''' Unset the union relationship between 2 people'''

        if self.p_unk == p2:
            return -1

        if self.p_unk == p1.former_partners[0]:
            p1.former_partners[0] = p2
        else:
            p1.former_partners[1] = p2

        if self.p_unk == p2.former_partners[0]:
            p2.former_partners[0] = p1
        else:
            p2.former_partners[1] = p1

        p1.current_partner = self.p_unk
        p2.current_partner = self.p_unk

        return 0

    def set_union(self, p1, p2):
        ''' Set a union relationship between 2 people'''

        for p in [p1, p2]:
            if self.p_unk != p.current_partner:
                self.separate_two_people(p, p.current_partner)

        p1.current_partner = p2
        p2.current_partner = p1

        return 0

    def set_deceased(self, p):
        ''' Set person as deceased'''
        p.death_year = randint(1, 65000)
        # if self.p_unk != p.current_partner:
        #     self.separate_two_people(p, p.current_partner)

        return 0


class Person(object):
    def __init__(self, p_id, p_unk):
        self.id = p_id
        self.birth_year = 0
        self.death_year = 0
        self.fname = ''
        self.mname = ''
        self.lname = ''
        self.adopted_children = []
        self.biological_children = []
        self.biological_mother = p_unk
        self.biological_father = p_unk
        self.adopting_parents = [p_unk, p_unk]
        self.current_partner = p_unk
        self.former_partners = [p_unk, p_unk]

    def gen_random_details(self):
        self.birth_year = randint(1, 65000)
        self.fname = sp.random_string(10)
        self.mname = sp.random_string(10)
        self.lname = sp.random_string(10)

    def gen_new_person_bytes(self):
        '''
        Generate byte string sent to create a new person.
        '''
        byte_str = ''
        byte_str += self.get_id_bytes()
        byte_str += sp.pack_single_uint16(self.birth_year)
        byte_str += sp.pack_single_string(self.fname)
        byte_str += sp.pack_single_string(self.mname)
        byte_str += sp.pack_single_string(self.lname)
        return sp.pack_single_uint32(len(byte_str)) + byte_str

    def get_id_bytes(self):
        return sp.pack_single_uint32(self.id)

    def get_death_date_bytes(self):
        return sp.pack_single_uint16(self.death_year)

    def __eq__(self, other):
        return self.id == other.id

    def __str__(self):
        return "Person(id={0},birthyr={1},deathyr={2},fname={3},mname={4},lname={5})".format(self.id, self.birth_year, self.death_year, self.fname, self.mname, self.lname)

    def __repr__(self):
        return self.__str__()


if __name__ == '__main__':

    ft = FamilyTree('')

    for i in range(10,20):
        p = Person(i, ft.p_unk)
        p.gen_random_details()
        ft.people.append(p)
        # print p.gen_new_person_bytes()

    ft.set_union(ft.people[2], ft.people[4])
    ft.set_adopted_child(ft.people[8], ft.people[2], ft.people[4])
    ft.set_union(ft.people[8], ft.people[9])
    print "Are p[1] and p[2] related? {0}".format(ft.find_are_related(ft.people[1], ft.people[2]))
    print "Are p[2] and p[4] related? {0}".format(ft.find_are_related(ft.people[2], ft.people[4]))
    print "Are p[2] and p[8] related? {0}".format(ft.find_are_related(ft.people[2], ft.people[8]))
    print "Are p[1] and p[9] related? {0}".format(ft.find_are_related(ft.people[1], ft.people[9]))
    print "Are p[2] and p[9] related? {0}".format(ft.find_are_related(ft.people[2], ft.people[9]))
    print "Are p[2] and p[2] related? {0}".format(ft.find_are_related(ft.people[2], ft.people[2]))
    print "Are p[2] and p_unk related? {0}".format(ft.find_are_related(ft.people[2], ft.p_unk))
