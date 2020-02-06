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
#include "cgc_sheap.h"
#include "cgc_libc.h"



unsigned int cgc_pos_ceil(double num){
    unsigned int trunc_num = (unsigned int) num;
    if((double) trunc_num == num)
        return trunc_num;

    return trunc_num + 1;
}






int cgc_buf_is_numeric(char *buf){
    for(int i = 0; i < cgc_strlen(buf); ++i){
        if((buf[i] < '0' || buf[i] > '9') && buf[i] != '-'){
            return 0;
        }
    }
    return 1;
}

int cgc_atoi(char *buf){
    int dir = 1;
    int start = 0;
    if(buf[start] == '-')
        dir = -1;

    int final = 0;
    for(int i = start; i < cgc_strlen(buf); ++i ){
        final = final * 10 + buf[i] - '0';
    }
    final *= dir;

    return final;
}


cgc_size_t cgc_read_ascii_line(int fd, char *data, cgc_size_t len){
    cgc_size_t tot_rx = 0;

    for(int i = 0; i < len && i < MAX_LINE_SZ-1; ++i){
        cgc_size_t this_recv = 0;
        int recv_ret = cgc_receive(fd, &(data[i]), 1, &this_recv);
        if(recv_ret == 0 && this_recv == 1){
            tot_rx += 1;
            
            if(data[i] == 0x0a || data[i] == 0x00){
                data[i] = 0x00;
                break;
            }
            
        
        }else{
            return 0;
        }
    }
    data[MAX_LINE_SZ-1] = 0x00;

    return tot_rx;

}

char *STRTOK = "";

char *cgc_strtok(char *str, const char delim){
    if(str == NULL){
        str = STRTOK;
    }else{
        STRTOK = "";
    }
    int sl = cgc_strlen(str);
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


void * cgc_calloc(cgc_size_t nmemb, cgc_size_t s){
    cgc_size_t sz = nmemb * s;



    char *x = (char *) cgc_malloc(sz);
    if(x == NULL){

        return NULL;
    }

    for(int i = 0; i < sz; i++){
        x[i] = 0x00;
    }

    return  x;
}
int cgc_recv_until(int fd, char *buf, const cgc_size_t buf_sz, const char delim){
    cgc_size_t size_recvd =0;
    int ret = cgc_receive(fd, (void *) buf, buf_sz, &size_recvd);
    if(ret != 0)
        return -1;
    

    for(int i =0; i < size_recvd; ++i){
        if(delim == buf[i])
            return i;

    }
    return -2;

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

cgc_size_t cgc_strlen(const char *s){
    int i = 0;
    const char *p;
    for(p = s; *p; ++p){


    }
    return p-s;
}

#ifdef DEBUG
void err(char *m){

    cgc_transmit_all(STDOUT, m, cgc_strlen(m)); 
    cgc_transmit_all(STDOUT, "\n", cgc_strlen("\n"));      
}
#endif

char *cgc_strcat(char * s1, char *s2){
    cgc_size_t n = cgc_strlen(s1);
    cgc_memcpy(&(s1[n]), s2, cgc_strlen(s2));

    return s1;
}




void cgc_memcpy(void *d, const void *s, cgc_size_t size){
    char *dc = (char *)d;
    char *sc = (char *)s;

    for(int j = 0; j < size; j++ ){
        *(dc+j) = *(sc+j);
    }
}


int cgc_memcmp(void *d, const void *s, cgc_size_t size){
    char *dc = (char *)d;
    char *sc = (char *)s;


    for(int j = 0; j < size; j++ ){
        if(*(dc+j) != *(sc+j))
            return 1;

    }
    return 0;
}

char * cgc_itoaB10(int value){
    int max_width = 12;
    char *s = cgc_malloc(max_width); // max len of 2**32 + negative to be paranoid
    if(s == NULL)
        return NULL;
    int tmp = value;
    
    if(value == 0){
        cgc_memcpy(s, "0\x00", 2);
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

    char *f = cgc_malloc(max_width);
    int final_len = cgc_strlen(s);
    for(int j =0; j < final_len; ++j){
        f[j] = s[final_len-j-1];
    }
    cgc_free(s);
    return f;
}


