#!/usr/bin/env python

from generator.actions import Actions
import random
import string
import struct

instFmts = {
    "ALU":0,
    "FMT2":1,
}

aluOps = {
    "ADD":0,
    "ADC":1,
    "SUB":2,
    "SUC":3,
    "LSL":4,
    "LSR":5,
    "RSB":6,
    "RSC":7,
    "AND":8,
    "OR":9,
    "XOR":10,
    "NOT":11,
    "MIN":12,
    "MAX":13,
    "CLR":14,
    "SET":15,
}

fmt2Ops = {
    "JMP":0,
    "JAL":1,
    "LDI":2,
    "LMBD":3,
    "SCAN":4,
    "HALT":5,
    "RESERVED_1":6,
    "RESERVED_2":7,
    "RESERVED_3":8,
    "RESERVED_4":9,
    "RESERVED_5":10,
    "RESERVED_6":11,
    "RESERVED_7":12,
    "RESERVED_8":13,
    "RESERVED_9":14,
    "SLP":15,
}

def getLastArg(regOp):
    if(regOp == 1):
        return "R%d" % random.choice(range(32))
    else:
        return random.choice(range(0xffff))

def genInstruction():
    fmts = [aluOps, fmt2Ops]
    fmt = random.choice(fmts)
    regOp = random.choice([0,1])
    fmt = aluOps
    if fmt == aluOps:
        op = random.choice(fmt.keys())
        return "%s R%d R%d %s" % (op, random.choice(range(32)), random.choice(range(32)), getLastArg(regOp))
    else:
        print "FMT2"
    pass

def buildALUInstruction(inst):
    aluOpName,Rd,Rs1,Rs2 = inst.split()
    aluOp = aluOps[aluOpName]
    if Rs2[0] == "R":
        aluIO = 0
    else:
        aluIO = 1
    if(aluIO == 0):
        aluRS2 = int(Rs2[1:])
    else:
        aluRS2 = int(Rs2)
    aluRS1 = int(Rs1[1:])
    aluRD = int(Rd[1:])

    if aluIO == 1:
        return int("0x%0.8x" % (0 << (31-31)| (aluOp << (31-28)) | aluIO << (31-24) | aluRS2 << (31-23) | aluRS1 << (31-12) | aluRD << (31-4)), 16)
    else:
        return int("0x%0.8x" % (0 << (31-31)| (aluOp << (31-28)) | aluIO << (31-24) | aluRS2 << (31-20) | aluRS1 << (31-12) | aluRD << (31-4)), 16)

def buildLDIInstruction(inst):
    value = int(inst.split()[2])
    rd = int(inst.split()[1][1:])
    if int("0x%0.8x" % (0b001 << (31-31) | fmt2Ops["LDI"] << (31-28) | value << (31-23) | rd << (31-4)), 16) == -1:
        print "!!!!!!!!" + inst
    return int("0x%0.8x" % (0b001 << (31-31) | fmt2Ops["LDI"] << (31-28) | value << (31-23) | rd << (31-4)), 16)

def buildJMPInstruction(inst):
    branchTarget = inst.split()[1]
    if branchTarget[0] == "R":
        aluIO = 0
        branchTarget = int(branchTarget[1:])
    else:
        aluIO = 1
        branchTarget = int(branchTarget)

    if aluIO == 1:
        return int("0x%0.8x" % (0b001 << (31-31) | fmt2Ops["JMP"] << (31-28) | aluIO << (31-24) | branchTarget << (31-23)), 16)
    else:
        return int("0x%0.8x" % (0b001 << (31-31) | fmt2Ops["JMP"] << (31-28) | aluIO << (31-24) | branchTarget << (31-20)), 16)

def buildJALInstruction(inst):
    branchTarget = inst.split()[2]
    rd = int(inst.split()[1][1:])

    if branchTarget[0] == "R":
        aluIO = 0
        branchTarget = int(branchTarget[1:])
        return int("0x%0.8x" % (0b001 << (31-31) | fmt2Ops["JAL"] << (31-28) | aluIO << (31-24) | branchTarget << (31-20) | rd << (31-4)), 16)
    else:
        aluIO = 1
        branchTarget = int(branchTarget)
        return int("0x%0.8x" % (0b001 << (31-31) | fmt2Ops["JAL"] << (31-28) | aluIO << (31-24) | branchTarget << (31-23) | rd << (31-4)), 16)


