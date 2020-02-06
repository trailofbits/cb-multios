#include "libcgc.h"

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef uint16_t reg_t;

// NOTE: Had to reduce the STATE_SIZE so that the segfault condition is easier to trigger - used to be 1024

#define STATE_SIZE (256)
#define NUM_CONSTANTS (6)
#define CONSTANT_SIZE (NUM_CONSTANTS * 4)
uint8_t* cgc_state = NULL; //[STATE_SIZE + CONSTANT_SIZE];
uint8_t* cgc__consts = NULL;

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

#define STATE8(_r)  ( *((uint8_t*)(cgc_state + _r))  )
#define STATE16(_r) ( *((uint16_t*)(cgc_state + _r)) )
#define STATE32(_r) ( *((uint32_t*)(cgc_state + _r)) )


#define REGLIMIT (STATE_SIZE / 2) 

#define ADDR(_r) (_r + REGLIMIT)

uint8_t cgc_DATA8(reg_t r)
{
 return (STATE8(r + REGLIMIT));
}

uint16_t cgc_DATA16(reg_t r)
{
 return (STATE16(r + REGLIMIT));
}

uint32_t cgc_DATA32(reg_t r)
{
 return (STATE32(r + REGLIMIT));
}

uint8_t cgc_REG8(reg_t r)
{
 return (STATE8(r));
}

uint16_t cgc_REG16(reg_t r)
{
 return (STATE16(r));
}

uint32_t cgc_REG32(reg_t r)
{
 return (STATE32(r));
}


void cgc_MOVIM8(reg_t r1, uint8_t im)
{
  STATE8(r1) = im;
}

void cgc_MOVIM16(reg_t r1, uint16_t im)
{
  STATE16(r1) = im;
}

void cgc_MOVIM32(reg_t r1, uint32_t im)
{
  STATE32(r1) = im;
}

void cgc_MOV8(reg_t r1, reg_t r2)
{
  STATE8(r1) = STATE8(r2);
}

void cgc_MOV16(reg_t r1, reg_t r2)
{
  STATE16(r1) = STATE16(r2);
}

void cgc_MOV32(reg_t r1, reg_t r2)
{
  STATE32(r1) = STATE32(r2);
}


void cgc_AND8(reg_t r1, reg_t r2, reg_t r3)
{
  STATE8(r1) = STATE8(r2) & STATE8(r3);
}

void cgc_AND16(reg_t r1, reg_t r2, reg_t r3)
{
  STATE16(r1) = STATE16(r2) & STATE16(r3);
}

void cgc_AND32(reg_t r1, reg_t r2, reg_t r3)
{
  STATE32(r1) = STATE32(r2) & STATE32(r3);
}

void cgc_OR8(reg_t r1, reg_t r2, reg_t r3)
{
  STATE8(r1) = STATE8(r2) | STATE8(r3);
}

void cgc_OR16(reg_t r1, reg_t r2, reg_t r3)
{
  STATE16(r1) = STATE16(r2) | STATE16(r3);
}

void cgc_OR32(reg_t r1, reg_t r2, reg_t r3)
{
  STATE32(r1) = STATE32(r2) | STATE32(r3);
}

void cgc_NOT8(reg_t r1, reg_t r2)
{
  STATE8(r1) = ~STATE8(r2);
}

void cgc_NOT16(reg_t r1, reg_t r2)
{
  STATE16(r1) = ~STATE16(r2);
}

void cgc_NOT32(reg_t r1, reg_t r2)
{
  STATE32(r1) = ~STATE32(r2);
}

void cgc_ADD8(reg_t r1, reg_t r2, reg_t r3)
{
  STATE8(r1) = STATE8(r2) + STATE8(r3);
}

void cgc_ADD16(reg_t r1, reg_t r2, reg_t r3)
{
  STATE16(r1) = STATE16(r2) + STATE16(r3);
}

void cgc_ADD32(reg_t r1, reg_t r2, reg_t r3)
{
  STATE32(r1) = STATE32(r2) + STATE32(r3);
}

void cgc_SUB8(reg_t r1, reg_t r2, reg_t r3)
{
  STATE8(r1) = STATE8(r2) - STATE8(r3);
}

void cgc_SUB16(reg_t r1, reg_t r2, reg_t r3)
{
  STATE16(r1) = STATE16(r2) - STATE16(r3);
}

void cgc_SUB32(reg_t r1, reg_t r2, reg_t r3)
{
  STATE32(r1) = STATE32(r2) - STATE32(r3);
}

