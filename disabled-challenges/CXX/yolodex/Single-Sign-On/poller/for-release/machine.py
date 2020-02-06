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
import string
import random
import itertools
import math
from struct import *
from collections import Counter

class TemplateGenerator(Actions):

    def start(self):
        self.token = pack('l', 4)
        self.resource = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(5))
        self.users = []
        self.commands = ['REQR', 'LOUT', 'REVR', 'REVU']

    def command_no_user_failure(self):
        command = random.choice(self.commands)
        user_id = random.randint(1,100000)
        while Counter(elem[0][0] for elem in self.users)[user_id] > 0:
            user_id = random.randint(1,100000)
        user_id_str = pack('l', user_id)
        self.write(command + user_id_str + self.token + self.resource + '\x07')
        self.read(delim="\n", expect = "Command failed.\n")

    def request_no_resource_failure(self):
        user = random.choice(self.users)
        user_id_str = pack('l', user[0][0])
        resource = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(5))
        while Counter(elem[0] for elem in user[1])[resource] > 0:
            resource = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(5))
        self.write("REQR" + user_id_str + self.token + resource + '\x07')
        self.read(delim="\n", expect = "Please re-authenticate.\n")

    def request_resource_wrong_token_failure(self):
        auth_val = Variable('authval')
        if len(filter(lambda x: x[1], self.users)) == 0:
            self.auth_success_with_auth_val()
        user = random.choice(filter(lambda x: x[1], self.users))
        user_id_str = pack('l', user[0][0])
        resource = random.choice(user[1])
        self.write("REQR" + user_id_str + self.token + resource[0] + '\x07')
        regex_str = 'Authentication failed for resource %s(.*)\x0a' % resource[0]
        auth_val.set_re(regex_str, group=1)
        self.read(delim="\n", assign=auth_val)
        self.read(delim="\n", expect = "Please re-authenticate.\n")

    def request_success(self):
        my_token = Variable('token')
        if len(filter(lambda x: x[1], self.users)) == 0:
            self.auth_success_with_auth_val()
        user = random.choice(filter(lambda x: x[1], self.users))
        user_id_str = pack('l', user[0][0])
        resource = random.choice(user[1])
        self.write("REQR" + user_id_str)
        self.write(resource[1])
        self.write(resource[0] + '\x07')
        regex_str = 'Access to %s is granted!(.*)\x0a' % resource[0]
        my_token.set_re(regex_str, group=1)
        self.read(delim="\n", assign=my_token)

    def auth_failure_new_user(self):
        user_id = random.randint(2,100000)
        while Counter(elem[0][0] for elem in self.users)[user_id] > 0:
            user_id = random.randint(2,100000)
        user_id_str = pack('l', user_id)
        varname = "user"+str(user_id)
        variable = Variable(varname)
        user_item = [user_id, variable]
        self.users.append([user_item, []])
        resource = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(10))
        self.write("AUTH" + user_id_str + self.token + resource + '\x07')
        regex_str = 'Authentication failed for resource %s(.*)\x0a' % resource
        variable.set_re(regex_str, group=1)
        self.read(delim="\n", assign=variable)

    def auth_failure_current_user(self):
        user = random.choice(self.users)
        user_id_str = pack('l', user[0][0])
        resource = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(10))
        variable = user[0][1]
        self.write("AUTH" + user_id_str + self.token + resource + '\x07')
        regex_str = 'Authentication failed for resource %s(.*)\x0a' % resource
        variable.set_re(regex_str, group=1)
        self.read(delim="\n", assign=variable)

    def auth_success_with_auth_val(self):
        user = random.choice(self.users)
        user_id_str = pack('l', user[0][0])
        resource = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(9))
        varname = resource+str(user[0][0])
        variable = Variable(varname)
        resource_item = [resource, variable]
        user[1].append(resource_item)
        self.write("AUTH" + user_id_str)
        self.write(user[0][1])
        self.write(resource + '\x07')
        regex_str = 'Access to %s is granted!(.*)\x0a' % resource
        variable.set_re(regex_str, group=1)
        self.read(delim="\n", assign=variable)

    def revoke_resource_success(self):
        if len(filter(lambda x: x[1], self.users)) == 0:
            self.auth_success_with_auth_val()
        user = random.choice(filter(lambda x: x[1], self.users))
        user_id_str = pack('l', user[0][0])
        resource = random.choice(user[1])
        user[1].remove(resource)
        self.write("REVR" + user_id_str)
        self.write(resource[1])
        self.write(resource[0] + '\x07')
        self.read(delim="\n", expect="Resource revoked.\n")

    def revoke_resource_failure(self):
        if len(filter(lambda x: x[1], self.users)) == 0:
            self.auth_success_with_auth_val()
        user = random.choice(filter(lambda x: x[1], self.users))
        user_id_str = pack('l', user[0][0])
        resource = random.choice(user[1])
        token = self.token
        self.write("REVR" + user_id_str)
        self.write(token)
        self.write(resource[0] + '\x07')
        self.read(delim="\n", expect="Revocation denied.\n")

    def logout(self):
        if not self.users:
            return self.quit()
        user = random.choice(self.users)
        user_id_str = pack('l', user[0][0])
        self.users.remove(user)
        self.write("LOUT" + user_id_str + self.token + self.resource + '\x07')
        self.read(delim="\n", expect="Logged out successfully.\n")


    def quit(self):
        return -1
