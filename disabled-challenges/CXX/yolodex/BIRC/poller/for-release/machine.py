from generator.actions import Actions
import random
import string
import struct
import numpy as np
import math
import datetime as dt
import ctypes

MAX_USERS = 256

REGISTER_USER_CMD_ID = struct.pack("H", 11382)
SEARCH_FOR_USER_CMD_ID = struct.pack("H", 11591)
DELETE_USER_CMD_ID = struct.pack("H", 11498)
JOIN_CHANNEL_CMD_ID = struct.pack("H", 22193)
SEARCH_FOR_CHANNEL_CMD_ID = struct.pack("H", 2201)
PART_CHANNEL_CMD_ID = struct.pack("H", 22881)
DELETE_CHANNEL_CMD_ID = struct.pack("H", 22117)
CHANNEL_CHAT_CMD_ID = struct.pack("H", 3190)
USER_CHAT_CMD_ID = struct.pack("H", 31900)
EXIT_SERVER_CMD_ID = struct.pack("H", 9999)
REMOTE_ADMIN_TOKEN_REQUEST_CMD_ID = struct.pack("H", 7777)
LOGIN_CMD_ID = struct.pack("H", 8711)
LOGOUT_CMD_ID = struct.pack("H", 8719)
CLIENT_SUCCESS = struct.pack("H", 1234)
CLIENT_FAIL = struct.pack("H", 4321)

CLIENT_LOGOUT_ALERT = struct.pack("H", 8791)
CLIENT_SESSION_TIMEOUT_ALERT = struct.pack("H", 2431)

pack_param = lambda x: struct.pack("H{0}s".format(len(x)), len(x), x)

def random_word(max_size=10, min_size=2):
    if random.randint(0,4):
        characters = string.letters + string.digits
    else:
        characters = string.letters
    max_size = max_size if max_size >= min_size else min_size
    max_size = random.randint(min_size, max_size)
    return ("".join(random.choice(characters) for c in range(max_size))).lower()

def random_text(max_words=10, min_words=3):
    max_words = max_words if max_words >= min_words else min_words
    text = ''
    for x in xrange(random.randint(min_words, max_words)):
        text += random_word() + ' '
    return text

def rand_bytes(min_size=3, max_size=30):
    rndbytes = ''
    for x in xrange(random.randint(min_size, max_size)):
        rndbytes += chr(random.randint(0,255))
    return rndbytes

class User():
    def __init__(self):
        self.name = ''
        self.password = ''

    def register_msg(self):
        msg = struct.pack("H", len(self.name))
        msg += struct.pack("{0}s".format(len(self.name)), self.name)
        return msg

    def search_for_user_msg():
        msg = struct.pack("H", len(self.name))
        msg += struct.pack("{0}s".format(len(self.name)), self.name)
        return msg

    def delete_msg():
        msg = struct.pack("H", len(self.password))
        msg += struct.pack("{0}s".format(len(self.password)), self.password)

    def login_msg():
        msg = struct.pack("H", len(self.name))
        msg += struct.pack("{0}s".format(len(self.name)), self.name)
        msg += struct.pack("H", len(self.password))
        msg += struct.pack("{0}s".format(len(self.password)), self.password)
        return msg

    def password_resp_msg(self):
        msg = struct.pack("H", len(self.password))
        msg += struct.pack("{0}s".format(len(self.password)), self.password)
        return msg

    @classmethod
    def random(cls):
        user = cls()
        user.name = rand_bytes()
        return user

class Channel():
    def __init__(self, creator):
        self.name = ''
        self.creator = creator
        self.users = [ creator ]

    def join_msg(self):
        msg = struct.pack("H", len(self.name))
        msg += struct.pack("{0}s".format(len(self.name)), self.name)
        return msg

    def search_for_channel_msg(self):
        msg = struct.pack("H", len(self.name))
        msg += struct.pack("{0}s".format(len(self.name)), self.name)
        return msg

    def part_msg(self):
        msg = struct.pack("H", len(self.name))
        msg += struct.pack("{0}s".format(len(self.name)), self.name)
        return msg

    def delete_msg(self):
        msg = struct.pack("H", len(self.name))
        msg += struct.pack("{0}s".format(len(self.name)), self.name)
        return msg

    @classmethod
    def random(cls, creator):
        channel = cls(creator)
        channel.name = rand_bytes()
        return channel


