import struct
import math
from generator.actions import Actions
import random
import sys

class customImage(object):

    def __init__(self):
        self.height = 512
        self.width = 512
        self.pixels = [[0 for x in range(512)] for y in range(512)]
        self.gradient_angle = [[0 for x in range(512)] for y in range(512)]

    def loadImage(self, data):
        seperated_data = data.split("\x02")

        #check whether or not the data was somewhat reasonably formatted
        if len(seperated_data) != 5 or len(seperated_data[4]) != (512*512):
            # the data was not correctly formatted
            print "data not correctly formatted"
            return

        # load the data
        x = 0
        y = 0
        for ele in seperated_data[4]:
            self.pixels[x][y] = struct.unpack('B', ele)[0]
            y = y + 1
            if y % 512 == 0:
                x = x + 1
                y = y % 512

    def writeImageDown(self):
        output = ""
        output += "CG\x02512\x02512\x02111\x02"
        for row in self.pixels:
            for ele in row:
                output += chr(ele)
        return output

    def getVal(self, x, y):

        # deal with out of bounds requests
        if x < 0:
            x = 0
        elif x > 511:
            x = 511

        if y < 0:
            y = 0
        elif y > 511:
            y = 511

        return self.pixels[x][y]


    def applyFilter(self):
        gaus_filter = [[2,4,5,4,2],[4,9,12,9,4],[5,12,15,12,5],[4,9,12,9,4],[2,4,5,4,2]]

        hold_pixels = [[0 for x in range(512)] for y in range(512)]

        # go through each pixel and apply the filter
        for m in range(512):
            for n in range(512):

                value = float(0)
                for x in range(-2, 3):
                    for y in range(-2, 3):
                        value += gaus_filter[x+2][y+2] * self.getVal(m+x, n+y)

                value = value / 159.0
                value = math.floor(value)
                hold_pixels[m][n] = int(value)%256

        for m in range(512):
            for n in range(512):
                self.pixels[m][n] = hold_pixels[m][n]

    def onlyTwoDecimals(self, incoming):
        string_rep = '%.12f' % incoming
        i, p, d = string_rep.partition('.')
        return '.'.join([i,(d+'0'*0)[:0]])

    def findGradients(self):
        x_kernel = [[-1,0,1],[-2,0,2],[-1,0,1]]
        y_kernel = [[1,2,1],[0,0,0],[-1,-2,-1]]

        kgx = [[0 for x in range(512)] for y in range(512)]
        kgy = [[0 for x in range(512)] for y in range(512)]

        hold_pixels = [[0 for x in range(512)] for y in range(512)]

        for m in range(512):
            for n in range(512):
                value_x = 0
                value_y = 0
                for x in range(-1,2):
                    for y in range(-1,2):
                        value_x += x_kernel[x+1][y+1] * self.getVal(m+x, n+y)
                        value_y += y_kernel[x+1][y+1] * self.getVal(m+x, n+y)
                kgx[m][n] = value_x
                kgy[m][n] = value_y
                hold_pixels[m][n] = int(math.sqrt((value_x*value_x)+(value_y*value_y)))%256
                if hold_pixels[m][n] > 255 or hold_pixels[m][n] < 0:
                    print value_x
                    print value_y
                    print hold_pixels[m][n]

                hold = float(0)
                if value_x != 0:
                    hold = math.fabs(value_y) / math.fabs(value_x)
                else:
                    hold = 0.0
                hold = float(self.onlyTwoDecimals(hold))

                grad_hold = math.atan(hold)
                grad_hold = float(self.onlyTwoDecimals(grad_hold))

                grad_hold = (57.29) * grad_hold
                grad_hold = float(self.onlyTwoDecimals(grad_hold))
                grad_hold += 22.5

                grad_hold = float(self.onlyTwoDecimals(grad_hold))
                self.gradient_angle[m][n] = int(math.floor(grad_hold))
                self.gradient_angle[m][n] = (self.gradient_angle[m][n] // 45) + 2
                #print self.gradient_angle[m][n]

        for m in range(512):
            for n in range(512):
                self.pixels[m][n] = hold_pixels[m][n] % 256

    def non_max_suppressions(self):

        hold_pixels = [[0 for x in range(512)] for y in range(512)]

        for m in range(512):
            for n in range(512):
                val_0_x = 0
                val_0_y = 0
                val_1_x = 0
                val_1_y = 0
                grad_value = self.gradient_angle[m][n]

                if grad_value == 0 or grad_value == 4:
                    val_0_x = -1
                    val_0_y = 0
                    val_1_x = 1
                    val_1_y = 0
                elif grad_value == 1 or grad_value == 5:
                    val_0_x = -1
                    val_0_y = -1
                    val_1_x = 1
                    val_1_y = 1
                elif grad_value == 2 or grad_value == 6:
                    val_0_x = 0
                    val_0_y = -1
                    val_1_x = 0
                    val_1_y = 1
                elif grad_value == 3 or grad_value == 7:
                    val_0_x = 1
                    val_0_y = -1
                    val_1_x = -1
                    val_1_y = 1

                val_0 = self.getVal(m+val_0_x, n+val_0_y)
                val_1 = self.getVal(m+val_1_x, n+val_1_y)
                max = self.getVal(m, n)
                if max < val_0 or max < val_1:
                    max = 0
                hold_pixels[m][n] = max

        for m in range(512):
            for n in range(512):
                self.pixels[m][n] = hold_pixels[m][n]

    def double_thresholding(self):
        hold_pixels = [[0 for x in range(512)] for y in range(512)]

        for m in range(512):
            for n in range(512):
                hold_value = 0
                pixel_value = self.pixels[m][n]
                if pixel_value > 70:
                    hold_value = 254
                elif pixel_value > 20:
                    hold_value = 60
                hold_pixels[m][n] = hold_value

        for m in range(512):
            for n in range(512):
                self.pixels[m][n] = hold_pixels[m][n]

    def hysteresis(self):
        hold_pixels = [[0 for x in range(512)] for y in range(512)]

        for m in range(512):
            for n in range(512):
                if self.pixels[m][n] == 60:
                    write_hold = 0
                    for x in range(-1, 2):
                        for y in range(-1, 2):
                            if self.getVal(m+x, n+y) == 254:
                                write_hold = 254
                    hold_pixels[m][n] = write_hold
                elif self.pixels[m][n] == 254:
                    hold_pixels[m][n] = 254

        for m in range(512):
            for n in range(512):
                self.pixels[m][n] = hold_pixels[m][n]

    def performImageMagic(self, data):
        self.loadImage(data)
        self.applyFilter()
        self.findGradients()
        self.non_max_suppressions()
        self.double_thresholding()
        self.hysteresis()
        d = self.writeImageDown()
        return d

class pacAttackGame(object):

    def __init__(self):
        self.board = [[1 for x in range(20)] for y in range(20)]
        walls = [(0,4),(0,5),(0,10),(0,11),(0,17),(1,1),(1,2),(1,4),(1,5),(1,10),(1,11),(2,14),(2,15),(2,16),(2,17),(2,18),(3,0),(3,1),(3,2),(3,10),(3,11),(3,14),(4,4),(4,5),(4,10),(4,11),(4,14),(4,19),(5,4),(5,5),(5,10),(5,11),(5,14),(5,15),(5,16),(5,19),(6,4),(6,5),(6,10),(6,11),(6,16),(6,19),(7,1),(7,2),(7,4),(7,5),(7,10),(7,11),(7,16),(7,18),(7,19),(8,1),(8,10),(8,11),(8,13),(8,14),(8,15),(8,16),(8,18),(8,19),(9,4),(9,5),(9,19),(10,4),(10,5),(10,10),(10,11),(10,14),(10,15),(10,19),(11,2),(11,4),(11,5),(11,10),(11,11),(11,13),(11,14),(11,15),(12,2),(12,4),(12,5),(12,10),(12,11),(13,1),(13,2),(13,4),(13,5),(13,10),(13,11),(13,16),(13,17),(13,18),(14,4),(14,5),(14,10),(14,11),(14,18),(15,4),(15,5),(15,7),(15,10),(15,11),(15,13),(15,14),(15,18),(16,4),(16,5),(16,7),(16,8),(16,10),(16,11),(16,18),(17,4),(17,5),(17,8),(17,10),(17,11),(17,14),(17,15),(17,16),(17,17),(17,18),(18,1),(18,2),(18,4),(18,5),(18,10),(18,11),(18,14),(19,0),(19,1),(19,2),(19,10),(19,11)]
        for (x,y) in walls:
            self.board[x][y] = 2

        self.pac_x_loc = 0
        self.pac_y_loc = 0

        self.board[0][0] = 4

    def drawBoard(self):
        output = ""

        for x in xrange(22):
            output += "-"

        output += "\x0c"

        for x in xrange(20):
            output += "|"
            for y in xrange(20):
                if(self.board[x][y] == 0):
                    output += " "
                elif(self.board[x][y] == 1):
                    output += "."
                elif(self.board[x][y] == 2):
                    output += "+"
                elif(self.board[x][y] == 4):
                    output += "O"
            output += "|\x0c"

        for x in xrange(22):
            output += "-"

        output += "\x0c"

        return output

    def userHasNotWon(self):
        # scroll through every element looking for a remaining dot
        for row in self.board:
            for ele in row:
                if ele == 1:
                    return True

        # if we got here, we didn't find one
        return False

    def makeMove(self, user_input, user_input_2):
        # get move char
        move_char = user_input[0]

        target_x_loc = self.pac_x_loc
        target_y_loc = self.pac_y_loc

        # check if move is valid
        if (self.pac_y_loc == 0 and move_char == 'a'):
            return
        elif (self.pac_y_loc == 19 and move_char == 'd'):
            return
        elif (self.pac_x_loc == 0 and move_char == 'w'):
            return
        elif (self.pac_x_loc == 19 and move_char == 's'):
            return

        # check if the move would take us into a wall
        if move_char == 'a':
            target_y_loc -= 1
        elif move_char == 'd':
            target_y_loc += 1
        elif move_char == 's':
            target_x_loc += 1
        elif move_char == 'w':
            target_x_loc -= 1
        elif move_char == 'q':
            location = user_input_2
            target_x_loc = int(((int(location))/20))
            target_y_loc = int(((int(location))%20))

            # make sure the values didn't get out of control
            if target_x_loc > 19 or target_x_loc < 0:
                target_x_loc = 0
            if target_y_loc > 19 or target_y_loc < 0:
                target_y_loc = 0
        else:
            return

        # now we need to make sure the location isn't a wall
        if self.board[target_x_loc][target_y_loc] != 2:
            # move the character to the new location
            self.board[target_x_loc][target_y_loc] = 4
            # remove the old pac
            self.board[self.pac_x_loc][self.pac_y_loc] = 0
            # set the new location
            self.pac_x_loc = target_x_loc
            self.pac_y_loc = target_y_loc


class game(object):

    def __init__(self):
        self.max_moves = min(random.paretovariate(9) * 100, 682)
        self.obj = pacAttackGame()

        self.over = False
        self.number_of_moves = 0

    def next(self, userInput, userInput2):
        output = ""

        if (self.number_of_moves < self.max_moves) and self.obj.userHasNotWon():
            self.number_of_moves += 1
            output += str(self.number_of_moves) + "\x0c"
            output += self.obj.drawBoard()
            # get user input
            user_input = userInput
            # deal with no input case
            if len(user_input) == 0:
                user_input = " "

            # send move to game obj
            self.obj.makeMove(user_input, userInput2)

        if not self.obj.userHasNotWon():
            output += "IMAGE MAGIC\x0c"
            my_obj = customImage()
            output += my_obj.performImageMagic(IMAGE_DATA)
            self.over = True

        if self.number_of_moves >= self.max_moves:
            self.over = True

        return output

def random_string(cnt):
    return ''.join([chr(random.randint(97, 122)) for x in xrange(cnt)])
def random_input():
    rndStr = random.choice(['q','a','s','w','d'])
    return rndStr

class TemplateGenerator(Actions):

    def start(self):
        #self.delay(100)
        self.write(self.magic_page[:4])
        self.write('\x00\xc0\x47\x43')
        self.read(length=0x1000, expect=self.magic_page)

        self.gameObj = game()

    def win(self):
        self.gameObj.max_moves = 682
        shuffled = list(xrange(400))
        random.shuffle(shuffled)
        turnCount = 0
        while not self.gameObj.over:
            # get user input
            if turnCount < 400:
                userInput = 'q'
                userInput2 = shuffled[turnCount]
                turnCount += 1
            else:
                userInput = random.choice(['a','s','w','d'])
            # get predicted output
            predicted_output = self.gameObj.next(userInput, userInput2)
            self.write(userInput + '\x0c')
 
            # handle teleport case
            if userInput == 'q':
                self.write(str(userInput2) + '\x0c')
            if self.gameObj.over:
                self.write(IMAGE_DATA)
             
            self.read(length=len(predicted_output), expect=predicted_output)

    def go(self):
        while not self.gameObj.over:
            # get user input
            userInput = random_input()
            userInput2 = random.randint(0,400)
            # get predicted output
            predicted_output = self.gameObj.next(userInput, userInput2)
            self.write(userInput + '\x0c')

            # handle teleport case
            if userInput == 'q':
                self.write(str(userInput2) + '\x0c')

            lines = predicted_output.split('\x0c')
            del lines[-1]
            for line in lines:
                self.read(delim='\x0c', expect=line+'\x0c')

    def quit(self):
        pass

IMAGE_DATA = open('./support/kitten_picture.pic', 'rb').read()
