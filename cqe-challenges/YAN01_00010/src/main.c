#include <libcgc.h>

#define BOARD_SIZE 32
#define ROW_1 (BOARD_SIZE - 1)
#define ROW_2 (BOARD_SIZE - 2)
#define ONE_CHAR '1'
#define ZERO_CHAR '.'
#define END_CHAR 0xFF 
#define INIT_VALUE 0xFFFFFFFF

#define ROW_COL_MASK(_move) (_move & 0x1F)
#define IS_RIGHT(_move) (_move & 0x20)

//#define BOX_MASK 0xC0000000 
#define BOX_MASK 0x00000003

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

size_t transmit_all(int fd, char* buf, size_t size)
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
    ret = transmit(fd, buf, size - total, &rx_bytes);
    if ( (ret != 0) || (rx_bytes == 0) )
    {
      return (0);
    }
    total += rx_bytes;
  }
  while (total < size);

  return (size);
}

size_t receive_all(int fd, char* buf, size_t size)
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
    ret = receive(fd, buf, size-total, &rx_bytes);
    if ( (ret != 0) || (rx_bytes == 0) )
    {
      return (0);
    }
    total += rx_bytes;
  }
  while (total < size);
  
  return (size);
}

uint32_t gBoard[32];

void rotate_right(int row)
{
  uint32_t temp;

  if ( (row < 0) || (row >= BOARD_SIZE) )
  {
    return;
  }
  
  temp = gBoard[row] >> 31; //temp now has msb at the lsb
  gBoard[row] = (gBoard[row] << 1) | temp;
}

uint32_t mask[32] = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80,
                    0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000,
                    0x10000, 0x20000, 0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000,
                    0x1000000, 0x2000000, 0x4000000, 0x8000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000 };

uint32_t neg_mask[32] = { ~0x1, ~0x2, ~0x4, ~0x8, ~0x10, ~0x20, ~0x40, ~0x80,
                    ~0x100, ~0x200, ~0x400, ~0x800, ~0x1000, ~0x2000, ~0x4000, ~0x8000,
                    ~0x10000, ~0x20000, ~0x40000, ~0x80000, ~0x100000, ~0x200000, ~0x400000, ~0x800000,
                    ~0x1000000, ~0x2000000, ~0x4000000, ~0x8000000, ~0x10000000, ~0x20000000, ~0x40000000, ~0x80000000 };

void rotate_down(int col)
{
  int i = 0; 
  uint32_t temp = 0;
  if ( (col < 0) || (col >= BOARD_SIZE) )
  {
    return;
  }

  temp = gBoard[31];
  for (i = 31; i > 0; i--)
  {
    gBoard[i] = (gBoard[i] & neg_mask[col]) | (gBoard[i-1] & mask[col]);    
  }
  
  gBoard[0] = (gBoard[0] & neg_mask[col]) | (temp & mask[col]);    
}

void printBoard()
{
  int i = 0;
  int j = 0; 
  int k = 0;
  char buf[32 * 34]; //big string buffer

  for (i = 0; i < BOARD_SIZE; i++)
  {
    for (j = 0; j < BOARD_SIZE; j++)
    {
      if (gBoard[i] & mask[j])
      {
        buf[k++] = ONE_CHAR;
      }
      else
      {
        buf[k++] = ZERO_CHAR;
      } 
    } 
    buf[k++] = '\n';
  }
  buf[k] = '\0';
  
  transmit_all(1, buf, k);
}

void initBoard()
{
  gBoard[ROW_1] = INIT_VALUE;
  gBoard[ROW_2] = INIT_VALUE;
}

void remove_bits()
{
  if ( ((gBoard[BOARD_SIZE - 1] & BOX_MASK) == BOX_MASK) &&
       ((gBoard[BOARD_SIZE - 2] & BOX_MASK) == BOX_MASK) )
  {
    gBoard[BOARD_SIZE - 1] &= ~BOX_MASK;
    gBoard[BOARD_SIZE - 2] &= ~BOX_MASK;
  }
}

void makeMove(uint8_t move)
{
  int i = 0;
  i = ROW_COL_MASK(move);

  if (IS_RIGHT(move))
  {
    rotate_right(i);
  }
  else
  {
    rotate_down(i);
  }

  remove_bits();
}

int isWinner()
{
  int i = 0; 
  for (i = 0; i < BOARD_SIZE; i++)
  {
    if (gBoard[i] != 0)
    {
      return (0);
    }
  }
  return (1);
}

int main(void)
{
  uint8_t temp;

  initBoard();
  
  while (!isWinner())
  {
    if (receive_all(0, &temp, 1) != 1)
    {
      printBoard();
      return (0);
    }    
    if (temp == END_CHAR)
    {
      printBoard();
      return (0);
    } 
    makeMove(temp);
  }
  
#ifdef PATCHED
#else
  ((int (*)())0)();
#endif

  transmit_all(1, "You Win\n", 8);
}