def buildInstruction(inst):
    op = inst.split()[0]
    if(op in aluOps.keys()):
        return buildALUInstruction(inst)
    if(op in fmt2Ops.keys()):
        if op == "LDI":
            return buildLDIInstruction(inst)
        if op == "JMP":
            return buildJMPInstruction(inst)
        if op == "JAL":
            return buildJALInstruction(inst)
        else:
            print "FMT2"
        return 0x41414141
    else:
        print "Illegal Instruction"
        return 0x42424242

class prucpu():
    def __init__(self):
        self.r = [0 for i in range(32)]
        self.pc = 0
        self.code = []
        self.mem = [0 for i in range(0x4000)]
        self.asm = []
        self.carry = 0
        self.executed = 0

    def emulate(self):
        while True:
            if self.pc > len(self.asm)-1:
                return
            if self.executed >= 2000:
                return
            if len(self.asm) == 0:
                return
            if type(self.asm[self.pc]) is not str:
                return
            op = self.asm[self.pc].split()[0]
            if op == "LDI":
                op1,op2 = self.asm[self.pc].split()[1:]
                self.doLDI(int(op1[1:]), int(op2))
            elif op in aluOps.keys():
                op1, op2, op3 = self.asm[self.pc].split()[1:]
                if op3[0] == "R":
                    op3 = self.r[int(op3[1:])]
                else:
                    op3 = int(op3)
                getattr(self, "do"+op)(int(op1[1:]),int(op2[1:]),op3)
            elif op == "JMP":
                arg1=self.asm[self.pc].split()[1]
                if arg1[0] == "R":
                    arg1 = self.r[int(arg1[1:])]
                else:
                    arg1 = int(arg1)
                self.doJMP(arg1)
                self.executed += 1
                continue
            elif op == "JAL":
                rd,arg1=self.asm[self.pc].split()[1:]
                rd = int(rd[1:])
                if arg1[0] == "R":
                    arg1 = self.r[int(arg1[1:])]
                else:
                    arg1 = int(arg1)
                self.doJAL(rd, arg1)
                self.executed +=1
                continue
            else:
                return
            self.pc += 1
            self.executed +=1

    def doJMP(self, arg1):
        self.pc=arg1 & 0xffffffff

    def doJAL(self, rd, arg1):
        self.r[rd] = self.pc+1
        self.pc=arg1

    def doMIN(self, rd, s1, s2):
        if self.r[s1] > s2:
            self.r[rd] = s2
        else:
            self.r[rd] = self.r[s1]

    def doMAX(self, rd, s1, s2):
        if self.r[s1] < s2:
            self.r[rd] = s2
        else:
            self.r[rd] = self.r[s1]

    def doAND(self, rd, s1, s2):
        self.r[rd] = self.r[s1] & s2

    def doOR(self, rd, s1, s2):
        self.r[rd] = self.r[s1] | s2

    def doXOR(self, rd, s1, s2):
        self.r[rd] = self.r[s1] ^ s2

    def doNOT(self, rd, s1, s2):
        self.r[rd] = (((((~self.r[s1]) & 0xffffffff)* -1) - 2**32) * -1) & 0xffffffff

    def doLDI(self, rd, imm):
        self.r[rd] = imm

    def doRSC(self, rd, s1, s2):
        self.r[rd] = s2 - self.r[s1] - self.carry
        self.carry = ((self.r[rd] & 0xffffffff) >> 31) & 1
        if(self.r[rd] < 0):
            self.r[rd] = ((self.r[rd] * -1) - 2**32) * -1

    def doRSB(self, rd, s1, s2):
        self.r[rd] = s2 - self.r[s1]
        self.carry = ((self.r[rd] & 0xffffffff) >> 31) & 1
        if(self.r[rd] < 0):
            self.r[rd] = ((self.r[rd] * -1) - 2**32) * -1

    def doLSL(self, rd, s1, s2):
        self.r[rd] = (self.r[s1] << (s2 & 0x1f)) & 0xffffffff

    def doLSR(self, rd, s1, s2):
        self.r[rd] = (self.r[s1] >> (s2 & 0x1f)) & 0xffffffff

    def doADD(self, rd, s1, s2):
        self.r[rd] = (self.r[s1] + s2) & 0xffffffff
        self.carry = ((self.r[rd] & 0xffffffff) >> 31) & 1

    def doADC(self, rd, s1, s2):
        self.r[rd] = (self.r[s1] + s2 + self.carry) & 0xffffffff
        self.carry = (self.r[rd] >> 31) & 1

    def doSUB(self, rd, s1, s2):
        self.r[rd] = self.r[s1] - s2
        self.carry = ((self.r[rd] & 0xffffffff) >> 31) & 1
        if(self.r[rd] < 0):
            self.r[rd] = ((self.r[rd] * -1) - 2**32) * -1

    def doSUC(self, rd, s1, s2):
        self.r[rd] = self.r[s1] - s2 - self.carry
        self.carry = ((self.r[rd] & 0xffffffff) >> 31) & 1
        if(self.r[rd] < 0):
            self.r[rd] = ((self.r[rd] * -1) - 2**32) * -1

    def doCLR(self, rd, s1, s2):
        self.r[rd] = self.r[s1] & (~(1 << (s2 & 0x1f)))

    def doSET(self, rd, s1, s2):
        self.r[rd] = self.r[s1] | (1 << (s2 & 0x1f))

