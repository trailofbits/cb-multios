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
    if ((vfs->root = calloc(sizeof(struct directory))) == NULL)
        return -1;

    // Unnecessary, but do this explicitly anyway
    vfs->root->owner = ROOT_UID;
    return 0;
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
    const char *name = (const char *)name_;

    return strncmp(dir->name, name, MAX_FILE_NAME_LENGTH) == 0;
}

static int
file_eq(const struct list_node *file_, void *name_)
{
    const struct file *file = list_entry(struct file, list, file_);
    const char *name = (const char *)name_;

    return strncmp(file->name, name, MAX_FILE_NAME_LENGTH) == 0;
}

struct directory *
lookup_dir(const struct vfs *vfs, const char *path, int follow_links)
{
    struct directory *ret = NULL;
    struct directory *dir = vfs->root;
    struct list *files;
    struct file *file;
    size_t path_len;
    char *path_dup, *cur;

    path_len = strlen(path);
    if (path_len == 0)
        return vfs->root;

    if ((path_dup = calloc(path_len + 1)) == NULL)
        return NULL;

    strncpy(path_dup, path, path_len);
    for (cur = strtok(path_dup, '/'); cur != NULL; cur = strtok(NULL, '/'))
    {
        if (dir == NULL)
            break;

        if (strcmp(cur, ".") == 0)
            continue;

        if (strcmp(cur, "..") == 0) {
            dir = dir->parent;
            continue;
        }

        files = &dir->files;
        if ((dir = list_find_entry(struct directory, list, &dir->subdirectories,
                        dir_eq, (void *)cur)) == NULL) {
            if (follow_links && ((file = list_find_entry(struct file, list, files,
                            file_eq, (void *)cur)) != NULL) && file->is_symlink) {
                dir = lookup_dir(vfs, (const char *)file->contents, follow_links);
            } else {
                goto free_path;
            }
        }
    }

    ret = dir;

free_path:
    free(path_dup);
    return ret;
}

struct file *
lookup_file(const struct vfs *vfs, const char *path, int follow_links)
{
    struct file *ret = NULL;
    struct directory *dir = vfs->root;
    size_t path_len;
    char *path_dup, *name;

    path_len = strlen(path);
    if (path[path_len - 1] == '/')
        return NULL;

    if ((path_dup = calloc(path_len + 1)) == NULL)
        return NULL;

    strncpy(path_dup, path, path_len + 1);

    if ((name = strrchr(path_dup, '/')) != NULL) {
        *name++ = '\0';
        dir = lookup_dir(vfs, path_dup, follow_links);
    } else {
        name = path_dup;
    }

    if (dir != NULL)
        ret = list_find_entry(struct file, list, &dir->files, file_eq, (void *)name);

    free(path_dup);
    return (ret && follow_links && ret->is_symlink) ? lookup_file(vfs, (const char *)ret->contents, follow_links) : ret;
}

char *
get_path_from_dir(const struct vfs *vfs, const struct directory *dir)
{
    char *tmp, *ret;
    size_t cur_len, path_len = 1;
    const struct directory *cur = dir;

    if ((ret = calloc(1)) == NULL)
        return NULL;

    while (cur != vfs->root) {
        cur_len = strnlen(cur->name, MAX_FILE_NAME_LENGTH);
        if ((tmp = realloc(ret, path_len + cur_len + 1)) == NULL) {
            free(ret);
            return NULL;
        }
        ret = tmp;

        memmove(ret + cur_len + 1, ret, path_len);
        ret[cur_len] = '/';
        memcpy(ret, cur->name, cur_len);

        path_len += cur_len + 1;
        cur = cur->parent;
    }

    // Prepend leading slash
    if (path_len > 0) {
        if ((tmp = realloc(ret, path_len + 1)) == NULL) {
            free(ret);
            return NULL;
        }
        ret = tmp;
        memmove(ret + 1, ret, path_len);
    } else {
        if ((ret = calloc(2)) == NULL)
            return NULL;
    }
    ret[0] = '/';

    return ret;
}

char *
get_path_from_file(const struct vfs *vfs, const struct file *file)
{
    char *tmp, *ret;
    size_t name_len;

    name_len = strnlen(file->name, MAX_FILE_NAME_LENGTH);
    if ((ret = get_path_from_dir(vfs, file->parent)) == NULL)
        return NULL;

    if ((tmp = realloc(ret, strlen(ret) + name_len + 1)) == NULL) {
        free(ret);
        return NULL;
    }
    ret = tmp;

    strncat(ret, file->name, name_len);
    return ret;
}

uid_t
get_owner(const struct vfs *vfs, const char *path)
{
    struct directory *dir;
    struct file *file;

    if ((dir = lookup_dir(vfs, path, 0)) != NULL)
        return dir->owner;
    else if ((file = lookup_file(vfs, path, 0)) != NULL)
        return file->owner;
        
    return INVALID_UID;
}

int
read_file(const struct vfs *vfs, uid_t user, const char *path, unsigned char **contents)
{
    struct file *file;

    // We can read any file in our current model, so suppress unused warning
    (void)(user);

    if ((file = lookup_file(vfs, path, 1)) == NULL)
        return -1;

    if (contents != NULL)
        *contents = file->contents;

    return 0;
}

