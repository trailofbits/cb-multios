#!/usr/bin/env python

from generator.actions import Actions
import random
import string
from struct import pack, unpack, unpack_from


class FileSystemTest(Actions):

    def start(self):

        #self.delay(100)
        self.securityID = 0
        self.userName = ''
        self.totalSize = 8192*300        
        self.blockSize = 8192

        self.totalBlocks = self.totalSize / self.blockSize

        self.freeBlocks = 0
        self.maxBlocksPerFile = (self.blockSize - 8) / 4
        self.maxDirEntries = 127
        self.maxOpenFiles = 10

        self.rootDir = []
        self.rootDirFileCount = 0

        self.fileData = []

        self.fileHandles = []

        for i in range(0, self.maxOpenFiles+1):
            self.fileHandles.append(-1)

        for i in range (0, self.maxDirEntries):
            # filename, size, type, in-use flag, owner-ID, other-perms, owner-name
            self.rootDir.append(["", 0, 0, 0, 0, 0, ''])
            # contents, readPos, writePos
            self.fileData.append(['', 0, 0])

        self.rootDir[0] = ['README.txt', 138, 2, 1, 0, 3, '       ']
        self.rootDir[1] = ['authentication.db', 4096, 4, 1, 0, 0, '       ']
        self.rootDirFileCount = 1

        self.fileData[0][0] = 'Welcome to the interactive filesystem shell. Valid commands are make, makememfile, erase, list, copy, write, show, first, last, and perms.'


    def top(self):

        pass

    def unauthed(self):

        self.read( length = 7, expect = 'login: ')

    def authed(self):

        self.read( length = 2, expect = '> ')

    def bad_auth(self):


        userName = ''.join(random.choice(string.ascii_lowercase) for _ in range(7))
        userToken = random.randint(0, 0xffff)

        message = '{} {}\n'.format(userName, userToken)

        self.write(message)

        self.read(delim = '\n', expect = "Invalid login\n")


    def authenticate(self):

        userNumber = random.randint(0, 127)

        offset = userNumber * 32
        userName = ''

        for x in range(0, 7):
            value = (ord(self.magic_page[offset+x]) % 26) + ord('a')
            userName = userName + chr(value)

        token = 0

        for x in range(14, 28):
            token = token + ord(self.magic_page[offset+x])

        message = '{} {}\n'.format(userName, token)

        self.write(message)

        self.securityID = unpack('i', self.magic_page[offset+28:offset+32])[0]

        self.securityID = self.securityID & 0x7fffffff

        self.userName = userName

        self.read(delim = '\n', expect = 'Access allowed\n')
        self.read(delim = '\n', expect = 'Welcome {}\n'.format(userName))


    def logout(self):

        self.write('logout\n')

        self.read(delim = '\n', expect = 'bye felicia\n')



    def create_file(self):


        length = random.randint(5, 19)
        filename = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        message = 'make ' + filename + '\n'
        self.write(message)

        # first make sure the file doesn't already exist
        for i in range(0, self.maxDirEntries):
            if self.rootDir[i][0] == filename:

                expect_string = 'file {} already exists\n'.format(filename)
                self.read(delim = '\n', expect = expect_string)
                return

        #it doesn't so find the first empty slot in the directory
        slotFound = False

        for i in range(0, self.maxDirEntries):
            if len(self.rootDir[i][0]) == 0:
                self.rootDir[i] = [filename, 0, 2, 1, self.securityID, 0, self.userName]
                slotFound = True
                self.rootDirFileCount = self.rootDirFileCount + 1
                break

        if slotFound == False:
            expect_string = 'error\n'
            self.read(delim = '\n', expect = expect_string)
            return            
           

    def set_perms(self):


        if self.rootDirFileCount == 0:
            self.write('\n')
            return

        fileChoice = random.randint(0, self.rootDirFileCount-1) 

        count = 0

        for x in range(0, self.maxDirEntries):
            if len(self.rootDir[x][0]) > 0:

                if count == fileChoice:
                    break

                count = count + 1

        message = 'perms ' + self.rootDir[x][0] + ' '

        perms = random.choice([0, 1, 2, 3])

        message = message + '{}\n'.format(perms) 
        self.write(message)

        if self.rootDir[x][4] == self.securityID:

            self.rootDir[x][5] = perms
        else:

            self.read(delim = '\n', expect = 'permission denied\n')


    def delete_file(self):

        if self.rootDirFileCount == 0:
            self.write('\n')
            return

        fileChoice = random.randint(0, self.rootDirFileCount-1) 

        count = 0

        for x in range(0, self.maxDirEntries):
            if len(self.rootDir[x][0]) > 0:

                if count == fileChoice:
                    break

                count = count + 1

        message = 'erase ' + self.rootDir[x][0] + '\n'

        self.write(message)

        if self.securityID != self.rootDir[x][4]:

            if self.rootDir[x][5] > 0 and self.rootDir[x][5]& 0x01 == 0:

                self.read(delim = '\n', expect = 'error erasing {}\n'.format(self.rootDir[x][0]))
                return

            elif self.rootDir[x][5] == 0:

                self.read(delim = '\n', expect = 'permission denied\n')
                return


        self.rootDir[x] = ["", 0, 0, 0, 0, 0]

        self.fileData[x] = ['', 0, 0]

        self.rootDirFileCount = self.rootDirFileCount - 1


    def write_file(self):

        if self.rootDirFileCount == 0:
            self.write('\n')
            return

        fileChoice = random.randint(0, self.rootDirFileCount-1) 

        count = 0

        for x in range(0, self.maxDirEntries):
            if len(self.rootDir[x][0]) > 0:

                if count == fileChoice:
                    break

                count = count + 1

        message = 'write ' + self.rootDir[x][0] + '\n'

        self.write(message)

        # if we don't have permissions to write, get an error message

        if self.securityID != self.rootDir[x][4]:

            if self.rootDir[x][5] > 0 and self.rootDir[x][5]& 0x01 == 0:

                self.read(delim = '\n', expect = 'permission denied for write\n')
                return

            elif self.rootDir[x][5] == 0:

                self.read(delim = '\n', expect = 'permission denied\n')
                return


        length = random.randint(5, 100)
        filedata = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        self.write(filedata + '\n\n')

        self.fileData[x][0] = filedata

        self.rootDir[x][1] = length

     

    def read_file(self):

        if self.rootDirFileCount == 0:
            self.write('\n')
            return

        fileChoice = random.randint(0, self.rootDirFileCount-1) 

        count = 0

        for x in range(0, self.maxDirEntries):
            if len(self.rootDir[x][0]) > 0:

                if count == fileChoice:
                    break

                count = count + 1


        message = 'show ' + self.rootDir[x][0] + '\n'

        self.write(message)

        if self.securityID != self.rootDir[x][4]:

            if self.rootDir[x][5] > 0 and self.rootDir[x][5]& 0x02 == 0:

                self.read(delim = '\n', expect = 'permission denied for read\n'.format(self.rootDir[x][0]))
                return

            elif self.rootDir[x][5] == 0:

                self.read(delim = '\n', expect = 'permission denied\n')
                return

        self.read(delim = '\n', expect = self.fileData[x][0] + '\n')
    def read_first_n(self):

        if self.rootDirFileCount == 0:
            self.write('\n')
            return

        fileChoice = random.randint(0, self.rootDirFileCount-1) 

        count = 0

        for x in range(0, self.maxDirEntries):
            if len(self.rootDir[x][0]) > 0:

                if count == fileChoice:
                    break

                count = count + 1


        message = 'first {} {}\n'.format(self.rootDir[x][0], 10)

        self.write(message)

        if self.securityID != self.rootDir[x][4]:

            if self.rootDir[x][5] > 0 and self.rootDir[x][5]& 0x02 == 0:

                self.read(delim = '\n', expect = 'permission denied for read\n'.format(self.rootDir[x][0]))
                return

            elif self.rootDir[x][5] == 0:

                self.read(delim = '\n', expect = 'permission denied\n')
                return

        self.read(delim = '\n', expect = self.fileData[x][0][0:10] + '\n')


    def read_last_n(self):

        if self.rootDirFileCount == 0:
            self.write('\n')
            return

        fileChoice = random.randint(0, self.rootDirFileCount-1) 

        count = 0

        for x in range(0, self.maxDirEntries):
            if len(self.rootDir[x][0]) > 0:

                if count == fileChoice:
                    break

                count = count + 1


        message = 'last {} {}\n'.format(self.rootDir[x][0], 10)

        self.write(message)

        if self.securityID != self.rootDir[x][4]:

            if self.rootDir[x][5] > 0 and self.rootDir[x][5]& 0x02 == 0:

                self.read(delim = '\n', expect = 'permission denied for read\n'.format(self.rootDir[x][0]))
                return

            elif self.rootDir[x][5] == 0:

                self.read(delim = '\n', expect = 'permission denied\n')
                return

        self.read(delim = '\n', expect = self.fileData[x][0][-10:] + '\n')


    def list_files(self):

        message = 'list\n'
        self.write(message)

        otherperms = ["--", "-W", "R-", "RW"]
        filetype = ["", "DIR", "REG", "MEM", "ROM" ]

        expect_string = "FILENAME                   SIZE        OWNER     O-PERMS    TYPE\n"
        self.read(delim = '\n', expect = expect_string)

        expect_string = "----------------------------------------------------------------\n"
        self.read(delim = '\n', expect = expect_string)

        for i in range(0, self.maxDirEntries):
            if len(self.rootDir[i][0]) != 0:

                expect_string = "{:25s}  {:10d}  {:8s}  {:2s}    {:3s}\n".format(self.rootDir[i][0], 
                                                                        self.rootDir[i][1],
                                                                        self.rootDir[i][6],
                                                                        otherperms[self.rootDir[i][5]],
                                                                        filetype[self.rootDir[i][2]])

                self.read(delim = '\n', expect = expect_string)

        self.read(delim = '\n', expect = '\n')


    def copy_file(self):

        if self.rootDirFileCount == 0:
            self.write('\n')
            return

        fileChoice = random.randint(0, self.rootDirFileCount-1) 
        count = 0

        for x in range(0, self.maxDirEntries):
            if len(self.rootDir[x][0]) > 0:

                if count == fileChoice:
                    break

                count = count + 1

        length = random.randint(5, 19)
        dest_filename = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        message = 'copy {} {}\n'.format(self.rootDir[x][0], dest_filename)

        self.write(message)

        if self.securityID != self.rootDir[x][4]:

            if self.rootDir[x][5] > 0 and self.rootDir[x][5]& 0x02 == 0:

                self.read(delim = '\n', expect = 'permission denied for read\n'.format(self.rootDir[x][0]))
                return

            elif self.rootDir[x][5] == 0:

                self.read(delim = '\n', expect = 'permission denied\n')
                return

        # first make sure the destination file doesn't already exist
        for i in range(0, self.maxDirEntries):
            if self.rootDir[i][0] == dest_filename:

                expect_string = 'file {} already exists\n'.format(filename)
                self.read(delim = '\n', expect = expect_string)
                return

        #it doesn't so find the first empty slot in the directory
        slotFound = False
        
        for i in range(0, self.maxDirEntries):
            if len(self.rootDir[i][0]) == 0:
                self.rootDir[i] = [dest_filename, self.rootDir[x][1], 2, 1, self.securityID, 0, self.userName]
                slotFound = True
                self.rootDirFileCount = self.rootDirFileCount + 1
                self.fileData[i][0] = self.fileData[x][0]
                break

        if slotFound == False:
            expect_string = 'error\n'
            self.read(delim = '\n', expect = expect_string)
            return   

    def exit(self):

        # tell the service to exit normally
        message = 'exit\n'

        self.write(message)


