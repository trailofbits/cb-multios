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
#include "string.h"
#include "stdlib.h"
#include "malloc.h"
#include "stdio.h"
#include "fs.h"

fs_tree allTrees[MAX_TREES];
char serviceTypes[MAX_SERVICE_TYPES][MAX_SERVICE_NAME];

void InitializeFileSystem()
{
  // Create Service Types
  for (int i=0; i< MAX_SERVICE_TYPES; i++)
  {
    populate_random_string(serviceTypes[i], random_in_range(MAX_SERVICE_NAME/2, MAX_SERVICE_NAME));
  }

  int treeNameLen = random_in_range(MAX_TREENAME_LEN / 2, MAX_TREENAME_LEN);
  for (int i=0; i < MAX_TREES - 1; i++)
  {
    fs_tree *tree = &allTrees[i];
    tree->treeID = rand();
    populate_random_string(tree->treeName, treeNameLen - i);
    strcpy(tree->serviceType, serviceTypes[random_in_range(0, MAX_SERVICE_TYPES - 1)]);
    int numFiles = random_in_range(1, MAX_FILES_PER_TREE);
    int fileIndex = 0;
    int fileNameLen = random_in_range(MAX_FILENAME_LEN/2, MAX_FILENAME_LEN);
    while (numFiles > 0)
    {
      char filename[MAX_FILENAME_LEN];
      populate_random_string(filename, fileNameLen - numFiles);
      fs_file *file = CreateFile(tree, (uint8_t *)filename, 0, FS_MODE_CREATE);
      int length = random_in_range(10, MAX_FILESIZE);
      uint8_t *buffer = calloc(length);
      populate_random_string((char *)buffer, length);
      WriteFile(file, buffer, 0, length);
      CloseFile(file);
      free(buffer);
      tree->files[fileIndex++] = file;
      numFiles--;
    }
  }

  fs_tree *lastTree = &allTrees[MAX_TREES - 1];
  lastTree->treeID = rand();
  strcpy(lastTree->treeName, "SOMETREE");
  strcpy(lastTree->serviceType, "EYEPSEE");   
  fs_file *file = calloc(sizeof(fs_file));
  strcpy(file->filename, "NETSTUFF");
  file->fileID = rand() & 0xffff;
  lastTree->files[0] = file;
  return;

}

fs_file *FindFileByName(fs_tree *tree, uint8_t *filename)
{
  for (int i=0; i< MAX_FILES_PER_TREE; i++)
  {
    fs_file *file = tree->files[i];
    if (file != NULL)
    {
     if (strcmp(file->filename, (char *)filename) == 0)
      {
        return file;
      }
    }
  }
  return NULL;
}

fs_file *CreateFile(fs_tree *tree, uint8_t *filename, uint32_t userID, uint32_t mode)
{
  fs_file *file = FindFileByName(tree, filename);
  if (file == NULL)
  {
    if (mode != FS_MODE_CREATE)
    {
      // File doesn't exist
      return NULL;
    }
    // Create new file
    for (int i=0; i < MAX_FILES_PER_TREE; i++)
    {
      if (tree->files[i] == NULL)
      {
        // Create new file in open slot
        fs_file *newfile = calloc(sizeof(fs_file));
        newfile->fileID = rand() & 0xffff;
        int len = strlen((char *)filename);
        if (len > MAX_FILENAME_LEN)
        {
          len = MAX_FILENAME_LEN;
        }
        strncpy(newfile->filename, (char *)filename, MAX_FILENAME_LEN);
        newfile->isOpen = 1;
        tree->files[i] = newfile;
        return newfile;
      }
    }
    // No open slots
    return NULL;
  }
  
  if (file->isOpen == 1)
  {
    // File already open
    return NULL;
  }
  file->isOpen = 1;
  return file;
}

void CloseFile(fs_file *file)
{
  if (file != NULL)
  {
    file->isOpen = 0;
  }
}

int ReadFile(uint8_t *dest, fs_file *file, uint16_t offset, uint16_t length)
{
  if ((file == NULL) || (dest == NULL) || (length == 0))
  {
    return -1;
  }
  if (offset > file->numBytes)
  {
    return -1;
  }
  if (offset + length > file->numBytes)
  {
    length = file->numBytes - offset;
  }
  memcpy(dest, file->bytes + offset, length);
  return 0;
}

int WriteFile(fs_file *file, uint8_t *source, uint16_t offset, uint16_t length)
{
  if ((file == NULL) || (source == NULL) || (length == 0))
  {
    return -1;
  }
  if (offset + length > MAX_FILESIZE)
  {
    return -1;
  }
  uint8_t *oldData = file->bytes;
  file->bytes = calloc(offset + length);
  if (offset > 0)
  {
    if (oldData != NULL)
    {
      if (file->numBytes >= offset)
      {
        memcpy(file->bytes, oldData, offset);
      } else {
        memcpy(file->bytes, oldData, file->numBytes);
      }
    }
  }
  memcpy(file->bytes + offset, source, length);
  file->numBytes = offset + length;
  free(oldData);
  return 0;
}

fs_tree *FindTreeByPath(uint32_t userID, uint8_t *path, uint8_t *service)
{
  for (int i=0; i < MAX_TREES; i++)
  {
    fs_tree *tree = &allTrees[i];
    if (strcmp(tree->treeName, (char *)path) == 0)
    {
      if (strcmp(tree->serviceType, (char *)service) == 0)
      {
        return tree;
      }
    }
  }
  return NULL;
}
