#include "libcgc.h"
#include "cgc_mylibc.h"

typedef void (*handler_func_t)(void);

//The 256bit large int is bytes[0] is the highest byte and bytes[7]
#define LARGE_INT_BITS 256
#define LARGE_INT_BYTES (LARGE_INT_BITS/8)
#define LARGE_INT_ARR_LEN (LARGE_INT_BYTES / sizeof(uint32_t))
#define BITS_IN_UINT32 (sizeof(uint32_t) * 8)

typedef struct _ulargeint_t 
{
  uint32_t bytes[LARGE_INT_ARR_LEN];
} ulargeint_t;

#define ZERO_LARGE_INT(_li) 				\
do							\
{							\
  for (int _i = 0; _i < LARGE_INT_ARR_LEN; _i++)	\
  {							\
    (_li)->bytes[_i] = 0;					\
  }							\
}							\
while (0)

#define COPY_LARGE_INT(_dst, _src) 				\
do							\
{							\
  for (int _i = 0; _i < LARGE_INT_ARR_LEN; _i++)	\
  {							\
    (_dst)->bytes[_i] = (_src)->bytes[_i];			\
  }							\
}							\
while (0)

static inline void cgc_intToLargeInt(ulargeint_t* plint, uint32_t i)
{
  if (plint == NULL)
  {
    return;
  }
  ZERO_LARGE_INT(plint);
  plint->bytes[LARGE_INT_ARR_LEN - 1] = i;  
}

static inline void largeIntToInt(uint32_t* pi, ulargeint_t* plint)
{
  if ( (pi == NULL) || (plint == NULL) )
  {
    return;
  }
  
  *pi = plint->bytes[LARGE_INT_ARR_LEN - 1];
}

void cgc_printLargeInt(ulargeint_t* plint)
{
  int i = 0; 

  if (plint == NULL)
  {
    return;
  }

  for (i = 0; i < LARGE_INT_ARR_LEN; i++)
  {
    //cgc_printf("%08x", plint->bytes[i]);
  }
}

void cgc_largeIntAdd(ulargeint_t* sum, ulargeint_t* op1, ulargeint_t* op2)
{
  uint64_t tempSum = 0;
  uint64_t tempOp1 = 0;
  uint64_t tempOp2 = 0;
  int i = 0;

  if ( (sum == NULL) || (op1 == NULL) || (op2 == NULL) )
  {
    return;
  }

  for (i = 0; i < LARGE_INT_ARR_LEN; i++)
  {
    tempOp1 = op1->bytes[LARGE_INT_ARR_LEN - 1 - i];
    tempOp2 = op2->bytes[LARGE_INT_ARR_LEN - 1 - i];
    tempSum = tempSum + tempOp1 + tempOp2;
    sum->bytes[LARGE_INT_ARR_LEN - 1 - i] = (uint32_t)(tempSum & 0xFFFFFFFF);
    tempSum = tempSum >> (BITS_IN_UINT32);
  }
}

void cgc_largeIntShl1(ulargeint_t* op)
{
  int i = 0;
  if (op == NULL)
  {
    return;
  }

  for (i = 0; i < (LARGE_INT_ARR_LEN - 1); i++)
  {
    op->bytes[i] = op->bytes[i] << 1;
    op->bytes[i] = op->bytes[i] | ( (op->bytes[i+1] & 0x80000000) >> 31 );
  }
  op->bytes[LARGE_INT_ARR_LEN - 1] = op->bytes[LARGE_INT_ARR_LEN - 1] << 1;
}

void cgc_largeIntShl(ulargeint_t* op, int amt)
{
  int i = 0;
  amt = amt % LARGE_INT_BITS;
  for (i = 0; i < LARGE_INT_BITS; i++)
  {
    cgc_largeIntShl1(op);
  }
}

