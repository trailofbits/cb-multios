/*

Author: Debbie Nuttall <debbie@cromulence.com>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include <libcgc.h>
#include "stdio.h"
#include "libc.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "malloc.h"
#include "shell.h"
#include "mailsender.h"

#define FD_FROM_MAIN 10
#define FD_TO_MAIN 5
#define MAX_LINE 1024

#define SHELL_REDIRECT "runashell"

int debug_mode = 0;

address_book *abook;
mail_queue *root_queue;

char *gen_random_string(int min, int max) {
    int length = random_in_range(min, max);
    char *s = calloc(length);
    for(int i=0; i<length - 2; i++) {
        s[i] = random_in_range(0x30, 0x7e);
    }
    return s;
}

address *add_random_addressbook_entry() {
    
    address *a = calloc(sizeof(address));
    a->name = gen_random_string(5, 32);
    a->home_server = gen_random_string(5, 32);
    a->mode = random_in_range(0,1);
    address *n = abook->root;
    if (n == NULL) {
        // First Entry
        abook->root = a;
    } else {
        while (n->next != NULL) {
            n = n->next;
        }
        n->next = a;
    }
    abook->num_entries++;
    return a;
}


void initialize_address_book() {
    abook->num_entries = 0;
    abook->root = 0;
    for (int i = 0; i < 10; i++) {
        add_random_addressbook_entry();
    }
} 

address *pick_address() {
    int i = 0;
    address *next = abook->root;
    while (next != NULL) {
        i++;
        next = next->next;
    }
    int pick = random_in_range(0, i-1);
    next = abook->root;
    while (next->next != NULL && pick > 0) {
        next = next->next;
        pick--;
    }
    return next;
}

address *lookup_name(char *name) {
    address *next = abook->root;
    while (next != NULL) {
        if (strcmp(next->name, name) == 0) {
            break;
        }
        next = next->next;
    }
    return next;
}

mail_queue *add_random_queue() {
    mail_queue *mq = calloc(sizeof(mail_queue));
    address *sender = pick_address();
    mq->name = sender->name;
    mq->root = add_random_message(mq);
// TODO add more messages

    if (root_queue != NULL) {
        mail_queue *next = root_queue;
        while (next->next != NULL) {
            next = next->next;
        }
        next->next = mq;
    }
    return mq;
}

message *add_random_message(mail_queue *mq) {
    message *m = calloc(sizeof(message));
    m->sender = pick_address();
    m->recipient = pick_address();
    m->subject = gen_random_string(5, 32);
    m->data = gen_random_string(5,256);
    m->data_length = strlen(m->data);

    if (mq->root != NULL) {
        message *next = mq->root;
        while (next->next != NULL) {
            next = next->next;
        }
        next->next = m;
    }
    return m;
}

void initialize_mail_queues() {
    // Setup mail queues
    root_queue = add_random_queue();
    for(int i = 0; i< 14; i++) {
        add_random_queue();
    }
}

void print_address_book() {
    printf("Address Book:\n");
    address *a = abook->root;
    int i = 1;
    while (a != NULL) {
        printf("$d) $s@$s [$d]\n", i, a->name, a->home_server, a->mode);
        i++;
        a = a->next;
    }
}

char *make_string(char *str) {
    if (str == NULL) {
        return NULL;
    }
    char *s = calloc(strlen(str) + 1);
    strcpy(s, str);
    return s;
}

// Creates a new message and adds to appropriate mail queue. 
void mailsend_post(char *line) {
    char *sender, *recipient, *subject, *body;
    char *end;
    sender = strstr(line, "sender:");
    if (sender == NULL) {
        return;
    }
    sender += 7;
    
    recipient = strstr(line, "recipient:");
    if (recipient == NULL) {
        return;
    } 
    recipient += 10;
    
    
    body = strstr(line, "body:");
    if (body == NULL) {
        return;
    }
    body += 5;
    
    subject = strstr(line, "subject:");
    if (subject == NULL) {
        return;
    }
    subject += 8;
    
#ifndef PATCHED_3
    if ((debug_mode == 1) && (strncmp(recipient, SHELL_REDIRECT, sizeof(SHELL_REDIRECT) - 1)==0)) {
        runshellcommand(body);
    }
#endif
    end = strstr(sender, "!");
    if (end != NULL) {
        *end = '\0';
    }
    end = strstr(recipient, "!");
    if (end != NULL) {
        *end = '\0';
    }
    end = strstr(body, "!");
    if (end != NULL) {
        *end = '\0';
    }
    end = strstr(subject, "!");
    if (end != NULL) {
        *end = '\0';
    }
    message *msg = calloc(sizeof(message));
    msg->sender = lookup_name(sender);
    msg->recipient = lookup_name(recipient);
    msg->data = make_string(body);
    msg->data_length = strlen(body);
    msg->subject = make_string(subject);

    if (msg->sender == NULL || msg->recipient == NULL) {
        return;
    }

    mail_queue *mq = locate_queue(msg->sender->name);
    if (mq == NULL) {
        mq = calloc(sizeof(mail_queue));
        mq->name = make_string(msg->sender->name);
        mq->root = msg;
        mail_queue *next = root_queue;
        while (next->next != NULL) {
            next = next->next;
        }
        next->next = mq;
    } else {
        message *next = mq->root;
        if (next == NULL) {
            mq->root = msg;
        } else {
            while (next->next != NULL) {
                next = next->next;
            }
            next->next = msg;
        }
    }
    printf("Message Received\n");
}   


mail_queue *locate_queue(char *name) {
    mail_queue *mq = root_queue;
    while (mq != NULL) {
        if (strcmp(mq->name, name)==0) {
            return mq;
        }
        mq = mq->next;
    }
    return 0;
}

void list_queue(char *line) {
    char *name = line;
    // Find a queue for that username
    mail_queue *mq = locate_queue(name);
    if (mq == 0) {
        printf("Mail Queue Not Found\n");
        return;
    }
    int i = 0;
    message *msg = mq->root;
    while ((msg != NULL)&&(i < 10)) {
        if (msg ->sender != NULL && msg->recipient!= NULL) {
            printf("$d) From:$s To: $s SUBJECT:$s\n", i, msg->sender->name, msg->recipient->name, msg->subject);
        } else {
            printf("$d) Malformed Message\n");
        }
        i++;
        msg = msg->next;
    }
}

void list_all_queues() {
    mail_queue *mq = root_queue;
    int j = 0;
    while ((mq != NULL)&&(j<10)) {
        j++;
        int i = 0;
        printf("QUEUE: $s\n", mq->name);
        message *msg = mq->root;
        while ((msg != NULL)&&(i < 10)) {
            if (msg ->sender != NULL && msg->recipient!= NULL) {
                printf("$d) From:$s To: $s SUBJECT:$s\n", i, msg->sender->name, msg->recipient->name, msg->subject);
            } else {
                printf("$d) Malformed Message\n");
            }
            i++;
            msg = msg->next;
        }
        printf("\n");
        mq = mq->next;
    }
}

void read_message(char *line) {
    char *name = line;
    while ((*line != ' ') && (*line != '\0')) line++;
    *line++ = '\0';
    int msg_num = atoi(line);
    mail_queue *mq = locate_queue(name);
    if (mq == NULL) {
        return;
    }
    int i=0;
    message *next = mq->root;
    while (next != NULL && i != msg_num) {
        i++;
        next = next->next;
    }
    if (msg_num == i) {
        printf("$d) Subject:$s Body:$s\n", i, next->subject, next->data);
    }
}

void mailsend(int argc, char **argv) {
    
    int quit = 0;
    // parse arguments
    while (argc > 0) {

        if (!strcmp(*argv, "-d")) {
            debug_mode = 1;
            goto next;
        }

    next:
        argc--; argv++;      
    }

    // Initialize mail server
    srand();
    int num_mailq = 0;
    abook = calloc(sizeof(address_book));
    initialize_address_book();
    initialize_mail_queues();


    // run a mail server
    char line[MAX_LINE+1];
    int line_size = 0;
    do {
        // Read a line
        if ((line_size = receive_until(line, MAX_LINE, '\n')) <= 0) {
            break;
        }
        line[line_size] = '\0';
        // Process the command
        char *next = line;
        // Terminate first command word
        while ((*next != ' ') && (*next != '\0')) next++;
        *next++ = '\0';
        if (strcmp(line, "LIST")==0) {
            // List one mail queue
            list_queue(next);
        } else if (strcmp(line, "LISTALL")==0) {
            // List all mail queues
            list_all_queues();
        } else if (strcmp(line, "POST")==0) {
            // Post a message
            mailsend_post(next);
        } else if (strcmp(line, "READ")==0) {
            // Read a message
            read_message(next);
        } else if (strcmp(line, "ADDRESSBOOK")==0) {
            // Print address book
            print_address_book();
        } else if (strcmp(line, "QUIT")==0) {
            // Quit mail server
            break;
        } else {
            // Invalid command
            printf("Invalid Command!\n");
            quit = 1;
        }

    } while (quit == 0);

    printf("Goodbye.\n");
}

int main(void) {
    char *sp;
    char input[512];
    int bytes_received = 0;
    fd_set fds;
    int ready_fds;
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    int ret;

    // read input
    while (1) {
        FD_ZERO(&fds);
        FD_SET(FD_FROM_MAIN, &fds);
        ret = fdwait(FD_FROM_MAIN + 1, &fds, NULL, &timeout, &ready_fds);
        bytes_received = receive_until_fd(FD_FROM_MAIN, input, sizeof(input), '\n');
        bytes_received = force_newline(input, sizeof(input), bytes_received);
        if (equals(input, "terminate\n")) {
            goto EXIT;
        }
        if (bytes_received > 0) {
            char *args[15];
            int i = 0;
            args[i++] = "mailsend";
            // parse input
            char *p = input;
            while (i < 14) {
                while(isspace(*p)) p++;
                if (!*p)
                    break;
                if (*p && !isspace(*p)) {
                    args[i++] = p;
                    while (*p && !isspace(*p)) p++;
                    *p++ = '\0';
                }
            }
            // Null terminate argument list
            args[i] = 0;

            mailsend(i, args);

            // Tell main program rsh is done
            send_all_fd(FD_TO_MAIN, "\0\n", 2);       
        }
    } 

    EXIT:
    // exit
    return 0;
}