class Brc(Actions):
    def _get_random_byte(self):
        self.prng1 = ctypes.c_uint32(36969 * (self.prng1 & 65535)).value + ctypes.c_uint32((self.prng1 >> 16)).value
        self.prng2 = ctypes.c_uint32(18000 * (self.prng2 & 65535)).value + ctypes.c_uint32((self.prng2 >> 16)).value
        byte_idx =  (ctypes.c_uint32((self.prng1 << 16)).value + self.prng2) % 4096;
        return struct.unpack('<B', self.magic_page[byte_idx])[0]

    def _generate_password(self):
        pw = ''
        for x in xrange(10):
            pw += chr(self._get_random_byte())
        return pw

    def _search_all_users(self, user):
        for u in self.all_users:
            if user.name == u.name:
                return True
        return False

    def _delete_cur_user(self):
        if not self.cur_user:
            return

        for x in xrange(len(self.all_users)):
            if self.cur_user.name == self.all_users[x].name:
                self.all_users.pop(x)
                break

        chans_to_delete = []
        for x in xrange(len(self.all_channels)):
            if self.cur_user.name == self.all_channels[x].creator.name:
                chans_to_delete.insert(0,x)
            else:
                for y in xrange(len(self.all_channels[x].users)):
                    if self.cur_user.name == self.all_channels[x].users[y].name:
                        self.all_channels[x].users.pop(y)
                        break
        for x in chans_to_delete:
            self.all_channels.pop(x)
        self.cur_user = None

    def _search_all_channels(self, chan):
        for c in self.all_channels:
            if chan.name == c.name:
                return True
        return False

    def _join_channel(self, chan):
        channel = None
        for c in self.all_channels:
            if chan.name == c.name:
                channel = c
                break
        if channel:
            for u in channel.users:
                if self.cur_user.name == u.name:
                    return False
            channel.users.append(self.cur_user)
        else:
            self.all_channels.append(chan)
        return True

    def _part_channel(self, chan):
        channel = None
        for c in self.all_channels:
            if chan.name == c.name:
                channel = c
        if channel:
            for x in xrange(len(channel.users)):
                if self.cur_user.name == channel.users[x].name:
                    channel.users.pop(x)
                    return True
        return False

    def _delete_channel(self, chan):
        for x in xrange(len(self.all_channels)):
            if chan.name == self.all_channels[x].name:
                if self.cur_user.name == self.all_channels[x].creator.name:
                    self.all_channels.pop(x)
                    return True
        return False

    def _read(self, data):
        self.read(length=len(data), expect=data)

    def _read_success_resp(self):
        self._read(CLIENT_SUCCESS)

    def _read_fail_resp(self):
        self._read(CLIENT_FAIL)

    def _read_logout_resp(self):
        self._read(CLIENT_LOGOUT_ALERT)

    def _read_timeout_alert(self):
        self._read(CLIENT_SESSION_TIMEOUT_ALERT)

    def _write_param(self, param):
        self.write(pack_param(param))

    def start(self):
        #self.delay(100)
        self.all_users = []
        self.all_channels = []
        self.cur_user = None
        self.session_timeout = 30
        self.prng1 = ctypes.c_uint32(struct.unpack('<I', self.magic_page[0:4])[0]).value
        self.prng2 = ctypes.c_uint32(struct.unpack('<I', self.magic_page[4:8])[0]).value

        self.session_timeout -= 1

    def awaiting_input(self):
        self.session_timeout -= 1
        if self.cur_user and self.session_timeout == 0:
            self._read_timeout_alert()

            if random.randint(0,9) > 2:
                self._write_param(self.cur_user.password)
                self._read_success_resp()
                self.session_timeout = 30
            else:
                self._write_param(rand_bytes(33,40))
                self._read_fail_resp()
                self._read_logout_resp()
                self.cur_user = None

    def register_user(self):
        self.write(REGISTER_USER_CMD_ID)
        if self.cur_user:
            self._read_fail_resp()
            return

        user = User.random()
        self.write(user.register_msg())
        if not self._search_all_users(user):
            self._read_success_resp()
            user.password = self._generate_password()
            self._read(user.password_resp_msg())
            self.all_users.append(user)
            self.cur_user = user
            self.session_timeout = 30
        else:
            self._read_fail_resp()

    def search_for_user(self):
        self.write(SEARCH_FOR_USER_CMD_ID)

        if self.all_users and random.randint(0,9) > 3:
            user = self.all_users[random.randint(0, len(self.all_users) - 1)]
            self._write_param(user.name)
            self._read_success_resp()
        else:
            self._write_param(rand_bytes(33,40))
            self._read_fail_resp()

    def delete_user(self):
        self.write(DELETE_USER_CMD_ID)
        if not self.cur_user:
            self._read_fail_resp()
            return

        if random.randint(0,9) > 3:
            self._write_param(self.cur_user.password)
            self._delete_cur_user()
            self._read_success_resp()
        else:
            self._write_param(rand_bytes(33,40))
            self._read_fail_resp()

    def join_channel(self):
        self.write(JOIN_CHANNEL_CMD_ID)
        if not self.cur_user:
            self._read_fail_resp()
            return

        if self.all_channels and random.randint(0,9) > 2:
            chan = self.all_channels[random.randint(0, len(self.all_channels) - 1)]
        else:
            chan = Channel.random(self.cur_user)

        self.write(chan.join_msg())
        if self._join_channel(chan):
            self._read_success_resp()
        else:
            self._read_fail_resp()

    def search_for_channel(self):
        self.write(SEARCH_FOR_CHANNEL_CMD_ID)

        if self.all_channels and random.randint(0,9) > 5:
            chan = self.all_channels[random.randint(0, len(self.all_channels) - 1)]
            self._write_param(chan.name)
            self._read_success_resp()
        else:
            self._write_param(rand_bytes(33,40))
            self._read_fail_resp()

    def part_channel(self):
        self.write(PART_CHANNEL_CMD_ID)
        if not self.cur_user:
            self._read_fail_resp()
            return

        if self.all_channels and random.randint(0,9) > 4:
            chan = self.all_channels[random.randint(0, len(self.all_channels) - 1)]
        else:
            chan = Channel.random(self.cur_user)

        self.write(chan.part_msg())
        if self._part_channel(chan):
            self._read_success_resp()
        else:
            self._read_fail_resp()

    def delete_channel(self):
        self.write(DELETE_CHANNEL_CMD_ID)
        if not self.cur_user:
            self._read_fail_resp()
            return


        if self.all_channels and random.randint(0,9) > 3:
            chan = self.all_channels[random.randint(0, len(self.all_channels) - 1)]
        else:
            chan = Channel.random(self.cur_user)

        self.write(chan.delete_msg())
        if self._delete_channel(chan):
            self._read_success_resp()
        else:
            self._read_fail_resp()

    def login(self):
        self.write(LOGIN_CMD_ID)
        if self.cur_user:
            self._read_fail_resp()
            return

        if self.all_users:
            self.cur_user = self.all_users[random.randint(0, len(self.all_users) - 1)]
            self._write_param(self.cur_user.name)
            self._write_param(self.cur_user.password)
            self._read_success_resp()
            self.session_timeout = 30
        else:
            self._write_param(rand_bytes(33, 40))
            self._write_param(rand_bytes(33, 40))
            self._read_fail_resp()

    def logout(self):
        self.write(LOGOUT_CMD_ID)
        if not self.cur_user:
            self._read_fail_resp()
            return

        self.cur_user = None
        self._read_success_resp()
        self._read_logout_resp()

    def exit_server(self):
        self.write(EXIT_SERVER_CMD_ID)

    def remote_admin_token_request():
        page_idx = random.randint(0, 1023)
        msg = REMOTE_ADMIN_TOKEN_REQUEST_CMD_ID
        msg += struct.pack("H", page_idx)


