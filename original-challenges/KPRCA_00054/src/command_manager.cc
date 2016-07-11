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

#include "command_manager.h"

CommandManager::CommandManager(FileManager *fm)
{
  this->fm = fm;
  commands = new List<Command *>(0);
}

CommandManager::~CommandManager()
{
}

List<Command *>* CommandManager::GetCommands()
{
  return commands;
}

void CommandManager::InstallCommand(Command *cmd)
{
  commands->add(cmd);
}

void CommandManager::UninstallCommand(const char* name)
{
  int i;
  for (i = 0; i < commands->length(); ++i)
  {
    Command *cmd = commands->get(i);
    if (strcmp(cmd->GetName(), name) == 0)
    {
      commands->remove(cmd);
      delete cmd;
      return;
    }
  }
}

int CommandManager::ExecuteCommand(const char* name, int argc, char** argv)
{
  int i;
  for (i = 0; i < commands->length(); ++i)
  {
    Command *cmd = commands->get(i);
    if (strcmp(cmd->GetName(), name) == 0 || strcmp(cmd->GetAlias(), name) == 0)
    {
      if (cmd->GetType() == Command::CT_HELP)
        cmd->Execute((FileManager *) this, argc, argv); 	// HACKZ
      else
        cmd->Execute(fm, argc, argv);
      return 0;
    }
  }
  return -1;
}

