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

#include "directory_tree.h"
#include <cstring.h>
#include <cstdio.h>

#include "print.h"

namespace {

void PrintFile(const fs_file *file_metadata, unsigned char num_tabs)
{
    for (int i = 0; i < num_tabs; i++)
        printf("    ");
    printf("File Name: ");
    PRINT_ARR_CHARS(file_metadata->name, sizeof(file_metadata->name));
}
void PrintSubdirectory(const fs_file *file_metadata, unsigned char num_tabs)
{
    for (int i = 0; i < num_tabs; i++)
        printf("    ");
    printf("Subdirectory Name: ");
    PRINT_ARR_CHARS(file_metadata->name, sizeof(file_metadata->name));
}
void PrintDirectory(const fs_file *file_metadata, char *dirname, int *namelen, bool skip_path_update)
{

    char *pname = &dirname[*namelen];
    for (int i = 0; i < sizeof(file_metadata->name); i++)
    {
        if (file_metadata->name[i] != 0x20 && !skip_path_update)
        {
            *pname++ = file_metadata->name[i];
            ++*namelen;
        }
    }
    if (dirname[*namelen-1] != '/' && (*namelen != 1 || *dirname != '/'))
    {

        *pname = '/';
        ++*namelen;
    }

    printf("Directory Name: ");
    PRINT_ARR_CHARS(dirname, *namelen);
}

}

DirectoryTree::DirectoryTree()
{
    directory_entry_ = (fs_file *)NULL;
}

DirectoryTree::DirectoryTree(fs_file *directory)
{
    directory_entry_ = directory;
}

void DirectoryTree::AddEntry(fs_file *file_info)
{
    if (!file_info)
        return;

    if (CgFsFile::IsDirectory(file_info))
        subdirectories_.Append(DirectoryTree(file_info));
    else
        file_list_.Append(file_info);
}


fs_file *DirectoryTree::FindFile(const char *path)
{
    if (!path)
        return (fs_file *)NULL;
    if (strcmp("/", path) == 0)
        return directory_entry_;

    DirectoryTree *dir_tree;
    fs_file *file_meta;

    if (FindFileHelper(this, path, &dir_tree, &file_meta))
    {
        if (dir_tree)
            return dir_tree->directory_entry();
        else if(file_meta)
            return file_meta;
    }

    return (fs_file *)NULL;
}

DirectoryTree *DirectoryTree::FindDirectory(const char *path)
{
    if (!path)
        return (DirectoryTree *)NULL;
    if (strcmp("/", path) == 0)
        return this;

    DirectoryTree *dir_tree;
    fs_file *file_meta;

    if (FindFileHelper(this, path, &dir_tree, &file_meta))
    {
        if (dir_tree)
            return dir_tree;
    }

    return (DirectoryTree *)NULL;
}

void DirectoryTree::ListFiles(const char *path, bool recursive)
{
    DirectoryTree *dir_tree;
    fs_file *file_meta;
    if (!path || strcmp("/", path) == 0)
    {
        char rootdir[] = "";
        ListFileHelper(this, (fs_file *)NULL, recursive, rootdir, strlen(rootdir), false);
        return;
    }
    else
    {
        if (FindFileHelper(this, path, &dir_tree, &file_meta))
            ListFileHelper(dir_tree, file_meta, recursive, path, strlen(path), true);
    }
}

void DirectoryTree::ClearTree(bool delete_root)
{
    fs_file *root_entry;
    if (delete_root)
    {
        delete directory_entry_;
        root_entry = (fs_file *)NULL;
    }
    else
    {
        root_entry = directory_entry_;
    }

    ClearTreeHelper(this);
    directory_entry_ = root_entry;
}

fs_file *DirectoryTree::directory_entry()
{
    return directory_entry_;
}

Array<DirectoryTree> DirectoryTree::subdirectories()
{
    return subdirectories_;
}

Array<fs_file *> DirectoryTree::file_list()
{
    return file_list_;
}

bool DirectoryTree::FindFileHelper(DirectoryTree *dirnode, const char *path, DirectoryTree **found_dir, fs_file **found_file)
{
    *found_dir = (DirectoryTree *)NULL;
    *found_file = (fs_file *)NULL;

    bool end_of_path = false;
    char *dir_path = (char *)path;
    char *filename;
    unsigned short name_len = 0;
    if (*dir_path == '/')
        ++dir_path;
    filename = dir_path;

    for( ; *dir_path && *dir_path != '/'; dir_path++)
        ++name_len;
    if (!*dir_path)
        end_of_path = true;

    if (name_len > sizeof(((fs_file *)0)->name))
        return (fs_file *)NULL;

    for (int i = 0; i < dirnode->subdirectories_.length(); i++)
    {
        if (CgFsFile::NameEquals(dirnode->subdirectories_[i].directory_entry_, filename, name_len))
        {

            if (filename[name_len] == '\0' || (filename[name_len] == '/' && filename[name_len + 1] == '\0'))
            {
                *found_dir = &dirnode->subdirectories_[i];
                return true;
            }
            else
            {
                return FindFileHelper(&dirnode->subdirectories_[i], filename + name_len, found_dir, found_file);
            }
        }
    }

    if (end_of_path)
    {
        for (int i = 0; i < dirnode->file_list_.length(); i++)
        {
            if (CgFsFile::NameEquals(dirnode->file_list_[i], filename, name_len))
            {
                *found_file = dirnode->file_list_[i];
                return true;
            }
        }
    }

    return false;
}

void DirectoryTree::ListFileHelper(DirectoryTree *dirnode, const fs_file *file_info, bool recursive, const char *dirname, int namelen,
                                    bool skip_path_update)
{
    char *cur_dir = (char *)NULL;
    int cur_namelen = 0;
    if (dirnode)
    {
        cur_dir = new char[namelen + sizeof(((fs_file *)0)->name) + 1];
        cur_namelen = namelen;
        memcpy(cur_dir, dirname, namelen);

        PrintDirectory(dirnode->directory_entry_, cur_dir, &cur_namelen, skip_path_update);
        if (!dirnode->subdirectories_.length() && !dirnode->file_list_.length())
        {
            printf("    --Empty Directory--" NL NL);
            return;
        }

        for (int i = 0; i < dirnode->subdirectories_.length(); i++)
            PrintSubdirectory(dirnode->subdirectories_[i].directory_entry(), 1);
        for (int i = 0; i < dirnode->file_list_.length(); i++)
            PrintFile(dirnode->file_list_[i], 1);
        printf(NL);

        if (recursive)
        {
            for (int i = 0; i < dirnode->subdirectories_.length(); i++)
                ListFileHelper(&dirnode->subdirectories_[i], (fs_file *)NULL, recursive, cur_dir, cur_namelen, false);
        }
    }
    else if (file_info)
    {
        PrintFile(file_info, 0);
    }

    if (cur_dir)
        delete[] cur_dir;

}

void DirectoryTree::ClearTreeHelper(DirectoryTree *dirnode)
{
    if (!dirnode)
        return;

    for (int i = 0; i < dirnode->subdirectories_.length(); i++)
        ClearTreeHelper(&dirnode->subdirectories_[i]);

    directory_entry_ = NULL;
    dirnode->subdirectories_.Clear();
    dirnode->file_list_.Clear();
}

