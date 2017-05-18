#!/usr/bin/env python

import random
import string
from struct import pack, unpack
import ctypes 
from generator.actions import Actions
import random

SLS_TYPE_CHANGESPEC  = 0x01
SLS_TYPE_ERROR       = 0x02
SLS_TYPE_HANDSHAKE   = 0x03
SLS_TYPE_APPLICATION = 0x04
SLS_TYPE_HEARTBEAT   = 0x05
SLS_TYPE_SHUTDOWN   = 0x06


MSLS_ERROR_LENGTH   = 0xe0
MSLS_ERROR_VERSION  = 0xe1
MSLS_ERROR_CHECKSUM = 0xe2

MSLS_SEVERITY_WARNING  = 0xa0
MSLS_SEVERITY_CRITICAL = 0xa1
MSLS_SEVERITY_FATAL    = 0xa2

MSLS_HEARTBEAT_REQUEST  = 0x41
MSLS_HEARTBEAT_RESPONSE = 0x42
SLS_HEARTBEAT_HEADER_LEN  = 1 + 2

SLS_VERSION = "\x01\xff"
SLS_HEADER_LENGTH  = 2+2+1+4+4+2
SLS_HANDSHAKE_HEADER_LEN  = (2+4+4+2)
SLS_APPLICATION_HEADER_LEN = (1+2)

MAX_CIPHER_SUITES = 12
MSLS_COOKIE_SIZE = 128

MSLS_HS_CLIENT_HELLO = 0x51
MSLS_HS_HELLO_VERIFY = 0x52
MSLS_HS_SERVER_HELLO = 0x53
MSLS_HS_CERTIFICATE  = 0x54
MSLS_HS_SERVER_KEYX  = 0x55
MSLS_HS_CLIENTKEYX   = 0x56
MSLS_HS_SERVER_DONE  = 0x57
MSLS_HS_CLIENT_DONE  = 0x58
MSLS_HS_FINISH       = 0x59

SERVER_SECRET1_OFFSET = 512
SERVER_SECRET2_OFFSET  = 512 + 128*4
PUBLIC_KEY_BASE1_OFFSET = 1024
PUBLIC_KEY_BASE2_OFFSET = 1024 + 128*4
RANDOM_BASE_OFFSET = 2048
RANDOM_BASE_END_OFFSET = 4096

APPLICATION_TYPE_LIST_BOARD     = 0xa0
APPLICATION_TYPE_POST_MESSAGE   = 0xa1
APPLICATION_TYPE_DELETE_MESSAGE = 0xa2
APPLICATION_TYPE_CLEAR_BOARD    = 0xa3
APPLICATION_TYPE_READ_MESSAGE   = 0xa4 
APPLICATION_TYPE_RESPONSE       = 0xaa
APPLICATION_MSG_LENGTH          = 128
APPLICATION_MAX_MESSAGES         = 64

class MSLS_HEARTBEAT_MESSAGE:
  length = 0
  def __init__(self, type):
    self.type = type  
    payload_length = random.randint(10,64)
    self.payload = "".join(random.choice(string.ascii_letters) for _ in range(payload_length))
    self.length = SLS_HEARTBEAT_HEADER_LEN + len(self.payload)

  def to_string(self):
    msg = ""
    msg += pack("<B", self.type)
    msg += pack("<H", len(self.payload))
    msg += self.payload
    return msg

  def get_length(self):
    return self.length


class MSLS_CHANGESPEC_MESSAGE:
  length=0
  def __init__(self, cipher_suite):
    self.cipher_suite = cipher_suite

  def to_string(self):
    msg = ""
    msg += pack("<H", self.cipher_suite)
    return msg

  def get_length(self):
    return 2

