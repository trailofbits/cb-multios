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
#include <libcgc.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "shell.h"
#include "screen.h"

environment ENV;

uint32_t ReadShellPrompt(int fd, char *buf, size_t len) {
	size_t total_len = 0;
	size_t rx_bytes;
	size_t i;
	char c;
	char t[2];
	t[1] = '\0';
	int8_t CurrCommandHistory = -1;
	char TmpBuf[MAX_CMD_LEN];
	uint32_t CursorPos = 0;
	
	bzero(TmpBuf, MAX_CMD_LEN);

	while ((receive(fd, &c, 1, &rx_bytes) == 0) && total_len < len-1) {
		if (rx_bytes == 0) {
			buf[0] = '\0';
			return(0);
		}
//		t[0] = c;
//		printf("$08x\n", t[0]);

		// backspace
		if (c == '\x7f') {
			if (CursorPos == total_len) {
				printf("\b\b\b   \b\b\b");
				total_len--;
				CursorPos--;
				continue;
			}
			for (i = CursorPos-1; i < total_len-1; i++) {
				buf[i] = buf[i+1];
			}
			total_len--;
			CursorPos--;
			EraseLine(0);
			PrintPrompt();
			buf[total_len] = '\0';
			printf("$s", buf);
			CursorLeft(total_len-CursorPos);
			continue;
		}

		// ctrl-c
		if (c == '\x03') {
			return(0);
		}

		// ctrl-e
		if (c == '\x05') {
			// move the cursor to the end
			EraseLine(0);
			PrintPrompt();
			buf[total_len] = '\0';
			printf("$s", buf);
			CursorPos = total_len;
			continue;
		}

		// ctrl-u
		if (c == '\x15') {
			EraseLine(0);
			PrintPrompt();
			total_len = 0;
			CursorPos = 0;
			continue;
		}

		// ctrl-d
		if (c == '\x04') {
			if (total_len > 0) {
				printf("\b\b  \b\b");
				continue;
			} else {
				printf("\b\b  \b\b");
				printf("exit  ");
				strcpy(buf, "exit");
				return(1);
			}
		}

		// escape codes
		if (c == '\x1b') {
			// receive the next char
			if (receive(fd, &c, 1, &rx_bytes) != 0) {
				buf[0] = '\0';
				return(0);
			}
			if (rx_bytes == 0) {
				buf[0] = '\0';
				return(0);
			}

			if (c == '\x5b') {
				// receive the next char
				if (receive(fd, &c, 1, &rx_bytes) != 0) {
					buf[0] = '\0';
					return(0);
				}
				if (rx_bytes == 0) {
					buf[0] = '\0';
					return(0);
				}

				if (c == '\x41') {
					// up arrow	
					// if there's no command history
					if (ENV.NumCommandHistory == 0) {
						EraseLine(0);
						PrintPrompt();
						buf[total_len] = '\0';
						printf("$s", buf);
						CursorPos = total_len;
						continue;
					}

					// if we're printing the first history buf,
					// save the current buf in case the user
					// arrow's back to it
					if (CurrCommandHistory == -1) {
						buf[total_len] = '\0';
						strcpy(TmpBuf, buf);
					}
					CurrCommandHistory++;
					if (CurrCommandHistory >= ENV.NumCommandHistory) {
						CurrCommandHistory = ENV.NumCommandHistory-1;
					}
					// print the next command in the history buf
					EraseLine(0);
					PrintPrompt();
					strcpy(buf, ENV.CommandHistory[CurrCommandHistory]);
					total_len = strlen(ENV.CommandHistory[CurrCommandHistory]);
					CursorPos = total_len;
					printf("$s", ENV.CommandHistory[CurrCommandHistory]);
					continue;
				} else if (c == '\x42') {
					// down arrow	
					if (CurrCommandHistory == -1) {
						// nothing to do
						EraseLine(0);
						PrintPrompt();
						buf[total_len] = '\0';
						printf("$s", buf);
						continue;
					}

					// see if we're at the first command in the history
					if (CurrCommandHistory == 0) {
						// go back to the user's original command
						EraseLine(0);
						PrintPrompt();
						strcpy(buf, TmpBuf);
						total_len = strlen(buf);
						CursorPos = total_len;
						printf("$s", buf);
						CurrCommandHistory = -1;
						continue;
					}

					// print the next command in the history
					CurrCommandHistory--;
					EraseLine(0);
					PrintPrompt();
					strcpy(buf, ENV.CommandHistory[CurrCommandHistory]);
					total_len = strlen(ENV.CommandHistory[CurrCommandHistory]);
					CursorPos = total_len;
					printf("$s", ENV.CommandHistory[CurrCommandHistory]);
					continue;

				} else if (c == '\x43') {
					// right arrow	
					if (CursorPos == total_len) {
						// nothing to do but remove the arrow control chars
						EraseLine(0);
						PrintPrompt();
						buf[total_len] = '\0';
						printf("$s", buf);
						continue;
					}

					// not at the end of the line, so move the cursor
					// right one character
					CursorPos++;
					EraseLine(0);
					PrintPrompt();
					buf[total_len] = '\0';
					printf("$s", buf);
					if (total_len != CursorPos) {
						CursorLeft(total_len-CursorPos);
					}
					continue;
				} else if (c == '\x44') {
					// left arrow	
					if (CursorPos == 0) {
						// nothing to do, re-print the line (to remove the control chars)
						EraseLine(0);
						PrintPrompt();
						buf[total_len] = '\0';
						printf("$s", buf);
						CursorLeft(total_len);
						continue;
					}
					// not at the beginning of the line, so move the cursor
					// left one character
					CursorPos--;
					EraseLine(0);
					PrintPrompt();
					buf[total_len] = '\0';
					printf("$s", buf);
					CursorLeft(total_len-CursorPos);
					continue;
				}
			}
		}

		if (c == '\r') {
			buf[CursorPos] = '\0';
			break;
		}
		if (c == '\n') {
			// receive the corresponding '\r'
			if (receive(fd, &c, 1, &rx_bytes) != 0) {
				buf[0] = '\0';
				return(0);
			}
			if (rx_bytes == 0) {
				buf[0] = '\0';
				return(0);
			}
			if (c != '\r') {
				buf[0] = '\0';
				return(0);
			}
			buf[CursorPos] = '\0';
//			EraseToEOL();
			break;
		}
		if (CursorPos == total_len) {
			buf[total_len++] = c;
			CursorPos++;
		} else {
			buf[CursorPos++] = c;
		}
		
	}
	if (rx_bytes == 0) {
		buf[0] = '\0';
		return(0);
	}
	buf[total_len] = '\0';

	return(total_len);
}

