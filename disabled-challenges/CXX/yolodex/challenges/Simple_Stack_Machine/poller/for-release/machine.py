#!/usr/bin/env python

from generator.actions import Actions
import copy
import random
import struct

_INT_MAX_ = 0x1FFFFFFF
_PUSH_ = 0x0
_POP_ = 0x1
_PUSHPC_ = 0x2
_JMPZ_ = 0x3
_SWAP_ = 0x4
_DUP_ = 0x5
_ADD_ = 0x6
_SUB_ = 0x7
_END_ = 0xFFFFFFFF
_FILLER_ = 0
_OPCODE_MASK_ = 0x7
_OP_MASK_ = 0x1FFFFFFF

_STACK_OVERFLOW_EXCP_MSG_ = "STACK OVERFLOW EXCEPTION\n"
_STACK_UNDERFLOW_EXCP_MSG_ = "STACK UNDERFLOW EXCEPTION\n"
_INSNS_OVERFLOW_EXCP_MSG_ = "INSNS OVERFLOW EXCEPTION\n"
_ILLEGAL_INSN_EXCP_MSG_ = "ILLEGAL INSTRUCTION EXCEPTION\n"
_PC_EXCP_MSG_ = "INVALID PROGRAM COUNTER EXCEPTION\n"

_MAX_STACK_SIZE_IN_BYTES_ = (4096)
_MAX_INSNS_SIZE_IN_BYTES_ = (8192)
_MAX_STACK_SIZE_ = (_MAX_STACK_SIZE_IN_BYTES_/4)
_MAX_INSNS_SIZE_ = (_MAX_INSNS_SIZE_IN_BYTES_/4)

def _INSN_TO_OPCODE_(insn) :
    return (insn & _OPCODE_MASK_)

def _INSN_TO_IMM_(insn) :
    return (insn >> 3)
    
def encodeInsn(opcode, op) :
    return ( (opcode & _OPCODE_MASK_) | ((op & _OP_MASK_) << 3) )

def toLittleEndian(i) :
    return (struct.pack("<I", i))

class StackMachine(Actions):

    def send_insn(self, opcode, op):
        if len(self.insns) >= _MAX_INSNS_SIZE_ :
          if not self.excp :
            self.excp = _INSNS_OVERFLOW_EXCP_MSG_
        else :
          insn = encodeInsn(opcode, op)
          self.insns.append(insn)
          self.write(toLittleEndian(insn))
        
    def start(self):
        self.stack = []
        self.insns = []
        self.excp = ""

    def generate_work(self):
        pass

    def gen_push(self):
        if len(self.stack) >= _MAX_STACK_SIZE_ :
          return
          if not self.excp :
            self.excp = _STACK_OVERFLOW_EXCP_MSG_ 
        op = random.randint(0,_INT_MAX_)
        self.send_insn(_PUSH_, op)
        self.stack.append(op)

    def gen_pop(self):
        if self.stack :
          self.stack.pop()
        else :
          if not self.excp :
            self.excp = _STACK_UNDERFLOW_EXCP_MSG_
  
        self.send_insn(_POP_, _FILLER_)

    def gen_add(self):
        if len(self.stack) >= 2 :
          self.stack[-2] += self.stack[-1]
          self.stack[-2] &= 0xFFFFFFFF
          self.stack.pop()
        else :
          if not self.excp :
            self.excp = _STACK_UNDERFLOW_EXCP_MSG_
        
        self.send_insn(_ADD_, _FILLER_)

    def gen_sub(self):
        if len(self.stack) >= 2 :
          self.stack[-2] -= self.stack[-1]
          self.stack[-2] &= 0xFFFFFFFF
          self.stack.pop()
        else :
          if not self.excp :
            self.excp = _STACK_UNDERFLOW_EXCP_MSG_

        self.send_insn(_SUB_, _FILLER_)

    def gen_swap(self):
        if self.stack :
          op = random.randint(0,len(self.stack)) #note that this can cause an underflow - which is good
          if (op >= len(self.stack)) :
            if not self.excp :
              self.excp = _STACK_UNDERFLOW_EXCP_MSG_
          else :
            temp = self.stack[-1] 
            self.stack[-1] = self.stack[len(self.stack) - 1 - op]
            self.stack[len(self.stack) - 1 - op] = temp

          self.send_insn(_SWAP_, op) #note that this can cause an underflow - which is good

    def gen_dup(self):
        if self.stack :
          op = random.randint(0,len(self.stack)) #note that this can cause an underflow - which is good
          if (op >= len(self.stack)) :
            if not self.excp :
              self.excp = _STACK_UNDERFLOW_EXCP_MSG_
          else :
            if len(self.stack) >= _MAX_STACK_SIZE_ :
              return

            self.stack.append(self.stack[len(self.stack) - 1 - op])

          self.send_insn(_DUP_, op) #note that this can cause an underflow - which is good

    def gen_loop(self):
        c = random.randint(0,10) 
        if not c :
          if not self.excp :
            self.send_insn(_PUSH_, _INT_MAX_)
            self.send_insn(_PUSH_, 0)
            self.send_insn(_JMPZ_, _FILLER_)
            self.excp = _PC_EXCP_MSG_
        elif c > 5 :
          self.send_insn(_PUSHPC_, _FILLER_)
          self.send_insn(_PUSH_, 5)
          self.send_insn(_ADD_, _FILLER_)
          self.send_insn(_PUSH_, 0)
          self.send_insn(_JMPZ_, _FILLER_)
        else :
          self.send_insn(_PUSHPC_, _FILLER_)
          self.send_insn(_PUSH_, 1)
          self.send_insn(_JMPZ_, _FILLER_)

    def end(self):
        if self.excp == _INSNS_OVERFLOW_EXCP_MSG_ :
          self.read(length=len(self.excp), expect=self.excp)
        else :
          self.write(toLittleEndian(_END_))
          if self.excp :
            self.read(length=len(self.excp), expect=self.excp)
          else :
            if self.stack :
                self.read(length=4, expect=toLittleEndian(self.stack[-1]))
            else :
              self.read(length=len(_STACK_UNDERFLOW_EXCP_MSG_), expect=_STACK_UNDERFLOW_EXCP_MSG_)
           

