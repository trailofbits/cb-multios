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

#include "service.h"




int send(const char *buf, const size_t size) {
    int ret;
    ret = sendall(STDOUT, buf, size);
    if (ret != 0)
        _terminate(1);

    return 0;
}

int recv(char *res_buf, size_t res_buf_size) {
    int bytes_read;
    bytes_read = recvline(STDIN, res_buf, res_buf_size);
    if (bytes_read < 0) {
        send(BADSTRERROR, strlen(BADSTRERROR));
        _terminate(2);
    }

    return 0;
}

// res_buf_size should be the number of byes to read from the user + 1 for '\0'.
int prompt_user(char* prompt_str, char* res_buf, size_t res_buf_size) {
    // send prompt
    send(prompt_str, strlen(prompt_str));

    // receive user input
    recv(res_buf, res_buf_size);
    
    return 0;
}

// transmit one random joke
int send_random_joke(jokedb_struct *jokedb) {

    // get joke count
    int count = joke_count(jokedb);
    // get random id between 0 and joke count
    uint32_t random_id = 0;
    if(rand(&random_id)) {
        _terminate(-10);
    }
    // send that joke
    send_joke(&jokedb->jokes[random_id % count]);

    return 0;
}

// transmit one joke
int send_joke(joke_struct *joke) {

    int return_buf_len = strlen(joke->joke_string) + 40;
    char return_buf[return_buf_len];
    snprintf(return_buf, return_buf_len, "~n: ~c\n", joke->joke_id, joke->joke_string);
    send(return_buf, strlen(return_buf));

    return 0;
}

// transmit all current jokes
int send_all_jokes(jokedb_struct *jokedb) {

    int count = jokedb->count;
    for (int i = 0; i < count; i++) {
        send_joke(&jokedb->jokes[i]);
    }

    return 0;
}


// handle LIST command
int do_list(jokedb_struct *jokedb) {
    send_all_jokes(jokedb);

    return 0;
}

// handle ADD command
int do_add(jokedb_struct *jokedb) {
    char joke_str[MAX_JOKE_STRING_LEN] = { 0 };

    int ret;

    // send ADDJOKE msg
    send(ADDJOKE, strlen(ADDJOKE));

    // send ADDPROMPT
    // get JOKE_STR from user
    prompt_user(ADDPROMPT, joke_str, MAX_JOKE_STRING_LEN);

    // append JOKE_STR to jokedb
    ret = insert_joke(jokedb, joke_str);
    if (ret == -1) {
        // jokedb is full
        send(JOKEDBFULL, strlen(JOKEDBFULL));
    } else if (ret <= -2) {
        // joke too long
        send(BADJOKEERROR, strlen(BADJOKEERROR));
    } else if (ret >= 0) {

        // joke is good
        // send JOKESTORED msg and joke_id to user
        int joke_id = ret;

        // the joke_id is up to 32bits, plus extra padding for \n and \0.
        int return_buf_len = strlen(JOKESTORED) + 40;
        char return_buf[return_buf_len];
        snprintf(return_buf, return_buf_len, JOKESTORED, joke_id);
        send(return_buf, strlen(return_buf));
    }

    return 0;
}

int do_show(jokedb_struct *jokedb) {

    // define buffer to store user provided 
    int joke_id_buf_sz = 11;
    char joke_id_buf[joke_id_buf_sz];
    uint32_t joke_id;
    char joke_str[MAX_JOKE_STRING_LEN] = { 0 };
    int id_type;
    
    // send SHOWWHICHID msg
    send(SHOWWHICHID, strlen(SHOWWHICHID));

provide_joke_id:
    // send LISTPROMPT and handle user input
    memset(joke_id_buf, '\0', joke_id_buf_sz);
    prompt_user(SHOWPROMPT, joke_id_buf, joke_id_buf_sz);

    // is joke_id_buf a number?

    id_type = is_numeric(joke_id_buf);
    // numeric and >= 0
    if (id_type == 0) {
        joke_id = str2uint32(joke_id_buf);
        if (joke_id == 1337) {
            send(EASTEREGG, strlen(EASTEREGG));           
        } else if (joke_id < joke_count(jokedb)) {
            send_joke(&jokedb->jokes[joke_id]);
        } else {
            send(BADIDERROR, strlen(BADIDERROR));
            goto provide_joke_id;
        }
    // not numeric
    } else if (id_type == -1 && streq(joke_id_buf, "RANDOM") == 0) {
        send_random_joke(jokedb);
    // either numeric < 0, or not numeric that is not "RANDOM"
    } else {
        send(BADIDERROR, strlen(BADIDERROR));
        goto provide_joke_id;
    }
    
    return 0;
}

int do_count(jokedb_struct *jokedb) {

    int return_buf_len = strlen(JOKECOUNT) + 40;
    char return_buf[return_buf_len];
    snprintf(return_buf, return_buf_len, JOKECOUNT, joke_count(jokedb));
    send(return_buf, strlen(return_buf));

    return 0;
}

int do_menu() {
    send(CHOICES, strlen(CHOICES));
    
    return 0;
}

int do_help() {
    send(INSULT, strlen(INSULT));
    do_menu();

    return 0;
}

int do_quit() {
    send(BYEBYE, strlen(BYEBYE));

    return 0;
}

int main(void) {
    size_t cmd_buf_sz = 20;
    char buf[cmd_buf_sz];
    jokedb_struct jokedb;

    // load with default jokes (array of joke_struct's)
    load_default_jokes(&jokedb);

    // send INITMSG
    send(INITMSG, strlen(INITMSG));
    
    // send MENU
    do_menu();
    
    while (1) {
        // send ROOTPROMPT
        memset(buf, '\0', cmd_buf_sz);
        prompt_user(ROOTPROMPT, buf, cmd_buf_sz);

        // receive user input and check for COMMAND
        if (streq(buf, "LIST") == 0) {
            do_list(&jokedb);
        } else if (streq(buf, "ADD") == 0) {
            do_add(&jokedb);
        } else if (streq(buf, "COUNT") == 0) {
            do_count(&jokedb);
        } else if (streq(buf, "SHOW") == 0) {
            do_show(&jokedb);
        } else if (streq(buf, "HELP") == 0) {
            do_help();
        } else if (streq(buf, "QUIT") == 0) {
            do_quit();
        } else {
            do_menu();
        }
    }
}

