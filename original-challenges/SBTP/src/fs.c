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
#include "stdint.h"
#include "malloc.h"
#include "fs.h"

#define DIRSEP "#"
#define DIRSEPCHR '#'
#define READMESTR "This is a sample file! Feel free to add your own!"

#define CHECKINIT() if (!root) init_fs();


static dirtree_t *root;

static void freedir(void *data);

static void freefile(void *data);

static bool get_file(void *fdata, void *data); 

static struct node *get_dir(struct node *cur, void *data);

char *ls_dir(char *path) {
    size_t len = 0;
    size_t idx;
    int i;
    char *dirlist;
    file_t *file;
    struct list *files;
    struct node *dirnode;
    dirtree_t *dir;
    struct node *head, *cur;
    size_t plen = strlen(path);

    debug("listing fs path @b\n", path);
    CHECKINIT();

    if (!plen) {
        debug("Path too short.\n");
        return NULL;
    } else if (plen == 1 && *path == DIRSEPCHR) {
        dir = root;
    } else {
        dirnode = list_find_node_with_data_recurse(&root->directories, &get_dir, path);
        if (!dirnode) {
            debug("Failed to find dir.\n");
            return NULL;
        }

        dir = (dirtree_t*)(dirnode->data);
    }

    files = &(dir->files);

    head = list_head_node(files);

    for (i=0, cur=head; i < list_length(files); i++) {
        len += strlen(((file_t*)cur->data)->name)+1;
        cur = cur->next;
    }

    len++;
    dirlist = calloc(len);

    if (!dirlist) {
        debug("Failed to allocate dirlist.\n");
        return NULL;
    }

    for (i=0, idx = 0, cur = head; i < list_length(files); i++) {
        file = ((file_t*)cur->data);
        strcpy(dirlist+idx, file->name);
        idx += strlen(file->name);
        *(dirlist+idx++) = ':';
        cur = cur->next;
    }

    *(dirlist+idx-1) = '\0';
    return dirlist;
}

int add_dir(char *path) {
    char *fn = NULL;
    char *tmp;
    char *parent;
    dirtree_t *nd;
    dirtree_t *dir;
    struct node *dirnode;

    debug("add dir @b\n", path);

    CHECKINIT();

    if (strlen(path) <= 1) {
        debug("Path is too short.\n");
        return 3;
    }

    if (strlen(path) > MAX_FILENAME_SIZE) {
        debug("Path is too long.\n");
        return 4;
    }

    dirnode = list_find_node_with_data_recurse(&root->directories, &get_dir, path);

    if (dirnode) {
        debug("Path already exists.\n");
        return 1;
    }

    parent = calloc(strlen(path)+1);

    if (!parent) {
        debug("Failed to allocate string.\n");
        return 2;
    }

    tmp = strtok(path, DIRSEPCHR);
    while (tmp) {
        if (fn) {
            if (!*fn)
                strcat(parent, DIRSEP);
            else
                strcat(parent, fn);
        }
        fn = tmp;
        tmp = strtok(NULL, DIRSEPCHR);
    }

    if (strlen(fn) < 1) {
        debug("Filename too short.\n");
        return 2;
    }

    if (strlen(parent) > 1) {
        dirnode = list_find_node_with_data_recurse(&root->directories, &get_dir, path);
        debug("path: @b\n",path);
        if (!dirnode) {
            debug("Failed to find directory.\n");
            return 3;
        }
        dir = (dirtree_t*)(dirnode->data);
    } else {
        dir = root;
    }

    nd = calloc(sizeof(dirtree_t));

    if (!nd) {
        debug("Failed to allocate directory.\n");
        return 1;
    }

    strcpy(nd->name, fn);

    list_init(&nd->directories, freedir);
    list_init(&nd->files, freefile);

    list_insert_at_end(&dir->directories, nd); 

    return 0;
}

