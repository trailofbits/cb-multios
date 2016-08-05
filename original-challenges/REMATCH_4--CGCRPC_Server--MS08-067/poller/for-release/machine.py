#!/usr/bin/env python

import random
import string
from struct import pack, unpack
import copy
from generator.actions import Actions


CGCMB_NEGOTIATE                  =  0x01
CGCMB_NEGOTIATE_RESPONSE         =  0xf1
CGCMB_SESSION_SETUP              =  0x02
CGCMB_SESSION_SETUP_RESPONSE     =  0xf2
CGCMB_TREE_CONNECT               =  0x03
CGCMB_TREE_CONNECT_RESPONSE      =  0xf3
CGCMB_TREE_DISCONNECT            =  0x04
CGCMB_TREE_DISCONNECT_RESPONSE   =  0xf4
CGCMB_FILE_CREATE                =  0x05
CGCMB_FILE_CREATE_RESPONSE       =  0xf5
CGCMB_FILE_CLOSE                 =  0x06
CGCMB_FILE_CLOSE_RESPONSE        =  0xf6
CGCMB_FILE_READ                  =  0x07
CGCMB_FILE_READ_RESPONSE         =  0xf7
CGCMB_FILE_WRITE                 =  0x08
CGCMB_FILE_WRITE_RESPONSE        =  0xf8
CGCMB_FILE_CANCEL                =  0x09
CGCMB_FILE_CANCEL_RESPONSE       =  0xf9
CGCMB_TRANSACTION                =  0x0a
CGCMB_TRANSACTION_RESPONSE       =  0xfa
CGCMB_ECHO                       =  0x0b
CGCMB_ECHO_RESPONSE              =  0xfb
CGCMB_END_SESSION                =  0x0c
CGCMB_END_SESSION_RESPONSE       =  0xfc
CGCMB_ERROR_RESPONSE             =  0xff

CGCMB_ERROR_FORMAT      = 0xe1
CGCMB_ERROR_LENGTH      = 0xe2
CGCMB_ERROR_STATE       = 0xe3
CGCMB_ERROR_ACCESS      = 0xe4 
CGCMB_ERROR_SESSION     = 0xe5
CGCMB_MESSAGE_TYPE      = 0xe6

MAX_CONNECTIONS   = 32

CGCRPC_SUCCESS          = 0
CGCRPC_FAILURE          = -1
CGCRPC_ERROR_FORMAT     = 2
CGCRPC_ERROR_COMMAND    = 4
CGCRPC_ERROR_NOT_FOUND  = 8
CGCRPC_ERROR_VERSION    = 10
MAX_CGCRPC_CONNECTIONS  = 10
MAX_CGCRPC_ENDPOINTS    = 10
MAX_CGCRPC_RESPONSE_SIZE = 2048
CGCRPC_BIND                   =  0xa0
CGCRPC_BIND_RESPONSE          =  0x0a
CGCRPC_WRITE_TO_PIPE          =  0xa1
CGCRPC_WRITE_TO_PIPE_RESPONSE = 0x1a


NETSTUFF_FILE_ENUM             = 0xb0
NETSTUFF_PATH_ENUM             = 0xb1
NETSTUFF_SERVICE_ENUM          = 0xb2
NETSTUFF_FIND_TREE             = 0xb3
NETSTUFF_FIND_FILE             = 0xb4
NETSTUFF_FILE_STAT             = 0xb5
NETSTUFF_FILE_CLOSE            = 0xb6
NETSTUFF_SESSION_ENUM          = 0xb7
NETSTUFF_SESSION_DEL           = 0xb8
NETSTUFF_CONNECTION_ENUM       = 0xb9
NETSTUFF_CONNECTION_DEL        = 0xba
NETSTUFF_NAME_CANONICALIZE     = 0xbb
NETSTUFF_NET_PATH_CANONICALIZE = 0xbc
NETSTUFF_PATH_COMPARE          = 0xbd
NETSTUFF_NAME_COMPARE          = 0xbe

