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
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_ctype.h"
#include "cgc_stdint.h"

#include "cgc_readuntil.h"
};

#include "cgc_command.h"
#include "cgc_command_manager.h"
#include "cgc_file_manager.h"
#include "cgc_llist.h"

CommandManager *cgc_cmdMan;
FileManager *cgc_fileMan;

void call_inits(void);

void init_commands()
{
  /* Create commands */
  cgc_cmdMan = new CommandManager(cgc_fileMan);
  ListCmd *list = new ListCmd();
  CreateCmd *create = new CreateCmd();
  OpenCmd *open = new OpenCmd();
  CloseCmd *close = new CloseCmd();
  CloseAllCmd *closeAll = new CloseAllCmd();
  ReadCmd *cgc_read = new ReadCmd();
  ModifyCmd *modify = new ModifyCmd();
  DeleteCmd *del = new DeleteCmd();
  CreateDirCmd *createDir = new CreateDirCmd();
  DeleteDirCmd *deleteDir = new DeleteDirCmd();
  ChangeDirCmd *changeDir = new ChangeDirCmd();
  QuitCmd *quit = new QuitCmd();
  HelpCmd *help = new HelpCmd();

  /* Install commands */
  cgc_cmdMan->InstallCommand(list);
  cgc_cmdMan->InstallCommand(create);
  cgc_cmdMan->InstallCommand(open);
  cgc_cmdMan->InstallCommand(close);
  cgc_cmdMan->InstallCommand(closeAll);
  cgc_cmdMan->InstallCommand(cgc_read);
  cgc_cmdMan->InstallCommand(modify);
  cgc_cmdMan->InstallCommand(del);
  cgc_cmdMan->InstallCommand(createDir);
  cgc_cmdMan->InstallCommand(deleteDir);
  cgc_cmdMan->InstallCommand(changeDir);
  cgc_cmdMan->InstallCommand(quit);
  cgc_cmdMan->InstallCommand(help);
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
    while (cgc_isspace(*p)) p++;
    if (!*p) break;
    while (*p && !cgc_isspace(*p)) p++;
    (*argc)++;
  }
  if (*argc > 0)
  {
    p = s;
    argv = (char **) cgc_calloc((*argc + 1), sizeof(char *));
    while (cgc_isspace(*p)) p++;
    while (*p)
    {
      argv[i] = p;
      while (*p && !cgc_isspace(*p)) p++;
      if (!*p) break;
      *p = '\0';
      p++;
      while (*p && cgc_isspace(*p)) p++;
      i++;
    }
  }
  return argv;
}

int main(int cgc_argc, char *cgc_argv[])
{
  int argc;
  char buf[2048], **argv = 0;
  cgc_fileMan = new FileManager();

  /* init */
  
  init_commands();

  while (1)
  {
    cgc_printf("$ ");
    if (cgc_read_until(STDIN, buf, sizeof(buf), '\n') < 0)
      return -1;
    argv = parse_args(buf, &argc);
    if (argc)
    {
      if (cgc_cmdMan->ExecuteCommand(argv[0], --argc, &argv[1]) < 0)
        cgc_printf("Unknown command [%s]\n", argv[0]);
      cgc_free(argv);
    }
  }
  return 0;
}
