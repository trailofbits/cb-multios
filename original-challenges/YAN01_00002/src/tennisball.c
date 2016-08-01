//#include "linux_wrapper.c"
#include <libcgc.h>
#include "tennisball.h"
#include "mylibc.h"

//minlen is used for leading 0's in the fractional part
int snprintdecimal(char* str, size_t len, uint32_t num, int minlen)
{
  int i = 0;
  int j = 0;
  uint32_t rem = 0;
  char temp[24]; //the maximum uint64_t value is 2^64 - 1
                 // which is approx 10^20 so 24 characters should be good
  temp[0] = '0';
  temp[0] = '\0';

  if ( (str == NULL) || (len < 2) || (len <= minlen) )
  {
    return (-1);
  }

  if (num == 0)
  {
    str[0] = '0';
    str[1] = '\0';
    return (1);
  }

  while (num != 0)
  {
    rem = num % 10; //get the remainder
    temp[i] = '0' + rem;
    num = num / 10; //divide it by 10 
    i++;
  }

  //fill in the leading zeroes
  for (j = 0; j < (minlen - i); j++)
  {
    str[j] = '0';
  }
 
  //now see if everything fits
  if (i < len)
  {
    //remember this is NOT a null terminated string
    i--; // decrement i first to get to the last character written
    while (i >= 0)
    {
      str[j] = temp[i]; 
      j++; //move j up
      i--; //move i down
    }  
    str[j] = '\0';
    return (j);
  }

  //now lets end the string by setting the NULL character
  return (-1); 
}

int snprintfloat(char* str, size_t len, float num)
{
  char tempStr[24];
  uint32_t iNum = 0;
  iNum = (uint32_t)num;
  int ret = 0;

  tempStr[0] = '0';
  tempStr[0] = '\0';
  //it seems that casting is the FLOOR function by default
  // do we need to enforce this?

  ret = snprintdecimal(str, len, iNum, 0);
  if (ret < 0)
  {
    return (ret);
  }

  if ( (ret + 1) < len)
  {
    str[ret] = '.';
    str[ret + 1] = '\0';

    iNum = (uint32_t)((num - (float)iNum) * (float)1000000.0);//get the next 6 numbers
    return (snprintdecimal(str+ret+1, len - ret - 1, iNum, 6)); 
  }
  return (-1);
}


/**
 * The maximum unsigned value is 4294967295 which is 0xFFFFFFFF
 * So the idea is to read in up to 9 digits and then convert that
 * into a uint64_t. We need a uint64_t because 9999999999 will overflow
 * uint32_t. 
 *
 * A 0 is returned - either because that is the actual number or because
 * the first 9 characters are not digits (NULL, '.' and ',' are all
 * terminal characters). Any subsequent characters are
 * simply ignored.
*/
uint32_t strToUint32(const char* str)
{
  int i = 0; 
  uint64_t val = 0; 
  uint32_t temp = 0;

  if (str == NULL)
  {
    return (0);
  }

  //the maximum unsigned value is 4294967295 which is 0xFFFFFFFF
  while ( (str[i] != '\0') && (str[i] != '\n') && (str[i] != '.') && (str[i] != ',') && (i < 9) )
  {
    if ( (str[i] >= '0') &&  (str[i] <= '9') )
    {
      temp = str[i] - '0';
      val *= 10;
      val += temp;
    }
    else //error - just return 0
    {
      return (0);
    }
    i++;
  }

  //should never be here
  if (val > 999999999ull)
  {
    return (0);
  }

  return ((uint32_t)val); //just cast it and return
}

/**
 * To convert a string into a double - we will do the following
 * go through the array to find the first '.' or ','
 * everything before the '.' will be converted into a uint32_t
 * and everything after the '.' will be converted into a uint32_t
 * We will then just calculate the double value by first converting
 * them into double and then using floating point
 * division and addition. Note that, there is indeed some funny
 * behavior since the number before the '.' or ',' can indeed
 * be over uint32_t. In that case, it is treated as 0xFFFFFFFF
 * same applies to the fractional part.
 * -0.0 is returned on error
**/
double strToDouble(const char* str)
{
  size_t i = 0;
  size_t fracStart = 0; 

  int bWhole = 1; //yes whole part

  uint32_t whole = 0;
  uint32_t frac = 0;
  uint32_t val = 0;
  uint32_t temp = 0;


  if (str == NULL)
  {
    return (NAN.d); 
  }

  //loop through the string and separate the number by either . or ,
  while ( (str[i] != '\0') && (str[i] != '\n') )
  {
    if ( (str[i] == '.') || (str[i] == ',') )
    {
      //if we were processing whole then switch to processing frac
      if (bWhole)
      {
        bWhole = 0;
        fracStart = i + 1;
        whole = val; 
        temp = 0;
        val = 0;
      }
      else //if we are already processing frac then error
      {
        return (NAN.d);
      }
    }
    else //see if there are already too many digits
    {
      if ( bWhole && (i >= 10) )
      {
        return (NAN.d);
      }
      else if ( !bWhole && ((i - fracStart) >= 9) ) //we can have an error here if we change 9 to 10 - in that case we get whatever is in memory at that location
      {
        return (NAN.d);
      }
 
      if ( (str[i] >= '0') &&  (str[i] <= '9') )
      {
        temp = str[i] - '0';
        val *= 10;
        val += temp;
      }
      else //error - just return 0
      {
        return (NAN.d);
      }
    }

    i++;
  }   

  //if we are here then we have reached the end of the string
  if (bWhole)
  {
    whole = val;
  }
  else
  {
    frac = val;
  }

  //now that we have both sections lets calculate and return the double
  return ( (double)whole + ( (double)frac / POWERS_OF_TEN[i - fracStart] ) );
  
  //something very curious - CLANG defaults to SSE instructions if available and
  // then uses x87 as a fallback. On the other hand, if we use long double instead
  // of double then CLANG will use the x87 instructions instead. 
  // To keep things consistent, we might want to just use long double 
}

