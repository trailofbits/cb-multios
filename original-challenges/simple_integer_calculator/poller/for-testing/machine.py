#!/usr/bin/env python

from generator.actions import Actions
import random
import string

types = ["Integer", "String", "Boolean"]

class Calculator(Actions):
    variables = []

    def genOperand(self, otype):
        if(otype == "String"):
            return "".join(random.choice(string.ascii_uppercase + string.digits) for _ in range(10))
        if(otype == "Integer"):
            return random.randint(0, 200000)
        if(otype == "Boolean"):
            return random.choice(["True", "False"])

    def start(self):
        self.read(delim='> ')

    def doSomething(self):
        pass

    def doLen(self):
        want = ""
        type1 = random.choice(types)
        operand1 = self.genOperand(type1)
        if(type1 == "String"):
            self.write("len \"%s\"\n" % operand1)
            want = operand1
        elif(type1 == "Boolean"):
            self.write("len %s\n" % operand1)
            want = "1"
        else:
            self.write("len %s\n" % operand1)
            want = str(operand1)
        self.read(delim='\n', expect=str(len(want)))

    def doMod(self):
        type1, type2 = (random.choice(types), random.choice(types))

        operand1, operand2 = (self.genOperand(type1), self.genOperand(type2))
        if(type1 == "Integer" and type2 == "Integer"):
            self.write("%s %s %s\n" % (operand1, random.choice(["%", "mod"]), operand2))
            if(operand2 == "0"):
                self.read(delim='\n', expect="Cannot mod by zero.")
            else:
                self.read(delim='\n', expect=str(operand1 % operand2))
        else:
            if type1 == "String":
                operand1 = "\"%s\"" % operand1
            if type2 == "String":
                operand2 = "\"%s\"" % operand2
            self.write("%s %s %s\n" % (operand1, random.choice(["%", "mod"]), operand2))
            self.read(delim='\n', expect="Mod does not make sense on %s and %s" % (type1, type2))

    def doNot(self):
        type1 = random.choice(types)
        operand1 = self.genOperand(type1)

        if type1 == "String":
            self.write("not \"%s\"\n" % operand1)
            if(operand1 == "OMG"):
                #Buy a lottery ticket.
                self.read(delim='\n', expect="BBQ")
            else:
                self.read(delim='\n', expect="OMG")
        elif type1 == "Integer":
            self.write("not %s\n" % operand1)
            self.read(delim="\n", expect=str(~operand1))
        elif type1 == "Boolean":
            self.write("not %s\n" % operand1)
            if(operand1 == "True"):
                self.read(delim="\n", expect="False")
            else:
                self.read(delim="\n", expect="True")

    def doEquals(self):
        type1, type2 = (random.choice(types), random.choice(types))
        operand1, operand2 = (self.genOperand(type1), self.genOperand(type2))
        match = random.randint(0, 1)

        if(match):
            if(type1 == "String"):
                self.write("\"%s\" %s \"%s\"\n" % (operand1, random.choice(["==", "equals"]), operand1))
            else:
                self.write("%s %s %s\n" % (operand1, random.choice(["==", "equals"]), operand1))
            self.read(delim="\n", expect="True")
        else:
            if(type1 == "String"):
                operand1 = "\"%s\"" % operand1
            if(type2 == "String"):
                operand2 = "\"%s\"" % operand2
            if(type1 == "Boolean" and type2 == "Boolean"):
                if(operand1 == "True"):
                    operand2 = "False"
                else:
                    operand2 = "True"
            self.write("%s %s %s\n" % (operand1, random.choice(["==", "equals"]), operand2))
            self.read(delim="\n", expect="False")


    def doType(self):
        type1 = random.choice(types)
        operand1 = self.genOperand(type1)
        if(type1 == "String"):
            self.write("type \"%s\"\n" % operand1)
        else:
            self.write("type %s\n" % operand1)
        self.read(delim="\n", expect=type1)

    def doAdd(self):
        type1, type2 = (random.choice(types), random.choice(types))

        operand1, operand2 = (self.genOperand(type1), self.genOperand(type2))
        if(type1 == "Integer" and type2 == "Integer"):
            self.write("%s %s %s\n" % (operand1, random.choice(["+", "add"]), operand2))
            self.read(delim='\n', expect=str(operand1 + operand2))
        elif(type1 == "String" and type2 == "Integer"):
            self.write("\"%s\" %s %s\n" % (operand1, random.choice(["+", "add"]), operand2))
            self.read(delim='\n', expect=operand1 + str(operand2))
        elif(type1 == "String" and type2 == "String"):
            self.write("\"%s\" %s \"%s\"\n" % (operand1, random.choice(["+", "add"]), operand2))
            self.read(delim='\n', expect=operand1 + operand2)
        else:
            if type1 == "String":
                operand1 = "\"%s\"" % operand1
            if type2 == "String":
                operand2 = "\"%s\"" % operand2
            self.write("%s %s %s\n" % (operand1, random.choice(["+", "add"]), operand2))
            self.read(delim='\n', expect="Add doesn't make sense on %s and %s" % (type1, type2))


    def doSub(self):
        type1, type2 = (random.choice(types), random.choice(types))

        operand1, operand2 = (self.genOperand(type1), self.genOperand(type2))
        if(type1 == "Integer" and type2 == "Integer"):
            self.write("%s %s %s\n" % (operand1, random.choice(["-", "sub"]), operand2))
            self.read(delim='\n', expect=str(operand1 - operand2))
        else:
            if type1 == "String":
                operand1 = "\"%s\"" % operand1
            if type2 == "String":
                operand2 = "\"%s\"" % operand2
            self.write("%s %s %s\n" % (operand1, random.choice(["-", "sub"]), operand2))
            self.read(delim='\n', expect="Sub does not make sense on %s and %s" % (type1, type2))

    def doMul(self):
        type1, type2 = (random.choice(types), random.choice(types))

        operand1, operand2 = (self.genOperand(type1), self.genOperand(type2))
        if(type1 == "Integer" and type2 == "Integer"):
            operand1 = operand1 % 2048
            operand2 = operand2 % 2048
            self.write("%s %s %s\n" % (operand1, random.choice(["*", "mul"]), operand2))
            total = (operand1 * operand2) & (pow(2,32)-1)
            if (total > (pow(2,31)-1)):
                total = total & (pow(2,31)-1)
                total *= -1
                self.read(delim='\n', expect=str(total))
            else:
                self.read(delim='\n', expect=str(total))
        elif(type1 == "String" and type2 == "Integer"):
            operand2 = random.randint(1, 20)
            self.write("\"%s\" * %s\n" % (operand1, operand2))
        else:
            if type1 == "String":
                operand1 = "\"%s\"" % operand1
            if type2 == "String":
                operand2 = "\"%s\"" % operand2
            self.write("%s %s %s\n" % (operand1, random.choice(["*", "mul"]), operand2))
            self.read(delim='\n', expect="Mul does not make sense with %s and %s" % (type1, type2))

    def doInt(self):
        type1 = random.choice(types)
        operand1 = self.genOperand(type1)

        if(type1 == "Integer"):
            self.write("int %s\n" % operand1)
            self.read(delim='\n', expect=str(operand1))

        elif(type1 == "String"):
            try:
                operand1 = int(operand1)
                self.write("int \"%s\"\n" % operand1)
            except ValueError:
                self.write("int \"%s\"\n")
                self.read(delim='\n', expect="Could not convert argument to int")
        elif(type1 == "Boolean"):
            self.write("int %s\n" % operand1)
            if operand1 == "True":
                line = "1"
            else:
                line = "0"
            self.read(delim='\n', expect=line)

    def doDiv(self):
        type1, type2 = (random.choice(types), random.choice(types))

        operand1, operand2 = (self.genOperand(type1), self.genOperand(type2))
        if(type1 == "Integer" and type2 == "Integer"):
            self.write("%s %s %s\n" % (operand1, random.choice(["/", "div"]), operand2))
            if(operand2 == "0"):
                self.read(delim='\n', expect="Cannot divide by zero.")
            else:
                self.read(delim='\n', expect=str(operand1 / operand2))
        else:
            if type1 == "String":
                operand1 = "\"%s\"" % operand1
            if type2 == "String":
                operand2 = "\"%s\"" % operand2
            self.write("%s %s %s\n" % (operand1, random.choice(["/", "div"]), operand2))
            self.read(delim='\n', expect="Division does not make sense on %s and %s" % (type1, type2))

    def doVar(self):
        type1 = random.choice(types)
        varName = "".join(random.choice(string.ascii_uppercase + string.ascii_lowercase) for _ in range(10))

        if(type1 == "String"):
            varValue = "".join(random.choice(string.ascii_uppercase + string.ascii_lowercase) for _ in range(10))
            self.write("var %s = \"%s\"\n" % (varName, varValue))
            self.variables.append((varName, varValue, type1))
        else:
            varValue = self.genOperand(type1)
            self.write("var %s = %s\n" % (varName, varValue))
            self.variables.append((varName, varValue, type1))
        self.write(varName + "\n")
        self.read(delim="\n", expect="> " + str(varValue))

    def end(self):
        self.write("terminate\n")