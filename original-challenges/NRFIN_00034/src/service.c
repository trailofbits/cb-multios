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

#include "list.h"
#include "libc.h"
#include "vfs.h"

#define USER_UID 1000
#define MAX_FILE_SIZE (4096 - 2 * sizeof(size_t))

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
append_to_path(char *path, const char *toappend)
{
    char *tmp;
    size_t len;

    len = strlen(path);
    if ((tmp = realloc(path, len + MAX_FILE_NAME_LENGTH + 2)) == NULL) {
        free(path);
        return NULL;
    }
    path = tmp;

    strcat(path, "/");
    strncat(path, toappend, MAX_FILE_NAME_LENGTH);
    path[len + MAX_FILE_NAME_LENGTH + 1] = '\0';

    return path;
}

static void
do_cron(void)
{
    void *buf;
    void (*job)(void) = NULL;
    struct file *cur, *target;

    // If a user can write to the crond directory, they can execute arbitrary code.
    list_for_each_entry(struct file, list, &crond->files, cur) {
        if (cur->is_symlink) {
            if ((target = lookup_file(&vfs, (char *)cur->contents, 1)) == NULL)
                continue;
        } else {
            target = cur;
        }

        if (allocate(target->size, 1, &buf) != 0)
            continue;

        memcpy(buf, target->contents, target->size);
        job = buf;

        job();

        deallocate(buf, cur->size);
    }
}

static int
do_cd(void)
{
    int ret = -1;
    char name[MAX_FILE_NAME_LENGTH + 1];
    char *path;
    struct directory *dir;

    if (read_all(STDIN, name, MAX_FILE_NAME_LENGTH) != MAX_FILE_NAME_LENGTH)
        return -1;
    name[MAX_FILE_NAME_LENGTH] = '\0';

    if ((path = get_path_from_dir(&vfs, pwd)) == NULL)
        return -1;

    if ((path = append_to_path(path, name)) == NULL)
        goto free_path;

    if ((dir = lookup_dir(&vfs, path, 1)) == NULL)
        goto free_path;

    pwd = dir;
    ret = 0;

free_path:
    free(path);
    return ret;
}

static int
do_read(void)
{
    int ret = -1;
    char name[MAX_FILE_NAME_LENGTH + 1];
    char *contents, *path;
    struct file *file;

    if (read_all(STDIN, name, MAX_FILE_NAME_LENGTH) != MAX_FILE_NAME_LENGTH)
        return -1;
    name[MAX_FILE_NAME_LENGTH] = '\0';

    if ((path = get_path_from_dir(&vfs, pwd)) == NULL)
        return -1;

    if ((path = append_to_path(path, name)) == NULL)
        goto free_path;

    if ((file = lookup_file(&vfs, path, 1)) == NULL)
        goto free_path;

    if (read_file(&vfs, USER_UID, path, (unsigned char **)&contents) != 0)
        goto free_path;

    write_all(STDOUT, contents, file->size);
    ret = 0;

free_path:
    free(path);
    return ret;
}

static int
do_write(void)
{
    int ret = -1;
    char name[MAX_FILE_NAME_LENGTH + 1];
    size_t size;
    char *contents, *path;
    struct file *file;

    if (read_all(STDIN, name, MAX_FILE_NAME_LENGTH) != MAX_FILE_NAME_LENGTH)
        return -1;
    name[MAX_FILE_NAME_LENGTH] = '\0';

    if (read_all(STDIN, &size, sizeof(size)) != sizeof(size))
        return -1;

    if (size > MAX_FILE_SIZE)
        return -1;

    if ((contents = calloc(size)) == NULL)
        return -1;

    if (read_all(STDIN, contents, size) != size)
        goto free_contents;

    if ((path = get_path_from_dir(&vfs, pwd)) == NULL)
        goto free_contents;

    if ((path = append_to_path(path, name)) == NULL)
        goto free_path;

    if ((file = create_file(&vfs, path)) == NULL)
        goto free_path;

    if (write_file(&vfs, USER_UID, path, (unsigned char *)contents, size) != 0)
        goto free_path;

    free(path);
    return 0;

free_path:
    free(path);
free_contents:
    free(contents);
    return ret;
}

static int
do_ln(void)
{
    int ret = -1;
    char name[MAX_FILE_NAME_LENGTH + 1];
    size_t size;
    char *src, *dst;

    if (read_all(STDIN, name, MAX_FILE_NAME_LENGTH) != MAX_FILE_NAME_LENGTH)
        return -1;
    name[MAX_FILE_NAME_LENGTH] = '\0';

    if (read_all(STDIN, &size, sizeof(size)) != sizeof(size))
        return -1;

    if (size > MAX_FILE_SIZE)
        return -1;

    if ((dst = calloc(size + 1)) == NULL)
        return -1;

    if (read_all(STDIN, dst, size) != size)
        goto free_dst;

    if ((src = get_path_from_dir(&vfs, pwd)) == NULL)
        goto free_dst;

    if ((src = append_to_path(src, name)) == NULL)
        goto free_src;

    if (create_symlink(&vfs, USER_UID, src, dst) != 0)
        goto free_src;

    ret = 0;

free_src:
    free(src);
free_dst:
    free(dst);
    return ret;
}

static int
do_rm(void)
{
    int ret = -1;
    char name[MAX_FILE_NAME_LENGTH + 1];
    char *path;
    struct file *file;

    if (read_all(STDIN, name, MAX_FILE_NAME_LENGTH) != MAX_FILE_NAME_LENGTH)
        return -1;
    name[MAX_FILE_NAME_LENGTH] = '\0';

    if ((path = get_path_from_dir(&vfs, pwd)) == NULL)
        return -1;

    if ((path = append_to_path(path, name)) == NULL)
        goto free_path;

    if ((file = lookup_file(&vfs, path, 1)) == NULL)
        goto free_path;

    if (delete_file(&vfs, USER_UID, file) != 0)
        goto free_path;

    ret = 0;

free_path:
    free(path);
    return ret;
}

int
main(void)
{
    int cmd, ret;

    vfs_init(&vfs);

    // Set up filesystem
    create_dir(&vfs, "/etc");
    crond = create_dir(&vfs, "/etc/crond");
    create_dir(&vfs, "/home");
    pwd = create_dir(&vfs, "/home/user");
    pwd->owner = USER_UID;

    while (1) {
        // Simulate a period cron job

        do_cron();

        if (read_all(STDIN, &cmd, sizeof(cmd)) != sizeof(cmd))
            continue;

        if (cmd == -1)
            break;

        switch (cmd) {
        case CD:
            ret = do_cd();
            break;
        case READ:
            ret = do_read();
            break;
        case WRITE:
            ret = do_write();
            break;
        case LN:
            ret = do_ln();
            break;
        case RM:
            ret = do_rm();
            break;
        default:
            continue;
        }

        write_all(STDOUT, &ret, sizeof(ret));
    }

    vfs_destroy(&vfs);

    return 0;
}

