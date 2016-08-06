/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/**
 * @file vfs.h
 *
 * In-memory virtual file system.
 */

#ifndef VFS_H_
#define VFS_H_

#include "libc.h"
#include "list.h"
#include "utf8.h"

#define MAX_FILE_NAME_LENGTH 16

struct directory {
    utf8char name[MAX_FILE_NAME_LENGTH];
    struct directory *parent;
    struct list subdirectories;
    struct list files;
    struct list_node list;
};

struct file {
    utf8char name[MAX_FILE_NAME_LENGTH];
    struct directory *parent;
    size_t size;
    unsigned char *contents;
    struct list_node list;
};

struct vfs {
    struct directory *root;
};

int vfs_init(struct vfs *vfs);
void vfs_destroy(struct vfs *vfs);

struct directory *lookup_dir(const struct vfs *vfs, const utf8char *path);
struct file *lookup_file(const struct vfs *vfs, const utf8char *path);

struct directory *create_dir(struct vfs *vfs, const utf8char *path);
struct directory *create_dir_in_dir(struct vfs *vfs, struct directory *dir, const utf8char *name);
struct file *create_file(struct vfs *vfs, const utf8char *path);
struct file *create_file_in_dir(struct vfs *vfs, struct directory *dir, const utf8char *name);

void delete_file(struct vfs *vfs, struct file *file);

#ifdef DEBUG
void dump_vfs(const struct vfs *vfs);
#endif

#endif /* VFS_H_ */

