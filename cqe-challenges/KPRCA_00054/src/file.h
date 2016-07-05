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

#ifndef FILE_H
#define FILE_H

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <stdint.h>
};

#include "llist.h"

class BaseFile
{
  public:
    BaseFile() {}
    virtual ~BaseFile() = 0;

    virtual int Open() = 0;
    virtual int Close() = 0;
    virtual int Read(size_t pos, size_t len, char **outBuf) = 0;
    virtual int Write(size_t pos, char *inBuf, size_t len) = 0;
    
    virtual void PrintFileInfo() = 0;
};

class File : public BaseFile
{
  public:
    enum FileType { FT_REG, FT_DIR };

  protected:
    char name[256];
    FileType type;
    size_t size;
    bool opened;
    union {
      char *content;
      List<File *> *files;
    } info;
    File *parent;

  public:
    File(const char* name, FileType type, size_t size, File* parent);
    ~File();

    const char* GetName() { return name; }
    FileType GetType() { return type; }
    size_t GetSize() { return size; }
    bool IsOpened() { return opened; }
    List<File *>* GetFiles() { return (type == FT_DIR ? info.files : 0); }
    File* GetParent() { return parent; }

    int Open();
    int Close();
    int Read(size_t pos, size_t len, char **outBuf);
    int Write(size_t pos, char *inBuf, size_t len);
    
    void PrintFileInfo();
};

#endif