int
write_file(struct vfs *vfs, uid_t user, const char *path, unsigned char *contents, size_t size)
{
    struct file *file;

    if ((file = lookup_file(vfs, path, 1)) == NULL) {
        if ((file = create_file(vfs, path)) != NULL &&
                (user != file->owner && user != ROOT_UID)) {

            delete_file(vfs, ROOT_UID, file);
            return -1;
        }
    }

    if (file == NULL)
        return -1;

    if (user != file->owner && user != ROOT_UID)
        return -1;

    free(file->contents);
    file->contents = contents;
    file->size = size;

    return 0;
}

struct directory *
create_dir(struct vfs *vfs, const char *path)
{
    struct directory *ret = NULL;
    struct directory *dir = vfs->root;
    size_t path_len;
    char *path_dup, *name;

    path_len = strlen(path);
    if ((path_dup = calloc(path_len + 1)) == NULL)
        return NULL;

    strncpy(path_dup, path, path_len + 1);
    while (path_dup[path_len - 1] == '/')
        path_dup[(path_len--) - 1] = '\0';

    if ((name = strrchr(path_dup, '/')) != NULL) {
        *name++ = '\0';
        dir = lookup_dir(vfs, path_dup, 1);
    } else {
        name = path_dup;
    }

    if (dir != NULL)
        ret = create_dir_in_dir(vfs, dir, name);

    free(path_dup);
    return ret;
}

struct directory *
create_dir_in_dir(struct vfs *vfs, struct directory *dir, const char *name)
{
    struct directory *ret;

    // Suppress unused warning
    (void)(vfs);

    // Ensure we can't create a directory with the same name as a file
    if (list_find(&dir->files, file_eq, (void *)name) != NULL)
        return NULL;

    // If the directory already exists, return it
    if ((ret = list_find_entry(struct directory, list, &dir->subdirectories,
                    dir_eq, (void *)name)) != NULL) {
        return ret;
    }

    if ((ret = calloc(sizeof(struct directory))) != NULL) {
        strncpy(ret->name, name, MAX_FILE_NAME_LENGTH);
        ret->owner = dir->owner;
        ret->parent = dir;
        list_push_entry_front(struct directory, list, &dir->subdirectories, ret);
    }

    return ret;
}

struct file *
create_file(struct vfs *vfs, const char *path)
{
    struct file *ret = NULL;
    struct directory *dir = vfs->root;
    size_t path_len;
    char *path_dup, *name;

    path_len = strlen(path);
    if (path[path_len - 1] == '/')
        return NULL;

    if ((path_dup = calloc(path_len + 1)) == NULL)
        return NULL;

    strncpy(path_dup, path, path_len + 1);
    if ((name = strrchr(path_dup, '/')) != NULL) {
        *name++ = '\0';
        dir = lookup_dir(vfs, path_dup, 1);
    } else {
        name = path_dup;
    }

    if (dir != NULL)
        ret = create_file_in_dir(vfs, dir, name);

    free(path_dup);
    return ret;
}

struct file *
create_file_in_dir(struct vfs *vfs, struct directory *dir, const char *name)
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
        ret->owner = dir->owner;
        ret->parent = dir;
        list_push_entry_front(struct file, list, &dir->files, ret);
    }

    return ret;
}

int
create_symlink(struct vfs *vfs, uid_t user, const char *src_path, const char *dst_path)
{
    int ret = -1;
    struct file *file, *cur;
    unsigned char *contents;
    struct directory *dir = vfs->root;
    size_t src_path_len, dst_path_len;
    char *path_dup, *name;
    uid_t owner;

    src_path_len = strlen(src_path);
    if (src_path[src_path_len - 1] == '/')
        return -1;

    if (lookup_file(vfs, src_path, 0) != NULL)
        return -1;

    if ((path_dup = calloc(src_path_len + 1)) == NULL)
        return -1;

    strncpy(path_dup, src_path, src_path_len + 1);
    if ((name = strrchr(path_dup, '/')) != NULL) {
        *name++ = '\0';
#ifdef PATCHED
        dir = lookup_dir(vfs, path_dup, 1);
        if (dir == NULL)
            goto free_path;

        owner = dir->owner;
#else
        // Suppress unused variable warning
        (void)(dir);

        owner = get_owner(vfs, path_dup);
        if (owner == INVALID_UID)
            goto free_path;
#endif
    } else {
        name = path_dup;
        owner = vfs->root->owner;
    }

    if (user != owner && user != ROOT_UID)
        goto free_path;

    dst_path_len = strlen(dst_path);
    if ((contents = calloc(dst_path_len + 1)) == NULL)
        goto free_path;

    strncpy((char *)contents, dst_path, dst_path_len + 1);

    file = create_file(vfs, src_path);
    if (file == NULL)
        goto free_path;

    file->owner = user;
    file->is_symlink = 1;
    file->size = dst_path_len + 1;
    file->contents = contents;

#ifdef PATCHED
    // Detect cyclical symlinks
    for (cur = lookup_file(vfs, (char *)file->contents, 0);
         cur && cur->is_symlink;
         cur = lookup_file(vfs, (char *)cur->contents, 0)) {

        if (cur == file) {
            delete_file(vfs, user, file);
            goto free_path;
        }
    }
#else
    // Suppress unused variable warning
    (void)(cur);
#endif

    ret = 0;

free_path:
    free(path_dup);
    return ret;
}

int
delete_file(struct vfs *vfs, uid_t user, struct file *file)
{
    // Suppress unused warning
    (void)vfs;

    // Do we have permission to write to the file?
    if (user != file->owner && user != ROOT_UID)
        return -1;

    list_remove_entry(struct file, list, &file->parent->files, file);
    free(file->contents);
    free(file);

    return 0;
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

