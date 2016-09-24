#include <libpov.h>

/*
 * The following functions are available to POV authors to support 
 * POV type negotiations.
 */

/*
 * Negotiate a type 1 pov. Caller specifies an ip bit mask, a register bit mask
 * and a general purpose register number (see the list below).
 *
   0 - eax
   1 - ecx
   2 - edx
   3 - ebx
   4 - esp
   5 - ebp
   6 - esi
   7 - edi
 * 
 * Returns 0 on success. On success, the t1vals structure holds required IP  
 * and register values that must be found when the target CB crashes. At the
 * time of the crash the following must hold:
 *  (crash_eip & ipmask) == t1vals->ipval 
 *  (crash_REG & regmask) == t1vals->regval 
 */
int type1_negotiate(unsigned int ipmask, unsigned int regmask, unsigned int regnum, type1_vals *t1vals) {
   uint32_t povType = 1;
   if (transmit_all(3, &povType, sizeof(povType)) ||
       transmit_all(3, &ipmask, sizeof(ipmask)) ||
       transmit_all(3, &regmask, sizeof(regmask)) ||
       transmit_all(3, &regnum, sizeof(regnum))) {
      return -1;
   }
   if (length_read(3, (unsigned char *)t1vals, sizeof(type1_vals)) != sizeof(type1_vals)) {
      return -1;
   }
   return 0;
}

/*
 * Negotiate a type 2 pov. 
 * Returns 0 on success. On success, the t2vals structure holds the address
 * (t2vals->region_addr) and size of a memory region (t2vals->region_size)
 * from which the POV must leak a specific number of bytes (t2vals->read_size).
 */
int type2_negotiate(type2_vals *t2vals) {
   uint32_t povType = 2;
   if (transmit_all(3, &povType, sizeof(povType))) {
      return -1;
   }
   if (length_read(3, (unsigned char *)t2vals, sizeof(type2_vals)) != sizeof(type2_vals)) {
      return -1;
   }
   return 0;
}

/*
 * Submit the len bytes in the val buffer as the results of a type 2 POV
 * Returns 0 on success
 */
int type2_submit(const unsigned char *val, size_t len) {
   return transmit_all(3, val, len);
}

typedef struct _read_buffer {
   uint32_t iptr;
   uint32_t eptr;
   uint8_t buf[4096];
} read_buffer;

static read_buffer *ibufs[16];

int buffered_receive(int fd, void *buf, size_t count, size_t *rx_bytes) {
   if (fd > 15) {
      return receive(fd, buf, count, rx_bytes);
   }
   read_buffer *rb = ibufs[fd];
   if (rb == NULL) {
      rb = (read_buffer*)malloc(sizeof(read_buffer));
      rb->iptr = rb->eptr = 0;
      ibufs[fd] = rb;
   }

   if (rx_bytes != NULL) {
      *rx_bytes = 0;
   }

   int res = 0;
   while (1) {
      uint32_t avail = rb->eptr - rb->iptr;
      if (avail > 0) {
         if (avail >= count) {
            //we have enough data buffered to satisfy request
            memcpy(buf, rb->buf + rb->iptr, count);
            rb->iptr += count;
            if (rx_bytes != NULL) {
               *rx_bytes += count;
            }
            return 0;
         }
         else {
            //avail < len some data buffered but not enough
            memcpy(buf, rb->buf + rb->iptr, avail);
            buf = avail + (char*)buf;
            count -= avail;
            if (rx_bytes != NULL) {
               *rx_bytes += avail;
            }
         }
      }
      size_t rxb;
      rb->iptr = rb->eptr = 0;
      res = receive(fd, rb->buf, sizeof(rb->buf), &rxb);
      if (res != 0 || rxb == 0) {
         break;
      }
      rb->eptr = rxb;
   }
   return res;
}

void delay(unsigned int msec) {
   struct timeval timeout;
   timeout.tv_sec = msec / 1000;
   timeout.tv_usec = (msec % 1000) * 1000;
   fdwait(0, NULL, NULL, &timeout, NULL);
}

unsigned char *append_var(const char *var, unsigned char *buf, unsigned int *buflen) {
   unsigned char *newbuf = buf;
   size_t varlen;
   unsigned char *varbuf = getenv(var, &varlen);
   if (varbuf != NULL) {
      newbuf = (unsigned char*)realloc(buf, *buflen + varlen);
      memcpy(newbuf + *buflen, varbuf, varlen);
      free(varbuf);
      *buflen += varlen;
   }
   return newbuf;         
}

