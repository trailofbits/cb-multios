#include <libcgc.h>

typedef unsigned int uint32_t;

#define END_INSN (0xFFFFFFFF)
#define INSN_TO_OPCODE(_x) (_x & 0x7)
#define INSN_TO_IMM(_x) (_x >> 3)
#define PUSH (0x0)
#define POP (0x1)
#define PUSHPC (0x2)
#define JMPZ (0x3)
#define SWAP (0x4)
#define DUP (0x5)
#define ADD (0x6)
#define SUB (0x7)

#define _MAX_STACK_SIZE_IN_BYTES_ (4096)
#define _MAX_INSNS_SIZE_IN_BYTES_ (8192)
#define _MAX_STACK_SIZE_ (_MAX_STACK_SIZE_IN_BYTES_/4)
#define _MAX_INSNS_SIZE_ (_MAX_INSNS_SIZE_IN_BYTES_/4)

#define _STACK_OVERFLOW_EXCP_MSG_ "STACK OVERFLOW EXCEPTION\n"
#define _STACK_UNDERFLOW_EXCP_MSG_ "STACK UNDERFLOW EXCEPTION\n"
#define _INSNS_OVERFLOW_EXCP_MSG_ "INSNS OVERFLOW EXCEPTION\n"
#define _ILLEGAL_INSN_EXCP_MSG_ "ILLEGAL INSTRUCTION EXCEPTION\n"
#define _PC_EXCP_MSG_ "INVALID PROGRAM COUNTER EXCEPTION\n"

size_t transmit_all(char* buf, size_t size)
{
  size_t rx_bytes = 0;
  size_t total = 0;
  int ret = 0;
  if (buf == NULL)
  {
    return (0);
  }
  
  do
  {
    ret = transmit(STDOUT, buf, size - total, &rx_bytes);
    if ( (ret != 0) || (rx_bytes == 0) )
    {
      _terminate(1);
    }
    total += rx_bytes;
  }
  while (total < size);

  return (size);
}

char gHelpMsg[] = "### The Instruction Set\n"
"\n"
"000b : PUSH # : Pushes a new number onto the stack\n"
"001b : POP : Pops the top number from the stack\n"
"010b : PUSHPC : Pushes the program counter of the current instruction (i.e. PUSHPC) onto the stack\n"
"011b : JMPZ : Pops the top number off of the stack, if its 0 then pop the next value off of the stack and store t\n"
"hat into the PC. If it is not-zero then just pop the next value off of the stack and do nothing with it.\n"
"100b : SWAP # : Swaps the nth number with the top one (which is 0) - meaning SWAP 0 does nothing\n"
"101b : DUP #: Duplicates nth number and pushes it to the top of the stack\n"
"110b : ADD : Pops the top two numbers off of the stack, adds them, and pushes the sum back onto the stack\n"
"111b : SUB : Pops the top two numbers off of the stack, subtracts them ( (top - 1) - top ), and pushes the differ\n"
"ence back onto the stack\n"
"\n"
"All instructions are 32-bits long with the first 3 bits (msbs) reserved for the instruction and the lower 29 bits\n"
 "for literals. POP, ADD, SUB, PUSHPC, JMPZ ignores the lower 29 bits, UNLESS the following special instructions a\n"
"re used:\n"
"\n"
"0xFFFFFFFF : RET : End of instruction stream - The topmost value is the return value\n"
"\n"
"### A simple program\n"
"\n"
"multiply(x,y)\n"
"\n"
"PUSH 0	; 0 - the SUM\n"
"PUSH y 	; SUM, y\n"
"PUSHPC 	; SUM, y, pc\n"
"DUP 1 	; SUM, y, pc, y\n"
"PUSH 1	; SUM, y, pc, y, 1\n"
"SUB	; SUM, y, pc, y-1\n"
"SWAP 2	; SUM, y-1, pc, y\n"
"SWAP 3	; y, y-1, pc, SUM\n"
"PUSH x 	; y, y-1, pc, SUM, x\n"
"ADD 	; y, y-1, pc, SUM+x\n"
"SWAP 3 	; SUM+x, y-1, pc, y\n"
"POP	; SUM+x, y-1, pc\n"
"PUSHPC	; SUM+x, y-1, pc, HERE\n"
"PUSH 7	; SUM+x, y-1, pc, HERE, 7\n"
"ADD	; SUM+x, y-1, pc, HERE+7 \n"
"DUP 2	; SUM+x, y-1, pc, HERE+7, y-1\n"
"JMPZ	;\n"
"PUSH 0	; SUM+x, y-1, pc, 0\n"
"JMPZ	;\n"
"POP	; SUM+x, y-1\n"
"POP	; SUM+x\n"
"RET\n"
"\n"
"If y-1 is not zero, then we will jump back up to where PUSHPC is and execute that whole stream again, except SUM \n"
"will now be SUM+x and y is now y-1\n"
"If y-1 is zero, then we will jump to the instruction after the second JMPZ (which is the first POP)\n";

