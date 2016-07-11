/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

extern "C" {
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#include "readuntil.h"
};

#include "command.h"
#include "command_manager.h"
#include "file_manager.h"
#include "llist.h"

CommandManager *cmdMan;
FileManager *fileMan;

void call_inits(void);

void init_commands()
{
  /* Create commands */
  cmdMan = new CommandManager(fileMan);
  ListCmd *list = new ListCmd();
  CreateCmd *create = new CreateCmd();
  OpenCmd *open = new OpenCmd();
  CloseCmd *close = new CloseCmd();
  CloseAllCmd *closeAll = new CloseAllCmd();
  ReadCmd *read = new ReadCmd();
  ModifyCmd *modify = new ModifyCmd();
  DeleteCmd *del = new DeleteCmd();
  CreateDirCmd *createDir = new CreateDirCmd();
  DeleteDirCmd *deleteDir = new DeleteDirCmd();
  ChangeDirCmd *changeDir = new ChangeDirCmd();
  QuitCmd *quit = new QuitCmd();
  HelpCmd *help = new HelpCmd();

  /* Install commands */
  cmdMan->InstallCommand(list);
  cmdMan->InstallCommand(create);
  cmdMan->InstallCommand(open);
  cmdMan->InstallCommand(close);
  cmdMan->InstallCommand(closeAll);
  cmdMan->InstallCommand(read);
  cmdMan->InstallCommand(modify);
  cmdMan->InstallCommand(del);
  cmdMan->InstallCommand(createDir);
  cmdMan->InstallCommand(deleteDir);
  cmdMan->InstallCommand(changeDir);
  cmdMan->InstallCommand(quit);
  cmdMan->InstallCommand(help);
}

char** parse_args(char *s, int *argc)
{
  char **argv = 0, *p;
  int i = 0;
  *argc = 0;

  if (!s && *s)
    return 0;
  p = s;
  while (*p)
  {
    while (isspace(*p)) p++;
    if (!*p) break;
    while (*p && !isspace(*p)) p++;
    (*argc)++;
  }
  if (*argc > 0)
  {
    p = s;
    argv = (char **) calloc((*argc + 1), sizeof(char *));
    while (isspace(*p)) p++;
    while (*p)
    {
      argv[i] = p;
      while (*p && !isspace(*p)) p++;
      if (!*p) break;
      *p = '\0';
      p++;
      while (*p && isspace(*p)) p++;
      i++;
    }
  }
  return argv;
}

int main()
{
  int argc;
  char buf[2048], **argv = 0;
  fileMan = new FileManager();

  /* init */
  call_inits();
  init_commands();

  while (1)
  {
    printf("$ ");
    if (read_until(STDIN, buf, sizeof(buf), '\n') < 0)
      return -1;
    argv = parse_args(buf, &argc);
    if (argc)
    {
      if (cmdMan->ExecuteCommand(argv[0], --argc, &argv[1]) < 0)
        printf("Unknown command [%s]\n", argv[0]);
      free(argv);
    }
  }
  return 0;
}
