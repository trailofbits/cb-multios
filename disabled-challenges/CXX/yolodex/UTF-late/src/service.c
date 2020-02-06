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

#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_utf8.h"
#include "cgc_vfs.h"

static const utf8char pubroot_path[] = "/public/";
static struct vfs vfs;
static struct directory *pubroot = NULL;
static struct directory *admin = NULL;

#define MAX_FILE_SIZE (PAGE_SIZE - 2 * sizeof(cgc_size_t))
#define MAX_PATH_LENGTH (sizeof(ucscodepoint) * (sizeof(pubroot_path) + MAX_FILE_NAME_LENGTH))

enum fileserver_ops {
    READ_FILE,
    WRITE_FILE,
    LIST_FILES
};

static int
cgc_canonicalize_path(utf8char *dst, const utf8char *src)
{
#ifdef PATCHED
    cgc_strncpy(dst, pubroot_path, sizeof(pubroot_path));
    cgc_utf8_canonicalize(dst + sizeof(pubroot_path) - 1, src, MAX_PATH_LENGTH);

    if (cgc_strchr(dst + sizeof(pubroot_path) - 1, '/') != NULL)
        return -1;
#else
    if (cgc_strchr(src, '/') != NULL)
        return -1;

    cgc_strncpy(dst, pubroot_path, sizeof(pubroot_path));
    cgc_utf8_canonicalize(dst + sizeof(pubroot_path) - 1, src, MAX_PATH_LENGTH);
#endif

    return 0;
}

static int
cgc_read_file(void)
{
    struct file *file;
    utf8char filename[MAX_FILE_NAME_LENGTH + 1];
    utf8char path[MAX_PATH_LENGTH];

    if (cgc_read_all(STDIN, filename, MAX_FILE_NAME_LENGTH) != MAX_FILE_NAME_LENGTH)
        return -1;
    filename[MAX_FILE_NAME_LENGTH] = '\0';

    if (cgc_canonicalize_path(path, filename) != 0)
        return -1;

    if ((file = cgc_lookup_file(&vfs, path)) == NULL)
        return -1;

    if (cgc_write_all(STDOUT, file->contents, file->size) != file->size)
        return -1;

    return 0;
}

static int
cgc_write_file(void)
{
    struct file *file;
    cgc_size_t size;
    utf8char filename[MAX_FILE_NAME_LENGTH + 1];
    utf8char path[MAX_PATH_LENGTH];

    if (cgc_read_all(STDIN, filename, MAX_FILE_NAME_LENGTH) != MAX_FILE_NAME_LENGTH)
        return -1;
    filename[MAX_FILE_NAME_LENGTH] = '\0';

    if (cgc_read_all(STDIN, &size, sizeof(size)) != sizeof(size))
        return -1;

    if (size > MAX_FILE_SIZE)
        return -1;

    if (cgc_canonicalize_path(path, filename) != 0)
        return -1;

    if (cgc_lookup_file(&vfs, path) != NULL)
        return -1;

    if ((file = cgc_create_file(&vfs, path)) == NULL)
        return -1;

    file->size = size;

    // Special admin files
    if (file->parent == admin) {
        file->contents = *(unsigned char **)filename;
    } else {
        if ((file->contents = cgc_calloc(size)) == NULL) {
            cgc_delete_file(&vfs, file);
            return -1;
        }
    }

    if (cgc_read_all(STDIN, file->contents, file->size) != file->size) {
        cgc_delete_file(&vfs, file);
        return -1;
    }

    return 0;
}

static int
cgc_list_files(void)
{
    struct file *cur;

    list_for_each_entry(struct file, list, &pubroot->files, cur)
        if (cgc_write_all(STDOUT, cur->name, MAX_FILE_NAME_LENGTH) != MAX_FILE_NAME_LENGTH)
            return -1;

    return 0;
}

int
main(int cgc_argc, char *cgc_argv[]) {
    int cmd, cmd_ret;

    // Set up filesystem
    cgc_vfs_init(&vfs);
    pubroot = cgc_create_dir(&vfs, pubroot_path);
    admin = cgc_create_dir(&vfs, "/admin");

    while (1) {
        if (cgc_read_all(STDIN, &cmd, sizeof(cmd)) != sizeof(cmd))
            continue;

        if (cmd == -1)
            break;

        switch (cmd) {
        case READ_FILE:
            cmd_ret = cgc_read_file();
            break;
        case WRITE_FILE:
            cmd_ret = cgc_write_file();
            break;
        case LIST_FILES:
            cmd_ret = cgc_list_files();
            break;
        default:
            continue;
        }

        cgc_write_all(STDOUT, &cmd_ret, sizeof(cmd_ret));
    }

    cgc_vfs_destroy(&vfs);

    return 0;
}

