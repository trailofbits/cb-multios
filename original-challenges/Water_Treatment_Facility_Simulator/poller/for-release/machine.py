#!/usr/bin/env python

from generator.actions import Actions
from random import *
import struct
import ctypes as ct

class WTFS():
    def __init__(self):
        self.MAX_VALVE_INPUT = 5
        self.MAX_VALVE_OUTPUT = 5
        self.MAX_FILTERS = 10
        self.SQFT_PER_FILTER = 50

        class PlantSystem(ct.Structure):
            pass

        PlantSystem._fields_ = [
		# system type
                ("Type", ct.c_ubyte),

                # system name
                ("Name", ct.c_char * 32),

                # Headworks
                ("TssReductionPct", ct.c_double),

                # Activated Sludge Process
                ("AerationPct", ct.c_double),
                ("AerationMaxScfm", ct.c_double),
                ("GlycerinRate", ct.c_double),
                ("AlumRate", ct.c_double),

                # Filter values
                ("GpmPerSqft", ct.c_double),
                ("NumActiveFilters", ct.c_ubyte),
                ("MaxFilters", ct.c_ubyte),

                # Disinfection values
                ("SuccessfulDisinfection", ct.c_ubyte),
                ("ChlorineRate", ct.c_double),
                ("ChlorineResidual", ct.c_double),

                # Effluent
                ("QualityFailures", ct.c_ubyte),

                # valve outputs
                ("Output", ct.POINTER(PlantSystem) * self.MAX_VALVE_OUTPUT),

                ("Flow", ct.c_double),
                ("Cbod", ct.c_double),
                ("Tss", ct.c_double),
                ("Tn", ct.c_double),
                ("Tp", ct.c_double),

		# valve inputs and output states
                ("Input", ct.POINTER(PlantSystem) * self.MAX_VALVE_INPUT),
                ("PctOpen", ct.c_double * self.MAX_VALVE_OUTPUT)
            ]

        self.dll = ct.CDLL('build/patched/so/CROMU_00048.so')
	self.Influent = PlantSystem.in_dll(self.dll, 'Influent')
	self.Headworks = PlantSystem.in_dll(self.dll, 'Headworks')
	self.HeadworksOutputValve = PlantSystem.in_dll(self.dll, 'HeadworksOutputValve')
	AspArray = PlantSystem * 5
	self.Asp = AspArray.in_dll(self.dll, 'Asp')
	self.AspOutputValve = PlantSystem.in_dll(self.dll, 'AspOutputValve')
	FilterArray = PlantSystem * 5
	self.Filter = FilterArray.in_dll(self.dll, 'Filter')
	self.FilterOutputValve = PlantSystem.in_dll(self.dll, 'FilterOutputValve')
	DisinfectionArray = PlantSystem * 5
	self.Disinfection = DisinfectionArray.in_dll(self.dll, 'Disinfection')
	self.DisinfectionOutputValve = PlantSystem.in_dll(self.dll, 'DisinfectionOutputValve')
	self.Effluent = PlantSystem.in_dll(self.dll, 'Effluent')
        SB = ct.c_char * 8192
	self.StatusBuf = SB.in_dll(self.dll, 'StatusBuf')

        self.InitPlant = self.dll.InitPlant
        self.InitPlant.argtypes = None
        self.InitPlant.restype = None

        self.RunSimStep = self.dll.RunSimStep
        self.RunSimStep.argtypes = None
        self.RunSimStep.restype = ct.c_ubyte

        self.GetValvePctFlow = self.dll.GetValvePctFlow
        self.GetValvePctFlow.argtypes = [ ct.POINTER(PlantSystem), ct.c_ubyte ]
        self.GetValvePctFlow.restype = ct.c_double

        self.SetValveOutput = self.dll.SetValveOutput
        self.SetValveOutput.argtypes = [ ct.POINTER(PlantSystem), ct.c_ubyte, ct.c_double ]
        self.SetValveOutput.restype = None

        self.ChangeAerationPercent = self.dll.ChangeAerationPercent
        self.ChangeAerationPercent.argtypes = [ ct.POINTER(PlantSystem), ct.c_double ]
        self.ChangeAerationPercent.restype = ct.c_double

        self.ChangeGlycerinRate = self.dll.ChangeGlycerinRate
        self.ChangeGlycerinRate.argtypes = [ ct.POINTER(PlantSystem), ct.c_double ]
        self.ChangeGlycerinRate.restype = ct.c_double

        self.ChangeAlumRate = self.dll.ChangeAlumRate
        self.ChangeAlumRate.argtypes = [ ct.POINTER(PlantSystem), ct.c_double ]
        self.ChangeAlumRate.restype = ct.c_double

        self.ChangeNumActiveFilters = self.dll.ChangeNumActiveFilters
        self.ChangeNumActiveFilters.argtypes = [ ct.POINTER(PlantSystem), ct.c_ubyte ]
        self.ChangeNumActiveFilters.restype = None

        self.ChangeChlorineRate = self.dll.ChangeChlorineRate
        self.ChangeChlorineRate.argtypes = [ ct.POINTER(PlantSystem), ct.c_double ]
        self.ChangeChlorineRate.restype = None

        self.SetSystemName = self.dll.SetSystemName
        self.SetSystemName.argtypes = [ ct.POINTER(PlantSystem), ct.c_char_p ]
        self.SetSystemName.restype = None

        self.RandomInfluent = self.dll.RandomInfluent
        self.RandomInfluent.argtypes = None
        self.RandomInfluent.restype = None

        self.seed_prng = self.dll.seed_prng
        self.seed_prng.argtypes = [ ct.c_uint ]
        self.seed_prng.restype = None

        self.CheckEffluentQuality = self.dll.CheckEffluentQuality
        self.CheckEffluentQuality.argtypes = None
        self.CheckEffluentQuality.restype = None

	self.PrintPlantStatusBuf = self.dll.PrintPlantStatusBuf
	self.PrintPlantStatusBuf.argtypes = None
	self.PrintPlantStatusBuf.restype = ct.c_char_p

