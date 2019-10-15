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

bool cgc_heapinit_done = false;
heap_chunk_t cgc_freedc = {0};
heap_chunk_t cgc_allocatedc = {0};
heap_chunk_t *cgc_freed = NULL;
heap_chunk_t *cgc_allocated = NULL;

uint8_t *cgc_lastpage = NULL;
uint32_t cgc_curleft = 0;

uint32_t cgc___cookie = 0;

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

    if (!size)
        return 0;

    if (!buf)
        return -1;

    while (size) {
        if (cgc_receive(fd, buf++, 1, &bytes_read))
            return -1;
        
        total_read++;
        size--;
    }

    return total_read;

}

// mod from FASTLANE: lines terminated with \x07, diff return values, 
int cgc_recvline(int fd, char *buf, cgc_size_t size) {
    cgc_size_t bytes_read = 0;
    cgc_size_t total_read = 0;

    if(!size)
        return 0;

    if (!buf)
        return -7;

    while (size) {
        if (cgc_receive(fd, buf++, 1, &bytes_read))
            return -7;
        
        total_read++;
        size--;
        
        if(*(buf-1) == '\x07')
            break;
    }

    if (*(buf-1) != '\x07')
        return -77;
    else
        *(buf-1) = '\0';

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

int cgc_startswith(char *s1, char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2)
            return 0;
	    s1++;
	    s2++;
    }
    return *s2 == '\0';
}

