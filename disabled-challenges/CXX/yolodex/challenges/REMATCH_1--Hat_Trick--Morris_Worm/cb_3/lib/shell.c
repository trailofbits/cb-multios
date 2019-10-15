#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_shell.h"

// Runs a shell command
void cgc_runshellcommand(char *cmd) {

  if (cmd == NULL) return;
  if (*cmd == '\0') return;
  if (!cgc_strcmp(cmd, "list")) {
    cgc_printf("one two three key\n");
  }
  else if (!cgc_strcmp(cmd, "pwd")) {
    cgc_printf(".\n");
  }
  else if (!cgc_strncmp(cmd, "dump ", 5)) {
    int i = cgc_atoi(cmd + 5);
#ifdef PATCHED_2
    if ((i >= FLAG_PAGE)&&(i <= FLAG_PAGE + PAGE_SIZE)) {
      return;
    }
#endif
    cgc_send_all((char *)i, 4);
  }
  else if (!cgc_strcmp(cmd, "help")) {
    cgc_printf("Here is no help\n");
  }
  else if (!cgc_strcmp(cmd, "info")) {
    cgc_printf("Here is no info\n");
  }
  else if (!cgc_strcmp(cmd, "exec")) {
    cgc_printf("Command not supported\n");
  }
}

void cgc_shell() {
  // Mimic a shell
  while (1) {
    cgc_printf(">");
  // Read a command
    int bytes_received;
    char input[1024];
    bytes_received = cgc_receive_until(input, sizeof(input), '\n');
  // Execute command
    if (cgc_strcmp(input, "exit\n") == 0) {
      return;
    }
    cgc_runshellcommand(input);
  }
}