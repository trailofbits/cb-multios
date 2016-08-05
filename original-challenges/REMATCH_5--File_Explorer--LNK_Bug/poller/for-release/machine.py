#!/usr/bin/env python

import random
import string
from struct import pack, unpack
from generator.actions import Actions

FILE_TEXT               = 0xf1
FILE_EXECUTABLE         = 0xf2
FILE_IMAGE              = 0xf3
FILE_LINK               = 0xf4
FILE_RAW                = 0xf5
FILE_LIBRARY            = 0xf6
FILE_DIRECTORY          = 0xf7
FILE_INVALID            = 0xf8 


MAX_FILE_SIZE           = 2048
MAX_FILESYSTEM_DEPTH    = 10
MAX_FILES_IN_SYSTEM     = 256

FS_SUCCESS              =  0
FS_ERROR_INVALID_INPUT  = -1
FS_ERROR_FILE_NOT_FOUND = -2
FS_ERROR_DUPLICATE_NAME = -3
FS_ERROR_ACCESS_DENIED  = -4
FS_ERROR_FS_FULL        = -5

UPLOAD_A_FILE   = 'u'
READ_A_FILE     = 'r'
DELETE_A_FILE   = 'd'
LIST_FILES      = 'l'
LIST_FILES_LONG = 'g'
CREATE_DIR      = 'c'
MOVE_FILE       = 'm'
PWD             = 'w'
CHANGE_DIR      = 'h'
EXIT_CMD        = 'x'

EXECUTABLE_FILE_MAGIC =0xC67CC76C
EXECUTABLE_TYPE_LIBRARY     =0xe1
EXECUTABLE_TYPE_EXECUTABLE  =0xe2
OPCODE_READ_MEM   =0x37  
OPCODE_WRITE_MEM  =0x38
OPCODE_WRITE_REG  =0x39
OPCODE_EXIT       =0x40

SHORTCUT_MAGIC = 0x4c494e4b

class FileNode():

    def __init__(self, name, type, contents, fileID):
      self.name = name
      self.type = type
      if (type != FILE_DIRECTORY):
        self.contents = contents
      else:
        self.contents = ""
      self.next = None
      self.prev = None
      self.child = None
      self.parent = None
      self.fileID = fileID


