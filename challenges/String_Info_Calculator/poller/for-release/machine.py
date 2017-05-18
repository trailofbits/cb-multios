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
from common import DEBUG

class StrInfo(Actions):

    INBUFSZ = 1000
    DEBUG_CONTENT = False

    TERM = '\x03'
    GIMME = "Give me your sentences.{0}".format(TERM)
    DONE = "Here are your results...{0}".format(TERM)

    def _get_content(self):
        all_chars = [chr(x) for x in range(128)]
        all_chars.remove(self.TERM)

        result = ''
        b_len = randint(5, self.INBUFSZ-1) #TERM is added at the end.
        remaining = b_len
        while 0 < remaining:

            if self.chance(0.7):
                result += sp.random_alpha(0, 10 if remaining > 10 else remaining)
            elif self.chance(0.3):
                result += sp.random_digits(0, 10 if remaining > 10 else remaining)
            else:
                result += ''.join(choice(all_chars) for _ in range(0, 10 if remaining > 10 else remaining))

            if len(result) >= b_len:
                break

            if self.chance(0.7):
                result += ' '
            else:
                result += '.'

            if self.chance(0.1):
                result += '\n'

            remaining = b_len - len(result)

        if True == self.DEBUG_CONTENT:
            result = "Bob's discount randumb stor-E gener8r for only $12.99. Come on in.\nGet your storie today!\n"

        if True == DEBUG:
            r = '\\'.join(hex(ord(c)) for c in result)
            print "result hex: {0}".format(r)
            print "result: {0}".format(result)

        return result

    def _get_results(self, s):
        '''
            unsigned int hash;

            unsigned short chars;
            unsigned short words;
            unsigned short sentences;
            unsigned short paragraphs;

            unsigned short printable;
            unsigned short non_printable;

            unsigned short letters;
            unsigned short numbers;
            unsigned short symbols;

            unsigned short session_id;
        '''
        r = {'chars': 0, 'words': 0,
            'sentences': 0, 'paragraphs': 0, 'printable': 0,
            'non_printable': 0, 'letters': 0, 'numbers': 0, 'symbols': 0,
            'session_id': 0}

        r = self._compute_char_type(s, r)
        r = self._compute_grammar_components(s, r)
        r = self._compute_session_id(r)
        return r

    def _compute_char_type(self, s, r):
        for ch in s:
            if True == sp.is_non_printable(ord(ch)):
                r['non_printable'] += 1
            else:
                r['printable'] += 1

                if True == sp.is_digit(ord(ch)):
                    r['numbers'] += 1
                elif True == sp.is_letter(ord(ch)):
                    r['letters'] += 1
                else:
                    r['symbols'] += 1

        if True == DEBUG:
            print "type: {0}".format(r)
        return r

    def _compute_grammar_components(self, s, r):
        ch_prev = '\x04'
        for ch in s:
            r['chars'] += 1

            if True == sp.is_word_end_char(ch) and \
                True == sp.is_letter(ord(ch_prev)):
                r['words'] += 1

            if True == sp.is_sentence_end_char(ch_prev):
                if ' ' == ch:
                    r['sentences'] += 1
                elif True == sp.is_paragraph_end_char(ch):
                    r['sentences'] += 1
                    r['paragraphs'] += 1

            ch_prev = ch

        if True == DEBUG:
            print "grammar: {0}".format(r)
        return r

    def _compute_session_id(self, r):
        '''
        const char *magic_sauce = (const char*)FLAG_PAGE;
        char session_id[2] = 0;
        unsigned short *p_sid = (unsigned short *)session_id;

        session_id[0] = magic_sauce[0] ^ magic_sauce[1000];
        session_id[1] = magic_sauce[2000] ^ magic_sauce[3000];

        r->session_id = *p_sid;
        '''
        b1 = ord(self.magic_page[0]) ^ ord(self.magic_page[1000])
        b2 = ord(self.magic_page[2000]) ^ ord(self.magic_page[3000])
        r['session_id'] = (b2 << 8) + b1

        return r

    def start(self):
        self.delay(50)
        pass

    def banner(self):
        self.read(delim=self.TERM, expect=self.GIMME)

    def content(self):
        s = self._get_content()
        self.write(s + self.TERM)

        r_clear = self._get_results(s)
        if True == DEBUG:
            print "clear: {0}".format(r_clear)

        r_packed = sp.pack_results(r_clear)
        if True == DEBUG:
            r = '\\'.join(hex(ord(c)) for c in r_packed)
            print "packed: {0}".format(r)

        self.read(delim=self.TERM, expect=self.DONE)
        self.read(length=4) # read the hash
        self.read(length=len(r_packed), expect=r_packed) # read the results
        # self.read(length=2) # read the session_id value

    def end(self):
        return
