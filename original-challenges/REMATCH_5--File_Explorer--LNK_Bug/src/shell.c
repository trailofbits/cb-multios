/*

Author: Debbie Nuttall <debbie@cromulence.com>

Copyright (c) 2016 Cromulence LLC

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
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "string.h"
#include "filesystem.h"
#include "cstring.h"
#include "osfiles.h"
#include "loader.h"
#include "shell.h"

void ListFilesRecurse(FileNode *file, int level)
{
  if (file == NULL)
  {
    return;
  }
  for (int i=0; i < level; i++)
  {
    printf("    ");
  }
  printf("$s ($d)\n", file->name,  GetFileID(file));
  ListFilesRecurse(file->child, level+1);
  ListFilesRecurse(file->next, level);
}

void ListFilesLong(FileNode *parent)
{
  FileNode *flavorFile = FindFileAbsolute("System%Special%Flavor.sl");
  ExecutableInMemory *flavorSL = LoadSharedLibrary(flavorFile);
  FileNode *file = parent->child;
  ExecutableInMemory *resourceSL = flavorSL;

  while (file != NULL)
  {
    resourceSL = flavorSL;
    int index = GetFileType(file) - FILE_TEXT;
    if (GetFileType(file) == FILE_LINK)
    {
      ExtractLinkTargetAndID((ShortcutFileHeader *)file->contents, parent,  &resourceSL, &index);
    }
    char *resource = LookupResource(resourceSL, index);
    printf("$s \t$d\t$s\n", GetFileName(file), GetFileSize(file), resource);
    file = file->next;
  }
}

void ExtractLinkTargetAndID(ShortcutFileHeader *sh, FileNode *parent, ExecutableInMemory **flavorSL, int *index)
{
  ExecutableInMemory *newFlavor = NULL;
  int newIndex = -1;

  if (sh->size > MAX_FILE_SIZE)
  {
    return;
  }
  if (sh->magic != SHORTCUT_MAGIC)
  {
    return;
  }
  
  if (strncmp(sh->targetName, "System%Special%", 15) != 0)
  {
    newIndex = -1;
  } else {
    newIndex = sh->index;
  }

  // Verify separator is not present
  char *sepPtr = strchr(sh->targetName, '+');
  if (sepPtr != NULL)
  {
    return;
  }
  // Add separator and copy
  char fileAndID[77];
  sprintf(fileAndID, "$s+$d", sh->targetName, newIndex);
#ifdef PATCHED_1
  char *pFileAndID = calloc(MAX_FILENAME + 4);
  strncpy(pFileAndID, fileAndID, MAX_FILENAME + 3);
#else
  char *pFileAndID = calloc(MAX_FILENAME + 3);
  strncpy(pFileAndID, fileAndID, MAX_FILENAME + 2);
#endif

  // Check for separator
  char *indexPtr = strchr(pFileAndID, '+');
  if (indexPtr == NULL)
  {
    return;
  }
  
  newIndex = atoi(indexPtr + 1);

  // Attempt usage of this flavor file
  if (newIndex >= 0)
  {
    newFlavor = VerifyAndLoadFlavorFile(sh->targetName, parent);
    if (newFlavor == NULL)
    {
      return;
    }

    *index = newIndex;
    *flavorSL = newFlavor;
  }
}
 

ExecutableInMemory *VerifyAndLoadFlavorFile(char *name, FileNode *parent)
{ 
  // check name fits with .listofiles added
  char listofiles[65];
  memset(listofiles, 0, 65);
  strncpy(listofiles, name, 64);
  char *sepIndex = strchr(listofiles, '_');
  if (sepIndex)
  {
    *sepIndex = 0;
  } else {
    sepIndex = listofiles + strlen(listofiles);
  }
  if (strlen(listofiles) > 64 - strlen(".listofiles"))
  {
    return NULL;
  }
  strcpy(sepIndex, ".listofiles");
  FileNode *listFile =  FindFile(listofiles, parent);

  // check file exists
  FileNode *flavor = FindFile(name, parent);
  if (flavor == NULL)
  {
    flavor = FindFileAbsolute(name);
  }
  return LoadSharedLibrary(flavor);
}


char ReceiveCommand()
{
  char cmd, delim;
  if (receive(STDIN, &cmd, 1, NULL) != 0) 
  {
    _terminate(-1);
  }
  if (receive(STDIN, &delim, 1, NULL) != 0) 
  {
    _terminate(-1);
  }
  if (delim != DELIM)
  {
    return EXIT_CMD;
  }
  return cmd;
}

int main()
{
  FileNode *cwd = InitializeFileSystem();
  int activeSession = 1;
  
  // Populate shell files and icons
  InitializeOSFiles();

  while (activeSession) {
    printf(">");
    // Receive a command
    char cmd = ReceiveCommand();
    switch(cmd)
    {
      // Process command
      case UPLOAD_A_FILE:
      {
        cString *name = ReceiveCString(64);
        uint8_t type;
        ReceiveBytes((char *)&type, 1);
        cString *contents = ReceiveCString(MAX_FILE_SIZE);
        if (CreateFile(name->string, type, contents->length, contents->string, cwd) != FS_SUCCESS)
        {
          printf("FAILED\n");
        } 
        DestroyCString(name);
        DestroyCString(contents);
        break;
      }
      case READ_A_FILE:
      {
        cString *name = ReceiveCString(64);
        FileNode *file = FindFile(name->string, cwd);
        /*
        if (GetFileType(file) == FILE_LINK)
        {
          file = FindFile(file->contents + 8);
        }*/
        if (file)
        {
          char *contents = ReadFile(file);
          printf("$s\n", contents);
          free(contents);
        }
        DestroyCString(name);
        break;
      }
      case DELETE_A_FILE:
      {
        cString *name = ReceiveCString(64);
        if ((DeleteFile(name->string, cwd)) != FS_SUCCESS)
        {
          printf("FAILED\n");
        }
        DestroyCString(name);
        break;
      }
      case LIST_FILES:
      {
        ListFilesRecurse(cwd, 0);
        break;
      }
      case LIST_FILES_LONG:
      {
        ListFilesLong(cwd);
        break;
      }
      case CREATE_DIR:
      {
        cString *name = ReceiveCString(64);
        if(CreateFile(name->string, FILE_DIRECTORY, 0, 0, cwd) != FS_SUCCESS)
        {
          printf("FAILED\n");
        }
        DestroyCString(name);
        break;
      }
      case PWD:
      {
        printf("$s$s\n", GetFilePath(cwd), GetFileName(cwd));
        break;
      }
      case CHANGE_DIR:
      {
        cString *name = ReceiveCString(64);
        if (strcmp("upone", name->string) == 0)
        {
          cwd = GetParent(cwd);
          break;
        }
        FileNode *newDir = FindFile(name->string, cwd);
        if (GetFileType(newDir) == FILE_DIRECTORY)
        {
          cwd = newDir;
        } else {
          printf("File Not Found\n");
        }
        break;
      }
      case EXIT_CMD:
        activeSession = 0;
        break;
      default:
        printf("Invalid Command\n");
    }
  }

  printf("\n");
}

