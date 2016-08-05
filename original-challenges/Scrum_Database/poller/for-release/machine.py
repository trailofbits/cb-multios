#!/usr/bin/env python

from generator.actions import Actions
import random
import string
from struct import pack, unpack, unpack_from


class ScrumTest(Actions):



    def send_message(self, message):

        data = pack('I', 0x12345678)

        # add the length of the message plus the checkvalue
        data = data + pack('H', len(message)-2 )

        # now append the message
        data = data + message

        self.write(data)


    def start(self):


        self.delay(50)
        self.productID_Counter = 0
        self.productIDs = []
        self.productDB = []

        self.sprintIDs = 100

        self.backlogIDs = 1000

        # calculate an integer sum of all values from the magic page to assure it wasn't modified
        value = 0
        for i in range(0, 1024):
            value = (value + unpack('I', self.magic_page[i*4:i*4+4])[0]) & 0xffffffff

        # disguise this value as the "database id"
        expect_string = 'ScrumMaster DB - Database ID: {:x}\n'.format(value)
        self.read(delim = '\n', expect = expect_string)

        # add an initial product so that other states will immediately be valid
        self.addProduct()


    def top(self):
        pass


    def addProduct(self):

        self.productID_Counter = self.productID_Counter + 1
        length = random.randint(5, 25)

        title = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        message = pack('2H', 0x101, self.productID_Counter) + title
        message = message + pack('B', 0)

        self.send_message(message)

        self.productDB.append([self.productID_Counter, title, [], []])
        self.productIDs.append(self.productID_Counter)

    def listAllProducts(self):


        if len(self.productDB) == 0:
            return
            
        message = pack('1H', 0x304)
        self.send_message(message)

        for i in range(0, len(self.productDB)):

            expect_string = 'Product: {}\n'.format(self.productDB[i][1])
            self.read(delim = '\n', expect = expect_string)

        self.read(delim = '\n', expect = '\n')



    def listProduct(self):

        if len(self.productDB) == 0:
            return

        productNumber = random.randint(0, len(self.productDB)-1)

        product2list = self.productDB[productNumber][0]

        message = pack('2H', 0x301, product2list)
        self.send_message(message)

        self.read(delim = '\n', expect = '\n')

        expect_string = 'Product Title: {}\n'.format(self.productDB[productNumber][1])
        self.read(delim = '\n', expect = expect_string)

        expect_string = '   Product ID: {}\n'.format(self.productDB[productNumber][0])
        self.read(delim = '\n', expect = expect_string)

        self.read(delim = '\n', expect = '\n')

        expect_string = 'Product Backlog:\n'
        self.read(delim = '\n', expect = expect_string)

        expect_string = '\t\tID\tPoints\tUser Story\n'
        self.read(delim = '\n', expect = expect_string)   

        for i in range(0, len(self.productDB[productNumber][2])):
            
            idnum = self.productDB[productNumber][2][i][0]
            desc = self.productDB[productNumber][2][i][1]
            points = self.productDB[productNumber][2][i][3]

            # expect_string = '\tItem\t{}:\t{}\t{}\n'.format(idnum, points, desc)
            expect_string = '\tItem\t{}:\t{}\n'.format(idnum, points)
            self.read(delim = '\n', expect = expect_string)  


        self.read(delim = '\n', expect = '\n')

        expect_string = 'Sprints:\n'
        self.read(delim = '\n', expect = expect_string)  

        for i in range(0, len(self.productDB[productNumber][3])):
    
            idnum = self.productDB[productNumber][3][i][0]
            desc = self.productDB[productNumber][3][i][1]

            expect_string = '\tSprint# {}: {}\n'.format(idnum, desc)
            self.read(delim = '\n', expect = expect_string)  

            for x in range(0, len(self.productDB[productNumber][3][i][5])):

                bl_id = self.productDB[productNumber][3][i][5][x][0]
                bl_desc = self.productDB[productNumber][3][i][5][x][1]
                bl_status = self.productDB[productNumber][3][i][5][x][2]
                bl_points = self.productDB[productNumber][3][i][5][x][3]

                # expect_string = '\t\tbacklogitem# {}: {}  {}  {}\n'.format(bl_id, bl_points, bl_status, bl_desc)
                expect_string = '\t\tbacklogitem# {}: {}  {}\n'.format(bl_id, bl_points, bl_status)

                self.read(delim = '\n', expect = expect_string)


            self.read(delim = '\n', expect = '\n')        

        self.read(delim = '\n', expect = '\n')
        


    def deleteProduct(self):

        if len(self.productDB) == 0:
            return

        selection = random.randint(0, len(self.productDB)-1)

        product2delete = self.productDB[selection][0]

        message = pack('2H', 0x403, product2delete)
        self.send_message(message)

        del self.productDB[selection]


    def addSprint(self):

        if len(self.productDB) == 0:
            return

        productNumber = random.randint(0, len(self.productDB)-1)

        selection = self.productDB[productNumber][0]

        length = random.randint(10,40)

        title = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        self.sprintIDs = self.sprintIDs + 1

        message = pack('3H', 0x103, selection, self.sprintIDs) + title
        message = message + pack('B', 0)
        self.send_message(message)

        self.productDB[productNumber][3].append([self.sprintIDs, title, 0, 0, 0, []])


    def addPBI(self):

        if len(self.productDB) == 0:
            return

        productNumber = random.randint(0, len(self.productDB)-1)

        selection = self.productDB[productNumber][0]

        length = random.randint(30, 50)

        title = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        self.backlogIDs = self.backlogIDs + 1

        message = pack('4H', 0x102, selection, self.backlogIDs, 5) + title
        message = message + pack('B', 0)
        self.send_message(message)

        self.productDB[productNumber][2].append([self.backlogIDs, title, 0, 5])

    def movePBI2Sprint(self):

        # make sure the product db isn't empty
        if len(self.productDB) == 0:
            return

        productNumber = random.randint(0, len(self.productDB)-1)

        selection = self.productDB[productNumber][0]

        # make sure the PB isn't empty
        if len(self.productDB[productNumber][2])== 0:
            return

        # make sure the sprint list isn't empty
        if len(self.productDB[productNumber][3])== 0:
            return        


        PBItemNum = random.randint(0, len(self.productDB[productNumber][2])-1)
        PB_ID = self.productDB[productNumber][2][PBItemNum][0]

        TargetSprintNum =random.randint(0, len(self.productDB[productNumber][3])-1)

        TargetSprintID = self.productDB[productNumber][3][TargetSprintNum][0]


        message = pack('4H', 0x201, selection, PB_ID, TargetSprintID)
        self.send_message(message)

        self.productDB[productNumber][3][TargetSprintNum][5].append(self.productDB[productNumber][2][PBItemNum])

        del self.productDB[productNumber][2][PBItemNum]

    def moveSBI2PBL(self):

        # make sure the product db isn't empty
        if len(self.productDB) == 0:
            return

        productNumber = random.randint(0, len(self.productDB)-1)
        selection = self.productDB[productNumber][0]

        # make sure the PB isn't empty
        if len(self.productDB[productNumber][2])== 0:
            return

        # make sure the sprint list isn't empty
        if len(self.productDB[productNumber][3])== 0:
            return        

        TargetSprintNum =random.randint(0, len(self.productDB[productNumber][3])-1)
        TargetSprintID = self.productDB[productNumber][3][TargetSprintNum][0]

        if len(self.productDB[productNumber][3][TargetSprintNum][5]) == 0:
            return

        PBItemNum = random.randint(0, len(self.productDB[productNumber][3][TargetSprintNum][5])-1)
        PB_ID = self.productDB[productNumber][3][TargetSprintNum][5][PBItemNum][0]


        message = pack('4H', 0x202, selection, PB_ID, TargetSprintID)
        self.send_message(message)

        self.productDB[productNumber][2].append(self.productDB[productNumber][3][TargetSprintNum][5][PBItemNum])

        del self.productDB[productNumber][3][TargetSprintNum][5][PBItemNum]


    def updateSBIStatus(self):

        # make sure the product db isn't empty
        if len(self.productDB) == 0:
            return

        productNumber = random.randint(0, len(self.productDB)-1)
        selection = self.productDB[productNumber][0]

        # make sure the sprint list isn't empty
        if len(self.productDB[productNumber][3])== 0:
            return        

        TargetSprintNum =random.randint(0, len(self.productDB[productNumber][3])-1)
        TargetSprintID = self.productDB[productNumber][3][TargetSprintNum][0]

        if len( self.productDB[productNumber][3][TargetSprintNum][5] ) == 0:
            return

        SBINum = random.randint(0, len( self.productDB[productNumber][3][TargetSprintNum][5] )-1)
        SB_ID = self.productDB[productNumber][3][TargetSprintNum][5][SBINum][0]


        Value = random.randint(0, 10)

        message = pack('5H', 0x501, selection, SB_ID, TargetSprintID, Value)
        self.send_message(message)


        self.productDB[productNumber][3][TargetSprintNum][5][SBINum][2] = Value


    def updateSBIPoints(self):

        # make sure the product db isn't empty
        if len(self.productDB) == 0:
            return

        productNumber = random.randint(0, len(self.productDB)-1)
        selection = self.productDB[productNumber][0]

        # make sure the sprint list isn't empty
        if len(self.productDB[productNumber][3])== 0:
            return        

        TargetSprintNum =random.randint(0, len(self.productDB[productNumber][3])-1)
        TargetSprintID = self.productDB[productNumber][3][TargetSprintNum][0]

        if len( self.productDB[productNumber][3][TargetSprintNum][5] ) == 0:
            return

        SBINum = random.randint(0, len( self.productDB[productNumber][3][TargetSprintNum][5] )-1)
        SB_ID = self.productDB[productNumber][3][TargetSprintNum][5][SBINum][0]


        Value = random.randint(0, 10)

        message = pack('5H', 0x502, selection, SB_ID, TargetSprintID, Value)
        self.send_message(message)


        self.productDB[productNumber][3][TargetSprintNum][5][SBINum][3] = Value



    def updateSBIDesc(self):

        # make sure the product db isn't empty
        if len(self.productDB) == 0:
            return

        productNumber = random.randint(0, len(self.productDB)-1)
        selection = self.productDB[productNumber][0]

        # make sure the sprint list isn't empty
        if len(self.productDB[productNumber][3])== 0:
            return        

        TargetSprintNum =random.randint(0, len(self.productDB[productNumber][3])-1)
        TargetSprintID = self.productDB[productNumber][3][TargetSprintNum][0]

        if len( self.productDB[productNumber][3][TargetSprintNum][5] ) == 0:
            return

        SBINum = random.randint(0, len( self.productDB[productNumber][3][TargetSprintNum][5] )-1)
        SB_ID = self.productDB[productNumber][3][TargetSprintNum][5][SBINum][0]


        length = random.randint(20, 30)
        title = ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

        message = pack('4H', 0x503, selection, SB_ID, TargetSprintID) + title
        message = message + pack('B', 0)
        self.send_message(message)


        self.productDB[productNumber][3][TargetSprintNum][5][SBINum][1] = title



    def deleteSprint(self):

        # make sure the product db isn't empty
        if len(self.productDB) == 0:
            return

        productNumber = random.randint(0, len(self.productDB)-1)
        selection = self.productDB[productNumber][0]

        # make sure the sprint list isn't empty
        if len(self.productDB[productNumber][3])== 0:
            return        

        TargetSprintNum =random.randint(0, len(self.productDB[productNumber][3])-1)
        TargetSprintID = self.productDB[productNumber][3][TargetSprintNum][0]


        message = pack('3H', 0x402, selection, TargetSprintID)
        self.send_message(message)


        if len( self.productDB[productNumber][3][TargetSprintNum][5] ) != 0:
            return
        else:
            del self.productDB[productNumber][3][TargetSprintNum]



    def end(self):

        # tell it to exit normally
        message = pack('H', 0xdead)
        self.send_message(message)




       