class FileSystem():

  file_types = [FILE_TEXT, FILE_EXECUTABLE, FILE_IMAGE, FILE_LINK, FILE_RAW, FILE_LIBRARY, FILE_DIRECTORY]
  FLAVOR_SL_FILE = '/\x02\x00\x00l\xc7|\xc6\xe1\x01\x00\x15\x00\x07\x00[\x00\x06\x00)\x02SharedLibraryMain\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00)\x02\x00\x00\x00\x00This is a text file\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00This is an executable\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00This is an image\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00This is a link\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00This file is raw\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00This is a shared library\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00This is a directory\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x007\xa0\x80\x04\x08@'
  

  def __init__(self, magic_page):
    self.fileIdIndex = 0
    self.magic_page = magic_page
    self.root = FileNode("root", FILE_DIRECTORY, "", 0)
    self.cwd = self.root
    self.numFiles = 1
    self.allFiles = []
    self.currentFile = None

    user = FileNode("User", FILE_DIRECTORY, "", self.getNextFileID())
    documents = FileNode("Documents", FILE_DIRECTORY, "", self.getNextFileID())
    self.root.child = documents
    documents.parent = self.root
    system = FileNode("System", FILE_DIRECTORY, "", self.getNextFileID())
    documents.next = system
    system.prev = documents
    system.parent = self.root
    
    system.next = user
    user.prev = system
    user.parent = self.root
    special = FileNode("Special", FILE_DIRECTORY, "", self.getNextFileID())
    special.parent = system
    system.child = special
    flavor = FileNode("Flavor.sl", FILE_LIBRARY, self.FLAVOR_SL_FILE, self.getNextFileID())
    flavor.resources = ["This is a text file",
        "This is an executable",
        "This is an image",
        "This is a link", 
        "This file is raw", 
        "This is a shared library",
        "This is a directory"]
    flavor.parent = special
    special.child = flavor
    self.reservedFiles = ["System", "Special", "Flavor.sl", "root"]
    self.resourceDefault = flavor

  def getNextFileID(self):
    fileId = unpack("<H", self.magic_page[self.fileIdIndex:self.fileIdIndex+2])[0]
    self.fileIdIndex += 2
    if (self.fileIdIndex >= 4096):
      self.fileIdIndex = 0
    return (fileId & 0xff)

  def CreateFile(self, name, type, contents, parent):
    newNode = FileNode(name, type, contents, self.getNextFileID())
    self.numFiles += 1
    newNode.parent = parent
    prev = parent.child
    self.allFiles.append(newNode)
    self.currentFile = newNode
    if (prev == None):
      parent.child = newNode
      return FS_SUCCESS
    while (prev != None):
      if (name == prev.name):
        self.allFiles.remove(newNode)
        return FS_ERROR_DUPLICATE_NAME
      if (name < prev.name):
        #Insert here
        if (prev.prev == None):
          #First in Directory
          newNode.next = prev
          prev.prev = newNode
          parent.child = newNode
          return FS_SUCCESS
        else:
          newNode.next = prev
          newNode.prev = prev.prev
          prev.prev.next = newNode
          newNode.next.prev = newNode
          return FS_SUCCESS
      else:
        #Keep looking
        last = prev
        prev = prev.next

    last.next = newNode
    newNode.prev = last
    return FS_SUCCESS

  def pickAFile(self):
    if (len(self.allFiles) > 0):
      return random.choice(self.allFiles)
    else:
      return None

  def pickAResourceFile(self):
    resourceFiles = [self.resourceDefault]
    for file in self.allFiles:
      if (file.type == FILE_LIBRARY):
        resourceFiles.append(file)
    return random.choice(resourceFiles)

  def Delete(self, file):
    #remove links
    if (file.parent.child == file):
      file.parent.child = file.next
    if (file.prev):
      file.prev.next = file.next
    if (file.next):
      file.next.prev = file.prev

    file.prev = None
    file.next = None
    
    self.RemoveNode(file)

  def RemoveNode(self, file):
    if (file):
      self.numFiles -= 1
      self.RemoveNode(file.child)
      self.RemoveNode(file.next)
      if (file in self.allFiles):
        self.allFiles.remove(file)

  def ListFiles(self):
    output = ""
    output = self.ListFilesRecurse(output, self.cwd, 0)

    return output

  def ListFilesRecurse(self, output, file, level):
    if (file):
      output += " " * level * 4
      output += "%s (%d)\n" % (file.name, file.fileID)
      output += self.ListFilesRecurse("", file.child, level + 1)
      output += self.ListFilesRecurse("", file.next, level)
    return output

  def ListFilesLong(self):
    output = ""
    file = self.cwd.child
    while (file):
      flavorText = self.resourceDefault.resources[file.type - FILE_TEXT]
      if (file.type == FILE_LINK):
        resourceFile = self.GetFile(file.resourceName)
        if (resourceFile == self.resourceDefault):
          flavorText = resourceFile.resources[file.resourceIndex]
          
      output += "%s \t%d\t%s\n" % (file.name, len(file.contents), flavorText)
      file = file.next
    return output

  def ChangeDirectory(self):
    possible = ["upone"]
    next = self.cwd.child
    while (next):
      if ((next.type == FILE_DIRECTORY) and (next.name != "System")):
        possible.append(next)
      next = next.next
    newDir = random.choice(possible)
    if (newDir == "upone"):
      if (self.cwd != self.root):
        self.cwd = self.cwd.parent
    else:
      self.cwd = newDir
    
    self.allFiles = []
    file = self.cwd.child
    while (file != None):
      if (file.name not in self.reservedFiles):
        self.allFiles.append(file)
      file = file.next
    
    return newDir

  def GetFile(self, name):
    if (name == "System%Special%Flavor.sl"):
      return self.resourceDefault
    for each in self.allFiles:
      if each.name == name:
        return each
    return None 

  def pwd(self):
    walk = []
    output = ""
    node = self.cwd.parent
    while (node):
      walk.append(node)
      node = node.parent
    while (len(walk) > 0):
      node = walk.pop()
      output += node.name + "%"
    output += self.cwd.name
    return output


