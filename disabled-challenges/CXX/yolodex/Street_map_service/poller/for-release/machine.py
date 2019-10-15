from generator.actions import Actions
import random
import string

class map:
	def __init__(self, newName):
		self.mapName = newName
		self.roadList = []
	def setMapName(self, newName):
		self.mapName = newName
		return
	def getMapName(self):
		return self.mapName
	def addroad(self, roadName, length):
		newRoad = [roadName, length, [],[]]
		self.roadList.append(newRoad)
		return
	def getRoadCount(self):
		return len(self.roadList)
	def getRoadByCount(self, count):
		return self.roadList[count]
	def getAddressCount(self, roadInt):
		return len(self.roadList[roadInt][3])
	def intersectionCount(self, roadOrd):
		return len(self.roadList[roadOrd][2])
	def isInRouteList(self, roadList, intersectionRoad):
		for i in roadList:
			if i[0] == intersectionRoad:
				return True
		return False

	def get_route(self, targetRoad, startRoad):
		count = 1
		curRouteListCount = 1
		#routeList [roadOrd thisRoad, routeListOrd parent] 
		routeList = []
		curRouteList = [startRoad, -1]
		routeList.append(curRouteList)
		count += 1
		curRoad = -1
		intersectionRoad = -1
		curIntersection = -1
		while True:
			curRoad = curRouteList[0]
			#intersection list is [2], otherroadOrd is [0]
			#for each intersection in curRoad intersectionList
			for i in self.roadList[curRoad][2]:
				#intersectionRoad = intersection[otherRoad]
				intersectionRoad = i[0]
				if not(self.isInRouteList(routeList, intersectionRoad)):
					if count > 32:
						return -1,-1
					#newrouteList = [intersecionRoadOrd, parentRouteListOrd]
					newrouteList = [intersectionRoad, (curRouteListCount-1)]
					routeList.append(newrouteList)
					count += 1
				if intersectionRoad == targetRoad:
					return count, routeList
			if (curRouteListCount < (count-1)):
				curRouteListCount += 1
				curRouteList = routeList[(curRouteListCount-1)]
			else:
				return -1,-1
		return -1,-1