int rm_dir(char *path) {
    char *fn = NULL;
    char *tmp = NULL;
    char *parent;
    size_t len;
    int i;
    struct list *dir;
    struct node *parentnode;
    struct node *cur;

    debug("rm dir @b\n", path);
    CHECKINIT();

    if(!path) {
        debug("Passed null path.\n");
        return 1;
    }

    len = strlen(path);

    if (len > MAX_FILENAME_SIZE) {
        debug("Path was too long.\n");
        return 2;
    }

    if (len <= 1) {
        debug("Path was too short.\n");
        return 7;
    }

    parent = calloc(len+1);

    if (!parent) {
        debug("Failed to allocate string.\n");
        return 3;
    }

    tmp = strtok(path, DIRSEPCHR);
    while (tmp) {
        if (fn) {
            if (!*fn)
                strcat(parent, DIRSEP);
            else
                strcat(parent, fn);
        }
        fn = tmp;
        tmp = strtok(NULL, DIRSEPCHR);
    }

    if (strlen(parent) == 1 && *parent == DIRSEPCHR) {
        dir = &root->directories;
    } else {
        parentnode = list_find_node_with_data_recurse(&root->directories, &get_dir, parent);

        if (!parentnode) {
            debug("Unable to find parent directory @b\n", parent);
            return 5;
        }

        dir = &((dirtree_t*)(parentnode->data))->directories;
    }

    if (!dir) {
        debug("Failed to get directory list.\n");
        return 6;
    }

    cur = list_head_node(dir);
    for (i=0; i < list_length(dir); i++) {
        if (streq(fn,((dirtree_t*)(cur->data))->name)) {
            list_remove_node(dir, cur);
            list_destroy_node(dir, &cur);
            return 0;
        }
        cur = cur->next;
    }
    
    debug("Failed to find directory to delete.\n");
    return 1;
}

int add_file(char *path, char *data) {
    file_t *nf;
    dirtree_t *dir;
    struct node *dirnode;
    char *fn = NULL;
    char *tmp;
    int i = 0, count = 0;
    size_t len;

    debug("add file @b\n", path);
    CHECKINIT();

    dirnode = list_find_node_with_data_recurse(&root->directories, &get_dir, path);

    if (!dirnode) {

        while (*(path+i) != '\0') {
            count += *(path+i++) == DIRSEPCHR;
        }

        if (*path != DIRSEPCHR && count != 1) {
            debug("Failed to parse file path.\n");
            return 1;
        } else {
            dir = root;
        }

    } else {
        dir = (dirtree_t *)dirnode->data;
    }

    tmp = strtok(path, DIRSEPCHR);

    while (tmp) {
        fn = tmp;
        tmp = strtok(NULL, DIRSEPCHR);
    }

    len = strlen(fn);

    if (len < 1) {
        debug("Filename too short.\n");
        return 2;
    }

    if (len > MAX_FILENAME_SIZE) {
        debug("Filename too long.\n");
        return 3;
    }

    if (strlen(data)+1 > MAX_FILE_SIZE) {
        debug("File data too long.\n");
        return 4;
    }

    if (!list_find_node_with_data(&dir->files, get_file, fn)) {
        nf  = calloc(sizeof(file_t));

        if (!nf) {
            debug("Failed to allocate new file.\n");
            return 7;
        }

        strcpy(nf->data, data);
        strcpy(nf->name, fn);

        list_insert_at_end(&dir->files, nf); 

        return 0;
    } else {
        debug("File already exists.\n");
        return 1;
    }
}

int rm_file(char *path) {
    char *fn = NULL;
    char *tmp = NULL;
    char *parent;
    size_t len;
    int i;
    struct list *files;
    struct node *parentnode;
    struct node *cur;

    debug("rm file @b\n", path);
    CHECKINIT();

    if(!path) {
        debug("Invalid arguments.\n");
        return 1;
    }

    len = strlen(path);

    if (len > MAX_FILENAME_SIZE) {
        debug("Path was too long.\n");
        return 2;
    }

    if (len <= 1) {
        debug("Path was too short.\n");
        return 7;
    }

    parent = calloc(len+1);

    if (!parent) {
        debug("Failed to allocate string.\n");
        return 3;
    }

    tmp = strtok(path, DIRSEPCHR);
    while (tmp) {
        if (fn) {
            if (!*fn)
                strcat(parent, DIRSEP);
            else
                strcat(parent, fn);
        }
        fn = tmp;
        tmp = strtok(NULL, DIRSEPCHR);
    }

    if (strlen(parent) == 1 && *parent == DIRSEPCHR) {
        files = &root->files;
    } else {
        parentnode = list_find_node_with_data_recurse(&root->directories, &get_dir, parent);

        if (!parentnode) {
            debug("Unable to find parent directory @b\n", parent);
            return 5;
        }

        files = &((dirtree_t*)(parentnode->data))->files;
    }

    if (!files) {
        debug("Could not enumerate directory.\n");
        return 7;
    }

    cur = list_head_node(files);
    for (i=0; i < list_length(files); i++) {
        debug("found @b\n",((file_t*)(cur->data))->name);
        if (streq(fn,((file_t*)(cur->data))->name)) {
            list_remove_node(files, cur);
            list_destroy_node(files, &cur);
            return 0;
        }
        cur = cur->next;
    }
    
    debug("Failed to find file to delete. @b @b\n", parent, fn);
    return 1;
}