class CROMU_00096_Generator(Actions):
  
 
  def start(self):
    self.delay(50)
    self.commands = 0
    self.fs = FileSystem(self.magic_page)
    
  def menu(self):
    self.read(length=1, expect=">")

    if (self.commands > 20):
      self.exit()
      return -1

  def randomString(self, min, max):
    s = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(min, max)))
    return s

  def writeCString(self, s):
    if ((s != None) and (len(s)>0)):
      self.write(pack("<H", len(s)))
      self.write(s)
    else:
      self.write(pack("<H", 0))

  def cwd(self):
    self.write(PWD+'\n')
    output = self.fs.pwd()
    self.read(length=len(output) + 1, expect=output + "\n")

  def UploadFile(self):
    self.write(UPLOAD_A_FILE + '\n')
    type = random.choice(self.fs.file_types)
    if (type == FILE_LIBRARY):
      name = self.randomString(1, 61) + ".sl"
      (contents, resources) = self.BuildLibraryFile(name)
    elif (type == FILE_LINK):
      name = self.randomString(1, 61) + ".lk"
      resourceFile = self.fs.pickAResourceFile()
      if (resourceFile):
        if (resourceFile == self.fs.resourceDefault):
          resourceName = "System%Special%Flavor.sl"
        else:
          resourceName = resourceFile.name
        resourceIndex = random.randint(0, len(resourceFile.resources) - 1)
      else:
        resourceName = self.randomString(1, 61) + ".sl"
        resourceIndex = 0
      contents = self.BuildShortcutFile(resourceName, resourceIndex)
    else:
      contents = self.randomString(1, 2048)
      name = self.randomString(1, 64)
   
    if (name in self.fs.reservedFiles):
      name = "A" + name
    self.writeCString(name)
    self.write(pack("<B", type))
    self.writeCString(contents)
    if self.fs.CreateFile(name, type, contents, self.fs.cwd) != FS_SUCCESS:
      self.read(delim='\n', expect="FAILED")

    file = self.fs.GetFile(name)
    if (file.type == FILE_LIBRARY):
      file.resources = resources
    elif (file.type == FILE_LINK):
      file.resourceIndex = resourceIndex
      file.resourceName = resourceName

  def ReadAFile(self):
    file = self.fs.pickAFile()
    if (file == None):
      self.write("\n\n")
      self.read(delim='\n', expect="Invalid Command\n")
      return 

    self.write(READ_A_FILE + "\n")
    self.writeCString(file.name)
    output = file.contents.split('\x00')[0] + '\n'
    self.read(length=len(output), expect=output)


  def DeleteAFile(self):
    file = self.fs.pickAFile()
    if (file == None):
      self.write("\n\n")
      self.read(delim='\n', expect="Invalid Command\n")
      return

    self.write(DELETE_A_FILE + '\n')
    self.writeCString(file.name)

    self.fs.Delete(file)

  def ListFiles(self):
    self.write(LIST_FILES + '\n')
    fileList = self.fs.ListFiles()
    self.read(length=len(fileList), expect=fileList)


  def CreateDir(self):
    self.write(CREATE_DIR + '\n')
    name = self.randomString(1, 64)
    type = FILE_DIRECTORY
    self.writeCString(name)
    if self.fs.CreateFile(name, type, "", self.fs.cwd) != FS_SUCCESS:
      self.read(delim='\n', expect="FAILED")

  def ChangeDir(self):
    newDir = self.fs.ChangeDirectory()
    self.write(CHANGE_DIR + '\n')
    if (newDir == "upone"):
      self.writeCString("upone")
    else:
      self.writeCString(newDir.name)

  def ListFilesLong(self):
    self.write(LIST_FILES_LONG + '\n')
    fileList = self.fs.ListFilesLong()
    if (len(fileList) > 0):
      self.read(length=len(fileList), expect=fileList)


  def padString(self, s, length):
    if (len(s) > length):
      return s[0:length]
    return s + '\x00' * (length - len(s))

  def BuildShortcutFile(self, targetName, index):
    file = pack("<I", 0x4c494e4b)
    file += self.padString(targetName, 65)
    file += pack("<I", index)
    file = pack("<I", 4 + len(file)) + file
    return file

  def BuildLibraryFile(self, name):
    functions = "\x37\xa0\x80\x04\x08\x40"
    header = pack("<I", 0xC67CC76C) #magic
    header += pack("<B", 0xe1) #type
    header += pack("<H", 1) #func count
    header += pack("<H", 21) #func table offset
    numResources = random.randint(1, 10)
    header += pack("<H", numResources) #resource count
    header += pack("<H", 21 + 1*(64+2+4)) #resource offset
    header += pack("<H", len(functions)) #functionssize
    header += pack("<H", 21 + 1*(64+2+4) + numResources*(2+64)) #functions offset

    functionTable = self.padString("SharedLibraryMain", 64)
    functionTable += "\x00\x00"
    functionTable += pack("<I", 21 + 1*(64+2+4) + numResources*(2+64)) 

    resourceTable = ""
    resources = []
    for num in range(numResources):
      resource = ''.join(random.choice(string.ascii_letters) for _ in range(random.randint(1, 64)))
      resources.append(resource)
      resourceTable += "\x00\x00" + self.padString(resource, 64)

    file = pack("<I", 4 + len(header) + len(functionTable) + len(resourceTable) + len(functions))
    file += header + functionTable + resourceTable + functions

    return (file, resources)

  def exit(self):
    self.write(EXIT_CMD + "\n")
    self.read(length=1, expect='\n')




