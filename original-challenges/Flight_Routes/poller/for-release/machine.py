#!/usr/bin/env python

from generator.actions import Actions
import random
import string
from struct import pack, unpack, unpack_from


class AirportTest(Actions):


    def start(self):


        #self.delay(100)
        self.airports = []

        value = 0
        for i in range(0, 4096):
            value = value + ord(self.magic_page[i])

        # disguise this value as the "database id"
        expect_string = 'Database checksum: {}\n'.format(value)
        self.read(delim = '\n', expect = expect_string)

        self.initDB()


    def top(self):

        pass


    def endIt(self):

        self.write('13\n')
        self.read(delim='\n', expect = 'OK\n')

    def finish(self):

        pass
       
    def initDB(self):


        offset = 1
        value = 0

        airportCount = ord(self.magic_page[0]) % 16 + 5


        for i in range(0, airportCount):

            Finished = False

            while Finished == False:
                apCode = ''

                for x in range(0, 3):

                    value = (ord(self.magic_page[offset]) % 26) + ord('A')
                    apCode = apCode+ chr(value)
                    offset = offset + 1


                Finished = True

                for ap in self.airports:

                    if apCode == ap[0]:

                        Finished = False
                        break


            self.airports.append([apCode, []])


        for ap in self.airports:

            connectionCount = ord(self.magic_page[offset]) % int(airportCount/2) + 1
            offset = offset + 1

            i = 0

            while i < connectionCount:

                connectionNum = ord(self.magic_page[offset]) % airportCount
                offset = offset + 1

                connectionCode = self.airports[connectionNum][0]

                Found = False

                for connection in ap[1]:

                    if connection[0] == connectionCode:
                        Found = True

                        break

                if Found == False:

                    ap[1].append([connectionCode,  ord(self.magic_page[offset]), ord(self.magic_page[offset+1])])
                    offset = offset + 2
                    i = i + 1

    def deleteAirport(self):


        self.write('3\n')

        if len(self.airports) == 0:

            self.read(delim = '\n', expect = 'EMPTY DB\n')
            return

        choice = random.randint(0, len(self.airports)-1)

        apCode = self.airports[choice][0]

        self.read(delim = '\n', expect = "Enter airport code for deletion:\n")

        self.write(apCode + '\n')

        del self.airports[choice]

        numAirports = len(self.airports)

        for i in range(0, numAirports):

            if len(self.airports[i]) == 1:
                continue

            numConnections = len(self.airports[i][1])

            for x in range(0, numConnections):

                if self.airports[i][1][x][0] == apCode:
                    del self.airports[i][1][x]
                    break

        self.read(delim = '\n', expect = 'OK\n')


    def addAirport(self):


        self.write('2\n')
        
        newCode = ''.join(random.choice(string.ascii_uppercase) for i in range(3))
        self.write(newCode + '\n')

        for ap in self.airports:

            if newCode == ap[0]:

                self.read(delim='\n', expect = 'Duplicate code detected\n')
                self.read(delim='\n', expect = 'AIRPORT CODE EXISTS\n')
                return


        self.read(delim = '\n', expect = 'Enter airport code for connection:\n')

        if len(self.airports) > 0:

            connectionCode = random.randint(0, len(self.airports)-1)


            while self.airports[connectionCode][0] == newCode:
                connectionCode = random.randint(0, len(self.airports)-1)

            cost = random.randint(1, 254)
            time = random.randint(1, 254)
            self.write(self.airports[connectionCode][0] + '\n')

            self.read(delim = '\n', expect = 'Connection cost:\n')

            self.write('{}\n'.format(cost))

            self.read(delim = '\n', expect = 'Connection duration:\n')

            self.write('{}\n'.format(time))

            self.airports.append([newCode, [[self.airports[connectionCode][0], cost, time]]])

            self.read(delim = '\n', expect = 'Enter airport code for connection:\n')

            self.write('\n')  
        else:
            self.write('\n')   
            self.airports.append([newCode] )

        self.read(delim = '\n', expect = 'OK\n')  

    def printAirports(self):


        self.write('1\n')

        if len(self.airports) == 0:
            self.read(delim = '\n', expect = 'EMPTY DB\n')
            return

        for airport in self.airports:

            expect_string = "Airport: {}\n".format(airport[0])
            self.read(delim = '\n', expect = expect_string)

            expect_string = "Connections: "
            
            if len(airport) > 1:
                for connection in airport[1]:

                    expect_string = expect_string + '{} ({}, {}), '.format(connection[0], connection[1], connection[2])

            if ',' in expect_string:
                expect_string = expect_string[:-2]

            expect_string = expect_string + '\n'

            self.read(delim = '\n', expect = expect_string)

            self.read(delim = '\n', expect = '\n')

        self.read(delim = '\n', expect = 'OK\n')


    def findRoutes(self):

        if len(self.airports) == 0:

            self.write('15/ABC/DEF\n')
            self.read(delim = '\n', expect = 'EMPTY DB\n')
            return

        if len(self.airports) ==1:
            return

        results = False

        fromCodeNum = random.randint(0, len(self.airports)-1)

        fromCode = self.airports[fromCodeNum][0]

        destinationCodeNum = random.randint(0, len(self.airports)-1)

        while destinationCodeNum == fromCodeNum:
            destinationCodeNum = random.randint(0, len(self.airports)-1)

        destinationCode = self.airports[destinationCodeNum][0]

        self.write('15/{}/{}\n'.format(fromCode, destinationCode))

        if len(self.airports[fromCodeNum]) == 1:
            self.read(delim = '\n', expect = '\n')
            self.read(delim = '\n', expect = 'NO RESULTS\n')
            return

        for firstHops in self.airports[fromCodeNum][1]:

            cost = firstHops[1]
            duration = firstHops[2]

            if firstHops[0] == destinationCode:

                results = True

                expect_string = '{} - {}: ({}, {})\n'.format(fromCode, destinationCode, cost, duration)
                self.read(delim = '\n', expect = expect_string)
                continue

            for connectionAirport in self.airports:

                if connectionAirport[0] == firstHops[0]:
                    break

            if len(connectionAirport) == 1:
                continue

            for nextHop in connectionAirport[1]:

                if nextHop[0] == destinationCode:

                    expect_string = '{} - {} - {}: ({}, {})\n'.format(fromCode, firstHops[0], destinationCode,
                                                                cost+ nextHop[1], duration + nextHop[2])

                    self.read(delim = '\n', expect = expect_string)

                    results = True
                    break


        self.read(delim = '\n', expect = '\n')

        if results:
            self.read(delim = '\n', expect = 'OK\n')
        else:
            self.read(delim = '\n', expect = 'NO RESULTS\n')

