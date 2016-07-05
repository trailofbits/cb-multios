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

#include "libc.h"
#include "list.h"

#include "vfs.h"

int
vfs_init(struct vfs *vfs)
{
    return (vfs->root = calloc(sizeof(struct directory))) ? 0 : -1;
}

static void
directory_destroy(struct directory *dir)
{
    struct file *cur_file, *n_file;
    struct directory *cur_dir, *n_dir;

    list_for_each_entry_safe(struct file, list, &dir->files, n_file, cur_file) {
        free(cur_file->contents);
        free(cur_file);
    }

    list_for_each_entry_safe(struct directory, list, &dir->subdirectories, n_dir, cur_dir)
        directory_destroy(cur_dir);

    free(dir);
}

void
vfs_destroy(struct vfs *vfs)
{
    directory_destroy(vfs->root);
}

static int
dir_eq(const struct list_node *dir_, void *name_)
{
    const struct directory *dir = list_entry(struct directory, list, dir_);
    const utf8char *name = (const utf8char *)name_;

    return strncmp(dir->name, name, MAX_FILE_NAME_LENGTH) == 0;
}

static int
file_eq(const struct list_node *file_, void *name_)
{
    const struct file *file = list_entry(struct file, list, file_);
    const utf8char *name = (const utf8char *)name_;

    return strncmp(file->name, name, MAX_FILE_NAME_LENGTH) == 0;
}

struct directory *
lookup_dir(const struct vfs *vfs, const utf8char *path)
{
    struct directory *ret = NULL;
    struct directory *dir = vfs->root;
    size_t path_len;
    utf8char *path_dup, *cur, *next;

    while (*path == '/')
        path++;

    path_len = strlen(path);
    if (path_len == 0)
        return vfs->root;

    if ((path_dup = calloc(path_len + 1)) == NULL)
        return NULL;

    strncpy(path_dup, path, path_len);
    for (cur = strtok(path_dup, '/'), next = strtok(NULL, '/');
            dir && next != NULL;
            cur = next, next = strtok(NULL, '/'))
    {
        if (strcmp(cur, ".") == 0)
            continue;

        if (strcmp(cur, "..") == 0) {
            dir = dir->parent;
            continue;
        }

        if ((dir = list_find_entry(struct directory, list, &dir->subdirectories,
                        dir_eq, (void *)cur)) == NULL) {
            goto free_path;
        }
    }

    ret = list_find_entry(struct directory, list, &dir->subdirectories, dir_eq, (void *)cur);

free_path:
    free(path_dup);
    return ret;
}

struct file *
lookup_file(const struct vfs *vfs, const utf8char *path)
{
    struct file *ret = NULL;
    struct directory *dir = vfs->root;
    size_t path_len;
    utf8char *path_dup, *name;

    path_len = strlen(path);
    if (path[path_len - 1] == '/')
        return NULL;

    if ((path_dup = calloc(path_len + 1)) == NULL)
        return NULL;

    strncpy(path_dup, path, path_len + 1);

    if ((name = strrchr(path_dup, '/')) != NULL) {
        *name++ = '\0';
        dir = lookup_dir(vfs, path_dup);
    } else {
        name = path_dup;
    }

    if (dir != NULL)
        ret = list_find_entry(struct file, list, &dir->files, file_eq, (void *)name);

    free(path_dup);
    return ret;
}

struct directory *
create_dir(struct vfs *vfs, const utf8char *path)
{
    struct directory *ret = NULL;
    struct directory *dir = vfs->root;
    size_t path_len;
    utf8char *path_dup, *name;

    path_len = strlen(path);
    if ((path_dup = calloc(path_len + 1)) == NULL)
        return NULL;

    strncpy(path_dup, path, path_len + 1);
    while (path_dup[path_len - 1] == '/')
        path_dup[(path_len--) - 1] = '\0';

    if ((name = strrchr(path_dup, '/')) != NULL) {
        *name++ = '\0';
        dir = lookup_dir(vfs, path_dup);
    } else {
        name = path_dup;
    }

    if (dir != NULL)
        ret = create_dir_in_dir(vfs, dir, name);

    free(path_dup);
    return ret;
}

struct directory *
create_dir_in_dir(struct vfs *vfs, struct directory *dir, const utf8char *name)
{
    struct directory *ret;

    // Suppress unused warning
    (void)(vfs);

    // Ensure we can't create a file with the same name as a file
    if (list_find(&dir->files, file_eq, (void *)name) != NULL)
        return NULL;

    // If the directory arelady exists, return it
    if ((ret = list_find_entry(struct directory, list, &dir->subdirectories,
                    dir_eq, (void *)name)) != NULL) {
        return ret;
    }

    if ((ret = calloc(sizeof(struct directory))) != NULL) {
        strncpy(ret->name, name, MAX_FILE_NAME_LENGTH);
        ret->parent = dir;
        list_push_entry_front(struct directory, list, &dir->subdirectories, ret);
    }

    return ret;
}

struct file *
create_file(struct vfs *vfs, const utf8char *path)
{
    struct file *ret = NULL;
    struct directory *dir = vfs->root;
    size_t path_len;
    utf8char *path_dup, *name;

    path_len = strlen(path);
    if (path[path_len - 1] == '/')
        return NULL;

    if ((path_dup = calloc(path_len + 1)) == NULL)
        return NULL;

    strncpy(path_dup, path, path_len + 1);
    if ((name = strrchr(path_dup, '/')) != NULL) {
        *name++ = '\0';
        dir = lookup_dir(vfs, path_dup);
    } else {
        name = path_dup;
    }

    if (dir != NULL)
        ret = create_file_in_dir(vfs, dir, name);

    free(path_dup);
    return ret;
}

struct file *
create_file_in_dir(struct vfs *vfs, struct directory *dir, const utf8char *name)
{
    struct file *ret;

    // Suppress unused warning
    (void)vfs;

    // Ensure we can't create a file with the same name as a directory
    if (list_find(&dir->subdirectories, dir_eq, (void *)name) != NULL)
        return NULL;

    // If file already exists, return it
    if ((ret = list_find_entry(struct file, list, &dir->files,
                    file_eq, (void *)name)) != NULL) {
        return ret;
    }

    if ((ret = calloc(sizeof(struct file))) != NULL) {
        strncpy(ret->name, name, MAX_FILE_NAME_LENGTH);
        ret->parent = dir;
        list_push_entry_front(struct file, list, &dir->files, ret);
    }

    return ret;
}

void
delete_file(struct vfs *vfs, struct file *file)
{
    // Suppress unused warning
    (void)vfs;

    list_remove_entry(struct file, list, &file->parent->files, file);
    free(file->contents);
    free(file);
}

#ifdef DEBUG
static void
dump_directory(const struct directory *dir, unsigned int level)
{
    unsigned int i;
    struct file *cur_file;
    struct directory *cur_dir;

    list_for_each_entry(struct directory, list, &dir->subdirectories, cur_dir) {
        for (i = 0; i < level; i++)
            printf("\t");
        printf("%s/\n", cur_dir->name);
        dump_directory(cur_dir, level + 1);
    }

    list_for_each_entry(struct file, list, &dir->files, cur_file) {
        for (i = 0; i < level; i++)
            printf("\t");
        printf("%s\n", cur_file->name);
    }
}

void
dump_vfs(const struct vfs *vfs)
{
    printf("/\n");
    dump_directory(vfs->root, 1);
}
#endif

