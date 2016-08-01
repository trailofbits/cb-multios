#include <libcgc.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef uint16_t reg_t;

// NOTE: Had to reduce the STATE_SIZE so that the segfault condition is easier to trigger - used to be 1024

#define STATE_SIZE (256)
#define NUM_CONSTANTS (6)
#define CONSTANT_SIZE (NUM_CONSTANTS * 4)
uint8_t* state = NULL; //[STATE_SIZE + CONSTANT_SIZE];
uint8_t* _consts = NULL;

#define R_ZERO   (STATE_SIZE + (4 * 0))
#define R_ONE    (STATE_SIZE + (4 * 1))
#define R_TRUE8  (STATE_SIZE + (4 * 2))
#define R_TRUE16 (STATE_SIZE + (4 * 3))
#define R_TRUE32 (STATE_SIZE + (4 * 4))
#define R_FALSE  (STATE_SIZE + (4 * 5))

#define TRUE8  (0xFF)
#define TRUE16 (0xFFFF)
#define TRUE32 (0xFFFFFFFF)
#define FALSE  (0x0)

#define STATE8(_r)  ( *((uint8_t*)(state + _r))  )
#define STATE16(_r) ( *((uint16_t*)(state + _r)) )
#define STATE32(_r) ( *((uint32_t*)(state + _r)) )


#define REGLIMIT (STATE_SIZE / 2) 

#define ADDR(_r) (_r + REGLIMIT)

uint8_t DATA8(reg_t r)
{
 return (STATE8(r + REGLIMIT));
}

uint16_t DATA16(reg_t r)
{
 return (STATE16(r + REGLIMIT));
}

uint32_t DATA32(reg_t r)
{
 return (STATE32(r + REGLIMIT));
}

uint8_t REG8(reg_t r)
{
 return (STATE8(r));
}

uint16_t REG16(reg_t r)
{
 return (STATE16(r));
}

uint32_t REG32(reg_t r)
{
 return (STATE32(r));
}


void MOVIM8(reg_t r1, uint8_t im)
{
  STATE8(r1) = im;
}

void MOVIM16(reg_t r1, uint16_t im)
{
  STATE16(r1) = im;
}

void MOVIM32(reg_t r1, uint32_t im)
{
  STATE32(r1) = im;
}

void MOV8(reg_t r1, reg_t r2)
{
  STATE8(r1) = STATE8(r2);
}

void MOV16(reg_t r1, reg_t r2)
{
  STATE16(r1) = STATE16(r2);
}

void MOV32(reg_t r1, reg_t r2)
{
  STATE32(r1) = STATE32(r2);
}


void AND8(reg_t r1, reg_t r2, reg_t r3)
{
  STATE8(r1) = STATE8(r2) & STATE8(r3);
}

void AND16(reg_t r1, reg_t r2, reg_t r3)
{
  STATE16(r1) = STATE16(r2) & STATE16(r3);
}

void AND32(reg_t r1, reg_t r2, reg_t r3)
{
  STATE32(r1) = STATE32(r2) & STATE32(r3);
}

void OR8(reg_t r1, reg_t r2, reg_t r3)
{
  STATE8(r1) = STATE8(r2) | STATE8(r3);
}

void OR16(reg_t r1, reg_t r2, reg_t r3)
{
  STATE16(r1) = STATE16(r2) | STATE16(r3);
}

void OR32(reg_t r1, reg_t r2, reg_t r3)
{
  STATE32(r1) = STATE32(r2) | STATE32(r3);
}

void NOT8(reg_t r1, reg_t r2)
{
  STATE8(r1) = ~STATE8(r2);
}

void NOT16(reg_t r1, reg_t r2)
{
  STATE16(r1) = ~STATE16(r2);
}

void NOT32(reg_t r1, reg_t r2)
{
  STATE32(r1) = ~STATE32(r2);
}

