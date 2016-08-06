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
//#define DEBUG


typedef struct MALLOC_AR_E {

    void *allocation;
    size_t size;

} MALLOC_E;

struct MALLOC_AR {
    MALLOC_E *head;
};

static struct MALLOC_AR malloc_array;

unsigned int pos_ceil(double num){
    unsigned int trunc_num = (unsigned int) num;
    if((double) trunc_num == num)
        return trunc_num;

    return trunc_num + 1;
}

int malloc_init(){
    int ret =  allocate(MAX_ALLOCATIONS*sizeof(MALLOC_E), 0, (void **) &malloc_array.head);
    if(ret != 0){
        _terminate(ret);
    }
    assert(malloc_array.head != NULL);
    return 0;
}



int buf_is_numeric(char *buf){
    for(int i = 0; i < strlen(buf); ++i){
        if((buf[i] < '0' || buf[i] > '9') && buf[i] != '-'){
            return 0;
        }
    }
    return 1;
}

int atoi(char *buf){
    int dir = 1;
    int start = 0;
    if(buf[start] == '-')
        dir = -1;

    int final = 0;
    for(int i = start; i < strlen(buf); ++i ){
        final = final * 10 + buf[i] - '0';
    }
    final *= dir;

    return final;
}


size_t read_ascii_line(int fd, char *data, size_t len){
    size_t tot_rx = 0;

    for(int i = 0; i < len && i < MAX_LINE_SZ-1; ++i){
        size_t this_recv = 0;
        int recv_ret = receive(fd, &(data[i]), 1, &this_recv);
        if(recv_ret == 0 && this_recv == 1){
            tot_rx += 1;
            // todo check if its ascii and not binary
            if(data[i] == 0x0a || data[i] == 0x00){
                data[i] = 0x00;
                break;
            }
            
        // todo we still modify the buf even if we have an error condition part way through
        }else{
            return 0;
        }
    }
    data[MAX_LINE_SZ-1] = 0x00;

    return tot_rx;

}

char *STRTOK = "";

char *strtok(char *str, const char delim){
    if(str == NULL){
        str = STRTOK;
    }else{
        STRTOK = "";
    }
    int sl = strlen(str);
    if(sl == 0){

        return NULL;
    }
    for(int i = 0; i < sl; ++i){
        if(str[i] == delim){
            // null terminate
            str[i] = 0x00;
            STRTOK = &(str[i+1]);
            return str;
        } else if(str[i] == 0x00 && i != 0){

            return str;
        }
    }
    
    return str;
}


void * calloc(size_t nmemb, size_t s){
    size_t sz = nmemb * s;



    char *x = (char *) malloc(sz);
    if(x == NULL){

        return NULL;
    }

    for(int i = 0; i < sz; i++){
        x[i] = 0x00;
    }

    return  x;
}
int recv_until(int fd, char *buf, const size_t buf_sz, const char delim){
    size_t size_recvd =0;
    int ret = receive(fd, (void *) buf, buf_sz, &size_recvd);
    if(ret != 0)
        return -1;
    

    for(int i =0; i < size_recvd; ++i){
        if(delim == buf[i])
            return i;

    }
    return -2;

}

int transmit_all(int fd, const char *buf, const size_t size) {
    size_t sent = 0;
    size_t sent_now = 0;
    int ret;


    if (!size)
        return 2;

    while (sent < size) {
        ret = transmit(fd, buf + sent, size - sent, &sent_now);
        if (ret != 0) {
            return 3;
        }
        sent += sent_now;
    }

    return 0;
}

size_t strlen(const char *s){
    int i = 0;
    const char *p;
    for(p = s; *p; ++p){


    }
    return p-s;
}

#ifdef DEBUG
void err(char *m){

    transmit_all(STDOUT, m, strlen(m)); 
    transmit_all(STDOUT, "\n", strlen("\n"));      
}
#endif

char *strcat(char * s1, char *s2){
    size_t n = strlen(s1);
    memcpy(&(s1[n]), s2, strlen(s2));

    return s1;
}

void * malloc(size_t s){
    // todo check size incoming and limit it.

    for(int i = 0; i < MAX_ALLOCATIONS; i++){
        MALLOC_E *mm = malloc_array.head+i;
        if(mm->allocation == NULL){

            int ret = allocate(s, 0, (void **)  &(mm->allocation));
            if(ret != 0){
#ifdef DEBUG                
                if(ret == EINVAL)
                    err("Alloc returns inval");
                if(ret == EFAULT)
                    err("invalid dest addr specd");
                err("Other error");
#endif
                return NULL;
            }
            mm->size = s;
            // todo remove once we get whole page size
            // for(int j = 0; j < 4096; ++j)
            //     ((char *) (mm->allocation))[j] = 0xc;
            return mm->allocation;

        }
    }
    

    return NULL;
}

void free(void *p){
    // traverse from the rear just to throw off identification
    if(p == NULL){
#ifdef DEBUG
        err("Can't free null!");
#endif
        return;

    }


    for(int i = MAX_ALLOCATIONS-1; i >= 0; i--){
        MALLOC_E *mm = malloc_array.head+i;
        if(mm != NULL && p == mm->allocation){
            int x = deallocate(mm->allocation, mm->size);
#ifdef DEBUG            
            if(x != 0)
                err("Deallocate problem");
#endif
            mm->allocation = NULL;
            mm->size = 0;
            return;
        }
    }
#ifdef DEBUG
    err("Failed to deallocate");
#endif
}

void memcpy(void *d, const void *s, size_t size){
    char *dc = (char *)d;
    char *sc = (char *)s;

    for(int j = 0; j < size; j++ ){
        *(dc+j) = *(sc+j);
    }
}

// todo not true memcmp in positive results
int memcmp(void *d, const void *s, size_t size){
    char *dc = (char *)d;
    char *sc = (char *)s;


    for(int j = 0; j < size; j++ ){
        if(*(dc+j) != *(sc+j))
            return 1;

    }
    return 0;
}

char * itoaB10(int value){
    int max_width = 12;
    char *s = malloc(max_width); // max len of 2**32 + negative to be paranoid
    if(s == NULL)
        return NULL;
    int tmp = value;
    
    if(value == 0){
        memcpy(s, "0\x00", 2);
        return s;
    }
    int neg = 0;
    if(value < 0){
        neg = 1;
        tmp = -tmp;
    }
    int i = 0;
    for(; i < max_width && tmp != 0; ++i){
        int r = tmp % 10;
        if(r > 9)
            s[i] = (r - 10) + 'a';
        else
            s[i] = r + '0';
        tmp = tmp/10;
    }

    if(neg == 1)
        s[i+1] = '-';

    char *f = malloc(max_width);
    int final_len = strlen(s);
    for(int j =0; j < final_len; ++j){
        f[j] = s[final_len-j-1];
    }
    free(s);
    return f;
}

void malloc_reset(){
    for(int i = MAX_ALLOCATIONS-1; i >= 0; i--){
        MALLOC_E *mm = malloc_array.head+i;
        if(mm != NULL && mm->allocation != NULL){
            int x = deallocate(mm->allocation, mm->size);
#ifdef DEBUG
            if(x != 0)
                err("Deallocate problem");
#endif
            mm->allocation = NULL;
            mm->size = 0;
            
        }
    }
}