class APPLICATION_MESSAGE:
  length=0
  def __init__(self, type, connection):
    self.type = type
    self.connection = connection
    self.length = SLS_APPLICATION_HEADER_LEN
    self.message = ""


  def to_string(self):
    msg = ""
    msg += pack("<B", self.type)
    msg += pack("<H", len(self.message))
    msg += self.message
    return msg

  def encrypt(self):
    encrypted = ""
    keyIndex = 0
    for each in self.message:
      byte = unpack("B", each)[0]
      serverKey = unpack("<I", self.connection['server_key'][keyIndex*4: keyIndex*4+4])[0] & 0xff
      clientSecret = unpack("<I", self.connection['client_secret'][keyIndex*4: keyIndex*4+4])[0] & 0xff
      value = (byte ^ serverKey ^ clientSecret)
      encrypted+= pack("B", value)
      keyIndex += 1
      if (keyIndex >= 128):
        keyIndex = 0
    self.message = encrypted

  def decrypt(self):
    decrypted = ""
    keyIndex = 0
    for each in self.message:
      byte = unpack("B", each)[0]
      clientKey = unpack("<I", self.connection['client_key'][keyIndex*4: keyIndex*4+4])[0] & 0xff
      serverSecret = unpack("<I", self.connection['server_secret'][keyIndex*4: keyIndex*4+4])[0] & 0xff
      value = (byte ^ clientKey ^ serverSecret)
      decrypted += pack("B", value)
      keyIndex += 1
      if (keyIndex >= 128):
        keyIndex = 0
    self.message = decrypted

  def get_length(self):
    return self.length

  def add_byte(self, byte):
    self.message += pack("<B", byte)
    self.length += 1

  def add_to_message(self, msg):
    if (len(msg) >= APPLICATION_MSG_LENGTH):
      self.message += msg[0:APPLICATION_MSG_LENGTH]
    else:
      self.message += msg + "\x00" * (APPLICATION_MSG_LENGTH - len(msg))
    self.length += 128

class MSLS_HANDSHAKE_MESSAGE:
  length = 0
  def __init__(self, type, connection):
    self.type = type  
    self.connection = connection
    self.length = SLS_HANDSHAKE_HEADER_LEN
    self.sequence_num = connection["sequence_num"]
    self.connection_id = connection["connection_id"]
    self.message = ""


  def to_string(self):
    msg = ""
    msg += pack("<H", self.type)
    msg += pack("<I", self.sequence_num)
    msg += pack("<I", self.connection_id)
    msg += pack("<H", len(self.message))
    msg += self.message
    return msg

  def add_to_message(self, data, length):
    if (length == 1):
      self.message += pack("B", data)
      self.length += 1
    elif (length == 2):
      self.message += pack("<H", data)
      self.length += 2
    elif (length == 4):
      self.message += pack("<I", data)
      self.length += 4
    elif (length == 0):
      self.message += data
      self.length += len(data)
    else:
      print "Bad Data Size %d" % length

  def get_length(self):
    return self.length

class SLS_MESSAGE:


  def __init__(self, type, connection):
    self.msg = {}
    self.msg["type"] = type
    self.msg["message"] = None
    self.connection = connection
    None

  def add_message(self, message):
    self.msg["message"] = message

  def to_string(self):
    msg_length = 0
    message = ""
    if self.msg["message"] != None:
      msg_length = self.msg["message"].get_length()
      message = self.msg["message"].to_string()
    msg = pack("<H", SLS_HEADER_LENGTH + msg_length)
    msg += SLS_VERSION
    msg += pack("<B", self.msg["type"])
    msg += pack("<I", self.checksum(message)) 
    if (self.msg["type"] == SLS_TYPE_SHUTDOWN):
      msg += pack("<I", 0)
    else:
      msg += pack("<I", self.connection["connection_id"])
    msg += pack("<H", msg_length)
    msg += message

    return msg

  def checksum(self, data):
    checksum = 0
    if (self.msg["message"]):
      for each in self.msg["message"].to_string():
        checksum = (((checksum << 8)&0xffffffff)|((checksum >> 24)&0xff)) ^ ord(each)
    return checksum


MAX_CONNECTIONS = 32

