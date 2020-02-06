#!/usr/bin/env python

from generator.actions import Actions
import random
import struct

MSG_DISCONNECT = 100
MSG_IGNORE = 101
MSG_UNRECOGNIZED = 102
MSG_SERVICE_REQUEST = 103
MSG_SERVICE_ACCEPT = 104
MSG_USERAUTH_REQUEST = 110
MSG_USERAUTH_FAILURE = 111
MSG_USERAUTH_SUCCESS = 112
MSG_USERAUTH_BANNER = 113
MSG_USERAUTH_PASSWD_CHANGEREQ = 120

def random_bytes(n):
    return ''.join([chr(random.randint(0,255)) for x in xrange(n)])

def byte(x):
    return struct.pack('>B', x)

def uint32(x):
    return struct.pack('>I', x)

def string(x):
    return uint32(len(x)) + x

class TemplateGenerator(Actions):
    def read_packet(self, data):
        padding_len = 8 - ((len(data) + 5) % 8)
        data = struct.pack('>IB', len(data) + padding_len + 1, padding_len) + data
        self.read(length=len(data), expect=data)
        self.read(length=padding_len)

    def write_packet(self, data):
        padding_len = 8 - ((len(data) + 5) % 8)
        padding = random_bytes(padding_len)
        data = struct.pack('>IB', len(data) + padding_len + 1, padding_len) + data + padding
        self.write(data)
        self.state['seq'] += 1

    def magic_string(self, max_n):
        offset = self.state['magic_offset']
        while True:
            s = self.magic_page[offset:offset + max_n]
            i = s.find('\0')
            if i == -1:
                break
            elif i != 0:
                offset += 1
                s = s[0:i]
                break
            offset += 1
        offset += len(s)
        self.state['magic_offset'] = offset
        return s

    def start(self):
        #self.delay(100)
        self.state['seq'] = 0
        self.state['creds'] = {}
        self.state['magic_offset'] = 0
        self.state['service'] = None

        for x in xrange(16):
            username = self.magic_string(8)
            password = self.magic_string(8)
            self.state['creds'][username] = password

    def go(self):
        pass

    def disconnect(self):
        self.write_packet(byte(MSG_DISCONNECT))
        self.read_packet(byte(MSG_DISCONNECT))

    def ignore(self):
        self.write_packet(byte(MSG_IGNORE))

    def service_request(self):
        service_name = 'userauth'
        self.state['service'] = 'userauth'
        self.write_packet(byte(MSG_SERVICE_REQUEST) + string(service_name))
        self.read_packet(byte(MSG_SERVICE_ACCEPT) + string(service_name))

    def userauth_request(self):
        username = random.choice(self.state['creds'].keys() + [random_bytes(random.randint(0, 32))])
        service_name = random_bytes(10)
        auth_name = 'password' if self.chance(0.9) else random_bytes(random.randint(0, 32))
        password = self.state['creds'].get(username, 'fakepassword')
        if self.chance(0.5):
            new_password = None
        else:
            new_password = random_bytes(random.randint(0,16))
            i = new_password.find('\0')
            if i >= 0:
                new_password = new_password[0:i]

        if new_password:
            self.write_packet(byte(MSG_USERAUTH_REQUEST) + string(username) + string(service_name) + string(auth_name) + byte(1) + string(password) + string(new_password))
        else:
            self.write_packet(byte(MSG_USERAUTH_REQUEST) + string(username) + string(service_name) + string(auth_name) + byte(0) + string(password))

        if self.state['service'] != 'userauth':
            self.read_packet(byte(MSG_UNRECOGNIZED) + uint32(self.state['seq'] - 1))
        elif auth_name == 'password' and username in self.state['creds'] and password == self.state['creds'][username]:
            if new_password:
                if len(new_password) >= 8:
                    self.state['creds'][username] = new_password
                    self.read_packet(byte(MSG_USERAUTH_SUCCESS))
                else:
                    prompt = 'Too short'
                    self.read_packet(byte(MSG_USERAUTH_PASSWD_CHANGEREQ) + string(prompt))
            else:
                self.read_packet(byte(MSG_USERAUTH_SUCCESS))
        else:
            self.read_packet(byte(MSG_USERAUTH_FAILURE) + string("password") + byte(0))

    def unimplemented(self):
        msg = random.choice(list(set(xrange(256)) - set([MSG_DISCONNECT, MSG_IGNORE, MSG_UNRECOGNIZED, MSG_SERVICE_ACCEPT, MSG_SERVICE_REQUEST, MSG_USERAUTH_REQUEST, MSG_USERAUTH_FAILURE, MSG_USERAUTH_SUCCESS, MSG_USERAUTH_BANNER, MSG_USERAUTH_PASSWD_CHANGEREQ])))
        self.write_packet(byte(msg) + random_bytes(random.randint(0, 1024)))
        self.read_packet(byte(MSG_UNRECOGNIZED) + uint32(self.state['seq'] - 1))