class Mapper(Actions):
#	myMap = map
	oMap = map("Newville") 
	#from example in understanding a poll generator.md
	def random_string(self, size):
		chars = string.letters + string.digits
		return ''.join(random.choice(chars) for _ in range(size))
	def random_digits(self, size):
		chars = string.digits
		return ''.join(random.choice(chars) for _ in range(size))
	def writeFloat(self, thisFloat):
		if thisFloat == '':
			self.write('\n')
			thisFloat = '0'
		elif len(thisFloat) < 10:
			self.write(thisFloat + '\n')
		else:					
			self.write (thisFloat)
		return thisFloat
	def selectRoad(self, legitOnly = False):
		#dont call if there are no roads in the roadlist
		roadCount = self.oMap.getRoadCount()
		if (roadCount == 0):
			return -1
		if (roadCount==1):
			self.read(delim='\n', expect='Only road selected.\n')
			return 0
		while(True):
			self.read(delim='\n', expect="Select Road by (N)umber, or (L)ist or (0)Exit.\n")
			self.read(delim='\n', expect="choice:\n")
			if (legitOnly):
				choice = 0
				roadnum = random.randint(1,(roadCount))
			else:
				choice = random.randint(0,2)
				roadnum = random.randint(0,(roadCount+1))
			if choice == 0:
				#number
				self.write("N\n")
				self.read(delim='\n', expect='1-' + str(roadCount) + ':\n')
				self.write(str(roadnum) + '\n')
				if roadnum == 0:
					self.read(delim='\n', expect='Invalid number. (0)\n')
				elif roadnum > roadCount:
					self.read(delim='\n', expect='Invalid number. (out of range)\n')
				else:
					#return the index of the road selected
					return (roadnum-1)
			if choice == 1:
				#list
				self.write("L\n")
				self.printRoads()
			if choice == 2:
				#exit
				self.write("0\n")
				return -1

	def printRoads(self):
		self.read(delim='\n', expect="The map " + self.oMap.getMapName() + " contains " + str(self.oMap.getRoadCount()) + " roads.\n")
		#ret = "The map " + self.oMap.getMapName() + " contains " + str(self.oMap.getRoadCount()) + " roads.\n"
		count = 1
		for i in self.oMap.roadList:
			self.read(delim='\n', 
				expect='(' + str(count) + ')' + " " + i[0] + " is " + str(i[1]) + ".00000 units long\n")
			count += 1
		return

	def printIntersection(self, roadOrd):
		road = self.oMap.roadList[roadOrd]
		#ret = 'The road ' + self.oMap.roadList[roadOrd][0] + ' contains ' + \
		#								str(len(self.oMap.roadList[roadOrd][2])) + ' intersections.\n'
		self.read(delim='\n', expect='The road ' + road[0] + ' contains ' + str(self.oMap.intersectionCount(roadOrd))  + ' intersections.\n')
		#str(len(self.oMap.roadList[roadOrd][2]))
		count = 1
		for i in road[2]:
			thisIntersection = i
			#(count) @roadname intersects @otherroadname
			#intersection [otherRoadOrd, prevIntersectionInt, distancetoprev, nextIntersectionInt, distancetonext]
			self.read(delim='\n', 
				expect='(' + str(count) + ')\t' + road[0] + ' intersects ' + self.oMap.roadList[i[0]][0] + '\n')
			if i[1] != -1:

				prevIntersectionOrd = i[1]
				prevIntersection = road[2][prevIntersectionOrd]
				prevIntersectionOtherRoadOrd = prevIntersection[0]
				prevIntersectionOtherRoadName = self.oMap.roadList[prevIntersectionOtherRoadOrd][0]
				self.read(delim='\n', 
					expect='\t\t' + str(i[2]) + '.00000 units after the intersection of ' + self.oMap.roadList[road[2][i[1]][0]][0] + '\n')
			if i[3] != -1:
				nextIntersectionOrd = i[3]
				nextIntersection = road[2][nextIntersectionOrd]
				nextIntersectionOtherRoadOrd = nextIntersection[0]
				nextIntersectionOtherRoadName = self.oMap.roadList[nextIntersectionOtherRoadOrd][0]
				self.read(delim='\n', 
					expect='\t\t' + str(i[4]) + '.00000 units before the intersection of ' + nextIntersectionOtherRoadName + '\n')
			count += 1
		return 

	def selectIntersection(self, roadOrd, legitOnly= False):
		interCount = self.oMap.intersectionCount(roadOrd)
		if interCount == 0:
			self.read(delim='\n', expect='This road has no intersections to choose.\n')
			return -1

		while(True):
			if legitOnly:	
				choice = random.randint(1,2)
			else:
				choice = random.randint(0,2)
			self.read(delim='\n', expect='Select intersection by (N)umber, (L)ist, or set to N(O)TDEFINED.\n')
			self.read(delim='\n', expect='choice:\n')
			if legitOnly:
				internum = random.randint(1,interCount)
			else:
				internum = random.randint(0,interCount+1)
			#List
			if choice == 0:
				self.write('L\n')
				#self.read(delim='\n', expect=self.printIntersection(roadOrd))
				self.printIntersection(roadOrd)
			#number
			if choice == 1:
				self.write('N\n')
				self.read(delim='\n', expect='1-' + str(interCount) + ':\n')
				self.write(str(internum) + '\n')
				if internum == 0 :
					self.read(delim='\n', expect='Invalid number.\n')
					return -1
				if interCount >= internum:
					return (internum-1)
				self.read(delim='\n', expect='Invalid number.\n')
				return -1
			#notdefined
			if choice ==2:
				self.write('O\n')
				return -1
	def selectAddress(self, roadOrd, legitOnly):
		addressCount = self.oMap.getAddressCount(roadOrd)
		if addressCount == 0:
			return -1
		if addressCount == 1:
			self.read(delim='\n', expect='Only address on road was selected\n')
			return 0
		while(True):
			self.read(delim='\n', expect='Select address (N)umber (L)ist or (0)Exit: \n')
			if legitOnly:	
				choice = 1
			else:
				choice = random.randint(0,2)
			if choice == 0:
				#do listAddress
				self.write('L\n')
				self.printAddresses(roadOrd)
			if choice == 1:
				#do Number
				self.write('N\n')
				self.read(delim='\n', expect='1-' + str(addressCount) + ':\n')
				if legitOnly:
					addressnum = random.randint(1,addressCount)
				else:
					addressnum = random.randint(0,addressCount+1)
				self.write(str(addressnum) + '\n')
				if int(addressnum) == 0:
					self.read(delim='\n', expect='Invalid number. (0)\n')
					return -1
				elif addressnum <= addressCount:
					return (addressnum-1)
				else:
					self.read(delim='\n', expect='Invalid number. (out of range)\n')
					return -1
			if choice == 2:
				self.write('0\n')
				return -1
				#do exit



	def printAddresses(self, roadOrd):		
		road = self.oMap.roadList[roadOrd]
		#ret = 'The road ' + self.oMap.roadList[roadOrd][0] + ' contains ' + \
		#								str(len(self.oMap.roadList[roadOrd][2])) + ' intersections.\n'
		self.read(delim='\n', expect='The road ' + road[0] + ' contains ' + str(self.oMap.getAddressCount(roadOrd))  + ' addresses.\n')
		#str(len(self.oMap.roadList[roadOrd][2]))
		count = 1
		for i in road[3]:
			self.read(delim='\n', expect='(' + str(count) + ')\t' + i[1] + '\n')
			self.read(delim='\n', expect='\t' + str(i[0]) + ' ' + road[0] + '\n')
			count = count + 1