int main(void)
{
  uint32_t insn = 0;
  size_t rx_bytes = 0;
  size_t total = 0;
  int curTop = -1;
  int totalInsns = 0;
  int pc = 0;
  int ret = 0;

  uint32_t* insns = NULL;
  uint32_t* stack = NULL;

  void* b1 = NULL;
  void* b2 = NULL;
  allocate(_MAX_STACK_SIZE_IN_BYTES_, 0, &b1);
  allocate(_MAX_STACK_SIZE_IN_BYTES_, 0, (void**)(&stack));
  allocate(_MAX_STACK_SIZE_IN_BYTES_, 0, &b2);
  allocate(_MAX_INSNS_SIZE_IN_BYTES_, 0, (void**)(&insns));

  deallocate(b1, _MAX_STACK_SIZE_IN_BYTES_);
  deallocate(b2, _MAX_STACK_SIZE_IN_BYTES_);

  do
  {
    total = 0;
    do
    {
      ret = receive(STDIN, ((char*)(&insn)) + total, sizeof(insn) - total, &rx_bytes);
      if ( (ret != 0) || (rx_bytes == 0) )
      {
        if (totalInsns == 0)
        {
          transmit_all(gHelpMsg, sizeof(gHelpMsg));
        }
        _terminate(-1);
      }
      total += rx_bytes;
    } while (total < sizeof(insn));

    insns[totalInsns] = insn;
    totalInsns++;
    if (totalInsns >= _MAX_INSNS_SIZE_)
    {
      transmit_all(_INSNS_OVERFLOW_EXCP_MSG_, sizeof(_INSNS_OVERFLOW_EXCP_MSG_));
      _terminate(-1);
    }
  } while (insn != END_INSN);


  for (pc = 0; (pc < totalInsns) && (insns[pc] != END_INSN) ; pc++)
  {
    insn = insns[pc];
    if (insn == END_INSN)
    {
      break;
    }

    switch (INSN_TO_OPCODE(insn))
    {
      case (PUSH):
      {
        curTop++;
#ifdef PATCHED
        if (curTop >= _MAX_STACK_SIZE_)
        {
          transmit_all(_STACK_OVERFLOW_EXCP_MSG_, sizeof(_STACK_OVERFLOW_EXCP_MSG_));
          _terminate(-1);
        }
#endif
        stack[curTop] = INSN_TO_IMM(insn);
        break;
      }
      case (POP):
      {
        if (curTop < 0)
        {
          transmit_all(_STACK_UNDERFLOW_EXCP_MSG_, sizeof(_STACK_UNDERFLOW_EXCP_MSG_));
          _terminate(-1);
        }
        curTop--;
        break;
      }
      case (PUSHPC):
      {
        curTop++;
        if (curTop >= _MAX_STACK_SIZE_)
        {
          transmit_all(_STACK_OVERFLOW_EXCP_MSG_, sizeof(_STACK_OVERFLOW_EXCP_MSG_));
          _terminate(-1);
        }
        stack[curTop] = pc;
        break;
      }
      case (JMPZ):
      {
        if (curTop < 1)
        {
          transmit_all(_STACK_UNDERFLOW_EXCP_MSG_, sizeof(_STACK_UNDERFLOW_EXCP_MSG_));
          _terminate(-1);
        }

        if (stack[curTop] == 0)
        {
          pc = stack[curTop - 1];
          if ((pc < 0) || (pc >= totalInsns))
          {
            transmit_all(_PC_EXCP_MSG_, sizeof(_PC_EXCP_MSG_));
            _terminate(-1);
          }
          pc--; //for the pc++ at the end of the loop
        }
        curTop -= 2;
        break;
      }
      case (SWAP):
      {
        if (curTop < 0)
        {
          transmit_all(_STACK_UNDERFLOW_EXCP_MSG_, sizeof(_STACK_UNDERFLOW_EXCP_MSG_));
          _terminate(-1);
        }

        uint32_t temp = stack[curTop];
        int temp2 = curTop - INSN_TO_IMM(insn);
        
        if ( (temp2 < 0) || (temp2 > curTop) )
        {
          transmit_all(_STACK_UNDERFLOW_EXCP_MSG_, sizeof(_STACK_UNDERFLOW_EXCP_MSG_));
          _terminate(-1);
        }

        stack[curTop] = stack[temp2];
        stack[temp2] = temp;
        break;
      } 
      case (DUP):
      {
        curTop++;
#ifdef PATCHED
        if (curTop >= _MAX_STACK_SIZE_)
        {
          transmit_all(_STACK_OVERFLOW_EXCP_MSG_, sizeof(_STACK_OVERFLOW_EXCP_MSG_));
          _terminate(-1);
        }
#endif
        int temp = curTop - INSN_TO_IMM(insn) - 1;
         
        if ( (temp < 0) || (temp > curTop) )
        {
          transmit_all(_STACK_UNDERFLOW_EXCP_MSG_, sizeof(_STACK_UNDERFLOW_EXCP_MSG_));
          _terminate(-1);
        }

        stack[curTop] = stack[curTop - INSN_TO_IMM(insn) - 1];
        break;
      }
      case (ADD):
      {
        if (curTop < 1)
        {
          transmit_all(_STACK_UNDERFLOW_EXCP_MSG_, sizeof(_STACK_UNDERFLOW_EXCP_MSG_));
          _terminate(-1);
        }
        stack[curTop - 1] += stack[curTop];
        curTop--;  
        break;
      }
      case (SUB):
      {
        if (curTop < 1)
        {
          transmit_all(_STACK_UNDERFLOW_EXCP_MSG_, sizeof(_STACK_UNDERFLOW_EXCP_MSG_));
          _terminate(-1);
        }
        stack[curTop - 1] -= stack[curTop];
        curTop--;  
        break;
      }
      default :
      {
        //empty
      }
    }
  }

  if (curTop < 0)
  {
    transmit_all(_STACK_UNDERFLOW_EXCP_MSG_, sizeof(_STACK_UNDERFLOW_EXCP_MSG_));
    _terminate(-1);
  }

  transmit_all(&stack[curTop], sizeof(uint32_t));

  return (0);
}

