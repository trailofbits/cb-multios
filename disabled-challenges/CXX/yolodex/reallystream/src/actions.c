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
#include "cgc_service.h"
#include "cgc_actions.h"
#include "cgc_libc.h"
#include "cgc_rle.h"
#include "cgc_r.h"

#define NOSUCHVID "I hate this hacker crap!"
#define VIDEXISTS "It's a UNIX system, I know this!"
#define GOODBYE "God help us, we're in the hands of engineers..."
#define ACCKEY "Your personal access key is: 0x"
#define REMOVED "Creation is an act of sheer will. Next time it'll be flawless."
#define FINISHED "PLAYBACK FINISHED" 

video *cgc_get_video_by_name(char *buf) {
    video *cur = vhead;
    while (cur) {
        if (cgc_streq(cur->name,buf))
            return cur;
        cur = cur->next;
    }
    return NULL;
}


void cgc_list(char *buf){
    uint32_t i = 1;
    char tmp[11] = {0};
    video *cur = vhead;

    while(cur) {
        cgc_int2str(tmp,sizeof(tmp),i++);
        SSEND(cgc_strlen(tmp),tmp);
        SSEND(3,".) ")
        SSENDL(cgc_strlen(cur->name),cur->name);
        cur = cur->next;
    }
}

void cgc_play(char *buf){
    char *key;
    video *toplay;

    if (cgc_streq(buf,"trolololo A")) {
        ALLOC(0, (void**)&toplay, sizeof(video));
        toplay->key = 'A';
        toplay->encbuf = r_bin;
        toplay->elen = r_bin_len-4;
        toplay->csum = *(uint32_t*)(r_bin+r_bin_len-4);
        cgc_decode(toplay,'A');

        if(toplay->decbuf){
            SSENDL(toplay->dlen,(char *)toplay->decbuf);
            SSENDL(sizeof(FINISHED)-1,FINISHED);
            DEALLOC((void*)toplay->decbuf, toplay->dlen);
        }else{
            SSENDL(sizeof(NOSUCHVID)-1,NOSUCHVID);
        }

        DEALLOC((void*)toplay, sizeof(video));
        return;
    }

    key = cgc_strchr(buf,' ');

    if(!key) {
        SSENDL(sizeof(NOSUCHVID)-1,NOSUCHVID);
        return;
    }

    *key = '\0'; 

    if(!*(key+1) || *(key+2)){
        SSENDL(sizeof(NOSUCHVID)-1,NOSUCHVID);
        return;
    }

    key += 1;

    toplay = cgc_get_video_by_name(buf);
    if(!toplay) {
        SSENDL(sizeof(NOSUCHVID)-1,NOSUCHVID);
        return;
    }

    cgc_decode(toplay,*key);

    if(toplay->decbuf){
        SSENDL(toplay->dlen,(char *)toplay->decbuf);
        SSENDL(sizeof(FINISHED)-1,FINISHED);
    }else{
        SSENDL(sizeof(NOSUCHVID)-1,NOSUCHVID);
    }
}

void cgc_add(char *buf){
    video *vlast = NULL, *new = NULL, *cur = NULL;
    char recvbuf[11] = {0};
    char keyascii[3] = {0};
    cur = vhead;
    cgc_size_t total, rndbytes;

    if(cgc_strlen(buf) > MAX_NAME_SIZE || cgc_strlen(buf) == 0) {
        SSENDL(sizeof(MAGICWORD)-1,MAGICWORD);
        cgc__terminate(14);
    }

    if(cgc_get_video_by_name(buf) || cgc_strchr(buf,' ')) {
        SSENDL(sizeof(VIDEXISTS)-1,VIDEXISTS);
        return;
    }

    SSEND(sizeof("Length: ")-1,"Length: ");
    SRECV(sizeof(recvbuf)-1,recvbuf);

    total = cgc_str2uint(recvbuf);

    #ifndef PATCHED
    if (total > 129*1024 || total < 8 || total%4 != 0) { 
    #else
    if (total > 128*1024 || total < 8 || total%4 != 0) { 
    #endif
        SSENDL(sizeof(MAGICWORD)-1,MAGICWORD);
        cgc__terminate(13);
    }

    ALLOC(0, (void**)&new, sizeof(video)+total);

    //RAND(&(new->key), 1, &rndbytes);
    new->key = 0x42; //cause we can't handle random data in poller

    cgc_b2hex(new->key,keyascii);

    SSEND(sizeof(ACCKEY)-1,ACCKEY);
    SSENDL(2,keyascii);

    
    new->can_delete = 1;
    cgc_strcpy(new->name,buf);
    
    RECV(total,((char*)new)+sizeof(video));
    new->elen = total-4;
    new->encbuf = ((uint8_t*)new)+sizeof(video);
    new->csum = *((uint32_t*)(new->encbuf+total-4));

    while (cur) {
        vlast = cur;
        cur = cur->next;
    }

    if (!vhead)
        vhead = new;

    if (vlast) {
        vlast->next = new;
        new->prev = vlast;
    }

    new->prev = vlast;
    new->next = NULL;

}

void cgc_remove(char *buf){
    video *toremove;
    
    toremove = cgc_get_video_by_name(buf);

    if(!toremove) {
        SSENDL(sizeof(NOSUCHVID)-1,NOSUCHVID);
        return;
    }
    
    if(!toremove->can_delete){
        SSENDL(sizeof(NOSUCHVID)-1,NOSUCHVID);
        return;
    }


    if(toremove->next)
        toremove->next->prev = toremove->prev;
    
    if(toremove->prev)
        toremove->prev->next = toremove->next;
    else
        vhead = toremove->next;

    if (toremove->decbuf)
        DEALLOC((void*)toremove->decbuf, toremove->dlen);

    DEALLOC((void*)toremove, sizeof(video)+toremove->elen);
    SSENDL(sizeof(REMOVED)-1,REMOVED);

}

void cgc_quit(char *buf){
    SSENDL(sizeof(GOODBYE)-1,GOODBYE);
    cgc__terminate(0);
}
