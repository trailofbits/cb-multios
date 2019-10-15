#!/usr/bin/env python

from generator.actions import Actions
import random
import string
from struct import pack, unpack, unpack_from


class FileSystemTest(Actions):

    def start(self):

        #self.delay(100)
        self.created_users = []
        self.securityTokenIndex = 0
        self.securityToken = 1337
        self.newPostId = unpack('I', self.magic_page[0:4])[0] & 0x0fffffff
        self.posts = []

        self.maxRealNameLen = 30
        self.maxPostLen = 128


    def top(self):
        pass

    def bad_auth(self):

        length = random.randint(4, 4)
        username = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        message = pack('=IB', 0xb0, length) + username

        length = random.randint(5, 10)
        password = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        message = message + pack('B', length) + password

        self.write(message)

        response = pack('I', 0xffffffff )

        self.read(length = len(response), expect = response)

    def authenticate(self):

        if len(self.created_users) == 0:
            return

        mychoice = random.randint(0, len(self.created_users) - 1 )

        message = pack('=IB', 0xb0, len(self.created_users[mychoice][0])) + self.created_users[mychoice][0]

        message = message + pack('=B', len(self.created_users[mychoice][1])) + self.created_users[mychoice][1]

        self.write(message)

        response = pack('I', self.created_users[mychoice][3] )

        self.read(length = len(response), expect = response)

    def create_user(self):

        length = random.randint(5, 10)
        username = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        message = pack('=IB', 0xa0, length) + username

        length = random.randint(5, 10)
        password = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        message = message + pack('B', length) + password

        length = random.randint(10, 25)
        fullname = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        message = message + pack('B', length) + fullname

        self.write(message)

        ID1 = (unpack('I', self.magic_page[self.securityTokenIndex*4+4:self.securityTokenIndex*4+8])[0])
        self.securityTokenIndex = self.securityTokenIndex + 1
        ID2 = (unpack('I', self.magic_page[self.securityTokenIndex*4+4:self.securityTokenIndex*4+8])[0])
        self.securityTokenIndex = self.securityTokenIndex + 1

        securityToken = (ID1 * ID2) & 0x7fffffff

        for i in range(0, len(self.created_users)-1):

            if self.created_users[i][3] == securityToken:
                securityToken = securityToken + 1
                break
        self.created_users.append([username, password, fullname, securityToken, 0, 0])

        response = pack('I', 0 )

        self.read(length = len(response), expect = response)
        
        
    def newFeed(self):

        if len(self.created_users) == 0:
            return

        mychoice = random.randint(0, len(self.created_users) - 1 )

        message = pack('=II', 0xc0, self.created_users[mychoice][3])

        self.write(message)

        lastItem = self.created_users[mychoice][4]

        index = len(self.posts)

        for i in range(0, len(self.posts)):

            if self.posts[i][0] > lastItem:
                index = i
                break

        if index < len(self.posts):

            item = self.posts[index]

            self.created_users[mychoice][4] = item[0]

            for i in range(0, len(self.created_users)):

                if self.created_users[i][3] == item[1]:
                    fullname = self.created_users[i][2]
                    break

            response = pack('I', len(fullname)) + fullname
            response = response + pack('I', len(item[2]) ) + item[2]

        else:
            response = pack('i', -1 )


        self.read(length = len(response), expect = response)   


    def newPost(self):

        if len(self.created_users) == 0:
            return

        mychoice = random.randint(0, len(self.created_users) - 1 )

        message = pack('=II', 0xd0, self.created_users[mychoice][3]);

        length = random.randint(20, 100)
        posting = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        message = message + pack('B', length) + posting

        self.write(message)

        self.posts.append([self.newPostId, self.created_users[mychoice][3], posting, []])

        response = pack('I', self.newPostId )

        self.newPostId = self.newPostId + 1

        self.read(length = len(response), expect = response) 

    def retrievePost(self):

        if len(self.posts) == 0:
            return

        mychoice = random.randint(0, len(self.posts) - 1)

        message = pack('=II', 0xf0, self.posts[mychoice][0])

        self.write(message)

        for i in range(0, len(self.created_users)):

            if self.created_users[i][3] == self.posts[mychoice][1]:
                fullname = self.created_users[i][2]
                break


        response = pack('I', len(fullname)) + fullname
        response = response + pack('I', len(self.posts[mychoice][2]) ) + self.posts[mychoice][2]

        self.read(length = len(response), expect = response) 

        # if there are any comments, read those too
        for x in range(0, len(self.posts[mychoice][3])):

            for i in range(0, len(self.created_users)):

                if self.created_users[i][3] == self.posts[mychoice][3][x][0]:
                    fullname = self.created_users[i][2]
                    break 

            response = pack('I', x+1)
            response = response + pack('I', len(fullname)) + fullname
            response = response + pack('I', len(self.posts[mychoice][3][x][1]) ) + self.posts[mychoice][3][x][1]

            self.read(length = len(response), expect = response) 

    def retrieveStickyPost(self):

        postChoice = random.randint(0, 15)

        message = pack('=II', 0xf0, postChoice)

        self.write(message)

        name = ''

        for i in range(0, self.maxRealNameLen):

            name = name + chr((ord(self.magic_page[postChoice*160 +1536 + i]) % 26) + ord('A'))

        response = pack('=I', len(name))
        self.read(length = len(response), expect = response) 
        self.read(length = len(name), expect = name )


        post = ''

        for i in range(0, self.maxPostLen):

            post = post + chr((ord(self.magic_page[postChoice*160 + 1536 + self.maxRealNameLen + i]) % 26) + ord('A'))

        response = pack('I', len(post))
        self.read(length = len(response), expect = response) 
        self.read(length = len(post), expect = post)

    def badRetrieve(self):

        message = pack('=II', 0xf0, self.newPostId+ random.randint(1, 1000))

        self.write(message)

        response = pack('i', -1 )

        self.read(length = len(response), expect = response)


    def addComment(self):

        if len(self.posts) == 0:
            return

        postchoice = random.randint(0, len(self.posts) - 1)

        commenterchoice = random.randint(0, len(self.created_users) - 1 )

        length = random.randint(20, 99)
        comment = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        message = pack('=IIIB', 0xe0, self.posts[postchoice][0], self.created_users[commenterchoice][3], length) + comment

        self.posts[postchoice][3].append([self.created_users[commenterchoice][3], comment])
        self.write(message)

        response = pack('I', 0)

        self.read(length = len(response), expect = response)


    def exit(self):

        # tell the service to exit normally
        message = pack('=I', 100)

        self.write(message)

        self.read(length = 4, expect = 'BYE!')

    def finish(self):

        pass


