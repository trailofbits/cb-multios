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
#ifndef LIBC_H
#define LIBC_H

#include <libcgc.h>
#include <stdint.h>

#define MAGICWORD "You didn't say the magic word."
#define MEMERR "Clever girl."
#define RNDERR "The essence of chaos."
#define SSEND(s,b) if(sendall(STDOUT,b,s)<0)  _terminate(3);
#define SSENDL(s,b) if(sendline(STDOUT,b,s)<0) _terminate(6);
#define SRECV(s,b) if(recvline(STDIN,b,s)<0){SSENDL(sizeof(MAGICWORD)-1,MAGICWORD); _terminate(2);}
#define RECV(s,b) if(recv(STDIN,b,s)<0){SSENDL(sizeof(MAGICWORD)-1,MAGICWORD); _terminate(4);}
#define ALLOC(x,a,s) if(allocate(s,x,a)!=0){ SSENDL(sizeof(MEMERR)-1,MEMERR); _terminate(9);}
#define DEALLOC(a,s) if(deallocate(a,s)!=0){ SSENDL(sizeof(MEMERR)-1,MEMERR); _terminate(18);}
#define RAND(b,s,r) if (random(b,s,r)){ SSENDL(sizeof(RNDERR)-1,RNDERR); _terminate(19);}
#define LOG(m) sendline(STDOUT,m,sizeof(m)-1)

void promptc(char *buf, uint16_t  size, char *prompt);
int int2str(char* str_buf, int buf_size, int i);
uint32_t str2uint(const char* str_buf);
int sendall(int fd, const char *buf, size_t size);
int sendline(int fd, const char *buf, size_t size);
int recvline(int fd, char *buf, size_t size);
int recv(int fd, char *buf, size_t size); 
size_t strcpy(char *s1, char *s2);
size_t strncpy(char *s1, char *s2, size_t n);
char * strcat(char *s1, char *s2);
size_t strlen(char *s);
int streq(char *s1, char *s2);
int startswith(char *s1, char *s2);
void * memset(void *dst, char c, size_t n); 
void * memcpy(void *dst, void *src, size_t n); 
char * b2hex(uint8_t b, char *h);
char * strchr(char *str, char c); 
void sleep(int s);

#endif

