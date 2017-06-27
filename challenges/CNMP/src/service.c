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

#include "cgc_service.h"




int cgc_send(const char *buf, const cgc_size_t size) {
    int ret;
    ret = cgc_sendall(STDOUT, buf, size);
    if (ret != 0)
        cgc__terminate(1);

    return 0;
}

int cgc_recv(char *res_buf, cgc_size_t res_buf_size) {
    int bytes_read;
    bytes_read = cgc_recvline(STDIN, res_buf, res_buf_size);
    if (bytes_read < 0) {
        cgc_send(BADSTRERROR, cgc_strlen(BADSTRERROR));
        cgc__terminate(2);
    }

    return 0;
}

// res_buf_size should be the number of byes to cgc_read from the user + 1 for '\0'.
int cgc_prompt_user(char* prompt_str, char* res_buf, cgc_size_t res_buf_size) {
    // send prompt
    cgc_send(prompt_str, cgc_strlen(prompt_str));

    // receive user input
    cgc_recv(res_buf, res_buf_size);
    
    return 0;
}

// transmit one random joke
int cgc_send_random_joke(jokedb_struct *jokedb) {

    // get joke count
    int count = cgc_joke_count(jokedb);
    // get random id between 0 and joke count
    uint32_t random_id = 0;
    if(cgc_rand(&random_id)) {
        cgc__terminate(-10);
    }
    // send that joke
    cgc_send_joke(&jokedb->jokes[random_id % count]);

    return 0;
}

// transmit one joke
int cgc_send_joke(joke_struct *joke) {

    int return_buf_len = cgc_strlen(joke->joke_string) + 40;
    char return_buf[return_buf_len];
    cgc_snprintf(return_buf, return_buf_len, "~n: ~c\n", joke->joke_id, joke->joke_string);
    cgc_send(return_buf, cgc_strlen(return_buf));

    return 0;
}

// transmit all current jokes
int cgc_send_all_jokes(jokedb_struct *jokedb) {

    int count = jokedb->count;
    for (int i = 0; i < count; i++) {
        cgc_send_joke(&jokedb->jokes[i]);
    }

    return 0;
}


// handle LIST command
int cgc_do_list(jokedb_struct *jokedb) {
    cgc_send_all_jokes(jokedb);

    return 0;
}

// handle ADD command
int cgc_do_add(jokedb_struct *jokedb) {
    char joke_str[MAX_JOKE_STRING_LEN] = { 0 };

    int ret;

    // send ADDJOKE msg
    cgc_send(ADDJOKE, cgc_strlen(ADDJOKE));

    // send ADDPROMPT
    // get JOKE_STR from user
    cgc_prompt_user(ADDPROMPT, joke_str, MAX_JOKE_STRING_LEN);

    // append JOKE_STR to jokedb
    ret = cgc_insert_joke(jokedb, joke_str);
    if (ret == -1) {
        // jokedb is full
        cgc_send(JOKEDBFULL, cgc_strlen(JOKEDBFULL));
    } else if (ret <= -2) {
        // joke too long
        cgc_send(BADJOKEERROR, cgc_strlen(BADJOKEERROR));
    } else if (ret >= 0) {

        // joke is good
        // send JOKESTORED msg and joke_id to user
        int joke_id = ret;

        // the joke_id is up to 32bits, plus extra padding for \n and \0.
        int return_buf_len = cgc_strlen(JOKESTORED) + 40;
        char return_buf[return_buf_len];
        cgc_snprintf(return_buf, return_buf_len, JOKESTORED, joke_id);
        cgc_send(return_buf, cgc_strlen(return_buf));
    }

    return 0;
}

int cgc_do_show(jokedb_struct *jokedb) {

    // define buffer to store user provided 
    int joke_id_buf_sz = 11;
    char joke_id_buf[joke_id_buf_sz];
    uint32_t joke_id;
    char joke_str[MAX_JOKE_STRING_LEN] = { 0 };
    int id_type;
    
    // send SHOWWHICHID msg
    cgc_send(SHOWWHICHID, cgc_strlen(SHOWWHICHID));

provide_joke_id:
    // send LISTPROMPT and handle user input
    cgc_memset(joke_id_buf, '\0', joke_id_buf_sz);
    cgc_prompt_user(SHOWPROMPT, joke_id_buf, joke_id_buf_sz);

    // is joke_id_buf a number?

    id_type = cgc_is_numeric(joke_id_buf);
    // numeric and >= 0
    if (id_type == 0) {
        joke_id = cgc_str2uint32(joke_id_buf);
        if (joke_id == 1337) {
            cgc_send(EASTEREGG, cgc_strlen(EASTEREGG));           
        } else if (joke_id < cgc_joke_count(jokedb)) {
            cgc_send_joke(&jokedb->jokes[joke_id]);
        } else {
            cgc_send(BADIDERROR, cgc_strlen(BADIDERROR));
            goto provide_joke_id;
        }
    // not numeric
    } else if (id_type == -1 && cgc_streq(joke_id_buf, "RANDOM") == 0) {
        cgc_send_random_joke(jokedb);
    // either numeric < 0, or not numeric that is not "RANDOM"
    } else {
        cgc_send(BADIDERROR, cgc_strlen(BADIDERROR));
        goto provide_joke_id;
    }
    
    return 0;
}

int cgc_do_count(jokedb_struct *jokedb) {

    int return_buf_len = cgc_strlen(JOKECOUNT) + 40;
    char return_buf[return_buf_len];
    cgc_snprintf(return_buf, return_buf_len, JOKECOUNT, cgc_joke_count(jokedb));
    cgc_send(return_buf, cgc_strlen(return_buf));

    return 0;
}

int cgc_do_menu() {
    cgc_send(CHOICES, cgc_strlen(CHOICES));
    
    return 0;
}

int cgc_do_help() {
    cgc_send(INSULT, cgc_strlen(INSULT));
    cgc_do_menu();

    return 0;
}

int cgc_do_quit() {
    cgc_send(BYEBYE, cgc_strlen(BYEBYE));

    return 0;
}

int main(int cgc_argc, char *cgc_argv[]) {
    cgc_size_t cmd_buf_sz = 20;
    char buf[cmd_buf_sz];
    jokedb_struct jokedb;

    // load with default jokes (array of joke_struct's)
    cgc_load_default_jokes(&jokedb);

    // send INITMSG
    cgc_send(INITMSG, cgc_strlen(INITMSG));
    
    // send MENU
    cgc_do_menu();
    
    while (1) {
        // send ROOTPROMPT
        cgc_memset(buf, '\0', cmd_buf_sz);
        cgc_prompt_user(ROOTPROMPT, buf, cmd_buf_sz);

        // receive user input and check for COMMAND
        if (cgc_streq(buf, "LIST") == 0) {
            cgc_do_list(&jokedb);
        } else if (cgc_streq(buf, "ADD") == 0) {
            cgc_do_add(&jokedb);
        } else if (cgc_streq(buf, "COUNT") == 0) {
            cgc_do_count(&jokedb);
        } else if (cgc_streq(buf, "SHOW") == 0) {
            cgc_do_show(&jokedb);
        } else if (cgc_streq(buf, "HELP") == 0) {
            cgc_do_help();
        } else if (cgc_streq(buf, "QUIT") == 0) {
            cgc_do_quit();
        } else {
            cgc_do_menu();
        }
    }
}

