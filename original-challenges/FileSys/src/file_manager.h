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

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

extern "C" {
  #include <stdlib.h>
  #include <string.h>
};

#include "file.h"

#define MAX_NUM_FILES 512
#define MAX_NUM_OPENED_FILES 20

class FileManager
{
  protected:
    unsigned int numFiles;
    unsigned int numOpenedFiles;
    File *rootDir;
    File* openedFiles[MAX_NUM_OPENED_FILES];
    File *cwd;
    
    void DeleteDirectoryHelper(File* dir);

  public:
    FileManager();
    ~FileManager();

    File* GetFile(const char* name);
    void PrintFile(const char* name);
    int CreateFile(const char* name);
    int CreateDirectory(const char* name);
    int OpenFile(const char* name);
    int CloseFile(unsigned int fileno);
    int CloseAll();
    int ReadFile(unsigned int fileno, size_t pos, size_t len, char** outBuf);
    int ModifyFile(unsigned int fileno, size_t pos, char* inBuf, size_t len);
    int DeleteFile(const char* name);
    int DeleteDirectory(const char* name);
    int ChangeDirectory(const char* name);
};

#endif