class MyClass(Actions):

    def start(self):
        #self.delay(100)
        self.SimStepCount = 0
	self.Wtfs = WTFS()
	self.Wtfs.seed_prng(ct.c_uint(struct.unpack('<L', self.magic_page[0:4])[0]))
	self.Wtfs.InitPlant()
	self.Wtfs.RunSimStep()
	self.CheckSchematic()
	self.CheckStatus()
	self.CheckBanner()
	self.CheckMainMenu()

    def RunGoodSim(self):
        self.comment("RunGoodSim")
        for i in range (0,24):
            self.Wtfs.RunSimStep()
            self.CalculateBestOperatingParameters()
            self.write("8\n")
            self.SimStepCount += 1
            self.Wtfs.RunSimStep()
            self.Wtfs.CheckEffluentQuality()
            self.Wtfs.RandomInfluent()
            if i < 23:
                self.CheckMainMenu()
                self.write("2\n")
                self.CheckStatus()
                self.CheckMainMenu()

        # end the simulation
        self.CheckMainMenu()
        self.write("9\n")

	if self.Wtfs.Effluent.QualityFailures > 5:
            self.read(delim="\n", expect="There were {} hours with sub-standard water quality levels. You Failed!\n".format(self.Wtfs.Effluent.QualityFailures))
        else:
            self.read(delim="\n", expect="Congratulations!  You've successfully operated the plant for 24 hours.  You Win!\n")

    def RunBadSim(self):
        self.comment("RunBadSim")
        for i in range (0,24):
            self.Wtfs.RunSimStep()
            self.write("8\n")
            self.SimStepCount += 1
            self.Wtfs.CheckEffluentQuality()
            if i < 23:
                self.CheckMainMenu()
                self.Wtfs.RunSimStep()
                self.Wtfs.RandomInfluent()
                self.write("2\n")
                self.CheckStatus()
                self.CheckMainMenu()

        # end the simulation
        self.CheckMainMenu()
        self.write("9\n")

	if self.Wtfs.Effluent.QualityFailures > 5:
            self.read(delim="\n", expect="There were {} hours with sub-standard water quality levels. You Failed!\n".format(self.Wtfs.Effluent.QualityFailures))
        else:
            self.read(delim="\n", expect="Congratulations!  You've successfully operated the plant for 24 hours.  You Win!\n")

    def TestInvalid(self):
        rnd = randint(0,2)

        if rnd == 0:
            self.SetInvaildAerationRate()
        elif rnd == 1:
            self.SetInvaildGlycerinRate()
        elif rnd == 2:
            self.SetInvaildAlumRate()

    def SetInvaildAerationRate(self):
        self.comment("SetInvalidAerationRate")
        self.write("3\n")
        self.CheckAspMenu()
        self.write("1\n")
        self.read(delim=": ", expect="Which ASP 0-2: ")
        self.write("{:d}\n".format(randint(0,2)))
        self.read(delim=": ", expect="New aeration percent: ")
        self.write("{:0.2f}\n".format(uniform(100.1,200.0)))
        self.CheckAspMenu()
        self.write("4\n")
        self.CheckMainMenu()
	# check the plant status which should still have the same values
	# as before since the Aeration set will have failed
        self.write("2\n")
	self.CheckStatus()
        self.CheckMainMenu()

    def SetInvaildGlycerinRate(self):
        self.comment("SetInvalidGlycerineRate")
        self.write("3\n")
        self.CheckAspMenu()
        self.write("2\n")
        self.read(delim=": ", expect="Which ASP 0-2: ")
        self.write("{:d}\n".format(randint(0,2)))
        self.read(delim=": ", expect="New glycerin rate (0-100 gallons/hr): ")
        self.write("{:0.2f}\n".format(uniform(100.1,200.0)))
        self.CheckAspMenu()
        self.write("4\n")
        self.CheckMainMenu()
	# check the plant status which should still have the same values
	# as before since the Aeration set will have failed
        self.write("2\n")
	self.CheckStatus()
        self.CheckMainMenu()

    def SetInvaildAlumRate(self):
        self.comment("SetInvalidAlumRate")
        self.write("3\n")
        self.CheckAspMenu()
        self.write("3\n")
        self.read(delim=": ", expect="Which ASP 0-2: ")
        self.write("{:d}\n".format(randint(0,2)))
        self.read(delim=": ", expect="New alum rate (0-100 gallons/hr): ")
        self.write("{:0.2f}\n".format(uniform(100.1,200.0)))
        self.CheckAspMenu()
        self.write("4\n")
        self.CheckMainMenu()
	# check the plant status which should still have the same values
	# as before since the Aeration set will have failed
        self.write("2\n")
	self.CheckStatus()
        self.CheckMainMenu()

    def CalculateBestOperatingParameters(self):
        # Start with ASP settings

        # Move to the ASP control menu
        self.write("3\n")
        self.CheckAspMenu()

        for Asp in range(0,3):
            InputValvePct = self.Wtfs.GetValvePctFlow(self.Wtfs.HeadworksOutputValve, ct.c_ubyte(Asp))
            CbodPerHr = self.Wtfs.Influent.Cbod / 24.0 * InputValvePct
            TnPerHr = self.Wtfs.Influent.Tn / 24.0 * InputValvePct
            TpPerHr = self.Wtfs.Influent.Tp / 24.0 * InputValvePct
