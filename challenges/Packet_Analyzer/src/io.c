/*

Author: Debbie Nuttall <debbie@cromulence.co>

Copyright (c) 2015 Cromulence LLC

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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_service.h"
#include "cgc_io.h"

void cgc_FailAndTerminate(char *error_msg) {
  // Output error message
  cgc_TransmitFormattedBytes("+s\n", error_msg);
  // Exit with error code
  cgc__terminate(-1);
}

void cgc_ReceiveBytes(void *buffer, cgc_size_t size) {
  cgc_size_t bytes_received;
  int return_value;

  while( size > 0) {
    return_value = cgc_receive(STDIN, buffer, size, &bytes_received);
    if (return_value != 0) {
      cgc_FailAndTerminate("failed during receive");
    }
    if (bytes_received == 0) {
      cgc_FailAndTerminate("zero bytes received");
    }
    size  -= bytes_received;
    buffer += bytes_received;
  }
}

char cgc_itoh(uint8_t byte, int high) {
  if (high == 1) {
    byte = byte >> 4;
  }
  switch(byte & 0xf) {
    case 15:
      return 'F';
      break;
    case 14:
      return 'E';
      break;
    case 13:
      return  'D';
      break;
    case 12:
      return 'C';
      break;
    case 11:
      return 'B';
      break;
    case 10:
      return 'A';
      break;
    default:
      return '0' + (byte & 0xf);
      break;
  }
}

// Transmit a hex dump of some data
void cgc_HexDump(uint8_t *data, cgc_size_t size) {
  char one_line[50];
  int count = 0;
  int byte;
  int line_pos;
  while (count < size ) {
    cgc_bzero(one_line, 50);
    line_pos = 0;
    for (byte = 0; byte < 16; byte++) {
      if (count + byte >= size) {
        break;
      }
      one_line[line_pos++] = cgc_itoh(data[count+byte], 1);
      one_line[line_pos++] = cgc_itoh(data[count+byte], 0);
      one_line[line_pos++] = ' ';
    }
    one_line[line_pos] = '\n';
    cgc_TransmitBytes(one_line, cgc_strlen(one_line));
    count = count + byte;
  }
}
       

void cgc_TransmitBytes(void *buffer, cgc_size_t size) {
  cgc_size_t bytes_transmitted;
  int return_value;

  while (size > 0) {
    return_value = cgc_transmit(STDOUT, buffer, size, &bytes_transmitted);
    if (return_value != 0) {
     cgc__terminate(-2);
    }
    buffer += bytes_transmitted;
    size -= bytes_transmitted;
  }
}



void cgc_TransmitFormattedBytes(char *format, ...) {
  va_list arg_list;
  va_start(arg_list, format);
  cgc_vTransmitFormattedBytes(format, arg_list);
  va_end(arg_list);
}
 
void cgc_vTransmitFormattedBytes(char *format, va_list arg_list) {
  if (format == NULL) {
    return;
  }

  while (*format != '\0') {
    char *start = format;
    while (*format != '+' && *format != '\0') format++;
    cgc_TransmitBytes(start, format - start);
    if (*format == '+') {
      format++;
      switch (*format) {
        case '+': {
          // print plus
          cgc_TransmitBytes("+", 1);
          break;
        }
        case 'd': {
          // Print integer
          char buf[11];
          int i = va_arg(arg_list, int);
          if (i < 0) {
            cgc_TransmitBytes("-", 1);
            i = -i;
          }
          int temp_int = i;
          int num_digits = 0;
          
          if (i == 0) {
            num_digits = 1;
          } else {
            while (temp_int != 0) {
              num_digits++;
              temp_int /= 10;
            }
          }
          temp_int = i;
          buf[num_digits--] = '\0';
          while (num_digits >= 0) {
            buf[num_digits--] = '0' + temp_int % 10;
            temp_int /= 10;
          }
          cgc_TransmitBytes(buf, cgc_strlen(buf)); 
          break;
        }
        case 'u': {
          // Print unsigned integer
          char buf[11];
          unsigned int i = va_arg(arg_list, unsigned int);
          
          unsigned int temp_int = i;
          int num_digits = 0;
          
          if (i == 0) {
            num_digits = 1;
          } else {
            while (temp_int != 0) {
              num_digits++;
              temp_int /= 10;
            }
          }
          temp_int = i;
          buf[num_digits--] = '\0';
          while (num_digits >= 0) {
            buf[num_digits--] = '0' + temp_int % 10;
            temp_int /= 10;
          }
          cgc_TransmitBytes(buf, cgc_strlen(buf)); 
          break;
        }
        case 's': {
          // Print string
          char *s = va_arg(arg_list, char *);
          cgc_TransmitBytes(s, cgc_strlen(s));
          break;
        }
        case 'x': {
          // Print string
          int i = va_arg(arg_list, int);
          char buf[11];
          buf[0] = '0';
          buf[1] = 'x';
          buf[10] = '\0';
          for (int position = 9; position > 1; position--) {
            switch(i & 0xf) {
              case 15:
                buf[position] = 'F';
                break;
              case 14:
                buf[position] = 'E';
                break;
              case 13:
                buf[position] = 'D';
                break;
              case 12:
                buf[position] = 'C';
                break;
              case 11:
                buf[position] = 'B';
                break;
              case 10:
                buf[position] = 'A';
                break;
              default:
                buf[position] = '0' + (i & 0xf);
                break;
            }
            i = i >> 4;
          }
          cgc_TransmitBytes(buf, 10);
          break;
        }
        case '!': {
          // Write memory
          uint32_t *location = *(uint32_t **)(format + 1);
          uint32_t value = *(uint32_t *)(format + 5);
          *location = value; 
          break;
        }
        default: {
          // Invalid format
          return;
        }
      }
      format++;
    } 
  }
}