######### /\ /\ /\ helper functs /\ /\ /\ ### \/ \/ \/ \/ \/ node functs \/ \/ \/ \/ #########
	def start(self):
		self.oMap = map("Newville")

	def finish(self):
		self.write('0\n')

	def Banner (self):
		self.read(delim='\n', expect='This is Mapper.\n')

	def choice(self):
		self.read(delim='\n', expect='choice:\n')

	def NAME_MAP(self):
		mapName = self.oMap.getMapName()
		self.write('A\n') 
		self.read(delim='\n', expect='Name:\n' )
		word = self.random_string(random.randint(1, 31))
		if len(word)==31:
			self.write(word)
		else:
			self.write(word + '\n')
		self.read(delim='\n', expect='Map ' + mapName + ' is now named ' + word + '.\n')
		self.oMap.setMapName(word)

	def NAME_MAP_0LEN(self):
		mapName = self.oMap.getMapName()
		self.write('A\n') 
		self.read(delim='\n', expect='Name:\n' )
		self.write('\n')
		self.read(delim='\n', expect='Name not set.\n')

	def ADDROAD(self,legitOnly = False):
		self.write('B\n')
		if (self.oMap.getRoadCount() >= 41):
			self.read(delim='\n', expect='No more roads allowed.(Limit)\n')
			return
		self.read(delim='\n', expect='Road Name:\n')
		if legitOnly:
			roadName = self.random_string(random.randint(1, 10))
			length = self.random_digits(random.randint(1, 4))
		else:
			roadName = self.random_string(random.randint(0, 31))
			length = self.random_digits(random.randint(0, 9))
		if len(roadName)==31:
			self.write(roadName)
		else:
		 	self.write(roadName+'\n')
		self.read(delim='\n', expect='Road Length:\n')
		self.write(length+'\n')
		if( (length=='') or (roadName=='') or (int(length)==0) ):
			self.read(delim='\n', expect='Invalid Road.\n')
		else:
			self.oMap.addroad(roadName, int(length))

	def GenerateMapContext(self):
		self.read(delim='\n', expect='choice:\n')
		for i in range(5):
			self.ADDROAD(True)
			self.choice()
		for i in range(10):
			self.ADDINTERSECTION(True)
			self.choice()
		for i in range(10):
			self.ADDADDRESS(True)
			self.choice()
		self.ADDADDRESS()

	def ADDADDRESS (self, legitOnly = False): 
		self.write('C\n')
		self.read (delim='\n', expect='Street Number: \n')
		roadCount = self.oMap.getRoadCount()
		if legitOnly:
			number = self.random_digits(random.randint(1,4))
			prevDistance = self.random_digits( random.randint(1,4) )
			nextDistance = self.random_digits( random.randint(1,4) )
		else:
			number = self.random_digits(random.randint(0,8))
			prevDistance = self.random_digits( random.randint(0,10) )
			nextDistance = self.random_digits( random.randint(0,10) )
		if ( len(number) < 8 ):
			self.write (number + '\n')
		else:
			self.write(number)
		if number == '':
			number = '0'
		if ( int(number) == 0 ):
			self.read (delim='\n', expect='Invalid number.\n')
			return
		self.read (delim='\n', expect='Resident: \n')
		if legitOnly:
			resident = self.random_string(random.randint(1, 10))
		else:
			resident = self.random_string(random.randint(0, 31))
		if(len(resident)<31):
			self.write(resident + '\n')
		else:
			self.write(resident)
		if resident == '':
			self.read (delim='\n', expect='Invalid resident.\n')
			return 		
		roadOrd = self.selectRoad(legitOnly)
		if roadOrd == -1:
			self.read (delim='\n', expect='Invalid road.\n')
			return
		if (self.oMap.getAddressCount(roadOrd) >= 41):
			self.read (delim='\n', expect='Invalid road.(Limit)\n')
			return
		prevIntersectionOrd = self.selectIntersection(roadOrd,legitOnly)
		if prevIntersectionOrd != -1:
			self.read (delim='\n', expect='Distance to intersection: \n')
			prevDistance = self.writeFloat(prevDistance)
			if int(prevDistance) == 0:
				self.read (delim='\n', expect='Invalid distance\n')
				return
		nextIntersectionOrd = self.selectIntersection(roadOrd,legitOnly)
		if nextIntersectionOrd != -1:
			self.read (delim='\n', expect='Distance to intersection: \n')
			nextDistance = self.writeFloat(nextDistance)			
			if int(nextDistance) == 0:
				self.read (delim='\n', expect='Invalid distance\n')
				return
		if nextIntersectionOrd == -1:
			nextDistance = '0'
		if prevIntersectionOrd == -1:
			prevDistance = '0'	
		address = [int(number), resident, int(prevIntersectionOrd), int(prevDistance), int(nextIntersectionOrd), int(nextDistance) ]
		count = 0
		#insert after lower or equal number
		for i in self.oMap.roadList[roadOrd][3]:
			if  i[0] <= int(number):
				count = count + 1
			else:
				break
		self.oMap.roadList[roadOrd][3].insert(count, address)


	def ADDINTERSECTION(self,legitOnly = False):
		self.write('D\n')
		roadOrd1 = self.selectRoad(legitOnly)
		roadOrd2 = self.selectRoad(legitOnly)
		prevDistance1 = self.random_digits( random.randint(1,10) )
		nextDistance1 = self.random_digits( random.randint(1,10) )
		prevDistance2 = self.random_digits( random.randint(1,10) )
		nextDistance2 = self.random_digits( random.randint(1,10) )
		if 	( (roadOrd1 == -1) or (roadOrd2 == -1) or (roadOrd1 == roadOrd2) ):
			self.read (delim='\n', expect='Invalid intersection.\n')
			return
		road1InterCount = self.oMap.intersectionCount(roadOrd1)
		road2InterCount = self.oMap.intersectionCount(roadOrd2)
		if ( ( road1InterCount >= 41 ) or ( road2InterCount >= 41) ):
			self.read (delim='\n', expect='Invalid intersection. (Limit)\n')
			return
		self.read (delim='\n', expect='Prev intersection on road 1.\n')
		prevIntersectionOrd1 = self.selectIntersection(roadOrd1,legitOnly)
		if prevIntersectionOrd1 != -1:
			self.read (delim='\n', expect='Distance to prev\n')

			prevDistance1 = self.writeFloat(prevDistance1)

			# +1 to adjust for ord vs count
			#if prevIntersectionOrd isn't the last intersection
			if (prevIntersectionOrd1 + 1) < road1InterCount:
				#will point to self after add, but get fixed later
				nextIntersectionOrd1 = (prevIntersectionOrd1 + 1)
				self.read (delim='\n', expect='Distance to next\n')
				nextDistance1 = self.writeFloat(nextDistance1)

			else:
				nextIntersectionOrd1 = -1
				nextDistance1 = '0'
		#prevIntersectionOrd1 is -1		
		else:
			prevDistance1 = '0'
			if road1InterCount > 0:
				nextIntersectionOrd1 = 1
				self.read (delim='\n', expect='Distance to next\n')
				nextDistance1 = self.writeFloat(nextDistance1)

			else:
				nextIntersectionOrd1 = -1
				nextDistance1 = '0'

		self.read (delim='\n', expect='Prev intersection on road 2.\n')
		prevIntersectionOrd2 = self.selectIntersection(roadOrd2,legitOnly)
		if prevIntersectionOrd2 != -1:
			self.read (delim='\n', expect='Distance to prev\n')

			prevDistance2 = self.writeFloat(prevDistance2)

			#see above
			if (prevIntersectionOrd2 + 1) < road2InterCount:
				nextIntersectionOrd2 = (prevIntersectionOrd2 + 1)
				self.read (delim='\n', expect='Distance to next\n')
				nextDistance2 = self.writeFloat(nextDistance2)
			else:
				nextIntersectionOrd2 = -1
				nextDistance2 = '0'

		else:
			prevDistance2 = '0'
			if road2InterCount > 0:
				nextIntersectionOrd2 = 1
				self.read (delim='\n', expect='Distance to next\n')
				nextDistance2 = self.writeFloat(nextDistance2)
			else:
				nextIntersectionOrd2 = -1
				nextDistance2 = '0'
		

		road1 = self.oMap.roadList[roadOrd1]
		road2 = self.oMap.roadList[roadOrd2]

		#[name,length,[intersectionList],[addressList]]
		#intersection[otherRoadOrd, prevIntersectionInt, distancetoprev, nextIntersectionInt, distancetonext]
		intersection1 = [roadOrd2, prevIntersectionOrd1, int(prevDistance1), nextIntersectionOrd1, int(nextDistance1)]
		intersection2 = [roadOrd1, prevIntersectionOrd2, int(prevDistance2), nextIntersectionOrd2, int(nextDistance2)]
		#if I do an insert, I must fix all occurances of ordinals greater this insert (ord = old ord+1, because they are all now shifted by 1  
		#also I have to fix up prev and next on either side of insert
		#really I don't have to keep track of any of it, as they should be in order always. prev is just this-1, next is this+1
		road1[2].insert(prevIntersectionOrd1+1, intersection1)
		#fix up all other ords
		count = 0
		for i in road1[2]:
			i[1] = count - 1
			i[3] = count + 1
			count += 1
		road1[2][road1InterCount][3] = -1

		road2[2].insert(prevIntersectionOrd2+1, intersection2)
		#fix up all other ords
		count = 0
		for i in road2[2]:
			i[1] = count - 1
			i[3] = count + 1
			count += 1
		road2[2][road2InterCount][3] = -1

		
	def PRINTMAP(self): 
		self.write('E\n')
		self.read(delim='\n', expect='Map Info\n')
		self.read(delim='\n', expect='Map Name: ' + self.oMap.mapName + ' Number of Roads: ' + str(self.oMap.getRoadCount()) + '\n')
		self.read(delim='\n', expect='Road List:\n')
		count = 0
		for i in self.oMap.roadList:
			#print each road
			self.read(delim='\n', expect=i[0] + ' is ' + str(i[1]) + '.00000 units long\n')
			self.read(delim='\n', expect='IntersectionList:\n')
			self.printIntersection(count)	
			self.read(delim='\n', expect='AddressList:\n')
			self.printAddresses(count)
			count += 1	
		self.read(delim='\n', expect='End of road list\n')

	def DELETEROAD(self):
		pass 
	def DELETEADDRESS(self): 
		pass
	def DELETEINTERSECTION(self): 
		pass
	def FINDROUTE(self,legitOnly = True):
		self.write('I\n')
		self.read(delim='\n', expect='from address \n')
		thisRoad = self.selectRoad(legitOnly)
		if (thisRoad == -1):
			return
		thisAddress = self.selectAddress(thisRoad, legitOnly)
		if (thisAddress == -1):
			return
		self.read(delim='\n', expect='to address \n')
		nextRoad = self.selectRoad(legitOnly)
		if (nextRoad == -1):
			return
		nextAddress = self.selectAddress(nextRoad, legitOnly)
		if (nextAddress == -1):
			return
		if thisRoad == nextRoad:
			self.read(delim='\n', expect='Address is on the same road.\n')
			return
		count,thisList = self.oMap.get_route(thisRoad, nextRoad)
		if count == -1:
			self.read(delim='\n', expect='No valid route.\n')
			self.read(delim='\n', expect='Can\'t get there from here\n')
			self.read(delim='\n', expect='#############################\n')

			return
		#print route
		thisRouteList = thisList[-1]
		nextRouteList = thisList[thisRouteList[1]]
		#roadOrd name
		self.read(delim='\n', expect='Starting on ' + self.oMap.roadList[thisRouteList[0]][0] + '.\n')
		while (nextRouteList != -1):
			self.read(delim='\n', expect='head towards ' + self.oMap.roadList[nextRouteList[0]][0] + ' then turn on to ' + self.oMap.roadList[nextRouteList[0]][0] + '\n')
			thisRouteList = nextRouteList
			#well here lies a nasty python bug, thisList[-1] is back to the end of the list
			if nextRouteList[1] == -1:
				nextRouteList = -1
			else:
				nextRouteList = thisList[nextRouteList[1]]
		self.read(delim='\n', expect='You have arrived at your destination.\n')
		self.read(delim='\n', expect='#############################\n')
		return

