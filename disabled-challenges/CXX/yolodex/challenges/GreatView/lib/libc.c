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

#include "libcgc.h"
#include "cgc_libc.h"


void (*freep)(void *);
void *(*mallocp)(cgc_size_t);

bool cgc_heapinit_done = false;

heap_chunk_t cgc_freedc[3] = {0};

heap_chunk_t cgc_allocatedc[3] = {0};

heap_chunk_t *cgc_freed[3] = {0};

heap_chunk_t *cgc_allocated[3] = {0};

uint8_t *cgc_lastpage[3] = {0};
uint32_t cgc_curleft[3] = {0};

uint32_t cgc___cookie[3] = {0};
uint32_t cgc___hcookie[3] = {0};
heaptype cgc___htype = 0;

static char *strtok_last = NULL;

void cgc_promptc(char *buf, uint16_t  size, char *prompt) {

    SSEND(cgc_strlen(prompt), prompt);

    SRECV((uint32_t)size, buf);
}

int cgc_sendall(int fd, const char *buf, cgc_size_t size) {
    cgc_size_t sent = 0;
    cgc_size_t total = 0;

    if (!buf)
        return -1;

    if (!size)
        return 0;

    while (size) {
        if (cgc_transmit(fd, buf, size, &sent)) {
            return -1;
        }

        buf += sent;
        total += sent;
        size -= sent;
    }

    return total;
}

int cgc_sendline(int fd, const char *buf, cgc_size_t size) {
    int ret;
    ret = cgc_sendall(fd, buf, size);
    if (ret < 0) {
        return ret;
    } else {
        if (cgc_transmit(fd, "\n", 1, &size))
            return -1;
        else
            return ++ret;
    }
}

int cgc_recv(int fd, char *buf, cgc_size_t size) {
    cgc_size_t bytes_read = 0;
    cgc_size_t total_read = 0;

    if(!size)
        return 0;

    if (!buf)
        return -1;

    while (size) {
        if (cgc_receive(fd, buf, size, &bytes_read))
            return -1;
        
        total_read += bytes_read;
        size -= bytes_read;
        buf += bytes_read;
    }

    return total_read;

}


int cgc_recvline(int fd, char *buf, cgc_size_t size) {
    return cgc_recvuntil(fd, buf, size, '\n');
}