// takes a uint32 and converts it to a string saved in str_buf
// str_buf must be large enough to fit the number(s) and '\0'
// returns 0 on success, -1 if error due to buf_size
int cgc_uint2str(char* str_buf, unsigned int buf_size, uint32_t i) {

    int idx = 0;
    uint32_t tmp;
    int digit;

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

    //testing
    // str_buf[0] = '0' - i;
    // str_buf[1] = '\0';

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

// takes an int32 and converts it to a string saved in str_buf
// str_buf must be large enough to fit the sign, number(s), and '\0'
// returns 0 on success, -1 if error due to buf_size
int cgc_int2str(char* str_buf, unsigned int buf_size, int i) {

    int idx = 0;
    int tmp;
    int digit;

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

    //testing
    // str_buf[0] = '0' - i;
    // str_buf[1] = '\0';

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

// takes a string and converts it to an uint32
// MAX uint32 is +/- 2^31-1 (2,147,483,647) which is 10 digits
// returns 0 if str_buf is "0" or has no digits.
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

static void cgc_heapinit() {
    cgc_allocated = &cgc_allocatedc;
    cgc_freed = &cgc_freedc;
    cgc_allocated->next = cgc_allocated;
    cgc_allocated->prev = cgc_allocated;
    cgc_freed->next = cgc_freed;
    cgc_freed->prev = cgc_freed;
    cgc_heapinit_done = true;
}

static void cgc_insert(heap_chunk_t *head, heap_chunk_t *node) {
    node->next = head;
    node->prev = head->prev;
    node->prev->next = node;
    head->prev = node;
}

static void cgc_remove(heap_chunk_t *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = NULL;
    node->prev = NULL;
}

void cgc_checkheap() {
    /*
     * Verify that there is no overlap between freed and allocated lists.
     */
    heap_chunk_t *fchunk = cgc_freed;
    heap_chunk_t *achunk;
    while (fchunk->next != cgc_freed) {
        achunk = cgc_allocated;
        while (achunk->next != cgc_allocated) {
            if ((uint32_t)fchunk < (uint32_t)(((uint8_t*)achunk)+achunk->size) &&
                (uint32_t)achunk < (uint32_t)(((uint8_t*)fchunk)+fchunk->size)) {
                LOG("corrupt");
                cgc__terminate(283);
            }
            achunk = achunk->next;
        }
        fchunk = fchunk->next;
    }
}

void *cgc_malloc(cgc_size_t size) {
    /*
     * A very stupid malloc implementation, meant to be simple.
     * Keeps a list of allocated and freed chunks
     * Alloc walks list of freed chunks to see if any are large enough
     * If not, it allocates space large enough to store
     * Oh, and we never actually free pages. It's quality software.
     *
     */
    if (!cgc_heapinit_done) 
        cgc_heapinit();

    if (size == 0)
        return NULL;

    heap_chunk_t *chunk = cgc_freed;
    //need space for inline metadata
    size += sizeof(heap_chunk_t);

    //walk freed list to see if we can find match
    while (chunk->size < size && chunk->next != cgc_freed) {
        chunk = chunk->next;
    }

    if (chunk->size >= size) {
        //found a match, remove from freed list, add to allocated list, and return
        //SSSENDL("found free chunk");
        cgc_remove(chunk);
        cgc_insert(cgc_allocated,chunk);
        return ((uint8_t*)chunk)+sizeof(heap_chunk_t);
    }

    //see if free space in last allocated page is enough
    if (size <= cgc_curleft) {
        //SSSENDL("had enough left in current page");
        chunk = (heap_chunk_t*)cgc_lastpage;
        chunk->size = size;
        cgc_lastpage += size;
        cgc_curleft -= size;
        cgc_insert(cgc_allocated,chunk);
        return ((uint8_t*)chunk)+sizeof(heap_chunk_t);
    }

    //need to allocate new page

    //SSSENDL("allocating new page");
    //first add the remaining page to our freed list as a lazy hack
    //if there's not enough left, we just let it leak
    if (cgc_curleft > sizeof(heap_chunk_t)) {
        //SSSENDL("adding remainder to free list");
        chunk = (heap_chunk_t*)cgc_lastpage;
        chunk->size = cgc_curleft;
        cgc_insert(cgc_freed,chunk);
    }

    if (cgc_allocate(size,0,(void**)&chunk) != 0)
        return NULL;

    chunk->size = size;
    cgc_insert(cgc_allocated,chunk);

    cgc_lastpage = ((uint8_t*)chunk)+size;
    //this is bad.
    if ((size & 0xfff) != 0)
        cgc_curleft = PAGE_SIZE-(size&(PAGE_SIZE-1));
    else
        cgc_curleft = 0;
    return ((uint8_t*)chunk)+sizeof(heap_chunk_t);
}

void *cgc_calloc(cgc_size_t size) {
    void *ptr;

    if (!(ptr = cgc_malloc(size)))
        return NULL;

    cgc_memset(ptr,'\0',size);
    return ptr;
}

void cgc_free(void *p) {
    /*
     * A very stupid free for a very stupid malloc
     * Simply moves pointer from allocated to free list
     * With no checking of anything, obviously
     *
     */
    if (!p)
        return;

    heap_chunk_t *chunk = (heap_chunk_t*)((uint8_t*)p - sizeof(heap_chunk_t));

    //fix allocated list
    cgc_remove(chunk);

    //add chunk to the freed list
    cgc_insert(cgc_freed,chunk);
    return;
}

void cgc___stack_cookie_init() {
    RAND(&cgc___cookie, sizeof(cgc___cookie), NULL);
}

void cgc___stack_cookie_fail() {
    SSENDL(sizeof(COOKIEFAIL)-1,COOKIEFAIL);
    cgc__terminate(66);
}

int cgc_transmit_all(int fd, const char *buf, const cgc_size_t size) {
    cgc_size_t sent = 0;
    cgc_size_t sent_now = 0;
    int ret;


    if (!size)
        return 2;

    while (sent < size) {
        ret = cgc_transmit(fd, buf + sent, size - sent, &sent_now);
        if (ret != 0) {
            return 3;
        }
        sent += sent_now;
    }

    return 0;
}

// Modified to stop at a max length
cgc_size_t cgc_strnlen(const char *string, cgc_size_t max_len) {
    cgc_size_t size = 0;
    
    while(size < max_len) {
        if(string[size] == '\0')
            return size;
        size++;
    }

    return max_len;
}

// From JUKEBOX, modified for non-null-terminated string2
int cgc_strcmp(const char* string1, const char* string2)
{
    int pos;

    for(pos = 0; string1[pos] != '\0' && string1[pos] == string2[pos]; pos++);
        
    if(string1[pos] == '\0')
        return 0;

    return string1[pos] - string2[pos];
}

int cgc_strncmp(const char *s1, const char *s2, cgc_size_t n)
{
     for(; n>0; s1++, s2++, --n)
     {
        if(*s1!=*s2)
            return *(const unsigned char*) s1 - *(const unsigned char*) s2;
     }

     return 0;
}