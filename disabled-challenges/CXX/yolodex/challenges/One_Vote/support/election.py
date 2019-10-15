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
from common import DEBUG, CONFIG
from random import randint, choice
import string


def random_string(length):
    '''
    Length is the length of resultant string including the term char.
    '''
    chars = string.letters
    return ''.join(choice(chars) for _ in range(length))

def random_digits(length, term, is_valid=True):
    '''
    Length is the length of resultant string including the term char.
    Term is the string termination char.
    '''
    chars = string.digits
    s = "{0}{1}".format(''.join(choice(chars) for _ in range(length - 1)), term)
    if is_valid is False:
        s = choice(string.letters) + s[1:]
    return s


def random_name(max_len=CONFIG['NAME_FIELD_SZ']):
    '''
    Return a random string of length between 5 and NAME_FIELD_SZ
    '''
    if 0 >= max_len:
        max_len = 6
    if 5 >= max_len:
        return random_string(max_len)
    else:
        return random_string(randint(5, max_len - 2))

class Election(object):

    def __init__(self):
        self.name = random_name()

        self.candidates = []
        self.voters = []
        self.votes = []

        self.next_candidate_id = CONFIG['FIRST_CANDIDATE_ID']
        self.next_voter_id = CONFIG['FIRST_VOTER_ID']

        self.state = 1
        self.e_mgr = None

        self.num_winners = 0
        self.max_candidates = 0
        self.write_in_ok = 0

        self.authd_user = None

        self.is_configured = False

    def _get_next_candidate_id(self):
        self.next_candidate_id += 1
        return self.next_candidate_id - 1

    def _get_next_voter_id(self):
        self.next_voter_id += 1
        return self.next_voter_id - 1

    def set_state(self, state_str):
        if "INIT" == state_str:
            self.state = 1
        elif "NEW" == state_str:
            self.state = 2
        elif "OPEN" == state_str:
            self.state = 4
        elif "CLOSED" == state_str:
            self.state = 8

    def get_candidate_count(self):
        return len(self.candidates)

    def get_voter_count(self):
        return len(self.voters)

    def get_vote_count(self):
        return len(self.votes)

    def have_authd_user(self):
        return None != self.authd_user

    def have_authd_e_mgr(self):
        return (True == self.have_authd_user()) and (CONFIG['E_MGR_ID'] == self.authd_user.id)

    def have_authd_voter(self):
        return (True == self.have_authd_user()) and (False == self.have_authd_e_mgr())

    def make_random_candidate(self, is_valid = True):
        if True == is_valid:
            return Candidate.make_random_candidate(self._get_next_candidate_id())
        else:
            return Candidate.make_random_candidate(self.next_candidate_id + 10)

    def make_random_voter(self, is_valid = True):
        if True == is_valid:
            return Voter.make_random_voter(self._get_next_voter_id())
        else:
            return Voter.make_random_voter(randint(CONFIG['E_MGR_ID'] + 1, CONFIG['FIRST_VOTER_ID'] - 1))

    def make_random_e_mgr(self):
        self.e_mgr = ElectionManager.make_random_e_mgr()
        return self.e_mgr

    def set_e_mgr_auth_key(self, auth_key):
        self.e_mgr.auth_key = auth_key

    def add_candidate(self, candidate):
        self.candidates.append(candidate)

    def add_voter(self, voter):
        self.voters.append(voter)

    def add_vote(self, vote):
        for v in self.votes:
            if vote.voter.id is v.voter.id:
                self.votes.remove(v)
                break
        self.votes.append(vote)

    def get_random_candidate(self):
        c = None
        if 0 < len(self.candidates):
            c = choice(self.candidates)
        return c

    def get_random_voter(self):
        v = None
        if 0 < len(self.voters):
            v = choice(self.voters)
        return v

    def get_vote_by_voter_id(self, voter_id):
        for v in self.votes:
            if v.has_voter_id(voter_id):
                return v
        return None

    def get_voting_results(self):
        res = []
        count = 0
        for c in self.candidates:
            for v in self.votes:
                if c.id is v.candidate.id:
                    count += 1
            res.append( (count, c) )
            count = 0

        res.sort(reverse=True)
        return res

class ElectionManager(object):

    def __init__(self, f_name, l_name, auth_key = 0):
        self.id = CONFIG['E_MGR_ID']
        self.f_name = f_name
        self.l_name = l_name
        self.auth_key = auth_key

    def __str__(self):
        return "e_mgr: id: {0}, name: {1} {2}, auth_key: {3}\n".format(self.id,
                                                                        self.f_name,
                                                                        self.l_name,
                                                                        self.auth_key)

    def __repr__(self):
        return self.__str__()

    @staticmethod
    def make_random_e_mgr():
        return ElectionManager(random_name(), random_name())

class Voter(object):

    def __init__(self, v_id, f_name, l_name, vote_id = 0):
        self.id = v_id
        self.f_name = f_name
        self.l_name = l_name
        self.vote_id = vote_id

    def __str__(self):
        return "voter: id: {0}, name: {1} {2}, vote_id: {3}\n".format(self.id,
                                                                        self.f_name,
                                                                        self.l_name,
                                                                        self.vote_id)

    def __repr__(self):
        return self.__str__()

    @staticmethod
    def make_random_voter(v_id):
        return Voter(v_id, random_name(), random_name())

class Candidate(object):

    def __init__(self, c_id, f_name, l_name):
        self.id = c_id
        self.f_name = f_name
        self.l_name = l_name
        self.votes = 0

    def __str__(self):
        return "candidate: id: {0}, name: {1} {2}\n".format(self.id,
                                                            self.f_name,
                                                            self.l_name)
    def __repr__(self):
        return self.__str__()

    @staticmethod
    def make_random_candidate(c_id):
        return Candidate(c_id, random_name(), random_name())

class Vote(object):

    def __init__(self, v_id, voter, candidate):
        self.id = v_id
        self.voter = voter
        self.candidate = candidate

    def __str__(self):
        return "vote: id: {0}\n\t{1}\n\t{2}\n".format(self.id,
                                                    self.voter,
                                                    self.candidate)

    def __repr__(self):
        return self.__str__()

    def has_voter_id(self, voter_id):
        return voter_id == self.voter.id

