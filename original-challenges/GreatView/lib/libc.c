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
#include "libc.h"


void (*freep)(void *);
void *(*mallocp)(size_t);

bool heapinit_done = false;

heap_chunk_t freedc[3] = {0};

heap_chunk_t allocatedc[3] = {0};

heap_chunk_t *freed[3] = {0};

heap_chunk_t *allocated[3] = {0};

uint8_t *lastpage[3] = {0};
uint32_t curleft[3] = {0};

uint32_t __cookie[3] = {0};
uint32_t __hcookie[3] = {0};
heaptype __htype = 0;

static char *strtok_last = NULL;

void promptc(char *buf, uint16_t  size, char *prompt) {

    SSEND(strlen(prompt), prompt);

    SRECV((uint32_t)size, buf);
}

int sendall(int fd, const char *buf, size_t size) {
    size_t sent = 0;
    size_t total = 0;

    if (!buf)
        return -1;

    if (!size)
        return 0;

    while (size) {
        if (transmit(fd, buf, size, &sent)) {
            return -1;
        }

        buf += sent;
        total += sent;
        size -= sent;
    }

    return total;
}

int sendline(int fd, const char *buf, size_t size) {
    int ret;
    ret = sendall(fd, buf, size);
    if (ret < 0) {
        return ret;
    } else {
        if (transmit(fd, "\n", 1, &size))
            return -1;
        else
            return ++ret;
    }
}

int recv(int fd, char *buf, size_t size) {
    size_t bytes_read = 0;
    size_t total_read = 0;

    if(!size)
        return 0;

    if (!buf)
        return -1;

    while (size) {
        if (receive(fd, buf, size, &bytes_read))
            return -1;
        
        total_read += bytes_read;
        size -= bytes_read;
        buf += bytes_read;
    }

    return total_read;

}


int recvline(int fd, char *buf, size_t size) {
    return recvuntil(fd, buf, size, '\n');
}

int recvuntil(int fd, char *buf, size_t size, char term) {
    size_t bytes_read = 0;
    size_t total_read = 0;

    if(!size)
        return 0;

    if (!buf)
        return -1;

    while (size) {
        if (receive(fd, buf, 1, &bytes_read))
            return -1;

        total_read+=bytes_read;
        size-=bytes_read;
        
        if(bytes_read && *buf == term)
            break;
        buf += bytes_read;
    }

    if (*(buf) != term)
        return -2;
    else
        *(buf) = '\0';

    return total_read;
}

//non-standard convention, returns num bytes copied instead of s1
size_t strcpy(char *s1, char *s2) {
    char *tmp = s1;
    while (*s2) {
        *tmp = *s2;
        tmp++;
        s2++;
    }
    *(tmp++)='\0';
    return tmp-s1-1;
}

//non-standard convention, returns num bytes copied instead of s1
size_t strncpy(char *s1, char *s2, size_t n) {
    char *tmp = s1;
    while ((tmp-s1 < n) && *s2) {
        *tmp = *s2;
        tmp++;
        s2++;
    }
    *(tmp++)='\0';
    return tmp-s1-1;
}

char * strcat(char *s1, char *s2) {
    char *tmp = s1;
    while (*tmp) tmp++;
    strcpy(tmp,s2);
    return s1;
}

size_t strlen(char *s) {
    char *tmp = s;
    while (*tmp) tmp++;
    return (size_t)(tmp-s);
}

int streq(char *s1, char *s2) {
    while (*s1 && *s2){
        if (*s1 != *s2)
            return 0;
	    s1++;
	    s2++;
    }
    return (*s1 == '\0') && (*s2 == '\0');
}

int strncmp(char *s1, char *s2, size_t n) {
    while (*s1 && *s2 && n--){
        if (*s1 != *s2)
            return 1;
	    s1++;
	    s2++;
    }
    return !((*s1 == '\0') && (*s2 == '\0'));
}