NETSTUFF_PATH_CHAR  = "\xd0"
NETSTUFF_DIR_CHAR   = "\xd1"
NETSTUFF_SERVICE_CHAR =  "\xd2"
NETSTUFF_PATH_CHAR2     = "\xd3"

NETSTUFF_SUCCESS        = 0xe0
NETSTUFF_ERROR_COMMAND  = 0xe1
NETSTUFF_ERROR_FORMAT   = 0xe2
NETSTUFF_ERROR_NOT_FOUND  = 0xe3

class PRNG:
  def __init__(self, magic_page, generator):
    self.prng_offset = 0
    self.magic_page = magic_page
    self.random_state = []
    for i in range(512):
      self.random_state.append(unpack("<Q", magic_page[i*8: i*8 + 8])[0])
    self.a = 12
    self.b = 25 
    self.c = 27
    self.mult = unpack("<Q", magic_page[4:12])[0] 
    self.randomIndex = 0
    self.generator = generator

  def prng(self):
    r = self.random_state[self.randomIndex] 
    r = r ^ (r >> self.a) & 0xffffffffffffffff
    r = r ^ (r << self.b) & 0xffffffffffffffff
    r = r ^ (r >> self.c) & 0xffffffffffffffff
    self.random_state[self.randomIndex] = r & 0xffffffffffffffff
    self.randomIndex = (self.randomIndex + 1) % 512
    big = r * self.mult
    return ((big >> 32) & 0xffffffff)


  def random_in_range(self, min, max):
    if (min > max):
      return 0
    if (min == max):
      return min
    delta = max - min
    scale = 0xffffffff / delta
    value = self.prng()
    return min + (value / scale)


  def random_string(self, length):
    s = []
    for i in range(length - 1):
      s.append(pack("B", self.random_in_range(0x41, 0x71)))
    s.append('\0')
    return ''.join(s)


class FileSystem():
  MAX_FILENAME_LEN =  128
  MAX_TREENAME_LEN =  128
  MAX_SERVICE_NAME =  64
  MAX_SERVICE_TYPES=  5
  MAX_FILESIZE     =  1024
  MAX_TREES       =   10
  MAX_FILES_PER_TREE  = 10
  
  FS_MODE_CREATE  =   0x31
  FS_MODE_READ      = 0x32
  FS_MODE_OVERWRITE = 0x33
  FS_MODE_WRITE     = 0x34

  def __init__(self, prng):
    self.trees = []
    self.serviceTypes = []
    self.prng = prng
    self.specialTree = None
    for i in range(self.MAX_SERVICE_TYPES):
      self.serviceTypes.append(prng.random_string(prng.random_in_range(self.MAX_SERVICE_NAME/2, self.MAX_SERVICE_NAME)))

    treenamelen = prng.random_in_range(self.MAX_TREENAME_LEN/2, self.MAX_TREENAME_LEN)
    for i in range(self.MAX_TREES - 1):
      tree = {}
      tree["id"] = prng.prng() 

      tree["name"] = prng.random_string(treenamelen - i)
      
      tree["service"] = self.serviceTypes[prng.random_in_range(0, self.MAX_SERVICE_TYPES - 1)]
      tree["files"] = []
      
      numFiles = prng.random_in_range(1, self.MAX_FILES_PER_TREE);
      filenamelen = prng.random_in_range(self.MAX_FILENAME_LEN/2, self.MAX_FILENAME_LEN)
      while(numFiles > 0):
        filename = prng.random_string(filenamelen - numFiles)
        file = self.CreateInitialFile(filename)
        tree["files"].append(file)
        numFiles -= 1
      self.trees.append(tree)

    tree = {}
    tree["id"] = prng.prng() 
    tree["name"] = "SOMETREE"
    tree["service"] = "EYEPSEE"
    tree["files"] = []
    file = {}
    file["name"] = "NETSTUFF"
    file["id"] = self.prng.prng() & 0xffff
    file["isOpen"] = False
    tree["files"].append(file)

    self.specialTree = tree

  def CreateInitialFile(self, filename):
    file = {}
    file["name"] = filename
    file["id"] = self.prng.prng() & 0xffff
    length =  self.prng.random_in_range(10, self.MAX_FILESIZE)
    file["bytes"] =  self.prng.random_string(length)
    file["isOpen"] = False
    return file

  