char *readfile(char *path) {
    dirtree_t *dir;
    struct node *dirnode, *filenode;
    char *fn = NULL;
    char *tmp;
    char *parent;
    size_t plen;
    debug("read file @b\n", path);

    CHECKINIT();

    plen = strlen(path);

    if (plen > MAX_FILENAME_SIZE) {
        debug("File path too long.\n", path);
        return NULL;
    }

    if (plen <= 1) {
        debug("File path too short.\n");
        return NULL;
    }

    parent = calloc(MAX_FILENAME_SIZE);

    if (!parent) {
        debug("Failed to allocate string.\n");
        return NULL;
    }

    tmp = strtok(path, DIRSEPCHR);
    while (tmp) {
        if (fn) {
            if (!*fn)
                strcat(parent, DIRSEP);
            else
                strcat(parent, fn);
        }
        fn = tmp;
        tmp = strtok(NULL, DIRSEPCHR);
    }


    if (strlen(fn) < 1) {
        debug("Filename too short.\n");
        return NULL;
    }

    debug("parent: @b\n", parent);
    if (strlen(parent) == 1 && *parent == DIRSEPCHR) {
        filenode = list_find_node_with_data(&root->files, get_file, fn);
    } else {
        dirnode = list_find_node_with_data_recurse(&root->directories, &get_dir, parent);

        if (!dirnode) {
            debug("Could not find file directory: @b.\n", parent);
            return NULL;
        }

        dir = (dirtree_t *)dirnode->data;

        filenode = list_find_node_with_data(&dir->files, get_file, fn);
    }

    if (!filenode) {
        debug ("Could not find file.\n");
        return NULL;
    }

    return ((file_t*)filenode->data)->data;
}

void init_fs() {
    char readmepath[] = DIRSEP"README";
    debug("init_fs...\n");

    if (root)
        _terminate(8);

    root = calloc(sizeof(dirtree_t));

    if (!root)
        _terminate(9);

    strcpy(root->name, DIRSEP);

    list_init(&root->directories, freedir);
    list_init(&root->files, freefile);

    if (add_file(readmepath, READMESTR))
        _terminate(6);
}

static void freedir(void *data) {
    dirtree_t *dir = (dirtree_t*)data;

    debug("freeing dir @b\n", dir->name);

    list_destroy(&dir->directories);
    list_destroy(&dir->files);
    free(dir);
}

static void freefile(void *data) {
    file_t *file = (file_t *)data;
    debug("freeing file @b\n", file->name);

    free(file);
}

static bool get_file(void *fdata, void *data) {
    file_t *f = (file_t *)fdata;

    if (streq(f->name, (char *)data))
        return true;
    return false;
}

static struct node *get_dir(struct node *cur, void *data) {
    char *path = (char *)data;
    struct node *res;
    dirtree_t *d = (dirtree_t *)cur->data;
    char *tmp = d->name;

    if (*path++ != DIRSEPCHR)
        return NULL;

    while (*path != '\0' && *path != DIRSEPCHR) {
        if (*tmp++ != *path++)
            return NULL;
    }

    if (*tmp == '\0' && *path == '\0')
        return cur;

    if (*path == '\0')
        return NULL;

    if ((res = list_find_node_with_data_recurse(&d->directories, &get_dir, path))) {
        return res;
    } else {
        path++;
        while (*path != '\0') {
            if (*path == DIRSEPCHR)
                return NULL;
            path++;
        }
        return cur;
    }
}
