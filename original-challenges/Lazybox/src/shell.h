/*

Author: Joe Rogers <joe@cromulence.com>

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
#ifndef SHELL_H
#define SHELL_H
#include <libcgc.h>
#include "stdint.h"

#define MAX_CMD_HISTORY (16)
#define MAX_CMD_LEN (256)
#define MAX_ARGS (8)
#define MAX_ARGLEN (63)
typedef struct _command {
	uint32_t argc;
	char argv[8][64];
} Command, *pCommand;

typedef struct _env {
        uint8_t NumCommandHistory;
        char CommandHistory[MAX_CMD_HISTORY][MAX_CMD_LEN];
        char User[32];
        char Group[32];
} environment;

void PrintPrompt(void);
int ParseCli(char *buf, Command *pCmd);
int32_t HandleListFiles(Command *pCmd);
int32_t HandleExit(Command *pCmd);
int32_t HandleHelp(Command *pCmd);
uint8_t HandleDump(Command *pCmd);
uint8_t HandlePrint(Command *pCmd);
void PrependCommandHistory(char *buf);

#endif
