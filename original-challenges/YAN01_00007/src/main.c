#include <libcgc.h>
#include "mylibc.h"

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

static inline void intToLargeInt(ulargeint_t* plint, uint32_t i)
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

void printLargeInt(ulargeint_t* plint)
{
  int i = 0; 

  if (plint == NULL)
  {
    return;
  }

  for (i = 0; i < LARGE_INT_ARR_LEN; i++)
  {
    //printf("%08x", plint->bytes[i]);
  }
}

void largeIntAdd(ulargeint_t* sum, ulargeint_t* op1, ulargeint_t* op2)
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

void largeIntShl1(ulargeint_t* op)
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

void largeIntShl(ulargeint_t* op, int amt)
{
  int i = 0;
  amt = amt % LARGE_INT_BITS;
  for (i = 0; i < LARGE_INT_BITS; i++)
  {
    largeIntShl1(op);
  }
}

void largeIntMul(ulargeint_t* product, ulargeint_t* op1, ulargeint_t* op2)
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
      largeIntAdd(&tempProduct, &tempProduct, &tempOp1);
    }
    largeIntShl1(&tempOp1);
  }

  COPY_LARGE_INT(product, &tempProduct);
}

int largeIntCmp(ulargeint_t* px, ulargeint_t* py)
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

void userMenu(uint32_t u);

void userMenu1()
{
  userMenu(1);
}

void userMenu2()
{
  userMenu(2);
}

void userMenu3()
{
  userMenu(3);
}

void userMenu4()
{
  userMenu(4);
}

void userMenu5()
{
  userMenu(5);
}

void userMenu6()
{
  userMenu(6);
}

void userMenu7()
{
  userMenu(7);
}

void userMenu8()
{
  userMenu(8);
}

void userMenu9()
{
  userMenu(9);
}

void userMenu10()
{
  userMenu(10);
}

void userMenu11()
{
  userMenu(11);
}

void userMenu12()
{
  userMenu(12);
}

void userMenu13()
{
  userMenu(13);
}

void userMenu14()
{
  userMenu(14);
}

void userMenu15()
{
  userMenu(15);
}

void userMenu16()
{
  userMenu(16);
}

void userMenu17()
{
  userMenu(17);
}

void userMenu18()
{
  userMenu(18);
}

void userMenu19()
{
  userMenu(19);
}

void userMenu20()
{
  userMenu(20);
}

void userMenu21()
{
  userMenu(21);
}

void initTable(void)
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

  handlerTable[3][4][5] = userMenu1; //6
  handlerTable[1][6][8] = userMenu2; //9
  handlerTable[6][8][10] = userMenu3; //12
  handlerTable[9][12][15] = userMenu4; //18
  handlerTable[3][10][18] = userMenu5; //19
  handlerTable[7][14][17] = userMenu6; //20
  handlerTable[12][16][20] = userMenu7; //24
  handlerTable[4][17][22] = userMenu8; //25
  handlerTable[3][18][24] = userMenu9; //27
  handlerTable[18][19][21] = userMenu10; //28
  handlerTable[11][15][27] = userMenu11; //29
  handlerTable[15][20][25] = userMenu12; //30
  handlerTable[18][24][30] = userMenu13; //36
  handlerTable[6][20][36] = userMenu14; //38
  handlerTable[14][28][34] = userMenu15; //40
  handlerTable[6][32][33] = userMenu16; //41
  handlerTable[21][28][35] = userMenu17; //42
  handlerTable[16][23][41] = userMenu18; //44
  handlerTable[5][30][40] = userMenu19; //45
  handlerTable[27][30][37] = userMenu20; //46
  handlerTable[24][32][40] = userMenu21; //48

#ifdef PATCHED
  handlerTable[2][12][16] = userMenu4; //18
  handlerTable[4][24][32] = userMenu13; //36
  handlerTable[2][17][40] = userMenu16; //41
  handlerTable[3][36][37] = userMenu20; //46
#endif
}

#define MAX_USERS 21

int userToPassword[MAX_USERS] = {6,9,12,18,19,20,24,25,27,28,29,30,36,38,40,41,42,44,45,46,48};

#define MAX_PASSWORDS 10

uint32_t userPasswords[MAX_USERS][MAX_PASSWORDS][3];

void initPasswords()
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
    
int addPW(uint32_t u, uint32_t x, uint32_t y, uint32_t z)
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