class CROMU_00097_Generator(Actions):
  
  def start(self):
    self.delay(50)
    self.state["connections"] = []
    self.state["current_connection"] = None
    self.rounds = 0
    self.pRandom = RANDOM_BASE_OFFSET
    self.applicationRounds = 0
    self.board = []

  def main(self):
    self.rounds += 1
    if (self.rounds > 5):
      self.exit()
      return -1

  def application_main(self):
    self.applicationRounds += 1
    if (self.applicationRounds > 5):
      self.exit()
      return -1

  def application_list(self):
    request = SLS_MESSAGE(SLS_TYPE_APPLICATION, self.state["current_connection"])
    app_msg = APPLICATION_MESSAGE(APPLICATION_TYPE_LIST_BOARD, self.state["current_connection"])
    app_msg.encrypt()
    request.add_message(app_msg)
    self.write(request.to_string())
    response = SLS_MESSAGE(SLS_TYPE_APPLICATION, self.state["current_connection"])
    app_rsp = APPLICATION_MESSAGE(APPLICATION_TYPE_RESPONSE, self.state["current_connection"])
    app_rsp.add_to_message("%d of %d slots filled\n" % (len(self.board), APPLICATION_MAX_MESSAGES))
    app_rsp.decrypt()
    response.add_message(app_rsp)
    msg = response.to_string()
    self.read(length=len(msg), expect=msg)

  def application_post(self):
    if (len(self.board) > APPLICATION_MAX_MESSAGES):
      return 
    new_post = ''.join(random.choice(string.ascii_letters) for _ in range(128))
    self.board.append(new_post)
    request = SLS_MESSAGE(SLS_TYPE_APPLICATION, self.state["current_connection"])
    app_msg = APPLICATION_MESSAGE(APPLICATION_TYPE_POST_MESSAGE, self.state["current_connection"])
    app_msg.add_to_message(new_post)
    app_msg.encrypt()
    request.add_message(app_msg)
    self.write(request.to_string())
    response = SLS_MESSAGE(SLS_TYPE_APPLICATION, self.state["current_connection"])
    app_rsp = APPLICATION_MESSAGE(APPLICATION_TYPE_RESPONSE, self.state["current_connection"])
    app_rsp.add_to_message("POST returned: 1\n" )
    app_rsp.decrypt()
    response.add_message(app_rsp)
    msg = response.to_string()
    self.read(length=len(msg), expect=msg)


  def application_delete(self):
    if (len(self.board) == 0):
      return
    index = random.choice(range(len(self.board)))
    self.board.remove(self.board[index])
    request = SLS_MESSAGE(SLS_TYPE_APPLICATION, self.state["current_connection"])
    app_msg = APPLICATION_MESSAGE(APPLICATION_TYPE_DELETE_MESSAGE, self.state["current_connection"])
    app_msg.add_byte(index)
    app_msg.encrypt()
    request.add_message(app_msg)
    self.write(request.to_string())
    response = SLS_MESSAGE(SLS_TYPE_APPLICATION, self.state["current_connection"])
    app_rsp = APPLICATION_MESSAGE(APPLICATION_TYPE_RESPONSE, self.state["current_connection"])
    app_rsp.add_to_message("DELETE returned: 1\n")
    app_rsp.decrypt()
    response.add_message(app_rsp)
    msg = response.to_string()
    self.read(length=len(msg), expect=msg)

  def application_clear(self):
    self.board = []
    request = SLS_MESSAGE(SLS_TYPE_APPLICATION, self.state["current_connection"])
    app_msg = APPLICATION_MESSAGE(APPLICATION_TYPE_CLEAR_BOARD, self.state["current_connection"])
    app_msg.encrypt()
    request.add_message(app_msg)
    self.write(request.to_string())
    response = SLS_MESSAGE(SLS_TYPE_APPLICATION, self.state["current_connection"])
    app_rsp = APPLICATION_MESSAGE(APPLICATION_TYPE_RESPONSE, self.state["current_connection"])
    app_rsp.add_to_message("Cleared Board\n")
    app_rsp.decrypt()
    response.add_message(app_rsp)
    msg = response.to_string()
    self.read(length=len(msg), expect=msg)

  def application_read(self):
    if (len(self.board) == 0):
      return
    index = random.choice(range(len(self.board)))
 
    request = SLS_MESSAGE(SLS_TYPE_APPLICATION, self.state["current_connection"])
    app_msg = APPLICATION_MESSAGE(APPLICATION_TYPE_READ_MESSAGE, self.state["current_connection"])
    app_msg.add_byte(index)
    app_msg.encrypt()
    request.add_message(app_msg)
    self.write(request.to_string())
    response = SLS_MESSAGE(SLS_TYPE_APPLICATION, self.state["current_connection"])
    app_rsp = APPLICATION_MESSAGE(APPLICATION_TYPE_RESPONSE, self.state["current_connection"])
    app_rsp.add_to_message(self.board[index])
    app_rsp.decrypt()
    response.add_message(app_rsp)
    msg = response.to_string()
    self.read(length=len(msg), expect=msg)

  def exit(self):
    request = SLS_MESSAGE(SLS_TYPE_SHUTDOWN, self.state["current_connection"])
    request.connection_id = 0
    msg = request.to_string()
    self.write(msg)
    self.read(length=len(msg), expect=msg)
    
  def get_random(self):
    random = unpack("<I", self.magic_page[self.pRandom:self.pRandom+4])[0]
    self.pRandom += 4
    random = random ^ unpack("<I", self.magic_page[self.pRandom:self.pRandom+4])[0]
    self.pRandom += 4
    if (self.pRandom +8 > RANDOM_BASE_END_OFFSET):
      self.pRandom = RANDOM_BASE_OFFSET
    return random

  def pick_random_connection(self):
    if (len(self.state["connections"]) > 0):
      self.state["current_connection"] = random.choice(self.state["connections"])
    else:
      self.state["current_connection"] = self.new_connection()
    return self.state["current_connection"]

  def heartbeat(self):
    connection = self.pick_random_connection()
    request = SLS_MESSAGE(SLS_TYPE_HEARTBEAT, connection)
    hb_msg = MSLS_HEARTBEAT_MESSAGE(MSLS_HEARTBEAT_REQUEST)
    request.add_message(hb_msg)
    self.write(request.to_string())
    hb_msg.type = MSLS_HEARTBEAT_RESPONSE
    response = request.to_string()
    self.read(length=len(response), expect=response)

  def handshake(self):
    connection = None
    while (connection == None):
      if (self.chance() < 0.2):
        connection = self.pick_random_connection()
        connection["sequence_num"] = 0
      else:
        connection = self.new_connection()

    self.client_hello(connection["connection_id"])
    self.client_hello_with_cookie(connection)
    self.client_keyx(connection)
    self.hello_done(connection)
    self.send_finished(connection)
    connection["is_connected"] = True

  def new_connection(self):
    if (len(self.state["connections"]) >= MAX_CONNECTIONS):
      return None
    client_id = random.randint(1, 0xffffffff)
    while (self.lookup_context(client_id) != None):
      client_id = random.randint(1, 0xffffffff)
    connection = {}
    connection["connection_id"] = client_id
    connection["in_handshake"] = False
    connection["is_connected"] = False
    connection["sequence_num"] = 0
    self.state["connections"].append(connection)
    self.state["current_connection"] = connection
    return connection

  def lookup_context(self, client_id):
    for each in self.state["connections"]:
      if (each["connection_id"] == client_id):
        return each
    return None

  def generate_cookie(self, client_id=0):
    cookie = ""
    for i in range(0, 128*4, 4):
      first_byte = unpack("<I", self.magic_page[i:i+4])[0]
      second_byte = unpack("<I", self.magic_page[128*4+i:128*4+i+4])[0]
      cookie += pack("<I", (first_byte ^ second_byte) ^ client_id)
    return cookie


  def client_hello(self, client_id=0):
    context = None
    if (client_id != 0):
      context = self.lookup_context(client_id)
    if (context == None):
      context = self.pick_random_connection()
      
    request = SLS_MESSAGE(SLS_TYPE_HANDSHAKE, context)
    hs_msg = MSLS_HANDSHAKE_MESSAGE(MSLS_HS_CLIENT_HELLO, context)
    hs_msg.add_to_message(SLS_VERSION, 0)
    context["random"] = random.randint(0, 0xffffffff)
    hs_msg.add_to_message(context["random"], 4)
    hs_msg.add_to_message(0, 4) 
    context["cookie"] = '\x00\x00\x00\x00' * MSLS_COOKIE_SIZE
    hs_msg.add_to_message(context["cookie"], 0)
    context["cipher_suites"] = '\x00\x00' * MAX_CIPHER_SUITES
    hs_msg.add_to_message(context["cipher_suites"], 0)
    request.add_message(hs_msg)
    self.write(request.to_string())

    response = SLS_MESSAGE(SLS_TYPE_HANDSHAKE, context)
    hs_msg = MSLS_HANDSHAKE_MESSAGE(MSLS_HS_HELLO_VERIFY, context)
    hs_msg.add_to_message(SLS_VERSION, 0)
    context["cookie"] = self.generate_cookie(context["connection_id"])
    hs_msg.add_to_message(context["cookie"], 0)
    context["sequence_num"] = 0
    response.add_message(hs_msg)
    s = response.to_string()
    self.read(length=len(s), expect=s)

  def client_hello_with_cookie(self, connection):

    request = SLS_MESSAGE(SLS_TYPE_HANDSHAKE, connection)
    hs_msg = MSLS_HANDSHAKE_MESSAGE(MSLS_HS_CLIENT_HELLO, connection)
    hs_msg.add_to_message(SLS_VERSION, 0)
    hs_msg.add_to_message(connection["random"], 4)
    hs_msg.add_to_message(connection["connection_id"], 4)
    hs_msg.add_to_message(connection["cookie"], 0)
    hs_msg.add_to_message(connection["cipher_suites"], 0)
    request.add_message(hs_msg)
    self.write(request.to_string())

    # Read Server Hello
    connection["sequence_num"] = 1
    response = SLS_MESSAGE(SLS_TYPE_HANDSHAKE, connection)
    hs_msg = MSLS_HANDSHAKE_MESSAGE(MSLS_HS_SERVER_HELLO, connection)
    hs_msg.add_to_message(SLS_VERSION, 0)
    cipher_offset = self.get_random() % (MAX_CIPHER_SUITES -1)
    connection["cipher_suite"] = unpack("<H", connection["cipher_suites"][cipher_offset*2:cipher_offset*2+2])[0]
    hs_msg.add_to_message(self.get_random(), 4)
    hs_msg.add_to_message(connection["cipher_suite"], 2)
    response.add_message(hs_msg)
    s = response.to_string()
    self.read(length=len(s), expect=s)

    # Read Server Keyx
    connection["sequence_num"] = 2
    response = SLS_MESSAGE(SLS_TYPE_HANDSHAKE, connection)
    hs_msg = MSLS_HANDSHAKE_MESSAGE(MSLS_HS_SERVER_KEYX, connection)
    connection["server_key"] = ""
    for i in range(0, 128*4, 4):
      first_byte = unpack("<I", self.magic_page[PUBLIC_KEY_BASE1_OFFSET + i: PUBLIC_KEY_BASE1_OFFSET + i + 4])[0]
      second_byte = unpack("<I", self.magic_page[PUBLIC_KEY_BASE2_OFFSET + i: PUBLIC_KEY_BASE2_OFFSET + i + 4])[0]
      connection["server_key"] += pack("<I", first_byte ^ second_byte)
    hs_msg.add_to_message(connection["server_key"], 0)
    response.add_message(hs_msg)
    r = response.to_string()
    self.read(length=len(r), expect=r)

    # Read Hello Done
    connection["sequence_num"] = 3
    response = SLS_MESSAGE(SLS_TYPE_HANDSHAKE, connection)
    hs_msg = MSLS_HANDSHAKE_MESSAGE(MSLS_HS_SERVER_DONE, connection)
    response.add_message(hs_msg)
    r = response.to_string()
    self.read(length=len(r), expect=r)

  def client_keyx(self, connection):
    connection["sequence_num"] = 4
    request = SLS_MESSAGE(SLS_TYPE_HANDSHAKE, connection)
    hs_msg = MSLS_HANDSHAKE_MESSAGE(MSLS_HS_CLIENTKEYX, connection)
    connection["client_key"] = "".join(random.choice(string.ascii_letters) for _ in range(128*4))
    connection["client_secret"] = "".join(random.choice(string.ascii_letters) for _ in range(128*4))
    hs_msg.add_to_message(connection["client_key"], 0)
    encrypted_secret = ""
    for i in range(0, 128*4, 4):
      secret_byte = unpack("<I", connection["server_key"][i:i+4])[0] 
      key_byte = unpack("<I", connection["client_secret"][i:i+4])[0]
      encrypted_secret += pack("<I", secret_byte ^ key_byte)
    hs_msg.add_to_message(encrypted_secret, 0)
    request.add_message(hs_msg)
    self.write(request.to_string())

  def hello_done(self, connection):
    connection["sequence_num"] = 5
    request = SLS_MESSAGE(SLS_TYPE_HANDSHAKE, connection)
    hs_msg = MSLS_HANDSHAKE_MESSAGE(MSLS_HS_CLIENT_DONE, connection)
    request.add_message(hs_msg)
    self.write(request.to_string())

    #read server finished
    connection["sequence_num"] = 6
    response = SLS_MESSAGE(SLS_TYPE_HANDSHAKE, connection)
    hs_msg = MSLS_HANDSHAKE_MESSAGE(MSLS_HS_FINISH, connection)
    connection["server_secret"] = ""
    for i in range(0, 128*4, 4):
      first_byte = unpack("<I", self.magic_page[SERVER_SECRET1_OFFSET + i: SERVER_SECRET1_OFFSET + i + 4])[0]
      second_byte = unpack("<I", self.magic_page[SERVER_SECRET2_OFFSET + i: SERVER_SECRET2_OFFSET + i + 4])[0]
      connection["server_secret"] += pack("<I", first_byte ^ second_byte)
    server_hash = ""
    for i in range(0, 128*4, 4):
      cookie = unpack("<I", connection["cookie"][i:i+4])[0]
      client_key = unpack("<I", connection["client_key"][i:i+4])[0]
      client_secret = unpack("<I", connection["client_secret"][i:i+4])[0]
      server_secret = unpack("<I", connection["server_secret"][i:i+4])[0]
      server_hash += pack("<I", cookie ^ client_key ^ client_secret ^ server_secret)
    hs_msg.add_to_message(server_hash, 0)
    response.add_message(hs_msg)
    r = response.to_string()
    self.read(length=len(r), expect=r)

  def changespec(self):
    
    if (len(self.state["connections"]) == 0):
      return
      
    connection = self.state["current_connection"] = random.choice(self.state["connections"])
 
    if (not connection["is_connected"]):
      return

    request = SLS_MESSAGE(SLS_TYPE_CHANGESPEC, connection)
    connection["cipher_suite"] = random.randint(0, 0xffff)
    cs_msg = MSLS_CHANGESPEC_MESSAGE(connection["cipher_suite"])
    request.add_message(cs_msg)
    self.write(request.to_string())

    connection["sequence_num"] += 1
    response = SLS_MESSAGE(SLS_TYPE_HANDSHAKE, connection)
    hs_msg = MSLS_HANDSHAKE_MESSAGE(MSLS_HS_SERVER_HELLO, connection)
    hs_msg.add_to_message(SLS_VERSION, 0)
    hs_msg.add_to_message(self.get_random(), 4)
    hs_msg.add_to_message(connection["cipher_suite"], 2)
    response.add_message(hs_msg)
    s = response.to_string()
    self.read(length=len(s), expect=s)




  def send_finished(self, connection):
    connection["sequence_num"] = 7
    request = SLS_MESSAGE(SLS_TYPE_HANDSHAKE, connection)
    hs_msg = MSLS_HANDSHAKE_MESSAGE(MSLS_HS_FINISH, connection)
    client_hash = ""
    for i in range(0, 128*4, 4):
      server_secret =  unpack("<I", connection["server_secret"][i:i+4])[0]
      server_key =  unpack("<I", connection["server_key"][i:i+4])[0]
      cookie = unpack("<I", connection["cookie"][i:i+4])[0]
      client_hash += pack("<I", server_secret ^ server_key ^ cookie)
    hs_msg.add_to_message(client_hash, 0)
    request.add_message(hs_msg)
    self.write(request.to_string())