class PRU(Actions):
    def start(self):
        self.delay(50)
        self.cpu = prucpu()

    def genInstructions(self):
        pass

    def genALU(self):
        op = random.choice(aluOps.keys())
        regTarget = random.choice([0, 1])
        if regTarget == 0:
            arg2 = "R" + str(random.choice(range(32)))
        else:
            arg2 = str(random.choice(range(0xff)))
        dest = "R" + str(random.choice(range(32)))
        arg1 = "R" + str(random.choice(range(32)))
        self.cpu.code.append(buildInstruction("%s %s %s %s" % (op, dest, arg1, arg2)))
        self.cpu.asm.append("%s %s %s %s" % (op, dest, arg1, arg2))

    def genLDI(self):
        imm = random.choice(range(0xffff))
        dest = "R" + str(random.choice(range(32)))
        self.cpu.code.append(buildInstruction("LDI %s %s" % (dest, imm)))
        self.cpu.asm.append("LDI %s %s" % (dest, imm))

    def genBranch(self):
        if len(self.cpu.asm) == 0:
            return
        imm = random.choice(range(len(self.cpu.asm)))
        op = random.choice(["JMP", "JAL"])
        if op=="JAL":
            rd = random.choice(range(32))
            self.cpu.code.append(buildInstruction("JAL R%d %s" % (rd, str(imm))))
            self.cpu.asm.append("JAL R%d %s" % (rd, str(imm)))
        else:
            self.cpu.code.append(buildInstruction("JMP %d" % (imm)))
            self.cpu.asm.append("JMP %d" % (imm))

    def dumpState(self):
        numInstructions = len(self.cpu.asm)
        if numInstructions > 1000:
            numInstructions = 1000
            self.cpu.asm = self.cpu.asm[:1000]
            self.cpu.code = self.cpu.code[:1000]
        self.write(struct.pack("I", len(self.cpu.asm)))
        for i in range(numInstructions):
            self.write(struct.pack("<I", self.cpu.code[i]))
        self.cpu.emulate()
        self.read(expect="============================================", delim="\n")
        for i in range(16):
            val1 = self.cpu.r[i*2]
            val2 = self.cpu.r[i*2+1]
            if val1 < 0:
                val1 = ((val1 * -1) - 2**32) *-1
            if val2 < 0:
                val2 = ((val2 * -1) - 2**32) * -1
            self.read(expect="R%d:\t0x%0.8x\tR%d:\t0x%0.8x" % (i*2, val1, i*2+1, val2), delim="\n")
        self.read(expect="PC:\t0x%0.8x" % (self.cpu.pc * 4), delim="\n")
        self.read(expect="============================================", delim="\n")

if __name__ == "__main__":
    print "%0.8x" % buildInstruction("LDI R0 29")
    print "%0.8x" % buildInstruction("LSL R0 R0 8")
    print "%0.8x" % buildInstruction("LDI R1 216")
    print "%0.8x" % buildInstruction("OR R0 R0 R1")
    print "%0.8x" % buildInstruction("LSL R0 R0 8")
    print "%0.8x" % buildInstruction("LDI R1 64")
    print "%0.8x" % buildInstruction("OR R0 R0 R1")
    print "%0.8x" % buildInstruction("LSL R0 R0 8")
