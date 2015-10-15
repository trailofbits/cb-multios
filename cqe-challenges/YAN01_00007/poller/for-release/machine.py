#!/usr/bin/env python

from generator.actions import Actions
import copy
import random
import string
import numpy
import struct

valid_users = [ [6, 3, 4, 5], [9, 1, 6, 8], [12, 6, 8, 10], [18, 9, 12, 15], [19, 3, 10, 18], [20, 7, 14, 17], [24, 12, 16, 20], [25, 4, 17, 22], [27, 3, 18, 24], [28, 18, 19, 21], [29, 11, 15, 27], [30, 15, 20, 25], [36, 18, 24, 30], [38, 6, 20, 36], [40, 14, 28, 34], [41, 6, 32, 33], [42, 21, 28, 35], [44, 16, 23, 41], [45, 5, 30, 40], [46, 27, 30, 37], [48, 24, 32, 40] ]

MAX_UINT = 1000000 #the version of strToDecimal in this CB does not support the whole uint32_t space
MAX_USERS = 21
MAX_PASSWORDS = 10

def tobytes(i) :
  return struct.pack("<I", i)

class DioGame(Actions):

    def processSecret(self, chosen_one, reverse=0):
        x = 1
        y = 2
        z = 3
        if reverse :
          z = 1
          x = 3

        self.read(delim='\n', expect="First Secret\n");
        self.write("%u\n" % chosen_one[x])
        self.read(delim='\n', expect="Second Secret\n");
        self.write("%u\n" % chosen_one[y])
        self.read(delim='\n', expect="Third Secret\n");
        self.write("%u\n" % chosen_one[z])

    def start(self):
        self.passwords = [ [ [0,0,0] for _ in xrange(MAX_PASSWORDS) ] for _ in xrange(MAX_USERS) ]

    def login(self):
        self.chosen_one = random.randint(0,len(valid_users)-1)
         
        self.read(delim='\n', expect="Welcome to the Diophantine Password Wallet\n")

    def bad_user(self):
        self.read(delim='\n', expect="Login\n")
        self.write("%u\n" % random.randint(len(valid_users) + 1, MAX_UINT))

        self.processSecret(valid_users[self.chosen_one])
        self.read(delim="\n", expect="User Not Found\n") 

 
    def good_user(self):
        self.read(delim='\n', expect="Login\n")
        self.write("%u\n" % self.chosen_one)

    def good_secrets(self):
        self.processSecret(valid_users[self.chosen_one])
 
    def bad_secrets(self):
        if random.randint(0,1):
          self.processSecret(valid_users[self.chosen_one], 1)
        else:
          self.processSecret( valid_users[(self.chosen_one + 1) % len(valid_users)] )

        self.read(delim='\n', expect="Login failed\n")

    def user_menu(self):
        pass

    def menu_print(self):
        self.write("P\n")
        j = 0;
        for i in self.passwords[self.chosen_one] :
          if i[0] != 0 or i[1] != 0 or i[2] != 0 :
            self.read(delim='\n', expect="Password %u : %u , %u , %u\n" % (j, i[0], i[1], i[2]))
            j += 1
 
    def menu_add(self):
        self.write("A\n")
        temp = [ random.randint(0,MAX_UINT) for _ in xrange(4) ]
        self.processSecret(temp)
        for i in self.passwords[self.chosen_one] :
          if i[0] == 0 and i[1] == 0 and i[2] == 0 :
            i[0] = temp[1]
            i[1] = temp[2]
            i[2] = temp[3]
            break
  
    def menu_rm(self):
        self.write("R\n")
        self.read(delim='\n', expect="Remove PW NUm?\n")
        temp = random.randint(0,MAX_PASSWORDS)
        self.write("%u\n" % temp)
        j = 0
        for i in xrange(MAX_PASSWORDS) :
          if (self.passwords[self.chosen_one][i][0] != 0) and (self.passwords[self.chosen_one][i][1] != 0) and (self.passwords[self.chosen_one][i][2] != 0) :
            if j == temp :
              self.passwords[self.chosen_one][i] = [0,0,0]
              break
            else :
              j += 1

    def menu_logout(self):
        self.write("L\n")

    def menu_bad(self):
        self.write(random.choice(string.ascii_lowercase) + "\n")
        self.read(delim='\n', expect="Bad command\n")

    def end(self):
        pass