void ADD8(reg_t r1, reg_t r2, reg_t r3)
{
  STATE8(r1) = STATE8(r2) + STATE8(r3);
}

void ADD16(reg_t r1, reg_t r2, reg_t r3)
{
  STATE16(r1) = STATE16(r2) + STATE16(r3);
}

void ADD32(reg_t r1, reg_t r2, reg_t r3)
{
  STATE32(r1) = STATE32(r2) + STATE32(r3);
}

void SUB8(reg_t r1, reg_t r2, reg_t r3)
{
  STATE8(r1) = STATE8(r2) - STATE8(r3);
}

void SUB16(reg_t r1, reg_t r2, reg_t r3)
{
  STATE16(r1) = STATE16(r2) - STATE16(r3);
}

void SUB32(reg_t r1, reg_t r2, reg_t r3)
{
  STATE32(r1) = STATE32(r2) - STATE32(r3);
}

void LAND8(reg_t r1, reg_t r2, reg_t r3)
{
  AND8(r1, r2, r3);
}

void LAND16(reg_t r1, reg_t r2, reg_t r3)
{
  AND16(r1, r2, r3);
}

void LAND32(reg_t r1, reg_t r2, reg_t r3)
{
  AND32(r1, r2, r3);
}

void LOR8(reg_t r1, reg_t r2, reg_t r3)
{
  OR8(r1, r2, r3);
}

void LOR16(reg_t r1, reg_t r2, reg_t r3)
{
  OR16(r1, r2, r3);
}

void LOR32(reg_t r1, reg_t r2, reg_t r3)
{
  OR32(r1, r2, r3);
}

void EQ8(reg_t r1, reg_t r2, reg_t r3)
{
  if (STATE8(r2) == STATE8(r3))
  {
    MOV8(r1, R_TRUE8);
  }
  else
  {
    MOV8(r1, R_FALSE);
  }
}

void EQ16(reg_t r1, reg_t r2, reg_t r3)
{
  if (STATE16(r2) == STATE16(r3))
  {
    MOV16(r1, R_TRUE16);
  }
  else
  {
    MOV16(r1, R_FALSE);
  }
}

void EQ32(reg_t r1, reg_t r2, reg_t r3)
{
  if (STATE32(r2) == STATE32(r3))
  {
    MOV32(r1, R_TRUE32);
  }
  else
  {
    MOV32(r1, R_FALSE);
  }
}

void GT8(reg_t r1, reg_t r2, reg_t r3)
{
  if (STATE8(r2) > STATE8(r3))
  {
    MOV8(r1, R_TRUE8);
  }
  else
  {
    MOV8(r1, R_FALSE);
  }
}

void GT16(reg_t r1, reg_t r2, reg_t r3)
{
  if (STATE16(r2) > STATE16(r3))
  {
    MOV16(r1, R_TRUE16);
  }
  else
  {
    MOV16(r1, R_FALSE);
  }
}

void GT32(reg_t r1, reg_t r2, reg_t r3)
{
  if (STATE32(r2) > STATE32(r3))
  {
    MOV32(r1, R_TRUE32);
  }
  else
  {
    MOV32(r1, R_FALSE);
  }
}


void GTE8(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  EQ8(r1, r2, r3);
  GT8(scratch, r2, r3);
  LOR8(r1, r1, scratch);  
}

void GTE16(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  EQ16(r1, r2, r3);
  GT16(scratch, r2, r3);
  LOR16(r1, r1, scratch);  
}

void GTE32(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  EQ32(r1, r2, r3);
  GT32(scratch, r2, r3);
  LOR32(r1, r1, scratch);  
}

void LT8(reg_t r1, reg_t r2, reg_t r3)
{
  GT8(r1, r3, r2);
}

void LT16(reg_t r1, reg_t r2, reg_t r3)
{
  GT16(r1, r3, r2);
}

void LT32(reg_t r1, reg_t r2, reg_t r3)
{
  GT32(r1, r3, r2);
}

