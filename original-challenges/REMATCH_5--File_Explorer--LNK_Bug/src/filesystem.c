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
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "filesystem.h"

FileNode *root;
uint16_t numFiles;
uint16_t *pNextFileID = (uint16_t *)MAGIC_PAGE;


FileNode *InitializeFileSystem()
{
  root = calloc(sizeof(FileNode));
  memcpy((char *)&root->name, &"root", 4);
  root->type = FILE_DIRECTORY;
  numFiles = 1;
  return root;
}

uint16_t NextFileID()
{
  uint16_t fileID = *pNextFileID++;
  if (pNextFileID >= (uint16_t *)(MAGIC_PAGE + 4096))
  {
    pNextFileID =  (uint16_t *)MAGIC_PAGE;
  }
  return (fileID & 0xff);
}


int CreateFile(char *name, uint8_t type, uint32_t size, char *contents, FileNode *parent)
{
  int nameLength = strlen(name);
  if (nameLength == 0)
  {
    return FS_ERROR_INVALID_INPUT;
  }
  if ((parent == NULL)||(parent->type != FILE_DIRECTORY))
  {
    parent = root;
  }
  if (GetPathDepth(parent) >= MAX_FILESYSTEM_DEPTH)
  {
    return FS_ERROR_ACCESS_DENIED;
  }
  if (type >= FILE_INVALID)
  {
    return FS_ERROR_INVALID_INPUT;
  }
  if (size > MAX_FILE_SIZE)
  {
    return FS_ERROR_INVALID_INPUT;
  }
  if (numFiles >= MAX_FILES_IN_SYSTEM)
  {
    return FS_ERROR_FS_FULL;
  }
  if (strcmp(name, "upone") == 0)
  {
    return FS_ERROR_INVALID_INPUT;
  }
  if (type == FILE_DIRECTORY)
  {
    size = 0;
  }
  FileNode *newNode = calloc(sizeof(FileNode));
  memcpy(newNode->name, name, nameLength);
  newNode->type = type;
  newNode->fileID = NextFileID();
  numFiles++;
  if ((size > 0)&&(contents != NULL))
  {
    newNode->contents = calloc(size);
    memcpy(newNode->contents, contents, size);
    newNode->size = size;
  }

  FileNode *prev = NULL;
  FileNode *last = NULL;
  prev = parent->child;
  newNode->parent = parent;
  if (prev == NULL)
  {
    // No files in directory, add this file first
    parent->child = newNode;
    return FS_SUCCESS;
  }

  while (prev != NULL)
  {
    int compare = strcmp(newNode->name, prev->name);
    if (compare == 0)
    {
      DestroyNode(newNode);
      return FS_ERROR_DUPLICATE_NAME;
    }
    if (compare < 0)
    {
      // Insert here
      if (prev->prev == NULL)
      {
        // First in directory
        newNode->next = prev;
        prev->prev = newNode;
        parent->child = newNode;
        return FS_SUCCESS;
      } else {
        newNode->next = prev;
        newNode->prev = prev->prev;
        prev->prev->next = newNode;
        newNode->next->prev = newNode;
        return FS_SUCCESS;
      }
    } else {
      // Keep looking
      last = prev;
      prev = prev->next;
    }
  }
  // Got to end of directory, insert here
  last->next = newNode;
  newNode->prev = last;
  return FS_SUCCESS;
}

void DestroyNode(FileNode *node)
{
  if (node)
  {
    numFiles--;
    DestroyNode(node->child);
    DestroyNode(node->next);
    free(node->contents);
  }
}

FileNode *FindFile(char *name, FileNode *parent)
{
  if ((parent == NULL)||(name == NULL))
  {
    return NULL;
  }
  FileNode *file = parent->child;
  while (file != NULL)
  {
    int compare = strcmp(name, file->name);
    if (compare == 0)
    {
      return file;
    }
    if (compare < 0)
    {
      break;
    }
    file = file->next;
  }
  return NULL;
}

FileNode *FindFileAbsolute(char *name)
{
  if (name == NULL)
  {
    return NULL;
  }
  char folder[65];
  char *namePtr = name;
  char *sepPtr = name;
  FileNode *cwd = root;
  while (*namePtr != '\0')
  {
    sepPtr = strchr(namePtr, '%');
    if (sepPtr == NULL)
    {
      break;
    }
    memset(folder, '\0', 65);
    memcpy(folder, namePtr, (sepPtr - namePtr));
    namePtr = sepPtr + 1;
    cwd = FindFile(folder, cwd);
    if (cwd == NULL)
    {
      return NULL;
    }
  }
  return FindFile(namePtr, cwd);
}




int DeleteFile(char *name, FileNode *parent)
{
  FileNode *file = FindFile(name, parent);
  if (file == NULL)
  {
    return FS_ERROR_FILE_NOT_FOUND;
  }
  if (file == root)
  {
    return FS_ERROR_ACCESS_DENIED;
  }
  if (parent->child == file)
  {
    parent->child = file->next;
  }
  if (file->prev)
  { 
    file->prev->next = file->next;
  }
  if (file->next != NULL)
  {
    file->next->prev = file->prev;
  }
  file->prev = NULL;
  file->next = NULL;
  DestroyNode(file);
  return FS_SUCCESS;
}

uint8_t GetFileType(FileNode *file)
{
  if (file == NULL)
  {
    return 0;
  }
  return file->type;
}

uint32_t GetFileSize(FileNode *file)
{
  if (file == NULL)
  {
    return 0;
  }
  return file->size;
}

uint32_t GetFileID(FileNode *file)
{
  if (file == NULL)
  {
    return 0;
  }
  return file->fileID;
}

char *GetFilePath(FileNode *file)
{
  if (file == NULL)
  {
    return NULL;
  }
  if (file == root)
  {
    return NULL;
  }
  int pathLength = 4 + 1;
  FileNode *parent = file->parent;
  while (parent != root)
  {
    pathLength += strlen(parent->name) + 1;
    parent = parent->parent;
  }
  char *path = calloc(pathLength + 1);
  parent = file->parent;
  char *pathPtr = path + pathLength;
  *--pathPtr = '%';
  while (parent != root)
  {
    pathPtr -= strlen(parent->name);
    memcpy(pathPtr, parent->name, strlen(parent->name));
    pathPtr--;
    *pathPtr = '%';
    parent = parent->parent;
  }
  memcpy(path, &"root", 4);
  return path;
}

int GetPathDepth(FileNode *file)
{
  int depth = 0;
  FileNode *parent = file;
  while ((parent != root)&&(parent != NULL))
  {
    depth++;
    parent = parent->parent;
  }
  return depth;
}

char *ReadFile(FileNode *file)
{
  
  char *returnData = NULL;
  if (file == NULL)
  {
    return NULL;
  }
  if (file->size > 0)
  {
    returnData = calloc(file->size + 1);
    memcpy(returnData, file->contents, file->size);
  }
  return returnData;
}

char *GetFileName(FileNode *file)
{
  return file->name;
}

FileNode *GetParent(FileNode *file)
{
  if (file == root)
  {
    return root;
  }
  return file->parent;
}