unsigned char *append_slice(const char *var, int begin, int end, unsigned char *buf, unsigned int *buflen) {
   unsigned char *newbuf = buf;
   size_t varlen;
   unsigned char *varbuf = getenv(var, &varlen);
   if (varbuf != NULL) {
      if (begin < 0) {
         begin += varlen;
         if (begin < 0) {
            begin = 0;
         }
      }
      if (end < 0) {
         end += varlen;
         if (end < 0) {
            end = 0;
         }
      }
      if (end > (int)varlen) {
         end = varlen;
      }
      if (begin < end) {
         int len = end - begin;
         newbuf = (unsigned char*)realloc(buf, *buflen + len);
         memcpy(newbuf + *buflen, varbuf + begin, len);
         free(varbuf);
         *buflen += len;
      }
   }
   return newbuf;         
}

unsigned char *append_buf(unsigned char *buf, unsigned int *buflen, unsigned char *sbuf, unsigned int sbuflen) {
   unsigned char *newbuf = buf;
   if (sbuf != NULL) {
      newbuf = (unsigned char*)realloc(buf, *buflen + sbuflen);
      memcpy(newbuf + *buflen, sbuf, sbuflen);
      *buflen += sbuflen;
   }
   return newbuf;     
}

int delimited_read(int fd, unsigned char **buf, unsigned int *size, unsigned char *delim, unsigned int delim_len) {
   unsigned int cap = 0;
   unsigned int idx = 0;
   unsigned char *dbuf = NULL;
   if (buf != NULL) {
      *buf = NULL;
   }
   if (size != NULL) {
      *size = 0;
   }
   int res;
   int haveDelim = 0;
   while (1) {
      unsigned char val;
      size_t rlen;
      res = buffered_receive(fd, &val, 1, &rlen);
      if (res != 0 || rlen == 0) {
         //error or eof but might have had some data
         break;
      }
      if (idx == cap) {
        unsigned char *nbuf = (unsigned char *)realloc(dbuf, cap ? cap * 2 : 128);
         if (nbuf != NULL) {
            dbuf = nbuf;
         }
         else {
            res = -1;
            break;
         }
         cap = cap ? cap * 2 : 128;
      }
      dbuf[idx++] = val;

      if (idx >= delim_len && memcmp(delim, dbuf + idx - delim_len, delim_len) == 0) {
         haveDelim = 1;
         break;
      }
   }
   if (buf != NULL) {
      *buf = dbuf;
   }
   else {
      free(dbuf);
   }
   if (size != NULL) {
      *size = idx;
   }
   return (int)idx;
}

int length_read(int fd, unsigned char *buf, unsigned int len) {
   unsigned int total = 0;
   while (total < len) {
      unsigned int need = len - total;
      size_t rlen;
      if (buf != NULL) {
         //read directly into caller buffer
         if (buffered_receive(fd, buf + total, need, &rlen) != 0 || rlen == 0) {
            //error or eof but might have had some data
            break;
         }
      }
      else {
         //caller supplied no buffer so just read len bytes
         //and discard
         unsigned char dbuf[512];
         if (need > sizeof(dbuf)) {
            need = sizeof(dbuf);
         }
         if (buffered_receive(fd, dbuf, need, &rlen) != 0 || rlen == 0) {
            //error or eof but might have had some data
            break;
         }
      }
      total += rlen;
   }
   return (int)total;
}

int transmit_all(int fd, const void *buf, const size_t size) {
    size_t sent = 0;
    size_t sent_now = 0;
    int ret;

    if (!buf)
        return 1;

    if (!size)
        return 2;

    while (sent < size) {
        ret = transmit(fd, sent + (char*)buf, size - sent, &sent_now);
        if (ret != 0) {
            return 3;
        }
        sent += sent_now;
    }

    return 0;
}

pcre *init_regex(const char *pattern) {
   pcre *regex;
   const char *error;
   int erroffset;
   regex = pcre_compile(pattern, PCRE_DOTALL, &error, &erroffset, NULL);
   return regex;
}

int regex_match(pcre *regex, unsigned int group, const unsigned char *buf, unsigned int len, match_result *res) {
   int *ovector = (int*)malloc((group + 1) * 3 * sizeof(int));
   int rc = pcre_exec(regex, NULL, (const char*)buf, len, 0, PCRE_ANCHORED, ovector, (group + 1) * 3);
   if (rc > 0) {
      int index  = group * 2;
      res->match_start = ovector[index];
      res->match_end = ovector[index + 1];
      res->len0 = ovector[1];
   }
   free(ovector);
   return rc;
}

