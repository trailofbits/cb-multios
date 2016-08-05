#include <libcgc.h>
#include "libc.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "shell.h"

// Runs a shell command
void runshellcommand(char *cmd) {

  if (cmd == NULL) return;
  if (*cmd == '\0') return;
  if (!strcmp(cmd, "list")) {
    printf("one two three key\n");
  }
  else if (!strcmp(cmd, "pwd")) {
    printf(".\n");
  }
  else if (!strncmp(cmd, "dump ", 5)) {
    int i = atoi(cmd + 5);
#ifdef PATCHED_2
    if ((i >= FLAG_PAGE)&&(i <= FLAG_PAGE + PAGE_SIZE)) {
      return;
    }
#endif
    send_all((char *)i, 4);
  }
  else if (!strcmp(cmd, "help")) {
    printf("Here is no help\n");
  }
  else if (!strcmp(cmd, "info")) {
    printf("Here is no info\n");
  }
  else if (!strcmp(cmd, "exec")) {
    printf("Command not supported\n");
  }
}

void shell() {
  // Mimic a shell
  while (1) {
    printf(">");
  // Read a command
    int bytes_received;
    char input[1024];
    bytes_received = receive_until(input, sizeof(input), '\n');
  // Execute command
    if (strcmp(input, "exit\n") == 0) {
      return;
    }
    runshellcommand(input);
  }
}