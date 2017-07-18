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

#include "cgc_libc.h"
#include "cgc_list.h"

#include "cgc_vfs.h"

int
cgc_vfs_init(struct vfs *vfs)
{
    return (vfs->root = cgc_calloc(sizeof(struct directory))) ? 0 : -1;
}

static void
cgc_directory_destroy(struct directory *dir)
{
    struct file *cur_file, *n_file;
    struct directory *cur_dir, *n_dir;

    list_for_each_entry_safe(struct file, list, &dir->files, n_file, cur_file) {
        cgc_free(cur_file->contents);
        cgc_free(cur_file);
    }

    list_for_each_entry_safe(struct directory, list, &dir->subdirectories, n_dir, cur_dir)
        cgc_directory_destroy(cur_dir);

    cgc_free(dir);
}

void
cgc_vfs_destroy(struct vfs *vfs)
{
    cgc_directory_destroy(vfs->root);
}

static int
cgc_dir_eq(const struct list_node *dir_, void *name_)
{
    const struct directory *dir = list_entry(struct directory, list, dir_);
    const utf8char *name = (const utf8char *)name_;

    return cgc_strncmp(dir->name, name, MAX_FILE_NAME_LENGTH) == 0;
}

static int
cgc_file_eq(const struct list_node *file_, void *name_)
{
    const struct file *file = list_entry(struct file, list, file_);
    const utf8char *name = (const utf8char *)name_;

    return cgc_strncmp(file->name, name, MAX_FILE_NAME_LENGTH) == 0;
}

struct directory *
cgc_lookup_dir(const struct vfs *vfs, const utf8char *path)
{
    struct directory *ret = NULL;
    struct directory *dir = vfs->root;
    cgc_size_t path_len;
    utf8char *path_dup, *cur, *next;

    while (*path == '/')
        path++;

    path_len = cgc_strlen(path);
    if (path_len == 0)
        return vfs->root;

    if ((path_dup = cgc_calloc(path_len + 1)) == NULL)
        return NULL;

    cgc_strncpy(path_dup, path, path_len);
    for (cur = cgc_strtok(path_dup, '/'), next = cgc_strtok(NULL, '/');
            dir && next != NULL;
            cur = next, next = cgc_strtok(NULL, '/'))
    {
        if (cgc_strcmp(cur, ".") == 0)
            continue;

        if (cgc_strcmp(cur, "..") == 0) {
            dir = dir->parent;
            continue;
        }

        if ((dir = list_find_entry(struct directory, list, &dir->subdirectories,
                        cgc_dir_eq, (void *)cur)) == NULL) {
            goto free_path;
        }
    }

    ret = list_find_entry(struct directory, list, &dir->subdirectories, cgc_dir_eq, (void *)cur);

free_path:
    cgc_free(path_dup);
    return ret;
}

struct file *
cgc_lookup_file(const struct vfs *vfs, const utf8char *path)
{
    struct file *ret = NULL;
    struct directory *dir = vfs->root;
    cgc_size_t path_len;
    utf8char *path_dup, *name;

    path_len = cgc_strlen(path);
    if (path[path_len - 1] == '/')
        return NULL;

    if ((path_dup = cgc_calloc(path_len + 1)) == NULL)
        return NULL;

    cgc_strncpy(path_dup, path, path_len + 1);

    if ((name = cgc_strrchr(path_dup, '/')) != NULL) {
        *name++ = '\0';
        dir = cgc_lookup_dir(vfs, path_dup);
    } else {
        name = path_dup;
    }

    if (dir != NULL)
        ret = list_find_entry(struct file, list, &dir->files, cgc_file_eq, (void *)name);

    cgc_free(path_dup);
    return ret;
}