void cgc_largeIntMul(ulargeint_t* product, ulargeint_t* op1, ulargeint_t* op2)
{
  ulargeint_t tempOp1;
  ulargeint_t tempProduct;

  int i = 0;

  if ( (product == NULL) || (op1 == NULL) || (op2 == NULL) )
  {
    return;
  }

  ZERO_LARGE_INT(&tempProduct);
  COPY_LARGE_INT(&tempOp1, op1);

  for (i = 0; i < LARGE_INT_BITS; i++)
  {
    if (op2->bytes[LARGE_INT_ARR_LEN - 1 - (i / (BITS_IN_UINT32))] & (0x1 << (i % (BITS_IN_UINT32))))
    {
      cgc_largeIntAdd(&tempProduct, &tempProduct, &tempOp1);
    }
    cgc_largeIntShl1(&tempOp1);
  }

  COPY_LARGE_INT(product, &tempProduct);
}

int cgc_largeIntCmp(ulargeint_t* px, ulargeint_t* py)
{
  int i = 0;

  if ( (px == NULL) || (py == NULL) )
  {
    return 0;
  }
 
  for (i = 0; i < LARGE_INT_ARR_LEN; i++)
  {
    if (px->bytes[i] > py->bytes[i])
    {
      return (1);
    }
    else if (px->bytes[i] < py->bytes[i])
    {
      return (-1);
    }
  }
  return (0);
}



#define HANDLER_TABLE_SIZE 50
handler_func_t handlerTable[HANDLER_TABLE_SIZE][HANDLER_TABLE_SIZE][HANDLER_TABLE_SIZE];

void cgc_userMenu(uint32_t u);

void cgc_userMenu1()
{
  cgc_userMenu(1);
}

void cgc_userMenu2()
{
  cgc_userMenu(2);
}

void cgc_userMenu3()
{
  cgc_userMenu(3);
}

void cgc_userMenu4()
{
  cgc_userMenu(4);
}

void cgc_userMenu5()
{
  cgc_userMenu(5);
}

void cgc_userMenu6()
{
  cgc_userMenu(6);
}

void cgc_userMenu7()
{
  cgc_userMenu(7);
}

void cgc_userMenu8()
{
  cgc_userMenu(8);
}

void cgc_userMenu9()
{
  cgc_userMenu(9);
}

void cgc_userMenu10()
{
  cgc_userMenu(10);
}

void cgc_userMenu11()
{
  cgc_userMenu(11);
}

void cgc_userMenu12()
{
  cgc_userMenu(12);
}

void cgc_userMenu13()
{
  cgc_userMenu(13);
}

void cgc_userMenu14()
{
  cgc_userMenu(14);
}

void cgc_userMenu15()
{
  cgc_userMenu(15);
}

void cgc_userMenu16()
{
  cgc_userMenu(16);
}

void cgc_userMenu17()
{
  cgc_userMenu(17);
}

void cgc_userMenu18()
{
  cgc_userMenu(18);
}

void cgc_userMenu19()
{
  cgc_userMenu(19);
}

void cgc_userMenu20()
{
  cgc_userMenu(20);
}

void cgc_userMenu21()
{
  cgc_userMenu(21);
}

void cgc_initTable(void)
{
  int i = 0;
  int j = 0;
  int k = 0;
  for (i = 0; i < HANDLER_TABLE_SIZE; i++)
  {
    for (j = 0; j < HANDLER_TABLE_SIZE; j++)
    {
      for (k = 0; k < HANDLER_TABLE_SIZE; k++)
      {
        handlerTable[i][j][k] = NULL;
      }
    }
  }

  handlerTable[3][4][5] = cgc_userMenu1; //6
  handlerTable[1][6][8] = cgc_userMenu2; //9
  handlerTable[6][8][10] = cgc_userMenu3; //12
  handlerTable[9][12][15] = cgc_userMenu4; //18
  handlerTable[3][10][18] = cgc_userMenu5; //19
  handlerTable[7][14][17] = cgc_userMenu6; //20
  handlerTable[12][16][20] = cgc_userMenu7; //24
  handlerTable[4][17][22] = cgc_userMenu8; //25
  handlerTable[3][18][24] = cgc_userMenu9; //27
  handlerTable[18][19][21] = cgc_userMenu10; //28
  handlerTable[11][15][27] = cgc_userMenu11; //29
  handlerTable[15][20][25] = cgc_userMenu12; //30
  handlerTable[18][24][30] = cgc_userMenu13; //36
  handlerTable[6][20][36] = cgc_userMenu14; //38
  handlerTable[14][28][34] = cgc_userMenu15; //40
  handlerTable[6][32][33] = cgc_userMenu16; //41
  handlerTable[21][28][35] = cgc_userMenu17; //42
  handlerTable[16][23][41] = cgc_userMenu18; //44
  handlerTable[5][30][40] = cgc_userMenu19; //45
  handlerTable[27][30][37] = cgc_userMenu20; //46
  handlerTable[24][32][40] = cgc_userMenu21; //48

#ifdef PATCHED
  handlerTable[2][12][16] = cgc_userMenu4; //18
  handlerTable[4][24][32] = cgc_userMenu13; //36
  handlerTable[2][17][40] = cgc_userMenu16; //41
  handlerTable[3][36][37] = cgc_userMenu20; //46
#endif
}

