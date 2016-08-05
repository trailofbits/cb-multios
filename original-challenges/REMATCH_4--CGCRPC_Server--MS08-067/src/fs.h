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
#ifndef FILE_H
#define FILE_H

#include "stdint.h"

#define MAX_TREES 10
#define MAX_FILES_PER_TREE 10

// Error codes
#define FS_ACCESS_DENIED  0x10
#define FS_FILE_NOT_FOUND 0x20

// File modes
#define FS_MODE_CREATE    0x31
#define FS_MODE_READ      0x32
#define FS_MODE_OVERWRITE 0x33
#define FS_MODE_WRITE     0x34

#define MAX_FILENAME_LEN  128
#define MAX_TREENAME_LEN  128
#define MAX_SERVICE_NAME  64
#define MAX_SERVICE_TYPES 5
#define MAX_FILESIZE      1024

typedef struct file_s {
  uint16_t fileID;
  char filename[MAX_FILENAME_LEN];
  uint16_t numBytes;
  uint8_t isOpen;
  uint8_t *bytes;
} fs_file;

typedef struct tree_s {
  uint32_t treeID; 
  char treeName[MAX_TREENAME_LEN];
  char serviceType[MAX_SERVICE_NAME];
  fs_file *files[MAX_FILES_PER_TREE];
} fs_tree;

extern fs_tree allTrees[MAX_TREES];
extern char serviceTypes[MAX_SERVICE_TYPES][MAX_SERVICE_NAME];

void InitializeFileSystem();
fs_file *CreateFile(fs_tree *tree, uint8_t *filename, uint32_t userID, uint32_t mode);
void CloseFile(fs_file *file);
fs_file *FindFileByName(fs_tree *tree, uint8_t *filename);
int ReadFile(uint8_t *dest, fs_file *file, uint16_t offset, uint16_t length);
int WriteFile(fs_file *file, uint8_t *source, uint16_t offset, uint16_t length);
fs_tree *FindTreeByPath(uint32_t userID, uint8_t *path, uint8_t *service);

#endif