#            print "Cbod {:8.2f} {:8.2f} {:8.2f}\n".format(self.Wtfs.Influent.Cbod,self.Wtfs.Influent.Tn,self.Wtfs.Influent.Tp)
#            print "CbodPerHr {:8.2f} {:8.2f} {:8.2f}\n".format(CbodPerHr,TnPerHr,TpPerHr)
            CbodDemand = 2.0 * CbodPerHr
            TnDemand = 4.6 * TnPerHr
            PctAeration = (CbodDemand + TnDemand) / 0.45 / 0.188 / 4800.0 * 100.0
            if (PctAeration > 100.0):
                PctAeration = 100.0
            GlycerinRate = 6.5 * TnPerHr / 9.78
            if (GlycerinRate > 100.0):
                GlycerinRate = 100.0
            AlumRate = 0.9 * TpPerHr / 0.49
            if (AlumRate > 100.0):
                AlumRate = 100.0

            # set the aeration rate
            self.write("1\n")
            self.read(delim=": ", expect="Which ASP 0-2: ")
            self.write("{:d}\n".format(Asp))
            self.read(delim=": ", expect="New aeration percent: ")
            self.write("{:0.2f}\n".format(PctAeration))
            self.CheckAspMenu()
            self.Wtfs.ChangeAerationPercent(self.Wtfs.Asp[Asp], float("{:0.2f}\n".format(PctAeration)))

            # set the glycerin
            self.write("2\n")
            self.read(delim=": ", expect="Which ASP 0-2: ")
            self.write("{:d}\n".format(Asp))
            self.read(delim=": ", expect="New glycerin rate (0-100 gallons/hr): ")
            self.write("{:0.2f}\n".format(GlycerinRate))
            self.CheckAspMenu()
            self.Wtfs.ChangeGlycerinRate(self.Wtfs.Asp[Asp], float("{:0.2f}\n".format(GlycerinRate)))
            
            # set the Alum
            self.write("3\n")
            self.read(delim=": ", expect="Which ASP 0-2: ")
            self.write("{:d}\n".format(Asp))
            self.read(delim=": ", expect="New alum rate (0-100 gallons/hr): ")
            self.write("{:0.2f}\n".format(AlumRate))
            self.CheckAspMenu()
            self.Wtfs.ChangeAlumRate(self.Wtfs.Asp[Asp], float("{:0.2f}\n".format(AlumRate)))

        # return to the main menu
        self.write("4\n")
        self.CheckMainMenu()

        # Move to the Filter control menu
        self.write("4\n")
        self.CheckFilterMenu()

        for Filter in range(0,3):
            # turn on all the filters
            self.write("1\n")
            self.read(delim=": ", expect="Which Filter 0-2: ")
            self.write("{:d}\n".format(Filter))
            self.read(delim=": ", expect="How many filters (0-{:d}): ".format(self.Wtfs.Filter[Filter].MaxFilters))
            self.write("{:d}\n".format(self.Wtfs.Filter[Filter].MaxFilters))
            self.CheckFilterMenu()
            self.Wtfs.ChangeNumActiveFilters(self.Wtfs.Filter[Filter], self.Wtfs.Filter[Filter].MaxFilters)

        # return to the main menu
        self.write("2\n")
        self.CheckMainMenu()

	# Move to the Disinfection control menu
        self.write("5\n")
        self.CheckDisinfectionMenu()

        for Tank in range(0,3):
            InputValvePct = self.Wtfs.GetValvePctFlow(self.Wtfs.FilterOutputValve, ct.c_ubyte(Tank))
            # Calculate the apporpriate chlorine rate
            # first, assume all Tn was removed by the ASP, so no chlorine is used by Tn
            ChlorineMass = 0
            # then add the mass for the flow rate we're seeing
            ChlorineMass = self.Wtfs.Influent.Flow * 8.34 * 13.0 * InputValvePct
            # then add enough ChlorineMass to give us a final concentration of 4 mg/l
            # Calculate the Chlorine Rate (0-100%) that will get us there
            ChlorineRate = (ChlorineMass / (76.1 * 0.12 * 24)) / 6.0 * 100.0
            if (ChlorineRate > 100.0):
		ChlorineRate = 100.0

            # set the rate in the CB and in the poller
            self.write("1\n")
            self.read(delim=": ", expect="Which Disinfection system 0-2: ")
            self.write("{:d}\n".format(Tank))
            self.read(delim=": ", expect="New chlorine rate (0-100): ")
            self.write("{:0.2f}\n".format(ChlorineRate))
            self.CheckDisinfectionMenu()
            self.Wtfs.ChangeChlorineRate(self.Wtfs.Disinfection[Tank], float("{:0.2f}\n".format(ChlorineRate)))

        # return to the main menu
        self.write("2\n")
        self.CheckMainMenu()
            
    def CheckValves(self):
        self.comment("CheckValves")
        # run through all of the valves and make sure they're funcitoning
        self.write("6\n")
	self.CheckValvesMenu()

        # keep track of any valve check failures
        ValveCheckFail = 0

	# V1
	OutputPct = 0.0
        for Output in range(0,3):
            self.write("1\n")
            self.read(delim=": ", expect="Valve Output: ")
            self.write("{:d}\n".format(Output))
            self.read(delim=": ", expect="Percent Open (0.00-100.00):")
            PctOpen = uniform(0.0,100.0)
            self.write("{:0.2f}\n".format(PctOpen))
            self.CheckValvesMenu()
            self.Wtfs.SetValveOutput(self.Wtfs.HeadworksOutputValve, Output, PctOpen)
            OutputPct += PctOpen
        if OutputPct < 100.0:
            ValveCheckFail = 1
	# V2
        for Output in range(0,3):
            self.write("2\n")
            self.read(delim=": ", expect="Valve Output: ")
            self.write("{:d}\n".format(Output))
            self.read(delim=": ", expect="Percent Open (0.00-100.00):")
            PctOpen = uniform(0.0,100.0)
            self.write("{:0.2f}\n".format(PctOpen))
            self.CheckValvesMenu()
            self.Wtfs.SetValveOutput(self.Wtfs.AspOutputValve, Output, PctOpen)
            OutputPct += PctOpen
        if OutputPct < 100.0:
            ValveCheckFail = 1
	# V3
        for Output in range(0,2):
            self.write("3\n")
            self.read(delim=": ", expect="Valve Output: ")
            self.write("{:d}\n".format(Output))
            self.read(delim=": ", expect="Percent Open (0.00-100.00):")
            PctOpen = uniform(0.0,100.0)
            self.write("{:0.2f}\n".format(PctOpen))
            self.CheckValvesMenu()
            self.Wtfs.SetValveOutput(self.Wtfs.FilterOutputValve, Output, PctOpen)
            OutputPct += PctOpen
        if OutputPct < 100.0:
            ValveCheckFail = 1
	# V4
        for Output in range(0,2):
            self.write("4\n")
            self.read(delim=": ", expect="Valve Output: ")
            self.write("{:d}\n".format(Output))
            self.read(delim=": ", expect="Percent Open (0.00-100.00):")
            PctOpen = uniform(0.0,100.0)
            self.write("{:0.2f}\n".format(PctOpen))
            self.CheckValvesMenu()
            self.Wtfs.SetValveOutput(self.Wtfs.DisinfectionOutputValve, Output, PctOpen)
            OutputPct += PctOpen
        if OutputPct < 100.0:
            ValveCheckFail = 1

        # return to the main menu and check the valve settings
        self.write("5\n")
	self.CheckMainMenu()
        self.write("2\n")
	self.CheckStatus()
	self.CheckMainMenu()

        # try a sim run and make sure we get a valve check failure if we expect one
        if ValveCheckFail: 
            self.write("8\n")
            self.read(delim="\n", expect="A valve's output percentages don't total to at least 100%.  Can't run the simulation.\n")
	    self.CheckMainMenu()

    def random_string(self, min_length, max_length):
        chars = map(chr, range(48,57)+range(65,90)+range(97,122))
        str = ''
        while len(str) < min_length:
            str = ''.join(choice(chars) for _ in range(randint(min_length, max_length))).rstrip()
        return str

    def CheckRenameSystems(self):
        self.comment("CheckRenameSystems")
	# rename each system
        self.write("7\n")
	self.CheckRenameMenu()

	# Influent
        NewName = self.random_string(2,20)
        self.write("1\n")
        self.read(delim=": ", expect="New Influent name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.Influent, NewName);
	self.CheckRenameMenu()

	# Headworks
        NewName = self.random_string(2,20)
        self.write("2\n")
        self.read(delim=": ", expect="New Headworks name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.Headworks, NewName);
	self.CheckRenameMenu()
	
	# ASPs
        NewName = self.random_string(2,20)
        self.write("3\n")
        self.read(delim=": ", expect="Which ASP 0-2: ")
        self.write("0\n")
        self.read(delim=": ", expect="New ASP0 name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.Asp[0], NewName);
	self.CheckRenameMenu()

        NewName = self.random_string(2,20)
        self.write("3\n")
        self.read(delim=": ", expect="Which ASP 0-2: ")
        self.write("1\n")
        self.read(delim=": ", expect="New ASP1 name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.Asp[1], NewName);
	self.CheckRenameMenu()
	
        NewName = self.random_string(2,20)
        self.write("3\n")
        self.read(delim=": ", expect="Which ASP 0-2: ")
        self.write("2\n")
        self.read(delim=": ", expect="New ASP2 name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.Asp[2], NewName);
	self.CheckRenameMenu()
	
	# Filters
        NewName = self.random_string(2,20)
        self.write("4\n")
        self.read(delim=": ", expect="Which Filter 0-2: ")
        self.write("0\n")
        self.read(delim=": ", expect="New Filter0 name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.Filter[0], NewName);
	self.CheckRenameMenu()

        NewName = self.random_string(2,20)
        self.write("4\n")
        self.read(delim=": ", expect="Which Filter 0-2: ")
        self.write("1\n")
        self.read(delim=": ", expect="New Filter1 name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.Filter[1], NewName);
	self.CheckRenameMenu()
	
        NewName = self.random_string(2,20)
        self.write("4\n")
        self.read(delim=": ", expect="Which Filter 0-2: ")
        self.write("2\n")
        self.read(delim=": ", expect="New Filter2 name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.Filter[2], NewName);
	self.CheckRenameMenu()
	
	# Disinfection systems
        NewName = self.random_string(2,20)
        self.write("5\n")
        self.read(delim=": ", expect="Which Disinfection system 0-2: ")
        self.write("0\n")
        self.read(delim=": ", expect="New Disinfection0 name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.Disinfection[0], NewName);
	self.CheckRenameMenu()

        NewName = self.random_string(2,20)
        self.write("5\n")
        self.read(delim=": ", expect="Which Disinfection system 0-2: ")
        self.write("1\n")
        self.read(delim=": ", expect="New Disinfection1 name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.Disinfection[1], NewName);
	self.CheckRenameMenu()
	
        NewName = self.random_string(2,20)
        self.write("5\n")
        self.read(delim=": ", expect="Which Disinfection system 0-2: ")
        self.write("2\n")
        self.read(delim=": ", expect="New Disinfection2 name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.Disinfection[2], NewName);
	self.CheckRenameMenu()
	
	# Effluent
        NewName = self.random_string(2,20)
        self.write("6\n")
        self.read(delim=": ", expect="New Effluent name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.Effluent, NewName);
	self.CheckRenameMenu()
	
	# Valves
        NewName = self.random_string(2,20)
        self.write("7\n")
        self.read(delim=": ", expect="1. V1\n2. V2\n3. V3\n4. V4\nWhich valve: ")
        self.write("1\n")
        self.read(delim=": ", expect="New V1 name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.HeadworksOutputValve, NewName);
	self.CheckRenameMenu()

        NewName = self.random_string(2,20)
        self.write("7\n")
        self.read(delim=": ", expect="1. V1\n2. V2\n3. V3\n4. V4\nWhich valve: ")
        self.write("2\n")
        self.read(delim=": ", expect="New V2 name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.AspOutputValve, NewName);
	self.CheckRenameMenu()

        NewName = self.random_string(2,20)
        self.write("7\n")
        self.read(delim=": ", expect="1. V1\n2. V2\n3. V3\n4. V4\nWhich valve: ")
        self.write("3\n")
        self.read(delim=": ", expect="New V3 name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.FilterOutputValve, NewName);
	self.CheckRenameMenu()

        self.write("7\n")
        self.read(delim=": ", expect="1. V1\n2. V2\n3. V3\n4. V4\nWhich valve: ")
        self.write("4\n")
        self.read(delim=": ", expect="New V4 name: ")
        self.write(NewName + "\n")
	self.Wtfs.SetSystemName(self.Wtfs.DisinfectionOutputValve, NewName);
	self.CheckRenameMenu()

	# return to the main menu
        self.write("8\n")
	self.CheckMainMenu()

	# check the plant status to see if the system names match
        self.write("2\n")
	self.CheckStatus()
	self.CheckMainMenu()

    def EndSimEarly(self):
        self.comment("EndSimEarly")
        self.write("9\n")
        self.read(delim='\n', expect='Ending simulation at less than 24 hours.\n')

    def CheckStatus(self):
	self.buf = self.Wtfs.PrintPlantStatusBuf()
        self.buf += '\n'
	self.read(length=len(self.buf), expect=self.buf)

    def CheckSchematic(self):

        schematic = "Plant Schematic\n"
        schematic += "#####################################################################################################################################\n"
        schematic += "                                         --------                -----------               -----------------                         \n"
        schematic += "                                -------> | ASP1 | ------  -----> | Filter1 | -----  -----> | Disinfection1 | -----                   \n"
        schematic += "                                |        --------      |  |      -----------     |  |      -----------------     |                   \n"
        schematic += "                                |                      |  |                      |  |                            |                   \n"
        schematic += "                                |                      |  |                      |  |                            |                   \n"
        schematic += "                                0                      v  0                      v  0                            v                   \n"
        schematic += "            -------------     ------     --------     ------     -----------    ------     -----------------    ------               \n"
        schematic += "Influent -> | Headworks | --> | V1 | 1-> | ASP2 | --> | V2 | 1-> | Filter2 | -> | V3 | 1-> | Disinfection2 | -> | V4 | 0-> Effluent  \n"
        schematic += "            -------------     ------     --------     ------     -----------    ------     -----------------    ------               \n"
        schematic += "                                2                      ^  2                      ^  2                            ^                   \n"
        schematic += "                                |                      |  |                      |  |                            |                   \n"
        schematic += "                                |                      |  |                      |  |                            |                   \n"
        schematic += "                                |        --------      |  |      -----------     |  |      -----------------     |                   \n"
        schematic += "                                -------> | ASP3 | ------  -----> | Filter3 | -----  -----> | Disinfection3 | -----                   \n"
        schematic += "                                         --------                -----------               -----------------                         \n"
        schematic += "#####################################################################################################################################\n"

	self.read(length=len(schematic), expect=schematic)
	
    def CheckBanner(self):
        banner =  "Welcome to the Wastewater Treatement Plant Simulator\n"
        banner += "###################################################\n"
        banner += "Your job is to take the plant described in the schematic above and make potable water.\n"
        banner += "The simulation starts with a random plant status.\n"
        banner += "\n"
	self.read(length=len(banner), expect=banner)

    def CheckMainMenu(self):
        menu =  "Wastewater Treatment Plant Simulation\n"
        menu += "Simulation Hour {}\n".format(self.SimStepCount)
        menu += "1. Print plant schematic\n"
        menu += "2. Print plant status\n"
        menu += "3. Control Activated Sludge Process (ASP)\n"
        menu += "4. Control Filters\n"
        menu += "5. Control Disinfection\n"
        menu += "6. Control Valves\n"
        menu += "7. Rename System\n"
        menu += "8. Run Simulation Step\n"
        menu += "9. Exit\n"
        menu += "Selection: "
	self.read(length=len(menu), expect=menu)

    def CheckAspMenu(self):
        menu =  "1. Change aeration rate\n"
        menu += "2. Change glycerin rate\n"
        menu += "3. Change alum rate\n"
        menu += "4. Return to previous menu\n"
        menu += "Selection: "
	self.read(length=len(menu), expect=menu)

    def CheckRenameMenu(self):
        menu =  "1. Influent\n"
        menu += "2. Headworks\n"
        menu += "3. ASPs\n"
        menu += "4. Filters\n"
        menu += "5. Disinfections\n"
        menu += "6. Effluent\n"
        menu += "7. Valves\n"
        menu += "8. Return to previous menu\n"
        menu += "Selection: "
	self.read(length=len(menu), expect=menu)

    def CheckFilterMenu(self):
        menu =  "1. Change active filter count\n"
        menu += "2. Return to previous menu\n"
        menu += "Selection: "
	self.read(length=len(menu), expect=menu)

    def CheckDisinfectionMenu(self):
        menu =  "1. Change chlorine rate\n"
        menu += "2. Return to previous menu\n"
        menu += "Selection: "
	self.read(length=len(menu), expect=menu)

    def CheckValvesMenu(self):
        menu =  "1. Change valve V1 output percentage\n"
        menu += "2. Change valve V2 output percentage\n"
        menu += "3. Change valve V3 output percentage\n"
        menu += "4. Change valve V4 output percentage\n"
        menu += "5. Return to previous menu\n"
        menu += "Selection: "
	self.read(length=len(menu), expect=menu)