void LTE8(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  GTE8(r1, r3, r2, scratch);
}

void LTE16(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  GTE16(r1, r3, r2, scratch);
}

void LTE32(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  GTE32(r1, r3, r2, scratch);
}

void INC8(reg_t r1)
{
  ADD8(r1, r1, R_ONE);
}

void INC16(reg_t r1)
{
  ADD16(r1, r1, R_ONE);
}

void INC32(reg_t r1)
{
  ADD32(r1, r1, R_ONE);
}

void DEC8(reg_t r1)
{
  SUB8(r1, r1, R_ONE);
}

void DEC16(reg_t r1)
{
  SUB16(r1, r1, R_ONE);
}

void DEC32(reg_t r1)
{
  SUB32(r1, r1, R_ONE);
}

void MUL32(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  MOV32(scratch, r2); 
  MOV32(scratch+4, r3); 

  //make sure this initialization is after r2 and r3 are already saved
  // otherwise, if r1 = r2 or r1 = r3, then we will have problems
  MOVIM32(r1, 0);

  GT32(scratch+8, r2, r3);
  if (REG32(scratch+8))
  {
    MOV32(scratch, r3);
    MOV32(scratch+4, r2);
  }

  
  GT32(scratch+8, scratch, R_ZERO);
  while (REG32(scratch+8))
  {
    ADD32(r1, r1, scratch+4);
    DEC32(scratch);
    GT32(scratch+8, scratch, R_ZERO);
  } 
}

void MUL16(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  MOVIM32(scratch, 0);
  MOV16(scratch, r1);
  MOVIM32(scratch+4, 0);
  MOV16(scratch+4, r2);
  MOVIM32(scratch+8, 0);
  MOV16(scratch+8, r3);
  MUL32(scratch, scratch+4, scratch+8, scratch+12);
  MOV16(r1, scratch);
}

void MUL8(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  MOVIM32(scratch, 0);
  MOV8(scratch, r1);
  MOVIM32(scratch+4, 0);
  MOV8(scratch+4, r2);
  MOVIM32(scratch+8, 0);
  MOV8(scratch+8, r3);
  MUL32(scratch, scratch+4, scratch+8, scratch+12);

  MOV8(r1, scratch);
}

void DIV32(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  MOV32(scratch, r2); 
  MOVIM32(r1, 0);

  EQ32(scratch+4, r3, R_ZERO);
  if (REG32(scratch+4))
  {
    goto _end;
  }

  
  GTE32(scratch+4, scratch, r3, scratch+8);
  GT32(scratch+8, scratch, R_ZERO);
  LAND32(scratch+12, scratch+4, scratch+8);
  while (REG32(scratch+12))
  {
    INC32(r1);
    SUB32(scratch, scratch, r3);
    GTE32(scratch+4, scratch, r3, scratch+8);
    GT32(scratch+8, scratch, R_ZERO);
    LAND32(scratch+12, scratch+4, scratch+8);
  } 

_end:
  return;
}

void DIV16(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  MOVIM32(scratch, 0);
  MOV16(scratch, r1);
  MOVIM32(scratch+4, 0);
  MOV16(scratch+4, r2);
  MOVIM32(scratch+8, 0);
  MOV16(scratch+8, r3);
  DIV32(scratch, scratch+4, scratch+8, scratch+12);
  MOV16(r1, scratch);
}

void DIV8(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  MOVIM32(scratch, 0);
  MOV8(scratch, r1);
  MOVIM32(scratch+4, 0);
  MOV8(scratch+4, r2);
  MOVIM32(scratch+8, 0);
  MOV8(scratch+8, r3);
  DIV32(scratch, scratch+4, scratch+8, scratch+12);

  MOV8(r1, scratch);
}

