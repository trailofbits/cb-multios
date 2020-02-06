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
  #include "cgc_ctype.h"
  #include "cgc_readuntil.h"
};

#include "cgc_command.h"
#include "cgc_command_manager.h"

Command::Command(const char *name, const char *alias)
{
  cgc_memset(this->name, 0, sizeof(this->name));
  cgc_memset(this->alias, 0, sizeof(this->alias));

  SetName(name);
  if (alias)
    SetAlias(alias);
}

Command::~Command()
{
}

bool is_number(char* c)
{
  while (*c)
  {
    if (!cgc_isdigit(*c))
      return false;
    c++;
  }
  return true;
}

void Command::HandleResponse(int res)
{
  if (res == 0)
    return;
  switch (this->GetType())
  {
    case CT_LIST:
      /* No error code */
      break;
    case CT_CREATEDIR:
    case CT_CREATE:
      if (res == -1)
        cgc_printf("Max number of files reached\n");
      else if (res == -2)
        cgc_printf("Internal error\n");
      else if (res == -3)
        cgc_printf("File already exists\n");
      else if (res == -4)
        cgc_printf("Name too long\n");
      break;
    case CT_OPEN:
      if (res == -1)
        cgc_printf("Max number of opened files reached\n");
      else if (res == -2)
        cgc_printf("Internal error\n");
      else if (res == -3)
        cgc_printf("Not a regular file\n");
      else if (res == -4)
        cgc_printf("Already opened\n");
      else if (res == -5)
        cgc_printf("No such file\n");
      break;
    case CT_CLOSE:
      if (res == -1 || res == -2)
        cgc_printf("Invalid fileno\n");
      else if (res == -3)
        cgc_printf("Not a regular file\n");
      else if (res == 1)
        cgc_printf("Already closed\n");
      break;
    case CT_CLOSEALL:
      /* No error code */
      break;
    case CT_READ:
      if (res == -1 || res == -2)
        cgc_printf("Invalid fileno\n");
      else if (res == -10)
        cgc_printf("Not a regular file\n");
      else if (res == -20)
        cgc_printf("Internal error\n");
      else if (res == -30)
        cgc_printf("File not opened\n");
      else if (res == -40)
        cgc_printf("Empty file\n");
      else if (res == -50)
        cgc_printf("Out of range\n");
      break;
    case CT_MODIFY:
      if (res == -1 || res == -2)
        cgc_printf("Invalid fileno\n");
      else if (res == -10)
        cgc_printf("Not a regular file\n");
      else if (res == -20 || res == -40)
        cgc_printf("Internal error\n");
      else if (res == -30)
        cgc_printf("File not opened\n");
      break;
    case CT_DELETE:
      if (res == -1)
        cgc_printf("Internal error\n");
      else if (res == -2)
        cgc_printf("Not valid file\n");
      else if (res == -3)
        cgc_printf("No such file\n");
      else if (res == -4)
        cgc_printf("Not a regular file\n");
      break;
    case CT_DELETEDIR:
      if (res == -1)
        cgc_printf("Internal error\n");
      else if (res == -2 || res == -3)
        cgc_printf("Not a directory\n");
      else if (res == -4)
        cgc_printf("No such directory\n");
      break;
    case CT_CHANGEDIR:
      if (res == -1)
        cgc_printf("Internal error\n");
      else if (res == -2)
        cgc_printf("Not a directory\n");
      else if (res == -3)
        cgc_printf("No such file or directory\n");
      break;
    case CT_QUIT:
      /* No error code */
      break;
    case CT_HELP:
      break;
  }
}

int ListCmd::Execute(FileManager *fm, int argc, char** argv)
{
  /* Current Directory */
  if (argc == 0)
    fm->PrintFile(0);
  /* Single File or Directory */
  else if (argc == 1)
  {
    if (!fm->GetFile(argv[0]))
      cgc_printf("%s: No such file or directory\n", argv[0]);
    else
      fm->PrintFile(argv[0]);
  }
  /* Multiple Files and/or Directories */
  else
  {
    int i;
    for (i = 0; i < argc; ++i)
    {
      if (!fm->GetFile(argv[i]))
        cgc_printf("%s: No such file or directory\n", argv[i]);
      else
      {
        cgc_printf("%s:\n", argv[i]);
        fm->PrintFile(argv[i]);
        if (i < argc - 1)
          cgc_printf("\n");
      }
    }
  }
  return 0;
}

int CreateCmd::Execute(FileManager *fm, int argc, char** argv)
{
  if (argc == 0)
  {
    cgc_printf("No filename specified\n");
    return -1;
  }
  HandleResponse(fm->CreateFile(argv[0]));
  return 0;
}

int OpenCmd::Execute(FileManager *fm, int argc, char** argv)
{
  if (argc == 0)
  {
    cgc_printf("No filename specified\n");
    return -1;
  }
  int n = fm->OpenFile(argv[0]);
  HandleResponse(n);
  if (n >= 0)
    cgc_printf("[%s] opened (%d)\n", argv[0], n);
  return 0;
}

