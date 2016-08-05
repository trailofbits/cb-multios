/*
 * Copyright (c) 2016 Kaprica Security, Inc.
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

#ifndef DIRECTORY_TREE_H_
#define DIRECTORY_TREE_H_

#include "fs_file.h"

class DirectoryTree
{
  public:
    DirectoryTree();
    DirectoryTree(fs_file *directory);
    void AddEntry(fs_file *file_info);
    fs_file *FindFile(const char *path);
    DirectoryTree *FindDirectory(const char *path);
    void ListFiles(const char *path, bool recursive);
    void ClearTree(bool delete_root);

    fs_file *directory_entry();
    Array<DirectoryTree> subdirectories();
    Array<fs_file *> file_list();

  private:
    fs_file *directory_entry_;
    Array<DirectoryTree> subdirectories_;
    Array<fs_file *> file_list_;

    bool FindFileHelper(DirectoryTree *dirnode, const char *path, DirectoryTree **found_dir, fs_file **found_file);
    void ListFileHelper(DirectoryTree *dirnode, const fs_file *file_info, bool recursive, const char *dirname, int namelen, bool skip_path_update);
    void ClearTreeHelper(DirectoryTree *dirnode);
};
#endif