void REM32(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  MOV32(scratch, r2); 
  MOVIM32(r1, 0);

  EQ32(scratch+4, r3, R_ZERO);
  if (REG32(scratch+4))
  {
    goto _end;
  }

  GTE32(scratch+4, scratch, r3, scratch+16);
  GT32(scratch+8, scratch, R_ZERO);
  LAND32(scratch+12, scratch+4, scratch+8);
  while (REG32(scratch+12))
  {
    SUB32(scratch, scratch, r3);

    GTE32(scratch+4, scratch, r3, scratch+16);
    GT32(scratch+8, scratch, R_ZERO);
    LAND32(scratch+12, scratch+4, scratch+8);
  } 

  MOV32(r1, scratch);
_end:
  return;
}

void REM16(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  MOVIM32(scratch, 0);
  MOV16(scratch, r1);
  MOVIM32(scratch+4, 0);
  MOV16(scratch+4, r2);
  MOVIM32(scratch+8, 0);
  MOV16(scratch+8, r3);
  REM32(scratch, scratch+4, scratch+8, scratch+12);
  MOV16(r1, scratch);
}

void REM8(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  MOVIM32(scratch, 0);
  MOV8(scratch, r1);
  MOVIM32(scratch+4, 0);
  MOV8(scratch+4, r2);
  MOVIM32(scratch+8, 0);
  MOV8(scratch+8, r3);
  REM32(scratch, scratch+4, scratch+8, scratch+12);

  MOV8(r1, scratch);
}

void INIT_MACHINE()
{
  int i = 0; 
  int ret  = 0;

  ret = allocate(STATE_SIZE + CONSTANT_SIZE, 0, (void**)(&state));

  if (ret != 0)
  {
    _terminate(-1);
  }

  //NOTE: Had to move the state to the end of the memory range so that
  // the segfault is easier to trigger
  state = state + 0x1000 - STATE_SIZE - CONSTANT_SIZE;

  _consts = state + STATE_SIZE;

  for (i = 0; i < STATE_SIZE; i+=4)
  {
    MOVIM32(i, 0);
  }

  MOVIM32(R_ZERO, 0);
  MOVIM32(R_ONE, 1);
  MOVIM32(R_TRUE8, TRUE8);
  MOVIM32(R_TRUE16, TRUE16);
  MOVIM32(R_TRUE32, TRUE32);
  MOVIM32(R_FALSE, FALSE);
}

void printChar(reg_t r)
{
  char c = REG8(r);
  size_t n;
  if (transmit(STDOUT, &c, 1, &n) != 0 || n != 1) {
     _terminate(1);
  }
}

int getChar(reg_t r)
{
  char c;
  size_t rx_bytes;
  int ret = 0;
  fd_set fdsToWait;
  struct timeval timeToWait;
  timeToWait.tv_sec = 1;
  timeToWait.tv_usec = 0;
  int readyfds = 0;

  FD_ZERO(&fdsToWait);
  FD_SET(0, &fdsToWait);
  ret = fdwait(1, &fdsToWait, NULL, &timeToWait, &readyfds);
  if ( (ret != 0) || (readyfds != 1) )
  {
    return (-1);
  }

  ret = receive(STDIN, &c, 1, &rx_bytes);
  if ((ret != 0) || (rx_bytes == 0))
  {
    return (-1);
  }

  MOVIM8(r, c);
  return (0);
}


void printString(reg_t r, reg_t ret, reg_t scratch)
{
  reg_t temp = scratch;
  MOV16(temp, r); //temp pointer to string

  scratch += 2;
  MOVIM8(scratch, 0); //constant i
 
  loop1:
  MOV8(scratch+1, REG16(temp));

  EQ8(scratch+2, R_ZERO, scratch+1);
  if (REG8(scratch+2))
  {
    goto loop1_end;
  }
  printChar(scratch+1);
  INC8(scratch);
  INC16(temp);
  goto loop1;
  loop1_end: 

  MOV8(ret, scratch);
}