void cgc_LAND8(reg_t r1, reg_t r2, reg_t r3)
{
  cgc_AND8(r1, r2, r3);
}

void cgc_LAND16(reg_t r1, reg_t r2, reg_t r3)
{
  cgc_AND16(r1, r2, r3);
}

void cgc_LAND32(reg_t r1, reg_t r2, reg_t r3)
{
  cgc_AND32(r1, r2, r3);
}

void cgc_LOR8(reg_t r1, reg_t r2, reg_t r3)
{
  cgc_OR8(r1, r2, r3);
}

void cgc_LOR16(reg_t r1, reg_t r2, reg_t r3)
{
  cgc_OR16(r1, r2, r3);
}

void cgc_LOR32(reg_t r1, reg_t r2, reg_t r3)
{
  cgc_OR32(r1, r2, r3);
}

void cgc_EQ8(reg_t r1, reg_t r2, reg_t r3)
{
  if (STATE8(r2) == STATE8(r3))
  {
    cgc_MOV8(r1, R_TRUE8);
  }
  else
  {
    cgc_MOV8(r1, R_FALSE);
  }
}

void cgc_EQ16(reg_t r1, reg_t r2, reg_t r3)
{
  if (STATE16(r2) == STATE16(r3))
  {
    cgc_MOV16(r1, R_TRUE16);
  }
  else
  {
    cgc_MOV16(r1, R_FALSE);
  }
}

void cgc_EQ32(reg_t r1, reg_t r2, reg_t r3)
{
  if (STATE32(r2) == STATE32(r3))
  {
    cgc_MOV32(r1, R_TRUE32);
  }
  else
  {
    cgc_MOV32(r1, R_FALSE);
  }
}

void cgc_GT8(reg_t r1, reg_t r2, reg_t r3)
{
  if (STATE8(r2) > STATE8(r3))
  {
    cgc_MOV8(r1, R_TRUE8);
  }
  else
  {
    cgc_MOV8(r1, R_FALSE);
  }
}

void cgc_GT16(reg_t r1, reg_t r2, reg_t r3)
{
  if (STATE16(r2) > STATE16(r3))
  {
    cgc_MOV16(r1, R_TRUE16);
  }
  else
  {
    cgc_MOV16(r1, R_FALSE);
  }
}

void cgc_GT32(reg_t r1, reg_t r2, reg_t r3)
{
  if (STATE32(r2) > STATE32(r3))
  {
    cgc_MOV32(r1, R_TRUE32);
  }
  else
  {
    cgc_MOV32(r1, R_FALSE);
  }
}


void cgc_GTE8(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_EQ8(r1, r2, r3);
  cgc_GT8(scratch, r2, r3);
  cgc_LOR8(r1, r1, scratch);  
}

void cgc_GTE16(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_EQ16(r1, r2, r3);
  cgc_GT16(scratch, r2, r3);
  cgc_LOR16(r1, r1, scratch);  
}

void cgc_GTE32(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_EQ32(r1, r2, r3);
  cgc_GT32(scratch, r2, r3);
  cgc_LOR32(r1, r1, scratch);  
}

void cgc_LT8(reg_t r1, reg_t r2, reg_t r3)
{
  cgc_GT8(r1, r3, r2);
}

void cgc_LT16(reg_t r1, reg_t r2, reg_t r3)
{
  cgc_GT16(r1, r3, r2);
}

void cgc_LT32(reg_t r1, reg_t r2, reg_t r3)
{
  cgc_GT32(r1, r3, r2);
}

void cgc_LTE8(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_GTE8(r1, r3, r2, scratch);
}

void cgc_LTE16(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_GTE16(r1, r3, r2, scratch);
}

void cgc_LTE32(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_GTE32(r1, r3, r2, scratch);
}

void cgc_INC8(reg_t r1)
{
  cgc_ADD8(r1, r1, R_ONE);
}

void cgc_INC16(reg_t r1)
{
  cgc_ADD16(r1, r1, R_ONE);
}

void cgc_INC32(reg_t r1)
{
  cgc_ADD32(r1, r1, R_ONE);
}

void cgc_DEC8(reg_t r1)
{
  cgc_SUB8(r1, r1, R_ONE);
}

void cgc_DEC16(reg_t r1)
{
  cgc_SUB16(r1, r1, R_ONE);
}

void cgc_DEC32(reg_t r1)
{
  cgc_SUB32(r1, r1, R_ONE);
}