int CloseCmd::Execute(FileManager *fm, int argc, char** argv)
{
  if (argc == 0)
  {
    cgc_printf("No fileno specified\n");
    return -1;
  }
  if (!is_number(argv[0]))
  {
    cgc_printf("Invalid fileno\n");
    return -1;
  }
  HandleResponse(fm->CloseFile(cgc_strtoul(argv[0], 0, 10)));
  return 0;
}

int CloseAllCmd::Execute(FileManager *fm, int argc, char** argv)
{
  fm->CloseAll();
  return 0;
}

int ReadCmd::Execute(FileManager *fm, int argc, char** argv)
{
  unsigned int fileno;
  cgc_size_t pos = 0, len = 0;
  if (argc == 0)
  {
    cgc_printf("No fileno specified\n");
    return -1;
  }
  if (!is_number(argv[0]))
  {
    cgc_printf("Invalid fileno\n");
    return -1;
  }
  fileno = cgc_strtoul(argv[0], 0, 10);
  if (argc > 1)
  {
    if (!is_number(argv[1]))
    {
      cgc_printf("Invalid pos\n");
      return -1;
    }
    pos = cgc_strtoul(argv[1], 0, 10);
  }
  if (argc > 2)
  {
    if (!is_number(argv[2]))
    {
      cgc_printf("Invalid len\n");
      return -1;
    }
    len = cgc_strtoul(argv[2], 0, 10);
  }

  char *buf;
  int n = fm->ReadFile(fileno, pos, len, &buf);
  HandleResponse(n);
  if (n >= 0)
  {
    cgc_transmit(STDOUT, buf, n, &len);
    cgc_free(buf);
  }
  return 0;
}

int ModifyCmd::Execute(FileManager *fm, int argc, char** argv)
{
  int n, len;
  unsigned int fileno;
  char buf[512];
  cgc_size_t pos = 0, numBytes = 0;
  if (argc == 0)
  {
    cgc_printf("No fileno specified\n");
    return -1;
  }
  if (!is_number(argv[0]))
  {
    cgc_printf("Invalid fileno\n");
    return -1;
  }
  fileno = cgc_strtoul(argv[0], 0, 10);
  if (argc > 1)
  {
    if (!is_number(argv[1]))
    {
      cgc_printf("Invalid pos\n");
      return -1;
    }
    pos = cgc_strtoul(argv[1], 0, 10);
  }
  /* Test if writable */
  n = fm->ModifyFile(fileno, pos, 0, 0);
  HandleResponse(n);
  if (n)
    return -1;
  cgc_printf("<< Edit Mode - end with EOF >>\n");
  cgc_printf("pos: %d\n", pos);
  cgc_printf("==============================\n");
  while (1)
  {
    if ((len = cgc_read_until(STDIN, buf, sizeof(buf), '\n')) < 0)
      return -1;
    if (cgc_strcmp(buf, "EOF") == 0)
      break;
    buf[len - 1] = '\n';
    n = fm->ModifyFile(fileno, pos, buf, len);
    HandleResponse(n);
    if (n != len)
      return -1;
    pos += n;
    numBytes += n;
  }
  cgc_printf("==============================\n");
  cgc_printf("Wrote %d byte(s)\n", numBytes);
  return 0;
}

int DeleteCmd::Execute(FileManager *fm, int argc, char** argv)
{
  if (argc == 0)
  {
    cgc_printf("No file specified\n");
    return -1;
  }
  HandleResponse(fm->DeleteFile(argv[0]));
  return 0;
}

int CreateDirCmd::Execute(FileManager *fm, int argc, char** argv)
{
  if (argc == 0)
  {
    cgc_printf("No dirname specified\n");
    return -1;
  }
  HandleResponse(fm->CreateDirectory(argv[0]));
  return 0;
}

int DeleteDirCmd::Execute(FileManager *fm, int argc, char** argv)
{
  if (argc == 0)
  {
    cgc_printf("No dirname specified\n");
    return -1;
  }
  HandleResponse(fm->DeleteDirectory(argv[0]));
  return 0;
}

int ChangeDirCmd::Execute(FileManager *fm, int argc, char** argv)
{
  if (argc == 0)
    fm->ChangeDirectory(0);
  else
    HandleResponse(fm->ChangeDirectory(argv[0]));
  return 0;
}

int QuitCmd::Execute(FileManager *fm, int argc, char** argv)
{
  cgc_exit(0);
  return 0;
}

int HelpCmd::Execute(FileManager *fm, int argc, char** argv)
{
  int i, j;
  CommandManager *cm = (CommandManager *) fm; // HACKZ
  List<Command *> *commands = cm->GetCommands();
  for (i = 0; i < commands->length(); ++i)
  {
    Command *cmd = commands->get(i);
    if (argc == 0)
      cgc_printf("%s\n", cmd->Usage());
    else
    {
      for (j = 0; j < argc; ++j)
      {
        if (cgc_strcmp(argv[j], cmd->GetName()) == 0 ||
            cgc_strcmp(argv[j], cmd->GetAlias()) == 0)
        {
          cgc_printf("%s\n", cmd->Usage());
          break;
        }
      }
    }
  }
  return 0;
}
