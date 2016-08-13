#!/usr/bin/env python
#
# Copyright (C) 2014 Brian Caswell <bmc@lungetech.com>
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

from generator.actions import Actions
import random
import string


def random_string(size):
    chars = string.letters + string.digits
    return ''.join(random.choice(chars) for _ in range(size))


class FTP(Actions):

    def start(self):
        pass

    def login(self):
        username = random.choice(
            ['anonymous', random_string(random.randint(1, 10))])
        self.write('USER %s\n' % username)

        if 'login' in self.state:
            self.read(delim='\n', expect='Already logged in\n')
        else:
            self.state['username'] = username
            self.read(delim='\n', expect='331 Please specify the password.\n')

    def password(self):
        password = random_string(random.randint(1, 10))
        self.write('PASS %s\n' % password)

        if 'username' in self.state:
            if 'login' in self.state:
                self.read(delim='\n', expect='301 Already logged in\n')
            else:
                self.state['login'] = True
                self.read(delim='\n', expect='230 Login successful.\n')
        else:
            self.read(delim='\n', expect='302 No username sent.\n')

    def after_login(self):
        pass

    def file_list(self):
        self.write('LIST\n')
        if 'login' in self.state:
            responses = ['^200']

            if 'upload' in self.state:
                responses.append('file: %s' % self.state['upload'])

            if 'deleted' in self.state:
                responses.append(r'(?s)^((?!file: %s).)*$' %
                                 self.state['deleted'])

            self.read(delim='\n\n', expect=random.choice(
                responses), expect_format='pcre')
        else:
            self.read('\n', expect="300 not logged in\n")

    def delete(self):
        files = [random_string(random.randint(1, 100))]

        if 'deleted' in self.state:
            files.append(self.state['deleted'])

        if 'upload' in self.state:
            files.append(self.state['upload'])

        filename = random.choice(files)

        self.write('DELETE %s\n' % filename)

        if 'login' not in self.state:
            self.read('\n', expect="300 not logged in\n")
        else:
            if 'upload' in self.state and filename == self.state['upload']:
                self.read('\n', expect="200 deleted\n")
                self.state['deleted'] = self.state.pop('upload')
            else:
                self.read('\n', expect="300 uknown file: %s\n" % filename)

    def fetch(self):
        files = [random_string(random.randint(1, 100))]

        if 'deleted' in self.state:
            files.append(self.state['deleted'])
        if 'upload' in self.state:
            files.append(self.state['upload'])

        filename = random.choice(files)

        self.write('FETCH %s\n' % filename)

        if 'login' not in self.state:
            self.read('\n', expect="300 not logged in\n")
        else:
            if 'upload' in self.state and filename == self.state['upload']:
                self.read('\n',
                          expect=r'400 OK (\d+ bytes).*\n\n',
                          expect_format='pcre')
            else:
                self.read('\n', expect="300 uknown file: %s\n" % filename)

    def put(self):
        filename = random_string(random.randint(1, 100))
        self.write("PUT %s\n" % filename)
        self.read(delim='\n', expect="200 OK\n")
        self.state['upload'] = filename

    def logout(self):
        self.write("LOGOUT\n")
        if 'login' in self.state:
            self.read('\n', expect="200 Logged %s out\n" %
                      self.state['username'])
            self.state.pop('login')
        else:
            self.read('\n', expect="399 error: not logged in\n")