/**
 * calculates the x and y coordinates of a tennis ball launched from the origin
 *  with velocity components v0_x and v0_y. The coordinates are then placed
 *  into the array for further processing. We do this for as many seconds as
 *  will fit into a page.
 *
**/
void fillPage(float v0_x, float v0_y, Coords* aData, int* pCount, int countsPerSecond)
{
  if ( (aData == NULL) || (pCount == NULL) )
  {
    return;
  }

  float tempTime = 0.0;
  float tempy = 0.0;
  float g = 9.8;
#ifdef PATCHED
#else
  float startTime = (float)*pCount / (float)countsPerSecond; //this is the starting time in seconds
#endif
  int base = 0;
  int i = 0;
  int j = 0;


  //timeStart is in milliseconds - 
  //now calculate the x and y components for the number of counts
  // that will fit into a page
  for (i = 0; i < (PAGE_SIZE / sizeof(Coords) / countsPerSecond); i++)
  {
    tempTime = (float)(*pCount) / (float)countsPerSecond;

#ifdef PATCHED
    base = i * countsPerSecond;
#else
    base = ((int)(tempTime - startTime) * countsPerSecond);
#endif

    for (j = 0; j < countsPerSecond; j++)
    {
      tempTime = (float)*pCount / (float)countsPerSecond;

      aData[base + j].x = v0_x * tempTime; 

      tempy = v0_y * tempTime - (g * tempTime * tempTime / (float)2.0);
      if (tempy < (float)0.0)
      {
        tempy = (float)0.0;
      }

      aData[base + j].y = tempy;

      (*pCount)++;
    }
  }
}


int main(void)
{
  int i = 0;
  float vx;
  float vy;
  DoubleInt dTemp;
  int count = 0;
  char temp[100];
  char tempStr[24];
  ssize_t ret = 0;
  Coords* c = NULL;
  ret = allocate(PAGE_SIZE, 0, (void**)(&c));
  if (ret != 0)
  {
    return (-1);
  }

  do
  {
    printfstr(STDOUT, "Initial Velocity X: ");
    ret = readLine(STDIN, temp, 100);
    if (ret < 0)
    {
      return (-1);
    }

    dTemp.d = strToDouble(temp);
  } while (dTemp.u == NAN.u);

  vx = (float)dTemp.d;

  do
  {
    printfstr(STDOUT, "Initial Velocity Y: ");
    ret = readLine(STDIN, temp, 100);
    if (ret < 0)
    {
      return (-1);
    }
   
    dTemp.d = strToDouble(temp);
  } while (dTemp.u == NAN.u);

  vy = (float)dTemp.d;

  printfstr(STDOUT, "Initial Count: ");
  ret = readLine(STDIN, temp, 100);
  if (ret < 0)
  {
    return (-1);
  }
  count = strToUint32(temp);

  do
  {
    fillPage(vx, vy, c, &count, 10);
    ret = readLine(STDIN, temp, 100);
    if (ret < 0)
    {
      return (-1);
    }
    if (temp[0] == 'p')
    {
      for (i = 0; i < 510; i++)
      {
        tempStr[0] = 'x';
        tempStr[1] = '=';
        tempStr[2] = '\0';
        snprintfloat(tempStr+2, 24, c[i].x);
        printfstr(STDOUT, tempStr);
        printfstr(STDOUT, ", ");
        tempStr[0] = 'y';
        tempStr[1] = '=';
        tempStr[2] = '\0';
        snprintfloat(tempStr+2, 24, c[i].y);
        printfstr(STDOUT, tempStr);
        printfstr(STDOUT, "\n");
      }
    }
  } while ( (temp[0] == 'c') || (temp[0] == 'p') );
}