int startswith(char *s1, char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2)
            return 0;
	    s1++;
	    s2++;
    }
    return *s2 == '\0';
}

int uint2str(char* str_buf, int buf_size, uint32_t i) {

    int idx = 0;
    uint32_t tmp = 0;
    int digit = 0;

    // at least fits 1 digit and '\0'
    if (buf_size < 2) {
        return -1;
    }

    tmp = i;

    // increment index in str_buf to where rightmost digit goes
    do {
        idx++;
        tmp = tmp/10;
    } while (tmp > 0);

    // see if this number will fit in the buffer
    if (idx >= buf_size)
        return -1;

    // insert '\0'
    str_buf[idx--] = '\0';

    // move left through string, writing digits along the way
    do {
        digit = i % 10;
        str_buf[idx--] = '0' + digit;
        i /= 10;
    } while (i > 0);

    return 0;
}

int int2str(char* str_buf, int buf_size, int i) {

    int idx = 0;
    int tmp = 0;
    int digit = 0;

    // at least fits 1 digit and '\0'
    if (buf_size < 2) {
        return -1;
    }

    if (i < 0) {
        if (buf_size < 3)
            return -1;
        str_buf[idx++] = '-';
    } else {
        i *= -1; // make i negative
    }

    // i is always 0 or negative at this point.
    tmp = i;

    // increment index in str_buf to where rightmost digit goes
    do {
        idx++;
        tmp = tmp/10;
    } while (tmp < 0);

    // see if this number will fit in the buffer
    if (idx >= buf_size)
        return -1;

    // insert '\0'
    str_buf[idx--] = '\0';

    // move left through string, writing digits along the way
    do {
        digit = -1 * (i % 10);
        str_buf[idx--] = '0' + digit;
        i /= 10;
    } while (i < 0);

    return 0;
}

uint32_t str2uint(const char* str_buf) {
    int result = 0;
    int max_chars = 10; // max number of chars read from str_buf
    int i = 0;

    if (str_buf == NULL)
        return result;

    for (; i < max_chars; i++) {
        if ( str_buf[i] >= '0' && str_buf[i] <= '9') {
            result *= 10;
            result += str_buf[i] - '0';

        } else {
            break;
        }
    }

    return result;
}

int str2int(const char* str_buf) {
    int result = 0;
    int max_chars = 10; // max number of chars read from str_buf
    int i = 0;
    int sign = 0;

    if (str_buf == NULL)
        return result;

    if (str_buf[0] == '-') {
        sign = -1;
        i++;
        max_chars++;
    }

    for (; i < max_chars; i++) {
        if ( str_buf[i] >= '0' && str_buf[i] <= '9') {
            result *= 10;
            result += str_buf[i] - '0';

        } else {
            break;
        }
    }

    if (sign == -1)
        result = -result;

    return result;
}

void * memset(void *dst, char c, size_t n) {
    size_t i;
    for (i=0; i<n; i++) {
        *((uint8_t*)dst+i) = c;
    }
    return dst;
}

void * memcpy(void *dst, void *src, size_t n) {
    size_t i;
    for (i=0; i<n; i++) {
        *((uint8_t*)dst+i) = *((uint8_t*)src+i);
    }
    return dst;
}

char * b2hex(uint8_t b, char *h) {
    if (b>>4 < 10)
        h[0] = (b>>4)+0x30;
    else
        h[0] = (b>>4)+0x41-10;

    if ((b&0xf) < 10)
        h[1] = (b&0xf)+0x30;
    else
        h[1] = (b&0xf)+0x41-10;
    h[2] = '\0';
    return h;
}

char * strchr(char *str, char c) {
    char *tmp = str;
    while (*tmp) {
        if (*tmp == c)
            return tmp;
        tmp++;
    }
    return 0;
}

