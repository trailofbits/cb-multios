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

#ifndef COMMAND_H
#define COMMAND_H

extern "C" {
  #include <stdlib.h>
  #include <string.h>
};

#include "file_manager.h"

class Command
{
  public:
    enum CmdType { CT_LIST, CT_CREATE, CT_OPEN, CT_CLOSE,
                   CT_CLOSEALL, CT_READ, CT_MODIFY, CT_DELETE,
                   CT_CREATEDIR, CT_DELETEDIR, CT_CHANGEDIR,
                   CT_QUIT, CT_HELP };
  protected:
    char name[256];
    char alias[256];

  public:
    Command(const char *name, const char *alias);
    virtual ~Command() = 0;

    friend bool operator== (Command &cmd1, Command &cmd2)
    {
      return (strcmp(cmd1.name, cmd2.name) == 0);
    }
    friend bool operator!= (Command &cmd1, Command &cmd2)
    {
      return !(cmd1 == cmd2);
    }

    virtual const char* Usage() = 0;
    virtual int Execute(FileManager* fm, int argc, char** argv) = 0;
    virtual CmdType GetType() = 0;

    void SetName(const char* name)
    {
      /* Assumes the length of the strings are validated */
      strcpy(this->name, name);
    }
    void SetAlias(const char* alias)
    {
      /* Assumes the length of the strings are validated */
      strcpy(this->alias, alias);
    }
    const char* GetName() { return name; }
    const char* GetAlias() { return alias; }
    
    void HandleResponse(int res);
};

class ListCmd: public Command
{
  public:
    ~ListCmd() {};
    ListCmd() : Command("list", "ls") {}

    const char* Usage()
    {
      return "list [file ..]\n - Lists files and directories.";
    }

    int Execute(FileManager *fm, int argc, char** argv);
    CmdType GetType() { return CT_LIST; }
};

class CreateCmd: public Command
{
  public:
    ~CreateCmd() {};
    CreateCmd() : Command("create", "new") {}

    const char* Usage()
    {
      return "create <filename>\n - Creates a file.";
    }

    int Execute(FileManager *fm, int argc, char** argv);
    CmdType GetType() { return CT_CREATE; }
};

class OpenCmd: public Command
{
  public:
    ~OpenCmd() {};
    OpenCmd() : Command("open", 0) {}

    const char* Usage()
    {
      return "open <filename>\n - Opens a file.";
    }

    int Execute(FileManager *fm, int argc, char** argv);
    CmdType GetType() { return CT_OPEN; }
};

class CloseCmd: public Command
{
  public:
    ~CloseCmd() {};
    CloseCmd() : Command("close", 0) {}

    const char* Usage()
    {
      return "close <fileno>\n - Closes an open file.";
    }

    int Execute(FileManager *fm, int argc, char** argv);
    CmdType GetType() { return CT_CLOSE; }
};

class CloseAllCmd: public Command
{
  public:
    ~CloseAllCmd() {};
    CloseAllCmd() : Command("close_all", 0) {}

    const char* Usage()
    {
      return "close_all\n - Closes all open files.";
    }

    int Execute(FileManager *fm, int argc, char** argv);
    CmdType GetType() { return CT_CLOSEALL; }
};

class ReadCmd: public Command
{
  public:
    ~ReadCmd() {};
    ReadCmd() : Command("read", "cat") {}

    const char* Usage()
    {
      return "read <fileno> [pos] [len]\n - Reads a file.";
    }

    int Execute(FileManager *fm, int argc, char** argv);
    CmdType GetType() { return CT_READ; }
};

class ModifyCmd: public Command
{
  public:
    ~ModifyCmd() {};
    ModifyCmd() : Command("modify", "write") {}

    const char* Usage()
    {
      return "modify <fileno> [pos]\n - Modifies a file.";
    }

    int Execute(FileManager *fm, int argc, char** argv);
    CmdType GetType() { return CT_MODIFY; }
};

class DeleteCmd: public Command
{
  public:
    ~DeleteCmd() {};
    DeleteCmd() : Command("delete", "rm") {}

    const char* Usage()
    {
      return "delete <filename>\n - Deletes a file.";
    }

    int Execute(FileManager *fm, int argc, char** argv);
    CmdType GetType() { return CT_DELETE; }
};

class CreateDirCmd: public Command
{
  public:
    ~CreateDirCmd() {};
    CreateDirCmd() : Command("mkdir", 0) {}

    const char* Usage()
    {
      return "mkdir <dirname>\n - Creates a directory.";
    }

    int Execute(FileManager *fm, int argc, char** argv);
    CmdType GetType() { return CT_CREATEDIR; }
};

class DeleteDirCmd: public Command
{
  public:
    ~DeleteDirCmd() {};
    DeleteDirCmd() : Command("rmdir", 0) {}

    const char* Usage()
    {
      return "rmdir <dirname>\n - Deletes a directory.";
    }

    int Execute(FileManager *fm, int argc, char** argv);
    CmdType GetType() { return CT_DELETEDIR; }
};

class ChangeDirCmd: public Command
{
  public:
    ~ChangeDirCmd() {};
    ChangeDirCmd() : Command("chdir", "cd") {}

    const char* Usage()
    {
      return "chdir <dirname>\n - Changes the working directory.";
    }

    int Execute(FileManager *fm, int argc, char** argv);
    CmdType GetType() { return CT_CHANGEDIR; }
};

class QuitCmd: public Command
{
  public:
    ~QuitCmd() {};
    QuitCmd() : Command("quit", "exit") {}

    const char* Usage()
    {
      return "quit\n - Quits the program.";
    }

    int Execute(FileManager *fm, int argc, char** argv);
    CmdType GetType() { return CT_QUIT; }
};

class HelpCmd: public Command
{
  public:
    ~HelpCmd() {};
    HelpCmd() : Command("help", "?") {}

    const char* Usage()
    {
      return "help [command]\n - Displays the help message.";
    }

    int Execute(FileManager *fm, int argc, char** argv);
    CmdType GetType() { return CT_HELP; }
};

#endif
