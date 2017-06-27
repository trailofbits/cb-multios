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
#include "libcgc.h"
#include "cgc_stdint.h"
#include "cgc_stdio.h"
#include "cgc_stdlib.h"
#include "cgc_malloc.h"
#include "cgc_string.h"
#include "cgc_filesystem.h"
#include "cgc_cstring.h"
#include "cgc_osfiles.h"
#include "cgc_loader.h"
#include "cgc_shell.h"

void cgc_ListFilesRecurse(FileNode *file, int level)
{
  if (file == NULL)
  {
    return;
  }
  for (int i=0; i < level; i++)
  {
    cgc_printf("    ");
  }
  cgc_printf("$s ($d)\n", file->name,  cgc_GetFileID(file));
  cgc_ListFilesRecurse(file->child, level+1);
  cgc_ListFilesRecurse(file->next, level);
}

void cgc_ListFilesLong(FileNode *parent)
{
  FileNode *flavorFile = cgc_FindFileAbsolute("System%Special%Flavor.sl");
  ExecutableInMemory *flavorSL = cgc_LoadSharedLibrary(flavorFile);
  FileNode *file = parent->child;
  ExecutableInMemory *resourceSL = flavorSL;

  while (file != NULL)
  {
    resourceSL = flavorSL;
    int index = cgc_GetFileType(file) - FILE_TEXT;
    if (cgc_GetFileType(file) == FILE_LINK)
    {
      cgc_ExtractLinkTargetAndID((ShortcutFileHeader *)file->contents, parent,  &resourceSL, &index);
    }
    char *resource = cgc_LookupResource(resourceSL, index);
    cgc_printf("$s \t$d\t$s\n", cgc_GetFileName(file), cgc_GetFileSize(file), resource);
    file = file->next;
  }
}

void cgc_ExtractLinkTargetAndID(ShortcutFileHeader *sh, FileNode *parent, ExecutableInMemory **flavorSL, int *index)
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
  
  if (cgc_strncmp(sh->targetName, "System%Special%", 15) != 0)
  {
    newIndex = -1;
  } else {
    newIndex = sh->index;
  }

  // Verify separator is not present
  char *sepPtr = cgc_strchr(sh->targetName, '+');
  if (sepPtr != NULL)
  {
    return;
  }
  // Add separator and copy
  char fileAndID[77];
  cgc_sprintf(fileAndID, "$s+$d", sh->targetName, newIndex);
#ifdef PATCHED_1
  char *pFileAndID = cgc_calloc(MAX_FILENAME + 4);
  cgc_strncpy(pFileAndID, fileAndID, MAX_FILENAME + 3);
#else
  char *pFileAndID = cgc_calloc(MAX_FILENAME + 3);
  cgc_strncpy(pFileAndID, fileAndID, MAX_FILENAME + 2);
#endif

  // Check for separator
  char *indexPtr = cgc_strchr(pFileAndID, '+');
  if (indexPtr == NULL)
  {
    return;
  }
  
  newIndex = cgc_atoi(indexPtr + 1);

  // Attempt usage of this flavor file
  if (newIndex >= 0)
  {
    newFlavor = cgc_VerifyAndLoadFlavorFile(sh->targetName, parent);
    if (newFlavor == NULL)
    {
      return;
    }

    *index = newIndex;
    *flavorSL = newFlavor;
  }
}
 

ExecutableInMemory *cgc_VerifyAndLoadFlavorFile(char *name, FileNode *parent)
{ 
  // check name fits with .listofiles added
  char listofiles[65];
  cgc_memset(listofiles, 0, 65);
  cgc_strncpy(listofiles, name, 64);
  char *sepIndex = cgc_strchr(listofiles, '_');
  if (sepIndex)
  {
    *sepIndex = 0;
  } else {
    sepIndex = listofiles + cgc_strlen(listofiles);
  }
  if (cgc_strlen(listofiles) > 64 - cgc_strlen(".listofiles"))
  {
    return NULL;
  }
  cgc_strcpy(sepIndex, ".listofiles");
  FileNode *listFile =  cgc_FindFile(listofiles, parent);

  // check file exists
  FileNode *flavor = cgc_FindFile(name, parent);
  if (flavor == NULL)
  {
    flavor = cgc_FindFileAbsolute(name);
  }
  return cgc_LoadSharedLibrary(flavor);
}


