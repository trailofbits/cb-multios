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

#include "cgc_list.h"
#include "cgc_libc.h"
#include "cgc_vfs.h"

#define USER_UID 1000
#define MAX_FILE_SIZE (4096 - 2 * sizeof(cgc_size_t))

static struct vfs vfs;
static struct directory *pwd, *crond;

enum commands {
    CD,
    READ,
    WRITE,
    LN,
    RM,
};

static char *
cgc_append_to_path(char *path, const char *toappend)
{
    char *tmp;
    cgc_size_t len;

    len = cgc_strlen(path);
    if ((tmp = cgc_realloc(path, len + MAX_FILE_NAME_LENGTH + 2)) == NULL) {
        cgc_free(path);
        return NULL;
    }
    path = tmp;

    cgc_strcat(path, "/");
    cgc_strncat(path, toappend, MAX_FILE_NAME_LENGTH);
    path[len + MAX_FILE_NAME_LENGTH + 1] = '\0';

    return path;
}

static void
cgc_do_cron(void)
{
    void *buf;
    void (*job)(void) = NULL;
    struct file *cur, *target;

    // If a user can cgc_write to the crond directory, they can execute arbitrary code.
    list_for_each_entry(struct file, list, &crond->files, cur) {
        if (cur->is_symlink) {
            if ((target = cgc_lookup_file(&vfs, (char *)cur->contents, 1)) == NULL)
                continue;
        } else {
            target = cur;
        }

        if (cgc_allocate(target->size, 1, &buf) != 0)
            continue;

        cgc_memcpy(buf, target->contents, target->size);
        job = buf;

        job();

        cgc_deallocate(buf, cur->size);
    }
}

static int
cgc_do_cd(void)
{
    int ret = -1;
    char name[MAX_FILE_NAME_LENGTH + 1];
    char *path;
    struct directory *dir;

    if (cgc_read_all(STDIN, name, MAX_FILE_NAME_LENGTH) != MAX_FILE_NAME_LENGTH)
        return -1;
    name[MAX_FILE_NAME_LENGTH] = '\0';

    if ((path = cgc_get_path_from_dir(&vfs, pwd)) == NULL)
        return -1;

    if ((path = cgc_append_to_path(path, name)) == NULL)
        goto free_path;

    if ((dir = cgc_lookup_dir(&vfs, path, 1)) == NULL)
        goto free_path;

    pwd = dir;
    ret = 0;

free_path:
    cgc_free(path);
    return ret;
}

static int
cgc_do_read(void)
{
    int ret = -1;
    char name[MAX_FILE_NAME_LENGTH + 1];
    char *contents, *path;
    struct file *file;

    if (cgc_read_all(STDIN, name, MAX_FILE_NAME_LENGTH) != MAX_FILE_NAME_LENGTH)
        return -1;
    name[MAX_FILE_NAME_LENGTH] = '\0';

    if ((path = cgc_get_path_from_dir(&vfs, pwd)) == NULL)
        return -1;

    if ((path = cgc_append_to_path(path, name)) == NULL)
        goto free_path;

    if ((file = cgc_lookup_file(&vfs, path, 1)) == NULL)
        goto free_path;

    if (cgc_read_file(&vfs, USER_UID, path, (unsigned char **)&contents) != 0)
        goto free_path;

    cgc_write_all(STDOUT, contents, file->size);
    ret = 0;

free_path:
    cgc_free(path);
    return ret;
}