void negotiate_type1(unsigned int ipmask, unsigned int regmask, unsigned int regnum) {
   uint32_t povType = 1;
   transmit_all(3, &povType, sizeof(povType));
   unsigned int type1vals[2];
   transmit_all(3, &ipmask, sizeof(ipmask));
   transmit_all(3, &regmask, sizeof(regmask));
   transmit_all(3, &regnum, sizeof(regnum));
   if (length_read(3, (unsigned char *)type1vals, sizeof(type1vals)) != sizeof(type1vals)) {
      _terminate(0);
   }
   putenv("TYPE1_IP", (unsigned char*)&type1vals[0], sizeof(unsigned int));
   putenv("TYPE1_REG", (unsigned char*)&type1vals[1], sizeof(unsigned int));
}

void negotiate_type2() {
   uint32_t povType = 2;
   transmit_all(3, &povType, sizeof(povType));
   unsigned int type2vals[3];
   if (length_read(3, (unsigned char *)type2vals, sizeof(type2vals)) != sizeof(type2vals)) {
      _terminate(0);
   }
   putenv("TYPE2_ADDR", (unsigned char*)&type2vals[0], sizeof(unsigned int));
   putenv("TYPE2_SIZE", (unsigned char*)&type2vals[1], sizeof(unsigned int));         
   putenv("TYPE2_LENGTH", (unsigned char*)&type2vals[2], sizeof(unsigned int));         
}

void submit_type2(const char *var) {
   size_t vlen;
   unsigned char *vbuf = NULL;
   if (var != NULL) {
      //try to find callers var
      vbuf = getenv(var, &vlen);
   }
   if (vbuf == NULL) {
      //if caller's var not specified or set fall back to TYPE2_VALUE
      vbuf = getenv("TYPE2_VALUE", &vlen);
   }
   if (vbuf != NULL) {
      //if a var was found, submit it
      transmit_all(3, vbuf, vlen);
      free(vbuf);
   }
}

size_t var_match(const unsigned char *readbuf, unsigned int buflen, const char *varName) {
   unsigned int result = 0;
   size_t var_len;
   unsigned char *var = getenv(varName, &var_len);
   if (var != NULL && var_len <= buflen) {
      if (memcmp(readbuf, var, var_len) == 0) {
         result = var_len;
      }
      else {
         //failed to match static text
      }
      free(var);
   }
   else {
      //var doesn't exist
   }
   return result;
}

unsigned int data_match(const unsigned char *readbuf, unsigned int buflen, const unsigned char *data, unsigned int datalen) {
   if (datalen <= buflen && memcmp(readbuf, data, datalen) == 0) {
      return datalen;
   }
   return 0;
}

unsigned int pcre_match(const unsigned char *readbuf, unsigned int buflen, const char *regex) {
   unsigned int result = 0;
   pcre *expr = init_regex(regex);
   match_result matchres;
   int rc = regex_match(expr, 0, readbuf, buflen, &matchres);
   if (rc > 0) {
      result = matchres.match_end - matchres.match_start;
   }
   else {
      //failed to match regex
   }
   pcre_free(expr);
   return result;
}

void assign_from_slice(const char *var, const void *readbuf, unsigned int buflen, int low, int high, int doMax) {
   //**** read assign to var from slice
   int dlen = (int)buflen;
   int abegin, aend;
   //adjust _start and _end to account for negative values and default max length
   if (low >= 0) {
      abegin = low;
   }
   else {
      abegin = buflen + low;
   }
   if (doMax) {
      aend = buflen;
   }
   else if (high >= 0) {
      aend = high;
   }
   else {
      aend = buflen + high;
   }
   if (aend < abegin || abegin < 0 || abegin > dlen || aend < 0 || aend > dlen) {
      //slice indicies are out of bounds, something went wrong
      _terminate(-1);
   }
   putenv(var, (const unsigned char *)readbuf + abegin, aend - abegin);
}

void assign_from_pcre(const char *var, const void *readbuf, unsigned int buflen, const char *regex, int group) {
   pcre *expr = init_regex(regex);
   match_result matchres;
   int rc = regex_match(expr, group, (const unsigned char *)readbuf, buflen, &matchres);
   if (rc > 0) {
      putenv(var, (const unsigned char *)readbuf + matchres.match_start, matchres.match_end - matchres.match_start);
   }
   else {
      putenv(var, (const unsigned char*)"", 0);
   }
   pcre_free(expr);
}