#define MAX_USERS 21

int userToPassword[MAX_USERS] = {6,9,12,18,19,20,24,25,27,28,29,30,36,38,40,41,42,44,45,46,48};

#define MAX_PASSWORDS 10

uint32_t userPasswords[MAX_USERS][MAX_PASSWORDS][3];

void cgc_initPasswords()
{
  for (int i = 0; i < MAX_USERS; i++)
  {
    for (int j = 0; j < MAX_PASSWORDS; j++)
    {
      userPasswords[i][j][0] = 0;
      userPasswords[i][j][1] = 0;
      userPasswords[i][j][2] = 0;
    }
  }
}
    
int cgc_addPW(uint32_t u, uint32_t x, uint32_t y, uint32_t z)
{
  int i = 0;
  for (i = 0; i < MAX_PASSWORDS; i++)
  {
    if ( (userPasswords[u][i][0] == 0)  
        && (userPasswords[u][i][1] == 0)
        && (userPasswords[u][i][2] == 0)
       )
    {
      userPasswords[u][i][0] = x;
      userPasswords[u][i][1] = y;
      userPasswords[u][i][2] = z;
      return (0);
    }
  }
    
  return (-1);
}

int cgc_rmPW(uint32_t u, uint32_t pwNum)
{
  int i = 0;
  int j = 0;
  for (i = 0; i < MAX_PASSWORDS; i++)
  {
    if ( (userPasswords[u][i][0] != 0)  
        && (userPasswords[u][i][1] != 0)
        && (userPasswords[u][i][2] != 0)
       )
    {
      if (j == pwNum)
      {
        userPasswords[u][i][0] = 0;
        userPasswords[u][i][1] = 0;
        userPasswords[u][i][2] = 0;
        return (0);
      }
      else
      {
        j++;
      }
    }
  }

  return (-1);
}

void cgc_printPW(uint32_t u)
{
  int i = 0;
  int j = 0;
  char buf[64];

  for (i = 0; i < MAX_PASSWORDS;  i++)
  {
    if ( (userPasswords[u][i][0] != 0)
        || (userPasswords[u][i][1] != 0)
        || (userPasswords[u][i][2] != 0)
       )
    {
      cgc_my_printf("Password ");
      cgc_snprintdecimal(buf, 64, j);
      cgc_my_printf(buf);

      cgc_my_printf(" : ");
      cgc_snprintdecimal(buf, 64, userPasswords[u][i][0]);
      cgc_my_printf(buf);
       
      cgc_my_printf(" , ");
      cgc_snprintdecimal(buf, 64, userPasswords[u][i][1]);
      cgc_my_printf(buf);
       
      cgc_my_printf(" , ");
      cgc_snprintdecimal(buf, 64, userPasswords[u][i][2]);
      cgc_my_printf(buf);
      
      cgc_my_printf("\n"); 
      j++;
    }
  }
}

