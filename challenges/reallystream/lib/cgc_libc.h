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
#include "cgc_stdint.h"

#ifndef LIBC_H
#define LIBC_H

#define MAGICWORD "You didn't say the magic word."
#define MEMERR "Clever girl."
#define RNDERR "The essence of chaos."
#define SSEND(s,b) if(cgc_sendall(STDOUT,b,s)<0)  cgc__terminate(3);
#define SSENDL(s,b) if(cgc_sendline(STDOUT,b,s)<0) cgc__terminate(6);
#define SRECV(s,b) if(cgc_recvline(STDIN,b,s)<0){SSENDL(sizeof(MAGICWORD)-1,MAGICWORD); cgc__terminate(2);}
#define RECV(s,b) if(cgc_recv(STDIN,b,s)<0){SSENDL(sizeof(MAGICWORD)-1,MAGICWORD); cgc__terminate(4);}
#define ALLOC(x,a,s) if(cgc_allocate(s,x,a)!=0){ SSENDL(sizeof(MEMERR)-1,MEMERR); cgc__terminate(9);}
#define DEALLOC(a,s) if(cgc_deallocate(a,s)!=0){ SSENDL(sizeof(MEMERR)-1,MEMERR); cgc__terminate(18);}
#define RAND(b,s,r) if (cgc_random(b,s,r)){ SSENDL(sizeof(RNDERR)-1,RNDERR); cgc__terminate(19);}

void cgc_promptc(char *buf, uint16_t  size, char *prompt);
int cgc_int2str(char* str_buf, int buf_size, int i);
uint32_t cgc_str2uint(const char* str_buf);
int cgc_sendall(int fd, const char *buf, cgc_size_t size);
int cgc_sendline(int fd, const char *buf, cgc_size_t size);
int cgc_recvline(int fd, char *buf, cgc_size_t size);
int cgc_recv(int fd, char *buf, cgc_size_t size); 
cgc_size_t cgc_strcpy(char *s1, char *s2);
cgc_size_t cgc_strncpy(char *s1, char *s2, cgc_size_t n);
char * cgc_strcat(char *s1, char *s2);
cgc_size_t cgc_strlen(char *s);
int cgc_streq(char *s1, char *s2);
int cgc_startswith(char *s1, char *s2);
void * cgc_memset(void *dst, char c, cgc_size_t n); 
void * cgc_memcpy(void *dst, void *src, cgc_size_t n); 
char * cgc_b2hex(uint8_t b, char *h);
char * cgc_strchr(char *str, char c); 

#endif