void printReg32(reg_t r, reg_t scratch)
{
  MOV32(scratch, r); //temporary r

  reg_t tens = scratch + 4;

  //tens table
  MOVIM32(tens,    1000000000);
  MOVIM32(tens+4,  100000000);
  MOVIM32(tens+8,  10000000);
  MOVIM32(tens+12, 1000000);
  MOVIM32(tens+16, 100000);
  MOVIM32(tens+20, 10000);
  MOVIM32(tens+24, 1000);
  MOVIM32(tens+28, 100);
  MOVIM32(tens+32, 10);
  MOVIM32(tens+36, 1);

  reg_t r_four = tens + 40;
  MOVIM16(r_four, 4);

 
  reg_t r_end = r_four+2;
  MOVIM16(r_end, tens + 40);

  reg_t i = r_end + 2;
  reg_t j = i+2;
  reg_t temp = j+2;

  MOVIM16(i, tens); 
  GT16(j, r_end, i);

  while (REG16(j))
  {
    DIV32(temp, scratch, REG16(i), temp + 5); 

    MOVIM8(temp + 4, '0');
    ADD8(temp + 4, temp + 4, temp); 
    printChar(temp + 4);
    REM32(scratch, scratch, REG16(i), temp + 5);
    
    ADD16(i, i, r_four);
    GT16(j, r_end, i);
  }
}

void printReg16(reg_t r, reg_t scratch)
{
  MOVIM32(scratch, 0);
  MOV16(scratch, r);
  printReg32(scratch, scratch + 4);
}

void printReg8(reg_t r, reg_t scratch)
{
  MOVIM32(scratch, 0);
  MOV8(scratch, r);
  printReg32(scratch, scratch + 4);
}

int isSpace(reg_t r, reg_t scratch)
{
  MOVIM8(scratch, ' ');
  MOVIM8(scratch+1, '\t');

  EQ8(scratch+2, r, scratch);
  EQ8(scratch+3, r, scratch+1);
  LOR8(scratch+2, scratch+2, scratch+3);
  return (REG8(scratch+2));
}

int isNumber(reg_t r, reg_t scratch)
{
  MOVIM8(scratch, '0');
  SUB8(scratch+1, r, scratch);
  MOVIM8(scratch+2, 10);

  LT8(scratch+3, scratch+1, scratch+2);
  return (REG8(scratch+3));
}

int isUpLetter(reg_t r, reg_t scratch)
{
  MOVIM8(scratch, 'A');
  MOVIM8(scratch+1, 'Z');

  GTE8(scratch+2, r, scratch, scratch+3);
  LTE8(scratch+3, r, scratch+1, scratch+4);
  LAND8(scratch+2, scratch+2, scratch+3);
  return (REG8(scratch+2));
}

int isLowLetter(reg_t r, reg_t scratch)
{
  MOVIM8(scratch, 'a');
  MOVIM8(scratch+1, 'z');

  GTE8(scratch+2, r, scratch, scratch+3);
  LTE8(scratch+3, r, scratch+1, scratch+4);
  LAND8(scratch+2, scratch+2, scratch+3);
  return (REG8(scratch+2));
}

int isSpecial(reg_t r, reg_t scratch)
{
  MOVIM8(scratch, '!');
  MOVIM8(scratch+1, '/');

  MOVIM8(scratch+2, ':');
  MOVIM8(scratch+3, '@');

  MOVIM8(scratch+4, '[');
  MOVIM8(scratch+5, '`');

  MOVIM8(scratch+6, 'P');
  MOVIM8(scratch+7, '~');

  
  GTE8(scratch+10, r, scratch, scratch+12);
  LTE8(scratch+11, r, scratch+1, scratch+13);
  LAND8(scratch+9, scratch+10, scratch+11);
  MOV8(scratch+8, scratch+9);

  GTE8(scratch+10, r, scratch+2, scratch+12);
  LTE8(scratch+11, r, scratch+3, scratch+13);
  LAND8(scratch+9, scratch+10, scratch+11);
  LOR8(scratch+8, scratch+8, scratch+9);

  GTE8(scratch+10, r, scratch+4, scratch+12);
  LTE8(scratch+11, r, scratch+5, scratch+13);
  LAND8(scratch+9, scratch+10, scratch+11);
  LOR8(scratch+8, scratch+8, scratch+9);

  GTE8(scratch+10, r, scratch+6, scratch+12);
  LTE8(scratch+11, r, scratch+7, scratch+13);
  LAND8(scratch+9, scratch+10, scratch+11);
  LOR8(scratch+8, scratch+8, scratch+9);

  return (REG8(scratch+8));
}