char cgc_ReceiveCommand()
{
  char cmd, delim;
  if (cgc_receive(STDIN, &cmd, 1, NULL) != 0) 
  {
    cgc__terminate(-1);
  }
  if (cgc_receive(STDIN, &delim, 1, NULL) != 0) 
  {
    cgc__terminate(-1);
  }
  if (delim != DELIM)
  {
    return EXIT_CMD;
  }
  return cmd;
}

int main(int cgc_argc, char *cgc_argv[])
{
  FileNode *cwd = cgc_InitializeFileSystem();
  int activeSession = 1;
  
  // Populate shell files and icons
  cgc_InitializeOSFiles();

  while (activeSession) {
    cgc_printf(">");
    // Receive a command
    char cmd = cgc_ReceiveCommand();
    switch(cmd)
    {
      // Process command
      case UPLOAD_A_FILE:
      {
        cString *name = cgc_ReceiveCString(64);
        uint8_t type;
        cgc_ReceiveBytes((char *)&type, 1);
        cString *contents = cgc_ReceiveCString(MAX_FILE_SIZE);
        if (cgc_CreateFile(name->string, type, contents->length, contents->string, cwd) != FS_SUCCESS)
        {
          cgc_printf("FAILED\n");
        } 
        cgc_DestroyCString(name);
        cgc_DestroyCString(contents);
        break;
      }
      case READ_A_FILE:
      {
        cString *name = cgc_ReceiveCString(64);
        FileNode *file = cgc_FindFile(name->string, cwd);
        /*
        if (GetFileType(file) == FILE_LINK)
        {
          file = FindFile(file->contents + 8);
        }*/
        if (file)
        {
          char *contents = cgc_ReadFile(file);
          cgc_printf("$s\n", contents);
          cgc_free(contents);
        }
        cgc_DestroyCString(name);
        break;
      }
      case DELETE_A_FILE:
      {
        cString *name = cgc_ReceiveCString(64);
        if ((cgc_DeleteFile(name->string, cwd)) != FS_SUCCESS)
        {
          cgc_printf("FAILED\n");
        }
        cgc_DestroyCString(name);
        break;
      }
      case LIST_FILES:
      {
        cgc_ListFilesRecurse(cwd, 0);
        break;
      }
      case LIST_FILES_LONG:
      {
        cgc_ListFilesLong(cwd);
        break;
      }
      case CREATE_DIR:
      {
        cString *name = cgc_ReceiveCString(64);
        if(cgc_CreateFile(name->string, FILE_DIRECTORY, 0, 0, cwd) != FS_SUCCESS)
        {
          cgc_printf("FAILED\n");
        }
        cgc_DestroyCString(name);
        break;
      }
      case PWD:
      {
        cgc_printf("$s$s\n", cgc_GetFilePath(cwd), cgc_GetFileName(cwd));
        break;
      }
      case CHANGE_DIR:
      {
        cString *name = cgc_ReceiveCString(64);
        if (cgc_strcmp("upone", name->string) == 0)
        {
          cwd = cgc_GetParent(cwd);
          break;
        }
        FileNode *newDir = cgc_FindFile(name->string, cwd);
        if (cgc_GetFileType(newDir) == FILE_DIRECTORY)
        {
          cwd = newDir;
        } else {
          cgc_printf("File Not Found\n");
        }
        break;
      }
      case EXIT_CMD:
        activeSession = 0;
        break;
      default:
        cgc_printf("Invalid Command\n");
    }
  }

  cgc_printf("\n");
}