class CGCMBMessage():
  def __init__(self, generator):
   
    self.generator = generator
    self.msg = ""
    self.command = 0
    self.data = []
    self.parameters = []
    self.status = 0
    self.flags = 0
    self.security = [0, 0, 0, 0, 0, 0, 0, 0]


  def AddParameter(self, parameter, length):
    if (length == 0):
      self.parameters.append(parameter)
    elif (length == 1):
      self.parameters.append(pack("<B", parameter))
    elif (length == 2):
      self.parameters.append(pack("<H", parameter))
    elif (length == 4):
      self.parameters.append(pack("<I", parameter))

  def AddData(self, data, length):
    if (length == 0):
      self.data.append(data)
    elif (length == 1):
      self.data.append(pack("<B", data))
    elif (length == 2):
      self.data.append(pack("<H", data))
    elif (length == 4):
      self.data.append(pack("<I", data))

  def Transmit(self):
    mbmessage = pack("<I", 0xC47C4D42) 
    mbmessage += pack("<B", self.command)
    mbmessage += pack("<B", self.status)
    mbmessage += pack("<B", self.flags)
    mbmessage += ''.join(pack("B", _) for _ in self.security)
    parameters = ''.join(self.parameters)
    mbmessage += pack("<H", len(parameters))
    if (len(parameters) > 0):
      mbmessage += parameters
    data = ''.join(self.data)
    mbmessage += pack("<H", len(data))
    if (len(data) > 0):
      mbmessage += data
    msg = pack("<B", 0) + pack("<I", len(mbmessage)) + mbmessage
    self.generator.write(msg)

  def Receive(self):
    mbmessage = pack("<I", 0xC47C4D42) 
    mbmessage += pack("<B", self.command)
    mbmessage += pack("<B", self.status)
    mbmessage += pack("<B", self.flags)
    mbmessage += ''.join(pack("B", _) for _ in self.security)
    parameters = ''.join(self.parameters)
    mbmessage += pack("<H", len(parameters))
    if (len(parameters) > 0):
      mbmessage += parameters
    data = ''.join(self.data)
    mbmessage += pack("<H", len(data))
    if (len(data) > 0):
      mbmessage += data
    msg = pack("<B", 0) + pack("<I", len(mbmessage)) + mbmessage
    self.generator.read(length=len(msg), expect=msg)

class NETSTUFF_Data():
  def __init__(self):
    self.data = []

  def AddData(self, data, length):
    if (length == 0):
      self.data.append(data)
    elif (length == 1):
      self.data.append(pack("<B", data))
    elif (length == 2):
      self.data.append(pack("<H", data))
    elif (length == 4):
      self.data.append(pack("<I", data))


  def GetData(self):
    return ''.join(self.data)