void cgc_MUL32(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_MOV32(scratch, r2); 
  cgc_MOV32(scratch+4, r3); 

  //make sure this initialization is after r2 and r3 are already saved
  // otherwise, if r1 = r2 or r1 = r3, then we will have problems
  cgc_MOVIM32(r1, 0);

  cgc_GT32(scratch+8, r2, r3);
  if (cgc_REG32(scratch+8))
  {
    cgc_MOV32(scratch, r3);
    cgc_MOV32(scratch+4, r2);
  }

  
  cgc_GT32(scratch+8, scratch, R_ZERO);
  while (cgc_REG32(scratch+8))
  {
    cgc_ADD32(r1, r1, scratch+4);
    cgc_DEC32(scratch);
    cgc_GT32(scratch+8, scratch, R_ZERO);
  } 
}

void cgc_MUL16(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_MOVIM32(scratch, 0);
  cgc_MOV16(scratch, r1);
  cgc_MOVIM32(scratch+4, 0);
  cgc_MOV16(scratch+4, r2);
  cgc_MOVIM32(scratch+8, 0);
  cgc_MOV16(scratch+8, r3);
  cgc_MUL32(scratch, scratch+4, scratch+8, scratch+12);
  cgc_MOV16(r1, scratch);
}

void cgc_MUL8(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_MOVIM32(scratch, 0);
  cgc_MOV8(scratch, r1);
  cgc_MOVIM32(scratch+4, 0);
  cgc_MOV8(scratch+4, r2);
  cgc_MOVIM32(scratch+8, 0);
  cgc_MOV8(scratch+8, r3);
  cgc_MUL32(scratch, scratch+4, scratch+8, scratch+12);

  cgc_MOV8(r1, scratch);
}

void cgc_DIV32(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_MOV32(scratch, r2); 
  cgc_MOVIM32(r1, 0);

  cgc_EQ32(scratch+4, r3, R_ZERO);
  if (cgc_REG32(scratch+4))
  {
    goto _end;
  }

  
  cgc_GTE32(scratch+4, scratch, r3, scratch+8);
  cgc_GT32(scratch+8, scratch, R_ZERO);
  cgc_LAND32(scratch+12, scratch+4, scratch+8);
  while (cgc_REG32(scratch+12))
  {
    cgc_INC32(r1);
    cgc_SUB32(scratch, scratch, r3);
    cgc_GTE32(scratch+4, scratch, r3, scratch+8);
    cgc_GT32(scratch+8, scratch, R_ZERO);
    cgc_LAND32(scratch+12, scratch+4, scratch+8);
  } 

_end:
  return;
}

void cgc_DIV16(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_MOVIM32(scratch, 0);
  cgc_MOV16(scratch, r1);
  cgc_MOVIM32(scratch+4, 0);
  cgc_MOV16(scratch+4, r2);
  cgc_MOVIM32(scratch+8, 0);
  cgc_MOV16(scratch+8, r3);
  cgc_DIV32(scratch, scratch+4, scratch+8, scratch+12);
  cgc_MOV16(r1, scratch);
}

void cgc_DIV8(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_MOVIM32(scratch, 0);
  cgc_MOV8(scratch, r1);
  cgc_MOVIM32(scratch+4, 0);
  cgc_MOV8(scratch+4, r2);
  cgc_MOVIM32(scratch+8, 0);
  cgc_MOV8(scratch+8, r3);
  cgc_DIV32(scratch, scratch+4, scratch+8, scratch+12);

  cgc_MOV8(r1, scratch);
}

void cgc_REM32(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_MOV32(scratch, r2); 
  cgc_MOVIM32(r1, 0);

  cgc_EQ32(scratch+4, r3, R_ZERO);
  if (cgc_REG32(scratch+4))
  {
    goto _end;
  }

  cgc_GTE32(scratch+4, scratch, r3, scratch+16);
  cgc_GT32(scratch+8, scratch, R_ZERO);
  cgc_LAND32(scratch+12, scratch+4, scratch+8);
  while (cgc_REG32(scratch+12))
  {
    cgc_SUB32(scratch, scratch, r3);

    cgc_GTE32(scratch+4, scratch, r3, scratch+16);
    cgc_GT32(scratch+8, scratch, R_ZERO);
    cgc_LAND32(scratch+12, scratch+4, scratch+8);
  } 

  cgc_MOV32(r1, scratch);
_end:
  return;
}

