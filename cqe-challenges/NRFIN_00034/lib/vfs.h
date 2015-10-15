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

#define MAX_FILE_NAME_LENGTH 16
#define ROOT_UID 0
#define INVALID_UID ((uid_t)-1)

typedef unsigned int uid_t;

struct directory {
    char name[MAX_FILE_NAME_LENGTH];
    uid_t owner;
    struct directory *parent;
    struct list subdirectories;
    struct list files;
    struct list_node list;
};

struct file {
    char name[MAX_FILE_NAME_LENGTH];
    uid_t owner;
    int is_symlink;
    struct directory *parent;
    size_t size;
    unsigned char *contents;
    struct list_node list;
};

struct vfs {
    struct directory *root;
};

/**
 * Initialize a virtual file system.
 *
 * @param vfs The vfs to initialize
 * @return 0 on success, -1 on failure
 */
int vfs_init(struct vfs *vfs);

/**
 * Destroy a virtual file system.
 *
 * @param vfs The vfs to destroy
 */
void vfs_destroy(struct vfs *vfs);

/**
 * Lookup a directory in a virtual file system by path.
 *
 * @param vfs The vfs
 * @param path The path to lookup
 * @param follow_links Whether or not to follow symbolic links
 * @return A pointer to the directory structure, or NULL if not found
 */
struct directory *lookup_dir(const struct vfs *vfs, const char *path, int follow_links);

/**
 * Lookup a file in a virtual file system by path.
 *
 * @param vfs The vfs
 * @param path The path to lookup
 * @param follow_links Whether or not to follow symbolic links
 * @return A pointer to the file structure, or NULL if not found
 */
struct file *lookup_file(const struct vfs *vfs, const char *path, int follow_links);

/**
 * Get the path from the root of a directory structure.
 *
 * @param vfs The vfs
 * @param dir The directory structure
 * @return The path, or NULL if not found. Caller is responsible for freeing
 */
char *get_path_from_dir(const struct vfs *vfs, const struct directory *dir);

/**
 * Get the path from the root of a file structure.
 *
 * @param vfs The vfs
 * @param file The file structure
 * @return The path, or NULL if not found. Caller is responsible for freeing
 */
char *get_path_from_file(const struct vfs *vfs, const struct file *file);

/**
 * Get the owner of a file or directory.
 *
 * @param vfs The vf
 * @param path The path to check
 * @return The uid of the owner of the path, or INVALID_UID on error
 */
uid_t get_owner(const struct vfs *vfs, const char *path);

/**
 * Read the contents of a file, respecting permissions.
 *
 * Note: In our current model, any user can read any file.
 *
 * @param vfs The vfs
 * @param user The uid of the user
 * @param path The path to read
 * @param contents Set to the contents of the file on success
 * @return 0 on success, -1 on failure
 */
int read_file(const struct vfs *vfs, uid_t user, const char *path, unsigned char **contents);

/**
 * Write the contents of a file, respecting permissions.
 *
 * @param vfs The vfs
 * @param user The uid of the user
 * @param path The path to read
 * @param contents Buffer to set as the new file contents on success, will be
 *      freed on delete
 * @param size The new size of the file
 * @return 0 on success, -1 on failure
 */
int write_file(struct vfs *vfs, uid_t user, const char *path, unsigned char *contents, size_t size);

/**
 * Create a new directory at the given path.
 *
 * @param vfs The vfs
 * @param path The path to create a directory at
 * @return A pointer to the new directory structure, or NULL on failure
 */
struct directory *create_dir(struct vfs *vfs, const char *path);

/**
 * Create a new directory under the given directory.
 *
 * @param vfs The vfs
 * @param dir The directory to create a directory under
 * @param name The name of the new directory
 * @return A pointer to the new directory structure, or NULL on failure
 */
struct directory *create_dir_in_dir(struct vfs *vfs, struct directory *dir, const char *name);

/**
 * Create a new file at the given path.
 *
 * @param vfs The vfs
 * @param path The path to create a file at
 * @return A pointer to the new file structure, or NULL on failure
 */
struct file *create_file(struct vfs *vfs, const char *path);

/**
 * Create a new file under the given directory.
 *
 * @param vfs The vfs
 * @param dir The directory to create a file under
 * @param name The name of the new file
 * @return A pointer to the new file structure, or NULL on failure
 */
struct file *create_file_in_dir(struct vfs *vfs, struct directory *dir, const char *name);

/**
 * Create a new symbolic link, respecting permissions.
 *
 * @param vfs The vfs
 * @param user The uid of the user
 * @param src_path The path to create a link at
 * @param dst_path The path to point the link at
 * @return 0 on success, -1 on failure
 */
int create_symlink(struct vfs *vfs, uid_t user, const char *src_path, const char *dst_path);

/**
 * Delete a file, respecting permissions.
 *
 * @param vfs The vfs
 * @param user The uid of the user
 * @param file The file to delete
 * @return 0 on success, -1 on failure
 */
int delete_file(struct vfs *vfs, uid_t user, struct file *file);

#ifdef DEBUG
void dump_vfs(const struct vfs *vfs);
#endif

#endif /* VFS_H_ */