char *strtok(char *s, char sep) {
    char *c;
    if (!s) {
        if (!strtok_last)
            return NULL;
        s = strtok_last;
        strtok_last = NULL;
        //continue parsing
    } 
    
    if (!(c = strchr(s,sep)))
        return s;

    *c = '\0';
    c++;
    strtok_last = c;
    return s;
}

//modulus
int __umoddi3(int a, int b) {
    return a-(a/b*b);
}

void sleep(int s) {
    struct timeval tv;
    tv.tv_sec = s;
    tv.tv_usec = 0;
    fdwait(0, NULL, NULL, &tv, NULL);
}

int memcmp(void *a, void *b, size_t n) {
    size_t i;
    for (i=0; i < n; i++)
        if ( *(uint8_t*)(a+i) != *(uint8_t*)(b+i))
            return -1;
    return 0;
}

static void heapinit() {
    int i;
    RAND(&__hcookie[SSHEAP], sizeof(__hcookie[SSHEAP]), NULL);
    __hcookie[SHEAP] = 0x50C0FFEE;
    for (i = 0; i < 3; i++) {
        allocated[i] = &allocatedc[i];
        freed[i] = &freedc[i];
        allocated[i]->next = allocated[i];
        allocated[i]->prev = allocated[i];
        allocated[i]->cookie = __hcookie[i];
        freed[i]->cookie = __hcookie[i];
        freed[i]->next = freed[i];
        freed[i]->prev = freed[i];
        heapinit_done = true;
    }
}

static void insert(heap_chunk_t *head, heap_chunk_t *node, heaptype type) {
    node->cookie = __hcookie[type];
    node->next = head;
    node->prev = head->prev;
    node->prev->next = node;
    head->prev = node;
}

static void remove(heap_chunk_t *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = NULL;
    node->prev = NULL;
}

static void *__malloc(size_t size, heaptype type) {
    /*
     * A very stupid malloc implementation, meant to be simple.
     * Keeps a list of allocated and freed chunks
     * Alloc walks list of freed chunks to see if any are large enough
     * If not, it allocates space large enough to store
     * Oh, and we never actually free pages. It's quality software.
     *
     */
    if (!heapinit_done) 
        heapinit();

    if (size == 0 || size > 0x7fffffff)
        return NULL;

    heap_chunk_t *chunk = freed[type];
    heap_chunk_t *frag = NULL;
    heap_chunk_t *prev = NULL;

    //need space for inline metadata
    size += sizeof(heap_chunk_t);

    //walk freed list to see if we can find match
    //while we're walking free list, might as well coalesce as we go
    //this will only coalesce adjacent blocks in the freelist
    while (chunk->size < size && HNEXT(chunk,type) != freed[type]) {

        //ommitted type of HNEXT(chunk,type) != freed here because freed is only node in BSS
        //should never be adjacent
        while ((uint8_t*)HNEXT(chunk,type) == ((uint8_t*)chunk)+chunk->size) {
            frag = HNEXT(chunk,type);
            remove(frag);
            chunk->size += frag->size;
        }

        //make sure HNEXT(chunk,type) isn't freed after coalesce, though
        if (HNEXT(chunk,type) == freed[type])
            break;

        chunk = HNEXT(chunk,type);

    }

    if (type && __hcookie[type] != chunk->cookie)
        __heap_cookie_fail();


    if (chunk->size >= size) {
        //found a match, remove from freed list, add to allocated list, and return
        //SSSENDL("found free chunk");
        
        remove(chunk);

        //first, break up chunk if we can create another valid chunk out of it
        //this will fragment badly under some workloads, but meh
        if (chunk->size > (size+sizeof(heap_chunk_t)+1)) {
            frag = (heap_chunk_t*)(((uint8_t*)chunk)+size);
            frag->size = chunk->size - size;
            chunk->size = size;
            insert(freed[type],frag,type);
        }

        insert(allocated[type],chunk,type);
        return ((uint8_t*)chunk)+sizeof(heap_chunk_t);
    }

    //see if free space in last allocated page is enough
    if (size <= curleft[type]) {
        //SSSENDL("had enough left in current page");
        chunk = (heap_chunk_t*)lastpage[type];
        chunk->size = size;
        lastpage[type] += size;
        curleft[type] -= size;
        insert(allocated[type],chunk,type);
        return ((uint8_t*)chunk)+sizeof(heap_chunk_t);
    }

    //need to allocate new page

    //SSSENDL("allocating new page");
    //first add the remaining page to our freed list as a lazy hack
    //if there's not enough left, we just let it leak
    if (curleft[type] > sizeof(heap_chunk_t)) {
        //SSSENDL("adding remainder to free list");
        chunk = (heap_chunk_t*)lastpage[type];
        chunk->size = curleft[type];
        insert(freed[type],chunk,type);
    }

    if (allocate(size,0,(void**)&chunk) != 0)
        return NULL;

    chunk->size = size;
    insert(allocated[type],chunk,type);

    lastpage[type] = ((uint8_t*)chunk)+size;
    //this is bad.
    if ((size & 0xfff) != 0)
        curleft[type] = PAGE_SIZE-(size&(PAGE_SIZE-1));
    else
        curleft[type] = 0;
    return ((uint8_t*)chunk)+sizeof(heap_chunk_t);
}