void cgc_REM16(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_MOVIM32(scratch, 0);
  cgc_MOV16(scratch, r1);
  cgc_MOVIM32(scratch+4, 0);
  cgc_MOV16(scratch+4, r2);
  cgc_MOVIM32(scratch+8, 0);
  cgc_MOV16(scratch+8, r3);
  cgc_REM32(scratch, scratch+4, scratch+8, scratch+12);
  cgc_MOV16(r1, scratch);
}

void cgc_REM8(reg_t r1, reg_t r2, reg_t r3, reg_t scratch)
{
  cgc_MOVIM32(scratch, 0);
  cgc_MOV8(scratch, r1);
  cgc_MOVIM32(scratch+4, 0);
  cgc_MOV8(scratch+4, r2);
  cgc_MOVIM32(scratch+8, 0);
  cgc_MOV8(scratch+8, r3);
  cgc_REM32(scratch, scratch+4, scratch+8, scratch+12);

  cgc_MOV8(r1, scratch);
}

void cgc_INIT_MACHINE()
{
  int i = 0; 
  int ret  = 0;

  ret = cgc_allocate(STATE_SIZE + CONSTANT_SIZE, 0, (void**)(&cgc_state));

  if (ret != 0)
  {
    cgc__terminate(-1);
  }

  //NOTE: Had to move the state to the end of the memory range so that
  // the segfault is easier to trigger
  cgc_state = cgc_state + 0x1000 - STATE_SIZE - CONSTANT_SIZE;

  cgc__consts = cgc_state + STATE_SIZE;

  for (i = 0; i < STATE_SIZE; i+=4)
  {
    cgc_MOVIM32(i, 0);
  }

  cgc_MOVIM32(R_ZERO, 0);
  cgc_MOVIM32(R_ONE, 1);
  cgc_MOVIM32(R_TRUE8, TRUE8);
  cgc_MOVIM32(R_TRUE16, TRUE16);
  cgc_MOVIM32(R_TRUE32, TRUE32);
  cgc_MOVIM32(R_FALSE, FALSE);
}

void cgc_printChar(reg_t r)
{
  char c = cgc_REG8(r);
  cgc_size_t n;
  if (cgc_transmit(STDOUT, &c, 1, &n) != 0 || n != 1) {
     cgc__terminate(1);
  }
}

int cgc_getChar(reg_t r)
{
  char c;
  cgc_size_t rx_bytes;
  int ret = 0;
  cgc_fd_set fdsToWait;
  struct cgc_timeval timeToWait;
  timeToWait.tv_sec = 1;
  timeToWait.tv_usec = 0;
  int readyfds = 0;

  FD_ZERO(&fdsToWait);
  FD_SET(0, &fdsToWait);
  ret = cgc_fdwait(1, &fdsToWait, NULL, &timeToWait, &readyfds);
  if ( (ret != 0) || (readyfds != 1) )
  {
    return (-1);
  }

  ret = cgc_receive(STDIN, &c, 1, &rx_bytes);
  if ((ret != 0) || (rx_bytes == 0))
  {
    return (-1);
  }

  cgc_MOVIM8(r, c);
  return (0);
}


void cgc_printString(reg_t r, reg_t ret, reg_t scratch)
{
  reg_t temp = scratch;
  cgc_MOV16(temp, r); //temp pointer to string

  scratch += 2;
  cgc_MOVIM8(scratch, 0); //constant i
 
  loop1:
  cgc_MOV8(scratch+1, cgc_REG16(temp));

  cgc_EQ8(scratch+2, R_ZERO, scratch+1);
  if (cgc_REG8(scratch+2))
  {
    goto loop1_end;
  }
  cgc_printChar(scratch+1);
  cgc_INC8(scratch);
  cgc_INC16(temp);
  goto loop1;
  loop1_end: 

  cgc_MOV8(ret, scratch);
}