struct directory *
cgc_create_dir(struct vfs *vfs, const utf8char *path)
{
    struct directory *ret = NULL;
    struct directory *dir = vfs->root;
    cgc_size_t path_len;
    utf8char *path_dup, *name;

    path_len = cgc_strlen(path);
    if ((path_dup = cgc_calloc(path_len + 1)) == NULL)
        return NULL;

    cgc_strncpy(path_dup, path, path_len + 1);
    while (path_dup[path_len - 1] == '/')
        path_dup[(path_len--) - 1] = '\0';

    if ((name = cgc_strrchr(path_dup, '/')) != NULL) {
        *name++ = '\0';
        dir = cgc_lookup_dir(vfs, path_dup);
    } else {
        name = path_dup;
    }

    if (dir != NULL)
        ret = cgc_create_dir_in_dir(vfs, dir, name);

    cgc_free(path_dup);
    return ret;
}

struct directory *
cgc_create_dir_in_dir(struct vfs *vfs, struct directory *dir, const utf8char *name)
{
    struct directory *ret;

    // Suppress unused warning
    (void)(vfs);

    // Ensure we can't create a file with the same name as a file
    if (cgc_list_find(&dir->files, cgc_file_eq, (void *)name) != NULL)
        return NULL;

    // If the directory arelady exists, return it
    if ((ret = list_find_entry(struct directory, list, &dir->subdirectories,
                    cgc_dir_eq, (void *)name)) != NULL) {
        return ret;
    }

    if ((ret = cgc_calloc(sizeof(struct directory))) != NULL) {
        cgc_strncpy(ret->name, name, MAX_FILE_NAME_LENGTH);
        ret->parent = dir;
        list_push_entry_front(struct directory, list, &dir->subdirectories, ret);
    }

    return ret;
}

struct file *
cgc_create_file(struct vfs *vfs, const utf8char *path)
{
    struct file *ret = NULL;
    struct directory *dir = vfs->root;
    cgc_size_t path_len;
    utf8char *path_dup, *name;

    path_len = cgc_strlen(path);
    if (path[path_len - 1] == '/')
        return NULL;

    if ((path_dup = cgc_calloc(path_len + 1)) == NULL)
        return NULL;

    cgc_strncpy(path_dup, path, path_len + 1);
    if ((name = cgc_strrchr(path_dup, '/')) != NULL) {
        *name++ = '\0';
        dir = cgc_lookup_dir(vfs, path_dup);
    } else {
        name = path_dup;
    }

    if (dir != NULL)
        ret = cgc_create_file_in_dir(vfs, dir, name);

    cgc_free(path_dup);
    return ret;
}

struct file *
cgc_create_file_in_dir(struct vfs *vfs, struct directory *dir, const utf8char *name)
{
    struct file *ret;

    // Suppress unused warning
    (void)vfs;

    // Ensure we can't create a file with the same name as a directory
    if (cgc_list_find(&dir->subdirectories, cgc_dir_eq, (void *)name) != NULL)
        return NULL;

    // If file already exists, return it
    if ((ret = list_find_entry(struct file, list, &dir->files,
                    cgc_file_eq, (void *)name)) != NULL) {
        return ret;
    }

    if ((ret = cgc_calloc(sizeof(struct file))) != NULL) {
        cgc_strncpy(ret->name, name, MAX_FILE_NAME_LENGTH);
        ret->parent = dir;
        list_push_entry_front(struct file, list, &dir->files, ret);
    }

    return ret;
}

void
cgc_delete_file(struct vfs *vfs, struct file *file)
{
    // Suppress unused warning
    (void)vfs;

    list_remove_entry(struct file, list, &file->parent->files, file);
    cgc_free(file->contents);
    cgc_free(file);
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
            cgc_printf("\t");
        cgc_printf("%s/\n", cur_dir->name);
        dump_directory(cur_dir, level + 1);
    }

    list_for_each_entry(struct file, list, &dir->files, cur_file) {
        for (i = 0; i < level; i++)
            cgc_printf("\t");
        cgc_printf("%s\n", cur_file->name);
    }
}

void
dump_vfs(const struct vfs *vfs)
{
    cgc_printf("/\n");
    dump_directory(vfs->root, 1);
}
#endif