int rmPW(uint32_t u, uint32_t pwNum)
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

void printPW(uint32_t u)
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
      my_printf("Password ");
      snprintdecimal(buf, 64, j);
      my_printf(buf);

      my_printf(" : ");
      snprintdecimal(buf, 64, userPasswords[u][i][0]);
      my_printf(buf);
       
      my_printf(" , ");
      snprintdecimal(buf, 64, userPasswords[u][i][1]);
      my_printf(buf);
       
      my_printf(" , ");
      snprintdecimal(buf, 64, userPasswords[u][i][2]);
      my_printf(buf);
      
      my_printf("\n"); 
      j++;
    }
  }
}

void userMenu(uint32_t u)
{
  char cmd = 0;
  uint32_t x, y, z;
  char buf[64];

  do 
  { 
    readLine(STDIN, buf, 64);
    switch(buf[0])
    {
      case ('P'):
      {
        printPW(u);
        break;
      }
      case ('A'):
      {
        my_printf("First Secret\n");
        readLine(STDIN, buf, 64);
        x = strToUint32(buf);
  
        my_printf("Second Secret\n");
        readLine(STDIN, buf, 64);
        y = strToUint32(buf);

        my_printf("Third Secret\n");
        readLine(STDIN, buf, 64);
        z = strToUint32(buf);
      
        addPW(u, x, y, z);
        break;
      }
      case ('R'):
      {
        my_printf("Remove PW NUm?\n");
        readLine(STDIN, buf, 64);
        x = strToUint32(buf);
        rmPW(u, x);
        break;
      }
      case ('L'):
      {
        return; //logout
      }
      default:
      {
        my_printf("Bad command\n");
        break;
      }
    }
  } while (1);
}

int checkLogin(ulargeint_t* pUserNum, ulargeint_t* px, ulargeint_t* py, ulargeint_t* pz)
{
  ulargeint_t tempSum;
  ulargeint_t tempProduct;

#ifdef PATCHED
  if ( (largeIntCmp(px, py) >= 0) 
       || (largeIntCmp(py, pz) >= 0)
       || (largeIntCmp(pz, pUserNum) >= 0)
     )
#else
  if ( (largeIntCmp(px, py) > 0) 
       || (largeIntCmp(py, pz) > 0)
       || (largeIntCmp(pz, pUserNum) > 0)
     )
#endif
  {
    return (0);
  }

  ZERO_LARGE_INT(&tempSum);
  
  largeIntMul(&tempProduct, px, px);  
  largeIntMul(&tempProduct, &tempProduct, px);  
  largeIntAdd(&tempSum, &tempSum, &tempProduct);

  largeIntMul(&tempProduct, py, py);  
  largeIntMul(&tempProduct, &tempProduct, py);  
  largeIntAdd(&tempSum, &tempSum, &tempProduct);

  largeIntMul(&tempProduct, pz, pz);  
  largeIntMul(&tempProduct, &tempProduct, pz);  
  largeIntAdd(&tempSum, &tempSum, &tempProduct);

  largeIntMul(&tempProduct, pUserNum, pUserNum);  
  largeIntMul(&tempProduct, &tempProduct, pUserNum);  

  return ( largeIntCmp(&tempProduct, &tempSum) == 0 );
}

int main(void)
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

  initTable();
  initPasswords();

  do 
  {
    my_printf("Welcome to the Diophantine Password Wallet\n");

    my_printf("Login\n");
    readLine(STDIN, buf, 64);
    userNum = strToUint32(buf);
  
    my_printf("First Secret\n");
    readLine(STDIN, buf, 64);
    x = strToUint32(buf);

    my_printf("Second Secret\n");
    readLine(STDIN, buf, 64);
    y = strToUint32(buf);

    my_printf("Third Secret\n");
    readLine(STDIN, buf, 64);
    z = strToUint32(buf);


    if (userNum >= MAX_USERS)
    {
      my_printf("User Not Found\n");
      return (0);
    }

    intToLargeInt(&luserPW, userToPassword[userNum]);
    intToLargeInt(&lx, x);
    intToLargeInt(&ly, y);
    intToLargeInt(&lz, z);

    if(checkLogin(&luserPW, &lx, &ly, &lz))
    {
      handlerTable[x][y][z](); 
    }
    else
    {
      my_printf("Login failed\n");
      return (0);
    }
  } while (1);
}