void cgc_printReg32(reg_t r, reg_t scratch)
{
  cgc_MOV32(scratch, r); //temporary r

  reg_t tens = scratch + 4;

  //tens table
  cgc_MOVIM32(tens,    1000000000);
  cgc_MOVIM32(tens+4,  100000000);
  cgc_MOVIM32(tens+8,  10000000);
  cgc_MOVIM32(tens+12, 1000000);
  cgc_MOVIM32(tens+16, 100000);
  cgc_MOVIM32(tens+20, 10000);
  cgc_MOVIM32(tens+24, 1000);
  cgc_MOVIM32(tens+28, 100);
  cgc_MOVIM32(tens+32, 10);
  cgc_MOVIM32(tens+36, 1);

  reg_t r_four = tens + 40;
  cgc_MOVIM16(r_four, 4);

 
  reg_t r_end = r_four+2;
  cgc_MOVIM16(r_end, tens + 40);

  reg_t i = r_end + 2;
  reg_t j = i+2;
  reg_t temp = j+2;

  cgc_MOVIM16(i, tens); 
  cgc_GT16(j, r_end, i);

  while (cgc_REG16(j))
  {
    cgc_DIV32(temp, scratch, cgc_REG16(i), temp + 5); 

    cgc_MOVIM8(temp + 4, '0');
    cgc_ADD8(temp + 4, temp + 4, temp); 
    cgc_printChar(temp + 4);
    cgc_REM32(scratch, scratch, cgc_REG16(i), temp + 5);
    
    cgc_ADD16(i, i, r_four);
    cgc_GT16(j, r_end, i);
  }
}

void cgc_printReg16(reg_t r, reg_t scratch)
{
  cgc_MOVIM32(scratch, 0);
  cgc_MOV16(scratch, r);
  cgc_printReg32(scratch, scratch + 4);
}

void cgc_printReg8(reg_t r, reg_t scratch)
{
  cgc_MOVIM32(scratch, 0);
  cgc_MOV8(scratch, r);
  cgc_printReg32(scratch, scratch + 4);
}

int cgc_isSpace(reg_t r, reg_t scratch)
{
  cgc_MOVIM8(scratch, ' ');
  cgc_MOVIM8(scratch+1, '\t');

  cgc_EQ8(scratch+2, r, scratch);
  cgc_EQ8(scratch+3, r, scratch+1);
  cgc_LOR8(scratch+2, scratch+2, scratch+3);
  return (cgc_REG8(scratch+2));
}

int cgc_isNumber(reg_t r, reg_t scratch)
{
  cgc_MOVIM8(scratch, '0');
  cgc_SUB8(scratch+1, r, scratch);
  cgc_MOVIM8(scratch+2, 10);

  cgc_LT8(scratch+3, scratch+1, scratch+2);
  return (cgc_REG8(scratch+3));
}

int cgc_isUpLetter(reg_t r, reg_t scratch)
{
  cgc_MOVIM8(scratch, 'A');
  cgc_MOVIM8(scratch+1, 'Z');

  cgc_GTE8(scratch+2, r, scratch, scratch+3);
  cgc_LTE8(scratch+3, r, scratch+1, scratch+4);
  cgc_LAND8(scratch+2, scratch+2, scratch+3);
  return (cgc_REG8(scratch+2));
}

int cgc_isLowLetter(reg_t r, reg_t scratch)
{
  cgc_MOVIM8(scratch, 'a');
  cgc_MOVIM8(scratch+1, 'z');

  cgc_GTE8(scratch+2, r, scratch, scratch+3);
  cgc_LTE8(scratch+3, r, scratch+1, scratch+4);
  cgc_LAND8(scratch+2, scratch+2, scratch+3);
  return (cgc_REG8(scratch+2));
}

int cgc_isSpecial(reg_t r, reg_t scratch)
{
  cgc_MOVIM8(scratch, '!');
  cgc_MOVIM8(scratch+1, '/');

  cgc_MOVIM8(scratch+2, ':');
  cgc_MOVIM8(scratch+3, '@');

  cgc_MOVIM8(scratch+4, '[');
  cgc_MOVIM8(scratch+5, '`');

  cgc_MOVIM8(scratch+6, 'P');
  cgc_MOVIM8(scratch+7, '~');

  
  cgc_GTE8(scratch+10, r, scratch, scratch+12);
  cgc_LTE8(scratch+11, r, scratch+1, scratch+13);
  cgc_LAND8(scratch+9, scratch+10, scratch+11);
  cgc_MOV8(scratch+8, scratch+9);

  cgc_GTE8(scratch+10, r, scratch+2, scratch+12);
  cgc_LTE8(scratch+11, r, scratch+3, scratch+13);
  cgc_LAND8(scratch+9, scratch+10, scratch+11);
  cgc_LOR8(scratch+8, scratch+8, scratch+9);

  cgc_GTE8(scratch+10, r, scratch+4, scratch+12);
  cgc_LTE8(scratch+11, r, scratch+5, scratch+13);
  cgc_LAND8(scratch+9, scratch+10, scratch+11);
  cgc_LOR8(scratch+8, scratch+8, scratch+9);

  cgc_GTE8(scratch+10, r, scratch+6, scratch+12);
  cgc_LTE8(scratch+11, r, scratch+7, scratch+13);
  cgc_LAND8(scratch+9, scratch+10, scratch+11);
  cgc_LOR8(scratch+8, scratch+8, scratch+9);

  return (cgc_REG8(scratch+8));
}

