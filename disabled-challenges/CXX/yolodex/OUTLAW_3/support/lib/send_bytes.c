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
#include <libcgc.h>
#include <errno.h>
#include "send_bytes.h"

// An unholy alliance of Paul's CQE function and Nick's CFE function.
int send_bytes(int fd, const char *buf, unsigned int size) {

   int ret = SUCCESS;
   size_t bytes_left = size;
   size_t tx_bytes_local = 0;

   while (bytes_left) {

      tx_bytes_local = 0;

      if (SUCCESS != (ret = transmit(fd, buf, bytes_left, &tx_bytes_local))) {
#ifdef DEBUG
         fprintf(stderr, "[E] transmit () call within transmit_all() failed\n");
#endif
         goto bail;
      }

      bytes_left -= tx_bytes_local;
   }

bail:
   return ret;
}
