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
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define MAX_FILENAME 64

typedef struct FileNode_s {
  char      name[MAX_FILENAME + 1];
  uint8_t   type;
  uint32_t  size;
  uint16_t  fileID;
  struct FileNode_s *prev;
  struct FileNode_s *next;
  struct FileNode_s *parent;
  struct FileNode_s *child;
  char   *contents;
} FileNode;

extern FileNode *root;
extern uint16_t numFiles;

// File Types (keep in order)
#define FILE_TEXT       0xf1
#define FILE_EXECUTABLE 0xf2
#define FILE_IMAGE      0xf3
#define FILE_LINK       0xf4
#define FILE_RAW        0xf5
#define FILE_LIBRARY    0xf6
#define FILE_DIRECTORY  0xf7
#define FILE_INVALID    0xf8 

#define MAX_FILE_SIZE 2048
#define MAX_FILESYSTEM_DEPTH 10
#define MAX_FILES_IN_SYSTEM 256

#define FS_SUCCESS               0
#define FS_ERROR_INVALID_INPUT  -1
#define FS_ERROR_FILE_NOT_FOUND -2
#define FS_ERROR_DUPLICATE_NAME -3
#define FS_ERROR_ACCESS_DENIED  -4
#define FS_ERROR_FS_FULL        -5

FileNode *InitializeFileSystem();
int CreateFile(char *name, uint8_t type, uint32_t size, char *contents, FileNode *parent);
int DeleteFile(char *name, FileNode *parent);
FileNode *FindFile(char *name, FileNode *parent);
uint16_t NextFileID();
uint8_t GetFileType(FileNode *file);
uint32_t GetFileSize(FileNode *file);
uint32_t GetFileID(FileNode *file);
char *GetFileName(FileNode *file);
char *GetFilePath(FileNode *file);
char *ReadFile(FileNode *file);
FileNode *GetParent(FileNode *file);
void DestroyNode(FileNode *node);
int GetPathDepth(FileNode *file);
FileNode *FindFileAbsolute(char *name);

#endif