void __free(void *p, heaptype type) {
    /*
     * A very stupid free for a very stupid malloc
     * Simply moves pointer from allocated to free list
     * With no typeing of anything, obviously
     *
     */
    if (!p)
        return;

    heap_chunk_t *chunk = (heap_chunk_t*)((uint8_t*)p - sizeof(heap_chunk_t));

    if (type && __hcookie[type] != chunk->cookie)
        __heap_cookie_fail();

    //fix allocated list
    remove(chunk);

    //add chunk to the freed list
    insert(freed[type],chunk,type);
    return;
}

void *nmalloc(size_t size) {
    return __malloc(size, YOLO);
}

void *smalloc(size_t size) {
    return __malloc(size, SHEAP);
}

void *ssmalloc(size_t size) {
    return __malloc(size, SSHEAP);
}

void *malloc(size_t size) {
    if (!mallocp)
        setheap(0);
    return mallocp(size);
}

void nfree(void *p) {
    return __free(p, YOLO);
}

void sfree(void *p) {
    return __free(p, SHEAP);
}

void ssfree(void *p) {
    return __free(p, SSHEAP);
}

void free(void *p) {
    if (!freep)
        setheap(0);
    freep(p);
}

void *calloc(size_t size) {
    void *ptr;

    if (!(ptr = malloc(size)))
        return NULL;

    memset(ptr,'\0',size);
    return ptr;
}


void setheap(uint32_t type) {
    if (type == 0x10100110) {
        __htype = YOLO;
        mallocp = nmalloc;
        freep = nfree;
    } else if (type == 0xF0C0FFEE) {
        __htype = SHEAP;
        mallocp = smalloc;
        freep = sfree;
    } else {
        __htype = SSHEAP;
        mallocp = ssmalloc;
        freep = ssfree;
    }
}

void checkheap() {
    //validate free and allocated lists!
    uint32_t type = __htype;
    heap_chunk_t *chunk = freed[type];

    //forward and backwards

    while((chunk=HNEXT(chunk,type)) != freed[type]);
    while((chunk=HPREV(chunk,type)) != freed[type]);
    chunk = allocated[type];
    while((chunk=HNEXT(chunk,type)) != allocated[type]);
    while((chunk=HPREV(chunk,type)) != allocated[type]);
}

void __stack_cookie_init() {
    RAND(&__cookie, sizeof(__cookie), NULL);
}

void __cookie_fail() {
    SSENDL(sizeof(COOKIEFAIL)-1,COOKIEFAIL);
    _terminate(66);
}

void __stack_cookie_fail() {
    __cookie_fail();
}

void __heap_cookie_fail() {
    __cookie_fail();
}