void cgc_insertString(reg_t r, const char* str, reg_t scratch)
{
  int i = 0;
  if (str == NULL)
  {
    return;
  }

  cgc_MOV16(scratch, r);
  while (str[i] != '\0')
  {
    cgc_MOVIM8(cgc_REG16(scratch), str[i]);
    cgc_INC16(scratch);
    i++; 
  } 
}

int main(int cgc_argc, char *cgc_argv[])
{
  int ret = 0;

  cgc_INIT_MACHINE();

  reg_t numCount    = 1;
  reg_t upCount     = 2;
  reg_t lowCount    = 3;
  reg_t specialCount  = 4;
  reg_t otherCount  = 5;
  reg_t spaceCount  = 6;

  cgc_MOVIM8(numCount, 0);
  cgc_MOVIM8(spaceCount, 0);
  cgc_MOVIM8(upCount, 0);
  cgc_MOVIM8(lowCount, 0);
  cgc_MOVIM8(specialCount, 0);
  cgc_MOVIM8(otherCount, 0);

  reg_t numString = 7;
  reg_t upString = 9;
  reg_t lowString = 11;
  reg_t spaceString = 13;
  reg_t specialString = 15;
  reg_t otherString = 17;
  reg_t newlineString = 19;

  cgc_MOVIM16(numString, ADDR(0));
  cgc_MOVIM16(spaceString, ADDR(16));
  cgc_MOVIM16(upString, ADDR(32));
  cgc_MOVIM16(lowString, ADDR(48));
  cgc_MOVIM16(specialString, ADDR(64));
  cgc_MOVIM16(otherString, ADDR(80));
  cgc_MOVIM16(newlineString, ADDR(96));


  reg_t i = 21;

  //                                  123456789012
  cgc_insertString(numString,     "numbers  = ", i);
  cgc_insertString(spaceString,   "spaces   = ", i);
  cgc_insertString(upString,      "uppers   = ", i);
  cgc_insertString(lowString,     "lowers   = ", i);
  cgc_insertString(specialString, "special  = ", i);
  cgc_insertString(otherString,   "other    = ", i);

  //endl
  cgc_MOVIM8(cgc_REG16(newlineString), '\n');
  cgc_MOVIM32(cgc_REG16(newlineString) + 1, 0);

  ret = cgc_getChar(i);
  while (ret != (-1))
  {
    if (cgc_isUpLetter(i, i+1))
    {
      cgc_INC8(upCount);
    }
    else if (cgc_isLowLetter(i, i+1))
    {
      cgc_INC8(lowCount);
    }
    else if (cgc_isNumber(i, i+1))
    {
      cgc_INC8(numCount);
    }
    else if (cgc_isSpace(i, i+1))
    {
#ifdef PATCHED
      cgc_INC8(spaceCount);
#else
      cgc_INC32(spaceCount);
#endif
    }
    else if (cgc_isSpecial(i, i+1))
    {
      cgc_INC8(specialCount);
    }
    else
    {
      cgc_INC8(otherCount);
    }
    cgc_printChar(i);
    ret = cgc_getChar(i);
  }

  cgc_printString(numString, i, i+4);
  cgc_printReg8(numCount, i);
  cgc_printString(newlineString, i, i+4);

  cgc_printString(upString, i, i+4);
  cgc_printReg8(upCount, i);
  cgc_printString(newlineString, i, i+4);

  cgc_printString(lowString, i, i+4);
  cgc_printReg8(lowCount, i);
  cgc_printString(newlineString, i, i+4);

  cgc_printString(spaceString, i, i+4);
  cgc_printReg8(spaceCount, i);
  cgc_printString(newlineString, i, i+4);

  cgc_printString(specialString, i, i+4);
  cgc_printReg8(specialCount, i);
  cgc_printString(newlineString, i, i+4);

  cgc_printString(otherString, i, i+4);
  cgc_printReg8(otherCount, i);
  cgc_printString(newlineString, i, i+4);

  return (0);
}

