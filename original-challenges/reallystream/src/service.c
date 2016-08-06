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
#include "service.h"
#include "actions.h"
#include "libc.h"

#define GREET "Hello and welcome to the RLEStream(TM) beta!\n\n"\
    "Use any of the following commands to interact:\n"\
    "list - List currently uploaded videos\n"\
    "play <name> <key> - Play a video\n"\
    "add <name> - Upload a video (will prompt for more data)\n"\
    "remove <name> - Delete a video\n\n"\
    "Thank you for choosing us for your archaic streaming needs!\n\n"

#define WAT "wat"

typedef struct action {
    char *name;
    void (*action)(char *req);
} action;

int main(void) {
    int i;
    char recv[1024] = {0};
    vhead = NULL;

    action alist[5] = {
                            {.name = "list", .action = list},
                            {.name = "play ", .action = play},
                            {.name = "add ", .action = add},
                            {.name = "remove ", .action = remove},
                            {.name = "quit", .action = quit}
    };
    
    SSENDL(sizeof(GREET)-1, GREET);

    while (1) {
        promptc(recv, sizeof(recv), "8=D ");

        for (i = 0; i < sizeof(alist)/sizeof(action); i++) {
            if (startswith(recv, alist[i].name)) {
                alist[i].action(recv+strlen(alist[i].name));
                break;
            }
        }

        if (i == sizeof(alist)/sizeof(action)) {
            SSENDL(sizeof(WAT)-1, WAT);
        }

    }
    return 0;
}
