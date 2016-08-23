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
#include "libc.h"
#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "shell.h"
#include "malloc.h"

#define FD_TO_MAIN 5
#define FD_FROM_MAIN 8

// Password entry 
typedef struct passwd_s {
  char *username;
  char *password;
} passwd;

typedef struct host_s {
  char *hostname;
  char *username;
} host;

#define BUFSIZ 1024
#define MAX_USERS 32
#define MAX_HOSTS 32
                    
passwd userlist[MAX_USERS] = {
  "username", "password"};
host hostlist[MAX_HOSTS] = {
  "hostname", "username"};


int hostlookup(char *hostname, char *username) {
  // Check host
  for (int i=0; i< MAX_HOSTS; i++) {
    if (!strcmp(hostname, hostlist[i].hostname) && !strcmp(username, hostlist[i].username)) {
      return 1;
    }
  }
  return 0;
} 

int userlookup(char *username, char *password) {
  // Check host
  for (int i=0; i< MAX_USERS; i++) {
    if (!strcmp(username, userlist[i].username) && !strcmp(password, userlist[i].password)) {
      return 1;
    }
  }
  return 0;
} 


int ish(char *input) 
{
  char *arg = input;
  char *host = 0;
  char *password = 0;
  char *user = 0;
  // Process arguments
  host = arg;
  while (!isspace(*arg)) arg++;
  *arg++ = '\0';
  while (*arg) {
    while (isspace(*arg)) arg++;
  	if (!strncmp(arg, "+l", 2)) {
		  arg+= 2;
      if (!isspace(*arg)) goto usage;
      arg++;
      user = arg;
      while(!isspace(*arg) && *arg) arg++;
      if (isspace(*arg)) {
        *arg++ = '\0';
      }
    } else if (!strncmp(arg, "+p", 2)) {
      arg+=2;
      if (!isspace(*arg)) goto usage;
      arg++;
      password = arg;
      while(!isspace(*arg) && *arg) arg++;
      if (isspace(*arg)) {
        *arg++ = '\0';
      }
    } else if (!strncmp(arg, "+n", 2)) {
      arg+=2;
    } else if (!strncmp(arg, "+L", 2)) {
      arg+=2;
    } else if (!strncmp(arg, "+e", 2)) {
      arg+=2;
    } else if (!strncmp(arg, "+9", 2)) {
      arg+=2;
    } else if (!strncmp(arg, "+8", 2)) {
      arg+=2;
    } else {
      // non flag argument found, proceed to command processing
      break;
    }
  }

	if (host == 0) {
    goto usage;
  }

  if (user == 0) {
    goto usage;
  }

  if (password == 0) {
    goto usage;
  }

  // Check host, user, and password for correct values
  if (hostlookup(host, user) && userlookup(user, password)) {
    char *cmd = arg;
    while (*arg != '\n') arg++;
    *arg = '\0';
    runshellcommand(cmd);
  } else {
    printf("Access Denied\n");
  }

	return(0);
usage:
	printf("usage: ish host [options] [+p password] [+l username] command\n");
	return(1);
}


char *gen_random_string(int min, int max) {
    int length = random_in_range(min, max);
    char *s = calloc(length);
    for(int i=0; i<length - 2; i++) {
        s[i] = random_in_range(0x30, 0x7e);
    }
    return s;
}


// Wait for input, then execute ish
int main(void) {
    char input[512];
    int bytes_received = 0;
    fd_set fds;
    int ready_fds;
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    int ret;

    //Setup my flag page
    int *myflagpage = calloc(PAGE_SIZE);
    for (int i=0; i< PAGE_SIZE/4; i++) {
      myflagpage[i] = ((int *)FLAG_PAGE)[i] & 0xff000000;
    }

    
    // Initialize host list
    srand();
    for (int i= 1; i< MAX_USERS; i++) {
      userlist[i].username = gen_random_string(5, 32);
      userlist[i].password = gen_random_string(5, 32);
    }
    for (int i=1; i< MAX_HOSTS; i++) {
      hostlist[i].hostname = gen_random_string(5,32);
      int user = random_in_range(1, MAX_USERS - 1);
      hostlist[i].username = userlist[user].username;
    }

    // read input
    while (1) {
        FD_ZERO(&fds);
        FD_SET(FD_FROM_MAIN, &fds);
        ret = fdwait(FD_FROM_MAIN + 1, &fds, NULL, &timeout, &ready_fds);
        bytes_received = receive_until_fd(FD_FROM_MAIN, input, sizeof(input), '\n');

        bytes_received = force_newline(input, sizeof(input) - 1, bytes_received);
        if (equals(input, "terminate\n")) {
            goto EXIT;
        }
        if (bytes_received > 0) {
          
            ish(input);

            // Tell main program ish is done
            send_all_fd(FD_TO_MAIN, "\0\n", 2);       
        }
    } 

    EXIT:
    // exit
    return 0;
}