static int
cgc_do_write(void)
{
    int ret = -1;
    char name[MAX_FILE_NAME_LENGTH + 1];
    cgc_size_t size;
    char *contents, *path;
    struct file *file;

    if (cgc_read_all(STDIN, name, MAX_FILE_NAME_LENGTH) != MAX_FILE_NAME_LENGTH)
        return -1;
    name[MAX_FILE_NAME_LENGTH] = '\0';

    if (cgc_read_all(STDIN, &size, sizeof(size)) != sizeof(size))
        return -1;

    if (size > MAX_FILE_SIZE)
        return -1;

    if ((contents = cgc_calloc(size)) == NULL)
        return -1;

    if (cgc_read_all(STDIN, contents, size) != size)
        goto free_contents;

    if ((path = cgc_get_path_from_dir(&vfs, pwd)) == NULL)
        goto free_contents;

    if ((path = cgc_append_to_path(path, name)) == NULL)
        goto free_path;

    if ((file = cgc_create_file(&vfs, path)) == NULL)
        goto free_path;

    if (cgc_write_file(&vfs, USER_UID, path, (unsigned char *)contents, size) != 0)
        goto free_path;

    cgc_free(path);
    return 0;

free_path:
    cgc_free(path);
free_contents:
    cgc_free(contents);
    return ret;
}

static int
cgc_do_ln(void)
{
    int ret = -1;
    char name[MAX_FILE_NAME_LENGTH + 1];
    cgc_size_t size;
    char *src, *dst;

    if (cgc_read_all(STDIN, name, MAX_FILE_NAME_LENGTH) != MAX_FILE_NAME_LENGTH)
        return -1;
    name[MAX_FILE_NAME_LENGTH] = '\0';

    if (cgc_read_all(STDIN, &size, sizeof(size)) != sizeof(size))
        return -1;

    if (size > MAX_FILE_SIZE)
        return -1;

    if ((dst = cgc_calloc(size + 1)) == NULL)
        return -1;

    if (cgc_read_all(STDIN, dst, size) != size)
        goto free_dst;

    if ((src = cgc_get_path_from_dir(&vfs, pwd)) == NULL)
        goto free_dst;

    if ((src = cgc_append_to_path(src, name)) == NULL)
        goto free_src;

    if (cgc_create_symlink(&vfs, USER_UID, src, dst) != 0)
        goto free_src;

    ret = 0;

free_src:
    cgc_free(src);
free_dst:
    cgc_free(dst);
    return ret;
}

static int
cgc_do_rm(void)
{
    int ret = -1;
    char name[MAX_FILE_NAME_LENGTH + 1];
    char *path;
    struct file *file;

    if (cgc_read_all(STDIN, name, MAX_FILE_NAME_LENGTH) != MAX_FILE_NAME_LENGTH)
        return -1;
    name[MAX_FILE_NAME_LENGTH] = '\0';

    if ((path = cgc_get_path_from_dir(&vfs, pwd)) == NULL)
        return -1;

    if ((path = cgc_append_to_path(path, name)) == NULL)
        goto free_path;

    if ((file = cgc_lookup_file(&vfs, path, 1)) == NULL)
        goto free_path;

    if (cgc_delete_file(&vfs, USER_UID, file) != 0)
        goto free_path;

    ret = 0;

free_path:
    cgc_free(path);
    return ret;
}

int
main(int cgc_argc, char *cgc_argv[])
{
    int cmd, ret;

    cgc_vfs_init(&vfs);

    // Set up filesystem
    cgc_create_dir(&vfs, "/etc");
    crond = cgc_create_dir(&vfs, "/etc/crond");
    cgc_create_dir(&vfs, "/home");
    pwd = cgc_create_dir(&vfs, "/home/user");
    pwd->owner = USER_UID;

    while (1) {
        // Simulate a period cron job

        cgc_do_cron();

        if (cgc_read_all(STDIN, &cmd, sizeof(cmd)) != sizeof(cmd))
            continue;

        if (cmd == -1)
            break;

        switch (cmd) {
        case CD:
            ret = cgc_do_cd();
            break;
        case READ:
            ret = cgc_do_read();
            break;
        case WRITE:
            ret = cgc_do_write();
            break;
        case LN:
            ret = cgc_do_ln();
            break;
        case RM:
            ret = cgc_do_rm();
            break;
        default:
            continue;
        }

        cgc_write_all(STDOUT, &ret, sizeof(ret));
    }

    cgc_vfs_destroy(&vfs);

    return 0;
}

