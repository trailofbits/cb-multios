/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <libpov.h>
#include "atox.h"
#include "service.h"
#include "bzero.h"
#include "atoi.h"

int harborMap[25][24] = {
   //     -10,  -9,  -8,  -7,  -6,  -5,  -4,  -3,  -2,  -1,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13
         {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,  13, 100, 100, 100, 100, 100}, // 10
         {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   7,   6,   7,   9, 100, 100, 100}, // 9
         {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   7,   5,   6,   7, 100, 100, 100, 100}, // 8
         {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   5,   5,   5,   6,   7,   8,   9, 100, 100}, // 7
         {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   4,   4,   5,   6,   7,   9,   9, 100, 100}, // 6       
         {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   3,   3,   4,   5,   6,   7,   8,   8, 100, 100}, // 5
         {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   2,   2,   2,   3,   4,   5,   6,   8,   9,   9, 100, 100}, // 4       
         {100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   1,   1,   1,   1,   2,   3,   4,   5,   6,   6,   7, 100, 100, 100}, // 3       
         {100, 100, 100, 100, 100, 100, 100, 100, 100,   1,   1,   1,   1,   1,   2,   3,   4,   5,   6,   7,   8,   9,   9, 100}, // 2
         {100, 100, 100, 100, 100, 100, 100, 100, 100,   1,   0,   0,   1,   1,   2,   3,   4,   5,   6,   8,   9,   9,  10, 100}, // 1
         {100, 100, 100, 100, 100, 100, 100, 100, 100,   0,   0,   0,   1,   1,   2,   3,   4,   5,   6,   7,   8,  13, 100, 100}, // 0
         {100, 100, 100, 100, 100, 100, 100, 100,  13,   0,   0,   1,   1,   2,   3,   4,   5,   6,   7,   8,   8, 100, 100, 100}, // -1
         {100, 100, 100, 100, 100, 100,   9,  12,  13,  13,  13,  13,   2,   3,   4,   5,   6,   7,   8,   9, 100, 100, 100, 100}, // -2
         {100, 100, 100, 100, 100,  10,  11,  12,  12,  12,  12,  13,   3,   4,   5,   6,   7,   8,  10,   9, 100, 100, 100, 100}, // -3
         {100, 100, 100, 100, 100,   9,  11,  11,  11,  11,  11,   4,   4,   5,   6,   7,   8,   9,  11, 100, 100, 100, 100, 100}, // -4
         {100, 100, 100,   9, 100,   9,   9,  10,  10,   9,   5,   5,   5,   6,   7,   8,  10,  10, 100, 100, 100, 100, 100, 100}, // -5
           {100, 100, 100,  10,  10,   9,   8,   7,   6,   6,   6,   6,   6,   7,   8,  10,   9,  11, 100, 100, 100, 100, 100, 100}, // -6
            {100, 100,  11,  11,  10,   9,   8,   7,   7,   7,   7,   7,   7,   8,   9,   9, 100,  12, 100, 100, 100, 100, 100, 100}, // -7
         {100,  12,  12,  11,  10,   9,   8,   8,   8,   8,   8,   8,   8,   9,   9, 100, 100, 100, 100, 100, 100, 100, 100, 100}, // -8
          {100,  13,  12,  11,  10,   9,   9,   9,   9,   9,   9,   9,   9,   8,  10, 100, 100, 100, 100, 100, 100, 100, 100, 100}, // -9
         {100, 100,  12, 100,  10,  10,  10,  10,  10,  11,  10, 100,  12,  11, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, // -10
         {100, 100, 100,  11,  11,  11,   9,  12,  11,  12, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, // -11
         {100, 100, 100,  13,  11,  10,  12,  10,  11, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, // -12
         {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, // -13
         {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}  // -14

        };

int cityMap[13][10] = {
        // -2,  -1,   0, 1,   2,   3,   4,   5,   6,   7
         {100, 100, 100, 8,  11, 100, 100, 100, 100, 100}, // 7
         {100, 100, 100, 5,   8, 100, 100, 100, 100, 100}, // 6
         {100, 100,   3, 4,   7,  10, 100, 100, 100, 100}, // 5
         {100, 100,   2, 3,   4,   7, 100, 100, 100, 100}, // 4
         {100,   1,   1, 1,   3,   6,   9, 100, 100, 100}, // 3
         {100,   1,   1, 1,   2,   3,   6, 100, 100, 100}, // 2
         {100,   0,   0, 0,   1,   1,   5,   8, 100, 100}, // 1
         {100,   0,   0, 0,   1,   1,   2,   3, 100, 100}, // 0
         {  9,   0,   0, 0,   1,   1,   3,   4,   5,   8}, // -1
         {100,   7,   4, 3,   2,   3,   4,   7,   8,  11}, // -2
         {100,  10,   7, 4,   3,   6,   7,  10, 100, 100}, // -3
         {100, 100,  8, 5,   6,   9,  100, 100, 100, 100}, // -4
         {100, 100, 11, 8, 100, 100,  100, 100, 100, 100}  // -5
        };

/**
 * Move criminal to most beneficial position
 * @param criminal Position of criminal
 */
void moveCriminalInBoat(Position* criminal) {
   int value=0;
   int bestX;
   int bestY;
   unsigned int tmp;
   int x, y;

   bestX = criminal->x;
   bestY = criminal->y;

   x = criminal->x;
   y = criminal->y;
   if(x > -11 && x < 14 && y > -14 && y < 11) {
      tmp = harborMap[23 - y - 13][x + 10];
      if(tmp > value) {
         value = tmp;
         bestX = x;
         bestY = y;
      }
   }

   x = criminal->x + 1;
   y = criminal->y;
   if(x > -11 && x < 14 && y > -14 && y < 11) {
      tmp = harborMap[23 - y - 13][x + 10];
      if(tmp > value) {
         value = tmp;
         bestX = x;
         bestY = y;
      }
   }

   x = criminal->x+1;
   y = criminal->y;
   if(x > -11 && x < 14 && y > -14 && y < 11) {
      tmp = harborMap[23 - y - 13][x + 10];
      if(tmp > value) {
         value = tmp;
         bestX = x;
         bestY = y;
      }
   }

   x = criminal->x;
   y = criminal->y+1;
   if(x > -11 && x < 14 && y > -14 && y < 11) {
      tmp = harborMap[23 - y - 13][x + 10];
      if(tmp > value) {
         value = tmp;
         bestX = x;
         bestY = y;
      }
   }

   x = criminal->x-1;
   y = criminal->y;
   if(x > -11 && x < 14 && y > -14 && y < 11) {
      tmp = harborMap[23 - y - 13][x + 10];
      if(tmp > value) {
         value = tmp;
         bestX = x;
         bestY = y;
      }
   }

   x = criminal->x;
   y = criminal->y-1;
   if(x > -11 && x < 14 && y > -14 && y < 11) {
      tmp = harborMap[23 - y - 13][x + 10];
      if(tmp > value) {
         value = tmp;
         bestX = x;
         bestY = y;
      }
   }

   x = criminal->x+1;
   y = criminal->y+1;
   if(x > -11 && x < 14 && y > -14 && y < 11) {
      tmp = harborMap[23 - y - 13][x + 10];
      if(tmp > value) {
         value = tmp;
         bestX = x;
         bestY = y;
      }
   }

   x = criminal->x-1;
   y = criminal->y-1;
   if(x > -11 && x < 14 && y > -14 && y < 11) {
      tmp = harborMap[23 - y - 13][x + 10];
      if(tmp > value) {
         value = tmp;
         bestX = x;
         bestY = y;
      }
   }

   criminal->x = bestX;
   criminal->y = bestY;

#ifdef DEBUG
   char send_buffer[1024];
   bzero(send_buffer, 1024);
   sprintf(send_buffer, "Criminal moves. Criminal at (!I, !I)\n", criminal->x, criminal->y);
   if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
      _terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move criminal in car to most beneficial position
 * @param criminal Position of criminal
 */
void moveCriminalInCar(Position* criminal) {
   int value=0;
   int bestX;
   int bestY;
   unsigned int tmp;
   int x,y;

   bestX = criminal->x;
   bestY = criminal->y;

   x = criminal->x;
   y = criminal->y;
   if(x > -2 && x < 8 && y > -6 && y < 8) {
      tmp = cityMap[12 - y - 5][x + 2];
      if(tmp > value) {
         value = tmp;
         bestX = x;
         bestY = y;
      }
   }

   x = criminal->x+1;
   y = criminal->y;
   if(x > -2 && x < 8 && y > -6 && y < 8) {
      tmp = cityMap[12 - y - 5][x + 2];
      if(tmp > value) {
         value = tmp;
         bestX = x;
         bestY = y;
      }
   }

   x = criminal->x;
   y = criminal->y+1;
   if(x > -2 && x < 8 && y > -6 && y < 8) {
      tmp = cityMap[12 - y - 5][x + 2];
      if(tmp > value) {
         value = tmp;
         bestX = x;
         bestY = y;
      }
   }

   x = criminal->x-1;
   y = criminal->y;
   if(x > -2 && x < 8 && y > -6 && y < 8) {
      tmp = cityMap[12 - y - 5][x + 2];
      if(tmp > value) {
         value = tmp;
         bestX = x;
         bestY = y;
      }
   }

   x = criminal->x;
   y = criminal->y-1;
   if(x > -2 && x < 8 && y > -6 && y < 8) {
      tmp = cityMap[12 - y - 5][x + 2];
      if(tmp > value) {
         value = tmp;
         bestX = x;
         bestY = y;
      }
   }

   criminal->x = bestX;
   criminal->y = bestY;

#ifdef DEBUG
   char send_buffer[1024];
   bzero(send_buffer, 1024);
   sprintf(send_buffer, "Criminal moves. Criminal at (!I, !I)\n", criminal->x, criminal->y);
   if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
      _terminate(TRANSMIT_ERROR);
#endif

}

/**
 * Move left in boat
 * @param criminal Position of criminal
 */
void moveLeftInBoat(Position* criminal) {
   int newX, newY;
   newX = criminal->y;
   newY = criminal->y - criminal->x;
   criminal->x = newX - 2;
   criminal->y = newY - 2;

#ifdef DEBUG
   char send_buffer[1024];
   bzero(send_buffer, 1024);
   sprintf(send_buffer, "Move Left. Criminal at (!I, !I)\n", criminal->x, criminal->y);
   if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
      _terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move forward in boat
 * @param criminal Position of criminal
 */
void moveForwardInBoat(Position* criminal) {
   criminal->x = criminal->x - 2;
   criminal->y = criminal->y - 2;

#ifdef DEBUG
   char send_buffer[1024];
   bzero(send_buffer, 1024);
   sprintf(send_buffer, "Move Forward. Criminal at (!I, !I)\n", criminal->x, criminal->y);
   if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
      _terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move right in boat
 * @param criminal Position of criminal
 */
void moveRightInBoat(Position* criminal) {
   int newX, newY;
   newX = criminal->x - criminal->y;
   newY = criminal->x;
   criminal->x = newX - 2;
   criminal->y = newY - 2;


#ifdef DEBUG
   char send_buffer[1024];
   bzero(send_buffer, 1024);
   sprintf(send_buffer, "Move Right. Criminal at (!I, !I)\n", criminal->x, criminal->y);
   if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
      _terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move forward in car
 * @param criminal Position of criminal
 */
void moveForwardInCar(Position* criminal) {
   criminal->y = criminal->y - 2;

#ifdef DEBUG
   char send_buffer[1024];
   bzero(send_buffer, 1024);
   sprintf(send_buffer, "Move Forward. Criminal at (!I, !I)\n", criminal->x, criminal->y);
   if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
      _terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move right in car
 * @param criminal Position of criminal
 */
void moveRightInCar(Position* criminal) {
   int newX, newY;
   newX = criminal->y * -1;
   newY = criminal->x - 2;
   criminal->x = newX;
   criminal->y = newY;

#ifdef DEBUG
   char send_buffer[1024];
   bzero(send_buffer, 1024);
   sprintf(send_buffer, "Move Right. Criminal at (!I, !I)\n", criminal->x, criminal->y);
   if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
      _terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Calculate the value of the best move the criminal can make 
 * from the position (x, y)
 * 
 * @param  map Map of the harbor
 * @param  x   X-coordinate of the criminal
 * @param  y   Y-coordinate of the criminal
 * @return     The value at the best move for the criminal
 */
unsigned int bestCriminalMove(int x, int y) {
   int tmp;
   unsigned int value = 0;

   tmp = harborMap[23 - y - 13][x + 10 -1];
   if(tmp > value)
      value = tmp;

   tmp = harborMap[23 - y - 13][x + 10 + 1];
   if(tmp > value)
      value = tmp;

   tmp = harborMap[23 - y - 13 + 1][x + 10];
   if(tmp > value)
      value = tmp;

   tmp = harborMap[23 - y - 13 - 1][x + 10];
   if(tmp > value)
      value = tmp;

   tmp = harborMap[23 - y - 13 + 1][x + 10 - 1];
   if(tmp > value)
      value = tmp;

   tmp = harborMap[23 - y - 13 - 1][x + 10 + 1];
   if(tmp > value)
      value = tmp;

   return value;
}

/**
 * Move boat based on given strategy
 * @param criminal Current position of criminal
 * @param map      Map of harbor
 */
char makeMoveInBoat(Position* criminal) {
   unsigned int value = -1;
   unsigned int tmp;
   char move;
   int x, y;

   x = criminal->y - 2;
   y = criminal->y - criminal->x - 2;
   if(x > -11 && x < 14 && y > -14 && y < 11) {
      tmp = bestCriminalMove(x, y);
      if(tmp < value) {
         value = tmp;
         move = 'L';
      }
   }

   x = criminal->x - 2;
   y = criminal->y - 2;
   if(x > -11 && x < 14 && y > -14 && y < 11) {
      tmp = bestCriminalMove(x, y);
      if(tmp < value) {
         value = tmp;
         move = 'F';
      }
   }

   x = criminal->x - criminal->y - 2;
   y = criminal->x - 2;
   if(x > -11 && x < 14 && y > -14 && y < 11) {
      tmp = bestCriminalMove(x, y);
      if(tmp < value) {
         value = tmp;
         move = 'R';
      }
   }

   if(move == 'L') {
      moveLeftInBoat(criminal);
      return 'L';
   }
   else if(move == 'F') {
      moveForwardInBoat(criminal);
      return 'F';
   }
   else {
      moveRightInBoat(criminal);
      return 'R';
   }

   return 'R';

#ifdef DEBUG
   char send_buffer[1024];
   bzero(send_buffer, 1024);
   sprintf(send_buffer, "Value: !U\n", value);
   if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
      _terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move car based on given strategy
 * @param  criminal Position of criminal
 * @return          Letter of corresponding move
 */
char makeMoveInCar(Position* criminal) {
      if(criminal->y < 1 || criminal->x < -1) {
          moveRightInCar(criminal);
          return 'R';        
      }
      else {
         moveForwardInCar(criminal);     
         return 'F';    
      }

      return 'F';
}

/**
 * Send string containing list of moves to service
 * @param move_str String containing the list of moves
 * @param length   length of the move_str
 */
void sendMoveString(unsigned char* move_str, unsigned int length) {
   unsigned char *write = NULL;
   unsigned int write_len = 0;

   write = append_buf(write, &write_len, move_str, length);
   if(length > 0) {
      transmit_all(1, write, write_len);
   }
   free(write);
}

/**
 * Read the caught message from service
 */
void readCaughtMessage() {
      unsigned char *read_00201;
      unsigned int read_00201_len;
      unsigned int read_00201_ptr = 0;
      //**** delimited read
      static unsigned char read_00201_delim[] = 
         "\x0a";
      read_00201 = NULL;
      read_00201_len = 0;
      int read_00201_res = delimited_read(0, &read_00201, &read_00201_len, read_00201_delim, 1);
      if (read_00201_res) {} //silence unused variable warning
      /* read match pcre:
Criminal caught in ([0-9]*) moves

*/
      static char read_00201_00000_regex[] = 
         "\x43\x72\x69\x6d\x69\x6e\x61\x6c\x20\x63\x61\x75\x67\x68\x74\x20"
         "\x69\x6e\x20\x28\x5b\x30\x2d\x39\x5d\x2a\x29\x20\x6d\x6f\x76\x65"
         "\x73\x0a";
      static match_result read_00201_00000_match;
      pcre *read_00201_00000_pcre = init_regex(read_00201_00000_regex);
      if (read_00201_00000_pcre != NULL) {
         int rc = regex_match(read_00201_00000_pcre, 0, read_00201 + read_00201_ptr, read_00201_len - read_00201_ptr, &read_00201_00000_match);
         if (rc > 0) {
            read_00201_ptr += read_00201_00000_match.match_end - read_00201_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00201_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      free(read_00201);
      if (read_00201_ptr) {}  //silence unused variable warning if any
   
}

/**
 * Read the X-coordinate from the criminal's position sent by service
 */
void readX() {
      unsigned char *read_00200;
      unsigned int read_00200_len;
      unsigned int read_00200_ptr = 0;
      //**** delimited read
      static unsigned char read_00200_delim[] = 
         "\x2c";
      read_00200 = NULL;
      read_00200_len = 0;
      int read_00200_res = delimited_read(0, &read_00200, &read_00200_len, read_00200_delim, 1);
      if (read_00200_res) {} //silence unused variable warning
      //**** read assign to var "criminalX" from pcre: Criminal at \((-?\d+),
      static char read_00200_regex[] = 
         "\x43\x72\x69\x6d\x69\x6e\x61\x6c\x20\x61\x74\x20\x5c\x28\x28\x2d"
         "\x3f\x5c\x64\x2b\x29\x2c";
      assign_from_pcre("criminalX", read_00200, read_00200_len - read_00200_ptr, read_00200_regex, 1);
      free(read_00200);
      if (read_00200_ptr) {}  //silence unused variable warning if any
             
}

/**
 * Read the Y-coordinate from the criminal's position sent by service
 */
void readY() {
      unsigned char *read_00201;
      unsigned int read_00201_len;
      unsigned int read_00201_ptr = 0;
      //**** delimited read
      static unsigned char read_00201_delim[] = 
         "\x0a";
      read_00201 = NULL;
      read_00201_len = 0;
      int read_00201_res = delimited_read(0, &read_00201, &read_00201_len, read_00201_delim, 1);
      if (read_00201_res) {} //silence unused variable warning
      //**** read assign to var "criminalY" from pcre:  (-?\d+)\)\n
      static char read_00201_regex[] = 
         "\x20\x28\x2d\x3f\x5c\x64\x2b\x29\x5c\x29\x5c\x6e";
      assign_from_pcre("criminalY", read_00201, read_00201_len - read_00201_ptr, read_00201_regex, 1);
      free(read_00201);
      if (read_00201_ptr) {}  //silence unused variable warning if any
           
}

/**
 * Get the criminal's position from message sent by service
 * @param criminal Position of the criminal
 */
void getCriminalPosition(Position* criminal) {
   unsigned char *criminalX_string = NULL;
   unsigned int criminalX_string_len = 0;
   unsigned char *criminalY_string = NULL;
   unsigned int criminalY_string_len = 0;
   int x, y;

   readX();
   readY();

   criminalX_string = append_var("criminalX", criminalX_string, &criminalX_string_len);
   criminalY_string = append_var("criminalY", criminalY_string, &criminalY_string_len);

   criminalX_string[criminalX_string_len] = '\0';
   criminalY_string[criminalY_string_len] = '\0';

   criminal->x = atoi((char*)criminalX_string);
   criminal->y = atoi((char*)criminalY_string);

   free(criminalX_string);
   free(criminalY_string);
}

/**
 * Create and send a move string the catches the criminal in a car at position
 * sent by service
 */
void catchCriminalInCar() {
   Position criminal;
   unsigned char move_str[2048];
   unsigned int moves=0;
   unsigned int length=0;

   for(int i=0; i<100; i++) {
      bzero((char*)move_str, 2048);
      moves = 0;
      getCriminalPosition(&criminal);
      move_str[moves*2] = makeMoveInCar(&criminal);
      move_str[moves*2+1] = '#';
      moves++;
      while (!(criminal.x > -2 && criminal.x < 2 && criminal.y > -2 && criminal.y < 2)) {
         moveCriminalInCar(&criminal);
         move_str[moves*2] = makeMoveInCar(&criminal);
         move_str[moves*2+1] = '#';
         moves++;
      }
      length = strlen((char*)move_str);
      sendMoveString(move_str, length);
      readCaughtMessage();
   }
}

/**
 * Create and send a move string to the service that 
 * catches the criminal in a boat in at least 100,000 moves
 */
void catchCriminalInBoat() {
   Position criminal;
   unsigned char move_str[100000*2 + 100];
   unsigned int moves=0;
   unsigned int length=0;

   bzero((char*)move_str, 100000*2 + 100);
   moves = 0;
   getCriminalPosition(&criminal);
   if(harborMap[23 - criminal.y - 13][criminal.x + 10] < 3) {
      moveLeftInBoat(&criminal);
      move_str[moves*2] = 'L';
   } else      
      move_str[moves*2] = makeMoveInBoat(&criminal);
   move_str[moves*2+1] = '#';
   moves++;
   while(moves < 100000) {
      while (!(harborMap[23 - criminal.y - 13][criminal.x + 10] == 1)) {
         moveCriminalInBoat(&criminal);
         move_str[moves*2] = makeMoveInBoat(&criminal);
         move_str[moves*2+1] = '#';
         moves++;
      }
      moveCriminalInBoat(&criminal);
      moveLeftInBoat(&criminal);
      move_str[moves*2] = 'L';
      move_str[moves*2+1] = '#';
      moves++;      
   }
   while (!(harborMap[23 - criminal.y - 13][criminal.x + 10] == 0)) {
      moveCriminalInBoat(&criminal);
      move_str[moves*2] = makeMoveInBoat(&criminal);
      move_str[moves*2+1] = '#';
      moves++;  
   }
   length = strlen((char*)move_str);
   sendMoveString(move_str, length);
   readCaughtMessage();
}

/**
 * Read the flag string sent by the service
 */
void readFlag() {
   unsigned char *read_00202;
   unsigned int read_00202_len;
   unsigned int read_00202_ptr = 0;
   //**** length read
   read_00202_len = 16;
   read_00202 = (unsigned char*)malloc(read_00202_len);
   int read_00202_res = length_read(0, read_00202, read_00202_len);
   if (read_00202_res) {} //silence unused variable warning
   //**** read assign to var "flag" from pcre: (.*)
   static char read_00202_regex[] = 
      "\x28\x2e\x2a\x29";
   assign_from_pcre("flag", read_00202, read_00202_len - read_00202_ptr, read_00202_regex, 1);
   free(read_00202);
   if (read_00202_ptr) {}  //silence unused variable warning if any

}

int main(void) {
   type2_vals t2vals;
   size_t bytes;

   if(type2_negotiate(&t2vals))
      _terminate(1);

   catchCriminalInCar();
   catchCriminalInBoat();
   readFlag();

   unsigned char *flag_string = NULL;
   unsigned int flag_string_len = 0;
   flag_string = append_var("flag", flag_string, &flag_string_len);

   unsigned char flag[16];
   // parse response
   for (unsigned int i = 0; i < 16; i++) {
      flag[i] = atox((char *)&(flag_string[i*4]));
   }
   //*** submitting type 2 POV results
   if(type2_submit(flag, 16))
      _terminate(2);
}
