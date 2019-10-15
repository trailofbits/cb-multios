#!/usr/bin/env python

from generator.actions import Actions
import copy
import random
import string
import numpy


def myFloatToString(x):
    tempi = int(numpy.float32(x))
    tempj = int((numpy.float32(x) - numpy.float32(tempi)) * (numpy.float32(1000000.0)))
    #we need this if statement because the CB actually prints 0 as 0.0 and not
    # and not 0.000000
    if tempj == 0 :
        return '{:d}.{:d}'.format(tempi, tempj)

    return '{:d}.{:06d}'.format(tempi, tempj)
         
class Tennisball(Actions):

    def start(self):
        #generate a random velocity
        self.v0x_whole = random.randint(0,99)
        self.v0x_frac = random.randint(0,999999)
        #NOTE: Keep in mind that because I am dividing by 1000000, a random number like 45 will become .000045 and not .45. Meaning it is not possible to get .450000 - but that is fine since it will be similar to .450001.
        self.v0x = numpy.float32(numpy.float64(self.v0x_whole) + (numpy.float64(self.v0x_frac) / numpy.float64(1000000)))

        self.v0y_whole = random.randint(0,99)
        self.v0y_frac = random.randint(0,999999)
        self.v0y = numpy.float32(numpy.float64(self.v0y_whole) + (numpy.float64(self.v0y_frac) / numpy.float64(1000000)))
        self.timecount = random.randrange(100) * 510

        self.vx = numpy.zeros(510, dtype='float32')
        self.vy = numpy.zeros(510, dtype='float32')

        #print(myFloatToString(self.v0x) + ' .. ' + myFloatToString(self.v0y) + ' .. ' + myFloatToString(self.timecount))

    def v0x(self):
        #lets make it look by giving a bad number
        self.read(length=20, expect='Initial Velocity X: ')
        #NOTE: I am just using z here - we can change it to other 
        # non number entries too
        self.write('z\n')

    def v0x_out(self):
        #time to get out of the v0x loop so give it a real velocity
        self.read(length=20, expect='Initial Velocity X: ')
        if self.v0x_frac == 0 :
            self.write('{:d}.{:d}\n'.format(self.v0x_whole, self.v0x_frac))
        else :
            self.write('{:d}.{:06d}\n'.format(self.v0x_whole, self.v0x_frac))

    def v0y(self):
        #lets make it look by giving a bad number
        self.read(length=20, expect='Initial Velocity Y: ')
        self.write('z\n')
   
    def v0y_out(self):
        self.read(length=20, expect='Initial Velocity Y: ')
        if self.v0x_frac == 0 :
            self.write('{:d}.{:d}\n'.format(self.v0y_whole, self.v0y_frac))
        else :
            self.write('{:d}.{:06d}\n'.format(self.v0y_whole, self.v0y_frac))

    
    def init_count(self):
        self.read(length=15, expect='Initial Count: ')
        self.write('{:d}\n'.format(self.timecount))

        #self.read(length=21, expect='49.145862, 84.926704\n')
        #self.running_p();

    def running_input(self):
        #don't need to do anything - just wait
        pass 

    def running_c(self):
        #issue a continue and increment the count
        self.write('c\n')
        self.timecount += 510

    def running_p(self):
        #issue a print command
        self.write('p\n')
         
        #then make sure the values are the same
        for i in xrange(51):

            for j in xrange(10):
                idx = i * 10 + j
                tempTime = numpy.float32(self.timecount) / numpy.float32(10)
                #NOTE: I need to force the calculations to use float64 as the intermediate
                # type - this is the default rounding mode
                #self.vx[idx] = tempTime * self.v0x
                #self.vy[idx] = (tempTime * self.v0y) - (numpy.float32(9.8) * tempTime * tempTime / numpy.float32(2.0))
                #NOTE: For gcc
                #self.vx[idx] = numpy.float32(numpy.float64(tempTime) * numpy.float64(self.v0x))
                #NOTE: For clang
                self.vx[idx] = numpy.float32(numpy.float32(tempTime) * numpy.float32(self.v0x))
                #I am just casting the constant to float32 first and then to float64 instead of going to float64 directly - not sure if this will really matter, but the idea is we want the number rounded to float32 but represented in float64
                #NOTE: For gcc
                #self.vy[idx] = numpy.float32((numpy.float64(tempTime) * numpy.float64(self.v0y)) - (numpy.float64(numpy.float32(9.8)) * numpy.float64(tempTime) * numpy.float64(tempTime) / numpy.float64(numpy.float32(2.0))))
 
                #Clang generates sse instructions and uses the *ss form meaning everything is done in single precision format. Thus, the clang version uses float32s instead of float64s for intermediate calculations
                #NOTE: For clang
                self.vy[idx] = numpy.float32((numpy.float32(tempTime) * numpy.float32(self.v0y)) - (numpy.float32(numpy.float32(9.8)) * numpy.float32(tempTime) * numpy.float32(tempTime) / numpy.float32(numpy.float32(2.0))))

                if self.vy[idx] < numpy.float32(0.0) :
                    self.vy[idx] = numpy.float32(0.0)

                self.read(delim='\n', expect='x=' + myFloatToString(self.vx[idx]) + ', y=' + myFloatToString(self.vy[idx]) + '\n');

                self.timecount += 1       

    def end(self):
        self.write('x\n');


