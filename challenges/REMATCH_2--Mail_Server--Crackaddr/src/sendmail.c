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
#include "libcgc.h"
#include "cgc_stdio.h"
#include "cgc_libc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_ctype.h"
#include "cgc_malloc.h"
#include "cgc_shell.h"
#include "cgc_prng.h"
#include "cgc_crackaddr.h"
#include "cgc_sendmail.h"

#define FD_FROM_MAIN STDIN
#define FD_TO_MAIN 5


int cgc_debug_mode = 0;

address_book *abook;
mail_queue *root_queue;

char *cgc_gen_random_string(int min, int max) {
    int length = cgc_random_in_range(min, max);
    char *s = cgc_calloc(length);
    for(int i=0; i<length - 2; i++) {
        s[i] = cgc_random_in_range(0x2e, 0x7e);
    }
    return s;
}

address *cgc_add_random_addressbook_entry() {
    
    address *a = cgc_calloc(sizeof(address));
    a->name = cgc_gen_random_string(5, 32);
    a->home_server = cgc_gen_random_string(5, 32);
    a->mode = cgc_random_in_range(0,1);
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


void cgc_initialize_address_book() {
    abook->num_entries = 0;
    abook->root = 0;
    for (int i = 0; i < 20; i++) {
        cgc_add_random_addressbook_entry();
    }
} 

address *cgc_pick_address() {
    int i = 0;
    address *next = abook->root;
    while (next != NULL) {
        i++;
        next = next->next;
    }
    int pick = cgc_random_in_range(0, i-1);
    next = abook->root;
    while (next->next != NULL && pick > 0) {
        next = next->next;
        pick--;
    }
    return next;
}

address *cgc_lookup_name(char *name) {
    address *next = abook->root;
    while (next != NULL) {
        if (cgc_strcmp(next->name, name) == 0) {
            break;
        }
        next = next->next;
    }
    return next;
}

mail_queue *cgc_add_random_queue() {
    mail_queue *mq = cgc_calloc(sizeof(mail_queue));
    address *sender = cgc_pick_address();
    mq->name = sender->name;
    mq->root = cgc_add_random_message(mq);
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

message *cgc_add_random_message(mail_queue *mq) {
    message *m = cgc_calloc(sizeof(message));
    m->sender = cgc_pick_address();
    m->recipient = cgc_pick_address();
    m->subject = cgc_gen_random_string(5, 32);
    m->data = cgc_gen_random_string(5,256);
    m->data_length = cgc_strlen(m->data);

    if (mq->root != NULL) {
        message *next = mq->root;
        while (next->next != NULL) {
            next = next->next;
        }
        next->next = m;
    }
    return m;
}

void cgc_initialize_mail_queues() {
    // Setup mail queues
    root_queue = cgc_add_random_queue();
    for(int i = 0; i< 32; i++) {
        cgc_add_random_queue();
    }
}

void cgc_print_address_book() {
    cgc_printf("Address Book:\n");
    address *a = abook->root;
    int i = 1;
    while (a != NULL) {
        cgc_printf("$d) $s@$s [$d]\n", i, a->name, a->home_server, a->mode);
        i++;
        a = a->next;
    }
}

char *cgc_make_string(char *str) {
    if (str == NULL) {
        return NULL;
    }
    char *s = cgc_calloc(cgc_strlen(str) + 1);
    cgc_strcpy(s, str);
    return s;
}

// Creates a new message and adds to appropriate mail queue. 
void cgc_sendmail_post(char *line) {
    char output[MAX_NAME];
    char *sender, *recipient, *subject, *body;
    char *end;
    sender = cgc_strstr(line, "sender:");
    if (sender == NULL) {
        return;
    }
    sender += 7;
    
    recipient = cgc_strstr(line, "recipient:");
    if (recipient == NULL) {
        return;
    } 
    recipient += 10;
    
    
    body = cgc_strstr(line, "body:");
    if (body == NULL) {
        return;
    }
    body += 5;
    
    subject = cgc_strstr(line, "subject:");
    if (subject == NULL) {
        return;
    }
    subject += 8;
    
    end = cgc_strstr(sender, "!");
    if (end != NULL) {
        *end = '\0';
    }
    end = cgc_strstr(recipient, "!");
    if (end != NULL) {
        *end = '\0';
    }
    end = cgc_strstr(body, "!");
    if (end != NULL) {
        *end = '\0';
    }
    end = cgc_strstr(subject, "!");
    if (end != NULL) {
        *end = '\0';
    }
    message *msg = cgc_calloc(sizeof(message));
    msg->sender = cgc_lookup_name(sender);
    
    if (recipient[0] == '+') {
        
        cgc_crackaddr(recipient, output);
        cgc_printf("addr:$s\n", output);
        return;
    }
    msg->recipient = cgc_lookup_name(recipient);
    if (msg->recipient == NULL) {
        return;
    }
    if (msg->sender == NULL) {
        return;
    }
    msg->data = cgc_make_string(body);
    msg->data_length = cgc_strlen(body);
    msg->subject = cgc_make_string(subject);

 

    mail_queue *mq = cgc_locate_queue(msg->sender->name);
    if (mq == NULL) {
        mq = cgc_calloc(sizeof(mail_queue));
        mq->name = cgc_make_string(msg->sender->name);
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
    cgc_printf("Message Received\n");
}   


mail_queue *cgc_locate_queue(char *name) {
    mail_queue *mq = root_queue;
    while (mq != NULL) {
        if (cgc_strcmp(mq->name, name)==0) {
            return mq;
        }
        mq = mq->next;
    }
    return 0;
}

void cgc_list_queue(char *line) {
    char *name = line;
    // Find a queue for that username
    mail_queue *mq = cgc_locate_queue(name);
    if (mq == 0) {
        cgc_printf("Mail Queue Not Found\n");
        return;
    }
    int i = 0;
    message *msg = mq->root;
    while (msg != NULL) {
        if (msg ->sender != NULL && msg->recipient!= NULL) {
            cgc_printf("$d) From:$s To: $s SUBJECT:$s\n", i, msg->sender->name, msg->recipient->name, msg->subject);
        } else {
            cgc_printf("$d) Malformed Message\n");
        }
        i++;
        msg = msg->next;
    }
}

void cgc_list_all_queues() {
    mail_queue *mq = root_queue;
    while (mq != NULL) {
        int i = 0;
        cgc_printf("QUEUE: $s\n", mq->name);
        message *msg = mq->root;
        while (msg != NULL) {
            if (msg ->sender != NULL && msg->recipient!= NULL) {
                cgc_printf("$d) From:$s To: $s SUBJECT:$s\n", i, msg->sender->name, msg->recipient->name, msg->subject);
            } else {
                cgc_printf("$d) Malformed Message\n");
            }
            i++;
            msg = msg->next;
        }
        cgc_printf("\n");
        mq = mq->next;
    }
}

void cgc_read_message(char *line) {
    char *name = line;
    while ((*line != ' ') && (*line != '\0')) line++;
    *line++ = '\0';
    int msg_num = cgc_atoi(line);
    mail_queue *mq = cgc_locate_queue(name);
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
        cgc_printf("$d) Subject:$s Body:$s\n", i, next->subject, next->data);
    }
}
    
    

int main(int cgc_argc, char *cgc_argv[]) {
    int quit = 0;
    
    // Initialize mail server
    cgc_seed_prng(*(uint32_t *)FLAG_PAGE);
    int num_mailq = 0;
    abook = cgc_calloc(sizeof(address_book));
    cgc_initialize_address_book();
    cgc_initialize_mail_queues();

    // run a mail server
    char line[MAX_LINE+1];
    int line_size = 0;
    cgc_printf("sendmail:");
    do {
        // Read a line
        if ((line_size = cgc_receive_until(line, MAX_LINE, '\n')) <= 0) {
            break;
        }
        line[line_size] = '\0';
        // Process the command
        char *next = line;
        // Terminate first command word
        while ((*next != ' ') && (*next != '\0')) next++;
        *next++ = '\0';
        if (cgc_strcmp(line, "LIST")==0) {
            // List one mail queue
            cgc_list_queue(next);
        } else if (cgc_strcmp(line, "LISTALL")==0) {
            // List all mail queues
            cgc_list_all_queues();
        } else if (cgc_strcmp(line, "POST")==0) {
            // Post a message
            cgc_sendmail_post(next);
        } else if (cgc_strcmp(line, "READ")==0) {
            // Read a message
            cgc_read_message(next);
        } else if (cgc_strcmp(line, "ADDRESSBOOK")==0) {
            // Print address book
            cgc_print_address_book();
        } else if (cgc_strcmp(line, "QUIT")==0) {
            // Quit mail server
            break;
        } else {
            // Invalid command
            cgc_printf("Invalid Command!\n");
            quit = 1;
        }

    } while (quit == 0);

    cgc_printf("Goodbye.\n");
}