int cgc_recvuntil(int fd, char *buf, cgc_size_t size, char term) {
    cgc_size_t bytes_read = 0;
    cgc_size_t total_read = 0;

    if(!size)
        return 0;

    if (!buf)
        return -1;

    while (size) {
        if (cgc_receive(fd, buf, 1, &bytes_read))
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
cgc_size_t cgc_strcpy(char *s1, char *s2) {
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
cgc_size_t cgc_strncpy(char *s1, char *s2, cgc_size_t n) {
    char *tmp = s1;
    while ((tmp-s1 < n) && *s2) {
        *tmp = *s2;
        tmp++;
        s2++;
    }
    *(tmp++)='\0';
    return tmp-s1-1;
}

char * cgc_strcat(char *s1, char *s2) {
    char *tmp = s1;
    while (*tmp) tmp++;
    cgc_strcpy(tmp,s2);
    return s1;
}

cgc_size_t cgc_strlen(char *s) {
    char *tmp = s;
    while (*tmp) tmp++;
    return (cgc_size_t)(tmp-s);
}

int cgc_streq(char *s1, char *s2) {
    while (*s1 && *s2){
        if (*s1 != *s2)
            return 0;
	    s1++;
	    s2++;
    }
    return (*s1 == '\0') && (*s2 == '\0');
}

int cgc_strncmp(char *s1, char *s2, cgc_size_t n) {
    while (*s1 && *s2 && n--){
        if (*s1 != *s2)
            return 1;
	    s1++;
	    s2++;
    }
    return !((*s1 == '\0') && (*s2 == '\0'));
}

int cgc_startswith(char *s1, char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2)
            return 0;
	    s1++;
	    s2++;
    }
    return *s2 == '\0';
}

int cgc_uint2str(char* str_buf, int buf_size, uint32_t i) {

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

int cgc_int2str(char* str_buf, int buf_size, int i) {

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

uint32_t cgc_str2uint(const char* str_buf) {
    int result = 0;
    int max_chars = 10; // max number of chars cgc_read from str_buf
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

int cgc_str2int(const char* str_buf) {
    int result = 0;
    int max_chars = 10; // max number of chars cgc_read from str_buf
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

void * cgc_memset(void *dst, char c, cgc_size_t n) {
    cgc_size_t i;
    for (i=0; i<n; i++) {
        *((uint8_t*)dst+i) = c;
    }
    return dst;
}

void * cgc_memcpy(void *dst, void *src, cgc_size_t n) {
    cgc_size_t i;
    for (i=0; i<n; i++) {
        *((uint8_t*)dst+i) = *((uint8_t*)src+i);
    }
    return dst;
}

char * cgc_b2hex(uint8_t b, char *h) {
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

char * cgc_strchr(char *str, char c) {
    char *tmp = str;
    while (*tmp) {
        if (*tmp == c)
            return tmp;
        tmp++;
    }
    return 0;
}

char *cgc_strtok(char *s, char sep) {
    char *c;
    if (!s) {
        if (!strtok_last)
            return NULL;
        s = strtok_last;
        strtok_last = NULL;
        //continue parsing
    } 
    
    if (!(c = cgc_strchr(s,sep)))
        return s;

    *c = '\0';
    c++;
    strtok_last = c;
    return s;
}

//modulus
int cgc___umoddi3(int a, int b) {
    return a-(a/b*b);
}

void cgc_sleep(int s) {
    struct cgc_timeval tv;
    tv.tv_sec = s;
    tv.tv_usec = 0;
    cgc_fdwait(0, NULL, NULL, &tv, NULL);
}

int cgc_memcmp(void *a, void *b, cgc_size_t n) {
    cgc_size_t i;
    for (i=0; i < n; i++)
        if ( *(uint8_t*)(a+i) != *(uint8_t*)(b+i))
            return -1;
    return 0;
}

static void heapinit() {
    int i;
    RAND(&cgc___hcookie[SSHEAP], sizeof(cgc___hcookie[SSHEAP]), NULL);
    cgc___hcookie[SHEAP] = 0x50C0FFEE;
    for (i = 0; i < 3; i++) {
        cgc_allocated[i] = &cgc_allocatedc[i];
        cgc_freed[i] = &cgc_freedc[i];
        cgc_allocated[i]->next = cgc_allocated[i];
        cgc_allocated[i]->prev = cgc_allocated[i];
        cgc_allocated[i]->cookie = cgc___hcookie[i];
        cgc_freed[i]->cookie = cgc___hcookie[i];
        cgc_freed[i]->next = cgc_freed[i];
        cgc_freed[i]->prev = cgc_freed[i];
        cgc_heapinit_done = true;
    }
}

static void insert(heap_chunk_t *head, heap_chunk_t *node, heaptype type) {
    node->cookie = cgc___hcookie[type];
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

static void *cgc___malloc(cgc_size_t size, heaptype type) {
    /*
     * A very stupid malloc implementation, meant to be simple.
     * Keeps a list of allocated and freed chunks
     * Alloc walks list of freed chunks to see if any are large enough
     * If not, it allocates space large enough to store
     * Oh, and we never actually free pages. It's quality software.
     *
     */
    if (!cgc_heapinit_done) 
        heapinit();

    if (size == 0 || size > 0x7fffffff)
        return NULL;

    heap_chunk_t *chunk = cgc_freed[type];
    heap_chunk_t *frag = NULL;
    heap_chunk_t *prev = NULL;

    //need space for inline metadata
    size += sizeof(heap_chunk_t);

    //walk freed list to see if we can find match
    //while we're walking free list, might as well coalesce as we go
    //this will only coalesce adjacent blocks in the freelist
    while (chunk->size < size && HNEXT(chunk,type) != cgc_freed[type]) {

        //ommitted type of HNEXT(chunk,type) != freed here because freed is only node in BSS
        //should never be adjacent
        while ((uint8_t*)HNEXT(chunk,type) == ((uint8_t*)chunk)+chunk->size) {
            frag = HNEXT(chunk,type);
            remove(frag);
            chunk->size += frag->size;
        }

        //make sure HNEXT(chunk,type) isn't freed after coalesce, though
        if (HNEXT(chunk,type) == cgc_freed[type])
            break;

        chunk = HNEXT(chunk,type);

    }

    if (type && cgc___hcookie[type] != chunk->cookie)
        cgc___heap_cookie_fail();


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
            insert(cgc_freed[type],frag,type);
        }

        insert(cgc_allocated[type],chunk,type);
        return ((uint8_t*)chunk)+sizeof(heap_chunk_t);
    }

    //see if free space in last allocated page is enough
    if (size <= cgc_curleft[type]) {
        //SSSENDL("had enough left in current page");
        chunk = (heap_chunk_t*)cgc_lastpage[type];
        chunk->size = size;
        cgc_lastpage[type] += size;
        cgc_curleft[type] -= size;
        insert(cgc_allocated[type],chunk,type);
        return ((uint8_t*)chunk)+sizeof(heap_chunk_t);
    }

    //need to allocate new page

    //SSSENDL("allocating new page");
    //first add the remaining page to our freed list as a lazy hack
    //if there's not enough left, we just let it leak
    if (cgc_curleft[type] > sizeof(heap_chunk_t)) {
        //SSSENDL("adding remainder to free list");
        chunk = (heap_chunk_t*)cgc_lastpage[type];
        chunk->size = cgc_curleft[type];
        insert(cgc_freed[type],chunk,type);
    }

    if (cgc_allocate(size,0,(void**)&chunk) != 0)
        return NULL;

    chunk->size = size;
    insert(cgc_allocated[type],chunk,type);

    cgc_lastpage[type] = ((uint8_t*)chunk)+size;
    //this is bad.
    if ((size & 0xfff) != 0)
        cgc_curleft[type] = PAGE_SIZE-(size&(PAGE_SIZE-1));
    else
        cgc_curleft[type] = 0;
    return ((uint8_t*)chunk)+sizeof(heap_chunk_t);
}

void cgc___free(void *p, heaptype type) {
    /*
     * A very stupid free for a very stupid malloc
     * Simply moves pointer from allocated to free list
     * With no typeing of anything, obviously
     *
     */
    if (!p)
        return;

    heap_chunk_t *chunk = (heap_chunk_t*)((uint8_t*)p - sizeof(heap_chunk_t));

    if (type && cgc___hcookie[type] != chunk->cookie)
        cgc___heap_cookie_fail();

    //fix allocated list
    remove(chunk);

    //add chunk to the freed list
    insert(cgc_freed[type],chunk,type);
    return;
}

void *cgc_nmalloc(cgc_size_t size) {
    return cgc___malloc(size, YOLO);
}

void *cgc_smalloc(cgc_size_t size) {
    return cgc___malloc(size, SHEAP);
}

void *cgc_ssmalloc(cgc_size_t size) {
    return cgc___malloc(size, SSHEAP);
}

void *cgc_malloc(cgc_size_t size) {
    if (!mallocp)
        cgc_setheap(0);
    return mallocp(size);
}

void cgc_nfree(void *p) {
    return cgc___free(p, YOLO);
}

void cgc_sfree(void *p) {
    return cgc___free(p, SHEAP);
}

void cgc_ssfree(void *p) {
    return cgc___free(p, SSHEAP);
}

void cgc_free(void *p) {
    if (!freep)
        cgc_setheap(0);
    freep(p);
}

void *cgc_calloc(cgc_size_t size) {
    void *ptr;

    if (!(ptr = cgc_malloc(size)))
        return NULL;

    cgc_memset(ptr,'\0',size);
    return ptr;
}


void cgc_setheap(uint32_t type) {
    if (type == 0x10100110) {
        cgc___htype = YOLO;
        mallocp = cgc_nmalloc;
        freep = cgc_nfree;
    } else if (type == 0xF0C0FFEE) {
        cgc___htype = SHEAP;
        mallocp = cgc_smalloc;
        freep = cgc_sfree;
    } else {
        cgc___htype = SSHEAP;
        mallocp = cgc_ssmalloc;
        freep = cgc_ssfree;
    }
}

void cgc_checkheap() {
    //validate free and allocated lists!
    uint32_t type = cgc___htype;
    heap_chunk_t *chunk = cgc_freed[type];

    //forward and backwards

    while((chunk=HNEXT(chunk,type)) != cgc_freed[type]);
    while((chunk=HPREV(chunk,type)) != cgc_freed[type]);
    chunk = cgc_allocated[type];
    while((chunk=HNEXT(chunk,type)) != cgc_allocated[type]);
    while((chunk=HPREV(chunk,type)) != cgc_allocated[type]);
}

void cgc___stack_cookie_init() {
    RAND(&cgc___cookie, sizeof(cgc___cookie), NULL);
}

void cgc___cookie_fail() {
    SSENDL(sizeof(COOKIEFAIL)-1,COOKIEFAIL);
    cgc__terminate(66);
}

void cgc___stack_cookie_fail() {
    cgc___cookie_fail();
}

void cgc___heap_cookie_fail() {
    cgc___cookie_fail();
}
