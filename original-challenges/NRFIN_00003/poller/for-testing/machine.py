#!/usr/bin/env python
#
# Copyright (C) 2014 
#   Brian Caswell <bmc@lungetech.com>
#   Narf Industries <info@narfindustries.com>
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
import imp
import os
import random
import string


def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))


def random_hex(a, b):
    return ''.join(choice(string.hexdigits) for _ in range(randint(a, b))) 


class Fastlane(Actions):
    RECV_BUF_LEN = 1024

    conf = imp.load_source(
        'conf', 
        os.path.join(
            os.path.dirname(os.path.realpath(__file__)), 
            '..',
            '..',
            'support',
            'config.py'))

    FIXUP_CYCLIC_GROUP_KEY = conf.conf['FIXUP_CYCLIC_GROUP_KEY']


    #### HELPER FUNCTIONS ####

    def start(self):
        """
        Intialize state.
        """
        self.state['credits'] = 0

        # get a legal filename (for use in other functions)
        self.write("SUP\n")
        self.read(
            delim='\n',
            expect="here're your files, plebian:")
        self.read(
            delim='\n',
            expect="----------------------------")

        token = Variable('legalfilename')
        token.set_re(r'([a-z]{16})')
        self.read(delim='\r', assign=token)
        self.state['filename'] = token

    def auth(self):
        """
        The main loop, in a sense.
        All other nodes edge to here and this node edges to all other nodes.

        (Possibly) adds credits.
        """
        # we don't have credits...
        # with some likelihood, we attempt to add credits
        if 0 == self.state['credits'] and self.chance(0.01):
            req = "AUTH "

            # with some likelihood, we send a bogus value
            if self.chance(0.5):
                self.write("AUTH BOGUS" + random_alpha(1, self.RECV_BUF_LEN-100) + "\n")
                self.read(
                    delim='\r',
                    expect="Adding FASTLANE credits...\n"
                           "--------------------------\n"
                           "invalid hex\n"
                           "Sorry, failed to add credits.\n")

            # with some likelihood, we send the right answer
            elif self.chance(0.5):
                req += self.FIXUP_CYCLIC_GROUP_KEY
                self.write(req + "\n")
                self.read(
                    delim='\r',
                    expect="Adding FASTLANE credits...\n"
                           "--------------------------\n"
                           "Authentication successful!\n")
                self.state['credits'] += 3  

            # and with some likelihood, we send the wrong answer
            else:
                # assumes key does not start with "42"
                req += "42"
                req += random_hex(0, 4)
                self.write(req + "\n")
                self.read(
                    delim='\r',
                    expect="Adding FASTLANE credits...\n"
                           "--------------------------\n"
                           "Sorry, failed to add credits.\n")

    def quit(self):
        """
        Quit the session / instance.

        Return -1 to indicate the session is dead.
        """
        self.write("QUIT\n")
        return -1


    #### ERROR STATES ####

    def invalid_verb(self):
        """
        Invalid verb specified.
        """
        self.write("BOGUS" + random_alpha(1, self.RECV_BUF_LEN-100) + "\n")
        self.read(delim='\r', expect="invalid verb\n")

    def invalid_request(self):
        """
        Legal verb specified, URI parameter absent.
        """
        self.write("SMORE\n")
        self.read(delim='\r', expect="invalid request\n")

    def file_not_found(self):
        """
        Request a file that doesn't exist.
        """
        self.write("MOOCH BOGUS" + random_alpha(1, self.RECV_BUF_LEN-100) + "\n")
        self.read(delim='\r', expect="the tubes are \"clogged\" right now...\n"
                                     "------------------------------------\n"
                                     "requested file not found\n")


    #### SLOWLANE VERBS ####
    
    def smore(self):
        """
        <write>
            <data>SMORE </data>
            <var>last_filename</var>
            <data>\n</data>
        </write>
        <read>
            <delim>\r</delim>
            <match>
                <data format="asciic">here's a lil' bit\n</data>
                <data format="asciic">-----------------\n</data>
                <pcre>^[0-9]{4}\r$</pcre>
            </match>
        </read>
        """
        # We overflow into the credits with the same number of credits.
        # This way patched and unpatched works the same.
        # This won't be in the for-release branch because in a sense, this 
        # leaks the vulnerability.
        import struct
        self.write('SMORE ', self.state['filename'], struct.pack("B", self.state['credits'] % 256), '\n')
        self.read(
            delim='\n',
            expect="here's a lil' bit")
        self.read(
            delim='\n',
            expect="-----------------")
        self.read(
            delim='\r',
            expect=r'^[0-9]{4}\r$',
            expect_format='pcre')

    def youup(self):
        self.write("YOUUP\n")
        self.read(delim="\r",
                  expect="Yep, i'm up, but all our basic lines are \"clogged\"\n"
                         "Upgrade to FASTLANE today!\n")

    def mooch(self):
        """
        <write>
            <data>MOOCH </data>
            <var>last_filename</var>
            <data>\n</data>
        </write>
        <read>
            <delim>\r</delim>
            <match>
                <data format="asciic">the tubes are "clogged" right now...\n</data>
                <data format="asciic">------------------------------------\n</data>
                <pcre>^[0-9]{16}\r$</pcre>
            </match>
        </read>
        """
        self.write('MOOCH ', self.state['filename'], '\n')
        self.read(
            delim='\n',
            expect="the tubes are \"clogged\" right now...")
        self.read(
            delim='\n',
            expect="------------------------------------")
        self.read(
            delim='\r',
            expect=r'^[0-9]{16}\r$',
            expect_format='pcre')

    def sup(self):
        self.write("SUP\n")
        self.read(
            delim='\n',
            expect="here're your files, plebian:")
        self.read(
            delim='\n',
            expect="----------------------------")
        self.read(
            delim='\r',
            expect=r'([a-z]{16}\n)+',
            expect_format='pcre')

    #### FASTLANE VERBS ####

    def check_credits(self, verb):
        if 0 == self.state['credits']:
            self.write(verb + "\n")
            self.read(delim='\r', expect="you're too poor to use this verb :(\n")
            return -1

        self.state['credits'] -= 1
        return 0

    def tip(self):
        """
        <write>
            <data>TIP </data>
            <var>last_filename</var>
            <data>\n</data>
        </write>
        <read>
            <delim>\r</delim>
            <match>
                <data format="asciic">Just the Tip!\n</data>
                <data format="asciic">-------------\n</data>
                <pcre>^[0-9]{4}\r$</pcre>
            </match>
        </read>
        """
        if -1 == self.check_credits("TIP"):
            return

        self.write('TIP ', self.state['filename'], '\n')
        self.read(
            delim='\n',
            expect="Just the Tip!")
        self.read(
            delim='\n',
            expect="-------------")
        self.read(
            delim='\r',
            expect=r'^[0-9]{4}\r$',
            expect_format='pcre')

    def status(self):
        if -1 == self.check_credits("STATUS"):
            return

        self.write("STATUS" + "\n")
        self.read(delim="\r",
                  expect="FASTLANE fully operational!\n"
                         "Thank you for asking kind sir/madam!\n")

    def gimme(self):
        """
        <write>
            <data>GIMME </data>
            <var>last_filename</var>
            <data>\n</data>
        </write>
        <read>
            <delim>\r</delim>
            <match>
                <data format="asciic">Your FASTLANE file contents; we appreciate your business!\n</data>
                <data format="asciic">---------------------------------------------------------\n</data>
                <pcre>^[0-9]{16}\r$</pcre>
            </match>
        </read>
        """
        if -1 == self.check_credits("GIMME"):
            return

        self.write('GIMME ', self.state['filename'], '\n')
        self.read(
            delim='\n',
            expect="Your FASTLANE file contents; we appreciate your business!")
        self.read(
            delim='\n',
            expect="---------------------------------------------------------")
        self.read(
            delim='\r',
            expect=r'^[0-9]{16}\r$',
            expect_format='pcre')

    def list(self):
        if -1 == self.check_credits("LIST"):
            return

        self.write("LIST" + "\n")
        self.read(
            delim='\n',
            expect="Your files, kind sir/madam!")
        self.read(
            delim='\n',
            expect="---------------------------")
        self.read(
            delim='\r',
            expect=r'([a-z]{16}\n)+',
            expect_format='pcre')
