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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_stdint.h"
#include "cgc_shell.h"
#include "cgc_screen.h"

environment cgc_ENV;

uint32_t cgc_ReadShellPrompt(int fd, char *buf, cgc_size_t len) {
	cgc_size_t total_len = 0;
	cgc_size_t rx_bytes;
	cgc_size_t i;
	char c;
	char t[2];
	t[1] = '\0';
	int8_t CurrCommandHistory = -1;
	char TmpBuf[MAX_CMD_LEN];
	uint32_t CursorPos = 0;
	
	cgc_bzero(TmpBuf, MAX_CMD_LEN);

	while ((cgc_receive(fd, &c, 1, &rx_bytes) == 0) && total_len < len-1) {
		if (rx_bytes == 0) {
			buf[0] = '\0';
			return(0);
		}
//		t[0] = c;
//		cgc_printf("$08x\n", t[0]);

		// backspace
		if (c == '\x7f') {
			if (CursorPos == total_len) {
				cgc_printf("\b\b\b   \b\b\b");
				total_len--;
				CursorPos--;
				continue;
			}
			for (i = CursorPos-1; i < total_len-1; i++) {
				buf[i] = buf[i+1];
			}
			total_len--;
			CursorPos--;
			cgc_EraseLine(0);
			cgc_PrintPrompt();
			buf[total_len] = '\0';
			cgc_printf("$s", buf);
			cgc_CursorLeft(total_len-CursorPos);
			continue;
		}

		// ctrl-c
		if (c == '\x03') {
			return(0);
		}

		// ctrl-e
		if (c == '\x05') {
			// move the cursor to the end
			cgc_EraseLine(0);
			cgc_PrintPrompt();
			buf[total_len] = '\0';
			cgc_printf("$s", buf);
			CursorPos = total_len;
			continue;
		}

		// ctrl-u
		if (c == '\x15') {
			cgc_EraseLine(0);
			cgc_PrintPrompt();
			total_len = 0;
			CursorPos = 0;
			continue;
		}

		// ctrl-d
		if (c == '\x04') {
			if (total_len > 0) {
				cgc_printf("\b\b  \b\b");
				continue;
			} else {
				cgc_printf("\b\b  \b\b");
				cgc_printf("exit  ");
				cgc_strcpy(buf, "exit");
				return(1);
			}
		}

		// escape codes
		if (c == '\x1b') {
			// receive the next char
			if (cgc_receive(fd, &c, 1, &rx_bytes) != 0) {
				buf[0] = '\0';
				return(0);
			}
			if (rx_bytes == 0) {
				buf[0] = '\0';
				return(0);
			}

			if (c == '\x5b') {
				// receive the next char
				if (cgc_receive(fd, &c, 1, &rx_bytes) != 0) {
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
					if (cgc_ENV.NumCommandHistory == 0) {
						cgc_EraseLine(0);
						cgc_PrintPrompt();
						buf[total_len] = '\0';
						cgc_printf("$s", buf);
						CursorPos = total_len;
						continue;
					}

					// if we're printing the first history buf,
					// save the current buf in case the user
					// arrow's back to it
					if (CurrCommandHistory == -1) {
						buf[total_len] = '\0';
						cgc_strcpy(TmpBuf, buf);
					}
					CurrCommandHistory++;
					if (CurrCommandHistory >= cgc_ENV.NumCommandHistory) {
						CurrCommandHistory = cgc_ENV.NumCommandHistory-1;
					}
					// print the next command in the history buf
					cgc_EraseLine(0);
					cgc_PrintPrompt();
					cgc_strcpy(buf, cgc_ENV.CommandHistory[CurrCommandHistory]);
					total_len = cgc_strlen(cgc_ENV.CommandHistory[CurrCommandHistory]);
					CursorPos = total_len;
					cgc_printf("$s", cgc_ENV.CommandHistory[CurrCommandHistory]);
					continue;
				} else if (c == '\x42') {
					// down arrow	
					if (CurrCommandHistory == -1) {
						// nothing to do
						cgc_EraseLine(0);
						cgc_PrintPrompt();
						buf[total_len] = '\0';
						cgc_printf("$s", buf);
						continue;
					}

					// see if we're at the first command in the history
					if (CurrCommandHistory == 0) {
						// go back to the user's original command
						cgc_EraseLine(0);
						cgc_PrintPrompt();
						cgc_strcpy(buf, TmpBuf);
						total_len = cgc_strlen(buf);
						CursorPos = total_len;
						cgc_printf("$s", buf);
						CurrCommandHistory = -1;
						continue;
					}

					// print the next command in the history
					CurrCommandHistory--;
					cgc_EraseLine(0);
					cgc_PrintPrompt();
					cgc_strcpy(buf, cgc_ENV.CommandHistory[CurrCommandHistory]);
					total_len = cgc_strlen(cgc_ENV.CommandHistory[CurrCommandHistory]);
					CursorPos = total_len;
					cgc_printf("$s", cgc_ENV.CommandHistory[CurrCommandHistory]);
					continue;

				} else if (c == '\x43') {
					// right arrow	
					if (CursorPos == total_len) {
						// nothing to do but remove the arrow control chars
						cgc_EraseLine(0);
						cgc_PrintPrompt();
						buf[total_len] = '\0';
						cgc_printf("$s", buf);
						continue;
					}

					// not at the end of the line, so move the cursor
					// right one character
					CursorPos++;
					cgc_EraseLine(0);
					cgc_PrintPrompt();
					buf[total_len] = '\0';
					cgc_printf("$s", buf);
					if (total_len != CursorPos) {
						cgc_CursorLeft(total_len-CursorPos);
					}
					continue;
				} else if (c == '\x44') {
					// left arrow	
					if (CursorPos == 0) {
						// nothing to do, re-print the line (to remove the control chars)
						cgc_EraseLine(0);
						cgc_PrintPrompt();
						buf[total_len] = '\0';
						cgc_printf("$s", buf);
						cgc_CursorLeft(total_len);
						continue;
					}
					// not at the beginning of the line, so move the cursor
					// left one character
					CursorPos--;
					cgc_EraseLine(0);
					cgc_PrintPrompt();
					buf[total_len] = '\0';
					cgc_printf("$s", buf);
					cgc_CursorLeft(total_len-CursorPos);
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
			if (cgc_receive(fd, &c, 1, &rx_bytes) != 0) {
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

uint32_t cgc_ReadUntilNewline(int fd, char *buf, cgc_size_t len) {
	cgc_size_t total_len = 0;
	cgc_size_t rx_bytes;
	cgc_size_t i;
	char c;
	uint32_t CursorPos = 0;

	while ((cgc_receive(fd, &c, 1, &rx_bytes) == 0) && total_len < len-1) {
		if (rx_bytes == 0) {
			buf[0] = '\0';
			return(0);
		}

		// backspace
		if (c == '\x7f') {
			if (CursorPos == 0) {
				cgc_printf("\b\b  \b\b");
				continue;
			}
			cgc_printf("\b\b\b   \b\b\b");
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
			if (cgc_receive(fd, &c, 1, &rx_bytes) != 0) {
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