void cgc_userMenu(uint32_t u)
{
  char cmd = 0;
  uint32_t x, y, z;
  char buf[64];

  do 
  { 
    cgc_readLine(STDIN, buf, 64);
    switch(buf[0])
    {
      case ('P'):
      {
        cgc_printPW(u);
        break;
      }
      case ('A'):
      {
        cgc_my_printf("First Secret\n");
        cgc_readLine(STDIN, buf, 64);
        x = cgc_strToUint32(buf);
  
        cgc_my_printf("Second Secret\n");
        cgc_readLine(STDIN, buf, 64);
        y = cgc_strToUint32(buf);

        cgc_my_printf("Third Secret\n");
        cgc_readLine(STDIN, buf, 64);
        z = cgc_strToUint32(buf);
      
        cgc_addPW(u, x, y, z);
        break;
      }
      case ('R'):
      {
        cgc_my_printf("Remove PW NUm?\n");
        cgc_readLine(STDIN, buf, 64);
        x = cgc_strToUint32(buf);
        cgc_rmPW(u, x);
        break;
      }
      case ('L'):
      {
        return; //logout
      }
      default:
      {
        cgc_my_printf("Bad command\n");
        break;
      }
    }
  } while (1);
}

int cgc_checkLogin(ulargeint_t* pUserNum, ulargeint_t* px, ulargeint_t* py, ulargeint_t* pz)
{
  ulargeint_t tempSum;
  ulargeint_t tempProduct;

#ifdef PATCHED
  if ( (cgc_largeIntCmp(px, py) >= 0) 
       || (cgc_largeIntCmp(py, pz) >= 0)
       || (cgc_largeIntCmp(pz, pUserNum) >= 0)
     )
#else
  if ( (cgc_largeIntCmp(px, py) > 0) 
       || (cgc_largeIntCmp(py, pz) > 0)
       || (cgc_largeIntCmp(pz, pUserNum) > 0)
     )
#endif
  {
    return (0);
  }

  ZERO_LARGE_INT(&tempSum);
  
  cgc_largeIntMul(&tempProduct, px, px);  
  cgc_largeIntMul(&tempProduct, &tempProduct, px);  
  cgc_largeIntAdd(&tempSum, &tempSum, &tempProduct);

  cgc_largeIntMul(&tempProduct, py, py);  
  cgc_largeIntMul(&tempProduct, &tempProduct, py);  
  cgc_largeIntAdd(&tempSum, &tempSum, &tempProduct);

  cgc_largeIntMul(&tempProduct, pz, pz);  
  cgc_largeIntMul(&tempProduct, &tempProduct, pz);  
  cgc_largeIntAdd(&tempSum, &tempSum, &tempProduct);

  cgc_largeIntMul(&tempProduct, pUserNum, pUserNum);  
  cgc_largeIntMul(&tempProduct, &tempProduct, pUserNum);  

  return ( cgc_largeIntCmp(&tempProduct, &tempSum) == 0 );
}

int main(int cgc_argc, char *cgc_argv[])
{
  ulargeint_t luserPW;
  ulargeint_t lx;
  ulargeint_t ly;
  ulargeint_t lz;
  uint32_t userNum = 0;
  uint32_t x = 0;
  uint32_t y = 0;
  uint32_t z = 0;
  char buf[64];

  cgc_initTable();
  cgc_initPasswords();

  do 
  {
    cgc_my_printf("Welcome to the Diophantine Password Wallet\n");

    cgc_my_printf("Login\n");
    cgc_readLine(STDIN, buf, 64);
    userNum = cgc_strToUint32(buf);
  
    cgc_my_printf("First Secret\n");
    cgc_readLine(STDIN, buf, 64);
    x = cgc_strToUint32(buf);

    cgc_my_printf("Second Secret\n");
    cgc_readLine(STDIN, buf, 64);
    y = cgc_strToUint32(buf);

    cgc_my_printf("Third Secret\n");
    cgc_readLine(STDIN, buf, 64);
    z = cgc_strToUint32(buf);


    if (userNum >= MAX_USERS)
    {
      cgc_my_printf("User Not Found\n");
      return (0);
    }

    cgc_intToLargeInt(&luserPW, userToPassword[userNum]);
    cgc_intToLargeInt(&lx, x);
    cgc_intToLargeInt(&ly, y);
    cgc_intToLargeInt(&lz, z);

    if(cgc_checkLogin(&luserPW, &lx, &ly, &lz))
    {
      handlerTable[x][y][z](); 
    }
    else
    {
      cgc_my_printf("Login failed\n");
      return (0);
    }
  } while (1);
}