void insertString(reg_t r, const char* str, reg_t scratch)
{
  int i = 0;
  if (str == NULL)
  {
    return;
  }

  MOV16(scratch, r);
  while (str[i] != '\0')
  {
    MOVIM8(REG16(scratch), str[i]);
    INC16(scratch);
    i++; 
  } 
}

int main(void)
{
  int ret = 0;

  INIT_MACHINE();

  reg_t numCount    = 1;
  reg_t upCount     = 2;
  reg_t lowCount    = 3;
  reg_t specialCount  = 4;
  reg_t otherCount  = 5;
  reg_t spaceCount  = 6;

  MOVIM8(numCount, 0);
  MOVIM8(spaceCount, 0);
  MOVIM8(upCount, 0);
  MOVIM8(lowCount, 0);
  MOVIM8(specialCount, 0);
  MOVIM8(otherCount, 0);

  reg_t numString = 7;
  reg_t upString = 9;
  reg_t lowString = 11;
  reg_t spaceString = 13;
  reg_t specialString = 15;
  reg_t otherString = 17;
  reg_t newlineString = 19;

  MOVIM16(numString, ADDR(0));
  MOVIM16(spaceString, ADDR(16));
  MOVIM16(upString, ADDR(32));
  MOVIM16(lowString, ADDR(48));
  MOVIM16(specialString, ADDR(64));
  MOVIM16(otherString, ADDR(80));
  MOVIM16(newlineString, ADDR(96));


  reg_t i = 21;

  //                                  123456789012
  insertString(numString,     "numbers  = ", i);
  insertString(spaceString,   "spaces   = ", i);
  insertString(upString,      "uppers   = ", i);
  insertString(lowString,     "lowers   = ", i);
  insertString(specialString, "special  = ", i);
  insertString(otherString,   "other    = ", i);

  //endl
  MOVIM8(REG16(newlineString), '\n');
  MOVIM32(REG16(newlineString) + 1, 0);

  ret = getChar(i);
  while (ret != (-1))
  {
    if (isUpLetter(i, i+1))
    {
      INC8(upCount);
    }
    else if (isLowLetter(i, i+1))
    {
      INC8(lowCount);
    }
    else if (isNumber(i, i+1))
    {
      INC8(numCount);
    }
    else if (isSpace(i, i+1))
    {
#ifdef PATCHED
      INC8(spaceCount);
#else
      INC32(spaceCount);
#endif
    }
    else if (isSpecial(i, i+1))
    {
      INC8(specialCount);
    }
    else
    {
      INC8(otherCount);
    }
    printChar(i);
    ret = getChar(i);
  }

  printString(numString, i, i+4);
  printReg8(numCount, i);
  printString(newlineString, i, i+4);

  printString(upString, i, i+4);
  printReg8(upCount, i);
  printString(newlineString, i, i+4);

  printString(lowString, i, i+4);
  printReg8(lowCount, i);
  printString(newlineString, i, i+4);

  printString(spaceString, i, i+4);
  printReg8(spaceCount, i);
  printString(newlineString, i, i+4);

  printString(specialString, i, i+4);
  printReg8(specialCount, i);
  printString(newlineString, i, i+4);

  printString(otherString, i, i+4);
  printReg8(otherCount, i);
  printString(newlineString, i, i+4);

  return (0);
}

