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

#include "file_manager.h"

FileManager::FileManager()
{
  numFiles = 0;
  numOpenedFiles = 0;
  rootDir = new File("/", File::FT_DIR, 0, 0);
  memset(openedFiles, 0, sizeof(openedFiles));
  cwd = rootDir;
}

FileManager::~FileManager()
{
}

File* FileManager::GetFile(const char* name)
{
  int i;
  List<File *> *files = cwd->GetFiles();
  if (!name || strcmp(name, ".") == 0)
    return cwd;
  if (strcmp(name, "..") == 0)
    return (cwd == rootDir) ? cwd : cwd->GetParent();
  if (!files)
    return 0;
  for (i = 0; i < files->length(); ++i)
  {
    File *file = files->get(i);
    if (strcmp(file->GetName(), name) == 0)
      return file;
  }
  return 0;
}

void FileManager::PrintFile(const char* name)
{
  int i;
  File *file = GetFile(name);
  if (!file)
    return;
  if (file->GetType() == File::FT_DIR)
  {
    List<File *> *files = file->GetFiles();
    printf("%d entries\n", files->length() + 2);
    printf("<DIR> D 0 .\n<DIR> D 0 ..\n");
    for (i = 0; files && i < files->length(); ++i)
    {
      File *f = files->get(i);
      f->PrintFileInfo();
    }
  }
  else
    file->PrintFileInfo();
}

int FileManager::CreateFile(const char* name)
{
  int i;
  if (numFiles == MAX_NUM_FILES)
    return -1;
  List<File *> *files = cwd->GetFiles();
  if (!files)
    return -2;
  if (strlen(name) > 255)
    return -4;
  if (!strcmp(name, ".") || !strcmp(name, "..") || !strcmp(name, "/"))
    return -3;
  for (i = 0; i < files->length(); ++i)
  {
    File *file = files->get(i);
    if (strcmp(file->GetName(), name) == 0)
      return -3;
  }
  File *file = new File(name, File::FT_REG, 0, cwd);
  files->add(file);
  numFiles++;
  return 0;
}

int FileManager::CreateDirectory(const char* name)
{
  int i;
  if (numFiles == MAX_NUM_FILES)
    return -1;
  List<File *> *files = cwd->GetFiles();
  if (!files)
    return -2;
  if (strlen(name) > 255)
    return -4;
  if (!strcmp(name, ".") || !strcmp(name, "..") || !strcmp(name, "/"))
    return -3;
  for (i = 0; i < files->length(); ++i)
  {
    File *file = files->get(i);
    if (strcmp(file->GetName(), name) == 0)
      return -3;
  }
  File *file = new File(name, File::FT_DIR, 0, cwd);
  files->add(file);
  numFiles++;
  return 0;
}

int FileManager::OpenFile(const char* name)
{
  int i;
  if (numOpenedFiles == MAX_NUM_OPENED_FILES)
    return -1;
  List<File *> *files = cwd->GetFiles();
  if (!files)
    return -2;
  if (!strcmp(name, ".") || !strcmp(name, "..") || !strcmp(name, "/"))
    return -3;
  for (i = 0; i < files->length(); ++i)
  {
    File *file = files->get(i);
    if (strcmp(file->GetName(), name) == 0)
    {
      if (file->GetType() == File::FT_DIR)
        return -3;
      if (file->IsOpened())
        return -4;
      int j;
      for (j = 0; j < MAX_NUM_OPENED_FILES; ++j)
        if (openedFiles[j] == 0)
          break;
      file->Open();
      openedFiles[j] = file;
      numOpenedFiles++;
      return j;
    }
  }
  return -5;
}

int FileManager::CloseFile(unsigned int fileno)
{
  if (fileno >= MAX_NUM_OPENED_FILES)
    return -1;
  File *file = openedFiles[fileno];
  if (!file)
    return -2;
  if (file->GetType() == File::FT_DIR)
    return -3;
  numOpenedFiles--;
  openedFiles[fileno] = 0;
  return file->Close();
}

int FileManager::CloseAll()
{
  int i;
  for (i = 0; i < MAX_NUM_OPENED_FILES; ++i)
  {
    if(openedFiles[i])
      CloseFile(i);
  }
  return 0;
}

int FileManager::ReadFile(unsigned int fileno, size_t pos, size_t len, char** outBuf)
{
  if (fileno >= MAX_NUM_OPENED_FILES)
    return -1;
  File *file = openedFiles[fileno];
  if (!file)
    return -2;
  return file->Read(pos, len, outBuf);
}

int FileManager::ModifyFile(unsigned int fileno, size_t pos, char *inBuf, size_t len)
{
  if (fileno >= MAX_NUM_OPENED_FILES)
    return -1;
  File *file = openedFiles[fileno];
  if (!file)
    return -2;
  return file->Write(pos, inBuf, len);
}

int FileManager::DeleteFile(const char* name)
{
  int i;
  List<File *> *files = cwd->GetFiles();
  if (!files)
    return -1;
  if (!strcmp(name, ".") || !strcmp(name, "..") || !strcmp(name, "/"))
    return -2;
  for (i = 0; i < files->length(); ++i)
  {
    File *file = files->get(i);
    if (strcmp(file->GetName(), name) == 0)
    {
      if (file->GetType() == File::FT_REG)
      {
#if PATCHED
        int j;
        for (j = 0; j < MAX_NUM_OPENED_FILES; ++j)
        {
          if (file == openedFiles[j])
          {
            CloseFile(j);
            break;
          }
        }
#endif
        files->remove(file);
        delete file;
        numFiles--;
        return 0;
      }
      else
        return -4;
    }
  }
  return -3;
}

void FileManager::DeleteDirectoryHelper(File *dir)
{
  int i;
  File *file;
  List<File *> *files = dir->GetFiles();
  while (files->length())
  {
    file = files->get(0);
    if (file->GetType() == File::FT_REG)
    {
      for (i = 0; i < MAX_NUM_OPENED_FILES; ++i)
      {
        if (file == openedFiles[i])
        {
          CloseFile(i);
          break;
        }
      }
    }
    else
    {
      DeleteDirectoryHelper(file);
    }
    files->remove(file);
    numFiles--;
    delete file;
  }
}

int FileManager::DeleteDirectory(const char* name)
{
  int i;
  bool found = false;
  File *file;
  List<File *> *files = cwd->GetFiles();
  if (!files)
    return -1;
  if (!strcmp(name, ".") || !strcmp(name, "..") || !strcmp(name, "/"))
    return -2;
  for (i = 0; i < files->length(); ++i)
  {
    file = files->get(i);
    if (strcmp(file->GetName(), name) == 0)
    {
      if (file->GetType() == File::FT_REG)
        return -3;
      found = true;
      break;
    }
  }
  if (!found)
    return -4;
  DeleteDirectoryHelper(file);
  files->remove(file);
  delete file;
  return 0;
}

int FileManager::ChangeDirectory(const char* name)
{
  int i;
  List<File *> *files = cwd->GetFiles();
  if (!files)
    return -1;
  if (!name || strcmp(name, "/") == 0)
  {
    cwd = rootDir;
    return 0;
  }
  if (strcmp(name, ".") == 0)
    return 0;
  if (strcmp(name, "..") == 0)
  {
    if (cwd != rootDir)
      cwd = cwd->GetParent();
    return 0;
  }
  for (i = 0; i < files->length(); ++i)
  {
    File *file = files->get(i);
    if (strcmp(file->GetName(), name) == 0)
    {
      if (file->GetType() != File::FT_DIR)
        return -2;
      cwd = file;
      return 0;
    }
  }
  return -3;
}