class CROMU_00095_Generator(Actions):
  
  def start(self):

    self.delay(50)
    self.state = "INITIAL"
    self.dialect = 0
    self.sessionKey = 0
    self.userID = 0
    self.connections = []
    self.prng = PRNG(self.magic_page, self)
    self.bindIDs = []
    self.fs = FileSystem(self.prng)


  def echo(self):
    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_ECHO
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_ECHO_RESPONSE
    randomString = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(5, 2048)))
    mbMessage.AddData(randomString, 0)
    mbResponse.AddData(randomString, 0)
    mbMessage.Transmit()
    mbResponse.Receive()

  def test(self):
    self.echo()

  def negotiate(self):
    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_NEGOTIATE
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_NEGOTIATE_RESPONSE
    if (self.chance() < 0.05):
      # Invalid negotiation
      self.state = "CLOSED"
      dialect = random.randint(0, 65535)
      while (dialect in [0x313e, 0x4155, 0x2671]):
        dialect = random.randint(0, 65535)
    else:
      #Valid negotiation
      self.state = "NEGOTIATE"
      dialect = random.choice([0x313e, 0x4155, 0x2671])
      self.dialect = dialect
      
    mbMessage.AddData(dialect, 2)
    mbMessage.Transmit()
    if (self.state == "NEGOTIATE"):
      self.sessionKey = self.prng.prng()
      mbResponse.AddData(self.sessionKey, 4)
      mbResponse.AddData(self.dialect, 2)
    mbResponse.Receive()

  def session(self):
    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_SESSION_SETUP
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_SESSION_SETUP_RESPONSE
    mbMessage.AddParameter(self.sessionKey, 4)
    password = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1, 32)))
    username = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1, 32)))
    mbMessage.AddParameter(len(password), 2)
    mbMessage.AddParameter(0, 4)
    mbMessage.AddData(password, 0)
    mbMessage.AddData(len(username), 2)
    mbMessage.AddData(username, 0)
    if (self.state != "NEGOTIATE"):
      mbResponse.command = CGCMB_ERROR_RESPONSE
      mbResponse.AddData(CGCMB_ERROR_STATE, 4)
      mbMessage.Transmit()
      mbResponse.Receive()
      return -1
    else:
      self.userID = 0xffff
      mbResponse.AddData(0xffff, 2)
      mbResponse.AddData(1, 1)
    mbMessage.Transmit()
    mbResponse.Receive()


  def tree_connect_known(self, tree):
    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_TREE_CONNECT
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_TREE_CONNECT_RESPONSE
    connection = {}
    connection["tree"] = tree
    password = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1, 32)))
    username = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1, 32)))
    mbMessage.AddParameter(self.sessionKey, 4)
    mbMessage.AddParameter(self.userID, 2)
    mbMessage.AddData(len(password), 2)
    mbMessage.AddData(password, 0)
    mbMessage.AddData(len(connection["tree"]["name"]), 2)
    mbMessage.AddData(connection["tree"]["name"], 0)
    mbMessage.AddData(len(connection["tree"]["service"]), 2)
    mbMessage.AddData(connection["tree"]["service"], 0)
    mbMessage.Transmit()
    
    connection["id"] = self.prng.prng()
    self.connections.append(connection)
    
    mbResponse.AddParameter(self.sessionKey, 4)
    mbResponse.AddParameter(self.userID, 2)
    mbResponse.AddData(connection["id"], 4)
    mbResponse.Receive()
    return connection

  def tree_connect(self):

    if (len(self.connections) >= MAX_CONNECTIONS):
      mbMessage = CGCMBMessage(self)
      mbMessage.command = CGCMB_TREE_CONNECT
      mbResponse = CGCMBMessage(self)
      mbResponse.command = CGCMB_TREE_CONNECT_RESPONSE
      mbResponse.command = CGCMB_ERROR_RESPONSE
      mbResponse.AddData(CGCMB_ERROR_FULL)
      mbMessage.Transmit()
      mbResponse.Receive()
      return -1
    
    tree = random.choice(self.fs.trees)
    self.tree_connect_known(tree)


  def tree_disconnect(self):
    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_TREE_DISCONNECT
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_TREE_DISCONNECT_RESPONSE
    if (len(self.connections) == 0):
      mbMessage.AddParameter(self.sessionKey, 4)
      mbMessage.AddParameter(self.userID, 2)
      mbMessage.AddData(random.randint(), 4)
      mbResponse.command = CGCMB_ERROR_RESPONSE
      mbResponse.AddData(CGCMB_ERROR_NOT_FOUND)
      mbMessage.Transmit()
      mbResponse.Receive()
    else:
      connection = self.connections.pop()
      mbMessage.AddParameter(self.sessionKey, 4)
      mbMessage.AddParameter(self.userID, 2)
      mbMessage.AddParameter(connection["id"], 4)
      mbResponse.AddParameter(self.sessionKey, 4)
      mbResponse.AddParameter(self.userID, 2)
      mbResponse.AddParameter(connection["id"], 4)
      mbMessage.Transmit()
      mbResponse.Receive()

  def file_write(self):
    if (len(self.connections) == 0):
      return
    connection = random.choice(self.connections)
    if (len(connection["tree"]["files"]) >= self.fs.MAX_FILES_PER_TREE):
      return
    filename = username = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1, 32)))
    file = {}
    file["name"] = filename
    
    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_FILE_CREATE
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_FILE_CREATE_RESPONSE
    mbMessage.AddParameter(self.sessionKey, 4)
    mbMessage.AddParameter(self.userID, 2)
    mbMessage.AddParameter(connection["id"], 4)
    mbMessage.AddParameter(self.fs.FS_MODE_CREATE, 4)
    mbMessage.AddData(len(filename), 2)
    mbMessage.AddData(filename, 0)
    mbMessage.Transmit()

    file["id"] = self.prng.prng() & 0xffff
    length =  random.randint(10, self.fs.MAX_FILESIZE)
    file["bytes"] =  ''.join(random.choice(string.ascii_letters) for _ in range(length))
    connection["tree"]["files"].append(file)
    mbResponse.AddParameter(self.sessionKey, 4)
    mbResponse.AddParameter(self.userID, 2)
    mbResponse.AddParameter(connection["id"], 4)
    mbResponse.AddParameter(file["id"], 2)
    mbResponse.Receive()
    
  

    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_FILE_WRITE
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_FILE_WRITE_RESPONSE
    mbMessage.AddParameter(self.sessionKey, 4)
    mbMessage.AddParameter(self.userID, 2)
    mbMessage.AddParameter(connection["id"], 4)
    mbMessage.AddParameter(file["id"], 2)
    mbMessage.AddParameter(0, 1)
    mbMessage.AddData(length, 2)
    mbMessage.AddData(0, 4)
    mbMessage.AddData(file["bytes"], 0)
    mbResponse.AddParameter(self.sessionKey, 4)
    mbResponse.AddParameter(self.userID, 2)
    mbResponse.AddParameter(connection["id"], 4)
    mbResponse.AddParameter(file["id"], 2)
    mbMessage.Transmit()
    mbResponse.Receive()

    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_FILE_CLOSE
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_FILE_CLOSE_RESPONSE
    mbMessage.AddParameter(self.sessionKey, 4)
    mbMessage.AddParameter(self.userID, 2)
    mbMessage.AddParameter(connection["id"], 4)
    mbMessage.AddParameter(file["id"], 2)
    mbResponse.AddParameter(self.sessionKey, 4)
    mbResponse.AddParameter(self.userID, 2)
    mbResponse.AddParameter(connection["id"], 4)
    mbResponse.AddParameter(file["id"], 2)
    mbMessage.Transmit()

    mbResponse.Receive()

  def file_read(self):
    if (len(self.connections) == 0):
      return
    connection = random.choice(self.connections)
    if (len(connection["tree"]["files"]) == 0):
      return
    file = random.choice(connection["tree"]["files"])
    
    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_FILE_CREATE
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_FILE_CREATE_RESPONSE
    mbMessage.AddParameter(self.sessionKey, 4)
    mbMessage.AddParameter(self.userID, 2)
    mbMessage.AddParameter(connection["id"], 4)
    mbMessage.AddParameter(self.fs.FS_MODE_READ, 4)
    mbMessage.AddData(len(file["name"]), 2)
    mbMessage.AddData(file["name"], 0)
    mbResponse.AddParameter(self.sessionKey, 4)
    mbResponse.AddParameter(self.userID, 2)
    mbResponse.AddParameter(connection["id"], 4)
    mbResponse.AddParameter(file["id"], 2)
    mbMessage.Transmit()

    mbResponse.Receive()
  

    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_FILE_READ
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_FILE_READ_RESPONSE
    mbMessage.AddParameter(self.sessionKey, 4)
    mbMessage.AddParameter(self.userID, 2)
    mbMessage.AddParameter(connection["id"], 4)
    mbMessage.AddParameter(file["id"], 2)
    mbMessage.AddData(len(file["bytes"]), 2)
    mbMessage.AddData(0, 4)
    mbResponse.AddParameter(self.sessionKey, 4)
    mbResponse.AddParameter(self.userID, 2)
    mbResponse.AddParameter(connection["id"], 4)
    mbResponse.AddParameter(len(file["bytes"]), 2)
    mbResponse.AddData(file["bytes"], 0)
    mbMessage.Transmit()
    mbResponse.Receive()

    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_FILE_CLOSE
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_FILE_CLOSE_RESPONSE
    mbMessage.AddParameter(self.sessionKey, 4)
    mbMessage.AddParameter(self.userID, 2)
    mbMessage.AddParameter(connection["id"], 4)
    mbMessage.AddParameter(file["id"], 2)
    mbResponse.AddParameter(self.sessionKey, 4)
    mbResponse.AddParameter(self.userID, 2)
    mbResponse.AddParameter(connection["id"], 4)
    mbResponse.AddParameter(file["id"], 2)
    mbMessage.Transmit()
    mbResponse.Receive()

  def transaction_bind(self):
    if (len(self.connections) >= MAX_CONNECTIONS):
      mbMessage = CGCMBMessage(self)
      mbMessage.command = CGCMB_TREE_CONNECT
      mbResponse = CGCMBMessage(self)
      mbResponse.command = CGCMB_TREE_CONNECT_RESPONSE
      mbResponse.command = CGCMB_ERROR_RESPONSE
      mbResponse.AddData(CGCMB_ERROR_FULL)
      mbMessage.Transmit()
      mbResponse.Receive()
      return -1
    
    connection = self.tree_connect_known(self.fs.specialTree)
    file = connection["tree"]["files"][0]
    
    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_FILE_CREATE
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_FILE_CREATE_RESPONSE
    mbMessage.AddParameter(self.sessionKey, 4)
    mbMessage.AddParameter(self.userID, 2)
    mbMessage.AddParameter(connection["id"], 4)
    mbMessage.AddParameter(self.fs.FS_MODE_READ, 4)
    mbMessage.AddData(len(file["name"]), 2)
    mbMessage.AddData(file["name"], 0)
    mbResponse.AddParameter(self.sessionKey, 4)
    mbResponse.AddParameter(self.userID, 2)
    mbResponse.AddParameter(connection["id"], 4)
    mbResponse.AddParameter(file["id"], 2)
    mbMessage.Transmit()

    mbResponse.Receive()
  


    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_TRANSACTION
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_TRANSACTION_RESPONSE
    mbMessage.AddParameter(self.sessionKey, 4)
    mbMessage.AddParameter(self.userID, 2)
    mbMessage.AddParameter(connection["id"], 4)
    mbMessage.AddParameter(file["id"], 2)
    mbMessage.AddData(CGCRPC_BIND, 2)
    mbMessage.AddData(len(file["name"]), 2)
    mbMessage.AddData(file["name"], 0)
    mbMessage.AddData(0xDC, 2)
    mbMessage.Transmit()
    
    bindID = self.prng.random_in_range(1, 0xffffffff)
    self.bindIDs.append((bindID, connection))

    mbResponse.AddParameter(self.sessionKey, 4)
    mbResponse.AddParameter(self.userID, 2)
    mbResponse.AddParameter(connection["id"], 4)
    mbResponse.AddParameter(CGCRPC_SUCCESS, 1)
    mbResponse.AddData(CGCRPC_BIND_RESPONSE, 2)
    mbResponse.AddData(CGCRPC_SUCCESS, 1)
    mbResponse.AddData(bindID, 4)
    mbResponse.Receive()

  def transaction_msg(self, opcode, sendbytes, returnbytes):

    (bindID, connection) = random.choice(self.bindIDs)
    file = connection["tree"]["files"][0]
    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_TRANSACTION
    mbResponse = CGCMBMessage(self)
    mbResponse.command = CGCMB_TRANSACTION_RESPONSE
    mbMessage.AddParameter(self.sessionKey, 4)
    mbMessage.AddParameter(self.userID, 2)
    mbMessage.AddParameter(connection["id"], 4)
    mbMessage.AddParameter(file["id"], 2)
    mbMessage.AddData(CGCRPC_WRITE_TO_PIPE, 2)
    mbMessage.AddData(bindID, 4)

    mbMessage.AddData(opcode, 2)
    mbMessage.AddData(len(sendbytes), 2)
    if (len(sendbytes) > 0):
      mbMessage.AddData(sendbytes, 0)

    mbResponse.AddParameter(self.sessionKey, 4)
    mbResponse.AddParameter(self.userID, 2)
    mbResponse.AddParameter(connection["id"], 4)
    mbResponse.AddParameter(CGCRPC_SUCCESS, 1)
    mbResponse.AddData(CGCRPC_WRITE_TO_PIPE_RESPONSE, 2)
    mbResponse.AddData(bindID, 4)
    mbResponse.AddData(len(returnbytes), 2)
    if (len(returnbytes) > 0):
      mbResponse.AddData(returnbytes, 0)
    
    mbMessage.Transmit()
    mbResponse.Receive()


  def netstuff_service_enum(self):
    opcode = NETSTUFF_SERVICE_ENUM
    response = NETSTUFF_Data()
    response.AddData(5, 2)
    response.AddData(''.join(self.fs.serviceTypes), 0)
    response.AddData(NETSTUFF_SUCCESS, 2)
    self.transaction_msg(opcode, "", response.GetData())

  def netstuff_file_stat(self):
    opcode = NETSTUFF_FILE_STAT
    tree = random.choice(self.fs.trees)
    file = random.choice(tree["files"])
    sendbytes = tree["service"].strip("\x00") +  NETSTUFF_SERVICE_CHAR + tree["name"].strip("\x00") +  NETSTUFF_PATH_CHAR + file["name"]
    response = NETSTUFF_Data()
    response.AddData(file["id"], 2)
    response.AddData(len(file["bytes"]), 2)
    response.AddData(0, 1)
    response.AddData(NETSTUFF_SUCCESS, 2)
    self.transaction_msg(opcode, sendbytes, response.GetData())


  def netstuff_canon_path(self):
    opcode = NETSTUFF_NET_PATH_CANONICALIZE
    tree = random.choice(self.fs.trees)
    file = random.choice(tree["files"])

    #sendbytes = 'A' * 500
    #while (len(sendbytes) > 428):
    tree = random.choice(self.fs.trees)
    file = random.choice(tree["files"])
    sendbytes = tree["service"].strip("\x00") + NETSTUFF_SERVICE_CHAR
    if (self.chance() < 0.3):
      sendbytes += ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1, 32)))
      sendbytes += NETSTUFF_PATH_CHAR + NETSTUFF_DIR_CHAR + NETSTUFF_PATH_CHAR2
    sendbytes += tree["name"].strip("\x00") + random.choice([NETSTUFF_PATH_CHAR2, NETSTUFF_PATH_CHAR])
    if (self.chance() < 0.3):
      sendbytes += ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1, 32)))
      sendbytes += random.choice([NETSTUFF_PATH_CHAR2, NETSTUFF_PATH_CHAR]) + NETSTUFF_DIR_CHAR + random.choice([NETSTUFF_PATH_CHAR2, NETSTUFF_PATH_CHAR])
    sendbytes += file["name"].strip("\x00")
    response = NETSTUFF_Data()
    response.AddData(tree["service"].strip("\x00"), 0)
    response.AddData(tree["service"].strip("\x00"), 0)
    response.AddData(NETSTUFF_SERVICE_CHAR, 0)
    response.AddData(tree["name"].strip("\x00") + NETSTUFF_PATH_CHAR + file["name"].strip("\x00"), 0)
    response.AddData(NETSTUFF_SUCCESS, 2)
    self.transaction_msg(opcode, sendbytes, response.GetData())


  def exit(self):
    mbMessage = CGCMBMessage(self)
    mbMessage.command = CGCMB_END_SESSION
    mbMessage.Transmit()
    mbMessage.command = CGCMB_END_SESSION_RESPONSE
    mbMessage.Receive()
    