uint32_t ReadUntilNewline(int fd, char *buf, size_t len) {
	size_t total_len = 0;
	size_t rx_bytes;
	size_t i;
	char c;
	uint32_t CursorPos = 0;

	while ((receive(fd, &c, 1, &rx_bytes) == 0) && total_len < len-1) {
		if (rx_bytes == 0) {
			buf[0] = '\0';
			return(0);
		}

		// backspace
		if (c == '\x7f') {
			if (CursorPos == 0) {
				printf("\b\b  \b\b");
				continue;
			}
			printf("\b\b\b   \b\b\b");
			total_len--;
			CursorPos--;
			continue;
		}

		// ctrl-c
		if (c == '\x03') {
			return(0);
		}

		if (c == '\r') {
			buf[CursorPos] = '\0';
			break;
		}
		if (c == '\n') {
			// receive the corresponding '\r'
			if (receive(fd, &c, 1, &rx_bytes) != 0) {
				buf[0] = '\0';
				return(0);
			}
			if (rx_bytes == 0) {
				buf[0] = '\0';
				return(0);
			}
			if (c != '\r') {
				buf[0] = '\0';
				return(0);
			}
			buf[CursorPos] = '\0';
			break;
		}

		if (CursorPos == total_len) {
			buf[total_len++] = c;
			CursorPos++;
		} else {
			buf[CursorPos++] = c;
		}
		
	}
	if (rx_bytes == 0) {
		buf[0] = '\0';
		return(0);
	}
	buf[total_len] = '\0';

	return(total_len);
}
